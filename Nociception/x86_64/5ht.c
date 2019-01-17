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
 
#define nrn_init _nrn_init__r5ht3a
#define _nrn_initial _nrn_initial__r5ht3a
#define nrn_cur _nrn_cur__r5ht3a
#define _nrn_current _nrn_current__r5ht3a
#define nrn_jacob _nrn_jacob__r5ht3a
#define nrn_state _nrn_state__r5ht3a
#define _net_receive _net_receive__r5ht3a 
#define kstates kstates__r5ht3a 
 
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
#define Re _p[4]
#define AR _p[5]
#define A2R _p[6]
#define A3R _p[7]
#define Ob _p[8]
#define Oi _p[9]
#define Ol _p[10]
#define C1 _p[11]
#define C2 _p[12]
#define AD _p[13]
#define A2D _p[14]
#define A3D _p[15]
#define D _p[16]
#define k1 _p[17]
#define k2 _p[18]
#define k3 _p[19]
#define d1 _p[20]
#define d2 _p[21]
#define d3 _p[22]
#define DRe _p[23]
#define DAR _p[24]
#define DA2R _p[25]
#define DA3R _p[26]
#define DOb _p[27]
#define DOi _p[28]
#define DOl _p[29]
#define DC1 _p[30]
#define DC2 _p[31]
#define DAD _p[32]
#define DA2D _p[33]
#define DA3D _p[34]
#define DD _p[35]
#define _g _p[36]
#define _nd_area  *_ppvar[0]._pval
#define serotonin	*_ppvar[2]._pval
#define _p_serotonin	_ppvar[2]._pval
 
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
#define d42 d42_r5ht3a
 double d42 = 1.5;
#define d41 d41_r5ht3a
 double d41 = 0.01;
#define d32 d32_r5ht3a
 double d32 = 0.81;
#define d31 d31_r5ht3a
 double d31 = 3e+07;
#define d22 d22_r5ht3a
 double d22 = 0.54;
#define d21 d21_r5ht3a
 double d21 = 4e+07;
#define d12 d12_r5ht3a
 double d12 = 0.27;
#define d11 d11_r5ht3a
 double d11 = 5e+07;
#define k52 k52_r5ht3a
 double k52 = 150;
#define k51 k51_r5ht3a
 double k51 = 165;
#define k42 k42_r5ht3a
 double k42 = 300;
#define k41 k41_r5ht3a
 double k41 = 55;
#define k32 k32_r5ht3a
 double k32 = 450;
#define k31 k31_r5ht3a
 double k31 = 3e+07;
#define k22 k22_r5ht3a
 double k22 = 300;
#define k21 k21_r5ht3a
 double k21 = 4e+07;
#define k12 k12_r5ht3a
 double k12 = 150;
#define k11 k11_r5ht3a
 double k11 = 5e+07;
#define o72 o72_r5ht3a
 double o72 = 5400;
#define o71 o71_r5ht3a
 double o71 = 5100;
#define o62 o62_r5ht3a
 double o62 = 1.2;
#define o61 o61_r5ht3a
 double o61 = 0.01;
#define o52 o52_r5ht3a
 double o52 = 11500;
#define o51 o51_r5ht3a
 double o51 = 11;
#define o42 o42_r5ht3a
 double o42 = 350;
#define o41 o41_r5ht3a
 double o41 = 1500;
#define o32 o32_r5ht3a
 double o32 = 6500;
#define o31 o31_r5ht3a
 double o31 = 18000;
#define o12 o12_r5ht3a
 double o12 = 330;
