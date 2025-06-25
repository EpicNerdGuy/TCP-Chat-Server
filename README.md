---

# TCP Multi-Client Chat Server in C

A simple multi-client chat server and client built using C and `pthread`, allowing multiple clients to connect and communicate with each other in real-time through a centralized server.

---

## Features

* ✅ TCP-based reliable chat communication
* ✅ Multi-client support using threads (`pthread`)
* ✅ Server broadcasts messages to all connected clients
* ✅ Clients can send and receive messages simultaneously
* ✅ Thread-safe handling of connected clients
* ✅ Clean terminal-based UI
* ✅ Graceful disconnection handling

---

## Technologies Used

* C (POSIX Sockets)
* `pthread` for multithreading
* Linux (tested on Kali/Ubuntu)
* `gcc` compiler

---

## File Structure

```bash
.
├── server.c       # Server source code
├── client.c    # Client source code
├── README.md   # You're reading it!
```

---

## How It Works

### Server (`server.c`)

* Creates a TCP socket and listens on a port (default: `8086`)
* Accepts multiple clients using `accept()`
* Spawns a new thread for each client
* Broadcasts each message received to **all other clients**

### Client (`client.c`)

* Connects to the server via IP and port
* Starts two threads:

  * One to send messages (`send_handler`)
  * One to receive messages (`recv_handler`)
* Messages are displayed asynchronously while typing

---

## How to Run

### 1. Compile

```bash
gcc server.c -o server -lpthread
gcc client.c -o client -lpthread
```

### 2. Run Server

```bash
./server
```

### 3. Run Client (in new terminals)

```bash
./client
```

Run multiple clients to simulate a real chatroom.

---

## 📸 Screenshot

```
Client 1 Terminal
-----------------
>> Hello from Client 2!

Client 2 Terminal
-----------------
>> Hello from Client 1!
```

---


## 📜 License

This project is licensed under the MIT License. See `LICENSE` for more details.

---
