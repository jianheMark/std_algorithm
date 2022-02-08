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
#include <iomanip>
#include <execution>
#include <chrono>
#include <functional>
#include <cassert>
#include <utility>
#include <type_traits>
#include <cmath>
#include <list>
//void print_pos(const auto &rem, const auto& v) {
//    using V = std::remove_cvref<decltype(v)>;
//    constexpr bool sep { std::is_same_v<typename V::value_type, int>};
//    std::cout<<rem<<std::showpos;
//    for (const auto& e: v) std::cout<<e<<(sep ? " ": "");
//    std::cout<<'\n';
//}
auto dice(){
    static std::uniform_int_distribution<int>distr{1,6};
    static std::random_device engine;
    static std::mt19937 noise{engine()};
    return distr(noise);
}
template<class Iter>
    void merge_sort(Iter first, Iter last)
{
    if (last -first >1) {
        Iter middle = first + (last -first)/2;
        merge_sort(first, middle);
        merge_sort(middle,last);
        std::inplace_merge(first, middle,last);
    }
}
int times_10(int x) {return x * 10;}
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt i = begin; i!= end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}

template <class Container, class Size, class T>
bool consecutive_values(const Container& c, Size count,const T& v)
{
    return std::search_n(std::begin(c),std::end(c), count,v) != std::end(c);
}
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
    /*
     * Erases all the elements.
     * Note that this function only erases the elements,
     * and that if the elements themselves are pointers,
     * the pointed-to memory is not touched in any way. Managing the pointer is the user's responsibility.
     */
    to_vector.clear();
    std::copy_if(
            from_vector.begin(), from_vector.end(),
            std::back_inserter(to_vector),
            [] (int x) {return x % 3 == 0;}
            );
    for (int x:to_vector) std::cout<<x<<' ';
    std::cout<<'\n';
    to_vector.clear();
    to_vector.resize(15); //Resizes the %vector to the specified number of elements
    std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());
    std::cout<<"to_vector contains: ";
    for (auto i: to_vector) std::cout<<i<<' ';
    std::vector<int>out;
    std::cout<<"copy_n module.\n";
    std::copy_n(to_vector.begin()+4, 6,std::back_inserter(out));
    auto print = [] (const int& i) {std::cout<<i<<' ';};
    std::for_each(out.begin(), out.end(), print);




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
struct SUM{
    void operator() (int n) {sum +=n;}
    int sum{0};
};
void forEachALL()
{
    std::vector<int> numbers {3,19,42,13,49};
    auto print = [] (const int& n) {std::cout<<" "<<n;};
    std::cout<<"Before: ";
    /* for_each(_InputIterator __first, _InputIterator __last, _Function __f)
     * Applies the function object __f to each element in the range [first,last).
     * __f must not modify the order of the sequence. If __f has a return value it is ignored
     */
    std::for_each(numbers.cbegin(), numbers.cend(), print);
    std::cout<<'\n';

    std::for_each(numbers.begin(), numbers.end(),[](int& n) {n++;});
    //call SUM::operator() for each number;
    SUM s = std::for_each(numbers.begin(), numbers.end(), SUM());
    std::cout<<"after: ";
    std::for_each(numbers.cbegin(), numbers.cend(),print);
    std::cout<<'\n';
    std::cout<<"sum: "<<s.sum<<'\n';

    /* Applies the given function object f to the result of dereferencing every iterator
     * in the range[first,last), in order.
     */
    std::for_each_n(numbers.begin(), 2,[](auto& n){n++;});
    std::cout<<"After for_each_n operation: ";
    for (auto i: numbers)  std::cout<<i<<' ';
    std::cout<<'\n';
}
void std_count_ifAndCount()
{
    constexpr std::array v = {1,2,3,4,5,6,7,8,9,10};
    std::cout<<v;
    std::cout<<'\n';
    for (const int target: {3,4,5}) {
        const int num_items = std::count(v.cbegin(), v.cend(),target);
        std::cout<<"number: "<<target<<", count: "<<num_items<<'\n';
    }

    //lambda expression to count elements divisible by 4.
    int count_divBy4 =
            std::count_if(v.begin(), v.end(), [] (int i ) {return i % 4 ==0;});
    std::cout<<"Numbers divisible by four: "<<count_divBy4<<'\n';

    auto distance = [] (auto first, auto last) {
        return std::count_if(first, last,[](auto) {return true;});
    };

    static_assert(distance(v.begin(), v.end())==10);

}
void std_remove()
{
    /* Remove all elements satisfying specific criteria from range[First, last)
     * and return a past-the-end iterator for the new end range.
     */
    std::string str1 = "Text with some    spaces";
    // the white spaces are removed from the string logically.
    auto noSpaceEnd = std::remove(str1.begin(), str1.end(),' ');
    std::cout<<std::string_view(str1.begin(), noSpaceEnd)<<" size: "<<str1.size()<<'\n';
    str1.erase(noSpaceEnd,str1.end());
    //The spaces are removed from the string physically.
    std::cout<<str1<<" size: "<<str1.size()<<'\n';
    std::cout<<"test std_if\n";
    std::string str2 = "Text\n with\tsome \t   whitespaces\n\n";
    str2.erase(
            std::remove_if(
                    str2.begin(), str2.end(),
                    [] (unsigned char x) {return std::isspace(x);}),
                    str2.end()
            );
    std::cout<<str2<<'\n';
    /* std::remove_copy: copies elements from range [first,last), to another range beginning at d_first,
     * omitting the elements which satisfy specific criteria.Source and destination not overlap.
     */
    //    std::string remove_str("psql");
    std::string str3 = "#Return #Value #Optimization";
    std::cout<<"before: "<<std::quoted(str3)<<'\n';
    std::cout<<"After: \"";

    std::remove_copy(str3.begin(),
                     str3.end(),
                     std::ostream_iterator<char>(std::cout),
                     'R'
                   );
    std::cout<<"\"\n";


}
void std_replace()
{
    /* Replaces all elements satisfying specific criteria with new_value in the range [first,last),
     *  std::replace_if Replaces all elements for which predicate p returns true.
     */
    std::cout<<"std:;replace code block begins.\n";
    std::vector<int> s {5,6,7,3,1,8,9,10,2,4};
    std::replace(s.begin(), s.end(),8, 88);
    for (int a: s) {
        std::cout<< a<<" ";
    }
    std::cout<<'\n';
    std::replace_if(s.begin(), s.end(),
                    std::bind(std::less<>(), std::placeholders::_1,5),55);
    std::cout<<"now the vector s: "<<s<<'\n';
//    for (int a : s) {
//        std::cout<< a<<" ";
//    }
//    std::cout<<"std_replace code block ends.\n";
    //std::replace_copy
    std::replace_copy_if(s.begin(), s.end(),
                         std::ostream_iterator<int>(std::cout, " "),
                                 [] (int n) {return n>60;}
                                 ,99);
    std::cout<<'\n';
}
void std_unique_copy()
{
    /* Copies the elements from range [first, last), to another range beginning
     * at d_first in such a way that there are no consecutive equal elements.
     */
    std::string s1 = "The     string  with   many    spaces!";
    std::cout<<"Before: "<<s1<<'\n';
    std::string s2;
    /*
     * Elements are compared using the given binary predicate p.
     */
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
                     [] (char c1, char c2) {return c1 == ' ' && c2 == ' ';});
    std::cout<<"After: "<<s2<<'\n';
}
void std_rotate_copy()
{
    std::vector<int> src = {1,2,3,4,5};
    auto pivot = std::find(src.begin(), src.end(),3);
    std::vector<int> dest(src.size());
/*
 *
    template< class ForwardIt, class OutputIt >
    constexpr OutputIt rotate_copy( ForwardIt first, ForwardIt n_first,
                                ForwardIt last, OutputIt d_first );
 * Copies the elements from range [first, last), to
 *  another range beginning at d_first in such a way,
 *  that the element n_first becomes the first element of the new range
 *  and n_first - 1 becomes the last element.
 */
    std::rotate_copy(
            src.begin(),pivot,src.end(),dest.begin()
            );
    for (const auto &i :dest)
    {
        std::cout<<i<<' ';
    }
    std::cout<<'\n';
}

