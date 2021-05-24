"""
预测波士顿房价趋势
回归问题

使用K折验证
多代后会过拟合
"""

from keras.datasets import boston_housing

# 1. 加载数据
(train_data, train_targets), (test_data, test_targets) = boston_housing.load_data()

# 2. 数据标准化
mean = train_data.mean(axis=0) 
train_data -= mean
std = train_data.std(axis=0) 
train_data /= std
test_data -= mean 
test_data /= std

# 3. 构建模型
from keras import models
from keras import layers
def build_model():
	# 因为需要将同一个模型多次实例化， 所以用一个函数来构建模型
	model = models.Sequential() 
	model.add(layers.Dense(64, activation='relu',input_shape=(train_data.shape[1],))) 
	model.add(layers.Dense(64, activation='relu'))
	model.add(layers.Dense(1))
	model.compile(optimizer='rmsprop', loss='mse', metrics=['mae']) 
	return model

# 4. 使用K折验证，来对网络进行评估
import numpy as np
k=4
num_val_samples = len(train_data) // k 
num_epochs = 500
all_mae_histories = []

for i in range(k): 
	print('processing fold #', i)
	# 准备验证数据:第 k 个 分区的数据
	val_data = train_data[ i * num_val_samples: ( i + 1 ) * num_val_samples] 
	val_targets = train_targets[ i * num_val_samples: ( i + 1 ) * num_val_samples]

	# 准备训练数据:其他所有分区的数据 
	partial_train_data = np.concatenate( 
		[train_data[:i * num_val_samples],
		train_data[(i + 1) * num_val_samples:]], 
		axis=0)
	partial_train_targets = np.concatenate( 
		[train_targets[:i * num_val_samples],
		train_targets[(i + 1) * num_val_samples:]], 
		axis=0)

# 5. 构建Keras模型(已编译) 
model = build_model() 
# 静默模式 verbose=0
history = model.fit(partial_train_data, partial_train_targets,
		validation_data=(val_data, val_targets),
		epochs=num_epochs, batch_size=1, verbose=0)

# 6. 在验证数据上评估模型
mae_history = history.history['val_mae']
all_mae_histories.append(mae_history)
average_mae_history = [np.mean([x[i] for x in all_mae_histories]) for i in range(num_epochs)]

# 7. 绘制验证分数
import matplotlib.pyplot as plt
plt.plot(range(1, len(average_mae_history) + 1), average_mae_history) 
plt.xlabel('Epochs')
plt.ylabel('Validation MAE')
plt.show()

# 8. 绘制验证分数(删除前 10 个数据点)
def smooth_curve(points, factor=0.9): 
	smoothed_points = []
	for point in points:
		if smoothed_points:
			previous = smoothed_points[-1]
			smoothed_points.append(previous * factor + point * (1 - factor))
		else: 
			smoothed_points.append(point)
	return smoothed_points

smooth_mae_history = smooth_curve(average_mae_history[10:])
plt.plot(range(1, len(smooth_mae_history) + 1), smooth_mae_history) 
plt.xlabel('Epochs')
plt.ylabel('Validation MAE')
plt.show()