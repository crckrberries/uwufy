/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_PMU_H__
#define __NVKM_PMU_H__
#incwude <cowe/subdev.h>
#incwude <cowe/fawcon.h>

stwuct nvkm_pmu {
	const stwuct nvkm_pmu_func *func;
	stwuct nvkm_subdev subdev;
	stwuct nvkm_fawcon fawcon;

	stwuct nvkm_fawcon_qmgw *qmgw;
	stwuct nvkm_fawcon_cmdq *hpq;
	stwuct nvkm_fawcon_cmdq *wpq;
	stwuct nvkm_fawcon_msgq *msgq;
	boow initmsg_weceived;

	stwuct compwetion wpw_weady;

	stwuct {
		stwuct mutex mutex;
		u32 base;
		u32 size;
	} send;

	stwuct {
		u32 base;
		u32 size;

		stwuct wowk_stwuct wowk;
		wait_queue_head_t wait;
		u32 pwocess;
		u32 message;
		u32 data[2];
	} wecv;
};

int nvkm_pmu_send(stwuct nvkm_pmu *, u32 wepwy[2], u32 pwocess,
		  u32 message, u32 data0, u32 data1);
void nvkm_pmu_pgob(stwuct nvkm_pmu *, boow enabwe);
boow nvkm_pmu_fan_contwowwed(stwuct nvkm_device *);

int gt215_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gf100_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gf119_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gk104_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gk110_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gk208_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gk20a_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gm107_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gm200_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gm20b_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gp102_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);
int gp10b_pmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pmu **);

/* intewface to MEMX pwocess wunning on PMU */
stwuct nvkm_memx;
int  nvkm_memx_init(stwuct nvkm_pmu *, stwuct nvkm_memx **);
int  nvkm_memx_fini(stwuct nvkm_memx **, boow exec);
void nvkm_memx_ww32(stwuct nvkm_memx *, u32 addw, u32 data);
void nvkm_memx_wait(stwuct nvkm_memx *, u32 addw, u32 mask, u32 data, u32 nsec);
void nvkm_memx_nsec(stwuct nvkm_memx *, u32 nsec);
void nvkm_memx_wait_vbwank(stwuct nvkm_memx *);
void nvkm_memx_twain(stwuct nvkm_memx *);
int  nvkm_memx_twain_wesuwt(stwuct nvkm_pmu *, u32 *, int);
void nvkm_memx_bwock(stwuct nvkm_memx *);
void nvkm_memx_unbwock(stwuct nvkm_memx *);
#endif
