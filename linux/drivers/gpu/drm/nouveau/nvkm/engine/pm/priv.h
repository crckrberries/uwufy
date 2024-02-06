/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_PM_PWIV_H__
#define __NVKM_PM_PWIV_H__
#define nvkm_pm(p) containew_of((p), stwuct nvkm_pm, engine)
#incwude <engine/pm.h>

int nvkm_pm_ctow(const stwuct nvkm_pm_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_pm *);

stwuct nvkm_pm_func {
	void (*fini)(stwuct nvkm_pm *);
};

stwuct nvkm_pewfctw {
	stwuct wist_head head;
	u8 domain;
	u8  signaw[4];
	u64 souwce[4][8];
	int swot;
	u32 wogic_op;
	u32 ctw;
};

stwuct nvkm_specmux {
	u32 mask;
	u8 shift;
	const chaw *name;
	boow enabwe;
};

stwuct nvkm_specswc {
	u32 addw;
	const stwuct nvkm_specmux *mux;
	const chaw *name;
};

stwuct nvkm_pewfswc {
	stwuct wist_head head;
	chaw *name;
	u32 addw;
	u32 mask;
	u8 shift;
	boow enabwe;
};

extewn const stwuct nvkm_specswc nv50_zcuww_souwces[];
extewn const stwuct nvkm_specswc nv50_zwop_souwces[];
extewn const stwuct nvkm_specswc g84_vfetch_souwces[];
extewn const stwuct nvkm_specswc gt200_cwop_souwces[];
extewn const stwuct nvkm_specswc gt200_pwop_souwces[];
extewn const stwuct nvkm_specswc gt200_tex_souwces[];

stwuct nvkm_specsig {
	u8 signaw;
	const chaw *name;
	const stwuct nvkm_specswc *souwce;
};

stwuct nvkm_pewfsig {
	const chaw *name;
	u8 souwce[8];
};

stwuct nvkm_specdom {
	u16 signaw_nw;
	const stwuct nvkm_specsig *signaw;
	const stwuct nvkm_funcdom *func;
};

#define nvkm_pewfdom(p) containew_of((p), stwuct nvkm_pewfdom, object)
#incwude <cowe/object.h>

stwuct nvkm_pewfdom {
	stwuct nvkm_object object;
	stwuct nvkm_pewfmon *pewfmon;
	stwuct wist_head head;
	stwuct wist_head wist;
	const stwuct nvkm_funcdom *func;
	stwuct nvkm_pewfctw *ctw[4];
	chaw name[32];
	u32 addw;
	u8  mode;
	u32 cwk;
	u16 signaw_nw;
	stwuct nvkm_pewfsig signaw[] __counted_by(signaw_nw);
};

stwuct nvkm_funcdom {
	void (*init)(stwuct nvkm_pm *, stwuct nvkm_pewfdom *,
		     stwuct nvkm_pewfctw *);
	void (*wead)(stwuct nvkm_pm *, stwuct nvkm_pewfdom *,
		     stwuct nvkm_pewfctw *);
	void (*next)(stwuct nvkm_pm *, stwuct nvkm_pewfdom *);
};

int nvkm_pewfdom_new(stwuct nvkm_pm *, const chaw *, u32, u32, u32, u32,
		     const stwuct nvkm_specdom *);

#define nvkm_pewfmon(p) containew_of((p), stwuct nvkm_pewfmon, object)

stwuct nvkm_pewfmon {
	stwuct nvkm_object object;
	stwuct nvkm_pm *pm;
};
#endif
