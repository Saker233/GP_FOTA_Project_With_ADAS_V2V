import serial
import time
import os
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer, QDate, QTime, Qt, QThread, pyqtSignal
from firebase_admin import credentials, storage, initialize_app
from security import decryption_process

# Initialize Firebase Admin SDK
cred = credentials.Certificate("fota-ce4bf-firebase-adminsdk-q2xub-a851db9e97.json")
initialize_app(cred, {'storageBucket': 'fota-ce4bf.appspot.com'})
bucket = storage.bucket()

class VersionChecker:
    """Class for checking and comparing software version numbers."""
    
    def __init__(self):
        pass

    def extract_version_from_filename(self, filename):
        """Extracts version numbers from a given filename.
        
        Args:
            filename (str): The filename containing version information.
        
        Returns:
            list: A list of integers representing the version numbers extracted from the filename.
                  Returns None if version numbers cannot be extracted.
        """
        try:
            # file_00_00_00 => [00, 00, 00]
            version_components = filename[:-4].split("_")[1:]  # Exclude ".hex" extension
            version_numbers = [int(component) for component in version_components]
            return version_numbers
        except (ValueError, IndexError):
            return None

    def compare_versions(self, version1, version2):
        """Compares two version numbers.
        
        Args:
            version1 (list): The first version number to compare.
            version2 (list): The second version number to compare.
        
        Returns:
            int: -1 if version1 is lower, 1 if version1 is higher, 0 if versions are equal.
        """
        for v1, v2 in zip(version1, version2):
            if v1 < v2:
                return -1  # version1 is lower
            elif v1 > v2:
                return 1  # version1 is higher
        return 0  # versions are equal
    

class VersionManager:
    """Class for managing software version metadata."""
    
    current_version = [0, 0, 0]
    description = "FOTA Team Welcome You"

    @classmethod
    def load_metadata(cls):
        """Loads metadata from the 'metadata' file."""
        try:
            with open("metadata", "r") as file:
                lines = file.readlines()
                cls.current_version = [int(num) for num in lines[0].strip().split('.')]
                cls.description = lines[1].strip()
                # print("Loaded metadata successfully:", cls.current_version, cls.description)
        except FileNotFoundError:
            cls.description = "No description available."
        except Exception as e:
            print("Error loading metadata:", e)

    @classmethod
    def save_metadata(cls):
        """Saves metadata to the 'metadata' file."""
        with open("metadata", "w") as file:
            file.write('.'.join(map(str, cls.current_version)) + '\n')
            file.write(cls.description)



class SerialCommunicator:
    """Class for serial communication."""
    
    def __init__(self, port_name, baud_rate=115200):
        """
        Initializes the SerialCommunicator.
        
        Args:
            port_name (str): The name of the serial port.
            baud_rate (int): The baud rate for serial communication. Default is 115200.
        """
        self.serial_port_name = port_name
        self.baud_rate = baud_rate
        self.serial_port = None

    def connect(self):
        """Connects to the serial port.
        
        Returns:
            bool: True if the connection is successful, False otherwise.
        """
        try:
            self.serial_port = serial.Serial(self.serial_port_name, self.baud_rate, timeout=1)
            return True
        except serial.SerialException:
            print("Failed to open serial port.")
            return False

    def send_command_and_wait(self, command, expected_response, timeout=1):
        """Sends a command and waits for a response.
        
        Args:
            command (bytes): The command to send.
            expected_response (bytes): The expected response from the target device.
            timeout (int): The maximum time (in seconds) to wait for a response. Default is 1 second.
        
        Returns:
            bool: True if the expected response is received within the timeout, False otherwise.
        """
        if not self.serial_port:
            print("Serial port is not open.")
            return False

        self.serial_port.write(command + b'\0')
        start_time = time.time()
        while time.time() - start_time < timeout:
            response = self.serial_port.read_until(expected_response)
            if expected_response in response:
                return True
        return False

    def flash_hex_file(self, hex_file_path):
        """Flashes a hex file to the target device.
        
        Args:
            hex_file_path (str): The path to the hex file to be flashed.
        """
        try:
            with open(hex_file_path, 'rb') as file:
                lines = file.readlines()
                total_lines = len(lines)
                lines_sent = 0
                for line in lines:
                    # print(f"Sending record {lines_sent + 1}/{total_lines} ({(lines_sent + 1) * 100 / total_lines:.2f}%)")
                    # print(line)
                    success = False
                    while not success:
                        success = self.send_command_and_wait(line.strip(), b'OK')
                        if success:
                            print("Target received correct response")
                        else:
                            print("Timeout or incorrect response from target")
                    lines_sent += 1
                print("[INFO] Transmission complete")
        except FileNotFoundError:
            print(f"Hex file '{hex_file_path}' not found.")

    def disconnect(self):
        """Disconnects from the serial port."""
        if self.serial_port and self.serial_port.is_open:
            self.serial_port.close()



