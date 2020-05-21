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
#include<boost/variant/static_visitor.hpp>
#include<boost/variant/apply_visitor.hpp>

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
using boost::static_visitor;
using boost::apply_visitor;

template<typename>
struct is_vector : false_type {};

template<typename T, typename A>
struct is_vector<vector<T,A>> : true_type {};

template<typename Fusion>
ptree to_json(Fusion const &fusion);

class Visitor : public static_visitor<>{
public:
  Visitor(ptree *_json, const string &_member_name) : json(_json), member_name(_member_name) {}

  ptree *json;
  const string member_name;

  template <typename T>
  void operator()(T value) const {
    json->put(member_name, value);
  }

  template <typename T>
  void operator()(T *value) const {
    json->add_child(member_name, to_json(*value));
  }

  template <typename T>
  void operator()(vector<T> value) const {
    ptree j;

    for (auto &item : value) {
      j.push_back(make_pair("", to_json(item)));
    }

    json->add_child(member_name, j);
  }
};

template <typename Fusion>
struct JsonConverter {
  JsonConverter(const Fusion &_fusion, ptree *_json) : fusion(_fusion), json(_json) {}

  const Fusion &fusion;
  ptree *json;

  template <typename Index>
  void operator() (Index) {

    using member_type = typename value_at<Fusion, Index>::type;
    string member_name = struct_member_name<Fusion, Index::value>::call();
    auto member_value = fusion.get_map()[member_name];

    Visitor v(json, member_name);
    apply_visitor(v, member_value);
  }
};

template<typename Fusion>
ptree to_json(Fusion const &fusion) {
  typedef range_c<unsigned, 0, size<Fusion>::value > Indices;
  ptree json;

  for_each(Indices(), JsonConverter<Fusion>(fusion, &json));

  return json;
}

// template<typename Fusion>
// ptree to_json(Fusion *fusion) {
//   typedef range_c<unsigned, 0, size<Fusion>::value > Indices;
//   ptree json;

//   for_each(Indices(), JsonConverter<Fusion>(*fusion, &json));

//   return json;
// }

#endif
