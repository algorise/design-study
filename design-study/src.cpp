
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "abs_factory.hpp"
#include "factory.hpp"

void abs_factory() 
{
	FordFactory fordFactory;
	ToyotaFactory toyotaFactory;
	createSomeCars(fordFactory);
	createSomeCars(toyotaFactory);
}

void factory() 
{
	/* NOTE: Factory methods are one way to implement virtual contructors, which are methods that create objects of different types. For example, the requestCar() method creates both Toyotas and Fords, depending on the conrete factory object on which it is called.*/
	ToyotaFactory myFactory;
	auto myCar{ myFactory.requestCar() };
	std::cout << myCar->info() << std::endl;

	//Build 10 Cars
	std::vector<std::unique_ptr<CarFactory>> factories;
	// Create 3 Ford factories and 1 Toyota Factory
	factories.push_back(std::make_unique<FordFactory>());
	factories.push_back(std::make_unique<FordFactory>());
	factories.push_back(std::make_unique<FordFactory>());
	factories.push_back(std::make_unique<ToyotaFactory>());

	factories[0]->requestCar();
	factories[0]->requestCar();
	factories[1]->requestCar();
	factories[3]->requestCar();

	LeastBusyFactory leastBusyFactory{ std::move(factories) };

	for (size_t i{ 0 }; i < 10; i++) 
	{
		auto theCar{ leastBusyFactory.requestCar() };
		std::cout << theCar->info() << std::endl;
	}
}

int main()
{
	abs_factory();
	factory();
}

