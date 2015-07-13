#ifndef __container__
#define __container__

namespace base
{
    template<class T>
    class container
    {
        T one, two, three;

    public:
        container();
        T& get(int n);
        container<T>& operator+(container<T>&);
        container<T>& operator*(int16_t&);
    };

    template<>
    container<int16_t>::container()
    {
        this->one   = 0;
        this->two   = 0;
        this->three = 0;
    }

    template<class T>
    T& container<T>::get(int n)
    {
        switch (n)
        {
            case 0 :
                return one; break;
            case 1 :
                return two; break;
            case 2 :
                return three; break;
        }
    }

    template<class T>
    container<T>& container<T>::operator+(container<T>& other)
    {
        for(int i = 0; i<3; i++) this->get(i) = this->get(i) + other.get(i);
        return *this;
    }

    template<class T>
    container<T>& container<T>::operator(*)(int16_t& n)
    {
        for(int i = 0; i<3; i++) this->get(i) * n;
        return *this;
    }
}
#endif
