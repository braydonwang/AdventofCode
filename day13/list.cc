#include "list.h"
#include "integer.h"
using namespace std;

List::List(): Packet{} {}

int List::compare(Integer *other) {
    List *newList = new List();
    newList->vec.push_back(other);
    return this->compare(newList);
}

int List::compare(List *other) {
    int ind = 0;
    vector<Packet *> othervec = other->vec;
    while (ind < vec.size() || ind < othervec.size()) {
        if (ind >= vec.size()) {
            return 1;
        } else if (ind >= othervec.size()) {
            return 2;
        } else {
            int num;
            if (dynamic_cast<Integer *>(othervec[ind])) {
                num = vec[ind]->compare(dynamic_cast<Integer *>(othervec[ind]));
            } else {
                num = vec[ind]->compare(dynamic_cast<List *>(othervec[ind]));
            }
            if (num == 1 || num == 2) {
                return num;
            }
        }
        ind++;
    }
    return 3;
}
