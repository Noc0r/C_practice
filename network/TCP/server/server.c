#include "server.h"

typedef struct server_private
{
    server public;
    int socket;
    server_errors last_error;
} server_private;



static bool create_socket(server_private* this)
{
}

static bool bind_port(server_private* this, SA *server)
{
}

static SA *listen(server_private* this)
{
}

static int send(server_private* this)
{
}

static int read(server_private* this)
{
}

static int get_socket(server_private* this)
{
    return this->socket;
}

static void set_socket(server_private* this, int sock)
{
    this->socket = sock;
}

static server_errors get_last_error(server_private* this)
{
    return this->last_error;
}

server* create_server()
{

}