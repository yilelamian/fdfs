#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include"make_log.h"
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char* argv[])
{

	if(argc < 2)
	{
		printf("./app filename\n");
		return -2;
	}

	int fd[2];
	int i,j,k;
	int ret = pipe(fd);
	LOG("aa","bb","hello");
	if(ret == -1)
	{
		LOG("error","error1","pipe is error");
		perror("pipe is error\n");
		exit(1);
	}

	int pid;
	char buf[1024] = {0};
	pid = fork();
	if(pid > 0)
	{
		close(fd[1]);
		int len = read(fd[0],buf,sizeof(buf));
		LOG("fdfs_upload_file","fdfs_upload_file1",buf);
		//LOG("11","22","file_path");
		wait(NULL);
	}
	else if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf",argv[1],NULL);
	}
	else
	{
		printf("fork is error\n");
		return -1;
	}
	return 0;
}
