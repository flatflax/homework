"""
通过embedding层 学习标记嵌入
"""
from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras import preprocessing
from tensorflow.keras.layers import Flatten, Dense, Embedding

# 特征单词数
max_features = 10000
# 截断文本间距
maxlen = 20

# 将数据加载为整数列表
(x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=max_features)

# 将整数列表转换成形状为(samples,maxlen) 的二维整数张量
x_train = preprocessing.sequence.pad_sequences(x_train, maxlen=maxlen)
x_test = preprocessing.sequence.pad_sequences(x_test, maxlen=maxlen)


model = Sequential()
# 指定 Embedding 层的最大输入长度，以便后面将嵌入输入展平。Embedding 层激活的形状为 (samples, maxlen, 8)
model.add(Embedding(10000, 8, input_length=maxlen))
# 将三维的嵌入张量展平成形状为 (samples, maxlen * 8) 的二维张量
model.add(Flatten())
# 在上面添加分类器
model.add(Dense(1, activation='sigmoid'))
model.compile(optimizer='rmsprop', loss='binary_crossentropy', metrics=['acc'])
model.summary()


history = model.fit(x_train, y_train,
	epochs=10,
	batch_size=32,
	validation_split=0.2)