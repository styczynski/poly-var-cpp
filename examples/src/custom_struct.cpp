#include <set>
#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

struct custom {
	int a;
	float b;
	string c;
	static var toVar(custom c) {
		cout<<"TOVAR\n";
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

		set<int> s;
		s.insert(1);
		s.insert(13);
		s.insert(5);

		var v = s;
		cout<<v<<"\n";

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
