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

CConfig::CConfig() : CRefCount()
{
	m_jacked_show_all = true;
	m_jacked_max_rows = 10;
	m_jacked_position.x = 48;
	m_jacked_position.y = -320;
	
	CConfigFile *configfile = GetConfigFile();
	
	if(configfile != NULL)
	{
		configfile->GetOrCreateBoolean("jacked_show_all", &m_jacked_show_all);
		configfile->GetOrCreateInt("jacked_max_rows", &m_jacked_max_rows);
		configfile->GetOrCreatePoint("jacked_position", &m_jacked_position);
	}
}

POINT CConfig::GetJackedPositionInScreen()
{
	POINT position;
	
	if(m_jacked_position.x < 0)
	{
		position.x = WIDTH;
		position.x += m_jacked_position.x;
		position.x -= m_jacked_show_all ? JACKED_ALL_WIDTH : JACKED_WIDTH;
	}
	else
	{
		position.x = m_jacked_position.x;
	}
	
	if(m_jacked_position.y < 0)
	{
		position.y = HEIGHT;
		position.y += m_jacked_position.y;
		position.y -= JACKED_HEIGHT;
	}
	else
	{
		position.y = m_jacked_position.y;
	}
	
	return position;
}
