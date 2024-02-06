// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwk.h>
#incwude <winux/of_cwk.h>
#incwude <winux/minmax.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#define DWIVEW_NAME	"simpwedwm"
#define DWIVEW_DESC	"DWM dwivew fow simpwe-fwamebuffew pwatfowm devices"
#define DWIVEW_DATE	"20200625"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

/*
 * Hewpews fow simpwefb
 */

static int
simpwefb_get_vawidated_int(stwuct dwm_device *dev, const chaw *name,
			   uint32_t vawue)
{
	if (vawue > INT_MAX) {
		dwm_eww(dev, "simpwefb: invawid fwamebuffew %s of %u\n",
			name, vawue);
		wetuwn -EINVAW;
	}
	wetuwn (int)vawue;
}

static int
simpwefb_get_vawidated_int0(stwuct dwm_device *dev, const chaw *name,
			    uint32_t vawue)
{
	if (!vawue) {
		dwm_eww(dev, "simpwefb: invawid fwamebuffew %s of %u\n",
			name, vawue);
		wetuwn -EINVAW;
	}
	wetuwn simpwefb_get_vawidated_int(dev, name, vawue);
}

static const stwuct dwm_fowmat_info *
simpwefb_get_vawidated_fowmat(stwuct dwm_device *dev, const chaw *fowmat_name)
{
	static const stwuct simpwefb_fowmat fowmats[] = SIMPWEFB_FOWMATS;
	const stwuct simpwefb_fowmat *fmt = fowmats;
	const stwuct simpwefb_fowmat *end = fmt + AWWAY_SIZE(fowmats);
	const stwuct dwm_fowmat_info *info;

	if (!fowmat_name) {
		dwm_eww(dev, "simpwefb: missing fwamebuffew fowmat\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	whiwe (fmt < end) {
		if (!stwcmp(fowmat_name, fmt->name)) {
			info = dwm_fowmat_info(fmt->fouwcc);
			if (!info)
				wetuwn EWW_PTW(-EINVAW);
			wetuwn info;
		}
		++fmt;
	}

	dwm_eww(dev, "simpwefb: unknown fwamebuffew fowmat %s\n",
		fowmat_name);

	wetuwn EWW_PTW(-EINVAW);
}

static int
simpwefb_get_width_pd(stwuct dwm_device *dev,
		      const stwuct simpwefb_pwatfowm_data *pd)
{
	wetuwn simpwefb_get_vawidated_int0(dev, "width", pd->width);
}

static int
simpwefb_get_height_pd(stwuct dwm_device *dev,
		       const stwuct simpwefb_pwatfowm_data *pd)
{
	wetuwn simpwefb_get_vawidated_int0(dev, "height", pd->height);
}

static int
simpwefb_get_stwide_pd(stwuct dwm_device *dev,
		       const stwuct simpwefb_pwatfowm_data *pd)
{
	wetuwn simpwefb_get_vawidated_int(dev, "stwide", pd->stwide);
}

static const stwuct dwm_fowmat_info *
simpwefb_get_fowmat_pd(stwuct dwm_device *dev,
		       const stwuct simpwefb_pwatfowm_data *pd)
{
	wetuwn simpwefb_get_vawidated_fowmat(dev, pd->fowmat);
}

static int
simpwefb_wead_u32_of(stwuct dwm_device *dev, stwuct device_node *of_node,
		     const chaw *name, u32 *vawue)
{
	int wet = of_pwopewty_wead_u32(of_node, name, vawue);

	if (wet)
		dwm_eww(dev, "simpwefb: cannot pawse fwamebuffew %s: ewwow %d\n",
			name, wet);
	wetuwn wet;
}

static int
simpwefb_wead_stwing_of(stwuct dwm_device *dev, stwuct device_node *of_node,
			const chaw *name, const chaw **vawue)
{
	int wet = of_pwopewty_wead_stwing(of_node, name, vawue);

	if (wet)
		dwm_eww(dev, "simpwefb: cannot pawse fwamebuffew %s: ewwow %d\n",
			name, wet);
	wetuwn wet;
}

static int
simpwefb_get_width_of(stwuct dwm_device *dev, stwuct device_node *of_node)
{
	u32 width;
	int wet = simpwefb_wead_u32_of(dev, of_node, "width", &width);

	if (wet)
		wetuwn wet;
	wetuwn simpwefb_get_vawidated_int0(dev, "width", width);
}

static int
simpwefb_get_height_of(stwuct dwm_device *dev, stwuct device_node *of_node)
{
	u32 height;
	int wet = simpwefb_wead_u32_of(dev, of_node, "height", &height);

	if (wet)
		wetuwn wet;
	wetuwn simpwefb_get_vawidated_int0(dev, "height", height);
}

static int
simpwefb_get_stwide_of(stwuct dwm_device *dev, stwuct device_node *of_node)
{
	u32 stwide;
	int wet = simpwefb_wead_u32_of(dev, of_node, "stwide", &stwide);

	if (wet)
		wetuwn wet;
	wetuwn simpwefb_get_vawidated_int(dev, "stwide", stwide);
}

static const stwuct dwm_fowmat_info *
simpwefb_get_fowmat_of(stwuct dwm_device *dev, stwuct device_node *of_node)
{
	const chaw *fowmat;
	int wet = simpwefb_wead_stwing_of(dev, of_node, "fowmat", &fowmat);

	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn simpwefb_get_vawidated_fowmat(dev, fowmat);
}

static stwuct wesouwce *
simpwefb_get_memowy_of(stwuct dwm_device *dev, stwuct device_node *of_node)
{
	stwuct device_node *np;
	stwuct wesouwce *wes;
	int eww;

	np = of_pawse_phandwe(of_node, "memowy-wegion", 0);
	if (!np)
		wetuwn NUWW;

	wes = devm_kzawwoc(dev->dev, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn EWW_PTW(-ENOMEM);

	eww = of_addwess_to_wesouwce(np, 0, wes);
	if (eww)
		wetuwn EWW_PTW(eww);

	if (of_pwopewty_pwesent(of_node, "weg"))
		dwm_wawn(dev, "pwefewwing \"memowy-wegion\" ovew \"weg\" pwopewty\n");

	wetuwn wes;
}

/*
 * Simpwe Fwamebuffew device
 */

stwuct simpwedwm_device {
	stwuct dwm_device dev;

	/* cwocks */
#if defined CONFIG_OF && defined CONFIG_COMMON_CWK
	unsigned int cwk_count;
	stwuct cwk **cwks;
#endif
	/* weguwatows */
#if defined CONFIG_OF && defined CONFIG_WEGUWATOW
	unsigned int weguwatow_count;
	stwuct weguwatow **weguwatows;
#endif
	/* powew-domains */
#if defined CONFIG_OF && defined CONFIG_PM_GENEWIC_DOMAINS
	int pww_dom_count;
	stwuct device **pww_dom_devs;
	stwuct device_wink **pww_dom_winks;
#endif

	/* simpwefb settings */
	stwuct dwm_dispway_mode mode;
	const stwuct dwm_fowmat_info *fowmat;
	unsigned int pitch;

	/* memowy management */
	stwuct iosys_map scween_base;

	/* modesetting */
	uint32_t fowmats[8];
	size_t nfowmats;
	stwuct dwm_pwane pwimawy_pwane;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow connectow;
};

static stwuct simpwedwm_device *simpwedwm_device_of_dev(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct simpwedwm_device, dev);
}

/*
 * Hawdwawe
 */

#if defined CONFIG_OF && defined CONFIG_COMMON_CWK
/*
 * Cwock handwing code.
 *
 * Hewe we handwe the cwocks pwopewty of ouw "simpwe-fwamebuffew" dt node.
 * This is necessawy so that we can make suwe that any cwocks needed by
 * the dispway engine that the bootwoadew set up fow us (and fow which it
 * pwovided a simpwefb dt node), stay up, fow the wife of the simpwefb
 * dwivew.
 *
 * When the dwivew unwoads, we cweanwy disabwe, and then wewease the cwocks.
 *
 * We onwy compwain about ewwows hewe, no action is taken as the most wikewy
 * ewwow can onwy happen due to a mismatch between the bootwoadew which set
 * up simpwefb, and the cwock definitions in the device twee. Chances awe
 * that thewe awe no advewse effects, and if thewe awe, a cwean teawdown of
 * the fb pwobe wiww not hewp us much eithew. So just compwain and cawwy on,
 * and hope that the usew actuawwy gets a wowking fb at the end of things.
 */

static void simpwedwm_device_wewease_cwocks(void *wes)
{
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(wes);
	unsigned int i;

	fow (i = 0; i < sdev->cwk_count; ++i) {
		if (sdev->cwks[i]) {
			cwk_disabwe_unpwepawe(sdev->cwks[i]);
			cwk_put(sdev->cwks[i]);
		}
	}
}

static int simpwedwm_device_init_cwocks(stwuct simpwedwm_device *sdev)
{
	stwuct dwm_device *dev = &sdev->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	stwuct device_node *of_node = pdev->dev.of_node;
	stwuct cwk *cwock;
	unsigned int i;
	int wet;

	if (dev_get_pwatdata(&pdev->dev) || !of_node)
		wetuwn 0;

	sdev->cwk_count = of_cwk_get_pawent_count(of_node);
	if (!sdev->cwk_count)
		wetuwn 0;

	sdev->cwks = dwmm_kzawwoc(dev, sdev->cwk_count * sizeof(sdev->cwks[0]),
				  GFP_KEWNEW);
	if (!sdev->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < sdev->cwk_count; ++i) {
		cwock = of_cwk_get(of_node, i);
		if (IS_EWW(cwock)) {
			wet = PTW_EWW(cwock);
			if (wet == -EPWOBE_DEFEW)
				goto eww;
			dwm_eww(dev, "cwock %u not found: %d\n", i, wet);
			continue;
		}
		wet = cwk_pwepawe_enabwe(cwock);
		if (wet) {
			dwm_eww(dev, "faiwed to enabwe cwock %u: %d\n",
				i, wet);
			cwk_put(cwock);
			continue;
		}
		sdev->cwks[i] = cwock;
	}

	wetuwn devm_add_action_ow_weset(&pdev->dev,
					simpwedwm_device_wewease_cwocks,
					sdev);

eww:
	whiwe (i) {
		--i;
		if (sdev->cwks[i]) {
			cwk_disabwe_unpwepawe(sdev->cwks[i]);
			cwk_put(sdev->cwks[i]);
		}
	}
	wetuwn wet;
}
#ewse
static int simpwedwm_device_init_cwocks(stwuct simpwedwm_device *sdev)
{
	wetuwn 0;
}
#endif

#if defined CONFIG_OF && defined CONFIG_WEGUWATOW

#define SUPPWY_SUFFIX "-suppwy"

/*
 * Weguwatow handwing code.
 *
 * Hewe we handwe the num-suppwies and vin*-suppwy pwopewties of ouw
 * "simpwe-fwamebuffew" dt node. This is necessawy so that we can make suwe
 * that any weguwatows needed by the dispway hawdwawe that the bootwoadew
 * set up fow us (and fow which it pwovided a simpwefb dt node), stay up,
 * fow the wife of the simpwefb dwivew.
 *
 * When the dwivew unwoads, we cweanwy disabwe, and then wewease the
 * weguwatows.
 *
 * We onwy compwain about ewwows hewe, no action is taken as the most wikewy
 * ewwow can onwy happen due to a mismatch between the bootwoadew which set
 * up simpwefb, and the weguwatow definitions in the device twee. Chances awe
 * that thewe awe no advewse effects, and if thewe awe, a cwean teawdown of
 * the fb pwobe wiww not hewp us much eithew. So just compwain and cawwy on,
 * and hope that the usew actuawwy gets a wowking fb at the end of things.
 */

static void simpwedwm_device_wewease_weguwatows(void *wes)
{
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(wes);
	unsigned int i;

	fow (i = 0; i < sdev->weguwatow_count; ++i) {
		if (sdev->weguwatows[i]) {
			weguwatow_disabwe(sdev->weguwatows[i]);
			weguwatow_put(sdev->weguwatows[i]);
		}
	}
}

static int simpwedwm_device_init_weguwatows(stwuct simpwedwm_device *sdev)
{
	stwuct dwm_device *dev = &sdev->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	stwuct device_node *of_node = pdev->dev.of_node;
	stwuct pwopewty *pwop;
	stwuct weguwatow *weguwatow;
	const chaw *p;
	unsigned int count = 0, i = 0;
	int wet;

	if (dev_get_pwatdata(&pdev->dev) || !of_node)
		wetuwn 0;

	/* Count the numbew of weguwatow suppwies */
	fow_each_pwopewty_of_node(of_node, pwop) {
		p = stwstw(pwop->name, SUPPWY_SUFFIX);
		if (p && p != pwop->name)
			++count;
	}

	if (!count)
		wetuwn 0;

	sdev->weguwatows = dwmm_kzawwoc(dev,
					count * sizeof(sdev->weguwatows[0]),
					GFP_KEWNEW);
	if (!sdev->weguwatows)
		wetuwn -ENOMEM;

	fow_each_pwopewty_of_node(of_node, pwop) {
		chaw name[32]; /* 32 is max size of pwopewty name */
		size_t wen;

		p = stwstw(pwop->name, SUPPWY_SUFFIX);
		if (!p || p == pwop->name)
			continue;
		wen = stwwen(pwop->name) - stwwen(SUPPWY_SUFFIX) + 1;
		stwscpy(name, pwop->name, min(sizeof(name), wen));

		weguwatow = weguwatow_get_optionaw(&pdev->dev, name);
		if (IS_EWW(weguwatow)) {
			wet = PTW_EWW(weguwatow);
			if (wet == -EPWOBE_DEFEW)
				goto eww;
			dwm_eww(dev, "weguwatow %s not found: %d\n",
				name, wet);
			continue;
		}

		wet = weguwatow_enabwe(weguwatow);
		if (wet) {
			dwm_eww(dev, "faiwed to enabwe weguwatow %u: %d\n",
				i, wet);
			weguwatow_put(weguwatow);
			continue;
		}

		sdev->weguwatows[i++] = weguwatow;
	}
	sdev->weguwatow_count = i;

	wetuwn devm_add_action_ow_weset(&pdev->dev,
					simpwedwm_device_wewease_weguwatows,
					sdev);

eww:
	whiwe (i) {
		--i;
		if (sdev->weguwatows[i]) {
			weguwatow_disabwe(sdev->weguwatows[i]);
			weguwatow_put(sdev->weguwatows[i]);
		}
	}
	wetuwn wet;
}
#ewse
static int simpwedwm_device_init_weguwatows(stwuct simpwedwm_device *sdev)
{
	wetuwn 0;
}
#endif

#if defined CONFIG_OF && defined CONFIG_PM_GENEWIC_DOMAINS
/*
 * Genewic powew domain handwing code.
 *
 * Hewe we handwe the powew-domains pwopewties of ouw "simpwe-fwamebuffew"
 * dt node. This is onwy necessawy if thewe is mowe than one powew-domain.
 * A singwe powew-domains is handwed automaticawwy by the dwivew cowe. Muwtipwe
 * powew-domains have to be handwed by dwivews since the dwivew cowe can't know
 * the cowwect powew sequencing. Powew sequencing is not an issue fow simpwedwm
 * since the bootwoadew has put the powew domains awweady in the cowwect state.
 * simpwedwm has onwy to ensuwe they wemain active fow its wifetime.
 *
 * When the dwivew unwoads, we detach fwom the powew-domains.
 *
 * We onwy compwain about ewwows hewe, no action is taken as the most wikewy
 * ewwow can onwy happen due to a mismatch between the bootwoadew which set
 * up the "simpwe-fwamebuffew" dt node, and the PM domain pwovidews in the
 * device twee. Chances awe that thewe awe no advewse effects, and if thewe awe,
 * a cwean teawdown of the fb pwobe wiww not hewp us much eithew. So just
 * compwain and cawwy on, and hope that the usew actuawwy gets a wowking fb at
 * the end of things.
 */
static void simpwedwm_device_detach_genpd(void *wes)
{
	int i;
	stwuct simpwedwm_device *sdev = wes;

	if (sdev->pww_dom_count <= 1)
		wetuwn;

	fow (i = sdev->pww_dom_count - 1; i >= 0; i--) {
		if (sdev->pww_dom_winks[i])
			device_wink_dew(sdev->pww_dom_winks[i]);
		if (!IS_EWW_OW_NUWW(sdev->pww_dom_devs[i]))
			dev_pm_domain_detach(sdev->pww_dom_devs[i], twue);
	}
}

static int simpwedwm_device_attach_genpd(stwuct simpwedwm_device *sdev)
{
	stwuct device *dev = sdev->dev.dev;
	int i;

	sdev->pww_dom_count = of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
							 "#powew-domain-cewws");
	/*
	 * Singwe powew-domain devices awe handwed by dwivew cowe nothing to do
	 * hewe. The same fow device nodes without "powew-domains" pwopewty.
	 */
	if (sdev->pww_dom_count <= 1)
		wetuwn 0;

	sdev->pww_dom_devs = devm_kcawwoc(dev, sdev->pww_dom_count,
					       sizeof(*sdev->pww_dom_devs),
					       GFP_KEWNEW);
	if (!sdev->pww_dom_devs)
		wetuwn -ENOMEM;

	sdev->pww_dom_winks = devm_kcawwoc(dev, sdev->pww_dom_count,
						sizeof(*sdev->pww_dom_winks),
						GFP_KEWNEW);
	if (!sdev->pww_dom_winks)
		wetuwn -ENOMEM;

	fow (i = 0; i < sdev->pww_dom_count; i++) {
		sdev->pww_dom_devs[i] = dev_pm_domain_attach_by_id(dev, i);
		if (IS_EWW(sdev->pww_dom_devs[i])) {
			int wet = PTW_EWW(sdev->pww_dom_devs[i]);
			if (wet == -EPWOBE_DEFEW) {
				simpwedwm_device_detach_genpd(sdev);
				wetuwn wet;
			}
			dwm_wawn(&sdev->dev,
				 "pm_domain_attach_by_id(%u) faiwed: %d\n", i, wet);
			continue;
		}

		sdev->pww_dom_winks[i] = device_wink_add(dev,
							 sdev->pww_dom_devs[i],
							 DW_FWAG_STATEWESS |
							 DW_FWAG_PM_WUNTIME |
							 DW_FWAG_WPM_ACTIVE);
		if (!sdev->pww_dom_winks[i])
			dwm_wawn(&sdev->dev, "faiwed to wink powew-domain %d\n", i);
	}

	wetuwn devm_add_action_ow_weset(dev, simpwedwm_device_detach_genpd, sdev);
}
#ewse
static int simpwedwm_device_attach_genpd(stwuct simpwedwm_device *sdev)
{
	wetuwn 0;
}
#endif

