set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(example example.cpp)

target_link_libraries(
		example
		TensorflowCC::Shared)