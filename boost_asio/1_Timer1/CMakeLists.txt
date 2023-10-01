cmake_minimum_required(VERSION 3.20)

set(PROJ_NAME "boost_timer1")

project(${PROJ_NAME})

find_package(Boost 1.78 REQUIRED COMPONENTS headers program_options)

set( ${PROJ_NAME}_SRCS 
	main.cc
)

add_executable(${PROJ_NAME} ${${PROJ_NAME}_SRCS}) 
target_link_libraries(${PROJ_NAME} PUBLIC Boost::headers Boost::program_options)
