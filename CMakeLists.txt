cmake_minimum_required(VERSION 3.5)

project(ExpressionCalc)

file(GLOB SRC_FILES
        "./src/*.cpp"
        )

add_executable(${PROJECT_NAME} ${SRC_FILES})