# TCP Chat Server in C

A simple multi-client TCP chat server built using the C programming language. This project demonstrates how to set up a TCP server that can handle multiple client connections, receive messages, and respond to each client individually.

## Features

- **Server-Client Communication**: The server listens on a specific port (8888) and accepts connections from clients.
- **Message Exchange**: The server receives messages from the client and sends responses back.
- **Multi-client Support**: The server is capable of handling multiple clients (via threading, if implemented) and broadcasting messages.
- **Basic Socket Operations**: Utilizes socket programming fundamentals including socket creation, binding, listening, accepting connections, sending, and receiving messages.

## Project Structure

The project consists of the following files:

1. **TcpServer.c**: The main server-side implementation where the server listens for client connections, handles data exchange, and responds to clients.
2. **TcpClient.c**: The client-side implementation where users can send messages to the server.

## Requirements

To compile and run this project, you need:

- A C compiler (such as GCC)
- A Unix-like system (Linux, macOS, or Windows with Cygwin or WSL for networking libraries)

### On Linux/macOS:
Ensure you have the necessary libraries:

```bash
sudo apt-get install build-essential

