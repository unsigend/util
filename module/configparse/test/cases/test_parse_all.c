#include <utest.h>
#include <string.h>
#include <stdlib.h>
#include <configparse.h>

extern const char * simple_filename;
extern const char * complex_filename;

typedef struct simple_callback_data{
    const char * key;
    const char * value;
} simple_callback_data_t;

static int _index = 0;
static void simple_callback(void * data, const char * section, const char * key, const char * value){
    simple_callback_data_t * data_list = (simple_callback_data_t *)data;
    data_list[_index].key = strdup(key);
    data_list[_index].value = strdup(value);
    _index++;
}

typedef struct complex_callback_data{
    const char * section;
    const char * key;
    const char * value;
} complex_callback_data_t;

static void complex_callback(void * data, const char * section, const char * key, const char * value){
    complex_callback_data_t * data_list = (complex_callback_data_t *)data;
    if ((strcmp(section, "core") == 0) ||
        (strcmp(section, "init") == 0) ||
        (strcmp(section, "color") == 0) ||
        (strcmp(section, "remote \"origin\"") == 0)||
        (strcmp(section, "merge") == 0) ||
        (strcmp(section, "credential") == 0) ||
        (strcmp(section, "url \"git@github.com:\"") == 0)){
        data_list[_index].section = strdup(section);
        data_list[_index].key = strdup(key);
        data_list[_index].value = strdup(value);
        _index++;
    }
}

static void complex_callback_everything(void * data, const char * section, const char * key, const char * value){
    complex_callback_data_t * data_list = (complex_callback_data_t *)data;
    data_list[_index].section = strdup(section);
    data_list[_index].key = strdup(key);
    data_list[_index].value = strdup(value);
    _index++;
}

// Just test the key-value pair, not the section
UTEST_TEST_CASE(configparse_parse_all_simple){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, simple_filename));
    simple_callback_data_t data_list[32];
    memset(data_list, 0, sizeof(data_list));

    configparse_parse_all(&configparse, simple_callback, data_list);
    EXPECT_EQUAL_INT(_index, 11);

    for (int i = 0; i < 11; i++){
        EXPECT_TRUE(data_list[i].key && data_list[i].value);
    }
    for (int i = 11; i < 32; i++){
        EXPECT_NULL(data_list[i].key);
        EXPECT_NULL(data_list[i].value);
    }

    EXPECT_EQUAL_STRING(data_list[0].key, "repositoryFormat");
    EXPECT_EQUAL_STRING(data_list[0].value, "0");

    EXPECT_EQUAL_STRING(data_list[1].key, "fileMode");
    EXPECT_EQUAL_STRING(data_list[1].value, "true");

    EXPECT_EQUAL_STRING(data_list[2].key, "bare");
    EXPECT_EQUAL_STRING(data_list[2].value, "false");

    EXPECT_EQUAL_STRING(data_list[3].key, "global");
    EXPECT_EQUAL_STRING(data_list[3].value, "true");

    EXPECT_EQUAL_STRING(data_list[4].key, "ignoreCase");
    EXPECT_EQUAL_STRING(data_list[4].value, "true");

    EXPECT_EQUAL_STRING(data_list[5].key, "unicode");
    EXPECT_EQUAL_STRING(data_list[5].value, "true");

    EXPECT_EQUAL_STRING(data_list[6].key, "url");
    EXPECT_EQUAL_STRING(data_list[6].value, "git@github.com");

    EXPECT_EQUAL_STRING(data_list[7].key, "fetch");
    EXPECT_EQUAL_STRING(data_list[7].value, "refs/heads/");

    EXPECT_EQUAL_STRING(data_list[8].key, "remote");
    EXPECT_EQUAL_STRING(data_list[8].value, "origin");

    EXPECT_EQUAL_STRING(data_list[9].key, "merge");
    EXPECT_EQUAL_STRING(data_list[9].value, "refs/heads/main");

    EXPECT_EQUAL_STRING(data_list[10].key, "vscode-merge-base");
    EXPECT_EQUAL_STRING(data_list[10].value, "origin/main");

    for (int i = 0; i < 11; i++){
        free((void *)data_list[i].key);
        free((void *)data_list[i].value);
    }
}

