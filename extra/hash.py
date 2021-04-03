from __future__ import print_function
import hashlib

string = raw_input("String: ")
print("\nMD5:    ",hashlib.md5(string).hexdigest())
print("\nSHA1:   ",hashlib.sha1(string).hexdigest())
print("\nSHA256: ",hashlib.sha256(string).hexdigest())
print("\nSHA512: ",hashlib.sha512(string).hexdigest())
