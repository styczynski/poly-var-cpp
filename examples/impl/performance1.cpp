#include <var.h>
#include <var_math.h>
#include <var_test.h>

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
