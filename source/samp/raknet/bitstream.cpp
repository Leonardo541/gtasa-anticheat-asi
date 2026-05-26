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

#include "../../main.h"

MEMBER_TYPEDEF(BitStream, void, Constructor_t, void *, uint32_t, bool);
MEMBER_TYPEDEF(BitStream, void, Destructor_t);
MEMBER_TYPEDEF(BitStream, bool, ReadBits_t, void *, int , bool);
MEMBER_TYPEDEF(BitStream, bool, Read_t, void *, int);
MEMBER_TYPEDEF(BitStream, bool, ReadNormQuat_t, float &, float &, float &, float &);
MEMBER_TYPEDEF(BitStream, bool, ReadVector_t, float &, float &, float &);

static Constructor_t pfnConstructor = NULL;
static Destructor_t pfnDestructor = NULL;
static ReadBits_t pfnReadBits = NULL;
static Read_t pfnRead = NULL;
static ReadNormQuat_t pfnReadNormQuat = NULL;
static ReadVector_t pfnReadVector = NULL;

void BitStream::ApplyHooks()
{
	POINTER_TO_MEMBER(pfnConstructor, samp_address + 0x0001F840);
	POINTER_TO_MEMBER(pfnDestructor, samp_address + 0x0001F8D0);
	POINTER_TO_MEMBER(pfnReadBits, samp_address + 0x0001F9B0);
	POINTER_TO_MEMBER(pfnRead, samp_address + 0x0001FEA0);
	POINTER_TO_MEMBER(pfnReadNormQuat, samp_address + 0x00009680);
	POINTER_TO_MEMBER(pfnReadVector, samp_address + 0x0000A3B0);
}

BitStream::BitStream(void *data, uint32_t bytes, bool copy_data)
{
	METHOD_CALL(this, pfnConstructor, data, bytes, copy_data);
}

BitStream::~BitStream()
{
	METHOD_CALL(this, pfnDestructor);
}

bool BitStream::ReadBits(void *output, int bits, bool right_aligned_bits)
{
	return METHOD_CALL(this, pfnReadBits, output, bits, right_aligned_bits);
}

bool BitStream::Read(void *output, int bytes)
{
	return METHOD_CALL(this, pfnRead, output, bytes);
}

bool BitStream::ReadNormQuat(float &w, float &x, float &y, float &z)
{
	return METHOD_CALL(this, pfnReadNormQuat, w, x, y, z);
}

bool BitStream::ReadVector(float &x, float &y, float &z)
{
	return METHOD_CALL(this, pfnReadVector, x, y, z);
}
