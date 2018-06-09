# motor

    c/c++ web application server

## 开发环境

* VIM 7.4 && VS Code
* GCC 5.
* G++ 5.4
* Doxygen 1.8
* ubuntu16.04.03

## 依赖库

* sqdlog: sudo apt-get install -y libspdlog-dev  (1.6-1)
  * https://github.com/gabime/spdlog [tag 0.17.0]
  * https://github.com/COMBINE-lab/spdlog
  * https://github.com/gabime/spdlog/wiki/1.-QuickStart

## 命名规范

* 命名空间格式 motor
* 类命名格式  XxxProcessor
  * LogProcessor   日志处理器

## g++ 编译选项

* -std=c++11
* -lpthread