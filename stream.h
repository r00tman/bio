#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <cstdlib>

namespace bio {

struct stream {
    virtual ~stream() {
    }

    virtual bool good() {
        return false;
    }
};

struct in_stream : public stream {
    virtual ~in_stream() {
    }

    virtual size_t read(std::vector<char> &buff, size_t bs) {
        return 0;
    }
};

struct out_stream : public stream {
    virtual ~out_stream() {
    }

    virtual size_t write(const std::vector<char> &buff, size_t bs) {
        return 0;
    }

    virtual void flush() {
    }
};

}

#endif //STREAM_H
