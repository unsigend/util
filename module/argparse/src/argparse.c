/**
 * MIT License
 * 
 * Copyright (c) 2025 QIU YIXIANG
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * Implementation of argparse library
 * Part of the util library project
 */

#include <argparse.h>

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>





void argparse_init(argparse *this, argparse_option *option_list, const char *program_name){
    this->_argc = 0;
    this->_argv = NULL;
    this->_option_list = option_list;
    this->_program_name = program_name;
    this->_description = NULL;
    this->_epilog = NULL;
    this->_flags = ARGPARSE_FLAG_STOP_UNKNOWN_OPTION;
}

void argparse_set_flags(argparse *this, argparse_flag flags){
    this->_flags = flags;
}

void argparse_add_description(argparse *this, const char *description, const char *epilog){
    this->_description = description;
    this->_epilog = epilog;
}


void argparse_parse(argparse *this, int argc, char *argv[]);
