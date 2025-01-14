#include "server/go_service.h"
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <iostream>
#include <grpcpp/grpcpp.h>

using grpc::ServerContext;
using grpc::Status;
using std::cout, std::endl;

Status GoServiceImpl::Move(ServerContext *context, const Coord *request, Empty *response) {
    Status st;
    if (mGameState.attemptMove(request->row(), request->col(), true))
        st = Status::OK;
    else
        st = Status::CANCELLED;

    cout << "Move: row " << request->row() << ", col " << request->col()
         << ", st " << (st.ok() ? "OK" : "FAILED") << endl;
    return st;
}
