//
// Created by vova1 on 29.06.2024.
//

#ifndef SHA1_TASK_APPLICATION_HPP
#define SHA1_TASK_APPLICATION_HPP

#include <string>
#include <utility>
#include <array>
#include <cstdint>
#include <queue>
#include <future>
#include <fstream>
#include <random>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <openssl/sha.h>

#include "Result.hpp"

namespace fs = boost::filesystem;

class Application {
public:
    using hash_t = Result::hash_t;

    Application(std::string scan_folder, std::string output_file, int threads_num, int time_limit) :
        folder_name(std::move(scan_folder)), output_file(std::move(output_file)), threads_num(threads_num),
        time_limit(time_limit), file_out(std::ofstream{output_file})
    {};

    void run();
private:
    static hash_t sha1(void* mem, size_t size);

    static Result process_file(const fs::path& file);



    std::ofstream file_out;

    const std::string folder_name;
    const std::string output_file;
    const int threads_num;
    const int time_limit;
};


#endif //SHA1_TASK_APPLICATION_HPP
