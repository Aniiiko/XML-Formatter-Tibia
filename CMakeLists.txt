cmake_minimum_required(VERSION 3.10)
project(Formatter)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_executable(Formatter ${formatter_src})

# Copy the input directory to the build output directory
add_custom_command(TARGET Formatter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/input $<TARGET_FILE_DIR:Formatter>/input
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/output $<TARGET_FILE_DIR:Formatter>/output
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/src/items.xml $<TARGET_FILE_DIR:Formatter>/items.xml)