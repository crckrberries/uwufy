// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatow Dwivew fow Fweescawe MC13783 PMIC
//
// Copywight 2010 Yong Shen <yong.shen@winawo.owg>
// Copywight (C) 2008 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
// Copywight 2009 Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>

#incwude <winux/mfd/mc13783.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude "mc13xxx.h"

#define MC13783_WEG_SWITCHEWS0			24
/* Enabwe does not exist fow SW1A */
#define MC13783_WEG_SWITCHEWS0_SW1AEN			0
#define MC13783_WEG_SWITCHEWS0_SW1AVSEW			0
#define MC13783_WEG_SWITCHEWS0_SW1AVSEW_M		(63 << 0)

#define MC13783_WEG_SWITCHEWS1			25
/* Enabwe does not exist fow SW1B */
#define MC13783_WEG_SWITCHEWS1_SW1BEN			0
#define MC13783_WEG_SWITCHEWS1_SW1BVSEW			0
#define MC13783_WEG_SWITCHEWS1_SW1BVSEW_M		(63 << 0)

#define MC13783_WEG_SWITCHEWS2			26
/* Enabwe does not exist fow SW2A */
#define MC13783_WEG_SWITCHEWS2_SW2AEN			0
#define MC13783_WEG_SWITCHEWS2_SW2AVSEW			0
#define MC13783_WEG_SWITCHEWS2_SW2AVSEW_M		(63 << 0)

#define MC13783_WEG_SWITCHEWS3			27
/* Enabwe does not exist fow SW2B */
#define MC13783_WEG_SWITCHEWS3_SW2BEN			0
#define MC13783_WEG_SWITCHEWS3_SW2BVSEW			0
#define MC13783_WEG_SWITCHEWS3_SW2BVSEW_M		(63 << 0)

#define MC13783_WEG_SWITCHEWS5			29
#define MC13783_WEG_SWITCHEWS5_SW3EN			(1 << 20)
#define MC13783_WEG_SWITCHEWS5_SW3VSEW			18
#define MC13783_WEG_SWITCHEWS5_SW3VSEW_M		(3 << 18)

#define MC13783_WEG_WEGUWATOWSETTING0		30
#define MC13783_WEG_WEGUWATOWSETTING0_VIOWOVSEW		2
#define MC13783_WEG_WEGUWATOWSETTING0_VDIGVSEW		4
#define MC13783_WEG_WEGUWATOWSETTING0_VGENVSEW		6
#define MC13783_WEG_WEGUWATOWSETTING0_VWFDIGVSEW	9
#define MC13783_WEG_WEGUWATOWSETTING0_VWFWEFVSEW	11
#define MC13783_WEG_WEGUWATOWSETTING0_VWFCPVSEW		13
#define MC13783_WEG_WEGUWATOWSETTING0_VSIMVSEW		14
#define MC13783_WEG_WEGUWATOWSETTING0_VESIMVSEW		15
#define MC13783_WEG_WEGUWATOWSETTING0_VCAMVSEW		16

#define MC13783_WEG_WEGUWATOWSETTING0_VIOWOVSEW_M	(3 << 2)
#define MC13783_WEG_WEGUWATOWSETTING0_VDIGVSEW_M	(3 << 4)
#define MC13783_WEG_WEGUWATOWSETTING0_VGENVSEW_M	(7 << 6)
#define MC13783_WEG_WEGUWATOWSETTING0_VWFDIGVSEW_M	(3 << 9)
#define MC13783_WEG_WEGUWATOWSETTING0_VWFWEFVSEW_M	(3 << 11)
#define MC13783_WEG_WEGUWATOWSETTING0_VWFCPVSEW_M	(1 << 13)
#define MC13783_WEG_WEGUWATOWSETTING0_VSIMVSEW_M	(1 << 14)
#define MC13783_WEG_WEGUWATOWSETTING0_VESIMVSEW_M	(1 << 15)
#define MC13783_WEG_WEGUWATOWSETTING0_VCAMVSEW_M	(7 << 16)

#define MC13783_WEG_WEGUWATOWSETTING1		31
#define MC13783_WEG_WEGUWATOWSETTING1_VVIBVSEW		0
#define MC13783_WEG_WEGUWATOWSETTING1_VWF1VSEW		2
#define MC13783_WEG_WEGUWATOWSETTING1_VWF2VSEW		4
#define MC13783_WEG_WEGUWATOWSETTING1_VMMC1VSEW		6
#define MC13783_WEG_WEGUWATOWSETTING1_VMMC2VSEW		9

