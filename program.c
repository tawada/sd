#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
 
int isNum(const unsigned char*);
void init();
const unsigned char* num2str(int);
 
#define MAX 1024
unsigned char* name[MAX];
int main(int argc, char* argv[]){
    int i,j;
    init(path);
    if(argc==1){
        for(i=0;i<MAX-1;i++){
            if(name[i]==NULL)return 0;
            printf("%s\t%d\n",name[i],i);
        }
        return 0;
    }else if(argc==2){
        if(!isNum(argv[1])){
            printf("argment is not num.\n");
            exit(1);
        }
        printf("%s",num2str(atoi(argv[1])));
    }else{
        for(i=1;i<argc;i++){
            if(isNum(argv[i]))
                argv[i]=(char*)num2str(atoi(argv[i]));
        }
        for(i=1;i<argc;i++){
            printf("%s ",argv[i]);
        }
        printf("\n");
        execvp(argv[1],argv+1);
    }
    return 0;
}
int isNum(const unsigned char* str){
    while(*str!='\0'){
        if(*str<'0'||*str>'9')return 0;
        str++;
    }
    return 1;
}
void init(){
    DIR *dp;
    struct dirent *entry;
    int i;
    if((dp=opendir("./"))==NULL)
        exit(1);
    for(i=0;i<MAX-1;i++){
        entry=readdir(dp);
        if(entry!=NULL){
            name[i]=malloc(strlen(entry->d_name)+1);
            strcpy(name[i],entry->d_name);
        }else{
            name[i]=NULL;
            return;
        }
    }
    printf("warning:too many entry.\n");
    name[MAX-1]=NULL;
}
const unsigned char* num2str(int num){
    int i;
    for(i=0;i<=num;i++)
        if(name[i]==NULL)return NULL;
    return name[num];
}
