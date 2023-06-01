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

#include <iostream>
#include <cstdlib>
#include <windows.h>

void ShowWebMiningMenu() 
{
    int option = 0;
    std::vector<std::string> folders;
    std::vector<std::thread> threadVector;
    do
    {
        std::cout << "WebMining Module Options..." << std::endl;

        std::cout << "1. Start WebScrapping" << std::endl;
        std::cout << "2. Load RawData from WebScrapping" << std::endl;
        std::cout << "3. Erase Raw Folder Contents" << std::endl;
        std::cout << "0. Exit Program" << std::endl;

        std::cin >> option;

        if(option == 1)
        {
            folders = DataManager::loadRawFolders();
            for (int i = 0; i < folders.size(); i++)
            {
                std::cout << "Starting WebScraping Daemons..." << std::endl;
                std::string folder = folders[i];
                try {
                    WebScrapperSpider spider(folder);
                    std::thread thread(spider);
                    thread.detach();
                    Sleep(3000);
                }
                catch (const std::exception& xcp) {
                    std::cout << xcp.what() << std::endl;
                }
            }  
        }
        else if (option == 2)
        {
            DataManager::loadDataFromRaw();
        }
        else if (option == 3)
        {
            system("ResetRawFolders.bat");
        }


        system("cls");

    } while (option);


    return;
}

int main()
{
    try
    {
        ShowWebMiningMenu();
        
    }
    catch (const std::exception& xcp) {
        std::cout << xcp.what() << std::endl;
    }
    return 0;
}

