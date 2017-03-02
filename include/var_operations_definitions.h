
	#define defaultNuberOperationImplementation(OPERATOR) \
		case VAR_TYPE_CHAR: return var( static_cast<char>(a.toChar() OPERATOR b.toChar()) ); \
		case VAR_TYPE_INT: return var( a.toInt() OPERATOR b.toInt() ); \
		case VAR_TYPE_DOUBLE: return var( a.toDouble() OPERATOR b.toDouble() ); \
		case VAR_TYPE_FLOAT: return var( a.toFloat() OPERATOR b.toFloat() ); \
		case VAR_TYPE_LONG_LONG: return var( a.toLongLong() OPERATOR b.toLongLong() );

	#define defaultNuberOperationImplementationFunct(OPERATOR) \
		case VAR_TYPE_CHAR: return ( static_cast<char>( OPERATOR ( a.toChar(), b.toChar() )) ); \
		case VAR_TYPE_INT: return ( OPERATOR ( a.toInt(), b.toInt() )); \
		case VAR_TYPE_DOUBLE: return ( OPERATOR ( a.toDouble(), b.toDouble() )); \
		case VAR_TYPE_FLOAT: return ( OPERATOR ( a.toFloat(), b.toFloat() )); \
		case VAR_TYPE_LONG_LONG: return ( OPERATOR ( a.toLongLong(), b.toLongLong() ));

	#define defaultNuberNegationImplementation() \
		case VAR_TYPE_CHAR: return var( -a.toChar() ); \
		case VAR_TYPE_INT: return var( -a.toInt() ); \
		case VAR_TYPE_DOUBLE: return var( -a.toDouble() ); \
		case VAR_TYPE_FLOAT: return var( -a.toFloat() ); \
		case VAR_TYPE_LONG_LONG: return var( -a.toLongLong() );

	#define calculateSafetyDiv(X,Y) (((X)==0&&(Y)==0)?(var::newNaN()):(((Y)==0)?(var::newInfinity()):(var((X)/(Y)))))
	#define calculateSafetyMod(X,Y) (((X)==0&&(Y)==0)?(var::newNaN()):(((Y)==0)?(var::newInfinity()):(var((X)%(Y)))))
	#define calculateSafetyModF(X,Y) (((X)==0&&(Y)==0)?(var::newNaN()):(((Y)==0)?(var::newInfinity()):(var((float)fmod((X),(Y))))))
	#define calculateSafetyModD(X,Y) (((X)==0&&(Y)==0)?(var::newNaN()):(((Y)==0)?(var::newInfinity()):(var((double)fmod((X),(Y))))))

	#define autohandle_references_1(X) \
		if(X.type==VAR_TYPE_REFERENCE) { \
			X = X.dereferenceConst(); \
			t = X.type; \
		}
 	#define autohandle_references_2(X1, X2) \
		if(X1.type==VAR_TYPE_REFERENCE) { \
			X1 = X1.dereferenceConst(); \
			t = X1.type; \
		} \
		if(X2.type==VAR_TYPE_REFERENCE) { \
			X2 = X2.dereferenceConst(); \
		}

	#define autohandle_functions_2(X1, X2, FUNCT) \
		if(X1.type==VAR_TYPE_FUNCT || X2.type==VAR_TYPE_FUNCT) { \
			return var_funct_decl({ \
				const var v1 = X1.apply(args); \
				const var v2 = X2.apply(args); \
				return FUNCT(v1.getType(), v1, v2, take_greater_precision_operation); \
			}); \
		}

	#define autohandle_functions_1(X1, FUNCT) \
		if(X1.type==VAR_TYPE_FUNCT) { \
			return var_funct_decl({ \
				const var v1 = X1.apply(args); \
				return FUNCT(v1.getType(), v1); \
			}); \
		}

	#define autohandle_Null if(a.isTypeNull() || b.isTypeNull()) return var::newNull();
	#define autohandle_NaN if(a.isTypeNaN() || b.isTypeNaN()) return var::newNaN();
	#define autohandle_Infinity if(a.isTypeInfinity() || b.isTypeInfinity()) return var::newInfinity();
	#define autohandle_Null_single if(a.isTypeNull()) return var::newNull();
	#define autohandle_NaN_single if(a.isTypeNaN()) return var::newNaN();
	#define autohandle_Infinity_single if(a.isTypeInfinity()) return var::newInfinity();

	#define greaterPrecision if(getGreaterPrecisionType(t, a.type, b.type)!=t && take_greater_precision_operation)


	inline var var::operator_add( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_add);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_add(b.type, a, b, false);
		}

		#ifdef USE_DEFAULT_STRING_BEHAVIOUR
			if(a.isTypeArray() || b.isTypeArray()) {
				return var( mergeVarrays( a.toArray(), b.toArray() ) );
			}
			if(a.isTypeHashmap() || b.isTypeHashmap()) {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
			}
			if(a.isTypeString() || b.isTypeString()) {
				return var( a.toString() + b.toString() );
			}
		#endif

		switch( t ) {
			defaultNuberOperationImplementation(+)

			#ifdef USE_DEFAULT_STRING_BEHAVIOUR
				case VAR_TYPE_STRING: return operator_add(b.type, a, b, false);
			#else
				case VAR_TYPE_STRING: return var( a.toString() + b.toString() );
			#endif
			case VAR_TYPE_BOOL: return var( a.toBool() || b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( mergeVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator+ ", a.getTypeName().c_str());
		}
		return var( 0 );
	}



	inline var var::operator_sub( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_sub);
		autohandle_Null
		autohandle_NaN

		if(a.isTypeInfinity() && b.isTypeInfinity()) return var::newNaN();
		if(a.isTypeInfinity() || b.isTypeInfinity()) return var::newInfinity();

		greaterPrecision {
			return operator_sub(b.type, a, b, false);
		}

		#ifdef USE_DEFAULT_STRING_BEHAVIOUR
			if(a.isTypeString() && b.isTypeString()) {
				return var( a.toDouble() - b.toDouble() );
			}
		#endif

		switch( t ) {
			defaultNuberOperationImplementation(-)
			#ifdef USE_DEFAULT_STRING_BEHAVIOUR
				case VAR_TYPE_STRING: return operator_sub(b.type, a, b, false);
			#else
				case VAR_TYPE_STRING: {
					string str_a = a.toString();
					const string str_b = b.toString();
					std::string::size_type i = str_a.find(str_b);
					if (i != std::string::npos)
					   str_a.erase(i, str_b.length());

					return var(str_a);
				}
			#endif
			case VAR_TYPE_BOOL: return var(a.toBool() && (!b.toBool()) );
			case VAR_TYPE_HASHMAP: {
				return var( substractHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( substractVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator- ", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_mul( var::var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_mul);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_mul(b.type, a, b, false);
		}

		#ifdef USE_DEFAULT_STRING_BEHAVIOUR
			if(a.isTypeString() && b.isTypeString()) {
				return var( a.toDouble() * b.toDouble() );
			}
		#endif

		switch( t ) {
			defaultNuberOperationImplementation(*)
			#ifdef USE_DEFAULT_STRING_BEHAVIOUR
				case VAR_TYPE_STRING: return operator_mul(b.type, a, b, false);
			#else
				case VAR_TYPE_STRING: {
					int rep = b.toInt();
					if(rep<=0) return var("");
					const string str_a = a.toString();
					string ret = str_a;
					for(int it=0;it<rep-1;++it) {
						ret += str_a;
					}
					return var(ret);
				}
			#endif
			case VAR_TYPE_BOOL: return var( a.toBool() && b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return doForeach([=](var a, var b){
					return a*b;
				}, a.toArray(), b.toArray());
				//return var( mergeVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator* ", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_div( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_div);
		autohandle_Null
		autohandle_NaN

		if(a.isTypeInfinity() && b.isTypeInfinity()) return var::newNaN();
		if(a.isTypeInfinity() || b.isTypeInfinity()) return var::newInfinity();


		greaterPrecision {
			return operator_div(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( calculateSafetyDiv( a.toDouble(), b.toDouble() ) );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return calculateSafetyDiv(a.toChar(), b.toChar());
			case VAR_TYPE_INT: return calculateSafetyDiv(a.toInt(), b.toInt());
			case VAR_TYPE_DOUBLE: return calculateSafetyDiv(a.toDouble(), b.toDouble());
			case VAR_TYPE_FLOAT: return calculateSafetyDiv(a.toFloat(), b.toFloat());
			case VAR_TYPE_LONG_LONG: calculateSafetyDiv(a.toLongLong(), b.toLongLong());
			case VAR_TYPE_STRING: return operator_div(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( !(!a.toBool() && b.toBool()) );
			case VAR_TYPE_HASHMAP: {
				return var( divideHVarays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( divideVarays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator/ ", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_neg( var::vartypeid t, var a ) {

		autohandle_references_1(a);
		autohandle_functions_1(a, var::operator_neg);
		autohandle_Null_single
		autohandle_NaN_single
		autohandle_Infinity_single

		switch( t ) {
			defaultNuberNegationImplementation()
			case VAR_TYPE_STRING: return var( -a.toDouble() );
			case VAR_TYPE_BOOL: return var( !(a.toBool()) );
			case VAR_TYPE_HASHMAP: {
				return var( a.toHashmap() );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( a.toArray() );
				break;
			}
			default: throw var_exception_no_such_operation("operator- [sign negation] ", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_or( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_or);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		return var(a.toBool() || b.toBool());
	}

	inline var var::operator_and( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_and);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		return var(a.toBool() && b.toBool());
	}


	inline var var::operator_mod( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_mod);
		autohandle_Null
		autohandle_NaN

		if(b.isTypeInfinity()) return a;
		if(a.isTypeInfinity()) return var::newNaN();


		greaterPrecision {
			return operator_mod(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( calculateSafetyModD( a.toDouble(), b.toDouble() ) );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return calculateSafetyMod(a.toChar(), b.toChar());
			case VAR_TYPE_INT: return calculateSafetyMod(a.toInt(), b.toInt());
			case VAR_TYPE_DOUBLE: return calculateSafetyModD(a.toDouble(), b.toDouble());
			case VAR_TYPE_FLOAT: return calculateSafetyModF(a.toFloat(), b.toFloat());
			case VAR_TYPE_LONG_LONG: calculateSafetyMod(a.toLongLong(), b.toLongLong());
			case VAR_TYPE_STRING: return operator_mod(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toInt() % b.toInt() );
			case VAR_TYPE_HASHMAP: {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( mergeVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator% ", a.getTypeName().c_str());
		}
		return var( 0 );

	}



	inline var var::operator_shift_left( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_shift_left);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_shift_left(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( a.toDouble() * pow(2.0, b.toDouble()) );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() << b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() << b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toDouble() * pow(2.0, b.toDouble()) );
			case VAR_TYPE_FLOAT: return var( (float)(a.toDouble() * pow(2.0, b.toDouble())) );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() << b.toLongLong() );
			case VAR_TYPE_STRING: return operator_shift_left(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toBool() << b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( mergeVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator<< ", a.getTypeName().c_str());
		}
		return var( 0 );
	}


	inline var var::operator_shift_right( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_shift_right);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_shift_right(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( a.toDouble() / pow(2.0, b.toDouble()) );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() >> b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() >> b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toDouble() / pow(2.0, b.toDouble()) );
			case VAR_TYPE_FLOAT: return var( (float)(a.toDouble() / pow(2.0, b.toDouble())) );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() >> b.toLongLong() );
			case VAR_TYPE_STRING: return operator_shift_right(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toBool() >> b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( mergeHVarrays( a.toHashmap(), b.toHashmap() ) );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( mergeVarrays( a.toArray(), b.toArray() ) );
				break;
			}
			default: throw var_exception_no_such_operation("operator>> ", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_bitwise_not( var::vartypeid t, var a ) {

		autohandle_references_1(a);
		autohandle_functions_1(a, var::operator_bitwise_not);
		autohandle_Null_single
		autohandle_NaN_single
		autohandle_Infinity_single

		switch( t ) {
			case VAR_TYPE_CHAR: return var( ~a.toChar() );
			case VAR_TYPE_INT: return var( ~a.toInt() );
			case VAR_TYPE_DOUBLE: return var( ~a.toInt() );
			case VAR_TYPE_FLOAT: return var( ~a.toInt() );
			case VAR_TYPE_LONG_LONG: return var( ~a.toLongLong() );
			case VAR_TYPE_STRING: return var( ~a.toInt() );
			case VAR_TYPE_BOOL: return var( ~a.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var(a.toHashmap());
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var(a.toArray());
				break;
			}
			default: throw var_exception_no_such_operation("operator~ [bitwise not]", a.getTypeName().c_str());
		}
		return var( 0 );
	}

	inline var var::operator_bitwise_and( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_bitwise_and);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_bitwise_and(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( a.toInt() & b.toInt() );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() & b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() & b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toInt() & b.toInt() );
			case VAR_TYPE_FLOAT: return var( a.toInt() & b.toInt() );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() & b.toLongLong() );
			case VAR_TYPE_STRING: return operator_bitwise_and(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toBool() & b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( a.toHashmap() );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( a.toArray() );
				break;
			}
			default: throw var_exception_no_such_operation("operator& [bitwise and]", a.getTypeName().c_str());
		}
		return var( 0 );
	}


	inline var var::operator_bitwise_or( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_bitwise_or);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_bitwise_or(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( a.toInt() | b.toInt() );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() | b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() | b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toInt() | b.toInt() );
			case VAR_TYPE_FLOAT: return var( a.toInt() | b.toInt() );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() | b.toLongLong() );
			case VAR_TYPE_STRING: return operator_bitwise_or(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toBool() | b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( a.toHashmap() );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( a.toArray() );
				break;
			}
			default: throw var_exception_no_such_operation("operator| [bitwise or]", a.getTypeName().c_str());
		}
		return var( 0 );
	}


	inline var var::operator_bitwise_xor( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_bitwise_xor);
		autohandle_Null
		autohandle_NaN
		autohandle_Infinity

		greaterPrecision {
			return operator_bitwise_xor(b.type, a, b, false);
		}

		if(a.isTypeString() && b.isTypeString()) {
			return var( a.toInt() ^ b.toInt() );
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() ^ b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() ^ b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toInt() ^ b.toInt() );
			case VAR_TYPE_FLOAT: return var( a.toInt() ^ b.toInt() );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() ^ b.toLongLong() );
			case VAR_TYPE_STRING: return operator_bitwise_xor(b.type, a, b, false);
			case VAR_TYPE_BOOL: return var( a.toBool() ^ b.toBool() );
			case VAR_TYPE_HASHMAP: {
				return var( a.toHashmap() );
				break;
			}
			case VAR_TYPE_ARRAY: {
				return var( a.toArray() );
				break;
			}
			default: throw var_exception_no_such_operation("operator^ [bitwise xor]", a.getTypeName().c_str());
		}
		return var( 0 );
	}



	inline var& var::operator_iterate( var::vartypeid t, var a, int index ) {

		autohandle_references_1(a);
		a.castToArray();
		switch( t ) {
			/*case VAR_TYPE_CHAR: a.castToString(); return var(a.getAutoCastedValue<string>()[index]);
			case VAR_TYPE_INT: a.castToString(); return a.getAutoCastedValue<string>()[index];
			case VAR_TYPE_DOUBLE: a.castToString(); return a.getAutoCastedValue<string>()[index];
			case VAR_TYPE_FLOAT: a.castToString(); return a.getAutoCastedValue<string>()[index];
			case VAR_TYPE_LONG_LONG: a.castToString(); return a.getAutoCastedValue<string>()[index];
			case VAR_TYPE_STRING: return a.getAutoCastedValue<string>()[index];
			case VAR_TYPE_BOOL: a.castToString(); return a.getAutoCastedValue<string>()[index];*/
			case VAR_TYPE_ARRAY: {
				return (a.toArray())[index];
			}
			default: throw var_exception_no_such_operation("operator[] [iteration operator]", a.getTypeName().c_str());
		}
	}




	inline var var::operator_comparsion_less( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_comparsion_less);

		if(a.getType() == VAR_TYPE_INFINITY || b.getType() == VAR_TYPE_INFINITY) return false;
		if(a.getType() == VAR_TYPE_NAN || b.getType() == VAR_TYPE_NAN) return false;
		if(a.getType() == VAR_TYPE_NULL || b.getType() == VAR_TYPE_NULL) return false;


		greaterPrecision {
			return operator_comparsion_less(b.type, a, b, false);
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() < b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() < b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toInt() < b.toInt() );
			case VAR_TYPE_FLOAT: return var( a.toFloat() < b.toFloat() );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() < b.toLongLong() );
			case VAR_TYPE_STRING: return var( a.toString() < b.toString() );
			case VAR_TYPE_BOOL: return var( a.toBool() < b.toBool() );
			case VAR_TYPE_ARRAY: {
				return a.size() < b.size();
				break;
			}
			default: throw var_exception_no_such_operation("operator< [less (than)]", a.getTypeName().c_str());
		}
		return var( false );
	}


	inline var var::operator_comparsion_more( var::vartypeid t, var a, var b, bool take_greater_precision_operation ) {

		autohandle_references_2(a, b);
		autohandle_functions_2(a, b, var::operator_comparsion_more);

		if(a.getType() == VAR_TYPE_INFINITY || b.getType() == VAR_TYPE_INFINITY) return false;
		if(a.getType() == VAR_TYPE_NAN || b.getType() == VAR_TYPE_NAN) return false;
		if(a.getType() == VAR_TYPE_NULL || b.getType() == VAR_TYPE_NULL) return false;


		greaterPrecision {
			return operator_comparsion_more(b.type, a, b, false);
		}

		switch( t ) {
			case VAR_TYPE_CHAR: return var( a.toChar() > b.toChar() );
			case VAR_TYPE_INT: return var( a.toInt() > b.toInt() );
			case VAR_TYPE_DOUBLE: return var( a.toInt() > b.toInt() );
			case VAR_TYPE_FLOAT: return var( a.toFloat() > b.toFloat() );
			case VAR_TYPE_LONG_LONG: return var( a.toLongLong() > b.toLongLong() );
			case VAR_TYPE_STRING: return var( a.toString() > b.toString() );
			case VAR_TYPE_BOOL: return var( a.toBool() > b.toBool() );
			case VAR_TYPE_ARRAY: {
				return a.size() > b.size();
				break;
			}
			default: throw var_exception_no_such_operation("operator> [more (than)]", a.getTypeName().c_str());
		}
		return var( false );
	}


	inline var var::operator_comparsion_equal( var::vartypeid t, var a, var b, bool take_greater_precision_operation) {
		return a.equals(b);
		//return (!var::operator_comparsion_less(t, a, b).toBool() && !var::operator_comparsion_more(t, a, b).toBool());
	}


	#undef defaultNuberOperationImplementation
	#undef defaultNuberOperationImplementationFunct
	#undef defaultNuberNegationImplementation
	#undef calculateSafetyDiv
	#undef calculateSafetyMod
	#undef calculateSafetyModF
	#undef calculateSafetyModD
	#undef autohandle_Null
	#undef autohandle_NaN
	#undef autohandle_Infinity
	#undef autohandle_Null_single
	#undef autohandle_NaN_single
	#undef autohandle_Infinity_single
	#undef greaterPrecision
