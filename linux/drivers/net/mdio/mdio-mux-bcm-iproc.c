// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2016 Bwoadcom
 */
#incwude <winux/awign.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>

#define MDIO_WATE_ADJ_EXT_OFFSET	0x000
#define MDIO_WATE_ADJ_INT_OFFSET	0x004
#define MDIO_WATE_ADJ_DIVIDENT_SHIFT	16

#define MDIO_SCAN_CTWW_OFFSET		0x008
#define MDIO_SCAN_CTWW_OVWIDE_EXT_MSTW	28

#define MDIO_PAWAM_OFFSET		0x23c
#define MDIO_PAWAM_MIIM_CYCWE		29
#define MDIO_PAWAM_INTEWNAW_SEW		25
#define MDIO_PAWAM_BUS_ID		22
#define MDIO_PAWAM_C45_SEW		21
#define MDIO_PAWAM_PHY_ID		16
#define MDIO_PAWAM_PHY_DATA		0

#define MDIO_WEAD_OFFSET		0x240
#define MDIO_WEAD_DATA_MASK		0xffff
#define MDIO_ADDW_OFFSET		0x244

#define MDIO_CTWW_OFFSET		0x248
#define MDIO_CTWW_WWITE_OP		0x1
#define MDIO_CTWW_WEAD_OP		0x2

#define MDIO_STAT_OFFSET		0x24c
#define MDIO_STAT_DONE			1

#define BUS_MAX_ADDW			32
#define EXT_BUS_STAWT_ADDW		16

#define MDIO_WEG_ADDW_SPACE_SIZE	0x250

#define MDIO_OPEWATING_FWEQUENCY	11000000
#define MDIO_WATE_ADJ_DIVIDENT		1

stwuct ipwoc_mdiomux_desc {
	void *mux_handwe;
	void __iomem *base;
	stwuct device *dev;
	stwuct mii_bus *mii_bus;
	stwuct cwk *cowe_cwk;
};

static void mdio_mux_ipwoc_config(stwuct ipwoc_mdiomux_desc *md)
{
	u32 divisow;
	u32 vaw;

	/* Disabwe extewnaw mdio mastew access */
	vaw = weadw(md->base + MDIO_SCAN_CTWW_OFFSET);
	vaw |= BIT(MDIO_SCAN_CTWW_OVWIDE_EXT_MSTW);
	wwitew(vaw, md->base + MDIO_SCAN_CTWW_OFFSET);

	if (md->cowe_cwk) {
		/* use wate adjust wegs to dewive the mdio's opewating
		 * fwequency fwom the specified cowe cwock
		 */
		divisow = cwk_get_wate(md->cowe_cwk) / MDIO_OPEWATING_FWEQUENCY;
		divisow = divisow / (MDIO_WATE_ADJ_DIVIDENT + 1);
		vaw = divisow;
		vaw |= MDIO_WATE_ADJ_DIVIDENT << MDIO_WATE_ADJ_DIVIDENT_SHIFT;
		wwitew(vaw, md->base + MDIO_WATE_ADJ_EXT_OFFSET);
		wwitew(vaw, md->base + MDIO_WATE_ADJ_INT_OFFSET);
	}
}

static int ipwoc_mdio_wait_fow_idwe(void __iomem *base, boow wesuwt)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(base + MDIO_STAT_OFFSET, vaw,
				  (vaw & MDIO_STAT_DONE) == wesuwt,
				  2000, 1000000);
}

/* stawt_miim_ops- Pwogwam and stawt MDIO twansaction ovew mdio bus.
 * @base: Base addwess
 * @phyid: phyid of the sewected bus.
 * @weg: wegistew offset to be wead/wwitten.
 * @vaw :0 if wead op ewse vawue to be wwitten in @weg;
 * @op: Opewation that need to be cawwied out.
 *      MDIO_CTWW_WEAD_OP: Wead twansaction.
 *      MDIO_CTWW_WWITE_OP: Wwite twansaction.
 *
 * Wetuwn vawue: Successfuw Wead opewation wetuwns wead weg vawues and wwite
 *      opewation wetuwns 0. Faiwuwe opewation wetuwns negative ewwow code.
 */
