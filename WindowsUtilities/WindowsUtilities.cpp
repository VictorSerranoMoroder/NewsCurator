#pragma once
#include "WindowsUtilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

int WindowsUtilities::countTxtFiles(std::string directoryPath) {
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

std::vector<std::string> WindowsUtilities::loadRawFolders()
{
    std::vector<std::string> rawFolderPaths;
    std::string DIRECTORY_PATH = "C:/Users/victo/Desktop/Proyectos/NewsCurator/rawFolders/";

    std::wstring wideDirectoryPath(DIRECTORY_PATH.begin(), DIRECTORY_PATH.end());
    std::wstring searchPath = wideDirectoryPath + L"\\*";
    WIN32_FIND_DATA fileInfo;
    HANDLE searchHandle = FindFirstFile(searchPath.c_str(), &fileInfo);

    if (searchHandle != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                std::wstring wideFolderName(fileInfo.cFileName);
                std::string folderName(wideFolderName.begin(), wideFolderName.end());

                if (folderName.substr(0, 3) == "raw") {
                    std::string folderPath = DIRECTORY_PATH + folderName;
                    rawFolderPaths.push_back(folderPath);
                }
            }
        } while (FindNextFile(searchHandle, &fileInfo));

        FindClose(searchHandle);
    }
    else {
        std::cerr << "Error opening directory: " << DIRECTORY_PATH << std::endl;
    }

    return rawFolderPaths;
}