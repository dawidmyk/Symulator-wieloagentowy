cmake_minimum_required(VERSION 3.5)
project(App)
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "builds")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "debug")
ADD_CUSTOM_TARGET(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
  )

ADD_CUSTOM_TARGET(release
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Switch CMAKE_BUILD_TYPE to Release"
  )
include_directories(headers inline-sources)
file(GLOB SOURCES "sources/*.cpp")
add_executable(app ${SOURCES})

