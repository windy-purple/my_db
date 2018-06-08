# -*- coding: UTF-8 -*-
import requests
from bs4 import BeautifulSoup
import os
import re


url="http://www.ivsky.com/bizhi/dongman_t3416/"
headers = {'User-Agent': 'Mozilla/5.0'}
response=requests.get(url,headers=headers)

soup=BeautifulSoup(response.content,'html.parser')
link=soup.find_all('img')

x=0

os.chdir("g://py/path")

for links in link:
	img_urls=link[x]['src']
	print img_urls
	img=requests.get(img_urls)
	with open('%d.jpg'%x,'wb') as file:
		file.write(img.content)
	file.close()
	print	("%d picture download" %x)
	x+=1
	
	
print ("download end")
	
