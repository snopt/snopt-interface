#ifndef SNOPTPROBLEM_H
#define SNOPTPROBLEM_H
#define DLL_ATTR __declspec(dllexport)

#include "snopt.h"

/* File snoptProblem.hpp
 *   C++ interface for SNOPT and SQOPT
 *
 */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblem {
protected:
  snoptProblem();
  snoptProblem(const char*name);
  ~snoptProblem();

  void init2zero();

  char    Prob[30];

  int     initCalled, memCalled;

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
  DLL_ATTR void setProbName    (const char *Prob);
  DLL_ATTR void setPrintFile   (const char *prtname);

  DLL_ATTR int getParameter    (const char *stroptin, char *stroptout);
  DLL_ATTR int getIntParameter (const char *stropt,   int    &opt);
  DLL_ATTR int getRealParameter(const char *stropt,   double &opt);
  DLL_ATTR int setParameter    (const char *stroptin);
  DLL_ATTR int setIntParameter (const char *stropt,   int     opt);
  DLL_ATTR int setRealParameter(const char *stropt,   double  opt);

  DLL_ATTR void setUserI       (int    *iu, int leniu);
  DLL_ATTR void setUserR       (double *ru, int lenru);
  DLL_ATTR void setUserspace   (int    *iu, int leniu, double *ru, int lenru);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblemABC : public snoptProblem  {
protected:
  snoptProblemABC();
  snoptProblemABC(const char*name);
  ~snoptProblemABC();

  void init2zero();

  isnLog  snLog;
  isnLog2 snLog2;
  isqLog  sqLog;
  isnSTOP snSTOP;

public:
  DLL_ATTR void initialize     (const char *prtfile, int summOn);
  DLL_ATTR int  setSpecsFile   (const char *specname);

  DLL_ATTR void setLog         (isnLog snLog, isnLog2 snLog2, isqLog sqLog);
  DLL_ATTR void setSTOP        (isnSTOP snSTOP);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblemA : public snoptProblemABC {
public:
  DLL_ATTR snoptProblemA();
  DLL_ATTR snoptProblemA(const char *name);
  DLL_ATTR ~snoptProblemA();

  DLL_ATTR void setWorkspace(int neF, int n, int neA, int neG);
  DLL_ATTR int  computeJac(int neF, int n, snFunA usrfunA,
			   double *x, double *xlow, double*xupp,
			   int *&iAfun, int *&jAvar, double *&A, int &neA,
			   int *&iGfun, int *&jGvar, int &neG);

  DLL_ATTR int  solve(int starttype, int nF, int n, double ObjAdd,
		      int ObjRow, snFunA usrfunA,
		      double *xlow, double *xupp, double *Flow, double *Fupp,
		      double *x, int *xstate, double *xmul,
		      double *F, int *Fstate, double *Fmul,
		      int &nS, int &nInf, double &sInf);

  DLL_ATTR int  solve(int starttype, int nF, int n, double ObjAdd,
		      int ObjRow, snFunA usrfunA,
		      int *iAfun, int *jAvar, double *A, int neA,
		      int *iGfun, int *jGvar, int neG,
		      double *xlow, double *xupp, double *Flow, double *Fupp,
		      double *x, int *xstate, double *xmul,
		      double *F, int *Fstate, double *Fmul,
		      int &nS, int &nInf, double &sInf);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblemC : public snoptProblemABC {
public:
  DLL_ATTR snoptProblemC();
  DLL_ATTR snoptProblemC(const char*name);
  DLL_ATTR ~snoptProblemC();

  DLL_ATTR void setWorkspace(int m, int n, int ne, int negCon,
			     int nnCon, int nnObj, int nnJac);

  DLL_ATTR int solve(int starttype, int m, int n, int ne, int negCon,
		     int nnCon, int nnObj, int nnJac,
		     int iObj, double ObjAdd, snFunC usrfunC,
		     double *Jval, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs,
		     double *x, double *pi, double *rc,
		     int &nS, int &nInf, double &sInf, double &objective);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class snoptProblemB : public snoptProblemC {
public:
  DLL_ATTR snoptProblemB();
  DLL_ATTR snoptProblemB(const char*name);
  DLL_ATTR ~snoptProblemB();

  DLL_ATTR int solve(int starttype, int m, int n, int ne, int negCon,
		     int nnCon, int nnObj, int nnJac,
		     int iObj, double ObjAdd,
		     snConB funcon, snObjB funobj,
		     double *Jval, int *indJ, int *locJ,
		     double *bl, double *bu, int *hs,
		     double *x, double *pi, double *rc,
		     int &nS, int &nInf, double &sInf, double &objective);
};

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

class sqoptProblem : public snoptProblem {
private:
  isqLog  sqLog;
  void init2zero();

public:
  DLL_ATTR sqoptProblem();
  DLL_ATTR sqoptProblem(const char*name);
  DLL_ATTR ~sqoptProblem();

  DLL_ATTR void initialize  (const char *prtfile, int summOn);
  DLL_ATTR int  setSpecsFile(const char *specname);
  DLL_ATTR void setLog      (isqLog sqLog);
  DLL_ATTR void setWorkspace(int m, int n, int neA, int ncObj, int nnH);

  DLL_ATTR int solve(int starttype, sqFunHx qpHx,
		     int m, int n, int neA, int ncObj, int nnH,
		     int iObj, double ObjAdd,
		     double *A, int *indA, int *locA,
		     double *bl, double *bu, double *cObj,
		     int *eType, int *hs, double *x, double *pi, double *rc,
		     int &nS, int &nInf, double &sInf, double &objective);
};

#endif /* SNOPTPROBLEM_H */
