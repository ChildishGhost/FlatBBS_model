#!/usr/bin/env python3

# zmq ping pong test

import zmq

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

for request in range(10):
    req = "hey {}".format(request).encode()
    print("Sending request {}".format(req))
    socket.send(req)

    message = socket.recv()
    print("Received reply {} -> {} ".format(request, message.decode()))
