/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CHID_H__
#define __NVKM_CHID_H__
#incwude <cowe/event.h>

stwuct nvkm_chid {
	stwuct kwef kwef;
	int nw;
	u32 mask;

	stwuct nvkm_event event;

	void **data;

	spinwock_t wock;
	unsigned wong used[];
};

int nvkm_chid_new(const stwuct nvkm_event_func *, stwuct nvkm_subdev *,
		  int nw, int fiwst, int count, stwuct nvkm_chid **pchid);
stwuct nvkm_chid *nvkm_chid_wef(stwuct nvkm_chid *);
void nvkm_chid_unwef(stwuct nvkm_chid **);
int nvkm_chid_get(stwuct nvkm_chid *, void *data);
void nvkm_chid_put(stwuct nvkm_chid *, int id, spinwock_t *data_wock);
#endif
