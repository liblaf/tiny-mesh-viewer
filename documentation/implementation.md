# Implementation

Personally, I am aggressive in embracing modern technologies. I mainly adopted the C++17 standard and [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) to develop this project, and I also applied some features (`source_location`) of C++20 in debug. My code style may differ from others in several aspects, such as:

- avoiding C-style for loops
- detailed inlay hints
- extensive use of lambda expressions
- python-like `with` statement to control OpenGL state
- smart pointers instead of explicit `new`/`delete`

It is actually quite easy to understand the source code, especially with Call Graph, as long as you understand what I explained in the "Design" section. So I will not talk too much nonsense here.
