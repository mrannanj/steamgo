#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using std::cout, std::endl, std::string, std::unique_ptr;

class GoServiceImpl final : public GoService::Service {
    Status Move(ServerContext *context, const Coord *request, Empty *response) override {
        cout << "Move: row " << request->row() << ", col " << request->col() << endl;
        return Status::OK;
    }
};

void RunServer() {
    string server_address("0.0.0.0:50051");
    GoServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;
    server->Wait();
}
