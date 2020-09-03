cmake_minimum_required(VERSION 3.5)

project(physics-engine LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(physics-engine SHARED
    albody.h
    alcollision.h
    almath.h
    alworld.h
    alrenderer.h
    alsettings.h
    albody.cpp
    alcollision.cpp
    almath.cpp
    alrenderer.cpp
    alworld.cpp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(physics-engine
    albody.h
    alcollision.h
    almath.h
    alworld.h
    alrenderer.h
    alsettings.h
    albody.cpp
    alcollision.cpp
    almath.cpp
    alrenderer.cpp
    alworld.cpp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
endif()

target_link_libraries(physics-engine PRIVATE Qt5::Widgets)
