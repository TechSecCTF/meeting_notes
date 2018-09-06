# RSA Buffet (150 pts)

* We were given 5 ciphertexts, 10 RSA public keys, and 2 python files.
* The first python file, `encrypt.py` detailed how to encrypt and decrypt the ciphertexts given an RSA public / private key. (Basically using [RSA OAEP]( http://www.inf.pucrs.br/~calazans/graduate/TPVLSI_I/RSA-oaep_spec.pdf))
* The second python file, `generate-plaintexts.py`, details how to generate the 5 plaintexts based on 5 original messages:
  * Using [Shamir's Secret Sharing](https://en.wikipedia.org/wiki/Shamir's_Secret_Sharing) the ith message was secret-shared among 5 people with a recovery threshold of i.
  * Each of the shares from the different messages were then concatenated together to make the plaintext.
  * Finally, the plaintext was encrypted using `encrypt.py`.
* The challenge told us the flag was in the 3rd message, so we needed to break at least 3 of the 5 ciphertexts to recover the flag.
* To do this, we needed to recover the private key from the public key, by exploiting various vulnerabilities in RSA. We ended up finding 4:
  * The modulus of `key-2.pem` was the product of a very large prime and a very small prime, so we were able to factor it using (https://factordb.com).
  * The moduli of `key-0.pem` and `key-6.pem` shared a common factor, so we were able to recover this prime using the Euclidean algorithm.
  * The two primes corresponding to `key-1.pem` were very close to each other, and could be recovered using [Fermat's factorization method](https://en.wikipedia.org/wiki/Fermat%27s_factorization_method).
  * The private exponent (d) corresponding to `key-3.pem` was small, and thus susceptible to recovery via [Wiener's Attack](https://en.wikipedia.org/wiki/Wiener%27s_attack).
* Using three of the above attacks, we were able to obtain 3 plaintexts and recover the 3rd message which said:

```
Three's the magic number!  FLAG{ndQzjRpnSP60NgWET6jX}
```

The flag was `FLAG{ndQzjRpnSP60NgWET6jX}`.
