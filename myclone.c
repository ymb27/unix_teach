#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFSIZE 4096

int
main(int argc,char *argv[]){

	int n,source,new;
	char buf[BUFFSIZE];
	struct stat statbuf;
	struct timespec times[2];

	if((source = open(argv[1],O_RDONLY)) < 0){
		err_sys("error: %s is no a file",argv[1]);
	}

	if(stat(argv[1],&statbuf) < 0){
		err_ret("%s : stat error",argv[1]);
	}

	times[0] = statbuf.st_atim;
	times[1] = statbuf.st_mtim;

	if((new = open(argv[2],O_RDWR|O_CREAT|O_TRUNC)) < 0){
			err_sys("error: %s is no a file",argv[2]);
		}

	while((n = read(source,buf,BUFFSIZE)) > 0){
		if(write(new,buf,n) != n)
			err_sys("write error");
	}
		
		if(n < 0)
			err_sys("read error");

	if(futimens(new,times) < 0)
		err_ret("%s: futimens error",argv[2]);

	close(new);
	exit(0);
}