"""
电影二分类
"""
from keras.datasets import imdb
import numpy as np

# 1. 加载数据
(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000)

# 2. 将索引解码为文本
word_index = imdb.get_word_index() #word_index 是一个将单词映射为整数索引的字典
reverse_word_index = dict([(value, key) for (key, value) in word_index.items()]) # 键值颠倒，将整索引映射为单词
decoded_review = ' '.join([reverse_word_index.get(i - 3, '?') for i in train_data[0]]) #将评论解码。
# 索引减去了 3，因为 0、1、2 是为“padding”(填充)、“start of sequence”(序列开始)、“unknown”(未知词)分别保留的索引

# 3. 序列化函数,将数据向量化
def vectorize_sequences(sequences, dimension=10000): 
	results = np.zeros((len(sequences), dimension)) 
	for i, sequence in enumerate(sequences):
		#创建一个形状为 (len(sequences), dimension) 的零矩阵
		results[i, sequence] = 1 # 将 results[i] 的指定索引设为 1 
	return results

x_train = vectorize_sequences(train_data) 
x_test = vectorize_sequences(test_data)

y_train = np.asarray(train_labels).astype('float32') 
y_test = np.asarray(test_labels).astype('float32')

# 4. 构建模型
from keras import models
from keras import layers
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,))) 
model.add(layers.Dense(16, activation='relu')) 
model.add(layers.Dense(1, activation='sigmoid'))

model.compile(optimizer='rmsprop',loss='binary_crossentropy', metrics=['accuracy'])

# 配置优化器
# from keras import optimizers
# model.compile(optimizer=optimizers.RMSprop(lr=0.001), loss='binary_crossentropy',metrics=['accuracy'])

# 使用自定义的损失和指标
# from keras import losses 
# from keras import metrics
# model.compile(optimizer=optimizers.RMSprop(lr=0.001), loss=losses.binary_crossentropy,metrics=[metrics.binary_accuracy])

# 5. 留出验证数据集
x_val = x_train[:10000]
partial_x_train = x_train[10000:]
y_val = y_train[:10000] 
partial_y_train = y_train[10000:]

# 6. 训练模型
history = model.fit(partial_x_train, partial_y_train,epochs=20,batch_size=512, validation_data=(x_val, y_val))