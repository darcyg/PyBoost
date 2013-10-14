#include <boost/python.hpp>

char const* greet()
{
   return "hello, world";
}

BOOST_PYTHON_MODULE(lazyass)
{
    using namespace boost::python;
    def("greet", greet);
}
