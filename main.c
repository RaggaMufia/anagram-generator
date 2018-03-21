#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmp(const void* a, const void* b);
int* numletters(char* word, int length);

int main(int argc, char* argv[]){
	if(argc > 1){
		char wtm[128];
		strcpy(wtm, argv[1]);
		
		int length;
		for(length = 0; length < 128 && wtm[length] != 0; length++);
		
		FILE *in = fopen("words.txt", "r");

		char word[length+1];
		word[length] = 0;
		
		for(int i = 0; i < length; i++)
			word[i] = wtm[i];
		for(int i = 0; i < length; i++)
			word[i] = tolower(word[i]);	
		
		char wordcp[length+1];
		wordcp[length] = 0;
		for(int i = 0; i < length; i++)
			wordcp[i] = word[i];

		//printf("%s ", word);
		qsort(word, length, sizeof(char), cmp);
		//printf("%s\n", word);

		int *numeach;
		numeach = numletters(word, length);
		
		//printf("word:%s wordcp:%s\n", word, wordcp);

		if(in){
			char scanned[128];
			while(fscanf(in, "%s", scanned) != EOF){
				int sclength;
				for(sclength = 0; sclength < 128 && scanned[sclength] != 0; sclength++);
				char scan[sclength+1];
				char scancp[sclength+1];
				scan[sclength] = 0;
				scan[sclength] = 0;
				for(int i = 0 ; i < sclength; i++)
					scan[i] = scanned[i];
				if(sclength != length)
					continue;
				for(int i = 0; i < sclength; i++)
					scan[i] = tolower(scan[i]);
				strcpy(scancp, scan);
				qsort(scancp, sclength, sizeof(char), cmp);
				//printf("MAYBE:%s %s\n", scan, scancp);
				if(strcmp(scancp, word) == 0){
					if(strcmp(scan, wordcp) != 0)
						printf("%s\n", scan);
				}
			}
		}
		fclose(in);
	}
	return 0;
}

int cmp(const void* a, const void* b){
	return strcmp((const char*) a, (const char*) b);
}

int* numletters(char* word, int length){
	static int fin[26] = {0};
	for(int i = 0; i < length; i++)
		fin[word[i]-'a']++;
	return fin;
}
