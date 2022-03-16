# SocketTemplate
This project is developed on linux with c++.

# About
SocketTemplate is a software library that facilitates ethernet (TCP) based peer to peer unidirectional communication between two hosts. 
A sender process can make use of APIs to connect and send data to a receiver application.
to connect to receiver - connect_to_server()
to send data to receiver - send_data()
A receiver process can make use of APIs to read data sent by the sender
to receiver data from sender - read_data()

# Running the application
clone the repo
> git clone https://github.com/arkag70/SocketTemplate.git
Building the repo
> . ./run.sh
Runing the receiver application in a terminal
> ./build/examples/receiver
Runing the sender application in another terminal
> ./build/examples/sender

Currently, IP, PORT, frequency of data tranfer are hard coded.
