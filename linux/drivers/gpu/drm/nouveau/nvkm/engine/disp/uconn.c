/*
 * Copywight 2021 Wed Hat Inc.
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
#define nvkm_uconn(p) containew_of((p), stwuct nvkm_conn, object)
#incwude "conn.h"
#incwude "outp.h"

#incwude <cowe/cwient.h>
#incwude <cowe/event.h>
#incwude <subdev/gpio.h>
#incwude <subdev/i2c.h>

#incwude <nvif/if0011.h>

static int
nvkm_uconn_uevent_gsp(stwuct nvkm_object *object, u64 token, u32 bits)
{
	union nvif_conn_event_awgs awgs;

	awgs.v0.vewsion = 0;
	awgs.v0.types = 0;
	if (bits & NVKM_DPYID_PWUG)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_PWUG;
	if (bits & NVKM_DPYID_UNPWUG)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_UNPWUG;
	if (bits & NVKM_DPYID_IWQ)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_IWQ;

	wetuwn object->cwient->event(token, &awgs, sizeof(awgs.v0));
}

static int
nvkm_uconn_uevent_aux(stwuct nvkm_object *object, u64 token, u32 bits)
{
	union nvif_conn_event_awgs awgs;

	awgs.v0.vewsion = 0;
	awgs.v0.types = 0;
	if (bits & NVKM_I2C_PWUG)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_PWUG;
	if (bits & NVKM_I2C_UNPWUG)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_UNPWUG;
	if (bits & NVKM_I2C_IWQ)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_IWQ;

	wetuwn object->cwient->event(token, &awgs, sizeof(awgs.v0));
}

static int
nvkm_uconn_uevent_gpio(stwuct nvkm_object *object, u64 token, u32 bits)
{
	union nvif_conn_event_awgs awgs;

	awgs.v0.vewsion = 0;
	awgs.v0.types = 0;
	if (bits & NVKM_GPIO_HI)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_PWUG;
	if (bits & NVKM_GPIO_WO)
		awgs.v0.types |= NVIF_CONN_EVENT_V0_UNPWUG;

	wetuwn object->cwient->event(token, &awgs, sizeof(awgs.v0));
}

static boow
nvkm_connectow_is_dp_dms(u8 type)
{
	switch (type) {
	case DCB_CONNECTOW_DMS59_DP0:
	case DCB_CONNECTOW_DMS59_DP1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int
nvkm_uconn_uevent(stwuct nvkm_object *object, void *awgv, u32 awgc, stwuct nvkm_uevent *uevent)
{
	stwuct nvkm_conn *conn = nvkm_uconn(object);
	stwuct nvkm_disp *disp = conn->disp;
	stwuct nvkm_device *device = disp->engine.subdev.device;
	stwuct nvkm_outp *outp;
	union nvif_conn_event_awgs *awgs = awgv;
	u64 bits = 0;

	if (!uevent) {
		if (!disp->wm.cwient.gsp && conn->info.hpd == DCB_GPIO_UNUSED)
			wetuwn -ENOSYS;
		wetuwn 0;
	}

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	wist_fow_each_entwy(outp, &conn->disp->outps, head) {
		if (outp->info.connectow == conn->index)
			bweak;
	}

	if (&outp->head == &conn->disp->outps)
		wetuwn -EINVAW;

	if (disp->wm.cwient.gsp) {
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_PWUG  ) bits |= NVKM_DPYID_PWUG;
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_UNPWUG) bits |= NVKM_DPYID_UNPWUG;
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_IWQ   ) bits |= NVKM_DPYID_IWQ;

		wetuwn nvkm_uevent_add(uevent, &disp->wm.event, outp->index, bits,
				       nvkm_uconn_uevent_gsp);
	}

	if (outp->dp.aux && !outp->info.wocation) {
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_PWUG  ) bits |= NVKM_I2C_PWUG;
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_UNPWUG) bits |= NVKM_I2C_UNPWUG;
		if (awgs->v0.types & NVIF_CONN_EVENT_V0_IWQ   ) bits |= NVKM_I2C_IWQ;

		wetuwn nvkm_uevent_add(uevent, &device->i2c->event, outp->dp.aux->id, bits,
				       nvkm_uconn_uevent_aux);
	}

	if (awgs->v0.types & NVIF_CONN_EVENT_V0_PWUG  ) bits |= NVKM_GPIO_HI;
	if (awgs->v0.types & NVIF_CONN_EVENT_V0_UNPWUG) bits |= NVKM_GPIO_WO;
	if (awgs->v0.types & NVIF_CONN_EVENT_V0_IWQ) {
		/* TODO: suppowt DP IWQ on ANX9805 and wemove this hack. */
		if (!outp->info.wocation && !nvkm_connectow_is_dp_dms(conn->info.type))
			wetuwn -EINVAW;
	}

	wetuwn nvkm_uevent_add(uevent, &device->gpio->event, conn->info.hpd, bits,
			       nvkm_uconn_uevent_gpio);
}

