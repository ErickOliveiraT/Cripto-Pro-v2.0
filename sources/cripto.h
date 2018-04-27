//cripto.h -- Reader File

//Libraries
#include <string>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
#include <conio.h>
#include "base64.h"

//Macros
#define pause system("pause")
#define clear system("cls")
#define SetColorGreen system("color 0a")
#define MAX_ENT 25000
#define MAX_HEX 50000
#define MAX_PASS 256
#define del_cripto_data system("del cripto_data.dat")
#define del_data_cripto system("del data_cripto.dat")

using namespace std;

//Functions
void menu();
void encript();
void decript();
void erro();
int password();
void criptoPro_enc(string ent, int key);
void criptoPro_dec(string ent, int key);
void criptoPro_dec2(char *ent, int n);
