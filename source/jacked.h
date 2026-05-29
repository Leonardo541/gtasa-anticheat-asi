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

#include "main.h"

#define JACKED_PLAYERNAME_WIDTH		(text_size_pname.x)
#define JACKED_DRIVERNAME_WIDTH		(text_size_pname.x)
#define JACKED_TELEPORT_DIST_WIDTH	(text_size_4chrs.x)
#define JACKED_TELEPORT_UP_Z_WIDTH	(text_size_4chrs.x)
#define JACKED_HEALTH_WIDTH			(text_size_4chrs.x)
#define JACKED_HEALTH_DIFF_WIDTH	(text_size_4chrs.x)
#define JACKED_COUNTER_WIDTH		(text_size_4chrs.x)
#define JACKED_TIME_ELAPSED_WIDTH	(config.GetPtr()->GetJackedMaxTime() <= 99 ? text_size_2chrs.x : text_size_4chrs.x)
#define JACKED_TEXTURE_WIDTH		(text_size_2chrs.y)

#define JACKED_WIDTH				(JACKED_PLAYERNAME_WIDTH                               + 4 + JACKED_TELEPORT_DIST_WIDTH + 4 + JACKED_TELEPORT_UP_Z_WIDTH + 4 + JACKED_HEALTH_WIDTH + 4 + JACKED_HEALTH_DIFF_WIDTH + 4 + JACKED_COUNTER_WIDTH + JACKED_TIME_ELAPSED_WIDTH)
#define JACKED_ALL_WIDTH			(JACKED_PLAYERNAME_WIDTH + 4 + JACKED_DRIVERNAME_WIDTH + 4 + JACKED_TELEPORT_DIST_WIDTH + 4 + JACKED_TELEPORT_UP_Z_WIDTH + 4 + JACKED_HEALTH_WIDTH + 4 + JACKED_HEALTH_DIFF_WIDTH + 4 + JACKED_COUNTER_WIDTH + JACKED_TIME_ELAPSED_WIDTH)

#define JACKED_HEIGHT				(text_size_2chrs.y)

class CJacked : public CRefCount
{
	NO_COPY_OBJECT(CJacked);
	
	private:
		uint16_t		m_playerid;
		char			m_playername[24 + 1];
		uint16_t		m_driverid;
		char			m_drivername[24 + 1];
		float			m_teleport_dist;
		float			m_teleport_up_z;
		float			m_health;
		float			m_health_diff;
		vector_t		m_old_position;
		float			m_old_up_z;
		float			m_old_health;
		uint32_t		m_counter;
		time_t			m_rawtime;
		bool			m_show_alert;
		
		RECT			m_close_rect;
	
	public:
		CJacked(uint16_t playerid, const char *playername, uint16_t driverid, const char *drivername, float teleport_dist, float teleport_up_z, float health, float health_diff, const vector_t &old_position, float old_up_z, float old_health, uint32_t counter, time_t rawtime, bool show_alert);
		
		void Draw(CFontRender *fontrender, POINT position, time_t rawtime);
		
		bool IsMouseInCloseRect();
		
		inline uint16_t GetPlayerId() { return m_playerid; }
		inline const char *GetPlayerName() { return m_playername; }
		inline uint16_t GetDriverId() { return m_driverid; }
		inline const char *GetDriverName() { return m_drivername; }
		inline float GetTeleportDist() { return m_teleport_dist; }
		inline float GetTeleportUpZ() { return m_teleport_up_z; }
		inline float GetHealth() { return m_health; }
		inline float GetHealthDiff() { return m_health_diff; }
		inline vector_t GetOldPosition() { return m_old_position; }
		inline float GetOldUpZ() { return m_old_up_z; }
		inline float GetOldHealth() { return m_old_health; }
		inline uint32_t GetCounter() { return m_counter; }
		inline time_t GetRawtime() { return m_rawtime; }
		inline bool GetShowAlert() { return m_show_alert; }
};
