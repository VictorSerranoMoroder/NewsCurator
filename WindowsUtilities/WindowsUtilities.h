#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

class WindowsUtilities
{
	public:
		static std::vector<std::string> loadRawFolders();
		static int countTxtFiles(std::string directoryPath);
	private:
		

};

