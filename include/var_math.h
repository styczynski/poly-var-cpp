
#define USE_DEFAULT_STRING_BEHAVIOUR
#define NAMESPACE_VAR_BEGIN__ namespace variable {
#define NAMESPACE_VAR_END__ };

#include <cmath>
#include "var_math_decl.h"

NAMESPACE_VAR_BEGIN__

inline var var_math::abs(var x) {
  const var::vartypeid t = x.getType();
  return var(  std::abs((double)x)  ).asType(t);
}

inline var var_math::sqrt(var x) {
  const var::vartypeid t = x.getType();
  return var(  std::sqrt((double)x)  ).asType(t);
}

inline var var_math::pow(var x, var y) {
  return var::Null;
}

inline var var_math::sin(var x) {
  const var::vartypeid t = x.getType();
  return var(  std::sin((double)x)  ).asType(t);
}

inline var var_math::cos(var x) {
  const var::vartypeid t = x.getType();
  return var(  std::cos((double)x)  ).asType(t);
}

inline var var_math::neg(var x) {
  return (-x);
}

NAMESPACE_VAR_END__
