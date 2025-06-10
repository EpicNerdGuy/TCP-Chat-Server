# TCP Chat Server in C

This repository contains a simple TCP chat server and client implemented in C, demonstrating socket programming fundamentals. It enables real-time, bidirectional communication between a server and a single client over a TCP connection.

---

## 📌 Features

* Full-duplex chat communication using TCP.
* Uses `IPv4` and `SOCK_STREAM` sockets.
* Graceful error handling for socket operations.
* Clearly separates server and client logic.
* Accepts IP address as a command-line argument on the client side.
* Displays client IP upon connection.

---

## 🛠 Technologies Used

* **Language:** C
* **Platform:** Linux (tested on Kali Linux)
* **Libraries:**

  * `<sys/socket.h>`
  * `<netinet/in.h>`
  * `<arpa/inet.h>`
  * `<unistd.h>`
  * `<stdio.h>`, `<stdlib.h>`, `<string.h>`

---

## 🔧 Compilation

Use `gcc` to compile both the server and client files.

### Compile Server:

```bash
gcc -o tcpServer tcpServer.c
```

### Compile Client:

```bash
gcc -o tcpClient tcpClient.c
```

---

## 🚀 Usage

### 1. Start the Server

Run the compiled server binary:

```bash
./tcpServer
```

The server listens on `port 8086` and waits for an incoming connection.

### 2. Run the Client

On a different terminal or machine:

```bash
./tcpClient <server_ip>
```

Replace `<server_ip>` with the actual IP address of the server. For local testing, you can use `127.0.0.1`.

---

## 🧠 How It Works

### Server Side:

1. Creates a socket.
2. Binds to port `8086`.
3. Listens for incoming client connections.
4. Accepts a client and establishes a communication channel.
5. Continuously receives messages from the client and sends responses.

### Client Side:

1. Takes server IP as command-line argument.
2. Creates a socket and attempts to connect to the server at port `8086`.
3. On success, continuously sends user input to server and displays server messages.

---

## 📁 File Structure

```
.
├── tcpClient.c       # Client code
├── tcpServer.c       # Server code
└── README.md         # Documentation
```

---

## 🧪 Sample Output

**Server Terminal**

```
SOCKET SET UP SUCCESSFUL
BIND SUCCESSFUL
LISTEN SUCCESSFUL
CONNECTED SOCKET
Connection accepted from: 127.0.0.1
CONNECTION ESTABLISHED
CLIENT: Hello Server
Your message:
```

**Client Terminal**

```
Your message:
Hello Server
SERVER: Hello Client
```

---

## ❗ Notes

* Ensure ports below `1024` are run with elevated permissions or use a port like `8086` as done here.
* This implementation handles a **single client**. To handle multiple clients, threading or `select()` mechanism is required.

---

## 📜 License

This project is licensed under the MIT License. See `LICENSE` for more details.

---
