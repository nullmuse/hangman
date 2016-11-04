#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static int MAX_MALLOC = 5000; 
static int MAX_WORD = 35; 


//Convert ascii representation of number to int
//Adapted from my timestable code
int transmute_char(char *subject) {
   int len = strlen(subject) - 1;
   int i,new = 0;

   for(i = 1;len >= 0;--len,i *= 10) {
      //built in handling of non-integer input
      if(subject[len] > 0x39 || subject[len] < 0x30) {
         return 0;
      }
      new += (subject[len] - 0x30) * i;
  }
   return new;
 }

//Convert integer to ascii representation
//Adapted from my timestable code 
char *transmute_int(int subject, int size) {
   int container = 0;
   int count = size - 1;
   int check = 0;
   char *new = malloc(size); //freeing the memory left to caller
   memset(new,0,size);

while(subject) {
      container = subject % 10;
      subject /= 10;
      new[--count] = container + 0x30;
      check++;
      }

   return new;
}







char *word_mongler(void) { 

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
char *word = NULL; 
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
while(word == NULL) { 
cand = strtok_r(wds,"\r",&savept);
while(rand() % 2)
cand = strtok_r(NULL,"\r",&savept);
if(cand != NULL) { 

cand_length = (strlen(cand) < MAX_WORD) ? strlen(cand):MAX_WORD;
word = malloc(cand_length + 1);
memset(word,0,cand_length + 1);  
strncpy(word,cand,cand_length - 1);
}

}
free(wds);
free(savept);
return word; 

}

char *read_stats(int read) { 

char *path = getenv("HOME");
char *filename = "/.hangman";
char *cand;
int memsize;
char *stats = malloc(10);
char *stat = malloc(10);
memset(stats,0,10);  
memset(stat,0,10);
int pathsize = strlen(path) + strlen(filename) + 2;
int fpoint,selection;
long i;
char *word = NULL;
char *filepath = malloc(pathsize);
memset(filepath,0,pathsize);
strncpy(filepath,path,strlen(path));
strncat(filepath,filename,strlen(filename));

FILE *fp  = fopen(filepath,"r");
if(fp == NULL)
  return NULL; 
fgets(stats,9,fp); 
strncpy(stat,stats,strlen(stats));
fclose(fp); 
free(filepath);
if(read) {
printf("Games played:%s",strtok(stats,":"));
printf(" Games won:%s",strtok(NULL,":"));
printf(" Games lost %s\n",strtok(NULL,":")); 
//,strtok(stats,NULL),strtok(stats,NULL));
} 

return stat; 

} 


void push_stats(char *stats) { 

char *path = getenv("HOME");
char *filename = "/.hangman";
char *cand;
int memsize;
int pathsize = strlen(path) + strlen(filename) + 2;
int fpoint,selection;
long i;
char *word = NULL;
char *filepath = malloc(pathsize);
memset(filepath,0,pathsize);
strncpy(filepath,path,strlen(path));
strncat(filepath,filename,strlen(filename));

FILE *fp = fopen(filepath,"w+");
fputs(stats,fp); 
fclose(fp);
free(filepath); 

return;

}

