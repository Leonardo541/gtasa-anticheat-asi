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

CRemotePlayer *CPlayerPool::GetRemotePlayer(uint16_t playerid)
{
	if(m_created[playerid])
	{
		CPlayerInfo *playerinfo = m_players[playerid];
		
		if(playerinfo != NULL)
			return playerinfo->m_remoteplayer;
	}
	
	return NULL;
}

CPlayerPed *CPlayerPool::GetPlayerPed(uint16_t playerid)
{
	if(playerid == m_localplayerid)
	{
		if(m_localplayer != NULL)
			return m_localplayer->m_playerped;
	}
	else
	{
		CRemotePlayer *remoteplayer = GetRemotePlayer(playerid);
		
		if(remoteplayer != NULL)
			return remoteplayer->m_playerped;
	}
	
	return NULL;
}

const char *CPlayerPool::GetPlayerName(uint16_t playerid)
{
	if(playerid == m_localplayerid)
	{
		if(m_localplayername.m_allocated_capacity < 16)
		{
			return m_localplayername.m_buf.local_buf;
		}
		else
		{
			return m_localplayername.m_buf.alloc_buf;
		}
	}
	else if(m_created[playerid])
	{
		CPlayerInfo *playerinfo = m_players[playerid];
		
		if(playerinfo != NULL)
		{
			if(playerinfo->m_playername.m_allocated_capacity < 16)
			{
				return playerinfo->m_playername.m_buf.local_buf;
			}
			else
			{
				return playerinfo->m_playername.m_buf.alloc_buf;
			}
		}
	}
	
	return NULL;
}

uint16_t CPlayerPool::GetPlayerIdFromEntity(CEntitySA *entity)
{
	for(uint16_t i = 0; i < 1004; i++)
	{
		CPlayerPed *playerped = GetPlayerPed(i);
		
		if(playerped != NULL)
		{
			if(playerped->m_entity == entity)
				return i;
		}
	}
	
	return 0xFFFF;
}
