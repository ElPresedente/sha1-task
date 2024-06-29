//
// Created by vova1 on 29.06.2024.
//

#include "Result.hpp"

std::ostream& operator<<(std::ostream& out, const Result& curr) {
    out << "Файл: " << curr.filename << ", нулей: " << curr.zero_count
        << ", SHA1: ";
    for(auto byte : curr.hash_sum){
        out << std::setw(2) << std::setfill('0') << std::hex << (int)byte;
    }
    out << ", доп блок: ";
    for(auto byte : curr.block_data){
        out << std::setw(2) << std::setfill('0') << std::hex << (int)byte;
    }
    return out;
}
