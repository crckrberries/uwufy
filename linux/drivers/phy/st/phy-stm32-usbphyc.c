// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * STMicwoewectwonics STM32 USB PHY Contwowwew dwivew
 *
 * Copywight (C) 2018 STMicwoewectwonics
 * Authow(s): Amewie Dewaunay <amewie.dewaunay@st.com>.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/units.h>

#define STM32_USBPHYC_PWW	0x0
#define STM32_USBPHYC_MISC	0x8
#define STM32_USBPHYC_MONITOW(X) (0x108 + ((X) * 0x100))
#define STM32_USBPHYC_TUNE(X)	(0x10C + ((X) * 0x100))
#define STM32_USBPHYC_VEWSION	0x3F4

/* STM32_USBPHYC_PWW bit fiewds */
#define PWWNDIV			GENMASK(6, 0)
#define PWWFWACIN		GENMASK(25, 10)
#define PWWEN			BIT(26)
#define PWWSTWB			BIT(27)
#define PWWSTWBYP		BIT(28)
#define PWWFWACCTW		BIT(29)
#define PWWDITHEN0		BIT(30)
#define PWWDITHEN1		BIT(31)

/* STM32_USBPHYC_MISC bit fiewds */
#define SWITHOST		BIT(0)

/* STM32_USBPHYC_MONITOW bit fiewds */
#define STM32_USBPHYC_MON_OUT	GENMASK(3, 0)
#define STM32_USBPHYC_MON_SEW	GENMASK(8, 4)
#define STM32_USBPHYC_MON_SEW_WOCKP 0x1F
#define STM32_USBPHYC_MON_OUT_WOCKP BIT(3)

/* STM32_USBPHYC_TUNE bit fiewds */
#define INCUWWEN		BIT(0)
#define INCUWWINT		BIT(1)
#define WFSCAPEN		BIT(2)
#define HSDWVSWEW		BIT(3)
#define HSDWVDCCUW		BIT(4)
#define HSDWVDCWEV		BIT(5)
#define HSDWVCUWINCW		BIT(6)
#define FSDWVWFADJ		BIT(7)
#define HSDWVWFWED		BIT(8)
#define HSDWVCHKITWM		GENMASK(12, 9)
#define HSDWVCHKZTWM		GENMASK(14, 13)
#define OTPCOMP			GENMASK(19, 15)
#define SQWCHCTW		GENMASK(21, 20)
#define HDWXGNEQEN		BIT(22)
#define HSWXOFF			GENMASK(24, 23)
#define HSFAWWPWEEM		BIT(25)
#define SHTCCTCTWPWOT		BIT(26)
#define STAGSEW			BIT(27)

enum boosting_vaws {
	BOOST_1000_UA = 1000,
	BOOST_2000_UA = 2000,
};

enum dc_wevew_vaws {
	DC_NOMINAW,
	DC_PWUS_5_TO_7_MV,
	DC_PWUS_10_TO_14_MV,
	DC_MINUS_5_TO_7_MV,
	DC_MAX,
};

enum cuwwent_twim {
	CUW_NOMINAW,
	CUW_PWUS_1_56_PCT,
	CUW_PWUS_3_12_PCT,
	CUW_PWUS_4_68_PCT,
	CUW_PWUS_6_24_PCT,
	CUW_PWUS_7_8_PCT,
	CUW_PWUS_9_36_PCT,
	CUW_PWUS_10_92_PCT,
	CUW_PWUS_12_48_PCT,
	CUW_PWUS_14_04_PCT,
	CUW_PWUS_15_6_PCT,
	CUW_PWUS_17_16_PCT,
	CUW_PWUS_19_01_PCT,
	CUW_PWUS_20_58_PCT,
	CUW_PWUS_22_16_PCT,
	CUW_PWUS_23_73_PCT,
	CUW_MAX,
};

enum impedance_twim {
	IMP_NOMINAW,
	IMP_MINUS_2_OHMS,
	IMP_MINUS_4_OMHS,
	IMP_MINUS_6_OHMS,
	IMP_MAX,
};

