#ifndef ZOOM_GLOBAL_H
#define ZOOM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZOOM_LIBRARY)
#  define ZOOM_EXPORT Q_DECL_EXPORT
#else
#  define ZOOM_EXPORT Q_DECL_IMPORT
#endif

#endif // ZOOM_GLOBAL_H
