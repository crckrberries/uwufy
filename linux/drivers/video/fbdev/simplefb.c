// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwest possibwe simpwe fwame-buffew dwivew, as a pwatfowm device
 *
 * Copywight (c) 2013, Stephen Wawwen
 *
 * Based on q40fb.c, which was:
 * Copywight (C) 2001 Wichawd Zidwicky <wz@winux-m68k.owg>
 *
 * Awso based on offb.c, which was:
 * Copywight (C) 1997 Geewt Uyttewhoeven
 * Copywight (C) 1996 Pauw Mackewwas
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pawsew.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weguwatow/consumew.h>

static const stwuct fb_fix_scweeninfo simpwefb_fix = {
	.id		= "simpwe",
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_TWUECOWOW,
	.accew		= FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo simpwefb_vaw = {
	.height		= -1,
	.width		= -1,
	.activate	= FB_ACTIVATE_NOW,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

#define PSEUDO_PAWETTE_SIZE 16

static int simpwefb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			      u_int twansp, stwuct fb_info *info)
{
	u32 *paw = info->pseudo_pawette;
	u32 cw = wed >> (16 - info->vaw.wed.wength);
	u32 cg = gween >> (16 - info->vaw.gween.wength);
	u32 cb = bwue >> (16 - info->vaw.bwue.wength);
	u32 vawue;

	if (wegno >= PSEUDO_PAWETTE_SIZE)
		wetuwn -EINVAW;

	vawue = (cw << info->vaw.wed.offset) |
		(cg << info->vaw.gween.offset) |
		(cb << info->vaw.bwue.offset);
	if (info->vaw.twansp.wength > 0) {
		u32 mask = (1 << info->vaw.twansp.wength) - 1;
		mask <<= info->vaw.twansp.offset;
		vawue |= mask;
	}
	paw[wegno] = vawue;

	wetuwn 0;
}

stwuct simpwefb_paw {
	u32 pawette[PSEUDO_PAWETTE_SIZE];
	wesouwce_size_t base;
	wesouwce_size_t size;
	stwuct wesouwce *mem;
#if defined CONFIG_OF && defined CONFIG_COMMON_CWK
	boow cwks_enabwed;
	unsigned int cwk_count;
	stwuct cwk **cwks;
#endif
#if defined CONFIG_OF && defined CONFIG_PM_GENEWIC_DOMAINS
	unsigned int num_genpds;
	stwuct device **genpds;
	stwuct device_wink **genpd_winks;
#endif
#if defined CONFIG_OF && defined CONFIG_WEGUWATOW
	boow weguwatows_enabwed;
	u32 weguwatow_count;
	stwuct weguwatow **weguwatows;
#endif
};

static void simpwefb_cwocks_destwoy(stwuct simpwefb_paw *paw);
static void simpwefb_weguwatows_destwoy(stwuct simpwefb_paw *paw);

/*
 * fb_ops.fb_destwoy is cawwed by the wast put_fb_info() caww at the end
 * of unwegistew_fwamebuffew() ow fb_wewease(). Do any cweanup hewe.
 */
static void simpwefb_destwoy(stwuct fb_info *info)
{
	stwuct simpwefb_paw *paw = info->paw;
	stwuct wesouwce *mem = paw->mem;

	simpwefb_weguwatows_destwoy(info->paw);
	simpwefb_cwocks_destwoy(info->paw);
	if (info->scween_base)
		iounmap(info->scween_base);

	fwamebuffew_wewease(info);

	if (mem)
		wewease_mem_wegion(mem->stawt, wesouwce_size(mem));
}

static const stwuct fb_ops simpwefb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_destwoy	= simpwefb_destwoy,
	.fb_setcowweg	= simpwefb_setcowweg,
};

static stwuct simpwefb_fowmat simpwefb_fowmats[] = SIMPWEFB_FOWMATS;

stwuct simpwefb_pawams {
	u32 width;
	u32 height;
	u32 stwide;
	stwuct simpwefb_fowmat *fowmat;
	stwuct wesouwce memowy;
};

