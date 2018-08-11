#include <sfmt.hpp>

#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>

template <class URBG> inline
void check_output(URBG& generator, const std::string path) {
    std::ifstream ifs(path);
    ifs.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    std::string buffer;
    for (int i=0; i<3; ++i) {
        std::getline(ifs, buffer);
    }
    uint64_t known_value;
    for (int i=0; i<1000; ++i) {
        ifs >> known_value;
        const auto x = generator();
        if (x != known_value) {
            std::ostringstream oss;
            oss << "\nOutput is different from known value:\n"
                << x << " != " << known_value;
            throw std::runtime_error(oss.str());
        }
    }
}

int main() {
    wtl::sfmt19937 engine32;
    check_output(engine32, "SFMT/SFMT.19937.out.txt");
    wtl::sfmt19937_64 engine64;
    check_output(engine64, "SFMT/SFMT.19937.64.out.txt");
    return 0;
}
