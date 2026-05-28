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

uint16_t CPlayerPool::GetLocalPlayerId()
{
	if(samp_version == SAMP_VERSION_037)
	{
		return v037.m_localplayerid;
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		return v037_r5.m_localplayerid;
	}
	
	return 0xFFFF;
}

const char *CPlayerPool::GetLocalPlayerName()
{
	CStringBase *str = NULL;
	
	if(samp_version == SAMP_VERSION_037)
	{
		str = &v037.m_localplayername;
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		str = &v037_r5.m_localplayername;
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

CLocalPlayer *CPlayerPool::GetLocalPlayer()
{
	if(samp_version == SAMP_VERSION_037)
	{
		return v037.m_localplayer;
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		return v037_r5.m_localplayer;
	}
	
	return NULL;
}

CPlayerInfo *CPlayerPool::GetPlayerInfo(uint16_t playerid)
{
	if(samp_version == SAMP_VERSION_037)
	{
		if(v037.m_created[playerid])
		{
			return v037.m_players[playerid];
		}
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		if(v037_r5.m_created[playerid])
		{
			return v037_r5.m_players[playerid];
		}
	}
	
	
	return NULL;
}

CRemotePlayer *CPlayerPool::GetRemotePlayer(uint16_t playerid)
{
	CPlayerInfo *playerinfo = GetPlayerInfo(playerid);
	
	if(playerinfo != NULL)
	{
		return playerinfo->GetRemotePlayer();
	}
	
	return NULL;
}

CPlayerPed *CPlayerPool::GetPlayerPed(uint16_t playerid)
{
	if(playerid == GetLocalPlayerId())
	{
		CLocalPlayer *localplayer = GetLocalPlayer();
		
		if(localplayer != NULL)
			return localplayer->GetPlayerPed();
	}
	else
	{
		CRemotePlayer *remoteplayer = GetRemotePlayer(playerid);
		
		if(remoteplayer != NULL)
			return remoteplayer->GetPlayerPed();
	}
	
	return NULL;
}

const char *CPlayerPool::GetPlayerName(uint16_t playerid)
{
	if(playerid == GetLocalPlayerId())
	{
		return GetLocalPlayerName();
	}
	else
	{
		CPlayerInfo *playerinfo = GetPlayerInfo(playerid);
		
		if(playerinfo != NULL)
		{
			return playerinfo->GetPlayerName();
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
