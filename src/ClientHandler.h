#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

using namespace std;

template <class P, class S> class ClientHandler {

public:
    virtual void handleClient(int socket) = 0;
};

#endif //MILESTONE2_CLIENTHANDLER_H
