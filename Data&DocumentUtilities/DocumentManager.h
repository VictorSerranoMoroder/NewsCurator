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

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class DocumentManager
{
    public:
        static bsoncxx::document::value CreateDocument(std::string input); 
        static bool valueDuplicatedInCollection(mongocxx::collection coll, std::string nameField, std::string fieldValue);
};

