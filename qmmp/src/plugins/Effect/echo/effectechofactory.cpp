#include "effectechofactory.h"
#include "settingsdialog.h"
#include "echoplugin.h"

const EffectProperties EffectEchoFactory::properties() const
{
    EffectProperties properties;
    properties.name = tr("Echo Plugin");
    properties.shortName = "echo";
    properties.hasSettings = true;
    return properties;
}

Effect *EffectEchoFactory::create()
{
    return new EchoPlugin();
}

void EffectEchoFactory::showSettings(QWidget *parent)
{
    SettingsDialog *s = new SettingsDialog(parent);
    s->show();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(echo, EffectEchoFactory)
#endif
