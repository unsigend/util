#include <argparse.h>

int main(int argc, char *argv[]){

    argparse argparse;
    argparse_option option_list[] = {
        OPTION_GROUP("General Options"),
        OPTION_BOOLEAN('h', "help", "show this help message and exit", NULL),
        OPTION_STRING('v', "version", "show version information and exit", NULL),
        OPTION_GROUP("MachO Specific Options"),
        OPTION_STRING('a', "arch", "show the architecture of the MachO file", NULL),
        OPTION_STRING('b', "base-address", "show the base address of the MachO file", NULL),
        OPTION_STRING('d', "dump", "dump the MachO file", NULL),
        OPTION_STRING('f', "file", "show the file of the MachO file", NULL),
        OPTION_END()
    };
    argparse_init(&argparse, option_list, "demo");
    argparse_add_description(&argparse, "This is a demo program", "Demo program for argparse");

    argparse_show_usage(&argparse, "[options]");
    return 0;
}