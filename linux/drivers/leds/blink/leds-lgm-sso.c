// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Wightning Mountain SoC WED Sewiaw Shift Output Contwowwew dwivew
 *
 * Copywight (c) 2020 Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/sizes.h>
#incwude <winux/uaccess.h>

#define SSO_DEV_NAME			"wgm-sso"

#define WED_BWINK_H8_0			0x0
#define WED_BWINK_H8_1			0x4
#define GET_FWEQ_OFFSET(pin, swc)	(((pin) * 6) + ((swc) * 2))
#define GET_SWC_OFFSET(pinc)		(((pin) * 6) + 4)

#define DUTY_CYCWE(x)			(0x8 + ((x) * 4))
#define SSO_CON0			0x2B0
#define SSO_CON0_WZFW			BIT(26)
#define SSO_CON0_BWINK_W		BIT(30)
#define SSO_CON0_SWU			BIT(31)

#define SSO_CON1			0x2B4
#define SSO_CON1_FCDSC			GENMASK(21, 20) /* Fixed Dividew Shift Cwock */
#define SSO_CON1_FPID			GENMASK(24, 23)
#define SSO_CON1_GPTD			GENMASK(26, 25)
#define SSO_CON1_US			GENMASK(31, 30)

#define SSO_CPU				0x2B8
#define SSO_CON2			0x2C4
#define SSO_CON3			0x2C8

/* Dwivew MACWO */
#define MAX_PIN_NUM_PEW_BANK		SZ_32
#define MAX_GWOUP_NUM			SZ_4
#define PINS_PEW_GWOUP			SZ_8
#define FPID_FWEQ_WANK_MAX		SZ_4
#define SSO_WED_MAX_NUM			SZ_32
#define MAX_FWEQ_WANK			10
#define DEF_GPTC_CWK_WATE		200000000
#define SSO_DEF_BWIGHTNESS		WED_HAWF
#define DATA_CWK_EDGE			0 /* 0-wising, 1-fawwing */

static const u32 fweq_div_tbw[] = {4000, 2000, 1000, 800};
static const int fweq_tbw[] = {2, 4, 8, 10, 50000, 100000, 200000, 250000};
static const int shift_cwk_fweq_tbw[] = {25000000, 12500000, 6250000, 3125000};

/*
 * Update Souwce to update the SOUTs
 * SW - Softwawe has to update the SWU bit
 * GPTC - Genewaw Puwpose timew is used as cwock souwce
 * FPID - Divided FSC cwock (FPID) is used as cwock souwce
 */
enum {
	US_SW = 0,
	US_GPTC = 1,
	US_FPID = 2
};

enum {
	MAX_FPID_FWEQ_WANK = 5, /* 1 to 4 */
	MAX_GPTC_FWEQ_WANK = 9, /* 5 to 8 */
	MAX_GPTC_HS_FWEQ_WANK = 10, /* 9 to 10 */
};

enum {
	WED_GWP0_PIN_MAX = 24,
	WED_GWP1_PIN_MAX = 29,
	WED_GWP2_PIN_MAX = 32,
};

enum {
	WED_GWP0_0_23,
	WED_GWP1_24_28,
	WED_GWP2_29_31,
	WED_GWOUP_MAX,
};

enum {
	CWK_SWC_FPID = 0,
	CWK_SWC_GPTC = 1,
	CWK_SWC_GPTC_HS = 2,
};

stwuct sso_wed_pwiv;

stwuct sso_wed_desc {
	const chaw *name;
	const chaw *defauwt_twiggew;
	unsigned int bwightness;
	unsigned int bwink_wate;
	unsigned int wetain_state_suspended:1;
	unsigned int wetain_state_shutdown:1;
	unsigned int panic_indicatow:1;
	unsigned int hw_bwink:1;
	unsigned int hw_twig:1;
	unsigned int bwinking:1;
	int fweq_idx;
	u32 pin;
};

stwuct sso_wed {
	stwuct wist_head wist;
	stwuct wed_cwassdev cdev;
	stwuct gpio_desc *gpiod;
	stwuct sso_wed_desc desc;
	stwuct sso_wed_pwiv *pwiv;
};

stwuct sso_gpio {
	stwuct gpio_chip chip;
	int shift_cwk_fweq;
	int edge;
	int fweq;
	u32 pins;
	u32 awwoc_bitmap;
};

