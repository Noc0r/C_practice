#include "server.h"

typedef struct server_private
{
    server public;
    int socket;
    int connect_socket;
    server_errors last_error;
} server_private;

static bool create_socket(server_private *this)
{
    this->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket == -1)
    {
        return false;
    }
    return true;
}

static bool bind_port(server_private *this, struct sockaddr_in *server)
{
    if ((bind(this->socket, (SA *)server, sizeof(struct sockaddr_in))) != 0)
    {
        return false;
    }
    return true;
}

static struct sockaddr_in *listen_socket(server_private *this)
{
    if ((listen(this->socket, 1)) != 0)
    {
        return NULL;
    }
    int len = sizeof(struct sockaddr_in);
    struct sockaddr_in *cli = (struct sockaddr_in *)malloc(len);
    this->connect_socket = accept(this->socket, (SA *)cli, &len);
    return cli;
}

static int send_data(server_private *this, char *msg, int msg_len)
{
    send(this->connect_socket, msg, msg_len, 0);
}

static int read_data(server_private *this, char *msg, int msg_len)
{
    recv(this->connect_socket, msg, msg_len, 0);
}

static int get_socket(server_private *this)
{
    return this->socket;
}

static void set_socket(server_private *this, int sock)
{
    this->socket = sock;
}

static server_errors get_last_error(server_private *this)
{
    return this->last_error;
}

server_private *create_server()
{
    server_private *this = (server_private *)malloc(sizeof(server_private));
    this->last_error = ALL_OK;
    this->public.bind_port = bind_port;
    this->public.create_socket = create_socket;
    this->public.get_last_error = get_last_error;
    this->public.get_socket = get_socket;
    this->public.listen_socket = listen_socket;
    this->public.read_data = read_data;
    this->public.send_data = send_data;
    this->public.set_socket = set_socket;
    return this;
}

server *get_public(server_private *this)
{
    return &this->public;
}

void destroy_server(server_private *this)
{
    close(this->socket);
}