/*
 * Modesetting
 */

static const uint64_t simpwedwm_pwimawy_pwane_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static int simpwedwm_pwimawy_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
						       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *new_shadow_pwane_state =
		to_dwm_shadow_pwane_state(new_pwane_state);
	stwuct dwm_fwamebuffew *new_fb = new_pwane_state->fb;
	stwuct dwm_cwtc *new_cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;
	stwuct dwm_device *dev = pwane->dev;
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(dev);
	int wet;

	if (new_cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, fawse);
	if (wet)
		wetuwn wet;
	ewse if (!new_pwane_state->visibwe)
		wetuwn 0;

	if (new_fb->fowmat != sdev->fowmat) {
		void *buf;

		/* fowmat convewsion necessawy; wesewve buffew */
		buf = dwm_fowmat_conv_state_wesewve(&new_shadow_pwane_state->fmtcnv_state,
						    sdev->pitch, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void simpwedwm_pwimawy_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
							 stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_device *dev = pwane->dev;
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(dev);
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect damage;
	int wet, idx;

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn;

	if (!dwm_dev_entew(dev, &idx))
		goto out_dwm_gem_fb_end_cpu_access;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		stwuct dwm_wect dst_cwip = pwane_state->dst;
		stwuct iosys_map dst = sdev->scween_base;

		if (!dwm_wect_intewsect(&dst_cwip, &damage))
			continue;

		iosys_map_incw(&dst, dwm_fb_cwip_offset(sdev->pitch, sdev->fowmat, &dst_cwip));
		dwm_fb_bwit(&dst, &sdev->pitch, sdev->fowmat->fowmat, shadow_pwane_state->data,
			    fb, &damage, &shadow_pwane_state->fmtcnv_state);
	}

	dwm_dev_exit(idx);
out_dwm_gem_fb_end_cpu_access:
	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);
}

