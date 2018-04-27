/*
	Name: Cripto Pro v1.5
	Author: Erick Oliveira
	Description: Criptography Project
*/

#include "cripto.h"

int password(void)
{	
	fflush(stdin);
	clear;
	
	char *pass, c;
	int i, aux = 0, tam_pass, key = 0;
	
	pass = (char *) malloc(sizeof(char) * MAX_PASS);
	if (!pass) erro();
	
	printf("Enter your Password:\n\n"); 
	
	do //Masking password
	{
		c = getch();
		
		if (isprint(c))
		{
			printf("*");
			pass[aux] = c;
			aux++;
		}
		else if (c == 8 && aux)
		{
			pass[aux] = '\0';
			aux--;
			printf("\b \b");
		}
	}while (c != 13);
	
	tam_pass = aux;
	
	if (tam_pass > MAX_PASS) //Limiting Password
	{
		printf("\nThe password can't be bigger than 256\n\n\n");
		pause;
		password();
	}
	
	for (i = 0; i < tam_pass; i++) //Processing Password
	{
		key += ("%d", pass[i]);
	}
	
	if (key%89 == 0 || key == 0 || key == 89) //Limiting key
	{
		printf("\nThis password can't be used\n\n");
		pause;
		password();
	}
	else //Calculing key
	{
		key = key%89;
	}
	free(pass);

	return key;
}


void criptoPro_enc(string ent, int key) //Encryption
{
	char *hex, *inv_hex, chr, *saida, aux2, *saida2;
	int i, j, tam_ent, cont = 0, aux;
	char poss[] = "aAbBc!Cd@De#Ef$F.,g%9Gh&8Hi*7Ij(6Jk)K5l-Lm_4Mn=N3oO+p2Pq'Q1r>Rs0<StT:uU;v[Vw]Wx{X}/|yYzZ aAbBc!Cd@De#Ef$F.,g%9Gh&8Hi*7Ij(6Jk)K5l-Lm_4Mn=N3oO+p2Pq'Q1r>Rs0<StT:uU;v[Vw]Wx{X}/|yYzZ ";

	tam_ent = ent.length();
	
	FILE *exp; //Converting to hexadecimal string
	exp = fopen("data_cripto.dat", "w");
	for (i = 0; i < tam_ent; i++)
	{
		fprintf(exp,"%x",ent[i]);
	}
	fclose(exp);
	
	hex = (char *) malloc(sizeof(char) * MAX_HEX); 
	
	FILE *input; //Hexadecimal string reading
	input = fopen("data_cripto.dat", "r");
	while (fscanf(input,"%c", &chr) != EOF)
	{
		hex[cont] = chr;
		cont++;
	}
	fclose(input);
	
	inv_hex = (char *) malloc(sizeof(char) * MAX_HEX);
	
	for (i = cont; i > -1; --i) //Reversing hexadecimal string
	{
		inv_hex[i] = hex[cont - i - 1];
	}
	free(hex);
	
	//inv_hex == new input
	tam_ent = cont;
	
	for (i = 0; i < tam_ent; i++) //Encoding -- First Level
	{
		for (j = 0; j < 90; j++) //Search inv_hex[i] in poss[]
		{
			if (inv_hex[i] == poss[j])
			{
				aux = j;
				break;
			}
		}
		inv_hex[i] = poss[aux+key];
	}
	
	saida = (char *) malloc(sizeof(char) * MAX_ENT);
	
	for (i = 0; i < tam_ent; i++) //Reversing string
	{
		saida[i] = inv_hex[tam_ent-i-1];
	}
	free(inv_hex);
	
	saida2 = (char *) malloc(sizeof(char) * MAX_ENT);
	
	//Encoding -- Second Level
	srand((unsigned)time(NULL));
	cont = 0;
	for (i = 0; i < tam_ent; i++)
	{
		aux = 32 + rand()%95;
		aux2 = ("%c", aux);
		saida2[cont] = saida[i];
		cont++;
		saida2[cont] = aux2;
		cont++;
	}
	free(saida);
	
	clear; //Printing results
	printf("Encoded Text:\n\n");
	for(i = 0; i < cont; i++) 
	{
		printf("%c", saida2[i]);
	}
	free(saida2);
	
	FILE *clean; //Cleaning .dat archive (just for security)
	clean = fopen("data_cripto.dat", "w");
	fprintf(clean," ");
	fclose(clean);
	
	printf("\n\n\n\n");
}


void criptoPro_dec(string ent, int key) //Decode
{
	clear;
	
	char *sai,*str, *sai2, *pass, c;
	char alf[] = "aAbBc!Cd@De#Ef$F.,g%9Gh&8Hi*7Ij(6Jk)K5l-Lm_4Mn=N3oO+p2Pq'Q1r>Rs0<StT:uU;v[Vw]Wx{X}/|yYzZ aAbBc!Cd@De#Ef$F.,g%9Gh&8Hi*7Ij(6Jk)K5l-Lm_4Mn=N3oO+p2Pq'Q1r>Rs0<StT:uU;v[Vw]Wx{X}/|yYzZ ";
	int i, j, tam_pass, tam_ent, tam_str, poss, aux = 0;	
	
	tam_ent = ent.length();
	
	sai = (char *) malloc(sizeof(char) * MAX_ENT);
	
	for (i = 0; i < tam_ent; i++) //Reversing
	{
		sai[i] = ent[tam_ent-i-1];
	}
		
	FILE *exp; //Archive manipulation operations
	exp = fopen("data_cripto.dat", "w");
	for (i = 1; i < tam_ent; i+=2) 
	{
		fprintf(exp,"%c",sai[i]);	
	}
	fclose(exp);
	free(sai);
	str = (char *) malloc(sizeof(char) * MAX_ENT);
	FILE *read;
	read = fopen("data_cripto.dat", "r");
	fscanf(read," %[^\n]s", str);
	tam_str = strlen(str);
	fclose(read);
	
	sai2 = (char *) malloc(sizeof(char) * MAX_ENT);
	
	for (i = 0; i < tam_str; i++) //Decoding
	{
		for (j = 91; j < 180; j++)
		{
			if (str[i] == alf[j])
			{
				poss = j;
				break;
			}
		}
		sai2[i] = alf[poss-key];
	}
	free(str);
	
	criptoPro_dec2(sai2,tam_str);
}

void criptoPro_dec2(char *ent, int n)
{
	char *inv, aux;
	int i, chr;
	
	inv = (char *) malloc(sizeof(char) * MAX_ENT);
	
	for (i = n; i > -1; --i)  //Reversing
	{
		inv[i] = ent[n-i-1];
	}
	
	FILE *breaker; //Exporting hexadecimal with line breaks to .dat
	breaker = fopen("data_cripto.dat", "w");
	for (i = 0; i < n; i+=2)
	{
		fprintf(breaker,"%c", inv[i]);
		fprintf(breaker,"%c", inv[i+1]);
		fprintf(breaker,"\n");
	}
	fclose(breaker);
	free(inv);
	
	ofstream decoded ("cripto_data.dat");
	if(!decoded.is_open()) erro();
	
	clear; //Reading from .dat and printing final output
	FILE *reading;
	reading = fopen("data_cripto.dat", "r");
	while(fscanf(reading,"%x",&chr) != EOF)
	{
		aux = ("%c", chr);
		decoded << aux;
	}
	decoded.close();
	fclose(reading);
	
	FILE *cleaner; //Cleaning .dat archive (just for security to)
	cleaner = fopen("data_cripto.dat", "w");
	fprintf(cleaner," ");
	fclose(cleaner);
}
