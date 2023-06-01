#pragma once
#include <string>
#include <vector>
#include <map>
class WebScrapperSpider
{
	public:
		void operator()() {
			startSpider();
		}

		WebScrapperSpider(std::string filePath);

	private:
		void startSpider();


		const std::string webScrapperDirectory = "cd C:/Users/victo/Desktop/Proyectos/NewsCurator/WebScrapper ; ";
		const std::string spiderInit = "scrapy crawl ";
		std::string filePath;
		std::map<std::string, std::string> spider_map = {
			{ "raw20MIN", "20min_spider"},
			{ "rawBBC", "bbc_spider"},
			{ "rawDIARIO", "diario_spider"}
		};
		
};

