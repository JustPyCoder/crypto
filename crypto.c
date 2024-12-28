#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <stdint.h>
#include<math.h>
#include<string.h>
#include"md5.h"
#include"functions.h"

int main(int argc, char *argv[]){
	char work[5];
	char flag = 0; 
	char start[255];
	char end[255];
	char *key = argv[2];
	char hash[33];
	char hashb[33];
	unsigned char obj;
	unsigned char cripto_data[32]; 

	name_file(argv[1],start);
	strcpy(end,start);
	format_file(argv[1],work);
	create_hash(hash,key);
	
	if (strcmp(work,".txt")==0){
		strcat(start,".txt");
		strcat(end,".bin");
		FILE *startf = fopen(start,"r");
		FILE *endf = fopen(end,"wb");
		if (startf != NULL){
			srand(time(NULL));
			for(unsigned char i = 0; i != 16; i++){
				obj = rand()%256; 
				cripto_data[flag] = obj;
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				fwrite(&obj,1,1,endf);
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
					xor_hash(hashb,cripto_data);
					create_hash(hash,hashb);
					flag = 0;
				}
			}
			while(fgets(&obj,2,startf)){
				cripto_data[flag] = obj;
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				fwrite(&obj,1,1,endf);
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
					xor_hash(hashb,cripto_data);
					create_hash(hash,hashb);
					flag = 0;
				}
			}
		}
		fclose(startf);
		fclose(endf);
	} else if (strcmp(work,".bin")==0) {
		strcat(start,".bin");
		strcat(end,".txt");
		FILE *startf = fopen(start,"rb");
		FILE *endf = fopen(end,"w");
		if (startf != NULL){
			for(unsigned char i = 0; i != 16; i++){
				fread(&obj,1,1,startf);
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				cripto_data[flag] = obj;
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
					xor_hash(hashb,cripto_data);
					create_hash(hash,hashb);
					flag = 0;
				}
			}
			while(fread(&obj,1,1,startf)){
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				cripto_data[flag] = obj;
				fprintf(endf,"%c",obj);
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
					xor_hash(hashb,cripto_data);
					create_hash(hash,hashb);
					flag = 0;
				}
			}
		} 
		fclose(startf);
		fclose(endf);
	} else {printf("ERROR"); return 1;}
	return 0;
}