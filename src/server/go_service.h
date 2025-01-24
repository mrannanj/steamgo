#ifndef GO_SERVICE_H
#define GO_SERVICE_H

#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include "common/gamestate.h"

class GoServiceImpl final : public go_service::GoService::Service {
private:
    int mPlayerCount;
    GameState mGameState;
    grpc::ServerWriter<go_service::Move> *mServerWriter;
public:
    GoServiceImpl();
    grpc::Status Hello(grpc::ServerContext *context, const go_service::Empty *request,
                       go_service::Token *response) override;
    grpc::Status MakeMove(grpc::ServerContext *context, const go_service::Move *request,
                          go_service::Empty *response) override;
    grpc::Status Subscribe(grpc::ServerContext *context, const go_service::Empty *request,
                           grpc::ServerWriter<go_service::Move> *writer) override;
};

#endif // GO_SERVICE_H
