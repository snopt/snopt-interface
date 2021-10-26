#ifndef SQOPTPROBLEM_H
#define SQOPTPROBLEM_H

#include "sqopt.h"

/* File sqoptProblem.hpp
 *   C++ interface for SQOPT
 *
 */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblem {
protected:
  // default constructor
  snoptProblem(const char*name, int *iw, int aleniw, double *rw, int alenrw);

  // delegated constructors
  snoptProblem() :
    snoptProblem("        ", 0, 0, 0, 0) {};
  snoptProblem(int aleniw, int alenrw) :
    snoptProblem("        ", 0, aleniw, 0, alenrw) {};
  snoptProblem(int *aiw, int aleniw, double *arw, int alenrw) :
    snoptProblem("        ", aiw, aleniw, arw, alenrw) {} ;
  snoptProblem(const char*name) :
    snoptProblem(name, 0, 0, 0, 0) {};
  snoptProblem(const char*name, int aleniw, int alenrw) :
    snoptProblem(name, 0, aleniw, 0, alenrw) {};

  ~snoptProblem();

  void init2zero();

  char    Prob[30];

  int     initCalled, memCalled, userWork;

  int     leniw, lenrw;
  double *rw;
  int    *iw;

  int     lenru, leniu;
  double *ru;
  int    *iu;

  void allocI    (int leniw);
  void allocR    (int lenrw);
  void reallocI  (int leniw);
  void reallocR  (int lenrw);

public:
  void setProbName    (const char *Prob);
  void setPrintFile   (const char *prtname);
  void setPrintFile   (const char *prtname, int iprint);

  int getIntParameter (const char *stropt,   int    &opt);
  int getRealParameter(const char *stropt,   double &opt);
  int setParameter    (const char *stroptin);
  int setIntParameter (const char *stropt,   int     opt);
  int setRealParameter(const char *stropt,   double  opt);

  void setUserI       (int    *iu, int leniu);
  void setUserR       (double *ru, int lenru);
  void setUserspace   (int    *iu, int leniu, double *ru, int lenru);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class sqoptProblem : public snoptProblem {
private:
  isqLog  sqLog;
  void init2zero();

public:
  // default constructor
  sqoptProblem(const char*name, int *iw, int aleniw, double *rw, int alenrw);

  // delegated constructors
  sqoptProblem() :
    sqoptProblem("        ", 0, 0, 0, 0) {};
  sqoptProblem(const char*name) :
    sqoptProblem(name, 0, 0, 0, 0) {};
  sqoptProblem(int aleniw, int alenrw) :
    sqoptProblem("        ", 0, aleniw, 0, alenrw) {};
  sqoptProblem(int *aiw, int aleniw, double *arw, int alenrw) :
    sqoptProblem("        ", aiw, aleniw, arw, alenrw) {};
  sqoptProblem(const char*name, int aleniw, int alenrw) :
    sqoptProblem(name, 0, aleniw, 0, alenrw) {};

  ~sqoptProblem();

  void initialize  (const char *prtfile, int summOn);
  void initialize  (const char *prtfile, int iprint, const char *sumfile, int isumm);

  int  setSpecsFile(const char *specname);
  int  setSpecsFile(const char *specname, int ispecs);

  void setLog      (isqLog sqLog);
  void setWorkspace(int m, int n, int neA, int ncObj, int nnH);

  int solve(int starttype, sqFunHx qpHx,
	    int m, int n, int neA, int ncObj, int nnH,
	    int iObj, double ObjAdd,
	    double *A, int *indA, int *locA,
	    double *bl, double *bu, double *cObj,
	    int *eType, int *hs, double *x, double *pi, double *rc,
	    int &nS, int &nInf, double &sInf, double &objective);
};

#endif /* SQOPTPROBLEM_H */
