###编译代码：
```bash
$ scl enable devtoolset-2 bash
$ g++ -std=c++11 -g -ggdb -O0 -pthread -Wall -Werror -o hello_gdb hello_gdb.cpp
$ make
```
###启动GDB
```
[Administrator] >> gdb hello_gdb.exe
GNU gdb (GDB) (Cygwin 7.10.1-1) 7.10.1
Copyright (C) 2015 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-pc-cygwin".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from hello_gdb.exe...done.
(gdb)
```
> 增加、删除、启用/禁用断点  
> 运行程序  
> 查看变量  
> 修改变量  
> 单步  
> 退出  

###增加断点  
> b[reak] 函数名  
> b[reak] 文件名:行号  
> b[reak] 文件名:行号 if 条件  

> tb[reak]  
> rb[reak]  

###删除断点  
> d[elete] [N]  

###__禁用/启用断点__
> enable/disable [N]  

###运行程序  
> r[un] [paramlist]  

###单步  
> n[ext]  
> s[tep]  
> c[ontinue]  

###查看上下文代码
> l[ist]

###查看变量  
> p[rint] [exprt]

###修改变量  
> set exprt = xxxx  

###退出  
> q[uit]

注意：  
> 1 编译没有加gdb选项，不会生成调试信息到EXE文件
```gdb
(gdb) b main
Breakpoint 1 at 0x100401252
(gdb) r
Starting program: /home/Administrator/test/hello_gdb.exe
[New Thread 2084.0x2714]
[New Thread 2084.0x2934]
[New Thread 2084.0x1d48]
[New Thread 2084.0x2c60]
[New Thread 2084.0x26fc]
```


###附加到进程调试  
```bash
$ gdb -p process_id  
```

###自动化调试
```bash
$ cat gdb.txt:
b main
p argc
q
gdb -p xxxx -x gdb.txt
```

###崩溃文件调试  
```bash
$ gdb -c xxxx.core  xxxx  

bt/backtrace
f[rame] N
```

###怎么终止调试？
CTRL + C 失效后  
```bash
kill -9 gdb_process_id
```
