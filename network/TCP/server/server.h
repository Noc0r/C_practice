#if !defined(SERVER)
#define SERVER

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdbool.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

typedef struct server_interface server;

typedef enum server_errors
{
    TCP_CREATE_SERVER_ERROR,
    TCP_BIND_SERVER_ERROR,
    TCP_LISTEN_SERVER_ERROR,
    TCP_SEND_SERVER_ERROR,
    TCP_READ_SERVER_ERROR,
    ALL_OK
} server_errors;

struct server_interface
{
    bool (*create_socket)(server_interface* interface);
    bool (*bind_port)(server_interface* interface, SA* server);
    SA* (*listen)(server_interface* interface);
    int (*send)(server_interface* interface);
    int (*read)(server_interface* interface);
    int (*get_socket)(server_interface* interface);
    void (*set_socket)(server_interface* interface, int sock);
    server_errors (*get_last_error)(server_interface* interface);
};

server_interface* create_server();

#endif // SERVER
