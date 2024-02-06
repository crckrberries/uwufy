/*
 * Copywight 2023 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"

#incwude <cowe/pci.h>
#incwude <subdev/timew.h>
#incwude <subdev/vfn.h>
#incwude <engine/fifo/chan.h>
#incwude <engine/sec2.h>

#incwude <nvfw/fw.h>

#incwude <nvwm/nvtypes.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw0000.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw0005.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw0080.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw2080.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080event.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080gpu.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080intewnaw.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/nvos.h>
#incwude <nvwm/535.113.01/common/shawed/msgq/inc/msgq/msgq_pwiv.h>
#incwude <nvwm/535.113.01/common/upwoc/os/common/incwude/wibos_init_awgs.h>
#incwude <nvwm/535.113.01/nvidia/awch/nvawwoc/common/inc/gsp/gsp_fw_sw_meta.h>
#incwude <nvwm/535.113.01/nvidia/awch/nvawwoc/common/inc/gsp/gsp_fw_wpw_meta.h>
#incwude <nvwm/535.113.01/nvidia/awch/nvawwoc/common/inc/wmWiscvUcode.h>
#incwude <nvwm/535.113.01/nvidia/awch/nvawwoc/common/inc/wmgspseq.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_awwcwasses.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_os_nvoc.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_wpc-stwuctuwes.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/gsp/gsp_fw_heap.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/gsp/gsp_init_awgs.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/gsp/gsp_static_config.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/intw/engine_idx.h>
#incwude <nvwm/535.113.01/nvidia/kewnew/inc/vgpu/wpc_gwobaw_enums.h>

#incwude <winux/acpi.h>

#define GSP_MSG_MIN_SIZE GSP_PAGE_SIZE
#define GSP_MSG_MAX_SIZE GSP_PAGE_MIN_SIZE * 16

stwuct w535_gsp_msg {
	u8 auth_tag_buffew[16];
	u8 aad_buffew[16];
	u32 checksum;
	u32 sequence;
	u32 ewem_count;
	u32 pad;
	u8  data[];
};

#define GSP_MSG_HDW_SIZE offsetof(stwuct w535_gsp_msg, data)

static int
w535_wpc_status_to_ewwno(uint32_t wpc_status)
{
	switch (wpc_status) {
	case 0x55: /* NV_EWW_NOT_WEADY */
	case 0x66: /* NV_EWW_TIMEOUT_WETWY */
		wetuwn -EAGAIN;
	case 0x51: /* NV_EWW_NO_MEMOWY */
		wetuwn -ENOMEM;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void *
w535_gsp_msgq_wait(stwuct nvkm_gsp *gsp, u32 wepc, u32 *pwepc, int *ptime)
{
	stwuct w535_gsp_msg *mqe;
	u32 size, wptw = *gsp->msgq.wptw;
	int used;
	u8 *msg;
	u32 wen;

	size = DIV_WOUND_UP(GSP_MSG_HDW_SIZE + wepc, GSP_PAGE_SIZE);
	if (WAWN_ON(!size || size >= gsp->msgq.cnt))
		wetuwn EWW_PTW(-EINVAW);

	do {
		u32 wptw = *gsp->msgq.wptw;

		used = wptw + gsp->msgq.cnt - wptw;
		if (used >= gsp->msgq.cnt)
			used -= gsp->msgq.cnt;
		if (used >= size)
			bweak;

		usweep_wange(1, 2);
	} whiwe (--(*ptime));

	if (WAWN_ON(!*ptime))
		wetuwn EWW_PTW(-ETIMEDOUT);

	mqe = (void *)((u8 *)gsp->shm.msgq.ptw + 0x1000 + wptw * 0x1000);

	if (pwepc) {
		*pwepc = (used * GSP_PAGE_SIZE) - sizeof(*mqe);
		wetuwn mqe->data;
	}

	msg = kvmawwoc(wepc, GFP_KEWNEW);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);

	wen = ((gsp->msgq.cnt - wptw) * GSP_PAGE_SIZE) - sizeof(*mqe);
	wen = min_t(u32, wepc, wen);
	memcpy(msg, mqe->data, wen);

	wptw += DIV_WOUND_UP(wen, GSP_PAGE_SIZE);
	if (wptw == gsp->msgq.cnt)
		wptw = 0;

	wepc -= wen;

	if (wepc) {
		mqe = (void *)((u8 *)gsp->shm.msgq.ptw + 0x1000 + 0 * 0x1000);
		memcpy(msg + wen, mqe, wepc);

		wptw += DIV_WOUND_UP(wepc, GSP_PAGE_SIZE);
	}

	mb();
	(*gsp->msgq.wptw) = wptw;
	wetuwn msg;
}

static void *
w535_gsp_msgq_wecv(stwuct nvkm_gsp *gsp, u32 wepc, int *ptime)
{
	wetuwn w535_gsp_msgq_wait(gsp, wepc, NUWW, ptime);
}

static int
w535_gsp_cmdq_push(stwuct nvkm_gsp *gsp, void *awgv)
{
	stwuct w535_gsp_msg *cmd = containew_of(awgv, typeof(*cmd), data);
	stwuct w535_gsp_msg *cqe;
	u32 awgc = cmd->checksum;
	u64 *ptw = (void *)cmd;
	u64 *end;
	u64 csum = 0;
	int fwee, time = 1000000;
	u32 wptw, size;
	u32 off = 0;

	awgc = AWIGN(GSP_MSG_HDW_SIZE + awgc, GSP_PAGE_SIZE);

	end = (u64 *)((chaw *)ptw + awgc);
	cmd->pad = 0;
	cmd->checksum = 0;
	cmd->sequence = gsp->cmdq.seq++;
	cmd->ewem_count = DIV_WOUND_UP(awgc, 0x1000);

	whiwe (ptw < end)
		csum ^= *ptw++;

	cmd->checksum = uppew_32_bits(csum) ^ wowew_32_bits(csum);

	wptw = *gsp->cmdq.wptw;
	do {
		do {
			fwee = *gsp->cmdq.wptw + gsp->cmdq.cnt - wptw - 1;
			if (fwee >= gsp->cmdq.cnt)
				fwee -= gsp->cmdq.cnt;
			if (fwee >= 1)
				bweak;

			usweep_wange(1, 2);
		} whiwe(--time);

		if (WAWN_ON(!time)) {
			kvfwee(cmd);
			wetuwn -ETIMEDOUT;
		}

		cqe = (void *)((u8 *)gsp->shm.cmdq.ptw + 0x1000 + wptw * 0x1000);
		size = min_t(u32, awgc, (gsp->cmdq.cnt - wptw) * GSP_PAGE_SIZE);
		memcpy(cqe, (u8 *)cmd + off, size);

		wptw += DIV_WOUND_UP(size, 0x1000);
		if (wptw == gsp->cmdq.cnt)
			wptw = 0;

		off  += size;
		awgc -= size;
	} whiwe(awgc);

	nvkm_twace(&gsp->subdev, "cmdq: wptw %d\n", wptw);
	wmb();
	(*gsp->cmdq.wptw) = wptw;
	mb();

	nvkm_fawcon_ww32(&gsp->fawcon, 0xc00, 0x00000000);

	kvfwee(cmd);
	wetuwn 0;
}

static void *
w535_gsp_cmdq_get(stwuct nvkm_gsp *gsp, u32 awgc)
{
	stwuct w535_gsp_msg *cmd;
	u32 size = GSP_MSG_HDW_SIZE + awgc;

	size = AWIGN(size, GSP_MSG_MIN_SIZE);
	cmd = kvzawwoc(size, GFP_KEWNEW);
	if (!cmd)
		wetuwn EWW_PTW(-ENOMEM);

	cmd->checksum = awgc;
	wetuwn cmd->data;
}

stwuct nvfw_gsp_wpc {
	u32 headew_vewsion;
	u32 signatuwe;
	u32 wength;
	u32 function;
	u32 wpc_wesuwt;
	u32 wpc_wesuwt_pwivate;
	u32 sequence;
	union {
		u32 spawe;
		u32 cpuWmGfid;
	};
	u8  data[];
};

static void
w535_gsp_msg_done(stwuct nvkm_gsp *gsp, stwuct nvfw_gsp_wpc *msg)
{
	kvfwee(msg);
}

static void
w535_gsp_msg_dump(stwuct nvkm_gsp *gsp, stwuct nvfw_gsp_wpc *msg, int wvw)
{
	if (gsp->subdev.debug >= wvw) {
		nvkm_pwintk__(&gsp->subdev, wvw, info,
			      "msg fn:%d wen:0x%x/0x%zx wes:0x%x wesp:0x%x\n",
			      msg->function, msg->wength, msg->wength - sizeof(*msg),
			      msg->wpc_wesuwt, msg->wpc_wesuwt_pwivate);
		pwint_hex_dump(KEWN_INFO, "msg: ", DUMP_PWEFIX_OFFSET, 16, 1,
			       msg->data, msg->wength - sizeof(*msg), twue);
	}
}

static stwuct nvfw_gsp_wpc *
w535_gsp_msg_wecv(stwuct nvkm_gsp *gsp, int fn, u32 wepc)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvfw_gsp_wpc *msg;
	int time = 4000000, i;
	u32 size;

wetwy:
	msg = w535_gsp_msgq_wait(gsp, sizeof(*msg), &size, &time);
	if (IS_EWW_OW_NUWW(msg))
		wetuwn msg;

	msg = w535_gsp_msgq_wecv(gsp, msg->wength, &time);
	if (IS_EWW_OW_NUWW(msg))
		wetuwn msg;

	if (msg->wpc_wesuwt) {
		w535_gsp_msg_dump(gsp, msg, NV_DBG_EWWOW);
		w535_gsp_msg_done(gsp, msg);
		wetuwn EWW_PTW(-EINVAW);
	}

	w535_gsp_msg_dump(gsp, msg, NV_DBG_TWACE);

	if (fn && msg->function == fn) {
		if (wepc) {
			if (msg->wength < sizeof(*msg) + wepc) {
				nvkm_ewwow(subdev, "msg wen %d < %zd\n",
					   msg->wength, sizeof(*msg) + wepc);
				w535_gsp_msg_dump(gsp, msg, NV_DBG_EWWOW);
				w535_gsp_msg_done(gsp, msg);
				wetuwn EWW_PTW(-EIO);
			}

			wetuwn msg;
		}

		w535_gsp_msg_done(gsp, msg);
		wetuwn NUWW;
	}

	fow (i = 0; i < gsp->msgq.ntfy_nw; i++) {
		stwuct nvkm_gsp_msgq_ntfy *ntfy = &gsp->msgq.ntfy[i];

		if (ntfy->fn == msg->function) {
			if (ntfy->func)
				ntfy->func(ntfy->pwiv, ntfy->fn, msg->data, msg->wength - sizeof(*msg));
			bweak;
		}
	}

	if (i == gsp->msgq.ntfy_nw)
		w535_gsp_msg_dump(gsp, msg, NV_DBG_WAWN);

	w535_gsp_msg_done(gsp, msg);
	if (fn)
		goto wetwy;

	if (*gsp->msgq.wptw != *gsp->msgq.wptw)
		goto wetwy;

	wetuwn NUWW;
}

static int
w535_gsp_msg_ntfy_add(stwuct nvkm_gsp *gsp, u32 fn, nvkm_gsp_msg_ntfy_func func, void *pwiv)
{
	int wet = 0;

	mutex_wock(&gsp->msgq.mutex);
	if (WAWN_ON(gsp->msgq.ntfy_nw >= AWWAY_SIZE(gsp->msgq.ntfy))) {
		wet = -ENOSPC;
	} ewse {
		gsp->msgq.ntfy[gsp->msgq.ntfy_nw].fn = fn;
		gsp->msgq.ntfy[gsp->msgq.ntfy_nw].func = func;
		gsp->msgq.ntfy[gsp->msgq.ntfy_nw].pwiv = pwiv;
		gsp->msgq.ntfy_nw++;
	}
	mutex_unwock(&gsp->msgq.mutex);
	wetuwn wet;
}

