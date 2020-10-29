#include "client.h"

typedef struct client_private
{
    client public;
    int socket;
    client_errors last_error;
} client_private;

static bool create_socket(client_private *this)
{
    this->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket == -1)
    {
        return false;
    }
    return true;
}

static bool connect_to_server(client_private *this, struct sockaddr_in *server)
{
    if (connect(this->socket, (SA *)server, sizeof(struct sockaddr_in)) != 0)
    {
        return false;
    }
    return true;
}

static int send_data(client_private *this, char *msg, int msg_len)
{
    send(this->socket, msg, msg_len, 0);
}

static int read_data(client_private *this, char* msg, int msg_len)
{
    recv(this->socket, msg, msg_len, 0); 
}

static int get_socket(client_private *this)
{
    return this->socket;
}

static void set_socket(client_private *this, int sock)
{
    this->socket = sock;
}

static client_errors get_last_error(client_private *this)
{
    return this->last_error;
}

client_private *create_client()
{
    client_private* this = (client_private*)malloc(sizeof(client_private));
    this->last_error = ALL_OK;
    this->public.create_socket = create_socket;
    this->public.get_last_error = get_last_error;
    this->public.get_socket = get_socket;
    this->public.connect_to_server = connect_to_server;
    this->public.read_data = read_data;
    this->public.send_data = send_data;
    this->public.set_socket = set_socket;
    return this;
}
void destroy_client(client_private* this)
{
    close(this->socket);
}

client* get_public(client_private* this)
{
    return &this->public;
}