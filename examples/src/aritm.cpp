#include <var.h>
#include <var_math.h>
#include <var_test.h>

using namespace variable;

int main(void) {

	try {

		var a = 20;
		var b = 22;
		cout<<a<<" > "<<b<<" := "<<(a>b)<<"\n";
		cout<<a<<" < "<<b<<" := "<<(a<b)<<"\n";
		cout<<a<<" == "<<b<<" := "<<(a==b)<<"\n";
		a.eachMax(b);
		b.eachMax(a);
		vardbg(a);
		vardbg(b);

		variable::var x = 0_var;
		var y = { "4", "5", "2.5", "5", "6", "7" };
		var z = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


		y = "ala ma kota";
		y.castToArray();
		vardbg(y);
		y.eachConvertToInteger();
		vardbg(y);
		y.eachAdd(0);
		vardbg(y);
		y.eachConvertToChar();
		vardbg(y);
		y.castToString();
		vardbg(y);


	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
