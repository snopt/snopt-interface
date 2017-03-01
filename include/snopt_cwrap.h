#ifndef SNOPT_C_H
#define SNOPT_C_H
#define DLL_ATTR __declspec(dllexport)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "snopt.h"

/* File: snopt_cwrap.h
 *   C interface for SNOPTB and SNOPTC.
 */
typedef struct {
  char   *name;

  int     memCalled;
  int     initCalled;

  isnSTOP snSTOP;
  isnLog  snLog;
  isnLog2 snLog2;
  isqLog  sqLog;

  int     lenrw, leniw;
  int    *iw;
  double *rw;

  int     lenru, leniu;
  int    *iu;
  double *ru;

} snProblem;

DLL_ATTR void snInit         ( snProblem* prob, char* name, char* prtfile, int summOn );
DLL_ATTR void init2zero      ( snProblem* prob );

DLL_ATTR void allocI         ( snProblem* prob, int len );
DLL_ATTR void allocR         ( snProblem* prob, int len );
DLL_ATTR void reallocI       ( snProblem* prob, int len );
DLL_ATTR void reallocR       ( snProblem* prob, int len );

DLL_ATTR void setPrintfile   ( snProblem* prob, char* prtname );
DLL_ATTR int  setSpecsfile   ( snProblem* prob, char* spcname );

DLL_ATTR int setParameter    ( snProblem* prob, char stropt[] );
DLL_ATTR int getParameter    ( snProblem* prob, char stropt[], char strout[] );
DLL_ATTR int setIntParameter ( snProblem* prob, char stropt[], int opt );
DLL_ATTR int getIntParameter ( snProblem* prob, char stropt[], int opt );
DLL_ATTR int setRealParameter( snProblem* prob, char stropt[], double opt );
DLL_ATTR int getRealParameter( snProblem* prob, char stropt[], double opt );

DLL_ATTR void setUserI       ( snProblem* prob, int *iu, int leniu );
DLL_ATTR void setUserR       ( snProblem* prob, double *ru, int lenru );
DLL_ATTR void setUserspace   ( snProblem* prob, int *iu, int leniu,
			       double *ru, int lenru );

DLL_ATTR void setLog         ( snProblem* prob, isnLog snLog, isnLog2 snLog2, isqLog sqLog );
DLL_ATTR void setSTOP        ( snProblem* prob, isnSTOP snSTOP );

DLL_ATTR void setWorkspace   ( snProblem* prob, int m, int n, int ne,
			       int negCon, int nnCon, int nnObj, int nnJac);
DLL_ATTR void setWorkspaceA  ( snProblem* prob, int nF, int n, int neA, int neG);

DLL_ATTR int solveA( snProblem* prob, int start,
		     int nF, int n, double ObjAdd, int ObjRow,
		     snFunA usrfun,
		     int neA, int *iAfun, int *jAvar, double *A,
		     int neG, int *iGfun, int *jGvar,
		     double *xlow, double *xupp, double *Flow, double *Fupp,
		     double *x, int *xstate, double *xmul,
		     double *F, int *Fstate, double *Fmul,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR int snoptA( snProblem* prob, int start,
		     int nF, int n, double ObjAdd, int ObjRow,
		     snFunA usrfun,
		     int neA, int *iAfun, int *jAvar, double *A,
		     int neG, int *iGfun, int *jGvar,
		     double *xlow, double *xupp, double *Flow, double *Fupp,
		     double *x, int *xstate, double *xmul,
		     double *F, int *Fstate, double *Fmul,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR int solveB( snProblem* prob, int start, int m, int n, int ne,
		     int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
		     snConB funcon, snObjB funobj,
		     double *valJ, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs, double *x,
		     double *pi, double *rc, double* objective,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR int snoptB( snProblem* prob, int start, int m, int n, int ne,
		     int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
		     snConB funcon, snObjB funobj,
		     double *valJ, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs, double *x,
		     double *pi, double *rc, double* objective,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR int solveC( snProblem* prob, int start, int m, int n, int ne,
		     int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
		     snFunC usrfun,
		     double *valJ, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs, double *x,
		     double *pi, double *rc, double* objective,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR int snoptC( snProblem* prob, int start, int m, int n, int ne,
		     int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
		     snFunC usrfun,
		     double *valJ, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs, double *x,
		     double *pi, double *rc, double* objective,
		     int* nS, int* nInf, double* sInf );

DLL_ATTR void deleteSNOPT( snProblem* prob );

#endif /* SNOPT_C_H */
