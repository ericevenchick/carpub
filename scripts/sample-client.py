import zmq
import time

ZMQ_PORT = 5555

ctx = zmq.Context()
socket = ctx.socket(zmq.SUB)
socket.connect("tcp://localhost:%s" % ZMQ_PORT)
socket.setsockopt(zmq.SUBSCRIBE, '')

while True:
    print socket.recv()
