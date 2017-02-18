# Solution to `crackme_3`

This challenge is a modified version of a real CTF challenge from AlexCTF 2017 (which happened about a week ago). You can read the writeup for that challenge [here](https://github.com/TechSecCTF/writeups/tree/master/alexctf2017/catalyst). The username, password, and flag were all changed.

We encourage you to try to follow the steps of the writeup to solve this modified challenge (the steps should be virtually identical). To confirm your answers or intermediate steps, we've base64 encoded the username, password and flag below:

```
username: bWl0X3JldmVyc2Vy
password: bnBjOTRBTVJONEp3OEtzNzZITnVnejdhSFBxZkZxT3F2MUFmNWVzUw==
flag: VGVjaFNlY3tUaDFzX3QwMGtfYV9mcjM0a2luZ19sMG5nX3QxbWVfdDBfcDR0Y2ghfQ==
```

You can decode these using python, as shown below, or using [an online tool](https://gchq.github.io/CyberChef/?recipe=%5B%7B%22op%22%3A%22From%20Base64%22%2C%22args%22%3A%5B%22A-Za-z0-9%2B%2F%3D%22%2Ctrue%5D%7D%5D).

```
$ python
Python 2.7.10
>>> import base64
>>> base64.b64decode("dGhpcyBpcyBhIHRlc3Q=")
'this is a test'
>>>
$
```