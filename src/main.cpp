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
    
    auto begin = fdepl_string.begin();
    auto end = fdepl_string.end();
    
    fdepl::fdepl_define_type output1;
    x3::phrase_parse(begin, end, fdepl::fdepl_define, fdepl::whitespace, output1);
    return 0;

    auto first = input.begin();
    auto last = input.end();

    ast::FModel output;

    int i = 0;
    x3::phrase_parse(first, last, fidl::fmodel, fidl::whitespace, output);
    if (first != last) {
        cout << endl << "Parsing failed at " << (first - input.begin()) << " of " << (last - input.begin()) << endl;
        cout << endl << "Not parsed part: <=" << endl << string(first, last);
        cout << "=>" << endl;
    } else {
        cout << endl << "Successfully parsed fidl package " << output.getPackageName() << ", got " << output.typeCollections.size() << " typecollection";
        if (output.typeCollections.size() > 1) {
            cout << "s";
        }
        cout << endl;
        for (const ast::FTypeCollection &tc : output.typeCollections) {
            cout << "TypeCollection " << tc.name;
            if (!tc.version) {
                cout << " without version specifier";
            } else {
                ast::FVersion ver = tc.version.get();
                cout << " version " << ver.major << "." << ver.minor;
            }
            cout << endl << endl << "Element count: " << tc.types.size() << endl;

            for(const auto &element : tc.types) {
                cout << "Element " << ++i << ": " << element;
                cout << endl;
            }
        }
    }
    cout << endl << "Known types: ";
    fidl::known_type.for_each([](string s, string ) { std::cout << s << " "; });

    return 0;
}
