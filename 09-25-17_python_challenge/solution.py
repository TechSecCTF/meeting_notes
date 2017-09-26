import random
import struct
import binascii
import base64

first_4_chars = struct.pack('<I', 1734437990)
fifth_char = chr(123)
last_char = chr(125)


q = binascii.unhexlify('505b603b8f3ed1e82f8e2e29a3c4a35f886f')

random.seed(1234)
rand_ints = [random.randint(0,255) for _ in range(len(q))]

s = ''.join([chr(ord(c) ^ r) for c,r in zip(q, rand_ints)])
middle_chars = base64.b64encode(s)

flag = first_4_chars + fifth_char + middle_chars + last_char
print(flag)
