# Test framework
project(task1)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(
                     ${PROJECT_NAME}
                     ${CMAKE_THREAD_LIBS_INIT}
                     )
                  