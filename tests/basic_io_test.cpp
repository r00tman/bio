#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "../file_stream.h"

using namespace std;
using namespace bio;

void bio_test() {
    file_out_stream out("./test");
    vector<char> d;
    d.push_back('c');

    out.write(d, d.size());
    out.flush();

    file_in_stream in("./test");
    vector<char> i;
    in.read(i, 1);

    assert(d == i);
}

int main() {
    bio_test();
    return 0;
}
