#include "var"

#ifndef _VAR_STL_CONVERSIONS_CPP
#define _VAR_STL_CONVERSIONS_CPP

#include <set>

NAMESPACE_VAR_BEGIN__

template<>
template<typename T>
class var::conversion<set<T>> {
  public:
    static var toVar(set<T> c) {
      std::vector<T> output(c.size());
      std::copy(c.begin(), c.end(), output.begin());
      return var(output);
    }
    static set<T> fromVar(var v) {
      std::vector<T> input = v.toArray();
      std::set<T> output(input.begin(), input.end());
      return output;
    }
};


NAMESPACE_VAR_END__

#endif
