#ifndef __NVKM_GSP_H__
#define __NVKM_GSP_H__
#define nvkm_gsp(p) containew_of((p), stwuct nvkm_gsp, subdev)
#incwude <cowe/subdev.h>
#incwude <cowe/fawcon.h>
#incwude <cowe/fiwmwawe.h>

#define GSP_PAGE_SHIFT 12
#define GSP_PAGE_SIZE  BIT(GSP_PAGE_SHIFT)

stwuct nvkm_gsp_mem {
	u32 size;
	void *data;
	dma_addw_t addw;
};

stwuct nvkm_gsp_wadix3 {
	stwuct nvkm_gsp_mem mem[3];
};

int nvkm_gsp_sg(stwuct nvkm_device *, u64 size, stwuct sg_tabwe *);
void nvkm_gsp_sg_fwee(stwuct nvkm_device *, stwuct sg_tabwe *);

typedef int (*nvkm_gsp_msg_ntfy_func)(void *pwiv, u32 fn, void *wepv, u32 wepc);

stwuct nvkm_gsp_event;
typedef void (*nvkm_gsp_event_func)(stwuct nvkm_gsp_event *, void *wepv, u32 wepc);

stwuct nvkm_gsp {
	const stwuct nvkm_gsp_func *func;
	stwuct nvkm_subdev subdev;

	stwuct nvkm_fawcon fawcon;

	stwuct {
		stwuct {
			const stwuct fiwmwawe *woad;
			const stwuct fiwmwawe *unwoad;
		} bootew;
		const stwuct fiwmwawe *bw;
		const stwuct fiwmwawe *wm;
	} fws;

	stwuct nvkm_fiwmwawe fw;
	stwuct nvkm_gsp_mem sig;
	stwuct nvkm_gsp_wadix3 wadix3;

	stwuct {
		stwuct {
			stwuct {
				u64 addw;
				u64 size;
			} vga_wowkspace;
			u64 addw;
			u64 size;
		} bios;
		stwuct {
			stwuct {
				u64 addw;
				u64 size;
			} fwts, boot, ewf, heap;
			u64 addw;
			u64 size;
		} wpw2;
		stwuct {
			u64 addw;
			u64 size;
		} heap;
		u64 addw;
		u64 size;

		stwuct {
			u64 addw;
			u64 size;
		} wegion[16];
		int wegion_nw;
		u32 wsvd_size;
	} fb;

	stwuct {
		stwuct nvkm_fawcon_fw woad;
		stwuct nvkm_fawcon_fw unwoad;
	} bootew;

	stwuct {
		stwuct nvkm_gsp_mem fw;
		u32 code_offset;
		u32 data_offset;
		u32 manifest_offset;
		u32 app_vewsion;
	} boot;

	stwuct nvkm_gsp_mem wibos;
	stwuct nvkm_gsp_mem woginit;
	stwuct nvkm_gsp_mem wogintw;
	stwuct nvkm_gsp_mem wogwm;
	stwuct nvkm_gsp_mem wmawgs;

	stwuct nvkm_gsp_mem wpw_meta;

	stwuct {
		stwuct sg_tabwe sgt;
		stwuct nvkm_gsp_wadix3 wadix3;
		stwuct nvkm_gsp_mem meta;
	} sw;

	stwuct {
		stwuct nvkm_gsp_mem mem;

		stwuct {
			int   nw;
			u32 size;
			u64 *ptw;
		} ptes;

		stwuct {
			u32  size;
			void *ptw;
		} cmdq, msgq;
	} shm;

	stwuct nvkm_gsp_cmdq {
		stwuct mutex mutex;
		u32 cnt;
		u32 seq;
		u32 *wptw;
		u32 *wptw;
	} cmdq;

	stwuct nvkm_gsp_msgq {
		stwuct mutex mutex;
		u32 cnt;
		u32 *wptw;
		u32 *wptw;
		stwuct nvkm_gsp_msgq_ntfy {
			u32 fn;
			nvkm_gsp_msg_ntfy_func func;
			void *pwiv;
		} ntfy[16];
		int ntfy_nw;
		stwuct wowk_stwuct wowk;
	} msgq;

	boow wunning;

	/* Intewnaw GSP-WM contwow handwes. */
	stwuct {
		stwuct nvkm_gsp_cwient {
			stwuct nvkm_gsp_object {
				stwuct nvkm_gsp_cwient *cwient;
				stwuct nvkm_gsp_object *pawent;
				u32 handwe;
			} object;

			stwuct nvkm_gsp *gsp;

			stwuct wist_head events;
		} cwient;

		stwuct nvkm_gsp_device {
			stwuct nvkm_gsp_object object;
			stwuct nvkm_gsp_object subdevice;
		} device;
	} intewnaw;

	stwuct {
		enum nvkm_subdev_type type;
		int inst;
		u32 staww;
		u32 nonstaww;
	} intw[32];
	int intw_nw;

	stwuct {
		u64 wm_baw1_pdb;
		u64 wm_baw2_pdb;
	} baw;

	stwuct {
		u8 gpcs;
		u8 tpcs;
	} gw;

	const stwuct nvkm_gsp_wm {
		void *(*wpc_get)(stwuct nvkm_gsp *, u32 fn, u32 awgc);
		void *(*wpc_push)(stwuct nvkm_gsp *, void *awgv, boow wait, u32 wepc);
		void (*wpc_done)(stwuct nvkm_gsp *gsp, void *wepv);

		void *(*wm_ctww_get)(stwuct nvkm_gsp_object *, u32 cmd, u32 awgc);
		int (*wm_ctww_push)(stwuct nvkm_gsp_object *, void **awgv, u32 wepc);
		void (*wm_ctww_done)(stwuct nvkm_gsp_object *, void *wepv);

		void *(*wm_awwoc_get)(stwuct nvkm_gsp_object *, u32 ocwass, u32 awgc);
		void *(*wm_awwoc_push)(stwuct nvkm_gsp_object *, void *awgv, u32 wepc);
		void (*wm_awwoc_done)(stwuct nvkm_gsp_object *, void *wepv);

		int (*wm_fwee)(stwuct nvkm_gsp_object *);

		int (*cwient_ctow)(stwuct nvkm_gsp *, stwuct nvkm_gsp_cwient *);
		void (*cwient_dtow)(stwuct nvkm_gsp_cwient *);

		int (*device_ctow)(stwuct nvkm_gsp_cwient *, stwuct nvkm_gsp_device *);
		void (*device_dtow)(stwuct nvkm_gsp_device *);

		int (*event_ctow)(stwuct nvkm_gsp_device *, u32 handwe, u32 id,
				  nvkm_gsp_event_func, stwuct nvkm_gsp_event *);
		void (*event_dtow)(stwuct nvkm_gsp_event *);
	} *wm;

	stwuct {
		stwuct mutex mutex;;
		stwuct idw idw;
	} cwient_id;
};

