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
	unsigned char asciihex[16] = "0123456789abcdef";
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
	char ascii[] = "0123456789abcdef"; 
	for (char j = 0; j != 16; j++){
		if (i == ascii[j]) return j;
	}
}

void copy(char *hashb, char *hash){
	for(char i = 0; i != 33; i++){
		hashb[i] = hash[i];
	}
}

void xor_hash(char *hash, char *cripto_data_hash){
	char ascii[] = "0123456789abcdef";
	for(char i = 0; i < 32; i++){
		hash[i] = ascii[toohex(hash[i]) ^ toohex(cripto_data_hash[i])];
	}
}