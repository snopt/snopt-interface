#include <assert.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "sqopt.h"
#include "sqoptProblem.hpp"

using namespace std;

static const char *sqversion =
  " ==============================\n\
   SQOPT C++ interface  2.2.0   ";
//  123456789|123456789|123456789|


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
snoptProblem::snoptProblem(const char *name, int *aiw, int aleniw, double *arw, int alenrw) {
  init2zero();
  sprintf(Prob, "%8s", name);

  if (aleniw >= 500 && alenrw >= 500) {
    if (aiw != 0 && arw != 0) {
      leniw = aleniw;
      lenrw = alenrw;
      iw    = aiw;
      rw    = arw;
      userWork  = 1;
    }
    else {
      allocI(aleniw);
      allocR(alenrw);
    }
    memCalled = 1;
  }
  else {
    allocI(500);
    allocR(500);
  }
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
snoptProblem::~snoptProblem() {
  f_sqend(iw, leniw, rw, lenrw);

  if (userWork == 0) {
    delete []rw;  delete []iw;
  }
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::init2zero() {
  initCalled = 0; memCalled = 0; userWork = 0;

  leniw = 0; lenrw = 0;
  iw    = 0; rw    = 0;

  leniu = 0; lenru = 0;
  iu    = 0; ru    = 0;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::allocI(int aleniw) {
  // Reset work array lengths.
  // Allocate new memory for work arrays.
  assert(aleniw >= 500);
  leniw = aleniw;
  iw    = new int[leniw];
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::allocR(int alenrw) {
  // Reset work array lengths.
  // Allocate new memory for work arrays.
  assert(alenrw >= 500);
  lenrw = alenrw;
  rw    = new double[lenrw];
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::reallocI(int aleniw) {
  int  tleniw = leniw;
  int    *tiw = iw;

  // Allocate new memory
  allocI(aleniw);

  // Copy old workspace into new.
  int mleniw = leniw < tleniw ? leniw : tleniw;
  memcpy(iw, tiw, mleniw*sizeof(int));

  // Delete temporary work arrays
  delete []tiw;

  setIntParameter((char*)"Total int workspace", leniw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::reallocR(int alenrw) {
  int  tlenrw = lenrw;
  double *trw = rw;

  // Allocate new memory
  allocR(alenrw);

  // Copy old workspace into new.
  int mlenrw = lenrw < tlenrw ? lenrw : tlenrw;
  memcpy(rw, trw, mlenrw*sizeof(double));

  // Delete temporary work arrays
  delete []trw;

  setIntParameter((char*)"Total real workspace   ", lenrw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setProbName(const char *name) {
  sprintf(Prob, "%8s", name);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setPrintFile(const char *prtname) {
  assert(initCalled == 1);

  int len = strlen(prtname);
  f_sqsetprintf(prtname, len, iw, leniw, rw, lenrw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setPrintFile(const char *prtname, int iprint) {
  assert(initCalled == 1);

  int len = strlen(prtname);
  f_sqsetprint(prtname, len, iprint, iw, leniw, rw, lenrw);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int snoptProblem::setParameter(const char *stropt) {
  assert(initCalled == 1);

  int errors, stropt_len = strlen(stropt);
  f_sqset(stropt, stropt_len, &errors, iw, leniw, rw, lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int snoptProblem::setIntParameter(const char *stropt, int opt) {
  assert(initCalled == 1);

  int errors, stropt_len = strlen(stropt);

  f_sqseti(stropt, stropt_len, opt, &errors,
	    iw, leniw, rw, lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int snoptProblem::getIntParameter(const char *stropt, int &opt) {
  assert(initCalled == 1);

  int errors, stropt_len = strlen(stropt);
  f_sqgeti(stropt, stropt_len, &opt, &errors,
	    iw, leniw, rw, lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int snoptProblem::setRealParameter(const char *stropt, double opt) {
  assert(initCalled == 1);

  int errors, stropt_len = strlen(stropt);
  f_sqsetr(stropt, stropt_len, opt, &errors,
	    iw, leniw, rw, lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int snoptProblem::getRealParameter(const char *stropt, double &opt) {
  assert(initCalled == 1);

  int errors, stropt_len = strlen(stropt);
  f_sqgetr(stropt, stropt_len, &opt, &errors,
	    iw, leniw, rw, lenrw);
  return errors;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setUserI(int *aiu, int aleniu) {
  leniu = aleniu;
  iu    = aiu;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setUserR(double *aru, int alenru) {
  lenru = alenru;
  ru    = aru;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void snoptProblem::setUserspace  (int*aiu,     int aleniu,
				   double *aru, int alenru) {
  leniu = aleniu;
  iu    = aiu;

  lenru = alenru;
  ru    = aru;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
sqoptProblem::sqoptProblem(const char *name,
			     int *aiw, int aleniw, double *arw, int alenrw) :
  snoptProblem(name,aiw,aleniw,arw,alenrw) {
  init2zero();
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
sqoptProblem::~sqoptProblem() {
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void sqoptProblem::init2zero() {
  sqLog = 0;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void sqoptProblem::initialize(const char*prtfile, int summOn) {
  int len = strlen(prtfile);

  if (summOn != 0) {
    std::cout << sqversion;
  }

  f_sqinitf(prtfile, len, summOn, iw, leniw, rw, lenrw);
  initCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void sqoptProblem::initialize(const char*prtfile, int iprint,
			      const char*sumfile, int isumm) {
  int plen, slen;
  plen = strlen(prtfile);
  slen = strlen(prtfile);

  if (isumm != 0) {
    std::cout << sqversion;
  }

  f_sqinit(prtfile, plen, iprint, sumfile, slen, isumm,
	   iw, leniw, rw, lenrw);
  initCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int sqoptProblem::setSpecsFile(const char *specname) {
  assert(initCalled == 1);

  int inform, len = strlen(specname);
  f_sqspecf(specname, len, &inform, iw, leniw, rw, lenrw);
  if(inform != 101){
    std::cerr << "Warning: unable to find specs file " <<
      specname << std::endl;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int sqoptProblem::setSpecsFile(const char *specname, int ispecs) {
  assert(initCalled == 1);

  int inform, len = strlen(specname);
  f_sqspec(specname, len, ispecs, &inform, iw, leniw, rw, lenrw);
  if(inform != 101){
    std::cerr << "Warning: unable to find specs file " <<
      specname << std::endl;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void sqoptProblem::setLog(isqLog asqLog) {
  sqLog  = asqLog;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void sqoptProblem::setWorkspace(int m, int n, int neA, int ncObj, int nnH) {
  assert(initCalled == 1);

  int inform, miniw, minrw;

  f_sqmem(&inform, m, n, neA, ncObj, nnH,
	   &miniw, &minrw, iw, leniw, rw, lenrw);

  if (miniw > leniw) { reallocI (miniw); }
  if (minrw > lenrw) { reallocR (minrw); }

  memCalled = 1;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int sqoptProblem::solve(int starttype, sqFunHx qpHx,
			int m, int n, int neA, int ncObj, int nnH,
			int iObj, double ObjAdd,
			double *A, int *indA, int *locA,
			double *bl, double *bu, double *cObj,
			int *eType, int *hs, double *x, double *pi, double *rc,
			int &nS, int &nInf, double &sInf, double &objective) {
  assert(initCalled == 1);

  int inform, sniObj, miniw, minrw;

  if (memCalled == 0) { setWorkspace(m, n, neA, ncObj, nnH); }

  for (int i = 0; i < neA; i++) {
    indA[i]++;
  }
  for (int i = 0; i <= n; i++) {
    locA[i]++;
  }

  sniObj = iObj+1;

  f_snkerq(starttype, qpHx, sqLog,
	   m, n, neA, ncObj, nnH,
	   sniObj, ObjAdd, Prob,
	   A, indA, locA, bl, bu, cObj,
	   eType, hs, x, pi, rc,
	   &inform, &nS, &nInf, &sInf, &objective,
	   &miniw, &minrw, iu, leniu, ru, lenru,
	   iw, leniw, rw, lenrw);

  for (int i = 0; i < neA; i++) {
    indA[i]--;
  }
  for (int i = 0; i <= n; i++) {
    locA[i]--;
  }

  return inform;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
