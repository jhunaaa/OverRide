# Help Level07

The binary is a simple program which yank the stdin to execute it's own commands store, read, quit. each command have it's own function.

read function: read will ask you an index and print an integer from an array of integers.

store function: store will ask you an index and a number, and store the number in the array of integers.

quit function: quit will exit the program.

# exploit

when you use the store function, you can write an integer to an index of the array. but the array is not protected, then you can write to an index outside of the array (index > 100). This will allow you to overwrite the return address of the function and execute arbitrary code.

we need to rewrite the return address to execute a ret2libc attack.

we can't give an address in hexadecimal format, so we need to convert the address to decimal format. the address of the system function is 0xf7e6aed0 in decimal format is 4159090384, and the address of the string "/bin/sh" is 0xf7f897ec in decimal format is 4160264172.

the index of the return address is 114 and 116 because 