void std_heap()
{
    /* std::is_heap_until Examine the range [first, last) and find the largest range beginning at first which is max heap.
     * std::is_heap Checks if the elements in range [first, last) are a max heap.
     * std::push_heap Inserts the element at the position last-1 into the max heap defined by the range[first, last-1).
     * std::pop_heap Swap the value in the position first and the position last-1 and makes the subrange [first, last-1)
     *  into a max heap.
     *  std::sort_heap Converts the max heap [first, last) into a sorted range in ascending order.
     */
    std::vector<int> v {3,1,4,1, 6,9};
    std::cout<<"Initially, v: "<< v;
    std::cout<<'\n';
    if(!std::is_heap(v.begin(), v.end())) {
        std::cout<<"Making heap....\n";
        std::make_heap(v.begin(), v.end());
    }
    std::cout<<"After make_heap, v: ";
    std::cout<<v;
    v.push_back(2);
    v.push_back(11);
    std::cout<<"Print out v again: " << v<<'\n';
    auto heap_end = std::is_heap_until(v.begin(), v.end());
    std::cout<<"Only heap: ";
    for (auto i= v.begin(); i != heap_end; ++i) std::cout<< *i<<' ';
    std::cout<<'\n';
    std::push_heap(v.begin(), v.end());
    std::cout<<"After push heap: ";
    std::cout<<v;
    std::cout<<'\n';
    std::pop_heap(v.begin(),v.end()); //move the largest to the end.
    std::cout<<"After pop-heap, now the position is "<<v<<'\n';
    int largest = v.back();
    v.pop_back();
    std::cout<<"Heap V without the largest: "<<v<<'\n';
    std::sort_heap(v.begin(), v.end());
    std::cout<<"\n sorted: \t"<<v;
}
void std_set_operation()
{
    /*
     *
     */
    std::vector<char> v1{'a','b','c','f','h','x'};
    std::vector<char> v2{'a','b','c'};
    std::vector<char> v3 {'a','c'};
    std::vector<char> v4 {'g'};
    std::vector<char> v5 {'a','c','g'};
    for (auto i:v1) std::cout<<i<<' ';
    std::cout<<"\nIncludes: \n"<<std::boolalpha;

    for(auto i:v2) std::cout<<i<<' ';
    std::cout<<": "<<std::includes(v1.begin(), v1.end(),
                                   v2.begin(), v2.end())<<'\n';
    for (auto i:v3) std::cout<<i<<' ';
    std::cout<<": "<<std::includes(v1.begin(), v1.end(),
                                   v3.begin(), v3.end())<<'\n';
    for (auto i: v4) std::cout<<i<<' ';
    std::cout<<": "<<std::includes(v1.begin(), v1.end(),
                                   v4.begin(), v4.end())<<'\n';
    for (auto i: v5) std::cout<<i<<' ';
    std::cout<<": "<<std::includes(
            v1.begin(), v1.end(),
            v5.begin(), v5.end()
            )<<'\n';

    auto cmp_nocase = [] (char a, char b) {
        return std::tolower(a) <std::tolower(b);
    };
    std::vector<char> v6 {'A','B','C'};

    for (auto i: v6) std::cout<<i <<' ';
    /* comp. The signature of the compatison function should be equivalent to the following
     * bool comp (const Type1 &a, const Type2 &b).
    */
    std::cout<<": (case-sensitive) "
            <<std::includes(v1.begin(),v1.end(),
                            v6.begin(),v6.end(),cmp_nocase)<<'\n';

    /* std::set_difference. Copies the elements from the sorted range[first1,last1)
     * which is not found in sorted range[first2,last2) to the range beginning at d_first.
     *
     */
    std::vector<int> int_v1 {1,2,5,6,5,9};
    std::vector<int> int_v2 {2,5,7};
    std::vector<int> diff;
    std::set_difference(
            int_v1.begin(), int_v1.end(),
            int_v2.begin(), int_v2.end(),
            std::inserter(diff,diff.begin())
            );
    for (auto i: int_v1) std::cout<<i<<' ';
    std::cout<<"minus ";
    for (auto i: int_v2) std::cout<<i<<' ';
    std::cout<<"is: ";
    for (auto i: diff) std::cout<<i<<' ';
    std::cout<<'\n';
    std::vector<int> v_intersection;
    /*
     *
     */
    std::set_intersection(int_v1.begin(), int_v1.end(),
                          int_v2.begin(), int_v2.end(),
                          std::back_inserter(v_intersection));
    for(auto i:v_intersection) std::cout<<i<<' ';
    /*
     * Computes symmetric difference of two sorted range: the elements that are found
     * in either of the ranges, but not in both of them are copied to the range beginning at d_first.
     * The result range is also sorted.
     */
    std::vector<int> v_symDifference;
    std::sort(int_v1.begin(), int_v1.end());
    std::sort(int_v2.begin(), int_v2.end());

    std::set_symmetric_difference(
            int_v1.begin(), int_v1.end(),
            int_v2.begin(), int_v2.end(),
            std::back_inserter(v_symDifference)
            );
    std::cout<<"The symmetric difference is: ";
    for (auto n:v_symDifference) std::cout<<n<<' ';
    /*
     * Constructs a sorted union beginning at d_first consisting of the set
     * of elements present in one or both sorted range[first1,last1) and [first2,last2).
     */
    std::vector<int> unionDest1;
    std::set_union(int_v1.begin(),int_v1.end(),
                   int_v2.begin(), int_v2.end(),
                   std::back_inserter(unionDest1));
    std::cout<<"After union, the union elements: ";
    for (auto i: unionDest1) std::cout<<i <<' ';
    std::cout<<'\n';
}

