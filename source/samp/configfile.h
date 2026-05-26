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
class CConfigFile
{
	public:
		static void ApplyHooks();
		
		bool Exists(const char *key);
		
		int GetInt(const char *key);
		const char *GetString(const char *key);
		float GetFloat(const char *key);
		bool GetBoolean(const char *key);
		POINT GetPoint(const char *key);
		
		int SetInt(const char *key, int value);
		int SetString(const char *key, const char *value);
		int SetFloat(const char *key, float value);
		int SetBoolean(const char *key, bool value);
		int SetPoint(const char *key, const POINT &value);
		
		void GetOrCreateInt(const char *key, int *value);
		void GetOrCreateString(const char *key, const char **value);
		void GetOrCreateFloat(const char *key, float *value);
		void GetOrCreateBoolean(const char *key, bool *value);
		void GetOrCreatePoint(const char *key, POINT *point);
};
#pragma pack(pop)
