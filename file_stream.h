#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include <fstream>
#include <iostream>
#include <string>

#include "stream.h"
#include "basic_logger.h"

namespace bio {

struct file_in_stream : public in_stream {
private:
    std::ifstream *m_stream;

public:
    file_in_stream() :
        m_stream(NULL) {
    }

    file_in_stream(const std::string &fn) {
        m_stream = NULL;
        open(fn);
    }

    virtual ~file_in_stream() {
        if (m_stream != NULL) {
            m_stream->close();
            delete m_stream;
        }
    }

    void open(const std::string &fn) {
        if (m_stream != NULL) {
            m_stream->close();
            delete m_stream;
        }
        m_stream = new std::ifstream(fn.c_str(),
            std::ios_base::in|std::ios_base::binary);

        if (!(*m_stream)) {
            log_error("couldn't open file for reading: " + fn);
        }
    }

    virtual bool good() {
        if (m_stream == NULL) {
            return false;
        }
        return (*m_stream);
    }

    virtual size_t read(std::vector<char> &buff, size_t bs) {
        buff.resize(bs);
        if (m_stream == NULL) {
            return 0;
        }
        return m_stream->readsome(&(*buff.begin()), bs);
    }
};

struct file_out_stream : public in_stream, out_stream {
private:
    std::ofstream *m_stream;
public:
    file_out_stream() :
        m_stream(NULL) {
    }

    file_out_stream(const std::string &fn) {
        m_stream = NULL;
        open(fn);
    }

    virtual ~file_out_stream() {
        if (m_stream != NULL) {
            m_stream->close();
            delete m_stream;
        }
    }

    void open(const std::string &fn) {
        if (m_stream != NULL) {
            m_stream->close();
            delete m_stream;
        }
        m_stream = new std::ofstream(fn.c_str(),
            std::ios_base::out|std::ios_base::binary);
        if (!(*m_stream)) {
            log_error("couldn't open file for writing: " + fn);
        }
    }

    virtual bool good() {
        if (m_stream == NULL) {
            return false;
        }
        return (*m_stream);
    }

    virtual size_t write(const std::vector<char> &buff, size_t bs) {
        if (m_stream == NULL) {
            return 0;
        }
        m_stream->write(&(*buff.begin()), bs);
        if (good()) {
            return bs;
        } else {
            return 0;
        }
    }

    virtual void flush() {
        if (m_stream) {
            m_stream->flush();
        }
    }
};

}

#endif // FILE_STREAM_H