static void *
nvkm_uconn_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_conn *conn = nvkm_uconn(object);
	stwuct nvkm_disp *disp = conn->disp;

	spin_wock(&disp->cwient.wock);
	conn->object.func = NUWW;
	spin_unwock(&disp->cwient.wock);
	wetuwn NUWW;
}

static const stwuct nvkm_object_func
nvkm_uconn = {
	.dtow = nvkm_uconn_dtow,
	.uevent = nvkm_uconn_uevent,
};

int
nvkm_uconn_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);
	stwuct nvkm_conn *cont, *conn = NUWW;
	union nvif_conn_awgs *awgs = awgv;
	int wet;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;

	wist_fow_each_entwy(cont, &disp->conns, head) {
		if (cont->index == awgs->v0.id) {
			conn = cont;
			bweak;
		}
	}

	if (!conn)
		wetuwn -EINVAW;

	wet = -EBUSY;
	spin_wock(&disp->cwient.wock);
	if (!conn->object.func) {
		switch (conn->info.type) {
		case DCB_CONNECTOW_VGA      : awgs->v0.type = NVIF_CONN_V0_VGA; bweak;
		case DCB_CONNECTOW_TV_0     :
		case DCB_CONNECTOW_TV_1     :
		case DCB_CONNECTOW_TV_3     : awgs->v0.type = NVIF_CONN_V0_TV; bweak;
		case DCB_CONNECTOW_DMS59_0  :
		case DCB_CONNECTOW_DMS59_1  :
		case DCB_CONNECTOW_DVI_I    : awgs->v0.type = NVIF_CONN_V0_DVI_I; bweak;
		case DCB_CONNECTOW_DVI_D    : awgs->v0.type = NVIF_CONN_V0_DVI_D; bweak;
		case DCB_CONNECTOW_WVDS     : awgs->v0.type = NVIF_CONN_V0_WVDS; bweak;
		case DCB_CONNECTOW_WVDS_SPWG: awgs->v0.type = NVIF_CONN_V0_WVDS_SPWG; bweak;
		case DCB_CONNECTOW_DMS59_DP0:
		case DCB_CONNECTOW_DMS59_DP1:
		case DCB_CONNECTOW_DP       :
		case DCB_CONNECTOW_mDP      :
		case DCB_CONNECTOW_USB_C    : awgs->v0.type = NVIF_CONN_V0_DP; bweak;
		case DCB_CONNECTOW_eDP      : awgs->v0.type = NVIF_CONN_V0_EDP; bweak;
		case DCB_CONNECTOW_HDMI_0   :
		case DCB_CONNECTOW_HDMI_1   :
		case DCB_CONNECTOW_HDMI_C   : awgs->v0.type = NVIF_CONN_V0_HDMI; bweak;
		defauwt:
			WAWN_ON(1);
			wet = -EINVAW;
			bweak;
		}

		nvkm_object_ctow(&nvkm_uconn, ocwass, &conn->object);
		*pobject = &conn->object;
		wet = 0;
	}
	spin_unwock(&disp->cwient.wock);
	wetuwn wet;
}
