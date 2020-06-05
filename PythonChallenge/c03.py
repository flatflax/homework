import re

with open('./metadata/c03.txt',encoding='utf-8') as f:
	original_string = f.read()

test_string = original_string
result = ""

match = re.search(r'[a-z][A-Z]{3}([a-z]{1})[A-Z]{3}[a-z]', test_string)
while match:
	result = result + match.group(1)
	test_string = test_string[match.span(0)[1]:]
	match = re.search(r'[a-z][A-Z]{3}([a-z]{1})[A-Z]{3}[a-z]', test_string)
print(result)		# linkedlist