#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
#include <numeric>
#include <functional>
#include <random>
#include <tuple>
#include <memory>

//print sequences.
auto print_seq = [](auto rem,auto first, auto last){
    for(std::cout<<rem; first != last; std::cout<<*first++ <<' ') {}
};

        struct DivisibleBY
{
    const int d;
    //todo to understand these sentence.
    explicit DivisibleBY(int n): d(n) {}
    bool operator()(int n) const {return n % d == 0;}
};
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
    if (std::all_of(v.cbegin(),v.cbegin(),[] (int i) {return i %2==0;}))
        {
        std::cout<<"All numbers are even.";
         }
    if (std::none_of(
            v.cbegin(),
            v.cend(),
            std::bind(std::modulus<>(),std::placeholders::_1,2)))
        {
            std::cout<<"None of them are odd\n";
        }
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

void std_findif_find_ifnot(){
    std::vector<int> v{1,3,3,10};
    int  n1 = 3, n2=5;
    auto is_even = [] (int i) {return i%2 == 0;}; //predicate form that can capture something.
    auto result1 = std::find(begin(v),end(v),n1);
    auto result2 = std::find(begin(v),end(v),n2);
    auto result3 = std::find_if(begin(v), end(v),is_even);
    (result1 != std::end(v))
        ? std::cout<<"V contains " <<n1<<'\n'
        : std::cout<<"V does not contain "<<n1<<'\n';

    (result2 != std::end(v))
        ? std::cout<<"V contains "<<n2<<'\n'
        : std::cout<<"V does not contains "<<n2<<'\n';

    (result3 != std::end(v))
        ? std::cout<< "V contains even number: "<<*result3<<'\n'
        : std::cout<< "V does not contain even numbers\n";
    if(result3 !=  std::end(v))
        std::cout<<"result3 deference "<<*result3<<" endl.";
}

void std_generate_n()
{
    std::mt19937 rng;
    std::generate_n(
            std::ostream_iterator<std::mt19937::result_type>(std::cout, " "),
                    5,
                    std::ref(rng)
            );
   std::cout<<'\n';
}
void std_mt19937_demo()
{
    // pseudo-random number generator.
    std::mt19937 mt;
    mt.seed(1289); //reinitializes the seed value of object.
    std::cout<<"random numbers generated by mt19937 are: \n";
    for (int i=5; i>0;i--) std::cout<<mt()<<' ';
}

using container = std::vector<std::string>;
void print(std::string_view comment, const container& src, const container& dst = {})
{
    auto prn = [](std::string_view name, const container& cont) {
        std::cout << name;
        for (const auto &s: cont) { std::cout << (s.empty() ? "." : s.data()) << ' '; }
        std::cout << '\n';
    };
    std::cout << comment << '\n';
    prn("src: ", src);
    if (dst.empty()) return;
    prn("dst: ", dst);
}

void std_partition()
{
    /* Reorders the elements in the range [First, last) in such a way that all elements
     * for which the predicate p return true precedes the elements for which
     * predicate p return false.
     * Relative order of the elements is not preserved.
     */
    std::array<int,10> v = {1,2,3,4,5,6,7,8,9,10};
    auto is_even = [] (int i){return i % 2;};
    std::cout.setf(std::ios_base::boolalpha);
    std::cout<<std::is_partitioned(v.begin(),v.end(),is_even)<<' ';

    //std::partition return Iterator to the first element of the second group.
    std::partition(v.begin(),v.end(),is_even);

    print_seq("After partitioning, v: ", v.cbegin(),v.cend());
    std::cout<<'\n';

    const auto pp = std::partition_point(v.cbegin(), v.cend(), is_even);
    const auto i = std::distance(v.cbegin(),pp);
    std::cout<<"Partition point is at "<<i<<"; v["<< *pp <<"]"<<'\n';
    print_seq("First partition (all even elements): ", v.cbegin(),pp);
    print_seq("; Second partition (all odd elements): ",pp, v.cend());
    std::cout<<'\n';
    std::cout<<std::is_partitioned(v.begin(),v.end(),is_even)<<'\n';
    std::reverse(v.begin(), v.end());

    std::cout<<std::is_partitioned(v.cbegin(), v.cend(), is_even)<<' ';

    std::cout<<std::is_partitioned(v.crbegin(), v.crend(),is_even)<<' ';
    std::cout<<"........std::partition_point....\n";
    for (auto i:v) std::cout<<i;
    int true_arr[5] = {0};
    int false_arr[5] = {0};
    /*
     * Copies the elements from range [first, last) to two different ranges depending
     * on the value returned by the predicate p. the element that satisfy the predicate p
     * are copied to the range beginning at d_first_true.
     */
    std::partition_copy(std::begin(v),std::end(v),
                        std::begin(true_arr),
                        std::begin(false_arr),
                        [] (int i) {return i>5;}
                        );
    std::cout<<"Partition Copy Demo, true_arr: \t";
    for (auto x:true_arr) {std::cout<<x<<' ';}

}

