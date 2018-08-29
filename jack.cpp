#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

// Hash Libraries //
#include "src/md5.h"
#include "src/sha1.h"
#include "src/sha256.h"
#include "src/sha512.h"
using namespace std;

// Global Variables //
bool verbose;

//Function prototypes //
void md5_crack(string hash, string file);
void sha1_crack(string hash, string file);
void sha256_crack(string hash, string file);
void sha512_crack(string hash, string file);

// CODE //

//INTERFACE//
void interface() {
	cout << "BlackJack21 Password Cracker v0.2" << endl;
	cout << "Written by Michael C. Dim. in C++ - Thessaloniki, Greece 2017" << endl;
	cout << "Python version: github.com/MichaelDim02/BlackJack" << endl;
	cout << "Hashes included: MD5, SHA1, SHA256, SHA512" << endl << endl;
	cout << "Usage: ./jack [HASH-TYPE] [HASH] [DICTIONARY] [-v]" << endl;
}
int main(int argc, char* argv[]) {
	if(argc < 4) {
		interface();
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
			if(type == "MD5" || type == "md5"){
				md5_crack(hash, dict);
			}else if(type == "SHA1" || type == "sha1"){
				sha1_crack(hash, dict);
			}else if(type == "SHA256" || type == "sha256"){
				sha256_crack(hash, dict);
			}else if(type == "SHA512" || type == "sha512"){
				sha512_crack(hash, dict);
			}
		} else {
			interface();
			cout << endl << "File could not be found." << endl;
		}
	} else {
		interface();
	}
}
void md5_crack(string hash, string filename) {
	int tries = 0;
	std::ifstream file(filename);
	string pass;
	while(file >> pass) {
		tries++;
		string hash_sum = md5(pass);
		if (hash_sum == hash) {
			cout << "[" << tries << "] - PASSWORD FOUND - " << pass << endl;
			exit(0);
		} else {
			if (verbose == true) {
				cout << "[" << tries << "] - FAILED ATTEMPT - " << pass << endl;
			}
		}
	}
}
void sha1_crack(string hash, string filename) {
        int tries = 0;
        std::ifstream file(filename);
        string pass;
        while(file >> pass) {
                tries++;
                string hash_sum = sha1(pass);
                if (hash_sum == hash) {
                        cout << "[" << tries << "] - PASSWORD FOUND - " << pass << endl;
                        exit(0);
                } else {
			if (verbose == true) {
				cout << "[" << tries << "] - FAILED ATTEMPT - " << pass << endl;
			}
                }
        }
}

void sha256_crack(string hash, string filename) {
        int tries = 0;
        std::ifstream file(filename);
        string pass;
        while(file >> pass) {
                tries++;
                string hash_sum = sha256(pass);
                if (hash_sum == hash) {
                        cout << "[" << tries << "] - PASSWORD FOUND - " << pass << endl;
                        exit(0);
                } else {
			if (verbose == true) {
				cout << "[" << tries << "] - FAILED ATTEMPT - " << pass << endl;
			}
		}
	}
}

void sha512_crack(string hash, string filename) {
        int tries = 0;
        std::ifstream file(filename);
        string pass;
        while(file >> pass) {
                tries++;
                string hash_sum = sha512(pass);
                if (hash_sum == hash) {
                        cout << "[" << tries << "] - PASSWORD FOUND - " << pass << endl;
                        exit(0);
                } else {
			if (verbose == true) {
				cout << "[" << tries << "] - FAILED ATTEMPT - " << pass << endl;
			}
		}
	}
}
