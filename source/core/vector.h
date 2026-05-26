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
typedef struct vector_t
{
	union
	{
		struct
		{
			float x, y, z;
		};

		float v[3];
	};

	vector_t()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	vector_t(const vector_t &v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	vector_t(float x, float y, float z) 
	{ 
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float DistanceToPoint(float x, float y, float z) const
	{
		return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2) + pow(this->z - z, 2));
	}

	float DistanceToPoint(vector_t point) const
	{
		return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2) + pow(this->z - point.z, 2));
	}
} vector_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct vector_noctor_t
{
	union
	{
		struct
		{
			float x, y, z;
		};

		float v[3];
	};
	
	inline operator const vector_t () const { return vector_t(this->x, this->y, this->z); }
} vector_noctor_t;
#pragma pack(pop)
