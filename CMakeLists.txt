cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
####################################################################################################
## Configure Project(s) ############################################################################

# Information
set(GIF_CMAKE_PROJECT_NAME "franciscoromano.gif")
project(${GIF_CMAKE_PROJECT_NAME})

# Output Directory
set(GIF_CMAKE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")

# Include Libraries
message(STATUS "${GIF_CMAKE_PROJECT_NAME} :: adding libraries...")
set(GIF_CMAKE_INCLUDE_LIBS "${CMAKE_DL_LIBS}")

# Include Directories
message(STATUS "${GIF_CMAKE_PROJECT_NAME} :: adding directories...")
set(GIF_CMAKE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/")
set(GIF_CMAKE_INCLUDE_DIRS "${GIF_CMAKE_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}/include/")
set(GIF_CMAKE_INCLUDE_DIRS "${GIF_CMAKE_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}/libraries/")
set(GIF_CMAKE_INCLUDE_DIRS "${GIF_CMAKE_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}/projects/GIF/")
set(GIF_CMAKE_INCLUDE_DIRS "${GIF_CMAKE_INCLUDE_DIRS};${PROJECT_SOURCE_DIR}/projects/sandbox/")

####################################################################################################
## Build Dynamic Library ###########################################################################

message(STATUS "${GIF_CMAKE_PROJECT_NAME} :: adding project files...")
file(GLOB GIF_CMAKE_PROJECT_FILES
    "${PROJECT_SOURCE_DIR}/projects/GIF89a/core/*.c"
    "${PROJECT_SOURCE_DIR}/projects/GIF89a/*.c"
)

# Create static library module (.lib)
message(STATUS "${GIF_CMAKE_PROJECT_NAME} :: configuring C/C++ project...")
set(LIBRARY_OUTPUT_PATH ${GIF_CMAKE_OUTPUT_PATH})
add_library(${GIF_CMAKE_PROJECT_NAME} STATIC
 ${GIF_CMAKE_PROJECT_FILES}
)
target_include_directories(${GIF_CMAKE_PROJECT_NAME} PRIVATE ${GIF_CMAKE_INCLUDE_DIRS})
target_link_libraries(${GIF_CMAKE_PROJECT_NAME} ${GIF_CMAKE_INCLUDE_LIBS})

####################################################################################################
###### DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ######

project("sandbox")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
add_executable("sandbox"
    "${PROJECT_SOURCE_DIR}/projects/sandbox/main.cpp"
)
target_include_directories("sandbox" PRIVATE ${GIF_CMAKE_INCLUDE_DIRS})

if(WIN32 AND "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
  target_link_libraries("sandbox" ${GIF_CMAKE_PROJECT_NAME} ${GIF_CMAKE_INCLUDE_LIBS} "${PROJECT_SOURCE_DIR}/libraries/console.x64.win32.lib")
else()
  target_link_libraries("sandbox" ${GIF_CMAKE_PROJECT_NAME} ${GIF_CMAKE_INCLUDE_LIBS} "${PROJECT_SOURCE_DIR}/libraries/console.x86.win32.lib")
endif()

###### DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ## DEBUG ######
####################################################################################################
