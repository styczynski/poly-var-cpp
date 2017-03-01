
	#define VAR_INFINITY (var::newInfinity())
	#define VAR_NAN (var::newNaN())
	#define VAR_NULL (var::newNull())

	#define declareOperatorOverload(OPERATOR, TYPENAME) \
		inline var operator OPERATOR (TYPENAME a, var b); \
		inline var operator OPERATOR (var a, TYPENAME b); \
		
	#define declareOperatorOverloadT(TEMPLATE, OPERATOR, TYPENAME) \
		template <typename TEMPLATE> \
		inline var operator OPERATOR (TYPENAME a, var b); \
		template <typename TEMPLATE> \
		inline var operator OPERATOR (var a, TYPENAME b);				
		
						
		
	/*template <typename T>
	inline var operator-(T a, var b);
	
	template <typename T>
	inline var operator*(T a, var b);
	
	template <typename T>
	inline var operator/(T a, var b);
	
	template <typename T>
	inline var operator%(T a, var b);
	
	template <typename T>
	inline var operator&(T a, var b);
	
	template <typename T>
	inline var operator|(T a, var b);
	
	template <typename T>
	inline var operator^(T a, var b);
	
	template <typename T>
	inline var operator+(var a, T b);
	
	template <typename T>
	inline var operator-(var a, T b);
	
	template <typename T>
	inline var operator*(var a, T b);
	
	template <typename T>
	inline var operator/(var a, T b);
	
	template <typename T>
	inline var operator%(var a, T b);
	
	template <typename T>
	inline var operator|(var a, T b);
	
	template <typename T>
	inline var operator&(var a, T b);
	
	template <typename T>
	inline var operator^(var a, T b);
	
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
	declareOperatorOverloadT(T, ||, vector<T>);*/
	
	inline ostream& operator<<(ostream &out, var v);
	
	inline istream& operator>>(istream &in, var& v);


