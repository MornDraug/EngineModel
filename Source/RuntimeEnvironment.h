#pragma once

#ifndef RUNTIMEENVIRONMENT_H
#define RUNTIMEENVIRONMENT_H

#include "Engine.h"

// ����� �������� ������ ���������.
class RuntimeEnvironment : private std::enable_shared_from_this<RuntimeEnvironment>
{
public:
	float step = 1; // ��� �� ������� � ��������.
	float maxTime = std::numeric_limits<float>::max(); // �����, ��� ������� �������� ������������� ��������.

	std::shared_ptr<Engine> engine;

private:
	float mTime = 0; // ������� ����� ������.

public:
	inline RuntimeEnvironment();
	inline virtual ~RuntimeEnvironment();

	inline float time() const;

	bool simulate();
	void reset();

	void nextStep();

private:
	void nextStep(int);
};

inline RuntimeEnvironment::RuntimeEnvironment()
{
}

inline RuntimeEnvironment::~RuntimeEnvironment()
{
}

inline float RuntimeEnvironment::time() const
{ return this->mTime; }

#endif // RUNTIMEENVIRONMENT_H
