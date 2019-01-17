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
 
#define nrn_init _nrn_init__naslow
#define _nrn_initial _nrn_initial__naslow
#define nrn_cur _nrn_cur__naslow
#define _nrn_current _nrn_current__naslow
#define nrn_jacob _nrn_jacob__naslow
#define nrn_state _nrn_state__naslow
#define _net_receive _net_receive__naslow 
#define kin kin__naslow 
#define rates rates__naslow 
 
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
#define gbar _p[0]
#define g _p[1]
#define ina _p[2]
#define c1 _p[3]
#define c2 _p[4]
#define o1 _p[5]
#define i1 _p[6]
#define i2 _p[7]
#define i3 _p[8]
#define ena _p[9]
#define o1c1 _p[10]
#define o1c2 _p[11]
#define i2c2 _p[12]
#define c1o1 _p[13]
#define c2o1 _p[14]
#define i1o1 _p[15]
#define i3o1 _p[16]
#define o1i1 _p[17]
#define i2i1 _p[18]
#define c2i2 _p[19]
#define i1i2 _p[20]
#define i3i2 _p[21]
#define o1i3 _p[22]
#define i2i3 _p[23]
#define Dc1 _p[24]
#define Dc2 _p[25]
#define Do1 _p[26]
#define Di1 _p[27]
#define Di2 _p[28]
#define Di3 _p[29]
#define v _p[30]
#define _g _p[31]
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
 
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
 static void _hoc_rates(void);
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
 "setdata_naslow", _hoc_setdata,
 "rates_naslow", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
