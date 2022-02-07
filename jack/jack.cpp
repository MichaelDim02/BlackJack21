#include <iostream>
#include <cstdio>

/*	BLACKJACK21
 *	jack.cpp
 */

#include <string>
#include <cstring>
#include <fstream>

/* Hash Libraries */
#include "lib/md5.h"
#include "lib/sha1.h"
#include "lib/sha256.h"
#include "lib/sha512.h"

using namespace std;

bool verbose;

void crack(string hash, string file, int alg);

void
interface(int f)
{
	printf( "BlackJack21 Minimal Password Cracking program v2.0\n"
		"Written by MCD (aka mk) - 2017\n\n");
	if (f == 1)
		printf( "Supported: MD5, SHA1, SHA256, SHA512\n\n"
			"Usage: ./jack [HASH-TYPE] [HASH] [DICTIONARY] [-v]\n");
}

int
main(int argc, char* argv[])
{
	if(argc < 4) { interface(1);
		exit(0);
	} else if(argc == 4 || argc == 5) {
		string type = argv[1];
		string hash = argv[2];
		string dict = argv[3];
		std::ifstream file(dict);
		if(file.is_open()) {
			if (argc == 5) {
				verbose = true;
			} else {
				verbose = false;
			}
			interface(0);
			printf("Hashing algorithm: %s\nCracking\n\n", type);
			if (type == "MD5" || type == "md5") 		crack(hash, dict, 0);
			else if(type == "SHA1" || type == "sha1") 	crack(hash, dict, 1);
			else if(type == "SHA256" || type == "sha256") 	crack(hash, dict, 2);
			else if(type == "SHA512" || type == "sha512")	crack(hash, dict, 3);
		} else {
			interface(1);
			printf("File could not be found.\n");
			exit(1);
		}
	} else {
		interface(1);
		exit(0);
	}
}

void
crack(string hash, string filename, int alg)
{
	int tries = 0;
	std::ifstream file(filename);
	string pass;
	while(file >> pass) {
		tries++;

		string hash_sum = "";
		if (alg == 0) hash_sum = md5(pass);
		else if (alg == 1) hash_sum = sha1(pass);
		else if (alg == 2) hash_sum = sha256(pass);
		else if (alg == 3) hash_sum = sha512(pass);

		if (hash_sum == hash) {
			printf("\n\n[%d] - PASSWORD FOUND - %s\n\n", tries, pass);
			exit(0);
		} else {
			if (verbose == true) {
				printf("[%d] - Failed Attempt - %s\n", tries, pass);
			}
		}
	}
}
