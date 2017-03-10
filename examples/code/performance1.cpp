#include <var>
#include <var_math>
#include <var_test>

using namespace variable;

int main(void) {

	try {

		var_profile([]()->void {
        var k;
        for(var i=0;i<10000;++i) {
          k = 0;
          k = "ala";
        }
    });

	} catch(var_exception e) {
		cout<<"[Exception] "<<e.what()<<"\n";
	}

	return 0;
}
