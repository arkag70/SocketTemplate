# ethcomlib
This project is developed on linux with c++.

# About
SocketTemplate is a software library that facilitates ethernet (TCP) based peer to peer unidirectional communication between two hosts. 

A sender process can make use of APIs to connect and send data to a receiver application.

to send data to receiver - send_data()

A receiver process can make use of APIs to read data sent by the sender

to receiver data from sender - read_data()

# Running the application
clone project
> git clone https://github.com/arkag70/SocketTemplate.git

Building project
> . ./run.sh

Run the receiver application in a terminal
> ./build/examples/receiver

Run the sender application in another terminal
> ./build/examples/sender
