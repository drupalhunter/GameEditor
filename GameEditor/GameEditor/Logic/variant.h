/********************************************************************
	Copyright (c) 2014-2014 uloveto.com

	http://www.uloveto.com
	
	created:	2014/09/05
	created:	5:9:2014   10:43
	filename: 	variant
	file ext:	h
	author:		zero
	
	purpose:	
*********************************************************************/

#ifndef __variant_h__
#define __variant_h__

#include <stddef.h>
#include <map>

class KSimpleBuffer 
{
public:
	void Init()
	{
		m_nBufferSize = 0;
		m_pBuffer = NULL;
	};

	unsigned int InitBufferSize(int nBufferSize)
	{
		m_nBufferSize = nBufferSize;
		m_pBuffer = new char[nBufferSize];

		return 1;
	};

	void CopyString(const char* szString, int nStrLen = 0)
	{
		Uninit();

		if (nStrLen <= 0)
		{
			nStrLen = (int)strlen(szString);
		}
		
		int nBufferSize = nStrLen + 1;
		if (nBufferSize > 0 && InitBufferSize(nBufferSize)) // δ���ڴ��ж�
		{
			memcpy(m_pBuffer, szString, nBufferSize);
			m_pBuffer[nBufferSize] = 0;
		}
	}

	char* GetBuffer()
	{
		return m_pBuffer;
	};

	void Uninit()
	{
		if (m_pBuffer)
		{
			delete []m_pBuffer;

			m_pBuffer = NULL;
			m_nBufferSize = 0;
		}
	};

private:
	char*			m_pBuffer;
	size_t			m_nBufferSize;
};

class KListNode
{
public:
	KListNode()
	{
		m_pNext = NULL;
		m_pPrev = NULL;

		m_pContainer = NULL;
	};

	virtual ~KListNode()
	{};

	void AddTail(KListNode* pTailNode)
	{
		KListNode* pNode = m_pContainer;
		KListNode* pPrev = NULL;

		while (pNode != NULL)
		{
			pPrev = pNode;
			pNode = pNode->m_pNext;
		}

		pNode = pTailNode;
		pTailNode->m_pPrev = pPrev;
		pTailNode->m_pNext = NULL;
	}

	KListNode* GetNext()
	{
		return m_pNext;
	}

protected:
	KListNode* m_pNext;
	KListNode* m_pPrev;

	KListNode* m_pContainer;
};

class KTreeNode
{
protected:
	KTreeNode* m_pParent;
	std::map<const char*, KTreeNode*> m_pChildren;
};

class KVariant : public KListNode, public KTreeNode
{
public:
	enum eVARIANT_TYPE
	{
		eVT_NUMBER,
		eVT_STRING,
		eVT_LONG_NUMBER,
		eVT_FLOAT,
		eVT_BOOL,
	};

	enum eSUB_TYPE
	{
		eST_VALUE = 0x01,
		eST_TREE = 0x02,
		eST_LIST = 0x04,
		eST_ALL = 0x07,
	};

	KVariant();
	virtual ~KVariant();
	KVariant* operator[](int nIndex);
	KVariant* operator[](const char* szIndex);


	/************************************************************************/
	/* Set & Get                                                            */
	/************************************************************************/
	void SetNumber(int number);
	int GetNumber();

	void SetLongNumber(long long number);
	long long GetLongNumber();

	void SetFloat(float fNumber);
	float GetFloat();

	void SetBool(bool bValue);
	bool GetBool();

	void SetString(const char* szContent, int nSize = 0);
	char* GetString();

	/************************************************************************/
	/* add                                                                     */
	/************************************************************************/
	void AddNumber(int number);
	void AddLongNumber(long long number);
	void AddBool(bool bValue);
	void AddFloat(float fValue);
	void AddString(const char* szContent, int nSize = 0);

	/************************************************************************/
	/* to                                                                     */
	/************************************************************************/
	int ToNumber();
	long long ToLongNumber();
	float ToFloat();
	bool ToBool();
	const char* ToString();

protected:
private:
	// Content
	union 
	{
		int				m_nNumber;
		long long		m_llNumber;		// Ϊʲô�� long long�������� long
		float			m_fNumber;		
		bool			m_bValue;
		KSimpleBuffer	m_Content;
	};

	// Index Conten
	union
	{
		int				m_nIndexNumer;
		KSimpleBuffer	m_IndexContent;
	};

	unsigned short				m_uType;
	//unsigned short				m_uStatus;

}; 

#endif // __variant_h__