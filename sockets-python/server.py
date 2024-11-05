"""
Title: Simple Chat Server Python
Author: Bruno Pereira dos Santos
Date: 04/11/24
Description:
    This script creates a TCP/IP socket and associates it with the user-provided address and port. 
    It then accepts a connection from a client, waits for incoming messages, and sends responses back to the client.
"""

import socket
import argparse

def start_server(host, port):
    """Initializes and starts the chat server."""
    # Create the TCP/IP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the provided address and port
    server_socket.bind((host, port))
    print(f"Server started at {host}:{port}")

    # Enable the server to listen for connections
    server_socket.listen()
    print("Waiting for connections...")

    # Accept the client connection
    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")

    try:
        # Loop to receive messages
        while True:
            message = client_socket.recv(1024).decode("utf-8")
            if not message:
                break  # If there is no message, close the connection
            print(f"Client: {message}")

            # Send response to the client
            response = input("Server: ")
            client_socket.sendall(response.encode("utf-8"))
    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close the connections
        client_socket.close()
        server_socket.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Start a TCP/IP chat server.",
        usage='%(prog)s <host> <port>'
    )
    parser.add_argument("host", type=str, help="The server address (e.g., 'localhost' or '0.0.0.0').")
    parser.add_argument("port", type=int, help="The server port (integer between 1 and 65535).")
    args = parser.parse_args()
    
    start_server(args.host, args.port)


