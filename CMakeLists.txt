project(HsTestEditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(HsTestEditor_SRCS HsTestEditor.cpp main.cpp)
qt4_automoc(${HsTestEditor_SRCS})
add_executable(HsTestEditor ${HsTestEditor_SRCS})
target_link_libraries(HsTestEditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
