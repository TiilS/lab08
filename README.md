## HOMEWORK
# CPack.cmake
```
name: CPack

on:
 push:
   tags:
     - v**

jobs: 

  build_packages_Linux:

    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v3

    - name: Configure Solver
      run: cmake ${{github.workspace}} -B ${{github.workspace}}/build -D PRINT_VERSION=${GITHUB_REF_NAME#v}

    - name: Build Solver
      run: cmake --build ${{github.workspace}}/build

    - name: Build package
      run: cmake --build ${{github.workspace}}/build --target package

    - name: Build source package
      run: cmake --build ${{github.workspace}}/build --target package_source

    - name: Make a release
      uses: ncipollo/release-action@v1.10.0
      with:
        artifacts: "build/*.deb,build/*.tar.gz,build/*.zip"
        token: ${{ secrets.GITHUB_TOKEN }}
```
# CMakeLists.txt
```
cmake_minimum_required(VERSION 3.29)

project(solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib formatter_ex_lib_dir)

add_library(solver_lib ${CMAKE_CURRENT_SOURCE_DIR}/solver_lib/solver.cpp)
add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/solver_application/equation.cpp)

target_include_directories(formatter_ex_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib
${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib
${CMAKE_CURRENT_SOURCE_DIR}/solver_lib
)

target_link_libraries(solver formatter_ex_lib formatter_lib solver_lib)

# Инструкции для инсталляции
install(TARGETS solver
    RUNTIME DESTINATION bin
)

include(CPack.cmake)
```
# actions.yml
```
name: CPack

on:
 push:
  branches: [master]
 pull_request:
  branches: [master]

jobs: 
 build_Linux:

  runs-on: ubuntu-latest

  steps:
  - uses: actions/checkout@v4

  - name: Configure Solver
    run: cmake ${{github.workspace}} -B ${{github.workspace}}/build

  - name: Build Solver
```
# Cpack.yml
```
name: CPack

on:
 push:
  branches: [master]
 pull_request:
  branches: [master]

jobs: 
 build_Linux:

  runs-on: ubuntu-latest

  steps:
  - uses: actions/checkout@v4

  - name: Configure Solver
    run: cmake ${{github.workspace}} -B ${{github.workspace}}/build

  - name: Build Solver
    run: cmake --build ${{github.workspace}}/build
```
