#include <iostream>
#include <map>
#include "ast/ast.h"
#include "parser/parser.h"
#include "constants.h"

using namespace std;

int main(int argc, const char *argv[])
{

    namespace x3 = boost::spirit::x3;
    using namespace std;

    if (argc < 2) {
        cerr << "No input file provided!" << endl <<  "Usage: spirit_parser [fdepl_file]" << endl;
        exit(1);
    }

    ast::FModel output;
    bool ok = FrancaParser::parse(argv[1], output);

    int i = 0;
    if (true == ok)
    {
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
    franca::known_type_parser::i().for_each([](string s, string ) { std::cout << s << " "; });
    std::cout<<std::endl;

    return 0;
}
