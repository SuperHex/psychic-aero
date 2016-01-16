#ifndef __Data_List__
#define __Data_List__

namespace Data
{
    template< typename a >
    struct basic_list
    {
        a value;
        basic_list<a>* next;
        basic_list();
        virtual ~basic_list(){ delete next; };
    };

    template< typename a >
    struct Nil : public basic_list<a> { };

    template< typename a >
    struct List
    {
        template< typename Head, typename ... Tail >
        basic_list<a>* make_list(const Head& h, const Tail& ... t)
        {
            auto node = new basic_list<Head>();
            node->value = h;
            node->next = make_list(t ...);
        }

        template< typename Last >
        basic_list<Last>* make_list(const Last& l)
        {
            auto node = new basic_list<Last>();
            node->value = l;
            node->next = new Nil<Last>();
        }
    };
}

#endif
