// NewsCurator.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once


#include <cstdint>
#include <iostream>
#include <vector>
#include <thread>


#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <vector>

#include "DatabaseConnection/DatabaseConnection.h"
#include "Data&DocumentUtilities/DocumentManager.h"
#include "Data&DocumentUtilities/DataManager.h"
#include "WebSpider/WebScrapperSpider.h"
#include "WebMiningManager.h"

#include <iostream>
#include <cstdlib>
#include <windows.h>

int main()
{
    try
    {
        WebMiningManager* webMiningManager = WebMiningManager::getInstance();
        webMiningManager->ShowWebMiningMenu();
    }
    catch (const std::exception& xcp) {
        std::cout << xcp.what() << std::endl;
    }
    return 0;
}

