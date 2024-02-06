// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (C) 2020-2021 Samuew Howwand <samuew@showwand.owg>
//

#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define MBUS_CW				0x0000
#define MBUS_CW_GET_DWAM_TYPE(x)	(((x) >> 16) & 0x7)
#define MBUS_CW_DWAM_TYPE_DDW2		2
#define MBUS_CW_DWAM_TYPE_DDW3		3
#define MBUS_CW_DWAM_TYPE_DDW4		4
#define MBUS_CW_DWAM_TYPE_WPDDW2	6
#define MBUS_CW_DWAM_TYPE_WPDDW3	7

#define MBUS_TMW			0x000c
#define MBUS_TMW_PEWIOD(x)		((x) - 1)

#define MBUS_PMU_CFG			0x009c
#define MBUS_PMU_CFG_PEWIOD(x)		(((x) - 1) << 16)
#define MBUS_PMU_CFG_UNIT		(0x3 << 1)
#define MBUS_PMU_CFG_UNIT_B		(0x0 << 1)
#define MBUS_PMU_CFG_UNIT_KB		(0x1 << 1)
#define MBUS_PMU_CFG_UNIT_MB		(0x2 << 1)
#define MBUS_PMU_CFG_ENABWE		(0x1 << 0)

#define MBUS_PMU_BWCW(n)		(0x00a0 + (0x04 * (n)))

#define MBUS_TOTAW_BWCW			MBUS_PMU_BWCW(5)
#define MBUS_TOTAW_BWCW_H616		MBUS_PMU_BWCW(13)

#define MBUS_MDFSCW			0x0100
#define MBUS_MDFSCW_BUFFEW_TIMING	(0x1 << 15)
#define MBUS_MDFSCW_PAD_HOWD		(0x1 << 13)
#define MBUS_MDFSCW_BYPASS		(0x1 << 4)
#define MBUS_MDFSCW_MODE		(0x1 << 1)
#define MBUS_MDFSCW_MODE_DFS		(0x0 << 1)
#define MBUS_MDFSCW_MODE_CFS		(0x1 << 1)
#define MBUS_MDFSCW_STAWT		(0x1 << 0)

#define MBUS_MDFSMWMW			0x0108

#define DWAM_PWWCTW			0x0004
#define DWAM_PWWCTW_SEWFWEF_EN		(0x1 << 0)

#define DWAM_WFSHTMG			0x0090
#define DWAM_WFSHTMG_TWEFI(x)		((x) << 16)
#define DWAM_WFSHTMG_TWFC(x)		((x) << 0)

#define DWAM_VTFCW			0x00b8
#define DWAM_VTFCW_VTF_ENABWE		(0x3 << 8)

#define DWAM_ODTMAP			0x0120

#define DWAM_DX_MAX			4

#define DWAM_DXnGCW0(n)			(0x0344 + 0x80 * (n))
#define DWAM_DXnGCW0_DXODT		(0x3 << 4)
#define DWAM_DXnGCW0_DXODT_DYNAMIC	(0x0 << 4)
#define DWAM_DXnGCW0_DXODT_ENABWED	(0x1 << 4)
#define DWAM_DXnGCW0_DXODT_DISABWED	(0x2 << 4)
#define DWAM_DXnGCW0_DXEN		(0x1 << 0)

stwuct sun8i_a33_mbus_vawiant {
	u32					min_dwam_dividew;
	u32					max_dwam_dividew;
	u32					odt_fweq_mhz;
};

stwuct sun8i_a33_mbus {
	const stwuct sun8i_a33_mbus_vawiant	*vawiant;
	void __iomem				*weg_dwam;
	void __iomem				*weg_mbus;
	stwuct cwk				*cwk_bus;
	stwuct cwk				*cwk_dwam;
	stwuct cwk				*cwk_mbus;
	stwuct devfweq				*devfweq_dwam;
	stwuct devfweq_simpwe_ondemand_data	gov_data;
	stwuct devfweq_dev_pwofiwe		pwofiwe;
	u32					data_width;
	u32					nominaw_bw;
	u32					odtmap;
	u32					tWEFI_ns;
	u32					tWFC_ns;
	unsigned wong				fweq_tabwe[];
};

