#include "var"

#ifndef _VAR_CPP
#define _VAR_CPP


NAMESPACE_VAR_BEGIN__

namespace var_typeconversion {

		template <typename T>
		inline string genericTypeToString( T value ) {
			std::ostringstream strs;
			strs << value;
			return strs.str();
		}

		template <>
		inline string genericTypeToString<bool>( bool value ) {
			if(value) return "true";
			return "false";
		}

		template <typename T>
		inline T stringToGenericType( string str ) {
			T container;
			std::stringstream strs;
			strs.str(str);
			strs >> container;
			return container;
		}

		template <>
		inline bool stringToGenericType<bool>( string str ) {
			if(str=="true" || str=="1") return true;
			return false;
		}

};


	string var::translateTypeName(var::vartypeid type) {
		switch(type) {
			case VAR_TYPE_NULL: return "null";
			case VAR_TYPE_NAN: return "NaN";
			case VAR_TYPE_INFINITY: return "infinity";
			case VAR_TYPE_CHAR: return "char";
			case VAR_TYPE_INT: return "int";
			case VAR_TYPE_REFERENCE: return "reference";
			case VAR_TYPE_DOUBLE: return "double";
			case VAR_TYPE_FLOAT: return "float";
			case VAR_TYPE_STRING: return "string";
			case VAR_TYPE_BOOL: return "bool";
			case VAR_TYPE_LONG_LONG: return "long long";
			case VAR_TYPE_ARRAY: return "array";
			case VAR_TYPE_HASHMAP: return "hashtable";
			case VAR_TYPE_FUNCT: return "function";

			//case VAR_TYPE_OBJECT: return "object";
			default: return "undefined{vartypeid="+var_typeconversion::genericTypeToString<vartypeid>(type)+"}";
		}
		return "undefined{vartypeid="+var_typeconversion::genericTypeToString<vartypeid>(type)+"}";
	}

	inline var::varray var::divideVarays(varray a, varray b) {
		const int sizea = a.size();
		varray c;
		varray buffer;
		for(int it=0;it<sizea;++it) {
			if(containsVarray(b, a[it])) {
				c.push_back(var(buffer));
				buffer.clear();
			} else {
				buffer.push_back(a[it]);
			}
		}
		if(buffer.size()>0) c.push_back(var(buffer));
		return c;
	}

	inline var::varray var::mergeVarrays(varray a, varray b) {
		const int sizea = a.size();
		const int sizeb = b.size();
		varray c;
		for(int it=0;it<sizea;++it) c.push_back(a[it]);
		for(int it=0;it<sizeb;++it) c.push_back(b[it]);
		return c;
	}

	inline bool var::containsVarray(const varray& a, const var& b) {
		const int len = a.size();
		for(int it=0;it<len;++it) {
			if(a[it].equals(b)) {
				return true;
			}
		}
		return false;
	}

	inline var::varray var::substractVarrays(varray a, varray b) {
		const int sizea = a.size();
		varray c;
		for(int it=0;it<sizea;++it) {
			if(!containsVarray(b, a[it])) {
				c.push_back(a[it]);
			}
		}
		return c;
	}

	inline var::varray var::makeArray(var obj) {
		varray v;
		v.push_back(obj);
		return v;
	}

	/////////////////



	inline var::h_varray var::divideHVarays(h_varray a, h_varray b) {
		varray out;
		h_varray buffer;
		for( auto el : a ) {
			if(containsHVarray(b, el.second)) {
				out.push_back(buffer);
				buffer.clear();
			} else {
				buffer[el.first] = el.second;
			}
		}
		if(buffer.size()>0) out.push_back(buffer);
		return makeHashmapFromArray(out);
	}

	inline var::h_varray var::mergeHVarrays(h_varray a, h_varray b) {
		h_varray c;
		for( auto el : a ) {
			c[el.first] = el.second;
		}
		for( auto el : b ) {
			if(c.count(el.first)) {
				int nkey = 0;
				while(c.count(var_typeconversion::genericTypeToString(nkey))) {
					++nkey;
				}
				c[var_typeconversion::genericTypeToString(nkey)] = el.second;
			} else c[el.first] = el.second;
		}
		return c;
	}

	inline var::h_varray var::mergeStrictHVarrays(h_varray a, h_varray b) {
		h_varray c;
		for( auto el : b ) {
			c[el.first] = el.second;
		}
		for( auto el : a ) {
			c[el.first] = el.second;
		}
		return c;
	}

	inline bool var::containsHVarray(const h_varray& a, const var& b) {
		for( auto el : a ) {
			if(el.second.equals(b)) {
				return true;
			}
		}
		return false;
	}

	inline bool var::containsHVarrayKey(const h_varray& a, const string& key) {
		return a.count(key);
	}

	inline var::h_varray var::substractHVarrays(h_varray a, h_varray b) {
		h_varray c;
		for(auto el : a) {
			if(!containsHVarray(b, el.second)) {
				c[el.first] = el.second;
			}
		}
		return c;
	}

	inline var::h_varray var::makeHashmap(var obj) {
		h_varray v;
		v["0"] = obj;
		return v;
	}

	////////////////

	template <typename T>
	inline var::varray var::makeArrayFrom(T obj) {
		varray v;
		v.push_back(var(obj));
		return v;
	}

	template <typename T>
	inline var::h_varray var::makeHashmapFrom(T obj) {
		h_varray v;
		v["0"] = (var(obj));
		return v;
	}

	template <typename T>
	inline var::varray var::makeArrayFromNotStrictObject(T obj) {
		return var(var_typeconversion::genericTypeToString(obj)).toArray();
	}

	template <typename T>
	inline var::h_varray var::makeHashmapFromNotStrictObject(T obj) {
		return var(var_typeconversion::genericTypeToString(obj)).toHashmap();
	}

	inline var::varray var::makeArrayFromHashmap(var::h_varray obj) {
		varray ret;
		for(auto el : obj) {
			ret.push_back(el.second);
		}
		return ret;
	}

	inline var::h_varray var::makeHashmapFromArray(var::varray obj) {
		h_varray ret;
		const int size = obj.size();
		for(int it=0;it<size;++it) {
			ret[var_typeconversion::genericTypeToString(it)] = obj[it];
		}
		return ret;
	}

	inline var::varray var::makeArrayFromString(string obj) {
		varray ret;
		for(char el : obj) {
			ret.push_back(var(el));
		}
		return ret;
	}

	inline var::h_varray var::makeHashmapFromString(string obj) {
		return makeHashmapFromArray( makeArrayFromString(obj) );
	}

	inline string var::HVarrayToReadableString(h_varray obj) {
		string ret = "{";
		int itnum = 0;
		const int size = obj.size();
		for(auto el : obj) {
			ret += "{" + el.first + ": " + el.second.toReadableString() + "}";
			if(itnum!=size-1) ret += ", ";
			++itnum;
		}
		ret += "}";
		return ret;
	}

	inline string var::HVarrayToString(h_varray obj) {
		string ret = "";
		for( auto el : obj ) {
			ret += el.second.toString();
		}
		return ret;
	}

	inline string var::VarrayToReadableString(varray obj) {
		const int len = obj.size();
		string ret = "[";
		for(int it=0;it<len;++it) {
			ret += obj[it].toReadableString();
			if(it!=len-1) ret += ", ";
		}
		ret += "]";
		return ret;
	}

	inline string var::VarrayToString(varray obj) {
		string ret = "";
		for( auto el : obj ) {
			ret += el.toString();
		}
		return ret;
	}

	inline var var::newInt() {
		return var(0);
	}

	inline var var::newDouble() {
		return var(0.0);
	}

	inline var var::newFloat() {
		return var(0.0f);
	}

	inline var var::newBool() {
		return var(false);
	}

	inline var var::newChar() {
		return var('\0');
	}

	inline var var::newArray() {
		varray t;
		return var(t);
	}

	inline var var::newString() {
		return var("");
	}

	inline var var::newLongLong() {
		return var(0LL);
	}

	inline var var::newShort() {
		return var((short)0);
	}

	inline var var::newNull() {
		var ret(0LL);
		ret.castToType(VAR_TYPE_NULL);
		return ret;
	}

	inline var var::newNaN() {
		var ret(0LL);
		ret.castToType(VAR_TYPE_NAN);
		return ret;
	}

	inline var var::newInfinity() {
		var ret(0LL);
		ret.castToType(VAR_TYPE_INFINITY);
		return ret;
	}

	inline var var::newHashmap() {
		h_varray t;
		return var(t);
	}

	inline var var::newFunction() {
		var_funct f = var_funct_decl({ return var::Null; });
		return var(f);
	}

	inline var var::newConstFunction(const var x) {
		var_funct f = var_funct_decl({ return x; });
		return var(f);
	}

	inline var var::newIdFunction() {
		var_funct f = var_funct_decl({ return args; });
		return var(f);
	}


	inline var var::newWrapperProcedure( void(*farg)() ) {
		void(*const f)() = farg;
		return var((std::function<var(var)>)([f](__attribute__ ((unused)) var args)->var {
			f();
			return var::Null;
		}));
	};


	template<typename Tret>
	inline var var::newWrapperFunction0( Tret(*farg)() ) {
		Tret(*const f)() = farg;
		return var((std::function<var(var)>)([f](var args)->var {
			return var(f());
		}));
	};

	template<typename Tret, typename T1>
	inline var var::newWrapperFunction1( Tret(*const farg)(T1) ) {
		Tret(*const f)(T1) = farg;
		return var((std::function<var(var)>)([f](var args)->var {
			return var(f( (T1)args[0] ));
		}));
	};

	template<typename Tret, typename T1, typename T2>
	inline var var::newWrapperFunction2( Tret(*farg)(T1, T2) ) {
		Tret(*const f)(T1, T2) = farg;
		return var((std::function<var(var)>)([f](var args)->var {
			return var(f( (T1)args[0], (T2)args[1] ));
		}));
	};

	template<typename Tret, typename T1, typename T2, typename T3>
	inline var var::newWrapperFunction3( Tret(*farg)(T1, T2, T3) ) {
		Tret(*const f)(T1, T2, T3) = farg;
		return var((std::function<var(var)>)([f](var args)->var {
			return var(f( (T1)args[0], (T2)args[1], (T3)args[2] ));
		}));
	};

	template<typename Tret, typename T1, typename T2, typename T3, typename T4>
	inline var var::newWrapperFunction4( Tret(*farg)(T1, T2, T3, T4) ) {
		Tret(*const f)(T1, T2, T3, T4) = farg;
		return var((std::function<var(var)>)([f](var args)->var {
			return var(f( (T1)args[0], (T2)args[1], (T3)args[2], (T4)args[3] ));
		}));
	};


