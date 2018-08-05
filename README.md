# motor

    c/c++ web application server

## 开发环境

* VIM 7.4 && VS Code
* GCC 5.
* G++ 5.4
* Doxygen 1.8
* ubuntu16.04.03
* ddd 调试工具

## 依赖库

* fmt 5.0
  * 地址
    * http://fmtlib.net/latest/index.html & https://github.com/fmtlib/fmt
      * wget https://github.com/fmtlib/fmt/archive/5.0.0.tar.gz
      * tar -zxf 5.0.0.tar.gz
      * cd fmt-5.0.0
      * mkdir build
      * cd build
      * cmake -DBUILD_SHARED_LIBS=TRUE ..
      * make
      * sudo make install
      * sudo ldconfig 

## 命名规范

* 文件名 全小写 前缀+模块名.[h|cpp] eg: mtr_pool.h mtr_pool.cpp
* 变量名 全小写 前缀+类型+变量描述 eg: m_str_filename l_p_pool
  * 前缀
    * 类的成员变量       m_
    * 类的静态成员变量    ms_
    * 静态全局变量       s_
    * 普通全局变量       g_
    * 普通局部变量       l_
  * 类型
    * char        ch
    * char[]      sz
    * string      str
    * bool        b
    * int         n
    * long        l
    * double      d
    * float       f
    * byte        by
    * function    fn
    * pointer     p
  * 变量描述  
* 类|结构体|枚举
  * 类名 每个单词的首字大写 不包含下划线 eg: PoolBaseClass
  * 构造函数前 + explicit
  * 复制构造函数
  * 重载=

## g++ 编译选项

* -std=c++11
* -lfmt