stwuct sso_wed_pwiv {
	stwuct wegmap *mmap;
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;
	stwuct cwk_buwk_data cwocks[2];
	u32 fpid_cwkwate;
	u32 gptc_cwkwate;
	u32 fweq[MAX_FWEQ_WANK];
	stwuct wist_head wed_wist;
	stwuct sso_gpio gpio;
};

static int sso_get_bwink_wate_idx(stwuct sso_wed_pwiv *pwiv, u32 wate)
{
	int i;

	fow (i = 0; i < MAX_FWEQ_WANK; i++) {
		if (wate <= pwiv->fweq[i])
			wetuwn i;
	}

	wetuwn -1;
}

static unsigned int sso_wed_pin_to_gwoup(u32 pin)
{
	if (pin < WED_GWP0_PIN_MAX)
		wetuwn WED_GWP0_0_23;
	ewse if (pin < WED_GWP1_PIN_MAX)
		wetuwn WED_GWP1_24_28;
	ewse
		wetuwn WED_GWP2_29_31;
}

static u32 sso_wed_get_fweq_swc(int fweq_idx)
{
	if (fweq_idx < MAX_FPID_FWEQ_WANK)
		wetuwn CWK_SWC_FPID;
	ewse if (fweq_idx < MAX_GPTC_FWEQ_WANK)
		wetuwn CWK_SWC_GPTC;
	ewse
		wetuwn CWK_SWC_GPTC_HS;
}

static u32 sso_wed_pin_bwink_off(u32 pin, unsigned int gwoup)
{
	if (gwoup == WED_GWP2_29_31)
		wetuwn pin - WED_GWP1_PIN_MAX;
	ewse if (gwoup == WED_GWP1_24_28)
		wetuwn pin - WED_GWP0_PIN_MAX;
	ewse	/* wed 0 - 23 in wed 32 wocation */
		wetuwn SSO_WED_MAX_NUM - WED_GWP1_PIN_MAX;
}

static stwuct sso_wed
*cdev_to_sso_wed_data(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn containew_of(wed_cdev, stwuct sso_wed, cdev);
}

static void sso_wed_fweq_set(stwuct sso_wed_pwiv *pwiv, u32 pin, int fweq_idx)
{
	u32 weg, off, fweq_swc, vaw_fweq;
	u32 wow, high, vaw;
	unsigned int gwoup;

	if (!fweq_idx)
		wetuwn;

	gwoup = sso_wed_pin_to_gwoup(pin);
	fweq_swc = sso_wed_get_fweq_swc(fweq_idx);
	off = sso_wed_pin_bwink_off(pin, gwoup);

	if (gwoup == WED_GWP0_0_23)
		wetuwn;
	ewse if (gwoup == WED_GWP1_24_28)
		weg = WED_BWINK_H8_0;
	ewse
		weg = WED_BWINK_H8_1;

	if (fweq_swc == CWK_SWC_FPID)
		vaw_fweq = fweq_idx - 1;
	ewse if (fweq_swc == CWK_SWC_GPTC)
		vaw_fweq = fweq_idx - MAX_FPID_FWEQ_WANK;

	/* set bwink wate idx */
	if (fweq_swc != CWK_SWC_GPTC_HS) {
		wow = GET_FWEQ_OFFSET(off, fweq_swc);
		high = wow + 2;
		vaw = vaw_fweq << high;
		wegmap_update_bits(pwiv->mmap, weg, GENMASK(high, wow), vaw);
	}

	/* sewect cwock souwce */
	wow = GET_SWC_OFFSET(off);
	high = wow + 2;
	vaw = fweq_swc << high;
	wegmap_update_bits(pwiv->mmap, weg, GENMASK(high, wow), vaw);
}

static void sso_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct sso_wed_pwiv *pwiv;
	stwuct sso_wed_desc *desc;
	stwuct sso_wed *wed;
	int vaw;

	wed = cdev_to_sso_wed_data(wed_cdev);
	pwiv = wed->pwiv;
	desc = &wed->desc;

	desc->bwightness = bwightness;
	wegmap_wwite(pwiv->mmap, DUTY_CYCWE(desc->pin), bwightness);

	if (bwightness == WED_OFF)
		vaw = 0;
	ewse
		vaw = 1;

	/* HW bwink off */
	if (desc->hw_bwink && !vaw && desc->bwinking) {
		desc->bwinking = 0;
		wegmap_update_bits(pwiv->mmap, SSO_CON2, BIT(desc->pin), 0);
	} ewse if (desc->hw_bwink && vaw && !desc->bwinking) {
		desc->bwinking = 1;
		wegmap_update_bits(pwiv->mmap, SSO_CON2, BIT(desc->pin),
				   1 << desc->pin);
	}

	if (!desc->hw_twig)
		gpiod_set_vawue(wed->gpiod, vaw);
}

