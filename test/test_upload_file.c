#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "make_log.h"

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd[2];//0为读端,1为写端
	pid_t pid;
	pid_t wpid;
	char buf[64];
	if(argc != 2)
	{
		printf("./main <local_filename>\n");
		exit(1);
	}
	//创建管道
	ret = pipe(fd);
	if(ret == -1)
	{
		printf("pipe error\n");
		exit(1);
	}
	//创建子进程
	pid = fork();
	if(pid == -1)
	{
		printf("fork error\n");
		exit(1);
	}
	//父进程
	if(pid > 0)
	{
		//关闭写端
		close(fd[1]);
		//读管道
		read(fd[0], buf, sizeof(buf));
		//打log
		dumpmsg_to_file("fdfs", "upload_file", __FILE__, __LINE__, __FUNCTION__, "%s", buf);
		//回收子进程
		while((wpid = waitpid(-1, NULL, WNOHANG)) != -1){}
		printf("log ok\n");
	}
	//子进程
	if(pid == 0)
	{
		//关闭读端
		close(fd[0]);
		//输出重定向
		dup2(fd[1], STDOUT_FILENO);
		//fdfs_upload_file
		execlp("fdfs_upload_file", "fdfs_upload_file", "/etc/fdfs/client.conf", argv[1], NULL);
		perror("fdfs_upload_file err\n");
		exit(1);
	}
	return ret;
}