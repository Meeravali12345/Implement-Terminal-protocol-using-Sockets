/*Doc
Name:
Date:
Description:
Input:
Output:
Doc
 */
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define port 5000
int main()
{
    while(1)
    {
	struct sockaddr_in serveraddr;
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
	    printf("socket creation is failed\n");
	    close(fd);
	    return 0;
	}
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr);
	socklen_t size = sizeof(serveraddr);
	int fd1  = connect(fd,(struct sockaddr *)&serveraddr,size);
	if(fd1 == -1)
	{
	    printf("connection is failed\n");
	    close(fd);
	    return 0;
	}
	int a,b;
	printf("Enter numbers : ");
	scanf("%d %d",&a,&b);
	//printf("Enter character : ");
	char ch,buf[100];
	//scanf(" %c",&ch);
	printf("Enter a operator : ");
	scanf(" %c",&ch);
	ssize_t fd2 =  send(fd,&ch,sizeof(ch),0);
	if(fd2 == -1)
	{
	    printf("error in sending the data\n");
	    close(fd);
	    return 0;
	}
	//char buf[100];
	ssize_t fd3 = recv(fd,buf,sizeof(buf),0);
	if(fd3 == -1)
	{
	    printf("error in recv the data\n");
	    close(fd);
	    return 0;
	}
	printf("recv from server is %s\n",buf);
	char ip[16];
	int port1;
	sscanf(buf, "%s %d", ip, &port1);


	//second socket
	struct sockaddr_in server;
	int fd4 = socket(AF_INET, SOCK_STREAM, 0);
	if(fd4 == -1)
	{
	    printf("Socket creation is failed\n");
	    return 0;

	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port1);
	inet_pton(AF_INET, ip, &server.sin_addr);
	int fd5 = connect(fd4, (struct sockaddr *)&server, sizeof(server));
	if(fd5 == -1)
	{
	    printf("Connection is failed\n");
	    close(fd4);
	    close(fd);
	}

	printf("INFO: Created server socket\n");

	int arr[2] = {a, b};
	ssize_t fd6 = send(fd4, arr, sizeof(arr), 0);
	if(fd6 == -1)
	{
	    printf("error in while second socket sending data\n");
	    close(fd);
	    close(fd5);
	    return 0;
	}
	int result;
	ssize_t fd7 =  recv(fd4, &result, sizeof(result), 0);
	if(fd7 == -1)
	{
	    printf("error in while second socket recv data\n");
	    close(fd);
	   close(fd5);
	    return 0;
	} 
	printf("RESULT: %d\n", result);

	close(fd4);
	close(fd);
	//rieturn 0;
    }
    //close(fd);
    return 0;
}


