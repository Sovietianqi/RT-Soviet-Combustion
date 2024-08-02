/*
 * Project Name: [RT-Soviet-Combustion]
 * Copyright (C) [星空赤影，Sovietianqi & RT Studio]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact Information:
 * [星空赤影，Sovietianqi & RT Studio]
 * [https://github.com/Sovietianqi/RT-Soviet-Combustion]
 */
#include <lib/RSCLoadPNG.hpp>
#if !defined(_RSC_SUPP_H_00568000_INCLUDED_)
#define _RSC_SUPP_H_00568000_INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#pragma pack(push)
#pragma pack(1)
__declspec(align(16)) struct stRSC
{
	UCHAR Header[0x1000];
	UCHAR Text[0xA9000];
	UCHAR Rdata[0x26000];
	UCHAR Data[0x8000];
	UCHAR Syhks00[0x4000];
	UCHAR Patch[0x1000];
	UCHAR Rsrc[0x484000];
	UCHAR Reloc[0x7000];
};
#pragma pack(pop)
__declspec(align(16)) extern stRSC RSC;
/* Data for initialization. */
extern UCHAR RSC_InitData[0xD13E];
extern HMODULE g_hRSC;
void* __stdcall RSC_RVA(DWORD rvaAddr);
#define RSC_VA(vaAddr) RSC_RVA((vaAddr) - 0x10000000)
#pragma once
#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#include <atlbase.h>
#include <atlstr.h>
#ifndef ASSERT
#include <assert.h>
#define ASSERT(x) assert(x)
#endif
#pragma once
#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif
#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif
#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif
#endif // !defined(_RSC_SUPP_H_00568000_INCLUDED_)
