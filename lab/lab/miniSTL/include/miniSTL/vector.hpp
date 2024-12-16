#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <limits>
#include <stdexcept>
#include <utility>
#include <compare>
#include <initializer_list>

template <class T, class Alloc = std::allocator<T>>
struct Vector
{
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = T const *;
    using reference = T &;
    using const_reference = T const &;
    using iterator = T *;
    using const_iterator = T const *;
    using reverse_iterator = std::reverse_iterator<T *>;
    using const_reverse_iterator = std::reverse_iterator<T const *>;

    T *m_data;
    size_t m_size;
    size_t m_cap;
    [[no_unique_address]] Alloc m_alloc;

    Vector()
    {
        m_data = nullptr;
        m_size = 0;
        m_cap = 0;
    }

    Vector(std::initializer_list<T> ilist, Alloc const &alloc = Alloc()) : Vector(ilist.begin(), ilist.end(), alloc)
    {
    }
    explicit Vector(size_t n, Alloc const &alloc = Alloc()) : m_alloc(alloc)
    {
        m_data = m_alloc.allocate(n);
        m_cap = m_size = n;
        for (size_t i = 0; i != n; i++)
        {
            std::__construct_at(&m_data[i]);
        }
    }
    Vector(size_t n, T const &val, Alloc const &alloc = Alloc())
    {
        m_data = m_alloc.allocate(n);
        m_cap = n;
        m_size = n;
        for (auto i = 0; i != n; ++i)
        {
            std::__construct_at(&m_data[i], val);
        }
    }

    template <std::random_access_iterator InputIt>
    Vector(InputIt first, InputIt last, Alloc const &alloc = Alloc())
    {

        m_size = last - first;
        m_cap = m_size;
        m_data = m_alloc.allocate(m_size);
        for (auto i = 0; i < m_size; ++i)
        {
            std::construct_at(&m_data[i], *first);
            ++first;
        }
    }

    void clear() noexcept
    {
        for (size_t i = 0; i != m_size; i++)
        {
            std::destroy_at(&m_data[i]);
        }
        m_size = 0;
    }

    void resize(size_t n)
    {
        if (n < m_size)
        {
            for (size_t i = n; i != m_size; i++)
            {
                std::destroy_at(&m_data[i]);
            }
            m_size = n;
        }
        else if (n > m_size)
        {
            reserve(n);
            for (size_t i = m_size; i != n; i++)
            {
                std::__construct_at(&m_data[i]);
            }
        }
        m_size = n;
    }

    void resize(size_t n, T const &val)
    {
        if (n < m_size)
        {
            for (size_t i = n; i != m_size; i++)
            {
                std::destroy_at(&m_data[i]);
            }
            m_size = n;
        }
        else if (n > m_size)
        {
            reserve(n);
            for (size_t i = m_size; i != n; i++)
            {
                std::__construct_at(&m_data[i], val);
            }
        }
        m_size = n;
    }

    void shrink_to_fit()
    {
        auto old_data = m_data;
        auto old_cap = m_cap;
        m_cap = m_size;
        if (m_size == 0)
        {
            m_data = nullptr;
        }
        else
        {
            m_data = m_alloc.allocate(m_size);
        }
        if (old_cap != 0) [[likely]]
        {
            for (size_t i = 0; i != m_size; i++)
            {
                std::__construct_at(&m_data[i], std::move_if_noexcept(old_data[i])); // m_data[i] = std::move(old_data[i])
                std::destroy_at(&old_data[i]);
            }
            m_alloc.deallocate(old_data, old_cap);
        }
    }

    void reserve(size_t n)
    {
        if (n <= m_cap)
            return;
        n = std::max(n, m_cap * 2);
        T *new_data = m_alloc.allocate(n);
        for (size_t i = 0; i < m_size; ++i)
        {
            std::construct_at(&new_data[i], std::move(m_data[i]));
            std::destroy_at(&m_data[i]);
        }
        if (m_data)
        {
            m_alloc.deallocate(m_data, m_cap);
        }
        m_data = new_data;
        m_cap = n;
    }

    [[nodiscard]] size_t capacity() const noexcept
    {
        return m_cap;
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return m_data == nullptr;
    }

    T const &operator[](size_t i) const noexcept
    {
        return m_data[i];
    }

    T &operator[](size_t i) noexcept
    {
        return m_data[i];
    }