// Test the complex.ini file, only test the key-value pair in the specified section
UTEST_TEST_CASE(configparse_parse_all_complex){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, complex_filename));
    complex_callback_data_t data_list[32];
    memset(data_list, 0, sizeof(data_list));

    _index = 0;

    EXPECT_EQUAL_INT(_index, 0);
    configparse_parse_all(&configparse, complex_callback, data_list);

    EXPECT_EQUAL_INT(_index, 29);
    for (int i = 0; i < 29; i++){
        EXPECT_NOT_NULL(data_list[i].section);
        EXPECT_NOT_NULL(data_list[i].key);
        EXPECT_NOT_NULL(data_list[i].value);
    }

    for (int i = 0; i < 7; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "core");
    }
    for (int i = 7; i < 9; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "init");
    }
    for (int i = 9; i < 16; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "color");
    }
    for (int i = 16; i < 20; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "remote \"origin\"");
    }
    for (int i = 20; i < 24; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "merge");
    }
    for (int i = 24; i < 27; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "credential");
    }
    for (int i = 27; i < 29; i++){
        EXPECT_EQUAL_STRING(data_list[i].section, "url \"git@github.com:\"");
    }

    EXPECT_EQUAL_STRING(data_list[0].key, "editor");
    EXPECT_EQUAL_STRING(data_list[0].value, "vim");

    EXPECT_EQUAL_STRING(data_list[1].key, "excludesfile");
    EXPECT_EQUAL_STRING(data_list[1].value, "~/.gitignore");

    EXPECT_EQUAL_STRING(data_list[2].key, "autocrlf");
    EXPECT_EQUAL_STRING(data_list[2].value, "input");

    EXPECT_EQUAL_STRING(data_list[3].key, "safecrlf");
    EXPECT_EQUAL_STRING(data_list[3].value, "warn");

    EXPECT_EQUAL_STRING(data_list[4].key, "quotepath");
    EXPECT_EQUAL_STRING(data_list[4].value, "false");

    EXPECT_EQUAL_STRING(data_list[5].key, "ignorecase");
    EXPECT_EQUAL_STRING(data_list[5].value, "true");

    EXPECT_EQUAL_STRING(data_list[6].key, "longpaths");
    EXPECT_EQUAL_STRING(data_list[6].value, "true");

    EXPECT_EQUAL_STRING(data_list[7].key, "defaultBranch");
    EXPECT_EQUAL_STRING(data_list[7].value, "main");

    EXPECT_EQUAL_STRING(data_list[8].key, "templateDir");
    EXPECT_EQUAL_STRING(data_list[8].value, "/usr/share/git-core/templates");

    EXPECT_EQUAL_STRING(data_list[9].key, "ui");
    EXPECT_EQUAL_STRING(data_list[9].value, "auto");

    EXPECT_EQUAL_STRING(data_list[10].key, "diff");
    EXPECT_EQUAL_STRING(data_list[10].value, "auto");

    EXPECT_EQUAL_STRING(data_list[11].key, "status");
    EXPECT_EQUAL_STRING(data_list[11].value, "auto");

    EXPECT_EQUAL_STRING(data_list[12].key, "branch");
    EXPECT_EQUAL_STRING(data_list[12].value, "auto");

    EXPECT_EQUAL_STRING(data_list[13].key, "interactive");
    EXPECT_EQUAL_STRING(data_list[13].value, "auto");

    EXPECT_EQUAL_STRING(data_list[14].key, "help");
    EXPECT_EQUAL_STRING(data_list[14].value, "auto");

    EXPECT_EQUAL_STRING(data_list[15].key, "pager");
    EXPECT_EQUAL_STRING(data_list[15].value, "true");

    EXPECT_EQUAL_STRING(data_list[16].key, "url");
    EXPECT_EQUAL_STRING(data_list[16].value, "git@github.com:username/repo.git");

    EXPECT_EQUAL_STRING(data_list[17].key, "fetch");
    EXPECT_EQUAL_STRING(data_list[17].value, "+refs/heads/*:refs/remotes/origin/*");

    EXPECT_EQUAL_STRING(data_list[18].key, "pushurl");
    EXPECT_EQUAL_STRING(data_list[18].value, "git@github.com:username/repo.git");

    EXPECT_EQUAL_STRING(data_list[19].key, "push");
    EXPECT_EQUAL_STRING(data_list[19].value, "refs/heads/main:refs/heads/main");

    EXPECT_EQUAL_STRING(data_list[20].key, "tool");
    EXPECT_EQUAL_STRING(data_list[20].value, "vimdiff");

    EXPECT_EQUAL_STRING(data_list[21].key, "conflictstyle");
    EXPECT_EQUAL_STRING(data_list[21].value, "diff3");

    EXPECT_EQUAL_STRING(data_list[22].key, "log");
    EXPECT_EQUAL_STRING(data_list[22].value, "true");

    EXPECT_EQUAL_STRING(data_list[23].key, "maxParents");
    EXPECT_EQUAL_STRING(data_list[23].value, "2");

    EXPECT_EQUAL_STRING(data_list[24].key, "helper");
    EXPECT_EQUAL_STRING(data_list[24].value, "cache --timeout=3600");

    EXPECT_EQUAL_STRING(data_list[25].key, "helper");
    EXPECT_EQUAL_STRING(data_list[25].value, "!aws codecommit credential-helper $@");

    EXPECT_EQUAL_STRING(data_list[26].key, "store");
    EXPECT_EQUAL_STRING(data_list[26].value, "true");

    EXPECT_EQUAL_STRING(data_list[27].key, "insteadOf");
    EXPECT_EQUAL_STRING(data_list[27].value, "https://github.com/");

    EXPECT_EQUAL_STRING(data_list[28].key, "pushInsteadOf");
    EXPECT_EQUAL_STRING(data_list[28].value, "git://github.com/");

    for (int i = 0; i < 29; i++){
        free((void *)data_list[i].section);
        free((void *)data_list[i].key);
        free((void *)data_list[i].value);
    }
    
}