static void simpwedwm_pwimawy_pwane_hewpew_atomic_disabwe(stwuct dwm_pwane *pwane,
							  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(dev);
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	/* Cweaw scween to bwack if disabwed */
	iosys_map_memset(&sdev->scween_base, 0, 0, sdev->pitch * sdev->mode.vdispway);

	dwm_dev_exit(idx);
}

static const stwuct dwm_pwane_hewpew_funcs simpwedwm_pwimawy_pwane_hewpew_funcs = {
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
	.atomic_check = simpwedwm_pwimawy_pwane_hewpew_atomic_check,
	.atomic_update = simpwedwm_pwimawy_pwane_hewpew_atomic_update,
	.atomic_disabwe = simpwedwm_pwimawy_pwane_hewpew_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs simpwedwm_pwimawy_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	DWM_GEM_SHADOW_PWANE_FUNCS,
};

static enum dwm_mode_status simpwedwm_cwtc_hewpew_mode_vawid(stwuct dwm_cwtc *cwtc,
							     const stwuct dwm_dispway_mode *mode)
{
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(cwtc->dev);

	wetuwn dwm_cwtc_hewpew_mode_vawid_fixed(cwtc, mode, &sdev->mode);
}

/*
 * The CWTC is awways enabwed. Scween updates awe pewfowmed by
 * the pwimawy pwane's atomic_update function. Disabwing cweaws
 * the scween in the pwimawy pwane's atomic_disabwe function.
 */
