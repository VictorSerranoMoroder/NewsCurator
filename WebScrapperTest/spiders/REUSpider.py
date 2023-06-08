import os
import scrapy
from bs4 import BeautifulSoup

class ScrappySpider(scrapy.Spider):
    counter = 0
    name = "reu_spider"
    start_urls = [
        'https://www.reuters.com/world/'
    ]

    custom_settings = {
        'CLOSESPIDER_TIMEOUT': 1200,
        'CLOSESPIDER_IDLE_TIMEOUT': 60   
    }

    def parse(self, response):
        
        # Extract the whole website text using Beautiful Soup
        website_text = ""
        soup = BeautifulSoup(response.body, 'html.parser')
        for string in soup.stripped_strings:
            for char in string:
                if (char == "."):
                    website_text += '\n'
                else:
                    website_text += char
        ##website_text = soup.get_text(separator=' ')
        #website_html = response.body.decode()

        # Do something with the extracted data (e.g., save it to a file or a database)
        self.save_data(response.url, website_text)

        # Follow links to other pages if needed
        # For example, let's follow links to the next pages in a pagination
        links = response.css('a::attr(href)').getall()
        for link in links:
            if ("reuters.com/world/" in link):
                yield response.follow(link, self.parse)

    
    def save_data(self, url, website_text):
        # Implement your logic to save the data here
        # For example, save it to a file or a database

        self.counter = self.counter + 1
        save_path = 'C:/Users/victo/Desktop/Proyectos/NewsCurator/rawFolders/rawNYT'
        completeNametxt = os.path.join(save_path, "rawNYT"+str(self.counter)+".txt")
        with open(completeNametxt, 'w', encoding='utf-8') as f:
            f.write(url + '\n')
            f.write(website_text.strip() + '\n')
            f.write('\n')

        #completeNamehtml = os.path.join(save_path, "rawBBC"+str(self.counter)+".html")
        #with open(completeNamehtml, 'w', encoding='utf-8') as f:
        #    f.write(f'URL: {url}\n')
        #    f.write(f'Website HTML:\n{website_html}\n')
        #    f.write('\n')