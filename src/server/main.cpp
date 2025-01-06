#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int accept_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (accept_fd < 0) {
        perror("socket() failed");
        exit(1);
    }
    struct sockaddr_in my_sa = {
        .sin_family = AF_INET,
        .sin_port = htons(2048),
        .sin_addr = {
            .s_addr = inet_addr("127.0.0.1"),
        },
    };
    int value = 1;
    if (setsockopt(accept_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0) {
        perror("setsockopt() failed");
        exit(1);
    }
    if (bind(accept_fd, (sockaddr*)&my_sa, sizeof(my_sa)) < 0) {
        perror("bind() failed");
        exit(1);
    }
    if (listen(accept_fd, 3) < 0) {
        perror("listen() failed");
        exit(1);
    }
    int client_fd = accept(accept_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept() failed");
        exit(1);
    }
    const char hello[] = "Hello, World\n";
    if (write(client_fd, hello, sizeof(hello)) < 0) {
        perror("write() failed");
        exit(1);
    }

    close(client_fd);
    close(accept_fd);

    return 0;
}
