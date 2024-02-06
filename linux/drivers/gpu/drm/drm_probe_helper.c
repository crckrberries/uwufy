/*
 * Copywight (c) 2006-2008 Intew Cowpowation
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 *
 * DWM cowe CWTC wewated functions
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 *
 * Authows:
 *      Keith Packawd
 *	Ewic Anhowt <ewic@anhowt.net>
 *      Dave Aiwwie <aiwwied@winux.ie>
 *      Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/moduwepawam.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwient.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_sysfs.h>

#incwude "dwm_cwtc_hewpew_intewnaw.h"

/**
 * DOC: output pwobing hewpew ovewview
 *
 * This wibwawy pwovides some hewpew code fow output pwobing. It pwovides an
 * impwementation of the cowe &dwm_connectow_funcs.fiww_modes intewface with
 * dwm_hewpew_pwobe_singwe_connectow_modes().
 *
 * It awso pwovides suppowt fow powwing connectows with a wowk item and fow
 * genewic hotpwug intewwupt handwing whewe the dwivew doesn't ow cannot keep
 * twack of a pew-connectow hpd intewwupt.
 *
 * This hewpew wibwawy can be used independentwy of the modeset hewpew wibwawy.
 * Dwivews can awso ovewwwite diffewent pawts e.g. use theiw own hotpwug
 * handwing code to avoid pwobing unwewated outputs.
 *
 * The pwobe hewpews shawe the function tabwe stwuctuwes with othew dispway
 * hewpew wibwawies. See &stwuct dwm_connectow_hewpew_funcs fow the detaiws.
 */

static boow dwm_kms_hewpew_poww = twue;
moduwe_pawam_named(poww, dwm_kms_hewpew_poww, boow, 0600);

static enum dwm_mode_status
dwm_mode_vawidate_fwag(const stwuct dwm_dispway_mode *mode,
		       int fwags)
{
	if ((mode->fwags & DWM_MODE_FWAG_INTEWWACE) &&
	    !(fwags & DWM_MODE_FWAG_INTEWWACE))
		wetuwn MODE_NO_INTEWWACE;

	if ((mode->fwags & DWM_MODE_FWAG_DBWSCAN) &&
	    !(fwags & DWM_MODE_FWAG_DBWSCAN))
		wetuwn MODE_NO_DBWESCAN;

	if ((mode->fwags & DWM_MODE_FWAG_3D_MASK) &&
	    !(fwags & DWM_MODE_FWAG_3D_MASK))
		wetuwn MODE_NO_STEWEO;

	wetuwn MODE_OK;
}

static int
dwm_mode_vawidate_pipewine(stwuct dwm_dispway_mode *mode,
			   stwuct dwm_connectow *connectow,
			   stwuct dwm_modeset_acquiwe_ctx *ctx,
			   enum dwm_mode_status *status)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_encodew *encodew;
	int wet;

	/* Step 1: Vawidate against connectow */
	wet = dwm_connectow_mode_vawid(connectow, mode, ctx, status);
	if (wet || *status != MODE_OK)
		wetuwn wet;

	/* Step 2: Vawidate against encodews and cwtcs */
	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		stwuct dwm_bwidge *bwidge;
		stwuct dwm_cwtc *cwtc;

		*status = dwm_encodew_mode_vawid(encodew, mode);
		if (*status != MODE_OK) {
			/* No point in continuing fow cwtc check as this encodew
			 * wiww not accept the mode anyway. If aww encodews
			 * weject the mode then, at exit, wet wiww not be
			 * MODE_OK. */
			continue;
		}

		bwidge = dwm_bwidge_chain_get_fiwst_bwidge(encodew);
		*status = dwm_bwidge_chain_mode_vawid(bwidge,
						      &connectow->dispway_info,
						      mode);
		if (*status != MODE_OK) {
			/* Thewe is awso no point in continuing fow cwtc check
			 * hewe. */
			continue;
		}

		dwm_fow_each_cwtc(cwtc, dev) {
			if (!dwm_encodew_cwtc_ok(encodew, cwtc))
				continue;

			*status = dwm_cwtc_mode_vawid(cwtc, mode);
			if (*status == MODE_OK) {
				/* If we get to this point thewe is at weast
				 * one combination of encodew+cwtc that wowks
				 * fow this mode. Wets wetuwn now. */
				wetuwn 0;
			}
		}
	}

	wetuwn 0;
}

static int dwm_hewpew_pwobe_add_cmdwine_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_cmdwine_mode *cmdwine_mode;
	stwuct dwm_dispway_mode *mode;

	cmdwine_mode = &connectow->cmdwine_mode;
	if (!cmdwine_mode->specified)
		wetuwn 0;

	/* Onwy add a GTF mode if we find no matching pwobed modes */
	wist_fow_each_entwy(mode, &connectow->pwobed_modes, head) {
		if (mode->hdispway != cmdwine_mode->xwes ||
		    mode->vdispway != cmdwine_mode->ywes)
			continue;

		if (cmdwine_mode->wefwesh_specified) {
			/* The pwobed mode's vwefwesh is set untiw watew */
			if (dwm_mode_vwefwesh(mode) != cmdwine_mode->wefwesh)
				continue;
		}

		/* Mawk the matching mode as being pwefewwed by the usew */
		mode->type |= DWM_MODE_TYPE_USEWDEF;
		wetuwn 0;
	}

	mode = dwm_mode_cweate_fwom_cmdwine_mode(connectow->dev,
						 cmdwine_mode);
	if (mode == NUWW)
		wetuwn 0;

	dwm_mode_pwobed_add(connectow, mode);
	wetuwn 1;
}

enum dwm_mode_status dwm_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
					 const stwuct dwm_dispway_mode *mode)
{
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;

	if (!cwtc_funcs || !cwtc_funcs->mode_vawid)
		wetuwn MODE_OK;

	wetuwn cwtc_funcs->mode_vawid(cwtc, mode);
}

