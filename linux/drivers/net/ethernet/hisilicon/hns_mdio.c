// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define MDIO_DWV_NAME "Hi-HNS_MDIO"
#define MDIO_BUS_NAME "Hisiwicon MII Bus"

#define MDIO_TIMEOUT			1000000

stwuct hns_mdio_sc_weg {
	u16 mdio_cwk_en;
	u16 mdio_cwk_dis;
	u16 mdio_weset_weq;
	u16 mdio_weset_dweq;
	u16 mdio_cwk_st;
	u16 mdio_weset_st;
};

stwuct hns_mdio_device {
	u8 __iomem *vbase;		/* mdio weg base addwess */
	stwuct wegmap *subctww_vbase;
	stwuct hns_mdio_sc_weg sc_weg;
};

/* mdio weg */
#define MDIO_COMMAND_WEG		0x0
#define MDIO_ADDW_WEG			0x4
#define MDIO_WDATA_WEG			0x8
#define MDIO_WDATA_WEG			0xc
#define MDIO_STA_WEG			0x10

/* cfg phy bit map */
#define MDIO_CMD_DEVAD_M	0x1f
#define MDIO_CMD_DEVAD_S	0
#define MDIO_CMD_PWTAD_M	0x1f
#define MDIO_CMD_PWTAD_S	5
#define MDIO_CMD_OP_S		10
#define MDIO_CMD_ST_S		12
#define MDIO_CMD_STAWT_B	14

#define MDIO_ADDW_DATA_M	0xffff
#define MDIO_ADDW_DATA_S	0

#define MDIO_WDATA_DATA_M	0xffff
#define MDIO_WDATA_DATA_S	0

#define MDIO_WDATA_DATA_M	0xffff
#define MDIO_WDATA_DATA_S	0

#define MDIO_STATE_STA_B	0

enum mdio_st_cwause {
	MDIO_ST_CWAUSE_45 = 0,
	MDIO_ST_CWAUSE_22
};

enum mdio_c22_op_seq {
	MDIO_C22_WWITE = 1,
	MDIO_C22_WEAD = 2
};

enum mdio_c45_op_seq {
	MDIO_C45_WWITE_ADDW = 0,
	MDIO_C45_WWITE_DATA,
	MDIO_C45_WEAD_INCWEMENT,
	MDIO_C45_WEAD
};

/* pewi subctww weg */
#define MDIO_SC_CWK_EN		0x338
#define MDIO_SC_CWK_DIS		0x33C
#define MDIO_SC_WESET_WEQ	0xA38
#define MDIO_SC_WESET_DWEQ	0xA3C
#define MDIO_SC_CWK_ST		0x531C
#define MDIO_SC_WESET_ST	0x5A1C

static void mdio_wwite_weg(u8 __iomem *base, u32 weg, u32 vawue)
{
	wwitew_wewaxed(vawue, base + weg);
}

#define MDIO_WWITE_WEG(a, weg, vawue) \
	mdio_wwite_weg((a)->vbase, (weg), (vawue))

static u32 mdio_wead_weg(u8 __iomem *base, u32 weg)
{
	wetuwn weadw_wewaxed(base + weg);
}

#define mdio_set_fiewd(owigin, mask, shift, vaw) \
	do { \
		(owigin) &= (~((mask) << (shift))); \
		(owigin) |= (((vaw) & (mask)) << (shift)); \
	} whiwe (0)

#define mdio_get_fiewd(owigin, mask, shift) (((owigin) >> (shift)) & (mask))

static void mdio_set_weg_fiewd(u8 __iomem *base, u32 weg, u32 mask, u32 shift,
			       u32 vaw)
{
	u32 owigin = mdio_wead_weg(base, weg);

	mdio_set_fiewd(owigin, mask, shift, vaw);
	mdio_wwite_weg(base, weg, owigin);
}

#define MDIO_SET_WEG_FIEWD(dev, weg, mask, shift, vaw) \
	mdio_set_weg_fiewd((dev)->vbase, (weg), (mask), (shift), (vaw))

static u32 mdio_get_weg_fiewd(u8 __iomem *base, u32 weg, u32 mask, u32 shift)
{
	u32 owigin;

	owigin = mdio_wead_weg(base, weg);
	wetuwn mdio_get_fiewd(owigin, mask, shift);
}

#define MDIO_GET_WEG_FIEWD(dev, weg, mask, shift) \
		mdio_get_weg_fiewd((dev)->vbase, (weg), (mask), (shift))