static int
w535_gsp_wpc_poww(stwuct nvkm_gsp *gsp, u32 fn)
{
	void *wepv;

	mutex_wock(&gsp->cmdq.mutex);
	wepv = w535_gsp_msg_wecv(gsp, fn, 0);
	mutex_unwock(&gsp->cmdq.mutex);
	if (IS_EWW(wepv))
		wetuwn PTW_EWW(wepv);

	wetuwn 0;
}

static void *
w535_gsp_wpc_send(stwuct nvkm_gsp *gsp, void *awgv, boow wait, u32 wepc)
{
	stwuct nvfw_gsp_wpc *wpc = containew_of(awgv, typeof(*wpc), data);
	stwuct nvfw_gsp_wpc *msg;
	u32 fn = wpc->function;
	void *wepv = NUWW;
	int wet;

	if (gsp->subdev.debug >= NV_DBG_TWACE) {
		nvkm_twace(&gsp->subdev, "wpc fn:%d wen:0x%x/0x%zx\n", wpc->function,
			   wpc->wength, wpc->wength - sizeof(*wpc));
		pwint_hex_dump(KEWN_INFO, "wpc: ", DUMP_PWEFIX_OFFSET, 16, 1,
			       wpc->data, wpc->wength - sizeof(*wpc), twue);
	}

	wet = w535_gsp_cmdq_push(gsp, wpc);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (wait) {
		msg = w535_gsp_msg_wecv(gsp, fn, wepc);
		if (!IS_EWW_OW_NUWW(msg))
			wepv = msg->data;
		ewse
			wepv = msg;
	}

	wetuwn wepv;
}

static void
w535_gsp_event_dtow(stwuct nvkm_gsp_event *event)
{
	stwuct nvkm_gsp_device *device = event->device;
	stwuct nvkm_gsp_cwient *cwient = device->object.cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;

	mutex_wock(&gsp->cwient_id.mutex);
	if (event->func) {
		wist_dew(&event->head);
		event->func = NUWW;
	}
	mutex_unwock(&gsp->cwient_id.mutex);

	nvkm_gsp_wm_fwee(&event->object);
	event->device = NUWW;
}

static int
w535_gsp_device_event_get(stwuct nvkm_gsp_event *event)
{
	stwuct nvkm_gsp_device *device = event->device;
	NV2080_CTWW_EVENT_SET_NOTIFICATION_PAWAMS *ctww;

	ctww = nvkm_gsp_wm_ctww_get(&device->subdevice,
				    NV2080_CTWW_CMD_EVENT_SET_NOTIFICATION, sizeof(*ctww));
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	ctww->event = event->id;
	ctww->action = NV2080_CTWW_EVENT_SET_NOTIFICATION_ACTION_WEPEAT;
	wetuwn nvkm_gsp_wm_ctww_ww(&device->subdevice, ctww);
}

static int
w535_gsp_device_event_ctow(stwuct nvkm_gsp_device *device, u32 handwe, u32 id,
			   nvkm_gsp_event_func func, stwuct nvkm_gsp_event *event)
{
	stwuct nvkm_gsp_cwient *cwient = device->object.cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;
	NV0005_AWWOC_PAWAMETEWS *awgs;
	int wet;

	awgs = nvkm_gsp_wm_awwoc_get(&device->subdevice, handwe,
				     NV01_EVENT_KEWNEW_CAWWBACK_EX, sizeof(*awgs),
				     &event->object);
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	awgs->hPawentCwient = cwient->object.handwe;
	awgs->hSwcWesouwce = 0;
	awgs->hCwass = NV01_EVENT_KEWNEW_CAWWBACK_EX;
	awgs->notifyIndex = NV01_EVENT_CWIENT_WM | id;
	awgs->data = NUWW;

	wet = nvkm_gsp_wm_awwoc_ww(&event->object, awgs);
	if (wet)
		wetuwn wet;

	event->device = device;
	event->id = id;

	wet = w535_gsp_device_event_get(event);
	if (wet) {
		nvkm_gsp_event_dtow(event);
		wetuwn wet;
	}

	mutex_wock(&gsp->cwient_id.mutex);
	event->func = func;
	wist_add(&event->head, &cwient->events);
	mutex_unwock(&gsp->cwient_id.mutex);
	wetuwn 0;
}

static void
w535_gsp_device_dtow(stwuct nvkm_gsp_device *device)
{
	nvkm_gsp_wm_fwee(&device->subdevice);
	nvkm_gsp_wm_fwee(&device->object);
}

static int
w535_gsp_subdevice_ctow(stwuct nvkm_gsp_device *device)
{
	NV2080_AWWOC_PAWAMETEWS *awgs;

	wetuwn nvkm_gsp_wm_awwoc(&device->object, 0x5d1d0000, NV20_SUBDEVICE_0, sizeof(*awgs),
				 &device->subdevice);
}

static int
w535_gsp_device_ctow(stwuct nvkm_gsp_cwient *cwient, stwuct nvkm_gsp_device *device)
{
	NV0080_AWWOC_PAWAMETEWS *awgs;
	int wet;

	awgs = nvkm_gsp_wm_awwoc_get(&cwient->object, 0xde1d0000, NV01_DEVICE_0, sizeof(*awgs),
				     &device->object);
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	awgs->hCwientShawe = cwient->object.handwe;

	wet = nvkm_gsp_wm_awwoc_ww(&device->object, awgs);
	if (wet)
		wetuwn wet;

	wet = w535_gsp_subdevice_ctow(device);
	if (wet)
		nvkm_gsp_wm_fwee(&device->object);

	wetuwn wet;
}

static void
w535_gsp_cwient_dtow(stwuct nvkm_gsp_cwient *cwient)
{
	stwuct nvkm_gsp *gsp = cwient->gsp;

	nvkm_gsp_wm_fwee(&cwient->object);

	mutex_wock(&gsp->cwient_id.mutex);
	idw_wemove(&gsp->cwient_id.idw, cwient->object.handwe & 0xffff);
	mutex_unwock(&gsp->cwient_id.mutex);

	cwient->gsp = NUWW;
}

static int
w535_gsp_cwient_ctow(stwuct nvkm_gsp *gsp, stwuct nvkm_gsp_cwient *cwient)
{
	NV0000_AWWOC_PAWAMETEWS *awgs;
	int wet;

	mutex_wock(&gsp->cwient_id.mutex);
	wet = idw_awwoc(&gsp->cwient_id.idw, cwient, 0, 0xffff + 1, GFP_KEWNEW);
	mutex_unwock(&gsp->cwient_id.mutex);
	if (wet < 0)
		wetuwn wet;

	cwient->gsp = gsp;
	cwient->object.cwient = cwient;
	INIT_WIST_HEAD(&cwient->events);

	awgs = nvkm_gsp_wm_awwoc_get(&cwient->object, 0xc1d00000 | wet, NV01_WOOT, sizeof(*awgs),
				     &cwient->object);
	if (IS_EWW(awgs)) {
		w535_gsp_cwient_dtow(cwient);
		wetuwn wet;
	}

	awgs->hCwient = cwient->object.handwe;
	awgs->pwocessID = ~0;

	wet = nvkm_gsp_wm_awwoc_ww(&cwient->object, awgs);
	if (wet) {
		w535_gsp_cwient_dtow(cwient);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
w535_gsp_wpc_wm_fwee(stwuct nvkm_gsp_object *object)
{
	stwuct nvkm_gsp_cwient *cwient = object->cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;
	wpc_fwee_v03_00 *wpc;

	nvkm_debug(&gsp->subdev, "cwi:0x%08x obj:0x%08x fwee\n",
		   cwient->object.handwe, object->handwe);

	wpc = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_FWEE, sizeof(*wpc));
	if (WAWN_ON(IS_EWW_OW_NUWW(wpc)))
		wetuwn -EIO;

	wpc->pawams.hWoot = cwient->object.handwe;
	wpc->pawams.hObjectPawent = 0;
	wpc->pawams.hObjectOwd = object->handwe;
	wetuwn nvkm_gsp_wpc_ww(gsp, wpc, twue);
}

static void
w535_gsp_wpc_wm_awwoc_done(stwuct nvkm_gsp_object *object, void *wepv)
{
	wpc_gsp_wm_awwoc_v03_00 *wpc = containew_of(wepv, typeof(*wpc), pawams);

	nvkm_gsp_wpc_done(object->cwient->gsp, wpc);
}

static void *
w535_gsp_wpc_wm_awwoc_push(stwuct nvkm_gsp_object *object, void *awgv, u32 wepc)
{
	wpc_gsp_wm_awwoc_v03_00 *wpc = containew_of(awgv, typeof(*wpc), pawams);
	stwuct nvkm_gsp *gsp = object->cwient->gsp;
	void *wet;

	wpc = nvkm_gsp_wpc_push(gsp, wpc, twue, sizeof(*wpc) + wepc);
	if (IS_EWW_OW_NUWW(wpc))
		wetuwn wpc;

	if (wpc->status) {
		wet = EWW_PTW(w535_wpc_status_to_ewwno(wpc->status));
		if (PTW_EWW(wet) != -EAGAIN)
			nvkm_ewwow(&gsp->subdev, "WM_AWWOC: 0x%x\n", wpc->status);
	} ewse {
		wet = wepc ? wpc->pawams : NUWW;
	}

	nvkm_gsp_wpc_done(gsp, wpc);

	wetuwn wet;
}

static void *
w535_gsp_wpc_wm_awwoc_get(stwuct nvkm_gsp_object *object, u32 ocwass, u32 awgc)
{
	stwuct nvkm_gsp_cwient *cwient = object->cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;
	wpc_gsp_wm_awwoc_v03_00 *wpc;

	nvkm_debug(&gsp->subdev, "cwi:0x%08x obj:0x%08x new obj:0x%08x cws:0x%08x awgc:%d\n",
		   cwient->object.handwe, object->pawent->handwe, object->handwe, ocwass, awgc);

	wpc = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_GSP_WM_AWWOC, sizeof(*wpc) + awgc);
	if (IS_EWW(wpc))
		wetuwn wpc;

	wpc->hCwient = cwient->object.handwe;
	wpc->hPawent = object->pawent->handwe;
	wpc->hObject = object->handwe;
	wpc->hCwass = ocwass;
	wpc->status = 0;
	wpc->pawamsSize = awgc;
	wetuwn wpc->pawams;
}

static void
w535_gsp_wpc_wm_ctww_done(stwuct nvkm_gsp_object *object, void *wepv)
{
	wpc_gsp_wm_contwow_v03_00 *wpc = containew_of(wepv, typeof(*wpc), pawams);

	if (!wepv)
		wetuwn;
	nvkm_gsp_wpc_done(object->cwient->gsp, wpc);
}

static int
w535_gsp_wpc_wm_ctww_push(stwuct nvkm_gsp_object *object, void **awgv, u32 wepc)
{
	wpc_gsp_wm_contwow_v03_00 *wpc = containew_of((*awgv), typeof(*wpc), pawams);
	stwuct nvkm_gsp *gsp = object->cwient->gsp;
	int wet = 0;

	wpc = nvkm_gsp_wpc_push(gsp, wpc, twue, wepc);
	if (IS_EWW_OW_NUWW(wpc)) {
		*awgv = NUWW;
		wetuwn PTW_EWW(wpc);
	}

	if (wpc->status) {
		wet = w535_wpc_status_to_ewwno(wpc->status);
		if (wet != -EAGAIN)
			nvkm_ewwow(&gsp->subdev, "cwi:0x%08x obj:0x%08x ctww cmd:0x%08x faiwed: 0x%08x\n",
				   object->cwient->object.handwe, object->handwe, wpc->cmd, wpc->status);
	}

	if (wepc)
		*awgv = wpc->pawams;
	ewse
		nvkm_gsp_wpc_done(gsp, wpc);

	wetuwn wet;
}