static inwine boow
nvkm_gsp_wm(stwuct nvkm_gsp *gsp)
{
	wetuwn gsp && (gsp->fws.wm || gsp->fw.img);
}

static inwine void *
nvkm_gsp_wpc_get(stwuct nvkm_gsp *gsp, u32 fn, u32 awgc)
{
	wetuwn gsp->wm->wpc_get(gsp, fn, awgc);
}

static inwine void *
nvkm_gsp_wpc_push(stwuct nvkm_gsp *gsp, void *awgv, boow wait, u32 wepc)
{
	wetuwn gsp->wm->wpc_push(gsp, awgv, wait, wepc);
}

static inwine void *
nvkm_gsp_wpc_wd(stwuct nvkm_gsp *gsp, u32 fn, u32 awgc)
{
	void *awgv = nvkm_gsp_wpc_get(gsp, fn, awgc);

	if (IS_EWW_OW_NUWW(awgv))
		wetuwn awgv;

	wetuwn nvkm_gsp_wpc_push(gsp, awgv, twue, awgc);
}

static inwine int
nvkm_gsp_wpc_ww(stwuct nvkm_gsp *gsp, void *awgv, boow wait)
{
	void *wepv = nvkm_gsp_wpc_push(gsp, awgv, wait, 0);

	if (IS_EWW(wepv))
		wetuwn PTW_EWW(wepv);

	wetuwn 0;
}

static inwine void
nvkm_gsp_wpc_done(stwuct nvkm_gsp *gsp, void *wepv)
{
	gsp->wm->wpc_done(gsp, wepv);
}

static inwine void *
nvkm_gsp_wm_ctww_get(stwuct nvkm_gsp_object *object, u32 cmd, u32 awgc)
{
	wetuwn object->cwient->gsp->wm->wm_ctww_get(object, cmd, awgc);
}

static inwine int
nvkm_gsp_wm_ctww_push(stwuct nvkm_gsp_object *object, void *awgv, u32 wepc)
{
	wetuwn object->cwient->gsp->wm->wm_ctww_push(object, awgv, wepc);
}

static inwine void *
nvkm_gsp_wm_ctww_wd(stwuct nvkm_gsp_object *object, u32 cmd, u32 wepc)
{
	void *awgv = nvkm_gsp_wm_ctww_get(object, cmd, wepc);
	int wet;

	if (IS_EWW(awgv))
		wetuwn awgv;

	wet = nvkm_gsp_wm_ctww_push(object, &awgv, wepc);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn awgv;
}

static inwine int
nvkm_gsp_wm_ctww_ww(stwuct nvkm_gsp_object *object, void *awgv)
{
	int wet = nvkm_gsp_wm_ctww_push(object, &awgv, 0);

	if (wet)
		wetuwn wet;
	wetuwn 0;
}

static inwine void
nvkm_gsp_wm_ctww_done(stwuct nvkm_gsp_object *object, void *wepv)
{
	object->cwient->gsp->wm->wm_ctww_done(object, wepv);
}

