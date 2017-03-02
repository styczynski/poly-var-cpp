#include <var.h>
#include <var_math.h>
#include <var_test.h>

using namespace variable;

int main(void) {

	try {

		var funct_pow = var::newWrapperFunction2<double,double,double>(std::pow);
		var funct_sqrt = var::newWrapperFunction1<double,double>      (std::sqrt);

		var funct_print = var_funct_decl({
			for( var x : args ) {
				cout<<"-> "<<x<<"\n";
			}
			return var::Null;
		});

		while(true) {
			var a = 0;
			var b = 0;
			cin>>a.castToDouble();
			cin>>b.castToDouble();
			cout<<var({ funct_sqrt.apply(a), funct_sqrt.apply(b)})<<"\n";cout.flush();
			cout<<funct_pow.apply({a, b})<<"\n";
		}

		//cout<<funct_print.apply({"ala", {13.5, '$', "wuteef", var::Function}, 16.5})<<"\n";

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
