cmake_minimum_required(VERSION 3.1)
project(wpn114ffteffects-qml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_LINK_FLAGS)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

set(WPN114DEVICES_QML_SOURCES
    qml_plugin.cpp
    source/convolver/convolver.hpp
    external/fftconvolver/AudioFFT.cpp
    external/fftconvolver/FFTConvolver.cpp
    external/fftconvolver/TwoStageFFTConvolver.cpp
    external/fftconvolver/Utilities.cpp
    )

if (UNIX AND NOT APPLE)
    set(WPN114_ROOT /usr/lib/qt/qml/WPN114)
    set(WPN114AUDIO_ROOT ${WPN114_ROOT}/Audio)
    set(WPN114AUDIO_INCLUDE ${WPN114AUDIO_ROOT}/include)
endif()


add_library(${PROJECT_NAME} SHARED ${WPN114DEVICES_QML_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Qml -L${WPN114AUDIO_ROOT} -lwpn114audio-qml -lsndfile)
target_include_directories(${PROJECT_NAME} PUBLIC ${WPN114AUDIO_INCLUDE})

install(TARGETS ${PROJECT_NAME} DESTINATION ${WPN114AUDIO_ROOT}/Devices)
install(FILES qml/ffteffects.qmltypes qml/qmldir DESTINATION ${WPN114AUDIO_ROOT}/Devices)
