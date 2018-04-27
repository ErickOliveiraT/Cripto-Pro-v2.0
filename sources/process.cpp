/*
	Name: Cripto Pro v2.0
	Author: Erick Oliveira
	Date: 26/04/18
	Description: Cryptography Project
*/

#include "cripto.h"

void encript()
{
	unsigned int key, tam_ent;
	string ent;
	
	//Reading input password and calculing key
	key = password();
	
	//Reading input string
	clear;
	cout << "Enter your Text:\n\n";
	getline(cin, ent);
	tam_ent = ent.length();
	
	//Reversing input string
	reverse(ent.begin(), ent.end());
	
	//Encoding input with base64 algorithm
	string encoded = base64_encode(reinterpret_cast<const unsigned char*>(ent.c_str()), tam_ent);
	
	//Encoding encoded string with Cripto Pro algorithm
	criptoPro_enc(encoded, key);
	
	//Deletig temp file
	del_data_cripto;
	
	//Back to menu
	pause;
	clear;
	menu();	
}

void decript()
{
	unsigned int key, tam_ent, i;
	string ent;
	
	//Reading input password and calculing key
	key = password();
	
	//Reading input string
	clear;
	cout << "Enter the Encripted Text:\n\n";
	getline(cin, ent);
	
	//Decoding input with Cripto Pro Algorithm
	criptoPro_dec(ent, key);
	
	//Reading base64 encoded string
	char *str, aux;
	str = (char *) malloc(sizeof(char) * MAX_ENT * 2);
	FILE * read;
	read = fopen("cripto_data.dat", "r");
	fscanf(read, " %[^\n]s", str);
	fclose(read);
	string base64;
	for (i = 0; i < strlen(str); i++)
	{
		aux = str[i];
		base64 += aux;		
	}
	free(str);
	
	//Decoding base64 string
	string decoded = base64_decode(base64);
	
	//Reversing decoded base64 string
	reverse(decoded.begin(), decoded.end());
	
	//Printing result
	printf("Decripted Text:\n\n");
	cout << decoded;
	printf("\n\n\n\n");
	
	//Deletig temp files
	del_cripto_data;
	del_data_cripto;
	
	//Back to menu
	pause;
	clear;
	menu();	
}

void erro() //Error with archive manipulation
{
	printf("\n\nThere was a serious crash and the program will be terminated!\n\n");
	pause;
	exit(0);
}
