#pragma once
#include "DataManager.h"

#include "../Data&DocumentUtilities/DocumentManager.h"
#include "../DatabaseConnection/DatabaseConnection.h"
#include "../WindowsUtilities/WindowsUtilities.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

void DataManager::loadDataFromRaw()
{
    std::vector<std::string> directoryPaths = WindowsUtilities::loadRawFolders();

    for (int i = 0; i < directoryPaths.size(); i++)
    {
        readFilesInDirectory(directoryPaths[i]);
    }
    return;
}

void DataManager::readFilesInDirectory(const std::string& directoryPath) {

    std::wstring wideDirectoryPath(directoryPath.begin(), directoryPath.end());
    std::wstring searchPath = wideDirectoryPath + L"\\*.*";
    WIN32_FIND_DATA fileInfo;
    HANDLE searchHandle = FindFirstFile(searchPath.c_str(), &fileInfo);

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            if (!(fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring wideFilename(fileInfo.cFileName);
                std::string filename(wideFilename.begin(), wideFilename.end());
                std::string filePath = directoryPath + "\\" + filename;
                std::cout << "Reading file " + filePath << std::endl;

                if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".txt") {
                    std::ifstream file(filePath);
                    if (file) {
                        std::string fileContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
                        std::cout << "Loading " + filePath << std::endl;
                        DataManager::loadDocumentToDatabase(DocumentManager::CreateDocument(fileContent), "NewsCurator", "TextDump");
                        file.close();
                    }
                    else {
                        std::cerr << "Error opening file: " << filePath << std::endl;
                    }
                }
            }
        } while (FindNextFile(searchHandle, &fileInfo));

        FindClose(searchHandle);
    }
    else {
        std::cerr << "Error opening directory: " << directoryPath << std::endl;
    }

    return;
}

void DataManager::loadDocumentToDatabase(bsoncxx::document::value document, std::string databaseName, std::string collectionName)
{
    try
    {
        mongocxx::collection col = DatabaseConnection::getInstance()->getDatabase(databaseName)
            .collection(collectionName);

        if (!DocumentManager::valueDuplicatedInCollection(col, "Web_URL", std::string(document["Web_URL"].get_string().value)))
            col.insert_one(std::move(document));
        
    }
    catch (const std::exception xcp)
    {
        std::cout << xcp.what() << std::endl;
        return;
    }
}