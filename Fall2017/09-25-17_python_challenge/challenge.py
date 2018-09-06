# uncompyle6 version 2.11.5
# Python bytecode 2.7 (62211)
# Decompiled from: Python 2.7.10 (default, Feb  7 2017, 00:08:15) 
# [GCC 4.2.1 Compatible Apple LLVM 8.0.0 (clang-800.0.34)]
# Embedded file name: /Users/fortenforge/Desktop/tmp/checker.py
# Compiled at: 2017-09-22 17:26:52
import binascii
import base64
import struct
import random
compare_to = '505b603b8f3ed1e82f8e2e29a3c4a35f886f'

def check_password(s):
    if len(s) < 4:
        return False
    if struct.unpack('<I', s[0:4])[0] != 1734437990:
        return False
    if ord(s[4]) + ord(s[-1]) != 248:
        return False
    if ord(s[4]) * ord(s[-1]) != 15375:
        return False
    if len(s) % 4 != 2:
        return False
    try:
        s = base64.b64decode(s[5:-1])
    except TypeError:
        return False

    random.seed(1234)
    q = ''.join([ chr(ord(c) ^ random.randint(0, 255)) for c in s ])
    return binascii.hexlify(q) == compare_to


def main():
    s = raw_input('Enter the password: ')
    if check_password(s):
        print 'Nice work!'
    else:
        print 'Nope.'


if __name__ == '__main__':
    main()
# okay decompiling challenge.pyc
