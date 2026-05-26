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

CJacked::CJacked(uint16_t playerid, const char *playername, uint16_t driverid, const char *drivername, float teleport_dist, float teleport_up_z, float health, float health_diff, const vector_t &old_position, float old_up_z, float old_health, uint32_t counter, time_t rawtime, bool show_alert) : CRefCount(), m_old_position(old_position)
{
	m_playerid = playerid;
	strcpy(m_playername, playername);
	m_driverid = driverid;
	strcpy(m_drivername, drivername);
	m_teleport_dist = teleport_dist;
	m_teleport_up_z = teleport_up_z;
	m_health = health;
	m_health_diff = health_diff;
	m_old_up_z = old_up_z;
	m_old_health = old_health;
	m_counter = counter;
	m_rawtime = rawtime;
	m_show_alert = show_alert;
	
	m_close_rect.left = 0;
	m_close_rect.top = 0;
	m_close_rect.right = 0;
	m_close_rect.bottom = 0;
}

void CJacked::Draw(CFontRender *fontrender, POINT position, time_t rawtime)
{
	static char text[256 + 1];
	
	time_t time_elapsed = rawtime - m_rawtime;
	
	float percent_health = ((m_health - 250.0f) * 100.0f) / 1000.0f;
	float percent_health_diff = (m_health_diff * 100.0f) / 1000.0f;
	
	RECT rect;
	
	rect.left = position.x;
	rect.top = position.y;
	rect.right = rect.left - 4;
	rect.bottom = rect.top + JACKED_HEIGHT;
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_PLAYERNAME_WIDTH;
	
	snprintf(text, 256, "[%u] %s", m_playerid, m_playername);
	fontrender->DrawText(text, &rect, DT_NOCLIP | DT_LEFT | DT_VCENTER, 0xFFFFFFFF, true, true);
	
	if(config.GetPtr()->GetJackedShowAll())
	{
		rect.left = rect.right + 4;
		rect.right = rect.left + JACKED_DRIVERNAME_WIDTH;
		
		snprintf(text, 256, "[%u] %s", m_driverid, m_drivername);
		fontrender->DrawText(text, &rect, DT_NOCLIP | DT_LEFT | DT_VCENTER, 0xFFFFFFFF, true, true);
	}
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_TELEPORT_DIST_WIDTH;
	
	if(m_teleport_dist < 10.0f)
	{
		snprintf(text, 256, "%.1f", m_teleport_dist);
		fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	}
	else
	{
		snprintf(text, 256, "%.0f", m_teleport_dist);
		fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	}
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_TELEPORT_UP_Z_WIDTH;
	
	snprintf(text, 256, "%.1f", m_teleport_up_z);
	fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
		
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_HEALTH_WIDTH;
	
	snprintf(text, 256, "%.0f%%", percent_health);
	fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_HEALTH_DIFF_WIDTH;
	
	snprintf(text, 256, "%.0f%%", percent_health_diff);
	fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_COUNTER_WIDTH;
	
	snprintf(text, 256, "%u", m_counter);
	fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	
	rect.left = rect.right + 4;
	rect.right = rect.left + JACKED_TIME_ELAPSED_WIDTH;
	
	m_close_rect = rect;
	
	if(IsMouseInCloseRect())
	{
		DRAW_TEXTURE(close_texture, JACKED_TEXTURE_WIDTH);
	}
	else
	{
		snprintf(text, 256, "%ld", time_elapsed);
		fontrender->DrawText(text, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, 0xFFFFFFFF, true, true);
	}
	
	if(m_show_alert && (rawtime % 2) == 1)
	{
		if(config.GetPtr()->GetJackedPosition().x < 0)
		{
			rect.left = position.x - 4 - JACKED_TIME_ELAPSED_WIDTH;
			rect.right = rect.left + JACKED_TIME_ELAPSED_WIDTH;
		}
		else
		{
			rect.left = rect.right + 4;
			rect.right = rect.left + JACKED_TIME_ELAPSED_WIDTH;
		}
		
		DRAW_TEXTURE(alert_texture, JACKED_TEXTURE_WIDTH);
	}
}

bool CJacked::IsMouseInCloseRect()
{
	return m_close_rect.left <= mouse_position.x && mouse_position.x < m_close_rect.right && m_close_rect.top <= mouse_position.y && mouse_position.y < m_close_rect.bottom;
}
