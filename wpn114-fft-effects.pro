TARGET = WPN114-fft-effects
TEMPLATE = lib
CONFIG += c++11 dll
QT += quick

localmod: DESTDIR = $$QML_MODULE_DESTDIR/WPN114/Audio/FFTEffects
else {
    DESTDIR = $$[QT_INSTALL_QML]/WPN114/Audio/FFTEffects
    QML_MODULE_DESTDIR = $$[QT_INSTALL_QML]
}

QMLDIR_FILES += $$PWD/qml/qmldir
QMLDIR_FILES += $$PWD/qml/ffteffects.qmltypes
OTHER_FILES = $$QMLDIR_FILES

for(FILE,QMLDIR_FILES) {
    QMAKE_POST_LINK += $$quote(cp $${FILE} $${DESTDIR}$$escape_expand(\n\t))
}

WPN114_AUDIO_REPOSITORY = ../WPN114-audio
INCLUDEPATH += $$WPN114_AUDIO_REPOSITORY
LIBS += -L$$QML_MODULE_DESTDIR/WPN114/Audio -lWPN114-audio
QMAKE_RPATHDIR += $$QML_MODULE_DESTDIR/WPN114/Audio

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
