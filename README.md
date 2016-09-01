# unity-template-project
This is a unity-framework template project.
This is actually the enhanced version of it with the extras on top.

The original unity framework consists of 3 files unity.c, unity.h and unity_internals.h which are located in unity-framework-src/src

In order to make unity more like CppUTest there are also the stuff on unity-framework-src/extras/fixture/src.

There are 4 main folders:
1) include folder: Here we put the production code header files
2) src folder: Here we put the production code source files without the main.c file (TODO: check this more thoroughly)
3) unity-framework-src folder: Here are all the unity files that we need to use the framework plus some examples. More details on this further down.
4) unity-unit-tests: Here we put the test code.

unity-framework-src contains the following:
3 examples
unity source files and test code to test them
extras to make it look like cpputest and the test code to test these
Some automation scripts that work with ruby plus some config files for the ruby scripts in yml format
Some docs