class DownloadThread(QThread):
    """Thread for downloading files."""
    
    progress_signal = pyqtSignal(int, int, int, str)

    def __init__(self, file_name):
        """
        Initializes the DownloadThread.
        
        Args:
            file_name (str): The name of the file to download.
        """
        super().__init__()
        self.file_name = file_name

    def run(self):
        blob = bucket.get_blob(self.file_name)
        file_path = os.path.join(os.path.dirname(__file__), self.file_name)

        # Get the size of the blob
        total_size = blob.size
        if total_size is None:
            return

        CHUNK_SIZE = 1024  # 1 MB chunk size (adjust as needed)
        bytes_downloaded = 0

        # Downloading
        with open(file_path, 'wb') as file:
            # Download data from server and write it to file
            while bytes_downloaded < total_size:
                chunk = blob.download_as_bytes(start=bytes_downloaded, end=bytes_downloaded + CHUNK_SIZE - 1)
                file.write(chunk)
                bytes_downloaded += len(chunk)
                progress_percentage = min(int(bytes_downloaded * 100 / total_size), 100)
                self.progress_signal.emit(progress_percentage, bytes_downloaded, total_size, "Downloading")  # Emit progress signal

        # Decryption
        if decryption_process(file_path):
            # BootLoader
            port_name = '/dev/ttyS0'  # Example on Linux
            baud_rate = 115200

            communicator = SerialCommunicator(port_name, baud_rate)

            if communicator.connect():
                with open(file_path, 'rb') as file:
                    lines = file.readlines()
                    total_lines = len(lines)
                    lines_sent = 0
                    for line in lines:
                        success = False
                        while not success:
                            success = communicator.send_command_and_wait(line.strip(), b'OK')
                            if success:
                                print("Target received correct response")
                            else:
                                print("Timeout or incorrect response from target")
                        lines_sent += 1
                        progress_percentage = min(int(lines_sent  * 100 / total_lines), 100)
                        self.progress_signal.emit(progress_percentage, lines_sent, total_lines, "Installing")  # Emit progress signal
                    print("[INFO] Transmission complete")
                    communicator.disconnect()
                    
            
            UpdateChecker.current_file = self.file_name
        else:
            print("[Error]: Unauthorized Update")


class UpdateChecker():
    """Class for checking and handling software updates."""
    
    updates_available = pyqtSignal(bool)
    current_file = None

    def __init__(self, MainWindow=None, parent=None):
        """
        Initializes the UpdateChecker.
        
        Args:
            MainWindow (QtWidgets.QMainWindow): The main window of the application.
            parent: The parent object.
        """
        self.mainwindow = MainWindow
        self.parent = parent

    def check_update(self):
        """Checks for available updates."""
        v_checker = VersionChecker()
        new_version_file_name = self.get_new_version_filename()
        
        if new_version_file_name:
            reply = QtWidgets.QMessageBox.question(self.mainwindow, 'Update Available',
                                         'A newer version is available. Do you want to download it?',
                                         QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No, QtWidgets.QMessageBox.No)
            if reply == QtWidgets.QMessageBox.Yes:
                self.parent.progress_label.show()
                self.parent.progress_bar.show()  # Show the progress bar before starting the download
                self.download_thread = DownloadThread(new_version_file_name)
                self.download_thread.progress_signal.connect(self.update_progress_bar)  # Connect progress signal
                self.download_thread.finished.connect(self.download_complete)
                self.download_thread.start()
        else:
            QtWidgets.QMessageBox.information(self.mainwindow, 'No Update Available', 'Your application is up to date.')

    def get_new_version_filename(self):
        """Gets the filename of the latest version available."""
        v_checker = VersionChecker()
        for blob in bucket.list_blobs():
            remote_version = v_checker.extract_version_from_filename(blob.name)
            if remote_version and v_checker.compare_versions(remote_version, VersionManager.current_version) > 0:
                return blob.name
        return None

    def update_progress_bar(self, progress_value, bytes_downloaded, total_size, state):
        """Updates the progress bar."""
        print(progress_value)
        self.parent.progress_label.setText(f'{state}: {bytes_downloaded}/{total_size} {"bytes" if state == "Downloading" else "lines"}')
        self.parent.progress_bar.setValue(progress_value)
    
    def download_complete(self):
        """Handles completion of the download process."""
        self.parent.progress_bar.hide()
        
        # Update the current version and save it to the metadata file
        if UpdateChecker.current_file is not None:
            VersionManager.current_version = VersionChecker().extract_version_from_filename(UpdateChecker.current_file)
        VersionManager.save_metadata()
        reply = QtWidgets.QMessageBox.information(self.mainwindow, 'Download Complete', 'New version downloaded successfully.')
        if reply:
            self.parent.progress_bar.hide()
            self.parent.progress_label.hide()

        if self.parent:
            self.parent.notification_timer.start()

        self.parent.notification_list.clear()  # Clear all notifications
        self.parent.check_update_btn.setText("Check for update")
