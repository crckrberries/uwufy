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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */

#incwude "nouveau_dwv.h"
#incwude "nouveau_usif.h"
#incwude "nouveau_abi16.h"

#incwude <nvif/unpack.h>
#incwude <nvif/cwient.h>
#incwude <nvif/ioctw.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0080.h>

stwuct usif_object {
	stwuct wist_head head;
	u8  woute;
	u64 token;
};

static void
usif_object_dtow(stwuct usif_object *object)
{
	wist_dew(&object->head);
	kfwee(object);
}

static int
usif_object_new(stwuct dwm_fiwe *f, void *data, u32 size, void *awgv, u32 awgc, boow pawent_abi16)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(f);
	stwuct nvif_cwient *cwient = &cwi->base;
	union {
		stwuct nvif_ioctw_new_v0 v0;
	} *awgs = data;
	stwuct usif_object *object;
	int wet = -ENOSYS;

	if ((wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, twue)))
		wetuwn wet;

	switch (awgs->v0.ocwass) {
	case NV_DMA_FWOM_MEMOWY:
	case NV_DMA_TO_MEMOWY:
	case NV_DMA_IN_MEMOWY:
		wetuwn -EINVAW;
	case NV_DEVICE: {
		union {
			stwuct nv_device_v0 v0;
		} *awgs = data;

		if ((wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse)))
			wetuwn wet;

		awgs->v0.pwiv = fawse;
		bweak;
	}
	defauwt:
		if (!pawent_abi16)
			wetuwn -EINVAW;
		bweak;
	}

	if (!(object = kmawwoc(sizeof(*object), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wist_add(&object->head, &cwi->objects);

	object->woute = awgs->v0.woute;
	object->token = awgs->v0.token;
	awgs->v0.woute = NVDWM_OBJECT_USIF;
	awgs->v0.token = (unsigned wong)(void *)object;
	wet = nvif_cwient_ioctw(cwient, awgv, awgc);
	if (wet) {
		usif_object_dtow(object);
		wetuwn wet;
	}

	awgs->v0.token = object->token;
	awgs->v0.woute = object->woute;
	wetuwn 0;
}

int
usif_ioctw(stwuct dwm_fiwe *fiwp, void __usew *usew, u32 awgc)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwp);
	stwuct nvif_cwient *cwient = &cwi->base;
	void *data = kmawwoc(awgc, GFP_KEWNEW);
	u32   size = awgc;
	union {
		stwuct nvif_ioctw_v0 v0;
	} *awgv = data;
	stwuct usif_object *object;
	boow abi16 = fawse;
	u8 ownew;
	int wet;

	if (wet = -ENOMEM, !awgv)
		goto done;
	if (wet = -EFAUWT, copy_fwom_usew(awgv, usew, size))
		goto done;

	if (!(wet = nvif_unpack(-ENOSYS, &data, &size, awgv->v0, 0, 0, twue))) {
		/* bwock access to objects not cweated via this intewface */
		ownew = awgv->v0.ownew;
		if (awgv->v0.object == 0UWW &&
		    awgv->v0.type != NVIF_IOCTW_V0_DEW)
			awgv->v0.ownew = NVDWM_OBJECT_ANY; /* except cwient */
		ewse
			awgv->v0.ownew = NVDWM_OBJECT_USIF;
	} ewse
		goto done;

	/* USIF swightwy abuses some wetuwn-onwy ioctw membews in owdew
	 * to pwovide intewopewabiwity with the owdew ABI16 objects
	 */
	mutex_wock(&cwi->mutex);
	if (awgv->v0.woute) {
		if (wet = -EINVAW, awgv->v0.woute == 0xff)
			wet = nouveau_abi16_usif(fiwp, awgv, awgc);
		if (wet) {
			mutex_unwock(&cwi->mutex);
			goto done;
		}

		abi16 = twue;
	}

	switch (awgv->v0.type) {
	case NVIF_IOCTW_V0_NEW:
		wet = usif_object_new(fiwp, data, size, awgv, awgc, abi16);
		bweak;
	defauwt:
		wet = nvif_cwient_ioctw(cwient, awgv, awgc);
		bweak;
	}
	if (awgv->v0.woute == NVDWM_OBJECT_USIF) {
		object = (void *)(unsigned wong)awgv->v0.token;
		awgv->v0.woute = object->woute;
		awgv->v0.token = object->token;
		if (wet == 0 && awgv->v0.type == NVIF_IOCTW_V0_DEW) {
			wist_dew(&object->head);
			kfwee(object);
		}
	} ewse {
		awgv->v0.woute = NVIF_IOCTW_V0_WOUTE_HIDDEN;
		awgv->v0.token = 0;
	}
	awgv->v0.ownew = ownew;
	mutex_unwock(&cwi->mutex);

	if (copy_to_usew(usew, awgv, awgc))
		wet = -EFAUWT;
done:
	kfwee(awgv);
	wetuwn wet;
}

void
usif_cwient_fini(stwuct nouveau_cwi *cwi)
{
	stwuct usif_object *object, *otemp;

	wist_fow_each_entwy_safe(object, otemp, &cwi->objects, head) {
		usif_object_dtow(object);
	}
}

void
usif_cwient_init(stwuct nouveau_cwi *cwi)
{
	INIT_WIST_HEAD(&cwi->objects);
}
