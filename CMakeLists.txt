project(HsTestEditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(HsTestEditor_SRCS HsTestEditor.cpp main.cpp)
qt4_automoc(${HsTestEditor_SRCS})
QT4_WRAP_UI(ui_mainwindow.h mainwindow.ui)
add_executable(hstesteditor ${HsTestEditor_SRCS} ui_mainwindow.h)
target_link_libraries(hstesteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