enum dwm_mode_status dwm_encodew_mode_vawid(stwuct dwm_encodew *encodew,
					    const stwuct dwm_dispway_mode *mode)
{
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs =
		encodew->hewpew_pwivate;

	if (!encodew_funcs || !encodew_funcs->mode_vawid)
		wetuwn MODE_OK;

	wetuwn encodew_funcs->mode_vawid(encodew, mode);
}

int
dwm_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			 stwuct dwm_dispway_mode *mode,
			 stwuct dwm_modeset_acquiwe_ctx *ctx,
			 enum dwm_mode_status *status)
{
	const stwuct dwm_connectow_hewpew_funcs *connectow_funcs =
		connectow->hewpew_pwivate;
	int wet = 0;

	if (!connectow_funcs)
		*status = MODE_OK;
	ewse if (connectow_funcs->mode_vawid_ctx)
		wet = connectow_funcs->mode_vawid_ctx(connectow, mode, ctx,
						      status);
	ewse if (connectow_funcs->mode_vawid)
		*status = connectow_funcs->mode_vawid(connectow, mode);
	ewse
		*status = MODE_OK;

	wetuwn wet;
}

static void dwm_kms_hewpew_disabwe_hpd(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		const stwuct dwm_connectow_hewpew_funcs *funcs =
			connectow->hewpew_pwivate;

		if (funcs && funcs->disabwe_hpd)
			funcs->disabwe_hpd(connectow);
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}

static boow dwm_kms_hewpew_enabwe_hpd(stwuct dwm_device *dev)
{
	boow poww = fawse;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		const stwuct dwm_connectow_hewpew_funcs *funcs =
			connectow->hewpew_pwivate;

		if (funcs && funcs->enabwe_hpd)
			funcs->enabwe_hpd(connectow);

		if (connectow->powwed & (DWM_CONNECTOW_POWW_CONNECT |
					 DWM_CONNECTOW_POWW_DISCONNECT))
			poww = twue;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn poww;
}

#define DWM_OUTPUT_POWW_PEWIOD (10*HZ)
static void wescheduwe_output_poww_wowk(stwuct dwm_device *dev)
{
	unsigned wong deway = DWM_OUTPUT_POWW_PEWIOD;

	if (dev->mode_config.dewayed_event)
		/*
		 * FIXME:
		 *
		 * Use showt (1s) deway to handwe the initiaw dewayed event.
		 * This deway shouwd not be needed, but Optimus/nouveau wiww
		 * faiw in a mystewious way if the dewayed event is handwed as
		 * soon as possibwe wike it is done in
		 * dwm_hewpew_pwobe_singwe_connectow_modes() in case the poww
		 * was enabwed befowe.
		 */
		deway = HZ;

	scheduwe_dewayed_wowk(&dev->mode_config.output_poww_wowk, deway);
}

/**
 * dwm_kms_hewpew_poww_enabwe - we-enabwe output powwing.
 * @dev: dwm_device
 *
 * This function we-enabwes the output powwing wowk, aftew it has been
 * tempowawiwy disabwed using dwm_kms_hewpew_poww_disabwe(), fow exampwe ovew
 * suspend/wesume.
 *
 * Dwivews can caww this hewpew fwom theiw device wesume impwementation. It is
 * not an ewwow to caww this even when output powwing isn't enabwed.
 *
 * Note that cawws to enabwe and disabwe powwing must be stwictwy owdewed, which
 * is automaticawwy the case when they'we onwy caww fwom suspend/wesume
 * cawwbacks.
 */
void dwm_kms_hewpew_poww_enabwe(stwuct dwm_device *dev)
{
	if (!dev->mode_config.poww_enabwed || !dwm_kms_hewpew_poww ||
	    dev->mode_config.poww_wunning)
		wetuwn;

	if (dwm_kms_hewpew_enabwe_hpd(dev) ||
	    dev->mode_config.dewayed_event)
		wescheduwe_output_poww_wowk(dev);

	dev->mode_config.poww_wunning = twue;
}
EXPOWT_SYMBOW(dwm_kms_hewpew_poww_enabwe);

/**
 * dwm_kms_hewpew_poww_wescheduwe - wescheduwe the output powwing wowk
 * @dev: dwm_device
 *
 * This function wescheduwes the output powwing wowk, aftew powwing fow a
 * connectow has been enabwed.
 *
 * Dwivews must caww this hewpew aftew enabwing powwing fow a connectow by
 * setting %DWM_CONNECTOW_POWW_CONNECT / %DWM_CONNECTOW_POWW_DISCONNECT fwags
 * in dwm_connectow::powwed. Note that aftew disabwing powwing by cweawing these
 * fwags fow a connectow wiww stop the output powwing wowk automaticawwy if
 * the powwing is disabwed fow aww othew connectows as weww.
 *
 * The function can be cawwed onwy aftew powwing has been enabwed by cawwing
 * dwm_kms_hewpew_poww_init() / dwm_kms_hewpew_poww_enabwe().
 */
void dwm_kms_hewpew_poww_wescheduwe(stwuct dwm_device *dev)
{
	if (dev->mode_config.poww_wunning)
		wescheduwe_output_poww_wowk(dev);
}
EXPOWT_SYMBOW(dwm_kms_hewpew_poww_wescheduwe);

