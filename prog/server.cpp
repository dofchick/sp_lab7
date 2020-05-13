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


int main() {
    char cl_name[1024];
    int clnt = 0;
    struct sockaddr_in address;

    int serv = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(5001);

    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(cl_name, 0, sizeof(cl_name));

    bind(serv, (struct sockaddr*)&address, sizeof(address));
    cout << "Server working!" << endl;
    listen(serv, 1);
    clnt = accept(serv, (struct sockaddr*)NULL, NULL);
    recv(clnt, cl_name, sizeof(cl_name), 0);
    cout << cl_name <<  " connected!" << endl << "please type your name :";
    fgets(out, sizeof(out), stdin);
    write(clnt, out, strlen(out)-1);
    while (1){
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        cout << "you: ";
        fgets(out, sizeof(out), stdin);
        write(clnt, out, strlen(out));
        if (strncmp(out, stop, 5) == 0){
            close(clnt);
            cout << "connection closed by you" << endl;
            exit(1);
        }
        recv(clnt, in, sizeof(in), 0);
        if (strncmp(in, stop, 5) == 0){
            close(clnt);
            cout << "connection closed by " << cl_name << endl;
            exit(1);
        }
        cout << endl << cl_name << ": " << in << endl;
    }
}
