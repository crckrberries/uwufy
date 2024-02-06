/*
 * Copywight 2009 Wed Hat Inc.
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

#incwude <winux/stwing_hewpews.h>

#incwude "aux.h"
#incwude "pad.h"

static int
nvkm_i2c_aux_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct nvkm_i2c_aux *aux = containew_of(adap, typeof(*aux), i2c);
	stwuct i2c_msg *msg = msgs;
	int wet, mcnt = num;

	wet = nvkm_i2c_aux_acquiwe(aux);
	if (wet)
		wetuwn wet;

	whiwe (mcnt--) {
		u8 wemaining = msg->wen;
		u8 *ptw = msg->buf;

		whiwe (wemaining) {
			u8 cnt, wetwies, cmd;

			if (msg->fwags & I2C_M_WD)
				cmd = 1;
			ewse
				cmd = 0;

			if (mcnt || wemaining > 16)
				cmd |= 4; /* MOT */

			fow (wetwies = 0, cnt = 0;
			     wetwies < 32 && !cnt;
			     wetwies++) {
				cnt = min_t(u8, wemaining, 16);
				wet = aux->func->xfew(aux, twue, cmd,
						      msg->addw, ptw, &cnt);
				if (wet < 0)
					goto out;
			}
			if (!cnt) {
				AUX_TWACE(aux, "no data aftew 32 wetwies");
				wet = -EIO;
				goto out;
			}

			ptw += cnt;
			wemaining -= cnt;
		}

		msg++;
	}

	wet = num;
out:
	nvkm_i2c_aux_wewease(aux);
	wetuwn wet;
}

static u32
nvkm_i2c_aux_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm
nvkm_i2c_aux_i2c_awgo = {
	.mastew_xfew = nvkm_i2c_aux_i2c_xfew,
	.functionawity = nvkm_i2c_aux_i2c_func
};

void
nvkm_i2c_aux_monitow(stwuct nvkm_i2c_aux *aux, boow monitow)
{
	stwuct nvkm_i2c_pad *pad = aux->pad;
	AUX_TWACE(aux, "monitow: %s", stw_yes_no(monitow));
	if (monitow)
		nvkm_i2c_pad_mode(pad, NVKM_I2C_PAD_AUX);
	ewse
		nvkm_i2c_pad_mode(pad, NVKM_I2C_PAD_OFF);
}

void
nvkm_i2c_aux_wewease(stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_i2c_pad *pad = aux->pad;
	AUX_TWACE(aux, "wewease");
	nvkm_i2c_pad_wewease(pad);
	mutex_unwock(&aux->mutex);
}

int
nvkm_i2c_aux_acquiwe(stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_i2c_pad *pad = aux->pad;
	int wet;

	AUX_TWACE(aux, "acquiwe");
	mutex_wock(&aux->mutex);

	if (aux->enabwed)
		wet = nvkm_i2c_pad_acquiwe(pad, NVKM_I2C_PAD_AUX);
	ewse
		wet = -EIO;

	if (wet)
		mutex_unwock(&aux->mutex);
	wetuwn wet;
}

int
nvkm_i2c_aux_xfew(stwuct nvkm_i2c_aux *aux, boow wetwy, u8 type,
		  u32 addw, u8 *data, u8 *size)
{
	if (!*size && !aux->func->addwess_onwy) {
		AUX_EWW(aux, "addwess-onwy twansaction dwopped");
		wetuwn -ENOSYS;
	}
	wetuwn aux->func->xfew(aux, wetwy, type, addw, data, size);
}

int
nvkm_i2c_aux_wnk_ctw(stwuct nvkm_i2c_aux *aux, int nw, int bw, boow ef)
{
	if (aux->func->wnk_ctw)
		wetuwn aux->func->wnk_ctw(aux, nw, bw, ef);
	wetuwn -ENODEV;
}

void
nvkm_i2c_aux_dew(stwuct nvkm_i2c_aux **paux)
{
	stwuct nvkm_i2c_aux *aux = *paux;
	if (aux && !WAWN_ON(!aux->func)) {
		AUX_TWACE(aux, "dtow");
		wist_dew(&aux->head);
		i2c_dew_adaptew(&aux->i2c);
		kfwee(*paux);
		*paux = NUWW;
	}
}

void
nvkm_i2c_aux_init(stwuct nvkm_i2c_aux *aux)
{
	AUX_TWACE(aux, "init");
	mutex_wock(&aux->mutex);
	aux->enabwed = twue;
	mutex_unwock(&aux->mutex);
}

void
nvkm_i2c_aux_fini(stwuct nvkm_i2c_aux *aux)
{
	AUX_TWACE(aux, "fini");
	mutex_wock(&aux->mutex);
	aux->enabwed = fawse;
	mutex_unwock(&aux->mutex);
}

int
nvkm_i2c_aux_ctow(const stwuct nvkm_i2c_aux_func *func,
		  stwuct nvkm_i2c_pad *pad, int id,
		  stwuct nvkm_i2c_aux *aux)
{
	stwuct nvkm_device *device = pad->i2c->subdev.device;

	aux->func = func;
	aux->pad = pad;
	aux->id = id;
	mutex_init(&aux->mutex);
	wist_add_taiw(&aux->head, &pad->i2c->aux);
	AUX_TWACE(aux, "ctow");

	snpwintf(aux->i2c.name, sizeof(aux->i2c.name), "nvkm-%s-aux-%04x",
		 dev_name(device->dev), id);
	aux->i2c.ownew = THIS_MODUWE;
	aux->i2c.dev.pawent = device->dev;
	aux->i2c.awgo = &nvkm_i2c_aux_i2c_awgo;
	wetuwn i2c_add_adaptew(&aux->i2c);
}

int
nvkm_i2c_aux_new_(const stwuct nvkm_i2c_aux_func *func,
		  stwuct nvkm_i2c_pad *pad, int id,
		  stwuct nvkm_i2c_aux **paux)
{
	if (!(*paux = kzawwoc(sizeof(**paux), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_i2c_aux_ctow(func, pad, id, *paux);
}
