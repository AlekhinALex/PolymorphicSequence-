cmake_minimum_required(VERSION 3.16)

project(Sequence VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Sequence_ru_RU.ts)

add_library(Models STATIC
    models/inc/arraySequence.hpp
    models/impl/arraySequence.tpp
    models/inc/dynamicArray.hpp
    models/impl/dynamicArray.tpp
    models/inc/linkedList.hpp
    models/impl/linkedList.tpp
    models/inc/listSequence.hpp
    models/impl/listSequence.tpp
    models/inc/sequence.hpp
)

set(PROJECT_SOURCES
    main.cpp
    views/operationdialog.h
    views/operationdialog.cpp
    views/createSequenceDialog.cpp
    views/createSequenceDialog.h
    views/mainwindow.cpp
    views/mainwindow.h
    views/mainwindow.ui
    controllers/MainController.cpp
    controllers/MainController.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sequence
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Sequence SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Sequence
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Sequence PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Models
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Sequence)
endif()

set_target_properties(Sequence PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Sequence Models
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sequence)
endif()
