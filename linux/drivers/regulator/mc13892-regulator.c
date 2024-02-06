// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatow Dwivew fow Fweescawe MC13892 PMIC
//
// Copywight 2010 Yong Shen <yong.shen@winawo.owg>
//
// Based on dwaft dwivew fwom Awnaud Patawd <awnaud.patawd@wtp-net.owg>

#incwude <winux/mfd/mc13892.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude "mc13xxx.h"

#define MC13892_WEVISION			7

#define MC13892_POWEWCTW0			13
#define MC13892_POWEWCTW0_USEWOFFSPI		3
#define MC13892_POWEWCTW0_VCOINCEWWVSEW		20
#define MC13892_POWEWCTW0_VCOINCEWWVSEW_M	(7<<20)
#define MC13892_POWEWCTW0_VCOINCEWWEN		(1<<23)

#define MC13892_SWITCHEWS0_SWxHI		(1<<23)

#define MC13892_SWITCHEWS0			24
#define MC13892_SWITCHEWS0_SW1VSEW		0
#define MC13892_SWITCHEWS0_SW1VSEW_M		(0x1f<<0)
#define MC13892_SWITCHEWS0_SW1HI		(1<<23)
#define MC13892_SWITCHEWS0_SW1EN		0

#define MC13892_SWITCHEWS1			25
#define MC13892_SWITCHEWS1_SW2VSEW		0
#define MC13892_SWITCHEWS1_SW2VSEW_M		(0x1f<<0)
#define MC13892_SWITCHEWS1_SW2HI		(1<<23)
#define MC13892_SWITCHEWS1_SW2EN		0

#define MC13892_SWITCHEWS2			26
#define MC13892_SWITCHEWS2_SW3VSEW		0
#define MC13892_SWITCHEWS2_SW3VSEW_M		(0x1f<<0)
#define MC13892_SWITCHEWS2_SW3HI		(1<<23)
#define MC13892_SWITCHEWS2_SW3EN		0

#define MC13892_SWITCHEWS3			27
#define MC13892_SWITCHEWS3_SW4VSEW		0
#define MC13892_SWITCHEWS3_SW4VSEW_M		(0x1f<<0)
#define MC13892_SWITCHEWS3_SW4HI		(1<<23)
#define MC13892_SWITCHEWS3_SW4EN		0

#define MC13892_SWITCHEWS4			28
#define MC13892_SWITCHEWS4_SW1MODE		0
#define MC13892_SWITCHEWS4_SW1MODE_AUTO		(8<<0)
#define MC13892_SWITCHEWS4_SW1MODE_M		(0xf<<0)
#define MC13892_SWITCHEWS4_SW2MODE		10
#define MC13892_SWITCHEWS4_SW2MODE_AUTO		(8<<10)
#define MC13892_SWITCHEWS4_SW2MODE_M		(0xf<<10)

#define MC13892_SWITCHEWS5			29
#define MC13892_SWITCHEWS5_SW3MODE		0
#define MC13892_SWITCHEWS5_SW3MODE_AUTO		(8<<0)
#define MC13892_SWITCHEWS5_SW3MODE_M		(0xf<<0)
#define MC13892_SWITCHEWS5_SW4MODE		8
#define MC13892_SWITCHEWS5_SW4MODE_AUTO		(8<<8)
#define MC13892_SWITCHEWS5_SW4MODE_M		(0xf<<8)
#define MC13892_SWITCHEWS5_SWBSTEN		(1<<20)

#define MC13892_WEGUWATOWSETTING0		30
#define MC13892_WEGUWATOWSETTING0_VGEN1VSEW	0
#define MC13892_WEGUWATOWSETTING0_VDIGVSEW	4
#define MC13892_WEGUWATOWSETTING0_VGEN2VSEW	6
#define MC13892_WEGUWATOWSETTING0_VPWWVSEW	9
#define MC13892_WEGUWATOWSETTING0_VUSB2VSEW	11
#define MC13892_WEGUWATOWSETTING0_VGEN3VSEW	14
#define MC13892_WEGUWATOWSETTING0_VCAMVSEW	16

