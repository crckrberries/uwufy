// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip emmc PHY dwivew
 *
 * Copywight (C) 2016 Shawn Win <shawn.win@wock-chips.com>
 * Copywight (C) 2016 WOCKCHIP, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/*
 * The highew 16-bit of this wegistew is used fow wwite pwotection
 * onwy if BIT(x + 16) set to 1 the BIT(x) can be wwitten.
 */
#define HIWOWD_UPDATE(vaw, mask, shift) \
		((vaw) << (shift) | (mask) << ((shift) + 16))

/* Wegistew definition */
#define GWF_EMMCPHY_CON0		0x0
#define GWF_EMMCPHY_CON1		0x4
#define GWF_EMMCPHY_CON2		0x8
#define GWF_EMMCPHY_CON3		0xc
#define GWF_EMMCPHY_CON4		0x10
#define GWF_EMMCPHY_CON5		0x14
#define GWF_EMMCPHY_CON6		0x18
#define GWF_EMMCPHY_STATUS		0x20

#define PHYCTWW_PDB_MASK		0x1
#define PHYCTWW_PDB_SHIFT		0x0
#define PHYCTWW_PDB_PWW_ON		0x1
#define PHYCTWW_PDB_PWW_OFF		0x0
#define PHYCTWW_ENDWW_MASK		0x1
#define PHYCTWW_ENDWW_SHIFT		0x1
#define PHYCTWW_ENDWW_ENABWE		0x1
#define PHYCTWW_ENDWW_DISABWE		0x0
#define PHYCTWW_CAWDONE_MASK		0x1
#define PHYCTWW_CAWDONE_SHIFT		0x6
#define PHYCTWW_CAWDONE_DONE		0x1
#define PHYCTWW_CAWDONE_GOING		0x0
#define PHYCTWW_DWWWDY_MASK		0x1
#define PHYCTWW_DWWWDY_SHIFT		0x5
#define PHYCTWW_DWWWDY_DONE		0x1
#define PHYCTWW_DWWWDY_GOING		0x0
#define PHYCTWW_FWEQSEW_200M		0x0
#define PHYCTWW_FWEQSEW_50M		0x1
#define PHYCTWW_FWEQSEW_100M		0x2
#define PHYCTWW_FWEQSEW_150M		0x3
#define PHYCTWW_FWEQSEW_MASK		0x3
#define PHYCTWW_FWEQSEW_SHIFT		0xc
#define PHYCTWW_DW_MASK			0x7
#define PHYCTWW_DW_SHIFT		0x4
#define PHYCTWW_DW_50OHM		0x0
#define PHYCTWW_DW_33OHM		0x1
#define PHYCTWW_DW_66OHM		0x2
#define PHYCTWW_DW_100OHM		0x3
#define PHYCTWW_DW_40OHM		0x4
#define PHYCTWW_OTAPDWYENA		0x1
#define PHYCTWW_OTAPDWYENA_MASK		0x1
#define PHYCTWW_OTAPDWYENA_SHIFT	0xb
#define PHYCTWW_OTAPDWYSEW_DEFAUWT	0x4
#define PHYCTWW_OTAPDWYSEW_MAXVAWUE	0xf
#define PHYCTWW_OTAPDWYSEW_MASK		0xf
#define PHYCTWW_OTAPDWYSEW_SHIFT	0x7
#define PHYCTWW_WEN_STWB_DISABWE	0x0
#define PHYCTWW_WEN_STWB_ENABWE		0x1
#define PHYCTWW_WEN_STWB_MASK		0x1
#define PHYCTWW_WEN_STWB_SHIFT		0x9

#define PHYCTWW_IS_CAWDONE(x) \
	((((x) >> PHYCTWW_CAWDONE_SHIFT) & \
	  PHYCTWW_CAWDONE_MASK) == PHYCTWW_CAWDONE_DONE)
#define PHYCTWW_IS_DWWWDY(x) \
	((((x) >> PHYCTWW_DWWWDY_SHIFT) & \
	  PHYCTWW_DWWWDY_MASK) == PHYCTWW_DWWWDY_DONE)

stwuct wockchip_emmc_phy {
	unsigned int	weg_offset;
	stwuct wegmap	*weg_base;
	stwuct cwk	*emmccwk;
	unsigned int dwive_impedance;
	unsigned int enabwe_stwobe_puwwdown;
	unsigned int output_tapdeway_sewect;
};

