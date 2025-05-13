# util
util is a C library that extends the standard C library by providing additional utility modules. 

The library is designed to be lightweight and modular, making it easy to embed in C programs. The Makefile for this project is simple and customizable, allowing developers to add or remove modules as needed.

# Quick Start
Everything is managed through Makefile. You can use the command `make help` to show the detailed command to compile and install the project. Here are the all commands list:
```Makefile
USAGE:
	make all	build all modules
	make clean	clean builds
	make list	list all modules
	make help	show this help message
```
You can configure the modules you need in the config/config.mk file. By default, all modules are included. Then use `make install` to install all the header files, in your project just include them.

# Modules
The util library includes several modules that can be selected based on your requirements. Below is an overview of the available modules:



# Contributing
Welcome contributions! Feel free to open issues or submit pull requests to help improve this project.

# License
This project is licensed under the [MIT License](https://github.com/unsigend/util/blob/main/LICENSE). 
Copyright (C) 2025 - 2026 QIU YIXIANG
