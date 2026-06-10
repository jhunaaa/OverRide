## Help level00

The level00 binary ask a password, if we found it, we got a /bin/sh.
By reading the binary we saw he compare the input with 0x149c, which mean, it's the level password but in hexadecimal.

By using python with python3 -c 'print(0x149c)' we got the true password : 5276

## Usage
./level00
5276

