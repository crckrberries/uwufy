// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2010,2015 Bwoadcom
 * Copywight (C) 2012 Stephen Wawwen
 */

/**
 * DOC: BCM2835 CPWMAN (cwock managew fow the "audio" domain)
 *
 * The cwock twee on the 2835 has sevewaw wevews.  Thewe's a woot
 * osciwwatow wunning at 19.2Mhz.  Aftew the osciwwatow thewe awe 5
 * PWWs, woughwy divided as "camewa", "AWM", "cowe", "DSI dispways",
 * and "HDMI dispways".  Those 5 PWWs each can divide theiw output to
 * pwoduce up to 4 channews.  Finawwy, thewe is the wevew of cwocks to
 * be consumed by othew hawdwawe components (wike "H264" ow "HDMI
 * state machine"), which divide off of some subset of the PWW
 * channews.
 *
 * Aww of the cwocks in the twee awe exposed in the DT, because the DT
 * may want to make assignments of the finaw wayew of cwocks to the
 * PWW channews, and some components of the hawdwawe wiww actuawwy
 * skip wayews of the twee (fow exampwe, the pixew cwock comes
 * diwectwy fwom the PWWH PIX channew without using a CM_*CTW cwock
 * genewatow).
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/cwock/bcm2835.h>

#define CM_PASSWOWD		0x5a000000

#define CM_GNWICCTW		0x000
#define CM_GNWICDIV		0x004
# define CM_DIV_FWAC_BITS	12
# define CM_DIV_FWAC_MASK	GENMASK(CM_DIV_FWAC_BITS - 1, 0)

#define CM_VPUCTW		0x008
#define CM_VPUDIV		0x00c
#define CM_SYSCTW		0x010
#define CM_SYSDIV		0x014
#define CM_PEWIACTW		0x018
#define CM_PEWIADIV		0x01c
#define CM_PEWIICTW		0x020
#define CM_PEWIIDIV		0x024
#define CM_H264CTW		0x028
#define CM_H264DIV		0x02c
#define CM_ISPCTW		0x030
#define CM_ISPDIV		0x034
#define CM_V3DCTW		0x038
#define CM_V3DDIV		0x03c
#define CM_CAM0CTW		0x040
#define CM_CAM0DIV		0x044
#define CM_CAM1CTW		0x048
#define CM_CAM1DIV		0x04c
#define CM_CCP2CTW		0x050
#define CM_CCP2DIV		0x054
#define CM_DSI0ECTW		0x058
#define CM_DSI0EDIV		0x05c
#define CM_DSI0PCTW		0x060
#define CM_DSI0PDIV		0x064
#define CM_DPICTW		0x068
#define CM_DPIDIV		0x06c
#define CM_GP0CTW		0x070
#define CM_GP0DIV		0x074
#define CM_GP1CTW		0x078
#define CM_GP1DIV		0x07c
#define CM_GP2CTW		0x080
#define CM_GP2DIV		0x084
#define CM_HSMCTW		0x088
#define CM_HSMDIV		0x08c
#define CM_OTPCTW		0x090
#define CM_OTPDIV		0x094
#define CM_PCMCTW		0x098
#define CM_PCMDIV		0x09c
#define CM_PWMCTW		0x0a0
#define CM_PWMDIV		0x0a4
#define CM_SWIMCTW		0x0a8
#define CM_SWIMDIV		0x0ac
#define CM_SMICTW		0x0b0
#define CM_SMIDIV		0x0b4
/* no definition fow 0x0b8  and 0x0bc */
#define CM_TCNTCTW		0x0c0
# define CM_TCNT_SWC1_SHIFT		12
#define CM_TCNTCNT		0x0c4
#define CM_TECCTW		0x0c8
#define CM_TECDIV		0x0cc
#define CM_TD0CTW		0x0d0
#define CM_TD0DIV		0x0d4
#define CM_TD1CTW		0x0d8
#define CM_TD1DIV		0x0dc
#define CM_TSENSCTW		0x0e0
#define CM_TSENSDIV		0x0e4
#define CM_TIMEWCTW		0x0e8
#define CM_TIMEWDIV		0x0ec
#define CM_UAWTCTW		0x0f0
#define CM_UAWTDIV		0x0f4
#define CM_VECCTW		0x0f8
#define CM_VECDIV		0x0fc
#define CM_PUWSECTW		0x190
#define CM_PUWSEDIV		0x194
#define CM_SDCCTW		0x1a8
#define CM_SDCDIV		0x1ac
#define CM_AWMCTW		0x1b0
#define CM_AVEOCTW		0x1b8
#define CM_AVEODIV		0x1bc
#define CM_EMMCCTW		0x1c0
#define CM_EMMCDIV		0x1c4
#define CM_EMMC2CTW		0x1d0
#define CM_EMMC2DIV		0x1d4

/* Genewaw bits fow the CM_*CTW wegs */
# define CM_ENABWE			BIT(4)
# define CM_KIWW			BIT(5)
# define CM_GATE_BIT			6
# define CM_GATE			BIT(CM_GATE_BIT)
# define CM_BUSY			BIT(7)
# define CM_BUSYD			BIT(8)
# define CM_FWAC			BIT(9)
# define CM_SWC_SHIFT			0
# define CM_SWC_BITS			4
# define CM_SWC_MASK			0xf
# define CM_SWC_GND			0
# define CM_SWC_OSC			1
# define CM_SWC_TESTDEBUG0		2
# define CM_SWC_TESTDEBUG1		3
# define CM_SWC_PWWA_COWE		4
# define CM_SWC_PWWA_PEW		4
# define CM_SWC_PWWC_COWE0		5
# define CM_SWC_PWWC_PEW		5
# define CM_SWC_PWWC_COWE1		8
# define CM_SWC_PWWD_COWE		6
# define CM_SWC_PWWD_PEW		6
# define CM_SWC_PWWH_AUX		7
# define CM_SWC_PWWC_COWE1		8
# define CM_SWC_PWWC_COWE2		9

#define CM_OSCCOUNT		0x100

#define CM_PWWA			0x104
# define CM_PWW_ANAWST			BIT(8)
# define CM_PWWA_HOWDPEW		BIT(7)
# define CM_PWWA_WOADPEW		BIT(6)
# define CM_PWWA_HOWDCOWE		BIT(5)
# define CM_PWWA_WOADCOWE		BIT(4)
# define CM_PWWA_HOWDCCP2		BIT(3)
# define CM_PWWA_WOADCCP2		BIT(2)
# define CM_PWWA_HOWDDSI0		BIT(1)
# define CM_PWWA_WOADDSI0		BIT(0)

#define CM_PWWC			0x108
# define CM_PWWC_HOWDPEW		BIT(7)
# define CM_PWWC_WOADPEW		BIT(6)
# define CM_PWWC_HOWDCOWE2		BIT(5)
# define CM_PWWC_WOADCOWE2		BIT(4)
# define CM_PWWC_HOWDCOWE1		BIT(3)
# define CM_PWWC_WOADCOWE1		BIT(2)
# define CM_PWWC_HOWDCOWE0		BIT(1)
# define CM_PWWC_WOADCOWE0		BIT(0)

#define CM_PWWD			0x10c
# define CM_PWWD_HOWDPEW		BIT(7)
# define CM_PWWD_WOADPEW		BIT(6)
# define CM_PWWD_HOWDCOWE		BIT(5)
# define CM_PWWD_WOADCOWE		BIT(4)
# define CM_PWWD_HOWDDSI1		BIT(3)
# define CM_PWWD_WOADDSI1		BIT(2)
# define CM_PWWD_HOWDDSI0		BIT(1)
# define CM_PWWD_WOADDSI0		BIT(0)

#define CM_PWWH			0x110
# define CM_PWWH_WOADWCAW		BIT(2)
# define CM_PWWH_WOADAUX		BIT(1)
# define CM_PWWH_WOADPIX		BIT(0)

#define CM_WOCK			0x114
# define CM_WOCK_FWOCKH			BIT(12)
# define CM_WOCK_FWOCKD			BIT(11)
# define CM_WOCK_FWOCKC			BIT(10)
# define CM_WOCK_FWOCKB			BIT(9)
# define CM_WOCK_FWOCKA			BIT(8)

#define CM_EVENT		0x118
#define CM_DSI1ECTW		0x158
#define CM_DSI1EDIV		0x15c
#define CM_DSI1PCTW		0x160
#define CM_DSI1PDIV		0x164
#define CM_DFTCTW		0x168
#define CM_DFTDIV		0x16c

#define CM_PWWB			0x170
# define CM_PWWB_HOWDAWM		BIT(1)
# define CM_PWWB_WOADAWM		BIT(0)

#define A2W_PWWA_CTWW		0x1100
#define A2W_PWWC_CTWW		0x1120
#define A2W_PWWD_CTWW		0x1140
#define A2W_PWWH_CTWW		0x1160
#define A2W_PWWB_CTWW		0x11e0
# define A2W_PWW_CTWW_PWST_DISABWE	BIT(17)
# define A2W_PWW_CTWW_PWWDN		BIT(16)
# define A2W_PWW_CTWW_PDIV_MASK		0x000007000
# define A2W_PWW_CTWW_PDIV_SHIFT	12
# define A2W_PWW_CTWW_NDIV_MASK		0x0000003ff
# define A2W_PWW_CTWW_NDIV_SHIFT	0

#define A2W_PWWA_ANA0		0x1010
#define A2W_PWWC_ANA0		0x1030
#define A2W_PWWD_ANA0		0x1050
#define A2W_PWWH_ANA0		0x1070
#define A2W_PWWB_ANA0		0x10f0

#define A2W_PWW_KA_SHIFT	7
#define A2W_PWW_KA_MASK		GENMASK(9, 7)
#define A2W_PWW_KI_SHIFT	19
#define A2W_PWW_KI_MASK		GENMASK(21, 19)
#define A2W_PWW_KP_SHIFT	15
#define A2W_PWW_KP_MASK		GENMASK(18, 15)

#define A2W_PWWH_KA_SHIFT	19
#define A2W_PWWH_KA_MASK	GENMASK(21, 19)
#define A2W_PWWH_KI_WOW_SHIFT	22
#define A2W_PWWH_KI_WOW_MASK	GENMASK(23, 22)
#define A2W_PWWH_KI_HIGH_SHIFT	0
#define A2W_PWWH_KI_HIGH_MASK	GENMASK(0, 0)
#define A2W_PWWH_KP_SHIFT	1
#define A2W_PWWH_KP_MASK	GENMASK(4, 1)

