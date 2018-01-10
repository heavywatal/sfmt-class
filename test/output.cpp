#include <sfmt.hpp>

#include <stdexcept>
#include <fstream>
#include <string>

template <class URBG> inline
void check_output(const std::string path) {
    URBG generator;
    std::ifstream ifs(path);
    ifs.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    std::string buffer;
    for (int i=0; i<3; ++i) {
        std::getline(ifs, buffer);
    }
    uint64_t known_value;
    for (int i=0; i<1000; ++i) {
        ifs >> known_value;
        if (generator() != known_value) {
            throw std::runtime_error("Output is different from known value");
        }
    }
}

int main() {
    check_output<wtl::sfmt19937>("SFMT/SFMT.19937.out.txt");
    check_output<wtl::sfmt19937_64>("SFMT/SFMT.19937.64.out.txt");
    return 0;
}
