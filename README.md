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
  * http://fmtlib.net/latest/index.html
  * https://github.com/fmtlib/fmt
    * wget https://github.com/fmtlib/fmt/archive/5.0.0.tar.gz
    * tar -zxf 5.0.0.tar.gz
    * cd fmt-5.0.0
    * mkdir build
    * cd build
    * cmake ..
    * make
    * sudo make install

## 命名规范

* 命名空间格式 motor
* 类命名格式  XxxProcessor
  * LogProcessor   日志处理器

## g++ 编译选项

* -std=c++11
* -lfmt