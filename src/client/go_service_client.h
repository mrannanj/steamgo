#ifndef GO_SERVICE_CLIENT_H
#define GO_SERVICE_CLIENT_H

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"

class GoServiceClient {
public:
    GoServiceClient(std::shared_ptr<grpc::Channel> channel);

    bool tryConnect(void);
    bool move(int row, int col);

private:
    std::shared_ptr<grpc::Channel> channel_;
    std::unique_ptr<GoService::Stub> stub_;
};

#endif // GO_SERVICE_CLIENT_H
