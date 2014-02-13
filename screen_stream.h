#ifndef SCREEN_STREAM_H
#define SCREEN_STREAM_H

#include <iostream>
#include "stream.h"

namespace bio {

struct screen_out_stream : public out_stream {
private:
    bool m_is_error;

public:
    virtual ~screen_out_stream() {
    }

    screen_out_stream(bool is_error = false) :
        m_is_error(is_error) {
    }

    virtual bool good() {
        if (m_is_error && std::cerr) {
            return true;
        } else if (!m_is_error && std::cout) {
            return true;
        }
        return false;
    }

    virtual size_t write(const std::vector<char> &buff, size_t bs) {
        std::ostream *str = &(std::cout);
        if (m_is_error) {
            str = &(std::cerr);
        }

        str->write(&(*buff.begin()), bs);

        if (good()) {
            return bs;
        } else {
            return 0;
        }
    }

    virtual void flush() {
        if (m_is_error) {
            std::cerr.flush();
        } else {
            std::cout.flush();
        }
    }

};

}

#endif // SCREEN_STREAM_H