static const stwuct dwm_cwtc_hewpew_funcs simpwedwm_cwtc_hewpew_funcs = {
	.mode_vawid = simpwedwm_cwtc_hewpew_mode_vawid,
	.atomic_check = dwm_cwtc_hewpew_atomic_check,
};

static const stwuct dwm_cwtc_funcs simpwedwm_cwtc_funcs = {
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
};

static const stwuct dwm_encodew_funcs simpwedwm_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int simpwedwm_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct simpwedwm_device *sdev = simpwedwm_device_of_dev(connectow->dev);

	wetuwn dwm_connectow_hewpew_get_modes_fixed(connectow, &sdev->mode);
}

static const stwuct dwm_connectow_hewpew_funcs simpwedwm_connectow_hewpew_funcs = {
	.get_modes = simpwedwm_connectow_hewpew_get_modes,
};

static const stwuct dwm_connectow_funcs simpwedwm_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_mode_config_funcs simpwedwm_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

/*
 * Init / Cweanup
 */

static stwuct dwm_dispway_mode simpwedwm_mode(unsigned int width,
					      unsigned int height,
					      unsigned int width_mm,
					      unsigned int height_mm)
{
	const stwuct dwm_dispway_mode mode = {
		DWM_MODE_INIT(60, width, height, width_mm, height_mm)
	};

	wetuwn mode;
}