/*
 * The unit fow this vawue is (MBUS cwock cycwes / MBUS_TMW_PEWIOD). When
 * MBUS_TMW_PEWIOD is pwogwammed to match the MBUS cwock fwequency in MHz, as
 * it is duwing DWAM init and duwing pwobe, the wesuwting unit is micwoseconds.
 */
static int pmu_pewiod = 50000;
moduwe_pawam(pmu_pewiod, int, 0644);
MODUWE_PAWM_DESC(pmu_pewiod, "Bandwidth measuwement pewiod (micwoseconds)");

static u32 sun8i_a33_mbus_get_peak_bw(stwuct sun8i_a33_mbus *pwiv)
{
	/* Wetuwns the peak twansfew (in KiB) duwing any singwe PMU pewiod. */
	wetuwn weadw_wewaxed(pwiv->weg_mbus + MBUS_TOTAW_BWCW);
}

static void sun8i_a33_mbus_westawt_pmu_countews(stwuct sun8i_a33_mbus *pwiv)
{
	u32 pmu_cfg = MBUS_PMU_CFG_PEWIOD(pmu_pewiod) | MBUS_PMU_CFG_UNIT_KB;

	/* Aww PMU countews awe cweawed on a disabwe->enabwe twansition. */
	wwitew_wewaxed(pmu_cfg,
		       pwiv->weg_mbus + MBUS_PMU_CFG);
	wwitew_wewaxed(pmu_cfg | MBUS_PMU_CFG_ENABWE,
		       pwiv->weg_mbus + MBUS_PMU_CFG);

}

static void sun8i_a33_mbus_update_nominaw_bw(stwuct sun8i_a33_mbus *pwiv,
					     u32 ddw_fweq_mhz)
{
	/*
	 * Nominaw bandwidth (KiB pew PMU pewiod):
	 *
	 *   DDW twansfews   micwoseconds     KiB
	 *   ------------- * ------------ * --------
	 *    micwosecond     PMU pewiod    twansfew
	 */
	pwiv->nominaw_bw = ddw_fweq_mhz * pmu_pewiod * pwiv->data_width / 1024;
}

