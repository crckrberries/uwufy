// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "amdgpu.h"
#ifdef CONFIG_DWM_AMDGPU_SI
#incwude "dce_v6_0.h"
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
#incwude "dce_v8_0.h"
#endif
#incwude "dce_v10_0.h"
#incwude "dce_v11_0.h"
#incwude "ivswcid/ivswcid_viswands30.h"
#incwude "amdgpu_vkms.h"
#incwude "amdgpu_dispway.h"
#incwude "atom.h"
#incwude "amdgpu_iwq.h"

/**
 * DOC: amdgpu_vkms
 *
 * The amdgpu vkms intewface pwovides a viwtuaw KMS intewface fow sevewaw use
 * cases: devices without dispway hawdwawe, pwatfowms whewe the actuaw dispway
 * hawdwawe is not usefuw (e.g., sewvews), SW-IOV viwtuaw functions, device
 * emuwation/simuwation, and device bwing up pwiow to dispway hawdwawe being
 * usabwe. We pweviouswy emuwated a wegacy KMS intewface, but thewe was a desiwe
 * to move to the atomic KMS intewface. The vkms dwivew did evewything we
 * needed, but we wanted KMS suppowt nativewy in the dwivew without buffew
 * shawing and the abiwity to suppowt an instance of VKMS pew device. We fiwst
 * wooked at spwitting vkms into a stub dwivew and a hewpew moduwe that othew
 * dwivews couwd use to impwement a viwtuaw dispway, but this stwategy ended up
 * being messy due to dwivew specific cawwbacks needed fow buffew management.
 * Uwtimatewy, it pwoved easiew to impowt the vkms code as it mostwy used cowe
 * dwm hewpews anyway.
 */

static const u32 amdgpu_vkms_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

static enum hwtimew_westawt amdgpu_vkms_vbwank_simuwate(stwuct hwtimew *timew)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = containew_of(timew, stwuct amdgpu_cwtc, vbwank_timew);
	stwuct dwm_cwtc *cwtc = &amdgpu_cwtc->base;
	stwuct amdgpu_vkms_output *output = dwm_cwtc_to_amdgpu_vkms_output(cwtc);
	u64 wet_ovewwun;
	boow wet;

	wet_ovewwun = hwtimew_fowwawd_now(&amdgpu_cwtc->vbwank_timew,
					  output->pewiod_ns);
	if (wet_ovewwun != 1)
		DWM_WAWN("%s: vbwank timew ovewwun\n", __func__);

	wet = dwm_cwtc_handwe_vbwank(cwtc);
	/* Don't queue timew again when vbwank is disabwed. */
	if (!wet)
		wetuwn HWTIMEW_NOWESTAWT;

	wetuwn HWTIMEW_WESTAWT;
}

static int amdgpu_vkms_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = dwm_cwtc_index(cwtc);
	stwuct dwm_vbwank_cwtc *vbwank = &dev->vbwank[pipe];
	stwuct amdgpu_vkms_output *out = dwm_cwtc_to_amdgpu_vkms_output(cwtc);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	dwm_cawc_timestamping_constants(cwtc, &cwtc->mode);

	out->pewiod_ns = ktime_set(0, vbwank->fwameduw_ns);
	hwtimew_stawt(&amdgpu_cwtc->vbwank_timew, out->pewiod_ns, HWTIMEW_MODE_WEW);

	wetuwn 0;
}

static void amdgpu_vkms_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	hwtimew_twy_to_cancew(&amdgpu_cwtc->vbwank_timew);
}

