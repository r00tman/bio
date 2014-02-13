#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>

#include "stream.h"

namespace bio {

namespace stream_utils {
static std::vector<char> load_binary(in_stream &in) {
    std::vector<char> res;
    const size_t BSIZE = 1024*32;
    std::vector<char> buffer(BSIZE);
    size_t lastcnt = -1;
    while (in.good() && lastcnt) {
        size_t cnt = in.read(buffer, BSIZE);
        std::copy(buffer.begin(), buffer.begin()+cnt, std::back_inserter(res));
        lastcnt = cnt;
    }
    return res;
}

static void copy(in_stream &in, out_stream &out) {
    const size_t BSIZE = 1024*32;
    std::vector<char> buffer(BSIZE);
    size_t lastcntin = -1;
    while (in.good() && out.good() && lastcntin) {
        size_t cntin = in.read(buffer, BSIZE);
        size_t cntout = 0;
        while (cntout < cntin && out.good()) {
            cntout += out.write(buffer, BSIZE);
        }
        lastcntin = cntin;
    }
}
}

}

#endif // STREAM_UTILS_H
