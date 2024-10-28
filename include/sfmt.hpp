#pragma once
#ifndef WTL_SFMT_HPP_
#define WTL_SFMT_HPP_

#include <random>
#include <limits>

#include "SFMT/SFMT.h"

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
namespace wtl {
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

class sfmt19937 {
  public:
    using result_type = uint32_t;
    using state_type = sfmt_t;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}
    static constexpr result_type default_seed = 1234U;

    // constructors
    explicit sfmt19937(result_type s=default_seed) {seed(s);}
    explicit sfmt19937(const state_type& state): state_(state) {}
    sfmt19937(const sfmt19937&) = default;
    sfmt19937(sfmt19937&&) = default;

    // [0, 2^32-1]
    result_type operator()() {
        return sfmt_genrand_uint32(&state_);
    }

    void seed(result_type s) {
        sfmt_init_gen_rand(&state_, s);
    }

    void discard(unsigned long long n) {
        for (; n != 0ULL; --n) {(*this)();}
    }

    const state_type& getstate() const {return state_;}
    void setstate(const state_type& state) {state_ = state;}

  private:
    state_type state_;
};


class sfmt19937_64 {
  public:
    using result_type = uint64_t;
    using state_type = sfmt_t;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}
    static constexpr result_type default_seed = 4321U;

    // constructors
    explicit sfmt19937_64(uint32_t s=static_cast<uint32_t>(default_seed)) {seed(s);}
    explicit sfmt19937_64(result_type s) {seed(s);}
    explicit sfmt19937_64(const state_type& state): state_(state) {}
    sfmt19937_64(const sfmt19937_64&) = default;
    sfmt19937_64(sfmt19937_64&&) = default;

    // [0, 2^64-1]
    result_type operator()() {
        return sfmt_genrand_uint64(&state_);
    }

    void seed(uint32_t s) {
        sfmt_init_gen_rand(&state_, s);
    }

    void seed(result_type s) {
        sfmt_init_by_array(&state_, reinterpret_cast<uint32_t*>(&s), 2);
    }

    void discard(unsigned long long n) {
        for (; n != 0ULL; --n) {(*this)();}
    }

    const state_type& getstate() const {return state_;}
    void setstate(const state_type& state) {state_ = state;}

  private:
    state_type state_;
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

inline sfmt19937& sfmt() {
    static sfmt19937 generator(std::random_device{}());
    return generator;
}

inline sfmt19937_64& sfmt64() {
    static sfmt19937_64 generator(std::random_device{}());
    return generator;
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
} // namespace wtl
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

#endif /* WTL_SFMT_HPP_ */