void std_merge()
{
    /*
     * Merges two sorted ranges [first1,last1) and[first2,last2) into
     * one sorted range beginning at d_first.
     *
     */
    // fill the vectors with random numbers.
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0,9);
    std::vector<int> v1(10), v2(10);
    std::generate(v1.begin(), v1.end(),std::bind(dis,std::ref(mt)));
    std::generate(v2.begin(),v2.end(),std::bind(dis,std::ref(mt)));

    //sort
    std::sort(v1.begin(),v1.end());
    std::sort(v2.begin(),v2.end());
    // output.
    std::cout<<"V1 is: ";
    for (auto s: v1) std::cout<<s<<' ';
    std::cout<<'\n';
    std::cout<<"V1 is: ";
    for (auto s: v1) std::cout<<s<<' ';
//    std::cout<<"V2: ";
//    for (auto i: v1) std::cout<<i<<' ';
    // output v1
//    std::cout << "v1 : ";
//    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << '\n';
//
//    // output v2
//    std::cout << "v2 : ";
//    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << '\n';

    //merge
    std::vector<int> dst_Merge;
    std::merge(v1.begin(),v1.end(),
               v1.begin(),v1.end(),
               std::back_inserter(dst_Merge)
               );
    std::cout<<"\nThe merged output is: ";
    std::copy(dst_Merge.cbegin(),
              dst_Merge.cend(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout<<'\n';
    /*
     * Merges two consecutive sorted ranges [first,middle) and [middle, last)
     * into one sorted range [first,last)
     */
    std::vector<int> v_inplace_merge{8,2,-2,0,11,11,1,7,3};
    std::cout<<"Before inpalce_merge: "<<v_inplace_merge<<'\n';
    merge_sort(v_inplace_merge.begin(),v_inplace_merge.end());
    std::cout<<"aFTER INplace_merge: "<<v_inplace_merge<<'\n';

}
void std_transform()
{
    /*
     * std::transform applies the given function to a range and stores
     * the results in another range, beginning at d_first.
     */
    std::string s("Hello");
    std::transform(
            s.begin(), s.end(),
            s.begin(),
            [] (unsigned char c) -> unsigned  char {return std::toupper(c);}
            );
    std::vector<std::size_t> ordinals;
    /*
     * std::size_t is the unsigned integer type of the result of the sizeof operator.
     */
    std::transform(
            s.begin(), s.end(),
            std::back_inserter(ordinals),
            [] (unsigned char c) -> std::size_t {return c;}
            );
    std::cout<<s<<':';
    for (auto i: ordinals) {
        std::cout<<' '<<i;
    }

}

void std_fill_n()
/*
 * Assigns the given value to the first count elements in the range beginning at first. if count >0
 * Does nothing otherwise.
 */
{
    std::vector<int> s;
    for (int i=1; i<10; i++)
        {s.emplace(s.end(),i);}

    std::cout<<s;
    std::fill_n(s.begin(),2, 11);
    std::cout<<s;
    std::cout<<"Now doing rotate.";
    std::rotate(s.begin(), s.begin()+2, s.end());
    std::cout<<"\n"<<s;
}
void adjacent_find()
{

    //Searches the range [first, last) for two consecutive identical elements.
    std::vector<std::string> v1{"ws", "hi","hello","hello","he","yes"};
    auto i1 = std::adjacent_find(v1.begin(), v1.end());
    if (i1 == v1.end()) {
        std::cout<<"No matching adjacent elements\n";
    }
    else {
        std::cout<<"the first adjacent pair of equal elements at: "
                <<std::distance(v1.begin(), i1)<<'\n';
    }

    //todo std::greater comparison.
    auto i2 = std::adjacent_find(v1.begin(), v1.end(),
                                 std::greater<>());
    if (i2 == v1.end()) {std::cout<<"The entire vector is sorted in ascending order\n";}
    else {
        std::cout<<"The last element in the non-decreasing subsequence is at: "
            <<std::distance(v1.begin(), i2) <<'\n';
    }
}

void std_searchN()
{
//    std::search_n searches a range for a number of consecutive copies of an element.
    const char sequences[] = "112903890238790111";
    std::cout<<std::boolalpha;
    std::cout<<"Has 4 consecutive ones: "
            <<consecutive_values(sequences,4,'1')<<'\n';
    std::cout<<"Has 3 consecutive ones: "
            <<consecutive_values(sequences,3,'1')<<'\n';
}
void iterSwap()
{
    //swap the values of the elements the given iterators are pointing to.

     //A standard interface to a platform-specific non-deterministic random number generator (if any are available).
    //Default constructs a new std::random_device object with an implementation-defined token.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> v;
    std::generate_n(
            std::back_inserter(v),
            20,
            std::bind(dist, gen)
            );
    std::cout<<"Before sort: ";
    for(auto e : v) std::cout<<e<<" ";
    selection_sort(v.begin(),v.end());
    std::cout<<"After swap sort: \n";
    for (auto e: v) std::cout<<e<<" ";
    std::cout<<"\n";
}
void std_MATH()
{
    /*
     *
     * template< class InputIt, class T, class BinaryOperation >
            T accumulate( InputIt first, InputIt last, T init,
              BinaryOperation op );
         accumulate.      Computes the sum of the given value init and the element in the range [first, last)
     */
    std::vector<int> int_v(10);
    std::iota(int_v.begin(), int_v.end(),1);
    int sum = std::accumulate(int_v.begin(), int_v.end(),0);
    int product =  std::accumulate(int_v.begin(), int_v.end(),1,
                                   std::multiplies<int>());
    auto dash_fold = [] (std::string a, int b) {
        return std::move(a) + '-' + std::to_string(b);
    };
    std::string rs = std::accumulate(
            std::next(int_v.rbegin()),
            int_v.rend(),
            std::to_string(int_v.back()),
            dash_fold
            );
    std::cout<<"1 to 10, sum is: "<<sum
            <<" product is "<<product
            <<" dash seperated string: "<< rs<<'\n';
    //std::inner_product
    std::cout<<"inner_product\n";
    std::vector<int> int_v1(5);
    std::vector<int> int_v2{5,4,2,3,1};
    std::iota(int_v1.begin(), int_v1.end(),0);

    int inner_product1 = std::inner_product(int_v1.begin(), int_v1.end(), int_v2.begin(),0);
    std::cout<<"Inner product of a and b: " <<inner_product1<<'\n';
    int inner_product2 = std::inner_product(int_v1.begin(),int_v1.end(),int_v2.begin(),0,
                                            std::plus<>(),std::equal_to<>());

     // first check if they are equal, if they are equal then return 1. then accunmulate all the "1"
    std::cout<<"Number of pairwise matches between a and b: " <<inner_product2<<'\n';
    //Computes the differences between the second and the first of each adjacent pair
    // of elements of the range [first, last) and write them to the range beginning at d_first + 1.
    std::vector int_v3 {2,4,6,8,10,12,14,16,18,20};
    std::adjacent_difference(int_v3.begin(), int_v3.end(),int_v3.begin());
    std::cout<<int_v3<<'\n';
    std::array<int,10> a {1};
    /*Computes the differences between the second
    and the first of each adjacent pair of elements of the range [first, last)
    and writes them to the range beginning at d_first + 1
     */

    std::adjacent_difference(begin(a),std::prev(end(a)),std::next(begin(a)), std::plus<>{});
    std::vector<int> int_v4(10,2);
    //std::partial_sum: Computes the partial sums of the elements in the subranges of the range [first,last)
    //and write them to the range beginning at d_first.
    std::cout<<"Using partial_sum for int_v4: ";
    std::partial_sum(int_v4.begin(), int_v4.end(),
                    std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    std::partial_sum(
            int_v4.begin(), int_v4.end(),
            int_v4.begin(),std::multiplies<int>());
    std::cout<<"after partial_sum transformation: "<<int_v4;
    //std::reduce  	similar to std::accumulate, except out of order
    std::vector<double> v(10'000'007, 0.5);
    auto t1 = std::chrono::high_resolution_clock::now();
    double result = std::accumulate(v.begin(), v.end(),0.0);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 -t1;
    std::cout<<std::fixed<<"std::accumulate result "<<result
                        <<" took " <<ms.count()<<" ms\n";
    {
        auto t3 = std::chrono::high_resolution_clock::now();
        double result1 = std::reduce(std::execution::par, v.begin(), v.end());
        auto t4 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms1 = t4-t3;
        std::cout<<"std::reduce result "<<result1<<" took " <<ms1.count()<<" ms\n";
    }
    std::vector data {3,1,4,1,5,9,2,6};
    /*
     * Computes an exclusive prefix sum operation using binary_op, using
     * init as the init value, and write the results to the range beginning
     * at d_first. "exclusive" means that the i-th input element is not included in the i-th sum.
     */
    std::cout<<"data vector as: "<<data<<'\n';
    std::cout<<"data vector exclusive sum: ";
    std::exclusive_scan(data.begin(),
                        data.end(),
                        std::ostream_iterator<int>(std::cout, " ")
                        ,-1);
    std::cout<<"\n\n Data vector Exclusive product: ";
    std::exclusive_scan(
            data.begin(),data.end(),
            std::ostream_iterator<int>(std::cout," "),
                    1,
                    std::multiplies<int>{}
            );
    std::cout<<"\n";
    std::cout<<"10 Times exclusive sum: ";
    /*
     * template< class InputIt, class OutputIt, class T,
          class BinaryOperation, class UnaryOperation>
            OutputIt transform_exclusive_scan(
                        InputIt first, InputIt last, OutputIt d_first, T init,
                        BinaryOperation binary_op, UnaryOperation unary_op);
     * unary_op - unary FunctionObject that will be applied to each element of the input range.
     * The return type must be acceptable as input to binary_op.

     * binary_op, binary FunctionObject that will be applied in to the result of unary_op, the result of other binary
     * and init.
     */
    std::transform_exclusive_scan(
            data.begin(),
            data.end(),
            std::ostream_iterator<int>(std::cout, " "),
                    0,
                    std::plus<int>{ },
                    times_10
            );
    std::cout<<"data Vetcor with transform_inclusive_scan \n";
    std::transform_inclusive_scan(
            data.begin(),
            data.end(),
            std::ostream_iterator<int>(std::cout," "),
                    std::plus<int>{ },
                    times_10
            );

}
void std_ranges_non_modifying_sequence_operation()
{
    std::vector<int> v(10,2);
    std::partial_sum(v.cbegin(),v.cend(),v.begin());
//    std::cout<<v[2];
    std::cout<<"Amount the numbers: ";
    //Copies the element in the range, defined by [first ,last), to another range beginning at result.
    std::ranges::copy(v,std::ostream_iterator<int>(std::cout, " "));
    std::cout<<'\n';

    if (std::ranges::all_of(v.cbegin(),v.cend(),[](int i) { return i % 2 == 0;})) {
        std::cout<<"All numbers are even. \n";
    }

    if (std::ranges::none_of(v,std::bind(std::modulus<>(), std::placeholders::_1,2))) {
        std::cout<<"None of them are odd.\n";
    }

    auto DivisibleBy = [] (int d) {
        return [d] (int m) {return m % d == 0;};
    };

    if(std::ranges::any_of(v, DivisibleBy(7))) {
        std::cout<<"At least one number is divisible by 7";
    }
//--------------------------std::ranges for_each code block----------------------
    std::vector<int> nums {3,4,2,8,17,289};
    auto print = [](const auto& n) {std::cout<<' '<<n;};
    std::cout<<"Before vector nums: ";
    std::ranges::for_each(std::as_const(nums), print);
    print('\n');

    std::ranges::for_each(nums, [] (int& n) {++n;});

    //calls SUM::operator() for each number.
    auto [i,s] = std::ranges::for_each(nums.begin(), nums.end(), SUM());
    assert(i == nums.end());
    std::cout<<"Now After: the nums as: ";
    std::ranges::for_each(nums.cbegin(), nums.cend(), print);

    using pair = std::pair<int,std::string>;
    std::vector<pair> pairs {{1,"one"}, {2,"two"},{3,"three"}};
    std::cout<<"Project the pair first::first:";
    std::ranges::for_each(pairs, print, [](const pair& p) {return p.first; });
    std::cout<<"\n Project the pair second: ";
    //todo understand &pair::second. html-book-20220201/reference/en/cpp/algorithm/ranges/for_each.html
    std::ranges::for_each(pairs, print, &pair::second);
    print('\n');
//--------------------------std::ranges for_each code block end----------------------

//--------------------------std::ranges for_each_n code block----------------------
    auto printContainer = [] (std::string_view name, auto const& v) {
        std::cout<<name<<": ";
        //--n means decrement n before using it in an expression.
        //n-- means decrement n after using it in an expression.
        //An array cannot have zero size.
        //https://stackoverflow.com/questions/9722632/what-happens-if-i-define-a-0-size-array-in-c-c/9723093
        for (auto n = v.size(); const auto& e:v) {
            std::cout<<e<<(--n ? "," :"\n");
        }
    };
    std::array int_arr1 {9,1,13,94,5};
    printContainer("int_arr1", int_arr1);
//--------------------------std::ranges for_each_n code block ends----------------------
    const int int_1 = 3;
    const int int_2 = 5;
    const auto v_int1 = {11, 10, 12, 89,3};
    if (std::ranges::find(v_int1, int_1) != v_int1.end()) {
        std::cout<<"v_int1 contains: "<<int_1<<'\n';
    } else {
        std::cout<<"v_int1 does not contain: "<<int_2<<'\n';
    }
    if (std::ranges::find(v_int1, int_2) != v_int1.end()) {
        std::cout<<"v_int1 contains: "<<int_2<<'\n';
    } else {
        std::cout<<"v_int1 does not contains: "<<int_2<<'\n';
    }
//find_if return iterator to the first element satisfying the condition or iterator equal to last if no such element is found.
    auto is_evenFunc_scope =  [](int x) { return x % 2 == 0;};
    if (auto result = std::ranges::find_if(v_int1.begin(),v_int1.end(),is_evenFunc_scope);
        result != v_int1.end()) {
        std::cout<<"int_1 vector have even value like "<<*result<<'\n';
    }else {
        std::cout<<"int_1 vector don't any even int value.";
    }

    auto divide_13 = [] (int x) {return x % 13 ==0; };
    if( auto result = std::ranges::find_if(v_int1.begin(),v_int1.end(),divide_13); result != v_int1.end()){
        std::cout<<*result <<" is one of the element can be divided by 13.\n";
    }else{
        std::cout<<"NO element can be divided by 13.\n";
    }
    if (auto result = std::ranges::find_if_not(v_int1.begin(), v_int1.end(),divide_13); result != v_int1.end()){
        std::cout<<"The first element in v_int1 cannot be divided by 13 is"<<*result<<'\n';
    }else {
        std::cout<<"all element can be divided by 13.\n";
    }
//--------------------------std::ranges find_if, find_if_not code block ends----------------------
//std::ranges::rotate. Performs a left rotation on the range of elemnts.
    std::string s_16(16,' ');
    for (int k{}; k!=5;++k) {
        std::iota(s_16.begin(),s_16.end(),'A');
        std::ranges::rotate(s_16,s_16.begin()+k);
        std::cout<<"Rotate left (" <<k<<"): "<<s_16<<'\n';
    }
    std::cout<<'\n';
    for (int k {}; k!=5; ++k) {
        std::iota(s_16.begin(),s_16.end(),'A');
        std::ranges::rotate(s_16,s_16.end()-k);
        std::cout<<"Rotate right ("<<k<<"): "<<s_16<<'\n';
    }
    std::cout<<"\nInsertion sort using `rotate`, step-by-step:\n";
    s_16 = {'2','4','2','0','5','9','7','3','7','1'};

    for (auto i=s_16.begin();i!=s_16.end();++i) {
        std::cout<<"i = "<<std::ranges::distance(s_16.begin(),i)<<":";
        // Returns an iterator pointing to the first element in the range [first, last) that is greater than value
//        auto upper = ranges::upper_bound(data.begin(), data.end(), 4);
        std::ranges::rotate(std::ranges::upper_bound(s_16.begin(),i,*i),i,i+1);
        std::cout<<s_16<<'\n';
    }
    std::vector<int> ranges_from_vector(10);
    std::iota(ranges_from_vector.begin(), ranges_from_vector.end(), 0);
    std::vector<int>ranges_to_vector;
    std::ranges::copy(ranges_from_vector.begin(),
                      ranges_from_vector.end(),
                      std::back_inserter(ranges_to_vector));
    std::cout<<"to_vector contains: ";
    std::ranges::copy(ranges_to_vector,std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    std::cout<<"odd numbers in ranges_to_vector are: ";
    std::ranges::copy_if(ranges_to_vector, std::ostream_iterator<int>(std::cout," "),
            [] (int x ) {return  (x % 2) == 1;});

    const std::string_view input_string_view {"ABCDEFGH"};
    std::string out;
    std::ranges::copy_n(input_string_view.begin(),4,std::back_inserter(out));
    std::cout<<quoted(out)<<'\n';
    out = "abcdefgh";
    const auto res = std::ranges::copy_n(input_string_view.begin(),5,out.begin());
    std::cout<<out<<'\n';

    std::cout<<"*(res.in): '"<<*(res.in)<<"', distance: "
            <<std::distance(std::begin(input_string_view), res.in)<<"', distance: "
            <<std::distance(std::begin(out),res.out)<<'\n';
//------------------------------------------------------------------------------------
//todo print_pos not working as intended.
    std::string spacious_string {"The    string    with many    spaces!"};
//    print_pos("spacious_string: ", spacious_string);
    std::string hello_s("hello");
    std::ranges::transform(hello_s.begin(),hello_s.end(), hello_s.begin(),
                           [](unsigned char c)-> unsigned char {return std::toupper(c);});
    std::cout<<hello_s;
    std::vector<std::size_t> ordinals;
    std::ranges::transform(hello_s,std::back_inserter(ordinals),
                           [](unsigned char c )-> std::size_t {return c;});
    std::cout<<hello_s<<':';
    for (auto ord: ordinals) {
        std::cout<<' '<<ord;
    }
    /*
      constexpr binary_transform_result<I1, I2, O>
            transform( I1 first1, S1 last1, I2 first2, S2 last2, O result,
            F binary_op, Proj1 proj1 = {}, Proj2 proj2 = {} );

     * the binary operation binary_op is applied to pairs of elements from two range:
        one is defined by [first1, last) and the other is defined by [first2, last2)
        (after respectively peojecting with projection proj1 and proj2.
     */
    std::ranges::transform(ordinals,ordinals, ordinals.begin(),std::plus{});
    printContainer("ordinals: ", ordinals);
    std::array<int, 8> arr_int8{};
    std::ranges::generate_n(arr_int8.begin(), arr_int8.size(),dice);
    printContainer("arr_int dice: ",arr_int8);
    //todo understand n{0} mean.
    std::ranges::generate_n(arr_int8.begin(),arr_int8.size(), [n {0}] () mutable {return n++;});
    printContainer("arr_int8 iota: ",arr_int8);
    std::vector<int> int_v5;
    std::array int_arr3{1,6,6,1,6};
    int_v5.resize(int_arr1.size());
    printContainer("int_arr3", int_arr3);
    /* constexpr replace_copy_result<I, O>
      replace_copy( I first, S last, O result, const T1& old_value, const T2& new_value,
                    Proj proj = {} );
Copies the elements from the source range [first,last) to the destination
range beginning at result. replacing all elements satisfying specific criteria with new value.  */
    std::ranges::replace_copy(int_arr3,int_v5.begin(), 6,9);
    printContainer("int_v5: ",int_v5);
    std::array int_arr2{1,2,3,6,7,8,4,5};
    printContainer("int_arr2",int_arr2);
    std::ranges::replace_if(int_arr2,[](int x) {return 5<x;},5);
    printContainer("int_arr2",int_arr2);
    std::string temps2;
    /*
        constexpr unique_copy_result<I, O>
        unique_copy( I first, S last, O result, C comp = {}, Proj proj = {} );

     * comp> the binary predicate to compare the projected element.
     * Copies the elements from the source range [first,last), to the destination range
     * beginning at the result in such a way that there are no consecutive equal elemenst.
     *
     */
    std::ranges::unique_copy(
            spacious_string.begin(),spacious_string.end(),
            std::back_inserter(temps2),
            [](char c1, char c2) {return c1 == ' ' && c2 == ' ';}
            );
    std::cout<<temps2;
    const auto int_v6 = {-1,+1,+2,-2,-3,+3,-3};
    printContainer("\nint_v6",int_v6);
    std::list<int> int_l1;
    /* Two consecutive element *(i-1) and *i are considered equivalent if
     * std::invoke(comp, std::invoke(proj, *(i-1)),std::invoke(proj,*i)) == true
     * where i is an iterator in the range[first +1,last).
     */
    std::ranges::unique_copy(
            int_v6, std::back_inserter(int_l1),
            {},
            [] (int x) {return std::abs(x);}
            );
    printContainer("list int_l1: ",int_l1);









}
void print_5(int n1, int n2, int n3, int n4, int n5) {
    std::cout<<n1<<' '<<n2<<' '<<n3<<' '<<n4<<' '<<n5;
}
int return_one_int(int n1) {
    return n1;
}
struct one_v_one_func{
    void print_sum(int n1, int n2) {
        std::cout<<"print the sum of two input parameter: "<< n1 + n2<<'\n';
    }
    int data = 10;
};
void std_bind(){
    std::cout<<"1) argument reordering and passing-by-reference: ";
    int  n = 7;
    auto f1
            =  std::bind(print_5, std::placeholders::_2, 42,std::placeholders::_1, std::cref(n),n);
    n = 10;
    f1(1,2,1001);
}
int main() {
    std::cout<<"line begin;\n";

//        std_bind();
        std_ranges_non_modifying_sequence_operation();
//        std_MATH();
//        iterSwap();
//        std_searchN();
//        adjacent_find();
//        std_fill_n();
//        std_transform();
//        std_merge();
//        std_set_operation();
//        std_heap();
//        std_rotate_copy();
//        std_replace();
//    std_remove();
//    std_unique_copy(); //https://en.cppreference.com/w/cpp/algorithm/unique_copy
//    std_count_ifAndCount();
//    forEachALL();
//    std_permutation();
//    unitializedCopyN(); https://en.cppreference.com/w/cpp/memory/uninitialized_copy_n
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

    std::cout<<"\t---line ends;\n";
    return 0;
}
