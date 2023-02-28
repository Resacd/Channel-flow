#include "ZouHe.h"
#include <cmath>
#include <iostream>


ZouHe::ZouHe(int coord_x, int coord_y)
	:	Node(coord_x, coord_y)
{
	SetInletVel(0.04 * sin(double(coord_y) / double(149) * PI), 0.0);	// parabolic inlet profile
}


ZouHe::~ZouHe()
{
}

void ZouHe::ApplyBC()
{
	double density = 1;	 // boundary condition is taken from :  
	if (IsCornerRightTop() == 1)
	{
		m_distributions[3] = m_distributions[1] + 2 / 3 * density * m_inlet[0];
		m_distributions[4] = m_distributions[2] + 2 / 3 * density * m_inlet[1];
		m_distributions[5] = density * (m_inlet[0] + m_inlet[1]);
		m_distributions[7] = -density * (m_inlet[0] + m_inlet[1]);
		m_distributions[8] = m_distributions[6] + 1 / 6 * density * (m_inlet[0] + m_inlet[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] - m_distributions[4]
			- m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}
	else if (IsCornerLeftTop() == 1)
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inlet[0];
		m_distributions[4] = m_distributions[2] + 2 / 3 * density * m_inlet[1];
		m_distributions[5] = density * (m_inlet[0] + m_inlet[1]);
		m_distributions[7] = -density * (m_inlet[0] + m_inlet[1]);
		m_distributions[8] = m_distributions[6] + 1 / 6 * density * (m_inlet[0] + m_inlet[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] - m_distributions[4]
			- m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}
	else if (IsCornerLeftLow() == 1) 
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inlet[0];
		m_distributions[2] = m_distributions[4] + 2 / 3 * density * m_inlet[1];
		m_distributions[5] = m_distributions[7] + 1 / 6 * density * (m_inlet[0] + m_inlet[1]);
		m_distributions[6] = -density * (m_inlet[0] + m_inlet[1]);
		m_distributions[8] = density * (m_inlet[0] + m_inlet[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] -
			m_distributions[4] - m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];


	}
	else
	{
		m_distributions[4] = m_distributions[2] + 2 / 3 * density * m_inlet[1];
		m_distributions[7] = m_distributions[5] - density / 2 * (m_distributions[1] - m_distributions[3]) + 1 / 2 * density * m_inlet[0] + 1 / 6 * density * m_inlet[1];
		m_distributions[6] = m_distributions[8] + density / 2 * (m_distributions[1] - m_distributions[3]) - 1 / 2 * density * m_inlet[0] + 1 / 6 * density * m_inlet[1];
	}

}

double ZouHe::Density()
{
	//return m_distributions[0] + m_distributions[2] + m_distributions[4] + 2 * (m_distributions[3] + m_distributions[6] + m_distributions[7]) * (1 - m_inletVel[0]);	// sum of distributions for all discrete velocities (in all directions)
	return 1;
}

std::vector<double> ZouHe::Velocity(std::shared_ptr<VelocitySet> velSet)
{
	return m_inlet;
}

void ZouHe::SetInletVel(double ux, double uy)
{
	m_inlet.push_back(ux);
	m_inlet.push_back(uy);
}

bool ZouHe::IsCorner()
{
	int nNeighbours = 0;
	for (auto neighbour : m_neighbours)
		if (neighbour != nullptr)
			nNeighbours++;
	if (nNeighbours > 3)
		return 0;
	else
		return 1;
}

bool ZouHe::IsCornerLow()
{
	if (IsCorner() && y_position == 0)
		return 1;
	else
		return 0;
}

bool ZouHe::IsCornerRightTop()
{
	if (IsCorner() && y_position != 0 && x_position !=0)
		return 1;
	else
		return 0;
}

bool ZouHe::IsCornerLeftTop()
{
	if (IsCorner() && y_position != 0 && x_position == 0)
		return 1;
	else
		return 0;
}

bool ZouHe::IsCornerLeftLow()
{
	if (IsCorner() && y_position == 0 && x_position == 0)
		return 1;
	else
		return 0;
}

const double ZouHe::PI = 3.1415;