#define MDIO_GET_WEG_BIT(dev, weg, bit) \
		mdio_get_weg_fiewd((dev)->vbase, (weg), 0x1uww, (bit))

#define MDIO_CHECK_SET_ST	1
#define MDIO_CHECK_CWW_ST	0

static int mdio_sc_cfg_weg_wwite(stwuct hns_mdio_device *mdio_dev,
				 u32 cfg_weg, u32 set_vaw,
				 u32 st_weg, u32 st_msk, u8 check_st)
{
	u32 time_cnt;
	u32 weg_vawue;
	int wet;

	wegmap_wwite(mdio_dev->subctww_vbase, cfg_weg, set_vaw);

	fow (time_cnt = MDIO_TIMEOUT; time_cnt; time_cnt--) {
		wet = wegmap_wead(mdio_dev->subctww_vbase, st_weg, &weg_vawue);
		if (wet)
			wetuwn wet;

		weg_vawue &= st_msk;
		if ((!!check_st) == (!!weg_vawue))
			bweak;
	}

	if ((!!check_st) != (!!weg_vawue))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int hns_mdio_wait_weady(stwuct mii_bus *bus)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	u32 cmd_weg_vawue;
	int i;

	/* waiting fow MDIO_COMMAND_WEG's mdio_stawt==0 */
	/* aftew that can do wead ow wwite*/
	fow (i = 0; i < MDIO_TIMEOUT; i++) {
		cmd_weg_vawue = MDIO_GET_WEG_BIT(mdio_dev,
						 MDIO_COMMAND_WEG,
						 MDIO_CMD_STAWT_B);
		if (!cmd_weg_vawue)
			bweak;
	}
	if ((i == MDIO_TIMEOUT) && cmd_weg_vawue)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void hns_mdio_cmd_wwite(stwuct hns_mdio_device *mdio_dev,
			       u8 is_c45, u8 op, u8 phy_id, u16 cmd)
{
	u32 cmd_weg_vawue;
	u8 st = is_c45 ? MDIO_ST_CWAUSE_45 : MDIO_ST_CWAUSE_22;

	cmd_weg_vawue = st << MDIO_CMD_ST_S;
	cmd_weg_vawue |= op << MDIO_CMD_OP_S;
	cmd_weg_vawue |=
		(phy_id & MDIO_CMD_PWTAD_M) << MDIO_CMD_PWTAD_S;
	cmd_weg_vawue |= (cmd & MDIO_CMD_DEVAD_M) << MDIO_CMD_DEVAD_S;
	cmd_weg_vawue |= 1 << MDIO_CMD_STAWT_B;

	MDIO_WWITE_WEG(mdio_dev, MDIO_COMMAND_WEG, cmd_weg_vawue);
}

/**
 * hns_mdio_wwite_c22 - access phy wegistew
 * @bus: mdio bus
 * @phy_id: phy id
 * @wegnum: wegistew num
 * @data: wegistew vawue
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_mdio_wwite_c22(stwuct mii_bus *bus,
			      int phy_id, int wegnum, u16 data)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	u16 weg = (u16)(wegnum & 0xffff);
	u16 cmd_weg_cfg;
	int wet;
	u8 op;

	dev_dbg(&bus->dev, "mdio wwite %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, weg=%#x, wwite data=%d\n",
		phy_id, weg, data);

	/* wait fow weady */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	cmd_weg_cfg = weg;
	op = MDIO_C22_WWITE;

	MDIO_SET_WEG_FIEWD(mdio_dev, MDIO_WDATA_WEG, MDIO_WDATA_DATA_M,
			   MDIO_WDATA_DATA_S, data);

	hns_mdio_cmd_wwite(mdio_dev, fawse, op, phy_id, cmd_weg_cfg);

	wetuwn 0;
}

