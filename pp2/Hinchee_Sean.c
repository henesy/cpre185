//FRIDAY
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

/*
Sean Hinchee
Section 58
12/11/2015
*/

/* 
Pre: The original plaintext phrase with spaces is passed in.
The function searches for a space.  When found,
the spece is removed by shifting all remaining elements 
in the array one space to the left.  
Post: The plaintext phrase has been modified so it no longer
contains spaces.
*/
void RmSpaces (char plaintext[]);

/* 
Pre: The plaintext phrase with the spaces removed is passed in.
Each character in the plaintext phrase is converted to lowercase.  
Post: The plaintext phrase has been modified so it no longer
has any uppercase letters in it.
*/

void MkLowerCase (char plaintext[]);

/* 
Pre: The plaintext phrase with the spaces removed, the key, the alphabet, 
the array to store the secret phrase, and the flag are passed in.  A true flag value
means the function should encrypt the plaintext phrase.  A false flag value 
means the function should decrypt the plaintext phrase.  
Post: Both the plaintext and the secret phrase arrays are filled.
*/

void EncryptDecrypt (int flag, char encryption[], char plaintext[], char secretkey[], char alphaList[] ); 

/* 
Pre: The plaintext phrase and the secret phrase are passed in.  
Post: The plaintext phrase and the secret phrase are printed.
*/
void PrintOutput (char plaintext[], char encryption[]);


int main (int argc, char* argv[]) {
	char alphabet[26] = 
	{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char key[26] = 
	{'n', 'o', 'p', 'q', 'r', 's', 't', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f'};
	
	char phrase[100] = "These are not the droids you are looking for";
	char secretphrase[100];
	
	RmSpaces(phrase);
	MkLowerCase(phrase);
	EncryptDecrypt(TRUE, secretphrase, phrase, key, alphabet);
	PrintOutput(phrase, secretphrase);
	
	return 0;
	
}

void RmSpaces (char plaintext[]){
	int i, j;
	for(i=0;i<100;i++){
		if(plaintext[i] == ' ') {
			for(j=i;j<99;j++){
				plaintext[j] = plaintext[j+1];
			}
			plaintext[99] = '\0';
		}
	}
}

void MkLowerCase (char plaintext[]){
	int i;
	for(i=0;i<100;i++) {
		plaintext[i] = tolower(plaintext[i]);
	}
}

void EncryptDecrypt (int flag, char encryption[], char plaintext[], char secretkey[], char alphaList[] ){
	int i, j;
	if(flag == TRUE){
		//encrypt
		for(i=0;i<100;i++){
			for(j=0;j<26;j++){
				if(plaintext[i] == alphaList[j]){
					encryption[i] = secretkey[j];
				}
			}
		}
	} else {
		//decrypt
		for(i=0;i<100;i++){
			for(j=0;j<26;j++){
				if(encryption[i] == secretkey[j]){
					plaintext[i] = alphaList[j];
				}
			}
		}
	}
}

void PrintOutput (char plaintext[], char encryption[]){
	printf("The plaintext is: %s\n", plaintext);
	printf("The secret phrase is: %s\n", encryption);
}

