#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"

namespace server_side
{
    template <class P, class S> class Server {

    public:
        virtual void open(int port, ClientHandler<P, S>* c) = 0;
        virtual void closeServer(ClientHandler<P, S>* c) = 0;
    };
}

#endif //MILESTONE2_SERVER_H
