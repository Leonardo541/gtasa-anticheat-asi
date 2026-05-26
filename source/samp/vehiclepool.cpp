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

CVehicle *CVehiclePool::GetVehicle(uint16_t vehicleid)
{
	if(m_created[vehicleid])
		return m_vehicles[vehicleid];
	
	return NULL;
}

uint16_t CVehiclePool::GetLocalVehicleId()
{
	static uint16_t last_localvehicleid = 0xFFFF;
	
	CEntitySA *vehicle_entity = *(CEntitySA **)0x00BA18FC;
	
	if(vehicle_entity != NULL)
	{
		if(last_localvehicleid != 0xFFFF)
		{
			uint16_t i = last_localvehicleid;
			
			if(m_created[i] && m_vehicles[i] != NULL)
			{
				if(m_vehicles[i]->m_entity == vehicle_entity)
					return i;
			}
			
			last_localvehicleid = 0xFFFF;
		}
		
		for(uint16_t i = 0; i < 2000; i++)
		{
			if(m_created[i] && m_vehicles[i] != NULL)
			{
				if(m_vehicles[i]->m_entity == vehicle_entity)
				{
					last_localvehicleid = i;
					return i;
				}
			}
		}
	}
	
	return 0xFFFF;
}