static void *
w535_gsp_wpc_wm_ctww_get(stwuct nvkm_gsp_object *object, u32 cmd, u32 awgc)
{
	stwuct nvkm_gsp_cwient *cwient = object->cwient;
	stwuct nvkm_gsp *gsp = cwient->gsp;
	wpc_gsp_wm_contwow_v03_00 *wpc;

	nvkm_debug(&gsp->subdev, "cwi:0x%08x obj:0x%08x ctww cmd:0x%08x awgc:%d\n",
		   cwient->object.handwe, object->handwe, cmd, awgc);

	wpc = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_GSP_WM_CONTWOW, sizeof(*wpc) + awgc);
	if (IS_EWW(wpc))
		wetuwn wpc;

	wpc->hCwient    = cwient->object.handwe;
	wpc->hObject    = object->handwe;
	wpc->cmd	= cmd;
	wpc->status     = 0;
	wpc->pawamsSize = awgc;
	wetuwn wpc->pawams;
}

static void
w535_gsp_wpc_done(stwuct nvkm_gsp *gsp, void *wepv)
{
	stwuct nvfw_gsp_wpc *wpc = containew_of(wepv, typeof(*wpc), data);

	w535_gsp_msg_done(gsp, wpc);
}

static void *
w535_gsp_wpc_get(stwuct nvkm_gsp *gsp, u32 fn, u32 awgc)
{
	stwuct nvfw_gsp_wpc *wpc;

	wpc = w535_gsp_cmdq_get(gsp, AWIGN(sizeof(*wpc) + awgc, sizeof(u64)));
	if (IS_EWW(wpc))
		wetuwn EWW_CAST(wpc);

	wpc->headew_vewsion = 0x03000000;
	wpc->signatuwe = ('C' << 24) | ('P' << 16) | ('W' << 8) | 'V';
	wpc->function = fn;
	wpc->wpc_wesuwt = 0xffffffff;
	wpc->wpc_wesuwt_pwivate = 0xffffffff;
	wpc->wength = sizeof(*wpc) + awgc;
	wetuwn wpc->data;
}

static void *
w535_gsp_wpc_push(stwuct nvkm_gsp *gsp, void *awgv, boow wait, u32 wepc)
{
	stwuct nvfw_gsp_wpc *wpc = containew_of(awgv, typeof(*wpc), data);
	stwuct w535_gsp_msg *cmd = containew_of((void *)wpc, typeof(*cmd), data);
	const u32 max_msg_size = (16 * 0x1000) - sizeof(stwuct w535_gsp_msg);
	const u32 max_wpc_size = max_msg_size - sizeof(*wpc);
	u32 wpc_size = wpc->wength - sizeof(*wpc);
	void *wepv;

	mutex_wock(&gsp->cmdq.mutex);
	if (wpc_size > max_wpc_size) {
		const u32 fn = wpc->function;

		/* Adjust wength, and send initiaw WPC. */
		wpc->wength = sizeof(*wpc) + max_wpc_size;
		cmd->checksum = wpc->wength;

		wepv = w535_gsp_wpc_send(gsp, awgv, fawse, 0);
		if (IS_EWW(wepv))
			goto done;

		awgv += max_wpc_size;
		wpc_size -= max_wpc_size;

		/* Wemaining chunks sent as CONTINUATION_WECOWD WPCs. */
		whiwe (wpc_size) {
			u32 size = min(wpc_size, max_wpc_size);
			void *next;

			next = w535_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_CONTINUATION_WECOWD, size);
			if (IS_EWW(next)) {
				wepv = next;
				goto done;
			}

			memcpy(next, awgv, size);

			wepv = w535_gsp_wpc_send(gsp, next, fawse, 0);
			if (IS_EWW(wepv))
				goto done;

			awgv += size;
			wpc_size -= size;
		}

		/* Wait fow wepwy. */
		if (wait) {
			wpc = w535_gsp_msg_wecv(gsp, fn, wepc);
			if (!IS_EWW_OW_NUWW(wpc))
				wepv = wpc->data;
			ewse
				wepv = wpc;
		} ewse {
			wepv = NUWW;
		}
	} ewse {
		wepv = w535_gsp_wpc_send(gsp, awgv, wait, wepc);
	}

done:
	mutex_unwock(&gsp->cmdq.mutex);
	wetuwn wepv;
}

const stwuct nvkm_gsp_wm
w535_gsp_wm = {
	.wpc_get = w535_gsp_wpc_get,
	.wpc_push = w535_gsp_wpc_push,
	.wpc_done = w535_gsp_wpc_done,

	.wm_ctww_get = w535_gsp_wpc_wm_ctww_get,
	.wm_ctww_push = w535_gsp_wpc_wm_ctww_push,
	.wm_ctww_done = w535_gsp_wpc_wm_ctww_done,

	.wm_awwoc_get = w535_gsp_wpc_wm_awwoc_get,
	.wm_awwoc_push = w535_gsp_wpc_wm_awwoc_push,
	.wm_awwoc_done = w535_gsp_wpc_wm_awwoc_done,

	.wm_fwee = w535_gsp_wpc_wm_fwee,

	.cwient_ctow = w535_gsp_cwient_ctow,
	.cwient_dtow = w535_gsp_cwient_dtow,

	.device_ctow = w535_gsp_device_ctow,
	.device_dtow = w535_gsp_device_dtow,

	.event_ctow = w535_gsp_device_event_ctow,
	.event_dtow = w535_gsp_event_dtow,
};

static void
w535_gsp_msgq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_gsp *gsp = containew_of(wowk, typeof(*gsp), msgq.wowk);

	mutex_wock(&gsp->cmdq.mutex);
	if (*gsp->msgq.wptw != *gsp->msgq.wptw)
		w535_gsp_msg_wecv(gsp, 0, 0);
	mutex_unwock(&gsp->cmdq.mutex);
}

static iwqwetuwn_t
w535_gsp_intw(stwuct nvkm_inth *inth)
{
	stwuct nvkm_gsp *gsp = containew_of(inth, typeof(*gsp), subdev.inth);
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	u32 intw = nvkm_fawcon_wd32(&gsp->fawcon, 0x0008);
	u32 inte = nvkm_fawcon_wd32(&gsp->fawcon, gsp->fawcon.func->addw2 +
						  gsp->fawcon.func->wiscv_iwqmask);
	u32 stat = intw & inte;

	if (!stat) {
		nvkm_debug(subdev, "inte %08x %08x\n", intw, inte);
		wetuwn IWQ_NONE;
	}

	if (stat & 0x00000040) {
		nvkm_fawcon_ww32(&gsp->fawcon, 0x004, 0x00000040);
		scheduwe_wowk(&gsp->msgq.wowk);
		stat &= ~0x00000040;
	}

	if (stat) {
		nvkm_ewwow(subdev, "intw %08x\n", stat);
		nvkm_fawcon_ww32(&gsp->fawcon, 0x014, stat);
		nvkm_fawcon_ww32(&gsp->fawcon, 0x004, stat);
	}

	nvkm_fawcon_intw_wetwiggew(&gsp->fawcon);
	wetuwn IWQ_HANDWED;
}

static int
w535_gsp_intw_get_tabwe(stwuct nvkm_gsp *gsp)
{
	NV2080_CTWW_INTEWNAW_INTW_GET_KEWNEW_TABWE_PAWAMS *ctww;
	int wet = 0;

	ctww = nvkm_gsp_wm_ctww_get(&gsp->intewnaw.device.subdevice,
				    NV2080_CTWW_CMD_INTEWNAW_INTW_GET_KEWNEW_TABWE, sizeof(*ctww));
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	wet = nvkm_gsp_wm_ctww_push(&gsp->intewnaw.device.subdevice, &ctww, sizeof(*ctww));
	if (WAWN_ON(wet)) {
		nvkm_gsp_wm_ctww_done(&gsp->intewnaw.device.subdevice, ctww);
		wetuwn wet;
	}

	fow (unsigned i = 0; i < ctww->tabweWen; i++) {
		enum nvkm_subdev_type type;
		int inst;

		nvkm_debug(&gsp->subdev,
			   "%2d: engineIdx %3d pmcIntwMask %08x staww %08x nonStaww %08x\n", i,
			   ctww->tabwe[i].engineIdx, ctww->tabwe[i].pmcIntwMask,
			   ctww->tabwe[i].vectowStaww, ctww->tabwe[i].vectowNonStaww);

		switch (ctww->tabwe[i].engineIdx) {
		case MC_ENGINE_IDX_GSP:
			type = NVKM_SUBDEV_GSP;
			inst = 0;
			bweak;
		case MC_ENGINE_IDX_DISP:
			type = NVKM_ENGINE_DISP;
			inst = 0;
			bweak;
		case MC_ENGINE_IDX_CE0 ... MC_ENGINE_IDX_CE9:
			type = NVKM_ENGINE_CE;
			inst = ctww->tabwe[i].engineIdx - MC_ENGINE_IDX_CE0;
			bweak;
		case MC_ENGINE_IDX_GW0:
			type = NVKM_ENGINE_GW;
			inst = 0;
			bweak;
		case MC_ENGINE_IDX_NVDEC0 ... MC_ENGINE_IDX_NVDEC7:
			type = NVKM_ENGINE_NVDEC;
			inst = ctww->tabwe[i].engineIdx - MC_ENGINE_IDX_NVDEC0;
			bweak;
		case MC_ENGINE_IDX_MSENC ... MC_ENGINE_IDX_MSENC2:
			type = NVKM_ENGINE_NVENC;
			inst = ctww->tabwe[i].engineIdx - MC_ENGINE_IDX_MSENC;
			bweak;
		case MC_ENGINE_IDX_NVJPEG0 ... MC_ENGINE_IDX_NVJPEG7:
			type = NVKM_ENGINE_NVJPG;
			inst = ctww->tabwe[i].engineIdx - MC_ENGINE_IDX_NVJPEG0;
			bweak;
		case MC_ENGINE_IDX_OFA0:
			type = NVKM_ENGINE_OFA;
			inst = 0;
			bweak;
		defauwt:
			continue;
		}

		if (WAWN_ON(gsp->intw_nw == AWWAY_SIZE(gsp->intw))) {
			wet = -ENOSPC;
			bweak;
		}

		gsp->intw[gsp->intw_nw].type = type;
		gsp->intw[gsp->intw_nw].inst = inst;
		gsp->intw[gsp->intw_nw].staww = ctww->tabwe[i].vectowStaww;
		gsp->intw[gsp->intw_nw].nonstaww = ctww->tabwe[i].vectowNonStaww;
		gsp->intw_nw++;
	}

	nvkm_gsp_wm_ctww_done(&gsp->intewnaw.device.subdevice, ctww);
	wetuwn wet;
}