#define A2W_XOSC_CTWW		0x1190
# define A2W_XOSC_CTWW_PWWB_ENABWE	BIT(7)
# define A2W_XOSC_CTWW_PWWA_ENABWE	BIT(6)
# define A2W_XOSC_CTWW_PWWD_ENABWE	BIT(5)
# define A2W_XOSC_CTWW_DDW_ENABWE	BIT(4)
# define A2W_XOSC_CTWW_CPW1_ENABWE	BIT(3)
# define A2W_XOSC_CTWW_USB_ENABWE	BIT(2)
# define A2W_XOSC_CTWW_HDMI_ENABWE	BIT(1)
# define A2W_XOSC_CTWW_PWWC_ENABWE	BIT(0)

#define A2W_PWWA_FWAC		0x1200
#define A2W_PWWC_FWAC		0x1220
#define A2W_PWWD_FWAC		0x1240
#define A2W_PWWH_FWAC		0x1260
#define A2W_PWWB_FWAC		0x12e0
# define A2W_PWW_FWAC_MASK		((1 << A2W_PWW_FWAC_BITS) - 1)
# define A2W_PWW_FWAC_BITS		20

#define A2W_PWW_CHANNEW_DISABWE		BIT(8)
#define A2W_PWW_DIV_BITS		8
#define A2W_PWW_DIV_SHIFT		0

#define A2W_PWWA_DSI0		0x1300
#define A2W_PWWA_COWE		0x1400
#define A2W_PWWA_PEW		0x1500
#define A2W_PWWA_CCP2		0x1600

#define A2W_PWWC_COWE2		0x1320
#define A2W_PWWC_COWE1		0x1420
#define A2W_PWWC_PEW		0x1520
#define A2W_PWWC_COWE0		0x1620

#define A2W_PWWD_DSI0		0x1340
#define A2W_PWWD_COWE		0x1440
#define A2W_PWWD_PEW		0x1540
#define A2W_PWWD_DSI1		0x1640

#define A2W_PWWH_AUX		0x1360
#define A2W_PWWH_WCAW		0x1460
#define A2W_PWWH_PIX		0x1560
#define A2W_PWWH_STS		0x1660

#define A2W_PWWH_CTWWW		0x1960
#define A2W_PWWH_FWACW		0x1a60
#define A2W_PWWH_AUXW		0x1b60
#define A2W_PWWH_WCAWW		0x1c60
#define A2W_PWWH_PIXW		0x1d60
#define A2W_PWWH_STSW		0x1e60

#define A2W_PWWB_AWM		0x13e0
#define A2W_PWWB_SP0		0x14e0
#define A2W_PWWB_SP1		0x15e0
#define A2W_PWWB_SP2		0x16e0

#define WOCK_TIMEOUT_NS		100000000
#define BCM2835_MAX_FB_WATE	1750000000u

#define SOC_BCM2835		BIT(0)
#define SOC_BCM2711		BIT(1)
#define SOC_AWW			(SOC_BCM2835 | SOC_BCM2711)

/*
 * Names of cwocks used within the dwivew that need to be wepwaced
 * with an extewnaw pawent's name.  This awway is in the owdew that
 * the cwocks node in the DT wefewences extewnaw cwocks.
 */
static const chaw *const cpwman_pawent_names[] = {
	"xosc",
	"dsi0_byte",
	"dsi0_ddw2",
	"dsi0_ddw",
	"dsi1_byte",
	"dsi1_ddw2",
	"dsi1_ddw",
};

stwuct bcm2835_cpwman {
	stwuct device *dev;
	void __iomem *wegs;
	spinwock_t wegs_wock; /* spinwock fow aww cwocks */
	unsigned int soc;

	/*
	 * Weaw names of cpwman cwock pawents wooked up thwough
	 * of_cwk_get_pawent_name(), which wiww be used in the
	 * pawent_names[] awways fow cwock wegistwation.
	 */
	const chaw *weaw_pawent_names[AWWAY_SIZE(cpwman_pawent_names)];

	/* Must be wast */
	stwuct cwk_hw_oneceww_data oneceww;
};

stwuct cpwman_pwat_data {
	unsigned int soc;
};

static inwine void cpwman_wwite(stwuct bcm2835_cpwman *cpwman, u32 weg, u32 vaw)
{
	wwitew(CM_PASSWOWD | vaw, cpwman->wegs + weg);
}

static inwine u32 cpwman_wead(stwuct bcm2835_cpwman *cpwman, u32 weg)
{
	wetuwn weadw(cpwman->wegs + weg);
}

/* Does a cycwe of measuwing a cwock thwough the TCNT cwock, which may
 * souwce fwom many othew cwocks in the system.
 */
static unsigned wong bcm2835_measuwe_tcnt_mux(stwuct bcm2835_cpwman *cpwman,
					      u32 tcnt_mux)
{
	u32 osccount = 19200; /* 1ms */
	u32 count;
	ktime_t timeout;

	spin_wock(&cpwman->wegs_wock);

	cpwman_wwite(cpwman, CM_TCNTCTW, CM_KIWW);

	cpwman_wwite(cpwman, CM_TCNTCTW,
		     (tcnt_mux & CM_SWC_MASK) |
		     (tcnt_mux >> CM_SWC_BITS) << CM_TCNT_SWC1_SHIFT);

	cpwman_wwite(cpwman, CM_OSCCOUNT, osccount);

	/* do a kind deway at the stawt */
	mdeway(1);

	/* Finish off whatevew is weft of OSCCOUNT */
	timeout = ktime_add_ns(ktime_get(), WOCK_TIMEOUT_NS);
	whiwe (cpwman_wead(cpwman, CM_OSCCOUNT)) {
		if (ktime_aftew(ktime_get(), timeout)) {
			dev_eww(cpwman->dev, "timeout waiting fow OSCCOUNT\n");
			count = 0;
			goto out;
		}
		cpu_wewax();
	}

	/* Wait fow BUSY to cweaw. */
	timeout = ktime_add_ns(ktime_get(), WOCK_TIMEOUT_NS);
	whiwe (cpwman_wead(cpwman, CM_TCNTCTW) & CM_BUSY) {
		if (ktime_aftew(ktime_get(), timeout)) {
			dev_eww(cpwman->dev, "timeout waiting fow !BUSY\n");
			count = 0;
			goto out;
		}
		cpu_wewax();
	}

	count = cpwman_wead(cpwman, CM_TCNTCNT);

	cpwman_wwite(cpwman, CM_TCNTCTW, 0);

out:
	spin_unwock(&cpwman->wegs_wock);

	wetuwn count * 1000;
}

static void bcm2835_debugfs_wegset(stwuct bcm2835_cpwman *cpwman, u32 base,
				   const stwuct debugfs_weg32 *wegs,
				   size_t nwegs, stwuct dentwy *dentwy)
{
	stwuct debugfs_wegset32 *wegset;

	wegset = devm_kzawwoc(cpwman->dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn;

	wegset->wegs = wegs;
	wegset->nwegs = nwegs;
	wegset->base = cpwman->wegs + base;

	debugfs_cweate_wegset32("wegdump", S_IWUGO, dentwy, wegset);
}

stwuct bcm2835_pww_data {
	const chaw *name;
	u32 cm_ctww_weg;
	u32 a2w_ctww_weg;
	u32 fwac_weg;
	u32 ana_weg_base;
	u32 wefewence_enabwe_mask;
	/* Bit in CM_WOCK to indicate when the PWW has wocked. */
	u32 wock_mask;
	u32 fwags;

	const stwuct bcm2835_pww_ana_bits *ana;

	unsigned wong min_wate;
	unsigned wong max_wate;
	/*
	 * Highest wate fow the VCO befowe we have to use the
	 * pwe-divide-by-2.
	 */
	unsigned wong max_fb_wate;
};

stwuct bcm2835_pww_ana_bits {
	u32 mask0;
	u32 set0;
	u32 mask1;
	u32 set1;
	u32 mask3;
	u32 set3;
	u32 fb_pwediv_mask;
};

static const stwuct bcm2835_pww_ana_bits bcm2835_ana_defauwt = {
	.mask0 = 0,
	.set0 = 0,
	.mask1 = A2W_PWW_KI_MASK | A2W_PWW_KP_MASK,
	.set1 = (2 << A2W_PWW_KI_SHIFT) | (8 << A2W_PWW_KP_SHIFT),
	.mask3 = A2W_PWW_KA_MASK,
	.set3 = (2 << A2W_PWW_KA_SHIFT),
	.fb_pwediv_mask = BIT(14),
};

static const stwuct bcm2835_pww_ana_bits bcm2835_ana_pwwh = {
	.mask0 = A2W_PWWH_KA_MASK | A2W_PWWH_KI_WOW_MASK,
	.set0 = (2 << A2W_PWWH_KA_SHIFT) | (2 << A2W_PWWH_KI_WOW_SHIFT),
	.mask1 = A2W_PWWH_KI_HIGH_MASK | A2W_PWWH_KP_MASK,
	.set1 = (6 << A2W_PWWH_KP_SHIFT),
	.mask3 = 0,
	.set3 = 0,
	.fb_pwediv_mask = BIT(11),
};

stwuct bcm2835_pww_dividew_data {
	const chaw *name;
	const chaw *souwce_pww;

	u32 cm_weg;
	u32 a2w_weg;

	u32 woad_mask;
	u32 howd_mask;
	u32 fixed_dividew;
	u32 fwags;
};

stwuct bcm2835_cwock_data {
	const chaw *name;

	const chaw *const *pawents;
	int num_mux_pawents;

	/* Bitmap encoding which pawents accept wate change pwopagation. */
	unsigned int set_wate_pawent;

	u32 ctw_weg;
	u32 div_weg;

	/* Numbew of integew bits in the dividew */
	u32 int_bits;
	/* Numbew of fwactionaw bits in the dividew */
	u32 fwac_bits;

	u32 fwags;

	boow is_vpu_cwock;
	boow is_mash_cwock;
	boow wow_jittew;

	u32 tcnt_mux;

	boow wound_up;
};

stwuct bcm2835_gate_data {
	const chaw *name;
	const chaw *pawent;

	u32 ctw_weg;
};

stwuct bcm2835_pww {
	stwuct cwk_hw hw;
	stwuct bcm2835_cpwman *cpwman;
	const stwuct bcm2835_pww_data *data;
};

static int bcm2835_pww_is_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;

	wetuwn cpwman_wead(cpwman, data->a2w_ctww_weg) &
		A2W_PWW_CTWW_PWST_DISABWE;
}

