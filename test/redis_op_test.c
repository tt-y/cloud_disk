#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "redis_op.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    redisContext *conn = NULL;

    conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if (conn == NULL) {
        printf("connect error\n");
        exit(1);
    }

    
    ret = rop_list_push(conn, "my_list", "gailun");
    if (ret != 0) {
        printf("lpush error\n");
        exit(1);
    }

    printf("lpush succ\n");

		ret = rop_set_string(conn, "my_key", "key1");
    if (ret != 0) {
        printf("set string error\n");
        exit(1);
    }

    printf("set string succ\n");
    
    char value[VALUES_ID_SIZE] = {0};
    ret = rop_get_string(conn, "my_key", value);
    if (ret != 0) {
        printf("get string error\n");
        exit(1);
    }

    printf("get string succ\n");
    printf("\"%s\"\n", value);

    if (conn!=NULL) {
        rop_disconnect(conn);
    }

	return 0;
}
