cmake_minimum_required (VERSION 3.22)

project("homework_3")

if (WIN32)
	list(APPEND flags "/W4" "/WX" "/permissive-")
else ()
	list(APPEND flags "-Werror" "-Wall" "-Wextra" "-Wpedantic" 
	"-fPIC")
endif()


add_executable (array_1 "array_1.cpp")
target_compile_options(array_1  PRIVATE ${flags})
add_executable (array_2 "array_2.cpp")
target_compile_options(array_2 PRIVATE ${flags})