static int simpwefb_pawse_dt(stwuct pwatfowm_device *pdev,
			   stwuct simpwefb_pawams *pawams)
{
	stwuct device_node *np = pdev->dev.of_node, *mem;
	int wet;
	const chaw *fowmat;
	int i;

	wet = of_pwopewty_wead_u32(np, "width", &pawams->width);
	if (wet) {
		dev_eww(&pdev->dev, "Can't pawse width pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "height", &pawams->height);
	if (wet) {
		dev_eww(&pdev->dev, "Can't pawse height pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "stwide", &pawams->stwide);
	if (wet) {
		dev_eww(&pdev->dev, "Can't pawse stwide pwopewty\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_stwing(np, "fowmat", &fowmat);
	if (wet) {
		dev_eww(&pdev->dev, "Can't pawse fowmat pwopewty\n");
		wetuwn wet;
	}
	pawams->fowmat = NUWW;
	fow (i = 0; i < AWWAY_SIZE(simpwefb_fowmats); i++) {
		if (stwcmp(fowmat, simpwefb_fowmats[i].name))
			continue;
		pawams->fowmat = &simpwefb_fowmats[i];
		bweak;
	}
	if (!pawams->fowmat) {
		dev_eww(&pdev->dev, "Invawid fowmat vawue\n");
		wetuwn -EINVAW;
	}

	mem = of_pawse_phandwe(np, "memowy-wegion", 0);
	if (mem) {
		wet = of_addwess_to_wesouwce(mem, 0, &pawams->memowy);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to pawse memowy-wegion\n");
			of_node_put(mem);
			wetuwn wet;
		}

		if (of_pwopewty_pwesent(np, "weg"))
			dev_wawn(&pdev->dev, "pwefewwing \"memowy-wegion\" ovew \"weg\" pwopewty\n");

		of_node_put(mem);
	} ewse {
		memset(&pawams->memowy, 0, sizeof(pawams->memowy));
	}

	wetuwn 0;
}

static int simpwefb_pawse_pd(stwuct pwatfowm_device *pdev,
			     stwuct simpwefb_pawams *pawams)
{
	stwuct simpwefb_pwatfowm_data *pd = dev_get_pwatdata(&pdev->dev);
	int i;

	pawams->width = pd->width;
	pawams->height = pd->height;
	pawams->stwide = pd->stwide;

	pawams->fowmat = NUWW;
	fow (i = 0; i < AWWAY_SIZE(simpwefb_fowmats); i++) {
		if (stwcmp(pd->fowmat, simpwefb_fowmats[i].name))
			continue;

		pawams->fowmat = &simpwefb_fowmats[i];
		bweak;
	}

	if (!pawams->fowmat) {
		dev_eww(&pdev->dev, "Invawid fowmat vawue\n");
		wetuwn -EINVAW;
	}

	memset(&pawams->memowy, 0, sizeof(pawams->memowy));

	wetuwn 0;
}

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
static int simpwefb_cwocks_get(stwuct simpwefb_paw *paw,
			       stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk *cwock;
	int i;

	if (dev_get_pwatdata(&pdev->dev) || !np)
		wetuwn 0;

	paw->cwk_count = of_cwk_get_pawent_count(np);
	if (!paw->cwk_count)
		wetuwn 0;

	paw->cwks = kcawwoc(paw->cwk_count, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!paw->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < paw->cwk_count; i++) {
		cwock = of_cwk_get(np, i);
		if (IS_EWW(cwock)) {
			if (PTW_EWW(cwock) == -EPWOBE_DEFEW) {
				whiwe (--i >= 0) {
					cwk_put(paw->cwks[i]);
				}
				kfwee(paw->cwks);
				wetuwn -EPWOBE_DEFEW;
			}
			dev_eww(&pdev->dev, "%s: cwock %d not found: %wd\n",
				__func__, i, PTW_EWW(cwock));
			continue;
		}
		paw->cwks[i] = cwock;
	}

	wetuwn 0;
}

static void simpwefb_cwocks_enabwe(stwuct simpwefb_paw *paw,
				   stwuct pwatfowm_device *pdev)
{
	int i, wet;

	fow (i = 0; i < paw->cwk_count; i++) {
		if (paw->cwks[i]) {
			wet = cwk_pwepawe_enabwe(paw->cwks[i]);
			if (wet) {
				dev_eww(&pdev->dev,
					"%s: faiwed to enabwe cwock %d: %d\n",
					__func__, i, wet);
				cwk_put(paw->cwks[i]);
				paw->cwks[i] = NUWW;
			}
		}
	}
	paw->cwks_enabwed = twue;
}

static void simpwefb_cwocks_destwoy(stwuct simpwefb_paw *paw)
{
	int i;

	if (!paw->cwks)
		wetuwn;

	fow (i = 0; i < paw->cwk_count; i++) {
		if (paw->cwks[i]) {
			if (paw->cwks_enabwed)
				cwk_disabwe_unpwepawe(paw->cwks[i]);
			cwk_put(paw->cwks[i]);
		}
	}

	kfwee(paw->cwks);
}
#ewse
static int simpwefb_cwocks_get(stwuct simpwefb_paw *paw,
	stwuct pwatfowm_device *pdev) { wetuwn 0; }
static void simpwefb_cwocks_enabwe(stwuct simpwefb_paw *paw,
	stwuct pwatfowm_device *pdev) { }
static void simpwefb_cwocks_destwoy(stwuct simpwefb_paw *paw) { }
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
static int simpwefb_weguwatows_get(stwuct simpwefb_paw *paw,
				   stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pwopewty *pwop;
	stwuct weguwatow *weguwatow;
	const chaw *p;
	int count = 0, i = 0;

	if (dev_get_pwatdata(&pdev->dev) || !np)
		wetuwn 0;

	/* Count the numbew of weguwatow suppwies */
	fow_each_pwopewty_of_node(np, pwop) {
		p = stwstw(pwop->name, SUPPWY_SUFFIX);
		if (p && p != pwop->name)
			count++;
	}

	if (!count)
		wetuwn 0;

	paw->weguwatows = devm_kcawwoc(&pdev->dev, count,
				       sizeof(stwuct weguwatow *), GFP_KEWNEW);
	if (!paw->weguwatows)
		wetuwn -ENOMEM;

	/* Get aww the weguwatows */
	fow_each_pwopewty_of_node(np, pwop) {
		chaw name[32]; /* 32 is max size of pwopewty name */

		p = stwstw(pwop->name, SUPPWY_SUFFIX);
		if (!p || p == pwop->name)
			continue;

		stwscpy(name, pwop->name,
			stwwen(pwop->name) - stwwen(SUPPWY_SUFFIX) + 1);
		weguwatow = devm_weguwatow_get_optionaw(&pdev->dev, name);
		if (IS_EWW(weguwatow)) {
			if (PTW_EWW(weguwatow) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;
			dev_eww(&pdev->dev, "weguwatow %s not found: %wd\n",
				name, PTW_EWW(weguwatow));
			continue;
		}
		paw->weguwatows[i++] = weguwatow;
	}
	paw->weguwatow_count = i;

	wetuwn 0;
}

static void simpwefb_weguwatows_enabwe(stwuct simpwefb_paw *paw,
				       stwuct pwatfowm_device *pdev)
{
	int i, wet;

	/* Enabwe aww the weguwatows */
	fow (i = 0; i < paw->weguwatow_count; i++) {
		wet = weguwatow_enabwe(paw->weguwatows[i]);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed to enabwe weguwatow %d: %d\n",
				i, wet);
			devm_weguwatow_put(paw->weguwatows[i]);
			paw->weguwatows[i] = NUWW;
		}
	}
	paw->weguwatows_enabwed = twue;
}

static void simpwefb_weguwatows_destwoy(stwuct simpwefb_paw *paw)
{
	int i;

	if (!paw->weguwatows || !paw->weguwatows_enabwed)
		wetuwn;

	fow (i = 0; i < paw->weguwatow_count; i++)
		if (paw->weguwatows[i])
			weguwatow_disabwe(paw->weguwatows[i]);
}
#ewse
static int simpwefb_weguwatows_get(stwuct simpwefb_paw *paw,
	stwuct pwatfowm_device *pdev) { wetuwn 0; }
static void simpwefb_weguwatows_enabwe(stwuct simpwefb_paw *paw,
	stwuct pwatfowm_device *pdev) { }
static void simpwefb_weguwatows_destwoy(stwuct simpwefb_paw *paw) { }
#endif

#if defined CONFIG_OF && defined CONFIG_PM_GENEWIC_DOMAINS
static void simpwefb_detach_genpds(void *wes)
{
	stwuct simpwefb_paw *paw = wes;
	unsigned int i = paw->num_genpds;

	if (paw->num_genpds <= 1)
		wetuwn;

	whiwe (i--) {
		if (paw->genpd_winks[i])
			device_wink_dew(paw->genpd_winks[i]);

		if (!IS_EWW_OW_NUWW(paw->genpds[i]))
			dev_pm_domain_detach(paw->genpds[i], twue);
	}
}

static int simpwefb_attach_genpds(stwuct simpwefb_paw *paw,
				  stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	unsigned int i;
	int eww;

	eww = of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
					 "#powew-domain-cewws");
	if (eww < 0) {
		/* Nothing wwong if optionaw PDs awe missing */
		if (eww == -ENOENT)
			wetuwn 0;

		dev_info(dev, "faiwed to pawse powew-domains: %d\n", eww);
		wetuwn eww;
	}

	paw->num_genpds = eww;

	/*
	 * Singwe powew-domain devices awe handwed by the dwivew cowe, so
	 * nothing to do hewe.
	 */
	if (paw->num_genpds <= 1)
		wetuwn 0;

	paw->genpds = devm_kcawwoc(dev, paw->num_genpds, sizeof(*paw->genpds),
				   GFP_KEWNEW);
	if (!paw->genpds)
		wetuwn -ENOMEM;

	paw->genpd_winks = devm_kcawwoc(dev, paw->num_genpds,
					sizeof(*paw->genpd_winks),
					GFP_KEWNEW);
	if (!paw->genpd_winks)
		wetuwn -ENOMEM;

	fow (i = 0; i < paw->num_genpds; i++) {
		paw->genpds[i] = dev_pm_domain_attach_by_id(dev, i);
		if (IS_EWW(paw->genpds[i])) {
			eww = PTW_EWW(paw->genpds[i]);
			if (eww == -EPWOBE_DEFEW) {
				simpwefb_detach_genpds(paw);
				wetuwn eww;
			}

			dev_wawn(dev, "faiwed to attach domain %u: %d\n", i, eww);
			continue;
		}

		paw->genpd_winks[i] = device_wink_add(dev, paw->genpds[i],
						      DW_FWAG_STATEWESS |
						      DW_FWAG_PM_WUNTIME |
						      DW_FWAG_WPM_ACTIVE);
		if (!paw->genpd_winks[i])
			dev_wawn(dev, "faiwed to wink powew-domain %u\n", i);
	}

	wetuwn devm_add_action_ow_weset(dev, simpwefb_detach_genpds, paw);
}
#ewse
static int simpwefb_attach_genpds(stwuct simpwefb_paw *paw,
				  stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif

static int simpwefb_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct simpwefb_pawams pawams;
	stwuct fb_info *info;
	stwuct simpwefb_paw *paw;
	stwuct wesouwce *wes, *mem;

	if (fb_get_options("simpwefb", NUWW))
		wetuwn -ENODEV;

	wet = -ENODEV;
	if (dev_get_pwatdata(&pdev->dev))
		wet = simpwefb_pawse_pd(pdev, &pawams);
	ewse if (pdev->dev.of_node)
		wet = simpwefb_pawse_dt(pdev, &pawams);

	if (wet)
		wetuwn wet;

	if (pawams.memowy.stawt == 0 && pawams.memowy.end == 0) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes) {
			dev_eww(&pdev->dev, "No memowy wesouwce\n");
			wetuwn -EINVAW;
		}
	} ewse {
		wes = &pawams.memowy;
	}

	mem = wequest_mem_wegion(wes->stawt, wesouwce_size(wes), "simpwefb");
	if (!mem) {
		/*
		 * We cannot make this fataw. Sometimes this comes fwom magic
		 * spaces ouw wesouwce handwews simpwy don't know about. Use
		 * the I/O-memowy wesouwce as-is and twy to map that instead.
		 */
		dev_wawn(&pdev->dev, "simpwefb: cannot wesewve video memowy at %pW\n", wes);
		mem = wes;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct simpwefb_paw), &pdev->dev);
	if (!info) {
		wet = -ENOMEM;
		goto ewwow_wewease_mem_wegion;
	}
	pwatfowm_set_dwvdata(pdev, info);

	paw = info->paw;

	info->fix = simpwefb_fix;
	info->fix.smem_stawt = mem->stawt;
	info->fix.smem_wen = wesouwce_size(mem);
	info->fix.wine_wength = pawams.stwide;

	info->vaw = simpwefb_vaw;
	info->vaw.xwes = pawams.width;
	info->vaw.ywes = pawams.height;
	info->vaw.xwes_viwtuaw = pawams.width;
	info->vaw.ywes_viwtuaw = pawams.height;
	info->vaw.bits_pew_pixew = pawams.fowmat->bits_pew_pixew;
	info->vaw.wed = pawams.fowmat->wed;
	info->vaw.gween = pawams.fowmat->gween;
	info->vaw.bwue = pawams.fowmat->bwue;
	info->vaw.twansp = pawams.fowmat->twansp;

	paw->base = info->fix.smem_stawt;
	paw->size = info->fix.smem_wen;

	info->fbops = &simpwefb_ops;
	info->scween_base = iowemap_wc(info->fix.smem_stawt,
				       info->fix.smem_wen);
	if (!info->scween_base) {
		wet = -ENOMEM;
		goto ewwow_fb_wewease;
	}
	info->pseudo_pawette = paw->pawette;

	wet = simpwefb_cwocks_get(paw, pdev);
	if (wet < 0)
		goto ewwow_unmap;

	wet = simpwefb_weguwatows_get(paw, pdev);
	if (wet < 0)
		goto ewwow_cwocks;

	wet = simpwefb_attach_genpds(paw, pdev);
	if (wet < 0)
		goto ewwow_weguwatows;

	simpwefb_cwocks_enabwe(paw, pdev);
	simpwefb_weguwatows_enabwe(paw, pdev);

	dev_info(&pdev->dev, "fwamebuffew at 0x%wx, 0x%x bytes\n",
			     info->fix.smem_stawt, info->fix.smem_wen);
	dev_info(&pdev->dev, "fowmat=%s, mode=%dx%dx%d, winewength=%d\n",
			     pawams.fowmat->name,
			     info->vaw.xwes, info->vaw.ywes,
			     info->vaw.bits_pew_pixew, info->fix.wine_wength);

	if (mem != wes)
		paw->mem = mem; /* wewease in cwean-up handwew */

	wet = devm_apewtuwe_acquiwe_fow_pwatfowm_device(pdev, paw->base, paw->size);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to acquiwe apewtuwe: %d\n", wet);
		goto ewwow_weguwatows;
	}
	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unabwe to wegistew simpwefb: %d\n", wet);
		goto ewwow_weguwatows;
	}

	dev_info(&pdev->dev, "fb%d: simpwefb wegistewed!\n", info->node);

	wetuwn 0;

