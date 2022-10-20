cmake_minimum_required(VERSION 3.5)

project(ant_colony_app VERSION 0.1 LANGUAGES CXX)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/GTest")
find_package(GTest REQUIRED)

SET(PROJECT_SOURCES
        world.cpp
        antcolony.cpp
        ant.cpp
        food.cpp
        pheromone.cpp
)
SET(PROJECT_HEADERS
        world.h
        antcolony.h
        ant.h
        food.h
        pheromone.h
)
add_library(antSim SHARED)
target_compile_features(antSim PUBLIC cxx_std_17)
target_sources(antSim
    PRIVATE
        ${PROJECT_SOURCES}
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${PROJECT_SOURCE_DIR}
            FILES ${PROJECT_HEADERS}
)
target_include_directories(antSim
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(ant_unittests)
target_sources(ant_unittests PRIVATE ant_unittests.cpp)
target_include_directories(ant_unittests PRIVATE "${GTEST_INCLUDE_DIRS}")
target_link_libraries(ant_unittests
    PRIVATE
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        antSim
)

set(QT_SOURCES
        main.cpp
        antpainter.h
        antpainter.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

#qt_add_executable(ant_colony_app
#    MANUAL_FINALIZATION
#    ${QT_SOURCES}
#)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${QT_SOURCES} )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE)
target_link_libraries(ant_colony_app PRIVATE Qt6::Widgets antSim)

#set_target_properties(ant_colony_app PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

install(TARGETS antSim
    EXPORT antSimTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT antSimTargets
    FILE antSimTargets.cmake
    NAMESPACE antSim::
    DESTINATION lib/cmake/antSim)

#install(
#    FILES
#        "antColonyConfig.cmake"
#    DESTINATION lib/cmake/binaryTree
#)

install(TARGETS ant_colony_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ant_colony_app)
endif()