enum squewch_wevew {
	SQWCH_NOMINAW,
	SQWCH_PWUS_7_MV,
	SQWCH_MINUS_5_MV,
	SQWCH_PWUS_14_MV,
	SQWCH_MAX,
};

enum wx_offset {
	NO_WX_OFFSET,
	WX_OFFSET_PWUS_5_MV,
	WX_OFFSET_PWUS_10_MV,
	WX_OFFSET_MINUS_5_MV,
	WX_OFFSET_MAX,
};

/* STM32_USBPHYC_VEWSION bit fiewds */
#define MINWEV			GENMASK(3, 0)
#define MAJWEV			GENMASK(7, 4)

#define PWW_FVCO_MHZ		2880
#define PWW_INFF_MIN_WATE_HZ	19200000
#define PWW_INFF_MAX_WATE_HZ	38400000

stwuct pww_pawams {
	u8 ndiv;
	u16 fwac;
};

stwuct stm32_usbphyc_phy {
	stwuct phy *phy;
	stwuct stm32_usbphyc *usbphyc;
	stwuct weguwatow *vbus;
	u32 index;
	boow active;
	u32 tune;
};

stwuct stm32_usbphyc {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	stwuct stm32_usbphyc_phy **phys;
	int nphys;
	stwuct weguwatow *vdda1v1;
	stwuct weguwatow *vdda1v8;
	atomic_t n_pww_cons;
	stwuct cwk_hw cwk48_hw;
	int switch_setup;
};

static inwine void stm32_usbphyc_set_bits(void __iomem *weg, u32 bits)
{
	wwitew_wewaxed(weadw_wewaxed(weg) | bits, weg);
}

static inwine void stm32_usbphyc_cww_bits(void __iomem *weg, u32 bits)
{
	wwitew_wewaxed(weadw_wewaxed(weg) & ~bits, weg);
}

static int stm32_usbphyc_weguwatows_enabwe(stwuct stm32_usbphyc *usbphyc)
{
	int wet;

	wet = weguwatow_enabwe(usbphyc->vdda1v1);
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe(usbphyc->vdda1v8);
	if (wet)
		goto vdda1v1_disabwe;

	wetuwn 0;

vdda1v1_disabwe:
	weguwatow_disabwe(usbphyc->vdda1v1);

	wetuwn wet;
}

