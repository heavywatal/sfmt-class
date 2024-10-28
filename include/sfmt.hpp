#pragma once
#ifndef WTL_SFMT_HPP_
#define WTL_SFMT_HPP_

#include <random>
#include <limits>
#include <type_traits>

#include "SFMT/SFMT.h"

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
namespace wtl {

template <class UIntType>
class sfmt19937_engine {
  public:
    using result_type = UIntType;
    using state_type = sfmt_t;

    static constexpr result_type min() {return 0U;}
    static constexpr result_type max() {return std::numeric_limits<result_type>::max();}
    static constexpr result_type default_seed = std::is_same_v<result_type, uint32_t> ? 1234U : 4321U;

    sfmt19937_engine(): sfmt19937_engine(static_cast<uint32_t>(default_seed)) {}
    explicit sfmt19937_engine(uint32_t s) {seed(s);}
    explicit sfmt19937_engine(uint64_t s) {seed(s);}
    explicit sfmt19937_engine(const state_type& state): state_(state) {}
    sfmt19937_engine(const sfmt19937_engine&) = default;
    sfmt19937_engine(sfmt19937_engine&&) = default;

    result_type operator()() {
      if constexpr (std::is_same_v<result_type, uint32_t>) {
        return sfmt_genrand_uint32(&state_);
      } else {
        return sfmt_genrand_uint64(&state_);
      }
    }

    void seed(uint32_t s) {
        sfmt_init_gen_rand(&state_, s);
    }

    void seed(uint64_t s) {
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

using sfmt19937 = sfmt19937_engine<uint32_t>;
using sfmt19937_64 = sfmt19937_engine<uint64_t>;

inline sfmt19937& sfmt() {
    static sfmt19937 generator(std::random_device{}());
    return generator;
}

inline sfmt19937_64& sfmt64() {
    static sfmt19937_64 generator(std::random_device{}());
    return generator;
}

} // namespace wtl
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

#endif // WTL_SFMT_HPP_