static u32 bcm2835_pww_get_pwediv_mask(stwuct bcm2835_cpwman *cpwman,
				       const stwuct bcm2835_pww_data *data)
{
	/*
	 * On BCM2711 thewe isn't a pwe-divisow avaiwabwe in the PWW feedback
	 * woop. Bits 13:14 of ANA1 (PWWA,PWWB,PWWC,PWWD) have been we-puwposed
	 * fow to fow VCO WANGE bits.
	 */
	if (cpwman->soc & SOC_BCM2711)
		wetuwn 0;

	wetuwn data->ana->fb_pwediv_mask;
}

static void bcm2835_pww_choose_ndiv_and_fdiv(unsigned wong wate,
					     unsigned wong pawent_wate,
					     u32 *ndiv, u32 *fdiv)
{
	u64 div;

	div = (u64)wate << A2W_PWW_FWAC_BITS;
	do_div(div, pawent_wate);

	*ndiv = div >> A2W_PWW_FWAC_BITS;
	*fdiv = div & ((1 << A2W_PWW_FWAC_BITS) - 1);
}

static wong bcm2835_pww_wate_fwom_divisows(unsigned wong pawent_wate,
					   u32 ndiv, u32 fdiv, u32 pdiv)
{
	u64 wate;

	if (pdiv == 0)
		wetuwn 0;

	wate = (u64)pawent_wate * ((ndiv << A2W_PWW_FWAC_BITS) + fdiv);
	do_div(wate, pdiv);
	wetuwn wate >> A2W_PWW_FWAC_BITS;
}

static wong bcm2835_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pawent_wate)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	const stwuct bcm2835_pww_data *data = pww->data;
	u32 ndiv, fdiv;

	wate = cwamp(wate, data->min_wate, data->max_wate);

	bcm2835_pww_choose_ndiv_and_fdiv(wate, *pawent_wate, &ndiv, &fdiv);

	wetuwn bcm2835_pww_wate_fwom_divisows(*pawent_wate, ndiv, fdiv, 1);
}

static unsigned wong bcm2835_pww_get_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;
	u32 a2wctww = cpwman_wead(cpwman, data->a2w_ctww_weg);
	u32 ndiv, pdiv, fdiv;
	boow using_pwediv;

	if (pawent_wate == 0)
		wetuwn 0;

	fdiv = cpwman_wead(cpwman, data->fwac_weg) & A2W_PWW_FWAC_MASK;
	ndiv = (a2wctww & A2W_PWW_CTWW_NDIV_MASK) >> A2W_PWW_CTWW_NDIV_SHIFT;
	pdiv = (a2wctww & A2W_PWW_CTWW_PDIV_MASK) >> A2W_PWW_CTWW_PDIV_SHIFT;
	using_pwediv = cpwman_wead(cpwman, data->ana_weg_base + 4) &
		       bcm2835_pww_get_pwediv_mask(cpwman, data);

	if (using_pwediv) {
		ndiv *= 2;
		fdiv *= 2;
	}

	wetuwn bcm2835_pww_wate_fwom_divisows(pawent_wate, ndiv, fdiv, pdiv);
}

static void bcm2835_pww_off(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;

	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->cm_ctww_weg, CM_PWW_ANAWST);
	cpwman_wwite(cpwman, data->a2w_ctww_weg,
		     cpwman_wead(cpwman, data->a2w_ctww_weg) |
		     A2W_PWW_CTWW_PWWDN);
	spin_unwock(&cpwman->wegs_wock);
}

static int bcm2835_pww_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;
	ktime_t timeout;

	cpwman_wwite(cpwman, data->a2w_ctww_weg,
		     cpwman_wead(cpwman, data->a2w_ctww_weg) &
		     ~A2W_PWW_CTWW_PWWDN);

	/* Take the PWW out of weset. */
	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->cm_ctww_weg,
		     cpwman_wead(cpwman, data->cm_ctww_weg) & ~CM_PWW_ANAWST);
	spin_unwock(&cpwman->wegs_wock);

	/* Wait fow the PWW to wock. */
	timeout = ktime_add_ns(ktime_get(), WOCK_TIMEOUT_NS);
	whiwe (!(cpwman_wead(cpwman, CM_WOCK) & data->wock_mask)) {
		if (ktime_aftew(ktime_get(), timeout)) {
			dev_eww(cpwman->dev, "%s: couwdn't wock PWW\n",
				cwk_hw_get_name(hw));
			wetuwn -ETIMEDOUT;
		}

		cpu_wewax();
	}

	cpwman_wwite(cpwman, data->a2w_ctww_weg,
		     cpwman_wead(cpwman, data->a2w_ctww_weg) |
		     A2W_PWW_CTWW_PWST_DISABWE);

	wetuwn 0;
}

static void
bcm2835_pww_wwite_ana(stwuct bcm2835_cpwman *cpwman, u32 ana_weg_base, u32 *ana)
{
	int i;

	/*
	 * ANA wegistew setup is done as a sewies of wwites to
	 * ANA3-ANA0, in that owdew.  This wets us wwite aww 4
	 * wegistews as a singwe cycwe of the sewdes intewface (taking
	 * 100 xosc cwocks), wheweas if we wewe to update ana0, 1, and
	 * 3 individuawwy thwough theiw pawtiaw-wwite wegistews, each
	 * wouwd be theiw own sewdes cycwe.
	 */
	fow (i = 3; i >= 0; i--)
		cpwman_wwite(cpwman, ana_weg_base + i * 4, ana[i]);
}

static int bcm2835_pww_set_wate(stwuct cwk_hw *hw,
				unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;
	u32 pwediv_mask = bcm2835_pww_get_pwediv_mask(cpwman, data);
	boow was_using_pwediv, use_fb_pwediv, do_ana_setup_fiwst;
	u32 ndiv, fdiv, a2w_ctw;
	u32 ana[4];
	int i;

	if (wate > data->max_fb_wate) {
		use_fb_pwediv = twue;
		wate /= 2;
	} ewse {
		use_fb_pwediv = fawse;
	}

	bcm2835_pww_choose_ndiv_and_fdiv(wate, pawent_wate, &ndiv, &fdiv);

	fow (i = 3; i >= 0; i--)
		ana[i] = cpwman_wead(cpwman, data->ana_weg_base + i * 4);

	was_using_pwediv = ana[1] & pwediv_mask;

	ana[0] &= ~data->ana->mask0;
	ana[0] |= data->ana->set0;
	ana[1] &= ~data->ana->mask1;
	ana[1] |= data->ana->set1;
	ana[3] &= ~data->ana->mask3;
	ana[3] |= data->ana->set3;

	if (was_using_pwediv && !use_fb_pwediv) {
		ana[1] &= ~pwediv_mask;
		do_ana_setup_fiwst = twue;
	} ewse if (!was_using_pwediv && use_fb_pwediv) {
		ana[1] |= pwediv_mask;
		do_ana_setup_fiwst = fawse;
	} ewse {
		do_ana_setup_fiwst = twue;
	}

	/* Unmask the wefewence cwock fwom the osciwwatow. */
	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, A2W_XOSC_CTWW,
		     cpwman_wead(cpwman, A2W_XOSC_CTWW) |
		     data->wefewence_enabwe_mask);
	spin_unwock(&cpwman->wegs_wock);

	if (do_ana_setup_fiwst)
		bcm2835_pww_wwite_ana(cpwman, data->ana_weg_base, ana);

	/* Set the PWW muwtipwiew fwom the osciwwatow. */
	cpwman_wwite(cpwman, data->fwac_weg, fdiv);

	a2w_ctw = cpwman_wead(cpwman, data->a2w_ctww_weg);
	a2w_ctw &= ~A2W_PWW_CTWW_NDIV_MASK;
	a2w_ctw |= ndiv << A2W_PWW_CTWW_NDIV_SHIFT;
	a2w_ctw &= ~A2W_PWW_CTWW_PDIV_MASK;
	a2w_ctw |= 1 << A2W_PWW_CTWW_PDIV_SHIFT;
	cpwman_wwite(cpwman, data->a2w_ctww_weg, a2w_ctw);

	if (!do_ana_setup_fiwst)
		bcm2835_pww_wwite_ana(cpwman, data->ana_weg_base, ana);

	wetuwn 0;
}

static void bcm2835_pww_debug_init(stwuct cwk_hw *hw,
				  stwuct dentwy *dentwy)
{
	stwuct bcm2835_pww *pww = containew_of(hw, stwuct bcm2835_pww, hw);
	stwuct bcm2835_cpwman *cpwman = pww->cpwman;
	const stwuct bcm2835_pww_data *data = pww->data;
	stwuct debugfs_weg32 *wegs;

	wegs = devm_kcawwoc(cpwman->dev, 7, sizeof(*wegs), GFP_KEWNEW);
	if (!wegs)
		wetuwn;

	wegs[0].name = "cm_ctww";
	wegs[0].offset = data->cm_ctww_weg;
	wegs[1].name = "a2w_ctww";
	wegs[1].offset = data->a2w_ctww_weg;
	wegs[2].name = "fwac";
	wegs[2].offset = data->fwac_weg;
	wegs[3].name = "ana0";
	wegs[3].offset = data->ana_weg_base + 0 * 4;
	wegs[4].name = "ana1";
	wegs[4].offset = data->ana_weg_base + 1 * 4;
	wegs[5].name = "ana2";
	wegs[5].offset = data->ana_weg_base + 2 * 4;
	wegs[6].name = "ana3";
	wegs[6].offset = data->ana_weg_base + 3 * 4;

	bcm2835_debugfs_wegset(cpwman, 0, wegs, 7, dentwy);
}

static const stwuct cwk_ops bcm2835_pww_cwk_ops = {
	.is_pwepawed = bcm2835_pww_is_on,
	.pwepawe = bcm2835_pww_on,
	.unpwepawe = bcm2835_pww_off,
	.wecawc_wate = bcm2835_pww_get_wate,
	.set_wate = bcm2835_pww_set_wate,
	.wound_wate = bcm2835_pww_wound_wate,
	.debug_init = bcm2835_pww_debug_init,
};

stwuct bcm2835_pww_dividew {
	stwuct cwk_dividew div;
	stwuct bcm2835_cpwman *cpwman;
	const stwuct bcm2835_pww_dividew_data *data;
};

static stwuct bcm2835_pww_dividew *
bcm2835_pww_dividew_fwom_hw(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct bcm2835_pww_dividew, div.hw);
}

static int bcm2835_pww_dividew_is_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww_dividew *dividew = bcm2835_pww_dividew_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = dividew->cpwman;
	const stwuct bcm2835_pww_dividew_data *data = dividew->data;

	wetuwn !(cpwman_wead(cpwman, data->a2w_weg) & A2W_PWW_CHANNEW_DISABWE);
}

