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
#define K1 _p[0]
#define L1 _p[1]
#define K2 _p[2]
#define L2 _p[3]
#define K3 _p[4]
#define L3 _p[5]
#define K4 _p[6]
#define L4 _p[7]
#define R4 _p[8]
#define D4 _p[9]
#define R3 _p[10]
#define D3 _p[11]
#define R2 _p[12]
#define D2 _p[13]
#define R5 _p[14]
#define D5 _p[15]
#define M4 _p[16]
#define N3 _p[17]
#define M3 _p[18]
#define N2 _p[19]
#define M2 _p[20]
#define N1 _p[21]
#define M1 _p[22]
#define gmax _p[23]
#define Ev _p[24]
#define i _p[25]
#define g _p[26]
#define Re _p[27]
#define AR _p[28]
#define A2R _p[29]
#define A3R _p[30]
#define Ro _p[31]
#define AD _p[32]
#define A2D _p[33]
#define A3D _p[34]
#define A3Df _p[35]
#define D _p[36]
#define k1 _p[37]
#define k2 _p[38]
#define k3 _p[39]
#define m1 _p[40]
#define m2 _p[41]
#define m3 _p[42]
#define DRe _p[43]
#define DAR _p[44]
#define DA2R _p[45]
#define DA3R _p[46]
#define DRo _p[47]
#define DAD _p[48]
#define DA2D _p[49]
#define DA3D _p[50]
#define DA3Df _p[51]
#define DD _p[52]
#define _g _p[53]
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
#define N4 N4_p2x2
 double N4 = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "N4_p2x2", "/s",
 "K1", "/mM",
 "L1", "/s",
 "K2", "/mM",
 "L2", "/s",
 "K3", "/mM",
 "L3", "/s",
 "K4", "/s",
 "L4", "/s",
 "R4", "/s",
 "D4", "/s",
 "R3", "/s",
 "D3", "/s",
 "R2", "/s",
 "D2", "/s",
 "R5", "/s",
 "D5", "/s",
 "M4", "/mM",
 "N3", "/s",
 "M3", "/mM",
 "N2", "/s",
 "M2", "/mM",
 "N1", "/s",
 "M1", "/mM",
 "gmax", "pS",
 "Ev", "mV",
 "i", "nA",
 "g", "pS",
 "patp", "uM",
 0,0
};
 static double A3Df0 = 0;
 static double A3D0 = 0;
 static double A2D0 = 0;
 static double AD0 = 0;
 static double A3R0 = 0;
 static double A2R0 = 0;
 static double AR0 = 0;
 static double D0 = 0;
 static double Ro0 = 0;
 static double Re0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "N4_p2x2", &N4_p2x2,
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
 "K1",
 "L1",
 "K2",
 "L2",
 "K3",
 "L3",
 "K4",
 "L4",
 "R4",
 "D4",
 "R3",
 "D3",
 "R2",
 "D2",
 "R5",
 "D5",
 "M4",
 "N3",
 "M3",
 "N2",
 "M2",
 "N1",
 "M1",
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
 "Ro",
 "AD",
 "A2D",
 "A3D",
 "A3Df",
 "D",
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
 	_p = nrn_prop_data_alloc(_mechtype, 54, _prop);
 	/*initialize range parameters*/
 	K1 = 120000;
 	L1 = 20;
 	K2 = 80000;
 	L2 = 40;
 	K3 = 40000;
 	L3 = 40;
 	K4 = 70;
 	L4 = 1;
 	R4 = 1e-05;
 	D4 = 1e-05;
 	R3 = 1e-05;
 	D3 = 1e-05;
 	R2 = 1e-05;
 	D2 = 1e-05;
 	R5 = 0.0001;
 	D5 = 0.0001;
 	M4 = 0.0001;
 	N3 = 0.0255;
 	M3 = 8000;
 	N2 = 0.017;
 	M2 = 16000;
 	N1 = 0.0085;
 	M1 = 24000;
 	gmax = 32.4;
 	Ev = -40;
  }
 	_prop->param = _p;
 	_prop->param_size = 54;
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
  hoc_register_prop_size(_mechtype, 54, 4);
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
 static int _slist1[10], _dlist1[10]; static double *_temp1;
 static int kstates();
 