void std_sort()
{
    /*is_sorted: Checks if the element in range [First, last) are sorted in non-descending order.
     *
     */
    int digits[] {3,1,4,1,8};
    std::cout<<": is_sorted: "<<std::boolalpha
            <<std::is_sorted(std::begin(digits),std::end(digits))
            <<'\n';
    std::sort(std::begin(digits),std::end(digits));
    for (auto i:digits) {std::cout<<i<<' ';}
    std::cout<<"After sort function: "<<std::is_sorted(std::begin(digits),std::end(digits))<<'\n';
}

//template to print out container elements wrapped it with "{" and "}".
template<typename Os, typename V>
Os& operator<< (Os& os, V const& v) {
    os<<"{ ";
    for ( auto const& e: v ) os << e <<' ';
    return os<< "}";
}

void std_permutation()
{
    static constexpr auto v1 = {1,2,3,4,5};
    static constexpr auto v2 = {3,5,4,1,2};
    static constexpr auto v3 = {2,3,1,5,4};
    std::cout<< v2<<" is a permutation of "<<v1<<": "<<std::boolalpha
             <<std::is_permutation(v1.begin(),v1.end(),v2.begin())<<'\n'
             << v3<<"is a permutation of " <<v1<<": "<<std::boolalpha
             <<std::is_permutation(v1.begin(),v1.end(),v3.begin());
}
void unitializedCopyN()
{
    /* Copies count elements from a range beginning at first to an uninitialized memory area beginning at d_first.
     *
     */
    std::vector<std::string> v = {"This", "is","an","Example"};
    std::string *p;
    //std::size_t is the unsigned integer type of the result of size_of operator.
    std::size_t sz;
    /*
     * Reinventing the wheel, but this time with prettier spokes!
     * This function tries to obtain storage for __len adjacent Tp objects.
     * The objects themselves are not constructed, of course. A pair
     * is returned containing the buffer s address and capacity (in the units of sizeof(_Tp)),
     * or a pair of 0 values if no storage can be obtained.
     * Note that the capacity obtained may be less than that requested if the memory is unavailable;
     * you should compare len with the .second return value. Provides the nothrow exception guarantee
     */
    std::tie(p,sz) = std::get_temporary_buffer<std::string>(v.size());

    sz = std::min(sz,v.size()); // both same: 4.

    std::uninitialized_copy_n(v.begin(),sz,p);

    for (std::string* i = p; i != p+sz; ++i) {
        std::cout<<*i<<' ';
        i->~basic_string<char>();
    }
    // Deallocates storage previously allocated with std::get_temporary_buffer.
    std::return_temporary_buffer(p);

}
int main() {


    std::cout<<"line begin;\n";

//    std_permutation();
    unitializedCopyN();

//    std_sort(); //sort
//    std_partition();
    {
//        container src{"foo", "bar", "baz"};
//        container dst{"qux", "quxx", "quuz", "corge"};
//        print("Non-overlapping case: before move_backward: ", src, dst);
//        /* Moves the elements from the range [first, last), to another range ending at d_last.
//         * The last element move first, but their relative order is preserved.
//         */
//        std::move_backward(src.begin(), src.end(), dst.end());
//        print("After: ", src, dst);
//        src = {"snap", "crackle", "pop", "lock", "drop"};
//
//        std::move_backward(src.begin(), src.begin() + 3, src.end());
//        std::cout << src.size(); //move only make content null, does not reduce size.
    }

    //    std::vector<int> v{1,5,8};
//    std_allof_anyof_noneof();
//    std_copy(); //https://en.cppreference.com/w/cpp/algorithm/copy

// any_of demo.
//    if(std::any_of(v.cbegin(),v.cend(), DivisibleBY(7)))
//        std::cout<<"At least one number is divisible by 7.\n";
//    else std::cout<<"No number is divisible by 7.\n";

/* std::find, std::find_if, std::find_if_not.
 * https://en.cppreference.com/w/cpp/algorithm/find
 * */
    //todo find if, two case, return one element or return more than one element.
//    std_findif_find_ifnot();

//        std_mt19937_demo(); // https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/

    std::cout<<"\t---line ends;\n";return 0;


}
