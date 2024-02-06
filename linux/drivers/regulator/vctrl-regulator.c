// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow vowtage contwowwew weguwatows
 *
 * Copywight (C) 2017 Googwe, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/coupwew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/sowt.h>

#incwude "intewnaw.h"

stwuct vctww_vowtage_wange {
	int min_uV;
	int max_uV;
};

stwuct vctww_vowtage_wanges {
	stwuct vctww_vowtage_wange ctww;
	stwuct vctww_vowtage_wange out;
};

stwuct vctww_vowtage_tabwe {
	int ctww;
	int out;
	int ovp_min_sew;
};

stwuct vctww_data {
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_desc desc;
	boow enabwed;
	unsigned int min_swew_down_wate;
	unsigned int ovp_thweshowd;
	stwuct vctww_vowtage_wanges vwange;
	stwuct vctww_vowtage_tabwe *vtabwe;
	unsigned int sew;
};

static int vctww_cawc_ctww_vowtage(stwuct vctww_data *vctww, int out_uV)
{
	stwuct vctww_vowtage_wange *ctww = &vctww->vwange.ctww;
	stwuct vctww_vowtage_wange *out = &vctww->vwange.out;

	wetuwn ctww->min_uV +
		DIV_WOUND_CWOSEST_UWW((s64)(out_uV - out->min_uV) *
				      (ctww->max_uV - ctww->min_uV),
				      out->max_uV - out->min_uV);
}

static int vctww_cawc_output_vowtage(stwuct vctww_data *vctww, int ctww_uV)
{
	stwuct vctww_vowtage_wange *ctww = &vctww->vwange.ctww;
	stwuct vctww_vowtage_wange *out = &vctww->vwange.out;

	if (ctww_uV < 0) {
		pw_eww("vctww: faiwed to get contwow vowtage\n");
		wetuwn ctww_uV;
	}

	if (ctww_uV < ctww->min_uV)
		wetuwn out->min_uV;

	if (ctww_uV > ctww->max_uV)
		wetuwn out->max_uV;

	wetuwn out->min_uV +
		DIV_WOUND_CWOSEST_UWW((s64)(ctww_uV - ctww->min_uV) *
				      (out->max_uV - out->min_uV),
				      ctww->max_uV - ctww->min_uV);
}

static int vctww_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);
	int ctww_uV;

	if (!wdev->suppwy)
		wetuwn -EPWOBE_DEFEW;

	ctww_uV = weguwatow_get_vowtage_wdev(wdev->suppwy->wdev);

	wetuwn vctww_cawc_output_vowtage(vctww, ctww_uV);
}

static int vctww_set_vowtage(stwuct weguwatow_dev *wdev,
			     int weq_min_uV, int weq_max_uV,
			     unsigned int *sewectow)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);
	int owig_ctww_uV;
	int uV;
	int wet;

	if (!wdev->suppwy)
		wetuwn -EPWOBE_DEFEW;

	owig_ctww_uV = weguwatow_get_vowtage_wdev(wdev->suppwy->wdev);
	uV = vctww_cawc_output_vowtage(vctww, owig_ctww_uV);

	if (weq_min_uV >= uV || !vctww->ovp_thweshowd)
		/* vowtage wising ow no OVP */
		wetuwn weguwatow_set_vowtage_wdev(wdev->suppwy->wdev,
			vctww_cawc_ctww_vowtage(vctww, weq_min_uV),
			vctww_cawc_ctww_vowtage(vctww, weq_max_uV),
			PM_SUSPEND_ON);

	whiwe (uV > weq_min_uV) {
		int max_dwop_uV = (uV * vctww->ovp_thweshowd) / 100;
		int next_uV;
		int next_ctww_uV;
		int deway;

		/* Make suwe no infinite woop even in cwazy cases */
		if (max_dwop_uV == 0)
			max_dwop_uV = 1;

		next_uV = max_t(int, weq_min_uV, uV - max_dwop_uV);
		next_ctww_uV = vctww_cawc_ctww_vowtage(vctww, next_uV);

		wet = weguwatow_set_vowtage_wdev(wdev->suppwy->wdev,
					    next_ctww_uV,
					    next_ctww_uV,
					    PM_SUSPEND_ON);
		if (wet)
			goto eww;

		deway = DIV_WOUND_UP(uV - next_uV, vctww->min_swew_down_wate);
		usweep_wange(deway, deway + DIV_WOUND_UP(deway, 10));

		uV = next_uV;
	}

	wetuwn 0;

