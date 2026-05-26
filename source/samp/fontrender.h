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

#pragma once

#include "../main.h"

#define DRAW_TEXTURE(texture, width)											\
{																				\
	RECT r = rect;																\
																				\
	r.left = r.left + ((r.right - r.left) - width) / 2;							\
	r.right = r.left + width;													\
																				\
	r.left += 1;																\
	r.top += 1;																	\
	r.right -= 1;																\
	r.bottom -= 1;																\
																				\
	if(texture == NULL)															\
		texture = fontrender->CreateTexture(texture##_data, texture##_size);	\
																				\
	fontrender->DrawTexture(texture, &texture##_rect, &r, 0xFFFFFFFF);			\
}

#pragma pack(push, 1)
class CFontRender
{
	public:
		MEMBER_BEGIN()
			MEMBER_VARIABLE_OFFZERO(ID3DXFont *			m_font1_colored)
			MEMBER_VARIABLE(0x4,	ID3DXFont *			m_font2_colored)
			MEMBER_VARIABLE(0x8,	ID3DXFont *			m_font1)
			MEMBER_VARIABLE(0xC,	ID3DXFont *			m_font2)
			MEMBER_VARIABLE(0x10,	ID3DXFont *			m_font3_colored)
			MEMBER_VARIABLE(0x14,	ID3DXSprite *		m_sprite)
			MEMBER_VARIABLE(0x18,	IDirect3DDevice9 *	m_device)
			MEMBER_VARIABLE(0x1C,	char *				m_buffer)
			MEMBER_VARIABLE(0x20,	int					m_sizeofy1)
			MEMBER_VARIABLE(0x24,	int					m_sizeofy2)
		MEMBER_END()
	
	public:
		static void ApplyHooks();
		
		POINT *CalcTextSize(POINT *size, const char *text, int format);
		void RenderText(ID3DXSprite *sprite, const char *text, int left, int top, int right, int bottom, int format, int color, int shadow);
		void DestroyDeviceObjects();
		void CreateFonts();
		
		void DrawTexture(IDirect3DTexture9 *texture, RECT *rect, D3DCOLOR color);
		void DrawTexture(IDirect3DTexture9 *texture, RECT *texture_rect, RECT *rect, D3DCOLOR color);
		void DrawText(const char *text, RECT *rect, uint32_t format, D3DCOLOR color, bool shadow, bool background);
		
		IDirect3DTexture9 *CreateTexture(uint8_t *data, uint32_t size);
};
#pragma pack(pop)
