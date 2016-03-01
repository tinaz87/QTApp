#include <QtWidgets>
#include <QtGui>
#include <QGLWidget>

#include <vector>
#include <map>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "GameSettings.h"
//#include "Drawer.h"
#include "GLWidget.h"
#include "Window.h"
#include "Snake.h"
#include "Player.h"
#include "Field.h"

#include "Utils.h"