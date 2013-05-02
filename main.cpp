/* ***** BEGIN LICENSE BLOCK *****
 * Version: MIT/X11 License
 * 
 * Copyright (c) 2013 Diego Casorran
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * 
 * Contributor(s):
 *   Diego Casorran <dcasorran@gmail.com> (Original Author)
 * 
 * ***** END LICENSE BLOCK ***** */

#define UNICODE

#ifdef UNICODE
# include <_mingw.h>
# define _UNICODE 1
# define _GLIBCXX_USE_WCHAR_T 1
#endif
#include <w32api.h>
#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <wincrypt.h>
#include <ddk/ntapi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <errno.h>
#include <dirent.h>

#include "PluginInterface.h"
#include "main.h"

static NppData nppData;

/*--------------------------------------------------------------------------*/

void hello()
{
	::MessageBox(NULL, TEXT("Hello, World!"), TEXT(PROGNAME), MB_OK);
}

/*--------------------------------------------------------------------------*/

static HWND getCurrentScintilla()
{
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return NULL;
	return (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;
}

/*--------------------------------------------------------------------------*/
static FuncItem *funcItem = NULL;
static int cmdItemCount = 0, cmdAllocItems = 10;

#define setFunction(N,F) setCommand((TCHAR *)TEXT(N),F,NULL,false)

static bool setCommand(TCHAR *n, PFUNCPLUGINCMD f, ShortcutKey *k, bool ci)
{
	if(funcItem == NULL && !(funcItem = (FuncItem *)calloc(cmdAllocItems+1,sizeof(*funcItem)))) {
		return false;
	}
	
	if(cmdItemCount+1 == cmdAllocItems) {
		funcItem = (FuncItem *)realloc(funcItem,(cmdAllocItems+=2)*sizeof(*funcItem));
		if(!funcItem) return false;
	}
	
	if(f) {
		lstrcpy(funcItem[cmdItemCount]._itemName, n);
		funcItem[cmdItemCount]._pFunc = f;
		funcItem[cmdItemCount]._init2Check = ci;
		funcItem[cmdItemCount]._pShKey = k;
		++cmdItemCount;
	}
	return !!f;
}

INLINE void commandMenuInit() {
	setFunction("Hello Notepad",hello);
}

INLINE void commandMenuCleanUp() {
	int i;
	
	for( i = 0 ; i < cmdItemCount ; ++i ) {
		
		if(funcItem[i]._pShKey) {
			free(funcItem[i]._pShKey);
		}
	}
	
	free(funcItem);
}

INLINE void pluginInit(HANDLE /* hModule */) {
	commandMenuInit();
}

INLINE void pluginCleanUp() {
	commandMenuCleanUp();
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData) {
	nppData = notpadPlusData;
}

extern "C" __declspec(dllexport) const TCHAR * getName() {
	return TEXT(PROGNAME);
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF) {
	*nbF = cmdItemCount;
	return funcItem;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification */*notifyCode*/) {
	
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT /* Message */, WPARAM /* wParam */, LPARAM /* lParam */) {
	return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode() {
	return TRUE;
}
#endif

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain( HANDLE hModule, DWORD reasonForCall, LPVOID /* lpReserved */) {
	switch (reasonForCall) {
		case DLL_PROCESS_ATTACH:
			pluginInit(hModule);
			break;
		
		case DLL_PROCESS_DETACH:
			pluginCleanUp();
			break;
		
		case DLL_THREAD_ATTACH:
			break;
		
		case DLL_THREAD_DETACH:
			break;
	}
	return true;
}
