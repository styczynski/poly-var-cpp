#include "var"
#include "var_math"

#ifndef _VAR_MATH_CPP
#define _VAR_MATH_CPP


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
  const var::vartypeid t = var::getGreaterPrecisionType(x.getType(), y.getType());
  return var(  std::pow((double)x, (double)y)  ).asType(t);
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

#endif
