DEFINES += QT_DEPRECATED_WARNINGS

WPN114_AUDIO_REPOSITORY = ../WPN114-audio
INCLUDEPATH += $$WPN114_AUDIO_REPOSITORY
LIBS += -L$$[QT_INSTALL_QML]/WPN114/Audio -lWPN114-audio

macx {
    QMAKE_MAC_SDK = macosx10.14
}

HEADERS += $$PWD/source/convolver/convolver.hpp
HEADERS += $$PWD/external/fftconvolver/AudioFFT.h
HEADERS += $$PWD/external/fftconvolver/FFTConvolver.h
HEADERS += $$PWD/external/fftconvolver/TwoStageFFTConvolver.h
HEADERS += $$PWD/external/fftconvolver/Utilities.h

SOURCES += $$PWD/source/convolver/convolver.cpp
SOURCES += $$PWD/external/fftconvolver/AudioFFT.cpp
SOURCES += $$PWD/external/fftconvolver/FFTConvolver.cpp
SOURCES += $$PWD/external/fftconvolver/TwoStageFFTConvolver.cpp
SOURCES += $$PWD/external/fftconvolver/Utilities.cpp

SOURCES += $$PWD/qml_plugin.cpp
HEADERS += $$PWD/qml_plugin.hpp
