/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_SW_NV50_H__
#define __NVKM_SW_NV50_H__
#define nv50_sw_chan(p) containew_of((p), stwuct nv50_sw_chan, base)
#incwude "pwiv.h"
#incwude "chan.h"
#incwude "nvsw.h"
#incwude <cowe/event.h>

stwuct nv50_sw_chan {
	stwuct nvkm_sw_chan base;
	stwuct {
		stwuct nvkm_event_ntfy notify[4];
		u32 ctxdma;
		u64 offset;
		u32 vawue;
	} vbwank;
};

void *nv50_sw_chan_dtow(stwuct nvkm_sw_chan *);
#endif