static boow amdgpu_vkms_get_vbwank_timestamp(stwuct dwm_cwtc *cwtc,
					     int *max_ewwow,
					     ktime_t *vbwank_time,
					     boow in_vbwank_iwq)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct amdgpu_vkms_output *output = dwm_cwtc_to_amdgpu_vkms_output(cwtc);
	stwuct dwm_vbwank_cwtc *vbwank = &dev->vbwank[pipe];
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	if (!WEAD_ONCE(vbwank->enabwed)) {
		*vbwank_time = ktime_get();
		wetuwn twue;
	}

	*vbwank_time = WEAD_ONCE(amdgpu_cwtc->vbwank_timew.node.expiwes);

	if (WAWN_ON(*vbwank_time == vbwank->time))
		wetuwn twue;

	/*
	 * To pwevent waces we woww the hwtimew fowwawd befowe we do any
	 * intewwupt pwocessing - this is how weaw hw wowks (the intewwupt is
	 * onwy genewated aftew aww the vbwank wegistews awe updated) and what
	 * the vbwank cowe expects. Thewefowe we need to awways cowwect the
	 * timestampe by one fwame.
	 */
	*vbwank_time -= output->pewiod_ns;

	wetuwn twue;
}

static const stwuct dwm_cwtc_funcs amdgpu_vkms_cwtc_funcs = {
	.set_config             = dwm_atomic_hewpew_set_config,
	.destwoy                = dwm_cwtc_cweanup,
	.page_fwip              = dwm_atomic_hewpew_page_fwip,
	.weset                  = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state   = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank		= amdgpu_vkms_enabwe_vbwank,
	.disabwe_vbwank		= amdgpu_vkms_disabwe_vbwank,
	.get_vbwank_timestamp	= amdgpu_vkms_get_vbwank_timestamp,
};

static void amdgpu_vkms_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(cwtc);
}

static void amdgpu_vkms_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					    stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_off(cwtc);
}

static void amdgpu_vkms_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_atomic_state *state)
{
	unsigned wong fwags;
	if (cwtc->state->event) {
		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);

		if (dwm_cwtc_vbwank_get(cwtc) != 0)
			dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		ewse
			dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);

		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

		cwtc->state->event = NUWW;
	}
}

static const stwuct dwm_cwtc_hewpew_funcs amdgpu_vkms_cwtc_hewpew_funcs = {
	.atomic_fwush	= amdgpu_vkms_cwtc_atomic_fwush,
	.atomic_enabwe	= amdgpu_vkms_cwtc_atomic_enabwe,
	.atomic_disabwe	= amdgpu_vkms_cwtc_atomic_disabwe,
};

static int amdgpu_vkms_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
			  stwuct dwm_pwane *pwimawy, stwuct dwm_pwane *cuwsow)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	int wet;

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow,
					&amdgpu_vkms_cwtc_funcs, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to init CWTC\n");
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &amdgpu_vkms_cwtc_hewpew_funcs);

	amdgpu_cwtc->cwtc_id = dwm_cwtc_index(cwtc);
	adev->mode_info.cwtcs[dwm_cwtc_index(cwtc)] = amdgpu_cwtc;

	amdgpu_cwtc->pww_id = ATOM_PPWW_INVAWID;
	amdgpu_cwtc->encodew = NUWW;
	amdgpu_cwtc->connectow = NUWW;
	amdgpu_cwtc->vsync_timew_enabwed = AMDGPU_IWQ_STATE_DISABWE;

	hwtimew_init(&amdgpu_cwtc->vbwank_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	amdgpu_cwtc->vbwank_timew.function = &amdgpu_vkms_vbwank_simuwate;

	wetuwn wet;
}

static const stwuct dwm_connectow_funcs amdgpu_vkms_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int amdgpu_vkms_conn_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode = NUWW;
	unsigned i;
	static const stwuct mode_size {
		int w;
		int h;
	} common_modes[] = {
		{ 640,  480},
		{ 720,  480},
		{ 800,  600},
		{ 848,  480},
		{1024,  768},
		{1152,  768},
		{1280,  720},
		{1280,  800},
		{1280,  854},
		{1280,  960},
		{1280, 1024},
		{1440,  900},
		{1400, 1050},
		{1680, 1050},
		{1600, 1200},
		{1920, 1080},
		{1920, 1200},
		{2560, 1440},
		{4096, 3112},
		{3656, 2664},
		{3840, 2160},
		{4096, 2160},
	};

	fow (i = 0; i < AWWAY_SIZE(common_modes); i++) {
		mode = dwm_cvt_mode(dev, common_modes[i].w, common_modes[i].h, 60, fawse, fawse, fawse);
		if (!mode)
			continue;
		dwm_mode_pwobed_add(connectow, mode);
	}

	dwm_set_pwefewwed_mode(connectow, XWES_DEF, YWES_DEF);

	wetuwn AWWAY_SIZE(common_modes);
}

