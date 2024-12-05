#include<stdio.h>
#include"md5.h"
#include<math.h>
#include<string.h>

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

void toostr(unsigned char data,char *hash,char i){
	unsigned char asciihex[16] = "0123456789ABCDEF";
	unsigned char flag = 1;
	unsigned char prom = 0;

	for (char j = 0; j < 4; j++){
		if (data & flag)
			prom+=pow(2,j);
		flag= flag<<1;
	}
	hash[i*2] = asciihex[(data-prom)/16];
	hash[i*2+1] = asciihex[prom];
}

void create_hash(char*data,char*key){
	size_t len = strlen(key);
    uint8_t result[16];
    md5((uint8_t*)key, len, result);

    for (int i = 0; i < 16; i++){
        toostr(result[i],data,i);
    }
}

char toohex(char i){
	char ascii[] = "0123456789ABCDEF"; 
	for (char j = 0; j != 16; j++){
		if (i == ascii[j]) return j;
	}
}

void copy(char *hashb, char *hash){
	for(char i = 0; i != 33; i++){
		hashb[i] = hash[i];
	}
}

int main(int argc, char *argv[]){
	char work[5];
	char flag = 0; 
	char start[255];
	char end[255];
	char *key = argv[2];
	char hash[33];
	char hashb[33];
	unsigned char obj;

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
			while(fgets(&obj,2,startf)){
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				fwrite(&obj,1,1,endf);
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
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
			while(fread(&obj,1,1,startf)){
				obj ^= (toohex(hash[flag])*16+toohex(hash[flag+1]));
				fprintf(endf,"%c",obj);
				flag+=2;
				if (flag == 32){
					copy(hashb,hash);
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
