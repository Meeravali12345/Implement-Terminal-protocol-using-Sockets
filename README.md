Distributed Arithmetic System Using Socket Programming
A multi-server architecture where clients connect via a relay agent to perform arithmetic operations.

📌 Overview
This project demonstrates a client-server model using socket programming in C. It consists of:

1 Agent Server (relay) that directs clients to the appropriate arithmetic server.

5 Arithmetic Servers (for +, -, *, /, % operations).

1 Client Program that sends operands and receives results.

The system follows a terminal protocol where the client first contacts the agent, which then provides the IP and port of the required arithmetic server.

⚙️ Features
✅ Agent Server

Maintains a hardcoded list of arithmetic servers (IP + Port).

Routes clients based on the requested operator (+, -, *, /, %).

✅ Arithmetic Servers

Each server runs on a different port (6000 to 6004).

Performs one specific arithmetic operation.

Runs indefinitely, handling multiple client requests.

✅ Client Program

Takes user input (two numbers and an operator).

Connects to the agent first, then the correct arithmetic server.

Displays the computed result.

✅ Error Handling

Checks for socket creation, binding, listening, and connection failures.

Gracefully closes sockets on errors.

🚀 How to Run
1. Start the Agent Server
bash
gcc agent_server.c -o agent_server
./agent_server
2. Start Arithmetic Servers
Open 5 different terminal tabs and run:

bash
# Addition (+) Server (Port 6000)
gcc server1.c -o server1 && ./server1

# Subtraction (-) Server (Port 6001)
gcc server2.c -o server2 && ./server2

# Division (/) Server (Port 6002)
gcc server3.c -o server3 && ./server3

# Multiplication (*) Server (Port 6003)
gcc server4.c -o server4 && ./server4

# Modulo (%) Server (Port 6004)
gcc server5.c -o server5 && ./server5
3. Run the Client
bash
gcc client.c -o client
./client
Sample Input:

text
Enter numbers: 10 20  
Enter operator: +  
Expected Output:

text
RESULT: 30  
📂 Project Structure
File	Description
agent_server.c	Relay server that routes clients to arithmetic servers.
server1.c	Addition (+) server (Port 6000).
server2.c	Subtraction (-) server (Port 6001).
server3.c	Division (/) server (Port 6002).
server4.c	Multiplication (*) server (Port 6003).
server5.c	Modulo (%) server (Port 6004).
client.c	Client program that interacts with agent and arithmetic servers.
🔧 Technologies Used
C Programming (Socket API, sys/socket.h, arpa/inet.h)

TCP/IP Networking (Client-Server Model)

Linux Environment (Tested on Ubuntu)

📜 Future Improvements
Dynamic Server Discovery (instead of hardcoding IPs).

Multi-threading to handle multiple clients simultaneously.

Logging System to track requests and errors.

📌 Note
All servers must be running before the client connects.

Ensure no firewall restrictions block the ports (5000, 6000-6004).

