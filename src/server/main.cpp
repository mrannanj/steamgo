#include "server/go_service.h"
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using std::cout, std::endl, std::string, std::unique_ptr;

void runServer() {
    string server_address("0.0.0.0:50051");
    GoServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;
    server->Wait();
}

int main() {
    runServer();
    return 0;
}
