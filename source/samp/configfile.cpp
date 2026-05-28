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

MEMBER_TYPEDEF(CConfigFile, bool, Exists_t, const char *);
MEMBER_TYPEDEF(CConfigFile, int, GetInt_t, const char *);
MEMBER_TYPEDEF(CConfigFile, const char *, GetString_t, const char *);
MEMBER_TYPEDEF(CConfigFile, float, GetFloat_t, const char *);
MEMBER_TYPEDEF(CConfigFile, int, SetInt_t, const char *, int, int);
MEMBER_TYPEDEF(CConfigFile, int, SetString_t, const char *, const char *, int);
MEMBER_TYPEDEF(CConfigFile, int, SetFloat_t, const char *, float, int);

static Exists_t pfnExists = NULL;
static GetInt_t pfnGetInt = NULL;
static GetString_t pfnGetString = NULL;
static GetFloat_t pfnGetFloat = NULL;
static SetInt_t pfnSetInt = NULL;
static SetString_t pfnSetString = NULL;
static SetFloat_t pfnSetFloat = NULL;

void CConfigFile::ApplyHooks()
{
	if(samp_version == SAMP_VERSION_037)
	{
		POINTER_TO_MEMBER(pfnExists, samp_address + 0x00062170);
		POINTER_TO_MEMBER(pfnGetInt, samp_address + 0x00062250);
		POINTER_TO_MEMBER(pfnGetString, samp_address + 0x00062280);
		POINTER_TO_MEMBER(pfnGetFloat, samp_address + 0x000622B0);
		POINTER_TO_MEMBER(pfnSetInt, samp_address + 0x000624C0);
		POINTER_TO_MEMBER(pfnSetString, samp_address + 0x00062520);
		POINTER_TO_MEMBER(pfnSetFloat, samp_address + 0x000625C0);
	}
	else if(samp_version == SAMP_VERSION_037_R5)
	{
		POINTER_TO_MEMBER(pfnExists, samp_address + 0x00065D30);
		POINTER_TO_MEMBER(pfnGetInt, samp_address + 0x00065E10);
		POINTER_TO_MEMBER(pfnGetString, samp_address + 0x00065E40);
		POINTER_TO_MEMBER(pfnGetFloat, samp_address + 0x00065E70);
		POINTER_TO_MEMBER(pfnSetInt, samp_address + 0x00066080);
		POINTER_TO_MEMBER(pfnSetString, samp_address + 0x000660E0);
		POINTER_TO_MEMBER(pfnSetFloat, samp_address + 0x00066180);
	}
}

bool CConfigFile::Exists(const char *key)
{
	return METHOD_CALL(this, pfnExists, key);
}

int CConfigFile::GetInt(const char *key)
{
	return METHOD_CALL(this, pfnGetInt, key);
}

const char *CConfigFile::GetString(const char *key)
{
	return METHOD_CALL(this, pfnGetString, key);
}

float CConfigFile::GetFloat(const char *key)
{
	return METHOD_CALL(this, pfnGetFloat, key);
}

bool CConfigFile::GetBoolean(const char *key)
{
	return METHOD_CALL(this, pfnGetInt, key) != 0;
}

POINT CConfigFile::GetPoint(const char *key)
{
	POINT pt;
	const char *str = METHOD_CALL(this, pfnGetString, key);
	
	if(str != NULL)
	{
		if(sscanf(str, "%ldx%ld", &pt.x, &pt.y) == 2)
			return pt;
	}
	
	pt.x = 0;
	pt.y = 0;
	
	return pt;
}

int CConfigFile::SetInt(const char *key, int value)
{
	return METHOD_CALL(this, pfnSetInt, key, value, 0);
}

int CConfigFile::SetString(const char *key, const char *value)
{
	return METHOD_CALL(this, pfnSetString, key, value, 0);
}

int CConfigFile::SetFloat(const char *key, float value)
{
	return METHOD_CALL(this, pfnSetFloat, key, value, 0);
}

int CConfigFile::SetBoolean(const char *key, bool value)
{
	return METHOD_CALL(this, pfnSetInt, key, value ? 1 : 0, 0);
}

int CConfigFile::SetPoint(const char *key, const POINT &value)
{
	static char str[48 + 1];
	snprintf(str, 48, "%ldx%ld", value.x, value.y);
	return METHOD_CALL(this, pfnSetString, key, str, 0);
}

void CConfigFile::GetOrCreateInt(const char *key, int *value)
{
	if(Exists(key))
	{
		*value = GetInt(key);
	}
	else
	{
		SetInt(key, *value);
	}
}

void CConfigFile::GetOrCreateString(const char *key, const char **value)
{
	if(Exists(key))
	{
		*value = GetString(key);
	}
	else
	{
		SetString(key, *value);
	}
}

void CConfigFile::GetOrCreateFloat(const char *key, float *value)
{
	if(Exists(key))
	{
		*value = GetFloat(key);
	}
	else
	{
		SetFloat(key, *value);
	}
}

void CConfigFile::GetOrCreateBoolean(const char *key, bool *value)
{
	if(Exists(key))
	{
		*value = GetBoolean(key);
	}
	else
	{
		SetBoolean(key, *value);
	}
}

void CConfigFile::GetOrCreatePoint(const char *key, POINT *point)
{
	if(Exists(key))
	{
		*point = GetPoint(key);
	}
	else
	{
		SetPoint(key, *point);
	}
}
