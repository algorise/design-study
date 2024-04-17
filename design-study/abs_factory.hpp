
#pragma once

class ICar
{
public:
	virtual ~ICar() = default;
	virtual std::string info() const = 0;
};

class Ford : public ICar{};

class FordSedan : public Ford
{
public:
	std::string info() const override {
		return "Ford Sedan";
	}
};

class FordSuv : public Ford
{
public:
	std::string info() const override {
		return "Ford Suv";
	}
};

class Toyota : public ICar{};

class ToyotaSedan : public Toyota
{
public:
	std::string info() const override {
		return "Toyota Sedan";
	}
};

class ToyotaSuv : public Toyota
{
public:
	std::string info() const override {
		return "Toyota Suv";
	}
};

class IAbstractCarFactory
{
public:
	virtual ~IAbstractCarFactory() = default;
	virtual std::unique_ptr<ICar> makeSedan() = 0;
	virtual std::unique_ptr<ICar> makeSuv() = 0;
};

class FordFactory : public IAbstractCarFactory
{
public:
	std::unique_ptr<ICar> makeSedan() override
	{
		return std::make_unique<FordSedan>();
	}
	std::unique_ptr<ICar> makeSuv() override
	{
		return std::make_unique<FordSuv>();
	}
};

class ToyotaFactory : public IAbstractCarFactory
{
public:
	std::unique_ptr<ICar> makeSedan() override
	{
		return std::make_unique<ToyotaSedan>();
	}
	std::unique_ptr<ICar> makeSuv() override
	{
		return std::make_unique<ToyotaSuv>();
	}
};

extern void createSomeCars(IAbstractCarFactory& carFactory);