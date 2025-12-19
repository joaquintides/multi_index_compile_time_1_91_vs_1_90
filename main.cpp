/* Dummy program to measure Boost.MultiIndex compile times.
 *
 * Copyright 2025 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ranked_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>

using namespace boost::multi_index;

struct element
{
  int x, y, z;
};

using container = multi_index_container<
  element,
  indexed_by<
    hashed_unique<tag<struct i0>, key<&element::x>>,
    random_access<tag<struct i1>>,
    ranked_unique<tag<struct i2>, key<&element::y>>,
    sequenced<tag<struct i3>>,
    ordered_unique<tag<struct i4>, key<&element::x, &element::y, &element::z>>
  >
>;

int main()
{
  container c;
  c.get<i0>().insert({0, 0, 0});
  c.get<i1>().push_back({1, 1, 1});
  c.get<i2>().insert({2, 2, 2});
  c.get<i3>().push_back({3, 3, 3});
  c.get<i4>().insert({4, 4, 4});

  int res = 0;
  for(auto it = c.get<i0>().find(0); it != c.get<i0>().end(); ++it) {
    res += it->x;
  }
  for(auto it = c.get<i1>().begin(); it != c.get<i1>().end(); ++it) {
    res += it->x;
  }
  for(auto it = c.get<i2>().find(2); it != c.get<i2>().end(); ++it) {
    res += it->y;
  }
  for(auto it = c.get<i3>().begin(); it != c.get<i3>().end(); ++it) {
    res += it->y;
  }
  for(auto it = c.get<i4>().find(4); it != c.get<i4>().end(); ++it) {
    res += it->z;
  }

  return res;
}
