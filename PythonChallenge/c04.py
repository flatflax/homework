from urllib import request
import re

url = 'http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing={}'
response = request.urlopen(url.format('12345'))
re_result = re.search(r'(\d+)$', response.read().decode('utf-8'))

count = 0
last_key = ''
response_data = ''

while re_result:
    last_key = re_result.group(1)
    new_url = url.format(last_key)
    response = request.urlopen(new_url)
    count = count + 1
    print(new_url)
    response_data = response.read().decode('utf-8')
    if 'Divide by two' in response_data:
        last_key = int(int(last_key) / 2)
        new_url = url.format(last_key)
        response = request.urlopen(new_url)
        count = count + 1
        print(new_url)
        response_data = response.read().decode('utf-8')
    re_result = re.search(r'(\d+)$', response_data)

print(response_data)        # peak.html
print(last_key)
print(count)