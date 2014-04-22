#ifndef LEXER_MANAGER_T_H
    #define LEXER_MANAGER_T_H

#define CFDEBUG

#ifndef CF_LEXERS_NUM
#define CF_LEXERS_NUM 0
#endif

#if CF_LEXERS_NUM >= 1
#include "cfl_1_cfl_1"
#define CF_LAST_LEXER_MANAGER lm_cfl_1
#endif
#if CF_LEXERS_NUM >= 2
#include "cfl_2_cfl_2"
#define CF_LAST_LEXER_MANAGER lm_cfl_2
#endif
#if CF_LEXERS_NUM >= 3
#include "cfl_3_cfl_3"
#define CF_LAST_LEXER_MANAGER lm_cfl_3
#endif
#if CF_LEXERS_NUM >= 4
#include "cfl_4_cfl_4"
#define CF_LAST_LEXER_MANAGER lm_cfl_4
#endif
#if CF_LEXERS_NUM >= 5
#include "cfl_5_cfl_5"
#define CF_LAST_LEXER_MANAGER lm_cfl_5
#endif
#if CF_LEXERS_NUM >= 6
#include "cfl_6_cfl_6"
#define CF_LAST_LEXER_MANAGER lm_cfl_6
#endif
#if CF_LEXERS_NUM >= 7
#include "cfl_7_cfl_7"
#define CF_LAST_LEXER_MANAGER lm_cfl_7
#endif
#if CF_LEXERS_NUM >= 8
#include "cfl_8_cfl_8"
#define CF_LAST_LEXER_MANAGER lm_cfl_8
#endif
#if CF_LEXERS_NUM >= 9
#include "cfl_9_cfl_9"
#define CF_LAST_LEXER_MANAGER lm_cfl_9
#endif
#if CF_LEXERS_NUM >= 10
#include "cfl_10_cfl_10"
#define CF_LAST_LEXER_MANAGER lm_cfl_10
#endif

#define TKN_TERMINATION 1
#define TKN_UNUSED 99

#include <iostream>
#include <cstring>
#include <string>


class base_lexer_manager
{
public:
    virtual std::wstring receive() = 0;
};

struct MemoryChunk {
    wchar_t* begin;
    wchar_t* end;
};

template<class LEXER_TEMPLATE, class TOKEN_TEMPLATE>
class lexer_manager_t : public base_lexer_manager
{
public:
    //std::wstring receive();  // The intelligent receive method.

private:
//    void (*fill)();                  // Method pointer to the corresponding fill metod. (Set up in construct time.)
//    void fill_from_lexer();          // Fill the buffer from lexer_source
//    void fill_from_wistream();       // Fill the buffer from wistream_source

    std::wistream*      stream_input = 0;       // Input source if it manages the 1st lexer.
    size_t              BUF_SIZE;               // The maximum size of the buffer to analyze.
    size_t              input_read = 0;         // The counter of all read lexeme. NOTE unused.
    base_lexer_manager* lm_input = 0;           // Input source if it manages an other lexer than 1st.
    bool                input_end = false;      // Flag for sign, that the source is terminated.

    wchar_t*            rx_buffer = 0;          // The buffer. It will be sign by the chunk.
    size_t              rx_size = 0;            // Size of the buffer.
    std::wstring        rec;                    // Receiver variable for lm_input. It carries the last value to the next reading cycle.
    size_t              read_size = 0;          //
    const wchar_t*      fallback_buffer = 0;
    size_t              fb_size = 0;
    MemoryChunk         chunk;

    LEXER_TEMPLATE*     lexer;
    TOKEN_TEMPLATE*     token_bank[2];
    size_t              queue0_size = 2;
    size_t              queue1_size = 2;
    TOKEN_TEMPLATE*     cur_tokens;
    TOKEN_TEMPLATE*     prev_tokens;

private:
    void (lexer_manager_t::*fill)();                  // Method pointer to the corresponding fill metod. (Set up in construct time.)
    void fill_from_lexer()           // Fill the buffer from lexer_source
    {
        if (chunk.begin == chunk.end) {
            if (rx_buffer != 0) {
                delete [] rx_buffer;
            }

            std::wstring rx_str(fallback_buffer, fb_size);
            fb_size = 0;

            // Amíg a beolvasott token belefér, belemásoljuk, és újraolvasunk, amíg van mit.
            while (rec.size() <= BUF_SIZE - rx_str.size() && !input_end) {
                rx_str += rec;
                rec = lm_input->receive();
                if (rec.size() == 0) {
                    input_end = true;
                    break;
                }
            }

            rx_buffer = new wchar_t[rx_str.size()];
            memcpy(rx_buffer, rx_str.c_str(), sizeof(wchar_t)*rx_str.size());

            chunk.begin = rx_buffer;
            chunk.end = chunk.begin + rx_str.size();
        }

        chunk.begin = (wchar_t*)lexer->buffer_fill_region_append(chunk.begin, chunk.end);
    }

