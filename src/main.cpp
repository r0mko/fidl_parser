#include <iostream>
#include <boost/spirit/home/x3.hpp>

using namespace std;

string input = "struct Vector {\n"
               "    Float x\n"
               "    Float y\n"
               "    Float z\n"
               "};";




namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;
using x3::int_;
using x3::lit;
using x3::double_;
using x3::lexeme;
using ascii::char_;

int main()
{
    cout << input;
    auto idenfifier = x3::alpha >> *x3::alnum;
    auto type = lit("Float")
            | lit("Double")
            | lit("UInt32")
            | lit("UInt16")
            | lit("Int16")
            | lit("Int32");


            return 0;
}