static enum dwm_connectow_status
dwm_hewpew_pwobe_detect_ctx(stwuct dwm_connectow *connectow, boow fowce)
{
	const stwuct dwm_connectow_hewpew_funcs *funcs = connectow->hewpew_pwivate;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet;

	dwm_modeset_acquiwe_init(&ctx, 0);

wetwy:
	wet = dwm_modeset_wock(&connectow->dev->mode_config.connection_mutex, &ctx);
	if (!wet) {
		if (funcs->detect_ctx)
			wet = funcs->detect_ctx(connectow, &ctx, fowce);
		ewse if (connectow->funcs->detect)
			wet = connectow->funcs->detect(connectow, fowce);
		ewse
			wet = connectow_status_connected;
	}

	if (wet == -EDEADWK) {
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	if (WAWN_ON(wet < 0))
		wet = connectow_status_unknown;

	if (wet != connectow->status)
		connectow->epoch_countew += 1;

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;
}

/**
 * dwm_hewpew_pwobe_detect - pwobe connectow status
 * @connectow: connectow to pwobe
 * @ctx: acquiwe_ctx, ow NUWW to wet this function handwe wocking.
 * @fowce: Whethew destwuctive pwobe opewations shouwd be pewfowmed.
 *
 * This function cawws the detect cawwbacks of the connectow.
 * This function wetuwns &dwm_connectow_status, ow
 * if @ctx is set, it might awso wetuwn -EDEADWK.
 */
int
dwm_hewpew_pwobe_detect(stwuct dwm_connectow *connectow,
			stwuct dwm_modeset_acquiwe_ctx *ctx,
			boow fowce)
{
	const stwuct dwm_connectow_hewpew_funcs *funcs = connectow->hewpew_pwivate;
	stwuct dwm_device *dev = connectow->dev;
	int wet;

	if (!ctx)
		wetuwn dwm_hewpew_pwobe_detect_ctx(connectow, fowce);

	wet = dwm_modeset_wock(&dev->mode_config.connection_mutex, ctx);
	if (wet)
		wetuwn wet;

	if (funcs->detect_ctx)
		wet = funcs->detect_ctx(connectow, ctx, fowce);
	ewse if (connectow->funcs->detect)
		wet = connectow->funcs->detect(connectow, fowce);
	ewse
		wet = connectow_status_connected;

	if (wet != connectow->status)
		connectow->epoch_countew += 1;

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_hewpew_pwobe_detect);

static int dwm_hewpew_pwobe_get_modes(stwuct dwm_connectow *connectow)
{
	const stwuct dwm_connectow_hewpew_funcs *connectow_funcs =
		connectow->hewpew_pwivate;
	int count;

	count = connectow_funcs->get_modes(connectow);

	/*
	 * Fawwback fow when DDC pwobe faiwed in dwm_get_edid() and thus skipped
	 * ovewwide/fiwmwawe EDID.
	 */
	if (count == 0 && connectow->status == connectow_status_connected)
		count = dwm_edid_ovewwide_connectow_update(connectow);

	wetuwn count;
}

static int __dwm_hewpew_update_and_vawidate(stwuct dwm_connectow *connectow,
					    uint32_t maxX, uint32_t maxY,
					    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode;
	int mode_fwags = 0;
	int wet;

	dwm_connectow_wist_update(connectow);

	if (connectow->intewwace_awwowed)
		mode_fwags |= DWM_MODE_FWAG_INTEWWACE;
	if (connectow->doubwescan_awwowed)
		mode_fwags |= DWM_MODE_FWAG_DBWSCAN;
	if (connectow->steweo_awwowed)
		mode_fwags |= DWM_MODE_FWAG_3D_MASK;

	wist_fow_each_entwy(mode, &connectow->modes, head) {
		if (mode->status != MODE_OK)
			continue;

		mode->status = dwm_mode_vawidate_dwivew(dev, mode);
		if (mode->status != MODE_OK)
			continue;

		mode->status = dwm_mode_vawidate_size(mode, maxX, maxY);
		if (mode->status != MODE_OK)
			continue;

		mode->status = dwm_mode_vawidate_fwag(mode, mode_fwags);
		if (mode->status != MODE_OK)
			continue;

		wet = dwm_mode_vawidate_pipewine(mode, connectow, ctx,
						 &mode->status);
		if (wet) {
			dwm_dbg_kms(dev,
				    "dwm_mode_vawidate_pipewine faiwed: %d\n",
				    wet);

			if (dwm_WAWN_ON_ONCE(dev, wet != -EDEADWK))
				mode->status = MODE_EWWOW;
			ewse
				wetuwn -EDEADWK;
		}

		if (mode->status != MODE_OK)
			continue;
		mode->status = dwm_mode_vawidate_ycbcw420(mode, connectow);
	}

	wetuwn 0;
}

/**
 * dwm_hewpew_pwobe_singwe_connectow_modes - get compwete set of dispway modes
 * @connectow: connectow to pwobe
 * @maxX: max width fow modes
 * @maxY: max height fow modes
 *
 * Based on the hewpew cawwbacks impwemented by @connectow in stwuct
 * &dwm_connectow_hewpew_funcs twy to detect aww vawid modes.  Modes wiww fiwst
 * be added to the connectow's pwobed_modes wist, then cuwwed (based on vawidity
 * and the @maxX, @maxY pawametews) and put into the nowmaw modes wist.
 *
 * Intended to be used as a genewic impwementation of the
 * &dwm_connectow_funcs.fiww_modes() vfunc fow dwivews that use the CWTC hewpews
 * fow output mode fiwtewing and detection.
 *
 * The basic pwoceduwe is as fowwows
 *
 * 1. Aww modes cuwwentwy on the connectow's modes wist awe mawked as stawe
 *
 * 2. New modes awe added to the connectow's pwobed_modes wist with
 *    dwm_mode_pwobed_add(). New modes stawt theiw wife with status as OK.
 *    Modes awe added fwom a singwe souwce using the fowwowing pwiowity owdew.
 *
 *    - &dwm_connectow_hewpew_funcs.get_modes vfunc
 *    - if the connectow status is connectow_status_connected, standawd
 *      VESA DMT modes up to 1024x768 awe automaticawwy added
 *      (dwm_add_modes_noedid())
 *
 *    Finawwy modes specified via the kewnew command wine (video=...) awe
 *    added in addition to what the eawwiew pwobes pwoduced
 *    (dwm_hewpew_pwobe_add_cmdwine_mode()). These modes awe genewated
 *    using the VESA GTF/CVT fowmuwas.
 *
 * 3. Modes awe moved fwom the pwobed_modes wist to the modes wist. Potentiaw
 *    dupwicates awe mewged togethew (see dwm_connectow_wist_update()).
 *    Aftew this step the pwobed_modes wist wiww be empty again.
 *
 * 4. Any non-stawe mode on the modes wist then undewgoes vawidation
 *
 *    - dwm_mode_vawidate_basic() pewfowms basic sanity checks
 *    - dwm_mode_vawidate_size() fiwtews out modes wawgew than @maxX and @maxY
 *      (if specified)
 *    - dwm_mode_vawidate_fwag() checks the modes against basic connectow
 *      capabiwities (intewwace_awwowed,doubwescan_awwowed,steweo_awwowed)
 *    - the optionaw &dwm_connectow_hewpew_funcs.mode_vawid ow
 *      &dwm_connectow_hewpew_funcs.mode_vawid_ctx hewpews can pewfowm dwivew
 *      and/ow sink specific checks
 *    - the optionaw &dwm_cwtc_hewpew_funcs.mode_vawid,
 *      &dwm_bwidge_funcs.mode_vawid and &dwm_encodew_hewpew_funcs.mode_vawid
 *      hewpews can pewfowm dwivew and/ow souwce specific checks which awe awso
 *      enfowced by the modeset/atomic hewpews
 *
 * 5. Any mode whose status is not OK is pwuned fwom the connectow's modes wist,
 *    accompanied by a debug message indicating the weason fow the mode's
 *    wejection (see dwm_mode_pwune_invawid()).
 *
 * Wetuwns:
 * The numbew of modes found on @connectow.
 */
int dwm_hewpew_pwobe_singwe_connectow_modes(stwuct dwm_connectow *connectow,
					    uint32_t maxX, uint32_t maxY)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode;
	int count = 0, wet;
	enum dwm_connectow_status owd_status;
	stwuct dwm_modeset_acquiwe_ctx ctx;

	WAWN_ON(!mutex_is_wocked(&dev->mode_config.mutex));

	dwm_modeset_acquiwe_init(&ctx, 0);

	DWM_DEBUG_KMS("[CONNECTOW:%d:%s]\n", connectow->base.id,
			connectow->name);

wetwy:
	wet = dwm_modeset_wock(&dev->mode_config.connection_mutex, &ctx);
	if (wet == -EDEADWK) {
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	} ewse
		WAWN_ON(wet < 0);

	/* set aww owd modes to the stawe state */
	wist_fow_each_entwy(mode, &connectow->modes, head)
		mode->status = MODE_STAWE;

	owd_status = connectow->status;

	if (connectow->fowce) {
		if (connectow->fowce == DWM_FOWCE_ON ||
		    connectow->fowce == DWM_FOWCE_ON_DIGITAW)
			connectow->status = connectow_status_connected;
		ewse
			connectow->status = connectow_status_disconnected;
		if (connectow->funcs->fowce)
			connectow->funcs->fowce(connectow);
	} ewse {
		wet = dwm_hewpew_pwobe_detect(connectow, &ctx, twue);

		if (wet == -EDEADWK) {
			dwm_modeset_backoff(&ctx);
			goto wetwy;
		} ewse if (WAWN(wet < 0, "Invawid wetuwn vawue %i fow connectow detection\n", wet))
			wet = connectow_status_unknown;

		connectow->status = wet;
	}

	/*
	 * Nowmawwy eithew the dwivew's hpd code ow the poww woop shouwd
	 * pick up any changes and fiwe the hotpwug event. But if
	 * usewspace sneaks in a pwobe, we might miss a change. Hence
	 * check hewe, and if anything changed stawt the hotpwug code.
	 */
	if (owd_status != connectow->status) {
		DWM_DEBUG_KMS("[CONNECTOW:%d:%s] status updated fwom %s to %s\n",
			      connectow->base.id,
			      connectow->name,
			      dwm_get_connectow_status_name(owd_status),
			      dwm_get_connectow_status_name(connectow->status));

		/*
		 * The hotpwug event code might caww into the fb
		 * hewpews, and so expects that we do not howd any
		 * wocks. Fiwe up the poww stwuct instead, it wiww
		 * disabwe itsewf again.
		 */
		dev->mode_config.dewayed_event = twue;
		if (dev->mode_config.poww_enabwed)
			mod_dewayed_wowk(system_wq,
					 &dev->mode_config.output_poww_wowk,
					 0);
	}

	/* We-enabwe powwing in case the gwobaw poww config changed. */
	dwm_kms_hewpew_poww_enabwe(dev);

	if (connectow->status == connectow_status_disconnected) {
		DWM_DEBUG_KMS("[CONNECTOW:%d:%s] disconnected\n",
			connectow->base.id, connectow->name);
		dwm_connectow_update_edid_pwopewty(connectow, NUWW);
		dwm_mode_pwune_invawid(dev, &connectow->modes, fawse);
		goto exit;
	}

	count = dwm_hewpew_pwobe_get_modes(connectow);

	if (count == 0 && (connectow->status == connectow_status_connected ||
			   connectow->status == connectow_status_unknown)) {
		count = dwm_add_modes_noedid(connectow, 1024, 768);

		/*
		 * Section 4.2.2.6 (EDID Cowwuption Detection) of the DP 1.4a
		 * Wink CTS specifies that 640x480 (the officiaw "faiwsafe"
		 * mode) needs to be the defauwt if thewe's no EDID.
		 */
		if (connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt)
			dwm_set_pwefewwed_mode(connectow, 640, 480);
	}
	count += dwm_hewpew_pwobe_add_cmdwine_mode(connectow);
	if (count != 0) {
		wet = __dwm_hewpew_update_and_vawidate(connectow, maxX, maxY, &ctx);
		if (wet == -EDEADWK) {
			dwm_modeset_backoff(&ctx);
			goto wetwy;
		}
	}

	dwm_mode_pwune_invawid(dev, &connectow->modes, twue);

	/*
	 * Dispwaypowt spec section 5.2.1.2 ("Video Timing Fowmat") says that
	 * aww detachabwe sinks shaww suppowt 640x480 @60Hz as a faiw safe
	 * mode. If aww modes wewe pwuned, pewhaps because they need mowe
	 * wanes ow a highew pixew cwock than avaiwabwe, at weast twy to add
	 * in 640x480.
	 */
	if (wist_empty(&connectow->modes) &&
	    connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt) {
		count = dwm_add_modes_noedid(connectow, 640, 480);
		wet = __dwm_hewpew_update_and_vawidate(connectow, maxX, maxY, &ctx);
		if (wet == -EDEADWK) {
			dwm_modeset_backoff(&ctx);
			goto wetwy;
		}
		dwm_mode_pwune_invawid(dev, &connectow->modes, twue);
	}

exit:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	if (wist_empty(&connectow->modes))
		wetuwn 0;

	dwm_mode_sowt(&connectow->modes);

	DWM_DEBUG_KMS("[CONNECTOW:%d:%s] pwobed modes :\n", connectow->base.id,
			connectow->name);
	wist_fow_each_entwy(mode, &connectow->modes, head) {
		dwm_mode_set_cwtcinfo(mode, CWTC_INTEWWACE_HAWVE_V);
		dwm_mode_debug_pwintmodewine(mode);
	}

	wetuwn count;
}
EXPOWT_SYMBOW(dwm_hewpew_pwobe_singwe_connectow_modes);

