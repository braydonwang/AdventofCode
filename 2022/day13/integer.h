#ifndef INTEGER_H
#define INTEGER_H

#include "packet.h"

class Integer: public Packet {
public:
    int num;
    Integer(int num);
    int compare(Integer *other) override;
    int compare(List *other) override;
};

#endif
