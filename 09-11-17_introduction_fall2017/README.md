# TechSec Informational Meeting

## Logistics

Action items (in decreasing order of importance):

* Fill out our [interest survey](https://goo.gl/forms/nPMJaSGRof6emGAf2). This is how you will get on our mailing list, techsec@mit.edu.
* Join [our slack](https://techsec-mit.slack.com/signup). We mainly use this for coordination during CTFs.
* Make an account and join our team on [ctftime](https://ctftime.org/team/24526). More about this website below.
* At some point, join our [team GitHub organization](https://github.com/TechSecCTF) (after giving us your username through the survey). We'll be using this to take meeting notes, share resources, and post writeups.

## MiniCTF

If you've done all that, have a go at [a MiniCTF](https://techsec.scripts.mit.edu/midway.pdf) that we prepared for the Activities Midway. For each challenge, you're looking for a "flag"—a specific string that signals that you've solved the challenge. All eight flags are of the form `TechSec{.*}` where any series of ASCII characters can appear in between the braces. If you solve a challenge, show us the flag at the end of today's meeting and we'll give you a lockpicking set.

## Introductions

* Ray Wang, Senior - raywang@mit.edu
* Rahul Sridhar, Senior - rsridhar@mit.edu
* Devin Neal, Senior - devneal@mit.edu

## Goals

* Establish a security community at MIT
* Share knowledge and learn new skills
* Compete in CTFs (and [qualify to DEF CON](https://legitbs.net/))


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

![alt-text](https://www.dropbox.com/s/3wnt96wyf5utma7/jeopardy.png?dl=1)

In Attack / Defense, each team is given a a set of identical services that they are required to maintain. Each of these services contains one or more vulnerabilities that teams will need to patch (defense). Teams can also exploit each others services to steal flags and gain points (attack). Teams are allowed to monitor the network traffic to their services, so if a team gets exploited, they are often able to figure out what the specific exploit was, and then apply it to all the other teams. This technique is known as *reflection*.

![alt-text](https://www.dropbox.com/s/jfje2ztja708djs/IMG_20160312_175714728.jpg?dl=1)

### ctftime.org

There are hundreds of CTFs that happen every year. Nearly all of them are documented on [ctftime](http://ctftime.org), a website that keeps track of CTF tournaments, CTF teams and informal rankings. When a CTF finishes, the final team ranking will be sent to ctftime, where they will cross-reference registered teams with team names on ctftime, so you can track your team's progress over multiple CTFs.

TechSec is a registered team on ctftime, and you all are free to join it. Just create an account and request to join TechSec. It's never used for anything official, but it has become the centralized system for keeping track of CTFs.

### Tentative Schedule (for Fall)

* CSAW CTF 2017 (September 15 - 17)
* NSA Codebreakers 2017 (September 15 - December)
* Pwn2Win CTF (October 20 - October 22)
* HITCON 2017 (November 4 - November 5)

We also have a [Google Calendar](https://calendar.google.com/calendar/embed?src=60as1dh4pclfl3csbcs99sal4c%40group.calendar.google.com&ctz=America/New_York).

### DEF CON

DEF CON is possibly the most well-known security convention; it takes place every year in Las Vegas, Nevada during the summer. There are a number of events and competitions that happen during the convention, but by far the most notable is the [DEF CON CTF](https://legitbs.net/), an Attack / Defense style competition that pits the most skilled CTF teams against each other.

Teams have to qualify for the event in order to participate. There are number of (mostly) Jeopardy style CTFs that DEF CON has designated as "qualifiers". TechSec, in collaboration with RPISEC and MIT Lincoln Labs (Lab RATs) qualified to DEF CON last year! We hope to do so again.

### Collaborations

We frequently collaborate with two other CTF teams, Lab RATs, which consists of employees at MIT Lincoln Labs (a great place for security UROPs!) and students at [RPISEC](https://rpis.ec/), RPI's CTF team.

<<<<<<< HEAD
On September 23rd, RPI has invited us to attend a workshop they're giving on binary exploitation. Let us know if you're interested on the form.
=======
On Setempber 23rd, RPI has invited us to attend a workshop they're giving on binary exploitation. Let us know if you're interested on the form.
>>>>>>> 223280ec8af51100b85bd3d33c3abf3212e5a324

### Resources

CTFs can be pretty intimidating for beginners, and many people have asked us what resources exist that they can use to practice and improve. We've compiled a list [here](https://github.com/TechSecCTF/resources/blob/master/Resources%20for%20CTFs.md). Feel free to add to it!

## Future Meetings

We plan to meet once a week on Mondays at 6:30pm in 32-124. Here's some ideas we have for various meetings:

* CTF Challenge Practice
* Workshops (How to use pwntools, How to use IDA, How to solve any RSA challenge)
* Guest Lectures on security research and news
* Post-CTF Walkthroughs

If you have an idea for a meeting, or want to teach a topic to the group feel free to let us know!

We keep fairly detailed meeting notes on a [repository](https://github.com/TechSecCTF/meeting_notes) on GitHub.
