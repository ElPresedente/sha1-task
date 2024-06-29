//
// Created by vova1 on 29.06.2024.
//

#ifndef SHA1_TASK_RESULT_HPP
#define SHA1_TASK_RESULT_HPP

#include <string>
#include <array>
#include <fstream>
#include <iomanip>

struct Result{
    using hash_t = std::array<uint8_t, 20>;

    std::string filename;
    int zero_count;
    hash_t hash_sum;
    std::array<uint8_t, 16> block_data;
};

std::ostream& operator<< (std::ostream& out, const Result& curr);


#endif //SHA1_TASK_RESULT_HPP
