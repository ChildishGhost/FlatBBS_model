#!/usr/bin/env python3

# zmq ping pong test

import os
import time
import zmq

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5566")


i = 1
while True:
    req = "# {}:{}\x00".format(os.getpid(), i)
    req *= 100
    #print(">> {}".format(req))
    socket.send(req.encode())
    message = socket.recv()
    #print("<< {} ".format(message.decode()))
    time.sleep(0.0001)
    i += 1
