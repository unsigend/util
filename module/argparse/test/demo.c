#include <argparse.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc == 1)
        return 0;

    // version flag
    bool show_version = false;
    // force flag
    bool force = false;
    // file list
    const char ** file_list = NULL;
    long file_list_size = 0;
    // output file
    const char * output = NULL;
    // dump file
    const char * dump = NULL;
    // arch
    const char * arch = NULL;
    // arch support
    const char ** arch_support = NULL;
    long arch_support_size = 0;
    // function starts address
    const char * function_starts_address = NULL;
    // x86 asm syntax
    const char * x86_asm_syntax = NULL;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_GROUP("Basic Options"),
        OPTION_HELP(),
        OPTION_BOOLEAN('v', "version", "show version", &show_version, NULL, 0),
        OPTION_BOOLEAN(0, "force", "force the operation", &force, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_GROUP("file Options"),
        OPTION_STRING('f', "file", "input file read form your device", &file_list, argparse_callback_multiple_arguments, (intptr_t)&file_list_size),
        OPTION_STRING(0, "output", "output file to save the result", &output, NULL, 0),
        OPTION_STRING(0, "dump", "dump the result to the console", &dump, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_GROUP("Arch Option"),
        OPTION_STRING(0, "arch", "set the architecture", &arch, NULL, 0),
        OPTION_STRING(0, "arch-support", "specify the architecture support", &arch_support, argparse_callback_multiple_arguments, (intptr_t)&arch_support_size),
        OPTION_STRING(0, "function-starts-address", "specify the function starts address", &function_starts_address, NULL, 0),
        OPTION_STRING(0, "x86-asm-syntax", "specify the x86 assembly syntax", &x86_asm_syntax, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_END()
    };
    struct argparse_description description = {
        "The demo program for the argparse library",
        "This program is used to test the argparse library",
        " [options] [file]...",
        "argparser"
    };

    argparse_init(&argparse, options, &description);
    argparse_parse(&argparse, argc - 1, argv + 1);

    fprintf(stdout, "show version: ");
    if (show_version)
        fprintf(stdout, "true\n");
    else
        fprintf(stdout, "false\n");

    fprintf(stdout, "force: ");
    if (force)
        fprintf(stdout, "true\n");
    else
        fprintf(stdout, "false\n");

    fprintf(stdout, "file list: ");
    for (int i = 0; i < file_list_size; i++)
        fprintf(stdout, "%s ", file_list[i]);
    fprintf(stdout, "\n");

    fprintf(stdout, "output: %s\n", output);
    fprintf(stdout, "dump: %s\n", dump);
    fprintf(stdout, "arch: %s\n", arch);
    fprintf(stdout, "arch support: ");
    for (int i = 0; i < arch_support_size; i++)
        fprintf(stdout, "%s ", arch_support[i]);
    fprintf(stdout, "\n");

    fprintf(stdout, "function starts address: %s\n", function_starts_address);
    fprintf(stdout, "x86 asm syntax: %s\n", x86_asm_syntax);
    return 0;
}