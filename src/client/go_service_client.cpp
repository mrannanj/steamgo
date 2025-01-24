#include "client/go_service_client.h"
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"

using go_service::GoService, go_service::Move, go_service::Empty, go_service::Token;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using std::cerr, std::endl;

GoServiceClient::GoServiceClient(std::shared_ptr<Channel> channel):
    stub_(GoService::NewStub(channel)) {}

bool GoServiceClient::hello(void) {
    ClientContext context;
    Empty request;
    Token response;

    Status status = stub_->Hello(&context, request, &response);
    if (status.ok()) {
        mColor = response.color();
        return true;
    }
    return false;
}

bool GoServiceClient::move(int row, int col) {
    ClientContext context;
    Move request;
    request.set_row(row);
    request.set_col(col);
    request.set_color(mColor);
    Empty response;

    Status status = stub_->MakeMove(&context, request, &response);

    return status.ok();
}

bool GoServiceClient::subscribe(void) {
    ClientContext context;
    Empty request;
    std::unique_ptr<grpc::ClientReader<go_service::Move>> reader(stub_->Subscribe(&context, request));
    go_service::Move move;
    while (reader.get()->Read(&move)) {
        std::cout << "got Move: " << move.row() << ", " << move.col() << endl;
    }
    //mClientReader = std::move(reader);
    return true;
}

go_service::Color GoServiceClient::getClientType(void) const {
    return mColor;
}

go_service::Move GoServiceClient::getMove(void) {
    go_service::Move move;
    //mClientReader.get()->Read(&move);
    return move;
}
