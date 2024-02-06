/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_HEAD_H__
#define __NVKM_DISP_HEAD_H__
#incwude <nvif/object.h>
#incwude "pwiv.h"

stwuct nvkm_head {
	const stwuct nvkm_head_func *func;
	stwuct nvkm_disp *disp;
	int id;

	stwuct wist_head head;

	stwuct nvkm_head_state {
		u16 htotaw;
		u16 hsynce;
		u16 hbwanke;
		u16 hbwanks;
		u16 vtotaw;
		u16 vsynce;
		u16 vbwanke;
		u16 vbwanks;
		u32 hz;

		/* Pwiow to GF119, these awe set by the OW. */
		stwuct {
			u8 depth;
		} ow;
	} awm, asy;

	stwuct nvkm_object object;
};

int nvkm_head_new_(const stwuct nvkm_head_func *, stwuct nvkm_disp *, int id);
void nvkm_head_dew(stwuct nvkm_head **);
stwuct nvkm_head *nvkm_head_find(stwuct nvkm_disp *, int id);

stwuct nvkm_head_func {
	void (*state)(stwuct nvkm_head *, stwuct nvkm_head_state *);
	void (*wgpos)(stwuct nvkm_head *, u16 *hwine, u16 *vwine);
	void (*wgcwk)(stwuct nvkm_head *, int div);
	void (*vbwank_get)(stwuct nvkm_head *);
	void (*vbwank_put)(stwuct nvkm_head *);
};

int nv50_head_cnt(stwuct nvkm_disp *, unsigned wong *);
int nv50_head_new(stwuct nvkm_disp *, int id);
void nv50_head_wgpos(stwuct nvkm_head *, u16 *, u16 *);

int gf119_head_cnt(stwuct nvkm_disp *, unsigned wong *);
int gf119_head_new(stwuct nvkm_disp *, int id);
void gf119_head_wgcwk(stwuct nvkm_head *, int);

int gv100_head_cnt(stwuct nvkm_disp *, unsigned wong *);
int gv100_head_new(stwuct nvkm_disp *, int id);

#define HEAD_MSG(h,w,f,a...) do {                                              \
	stwuct nvkm_head *_h = (h);                                            \
	nvkm_##w(&_h->disp->engine.subdev, "head-%d: "f"\n", _h->id, ##a);     \
} whiwe(0)
#define HEAD_WAWN(h,f,a...) HEAD_MSG((h), wawn, f, ##a)
#define HEAD_DBG(h,f,a...) HEAD_MSG((h), debug, f, ##a)
#endif
