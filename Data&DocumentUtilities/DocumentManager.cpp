#pragma once
#include "DocumentManager.h"

#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>




bsoncxx::document::value DocumentManager::CreateDocument(std::string input)
{
    std::string url = input.substr(0, input.find_first_of('\n'));
    std::string txt = input.substr(input.find_first_of('\n')+1, input.length());

    bsoncxx::document::value docValue = make_document(
        kvp("Web_URL", url),
        kvp("Web_Text", txt)
    );
    
    return docValue;
}