static int kstates ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<10;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = K1 * patp ;
   k2 = K2 * patp ;
   k3 = K3 * patp ;
   m1 = M1 * patp ;
   m2 = M2 * patp ;
   m3 = M3 * patp ;
   /* ~ Re <-> AR ( k1 , L1 )*/
 f_flux =  k1 * Re ;
 b_flux =  L1 * AR ;
 _RHS1( 9) -= (f_flux - b_flux);
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  k1 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 7 ,9)  -= _term;
 _term =  L1 ;
 _MATELM1( 9 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , L2 )*/
 f_flux =  k2 * AR ;
 b_flux =  L2 * A2R ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 6) += (f_flux - b_flux);
 
 _term =  k2 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 6 ,7)  -= _term;
 _term =  L2 ;
 _MATELM1( 7 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ AR <-> AD ( D2 , R2 )*/
 f_flux =  D2 * AR ;
 b_flux =  R2 * AD ;
 _RHS1( 7) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  D2 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 4 ,7)  -= _term;
 _term =  R2 ;
 _MATELM1( 7 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , L3 )*/
 f_flux =  k3 * A2R ;
 b_flux =  L3 * A3R ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  k3 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  L3 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A2D ( D3 , R3 )*/
 f_flux =  D3 * A2R ;
 b_flux =  R3 * A2D ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  D3 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 3 ,6)  -= _term;
 _term =  R3 ;
 _MATELM1( 6 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Ro ( K4 , L4 )*/
 f_flux =  K4 * A3R ;
 b_flux =  L4 * Ro ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 8) += (f_flux - b_flux);
 
 _term =  K4 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 8 ,5)  -= _term;
 _term =  L4 ;
 _MATELM1( 5 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ A3R <-> A3D ( D4 , R4 )*/
 f_flux =  D4 * A3R ;
 b_flux =  R4 * A3D ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  D4 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 2 ,5)  -= _term;
 _term =  R4 ;
 _MATELM1( 5 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ Ro <-> A3Df ( D5 , R5 )*/
 f_flux =  D5 * Ro ;
 b_flux =  R5 * A3Df ;
 _RHS1( 8) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  D5 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 1 ,8)  -= _term;
 _term =  R5 ;
 _MATELM1( 8 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ A3Df <-> A3D ( N4 , M4 )*/
 f_flux =  N4 * A3Df ;
 b_flux =  M4 * A3D ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  N4 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  M4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ A3D <-> A2D ( N3 , m3 )*/
 f_flux =  N3 * A3D ;
 b_flux =  m3 * A2D ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  N3 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 3 ,2)  -= _term;
 _term =  m3 ;
 _MATELM1( 2 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ A2D <-> AD ( N2 , m2 )*/
 f_flux =  N2 * A2D ;
 b_flux =  m2 * AD ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  N2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 4 ,3)  -= _term;
 _term =  m2 ;
 _MATELM1( 3 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ AD <-> D ( N1 , m1 )*/
 f_flux =  N1 * AD ;
 b_flux =  m1 * D ;
 _RHS1( 4) -= (f_flux - b_flux);
 
 _term =  N1 ;
 _MATELM1( 4 ,4)  += _term;
 _term =  m1 ;
 _MATELM1( 4 ,0)  -= _term;
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ro + AD + A2D + A3D + A3Df + D = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= D ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= A3Df ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= A3D ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= A2D ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= AD ;
 _MATELM1(0, 8) = 1;
 _RHS1(0) -= Ro ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= A3R ;
 _MATELM1(0, 6) = 1;
 _RHS1(0) -= A2R ;
 _MATELM1(0, 7) = 1;
 _RHS1(0) -= AR ;
 _MATELM1(0, 9) = 1;
 _RHS1(0) -= Re ;
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<10;_i++) _p[_dlist1[_i]] = 0.0;}
 k1 = K1 * patp ;
 k2 = K2 * patp ;
 k3 = K3 * patp ;
 m1 = M1 * patp ;
 m2 = M2 * patp ;
 m3 = M3 * patp ;
 /* ~ Re <-> AR ( k1 , L1 )*/
 f_flux =  k1 * Re ;
 b_flux =  L1 * AR ;
 DRe -= (f_flux - b_flux);
 DAR += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , L2 )*/
 f_flux =  k2 * AR ;
 b_flux =  L2 * A2R ;
 DAR -= (f_flux - b_flux);
 DA2R += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ AR <-> AD ( D2 , R2 )*/
 f_flux =  D2 * AR ;
 b_flux =  R2 * AD ;
 DAR -= (f_flux - b_flux);
 DAD += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , L3 )*/
 f_flux =  k3 * A2R ;
 b_flux =  L3 * A3R ;
 DA2R -= (f_flux - b_flux);
 DA3R += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A2R <-> A2D ( D3 , R3 )*/
 f_flux =  D3 * A2R ;
 b_flux =  R3 * A2D ;
 DA2R -= (f_flux - b_flux);
 DA2D += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3R <-> Ro ( K4 , L4 )*/
 f_flux =  K4 * A3R ;
 b_flux =  L4 * Ro ;
 DA3R -= (f_flux - b_flux);
 DRo += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3R <-> A3D ( D4 , R4 )*/
 f_flux =  D4 * A3R ;
 b_flux =  R4 * A3D ;
 DA3R -= (f_flux - b_flux);
 DA3D += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Ro <-> A3Df ( D5 , R5 )*/
 f_flux =  D5 * Ro ;
 b_flux =  R5 * A3Df ;
 DRo -= (f_flux - b_flux);
 DA3Df += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3Df <-> A3D ( N4 , M4 )*/
 f_flux =  N4 * A3Df ;
 b_flux =  M4 * A3D ;
 DA3Df -= (f_flux - b_flux);
 DA3D += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A3D <-> A2D ( N3 , m3 )*/
 f_flux =  N3 * A3D ;
 b_flux =  m3 * A2D ;
 DA3D -= (f_flux - b_flux);
 DA2D += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ A2D <-> AD ( N2 , m2 )*/
 f_flux =  N2 * A2D ;
 b_flux =  m2 * AD ;
 DA2D -= (f_flux - b_flux);
 DAD += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ AD <-> D ( N1 , m1 )*/
 f_flux =  N1 * AD ;
 b_flux =  m1 * D ;
 DAD -= (f_flux - b_flux);
 DD += (f_flux - b_flux);
 
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ro + AD + A2D + A3D + A3Df + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<10;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 k1 = K1 * patp ;
 k2 = K2 * patp ;
 k3 = K3 * patp ;
 m1 = M1 * patp ;
 m2 = M2 * patp ;
 m3 = M3 * patp ;
 /* ~ Re <-> AR ( k1 , L1 )*/
 _term =  k1 ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 7 ,9)  -= _term;
 _term =  L1 ;
 _MATELM1( 9 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ AR <-> A2R ( k2 , L2 )*/
 _term =  k2 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 6 ,7)  -= _term;
 _term =  L2 ;
 _MATELM1( 7 ,6)  -= _term;
 _MATELM1( 6 ,6)  += _term;
 /*REACTION*/
  /* ~ AR <-> AD ( D2 , R2 )*/
 _term =  D2 ;
 _MATELM1( 7 ,7)  += _term;
 _MATELM1( 4 ,7)  -= _term;
 _term =  R2 ;
 _MATELM1( 7 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A3R ( k3 , L3 )*/
 _term =  k3 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  L3 ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ A2R <-> A2D ( D3 , R3 )*/
 _term =  D3 ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 3 ,6)  -= _term;
 _term =  R3 ;
 _MATELM1( 6 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ A3R <-> Ro ( K4 , L4 )*/
 _term =  K4 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 8 ,5)  -= _term;
 _term =  L4 ;
 _MATELM1( 5 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ A3R <-> A3D ( D4 , R4 )*/
 _term =  D4 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 2 ,5)  -= _term;
 _term =  R4 ;
 _MATELM1( 5 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ Ro <-> A3Df ( D5 , R5 )*/
 _term =  D5 ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 1 ,8)  -= _term;
 _term =  R5 ;
 _MATELM1( 8 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ A3Df <-> A3D ( N4 , M4 )*/
 _term =  N4 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  M4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ A3D <-> A2D ( N3 , m3 )*/
 _term =  N3 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 3 ,2)  -= _term;
 _term =  m3 ;
 _MATELM1( 2 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ A2D <-> AD ( N2 , m2 )*/
 _term =  N2 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 4 ,3)  -= _term;
 _term =  m2 ;
 _MATELM1( 3 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ AD <-> D ( N1 , m1 )*/
 _term =  N1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 0 ,4)  -= _term;
 _term =  m1 ;
 _MATELM1( 4 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* Re + AR + A2R + A3R + Ro + AD + A2D + A3D + A3Df + D = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 10;}
 
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
	for (_i=0; _i < 10; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse(&_cvsparseobj1, 10, _dlist1, _p, _ode_matsol1, &_coef1);
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
  A3Df = A3Df0;
  A3D = A3D0;
  A2D = A2D0;
  AD = AD0;
  A3R = A3R0;
  A2R = A2R0;
  AR = AR0;
  D = D0;
  Ro = Ro0;
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
   g = gmax * Ro ;
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
 { error = sparse(&_sparseobj1, 10, _slist1, _dlist1, _p, &t, dt, kstates,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 82 in file p2x2.mod:\n	SOLVE kstates METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
    if (secondorder) {
    int _i;
    for (_i = 0; _i < 10; ++_i) {
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
 _slist1[1] = &(A3Df) - _p;  _dlist1[1] = &(DA3Df) - _p;
 _slist1[2] = &(A3D) - _p;  _dlist1[2] = &(DA3D) - _p;
 _slist1[3] = &(A2D) - _p;  _dlist1[3] = &(DA2D) - _p;
 _slist1[4] = &(AD) - _p;  _dlist1[4] = &(DAD) - _p;
 _slist1[5] = &(A3R) - _p;  _dlist1[5] = &(DA3R) - _p;
 _slist1[6] = &(A2R) - _p;  _dlist1[6] = &(DA2R) - _p;
 _slist1[7] = &(AR) - _p;  _dlist1[7] = &(DAR) - _p;
 _slist1[8] = &(Ro) - _p;  _dlist1[8] = &(DRo) - _p;
 _slist1[9] = &(Re) - _p;  _dlist1[9] = &(DRe) - _p;
_first = 0;
}
