#if !defined(CLIENT)
#define CLIENT

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

typedef struct client_interface client;

typedef enum client_errors
{
    TCP_CREATE_CLIENT_ERROR,
    TCP_CONNECT_CLIENT_ERROR,
    TCP_SEND_CLIENT_ERROR,
    TCP_READ_CLIENT_ERROR,
    ALL_OK
} client_errors;

struct client_interface
{
    bool (*create_socket)(client_interface interface);
    bool (*connect)(client_interface interface, SA* server);
    int (*send)(client_interface interface);
    int (*read)(client_interface interface);
    int (*get_socket)(client_interface interface);
    void (*set_socket)(client_interface interface);
    client_errors (*get_last_error)();
};

client_interface* create_client();

#endif // CLIENT
