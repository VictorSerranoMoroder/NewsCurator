#include "WebScrapperSpider.h"
#include <string>

WebScrapperSpider::WebScrapperSpider(std::string filePath)
{
	this->filePath = filePath;
}

void WebScrapperSpider::startSpider()
{
	std::string spiderOrder;
	std::string folder = filePath.substr(filePath.find_last_of('/')+1, filePath.size());
	spiderOrder += spiderInit + spider_map[folder] + " --nolog";
	
	system(spiderOrder.c_str());
}
