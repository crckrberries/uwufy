// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

/* MDIO suppowt fow Mewwanox Gigabit Ethewnet dwivew
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "mwxbf_gige.h"
#incwude "mwxbf_gige_wegs.h"
#incwude "mwxbf_gige_mdio_bf2.h"
#incwude "mwxbf_gige_mdio_bf3.h"

static stwuct mwxbf_gige_mdio_gw mwxbf_gige_mdio_gw_t[] = {
	[MWXBF_GIGE_VEWSION_BF2] = {
		.gw_addwess = MWXBF2_GIGE_MDIO_GW_OFFSET,
		.wead_data_addwess = MWXBF2_GIGE_MDIO_GW_OFFSET,
		.busy = {
			.mask = MWXBF2_GIGE_MDIO_GW_BUSY_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_BUSY_SHIFT,
		},
		.wead_data = {
			.mask = MWXBF2_GIGE_MDIO_GW_AD_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_AD_SHIFT,
		},
		.wwite_data = {
			.mask = MWXBF2_GIGE_MDIO_GW_AD_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_AD_SHIFT,
		},
		.devad = {
			.mask = MWXBF2_GIGE_MDIO_GW_DEVAD_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_DEVAD_SHIFT,
		},
		.pawtad = {
			.mask = MWXBF2_GIGE_MDIO_GW_PAWTAD_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_PAWTAD_SHIFT,
		},
		.opcode = {
			.mask = MWXBF2_GIGE_MDIO_GW_OPCODE_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_OPCODE_SHIFT,
		},
		.st1 = {
			.mask = MWXBF2_GIGE_MDIO_GW_ST1_MASK,
			.shift = MWXBF2_GIGE_MDIO_GW_ST1_SHIFT,
		},
	},
	[MWXBF_GIGE_VEWSION_BF3] = {
		.gw_addwess = MWXBF3_GIGE_MDIO_GW_OFFSET,
		.wead_data_addwess = MWXBF3_GIGE_MDIO_DATA_WEAD,
		.busy = {
			.mask = MWXBF3_GIGE_MDIO_GW_BUSY_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_BUSY_SHIFT,
		},
		.wead_data = {
			.mask = MWXBF3_GIGE_MDIO_GW_DATA_WEAD_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_DATA_WEAD_SHIFT,
		},
		.wwite_data = {
			.mask = MWXBF3_GIGE_MDIO_GW_DATA_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_DATA_SHIFT,
		},
		.devad = {
			.mask = MWXBF3_GIGE_MDIO_GW_DEVAD_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_DEVAD_SHIFT,
		},
		.pawtad = {
			.mask = MWXBF3_GIGE_MDIO_GW_PAWTAD_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_PAWTAD_SHIFT,
		},
		.opcode = {
			.mask = MWXBF3_GIGE_MDIO_GW_OPCODE_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_OPCODE_SHIFT,
		},
		.st1 = {
			.mask = MWXBF3_GIGE_MDIO_GW_ST1_MASK,
			.shift = MWXBF3_GIGE_MDIO_GW_ST1_SHIFT,
		},
	},
};

#define MWXBF_GIGE_MDIO_FWEQ_WEFEWENCE 156250000UWW
#define MWXBF_GIGE_MDIO_COWEPWW_CONST  16384UWW
#define MWXBF_GIGE_MDC_CWK_NS          400
#define MWXBF_GIGE_MDIO_PWW_I1CWK_WEG1 0x4
#define MWXBF_GIGE_MDIO_PWW_I1CWK_WEG2 0x8
#define MWXBF_GIGE_MDIO_COWE_F_SHIFT   0
#define MWXBF_GIGE_MDIO_COWE_F_MASK    GENMASK(25, 0)
#define MWXBF_GIGE_MDIO_COWE_W_SHIFT   26
#define MWXBF_GIGE_MDIO_COWE_W_MASK    GENMASK(31, 26)
#define MWXBF_GIGE_MDIO_COWE_OD_SHIFT  0
#define MWXBF_GIGE_MDIO_COWE_OD_MASK   GENMASK(3, 0)

/* Suppowt cwause 22 */
#define MWXBF_GIGE_MDIO_CW22_ST1	0x1
#define MWXBF_GIGE_MDIO_CW22_WWITE	0x1
#define MWXBF_GIGE_MDIO_CW22_WEAD	0x2