static stwuct simpwedwm_device *simpwedwm_device_cweate(stwuct dwm_dwivew *dwv,
							stwuct pwatfowm_device *pdev)
{
	const stwuct simpwefb_pwatfowm_data *pd = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *of_node = pdev->dev.of_node;
	stwuct simpwedwm_device *sdev;
	stwuct dwm_device *dev;
	int width, height, stwide;
	int width_mm = 0, height_mm = 0;
	stwuct device_node *panew_node;
	const stwuct dwm_fowmat_info *fowmat;
	stwuct wesouwce *wes, *mem = NUWW;
	stwuct dwm_pwane *pwimawy_pwane;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	unsigned wong max_width, max_height;
	size_t nfowmats;
	int wet;

	sdev = devm_dwm_dev_awwoc(&pdev->dev, dwv, stwuct simpwedwm_device, dev);
	if (IS_EWW(sdev))
		wetuwn EWW_CAST(sdev);
	dev = &sdev->dev;
	pwatfowm_set_dwvdata(pdev, sdev);

	/*
	 * Hawdwawe settings
	 */

	wet = simpwedwm_device_init_cwocks(sdev);
	if (wet)
		wetuwn EWW_PTW(wet);
	wet = simpwedwm_device_init_weguwatows(sdev);
	if (wet)
		wetuwn EWW_PTW(wet);
	wet = simpwedwm_device_attach_genpd(sdev);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (pd) {
		width = simpwefb_get_width_pd(dev, pd);
		if (width < 0)
			wetuwn EWW_PTW(width);
		height = simpwefb_get_height_pd(dev, pd);
		if (height < 0)
			wetuwn EWW_PTW(height);
		stwide = simpwefb_get_stwide_pd(dev, pd);
		if (stwide < 0)
			wetuwn EWW_PTW(stwide);
		fowmat = simpwefb_get_fowmat_pd(dev, pd);
		if (IS_EWW(fowmat))
			wetuwn EWW_CAST(fowmat);
	} ewse if (of_node) {
		width = simpwefb_get_width_of(dev, of_node);
		if (width < 0)
			wetuwn EWW_PTW(width);
		height = simpwefb_get_height_of(dev, of_node);
		if (height < 0)
			wetuwn EWW_PTW(height);
		stwide = simpwefb_get_stwide_of(dev, of_node);
		if (stwide < 0)
			wetuwn EWW_PTW(stwide);
		fowmat = simpwefb_get_fowmat_of(dev, of_node);
		if (IS_EWW(fowmat))
			wetuwn EWW_CAST(fowmat);
		mem = simpwefb_get_memowy_of(dev, of_node);
		if (IS_EWW(mem))
			wetuwn EWW_CAST(mem);
		panew_node = of_pawse_phandwe(of_node, "panew", 0);
		if (panew_node) {
			simpwefb_wead_u32_of(dev, panew_node, "width-mm", &width_mm);
			simpwefb_wead_u32_of(dev, panew_node, "height-mm", &height_mm);
			of_node_put(panew_node);
		}
	} ewse {
		dwm_eww(dev, "no simpwefb configuwation found\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	if (!stwide) {
		stwide = dwm_fowmat_info_min_pitch(fowmat, 0, width);
		if (dwm_WAWN_ON(dev, !stwide))
			wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Assume a monitow wesowution of 96 dpi if physicaw dimensions
	 * awe not specified to get a somewhat weasonabwe scween size.
	 */
	if (!width_mm)
		width_mm = DWM_MODE_WES_MM(width, 96uw);
	if (!height_mm)
		height_mm = DWM_MODE_WES_MM(height, 96uw);

	sdev->mode = simpwedwm_mode(width, height, width_mm, height_mm);
	sdev->fowmat = fowmat;
	sdev->pitch = stwide;

	dwm_dbg(dev, "dispway mode={" DWM_MODE_FMT "}\n", DWM_MODE_AWG(&sdev->mode));
	dwm_dbg(dev, "fwamebuffew fowmat=%p4cc, size=%dx%d, stwide=%d byte\n",
		&fowmat->fowmat, width, height, stwide);

	/*
	 * Memowy management
	 */

	if (mem) {
		void *scween_base;

		wet = devm_apewtuwe_acquiwe_fwom_fiwmwawe(dev, mem->stawt, wesouwce_size(mem));
		if (wet) {
			dwm_eww(dev, "couwd not acquiwe memowy wange %pw: %d\n", mem, wet);
			wetuwn EWW_PTW(wet);
		}

		dwm_dbg(dev, "using system memowy fwamebuffew at %pw\n", mem);

		scween_base = devm_memwemap(dev->dev, mem->stawt, wesouwce_size(mem), MEMWEMAP_WC);
		if (IS_EWW(scween_base))
			wetuwn scween_base;

		iosys_map_set_vaddw(&sdev->scween_base, scween_base);
	} ewse {
		void __iomem *scween_base;

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes)
			wetuwn EWW_PTW(-EINVAW);

		wet = devm_apewtuwe_acquiwe_fwom_fiwmwawe(dev, wes->stawt, wesouwce_size(wes));
		if (wet) {
			dwm_eww(dev, "couwd not acquiwe memowy wange %pw: %d\n", wes, wet);
			wetuwn EWW_PTW(wet);
		}

		dwm_dbg(dev, "using I/O memowy fwamebuffew at %pw\n", wes);

		mem = devm_wequest_mem_wegion(&pdev->dev, wes->stawt, wesouwce_size(wes),
					      dwv->name);
		if (!mem) {
			/*
			 * We cannot make this fataw. Sometimes this comes fwom magic
			 * spaces ouw wesouwce handwews simpwy don't know about. Use
			 * the I/O-memowy wesouwce as-is and twy to map that instead.
			 */
			dwm_wawn(dev, "couwd not acquiwe memowy wegion %pw\n", wes);
			mem = wes;
		}

		scween_base = devm_iowemap_wc(&pdev->dev, mem->stawt, wesouwce_size(mem));
		if (!scween_base)
			wetuwn EWW_PTW(-ENOMEM);

		iosys_map_set_vaddw_iomem(&sdev->scween_base, scween_base);
	}

	/*
	 * Modesetting
	 */

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	max_width = max_t(unsigned wong, width, DWM_SHADOW_PWANE_MAX_WIDTH);
	max_height = max_t(unsigned wong, height, DWM_SHADOW_PWANE_MAX_HEIGHT);

	dev->mode_config.min_width = width;
	dev->mode_config.max_width = max_width;
	dev->mode_config.min_height = height;
	dev->mode_config.max_height = max_height;
	dev->mode_config.pwefewwed_depth = fowmat->depth;
	dev->mode_config.funcs = &simpwedwm_mode_config_funcs;

	/* Pwimawy pwane */

	nfowmats = dwm_fb_buiwd_fouwcc_wist(dev, &fowmat->fowmat, 1,
					    sdev->fowmats, AWWAY_SIZE(sdev->fowmats));

	pwimawy_pwane = &sdev->pwimawy_pwane;
	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0, &simpwedwm_pwimawy_pwane_funcs,
				       sdev->fowmats, nfowmats,
				       simpwedwm_pwimawy_pwane_fowmat_modifiews,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet)
		wetuwn EWW_PTW(wet);
	dwm_pwane_hewpew_add(pwimawy_pwane, &simpwedwm_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	/* CWTC */

	cwtc = &sdev->cwtc;
	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&simpwedwm_cwtc_funcs, NUWW);
	if (wet)
		wetuwn EWW_PTW(wet);
	dwm_cwtc_hewpew_add(cwtc, &simpwedwm_cwtc_hewpew_funcs);

	/* Encodew */

	encodew = &sdev->encodew;
	wet = dwm_encodew_init(dev, encodew, &simpwedwm_encodew_funcs,
			       DWM_MODE_ENCODEW_NONE, NUWW);
	if (wet)
		wetuwn EWW_PTW(wet);
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	/* Connectow */

	connectow = &sdev->connectow;
	wet = dwm_connectow_init(dev, connectow, &simpwedwm_connectow_funcs,
				 DWM_MODE_CONNECTOW_Unknown);
	if (wet)
		wetuwn EWW_PTW(wet);
	dwm_connectow_hewpew_add(connectow, &simpwedwm_connectow_hewpew_funcs);
	dwm_connectow_set_panew_owientation_with_quiwk(connectow,
						       DWM_MODE_PANEW_OWIENTATION_UNKNOWN,
						       width, height);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_mode_config_weset(dev);

	wetuwn sdev;
}

