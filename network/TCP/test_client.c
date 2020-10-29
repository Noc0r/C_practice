#include <stdio.h>
#include "client/client.h"

int main()
{
    client_private *client_entry = create_client();
    client *client_lib = get_public(client_entry);
    struct sockaddr_in servaddr;
    if (client_lib->create_socket(client_entry))
        printf("nice");
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (client_lib->connect_to_server(client_entry, &servaddr))
        printf("nice");
    client_lib->send_data(client_entry, "hehehe", 6);
    destroy_client(client_entry);
    return 0;
}