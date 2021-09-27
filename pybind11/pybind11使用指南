# Pybind 使用教程

## 一、使用cmake构建项目

### 1、准备工作(注意所有命令都要改为您下载的版本)

检查python版本，安装依赖，否则会报错：找不到Python.h头文件

~~~bash
sudo apt-get install python-dev
~~~

注意后面构建项目时出现bug，针对您所使用的python版本安装特定依赖：

~~~bash
python --version	#查询python版本，例如笔者是python3.7
sudo apt-get install python3.y-dev
~~~

### 2、pybind11的安装(注意所有命令都要改为您下载的版本)

Step1：到 https://github.com/pybind/pybind11 中下载Pybind11的Release版本，笔者写下此文时最新版本为2.7.1

Step2：解压到home文件夹下，执行以下命令

~~~bash
cd pybind11-2.7.1
~~~

Step3：

~~~bash
mkdir build
cd build
cmake ..
make check -j4
sudo make install
~~~

### 3、CMakeLists.txt

假设有如下的目录结构，我们想要从example.cpp中导出类：

~~~bash
.
├── build
├── CMakeLists.txt
├── lib
├── setup.py
└── src
    └── example.cpp
~~~

 a)如果已经将pybind安装到系统目录（执行过install行为）

~~~cmake
cmake_minimum_required(VERSION 3.15)		#建议cmake最低版本3.15
project(pybind_example)

set(CMAKE_CXX_STANDRAD 14)					#建议采用最低c++14要求
find_package(pybind11)						#如果已经将pybind11库安装到系统路径中
pybind11_add_module(test_pybind src/example.cpp)	#注意test_pybind要与cpp中导出的module一致

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
~~~

b)如果将pybind文件夹放置在工程文件夹下 如：

~~~
.
├── build
├── CMakeLists.txt
├── lib
├── setup.py
|—— pybind
└── src
    └── example.cpp
~~~

则可以将find_package替换掉：

~~~cmake
cmake_minimum_required(VERSION 3.15)		#建议cmake最低版本3.15
project(pybind_example)

set(CMAKE_CXX_STANDRAD 14)					#建议采用最低c++14要求
add_subdirectory(pybind11)					#如果已经将pybind11库安装到系统路径中
pybind11_add_module(test_pybind src/example.cpp)	#注意test_pybind要与cpp中导出的module一致

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
~~~