    T const &at(size_t i) const
    {
        return m_data[i];
    }

    T &at(size_t i)
    {
        return m_data[i];
    }

    Vector(Vector &&that) noexcept : m_data(that.m_data), m_size(that.m_size), m_cap(that.m_cap),
                                     m_alloc(std::move(that.m_alloc))
    {
        that.m_data = nullptr;
        that.m_size = 0;
        that.m_cap = 0;
    }

    Vector(Vector &&that, Alloc const &alloc) noexcept : m_data(that.m_data), m_size(that.m_size), m_cap(that.m_cap),
                                                         m_alloc(alloc)
    {
        that.m_data = nullptr;
        that.m_size = 0;
        that.m_cap = 0;
    }
    Vector &operator=(Vector &&that) noexcept
    {
        for (auto i = 0; i < m_size; ++i)
        {
            std::destroy_at(&m_data[i]);
        }
        if (!m_cap)
        {
            m_alloc.deallocate(m_data, m_cap);
        }
        m_data = that.m_data;
        m_size = that.m_size;
        m_cap = that.m_cap;
        that.m_data = nullptr;
        that.m_size = 0;
        that.m_cap = 0;
        return *this;
    }

    void swap(Vector &that) noexcept
    {
        std::swap(m_data, that.m_data);
        std::swap(m_size, that.m_size);
        std::swap(m_cap, that.m_cap);
        std::swap(m_alloc, that.m_alloc);
    }

    Vector(Vector const &that)
        : m_alloc(that.m_alloc), m_size(that.m_size), m_cap(that.m_size), m_data(nullptr)
    {
        if (m_size != 0)
        {
            m_data = m_alloc.allocate(m_size);
            std::uninitialized_copy(that.m_data, that.m_data + m_size, m_data);
        }
    }

    Vector(Vector const &that, Alloc const &alloc)
        : m_alloc(alloc), m_size(that.m_size), m_cap(that.m_cap), m_data(nullptr)
    {
        if (m_size != 0)
        {
            // 分配内存
            m_data = m_alloc.allocate(m_size);

            // 拷贝构造元素，提供异常安全性
            for (size_t i = 0; i < m_size; ++i)
            {
                std::construct_at(&m_data[i], that.m_data[i]);
            }
        }
    }

    Vector &operator=(Vector const &that) noexcept
    {
        reserve(that.m_size);
        m_size = that.m_size;
        for (size_t i = 0; i != m_size; i++)
        {
            std::construct_at(&m_data[i], that.m_data[i]);
        }
        return *this;
    }

    T const &front() const noexcept
    {
        return *m_data;
    }

    T &front() noexcept
    {
        return *m_data;
    }

    T const &back() const noexcept
    {
        return m_data[m_size - 1];
    }

    T &back() noexcept
    {
        return m_data[m_size - 1];
    }

    void push_back(T const &val)
    {
        std::construct_at(&m_data[m_size], std::move(val));
        ++m_size;
    }

    void push_back(T &&val)
    {
        std::construct_at(&m_data[m_size], std::move(val));
        ++m_size;
    }

    T *data() noexcept
    {
        return m_data;
    }

    T const *data() const noexcept
    {
        return m_data;
    }

    T const *cdata() const noexcept
    {
        return m_data;
    }

    T *begin() noexcept
    {
        return m_data;
    }

    T *end() noexcept
    {
        return m_data + m_size;
    }

    T const *begin() const noexcept
    {
        return m_data;
    }

    T const *end() const noexcept
    {
        return m_data + m_size;
    }

    T const *cbegin() const noexcept
    {
        return m_data;
    }

    T const *cend() const noexcept
    {
        return m_data + m_size;
    }

    std::reverse_iterator<T *> rbegin() noexcept
    {
        return std::make_reverse_iterator(m_data + m_size);
    }

    std::reverse_iterator<T *> rend() noexcept
    {
        return std::make_reverse_iterator(m_data);
    }

    std::reverse_iterator<T const *> crbegin() const noexcept
    {
        return std::make_reverse_iterator(m_data + m_size);
    }

    std::reverse_iterator<T const *> crend() const noexcept
    {
        return std::make_reverse_iterator(m_data);
    }

    void pop_back() noexcept
    {
        m_size -= 1;
        std::destroy_at(&m_data[m_size]);
    }