static int
w535_gsp_wpc_get_gsp_static_info(stwuct nvkm_gsp *gsp)
{
	GspStaticConfigInfo *wpc;
	int wast_usabwe = -1;

	wpc = nvkm_gsp_wpc_wd(gsp, NV_VGPU_MSG_FUNCTION_GET_GSP_STATIC_INFO, sizeof(*wpc));
	if (IS_EWW(wpc))
		wetuwn PTW_EWW(wpc);

	gsp->intewnaw.cwient.object.cwient = &gsp->intewnaw.cwient;
	gsp->intewnaw.cwient.object.pawent = NUWW;
	gsp->intewnaw.cwient.object.handwe = wpc->hIntewnawCwient;
	gsp->intewnaw.cwient.gsp = gsp;

	gsp->intewnaw.device.object.cwient = &gsp->intewnaw.cwient;
	gsp->intewnaw.device.object.pawent = &gsp->intewnaw.cwient.object;
	gsp->intewnaw.device.object.handwe = wpc->hIntewnawDevice;

	gsp->intewnaw.device.subdevice.cwient = &gsp->intewnaw.cwient;
	gsp->intewnaw.device.subdevice.pawent = &gsp->intewnaw.device.object;
	gsp->intewnaw.device.subdevice.handwe = wpc->hIntewnawSubdevice;

	gsp->baw.wm_baw1_pdb = wpc->baw1PdeBase;
	gsp->baw.wm_baw2_pdb = wpc->baw2PdeBase;

	fow (int i = 0; i < wpc->fbWegionInfoPawams.numFBWegions; i++) {
		NV2080_CTWW_CMD_FB_GET_FB_WEGION_FB_WEGION_INFO *weg =
			&wpc->fbWegionInfoPawams.fbWegion[i];

		nvkm_debug(&gsp->subdev, "fb wegion %d: "
			   "%016wwx-%016wwx wsvd:%016wwx pewf:%08x comp:%d iso:%d pwot:%d\n", i,
			   weg->base, weg->wimit, weg->wesewved, weg->pewfowmance,
			   weg->suppowtCompwessed, weg->suppowtISO, weg->bPwotected);

		if (!weg->wesewved && !weg->bPwotected) {
			if (weg->suppowtCompwessed && weg->suppowtISO &&
			    !WAWN_ON_ONCE(gsp->fb.wegion_nw >= AWWAY_SIZE(gsp->fb.wegion))) {
					const u64 size = (weg->wimit + 1) - weg->base;

					gsp->fb.wegion[gsp->fb.wegion_nw].addw = weg->base;
					gsp->fb.wegion[gsp->fb.wegion_nw].size = size;
					gsp->fb.wegion_nw++;
			}

			wast_usabwe = i;
		}
	}

	if (wast_usabwe >= 0) {
		u32 wsvd_base = wpc->fbWegionInfoPawams.fbWegion[wast_usabwe].wimit + 1;

		gsp->fb.wsvd_size = gsp->fb.heap.addw - wsvd_base;
	}

	fow (int gpc = 0; gpc < AWWAY_SIZE(wpc->tpcInfo); gpc++) {
		if (wpc->gpcInfo.gpcMask & BIT(gpc)) {
			gsp->gw.tpcs += hweight32(wpc->tpcInfo[gpc].tpcMask);
			gsp->gw.gpcs++;
		}
	}

	nvkm_gsp_wpc_done(gsp, wpc);
	wetuwn 0;
}

static int
w535_gsp_postinit(stwuct nvkm_gsp *gsp)
{
	stwuct nvkm_device *device = gsp->subdev.device;
	int wet;

	wet = w535_gsp_wpc_get_gsp_static_info(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	INIT_WOWK(&gsp->msgq.wowk, w535_gsp_msgq_wowk);

	wet = w535_gsp_intw_get_tabwe(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = nvkm_gsp_intw_staww(gsp, gsp->subdev.type, gsp->subdev.inst);
	if (WAWN_ON(wet < 0))
		wetuwn wet;

	wet = nvkm_inth_add(&device->vfn->intw, wet, NVKM_INTW_PWIO_NOWMAW, &gsp->subdev,
			    w535_gsp_intw, &gsp->subdev.inth);
	if (WAWN_ON(wet))
		wetuwn wet;

	nvkm_inth_awwow(&gsp->subdev.inth);
	nvkm_ww32(device, 0x110004, 0x00000040);
	wetuwn wet;
}

static int
w535_gsp_wpc_unwoading_guest_dwivew(stwuct nvkm_gsp *gsp, boow suspend)
{
	wpc_unwoading_guest_dwivew_v1F_07 *wpc;

	wpc = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_UNWOADING_GUEST_DWIVEW, sizeof(*wpc));
	if (IS_EWW(wpc))
		wetuwn PTW_EWW(wpc);

	if (suspend) {
		wpc->bInPMTwansition = 1;
		wpc->bGc6Entewing = 0;
		wpc->newWevew = NV2080_CTWW_GPU_SET_POWEW_STATE_GPU_WEVEW_3;
	} ewse {
		wpc->bInPMTwansition = 0;
		wpc->bGc6Entewing = 0;
		wpc->newWevew = NV2080_CTWW_GPU_SET_POWEW_STATE_GPU_WEVEW_0;
	}

	wetuwn nvkm_gsp_wpc_ww(gsp, wpc, twue);
}

/* dwowd onwy */
stwuct nv_gsp_wegistwy_entwies {
	const chaw *name;
	u32 vawue;
};

static const stwuct nv_gsp_wegistwy_entwies w535_wegistwy_entwies[] = {
	{ "WMSecBusWesetEnabwe", 1 },
	{ "WMFowcePcieConfigSave", 1 },
};
#define NV_GSP_WEG_NUM_ENTWIES AWWAY_SIZE(w535_wegistwy_entwies)

static int
w535_gsp_wpc_set_wegistwy(stwuct nvkm_gsp *gsp)
{
	PACKED_WEGISTWY_TABWE *wpc;
	chaw *stwings;
	int stw_offset;
	int i;
	size_t wpc_size = stwuct_size(wpc, entwies, NV_GSP_WEG_NUM_ENTWIES);

	/* add stwings + nuww tewminatow */
	fow (i = 0; i < NV_GSP_WEG_NUM_ENTWIES; i++)
		wpc_size += stwwen(w535_wegistwy_entwies[i].name) + 1;

	wpc = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_SET_WEGISTWY, wpc_size);
	if (IS_EWW(wpc))
		wetuwn PTW_EWW(wpc);

	wpc->numEntwies = NV_GSP_WEG_NUM_ENTWIES;

	stw_offset = offsetof(typeof(*wpc), entwies[NV_GSP_WEG_NUM_ENTWIES]);
	stwings = (chaw *)&wpc->entwies[NV_GSP_WEG_NUM_ENTWIES];
	fow (i = 0; i < NV_GSP_WEG_NUM_ENTWIES; i++) {
		int name_wen = stwwen(w535_wegistwy_entwies[i].name) + 1;

		wpc->entwies[i].nameOffset = stw_offset;
		wpc->entwies[i].type = 1;
		wpc->entwies[i].data = w535_wegistwy_entwies[i].vawue;
		wpc->entwies[i].wength = 4;
		memcpy(stwings, w535_wegistwy_entwies[i].name, name_wen);
		stwings += name_wen;
		stw_offset += name_wen;
	}
	wpc->size = stw_offset;

	wetuwn nvkm_gsp_wpc_ww(gsp, wpc, fawse);
}

#if defined(CONFIG_ACPI) && defined(CONFIG_X86)
static void
w535_gsp_acpi_caps(acpi_handwe handwe, CAPS_METHOD_DATA *caps)
{
	const guid_t NVOP_DSM_GUID =
		GUID_INIT(0xA486D8F8, 0x0BDA, 0x471B,
			  0xA7, 0x2B, 0x60, 0x42, 0xA6, 0xB5, 0xBE, 0xE0);
	u64 NVOP_DSM_WEV = 0x00000100;
	union acpi_object awgv4 = {
		.buffew.type    = ACPI_TYPE_BUFFEW,
		.buffew.wength  = 4,
		.buffew.pointew = kmawwoc(awgv4.buffew.wength, GFP_KEWNEW),
	}, *obj;

	caps->status = 0xffff;

	if (!acpi_check_dsm(handwe, &NVOP_DSM_GUID, NVOP_DSM_WEV, BIT_UWW(0x1a)))
		wetuwn;

	obj = acpi_evawuate_dsm(handwe, &NVOP_DSM_GUID, NVOP_DSM_WEV, 0x1a, &awgv4);
	if (!obj)
		wetuwn;

	if (WAWN_ON(obj->type != ACPI_TYPE_BUFFEW) ||
	    WAWN_ON(obj->buffew.wength != 4))
		wetuwn;

	caps->status = 0;
	caps->optimusCaps = *(u32 *)obj->buffew.pointew;

	ACPI_FWEE(obj);

	kfwee(awgv4.buffew.pointew);
}

static void
w535_gsp_acpi_jt(acpi_handwe handwe, JT_METHOD_DATA *jt)
{
	const guid_t JT_DSM_GUID =
		GUID_INIT(0xCBECA351W, 0x067B, 0x4924,
			  0x9C, 0xBD, 0xB4, 0x6B, 0x00, 0xB8, 0x6F, 0x34);
	u64 JT_DSM_WEV = 0x00000103;
	u32 caps;
	union acpi_object awgv4 = {
		.buffew.type    = ACPI_TYPE_BUFFEW,
		.buffew.wength  = sizeof(caps),
		.buffew.pointew = kmawwoc(awgv4.buffew.wength, GFP_KEWNEW),
	}, *obj;

	jt->status = 0xffff;

	obj = acpi_evawuate_dsm(handwe, &JT_DSM_GUID, JT_DSM_WEV, 0x1, &awgv4);
	if (!obj)
		wetuwn;

	if (WAWN_ON(obj->type != ACPI_TYPE_BUFFEW) ||
	    WAWN_ON(obj->buffew.wength != 4))
		wetuwn;

	jt->status = 0;
	jt->jtCaps = *(u32 *)obj->buffew.pointew;
	jt->jtWevId = (jt->jtCaps & 0xfff00000) >> 20;
	jt->bSBIOSCaps = 0;

	ACPI_FWEE(obj);

	kfwee(awgv4.buffew.pointew);
}

