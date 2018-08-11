# SQL Server函数记录

* 计算时间差

	DATEDIFF ( date-part, date-expression-1, date-expression-2 )

date-part : year | quarter | month | week | day | hour | minute | second | millisecond

date-expression-1 : 起始日期

date-expression-2 : 结束日期

* 转型

	CONVERT(data_type(length),data_to_be_converted,style)

data_type(length) : 目标数据类型和长度

data_to_be_converted ： 被转换的数据

style ： 输出格式

[日期输出格式](http://www.w3school.com.cn/sql/func_convert.asp)