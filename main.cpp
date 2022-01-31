#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <functional>
void std_allof_anyof_noneof(){
    /*
     * PREDICATE: describe a callable that returns a value testable as a bool.
     * https://en.cppreference.com/w/cpp/named_req/Predicate
     */
    std::vector<int> v(10,2);
    std::partial_sum(v.cbegin(),v.cend(),v.begin());
    std::cout<<"Amount the numbers: ";
    std::copy(v.cbegin(),v.cend(),std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
}
void std_copy(){
    std::vector<int> from_vector(10);
    std::iota(from_vector.begin(),from_vector.end(),1);
    std::vector<int> to_vector;
    std::copy(from_vector.begin(),from_vector.end(),std::back_inserter(to_vector));
    //or alternatively,
//    std::vector<int> to_vector1(from_vector.size());
//    std::copy(from_vector.begin(),from_vector.end(),to_vector.begin());
    std::cout<<"to vector contains: ";
    std::copy(
            to_vector.begin(),
            to_vector.end(),
            std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    std::cout<<"Odd numbers in to_vector are: ";
    std::copy_if(
            to_vector.begin(),
            to_vector.end(),
            std::ostream_iterator<int>(std::cout, " "),
            [](int x) {return x %2 !=0;} // lambda by-copy capture by default.
            );
    std::cout<<'\n';
    std::cout<<"to_vector contains these multiples of 3: \n";
    to_vector.clear();
    std::copy_if(
            from_vector.begin(), from_vector.end(),
            std::back_inserter(to_vector),
            [] (int x) {return x % 3 == 0;}
            );
    for (int x:to_vector) std::cout<<x<<' ';
}
int main() {
//    std_allof_anyof_noneof();
    std_copy(); //https://en.cppreference.com/w/cpp/algorithm/copy

    std::cout<<"\tOK\n";return 0;
}
