#include <fstream>
#include <iostream>
#include <string>
#include "lexer_manager_t.h"

#ifndef CF_LEXERS_NUM
#define CF_LEXERS_NUM 0
#endif

#if CF_LEXERS_NUM >= 1
#include "cfl_1"
#define CF_LAST_LEXER_MANAGER lm_cfl_1
#endif
#if CF_LEXERS_NUM >= 2
#include "cfl_2"
#define CF_LAST_LEXER_MANAGER lm_cfl_2
#endif
#if CF_LEXERS_NUM >= 3
#include "cfl_3"
#define CF_LAST_LEXER_MANAGER lm_cfl_3
#endif
#if CF_LEXERS_NUM >= 4
#include "cfl_4"
#define CF_LAST_LEXER_MANAGER lm_cfl_4
#endif
#if CF_LEXERS_NUM >= 5
#include "cfl_5"
#define CF_LAST_LEXER_MANAGER lm_cfl_5
#endif
#if CF_LEXERS_NUM >= 6
#include "cfl_6"
#define CF_LAST_LEXER_MANAGER lm_cfl_6
#endif
#if CF_LEXERS_NUM >= 7
#include "cfl_7"
#define CF_LAST_LEXER_MANAGER lm_cfl_7
#endif
#if CF_LEXERS_NUM >= 8
#include "cfl_8"
#define CF_LAST_LEXER_MANAGER lm_cfl_8
#endif
#if CF_LEXERS_NUM >= 9
#include "cfl_9"
#define CF_LAST_LEXER_MANAGER lm_cfl_9
#endif
#if CF_LEXERS_NUM >= 10
#include "cfl_10"
#define CF_LAST_LEXER_MANAGER lm_cfl_10
#endif

using namespace std;

void run(std::wistream &input, std::wostream &output)
{
#if CF_LEXERS_NUM >= 1
    lexer_manager_t<quex::cfl_1, QUEX_TYPE_TOKEN> lm_cfl_1(input);
#endif
#if CF_LEXERS_NUM >= 2
    lexer_manager_t<quex::cfl_2, QUEX_TYPE_TOKEN> lm_cfl_2(&lm_cfl_1);
#endif
#if CF_LEXERS_NUM >= 3
    lexer_manager_t<quex::cfl_3, QUEX_TYPE_TOKEN> lm_cfl_3(&lm_cfl_2);
#endif
#if CF_LEXERS_NUM >= 4
    lexer_manager_t<quex::cfl_4, QUEX_TYPE_TOKEN> lm_cfl_4(&lm_cfl_3);
#endif
#if CF_LEXERS_NUM >= 5
    lexer_manager_t<quex::cfl_5, QUEX_TYPE_TOKEN> lm_cfl_5(&lm_cfl_4);
#endif
#if CF_LEXERS_NUM >= 6
    lexer_manager_t<quex::cfl_6, QUEX_TYPE_TOKEN> lm_cfl_6(&lm_cfl_5);
#endif
#if CF_LEXERS_NUM >= 7
    lexer_manager_t<quex::cfl_7, QUEX_TYPE_TOKEN> lm_cfl_7(&lm_cfl_6);
#endif
#if CF_LEXERS_NUM >= 8
    lexer_manager_t<quex::cfl_8, QUEX_TYPE_TOKEN> lm_cfl_8(&lm_cfl_7);
#endif
#if CF_LEXERS_NUM >= 9
    lexer_manager_t<quex::cfl_9, QUEX_TYPE_TOKEN> lm_cfl_9(&lm_cfl_8);
#endif
#if CF_LEXERS_NUM >= 10
    lexer_manager_t<quex::cfl_10, QUEX_TYPE_TOKEN> lm_cfl_10(&lm_cfl_9);
#endif

#if CF_LEXERS_NUM != 0
    bool end = false;
    while (!end)
    {
        output << CF_LAST_LEXER_MANAGER.receive(end);
    }
#endif
}

#define DEFMAIN main
int DEFMAIN(int argc, char const *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}