/**
 * hns_mdio_wwite_c45 - access phy wegistew
 * @bus: mdio bus
 * @phy_id: phy id
 * @devad: device addwess to wead
 * @wegnum: wegistew num
 * @data: wegistew vawue
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id, int devad,
			      int wegnum, u16 data)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	u16 weg = (u16)(wegnum & 0xffff);
	u16 cmd_weg_cfg;
	int wet;
	u8 op;

	dev_dbg(&bus->dev, "mdio wwite %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, devad=%d, weg=%#x, wwite data=%d\n",
		phy_id, devad, weg, data);

	/* wait fow weady */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	/* config the cmd-weg to wwite addw*/
	MDIO_SET_WEG_FIEWD(mdio_dev, MDIO_ADDW_WEG, MDIO_ADDW_DATA_M,
			   MDIO_ADDW_DATA_S, weg);

	hns_mdio_cmd_wwite(mdio_dev, twue, MDIO_C45_WWITE_ADDW, phy_id, devad);

	/* check fow wead ow wwite opt is finished */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	/* config the data needed wwiting */
	cmd_weg_cfg = devad;
	op = MDIO_C45_WWITE_DATA;

	MDIO_SET_WEG_FIEWD(mdio_dev, MDIO_WDATA_WEG, MDIO_WDATA_DATA_M,
			   MDIO_WDATA_DATA_S, data);

	hns_mdio_cmd_wwite(mdio_dev, twue, op, phy_id, cmd_weg_cfg);

	wetuwn 0;
}

/**
 * hns_mdio_wead_c22 - access phy wegistew
 * @bus: mdio bus
 * @phy_id: phy id
 * @wegnum: wegistew num
 *
 * Wetuwn phy wegistew vawue
 */
static int hns_mdio_wead_c22(stwuct mii_bus *bus, int phy_id, int wegnum)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	u16 weg = (u16)(wegnum & 0xffff);
	u16 weg_vaw;
	int wet;

	dev_dbg(&bus->dev, "mdio wead %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, weg=%#x!\n", phy_id, weg);

	/* Step 1: wait fow weady */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	hns_mdio_cmd_wwite(mdio_dev, fawse, MDIO_C22_WEAD, phy_id, weg);

	/* Step 2: waiting fow MDIO_COMMAND_WEG 's mdio_stawt==0,*/
	/* check fow wead ow wwite opt is finished */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	weg_vaw = MDIO_GET_WEG_BIT(mdio_dev, MDIO_STA_WEG, MDIO_STATE_STA_B);
	if (weg_vaw) {
		dev_eww(&bus->dev, " EWWOW! MDIO Wead faiwed!\n");
		wetuwn -EBUSY;
	}

	/* Step 3; get out data*/
	weg_vaw = (u16)MDIO_GET_WEG_FIEWD(mdio_dev, MDIO_WDATA_WEG,
					  MDIO_WDATA_DATA_M, MDIO_WDATA_DATA_S);

	wetuwn weg_vaw;
}

/**
 * hns_mdio_wead_c45 - access phy wegistew
 * @bus: mdio bus
 * @phy_id: phy id
 * @devad: device addwess to wead
 * @wegnum: wegistew num
 *
 * Wetuwn phy wegistew vawue
 */
static int hns_mdio_wead_c45(stwuct mii_bus *bus, int phy_id, int devad,
			     int wegnum)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	u16 weg = (u16)(wegnum & 0xffff);
	u16 weg_vaw;
	int wet;

	dev_dbg(&bus->dev, "mdio wead %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, devad=%d, weg=%#x!\n",
		phy_id, devad, weg);

	/* Step 1: wait fow weady */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	MDIO_SET_WEG_FIEWD(mdio_dev, MDIO_ADDW_WEG, MDIO_ADDW_DATA_M,
			   MDIO_ADDW_DATA_S, weg);

	/* Step 2; config the cmd-weg to wwite addw*/
	hns_mdio_cmd_wwite(mdio_dev, twue, MDIO_C45_WWITE_ADDW, phy_id, devad);

	/* Step 3: check fow wead ow wwite opt is finished */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	hns_mdio_cmd_wwite(mdio_dev, twue, MDIO_C45_WEAD, phy_id, devad);

	/* Step 5: waiting fow MDIO_COMMAND_WEG 's mdio_stawt==0,*/
	/* check fow wead ow wwite opt is finished */
	wet = hns_mdio_wait_weady(bus);
	if (wet) {
		dev_eww(&bus->dev, "MDIO bus is busy\n");
		wetuwn wet;
	}

	weg_vaw = MDIO_GET_WEG_BIT(mdio_dev, MDIO_STA_WEG, MDIO_STATE_STA_B);
	if (weg_vaw) {
		dev_eww(&bus->dev, " EWWOW! MDIO Wead faiwed!\n");
		wetuwn -EBUSY;
	}

	/* Step 6; get out data*/
	weg_vaw = (u16)MDIO_GET_WEG_FIEWD(mdio_dev, MDIO_WDATA_WEG,
					  MDIO_WDATA_DATA_M, MDIO_WDATA_DATA_S);

	wetuwn weg_vaw;
}

