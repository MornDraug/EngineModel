#pragma once

#ifndef ICENGINE_H
#define ICENGINE_H

#include "Engine.h"

// ��������� ����������� �������� (Internal combustion engine).
class ICEngine : public Engine
{
public:
	struct Parameters
	{
		std::vector<float> M; // �������� ������, �*�.
		std::vector<float> V; // �������� �������� ���������, ���/�.

		float I  = 0; // ������ ������� ���������, ��*�2.
		float Km = 0; // ����������� ����������� �������� ������� �� ��������� �������.
		float Kv = 0; // ����������� ����������� �������� ������� �� �������� �������� ���������.
		float C  = 0; // ����������� ����������� �������� ���������� �� ����������� ��������� � ���������� �����.
	};

public:
	const Parameters pars;

public:
	inline ICEngine(const Parameters pars, float Tmax, float Tenv);
	inline virtual ~ICEngine();

	float torque() const;
	inline float acceleration() const;

	inline float heatingRate() const;
	inline float coolingRate() const;

	void update(float dt) override;
};

inline ICEngine::ICEngine(const Parameters pars, float Tmax, float Tenv)
	: Engine(Tmax, Tenv), pars(pars)
{
	if (pars.M.size() <= 0)
		throw std::invalid_argument("������� M � V �� ����� ���� �������");

	if (pars.M.size() != pars.V.size())
		throw std::invalid_argument("������� M � V ������ ����� ���������� ������");
}

inline ICEngine::~ICEngine()
{
}

inline float ICEngine::acceleration() const
{ return this->torque() / this->pars.I; }

inline float ICEngine::heatingRate() const
{ return this->torque() * this->pars.Km + std::pow(this->Vcur, 2) * this->pars.Kv; }

inline float ICEngine::coolingRate() const
{ return this->pars.C * (this->Tenv - this->Tcur); }

#endif // ICENGINE_H
