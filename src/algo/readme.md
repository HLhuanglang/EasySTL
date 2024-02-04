# 算法合集

参考：https://cplusplus.com/reference/algorithm/

STL中提供了七十多种算法，加上重载版本，大约有100多个不同的函数模板。因为不同的算法需要的迭代器能力不一样，下图是迭代器对应的能力。

![image-20220711235435392](https://hl1998-1255562705.cos.ap-shanghai.myqcloud.com/Img/image-20220711235435392.png)


所有的算法应该针对模板入参的迭代器类型进行检测，例如all_of算法要求InputIterator

如果检测呢？查看libstd++下的实现，采用了boost提供的CCL库来判断

https://ericniebler.com/2013/11/23/concept-checking-in-c11/