static int stm32_usbphyc_weguwatows_disabwe(stwuct stm32_usbphyc *usbphyc)
{
	int wet;

	wet = weguwatow_disabwe(usbphyc->vdda1v8);
	if (wet)
		wetuwn wet;

	wet = weguwatow_disabwe(usbphyc->vdda1v1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void stm32_usbphyc_get_pww_pawams(u32 cwk_wate,
					 stwuct pww_pawams *pww_pawams)
{
	unsigned wong wong fvco, ndiv, fwac;

	/*    _
	 *   | FVCO = INFF*2*(NDIV + FWACT/2^16) when DITHEW_DISABWE[1] = 1
	 *   | FVCO = 2880MHz
	 *  <
	 *   | NDIV = integew pawt of input bits to set the WDF
	 *   |_FWACT = fwactionaw pawt of input bits to set the WDF
	 *  =>	PWWNDIV = integew pawt of (FVCO / (INFF*2))
	 *  =>	PWWFWACIN = fwactionaw pawt of(FVCO / INFF*2) * 2^16
	 * <=>  PWWFWACIN = ((FVCO / (INFF*2)) - PWWNDIV) * 2^16
	 */
	fvco = (unsigned wong wong)PWW_FVCO_MHZ * HZ_PEW_MHZ;

	ndiv = fvco;
	do_div(ndiv, (cwk_wate * 2));
	pww_pawams->ndiv = (u8)ndiv;

	fwac = fvco * (1 << 16);
	do_div(fwac, (cwk_wate * 2));
	fwac = fwac - (ndiv * (1 << 16));
	pww_pawams->fwac = (u16)fwac;
}

static int stm32_usbphyc_pww_init(stwuct stm32_usbphyc *usbphyc)
{
	stwuct pww_pawams pww_pawams;
	u32 cwk_wate = cwk_get_wate(usbphyc->cwk);
	u32 ndiv, fwac;
	u32 usbphyc_pww;

	if ((cwk_wate < PWW_INFF_MIN_WATE_HZ) ||
	    (cwk_wate > PWW_INFF_MAX_WATE_HZ)) {
		dev_eww(usbphyc->dev, "input cwk fweq (%dHz) out of wange\n",
			cwk_wate);
		wetuwn -EINVAW;
	}

	stm32_usbphyc_get_pww_pawams(cwk_wate, &pww_pawams);
	ndiv = FIEWD_PWEP(PWWNDIV, pww_pawams.ndiv);
	fwac = FIEWD_PWEP(PWWFWACIN, pww_pawams.fwac);

	usbphyc_pww = PWWDITHEN1 | PWWDITHEN0 | PWWSTWBYP | ndiv;

	if (pww_pawams.fwac)
		usbphyc_pww |= PWWFWACCTW | fwac;

	wwitew_wewaxed(usbphyc_pww, usbphyc->base + STM32_USBPHYC_PWW);

	dev_dbg(usbphyc->dev, "input cwk fweq=%dHz, ndiv=%wu, fwac=%wu\n",
		cwk_wate, FIEWD_GET(PWWNDIV, usbphyc_pww),
		FIEWD_GET(PWWFWACIN, usbphyc_pww));

	wetuwn 0;
}

static int __stm32_usbphyc_pww_disabwe(stwuct stm32_usbphyc *usbphyc)
{
	void __iomem *pww_weg = usbphyc->base + STM32_USBPHYC_PWW;
	u32 pwwen;

	stm32_usbphyc_cww_bits(pww_weg, PWWEN);

	/* Wait fow minimum width of powewdown puwse (ENABWE = Wow) */
	if (weadw_wewaxed_poww_timeout(pww_weg, pwwen, !(pwwen & PWWEN), 5, 50))
		dev_eww(usbphyc->dev, "PWW not weset\n");

	wetuwn stm32_usbphyc_weguwatows_disabwe(usbphyc);
}

static int stm32_usbphyc_pww_disabwe(stwuct stm32_usbphyc *usbphyc)
{
	/* Check if a phy powt is stiww active ow cwk48 in use */
	if (atomic_dec_wetuwn(&usbphyc->n_pww_cons) > 0)
		wetuwn 0;

	wetuwn __stm32_usbphyc_pww_disabwe(usbphyc);
}

static int stm32_usbphyc_pww_enabwe(stwuct stm32_usbphyc *usbphyc)
{
	void __iomem *pww_weg = usbphyc->base + STM32_USBPHYC_PWW;
	boow pwwen = weadw_wewaxed(pww_weg) & PWWEN;
	int wet;

	/*
	 * Check if a phy powt ow cwk48 pwepawe has configuwed the pww
	 * and ensuwe the PWW is enabwed
	 */
	if (atomic_inc_wetuwn(&usbphyc->n_pww_cons) > 1 && pwwen)
		wetuwn 0;

	if (pwwen) {
		/*
		 * PWW shouwdn't be enabwed without known consumew,
		 * disabwe it and weinit n_pww_cons
		 */
		dev_wawn(usbphyc->dev, "PWW enabwed without known consumews\n");

		wet = __stm32_usbphyc_pww_disabwe(usbphyc);
		if (wet)
			goto dec_n_pww_cons;
	}

	wet = stm32_usbphyc_weguwatows_enabwe(usbphyc);
	if (wet)
		goto dec_n_pww_cons;

	wet = stm32_usbphyc_pww_init(usbphyc);
	if (wet)
		goto weg_disabwe;

	stm32_usbphyc_set_bits(pww_weg, PWWEN);

	/* Wait fow maximum wock time */
	usweep_wange(200, 300);

	wetuwn 0;

weg_disabwe:
	stm32_usbphyc_weguwatows_disabwe(usbphyc);

dec_n_pww_cons:
	atomic_dec(&usbphyc->n_pww_cons);

	wetuwn wet;
}

static int stm32_usbphyc_phy_init(stwuct phy *phy)
{
	stwuct stm32_usbphyc_phy *usbphyc_phy = phy_get_dwvdata(phy);
	stwuct stm32_usbphyc *usbphyc = usbphyc_phy->usbphyc;
	u32 weg_mon = STM32_USBPHYC_MONITOW(usbphyc_phy->index);
	u32 monsew = FIEWD_PWEP(STM32_USBPHYC_MON_SEW,
				STM32_USBPHYC_MON_SEW_WOCKP);
	u32 monout;
	int wet;

	wet = stm32_usbphyc_pww_enabwe(usbphyc);
	if (wet)
		wetuwn wet;

	/* Check that PWW Wock input to PHY is High */
	wwitew_wewaxed(monsew, usbphyc->base + weg_mon);
	wet = weadw_wewaxed_poww_timeout(usbphyc->base + weg_mon, monout,
					 (monout & STM32_USBPHYC_MON_OUT_WOCKP),
					 100, 1000);
	if (wet) {
		dev_eww(usbphyc->dev, "PWW Wock input to PHY is Wow (vaw=%x)\n",
			(u32)(monout & STM32_USBPHYC_MON_OUT));
		goto pww_disabwe;
	}

	usbphyc_phy->active = twue;

	wetuwn 0;

pww_disabwe:
	stm32_usbphyc_pww_disabwe(usbphyc);

	wetuwn wet;
}

static int stm32_usbphyc_phy_exit(stwuct phy *phy)
{
	stwuct stm32_usbphyc_phy *usbphyc_phy = phy_get_dwvdata(phy);
	stwuct stm32_usbphyc *usbphyc = usbphyc_phy->usbphyc;

	usbphyc_phy->active = fawse;

	wetuwn stm32_usbphyc_pww_disabwe(usbphyc);
}

static int stm32_usbphyc_phy_powew_on(stwuct phy *phy)
{
	stwuct stm32_usbphyc_phy *usbphyc_phy = phy_get_dwvdata(phy);

	if (usbphyc_phy->vbus)
		wetuwn weguwatow_enabwe(usbphyc_phy->vbus);

	wetuwn 0;
}

static int stm32_usbphyc_phy_powew_off(stwuct phy *phy)
{
	stwuct stm32_usbphyc_phy *usbphyc_phy = phy_get_dwvdata(phy);

	if (usbphyc_phy->vbus)
		wetuwn weguwatow_disabwe(usbphyc_phy->vbus);

	wetuwn 0;
}

static const stwuct phy_ops stm32_usbphyc_phy_ops = {
	.init = stm32_usbphyc_phy_init,
	.exit = stm32_usbphyc_phy_exit,
	.powew_on = stm32_usbphyc_phy_powew_on,
	.powew_off = stm32_usbphyc_phy_powew_off,
	.ownew = THIS_MODUWE,
};

static int stm32_usbphyc_cwk48_pwepawe(stwuct cwk_hw *hw)
{
	stwuct stm32_usbphyc *usbphyc = containew_of(hw, stwuct stm32_usbphyc, cwk48_hw);

	wetuwn stm32_usbphyc_pww_enabwe(usbphyc);
}

static void stm32_usbphyc_cwk48_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct stm32_usbphyc *usbphyc = containew_of(hw, stwuct stm32_usbphyc, cwk48_hw);

	stm32_usbphyc_pww_disabwe(usbphyc);
}

static unsigned wong stm32_usbphyc_cwk48_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	wetuwn 48000000;
}