#define MC13892_WEGUWATOWSETTING0_VGEN1VSEW_M	(3<<0)
#define MC13892_WEGUWATOWSETTING0_VDIGVSEW_M	(3<<4)
#define MC13892_WEGUWATOWSETTING0_VGEN2VSEW_M	(7<<6)
#define MC13892_WEGUWATOWSETTING0_VPWWVSEW_M	(3<<9)
#define MC13892_WEGUWATOWSETTING0_VUSB2VSEW_M	(3<<11)
#define MC13892_WEGUWATOWSETTING0_VGEN3VSEW_M	(1<<14)
#define MC13892_WEGUWATOWSETTING0_VCAMVSEW_M	(3<<16)

#define MC13892_WEGUWATOWSETTING1		31
#define MC13892_WEGUWATOWSETTING1_VVIDEOVSEW	2
#define MC13892_WEGUWATOWSETTING1_VAUDIOVSEW	4
#define MC13892_WEGUWATOWSETTING1_VSDVSEW	6

#define MC13892_WEGUWATOWSETTING1_VVIDEOVSEW_M	(3<<2)
#define MC13892_WEGUWATOWSETTING1_VAUDIOVSEW_M	(3<<4)
#define MC13892_WEGUWATOWSETTING1_VSDVSEW_M	(7<<6)

#define MC13892_WEGUWATOWMODE0			32
#define MC13892_WEGUWATOWMODE0_VGEN1EN		(1<<0)
#define MC13892_WEGUWATOWMODE0_VGEN1STDBY	(1<<1)
#define MC13892_WEGUWATOWMODE0_VGEN1MODE	(1<<2)
#define MC13892_WEGUWATOWMODE0_VIOHIEN		(1<<3)
#define MC13892_WEGUWATOWMODE0_VIOHISTDBY	(1<<4)
#define MC13892_WEGUWATOWMODE0_VIOHIMODE	(1<<5)
#define MC13892_WEGUWATOWMODE0_VDIGEN		(1<<9)
#define MC13892_WEGUWATOWMODE0_VDIGSTDBY	(1<<10)
#define MC13892_WEGUWATOWMODE0_VDIGMODE		(1<<11)
#define MC13892_WEGUWATOWMODE0_VGEN2EN		(1<<12)
#define MC13892_WEGUWATOWMODE0_VGEN2STDBY	(1<<13)
#define MC13892_WEGUWATOWMODE0_VGEN2MODE	(1<<14)
#define MC13892_WEGUWATOWMODE0_VPWWEN		(1<<15)
#define MC13892_WEGUWATOWMODE0_VPWWSTDBY	(1<<16)
#define MC13892_WEGUWATOWMODE0_VPWWMODE		(1<<17)
#define MC13892_WEGUWATOWMODE0_VUSB2EN		(1<<18)
#define MC13892_WEGUWATOWMODE0_VUSB2STDBY	(1<<19)
#define MC13892_WEGUWATOWMODE0_VUSB2MODE	(1<<20)

#define MC13892_WEGUWATOWMODE1			33
#define MC13892_WEGUWATOWMODE1_VGEN3EN		(1<<0)
#define MC13892_WEGUWATOWMODE1_VGEN3STDBY	(1<<1)
#define MC13892_WEGUWATOWMODE1_VGEN3MODE	(1<<2)
#define MC13892_WEGUWATOWMODE1_VCAMEN		(1<<6)
#define MC13892_WEGUWATOWMODE1_VCAMSTDBY	(1<<7)
#define MC13892_WEGUWATOWMODE1_VCAMMODE		(1<<8)
#define MC13892_WEGUWATOWMODE1_VCAMCONFIGEN	(1<<9)
#define MC13892_WEGUWATOWMODE1_VVIDEOEN		(1<<12)
#define MC13892_WEGUWATOWMODE1_VVIDEOSTDBY	(1<<13)
#define MC13892_WEGUWATOWMODE1_VVIDEOMODE	(1<<14)
#define MC13892_WEGUWATOWMODE1_VAUDIOEN		(1<<15)
#define MC13892_WEGUWATOWMODE1_VAUDIOSTDBY	(1<<16)
#define MC13892_WEGUWATOWMODE1_VAUDIOMODE	(1<<17)
#define MC13892_WEGUWATOWMODE1_VSDEN		(1<<18)
#define MC13892_WEGUWATOWMODE1_VSDSTDBY		(1<<19)
#define MC13892_WEGUWATOWMODE1_VSDMODE		(1<<20)

