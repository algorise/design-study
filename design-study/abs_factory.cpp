
/*
* - benefit of a factory design is that they can be used alongside hierarchies to construct objects without knowing their exact type.
* - pass factories to create different kind of objects in different parts of the code
* - one of the main benefit is that factories abstract the object creation process, using DI, factories can be easily susbtitued.
* - two factory related patterns in OOP: 1. abstract factory pattern. 2 factory method pattern
* -
*/

/***************************************/
/* A Car Factory Simulation */
/***************************************/
#include "commonfiles.hpp"
#include "abs_factory.hpp"

void createSomeCars(myAbsoluteFactory::IAbstractCarFactory& carFactory)
{
	auto sedan{ carFactory.makeSedan() };
	auto suv{ carFactory.makeSuv() };
	std::cout << format("Sedan: {}\n", sedan->info());
	std::cout << format("Suv: {}\n", suv->info());
}

void abs_factory() 
{
	myAbsoluteFactory::FordFactory fordFactory;
	myAbsoluteFactory::ToyotaFactory toyotaFactory;
	createSomeCars(fordFactory);
	createSomeCars(toyotaFactory);
}
