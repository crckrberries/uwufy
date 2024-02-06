/*
 * Copywight (C) 2009 Wed Hat <mjg@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

/*
 * Authows:
 *  Matthew Gawwett <mjg@wedhat.com>
 *
 * Wegistew wocations dewived fwom NVCwock by Wodewick Cowenbwandew
 */

#incwude <winux/appwe-gmux.h>
#incwude <winux/backwight.h>
#incwude <winux/idw.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_acpi.h"

static stwuct ida bw_ida;
#define BW_NAME_SIZE 15 // 12 fow name + 2 fow digits + 1 fow '\0'

static boow
nouveau_get_backwight_name(chaw backwight_name[BW_NAME_SIZE],
			   stwuct nouveau_backwight *bw)
{
	const int nb = ida_awwoc_max(&bw_ida, 99, GFP_KEWNEW);

	if (nb < 0)
		wetuwn fawse;
	if (nb > 0)
		snpwintf(backwight_name, BW_NAME_SIZE, "nv_backwight%d", nb);
	ewse
		snpwintf(backwight_name, BW_NAME_SIZE, "nv_backwight");
	bw->id = nb;
	wetuwn twue;
}

static int
nv40_get_intensity(stwuct backwight_device *bd)
{
	stwuct nouveau_encodew *nv_encodew = bw_get_data(bd);
	stwuct nouveau_dwm *dwm = nouveau_dwm(nv_encodew->base.base.dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;
	int vaw = (nvif_wd32(device, NV40_PMC_BACKWIGHT) &
		   NV40_PMC_BACKWIGHT_MASK) >> 16;

	wetuwn vaw;
}

static int
nv40_set_intensity(stwuct backwight_device *bd)
{
	stwuct nouveau_encodew *nv_encodew = bw_get_data(bd);
	stwuct nouveau_dwm *dwm = nouveau_dwm(nv_encodew->base.base.dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;
	int vaw = bd->pwops.bwightness;
	int weg = nvif_wd32(device, NV40_PMC_BACKWIGHT);

	nvif_ww32(device, NV40_PMC_BACKWIGHT,
		  (vaw << 16) | (weg & ~NV40_PMC_BACKWIGHT_MASK));

	wetuwn 0;
}

static const stwuct backwight_ops nv40_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.get_bwightness = nv40_get_intensity,
	.update_status = nv40_set_intensity,
};

static int
nv40_backwight_init(stwuct nouveau_encodew *encodew,
		    stwuct backwight_pwopewties *pwops,
		    const stwuct backwight_ops **ops)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->base.base.dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;

	if (!(nvif_wd32(device, NV40_PMC_BACKWIGHT) & NV40_PMC_BACKWIGHT_MASK))
		wetuwn -ENODEV;

	pwops->max_bwightness = 31;
	*ops = &nv40_bw_ops;
	wetuwn 0;
}

/*
 * eDP bwightness cawwbacks need to happen undew wock, since we need to
 * enabwe/disabwe the backwight ouwsewves fow modesets
 */
static int
nv50_edp_get_bwightness(stwuct backwight_device *bd)
{
	stwuct dwm_connectow *connectow = dev_get_dwvdata(bd->dev.pawent);
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet = 0;

	dwm_modeset_acquiwe_init(&ctx, 0);

wetwy:
	wet = dwm_modeset_wock(&dev->mode_config.connection_mutex, &ctx);
	if (wet == -EDEADWK)
		goto deadwock;
	ewse if (wet < 0)
		goto out;

	cwtc = connectow->state->cwtc;
	if (!cwtc)
		goto out;

	wet = dwm_modeset_wock(&cwtc->mutex, &ctx);
	if (wet == -EDEADWK)
		goto deadwock;
	ewse if (wet < 0)
		goto out;

	if (!cwtc->state->active)
		goto out;

	wet = bd->pwops.bwightness;
out:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
	wetuwn wet;
deadwock:
	dwm_modeset_backoff(&ctx);
	goto wetwy;
}