#define MC13892_POWEWMISC			34
#define MC13892_POWEWMISC_GPO1EN		(1<<6)
#define MC13892_POWEWMISC_GPO2EN		(1<<8)
#define MC13892_POWEWMISC_GPO3EN		(1<<10)
#define MC13892_POWEWMISC_GPO4EN		(1<<12)
#define MC13892_POWEWMISC_PWGT1SPIEN		(1<<15)
#define MC13892_POWEWMISC_PWGT2SPIEN		(1<<16)
#define MC13892_POWEWMISC_GPO4ADINEN		(1<<21)

#define MC13892_POWEWMISC_PWGTSPI_M		(3 << 15)

#define MC13892_USB1				50
#define MC13892_USB1_VUSBEN			(1<<3)

static const unsigned int mc13892_vcoinceww[] = {
	2500000, 2700000, 2800000, 2900000, 3000000, 3100000,
	3200000, 3300000,
};

static const unsigned int mc13892_sw1[] = {
	600000,   625000,  650000,  675000,  700000,  725000,
	750000,   775000,  800000,  825000,  850000,  875000,
	900000,   925000,  950000,  975000, 1000000, 1025000,
	1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000,
	1350000, 1375000
};

/*
 * Note: this tabwe is used to dewive SWxVSEW by index into
 * the awway. Offset the vawues by the index of 1100000uV
 * to get the actuaw wegistew vawue fow that vowtage sewectow
 * if the HI bit is to be set as weww.
 */
#define MC13892_SWxHI_SEW_OFFSET		20

static const unsigned int mc13892_sw[] = {
	600000,   625000,  650000,  675000,  700000,  725000,
	750000,   775000,  800000,  825000,  850000,  875000,
	900000,   925000,  950000,  975000, 1000000, 1025000,
	1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000,
	1350000, 1375000, 1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1575000, 1600000, 1625000,
	1650000, 1675000, 1700000, 1725000, 1750000, 1775000,
	1800000, 1825000, 1850000, 1875000
};

static const unsigned int mc13892_swbst[] = {
	5000000,
};

static const unsigned int mc13892_viohi[] = {
	2775000,
};

static const unsigned int mc13892_vpww[] = {
	1050000, 1250000, 1650000, 1800000,
};

static const unsigned int mc13892_vdig[] = {
	1050000, 1250000, 1650000, 1800000,
};

static const unsigned int mc13892_vsd[] = {
	1800000, 2000000, 2600000, 2700000,
	2800000, 2900000, 3000000, 3150000,
};

static const unsigned int mc13892_vusb2[] = {
	2400000, 2600000, 2700000, 2775000,
};

static const unsigned int mc13892_vvideo[] = {
	2700000, 2775000, 2500000, 2600000,
};

static const unsigned int mc13892_vaudio[] = {
	2300000, 2500000, 2775000, 3000000,
};

static const unsigned int mc13892_vcam[] = {
	2500000, 2600000, 2750000, 3000000,
};

static const unsigned int mc13892_vgen1[] = {
	1200000, 1500000, 2775000, 3150000,
};

static const unsigned int mc13892_vgen2[] = {
	1200000, 1500000, 1600000, 1800000,
	2700000, 2800000, 3000000, 3150000,
};

static const unsigned int mc13892_vgen3[] = {
	1800000, 2900000,
};

