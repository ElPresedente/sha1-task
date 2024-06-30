//
// Created by vova1 on 29.06.2024.
//

#include "Application.hpp"

void Application::run() {
    fs::path folder{folder_name};
    if(!fs::exists(folder))
        throw std::runtime_error{"Указанная папка не существует"};

    std::queue<std::future<Result>> task_queue;

    //для красивого цикла по коллекции взял boost.range, но можно было и без него
    for(auto&& file : boost::make_iterator_range(fs::directory_iterator(folder), {})){
        if(!fs::is_regular_file(file))
            continue;
        task_queue.emplace(std::async(Application::process_file, file, time_limit));
        if(task_queue.size() >= threads_num){
            auto result = task_queue.front().get();
            file_out << result << std::endl;
            task_queue.pop();
        }
    }
    while(!task_queue.empty()){
        auto result = task_queue.front().get();
        file_out << result << std::endl;
        task_queue.pop();
    }

}

Application::hash_t Application::sha1(void *mem, size_t size) {
    SHA_CTX sha_ctx;
    hash_t result;
    SHA1_Init(&sha_ctx);
    SHA1_Update(&sha_ctx, mem, size);
    SHA1_Final(result.data(), &sha_ctx);
    return result;
}

Result Application::process_file(const fs::path &file_path, int time_limit) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    Result res;
    res.filename = file_path.filename().generic_string();
    res.zero_count = -1;

    std::vector<uint8_t> data;
    data.reserve(16);
    for(int i = 0; i < 16; i++){
        data.emplace_back(0);
    }

    std::ifstream file{file_path.generic_string()};

    data.insert(data.end(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    auto block_end = data.begin();
    std::advance(block_end, 16);

#ifndef NDEBUG
    int iter_count = 0;
#endif
    for(auto start_time = std::chrono::steady_clock::now(), current_time = start_time;
        std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time) < std::chrono::seconds(time_limit);
        current_time = std::chrono::steady_clock::now()
#ifndef NDEBUG
        , iter_count++
#endif
    ){
        // 1. заполнение блока
        for(int i = 0; i < 16; i++){
            data.at(i) = static_cast<uint8_t>(dis(gen));
        }
        // 2. подсчет хеша
        auto hash_sum = sha1(data.data(), data.size());
        // 3. проверка нулей
        auto zero_count = count_zeros(hash_sum);

        if(zero_count > res.zero_count){
            std::copy(data.begin(), block_end, res.block_data.begin());
            res.zero_count = zero_count;
            res.hash_sum = hash_sum;
        }
    }
#ifndef NDEBUG
    std::cout << res << ", итераций: " << iter_count << std::endl;
#endif
    return res;
}

int Application::count_zeros(const Application::hash_t &hash) {
    int zero_count = 0;
    for(auto byte : hash){
        for(int i = 7; i >= 0; i--){
            if((byte & (1 << i)) == 0){
                zero_count++;
            }
            else{ // эхъ вот бы break(2)
                return zero_count;
            }
        }
    }
    return zero_count;
}
