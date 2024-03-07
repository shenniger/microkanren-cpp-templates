This is an implementation of microKanren that runs entirely on the C++ type/template system.
I wrote this to learn the former, and refresh my knowledge on the latter.

All microKanren code is fully executed at C++ compile time, when template types are resolved.

C++ templates have long been shown to be Turing-complete. This example demonstrates that they
can theoretically be used as a relatively complete functional language, the biggest limitation
being C++'s ban on template members in local and anonymous classes, which overcomplicates
emulating lambdas.

* Status
WIP. See `example.cpp` for a small working example that demonstrates how to use this.

* Dependencies
Clang. GCC does not work due to a bug.

* See also
- μKanren: A Minimal Functional Core for Relational Programming http://webyrd.net/scheme-2013/papers/HemannMuKanren2013.pdf
- https://minikanren.org
