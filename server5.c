/*Doc
Name:
Date:
Description:
Input:
Output:
Doc
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 6004

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr, client;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    int b = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(b==-1)
    {
        printf("binding failed\n");
        close(fd);
        return 0;
    }
    int s = listen(fd, 1);
    if(s==-1)
    {
        printf("listening failed\n");
        close(fd);
    }

    printf("LISTENING: minus server is listening\n");

    while(1) {  // Add infinite loop
        socklen_t clen = sizeof(client);
        int cfd = accept(fd, (struct sockaddr *)&client, &clen);
        if(cfd==-1)
        {
            printf("accept failed\n");
            close(fd);
            return 0;
        }
        printf("ACCEPTED: accepted a connection\n");

        int arr[2];
        ssize_t fd2 = recv(cfd, arr, sizeof(arr), 0);
        if(fd2==-1)
        {
            printf("recv failed\n");
            close(fd);
            close(cfd);
            return 0;
        }
        printf("Client data: %d %d +\n", arr[0], arr[1]);

        int result = arr[0] % arr[1];
        printf("Result is %d\n", result);
        ssize_t fd3 = send(cfd, &result, sizeof(result), 0);
        if(fd3 == -1)
        {
            printf("sending failed\n");
            close(fd);
            close(cfd);
            return 0;
        }
        printf("Sending result to client...\n");

        //close(cfd);  // Close client connection but keep server running
    }

    close(fd);
    return 0;
}

