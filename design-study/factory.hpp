#pragma once

/* Factory Method Pattern */
/*
* - In this pattern it is entirely up to the concrete class to decide what kind of objects to create.
* - This approaches uses polymorphism on factories.
* - This approach leads to easily extensible programs; simply changing the factory instance can allow the program to work on a completely different set of objects and classes.
* - One reason for using factories is that the type of the object you want to create may depend on some condition. For example, if you want a car, you might want to put your order into the factory
*	- that has received the fewest requests so far, regardless of whether the car you eventually get is a Toyota or a Ford.
* - The first we'll need is the hierarchy of cars.
*/

class IICar 
{
public:
	virtual ~IICar() = default; // always a virtual destructor
	virtual std::string info() const = 0;
};

class Ford : public IICar
{
public:
	std::string info() const override { return "Ford"; }
};

class Toyota : public IICar
{
public:
	std::string info() const override { return "Toyota"; }
};

/*
* - The CarFactory class is a bit more interesting. Each factory keeps track of the number of cars produced. When the public non-virtual requestCar() method is called, the number of cars produced at the factory is increased by one, and the protected pure-virtual createCar() method is called, which reates and returns a new concrete car.
* - The idea is that individual factories override createCar() to return the appropriate type of car. The CarFactory itself implements requestCar(), which takes care of updating the number of cars produced. The CarFactory also providees a public method to query the number of cars produced at each factory.
*/

class CarFactory 
{
public:
	virtual ~CarFactory() = default;

	std::unique_ptr<IICar> requestCar()
	{
		++m_numberOfCarsProduced;
		return createCar();
	}

	size_t getNumberOfCarsProduced() const { return m_numberOfCarsProduced;  }

protected:
	virtual std::unique_ptr<IICar> createCar() = 0;

private:
	size_t m_numberOfCarsProduced;
};

class ToyotaFactory : public CarFactory 
{
protected:
	std::unique_ptr<IICar> createCar() override
	{
		return std::make_unique<Toyota>();
	}
};

class FordFactory : public CarFactory
{
protected:
	std::unique_ptr<IICar> createCar() override
	{
		return std::make_unique<Ford>();
	}
};

/* A more interesting example makes use of the virtual constructor idea to build a car in the factory that has the fewest cars produced. To do this, you can create a new factory, called LeastBusyFactory, that derives from CarFactory and that accepts a number of other CarFactory objects in its constructor. As all CarFactory classe have to do, LeastBusyFactory
* - LeastBusyFactory overrides the createCar() method. Its implementation finds the least busy factory in the list of factories passed to the constructor and asks that factory to create a car.
*/

class LeastBusyFactory : public CarFactory 
{
public:
	explicit LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories);

protected:
	std::unique_ptr<IICar> createCar() override;

private:
	std::vector<std::unique_ptr<CarFactory>> m_factories;
};

LeastBusyFactory::LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories) : m_factories{ std::move(factories) }
{
	if (m_factories.empty())
	{
		throw runtime_error{ "No factories provided" };
	}
}

std::unique_ptr<IICar> LeastBusyFactory::createCar() 
{
	CarFactory* bestSoFar{ m_factories[0].get() };

	for (auto& factory : m_factories) {
		if (factory->getNumberOfCarsProduced() < bestSoFar->getNumberOfCarsProduced())
		{
			bestSoFar = factory.get();
		}
	}

	return bestSoFar->requestCar();
}

/* Other Types Of Factories
* - A Factory can be implemented in a single class instead of a class hierarchy. In that case, a single create() method on the factory takes a type or string parameter from which it decides which object to create, instead of delegating that work to concrete subclasses.
*/

/* Other Uses Of Factories 
* - Use a factory pattern for more than just modeling real-world factories.
* - Word Processor for different languages.
* - as an alternative to pimpl idiom
*/


