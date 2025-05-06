# MIT License

# Copyright (c) 2025 QIU YIXIANG

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# util is a library which extends many features in C library.
# It is a collection of utility modules can be easily used and embeded in C programs.
# The Makefile of this project is designed to be simple and easy to include more modules.
# Configuration for makefile

# Configure for verbose mode
VERBOSE 	:= 		0

# Configure for debug mode
DEBUG 		:= 		0

# Configure for Modules (default : all)
# MODULES		:= 		

# Configure for library name
LIB_NAME	:= 		util

# Configure for library build method
# LIB_METHOD	:= 		static
LIB_METHOD	:= 		shared