import os
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer, QDate, QTime, Qt, QThread, pyqtSignal
from fota_ui import Ui_FOTA
from utils import VersionManager, VersionChecker, UpdateChecker

# Change directory to the script's directory
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

class CUSTOM_FOTA(Ui_FOTA):
    """Customized FOTA (Firmware Over-The-Air) application."""

    def __init__(self, FOTA):
        """
        Initializes the custom FOTA application.

        Args:
            FOTA (QtWidgets.QMainWindow): The main window of the application.
        """
        super().__init__()
        self.setupUi(FOTA)  # Initialize the UI
        
        # Set window title
        _translate = QtCore.QCoreApplication.translate
        FOTA.setWindowTitle(_translate("FOTA", "FOTA"))

        # Load metadata for the application version
        VersionManager.load_metadata()
        # Set the main window as the default view
        self.stackedWidget.setCurrentIndex(0)

        # Initialize progress bar for updates
        self.progress_bar = QtWidgets.QProgressBar()
        # More code for progress bar setup...

        # Hide progress bar initially
        self.progress_bar.hide()
        self.progress_label.hide()

        # Initialize update checker
        self.UC = UpdateChecker(FOTA, self)
        self.check_update_btn.clicked.connect(self.UC.check_update)


        ###################### notification ##############################
        self.notification_list.doubleClicked.connect(self.download_update)
        
        # Check for updates every minute
        self.notification_timer = QTimer(FOTA)
        self.notification_timer.timeout.connect(self.check_for_updates)
        self.notification_timer.start(1000)  # .5 second

        # item font
        self.item_font = QtGui.QFont()
        self.item_font.setFamily("Segoe UI")
        self.item_font.setPointSize(10)
        self.item_font.setBold(False)
        self.item_font.setItalic(False)
        self.item_font.setWeight(50)
        self.item_font.setStrikeOut(False)

        ###################### Dashboard ##############################
        # update time and date
        self.update_timer = QTimer(FOTA)
        self.update_timer.timeout.connect(self.update_time_date_day)
        self.update_timer.start(1000)  # Update every second


        ###################### Main Board ##############################
        # main window control navigation
        self.dashboard_btn.clicked.connect(self.show_dashboard_page)
        self.update_btn.clicked.connect(self.show_update_page)
        self.notification_btn.clicked.connect(self.show_notification_page)
        self.about_btn.clicked.connect(self.show_about_page)
        
    def show_dashboard_page(self):
        """Switches to the dashboard page."""
        VersionManager.load_metadata()
        self.stackedWidget.setCurrentIndex(0)  # Show dashboard window

    def show_update_page(self):
        """Switches to the update page."""
        VersionManager.load_metadata()
        self.stackedWidget.setCurrentIndex(1)  # Show update window

    def show_notification_page(self):
        """Switches to the notification page."""
        VersionManager.load_metadata()
        self.stackedWidget.setCurrentIndex(2)  # Show notification window

    def show_about_page(self):
        """Switches to the about page."""
        # Note: this line needs to change 
        VersionManager.load_metadata()

        self.version_label.setText('Current Version: ' + '.'.join(map(str, VersionManager.current_version)))
        self.description_label.setText('Description: ' + VersionManager.description)

        self.stackedWidget.setCurrentIndex(3)  # Show about page

    def update_time_date_day(self):
        """Updates the current time, date, and day."""
        current_time = QTime.currentTime().toString(Qt.DefaultLocaleLongDate)
        current_date = QDate.currentDate().toString(Qt.DefaultLocaleLongDate)

        self.date_label.setText(current_date)
        self.time_label.setText(current_time)

    def add_notification(self, message, file_name):
        """
        Adds a notification to the notification list.

        Args:
            message (str): The notification message to display.
            file_name (str): The name of the file associated with the notification.
        """
        notification_item = QtWidgets.QListWidgetItem(message)
        notification_item.setTextAlignment(Qt.AlignHCenter | Qt.AlignTop)

        notification_item.setFont(self.item_font)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(Qt.SolidPattern)
        notification_item.setBackground(brush)
        brush = QtGui.QBrush(QtGui.QColor(75, 151, 226))
        brush.setStyle(Qt.SolidPattern)
        notification_item.setForeground(brush)

        notification_item.setData(Qt.UserRole, file_name)  # Store the file name in user data
        self.notification_list.addItem(notification_item)

    def check_for_updates(self):
        """Checks for updates and adds notifications if available."""
        vc = VersionChecker()
        new_version_file_name = self.UC.get_new_version_filename()
        if new_version_file_name:
            self.notification_timer.stop()
            v = vc.extract_version_from_filename(new_version_file_name)
            message = f'Update is available new version: {v[0]}.{v[1]}.{v[2]}. Double Click to download.'
            self.add_notification(message, new_version_file_name)

    def download_update(self, item):
        """
        Downloads an update based on the selected item in the notification list.

        Args:
            item (QtWidgets.QListWidgetItem): The selected item in the notification list.
        """
        file_name = item.data(Qt.UserRole)
        vc = VersionChecker()

        if file_name:
            v = vc.extract_version_from_filename(file_name)
            reply = QtWidgets.QMessageBox.question(FOTA, 'Download Update',
                                                    f'Do you want to download the updated version: {v[0]}.{v[1]}.{v[2]}?',
                                                    QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No,
                                                    QtWidgets.QMessageBox.No)
            if reply == QtWidgets.QMessageBox.Yes:
                self.check_update_btn.setText("Download Now")
                self.show_update_page()


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    FOTA = QtWidgets.QMainWindow()
    ui = CUSTOM_FOTA(FOTA)
    FOTA.show()
    sys.exit(app.exec_())
