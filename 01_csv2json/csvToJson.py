import json
'''
将以下格式csv格式化为json

csv:
cran,tran
,yarn
,,uran
,oran

树构造：
cran
-tran
-yarn
--uran
-oran

'''

def nested_dict(k,tree):
	'''
	tree[0]:list:根
	tree[1]：list:第一层
	...以此类推
	非根层元素:dict:{parent_node:父节点位置,key:节点名,value:值}
	根元素：dict:{key:节点名,value:值}
	'''
	l = k.split(',')
	for i in range(len(l)):
		if l[i]!='':
			if (i>len(tree)):
				# 不符合的数据丢弃
				break
			if (i+1>len(tree)):
				# 深度需要+1的情况
				tree.append([])
			if i>0:
				# 非根层的情况
				parent_node = len(tree[i-1])-1
				tree[i].append({'parent_node':parent_node,
									'key':l[i],
									'value':[]	})
			if i==0:
				# 根层的情况
				tree[i].append({'key':l[i],
								'value':[]		})
	return tree

def transferToJson(tree):
	'''
	倒置树，从原树的最深一层向前填充
	'''
	tree.reverse()
	tree_deep = len(tree)
	for i in range(1,tree_deep):
		for key in tree[i-1]:
			# 子节点的key-value合并到父节点
			new_key = {key['key']:key['value']}
			tree[i][key['parent_node']]['value'].append(new_key)

		# 清空子节点 可有可无
		tree[i-1] = []
	result = dict()
	for key in tree[-1]:
		key_name = key['key']
		key_value = key['value']
		result[key_name] = key_value
	return result


if __name__ == '__main__':
	tree = []
	content = []

	with open('text.csv','r',encoding='utf-8') as f:
		for index, line in enumerate(f):
			content.append(line.replace('\n',''))
		f.close

	for k in content:
		nested_dict(k,tree)

	result = transferToJson(tree)
	with open('result.json','a',encoding='utf-8') as f:
		json.dump(result,f,ensure_ascii=False) 
		f.close()