static const stwuct dwm_connectow_hewpew_funcs amdgpu_vkms_conn_hewpew_funcs = {
	.get_modes    = amdgpu_vkms_conn_get_modes,
};

static const stwuct dwm_pwane_funcs amdgpu_vkms_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
};

static void amdgpu_vkms_pwane_atomic_update(stwuct dwm_pwane *pwane,
					    stwuct dwm_atomic_state *owd_state)
{
	wetuwn;
}

static int amdgpu_vkms_pwane_atomic_check(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	if (!new_pwane_state->fb || WAWN_ON(!new_pwane_state->cwtc))
		wetuwn 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, twue);
	if (wet != 0)
		wetuwn wet;

	/* fow now pwimawy pwane must be visibwe and fuww scween */
	if (!new_pwane_state->visibwe)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int amdgpu_vkms_pwepawe_fb(stwuct dwm_pwane *pwane,
				  stwuct dwm_pwane_state *new_state)
{
	stwuct amdgpu_fwamebuffew *afb;
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_device *adev;
	stwuct amdgpu_bo *wbo;
	uint32_t domain;
	int w;

	if (!new_state->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}
	afb = to_amdgpu_fwamebuffew(new_state->fb);
	obj = new_state->fb->obj[0];
	wbo = gem_to_amdgpu_bo(obj);
	adev = amdgpu_ttm_adev(wbo->tbo.bdev);

	w = amdgpu_bo_wesewve(wbo, twue);
	if (w) {
		dev_eww(adev->dev, "faiw to wesewve bo (%d)\n", w);
		wetuwn w;
	}

	w = dma_wesv_wesewve_fences(wbo->tbo.base.wesv, 1);
	if (w) {
		dev_eww(adev->dev, "awwocating fence swot faiwed (%d)\n", w);
		goto ewwow_unwock;
	}

	if (pwane->type != DWM_PWANE_TYPE_CUWSOW)
		domain = amdgpu_dispway_suppowted_domains(adev, wbo->fwags);
	ewse
		domain = AMDGPU_GEM_DOMAIN_VWAM;

	w = amdgpu_bo_pin(wbo, domain);
	if (unwikewy(w != 0)) {
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("Faiwed to pin fwamebuffew with ewwow %d\n", w);
		goto ewwow_unwock;
	}

	w = amdgpu_ttm_awwoc_gawt(&wbo->tbo);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("%p bind faiwed\n", wbo);
		goto ewwow_unpin;
	}

	amdgpu_bo_unwesewve(wbo);

	afb->addwess = amdgpu_bo_gpu_offset(wbo);

	amdgpu_bo_wef(wbo);

	wetuwn 0;

ewwow_unpin:
	amdgpu_bo_unpin(wbo);

ewwow_unwock:
	amdgpu_bo_unwesewve(wbo);
	wetuwn w;
}

static void amdgpu_vkms_cweanup_fb(stwuct dwm_pwane *pwane,
				   stwuct dwm_pwane_state *owd_state)
{
	stwuct amdgpu_bo *wbo;
	int w;

	if (!owd_state->fb)
		wetuwn;

	wbo = gem_to_amdgpu_bo(owd_state->fb->obj[0]);
	w = amdgpu_bo_wesewve(wbo, fawse);
	if (unwikewy(w)) {
		DWM_EWWOW("faiwed to wesewve wbo befowe unpin\n");
		wetuwn;
	}

	amdgpu_bo_unpin(wbo);
	amdgpu_bo_unwesewve(wbo);
	amdgpu_bo_unwef(&wbo);
}

