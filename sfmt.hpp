// -*- mode: c++; coding: utf-8 -*-
#pragma once
#ifndef WTL_SFMT_HPP_
#define WTL_SFMT_HPP_

#include <random>
#include <limits>

#define HAVE_SSE2
#define SFMT_MEXP 19937
#include "SFMT/SFMT.h"

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
namespace wtl {
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

namespace {
    union bits64_t {
        uint64_t as_uint64_t;
        uint32_t as_uint32_t[2];
        double as_double;
    };

    // Use 52 bits to make double [0.0, 1.0)
    inline double as_canonical(uint64_t x) {
        bits64_t bits = {(x >> 2) | 0x3ff0'0000'0000'0000};
        return bits.as_double - 1.0;
    }
}

class sfmt19937 {
  public:
    typedef uint32_t result_type;
    typedef sfmt_t state_type;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}
    static constexpr result_type default_seed = 5489U;

    // constructors
    explicit sfmt19937(const result_type s=default_seed) {seed(s);}
    explicit sfmt19937(const state_type& state): state_(state) {}
    sfmt19937(const sfmt19937&) = default;
    sfmt19937(sfmt19937&&) = default;

    // [0, 2^32-1]
    result_type operator()() {
        return sfmt_genrand_uint32(&state_);
    }

    // [0.0, 1.0)
    double canonical() {
        return std::generate_canonical<double, std::numeric_limits<double>::digits>(*this);
    }
    // possible implementation
    double _canonical() {
        bits64_t bits = {.as_uint32_t = {this->operator()(), this->operator()()}};
        return as_canonical(bits.as_uint64_t);
    }

    void seed(const result_type s) {
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
    typedef uint64_t result_type;
    typedef sfmt_t state_type;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}
    static constexpr result_type default_seed = 5489U;

    // constructors
    explicit sfmt19937_64(const result_type s=default_seed) {seed(s);}
    explicit sfmt19937_64(const state_type& state): state_(state) {}
    sfmt19937_64(const sfmt19937_64&) = default;
    sfmt19937_64(sfmt19937_64&&) = default;

    // [0, 2^64-1]
    result_type operator()() {
        return sfmt_genrand_uint64(&state_);
    }

    // [0.0, 1.0)
    double canonical() {
        return std::generate_canonical<double, std::numeric_limits<double>::digits>(*this);
    }
    // possible implementation
    double _canonical() {
        return as_canonical(this->operator()());
    }

    void seed(const result_type s) {
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
