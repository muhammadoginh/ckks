##
## CMakeLists.txt for CKKS implementation based on OpenFHE
##
## This script will build machine-specific header files for compile
## as it generates the Makefile
##
## Note many user options are handled using an OPTION in CMake
## An option has the value of ON or OFF
## See below for the list of options


cmake_minimum_required(VERSION 3.25.0)

project(FHE C CXX)

# add_executable(${PROJECT_NAME} main.cpp)

#--------------------------------------------------------------------
# Installation logic
#--------------------------------------------------------------------


### set up for install
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")


#--------------------------------------------------------------------
# Third-party logic
#--------------------------------------------------------------------

### add each of the subdirs of src
add_subdirectory(src/core)
add_subdirectory(src/pke)
add_subdirectory(src/binfhe)
