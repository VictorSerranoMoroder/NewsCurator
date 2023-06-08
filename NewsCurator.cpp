// NewsCurator.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <thread>

#include "WebMining/WebMiningManager.h"



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

