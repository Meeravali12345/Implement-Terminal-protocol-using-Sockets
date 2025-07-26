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
struct ips
{
    char op;
    char addr[16];
    int ports;
};
struct ips ip[]={
    {'+',"127.0.0.1",6000},
    {'-',"127.0.0.1",6001},
    {'/',"127.0.0.1",6002},
    {'*',"127.0.0.1",6003},
    {'%',"127.0.0.1",6004}
};
int main()
{
    struct sockaddr_in serveraddr,cliant;
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1)
    {
	printf("socket creation is failed\n");
	close(fd);
	return 0;
    }
    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&cliant,0,sizeof(cliant));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t size = sizeof(serveraddr);
    int fd4 =  bind(fd,(struct sockaddr *)&serveraddr,size);
    if(fd4 == -1)
    {
	printf("binding failed\n");
	close(fd);
	return 0;
    }
    int fd5 = listen(fd,1);
    if(fd5 == -1)
    {
	printf("listen is failed\n");
	close(fd);
	return 0;
    }
    printf("port listening\n");
    socklen_t size_cliant = sizeof(cliant);
    int fd1;
    while(1)
    {
	fd1  = accept(fd,(struct sockaddr *)&cliant,&size_cliant);
	if(fd1 == -1)
	{
	    printf("connection is failed\n");
	    close(fd);
	    close(fd1);
	    return 0;
	}
	char ch,buf[100];
	ssize_t fd2 =  recv(fd1,&ch,sizeof(ch),0);
	if(fd2 == -1)
	{
	    printf("error in recv the data\n");
	    close(fd);
	    close(fd1);
	    return 0;
	}
	//printf("recv operator from client is %c\n",ch);
	printf("recv from client ch = %c\n",ch);
	for(int i=0;i<5;i++)
	{
	    if(ip[i].op == ch)
	    {
		sprintf(buf,"%s %d",ip[i].addr,ip[i].ports);
		ssize_t fd3 = send(fd1,buf,strlen(buf)+1,0);
		if(fd3 == -1)
		{
		    printf("error in recv the data\n");
		    close(fd1);
		    close(fd);
		    return 0;
		}
		printf("response sent to client\n");
		//close(fd1);
	    }
	}
	//close(fd);
    }
    close(fd1);
}


