# poly-var-cpp
Just-for-fun implementation of polymorphic variables in C/C++

## Usage

Clone the repository, go to the directory where it's placed
and do `make` to get information about functionality of makefile.

If you want to compile all examples do `make all`
And then run any of the examples by running  `make run-example-aritm`, `make run-example-tree` etc.

The basic usage looks like this:

```c++
#include <var>
using namespace variable;

int main() {
  var x = 0;
  x += "2.5";
  cout<<x<<"\n";

  return 0;
}
```

Or if you want to use printf/scanf style:

```c++
#include <var>
using namespace variable;

int main() {
  var x = 0;
  x += "2.5";
  printf("%d", (int)x);

  return 0;
}
```

You can read the standard input too (floats for example):

```c++
  var x;
  cin >> x.castToFloat();
```

Or:
```c++
  var x;
  scanf("%f", (float*)x);
```


## More examples

Checkout examples/src for details about functionality of the module.
Also you can see ./include/var.h to get more details.
