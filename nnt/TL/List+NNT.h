
# ifndef __NNT_CORE_LIST_03F2316AB5314A23AFA54CDB13D9A0B7_H_INCLUDED
# define __NNT_CORE_LIST_03F2316AB5314A23AFA54CDB13D9A0B7_H_INCLUDED

# ifdef NNT_CXX

# ifdef NNT_USER_SPACE

# include <list>

# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

# ifdef NNT_USER_SPACE

template <typename valT>
class _list
{
    typedef ::std::list<valT> stl_type;
    
public:
    
    typedef typename stl_type::const_iterator const_iterator;
    typedef typename stl_type::iterator iterator;
    typedef valT value_type;
    typedef typename stl_type::size_type size_type;
    typedef typename stl_type::reference reference;
    typedef typename stl_type::const_reference const_reference;
    
    const_iterator begin() const
    {
        return _stl.begin();
    }
    
    iterator begin()
    {
        return _stl.begin();
    }
    
    const_iterator end() const
    {
        return _stl.end();
    }
    
    iterator end()
    {
        return _stl.end();
    }
    
    void push_back(value_type const& r)
    {
        _stl.push_back(r);
    }
    
    void push_front(value_type const& r)
    {
        _stl.push_front(r);
    }
    
    size_type size() const
    {
        return _stl.size();
    }
    
    size_type count() const
    {
        return _stl.size();
    }
    
    size_type length() const
    {
        return _stl.size();
    }
    
    void clear()
    {
        _stl.clear();
    }
    
    void resize(size_type sz, value_type v = value_type())
    {
        _stl.resize(sz, v);
    }
    
    reference front()
    {
        return _stl.front();
    }
    
    reference back()
    {
        return _stl.back();
    }
    
    const_reference front() const
    {
        return _stl.front();
    }
    
    const_reference back() const
    {
        return _stl.back();
    }
    
    operator stl_type& ()
    {
        return _stl;
    }
    
    operator stl_type const& () const
    {
        return _stl;
    }
    
protected:
    
    stl_type _stl;
    
};

template <typename valT>
class list
: public _list<valT>
{
    
};

template <typename valT>
class list <valT*>
: public _list<valT*>
{
    typedef _list<valT*> super;    
    
public:
    
    typedef typename super::iterator iterator;
    
    void clear_destroy()
    {
        for (iterator iter = this->begin();
             iter != this->end();
             ++iter)
        {
            delete *iter;
        }
        this->clear();
    }
    
    void clear_drop()
    {
        for (iterator iter = this->begin();
             iter != this->end();
             ++iter)
        {
            if (*iter)
                (*iter)->drop();
        }
        this->clear();
    }
    
    template <typename val2T>
    void push_back(val2T const& r, typename is_instance<val2T>::type* trait = NULL)
    {
        this->_push_back(r, trait);
    }
    
    template <typename val2T>
    void push_front(val2T const& r, typename is_instance<val2T>::type* trait = NULL)
    {
        this->_push_front(new valT(r));
    }
    
    template <typename iterT>
    void erase_destroy(iterT const& iter)
    {
        delete (*iter);
        this->_stl.erase(iter);
    }
    
    template <typename iterT>
    void erase_drop(iterT const& iter)
    {
        if (*iter)
            (*iter)->drop();
        this->_stl.erase(iter);
    }
    
protected:
    
    template <typename val2T>
    void _push_back(val2T const& r, instance_type*)
    {
        this->_stl.push_back(new valT(r));
    }
    
    template <typename val2T>
    void _push_back(val2T const& r, pointer_type*)
    {
        this->_stl.push_back(r);        
    }
    
    template <typename val2T>
    void _push_front(val2T const& r, instance_type*)
    {
        this->_stl.push_front(new valT(r));
    }
    
    template <typename val2T>
    void _push_front(val2T const& r, pointer_type*)
    {
        this->_stl.push_front(r);        
    }
    
};

template <typename valT>
class pointer_list
: public list<valT*>
{
    typedef list<valT*> super;
    
public:
    
    typedef typename super::size_type size_type;
    typedef typename super::iterator iterator;
    typedef valT value_type;

    ~pointer_list()
    {
        this->clear();
    }
    
    void clear()
    {
        this->clear_destroy();
    }
    
    void resize(size_type sz, bool mem = true)
    {
        size_type const cur = this->size();
        if (cur > sz)
        {
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, sz);            
                while(iter != this->end())
                {
                    delete *iter;
                    ++iter;
                }
            }
            super::resize(sz, NULL);            
        }
        else if (cur < sz)
        {
            super::resize(sz, NULL);
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, cur);  
                while (iter != this->end())
                {
                    *iter = new value_type;
                    ++iter;
                }
            }
        }
    }
    
};