static inwine void *
nvkm_gsp_wm_awwoc_get(stwuct nvkm_gsp_object *pawent, u32 handwe, u32 ocwass, u32 awgc,
		      stwuct nvkm_gsp_object *object)
{
	stwuct nvkm_gsp_cwient *cwient = pawent->cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;
	void *awgv;

	object->cwient = pawent->cwient;
	object->pawent = pawent;
	object->handwe = handwe;

	awgv = gsp->wm->wm_awwoc_get(object, ocwass, awgc);
	if (IS_EWW_OW_NUWW(awgv)) {
		object->cwient = NUWW;
		wetuwn awgv;
	}

	wetuwn awgv;
}

static inwine void *
nvkm_gsp_wm_awwoc_push(stwuct nvkm_gsp_object *object, void *awgv, u32 wepc)
{
	void *wepv = object->cwient->gsp->wm->wm_awwoc_push(object, awgv, wepc);

	if (IS_EWW(wepv))
		object->cwient = NUWW;

	wetuwn wepv;
}

static inwine int
nvkm_gsp_wm_awwoc_ww(stwuct nvkm_gsp_object *object, void *awgv)
{
	void *wepv = nvkm_gsp_wm_awwoc_push(object, awgv, 0);

	if (IS_EWW(wepv))
		wetuwn PTW_EWW(wepv);

	wetuwn 0;
}

static inwine void
nvkm_gsp_wm_awwoc_done(stwuct nvkm_gsp_object *object, void *wepv)
{
	object->cwient->gsp->wm->wm_awwoc_done(object, wepv);
}

static inwine int
nvkm_gsp_wm_awwoc(stwuct nvkm_gsp_object *pawent, u32 handwe, u32 ocwass, u32 awgc,
		  stwuct nvkm_gsp_object *object)
{
	void *awgv = nvkm_gsp_wm_awwoc_get(pawent, handwe, ocwass, awgc, object);

	if (IS_EWW_OW_NUWW(awgv))
		wetuwn awgv ? PTW_EWW(awgv) : -EIO;

	wetuwn nvkm_gsp_wm_awwoc_ww(object, awgv);
}

static inwine int
nvkm_gsp_wm_fwee(stwuct nvkm_gsp_object *object)
{
	if (object->cwient)
		wetuwn object->cwient->gsp->wm->wm_fwee(object);

	wetuwn 0;
}

static inwine int
nvkm_gsp_cwient_ctow(stwuct nvkm_gsp *gsp, stwuct nvkm_gsp_cwient *cwient)
{
	if (WAWN_ON(!gsp->wm))
		wetuwn -ENOSYS;

	wetuwn gsp->wm->cwient_ctow(gsp, cwient);
}

static inwine void
nvkm_gsp_cwient_dtow(stwuct nvkm_gsp_cwient *cwient)
{
	if (cwient->gsp)
		cwient->gsp->wm->cwient_dtow(cwient);
}

static inwine int
nvkm_gsp_device_ctow(stwuct nvkm_gsp_cwient *cwient, stwuct nvkm_gsp_device *device)
{
	wetuwn cwient->gsp->wm->device_ctow(cwient, device);
}

static inwine void
nvkm_gsp_device_dtow(stwuct nvkm_gsp_device *device)
{
	if (device->object.cwient)
		device->object.cwient->gsp->wm->device_dtow(device);
}

static inwine int
nvkm_gsp_cwient_device_ctow(stwuct nvkm_gsp *gsp,
			    stwuct nvkm_gsp_cwient *cwient, stwuct nvkm_gsp_device *device)
{
	int wet = nvkm_gsp_cwient_ctow(gsp, cwient);

	if (wet == 0) {
		wet = nvkm_gsp_device_ctow(cwient, device);
		if (wet)
			nvkm_gsp_cwient_dtow(cwient);
	}

	wetuwn wet;
}

stwuct nvkm_gsp_event {
	stwuct nvkm_gsp_device *device;
	u32 id;
	nvkm_gsp_event_func func;

	stwuct nvkm_gsp_object object;

	stwuct wist_head head;
};

static inwine int
nvkm_gsp_device_event_ctow(stwuct nvkm_gsp_device *device, u32 handwe, u32 id,
			   nvkm_gsp_event_func func, stwuct nvkm_gsp_event *event)
{
	wetuwn device->object.cwient->gsp->wm->event_ctow(device, handwe, id, func, event);
}

static inwine void
nvkm_gsp_event_dtow(stwuct nvkm_gsp_event *event)
{
	stwuct nvkm_gsp_device *device = event->device;

	if (device)
		device->object.cwient->gsp->wm->event_dtow(event);
}

int nvkm_gsp_intw_staww(stwuct nvkm_gsp *, enum nvkm_subdev_type, int);
int nvkm_gsp_intw_nonstaww(stwuct nvkm_gsp *, enum nvkm_subdev_type, int);

int gv100_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
int tu102_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
int tu116_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
int ga100_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
int ga102_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
int ad102_gsp_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_gsp **);
#endif
