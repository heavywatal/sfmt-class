#include <iostream>
#include <random>

#include <sfmt.hpp>

int main() {
    std::random_device seeder;
    std::normal_distribution<double> dist(0.0, 1.0);

    // local instance
    // std::mt19937 rng(seeder());
    wtl::sfmt19937 rng(seeder());
    for (size_t i=0; i<5; ++i) {
        std::cout << dist(rng) << std::endl;
    }

    // global instance
    wtl::sfmt().seed(seeder());
    for (size_t i=0; i<5; ++i) {
        std::cout << dist(wtl::sfmt()) << std::endl;
    }
    return 0;
}
