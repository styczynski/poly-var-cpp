NAMESPACE_VAR_BEGIN__

class var_exception: public exception {
	private:
		const char* message = nullptr;
		
	protected:
		
		inline void setMessage(const char* argMessage) {
			message = argMessage;
		}
		
	public:
		
		var_exception() {
			
		}
		
		var_exception(const char* argMessage) {
			message = argMessage;
		}
	
		inline virtual const char* what() const throw() {
			return message;
		}
		
		inline const char* getMessage() {
			return message;
		}
	
};

class var_exception_no_such_operation: public var_exception {
	private:
		char* opname;
		char* optypename;
	
	public:
	
		var_exception_no_such_operation(const char* operation_name, const char* operation_typename) : var_exception() {
			char* opname = nullptr;
			char* optypename = nullptr;
			char* buffer = nullptr;
			opname =    (char*)malloc(80);
			optypename = (char*)malloc(80);
			strcpy(opname, operation_name);
			strcpy(optypename, operation_typename);
			const char* basic_result_prefix = "Operation is not supported (";
			const char* basic_result_postfix = "]. Please verify your code. ";
			buffer = (char*)malloc(160);
			strcpy(buffer, basic_result_prefix);
			strcat(buffer, opname);
			strcat(buffer, ") on type [");
			strcat(buffer, optypename);
			strcat(buffer, basic_result_postfix);
			setMessage(buffer);
		}
};

NAMESPACE_VAR_END__
