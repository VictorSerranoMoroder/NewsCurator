
#pragma once
#include "WebMiningManager.h"

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

#include "../Data&DocumentUtilities/DataManager.h"
#include "../DatabaseConnection/DatabaseConnection.h"
#include "WebSpider/WebScrapperSpider.h"
#include "../WindowsUtilities/WindowsUtilities.h"

#include <iostream>
#include <cstdlib>
#include <windows.h>

int totalFiles = 0;

void WebMiningManager::MonitorMiningStatus(std::vector<std::string> folders, std::vector<std::thread>* threadVector)
{
    int option;
    std::atomic<bool> terminateThread = false;

    auto updateProgress = [](std::vector<std::string> folders, std::atomic<bool>* terminateThread)
    {
        int files = 0;
        int prevTotal = 0;
        do
        {
            system("cls");
            std::cout << "WebMining in Progress... Total Files: " << totalFiles + files << std::endl;
            std::cout << "Mining Rate (Pages/sec): " << totalFiles + files - prevTotal << std::endl;
            prevTotal = totalFiles + files;
            files = 0;

            for (int i = 0; i < folders.size(); i++)
            {
                int count = WindowsUtilities::countTxtFiles(folders[i]);
                std::cout << "From " + folders[i] + ": " << std::to_string(count) << std::endl;
                files += count;
            }
            Sleep(1000);

        } while (!*terminateThread);
        totalFiles += files;
    };

    std::thread thr(updateProgress, folders, &terminateThread);
    for (int i = 0; i < threadVector->size(); i++)
        threadVector->at(i).join();

    terminateThread = true;
    thr.join();
    system("pause");
}

void WebMiningManager::RunMiningThread(const std::string& folder)
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

std::vector<std::string> WebMiningManager::getFoldersToProcess(std::vector<std::string>* folders)
{
    std::vector<std::string> processFolders;

    for (int i = 0; i < TUPPLE_SIZE; i++)
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

void WebMiningManager::RunWebScrapping()
{
    std::vector<std::string> folders;
    std::vector<std::thread> threadVector;

    int option;

    system("ResetRawFolders.bat");
    folders = WindowsUtilities::loadRawFolders();
    for (int tupple = 0; folders.size() > 0; tupple++)
    {
        threadVector.clear();
        std::vector<std::string> processedFolders = getFoldersToProcess(&folders);

        for (int i = 0; i < processedFolders.size(); i++)
        {
            threadVector.emplace_back(std::thread(&WebMiningManager::RunMiningThread, this, std::ref(processedFolders[i])));
            Sleep(200);
        }
        MonitorMiningStatus(processedFolders, &threadVector);
    }
}

void WebMiningManager::ShowWebMiningMenu()
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

        if (option == 1)
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

WebMiningManager* WebMiningManager::webminingmanager_ = nullptr;

WebMiningManager* WebMiningManager::getInstance()
{
    if (webminingmanager_ == nullptr) {
        webminingmanager_ = new WebMiningManager();
    }
    return webminingmanager_;
}

WebMiningManager::WebMiningManager()
{
    return;
}