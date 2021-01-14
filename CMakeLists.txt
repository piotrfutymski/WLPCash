cmake_minimum_required(VERSION 3.0.0)
project(WLPCash VERSION 0.1.0)

SET(CXX_STANDARD 11)
SET(CXX_STANDARD_REQUIRED TRUE)
SET(SOCI_CXX11 ON)
SET(SOCI_TESTS OFF)

if(WIN32)
	set(wxWidgets_ROOT_DIR C:/Users/Jakub/source/lib/wxWidgets-3.1.4)
	set(wxWidgets_LIB_DIR C:/Users/Jakub/source/lib/wxWidgets-3.1.4/lib/vc_x64_lib)
	set(wxWidgets_CONFIGURATION mswud)
endif()
find_package(wxWidgets COMPONENTS core base REQUIRED)

add_subdirectory(lib/SOCI)



include_directories("include" "lib/SOCI/include" "build/lib/SOCI/include")

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" )

include(CTest)
include( "${wxWidgets_USE_FILE}" )
enable_testing()

add_executable(WLPCash ${SOURCES} ${HEADERS})

target_link_libraries(WLPCash ${wxWidgets_LIBRARIES} soci_core soci_odbc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)