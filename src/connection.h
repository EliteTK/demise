#ifndef __CONNECTION_H

enum c_error {
        SUCCESS,
        ADDRESS_RESOLVE_FAIL,
        SOCKET_CREATE_FAIL,
        CONNECT_FAIL,
};

typedef struct {
        int socket;
} Connection;

Connection *c_connect(char *, int, enum c_error *);
void c_disconnect(Connection *);
int c_send(Connection *, char *);
int c_recv(Connection *, char *, int);

#define __CONNECTION_H 1
#endif
