编译器使用VS自带的64位编译器  
note:
1. sdk里面的gtest只有64位版本, 另外cmake里面没有link pthread. 如果换别的编译器要注意这两点.
2. 如果结果不符合预期, 可以删除build文件夹重新编译试试
3. 行情数据存放在build/tests/Debug/hq.txt, 可以查看是否符合预期.
