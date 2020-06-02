#ifndef JSON_HPP
#define JSON_HPP

#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<type_traits>

#include<boost/type_index.hpp>
#include<boost/mpl/range_c.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/variant/static_visitor.hpp>
#include<boost/variant/apply_visitor.hpp>

using std::vector;
using std::false_type;
using std::true_type;
using std::string;
using std::make_pair;
using boost::property_tree::ptree;
using boost::static_visitor;
using boost::apply_visitor;

template<typename>
struct is_vector : false_type {};

template<typename T, typename A>
struct is_vector<vector<T,A>> : true_type {};

template<typename T>
ptree to_json(T const &obj);

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

template<typename T>
ptree to_json(T const &obj) {
  ptree json;

  for (const auto& [key, value] : obj.get_map()) {
    Visitor v(&json, key);
    apply_visitor(v, value);
  }

  return json;
}

#endif