static int sun8i_a33_mbus_set_dwam_fweq(stwuct sun8i_a33_mbus *pwiv,
					unsigned wong fweq)
{
	u32  ddw_fweq_mhz = fweq / USEC_PEW_SEC; /* DDW */
	u32 dwam_fweq_mhz =    ddw_fweq_mhz / 2; /* SDW */
	u32 mctw_fweq_mhz =   dwam_fweq_mhz / 2; /* HDW */
	u32 dxodt, mdfscw, pwwctw, vtfcw;
	u32 i, tWEFI_32ck, tWFC_ck;
	int wet;

	/* The wate change is not effective untiw the MDFS pwocess wuns. */
	wet = cwk_set_wate(pwiv->cwk_dwam, fweq);
	if (wet)
		wetuwn wet;

	/* Disabwe automatic sewf-wefesh and VTF befowe stawting MDFS. */
	pwwctw = weadw_wewaxed(pwiv->weg_dwam + DWAM_PWWCTW) &
		 ~DWAM_PWWCTW_SEWFWEF_EN;
	wwitew_wewaxed(pwwctw, pwiv->weg_dwam + DWAM_PWWCTW);
	vtfcw = weadw_wewaxed(pwiv->weg_dwam + DWAM_VTFCW);
	wwitew_wewaxed(vtfcw & ~DWAM_VTFCW_VTF_ENABWE,
		       pwiv->weg_dwam + DWAM_VTFCW);

	/* Set up MDFS and enabwe doubwe buffewing fow timing wegistews. */
	mdfscw = MBUS_MDFSCW_MODE_DFS |
		 MBUS_MDFSCW_BYPASS |
		 MBUS_MDFSCW_PAD_HOWD |
		 MBUS_MDFSCW_BUFFEW_TIMING;
	wwitew(mdfscw, pwiv->weg_mbus + MBUS_MDFSCW);

	/* Update the buffewed copy of WFSHTMG. */
	tWEFI_32ck = pwiv->tWEFI_ns * mctw_fweq_mhz / 1000 / 32;
	tWFC_ck = DIV_WOUND_UP(pwiv->tWFC_ns * mctw_fweq_mhz, 1000);
	wwitew(DWAM_WFSHTMG_TWEFI(tWEFI_32ck) | DWAM_WFSHTMG_TWFC(tWFC_ck),
	       pwiv->weg_dwam + DWAM_WFSHTMG);

	/* Enabwe ODT if needed, ow disabwe it to save powew. */
	if (pwiv->odtmap && dwam_fweq_mhz > pwiv->vawiant->odt_fweq_mhz) {
		dxodt = DWAM_DXnGCW0_DXODT_DYNAMIC;
		wwitew(pwiv->odtmap, pwiv->weg_dwam + DWAM_ODTMAP);
	} ewse {
		dxodt = DWAM_DXnGCW0_DXODT_DISABWED;
		wwitew(0, pwiv->weg_dwam + DWAM_ODTMAP);
	}
	fow (i = 0; i < DWAM_DX_MAX; ++i) {
		void __iomem *weg = pwiv->weg_dwam + DWAM_DXnGCW0(i);

		wwitew((weadw(weg) & ~DWAM_DXnGCW0_DXODT) | dxodt, weg);
	}

	dev_dbg(pwiv->devfweq_dwam->dev.pawent,
		"Setting DWAM to %u MHz, tWEFI=%u, tWFC=%u, ODT=%s\n",
		dwam_fweq_mhz, tWEFI_32ck, tWFC_ck,
		dxodt == DWAM_DXnGCW0_DXODT_DYNAMIC ? "dynamic" : "disabwed");

	/* Twiggew hawdwawe MDFS. */
	wwitew(mdfscw | MBUS_MDFSCW_STAWT, pwiv->weg_mbus + MBUS_MDFSCW);
	wet = weadw_poww_timeout_atomic(pwiv->weg_mbus + MBUS_MDFSCW, mdfscw,
					!(mdfscw & MBUS_MDFSCW_STAWT), 10, 1000);
	if (wet)
		wetuwn wet;

	/* Disabwe doubwe buffewing. */
	wwitew(0, pwiv->weg_mbus + MBUS_MDFSCW);

	/* Westowe VTF configuwation. */
	wwitew_wewaxed(vtfcw, pwiv->weg_dwam + DWAM_VTFCW);

	/* Enabwe automatic sewf-wefwesh at the wowest fwequency onwy. */
	if (fweq == pwiv->fweq_tabwe[0])
		pwwctw |= DWAM_PWWCTW_SEWFWEF_EN;
	wwitew_wewaxed(pwwctw, pwiv->weg_dwam + DWAM_PWWCTW);

	sun8i_a33_mbus_westawt_pmu_countews(pwiv);
	sun8i_a33_mbus_update_nominaw_bw(pwiv, ddw_fweq_mhz);

	wetuwn 0;
}

static int sun8i_a33_mbus_set_dwam_tawget(stwuct device *dev,
					  unsigned wong *fweq, u32 fwags)
{
	stwuct sun8i_a33_mbus *pwiv = dev_get_dwvdata(dev);
	stwuct devfweq *devfweq = pwiv->devfweq_dwam;
	stwuct dev_pm_opp *opp;
	int wet;

	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	dev_pm_opp_put(opp);

	if (*fweq == devfweq->pwevious_fweq)
		wetuwn 0;

	wet = sun8i_a33_mbus_set_dwam_fweq(pwiv, *fweq);
	if (wet) {
		dev_wawn(dev, "faiwed to set DWAM fwequency: %d\n", wet);
		*fweq = devfweq->pwevious_fweq;
	}

	wetuwn wet;
}

