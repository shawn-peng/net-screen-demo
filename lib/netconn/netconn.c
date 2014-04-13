
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


#include <basis.h>
#include "netconn.h"

typedef struct tag_netconn
{
	int socket_fd;

	NETCONN_TYPE conn_type;

	sockaddr_in peer_addr;
}NETCONN;

/**
 *
 */
void *netconn_create()
{
	NETCONN *new_conn = malloc(sizeof(*new_conn));
	if (NULL == new_conn)
	{
		trace_error("malloc");
		errno = ECANCELED;
		return NULL;
	}

	new_conn.socket_fd = socket(AF_INET, SOCK_STREAM, IPPRO);
	if (new_conn.socket_fd < 0)
	{
		trace_error("create socket");
		errno = ECANCELED;
		free(new_conn);
		return NULL;
	}
}

void netconn_destroy(void *conn)
{
	free(conn);
}

int netconn_setsockopt(void *conn)
{
	if (NULL == conn)
	{
		errno = EINVAL;
		return -1;
	}
	return 0;
}

int netconn_bind(void *conn)
{
	struct sockaddr_in addr;
	int ret;
	if (NULL == conn)
	{
		errno = EINVAL;
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(NETCONN_SVR_PORT);
	ret = inet_aton(INADDR_ANY, &addr.sin_addr);
	if (ret < 0)
	{
		trace_error("transform addr");
		errno = ECANCELED;
		return -1;
	}

	ret = bind(conn->socket_fd, (VOID *)&addr, sizeof(addr));
	if (ret < 0)
	{
		trace_error("bind");
		errno = ECANCELED;
		return -1;
	}

	return 0;
}

int netconn_waitconn(void *conn)
{
	int ret;

	ret = accept(conn->socket_fd, &conn->peer_addr,
				sizeof(conn->peer_addr));
	if (ret < 0)
	{
		trace_error("accept");
		errno = ECANCELED;
		return -1;
	}

	close(conn->socket_fd);
	conn->socket_fd = ret;

	return 0;
}

int netconn_connect(void *conn)
{
	int ret;

	ret = connect(conn->socket_fd, &conn->peer_addr,
				sizeof(conn->peer_addr));
	if (ret < 0)
	{
		trace_error("connect to server");
		errno = ECANCELED;
		return -1;
	}

	return 0;
}

int netconn_init(void *conn, NETCONN_TYPE type, char *ip_addr)
{
	if (NULL == conn)
	{
		errno = EINVAL;
		return -1;
	}
	conn->conn_type = type;

	if (NETCONN_SERVER == type)
	{
		// set socket opt
		ret = netconn_setsockopt(conn);
		if (ret < 0)
		{
			trace_error("set socket options");
			errno = ECANCELED;
			return -1;
		}

		// bind
		ret = netconn_bind(conn);
		if (ret < 0)
		{
			trace_error("bind netconn to service port");
			errno = ECANCELED;
			return -1;
		}

		// listen
		ret = netcon_listen(conn);
		if (ret < 0)
		{
			trace_error("set netconn to listen state");
			errno = ECANCELED;
			return -1;
		}
	}
	else if (NETCONN_CLIENT == type)
	{
		conn->peer_addr.sin_port = NETCONN_SVR_PORT;
		ret = inet_aton(ip_addr, &conn->peer_addr.sin_addr);
		if (ret < 0)
		{
			trace_error("trans ip address");
			errno = ECANCELED;
			return -1;
		}
	}
	else
	{
		errno = EINVAL;
		return -1;
	}

	return 0;
}

void *netconn_open(char *ip_addr, NETCONN_TYPE type)
{
	int ret;
	NETCONN *new_conn = netconn_create();
	if (NULL == new_conn)
	{
		trace_error("create netconn");
		errno = ECANCELED;
		return NULL;
	}

	ret = netconn_init(new_conn, type, ip_addr);
	if (ret < 0)
	{
		trace_error("init netconn");
		netconn_destroy(new_conn);
		errno = ECANCELED;
		return NULL;
	}

	if (NETCONN_SERVER == type)
	{// Server end
		// wait connection
		ret = netconn_waitconn(new_conn);
		if (ret < 0)
		{
			trace_error("wait connection");
			netconn_destroy(new_conn);
			errno = ECANCELED;
			return NULL;
		}
	}
	else if (NETCONN_CLIENT == type)
	{// Client end
		// connect
		ret = netconn_connect(new_conn);
		if (ret < 0)
		{
			trace_error("connect to netconn server");
			netconn_destroy(new_conn);
			errno = ECANCELED;
			return NULL;
		}
	}
	else
	{
		ASSERT(0);
		netconn_destroy(new_conn);
		errno = ECANCELED;
		return NULL;
	}

	return new_conn;
}

void netconn_close(void *conn)
{
	close(..);
	netconn_destroy(conn);
	return;
}

int netconn_send(void *conn, const void *buf, unsigned long datalen)
{
	int ret;

	ret = send(conn->socket_fd, buf, datalen, 0);
	if (ret < 0)
	{
		trace_error("send data");
		errno = ECANCELED;
		return -1;
	}

	return ret;
}

int netconn_recv(void *conn, void *buf, unsigned long bufsize)
{
	int ret;

	ret = recv(conn->socket_fd, buf, bufsize, 0);
	if (ret < 0)
	{
		trace_error("recv data");
		errno = ECANCELED;
		return -1;
	}

	return ret;
}