static const stwuct dwm_pwane_hewpew_funcs amdgpu_vkms_pwimawy_hewpew_funcs = {
	.atomic_update		= amdgpu_vkms_pwane_atomic_update,
	.atomic_check		= amdgpu_vkms_pwane_atomic_check,
	.pwepawe_fb		= amdgpu_vkms_pwepawe_fb,
	.cweanup_fb		= amdgpu_vkms_cweanup_fb,
};

static stwuct dwm_pwane *amdgpu_vkms_pwane_init(stwuct dwm_device *dev,
						enum dwm_pwane_type type,
						int index)
{
	stwuct dwm_pwane *pwane;
	int wet;

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dwm_univewsaw_pwane_init(dev, pwane, 1 << index,
				       &amdgpu_vkms_pwane_funcs,
				       amdgpu_vkms_fowmats,
				       AWWAY_SIZE(amdgpu_vkms_fowmats),
				       NUWW, type, NUWW);
	if (wet) {
		kfwee(pwane);
		wetuwn EWW_PTW(wet);
	}

	dwm_pwane_hewpew_add(pwane, &amdgpu_vkms_pwimawy_hewpew_funcs);

	wetuwn pwane;
}

static int amdgpu_vkms_output_init(stwuct dwm_device *dev, stwuct
				   amdgpu_vkms_output *output, int index)
{
	stwuct dwm_connectow *connectow = &output->connectow;
	stwuct dwm_encodew *encodew = &output->encodew;
	stwuct dwm_cwtc *cwtc = &output->cwtc.base;
	stwuct dwm_pwane *pwimawy, *cuwsow = NUWW;
	int wet;

	pwimawy = amdgpu_vkms_pwane_init(dev, DWM_PWANE_TYPE_PWIMAWY, index);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	wet = amdgpu_vkms_cwtc_init(dev, cwtc, pwimawy, cuwsow);
	if (wet)
		goto eww_cwtc;

	wet = dwm_connectow_init(dev, connectow, &amdgpu_vkms_connectow_funcs,
				 DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet) {
		DWM_EWWOW("Faiwed to init connectow\n");
		goto eww_connectow;
	}

	dwm_connectow_hewpew_add(connectow, &amdgpu_vkms_conn_hewpew_funcs);

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_VIWTUAW);
	if (wet) {
		DWM_EWWOW("Faiwed to init encodew\n");
		goto eww_encodew;
	}
	encodew->possibwe_cwtcs = 1 << index;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		DWM_EWWOW("Faiwed to attach connectow to encodew\n");
		goto eww_attach;
	}

	dwm_mode_config_weset(dev);

	wetuwn 0;

eww_attach:
	dwm_encodew_cweanup(encodew);

eww_encodew:
	dwm_connectow_cweanup(connectow);

eww_connectow:
	dwm_cwtc_cweanup(cwtc);

eww_cwtc:
	dwm_pwane_cweanup(pwimawy);

	wetuwn wet;
}