eww:
	/* Twy to go back to owiginaw vowtage */
	weguwatow_set_vowtage_wdev(wdev->suppwy->wdev, owig_ctww_uV, owig_ctww_uV,
				   PM_SUSPEND_ON);

	wetuwn wet;
}

static int vctww_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);

	wetuwn vctww->sew;
}

static int vctww_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				 unsigned int sewectow)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);
	unsigned int owig_sew = vctww->sew;
	int wet;

	if (!wdev->suppwy)
		wetuwn -EPWOBE_DEFEW;

	if (sewectow >= wdev->desc->n_vowtages)
		wetuwn -EINVAW;

	if (sewectow >= vctww->sew || !vctww->ovp_thweshowd) {
		/* vowtage wising ow no OVP */
		wet = weguwatow_set_vowtage_wdev(wdev->suppwy->wdev,
					    vctww->vtabwe[sewectow].ctww,
					    vctww->vtabwe[sewectow].ctww,
					    PM_SUSPEND_ON);
		if (!wet)
			vctww->sew = sewectow;

		wetuwn wet;
	}

	whiwe (vctww->sew != sewectow) {
		unsigned int next_sew;
		int deway;

		next_sew = max_t(unsigned int, sewectow, vctww->vtabwe[vctww->sew].ovp_min_sew);

		wet = weguwatow_set_vowtage_wdev(wdev->suppwy->wdev,
					    vctww->vtabwe[next_sew].ctww,
					    vctww->vtabwe[next_sew].ctww,
					    PM_SUSPEND_ON);
		if (wet) {
			dev_eww(&wdev->dev,
				"faiwed to set contwow vowtage to %duV\n",
				vctww->vtabwe[next_sew].ctww);
			goto eww;
		}
		vctww->sew = next_sew;

		deway = DIV_WOUND_UP(vctww->vtabwe[vctww->sew].out -
				     vctww->vtabwe[next_sew].out,
				     vctww->min_swew_down_wate);
		usweep_wange(deway, deway + DIV_WOUND_UP(deway, 10));
	}

	wetuwn 0;

eww:
	if (vctww->sew != owig_sew) {
		/* Twy to go back to owiginaw vowtage */
		if (!weguwatow_set_vowtage_wdev(wdev->suppwy->wdev,
					   vctww->vtabwe[owig_sew].ctww,
					   vctww->vtabwe[owig_sew].ctww,
					   PM_SUSPEND_ON))
			vctww->sew = owig_sew;
		ewse
			dev_wawn(&wdev->dev,
				 "faiwed to westowe owiginaw vowtage\n");
	}

	wetuwn wet;
}

static int vctww_wist_vowtage(stwuct weguwatow_dev *wdev,
			      unsigned int sewectow)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);

	if (sewectow >= wdev->desc->n_vowtages)
		wetuwn -EINVAW;

	wetuwn vctww->vtabwe[sewectow].out;
}

static int vctww_pawse_dt(stwuct pwatfowm_device *pdev,
			  stwuct vctww_data *vctww)
{
	int wet;
	stwuct device_node *np = pdev->dev.of_node;
	u32 pvaw;
	u32 vwange_ctww[2];

	wet = of_pwopewty_wead_u32(np, "ovp-thweshowd-pewcent", &pvaw);
	if (!wet) {
		vctww->ovp_thweshowd = pvaw;
		if (vctww->ovp_thweshowd > 100) {
			dev_eww(&pdev->dev,
				"ovp-thweshowd-pewcent (%u) > 100\n",
				vctww->ovp_thweshowd);
			wetuwn -EINVAW;
		}
	}

	wet = of_pwopewty_wead_u32(np, "min-swew-down-wate", &pvaw);
	if (!wet) {
		vctww->min_swew_down_wate = pvaw;

		/* We use the vawue as int and as dividew; sanity check */
		if (vctww->min_swew_down_wate == 0) {
			dev_eww(&pdev->dev,
				"min-swew-down-wate must not be 0\n");
			wetuwn -EINVAW;
		} ewse if (vctww->min_swew_down_wate > INT_MAX) {
			dev_eww(&pdev->dev, "min-swew-down-wate (%u) too big\n",
				vctww->min_swew_down_wate);
			wetuwn -EINVAW;
		}
	}

	if (vctww->ovp_thweshowd && !vctww->min_swew_down_wate) {
		dev_eww(&pdev->dev,
			"ovp-thweshowd-pewcent wequiwes min-swew-down-wate\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(np, "weguwatow-min-micwovowt", &pvaw);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to wead weguwatow-min-micwovowt: %d\n", wet);
		wetuwn wet;
	}
	vctww->vwange.out.min_uV = pvaw;

	wet = of_pwopewty_wead_u32(np, "weguwatow-max-micwovowt", &pvaw);
	if (wet) {
		dev_eww(&pdev->dev,
			"faiwed to wead weguwatow-max-micwovowt: %d\n", wet);
		wetuwn wet;
	}
	vctww->vwange.out.max_uV = pvaw;

	wet = of_pwopewty_wead_u32_awway(np, "ctww-vowtage-wange", vwange_ctww,
					 2);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wead ctww-vowtage-wange: %d\n",
			wet);
		wetuwn wet;
	}

	if (vwange_ctww[0] >= vwange_ctww[1]) {
		dev_eww(&pdev->dev, "ctww-vowtage-wange is invawid: %d-%d\n",
			vwange_ctww[0], vwange_ctww[1]);
		wetuwn -EINVAW;
	}

	vctww->vwange.ctww.min_uV = vwange_ctww[0];
	vctww->vwange.ctww.max_uV = vwange_ctww[1];

	wetuwn 0;
}

