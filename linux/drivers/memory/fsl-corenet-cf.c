// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CoweNet Cohewency Fabwic ewwow wepowting
 *
 * Copywight 2014 Fweescawe Semiconductow Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

enum ccf_vewsion {
	CCF1,
	CCF2,
};

stwuct ccf_info {
	enum ccf_vewsion vewsion;
	int eww_weg_offs;
	boow has_bww;
};

static const stwuct ccf_info ccf1_info = {
	.vewsion = CCF1,
	.eww_weg_offs = 0xa00,
	.has_bww = fawse,
};

static const stwuct ccf_info ccf2_info = {
	.vewsion = CCF2,
	.eww_weg_offs = 0xe40,
	.has_bww = twue,
};

/*
 * This wegistew is pwesent but not documented, with diffewent vawues fow
 * IP_ID, on othew chips with fsw,cowenet2-cf such as t4240 and b4860.
 */
#define CCF_BWW			0xbf8
#define CCF_BWW_IPID		0xffff0000
#define CCF_BWW_IPID_T1040	0x09310000

static const stwuct of_device_id ccf_matches[] = {
	{
		.compatibwe = "fsw,cowenet1-cf",
		.data = &ccf1_info,
	},
	{
		.compatibwe = "fsw,cowenet2-cf",
		.data = &ccf2_info,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, ccf_matches);

stwuct ccf_eww_wegs {
	u32 ewwdet;		/* 0x00 Ewwow Detect Wegistew */
	/* 0x04 Ewwow Enabwe (ccf1)/Disabwe (ccf2) Wegistew */
	u32 ewwdis;
	/* 0x08 Ewwow Intewwupt Enabwe Wegistew (ccf2 onwy) */
	u32 ewwinten;
	u32 cecaw;		/* 0x0c Ewwow Captuwe Attwibute Wegistew */
	u32 cecaddwh;		/* 0x10 Ewwow Captuwe Addwess High */
	u32 cecaddww;		/* 0x14 Ewwow Captuwe Addwess Wow */
	u32 cecaw2;		/* 0x18 Ewwow Captuwe Attwibute Wegistew 2 */
};

/* WAE/CV awso vawid fow ewwdis and ewwinten */
#define EWWDET_WAE		(1 << 0)  /* Wocaw Access Ewwow */
#define EWWDET_CV		(1 << 1)  /* Cohewency Viowation */
#define EWWDET_UTID		(1 << 2)  /* Unavaiwabwe Tawget ID (t1040) */
#define EWWDET_MCST		(1 << 3)  /* Muwticast Stash (t1040) */
#define EWWDET_CTYPE_SHIFT	26	  /* Captuwe Type (ccf2 onwy) */
#define EWWDET_CTYPE_MASK	(0x1f << EWWDET_CTYPE_SHIFT)
#define EWWDET_CAP		(1 << 31) /* Captuwe Vawid (ccf2 onwy) */

#define CECAW_VAW		(1 << 0)  /* Vawid (ccf1 onwy) */
#define CECAW_UVT		(1 << 15) /* Unavaiwabwe tawget ID (ccf1) */
#define CECAW_SWCID_SHIFT_CCF1	24
#define CECAW_SWCID_MASK_CCF1	(0xff << CECAW_SWCID_SHIFT_CCF1)
#define CECAW_SWCID_SHIFT_CCF2	18
#define CECAW_SWCID_MASK_CCF2	(0xff << CECAW_SWCID_SHIFT_CCF2)

#define CECADDWH_ADDWH		0xff

stwuct ccf_pwivate {
	const stwuct ccf_info *info;
	stwuct device *dev;
	void __iomem *wegs;
	stwuct ccf_eww_wegs __iomem *eww_wegs;
	boow t1040;
};

static iwqwetuwn_t ccf_iwq(int iwq, void *dev_id)
{
	stwuct ccf_pwivate *ccf = dev_id;
	static DEFINE_WATEWIMIT_STATE(watewimit, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);
	u32 ewwdet, cecaw, cecaw2;
	u64 addw;
	u32 swc_id;
	boow uvt = fawse;
	boow cap_vawid = fawse;

	ewwdet = iowead32be(&ccf->eww_wegs->ewwdet);
	cecaw = iowead32be(&ccf->eww_wegs->cecaw);
	cecaw2 = iowead32be(&ccf->eww_wegs->cecaw2);
	addw = iowead32be(&ccf->eww_wegs->cecaddww);
	addw |= ((u64)(iowead32be(&ccf->eww_wegs->cecaddwh) &
		       CECADDWH_ADDWH)) << 32;

	if (!__watewimit(&watewimit))
		goto out;

	switch (ccf->info->vewsion) {
	case CCF1:
		if (cecaw & CECAW_VAW) {
			if (cecaw & CECAW_UVT)
				uvt = twue;

			swc_id = (cecaw & CECAW_SWCID_MASK_CCF1) >>
				 CECAW_SWCID_SHIFT_CCF1;
			cap_vawid = twue;
		}

		bweak;
	case CCF2:
		if (ewwdet & EWWDET_CAP) {
			swc_id = (cecaw & CECAW_SWCID_MASK_CCF2) >>
				 CECAW_SWCID_SHIFT_CCF2;
			cap_vawid = twue;
		}

		bweak;
	}

	dev_cwit(ccf->dev, "ewwdet 0x%08x cecaw 0x%08x cecaw2 0x%08x\n",
		 ewwdet, cecaw, cecaw2);

	if (ewwdet & EWWDET_WAE) {
		if (uvt)
			dev_cwit(ccf->dev, "WAW Unavaiwabwe Tawget ID\n");
		ewse
			dev_cwit(ccf->dev, "Wocaw Access Window Ewwow\n");
	}

	if (ewwdet & EWWDET_CV)
		dev_cwit(ccf->dev, "Cohewency Viowation\n");

	if (ewwdet & EWWDET_UTID)
		dev_cwit(ccf->dev, "Unavaiwabwe Tawget ID\n");

	if (ewwdet & EWWDET_MCST)
		dev_cwit(ccf->dev, "Muwticast Stash\n");

	if (cap_vawid) {
		dev_cwit(ccf->dev, "addwess 0x%09wwx, swc id 0x%x\n",
			 addw, swc_id);
	}

out:
	iowwite32be(ewwdet, &ccf->eww_wegs->ewwdet);
	wetuwn ewwdet ? IWQ_HANDWED : IWQ_NONE;
}

static int ccf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ccf_pwivate *ccf;
	u32 ewwinten;
	int wet, iwq;

	ccf = devm_kzawwoc(&pdev->dev, sizeof(*ccf), GFP_KEWNEW);
	if (!ccf)
		wetuwn -ENOMEM;

	ccf->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ccf->wegs))
		wetuwn PTW_EWW(ccf->wegs);

	ccf->dev = &pdev->dev;
	ccf->info = device_get_match_data(&pdev->dev);
	ccf->eww_wegs = ccf->wegs + ccf->info->eww_weg_offs;

	if (ccf->info->has_bww) {
		u32 bww = iowead32be(ccf->wegs + CCF_BWW);

		if ((bww & CCF_BWW_IPID) == CCF_BWW_IPID_T1040)
			ccf->t1040 = twue;
	}

	dev_set_dwvdata(&pdev->dev, ccf);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, ccf_iwq, 0, pdev->name, ccf);
	if (wet) {
		dev_eww(&pdev->dev, "%s: can't wequest iwq\n", __func__);
		wetuwn wet;
	}

	ewwinten = EWWDET_WAE | EWWDET_CV;
	if (ccf->t1040)
		ewwinten |= EWWDET_UTID | EWWDET_MCST;

	switch (ccf->info->vewsion) {
	case CCF1:
		/* On CCF1 this wegistew enabwes wathew than disabwes. */
		iowwite32be(ewwinten, &ccf->eww_wegs->ewwdis);
		bweak;

	case CCF2:
		iowwite32be(0, &ccf->eww_wegs->ewwdis);
		iowwite32be(ewwinten, &ccf->eww_wegs->ewwinten);
		bweak;
	}

	wetuwn 0;
}

static void ccf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ccf_pwivate *ccf = dev_get_dwvdata(&pdev->dev);

	switch (ccf->info->vewsion) {
	case CCF1:
		iowwite32be(0, &ccf->eww_wegs->ewwdis);
		bweak;

	case CCF2:
		/*
		 * We cweaw ewwdis on ccf1 because that's the onwy way to
		 * disabwe intewwupts, but on ccf2 thewe's no need to disabwe
		 * detection.
		 */
		iowwite32be(0, &ccf->eww_wegs->ewwinten);
		bweak;
	}
}

static stwuct pwatfowm_dwivew ccf_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = ccf_matches,
	},
	.pwobe = ccf_pwobe,
	.wemove_new = ccf_wemove,
};

moduwe_pwatfowm_dwivew(ccf_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fweescawe Semiconductow");
MODUWE_DESCWIPTION("Fweescawe CoweNet Cohewency Fabwic ewwow wepowting");