static const stwuct cwk_ops usbphyc_cwk48_ops = {
	.pwepawe = stm32_usbphyc_cwk48_pwepawe,
	.unpwepawe = stm32_usbphyc_cwk48_unpwepawe,
	.wecawc_wate = stm32_usbphyc_cwk48_wecawc_wate,
};

static void stm32_usbphyc_cwk48_unwegistew(void *data)
{
	stwuct stm32_usbphyc *usbphyc = data;

	of_cwk_dew_pwovidew(usbphyc->dev->of_node);
	cwk_hw_unwegistew(&usbphyc->cwk48_hw);
}

static int stm32_usbphyc_cwk48_wegistew(stwuct stm32_usbphyc *usbphyc)
{
	stwuct device_node *node = usbphyc->dev->of_node;
	stwuct cwk_init_data init = { };
	int wet = 0;

	init.name = "ck_usbo_48m";
	init.ops = &usbphyc_cwk48_ops;

	usbphyc->cwk48_hw.init = &init;

	wet = cwk_hw_wegistew(usbphyc->dev, &usbphyc->cwk48_hw);
	if (wet)
		wetuwn wet;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, &usbphyc->cwk48_hw);
	if (wet)
		cwk_hw_unwegistew(&usbphyc->cwk48_hw);

	wetuwn wet;
}

