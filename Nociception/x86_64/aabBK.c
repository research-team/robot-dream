/* Created by Language version: 7.5.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
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
 
#define nrn_init _nrn_init__aabBK
#define _nrn_initial _nrn_initial__aabBK
#define nrn_cur _nrn_cur__aabBK
#define _nrn_current _nrn_current__aabBK
#define nrn_jacob _nrn_jacob__aabBK
#define nrn_state _nrn_state__aabBK
#define _net_receive _net_receive__aabBK 
#define rates rates__aabBK 
#define state state__aabBK 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gakbar _p[0]
#define gabkbar _p[1]
#define tau _p[2]
#define cal _p[3]
#define base _p[4]
#define gak _p[5]
#define gabk _p[6]
#define ainf _p[7]
#define atau _p[8]
#define abinf _p[9]
#define abtau _p[10]
#define ca_i _p[11]
#define a _p[12]
#define ab _p[13]
#define ek _p[14]
#define ik _p[15]
#define ica _p[16]
#define Dca_i _p[17]
#define Da _p[18]
#define Dab _p[19]
#define v _p[20]
#define _g _p[21]
#define _ion_ica	*_ppvar[0]._pval
#define _ion_ek	*_ppvar[1]._pval
#define _ion_ik	*_ppvar[2]._pval
#define _ion_dikdv	*_ppvar[3]._pval
#define area	*_ppvar[4]._pval
 
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
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_peakab(void);
 static void _hoc_peaka(void);
 static void _hoc_rates(void);
 static void _hoc_shiftab(void);
 static void _hoc_shifta(void);
 static void _hoc_taufunc(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_aabBK", _hoc_setdata,
 "peakab_aabBK", _hoc_peakab,
 "peaka_aabBK", _hoc_peaka,
 "rates_aabBK", _hoc_rates,
 "shiftab_aabBK", _hoc_shiftab,
 "shifta_aabBK", _hoc_shifta,
 "taufunc_aabBK", _hoc_taufunc,
 0, 0
};
#define peakab peakab_aabBK
#define peaka peaka_aabBK
#define shiftab shiftab_aabBK
#define shifta shifta_aabBK
#define taufunc taufunc_aabBK
 extern double peakab( _threadargsprotocomma_ double );
 extern double peaka( _threadargsprotocomma_ double );
 extern double shiftab( _threadargsprotocomma_ double );
 extern double shifta( _threadargsprotocomma_ double );
 extern double taufunc( _threadargsprotocomma_ double );
 /* declare global and static user variables */
#define cascale cascale_aabBK
 double cascale = 3;
#define ca0 ca0_aabBK
 double ca0 = 7e-05;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ca0_aabBK", "mM",
 "gakbar_aabBK", "S/cm2",
 "gabkbar_aabBK", "S/cm2",
 "tau_aabBK", "ms",
 "cal_aabBK", "mM",
 "base_aabBK", "mV",
 "ca_i_aabBK", "mM",
 "gak_aabBK", "S/cm2",
 "gabk_aabBK", "S/cm2",
 "ainf_aabBK", "mV",
 "atau_aabBK", "ms",
 "abinf_aabBK", "mV",
 "abtau_aabBK", "ms",
 0,0
};
 static double ab0 = 0;
 static double a0 = 0;
 static double ca_i0 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ca0_aabBK", &ca0_aabBK,
 "cascale_aabBK", &cascale_aabBK,
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
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[5]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"aabBK",
 "gakbar_aabBK",
 "gabkbar_aabBK",
 "tau_aabBK",
 "cal_aabBK",
 "base_aabBK",
 0,
 "gak_aabBK",
 "gabk_aabBK",
 "ainf_aabBK",
 "atau_aabBK",
 "abinf_aabBK",
 "abtau_aabBK",
 0,
 "ca_i_aabBK",
 "a_aabBK",
 "ab_aabBK",
 0,
 0};
 extern Node* nrn_alloc_node_;
 static Symbol* _ca_sym;
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	gakbar = 0.01;
 	gabkbar = 0.01;
 	tau = 2;
 	cal = 0;
 	base = 1;
 	_prop->param = _p;
 	_prop->param_size = 22;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 6, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 	_ppvar[4]._pval = &nrn_alloc_node_->_area; /* diam */
 prop_ion = need_memb(_ca_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ica */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[1]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _aabBK_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("k", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_prop_size(_mechtype, 22, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "cvodeieq");
  hoc_register_dparam_semantics(_mechtype, 4, "area");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 aabBK /Users/sulgod/rd/Nociception/x86_64/aabBK.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double B = .26;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double, double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   Dca_i = - B * ( ica * cascale ) - ( ca_i - ca0 ) / tau ;
   rates ( _threadargscomma_ v , ca_i ) ;
   Da = ( ainf - a ) / atau ;
   Dab = ( abinf - ab ) / abtau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 Dca_i = Dca_i  / (1. - dt*( ( - ( ( 1.0 ) ) / tau ) )) ;
 rates ( _threadargscomma_ v , ca_i ) ;
 Da = Da  / (1. - dt*( ( ( ( - 1.0 ) ) ) / atau )) ;
 Dab = Dab  / (1. - dt*( ( ( ( - 1.0 ) ) ) / abtau )) ;
  return 0;
}
 /*END CVODE*/
 static int state (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
    ca_i = ca_i + (1. - exp(dt*(( - ( ( 1.0 ) ) / tau ))))*(- ( ( - B )*( ( ( ica )*( cascale ) ) ) - ( ( ( - ca0 ) ) ) / tau ) / ( ( - ( ( 1.0 ) ) / tau ) ) - ca_i) ;
   rates ( _threadargscomma_ v , ca_i ) ;
    a = a + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / atau)))*(- ( ( ( ainf ) ) / atau ) / ( ( ( ( - 1.0 ) ) ) / atau ) - a) ;
    ab = ab + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / abtau)))*(- ( ( ( abinf ) ) / abtau ) / ( ( ( ( - 1.0 ) ) ) / abtau ) - ab) ;
   }
  return 0;
}
 
