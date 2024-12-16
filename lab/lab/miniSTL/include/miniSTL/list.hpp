#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <limits>
#include <stdexcept>
#include <utility>
#include <compare>
#include <initializer_list>

template <class T>
struct ListBaseNode
{
    ListBaseNode *m_next;
    ListBaseNode *m_prev;

    inline T &value();

    inline T const &value() const;
};
template <class T>
struct ListValueNode : ListBaseNode<T>
{
    union
    {
        T m_value;
    };
};
template <class T>
inline T &ListBaseNode<T>::value()
{
    return static_cast<ListValueNode<T> &>(*this).m_value;
}
template <class T>
inline T const &ListBaseNode<T>::value() const
{
    return static_cast<ListValueNode<T> const &>(*this).m_value;
}
template <class T, class Alloc = std::allocator<T>>
struct List
{
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = T const *;
    using reference = T &;
    using const_reference = T const &;

private:
    using ListNode = ListBaseNode<T>;
    using AllocNode = std::allocator_traits<Alloc>::template rebind_alloc<ListValueNode<T>>;

    ListNode m_dummy;
    size_t m_size;
    [[no_unique_address]] Alloc m_alloc;

public:
    void init_move(List &&that)
    {
        auto prev = that.m_dummy.m_prev;
        auto next = that.m_dummy.m_next;
        prev->m_next = &m_dummy;
        next->m_prev = &m_dummy;
        m_dummy = that.m_dummy;
        m_size = that.m_size;
        that.m_dummy.m_next = that.m_dummy.m_prev = &that.m_dummy;
        that.m_size = 0;
    }
    template <std::input_iterator InputIt>
    void init_move(InputIt first, InputIt last)
    {
        m_size = 0;
        ListNode *prev = &m_dummy;
        while (first != last)
        {
            ListNode *node = AllocNode{m_alloc}.allocate(1);
            prev->m_next = node;
            node->m_prev = prev;
            std::__construct_at(&node->value(), *first);
            prev = node;
            ++first;
            ++m_size;
        }
        m_dummy.m_prev = prev;
        prev->m_next = &m_dummy;
    }
    void init_move(size_t n)
    {
        ListNode *prev = &m_dummy;
        while (n)
        {
            ListNode *node = AllocNode{m_alloc}.allocate(1);
            prev->m_next = node;
            node->m_prev = prev;
            std::__construct_at(&node->value());
            prev = node;
            --n;
        }
        m_dummy.m_prev = prev;
        prev->m_next = &m_dummy;
        m_size = n;
    }
    void init_move(size_t n, T const &val)
    {
        ListNode *prev = &m_dummy;
        while (n)
        {
            ListNode *node = AllocNode{m_alloc}.allocate(1);
            prev->m_next = node;
            node->m_prev = prev;
            std::__construct_at(&node->value(), val);
            prev = node;
            --n;
        }
        m_dummy.m_prev = prev;
        prev->m_next = &m_dummy;
        m_size = n;
    }
    List()
    {
        m_dummy.m_next = &m_dummy;
        m_dummy.m_prev = &m_dummy;
        m_size = 0;
    }
    List(List &&that) noexcept : m_size(std::move(that.m_size)), m_alloc(std::move(that.m_alloc))
    {
        init_move(std::move(that));
    }

    List(List const &that) noexcept : m_size(std::move(that.m_size)), m_alloc(std::move(that.m_alloc))
    {
        init_move(std::move(that));
    }
    List &operator=(List const &that)
    {
        assign(that.cbegin(), that.cend());
        return *this;
    }

    bool empty() noexcept
    {
        return m_dummy.m_prev = m_dummy.m_next;
    }

    T &front() noexcept
    {
        return m_dummy.m_next->value();
    }

    T &back() noexcept
    {
        return m_dummy.m_prev->value();
    }

    T const &front() const noexcept
    {
        return m_dummy.m_next->value();
    }

    T const &back() const noexcept
    {
        return m_dummy.m_prev->value();
    }

    explicit List(size_t n, Alloc const &alloc = Alloc()) : m_alloc(alloc)
    {
        init_move(n);
    }

    List(size_t n, T const &val, Alloc const &alloc = Alloc()) : m_alloc(alloc)
    {
        init_move(n, val);
    }

    template <std::input_iterator InputIt>
    List(InputIt first, InputIt last, Alloc const &alloc = Alloc())
    {
        init_move(first, last);
    }