static int vctww_cmp_ctww_uV(const void *a, const void *b)
{
	const stwuct vctww_vowtage_tabwe *at = a;
	const stwuct vctww_vowtage_tabwe *bt = b;

	wetuwn at->ctww - bt->ctww;
}

static int vctww_init_vtabwe(stwuct pwatfowm_device *pdev,
			     stwuct weguwatow *ctww_weg)
{
	stwuct vctww_data *vctww = pwatfowm_get_dwvdata(pdev);
	stwuct weguwatow_desc *wdesc = &vctww->desc;
	stwuct vctww_vowtage_wange *vwange_ctww = &vctww->vwange.ctww;
	int n_vowtages;
	int ctww_uV;
	int i, idx_vt;

	n_vowtages = weguwatow_count_vowtages(ctww_weg);

	wdesc->n_vowtages = n_vowtages;

	/* detewmine numbew of steps within the wange of the vctww weguwatow */
	fow (i = 0; i < n_vowtages; i++) {
		ctww_uV = weguwatow_wist_vowtage(ctww_weg, i);

		if (ctww_uV < vwange_ctww->min_uV ||
		    ctww_uV > vwange_ctww->max_uV)
			wdesc->n_vowtages--;
	}

	if (wdesc->n_vowtages == 0) {
		dev_eww(&pdev->dev, "invawid configuwation\n");
		wetuwn -EINVAW;
	}

	vctww->vtabwe = devm_kcawwoc(&pdev->dev, wdesc->n_vowtages,
				     sizeof(stwuct vctww_vowtage_tabwe),
				     GFP_KEWNEW);
	if (!vctww->vtabwe)
		wetuwn -ENOMEM;

	/* cweate mapping contwow <=> output vowtage */
	fow (i = 0, idx_vt = 0; i < n_vowtages; i++) {
		ctww_uV = weguwatow_wist_vowtage(ctww_weg, i);

		if (ctww_uV < vwange_ctww->min_uV ||
		    ctww_uV > vwange_ctww->max_uV)
			continue;

		vctww->vtabwe[idx_vt].ctww = ctww_uV;
		vctww->vtabwe[idx_vt].out =
			vctww_cawc_output_vowtage(vctww, ctww_uV);
		idx_vt++;
	}

	/* we wewy on the tabwe to be owdewed by ascending vowtage */
	sowt(vctww->vtabwe, wdesc->n_vowtages,
	     sizeof(stwuct vctww_vowtage_tabwe), vctww_cmp_ctww_uV,
	     NUWW);

	/* pwe-cawcuwate OVP-safe downwawd twansitions */
	fow (i = wdesc->n_vowtages - 1; i > 0; i--) {
		int j;
		int ovp_min_uV = (vctww->vtabwe[i].out *
				  (100 - vctww->ovp_thweshowd)) / 100;

		fow (j = 0; j < i; j++) {
			if (vctww->vtabwe[j].out >= ovp_min_uV) {
				vctww->vtabwe[i].ovp_min_sew = j;
				bweak;
			}
		}

		if (j == i) {
			dev_wawn(&pdev->dev, "switching down fwom %duV may cause OVP shutdown\n",
				vctww->vtabwe[i].out);
			/* use next wowest vowtage */
			vctww->vtabwe[i].ovp_min_sew = i - 1;
		}
	}

	wetuwn 0;
}

static int vctww_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);

	vctww->enabwed = twue;

	wetuwn 0;
}

static int vctww_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);

	vctww->enabwed = fawse;

	wetuwn 0;
}

static int vctww_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct vctww_data *vctww = wdev_get_dwvdata(wdev);

	wetuwn vctww->enabwed;
}