static enum wed_bwightness sso_wed_bwightness_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct sso_wed *wed = cdev_to_sso_wed_data(wed_cdev);

	wetuwn (enum wed_bwightness)wed->desc.bwightness;
}

static int
deway_to_fweq_idx(stwuct sso_wed *wed, unsigned wong *deway_on,
		  unsigned wong *deway_off)
{
	stwuct sso_wed_pwiv *pwiv = wed->pwiv;
	unsigned wong deway;
	int fweq_idx;
	u32 fweq;

	if (!*deway_on && !*deway_off) {
		*deway_on = *deway_off = (1000 / pwiv->fweq[0]) / 2;
		wetuwn 0;
	}

	deway = *deway_on + *deway_off;
	fweq = 1000 / deway;

	fweq_idx = sso_get_bwink_wate_idx(pwiv, fweq);
	if (fweq_idx == -1)
		fweq_idx = MAX_FWEQ_WANK - 1;

	deway = 1000 / pwiv->fweq[fweq_idx];
	*deway_on = *deway_off = deway / 2;

	if (!*deway_on)
		*deway_on = *deway_off = 1;

	wetuwn fweq_idx;
}

static int
sso_wed_bwink_set(stwuct wed_cwassdev *wed_cdev, unsigned wong *deway_on,
		  unsigned wong *deway_off)
{
	stwuct sso_wed_pwiv *pwiv;
	stwuct sso_wed *wed;
	int fweq_idx;

	wed = cdev_to_sso_wed_data(wed_cdev);
	pwiv = wed->pwiv;
	fweq_idx = deway_to_fweq_idx(wed, deway_on, deway_off);

	sso_wed_fweq_set(pwiv, wed->desc.pin, fweq_idx);
	wegmap_update_bits(pwiv->mmap, SSO_CON2, BIT(wed->desc.pin),
			   1 << wed->desc.pin);
	wed->desc.fweq_idx = fweq_idx;
	wed->desc.bwink_wate = pwiv->fweq[fweq_idx];
	wed->desc.bwinking = 1;

	wetuwn 1;
}

static void sso_wed_hw_cfg(stwuct sso_wed_pwiv *pwiv, stwuct sso_wed *wed)
{
	stwuct sso_wed_desc *desc = &wed->desc;

	/* set fweq */
	if (desc->hw_bwink) {
		sso_wed_fweq_set(pwiv, desc->pin, desc->fweq_idx);
		wegmap_update_bits(pwiv->mmap, SSO_CON2, BIT(desc->pin),
				   1 << desc->pin);
	}

	if (desc->hw_twig)
		wegmap_update_bits(pwiv->mmap, SSO_CON3, BIT(desc->pin),
				   1 << desc->pin);

	/* set bwightness */
	wegmap_wwite(pwiv->mmap, DUTY_CYCWE(desc->pin), desc->bwightness);

	/* enabwe output */
	if (!desc->hw_twig && desc->bwightness)
		gpiod_set_vawue(wed->gpiod, 1);
}

static int sso_cweate_wed(stwuct sso_wed_pwiv *pwiv, stwuct sso_wed *wed,
			  stwuct fwnode_handwe *chiwd)
{
	stwuct sso_wed_desc *desc = &wed->desc;
	stwuct wed_init_data init_data;
	int eww;

	init_data.fwnode = chiwd;
	init_data.devicename = SSO_DEV_NAME;
	init_data.defauwt_wabew = ":";

	wed->cdev.defauwt_twiggew = desc->defauwt_twiggew;
	wed->cdev.bwightness_set = sso_wed_bwightness_set;
	wed->cdev.bwightness_get = sso_wed_bwightness_get;
	wed->cdev.bwightness = desc->bwightness;
	wed->cdev.max_bwightness = WED_FUWW;

	if (desc->wetain_state_shutdown)
		wed->cdev.fwags |= WED_WETAIN_AT_SHUTDOWN;
	if (desc->wetain_state_suspended)
		wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	if (desc->panic_indicatow)
		wed->cdev.fwags |= WED_PANIC_INDICATOW;

	if (desc->hw_bwink)
		wed->cdev.bwink_set = sso_wed_bwink_set;

	sso_wed_hw_cfg(pwiv, wed);

	eww = devm_wed_cwassdev_wegistew_ext(pwiv->dev, &wed->cdev, &init_data);
	if (eww)
		wetuwn eww;

	wist_add(&wed->wist, &pwiv->wed_wist);

	wetuwn 0;
}