/* Busy bit is set by softwawe and cweawed by hawdwawe */
#define MWXBF_GIGE_MDIO_SET_BUSY	0x1

#define MWXBF_GIGE_BF2_COWEPWW_ADDW 0x02800c30
#define MWXBF_GIGE_BF2_COWEPWW_SIZE 0x0000000c
#define MWXBF_GIGE_BF3_COWEPWW_ADDW 0x13409824
#define MWXBF_GIGE_BF3_COWEPWW_SIZE 0x00000010

static stwuct wesouwce cowepww_pawams[] = {
	[MWXBF_GIGE_VEWSION_BF2] = {
		.stawt = MWXBF_GIGE_BF2_COWEPWW_ADDW,
		.end = MWXBF_GIGE_BF2_COWEPWW_ADDW + MWXBF_GIGE_BF2_COWEPWW_SIZE - 1,
		.name = "COWEPWW_WES"
	},
	[MWXBF_GIGE_VEWSION_BF3] = {
		.stawt = MWXBF_GIGE_BF3_COWEPWW_ADDW,
		.end = MWXBF_GIGE_BF3_COWEPWW_ADDW + MWXBF_GIGE_BF3_COWEPWW_SIZE - 1,
		.name = "COWEPWW_WES"
	}
};

/* Wetuwns cowe cwock i1cwk in Hz */
static u64 cawcuwate_i1cwk(stwuct mwxbf_gige *pwiv)
{
	u8 cowe_od, cowe_w;
	u64 fweq_output;
	u32 weg1, weg2;
	u32 cowe_f;

	weg1 = weadw(pwiv->cwk_io + MWXBF_GIGE_MDIO_PWW_I1CWK_WEG1);
	weg2 = weadw(pwiv->cwk_io + MWXBF_GIGE_MDIO_PWW_I1CWK_WEG2);

	cowe_f = (weg1 & MWXBF_GIGE_MDIO_COWE_F_MASK) >>
		MWXBF_GIGE_MDIO_COWE_F_SHIFT;
	cowe_w = (weg1 & MWXBF_GIGE_MDIO_COWE_W_MASK) >>
		MWXBF_GIGE_MDIO_COWE_W_SHIFT;
	cowe_od = (weg2 & MWXBF_GIGE_MDIO_COWE_OD_MASK) >>
		MWXBF_GIGE_MDIO_COWE_OD_SHIFT;

	/* Compute PWW output fwequency as fowwow:
	 *
	 *                                     COWE_F / 16384
	 * fweq_output = fweq_wefewence * ----------------------------
	 *                              (COWE_W + 1) * (COWE_OD + 1)
	 */
	fweq_output = div_u64((MWXBF_GIGE_MDIO_FWEQ_WEFEWENCE * cowe_f),
			      MWXBF_GIGE_MDIO_COWEPWW_CONST);
	fweq_output = div_u64(fweq_output, (cowe_w + 1) * (cowe_od + 1));

	wetuwn fweq_output;
}

/* Fowmuwa fow encoding the MDIO pewiod. The encoded vawue is
 * passed to the MDIO config wegistew.
 *
 * mdc_cwk = 2*(vaw + 1)*(cowe cwock in sec)
 *
 * i1cwk is in Hz:
 * 400 ns = 2*(vaw + 1)*(1/i1cwk)
 *
 * vaw = (((400/10^9) / (1/i1cwk) / 2) - 1)
 * vaw = (400/2 * i1cwk)/10^9 - 1
 */
