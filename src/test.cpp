// #include <iostream>
// #include <string>
// #include <vector>
// #include <type_traits>

// #include <boost/mpl/range_c.hpp>
// #include <boost/fusion/include/for_each.hpp>
// #include <boost/fusion/include/zip.hpp>
// #include <boost/fusion/include/at_c.hpp>
// #include <boost/fusion/include/adapt_struct.hpp>
// #include <boost/fusion/include/mpl.hpp>

// #include <boost/type_index.hpp>

// template<typename>
// struct is_vector : std::false_type {};

// template<typename T, typename A>
// struct is_vector<std::vector<T,A>> : std::true_type {};

// namespace fusion=boost::fusion;
// namespace mpl=boost::mpl;

// struct Foo
// {
//     int x;
//     int y;
//     std::vector<int> z;
// };

// BOOST_FUSION_ADAPT_STRUCT(Foo, x, y, z);

// struct Bar
// {
//     std::pair<int,int> p;
//     std::string s;
// };

// BOOST_FUSION_ADAPT_STRUCT(Bar, p, s);

// template <typename Sequence>
// struct Struct_member_printer
// {
//     Struct_member_printer(const Sequence& seq):seq_(seq){}
//     const Sequence& seq_;
//     template <typename Index>
//     void operator() (Index) const
//     {

//         std::string member_type = boost::typeindex::type_id<typename fusion::result_of::value_at<Sequence,Index>::type >().pretty_name() ;
//         std::string member_name = fusion::extension::struct_member_name<Sequence,Index::value>::call();
//         if (is_vector<typename fusion::result_of::value_at<Sequence,Index>::type>::value) {
//           std::cout << std::endl << std::endl << "lololol  " << member_name << std::endl << std::endl << std::endl;
//         }

//         std::cout << member_type << " " << member_name << "; ";
//     }
// };
// template<typename Sequence>
// void print_struct(Sequence const& v)
// {
//     typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Sequence>::value > Indices;
//     fusion::for_each(Indices(), Struct_member_printer<Sequence>(v));
//     std::cout << std::endl;
// }

// int main()
// {
//     Foo foo;
//     print_struct(foo);

//     Bar bar;
//     print_struct(bar);
// }
