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

#include "../../main.h"

#define BITSTREAM_STACK_ALLOCATION_SIZE 256

class BitStream
{
	private:
		int					m_bits_used;
		int					m_bits_allocated;
		int					m_read_offset;
		uint8_t *			m_data;
		bool				m_copy_data;
		uint8_t				m_stack_data[BITSTREAM_STACK_ALLOCATION_SIZE];
	
	public:
		static void ApplyHooks();
		
		BitStream(void *data, uint32_t bytes, bool copy_data);
		~BitStream();
		
		bool ReadBits(void *output, int bits, bool right_aligned_bits = true);
		bool Read(void *output, int bytes);
		bool ReadNormQuat(float &w, float &x, float &y, float &z);
		bool ReadVector(float &x, float &y, float &z);
		
		template <class T> inline void Read(T &var) { ReadBits(&var, sizeof(T) * 8); }
		
		inline int GetNumberOfBitsUsed() const { return m_bits_used; }
};
