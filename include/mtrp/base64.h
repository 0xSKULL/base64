#ifndef _mtrp_b64_H_
#define _mtrp_b64_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MTRP_B64_ERROR (-(size_t)1u);
#define MTRP_B64_PADDING_OPTIONAL 0
#define MTRP_B64_PADDING_MANDATORY 1
#define MTRP_B64_PADDING_FORBIDDEN 2

#ifdef __cplusplus
extern "C" {
#endif



/** Encoded message size calculator
 * 
 * @param beg Beginning of the ORIGINAL message
 * @param end Ending of the ORIGINAL message
 * @param padding_option Optional/Mandatory/Forbidden (0/1/2) (optional == forbidden)
 * @return Size of the future encoded message
*/

inline size_t mtrp_b64_calc_enc(void const* beg, void const* end, int padding_option)
{
    uint8_t const* b = (uint8_t const*)beg;
    uint8_t const* e = (uint8_t const*)end;

    size_t const len = (e - b);
    if (padding_option == MTRP_B64_PADDING_MANDATORY)
        return (len + 2) / 3u * 4u;

    size_t const bulk = len / 3u * 4u;
    size_t const modulo = len % 3u;

    return (modulo == 0) ? bulk : bulk + modulo + 1;
}

#define mtrp_b64url_calc_enc(beg, end, padding_option) mtrp_b64_calc_enc(beg, end, padding_option)



/** Decoded (original) message size calculator
 * 
 * @param beg Beginning of the ENCODED message
 * @param end Ending of the ENCODED message
 * @param padding_option Optional/Mandatory/Forbidden (0/1/2)
 * @return Size of the future decoded message or MTRP_B64_ERROR
*/

inline size_t mtrp_b64_calc_dec(void const* const beg, void const* const end, int padding_option)
{
    uint8_t const* const b = (uint8_t const*)beg;
    uint8_t const* const e = (uint8_t const*)end;

    size_t const len = (e - b);
    size_t const bulk = len / 4u * 3u;
    size_t const modulo = len % 4u;

    if (modulo > 0u) {
        if (padding_option == MTRP_B64_PADDING_MANDATORY || e[-1] == '=' || modulo == 1)
            return MTRP_B64_ERROR;
        return bulk + (modulo - 1);
    }
    else /* modulo == 0 */ {
        if (len == 0u) return 0u;

        /* The code below just calculates the necessary size of the future decoded message (as fast as possible) 
           Only the decoder is responsible for correctness of the encoded message. */
        
        char const symbol3 = e[-2];
        char const symbol4 = e[-1];

        int x = 0;
        if (symbol4 == '=') x = 1;
        if (symbol3 == '=') x = 2;
        
        if (padding_option == MTRP_B64_PADDING_FORBIDDEN && x != 0)
            return MTRP_B64_ERROR;
        
        return bulk - x;
    }
}

#define mtrp_b64url_calc_dec(beg, end, padding_option) mtrp_b64_calc_dec(beg, end, padding_option)



/** Encoder
 * 
 * @param input_beg Beginning of the ORIGINAL message
 * @param input_end Ending of the ORIGINAL message
 * @param output    Buffer for the future ENCODED message
 * @param padding_option Optional/Mandatory/Forbidden (0/1/2) (optional == forbidden)
*/

void mtrp_b64_encode(void const* input_beg, void const* input_end, void *output, int padding_option);
void mtrp_b64url_encode(void const* input_beg, void const* input_end, void *output, int padding_option);



/** Decoder
 * 
 * @param input_beg Beginning of the ENCODED message
 * @param input_end Ending of the ENCODED message
 * @param output    Buffer for the future DECODED (original) message
 * @param padding_option Not used (reserved)
 * @return 'true' if the message is a valid Base64 string, 'false' if the message is corrupted or incorrect
*/

bool mtrp_b64_decode(void const* input_beg, void const* input_end, void *output, int padding_option);
bool mtrp_b64url_decode(void const* input_beg, void const* input_end, void *output, int padding_option);

#ifdef __cplusplus
}
#endif

#endif
