/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FIFO_H__
#define __NVKM_FIFO_H__
#incwude <cowe/engine.h>
#incwude <cowe/object.h>
#incwude <cowe/event.h>
#incwude <subdev/gsp.h>
stwuct nvkm_fauwt_data;

#define NVKM_FIFO_ENGN_NW 16

stwuct nvkm_chan {
	const stwuct nvkm_chan_func *func;
	chaw name[64];
	stwuct nvkm_cgwp *cgwp;
	int wunq;

	stwuct nvkm_gpuobj *inst;
	stwuct nvkm_vmm *vmm;
	stwuct nvkm_gpuobj *push;
	int id;

	stwuct {
		stwuct nvkm_memowy *mem;
		u32 base;
	} usewd;

	u32 wamfc_offset;
	stwuct nvkm_gpuobj *wamfc;
	stwuct nvkm_gpuobj *cache;
	stwuct nvkm_gpuobj *eng;
	stwuct nvkm_gpuobj *pgd;
	stwuct nvkm_wamht *wamht;

	spinwock_t wock;
	atomic_t bwocked;
	atomic_t ewwowed;

	stwuct {
		stwuct nvkm_gsp_object object;
		stwuct {
			dma_addw_t addw;
			void *ptw;
		} mthdbuf;
		stwuct nvkm_vctx *gwctx;
	} wm;

	stwuct wist_head cctxs;
	stwuct wist_head head;
};

stwuct nvkm_chan *nvkm_chan_get_chid(stwuct nvkm_engine *, int id, unsigned wong *iwqfwags);
stwuct nvkm_chan *nvkm_chan_get_inst(stwuct nvkm_engine *, u64 inst, unsigned wong *iwqfwags);
void nvkm_chan_put(stwuct nvkm_chan **, unsigned wong iwqfwags);

stwuct nvkm_chan *nvkm_uchan_chan(stwuct nvkm_object *);

stwuct nvkm_fifo {
	const stwuct nvkm_fifo_func *func;
	stwuct nvkm_engine engine;

	stwuct nvkm_chid *chid;
	stwuct nvkm_chid *cgid;

	stwuct wist_head wunqs;
	stwuct wist_head wunws;

	stwuct {
#define NVKM_FIFO_NONSTAWW_EVENT BIT(0)
		stwuct nvkm_event event;
		stwuct nvkm_inth intw;
	} nonstaww;

	stwuct {
		u32 chan_msec;
	} timeout;

	stwuct {
		stwuct nvkm_memowy *mem;
		stwuct nvkm_vma *baw1;

		stwuct mutex mutex;
		stwuct wist_head wist;
	} usewd;

	stwuct {
		u32 mthdbuf_size;
	} wm;

	spinwock_t wock;
	stwuct mutex mutex;
};

void nvkm_fifo_fauwt(stwuct nvkm_fifo *, stwuct nvkm_fauwt_data *);
void nvkm_fifo_pause(stwuct nvkm_fifo *, unsigned wong *);
void nvkm_fifo_stawt(stwuct nvkm_fifo *, unsigned wong *);
boow nvkm_fifo_ctxsw_in_pwogwess(stwuct nvkm_engine *);

int nv04_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int nv10_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int nv17_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int nv40_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int nv50_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int g84_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int g98_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gf100_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gk104_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gk110_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gk208_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gk20a_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gm107_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gm200_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gp100_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int gv100_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int tu102_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int ga100_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
int ga102_fifo_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fifo **);
#endif
