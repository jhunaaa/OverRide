# Help - level05

This challenge is straightforward. The executable expects two inputs:

* a **login**
* a **serial**

By analyzing the code, we can see that the program computes a serial number from the provided login. Our goal is therefore to recover the result of this algorithm and use it as the serial.

## Bypassing `ptrace`

To inspect the program with GDB, we first need to bypass the `ptrace` anti-debugging check.

Start GDB and disassemble the `auth` function (there is no need to disassemble `main`):

```gdb
disas auth
```

Set two breakpoints:

* one just before the `ptrace` call;
* one right after the serial-generation algorithm.

```gdb
b *0x080487b5    # Before the ptrace call
b *0x08048866    # After the algorithm
```

Run the program and enter a login. In this example, we'll use:

```text
pikachu
```

When execution stops at the first breakpoint, jump past the `ptrace` check:

```gdb
jump *0x080487ed
```

The program will continue until it reaches the second breakpoint. At this point, print the computed serial:

```gdb
p *(int*)($ebp-0x10)
```

Output:

```text
$1 = 6233768
```

## Getting the shell

Now simply run the program with:

* **Login:** `pikachu`
* **Serial:** `6233768`

The program validates the credentials and spawns a `/bin/sh`.
