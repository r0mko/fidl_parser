#include <iostream>
#include <map>

#include "ast/ast.h"
#include "parser/parser.h"

using namespace std;

int main(int argc, const char *argv[])
{

    namespace x3 = boost::spirit::x3;
    using namespace std;
    
    cout << "Argument count " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }

    if (argc < 2) {
        cerr << "No input file provided!" << endl <<  "Usage: spirit_parser [fidl_file]" << endl;
        exit(1);
    }

    bool ok;
    string input = FrancaParser::readFile(argv[1], ok);
    if (!ok) {
        cerr << "Can't open input file " << argv[1] << endl << "Exiting" << endl;
        exit(1);
    }

    auto first = input.begin();
    auto last = input.end();
    
    fdepl::fdepl_full_t output1;
    try
    {
       x3::phrase_parse(first, last, fdepl::fdepl_full, fdepl::whitespace, output1);
    } catch (const std::exception& e)
    {
       std::cerr<<e.what()<<std::endl;
    }
    
    return 0;

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