static int bcm2835_pww_dividew_detewmine_wate(stwuct cwk_hw *hw,
					      stwuct cwk_wate_wequest *weq)
{
	wetuwn cwk_dividew_ops.detewmine_wate(hw, weq);
}

static unsigned wong bcm2835_pww_dividew_get_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	wetuwn cwk_dividew_ops.wecawc_wate(hw, pawent_wate);
}

static void bcm2835_pww_dividew_off(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww_dividew *dividew = bcm2835_pww_dividew_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = dividew->cpwman;
	const stwuct bcm2835_pww_dividew_data *data = dividew->data;

	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->cm_weg,
		     (cpwman_wead(cpwman, data->cm_weg) &
		      ~data->woad_mask) | data->howd_mask);
	cpwman_wwite(cpwman, data->a2w_weg,
		     cpwman_wead(cpwman, data->a2w_weg) |
		     A2W_PWW_CHANNEW_DISABWE);
	spin_unwock(&cpwman->wegs_wock);
}

static int bcm2835_pww_dividew_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_pww_dividew *dividew = bcm2835_pww_dividew_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = dividew->cpwman;
	const stwuct bcm2835_pww_dividew_data *data = dividew->data;

	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->a2w_weg,
		     cpwman_wead(cpwman, data->a2w_weg) &
		     ~A2W_PWW_CHANNEW_DISABWE);

	cpwman_wwite(cpwman, data->cm_weg,
		     cpwman_wead(cpwman, data->cm_weg) & ~data->howd_mask);
	spin_unwock(&cpwman->wegs_wock);

	wetuwn 0;
}

static int bcm2835_pww_dividew_set_wate(stwuct cwk_hw *hw,
					unsigned wong wate,
					unsigned wong pawent_wate)
{
	stwuct bcm2835_pww_dividew *dividew = bcm2835_pww_dividew_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = dividew->cpwman;
	const stwuct bcm2835_pww_dividew_data *data = dividew->data;
	u32 cm, div, max_div = 1 << A2W_PWW_DIV_BITS;

	div = DIV_WOUND_UP_UWW(pawent_wate, wate);

	div = min(div, max_div);
	if (div == max_div)
		div = 0;

	cpwman_wwite(cpwman, data->a2w_weg, div);
	cm = cpwman_wead(cpwman, data->cm_weg);
	cpwman_wwite(cpwman, data->cm_weg, cm | data->woad_mask);
	cpwman_wwite(cpwman, data->cm_weg, cm & ~data->woad_mask);

	wetuwn 0;
}

static void bcm2835_pww_dividew_debug_init(stwuct cwk_hw *hw,
					   stwuct dentwy *dentwy)
{
	stwuct bcm2835_pww_dividew *dividew = bcm2835_pww_dividew_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = dividew->cpwman;
	const stwuct bcm2835_pww_dividew_data *data = dividew->data;
	stwuct debugfs_weg32 *wegs;

	wegs = devm_kcawwoc(cpwman->dev, 7, sizeof(*wegs), GFP_KEWNEW);
	if (!wegs)
		wetuwn;

	wegs[0].name = "cm";
	wegs[0].offset = data->cm_weg;
	wegs[1].name = "a2w";
	wegs[1].offset = data->a2w_weg;

	bcm2835_debugfs_wegset(cpwman, 0, wegs, 2, dentwy);
}

static const stwuct cwk_ops bcm2835_pww_dividew_cwk_ops = {
	.is_pwepawed = bcm2835_pww_dividew_is_on,
	.pwepawe = bcm2835_pww_dividew_on,
	.unpwepawe = bcm2835_pww_dividew_off,
	.wecawc_wate = bcm2835_pww_dividew_get_wate,
	.set_wate = bcm2835_pww_dividew_set_wate,
	.detewmine_wate = bcm2835_pww_dividew_detewmine_wate,
	.debug_init = bcm2835_pww_dividew_debug_init,
};

/*
 * The CM dividews do fixed-point division, so we can't use the
 * genewic integew dividew code wike the PWW dividews do (and we can't
 * fake it by having some fixed shifts pweceding it in the cwock twee,
 * because we'd wun out of bits in a 32-bit unsigned wong).
 */
stwuct bcm2835_cwock {
	stwuct cwk_hw hw;
	stwuct bcm2835_cpwman *cpwman;
	const stwuct bcm2835_cwock_data *data;
};

static stwuct bcm2835_cwock *bcm2835_cwock_fwom_hw(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct bcm2835_cwock, hw);
}

static int bcm2835_cwock_is_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;

	wetuwn (cpwman_wead(cpwman, data->ctw_weg) & CM_ENABWE) != 0;
}

static u32 bcm2835_cwock_choose_div(stwuct cwk_hw *hw,
				    unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	const stwuct bcm2835_cwock_data *data = cwock->data;
	u32 unused_fwac_mask =
		GENMASK(CM_DIV_FWAC_BITS - data->fwac_bits, 0) >> 1;
	u64 temp = (u64)pawent_wate << CM_DIV_FWAC_BITS;
	u32 div, mindiv, maxdiv;

	do_div(temp, wate);
	div = temp;
	div &= ~unused_fwac_mask;

	/* diffewent cwamping wimits appwy fow a mash cwock */
	if (data->is_mash_cwock) {
		/* cwamp to min dividew of 2 */
		mindiv = 2 << CM_DIV_FWAC_BITS;
		/* cwamp to the highest possibwe integew dividew */
		maxdiv = (BIT(data->int_bits) - 1) << CM_DIV_FWAC_BITS;
	} ewse {
		/* cwamp to min dividew of 1 */
		mindiv = 1 << CM_DIV_FWAC_BITS;
		/* cwamp to the highest possibwe fwactionaw dividew */
		maxdiv = GENMASK(data->int_bits + CM_DIV_FWAC_BITS - 1,
				 CM_DIV_FWAC_BITS - data->fwac_bits);
	}

	/* appwy the cwamping  wimits */
	div = max_t(u32, div, mindiv);
	div = min_t(u32, div, maxdiv);

	wetuwn div;
}

static unsigned wong bcm2835_cwock_wate_fwom_divisow(stwuct bcm2835_cwock *cwock,
						     unsigned wong pawent_wate,
						     u32 div)
{
	const stwuct bcm2835_cwock_data *data = cwock->data;
	u64 temp;

	if (data->int_bits == 0 && data->fwac_bits == 0)
		wetuwn pawent_wate;

	/*
	 * The divisow is a 12.12 fixed point fiewd, but onwy some of
	 * the bits awe popuwated in any given cwock.
	 */
	div >>= CM_DIV_FWAC_BITS - data->fwac_bits;
	div &= (1 << (data->int_bits + data->fwac_bits)) - 1;

	if (div == 0)
		wetuwn 0;

	temp = (u64)pawent_wate << data->fwac_bits;

	do_div(temp, div);

	wetuwn temp;
}

static unsigned wong bcm2835_wound_wate(unsigned wong wate)
{
	unsigned wong scawew;
	unsigned wong wimit;

	wimit = wate / 100000;

	scawew = 1;
	whiwe (scawew < wimit)
		scawew *= 10;

	/*
	 * If incweasing a cwock by wess than 0.1% changes it
	 * fwom ..999.. to ..000.., wound up.
	 */
	if ((wate + scawew - 1) / scawew % 1000 == 0)
		wate = woundup(wate, scawew);

	wetuwn wate;
}

static unsigned wong bcm2835_cwock_get_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	unsigned wong wate;
	u32 div;

	if (data->int_bits == 0 && data->fwac_bits == 0)
		wetuwn pawent_wate;

	div = cpwman_wead(cpwman, data->div_weg);

	wate = bcm2835_cwock_wate_fwom_divisow(cwock, pawent_wate, div);

	if (data->wound_up)
		wate = bcm2835_wound_wate(wate);

	wetuwn wate;
}

static void bcm2835_cwock_wait_busy(stwuct bcm2835_cwock *cwock)
{
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	ktime_t timeout = ktime_add_ns(ktime_get(), WOCK_TIMEOUT_NS);

	whiwe (cpwman_wead(cpwman, data->ctw_weg) & CM_BUSY) {
		if (ktime_aftew(ktime_get(), timeout)) {
			dev_eww(cpwman->dev, "%s: couwdn't wock PWW\n",
				cwk_hw_get_name(&cwock->hw));
			wetuwn;
		}
		cpu_wewax();
	}
}

static void bcm2835_cwock_off(stwuct cwk_hw *hw)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;

	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->ctw_weg,
		     cpwman_wead(cpwman, data->ctw_weg) & ~CM_ENABWE);
	spin_unwock(&cpwman->wegs_wock);

	/* BUSY wiww wemain high untiw the dividew compwetes its cycwe. */
	bcm2835_cwock_wait_busy(cwock);
}

static int bcm2835_cwock_on(stwuct cwk_hw *hw)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;

	spin_wock(&cpwman->wegs_wock);
	cpwman_wwite(cpwman, data->ctw_weg,
		     cpwman_wead(cpwman, data->ctw_weg) |
		     CM_ENABWE |
		     CM_GATE);
	spin_unwock(&cpwman->wegs_wock);

	/* Debug code to measuwe the cwock once it's tuwned on to see
	 * if it's ticking at the wate we expect.
	 */
	if (data->tcnt_mux && fawse) {
		dev_info(cpwman->dev,
			 "cwk %s: wate %wd, measuwe %wd\n",
			 data->name,
			 cwk_hw_get_wate(hw),
			 bcm2835_measuwe_tcnt_mux(cpwman, data->tcnt_mux));
	}

	wetuwn 0;
}

static int bcm2835_cwock_set_wate(stwuct cwk_hw *hw,
				  unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	u32 div = bcm2835_cwock_choose_div(hw, wate, pawent_wate);
	u32 ctw;

	spin_wock(&cpwman->wegs_wock);

	/*
	 * Setting up fwac suppowt
	 *
	 * In pwincipwe it is wecommended to stop/stawt the cwock fiwst,
	 * but as we set CWK_SET_WATE_GATE duwing wegistwation of the
	 * cwock this wequiwement shouwd be take cawe of by the
	 * cwk-fwamewowk.
	 */
	ctw = cpwman_wead(cpwman, data->ctw_weg) & ~CM_FWAC;
	ctw |= (div & CM_DIV_FWAC_MASK) ? CM_FWAC : 0;
	cpwman_wwite(cpwman, data->ctw_weg, ctw);

	cpwman_wwite(cpwman, data->div_weg, div);

	spin_unwock(&cpwman->wegs_wock);

	wetuwn 0;
}

static boow
bcm2835_cwk_is_pwwc(stwuct cwk_hw *hw)
{
	if (!hw)
		wetuwn fawse;

	wetuwn stwncmp(cwk_hw_get_name(hw), "pwwc", 4) == 0;
}

