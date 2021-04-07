cmake_minimum_required(VERSION 3.5)

project(aproxim LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE sigma.icns)
    set(APP_ICON_MACOSX images/sigma.icns)
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)
find_package(Qt5 COMPONENTS DataVisualization REQUIRED)

if(WIN32)
    find_package(Qt5 COMPONENTS AxBase REQUIRED)
    find_package(Qt5 COMPONENTS AxContainer REQUIRED)
endif()

if(ANDROID)
  add_library(aproxim SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    options.cpp
    options.h
    options.ui
    common.h
    approximator.cpp
    approximator.h
    approximator_2.cpp
    approximator_2.h
    dataanalysis.cpp
    dataanalysis.h
    functions.cpp
    functions.h
    util.cpp
    util.h
    xls_table.cpp
    xls_table.h
    aproxim.qrc
  )
elseif(APPLE)
  add_executable(aproxim MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    options.cpp
    options.h
    options.ui
    common.h
    approximator.cpp
    approximator.h
    approximator_2.cpp
    approximator_2.h
    dataanalysis.cpp
    dataanalysis.h
    functions.cpp
    functions.h
    util.cpp
    util.h
    xls_table.cpp
    xls_table.h
    aproxim.qrc
    ${APP_ICON_MACOSX}
  )
else()
  add_executable(aproxim
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    options.cpp
    options.h
    options.ui
    common.h
    approximator.cpp
    approximator.h
    approximator_2.cpp
    approximator_2.h
    dataanalysis.cpp
    dataanalysis.h
    functions.cpp
    functions.h
    util.cpp
    util.h
    xls_table.cpp
    xls_table.h
    aproxim.qrc
    aproxim.rc
  )
endif()

if(WIN32)
    target_link_libraries(aproxim PRIVATE Qt5::Widgets Qt5::Charts Qt5::DataVisualization Qt5::AxBase Qt5::AxContainer)
else()
    target_link_libraries(aproxim PRIVATE Qt5::Widgets Qt5::Charts Qt5::DataVisualization)
endif()
