import socket
import serial

serial_port = '/dev/ttyS0'
baud_rate = 9600

ser = serial.Serial(serial_port, baud_rate, timeout=1)

HOST = '0.0.0.0'
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((HOST, PORT))
    server_socket.listen()
    print(f"Listening for connections on {HOST}:{PORT}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address} has been established.")

        try:
            while True:
                data = client_socket.recv(1024)
                if not data:
                    break
                print("Received:", data.decode())
                
                if data == b'\x55':
                    
                    data_to_send = b'\x55'
                    
                    ser.write(data_to_send)
                    print("Data sent:", data_to_send)
        except Exception as e:
            print("Error:", e)
        finally:
            client_socket.close()

print("Server closed.")
