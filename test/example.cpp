#include <iostream>
#include <random>

#include <sfmt.hpp>

void std_mt() {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::normal_distribution<double> normal(0.0, 1.0);
    for (size_t i=0; i<3; ++i) {
        std::cout << normal(engine) << std::endl;
    }
}

void wtl_sfmt() {
    std::random_device seeder;
    wtl::sfmt19937 engine(seeder());
    std::normal_distribution<double> normal(0.0, 1.0);
    for (size_t i=0; i<3; ++i) {
        std::cout << normal(engine) << std::endl;
    }
}

void predefined_global() {
    std::normal_distribution<double> normal(0.0, 1.0);
    for (size_t i=0; i<3; ++i) {
        std::cout << normal(wtl::sfmt()) << std::endl;
    }
}

int main() {
    std_mt();
    wtl_sfmt();
    predefined_global();
    return 0;
}
