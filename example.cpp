#include <iostream>
#include <random>

#define HAVE_SSE2
#define DSFMT_MEXP 19937
#define DSFMT_DO_NOT_USE_OLD_NAMES
#include <dSFMT.h>
//#define SFMT_MEXP 19937
//#include <SFMT.h>

int main() {
    std::random_device seeder;
    dsfmt_t state;
    dsfmt_init_gen_rand(&state, seeder());

    // real [0, 1)
    double x = dsfmt_genrand_close_open(&state);

    // integer [0, 2^32 - 1]
    unsigned int y = dsfmt_genrand_uint32(&state);

    std::cout << x << std::endl;
    std::cout << y << std::endl;
    return 0;
}