    List(std::initializer_list<T> ilist, Alloc const &alloc = Alloc()) : List(ilist.begin(), ilist.end(), alloc) {}

    List &operator=(std::initializer_list<T> ilist)
    {
        assign(ilist);
        return *this;
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return m_size;
    }

    template <std::input_iterator InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        init_move(first, last);
    }

    void assign(std::initializer_list<T> ilist)
    {
        clear();
        init_move(ilist.begin(), ilist.end());
    }

    void assign(size_t n, T const &val)
    {
        clear();
        init_move(n, val);
    }

    void push_back(T const &val)
    {
        ++m_size;
        ListNode *node = AllocNode{m_alloc}.allocate(1);
        node->m_prev = m_dummy.m_prev;
        node->m_next = &m_dummy;
        m_dummy.m_prev->m_next = node;
        m_dummy.m_prev = node;
        std::__construct_at(&node->value(), val);
    }

    void push_back(T &&val)
    {
        ++m_size;
        ListNode *Node = AllocNode{m_alloc}.allocate(1);
        Node->m_prev = m_dummy.m_prev;
        Node->m_next = &m_dummy;
        m_dummy.m_prev->m_next = Node;
        m_dummy.m_prev = Node;
        std::__construct_at(&Node->value(), std::move(val));
    }

    void push_front(T const &val)
    {
        ++m_size;
        ListNode *node = AllocNode{m_alloc}.allocate(1);
        m_dummy.m_next->m_prev = node;
        node->m_next = m_dummy.m_next;
        node->m_prev = &m_dummy;
        m_dummy.m_next = node;
        std::__construct_at(&node->value(), val);
    }

    void push_front(T &&val)
    {
        ++m_size;
        auto node = AllocNode{m_alloc}.allocate(1);

        m_dummy.m_next->m_prev = node;
        node->m_next = m_dummy.m_next;
        node->m_prev = &m_dummy;
        m_dummy.m_next = node;
        std::__construct_at(&node->value(), std::move(val));
    }

    ~List()
    {
        clear();
    }

    void clear() noexcept
    {
        ListNode *cur = m_dummy.m_next;
        while (cur != &m_dummy)
        {
            auto temp = cur->m_next;
            std::destroy_at(&cur->value());
            AllocNode{m_alloc}.deallocate(static_cast<ListValueNode<T> *>(cur), 1);
            cur = temp;
        }
        m_dummy.m_next = &m_dummy;
        m_dummy.m_prev = &m_dummy;
        m_size = 0;
    }

    struct iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

    private:
        ListNode *m_curr;

        friend List;

        explicit iterator(ListNode *curr) : m_curr(curr) {};

    public:
        iterator() = default;

        iterator &operator++() noexcept
        {
            m_curr = m_curr->m_next;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            auto ret = *this;
            m_curr = m_curr->m_next;
            return ret;
        }

        iterator &operator--() noexcept
        {
            m_curr = m_curr->m_prev;
            return *this;
        }

        iterator operator--(int) noexcept
        {
            auto ret = *this;
            m_curr = m_curr->m_prev;
            return ret;
        }

        T &operator*() const noexcept
        {
            return m_curr->value();
        }

        bool operator!=(iterator const &that) const noexcept
        {
            return !(*this == that);
        }

        bool operator==(iterator const &that)
        {
            return m_curr == that.m_curr;
        }
    };

    struct const_iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T const *;
        using reference = T const &;

    private:
        ListNode const *m_curr;

        friend List;

        explicit const_iterator(ListNode const *curr) noexcept : m_curr(curr)
        {
        }

    public:
        const_iterator() = default;

        const_iterator(iterator that) noexcept : m_curr(that.m_curr) {}

        explicit operator iterator() noexcept
        {
            return iterator{const_cast<ListNode *>(m_curr)};
        }

        const_iterator &operator++() noexcept
        {
            m_curr = m_curr->m_next;
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            auto ret = *this;
            m_curr = m_curr->m_next;
            return ret;
        }

        const_iterator &operator--() noexcept
        {
            m_curr = m_curr->m_prev;
            return *this;
        }

        const_iterator operator--(int) noexcept
        {
            auto ret = *this;
            m_curr = m_curr->m_prev;
            return ret;
        }

        T const &operator*() const noexcept
        {
            return m_curr->value();
        }

        bool operator!=(const_iterator const &that)
        {
            return !(*this == that);
        }

        bool operator==(const_iterator const &that)
        {
            return m_curr == that.m_curr;
        }
    };

    iterator begin() noexcept
    {
        return iterator{m_dummy.m_next};
    }

    iterator end() noexcept
    {
        return iterator{&m_dummy};
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator{m_dummy.m_next};
    }

    const_iterator cend() const noexcept
    {
        return const_iterator{&m_dummy};
    }

    const_iterator begin() const noexcept
    {
        return cbegin();
    }

    const_iterator end() const noexcept
    {
        return cend();
    }

    using reverse_iterator = std::reverse_iterator<iterator>;
    using reverse_const_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() noexcept
    {
        return std::make_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::make_reverse_iterator(begin());
    }

    reverse_const_iterator crbegin() const noexcept
    {
        return std::make_reverse_iterator(cend());
    }

    reverse_const_iterator crend()
    {
        return std::make_reverse_iterator(cbegin());
    }

    reverse_const_iterator rbegin() const noexcept
    {
        return crbegin();
    }

    reverse_const_iterator rend() const noexcept
    {
        return crend();
    }

    iterator erase(const_iterator pos) noexcept
    {
        auto noConstNode = const_cast<ListNode *>(pos.m_curr);

        auto next = noConstNode->m_next;
        noConstNode->m_next->m_prev = noConstNode->m_prev;
        noConstNode->m_prev->m_next = noConstNode->m_next;
        std::destroy_at(&noConstNode->value());

        AllocNode{m_alloc}.deallocate(static_cast<ListValueNode<T> *>(noConstNode), 1);
        --m_size;
        return iterator{next};
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase(first);
        }
        return iterator(first);
    }

    void pop_front() noexcept
    {
        erase(this->begin());
    }

    void pop_back() noexcept
    {
        erase(this->rbegin());
    }

    iterator insert(const_iterator pos, const T &val)
    {
        ++m_size;
        ListNode *curr = AllocNode{m_alloc}.allocate(1);
        auto *next = const_cast<ListNode *>(pos.m_curr);

        curr->m_prev = next->m_prev;
        next->m_prev->m_next = curr;
        curr->m_next = next;
        next->m_prev = curr;

        std::construct_at(&curr->value(), val);
        return iterator{curr};
    }

    iterator insert(const_iterator pos, T &&val)
    {
        ++m_size;
        ListNode *curr = AllocNode{m_alloc}.allocate(1);
        auto *next = const_cast<ListNode *>(pos.m_curr);

        curr->m_prev = next->m_prev;
        next->m_prev->m_next = curr;
        curr->m_next = next;
        next->m_prev = curr;

        std::construct_at(&curr->value(), std::move(val));
        return iterator{curr};
    }

    iterator insert(const_iterator pos, size_t n, T const &val)
    {
        m_size += n;
        auto result = pos;
        bool isFirstInsert = true;

        while (n)
        {
            if (isFirstInsert)
            {
                result = insert(pos, val);
                ++pos;
                isFirstInsert = false;
                ++m_size;
                --n;
                continue;
            }
            --n;
            ++m_size;
            insert(pos, val);
            ++pos;
        }

        return iterator{result};
    }

    template <std::input_iterator InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        auto result = pos;
        bool isFirstInsert = true;

        while (first != last)
        {
            if (isFirstInsert)
            {
                result = insert(pos, *first);
                ++pos;
                ++first;
                isFirstInsert = false;
                ++m_size;
                continue;
            }
            ++m_size;
            insert(pos, *first);
            ++pos;
            ++first;
        }
        return iterator{result};
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        return insert(pos, ilist.begin(), ilist.end());
    }

    bool operator==(List const &that) const noexcept
    {
        if (that.size() != m_size)
            return false;
        const_iterator thisIterator = this->cbegin();
        const_iterator thatIterator = that.cbegin();
        const_iterator thisEnd = this->cend();
        const_iterator thatEnd = that.cend();

        while (thisIterator != thisEnd && thatIterator != thatEnd)
        {
            auto temp1 = *thisIterator;
            auto temp2 = *thatIterator;
            if (temp1 != temp2)
            {
                return false;
            }
            ++thisIterator;
            ++thatIterator;
        }

        return true;
    }
};