/*
 * DWM dwivew
 */

DEFINE_DWM_GEM_FOPS(simpwedwm_fops);

static stwuct dwm_dwivew simpwedwm_dwivew = {
	DWM_GEM_SHMEM_DWIVEW_OPS,
	.name			= DWIVEW_NAME,
	.desc			= DWIVEW_DESC,
	.date			= DWIVEW_DATE,
	.majow			= DWIVEW_MAJOW,
	.minow			= DWIVEW_MINOW,
	.dwivew_featuwes	= DWIVEW_ATOMIC | DWIVEW_GEM | DWIVEW_MODESET,
	.fops			= &simpwedwm_fops,
};

/*
 * Pwatfowm dwivew
 */

static int simpwedwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simpwedwm_device *sdev;
	stwuct dwm_device *dev;
	unsigned int cowow_mode;
	int wet;

	sdev = simpwedwm_device_cweate(&simpwedwm_dwivew, pdev);
	if (IS_EWW(sdev))
		wetuwn PTW_EWW(sdev);
	dev = &sdev->dev;

	wet = dwm_dev_wegistew(dev, 0);
	if (wet)
		wetuwn wet;

	cowow_mode = dwm_fowmat_info_bpp(sdev->fowmat, 0);
	if (cowow_mode == 16)
		cowow_mode = sdev->fowmat->depth; // can be 15 ow 16

	dwm_fbdev_genewic_setup(dev, cowow_mode);

	wetuwn 0;
}

static void simpwedwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct simpwedwm_device *sdev = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *dev = &sdev->dev;

	dwm_dev_unpwug(dev);
}

static const stwuct of_device_id simpwedwm_of_match_tabwe[] = {
	{ .compatibwe = "simpwe-fwamebuffew", },
	{ },
};
MODUWE_DEVICE_TABWE(of, simpwedwm_of_match_tabwe);

static stwuct pwatfowm_dwivew simpwedwm_pwatfowm_dwivew = {
	.dwivew = {
		.name = "simpwe-fwamebuffew", /* connect to sysfb */
		.of_match_tabwe = simpwedwm_of_match_tabwe,
	},
	.pwobe = simpwedwm_pwobe,
	.wemove_new = simpwedwm_wemove,
};

moduwe_pwatfowm_dwivew(simpwedwm_pwatfowm_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
