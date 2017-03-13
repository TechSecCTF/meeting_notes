# Prudential v2 (50 pts)

* We were given a website with a username and password.
* With a little digging, we found the php source of the website, which was essentially taking the SHA1 hash of the username and password and verifying that they were equal (and that the username and password were distinct).
* This meant we needed to find a SHA1 collision. Fortunately, a few days before the CTF, Google and CWI [published](http://shattered.io/) just such a collision in an attack they dubbed SHATTERED.
* They came up with two pdf files that were visually distinct, but had the same SHA1 hash.
* When we submitted these pdfs for the username and password, we got a response indicating that our POST arguments were too long.
* Luckily, the two pdfs only differed in a few blocks, so we could eliminate the blocks that were identical and preserve the property that both files collided. Once we submitted the shortened versions, we got the flag:

```
FLAG{AfterThursdayWeHadToReduceThePointValue}
```