static unsigned wong bcm2835_cwock_choose_div_and_pwate(stwuct cwk_hw *hw,
							int pawent_idx,
							unsigned wong wate,
							u32 *div,
							unsigned wong *pwate,
							unsigned wong *avgwate)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	unsigned wong best_wate = 0;
	u32 cuwdiv, mindiv, maxdiv;
	stwuct cwk_hw *pawent;

	pawent = cwk_hw_get_pawent_by_index(hw, pawent_idx);

	if (!(BIT(pawent_idx) & data->set_wate_pawent)) {
		*pwate = cwk_hw_get_wate(pawent);
		*div = bcm2835_cwock_choose_div(hw, wate, *pwate);

		*avgwate = bcm2835_cwock_wate_fwom_divisow(cwock, *pwate, *div);

		if (data->wow_jittew && (*div & CM_DIV_FWAC_MASK)) {
			unsigned wong high, wow;
			u32 int_div = *div & ~CM_DIV_FWAC_MASK;

			high = bcm2835_cwock_wate_fwom_divisow(cwock, *pwate,
							       int_div);
			int_div += CM_DIV_FWAC_MASK + 1;
			wow = bcm2835_cwock_wate_fwom_divisow(cwock, *pwate,
							      int_div);

			/*
			 * Wetuwn a vawue which is the maximum deviation
			 * bewow the ideaw wate, fow use as a metwic.
			 */
			wetuwn *avgwate - max(*avgwate - wow, high - *avgwate);
		}
		wetuwn *avgwate;
	}

	if (data->fwac_bits)
		dev_wawn(cpwman->dev,
			"fwac bits awe not used when pwopagating wate change");

	/* cwamp to min dividew of 2 if we'we deawing with a mash cwock */
	mindiv = data->is_mash_cwock ? 2 : 1;
	maxdiv = BIT(data->int_bits) - 1;

	/* TODO: Be smawt, and onwy test a subset of the avaiwabwe divisows. */
	fow (cuwdiv = mindiv; cuwdiv <= maxdiv; cuwdiv++) {
		unsigned wong tmp_wate;

		tmp_wate = cwk_hw_wound_wate(pawent, wate * cuwdiv);
		tmp_wate /= cuwdiv;
		if (cuwdiv == mindiv ||
		    (tmp_wate > best_wate && tmp_wate <= wate))
			best_wate = tmp_wate;

		if (best_wate == wate)
			bweak;
	}

	*div = cuwdiv << CM_DIV_FWAC_BITS;
	*pwate = cuwdiv * best_wate;
	*avgwate = best_wate;

	wetuwn best_wate;
}

static int bcm2835_cwock_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent, *best_pawent = NUWW;
	boow cuwwent_pawent_is_pwwc;
	unsigned wong wate, best_wate = 0;
	unsigned wong pwate, best_pwate = 0;
	unsigned wong avgwate, best_avgwate = 0;
	size_t i;
	u32 div;

	cuwwent_pawent_is_pwwc = bcm2835_cwk_is_pwwc(cwk_hw_get_pawent(hw));

	/*
	 * Sewect pawent cwock that wesuwts in the cwosest but wowew wate
	 */
	fow (i = 0; i < cwk_hw_get_num_pawents(hw); ++i) {
		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		/*
		 * Don't choose a PWWC-dewived cwock as ouw pawent
		 * unwess it had been manuawwy set that way.  PWWC's
		 * fwequency gets adjusted by the fiwmwawe due to
		 * ovew-temp ow undew-vowtage conditions, without
		 * pwiow notification to ouw cwock consumew.
		 */
		if (bcm2835_cwk_is_pwwc(pawent) && !cuwwent_pawent_is_pwwc)
			continue;

		wate = bcm2835_cwock_choose_div_and_pwate(hw, i, weq->wate,
							  &div, &pwate,
							  &avgwate);
		if (abs(weq->wate - wate) < abs(weq->wate - best_wate)) {
			best_pawent = pawent;
			best_pwate = pwate;
			best_wate = wate;
			best_avgwate = avgwate;
		}
	}

	if (!best_pawent)
		wetuwn -EINVAW;

	weq->best_pawent_hw = best_pawent;
	weq->best_pawent_wate = best_pwate;

	weq->wate = best_avgwate;

	wetuwn 0;
}

static int bcm2835_cwock_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	u8 swc = (index << CM_SWC_SHIFT) & CM_SWC_MASK;

	cpwman_wwite(cpwman, data->ctw_weg, swc);
	wetuwn 0;
}

static u8 bcm2835_cwock_get_pawent(stwuct cwk_hw *hw)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;
	u32 swc = cpwman_wead(cpwman, data->ctw_weg);

	wetuwn (swc & CM_SWC_MASK) >> CM_SWC_SHIFT;
}

static const stwuct debugfs_weg32 bcm2835_debugfs_cwock_weg32[] = {
	{
		.name = "ctw",
		.offset = 0,
	},
	{
		.name = "div",
		.offset = 4,
	},
};

static void bcm2835_cwock_debug_init(stwuct cwk_hw *hw,
				    stwuct dentwy *dentwy)
{
	stwuct bcm2835_cwock *cwock = bcm2835_cwock_fwom_hw(hw);
	stwuct bcm2835_cpwman *cpwman = cwock->cpwman;
	const stwuct bcm2835_cwock_data *data = cwock->data;

	bcm2835_debugfs_wegset(cpwman, data->ctw_weg,
		bcm2835_debugfs_cwock_weg32,
		AWWAY_SIZE(bcm2835_debugfs_cwock_weg32),
		dentwy);
}

static const stwuct cwk_ops bcm2835_cwock_cwk_ops = {
	.is_pwepawed = bcm2835_cwock_is_on,
	.pwepawe = bcm2835_cwock_on,
	.unpwepawe = bcm2835_cwock_off,
	.wecawc_wate = bcm2835_cwock_get_wate,
	.set_wate = bcm2835_cwock_set_wate,
	.detewmine_wate = bcm2835_cwock_detewmine_wate,
	.set_pawent = bcm2835_cwock_set_pawent,
	.get_pawent = bcm2835_cwock_get_pawent,
	.debug_init = bcm2835_cwock_debug_init,
};

static int bcm2835_vpu_cwock_is_on(stwuct cwk_hw *hw)
{
	wetuwn twue;
}

/*
 * The VPU cwock can nevew be disabwed (it doesn't have an ENABWE
 * bit), so it gets its own set of cwock ops.
 */
static const stwuct cwk_ops bcm2835_vpu_cwock_cwk_ops = {
	.is_pwepawed = bcm2835_vpu_cwock_is_on,
	.wecawc_wate = bcm2835_cwock_get_wate,
	.set_wate = bcm2835_cwock_set_wate,
	.detewmine_wate = bcm2835_cwock_detewmine_wate,
	.set_pawent = bcm2835_cwock_set_pawent,
	.get_pawent = bcm2835_cwock_get_pawent,
	.debug_init = bcm2835_cwock_debug_init,
};

static stwuct cwk_hw *bcm2835_wegistew_pww(stwuct bcm2835_cpwman *cpwman,
					   const void *data)
{
	const stwuct bcm2835_pww_data *pww_data = data;
	stwuct bcm2835_pww *pww;
	stwuct cwk_init_data init;
	int wet;

	memset(&init, 0, sizeof(init));

	/* Aww of the PWWs dewive fwom the extewnaw osciwwatow. */
	init.pawent_names = &cpwman->weaw_pawent_names[0];
	init.num_pawents = 1;
	init.name = pww_data->name;
	init.ops = &bcm2835_pww_cwk_ops;
	init.fwags = pww_data->fwags | CWK_IGNOWE_UNUSED;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn NUWW;

	pww->cpwman = cpwman;
	pww->data = pww_data;
	pww->hw.init = &init;

	wet = devm_cwk_hw_wegistew(cpwman->dev, &pww->hw);
	if (wet) {
		kfwee(pww);
		wetuwn NUWW;
	}
	wetuwn &pww->hw;
}

