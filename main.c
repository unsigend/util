#include <argparse.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int all_headers = 0;
  int file_headers = 0;
  int section_headers = 0;
  int disassemble = 0;
  int disassemble_all = 0;
  int demangle = 0;
  char *arch = NULL;
  char *target_file = NULL;
  struct argparse_list *includes = NULL;
  int count = 0;
  double ratio = 0.0;

  /* gcc -I./include main.c lib/libutil.a -o main.out */

  struct argparse_opt opts[] = {
      OPT_GROUP("General Options"),
      OPT_HELP(),
      OPT_BOOL('H', "all-headers",
               "Display all available header information, relocation entries, "
               "and the symbol table",
               &all_headers),
      OPT_BOOL('f', "file-headers",
               "Display the contents of the overall file header",
               &file_headers),
      OPT_BOOL('S', "section-headers",
               "Display the contents of section headers", &section_headers),
      OPT_STR('\0', "arch-name", "Target architecture to disassemble for",
              &arch, OPT_OPTIONAL),
      OPT_STR('\0', "target-file", "Primary input object file to inspect",
              &target_file, OPT_REQUIRED),
      OPT_GROUP_END(),
      OPT_GROUP("Disassembly Options"),
      OPT_BOOL('d', "disassemble", "Disassemble executable sections",
               &disassemble),
      OPT_BOOL('D', "disassemble-all",
               "Disassemble all sections found in input files",
               &disassemble_all),
      OPT_BOOL('C', "demangle", "Demangle symbol names", &demangle),
      OPT_GROUP_END(),
      OPT_GROUP("Filter and Output Options"),
      OPT_STR('F', "file", "Display information about the file", &target_file,
              OPT_OPTIONAL),
      OPT_LIST('I', "include", "include path", &includes),
      OPT_INT('c', "count", "display the number of occurrences", &count,
              OPT_REQUIRED),
      OPT_DOUBLE('r', "ratio", "display the ratio of the occurrences", &ratio,
                 OPT_REQUIRED),
      OPT_GROUP_END(),
      OPT_END()};
  struct argparse_desc desc = {"objdump", "LLVM object file dumper",
                               "objdump [options] <input object files>",
                               "Use --help to print all available options."};

  struct argparse ctx;
  if (argparse_init(&ctx, opts, &desc) != 0)
    return 1;
  if (argparse_parse(&ctx, argc - 1, argv + 1) != 0) {
    fprintf(stderr, "%s\n", argparse_strerror(&ctx));
    argparse_fini(&ctx);
    return 1;
  }

  argparse_fini(&ctx);
  return 0;
}