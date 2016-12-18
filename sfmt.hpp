// -*- mode: c++; coding: utf-8 -*-
#pragma once
#ifndef WTL_SFMT_HPP_
#define WTL_SFMT_HPP_

#include <limits>

#define HAVE_SSE2
#define SFMT_MEXP 19937
#include "SFMT/SFMT.h"

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
namespace wtl {
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

class sfmt19937 {
  public:
    typedef uint32_t result_type;
    typedef sfmt_t state_type;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}

    // constructors
    explicit sfmt19937(const result_type s) {seed(s);}
    explicit sfmt19937(const state_type& state): state_(state) {}
    sfmt19937(const sfmt19937&) = delete;

    // [0, 2^32-1]
    result_type operator()() {
        return sfmt_genrand_uint32(&state_);
    }

    // [0.0, 1.0)
    double canonical() {
        return sfmt_genrand_real2(&state_);
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
} // namespace wtl
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

#endif /* WTL_SFMT_HPP_ */
