#pragma once
#include <functional>
#include "Mecro.h"
#include <time.h>

template<typename Type>
class Timer
{
protected:
	int m_iOldTime; // �����ð�
	int m_iSecond; // ���ؽð�
	std::function<Type()> m_callbackFunc;

public:
	Timer() {}
	~Timer() {}

	// Ÿ�̸Ӱ� ����
	void SetTimer(int iSecond, std::function<Type()> _callbackFunc)
	{
		m_iSecond = iSecond;
		m_iOldTime = clock();
		m_callbackFunc = _callbackFunc;
	}

	Type CheckTimer() // Ÿ�̸� ���
	{
		Type Result{};
		if (clock() - m_iOldTime >= m_iSecond)
		{
			Result = m_callbackFunc();
			m_iOldTime = clock();
			return Result;
		}

		return Result;
	}

	void ChangeSecond(int iSecond)
	{
		m_iSecond = iSecond;
	}
	int GetSecond() { return m_iSecond; }

};

