
#include <QtCore>
#include <QtGui>
#include "widgetfactory.h"

namespace PlexyDesk
{

class WidgetFactory::Private
{
    public:
        Private() {}
        ~Private() {}
        WidgetInterface * currentDrop;
};


WidgetFactory::WidgetFactory(QObject * parent):QObject(parent),d(new Private)
{
#ifdef Q_WS_MAC
    QPluginLoader loader ("/usr/local/lib/plexyext/widgets/libwidgetdemo.dylib");
#endif

#ifdef Q_WS_X11
    QPluginLoader loader ("/usr/local/lib/plexyext/widgets/libwidgetdemo.so");
#endif

    QObject * plugin =  loader.instance();
    if (plugin) {
        d->currentDrop = qobject_cast<WidgetInterface*>(plugin);
    }else {
        qDebug()<<loader.errorString()<<endl;;
        d->currentDrop = 0;
    }
}

WidgetFactory::~WidgetFactory()
{
    delete d;
}

WidgetInterface * WidgetFactory::instance ()
{
return d->currentDrop ;
}

} // namespace PlexyDesk


#include "widgetfactory.moc"