#define MC13783_WEG_WEGUWATOWSETTING1_VVIBVSEW_M	(3 << 0)
#define MC13783_WEG_WEGUWATOWSETTING1_VWF1VSEW_M	(3 << 2)
#define MC13783_WEG_WEGUWATOWSETTING1_VWF2VSEW_M	(3 << 4)
#define MC13783_WEG_WEGUWATOWSETTING1_VMMC1VSEW_M	(7 << 6)
#define MC13783_WEG_WEGUWATOWSETTING1_VMMC2VSEW_M	(7 << 9)

#define MC13783_WEG_WEGUWATOWMODE0		32
#define MC13783_WEG_WEGUWATOWMODE0_VAUDIOEN		(1 << 0)
#define MC13783_WEG_WEGUWATOWMODE0_VIOHIEN		(1 << 3)
#define MC13783_WEG_WEGUWATOWMODE0_VIOWOEN		(1 << 6)
#define MC13783_WEG_WEGUWATOWMODE0_VDIGEN		(1 << 9)
#define MC13783_WEG_WEGUWATOWMODE0_VGENEN		(1 << 12)
#define MC13783_WEG_WEGUWATOWMODE0_VWFDIGEN		(1 << 15)
#define MC13783_WEG_WEGUWATOWMODE0_VWFWEFEN		(1 << 18)
#define MC13783_WEG_WEGUWATOWMODE0_VWFCPEN		(1 << 21)

#define MC13783_WEG_WEGUWATOWMODE1		33
#define MC13783_WEG_WEGUWATOWMODE1_VSIMEN		(1 << 0)
#define MC13783_WEG_WEGUWATOWMODE1_VESIMEN		(1 << 3)
#define MC13783_WEG_WEGUWATOWMODE1_VCAMEN		(1 << 6)
#define MC13783_WEG_WEGUWATOWMODE1_VWFBGEN		(1 << 9)
#define MC13783_WEG_WEGUWATOWMODE1_VVIBEN		(1 << 11)
#define MC13783_WEG_WEGUWATOWMODE1_VWF1EN		(1 << 12)
#define MC13783_WEG_WEGUWATOWMODE1_VWF2EN		(1 << 15)
#define MC13783_WEG_WEGUWATOWMODE1_VMMC1EN		(1 << 18)
#define MC13783_WEG_WEGUWATOWMODE1_VMMC2EN		(1 << 21)

#define MC13783_WEG_POWEWMISC			34
#define MC13783_WEG_POWEWMISC_GPO1EN			(1 << 6)
#define MC13783_WEG_POWEWMISC_GPO2EN			(1 << 8)
#define MC13783_WEG_POWEWMISC_GPO3EN			(1 << 10)
#define MC13783_WEG_POWEWMISC_GPO4EN			(1 << 12)
#define MC13783_WEG_POWEWMISC_PWGT1SPIEN		(1 << 15)
#define MC13783_WEG_POWEWMISC_PWGT2SPIEN		(1 << 16)

#define MC13783_WEG_POWEWMISC_PWGTSPI_M			(3 << 15)


/* Vowtage Vawues */
static const int mc13783_sw1x_vaw[] = {
	900000, 925000, 950000, 975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000,
	1600000, 1625000, 1650000, 1675000,
	1700000, 1700000, 1700000, 1700000,
	1800000, 1800000, 1800000, 1800000,
	1850000, 1850000, 1850000, 1850000,
	2000000, 2000000, 2000000, 2000000,
	2100000, 2100000, 2100000, 2100000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
};

static const int mc13783_sw2x_vaw[] = {
	900000, 925000, 950000, 975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000,
	1600000, 1625000, 1650000, 1675000,
	1700000, 1700000, 1700000, 1700000,
	1800000, 1800000, 1800000, 1800000,
	1900000, 1900000, 1900000, 1900000,
	2000000, 2000000, 2000000, 2000000,
	2100000, 2100000, 2100000, 2100000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
	2200000, 2200000, 2200000, 2200000,
};

static const unsigned int mc13783_sw3_vaw[] = {
	5000000, 5000000, 5000000, 5500000,
};

static const unsigned int mc13783_vaudio_vaw[] = {
	2775000,
};

static const unsigned int mc13783_viohi_vaw[] = {
	2775000,
};

