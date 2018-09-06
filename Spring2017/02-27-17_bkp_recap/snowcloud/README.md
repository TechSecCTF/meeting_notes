# snowcloud (200 pts)

* We were given an website where you could create text snippets.
* The the first user listed on the page was always `admin`, even when the website crashed and had to be restarted.
* We then guessed that we needed to launch an XSS attack against the admin and steal his cookie.
* The website stated that our text snippets were "printed out" before being sent back to us.
* We eventually figured out that when we posted out text snippets, they were first being converted to an image, and then OCR'd before getting stored on the website.
* After that we spent quite a long time trying to find a good set of symbols that would yield an appropriate XSS attack. We had the full Unicode character set to work with, but it still required a great deal of fiddling.