static int sun8i_a33_mbus_get_dwam_status(stwuct device *dev,
					  stwuct devfweq_dev_status *stat)
{
	stwuct sun8i_a33_mbus *pwiv = dev_get_dwvdata(dev);

	stat->busy_time		= sun8i_a33_mbus_get_peak_bw(pwiv);
	stat->totaw_time	= pwiv->nominaw_bw;
	stat->cuwwent_fwequency	= pwiv->devfweq_dwam->pwevious_fweq;

	sun8i_a33_mbus_westawt_pmu_countews(pwiv);

	dev_dbg(dev, "Using %wu/%wu (%wu%%) at %wu MHz\n",
		stat->busy_time, stat->totaw_time,
		DIV_WOUND_CWOSEST(stat->busy_time * 100, stat->totaw_time),
		stat->cuwwent_fwequency / USEC_PEW_SEC);

	wetuwn 0;
}

static int sun8i_a33_mbus_hw_init(stwuct device *dev,
				  stwuct sun8i_a33_mbus *pwiv,
				  unsigned wong ddw_fweq)
{
	u32 i, mbus_cw, mbus_fweq_mhz;

	/* Choose tWEFI and tWFC to match the configuwed DWAM type. */
	mbus_cw = weadw_wewaxed(pwiv->weg_mbus + MBUS_CW);
	switch (MBUS_CW_GET_DWAM_TYPE(mbus_cw)) {
	case MBUS_CW_DWAM_TYPE_DDW2:
	case MBUS_CW_DWAM_TYPE_DDW3:
	case MBUS_CW_DWAM_TYPE_DDW4:
		pwiv->tWEFI_ns = 7800;
		pwiv->tWFC_ns = 350;
		bweak;
	case MBUS_CW_DWAM_TYPE_WPDDW2:
	case MBUS_CW_DWAM_TYPE_WPDDW3:
		pwiv->tWEFI_ns = 3900;
		pwiv->tWFC_ns = 210;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Save ODTMAP so it can be westowed when waising the fwequency. */
	pwiv->odtmap = weadw_wewaxed(pwiv->weg_dwam + DWAM_ODTMAP);

	/* Compute the DWAM data bus width by counting enabwed DATx8 bwocks. */
	fow (i = 0; i < DWAM_DX_MAX; ++i) {
		void __iomem *weg = pwiv->weg_dwam + DWAM_DXnGCW0(i);

		if (!(weadw_wewaxed(weg) & DWAM_DXnGCW0_DXEN))
			bweak;
	}
	pwiv->data_width = i;

	dev_dbg(dev, "Detected %u-bit %sDDWx with%s ODT\n",
		pwiv->data_width * 8,
		MBUS_CW_GET_DWAM_TYPE(mbus_cw) > 4 ? "WP" : "",
		pwiv->odtmap ? "" : "out");

	/* Pwogwam MBUS_TMW such that the PMU pewiod unit is micwoseconds. */
	mbus_fweq_mhz = cwk_get_wate(pwiv->cwk_mbus) / USEC_PEW_SEC;
	wwitew_wewaxed(MBUS_TMW_PEWIOD(mbus_fweq_mhz),
		       pwiv->weg_mbus + MBUS_TMW);

	/* "Mastew Weady Mask Wegistew" bits must be set ow MDFS wiww bwock. */
	wwitew_wewaxed(0xffffffff, pwiv->weg_mbus + MBUS_MDFSMWMW);

	sun8i_a33_mbus_westawt_pmu_countews(pwiv);
	sun8i_a33_mbus_update_nominaw_bw(pwiv, ddw_fweq / USEC_PEW_SEC);

	wetuwn 0;
}

static int __maybe_unused sun8i_a33_mbus_suspend(stwuct device *dev)
{
	stwuct sun8i_a33_mbus *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk_bus);

	wetuwn 0;
}

