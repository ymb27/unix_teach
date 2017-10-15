#include "apue.h"
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>

int
main(int argc,char *argv[])
{

	DIR *dp;
	struct stat buf;
	struct dirent *dirp;

	char usr_mode[]="---";
	
	if(argv[1] == 0){
		err_quit("usage: myls directory_name");
	}


	if((dp = opendir(argv[1])) == NULL)

		err_quit("error: %s is no a directory",argv[1]);
	
		while((dirp = readdir(dp)) != NULL){

			if(stat(dirp->d_name,&buf) == 0){
				
				if(S_ISREG(buf.st_mode)){

					if(buf.st_mode & S_IRUSR)
						usr_mode[0] = 'r';
					
					if(buf.st_mode & S_IWUSR)
						usr_mode[1] = 'w';
					
					if(buf.st_mode & S_IXUSR)
						usr_mode[2] = 'x';
					

				printf("%s ",usr_mode);

				printf("%s ",getpwuid(buf.st_uid)->pw_name);

				printf("%s\n",dirp->d_name);
				}
			}
		}

				

	closedir(dp);
	exit(0);
}