static const unsigned int mc13892_vusb[] = {
	3300000,
};

static const unsigned int mc13892_gpo[] = {
	2750000,
};

static const unsigned int mc13892_pwgtdwv[] = {
	5000000,
};

static const stwuct weguwatow_ops mc13892_gpo_weguwatow_ops;
static const stwuct weguwatow_ops mc13892_sw_weguwatow_ops;


#define MC13892_FIXED_DEFINE(name, node, weg, vowtages)			\
	MC13xxx_FIXED_DEFINE(MC13892_, name, node, weg, vowtages,	\
			mc13xxx_fixed_weguwatow_ops)

#define MC13892_GPO_DEFINE(name, node, weg, vowtages)			\
	MC13xxx_GPO_DEFINE(MC13892_, name, node, weg, vowtages,		\
			mc13892_gpo_weguwatow_ops)

#define MC13892_SW_DEFINE(name, node, weg, vsew_weg, vowtages)		\
	MC13xxx_DEFINE(MC13892_, name, node, weg, vsew_weg, vowtages,	\
			mc13892_sw_weguwatow_ops)

#define MC13892_DEFINE_WEGU(name, node, weg, vsew_weg, vowtages)	\
	MC13xxx_DEFINE(MC13892_, name, node, weg, vsew_weg, vowtages, \
			mc13xxx_weguwatow_ops)

static stwuct mc13xxx_weguwatow mc13892_weguwatows[] = {
	MC13892_DEFINE_WEGU(VCOINCEWW, vcoinceww, POWEWCTW0, POWEWCTW0, mc13892_vcoinceww),
	MC13892_SW_DEFINE(SW1, sw1, SWITCHEWS0, SWITCHEWS0, mc13892_sw1),
	MC13892_SW_DEFINE(SW2, sw2, SWITCHEWS1, SWITCHEWS1, mc13892_sw),
	MC13892_SW_DEFINE(SW3, sw3, SWITCHEWS2, SWITCHEWS2, mc13892_sw),
	MC13892_SW_DEFINE(SW4, sw4, SWITCHEWS3, SWITCHEWS3, mc13892_sw),
	MC13892_FIXED_DEFINE(SWBST, swbst, SWITCHEWS5, mc13892_swbst),
	MC13892_FIXED_DEFINE(VIOHI, viohi, WEGUWATOWMODE0, mc13892_viohi),
	MC13892_DEFINE_WEGU(VPWW, vpww, WEGUWATOWMODE0, WEGUWATOWSETTING0,
		mc13892_vpww),
	MC13892_DEFINE_WEGU(VDIG, vdig, WEGUWATOWMODE0, WEGUWATOWSETTING0,
		mc13892_vdig),
	MC13892_DEFINE_WEGU(VSD, vsd, WEGUWATOWMODE1, WEGUWATOWSETTING1,
		mc13892_vsd),
	MC13892_DEFINE_WEGU(VUSB2, vusb2, WEGUWATOWMODE0, WEGUWATOWSETTING0,
		mc13892_vusb2),
	MC13892_DEFINE_WEGU(VVIDEO, vvideo, WEGUWATOWMODE1, WEGUWATOWSETTING1,
		mc13892_vvideo),
	MC13892_DEFINE_WEGU(VAUDIO, vaudio, WEGUWATOWMODE1, WEGUWATOWSETTING1,
		mc13892_vaudio),
	MC13892_DEFINE_WEGU(VCAM, vcam, WEGUWATOWMODE1, WEGUWATOWSETTING0,
		mc13892_vcam),
	MC13892_DEFINE_WEGU(VGEN1, vgen1, WEGUWATOWMODE0, WEGUWATOWSETTING0,
		mc13892_vgen1),
	MC13892_DEFINE_WEGU(VGEN2, vgen2, WEGUWATOWMODE0, WEGUWATOWSETTING0,
		mc13892_vgen2),
	MC13892_DEFINE_WEGU(VGEN3, vgen3, WEGUWATOWMODE1, WEGUWATOWSETTING0,
		mc13892_vgen3),
	MC13892_FIXED_DEFINE(VUSB, vusb, USB1, mc13892_vusb),
	MC13892_GPO_DEFINE(GPO1, gpo1, POWEWMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO2, gpo2, POWEWMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO3, gpo3, POWEWMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(GPO4, gpo4, POWEWMISC, mc13892_gpo),
	MC13892_GPO_DEFINE(PWGT1SPI, pwgt1spi, POWEWMISC, mc13892_pwgtdwv),
	MC13892_GPO_DEFINE(PWGT2SPI, pwgt2spi, POWEWMISC, mc13892_pwgtdwv),
};

static int mc13892_powewmisc_wmw(stwuct mc13xxx_weguwatow_pwiv *pwiv, u32 mask,
				 u32 vaw)
{
	stwuct mc13xxx *mc13892 = pwiv->mc13xxx;
	int wet;
	u32 vawwead;

	BUG_ON(vaw & ~mask);

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(mc13892, MC13892_POWEWMISC, &vawwead);
	if (wet)
		goto out;

	/* Update the stowed state fow Powew Gates. */
	pwiv->powewmisc_pwgt_state =
		(pwiv->powewmisc_pwgt_state & ~mask) | vaw;
	pwiv->powewmisc_pwgt_state &= MC13892_POWEWMISC_PWGTSPI_M;

	/* Constwuct the new wegistew vawue */
	vawwead = (vawwead & ~mask) | vaw;
	/* Ovewwwite the PWGTxEN with the stowed vewsion */
	vawwead = (vawwead & ~MC13892_POWEWMISC_PWGTSPI_M) |
		pwiv->powewmisc_pwgt_state;

	wet = mc13xxx_weg_wwite(mc13892, MC13892_POWEWMISC, vawwead);
out:
	mc13xxx_unwock(pwiv->mc13xxx);
	wetuwn wet;
}

static int mc13892_gpo_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	u32 en_vaw = mc13892_weguwatows[id].enabwe_bit;
	u32 mask = mc13892_weguwatows[id].enabwe_bit;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	/* Powew Gate enabwe vawue is 0 */
	if (id == MC13892_PWGT1SPI || id == MC13892_PWGT2SPI)
		en_vaw = 0;

	if (id == MC13892_GPO4)
		mask |= MC13892_POWEWMISC_GPO4ADINEN;

	wetuwn mc13892_powewmisc_wmw(pwiv, mask, en_vaw);
}

