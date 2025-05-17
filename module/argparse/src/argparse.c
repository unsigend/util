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

#define ASCII_COLOR_RED     "\033[31m"
#define ASCII_COLOR_RESET   "\033[0m"

#define SHORT_OPTION_PREFIX     '-'
#define LONG_OPTION_PREFIX      "--"
#define NAME_MAX_LENGTH         25

// static bool start_with(const char *str, const char *prefix){
//     return strncmp(str, prefix, strlen(prefix)) == 0;
// }


// static void argparse_error(const char * program_name, const char * message){
//     fprintf(stderr, ASCII_COLOR_RED "%s" ASCII_COLOR_RESET ": %s\n", program_name, message);
// }

// public functions implementation
void argparse_init(argparse *this, argparse_option *option_list, const char *program_name){

    // initialize the argparse
    memset(this, 0, sizeof(argparse));

    this->_option_list = option_list;
    this->_program_name = program_name;
    this->_argc = 0;
    this->_argv = NULL;
    this->_description = NULL;
    this->_epilog = NULL;
}

void argparse_add_description(argparse *this, const char *description, const char *epilog){
    this->_description = description;
    this->_epilog = epilog;
}

void argparse_show_usage(argparse *this, const char * usage){
    // show program name and usage
    fprintf(stdout, "USAGE: %s %s\n", this->_program_name, usage);

    // show description
    if (this->_description){
        fprintf(stdout, "%s\n", this->_description);
    }
    // show option description categorized by group
    for (int option_index = 0; this->_option_list[option_index]._type != ARGPARSE_OPTION_TYPE_END;
     option_index++){
        if (this->_option_list[option_index]._type == ARGPARSE_OPTION_TYPE_GROUP){
            fputc('\n', stdout);
            fprintf(stdout, "%s\n", this->_option_list[option_index]._description);
            fputc('\n', stdout);
        }else{
            char name_buffer[64];
            memset(name_buffer, 0, sizeof(name_buffer));
            
            // Build option name string
            sprintf(name_buffer, "  -%c,--%s", 
                this->_option_list[option_index]._short_name,
                this->_option_list[option_index]._long_name);
                
            // Add =<value> for non-boolean options
            if (this->_option_list[option_index]._type != ARGPARSE_OPTION_TYPE_BOOL) {
                strcat(name_buffer, "=<value>");
            }
            
            int name_len = strlen(name_buffer);
            
            // If name length exceeds max, print name and description on separate lines
            if (name_len >= NAME_MAX_LENGTH) {
                fprintf(stdout, "%s\n", name_buffer);
                fprintf(stdout, "%*s%s\n", NAME_MAX_LENGTH + 2, "", 
                    this->_option_list[option_index]._description);
            } else {
                // Print name and description on same line, aligned
                fprintf(stdout, "%-*s  %s\n", 
                    NAME_MAX_LENGTH,
                    name_buffer,
                    this->_option_list[option_index]._description);
            }
        }
    }
    // show epilog
    if (this->_epilog){
        fprintf(stdout, "\n%s\n", this->_epilog);
    }
    fflush(stdout);
}

void argparse_parse(argparse *this, int argc, char *argv[]){
    this->_argc = argc;
    this->_argv = argv;


}





