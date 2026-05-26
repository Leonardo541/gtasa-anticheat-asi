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

#include "../main.h"

MEMBER_TYPEDEF(CCmdWindow, void, Enable_t);
MEMBER_TYPEDEF(CCmdWindow, void, Disable_t);
MEMBER_TYPEDEF(CCmdWindow, void, OnRender_t);
MEMBER_TYPEDEF(CCmdWindow, int, MsgProc_t, UINT, WPARAM, LPARAM);

static Enable_t pfnEnable = NULL;
static Disable_t pfnDisable = NULL;
static OnRender_t pfnOnRender = NULL;
static MsgProc_t pfnMsgProc = NULL;

void CCmdWindow::ApplyHooks()
{
	POINTER_TO_MEMBER(pfnEnable, samp_address + 0x00069480);
	POINTER_TO_MEMBER(pfnDisable, samp_address + 0x00069580);
	
	MEMBER_CALL(samp_address + 0x00075A90, CCmdWindow, OnRender);
	MEMBER_CALL(samp_address + 0x000616C2, CCmdWindow, MsgProc);
}

void CCmdWindow::Enable()
{
	METHOD_CALL(this, pfnEnable);
}

void CCmdWindow::Disable()
{
	METHOD_CALL(this, pfnDisable);
}

void CCmdWindow::OnRender()
{
	CFontRender *fontrender = *(CFontRender **)(samp_address + 0x0026EB9C);
	
	if(fontrender)
	{
		if(!m_enable)
		{
			if(mouse_position.x != 0 || mouse_position.y != 0)
			{
				mouse_position.x = 0;
				mouse_position.y = 0;
			}
		}
		
		if(calc_text_size)
		{
			fontrender->CalcTextSize(&text_size_pname, "LONGESTNICKNICK_NICKNICK", DT_LEFT);
			fontrender->CalcTextSize(&text_size_4chrs, "YYYY", DT_LEFT);
			fontrender->CalcTextSize(&text_size_2chrs, "YY", DT_LEFT);
			
			text_size_pname.x += 8;
			text_size_pname.y += 4;
			
			text_size_4chrs.x += 8;
			text_size_4chrs.y += 4;
			
			text_size_2chrs.x += 8;
			text_size_2chrs.y += 4;
			
			calc_text_size = false;
		}
		
		fontrender->m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		DrawJacked(fontrender);
		
		fontrender->m_sprite->End();
	}
	
	METHOD_CALL(this, pfnOnRender);
}

int CCmdWindow::MsgProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(m_enable)
	{
		if(msg == WM_LBUTTONDOWN || msg == WM_MOUSEMOVE)
		{
			mouse_position = MAKEPOINTS(lparam);
		}
		else if(msg == WM_LBUTTONUP)
		{
			mouse_position = MAKEPOINTS(lparam);
			
			POINT position = config.GetPtr()->GetJackedPositionInScreen();
			
			for(std::vector<CRefPtr<CJacked>>::reverse_iterator it = jacked_list.rbegin(); it != jacked_list.rend(); it++)
			{
				CRefPtr<CJacked> jacked = *it;
				
				if(jacked.GetPtr()->IsMouseInCloseRect())
				{
					jacked_list.erase((++it).base());
					
					Disable();
					Enable();
					
					*(uint32_t *)(samp_address + 0x0012DE6C) = 0; // cancel CCmdWindow::Disable()
					return 0;
				}
				
				position.y -= JACKED_HEIGHT + 4;
			}
		}
	}
	
	return METHOD_CALL(this, pfnMsgProc, msg, wparam, lparam);
}

void CCmdWindow::DrawJacked(CFontRender *fontrender)
{
	POINT position = config.GetPtr()->GetJackedPositionInScreen();
	
	time_t rawtime;
	time(&rawtime);
	
	bool clear_jacked_list = false;
	
	for(std::vector<CRefPtr<CJacked>>::reverse_iterator it = jacked_list.rbegin(); it != jacked_list.rend(); it++)
	{
		CRefPtr<CJacked> jacked = *it;
		
		time_t time_elapsed = rawtime - jacked.GetPtr()->GetRawtime();
		
		if(time_elapsed > 99)
		{
			clear_jacked_list = true;
			continue;
		}
		
		jacked.GetPtr()->Draw(fontrender, position, rawtime);
		
		position.y -= JACKED_HEIGHT + 4;
	}
	
	if(clear_jacked_list)
	{
		std::vector<CRefPtr<CJacked>>::iterator it = jacked_list.begin();
		
		while(it != jacked_list.end())
		{
			CRefPtr<CJacked> jacked = *it;
			
			time_t time_elapsed = rawtime - jacked.GetPtr()->GetRawtime();
			
			if(time_elapsed > 99)
			{
				it = jacked_list.erase(it);
				continue;
			}
			
			it++;
		}
	}
}
