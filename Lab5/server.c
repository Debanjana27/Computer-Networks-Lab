//server file
/*Client sends one integer. Server reverse the number and send back 
to client.*/
#include <stdio.h>
#include <sys/socket.h>     //for socket(),connect()
#include <arpa/inet.h>      //for server
#include <string.h>         //for exit()
#include <stdlib.h>         //for strlen()


int main(){

    int sock_fd,new_sock,c;                                   //Creating Socket variable
    struct sockaddr_in server,client;                     //Visit: https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
    int num,sign=0,t=0;

    //Task1 - Creating socket
    sock_fd=socket(AF_INET,SOCK_STREAM,0);         //if socket() doesn't returns -1 the socket created       
    if(sock_fd == -1) {
        puts("Client socket creation FAILED\n");
        exit(1);
    }

    //part2 - Assigning server information
    server.sin_addr.s_addr = INADDR_ANY;                         //INADDR_ANY= to listen to any aclient IP
    server.sin_port = htons(6666);                                 //Port of server 
    server.sin_family= AF_INET;                                  //AF_INET= IPV4 family

    //part3 - Bind socket to ipaddress
    if(bind(sock_fd,(struct sockaddr *)&server,sizeof(server))<0){
        puts("Server Bind failed");
        exit(1);
    }
    puts("Server Bind Successful\n");

    //part4 - Set the number of connection to service from requests
    listen(sock_fd,5);       //max 5 connection will be handled

    //part5 - Wait for connection
    c=sizeof(struct sockaddr_in);
    new_sock=accept(sock_fd,(struct sockaddr *)&client,(socklen_t*)&c);  //newsock will be used now for sending and receiving
    
    
    if(new_sock <0){
        puts("Accept failed");
    }
    puts("Connection Accepted\n");
        
    recv(new_sock,&num,sizeof(int),0);
    if(num<0)
        sign=1,num*=-1;
    for(;num>0;num/=10)
        t=(t*10)+(num%10);
    num=t*(sign==1?-1:1);
    send(new_sock,&num,sizeof(int),0);
    
    return 0;
}