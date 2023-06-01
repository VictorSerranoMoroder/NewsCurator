#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "DocumentManager.h"


bsoncxx::document::value DocumentManager::CreateDocument(std::string input)
{
    std::string url = input.substr(0, input.find_first_of('\n'));
    std::string txt = input.substr(input.find_first_of('\n')+1, input.length());

    bsoncxx::document::value docValue = make_document(
        kvp("Web_URL_text", url),
        kvp("Web_Text", txt)
    );
    
    return docValue;
}