#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _5ht_reg(void);
extern void _DNav18_reg(void);
extern void _Nav17_a_reg(void);
extern void _Nav18_a_reg(void);
extern void _Nav1_3_reg(void);
extern void _atp4_reg(void);
extern void _atp42_reg(void);
extern void _extrapump_reg(void);
extern void _k_ion_dynamics_reg(void);
extern void _kadist_reg(void);
extern void _kaprox_reg(void);
extern void _kdr_reg(void);
extern void _kf_reg(void);
extern void _kna_reg(void);
extern void _ks_reg(void);
extern void _leak_reg(void);
extern void _na1p8_reg(void);
extern void _na_ion_dynamics_reg(void);
extern void _nakpump_reg(void);
extern void _nattxs_reg(void);
extern void _nav18_reg(void);
extern void _nav1p9_reg(void);
extern void _p2x2_reg(void);
extern void _p2x3_reg(void);
extern void _slowATP_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," ./mod/5ht.mod");
    fprintf(stderr," ./mod/DNav18.mod");
    fprintf(stderr," ./mod/Nav17_a.mod");
    fprintf(stderr," ./mod/Nav18_a.mod");
    fprintf(stderr," ./mod/Nav1_3.mod");
    fprintf(stderr," ./mod/atp4.mod");
    fprintf(stderr," ./mod/atp42.mod");
    fprintf(stderr," ./mod/extrapump.mod");
    fprintf(stderr," ./mod/k_ion_dynamics.mod");
    fprintf(stderr," ./mod/kadist.mod");
    fprintf(stderr," ./mod/kaprox.mod");
    fprintf(stderr," ./mod/kdr.mod");
    fprintf(stderr," ./mod/kf.mod");
    fprintf(stderr," ./mod/kna.mod");
    fprintf(stderr," ./mod/ks.mod");
    fprintf(stderr," ./mod/leak.mod");
    fprintf(stderr," ./mod/na1p8.mod");
    fprintf(stderr," ./mod/na_ion_dynamics.mod");
    fprintf(stderr," ./mod/nakpump.mod");
    fprintf(stderr," ./mod/nattxs.mod");
    fprintf(stderr," ./mod/nav18.mod");
    fprintf(stderr," ./mod/nav1p9.mod");
    fprintf(stderr," ./mod/p2x2.mod");
    fprintf(stderr," ./mod/p2x3.mod");
    fprintf(stderr," ./mod/slowATP.mod");
    fprintf(stderr, "\n");
  }
  _5ht_reg();
  _DNav18_reg();
  _Nav17_a_reg();
  _Nav18_a_reg();
  _Nav1_3_reg();
  _atp4_reg();
  _atp42_reg();
  _extrapump_reg();
  _k_ion_dynamics_reg();
  _kadist_reg();
  _kaprox_reg();
  _kdr_reg();
  _kf_reg();
  _kna_reg();
  _ks_reg();
  _leak_reg();
  _na1p8_reg();
  _na_ion_dynamics_reg();
  _nakpump_reg();
  _nattxs_reg();
  _nav18_reg();
  _nav1p9_reg();
  _p2x2_reg();
  _p2x3_reg();
  _slowATP_reg();
}
