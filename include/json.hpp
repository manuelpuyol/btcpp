#ifndef JSON_HPP
#define JSON_HPP

#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<type_traits>

#include<boost/type_index.hpp>
#include<boost/mpl/range_c.hpp>
#include<boost/fusion/include/for_each.hpp>
#include<boost/fusion/include/zip.hpp>
#include<boost/fusion/include/at_c.hpp>
#include<boost/fusion/include/adapt_struct.hpp>
#include<boost/fusion/include/mpl.hpp>
#include<boost/property_tree/ptree.hpp>

using std::vector;
using std::false_type;
using std::true_type;
using std::string;
using std::make_pair;
using boost::mpl::range_c;
using boost::fusion::extension::struct_member_name;
using boost::fusion::result_of::value_at;
using boost::fusion::result_of::size;
using boost::fusion::for_each;
using boost::property_tree::ptree;

template<typename>
struct is_vector : false_type {};

template<typename T, typename A>
struct is_vector<vector<T,A>> : true_type {};

template<typename Fusion>
ptree to_json(Fusion const &fusion);

template <typename Fusion>
struct JsonConverter {
  JsonConverter(const Fusion &_fusion, ptree *_json) : fusion(_fusion), json(_json) {}

  const Fusion &fusion;
  ptree *json;

  template <typename Index>
  void operator() (Index) {

    string member_name = struct_member_name<Fusion, Index::value>::call();
    auto member_value = fusion.get_map()[member_name];

    if constexpr(is_vector<typename value_at<Fusion, Index>::type>::value) {
      ptree j;

      for (auto &item : member_value) {
        j.push_back(make_pair("", to_json(item)));
      }

      json->add_child(member_name, j);

      return;
    }

    json->put(member_name, member_value);
  }
};

template<typename Fusion>
ptree to_json(Fusion const &fusion) {
  typedef range_c<unsigned, 0, size<Fusion>::value > Indices;
  ptree json;

  for_each(Indices(), JsonConverter<Fusion>(fusion, &json));

  return json;
}

#endif
