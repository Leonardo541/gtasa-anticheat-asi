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

uint32_t CEntitySA::GetVehicleSubtype()
{
	if(*(uint32_t *)this == 0x00871120)
	{
		return VEHICLE_SUBTYPE_CAR;
	}
	else if(*(uint32_t *)this == 0x008721A0)
	{
		return VEHICLE_SUBTYPE_BOAT;
	}
	else if(*(uint32_t *)this == 0x00871360)
	{
		return VEHICLE_SUBTYPE_BIKE;
	}
	else if(*(uint32_t *)this == 0x00871948)
	{
		return VEHICLE_SUBTYPE_PLANE;
	}
	else if(*(uint32_t *)this == 0x00871680)
	{
		return VEHICLE_SUBTYPE_HELI;
	}
	else if(*(uint32_t *)this == 0x00871528)
	{
		return VEHICLE_SUBTYPE_PUSHBIKE;
	}
	else if(*(uint32_t *)this == 0x00872370)
	{
		return VEHICLE_SUBTYPE_TRAIN;
	}
	
	return 0;
}
