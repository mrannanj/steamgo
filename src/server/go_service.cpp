#include "server/go_service.h"
#include "protos/go_service.pb.h"
#include "protos/go_service.grpc.pb.h"
#include <iostream>
#include <grpcpp/grpcpp.h>

using go_service::Color, go_service::Empty, go_service::Token;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;
using std::cout, std::endl;

GoServiceImpl::GoServiceImpl():
    mPlayerCount(0),
    mGameState(),
    mServerWriter(nullptr)
{
}

Status GoServiceImpl::Hello(ServerContext *context, const Empty *request, Token *response) {
    if (mPlayerCount == 0)
        response->set_color(Color::BLACK);
    else if (mPlayerCount == 1)
        response->set_color(Color::WHITE);
    else
        response->set_color(Color::NONE);
    mPlayerCount += 1;

    return Status::OK;
}

Status GoServiceImpl::MakeMove(ServerContext *context,
                               const go_service::Move *request,
                               Empty *response) {
    Status st;
    if (mGameState.attemptMove(request->row(), request->col(), true)) {
        st = Status::OK;
    } else {
        st = Status::CANCELLED;
    }

    return st;
}

Status GoServiceImpl::Subscribe(ServerContext *context, const Empty *request,
                                ServerWriter<go_service::Move> *writer) {
    for (const auto& m : mGameState.moves) {
        go_service::Move move;
        move.set_row(m.row);
        move.set_col(m.col);
        move.set_color(m.stone == Stone::BLACK ? go_service::Color::BLACK : go_service::Color::WHITE);
        cout << "Sending Move: row " << m.row << ", col " << m.col << endl;
        if (!writer->Write(move))
            break;
    }
    return Status::OK;
}
