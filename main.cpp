#include <iostream>
#include <argparse/argparse.hpp>

#include "Application.hpp"

int main(int argc, char** argv) {
    argparse::ArgumentParser program{"sha1_task", "0.0.1"};

    program.add_argument("folder")
        .required()
        .help("входная директория, в которой располагаются файлы")
        .nargs(1);
    program.add_argument("--threads")
        .help("количество используемых потоков выполнения")
        .default_value(4)
        .nargs(1)
        .scan<'i', int>();
    program.add_argument("--time-limit")
        .help("время в секундах для расчета блока на каждый файл")
        .default_value(4)
        .nargs(1)
        .scan<'i', int>();
    program.add_argument("--output")
        .help("имя файла, в котором будут записаны результаты подбора")
        .default_value(std::string{"out.txt"})
        .nargs(1);

    try {
        program.parse_args(argc, argv);   // Example: ./main --input_files config.yml System.xml
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    auto folder = program.get<std::string>("folder");
    auto threads_num = program.get<int>("--threads");
    auto time_limit = program.get<int>("--time-limit");
    auto output_file = program.get<std::string>("--output");

    Application app{folder, output_file, threads_num, time_limit};
    try{
        app.run();
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(1);
    }
    return 0;
}
