#include <iostream>
#include <map>

#include "ast.h"
#include "parser.h"
#include "constants.h"

using namespace std;

//const string input =
//        "typedef Timestamp is UInt64            \n"
//        "                                       \n"
//        "enumeration LandmarkObjectType {       \n"
//        "    Sign                               \n"
//        "    Pole                               \n"
//        "    PerpendicularWall                  \n"
//        "}                                      \n"
//        "enumeration LandmarkObjectSignShape {  \n"
//        "    Triangle = 0                       \n"
//        "    Rectangle = 1                      \n"
//        "    Round = 2                          \n"
//        "    Octagon = 3                        \n"
//        "    Diamond = 4                        \n"
//        "    CrossBuck = 5                      \n"
//        "    Yield = 6                          \n"
//        "    Ellipse = 7                        \n"
//        "    Other = 8                          \n"
//        "    Unknown = 15                       \n"
//        "}                                      \n"
//        "struct Vector {                        \n"
//        "    Float x                            \n"
//        "    Float y                            \n"
//        "    Float z                            \n"
//        "}                                      \n"
//        "                                       \n"
//        "struct Foo polymorphic {               \n"
//        "    Timestamp date                     \n"
//        "    Vector direction                   \n"
//        "    Vector[] directions                \n"
//        "}                                      \n"
//        "                                       \n"
//        "typedef MyVector is Foo                \n"
//        "struct Bar extends Foo                 \n"
//        "{                                      \n"
//        "    Vector v                           \n"
//        "    UInt64 [] zahl                     \n"
//        "    LandmarkObjectSignShape shape      \n"
//        "}                                      \n";

int main()
{
    namespace x3 = boost::spirit::x3;
    using namespace std;

    auto first = input.begin();
    auto last = input.end();

    ast::FTypeCollection output;

    x3::phrase_parse(first, last, fidl::type_collection, fidl::whitespace, output);
    if (first != last) {
        cout << endl << "Parsing failed at " << (first - input.begin()) << " of " << (last - input.begin()) << endl;
        cout << endl << "Not parsed part: <=" << endl << string(first, last);
        cout << "=>" << endl;
    } else {
        cout << endl << "Parsing succeeded: got typeCollection " << output.name;
        if (!output.version) {
            cout << " without version specifier";
        } else {
            ast::FVersion ver = output.version.get();
            cout << " version " << ver.major << "." << ver.minor;
        }
    }
    cout << endl << "Known types: ";
    fidl::known_type.for_each([](string s, string ) { std::cout << s << " "; });

    cout << endl << endl << "Output size " << output.types.size() << endl;
    int i = 0;
    for(auto element : output.types) {
        cout << "element " << ++i << " = " << element;
        cout << endl;
    }


    return 0;
}
