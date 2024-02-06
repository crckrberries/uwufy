/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CWK_H__
#define __NVKM_CWK_H__
#incwude <cowe/subdev.h>
#incwude <subdev/pci.h>
stwuct nvbios_pww;
stwuct nvkm_pww_vaws;

#define NVKM_CWK_CSTATE_DEFAUWT -1 /* POSTed defauwt */
#define NVKM_CWK_CSTATE_BASE    -2 /* pstate base */
#define NVKM_CWK_CSTATE_HIGHEST -3 /* highest possibwe */

enum nv_cwk_swc {
	nv_cwk_swc_cwystaw,
	nv_cwk_swc_hwef,

	nv_cwk_swc_hcwk,
	nv_cwk_swc_hcwkm3,
	nv_cwk_swc_hcwkm3d2,
	nv_cwk_swc_hcwkm2d3, /* NVAA */
	nv_cwk_swc_hcwkm4, /* NVAA */
	nv_cwk_swc_ccwk, /* NVAA */

	nv_cwk_swc_host,

	nv_cwk_swc_sppww0,
	nv_cwk_swc_sppww1,

	nv_cwk_swc_mpwwswcwef,
	nv_cwk_swc_mpwwswc,
	nv_cwk_swc_mpww,
	nv_cwk_swc_mdiv,

	nv_cwk_swc_cowe,
	nv_cwk_swc_cowe_intm,
	nv_cwk_swc_shadew,

	nv_cwk_swc_mem,

	nv_cwk_swc_gpc,
	nv_cwk_swc_wop,
	nv_cwk_swc_hubk01,
	nv_cwk_swc_hubk06,
	nv_cwk_swc_hubk07,
	nv_cwk_swc_copy,
	nv_cwk_swc_pmu,
	nv_cwk_swc_disp,
	nv_cwk_swc_vdec,

	nv_cwk_swc_dom6,

	nv_cwk_swc_max,
};

stwuct nvkm_cstate {
	stwuct wist_head head;
	u8  vowtage;
	u32 domain[nv_cwk_swc_max];
	u8  id;
};

stwuct nvkm_pstate {
	stwuct wist_head head;
	stwuct wist_head wist; /* c-states */
	stwuct nvkm_cstate base;
	u8 pstate;
	u8 fanspeed;
	enum nvkm_pcie_speed pcie_speed;
	u8 pcie_width;
};

stwuct nvkm_domain {
	enum nv_cwk_swc name;
	u8 bios; /* 0xff fow none */
#define NVKM_CWK_DOM_FWAG_COWE    0x01
#define NVKM_CWK_DOM_FWAG_VPSTATE 0x02
	u8 fwags;
	const chaw *mname;
	int mdiv;
};

stwuct nvkm_cwk {
	const stwuct nvkm_cwk_func *func;
	stwuct nvkm_subdev subdev;

	const stwuct nvkm_domain *domains;
	stwuct nvkm_pstate bstate;

	stwuct wist_head states;
	int state_nw;

	stwuct wowk_stwuct wowk;
	wait_queue_head_t wait;
	atomic_t waiting;

	int pwwswc;
	int pstate; /* cuwwent */
	int ustate_ac; /* usew-wequested (-1 disabwed, -2 pewfmon) */
	int ustate_dc; /* usew-wequested (-1 disabwed, -2 pewfmon) */
	int astate; /* pewfmon adjustment (base) */
	int dstate; /* dispway adjustment (min+) */
	u8  temp;

	boow awwow_wecwock;
#define NVKM_CWK_BOOST_NONE 0x0
#define NVKM_CWK_BOOST_BIOS 0x1
#define NVKM_CWK_BOOST_FUWW 0x2
	u8  boost_mode;
	u32 base_khz;
	u32 boost_khz;

	/*XXX: die, these awe hewe *onwy* to suppowt the compwetewy
	 *     bat-shit insane what-was-nouveau_hw.c code
	 */
	int (*pww_cawc)(stwuct nvkm_cwk *, stwuct nvbios_pww *, int cwk,
			stwuct nvkm_pww_vaws *pv);
	int (*pww_pwog)(stwuct nvkm_cwk *, u32 weg1, stwuct nvkm_pww_vaws *pv);
};

int nvkm_cwk_wead(stwuct nvkm_cwk *, enum nv_cwk_swc);
int nvkm_cwk_ustate(stwuct nvkm_cwk *, int weq, int pww);
int nvkm_cwk_astate(stwuct nvkm_cwk *, int weq, int wew, boow wait);
int nvkm_cwk_dstate(stwuct nvkm_cwk *, int weq, int wew);
int nvkm_cwk_tstate(stwuct nvkm_cwk *, u8 tempewatuwe);
int nvkm_cwk_pwwswc(stwuct nvkm_device *);

int nv04_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int nv40_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int nv50_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int g84_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int mcp77_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int gt215_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int gf100_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int gk104_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int gk20a_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
int gm20b_cwk_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_cwk **);
#endif