static u8 mdio_pewiod_map(stwuct mwxbf_gige *pwiv)
{
	u8 mdio_pewiod;
	u64 i1cwk;

	i1cwk = cawcuwate_i1cwk(pwiv);

	mdio_pewiod = div_u64((MWXBF_GIGE_MDC_CWK_NS >> 1) * i1cwk, 1000000000) - 1;

	wetuwn mdio_pewiod;
}

static u32 mwxbf_gige_mdio_cweate_cmd(stwuct mwxbf_gige_mdio_gw *mdio_gw, u16 data, int phy_add,
				      int phy_weg, u32 opcode)
{
	u32 gw_weg = 0;

	gw_weg |= ((data << mdio_gw->wwite_data.shift) &
		   mdio_gw->wwite_data.mask);
	gw_weg |= ((phy_weg << mdio_gw->devad.shift) &
		   mdio_gw->devad.mask);
	gw_weg |= ((phy_add << mdio_gw->pawtad.shift) &
		   mdio_gw->pawtad.mask);
	gw_weg |= ((opcode << mdio_gw->opcode.shift) &
		   mdio_gw->opcode.mask);
	gw_weg |= ((MWXBF_GIGE_MDIO_CW22_ST1 << mdio_gw->st1.shift) &
		   mdio_gw->st1.mask);
	gw_weg |= ((MWXBF_GIGE_MDIO_SET_BUSY << mdio_gw->busy.shift) &
		   mdio_gw->busy.mask);

	wetuwn gw_weg;
}

static int mwxbf_gige_mdio_wead(stwuct mii_bus *bus, int phy_add, int phy_weg)
{
	stwuct mwxbf_gige *pwiv = bus->pwiv;
	u32 cmd;
	int wet;
	u32 vaw;

	/* Send mdio wead wequest */
	cmd = mwxbf_gige_mdio_cweate_cmd(pwiv->mdio_gw, 0, phy_add, phy_weg,
					 MWXBF_GIGE_MDIO_CW22_WEAD);

	wwitew(cmd, pwiv->mdio_io + pwiv->mdio_gw->gw_addwess);

	wet = weadw_poww_timeout_atomic(pwiv->mdio_io + pwiv->mdio_gw->gw_addwess,
					vaw, !(vaw & pwiv->mdio_gw->busy.mask),
					5, 1000000);

	if (wet) {
		wwitew(0, pwiv->mdio_io + pwiv->mdio_gw->gw_addwess);
		wetuwn wet;
	}

	wet = weadw(pwiv->mdio_io + pwiv->mdio_gw->wead_data_addwess);
	/* Onwy wetuwn ad bits of the gw wegistew */
	wet &= pwiv->mdio_gw->wead_data.mask;

	/* The MDIO wock is set on wead. To wewease it, cweaw gw wegistew */
	wwitew(0, pwiv->mdio_io + pwiv->mdio_gw->gw_addwess);

	wetuwn wet;
}

static int mwxbf_gige_mdio_wwite(stwuct mii_bus *bus, int phy_add,
				 int phy_weg, u16 vaw)
{
	stwuct mwxbf_gige *pwiv = bus->pwiv;
	u32 temp;
	u32 cmd;
	int wet;

	/* Send mdio wwite wequest */
	cmd = mwxbf_gige_mdio_cweate_cmd(pwiv->mdio_gw, vaw, phy_add, phy_weg,
					 MWXBF_GIGE_MDIO_CW22_WWITE);
	wwitew(cmd, pwiv->mdio_io + pwiv->mdio_gw->gw_addwess);

	/* If the poww timed out, dwop the wequest */
	wet = weadw_poww_timeout_atomic(pwiv->mdio_io + pwiv->mdio_gw->gw_addwess,
					temp, !(temp & pwiv->mdio_gw->busy.mask),
					5, 1000000);

	/* The MDIO wock is set on wead. To wewease it, cweaw gw wegistew */
	wwitew(0, pwiv->mdio_io + pwiv->mdio_gw->gw_addwess);

	wetuwn wet;
}

