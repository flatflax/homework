"""
路透社多分类
"""
from keras.datasets import reuters
from keras import models 
from keras import layers
import numpy as np
import matplotlib.pyplot as plt

# 1. 加载数据集
(train_data, train_labels), (test_data, test_labels) = reuters.load_data( num_words=10000)

# 2. 将索引解码为新闻文本
word_index = reuters.get_word_index()
reverse_word_index = dict([(value, key) for (key, value) in word_index.items()]) 
decoded_newswire = ' '.join([reverse_word_index.get(i - 3, '?') for i in train_data[0]])
# 索引减去了 3，因为 0、1、2 是为“padding”(填充)、“start of sequence”(序列开始)、“unknown”(未知词)分别保留的索引

# 3. 编码数据 - 将数据向量化
# 3.1 将标签列表转换为整数张量
def vectorize_sequences(sequences, dimension=10000): 
	results = np.zeros((len(sequences), dimension)) 
	for i, sequence in enumerate(sequences):
   		results[i, sequence] = 1
   		return results

x_train = vectorize_sequences(train_data) # 将训练数据向量化
x_test = vectorize_sequences(test_data)	# 将测试数据向量化

# 3.2 使用one-hot编码
def to_one_hot(labels, dimension=46):
	results = np.zeros((len(labels), dimension)) 
	for i, label in enumerate(labels):
		results[i, label] = 1
		return results

one_hot_train_labels = to_one_hot(train_labels) 
one_hot_test_labels = to_one_hot(test_labels)

# 4. 构建模型
model = models.Sequential()
model.add(layers.Dense(64, activation='relu', input_shape=(10000,))) 
model.add(layers.Dense(64, activation='relu')) 
model.add(layers.Dense(46, activation='softmax'))

# 编译模型
model.compile(optimizer='rmsprop', loss='categorical_crossentropy',metrics=['acc'])

# 5. 留出验证集
x_val = x_train[:1000]
partial_x_train = x_train[1000:]
y_val = one_hot_train_labels[:1000] 
partial_y_train = one_hot_train_labels[1000:]

# 6. 训练模型
history = model.fit(partial_x_train, partial_y_train,epochs=20,batch_size=512, validation_data=(x_val, y_val))

# 7. 绘制训练损失和验证损失
loss = history.history['loss'] 
val_loss = history.history['val_loss']
epochs = range(1, len(loss) + 1)
plt.plot(epochs, loss, 'bo', label='Training loss') 
plt.plot(epochs, val_loss, 'b', label='Validation loss') 
plt.title('Training and validation loss') 
plt.xlabel('Epochs')
plt.ylabel('Loss') 
plt.legend()
plt.show()


# 8.绘制训练精度和验证精度
plt.clf() # 清空图像
acc = history.history['acc']
val_acc = history.history['val_acc']
plt.plot(epochs, acc, 'bo', label='Training acc') 
plt.plot(epochs, val_acc, 'b', label='Validation acc') 
plt.title('Training and validation accuracy') 
plt.xlabel('Epochs')
plt.ylabel('Accuracy') 
plt.legend()
plt.show()

# 9. 在新数据上预测结果
prediction = model.predict(x_test)