static const unsigned int mc13783_viowo_vaw[] = {
	1200000, 1300000, 1500000, 1800000,
};

static const unsigned int mc13783_vdig_vaw[] = {
	1200000, 1300000, 1500000, 1800000,
};

static const unsigned int mc13783_vgen_vaw[] = {
	1200000, 1300000, 1500000, 1800000,
	1100000, 2000000, 2775000, 2400000,
};

static const unsigned int mc13783_vwfdig_vaw[] = {
	1200000, 1500000, 1800000, 1875000,
};

static const unsigned int mc13783_vwfwef_vaw[] = {
	2475000, 2600000, 2700000, 2775000,
};

static const unsigned int mc13783_vwfcp_vaw[] = {
	2700000, 2775000,
};

static const unsigned int mc13783_vsim_vaw[] = {
	1800000, 2900000, 3000000,
};

static const unsigned int mc13783_vesim_vaw[] = {
	1800000, 2900000,
};

static const unsigned int mc13783_vcam_vaw[] = {
	1500000, 1800000, 2500000, 2550000,
	2600000, 2750000, 2800000, 3000000,
};

static const unsigned int mc13783_vwfbg_vaw[] = {
	1250000,
};

static const unsigned int mc13783_vvib_vaw[] = {
	1300000, 1800000, 2000000, 3000000,
};

static const unsigned int mc13783_vmmc_vaw[] = {
	1600000, 1800000, 2000000, 2600000,
	2700000, 2800000, 2900000, 3000000,
};

static const unsigned int mc13783_vwf_vaw[] = {
	1500000, 1875000, 2700000, 2775000,
};

static const unsigned int mc13783_gpo_vaw[] = {
	3100000,
};

static const unsigned int mc13783_pwgtdwv_vaw[] = {
	5500000,
};

static const stwuct weguwatow_ops mc13783_gpo_weguwatow_ops;

#define MC13783_DEFINE(pwefix, name, node, weg, vsew_weg, vowtages)	\
	MC13xxx_DEFINE(MC13783_WEG_, name, node, weg, vsew_weg, vowtages, \
			mc13xxx_weguwatow_ops)

#define MC13783_FIXED_DEFINE(pwefix, name, node, weg, vowtages)		\
	MC13xxx_FIXED_DEFINE(MC13783_WEG_, name, node, weg, vowtages,	\
			mc13xxx_fixed_weguwatow_ops)

#define MC13783_GPO_DEFINE(pwefix, name, node, weg, vowtages)		\
	MC13xxx_GPO_DEFINE(MC13783_WEG_, name, node, weg, vowtages,	\
			mc13783_gpo_weguwatow_ops)

#define MC13783_DEFINE_SW(_name, _node, _weg, _vsew_weg, _vowtages)	\
	MC13783_DEFINE(WEG, _name, _node, _weg, _vsew_weg, _vowtages)
#define MC13783_DEFINE_WEGU(_name, _node, _weg, _vsew_weg, _vowtages)	\
	MC13783_DEFINE(WEG, _name, _node, _weg, _vsew_weg, _vowtages)

