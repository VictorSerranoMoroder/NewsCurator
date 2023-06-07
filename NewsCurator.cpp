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

const int TUPPLE_SIZE = 5;
int totalFiles = 0;

int countTxtFiles(std::string directoryPath) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    int count = 0;

    // Construct the search pattern
    std::string searchPattern(directoryPath.c_str());
    searchPattern += "\\*.txt";

    // Start finding files
    hFind = FindFirstFileA(searchPattern.c_str(), &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Exclude directories and subdirectories
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                count++;
        } while (FindNextFileA(hFind, &findData));
        FindClose(hFind);
    }

    return count;
}

void MonitorMiningStatus(std::vector<std::string> folders, std::vector<std::thread>* threadVector)
{
    int option;
    std::atomic<bool> terminateThread = false;

    auto updateProgress = [](std::vector<std::string> folders, std::atomic<bool>* terminateThread)
    {
        int files = 0;
        do
        {
            system("cls");
            std::cout << "WebMining in Progress... Total Files: " << totalFiles + files << std::endl;
            files = 0;
            
            for (int i = 0; i < folders.size(); i++)
            {
                int count = countTxtFiles(folders[i]);
                std::cout << "From " + folders[i] + ": " << std::to_string(count) << std::endl;
                files += count;
            }

            
        } while (!*terminateThread);
        totalFiles += files;
    };

    std::thread thr(updateProgress,folders,&terminateThread);
    for (int i = 0; i < threadVector->size(); i++)
        threadVector->at(i).join();

    terminateThread = true;
    thr.join();
    system("pause");
}

void RunMiningThread(const std::string& folder)
{
    std::cout << "Starting WebScraping Daemon for: " + folder << std::endl;

    try {
        WebScrapperSpider spider(folder);
        spider();
    }
    catch (const std::exception& xcp) {
        std::cout << xcp.what() << std::endl;
    }
}

std::vector<std::string> getFoldersToProcess(std::vector<std::string>* folders)
{
    std::vector<std::string> processFolders;

    for (int i = 0; i < TUPPLE_SIZE ; i++)
    {
        if (folders->size() > 0)
        {
            processFolders.emplace_back(folders->at(0));
            folders->erase(folders->begin());
        }
        else
        {
            break;
        }
    }

    return processFolders;
}

void RunWebScrapping()
{
    std::vector<std::string> folders;
    std::vector<std::thread> threadVector;    
    
    int option;

        system("ResetRawFolders.bat");
        folders = DataManager::loadRawFolders();
        for (int tupple = 0; folders.size() > 0 ; tupple++)
        {
            threadVector.clear();
            std::vector<std::string> processedFolders = getFoldersToProcess(&folders);

            for (int i = 0; i < processedFolders.size(); i++)
            {
                threadVector.emplace_back(std::thread(RunMiningThread, processedFolders[i]));
                Sleep(200);
            }
            MonitorMiningStatus(processedFolders, &threadVector);
        }
}

void ShowWebMiningMenu() 
{
    int option = 0;

    do
    {
        std::cout << "WebMining Module Options..." << std::endl;

        std::cout << "1. Start WebScrapping" << std::endl;
        std::cout << "2. Load RawData from WebScrapping" << std::endl;
        std::cout << "3. Clear Database" << std::endl;
        std::cout << "0. Exit Program" << std::endl;

        std::cin >> option;

        if(option == 1)
        {
            RunWebScrapping();
        }
        else if (option == 2)
        {
            DataManager::loadDataFromRaw();
        }
        else if (option == 3)
        {
            DatabaseConnection* dbCon = DatabaseConnection::getInstance();
            bsoncxx::document::value filter = bsoncxx::builder::basic::make_document();
            mongocxx::collection col = dbCon->getDatabase("NewsCurator").collection("TextDump");
            col.delete_many(filter.view());
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

