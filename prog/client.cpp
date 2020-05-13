#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>

using namespace std;

char in[1024];
char out[1024];
char stop[] = "/stop";
char* ip = "127.0.0.1";

int main() {
    char srv_name[1024];
    struct sockaddr_in address;

    int serv = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(5001);

    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(srv_name, 0, sizeof(srv_name));

    cout << "Type your name: ";
    fgets(out, sizeof(out), stdin);
    connect(serv, (struct sockaddr *)&address, sizeof(address));
    write(serv, out, strlen(out)-1);
    cout << "Connected! Wait server name..." << endl;
    recv(serv, srv_name, sizeof(srv_name), 0);
    cout << srv_name <<  " connected!" << endl;
    while (1){
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        recv(serv, in, sizeof(in), 0);
        if (strncmp(in, stop, 5) == 0){
            close(serv);
            cout << "connection closed by " << srv_name << endl;
            exit(1);
        }
        cout << endl << srv_name << ": " << in << endl;
        cout << "you: ";
        fgets(out, sizeof(out), stdin);
        write(serv, out, strlen(out));
        if (strncmp(out, stop, 5) == 0){
            close(serv);
            cout << "connection closed by you" << endl;
            exit(1);
        }
    }
}
