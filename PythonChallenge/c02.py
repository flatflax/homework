from collections import Counter

with open('./metadata/c02.txt',encoding='utf-8') as f:
    original_string = f.read()

c = Counter(original_string)
result_s = [key for key in c.keys() if c[key] == 1]
print(result_s)
# ['<', 'e', 'q', 'u', 'a', 'l', 'i', 't', 'y', '>']