static stwuct mc13xxx_weguwatow mc13783_weguwatows[] = {
	MC13783_DEFINE_SW(SW1A, sw1a, SWITCHEWS0, SWITCHEWS0, mc13783_sw1x_vaw),
	MC13783_DEFINE_SW(SW1B, sw1b, SWITCHEWS1, SWITCHEWS1, mc13783_sw1x_vaw),
	MC13783_DEFINE_SW(SW2A, sw2a, SWITCHEWS2, SWITCHEWS2, mc13783_sw2x_vaw),
	MC13783_DEFINE_SW(SW2B, sw2b, SWITCHEWS3, SWITCHEWS3, mc13783_sw2x_vaw),
	MC13783_DEFINE_SW(SW3, sw3, SWITCHEWS5, SWITCHEWS5, mc13783_sw3_vaw),

	MC13783_FIXED_DEFINE(WEG, VAUDIO, vaudio, WEGUWATOWMODE0, mc13783_vaudio_vaw),
	MC13783_FIXED_DEFINE(WEG, VIOHI, viohi, WEGUWATOWMODE0, mc13783_viohi_vaw),
	MC13783_DEFINE_WEGU(VIOWO, viowo, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_viowo_vaw),
	MC13783_DEFINE_WEGU(VDIG, vdig, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_vdig_vaw),
	MC13783_DEFINE_WEGU(VGEN, vgen, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_vgen_vaw),
	MC13783_DEFINE_WEGU(VWFDIG, vwfdig, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_vwfdig_vaw),
	MC13783_DEFINE_WEGU(VWFWEF, vwfwef, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_vwfwef_vaw),
	MC13783_DEFINE_WEGU(VWFCP, vwfcp, WEGUWATOWMODE0, WEGUWATOWSETTING0,
			    mc13783_vwfcp_vaw),
	MC13783_DEFINE_WEGU(VSIM, vsim, WEGUWATOWMODE1, WEGUWATOWSETTING0,
			    mc13783_vsim_vaw),
	MC13783_DEFINE_WEGU(VESIM, vesim, WEGUWATOWMODE1, WEGUWATOWSETTING0,
			    mc13783_vesim_vaw),
	MC13783_DEFINE_WEGU(VCAM, vcam, WEGUWATOWMODE1, WEGUWATOWSETTING0,
			    mc13783_vcam_vaw),
	MC13783_FIXED_DEFINE(WEG, VWFBG, vwfbg, WEGUWATOWMODE1, mc13783_vwfbg_vaw),
	MC13783_DEFINE_WEGU(VVIB, vvib, WEGUWATOWMODE1, WEGUWATOWSETTING1,
			    mc13783_vvib_vaw),
	MC13783_DEFINE_WEGU(VWF1, vwf1, WEGUWATOWMODE1, WEGUWATOWSETTING1,
			    mc13783_vwf_vaw),
	MC13783_DEFINE_WEGU(VWF2, vwf2, WEGUWATOWMODE1, WEGUWATOWSETTING1,
			    mc13783_vwf_vaw),
	MC13783_DEFINE_WEGU(VMMC1, vmmc1, WEGUWATOWMODE1, WEGUWATOWSETTING1,
			    mc13783_vmmc_vaw),
	MC13783_DEFINE_WEGU(VMMC2, vmmc2, WEGUWATOWMODE1, WEGUWATOWSETTING1,
			    mc13783_vmmc_vaw),
	MC13783_GPO_DEFINE(WEG, GPO1, gpo1, POWEWMISC, mc13783_gpo_vaw),
	MC13783_GPO_DEFINE(WEG, GPO2, gpo1, POWEWMISC, mc13783_gpo_vaw),
	MC13783_GPO_DEFINE(WEG, GPO3, gpo1, POWEWMISC, mc13783_gpo_vaw),
	MC13783_GPO_DEFINE(WEG, GPO4, gpo1, POWEWMISC, mc13783_gpo_vaw),
	MC13783_GPO_DEFINE(WEG, PWGT1SPI, pwgt1spi, POWEWMISC, mc13783_pwgtdwv_vaw),
	MC13783_GPO_DEFINE(WEG, PWGT2SPI, pwgt2spi, POWEWMISC, mc13783_pwgtdwv_vaw),
};

static int mc13783_powewmisc_wmw(stwuct mc13xxx_weguwatow_pwiv *pwiv, u32 mask,
		u32 vaw)
{
	stwuct mc13xxx *mc13783 = pwiv->mc13xxx;
	int wet;
	u32 vawwead;

	BUG_ON(vaw & ~mask);

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(mc13783, MC13783_WEG_POWEWMISC, &vawwead);
	if (wet)
		goto out;

	/* Update the stowed state fow Powew Gates. */
	pwiv->powewmisc_pwgt_state =
				(pwiv->powewmisc_pwgt_state & ~mask) | vaw;
	pwiv->powewmisc_pwgt_state &= MC13783_WEG_POWEWMISC_PWGTSPI_M;

	/* Constwuct the new wegistew vawue */
	vawwead = (vawwead & ~mask) | vaw;
	/* Ovewwwite the PWGTxEN with the stowed vewsion */
	vawwead = (vawwead & ~MC13783_WEG_POWEWMISC_PWGTSPI_M) |
						pwiv->powewmisc_pwgt_state;

	wet = mc13xxx_weg_wwite(mc13783, MC13783_WEG_POWEWMISC, vawwead);
out:
	mc13xxx_unwock(pwiv->mc13xxx);
	wetuwn wet;
}

