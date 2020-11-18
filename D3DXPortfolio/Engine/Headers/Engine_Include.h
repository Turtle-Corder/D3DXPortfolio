#pragma once

#ifndef __ENGINE_INCLUDE_H__
#define __ENGINE_INCLUDE_H__

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <strsafe.h>
#include <ctime>
#include <algorithm>
#include <functional>
#include <tchar.h>
#include <process.h>


#include <d3d9.h>
#include <d3dx9.h>


#include "Engine_Macro.h"
#include "Engine_Typedef.h"
#include "Engine_Struct.h"
#include "Engine_Function.h"
#include "Engine_Enum.h"


#pragma warning(disable : 4251)

//#define DIRECTINPUT_VERSION	0x0800
//#include <dinput.h>


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif // DBG_NEW

#endif // _DEBUG

using namespace std;

#endif // !__ENGINE_INCLUDE_H__
