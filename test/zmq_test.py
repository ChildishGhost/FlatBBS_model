#!/usr/bin/env python3

# zmq ping pong test

import os
import time
import zmq
import random

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5566")


def api(req):
    req += "\x00"
    print(">> {}".format(req))
    socket.send(req.encode())
    message = socket.recv()
    print("<< {} ({})".format(message.decode(), len(message)))
    time.sleep(0.0001)

N = 10000
for i in range(N):
    #api(""" {{ "api" : "board_new",
    #            "name" : "test{}",
    #            "category" : "測試",
    #            "title" : "測試用",
    #            "masters" : [ "aaa", "bbb", "ccc" ],
    #            "perm" : "public",
    #            "attr" : {}
    #        }}""".format(i, i+1))
    #api('{{ "api" : "board_get" ,              "bid" : {} }}'.format(i))
    #api('{ "api" : "board_length" }')
    api(""" {{ "api" : "user_new",
                "username" : "test{}",
                "password" : "55665566-{}",
                "usernick" : "測試用",
                "email" : "null@gmail.com",
                "month" : 5,
                "day" : 6,
                "sex" : "female"
            }}""".format(i, i+1))
    api('{{ "api" : "user_get" ,              "uid" : {} }}'.format(i+1))
    api('{ "api" : "user_length" }')

input()


for i in range(N):
    api('{{ "api" : "user_get" ,              "uid" : {} }}'.format(random.randint(0, N)+1))