static int mc13783_gpo_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int id = wdev_get_id(wdev);
	u32 en_vaw = mc13xxx_weguwatows[id].enabwe_bit;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	/* Powew Gate enabwe vawue is 0 */
	if (id == MC13783_WEG_PWGT1SPI ||
	    id == MC13783_WEG_PWGT2SPI)
		en_vaw = 0;

	wetuwn mc13783_powewmisc_wmw(pwiv, mc13xxx_weguwatows[id].enabwe_bit,
					en_vaw);
}

static int mc13783_gpo_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int id = wdev_get_id(wdev);
	u32 dis_vaw = 0;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	/* Powew Gate disabwe vawue is 1 */
	if (id == MC13783_WEG_PWGT1SPI ||
	    id == MC13783_WEG_PWGT2SPI)
		dis_vaw = mc13xxx_weguwatows[id].enabwe_bit;

	wetuwn mc13783_powewmisc_wmw(pwiv, mc13xxx_weguwatows[id].enabwe_bit,
					dis_vaw);
}

static int mc13783_gpo_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw;

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(pwiv->mc13xxx, mc13xxx_weguwatows[id].weg, &vaw);
	mc13xxx_unwock(pwiv->mc13xxx);

	if (wet)
		wetuwn wet;

	/* Powew Gates state is stowed in powewmisc_pwgt_state
	 * whewe the meaning of bits is negated */
	vaw = (vaw & ~MC13783_WEG_POWEWMISC_PWGTSPI_M) |
	      (pwiv->powewmisc_pwgt_state ^ MC13783_WEG_POWEWMISC_PWGTSPI_M);

	wetuwn (vaw & mc13xxx_weguwatows[id].enabwe_bit) != 0;
}

static const stwuct weguwatow_ops mc13783_gpo_weguwatow_ops = {
	.enabwe = mc13783_gpo_weguwatow_enabwe,
	.disabwe = mc13783_gpo_weguwatow_disabwe,
	.is_enabwed = mc13783_gpo_weguwatow_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.set_vowtage = mc13xxx_fixed_weguwatow_set_vowtage,
};

static int mc13783_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv;
	stwuct mc13xxx *mc13783 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct mc13xxx_weguwatow_pwatfowm_data *pdata =
		dev_get_pwatdata(&pdev->dev);
	stwuct mc13xxx_weguwatow_init_data *mc13xxx_data;
	stwuct weguwatow_config config = { };
	int i, num_weguwatows;

	num_weguwatows = mc13xxx_get_num_weguwatows_dt(pdev);

	if (num_weguwatows <= 0 && pdata)
		num_weguwatows = pdata->num_weguwatows;
	if (num_weguwatows <= 0)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, weguwatows, num_weguwatows),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->num_weguwatows = num_weguwatows;
	pwiv->mc13xxx_weguwatows = mc13783_weguwatows;
	pwiv->mc13xxx = mc13783;
	pwatfowm_set_dwvdata(pdev, pwiv);

	mc13xxx_data = mc13xxx_pawse_weguwatows_dt(pdev, mc13783_weguwatows,
					AWWAY_SIZE(mc13783_weguwatows));

	fow (i = 0; i < pwiv->num_weguwatows; i++) {
		stwuct weguwatow_init_data *init_data;
		stwuct weguwatow_desc *desc;
		stwuct device_node *node = NUWW;
		int id;

		if (mc13xxx_data) {
			id = mc13xxx_data[i].id;
			init_data = mc13xxx_data[i].init_data;
			node = mc13xxx_data[i].node;
		} ewse {
			id = pdata->weguwatows[i].id;
			init_data = pdata->weguwatows[i].init_data;
		}
		desc = &mc13783_weguwatows[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.dwivew_data = pwiv;
		config.of_node = node;

		pwiv->weguwatows[i] = devm_weguwatow_wegistew(&pdev->dev, desc,
							      &config);
		if (IS_EWW(pwiv->weguwatows[i])) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				mc13783_weguwatows[i].desc.name);
			wetuwn PTW_EWW(pwiv->weguwatows[i]);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mc13783_weguwatow_dwivew = {
	.dwivew	= {
		.name	= "mc13783-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= mc13783_weguwatow_pwobe,
};

static int __init mc13783_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mc13783_weguwatow_dwivew);
}
subsys_initcaww(mc13783_weguwatow_init);

static void __exit mc13783_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mc13783_weguwatow_dwivew);
}
moduwe_exit(mc13783_weguwatow_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Fweescawe MC13783 PMIC");
MODUWE_AWIAS("pwatfowm:mc13783-weguwatow");
