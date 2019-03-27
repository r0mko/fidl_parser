#include <iostream>
#include <map>

#include "ast/ast.h"
#include "parser/parser.h"
#include "constants.h"

using namespace std;

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
    for(const auto &element : output.types) {
        cout << "element " << ++i << " = " << element;
        cout << endl;
    }

    return 0;
}
