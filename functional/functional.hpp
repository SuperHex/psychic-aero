#ifndef __Functional__
#define __Functional__

namespace until
{
    template< typename T >
    struct Monoid
    {
    public:
        Monoid();
        virtual ~Monoid();
        static T mempty();
        static T mappend(const T&, const T&);
    };

    template< typename T >
    struct Maybe
    {
    public:
        T value;
        bool isNothing = true;
    };

    template< typename a >
    struct Monoid<Maybe<a>>
    {
        static Maybe<a> mempty()
        {
            Maybe<a> r;
            return r;
        }

        static Maybe<a> mappend(const Maybe<a>& a1, const Maybe<a>& a2)
        {
            if (a1.isNothing || a2.isNothing)
            {
                Maybe<a> no;
                return no;
            }
            else
            {
                return mappend(a1.value, a2.value);
            }
        }
    };

    template< template< typename ... > class f >
    struct Functor
    {
        template< typename a, typename b >
        static f<b> fmap(b(*)(const a&), const f<a>&);
    };

    template< template< typename ... > class f >
    struct Applicative
    {
        template< typename a >
        static f<a> pure(const a&);

        template< typename a, typename b >
        static f<b> ap(const f<b(*)(const a&)>, const f<a>&);
    };

    template< template< typename ... > class m >
    struct Monad
    {
        template< typename a >
        static m<a> mreturn(const a&);

        template< typename a, typename b >
        static m<b> mbind(const m<a>&, const m<b>(*)(const a&));
    };

    template< >
    struct Functor<Maybe>
    {
        template< typename a, typename b >
        static Maybe<b> fmap(b(*function)(const a&), Maybe<a> ma)
        {
            Maybe<b> r;
            if (!ma.isNothing)
            {
                r.value = function(ma.value);
            }
            return r;
        }
    };

    template< >
    struct Applicative<Maybe>
    {
        template< typename a >
        static Maybe<a> pure(const a& val)
        {
            return mreturn(val);
        }

        template< typename a, typename b >
        static Maybe<b> ap(const Maybe<b(*)(const a&)> function, const Maybe<a>& x)
        {
            return fmap(function.value, x);
        }
    };

    template< >
    struct Monad<Maybe>
    {
        template< typename a >
        static Maybe<a> mreturn(const a& v)
        {
            Maybe<a> r;
            r.isNothing = false;
            r.value = v;
            return r;
        }

        template< typename a, typename b >
        static Maybe<b> mbind(const Maybe<a>& ma, const Maybe<b>(*function)(const a&))
        {
            if (ma.isNothing) return ma;
            else
            {
                return function(ma.value);
            }
        }
    };
}

#endif