ewwow_weguwatows:
	simpwefb_weguwatows_destwoy(paw);
ewwow_cwocks:
	simpwefb_cwocks_destwoy(paw);
ewwow_unmap:
	iounmap(info->scween_base);
ewwow_fb_wewease:
	fwamebuffew_wewease(info);
ewwow_wewease_mem_wegion:
	if (mem != wes)
		wewease_mem_wegion(mem->stawt, wesouwce_size(mem));
	wetuwn wet;
}

static void simpwefb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);

	/* simpwefb_destwoy takes cawe of info cweanup */
	unwegistew_fwamebuffew(info);
}

static const stwuct of_device_id simpwefb_of_match[] = {
	{ .compatibwe = "simpwe-fwamebuffew", },
	{ },
};
MODUWE_DEVICE_TABWE(of, simpwefb_of_match);

static stwuct pwatfowm_dwivew simpwefb_dwivew = {
	.dwivew = {
		.name = "simpwe-fwamebuffew",
		.of_match_tabwe = simpwefb_of_match,
	},
	.pwobe = simpwefb_pwobe,
	.wemove_new = simpwefb_wemove,
};

moduwe_pwatfowm_dwivew(simpwefb_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@wwwdotowg.owg>");
MODUWE_DESCWIPTION("Simpwe fwamebuffew dwivew");
MODUWE_WICENSE("GPW v2");
