# Elucent's Magical Unicode Library

Not actually that magical...just a fairly lightweight unicode utility. Still kinda fun though!

This is neither the fastest nor most complete thing out there, but it covers a few core unicode features:
encoding, decoding, and character types. These are implemented at the bottom of utf8.c. The library is
intended to be linked statically, does not depend on libc, and produces a binary less than 32 kB in size (at least on my current laptop).

Most of the code / binary size in this library comes from the code-point range tables in utf8.c. 
These arrays can be automatically generated from a Unicode Character Database distribution using
the included `genranges.py` script.

By default, the library also generates a character type lookup table at runtime, occupying 2 MiB of memory.
This can be turned off in the Makefile, in which case the program will perform a binary search over
the included code-point ranges.
