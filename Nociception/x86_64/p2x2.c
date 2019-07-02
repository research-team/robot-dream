/* Created by Language version: 7.5.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__p2x2
#define _nrn_initial _nrn_initial__p2x2
#define nrn_cur _nrn_cur__p2x2
#define _nrn_current _nrn_current__p2x2
#define nrn_jacob _nrn_jacob__p2x2
#define nrn_state _nrn_state__p2x2
#define _net_receive _net_receive__p2x2 
#define kstates kstates__p2x2 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gmax _p[0]
#define Ev _p[1]
#define i _p[2]
#define g _p[3]
#define C1 _p[4]
#define C2 _p[5]
#define C3 _p[6]
#define C4 _p[7]
#define F5 _p[8]
#define O6 _p[9]
#define O7 _p[10]
#define F8 _p[11]
#define k1 _p[12]
#define k2 _p[13]
#define k3 _p[14]
#define DC1 _p[15]
#define DC2 _p[16]
#define DC3 _p[17]
#define DC4 _p[18]
#define DF5 _p[19]
#define DO6 _p[20]
#define DO7 _p[21]
#define DF8 _p[22]
#define _g _p[23]
#define _nd_area  *_ppvar[0]._pval
#define patp	*_ppvar[2]._pval
#define _p_patp	_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
#define alfa2 alfa2_p2x2
 double alfa2 = 0.246;
#define alfa1 alfa1_p2x2
 double alfa1 = 1088;
#define beta2 beta2_p2x2
 double beta2 = 0.033;
#define beta1 beta1_p2x2
 double beta1 = 540;
#define delta delta_p2x2
 double delta = 3718;
#define eps2 eps2_p2x2
 double eps2 = 3.2;
#define eps1 eps1_p2x2
 double eps1 = 79;
#define gamma gamma_p2x2
 double gamma = 43.54;
#define koff3 koff3_p2x2
 double koff3 = 6822;
#define koff2 koff2_p2x2
 double koff2 = 380;
#define koff1 koff1_p2x2
 double koff1 = 0.019;
#define kon3 kon3_p2x2
 double kon3 = 11.6;
#define kon2 kon2_p2x2
 double kon2 = 16.3;
#define kon1 kon1_p2x2
 double kon1 = 15.98;
#define sigma2 sigma2_p2x2
 double sigma2 = 4.53;
#define sigma1 sigma1_p2x2
 double sigma1 = 31.16;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "kon1_p2x2", "/uM",
 "kon2_p2x2", "/uM",
 "kon3_p2x2", "/uM",
 "koff1_p2x2", "/s",
 "koff2_p2x2", "/s",
 "koff3_p2x2", "/s",
 "delta_p2x2", "/s",
 "gamma_p2x2", "/s",
 "alfa1_p2x2", "/s",
 "beta1_p2x2", "/s",
 "alfa2_p2x2", "/s",
 "beta2_p2x2", "/s",
 "sigma1_p2x2", "/s",
 "eps1_p2x2", "/s",
 "sigma2_p2x2", "/s",
 "eps2_p2x2", "/s",
 "gmax", "pS",
 "Ev", "mV",
 "i", "nA",
 "g", "pS",
 "patp", "uM",
 0,0
};
 static double C40 = 0;
 static double C30 = 0;
 static double C20 = 0;
 static double C10 = 0;
 static double F80 = 0;
 static double F50 = 0;
 static double O70 = 0;
 static double O60 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "kon1_p2x2", &kon1_p2x2,
 "kon2_p2x2", &kon2_p2x2,
 "kon3_p2x2", &kon3_p2x2,
 "koff1_p2x2", &koff1_p2x2,
 "koff2_p2x2", &koff2_p2x2,
 "koff3_p2x2", &koff3_p2x2,
 "delta_p2x2", &delta_p2x2,
 "gamma_p2x2", &gamma_p2x2,
 "alfa1_p2x2", &alfa1_p2x2,
 "beta1_p2x2", &beta1_p2x2,
 "alfa2_p2x2", &alfa2_p2x2,
 "beta2_p2x2", &beta2_p2x2,
 "sigma1_p2x2", &sigma1_p2x2,
 "eps1_p2x2", &eps1_p2x2,
 "sigma2_p2x2", &sigma2_p2x2,
 "eps2_p2x2", &eps2_p2x2,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"p2x2",
 "gmax",
 "Ev",
 0,
 "i",
 "g",
 0,
 "C1",
 "C2",
 "C3",
 "C4",
 "F5",
 "O6",
 "O7",
 "F8",
 0,
 "patp",
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 24, _prop);
 	/*initialize range parameters*/
 	gmax = 32.4;
 	Ev = -40;
  }
 	_prop->param = _p;
 	_prop->param_size = 24;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _p2x2_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 24, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 p2x2 /Users/sulgod/rd/Nociception/x86_64/p2x2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 extern double *_getelm();
 
