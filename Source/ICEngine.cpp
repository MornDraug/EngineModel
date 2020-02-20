#include "stdafx.h"
#include "ICEngine.h"

float ICEngine::torque() const
{
	int i;

	for (i = 0; i < this->pars.V.size(); i++)
	{
		if (this->Vcur > this->pars.V[i])
			continue;

		break;
	}

	if (i <= 0)
		return this->pars.M[0];
	//else if (i >= this->pars.M.size() - 1)
	//	return this->pars.M[this->pars.M.size() - 1];

	float V1 = this->pars.V[i - 1];
	float V2 = this->pars.V[i];

	float M1 = this->pars.M[i - 1];
	float M2 = this->pars.M[i];

	float ratio = (this->Vcur - V1) / (V2 - V1);

	return lerp(M1, M2, ratio);
}

void ICEngine::update(float dt)
{
	this->Vcur += this->acceleration() * dt;
	this->Tcur += (this->heatingRate() - this->coolingRate()) * dt;
}
