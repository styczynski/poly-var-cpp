#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

int main(void) {

	try {

		var hm = { 5 };
		hm.castToHashmap();
		hm["patologia"] = "dafcuk";
		hm["5"] = "dafcuk";
		vardbg(hm);

		var hm2 = hm.deepCopy();
		hm2.eachGetKey();
		vardbg(hm);
		vardbg(hm2);


	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
