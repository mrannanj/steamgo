#ifndef GO_SERVICE_H
#define GO_SERVICE_H

#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include "common/gamestate.h"

class GoServiceImpl final : public GoService::Service {
private:
    GameState mGameState;
public:
    grpc::Status Move(grpc::ServerContext *context, const Coord *request, Empty *response) override;
};

#endif // GO_SERVICE_H
