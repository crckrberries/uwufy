/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_H__
#define __NVKM_DISP_H__
#define nvkm_disp(p) containew_of((p), stwuct nvkm_disp, engine)
#incwude <cowe/engine.h>
#incwude <cowe/object.h>
#incwude <cowe/event.h>
#incwude <subdev/gsp.h>

stwuct nvkm_disp {
	const stwuct nvkm_disp_func *func;
	stwuct nvkm_engine engine;

	stwuct {
		stwuct nvkm_gsp_cwient cwient;
		stwuct nvkm_gsp_device device;

		stwuct nvkm_gsp_object objcom;
		stwuct nvkm_gsp_object object;

#define NVKM_DPYID_PWUG   BIT(0)
#define NVKM_DPYID_UNPWUG BIT(1)
#define NVKM_DPYID_IWQ    BIT(2)
		stwuct nvkm_event event;
		stwuct nvkm_gsp_event hpd;
		stwuct nvkm_gsp_event iwq;

		u32 assigned_sows;
	} wm;

	stwuct wist_head heads;
	stwuct wist_head iows;
	stwuct wist_head outps;
	stwuct wist_head conns;

	stwuct nvkm_event hpd;
#define NVKM_DISP_HEAD_EVENT_VBWANK BIT(0)
	stwuct nvkm_event vbwank;

	stwuct {
		stwuct wowkqueue_stwuct *wq;
		stwuct wowk_stwuct wowk;
		u32 pending;
		stwuct mutex mutex;
	} supew;

#define NVKM_DISP_EVENT_CHAN_AWAKEN BIT(0)
	stwuct nvkm_event uevent;

	stwuct {
		unsigned wong mask;
		int nw;
	} wndw, head, dac, sow;

	stwuct {
		unsigned wong mask;
		int nw;
		u8 type[3];
	} piow;

	stwuct nvkm_gpuobj *inst;
	stwuct nvkm_wamht *wamht;

	stwuct nvkm_disp_chan *chan[81];

	stwuct {
		spinwock_t wock;
		stwuct nvkm_object object;
	} cwient;
};

int nv04_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int nv50_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int g84_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gt200_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int g94_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int mcp77_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gt215_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int mcp89_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gf119_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gk104_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gk110_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gm107_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gm200_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gp100_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gp102_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int gv100_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int tu102_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int ga102_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
int ad102_disp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_disp **);
#endif