#define _MATELM1(_row,_col)	*(_getelm(_row + 1, _col + 1))
 
#define _RHS1(_arg) _coef1[_arg + 1]
 static double *_coef1;
 
#define _linmat1  1
 static void* _sparseobj1;
 static void* _cvsparseobj1;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[8], _dlist1[8]; static double *_temp1;
 static int kstates();
 
static int kstates ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<8;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = kon1 * patp ;
   k2 = kon2 * patp ;
   k3 = kon3 * patp ;
   /* ~ C1 <-> C2 ( k1 , koff1 )*/
 f_flux =  k1 * C1 ;
 b_flux =  koff1 * C2 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  k1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  koff1 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ C2 <-> C3 ( k2 , koff2 )*/
 f_flux =  k2 * C2 ;
 b_flux =  koff2 * C3 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  k2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff2 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ C3 <-> C4 ( k3 , koff3 )*/
 f_flux =  k3 * C3 ;
 b_flux =  koff3 * C4 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  k3 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  koff3 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C4 <-> F5 ( delta , gamma )*/
 f_flux =  delta * C4 ;
 b_flux =  gamma * F5 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  delta ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  gamma ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ F5 <-> O6 ( beta1 , alfa1 )*/
 f_flux =  beta1 * F5 ;
 b_flux =  alfa1 * O6 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  beta1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 7 ,5)  -= _term;
 _term =  alfa1 ;
 _MATELM1( 5 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ F5 <-> O7 ( beta2 , alfa2 )*/
 f_flux =  beta2 * F5 ;
 b_flux =  alfa2 * O7 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  beta2 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 6 ,5)  -= _term;
 _term =  alfa2 ;
 _MATELM1( 5 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ F8 <-> O6 ( eps1 , sigma1 )*/
 f_flux =  eps1 * F8 ;
 b_flux =  sigma1 * O6 ;
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  eps1 ;
 _MATELM1( 7 ,0)  -= _term;
 _term =  sigma1 ;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ F8 <-> O7 ( eps2 , sigma2 )*/
 f_flux =  eps2 * F8 ;
 b_flux =  sigma2 * O7 ;
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  eps2 ;
 _MATELM1( 6 ,0)  -= _term;
 _term =  sigma2 ;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
   /* C1 + C2 + C3 + C4 + F5 + O6 + O7 + F8 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= F8 ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= O7 ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= O6 ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= F5 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C4 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= C3 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= C1 ;
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<8;_i++) _p[_dlist1[_i]] = 0.0;}
 k1 = kon1 * patp ;
 k2 = kon2 * patp ;
 k3 = kon3 * patp ;
 /* ~ C1 <-> C2 ( k1 , koff1 )*/
 f_flux =  k1 * C1 ;
 b_flux =  koff1 * C2 ;
 DC1 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> C3 ( k2 , koff2 )*/
 f_flux =  k2 * C2 ;
 b_flux =  koff2 * C3 ;
 DC2 -= (f_flux - b_flux);
 DC3 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C3 <-> C4 ( k3 , koff3 )*/
 f_flux =  k3 * C3 ;
 b_flux =  koff3 * C4 ;
 DC3 -= (f_flux - b_flux);
 DC4 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C4 <-> F5 ( delta , gamma )*/
 f_flux =  delta * C4 ;
 b_flux =  gamma * F5 ;
 DC4 -= (f_flux - b_flux);
 DF5 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ F5 <-> O6 ( beta1 , alfa1 )*/
 f_flux =  beta1 * F5 ;
 b_flux =  alfa1 * O6 ;
 DF5 -= (f_flux - b_flux);
 DO6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ F5 <-> O7 ( beta2 , alfa2 )*/
 f_flux =  beta2 * F5 ;
 b_flux =  alfa2 * O7 ;
 DF5 -= (f_flux - b_flux);
 DO7 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ F8 <-> O6 ( eps1 , sigma1 )*/
 f_flux =  eps1 * F8 ;
 b_flux =  sigma1 * O6 ;
 DF8 -= (f_flux - b_flux);
 DO6 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ F8 <-> O7 ( eps2 , sigma2 )*/
 f_flux =  eps2 * F8 ;
 b_flux =  sigma2 * O7 ;
 DF8 -= (f_flux - b_flux);
 DO7 += (f_flux - b_flux);
 
 /*REACTION*/
   /* C1 + C2 + C3 + C4 + F5 + O6 + O7 + F8 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<8;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = kon1 * patp ;
 k2 = kon2 * patp ;
 k3 = kon3 * patp ;
 /* ~ C1 <-> C2 ( k1 , koff1 )*/
 _term =  k1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  koff1 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ C2 <-> C3 ( k2 , koff2 )*/
 _term =  k2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  koff2 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ C3 <-> C4 ( k3 , koff3 )*/
 _term =  k3 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  koff3 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C4 <-> F5 ( delta , gamma )*/
 _term =  delta ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  gamma ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ F5 <-> O6 ( beta1 , alfa1 )*/
 _term =  beta1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 7 ,5)  -= _term;
 _term =  alfa1 ;
 _MATELM1( 5 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ F5 <-> O7 ( beta2 , alfa2 )*/
 _term =  beta2 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 6 ,5)  -= _term;
 _term =  alfa2 ;
 _MATELM1( 5 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ F8 <-> O6 ( eps1 , sigma1 )*/
 _term =  eps1 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 7 ,0)  -= _term;
 _term =  sigma1 ;
 _MATELM1( 0 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ F8 <-> O7 ( eps2 , sigma2 )*/
 _term =  eps2 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 6 ,0)  -= _term;
 _term =  sigma2 ;
 _MATELM1( 0 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
   /* C1 + C2 + C3 + C4 + F5 + O6 + O7 + F8 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 8;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 8; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse(&_cvsparseobj1, 8, _dlist1, _p, _ode_matsol1, &_coef1);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  C4 = C40;
  C3 = C30;
  C2 = C20;
  C1 = C10;
  F8 = F80;
  F5 = F50;
  O7 = O70;
  O6 = O60;
 {
   C1 = 1.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = gmax * ( O6 + O7 ) * ( 1e+9 ) ;
   i = g * ( v - Ev ) ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 { error = sparse(&_sparseobj1, 8, _slist1, _dlist1, _p, &t, dt, kstates,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 65 in file p2x2.mod:\n	SOLVE kstates METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
    if (secondorder) {
    int _i;
    for (_i = 0; _i < 8; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(F8) - _p;  _dlist1[0] = &(DF8) - _p;
 _slist1[1] = &(C4) - _p;  _dlist1[1] = &(DC4) - _p;
 _slist1[2] = &(C3) - _p;  _dlist1[2] = &(DC3) - _p;
 _slist1[3] = &(C2) - _p;  _dlist1[3] = &(DC2) - _p;
 _slist1[4] = &(C1) - _p;  _dlist1[4] = &(DC1) - _p;
 _slist1[5] = &(F5) - _p;  _dlist1[5] = &(DF5) - _p;
 _slist1[6] = &(O7) - _p;  _dlist1[6] = &(DO7) - _p;
 _slist1[7] = &(O6) - _p;  _dlist1[7] = &(DO6) - _p;
_first = 0;
}
