#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdexcept>
#include <vector>
#include <polyml/pml_node.h>

#include "file.h"

namespace bio {

class container {
private:
    pml::pml_node *m_node;
    std::vector<std::string> split_path(const std::string &path) {
        std::vector<std::string> result;
        std::string current;
        for (size_t i = 0; i < path.length(); ++i) {
            if (path[i] == '/' || path[i] == '\\') {
                if (current.length() > 0) {
                    result.push_back(current);
                }
                current.clear();
            } else {
                current.push_back(path[i]);
            }
        }

        if (current.length() > 0) {
            result.push_back(current);
        }
        return result;
    }

public:
    container() {
        m_node = new pml::pml_node();
    }

    std::vector<char> get(const std::string &fn) {
        std::vector<std::string> blocks = split_path(fn);
        pml::pml_node *c = m_node;
        for (size_t i = 0; i < blocks.size(); ++i) {
            bool found = false;
            for (size_t j = 0; j < c->children_count(); ++j) {
                std::string fn;
                file_t::parse_fn((*c->get_children())[j]->data(), fn);
                if (fn == blocks[i]) {
                    c = (*c->get_children())[j];
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw std::runtime_error("file not found");
            }
        }
        
        file_t result;
        result.parse(c->data());
        return result.content;
    }

    void add(const std::vector<char> &data, const std::string &path) {
        std::vector<std::string> blocks = split_path(path);
        pml::pml_node *c = m_node;
        for (size_t i = 0; i < blocks.size(); ++i) {
            bool found = false;
            for (size_t j = 0; j < c->children_count(); ++j) {
                std::string fn;
                file_t::parse_fn((*c->get_children())[j]->data(), fn);
                if (fn == blocks[i]) {
                    c = (*c->get_children())[j];
                    found = true;
                    break;
                }
            }
            if (!found) {
                pml::pml_node *r = new pml::pml_node();
                file_t f;
                f.file_name = blocks[i];
                r->set_data(f.write());
                c->add_child(r);
                c = r;
            }
        }

        file_t f;
        f.file_name = blocks[blocks.size()-1];
        f.content = data;
        c->set_data(f.write());
    }
};

}
#endif // CONTAINER_H
