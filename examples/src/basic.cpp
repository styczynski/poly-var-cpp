#include <var.h>
#include <var_math.h>
using namespace variable;

int main(void) {

	try {

		/*Performance test*/

		#define vardbg(x) cout<<varstr(x)<<" := "<<(x)<<"\n";
		#define varstr(x) #x

		var x = 0;

		cout << var_math.cos(x) << "\n";

		/*var nan = var::Hashmap;
		nan["foo"] = "bar";
		nan["hello"] = 231;
		var a = nan.ref();
		var ref = {a.ref(), 42};
		var ref2 = {ref.ref(), 69, 25};
		var tree = { {{}, 12, {}}, 42, {{}, 69, {}} };
		vardbg(nan);
		vardbg(ref2);*/



		/*var hm = { 5 };
		hm.castToHashmap();
		hm["patologia"] = "dafcuk";
		hm["5"] = "dafcuk";
		cout<<hm<<"\n";

		var hm2 = hm.deepCopy();
		hm2.eachGetKey();
		cout<<hm<<"\n";
		cout<<hm2<<"\n";

		var a = 20;
		var b = 22;
		cout<<a<<" > "<<b<<" := "<<(a>b)<<"\n";
		cout<<a<<" < "<<b<<" := "<<(a<b)<<"\n";
		cout<<a<<" == "<<b<<" := "<<(a==b)<<"\n";
		a.eachMax(b);
		b.eachMax(a);
		cout<<"a := "<<a<<"\n";
		cout<<"b := "<<b<<"\n";

		variable::var x = 0_var;
		var y = { "4", "5", "2.5", "5", "6", "7" };
		var z = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


		y = "ala ma kota";
		y.castToArray();
		cout<<y<<"\n";
		y.eachConvertToInteger();
		cout<<y<<"\n";
		y.eachAdd(0);
		cout<<y<<"\n";
		y.eachConvertToChar();
		cout<<y<<"\n";
		y.castToString();
		cout<<y<<"\n";*/


	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
