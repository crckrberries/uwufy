/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MC_PWIV_H__
#define __NVKM_MC_PWIV_H__
#define nvkm_mc(p) containew_of((p), stwuct nvkm_mc, subdev)
#incwude <subdev/mc.h>

int nvkm_mc_new_(const stwuct nvkm_mc_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_mc **);

stwuct nvkm_mc_map {
	u32 stat;
	enum nvkm_subdev_type type;
	int inst;
	boow noauto;
};

stwuct nvkm_mc_func {
	void (*init)(stwuct nvkm_mc *);

	const stwuct nvkm_intw_func *intw;
	const stwuct nvkm_intw_data *intws;
	boow intw_nonstaww;

	const stwuct nvkm_mc_device_func {
		boow (*enabwed)(stwuct nvkm_mc *, u32 mask);
		void (*enabwe)(stwuct nvkm_mc *, u32 mask);
		void (*disabwe)(stwuct nvkm_mc *, u32 mask);
	} *device;

	const stwuct nvkm_mc_map *weset;

	void (*unk260)(stwuct nvkm_mc *, u32);
};

void nv04_mc_init(stwuct nvkm_mc *);
extewn const stwuct nvkm_intw_func nv04_mc_intw;
boow nv04_mc_intw_pending(stwuct nvkm_intw *);
void nv04_mc_intw_unawm(stwuct nvkm_intw *);
void nv04_mc_intw_weawm(stwuct nvkm_intw *);
extewn const stwuct nvkm_mc_device_func nv04_mc_device;
extewn const stwuct nvkm_mc_map nv04_mc_weset[];

extewn const stwuct nvkm_intw_data nv17_mc_intws[];
extewn const stwuct nvkm_mc_map nv17_mc_weset[];

void nv44_mc_init(stwuct nvkm_mc *);

void nv50_mc_init(stwuct nvkm_mc *);

extewn const stwuct nvkm_intw_func gt215_mc_intw;
void gf100_mc_unk260(stwuct nvkm_mc *, u32);

void gk104_mc_init(stwuct nvkm_mc *);
extewn const stwuct nvkm_intw_data gk104_mc_intws[];
extewn const stwuct nvkm_mc_map gk104_mc_weset[];

extewn const stwuct nvkm_intw_func gp100_mc_intw;
extewn const stwuct nvkm_intw_data gp100_mc_intws[];
#endif
