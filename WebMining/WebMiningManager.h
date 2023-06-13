#pragma once
#include <vector>
#include <string>
#include <thread>

class WebMiningManager
{
	public:
		//Singleton Access Method
		static WebMiningManager* getInstance();
		//Operator Overloading for Singleton
		WebMiningManager(WebMiningManager& other) = delete;
		void operator=(const WebMiningManager&) = delete;


		void ShowWebMiningMenu();

	private:
		void RunWebScrapping();
		std::vector<std::string> getFoldersToProcess(std::vector<std::string>* folders);
		void RunMiningThread(const std::string& folder);
		void MonitorMiningStatus(std::vector<std::string> folders, std::vector<std::thread>* threadVector);
		static int countTxtFiles(std::string directoryPath);

		WebMiningManager();
		static WebMiningManager* webminingmanager_;

		const int TUPPLE_SIZE = 8;
		

};