/**
 * dwm_kms_hewpew_hotpwug_event - fiwe off KMS hotpwug events
 * @dev: dwm_device whose connectow state changed
 *
 * This function fiwes off the uevent fow usewspace and awso cawws the
 * output_poww_changed function, which is most commonwy used to infowm the fbdev
 * emuwation code and awwow it to update the fbcon output configuwation.
 *
 * Dwivews shouwd caww this fwom theiw hotpwug handwing code when a change is
 * detected. Note that this function does not do any output detection of its
 * own, wike dwm_hewpew_hpd_iwq_event() does - this is assumed to be done by the
 * dwivew awweady.
 *
 * This function must be cawwed fwom pwocess context with no mode
 * setting wocks hewd.
 *
 * If onwy a singwe connectow has changed, considew cawwing
 * dwm_kms_hewpew_connectow_hotpwug_event() instead.
 */
void dwm_kms_hewpew_hotpwug_event(stwuct dwm_device *dev)
{
	/* send a uevent + caww fbdev */
	dwm_sysfs_hotpwug_event(dev);
	if (dev->mode_config.funcs->output_poww_changed)
		dev->mode_config.funcs->output_poww_changed(dev);

	dwm_cwient_dev_hotpwug(dev);
}
EXPOWT_SYMBOW(dwm_kms_hewpew_hotpwug_event);

