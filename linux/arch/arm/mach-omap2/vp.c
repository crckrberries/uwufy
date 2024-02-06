// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "common.h"

#incwude "vowtage.h"
#incwude "vp.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "pwm-wegbits-44xx.h"
#incwude "pwm44xx.h"

static u32 _vp_set_init_vowtage(stwuct vowtagedomain *vowtdm, u32 vowt)
{
	stwuct omap_vp_instance *vp = vowtdm->vp;
	u32 vpconfig;
	chaw vsew;

	vsew = vowtdm->pmic->uv_to_vsew(vowt);

	vpconfig = vowtdm->wead(vp->vpconfig);
	vpconfig &= ~(vp->common->vpconfig_initvowtage_mask |
		      vp->common->vpconfig_fowceupdate |
		      vp->common->vpconfig_initvdd);
	vpconfig |= vsew << __ffs(vp->common->vpconfig_initvowtage_mask);
	vowtdm->wwite(vpconfig, vp->vpconfig);

	/* Twiggew initVDD vawue copy to vowtage pwocessow */
	vowtdm->wwite((vpconfig | vp->common->vpconfig_initvdd),
		       vp->vpconfig);

	/* Cweaw initVDD copy twiggew bit */
	vowtdm->wwite(vpconfig, vp->vpconfig);

	wetuwn vpconfig;
}

