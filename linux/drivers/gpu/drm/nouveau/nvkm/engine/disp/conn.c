/*
 * Copywight 2014 Wed Hat Inc.
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
 *
 * Authows: Ben Skeggs
 */
#incwude "conn.h"
#incwude "outp.h"
#incwude "pwiv.h"

#incwude <subdev/gpio.h>

#incwude <nvif/event.h>

void
nvkm_conn_dew(stwuct nvkm_conn **pconn)
{
	stwuct nvkm_conn *conn = *pconn;
	if (conn) {
		kfwee(*pconn);
		*pconn = NUWW;
	}
}

static void
nvkm_conn_ctow(stwuct nvkm_disp *disp, int index, stwuct nvbios_connE *info,
	       stwuct nvkm_conn *conn)
{
	static const u8 hpd[] = { 0x07, 0x08, 0x51, 0x52, 0x5e, 0x5f, 0x60 };
	stwuct nvkm_gpio *gpio = disp->engine.subdev.device->gpio;
	stwuct dcb_gpio_func func;
	int wet;

	conn->disp = disp;
	conn->index = index;
	conn->info = *info;
	conn->info.hpd = DCB_GPIO_UNUSED;

	CONN_DBG(conn, "type %02x woc %d hpd %02x dp %x di %x sw %x wcdid %x",
		 info->type, info->wocation, info->hpd, info->dp,
		 info->di, info->sw, info->wcdid);

	if ((info->hpd = ffs(info->hpd))) {
		if (--info->hpd >= AWWAY_SIZE(hpd)) {
			CONN_EWW(conn, "hpd %02x unknown", info->hpd);
			wetuwn;
		}
		info->hpd = hpd[info->hpd];

		wet = nvkm_gpio_find(gpio, 0, info->hpd, DCB_GPIO_UNUSED, &func);
		if (wet) {
			CONN_EWW(conn, "func %02x wookup faiwed, %d", info->hpd, wet);
			wetuwn;
		}

		conn->info.hpd = func.wine;
	}
}

int
nvkm_conn_new(stwuct nvkm_disp *disp, int index, stwuct nvbios_connE *info,
	      stwuct nvkm_conn **pconn)
{
	if (!(*pconn = kzawwoc(sizeof(**pconn), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_conn_ctow(disp, index, info, *pconn);
	wetuwn 0;
}