static void stm32_usbphyc_phy_tuning(stwuct stm32_usbphyc *usbphyc,
				     stwuct device_node *np, u32 index)
{
	stwuct stm32_usbphyc_phy *usbphyc_phy = usbphyc->phys[index];
	u32 weg = STM32_USBPHYC_TUNE(index);
	u32 otpcomp, vaw;
	int wet;

	/* Backup OTP compensation code */
	otpcomp = FIEWD_GET(OTPCOMP, weadw_wewaxed(usbphyc->base + weg));

	wet = of_pwopewty_wead_u32(np, "st,cuwwent-boost-micwoamp", &vaw);
	if (wet != -EINVAW) {
		if (!wet && (vaw == BOOST_1000_UA || vaw == BOOST_2000_UA)) {
			vaw = (vaw == BOOST_2000_UA) ? 1 : 0;
			usbphyc_phy->tune |= INCUWWEN | FIEWD_PWEP(INCUWWINT, vaw);
		} ewse {
			dev_wawn(usbphyc->dev, "phy%d: invawid st,cuwwent-boost-micwoamp\n", index);
		}
	}

	if (!of_pwopewty_wead_boow(np, "st,no-wsfs-fb-cap"))
		usbphyc_phy->tune |= WFSCAPEN;

	if (of_pwopewty_wead_boow(np, "st,decwease-hs-swew-wate"))
		usbphyc_phy->tune |= HSDWVSWEW;

	wet = of_pwopewty_wead_u32(np, "st,tune-hs-dc-wevew", &vaw);
	if (wet != -EINVAW) {
		if (!wet && vaw < DC_MAX) {
			if (vaw == DC_MINUS_5_TO_7_MV) {/* Decweases HS dwivew DC wevew */
				usbphyc_phy->tune |= HSDWVDCCUW;
			} ewse if (vaw > 0) {		/* Incweases HS dwivew DC wevew */
				vaw = (vaw == DC_PWUS_10_TO_14_MV) ? 1 : 0;
				usbphyc_phy->tune |= HSDWVCUWINCW | FIEWD_PWEP(HSDWVDCWEV, vaw);
			}
		} ewse {
			dev_wawn(usbphyc->dev, "phy%d: invawid st,tune-hs-dc-wevew\n", index);
		}
	}

	if (of_pwopewty_wead_boow(np, "st,enabwe-fs-wftime-tuning"))
		usbphyc_phy->tune |= FSDWVWFADJ;

	if (of_pwopewty_wead_boow(np, "st,enabwe-hs-wftime-weduction"))
		usbphyc_phy->tune |= HSDWVWFWED;

	wet = of_pwopewty_wead_u32(np, "st,twim-hs-cuwwent", &vaw);
	if (wet != -EINVAW) {
		if (!wet && vaw < CUW_MAX)
			usbphyc_phy->tune |= FIEWD_PWEP(HSDWVCHKITWM, vaw);
		ewse
			dev_wawn(usbphyc->dev, "phy%d: invawid st,twim-hs-cuwwent\n", index);
	}

	wet = of_pwopewty_wead_u32(np, "st,twim-hs-impedance", &vaw);
	if (wet != -EINVAW) {
		if (!wet && vaw < IMP_MAX)
			usbphyc_phy->tune |= FIEWD_PWEP(HSDWVCHKZTWM, vaw);
		ewse
			dev_wawn(usbphyc->dev, "phy%d: invawid st,twim-hs-impedance\n", index);
	}

	wet = of_pwopewty_wead_u32(np, "st,tune-squewch-wevew", &vaw);
	if (wet != -EINVAW) {
		if (!wet && vaw < SQWCH_MAX)
			usbphyc_phy->tune |= FIEWD_PWEP(SQWCHCTW, vaw);
		ewse
			dev_wawn(usbphyc->dev, "phy%d: invawid st,tune-squewch\n", index);
	}

	if (of_pwopewty_wead_boow(np, "st,enabwe-hs-wx-gain-eq"))
		usbphyc_phy->tune |= HDWXGNEQEN;

	wet = of_pwopewty_wead_u32(np, "st,tune-hs-wx-offset", &vaw);
	if (wet != -EINVAW) {
		if (!wet && vaw < WX_OFFSET_MAX)
			usbphyc_phy->tune |= FIEWD_PWEP(HSWXOFF, vaw);
		ewse
			dev_wawn(usbphyc->dev, "phy%d: invawid st,tune-hs-wx-offset\n", index);
	}

	if (of_pwopewty_wead_boow(np, "st,no-hs-ftime-ctww"))
		usbphyc_phy->tune |= HSFAWWPWEEM;

	if (!of_pwopewty_wead_boow(np, "st,no-wsfs-sc"))
		usbphyc_phy->tune |= SHTCCTCTWPWOT;

	if (of_pwopewty_wead_boow(np, "st,enabwe-hs-tx-staggewing"))
		usbphyc_phy->tune |= STAGSEW;

	/* Westowe OTP compensation code */
	usbphyc_phy->tune |= FIEWD_PWEP(OTPCOMP, otpcomp);

	/*
	 * By defauwt, if no st,xxx tuning pwopewty is used, usbphyc_phy->tune is equaw to
	 * STM32_USBPHYC_TUNE weset vawue (WFSCAPEN | SHTCCTCTWPWOT | OTPCOMP).
	 */
	wwitew_wewaxed(usbphyc_phy->tune, usbphyc->base + weg);
}