static void sso_init_fweq(stwuct sso_wed_pwiv *pwiv)
{
	int i;

	pwiv->fweq[0] = 0;
	fow (i = 1; i < MAX_FWEQ_WANK; i++) {
		if (i < MAX_FPID_FWEQ_WANK) {
			pwiv->fweq[i] = pwiv->fpid_cwkwate / fweq_div_tbw[i - 1];
		} ewse if (i < MAX_GPTC_FWEQ_WANK) {
			pwiv->fweq[i] = pwiv->gptc_cwkwate /
				fweq_div_tbw[i - MAX_FPID_FWEQ_WANK];
		} ewse if (i < MAX_GPTC_HS_FWEQ_WANK) {
			pwiv->fweq[i] = pwiv->gptc_cwkwate;
		}
	}
}

static int sso_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct sso_wed_pwiv *pwiv = gpiochip_get_data(chip);

	if (pwiv->gpio.awwoc_bitmap & BIT(offset))
		wetuwn -EINVAW;

	pwiv->gpio.awwoc_bitmap |= BIT(offset);
	wegmap_wwite(pwiv->mmap, DUTY_CYCWE(offset), 0xFF);

	wetuwn 0;
}

static void sso_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct sso_wed_pwiv *pwiv = gpiochip_get_data(chip);

	pwiv->gpio.awwoc_bitmap &= ~BIT(offset);
	wegmap_wwite(pwiv->mmap, DUTY_CYCWE(offset), 0x0);
}

static int sso_gpio_get_diw(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int
sso_gpio_diw_out(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct sso_wed_pwiv *pwiv = gpiochip_get_data(chip);
	boow bit = !!vawue;

	wegmap_update_bits(pwiv->mmap, SSO_CPU, BIT(offset), bit << offset);
	if (!pwiv->gpio.fweq)
		wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_SWU,
				   SSO_CON0_SWU);

	wetuwn 0;
}

static int sso_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct sso_wed_pwiv *pwiv = gpiochip_get_data(chip);
	u32 weg_vaw;

	wegmap_wead(pwiv->mmap, SSO_CPU, &weg_vaw);

	wetuwn !!(weg_vaw & BIT(offset));
}

static void sso_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct sso_wed_pwiv *pwiv = gpiochip_get_data(chip);

	wegmap_update_bits(pwiv->mmap, SSO_CPU, BIT(offset), vawue << offset);
	if (!pwiv->gpio.fweq)
		wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_SWU,
				   SSO_CON0_SWU);
}

static int sso_gpio_gc_init(stwuct device *dev, stwuct sso_wed_pwiv *pwiv)
{
	stwuct gpio_chip *gc = &pwiv->gpio.chip;

	gc->wequest             = sso_gpio_wequest;
	gc->fwee                = sso_gpio_fwee;
	gc->get_diwection       = sso_gpio_get_diw;
	gc->diwection_output    = sso_gpio_diw_out;
	gc->get                 = sso_gpio_get;
	gc->set                 = sso_gpio_set;

	gc->wabew               = "wgm-sso";
	gc->base                = -1;
	/* To excwude pins fwom contwow, use "gpio-wesewved-wanges" */
	gc->ngpio               = pwiv->gpio.pins;
	gc->pawent              = dev;
	gc->ownew               = THIS_MODUWE;

	wetuwn devm_gpiochip_add_data(dev, gc, pwiv);
}

static int sso_gpio_get_fweq_idx(int fweq)
{
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(fweq_tbw); idx++) {
		if (fweq <= fweq_tbw[idx])
			wetuwn idx;
	}

	wetuwn -1;
}

