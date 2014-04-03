
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "netconn.h"

typedef struct tag_netconn
{
	int fd_socket;

	NETCONN_TYPE conn_type;
}NETCONN;


void *netconn_open(int ip_addr, NETCONN_TYPE type)
{
	NETCONN *new_conn = malloc(sizeof(*new_conn));
	new_conn.fd_socket = socket(AF_INET, SOCK_STREAM, );
}

void netconn_close(void *conn)
{

}

int netconn_send(void *buf, unsigned long datalen)
{

}

int netconn_recv(void *buf, unsigned long bufsize)
{

}


