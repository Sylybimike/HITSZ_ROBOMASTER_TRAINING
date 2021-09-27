# CMake使用笔记

## 一、创建库

### 1、生成库

~~~cmake
ADD_LIBRARY(name SHARED|STATIC|... 源文件)
~~~

1）会生成libname.so/libname.a这样的文件

2）SHARED:生成动态链接库 后缀.so

3）STATIC:生成静态库 后缀.a

### 2、设置库

~~~cmake
SET_TARGET_PROPERTIES(target PROPERTIES 参数)
~~~

1）target：add_library语句中的name可以作为target

2）常用参数：OUTPUT_NAME 可以指定生成的库的名字

VERSION SOVERSION

## 二、使用库

### 1、添加头文件路径

~~~cmake
INCLUDE_DIRECTORIES(路径)
~~~

可以通过设置CMAKE_INCLUDE_PATH来改变搜索目录，配合FIND_PATH使用

~~~bash
export CMAKE_INCLUDE_PATH=...	
~~~

然后在CMakeLists.txt中使用

~~~cmake
FIND_PATH(储存路径的变量 要查找的头文件)
INCLUDE_DIRECTORIES(${储存路径的变量})
~~~

### 2、将动态库连接到目标文件

~~~cmake
TARGET_LINK_LIBRARIES(共享库/OBJ库/target 共享库)
~~~

其中第一个变量可以是由ADD_LIBRARY创建的OBJECT类型库

## 三、包含子工程

~~~cmake
ADD_SUBDIRECTORIES(..)
~~~

将子目录包含到工程中
