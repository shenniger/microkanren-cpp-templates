namespace uKanren {
/* Substitutions and walking */
struct EmptySubstitionList {
  using headType = void;
  using headSubst = void;
  using tail = EmptySubstitionList;
  template <class _> struct find {
    using result = void;
  };
  template <class Needle, class _> struct walk {
    using result = Needle;
  };
};
template <class HeadType, class HeadSubst, class Tail> struct SubstitutionList {
  using headType = HeadType;
  using headSubst = HeadSubst;
  using tail = Tail;
  template <class Needle> struct find {
    using result = typename tail::template find<Needle>::result;
  };
  template <> struct find<headType> {
    using result = headSubst;
  };
  template <class Needle, class OriginalList> struct walk {
    using result = typename tail::template walk<Needle, OriginalList>::result;
  };
  template <class OriginalList> struct walk<headType, OriginalList> {
    using result =
        typename OriginalList::template walk<headSubst, OriginalList>::result;
  };
};
template <class Needle, class Haystack>
using Walk = typename Haystack::template walk<Needle, Haystack>::result;

/* State */
template <int I> class Var {
  enum { i = I };
};
template <class Substitutions, int FreshCounter> struct State {
  using substitutions = Substitutions;
  enum { freshCounter = FreshCounter };
};

/* Unify */
template <class A, class B, class S> struct UnifyMatch {
  using apply = void;
};
template <class A, class S> struct UnifyMatch<A, A, S> {
  using apply = S;
};
template <int A, class B, class S> struct UnifyMatch<Var<A>, B, S> {
  using apply = State<SubstitutionList<Var<A>, B, typename S::substitutions>,
                      S::freshCounter>;
};
template <class A, int B, class S> struct UnifyMatch<A, Var<B>, S> {
  using apply = typename UnifyMatch<Var<B>, A, S>::apply;
};
/* TODO: match pairs */
template <class A, class B, class S>
using Unify = UnifyMatch<Walk<A, typename S::substitutions>,
                         Walk<B, typename S::substitutions>, S>;

template <class A, class B> struct UnifyO {
  template <class S> using apply = typename Unify<A, B, S>::apply;
};

template <class F> struct CallFresh {
private:
  template <class S>
  using lambda = typename F::template apply<Var<S::freshCounter>>;

public:
  template <class S>
  using apply = typename lambda<S>::template apply<
      State<typename S::substitutions, S::freshCounter + 1>>;
};

struct NilStream {
  using element = void;
  using next = NilStream;
};
template <class Element, class Next> struct Stream {
  using hd = Element;
  using tl = Next;
};
template <int I> struct IntAtom {
  enum { value = I };
};
template <class T>
using CallEmptyState =
    typename T::template apply<State<EmptySubstitionList, 0>>;

template <class F>
using Run1 = typename F::template apply<Var<0>>::template apply<State<
    EmptySubstitionList, 1>>::substitutions::template find<Var<0>>::result;

} // namespace uKanren
