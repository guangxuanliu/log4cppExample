# log4cppExample


### Eclipse 添加C++11支持

```
步骤：
1. 选择要修改的项目 -> 右键 -> Properties
2. C/C++ Build -> Settings -> Tool Settings -> GCC C++ Compiler -> Miscellaneous -> Other Flags -> 尾部添加编译参数 -std=c++11 -> Apply

3. C/C++ General -> Paths and Symbols -> Symbols -> GNU C++ -> 添加 Name为 __GXX_EXPERIMENTAL_CXX0X__ ，Value为空的项 -> Apply -> OK
```

### 添加动态库

```
log4cpp
pthread
```

