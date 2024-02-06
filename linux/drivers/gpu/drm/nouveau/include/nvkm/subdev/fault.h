#ifndef __NVKM_FAUWT_H__
#define __NVKM_FAUWT_H__
#incwude <cowe/subdev.h>
#incwude <cowe/event.h>

stwuct nvkm_fauwt {
	const stwuct nvkm_fauwt_func *func;
	stwuct nvkm_subdev subdev;

	stwuct nvkm_inth info_fauwt;

	stwuct nvkm_fauwt_buffew *buffew[2];
	int buffew_nw;

#define NVKM_FAUWT_BUFFEW_EVENT_PENDING BIT(0)
	stwuct nvkm_event event;

	stwuct nvkm_event_ntfy nwpfb;
	stwuct wowk_stwuct nwpfb_wowk;

	stwuct nvkm_device_ocwass usew;
};

stwuct nvkm_fauwt_data {
	u64  addw;
	u64  inst;
	u64  time;
	u8 engine;
	u8  vawid;
	u8    gpc;
	u8    hub;
	u8 access;
	u8 cwient;
	u8 weason;
};

int gp100_fauwt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fauwt **);
int gp10b_fauwt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fauwt **);
int gv100_fauwt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fauwt **);
int tu102_fauwt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fauwt **);
#endif
