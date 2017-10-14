#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

int main(void) {

	try {

		var nan = var::Hashmap;
		nan["foo"] = "bar";
		nan["hello"] = 231;
		var a = nan.ref();
		var ref = {a.ref(), 42};
		var ref2 = {ref.ref(), 69, 25};
		var tree = { {{}, 12, {}}, "ala", {{}, 69, {}} };
		vardbg(nan);
		vardbg(ref2);

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
