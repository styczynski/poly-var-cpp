/*

 C/C++ Var Library (1.0v)
 Version 1.0 Alpha
 2014-11-10

 Styczynsky Digital Systems property
 All rights are reserved


 Library supports the following data types:
 	* int
 	* long long
 	* char
 	* bool
 	* string
 	* float
 	* double
 	* arrays of any primitive type or vars
 	    (also bracket initializers)

 Partially supports (they're not built-in types, but are supported):
  	* short


 Basic operation type calculation rules:

	<anything> [operator] <anything> gives as the result data of type of greater
		precision from this given to operator as arguments

		E.g. <double> + <long long> gives <double>
		E.g  <int> + <float> gives <float>
	 	E.g. <int> * <bool> gives <int>

	<string> + <anything> always gives <string>
		(strings are concatenaded)

	<string> [any operator except +] <string> always gives double as the result
		(strings are converted into doubles then the math expression is beiing calculated)

 Rading/writing data from/to standard input/output:

 	Using scanfs and printfs:
 		var x;
 		scanf("%d", (int*)x);     //To load int
 		scanf("%d", (bool*)x);    //To load bool
 		scanf("%lf", (double*)x);  //To read double

 		printf("%d", (int)x);     //To write int
 		printf("%d", (bool)x);    //To write bool
 		printf("%lf", (double)x);  //To write double

 	Using cins/couts:
 		var x;
 		cin>>x.castToInt();    //To read int
 		cin>>x.castToBool();      //To read bool
 		cin>>x.castToDouble();    //To read double

 		cout<<x.toInt();          //To write int
 		cout<<x.toBool();         //To write bool
 		cout<<x.toDouble();       //To write double


 	Definition of non trivial operations:
 		<string> + <string> means string concatenation
 		<string> * <string> means math multiplication of numbers represented by the given strings.
 			Operators like -, %, / behaves on similar way.
		<array> / (anything) gives you array divided by specified element (return type will be array of arrays)
 			E.g. {1, 2, 3, 4, 3, 5} / 3 = { {1, 2}, {4}, {5} }
		<array> + (anything) means pushing new element on array
			E.g. {1, 2} + 3 = {1, 2, 3}
		<array> - (anything) means element removal from array
			E.g. {1, 2} - 3 = {1, 2}
			E.g. {1, 2} - 2 = {1}
		<array> * (anything) is not definied as well as %, * and similar operators

	Use castTo... methods family to convert var types:
		E.g. castToString converts var value to its string representation

	Use asInt, asFloat, asDouble methods family to get converted vars values
	without actualy modyfying their values.

	Use toString, toDouble, toFloats methods family to convert vars into
	C/C++ builtin types.
	To array returns vector<var> representation of var array.

	Use getType() to get var::vartypeid representation of var current type.
	Then you can use castToType(var::vartypeid) to cast var to desired type.
	There's also castToTypeOf(var) method which converts var to type of the given var.


 Var's string representation

	You can use method toString() to get string representation of the specified variable.
	You can also use c_str() which returns const char* (C-style string) representation of the var.


 Built-in types conversion

 	You can easily convert data using standard C cast style operators instead of calling toString(), toDouble() etc. methods:
 		E.g. (string)var works as var.toString()
 		E.g. (long long)var works as var.toLongLong()
 		E.g. (int)var works as var.toInt()

 Pointer conversion

 	The operators for casting vars into pointers are overloaded that thay returns
	pointers to the data holders of vars:
		E.g. (string*) cast of var gives you the pointer to the string, which holds var value.
	If the var's type is different that the casted type the type conversion takes place.
	It gives you capibility of reading data into raw vars' pointer or manipulating
	their values directly.

	[WARNNING!] casting vars or changing their values may lead to the situation when
	the received pointer is not valid anymore!
	So please DO NOT USE var data pointers, when THE VAR VALUE MAY BE AFFECTED by
	your application.

 Easily generate default vars of desired types:

 	var::newInt() - generates new var of type int (default value is 0)
 	var::newString() - generates new var of type string (default value is "")
 	var::newArray() - generates new var of type array (default value is {})

   Also you can get special var constants:

    var::getNull()
    var::getNaN()
    var::getInfinity()

*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <typeinfo>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstring>
#include <cstdlib>
#include <cstddef>
using namespace std;

#ifndef _VAR_H
#define _VAR_H

NAMESPACE_VAR_BEGIN__

class var {

	public:

		// Generic data pointer type
		typedef void* ptr;

		// Type ID holder type
		typedef unsigned short vartypeid;

		// Array holder type
		typedef std::vector<var> varray;

		// Hashmap holder type
		typedef std::map<std::string, var> h_varray;

		// Function holder type
		typedef std::function<var(var)> var_funct;


	private:
		// Pointer data holder
		ptr data = nullptr;

		// Type ID of variable
		vartypeid type = VAR_TYPE_UNKNOWN;

	private:

		// For streaming vars
		friend ostream& operator<<(ostream &out, var v);
		friend istream& operator>>(istream &in, var& v);

		// Data type IDs declarations
		static const vartypeid VAR_TYPE_UNKNOWN    = 1;
		static const vartypeid VAR_TYPE_NULL       = 2;
		static const vartypeid VAR_TYPE_NAN        = 3;
		static const vartypeid VAR_TYPE_INFINITY   = 4;
		static const vartypeid VAR_TYPE_BOOL       = 10;
		static const vartypeid VAR_TYPE_CHAR       = 11;
		static const vartypeid VAR_TYPE_INT        = 12;
		static const vartypeid VAR_TYPE_REFERENCE  = 13;
		static const vartypeid VAR_TYPE_LONG_LONG  = 15;
		static const vartypeid VAR_TYPE_FLOAT      = 20;
		static const vartypeid VAR_TYPE_DOUBLE     = 21;
		static const vartypeid VAR_TYPE_STRING     = 50;
		static const vartypeid VAR_TYPE_ARRAY      = 100;
		static const vartypeid VAR_TYPE_HASHMAP    = 101;
		static const vartypeid VAR_TYPE_FUNCT      = 200;

		//TODO: Make references work!
		#define reference_decode(OP, RET) if(type == VAR_TYPE_REFERENCE) { var value (*((*var) data)); OP; return RET; }

		// Translates typeid into readable string
		static string translateTypeName(vartypeid type);

    // Operations for arrays/hashmaps
		inline static varray divideVarays(varray a, varray b);
		inline static varray mergeVarrays(varray a, varray b);
		inline static bool containsVarray(const varray& a, const var& b);
		inline static varray substractVarrays(varray a, varray b);
		inline static varray makeArray(var obj);
		inline static h_varray divideHVarays(h_varray a, h_varray b);
		inline static h_varray mergeHVarrays(h_varray a, h_varray b);
		inline static h_varray mergeStrictHVarrays(h_varray a, h_varray b);
		inline static bool containsHVarray(const h_varray& a, const var& b);
		inline static bool containsHVarrayKey(const h_varray& a, const string& key);
		inline static h_varray substractHVarrays(h_varray a, h_varray b);
		inline static h_varray makeHashmap(var obj);
		template <typename T> inline static varray makeArrayFrom(T obj);
		template <typename T> inline static h_varray makeHashmapFrom(T obj);
		template <typename T> inline static varray makeArrayFromNotStrictObject(T obj);
		template <typename T> inline static h_varray makeHashmapFromNotStrictObject(T obj);
		inline static varray makeArrayFromHashmap(h_varray obj);
		inline static h_varray makeHashmapFromArray(varray obj);
		inline static varray makeArrayFromString(string obj);
		inline static h_varray makeHashmapFromString(string obj);
		inline static string HVarrayToString(h_varray obj);
		inline static string VarrayToString(varray obj);
		inline static string HVarrayToReadableString(h_varray obj);
		inline static string VarrayToReadableString(varray obj);

		// Getters for important atom types
		inline static var getNull();
		inline static var getNaN();
		inline static var getInfinity();


		inline static void delete_(var* a);
		inline static void operator delete(void* a);

		inline static vartypeid getGreaterPrecisionType(vartypeid a, vartypeid b);
		inline static vartypeid getGreaterPrecisionType(vartypeid a, vartypeid b, vartypeid c);

		inline static var operator_add( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_sub( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_mul( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_div( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_neg( vartypeid t, var a );
		inline static var operator_or( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_and( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_mod( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_shift_left( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_shift_right( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_bitwise_not( vartypeid t, var a );
		inline static var operator_bitwise_and( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_bitwise_or( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_bitwise_xor( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_comparsion_less( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_comparsion_equal( vartypeid t, var a, var b, bool take_greater_precision_operation = true );
		inline static var operator_comparsion_more( vartypeid t, var a, var b, bool take_greater_precision_operation = true );


		inline static var& operator_iterate( vartypeid t, var a, int index );

	public:

		// STL-like iterator
		class iterator {
			public:
				var* ptr;
				int index;
				int max_index;

		  public:
		    typedef std::ptrdiff_t difference_type;
		    typedef var value_type;
		    typedef var& reference;
		    typedef var* pointer;
		    typedef std::random_access_iterator_tag iterator_category;

				iterator(var* v, int i, int m);
		    iterator(const iterator& it);
		    ~iterator();
		    iterator& operator=(const iterator& it);
		    bool operator==(const iterator& it) const;
		    bool operator!=(const iterator& it) const;
				bool operator<(const iterator& it);
        bool operator>(const iterator& it);
        bool operator<=(const iterator& it);
        bool operator>=(const iterator& it);
				iterator& operator++();
        iterator operator++(int i);
        iterator& operator--();
        iterator operator--(int i);
        iterator& operator+=(int i);
        iterator operator+(int i) const;
        iterator& operator-=(int i);
        iterator operator-(int i) const;
        difference_type operator-(iterator it) const;
		    reference operator*() const;
		    pointer operator->() const;
    };


		inline static var newInt();
		inline static var newDouble();
		inline static var newFloat();
		inline static var newBool();
		inline static var newChar();
		inline static var newArray();
		inline static var newString();
		inline static var newLongLong();
		inline static var newShort();
		inline static var newNull();
		inline static var newNaN();
		inline static var newInfinity();
		inline static var newHashmap();
		inline static var newFunction();
		inline static var newConstFunction(const var x);
		inline static var newIdFunction();


		inline static var newWrapperProcedure( void(*farg)() );

		template<typename Tret>
		inline static var newWrapperFunction0( Tret(*farg)() );

		template<typename Tret, typename T1>
		inline static var newWrapperFunction1( Tret(*const farg)(T1) );

		template<typename Tret, typename T1, typename T2>
		inline static var newWrapperFunction2( Tret(*farg)(T1, T2) );

		template<typename Tret, typename T1, typename T2, typename T3>
		inline static var newWrapperFunction3( Tret(*farg)(T1, T2, T3) );

		template<typename Tret, typename T1, typename T2, typename T3, typename T4>
		inline static var newWrapperFunction4( Tret(*farg)(T1, T2, T3, T4) );


		inline static var createHashmap(var l);

		const static var Null;
		const static var NaN;
		const static var Infinity;
		const static var Double;
		const static var Float;
		const static var Int;
		const static var Bool;
		const static var Char;
		const static var Array;
		const static var String;
		const static var LongLong;
		const static var Short;
		const static var Hashmap;
		const static var Function;
		const static var IdFunction;

		/** Creates empty var of UNKNOWN type **/
		var( );
		/** This destructor frees all the used memory **/
		~var( );
		/** Creates copy of variable from the existing one. **/
		var( const var& v );

		/** Creates variable from any supported type of data. **/
		template <typename T> var( T from );
		/** Created variable of ARRAY type from the given initialization list. **/
		var(std::initializer_list<var> l);
		//template <typename T> var(std::initializer_list<T> l);

		/** Sets var to the given value. **/
		inline void setTo(var v);

		/** Gets the memory adress where the data is stored.
			Use conversion to void pointer type to manually obtain the saved data. **/
		inline long long getMemoryLocation() const;

		/** Inverse function to toString() **/
		static inline var fromString();

		/** Converts variable to string. **/
		inline string toReadableString() const;
		/** Converts variable to string. **/
		inline string toString() const;
		/** Converts variable to double. **/
		inline double toDouble() const;
		/** Converts variable to integer. **/
		inline int toInt() const;
		/** Converts variable to float. **/
		inline float toFloat() const;
		/** Converts variable to bool. **/
		inline bool toBool() const;
		/** Converts variable to long long. **/
		inline long long toLongLong() const;
		/** Converts variable to char. **/
		inline char toChar() const;
		/** Converts variable to array (var::varray). **/
		inline varray toArray() const;
		/** Converts variable to hashmap (var::h_varray). **/
		inline h_varray toHashmap() const;
		/* Converts variable to var->var function */
		inline var_funct toFunction() const;

		/** Obtains the data pointer from variable in the format of integer pointer. **/
		inline operator int*();
		/** Obtains the data pointer from variable in the format of integer pointer. **/
		inline operator double*();
		/** Obtains the data pointer from variable in the format of double pointer. **/
		inline operator float*();
		/** Obtains the data pointer from variable in the format of float pointer. **/
		inline operator string*();
		/** Obtains the data pointer from variable in the format of string pointer. **/
		inline operator bool*();
		/** Obtains the data pointer from variable in the format of bool pointer. **/
		inline operator long long*();
		/** Obtains the data pointer from variable in the format of long long pointer. **/
		inline operator char*();
		/** Obtains the data pointer from variable in the format of array pointer (var::h_varray*). **/
		inline operator varray*();
		/** Obtains the data pointer from variable in the format of hashmap pointer (var::h_varray*). **/
		inline operator h_varray*();

		inline operator var_funct*();

		/** Converts variable to int. **/
		inline operator int();
		/** Converts variable to double. **/
		inline operator double();
		/** Converts variable to float. **/
		inline operator float();
		/** Converts variable to string. **/
		inline operator string();
		/** Converts variable to bool. **/
		inline operator bool();
		/** Converts variable to long long. **/
		inline operator long long();
		/** Converts variable to char. **/
		inline operator char();
		/** Function cast **/
		inline operator var_funct();
		/** Generic any-type casts **/
		template <typename T> inline operator T*();
		template <typename T> inline operator T();

		/* Convert to cstring */
		inline const char* c_str();

		/** Obtains the type of the variable (var::vartypeid). **/
		inline vartypeid getType() const;
		/** Obtains the human readable string name of the variable's type. **/
		inline string getTypeName() const;
		/** Checks if the variable is integer type. **/
		inline bool isTypeInt() const;
		/** Checks if the variable is double type. **/
		inline bool isTypeDouble() const;
		/** Checks if the variable is float type. **/
		inline bool isTypeFloat() const;
		/** Checks if the variable is string type. **/
		inline bool isTypeString() const;
		/** Checks if the variable is bool type. **/
		inline bool isTypeBool() const;
		/** Checks if the variable is long long type. **/
		inline bool isTypeLongLong() const;
		/** Checks if the variable is char type. **/
		inline bool isTypeChar() const;
		/** Checks if the variable is array type. **/
		inline bool isTypeArray() const;
		/** Checks if the variable is hashmap type. **/
		inline bool isTypeHashmap() const;
		/** Checks if the variable is null. **/
		inline bool isTypeNull() const;
		/** Checks if the variable is NaN. **/
		inline bool isTypeNaN() const;
		/** Checks if the variable is infinity. **/
		inline bool isTypeInfinity() const;
		/** Checks if the variable is a function. **/
		inline bool isTypeFunction() const;
		/** Checks if the variable is a referece. **/
		inline bool isTypeReference() const;
		/** Checks if the variable is the same type as argument var. **/
		inline bool isTypeOf(var v) const;

		/** Checks if the variable is infinity. **/
		inline bool isInfinity() const;
		/** Checks if the variable is NaN. **/
		inline bool isNaN() const;
		/** Checks if the variable is null. **/
		inline bool isNull() const;

		/* Casting functions */
		inline var& castToInt();
		inline var& castToDouble();
		inline var& castToFloat();
		inline var& castToString();
		inline var& castToBool();
		inline var& castToLongLong();
		inline var& castToChar();
		inline var& castToArray();
		inline var& castToHashmap();
		inline var& castToFunction();
		inline var asInt();
		inline var asDouble();
		inline var asFloat();
		inline var asString();
		inline var asBool();
		inline var asLongLong();
		inline var asChar();
		inline var asArray();
		inline var asHashmap();
		inline var asFunction();
		inline var asType(vartypeid t);
		inline var asTypeOf(var v) const;
		template <typename T> inline void assignPointer(T* ptr);
		inline void castToType(vartypeid castType);
		inline void castToTypeOf(const var v);

		/** Get derefernced data pointer without type changes assuming its of the given type **/
		template <typename T> inline T getAutoCastedValue() const;

		/** Get data pointer without type changes assuming its of the given type **/
		template <typename T> inline T* getAutoCastedPointer() const;

		/** Autocast to template parameter type **/
		template <typename T> inline void autoCastTo();

		/** Directly assigns value to variable **/
		template <typename T> inline void assignValue(T val, vartypeid newtype = VAR_TYPE_UNKNOWN);

		/** Size determining functions **/
		inline const unsigned int size();
		inline const unsigned int allocationSize();
		inline const unsigned int dataSize();
		inline const unsigned int totalDataSize();

		/** Operations for hashmaps **/
		inline void removeKey(string key);
		inline void removeKey(const char* key);
		inline bool hasKey(string key);
		inline bool hasKey(const char* key);
		template <typename T> inline void put(string key, T value);
		template <typename T> inline void put(const char* key, T value);

		/** Operations for arrays **/
		template <typename T> inline void put(T value);
		inline var& get(int index);
		inline char getChar(int index);
		inline void setChar(int index, char newChar);
		inline int getCharSize();
		inline int getCharLength();
		inline var first();
		inline var second();
		inline var third();
		inline var& cutoff();
		inline var& cutoff(int beginIndex);
		inline var copy();
		inline var deepCopy();
		inline var reference();
		inline var ref();
		inline var& dereference();
		inline var dereferenceConst() const;
		inline var& put(var v);
		inline var& referenceBottom();
		inline var& concat(var value);
		inline var& erase(int from=0, int to=-1);
		inline var& glue(int from=0, int to=-1);
		inline int find(var value);
		inline int findStrictly(var value);
		inline bool contains(var value);
		inline bool containsStrictly(var value);
		inline bool isSubsetOf(var v);
		inline var getCommonElementsWith(var v);
		inline bool hasCommonElementsWith(var v);
		inline bool has(var v);
		inline bool isSameSet(var v);
		inline void reverse();
		inline void pop();
		inline void push(var v);
		inline void pop_front();
		inline void push_front(var v);
		inline void sort();
		inline void sort(var f);
		inline long long hash();
		inline void unique();

		/** Operations for functions **/
		inline var apply(var args) const;
		inline var apply() const;
		inline var appliedTo(var f) const;
		inline var call(var v1, var v2, var v3, var v4, var v5) const;
		inline var call(var v1, var v2, var v3, var v4) const;
		inline var call(var v1, var v2, var v3) const;
		inline var call(var v1, var v2) const;
		inline var call(var v1) const;
		inline var call() const;
		inline var operator()(var v1, var v2, var v3, var v4, var v5) const;
		inline var operator()(var v1, var v2, var v3, var v4) const;
		inline var operator()(var v1, var v2, var v3) const;
		inline var operator()(var v1, var v2) const;
		inline var operator()(var v1) const;
		inline var operator()() const;

		/** Equality checkers **/
		inline bool equals(var v) const;
		inline bool dEquals(var v) const;
		inline bool anyEquals(var v) const;
		inline bool equalsCast(vartypeid type, var v) const;
	  inline bool equalsStrictly(var v) const;
	  inline bool equalsStrictlySet(var v) const;
	  inline bool equals(var v, unsigned short level);

		/** Iterating functions **/
		inline void foreach(function<void(var)> callback);
		inline void foreach(function<void(var, var)> callback);
		inline void foreachMutate(function<var(var)> callback);
		inline void foreachMutate(function<var(var, var)> callback);
		#define eachMutate(VARNAME, OPCODE) foreachMutate((function<var(var, var)>)([&](var key, var VARNAME)->var{return (OPCODE);}))
		inline void eachMin(var v);
		inline void eachMax(var v);
		inline void eachSet(var v);
		inline void eachGetKey();
		inline void eachAdd(var v);
		inline void eachDivide(var v);
		inline void eachSubstract(var v);
		inline void eachMultiply(var v);
		inline void eachConvertToNumber();
		inline void eachConvertToString();
		inline void eachConvertToLongLong();
		inline void eachConvertToInteger();
		inline void eachConvertToChar();
		inline void eachConvertToDouble();
		inline void eachConvertToFloat();
		inline void eachConvertToArray();
		inline void eachConvertToHashmap();
		inline void eachConvertToFunction();
		inline void eachApply(var args);
		inline void eachApply();
		inline void iterate(var f);
		inline var fold(var f, var acc);
		inline static varray doForeach(function<var(var)> callback, varray obj);
		inline static h_varray doForeach(function<var(var, var)> callback, h_varray obj);
		inline static varray doForeach(function<var(var, var)> callback, varray obj, varray obj2);
		inline static h_varray doForeach(function<var(var, var, var, var)> callback, h_varray obj, h_varray obj2);

		/** Assignment operators **/
		inline void operator=(short val);
		inline void operator=(int val);
		inline void operator=(float val);
		inline void operator=(double val);
		inline void operator=(string val);
		inline void operator=(bool val);
		inline void operator=(long long val);
		inline void operator=(char val);
		inline void operator=(var_funct val);
		template <typename T> inline void operator=(std::initializer_list<T> l);
		template <typename T, int N> inline void operator=(const T arr[N]);
		template <typename T1, typename T2> inline void operator=(map<T1, T2> arr);
		template <typename T> inline void operator=(vector<T> arr);
		inline void operator=(char val[]);
		inline void operator=(const char val[]);
		inline void operator=(var v);
		template <typename T> inline void operator=(T* x);
		template <typename T> inline void operator=(T x);

		/** Arithmetics operators **/
		inline var& operator*();
		inline var operator-();
		inline var operator!();
		inline var operator||(var v);
		inline var operator&&(var v);
		inline var operator&(var v);
		inline var operator|(var v);
		inline var operator^(var v);
		inline void operator&=(var v);
		inline void operator|=(var v);
		inline void operator^=(var v);
		inline var operator~();
		inline var operator+(var v);
		inline void operator+=(var v);
		inline var operator-(var v);
		inline void operator-=(var v);
		inline var operator*(var v);
		inline void operator*=(var v);
		inline var operator/(var v);
		inline void operator/=(var v);
		inline var operator%(var v);
		inline void operator%=(var v);
		inline var operator<<(var v);
		inline void operator<<=(var v);
		inline var operator>>(var v);
		inline void operator>>=(var v);
		inline var& operator++();
		inline var operator++(int dummy_parameter);
		inline var& operator--();
		inline var operator--(int dummy_parameter);
		//inline var& operator[](int index);
		//inline var& operator[](std::string key);
		//inline var& operator[](const char* key);
		inline var& operator[](var key);
		template <typename T> inline var& operator[](T key);
		template <typename T> inline var operator<(T v) const;
		template <typename T> inline var operator>(T v) const;
		template <typename T> inline var operator<=(T v) const;
		template <typename T> inline var operator>=(T v) const;
		template <typename T> inline var operator==(T v) const;

		/** Basic math functionality **/
		inline var abs();
		inline var neg();

		/** Generic autoconversion getter **/
		template <typename T> inline T get();

		/** Clears variable values **/
		inline void clear();

		/** Iterating utility **/
		inline iterator begin();
		inline iterator end();

};

#include "var_operator_toolkit.h"

NAMESPACE_VAR_END__

#endif
