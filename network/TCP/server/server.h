#if !defined(SERVER)
#define SERVER

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

typedef struct server_interface server;
typedef struct server_private server_private;

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
    bool (*create_socket)(server_private* interface);
    bool (*bind_port)(server_private* interface, struct sockaddr_in * server);
    struct sockaddr_in* (*listen_socket)(server_private* interface);
    int (*send_data)(server_private* interface, char* msg, int msg_len);
    int (*read_data)(server_private* interface, char* msg, int msg_len);
    int (*get_socket)(server_private* interface);
    void (*set_socket)(server_private* interface, int sock);
    server_errors (*get_last_error)(server_private* interface);
};

server_private* create_server();
server* get_public(server_private* this);
void destroy_server(server_private* this);

#endif // SERVER
