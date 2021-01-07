cmake_minimum_required(VERSION 3.0.0)
project(WLPCash VERSION 0.1.0)

find_package(wxWidgets COMPONENTS core base REQUIRED)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" )


include(CTest)
include( "${wxWidgets_USE_FILE}" )
enable_testing()

add_executable(WLPCash ${SOURCES} ${HEADERS})

target_link_libraries(WLPCash ${wxWidgets_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)