    void fill_from_wistream()        // Fill the buffer from wistream_source
    {
        if (chunk.begin == chunk.end) {
            if (rx_buffer != 0) {
                delete [] rx_buffer;
            }

            read_size = BUF_SIZE - fb_size;
            wchar_t *_rec = new wchar_t[read_size];

            stream_input->read(_rec, read_size); //TODO: Rövidítés egy sorba.
            rx_size = stream_input->gcount() + fb_size;
            input_read += stream_input->gcount();


            if (rx_size == 0) {
                input_end = true;
                return;
            }

            rx_buffer = new wchar_t[rx_size];
            memcpy(rx_buffer, fallback_buffer, sizeof(wchar_t)*fb_size);
            memcpy(rx_buffer+fb_size, _rec, sizeof(wchar_t)*(rx_size-fb_size));
            delete [] _rec;

            chunk.begin = rx_buffer;
            chunk.end = chunk.begin + rx_size;

            fb_size = 0;
        }

        chunk.begin = (wchar_t*)lexer->buffer_fill_region_append(chunk.begin, chunk.end);
    }

    void init()
    {
        lexer = new LEXER_TEMPLATE((wchar_t*)0, 0);
        token_bank[0] = new TOKEN_TEMPLATE[queue0_size];
        token_bank[1] = new TOKEN_TEMPLATE[queue1_size];
        cur_tokens =  token_bank[0];
        prev_tokens =  token_bank[1];
        cur_tokens[0].set(TKN_TERMINATION);
        cur_tokens[1].set(TKN_TERMINATION);
        prev_tokens[0].set(TKN_TERMINATION);
        prev_tokens[1].set(TKN_TERMINATION);
        lexer->token_queue_switch(&cur_tokens, &queue0_size);
        chunk.begin = chunk.end;
    }

public:
    lexer_manager_t(std::wistream *src, const size_t &bf_s)
    {
        stream_input = src;
        BUF_SIZE = bf_s;
        fill = &lexer_manager_t::fill_from_wistream;
        init();
    }

    lexer_manager_t(base_lexer_manager *src, const size_t &bf_s)
    {
        lm_input = src;
        BUF_SIZE = bf_s;
        fill = &lexer_manager_t::fill_from_lexer;
        init();
    }

    ~lexer_manager_t()
    {
        delete lexer;
        delete [] token_bank[0];
        delete [] token_bank[1];
    }

    std::wstring receive()
    {
        std::wstring result;
        while (result.empty() && !input_end) {
            lexer->token_queue_switch(&prev_tokens, &queue1_size);
            lexer->receive(&cur_tokens);

            if (cur_tokens[0].type_id() == TKN_TERMINATION) {
                if (prev_tokens[1].type_id() != TKN_TERMINATION) {
                    if (prev_tokens[0].type_id() == TKN_UNUSED) {
                        result += prev_tokens[0].text;
                        result += prev_tokens[1].value;
                    } else {
                        result += prev_tokens[0].value;
                    }
                }
                (this->*fill)();
                continue;
            }

            if (cur_tokens[0].type_id() == TKN_UNUSED && cur_tokens[1].type_id() == TKN_TERMINATION) {
                fallback_buffer = cur_tokens[0].text.c_str();
                fb_size = cur_tokens[0].text.size();
            }

            if (prev_tokens[0].type_id() != TKN_TERMINATION) {
                if (prev_tokens[0].type_id() == TKN_UNUSED) {
                    result += prev_tokens[0].text;
                    result += prev_tokens[1].value;
                } else {
                    result += prev_tokens[0].value;
                }
            }

        }

        return result;
    }
};


#endif // LEXER_MANAGER_T_H
