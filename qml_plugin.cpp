#include "qml_plugin.hpp"

#include <source/convolver/convolver.hpp>
#include <QQmlEngine>
#include <qqml.h>

void qml_plugin::registerTypes(const char *uri)
{
    Q_UNUSED ( uri );
    qmlRegisterType<Convolver, 1> ( "WPN114.Audio.FFTEffects", 1, 0, "Convolver" );
}
