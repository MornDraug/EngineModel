#include "stdafx.h"

#include "Engine.h"
#include "ICEngine.h"
#include "RuntimeEnvironment.h"

// Создаёт объект Engine из файла.
template<class _Engine>
std::shared_ptr<_Engine> createEngine(const std::string& filename, float Tenv)
{ return nullptr; }

template<>
std::shared_ptr<ICEngine> createEngine(const std::string& filename, float Tenv)
{
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::invalid_argument("Не удалось открыть файл: " + filename);

	ICEngine::Parameters pars;
	float Tmax;

	std::string line;
	std::string val;

	std::vector<std::string> par;

	while (std::getline(file, line))
	{
		par.clear();

		std::stringstream str(line);

		while (std::getline(str, val, ' '))
			par.emplace_back(val);

		if (par.size() < 2)
			continue;

		if (par[0] == "M")
		{
			for (int i = 1; i < par.size(); i++)
				pars.M.push_back(atof(par[i].c_str()));
		}
		else if (par[0] == "V")
		{
			for (int i = 1; i < par.size(); i++)
				pars.V.push_back(atof(par[i].c_str()));
		}
		else if (par[0] == "I")
			pars.I = atof(par[1].c_str());
		else if (par[0] == "Km")
			pars.Km = atof(par[1].c_str());
		else if (par[0] == "Kv")
			pars.Kv = atof(par[1].c_str());
		else if (par[0] == "C")
			pars.C = atof(par[1].c_str());
		else if (par[0] == "Tmax")
			Tmax = atof(par[1].c_str());
	}

	file.close();

	return std::make_shared<ICEngine>(pars, Tmax, Tenv);
}

// Точка входа приложение.
int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "ru_RU");
	std::setlocale(LC_NUMERIC, "en_EN");

	float Tenv;

	std::cout << "Введите температуру окружающей среды: ";
	std::cin >> Tenv;
	std::cout << std::endl;

	std::shared_ptr<ICEngine> engine;

	try
	{
		engine = createEngine<ICEngine>("parameters.txt", Tenv);
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	RuntimeEnvironment env;

	env.step = 1;
	env.maxTime = 60 * 60 * 24;
	env.engine = std::static_pointer_cast<Engine>(engine);

#ifdef TRACE

	std::cout << "Time " << env.time() << std::endl;
	std::cout << "   T " << engine->temperature() << std::endl;
	std::cout << "   V " << engine->velocity() << std::endl;

	try
	{
		do
		{
			env.nextStep();

			std::cout << "Time " << env.time() << std::endl;
			std::cout << "   T " << engine->temperature() << std::endl;
			std::cout << "   V " << engine->velocity() << std::endl;

			std::cin.get();
		} while (!engine->isOverheated() && env.time() < env.maxTime);
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

#else

	try
	{
		if (env.simulate())
		{
			if (engine->temperature() >= engine->Tmax)
				std::cout << "Двигатель перегрелся за " << env.time() << " секунд" << std::endl;
			else if (env.time() >= env.maxTime)
				std::cout << "Превышено время симуляции" << std::endl;
		}
		else
			std::cout << "Симуляция не была начата" << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}


#endif // TRACE

	system("pause");

	return EXIT_SUCCESS;
}
