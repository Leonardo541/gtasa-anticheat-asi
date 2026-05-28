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

#define SAMP_VERSION_037				1
#define SAMP_VERSION_037_R5				2

#define WIDTH							(*(int *)0x00C17044)
#define HEIGHT							(*(int *)0x00C17048)

#define POINTER_TO_MEMBER(m, n)			*(uint32_t *)&m = n
#define MEMBER_TYPEDEF(c, t, m, ...)	typedef t (c::*m)(__VA_ARGS__)
#define MEMBER_CALL(a, c, f)			{ f##_t pfn = (f##_t)&c::f; Call(a, *(uint32_t *)&pfn, (uint32_t *)&pfn##f); }
#define METHOD_CALL(m, n ,...)			(m->*n)(__VA_ARGS__)

#define MEMBER_BEGIN()					union {
#define MEMBER_VARIABLE_OFFZERO(v)		struct { v; };
#define MEMBER_VARIABLE(o, v)			struct { uint8_t m_padding##o[o]; v; };
#define MEMBER_END(...)					} __VA_ARGS__;

#if __cplusplus >= 201103L
	#define NO_COPY_OBJECT(t)					\
		public:									\
			t(const t &o) = delete;				\
			t &operator = (const t &o) = delete
#else
	#define NO_COPY_OBJECT(t)					\
		private:								\
			t(const t &o);						\
			t &operator = (const t &o)
#endif

#if defined _MSC_VER && _MSC_VER <= 1800
	#define snprintf _snprintf
#endif

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <vector>

#include <d3dx9core.h>

// core
#include "core/crc32.h"
#include "core/refs.h"
#include "core/textures.h"
#include "core/vector.h"

// game
#include "game/matrix.h"
#include "game/entitysa.h"

// raknet
#include "samp/raknet/networktypes.h"
#include "samp/raknet/bitstream.h"

// samp
#include "samp/configfile.h"
#include "samp/fontrender.h"
#include "samp/cmdwindow.h"
#include "samp/playerped.h"
#include "samp/localplayer.h"
#include "samp/remoteplayer.h"
#include "samp/playerinfo.h"
#include "samp/vehicle.h"
#include "samp/playerpool.h"
#include "samp/vehiclepool.h"
#include "samp/pools.h"
#include "samp/netgame.h"

#include "config.h"
#include "jacked.h"

extern uint32_t samp_address;
extern uint32_t samp_version;

extern CRefPtr<CConfig> config;

extern std::vector<CRefPtr<CJacked>> jacked_list;

extern POINTS mouse_position;

extern POINT text_size_pname;
extern POINT text_size_4chrs;
extern POINT text_size_2chrs;

extern bool calc_text_size;

void Call(uint32_t address, uint32_t function, uint32_t *old);

CConfigFile *GetConfigFile();
CFontRender *GetFontRender();
