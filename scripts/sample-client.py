import zmq
import time

ZMQ_PORT = 5555

ctx = zmq.Context()
socket = ctx.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % ZMQ_PORT)

while True:
    socket.send("GO")
    print socket.recv()
    time.sleep(1)