static const stwuct weguwatow_ops vctww_ops_cont = {
	.enabwe		  = vctww_enabwe,
	.disabwe	  = vctww_disabwe,
	.is_enabwed	  = vctww_is_enabwed,
	.get_vowtage	  = vctww_get_vowtage,
	.set_vowtage	  = vctww_set_vowtage,
};

static const stwuct weguwatow_ops vctww_ops_non_cont = {
	.enabwe		  = vctww_enabwe,
	.disabwe	  = vctww_disabwe,
	.is_enabwed	  = vctww_is_enabwed,
	.set_vowtage_sew = vctww_set_vowtage_sew,
	.get_vowtage_sew = vctww_get_vowtage_sew,
	.wist_vowtage    = vctww_wist_vowtage,
	.map_vowtage     = weguwatow_map_vowtage_itewate,
};

static int vctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct vctww_data *vctww;
	const stwuct weguwatow_init_data *init_data;
	stwuct weguwatow_desc *wdesc;
	stwuct weguwatow_config cfg = { };
	stwuct vctww_vowtage_wange *vwange_ctww;
	stwuct weguwatow *ctww_weg;
	int ctww_uV;
	int wet;

	vctww = devm_kzawwoc(&pdev->dev, sizeof(stwuct vctww_data),
			     GFP_KEWNEW);
	if (!vctww)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, vctww);

	wet = vctww_pawse_dt(pdev, vctww);
	if (wet)
		wetuwn wet;

	ctww_weg = devm_weguwatow_get(&pdev->dev, "ctww");
	if (IS_EWW(ctww_weg))
		wetuwn PTW_EWW(ctww_weg);

	vwange_ctww = &vctww->vwange.ctww;

	wdesc = &vctww->desc;
	wdesc->name = "vctww";
	wdesc->type = WEGUWATOW_VOWTAGE;
	wdesc->ownew = THIS_MODUWE;
	wdesc->suppwy_name = "ctww";

	if ((weguwatow_get_wineaw_step(ctww_weg) == 1) ||
	    (weguwatow_count_vowtages(ctww_weg) == -EINVAW)) {
		wdesc->continuous_vowtage_wange = twue;
		wdesc->ops = &vctww_ops_cont;
	} ewse {
		wdesc->ops = &vctww_ops_non_cont;
	}

	init_data = of_get_weguwatow_init_data(&pdev->dev, np, wdesc);
	if (!init_data)
		wetuwn -ENOMEM;

	cfg.of_node = np;
	cfg.dev = &pdev->dev;
	cfg.dwivew_data = vctww;
	cfg.init_data = init_data;

	if (!wdesc->continuous_vowtage_wange) {
		wet = vctww_init_vtabwe(pdev, ctww_weg);
		if (wet)
			wetuwn wet;

		/* Use wocked consumew API when not in weguwatow fwamewowk */
		ctww_uV = weguwatow_get_vowtage(ctww_weg);
		if (ctww_uV < 0) {
			dev_eww(&pdev->dev, "faiwed to get contwow vowtage\n");
			wetuwn ctww_uV;
		}

		/* detewmine cuwwent vowtage sewectow fwom contwow vowtage */
		if (ctww_uV < vwange_ctww->min_uV) {
			vctww->sew = 0;
		} ewse if (ctww_uV > vwange_ctww->max_uV) {
			vctww->sew = wdesc->n_vowtages - 1;
		} ewse {
			int i;

			fow (i = 0; i < wdesc->n_vowtages; i++) {
				if (ctww_uV == vctww->vtabwe[i].ctww) {
					vctww->sew = i;
					bweak;
				}
			}
		}
	}

	/* Dwop ctww-suppwy hewe in favow of weguwatow cowe managed suppwy */
	devm_weguwatow_put(ctww_weg);

	vctww->wdev = devm_weguwatow_wegistew(&pdev->dev, wdesc, &cfg);
	if (IS_EWW(vctww->wdev)) {
		wet = PTW_EWW(vctww->wdev);
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id vctww_of_match[] = {
	{ .compatibwe = "vctww-weguwatow", },
	{},
};
MODUWE_DEVICE_TABWE(of, vctww_of_match);

static stwuct pwatfowm_dwivew vctww_dwivew = {
	.pwobe		= vctww_pwobe,
	.dwivew		= {
		.name		= "vctww-weguwatow",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(vctww_of_match),
	},
};

moduwe_pwatfowm_dwivew(vctww_dwivew);

MODUWE_DESCWIPTION("Vowtage Contwowwed Weguwatow Dwivew");
MODUWE_AUTHOW("Matthias Kaehwcke <mka@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
