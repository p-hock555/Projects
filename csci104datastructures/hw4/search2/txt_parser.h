#ifndef TXT_PARSER_H
#define TXT_PARSER_H

#include <string>
#include <set>

#include "pageparser.h"

class TXTParser : public PageParser {
public:
    /**
     * See documentation in PageParser class
     */
    void parse(std::string filename,
               std::set<std::string>& allSearchableTerms,
               std::set<std::string>& allOutgoingLinks);
    /**
     * See documentation in PageParser class
     */
    std::string display_text(std::string filename);

    //virtual crawl function
    void crawl(
        const std::map<std::string, PageParser*>& parsers,
        std::string filename,
        std::set<std::string>& processed,
        std::ostream& ofile);

private:
    // You may add additional private helpers or data members below

};

#endif
