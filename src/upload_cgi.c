#include "fcgi_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
//extern char **environ;
#endif

#include "fcgi_stdio.h"
#include <string.h>

//find 'substr' from a fixed-length buffer   
//('full_data' will be treated as binary data buffer)  
//return NULL if not found  
char* memstr(char* full_data, int full_data_len, char* substr) 
{ 
	if (full_data == NULL || full_data_len <= 0 || substr == NULL) { 
		return NULL; 
	} 

	if (*substr == '\0') { 
		return NULL; 
	} 

	int sublen = strlen(substr); 

	int i; 
	char* cur = full_data; 
	int last_possible = full_data_len - sublen + 1; 
	for (i = 0; i < last_possible; i++) { 
		if (*cur == *substr) { 
			//assert(full_data_len - i >= sublen);  
			if (memcmp(cur, substr, sublen) == 0) { 
				//found  
				return cur; 
			} 
		} 
		cur++; 
	} 

	return NULL; 
} 

/*
static void PrintEnv(char *label, char **envp)
{
	printf("%s:<br>\n<pre>\n", label);
	for ( ; *envp != NULL; envp++) {
		printf("%s\n", *envp);
	}
	printf("</pre><p>\n");
}
*/

int main ()
{
	//char **initialEnv = environ;
	int count = 0;
	char *buf = NULL;
	char *p = NULL;
	char *q = NULL;
	char line[128] = {0};
	char fileName[128] = {0};
	int fileLength = 0;

	while (FCGI_Accept() >= 0) {
		char *contentLength = getenv("CONTENT_LENGTH");
		int len;

		printf("Content-type: text/html\r\n"
				"\r\n"
				"<title>FastCGI echo</title>"
				"<h1>FastCGI echo</h1>\n"
				"Request number %d,  Process ID: %d<p>\n", ++count, getpid());

		if (contentLength != NULL) {
			len = strtol(contentLength, NULL, 10);
		}
		else {
			len = 0;
		}

		if (len <= 0) {
			printf("No data from standard input.<p>\n");
		}
		else {
			int i, ch;
			//开辟空间存储post的数据
			buf = malloc(len);

			printf("Standard input:<br>\n<pre>\n");

			for (i = 0; i < len; i++) {
				if ((ch = getchar()) < 0) {
					printf("Error: Not enough bytes received on standard input<p>\n");
					break;
				}
				buf[i] = ch;
				//putchar(ch);
			}
			//printf("%s", buf);

			//解析数据
			p = buf;
			q = buf;
			//获得协议头
			q = strstr(p, "\r\n");
			strncpy(line, p, q - p);
			printf("line:%s\n", line);
			//获得文件名
			p = strstr(q + 2, "filename=") + strlen("filename=");
			q = strstr(p, "\r\n");
			strncpy(fileName, p, q - p);
			printf("fileName:%s\n", fileName);
			//获得文件数据大小
			p = strstr(q + 2, "\r\n");
			p = strstr(p + 2, "\r\n") + 2;
			q = memstr(p, len - (p - buf), line);
			fileLength = q - 2 - p;
			printf("fileLength:%d\n", fileLength);

			printf("\n</pre><p>\n");
		}

		//PrintEnv("Request environment", environ);
		//PrintEnv("Initial environment", initialEnv);
	} /* while */

	return 0;
}