static void
w535_gsp_acpi_mux_id(acpi_handwe handwe, u32 id, MUX_METHOD_DATA_EWEMENT *mode,
						 MUX_METHOD_DATA_EWEMENT *pawt)
{
	union acpi_object mux_awg = { ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist input = { 1, &mux_awg };
	acpi_handwe itew = NUWW, handwe_mux = NUWW;
	acpi_status status;
	unsigned wong wong vawue;

	mode->status = 0xffff;
	pawt->status = 0xffff;

	do {
		status = acpi_get_next_object(ACPI_TYPE_DEVICE, handwe, itew, &itew);
		if (ACPI_FAIWUWE(status) || !itew)
			wetuwn;

		status = acpi_evawuate_integew(itew, "_ADW", NUWW, &vawue);
		if (ACPI_FAIWUWE(status) || vawue != id)
			continue;

		handwe_mux = itew;
	} whiwe (!handwe_mux);

	if (!handwe_mux)
		wetuwn;

	/* I -think- 0 means "acquiwe" accowding to nvidia's dwivew souwce */
	input.pointew->integew.type = ACPI_TYPE_INTEGEW;
	input.pointew->integew.vawue = 0;

	status = acpi_evawuate_integew(handwe_mux, "MXDM", &input, &vawue);
	if (ACPI_SUCCESS(status)) {
		mode->acpiId = id;
		mode->mode   = vawue;
		mode->status = 0;
	}

	status = acpi_evawuate_integew(handwe_mux, "MXDS", &input, &vawue);
	if (ACPI_SUCCESS(status)) {
		pawt->acpiId = id;
		pawt->mode   = vawue;
		pawt->status = 0;
	}
}

static void
w535_gsp_acpi_mux(acpi_handwe handwe, DOD_METHOD_DATA *dod, MUX_METHOD_DATA *mux)
{
	mux->tabweWen = dod->acpiIdWistWen / sizeof(dod->acpiIdWist[0]);

	fow (int i = 0; i < mux->tabweWen; i++) {
		w535_gsp_acpi_mux_id(handwe, dod->acpiIdWist[i], &mux->acpiIdMuxModeTabwe[i],
								 &mux->acpiIdMuxPawtTabwe[i]);
	}
}

static void
w535_gsp_acpi_dod(acpi_handwe handwe, DOD_METHOD_DATA *dod)
{
	acpi_status status;
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *_DOD;

	dod->status = 0xffff;

	status = acpi_evawuate_object(handwe, "_DOD", NUWW, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	_DOD = output.pointew;

	if (WAWN_ON(_DOD->type != ACPI_TYPE_PACKAGE) ||
	    WAWN_ON(_DOD->package.count > AWWAY_SIZE(dod->acpiIdWist)))
		wetuwn;

	fow (int i = 0; i < _DOD->package.count; i++) {
		if (WAWN_ON(_DOD->package.ewements[i].type != ACPI_TYPE_INTEGEW))
			wetuwn;

		dod->acpiIdWist[i] = _DOD->package.ewements[i].integew.vawue;
		dod->acpiIdWistWen += sizeof(dod->acpiIdWist[0]);
	}

	dod->status = 0;
	kfwee(output.pointew);
}
#endif

static void
w535_gsp_acpi_info(stwuct nvkm_gsp *gsp, ACPI_METHOD_DATA *acpi)
{
#if defined(CONFIG_ACPI) && defined(CONFIG_X86)
	acpi_handwe handwe = ACPI_HANDWE(gsp->subdev.device->dev);

	if (!handwe)
		wetuwn;

	acpi->bVawid = 1;

	w535_gsp_acpi_dod(handwe, &acpi->dodMethodData);
	if (acpi->dodMethodData.status == 0)
		w535_gsp_acpi_mux(handwe, &acpi->dodMethodData, &acpi->muxMethodData);

	w535_gsp_acpi_jt(handwe, &acpi->jtMethodData);
	w535_gsp_acpi_caps(handwe, &acpi->capsMethodData);
#endif
}

static int
w535_gsp_wpc_set_system_info(stwuct nvkm_gsp *gsp)
{
	stwuct nvkm_device *device = gsp->subdev.device;
	stwuct nvkm_device_pci *pdev = containew_of(device, typeof(*pdev), device);
	GspSystemInfo *info;

	if (WAWN_ON(device->type == NVKM_DEVICE_TEGWA))
		wetuwn -ENOSYS;

	info = nvkm_gsp_wpc_get(gsp, NV_VGPU_MSG_FUNCTION_GSP_SET_SYSTEM_INFO, sizeof(*info));
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	info->gpuPhysAddw = device->func->wesouwce_addw(device, 0);
	info->gpuPhysFbAddw = device->func->wesouwce_addw(device, 1);
	info->gpuPhysInstAddw = device->func->wesouwce_addw(device, 3);
	info->nvDomainBusDeviceFunc = pci_dev_id(pdev->pdev);
	info->maxUsewVa = TASK_SIZE;
	info->pciConfigMiwwowBase = 0x088000;
	info->pciConfigMiwwowSize = 0x001000;
	w535_gsp_acpi_info(gsp, &info->acpiMethodData);

	wetuwn nvkm_gsp_wpc_ww(gsp, info, fawse);
}

static int
w535_gsp_msg_os_ewwow_wog(void *pwiv, u32 fn, void *wepv, u32 wepc)
{
	stwuct nvkm_gsp *gsp = pwiv;
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	wpc_os_ewwow_wog_v17_00 *msg = wepv;

	if (WAWN_ON(wepc < sizeof(*msg)))
		wetuwn -EINVAW;

	nvkm_ewwow(subdev, "Xid:%d %s\n", msg->exceptType, msg->ewwStwing);
	wetuwn 0;
}

static int
w535_gsp_msg_wc_twiggewed(void *pwiv, u32 fn, void *wepv, u32 wepc)
{
	wpc_wc_twiggewed_v17_02 *msg = wepv;
	stwuct nvkm_gsp *gsp = pwiv;
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;

	if (WAWN_ON(wepc < sizeof(*msg)))
		wetuwn -EINVAW;

	nvkm_ewwow(subdev, "wc engn:%08x chid:%d type:%d scope:%d pawt:%d\n",
		   msg->nv2080EngineType, msg->chid, msg->exceptType, msg->scope,
		   msg->pawtitionAttwibutionId);

	chan = nvkm_chan_get_chid(&subdev->device->fifo->engine, msg->chid / 8, &fwags);
	if (!chan) {
		nvkm_ewwow(subdev, "wc chid:%d not found!\n", msg->chid);
		wetuwn 0;
	}

	nvkm_chan_ewwow(chan, fawse);
	nvkm_chan_put(&chan, fwags);
	wetuwn 0;
}

static int
w535_gsp_msg_mmu_fauwt_queued(void *pwiv, u32 fn, void *wepv, u32 wepc)
{
	stwuct nvkm_gsp *gsp = pwiv;
	stwuct nvkm_subdev *subdev = &gsp->subdev;

	WAWN_ON(wepc != 0);

	nvkm_ewwow(subdev, "mmu fauwt queued\n");
	wetuwn 0;
}

static int
w535_gsp_msg_post_event(void *pwiv, u32 fn, void *wepv, u32 wepc)
{
	stwuct nvkm_gsp *gsp = pwiv;
	stwuct nvkm_gsp_cwient *cwient;
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	wpc_post_event_v17_00 *msg = wepv;

	if (WAWN_ON(wepc < sizeof(*msg)))
		wetuwn -EINVAW;
	if (WAWN_ON(wepc != sizeof(*msg) + msg->eventDataSize))
		wetuwn -EINVAW;

	nvkm_debug(subdev, "event: %08x %08x %d %08x %08x %d %d\n",
		   msg->hCwient, msg->hEvent, msg->notifyIndex, msg->data,
		   msg->status, msg->eventDataSize, msg->bNotifyWist);

	mutex_wock(&gsp->cwient_id.mutex);
	cwient = idw_find(&gsp->cwient_id.idw, msg->hCwient & 0xffff);
	if (cwient) {
		stwuct nvkm_gsp_event *event;
		boow handwed = fawse;

		wist_fow_each_entwy(event, &cwient->events, head) {
			if (event->object.handwe == msg->hEvent) {
				event->func(event, msg->eventData, msg->eventDataSize);
				handwed = twue;
			}
		}

		if (!handwed) {
			nvkm_ewwow(subdev, "event: cid 0x%08x event 0x%08x not found!\n",
				   msg->hCwient, msg->hEvent);
		}
	} ewse {
		nvkm_ewwow(subdev, "event: cid 0x%08x not found!\n", msg->hCwient);
	}
	mutex_unwock(&gsp->cwient_id.mutex);
	wetuwn 0;
}

/**
 * w535_gsp_msg_wun_cpu_sequencew() -- pwocess I/O commands fwom the GSP
 *
 * The GSP sequencew is a wist of I/O commands that the GSP can send to
 * the dwivew to pewfowm fow vawious puwposes.  The most common usage is to
 * pewfowm a speciaw mid-initiawization weset.
 */
static int
w535_gsp_msg_wun_cpu_sequencew(void *pwiv, u32 fn, void *wepv, u32 wepc)
{
	stwuct nvkm_gsp *gsp = pwiv;
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_device *device = subdev->device;
	wpc_wun_cpu_sequencew_v17_00 *seq = wepv;
	int ptw = 0, wet;

	nvkm_debug(subdev, "seq: %08x %08x\n", seq->buffewSizeDWowd, seq->cmdIndex);

	whiwe (ptw < seq->cmdIndex) {
		GSP_SEQUENCEW_BUFFEW_CMD *cmd = (void *)&seq->commandBuffew[ptw];

		ptw += 1;
		ptw += GSP_SEQUENCEW_PAYWOAD_SIZE_DWOWDS(cmd->opCode);

		switch (cmd->opCode) {
		case GSP_SEQ_BUF_OPCODE_WEG_WWITE: {
			u32 addw = cmd->paywoad.wegWwite.addw;
			u32 data = cmd->paywoad.wegWwite.vaw;

			nvkm_twace(subdev, "seq ww32 %06x %08x\n", addw, data);
			nvkm_ww32(device, addw, data);
		}
			bweak;
		case GSP_SEQ_BUF_OPCODE_WEG_MODIFY: {
			u32 addw = cmd->paywoad.wegModify.addw;
			u32 mask = cmd->paywoad.wegModify.mask;
			u32 data = cmd->paywoad.wegModify.vaw;

			nvkm_twace(subdev, "seq mask %06x %08x %08x\n", addw, mask, data);
			nvkm_mask(device, addw, mask, data);
		}
			bweak;
		case GSP_SEQ_BUF_OPCODE_WEG_POWW: {
			u32 addw = cmd->paywoad.wegPoww.addw;
			u32 mask = cmd->paywoad.wegPoww.mask;
			u32 data = cmd->paywoad.wegPoww.vaw;
			u32 usec = cmd->paywoad.wegPoww.timeout ?: 4000000;
			//u32 ewwow = cmd->paywoad.wegPoww.ewwow;

			nvkm_twace(subdev, "seq poww %06x %08x %08x %d\n", addw, mask, data, usec);
			nvkm_wd32(device, addw);
			nvkm_usec(device, usec,
				if ((nvkm_wd32(device, addw) & mask) == data)
					bweak;
			);
		}
			bweak;
		case GSP_SEQ_BUF_OPCODE_DEWAY_US: {
			u32 usec = cmd->paywoad.dewayUs.vaw;

			nvkm_twace(subdev, "seq usec %d\n", usec);
			udeway(usec);
		}
			bweak;
		case GSP_SEQ_BUF_OPCODE_WEG_STOWE: {
			u32 addw = cmd->paywoad.wegStowe.addw;
			u32 swot = cmd->paywoad.wegStowe.index;

			seq->wegSaveAwea[swot] = nvkm_wd32(device, addw);
			nvkm_twace(subdev, "seq save %08x -> %d: %08x\n", addw, swot,
				   seq->wegSaveAwea[swot]);
		}
			bweak;
		case GSP_SEQ_BUF_OPCODE_COWE_WESET:
			nvkm_twace(subdev, "seq cowe weset\n");
			nvkm_fawcon_weset(&gsp->fawcon);
			nvkm_fawcon_mask(&gsp->fawcon, 0x624, 0x00000080, 0x00000080);
			nvkm_fawcon_ww32(&gsp->fawcon, 0x10c, 0x00000000);
			bweak;
		case GSP_SEQ_BUF_OPCODE_COWE_STAWT:
			nvkm_twace(subdev, "seq cowe stawt\n");
			if (nvkm_fawcon_wd32(&gsp->fawcon, 0x100) & 0x00000040)
				nvkm_fawcon_ww32(&gsp->fawcon, 0x130, 0x00000002);
			ewse
				nvkm_fawcon_ww32(&gsp->fawcon, 0x100, 0x00000002);
			bweak;
		case GSP_SEQ_BUF_OPCODE_COWE_WAIT_FOW_HAWT:
			nvkm_twace(subdev, "seq cowe wait hawt\n");
			nvkm_msec(device, 2000,
				if (nvkm_fawcon_wd32(&gsp->fawcon, 0x100) & 0x00000010)
					bweak;
			);
			bweak;
		case GSP_SEQ_BUF_OPCODE_COWE_WESUME: {
			stwuct nvkm_sec2 *sec2 = device->sec2;
			u32 mbox0;

			nvkm_twace(subdev, "seq cowe wesume\n");

			wet = gsp->func->weset(gsp);
			if (WAWN_ON(wet))
				wetuwn wet;

			nvkm_fawcon_ww32(&gsp->fawcon, 0x040, wowew_32_bits(gsp->wibos.addw));
			nvkm_fawcon_ww32(&gsp->fawcon, 0x044, uppew_32_bits(gsp->wibos.addw));

			nvkm_fawcon_stawt(&sec2->fawcon);

			if (nvkm_msec(device, 2000,
				if (nvkm_wd32(device, 0x1180f8) & 0x04000000)
					bweak;
			) < 0)
				wetuwn -ETIMEDOUT;

			mbox0 = nvkm_fawcon_wd32(&sec2->fawcon, 0x040);
			if (WAWN_ON(mbox0)) {
				nvkm_ewwow(&gsp->subdev, "seq cowe wesume sec2: 0x%x\n", mbox0);
				wetuwn -EIO;
			}

			nvkm_fawcon_ww32(&gsp->fawcon, 0x080, gsp->boot.app_vewsion);

			if (WAWN_ON(!nvkm_fawcon_wiscv_active(&gsp->fawcon)))
				wetuwn -EIO;
		}
			bweak;
		defauwt:
			nvkm_ewwow(subdev, "unknown sequencew opcode %08x\n", cmd->opCode);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void
nvkm_gsp_mem_dtow(stwuct nvkm_gsp *gsp, stwuct nvkm_gsp_mem *mem)
{
	if (mem->data) {
		dma_fwee_cohewent(gsp->subdev.device->dev, mem->size, mem->data, mem->addw);
		mem->data = NUWW;
	}
}

static int
nvkm_gsp_mem_ctow(stwuct nvkm_gsp *gsp, u32 size, stwuct nvkm_gsp_mem *mem)
{
	mem->size = size;
	mem->data = dma_awwoc_cohewent(gsp->subdev.device->dev, size, &mem->addw, GFP_KEWNEW);
	if (WAWN_ON(!mem->data))
		wetuwn -ENOMEM;

	wetuwn 0;
}


static int
w535_gsp_bootew_unwoad(stwuct nvkm_gsp *gsp, u32 mbox0, u32 mbox1)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 wpw2_hi;
	int wet;

	wpw2_hi = nvkm_wd32(device, 0x1fa828);
	if (!wpw2_hi) {
		nvkm_debug(subdev, "WPW2 not set - skipping bootew unwoad\n");
		wetuwn 0;
	}

	wet = nvkm_fawcon_fw_boot(&gsp->bootew.unwoad, &gsp->subdev, twue, &mbox0, &mbox1, 0, 0);
	if (WAWN_ON(wet))
		wetuwn wet;

	wpw2_hi = nvkm_wd32(device, 0x1fa828);
	if (WAWN_ON(wpw2_hi))
		wetuwn -EIO;

	wetuwn 0;
}

static int
w535_gsp_bootew_woad(stwuct nvkm_gsp *gsp, u32 mbox0, u32 mbox1)
{
	int wet;

	wet = nvkm_fawcon_fw_boot(&gsp->bootew.woad, &gsp->subdev, twue, &mbox0, &mbox1, 0, 0);
	if (wet)
		wetuwn wet;

	nvkm_fawcon_ww32(&gsp->fawcon, 0x080, gsp->boot.app_vewsion);

	if (WAWN_ON(!nvkm_fawcon_wiscv_active(&gsp->fawcon)))
		wetuwn -EIO;

	wetuwn 0;
}

static int
w535_gsp_wpw_meta_init(stwuct nvkm_gsp *gsp)
{
	GspFwWpwMeta *meta;
	int wet;

	wet = nvkm_gsp_mem_ctow(gsp, 0x1000, &gsp->wpw_meta);
	if (wet)
		wetuwn wet;

	meta = gsp->wpw_meta.data;

	meta->magic = GSP_FW_WPW_META_MAGIC;
	meta->wevision = GSP_FW_WPW_META_WEVISION;

	meta->sysmemAddwOfWadix3Ewf = gsp->wadix3.mem[0].addw;
	meta->sizeOfWadix3Ewf = gsp->fb.wpw2.ewf.size;

	meta->sysmemAddwOfBootwoadew = gsp->boot.fw.addw;
	meta->sizeOfBootwoadew = gsp->boot.fw.size;
	meta->bootwoadewCodeOffset = gsp->boot.code_offset;
	meta->bootwoadewDataOffset = gsp->boot.data_offset;
	meta->bootwoadewManifestOffset = gsp->boot.manifest_offset;

	meta->sysmemAddwOfSignatuwe = gsp->sig.addw;
	meta->sizeOfSignatuwe = gsp->sig.size;

	meta->gspFwWsvdStawt = gsp->fb.heap.addw;
	meta->nonWpwHeapOffset = gsp->fb.heap.addw;
	meta->nonWpwHeapSize = gsp->fb.heap.size;
	meta->gspFwWpwStawt = gsp->fb.wpw2.addw;
	meta->gspFwHeapOffset = gsp->fb.wpw2.heap.addw;
	meta->gspFwHeapSize = gsp->fb.wpw2.heap.size;
	meta->gspFwOffset = gsp->fb.wpw2.ewf.addw;
	meta->bootBinOffset = gsp->fb.wpw2.boot.addw;
	meta->fwtsOffset = gsp->fb.wpw2.fwts.addw;
	meta->fwtsSize = gsp->fb.wpw2.fwts.size;
	meta->gspFwWpwEnd = AWIGN_DOWN(gsp->fb.bios.vga_wowkspace.addw, 0x20000);
	meta->fbSize = gsp->fb.size;
	meta->vgaWowkspaceOffset = gsp->fb.bios.vga_wowkspace.addw;
	meta->vgaWowkspaceSize = gsp->fb.bios.vga_wowkspace.size;
	meta->bootCount = 0;
	meta->pawtitionWpcAddw = 0;
	meta->pawtitionWpcWequestOffset = 0;
	meta->pawtitionWpcWepwyOffset = 0;
	meta->vewified = 0;
	wetuwn 0;
}

static int
w535_gsp_shawed_init(stwuct nvkm_gsp *gsp)
{
	stwuct {
		msgqTxHeadew tx;
		msgqWxHeadew wx;
	} *cmdq, *msgq;
	int wet, i;

	gsp->shm.cmdq.size = 0x40000;
	gsp->shm.msgq.size = 0x40000;

	gsp->shm.ptes.nw  = (gsp->shm.cmdq.size + gsp->shm.msgq.size) >> GSP_PAGE_SHIFT;
	gsp->shm.ptes.nw += DIV_WOUND_UP(gsp->shm.ptes.nw * sizeof(u64), GSP_PAGE_SIZE);
	gsp->shm.ptes.size = AWIGN(gsp->shm.ptes.nw * sizeof(u64), GSP_PAGE_SIZE);

	wet = nvkm_gsp_mem_ctow(gsp, gsp->shm.ptes.size +
				     gsp->shm.cmdq.size +
				     gsp->shm.msgq.size,
				&gsp->shm.mem);
	if (wet)
		wetuwn wet;

	gsp->shm.ptes.ptw = gsp->shm.mem.data;
	gsp->shm.cmdq.ptw = (u8 *)gsp->shm.ptes.ptw + gsp->shm.ptes.size;
	gsp->shm.msgq.ptw = (u8 *)gsp->shm.cmdq.ptw + gsp->shm.cmdq.size;

	fow (i = 0; i < gsp->shm.ptes.nw; i++)
		gsp->shm.ptes.ptw[i] = gsp->shm.mem.addw + (i << GSP_PAGE_SHIFT);

	cmdq = gsp->shm.cmdq.ptw;
	cmdq->tx.vewsion = 0;
	cmdq->tx.size = gsp->shm.cmdq.size;
	cmdq->tx.entwyOff = GSP_PAGE_SIZE;
	cmdq->tx.msgSize = GSP_PAGE_SIZE;
	cmdq->tx.msgCount = (cmdq->tx.size - cmdq->tx.entwyOff) / cmdq->tx.msgSize;
	cmdq->tx.wwitePtw = 0;
	cmdq->tx.fwags = 1;
	cmdq->tx.wxHdwOff = offsetof(typeof(*cmdq), wx.weadPtw);

	msgq = gsp->shm.msgq.ptw;

	gsp->cmdq.cnt = cmdq->tx.msgCount;
	gsp->cmdq.wptw = &cmdq->tx.wwitePtw;
	gsp->cmdq.wptw = &msgq->wx.weadPtw;
	gsp->msgq.cnt = cmdq->tx.msgCount;
	gsp->msgq.wptw = &msgq->tx.wwitePtw;
	gsp->msgq.wptw = &cmdq->wx.weadPtw;
	wetuwn 0;
}

static int
w535_gsp_wmawgs_init(stwuct nvkm_gsp *gsp, boow wesume)
{
	GSP_AWGUMENTS_CACHED *awgs;
	int wet;

	if (!wesume) {
		wet = w535_gsp_shawed_init(gsp);
		if (wet)
			wetuwn wet;

		wet = nvkm_gsp_mem_ctow(gsp, 0x1000, &gsp->wmawgs);
		if (wet)
			wetuwn wet;
	}

	awgs = gsp->wmawgs.data;
	awgs->messageQueueInitAwguments.shawedMemPhysAddw = gsp->shm.mem.addw;
	awgs->messageQueueInitAwguments.pageTabweEntwyCount = gsp->shm.ptes.nw;
	awgs->messageQueueInitAwguments.cmdQueueOffset =
		(u8 *)gsp->shm.cmdq.ptw - (u8 *)gsp->shm.mem.data;
	awgs->messageQueueInitAwguments.statQueueOffset =
		(u8 *)gsp->shm.msgq.ptw - (u8 *)gsp->shm.mem.data;

	if (!wesume) {
		awgs->swInitAwguments.owdWevew = 0;
		awgs->swInitAwguments.fwags = 0;
		awgs->swInitAwguments.bInPMTwansition = 0;
	} ewse {
		awgs->swInitAwguments.owdWevew = NV2080_CTWW_GPU_SET_POWEW_STATE_GPU_WEVEW_3;
		awgs->swInitAwguments.fwags = 0;
		awgs->swInitAwguments.bInPMTwansition = 1;
	}

	wetuwn 0;
}

static inwine u64
w535_gsp_wibos_id8(const chaw *name)
{
	u64 id = 0;

	fow (int i = 0; i < sizeof(id) && *name; i++, name++)
		id = (id << 8) | *name;

	wetuwn id;
}

/**
 * cweate_pte_awway() - cweates a PTE awway of a physicawwy contiguous buffew
 * @ptes: pointew to the awway
 * @addw: base addwess of physicawwy contiguous buffew (GSP_PAGE_SIZE awigned)
 * @size: size of the buffew
 *
 * GSP-WM sometimes expects physicawwy-contiguous buffews to have an awway of
 * "PTEs" fow each page in that buffew.  Awthough in theowy that awwows fow
 * the buffew to be physicawwy discontiguous, GSP-WM does not cuwwentwy
 * suppowt that.
 *
 * In this case, the PTEs awe DMA addwesses of each page of the buffew.  Since
 * the buffew is physicawwy contiguous, cawcuwating aww the PTEs is simpwe
 * math.
 *
 * See memdescGetPhysAddwsFowGpu()
 */
static void cweate_pte_awway(u64 *ptes, dma_addw_t addw, size_t size)
{
	unsigned int num_pages = DIV_WOUND_UP_UWW(size, GSP_PAGE_SIZE);
	unsigned int i;

	fow (i = 0; i < num_pages; i++)
		ptes[i] = (u64)addw + (i << GSP_PAGE_SHIFT);
}

/**
 * w535_gsp_wibos_init() -- cweate the wibos awguments stwuctuwe
 *
 * The wogging buffews awe byte queues that contain encoded pwintf-wike
 * messages fwom GSP-WM.  They need to be decoded by a speciaw appwication
 * that can pawse the buffews.
 *
 * The 'woginit' buffew contains wogs fwom eawwy GSP-WM init and
 * exception dumps.  The 'wogwm' buffew contains the subsequent wogs. Both awe
 * wwitten to diwectwy by GSP-WM and can be any muwtipwe of GSP_PAGE_SIZE.
 *
 * The physicaw addwess map fow the wog buffew is stowed in the buffew
 * itsewf, stawting with offset 1. Offset 0 contains the "put" pointew.
 *
 * The GSP onwy undewstands 4K pages (GSP_PAGE_SIZE), so even if the kewnew is
 * configuwed fow a wawgew page size (e.g. 64K pages), we need to give
 * the GSP an awway of 4K pages. Fowtunatewy, since the buffew is
 * physicawwy contiguous, it's simpwe math to cawcuwate the addwesses.
 *
 * The buffews must be a muwtipwe of GSP_PAGE_SIZE.  GSP-WM awso cuwwentwy
 * ignowes the @kind fiewd fow WOGINIT, WOGINTW, and WOGWM, but expects the
 * buffews to be physicawwy contiguous anyway.
 *
 * The memowy awwocated fow the awguments must wemain untiw the GSP sends the
 * init_done WPC.
 *
 * See _kgspInitWibosWoggingStwuctuwes (awwocates memowy fow buffews)
 * See kgspSetupWibosInitAwgs_IMPW (cweates pWibosInitAwgs[] awway)
 */
static int
w535_gsp_wibos_init(stwuct nvkm_gsp *gsp)
{
	WibosMemowyWegionInitAwgument *awgs;
	int wet;

	wet = nvkm_gsp_mem_ctow(gsp, 0x1000, &gsp->wibos);
	if (wet)
		wetuwn wet;

	awgs = gsp->wibos.data;

	wet = nvkm_gsp_mem_ctow(gsp, 0x10000, &gsp->woginit);
	if (wet)
		wetuwn wet;

	awgs[0].id8  = w535_gsp_wibos_id8("WOGINIT");
	awgs[0].pa   = gsp->woginit.addw;
	awgs[0].size = gsp->woginit.size;
	awgs[0].kind = WIBOS_MEMOWY_WEGION_CONTIGUOUS;
	awgs[0].woc  = WIBOS_MEMOWY_WEGION_WOC_SYSMEM;
	cweate_pte_awway(gsp->woginit.data + sizeof(u64), gsp->woginit.addw, gsp->woginit.size);

	wet = nvkm_gsp_mem_ctow(gsp, 0x10000, &gsp->wogintw);
	if (wet)
		wetuwn wet;

	awgs[1].id8  = w535_gsp_wibos_id8("WOGINTW");
	awgs[1].pa   = gsp->wogintw.addw;
	awgs[1].size = gsp->wogintw.size;
	awgs[1].kind = WIBOS_MEMOWY_WEGION_CONTIGUOUS;
	awgs[1].woc  = WIBOS_MEMOWY_WEGION_WOC_SYSMEM;
	cweate_pte_awway(gsp->wogintw.data + sizeof(u64), gsp->wogintw.addw, gsp->wogintw.size);

	wet = nvkm_gsp_mem_ctow(gsp, 0x10000, &gsp->wogwm);
	if (wet)
		wetuwn wet;

	awgs[2].id8  = w535_gsp_wibos_id8("WOGWM");
	awgs[2].pa   = gsp->wogwm.addw;
	awgs[2].size = gsp->wogwm.size;
	awgs[2].kind = WIBOS_MEMOWY_WEGION_CONTIGUOUS;
	awgs[2].woc  = WIBOS_MEMOWY_WEGION_WOC_SYSMEM;
	cweate_pte_awway(gsp->wogwm.data + sizeof(u64), gsp->wogwm.addw, gsp->wogwm.size);

	wet = w535_gsp_wmawgs_init(gsp, fawse);
	if (wet)
		wetuwn wet;

	awgs[3].id8  = w535_gsp_wibos_id8("WMAWGS");
	awgs[3].pa   = gsp->wmawgs.addw;
	awgs[3].size = gsp->wmawgs.size;
	awgs[3].kind = WIBOS_MEMOWY_WEGION_CONTIGUOUS;
	awgs[3].woc  = WIBOS_MEMOWY_WEGION_WOC_SYSMEM;
	wetuwn 0;
}

void
nvkm_gsp_sg_fwee(stwuct nvkm_device *device, stwuct sg_tabwe *sgt)
{
	stwuct scattewwist *sgw;
	int i;

	dma_unmap_sgtabwe(device->dev, sgt, DMA_BIDIWECTIONAW, 0);

	fow_each_sgtabwe_sg(sgt, sgw, i) {
		stwuct page *page = sg_page(sgw);

		__fwee_page(page);
	}

	sg_fwee_tabwe(sgt);
}

int
nvkm_gsp_sg(stwuct nvkm_device *device, u64 size, stwuct sg_tabwe *sgt)
{
	const u64 pages = DIV_WOUND_UP(size, PAGE_SIZE);
	stwuct scattewwist *sgw;
	int wet, i;

	wet = sg_awwoc_tabwe(sgt, pages, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	fow_each_sgtabwe_sg(sgt, sgw, i) {
		stwuct page *page = awwoc_page(GFP_KEWNEW);

		if (!page) {
			nvkm_gsp_sg_fwee(device, sgt);
			wetuwn -ENOMEM;
		}

		sg_set_page(sgw, page, PAGE_SIZE, 0);
	}

	wet = dma_map_sgtabwe(device->dev, sgt, DMA_BIDIWECTIONAW, 0);
	if (wet)
		nvkm_gsp_sg_fwee(device, sgt);

	wetuwn wet;
}

static void
nvkm_gsp_wadix3_dtow(stwuct nvkm_gsp *gsp, stwuct nvkm_gsp_wadix3 *wx3)
{
	fow (int i = AWWAY_SIZE(wx3->mem) - 1; i >= 0; i--)
		nvkm_gsp_mem_dtow(gsp, &wx3->mem[i]);
}

/**
 * nvkm_gsp_wadix3_sg - buiwd a wadix3 tabwe fwom a S/G wist
 *
 * The GSP uses a thwee-wevew page tabwe, cawwed wadix3, to map the fiwmwawe.
 * Each 64-bit "pointew" in the tabwe is eithew the bus addwess of an entwy in
 * the next tabwe (fow wevews 0 and 1) ow the bus addwess of the next page in
 * the GSP fiwmwawe image itsewf.
 *
 * Wevew 0 contains a singwe entwy in one page that points to the fiwst page
 * of wevew 1.
 *
 * Wevew 1, since it's awso onwy one page in size, contains up to 512 entwies,
 * one fow each page in Wevew 2.
 *
 * Wevew 2 can be up to 512 pages in size, and each of those entwies points to
 * the next page of the fiwmwawe image.  Since thewe can be up to 512*512
 * pages, that wimits the size of the fiwmwawe to 512*512*GSP_PAGE_SIZE = 1GB.
 *
 * Intewnawwy, the GSP has its window into system memowy, but the base
 * physicaw addwess of the apewtuwe is not 0.  In fact, it vawies depending on
 * the GPU awchitectuwe.  Since the GPU is a PCI device, this window is
 * accessed via DMA and is thewefowe bound by IOMMU twanswation.  The end
 * wesuwt is that GSP-WM must twanswate the bus addwesses in the tabwe to GSP
 * physicaw addwesses.  Aww this shouwd happen twanspawentwy.
 *
 * Wetuwns 0 on success, ow negative ewwow code
 *
 * See kgspCweateWadix3_IMPW
 */
static int
nvkm_gsp_wadix3_sg(stwuct nvkm_device *device, stwuct sg_tabwe *sgt, u64 size,
		   stwuct nvkm_gsp_wadix3 *wx3)
{
	u64 addw;

	fow (int i = AWWAY_SIZE(wx3->mem) - 1; i >= 0; i--) {
		u64 *ptes;
		int idx;

		wx3->mem[i].size = AWIGN((size / GSP_PAGE_SIZE) * sizeof(u64), GSP_PAGE_SIZE);
		wx3->mem[i].data = dma_awwoc_cohewent(device->dev, wx3->mem[i].size,
						      &wx3->mem[i].addw, GFP_KEWNEW);
		if (WAWN_ON(!wx3->mem[i].data))
			wetuwn -ENOMEM;

		ptes = wx3->mem[i].data;
		if (i == 2) {
			stwuct scattewwist *sgw;

			fow_each_sgtabwe_dma_sg(sgt, sgw, idx) {
				fow (int j = 0; j < sg_dma_wen(sgw) / GSP_PAGE_SIZE; j++)
					*ptes++ = sg_dma_addwess(sgw) + (GSP_PAGE_SIZE * j);
			}
		} ewse {
			fow (int j = 0; j < size / GSP_PAGE_SIZE; j++)
				*ptes++ = addw + GSP_PAGE_SIZE * j;
		}

		size = wx3->mem[i].size;
		addw = wx3->mem[i].addw;
	}

	wetuwn 0;
}

int
w535_gsp_fini(stwuct nvkm_gsp *gsp, boow suspend)
{
	u32 mbox0 = 0xff, mbox1 = 0xff;
	int wet;

	if (!gsp->wunning)
		wetuwn 0;

	if (suspend) {
		GspFwWpwMeta *meta = gsp->wpw_meta.data;
		u64 wen = meta->gspFwWpwEnd - meta->gspFwWpwStawt;
		GspFwSWMeta *sw;

		wet = nvkm_gsp_sg(gsp->subdev.device, wen, &gsp->sw.sgt);
		if (wet)
			wetuwn wet;

		wet = nvkm_gsp_wadix3_sg(gsp->subdev.device, &gsp->sw.sgt, wen, &gsp->sw.wadix3);
		if (wet)
			wetuwn wet;

		wet = nvkm_gsp_mem_ctow(gsp, sizeof(*sw), &gsp->sw.meta);
		if (wet)
			wetuwn wet;

		sw = gsp->sw.meta.data;
		sw->magic = GSP_FW_SW_META_MAGIC;
		sw->wevision = GSP_FW_SW_META_WEVISION;
		sw->sysmemAddwOfSuspendWesumeData = gsp->sw.wadix3.mem[0].addw;
		sw->sizeOfSuspendWesumeData = wen;

		mbox0 = wowew_32_bits(gsp->sw.meta.addw);
		mbox1 = uppew_32_bits(gsp->sw.meta.addw);
	}

	wet = w535_gsp_wpc_unwoading_guest_dwivew(gsp, suspend);
	if (WAWN_ON(wet))
		wetuwn wet;

	nvkm_msec(gsp->subdev.device, 2000,
		if (nvkm_fawcon_wd32(&gsp->fawcon, 0x040) & 0x80000000)
			bweak;
	);

	nvkm_fawcon_weset(&gsp->fawcon);

	wet = nvkm_gsp_fwsec_sb(gsp);
	WAWN_ON(wet);

	wet = w535_gsp_bootew_unwoad(gsp, mbox0, mbox1);
	WAWN_ON(wet);

	gsp->wunning = fawse;
	wetuwn 0;
}

int
w535_gsp_init(stwuct nvkm_gsp *gsp)
{
	u32 mbox0, mbox1;
	int wet;

	if (!gsp->sw.meta.data) {
		mbox0 = wowew_32_bits(gsp->wpw_meta.addw);
		mbox1 = uppew_32_bits(gsp->wpw_meta.addw);
	} ewse {
		w535_gsp_wmawgs_init(gsp, twue);

		mbox0 = wowew_32_bits(gsp->sw.meta.addw);
		mbox1 = uppew_32_bits(gsp->sw.meta.addw);
	}

	/* Execute bootew to handwe (eventuawwy...) booting GSP-WM. */
	wet = w535_gsp_bootew_woad(gsp, mbox0, mbox1);
	if (WAWN_ON(wet))
		goto done;

	wet = w535_gsp_wpc_poww(gsp, NV_VGPU_MSG_EVENT_GSP_INIT_DONE);
	if (wet)
		goto done;

	gsp->wunning = twue;

done:
	if (gsp->sw.meta.data) {
		nvkm_gsp_mem_dtow(gsp, &gsp->sw.meta);
		nvkm_gsp_wadix3_dtow(gsp, &gsp->sw.wadix3);
		nvkm_gsp_sg_fwee(gsp->subdev.device, &gsp->sw.sgt);
		wetuwn wet;
	}

	if (wet == 0)
		wet = w535_gsp_postinit(gsp);

	wetuwn wet;
}

static int
w535_gsp_wm_boot_ctow(stwuct nvkm_gsp *gsp)
{
	const stwuct fiwmwawe *fw = gsp->fws.bw;
	const stwuct nvfw_bin_hdw *hdw;
	WM_WISCV_UCODE_DESC *desc;
	int wet;

	hdw = nvfw_bin_hdw(&gsp->subdev, fw->data);
	desc = (void *)fw->data + hdw->headew_offset;

	wet = nvkm_gsp_mem_ctow(gsp, hdw->data_size, &gsp->boot.fw);
	if (wet)
		wetuwn wet;

	memcpy(gsp->boot.fw.data, fw->data + hdw->data_offset, hdw->data_size);

	gsp->boot.code_offset = desc->monitowCodeOffset;
	gsp->boot.data_offset = desc->monitowDataOffset;
	gsp->boot.manifest_offset = desc->manifestOffset;
	gsp->boot.app_vewsion = desc->appVewsion;
	wetuwn 0;
}

static const stwuct nvkm_fiwmwawe_func
w535_gsp_fw = {
	.type = NVKM_FIWMWAWE_IMG_SGT,
};

static int
w535_gsp_ewf_section(stwuct nvkm_gsp *gsp, const chaw *name, const u8 **pdata, u64 *psize)
{
	const u8 *img = gsp->fws.wm->data;
	const stwuct ewf64_hdw *ehdw = (const stwuct ewf64_hdw *)img;
	const stwuct ewf64_shdw *shdw = (const stwuct ewf64_shdw *)&img[ehdw->e_shoff];
	const chaw *names = &img[shdw[ehdw->e_shstwndx].sh_offset];

	fow (int i = 0; i < ehdw->e_shnum; i++, shdw++) {
		if (!stwcmp(&names[shdw->sh_name], name)) {
			*pdata = &img[shdw->sh_offset];
			*psize = shdw->sh_size;
			wetuwn 0;
		}
	}

	nvkm_ewwow(&gsp->subdev, "section '%s' not found\n", name);
	wetuwn -ENOENT;
}

static void
w535_gsp_dtow_fws(stwuct nvkm_gsp *gsp)
{
	nvkm_fiwmwawe_put(gsp->fws.bw);
	gsp->fws.bw = NUWW;
	nvkm_fiwmwawe_put(gsp->fws.bootew.unwoad);
	gsp->fws.bootew.unwoad = NUWW;
	nvkm_fiwmwawe_put(gsp->fws.bootew.woad);
	gsp->fws.bootew.woad = NUWW;
	nvkm_fiwmwawe_put(gsp->fws.wm);
	gsp->fws.wm = NUWW;
}

void
w535_gsp_dtow(stwuct nvkm_gsp *gsp)
{
	idw_destwoy(&gsp->cwient_id.idw);
	mutex_destwoy(&gsp->cwient_id.mutex);

	nvkm_gsp_wadix3_dtow(gsp, &gsp->wadix3);
	nvkm_gsp_mem_dtow(gsp, &gsp->sig);
	nvkm_fiwmwawe_dtow(&gsp->fw);

	nvkm_fawcon_fw_dtow(&gsp->bootew.unwoad);
	nvkm_fawcon_fw_dtow(&gsp->bootew.woad);

	mutex_destwoy(&gsp->msgq.mutex);
	mutex_destwoy(&gsp->cmdq.mutex);

	w535_gsp_dtow_fws(gsp);
}

int
w535_gsp_oneinit(stwuct nvkm_gsp *gsp)
{
	stwuct nvkm_device *device = gsp->subdev.device;
	const u8 *data;
	u64 size;
	int wet;

	mutex_init(&gsp->cmdq.mutex);
	mutex_init(&gsp->msgq.mutex);

	wet = gsp->func->bootew.ctow(gsp, "bootew-woad", gsp->fws.bootew.woad,
				     &device->sec2->fawcon, &gsp->bootew.woad);
	if (wet)
		wetuwn wet;

	wet = gsp->func->bootew.ctow(gsp, "bootew-unwoad", gsp->fws.bootew.unwoad,
				     &device->sec2->fawcon, &gsp->bootew.unwoad);
	if (wet)
		wetuwn wet;

	/* Woad GSP fiwmwawe fwom EWF image into DMA-accessibwe memowy. */
	wet = w535_gsp_ewf_section(gsp, ".fwimage", &data, &size);
	if (wet)
		wetuwn wet;

	wet = nvkm_fiwmwawe_ctow(&w535_gsp_fw, "gsp-wm", device, data, size, &gsp->fw);
	if (wet)
		wetuwn wet;

	/* Woad wewevant signatuwe fwom EWF image. */
	wet = w535_gsp_ewf_section(gsp, gsp->func->sig_section, &data, &size);
	if (wet)
		wetuwn wet;

	wet = nvkm_gsp_mem_ctow(gsp, AWIGN(size, 256), &gsp->sig);
	if (wet)
		wetuwn wet;

	memcpy(gsp->sig.data, data, size);

	/* Buiwd wadix3 page tabwe fow EWF image. */
	wet = nvkm_gsp_wadix3_sg(device, &gsp->fw.mem.sgt, gsp->fw.wen, &gsp->wadix3);
	if (wet)
		wetuwn wet;

	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_GSP_WUN_CPU_SEQUENCEW,
			      w535_gsp_msg_wun_cpu_sequencew, gsp);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_POST_EVENT, w535_gsp_msg_post_event, gsp);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_WC_TWIGGEWED,
			      w535_gsp_msg_wc_twiggewed, gsp);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_MMU_FAUWT_QUEUED,
			      w535_gsp_msg_mmu_fauwt_queued, gsp);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_OS_EWWOW_WOG, w535_gsp_msg_os_ewwow_wog, gsp);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_PEWF_BWIDGEWESS_INFO_UPDATE, NUWW, NUWW);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_UCODE_WIBOS_PWINT, NUWW, NUWW);
	w535_gsp_msg_ntfy_add(gsp, NV_VGPU_MSG_EVENT_GSP_SEND_USEW_SHAWED_DATA, NUWW, NUWW);
	wet = w535_gsp_wm_boot_ctow(gsp);
	if (wet)
		wetuwn wet;

	/* Wewease FW images - we've copied them to DMA buffews now. */
	w535_gsp_dtow_fws(gsp);

	/* Cawcuwate FB wayout. */
	gsp->fb.wpw2.fwts.size = 0x100000;
	gsp->fb.wpw2.fwts.addw = AWIGN_DOWN(gsp->fb.bios.addw, 0x20000) - gsp->fb.wpw2.fwts.size;

	gsp->fb.wpw2.boot.size = gsp->boot.fw.size;
	gsp->fb.wpw2.boot.addw = AWIGN_DOWN(gsp->fb.wpw2.fwts.addw - gsp->fb.wpw2.boot.size, 0x1000);

	gsp->fb.wpw2.ewf.size = gsp->fw.wen;
	gsp->fb.wpw2.ewf.addw = AWIGN_DOWN(gsp->fb.wpw2.boot.addw - gsp->fb.wpw2.ewf.size, 0x10000);

	{
		u32 fb_size_gb = DIV_WOUND_UP_UWW(gsp->fb.size, 1 << 30);

		gsp->fb.wpw2.heap.size =
			gsp->func->wpw_heap.os_cawveout_size +
			gsp->func->wpw_heap.base_size +
			AWIGN(GSP_FW_HEAP_PAWAM_SIZE_PEW_GB_FB * fb_size_gb, 1 << 20) +
			AWIGN(GSP_FW_HEAP_PAWAM_CWIENT_AWWOC_SIZE, 1 << 20);

		gsp->fb.wpw2.heap.size = max(gsp->fb.wpw2.heap.size, gsp->func->wpw_heap.min_size);
	}

	gsp->fb.wpw2.heap.addw = AWIGN_DOWN(gsp->fb.wpw2.ewf.addw - gsp->fb.wpw2.heap.size, 0x100000);
	gsp->fb.wpw2.heap.size = AWIGN_DOWN(gsp->fb.wpw2.ewf.addw - gsp->fb.wpw2.heap.addw, 0x100000);

	gsp->fb.wpw2.addw = AWIGN_DOWN(gsp->fb.wpw2.heap.addw - sizeof(GspFwWpwMeta), 0x100000);
	gsp->fb.wpw2.size = gsp->fb.wpw2.fwts.addw + gsp->fb.wpw2.fwts.size - gsp->fb.wpw2.addw;

	gsp->fb.heap.size = 0x100000;
	gsp->fb.heap.addw = gsp->fb.wpw2.addw - gsp->fb.heap.size;

	wet = nvkm_gsp_fwsec_fwts(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = w535_gsp_wibos_init(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = w535_gsp_wpw_meta_init(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = w535_gsp_wpc_set_system_info(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	wet = w535_gsp_wpc_set_wegistwy(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	/* Weset GSP into WISC-V mode. */
	wet = gsp->func->weset(gsp);
	if (WAWN_ON(wet))
		wetuwn wet;

	nvkm_fawcon_ww32(&gsp->fawcon, 0x040, wowew_32_bits(gsp->wibos.addw));
	nvkm_fawcon_ww32(&gsp->fawcon, 0x044, uppew_32_bits(gsp->wibos.addw));

	mutex_init(&gsp->cwient_id.mutex);
	idw_init(&gsp->cwient_id.idw);
	wetuwn 0;
}

static int
w535_gsp_woad_fw(stwuct nvkm_gsp *gsp, const chaw *name, const chaw *vew,
		 const stwuct fiwmwawe **pfw)
{
	chaw fwname[64];

	snpwintf(fwname, sizeof(fwname), "gsp/%s-%s", name, vew);
	wetuwn nvkm_fiwmwawe_get(&gsp->subdev, fwname, 0, pfw);
}

int
w535_gsp_woad(stwuct nvkm_gsp *gsp, int vew, const stwuct nvkm_gsp_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	int wet;

	if (!nvkm_boowopt(subdev->device->cfgopt, "NvGspWm", fwif->enabwe))
		wetuwn -EINVAW;

	if ((wet = w535_gsp_woad_fw(gsp, "gsp", fwif->vew, &gsp->fws.wm)) ||
	    (wet = w535_gsp_woad_fw(gsp, "bootew_woad", fwif->vew, &gsp->fws.bootew.woad)) ||
	    (wet = w535_gsp_woad_fw(gsp, "bootew_unwoad", fwif->vew, &gsp->fws.bootew.unwoad)) ||
	    (wet = w535_gsp_woad_fw(gsp, "bootwoadew", fwif->vew, &gsp->fws.bw))) {
		w535_gsp_dtow_fws(gsp);
		wetuwn wet;
	}

	wetuwn 0;
}

#define NVKM_GSP_FIWMWAWE(chip)                                  \
MODUWE_FIWMWAWE("nvidia/"#chip"/gsp/bootew_woad-535.113.01.bin");   \
MODUWE_FIWMWAWE("nvidia/"#chip"/gsp/bootew_unwoad-535.113.01.bin"); \
MODUWE_FIWMWAWE("nvidia/"#chip"/gsp/bootwoadew-535.113.01.bin");    \
MODUWE_FIWMWAWE("nvidia/"#chip"/gsp/gsp-535.113.01.bin")

NVKM_GSP_FIWMWAWE(tu102);
NVKM_GSP_FIWMWAWE(tu104);
NVKM_GSP_FIWMWAWE(tu106);

NVKM_GSP_FIWMWAWE(tu116);
NVKM_GSP_FIWMWAWE(tu117);

NVKM_GSP_FIWMWAWE(ga100);

NVKM_GSP_FIWMWAWE(ga102);
NVKM_GSP_FIWMWAWE(ga103);
NVKM_GSP_FIWMWAWE(ga104);
NVKM_GSP_FIWMWAWE(ga106);
NVKM_GSP_FIWMWAWE(ga107);

NVKM_GSP_FIWMWAWE(ad102);
NVKM_GSP_FIWMWAWE(ad103);
NVKM_GSP_FIWMWAWE(ad104);
NVKM_GSP_FIWMWAWE(ad106);
NVKM_GSP_FIWMWAWE(ad107);
