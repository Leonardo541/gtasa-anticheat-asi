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

MEMBER_TYPEDEF(CFontRender, POINT *, CalcTextSize_t, POINT *size, const char *text, int format);
MEMBER_TYPEDEF(CFontRender, void, RenderText_t, ID3DXSprite *, const char *, int, int, int, int, int, int, int);
MEMBER_TYPEDEF(CFontRender, void, DestroyDeviceObjects_t);
MEMBER_TYPEDEF(CFontRender, void, CreateFonts_t);

static CalcTextSize_t pfnCalcTextSize = NULL;
static RenderText_t pfnRenderText = NULL;
static DestroyDeviceObjects_t pfnDestroyDeviceObjects = NULL;
static CreateFonts_t pfnCreateFonts = NULL;

void CFontRender::ApplyHooks()
{
	if(samp_version == SAMP_VERSION_037)
	{
		POINTER_TO_MEMBER(pfnCalcTextSize, samp_address + 0x00066BD0);
		POINTER_TO_MEMBER(pfnRenderText, samp_address + 0x00066E00);
		
		MEMBER_CALL(samp_address + 0x000B299C, CFontRender, DestroyDeviceObjects);
		MEMBER_CALL(samp_address + 0x00064AF3, CFontRender, CreateFonts);
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		POINTER_TO_MEMBER(pfnCalcTextSize, samp_address + 0x0006B2B0);
		POINTER_TO_MEMBER(pfnRenderText, samp_address + 0x0006B4E0);
		
		MEMBER_CALL(samp_address + 0x000C3F6C, CFontRender, DestroyDeviceObjects);
		MEMBER_CALL(samp_address + 0x000686C3, CFontRender, CreateFonts);
	}
}

POINT *CFontRender::CalcTextSize(POINT *size, const char *text, int format)
{
	return METHOD_CALL(this, pfnCalcTextSize, size, text, format);
}

void CFontRender::RenderText(ID3DXSprite *sprite, const char *text, int left, int top, int right, int bottom, int format, int color, int shadow)
{
	METHOD_CALL(this, pfnRenderText, sprite, text, left, top, right, bottom, format, color, shadow);
}

void CFontRender::CreateFonts()
{
	calc_text_size = true;
	
	return METHOD_CALL(this, pfnCreateFonts);
}

void CFontRender::DestroyDeviceObjects()
{
	if(blank_texture != NULL)
	{
		blank_texture->Release();
		blank_texture = NULL;
	}
	
	if(close_texture != NULL)
	{
		close_texture->Release();
		close_texture = NULL;
	}
	
	if(alert_texture != NULL)
	{
		alert_texture->Release();
		alert_texture = NULL;
	}
	
	METHOD_CALL(this, pfnDestroyDeviceObjects);
}

void CFontRender::DrawTexture(IDirect3DTexture9 *texture, RECT *rect, D3DCOLOR color)
{
	RECT r;
	
	r.left = 0;
	r.top = 0;
	r.right = rect->right - rect->left;
	r.bottom = rect->bottom - rect->top;
	
	D3DXVECTOR3 position((float)rect->left, (float)rect->top, 0.0f);
	m_sprite->Draw(texture, &r, NULL, &position, color);
}

void CFontRender::DrawTexture(IDirect3DTexture9 *texture, RECT *texture_rect, RECT *rect, D3DCOLOR color)
{
	D3DXMATRIX oldmatrix;
	m_sprite->GetTransform(&oldmatrix);
	
	D3DXVECTOR2 scale;

	scale.x = (float)(rect->right - rect->left) / (float)(texture_rect->right - texture_rect->left);
	scale.y = (float)(rect->bottom - rect->top) / (float)(texture_rect->bottom - texture_rect->top);
	
	D3DXVECTOR2 trans((float)rect->left, (float)rect->top);
	
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scale, NULL, 0.0f, &trans);
	m_sprite->SetTransform(&matrix);
	
	m_sprite->Draw(texture, texture_rect, NULL, NULL, color);
	
	m_sprite->SetTransform(&oldmatrix);
}

void CFontRender::DrawText(const char *text, RECT *rect, uint32_t format, D3DCOLOR color, bool shadow, bool background)
{
	if(background)
	{
		if(blank_texture == NULL)
			blank_texture = CreateTexture(blank_texture_data, blank_texture_size);
		
		DrawTexture(blank_texture, rect, 0xAA000000);
	}
	
	rect->left += 8;
	rect->right -= 8;
	
	RenderText(m_sprite, text, rect->left, rect->top, rect->right, rect->bottom, format, color, shadow);
	
	rect->left -= 8;
	rect->right += 8;
}

IDirect3DTexture9 *CFontRender::CreateTexture(uint8_t *data, uint32_t size)
{
	IDirect3DTexture9 *texture;
	
	if(SUCCEEDED(D3DXCreateTextureFromFileInMemoryEx(m_device, data, size, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture)))
		return texture;
	
	return NULL;
}
