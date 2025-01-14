#include "server/go_service.h"
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <iostream>
#include <grpcpp/grpcpp.h>

using grpc::ServerContext;
using grpc::Status;
using std::cout, std::endl;

Status GoServiceImpl::Move(ServerContext *context, const Coord *request, Empty *response) {
    cout << "Move: row " << request->row() << ", col " << request->col() << endl;
    return Status::OK;
}
