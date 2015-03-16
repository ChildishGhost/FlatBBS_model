# some docs about zmq

## ZMQ version

We're using ZMQ [4.0 API](http://api.zeromq.org/4-0:_start)


## common patterns

### server and socket

- context -> socket -> bind connections
- send/recv messages via the socket
- we are currently using the [REQ/REP pattern](http://rfc.zeromq.org/spec:28)

```
    void *zmq_context = zmq_ctx_new ();
    void *zmq_server = zmq_socket (zmq_context, ZMQ_REP);
    assert(zmq_bind (zmq_server, "tcp://*:5566") == 0);

    zmq_close(zmq_server);
    zmq_ctx_destroy(zmq_context);
```

### message object operations

#### message type

- use `zmq_msg_t` for messages from/to other places for arbitrary length stuffs

- they're usually passed by the pointer to the object with `&` operator in C

```
    zmq_msg_t msg;
```

#### initialization

- initialize and destroy messages with `zmq_msg_init` and `zmq_msg_close`

- initialize a message object with size or data

  + a destructor function will be invoked to release the original data buffer

```
    zmq_msg_init(&msg);
    zmq_msg_close (&msg);

    size_t size = 1024;
    char buf[1024];

    zmq_msg_init_size(&msg, size);

    zmq_msg_init_data (&msg, buf, size, __dtor, hint);

    void __dtor(void *data, void *hint) {
        free(data);
    }

```

#### send and receive messages

```
    zmq_msg_send(&msg, zmq_server, ZMQ_DONTWAIT);
    zmq_msg_recv(&msg, zmq_server, ZMQ_DONTWAIT);
```

####  getting data from a message object

- get the size of the object by `zmq_msg_size`
- use `memcpy` to copy from the pointer returned by `zmq_msg_data`
- beware of `malloc/free` pairs

```
    size_t size = zmq_msg_size(&msg);
    if (size >  0) {
        char *buf = (char *)malloc(size);
        if (buf) {
            memcpy(buf, zmq_msg_data(&msg), size);
        }
        free(buf);
    }
```

#### copy/move messages with `zmq_msg_copy` or `zmq_msg_move`

```
    zmq_msg_t src;
    zmq_msg_t dst;
    zmq_msg_copy(&dst, &src);
    zmq_msg_move(&dst, &src);
```

