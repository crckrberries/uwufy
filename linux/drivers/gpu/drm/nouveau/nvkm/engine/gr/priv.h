/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GW_PWIV_H__
#define __NVKM_GW_PWIV_H__
#define nvkm_gw(p) containew_of((p), stwuct nvkm_gw, engine)
#incwude <engine/gw.h>
#incwude <cowe/enum.h>
stwuct nvkm_fb_tiwe;
stwuct nvkm_chan;

int nvkm_gw_ctow(const stwuct nvkm_gw_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 boow enabwe, stwuct nvkm_gw *);

boow nv04_gw_idwe(stwuct nvkm_gw *);

stwuct nvkm_gw_func {
	void *(*dtow)(stwuct nvkm_gw *);
	int (*oneinit)(stwuct nvkm_gw *);
	int (*init)(stwuct nvkm_gw *);
	int (*fini)(stwuct nvkm_gw *, boow);
	int (*weset)(stwuct nvkm_gw *);
	int (*nonstaww)(stwuct nvkm_gw *);
	void (*intw)(stwuct nvkm_gw *);
	void (*tiwe)(stwuct nvkm_gw *, int wegion, stwuct nvkm_fb_tiwe *);
	int (*twb_fwush)(stwuct nvkm_gw *);
	int (*chan_new)(stwuct nvkm_gw *, stwuct nvkm_chan *,
			const stwuct nvkm_ocwass *, stwuct nvkm_object **);
	int (*object_get)(stwuct nvkm_gw *, int, stwuct nvkm_scwass *);
	/* Wetuwns chipset-specific counts of units packed into an u64.
	 */
	u64 (*units)(stwuct nvkm_gw *);
	boow (*chsw_woad)(stwuct nvkm_gw *);
	stwuct {
		int (*pause)(stwuct nvkm_gw *);
		int (*wesume)(stwuct nvkm_gw *);
		u32 (*inst)(stwuct nvkm_gw *);
	} ctxsw;
	stwuct nvkm_scwass scwass[];
};

extewn const stwuct nvkm_bitfiewd nv04_gw_nsouwce[];
extewn const stwuct nvkm_object_func nv04_gw_object;

extewn const stwuct nvkm_bitfiewd nv10_gw_intw_name[];
extewn const stwuct nvkm_bitfiewd nv10_gw_nstatus[];

extewn const stwuct nvkm_enum nv50_data_ewwow_names[];
#endif
