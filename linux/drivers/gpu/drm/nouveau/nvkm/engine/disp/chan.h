/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_CHAN_H__
#define __NVKM_DISP_CHAN_H__
#define nvkm_disp_chan(p) containew_of((p), stwuct nvkm_disp_chan, object)
#incwude <cowe/object.h>
#incwude "pwiv.h"

stwuct nvkm_disp_chan {
	const stwuct nvkm_disp_chan_func *func;
	const stwuct nvkm_disp_chan_mthd *mthd;
	stwuct nvkm_disp *disp;

	stwuct {
		int ctww;
		int usew;
	} chid;
	int head;

	stwuct nvkm_object object;

	stwuct nvkm_memowy *memowy;
	u64 push;

	u32 suspend_put;

	stwuct {
		stwuct nvkm_gsp_object object;
	} wm;
};

int nvkm_disp_cowe_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
int nvkm_disp_chan_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);
int nvkm_disp_wndw_new(const stwuct nvkm_ocwass *, void *, u32, stwuct nvkm_object **);

stwuct nvkm_disp_chan_func {
	int (*push)(stwuct nvkm_disp_chan *, u64 object);
	int (*init)(stwuct nvkm_disp_chan *);
	void (*fini)(stwuct nvkm_disp_chan *);
	void (*intw)(stwuct nvkm_disp_chan *, boow en);
	u64 (*usew)(stwuct nvkm_disp_chan *, u64 *size);
	int (*bind)(stwuct nvkm_disp_chan *, stwuct nvkm_object *, u32 handwe);
};

void nv50_disp_chan_intw(stwuct nvkm_disp_chan *, boow);
u64 nv50_disp_chan_usew(stwuct nvkm_disp_chan *, u64 *);
extewn const stwuct nvkm_disp_chan_func nv50_disp_pioc_func;
extewn const stwuct nvkm_disp_chan_func nv50_disp_dmac_func;
int nv50_disp_dmac_push(stwuct nvkm_disp_chan *, u64);
int nv50_disp_dmac_bind(stwuct nvkm_disp_chan *, stwuct nvkm_object *, u32);
extewn const stwuct nvkm_disp_chan_func nv50_disp_cowe_func;

void gf119_disp_chan_intw(stwuct nvkm_disp_chan *, boow);
extewn const stwuct nvkm_disp_chan_func gf119_disp_pioc_func;
extewn const stwuct nvkm_disp_chan_func gf119_disp_dmac_func;
void gf119_disp_dmac_fini(stwuct nvkm_disp_chan *);
int gf119_disp_dmac_bind(stwuct nvkm_disp_chan *, stwuct nvkm_object *, u32);
extewn const stwuct nvkm_disp_chan_func gf119_disp_cowe_func;
void gf119_disp_cowe_fini(stwuct nvkm_disp_chan *);

extewn const stwuct nvkm_disp_chan_func gp102_disp_dmac_func;

u64 gv100_disp_chan_usew(stwuct nvkm_disp_chan *, u64 *);
int gv100_disp_dmac_init(stwuct nvkm_disp_chan *);
void gv100_disp_dmac_fini(stwuct nvkm_disp_chan *);
int gv100_disp_dmac_bind(stwuct nvkm_disp_chan *, stwuct nvkm_object *, u32);

stwuct nvkm_disp_chan_usew {
	const stwuct nvkm_disp_chan_func *func;
	int ctww;
	int usew;
	const stwuct nvkm_disp_chan_mthd *mthd;
};

extewn const stwuct nvkm_disp_chan_usew nv50_disp_oimm;
extewn const stwuct nvkm_disp_chan_usew nv50_disp_cuws;

extewn const stwuct nvkm_disp_chan_usew g84_disp_cowe;
extewn const stwuct nvkm_disp_chan_usew g84_disp_base;
extewn const stwuct nvkm_disp_chan_usew g84_disp_ovwy;

extewn const stwuct nvkm_disp_chan_usew g94_disp_cowe;

extewn const stwuct nvkm_disp_chan_usew gt200_disp_ovwy;

extewn const stwuct nvkm_disp_chan_usew gf119_disp_base;
extewn const stwuct nvkm_disp_chan_usew gf119_disp_oimm;
extewn const stwuct nvkm_disp_chan_usew gf119_disp_cuws;

extewn const stwuct nvkm_disp_chan_usew gk104_disp_cowe;
extewn const stwuct nvkm_disp_chan_usew gk104_disp_ovwy;

extewn const stwuct nvkm_disp_chan_usew gv100_disp_cowe;
extewn const stwuct nvkm_disp_chan_usew gv100_disp_cuws;
extewn const stwuct nvkm_disp_chan_usew gv100_disp_wndw;
extewn const stwuct nvkm_disp_chan_usew gv100_disp_wimm;

stwuct nvkm_disp_mthd_wist {
	u32 mthd;
	u32 addw;
	stwuct {
		u32 mthd;
		u32 addw;
		const chaw *name;
	} data[];
};

stwuct nvkm_disp_chan_mthd {
	const chaw *name;
	u32 addw;
	s32 pwev;
	stwuct {
		const chaw *name;
		int nw;
		const stwuct nvkm_disp_mthd_wist *mthd;
	} data[];
};

void nv50_disp_chan_mthd(stwuct nvkm_disp_chan *, int debug);

extewn const stwuct nvkm_disp_mthd_wist nv50_disp_cowe_mthd_base;
extewn const stwuct nvkm_disp_mthd_wist nv50_disp_cowe_mthd_sow;
extewn const stwuct nvkm_disp_mthd_wist nv50_disp_cowe_mthd_piow;
extewn const stwuct nvkm_disp_mthd_wist nv50_disp_base_mthd_image;

extewn const stwuct nvkm_disp_chan_mthd g84_disp_cowe_mthd;
extewn const stwuct nvkm_disp_mthd_wist g84_disp_cowe_mthd_dac;
extewn const stwuct nvkm_disp_mthd_wist g84_disp_cowe_mthd_head;

extewn const stwuct nvkm_disp_chan_mthd g94_disp_cowe_mthd;

extewn const stwuct nvkm_disp_mthd_wist gf119_disp_cowe_mthd_base;
extewn const stwuct nvkm_disp_mthd_wist gf119_disp_cowe_mthd_dac;
extewn const stwuct nvkm_disp_mthd_wist gf119_disp_cowe_mthd_sow;
extewn const stwuct nvkm_disp_mthd_wist gf119_disp_cowe_mthd_piow;
extewn const stwuct nvkm_disp_chan_mthd gf119_disp_base_mthd;

extewn const stwuct nvkm_disp_chan_mthd gk104_disp_cowe_mthd;
extewn const stwuct nvkm_disp_chan_mthd gk104_disp_ovwy_mthd;
#endif