/*ssss*/



	/*inline var var::newWrapperProcedure(function<void()> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			f();
			return var::Null;
		}));
	};

	template<typename Tret>
	inline var var::newWrapperFunction0(function<Tret()> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			return var(f());
		}));
	};

	template<typename Tret, typename T1>
	inline var var::newWrapperFunction1(function<Tret(T1)> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			return var(f( (T1)args[0] ));
		}));
	};

	template<typename Tret, typename T1, typename T2>
	inline var var::newWrapperFunction2(function<Tret(T1, T2)> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			return var(f( (T1)args[0], (T2)args[1] ));
		}));
	};

	template<typename Tret, typename T1, typename T2, typename T3>
	inline var var::newWrapperFunction3(function<Tret(T1, T2, T3)> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			return var(f( (T1)args[0], (T2)args[1], (T3)args[2] ));
		}));
	};

	template<typename Tret, typename T1, typename T2, typename T3, typename T4>
	inline var var::newWrapperFunction4(function<Tret(T1, T2, T3, T4)> farg) {
		const auto f = farg;
		return var(var_funct_decl({
			return var(f( (T1)args[0], (T2)args[1], (T3)args[2], (T4)args[3] ));
		}));
	};*/


	inline var var::createHashmap(var l) {
		var ret = var::Hashmap;
		l.foreach([&ret](var element)->void {
			ret[element[0].toString()] = element[1];
		});
		return ret;
	}

	const var var::Null = var::newNull();
	const var var::NaN = var::newNaN();
	const var var::Infinity = var::newInfinity();
	const var var::Double = var::newDouble();
	const var var::Float = var::newFloat();
	const var var::Bool = var::newBool();
	const var var::Char = var::newChar();
	const var var::Array = var::newArray();
	const var var::String = var::newString();
	const var var::LongLong = var::newLongLong();
	const var var::Short = var::newShort();
	const var var::Hashmap = var::newHashmap();
	const var var::Function = var::newFunction();
	const var var::IdFunction = var::newIdFunction();


	inline var var::getNull() {
		return newNull();
	}

	inline var var::getNaN() {
		return newNaN();
	}

	inline var var::getInfinity() {
		return newInfinity();
	}

	inline void var::delete_(var* a) {
		void *ptr = a->data;
		if(ptr == nullptr) return;

		switch(a->type) {
			case VAR_TYPE_REFERENCE: /*TODO: Deallocate anything?*/ break;
			case VAR_TYPE_CHAR: delete (static_cast<char*>(ptr)); break;
			case VAR_TYPE_INT: delete (static_cast<int*>(ptr)); break;
			case VAR_TYPE_DOUBLE: delete (static_cast<double*>(ptr)); break;
			case VAR_TYPE_FLOAT: delete (static_cast<float*>(ptr)); break;
			case VAR_TYPE_STRING: delete (static_cast<string*>(ptr)); break;
			case VAR_TYPE_BOOL: delete (static_cast<bool*>(ptr)); break;
			case VAR_TYPE_LONG_LONG: delete (static_cast<long long*>(ptr)); break;
			case VAR_TYPE_ARRAY: delete (static_cast<varray*>(ptr)); break;
			case VAR_TYPE_HASHMAP: delete (static_cast<h_varray*>(ptr)); break;
			case VAR_TYPE_FUNCT: delete (static_cast<var_funct*>(ptr)); break;
			case VAR_TYPE_NULL: case VAR_TYPE_INFINITY: case VAR_TYPE_NAN: break;
			default: throw var_exception_no_such_operation("delete [memory dealocation]", static_cast<var*>(a)->getTypeName().c_str());
		}
		a->data = nullptr;
		a->type = VAR_TYPE_UNKNOWN;
	}

	inline void var::operator delete(void* a) {
		if(a==nullptr) return;
		var::delete_(static_cast<var*>(a));
	}

	inline var::vartypeid var::getGreaterPrecisionType(vartypeid a, vartypeid b) {
		if(a>=b) return a;
		return b;
	}

	inline var::vartypeid var::getGreaterPrecisionType(vartypeid a, vartypeid b, vartypeid c) {
		if(a>=b) return getGreaterPrecisionType(a, c);
		return getGreaterPrecisionType(b, c);
	}

	#include "var_operations_definitions.h"

	//define castToTypeOf(x) castToType((x).getType())

	var::var( ) {

	}

	var::~var( ) {
		//var::delete_(this);
	}

	var::var( const var& v ) {
		switch(v.type) {
			case VAR_TYPE_REFERENCE: data = v.data; break;
			case VAR_TYPE_CHAR: assignValue(v.getAutoCastedValue<char>(), v.type); break;
			case VAR_TYPE_INT: assignValue(v.getAutoCastedValue<int>(), v.type); break;
			case VAR_TYPE_DOUBLE: assignValue(v.getAutoCastedValue<double>(), v.type); break;
			case VAR_TYPE_FLOAT: assignValue(v.getAutoCastedValue<float>(), v.type); break;
			case VAR_TYPE_STRING: assignValue(v.getAutoCastedValue<string>(), v.type); break;
			case VAR_TYPE_BOOL: assignValue(v.getAutoCastedValue<bool>(), v.type); break;
			case VAR_TYPE_LONG_LONG: assignValue(v.getAutoCastedValue<long long>(), v.type); break;
			case VAR_TYPE_ARRAY: assignValue(v.getAutoCastedValue<varray>(), v.type); break;
			case VAR_TYPE_HASHMAP: assignValue(v.getAutoCastedValue<h_varray>(), v.type); break;
			case VAR_TYPE_FUNCT: assignValue(v.getAutoCastedValue<var_funct>(), v.type); break;
			case VAR_TYPE_NULL: break;
			case VAR_TYPE_NAN: break;
			case VAR_TYPE_INFINITY: break;
			//default: throw var_exception_no_such_operation("var( const var& ) [copy constructor]", v.getTypeName().c_str());
		}
		type = v.type;
	}

	/*template <typename T>
	var::var(std::initializer_list<T> l) {
		operator=(vector<T>(l));
	}*/

	var::var(std::initializer_list<var> l) {
		operator=(vector<var>(l));
	}

	template <typename T>
	var::var( T from ) {
		operator=(from);
	}

	inline void var::setTo(var v) {
		switch(v.type) {
			case VAR_TYPE_REFERENCE: data = v.data; break;
			case VAR_TYPE_CHAR: assignValue(v.getAutoCastedValue<char>(), v.type); break;
			case VAR_TYPE_INT: assignValue(v.getAutoCastedValue<int>(), v.type); break;
			case VAR_TYPE_DOUBLE: assignValue(v.getAutoCastedValue<double>(), v.type); break;
			case VAR_TYPE_FLOAT: assignValue(v.getAutoCastedValue<float>(), v.type); break;
			case VAR_TYPE_STRING: assignValue(v.getAutoCastedValue<string>(), v.type); break;
			case VAR_TYPE_BOOL: assignValue(v.getAutoCastedValue<bool>(), v.type); break;
			case VAR_TYPE_LONG_LONG: assignValue(v.getAutoCastedValue<long long>(), v.type); break;
			case VAR_TYPE_ARRAY: assignValue(v.getAutoCastedValue<varray>(), v.type); break;
			case VAR_TYPE_HASHMAP: assignValue(v.getAutoCastedValue<h_varray>(), v.type); break;
			case VAR_TYPE_FUNCT: assignValue(v.getAutoCastedValue<var_funct>(), v.type); break;
			case VAR_TYPE_NULL: break;
			case VAR_TYPE_NAN: break;
			case VAR_TYPE_INFINITY: break;
			default: throw var_exception_no_such_operation("operator= [setTo(...) - copy constructor]", v.getTypeName().c_str());
		}
		type = v.type;
	}

	inline long long var::getMemoryLocation() const {
		return (long long)data;
	}

	/*inline void mergeWithArray(var arr) {
		const varray*
	}*/

	bool compare(pair<int,int> x, pair<int,int> y) {
	  return x.first < y.first;
	}

	/*static inline var var::fromString(const string str) {
		if(str.toLowerCase()=="infinity") return var::newInfinity();
		if(str.toLowerCase()=="nan") return var::newNaN();
		if(str.toLowerCase()=="null") return var::newNull();
		remove(str.begin(),str.end(),' ');
		const int len = str.size();
		for(int i=0;i<len;++i) {

		}
		return var::newNull();
	}*/

	inline string var::toReadableString() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toString();
			case VAR_TYPE_CHAR: return "'" + var_typeconversion::genericTypeToString( getAutoCastedValue<char>() ) + "'";
			case VAR_TYPE_INT: return var_typeconversion::genericTypeToString( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return var_typeconversion::genericTypeToString( getAutoCastedValue<double>() ) + "d";
			case VAR_TYPE_FLOAT: return var_typeconversion::genericTypeToString( getAutoCastedValue<float>() ) + "f";
			case VAR_TYPE_STRING: return "\"" + getAutoCastedValue<string>() + "\"";
			case VAR_TYPE_BOOL: return var_typeconversion::genericTypeToString( getAutoCastedValue<bool>() ) + "b";
			case VAR_TYPE_LONG_LONG: return var_typeconversion::genericTypeToString( getAutoCastedValue<long long>() );
			case VAR_TYPE_ARRAY: return VarrayToReadableString( getAutoCastedValue<varray>() );
			case VAR_TYPE_HASHMAP: return HVarrayToReadableString( getAutoCastedValue<h_varray>() );
			case VAR_TYPE_FUNCT: return "<function>";
			case VAR_TYPE_NULL: return "null";
			case VAR_TYPE_NAN: return "NaN";
			case VAR_TYPE_INFINITY: return "infinity";
			case VAR_TYPE_UNKNOWN: return "<unknown>";
			default: return "<unknown "+getTypeName()+">";
			//default: throw var_exception_no_such_operation("toReadableString()", getTypeName().c_str());
		}
		return "";
	}

	inline string var::toString() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toString();
			case VAR_TYPE_CHAR: return var_typeconversion::genericTypeToString( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return var_typeconversion::genericTypeToString( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return var_typeconversion::genericTypeToString( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return var_typeconversion::genericTypeToString( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return getAutoCastedValue<string>();
			case VAR_TYPE_BOOL: return var_typeconversion::genericTypeToString( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return var_typeconversion::genericTypeToString( getAutoCastedValue<long long>() );
			case VAR_TYPE_ARRAY: return VarrayToString( getAutoCastedValue<varray>() );
			case VAR_TYPE_HASHMAP: return HVarrayToString( getAutoCastedValue<h_varray>() );
			case VAR_TYPE_FUNCT: return "<function>";
			case VAR_TYPE_NULL: return "null";
			case VAR_TYPE_NAN: return "NaN";
			case VAR_TYPE_INFINITY: return "infinity";
			default: throw var_exception_no_such_operation("toString()", getTypeName().c_str());
		}
		return "";
	}

	inline double var::toDouble() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toDouble();
			case VAR_TYPE_CHAR: return static_cast<double>( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return static_cast<double>( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return static_cast<double>( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return static_cast<double>( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<double>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return static_cast<double>( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return static_cast<double>( getAutoCastedValue<long long>() );
			default: throw var_exception_no_such_operation("toDouble()", getTypeName().c_str());
		}
		return 0.0;
	}

	inline int var::toInt() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toInt();
			case VAR_TYPE_CHAR: return static_cast<int>( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return static_cast<int>( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return static_cast<int>( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return static_cast<int>( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<int>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return static_cast<int>( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return static_cast<int>( getAutoCastedValue<long long>() );
		}
		return 0;
	}

	inline float var::toFloat() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toFloat();
			case VAR_TYPE_CHAR: return static_cast<float>( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return static_cast<float>( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return static_cast<float>( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return static_cast<float>( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<float>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return static_cast<float>( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return static_cast<float>( getAutoCastedValue<long long>() );
			default: throw var_exception_no_such_operation("toFloat()", getTypeName().c_str());
		}
		return 0.0f;
	}

	inline bool var::toBool() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toBool();
			case VAR_TYPE_CHAR: if(( getAutoCastedValue<char>() ) != 0) return true; break;
			case VAR_TYPE_INT: if(( getAutoCastedValue<int>() ) != 0) return true; break;
			case VAR_TYPE_DOUBLE: if(( getAutoCastedValue<double>() ) != 0) return true; break;
			case VAR_TYPE_FLOAT: if(( getAutoCastedValue<float>() ) != 0) return true; break;
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<bool>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: if(( getAutoCastedValue<bool>() ) != 0) return true; break;
			case VAR_TYPE_LONG_LONG: if(( getAutoCastedValue<long long>() ) != 0) return true; break;
			default: throw var_exception_no_such_operation("toBool()", getTypeName().c_str());
		}
		return false;
	}

	inline long long var::toLongLong() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toLongLong();
			case VAR_TYPE_CHAR: return static_cast<long long>( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return static_cast<long long>( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return static_cast<long long>( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return static_cast<long long>( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<long long>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return static_cast<long long>( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return static_cast<long long>( getAutoCastedValue<long long>() );
			default: throw var_exception_no_such_operation("toLongLong()", getTypeName().c_str());
		}
		return 0LL;
	}

	inline char var::toChar() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toChar();
			case VAR_TYPE_CHAR: return static_cast<char>( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return static_cast<char>( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return static_cast<char>( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return static_cast<char>( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var_typeconversion::stringToGenericType<char>( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return static_cast<char>( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return static_cast<char>( getAutoCastedValue<long long>() );
			default: throw var_exception_no_such_operation("toChar()", getTypeName().c_str());
		}
		return '\0';
	}

	inline var::varray var::toArray() const {
		switch(type) {
			case VAR_TYPE_UNKNOWN: return vector<var>();
			case VAR_TYPE_NAN: return var::makeArrayFrom( var::NaN );
			case VAR_TYPE_NULL: return vector<var>();
			case VAR_TYPE_INFINITY: return var::makeArrayFrom( var::Infinity );
			case VAR_TYPE_REFERENCE: return dereferenceConst().toArray();
			case VAR_TYPE_CHAR: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<char>() ) );
			case VAR_TYPE_INT: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<int>() ) );
			case VAR_TYPE_DOUBLE: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<double>() ) );
			case VAR_TYPE_FLOAT: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<float>() ) );
			case VAR_TYPE_BOOL: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<bool>() ) );
			case VAR_TYPE_LONG_LONG: return var::makeArrayFromString( var_typeconversion::genericTypeToString( getAutoCastedValue<long long>() ) );
			case VAR_TYPE_STRING: return var::makeArrayFromString( getAutoCastedValue<string>() );
			case VAR_TYPE_ARRAY: return getAutoCastedValue<varray>();
			case VAR_TYPE_HASHMAP: return var::makeArrayFromHashmap( getAutoCastedValue<h_varray>() );
			case VAR_TYPE_FUNCT: return apply().toArray();
			default: throw var_exception_no_such_operation("toArray()", getTypeName().c_str());
		}
		varray t;
		return t;
	}

	inline var::h_varray var::toHashmap() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toHashmap();
			case VAR_TYPE_CHAR: return var::makeHashmapFrom( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return var::makeHashmapFrom( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return var::makeHashmapFrom( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return var::makeHashmapFrom( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return var::makeHashmapFromString( getAutoCastedValue<string>() );
			case VAR_TYPE_BOOL: return var::makeHashmapFrom( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return var::makeHashmapFrom( getAutoCastedValue<long long>() );
			case VAR_TYPE_ARRAY: return var::makeHashmapFromArray( getAutoCastedValue<varray>() );
			case VAR_TYPE_HASHMAP: return getAutoCastedValue<h_varray>();
			case VAR_TYPE_FUNCT: return apply().toHashmap();
			default: throw var_exception_no_such_operation("toHashmap()", getTypeName().c_str());
		}
		h_varray t;
		return t;
	}

	inline var::var_funct var::toFunction() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toFunction();
			case VAR_TYPE_CHAR:
			case VAR_TYPE_INT:
			case VAR_TYPE_DOUBLE:
			case VAR_TYPE_FLOAT:
			case VAR_TYPE_STRING:
			case VAR_TYPE_BOOL:
			case VAR_TYPE_LONG_LONG:
			case VAR_TYPE_ARRAY:
			case VAR_TYPE_HASHMAP: {
				const var value = (*this);
				return var_funct_decl({ return value; });
			}
			case VAR_TYPE_FUNCT: return getAutoCastedValue<var_funct>();
			default: throw var_exception_no_such_operation("toFunction()", getTypeName().c_str());
		}
		return var_funct_decl({ return var::Null; });
	}

	/*inline var::var_funct var::toFunction() const {
		switch(type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().toFunction();
			case VAR_TYPE_CHAR:
			case VAR_TYPE_INT:
			case VAR_TYPE_DOUBLE:
			case VAR_TYPE_FLOAT:
			case VAR_TYPE_STRING:
			case VAR_TYPE_BOOL:
			case VAR_TYPE_LONG_LONG:
			case VAR_TYPE_ARRAY:
			case VAR_TYPE_HASHMAP:
				return var::newConstFunction(*this);
			case VAR_TYPE_FUNCT: return var(*this);
			default: throw var_exception_no_such_operation("toFunction()", getTypeName().c_str());
		}
		return var::newFunction();
	}*/

	inline var::operator int*() {
		castToType(VAR_TYPE_INT);
		return static_cast<int*>(this->data);
	}

	inline var::operator double*() {
		castToType(VAR_TYPE_DOUBLE);
		return static_cast<double*>(this->data);
	}

	inline var::operator float*() {
		castToType(VAR_TYPE_FLOAT);
		return static_cast<float*>(this->data);
	}

	inline var::operator string*() {
		castToType(VAR_TYPE_STRING);
		return static_cast<string*>(this->data);
	}

	inline var::operator bool*() {
		castToType(VAR_TYPE_BOOL);
		return static_cast<bool*>(this->data);
	}

	inline var::operator long long*() {
		castToType(VAR_TYPE_LONG_LONG);
		return static_cast<long long*>(this->data);
	}

	inline var::operator char*() {
		castToType(VAR_TYPE_CHAR);
		return static_cast<char*>(this->data);
	}

	inline var::operator varray*() {
		castToType(VAR_TYPE_ARRAY);
		return static_cast<varray*>(this->data);
	}

	inline var::operator h_varray*() {
		castToType(VAR_TYPE_HASHMAP);
		return static_cast<h_varray*>(this->data);
	}

	inline var::operator var_funct*() {
		castToType(VAR_TYPE_FUNCT);
		return static_cast<var_funct*>(this->data);
	}

	inline var::operator int() {
		return toInt();
	}

	inline var::operator double() {
		return toDouble();
	}

	inline var::operator float() {
		return toFloat();
	}

	inline var::operator string() {
		return toString();
	}

	inline var::operator bool() {
		return toBool();
	}

	inline var::operator long long() {
		return toLongLong();
	}

	inline var::operator char() {
		return toChar();
 }

 inline var::operator var::var_funct() {
	 return toFunction();
 }

	template <typename T>
	inline var::operator T*() {
		return (T*)toLongLong();
	}

	template <typename T>
	inline var::operator T() {
		cout<<"[WARN] Experimental generic CONVERSION WAS USED! [var->T] :(\n";cout.flush();
		//return (T::fromVar(*this));
		return (var::conversion<T>::fromVar(*this));
	}


	inline var::vartypeid var::getType() const {
		return type;
	}

	inline unsigned int var::size() {
		return toArray().size();
	}

	inline unsigned int var::allocationSize() {
		switch(type) {
			case VAR_TYPE_NULL: return 0;
			case VAR_TYPE_INFINITY: return 0;
			case VAR_TYPE_NAN: return 0;
			case VAR_TYPE_REFERENCE: return sizeof( getAutoCastedValue<var*>() );
			case VAR_TYPE_CHAR: return sizeof( getAutoCastedValue<char>() );
			case VAR_TYPE_INT: return sizeof( getAutoCastedValue<int>() );
			case VAR_TYPE_DOUBLE: return sizeof( getAutoCastedValue<double>() );
			case VAR_TYPE_FLOAT: return sizeof( getAutoCastedValue<float>() );
			case VAR_TYPE_STRING: return sizeof(getAutoCastedValue<string>().c_str()) + sizeof(char) * strlen(getAutoCastedValue<string>().c_str());
			case VAR_TYPE_BOOL: return sizeof( getAutoCastedValue<bool>() );
			case VAR_TYPE_LONG_LONG: return sizeof( getAutoCastedValue<long long>() );
			case VAR_TYPE_ARRAY: return sizeof(getAutoCastedValue<varray>()) + sizeof(varray) * getAutoCastedValue<varray>().capacity();
			case VAR_TYPE_HASHMAP: return sizeof(getAutoCastedValue<h_varray>()) + sizeof(h_varray) * getAutoCastedValue<h_varray>().size();
			case VAR_TYPE_FUNCT: return sizeof(getAutoCastedValue<var_funct>());
			default: throw var_exception_no_such_operation("allocation_size()", getTypeName().c_str());
		}
	}

	inline unsigned int var::dataSize() {
		return sizeof(this) + allocationSize();
	}

	inline unsigned int var::totalDataSize() {
		if(type == VAR_TYPE_REFERENCE) {
			return dataSize() + dereference().totalDataSize();
		}
		return dataSize();
	}

	inline void var::removeKey(string key) {
		castToHashmap();
		getAutoCastedValue<h_varray>().erase(key);
	}

	inline void var::removeKey(const char* key) {
		castToHashmap();
		getAutoCastedValue<h_varray>().erase(string(key));
	}

	inline bool var::hasKey(string key) {
		castToHashmap();
		return getAutoCastedValue<h_varray>().count(key);
	}

	inline bool var::hasKey(const char* key) {
		castToHashmap();
		return getAutoCastedValue<h_varray>().count(string(key));
	}

	template <typename T>
	inline void var::put(string key, T value) {
		castToHashmap();
		getAutoCastedValue<h_varray>()[key] = var(value);
	}

	template <typename T>
	inline void var::put(const char* key, T value) {
		castToHashmap();
		getAutoCastedValue<h_varray>()[string(key)] = var(value);
	}

	template <typename T>
	inline void var::put(T value) {
		if(type == VAR_TYPE_HASHMAP) {
			h_varray h;
			h["0"] = var(value);
			operator=(mergeHVarrays(getAutoCastedValue<h_varray>(), h));
		} else if(type == VAR_TYPE_STRING) {
			operator=(getAutoCastedValue<string>()+var_typeconversion::genericTypeToString(value));
		} else if(type == VAR_TYPE_ARRAY) {
			varray h;
			h.push_back(var(value));
			operator=(mergeVarrays(getAutoCastedValue<varray>(), h));
		} else {
			operator=(value);
		}
	}

	inline var& var::get(int index) {
		castToArray();
		return (*(static_cast<varray*>(data)))[index];
	}

	inline void var::setChar(int index, char newChar) {
		const vartypeid t = type;
		string str = toString();
		str[index] = newChar;
		operator=(str);
		castToType(t);
	}

	inline char var::getChar(int index) {
		return toString()[index];
	}

	inline int var::getCharSize() {
		return toString().size();
	}

	inline int var::getCharLength() {
		return toString().size();
	}

	inline var var::first() {
		return operator[](0);
	}

	inline var var::second() {
		return operator[](1);
	}

	inline var var::third() {
		return operator[](2);
	}

	inline var& var::cutoff() {
		operator=(first());
		return (*this);
	}

	inline var& var::cutoff(int beginIndex) {
		castToArray();
		varray v = *static_cast<varray*>(data);
		const int size = v.size();
		varray nv;
		for(int it=0;it<beginIndex;++it) {
			if(it>=size) {
				nv.push_back(0);
			} else {
				nv.push_back(v[it]);
			}
		}
		operator=(nv);
		return (*this);
	}

	inline var var::copy() {
		return var(*this);
	}

	inline var var::deepCopy() {
		switch(type) {
			case VAR_TYPE_NULL:
			case VAR_TYPE_INFINITY:
			case VAR_TYPE_NAN:
			case VAR_TYPE_REFERENCE:
			case VAR_TYPE_CHAR:
			case VAR_TYPE_INT:
			case VAR_TYPE_DOUBLE:
			case VAR_TYPE_FLOAT:
			case VAR_TYPE_STRING:
			case VAR_TYPE_BOOL:
			case VAR_TYPE_FUNCT:
			case VAR_TYPE_LONG_LONG:
				return copy();
			case VAR_TYPE_ARRAY: {
				varray* v = new varray();
				foreach((function<var(var)>)([&](var value)->var {
					v->push_back(value.deepCopy());
					return value;
				}));
				var ret;
				ret.data = v;
				ret.type = VAR_TYPE_ARRAY;
				return ret;
			}
			case VAR_TYPE_HASHMAP: {
				h_varray* v = new h_varray();
				foreach((function<var(var, var)>)([&](var key, var value)->var {
					(*v)[key] = value.deepCopy();
					return value;
				}));
				var ret;
				ret.data = v;
				ret.type = VAR_TYPE_HASHMAP;
				return ret;
			}
			default: throw var_exception_no_such_operation("deep_copy()", getTypeName().c_str());
		}
	}

	inline var var::reference() {
		var ref;
		ref.data = this;
		ref.type = VAR_TYPE_REFERENCE;
		return ref;
	}

	inline var var::ref() {
		var ref;
		ref.data = this;
		ref.type = VAR_TYPE_REFERENCE;
		return ref;
	}

	inline var& var::dereference() {
		if(type==VAR_TYPE_REFERENCE) {
			return *((var*)data);
		}
		return *this;
	}

	inline var var::dereferenceConst() const {
		if(type==VAR_TYPE_REFERENCE) {
			return *((var*)data);
		}
		return *this;
	}

	inline var& var::put(var v) {
		dereference() = v;
		return (*this);
	}

	inline var& var::referenceBottom() {
		if(type==VAR_TYPE_REFERENCE) {
			return dereference().referenceBottom();
		}
		return (*this);
	}

	inline var& var::concat(var value) {
		operator=(toString()+value.toString());
		return (*this);
	}

	inline var& var::erase(int from, int to) {
		castToArray();
		if(to<0) to=from;
		if(to<from) {
			swap(from, to);
		}
		varray& v = *static_cast<varray*>(data);
		if(from<0) from=0;
		if(to>(int)v.size()-1) to=v.size()-1;
		v.erase((varray::iterator)v.begin()+from, (varray::iterator)v.begin()+to+1);
		return (*this);
	}

	inline var& var::glue(int from, int to) {
		castToArray();
		varray& v = *static_cast<varray*>(data);
		if(to<0) to=v.size()-1;
		if(to<from) {
			swap(from, to);
		}
		if(from<0) from=0;
		if(to>(int)v.size()-1) to=v.size()-1;
		var x = "";
		for(int it=from;it<to+1;++it) {
			x.concat(v[it]);
		}
		erase(from+1, to);
		v[from] = x;
		return (*this);
	}

	inline int var::find(var value) {
		castToArray();
		varray& v = *static_cast<varray*>(data);
		int ret = (int)(std::find(v.begin(), v.end(), value)-v.begin());
		if(ret>=(int)v.size()) return -1;
		return ret;
	}

	inline int var::findStrictly(var value) {
		castToArray();
		varray& v = *static_cast<varray*>(data);
		int it = 0;
		for(var el : v) {
			if(el.equalsStrictly(value)) return it;
			++it;
		}
		return -1;
	}

	inline bool var::contains(var value) {
		return find(value)!=-1;
	}

	inline bool var::containsStrictly(var value) {
		return findStrictly(value)!=-1;
	}

	inline bool var::isSubsetOf(var v) {
		varray a = toArray();
		varray b = v.toArray();
		for( var el : a ) {
			if(!containsVarray(b, el)) {
				return false;
			}
		}
		return true;
	}

	inline var var::getCommonElementsWith(var v) {
		varray a = toArray();
		varray b = v.toArray();
		if(a.size() >= b.size()) {
			return var( substractVarrays(a, substractVarrays(a, b)) );
		} else {
			return var ( substractVarrays(b, substractVarrays(b, a)) );
		}
	}

	inline bool var::hasCommonElementsWith(var v) {
		return getCommonElementsWith(v).size() != 0;
	}

	inline bool var::has(var v) {
		return v.isSubsetOf(*this);
	}

	inline bool var::isSameSet(var v) {
		return size()==v.size() && isSubsetOf(v);
	}

	inline void var::reverse() {
		vartypeid t = type;
		std::reverse(begin(), end());
		castToType(t);
	}

	inline void var::pop() {
		vartypeid t = type;
		varray a = toArray();
		if(a.size()>0) {
			a.pop_back();
		}
		operator=(a);
		castToType(t);
	}

	inline void var::push(var v) {
		vartypeid t = type;
		varray a = toArray();
		a.push_back(v);
		operator=(a);
		castToType(t);
	}

	inline void var::pop_front() {
		vartypeid t = type;
		varray a = toArray();
		if(a.size()>0) {
			a.erase(a.begin());
		}
		operator=(a);
		castToType(t);
	}

	inline void var::push_front(var v) {
		vartypeid t = type;
		varray a = toArray();
		a.insert(a.begin(), v);
		operator=(a);
		castToType(t);
	}

	inline void var::sort() {
		vartypeid t = type;
		std::sort(begin(), end());
		castToType(t);
	}

	inline void var::sort(var f) {
		vartypeid t = type;
		std::sort(begin(), end(), [f](const var &a, const var &b) -> bool {
			 return f(a, b).toBool();
		});
		castToType(t);
	}

	inline long long var::hash() {
		switch(type) {
			case VAR_TYPE_FUNCT:
			case VAR_TYPE_UNKNOWN: {
				return getType()*1000+3219;
			}
			default: {
				std::hash<std::string> str_hash;
				return (long long)str_hash(toReadableString());
			}
		}
		return 0;
	}

	inline void var::unique() {
		vartypeid t = type;
		varray a = toArray();
		std::unique(a.begin(), a.end());
		operator=(a);
		castToType(t);
	}

	inline var var::apply(var args) const {
		if(type==VAR_TYPE_FUNCT) {
			return (*(static_cast<var_funct*>(data)))(args);
		}
		return *this;
	}

	inline var var::apply() const {
		return apply(var::newArray());
	}

	inline var var::appliedTo(var f) const {
		return f.apply(*this);
	}

	inline var var::call(var v1, var v2, var v3, var v4, var v5) const {
		return apply({v1, v2, v3, v4, v5});
	}

	inline var var::call(var v1, var v2, var v3, var v4) const {
		return apply({v1, v2, v3, v4});
	}

	inline var var::call(var v1, var v2, var v3) const {
		return apply({v1, v2, v3});
	}

	inline var var::call(var v1, var v2) const {
		return apply({v1, v2});
	}

	inline var var::call(var v1) const {
		return apply({v1});
	}

	inline var var::call() const {
		return apply();
	}

	inline var var::operator()(var v1, var v2, var v3, var v4, var v5) const {
		return apply({v1, v2, v3, v4, v5});
	}

	inline var var::operator()(var v1, var v2, var v3, var v4) const {
		return apply({v1, v2, v3, v4});
	}

	inline var var::operator()(var v1, var v2, var v3) const {
		return apply({v1, v2, v3});
	}

	inline var var::operator()(var v1, var v2) const {
		return apply({v1, v2});
	}

	inline var var::operator()(var v1) const {
		return apply({v1});
	}

	inline var var::operator()() const {
		return apply();
	}

	inline void var::foreachMutate(function<var(var)> callback) {
    switch(type) {
			case VAR_TYPE_REFERENCE: dereference().foreachMutate(callback); break;
			case VAR_TYPE_NULL:
			case VAR_TYPE_NAN:
			case VAR_TYPE_INFINITY:
			case VAR_TYPE_CHAR:
			case VAR_TYPE_INT:
			case VAR_TYPE_DOUBLE:
			case VAR_TYPE_FLOAT:
      case VAR_TYPE_BOOL:
			case VAR_TYPE_FUNCT:
			case VAR_TYPE_LONG_LONG:
        setTo(callback(*this));
      break;
			case VAR_TYPE_STRING: {
				string* ptr = (string*) data;
        const int len = ptr->size();
				for(int i=0;i<len;++i) {
					ptr[i] = callback(var(ptr[i])).toChar();
				}
				break;
			};
			case VAR_TYPE_ARRAY: {
				varray& v = *((varray*)data);
				for(auto& el : v) {
					el = callback(el);
				}
				break;
			};
			case VAR_TYPE_HASHMAP: {
				h_varray& v = *((h_varray*)data);
				for(auto& el : v) {
					el.second = callback(el.second);
				}
				break;
			};
			default: break;
		}
	}

	inline void var::foreachMutate(function<var(var, var)> callback) {
		switch(type) {
			case VAR_TYPE_REFERENCE: dereference().foreachMutate(callback); break;
			case VAR_TYPE_NULL:
			case VAR_TYPE_NAN:
			case VAR_TYPE_INFINITY:
			case VAR_TYPE_CHAR:
			case VAR_TYPE_INT:
			case VAR_TYPE_DOUBLE:
			case VAR_TYPE_FLOAT:
			case VAR_TYPE_BOOL:
			case VAR_TYPE_FUNCT:
			case VAR_TYPE_LONG_LONG:
				setTo(callback(var(0), *this));
			break;
			case VAR_TYPE_STRING: {
				string* ptr = (string*) data;
				const int len = ptr->size();
				for(int i=0;i<len;++i) {
					ptr[i] = callback(var(i), var(ptr[i])).toChar();
				}
				break;
			};
			case VAR_TYPE_ARRAY: {
				varray& v = *((varray*)data);
				int index = 0;
				for(auto& el : v) {
					el = callback(var(index), el);
					++index;
				}
				break;
			};
			case VAR_TYPE_HASHMAP: {
				h_varray& v = *((h_varray*)data);
				for(auto& el : v) {
					el.second = callback(var(el.first), el.second);
				}
				break;
			};
			default: break;
		}
	}

	inline void var::foreach(function<void(var)> callback) {
		foreachMutate((function<var(var)>)([callback](var value)->var{callback(value); return value;}));
	}

	inline void var::foreach(function<void(var, var)> callback) {
		foreachMutate((function<var(var, var)>)([callback](var key, var value)->var{callback(key, value); return value;}));
	}

	inline void var::eachMax(var t) {
		eachMutate(x, (x>t)?(x):(t));
	}

	inline void var::eachMin(var t) {
		eachMutate(x, (x<t)?(x):(t));
	}

	inline void var::eachSet(var t) {
		eachMutate(x, t);
	}

	inline void var::eachGetKey() {
		eachMutateKey(x, key);
	}

	inline void var::eachAdd(var t) {
		eachMutate(x, x+t);
	}

	inline void var::eachDivide(var t) {
		eachMutate(x, x/t);
	}

	inline void var::eachSubstract(var t) {
		eachMutate(x, x-t);
	}

	inline void var::eachMultiply(var t) {
		eachMutate(x, x*t);
	}

	inline void var::eachConvertToNumber() {
		eachMutate(x, x.toDouble());
	}

	inline void var::eachConvertToString() {
		eachMutate(x, x.toString());
	}
	//
	inline void var::eachConvertToLongLong() {
		eachMutate(x, x.toLongLong());
	}

	inline void var::eachConvertToInteger() {
		eachMutate(x, x.toInt());
	}

	inline void var::eachConvertToChar() {
		eachMutate(x, x.toChar());
	}

	inline void var::eachConvertToDouble() {
		eachMutate(x, x.toDouble());
	}

	inline void var::eachConvertToFloat() {
		eachMutate(x, x.toFloat());
	}

	inline void var::eachConvertToArray() {
		eachMutate(x, x.asArray());
	}

	inline void var::eachConvertToHashmap() {
		eachMutate(x, x.asHashmap());
	}

	inline void var::eachConvertToFunction() {
		eachMutate(x, x.asFunction());
	}

	inline void var::eachApply(var args) {
		eachMutate(x, x.apply(args));
	}

	inline void var::eachApply() {
		eachMutate(x, x.apply());
	}

	inline void var::iterate(var f) {
		eachMutateKey(x, f.call(x, key));
	}

	inline var var::fold(var f, var acc) {
		foreach([&acc, f](var element)->void {
			acc = f(acc, element);
		});
		return acc;
	}

	inline var::varray var::doForeach(function<var(var)> callback, varray obj) {
		for(var& el : obj) {
			el = callback(el);
		}
		return obj;
	}

	inline var::h_varray var::doForeach(function<var(var, var)> callback, h_varray obj) {
		for(auto& el : obj) {
			el.second = callback(var(el.first), el.second);
		}
		return obj;
	}

	inline var::varray var::doForeach(function<var(var, var)> callback, varray obj, varray obj2) {
		varray ret;
		const int size = obj.size();
		const int size2 = obj2.size();
		for(int i=0;i<size;++i) {
			for(int j=0;j<size2;++j) {
				ret.push_back(callback(obj[i], obj2[j]));
			}
		}
		return ret;
	}

	inline var::h_varray var::doForeach(function<var(var, var, var, var)> callback, h_varray obj, h_varray obj2) {
		h_varray ret;
		int nkey = 0;
		for(auto i : obj) {
			for(auto j : obj2) {
				ret[var_typeconversion::genericTypeToString(nkey)] = callback(var(i.first), i.second, var(j.first), j.second);
				++nkey;
			}
		}
		return ret;
	}


	inline string var::getTypeName() const {
		return var::translateTypeName(type);
	}

	inline bool var::isTypeInt() const {
		return type == VAR_TYPE_INT;
	}

	inline bool var::isTypeDouble() const {
		return type == VAR_TYPE_DOUBLE;
	}

	inline bool var::isTypeFloat() const {
		return type == VAR_TYPE_FLOAT;
	}

	inline bool var::isTypeString() const {
		return type == VAR_TYPE_STRING;
	}

	inline bool var::isTypeBool() const {
		return type == VAR_TYPE_BOOL;
	}

	inline bool var::isTypeLongLong() const {
		return type == VAR_TYPE_LONG_LONG;
	}

	inline bool var::isTypeChar() const {
		return type == VAR_TYPE_CHAR;
	}

	inline bool var::isTypeArray() const {
		return type == VAR_TYPE_ARRAY;
	}

	inline bool var::isTypeHashmap() const {
		return type == VAR_TYPE_HASHMAP;
	}

	inline bool var::isTypeNull() const {
		return type == VAR_TYPE_NULL;
	}

	inline bool var::isTypeNaN() const {
		return type == VAR_TYPE_NAN;
	}

	inline bool var::isTypeInfinity() const {
		return type == VAR_TYPE_INFINITY;
	}

	inline bool var::isTypeFunction() const {
		return type == VAR_TYPE_FUNCT;
	}

	inline bool var::isTypeReference() const {
		return type == VAR_TYPE_REFERENCE;
	}

	inline bool var::isInfinity() const {
		return type == VAR_TYPE_INFINITY;
	}

	inline bool var::isTypeOf(var v) const {
		return type == v.type;
	}

	inline bool var::isNaN() const {
		return type == VAR_TYPE_NAN;
	}

	inline bool var::isNull() const {
		return type == VAR_TYPE_NULL;
	}

	inline var& var::castToInt() {
		castToType(VAR_TYPE_INT);
		return *this;
	}

	inline var& var::castToDouble() {
		castToType(VAR_TYPE_DOUBLE);
		return *this;
	}

	inline var& var::castToFloat() {
		castToType(VAR_TYPE_FLOAT);
		return *this;
	}

	inline var& var::castToString() {
		castToType(VAR_TYPE_STRING);
		return *this;
	}

	inline var& var::castToBool() {
		castToType(VAR_TYPE_BOOL);
		return *this;
	}

	inline var& var::castToLongLong() {
		castToType(VAR_TYPE_LONG_LONG);
		return *this;
	}

	inline var& var::castToChar() {
		castToType(VAR_TYPE_CHAR);
		return *this;
	}

	inline var& var::castToArray() {
		castToType(VAR_TYPE_ARRAY);
		return *this;
	}

	inline var& var::castToHashmap() {
		castToType(VAR_TYPE_HASHMAP);
		return *this;
	}

	inline var& var::castToFunction() {
		castToType(VAR_TYPE_FUNCT);
		return *this;
	}

	inline var var::asInt() {
		var ret(*this);
		ret.castToInt();
		return ret;
	}

	inline var var::asDouble() {
		var ret(*this);
		ret.castToDouble();
		return ret;
	}

	inline var var::asFloat() {
		var ret(*this);
		ret.castToFloat();
		return ret;
	}

	inline var var::asString() {
		var ret(*this);
		ret.castToString();
		return ret;
	}

	inline var var::asBool() {
		var ret(*this);
		ret.castToBool();
		return ret;
	}

	inline var var::asLongLong() {
		var ret(*this);
		ret.castToLongLong();
		return ret;
	}

	inline var var::asChar() {
		var ret(*this);
		ret.castToChar();
		return ret;
	}

	inline var var::asArray() {
		var ret(*this);
		ret.castToArray();
		return ret;
	}

	inline var var::asHashmap() {
		var ret(*this);
		ret.castToHashmap();
		return ret;
	}

	inline var var::asFunction() {
		var ret(*this);
		ret.castToFunction();
		return ret;
	}

	inline var var::asType(var::vartypeid t) {
		var ret(*this);
		ret.castToType(t);
		return ret;
	}

	inline var var::asTypeOf(var v) const {
		var ret(*this);
		ret.castToTypeOf(v);
		return ret;
	}

	template <typename T>
	inline void var::assignPointer(T* ptr) {
		this->data = (void*)ptr;
	}

	inline void var::castToType(var::vartypeid castType) {
		if(type == castType) return;
		switch(castType) {
			case VAR_TYPE_REFERENCE: dereference().castToType(castType); break;
			case VAR_TYPE_CHAR: assignValue(toChar(), castType); break;
			case VAR_TYPE_INT: assignValue(toInt(), castType); break;
			case VAR_TYPE_DOUBLE: assignValue(toDouble(), castType); break;
			case VAR_TYPE_FLOAT: assignValue(toFloat(), castType); break;
			case VAR_TYPE_STRING: assignValue(toString(), castType); break;
			case VAR_TYPE_BOOL: assignValue(toBool(), castType); break;
			case VAR_TYPE_LONG_LONG: assignValue(toLongLong(), castType); break;
			case VAR_TYPE_ARRAY: assignValue(toArray(), castType); break;
			case VAR_TYPE_HASHMAP: assignValue(toHashmap(), castType); break;
			case VAR_TYPE_FUNCT: var::newConstFunction(*this); break;
			case VAR_TYPE_NULL: break;
			case VAR_TYPE_NAN: break;
			case VAR_TYPE_INFINITY: break;
			default: return;
			//default: throw var_exception_no_such_operation("castTo(...)", getTypeName().c_str());
		}
		type = castType;
	}

	inline void var::castToTypeOf(const var v) {
		castToType(v.getType());
	}

	template <typename T>
	inline T var::getAutoCastedValue() const {
		return (T)(*static_cast<T*>(this->data));
	}

  template <typename T>
  inline T* var::getAutoCastedPointer() const {
    return (static_cast<T*>(this->data));
  }

	template <typename T>
	inline void var::autoCastTo() {
		T* memalloc = new T;
		(*memalloc) = (T)(*static_cast<T*>(this->data));
		delete this;
		assignPointer(memalloc);
	}

	template <typename T>
	inline void var::assignValue(T val, vartypeid newtype) {
		if(newtype != type || newtype == VAR_TYPE_UNKNOWN) {
			var::delete_(this);
			T* memalloc = new T;
			(*memalloc) = val;
			assignPointer(memalloc);
		} else {
			(*static_cast<T*>(data)) = val;
			//assignPointer(&val);
		}
		type = newtype;
	}

	inline const char* var::c_str() {
		return toString().c_str();
	}

	template <typename T>
	inline void var::operator=(std::initializer_list<T> l) {
		operator=(vector<T>(l));
	}

	inline void var::operator=(short val) {
		assignValue((int)val, VAR_TYPE_INT);
	}

	inline void var::operator=(int val) {
		assignValue(val, VAR_TYPE_INT);
	}

	inline void var::operator=(float val) {
		assignValue(val, VAR_TYPE_FLOAT);
	}

	inline void var::operator=(double val) {
		assignValue(val, VAR_TYPE_DOUBLE);
	}

	inline void var::operator=(string val) {
		assignValue(val, VAR_TYPE_STRING);
	}

	inline void var::operator=(bool val) {
		assignValue(val, VAR_TYPE_BOOL);
	}

	inline void var::operator=(long long val) {
		assignValue(val, VAR_TYPE_LONG_LONG);
	}

	inline void var::operator=(char val) {
		assignValue(val, VAR_TYPE_CHAR);
	}

	inline void var::operator=(var_funct val) {
		assignValue(val, VAR_TYPE_FUNCT);
	}

	template <typename T, int N>
	inline void var::operator=(const T arr[N]) {
		vector<T> vec;
		for(int it=0;it<N;++it) {
			vec.push_back(arr[it]);
		}
		operator=(vec);
	}

	template <typename T>
	inline void var::operator=(vector<T> arr) {
		varray v;
		for( T i : arr ) {
			v.push_back(var(i));
		}
		assignValue(v, VAR_TYPE_ARRAY);
		type = VAR_TYPE_ARRAY;
	}

	template <typename T1, typename T2>
	inline void var::operator=(map<T1, T2> arr) {
		h_varray v;
		for( auto i : arr ) {
			v[i.first] = i.second;
		}
		assignValue(v, VAR_TYPE_HASHMAP);
		type = VAR_TYPE_HASHMAP;
	}

	inline void var::operator=(char val[]) {
		assignValue(string(val), VAR_TYPE_STRING);
	}

	inline void var::operator=(const char val[]) {
		assignValue(string(val), VAR_TYPE_STRING);
	}

	inline void var::operator=(var v) {
		setTo(v);
	}

	template <typename T>
	inline void var::operator=(T* x) {
		assignValue((long long)x, VAR_TYPE_LONG_LONG);
	}

	template <typename T>
	inline void var::operator=(T x) {
		cout<<"[WARN] Experimental generic CONVERSION WAS USED! [T->var] :(\n";cout.flush();
		//setTo(T::toVar(x));
		setTo(var::conversion<T>::toVar(x));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*inline bool var::operator==(var t) const {
		var comp1(*this);
		var comp2(t);
		comp2.asTypeOf(comp1);
		switch(comp1.type) {
			case VAR_TYPE_CHAR: return comp1.toChar()==comp2.toChar();
			case VAR_TYPE_INT: return comp1.toInt()==comp2.toInt(); break;
			case VAR_TYPE_DOUBLE: return comp1.toDouble()==comp2.toDouble(); break;
			case VAR_TYPE_FLOAT: return comp1.toFloat()==comp2.toFloat(); break;
			case VAR_TYPE_STRING: return comp1.toString()==comp2.toString(); break;
			case VAR_TYPE_BOOL: return comp1.toBool()==comp2.toBool(); break;
			case VAR_TYPE_LONG_LONG: return comp1.toLongLong()==comp2.toLongLong();break;
			default: throw var_exception_no_such_operation("operator== [comparsion]", comp1.getTypeName().c_str());
			//default: return false;
		}

	}*/

	inline bool var::equals(var t) const {
		return equalsCast(getGreaterPrecisionType(type, t.type), t);
	}

	inline bool var::anyEquals(var t) const {
		return equalsCast(type, t) || equalsCast(t.type, t);
	}

	inline bool var::dEquals(var t) const {
		return equalsCast(type, t);
	}

	inline bool var::equalsCast(vartypeid type, var t) const {
		var comp1(*this);
		var comp2(t);
		comp2.castToType(type);
		comp1.castToType(type);

		switch(comp1.type) {
			case VAR_TYPE_REFERENCE: return dereferenceConst().equalsCast(type, t); break;
			case VAR_TYPE_CHAR: return comp1.toChar()==comp2.toChar(); break;
			case VAR_TYPE_INT: return comp1.toInt()==comp2.toInt(); break;
			case VAR_TYPE_DOUBLE: return comp1.toDouble()==comp2.toDouble(); break;
			case VAR_TYPE_FLOAT: return comp1.toFloat()==comp2.toFloat(); break;
			case VAR_TYPE_STRING: return comp1.toString()==comp2.toString(); break;
			case VAR_TYPE_BOOL: return comp1.toBool()==comp2.toBool(); break;
			case VAR_TYPE_LONG_LONG: return comp1.toLongLong()==comp2.toLongLong();break;
			case VAR_TYPE_FUNCT: return /*comp1.toFunction()==comp2.toFunction();*/ false; break;
			case VAR_TYPE_ARRAY: {
				varray a = toArray();
				varray b = t.toArray();
				const int size = a.size();
				if(size!=(int)b.size()) return false;
				for(int it=0;it<size;++it) {
					if(!a[it].equals(b[it])) {
						return false;
					}
				}
				return true;
				break;
			}
			case VAR_TYPE_HASHMAP: {
				h_varray a = toHashmap();
				h_varray b = t.toHashmap();
				const int size = a.size();
				if(size!=(int)b.size()) return false;
				for(auto el : a) {
					if(!b.count(el.first)) {
						return false;
					}
				}
				return true;
				break;
			}
			default: throw var_exception_no_such_operation("operator== [comparsion]", comp1.getTypeName().c_str());
			//default: return false;
		}
	}

	inline bool var::equalsStrictly(var v) const {
		if(type != v.type) return false;
		return var::equals(v);
	}

	inline bool var::equalsStrictlySet(var v) const {
		if(type != VAR_TYPE_ARRAY && type != VAR_TYPE_HASHMAP) return equalsStrictly(v);
		if(type != v.type) return false;
		h_varray a = toHashmap();
		h_varray b = v.toHashmap();
		if(a.size() != b.size()) return false;
		for(auto el : a) {
			if(!b.count(el.first)) {
				return false;
			} else {
				if(!el.second.equalsStrictlySet(b[el.first])) {
					return false;
				}
			}
		}
		return true;
	}

	inline bool var::equals(var v, unsigned short level) {
		if(level==0) {
			return equals(v);
		} else if(level==1) {
			return equalsStrictly(v);
		} else if(level>=2) {
			return equalsStrictlySet(v);
		}
		return false;
	}

	inline var& var::operator*() {
		return dereference();
	}

	/*inline var var::operator&() {
		return reference();
	}*/

	/*inline var& var::operator<<(var v) {
		dereference() = (v);
		return *this;
	}*/

	inline var var::operator-() {
		return var::operator_neg( type, *this );
	}

	inline var var::operator!() {
		return var::operator_neg( type, *this );
	}

	inline var var::operator||(var v) {
		return var::operator_or( type, *this, v );
	}

	inline var var::operator&&(var v) {
		return var::operator_and( type, *this, v );
	}

	inline var var::operator&(var v) {
		return var::operator_bitwise_and( type, *this, v );
	}

	inline var var::operator|(var v) {
		return var::operator_bitwise_or( type, *this, v );
	}

	inline var var::operator^(var v) {
		return var::operator_bitwise_xor( type, *this, v );
	}

	inline void var::operator&=(var v) {
		setTo(var(operator&(v)));
	}

	inline void var::operator|=(var v) {
		setTo(var(operator|(v)));
	}

	inline void var::operator^=(var v) {
		setTo(var(operator^(v)));
	}

	inline var var::operator~() {
		return var::operator_bitwise_not( type, *this );
	}

	/*inline var& var::operator[](int index) {
		if(type == VAR_TYPE_HASHMAP) {
			return (*(static_cast<h_varray*>(data)))[var(index)];
		} else {
			castToArray();
			//if((int)(*(static_cast<varray*>(data))).size()<=index || index<0) var_exception_no_such_operation("operator[] [element of array] invalid index", getTypeName().c_str());
			return (*(static_cast<varray*>(data)))[index];
		}
	}

	inline var& var::operator[](std::string key) {
		castToHashmap();
		return (*(static_cast<h_varray*>(data)))[key];
	}

	inline var& var::operator[](const char* key) {
		castToHashmap();
		return (*(static_cast<h_varray*>(data)))[string(key)];
	}*/

	inline var& var::operator[](var key) {
		if(type == VAR_TYPE_HASHMAP) {
			return (*(static_cast<h_varray*>(data)))[key];
		} else if(type == VAR_TYPE_ARRAY) {
			return (*(static_cast<varray*>(data)))[(int)key];
		} else if(type == VAR_TYPE_STRING) {
			castToArray();
			return (*(static_cast<varray*>(data)))[(int)key];
		} else {
			return *this;
		}
	}

	template <typename T>
	inline var& var::operator[](T key) {
			return operator[](var(key));
	}

	inline var var::operator+(var v) {
		return var::operator_add( type, *this, v );
	}

	inline void var::operator+=(var v) {
		setTo(var(operator+(v)));
	}

	inline var var::operator-(var v) {
		return var::operator_sub( type, *this, v );
	}

	inline void var::operator-=(var v) {
		setTo(var(operator-(v)));
	}

	inline var var::operator*(var v) {
		return var::operator_mul( type, *this, v );
	}

	inline void var::operator*=(var v) {
		setTo(var(operator*(v)));
	}

	inline var var::operator/(var v) {
		return var::operator_div( type, *this, v );
	}

	inline void var::operator/=(var v) {
		setTo(var(operator/(v)));
	}

	inline var var::operator%(var v) {
		return var::operator_mod( type, *this, v );
	}

	inline void var::operator%=(var v) {
		setTo(var(operator%(v)));
	}

	inline var var::operator<<(var v) {
		return var::operator_shift_left( type, *this, v );
	}

	inline void var::operator<<=(var v) {
		setTo(var(operator<<(v)));
	}

	inline var var::operator>>(var v) {
		return var::operator_shift_right( type, *this, v );
	}

	inline void var::operator>>=(var v) {
		setTo(var(operator>>(v)));
	}

	inline var& var::operator++() {
		operator+=(var(1).asTypeOf(*this));
		return (*this);
	}

	inline var var::operator++(__attribute__ ((unused)) int dummy_parameter) {
		operator+=(var(1).asTypeOf(*this));
		return (*this);
	}

	inline var& var::operator--() {
		operator-=(var(1).asTypeOf(*this));
		return (*this);
	}

	inline var var::operator--(__attribute__ ((unused)) int dummy_parameter) {
		operator-=(var(1).asTypeOf(*this) );
		return (*this);
	}


	template <typename T>
	inline T var::get() {
		return (T)(*this);
	}

	template <typename T>
	inline var var::operator<(T v) const {
		return var::operator_comparsion_less( type, *this, v );
	}

	template <typename T>
	inline var var::operator>(T v) const {
		return var::operator_comparsion_more( type, *this, v );
	}

	template <typename T>
	inline var var::operator<=(T v) const {
		if(var::operator_comparsion_equal( type, *this, v )) return true;
		return var::operator_comparsion_less( type, *this, v );
	}

	template <typename T>
	inline var var::operator>=(T v) const {
		if(var::operator_comparsion_equal( type, *this, v )) return true;
		return var::operator_comparsion_more( type, *this, v );
	}

	template <typename T>
	inline var var::operator==(T v) const {
		return var::operator_comparsion_equal( type, *this, v );
	}

	inline var var::abs() {
		if((*this)>0) return (*this);
		return -(*this);
	}

	inline var var::neg() {
		return -(*this);
	}

	inline void var::clear() {
		delete_(this);
		type = VAR_TYPE_NULL;
	}

	inline var::iterator var::begin() {
		iterator i(this, 0, size());
		return i;
	}

	inline var::iterator var::end() {
		iterator i(this, size(), size());
		return i;
	}

	var::iterator::iterator(var* v, int i, int m) {
		ptr = v;
		index = i;
		max_index = m;
	}

	var::iterator::iterator(const var::iterator& it) {
		ptr = it.ptr;
		index = it.index;
		max_index = it.max_index;
	}

	var::iterator::~iterator() {

	}

	var::iterator& var::iterator::operator=(const var::iterator& it) {
		ptr = it.ptr;
		index = it.index;
		max_index = it.max_index;
		return (*this);
	}

	bool var::iterator::operator==(const var::iterator& it) const {
		return (ptr == it.ptr && index == it.index);
	}

	bool var::iterator::operator!=(const var::iterator& it) const {
		return !(ptr == it.ptr && index == it.index);
	}

	bool var::iterator::operator<(const var::iterator& it) {
		return (index < it.index);
	}

	bool var::iterator::operator>(const var::iterator& it) {
		return (index > it.index);
	}

	bool var::iterator::operator<=(const var::iterator& it) {
		return (index <= it.index);
	}

	bool var::iterator::operator>=(const var::iterator& it) {
		return (index >= it.index);
	}

	var::iterator& var::iterator::operator++() {
		++index;
		return (*this);
	}

	var::iterator var::iterator::operator++(__attribute__ ((unused)) int i) {
		++index;
		return (*this);
	}

	var::iterator& var::iterator::operator--() {
		if(index>0) --index;
		return (*this);
	}

	var::iterator var::iterator::operator--(__attribute__ ((unused)) int i) {
		if(index>0) --index;
		return (*this);
	}

	var::iterator& var::iterator::operator+=(int i) {
		index += i;
		if(index > max_index) index=max_index;
		return (*this);
	}

	var::iterator var::iterator::operator+(int i) const {
		var::iterator it((var*)0,0,0);
		it.ptr = ptr;
		it.index = index + i;
		it.max_index = max_index;
		if(it.index > it.max_index) it.index = max_index;
		return it;
	}

	var::iterator& var::iterator::operator-=(int i) {
		if(index>0) index -= i;
		return (*this);
	}

	var::iterator var::iterator::operator-(int i) const {
		var::iterator it((var*)0,0,0);
		it.ptr = ptr;
		it.index = index - i;
		it.max_index = max_index;
		if(it.index < 0) it.index = 0;
		return it;
	}

	var::iterator::difference_type var::iterator::operator-(var::iterator it) const {
		return index - it.index + 1;
	}

	var::iterator::reference var::iterator::operator*() const {
		int qq = index;
		if(index==max_index) --qq;
		return (*ptr)[qq];
	}

	var::iterator::pointer var::iterator::operator->() const {
		int qq = index;
		if(index==max_index) --qq;
		return &((*ptr)[qq]);
	}



	/*inline var::varray::iterator var::begin() {
		castToArray();
		//return toArray().begin();
		return ((varray*)data)->begin();
	}

	inline var::varray::iterator var::end() {
		castToArray();
		//return toArray().end();
		return ((varray*)data)->end();
	}*/



NAMESPACE_VAR_END__

/*

 Supports:
 	* int
 	* long long
 	* char
 	* bool
 	* string
 	* float
 	* double

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


*/

#endif
