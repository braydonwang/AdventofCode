#include "integer.h"
#include "list.h"

Integer::Integer(int num): Packet{}, num{num} {}

int Integer::compare(Integer *other) {
    if (num < other->num) {
        return 1;
    } else if (num > other->num) {
        return 2;
    } else {
        return 3;
    }
}

int Integer::compare(List *other) {
    List *newList = new List();
    newList->vec.push_back(this);
    return newList->compare(other);
}
