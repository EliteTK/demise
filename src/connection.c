#include "connection.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static char **dns_servers;
static int dns_servers_count;

static bool to_in_addr(struct in_addr *, char *);

Connection *c_connect(char *address, int port, enum c_error *err)
{
        struct in_addr sin_addr;
        if (!to_in_addr(&sin_addr, address)) {
                *err = ADDRESS_RESOLVE_FAIL;
                return NULL;
        }

        int s;
        if (!(s = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0))) {
                *err = SOCKET_CREATE_FAIL;
                return NULL;
        }

        struct sockaddr_in saddr = {
                AF_INET,
                port,
                sin_addr
        };

        if (connect(s, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) < 0) {
                *err = CONNECT_FAIL;
                return NULL;
        }

        Connection *connection = malloc(sizeof(Connection));

        connection->socket = s;

        *err = SUCCESS;
        return connection;
}

void c_disconnect(Connection *connection)
{
        close(connection->socket);
        free(connection);
}

int c_send(Connection *connection, char *message)
{
        return send(connection->socket, message, strlen(message), 0);
}

int c_recv(Connection *connection, char *message, int length)
{
        return recv(connection->socket, message, length, 0);
}

static bool parse(struct in_addr *output, char *source)
{
        if (inet_pton(AF_INET, source, output))
                return false;

        struct hostent* he;

        if(!(he = gethostbyname(source))) {
                herror("gethostbyname");
                return true;
        }

        memcpy(output, he->h_addr, sizeof(struct in_addr));
        return false;
}
