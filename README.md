# num_sort
	author  chamlion 
	mail    chamlionchina@gmail.com
	看了陈硕老师在知乎上的一篇回答，why dont i give it a try!
	要求如下:
	一、多机数据处理。有 10 台机器，每台机器上保存着 10 亿个 64-bit 整数（不一定刚好 10 亿个，可能有上下几千万的浮动），一共约100亿个整数（其实一共也就 80GB 数据，不算大，选这个量级是考虑了 VPS 虚拟机的容量，便于实验）。编程求出：
	1. 这些数的平均数。
	2. 这些数的中位数。
	3. 出现次数最多的 100 万个数。
	*4. （附加题）对这 100 亿个整数排序，结果顺序存放到这 10 台机器上。
	*5. （附加健壮性要求）你的程序应该能正确应对输入数据的各种分布（均匀、正态、Zipf）。
	*6. （附加伸缩性要求）你的程序应该能平滑扩展到更多的机器，支持更大的数据量。比如 20 台机器、一共 200 亿个整数，或者 50台机器、一共 500 亿个整数。
	作者：陈硕
	链接：http://www.zhihu.com/question/22608820/answer/21968467
	来源：知乎
	著作权归作者所有，转载请联系作者获得授权
``` c++
文件结构 ：
|
|-----build.sh 
|-----CmakeLists.txt
|-----README.md
|-----num_base
|      |-----CmakeLists.txt
|      |-----bolcking_task_queue.h      实现无锁队列
|      |-----fucntions{.cc,.h}          包含得到当前文件路径、得到某个文件夹所有文件名、程序运行时间计时、noncopyable类 
|      |-----num_sort{.cc,.h}           单个文件排序
|      |-----success_tree{.cc,.h}       将排序好的文件中的数据进行多路归并排序
|      |-----thread_poll{.cc,.h}        线程池 可用在对多个单文件的排序
|     
|-----src
|      |-----CmakeLists.txt
|      |-----bolcking_task_queue_test.cc   
|      |-----num_sort_test.cc
|      |-----success_tree_test.cc
|      |-----thread_poll_test.cc
``` 
	使用方法       在build.sh 目录下 执行 sudo ./build.sh  则会生成相应的静态库 及测试文件	
	静态库的使用   比如欲使用functions.h 则应包含头文件<num/base/functions.h>