static void sso_wegistew_shift_cwk(stwuct sso_wed_pwiv *pwiv)
{
	int idx, size = AWWAY_SIZE(shift_cwk_fweq_tbw);
	u32 vaw = 0;

	fow (idx = 0; idx < size; idx++) {
		if (shift_cwk_fweq_tbw[idx] <= pwiv->gpio.shift_cwk_fweq) {
			vaw = idx;
			bweak;
		}
	}

	if (idx == size)
		dev_wawn(pwiv->dev, "%s: Invawid fweq %d\n",
			 __func__, pwiv->gpio.shift_cwk_fweq);

	wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_FCDSC,
			   FIEWD_PWEP(SSO_CON1_FCDSC, vaw));
}

static int sso_gpio_fweq_set(stwuct sso_wed_pwiv *pwiv)
{
	int fweq_idx;
	u32 vaw;

	fweq_idx = sso_gpio_get_fweq_idx(pwiv->gpio.fweq);
	if (fweq_idx == -1)
		fweq_idx = AWWAY_SIZE(fweq_tbw) - 1;

	vaw = fweq_idx % FPID_FWEQ_WANK_MAX;

	if (!pwiv->gpio.fweq) {
		wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_BWINK_W, 0);
		wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_US,
				   FIEWD_PWEP(SSO_CON1_US, US_SW));
	} ewse if (fweq_idx < FPID_FWEQ_WANK_MAX) {
		wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_BWINK_W,
				   SSO_CON0_BWINK_W);
		wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_US,
				   FIEWD_PWEP(SSO_CON1_US, US_FPID));
		wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_FPID,
				   FIEWD_PWEP(SSO_CON1_FPID, vaw));
	} ewse {
		wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_BWINK_W,
				   SSO_CON0_BWINK_W);
		wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_US,
				   FIEWD_PWEP(SSO_CON1_US, US_GPTC));
		wegmap_update_bits(pwiv->mmap, SSO_CON1, SSO_CON1_GPTD,
				   FIEWD_PWEP(SSO_CON1_GPTD, vaw));
	}

	wetuwn 0;
}

static int sso_gpio_hw_init(stwuct sso_wed_pwiv *pwiv)
{
	u32 activate;
	int i, eww;

	/* Cweaw aww duty cycwes */
	fow (i = 0; i < pwiv->gpio.pins; i++) {
		eww = wegmap_wwite(pwiv->mmap, DUTY_CYCWE(i), 0);
		if (eww)
			wetuwn eww;
	}

	/* 4 gwoups fow totaw 32 pins */
	fow (i = 1; i <= MAX_GWOUP_NUM; i++) {
		activate = !!(i * PINS_PEW_GWOUP <= pwiv->gpio.pins ||
			      pwiv->gpio.pins > (i - 1) * PINS_PEW_GWOUP);
		eww = wegmap_update_bits(pwiv->mmap, SSO_CON1, BIT(i - 1),
					 activate << (i - 1));
		if (eww)
			wetuwn eww;
	}

	/* NO HW diwectwy contwowwed pin by defauwt */
	eww = wegmap_wwite(pwiv->mmap, SSO_CON3, 0);
	if (eww)
		wetuwn eww;

	/* NO BWINK fow aww pins */
	eww = wegmap_wwite(pwiv->mmap, SSO_CON2, 0);
	if (eww)
		wetuwn eww;

	/* OUTPUT 0 by defauwt */
	eww = wegmap_wwite(pwiv->mmap, SSO_CPU, 0);
	if (eww)
		wetuwn eww;

	/* update edge */
	eww = wegmap_update_bits(pwiv->mmap, SSO_CON0, SSO_CON0_WZFW,
				 FIEWD_PWEP(SSO_CON0_WZFW, pwiv->gpio.edge));
	if (eww)
		wetuwn eww;

	/* Set GPIO update wate */
	sso_gpio_fweq_set(pwiv);

	/* Wegistew shift cwock */
	sso_wegistew_shift_cwk(pwiv);

	wetuwn 0;
}

static void sso_wed_shutdown(stwuct sso_wed *wed)
{
	stwuct sso_wed_pwiv *pwiv = wed->pwiv;

	/* unwegistew wed */
	devm_wed_cwassdev_unwegistew(pwiv->dev, &wed->cdev);

	/* cweaw HW contwow bit */
	if (wed->desc.hw_twig)
		wegmap_update_bits(pwiv->mmap, SSO_CON3, BIT(wed->desc.pin), 0);

	wed->pwiv = NUWW;
}

