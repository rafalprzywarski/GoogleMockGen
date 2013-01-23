**Google Mock Generator** provides a reliable way of automatically generating Mock Objects for Google Mock. It is intended to be used as part of build system.

## Building

 + get [clang](http://clang.llvm.org)
 + clone the repository into llvm/tools/clang/plugins
 + build all targets using KDevelop or cmake
 + run the regression using [cucumber](http://cukes.info)

## Usage
```
gmockgen HeaderFile.hpp ClassName
```
This will output ClassNameMock.hpp

