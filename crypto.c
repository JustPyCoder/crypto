#include"functions.h"

int main(int argc, char *argv[]){
	char work[5];
	char flag = 0; 
	char start[255];
	char end[255];
	char *key = argv[2];
	unsigned char hash[17];
	unsigned char hashd[17];
	unsigned char obj;
	unsigned char random_data[17]; 

	name_file(argv[1],start);
	strcpy(end,start);
	format_file(argv[1],work);
	create_hash(hash,key);
	
	if (strcmp(work,".txt")==0){
		strcat(start,".txt");
		strcat(end,".bin");
		FILE *startf = fopen(start,"r");
		if (startf != NULL){
			FILE *endf = fopen(end,"wb");
			srand(time(NULL));
			for(unsigned char i = 0; i != 16; i++){
				obj = rand()%256; 
				random_data[i] = obj;
				obj ^= hash[i];
				fwrite(&obj,1,1,endf);
			}
			strcpy(hashd,hash);
			create_hash(hash,hashd);
			xor_hash(hash,random_data);
			strcpy(hashd,hash);
			create_hash(hash,hashd);
			while (fgets(&obj, 2, startf)){
				obj^= hash[flag];
				fwrite(&obj,1,1,endf);
				flag++;
				if (flag == 16){
					xor_hash(hash,random_data);
					strcpy(hashd,hash);
					create_hash(hash,hashd);
					flag = 0;
				}
			}
			fclose(endf);
		} else {
			printf("\nFile not found error");
		}
		fclose(startf);
	} else if (strcmp(work,".bin")==0) {
		strcat(start,".bin");
		strcat(end,".txt");
		FILE *startf = fopen(start,"rb");
		if (startf != NULL){
			FILE *endf = fopen(end,"w");
			for(unsigned char i = 0; i != 16; i++){
				fread(&obj,1,1,startf);
				obj ^= hash[i];
				random_data[i] = obj;
			}
			strcpy(hashd,hash);
			create_hash(hash,hashd);
			xor_hash(hash,random_data);
			strcpy(hashd,hash);
			create_hash(hash,hashd);
			while (fread(&obj,1,1,startf)){
				obj ^= hash[flag];
				fprintf(endf,"%c",obj);
				flag++;
				if (flag == 16){
					xor_hash(hash,random_data);
					strcpy(hashd,hash);
					create_hash(hash,hashd);
					flag = 0;
				}
			}
			fclose(endf);
		} else {
			printf("\nFile not found error");
		}
		fclose(startf);
	} else {printf("Format error"); return 1;}
	return 0;
}
