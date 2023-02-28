
#include <iostream>
#include "D2Q9.h"
#include "Simulation.h"
#include "OutputFile.h"

int main()
{
	int Nx = 300;
	int Ny = 150;
	double vel_LB = 0.04;
	double Re = 220;
	double nu_LB = 2 * vel_LB * Nx / Re;   
		

	double tau = 3 * nu_LB + 0.5;    //taken from paper http://dx.doi.org/10.1016/j.compfluid.2012.11.006 page #2

	std::vector<int> domainSize{ Nx, Ny };
	std::shared_ptr<D2Q9> velSet = std::make_shared<D2Q9>();
	Domain domain(velSet, domainSize);
	domain.CreateNodes();
	domain.ConnectNodes();
	domain.Initialize();

	Simulation sim(domain);
	sim.SetRelaxation(tau);

	int max_iter = 0;
	max_iter = 10000;

	for (int iter = 1; iter <= max_iter; iter++)
	{
		sim.Iterate();
		std::cout << "Iteration: " << iter << std::endl;

		if (iter % 25 == 0)
			sim.WriteOutput(iter);
	}

	return 0;
}

