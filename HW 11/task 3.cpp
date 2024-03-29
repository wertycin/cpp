#include<iostream>

template< typename T >
struct decay {
private:
    typedef typename std::remove_reference<T>::type U;
public:
    typedef typename std::conditional<
        std::is_array<U>::value,
        typename std::remove_extent<U>::type*,
        typename std::conditional<
        std::is_function<U>::value,
        typename std::add_pointer<U>::type,
        typename std::remove_cv<U>::type
        >::type
    >::type type;
};

template <typename T>
using decay_t = typename decay<T>::type;

const int f() { return 0; }

int main()
{
    std::cout << std::boolalpha;

    const int x = 1;
    std::cout << typeid(x).name() << " is const: " << std::is_const_v<decltype(x)> << std::endl;
    std::cout << typeid(decay_t<decltype(x)>).name() << " is const: " << std::is_const_v<decay<decltype(x)>::type> << std::endl;

    std::cout << typeid(f).name() << std::endl;
    std::cout << typeid(decay_t<decltype(f)>).name() << std::endl;
}
