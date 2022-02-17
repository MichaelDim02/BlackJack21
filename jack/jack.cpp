#include <iostream>
#include <time.h>
#include <cstdio>

/* blackjack21 */

#include <string>
#include <cstring>
#include <fstream>

#include "lib/md5.h"
#include "lib/sha1.h"
#include "lib/sha256.h"
#include "lib/sha512.h"

using namespace std;

bool verbose;

void crack(string hash, string file, int alg);

void
interface(int f, char *exename)
{
	printf( "BlackJack21 - small password cracking program v2.1\n"
		"MCD, 2017\n\n");
	if (f == 1)
		printf( "Supported: md5, sha1, sha256, sha512\n\n"
			"Usage: %s [HASH-TYPE] [HASH] [DICTIONARY] [-v]\n",
			exename);
}

int
main(int argc, char* argv[])
{
	if(argc < 4) { interface(1, argv[0]);
		exit(0);
	} else if(argc == 4 || argc == 5) {
		string type = argv[1];
		string hash = argv[2];
		string dict = argv[3];
		std::ifstream file(dict);
		if(file.is_open()) {

			if (argc == 5)
				verbose = true;
			else
				verbose = false;

			interface(0, argv[0]);
			cout <<"Hashing algorithm: " << type << "\nCracking...\n\n";
			if (type == "MD5" || type == "md5") 		crack(hash, dict, 0);
			else if(type == "SHA1" || type == "sha1") 	crack(hash, dict, 1);
			else if(type == "SHA256" || type == "sha256") 	crack(hash, dict, 2);
			else if(type == "SHA512" || type == "sha512")	crack(hash, dict, 3);
		} else {
			interface(1, argv[0]);
			printf("File could not be found.\n");
			exit(1);
		}
	} else {
		interface(1, argv[0]);
	}

	exit(1);
}

int
iterate(string filename)
{
	int tries = 0;
	std::ifstream file(filename);
	string pass;
	while(file >> pass) {
		tries++;
	}

	return tries;
}

void
crack(string hash, string filename, int alg)
{
	int lines = iterate(filename);
	int tries = 0;
	std::ifstream file(filename);
	string pass;

	/* hide cursor */
	printf("\e[?25l");

	clock_t t;
	t = clock();

	while(file >> pass) {

		tries++;

		string hash_sum = "";
		if (alg == 0) hash_sum = md5(pass);
		else if (alg == 1) hash_sum = sha1(pass);
		else if (alg == 2) hash_sum = sha256(pass);
		else if (alg == 3) hash_sum = sha512(pass);

		if (hash_sum == hash) {
			cout << "\n\n[" << tries << "] - PASSWORD FOUND - " << pass << "\n\n";

			t = clock() - t;
			double time_taken = ((double)t) / CLOCKS_PER_SEC;
			printf("Elapsed time: %fs\n", time_taken);

			printf("\e[?25h");
			exit(0);
		} else {
			if (verbose == true)
				cout << "[" << tries << "] - Failed attempt - " << pass << endl;
			else
				printf("\rTried %d of %d lines", tries, lines );
		}
	}
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.2fs\n", time_taken);
	printf("\e[?25h");
}
