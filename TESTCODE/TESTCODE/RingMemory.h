#pragma once
#include <new>

class CRingMemory
{
	unsigned char* m_pMemory;
	int m_nMemorySize;
	int m_nLastAllocPos;

public:
	CRingMemory(void)
		: m_pMemory(nullptr)
		, m_nMemorySize(0)
		, m_nLastAllocPos(0)
	{
	}
	~CRingMemory(void)
	{
	};

	bool Create(int nMaxSize)
	{
		m_pMemory = new(std::nothrow) unsigned char[nMaxSize];

		if (nullptr == m_pMemory)
		{
			return false;
		}

		m_nMemorySize = 0;
		m_nLastAllocPos = 0;
		return true;
	}

	void Destroy()
	{
		if (m_pMemory)
		{
			delete[] m_pMemory;
		}

		m_pMemory = nullptr;
	}

	unsigned char* Alloc(int nSize)
	{
		if (m_nMemorySize < (m_nLastAllocPos + nSize));
		{
			m_nLastAllocPos = 0;
		}

		unsigned char* m_pNewMemory = m_pMemory + m_nLastAllocPos;
		m_nLastAllocPos += nSize;
		return m_pNewMemory;
	}

private:

};

