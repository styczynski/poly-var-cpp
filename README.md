# Polymorphic variables in C++

[![Made by Styczynsky Digital Systems][badge sts]][link styczynski]

[![Platform - Node][badge support ccpp]][link styczynski]

Just-for-fun implementation of polymorphic variables in C/C++

```c++
#include <var>
#include <var_math>
#include <var_test>
using namespace variable;

int main(void) {

  /* Constructing a polymorphic-type tree */
	var hmap = var::Hashmap;
	hmap["foo"] = "bar";

	var a = hmap.ref();
	var ref = {a.ref(), 42};
	var ref2 = {ref.ref(), 69, 25};
	var tree = { {{}, 12, {}}, "ala", {{}, 69, {}} };

  vardbg(tree);

	return 0;
}

```

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

[badge sts]: https://img.shields.io/badge/-styczynsky_digital_systems-blue.svg?style=flat-square&logoWidth=20&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABYAAAAXCAYAAAAP6L%2BeAAAABmJLR0QA%2FwD%2FAP%2BgvaeTAAAACXBIWXMAAA7DAAAOwwHHb6hkAAAAB3RJTUUH4AgSEh0nVTTLngAAAB1pVFh0Q29tbWVudAAAAAAAQ3JlYXRlZCB3aXRoIEdJTVBkLmUHAAAAm0lEQVQ4y2Pc%2Bkz2PwMNAAs2wVMzk4jSbJY%2BD6ccEwONACMsKIh1JSEgbXKeQdr4PO1cPPQMZiGkoC7bkCQD7%2Fx7znDn35AOClK9PEJSBbNYAJz999UGrOLocsM0KHB5EZ%2FXPxiVMDAwMDD8SP3DwJA6kFka5hJCQOBcDwMDAwPDm3%2FbGBj%2BbR8tNrFUTbiAB8tknHI7%2FuTilAMA9aAwA8miDpgAAAAASUVORK5CYII%3D

[badge support ccpp]: https://img.shields.io/badge/platform-c%2Fc%2B%2B-blue.svg?style=flat-square&logoWidth=20&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABkAAAAZCAYAAADE6YVjAAAAAXNSR0IArs4c6QAAAARnQU1BAACx%0Ajwv8YQUAAAAJcEhZcwAADsQAAA7EAZUrDhsAAANTSURBVEhLjVRLSJVREJ6bXokeSJGF4CbcGZXQ%0AIoKCWlekbVr4uEIGSpsgzWhTtslsY0LYw0ytbNG7zG5ClC0MScNSaCElhhl2r%2BKDEBK6zTfnzP%2Bf%0A%2B1D68P9nzry%2BmTn%2FNRBj0H8i1PSJKIDwALVVbDdGhlsiEAiIVBvOS5LArAmhq1xcYAjMmyhzVTo1%0Alm6BY1kICQoq3E4%2BfJulK91jpqLY4Ffd5rChuXwrBdOMA%2FmJ9bxJIJQAMN1rsG%2BPh%2BuP8Qrzk%2BoA%0ASZP4q%2FGBHE61pbSk1VCUNQRpHfe%2BvEngPPtwhMaiC14npgRKSRA18O7XrQ6aTMbA6CxdDo%2FaE4OZ%0AhJwT0VTNgVzKy1lrXGDo%2BTJFLT3jYlAS1dsr80VPBfiBMkzPKYbATsTndl4fsAIvJQC8fXLccgSA%0ArIKfNokzOhJf9g%2FLc6L1vcQJCVowPZk30FqxzWrx0O4B1SFxDy%2F6h6iLi8veHAhJjI3GbjoRTSey%0AwErwUZRd%2ByyyvvOr9RD1jUQoq%2FwO2OSMlt1mzCQW4mQi9%2BsAUPQvS%2BMHYjQ8Pk%2Bt78al%2BMH6brFq%0AY%2FgO3SaFBEZPOitwu3Ei2BmQtVS3v5V4hEWai008%2F%2F26URSXGzcJgA4QAOl3YxJwej0wSF0DQ6KL%0Al2OiN4uhsSyhN%2Bf2Sx50hSXxF5EK0iC%2FOsJhmoz8pJmIfo2mCbkPK%2FfVdkpsVvltsQGWBGvwu9Zp%0AFPe4OB4DjmP%2FTPQH7cjBj9PEKRGw8dhdNQuExC2IIrhof1VEi09PW83H5k2ZFK49wndRQv0XCthi%0AasTwqQr8fPnFh5oGpTuDGE3PzdOz6t3eRC5hIrRBxGw4alYk8Wwu2pNLDWW77LpsESR0hF9RuLeX%0AMgrrxbYcAQA%2FnmDBRZqdmpBHhnLSZJLnHyfp8PlbagIbsuW0%2BKRGpDuRqwMgiIdh0VwhgZJd2kjR%0AuQUxxsG4af5%2BFa3MSBcdGJmYprzK614ziagL7aWThTtF90gUSV3BjUIqUwEVHJdOoBAS8CTuPnio%0ALnVxLRjfm8T8eXzKqvG1kibRIwLP8L%2BNS4%2F65Lwcvrccp%2Bz1a%2BwpGR4JxJIXi6kAsXE4MljPSE%2Bj%0A3w%2BqxOUiMT9pEkUiKaCfNYC9JxZz4fuI%2FgGlbtJ34E8YtQAAAABJRU5ErkJggg%3D%3D

[link styczynski]: http://styczynski.in