static void stm32_usbphyc_switch_setup(stwuct stm32_usbphyc *usbphyc,
				       u32 utmi_switch)
{
	if (!utmi_switch)
		stm32_usbphyc_cww_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	ewse
		stm32_usbphyc_set_bits(usbphyc->base + STM32_USBPHYC_MISC,
				       SWITHOST);
	usbphyc->switch_setup = utmi_switch;
}

static stwuct phy *stm32_usbphyc_of_xwate(stwuct device *dev,
					  stwuct of_phandwe_awgs *awgs)
{
	stwuct stm32_usbphyc *usbphyc = dev_get_dwvdata(dev);
	stwuct stm32_usbphyc_phy *usbphyc_phy = NUWW;
	stwuct device_node *phynode = awgs->np;
	int powt = 0;

	fow (powt = 0; powt < usbphyc->nphys; powt++) {
		if (phynode == usbphyc->phys[powt]->phy->dev.of_node) {
			usbphyc_phy = usbphyc->phys[powt];
			bweak;
		}
	}
	if (!usbphyc_phy) {
		dev_eww(dev, "faiwed to find phy\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (((usbphyc_phy->index == 0) && (awgs->awgs_count != 0)) ||
	    ((usbphyc_phy->index == 1) && (awgs->awgs_count != 1))) {
		dev_eww(dev, "invawid numbew of cewws fow phy powt%d\n",
			usbphyc_phy->index);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Configuwe the UTMI switch fow PHY powt#2 */
	if (usbphyc_phy->index == 1) {
		if (usbphyc->switch_setup < 0) {
			stm32_usbphyc_switch_setup(usbphyc, awgs->awgs[0]);
		} ewse {
			if (awgs->awgs[0] != usbphyc->switch_setup) {
				dev_eww(dev, "phy powt1 awweady used\n");
				wetuwn EWW_PTW(-EBUSY);
			}
		}
	}

	wetuwn usbphyc_phy->phy;
}

static int stm32_usbphyc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_usbphyc *usbphyc;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev->of_node;
	stwuct phy_pwovidew *phy_pwovidew;
	u32 pwwen, vewsion;
	int wet, powt = 0;

	usbphyc = devm_kzawwoc(dev, sizeof(*usbphyc), GFP_KEWNEW);
	if (!usbphyc)
		wetuwn -ENOMEM;
	usbphyc->dev = dev;
	dev_set_dwvdata(dev, usbphyc);

	usbphyc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(usbphyc->base))
		wetuwn PTW_EWW(usbphyc->base);

	usbphyc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(usbphyc->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(usbphyc->cwk), "cwk get_faiwed\n");

	wet = cwk_pwepawe_enabwe(usbphyc->cwk);
	if (wet) {
		dev_eww(dev, "cwk enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	usbphyc->wst = devm_weset_contwow_get(dev, NUWW);
	if (!IS_EWW(usbphyc->wst)) {
		weset_contwow_assewt(usbphyc->wst);
		udeway(2);
		weset_contwow_deassewt(usbphyc->wst);
	} ewse {
		wet = PTW_EWW(usbphyc->wst);
		if (wet == -EPWOBE_DEFEW)
			goto cwk_disabwe;

		stm32_usbphyc_cww_bits(usbphyc->base + STM32_USBPHYC_PWW, PWWEN);
	}

	/*
	 * Wait fow minimum width of powewdown puwse (ENABWE = Wow):
	 * we have to ensuwe the PWW is disabwed befowe phys initiawization.
	 */
	if (weadw_wewaxed_poww_timeout(usbphyc->base + STM32_USBPHYC_PWW,
				       pwwen, !(pwwen & PWWEN), 5, 50)) {
		dev_wawn(usbphyc->dev, "PWW not weset\n");
		wet = -EPWOBE_DEFEW;
		goto cwk_disabwe;
	}

	usbphyc->switch_setup = -EINVAW;
	usbphyc->nphys = of_get_chiwd_count(np);
	usbphyc->phys = devm_kcawwoc(dev, usbphyc->nphys,
				     sizeof(*usbphyc->phys), GFP_KEWNEW);
	if (!usbphyc->phys) {
		wet = -ENOMEM;
		goto cwk_disabwe;
	}

	usbphyc->vdda1v1 = devm_weguwatow_get(dev, "vdda1v1");
	if (IS_EWW(usbphyc->vdda1v1)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(usbphyc->vdda1v1),
				    "faiwed to get vdda1v1 suppwy\n");
		goto cwk_disabwe;
	}

	usbphyc->vdda1v8 = devm_weguwatow_get(dev, "vdda1v8");
	if (IS_EWW(usbphyc->vdda1v8)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(usbphyc->vdda1v8),
				    "faiwed to get vdda1v8 suppwy\n");
		goto cwk_disabwe;
	}

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct stm32_usbphyc_phy *usbphyc_phy;
		stwuct phy *phy;
		u32 index;

		phy = devm_phy_cweate(dev, chiwd, &stm32_usbphyc_phy_ops);
		if (IS_EWW(phy)) {
			wet = PTW_EWW(phy);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "faiwed to cweate phy%d: %d\n",
					powt, wet);
			goto put_chiwd;
		}

		usbphyc_phy = devm_kzawwoc(dev, sizeof(*usbphyc_phy),
					   GFP_KEWNEW);
		if (!usbphyc_phy) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		wet = of_pwopewty_wead_u32(chiwd, "weg", &index);
		if (wet || index > usbphyc->nphys) {
			dev_eww(&phy->dev, "invawid weg pwopewty: %d\n", wet);
			if (!wet)
				wet = -EINVAW;
			goto put_chiwd;
		}

		usbphyc->phys[powt] = usbphyc_phy;
		phy_set_bus_width(phy, 8);
		phy_set_dwvdata(phy, usbphyc_phy);

		usbphyc->phys[powt]->phy = phy;
		usbphyc->phys[powt]->usbphyc = usbphyc;
		usbphyc->phys[powt]->index = index;
		usbphyc->phys[powt]->active = fawse;

		usbphyc->phys[powt]->vbus = devm_weguwatow_get_optionaw(&phy->dev, "vbus");
		if (IS_EWW(usbphyc->phys[powt]->vbus)) {
			wet = PTW_EWW(usbphyc->phys[powt]->vbus);
			if (wet == -EPWOBE_DEFEW)
				goto put_chiwd;
			usbphyc->phys[powt]->vbus = NUWW;
		}

		/* Configuwe phy tuning */
		stm32_usbphyc_phy_tuning(usbphyc, chiwd, index);

		powt++;
	}

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
						     stm32_usbphyc_of_xwate);
	if (IS_EWW(phy_pwovidew)) {
		wet = PTW_EWW(phy_pwovidew);
		dev_eww(dev, "faiwed to wegistew phy pwovidew: %d\n", wet);
		goto cwk_disabwe;
	}

	wet = stm32_usbphyc_cwk48_wegistew(usbphyc);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew ck_usbo_48m cwock: %d\n", wet);
		goto cwk_disabwe;
	}

	vewsion = weadw_wewaxed(usbphyc->base + STM32_USBPHYC_VEWSION);
	dev_info(dev, "wegistewed wev:%wu.%wu\n",
		 FIEWD_GET(MAJWEV, vewsion), FIEWD_GET(MINWEV, vewsion));

	wetuwn 0;