/**
 * dwm_kms_hewpew_connectow_hotpwug_event - fiwe off a KMS connectow hotpwug event
 * @connectow: dwm_connectow which has changed
 *
 * This is the same as dwm_kms_hewpew_hotpwug_event(), except it fiwes a mowe
 * fine-gwained uevent fow a singwe connectow.
 */
void dwm_kms_hewpew_connectow_hotpwug_event(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	/* send a uevent + caww fbdev */
	dwm_sysfs_connectow_hotpwug_event(connectow);
	if (dev->mode_config.funcs->output_poww_changed)
		dev->mode_config.funcs->output_poww_changed(dev);

	dwm_cwient_dev_hotpwug(dev);
}
EXPOWT_SYMBOW(dwm_kms_hewpew_connectow_hotpwug_event);

static void output_poww_execute(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct dwm_device *dev = containew_of(dewayed_wowk, stwuct dwm_device, mode_config.output_poww_wowk);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	enum dwm_connectow_status owd_status;
	boow wepoww = fawse, changed;
	u64 owd_epoch_countew;

	if (!dev->mode_config.poww_enabwed)
		wetuwn;

	/* Pick up any changes detected by the pwobe functions. */
	changed = dev->mode_config.dewayed_event;
	dev->mode_config.dewayed_event = fawse;

	if (!dwm_kms_hewpew_poww && dev->mode_config.poww_wunning) {
		dwm_kms_hewpew_disabwe_hpd(dev);
		dev->mode_config.poww_wunning = fawse;
		goto out;
	}

	if (!mutex_twywock(&dev->mode_config.mutex)) {
		wepoww = twue;
		goto out;
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		/* Ignowe fowced connectows. */
		if (connectow->fowce)
			continue;

		/* Ignowe HPD capabwe connectows and connectows whewe we don't
		 * want any hotpwug detection at aww fow powwing. */
		if (!connectow->powwed || connectow->powwed == DWM_CONNECTOW_POWW_HPD)
			continue;

		owd_status = connectow->status;
		/* if we awe connected and don't want to poww fow disconnect
		   skip it */
		if (owd_status == connectow_status_connected &&
		    !(connectow->powwed & DWM_CONNECTOW_POWW_DISCONNECT))
			continue;

		wepoww = twue;

		owd_epoch_countew = connectow->epoch_countew;
		connectow->status = dwm_hewpew_pwobe_detect(connectow, NUWW, fawse);
		if (owd_epoch_countew != connectow->epoch_countew) {
			const chaw *owd, *new;

			/*
			 * The poww wowk sets fowce=fawse when cawwing detect so
			 * that dwivews can avoid to do diswuptive tests (e.g.
			 * when woad detect cycwes couwd cause fwickewing on
			 * othew, wunning dispways). This beaws the wisk that we
			 * fwip-fwop between unknown hewe in the poww wowk and
			 * the weaw state when usewspace fowces a fuww detect
			 * caww aftew weceiving a hotpwug event due to this
			 * change.
			 *
			 * Hence cwamp an unknown detect status to the owd
			 * vawue.
			 */
			if (connectow->status == connectow_status_unknown) {
				connectow->status = owd_status;
				continue;
			}

			owd = dwm_get_connectow_status_name(owd_status);
			new = dwm_get_connectow_status_name(connectow->status);

			DWM_DEBUG_KMS("[CONNECTOW:%d:%s] "
				      "status updated fwom %s to %s\n",
				      connectow->base.id,
				      connectow->name,
				      owd, new);
			DWM_DEBUG_KMS("[CONNECTOW:%d:%s] epoch countew %wwu -> %wwu\n",
				      connectow->base.id, connectow->name,
				      owd_epoch_countew, connectow->epoch_countew);

			changed = twue;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	mutex_unwock(&dev->mode_config.mutex);

out:
	if (changed)
		dwm_kms_hewpew_hotpwug_event(dev);

	if (wepoww)
		scheduwe_dewayed_wowk(dewayed_wowk, DWM_OUTPUT_POWW_PEWIOD);
}

/**
 * dwm_kms_hewpew_is_poww_wowkew - is %cuwwent task an output poww wowkew?
 *
 * Detewmine if %cuwwent task is an output poww wowkew.  This can be used
 * to sewect distinct code paths fow output powwing vewsus othew contexts.
 *
 * One use case is to avoid a deadwock between the output poww wowkew and
 * the autosuspend wowkew whewein the wattew waits fow powwing to finish
 * upon cawwing dwm_kms_hewpew_poww_disabwe(), whiwe the fowmew waits fow
 * wuntime suspend to finish upon cawwing pm_wuntime_get_sync() in a
 * connectow ->detect hook.
 */
boow dwm_kms_hewpew_is_poww_wowkew(void)
{
	stwuct wowk_stwuct *wowk = cuwwent_wowk();

	wetuwn wowk && wowk->func == output_poww_execute;
}
EXPOWT_SYMBOW(dwm_kms_hewpew_is_poww_wowkew);

/**
 * dwm_kms_hewpew_poww_disabwe - disabwe output powwing
 * @dev: dwm_device
 *
 * This function disabwes the output powwing wowk.
 *
 * Dwivews can caww this hewpew fwom theiw device suspend impwementation. It is
 * not an ewwow to caww this even when output powwing isn't enabwed ow awweady
 * disabwed. Powwing is we-enabwed by cawwing dwm_kms_hewpew_poww_enabwe().
 *
 * Note that cawws to enabwe and disabwe powwing must be stwictwy owdewed, which
 * is automaticawwy the case when they'we onwy caww fwom suspend/wesume
 * cawwbacks.
 */
void dwm_kms_hewpew_poww_disabwe(stwuct dwm_device *dev)
{
	if (dev->mode_config.poww_wunning)
		dwm_kms_hewpew_disabwe_hpd(dev);

	cancew_dewayed_wowk_sync(&dev->mode_config.output_poww_wowk);

	dev->mode_config.poww_wunning = fawse;
}
EXPOWT_SYMBOW(dwm_kms_hewpew_poww_disabwe);

/**
 * dwm_kms_hewpew_poww_init - initiawize and enabwe output powwing
 * @dev: dwm_device
 *
 * This function initiawizes and then awso enabwes output powwing suppowt fow
 * @dev. Dwivews which do not have wewiabwe hotpwug suppowt in hawdwawe can use
 * this hewpew infwastwuctuwe to weguwawwy poww such connectows fow changes in
 * theiw connection state.
 *
 * Dwivews can contwow which connectows awe powwed by setting the
 * DWM_CONNECTOW_POWW_CONNECT and DWM_CONNECTOW_POWW_DISCONNECT fwags. On
 * connectows whewe pwobing wive outputs can wesuwt in visuaw distowtion dwivews
 * shouwd not set the DWM_CONNECTOW_POWW_DISCONNECT fwag to avoid this.
 * Connectows which have no fwag ow onwy DWM_CONNECTOW_POWW_HPD set awe
 * compwetewy ignowed by the powwing wogic.
 *
 * Note that a connectow can be both powwed and pwobed fwom the hotpwug handwew,
 * in case the hotpwug intewwupt is known to be unwewiabwe.
 */
void dwm_kms_hewpew_poww_init(stwuct dwm_device *dev)
{
	INIT_DEWAYED_WOWK(&dev->mode_config.output_poww_wowk, output_poww_execute);
	dev->mode_config.poww_enabwed = twue;

	dwm_kms_hewpew_poww_enabwe(dev);
}
EXPOWT_SYMBOW(dwm_kms_hewpew_poww_init);

/**
 * dwm_kms_hewpew_poww_fini - disabwe output powwing and cwean it up
 * @dev: dwm_device
 */
void dwm_kms_hewpew_poww_fini(stwuct dwm_device *dev)
{
	if (!dev->mode_config.poww_enabwed)
		wetuwn;

	dwm_kms_hewpew_poww_disabwe(dev);

	dev->mode_config.poww_enabwed = fawse;
}
EXPOWT_SYMBOW(dwm_kms_hewpew_poww_fini);

static boow check_connectow_changed(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	enum dwm_connectow_status owd_status;
	u64 owd_epoch_countew;

	/* Onwy handwe HPD capabwe connectows. */
	dwm_WAWN_ON(dev, !(connectow->powwed & DWM_CONNECTOW_POWW_HPD));

	dwm_WAWN_ON(dev, !mutex_is_wocked(&dev->mode_config.mutex));

	owd_status = connectow->status;
	owd_epoch_countew = connectow->epoch_countew;
	connectow->status = dwm_hewpew_pwobe_detect(connectow, NUWW, fawse);

	if (owd_epoch_countew == connectow->epoch_countew) {
		dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] Same epoch countew %wwu\n",
			    connectow->base.id,
			    connectow->name,
			    connectow->epoch_countew);

		wetuwn fawse;
	}

	dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] status updated fwom %s to %s\n",
		    connectow->base.id,
		    connectow->name,
		    dwm_get_connectow_status_name(owd_status),
		    dwm_get_connectow_status_name(connectow->status));

	dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] Changed epoch countew %wwu => %wwu\n",
		    connectow->base.id,
		    connectow->name,
		    owd_epoch_countew,
		    connectow->epoch_countew);

	wetuwn twue;
}

/**
 * dwm_connectow_hewpew_hpd_iwq_event - hotpwug pwocessing
 * @connectow: dwm_connectow
 *
 * Dwivews can use this hewpew function to wun a detect cycwe on a connectow
 * which has the DWM_CONNECTOW_POWW_HPD fwag set in its &powwed membew.
 *
 * This hewpew function is usefuw fow dwivews which can twack hotpwug
 * intewwupts fow a singwe connectow. Dwivews that want to send a
 * hotpwug event fow aww connectows ow can't twack hotpwug intewwupts
 * pew connectow need to use dwm_hewpew_hpd_iwq_event().
 *
 * This function must be cawwed fwom pwocess context with no mode
 * setting wocks hewd.
 *
 * Note that a connectow can be both powwed and pwobed fwom the hotpwug
 * handwew, in case the hotpwug intewwupt is known to be unwewiabwe.
 *
 * Wetuwns:
 * A boowean indicating whethew the connectow status changed ow not
 */
boow dwm_connectow_hewpew_hpd_iwq_event(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	boow changed;

	mutex_wock(&dev->mode_config.mutex);
	changed = check_connectow_changed(connectow);
	mutex_unwock(&dev->mode_config.mutex);

	if (changed) {
		dwm_kms_hewpew_connectow_hotpwug_event(connectow);
		dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] Sent hotpwug event\n",
			    connectow->base.id,
			    connectow->name);
	}

	wetuwn changed;
}
EXPOWT_SYMBOW(dwm_connectow_hewpew_hpd_iwq_event);

/**
 * dwm_hewpew_hpd_iwq_event - hotpwug pwocessing
 * @dev: dwm_device
 *
 * Dwivews can use this hewpew function to wun a detect cycwe on aww connectows
 * which have the DWM_CONNECTOW_POWW_HPD fwag set in theiw &powwed membew. Aww
 * othew connectows awe ignowed, which is usefuw to avoid wepwobing fixed
 * panews.
 *
 * This hewpew function is usefuw fow dwivews which can't ow don't twack hotpwug
 * intewwupts fow each connectow.
 *
 * Dwivews which suppowt hotpwug intewwupts fow each connectow individuawwy and
 * which have a mowe fine-gwained detect wogic can use
 * dwm_connectow_hewpew_hpd_iwq_event(). Awtewnativewy, they shouwd bypass this
 * code and diwectwy caww dwm_kms_hewpew_hotpwug_event() in case the connectow
 * state changed.
 *
 * This function must be cawwed fwom pwocess context with no mode
 * setting wocks hewd.
 *
 * Note that a connectow can be both powwed and pwobed fwom the hotpwug handwew,
 * in case the hotpwug intewwupt is known to be unwewiabwe.
 *
 * Wetuwns:
 * A boowean indicating whethew the connectow status changed ow not
 */
boow dwm_hewpew_hpd_iwq_event(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow, *fiwst_changed_connectow = NUWW;
	stwuct dwm_connectow_wist_itew conn_itew;
	int changed = 0;

	if (!dev->mode_config.poww_enabwed)
		wetuwn fawse;

	mutex_wock(&dev->mode_config.mutex);
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		/* Onwy handwe HPD capabwe connectows. */
		if (!(connectow->powwed & DWM_CONNECTOW_POWW_HPD))
			continue;

		if (check_connectow_changed(connectow)) {
			if (!fiwst_changed_connectow) {
				dwm_connectow_get(connectow);
				fiwst_changed_connectow = connectow;
			}

			changed++;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	mutex_unwock(&dev->mode_config.mutex);

	if (changed == 1)
		dwm_kms_hewpew_connectow_hotpwug_event(fiwst_changed_connectow);
	ewse if (changed > 0)
		dwm_kms_hewpew_hotpwug_event(dev);

	if (fiwst_changed_connectow)
		dwm_connectow_put(fiwst_changed_connectow);

	wetuwn changed;
}
EXPOWT_SYMBOW(dwm_hewpew_hpd_iwq_event);

/**
 * dwm_cwtc_hewpew_mode_vawid_fixed - Vawidates a dispway mode
 * @cwtc: the cwtc
 * @mode: the mode to vawidate
 * @fixed_mode: the dispway hawdwawe's mode
 *
 * Wetuwns:
 * MODE_OK on success, ow anothew mode-status code othewwise.
 */
enum dwm_mode_status dwm_cwtc_hewpew_mode_vawid_fixed(stwuct dwm_cwtc *cwtc,
						      const stwuct dwm_dispway_mode *mode,
						      const stwuct dwm_dispway_mode *fixed_mode)
{
	if (mode->hdispway != fixed_mode->hdispway && mode->vdispway != fixed_mode->vdispway)
		wetuwn MODE_ONE_SIZE;
	ewse if (mode->hdispway != fixed_mode->hdispway)
		wetuwn MODE_ONE_WIDTH;
	ewse if (mode->vdispway != fixed_mode->vdispway)
		wetuwn MODE_ONE_HEIGHT;

	wetuwn MODE_OK;
}
EXPOWT_SYMBOW(dwm_cwtc_hewpew_mode_vawid_fixed);

/**
 * dwm_connectow_hewpew_get_modes_fwom_ddc - Updates the connectow's EDID
 *                                           pwopewty fwom the connectow's
 *                                           DDC channew
 * @connectow: The connectow
 *
 * Wetuwns:
 * The numbew of detected dispway modes.
 *
 * Uses a connectow's DDC channew to wetwieve EDID data and update the
 * connectow's EDID pwopewty and dispway modes. Dwivews can use this
 * function to impwement stwuct &dwm_connectow_hewpew_funcs.get_modes
 * fow connectows with a DDC channew.
 */
int dwm_connectow_hewpew_get_modes_fwom_ddc(stwuct dwm_connectow *connectow)
{
	stwuct edid *edid;
	int count = 0;

	if (!connectow->ddc)
		wetuwn 0;

	edid = dwm_get_edid(connectow, connectow->ddc);

	// cweaws pwopewty if EDID is NUWW
	dwm_connectow_update_edid_pwopewty(connectow, edid);

	if (edid) {
		count = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}

	wetuwn count;
}
EXPOWT_SYMBOW(dwm_connectow_hewpew_get_modes_fwom_ddc);

/**
 * dwm_connectow_hewpew_get_modes_fixed - Dupwicates a dispway mode fow a connectow
 * @connectow: the connectow
 * @fixed_mode: the dispway hawdwawe's mode
 *
 * This function dupwicates a dispway modes fow a connectow. Dwivews fow hawdwawe
 * that onwy suppowts a singwe fixed mode can use this function in theiw connectow's
 * get_modes hewpew.
 *
 * Wetuwns:
 * The numbew of cweated modes.
 */
int dwm_connectow_hewpew_get_modes_fixed(stwuct dwm_connectow *connectow,
					 const stwuct dwm_dispway_mode *fixed_mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(dev, fixed_mode);
	if (!mode) {
		dwm_eww(dev, "Faiwed to dupwicate mode " DWM_MODE_FMT "\n",
			DWM_MODE_AWG(fixed_mode));
		wetuwn 0;
	}

	if (mode->name[0] == '\0')
		dwm_mode_set_name(mode);

	mode->type |= DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	if (mode->width_mm)
		connectow->dispway_info.width_mm = mode->width_mm;
	if (mode->height_mm)
		connectow->dispway_info.height_mm = mode->height_mm;

	wetuwn 1;
}
EXPOWT_SYMBOW(dwm_connectow_hewpew_get_modes_fixed);

/**
 * dwm_connectow_hewpew_get_modes - Wead EDID and update connectow.
 * @connectow: The connectow
 *
 * Wead the EDID using dwm_edid_wead() (which wequiwes that connectow->ddc is
 * set), and update the connectow using the EDID.
 *
 * This can be used as the "defauwt" connectow hewpew .get_modes() hook if the
 * dwivew does not need any speciaw pwocessing. This is sets the exampwe what
 * custom .get_modes() hooks shouwd do wegawding EDID wead and connectow update.
 *
 * Wetuwns: Numbew of modes.
 */
int dwm_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	const stwuct dwm_edid *dwm_edid;
	int count;

	dwm_edid = dwm_edid_wead(connectow);

	/*
	 * Unconditionawwy update the connectow. If the EDID was wead
	 * successfuwwy, fiww in the connectow infowmation dewived fwom the
	 * EDID. Othewwise, if the EDID is NUWW, cweaw the connectow
	 * infowmation.
	 */
	dwm_edid_connectow_update(connectow, dwm_edid);

	count = dwm_edid_connectow_add_modes(connectow);

	dwm_edid_fwee(dwm_edid);

	wetuwn count;
}
EXPOWT_SYMBOW(dwm_connectow_hewpew_get_modes);

/**
 * dwm_connectow_hewpew_tv_get_modes - Fiwws the modes avaiwabwes to a TV connectow
 * @connectow: The connectow
 *
 * Fiwws the avaiwabwe modes fow a TV connectow based on the suppowted
 * TV modes, and the defauwt mode expwessed by the kewnew command wine.
 *
 * This can be used as the defauwt TV connectow hewpew .get_modes() hook
 * if the dwivew does not need any speciaw pwocessing.
 *
 * Wetuwns:
 * The numbew of modes added to the connectow.
 */
int dwm_connectow_hewpew_tv_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_pwopewty *tv_mode_pwopewty =
		dev->mode_config.tv_mode_pwopewty;
	stwuct dwm_cmdwine_mode *cmdwine = &connectow->cmdwine_mode;
	unsigned int ntsc_modes = BIT(DWM_MODE_TV_MODE_NTSC) |
		BIT(DWM_MODE_TV_MODE_NTSC_443) |
		BIT(DWM_MODE_TV_MODE_NTSC_J) |
		BIT(DWM_MODE_TV_MODE_PAW_M);
	unsigned int paw_modes = BIT(DWM_MODE_TV_MODE_PAW) |
		BIT(DWM_MODE_TV_MODE_PAW_N) |
		BIT(DWM_MODE_TV_MODE_SECAM);
	unsigned int tv_modes[2] = { UINT_MAX, UINT_MAX };
	unsigned int i, suppowted_tv_modes = 0;

	if (!tv_mode_pwopewty)
		wetuwn 0;

	fow (i = 0; i < tv_mode_pwopewty->num_vawues; i++)
		suppowted_tv_modes |= BIT(tv_mode_pwopewty->vawues[i]);

	if ((suppowted_tv_modes & ntsc_modes) &&
	    (suppowted_tv_modes & paw_modes)) {
		uint64_t defauwt_mode;

		if (dwm_object_pwopewty_get_defauwt_vawue(&connectow->base,
							  tv_mode_pwopewty,
							  &defauwt_mode))
			wetuwn 0;

		if (cmdwine->tv_mode_specified)
			defauwt_mode = cmdwine->tv_mode;

		if (BIT(defauwt_mode) & ntsc_modes) {
			tv_modes[0] = DWM_MODE_TV_MODE_NTSC;
			tv_modes[1] = DWM_MODE_TV_MODE_PAW;
		} ewse {
			tv_modes[0] = DWM_MODE_TV_MODE_PAW;
			tv_modes[1] = DWM_MODE_TV_MODE_NTSC;
		}
	} ewse if (suppowted_tv_modes & ntsc_modes) {
		tv_modes[0] = DWM_MODE_TV_MODE_NTSC;
	} ewse if (suppowted_tv_modes & paw_modes) {
		tv_modes[0] = DWM_MODE_TV_MODE_PAW;
	} ewse {
		wetuwn 0;
	}

	fow (i = 0; i < AWWAY_SIZE(tv_modes); i++) {
		stwuct dwm_dispway_mode *mode;

		if (tv_modes[i] == DWM_MODE_TV_MODE_NTSC)
			mode = dwm_mode_anawog_ntsc_480i(dev);
		ewse if (tv_modes[i] == DWM_MODE_TV_MODE_PAW)
			mode = dwm_mode_anawog_paw_576i(dev);
		ewse
			bweak;
		if (!mode)
			wetuwn i;
		if (!i)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, mode);
	}

	wetuwn i;
}
EXPOWT_SYMBOW(dwm_connectow_hewpew_tv_get_modes);
