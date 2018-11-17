# Cryptography

Cryptography is the study of secure communication. But like all areas of security, it is easy for developers to make mistakes implementing cryptography, which is why we try to find these vulnerabilities and exploit them in CTFs.  
  
For the following challenges, feel free to use whatever language you are most comfortable with.

## Base 64
Why do we use base 64? It is easy to represent binary data this way, and it only uses the characters 0-9, A-Z, and a-z, so you can read all the characters. So whenever you see alphanumeric characters, possibly with + and = signs, you are likely looking at a base 64 encoding.  
  
_Challenge 1_  
`aV9saWtlX2NyeXB0bw==`

_Challenge 2_  
`546563685365637B313C336B727970746F7D`
  
## Caesar Cipher

![Caesar Cipher](https://github.com/TechSecCTF/meeting_notes/blob/master/Fall2018/9-27-18_cryptography_fall2018/caesar-cipher.png)  

_Challenge 3_  
`fqoteqo{kmk_eqogdufk}`


## One Time Pad

![One Time Pad](https://github.com/TechSecCTF/meeting_notes/blob/master/Fall2018/9-27-18_cryptography_fall2018/one-time-pad.png)  

_Challenge 4_  
There are two 121-character English strings encrypted with the same “one-time pad” in `one-time-pad.py`. Decrypt the ciphertexts.

## RSA
![RSA](https://github.com/TechSecCTF/meeting_notes/blob/master/Fall2018/9-27-18_cryptography_fall2018/rsa.png)  

_Challenge 5_  
http://techsec.scripts.mit.edu/rsa.txt  
  
_Challenge 6_  
`n = 19496328704043440274928888604301794286813298517292582248654651820213827417766290799920782799935543004266912748113264304674483670412566049994599276530290804149292124076282435192572618912847345349710679754292257363482689384550203196236438078662381543186953290330976011794196887806414067021683120553212012689851945991251617192307627285781067411852598272956537270381008574241301981959318644501195345459004436936314181659876531823973737414011122846302525214090779888102416171866864534361902962019427365800501866980340013860007431879099430368949207928312328644193832519485899486341243557073846652069179437071358900972835057` 
  
`e1 = 1231`  
`c1 = 15081791209992142998045966172639146065270390554235449149481375489144402494913576581809974138054955879358796971410940656940813286389556134159861655681855708376888494437079709859226535320931353795212830543228887240987427831878525017608404222482722531905098372905369534409816576886473302011572463013131869859503348951729717939874750286584869183260692372156150025097797741476845513276803636096485564583903511737225186518202385405108109204016051723987938756220398471332006749348585517760418810456213195180943461045833153944756446192187333167933795131386430843833719200596863936298983230151456452707952397158684811294022575`  
  
`e2 = 59583931`  
`c2 = 17916693510420986853084408280440959958463618715415859884010967918235411858550455516549352227773027093656002572611550208389006238957393220656749119044241524990510181619062229420037307631680873573286239876922468019561460692804894621815904498752753655704060208240055007606069982130311462659735747504993698049314246435299188534737461639686799839812264074747964968299028404216704773274718073421584255888951073368306425360705201366801742788467396878698196140355614215650971488721699632363632515973873055318696655416578166296914658716451505194494286914695516022848281997568533517302183633976105657513093623167443584971536823`

## Info Session Challenges
_Challenge 7_  
`AljoZlj{Ulc3y_BzL_Jhlz@y_j1wOLY}`  
  
_Challenge 8 (single byte XOR cipher)_  
`5d6c6a615a6c6a724740676c56607a564856657c4a427056675c644b6c7b74`

## More Challenges
If you solve everything, start working on [Cryptopals](https://cryptopals.com/).