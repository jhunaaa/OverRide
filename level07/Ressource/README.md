# Help Level07

The binary is a simple program which yank the stdin to execute it's own commands store, read, quit. each command have it's own function.

read function: read will ask you an index and print an integer from an array of integers.

store function: store will ask you an index and a number, and store the number in the array of integers.

quit function: quit will exit the program.

# exploit

when you use the store function, you can write an integer to an index of the array. but the array is not protected, then you can write to an index outside of the array (index > 100). This will allow you to overwrite the return address of the function and execute arbitrary code.

we need to rewrite the return address to execute a ret2libc attack.

we can't give an address in hexadecimal format, so we need to convert the address to decimal format. the address of the system function is 0xf7e6aed0 in decimal format is 4159090384, and the address of the string "/bin/sh" is 0xf7f897ec in decimal format is 4160264172.

the indexes we need to pass to overwite the return address are 114 and 116 because the padding is 112 bytes and the return address is 4 bytes.

however the store function will check if the index is a multiple of 3 or the first 8 bits of the number are 0xb7, if it's the case, it will print an error message and return.

then we need to find a way to bypass this check.
to bypass this check, we can use an int overflow to make it we must find the first number that is not a multiple of 3 but the overflow result must be 114

then right index to use to bypass this check is 1073741824 + 114 = 1073741938.
why is it working? because the index is passed through shl 2 (multiply by 4) to get the index of the array, so 1073741938 * 4 = 4294967752 which is equal to 114 after the overflow.

we can use the following command to exploit the program:
```
./level07
store
4159090384
1073741938
store
4160264172
116
quit
```

cat /home/users/level08/.pass
