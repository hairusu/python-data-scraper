import requests
from bs4 import BeautifulSoup
import pandas as pd

def fetch_data():
    url = "https://quotes.toscrape.com/"
    response = requests.get(url)
    
    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')
        quotes_data = []
        
        quote_elements = soup.find_all('div', class_='quote')
        for quote in quote_elements:
            text = quote.find('span', class_='text').get_text(strip=True)
            author = quote.find('small', class_='author').get_text(strip=True)
            quotes_data.append({'Quote': text, 'Author': author})
            
        return quotes_data
    else:
        print(f"Failed to retrieve page. Status code: {response.status_code}")
        return []

def save_to_csv(data, filename="scraped_output.csv"):
    df = pd.DataFrame(data)
    df.to_csv(filename, index=False)
    print(f"Successfully saved {len(data)} records to {filename}")

if __name__ == "__main__":
    data = fetch_data()
    if data:
        save_to_csv(data)