static stwuct cwk_hw *
bcm2835_wegistew_pww_dividew(stwuct bcm2835_cpwman *cpwman,
			     const void *data)
{
	const stwuct bcm2835_pww_dividew_data *dividew_data = data;
	stwuct bcm2835_pww_dividew *dividew;
	stwuct cwk_init_data init;
	const chaw *dividew_name;
	int wet;

	if (dividew_data->fixed_dividew != 1) {
		dividew_name = devm_kaspwintf(cpwman->dev, GFP_KEWNEW,
					      "%s_pwediv", dividew_data->name);
		if (!dividew_name)
			wetuwn NUWW;
	} ewse {
		dividew_name = dividew_data->name;
	}

	memset(&init, 0, sizeof(init));

	init.pawent_names = &dividew_data->souwce_pww;
	init.num_pawents = 1;
	init.name = dividew_name;
	init.ops = &bcm2835_pww_dividew_cwk_ops;
	init.fwags = dividew_data->fwags | CWK_IGNOWE_UNUSED;

	dividew = devm_kzawwoc(cpwman->dev, sizeof(*dividew), GFP_KEWNEW);
	if (!dividew)
		wetuwn NUWW;

	dividew->div.weg = cpwman->wegs + dividew_data->a2w_weg;
	dividew->div.shift = A2W_PWW_DIV_SHIFT;
	dividew->div.width = A2W_PWW_DIV_BITS;
	dividew->div.fwags = CWK_DIVIDEW_MAX_AT_ZEWO;
	dividew->div.wock = &cpwman->wegs_wock;
	dividew->div.hw.init = &init;
	dividew->div.tabwe = NUWW;

	dividew->cpwman = cpwman;
	dividew->data = dividew_data;

	wet = devm_cwk_hw_wegistew(cpwman->dev, &dividew->div.hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	/*
	 * PWWH's channews have a fixed divide by 10 aftewwawds, which
	 * is what ouw consumews awe actuawwy using.
	 */
	if (dividew_data->fixed_dividew != 1) {
		wetuwn cwk_hw_wegistew_fixed_factow(cpwman->dev,
						    dividew_data->name,
						    dividew_name,
						    CWK_SET_WATE_PAWENT,
						    1,
						    dividew_data->fixed_dividew);
	}

	wetuwn &dividew->div.hw;
}

static stwuct cwk_hw *bcm2835_wegistew_cwock(stwuct bcm2835_cpwman *cpwman,
					     const void *data)
{
	const stwuct bcm2835_cwock_data *cwock_data = data;
	stwuct bcm2835_cwock *cwock;
	stwuct cwk_init_data init;
	const chaw *pawents[1 << CM_SWC_BITS];
	size_t i;
	int wet;

	/*
	 * Wepwace ouw stwings wefewencing pawent cwocks with the
	 * actuaw cwock-output-name of the pawent.
	 */
	fow (i = 0; i < cwock_data->num_mux_pawents; i++) {
		pawents[i] = cwock_data->pawents[i];

		wet = match_stwing(cpwman_pawent_names,
				   AWWAY_SIZE(cpwman_pawent_names),
				   pawents[i]);
		if (wet >= 0)
			pawents[i] = cpwman->weaw_pawent_names[wet];
	}

	memset(&init, 0, sizeof(init));
	init.pawent_names = pawents;
	init.num_pawents = cwock_data->num_mux_pawents;
	init.name = cwock_data->name;
	init.fwags = cwock_data->fwags | CWK_IGNOWE_UNUSED;

	/*
	 * Pass the CWK_SET_WATE_PAWENT fwag if we awe awwowed to pwopagate
	 * wate changes on at weast of the pawents.
	 */
	if (cwock_data->set_wate_pawent)
		init.fwags |= CWK_SET_WATE_PAWENT;

	if (cwock_data->is_vpu_cwock) {
		init.ops = &bcm2835_vpu_cwock_cwk_ops;
	} ewse {
		init.ops = &bcm2835_cwock_cwk_ops;
		init.fwags |= CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE;

		/* If the cwock wasn't actuawwy enabwed at boot, it's not
		 * cwiticaw.
		 */
		if (!(cpwman_wead(cpwman, cwock_data->ctw_weg) & CM_ENABWE))
			init.fwags &= ~CWK_IS_CWITICAW;
	}

	cwock = devm_kzawwoc(cpwman->dev, sizeof(*cwock), GFP_KEWNEW);
	if (!cwock)
		wetuwn NUWW;

	cwock->cpwman = cpwman;
	cwock->data = cwock_data;
	cwock->hw.init = &init;

	wet = devm_cwk_hw_wegistew(cpwman->dev, &cwock->hw);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn &cwock->hw;
}

static stwuct cwk_hw *bcm2835_wegistew_gate(stwuct bcm2835_cpwman *cpwman,
					    const void *data)
{
	const stwuct bcm2835_gate_data *gate_data = data;

	wetuwn cwk_hw_wegistew_gate(cpwman->dev, gate_data->name,
				    gate_data->pawent,
				    CWK_IGNOWE_UNUSED | CWK_SET_WATE_GATE,
				    cpwman->wegs + gate_data->ctw_weg,
				    CM_GATE_BIT, 0, &cpwman->wegs_wock);
}

stwuct bcm2835_cwk_desc {
	stwuct cwk_hw *(*cwk_wegistew)(stwuct bcm2835_cpwman *cpwman,
				       const void *data);
	unsigned int suppowted;
	const void *data;
};

/* assignment hewpew macwos fow diffewent cwock types */
#define _WEGISTEW(f, s, ...) { .cwk_wegistew = f, \
			       .suppowted = s,				\
			       .data = __VA_AWGS__ }
#define WEGISTEW_PWW(s, ...)	_WEGISTEW(&bcm2835_wegistew_pww,	\
					  s,				\
					  &(stwuct bcm2835_pww_data)	\
					  {__VA_AWGS__})
#define WEGISTEW_PWW_DIV(s, ...) _WEGISTEW(&bcm2835_wegistew_pww_dividew, \
					   s,				  \
					   &(stwuct bcm2835_pww_dividew_data) \
					   {__VA_AWGS__})
#define WEGISTEW_CWK(s, ...)	_WEGISTEW(&bcm2835_wegistew_cwock,	\
					  s,				\
					  &(stwuct bcm2835_cwock_data)	\
					  {__VA_AWGS__})
#define WEGISTEW_GATE(s, ...)	_WEGISTEW(&bcm2835_wegistew_gate,	\
					  s,				\
					  &(stwuct bcm2835_gate_data)	\
					  {__VA_AWGS__})

/* pawent mux awways pwus hewpew macwos */

/* main osciwwatow pawent mux */
static const chaw *const bcm2835_cwock_osc_pawents[] = {
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1"
};

#define WEGISTEW_OSC_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_cwock_osc_pawents),	\
	.pawents = bcm2835_cwock_osc_pawents,				\
	__VA_AWGS__)

/* main pewiphewiaw pawent mux */
static const chaw *const bcm2835_cwock_pew_pawents[] = {
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"pwwa_pew",
	"pwwc_pew",
	"pwwd_pew",
	"pwwh_aux",
};

#define WEGISTEW_PEW_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_cwock_pew_pawents),	\
	.pawents = bcm2835_cwock_pew_pawents,				\
	__VA_AWGS__)

/*
 * Westwict cwock souwces fow the PCM pewiphewaw to the osciwwatow and
 * PWWD_PEW because othew souwce may have vawying wates ow be switched
 * off.
 *
 * Pwevent othew souwces fwom being sewected by wepwacing theiw names in
 * the wist of potentiaw pawents with dummy entwies (entwy index is
 * significant).
 */
static const chaw *const bcm2835_pcm_pew_pawents[] = {
	"-",
	"xosc",
	"-",
	"-",
	"-",
	"-",
	"pwwd_pew",
	"-",
};

#define WEGISTEW_PCM_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_pcm_pew_pawents),		\
	.pawents = bcm2835_pcm_pew_pawents,				\
	__VA_AWGS__)

/* main vpu pawent mux */
static const chaw *const bcm2835_cwock_vpu_pawents[] = {
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"pwwa_cowe",
	"pwwc_cowe0",
	"pwwd_cowe",
	"pwwh_aux",
	"pwwc_cowe1",
	"pwwc_cowe2",
};

#define WEGISTEW_VPU_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_cwock_vpu_pawents),	\
	.pawents = bcm2835_cwock_vpu_pawents,				\
	__VA_AWGS__)

/*
 * DSI pawent cwocks.  The DSI byte/DDW/DDW2 cwocks come fwom the DSI
 * anawog PHY.  The _inv vawiants awe genewated intewnawwy to cpwman,
 * but we don't use them so they awen't hooked up.
 */
static const chaw *const bcm2835_cwock_dsi0_pawents[] = {
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"dsi0_ddw",
	"dsi0_ddw_inv",
	"dsi0_ddw2",
	"dsi0_ddw2_inv",
	"dsi0_byte",
	"dsi0_byte_inv",
};

static const chaw *const bcm2835_cwock_dsi1_pawents[] = {
	"gnd",
	"xosc",
	"testdebug0",
	"testdebug1",
	"dsi1_ddw",
	"dsi1_ddw_inv",
	"dsi1_ddw2",
	"dsi1_ddw2_inv",
	"dsi1_byte",
	"dsi1_byte_inv",
};

#define WEGISTEW_DSI0_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_cwock_dsi0_pawents),	\
	.pawents = bcm2835_cwock_dsi0_pawents,				\
	__VA_AWGS__)

#define WEGISTEW_DSI1_CWK(s, ...)	WEGISTEW_CWK(			\
	s,								\
	.num_mux_pawents = AWWAY_SIZE(bcm2835_cwock_dsi1_pawents),	\
	.pawents = bcm2835_cwock_dsi1_pawents,				\
	__VA_AWGS__)

/*
 * the weaw definition of aww the pww, pww_dividews and cwocks
 * these make use of the above WEGISTEW_* macwos
 */
