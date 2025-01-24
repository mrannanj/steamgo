#include "server/go_service.h"
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <iostream>
#include <grpcpp/grpcpp.h>

using grpc::ServerContext;
using grpc::Status;
using std::cout, std::endl;

Status GoServiceImpl::Move(ServerContext *context, const Coord *request, Empty *response) {
    const std::multimap<grpc::string_ref, grpc::string_ref> &map = context->client_metadata();
    for (const auto &kv : map) {
        cout << "Map: key " << kv.first << ", value " << kv.second << endl;
    }
    std::shared_ptr<const grpc::AuthContext> auth_ctx = context->auth_context();
    std::vector<grpc::string_ref> identity = auth_ctx->GetPeerIdentity();
    for (const auto &v : identity) {
        cout << "Identity: " << v << endl;
    }

    Status st;
    if (mGameState.attemptMove(request->row(), request->col(), true))
        st = Status::OK;
    else
        st = Status::CANCELLED;

    cout << "Move: row " << request->row() << ", col " << request->col()
         << ", st " << (st.ok() ? "OK" : "FAILED") << endl;
    return st;
}