template <typename valT>
class refpointer_list
: public list<valT*>
{
    typedef list<valT*> super;
    
public:
    
    typedef typename super::size_type size_type;
    typedef typename super::iterator iterator;
    typedef valT value_type;
    
    ~refpointer_list()
    {
        this->clear();
    }
    
    void clear()
    {
        this->clear_drop();
    }
    
    void resize(size_type sz, bool mem = true)
    {
        size_type const cur = this->size();
        if (cur > sz)
        {
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, sz);
                while(iter != this->end())
                {
                    if (*iter)
                        (*iter)->drop();
                    ++iter;
                }
            }
            super::resize(sz, NULL);
        }
        else if (cur < sz)
        {
            super::resize(sz, NULL);
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, cur);
                while (iter != this->end())
                {
                    *iter = new value_type;
                    ++iter;
                }
            }
        }
    }
    
};

template <class ValueT>
inline_impl list<ValueT>& operator << (list<ValueT>& left, ValueT right)
{
    left.push_back(right);
    return left;
}

# else // kernel space.

template <typename ValT>
class list
{

protected:

# ifdef NNT_MSVC

    struct _entry
    {
        LIST_ENTRY entry;
        ValT val;
    };   

# endif

# ifdef NNT_BSD

    struct _entry
    {
        STAILQ_ENTRY(_entry) entry;
        ValT val;
    };

# endif

    typedef alloc::Heap<_entry> _heap;

public:

    typedef ValT value_type;

    list()
    {
# ifdef NNT_MSVC
        ::InitializeListHead(*this);
# endif

# ifdef NNT_BSD
        _lst.stqh_first = NULL;
        _lst.stqh_last = &_lst.stqh_first;
        STAILQ_INIT(&_lst);
# endif
    }

    ~list()
    {
        this->clear();
    }

    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }

    bool empty() const
    {
# ifdef NNT_MSVC
        return ::IsListEmpty(*this);
# endif

# ifdef NNT_BSD
        return STAILQ_EMPTY(&_lst);
# endif
    }

    void push_front(value_type const& val)
    {
        _entry* obj = _heap::Create();
        obj->val = val;

# ifdef NNT_MSVC
        ::InsertHeadList(*this, &obj->entry);
# endif

# ifdef NNT_BSD
        STAILQ_INSERT_HEAD(&_lst, obj, _lst.entry);
# endif
    }

    void push_back(value_type const& val)
    {
        _entry* obj = _heap::Create();
        obj->val = val;

# ifdef NNT_MSVC
        ::InsertTailList(*this, &obj->entry);
# endif

# ifdef NNT_BSD
        STAILQ_INSERT_TAIL(&_lst, obj, _lst.entry);
# endif
    }

    value_type pop()
    {
# ifdef NNT_MSVC
        PLIST_ENTRY pent = ::RemoveHeadList(*this);
        _entry* pobj = CONTAINING_RECORD(pent, _entry, entry);
        value_type ret = pobj->val;
        _heap::Free(pobj);
        return ret;
# endif

# ifdef NNT_BSD
        _entry* pobj = STAILQ_FIRST(&_lst);
        STAILQ_REMOVE_HEAD(&_lst, entry);
        value_type ret = pobj->val;
        _heap::Free(pobj);
        return ret;
# endif
    }

# ifdef NNT_MSVC

    operator PLIST_ENTRY () const
    {
        return (PLIST_ENTRY)&_lst;
    }

protected:

    _entry _lst;

# endif

# ifdef NNT_BSD

protected:

    STAILQ_HEAD(_entryhead, _entry) _lst;

# endif

};

# endif // user space.

NNT_END_NS
NNT_END_HEADER_CXX

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

typedef ::nnt::core::list<id> _NSList;
typedef _NSList::iterator NSListIterator;
typedef _NSList::const_iterator NSListConstIterator;

@interface NSList : NNTObject {
    _NSList *_list;
}

@property (nonatomic, discard) _NSList *container;

- (NSListIterator)begin;
- (NSListIterator)end;

@end

NNT_END_HEADER_OBJC

# endif // objc

# endif // cxx

# endif