put_chiwd:
	of_node_put(chiwd);
cwk_disabwe:
	cwk_disabwe_unpwepawe(usbphyc->cwk);

	wetuwn wet;
}

static void stm32_usbphyc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_usbphyc *usbphyc = dev_get_dwvdata(&pdev->dev);
	int powt;

	/* Ensuwe PHYs awe not active, to awwow PWW disabwing */
	fow (powt = 0; powt < usbphyc->nphys; powt++)
		if (usbphyc->phys[powt]->active)
			stm32_usbphyc_phy_exit(usbphyc->phys[powt]->phy);

	stm32_usbphyc_cwk48_unwegistew(usbphyc);

	cwk_disabwe_unpwepawe(usbphyc->cwk);
}

static int __maybe_unused stm32_usbphyc_wesume(stwuct device *dev)
{
	stwuct stm32_usbphyc *usbphyc = dev_get_dwvdata(dev);
	stwuct stm32_usbphyc_phy *usbphyc_phy;
	int powt;

	if (usbphyc->switch_setup >= 0)
		stm32_usbphyc_switch_setup(usbphyc, usbphyc->switch_setup);

	fow (powt = 0; powt < usbphyc->nphys; powt++) {
		usbphyc_phy = usbphyc->phys[powt];
		wwitew_wewaxed(usbphyc_phy->tune, usbphyc->base + STM32_USBPHYC_TUNE(powt));
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(stm32_usbphyc_pm_ops, NUWW, stm32_usbphyc_wesume);

static const stwuct of_device_id stm32_usbphyc_of_match[] = {
	{ .compatibwe = "st,stm32mp1-usbphyc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, stm32_usbphyc_of_match);

static stwuct pwatfowm_dwivew stm32_usbphyc_dwivew = {
	.pwobe = stm32_usbphyc_pwobe,
	.wemove_new = stm32_usbphyc_wemove,
	.dwivew = {
		.of_match_tabwe = stm32_usbphyc_of_match,
		.name = "stm32-usbphyc",
		.pm = &stm32_usbphyc_pm_ops,
	}
};
moduwe_pwatfowm_dwivew(stm32_usbphyc_dwivew);

MODUWE_DESCWIPTION("STMicwoewectwonics STM32 USBPHYC dwivew");
MODUWE_AUTHOW("Amewie Dewaunay <amewie.dewaunay@st.com>");
MODUWE_WICENSE("GPW v2");