    T *erase(T const *it) noexcept(std::is_nothrow_move_assignable_v<T>)
    {
        auto idx = it - m_data;
        --m_size;
        for (auto i = idx; i < m_size; ++i)
        {
            m_data[i] = std::move(m_data[i + 1]);
        }
        std::destroy_at(&m_data[m_size]);
        return const_cast<T *>(it);
    }
    T *erase(const T *first, const T *last) noexcept(std::is_nothrow_move_assignable_v<T>)
    {
        size_t count = last - first;
        size_t start_index = first - m_data;
        size_t end_index = last - m_data;
        for (size_t i = end_index; i < m_size; ++i)
        {
            m_data[i - count] = std::move(m_data[i]);
        }
        for (size_t i = m_size - count; i < m_size; ++i)
        {
            std::destroy_at(&m_data[i]);
        }
        m_size -= count;
        return const_cast<T *>(first);
    }

    void assign(size_t n, T const &val)
    {
        clear();
        reserve(n);
        m_size = n;
        for (auto i = 0; i < n; ++i)
        {
            std::construct_at(&m_data[i], val);
        }
    }

    template <std::random_access_iterator InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        const auto n = last - first;
        reserve(n);
        m_size = n;
        for (auto i = 0; i < n; ++i)
        {
            std::construct_at(&m_data[i], *first);
            ++first;
        }
    }

    void assign(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
    }

    Vector &operator=(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
        return *this;
    }

    T *insert(T const *it, T &&val)
    {
        auto idx = it - m_data;
        if (m_size + 1 >= m_cap)
        {
            reserve(m_size + 1);
        }
        for (auto i = m_size; i > idx; --i)
        {
            std::construct_at(&m_data[i], std::move(m_data[i - 1]));
            std::destroy_at(&m_data[i - 1]);
        }
        m_size++;
        std::construct_at(&m_data[idx], std::move(val));
        return m_data + idx;
    }

    T *insert(T const *it, T const &val)
    {
        auto idx = it - m_data;
        if (m_size + 1 >= m_cap)
        {
            reserve(m_size + 1);
        }
        for (auto i = m_size; i > idx; --i)
        {
            std::construct_at(&m_data[i], std::move(m_data[i - 1]));
            std::destroy_at(&m_data[i - 1]);
        }
        m_size++;
        std::construct_at(&m_data[idx], val);
        return m_data + idx;
    }

    T *insert(T const *it, size_t n, T const &val)
    {
        auto idx = it - m_data;
        if (!n)
            return const_cast<T *>(it);
        if (m_size + n >= m_cap)
        {
            reserve(m_size + n);
        }

        for (auto i = m_size; i > idx; --i)
        {
            std::construct_at(&m_data[i + n - 1], std::move(m_data[i - 1]));
            std::destroy_at(&m_data[i - 1]);
        }

        m_size += n;

        for (auto i = idx; i < idx + n; ++i)
        {
            std::construct_at(&m_data[i], val);
        }

        return m_data + idx;
    }

    template <std::random_access_iterator InputIt>
    T *insert(T const *it, InputIt first, InputIt last)
    {
        auto idx = it - m_data;
        auto num = last - first;
        if (!num)
            return const_cast<T *>(it);

        if (m_size + num >= m_cap)
        {
            reserve(m_size + num);
        }

        for (auto i = m_size; i > idx; --i)
        {
            std::construct_at(&m_data[i + num - 1], std::move(m_data[i - 1]));
            std::destroy_at(&m_data[i - 1]);
        }
        m_size += num;

        for (auto i = idx; i < idx + num; ++i)
        {
            std::construct_at(&m_data[i], *first);
            ++first;
        }

        return m_data + idx;
    }

    T *insert(T const *it, std::initializer_list<T> ilist)
    {
        return insert(it, ilist.begin(), ilist.end());
    }

    ~Vector()
    {
        for (auto i = 0; i != m_size; ++i)
        {
            std::destroy_at(&m_data[i]);
        }
        if (!m_cap)
        {
            m_alloc.deallocate(m_data, m_cap);
        }
    }

    bool operator==(Vector const &that) const noexcept
    {
        if (that.m_size != m_size)
        {
            return false;
        }

        for (auto i = 0; i < m_size; ++i)
        {
            if (that.m_data[i] != m_data[i])
            {
                return false;
            }
        }

        return true;
    }
};