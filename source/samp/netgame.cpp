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

MEMBER_TYPEDEF(CNetGame, void, Packet_VehicleSync_t, Packet *);

static Packet_VehicleSync_t pfnPacket_VehicleSync = NULL;

void CNetGame::ApplyHooks()
{
	MEMBER_CALL(samp_address + 0x0000B2B6, CNetGame, Packet_VehicleSync);
}

void CNetGame::Packet_VehicleSync(Packet *packet)
{
	int max_rows = config.GetPtr()->GetJackedMaxRows();
	
	if(max_rows > 0)
	{
		BitStream bs(packet->data, packet->length, false);
		
		uint8_t packet_id;
		uint32_t timestamp;
		uint16_t playerid;
		uint16_t vehicleid;
		int16_t keys_leftright;
		int16_t keys_updown;
		uint16_t keys;
		float quaternion[4];
		vector_t position;
		vector_t velocity;
		int16_t health;
		
		if(*packet->data == 40) // ID_TIMESTAMP
		{
			bs.Read(packet_id);
			bs.Read(timestamp);
		}
		
		bs.Read(packet_id);
		bs.Read(playerid);
		bs.Read(vehicleid);
		bs.Read(keys_leftright);
		bs.Read(keys_updown);
		bs.Read(keys);
		bs.ReadNormQuat(quaternion[0], quaternion[1], quaternion[2], quaternion[3]);
		bs.Read(&position, sizeof(vector_t));
		bs.ReadVector(velocity.x, velocity.y, velocity.z);
		bs.Read(health);
		
		if(playerid < 1004 && vehicleid < 2000)
		{
			if(m_pools != NULL)
			{
				CPlayerPool *playerpool = m_pools->m_playerpool;
				CVehiclePool *vehiclepool = m_pools->m_vehiclepool;
				
				if(playerpool != NULL && vehiclepool != NULL)
				{
					CPlayerPed *playerped = playerpool->GetPlayerPed(playerid);
					CVehicle *vehicle = vehiclepool->GetVehicle(vehicleid);
					
					if(playerped != NULL && vehicle != NULL)
					{
						if(playerped->m_entity != NULL && vehicle->m_entity != NULL)
						{
							if(vehicle->m_entity->m_driver != NULL && vehicle->m_entity->m_driver != playerped->m_entity)
							{
								uint16_t driverid = playerpool->GetPlayerIdFromEntity(vehicle->m_entity->m_driver);
								
								if(config.GetPtr()->GetJackedShowAll() || driverid == playerpool->m_localplayerid)
								{
									time_t rawtime;
									time(&rawtime);
									
									const char *playername = playerpool->GetPlayerName(playerid);
									
									if(playername == NULL)
										playername = "(null)";
									
									const char *drivername = playerpool->GetPlayerName(driverid);
									
									if(drivername == NULL)
										drivername = "(null)";
									
									vector_t old_position;
									float old_up_z;
									float old_health = vehicle->m_entity->m_vehicle_health;
									
									if(vehicle->m_entity->m_matrix != NULL)
									{
										old_position = vehicle->m_entity->m_matrix->pos;
										old_up_z = vehicle->m_entity->m_matrix->up.z;
									}
									else
									{
										old_position = vehicle->m_entity->m_pos;
										old_up_z = 1.0f;
									}
									
									float teleport_dist = old_position.DistanceToPoint(position);
									float teleport_up_z = quaternion[3] * quaternion[3] - (quaternion[2] * quaternion[2] + quaternion[1] * quaternion[1]) + quaternion[0] * quaternion[0];
									
									float vehicle_health = (float)health;
									
									uint32_t counter = 1;
									
									bool show_alert = false;
									
									for(std::vector<CRefPtr<CJacked>>::iterator it = jacked_list.begin(); it != jacked_list.end(); it++)
									{
										CRefPtr<CJacked> jacked = *it;
										
										if(jacked.GetPtr()->GetPlayerId() == playerid && jacked.GetPtr()->GetDriverId() == driverid)
										{
											if(jacked.GetPtr()->GetShowAlert())
												show_alert = true;
											
											time_t time_elapsed = rawtime - jacked.GetPtr()->GetRawtime();
											
											if(time_elapsed <= 2)
											{
												old_position = jacked.GetPtr()->GetOldPosition();
												old_up_z = jacked.GetPtr()->GetOldUpZ();
												old_health = jacked.GetPtr()->GetOldHealth();
												
												teleport_dist = old_position.DistanceToPoint(position);
												
												if(teleport_dist < jacked.GetPtr()->GetTeleportDist())
													teleport_dist = jacked.GetPtr()->GetTeleportDist();
												
												if(teleport_up_z > jacked.GetPtr()->GetTeleportUpZ())
													teleport_up_z = jacked.GetPtr()->GetTeleportUpZ();
												
												if(vehicle_health > jacked.GetPtr()->GetHealth())
													vehicle_health = jacked.GetPtr()->GetHealth();
												
												counter = jacked.GetPtr()->GetCounter() + 1;
												
												jacked_list.erase(it);
												break;
											}
										}
									}
									
									if(teleport_dist > 25.0)
										show_alert = true;
									
									if(teleport_up_z <= 0.0f && old_up_z > 0.0f)
										show_alert = true;
									
									if(vehicle_health <= 250.0f && old_health > 250.0f)
										show_alert = true;
									
									CRefPtr<CJacked> jacked = new CJacked(playerid, playername, driverid, drivername, teleport_dist, teleport_up_z, vehicle_health, (float)vehicle_health - old_health, old_position, old_up_z, old_health, counter, rawtime, show_alert);
									
									jacked_list.push_back(jacked);
									
									if(jacked_list.size() > (uint32_t)max_rows)
										jacked_list.erase(jacked_list.begin());
									
									if(show_alert && driverid == playerpool->m_localplayerid)
										return;
								}
							}
						}
					}
				}
			}
		}
	}
	
	METHOD_CALL(this, pfnPacket_VehicleSync, packet);
}