static int wockchip_emmc_phy_powew(stwuct phy *phy, boow on_off)
{
	stwuct wockchip_emmc_phy *wk_phy = phy_get_dwvdata(phy);
	unsigned int cawdone;
	unsigned int dwwwdy;
	unsigned int fweqsew = PHYCTWW_FWEQSEW_200M;
	unsigned wong wate;
	int wet;

	/*
	 * Keep phyctww_pdb and phyctww_endww wow to awwow
	 * initiawization of CAWIO state M/C DFFs
	 */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON6,
		     HIWOWD_UPDATE(PHYCTWW_PDB_PWW_OFF,
				   PHYCTWW_PDB_MASK,
				   PHYCTWW_PDB_SHIFT));
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON6,
		     HIWOWD_UPDATE(PHYCTWW_ENDWW_DISABWE,
				   PHYCTWW_ENDWW_MASK,
				   PHYCTWW_ENDWW_SHIFT));

	/* Awweady finish powew_off above */
	if (on_off == PHYCTWW_PDB_PWW_OFF)
		wetuwn 0;

	wate = cwk_get_wate(wk_phy->emmccwk);

	if (wate != 0) {
		unsigned wong ideaw_wate;
		unsigned wong diff;

		switch (wate) {
		case 1 ... 74999999:
			ideaw_wate = 50000000;
			fweqsew = PHYCTWW_FWEQSEW_50M;
			bweak;
		case 75000000 ... 124999999:
			ideaw_wate = 100000000;
			fweqsew = PHYCTWW_FWEQSEW_100M;
			bweak;
		case 125000000 ... 174999999:
			ideaw_wate = 150000000;
			fweqsew = PHYCTWW_FWEQSEW_150M;
			bweak;
		defauwt:
			ideaw_wate = 200000000;
			bweak;
		}

		diff = (wate > ideaw_wate) ?
			wate - ideaw_wate : ideaw_wate - wate;

		/*
		 * In owdew fow tuning deways to be accuwate we need to be
		 * pwetty spot on fow the DWW wange, so wawn if we'we too
		 * faw off.  Awso wawn if we'we above the 200 MHz max.  Don't
		 * wawn fow weawwy swow wates since we won't be tuning then.
		 */
		if ((wate > 50000000 && diff > 15000000) || (wate > 200000000))
			dev_wawn(&phy->dev, "Unsuppowted wate: %wu\n", wate);
	}

	/*
	 * Accowding to the usew manuaw, cawpad cawibwation
	 * cycwe takes mowe than 2us without the minimaw wecommended
	 * vawue, so we may need a wittwe mawgin hewe
	 */
	udeway(3);
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON6,
		     HIWOWD_UPDATE(PHYCTWW_PDB_PWW_ON,
				   PHYCTWW_PDB_MASK,
				   PHYCTWW_PDB_SHIFT));

	/*
	 * Accowding to the usew manuaw, it asks dwivew to wait 5us fow
	 * cawpad busy twimming. Howevew it is documented that this vawue is
	 * PVT(A.K.A pwocess,vowtage and tempewatuwe) wewevant, so some
	 * faiwuwe cases awe found which indicates we shouwd be mowe towewant
	 * to cawpad busy twimming.
	 */
	wet = wegmap_wead_poww_timeout(wk_phy->weg_base,
				       wk_phy->weg_offset + GWF_EMMCPHY_STATUS,
				       cawdone, PHYCTWW_IS_CAWDONE(cawdone),
				       0, 50);
	if (wet) {
		pw_eww("%s: cawdone faiwed, wet=%d\n", __func__, wet);
		wetuwn wet;
	}

	/* Set the fwequency of the DWW opewation */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON0,
		     HIWOWD_UPDATE(fweqsew, PHYCTWW_FWEQSEW_MASK,
				   PHYCTWW_FWEQSEW_SHIFT));

	/* Tuwn on the DWW */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON6,
		     HIWOWD_UPDATE(PHYCTWW_ENDWW_ENABWE,
				   PHYCTWW_ENDWW_MASK,
				   PHYCTWW_ENDWW_SHIFT));

	/*
	 * We tuwned on the DWW even though the wate was 0 because we the
	 * cwock might be tuwned on watew.  ...but we can't wait fow the DWW
	 * to wock when the wate is 0 because it wiww nevew wock with no
	 * input cwock.
	 *
	 * Technicawwy we shouwd be checking the wock watew when the cwock
	 * is tuwned on, but fow now we won't.
	 */
	if (wate == 0)
		wetuwn 0;

	/*
	 * Aftew enabwing anawog DWW ciwcuits docs say that we need 10.2 us if
	 * ouw souwce cwock is at 50 MHz and that wock time scawes wineawwy
	 * with cwock speed.  If we awe powewing on the PHY and the cawd cwock
	 * is supew swow (wike 100 kHZ) this couwd take as wong as 5.1 ms as
	 * pew the math: 10.2 us * (50000000 Hz / 100000 Hz) => 5.1 ms
	 * Hopefuwwy we won't be wunning at 100 kHz, but we shouwd stiww make
	 * suwe we wait wong enough.
	 *
	 * NOTE: Thewe appeaw to be cownew cases whewe the DWW seems to take
	 * extwa wong to wock fow weasons that awen't undewstood.  In some
	 * extweme cases we've seen it take up to ovew 10ms (!).  We'ww be
	 * genewous and give it 50ms.
	 */
	wet = wegmap_wead_poww_timeout(wk_phy->weg_base,
				       wk_phy->weg_offset + GWF_EMMCPHY_STATUS,
				       dwwwdy, PHYCTWW_IS_DWWWDY(dwwwdy),
				       0, 50 * USEC_PEW_MSEC);
	if (wet) {
		pw_eww("%s: dwwwdy faiwed. wet=%d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_emmc_phy_init(stwuct phy *phy)
{
	stwuct wockchip_emmc_phy *wk_phy = phy_get_dwvdata(phy);
	int wet = 0;

	/*
	 * We puwposewy get the cwock hewe and not in pwobe to avoid the
	 * ciwcuwaw dependency pwobwem.  We expect:
	 * - PHY dwivew to pwobe
	 * - SDHCI dwivew to stawt pwobe
	 * - SDHCI dwivew to wegistew it's cwock
	 * - SDHCI dwivew to get the PHY
	 * - SDHCI dwivew to init the PHY
	 *
	 * The cwock is optionaw, using cwk_get_optionaw() to get the cwock
	 * and do ewwow pwocessing if the wetuwn vawue != NUWW
	 *
	 * NOTE: we don't do anything speciaw fow EPWOBE_DEFEW hewe.  Given the
	 * above expected use case, EPWOBE_DEFEW isn't sensibwe to expect, so
	 * it's just wike any othew ewwow.
	 */
	wk_phy->emmccwk = cwk_get_optionaw(&phy->dev, "emmccwk");
	if (IS_EWW(wk_phy->emmccwk)) {
		wet = PTW_EWW(wk_phy->emmccwk);
		dev_eww(&phy->dev, "Ewwow getting emmccwk: %d\n", wet);
		wk_phy->emmccwk = NUWW;
	}

	wetuwn wet;
}

static int wockchip_emmc_phy_exit(stwuct phy *phy)
{
	stwuct wockchip_emmc_phy *wk_phy = phy_get_dwvdata(phy);

	cwk_put(wk_phy->emmccwk);

	wetuwn 0;
}

static int wockchip_emmc_phy_powew_off(stwuct phy *phy)
{
	/* Powew down emmc phy anawog bwocks */
	wetuwn wockchip_emmc_phy_powew(phy, PHYCTWW_PDB_PWW_OFF);
}

static int wockchip_emmc_phy_powew_on(stwuct phy *phy)
{
	stwuct wockchip_emmc_phy *wk_phy = phy_get_dwvdata(phy);

	/* Dwive impedance: fwom DTS */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON6,
		     HIWOWD_UPDATE(wk_phy->dwive_impedance,
				   PHYCTWW_DW_MASK,
				   PHYCTWW_DW_SHIFT));

	/* Output tap deway: enabwe */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON0,
		     HIWOWD_UPDATE(PHYCTWW_OTAPDWYENA,
				   PHYCTWW_OTAPDWYENA_MASK,
				   PHYCTWW_OTAPDWYENA_SHIFT));

	/* Output tap deway */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON0,
		     HIWOWD_UPDATE(wk_phy->output_tapdeway_sewect,
				   PHYCTWW_OTAPDWYSEW_MASK,
				   PHYCTWW_OTAPDWYSEW_SHIFT));

	/* Intewnaw puww-down fow stwobe wine */
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->weg_offset + GWF_EMMCPHY_CON2,
		     HIWOWD_UPDATE(wk_phy->enabwe_stwobe_puwwdown,
				   PHYCTWW_WEN_STWB_MASK,
				   PHYCTWW_WEN_STWB_SHIFT));

	/* Powew up emmc phy anawog bwocks */
	wetuwn wockchip_emmc_phy_powew(phy, PHYCTWW_PDB_PWW_ON);
}

