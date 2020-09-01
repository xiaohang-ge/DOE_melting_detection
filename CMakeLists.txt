cmake_minimum_required(VERSION 3.0)

project(DOE_melting_detection)


if (MSVC)
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
endif()

# compiler
set(gcc_like_compilers GNU Clang Intel)

# warning level
if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]" OR CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    ADD_DEFINITIONS(
      -D_CRT_SECURE_NO_WARNINGS
      -D_CRT_SECURE_NO_DEPRECATE
      )
elseif((";${gcc_like_compilers};" MATCHES ";${CMAKE_CXX_COMPILER_ID};"))
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()


set(OpenCV_DIR D:/opencv/build)
find_package(OpenCV REQUIRED)

include_directories(
include
D:/eigen-eigen-bdd17ee3b1b3/eigen-eigen-bdd17ee3b1b3
${OpenCV_INCLUDE_DIRS}
)


add_executable(DOE_melting_detection src/main.cpp)

#依赖库
target_link_libraries(DOE_melting_detection
	${OpenCV_LIBS}
)