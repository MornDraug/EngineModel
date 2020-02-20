#pragma once

#ifndef ENGINE_H
#define ENGINE_H

// ����� ����� ��� ����������.
class Engine
{
public:
	const float Tmax = 0; // ����������� ��������� ���������, C�.
	const float Tenv = 0; // ������� ����������� ���������� �����, C�.

protected:
	float Tcur = 0; // ������� ����������� ���������, C�.
	float Vcur = 0; // ������� �������� ���������, ���/�.

public:
	inline Engine(float Tmax, float Tenv);
	inline virtual ~Engine();

	inline float temperature() const;
	inline float velocity() const;

	inline bool isOverheated() const;

	inline virtual void update(float dt) = 0;
	inline virtual void reset();
};

inline Engine::Engine(float Tmax, float Tenv)
	: Tmax(Tmax), Tenv(Tenv), Tcur(Tenv)
{
}

inline Engine::~Engine()
{
}

inline float Engine::temperature() const
{ return this->Tcur; }

inline float Engine::velocity() const
{ return this->Vcur; }

inline bool Engine::isOverheated() const
{ return this->Tcur >= this->Tmax; }

inline void Engine::reset()
{
	this->Tcur = this->Tenv;
	this->Vcur = 0;
}

#endif // ENGINE_H
