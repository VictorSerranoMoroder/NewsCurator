#pragma once
#include <string>
#include <vector>
#include <bsoncxx/document/value.hpp>
class DataManager
{
	public:
		static void loadDataFromRaw();
		static std::vector<std::string> loadRawFolders();

	private:
		static void readFilesInDirectory(const std::string& directoryPath);
		static void loadDocumentToDatabase(bsoncxx::document::value document);

};