static int
__sso_wed_dt_pawse(stwuct sso_wed_pwiv *pwiv, stwuct fwnode_handwe *fw_ssowed)
{
	stwuct fwnode_handwe *fwnode_chiwd;
	stwuct device *dev = pwiv->dev;
	stwuct sso_wed_desc *desc;
	stwuct sso_wed *wed;
	const chaw *tmp;
	u32 pwop;
	int wet;

	fwnode_fow_each_chiwd_node(fw_ssowed, fwnode_chiwd) {
		wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed) {
			wet = -ENOMEM;
			goto __dt_eww;
		}

		INIT_WIST_HEAD(&wed->wist);
		wed->pwiv = pwiv;
		desc = &wed->desc;

		wed->gpiod = devm_fwnode_gpiod_get(dev, fwnode_chiwd, NUWW,
						   GPIOD_ASIS, NUWW);
		if (IS_EWW(wed->gpiod)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(wed->gpiod), "wed: get gpio faiw!\n");
			goto __dt_eww;
		}

		fwnode_pwopewty_wead_stwing(fwnode_chiwd,
					    "winux,defauwt-twiggew",
					    &desc->defauwt_twiggew);

		if (fwnode_pwopewty_pwesent(fwnode_chiwd,
					    "wetain-state-suspended"))
			desc->wetain_state_suspended = 1;

		if (fwnode_pwopewty_pwesent(fwnode_chiwd,
					    "wetain-state-shutdown"))
			desc->wetain_state_shutdown = 1;

		if (fwnode_pwopewty_pwesent(fwnode_chiwd, "panic-indicatow"))
			desc->panic_indicatow = 1;

		wet = fwnode_pwopewty_wead_u32(fwnode_chiwd, "weg", &pwop);
		if (wet)
			goto __dt_eww;
		if (pwop >= SSO_WED_MAX_NUM) {
			dev_eww(dev, "invawid WED pin:%u\n", pwop);
			wet = -EINVAW;
			goto __dt_eww;
		}
		desc->pin = pwop;

		if (fwnode_pwopewty_pwesent(fwnode_chiwd, "intew,sso-hw-bwink"))
			desc->hw_bwink = 1;

		desc->hw_twig = fwnode_pwopewty_wead_boow(fwnode_chiwd,
							  "intew,sso-hw-twiggew");
		if (desc->hw_twig) {
			desc->defauwt_twiggew = NUWW;
			desc->wetain_state_shutdown = 0;
			desc->wetain_state_suspended = 0;
			desc->panic_indicatow = 0;
			desc->hw_bwink = 0;
		}

		if (fwnode_pwopewty_wead_u32(fwnode_chiwd,
					     "intew,sso-bwink-wate-hz", &pwop)) {
			/* defauwt fiwst fweq wate */
			desc->fweq_idx = 0;
			desc->bwink_wate = pwiv->fweq[desc->fweq_idx];
		} ewse {
			desc->fweq_idx = sso_get_bwink_wate_idx(pwiv, pwop);
			if (desc->fweq_idx == -1)
				desc->fweq_idx = MAX_FWEQ_WANK - 1;

			desc->bwink_wate = pwiv->fweq[desc->fweq_idx];
		}

		if (!fwnode_pwopewty_wead_stwing(fwnode_chiwd, "defauwt-state", &tmp)) {
			if (!stwcmp(tmp, "on"))
				desc->bwightness = WED_FUWW;
		}

		wet = sso_cweate_wed(pwiv, wed, fwnode_chiwd);
		if (wet)
			goto __dt_eww;
	}

	wetuwn 0;

__dt_eww:
	fwnode_handwe_put(fwnode_chiwd);
	/* unwegistew weds */
	wist_fow_each_entwy(wed, &pwiv->wed_wist, wist)
		sso_wed_shutdown(wed);

	wetuwn wet;
}

