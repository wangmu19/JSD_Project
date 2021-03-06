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
#include "Node.h"
#include "ElementGroup.h"
#include "Outputter.h"
#include "Solver.h"
#include "LoadCaseData.h"
#include "SkylineMatrix.h"

using namespace std;

//!	Clear an array
template <class type> void clear( type* a, unsigned int N );

//!	Domain class : Define the problem domain
/*!	Only a single instance of Domain class can be created */
class CDomain
{
private:

//!	The instance of the Domain class
	static CDomain* _instance;

//!	Input file stream for reading data from input data file
	ifstream Input;

//!	Heading information for use in labeling the outpu
	char Title[256]; 

//!	Solution MODEX
//	0 -- Data check only
//  1 -- static problem
//  2 -- modal analysis
//  3 -- dynamic problem
	unsigned int MODEX;

//!	Total number of nodal points
	unsigned int NUMNP;

//!	List of all nodes in the domain
	CNode* NodeList;

//!	Total number of element groups.
/*! An element group consists of a convenient collection of elements with same type */
	unsigned int NUMEG;

//! Element group list
    CElementGroup* EleGrpList;
    
//!	Number of load cases
	unsigned int NLCASE;

//!	List of all load cases
	CLoadCaseData* LoadCases;

//!	Number of concentrated loads applied in each load case
	unsigned int* NLOAD;

//!	Total number of equations in the system
	unsigned int NEQ;

//!	Banded stiffness matrix
/*! A one-dimensional array storing only the elements below the	skyline of the 
    global stiffness matrix. */
    CSkylineMatrix<double>* StiffnessMatrix;

//! Consistent mass matrix --- has the same for with the global stiffness matrix
	CSkylineMatrix<double>* C_MassMatrix;

//! Lumped mass matrix --- has the same length of NEQ
	double* L_MassMatrix;

//!	Global nodal force/displacement vector
	double* Force;

//! Output history messages of which freedom
	int Num_His_Output;
	int* His_freedom;

//! Time interval and damping coefficients
	double Dyna_para[3];


public:

//!	Constructor
	CDomain();

//!	Desconstructor
	~CDomain();

//!	Return pointer to the instance of the Domain class
	static CDomain* Instance();

//!	Read domain data from the input data file
	bool ReadData(string FileName, string OutFile);

//! Read domain data from the inp data file
	bool ReadInpData(string FileName,string OutFile);

//! Return the place of the first "code" from start streampos	
	streampos seek(string code, streampos start,int *flag);

//! Return the place of selected set information, target for target set, set for the type of set(*Nset or *Elset
	streampos seekset(string target, string set);

//! Search between start and end, count the time that "code" appears
	int countcode(string code, streampos start, streampos end);

//!	Read nodal point data
	bool ReadInpNodalPoints();

//!	Read nodal point data
	bool ReadNodalPoints();

//!	Read load case data
	bool ReadInpLoadCases();

//!	Read load case data
	bool ReadLoadCases();

//!	Read element data
	bool ReadInpElements();
	
//!	Read element data
	bool ReadElements();

//!	Read history output message
	bool ReadInpHisMessage();

//!	Read history output message
	bool ReadHisMessage();

//!	Calculate global equation numbers corresponding to every degree of freedom of each node
	void CalculateEquationNumber();

//!	Calculate column heights
	void CalculateColumnHeights();

//! Allocate storage for matrices
/*!	Allocate Force, ColumnHeights, DiagonalAddress and StiffnessMatrix and 
    calculate the column heights and address of diagonal elements */
	void AllocateMatrices();

//!	Assemble the banded gloabl stiffness matrix
	void AssembleStiffnessMatrix();

//! Assemble the global mass matrix
	void AssembleMassMatrix();

//!	Assemble the global nodal force vector for load case LoadCase
	bool AssembleForce(unsigned int LoadCase); 

//!	Return solution mode
	inline unsigned int GetMODEX() { return MODEX; }

//!	Return the title of problem
	inline string GetTitle() { return Title; }

//!	Return the total number of equations
	inline unsigned int GetNEQ() { return NEQ; }

//!	Return the total number of nodal points
	inline unsigned int GetNUMNP() { return NUMNP; }

//!	Return the node list
	inline CNode* GetNodeList() { return NodeList; }

//!	Return total number of element groups
	inline unsigned int GetNUMEG() { return NUMEG; }

//! Return element group list
    CElementGroup* GetEleGrpList() { return EleGrpList; }

//!	Return pointer to the global nodal force vector
	inline double* GetForce() { return Force; }

//!	Return pointer to the global nodal displacement vector
	inline double* GetDisplacement() { return Force; }

//!	Return the total number of load cases
	inline unsigned int GetNLCASE() { return NLCASE; }

//!	Return the number of concentrated loads applied in each load case
	inline unsigned int* GetNLOAD() { return NLOAD; }

//!	Return the list of load cases
	inline CLoadCaseData* GetLoadCases() { return LoadCases; }

//!	Return pointer to the banded stiffness matrix
	inline CSkylineMatrix<double>* GetStiffnessMatrix() { return StiffnessMatrix; }

//!	Return pointer to the banded mass matrix
	inline CSkylineMatrix<double>* GetMassMatrix() { return C_MassMatrix; }

//! Return the number of freedoms for history output
	inline int GetNumHisFreedom() { return Num_His_Output; }

//! Return the messages of freedoms for history output
	inline int* GetMessHisFreedom() { return His_freedom; }

//! Return the dynamics parameters
	inline double* GetDynPara() { return Dyna_para; }

};
