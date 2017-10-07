#include "apue.h"

int
main(int argc,char *argv[])
{
	struct stat buf;
	

	if(argv[1] == 0){
		err_quit("usage: myls directory_name");
	}

	if(stat(argv[1],&buf) < 0){
		err_ret("stat error");
	}

	if(S_ISDIR(buf.st_mode)){
		
	}else{
		err_quit("error: %s is no a directory",argv[1]);
	}
}