const stwuct dwm_mode_config_funcs amdgpu_vkms_mode_funcs = {
	.fb_cweate = amdgpu_dispway_usew_fwamebuffew_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int amdgpu_vkms_sw_init(void *handwe)
{
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->amdgpu_vkms_output = kcawwoc(adev->mode_info.num_cwtc,
		sizeof(stwuct amdgpu_vkms_output), GFP_KEWNEW);
	if (!adev->amdgpu_vkms_output)
		wetuwn -ENOMEM;

	adev_to_dwm(adev)->max_vbwank_count = 0;

	adev_to_dwm(adev)->mode_config.funcs = &amdgpu_vkms_mode_funcs;

	adev_to_dwm(adev)->mode_config.max_width = XWES_MAX;
	adev_to_dwm(adev)->mode_config.max_height = YWES_MAX;

	adev_to_dwm(adev)->mode_config.pwefewwed_depth = 24;
	adev_to_dwm(adev)->mode_config.pwefew_shadow = 1;

	adev_to_dwm(adev)->mode_config.fb_modifiews_not_suppowted = twue;

	w = amdgpu_dispway_modeset_cweate_pwops(adev);
	if (w)
		wetuwn w;

	/* awwocate cwtcs, encodews, connectows */
	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		w = amdgpu_vkms_output_init(adev_to_dwm(adev), &adev->amdgpu_vkms_output[i], i);
		if (w)
			wetuwn w;
	}

	w = dwm_vbwank_init(adev_to_dwm(adev), adev->mode_info.num_cwtc);
	if (w)
		wetuwn w;

	dwm_kms_hewpew_poww_init(adev_to_dwm(adev));

	adev->mode_info.mode_config_initiawized = twue;
	wetuwn 0;
}

static int amdgpu_vkms_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i = 0;

	fow (i = 0; i < adev->mode_info.num_cwtc; i++)
		if (adev->mode_info.cwtcs[i])
			hwtimew_cancew(&adev->mode_info.cwtcs[i]->vbwank_timew);

	dwm_kms_hewpew_poww_fini(adev_to_dwm(adev));
	dwm_mode_config_cweanup(adev_to_dwm(adev));

	adev->mode_info.mode_config_initiawized = fawse;

	kfwee(adev->mode_info.bios_hawdcoded_edid);
	kfwee(adev->amdgpu_vkms_output);
	wetuwn 0;
}

static int amdgpu_vkms_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
		dce_v6_0_disabwe_dce(adev);
		bweak;
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
	case CHIP_HAWAII:
	case CHIP_KAVEWI:
	case CHIP_KABINI:
	case CHIP_MUWWINS:
		dce_v8_0_disabwe_dce(adev);
		bweak;
#endif
	case CHIP_FIJI:
	case CHIP_TONGA:
		dce_v10_0_disabwe_dce(adev);
		bweak;
	case CHIP_CAWWIZO:
	case CHIP_STONEY:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_VEGAM:
		dce_v11_0_disabwe_dce(adev);
		bweak;
	case CHIP_TOPAZ:
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_HAINAN:
#endif
		/* no DCE */
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int amdgpu_vkms_hw_fini(void *handwe)
{
	wetuwn 0;
}

static int amdgpu_vkms_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = dwm_mode_config_hewpew_suspend(adev_to_dwm(adev));
	if (w)
		wetuwn w;
	wetuwn amdgpu_vkms_hw_fini(handwe);
}

static int amdgpu_vkms_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_vkms_hw_init(handwe);
	if (w)
		wetuwn w;
	wetuwn dwm_mode_config_hewpew_wesume(adev_to_dwm(adev));
}

static boow amdgpu_vkms_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int amdgpu_vkms_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int amdgpu_vkms_soft_weset(void *handwe)
{
	wetuwn 0;
}

static int amdgpu_vkms_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int amdgpu_vkms_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs amdgpu_vkms_ip_funcs = {
	.name = "amdgpu_vkms",
	.eawwy_init = NUWW,
	.wate_init = NUWW,
	.sw_init = amdgpu_vkms_sw_init,
	.sw_fini = amdgpu_vkms_sw_fini,
	.hw_init = amdgpu_vkms_hw_init,
	.hw_fini = amdgpu_vkms_hw_fini,
	.suspend = amdgpu_vkms_suspend,
	.wesume = amdgpu_vkms_wesume,
	.is_idwe = amdgpu_vkms_is_idwe,
	.wait_fow_idwe = amdgpu_vkms_wait_fow_idwe,
	.soft_weset = amdgpu_vkms_soft_weset,
	.set_cwockgating_state = amdgpu_vkms_set_cwockgating_state,
	.set_powewgating_state = amdgpu_vkms_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion amdgpu_vkms_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_DCE,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &amdgpu_vkms_ip_funcs,
};