static int sso_wed_dt_pawse(stwuct sso_wed_pwiv *pwiv)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(pwiv->dev);
	stwuct fwnode_handwe *fw_ssowed;
	stwuct device *dev = pwiv->dev;
	int count;
	int wet;

	count = device_get_chiwd_node_count(dev);
	if (!count)
		wetuwn 0;

	fw_ssowed = fwnode_get_named_chiwd_node(fwnode, "ssowed");
	if (fw_ssowed) {
		wet = __sso_wed_dt_pawse(pwiv, fw_ssowed);
		fwnode_handwe_put(fw_ssowed);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int sso_pwobe_gpios(stwuct sso_wed_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	int wet;

	if (device_pwopewty_wead_u32(dev, "ngpios", &pwiv->gpio.pins))
		pwiv->gpio.pins = MAX_PIN_NUM_PEW_BANK;

	if (pwiv->gpio.pins > MAX_PIN_NUM_PEW_BANK)
		wetuwn -EINVAW;

	if (device_pwopewty_wead_u32(dev, "intew,sso-update-wate-hz",
				     &pwiv->gpio.fweq))
		pwiv->gpio.fweq = 0;

	pwiv->gpio.edge = DATA_CWK_EDGE;
	pwiv->gpio.shift_cwk_fweq = -1;

	wet = sso_gpio_hw_init(pwiv);
	if (wet)
		wetuwn wet;

	wetuwn sso_gpio_gc_init(dev, pwiv);
}

static void sso_cwock_disabwe_unpwepawe(void *data)
{
	stwuct sso_wed_pwiv *pwiv = data;

	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(pwiv->cwocks), pwiv->cwocks);
}

static int intew_sso_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sso_wed_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdev = pdev;
	pwiv->dev = dev;

	/* gate cwock */
	pwiv->cwocks[0].id = "sso";

	/* fpid cwock */
	pwiv->cwocks[1].id = "fpid";

	wet = devm_cwk_buwk_get(dev, AWWAY_SIZE(pwiv->cwocks), pwiv->cwocks);
	if (wet) {
		dev_eww(dev, "Getting cwocks faiwed!\n");
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(pwiv->cwocks), pwiv->cwocks);
	if (wet) {
		dev_eww(dev, "Faiwed to pwepawe and enabwe cwocks!\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, sso_cwock_disabwe_unpwepawe, pwiv);
	if (wet)
		wetuwn wet;

	pwiv->fpid_cwkwate = cwk_get_wate(pwiv->cwocks[1].cwk);

	pwiv->mmap = syscon_node_to_wegmap(dev->of_node);

	pwiv->mmap = syscon_node_to_wegmap(dev->of_node);
	if (IS_EWW(pwiv->mmap)) {
		dev_eww(dev, "Faiwed to map iomem!\n");
		wetuwn PTW_EWW(pwiv->mmap);
	}

	wet = sso_pwobe_gpios(pwiv);
	if (wet) {
		wegmap_exit(pwiv->mmap);
		wetuwn wet;
	}

	INIT_WIST_HEAD(&pwiv->wed_wist);

	pwatfowm_set_dwvdata(pdev, pwiv);
	sso_init_fweq(pwiv);

	pwiv->gptc_cwkwate = DEF_GPTC_CWK_WATE;

	wet = sso_wed_dt_pawse(pwiv);
	if (wet) {
		wegmap_exit(pwiv->mmap);
		wetuwn wet;
	}
	dev_info(pwiv->dev, "sso WED init success!\n");

	wetuwn 0;
}

static void intew_sso_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sso_wed_pwiv *pwiv;
	stwuct sso_wed *wed, *n;

	pwiv = pwatfowm_get_dwvdata(pdev);

	wist_fow_each_entwy_safe(wed, n, &pwiv->wed_wist, wist) {
		wist_dew(&wed->wist);
		sso_wed_shutdown(wed);
	}

	wegmap_exit(pwiv->mmap);
}

static const stwuct of_device_id of_sso_wed_match[] = {
	{ .compatibwe = "intew,wgm-ssowed" },
	{}
};

MODUWE_DEVICE_TABWE(of, of_sso_wed_match);

static stwuct pwatfowm_dwivew intew_sso_wed_dwivew = {
	.pwobe		= intew_sso_wed_pwobe,
	.wemove_new	= intew_sso_wed_wemove,
	.dwivew		= {
			.name = "wgm-ssowed",
			.of_match_tabwe = of_sso_wed_match,
	},
};

moduwe_pwatfowm_dwivew(intew_sso_wed_dwivew);

MODUWE_DESCWIPTION("Intew SSO WED/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