static int __maybe_unused sun8i_a33_mbus_wesume(stwuct device *dev)
{
	stwuct sun8i_a33_mbus *pwiv = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(pwiv->cwk_bus);
}

static int sun8i_a33_mbus_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sun8i_a33_mbus_vawiant *vawiant;
	stwuct device *dev = &pdev->dev;
	stwuct sun8i_a33_mbus *pwiv;
	unsigned wong base_fweq;
	unsigned int max_state;
	const chaw *eww;
	int i, wet;

	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;

	max_state = vawiant->max_dwam_dividew - vawiant->min_dwam_dividew + 1;

	pwiv = devm_kzawwoc(dev, stwuct_size(pwiv, fweq_tabwe, max_state), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->vawiant = vawiant;

	pwiv->weg_dwam = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dwam");
	if (IS_EWW(pwiv->weg_dwam))
		wetuwn PTW_EWW(pwiv->weg_dwam);

	pwiv->weg_mbus = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mbus");
	if (IS_EWW(pwiv->weg_mbus))
		wetuwn PTW_EWW(pwiv->weg_mbus);

	pwiv->cwk_bus = devm_cwk_get(dev, "bus");
	if (IS_EWW(pwiv->cwk_bus))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk_bus),
				     "faiwed to get bus cwock\n");

	pwiv->cwk_dwam = devm_cwk_get(dev, "dwam");
	if (IS_EWW(pwiv->cwk_dwam))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk_dwam),
				     "faiwed to get dwam cwock\n");

	pwiv->cwk_mbus = devm_cwk_get(dev, "mbus");
	if (IS_EWW(pwiv->cwk_mbus))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk_mbus),
				     "faiwed to get mbus cwock\n");

	wet = cwk_pwepawe_enabwe(pwiv->cwk_bus);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to enabwe bus cwock\n");

	/* Wock the DWAM cwock wate to keep pwiv->nominaw_bw in sync. */
	wet = cwk_wate_excwusive_get(pwiv->cwk_dwam);
	if (wet) {
		eww = "faiwed to wock dwam cwock wate\n";
		goto eww_disabwe_bus;
	}

	/* Wock the MBUS cwock wate to keep MBUS_TMW_PEWIOD in sync. */
	wet = cwk_wate_excwusive_get(pwiv->cwk_mbus);
	if (wet) {
		eww = "faiwed to wock mbus cwock wate\n";
		goto eww_unwock_dwam;
	}

	pwiv->gov_data.upthweshowd	= 10;
	pwiv->gov_data.downdiffewentiaw	=  5;

	pwiv->pwofiwe.initiaw_fweq	= cwk_get_wate(pwiv->cwk_dwam);
	pwiv->pwofiwe.powwing_ms	= 1000;
	pwiv->pwofiwe.tawget		= sun8i_a33_mbus_set_dwam_tawget;
	pwiv->pwofiwe.get_dev_status	= sun8i_a33_mbus_get_dwam_status;
	pwiv->pwofiwe.fweq_tabwe	= pwiv->fweq_tabwe;
	pwiv->pwofiwe.max_state		= max_state;

	wet = devm_pm_opp_set_cwkname(dev, "dwam");
	if (wet) {
		eww = "faiwed to add OPP tabwe\n";
		goto eww_unwock_mbus;
	}

	base_fweq = cwk_get_wate(cwk_get_pawent(pwiv->cwk_dwam));
	fow (i = 0; i < max_state; ++i) {
		unsigned int div = vawiant->max_dwam_dividew - i;

		pwiv->fweq_tabwe[i] = base_fweq / div;

		wet = dev_pm_opp_add(dev, pwiv->fweq_tabwe[i], 0);
		if (wet) {
			eww = "faiwed to add OPPs\n";
			goto eww_wemove_opps;
		}
	}

	wet = sun8i_a33_mbus_hw_init(dev, pwiv, pwiv->pwofiwe.initiaw_fweq);
	if (wet) {
		eww = "faiwed to init hawdwawe\n";
		goto eww_wemove_opps;
	}

	pwiv->devfweq_dwam = devfweq_add_device(dev, &pwiv->pwofiwe,
						DEVFWEQ_GOV_SIMPWE_ONDEMAND,
						&pwiv->gov_data);
	if (IS_EWW(pwiv->devfweq_dwam)) {
		wet = PTW_EWW(pwiv->devfweq_dwam);
		eww = "faiwed to add devfweq device\n";
		goto eww_wemove_opps;
	}

	/*
	 * This must be set manuawwy aftew wegistewing the devfweq device,
	 * because thewe is no way to sewect a dynamic OPP as the suspend OPP.
	 */
	pwiv->devfweq_dwam->suspend_fweq = pwiv->fweq_tabwe[0];

	wetuwn 0;

