#ifndef __Matrix__
#define __Matrix__

#define GETSIZE(array) (sizeof(array) / sizeof(*array))

namespace base
{
    namespace matrix
    {
        template < unsigned int Row, unsigned int Col, typename T >
        struct matrix
        {
        public:
            typedef T value_type;

            // since std::vector is absence in avr-gcc, I will use a plain
            // two-dimensional array to represent a matrix, e.g. mdata[row][col]
            matrix() : mrow(Row), mcol(Col)
            {
                mdata = new value_type*[mrow];
                for(int i = 0; i < mrow; i++)
                {
                    mdata[i] = new value_type[mcol];
                }
            }

            ~matrix()
            {
                for(int i = 0; i < mrow; i++)
                {
                    delete [] mdata[i];
                }
                delete [] mdata;
            }

            // a specific version of traverse. side-effect is everywhere!
            // traverse :: (a -> b) -> Matrix b
            template< typename UnaryFunction >
            void traverse(UnaryFunction f)
            {
                for(int i = 0; i < mrow; i++)
                {
                    for(int j = 0; j < mcol; j++)
                    {
                        f(mdata[i][j]);
                    }
                }
            }

            void fillwith(value_type* list)
            {
                auto len = GETSIZE(list);
                //static_assert((mrow * mcol) <= len, "matrix need more elements");

                unsigned int index = 0;
                traverse([&index, &list](value_type i){ i = list[index++]; });
            }

            inline value_type at(unsigned row, unsigned col)
            {
                //static_assert((row <= mrow && col <= mcol), "out of bound");
                return mdata[row][col];
            }

        private:
            unsigned int  mrow;
            unsigned int  mcol;
            value_type**  mdata;
        };

        int main()
        {
            matrix<3,3,float> m;
            float f[9] = {1,2,3,4,5,6,7,8,9};
            m.fillwith(f);
            return 0;
        }

    }
}

#endif
