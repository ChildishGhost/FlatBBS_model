#!/usr/bin/env python3

# zmq ping pong test

import os
import time
import zmq

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5566")


def api(req):
    req += "\x00"
    print(">> {}".format(req))
    socket.send(req.encode())
    message = socket.recv()
    print("<< {} ".format(message.decode()))
    time.sleep(0.0001)

for i in range(10):
    #api('{ "api" : "board_list" ,              "param" : {} }');
    #api('{ "api" : "board_length" ,            "param" : {} }');
    api('{ "api" : "utf8_test" ,            "param" : "{安安你好 (✌ﾟ∀ﾟ)☞}" }');
    #api('{ "api" : "board_post_list" ,         "param" : {} }');
    #api('{ "api" : "board_post_length" ,       "param" : {} }');
    #api('{ "api" : "board_inner_post_list" ,   "param" : {} }');
    #api('{ "api" : "board_inner_post_length" , "param" : {} }');
    #api('{ "api" : "user_fav_list" ,           "param" : {} }');
    #api('{ "api" : "user_fav_list_length" ,    "param" : {} }');
    #api('{ "api" : "board_post_path" ,         "param" : {} }');
    #api('{ "api" : "class_items_list" ,        "param" : {} }');
