from socket import *  
from struct import *

s = socket(AF_INET, SOCK_STREAM)  
s.connect(("localhost", 2999))  
challange = s.recv(1024)  
start = challange.find("'") + 1  
end = challange.find("'", start)  
num = int(challange[start:end])  
print "Challange: " + str(num)  
li = pack("<I", num)  
s.send(li)  
print(s.recv(1024))  
s.close()  
