/*****************************************************************************/
/*  STAP++ : A C++ FEM code sharing the same input data file with STAP90     */
/*     Computational Dynamics Laboratory                                     */
/*     School of Aerospace Engineering, Tsinghua University                  */
/*                                                                           */
/*     Release 1.11, November 22, 2017                                       */
/*                                                                           */
/*     http://www.comdyn.cn/                                                 */
/*****************************************************************************/

#pragma once

#include "Outputter.h"
#include <istream>
#include <string>

using namespace std;

//!	Material base class which only define one data member
/*!	All type of material classes should be derived from this base class */
class CMaterial
{
public:

	unsigned int nset;	//!< Number of set
	
	double E;  //!< Young's modulus

	double rho;  //!<  Density

public:

//! Virtual deconstructor
    virtual ~CMaterial() {};

//!	Read material data from stream Input
	virtual bool Read(ifstream& Input, unsigned int mset) = 0;

	//!	Read material data from stream Input(inp)
	virtual bool ReadInp(ifstream& Input, unsigned int mset, streampos pMaterial) = 0;

//!	Write material data to Stream
    virtual void Write(COutputter& output, unsigned int mset) = 0;

};

//!	Material class for bar element
class CBarMaterial : public CMaterial
{
public:

	double Area;	//!< Sectional area of a bar element

public:
	
//!	Read material data from stream Input
	virtual bool Read(ifstream& Input, unsigned int mset);

	//!	Read material data from stream Input(inp)
	virtual bool ReadInp(ifstream& Input, unsigned int mset, streampos pMaterial);

//!	Write material data to Stream
	virtual void Write(COutputter& output, unsigned int mset);
};

//!	Material class for bar element
class CQ4Material : public CMaterial
{
public:

	double miu;	// ! Poisson ratio
	double t;  // ! Thickness
	int ss; // ! 0 - Plane strain  1 - Plane stress

public:

	//!	Read material data from stream Input
	virtual bool Read(ifstream& Input, unsigned int mset);
	
	//!	Read material data from stream Input(inp)
	virtual bool ReadInp(ifstream& Input, unsigned int mset, streampos pMaterial);

	//!	Write material data to Stream
	virtual void Write(COutputter& output, unsigned int mset);
};
class CAX8RMaterial : public CMaterial//yjl
{
public:

	double rou; // ! density
	double mu;	// ! Poisson ratio

public:

	//!	Read material data from stream Input
	virtual bool Read(ifstream& Input, unsigned int mset);

	//!	Read material data from stream Input(inp)
	virtual bool ReadInp(ifstream& Input, unsigned int mset, streampos pMaterial);

	//!	Write material data to Stream
	virtual void Write(COutputter& output, unsigned int mset);
};
