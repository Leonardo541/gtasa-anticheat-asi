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

CRemotePlayer *CPlayerInfo::GetRemotePlayer()
{
	if(samp_version == SAMP_VERSION_037)
	{
		return v037.m_remoteplayer;
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		return v037_r5.m_remoteplayer;
	}
	
	return NULL;
}

const char *CPlayerInfo::GetPlayerName()
{
	CStringBase *str = NULL;
	
	if(samp_version == SAMP_VERSION_037)
	{
		str = &v037.m_playername;
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		str = &v037_r5.m_playername;
	}
	
	if(str != NULL)
	{
		if(str->m_allocated_capacity < 16)
		{
			return str->m_buf.local_buf;
		}
		else
		{
			return str->m_buf.alloc_buf;
		}
	}
	
	return NULL;
}