#define o11 o11_r5ht3a
 double o11 = 0.02;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "k11_r5ht3a", "/molar",
 "k21_r5ht3a", "/molar",
 "k31_r5ht3a", "/molar",
 "d11_r5ht3a", "/molar",
 "d21_r5ht3a", "/molar",
 "d31_r5ht3a", "/molar",
 "gmax", "pS",
 "Ev", "mV",
 "i", "nA",
 "g", "pS",
 "serotonin", "uM",
 0,0
};
 static double A3D0 = 0;
 static double A2D0 = 0;
 static double AD0 = 0;
 static double A3R0 = 0;
 static double A2R0 = 0;
 static double AR0 = 0;
 static double C20 = 0;
 static double C10 = 0;
 static double D0 = 0;
 static double Ol0 = 0;
 static double Oi0 = 0;
 static double Ob0 = 0;
 static double Re0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "k11_r5ht3a", &k11_r5ht3a,
 "k12_r5ht3a", &k12_r5ht3a,
 "k21_r5ht3a", &k21_r5ht3a,
 "k22_r5ht3a", &k22_r5ht3a,
 "k31_r5ht3a", &k31_r5ht3a,
 "k32_r5ht3a", &k32_r5ht3a,
 "k41_r5ht3a", &k41_r5ht3a,
 "k42_r5ht3a", &k42_r5ht3a,
 "k51_r5ht3a", &k51_r5ht3a,
 "k52_r5ht3a", &k52_r5ht3a,
 "o11_r5ht3a", &o11_r5ht3a,
 "o12_r5ht3a", &o12_r5ht3a,
 "o31_r5ht3a", &o31_r5ht3a,
 "o32_r5ht3a", &o32_r5ht3a,
 "o41_r5ht3a", &o41_r5ht3a,
 "o42_r5ht3a", &o42_r5ht3a,
 "o51_r5ht3a", &o51_r5ht3a,
 "o52_r5ht3a", &o52_r5ht3a,
 "o61_r5ht3a", &o61_r5ht3a,
 "o62_r5ht3a", &o62_r5ht3a,
 "o71_r5ht3a", &o71_r5ht3a,
 "o72_r5ht3a", &o72_r5ht3a,
 "d11_r5ht3a", &d11_r5ht3a,
 "d12_r5ht3a", &d12_r5ht3a,
 "d21_r5ht3a", &d21_r5ht3a,
 "d22_r5ht3a", &d22_r5ht3a,
 "d31_r5ht3a", &d31_r5ht3a,
 "d32_r5ht3a", &d32_r5ht3a,
 "d41_r5ht3a", &d41_r5ht3a,
 "d42_r5ht3a", &d42_r5ht3a,
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
"r5ht3a",
 "gmax",
 "Ev",
 0,
 "i",
 "g",
 0,
 "Re",
 "AR",
 "A2R",
 "A3R",
 "Ob",
 "Oi",
 "Ol",
 "C1",
 "C2",
 "AD",
 "A2D",
 "A3D",
 "D",
 0,
 "serotonin",
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
 	_p = nrn_prop_data_alloc(_mechtype, 37, _prop);
 	/*initialize range parameters*/
 	gmax = 0.31;
 	Ev = 28;
  }
 	_prop->param = _p;
 	_prop->param_size = 37;
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

 void _5ht_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 37, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 r5ht3a /Users/sulgod/rd/Nociception/x86_64/5ht.mod\n");
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
 static int _slist1[13], _dlist1[13]; static double *_temp1;
 static int kstates();
 
