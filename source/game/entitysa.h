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

#define	VEHICLE_SUBTYPE_CAR				1
#define	VEHICLE_SUBTYPE_BIKE			2
#define	VEHICLE_SUBTYPE_HELI			3
#define	VEHICLE_SUBTYPE_BOAT			4
#define	VEHICLE_SUBTYPE_PLANE			5
#define	VEHICLE_SUBTYPE_PUSHBIKE		6
#define	VEHICLE_SUBTYPE_TRAIN			7

#pragma pack(push, 1)
class CEntitySA
{
	public:
		MEMBER_BEGIN()
			// CEntitySA
			MEMBER_VARIABLE(0x4,	vector_noctor_t	m_pos)
			MEMBER_VARIABLE(0x10,	float			m_angle)
			MEMBER_VARIABLE(0x14,	RwMatrix *		m_matrix)
			MEMBER_VARIABLE(0x22,	uint16_t		m_modelid)
			
			MEMBER_VARIABLE(0x36,	uint8_t			m_type : 3;
									uint8_t			m_status : 5)
			
			MEMBER_VARIABLE(0xDC,	CEntitySA *		m_collidedentity)
			MEMBER_VARIABLE(0xE0,	vector_noctor_t	m_collisionvelocity)
			MEMBER_VARIABLE(0xEC,	vector_noctor_t	m_collisionposition)
			
			// CVehicleSA
			MEMBER_VARIABLE(0x460,	CEntitySA *		m_driver)
			MEMBER_VARIABLE(0x4C0,	float			m_vehicle_health)
			
			// CPadSA
			MEMBER_VARIABLE(0x540,	float			m_player_health)
			MEMBER_VARIABLE(0x568,	CEntitySA *		m_contactvehicle)
			MEMBER_VARIABLE(0x584,	CEntitySA *		m_contactentity)
			MEMBER_VARIABLE(0x58C,	CEntitySA *		m_vehicle)
			MEMBER_VARIABLE(0x960,	uint8_t			m_contact_wheels)
		MEMBER_END()
	
	public:
		uint32_t GetVehicleSubtype();
};
#pragma pack(pop)
