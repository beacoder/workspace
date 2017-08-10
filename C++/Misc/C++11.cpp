#include <functional>

// combine std::bind(), variadic templates, and perfect forwarding

void third_party(int n, std::function<void(int)> f)
{
  f(n);
}

struct foo
{
  template <typename... Args>
  void invoke(int n, Args&&... args)
  {
    auto bound = std::bind(&foo::invoke_impl<Args&...>, this,
                           std::placeholders::_1, std::forward<Args>(args)...);
 
    third_party(n, bound);
  }
 
  template <typename... Args>
  void invoke_impl(int, Args&&...)
  {
  }
};
 
int main()
{
    foo f;
    f.invoke(1, 2);
}


// std::bind() vs lambdas in C++14

// move and capture varaibles
auto f1 = std::bind(f, 42, _1, std::move(v));
auto f1 = [v = std::move(v)](auto arg) { f(42, arg, std::move(v)); };

// capture expressions
auto f1 = std::bind(f, 42, _1, a + b);
auto f1 = [sum = a + b](auto arg) { f(42, arg, sum); };

// perfect forwarding
auto f1 = std::bind(f, 42, std::forward<Args>(args)...);
auto f1 = [=](auto&& arg) { f(42, std::forward<decltype(arg)>(arg)); };
