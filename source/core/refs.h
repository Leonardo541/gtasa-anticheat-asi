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

class CRefCount
{
	private:
		uint32_t		m_refs;
	
	public:
		CRefCount();
		
		inline void AddRef() { m_refs++; }
		inline void RemoveRef() { m_refs--; }
		
		inline uint32_t GetRefs() const { return m_refs; }
};

template <class T> class CRefPtr
{
	private:
		T *				m_ptr;
	
	public:
		CRefPtr()
		{
			m_ptr = NULL;
		};
		
		CRefPtr(T *ptr)
		{
			m_ptr = ptr;
			AddRef();
		};
		
		CRefPtr(const CRefPtr<T> &ref_ptr)
		{
			m_ptr = ref_ptr.GetPtr();
			AddRef();
		};
		
		~CRefPtr()
		{
			RemoveRef();
		};
		
		void AddRef()
		{
			if(m_ptr != NULL)
			{
				m_ptr->AddRef();
			}
		}
		
		void RemoveRef()
		{
			if(m_ptr != NULL)
			{
				m_ptr->RemoveRef();
				
				if(m_ptr->GetRefs() == 0)
					delete m_ptr;
			}
		}
		
		CRefPtr<T> &operator = (T *ptr)
		{
			RemoveRef();
			m_ptr = ptr;
			AddRef();
			
			return *this;
		}
		
		CRefPtr<T> &operator = (const CRefPtr<T> &ref_ptr)
		{
			RemoveRef();
			m_ptr = ref_ptr.GetPtr();
			AddRef();
			
			return *this;
		}
		
		inline T *GetPtr() const { return m_ptr; }
};