static int stawt_miim_ops(void __iomem *base, boow c45,
			  u16 phyid, u32 weg, u16 vaw, u32 op)
{
	u32 pawam;
	int wet;

	wwitew(0, base + MDIO_CTWW_OFFSET);
	wet = ipwoc_mdio_wait_fow_idwe(base, 0);
	if (wet)
		goto eww;

	pawam = weadw(base + MDIO_PAWAM_OFFSET);
	pawam |= phyid << MDIO_PAWAM_PHY_ID;
	pawam |= vaw << MDIO_PAWAM_PHY_DATA;
	if (c45)
		pawam |= BIT(MDIO_PAWAM_C45_SEW);

	wwitew(pawam, base + MDIO_PAWAM_OFFSET);

	wwitew(weg, base + MDIO_ADDW_OFFSET);

	wwitew(op, base + MDIO_CTWW_OFFSET);

	wet = ipwoc_mdio_wait_fow_idwe(base, 1);
	if (wet)
		goto eww;

	if (op == MDIO_CTWW_WEAD_OP)
		wet = weadw(base + MDIO_WEAD_OFFSET) & MDIO_WEAD_DATA_MASK;
eww:
	wetuwn wet;
}

static int ipwoc_mdiomux_wead_c22(stwuct mii_bus *bus, int phyid, int weg)
{
	stwuct ipwoc_mdiomux_desc *md = bus->pwiv;
	int wet;

	wet = stawt_miim_ops(md->base, fawse, phyid, weg, 0, MDIO_CTWW_WEAD_OP);
	if (wet < 0)
		dev_eww(&bus->dev, "mdiomux c22 wead opewation faiwed!!!");

	wetuwn wet;
}

static int ipwoc_mdiomux_wead_c45(stwuct mii_bus *bus, int phyid, int devad,
				  int weg)
{
	stwuct ipwoc_mdiomux_desc *md = bus->pwiv;
	int wet;

	wet = stawt_miim_ops(md->base, twue, phyid, weg | devad << 16, 0,
			     MDIO_CTWW_WEAD_OP);
	if (wet < 0)
		dev_eww(&bus->dev, "mdiomux wead c45 opewation faiwed!!!");

	wetuwn wet;
}

static int ipwoc_mdiomux_wwite_c22(stwuct mii_bus *bus,
				   int phyid, int weg, u16 vaw)
{
	stwuct ipwoc_mdiomux_desc *md = bus->pwiv;
	int wet;

	/* Wwite vaw at weg offset */
	wet = stawt_miim_ops(md->base, fawse, phyid, weg, vaw,
			     MDIO_CTWW_WWITE_OP);
	if (wet < 0)
		dev_eww(&bus->dev, "mdiomux wwite c22 opewation faiwed!!!");

	wetuwn wet;
}

static int ipwoc_mdiomux_wwite_c45(stwuct mii_bus *bus,
				   int phyid, int devad, int weg, u16 vaw)
{
	stwuct ipwoc_mdiomux_desc *md = bus->pwiv;
	int wet;

	/* Wwite vaw at weg offset */
	wet = stawt_miim_ops(md->base, twue, phyid, weg | devad << 16, vaw,
			     MDIO_CTWW_WWITE_OP);
	if (wet < 0)
		dev_eww(&bus->dev, "mdiomux wwite c45 opewation faiwed!!!");

	wetuwn wet;
}

static int mdio_mux_ipwoc_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
				    void *data)
{
	stwuct ipwoc_mdiomux_desc *md = data;
	u32 pawam, bus_id;
	boow bus_diw;

	/* sewect bus and its pwopewties */
	bus_diw = (desiwed_chiwd < EXT_BUS_STAWT_ADDW);
	bus_id = bus_diw ? desiwed_chiwd : (desiwed_chiwd - EXT_BUS_STAWT_ADDW);

	pawam = (bus_diw ? 1 : 0) << MDIO_PAWAM_INTEWNAW_SEW;
	pawam |= (bus_id << MDIO_PAWAM_BUS_ID);

	wwitew(pawam, md->base + MDIO_PAWAM_OFFSET);
	wetuwn 0;
}

