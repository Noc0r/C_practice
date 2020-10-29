#include <stdio.h>
#include "server/server.h"

int main()
{
    server_private *server_entry = create_server();
    server *server_lib = get_public(server_entry);
    struct sockaddr_in servaddr;
    if (server_lib->create_socket(server_entry))
        printf("nice");
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if (server_lib->bind_port(server_entry, &servaddr))
        printf("nice");
    struct sockaddr_in *client = server_lib->listen_socket(server_entry);
    if (client)
        printf("nice");
    char *buffer = (char *)malloc(10 * sizeof(char));
    server_lib->read_data(server_entry, buffer, 10);
    printf("%s", buffer);
    destroy_server(server_entry);
    return 0;
}