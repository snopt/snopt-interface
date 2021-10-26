#ifndef SQOPT_H
#define SQOPT_H

/*
 * File:  sqopt.h
 *   Header file for the SQOPT functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

  typedef void (*isqLog)
  ( int *Prob, char *ProbTag, int *Elastc, int *gotR, int *jstFea, int *feasbl,
    int *m, int *mBS, int *nnH, int *nS, int *jSq, int *jBr, int *jSr,
    int *linesP, int *linesS, int *itn, int *itQP, int *kPrc, int *lvlInf,
    double *pivot, double *step, int *nInf, double *sInf, double *wtInf,
    double *ObjPrt, double *condHz, double *djqPrt, double *rgNorm,
    int kBS[], double xBS[],
    int iw[], int *leniw );

  typedef void (*sqFunHx)
  ( int    *nnH, double x[], double Hx[], int *nState,
    char     cu[], int   *lencu,
    int      iu[], int   *leniu,
    double   ru[], int   *lenru );


  /* SQOPT */
  void f_sqinit ( const char *print, int plen, int iprint,
		  const char *summ,  int slen, int isumm,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqspec ( const char *specfile, int len, int ispecs, int *inform,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqinitf( const char *name, int len, int summOn,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqspecf( const char *specfile, int len, int *inform,
		  int iw[], int leniw, double rw[], int lenrw );

  void f_sqinitx( const char *print, int plen,
		  const char *summ,  int slen,
		  int iw[], int leniw, double rw[], int lenrw );

  void f_sqgeti ( const char *buffer, int len, int  *ivalue, int *errors,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqgetr ( const char *buffer, int len, double *ivalue, int *errors,
		  int iw[], int leniw, double rw[], int lenrw );

  void f_sqset  ( const char *buffer, int len, int *errors,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqseti ( const char *buffer, int len, int iopt, int *errors,
		  int iw[], int leniw, double rw[], int lenrw );
  void f_sqsetr ( const char *buffer, int len, double rvalue, int *errors,
		  int iw[], int leniw, double rw[], int lenrw );

  void f_sqsetprint ( const char *name, int len, int iprint,
		      int iw[], int leniw, double rw[], int lenrw );
  void f_sqsetprintf( const char *name, int len,
		      int iw[], int leniw, double rw[], int lenrw );
  void f_sqend ( int iw[], int leniw, double rw[], int lenrw );


  /* SQOPT */
  void f_snkerq ( int start, sqFunHx qpHx, isqLog sqLog,
		  int m, int n, int neA, int ncObj, int nnH,
		  int iobj, double objadd, const char *name,
		  double A[], int indA[], int locA[],
		  double bl[], double bu[], double cObj[],
		  int eType[], int hs[], double x[],
		  double pi[], double rc[], int *inform,
		  int *ns, int *ninf, double *sinf, double *obj,
		  int *miniw, int *minrw,
		  int iu[], int leniu, double ru[], int lenru,
		  int iw[], int leniw, double rw[], int lenrw );

  void f_sqmem  ( int *info, int m, int n, int neA, int ncObj, int nnH,
		  int *miniw, int *minrw,
		  int iw[], int leniw, double rw[], int lenrw );
#ifdef __cplusplus
}
#endif

#endif /* SQOPT_H */
