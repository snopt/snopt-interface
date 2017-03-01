#ifndef SQOPT_C_H
#define SQOPT_C_H
#define DLL_ATTR __declspec(dllexport)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "snopt.h"

/* File: sqopt_cwrap.h
 *   C interface for SQOPT.
 */
typedef struct {
  char   *name;

  int     memCalled;
  int     initCalled;
  isqLog  sqLog;

  int     lenrw, leniw;
  int    *iw;
  double *rw;

  int     lenru, leniu;
  int    *iu;
  double *ru;

} sqProblem;

DLL_ATTR void sqInit         (sqProblem* prob, char* name, char* prtfile, int summOn);
DLL_ATTR void init2zeroQ     (sqProblem* prob);

DLL_ATTR void allocIQ        (sqProblem* prob, int len);
DLL_ATTR void allocRQ        (sqProblem* prob, int len);
DLL_ATTR void reallocIQ      (sqProblem* prob, int len);
DLL_ATTR void reallocRQ      (sqProblem* prob, int len);

DLL_ATTR void sqPrintfile   (sqProblem* prob, char* prtname);
DLL_ATTR int  sqSpecsfile   (sqProblem* prob, char* spcname);

DLL_ATTR int sqSetParameter    (sqProblem* prob, char stropt[]);
DLL_ATTR int sqGetParameter    (sqProblem* prob, char stropt[], char strout[]);
DLL_ATTR int sqSetIntParameter (sqProblem* prob, char stropt[], int opt);
DLL_ATTR int sqGetIntParameter (sqProblem* prob, char stropt[], int opt);
DLL_ATTR int sqSetRealParameter(sqProblem* prob, char stropt[], double opt);
DLL_ATTR int sqGetRealParameter(sqProblem* prob, char stropt[], double opt);

DLL_ATTR void sqUserI       (sqProblem* prob, int *iu, int leniu);
DLL_ATTR void sqUserR       (sqProblem* prob, double *ru, int lenru);
DLL_ATTR void sqUserspace   (sqProblem* prob, int *iu, int leniu, double *ru, int lenru);
DLL_ATTR void sqSetLog      (sqProblem* prob, isqLog sqLog);
DLL_ATTR void sqWorkspace   (sqProblem* prob, int m, int n, int neA, int ncObj, int nnH);

DLL_ATTR int solveQ(sqProblem* prob, int start, sqFunHx qpHx,
		    int m, int n, int neA, int ncObj, int nnH,
		    int iObj, double ObjAdd,
		    double *valA, int *indA, int *locA,
		    double *bl, double *bu, double *cObj,
		    int *eType, int *hs, double *x, double *pi, double *rc,
		    double* objective,
		    int* nS, int* nInf, double* sInf);

DLLA_ATTR int sqopt(sqProblem* prob, int start, sqFunHx qpHx,
		    int m, int n, int neA, int ncObj, int nnH,
		    int iObj, double ObjAdd,
		    double *valA, int *indA, int *locA,
		    double *bl, double *bu, double *cObj,
		    int *eType, int *hs, double *x, double *pi, double *rc,
		    double* objective,
		    int* nS, int* nInf, double* sInf);

void deleteSQOPT(sqProblem* prob);

#endif /* SQOPT_C_H */
