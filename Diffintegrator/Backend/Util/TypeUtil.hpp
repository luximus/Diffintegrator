//
//  TypeUtil.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef TypeUtil_hpp
#define TypeUtil_hpp

#include <tuple>

template <int N, typename... Ts> using NthTypeOf =
    typename std::tuple_element<N, std::tuple<Ts...>>::type;

#endif /* TypeUtil_hpp */
