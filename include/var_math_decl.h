
#ifndef _VAR_MATH_H
#define _VAR_MATH_H

NAMESPACE_VAR_BEGIN__

class var_math {
  public:
    inline static var abs(var x);
    inline static var sqrt(var x);
    inline static var pow(var x, var y);
    inline static var sin(var x);
    inline static var cos(var x);
    inline static var neg(var x);

};

NAMESPACE_VAR_END__
