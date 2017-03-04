#include <var.h>
#include <var_math.h>
#include <var_test.h>

using namespace variable;

int main(void) {

	try {

		var list = {1, 2, {"I", "am", "a", "good", "programmer"}, {"Hello"}, 56.9, var::Null};
		std::sort( list.begin(), list.end() );
		cout<<list<<"\n";

		var str = "Im good one";
		str.reverse();
		cout<<str<<"\n";

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
