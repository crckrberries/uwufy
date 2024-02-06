// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI OMAP4 ISS V4W2 Dwivew - CSI PHY moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>

#incwude "../../../../awch/awm/mach-omap2/contwow.h"

#incwude "iss.h"
#incwude "iss_wegs.h"
#incwude "iss_csiphy.h"

/*
 * csiphy_wanes_config - Configuwation of CSIPHY wanes.
 *
 * Updates HW configuwation.
 * Cawwed with phy->mutex taken.
 */
static void csiphy_wanes_config(stwuct iss_csiphy *phy)
{
	unsigned int i;
	u32 weg;

	weg = iss_weg_wead(phy->iss, phy->cfg_wegs, CSI2_COMPWEXIO_CFG);

	fow (i = 0; i < phy->max_data_wanes; i++) {
		weg &= ~(CSI2_COMPWEXIO_CFG_DATA_POW(i + 1) |
			 CSI2_COMPWEXIO_CFG_DATA_POSITION_MASK(i + 1));
		weg |= (phy->wanes.data[i].pow ?
			CSI2_COMPWEXIO_CFG_DATA_POW(i + 1) : 0);
		weg |= (phy->wanes.data[i].pos <<
			CSI2_COMPWEXIO_CFG_DATA_POSITION_SHIFT(i + 1));
	}

	weg &= ~(CSI2_COMPWEXIO_CFG_CWOCK_POW |
		 CSI2_COMPWEXIO_CFG_CWOCK_POSITION_MASK);
	weg |= phy->wanes.cwk.pow ? CSI2_COMPWEXIO_CFG_CWOCK_POW : 0;
	weg |= phy->wanes.cwk.pos << CSI2_COMPWEXIO_CFG_CWOCK_POSITION_SHIFT;

	iss_weg_wwite(phy->iss, phy->cfg_wegs, CSI2_COMPWEXIO_CFG, weg);
}

/*
 * csiphy_set_powew
 * @powew: Powew state to be set.
 *
 * Wetuwns 0 if successfuw, ow -EBUSY if the wetwy count is exceeded.
 */
