## Homework
Представьте, что вы стажер в компании "Formatter Inc.".

# Задание 1
Вам поручили перейти на систему автоматизированной сборки CMake. Исходные файлы находятся в директории formatter_lib. В этой директории находятся файлы для статической библиотеки formatter. Создайте CMakeList.txt в директории formatter_lib, с помощью которого можно будет собирать статическую библиотеку formatter.
```
$ cmake --version
```
```
cmake version 3.29.2

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```
```
$ cd ./formatter_lib/
$ cat >> CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.29.2)
project(formatter)
EOF
$ cat >> CMakeLists.txt <<EOF
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)
EOF
$ cat >> CMakeLists.txt <<EOF
add_library(formatter STATIC \${CMAKE_CURRENT_SOURCE_DIR}/formatter.cpp)
EOF
$ cat >> CMakeLists.txt <<EOF
include_directories(\${CMAKE_CURRENT_SOURCE_DIR})
EOF
$ cmake -H. -B_build
```
# Вывод:
```
-- The C compiler identification is AppleClang 15.0.0.15000100
-- The CXX compiler identification is AppleClang 15.0.0.15000100
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/main/TiilS/workspace/projects/lab03/formatter_lib/_build
```
# Создание файлов formatter.o, libformatter.a:
```
$  g++ -c formatter.cpp -o formatter.o
$  ar rcs libformatter.a formatter.o
```
# Содержимое CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.29.2)

project(formatter_lib)
set(SOURCE_LIB formatter.cpp formatter.h)
add_library(formatter_lib STATIC ${SOURCE_LIB})
```
## Задание 2
У компании "Formatter Inc." есть перспективная библиотека, которая является расширением предыдущей библиотеки. Т.к. вы уже овладели навыком созданием CMakeList.txt для статической библиотеки formatter, ваш руководитель поручает заняться созданием CMakeList.txt для библиотеки formatter_ex, которая в свою очередь использует библиотеку formatter.
```
$ cd ../formatter_ex_lib/
$ cat >> CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.29)
project(formatter_ex)
EOF
$ cat >> CMakeLists.txt <<EOF
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CURRENT_SOURCE_DIR /Users/main/TiilS/workspace/projects/lab03/formatter_ex_lib)
EOF
$ cat >> CMakeLists.txt << EOF
add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.cpp)
EOF
$ cat >> CMakeLists.txt << EOF
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib)
EOF
$ cat >> CMakeLists.txt << EOF
target_link_libraries(formatter_ex formatter)
EOF
$ cmake -H. -B_build
$  g++ -c formatter_ex.cpp -o formatter_ex.o
$  ar rcs libformatter_ex.a formatter_ex.o
```
# Содержимое CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.29.2)

project(formatter_ex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установим путь к директории formatter_ex_lib
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib)

# Явно перечислим исходные файлы
set(SOURCES
    formatter_ex.cpp
)

# Создадим библиотеку formatter_ex
add_library(formatter_ex STATIC ${SOURCES})

# Установим директорию для поиска заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib)

# Добавим зависимость от библиотеки formatter
target_link_libraries(formatter_ex formatter)
```
# Задание 3
Конечно же ваша компания предоставляет примеры использования своих библиотек. Чтобы продемонстрировать как работать с библиотекой formatter_ex, вам необходимо создать два CMakeList.txt для двух простых приложений:

hello_world, которое использует библиотеку formatter_ex;
solver, приложение которое испольует статические библиотеки formatter_ex и solver_lib.
# 1. Hello_world_application
```
$ cd ../hello_world_application
$ cat >> CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.29.2)
project(hello_world)
EOF
$ cat >> CMakeLists.txt <<EOF
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CURRENT_SOURCE_DIR /Users/main/TiilS/workspace/projects/lab03)
EOF
$ cat >> CMakeLists.txt << EOF
add_executable(hello_world ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_application/hello_world.cpp)
EOF
$ cat >> ./CMakeLists.txt << EOF
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib)
EOF
$ cat >> CMakeLists.txt << EOF
find_library(formatter NAMES libformatter.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib)
find_library(formatter_ex NAMES libformatter_ex.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib)
EOF
$ cat >> CMakeLists.txt << EOF
target_link_libraries(hello_world ${formatter} ${formatter_ex})
EOF
$ cmake -H. -B_build
$ cmake --build _build
```
# Содержимое CMakeLists.txt:
```
cmake_minimum_required(VERSION 3.29.2)
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

project(hello_world)				 # Название проекта

set(SOURCE_EXE hello_world.cpp)			 # Установка переменной со списком исходников

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/)

add_executable(main ${SOURCE_EXE})	 # Создает исполняемый файл с именем main

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/ formatter_ex_lib)

target_link_libraries(main formatter_ex_lib)		 # Линковка программы с библиотекой
```
# Вывод: 
```
-- The C compiler identification is AppleClang 15.0.0.15000100
-- The CXX compiler identification is AppleClang 15.0.0.15000100
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/main/TiilS/workspace/projects/lab03/hello_world_application/_build
```
# 2. Solver_application
```
$ cd ../solver_lib/
$ cat >> ./CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.29)
project(solver)
EOF
$ cat >> CMakeLists.txt <<EOF
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CURRENT_SOURCE_DIR /Users/main/TiilS/workspace/projects/lab03)
EOF
$ cat >> ./CMakeLists.txt << EOF
add_library(solver_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/solver_lib/solver.cpp)
EOF
$ cat >> ./CMakeLists.txt << EOF
include_directories(/solver_lib /formatter_lib /formatter_ex_lib)
EOF
$ cat >> CMakeLists.txt << EOF
add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/solver_application/equation.cpp)
EOF
$ cat >> CMakeLists.txt << EOF
find_library(formatter NAMES libformatter.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib)
find_library(formatter_ex NAMES libformatter_ex.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib)
find_library(solver_lib NAMES libsolver.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/solver_lib)
 EOF
$ cat >> CMakeLists.txt << EOF
target_link_libraries(solver ${formatter} ${formatter_ex} ${solver_lib})
EOF
$ cmake -H. -B_build
$ cmake --build _build
```
CMakeLists.txt
```
cmake_minimum_required(VERSION 3.29.2)

project(solver)				# Название проекта

set(SOURCE_EXE equation.cpp)			# Установка переменной со списком исходников

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/"
					"${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib/")

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/ formatter_ex_lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib/ solver_lib)

target_link_libraries(main formatter_ex_lib solver_lib)		# Линковка программы с библиотекой
```
