#pragma once

#include <string>
#include <string_view>

#include <gsl/gsl>
#include <wil/result_macros.h>

namespace wacpp::str::detail
{

template <size_t N>
    requires (N > 3)
class Utf8Range
{
public:
    using Input = std::wstring_view;
    using Output = gsl::span<char>;
    class Iterator;
    struct Sentinel {};

    Utf8Range(Input input) noexcept : m_input{ input }, m_block{}
    {}

    Iterator begin()
    {
        return { m_input, Output{m_block} };
    }

    Sentinel end()
    {
        return {};
    }

    class Iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = char;

        Iterator() noexcept : m_source{}, m_next_offset{}, m_block{}, m_index{}
        {}

        Iterator(Input source, Output block)
            : m_source{ source }, m_next_offset{}, m_block{ block }, m_index{ m_block.size() - 1 }
        {
            move_next();
        }

        char operator*() const
        {
            return m_block[m_index];
        }

        Iterator& operator++()
        {
            if (!at_end())
            {
                move_next_char();
            }

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator prev = *this;
            ++*this;
            return prev;
        }

        bool operator==(Sentinel) const noexcept
        {
            return at_end();
        }

    private:
        bool at_block_end() const noexcept
        {
            return m_index == m_block.size() - 1;
        }

        bool at_end() const noexcept
        {
            return (m_next_offset >= m_source.size()) && at_block_end();
        }

        void move_next_char()
        {
            if (!at_block_end())
            {
                ++m_index;
            }
            else
            {
                move_next();
            }
        }

        void move_next()
        {
            if (at_end())
            {
                return;
            }

            if (FAILED(try_move_next<false>()))
            {
                const auto hr = try_move_next<true>();
                THROW_IF_FAILED_MSG(hr, "Error near offset %llu while attempting UTF-8 conversion", m_next_offset);
            }

            m_index = 0;
        }

        template <bool OneMore>
        HRESULT try_move_next()
        {
            const auto input_block = next_block<OneMore>();
            const auto input_size = gsl::narrow<int>(input_block.size());
            static constexpr const auto output_size = gsl::narrow<int>(N);
            const auto actual_size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, input_block.data(), input_size, m_block.data(), output_size, nullptr, nullptr);
            if (actual_size == 0)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            m_block = m_block.subspan(0, actual_size);
            m_next_offset += actual_size;
            return S_OK;
        }

        template <bool OneMore>
        auto next_block() const
        {
            static constexpr const auto M = (N / 4) + (OneMore ? 1 : 0);
            const auto max_input_size = m_source.size() - m_next_offset;
            const auto input_size = (M <= max_input_size) ? M : max_input_size;
            return m_source.substr(m_next_offset, input_size);
        }

        Input m_source;
        size_t m_next_offset;
        Output m_block;
        size_t m_index;
    };

private:
    Input m_input;
    std::array<char, N> m_block;
};

}

namespace wacpp::str
{

template <size_t N>
    requires (N > 3)
detail::Utf8Range<N> to_utf8(const std::wstring& utf16_input)
{
    return { std::wstring_view{utf16_input} };
}

std::string to_utf8(const std::wstring& utf16_input);

}