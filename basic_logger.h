#ifndef BASIC_LOGGER_H
#define BASIC_LOGGER_H

#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <cstdio>
#include <vector>

#include "media/stream.h"

template<class T>
static std::string to_str(T t) {
    std::ostringstream str;
    str << t;
    return str.str();
}

#define log_header  (to_str(__FILE__) + "[" + to_str(__LINE__) + "] ")
#define log_info(x)    clogger.write_ln_value("[I] ", (x))
#define log_warning(x) clogger.write_ln_value("[W] ", (x))
#define log_error(x)   clogger.write_ln_value("[E] ", (x))
#define log_fatal(x)   clogger.write_ln_value("[F] ", (x))

class basic_logger {
public:
    basic_logger();
    ~basic_logger();

    void add_log_file(const std::string &name);
    void add_log_stream(out_stream *stream);
    void write(const std::string &msg);
    void write_ln(const std::string &msg);
    template <class T>
    void write_value(const std::string &prefix, T val) {
        write(prefix);
        std::ostringstream str;
        str << val;
        write(str.str());
    }

    template <class T>
    void write_ln_value(const std::string &prefix, T val) {
        write_value(prefix, val);
        write("\n");
    }

private:
    std::vector<out_stream*> m_output;
};

extern basic_logger clogger;

#endif // BASIC_LOGGER_H
