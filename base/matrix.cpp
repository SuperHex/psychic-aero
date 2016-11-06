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
            const unsigned rowSize = Row;
            const unsigned colSize = Col;

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

            void fillWithList(const value_type* list)
            {
                unsigned index = 0;
                traverse(
                    [&](value_type i)
                    {
                        i = list[index++];
                    }
                );
            }

            void fillWith(const value_type v)
            {
                traverse(
                    [=](value_type i)
                    {
                        i = v;
                    }
                );
            }

            template < unsigned row, unsigned col >
            inline value_type at()
            {
                return mdata[row][col];
            }

            template < unsigned row, unsigned col >
            inline void set(const value_type v)
            {
                mdata[row][col] = v;
            }

            template < unsigned R, unsigned C >
            auto operator * (const matrix<R,C,value_type>& m)
                -> decltype(matrix<Row,C,value_type>())
            {
                matrix<mrow, m.colSize(), value_type> ret = new matrix();
                for(int index = 0; index < mrow; index++)
                {
                    for(int i = 0; i < m.colSize(); i++)
                    {
                        auto reminder = 0;
                        for(int j = 0; j < mcol; j++)
                        {
                            reminder += mdata[i][j] * m.at<j,i>();
                        }
                        ret[index][i] = reminder;
                    }
                }
            }

        private:
            unsigned int  mrow;
            unsigned int  mcol;
            value_type** mdata;
        };
    }
}

// just for test.
int main()
{
    using namespace base::matrix;
    matrix<3,3,float> m;
    float f[9] = {1,2,3,4,5,6,7,8,9};
    m.fillWithList(f);
    m.set<2,2>(3);
    int d = m.at<2,3>();
    return 0;
}

#endif
