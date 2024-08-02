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
#include <RSC.h>
HMODULE g_hRSC;
BOOL (WINAPI *RSC_DllEntryPoint)(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);

extern UCHAR RSC_text[0xA9000];
extern UCHAR RSC_rdata[0x26000];
extern UCHAR RSC_data[0x8000];
extern UCHAR RSC_syhks00[0x4000];
extern UCHAR RSC_patch[0x1000];
extern UCHAR RSC_rsrc[0x484000];
extern UCHAR RSC_reloc[0x7000];

__declspec(align(16)) stRSC RSC;

void* __stdcall RSC_RVA(DWORD rvaAddr)
{
	return (UCHAR*)&RSC + rvaAddr;
}


#if 0
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif
