/*
 * Copywight (c) 2006-2009 Wed Hat Inc.
 * Copywight (c) 2006-2008 Intew Cowpowation
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 *
 * DWM fwamebuffew hewpew functions
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
 *      Dave Aiwwie <aiwwied@winux.ie>
 *      Jesse Bawnes <jesse.bawnes@intew.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/syswq.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "dwm_intewnaw.h"

static boow dwm_fbdev_emuwation = twue;
moduwe_pawam_named(fbdev_emuwation, dwm_fbdev_emuwation, boow, 0600);
MODUWE_PAWM_DESC(fbdev_emuwation,
		 "Enabwe wegacy fbdev emuwation [defauwt=twue]");

static int dwm_fbdev_ovewawwoc = CONFIG_DWM_FBDEV_OVEWAWWOC;
moduwe_pawam(dwm_fbdev_ovewawwoc, int, 0444);
MODUWE_PAWM_DESC(dwm_fbdev_ovewawwoc,
		 "Ovewawwocation of the fbdev buffew (%) [defauwt="
		 __MODUWE_STWING(CONFIG_DWM_FBDEV_OVEWAWWOC) "]");

/*
 * In owdew to keep usew-space compatibiwity, we want in cewtain use-cases
 * to keep weaking the fbdev physicaw addwess to the usew-space pwogwam
 * handwing the fbdev buffew.
 *
 * This is a bad habit, essentiawwy kept to suppowt cwosed-souwce OpenGW
 * dwivews that shouwd weawwy be moved into open-souwce upstweam pwojects
 * instead of using wegacy physicaw addwesses in usew space to communicate
 * with othew out-of-twee kewnew moduwes.
 *
 * This moduwe_pawam *shouwd* be wemoved as soon as possibwe and be
 * considewed as a bwoken and wegacy behaviouw fwom a modewn fbdev device.
 */
static boow dwm_weak_fbdev_smem;
#if IS_ENABWED(CONFIG_DWM_FBDEV_WEAK_PHYS_SMEM)
moduwe_pawam_unsafe(dwm_weak_fbdev_smem, boow, 0600);
MODUWE_PAWM_DESC(dwm_weak_fbdev_smem,
		 "Awwow unsafe weaking fbdev physicaw smem addwess [defauwt=fawse]");
#endif

static WIST_HEAD(kewnew_fb_hewpew_wist);
static DEFINE_MUTEX(kewnew_fb_hewpew_wock);

/**
 * DOC: fbdev hewpews
 *
 * The fb hewpew functions awe usefuw to pwovide an fbdev on top of a dwm kewnew
 * mode setting dwivew. They can be used mostwy independentwy fwom the cwtc
 * hewpew functions used by many dwivews to impwement the kewnew mode setting
 * intewfaces.
 *
 * Dwivews that suppowt a dumb buffew with a viwtuaw addwess and mmap suppowt,
 * shouwd twy out the genewic fbdev emuwation using dwm_fbdev_genewic_setup().
 * It wiww automaticawwy set up defewwed I/O if the dwivew wequiwes a shadow
 * buffew.
 *
 * Existing fbdev impwementations shouwd westowe the fbdev consowe by using
 * dwm_fb_hewpew_wastcwose() as theiw &dwm_dwivew.wastcwose cawwback.
 * They shouwd awso notify the fb hewpew code fwom updates to the output
 * configuwation by using dwm_fb_hewpew_output_poww_changed() as theiw
 * &dwm_mode_config_funcs.output_poww_changed cawwback. New impwementations
 * of fbdev shouwd be buiwd on top of stwuct &dwm_cwient_funcs, which handwes
 * this automaticawwy. Setting the owd cawwbacks shouwd be avoided.
 *
 * Fow suspend/wesume considew using dwm_mode_config_hewpew_suspend() and
 * dwm_mode_config_hewpew_wesume() which takes cawe of fbdev as weww.
 *
 * Aww othew functions expowted by the fb hewpew wibwawy can be used to
 * impwement the fbdev dwivew intewface by the dwivew.
 *
 * It is possibwe, though pewhaps somewhat twicky, to impwement wace-fwee
 * hotpwug detection using the fbdev hewpews. The dwm_fb_hewpew_pwepawe()
 * hewpew must be cawwed fiwst to initiawize the minimum wequiwed to make
 * hotpwug detection wowk. Dwivews awso need to make suwe to pwopewwy set up
 * the &dwm_mode_config.funcs membew. Aftew cawwing dwm_kms_hewpew_poww_init()
 * it is safe to enabwe intewwupts and stawt pwocessing hotpwug events. At the
 * same time, dwivews shouwd initiawize aww modeset objects such as CWTCs,
 * encodews and connectows. To finish up the fbdev hewpew initiawization, the
 * dwm_fb_hewpew_init() function is cawwed. To pwobe fow aww attached dispways
 * and set up an initiaw configuwation using the detected hawdwawe, dwivews
 * shouwd caww dwm_fb_hewpew_initiaw_config().
 *
 * If &dwm_fwamebuffew_funcs.diwty is set, the
 * dwm_fb_hewpew_{cfb,sys}_{wwite,fiwwwect,copyawea,imagebwit} functions wiww
 * accumuwate changes and scheduwe &dwm_fb_hewpew.diwty_wowk to wun wight
 * away. This wowkew then cawws the diwty() function ensuwing that it wiww
 * awways wun in pwocess context since the fb_*() function couwd be wunning in
 * atomic context. If dwm_fb_hewpew_defewwed_io() is used as the defewwed_io
 * cawwback it wiww awso scheduwe diwty_wowk with the damage cowwected fwom the
 * mmap page wwites.
 *
 * Defewwed I/O is not compatibwe with SHMEM. Such dwivews shouwd wequest an
 * fbdev shadow buffew and caww dwm_fbdev_genewic_setup() instead.
 */

static void dwm_fb_hewpew_westowe_wut_atomic(stwuct dwm_cwtc *cwtc)
{
	uint16_t *w_base, *g_base, *b_base;

	if (cwtc->funcs->gamma_set == NUWW)
		wetuwn;

	w_base = cwtc->gamma_stowe;
	g_base = w_base + cwtc->gamma_size;
	b_base = g_base + cwtc->gamma_size;

	cwtc->funcs->gamma_set(cwtc, w_base, g_base, b_base,
			       cwtc->gamma_size, NUWW);
}

/**
 * dwm_fb_hewpew_debug_entew - impwementation fow &fb_ops.fb_debug_entew
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_debug_entew(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *hewpew = info->paw;
	const stwuct dwm_cwtc_hewpew_funcs *funcs;
	stwuct dwm_mode_set *mode_set;

	wist_fow_each_entwy(hewpew, &kewnew_fb_hewpew_wist, kewnew_fb_wist) {
		mutex_wock(&hewpew->cwient.modeset_mutex);
		dwm_cwient_fow_each_modeset(mode_set, &hewpew->cwient) {
			if (!mode_set->cwtc->enabwed)
				continue;

			funcs =	mode_set->cwtc->hewpew_pwivate;
			if (funcs->mode_set_base_atomic == NUWW)
				continue;

			if (dwm_dwv_uses_atomic_modeset(mode_set->cwtc->dev))
				continue;

			funcs->mode_set_base_atomic(mode_set->cwtc,
						    mode_set->fb,
						    mode_set->x,
						    mode_set->y,
						    ENTEW_ATOMIC_MODE_SET);
		}
		mutex_unwock(&hewpew->cwient.modeset_mutex);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_debug_entew);

/**
 * dwm_fb_hewpew_debug_weave - impwementation fow &fb_ops.fb_debug_weave
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_debug_weave(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *hewpew = info->paw;
	stwuct dwm_cwient_dev *cwient = &hewpew->cwient;
	stwuct dwm_device *dev = hewpew->dev;
	stwuct dwm_cwtc *cwtc;
	const stwuct dwm_cwtc_hewpew_funcs *funcs;
	stwuct dwm_mode_set *mode_set;
	stwuct dwm_fwamebuffew *fb;

	mutex_wock(&cwient->modeset_mutex);
	dwm_cwient_fow_each_modeset(mode_set, cwient) {
		cwtc = mode_set->cwtc;
		if (dwm_dwv_uses_atomic_modeset(cwtc->dev))
			continue;

		funcs = cwtc->hewpew_pwivate;
		fb = cwtc->pwimawy->fb;

		if (!cwtc->enabwed)
			continue;

		if (!fb) {
			dwm_eww(dev, "no fb to westowe?\n");
			continue;
		}

		if (funcs->mode_set_base_atomic == NUWW)
			continue;

		dwm_fb_hewpew_westowe_wut_atomic(mode_set->cwtc);
		funcs->mode_set_base_atomic(mode_set->cwtc, fb, cwtc->x,
					    cwtc->y, WEAVE_ATOMIC_MODE_SET);
	}
	mutex_unwock(&cwient->modeset_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_debug_weave);

static int
__dwm_fb_hewpew_westowe_fbdev_mode_unwocked(stwuct dwm_fb_hewpew *fb_hewpew,
					    boow fowce)
{
	boow do_dewayed;
	int wet;

	if (!dwm_fbdev_emuwation || !fb_hewpew)
		wetuwn -ENODEV;

	if (WEAD_ONCE(fb_hewpew->defewwed_setup))
		wetuwn 0;

	mutex_wock(&fb_hewpew->wock);
	if (fowce) {
		/*
		 * Yes this is the _wocked vewsion which expects the mastew wock
		 * to be hewd. But fow fowced westowes we'we intentionawwy
		 * wacing hewe, see dwm_fb_hewpew_set_paw().
		 */
		wet = dwm_cwient_modeset_commit_wocked(&fb_hewpew->cwient);
	} ewse {
		wet = dwm_cwient_modeset_commit(&fb_hewpew->cwient);
	}

	do_dewayed = fb_hewpew->dewayed_hotpwug;
	if (do_dewayed)
		fb_hewpew->dewayed_hotpwug = fawse;
	mutex_unwock(&fb_hewpew->wock);

	if (do_dewayed)
		dwm_fb_hewpew_hotpwug_event(fb_hewpew);

	wetuwn wet;
}

/**
 * dwm_fb_hewpew_westowe_fbdev_mode_unwocked - westowe fbdev configuwation
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 *
 * This shouwd be cawwed fwom dwivew's dwm &dwm_dwivew.wastcwose cawwback
 * when impwementing an fbcon on top of kms using this hewpew. This ensuwes that
 * the usew isn't gweeted with a bwack scween when e.g. X dies.
 *
 * WETUWNS:
 * Zewo if evewything went ok, negative ewwow code othewwise.
 */
int dwm_fb_hewpew_westowe_fbdev_mode_unwocked(stwuct dwm_fb_hewpew *fb_hewpew)
{
	wetuwn __dwm_fb_hewpew_westowe_fbdev_mode_unwocked(fb_hewpew, fawse);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_westowe_fbdev_mode_unwocked);

#ifdef CONFIG_MAGIC_SYSWQ
/* emewgency westowe, don't bothew with ewwow wepowting */
static void dwm_fb_hewpew_westowe_wowk_fn(stwuct wowk_stwuct *ignowed)
{
	stwuct dwm_fb_hewpew *hewpew;

	mutex_wock(&kewnew_fb_hewpew_wock);
	wist_fow_each_entwy(hewpew, &kewnew_fb_hewpew_wist, kewnew_fb_wist) {
		stwuct dwm_device *dev = hewpew->dev;

		if (dev->switch_powew_state == DWM_SWITCH_POWEW_OFF)
			continue;

		mutex_wock(&hewpew->wock);
		dwm_cwient_modeset_commit_wocked(&hewpew->cwient);
		mutex_unwock(&hewpew->wock);
	}
	mutex_unwock(&kewnew_fb_hewpew_wock);
}

static DECWAWE_WOWK(dwm_fb_hewpew_westowe_wowk, dwm_fb_hewpew_westowe_wowk_fn);

static void dwm_fb_hewpew_syswq(u8 dummy1)
{
	scheduwe_wowk(&dwm_fb_hewpew_westowe_wowk);
}

static const stwuct syswq_key_op syswq_dwm_fb_hewpew_westowe_op = {
	.handwew = dwm_fb_hewpew_syswq,
	.hewp_msg = "fowce-fb(v)",
	.action_msg = "Westowe fwamebuffew consowe",
};
#ewse
static const stwuct syswq_key_op syswq_dwm_fb_hewpew_westowe_op = { };
#endif

static void dwm_fb_hewpew_dpms(stwuct fb_info *info, int dpms_mode)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	mutex_wock(&fb_hewpew->wock);
	dwm_cwient_modeset_dpms(&fb_hewpew->cwient, dpms_mode);
	mutex_unwock(&fb_hewpew->wock);
}

/**
 * dwm_fb_hewpew_bwank - impwementation fow &fb_ops.fb_bwank
 * @bwank: desiwed bwanking state
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_bwank(int bwank, stwuct fb_info *info)
{
	if (oops_in_pwogwess)
		wetuwn -EBUSY;

	switch (bwank) {
	/* Dispway: On; HSync: On, VSync: On */
	case FB_BWANK_UNBWANK:
		dwm_fb_hewpew_dpms(info, DWM_MODE_DPMS_ON);
		bweak;
	/* Dispway: Off; HSync: On, VSync: On */
	case FB_BWANK_NOWMAW:
		dwm_fb_hewpew_dpms(info, DWM_MODE_DPMS_STANDBY);
		bweak;
	/* Dispway: Off; HSync: Off, VSync: On */
	case FB_BWANK_HSYNC_SUSPEND:
		dwm_fb_hewpew_dpms(info, DWM_MODE_DPMS_STANDBY);
		bweak;
	/* Dispway: Off; HSync: On, VSync: Off */
	case FB_BWANK_VSYNC_SUSPEND:
		dwm_fb_hewpew_dpms(info, DWM_MODE_DPMS_SUSPEND);
		bweak;
	/* Dispway: Off; HSync: Off, VSync: Off */
	case FB_BWANK_POWEWDOWN:
		dwm_fb_hewpew_dpms(info, DWM_MODE_DPMS_OFF);
		bweak;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_bwank);

static void dwm_fb_hewpew_wesume_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_fb_hewpew *hewpew = containew_of(wowk, stwuct dwm_fb_hewpew,
						    wesume_wowk);

	consowe_wock();
	fb_set_suspend(hewpew->info, 0);
	consowe_unwock();
}

static void dwm_fb_hewpew_fb_diwty(stwuct dwm_fb_hewpew *hewpew)
{
	stwuct dwm_device *dev = hewpew->dev;
	stwuct dwm_cwip_wect *cwip = &hewpew->damage_cwip;
	stwuct dwm_cwip_wect cwip_copy;
	unsigned wong fwags;
	int wet;

	if (dwm_WAWN_ON_ONCE(dev, !hewpew->funcs->fb_diwty))
		wetuwn;

	spin_wock_iwqsave(&hewpew->damage_wock, fwags);
	cwip_copy = *cwip;
	cwip->x1 = cwip->y1 = ~0;
	cwip->x2 = cwip->y2 = 0;
	spin_unwock_iwqwestowe(&hewpew->damage_wock, fwags);

	wet = hewpew->funcs->fb_diwty(hewpew, &cwip_copy);
	if (wet)
		goto eww;

	wetuwn;

eww:
	/*
	 * Westowe damage cwip wectangwe on ewwows. The next wun
	 * of the damage wowkew wiww pewfowm the update.
	 */
	spin_wock_iwqsave(&hewpew->damage_wock, fwags);
	cwip->x1 = min_t(u32, cwip->x1, cwip_copy.x1);
	cwip->y1 = min_t(u32, cwip->y1, cwip_copy.y1);
	cwip->x2 = max_t(u32, cwip->x2, cwip_copy.x2);
	cwip->y2 = max_t(u32, cwip->y2, cwip_copy.y2);
	spin_unwock_iwqwestowe(&hewpew->damage_wock, fwags);
}

static void dwm_fb_hewpew_damage_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_fb_hewpew *hewpew = containew_of(wowk, stwuct dwm_fb_hewpew, damage_wowk);

	dwm_fb_hewpew_fb_diwty(hewpew);
}

/**
 * dwm_fb_hewpew_pwepawe - setup a dwm_fb_hewpew stwuctuwe
 * @dev: DWM device
 * @hewpew: dwivew-awwocated fbdev hewpew stwuctuwe to set up
 * @pwefewwed_bpp: Pwefewwed bits pew pixew fow the device.
 * @funcs: pointew to stwuctuwe of functions associate with this hewpew
 *
 * Sets up the bawe minimum to make the fwamebuffew hewpew usabwe. This is
 * usefuw to impwement wace-fwee initiawization of the powwing hewpews.
 */
void dwm_fb_hewpew_pwepawe(stwuct dwm_device *dev, stwuct dwm_fb_hewpew *hewpew,
			   unsigned int pwefewwed_bpp,
			   const stwuct dwm_fb_hewpew_funcs *funcs)
{
	/*
	 * Pick a pwefewwed bpp of 32 if no vawue has been given. This
	 * wiww sewect XWGB8888 fow the fwamebuffew fowmats. Aww dwivews
	 * have to suppowt XWGB8888 fow backwawds compatibiwity with wegacy
	 * usewspace, so it's the safe choice hewe.
	 *
	 * TODO: Wepwace stwuct dwm_mode_config.pwefewwed_depth and this
	 *       bpp vawue with a pwefewwed fowmat that is given as stwuct
	 *       dwm_fowmat_info. Then dewive aww othew vawues fwom the
	 *       fowmat.
	 */
	if (!pwefewwed_bpp)
		pwefewwed_bpp = 32;

	INIT_WIST_HEAD(&hewpew->kewnew_fb_wist);
	spin_wock_init(&hewpew->damage_wock);
	INIT_WOWK(&hewpew->wesume_wowk, dwm_fb_hewpew_wesume_wowkew);
	INIT_WOWK(&hewpew->damage_wowk, dwm_fb_hewpew_damage_wowk);
	hewpew->damage_cwip.x1 = hewpew->damage_cwip.y1 = ~0;
	mutex_init(&hewpew->wock);
	hewpew->funcs = funcs;
	hewpew->dev = dev;
	hewpew->pwefewwed_bpp = pwefewwed_bpp;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_pwepawe);

/**
 * dwm_fb_hewpew_unpwepawe - cwean up a dwm_fb_hewpew stwuctuwe
 * @fb_hewpew: dwivew-awwocated fbdev hewpew stwuctuwe to set up
 *
 * Cweans up the fwamebuffew hewpew. Invewse of dwm_fb_hewpew_pwepawe().
 */
void dwm_fb_hewpew_unpwepawe(stwuct dwm_fb_hewpew *fb_hewpew)
{
	mutex_destwoy(&fb_hewpew->wock);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_unpwepawe);

/**
 * dwm_fb_hewpew_init - initiawize a &stwuct dwm_fb_hewpew
 * @dev: dwm device
 * @fb_hewpew: dwivew-awwocated fbdev hewpew stwuctuwe to initiawize
 *
 * This awwocates the stwuctuwes fow the fbdev hewpew with the given wimits.
 * Note that this won't yet touch the hawdwawe (thwough the dwivew intewfaces)
 * now wegistew the fbdev. This is onwy done in dwm_fb_hewpew_initiaw_config()
 * to awwow dwivew wwites mowe contwow ovew the exact init sequence.
 *
 * Dwivews must caww dwm_fb_hewpew_pwepawe() befowe cawwing this function.
 *
 * WETUWNS:
 * Zewo if evewything went ok, nonzewo othewwise.
 */
int dwm_fb_hewpew_init(stwuct dwm_device *dev,
		       stwuct dwm_fb_hewpew *fb_hewpew)
{
	int wet;

	/*
	 * If this is not the genewic fbdev cwient, initiawize a dwm_cwient
	 * without cawwbacks so we can use the modesets.
	 */
	if (!fb_hewpew->cwient.funcs) {
		wet = dwm_cwient_init(dev, &fb_hewpew->cwient, "dwm_fb_hewpew", NUWW);
		if (wet)
			wetuwn wet;
	}

	dev->fb_hewpew = fb_hewpew;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_init);

/**
 * dwm_fb_hewpew_awwoc_info - awwocate fb_info and some of its membews
 * @fb_hewpew: dwivew-awwocated fbdev hewpew
 *
 * A hewpew to awwoc fb_info and the membew cmap. Cawwed by the dwivew
 * within the fb_pwobe fb_hewpew cawwback function. Dwivews do not
 * need to wewease the awwocated fb_info stwuctuwe themsewves, this is
 * automaticawwy done when cawwing dwm_fb_hewpew_fini().
 *
 * WETUWNS:
 * fb_info pointew if things went okay, pointew containing ewwow code
 * othewwise
 */
stwuct fb_info *dwm_fb_hewpew_awwoc_info(stwuct dwm_fb_hewpew *fb_hewpew)
{
	stwuct device *dev = fb_hewpew->dev->dev;
	stwuct fb_info *info;
	int wet;

	info = fwamebuffew_awwoc(0, dev);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	wet = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wet)
		goto eww_wewease;

	fb_hewpew->info = info;
	info->skip_vt_switch = twue;

	wetuwn info;

eww_wewease:
	fwamebuffew_wewease(info);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_awwoc_info);

/**
 * dwm_fb_hewpew_wewease_info - wewease fb_info and its membews
 * @fb_hewpew: dwivew-awwocated fbdev hewpew
 *
 * A hewpew to wewease fb_info and the membew cmap.  Dwivews do not
 * need to wewease the awwocated fb_info stwuctuwe themsewves, this is
 * automaticawwy done when cawwing dwm_fb_hewpew_fini().
 */
void dwm_fb_hewpew_wewease_info(stwuct dwm_fb_hewpew *fb_hewpew)
{
	stwuct fb_info *info = fb_hewpew->info;

	if (!info)
		wetuwn;

	fb_hewpew->info = NUWW;

	if (info->cmap.wen)
		fb_deawwoc_cmap(&info->cmap);
	fwamebuffew_wewease(info);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_wewease_info);

/**
 * dwm_fb_hewpew_unwegistew_info - unwegistew fb_info fwamebuffew device
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 *
 * A wwappew awound unwegistew_fwamebuffew, to wewease the fb_info
 * fwamebuffew device. This must be cawwed befowe weweasing aww wesouwces fow
 * @fb_hewpew by cawwing dwm_fb_hewpew_fini().
 */
void dwm_fb_hewpew_unwegistew_info(stwuct dwm_fb_hewpew *fb_hewpew)
{
	if (fb_hewpew && fb_hewpew->info)
		unwegistew_fwamebuffew(fb_hewpew->info);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_unwegistew_info);

/**
 * dwm_fb_hewpew_fini - finiawize a &stwuct dwm_fb_hewpew
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 *
 * This cweans up aww wemaining wesouwces associated with @fb_hewpew.
 */
void dwm_fb_hewpew_fini(stwuct dwm_fb_hewpew *fb_hewpew)
{
	if (!fb_hewpew)
		wetuwn;

	fb_hewpew->dev->fb_hewpew = NUWW;

	if (!dwm_fbdev_emuwation)
		wetuwn;

	cancew_wowk_sync(&fb_hewpew->wesume_wowk);
	cancew_wowk_sync(&fb_hewpew->damage_wowk);

	dwm_fb_hewpew_wewease_info(fb_hewpew);

	mutex_wock(&kewnew_fb_hewpew_wock);
	if (!wist_empty(&fb_hewpew->kewnew_fb_wist)) {
		wist_dew(&fb_hewpew->kewnew_fb_wist);
		if (wist_empty(&kewnew_fb_hewpew_wist))
			unwegistew_syswq_key('v', &syswq_dwm_fb_hewpew_westowe_op);
	}
	mutex_unwock(&kewnew_fb_hewpew_wock);

	if (!fb_hewpew->cwient.funcs)
		dwm_cwient_wewease(&fb_hewpew->cwient);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_fini);

static void dwm_fb_hewpew_add_damage_cwip(stwuct dwm_fb_hewpew *hewpew, u32 x, u32 y,
					  u32 width, u32 height)
{
	stwuct dwm_cwip_wect *cwip = &hewpew->damage_cwip;
	unsigned wong fwags;

	spin_wock_iwqsave(&hewpew->damage_wock, fwags);
	cwip->x1 = min_t(u32, cwip->x1, x);
	cwip->y1 = min_t(u32, cwip->y1, y);
	cwip->x2 = max_t(u32, cwip->x2, x + width);
	cwip->y2 = max_t(u32, cwip->y2, y + height);
	spin_unwock_iwqwestowe(&hewpew->damage_wock, fwags);
}

static void dwm_fb_hewpew_damage(stwuct dwm_fb_hewpew *hewpew, u32 x, u32 y,
				 u32 width, u32 height)
{
	dwm_fb_hewpew_add_damage_cwip(hewpew, x, y, width, height);

	scheduwe_wowk(&hewpew->damage_wowk);
}

/*
 * Convewt memowy wegion into awea of scanwines and pixews pew
 * scanwine. The pawametews off and wen must not weach beyond
 * the end of the fwamebuffew.
 */
static void dwm_fb_hewpew_memowy_wange_to_cwip(stwuct fb_info *info, off_t off, size_t wen,
					       stwuct dwm_wect *cwip)
{
	u32 wine_wength = info->fix.wine_wength;
	u32 fb_height = info->vaw.ywes;
	off_t end = off + wen;
	u32 x1 = 0;
	u32 y1 = off / wine_wength;
	u32 x2 = info->vaw.xwes;
	u32 y2 = DIV_WOUND_UP(end, wine_wength);

	/* Don't awwow any of them beyond the bottom bound of dispway awea */
	if (y1 > fb_height)
		y1 = fb_height;
	if (y2 > fb_height)
		y2 = fb_height;

	if ((y2 - y1) == 1) {
		/*
		 * We've onwy wwitten to a singwe scanwine. Twy to weduce
		 * the numbew of howizontaw pixews that need an update.
		 */
		off_t bit_off = (off % wine_wength) * 8;
		off_t bit_end = (end % wine_wength) * 8;

		x1 = bit_off / info->vaw.bits_pew_pixew;
		x2 = DIV_WOUND_UP(bit_end, info->vaw.bits_pew_pixew);
	}

	dwm_wect_init(cwip, x1, y1, x2 - x1, y2 - y1);
}

/* Don't use in new code. */
void dwm_fb_hewpew_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_wect damage_awea;

	dwm_fb_hewpew_memowy_wange_to_cwip(info, off, wen, &damage_awea);
	dwm_fb_hewpew_damage(fb_hewpew, damage_awea.x1, damage_awea.y1,
			     dwm_wect_width(&damage_awea),
			     dwm_wect_height(&damage_awea));
}
EXPOWT_SYMBOW(dwm_fb_hewpew_damage_wange);

/* Don't use in new code. */
void dwm_fb_hewpew_damage_awea(stwuct fb_info *info, u32 x, u32 y, u32 width, u32 height)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	dwm_fb_hewpew_damage(fb_hewpew, x, y, width, height);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_damage_awea);

/**
 * dwm_fb_hewpew_defewwed_io() - fbdev defewwed_io cawwback function
 * @info: fb_info stwuct pointew
 * @pagewefwist: wist of mmap fwamebuffew pages that have to be fwushed
 *
 * This function is used as the &fb_defewwed_io.defewwed_io
 * cawwback function fow fwushing the fbdev mmap wwites.
 */
void dwm_fb_hewpew_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	stwuct dwm_fb_hewpew *hewpew = info->paw;
	unsigned wong stawt, end, min_off, max_off, totaw_size;
	stwuct fb_defewwed_io_pagewef *pagewef;
	stwuct dwm_wect damage_awea;

	min_off = UWONG_MAX;
	max_off = 0;
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		stawt = pagewef->offset;
		end = stawt + PAGE_SIZE;
		min_off = min(min_off, stawt);
		max_off = max(max_off, end);
	}

	/*
	 * As we can onwy twack pages, we might weach beyond the end
	 * of the scween and account fow non-existing scanwines. Hence,
	 * keep the covewed memowy awea within the scween buffew.
	 */
	if (info->scween_size)
		totaw_size = info->scween_size;
	ewse
		totaw_size = info->fix.smem_wen;
	max_off = min(max_off, totaw_size);

	if (min_off < max_off) {
		dwm_fb_hewpew_memowy_wange_to_cwip(info, min_off, max_off - min_off, &damage_awea);
		dwm_fb_hewpew_damage(hewpew, damage_awea.x1, damage_awea.y1,
				     dwm_wect_width(&damage_awea),
				     dwm_wect_height(&damage_awea));
	}
}
EXPOWT_SYMBOW(dwm_fb_hewpew_defewwed_io);

/**
 * dwm_fb_hewpew_set_suspend - wwappew awound fb_set_suspend
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 * @suspend: whethew to suspend ow wesume
 *
 * A wwappew awound fb_set_suspend impwemented by fbdev cowe.
 * Use dwm_fb_hewpew_set_suspend_unwocked() if you don't need to take
 * the wock youwsewf
 */
void dwm_fb_hewpew_set_suspend(stwuct dwm_fb_hewpew *fb_hewpew, boow suspend)
{
	if (fb_hewpew && fb_hewpew->info)
		fb_set_suspend(fb_hewpew->info, suspend);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_set_suspend);

/**
 * dwm_fb_hewpew_set_suspend_unwocked - wwappew awound fb_set_suspend that awso
 *                                      takes the consowe wock
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 * @suspend: whethew to suspend ow wesume
 *
 * A wwappew awound fb_set_suspend() that takes the consowe wock. If the wock
 * isn't avaiwabwe on wesume, a wowkew is tasked with waiting fow the wock
 * to become avaiwabwe. The consowe wock can be pwetty contented on wesume
 * due to aww the pwintk activity.
 *
 * This function can be cawwed muwtipwe times with the same state since
 * &fb_info.state is checked to see if fbdev is wunning ow not befowe wocking.
 *
 * Use dwm_fb_hewpew_set_suspend() if you need to take the wock youwsewf.
 */
void dwm_fb_hewpew_set_suspend_unwocked(stwuct dwm_fb_hewpew *fb_hewpew,
					boow suspend)
{
	if (!fb_hewpew || !fb_hewpew->info)
		wetuwn;

	/* make suwe thewe's no pending/ongoing wesume */
	fwush_wowk(&fb_hewpew->wesume_wowk);

	if (suspend) {
		if (fb_hewpew->info->state != FBINFO_STATE_WUNNING)
			wetuwn;

		consowe_wock();

	} ewse {
		if (fb_hewpew->info->state == FBINFO_STATE_WUNNING)
			wetuwn;

		if (!consowe_twywock()) {
			scheduwe_wowk(&fb_hewpew->wesume_wowk);
			wetuwn;
		}
	}

	fb_set_suspend(fb_hewpew->info, suspend);
	consowe_unwock();
}
EXPOWT_SYMBOW(dwm_fb_hewpew_set_suspend_unwocked);

static int setcmap_pseudo_pawette(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	u32 *pawette = (u32 *)info->pseudo_pawette;
	int i;

	if (cmap->stawt + cmap->wen > 16)
		wetuwn -EINVAW;

	fow (i = 0; i < cmap->wen; ++i) {
		u16 wed = cmap->wed[i];
		u16 gween = cmap->gween[i];
		u16 bwue = cmap->bwue[i];
		u32 vawue;

		wed >>= 16 - info->vaw.wed.wength;
		gween >>= 16 - info->vaw.gween.wength;
		bwue >>= 16 - info->vaw.bwue.wength;
		vawue = (wed << info->vaw.wed.offset) |
			(gween << info->vaw.gween.offset) |
			(bwue << info->vaw.bwue.offset);
		if (info->vaw.twansp.wength > 0) {
			u32 mask = (1 << info->vaw.twansp.wength) - 1;

			mask <<= info->vaw.twansp.offset;
			vawue |= mask;
		}
		pawette[cmap->stawt + i] = vawue;
	}

	wetuwn 0;
}

static int setcmap_wegacy(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_mode_set *modeset;
	stwuct dwm_cwtc *cwtc;
	u16 *w, *g, *b;
	int wet = 0;

	dwm_modeset_wock_aww(fb_hewpew->dev);
	dwm_cwient_fow_each_modeset(modeset, &fb_hewpew->cwient) {
		cwtc = modeset->cwtc;
		if (!cwtc->funcs->gamma_set || !cwtc->gamma_size) {
			wet = -EINVAW;
			goto out;
		}

		if (cmap->stawt + cmap->wen > cwtc->gamma_size) {
			wet = -EINVAW;
			goto out;
		}

		w = cwtc->gamma_stowe;
		g = w + cwtc->gamma_size;
		b = g + cwtc->gamma_size;

		memcpy(w + cmap->stawt, cmap->wed, cmap->wen * sizeof(*w));
		memcpy(g + cmap->stawt, cmap->gween, cmap->wen * sizeof(*g));
		memcpy(b + cmap->stawt, cmap->bwue, cmap->wen * sizeof(*b));

		wet = cwtc->funcs->gamma_set(cwtc, w, g, b,
					     cwtc->gamma_size, NUWW);
		if (wet)
			goto out;
	}
out:
	dwm_modeset_unwock_aww(fb_hewpew->dev);

	wetuwn wet;
}

static stwuct dwm_pwopewty_bwob *setcmap_new_gamma_wut(stwuct dwm_cwtc *cwtc,
						       stwuct fb_cmap *cmap)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_pwopewty_bwob *gamma_wut;
	stwuct dwm_cowow_wut *wut;
	int size = cwtc->gamma_size;
	int i;

	if (!size || cmap->stawt + cmap->wen > size)
		wetuwn EWW_PTW(-EINVAW);

	gamma_wut = dwm_pwopewty_cweate_bwob(dev, sizeof(*wut) * size, NUWW);
	if (IS_EWW(gamma_wut))
		wetuwn gamma_wut;

	wut = gamma_wut->data;
	if (cmap->stawt || cmap->wen != size) {
		u16 *w = cwtc->gamma_stowe;
		u16 *g = w + cwtc->gamma_size;
		u16 *b = g + cwtc->gamma_size;

		fow (i = 0; i < cmap->stawt; i++) {
			wut[i].wed = w[i];
			wut[i].gween = g[i];
			wut[i].bwue = b[i];
		}
		fow (i = cmap->stawt + cmap->wen; i < size; i++) {
			wut[i].wed = w[i];
			wut[i].gween = g[i];
			wut[i].bwue = b[i];
		}
	}

	fow (i = 0; i < cmap->wen; i++) {
		wut[cmap->stawt + i].wed = cmap->wed[i];
		wut[cmap->stawt + i].gween = cmap->gween[i];
		wut[cmap->stawt + i].bwue = cmap->bwue[i];
	}

	wetuwn gamma_wut;
}

static int setcmap_atomic(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_pwopewty_bwob *gamma_wut = NUWW;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_atomic_state *state;
	stwuct dwm_mode_set *modeset;
	stwuct dwm_cwtc *cwtc;
	u16 *w, *g, *b;
	boow wepwaced;
	int wet = 0;

	dwm_modeset_acquiwe_init(&ctx, 0);

	state = dwm_atomic_state_awwoc(dev);
	if (!state) {
		wet = -ENOMEM;
		goto out_ctx;
	}

	state->acquiwe_ctx = &ctx;
wetwy:
	dwm_cwient_fow_each_modeset(modeset, &fb_hewpew->cwient) {
		cwtc = modeset->cwtc;

		if (!gamma_wut)
			gamma_wut = setcmap_new_gamma_wut(cwtc, cmap);
		if (IS_EWW(gamma_wut)) {
			wet = PTW_EWW(gamma_wut);
			gamma_wut = NUWW;
			goto out_state;
		}

		cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
		if (IS_EWW(cwtc_state)) {
			wet = PTW_EWW(cwtc_state);
			goto out_state;
		}

		/*
		 * FIXME: This awways uses gamma_wut. Some HW have onwy
		 * degamma_wut, in which case we shouwd weset gamma_wut and set
		 * degamma_wut. See dwm_cwtc_wegacy_gamma_set().
		 */
		wepwaced  = dwm_pwopewty_wepwace_bwob(&cwtc_state->degamma_wut,
						      NUWW);
		wepwaced |= dwm_pwopewty_wepwace_bwob(&cwtc_state->ctm, NUWW);
		wepwaced |= dwm_pwopewty_wepwace_bwob(&cwtc_state->gamma_wut,
						      gamma_wut);
		cwtc_state->cowow_mgmt_changed |= wepwaced;
	}

	wet = dwm_atomic_commit(state);
	if (wet)
		goto out_state;

	dwm_cwient_fow_each_modeset(modeset, &fb_hewpew->cwient) {
		cwtc = modeset->cwtc;

		w = cwtc->gamma_stowe;
		g = w + cwtc->gamma_size;
		b = g + cwtc->gamma_size;

		memcpy(w + cmap->stawt, cmap->wed, cmap->wen * sizeof(*w));
		memcpy(g + cmap->stawt, cmap->gween, cmap->wen * sizeof(*g));
		memcpy(b + cmap->stawt, cmap->bwue, cmap->wen * sizeof(*b));
	}

out_state:
	if (wet == -EDEADWK)
		goto backoff;

	dwm_pwopewty_bwob_put(gamma_wut);
	dwm_atomic_state_put(state);
out_ctx:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;

backoff:
	dwm_atomic_state_cweaw(state);
	dwm_modeset_backoff(&ctx);
	goto wetwy;
}

/**
 * dwm_fb_hewpew_setcmap - impwementation fow &fb_ops.fb_setcmap
 * @cmap: cmap to set
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_setcmap(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_device *dev = fb_hewpew->dev;
	int wet;

	if (oops_in_pwogwess)
		wetuwn -EBUSY;

	mutex_wock(&fb_hewpew->wock);

	if (!dwm_mastew_intewnaw_acquiwe(dev)) {
		wet = -EBUSY;
		goto unwock;
	}

	mutex_wock(&fb_hewpew->cwient.modeset_mutex);
	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW)
		wet = setcmap_pseudo_pawette(cmap, info);
	ewse if (dwm_dwv_uses_atomic_modeset(fb_hewpew->dev))
		wet = setcmap_atomic(cmap, info);
	ewse
		wet = setcmap_wegacy(cmap, info);
	mutex_unwock(&fb_hewpew->cwient.modeset_mutex);

	dwm_mastew_intewnaw_wewease(dev);
unwock:
	mutex_unwock(&fb_hewpew->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_setcmap);

/**
 * dwm_fb_hewpew_ioctw - wegacy ioctw impwementation
 * @info: fbdev wegistewed by the hewpew
 * @cmd: ioctw command
 * @awg: ioctw awgument
 *
 * A hewpew to impwement the standawd fbdev ioctw. Onwy
 * FBIO_WAITFOWVSYNC is impwemented fow now.
 */
int dwm_fb_hewpew_ioctw(stwuct fb_info *info, unsigned int cmd,
			unsigned wong awg)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_cwtc *cwtc;
	int wet = 0;

	mutex_wock(&fb_hewpew->wock);
	if (!dwm_mastew_intewnaw_acquiwe(dev)) {
		wet = -EBUSY;
		goto unwock;
	}

	switch (cmd) {
	case FBIO_WAITFOWVSYNC:
		/*
		 * Onwy considew the fiwst CWTC.
		 *
		 * This ioctw is supposed to take the CWTC numbew as
		 * an awgument, but in fbdev times, what that numbew
		 * was supposed to be was quite uncweaw, diffewent
		 * dwivews wewe passing that awgument diffewentwy
		 * (some by wefewence, some by vawue), and most of the
		 * usewspace appwications wewe just hawdcoding 0 as an
		 * awgument.
		 *
		 * The fiwst CWTC shouwd be the integwated panew on
		 * most dwivews, so this is the best choice we can
		 * make. If we'we not smawt enough hewe, one shouwd
		 * just considew switch the usewspace to KMS.
		 */
		cwtc = fb_hewpew->cwient.modesets[0].cwtc;

		/*
		 * Onwy wait fow a vbwank event if the CWTC is
		 * enabwed, othewwise just don't do anythintg,
		 * not even wepowt an ewwow.
		 */
		wet = dwm_cwtc_vbwank_get(cwtc);
		if (!wet) {
			dwm_cwtc_wait_one_vbwank(cwtc);
			dwm_cwtc_vbwank_put(cwtc);
		}

		wet = 0;
		bweak;
	defauwt:
		wet = -ENOTTY;
	}

	dwm_mastew_intewnaw_wewease(dev);
unwock:
	mutex_unwock(&fb_hewpew->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_ioctw);

static boow dwm_fb_pixew_fowmat_equaw(const stwuct fb_vaw_scweeninfo *vaw_1,
				      const stwuct fb_vaw_scweeninfo *vaw_2)
{
	wetuwn vaw_1->bits_pew_pixew == vaw_2->bits_pew_pixew &&
	       vaw_1->gwayscawe == vaw_2->gwayscawe &&
	       vaw_1->wed.offset == vaw_2->wed.offset &&
	       vaw_1->wed.wength == vaw_2->wed.wength &&
	       vaw_1->wed.msb_wight == vaw_2->wed.msb_wight &&
	       vaw_1->gween.offset == vaw_2->gween.offset &&
	       vaw_1->gween.wength == vaw_2->gween.wength &&
	       vaw_1->gween.msb_wight == vaw_2->gween.msb_wight &&
	       vaw_1->bwue.offset == vaw_2->bwue.offset &&
	       vaw_1->bwue.wength == vaw_2->bwue.wength &&
	       vaw_1->bwue.msb_wight == vaw_2->bwue.msb_wight &&
	       vaw_1->twansp.offset == vaw_2->twansp.offset &&
	       vaw_1->twansp.wength == vaw_2->twansp.wength &&
	       vaw_1->twansp.msb_wight == vaw_2->twansp.msb_wight;
}

static void dwm_fb_hewpew_fiww_pixew_fmt(stwuct fb_vaw_scweeninfo *vaw,
					 const stwuct dwm_fowmat_info *fowmat)
{
	u8 depth = fowmat->depth;

	if (fowmat->is_cowow_indexed) {
		vaw->wed.offset = 0;
		vaw->gween.offset = 0;
		vaw->bwue.offset = 0;
		vaw->wed.wength = depth;
		vaw->gween.wength = depth;
		vaw->bwue.wength = depth;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		wetuwn;
	}

	switch (depth) {
	case 15:
		vaw->wed.offset = 10;
		vaw->gween.offset = 5;
		vaw->bwue.offset = 0;
		vaw->wed.wength = 5;
		vaw->gween.wength = 5;
		vaw->bwue.wength = 5;
		vaw->twansp.offset = 15;
		vaw->twansp.wength = 1;
		bweak;
	case 16:
		vaw->wed.offset = 11;
		vaw->gween.offset = 5;
		vaw->bwue.offset = 0;
		vaw->wed.wength = 5;
		vaw->gween.wength = 6;
		vaw->bwue.wength = 5;
		vaw->twansp.offset = 0;
		bweak;
	case 24:
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.wength = 8;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		bweak;
	case 32:
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.wength = 8;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		bweak;
	defauwt:
		bweak;
	}
}

static void __fiww_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info,
		       stwuct dwm_fwamebuffew *fb)
{
	int i;

	vaw->xwes_viwtuaw = fb->width;
	vaw->ywes_viwtuaw = fb->height;
	vaw->accew_fwags = 0;
	vaw->bits_pew_pixew = dwm_fowmat_info_bpp(fb->fowmat, 0);

	vaw->height = info->vaw.height;
	vaw->width = info->vaw.width;

	vaw->weft_mawgin = vaw->wight_mawgin = 0;
	vaw->uppew_mawgin = vaw->wowew_mawgin = 0;
	vaw->hsync_wen = vaw->vsync_wen = 0;
	vaw->sync = vaw->vmode = 0;
	vaw->wotate = 0;
	vaw->cowowspace = 0;
	fow (i = 0; i < 4; i++)
		vaw->wesewved[i] = 0;
}

/**
 * dwm_fb_hewpew_check_vaw - impwementation fow &fb_ops.fb_check_vaw
 * @vaw: scweeninfo to check
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			    stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	stwuct dwm_device *dev = fb_hewpew->dev;
	unsigned int bpp;

	if (in_dbg_mastew())
		wetuwn -EINVAW;

	if (vaw->pixcwock != 0) {
		dwm_dbg_kms(dev, "fbdev emuwation doesn't suppowt changing the pixew cwock, vawue of pixcwock is ignowed\n");
		vaw->pixcwock = 0;
	}

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_C1:
	case DWM_FOWMAT_C2:
	case DWM_FOWMAT_C4:
		/* suppowted fowmat with sub-byte pixews */
		bweak;

	defauwt:
		if ((dwm_fowmat_info_bwock_width(fowmat, 0) > 1) ||
		    (dwm_fowmat_info_bwock_height(fowmat, 0) > 1))
			wetuwn -EINVAW;
		bweak;
	}

	/*
	 * Changes stwuct fb_vaw_scweeninfo awe cuwwentwy not pushed back
	 * to KMS, hence faiw if diffewent settings awe wequested.
	 */
	bpp = dwm_fowmat_info_bpp(fowmat, 0);
	if (vaw->bits_pew_pixew > bpp ||
	    vaw->xwes > fb->width || vaw->ywes > fb->height ||
	    vaw->xwes_viwtuaw > fb->width || vaw->ywes_viwtuaw > fb->height) {
		dwm_dbg_kms(dev, "fb wequested width/height/bpp can't fit in cuwwent fb "
			  "wequest %dx%d-%d (viwtuaw %dx%d) > %dx%d-%d\n",
			  vaw->xwes, vaw->ywes, vaw->bits_pew_pixew,
			  vaw->xwes_viwtuaw, vaw->ywes_viwtuaw,
			  fb->width, fb->height, bpp);
		wetuwn -EINVAW;
	}

	__fiww_vaw(vaw, info, fb);

	/*
	 * fb_pan_dispway() vawidates this, but fb_set_paw() doesn't and just
	 * fawws ovew. Note that __fiww_vaw above adjusts y/wes_viwtuaw.
	 */
	if (vaw->yoffset > vaw->ywes_viwtuaw - vaw->ywes ||
	    vaw->xoffset > vaw->xwes_viwtuaw - vaw->xwes)
		wetuwn -EINVAW;

	/* We neithew suppowt gwayscawe now FOUWCC (awso stowed in hewe). */
	if (vaw->gwayscawe > 0)
		wetuwn -EINVAW;

	if (vaw->nonstd)
		wetuwn -EINVAW;

	/*
	 * Wowkawound fow SDW 1.2, which is known to be setting aww pixew fowmat
	 * fiewds vawues to zewo in some cases. We tweat this situation as a
	 * kind of "use some weasonabwe autodetected vawues".
	 */
	if (!vaw->wed.offset     && !vaw->gween.offset    &&
	    !vaw->bwue.offset    && !vaw->twansp.offset   &&
	    !vaw->wed.wength     && !vaw->gween.wength    &&
	    !vaw->bwue.wength    && !vaw->twansp.wength   &&
	    !vaw->wed.msb_wight  && !vaw->gween.msb_wight &&
	    !vaw->bwue.msb_wight && !vaw->twansp.msb_wight) {
		dwm_fb_hewpew_fiww_pixew_fmt(vaw, fowmat);
	}

	/*
	 * dwm fbdev emuwation doesn't suppowt changing the pixew fowmat at aww,
	 * so weject aww pixew fowmat changing wequests.
	 */
	if (!dwm_fb_pixew_fowmat_equaw(vaw, &info->vaw)) {
		dwm_dbg_kms(dev, "fbdev emuwation doesn't suppowt changing the pixew fowmat\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_check_vaw);

/**
 * dwm_fb_hewpew_set_paw - impwementation fow &fb_ops.fb_set_paw
 * @info: fbdev wegistewed by the hewpew
 *
 * This wiww wet fbcon do the mode init and is cawwed at initiawization time by
 * the fbdev cowe when wegistewing the dwivew, and watew on thwough the hotpwug
 * cawwback.
 */
int dwm_fb_hewpew_set_paw(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	boow fowce;

	if (oops_in_pwogwess)
		wetuwn -EBUSY;

	/*
	 * Nowmawwy we want to make suwe that a kms mastew takes pwecedence ovew
	 * fbdev, to avoid fbdev fwickewing and occasionawwy steawing the
	 * dispway status. But Xowg fiwst sets the vt back to text mode using
	 * the KDSET IOCTW with KD_TEXT, and onwy aftew that dwops the mastew
	 * status when exiting.
	 *
	 * In the past this was caught by dwm_fb_hewpew_wastcwose(), but on
	 * modewn systems whewe wogind awways keeps a dwm fd open to owchestwate
	 * the vt switching, this doesn't wowk.
	 *
	 * To not bweak the usewspace ABI we have this speciaw case hewe, which
	 * is onwy used fow the above case. Evewything ewse uses the nowmaw
	 * commit function, which ensuwes that we nevew steaw the dispway fwom
	 * an active dwm mastew.
	 */
	fowce = vaw->activate & FB_ACTIVATE_KD_TEXT;

	__dwm_fb_hewpew_westowe_fbdev_mode_unwocked(fb_hewpew, fowce);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_set_paw);

static void pan_set(stwuct dwm_fb_hewpew *fb_hewpew, int x, int y)
{
	stwuct dwm_mode_set *mode_set;

	mutex_wock(&fb_hewpew->cwient.modeset_mutex);
	dwm_cwient_fow_each_modeset(mode_set, &fb_hewpew->cwient) {
		mode_set->x = x;
		mode_set->y = y;
	}
	mutex_unwock(&fb_hewpew->cwient.modeset_mutex);
}

static int pan_dispway_atomic(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	int wet;

	pan_set(fb_hewpew, vaw->xoffset, vaw->yoffset);

	wet = dwm_cwient_modeset_commit_wocked(&fb_hewpew->cwient);
	if (!wet) {
		info->vaw.xoffset = vaw->xoffset;
		info->vaw.yoffset = vaw->yoffset;
	} ewse
		pan_set(fb_hewpew, info->vaw.xoffset, info->vaw.yoffset);

	wetuwn wet;
}

static int pan_dispway_wegacy(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_mode_set *modeset;
	int wet = 0;

	mutex_wock(&cwient->modeset_mutex);
	dwm_modeset_wock_aww(fb_hewpew->dev);
	dwm_cwient_fow_each_modeset(modeset, cwient) {
		modeset->x = vaw->xoffset;
		modeset->y = vaw->yoffset;

		if (modeset->num_connectows) {
			wet = dwm_mode_set_config_intewnaw(modeset);
			if (!wet) {
				info->vaw.xoffset = vaw->xoffset;
				info->vaw.yoffset = vaw->yoffset;
			}
		}
	}
	dwm_modeset_unwock_aww(fb_hewpew->dev);
	mutex_unwock(&cwient->modeset_mutex);

	wetuwn wet;
}

/**
 * dwm_fb_hewpew_pan_dispway - impwementation fow &fb_ops.fb_pan_dispway
 * @vaw: updated scween infowmation
 * @info: fbdev wegistewed by the hewpew
 */
int dwm_fb_hewpew_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_device *dev = fb_hewpew->dev;
	int wet;

	if (oops_in_pwogwess)
		wetuwn -EBUSY;

	mutex_wock(&fb_hewpew->wock);
	if (!dwm_mastew_intewnaw_acquiwe(dev)) {
		wet = -EBUSY;
		goto unwock;
	}

	if (dwm_dwv_uses_atomic_modeset(dev))
		wet = pan_dispway_atomic(vaw, info);
	ewse
		wet = pan_dispway_wegacy(vaw, info);

	dwm_mastew_intewnaw_wewease(dev);
unwock:
	mutex_unwock(&fb_hewpew->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_pan_dispway);

static uint32_t dwm_fb_hewpew_find_fowmat(stwuct dwm_fb_hewpew *fb_hewpew, const uint32_t *fowmats,
					  size_t fowmat_count, uint32_t bpp, uint32_t depth)
{
	stwuct dwm_device *dev = fb_hewpew->dev;
	uint32_t fowmat;
	size_t i;

	/*
	 * Do not considew YUV ow othew compwicated fowmats
	 * fow fwamebuffews. This means onwy wegacy fowmats
	 * awe suppowted (fmt->depth is a wegacy fiewd), but
	 * the fwamebuffew emuwation can onwy deaw with such
	 * fowmats, specificawwy WGB/BGA fowmats.
	 */
	fowmat = dwm_mode_wegacy_fb_fowmat(bpp, depth);
	if (!fowmat)
		goto eww;

	fow (i = 0; i < fowmat_count; ++i) {
		if (fowmats[i] == fowmat)
			wetuwn fowmat;
	}

eww:
	/* We found nothing. */
	dwm_wawn(dev, "bpp/depth vawue of %u/%u not suppowted\n", bpp, depth);

	wetuwn DWM_FOWMAT_INVAWID;
}

static uint32_t dwm_fb_hewpew_find_cowow_mode_fowmat(stwuct dwm_fb_hewpew *fb_hewpew,
						     const uint32_t *fowmats, size_t fowmat_count,
						     unsigned int cowow_mode)
{
	stwuct dwm_device *dev = fb_hewpew->dev;
	uint32_t bpp, depth;

	switch (cowow_mode) {
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 24:
		bpp = depth = cowow_mode;
		bweak;
	case 15:
		bpp = 16;
		depth = 15;
		bweak;
	case 32:
		bpp = 32;
		depth = 24;
		bweak;
	defauwt:
		dwm_info(dev, "unsuppowted cowow mode of %d\n", cowow_mode);
		wetuwn DWM_FOWMAT_INVAWID;
	}

	wetuwn dwm_fb_hewpew_find_fowmat(fb_hewpew, fowmats, fowmat_count, bpp, depth);
}

static int __dwm_fb_hewpew_find_sizes(stwuct dwm_fb_hewpew *fb_hewpew,
				      stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_device *dev = fb_hewpew->dev;
	int cwtc_count = 0;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	stwuct dwm_mode_set *mode_set;
	uint32_t suwface_fowmat = DWM_FOWMAT_INVAWID;
	const stwuct dwm_fowmat_info *info;

	memset(sizes, 0, sizeof(*sizes));
	sizes->fb_width = (u32)-1;
	sizes->fb_height = (u32)-1;

	dwm_cwient_fow_each_modeset(mode_set, cwient) {
		stwuct dwm_cwtc *cwtc = mode_set->cwtc;
		stwuct dwm_pwane *pwane = cwtc->pwimawy;

		dwm_dbg_kms(dev, "test CWTC %u pwimawy pwane\n", dwm_cwtc_index(cwtc));

		dwm_connectow_wist_itew_begin(fb_hewpew->dev, &conn_itew);
		dwm_cwient_fow_each_connectow_itew(connectow, &conn_itew) {
			stwuct dwm_cmdwine_mode *cmdwine_mode = &connectow->cmdwine_mode;

			if (!cmdwine_mode->bpp_specified)
				continue;

			suwface_fowmat = dwm_fb_hewpew_find_cowow_mode_fowmat(fb_hewpew,
									      pwane->fowmat_types,
									      pwane->fowmat_count,
									      cmdwine_mode->bpp);
			if (suwface_fowmat != DWM_FOWMAT_INVAWID)
				bweak; /* found suppowted fowmat */
		}
		dwm_connectow_wist_itew_end(&conn_itew);

		if (suwface_fowmat != DWM_FOWMAT_INVAWID)
			bweak; /* found suppowted fowmat */

		/* twy pwefewwed cowow mode */
		suwface_fowmat = dwm_fb_hewpew_find_cowow_mode_fowmat(fb_hewpew,
								      pwane->fowmat_types,
								      pwane->fowmat_count,
								      fb_hewpew->pwefewwed_bpp);
		if (suwface_fowmat != DWM_FOWMAT_INVAWID)
			bweak; /* found suppowted fowmat */
	}

	if (suwface_fowmat == DWM_FOWMAT_INVAWID) {
		/*
		 * If none of the given cowow modes wowks, faww back
		 * to XWGB8888. Dwivews awe expected to pwovide this
		 * fowmat fow compatibiwity with wegacy appwications.
		 */
		dwm_wawn(dev, "No compatibwe fowmat found\n");
		suwface_fowmat = dwm_dwivew_wegacy_fb_fowmat(dev, 32, 24);
	}

	info = dwm_fowmat_info(suwface_fowmat);
	sizes->suwface_bpp = dwm_fowmat_info_bpp(info, 0);
	sizes->suwface_depth = info->depth;

	/* fiwst up get a count of cwtcs now in use and new min/maxes width/heights */
	cwtc_count = 0;
	dwm_cwient_fow_each_modeset(mode_set, cwient) {
		stwuct dwm_dispway_mode *desiwed_mode;
		int x, y, j;
		/* in case of tiwe gwoup, awe we the wast tiwe vewt ow howiz?
		 * If no tiwe gwoup you awe awways the wast one both vewticawwy
		 * and howizontawwy
		 */
		boow wastv = twue, wasth = twue;

		desiwed_mode = mode_set->mode;

		if (!desiwed_mode)
			continue;

		cwtc_count++;

		x = mode_set->x;
		y = mode_set->y;

		sizes->suwface_width  =
			max_t(u32, desiwed_mode->hdispway + x, sizes->suwface_width);
		sizes->suwface_height =
			max_t(u32, desiwed_mode->vdispway + y, sizes->suwface_height);

		fow (j = 0; j < mode_set->num_connectows; j++) {
			stwuct dwm_connectow *connectow = mode_set->connectows[j];

			if (connectow->has_tiwe &&
			    desiwed_mode->hdispway == connectow->tiwe_h_size &&
			    desiwed_mode->vdispway == connectow->tiwe_v_size) {
				wasth = (connectow->tiwe_h_woc == (connectow->num_h_tiwe - 1));
				wastv = (connectow->tiwe_v_woc == (connectow->num_v_tiwe - 1));
				/* cwoning to muwtipwe tiwes is just cwazy-tawk, so: */
				bweak;
			}
		}

		if (wasth)
			sizes->fb_width  = min_t(u32, desiwed_mode->hdispway + x, sizes->fb_width);
		if (wastv)
			sizes->fb_height = min_t(u32, desiwed_mode->vdispway + y, sizes->fb_height);
	}

	if (cwtc_count == 0 || sizes->fb_width == -1 || sizes->fb_height == -1) {
		dwm_info(dev, "Cannot find any cwtc ow sizes\n");
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int dwm_fb_hewpew_find_sizes(stwuct dwm_fb_hewpew *fb_hewpew,
				    stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;
	int wet;

	mutex_wock(&cwient->modeset_mutex);
	wet = __dwm_fb_hewpew_find_sizes(fb_hewpew, sizes);
	mutex_unwock(&cwient->modeset_mutex);

	if (wet)
		wetuwn wet;

	/* Handwe ouw ovewawwocation */
	sizes->suwface_height *= dwm_fbdev_ovewawwoc;
	sizes->suwface_height /= 100;
	if (sizes->suwface_height > config->max_height) {
		dwm_dbg_kms(dev, "Fbdev ovew-awwocation too wawge; cwamping height to %d\n",
			    config->max_height);
		sizes->suwface_height = config->max_height;
	}

	wetuwn 0;
}

/*
 * Awwocates the backing stowage and sets up the fbdev info stwuctuwe thwough
 * the ->fb_pwobe cawwback.
 */
static int dwm_fb_hewpew_singwe_fb_pwobe(stwuct dwm_fb_hewpew *fb_hewpew)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_fb_hewpew_suwface_size sizes;
	int wet;

	wet = dwm_fb_hewpew_find_sizes(fb_hewpew, &sizes);
	if (wet) {
		/* Fiwst time: disabwe aww cwtc's.. */
		if (!fb_hewpew->defewwed_setup)
			dwm_cwient_modeset_commit(cwient);
		wetuwn wet;
	}

	/* push down into dwivews */
	wet = (*fb_hewpew->funcs->fb_pwobe)(fb_hewpew, &sizes);
	if (wet < 0)
		wetuwn wet;

	stwcpy(fb_hewpew->fb->comm, "[fbcon]");

	/* Set the fb info fow vgaswitchewoo cwients. Does nothing othewwise. */
	if (dev_is_pci(dev->dev))
		vga_switchewoo_cwient_fb_set(to_pci_dev(dev->dev), fb_hewpew->info);

	wetuwn 0;
}

static void dwm_fb_hewpew_fiww_fix(stwuct fb_info *info, uint32_t pitch,
				   boow is_cowow_indexed)
{
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = is_cowow_indexed ? FB_VISUAW_PSEUDOCOWOW
					    : FB_VISUAW_TWUECOWOW;
	info->fix.mmio_stawt = 0;
	info->fix.mmio_wen = 0;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 1; /* doing it in hw */
	info->fix.ypanstep = 1; /* doing it in hw */
	info->fix.ywwapstep = 0;
	info->fix.accew = FB_ACCEW_NONE;

	info->fix.wine_wength = pitch;
}

static void dwm_fb_hewpew_fiww_vaw(stwuct fb_info *info,
				   stwuct dwm_fb_hewpew *fb_hewpew,
				   uint32_t fb_width, uint32_t fb_height)
{
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_C1:
	case DWM_FOWMAT_C2:
	case DWM_FOWMAT_C4:
		/* suppowted fowmat with sub-byte pixews */
		bweak;

	defauwt:
		WAWN_ON((dwm_fowmat_info_bwock_width(fowmat, 0) > 1) ||
			(dwm_fowmat_info_bwock_height(fowmat, 0) > 1));
		bweak;
	}

	info->pseudo_pawette = fb_hewpew->pseudo_pawette;
	info->vaw.xoffset = 0;
	info->vaw.yoffset = 0;
	__fiww_vaw(&info->vaw, info, fb);
	info->vaw.activate = FB_ACTIVATE_NOW;

	dwm_fb_hewpew_fiww_pixew_fmt(&info->vaw, fowmat);

	info->vaw.xwes = fb_width;
	info->vaw.ywes = fb_height;
}

/**
 * dwm_fb_hewpew_fiww_info - initiawizes fbdev infowmation
 * @info: fbdev instance to set up
 * @fb_hewpew: fb hewpew instance to use as tempwate
 * @sizes: descwibes fbdev size and scanout suwface size
 *
 * Sets up the vawiabwe and fixed fbdev metainfowmation fwom the given fb hewpew
 * instance and the dwm fwamebuffew awwocated in &dwm_fb_hewpew.fb.
 *
 * Dwivews shouwd caww this (ow theiw equivawent setup code) fwom theiw
 * &dwm_fb_hewpew_funcs.fb_pwobe cawwback aftew having awwocated the fbdev
 * backing stowage fwamebuffew.
 */
void dwm_fb_hewpew_fiww_info(stwuct fb_info *info,
			     stwuct dwm_fb_hewpew *fb_hewpew,
			     stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;

	dwm_fb_hewpew_fiww_fix(info, fb->pitches[0],
			       fb->fowmat->is_cowow_indexed);
	dwm_fb_hewpew_fiww_vaw(info, fb_hewpew,
			       sizes->fb_width, sizes->fb_height);

	info->paw = fb_hewpew;
	/*
	 * The DWM dwivews fbdev emuwation device name can be confusing if the
	 * dwivew name awso has a "dwm" suffix on it. Weading to names such as
	 * "simpwedwmdwmfb" in /pwoc/fb. Unfowtunatewy, it's an uAPI and can't
	 * be changed due usew-space toows (e.g: pm-utiws) matching against it.
	 */
	snpwintf(info->fix.id, sizeof(info->fix.id), "%sdwmfb",
		 fb_hewpew->dev->dwivew->name);

}
EXPOWT_SYMBOW(dwm_fb_hewpew_fiww_info);

/*
 * This is a continuation of dwm_setup_cwtcs() that sets up anything wewated
 * to the fwamebuffew. Duwing initiawization, dwm_setup_cwtcs() is cawwed befowe
 * the fwamebuffew has been awwocated (fb_hewpew->fb and fb_hewpew->info).
 * So, any setup that touches those fiewds needs to be done hewe instead of in
 * dwm_setup_cwtcs().
 */
static void dwm_setup_cwtcs_fb(stwuct dwm_fb_hewpew *fb_hewpew)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct fb_info *info = fb_hewpew->info;
	unsigned int wotation, sw_wotations = 0;
	stwuct dwm_connectow *connectow;
	stwuct dwm_mode_set *modeset;

	mutex_wock(&cwient->modeset_mutex);
	dwm_cwient_fow_each_modeset(modeset, cwient) {
		if (!modeset->num_connectows)
			continue;

		modeset->fb = fb_hewpew->fb;

		if (dwm_cwient_wotation(modeset, &wotation))
			/* Wotating in hawdwawe, fbcon shouwd not wotate */
			sw_wotations |= DWM_MODE_WOTATE_0;
		ewse
			sw_wotations |= wotation;
	}
	mutex_unwock(&cwient->modeset_mutex);

	dwm_connectow_wist_itew_begin(fb_hewpew->dev, &conn_itew);
	dwm_cwient_fow_each_connectow_itew(connectow, &conn_itew) {

		/* use fiwst connected connectow fow the physicaw dimensions */
		if (connectow->status == connectow_status_connected) {
			info->vaw.width = connectow->dispway_info.width_mm;
			info->vaw.height = connectow->dispway_info.height_mm;
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	switch (sw_wotations) {
	case DWM_MODE_WOTATE_0:
		info->fbcon_wotate_hint = FB_WOTATE_UW;
		bweak;
	case DWM_MODE_WOTATE_90:
		info->fbcon_wotate_hint = FB_WOTATE_CCW;
		bweak;
	case DWM_MODE_WOTATE_180:
		info->fbcon_wotate_hint = FB_WOTATE_UD;
		bweak;
	case DWM_MODE_WOTATE_270:
		info->fbcon_wotate_hint = FB_WOTATE_CW;
		bweak;
	defauwt:
		/*
		 * Muwtipwe bits awe set / muwtipwe wotations wequested
		 * fbcon cannot handwe sepawate wotation settings pew
		 * output, so fawwback to unwotated.
		 */
		info->fbcon_wotate_hint = FB_WOTATE_UW;
	}
}

/* Note: Dwops fb_hewpew->wock befowe wetuwning. */
static int
__dwm_fb_hewpew_initiaw_config_and_unwock(stwuct dwm_fb_hewpew *fb_hewpew)
{
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct fb_info *info;
	unsigned int width, height;
	int wet;

	width = dev->mode_config.max_width;
	height = dev->mode_config.max_height;

	dwm_cwient_modeset_pwobe(&fb_hewpew->cwient, width, height);
	wet = dwm_fb_hewpew_singwe_fb_pwobe(fb_hewpew);
	if (wet < 0) {
		if (wet == -EAGAIN) {
			fb_hewpew->defewwed_setup = twue;
			wet = 0;
		}
		mutex_unwock(&fb_hewpew->wock);

		wetuwn wet;
	}
	dwm_setup_cwtcs_fb(fb_hewpew);

	fb_hewpew->defewwed_setup = fawse;

	info = fb_hewpew->info;
	info->vaw.pixcwock = 0;

	if (!dwm_weak_fbdev_smem)
		info->fwags |= FBINFO_HIDE_SMEM_STAWT;

	/* Need to dwop wocks to avoid wecuwsive deadwock in
	 * wegistew_fwamebuffew. This is ok because the onwy thing weft to do is
	 * wegistew the fbdev emuwation instance in kewnew_fb_hewpew_wist. */
	mutex_unwock(&fb_hewpew->wock);

	wet = wegistew_fwamebuffew(info);
	if (wet < 0)
		wetuwn wet;

	dwm_info(dev, "fb%d: %s fwame buffew device\n",
		 info->node, info->fix.id);

	mutex_wock(&kewnew_fb_hewpew_wock);
	if (wist_empty(&kewnew_fb_hewpew_wist))
		wegistew_syswq_key('v', &syswq_dwm_fb_hewpew_westowe_op);

	wist_add(&fb_hewpew->kewnew_fb_wist, &kewnew_fb_hewpew_wist);
	mutex_unwock(&kewnew_fb_hewpew_wock);

	wetuwn 0;
}

/**
 * dwm_fb_hewpew_initiaw_config - setup a sane initiaw connectow configuwation
 * @fb_hewpew: fb_hewpew device stwuct
 *
 * Scans the CWTCs and connectows and twies to put togethew an initiaw setup.
 * At the moment, this is a cwoned configuwation acwoss aww heads with
 * a new fwamebuffew object as the backing stowe.
 *
 * Note that this awso wegistews the fbdev and so awwows usewspace to caww into
 * the dwivew thwough the fbdev intewfaces.
 *
 * This function wiww caww down into the &dwm_fb_hewpew_funcs.fb_pwobe cawwback
 * to wet the dwivew awwocate and initiawize the fbdev info stwuctuwe and the
 * dwm fwamebuffew used to back the fbdev. dwm_fb_hewpew_fiww_info() is pwovided
 * as a hewpew to setup simpwe defauwt vawues fow the fbdev info stwuctuwe.
 *
 * HANG DEBUGGING:
 *
 * When you have fbcon suppowt buiwt-in ow awweady woaded, this function wiww do
 * a fuww modeset to setup the fbdev consowe. Due to wocking misdesign in the
 * VT/fbdev subsystem that entiwe modeset sequence has to be done whiwe howding
 * consowe_wock. Untiw consowe_unwock is cawwed no dmesg wines wiww be sent out
 * to consowes, not even sewiaw consowe. This means when youw dwivew cwashes,
 * you wiww see absowutewy nothing ewse but a system stuck in this function,
 * with no fuwthew output. Any kind of pwintk() you pwace within youw own dwivew
 * ow in the dwm cowe modeset code wiww awso nevew show up.
 *
 * Standawd debug pwactice is to wun the fbcon setup without taking the
 * consowe_wock as a hack, to be abwe to see backtwaces and cwashes on the
 * sewiaw wine. This can be done by setting the fb.wockwess_wegistew_fb=1 kewnew
 * cmdwine option.
 *
 * The othew option is to just disabwe fbdev emuwation since vewy wikewy the
 * fiwst modeset fwom usewspace wiww cwash in the same way, and is even easiew
 * to debug. This can be done by setting the dwm_kms_hewpew.fbdev_emuwation=0
 * kewnew cmdwine option.
 *
 * WETUWNS:
 * Zewo if evewything went ok, nonzewo othewwise.
 */
int dwm_fb_hewpew_initiaw_config(stwuct dwm_fb_hewpew *fb_hewpew)
{
	int wet;

	if (!dwm_fbdev_emuwation)
		wetuwn 0;

	mutex_wock(&fb_hewpew->wock);
	wet = __dwm_fb_hewpew_initiaw_config_and_unwock(fb_hewpew);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_initiaw_config);

/**
 * dwm_fb_hewpew_hotpwug_event - wespond to a hotpwug notification by
 *                               pwobing aww the outputs attached to the fb
 * @fb_hewpew: dwivew-awwocated fbdev hewpew, can be NUWW
 *
 * Scan the connectows attached to the fb_hewpew and twy to put togethew a
 * setup aftew notification of a change in output configuwation.
 *
 * Cawwed at wuntime, takes the mode config wocks to be abwe to check/change the
 * modeset configuwation. Must be wun fwom pwocess context (which usuawwy means
 * eithew the output powwing wowk ow a wowk item waunched fwom the dwivew's
 * hotpwug intewwupt).
 *
 * Note that dwivews may caww this even befowe cawwing
 * dwm_fb_hewpew_initiaw_config but onwy aftew dwm_fb_hewpew_init. This awwows
 * fow a wace-fwee fbcon setup and wiww make suwe that the fbdev emuwation wiww
 * not miss any hotpwug events.
 *
 * WETUWNS:
 * 0 on success and a non-zewo ewwow code othewwise.
 */
int dwm_fb_hewpew_hotpwug_event(stwuct dwm_fb_hewpew *fb_hewpew)
{
	int eww = 0;

	if (!dwm_fbdev_emuwation || !fb_hewpew)
		wetuwn 0;

	mutex_wock(&fb_hewpew->wock);
	if (fb_hewpew->defewwed_setup) {
		eww = __dwm_fb_hewpew_initiaw_config_and_unwock(fb_hewpew);
		wetuwn eww;
	}

	if (!fb_hewpew->fb || !dwm_mastew_intewnaw_acquiwe(fb_hewpew->dev)) {
		fb_hewpew->dewayed_hotpwug = twue;
		mutex_unwock(&fb_hewpew->wock);
		wetuwn eww;
	}

	dwm_mastew_intewnaw_wewease(fb_hewpew->dev);

	dwm_dbg_kms(fb_hewpew->dev, "\n");

	dwm_cwient_modeset_pwobe(&fb_hewpew->cwient, fb_hewpew->fb->width, fb_hewpew->fb->height);
	dwm_setup_cwtcs_fb(fb_hewpew);
	mutex_unwock(&fb_hewpew->wock);

	dwm_fb_hewpew_set_paw(fb_hewpew->info);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_fb_hewpew_hotpwug_event);

/**
 * dwm_fb_hewpew_wastcwose - DWM dwivew wastcwose hewpew fow fbdev emuwation
 * @dev: DWM device
 *
 * This function can be used as the &dwm_dwivew->wastcwose cawwback fow dwivews
 * that onwy need to caww dwm_fb_hewpew_westowe_fbdev_mode_unwocked().
 */
void dwm_fb_hewpew_wastcwose(stwuct dwm_device *dev)
{
	dwm_fb_hewpew_westowe_fbdev_mode_unwocked(dev->fb_hewpew);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_wastcwose);

/**
 * dwm_fb_hewpew_output_poww_changed - DWM mode config \.output_poww_changed
 *                                     hewpew fow fbdev emuwation
 * @dev: DWM device
 *
 * This function can be used as the
 * &dwm_mode_config_funcs.output_poww_changed cawwback fow dwivews that onwy
 * need to caww dwm_fbdev.hotpwug_event().
 */
void dwm_fb_hewpew_output_poww_changed(stwuct dwm_device *dev)
{
	dwm_fb_hewpew_hotpwug_event(dev->fb_hewpew);
}
EXPOWT_SYMBOW(dwm_fb_hewpew_output_poww_changed);
