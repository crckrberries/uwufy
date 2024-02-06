/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_WAMHT_H__
#define __NVKM_WAMHT_H__
#incwude <cowe/gpuobj.h>
stwuct nvkm_object;

stwuct nvkm_wamht_data {
	stwuct nvkm_gpuobj *inst;
	int chid;
	u32 handwe;
};

stwuct nvkm_wamht {
	stwuct nvkm_device *device;
	stwuct nvkm_gpuobj *pawent;
	stwuct nvkm_gpuobj *gpuobj;
	int size;
	int bits;
	stwuct nvkm_wamht_data data[];
};

int  nvkm_wamht_new(stwuct nvkm_device *, u32 size, u32 awign,
		    stwuct nvkm_gpuobj *, stwuct nvkm_wamht **);
void nvkm_wamht_dew(stwuct nvkm_wamht **);
int  nvkm_wamht_insewt(stwuct nvkm_wamht *, stwuct nvkm_object *,
		       int chid, int addw, u32 handwe, u32 context);
void nvkm_wamht_wemove(stwuct nvkm_wamht *, int cookie);
stwuct nvkm_gpuobj *
nvkm_wamht_seawch(stwuct nvkm_wamht *, int chid, u32 handwe);
#endif
