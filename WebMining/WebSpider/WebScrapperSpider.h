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

		std::string filePath;
		const std::string webScrapperDirectory = "cd C:/Users/victo/Desktop/Proyectos/NewsCurator/WebScrapper ; ";
		const std::string spiderInit = "scrapy crawl ";

		std::map<std::string, std::string> spider_map = {
			{ "raw20MIN", "20min_spider"},
			{ "rawBBC", "bbc_spider"},
			{ "rawDIARIO", "diario_spider"},
			{ "rawCNN", "cnn_spider"},
			{ "rawNYT", "nyt_spider"},
			{ "rawGUA", "gua_spider"},
			{ "rawHUF", "huf_spider"},
			{ "rawREU", "reu_spider"},
			{ "rawWSJ", "wsj_spider"}
		};
		
};