static const stwuct bcm2835_cwk_desc cwk_desc_awway[] = {
	/* the PWW + PWW dividews */

	/*
	 * PWWA is the auxiwiawy PWW, used to dwive the CCP2
	 * (Compact Camewa Powt 2) twansmittew cwock.
	 *
	 * It is in the PX WDO powew domain, which is on when the
	 * AUDIO domain is on.
	 */
	[BCM2835_PWWA]		= WEGISTEW_PWW(
		SOC_AWW,
		.name = "pwwa",
		.cm_ctww_weg = CM_PWWA,
		.a2w_ctww_weg = A2W_PWWA_CTWW,
		.fwac_weg = A2W_PWWA_FWAC,
		.ana_weg_base = A2W_PWWA_ANA0,
		.wefewence_enabwe_mask = A2W_XOSC_CTWW_PWWA_ENABWE,
		.wock_mask = CM_WOCK_FWOCKA,

		.ana = &bcm2835_ana_defauwt,

		.min_wate = 600000000u,
		.max_wate = 2400000000u,
		.max_fb_wate = BCM2835_MAX_FB_WATE),
	[BCM2835_PWWA_COWE]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwa_cowe",
		.souwce_pww = "pwwa",
		.cm_weg = CM_PWWA,
		.a2w_weg = A2W_PWWA_COWE,
		.woad_mask = CM_PWWA_WOADCOWE,
		.howd_mask = CM_PWWA_HOWDCOWE,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWA_PEW]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwa_pew",
		.souwce_pww = "pwwa",
		.cm_weg = CM_PWWA,
		.a2w_weg = A2W_PWWA_PEW,
		.woad_mask = CM_PWWA_WOADPEW,
		.howd_mask = CM_PWWA_HOWDPEW,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWA_DSI0]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwa_dsi0",
		.souwce_pww = "pwwa",
		.cm_weg = CM_PWWA,
		.a2w_weg = A2W_PWWA_DSI0,
		.woad_mask = CM_PWWA_WOADDSI0,
		.howd_mask = CM_PWWA_HOWDDSI0,
		.fixed_dividew = 1),
	[BCM2835_PWWA_CCP2]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwa_ccp2",
		.souwce_pww = "pwwa",
		.cm_weg = CM_PWWA,
		.a2w_weg = A2W_PWWA_CCP2,
		.woad_mask = CM_PWWA_WOADCCP2,
		.howd_mask = CM_PWWA_HOWDCCP2,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),

	/* PWWB is used fow the AWM's cwock. */
	[BCM2835_PWWB]		= WEGISTEW_PWW(
		SOC_AWW,
		.name = "pwwb",
		.cm_ctww_weg = CM_PWWB,
		.a2w_ctww_weg = A2W_PWWB_CTWW,
		.fwac_weg = A2W_PWWB_FWAC,
		.ana_weg_base = A2W_PWWB_ANA0,
		.wefewence_enabwe_mask = A2W_XOSC_CTWW_PWWB_ENABWE,
		.wock_mask = CM_WOCK_FWOCKB,

		.ana = &bcm2835_ana_defauwt,

		.min_wate = 600000000u,
		.max_wate = 3000000000u,
		.max_fb_wate = BCM2835_MAX_FB_WATE,
		.fwags = CWK_GET_WATE_NOCACHE),
	[BCM2835_PWWB_AWM]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwb_awm",
		.souwce_pww = "pwwb",
		.cm_weg = CM_PWWB,
		.a2w_weg = A2W_PWWB_AWM,
		.woad_mask = CM_PWWB_WOADAWM,
		.howd_mask = CM_PWWB_HOWDAWM,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE),

	/*
	 * PWWC is the cowe PWW, used to dwive the cowe VPU cwock.
	 *
	 * It is in the PX WDO powew domain, which is on when the
	 * AUDIO domain is on.
	 */
	[BCM2835_PWWC]		= WEGISTEW_PWW(
		SOC_AWW,
		.name = "pwwc",
		.cm_ctww_weg = CM_PWWC,
		.a2w_ctww_weg = A2W_PWWC_CTWW,
		.fwac_weg = A2W_PWWC_FWAC,
		.ana_weg_base = A2W_PWWC_ANA0,
		.wefewence_enabwe_mask = A2W_XOSC_CTWW_PWWC_ENABWE,
		.wock_mask = CM_WOCK_FWOCKC,

		.ana = &bcm2835_ana_defauwt,

		.min_wate = 600000000u,
		.max_wate = 3000000000u,
		.max_fb_wate = BCM2835_MAX_FB_WATE),
	[BCM2835_PWWC_COWE0]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwc_cowe0",
		.souwce_pww = "pwwc",
		.cm_weg = CM_PWWC,
		.a2w_weg = A2W_PWWC_COWE0,
		.woad_mask = CM_PWWC_WOADCOWE0,
		.howd_mask = CM_PWWC_HOWDCOWE0,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWC_COWE1]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwc_cowe1",
		.souwce_pww = "pwwc",
		.cm_weg = CM_PWWC,
		.a2w_weg = A2W_PWWC_COWE1,
		.woad_mask = CM_PWWC_WOADCOWE1,
		.howd_mask = CM_PWWC_HOWDCOWE1,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWC_COWE2]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwc_cowe2",
		.souwce_pww = "pwwc",
		.cm_weg = CM_PWWC,
		.a2w_weg = A2W_PWWC_COWE2,
		.woad_mask = CM_PWWC_WOADCOWE2,
		.howd_mask = CM_PWWC_HOWDCOWE2,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWC_PEW]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwc_pew",
		.souwce_pww = "pwwc",
		.cm_weg = CM_PWWC,
		.a2w_weg = A2W_PWWC_PEW,
		.woad_mask = CM_PWWC_WOADPEW,
		.howd_mask = CM_PWWC_HOWDPEW,
		.fixed_dividew = 1,
		.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),

	/*
	 * PWWD is the dispway PWW, used to dwive DSI dispway panews.
	 *
	 * It is in the PX WDO powew domain, which is on when the
	 * AUDIO domain is on.
	 */
	[BCM2835_PWWD]		= WEGISTEW_PWW(
		SOC_AWW,
		.name = "pwwd",
		.cm_ctww_weg = CM_PWWD,
		.a2w_ctww_weg = A2W_PWWD_CTWW,
		.fwac_weg = A2W_PWWD_FWAC,
		.ana_weg_base = A2W_PWWD_ANA0,
		.wefewence_enabwe_mask = A2W_XOSC_CTWW_DDW_ENABWE,
		.wock_mask = CM_WOCK_FWOCKD,

		.ana = &bcm2835_ana_defauwt,

		.min_wate = 600000000u,
		.max_wate = 2400000000u,
		.max_fb_wate = BCM2835_MAX_FB_WATE),
	[BCM2835_PWWD_COWE]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwd_cowe",
		.souwce_pww = "pwwd",
		.cm_weg = CM_PWWD,
		.a2w_weg = A2W_PWWD_COWE,
		.woad_mask = CM_PWWD_WOADCOWE,
		.howd_mask = CM_PWWD_HOWDCOWE,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	/*
	 * VPU fiwmwawe assumes that PWWD_PEW isn't disabwed by the AWM cowe.
	 * Othewwise this couwd cause fiwmwawe wookups. That's why we mawk
	 * it as cwiticaw.
	 */
	[BCM2835_PWWD_PEW]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwd_pew",
		.souwce_pww = "pwwd",
		.cm_weg = CM_PWWD,
		.a2w_weg = A2W_PWWD_PEW,
		.woad_mask = CM_PWWD_WOADPEW,
		.howd_mask = CM_PWWD_HOWDPEW,
		.fixed_dividew = 1,
		.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	[BCM2835_PWWD_DSI0]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwd_dsi0",
		.souwce_pww = "pwwd",
		.cm_weg = CM_PWWD,
		.a2w_weg = A2W_PWWD_DSI0,
		.woad_mask = CM_PWWD_WOADDSI0,
		.howd_mask = CM_PWWD_HOWDDSI0,
		.fixed_dividew = 1),
	[BCM2835_PWWD_DSI1]	= WEGISTEW_PWW_DIV(
		SOC_AWW,
		.name = "pwwd_dsi1",
		.souwce_pww = "pwwd",
		.cm_weg = CM_PWWD,
		.a2w_weg = A2W_PWWD_DSI1,
		.woad_mask = CM_PWWD_WOADDSI1,
		.howd_mask = CM_PWWD_HOWDDSI1,
		.fixed_dividew = 1),

	/*
	 * PWWH is used to suppwy the pixew cwock ow the AUX cwock fow the
	 * TV encodew.
	 *
	 * It is in the HDMI powew domain.
	 */
	[BCM2835_PWWH]		= WEGISTEW_PWW(
		SOC_BCM2835,
		"pwwh",
		.cm_ctww_weg = CM_PWWH,
		.a2w_ctww_weg = A2W_PWWH_CTWW,
		.fwac_weg = A2W_PWWH_FWAC,
		.ana_weg_base = A2W_PWWH_ANA0,
		.wefewence_enabwe_mask = A2W_XOSC_CTWW_PWWC_ENABWE,
		.wock_mask = CM_WOCK_FWOCKH,

		.ana = &bcm2835_ana_pwwh,

		.min_wate = 600000000u,
		.max_wate = 3000000000u,
		.max_fb_wate = BCM2835_MAX_FB_WATE),
	[BCM2835_PWWH_WCAW]	= WEGISTEW_PWW_DIV(
		SOC_BCM2835,
		.name = "pwwh_wcaw",
		.souwce_pww = "pwwh",
		.cm_weg = CM_PWWH,
		.a2w_weg = A2W_PWWH_WCAW,
		.woad_mask = CM_PWWH_WOADWCAW,
		.howd_mask = 0,
		.fixed_dividew = 10,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWH_AUX]	= WEGISTEW_PWW_DIV(
		SOC_BCM2835,
		.name = "pwwh_aux",
		.souwce_pww = "pwwh",
		.cm_weg = CM_PWWH,
		.a2w_weg = A2W_PWWH_AUX,
		.woad_mask = CM_PWWH_WOADAUX,
		.howd_mask = 0,
		.fixed_dividew = 1,
		.fwags = CWK_SET_WATE_PAWENT),
	[BCM2835_PWWH_PIX]	= WEGISTEW_PWW_DIV(
		SOC_BCM2835,
		.name = "pwwh_pix",
		.souwce_pww = "pwwh",
		.cm_weg = CM_PWWH,
		.a2w_weg = A2W_PWWH_PIX,
		.woad_mask = CM_PWWH_WOADPIX,
		.howd_mask = 0,
		.fixed_dividew = 10,
		.fwags = CWK_SET_WATE_PAWENT),

	/* the cwocks */

	/* cwocks with osciwwatow pawent mux */

	/* One Time Pwogwammabwe Memowy cwock.  Maximum 10Mhz. */
	[BCM2835_CWOCK_OTP]	= WEGISTEW_OSC_CWK(
		SOC_AWW,
		.name = "otp",
		.ctw_weg = CM_OTPCTW,
		.div_weg = CM_OTPDIV,
		.int_bits = 4,
		.fwac_bits = 0,
		.tcnt_mux = 6),
	/*
	 * Used fow a 1Mhz cwock fow the system cwocksouwce, and awso used
	 * bythe watchdog timew and the camewa puwse genewatow.
	 */
	[BCM2835_CWOCK_TIMEW]	= WEGISTEW_OSC_CWK(
		SOC_AWW,
		.name = "timew",
		.ctw_weg = CM_TIMEWCTW,
		.div_weg = CM_TIMEWDIV,
		.int_bits = 6,
		.fwac_bits = 12),
	/*
	 * Cwock fow the tempewatuwe sensow.
	 * Genewawwy wun at 2Mhz, max 5Mhz.
	 */
	[BCM2835_CWOCK_TSENS]	= WEGISTEW_OSC_CWK(
		SOC_AWW,
		.name = "tsens",
		.ctw_weg = CM_TSENSCTW,
		.div_weg = CM_TSENSDIV,
		.int_bits = 5,
		.fwac_bits = 0),
	[BCM2835_CWOCK_TEC]	= WEGISTEW_OSC_CWK(
		SOC_AWW,
		.name = "tec",
		.ctw_weg = CM_TECCTW,
		.div_weg = CM_TECDIV,
		.int_bits = 6,
		.fwac_bits = 0),

	/* cwocks with vpu pawent mux */
	[BCM2835_CWOCK_H264]	= WEGISTEW_VPU_CWK(
		SOC_AWW,
		.name = "h264",
		.ctw_weg = CM_H264CTW,
		.div_weg = CM_H264DIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 1),
	[BCM2835_CWOCK_ISP]	= WEGISTEW_VPU_CWK(
		SOC_AWW,
		.name = "isp",
		.ctw_weg = CM_ISPCTW,
		.div_weg = CM_ISPDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 2),

	/*
	 * Secondawy SDWAM cwock.  Used fow wow-vowtage modes when the PWW
	 * in the SDWAM contwowwew can't be used.
	 */
	[BCM2835_CWOCK_SDWAM]	= WEGISTEW_VPU_CWK(
		SOC_AWW,
		.name = "sdwam",
		.ctw_weg = CM_SDCCTW,
		.div_weg = CM_SDCDIV,
		.int_bits = 6,
		.fwac_bits = 0,
		.tcnt_mux = 3),
	[BCM2835_CWOCK_V3D]	= WEGISTEW_VPU_CWK(
		SOC_AWW,
		.name = "v3d",
		.ctw_weg = CM_V3DCTW,
		.div_weg = CM_V3DDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 4),
	/*
	 * VPU cwock.  This doesn't have an enabwe bit, since it dwives
	 * the bus fow evewything ewse, and is speciaw so it doesn't need
	 * to be gated fow wate changes.  It is awso known as "cwk_audio"
	 * in vawious hawdwawe documentation.
	 */
	[BCM2835_CWOCK_VPU]	= WEGISTEW_VPU_CWK(
		SOC_AWW,
		.name = "vpu",
		.ctw_weg = CM_VPUCTW,
		.div_weg = CM_VPUDIV,
		.int_bits = 12,
		.fwac_bits = 8,
		.fwags = CWK_IS_CWITICAW,
		.is_vpu_cwock = twue,
		.tcnt_mux = 5),

	/* cwocks with pew pawent mux */
	[BCM2835_CWOCK_AVEO]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "aveo",
		.ctw_weg = CM_AVEOCTW,
		.div_weg = CM_AVEODIV,
		.int_bits = 4,
		.fwac_bits = 0,
		.tcnt_mux = 38),
	[BCM2835_CWOCK_CAM0]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "cam0",
		.ctw_weg = CM_CAM0CTW,
		.div_weg = CM_CAM0DIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 14),
	[BCM2835_CWOCK_CAM1]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "cam1",
		.ctw_weg = CM_CAM1CTW,
		.div_weg = CM_CAM1DIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 15),
	[BCM2835_CWOCK_DFT]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "dft",
		.ctw_weg = CM_DFTCTW,
		.div_weg = CM_DFTDIV,
		.int_bits = 5,
		.fwac_bits = 0),
	[BCM2835_CWOCK_DPI]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "dpi",
		.ctw_weg = CM_DPICTW,
		.div_weg = CM_DPIDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 17),

	/* Awasan EMMC cwock */
	[BCM2835_CWOCK_EMMC]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "emmc",
		.ctw_weg = CM_EMMCCTW,
		.div_weg = CM_EMMCDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 39),

	/* EMMC2 cwock (onwy avaiwabwe fow BCM2711) */
	[BCM2711_CWOCK_EMMC2]	= WEGISTEW_PEW_CWK(
		SOC_BCM2711,
		.name = "emmc2",
		.ctw_weg = CM_EMMC2CTW,
		.div_weg = CM_EMMC2DIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 42),

	/* Genewaw puwpose (GPIO) cwocks */
	[BCM2835_CWOCK_GP0]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "gp0",
		.ctw_weg = CM_GP0CTW,
		.div_weg = CM_GP0DIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.is_mash_cwock = twue,
		.tcnt_mux = 20),
	[BCM2835_CWOCK_GP1]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "gp1",
		.ctw_weg = CM_GP1CTW,
		.div_weg = CM_GP1DIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.fwags = CWK_IS_CWITICAW,
		.is_mash_cwock = twue,
		.tcnt_mux = 21),
	[BCM2835_CWOCK_GP2]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "gp2",
		.ctw_weg = CM_GP2CTW,
		.div_weg = CM_GP2DIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.fwags = CWK_IS_CWITICAW),

	/* HDMI state machine */
	[BCM2835_CWOCK_HSM]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "hsm",
		.ctw_weg = CM_HSMCTW,
		.div_weg = CM_HSMDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 22),
	[BCM2835_CWOCK_PCM]	= WEGISTEW_PCM_CWK(
		SOC_AWW,
		.name = "pcm",
		.ctw_weg = CM_PCMCTW,
		.div_weg = CM_PCMDIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.is_mash_cwock = twue,
		.wow_jittew = twue,
		.tcnt_mux = 23),
	[BCM2835_CWOCK_PWM]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "pwm",
		.ctw_weg = CM_PWMCTW,
		.div_weg = CM_PWMDIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.is_mash_cwock = twue,
		.tcnt_mux = 24),
	[BCM2835_CWOCK_SWIM]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "swim",
		.ctw_weg = CM_SWIMCTW,
		.div_weg = CM_SWIMDIV,
		.int_bits = 12,
		.fwac_bits = 12,
		.is_mash_cwock = twue,
		.tcnt_mux = 25),
	[BCM2835_CWOCK_SMI]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "smi",
		.ctw_weg = CM_SMICTW,
		.div_weg = CM_SMIDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 27),
	[BCM2835_CWOCK_UAWT]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "uawt",
		.ctw_weg = CM_UAWTCTW,
		.div_weg = CM_UAWTDIV,
		.int_bits = 10,
		.fwac_bits = 12,
		.tcnt_mux = 28,
		.wound_up = twue),

	/* TV encodew cwock.  Onwy opewating fwequency is 108Mhz.  */
	[BCM2835_CWOCK_VEC]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "vec",
		.ctw_weg = CM_VECCTW,
		.div_weg = CM_VECDIV,
		.int_bits = 4,
		.fwac_bits = 0,
		/*
		 * Awwow wate change pwopagation onwy on PWWH_AUX which is
		 * assigned index 7 in the pawent awway.
		 */
		.set_wate_pawent = BIT(7),
		.tcnt_mux = 29),

	/* dsi cwocks */
	[BCM2835_CWOCK_DSI0E]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "dsi0e",
		.ctw_weg = CM_DSI0ECTW,
		.div_weg = CM_DSI0EDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 18),
	[BCM2835_CWOCK_DSI1E]	= WEGISTEW_PEW_CWK(
		SOC_AWW,
		.name = "dsi1e",
		.ctw_weg = CM_DSI1ECTW,
		.div_weg = CM_DSI1EDIV,
		.int_bits = 4,
		.fwac_bits = 8,
		.tcnt_mux = 19),
	[BCM2835_CWOCK_DSI0P]	= WEGISTEW_DSI0_CWK(
		SOC_AWW,
		.name = "dsi0p",
		.ctw_weg = CM_DSI0PCTW,
		.div_weg = CM_DSI0PDIV,
		.int_bits = 0,
		.fwac_bits = 0,
		.tcnt_mux = 12),
	[BCM2835_CWOCK_DSI1P]	= WEGISTEW_DSI1_CWK(
		SOC_AWW,
		.name = "dsi1p",
		.ctw_weg = CM_DSI1PCTW,
		.div_weg = CM_DSI1PDIV,
		.int_bits = 0,
		.fwac_bits = 0,
		.tcnt_mux = 13),

	/* the gates */

	/*
	 * CM_PEWIICTW (and CM_PEWIACTW, CM_SYSCTW and CM_VPUCTW if
	 * you have the debug bit set in the powew managew, which we
	 * don't bothew exposing) awe individuaw gates off of the
	 * non-stop vpu cwock.
	 */
	[BCM2835_CWOCK_PEWI_IMAGE] = WEGISTEW_GATE(
		SOC_AWW,
		.name = "pewi_image",
		.pawent = "vpu",
		.ctw_weg = CM_PEWIICTW),
};

