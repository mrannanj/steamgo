#include "client/go_service_client.h"
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using std::cerr, std::endl;

GoServiceClient::GoServiceClient(std::shared_ptr<Channel> channel):
    channel_(channel), stub_(GoService::NewStub(channel_))
{}

bool GoServiceClient::tryConnect() {
    return channel_->GetState(true) == GRPC_CHANNEL_READY;
}

bool GoServiceClient::move(int row, int col) {
    Coord request;
    request.set_row(row);
    request.set_col(col);
    Empty response;
    ClientContext context;

    Status status = stub_->Move(&context, request, &response);

    return status.ok();
}
