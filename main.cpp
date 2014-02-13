#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

#include "container.h"

int main() {
    bio::container c;
    std::vector<char> a;
    a.push_back('a');
    std::vector<char> b;
    b.push_back('b');

    c.add(a, "files/a/aa");
    c.add(b, "files/b/bb");

    std::vector<char> aa, bb;
    aa = c.get("files/a/aa");
    bb = c.get("files/b/bb");

    assert(aa == a && "BAD A");
    assert(bb == b && "BAD B");

    return 0;
}
