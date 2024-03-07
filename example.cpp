#include "ukanren.hpp"
using namespace uKanren;

struct Outer {
  template <class T> using apply = UnifyO<T, IntAtom<5>>;
};
using thisShouldBeFive = Run1<Outer>;
static_assert(thisShouldBeFive::value == 5);
