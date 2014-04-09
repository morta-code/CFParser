#ifndef LEXER_MANAGER_T_H
    #define LEXER_MANAGER_T_H

#ifndef QUEX_TYPE_CHARACTER
    #define QUEX_TYPE_CHARACTER wchar_t
#endif

#ifndef CF_DEFAULT_BUFFER_SIZE
    #define CF_DEFAULT_BUFFER_SIZE 32768
#endif

#ifndef CF_MINIMUM_CONTENT_LENGTH
    #define CF_MINIMUM_CONTENT_LENGTH 4096
#endif

#include <iostream>
#include <cstring>
#include <string>

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
class lexer_manager_t
{
    QUEX_TYPE_CHARACTER *buffer;    // The buffer. The managed lexer uses this as the source.
    size_t buf_len;           // The maximum length of the buffer.
    size_t buf_cont_begin;          // The number (and not the address) of the firs character in the buffer.
    size_t buf_cont_len;            // The actual length of buffer content.
    size_t min_cont_len;            // The minimum length of buffer content.

    lexer_manager_t *lexer_source;                // The source if the lexer is not the first in pipeline.
    std::basic_string<QUEX_TYPE_CHARACTER> str_tmp;     // The intermediate buffer for lexer_source.
    std::wistream *wistream_source;               // The source if the lexer is the first.
    bool source_terminated;                             // Flag for indicate the source's terminatiom.

    LEXER_TEMPLATE *lexer;          // The managed lexer. The receive() method read from this.

public:
    lexer_manager_t(lexer_manager_t *source, size_t buf_len, size_t min_cont_len); // Constr. for lexer source.
    lexer_manager_t(std::wistream *source, size_t buf_len, size_t min_cont_len);   // Constr. for input source.
    ~lexer_manager_t();

    std::basic_string<QUEX_TYPE_CHARACTER> receive(bool &terminated);  // The intelligent receive method.

private:
    void (*fill)();                  // Method pointer to the corresponding fill metod. (Set up in construct time.)
    void fill_from_lexer();          // Fill the buffer from lexer_source
    void fill_from_wistream();       // Fill the buffer from wistream_source
    void move_to_left();             // Move the content of buffer to the 1st position
};


#endif // LEXER_MANAGER_T_H
