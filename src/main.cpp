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
    
    auto first = fdepl_string.begin();
    auto last = fdepl_string.end();
    
    using boost::spirit::x3::ascii::space;
    typedef std::string::const_iterator iterator_type;
    using boost::spirit::x3::with;
    using boost::spirit::x3::error_handler_tag;
    using error_handler_type = boost::spirit::x3::error_handler<iterator_type>;
    
    // Our error handler
    error_handler_type error_handler(first, last, std::cerr);
    
    // Our parser
    auto const parser =
       // we pass our error handler to the parser so we can access
       // it later in our on_error and on_sucess handlers
       with<error_handler_tag>(std::ref(error_handler))
          [
             fdepl::fdepl_full
          ];
    
    
    ast::fdepl::fdepl_full_t output1;

    x3::phrase_parse(first, last, parser, fdepl::whitespace, output1);
    
    return 0;


}
