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
    bool hello(void);
    bool move(int row, int col);
    bool subscribe(void);
    go_service::Color getClientType(void) const;
    go_service::Move getMove(void);

private:
    //std::unique_ptr<grpc::ClientReader<go_service::Move>> mClientReader;
    go_service::Color mColor;
    std::unique_ptr<go_service::GoService::Stub> stub_;
};

#endif // GO_SERVICE_CLIENT_H
