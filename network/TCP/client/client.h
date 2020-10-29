#if !defined(CLIENT)
#define CLIENT

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

typedef struct client_interface client;
typedef struct client_private client_private;

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
    bool (*create_socket)(client_private *interface);
    bool (*connect_to_server)(client_private *interface, struct sockaddr_in *server);
    int (*send_data)(client_private *interface, char *msg, int msg_len);
    int (*read_data)(client_private *interface, char* msg, int msg_len);
    int (*get_socket)(client_private *interface);
    void (*set_socket)(client_private *interface, int sock);
    client_errors (*get_last_error)(client_private *);
};

client_private *create_client();
client* get_public(client_private* this);
void destroy_client(client_private* this);

#endif // CLIENT