static int kstates ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<13;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = k11 * serotonin ;
   k2 = k21 * serotonin ;
   k3 = k31 * serotonin ;
   d1 = d11 * serotonin ;
   d2 = d21 * serotonin ;
   d3 = d31 * serotonin ;
   /* ~ Re <-> AR ( k1 , k12 )*/
 f_flux =  k1 * Re ;
 b_flux =  k12 * AR ;
 _RHS1( 12) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  k1 ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 6 ,12)  -= _term;
 _term =  k12 ;
 _MATELM1( 12 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ Re <-> D ( d41 , d42 )*/
 f_flux =  d41 * Re ;
 b_flux =  d42 * D ;
 _RHS1( 12) -= (f_flux - b_flux);
 
 _term =  d41 ;
 _MATELM1( 12 ,12)  += _term;
 _term =  d42 ;
 _MATELM1( 12 ,0)  -= _term;
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , k22 )*/
 f_flux =  k2 * AR ;
 b_flux =  k22 * A2R ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  k2 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  k22 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , k32 )*/
 f_flux =  k3 * A2R ;
 b_flux =  k32 * A3R ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  k3 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  k32 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Ob ( k41 , k42 )*/
 f_flux =  k41 * A3R ;
 b_flux =  k42 * Ob ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 11) += (f_flux - b_flux);
 
 _term =  k41 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 11 ,4)  -= _term;
 _term =  k42 ;
 _MATELM1( 4 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Oi ( k51 , k52 )*/
 f_flux =  k51 * A3R ;
 b_flux =  k52 * Oi ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 10) += (f_flux - b_flux);
 
 _term =  k51 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 10 ,4)  -= _term;
 _term =  k52 ;
 _MATELM1( 4 ,10)  -= _term;
 _MATELM1( 10 ,10)  += _term;
 /*REACTION*/
  /* ~ Ol <-> A3R ( o11 , o12 )*/
 f_flux =  o11 * Ol ;
 b_flux =  o12 * A3R ;
 _RHS1( 9) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  o11 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 4 ,9)  -= _term;
 _term =  o12 ;
 _MATELM1( 9 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ Ol <-> C1 ( o51 , o52 )*/
 f_flux =  o51 * Ol ;
 b_flux =  o52 * C1 ;
 _RHS1( 9) -= (f_flux - b_flux);
 _RHS1( 8) += (f_flux - b_flux);
 
 _term =  o51 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 8 ,9)  -= _term;
 _term =  o52 ;
 _MATELM1( 9 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ C1 <-> Oi ( o41 , o42 )*/
 f_flux =  o41 * C1 ;
 b_flux =  o42 * Oi ;
 _RHS1( 8) -= (f_flux - b_flux);
 _RHS1( 10) += (f_flux - b_flux);
 
 _term =  o41 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 10 ,8)  -= _term;
 _term =  o42 ;
 _MATELM1( 8 ,10)  -= _term;
 _MATELM1( 10 ,10)  += _term;
 /*REACTION*/
  /* ~ C1 <-> Ob ( o31 , o32 )*/
 f_flux =  o31 * C1 ;
 b_flux =  o32 * Ob ;
 _RHS1( 8) -= (f_flux - b_flux);
 _RHS1( 11) += (f_flux - b_flux);
 
 _term =  o31 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 11 ,8)  -= _term;
 _term =  o32 ;
 _MATELM1( 8 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ A3D <-> Ol ( o61 , o62 )*/
 f_flux =  o61 * A3D ;
 b_flux =  o62 * Ol ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 9) += (f_flux - b_flux);
 
 _term =  o61 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 9 ,1)  -= _term;
 _term =  o62 ;
 _MATELM1( 1 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ C2 <-> C1 ( o71 , o72 )*/
 f_flux =  o71 * C2 ;
 b_flux =  o72 * C1 ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 8) += (f_flux - b_flux);
 
 _term =  o71 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 8 ,7)  -= _term;
 _term =  o72 ;
 _MATELM1( 7 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ D <-> AD ( d11 , d12 )*/
 f_flux =  d11 * D ;
 b_flux =  d12 * AD ;
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  d11 ;
 _MATELM1( 3 ,0)  -= _term;
 _term =  d12 ;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ AD <-> A2D ( d21 , d22 )*/
 f_flux =  d21 * AD ;
 b_flux =  d22 * A2D ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  d21 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  d22 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ A2D <-> A3D ( d31 , d32 )*/
 f_flux =  d31 * A2D ;
 b_flux =  d32 * A3D ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  d31 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  d32 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ob + Oi + Ol + C1 + C2 + AD + A2D + A3D + D = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= D ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= A3D ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= A2D ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= AD ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 8) = 1;
 _RHS1(0) -= C1 ;
 _MATELM1(0, 9) = 1;
 _RHS1(0) -= Ol ;
 _MATELM1(0, 10) = 1;
 _RHS1(0) -= Oi ;
 _MATELM1(0, 11) = 1;
 _RHS1(0) -= Ob ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= A3R ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= A2R ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= AR ;
 _MATELM1(0, 12) = 1;
 _RHS1(0) -= Re ;
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<13;_i++) _p[_dlist1[_i]] = 0.0;}
 k1 = k11 * serotonin ;
 k2 = k21 * serotonin ;
 k3 = k31 * serotonin ;
 d1 = d11 * serotonin ;
 d2 = d21 * serotonin ;
 d3 = d31 * serotonin ;
 /* ~ Re <-> AR ( k1 , k12 )*/
 f_flux =  k1 * Re ;
 b_flux =  k12 * AR ;
 DRe -= (f_flux - b_flux);
 DAR += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Re <-> D ( d41 , d42 )*/
 f_flux =  d41 * Re ;
 b_flux =  d42 * D ;
 DRe -= (f_flux - b_flux);
 DD += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , k22 )*/
 f_flux =  k2 * AR ;
 b_flux =  k22 * A2R ;
 DAR -= (f_flux - b_flux);
 DA2R += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , k32 )*/
 f_flux =  k3 * A2R ;
 b_flux =  k32 * A3R ;
 DA2R -= (f_flux - b_flux);
 DA3R += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3R <-> Ob ( k41 , k42 )*/
 f_flux =  k41 * A3R ;
 b_flux =  k42 * Ob ;
 DA3R -= (f_flux - b_flux);
 DOb += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3R <-> Oi ( k51 , k52 )*/
 f_flux =  k51 * A3R ;
 b_flux =  k52 * Oi ;
 DA3R -= (f_flux - b_flux);
 DOi += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Ol <-> A3R ( o11 , o12 )*/
 f_flux =  o11 * Ol ;
 b_flux =  o12 * A3R ;
 DOl -= (f_flux - b_flux);
 DA3R += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Ol <-> C1 ( o51 , o52 )*/
 f_flux =  o51 * Ol ;
 b_flux =  o52 * C1 ;
 DOl -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C1 <-> Oi ( o41 , o42 )*/
 f_flux =  o41 * C1 ;
 b_flux =  o42 * Oi ;
 DC1 -= (f_flux - b_flux);
 DOi += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C1 <-> Ob ( o31 , o32 )*/
 f_flux =  o31 * C1 ;
 b_flux =  o32 * Ob ;
 DC1 -= (f_flux - b_flux);
 DOb += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3D <-> Ol ( o61 , o62 )*/
 f_flux =  o61 * A3D ;
 b_flux =  o62 * Ol ;
 DA3D -= (f_flux - b_flux);
 DOl += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> C1 ( o71 , o72 )*/
 f_flux =  o71 * C2 ;
 b_flux =  o72 * C1 ;
 DC2 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ D <-> AD ( d11 , d12 )*/
 f_flux =  d11 * D ;
 b_flux =  d12 * AD ;
 DD -= (f_flux - b_flux);
 DAD += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ AD <-> A2D ( d21 , d22 )*/
 f_flux =  d21 * AD ;
 b_flux =  d22 * A2D ;
 DAD -= (f_flux - b_flux);
 DA2D += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A2D <-> A3D ( d31 , d32 )*/
 f_flux =  d31 * A2D ;
 b_flux =  d32 * A3D ;
 DA2D -= (f_flux - b_flux);
 DA3D += (f_flux - b_flux);
 
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ob + Oi + Ol + C1 + C2 + AD + A2D + A3D + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<13;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = k11 * serotonin ;
 k2 = k21 * serotonin ;
 k3 = k31 * serotonin ;
 d1 = d11 * serotonin ;
 d2 = d21 * serotonin ;
 d3 = d31 * serotonin ;
 /* ~ Re <-> AR ( k1 , k12 )*/
 _term =  k1 ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 6 ,12)  -= _term;
 _term =  k12 ;
 _MATELM1( 12 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ Re <-> D ( d41 , d42 )*/
 _term =  d41 ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 0 ,12)  -= _term;
 _term =  d42 ;
 _MATELM1( 12 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , k22 )*/
 _term =  k2 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  k22 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , k32 )*/
 _term =  k3 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  k32 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Ob ( k41 , k42 )*/
 _term =  k41 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 11 ,4)  -= _term;
 _term =  k42 ;
 _MATELM1( 4 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Oi ( k51 , k52 )*/
 _term =  k51 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 10 ,4)  -= _term;
 _term =  k52 ;
 _MATELM1( 4 ,10)  -= _term;
 _MATELM1( 10 ,10)  += _term;
 /*REACTION*/
  /* ~ Ol <-> A3R ( o11 , o12 )*/
 _term =  o11 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 4 ,9)  -= _term;
 _term =  o12 ;
 _MATELM1( 9 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ Ol <-> C1 ( o51 , o52 )*/
 _term =  o51 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 8 ,9)  -= _term;
 _term =  o52 ;
 _MATELM1( 9 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ C1 <-> Oi ( o41 , o42 )*/
 _term =  o41 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 10 ,8)  -= _term;
 _term =  o42 ;
 _MATELM1( 8 ,10)  -= _term;
 _MATELM1( 10 ,10)  += _term;
 /*REACTION*/
  /* ~ C1 <-> Ob ( o31 , o32 )*/
 _term =  o31 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 11 ,8)  -= _term;
 _term =  o32 ;
 _MATELM1( 8 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ A3D <-> Ol ( o61 , o62 )*/
 _term =  o61 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 9 ,1)  -= _term;
 _term =  o62 ;
 _MATELM1( 1 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ C2 <-> C1 ( o71 , o72 )*/
 _term =  o71 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 8 ,7)  -= _term;
 _term =  o72 ;
 _MATELM1( 7 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ D <-> AD ( d11 , d12 )*/
 _term =  d11 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 3 ,0)  -= _term;
 _term =  d12 ;
 _MATELM1( 0 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ AD <-> A2D ( d21 , d22 )*/
 _term =  d21 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  d22 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ A2D <-> A3D ( d31 , d32 )*/
 _term =  d31 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  d32 ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ob + Oi + Ol + C1 + C2 + AD + A2D + A3D + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 13;}
 
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
	for (_i=0; _i < 13; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse(&_cvsparseobj1, 13, _dlist1, _p, _ode_matsol1, &_coef1);
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
  A3D = A3D0;
  A2D = A2D0;
  AD = AD0;
  A3R = A3R0;
  A2R = A2R0;
  AR = AR0;
  C2 = C20;
  C1 = C10;
  D = D0;
  Ol = Ol0;
  Oi = Oi0;
  Ob = Ob0;
  Re = Re0;
 {
   Re = 1.0 ;
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
   g = gmax * ( Ol + Oi + Ob ) ;
   i = ( 1e-3 ) * g * ( v - Ev ) ;
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
 { error = sparse(&_sparseobj1, 13, _slist1, _dlist1, _p, &t, dt, kstates,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 89 in file 5ht.mod:\n	SOLVE kstates METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
    if (secondorder) {
    int _i;
    for (_i = 0; _i < 13; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 }}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(D) - _p;  _dlist1[0] = &(DD) - _p;
 _slist1[1] = &(A3D) - _p;  _dlist1[1] = &(DA3D) - _p;
 _slist1[2] = &(A2D) - _p;  _dlist1[2] = &(DA2D) - _p;
 _slist1[3] = &(AD) - _p;  _dlist1[3] = &(DAD) - _p;
 _slist1[4] = &(A3R) - _p;  _dlist1[4] = &(DA3R) - _p;
 _slist1[5] = &(A2R) - _p;  _dlist1[5] = &(DA2R) - _p;
 _slist1[6] = &(AR) - _p;  _dlist1[6] = &(DAR) - _p;
 _slist1[7] = &(C2) - _p;  _dlist1[7] = &(DC2) - _p;
 _slist1[8] = &(C1) - _p;  _dlist1[8] = &(DC1) - _p;
 _slist1[9] = &(Ol) - _p;  _dlist1[9] = &(DOl) - _p;
 _slist1[10] = &(Oi) - _p;  _dlist1[10] = &(DOi) - _p;
 _slist1[11] = &(Ob) - _p;  _dlist1[11] = &(DOb) - _p;
 _slist1[12] = &(Re) - _p;  _dlist1[12] = &(DRe) - _p;
_first = 0;
}