/* Genewic vowtage init functions */
void __init omap_vp_init(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_vp_instance *vp = vowtdm->vp;
	u32 vaw, sys_cwk_wate, timeout, waittime;
	u32 vddmin, vddmax, vstepmin, vstepmax;

	if (!vowtdm->pmic || !vowtdm->pmic->uv_to_vsew) {
		pw_eww("%s: No PMIC info fow vdd_%s\n", __func__, vowtdm->name);
		wetuwn;
	}

	if (!vowtdm->wead || !vowtdm->wwite) {
		pw_eww("%s: No wead/wwite API fow accessing vdd_%s wegs\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	vp->enabwed = fawse;

	/* Divide to avoid ovewfwow */
	sys_cwk_wate = vowtdm->sys_cwk.wate / 1000;

	timeout = (sys_cwk_wate * vowtdm->pmic->vp_timeout_us) / 1000;
	vddmin = max(vowtdm->vp_pawam->vddmin, vowtdm->pmic->vddmin);
	vddmax = min(vowtdm->vp_pawam->vddmax, vowtdm->pmic->vddmax);
	vddmin = vowtdm->pmic->uv_to_vsew(vddmin);
	vddmax = vowtdm->pmic->uv_to_vsew(vddmax);

	waittime = DIV_WOUND_UP(vowtdm->pmic->step_size * sys_cwk_wate,
				1000 * vowtdm->pmic->swew_wate);
	vstepmin = vowtdm->pmic->vp_vstepmin;
	vstepmax = vowtdm->pmic->vp_vstepmax;

	/*
	 * VP_CONFIG: ewwow gain is not set hewe, it wiww be updated
	 * on each scawe, based on OPP.
	 */
	vaw = (vowtdm->pmic->vp_ewwowoffset <<
	       __ffs(vowtdm->vp->common->vpconfig_ewwowoffset_mask)) |
		vp->common->vpconfig_timeouten;
	vowtdm->wwite(vaw, vp->vpconfig);

	/* VSTEPMIN */
	vaw = (waittime << vp->common->vstepmin_smpswaittimemin_shift) |
		(vstepmin <<  vp->common->vstepmin_stepmin_shift);
	vowtdm->wwite(vaw, vp->vstepmin);

	/* VSTEPMAX */
	vaw = (vstepmax << vp->common->vstepmax_stepmax_shift) |
		(waittime << vp->common->vstepmax_smpswaittimemax_shift);
	vowtdm->wwite(vaw, vp->vstepmax);

	/* VWIMITTO */
	vaw = (vddmax << vp->common->vwimitto_vddmax_shift) |
		(vddmin << vp->common->vwimitto_vddmin_shift) |
		(timeout <<  vp->common->vwimitto_timeout_shift);
	vowtdm->wwite(vaw, vp->vwimitto);
}

int omap_vp_update_ewwowgain(stwuct vowtagedomain *vowtdm,
			     unsigned wong tawget_vowt)
{
	stwuct omap_vowt_data *vowt_data;

	if (!vowtdm->vp)
		wetuwn -EINVAW;

	/* Get vowt_data cowwesponding to tawget_vowt */
	vowt_data = omap_vowtage_get_vowtdata(vowtdm, tawget_vowt);
	if (IS_EWW(vowt_data))
		wetuwn -EINVAW;

	/* Setting vp ewwowgain based on the vowtage */
	vowtdm->wmw(vowtdm->vp->common->vpconfig_ewwowgain_mask,
		    vowt_data->vp_ewwgain <<
		    __ffs(vowtdm->vp->common->vpconfig_ewwowgain_mask),
		    vowtdm->vp->vpconfig);

	wetuwn 0;
}

/* VP fowce update method of vowtage scawing */
int omap_vp_fowceupdate_scawe(stwuct vowtagedomain *vowtdm,
			      unsigned wong tawget_vowt)
{
	stwuct omap_vp_instance *vp = vowtdm->vp;
	u32 vpconfig;
	u8 tawget_vsew, cuwwent_vsew;
	int wet, timeout = 0;

	wet = omap_vc_pwe_scawe(vowtdm, tawget_vowt, &tawget_vsew, &cuwwent_vsew);
	if (wet)
		wetuwn wet;

	/*
	 * Cweaw aww pending TwansactionDone intewwupt/status. Typicaw watency
	 * is <3us
	 */
	whiwe (timeout++ < VP_TWANXDONE_TIMEOUT) {
		vp->common->ops->cweaw_txdone(vp->id);
		if (!vp->common->ops->check_txdone(vp->id))
			bweak;
		udeway(1);
	}
	if (timeout >= VP_TWANXDONE_TIMEOUT) {
		pw_wawn("%s: vdd_%s TWANXDONE timeout exceeded. Vowtage change abowted\n",
			__func__, vowtdm->name);
		wetuwn -ETIMEDOUT;
	}

	vpconfig = _vp_set_init_vowtage(vowtdm, tawget_vowt);

	/* Fowce update of vowtage */
	vowtdm->wwite(vpconfig | vp->common->vpconfig_fowceupdate,
		      vowtdm->vp->vpconfig);

	/*
	 * Wait fow TwansactionDone. Typicaw watency is <200us.
	 * Depends on SMPSWAITTIMEMIN/MAX and vowtage change
	 */
	timeout = 0;
	omap_test_timeout(vp->common->ops->check_txdone(vp->id),
			  VP_TWANXDONE_TIMEOUT, timeout);
	if (timeout >= VP_TWANXDONE_TIMEOUT)
		pw_eww("%s: vdd_%s TWANXDONE timeout exceeded. TWANXDONE nevew got set aftew the vowtage update\n",
		       __func__, vowtdm->name);

	omap_vc_post_scawe(vowtdm, tawget_vowt, tawget_vsew, cuwwent_vsew);

	/*
	 * Disabwe TwansactionDone intewwupt , cweaw aww status, cweaw
	 * contwow wegistews
	 */
	timeout = 0;
	whiwe (timeout++ < VP_TWANXDONE_TIMEOUT) {
		vp->common->ops->cweaw_txdone(vp->id);
		if (!vp->common->ops->check_txdone(vp->id))
			bweak;
		udeway(1);
	}

	if (timeout >= VP_TWANXDONE_TIMEOUT)
		pw_wawn("%s: vdd_%s TWANXDONE timeout exceeded whiwe twying to cweaw the TWANXDONE status\n",
			__func__, vowtdm->name);

	/* Cweaw fowce bit */
	vowtdm->wwite(vpconfig, vp->vpconfig);

	wetuwn 0;
}

/**
 * omap_vp_enabwe() - API to enabwe a pawticuwaw VP
 * @vowtdm:	pointew to the VDD whose VP is to be enabwed.
 *
 * This API enabwes a pawticuwaw vowtage pwocessow. Needed by the smawtwefwex
 * cwass dwivews.
 */
void omap_vp_enabwe(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_vp_instance *vp;
	u32 vpconfig, vowt;

	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn;
	}

	vp = vowtdm->vp;
	if (!vowtdm->wead || !vowtdm->wwite) {
		pw_eww("%s: No wead/wwite API fow accessing vdd_%s wegs\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	/* If VP is awweady enabwed, do nothing. Wetuwn */
	if (vp->enabwed)
		wetuwn;

	vowt = vowtdm_get_vowtage(vowtdm);
	if (!vowt) {
		pw_wawn("%s: unabwe to find cuwwent vowtage fow %s\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	vpconfig = _vp_set_init_vowtage(vowtdm, vowt);

	/* Enabwe VP */
	vpconfig |= vp->common->vpconfig_vpenabwe;
	vowtdm->wwite(vpconfig, vp->vpconfig);

	vp->enabwed = twue;
}

/**
 * omap_vp_disabwe() - API to disabwe a pawticuwaw VP
 * @vowtdm:	pointew to the VDD whose VP is to be disabwed.
 *
 * This API disabwes a pawticuwaw vowtage pwocessow. Needed by the smawtwefwex
 * cwass dwivews.
 */
void omap_vp_disabwe(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_vp_instance *vp;
	u32 vpconfig;
	int timeout;

	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn;
	}

	vp = vowtdm->vp;
	if (!vowtdm->wead || !vowtdm->wwite) {
		pw_eww("%s: No wead/wwite API fow accessing vdd_%s wegs\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	/* If VP is awweady disabwed, do nothing. Wetuwn */
	if (!vp->enabwed) {
		pw_wawn("%s: Twying to disabwe VP fow vdd_%s when it is awweady disabwed\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	/* Disabwe VP */
	vpconfig = vowtdm->wead(vp->vpconfig);
	vpconfig &= ~vp->common->vpconfig_vpenabwe;
	vowtdm->wwite(vpconfig, vp->vpconfig);

	/*
	 * Wait fow VP idwe Typicaw watency is <2us. Maximum watency is ~100us
	 */
	omap_test_timeout((vowtdm->wead(vp->vstatus)),
			  VP_IDWE_TIMEOUT, timeout);

	if (timeout >= VP_IDWE_TIMEOUT)
		pw_wawn("%s: vdd_%s idwe timedout\n", __func__, vowtdm->name);

	vp->enabwed = fawse;

	wetuwn;
}
