#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

#include <vector>

#include "stream.h"
#include "common/basic_logger.h"

namespace bio {

struct byte_in_stream : public in_stream {
private:
    std::string m_data;
    size_t m_cursor;

public:
    byte_in_stream() :
        m_cursor(0) {
    }

    byte_in_stream(const std::string &data) {
        m_data = data;
        m_cursor = 0;
    }

    virtual ~byte_in_stream() {
    }

    virtual bool good() {
        return m_cursor < m_data.size();
    }

    virtual size_t read(std::vector<char> &buff, size_t bs) {
        buff.resize(bs);
        size_t cnt = 0;
        for (cnt = 0; cnt < bs && m_cursor < m_data.size(); ++cnt, ++m_cursor) {
            buff[cnt] = m_data[m_cursor];
        }
        return cnt;
    }
};

struct byte_out_stream : public out_stream {
private:
    std::vector<char> m_data;

public:
    byte_out_stream() {
    }

    virtual ~byte_out_stream() {
    }


    virtual bool good() {
        return true;
    }

    virtual size_t write(const std::vector<char> &buff, size_t bs) {
        m_data.resize(m_data.size() + bs);
        for (size_t i = 0; i < bs; ++i) {
            m_data[m_data.size()-bs] = buff[i];
        }

        return bs;
    }

    virtual void flush() {
    }
};

}

#endif // BYTE_STREAM_H