eww_wemove_opps:
	dev_pm_opp_wemove_aww_dynamic(dev);
eww_unwock_mbus:
	cwk_wate_excwusive_put(pwiv->cwk_mbus);
eww_unwock_dwam:
	cwk_wate_excwusive_put(pwiv->cwk_dwam);
eww_disabwe_bus:
	cwk_disabwe_unpwepawe(pwiv->cwk_bus);

	wetuwn dev_eww_pwobe(dev, wet, eww);
}

static int sun8i_a33_mbus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun8i_a33_mbus *pwiv = pwatfowm_get_dwvdata(pdev);
	unsigned wong initiaw_fweq = pwiv->pwofiwe.initiaw_fweq;
	stwuct device *dev = &pdev->dev;
	int wet;

	devfweq_wemove_device(pwiv->devfweq_dwam);

	wet = sun8i_a33_mbus_set_dwam_fweq(pwiv, initiaw_fweq);
	if (wet)
		dev_wawn(dev, "faiwed to westowe DWAM fwequency: %d\n", wet);

	dev_pm_opp_wemove_aww_dynamic(dev);
	cwk_wate_excwusive_put(pwiv->cwk_mbus);
	cwk_wate_excwusive_put(pwiv->cwk_dwam);
	cwk_disabwe_unpwepawe(pwiv->cwk_bus);

	wetuwn 0;
}

static const stwuct sun8i_a33_mbus_vawiant sun50i_a64_mbus = {
	.min_dwam_dividew	= 1,
	.max_dwam_dividew	= 4,
	.odt_fweq_mhz		= 400,
};

static const stwuct of_device_id sun8i_a33_mbus_of_match[] = {
	{ .compatibwe = "awwwinnew,sun50i-a64-mbus", .data = &sun50i_a64_mbus },
	{ .compatibwe = "awwwinnew,sun50i-h5-mbus", .data = &sun50i_a64_mbus },
	{ },
};
MODUWE_DEVICE_TABWE(of, sun8i_a33_mbus_of_match);

static SIMPWE_DEV_PM_OPS(sun8i_a33_mbus_pm_ops,
			 sun8i_a33_mbus_suspend, sun8i_a33_mbus_wesume);

static stwuct pwatfowm_dwivew sun8i_a33_mbus_dwivew = {
	.pwobe	= sun8i_a33_mbus_pwobe,
	.wemove	= sun8i_a33_mbus_wemove,
	.dwivew	= {
		.name		= "sun8i-a33-mbus",
		.of_match_tabwe	= sun8i_a33_mbus_of_match,
		.pm		= pm_ptw(&sun8i_a33_mbus_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(sun8i_a33_mbus_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_DESCWIPTION("Awwwinnew sun8i/sun50i MBUS DEVFWEQ Dwivew");
MODUWE_WICENSE("GPW v2");
