#pragma once

#ifndef ICENGINE_H
#define ICENGINE_H

#include "Engine.h"

// Двигатель внутреннего сгорания (Internal combustion engine).
class ICEngine : public Engine
{
public:
	struct Parameters
	{
		std::vector<float> M; // Крутящий момент, Н*м.
		std::vector<float> V; // Скорость вращения коленвала, рад/с.

		float I  = 0; // Момент инерции двигателя, кг*м2.
		float Km = 0; // Коэффициент зависимости скорости нагрева от крутящего момента.
		float Kv = 0; // Коэффициент зависимости скорости нагрева от скорости вращения коленвала.
		float C  = 0; // Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды.
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
		throw std::invalid_argument("Векторы M и V не могут быть пустыми");

	if (pars.M.size() != pars.V.size())
		throw std::invalid_argument("Векторы M и V должны иметь одинаковый размер");
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
