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

/**
 * @brief: Internal Macros
 */
#define ASCII_COLOR_RED     "\033[31m"
#define ASCII_COLOR_GREEN   "\033[32m"
#define ASCII_COLOR_YELLOW  "\033[33m"
#define ASCII_COLOR_BLUE    "\033[34m"
#define ASCII_COLOR_MAGENTA "\033[35m"
#define ASCII_COLOR_CYAN    "\033[36m"
#define ASCII_COLOR_RESET   "\033[0m"

/**
 * @brief: Private functions implementation
 */

/**
 * @brief: help information display functions
 */
static void argparse_show_option_list(argparse *this){

}

static void argparse_show_all(argparse *this){
    // show the description
    if (this->_description)
        fprintf(stdout, "Overview : %s\n\n", this->_description);

    // show the program name
    if (this->_program_name)
        fprintf(stdout, "USAGE: %s ", this->_program_name);
    
    // show the usage
    if (this->_usage)
        fprintf(stdout, "%s", this->_usage);

    fprintf(stdout, "\n\n");

    // show the option list
    if (this->_option_list)
        argparse_show_option_list(this);

    // show the epilog
    if (this->_epilog)
        fprintf(stdout, "%s", this->_epilog);
}

/**
 * @brief: error handling functions
 */
static void internal_error(const char *message){
    fprintf(stderr, ASCII_COLOR_RED "INTERNAL ERROR: " ASCII_COLOR_RESET "%s\n", message);
    exit(EXIT_FAILURE);
}

static void option_error(const char * message, int flag, const argparse_option * option){

}


/**
 * @brief: Public API functions implementation
 */
void argparse_init(argparse *this, argparse_option *option_list, const char *program_name){
    this->_argc = 0;
    this->_argv = NULL;
    this->_option_list = option_list;
    this->_program_name = program_name;
    this->_description = NULL;
    this->_epilog = NULL;
    this->_usage = NULL;
    this->_flags = ARGPARSE_FLAG_STOP_UNKNOWN_OPTION;
}

void argparse_set_flags(argparse *this, argparse_flag flags){
    this->_flags = flags;
}

void argparse_add_description(argparse *this, const char *description, const char *epilog, const char *usage){
    this->_description = description;
    this->_epilog = epilog;
    this->_usage = usage;
}


void argparse_parse(argparse *this, int argc, char *argv[]){

    if (argv == NULL || argv[0] == NULL)
        internal_error("argv is NULL");

    this->_argc = argc;
    this->_argv = argv;

    /**
     * this core logic will not update the internal variables of the argparse
     * it will only process the argc and argv, and dispatch the option to the handler function,
     * then the argc and argv will be updated by the handler function.
     * 
     * @note: the loop will always assume that the argv is pointing to the option, 
     * rather than the argument.
     */
    
    for ( ; this->_argc > 0; ){
        const char * current_option = this->_argv[0];
        size_t current_option_length = strlen(current_option);

        // for short option


        // for long option


        // for unknown option
        unknown_option:
            if (this->_flags & ARGPARSE_FLAG_IGNORE_UNKNOWN_OPTION){
                this->_argc--;
                this->_argv++;
            }else{
                fprintf(stderr, ASCII_COLOR_RED "%s" ASCII_COLOR_RESET " : unknown option %s\n", 
                this->_program_name, current_option);
                exit(EXIT_FAILURE);
            }
    }
}


/**
 * @brief: build-in callback functions implementation
 */

void argparse_callback_help(argparse* this, argparse_option *option){
    (void)option;
    argparse_show_all(this);
    exit(EXIT_SUCCESS);
}

void argparse_callback_multiple_arguments(argparse* this, argparse_option *option){

}