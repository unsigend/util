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

#ifndef ARGPARSE_H
#define ARGPARSE_H

/**
 * @brief: argparse library is part of the util library project
 *         This library is used to parse command line arguments
 * @author: QIU YIXIANG
 */

// compatible with C++
#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

/**
 * @brief: the type of the option
 * @note: this is the type of the option
 *      ARGPARSE_OPTION_TYPE_GROUP    : the option is a group
 *      ARGPARSE_OPTION_TYPE_STRING   : the option is a string
 *      ARGPARSE_OPTION_TYPE_INT      : the option is an integer
 *      ARGPARSE_OPTION_TYPE_FLOAT    : the option is a float
 *      ARGPARSE_OPTION_TYPE_DOUBLE   : the option is a double
 *      ARGPARSE_OPTION_TYPE_BOOL     : the option is a boolean with no value
 *      ARGPARSE_OPTION_TYPE_END      : the end of the option type
 */
typedef enum{
    ARGPARSE_OPTION_TYPE_GROUP,
    ARGPARSE_OPTION_TYPE_STRING,
    ARGPARSE_OPTION_TYPE_INT,
    ARGPARSE_OPTION_TYPE_FLOAT,
    ARGPARSE_OPTION_TYPE_DOUBLE,
    ARGPARSE_OPTION_TYPE_BOOL,
    ARGPARSE_OPTION_TYPE_END,
}argparse_option_type;

/**
 * @brief: the flag of the argparse
 */
typedef enum{
    ARGPARSE_FLAG_STOP_UNKNOWN_OPTION = 0x01,
}argparse_flag;

/**
 * @brief: the option struct for the argparse
 * @param _type: the type of the option
 * @param _short_name: the short name of the option
 * @param _long_name: the long name of the option
 * @param _description: the description of the option
 * @param _value: the _value is a pointer to the value to store the option
 */
typedef struct{
    argparse_option_type    _type;
    const char              _short_name;
    const char *            _long_name;
    const char *            _description;
    void *                  _value;
}argparse_option;

/**
 * @brief: the argparse struct for the argparse
 * @note: this is the struct of the argparse
 */
typedef struct{
    int                     _argc;
    char **                 _argv;
    const argparse_option * _option_list;
    const char *            _program_name;
    const char *            _description;
    const char *            _epilog;
    argparse_flag           _flags;
}argparse;


// Macros for build the option element
#define OPTION_END()                                                \
    {ARGPARSE_OPTION_TYPE_END, 0, NULL, NULL, NULL}
#define OPTION_GROUP(DESCRIPTION)                                   \
    {ARGPARSE_OPTION_TYPE_GROUP, 0, NULL, DESCRIPTION, NULL}
#define OPTION_BOOLEAN(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE)   \
    {ARGPARSE_OPTION_TYPE_BOOL, SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE}
#define OPTION_STRING(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE)    \
    {ARGPARSE_OPTION_TYPE_STRING, SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE}
#define OPTION_INT(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE)       \
    {ARGPARSE_OPTION_TYPE_INT, SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE}
#define OPTION_FLOAT(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE)     \
    {ARGPARSE_OPTION_TYPE_FLOAT, SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE}
#define OPTION_DOUBLE(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE)    \
    {ARGPARSE_OPTION_TYPE_DOUBLE, SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE}

// function declaration
extern void argparse_init(argparse *this, argparse_option *option_list, const char *program_name);
extern void argparse_add_description(argparse *this, const char *description, const char *epilog);
extern void argparse_show_usage(argparse *this, const char * usage);
extern void argparse_parse(argparse *this, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif