#ifndef LIST_UTIL_H
#define LIST_UTIL_H

#include <string>
#include <vector>

namespace list_util
{
    void generate_random_list(const std::string& filename, std::vector<int>& list, int low = 0, int high = 1e6, uint count = 1e6);
    void read_list(const std::string& filename, std::vector<int>& list);
};

#endif // LIST_UTIL_H