#define vshift vshift_naslow
 double vshift = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "vshift_naslow", "mV",
 "gbar_naslow", "S/cm2",
 "g_naslow", "S/cm2",
 "ina_naslow", "mA/cm2",
 0,0
};
 static double c20 = 0;
 static double c10 = 0;
 static double delta_t = 0.01;
 static double i30 = 0;
 static double i20 = 0;
 static double i10 = 0;
 static double o10 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "vshift_naslow", &vshift_naslow,
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
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"naslow",
 "gbar_naslow",
 0,
 "g_naslow",
 "ina_naslow",
 0,
 "c1_naslow",
 "c2_naslow",
 "o1_naslow",
 "i1_naslow",
 "i2_naslow",
 "i3_naslow",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 32, _prop);
 	/*initialize range parameters*/
 	gbar = 0.035;
 	_prop->param = _p;
 	_prop->param_size = 32;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _naslow_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_prop_size(_mechtype, 32, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 naslow /Users/sulgod/rd/Nociception/cfiber/x86_64/naslow.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 extern double *_nrn_thread_getelm();
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[6], _dlist1[6]; static double *_temp1;
 static int kin();
 
static int kin (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<6;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
   /* ~ c1 <-> o1 ( c1o1 , o1c1 )*/
 f_flux =  c1o1 * c1 ;
 b_flux =  o1c1 * o1 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  c1o1 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 5 ,2)  -= _term;
 _term =  o1c1 ;
 _MATELM1( 2 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ c2 <-> o1 ( c2o1 , o1c2 )*/
 f_flux =  c2o1 * c2 ;
 b_flux =  o1c2 * o1 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  c2o1 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  o1c2 ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 f_flux =  o1i1 * o1 ;
 b_flux =  i1o1 * i1 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  o1i1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  i1o1 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ c2 <-> i2 ( c2i2 , i2c2 )*/
 f_flux =  c2i2 * c2 ;
 b_flux =  i2c2 * i2 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  c2i2 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 3 ,1)  -= _term;
 _term =  i2c2 ;
 _MATELM1( 1 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ i1 <-> i2 ( i1i2 , i2i1 )*/
 f_flux =  i1i2 * i1 ;
 b_flux =  i2i1 * i2 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  i1i2 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  i2i1 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i3 ( o1i3 , i3o1 )*/
 f_flux =  o1i3 * o1 ;
 b_flux =  i3o1 * i3 ;
 _RHS1( 5) -= (f_flux - b_flux);
 
 _term =  o1i3 ;
 _MATELM1( 5 ,5)  += _term;
 _term =  i3o1 ;
 _MATELM1( 5 ,0)  -= _term;
 /*REACTION*/
  /* ~ i2 <-> i3 ( i2i3 , i3i2 )*/
 f_flux =  i2i3 * i2 ;
 b_flux =  i3i2 * i3 ;
 _RHS1( 3) -= (f_flux - b_flux);
 
 _term =  i2i3 ;
 _MATELM1( 3 ,3)  += _term;
 _term =  i3i2 ;
 _MATELM1( 3 ,0)  -= _term;
 /*REACTION*/
   /* c1 + c2 + o1 + i1 + i2 + i3 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= i3 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= i2 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= i1 ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= o1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= c2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= c1 ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static int  rates ( _threadargsprotocomma_ double _lvm ) {
    o1c1 = exp ( - 5.0180000 + ( _lvm * - 0.1772490 ) ) ;
   o1i3 = exp ( 0.5123500 + ( _lvm * 0.0052635 ) ) ;
   i2i3 = exp ( - 3.6711500 + ( _lvm * 0.0436584 ) ) ;
   c1o1 = exp ( 5.2180000 + ( _lvm * 0.1065610 ) ) ;
   i3o1 = exp ( 14.8486500 + ( _lvm * 0.2956365 ) ) ;
   i1o1 = exp ( - 18.6755000 + ( _lvm * - 0.0000025 ) ) ;
   c2o1 = exp ( 2.1866650 + ( _lvm * 0.0443300 ) ) ;
   o1i1 = exp ( - 11.5305000 + ( _lvm * 0.0304675 ) ) ;
   i2i1 = exp ( - 1.5985000 + ( _lvm * - 0.0000000 ) ) ;
   i3i2 = exp ( 16.6071500 + ( _lvm * 0.4175016 ) ) ;
   i1i2 = exp ( - 2.8015000 + ( _lvm * 0.0530000 ) ) ;
   c2i2 = exp ( 6.8627500 + ( _lvm * 0.2200150 ) ) ;
   o1c2 = exp ( - 2.8188350 + ( _lvm * - 0.1497800 ) ) ;
   i2c2 = exp ( - 4.0847500 + ( _lvm * - 0.0575650 ) ) ;
     return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<6;_i++) _p[_dlist1[_i]] = 0.0;}
 rates ( _threadargscomma_ v ) ;
 /* ~ c1 <-> o1 ( c1o1 , o1c1 )*/
 f_flux =  c1o1 * c1 ;
 b_flux =  o1c1 * o1 ;
 Dc1 -= (f_flux - b_flux);
 Do1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ c2 <-> o1 ( c2o1 , o1c2 )*/
 f_flux =  c2o1 * c2 ;
 b_flux =  o1c2 * o1 ;
 Dc2 -= (f_flux - b_flux);
 Do1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 f_flux =  o1i1 * o1 ;
 b_flux =  i1o1 * i1 ;
 Do1 -= (f_flux - b_flux);
 Di1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ c2 <-> i2 ( c2i2 , i2c2 )*/
 f_flux =  c2i2 * c2 ;
 b_flux =  i2c2 * i2 ;
 Dc2 -= (f_flux - b_flux);
 Di2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ i1 <-> i2 ( i1i2 , i2i1 )*/
 f_flux =  i1i2 * i1 ;
 b_flux =  i2i1 * i2 ;
 Di1 -= (f_flux - b_flux);
 Di2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ o1 <-> i3 ( o1i3 , i3o1 )*/
 f_flux =  o1i3 * o1 ;
 b_flux =  i3o1 * i3 ;
 Do1 -= (f_flux - b_flux);
 Di3 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ i2 <-> i3 ( i2i3 , i3i2 )*/
 f_flux =  i2i3 * i2 ;
 b_flux =  i3i2 * i3 ;
 Di2 -= (f_flux - b_flux);
 Di3 += (f_flux - b_flux);
 
 /*REACTION*/
   /* c1 + c2 + o1 + i1 + i2 + i3 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<6;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
 /* ~ c1 <-> o1 ( c1o1 , o1c1 )*/
 _term =  c1o1 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 5 ,2)  -= _term;
 _term =  o1c1 ;
 _MATELM1( 2 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ c2 <-> o1 ( c2o1 , o1c2 )*/
 _term =  c2o1 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  o1c2 ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i1 ( o1i1 , i1o1 )*/
 _term =  o1i1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 4 ,5)  -= _term;
 _term =  i1o1 ;
 _MATELM1( 5 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ c2 <-> i2 ( c2i2 , i2c2 )*/
 _term =  c2i2 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 3 ,1)  -= _term;
 _term =  i2c2 ;
 _MATELM1( 1 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ i1 <-> i2 ( i1i2 , i2i1 )*/
 _term =  i1i2 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  i2i1 ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ o1 <-> i3 ( o1i3 , i3o1 )*/
 _term =  o1i3 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 0 ,5)  -= _term;
 _term =  i3o1 ;
 _MATELM1( 5 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ i2 <-> i3 ( i2i3 , i3i2 )*/
 _term =  i2i3 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 0 ,3)  -= _term;
 _term =  i3i2 ;
 _MATELM1( 3 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* c1 + c2 + o1 + i1 + i2 + i3 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 6;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 6; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 6, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
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
  ena = _ion_ena;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  c2 = c20;
  c1 = c10;
  i3 = i30;
  i2 = i20;
  i1 = i10;
  o1 = o10;
 {
   double _lsum ;
 c1 = 1.0 ;
   c2 = exp ( - 4.1003000 + ( - 0.0065631 * v ) ) ;
   o1 = exp ( 10.2360000 + ( 0.2838100 * v ) ) ;
   i1 = exp ( 17.3810000 + ( 0.3142800 * v ) ) ;
   i2 = exp ( 16.1780000 + ( 0.3672800 * v ) ) ;
   i3 = exp ( 5.2305000 + ( 0.0897000 * v ) ) ;
   _lsum = c1 + c2 + o1 + i1 + i2 + i3 ;
   c1 = c1 / _lsum ;
   c2 = c2 / _lsum ;
   o1 = o1 / _lsum ;
   i1 = i1 / _lsum ;
   i2 = i2 / _lsum ;
   i3 = i3 / _lsum ;
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
  ena = _ion_ena;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g = gbar * o1 ;
   ina = g * ( v - ena ) ;
   }
 _current += ina;

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
  ena = _ion_ena;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
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
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
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
  ena = _ion_ena;
 {  sparse_thread(&_thread[_spth1]._pvoid, 6, _slist1, _dlist1, _p, &t, dt, kin, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 6; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(i3) - _p;  _dlist1[0] = &(Di3) - _p;
 _slist1[1] = &(c2) - _p;  _dlist1[1] = &(Dc2) - _p;
 _slist1[2] = &(c1) - _p;  _dlist1[2] = &(Dc1) - _p;
 _slist1[3] = &(i2) - _p;  _dlist1[3] = &(Di2) - _p;
 _slist1[4] = &(i1) - _p;  _dlist1[4] = &(Di1) - _p;
 _slist1[5] = &(o1) - _p;  _dlist1[5] = &(Do1) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif
