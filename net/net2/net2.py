from socket import *  
from struct import *

s = socket(AF_INET, SOCK_STREAM)  
s.connect(("localhost", 2997))

sum = 0  
for i in range(4):  
        n = s.recv(1024)
        num = int(unpack("<I", n)[0])
        print("Received: " + str(num))
        sum += num
print("Sum: " + str(sum))  
sum = pack("<I", sum)  
s.send(str(sum))

print(s.recv(1024))  
s.close()  
