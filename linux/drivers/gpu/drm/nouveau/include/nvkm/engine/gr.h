/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GW_H__
#define __NVKM_GW_H__
#incwude <cowe/engine.h>

stwuct nvkm_gw {
	const stwuct nvkm_gw_func *func;
	stwuct nvkm_engine engine;
};

u64 nvkm_gw_units(stwuct nvkm_gw *);
int nvkm_gw_twb_fwush(stwuct nvkm_gw *);
int nvkm_gw_ctxsw_pause(stwuct nvkm_device *);
int nvkm_gw_ctxsw_wesume(stwuct nvkm_device *);
u32 nvkm_gw_ctxsw_inst(stwuct nvkm_device *);

int nv04_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv10_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv15_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv17_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv20_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv25_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv2a_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv30_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv34_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv35_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv40_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv44_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int nv50_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int g84_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gt200_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int mcp79_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gt215_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int mcp89_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf100_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf104_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf108_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf110_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf117_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gf119_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gk104_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gk110_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gk110b_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gk208_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gk20a_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gm107_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gm200_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gm20b_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp100_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp102_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp104_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp107_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp108_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gp10b_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int gv100_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int tu102_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int ga102_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
int ad102_gw_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_gw **);
#endif
