#include "snopt_cwrap.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void snInit(snProblem* prob, char* name, char* prtfile, int summOn) {
  int leniw, lenrw, len;

  init2zero(prob);

  leniw = 500;
  lenrw = 500;

  allocI(prob, leniw);
  allocR(prob, lenrw);

  prob->name   = name;

  len = strlen(prtfile);

  if (summOn != 0) {
    printf(" ==============================\n");
    printf("   SNOPT  C interface  2.0.0   ");
    fflush(stdout);
    //------123456789|123456789|123456789|
  }

  f_sninit(prtfile, len, summOn,
	   prob->iw, prob->leniw,
	   prob->rw, prob->lenrw);
  prob->initCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void init2zero(snProblem* prob) {
  prob->name      = NULL;

  prob->memCalled  = 0;
  prob->initCalled = 0;

  prob->snLog     = NULL;
  prob->snLog2    = NULL;
  prob->sqLog     = NULL;
  prob->snSTOP    = NULL;

  prob->leniw     = 0;
  prob->lenrw     = 0;
  prob->iw        = NULL;
  prob->rw        = NULL;

  prob->leniu     = 0;
  prob->lenru     = 0;
  prob->iu        = NULL;
  prob->ru        = NULL;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void allocI(snProblem* prob, int len) {
  prob->leniw = len;
  prob->iw    = malloc(sizeof(int)*len);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void allocR(snProblem* prob, int len) {
  prob->lenrw = len;
  prob->rw    = malloc(sizeof(double)*len);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void reallocI (snProblem* prob, int len) {
  prob->leniw = len;
  prob->iw    = (int*)realloc(prob->iw, sizeof(int)*prob->leniw);

  setIntParameter(prob, (char*)"Total int workspace", prob->leniw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void reallocR(snProblem* prob, int len) {
  prob->lenrw = len;
  prob->rw = (double*)realloc(prob->rw, sizeof(double)*prob->lenrw);

  setIntParameter(prob, (char*)"Total real workspace", prob->lenrw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setPrintfile(snProblem* prob, char *prtname) {
  int len = strlen(prtname);

  assert(prob->initCalled == 1);
  f_snsetprint(prtname, len,
		prob->iw, prob->leniw, prob->rw, prob->lenrw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int setSpecsfile(snProblem* prob, char *spcname) {
  int inform;
  int len = strlen(spcname);

  assert(prob->initCalled == 1);
  f_snspec(spcname, len, &inform,
	    prob->iw, prob->leniw, prob->rw, prob->lenrw);

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int setParameter(snProblem* prob, char stropt[]) {
  int errors, len = strlen(stropt);

  assert(prob->initCalled == 1);
  f_snset(stropt, len, &errors,
	   prob->iw, prob->leniw, prob->rw, prob->lenrw);

  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int getParameter(snProblem* prob, char stropt[], char strout[]) {
  int errors;
  int inlen  = strlen(stropt);
  int outlen = strlen(strout);

  assert(prob->initCalled == 1);
  f_sngetc(stropt, inlen, strout, outlen, &errors,
	    prob->iw, prob->leniw, prob->rw, prob->lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int setIntParameter(snProblem* prob, char stropt[], int opt) {
  int errors, len = strlen(stropt);

  assert(prob->initCalled == 1);
  f_snseti (stropt, len, opt, &errors,
	     prob->iw, prob->leniw, prob->rw, prob->lenrw);

  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int getIntParameter(snProblem* prob, char stropt[], int opt) {
  int errors, len = strlen(stropt);

  assert(prob->initCalled == 1);
  f_sngeti(stropt, len, &opt, &errors,
	    prob->iw, prob->leniw, prob->rw, prob->lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int setRealParameter(snProblem* prob, char stropt[], double opt) {
  int errors, len = strlen(stropt);

  assert(prob->initCalled == 1);
  f_snsetr (stropt, len, opt, &errors,
	     prob->iw, prob->leniw, prob->rw, prob->lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int getRealParameter(snProblem* prob, char stropt[], double opt) {
  int errors, len = strlen(stropt);

  assert(prob->initCalled == 1);
  f_sngetr (stropt, len, &opt, &errors,
	     prob->iw, prob->leniw, prob->rw, prob->lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setUserI(snProblem* prob, int *iu, int leniu) {
  prob->iu    = iu;
  prob->leniu = leniu;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setUserR(snProblem* prob, double *ru, int lenru) {
  prob->ru    = ru;
  prob->lenru = lenru;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setUserspace(snProblem* prob, int *iu, int leniu, double *ru, int lenru) {
  prob->iu    = iu;
  prob->leniu = leniu;

  prob->ru    = ru;
  prob->lenru = lenru;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setWorkspace(snProblem* prob, int m, int n, int ne,
		  int negCon, int nnCon, int nnObj, int nnJac) {
  int miniw, minrw, inform, ineG;
  int memGuess = 0;

  assert(prob->initCalled == 1);

  if (negCon < 0) {
    ineG = nnCon*nnJac;
    memGuess = 1;
  } else {
    ineG = negCon;
  }

  f_snmem(&inform, m, n, ne,
	  ineG, nnCon, nnObj, nnJac, &miniw, &minrw,
	  prob->iw, prob->leniw, prob->rw, prob->lenrw);

  if (miniw > prob->leniw) { reallocI(prob, miniw); }
  if (minrw > prob->lenrw) { reallocR(prob, minrw); }

  prob->memCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setWorkspaceA(snProblem* prob, int nF, int n, int neA, int neG) {
  int miniw, minrw, inform, ineG;
  int memGuess = 0;

  assert(prob->initCalled == 1);

  if (neG < 0) {
    ineG     = n*nF;
    memGuess = 1;
  } else {
    ineG = neG;
  }

  f_snmema(&inform, nF, n, neA, ineG,
	   &miniw, &minrw,
	   prob->iw, prob->leniw, prob->rw, prob->lenrw);

  if (miniw > prob->leniw) { reallocI(prob, miniw); }
  if (minrw > prob->lenrw) { reallocR(prob, minrw); }

  prob->memCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setLog(snProblem* prob, isnLog snLog, isnLog2 snLog2, isqLog sqLog) {
  prob->snLog  = snLog;
  prob->snLog2 = snLog2;
  prob->sqLog  = sqLog;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void setSTOP(snProblem* prob, isnSTOP snSTOP) {
  prob->snSTOP = snSTOP;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int solveA(snProblem* prob, int start,
	   int nF, int n, double ObjAdd, int ObjRow,
	   snFunA usrfun,
	   int neA, int *iAfun, int *jAvar, double *A,
	   int neG, int *iGfun, int *jGvar,
	   double *xlow, double *xupp, double *Flow, double *Fupp,
	   double *x, int *xstate, double *xmul,
	   double *F, int *Fstate, double *Fmul,
	   int* nS, int* nInf, double* sInf) {

  int i, inform, iObj, miniw, minrw;

  assert(prob->initCalled == 1);

  if (prob->memCalled == 0) { setWorkspaceA(prob, nF, n, neA, neG); }

  for (i = 0; i < neA; i++) {
    iAfun[i]++;
    jAvar[i]++;
  }
  for (i = 0; i < neG; i++) {
    iGfun[i]++;
    jGvar[i]++;
  }

  iObj = ObjRow+1;

  f_snkera(start, prob->name, nF, n, ObjAdd, iObj, usrfun,
	   prob->snLog, prob->snLog2, prob->sqLog, prob->snSTOP,
	   iAfun, jAvar, neA, A,
	   iGfun, jGvar, neG,
	   xlow, xupp, Flow, Fupp,
	   x, xstate, xmul,
	   F, Fstate, Fmul,
	   &inform, nS, nInf, sInf,
	   &miniw, &minrw,
	   prob->iu, prob->leniu, prob->ru, prob->lenru,
	   prob->iw, prob->leniw, prob->rw, prob->lenrw);


  for (i = 0; i < neA; i++) {
    iAfun[i]--;
    jAvar[i]--;
  }
  for (i = 0; i < neG; i++) {
    iGfun[i]--;
    jGvar[i]--;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int solveB(snProblem* prob, int start, int m, int n, int ne,
	   int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
	   snConB funcon, snObjB funobj,
	   double *valJ, int *indJ, int *locJ,
	   double *bl, double *bu, int *hs, double *x,
	   double *pi, double *rc, double* objective,
	   int* nS, int* nInf, double* sInf) {

  int i, inform, iiObj, miniw, minrw;

  assert(prob->initCalled == 1);

  if (prob->memCalled == 0) {
    setWorkspace(prob, m, n, ne, -1, nnCon, nnObj, nnJac);
  }


  for (i = 0; i < ne; i++) {
    indJ[i]++;
  }
  for (i = 0; i <= n; i++) {
    locJ[i]++;
  }

  iiObj = iObj+1;

  f_snkerb(start, prob->name, m, n, ne,
	   nnCon, nnObj, nnJac, iiObj,
	   ObjAdd,
	   funcon, funobj,
	   prob->snLog, prob->snLog2, prob->sqLog, prob->snSTOP,
	   valJ, indJ, locJ,
	   bl, bu, hs, x, pi, rc,
	   &inform, nS, nInf, sInf, objective,
	   &miniw, &minrw,
	   prob->iu, prob->leniu, prob->ru, prob->lenru,
	   prob->iw, prob->leniw, prob->rw, prob->lenrw);

  for (i = 0; i < ne; i++) {
    indJ[i]--;
  }
  for (i = 0; i <= n; i++) {
    locJ[i]--;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int solveC(snProblem* prob, int start, int m, int n, int ne,
	   int nnCon, int nnObj, int nnJac, int iObj, double ObjAdd,
	   snFunC usrfun,
	   double *valJ, int *indJ, int *locJ,
	   double *bl, double *bu, int *hs, double *x,
	   double *pi, double *rc, double* objective,
	   int* nS, int* nInf, double* sInf) {

  int i, inform, iiObj, miniw, minrw;

  assert(prob->initCalled == 1);

  if (prob->memCalled == 0) {
    setWorkspace(prob, m, n, ne, -1, nnCon, nnObj, nnJac);
  }

  for (i = 0; i < ne; i++) {
    indJ[i]++;
  }
  for (i = 0; i <= n; i++) {
    locJ[i]++;
  }
  iiObj = iObj+1;

  f_snkerc(start, prob->name, m, n, ne,
	   nnCon, nnObj, nnJac, iiObj, ObjAdd,
	   usrfun,
	   prob->snLog, prob->snLog2, prob->sqLog, prob->snSTOP,
	   valJ, indJ, locJ,
	   bl, bu, hs, x, pi, rc,
	   &inform, nS, nInf, sInf, objective,
	   &miniw, &minrw,
	   prob->iu, prob->leniu, prob->ru, prob->lenru,
	   prob->iw, prob->leniw, prob->rw, prob->lenrw);

  for (i = 0; i < ne; i++) {
    indJ[i]--;
  }
  for (i = 0; i <= n; i++) {
    locJ[i]--;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void deleteSNOPT(snProblem* prob) {
  f_snend(prob->iw, prob->leniw, prob->rw, prob->lenrw);

  free(prob->iw);
  free(prob->rw);

  init2zero(prob);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
