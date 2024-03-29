project(HsTestEditor)
cmake_minimum_required(VERSION 2.6)

if(CMAKE_CROSSCOMPILING)
  set(QT_HEADERS_DIR "/usr/i486-mingw32/include")
  set(QT_LIBRARY_DIR "/usr/i486-mingw32/lib")
endif(CMAKE_CROSSCOMPILING)

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(HsTestEditor_SRCS dlgsetting.cpp dlgfind.cpp htmltemplate.cpp dlgaddtask.cpp dlgcreatetest.cpp testnode.cpp test.cpp testmanager.cpp HsTestEditor.cpp main.cpp)
set(HsTestEditor_UIS dlgsetting.ui dlgaddtask.ui dlgcreatetest.ui mainwindow.ui)
set(HsTestEditor_QRCS hstesteditor.qrc)

qt4_automoc(${HsTestEditor_SRCS})
QT4_WRAP_UI(UI_HEADERS ${HsTestEditor_UIS})
QT4_ADD_RESOURCES(QRC_SOURCES ${HsTestEditor_QRCS})

add_executable(hstesteditor WIN32 ${HsTestEditor_SRCS} ${UI_HEADERS} ${QRC_SOURCES})
target_link_libraries(hstesteditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS hstesteditor DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES hstesteditor.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES icons/hstesteditor.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
