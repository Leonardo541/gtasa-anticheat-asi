/*
 * MIT License
 *
 * Copyright (c) 2026 Leonardo541
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "main.h"

uint32_t samp_address = 0;

CRefPtr<CConfig> config;

std::vector<CRefPtr<CJacked>> jacked_list;

POINTS mouse_position = {0, 0};

POINT text_size_pname = {0, 0};
POINT text_size_4chrs = {0, 0};
POINT text_size_2chrs = {0, 0};

bool calc_text_size = true;

typedef int (__cdecl *EndLoop_t)(void *camera);

EndLoop_t pfnEndLoop = NULL;

bool Unlock(uint32_t address, int len)
{
	DWORD oldp;
	return !!VirtualProtect((void *)address, len, PAGE_EXECUTE_READWRITE, &oldp);
}

void Call(uint32_t address, uint32_t function, uint32_t *old)
{
	if(Unlock(address, 5))
	{
		if(*(uint8_t *)(address) == 0xE8)
		{
			if(old != NULL)
				*old = *(uint32_t *)(address + 1) + (address + 5);
			
			*(uint32_t *)(address + 1) = function - (address + 5);
		}
	}
}

void Initialize()
{
	BitStream::ApplyHooks();
	CCmdWindow::ApplyHooks();
	CConfigFile::ApplyHooks();
	CFontRender::ApplyHooks();
	CNetGame::ApplyHooks();
	
	config = new CConfig();
}

int EndLoop(void *camera)
{
	int ret = pfnEndLoop(camera);
	
	if(*(uint32_t *)0x00C8D4C0 == 9)
	{
		static bool initialized = false;
		
		if(!initialized)
		{
			samp_address = (uint32_t)GetModuleHandle("samp.dll");
			
			if(samp_address != 0)
			{
				CConfigFile *configfile = *(CConfigFile **)(samp_address + 0x0026EB7C);
				
				if(configfile != NULL)
				{
					Initialize();
					initialized = true;
				}
			}
		}
	}
	
	return ret;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		Call(0x0053EC01, (uint32_t)EndLoop, (uint32_t *)&pfnEndLoop);
	}
	else if(reason == DLL_PROCESS_DETACH)
	{
		
	}
	
	return TRUE;
}
