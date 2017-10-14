#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

int main(void) {

	try {

		while(true) {
			var a = "";
			cin>>a.castToString();
			a.castToArray();
			for(var el : a) {
				cout<<"# => "<<el<<"\n";
			}
			a.sort();
			cout<<"sorted string := "<<a<<"\n";
		}

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