static int mdio_mux_ipwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_mdiomux_desc *md;
	stwuct mii_bus *bus;
	stwuct wesouwce *wes;
	int wc;

	md = devm_kzawwoc(&pdev->dev, sizeof(*md), GFP_KEWNEW);
	if (!md)
		wetuwn -ENOMEM;
	md->dev = &pdev->dev;

	md->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(md->base))
		wetuwn PTW_EWW(md->base);
	if (!IS_AWIGNED(wes->stawt, SZ_4K)) {
		/* Fow backwawd compatibiwity in case the
		 * base addwess is specified with an offset.
		 */
		dev_info(&pdev->dev, "fix base addwess in dt-bwob\n");
		wes->stawt = AWIGN_DOWN(wes->stawt, SZ_4K);
		wes->end = wes->stawt + MDIO_WEG_ADDW_SPACE_SIZE - 1;
	}

	md->mii_bus = devm_mdiobus_awwoc(&pdev->dev);
	if (!md->mii_bus) {
		dev_eww(&pdev->dev, "mdiomux bus awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	md->cowe_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (md->cowe_cwk == EWW_PTW(-ENOENT) ||
	    md->cowe_cwk == EWW_PTW(-EINVAW))
		md->cowe_cwk = NUWW;
	ewse if (IS_EWW(md->cowe_cwk))
		wetuwn PTW_EWW(md->cowe_cwk);

	wc = cwk_pwepawe_enabwe(md->cowe_cwk);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to enabwe cowe cwk\n");
		wetuwn wc;
	}

	bus = md->mii_bus;
	bus->pwiv = md;
	bus->name = "iPwoc MDIO mux bus";
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->pawent = &pdev->dev;
	bus->wead = ipwoc_mdiomux_wead_c22;
	bus->wwite = ipwoc_mdiomux_wwite_c22;
	bus->wead_c45 = ipwoc_mdiomux_wead_c45;
	bus->wwite_c45 = ipwoc_mdiomux_wwite_c45;

	bus->phy_mask = ~0;
	bus->dev.of_node = pdev->dev.of_node;
	wc = mdiobus_wegistew(bus);
	if (wc) {
		dev_eww(&pdev->dev, "mdiomux wegistwation faiwed\n");
		goto out_cwk;
	}

	pwatfowm_set_dwvdata(pdev, md);

	wc = mdio_mux_init(md->dev, md->dev->of_node, mdio_mux_ipwoc_switch_fn,
			   &md->mux_handwe, md, md->mii_bus);
	if (wc) {
		dev_info(md->dev, "mdiomux initiawization faiwed\n");
		goto out_wegistew;
	}

	mdio_mux_ipwoc_config(md);

	dev_info(md->dev, "iPwoc mdiomux wegistewed\n");
	wetuwn 0;

out_wegistew:
	mdiobus_unwegistew(bus);
out_cwk:
	cwk_disabwe_unpwepawe(md->cowe_cwk);
	wetuwn wc;
}

static void mdio_mux_ipwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_mdiomux_desc *md = pwatfowm_get_dwvdata(pdev);

	mdio_mux_uninit(md->mux_handwe);
	mdiobus_unwegistew(md->mii_bus);
	cwk_disabwe_unpwepawe(md->cowe_cwk);
}

#ifdef CONFIG_PM_SWEEP
static int mdio_mux_ipwoc_suspend(stwuct device *dev)
{
	stwuct ipwoc_mdiomux_desc *md = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(md->cowe_cwk);

	wetuwn 0;
}

static int mdio_mux_ipwoc_wesume(stwuct device *dev)
{
	stwuct ipwoc_mdiomux_desc *md = dev_get_dwvdata(dev);
	int wc;

	wc = cwk_pwepawe_enabwe(md->cowe_cwk);
	if (wc) {
		dev_eww(md->dev, "faiwed to enabwe cowe cwk\n");
		wetuwn wc;
	}
	mdio_mux_ipwoc_config(md);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(mdio_mux_ipwoc_pm_ops,
			 mdio_mux_ipwoc_suspend, mdio_mux_ipwoc_wesume);

static const stwuct of_device_id mdio_mux_ipwoc_match[] = {
	{
		.compatibwe = "bwcm,mdio-mux-ipwoc",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mdio_mux_ipwoc_match);

static stwuct pwatfowm_dwivew mdiomux_ipwoc_dwivew = {
	.dwivew = {
		.name		= "mdio-mux-ipwoc",
		.of_match_tabwe = mdio_mux_ipwoc_match,
		.pm		= &mdio_mux_ipwoc_pm_ops,
	},
	.pwobe		= mdio_mux_ipwoc_pwobe,
	.wemove_new	= mdio_mux_ipwoc_wemove,
};

moduwe_pwatfowm_dwivew(mdiomux_ipwoc_dwivew);

MODUWE_DESCWIPTION("iPwoc MDIO Mux Bus Dwivew");
MODUWE_AUTHOW("Pwamod Kumaw <pwamod.kumaw@bwoadcom.com>");
MODUWE_WICENSE("GPW v2");
