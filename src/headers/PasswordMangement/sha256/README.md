# SHA-256 C++ Implementation

Welcome to the **SHA-256 C++ Implementation** repository! This project provides a clear and concise implementation of the SHA-256 cryptographic hash function in C++. The SHA-256 algorithm is widely used for data integrity verification, password hashing, and digital signatures.

Modified from "[Hak8or](https://gist.github.com/hak8or/8794351)"

## Features

- **SHA-256 Algorithm**: This repository demonstrates a C++ implementation of the SHA-256 hashing algorithm, making it easy for developers to understand and use.

- **Clear Code**: The code is well-commented and structured, making it accessible for learning and integration into other projects.


// By: hak8or
// To compile: g++ -std=c++0x SHA_256_hak.cpp -o SHA_256_hak
// To run self test just run the following: SHA_256_hak
// To run and generate a hash run the following: SHA_256_hak stringtohashgoeshere

// Description: 
//	SHA-256 is one of the most common one way security hashes used in the wild,
//	SSL, SSH, PGP, and bitcoin all rely on this hash function. I had originally
//	hoped on doing SHA-3, but the standard is still not done, and the math behind
//	it seeems a bit over my head due to the lack of a "plain english" explanation
//	like NIST provided for SHA-2.
//
//	I find the coolest part of this is how the core of this can be simplified to
//	just rotating bits around, which isn't that difficult with logic gates and
//	whatnot on an FPGA. This being at its core just rotating bits mean it is
//	easy to impliment on a hardware level for even the most space conservative 
//	IC's or even in software on low power device.
//
// Implimentation:
//	This implimentation is for SHA-256, which generates a 256 bit hash for any
//	message up to a size of 2^64 bits (2^64 bits / 8 bit ASCII chars gives about
//	two quintillion characters).
//
//	Step 1
//	Pre Processing, we take the message and add "padding" to it consisting of 1 
// 	and 0's so the message is in 512 bit incriments, or blocks. This implimentation
//	assumes that the message will be no longer than 55 characters as it does not
//	handle messages which require more than one 512 bit block for longer length
//	messages. Lastly, the initial hash values are set which will be used for
//	the hash computation.
//
//	Padding specifically consist of having your message, adding 0's to it so you
//	will have the current length be 448 bits long, and then adding 64 bits which
//	say how long the original message was, giving you a total of 512 bits.
//
//	Initilizing just means initializing variables used in the hash computation so
//	the first round of hashing does not start with 0's, which would make this
//	hashing broken security wise.
//
//		Step 2
//	The actual hash computation. It is based on a message queue which sends 64
//	thirty two bit words to the next round, eight working variables with two
//	temporary variables, and 8 hash segments which will be combined at the end
//	to the 256 bit hash.
//

// Primary resource for getting an idea of what is going on: 
//	http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf
// For more information:
//	http://tools.ietf.org/html/rfc6234
// Testing:
//	http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
// Concrete Specification:
//	http://tools.ietf.org/html/rfc6234
//
// Useful links:
//	http://www.miniwebtool.com/hex-calculator
//	http://en.cppreference.com/w/cpp/language/ascii
//	https://github.com/adambard/learnxinyminutes-docs
//
// Should put this in a class someday instead of this mess of functions.
// If will use boost program options, put in a help option.