// Test the complex.ini file, test all the key-value pair
UTEST_TEST_CASE(configparse_parse_all_complex_everything){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, complex_filename));

    complex_callback_data_t data_list[128];
    memset(data_list, 0, sizeof(data_list));

    _index = 0;

    configparse_parse_all(&configparse, complex_callback_everything, data_list);

    EXPECT_EQUAL_INT(_index, 69);
    for (int i = 0; i < 69; i++){
        EXPECT_NOT_NULL(data_list[i].section);
        EXPECT_NOT_NULL(data_list[i].key);
        EXPECT_NOT_NULL(data_list[i].value);
    }
    for (int i = 69; i < 128; i++){
        EXPECT_NULL(data_list[i].section);
        EXPECT_NULL(data_list[i].key);
        EXPECT_NULL(data_list[i].value);
    }

    int current_index = 0;

    for (int i = 0; i < 7; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "core");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "editor");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "vim");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "excludesfile");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "~/.gitignore");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "autocrlf");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "input");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "safecrlf");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "warn");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].key, "quotepath");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].value, "false");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].key, "ignorecase");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].key, "longpaths");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].value, "true");
    current_index += 7;

    for (int i = 0; i < 2; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "init");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "defaultBranch");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "main");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "templateDir");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "/usr/share/git-core/templates");
    current_index += 2;

    for (int i = 0; i < 7; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "alias");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "st");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "status");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "co");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "checkout");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "br");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "branch");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "ci");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "commit");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].key, "unstage");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].value, "reset HEAD --");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].key, "last");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].value, "log -1 HEAD");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].key, "visual");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].value, "!gitk");
    current_index += 7;

    for (int i = 0; i < 7; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "color");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "ui");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "diff");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "status");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "branch");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].key, "interactive");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].key, "help");
    EXPECT_EQUAL_STRING(data_list[current_index + 5].value, "auto");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].key, "pager");
    EXPECT_EQUAL_STRING(data_list[current_index + 6].value, "true");
    current_index += 7;

    for (int i = 0; i < 5; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "color \"diff\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "meta");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "yellow bold");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "frag");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "magenta bold");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "old");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "red bold");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "new");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "green bold");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].key, "whitespace");
    EXPECT_EQUAL_STRING(data_list[current_index + 4].value, "red reverse");
    current_index += 5;

    for (int i = 0; i < 3; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "push");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "default");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "simple");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "followTags");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "matching");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "true");
    current_index += 3;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "remote \"origin\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "url");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "fetch");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "+refs/heads/*:refs/remotes/origin/*");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "pushurl");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "push");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "refs/heads/main:refs/heads/main");
    current_index += 4;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "branch \"main\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "remote");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "origin");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "merge");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "refs/heads/main");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "rebase");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "autostash");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "true");
    current_index += 4;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "merge");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "tool");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "vimdiff");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "conflictstyle");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "diff3");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "log");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "maxParents");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "2");
    current_index += 4;

    for (int i = 0; i < 3; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "merge \"custom-merge\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "name");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "Custom Merge Driver");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "driver");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "custom-merge-driver %O %A %B");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "recursive");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "binary");
    current_index += 3;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "filter \"lfs\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "clean");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "git-lfs clean -- %f");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "smudge");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "git-lfs smudge -- %f");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "process");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "git-lfs filter-process");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "required");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "true");
    current_index += 4;

    for (int i = 0; i < 3; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "credential");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "helper");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "cache --timeout=3600");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "helper");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "!aws codecommit credential-helper $@");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "store");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "true");
    current_index += 3;

    for (int i = 0; i < 2; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "include");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "path");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "~/.gitconfig.local");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "path");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, ".gitconfig.work");
    current_index += 2;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "user");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "name");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "John Doe");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "email");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "john.doe@example.com");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "signingkey");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "ABCD1234");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "sign");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "true");
    current_index += 4;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "commit");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "template");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "~/.gitmessage");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "gpgsign");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "cleanup");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "strip");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "verbose");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "true");
    current_index += 4;

    for (int i = 0; i < 4; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "status");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "showStash");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "showUntrackedFiles");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "all");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].key, "showIgnoredFiles");
    EXPECT_EQUAL_STRING(data_list[current_index + 2].value, "true");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].key, "submoduleSummary");
    EXPECT_EQUAL_STRING(data_list[current_index + 3].value, "true");
    current_index += 4;

    for (int i = 0; i < 2; i++) {
        EXPECT_EQUAL_STRING(data_list[current_index + i].section, "url \"git@github.com:\"");
    }
    EXPECT_EQUAL_STRING(data_list[current_index].key, "insteadOf");
    EXPECT_EQUAL_STRING(data_list[current_index].value, "https://github.com/");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].key, "pushInsteadOf");
    EXPECT_EQUAL_STRING(data_list[current_index + 1].value, "git://github.com/");
    current_index += 2;

    EXPECT_EQUAL_INT(current_index, 69);

    for (int i = 0; i < 69; i++){
        free((void *)data_list[i].section);
        free((void *)data_list[i].key);
        free((void *)data_list[i].value);
    }
}
UTEST_TEST_SUITE(configparse_parse_all){
    UTEST_RUN_TEST_CASE(configparse_parse_all_simple);
    UTEST_RUN_TEST_CASE(configparse_parse_all_complex);
    UTEST_RUN_TEST_CASE(configparse_parse_all_complex_everything);
}