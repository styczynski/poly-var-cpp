
#define USE_DEFAULT_STRING_BEHAVIOUR
#define NAMESPACE_VAR_BEGIN__ namespace variable {
#define NAMESPACE_VAR_END__ };

#include <cmath>
#include "var_math_decl.h"

NAMESPACE_VAR_BEGIN__

inline static var var_math::abs(var x) {
  const vartypeid t = x.getType();
  return var(  std::abs((double)x)  ).castToType(t);
}

inline static var var_math::sqrt(var x) {
  const vartypeid t = x.getType();
  return var(  std::sqrt((double)x)  ).castToType(t);
}

inline static var var_math::pow(var x, var y) {
  return var::Null;
}

inline static var var_math::sin(var x) {
  const vartypeid t = x.getType();
  return var(  std::sin((double)x)  ).castToType(t);
}

inline static var var_math::cos(var x) {
  const vartypeid t = x.getType();
  return var(  std::cos((double)x)  ).castToType(t);
}

inline static var var_math::neg(var x) {
  return (-x);
}

NAMESPACE_VAR_END__