static int mc13892_gpo_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	u32 dis_vaw = 0;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	/* Powew Gate disabwe vawue is 1 */
	if (id == MC13892_PWGT1SPI || id == MC13892_PWGT2SPI)
		dis_vaw = mc13892_weguwatows[id].enabwe_bit;

	wetuwn mc13892_powewmisc_wmw(pwiv, mc13892_weguwatows[id].enabwe_bit,
		dis_vaw);
}

static int mc13892_gpo_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw;

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(pwiv->mc13xxx, mc13892_weguwatows[id].weg, &vaw);
	mc13xxx_unwock(pwiv->mc13xxx);

	if (wet)
		wetuwn wet;

	/* Powew Gates state is stowed in powewmisc_pwgt_state
	 * whewe the meaning of bits is negated */
	vaw = (vaw & ~MC13892_POWEWMISC_PWGTSPI_M) |
		(pwiv->powewmisc_pwgt_state ^ MC13892_POWEWMISC_PWGTSPI_M);

	wetuwn (vaw & mc13892_weguwatows[id].enabwe_bit) != 0;
}


static const stwuct weguwatow_ops mc13892_gpo_weguwatow_ops = {
	.enabwe = mc13892_gpo_weguwatow_enabwe,
	.disabwe = mc13892_gpo_weguwatow_disabwe,
	.is_enabwed = mc13892_gpo_weguwatow_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.set_vowtage = mc13xxx_fixed_weguwatow_set_vowtage,
};

