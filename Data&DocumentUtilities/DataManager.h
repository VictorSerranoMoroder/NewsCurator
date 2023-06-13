#pragma once
#include <string>
#include <vector>
#include <bsoncxx/document/value.hpp>
class DataManager
{
	public:
		static void loadDataFromRaw();

	private:
		static void readFilesInDirectory(const std::string& directoryPath);
		static void loadDocumentToDatabase(bsoncxx::document::value document);

};

