# util
util is a library which extends many features in C library.

It is a collection of utility modules can be easily used and embeded in C programs.The Makefile of this project is designed to be simple and easy to include more modules.

# Quick Start
Everything is managed through Makefile. You can use the command `make help` to show the detailed command to compile and install the project. Here are the all commands list:
```Makefile
USAGE:
	make all	build all modules
	make clean	clean builds
	make list	list all modules
	make help	show this help message
```
You can configure the modules you want in the `config/config.mk` or using all modules by default. After that you can use `make install` to install all the header files. And in your project just include them. And linking with the library `libutil.so` or `libutil.a`.

# Modules
As mentioned above the util library has many modules. Which can be selected by your preference. Below is the overview of the module list and their documents.

- [utest](#): A C Unit Test Framework.
- [argparse](#): A command line argument parsing library.


