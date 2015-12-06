/*
 * TimeSolver.cc
 *
 *  Created on: 5 déc. 2015
 *      Author: agallastegui
 */
#include "TimeSolver.h"

TimeSolver::TimeSolver(RCPSPInstance* problem):Solver(problem){
	this->initModel();
}

TimeSolver::~TimeSolver(){}


void TimeSolver::initModel(){
	IloInt nb_jobs = this->problem->nbJobs();
	IloInt nb_ressources = this->problem->nbRessources();
	IloInt M = this->problem->sumDuration() + 1;
	IloInt T = this->problem->duration();

	// INITIALISATION DES VARIABLES
	// ----------------------------

	// Variable x_ij : 1 la tâche j succede i. 0 sinon
	IloArray< IloNumVarArray > y(*this->environment, nb_jobs);
	for(IloInt i=0; i<nb_jobs; i++){
		y[i] = IloNumVarArray(*this->environment,T, 0, 1, ILOBOOL);
	}


	// Variable S_i : date de début de la tache i
	IloNumVarArray S(*this->environment, nb_jobs, 0, IloInfinity, ILOINT);

	// Variable C_lt  l configuration & t temps d'ordonnancement:
	IloArray<IloNumVarArray> C(*this->environment, nb_jobs);
	for(IloInt j=0; j<nb_jobs;j++){
		C[j] = IloNumVarArray(*this->environment, T, 0, M, ILOINT);
	}

	// FONCTION OBJECTIF
	// ------------------------------
	// On minimise la date a laquelle on peut ordonnacer la derniere tache (tâche fictive de durée 0).
	IloExpr Obj(*this->environment);
	for(IloInt t=0; t < T; t++){
		Obj += t*y[nb_jobs-1][t];
	}
	this->model->add(IloMinimize(*this->environment,Obj));

	//CONTRAINTES
	//--------------------------------

	//contrainte1
	for(IloInt i=0; i<nb_jobs;i++){
		IloExpr Ctr1(*this->environment);
		for(IloInt t=0; t<T; t++){
			Ctr1 += y[i][t];
		}
		Ctr1=1;
	}

	//Contraine2
	for(IloInt i=0; i<nb_jobs; i++){
		for(IloInt j=0; j<nb; j++){
			if(this->problem->isSuccessor(i,j)==1){
				IloExpr Ctr2(*this->environment);
				for(IloInt t=0; t<T; t++){
					Ctr2 += t*(y[j][t]-y[i][t]);
				}
			}
			Ctr2 >= this-> problem-> jobDuration(i);
		}
	}