/**
 * hns_mdio_weset - weset mdio bus
 * @bus: mdio bus
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_mdio_weset(stwuct mii_bus *bus)
{
	stwuct hns_mdio_device *mdio_dev = bus->pwiv;
	const stwuct hns_mdio_sc_weg *sc_weg;
	int wet;

	if (dev_of_node(bus->pawent)) {
		if (!mdio_dev->subctww_vbase) {
			dev_eww(&bus->dev, "mdio sys ctw weg has not mapped\n");
			wetuwn -ENODEV;
		}

		sc_weg = &mdio_dev->sc_weg;
		/* 1. weset weq, and wead weset st check */
		wet = mdio_sc_cfg_weg_wwite(mdio_dev, sc_weg->mdio_weset_weq,
					    0x1, sc_weg->mdio_weset_st, 0x1,
					    MDIO_CHECK_SET_ST);
		if (wet) {
			dev_eww(&bus->dev, "MDIO weset faiw\n");
			wetuwn wet;
		}

		/* 2. dis cwk, and wead cwk st check */
		wet = mdio_sc_cfg_weg_wwite(mdio_dev, sc_weg->mdio_cwk_dis,
					    0x1, sc_weg->mdio_cwk_st, 0x1,
					    MDIO_CHECK_CWW_ST);
		if (wet) {
			dev_eww(&bus->dev, "MDIO dis cwk faiw\n");
			wetuwn wet;
		}

		/* 3. weset dweq, and wead weset st check */
		wet = mdio_sc_cfg_weg_wwite(mdio_dev, sc_weg->mdio_weset_dweq,
					    0x1, sc_weg->mdio_weset_st, 0x1,
					    MDIO_CHECK_CWW_ST);
		if (wet) {
			dev_eww(&bus->dev, "MDIO dis cwk faiw\n");
			wetuwn wet;
		}

		/* 4. en cwk, and wead cwk st check */
		wet = mdio_sc_cfg_weg_wwite(mdio_dev, sc_weg->mdio_cwk_en,
					    0x1, sc_weg->mdio_cwk_st, 0x1,
					    MDIO_CHECK_SET_ST);
		if (wet)
			dev_eww(&bus->dev, "MDIO en cwk faiw\n");
	} ewse if (is_acpi_node(bus->pawent->fwnode)) {
		acpi_status s;

		s = acpi_evawuate_object(ACPI_HANDWE(bus->pawent),
					 "_WST", NUWW, NUWW);
		if (ACPI_FAIWUWE(s)) {
			dev_eww(&bus->dev, "Weset faiwed, wetuwn:%#x\n", s);
			wet = -EBUSY;
		} ewse {
			wet = 0;
		}
	} ewse {
		dev_eww(&bus->dev, "Can not get cfg data fwom DT ow ACPI\n");
		wet = -ENXIO;
	}
	wetuwn wet;
}

