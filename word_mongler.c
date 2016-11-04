#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static int MAX_MALLOC = 5000; 
static int MAX_WORD = 35; 
int main(void) { 

srand(time(NULL)); 
char *path = getenv("HOME"); 
char *filename = "/.words"; 
char *wds; 
int cand_length;
char *cand; 
char *savept = malloc(MAX_WORD);
int memsize;
int pathsize = strlen(path) + strlen(filename) + 2;
int fpoint,selection;
long i;
char *word = malloc(MAX_WORD); 
memset(word,0,MAX_WORD);  
char *filepath = malloc(pathsize);
memset(filepath,0,pathsize);  
strncpy(filepath,path,strlen(path)); 
strncat(filepath,filename,strlen(filename)); 

FILE *fp = fopen(filepath,"r"); 
fseek(fp,0L,SEEK_END); 
fpoint = ftell(fp); 
rewind(fp); 
selection = rand() % fpoint + 1;
if(selection >  fpoint / 2) {
i = fpoint / 2; 
}
else  {
i = 0; 
}
selection = fpoint / 2;

memsize = (selection < MAX_MALLOC) ? selection:MAX_MALLOC; 
wds = malloc(memsize);
fseek(fp,i,SEEK_SET);  
fgets(wds,memsize,fp); 
fclose(fp); 
free(filepath);  
while(*word == 0) { 
cand = strtok_r(wds,"\r",&savept);
while(rand() % 2)
cand = strtok_r(NULL,"\r",&savept);
if(cand != NULL) { 
cand_length = (strlen(cand) < MAX_WORD) ? strlen(cand):MAX_WORD;
strncpy(word,cand,cand_length);
}

}
printf("%s\n",word);  
return 0; 

}