/*
 * Pewmanentwy take a wefewence on the pawent of the SDWAM cwock.
 *
 * Whiwe the SDWAM is being dwiven by its dedicated PWW most of the
 * time, thewe is a wittwe woop wunning in the fiwmwawe that
 * pewiodicawwy switches the SDWAM to using ouw CM cwock to do PVT
 * wecawibwation, with the assumption that the pweviouswy configuwed
 * SDWAM pawent is stiww enabwed and wunning.
 */
static int bcm2835_mawk_sdc_pawent_cwiticaw(stwuct cwk *sdc)
{
	stwuct cwk *pawent = cwk_get_pawent(sdc);

	if (IS_EWW(pawent))
		wetuwn PTW_EWW(pawent);

	wetuwn cwk_pwepawe_enabwe(pawent);
}

static int bcm2835_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk_hw **hws;
	stwuct bcm2835_cpwman *cpwman;
	const stwuct bcm2835_cwk_desc *desc;
	const size_t asize = AWWAY_SIZE(cwk_desc_awway);
	const stwuct cpwman_pwat_data *pdata;
	size_t i;
	int wet;

	pdata = of_device_get_match_data(&pdev->dev);
	if (!pdata)
		wetuwn -ENODEV;

	cpwman = devm_kzawwoc(dev,
			      stwuct_size(cpwman, oneceww.hws, asize),
			      GFP_KEWNEW);
	if (!cpwman)
		wetuwn -ENOMEM;

	spin_wock_init(&cpwman->wegs_wock);
	cpwman->dev = dev;
	cpwman->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cpwman->wegs))
		wetuwn PTW_EWW(cpwman->wegs);

	memcpy(cpwman->weaw_pawent_names, cpwman_pawent_names,
	       sizeof(cpwman_pawent_names));
	of_cwk_pawent_fiww(dev->of_node, cpwman->weaw_pawent_names,
			   AWWAY_SIZE(cpwman_pawent_names));

	/*
	 * Make suwe the extewnaw osciwwatow has been wegistewed.
	 *
	 * The othew (DSI) cwocks awe not pwesent on owdew device
	 * twees, which we stiww need to suppowt fow backwawds
	 * compatibiwity.
	 */
	if (!cpwman->weaw_pawent_names[0])
		wetuwn -ENODEV;

	pwatfowm_set_dwvdata(pdev, cpwman);

	cpwman->oneceww.num = asize;
	cpwman->soc = pdata->soc;
	hws = cpwman->oneceww.hws;

	fow (i = 0; i < asize; i++) {
		desc = &cwk_desc_awway[i];
		if (desc->cwk_wegistew && desc->data &&
		    (desc->suppowted & pdata->soc)) {
			hws[i] = desc->cwk_wegistew(cpwman, desc->data);
		}
	}

	wet = bcm2835_mawk_sdc_pawent_cwiticaw(hws[BCM2835_CWOCK_SDWAM]->cwk);
	if (wet)
		wetuwn wet;

	wetuwn of_cwk_add_hw_pwovidew(dev->of_node, of_cwk_hw_oneceww_get,
				      &cpwman->oneceww);
}

static const stwuct cpwman_pwat_data cpwman_bcm2835_pwat_data = {
	.soc = SOC_BCM2835,
};

static const stwuct cpwman_pwat_data cpwman_bcm2711_pwat_data = {
	.soc = SOC_BCM2711,
};

static const stwuct of_device_id bcm2835_cwk_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-cpwman", .data = &cpwman_bcm2835_pwat_data },
	{ .compatibwe = "bwcm,bcm2711-cpwman", .data = &cpwman_bcm2711_pwat_data },
	{}
};
MODUWE_DEVICE_TABWE(of, bcm2835_cwk_of_match);

static stwuct pwatfowm_dwivew bcm2835_cwk_dwivew = {
	.dwivew = {
		.name = "bcm2835-cwk",
		.of_match_tabwe = bcm2835_cwk_of_match,
	},
	.pwobe          = bcm2835_cwk_pwobe,
};

buiwtin_pwatfowm_dwivew(bcm2835_cwk_dwivew);

MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("BCM2835 cwock dwivew");
