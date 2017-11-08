from socket import *  
from struct import *

s = socket(AF_INET, SOCK_STREAM)  
s.connect(("localhost", 2998))

wanted = s.recv(1024)  
challange = str(unpack("<I", wanted)[0])  
print("Received: " + str(challange))  
s.send(challange)

print(s.recv(1024))  
s.close()  
