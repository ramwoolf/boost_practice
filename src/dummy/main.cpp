#include <iostream>
#include <fstream>

template <typename C = char, typename T = std::char_traits<char>>
void Process(std::basic_istream<C, T>& in, std::basic_ostream<C, T>& out) {
    out << in.rdbuf();
}

int main(int argc, char const **argv) {
    std::fstream in, out;
    if (argc > 1) {
        in.open(argv[1], std::ios::in | std::ios::binary);
    }
    if (argc > 2) {
        out.open(argv[2], std::ios::out | std::ios::binary);
    }

    Process(in.is_open() ? in : std::cin, out.is_open() ? out : std::cout);
    return 0;
}