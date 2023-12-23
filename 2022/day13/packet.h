#ifndef PACKET_H
#define PACKET_H

class Integer;
class List;

class Packet {
public:
    virtual int compare(Integer *other) = 0;
    virtual int compare(List *other) = 0;
};

#endif
