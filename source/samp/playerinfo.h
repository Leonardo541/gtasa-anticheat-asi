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

#pragma pack(push, 1)
class CStringBase
{
	public:
		union buf_type
		{
			char			local_buf[16];
			char *			alloc_buf;
		};
		
		MEMBER_BEGIN()
			MEMBER_VARIABLE(0x4,	buf_type		m_buf)
			MEMBER_VARIABLE(0x18,	int				m_allocated_capacity)
		MEMBER_END()
};
#pragma pack(pop)

#pragma pack(push, 1)
class CPlayerInfo
{
	public:
		MEMBER_BEGIN()
			MEMBER_VARIABLE(0x10,	CRemotePlayer *	m_remoteplayer)
			MEMBER_VARIABLE(0x14,	CStringBase		m_playername)
		MEMBER_END()
};
#pragma pack(pop)