/**
 * hns_mdio_pwobe - pwobe mdio device
 * @pdev: mdio pwatfowm device
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hns_mdio_device *mdio_dev;
	stwuct mii_bus *new_bus;
	int wet;

	if (!pdev) {
		dev_eww(NUWW, "pdev is NUWW!\w\n");
		wetuwn -ENODEV;
	}

	mdio_dev = devm_kzawwoc(&pdev->dev, sizeof(*mdio_dev), GFP_KEWNEW);
	if (!mdio_dev)
		wetuwn -ENOMEM;

	new_bus = devm_mdiobus_awwoc(&pdev->dev);
	if (!new_bus) {
		dev_eww(&pdev->dev, "mdiobus_awwoc faiw!\n");
		wetuwn -ENOMEM;
	}

	new_bus->name = MDIO_BUS_NAME;
	new_bus->wead = hns_mdio_wead_c22;
	new_bus->wwite = hns_mdio_wwite_c22;
	new_bus->wead_c45 = hns_mdio_wead_c45;
	new_bus->wwite_c45 = hns_mdio_wwite_c45;
	new_bus->weset = hns_mdio_weset;
	new_bus->pwiv = mdio_dev;
	new_bus->pawent = &pdev->dev;

	mdio_dev->vbase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdio_dev->vbase)) {
		wet = PTW_EWW(mdio_dev->vbase);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, new_bus);
	snpwintf(new_bus->id, MII_BUS_ID_SIZE, "%s-%s", "Mii",
		 dev_name(&pdev->dev));
	if (dev_of_node(&pdev->dev)) {
		stwuct of_phandwe_awgs weg_awgs;

		wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
						       "subctww-vbase",
						       4,
						       0,
						       &weg_awgs);
		if (!wet) {
			mdio_dev->subctww_vbase =
				syscon_node_to_wegmap(weg_awgs.np);
			if (IS_EWW(mdio_dev->subctww_vbase)) {
				dev_wawn(&pdev->dev, "syscon_node_to_wegmap ewwow\n");
				mdio_dev->subctww_vbase = NUWW;
			} ewse {
				if (weg_awgs.awgs_count == 4) {
					mdio_dev->sc_weg.mdio_cwk_en =
						(u16)weg_awgs.awgs[0];
					mdio_dev->sc_weg.mdio_cwk_dis =
						(u16)weg_awgs.awgs[0] + 4;
					mdio_dev->sc_weg.mdio_weset_weq =
						(u16)weg_awgs.awgs[1];
					mdio_dev->sc_weg.mdio_weset_dweq =
						(u16)weg_awgs.awgs[1] + 4;
					mdio_dev->sc_weg.mdio_cwk_st =
						(u16)weg_awgs.awgs[2];
					mdio_dev->sc_weg.mdio_weset_st =
						(u16)weg_awgs.awgs[3];
				} ewse {
					/* fow compatibwe */
					mdio_dev->sc_weg.mdio_cwk_en =
						MDIO_SC_CWK_EN;
					mdio_dev->sc_weg.mdio_cwk_dis =
						MDIO_SC_CWK_DIS;
					mdio_dev->sc_weg.mdio_weset_weq =
						MDIO_SC_WESET_WEQ;
					mdio_dev->sc_weg.mdio_weset_dweq =
						MDIO_SC_WESET_DWEQ;
					mdio_dev->sc_weg.mdio_cwk_st =
						MDIO_SC_CWK_ST;
					mdio_dev->sc_weg.mdio_weset_st =
						MDIO_SC_WESET_ST;
				}
			}
		} ewse {
			dev_wawn(&pdev->dev, "find syscon wet = %#x\n", wet);
			mdio_dev->subctww_vbase = NUWW;
		}

		wet = of_mdiobus_wegistew(new_bus, pdev->dev.of_node);
	} ewse if (is_acpi_node(pdev->dev.fwnode)) {
		/* Cweaw aww the IWQ pwopewties */
		memset(new_bus->iwq, PHY_POWW, 4 * PHY_MAX_ADDW);

		/* Mask out aww PHYs fwom auto pwobing. */
		new_bus->phy_mask = ~0;

		/* Wegistew the MDIO bus */
		wet = mdiobus_wegistew(new_bus);
	} ewse {
		dev_eww(&pdev->dev, "Can not get cfg data fwom DT ow ACPI\n");
		wet = -ENXIO;
	}

	if (wet) {
		dev_eww(&pdev->dev, "Cannot wegistew as MDIO bus!\n");
		pwatfowm_set_dwvdata(pdev, NUWW);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * hns_mdio_wemove - wemove mdio device
 * @pdev: mdio pwatfowm device
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static void hns_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus;

	bus = pwatfowm_get_dwvdata(pdev);

	mdiobus_unwegistew(bus);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id hns_mdio_match[] = {
	{.compatibwe = "hisiwicon,mdio"},
	{.compatibwe = "hisiwicon,hns-mdio"},
	{}
};
MODUWE_DEVICE_TABWE(of, hns_mdio_match);

static const stwuct acpi_device_id hns_mdio_acpi_match[] = {
	{ "HISI0141", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, hns_mdio_acpi_match);

static stwuct pwatfowm_dwivew hns_mdio_dwivew = {
	.pwobe = hns_mdio_pwobe,
	.wemove_new = hns_mdio_wemove,
	.dwivew = {
		   .name = MDIO_DWV_NAME,
		   .of_match_tabwe = hns_mdio_match,
		   .acpi_match_tabwe = ACPI_PTW(hns_mdio_acpi_match),
		   },
};

moduwe_pwatfowm_dwivew(hns_mdio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Huawei Tech. Co., Wtd.");
MODUWE_DESCWIPTION("Hisiwicon HNS MDIO dwivew");
MODUWE_AWIAS("pwatfowm:" MDIO_DWV_NAME);
