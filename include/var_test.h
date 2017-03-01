
#define USE_DEFAULT_STRING_BEHAVIOUR
#define NAMESPACE_VAR_BEGIN__ namespace variable {
#define NAMESPACE_VAR_END__ };

#include <ctime>
#include <functional>

NAMESPACE_VAR_BEGIN__

#define vardbg(x) cout<<varstr(x)<<" := "<<(x)<<"\n";
#define vardbgOp1(a, op) cout<<varstr(a)<<" := "<<(a)<<" |-> "<<varstr(op)<<" := "<<(op)<<"\n";
#define varstr(x) #x

void var_profile(function<void(void)> f) {
  clock_t begin = clock();
  f();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC * 1000;
  cout<<"[VAR_PROFILE] Code execution time: "<<elapsed_secs<<" ms\n";
}

NAMESPACE_VAR_END__
