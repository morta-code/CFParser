#include "lexer_manager_t.h"

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::lexer_manager_t(
    lexer_manager_t *source, size_t buf_len = CF_DEFAULT_BUFFER_SIZE, size_t min_cont_len = CF_MINIMUM_CONTENT_LENGTH)
{
    this->lexer_source = source;
    this->buf_len = buf_len;
    this->min_cont_len = min_cont_len;
    fill = fill_from_lexer;
    buffer = new QUEX_TYPE_CHARACTER[buf_len];
    buf_cont_begin = 1;
    buf_cont_len = 0;
    buffer[0] = 0;
    str_tmp.clear();
    source_terminated = false;
    lexer = new LEXER_TEMPLATE(buffer, buf_len, buffer + buf_cont_begin + buf_cont_len);
}

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::lexer_manager_t(
    std::wistream *source, size_t buf_len = CF_DEFAULT_BUFFER_SIZE, size_t min_cont_len = CF_MINIMUM_CONTENT_LENGTH)
{
    this->wistream_source = source;
    this->buf_len = buf_len;
    this->min_cont_len = min_cont_len;
    fill = fill_from_wistream;
    buffer = new QUEX_TYPE_CHARACTER[buf_len];
    buf_cont_begin = 1;
    buf_cont_len = 0;
    buffer[0] = 0;
    source_terminated = false;
    lexer = new LEXER_TEMPLATE(buffer, buf_len, buffer + buf_cont_begin + buf_cont_len);
}

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::~lexer_manager_t()
{
    delete [] buffer;
    delete lexer;
}

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
std::basic_string<QUEX_TYPE_CHARACTER> lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::receive(bool &terminated)
{
    if (buf_cont_len < min_cont_len)
    {
        fill();
        // TODO Ez így jó? tesztelése
        lexer->buffer_fill_region_finish(buf_cont_len); // Valószínű a receive_n csak az újonnan hozzáadottakat jelenti.
        lexer->buffer_input_pointer_set(buffer + 1);
    }
    TOKEN_TEMPLATE tok;
    lexer->receive(&tok);
    if (tok.type_id() == 0)
    {
        // TNK_TERMINATION
        terminated = true;
    }
    return tok.value; // TODO: implement!
}


template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
void lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::fill_from_lexer()
{
    move_to_left();
    while (1)
    {
        // TODO: átgondolni (Nyékyné)
        if (str_tmp.empty())
            str_tmp = lexer_source->receive(source_terminated);
        if (str_tmp.length() > buf_len - buf_cont_len)
            return;
        memcpy(buffer + buf_cont_begin + buf_cont_len, str_tmp.c_str(), str_tmp.length());
        buf_cont_len += str_tmp.length();
        str_tmp.clear();
    }
}

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
void lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::fill_from_wistream()
{
    move_to_left();
    size_t read_len = wistream_source->readsome(buffer + buf_cont_begin + buf_cont_len, buf_len - buf_cont_len );
    if (read_len != buf_len - buf_cont_len)
    {
        source_terminated = true;
    }
    buf_cont_len += read_len;
}

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
void lexer_manager_t< LEXER_TEMPLATE, TOKEN_TEMPLATE >::move_to_left()
{
    if (buf_cont_begin == 1)
        return;
    QUEX_TYPE_CHARACTER temp_buf[buf_cont_len];
    memcpy(temp_buf, buffer + buf_cont_begin, buf_cont_len);
    memcpy(buffer + 1, temp_buf, buf_cont_len);
    buf_cont_begin = 1;
}
