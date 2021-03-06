#include "var"

#ifndef _VAR_OPERATOR_TOOLKIT_CPP
#define _VAR_OPERATOR_TOOLKIT_CPP

NAMESPACE_VAR_BEGIN__

	#undef declareOperatorOverload
	#define declareOperatorOverload(OPERATOR, TYPENAME) \
		inline var operator OPERATOR (TYPENAME a, var b) { \
			return var(a) OPERATOR b; \
		}
		/*inline var operator OPERATOR (var a, TYPENAME b) { \
			return a OPERATOR var(b); \
		}*/

	#undef declareOperatorOverloadT
	#define declareOperatorOverloadT(TEMPLATE, OPERATOR, TYPENAME) \
		template <typename TEMPLATE> \
		inline var operator OPERATOR (TYPENAME a, var b) { \
			return var(a) OPERATOR b; \
		}
		/*template <typename TEMPLATE> \
		inline var operator OPERATOR (var a, TYPENAME b) { \
			return a OPERATOR var(b); \
		}*/



	/*template <typename T>
	inline var operator-(T a, var b) {
		return var(a)-b;
	}

	template <typename T>
	inline var operator*(T a, var b) {
		return var(a)*b;
	}

	template <typename T>
	inline var operator/(T a, var b) {
		return var(a)/b;
	}

	template <typename T>
	inline var operator%(T a, var b) {
		return var(a)%b;
	}

	template <typename T>
	inline var operator&(T a, var b) {
		return var(a)&b;
	}

	template <typename T>
	inline var operator|(T a, var b) {
		return var(a)|b;
	}

	template <typename T>
	inline var operator^(T a, var b) {
		return var(a)^b;
	}


	template <typename T>
	inline var operator+(var a, T b) {
		return a+var(b);
	}

	template <typename T>
	inline var operator-(var a, T b) {
		return a-var(b);
	}

	template <typename T>
	inline var operator*(var a, T b) {
		return a*var(b);
	}

	template <typename T>
	inline var operator/(var a, T b) {
		return a/var(b);
	}

	template <typename T>
	inline var operator%(var a, T b) {
		return a%var(b);
	}

	template <typename T>
	inline var operator|(var a, T b) {
		return a|var(b);
	}

	template <typename T>
	inline var operator&(var a, T b) {
		return a&var(b);
	}

	template <typename T>
	inline var operator^(var a, T b) {
		return a^var(b);
	}*/

	declareOperatorOverload(<<, short);
	declareOperatorOverload(<<, int);
	declareOperatorOverload(<<, long long);
	declareOperatorOverload(<<, bool);
	declareOperatorOverload(<<, char);
	declareOperatorOverload(<<, string);
	declareOperatorOverloadT(T, <<, vector<T>);
	declareOperatorOverload(>>, short);
	declareOperatorOverload(>>, int);
	declareOperatorOverload(>>, long long);
	declareOperatorOverload(>>, bool);
	declareOperatorOverload(>>, char);
	declareOperatorOverload(>>, string);
	declareOperatorOverloadT(T, >>, vector<T>);

	declareOperatorOverload(&&, short);
	//declareOperatorOverload(&&, int);
	declareOperatorOverload(&&, long long);
	declareOperatorOverload(&&, bool);
	declareOperatorOverload(&&, char);
	declareOperatorOverload(&&, string);
	declareOperatorOverloadT(T, &&, vector<T>);
	declareOperatorOverload(||, short);
	declareOperatorOverload(||, int);
	declareOperatorOverload(||, long long);
	declareOperatorOverload(||, bool);
	declareOperatorOverload(||, char);
	declareOperatorOverload(||, string);
	declareOperatorOverloadT(T, ||, vector<T>);

	inline ostream& operator<<(ostream &out, var v) {
		out<<v.toReadableString();
		return out;
	}

	inline istream& operator>>(istream &in, var& v) {
		string str;
		cin>>str;
		const var::vartypeid type = v.getType();
		v = str;
		v.castToType(type);
		return in;
	}


	/*
	//TODO: Some errors on g++ gcc version 5.4.0 20160603 (release) (PLD-Linux)

	var operator"" _var( const char* value, unsigned int len ){
  		return var(string(value));
	}
	*/

	var operator"" _var( long double value ){
  		return var((double)value);
	}

	var operator"" _var( unsigned long long int value ){
  		return var((long long)value);
	}

NAMESPACE_VAR_END__

#endif
