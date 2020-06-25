# QT

#### Qt的对象树

setParent()绑定到对象树



#### **信号和槽**

Connect （负责信号的发送、接受和处理）

信号槽(slots)：信号的处理。发送端和接受端没有关联，通过connect连接

```cpp
[static] QMetaObject::Connection QObject::connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type = Qt::AutoConnection)
  
// signal: sender's signal func
// method: receiver's slot func
```



##### 自定义信号和槽

- 自定义信号：

signals: return void 

只有声明，没有实现。可以有参数，可以重载

- 自定义槽：

Public slot/ public/ 全局: return void

有声明也有实现。可以有参数，可以重载

- 连接和触发

```cpp
connect(sender, signal, receiver, method);			// 创建连接
disconnect(sender, signal, receiver, method);	// 断开连接
emit func();		// 触发函数
```

- 出现重载

调用connect时，使用函数指针，指定调用的函数地址

- QDebug 输出char*

```cpp
QString::toUtf8();	//  —> return QByteArray
QByteArray.data();	// —> get char*

Qstring str = new QString(tr("&test"));
qDebug() << str.toUtf8().data();
```

- 函数指针

```cpp
typedef int (*fun_ptr)(int,int); // 声明一个指向同样参数、返回值的函数指针类型
```



#### QMainWindow

包含菜单栏menu bar、工具栏tool bar、锚接部件dock widgets、状态栏status bar和中心部件central widget



##### 模态对话框和非模态对话框

模态：不可对其他窗口进行操作；```dialog.exec();```

非模态：可以对其他窗口进行操作 ```dialog.show();```

##### 组件

###### QMessageBox 静态成员函数

利用返回值判断用户行为

###### QTreeLable 树便签

```cpp
QTreeWidget treeWidget = new QTreeWidget(this);

// 设置头
QString hLabel = new QString("header");
treeWidget.setHeaderLabel(hLabel);

// 插入顶标签item
QTreeWidgetItem item = new QTreeWidgetItem();
treeWidget.insertTopLevelItem(item);

// 添加child
QTreeWidgetItem itemChild = new QTreeWidgetItem();
item.addChild(itemChild);
```

###### QTableWidge 表控件

```cpp
SetColumnCount(); 	// 设置列数
setHorizontalHeaderLabels(); 	//设置水平表头
setRowCount(); 	// 设置行数
setItem(col, row, (QTableWidgeItem)item);
```



**事件**

###### 鼠标事件```QMouseEvent```

传入到`QWidget`类的鼠标相关方法（如```QMenu::mousePressEvent```等）



###### 定时器 `QTimerEvent`

1. `startTimer(500)  timeEvent(QTimeTvent * ev);` 根据`ev->timerId()`区分定时器事件

2. `Qtimer * timer = new Qtimer(this); `

3. 1. `timer->start(500); connect(timer, &Qtimer::timeout, [](){});`
   2. `Timer->stop();`



###### event分发器

通过分发器把事件发送给不同的事件处理函数

如果想要在分发器阶段进行拦截，可以使用子类函数重写`event(QEvent * e)`, 通过判断e的类型进行处理，其他时间可以通过返回父类同名函数解决 `return QLabel::event(e);`



###### 事件过滤器

在分发器阶段前对事件进行过滤,对组件安装事件过滤器，然后重写`bool eventFilter(QObject *, QEvent *)`事件，判断`QObjet`和`QEvent`类型，进行相关处理，其余`return QWidget::eventFilter();`

```cpp
// SmallLabel.cpp
SmallLabel::SmallLabel(QWidget * parent):QWidget(parent),...{
	ui->label->installEventFilter(this);...}

bool SmallLabel::eventFilter(QObject * o, QEvent * e){
  if(o == ui->label && e->type() == QEvent::MouseButtonPress)
  {
    ...
      return true;
  }
  else{ return QWidget::eventFilter(o, e);}
}
```

###### `QPainter`绘图事件

可以使用`QPen`指定线的颜色和风格，`QBrush`制定填充风格

```cpp
// TestWidget.cpp
// 重写paintEvent
void TestWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);	//指定绘图设备QPainterDevice = this;
  painter.setRenderHint();	// 抗锯齿
  painter.drawLine(QPoint(0,0), QPoint(100,100));
  painter.drawPixmap(x,y,QPixmap(path));
  ...
}

// 手动调用绘图事件
Widget::update();
```

##### 文件读写

###### `QFile`文件读写

```cpp
QString path = QDialog::getOpenFileName(this, tip_text, path);
ui->lineEdit->setText(path);

// read
// QFile default encode type: utf-8
QTextCodec * codec = QTextCodec::codecForName('gbk');
QFile file(path);
file.open(QIODevice::ReadOnly);

QByteArray array = file.readAll();
ui->textEdit->setText(array);
file.close();

//write
file.open(QIODevice::Append);
file.write(str);
file.close;
```

###### `QFileInfo`文件信息类

存储包括修改日期，大小，后缀名等信息。

