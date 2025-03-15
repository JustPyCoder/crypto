#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
#include<string.h>
#include"md5.h"

void name_file(char *file, char *end_file){
	for(int i = 0; i != strlen(file); i++){
		if (file[i] != '.'){end_file[i] = file[i];}
		else {break;}
	}
}

void format_file(char *file, char *end_file){
	for(int i = 0; i != 4; i++){
		end_file[i] = file[strlen(file)-4+i];
	}
}
void create_hash(char*data,char*key){
	size_t len = strlen(key);
    uint8_t result[16];
    md5((uint8_t*)key, len, result);
    strcpy(data,result);
}

void xor_hash(char *hash, char *cripto_data_hash){
	for(char i = 0; i < 16; i++){
		hash[i] = hash[i] ^ cripto_data_hash[i];
	}
}