# motor

    c/c++ web application server

## 开发环境

* VIM 7.4 && VS Code
* GCC 5.
* G++ 5.4
* Doxygen 1.8
* ubuntu16.04.03

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
  * 包含
    * #ifndef _MTR_USE_FMT_INCLUDE_H_
    * #define _MTR_USE_FMT_INCLUDE_H_
    * #include <fmt/core.h>
    * #include <fmt/format.h>
    * #include <fmt/posix.h>
    * #include <fmt/time.h>
    * #include <fmt/ranges.h>
    * #include <fmt/printf.h>
    * #include <fmt/ostream.h>
    * #include <fmt/format-inl.h>
    * #endif  

## 命名规范

* 命名空间格式 motor
* 类命名格式  XxxProcessor
  * LogProcessor   日志处理器

## g++ 编译选项

* -std=c++11
* -lfmt