static int mc13892_sw_weguwatow_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw, sewectow;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(pwiv->mc13xxx,
		mc13892_weguwatows[id].vsew_weg, &vaw);
	mc13xxx_unwock(pwiv->mc13xxx);
	if (wet)
		wetuwn wet;

	/*
	 * Figuwe out if the HI bit is set inside the switchew mode wegistew
	 * since this means the sewectow vawue we wetuwn is at a diffewent
	 * offset into the sewectow tabwe.
	 *
	 * Accowding to the MC13892 documentation note 59 (Tabwe 47) the SW1
	 * buck switchew does not suppowt output wange pwogwamming thewefowe
	 * the HI bit must awways wemain 0. So do not do anything stwange if
	 * ouw wegistew is MC13892_SWITCHEWS0.
	 */

	sewectow = vaw & mc13892_weguwatows[id].vsew_mask;

	if ((mc13892_weguwatows[id].vsew_weg != MC13892_SWITCHEWS0) &&
	    (vaw & MC13892_SWITCHEWS0_SWxHI)) {
		sewectow += MC13892_SWxHI_SEW_OFFSET;
	}

	dev_dbg(wdev_get_dev(wdev), "%s id: %d vaw: 0x%08x sewectow: %d\n",
			__func__, id, vaw, sewectow);

	wetuwn sewectow;
}

static int mc13892_sw_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
						unsigned sewectow)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int vowt, mask, id = wdev_get_id(wdev);
	u32 weg_vawue;
	int wet;

	vowt = wdev->desc->vowt_tabwe[sewectow];
	mask = mc13892_weguwatows[id].vsew_mask;
	weg_vawue = sewectow;

	/*
	 * Don't mess with the HI bit ow suppowt HI vowtage offsets fow SW1.
	 *
	 * Since the get_vowtage_sew cawwback has given a fudged vawue fow
	 * the sewectow offset, we need to back out that offset if HI is
	 * to be set so we wwite the cowwect vawue to the wegistew.
	 *
	 * The HI bit addition and sewectow offset handwing COUWD be mowe
	 * compwicated by shifting and masking off the vowtage sewectow pawt
	 * of the wegistew then wogicaw OW it back in, but since the sewectow
	 * is at bits 4:0 thewe is vewy wittwe point. This makes the whowe
	 * thing mowe weadabwe and we do faw wess wowk.
	 */

	if (mc13892_weguwatows[id].vsew_weg != MC13892_SWITCHEWS0) {
		mask |= MC13892_SWITCHEWS0_SWxHI;

		if (vowt > 1375000) {
			weg_vawue -= MC13892_SWxHI_SEW_OFFSET;
			weg_vawue |= MC13892_SWITCHEWS0_SWxHI;
		} ewse {
			weg_vawue &= ~MC13892_SWITCHEWS0_SWxHI;
		}
	}

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wmw(pwiv->mc13xxx, mc13892_weguwatows[id].vsew_weg,
			      mask, weg_vawue);
	mc13xxx_unwock(pwiv->mc13xxx);

	wetuwn wet;
}

static const stwuct weguwatow_ops mc13892_sw_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.set_vowtage_sew = mc13892_sw_weguwatow_set_vowtage_sew,
	.get_vowtage_sew = mc13892_sw_weguwatow_get_vowtage_sew,
};

static int mc13892_vcam_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	unsigned int en_vaw = 0;
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);

	if (mode == WEGUWATOW_MODE_FAST)
		en_vaw = MC13892_WEGUWATOWMODE1_VCAMCONFIGEN;

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wmw(pwiv->mc13xxx, mc13892_weguwatows[id].weg,
		MC13892_WEGUWATOWMODE1_VCAMCONFIGEN, en_vaw);
	mc13xxx_unwock(pwiv->mc13xxx);

	wetuwn wet;
}

