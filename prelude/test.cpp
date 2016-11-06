//
//  main.cpp
//  Prelude
//
//  Created by Soei Wong on 2016/10/31.
//  Copyright © 2016年 Cirno. All rights reserved.
//

#include "array.hpp"
#include "category.h"
#include "function.hpp"
#include "utility.hpp"
#include "pointer.hpp"
#include "matrix.hpp"
#include <assert.h>
#include <iostream>

int test_array()
{
    //auto print = [](double x) -> double { std::cout << x << ","; return x; };
    
    prelude::array<double, 9> foo = {1,2,3,4,5,6,7,8,9};
    prelude::array<double,9> bar { 1,1,1,1,1,1,1,1,1 };
    
    std::cout << "construction: Pass" << std::endl;
    
    assert(foo[3] == (foo + bar - bar)[3]);
    
    std::cout << "addition: Pass" << std::endl;
    
    foo = bar;
    
    std::cout << "before: foo: " << foo[8] << std::endl;
    std::cout << "before: bar: " << bar[8] << std:: endl;
    foo = prelude::move(bar);
    std::cout << "after: foo: " << foo[8] << std::endl;
    
    return 0;
}

void test_category()
{
    
}

void test_function()
{
    prelude::function<int(int)> f = [](int x) { return x + x; };
    prelude::function<int(int)> g = [](int x) { return x * x; };
    
    std::cout << f(g(5))  << std::endl;
    
    prelude::function<int(int)>  h = prelude::compose(g,f);
    
    std::cout << h(5) << std::endl;
}

#include "utility.hpp"

void test_rvalue()
{
    int x = 1;
    int y = prelude::move(x);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

void test_pointer()
{
    prelude::unique_ptr<prelude::array<int,5>> foo = new prelude::array<int,5>(1,2,3,4,5);
    prelude::unique_ptr<prelude::array<int,5>> bar;
    bar = prelude::move(foo);
    std::cout  << " " << (*bar)[2] << std::endl;
}

void test_matrix()
{
    using prelude::matrix;
    matrix<double,3,3> foo {
        1,2,3,
        4,5,6,
        7,8,9 };
    Matrix3x3<double> id {
        1,0,0,
        0,1,0,
        0,0,1 };
    
    matrix<double,4,4> four {
        3,0,2,-1,
        1,2,0,-2,
        4,0,6,-3,
        5,0,2,0 };
    

    assert(foo(1,2) == (foo + id - id)(1,2));
    std::cout << "addition: Pass" << std::endl;
    
    assert(four.determinant() == 20);
    assert(id.determinant() == 1);
    std::cout << "determinant: Pass" << std::endl;
    
    assert((foo.submatrix<2,2>(1,1) * id.submatrix<2,2>(1,1)) == (foo.submatrix<2,2>(1,1)));
    assert((foo.left_adjoint(id).submatrix<3, 3>(1, 1)) == foo);
    assert((foo.left_adjoint(id).submatrix<3, 3>(1, 4)) == id);

    
    // adjugate test
    assert(id.adjugate() == id);
    assert(four.adjugate().transpose() == four.transpose().adjugate());
    assert((four * four).adjugate() == (four.adjugate() * four.adjugate()));
    std::cout << "adjugate: Pass" << std::endl;
    
    // inverse test
    assert(id.inverse() * id == id);
    std::cout << "inverse : Pass" << std::endl;
}

int main()
{
    std::cout << "-------- array    --------" << std::endl;
    test_array();
    std::cout << "-------- category ----------" << std::endl;
    test_category();
    std::cout << "-------- function ----------" << std::endl;
    test_function();
    test_rvalue();
    std::cout << "-------- pointer --------" << std::endl;
    test_pointer();
    std::cout << "-------- matrix --------" << std::endl;
    test_matrix();
}