double shifta ( _threadargsprotocomma_ double _lca ) {
   double _lshifta;
 _lshifta = 25.0 - 50.3 + ( 107.5 * exp ( - .12 * _lca * 1e3 ) ) ;
   
return _lshifta;
 }
 
static void _hoc_shifta(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  shifta ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double peaka ( _threadargsprotocomma_ double _lca ) {
   double _lpeaka;
 _lpeaka = 2.9 + ( 6.3 * exp ( - .36 * _lca * 1e3 ) ) ;
   
return _lpeaka;
 }
 
static void _hoc_peaka(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  peaka ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double shiftab ( _threadargsprotocomma_ double _lca ) {
   double _lshiftab;
 _lshiftab = 25.0 - 55.7 + 136.9 * exp ( - .28 * _lca * 1e3 ) ;
   
return _lshiftab;
 }
 
static void _hoc_shiftab(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  shiftab ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double peakab ( _threadargsprotocomma_ double _lca ) {
   double _lpeakab;
 _lpeakab = 13.7 + 234.0 * exp ( - .72 * _lca * 1e3 ) ;
   
return _lpeakab;
 }
 
static void _hoc_peakab(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  peakab ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double taufunc ( _threadargsprotocomma_ double _lv ) {
   double _ltaufunc;
 _ltaufunc = 1.0 / ( ( 10.0 * ( exp ( - _lv / 63.6 ) + exp ( - ( 150.0 - _lv ) / 63.6 ) ) ) - 5.2 ) ;
   if ( _ltaufunc <= 0.2 ) {
     _ltaufunc = 0.2 ;
     }
   
return _ltaufunc;
 }
 
static void _hoc_taufunc(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  taufunc ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  rates ( _threadargsprotocomma_ double _lv , double _lc ) {
   double _lrange , _lvv ;
 ainf = - 32.0 + ( 59.2 * exp ( - .09 * _lc * 1e3 ) ) + ( 96.7 * exp ( - .47 * _lc * 1e3 ) ) ;
   ainf = 1.0 / ( 1.0 + exp ( ( ainf - _lv ) / ( 25.0 / 1.6 ) ) ) ;
   _lvv = _lv + 100.0 - shifta ( _threadargscomma_ _lc ) ;
   atau = taufunc ( _threadargscomma_ _lvv ) ;
   _lrange = peaka ( _threadargscomma_ _lc ) - 1.0 ;
   atau = ( _lrange * ( ( atau - .2 ) / .8 ) ) + 1.0 ;
   abinf = - 56.449 + 104.52 * exp ( - .22964 * _lc * 1e3 ) + 295.68 * exp ( - 2.1571 * _lc * 1e3 ) ;
   abinf = 1.0 / ( 1.0 + exp ( ( abinf - _lv ) / ( 25.0 / 1.6 ) ) ) ;
   _lvv = _lv + 100.0 - shiftab ( _threadargscomma_ _lc ) ;
   abtau = taufunc ( _threadargscomma_ _lvv ) ;
   _lrange = peakab ( _threadargscomma_ _lc ) - base ;
   abtau = ( _lrange * ( ( abtau - .2 ) / .8 ) ) + base ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ica = _ion_ica;
  ek = _ion_ek;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ica = _ion_ica;
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  ab = ab0;
  a = a0;
  ca_i = ca_i0;
 {
   ca_i = ca0 ;
   rates ( _threadargscomma_ v , ca_i ) ;
   a = ainf ;
   ab = abinf ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  ica = _ion_ica;
  ek = _ion_ek;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   gak = gakbar * a ;
   gabk = gabkbar * ab ;
   ik = ( gak + gabk ) * ( v - ek ) ;
   cal = ca_i ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  ica = _ion_ica;
  ek = _ion_ek;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  ica = _ion_ica;
  ek = _ion_ek;
 {   state(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ca_i) - _p;  _dlist1[0] = &(Dca_i) - _p;
 _slist1[1] = &(a) - _p;  _dlist1[1] = &(Da) - _p;
 _slist1[2] = &(ab) - _p;  _dlist1[2] = &(Dab) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif
