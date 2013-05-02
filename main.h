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

#ifndef MAIN_H
#define MAIN_H

#define __mS(cc)	#cc
#define _mS(zz)	__mS(zz)

#define MAJOR_NUMBER 0
#define MINOR_NUMBER 1
#define BUILD_NUMBER 1
#define BUILD_NUMBER_STRING _mS(BUILD_NUMBER)
#define VERSION_NUMBER_STRING _mS(MAJOR_NUMBER) "." _mS(MINOR_NUMBER) "." BUILD_NUMBER_STRING
#define FULL_VERSION_NUMBER_STRING (VERSION_NUMBER_STRING)

#define SAFE_VERSION_NUMBER_STRING (_mS(MAJOR_NUMBER) _mS(MINOR_NUMBER) BUILD_NUMBER_STRING)
#define SAFE_FULL_VERSION_NUMBER_STRING (SAFE_VERSION_NUMBER_STRING)
#define COMPANY_NAME "Your Name"

#define PROGNAME	"NppSkeleton"
#define VERSION		FULL_VERSION_NUMBER_STRING
#define COPYRIGHT	"Copyright \xa9 2013 " COMPANY_NAME
#define BOXTITLE	PROGNAME " " VERSION " " COPYRIGHT
#define PROGDESC	"Notepad++ PlugIn"

#define ICON_ID	100
#define ICON_ID_LARGE ICON_ID
#define ICON_ID_SMALL ICON_ID

#define UNUSED __attribute__((unused)) /* for functions, variables and types */
#define USED   __attribute__((used))   /* for functions only! */
#define INLINE static __inline __attribute__((always_inline))

#define CONSTRUCTOR( function ) \
	static void __attribute__((constructor)) function ( void )

#define DESTRUCTOR( function ) \
	static void __attribute__((destructor)) function ( void )

#endif /* MAIN_H */
