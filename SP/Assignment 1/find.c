#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int compareString(char* s1, char* s2){
	int i=0;
	while(s1[i]!='\0'){
		if(s1[i]!=s2[i])
			return -1;
		i++;
	}
	return 1;
}

void findWithName(char* path, char *fileName){
	DIR *dp=opendir(path);
	struct dirent *dirs;
	errno=0;
	char compPath[1000]="\0";
	
	while(1){
		for(int i=0;i<1000;i++)
		compPath[i]='\0';
		int i=0;
		
		for(i=0;path[i]!='\0';i++)
			compPath[i]=path[i];
		errno=0;
		dirs=readdir(dp);
		
		if(dirs==NULL){
			if(errno!=0){
				perror("Error: ");
				break;
			}
			else{
				break;
			}
		}
		if(compareString(fileName,dirs->d_name)==1){
			int k=0;
			if(compPath[i-1]!='/'){
				compPath[i]='/';
				i++;
			}
			while(dirs->d_name[k]!='\0'){
				compPath[i]=dirs->d_name[k];
				i++;
				k++;
			}
			printf("%s\n", compPath);
		}
		else if(dirs->d_type==4){
			if(dirs->d_name[0]=='.')
				continue;
			int k=0;
			if(compPath[i-1]!='/'){
				compPath[i]='/';
				i++;
			}
			while(dirs->d_name[k]!='\0'){
				compPath[i]=dirs->d_name[k];
				i++;
				k++;
			}
		 	findWithName(compPath,fileName);
		} 
		
	}
}


void findWithMode(char* path, int modeI){
	DIR *dp=opendir(path);
	struct dirent *dirs;
	errno=0;
	
	
	while(1){
		char compPath[1000]="\0";
		int i=0;
		
		for(i=0;path[i]!='\0';i++)
			compPath[i]=path[i];
		dirs=readdir(dp);
		errno=0;
		if(dirs==NULL){
			if(errno!=0){
				perror("Error: ");
				return;
			}
			else{
				return;
			}
		}
		
		compPath[i]='/';
		i++;
		int k=0;
		while(dirs->d_name[k]!='\0'){
			compPath[i]=dirs->d_name[k];
			i++;
			k++;
		}
		if(modeI==dirs->d_type){
			if(compareString(dirs->d_name,".")==1 || compareString(dirs->d_name,"..")==1)
				continue;
			
			printf("%s\n", compPath);
		}
		if(dirs->d_type==DT_DIR){
			if(compareString(dirs->d_name,".")==1 || compareString(dirs->d_name,"..")==1)
				continue;
			findWithMode(compPath,modeI);
		}
	}
}

int main(int argc, char* argv[]){
	if(argc!=4){
		printf("Use correct format: ./find /dir -name filename.\n" );
	}
	else if(argv[2][1]=='n') {
		findWithName(argv[1],argv[3]);
	}
	else{
		int modeI=0;
		char mode=argv[3][0];
		if(mode == 'b')
			modeI=DT_BLK;
		else if(mode == 'c')
			modeI=DT_CHR;
		else if(mode == 'd')
			modeI=DT_DIR;
		else if(mode == 'p')
			modeI=DT_FIFO;
		else if(mode == 'l')
			modeI=DT_LNK;
		else if(mode == 's')
			modeI=DT_SOCK;
		else if(mode == 'f')
			modeI=DT_REG;
		else return 0;
		findWithMode(argv[1],modeI);
	}
	return 0;
}
