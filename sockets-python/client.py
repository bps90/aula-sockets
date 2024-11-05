"""
Title: Simple Chat Client Python
Author: Bruno Pereira dos Santos
Date: 04/11/24
Description:
    This script starts a TCP/IP chat client that connects to a specified server address and port. 
    It allows the client to send messages to the server and receive responses in real-time. 
    Type 'exit' to close the connection and end the chat session.
.
"""

import socket
import argparse

def start_client(host, port):
    """Initializes the chat client and connects to the server."""
    # Create the TCP/IP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        client_socket.connect((host, port))
        print(f"Connected to the server at {host}:{port}")

        # Loop to send and receive messages
        while True:
            message = input("Client: ")
            if message.lower() == 'exit':
                break  # Exit the chat by typing 'exit'

            # Send message to the server
            client_socket.sendall(message.encode('utf-8'))

            # Receive response from the server
            response = client_socket.recv(1024).decode('utf-8')
            print(f"Server: {response}")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Start a TCP/IP chat client.",
        usage='%(prog)s <host> <port>'
    )
    parser.add_argument("host", type=str, help="The server address (e.g., 'localhost' or an IP address).")
    parser.add_argument("port", type=int, help="The server port (integer between 1 and 65535).")
    args = parser.parse_args()
    
    start_client(args.host, args.port)


