#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include "lexer_manager_t.h"

#define CF_DFAULT_BUF_SIZE 20000

void run(std::wistream &input, std::wostream &output)
{
#if CF_LEXERS_NUM >= 1
    lexer_manager_t<cfl_1::cfl_1, cfl_1::Token> lm_cfl_1(&input, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 2
    lexer_manager_t<cfl_2::cfl_2, cfl_2::Token> lm_cfl_2(&lm_cfl_1, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 3
    lexer_manager_t<cfl_3::cfl_3, cfl_3::Token> lm_cfl_3(&lm_cfl_2, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 4
    lexer_manager_t<cfl_4::cfl_4, cfl_4::Token> lm_cfl_4(&lm_cfl_3, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 5
    lexer_manager_t<cfl_5::cfl_5, cfl_5::Token> lm_cfl_5(&lm_cfl_4, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 6
    lexer_manager_t<cfl_6::cfl_6, cfl_6::Token> lm_cfl_6(&lm_cfl_5, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 7
    lexer_manager_t<cfl_7::cfl_7, cfl_7::Token> lm_cfl_7(&lm_cfl_6, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 8
    lexer_manager_t<cfl_8::cfl_8, cfl_8::Token> lm_cfl_8(&lm_cfl_7, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 9
    lexer_manager_t<cfl_9::cfl_9, cfl_9::Token> lm_cfl_9(&lm_cfl_8, CF_DFAULT_BUF_SIZE);
#endif
#if CF_LEXERS_NUM >= 10
    lexer_manager_t<cfl_10::cfl_10, cfl_10::Token> lm_cfl_10(&lm_cfl_9, CF_DFAULT_BUF_SIZE);
#endif

#if CF_LEXERS_NUM != 0
    //bool end = false;
    while (true/*!end*/)
    {
        std::wstring res = CF_LAST_LEXER_MANAGER.receive();
        if (res.empty()) {
            //end = true;
            break;
        }
#ifdef CFDEBUG2
        output << res << std::endl;
#else
        output << res;
#endif
    }
    output.flush();
#endif
}


int main()//(int argc, char *argv[])
{
    setlocale(LC_ALL, "hu_HU.utf8");
    std::wcout << L"Ezzel a sorral tudjuk átverni a cout-ot.\n";
    std::wifstream input("go.txt");
    input.imbue(std::locale("C.UTF-8"));
    run(input, std::wcout);
    input.close();
    return EXIT_SUCCESS;
}