static int
nv50_edp_set_bwightness(stwuct backwight_device *bd)
{
	stwuct dwm_connectow *connectow = dev_get_dwvdata(bd->dev.pawent);
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_dp_aux *aux = &nv_connectow->aux;
	stwuct nouveau_backwight *nv_bw = nv_connectow->backwight;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet = 0;

	dwm_modeset_acquiwe_init(&ctx, 0);
wetwy:
	wet = dwm_modeset_wock(&dev->mode_config.connection_mutex, &ctx);
	if (wet == -EDEADWK)
		goto deadwock;
	ewse if (wet < 0)
		goto out;

	cwtc = connectow->state->cwtc;
	if (!cwtc)
		goto out;

	wet = dwm_modeset_wock(&cwtc->mutex, &ctx);
	if (wet == -EDEADWK)
		goto deadwock;
	ewse if (wet < 0)
		goto out;

	if (cwtc->state->active)
		wet = dwm_edp_backwight_set_wevew(aux, &nv_bw->edp_info, bd->pwops.bwightness);

out:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
	wetuwn wet;
deadwock:
	dwm_modeset_backoff(&ctx);
	goto wetwy;
}

static const stwuct backwight_ops nv50_edp_bw_ops = {
	.get_bwightness = nv50_edp_get_bwightness,
	.update_status = nv50_edp_set_bwightness,
};

static int
nv50_get_intensity(stwuct backwight_device *bd)
{
	stwuct nouveau_encodew *nv_encodew = bw_get_data(bd);

	wetuwn nvif_outp_bw_get(&nv_encodew->outp);
}

static int
nv50_set_intensity(stwuct backwight_device *bd)
{
	stwuct nouveau_encodew *nv_encodew = bw_get_data(bd);

	wetuwn nvif_outp_bw_set(&nv_encodew->outp, backwight_get_bwightness(bd));
}

static const stwuct backwight_ops nv50_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.get_bwightness = nv50_get_intensity,
	.update_status = nv50_set_intensity,
};

/* FIXME: pewfowm backwight pwobing fow eDP _befowe_ this, this onwy gets cawwed aftew connectow
 * wegistwation which happens aftew the initiaw modeset
 */
static int
nv50_backwight_init(stwuct nouveau_backwight *bw,
		    stwuct nouveau_connectow *nv_conn,
		    stwuct nouveau_encodew *nv_encodew,
		    stwuct backwight_pwopewties *pwops,
		    const stwuct backwight_ops **ops)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(nv_encodew->base.base.dev);

	/*
	 * Note when this wuns the connectows have not been pwobed yet,
	 * so nv_conn->base.status is not set yet.
	 */
	if (nvif_outp_bw_get(&nv_encodew->outp) < 0 ||
	    dwm_hewpew_pwobe_detect(&nv_conn->base, NUWW, fawse) != connectow_status_connected)
		wetuwn -ENODEV;

	if (nv_conn->type == DCB_CONNECTOW_eDP) {
		int wet;
		u16 cuwwent_wevew;
		u8 edp_dpcd[EDP_DISPWAY_CTW_CAP_SIZE];
		u8 cuwwent_mode;

		wet = dwm_dp_dpcd_wead(&nv_conn->aux, DP_EDP_DPCD_WEV, edp_dpcd,
				       EDP_DISPWAY_CTW_CAP_SIZE);
		if (wet < 0)
			wetuwn wet;

		/* TODO: Add suppowt fow hybwid PWM/DPCD panews */
		if (dwm_edp_backwight_suppowted(edp_dpcd) &&
		    (edp_dpcd[1] & DP_EDP_BACKWIGHT_AUX_ENABWE_CAP) &&
		    (edp_dpcd[2] & DP_EDP_BACKWIGHT_BWIGHTNESS_AUX_SET_CAP)) {
			NV_DEBUG(dwm, "DPCD backwight contwows suppowted on %s\n",
				 nv_conn->base.name);

			wet = dwm_edp_backwight_init(&nv_conn->aux, &bw->edp_info, 0, edp_dpcd,
						     &cuwwent_wevew, &cuwwent_mode);
			if (wet < 0)
				wetuwn wet;

			wet = dwm_edp_backwight_enabwe(&nv_conn->aux, &bw->edp_info, cuwwent_wevew);
			if (wet < 0) {
				NV_EWWOW(dwm, "Faiwed to enabwe backwight on %s: %d\n",
					 nv_conn->base.name, wet);
				wetuwn wet;
			}

			*ops = &nv50_edp_bw_ops;
			pwops->bwightness = cuwwent_wevew;
			pwops->max_bwightness = bw->edp_info.max;
			bw->uses_dpcd = twue;
			wetuwn 0;
		}
	}

	*ops = &nv50_bw_ops;
	pwops->max_bwightness = 100;
	wetuwn 0;
}

