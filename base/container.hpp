#ifndef __container__
#define __container__

namespace base
{
    template< typename T >
    struct container
    {
        T one, two, three;

    public:
        container() : one(), two(), three(){ }
        T& get(int n);
        T  foldWithAdd();
        T  foldWithMul();
        container<T>& operator+(container<T>& other)
        {
            this->get(0) = this->get(0) + other.get(0);
            this->get(1) = this->get(1) + other.get(1);
            this->get(2) = this->get(2) + other.get(2);
            return *this;
        }

        container<T>& operator*(container<T>& other)
        {
            this->get(0) = this->get(0) * other.get(0);
            this->get(1) = this->get(1) * other.get(1);
            this->get(2) = this->get(2) * other.get(2);
            return *this;
        }

        container<T>& operator*(T n)
        {
            for(int i = 0; i<3; i++)
                this->get(i) = this->get(i) * n;
            return *this;
        }

        container<T>& operator-(container<T>& other)
        {
            for(int i = 0; i<3; i++)
                this->get(i) = this->get(i) - other.get(i);
            return *this;
        }

        container<T>& operator/(container<T>& other)
        {
            for(int i = 0; i<3; i++)
            {
                if(other.get(i) != 0) {
                    this->get(i) = this->get(i) / other.get(i);
                } else {
                    // if divided by 0, hold on.
                }
            }
            return *this;
        }

        T& operator[](int index)
        {
            return this->get(index);
        }
    };

    template< typename T >
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

    template< typename T >
    T container<T>::foldWithAdd()
    {
        return (this->get(0) + this->get(1) + this->get(2));
    }

    template< typename T >
    T container<T>::foldWithMul()
    {
        return (this->get(0) + this->get(1) + this->get(2));
    }
}
#endif