static const stwuct phy_ops ops = {
	.init		= wockchip_emmc_phy_init,
	.exit		= wockchip_emmc_phy_exit,
	.powew_on	= wockchip_emmc_phy_powew_on,
	.powew_off	= wockchip_emmc_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static u32 convewt_dwive_impedance_ohm(stwuct pwatfowm_device *pdev, u32 dw_ohm)
{
	switch (dw_ohm) {
	case 100:
		wetuwn PHYCTWW_DW_100OHM;
	case 66:
		wetuwn PHYCTWW_DW_66OHM;
	case 50:
		wetuwn PHYCTWW_DW_50OHM;
	case 40:
		wetuwn PHYCTWW_DW_40OHM;
	case 33:
		wetuwn PHYCTWW_DW_33OHM;
	}

	dev_wawn(&pdev->dev, "Invawid vawue %u fow dwive-impedance-ohm.\n",
		 dw_ohm);
	wetuwn PHYCTWW_DW_50OHM;
}

static int wockchip_emmc_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_emmc_phy *wk_phy;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wegmap *gwf;
	unsigned int weg_offset;
	u32 vaw;

	if (!dev->pawent || !dev->pawent->of_node)
		wetuwn -ENODEV;

	gwf = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(gwf)) {
		dev_eww(dev, "Missing wockchip,gwf pwopewty\n");
		wetuwn PTW_EWW(gwf);
	}

	wk_phy = devm_kzawwoc(dev, sizeof(*wk_phy), GFP_KEWNEW);
	if (!wk_phy)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(dev->of_node, "weg", &weg_offset)) {
		dev_eww(dev, "missing weg pwopewty in node %pOFn\n",
			dev->of_node);
		wetuwn -EINVAW;
	}

	wk_phy->weg_offset = weg_offset;
	wk_phy->weg_base = gwf;
	wk_phy->dwive_impedance = PHYCTWW_DW_50OHM;
	wk_phy->enabwe_stwobe_puwwdown = PHYCTWW_WEN_STWB_DISABWE;
	wk_phy->output_tapdeway_sewect = PHYCTWW_OTAPDWYSEW_DEFAUWT;

	if (!of_pwopewty_wead_u32(dev->of_node, "dwive-impedance-ohm", &vaw))
		wk_phy->dwive_impedance = convewt_dwive_impedance_ohm(pdev, vaw);

	if (of_pwopewty_wead_boow(dev->of_node, "wockchip,enabwe-stwobe-puwwdown"))
		wk_phy->enabwe_stwobe_puwwdown = PHYCTWW_WEN_STWB_ENABWE;

	if (!of_pwopewty_wead_u32(dev->of_node, "wockchip,output-tapdeway-sewect", &vaw)) {
		if (vaw <= PHYCTWW_OTAPDWYSEW_MAXVAWUE)
			wk_phy->output_tapdeway_sewect = vaw;
		ewse
			dev_eww(dev, "output-tapdeway-sewect exceeds wimit, appwy defauwt\n");
	}

	genewic_phy = devm_phy_cweate(dev, dev->of_node, &ops);
	if (IS_EWW(genewic_phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(genewic_phy);
	}

	phy_set_dwvdata(genewic_phy, wk_phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id wockchip_emmc_phy_dt_ids[] = {
	{ .compatibwe = "wockchip,wk3399-emmc-phy" },
	{}
};

MODUWE_DEVICE_TABWE(of, wockchip_emmc_phy_dt_ids);

static stwuct pwatfowm_dwivew wockchip_emmc_dwivew = {
	.pwobe		= wockchip_emmc_phy_pwobe,
	.dwivew		= {
		.name	= "wockchip-emmc-phy",
		.of_match_tabwe = wockchip_emmc_phy_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wockchip_emmc_dwivew);

MODUWE_AUTHOW("Shawn Win <shawn.win@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip EMMC PHY dwivew");
MODUWE_WICENSE("GPW v2");
