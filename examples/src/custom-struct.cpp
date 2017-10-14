#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

struct custom {
	int a;
	float b;
	string c;

	static var toVar(custom c) {
		var ret = var::Hashmap;
		ret["a"] = c.a;
		ret["b"] = c.b;
		ret["c"] = c.c;
		return ret;
	}

	static custom fromVar(var v) {
		custom ret;
		ret.a = v["a"].toInt();
		ret.b = v["b"].toFloat();
		ret.c = v["c"].toString();
		return ret;
	}

};


int main(void) {

	try {


		custom custom_obj = {0, 0.5, "ala"};
		var x = custom_obj;
		vardbg(x);
		x["a"] = 123;
		custom_obj = x;
		cout<<"custom_obj.a = "<<custom_obj.a<<"\n";
		cout<<"custom_obj.b = "<<custom_obj.b<<"\n";
		cout<<"custom_obj.c = "<<custom_obj.c<<"\n";

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
