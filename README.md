# FHE Implementation 
implementation of CKKS Scheme using C++
> Based on: https://github.com/openfheorg/openfhe-development

### How to set up this project
type this script in your terminal
- touch CMakeLists.txt
- mkdir build
- cd build
- cmake -S ../ -B .

after that we write some script in CMakeLists.txt file in the root folder (of this project)
- for making sure the minimum version of cmake was fullfiled you can check it by using
    - cmake --version

after we write some script in CMakeLists.txt
- cmake -S ../ -B .
- make

## Directory Structure
The below trees describes the structure of this repostitory.
```
|-> benchmark
|
|-> build
|
|-> configure
|
|-> src
|   |-> binfhe
|   |-> core
|   |-> pke
|-> test
|-> third-party
```

## The descriptions of library components
| Directory   | Description      |
|:------------|:-----------------|
| benchmark   | Code for benchmarking OpenFHE library components, using the Google Benchmark frameworks. |
| build       | Binaries and build scripts (this folder is created by the user).  |
| configure   | Preparation for creating config_core.h file  |
| src         | Library source code. Each subcomponent has four or five subdirectories: include (for library header files), lib (for library source files), unittest (for google test cases), examples (for code samples), and optionally extras (for additional code samples). |
| test        | Google unit test code.   |
| third-party | Code for distributions from third parties (includes NTL/GMP + git submodules for gperftools, cereal, google test, and google benchmark). |