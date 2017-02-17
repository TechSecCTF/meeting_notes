# TechSec Informational Meeting

## Logistics

Action items (in decreasing order of importance):

* Fill out our [interest survey](https://goo.gl/forms/Z996dPHf5jNzRyLx2). This is how you will get on our mailing list, techsec@mit.edu.
* Join [our slack](https://techsec-mit.slack.com/signup). We mainly use this for coordination during CTFs.
* Make an account and join our team on [ctftime](https://ctftime.org/team/24526). More about this website below.
* At some point, join our [team GitHub organization](https://github.com/TechSecCTF) (after giving us your username through the survey). We'll be using this to take meeting notes, share resources, and post writeups.

## Crackmes

If you've done all that, have a go at [these three crackmes](https://github.com/TechSecCTF/meeting_notes/tree/master/2-15-17_introduction/crackmes) that we prepared for this meeting. For each one, you're looking for a "flag"—a specific string that signals that you've solved the challenge. All three flags are of the form `TechSec{.*}` where any series of ASCII characters can appear in between the braces. We'll go over the solutions to the three exercises at the end of this meeting.

Having trouble getting started with these? Here are some tips:

* All three crackmes are [ELF files](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) meaning they'll need to be executed on some flavor of Linux.
* You can move a file to athena to play with it by running:

```
scp crackme_1 [username]@athena.dialup.mit.edu:~
```

* You also will need to set the execute bit in order to run it. You can do this by running:

```
chmod +x crackme_1
```

* You can disassemble a file with the command `objdump -d crackme_1`. Also check out the other options for this command by running `man objdump`.
* You can try to run it in a debugger using [gdb](http://www.unknownroad.com/rtfm/gdbtut/).
* Finally, you can try running it in [this vm image](https://www.dropbox.com/s/4pdiubsd8t5jyec/Kali-Linux-2016.2-vm-amd64.7z?dl=0) of Kali Linux, which has a ton of useful tools installed.

## Introductions

* Ray Wang, Junior - raywang@mit.edu
* Rahul Sridhar, Junior - rsridhar@mit.edu
* Devin Neal, Senior - devneal@mit.edu
* Max Justicz, Senior - maxj@mit.edu

## Goals

* Establish a security community at MIT
* Share knowledge and learn new skills
* Compete in CTFs (and eventually [qualify to DEF CON](https://legitbs.net/))


## CTFs

### What is a CTF?

CTFs, or *Capture the Flag* games are team competitions that test your knowledge of security. They generally come in two flavors: Jeopardy and Attack / Defense.

In Jeopardy style, the organizers will release a bunch of different challenges distributed among a number of categories. For each challenge, the goal is to find a *flag*, a specific string that signals that you've solved the challenge. If you submit the flag, you get points. The team with the most points at the end wins.

Categories include:

* Pwn: given a binary and a service running that binary, need to exploit it somehow to access information on the server
* Rev: given just a binary, reverse engineer it to understand how it works
* Crypto: exploit a vulnerability in a flawed cryptographic service
* Web: exploit a vulnerability in a website
* Forensics: read a packet dump to piece together what happened
* Steganography: recover secret information (the flag) hidden in an image or other file
* Recon: stalk one of the organizers of the CTF to find a flag


Here's an example of what a Jeopardy style CTF might look like:

![alt-text](https://www.dropbox.com/s/amzd4zaxa7gk87g/Screenshot%202017-02-12%2021.55.14.png?dl=1)

In Attack / Defense, each team is given a a set of identical services that they are required to maintain. Each of these services contains one or more vulnerabilities that teams will need to patch (defense). Teams can also exploit each others services to steal flags and gain points (attack). Teams are allowed to monitor the network traffic to their services, so if a team gets exploited, they are often able to figure out what the specific exploit was, and then apply it to all the other teams. This technique is known as *reflection*.

![alt-text](https://www.dropbox.com/s/jfje2ztja708djs/IMG_20160312_175714728.jpg?dl=1)

### ctftime.org

There are hundreds of CTFs that happen every year. Nearly all of them are documented on [ctftime](http://ctftime.org), a website that keeps track of CTF tournaments, CTF teams and informal rankings. When a CTF finishes, the final team ranking will be sent to ctftime, where they will cross-reference registered teams with team names on ctftime, so you can track your team's progress over multiple CTFs.

TechSec is a registered team on ctftime, and you all are free to join it. Just create an account and request to join TechSec. It's never used for anything official, but it has become the centralized system for keeping track of CTFs.

### Tentative Schedule

* Boston Key Party - February 24th
* iCTF - March 3th
* MIT CTF - March 18th***
* Nuit du Hack CTF Quals 2017 - March 31st
* ASIS CTF Quals 2017 - April 7th
* PlaidCTF - April 21st
* DEF CON CTF Quals - April 29th

*** [This event](http://ctf.mit.edu/) is being organized by Max and Steven and is happening at MIT. It's teams of size 4. Register [here](https://docs.google.com/forms/d/e/1FAIpQLScxjVlYGIa1QzgNEXhK2sG8LxEcp-A7g_rmfUSF1zRINN-Teg/viewform?c=0&w=1).

### DEF CON

DEF CON is possibly the most well-known security convention; it takes place every year in Las Vegas, Nevada during the summer. There are a number of events and competitions that happen during the convention, but by far the most notable is the [DEF CON CTF](https://legitbs.net/), an Attack / Defense style competition that pits the most skilled CTF teams against each other.

Teams have to qualify for the event in order to participate. There are number of (mostly) Jeopardy style CTFs that DEF CON has designated as "qualifiers". (A number of them are on the list above!) One of the long term goals of TechSec is to eventually qualify to DEF CON.

### Resources

CTFs can be pretty intimidating for beginners, and many people have asked us what resources exist that they can use to practice and improve. We've compiled a list [here](https://github.com/TechSecCTF/resources/blob/master/Resources%20for%20CTFs.md). Feel free to add to it!

### Boston Key Party

The first event we plan to compete in is the [Boston Key Party](https://bostonkey.party/) which will run from February 24th to February 26th (Friday to Sunday). We plan to meet right at the start, and will probably hold a couple more "official" meetings later in the weekend. We'll all be active on the Slack approximately 24/7 so feel free to contribute wherever you are that weekend.

This is a DEF CON qualifier, and is also one of the better-run annual CTFs, so we'd like to put up a strong showing.

If you are new to CTFs and want to learn how get better, we strongly recommend that you show up right at the start of the event rather than later. All the easy challenges will get solved first, and you'll get a chance to actually watch how people approach these problems.

*One final note: while anyone is free to attend our weekly meetings, we are restricting the CTF teams for each event to MIT undergrads and graduate students.*

## Future Meetings

We plan to meet once a week at a time and place to be determined (although probably 7:00 on some weekday). Here's some ideas we have for various meetings:

* CTF Challenge Practice
* Workshops (How to use pwntools, How to use IDA, How to solve any RSA challenge)
* Guest Lectures on security research and news
* Post-CTF Walkthroughs

If you have an idea for a meeting, or want to teach a topic to the group feel free to let us know!

## Crackme Solutions

We'll now go over the solutions to the three crackmes that we released at the start. We'll post these solutions to the git repository immediately after the session on the 17th.

## Miscellaneous Items

* If you are interested in building a website or designing a logo, please contact one of us now, or through email.
* We're holding two iterations of this first informational meeting. Once on the 15th and once on the 17th. The two sessions will be identical—there's no need to come to both.
