#pragma once

#ifndef CONFIG_H
#define CONFIG_H

class ConfigParameter
{
public:
	std::variant<float, std::vector<float>> val;

public:
	inline ConfigParameter();
	inline virtual ~ConfigParameter();
};

inline ConfigParameter::ConfigParameter()
{
}

inline ConfigParameter::~ConfigParameter()
{
}

class Config
{
public:
	inline Config();
	inline Config(const std::string& filename);
	inline virtual ~Config();

	inline bool find(const std::string& name) const;

	inline const ConfigParameter& get(const std::string& name) const;
	inline ConfigParameter& get(const std::string& name);

	void readFromFile(const std::string& filename);

private:
	std::map<std::string, ConfigParameter> pars;
};

inline Config::Config()
{
}

inline Config::Config(const std::string& filename)
{ this->readFromFile(filename); }

inline Config::~Config()
{
}

inline bool Config::find(const std::string& name) const
{ return this->pars.find(name) != this->pars.end(); }

inline const ConfigParameter& Config::get(const std::string & name) const
{ return this->pars.at(name); }

inline ConfigParameter& Config::get(const std::string & name)
{ return this->pars.at(name); }

#endif // CONFIG_H
