#ifndef LIST_H
#define LIST_H

#include "packet.h"
#include <vector>

class List: public Packet {
public:
    std::vector<Packet *> vec;
    List();
    int compare(Integer *other) override;
    int compare(List *other) override;
};

#endif
