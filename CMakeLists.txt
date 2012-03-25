project(HsTestEditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(HsTestEditor_SRCS testnode.cpp test.cpp testmanager.cpp HsTestEditor.cpp main.cpp)
qt4_automoc(${HsTestEditor_SRCS})
QT4_WRAP_UI(UI_HEADERS mainwindow.ui)
QT4_ADD_RESOURCES(QRC_SOURCES hstesteditor.qrc)
add_executable(hstesteditor ${HsTestEditor_SRCS} ${UI_HEADERS} ${QRC_SOURCES})
target_link_libraries(hstesteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
