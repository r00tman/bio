#include "basic_logger.h"

#include "media/file_stream.h"

basic_logger clogger;

basic_logger::basic_logger() {
}

basic_logger::~basic_logger() {
}

void basic_logger::add_log_file(const std::string &name) {
    file_out_stream *output = new file_out_stream();

    if ("" != name) {
        output->open(name);
        m_output.push_back(output);
    }
}

void basic_logger::add_log_stream(out_stream *stream) {
    m_output.push_back(stream);
}

void basic_logger::write(const std::string &msg) {
    for (size_t i = 0; i < m_output.size(); i++) {
        if (m_output[i] != NULL) {
            m_output[i]->write(std::vector<char>(msg.begin(), msg.end()), msg.size());
            m_output[i]->flush();
        }
    }
}

void basic_logger::write_ln(const std::string &msg) {
    write(msg);
    write("\n");
}
