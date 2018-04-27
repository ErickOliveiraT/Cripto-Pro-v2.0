/*
	Name: Cripto Pro v2.0
	Author: Erick Oliveira
	Date: 26/04/18
	Description: Cryptography Project
*/

#include "cripto.h"

int main()
{
	SetConsoleTitle("Cripto Pro 2.0");
	SetColorGreen;
	menu();
}

void menu()
{
	int op;
	
	printf("\t Cripto Pro 2.0 by Cripto S.A\n\n");
	printf(" 1 - Encript\n");
	printf(" 2 - Decript\n");
	printf(" 3 - Exit\n\n");
	printf(" Option: ");
	scanf("%d", &op);
	
	switch (op)
	{
		case 1:
			encript();
			break;
		case 2:
			decript();
			break;
		case 3:
			exit(0);
		default:
			clear;
			menu();
	}	
}
