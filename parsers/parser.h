/*
 * parser.h
 * Andrew Frost
 * December 2019
 *
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "parsers/token.h"
#include "parsers/tokeniser.h"

namespace rt {

    class parser{
    public:

        Camera parseCamera();
        Scene parseScene();
        
    private:
        void nextToken();
        Token expect(/* list of expected/accepted tokens */);
        bool accept();


    };
} // namespace rt

#endif // !PARSER_H_
