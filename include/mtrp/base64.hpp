#pragma once

#include <type_traits>
#include <iterator>
#include <utility>
#include <stdint.h>
#include <stddef.h>

namespace mtrp::b64
{
    using u8 = uint8_t;
    using u32 = uint32_t;

    constexpr size_t ERROR = -size_t(1u);

    enum class pad {
        OPTIONAL  = 0, 
        MANDATORY = 1, 
        FORBIDDEN = 2
    };

    namespace detail {
        namespace c_api {
            extern "C" {
                void mtrp_b64_encode(void const*, void const*, void *, int);
                bool mtrp_b64_decode(void const*, void const*, void *, int);

                void mtrp_b64url_encode(void const*, void const*, void *, int);
                bool mtrp_b64url_decode(void const*, void const*, void *, int);
            }
        }

        constexpr size_t calc_enc(void const* beg, void const* end, pad const pd) noexcept
        {
            uint8_t const* b = (uint8_t const*)beg;
            uint8_t const* e = (uint8_t const*)end;

            size_t const len = (e - b);
            if (pd == pad::MANDATORY)
                return (len + 2) / 3u * 4u;

            size_t const bulk = len / 3u * 4u;
            size_t const modulo = len % 3u;

            return (modulo == 0) ? bulk : bulk + modulo + 1;
        }

        constexpr size_t calc_dec(void const* const beg, void const* const end, pad const pd) noexcept
        {
            uint8_t const* const b = (uint8_t const*)beg;
            uint8_t const* const e = (uint8_t const*)end;

            size_t const len = (e - b);
            size_t const bulk = len / 4u * 3u;
            size_t const modulo = len % 4u;

            if (modulo > 0u) {
                if (pd == pad::MANDATORY || e[-1] == '=' || modulo == 1)
                    return ERROR;
                return bulk + (modulo - 1);
            }
            else /* modulo == 0 */ {
                if (len == 0u) return 0u;
                
                char const symbol3 = e[-2];
                char const symbol4 = e[-1];

                int x = 0;
                if (symbol4 == '=') x = 1;
                if (symbol3 == '=') x = 2;
                
                if (pd == pad::FORBIDDEN && x != 0)
                    return ERROR;
                
                return bulk - x;
            }
        }

        template <auto &__C_API_ENCODER_IMPL, typename IN, typename OUT>
        inline void __encode(IN const& input, OUT && output, pad const padding_option) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
        {
            using namespace std;

            using IN_iterator = decltype(std::begin(input));
            using OUT_iterator = decltype(std::begin(output));

            static_assert(sizeof(typename iterator_traits<OUT_iterator>::value_type) == 1, "the value_type size must be equal to one byte");
            static_assert(is_same_v<random_access_iterator_tag, typename iterator_traits<IN_iterator>::iterator_category>, "only ContiguousContainer is supported");
            static_assert(is_same_v<random_access_iterator_tag, typename iterator_traits<OUT_iterator>::iterator_category>, "only ContiguousContainer is supported");

            void const* beg = &*std::begin(input);
            void const* end = &*std::end(input);

            size_t const required_size = detail::calc_enc(beg, end, padding_option);
            output.resize(required_size);
            
            __C_API_ENCODER_IMPL(beg, end, &*std::begin(output), int(padding_option));
        }

        template <auto &__C_API_DECODER_IMPL, typename IN, typename OUT>
        inline bool __decode(IN const& input, OUT && output, pad const padding_option) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
        {
            using namespace std;

            using IN_iterator = decltype(std::begin(input));
            using OUT_iterator = decltype(std::begin(output));

            static_assert(sizeof(typename iterator_traits<IN_iterator>::value_type) == 1, "the value_type size must be equal to one byte");
            static_assert(sizeof(typename iterator_traits<OUT_iterator>::value_type) == 1, "the value_type size must be equal to one byte");
            static_assert(is_same_v<random_access_iterator_tag, typename iterator_traits<IN_iterator>::iterator_category>, "only ContiguousContainer is supported");
            static_assert(is_same_v<random_access_iterator_tag, typename iterator_traits<OUT_iterator>::iterator_category>, "only ContiguousContainer is supported");

            void const* const beg = &*std::begin(input);
            void const* const end = &*std::end(input);

            size_t const required_size = detail::calc_dec(beg, end, padding_option);
            if (required_size == ERROR)
                return false;

            output.resize(required_size);
            return __C_API_DECODER_IMPL(beg, end, &*std::begin(output), 0);
        }
    }

    /** Encoder
     * 
     * @param input A reference to the ORIGINAL message container (can be any ContiguousContainer, like std::vector or std::string)
     * @param output A reference to the future ENCODED message container (can be any ContiguousContainer, like std::vector or std::string)
     * @param padding_option pad::OPTIONAL/pad::MANDATORY/pad::FORBIDDEN (optional == forbidden)
    */
    template <typename IN, typename OUT>
    inline void encode(IN const& input, OUT && output, pad const padding_option = pad::OPTIONAL) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
    {
        detail::__encode<detail::c_api::mtrp_b64_encode>(input, std::forward<OUT>(output), padding_option);
    }

    /** Encoder
     * 
     * @param input A reference to the ENCODED message container (can be any ContiguousContainer, like std::vector or std::string)
     * @param output A reference to the future DECODED message container (can be any ContiguousContainer, like std::vector or std::string)
     * @param padding_option pad::OPTIONAL/pad::MANDATORY/pad::FORBIDDEN
    */
    template <typename IN, typename OUT>
    inline bool decode(IN const& input, OUT && output, pad const padding_option = pad::OPTIONAL) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
    {
        return detail::__decode<detail::c_api::mtrp_b64_decode>(input, std::forward<OUT>(output), padding_option);
    }

    namespace urlsafe
    {
        /** Encoder
         * 
         * @param input A reference to the ORIGINAL message container (can be any ContiguousContainer, like std::vector or std::string)
         * @param output A reference to the future ENCODED message container (can be any ContiguousContainer, like std::vector or std::string)
         * @param padding_option pad::OPTIONAL/pad::MANDATORY/pad::FORBIDDEN (optional == forbidden)
        */
        template <typename IN, typename OUT>
        inline void encode(IN const& input, OUT && output, pad const padding_option = pad::OPTIONAL) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
        {
            detail::__encode<detail::c_api::mtrp_b64url_encode>(input, std::forward<OUT>(output), padding_option);
        }

        /** Encoder
         * 
         * @param input A reference to the ENCODED message container (can be any ContiguousContainer, like std::vector or std::string)
         * @param output A reference to the future DECODED message container (can be any ContiguousContainer, like std::vector or std::string)
         * @param padding_option pad::OPTIONAL/pad::MANDATORY/pad::FORBIDDEN
        */
        template <typename IN, typename OUT>
        inline bool decode(IN const& input, OUT && output, pad const padding_option = pad::OPTIONAL) noexcept(noexcept(std::declval<OUT>().resize(0xffff)))
        {
            return detail::__decode<detail::c_api::mtrp_b64url_decode>(input, std::forward<OUT>(output), padding_option);
        }
    }
}