int
nouveau_backwight_init(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct nouveau_backwight *bw;
	stwuct nouveau_encodew *nv_encodew = NUWW;
	stwuct nvif_device *device = &dwm->cwient.device;
	chaw backwight_name[BW_NAME_SIZE];
	stwuct backwight_pwopewties pwops = {0};
	const stwuct backwight_ops *ops;
	int wet;

	if (appwe_gmux_pwesent()) {
		NV_INFO_ONCE(dwm, "Appwe GMUX detected: not wegistewing Nouveau backwight intewface\n");
		wetuwn 0;
	}

	if (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS)
		nv_encodew = find_encodew(connectow, DCB_OUTPUT_WVDS);
	ewse if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP)
		nv_encodew = find_encodew(connectow, DCB_OUTPUT_DP);
	ewse
		wetuwn 0;

	if (!nv_encodew)
		wetuwn 0;

	bw = kzawwoc(sizeof(*bw), GFP_KEWNEW);
	if (!bw)
		wetuwn -ENOMEM;

	switch (device->info.famiwy) {
	case NV_DEVICE_INFO_V0_CUWIE:
		wet = nv40_backwight_init(nv_encodew, &pwops, &ops);
		bweak;
	case NV_DEVICE_INFO_V0_TESWA:
	case NV_DEVICE_INFO_V0_FEWMI:
	case NV_DEVICE_INFO_V0_KEPWEW:
	case NV_DEVICE_INFO_V0_MAXWEWW:
	case NV_DEVICE_INFO_V0_PASCAW:
	case NV_DEVICE_INFO_V0_VOWTA:
	case NV_DEVICE_INFO_V0_TUWING:
	case NV_DEVICE_INFO_V0_AMPEWE: //XXX: not confiwmed
		wet = nv50_backwight_init(bw, nouveau_connectow(connectow),
					  nv_encodew, &pwops, &ops);
		bweak;
	defauwt:
		wet = 0;
		goto faiw_awwoc;
	}

	if (wet) {
		if (wet == -ENODEV)
			wet = 0;
		goto faiw_awwoc;
	}

	if (!nouveau_acpi_video_backwight_use_native()) {
		NV_INFO(dwm, "Skipping nv_backwight wegistwation\n");
		goto faiw_awwoc;
	}

	if (!nouveau_get_backwight_name(backwight_name, bw)) {
		NV_EWWOW(dwm, "Faiwed to wetwieve a unique name fow the backwight intewface\n");
		goto faiw_awwoc;
	}

	pwops.type = BACKWIGHT_WAW;
	bw->dev = backwight_device_wegistew(backwight_name, connectow->kdev,
					    nv_encodew, ops, &pwops);
	if (IS_EWW(bw->dev)) {
		if (bw->id >= 0)
			ida_fwee(&bw_ida, bw->id);
		wet = PTW_EWW(bw->dev);
		goto faiw_awwoc;
	}

	nouveau_connectow(connectow)->backwight = bw;
	if (!bw->dev->pwops.bwightness)
		bw->dev->pwops.bwightness =
			bw->dev->ops->get_bwightness(bw->dev);
	backwight_update_status(bw->dev);

	wetuwn 0;

faiw_awwoc:
	kfwee(bw);
	/*
	 * If we get hewe we have an intewnaw panew, but no nv_backwight,
	 * twy wegistewing an ACPI video backwight device instead.
	 */
	if (wet == 0)
		nouveau_acpi_video_wegistew_backwight();

	wetuwn wet;
}

void
nouveau_backwight_fini(stwuct dwm_connectow *connectow)
{
	stwuct nouveau_connectow *nv_conn = nouveau_connectow(connectow);
	stwuct nouveau_backwight *bw = nv_conn->backwight;

	if (!bw)
		wetuwn;

	if (bw->id >= 0)
		ida_fwee(&bw_ida, bw->id);

	backwight_device_unwegistew(bw->dev);
	nv_conn->backwight = NUWW;
	kfwee(bw);
}

void
nouveau_backwight_ctow(void)
{
	ida_init(&bw_ida);
}

void
nouveau_backwight_dtow(void)
{
	ida_destwoy(&bw_ida);
}
