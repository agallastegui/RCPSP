/*
 * TimeSolver.h
 *
 *  Created on: 5 déc. 2015
 *      Author: agallastegui
 */

#ifndef SOLVER_TIMESOLVER_H_
#define SOLVER_TIMESOLVER_H_
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ilconcert/iloenv.h"
#include "ilconcert/ilomodel.h"
#include "ilcplex/ilocplexi.h"
#include "ilconcert/ilosys.h"
#include "ilconcert/iloexpression.h"
#include "../problem/RCPSPInstance.h"

class Solver {
 protected:
	IloEnv* environment;
	IloModel* model;
 	RCPSPInstance* problem;

 public:
	Solver(RCPSPInstance* problem);
	virtual ~Solver();
	virtual void initModel() = 0;
	void solve();
 };




#endif /* SOLVER_TIMESOLVER_H_ */