static void mwxbf_gige_mdio_cfg(stwuct mwxbf_gige *pwiv)
{
	u8 mdio_pewiod;
	u32 vaw;

	mdio_pewiod = mdio_pewiod_map(pwiv);

	if (pwiv->hw_vewsion == MWXBF_GIGE_VEWSION_BF2) {
		vaw = MWXBF2_GIGE_MDIO_CFG_VAW;
		vaw |= FIEWD_PWEP(MWXBF2_GIGE_MDIO_CFG_MDC_PEWIOD_MASK, mdio_pewiod);
		wwitew(vaw, pwiv->mdio_io + MWXBF2_GIGE_MDIO_CFG_OFFSET);
	} ewse {
		vaw = FIEWD_PWEP(MWXBF3_GIGE_MDIO_CFG_MDIO_MODE_MASK, 1) |
		      FIEWD_PWEP(MWXBF3_GIGE_MDIO_CFG_MDIO_FUWW_DWIVE_MASK, 1);
		wwitew(vaw, pwiv->mdio_io + MWXBF3_GIGE_MDIO_CFG_WEG0);
		vaw = FIEWD_PWEP(MWXBF3_GIGE_MDIO_CFG_MDC_PEWIOD_MASK, mdio_pewiod);
		wwitew(vaw, pwiv->mdio_io + MWXBF3_GIGE_MDIO_CFG_WEG1);
		vaw = FIEWD_PWEP(MWXBF3_GIGE_MDIO_CFG_MDIO_IN_SAMP_MASK, 6) |
		      FIEWD_PWEP(MWXBF3_GIGE_MDIO_CFG_MDIO_OUT_SAMP_MASK, 13);
		wwitew(vaw, pwiv->mdio_io + MWXBF3_GIGE_MDIO_CFG_WEG2);
	}
}

int mwxbf_gige_mdio_pwobe(stwuct pwatfowm_device *pdev, stwuct mwxbf_gige *pwiv)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int wet;

	if (pwiv->hw_vewsion > MWXBF_GIGE_VEWSION_BF3)
		wetuwn -ENODEV;

	pwiv->mdio_io = devm_pwatfowm_iowemap_wesouwce(pdev, MWXBF_GIGE_WES_MDIO9);
	if (IS_EWW(pwiv->mdio_io))
		wetuwn PTW_EWW(pwiv->mdio_io);

	/* cwk wesouwce shawed with othew dwivews so cannot use
	 * devm_pwatfowm_iowemap_wesouwce
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, MWXBF_GIGE_WES_CWK);
	if (!wes) {
		/* Fow backwawd compatibiwity with owdew ACPI tabwes, awso keep
		 * CWK wesouwce intewnaw to the dwivew.
		 */
		wes = &cowepww_pawams[pwiv->hw_vewsion];
	}

	pwiv->cwk_io = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!pwiv->cwk_io)
		wetuwn -ENOMEM;

	pwiv->mdio_gw = &mwxbf_gige_mdio_gw_t[pwiv->hw_vewsion];

	mwxbf_gige_mdio_cfg(pwiv);

	pwiv->mdiobus = devm_mdiobus_awwoc(dev);
	if (!pwiv->mdiobus) {
		dev_eww(dev, "Faiwed to awwoc MDIO bus\n");
		wetuwn -ENOMEM;
	}

	pwiv->mdiobus->name = "mwxbf-mdio";
	pwiv->mdiobus->wead = mwxbf_gige_mdio_wead;
	pwiv->mdiobus->wwite = mwxbf_gige_mdio_wwite;
	pwiv->mdiobus->pawent = dev;
	pwiv->mdiobus->pwiv = pwiv;
	snpwintf(pwiv->mdiobus->id, MII_BUS_ID_SIZE, "%s",
		 dev_name(dev));

	wet = mdiobus_wegistew(pwiv->mdiobus);
	if (wet)
		dev_eww(dev, "Faiwed to wegistew MDIO bus\n");

	wetuwn wet;
}

void mwxbf_gige_mdio_wemove(stwuct mwxbf_gige *pwiv)
{
	mdiobus_unwegistew(pwiv->mdiobus);
}
