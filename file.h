#ifndef FILE_H
#define FILE_H
#include <cstdlib>

namespace bio {

struct file_t {
private:
    static
    size_t read_size_t(const std::vector<char> &raw, size_t &cursor) {
        if (raw.size() < cursor + sizeof(size_t)) {
            throw std::runtime_error("corrupted size_t");
        }
        union {
            size_t res;
            char a[sizeof(size_t)];
        };
        for (size_t i = 0; i < sizeof(size_t); ++i) {
            a[i] = raw[i+cursor];
        }
        cursor += sizeof(size_t);
        return res;
    }

    static
    void write_size_t(std::vector<char> &raw, size_t val) {
        union {
            size_t a;
            char res[sizeof(size_t)];
        };
        a = val;
        for (size_t i = 0; i < sizeof(size_t); ++i) {
            raw.push_back(res[i]);
        }
    }

public:
    std::string file_name;
    std::vector<char> content;

    static
    size_t parse_fn(const std::vector<char> &raw, std::string &result) {
        size_t cursor = 0;
        size_t fn_size = read_size_t(raw, cursor);
        if (raw.size() < cursor + fn_size) {
            throw std::runtime_error("corrupted file name");
        }
        result.assign(raw.begin()+cursor, raw.begin()+cursor+fn_size);
        cursor += fn_size;
        return cursor;
    }

    void parse(const std::vector<char> &raw) {
        size_t cursor = 0;
        cursor += parse_fn(raw, file_name);
        size_t content_size = read_size_t(raw, cursor);
        if (raw.size() < cursor + content_size) {
            throw std::runtime_error("corrupted file content");
        }
        content.assign(raw.begin()+cursor, raw.begin()+cursor+content_size);
    }

    std::vector<char> write() {
        std::vector<char> result;
        write_size_t(result, file_name.size());
        for (size_t i = 0; i < file_name.size(); ++i) {
            result.push_back(file_name[i]);
        }

        write_size_t(result, content.size());

        for (size_t i = 0; i < content.size(); ++i) {
            result.push_back(content[i]);
        }
        return result;
    }
};

}

#endif // FILE_H
