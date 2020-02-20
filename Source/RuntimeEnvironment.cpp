#include "stdafx.h"
#include "RuntimeEnvironment.h"

bool RuntimeEnvironment::simulate()
{
	if (!this->engine)
		return false;

	if (this->step <= 0)
		return false;

	do
	{
		this->nextStep(0);
	} while (!this->engine->isOverheated() && this->time() < this->maxTime);

	return true;
}

void RuntimeEnvironment::reset()
{
	this->mTime = 0;
	this->step  = 1;

	if (this->engine)
		this->engine->reset();
}

void RuntimeEnvironment::nextStep()
{
	if (!this->engine)
		return;

	if (this->step <= 0)
		return;

	this->nextStep(0);
}

void RuntimeEnvironment::nextStep(int)
{
	this->engine->update(this->step);
	this->mTime += this->step;
}