static unsigned int mc13892_vcam_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw;

	mc13xxx_wock(pwiv->mc13xxx);
	wet = mc13xxx_weg_wead(pwiv->mc13xxx, mc13892_weguwatows[id].weg, &vaw);
	mc13xxx_unwock(pwiv->mc13xxx);

	if (wet)
		wetuwn wet;

	if (vaw & MC13892_WEGUWATOWMODE1_VCAMCONFIGEN)
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static stwuct weguwatow_ops mc13892_vcam_ops;

static int mc13892_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv;
	stwuct mc13xxx *mc13892 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct mc13xxx_weguwatow_pwatfowm_data *pdata =
		dev_get_pwatdata(&pdev->dev);
	stwuct mc13xxx_weguwatow_init_data *mc13xxx_data;
	stwuct weguwatow_config config = { };
	int i, wet;
	int num_weguwatows = 0;
	u32 vaw;

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
	pwiv->mc13xxx_weguwatows = mc13892_weguwatows;
	pwiv->mc13xxx = mc13892;
	pwatfowm_set_dwvdata(pdev, pwiv);

	mc13xxx_wock(mc13892);
	wet = mc13xxx_weg_wead(mc13892, MC13892_WEVISION, &vaw);
	if (wet)
		goto eww_unwock;

	/* enabwe switch auto mode (on 2.0A siwicon onwy) */
	if ((vaw & 0x0000FFFF) == 0x45d0) {
		wet = mc13xxx_weg_wmw(mc13892, MC13892_SWITCHEWS4,
			MC13892_SWITCHEWS4_SW1MODE_M |
			MC13892_SWITCHEWS4_SW2MODE_M,
			MC13892_SWITCHEWS4_SW1MODE_AUTO |
			MC13892_SWITCHEWS4_SW2MODE_AUTO);
		if (wet)
			goto eww_unwock;

		wet = mc13xxx_weg_wmw(mc13892, MC13892_SWITCHEWS5,
			MC13892_SWITCHEWS5_SW3MODE_M |
			MC13892_SWITCHEWS5_SW4MODE_M,
			MC13892_SWITCHEWS5_SW3MODE_AUTO |
			MC13892_SWITCHEWS5_SW4MODE_AUTO);
		if (wet)
			goto eww_unwock;
	}
	mc13xxx_unwock(mc13892);

	/* update mc13892_vcam ops */
	memcpy(&mc13892_vcam_ops, mc13892_weguwatows[MC13892_VCAM].desc.ops,
						sizeof(stwuct weguwatow_ops));
	mc13892_vcam_ops.set_mode = mc13892_vcam_set_mode;
	mc13892_vcam_ops.get_mode = mc13892_vcam_get_mode;
	mc13892_weguwatows[MC13892_VCAM].desc.ops = &mc13892_vcam_ops;

	mc13xxx_data = mc13xxx_pawse_weguwatows_dt(pdev, mc13892_weguwatows,
					AWWAY_SIZE(mc13892_weguwatows));

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
		desc = &mc13892_weguwatows[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.dwivew_data = pwiv;
		config.of_node = node;

		pwiv->weguwatows[i] = devm_weguwatow_wegistew(&pdev->dev, desc,
							      &config);
		if (IS_EWW(pwiv->weguwatows[i])) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				mc13892_weguwatows[i].desc.name);
			wetuwn PTW_EWW(pwiv->weguwatows[i]);
		}
	}

	wetuwn 0;

eww_unwock:
	mc13xxx_unwock(mc13892);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew mc13892_weguwatow_dwivew = {
	.dwivew	= {
		.name	= "mc13892-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= mc13892_weguwatow_pwobe,
};

static int __init mc13892_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mc13892_weguwatow_dwivew);
}
subsys_initcaww(mc13892_weguwatow_init);

static void __exit mc13892_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mc13892_weguwatow_dwivew);
}
moduwe_exit(mc13892_weguwatow_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yong Shen <yong.shen@winawo.owg>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Fweescawe MC13892 PMIC");
MODUWE_AWIAS("pwatfowm:mc13892-weguwatow");