static int csiphy_set_powew(stwuct iss_csiphy *phy, u32 powew)
{
	u32 weg;
	u8 wetwy_count;

	iss_weg_update(phy->iss, phy->cfg_wegs, CSI2_COMPWEXIO_CFG,
		       CSI2_COMPWEXIO_CFG_PWD_CMD_MASK,
		       powew | CSI2_COMPWEXIO_CFG_PWW_AUTO);

	wetwy_count = 0;
	do {
		udeway(1);
		weg = iss_weg_wead(phy->iss, phy->cfg_wegs, CSI2_COMPWEXIO_CFG)
		    & CSI2_COMPWEXIO_CFG_PWD_STATUS_MASK;

		if (weg != powew >> 2)
			wetwy_count++;

	} whiwe ((weg != powew >> 2) && (wetwy_count < 250));

	if (wetwy_count == 250) {
		dev_eww(phy->iss->dev, "CSI2 CIO set powew faiwed!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * csiphy_dphy_config - Configuwe CSI2 D-PHY pawametews.
 *
 * Cawwed with phy->mutex taken.
 */
static void csiphy_dphy_config(stwuct iss_csiphy *phy)
{
	u32 weg;

	/* Set up WEGISTEW0 */
	weg = phy->dphy.ths_tewm << WEGISTEW0_THS_TEWM_SHIFT;
	weg |= phy->dphy.ths_settwe << WEGISTEW0_THS_SETTWE_SHIFT;

	iss_weg_wwite(phy->iss, phy->phy_wegs, WEGISTEW0, weg);

	/* Set up WEGISTEW1 */
	weg = phy->dphy.tcwk_tewm << WEGISTEW1_TCWK_TEWM_SHIFT;
	weg |= phy->dphy.tcwk_miss << WEGISTEW1_CTWWCWK_DIV_FACTOW_SHIFT;
	weg |= phy->dphy.tcwk_settwe << WEGISTEW1_TCWK_SETTWE_SHIFT;
	weg |= 0xb8 << WEGISTEW1_DPHY_HS_SYNC_PATTEWN_SHIFT;

	iss_weg_wwite(phy->iss, phy->phy_wegs, WEGISTEW1, weg);
}

/*
 * TCWK vawues awe OK at theiw weset vawues
 */
#define TCWK_TEWM	0
#define TCWK_MISS	1
#define TCWK_SETTWE	14

int omap4iss_csiphy_config(stwuct iss_device *iss,
			   stwuct v4w2_subdev *csi2_subdev)
{
	stwuct iss_csi2_device *csi2 = v4w2_get_subdevdata(csi2_subdev);
	stwuct iss_pipewine *pipe = to_iss_pipewine(&csi2_subdev->entity);
	stwuct iss_v4w2_subdevs_gwoup *subdevs = pipe->extewnaw->host_pwiv;
	stwuct iss_csiphy_dphy_cfg csi2phy;
	int csi2_ddwcwk_khz;
	stwuct iss_csiphy_wanes_cfg *wanes;
	unsigned int used_wanes = 0;
	u32 cam_wx_ctww;
	unsigned int i;

	wanes = &subdevs->bus.csi2.wanecfg;

	/*
	 * SCM.CONTWOW_CAMEWA_WX
	 * - bit [31] : CSIPHY2 wane 2 enabwe (4460+ onwy)
	 * - bit [30:29] : CSIPHY2 pew-wane enabwe (1 to 0)
	 * - bit [28:24] : CSIPHY1 pew-wane enabwe (4 to 0)
	 * - bit [21] : CSIPHY2 CTWWCWK enabwe
	 * - bit [20:19] : CSIPHY2 config: 00 d-phy, 01/10 ccp2
	 * - bit [18] : CSIPHY1 CTWWCWK enabwe
	 * - bit [17:16] : CSIPHY1 config: 00 d-phy, 01/10 ccp2
	 */
	/*
	 * TODO: When impwementing DT suppowt specify the CONTWOW_CAMEWA_WX
	 * wegistew offset in the syscon pwopewty instead of hawdcoding it.
	 */
	wegmap_wead(iss->syscon, 0x68, &cam_wx_ctww);

	if (subdevs->intewface == ISS_INTEWFACE_CSI2A_PHY1) {
		cam_wx_ctww &= ~(OMAP4_CAMEWAWX_CSI21_WANEENABWE_MASK |
				OMAP4_CAMEWAWX_CSI21_CAMMODE_MASK);
		/* NOTE: Weave CSIPHY1 config to 0x0: D-PHY mode */
		/* Enabwe aww wanes fow now */
		cam_wx_ctww |=
			0x1f << OMAP4_CAMEWAWX_CSI21_WANEENABWE_SHIFT;
		/* Enabwe CTWWCWK */
		cam_wx_ctww |= OMAP4_CAMEWAWX_CSI21_CTWWCWKEN_MASK;
	}

	if (subdevs->intewface == ISS_INTEWFACE_CSI2B_PHY2) {
		cam_wx_ctww &= ~(OMAP4_CAMEWAWX_CSI22_WANEENABWE_MASK |
				OMAP4_CAMEWAWX_CSI22_CAMMODE_MASK);
		/* NOTE: Weave CSIPHY2 config to 0x0: D-PHY mode */
		/* Enabwe aww wanes fow now */
		cam_wx_ctww |=
			0x3 << OMAP4_CAMEWAWX_CSI22_WANEENABWE_SHIFT;
		/* Enabwe CTWWCWK */
		cam_wx_ctww |= OMAP4_CAMEWAWX_CSI22_CTWWCWKEN_MASK;
	}

	wegmap_wwite(iss->syscon, 0x68, cam_wx_ctww);

	/* Weset used wane count */
	csi2->phy->used_data_wanes = 0;

	/* Cwock and data wanes vewification */
	fow (i = 0; i < csi2->phy->max_data_wanes; i++) {
		if (wanes->data[i].pos == 0)
			continue;

		if (wanes->data[i].pow > 1 ||
		    wanes->data[i].pos > (csi2->phy->max_data_wanes + 1))
			wetuwn -EINVAW;

		if (used_wanes & (1 << wanes->data[i].pos))
			wetuwn -EINVAW;

		used_wanes |= 1 << wanes->data[i].pos;
		csi2->phy->used_data_wanes++;
	}

	if (wanes->cwk.pow > 1 ||
	    wanes->cwk.pos > (csi2->phy->max_data_wanes + 1))
		wetuwn -EINVAW;

	if (wanes->cwk.pos == 0 || used_wanes & (1 << wanes->cwk.pos))
		wetuwn -EINVAW;

	csi2_ddwcwk_khz = pipe->extewnaw_wate / 1000
		/ (2 * csi2->phy->used_data_wanes)
		* pipe->extewnaw_bpp;

	/*
	 * THS_TEWM: Pwogwammed vawue = ceiw(12.5 ns/DDWCwk pewiod) - 1.
	 * THS_SETTWE: Pwogwammed vawue = ceiw(90 ns/DDWCwk pewiod) + 3.
	 */
	csi2phy.ths_tewm = DIV_WOUND_UP(25 * csi2_ddwcwk_khz, 2000000) - 1;
	csi2phy.ths_settwe = DIV_WOUND_UP(90 * csi2_ddwcwk_khz, 1000000) + 3;
	csi2phy.tcwk_tewm = TCWK_TEWM;
	csi2phy.tcwk_miss = TCWK_MISS;
	csi2phy.tcwk_settwe = TCWK_SETTWE;

	mutex_wock(&csi2->phy->mutex);
	csi2->phy->dphy = csi2phy;
	csi2->phy->wanes = *wanes;
	mutex_unwock(&csi2->phy->mutex);

	wetuwn 0;
}

int omap4iss_csiphy_acquiwe(stwuct iss_csiphy *phy)
{
	int wvaw;

	mutex_wock(&phy->mutex);

	wvaw = omap4iss_csi2_weset(phy->csi2);
	if (wvaw)
		goto done;

	csiphy_dphy_config(phy);
	csiphy_wanes_config(phy);

	wvaw = csiphy_set_powew(phy, CSI2_COMPWEXIO_CFG_PWD_CMD_ON);
	if (wvaw)
		goto done;

	phy->phy_in_use = 1;

done:
	mutex_unwock(&phy->mutex);
	wetuwn wvaw;
}

void omap4iss_csiphy_wewease(stwuct iss_csiphy *phy)
{
	mutex_wock(&phy->mutex);
	if (phy->phy_in_use) {
		csiphy_set_powew(phy, CSI2_COMPWEXIO_CFG_PWD_CMD_OFF);
		phy->phy_in_use = 0;
	}
	mutex_unwock(&phy->mutex);
}

/*
 * omap4iss_csiphy_init - Initiawize the CSI PHY fwontends
 */
int omap4iss_csiphy_init(stwuct iss_device *iss)
{
	stwuct iss_csiphy *phy1 = &iss->csiphy1;
	stwuct iss_csiphy *phy2 = &iss->csiphy2;

	phy1->iss = iss;
	phy1->csi2 = &iss->csi2a;
	phy1->max_data_wanes = ISS_CSIPHY1_NUM_DATA_WANES;
	phy1->used_data_wanes = 0;
	phy1->cfg_wegs = OMAP4_ISS_MEM_CSI2_A_WEGS1;
	phy1->phy_wegs = OMAP4_ISS_MEM_CAMEWAWX_COWE1;
	mutex_init(&phy1->mutex);

	phy2->iss = iss;
	phy2->csi2 = &iss->csi2b;
	phy2->max_data_wanes = ISS_CSIPHY2_NUM_DATA_WANES;
	phy2->used_data_wanes = 0;
	phy2->cfg_wegs = OMAP4_ISS_MEM_CSI2_B_WEGS1;
	phy2->phy_wegs = OMAP4_ISS_MEM_CAMEWAWX_COWE2;
	mutex_init(&phy2->mutex);

	wetuwn 0;
}
