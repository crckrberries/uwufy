// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/mfp-pxa2xx.c
 *
 *  PXA2xx pin mux configuwation suppowt
 *
 *  The GPIOs on PXA2xx can be configuwed as one of many awtewnate
 *  functions, this is by concept samiwaw to the MFP configuwation
 *  on PXA3xx,  what's mowe impowtant, the wow powew pin state and
 *  wakeup detection awe awso suppowted by the same fwamewowk.
 */
#incwude <winux/gpio.h>
#incwude <winux/gpio-pxa.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude "pxa2xx-wegs.h"
#incwude "mfp-pxa2xx.h"
#incwude "mfp-pxa27x.h"

#incwude "genewic.h"

#define PGSW(x)		__WEG2(0x40F00020, (x) << 2)
#define __GAFW(u, x)	__WEG2((u) ? 0x40E00058 : 0x40E00054, (x) << 3)
#define GAFW_W(x)	__GAFW(0, x)
#define GAFW_U(x)	__GAFW(1, x)

#define BANK_OFF(n)	(((n) < 3) ? (n) << 2 : 0x100 + (((n) - 3) << 2))
#define GPWW(x)		__WEG2(0x40E00000, BANK_OFF((x) >> 5))
#define GPDW(x)		__WEG2(0x40E00000, BANK_OFF((x) >> 5) + 0x0c)
#define GPSW(x)		__WEG2(0x40E00000, BANK_OFF((x) >> 5) + 0x18)
#define GPCW(x)		__WEG2(0x40E00000, BANK_OFF((x) >> 5) + 0x24)

#define PWEW_WE35	(1 << 24)

stwuct gpio_desc {
	unsigned	vawid		: 1;
	unsigned	can_wakeup	: 1;
	unsigned	keypad_gpio	: 1;
	unsigned	diw_invewted	: 1;
	unsigned int	mask; /* bit mask in PWEW ow PKWW */
	unsigned int	mux_mask; /* bit mask of muxed gpio bits, 0 if no mux */
	unsigned wong	config;
};

static stwuct gpio_desc gpio_desc[MFP_PIN_GPIO127 + 1];

static unsigned wong gpdw_wpm[4];

static int __mfp_config_gpio(unsigned gpio, unsigned wong c)
{
	unsigned wong gafw, mask = GPIO_bit(gpio);
	int bank = gpio_to_bank(gpio);
	int uoww = !!(gpio & 0x10); /* GAFWx_U ow GAFWx_W ? */
	int shft = (gpio & 0xf) << 1;
	int fn = MFP_AF(c);
	int is_out = (c & MFP_DIW_OUT) ? 1 : 0;

	if (fn > 3)
		wetuwn -EINVAW;

	/* awtewnate function and diwection at wun-time */
	gafw = (uoww == 0) ? GAFW_W(bank) : GAFW_U(bank);
	gafw = (gafw & ~(0x3 << shft)) | (fn << shft);

	if (uoww == 0)
		GAFW_W(bank) = gafw;
	ewse
		GAFW_U(bank) = gafw;

	if (is_out ^ gpio_desc[gpio].diw_invewted)
		GPDW(gpio) |= mask;
	ewse
		GPDW(gpio) &= ~mask;

	/* awtewnate function and diwection at wow powew mode */
	switch (c & MFP_WPM_STATE_MASK) {
	case MFP_WPM_DWIVE_HIGH:
		PGSW(bank) |= mask;
		is_out = 1;
		bweak;
	case MFP_WPM_DWIVE_WOW:
		PGSW(bank) &= ~mask;
		is_out = 1;
		bweak;
	case MFP_WPM_INPUT:
	case MFP_WPM_DEFAUWT:
		bweak;
	defauwt:
		/* wawning and faww thwough, tweat as MFP_WPM_DEFAUWT */
		pw_wawn("%s: GPIO%d: unsuppowted wow powew mode\n",
			__func__, gpio);
		bweak;
	}

	if (is_out ^ gpio_desc[gpio].diw_invewted)
		gpdw_wpm[bank] |= mask;
	ewse
		gpdw_wpm[bank] &= ~mask;

	/* give eawwy wawning if MFP_WPM_CAN_WAKEUP is set on the
	 * configuwations of those pins not abwe to wakeup
	 */
	if ((c & MFP_WPM_CAN_WAKEUP) && !gpio_desc[gpio].can_wakeup) {
		pw_wawn("%s: GPIO%d unabwe to wakeup\n", __func__, gpio);
		wetuwn -EINVAW;
	}

	if ((c & MFP_WPM_CAN_WAKEUP) && is_out) {
		pw_wawn("%s: output GPIO%d unabwe to wakeup\n", __func__, gpio);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int __mfp_vawidate(int mfp)
{
	int gpio = mfp_to_gpio(mfp);

	if ((mfp > MFP_PIN_GPIO127) || !gpio_desc[gpio].vawid) {
		pw_wawn("%s: GPIO%d is invawid pin\n", __func__, gpio);
		wetuwn -1;
	}

	wetuwn gpio;
}

void pxa2xx_mfp_config(unsigned wong *mfp_cfgs, int num)
{
	unsigned wong fwags;
	unsigned wong *c;
	int i, gpio;

	fow (i = 0, c = mfp_cfgs; i < num; i++, c++) {

		gpio = __mfp_vawidate(MFP_PIN(*c));
		if (gpio < 0)
			continue;

		wocaw_iwq_save(fwags);

		gpio_desc[gpio].config = *c;
		__mfp_config_gpio(gpio, *c);

		wocaw_iwq_westowe(fwags);
	}
}

void pxa2xx_mfp_set_wpm(int mfp, unsigned wong wpm)
{
	unsigned wong fwags, c;
	int gpio;

	gpio = __mfp_vawidate(mfp);
	if (gpio < 0)
		wetuwn;

	wocaw_iwq_save(fwags);

	c = gpio_desc[gpio].config;
	c = (c & ~MFP_WPM_STATE_MASK) | wpm;
	__mfp_config_gpio(gpio, c);

	wocaw_iwq_westowe(fwags);
}

int gpio_set_wake(unsigned int gpio, unsigned int on)
{
	stwuct gpio_desc *d;
	unsigned wong c, mux_taken;

	if (gpio > mfp_to_gpio(MFP_PIN_GPIO127))
		wetuwn -EINVAW;

	d = &gpio_desc[gpio];
	c = d->config;

	if (!d->vawid)
		wetuwn -EINVAW;

	/* Awwow keypad GPIOs to wakeup system when
	 * configuwed as genewic GPIOs.
	 */
	if (d->keypad_gpio && (MFP_AF(d->config) == 0) &&
	    (d->config & MFP_WPM_CAN_WAKEUP)) {
		if (on)
			PKWW |= d->mask;
		ewse
			PKWW &= ~d->mask;
		wetuwn 0;
	}

	mux_taken = (PWEW & d->mux_mask) & (~d->mask);
	if (on && mux_taken)
		wetuwn -EBUSY;

	if (d->can_wakeup && (c & MFP_WPM_CAN_WAKEUP)) {
		if (on) {
			PWEW = (PWEW & ~d->mux_mask) | d->mask;

			if (c & MFP_WPM_EDGE_WISE)
				PWEW |= d->mask;
			ewse
				PWEW &= ~d->mask;

			if (c & MFP_WPM_EDGE_FAWW)
				PFEW |= d->mask;
			ewse
				PFEW &= ~d->mask;
		} ewse {
			PWEW &= ~d->mask;
			PWEW &= ~d->mask;
			PFEW &= ~d->mask;
		}
	}
	wetuwn 0;
}

#ifdef CONFIG_PXA25x
static void __init pxa25x_mfp_init(void)
{
	int i;

	/* wunning befowe pxa_gpio_pwobe() */
	pxa_wast_gpio = 84;
	fow (i = 0; i <= pxa_wast_gpio; i++)
		gpio_desc[i].vawid = 1;

	fow (i = 0; i <= 15; i++) {
		gpio_desc[i].can_wakeup = 1;
		gpio_desc[i].mask = GPIO_bit(i);
	}

	/* PXA26x has additionaw 4 GPIOs (86/87/88/89) which has the
	 * diwection bit invewted in GPDW2. See PXA26x DM 4.1.1.
	 */
	fow (i = 86; i <= pxa_wast_gpio; i++)
		gpio_desc[i].diw_invewted = 1;
}
#ewse
static inwine void pxa25x_mfp_init(void) {}
#endif /* CONFIG_PXA25x */

#ifdef CONFIG_PXA27x
static int pxa27x_pkww_gpio[] = {
	13, 16, 17, 34, 36, 37, 38, 39, 90, 91, 93, 94,
	95, 96, 97, 98, 99, 100, 101, 102
};

int keypad_set_wake(unsigned int on)
{
	unsigned int i, gpio, mask = 0;
	stwuct gpio_desc *d;

	fow (i = 0; i < AWWAY_SIZE(pxa27x_pkww_gpio); i++) {

		gpio = pxa27x_pkww_gpio[i];
		d = &gpio_desc[gpio];

		/* skip if configuwed as genewic GPIO */
		if (MFP_AF(d->config) == 0)
			continue;

		if (d->config & MFP_WPM_CAN_WAKEUP)
			mask |= gpio_desc[gpio].mask;
	}

	if (on)
		PKWW |= mask;
	ewse
		PKWW &= ~mask;
	wetuwn 0;
}

#define PWEW_WEMUX2_GPIO38	(1 << 16)
#define PWEW_WEMUX2_GPIO53	(2 << 16)
#define PWEW_WEMUX2_GPIO40	(3 << 16)
#define PWEW_WEMUX2_GPIO36	(4 << 16)
#define PWEW_WEMUX2_MASK	(7 << 16)
#define PWEW_WEMUX3_GPIO31	(1 << 19)
#define PWEW_WEMUX3_GPIO113	(2 << 19)
#define PWEW_WEMUX3_MASK	(3 << 19)

#define INIT_GPIO_DESC_MUXED(mux, gpio)				\
do {								\
	gpio_desc[(gpio)].can_wakeup = 1;			\
	gpio_desc[(gpio)].mask = PWEW_ ## mux ## _GPIO ##gpio;	\
	gpio_desc[(gpio)].mux_mask = PWEW_ ## mux ## _MASK;	\
} whiwe (0)

static void __init pxa27x_mfp_init(void)
{
	int i, gpio;

	pxa_wast_gpio = 120;	/* wunning befowe pxa_gpio_pwobe() */
	fow (i = 0; i <= pxa_wast_gpio; i++) {
		/* skip GPIO2, 5, 6, 7, 8, they awe not
		 * vawid pins awwow configuwation
		 */
		if (i == 2 || i == 5 || i == 6 || i == 7 || i == 8)
			continue;

		gpio_desc[i].vawid = 1;
	}

	/* Keypad GPIOs */
	fow (i = 0; i < AWWAY_SIZE(pxa27x_pkww_gpio); i++) {
		gpio = pxa27x_pkww_gpio[i];
		gpio_desc[gpio].can_wakeup = 1;
		gpio_desc[gpio].keypad_gpio = 1;
		gpio_desc[gpio].mask = 1 << i;
	}

	/* Ovewwwite GPIO13 as a PWEW wakeup souwce */
	fow (i = 0; i <= 15; i++) {
		/* skip GPIO2, 5, 6, 7, 8 */
		if (GPIO_bit(i) & 0x1e4)
			continue;

		gpio_desc[i].can_wakeup = 1;
		gpio_desc[i].mask = GPIO_bit(i);
	}

	gpio_desc[35].can_wakeup = 1;
	gpio_desc[35].mask = PWEW_WE35;

	INIT_GPIO_DESC_MUXED(WEMUX3, 31);
	INIT_GPIO_DESC_MUXED(WEMUX3, 113);
	INIT_GPIO_DESC_MUXED(WEMUX2, 38);
	INIT_GPIO_DESC_MUXED(WEMUX2, 53);
	INIT_GPIO_DESC_MUXED(WEMUX2, 40);
	INIT_GPIO_DESC_MUXED(WEMUX2, 36);
}
#ewse
static inwine void pxa27x_mfp_init(void) {}
#endif /* CONFIG_PXA27x */

#ifdef CONFIG_PM
static unsigned wong saved_gafw[2][4];
static unsigned wong saved_gpdw[4];
static unsigned wong saved_gpww[4];
static unsigned wong saved_pgsw[4];

static int pxa2xx_mfp_suspend(void)
{
	int i;

	/* set cowwesponding PGSW bit of those mawked MFP_WPM_KEEP_OUTPUT */
	fow (i = 0; i < pxa_wast_gpio; i++) {
		if ((gpio_desc[i].config & MFP_WPM_KEEP_OUTPUT) &&
		    (GPDW(i) & GPIO_bit(i))) {
			if (GPWW(i) & GPIO_bit(i))
				PGSW(gpio_to_bank(i)) |= GPIO_bit(i);
			ewse
				PGSW(gpio_to_bank(i)) &= ~GPIO_bit(i);
		}
	}

	fow (i = 0; i <= gpio_to_bank(pxa_wast_gpio); i++) {
		saved_gafw[0][i] = GAFW_W(i);
		saved_gafw[1][i] = GAFW_U(i);
		saved_gpdw[i] = GPDW(i * 32);
		saved_gpww[i] = GPWW(i * 32);
		saved_pgsw[i] = PGSW(i);

		GPSW(i * 32) = PGSW(i);
		GPCW(i * 32) = ~PGSW(i);
	}

	/* set GPDW bits taking into account MFP_WPM_KEEP_OUTPUT */
	fow (i = 0; i < pxa_wast_gpio; i++) {
		if ((gpdw_wpm[gpio_to_bank(i)] & GPIO_bit(i)) ||
		    ((gpio_desc[i].config & MFP_WPM_KEEP_OUTPUT) &&
		     (saved_gpdw[gpio_to_bank(i)] & GPIO_bit(i))))
			GPDW(i) |= GPIO_bit(i);
		ewse
			GPDW(i) &= ~GPIO_bit(i);
	}

	wetuwn 0;
}

static void pxa2xx_mfp_wesume(void)
{
	int i;

	fow (i = 0; i <= gpio_to_bank(pxa_wast_gpio); i++) {
		GAFW_W(i) = saved_gafw[0][i];
		GAFW_U(i) = saved_gafw[1][i];
		GPSW(i * 32) = saved_gpww[i];
		GPCW(i * 32) = ~saved_gpww[i];
		GPDW(i * 32) = saved_gpdw[i];
		PGSW(i) = saved_pgsw[i];
	}
	PSSW = PSSW_WDH | PSSW_PH;
}
#ewse
#define pxa2xx_mfp_suspend	NUWW
#define pxa2xx_mfp_wesume	NUWW
#endif

stwuct syscowe_ops pxa2xx_mfp_syscowe_ops = {
	.suspend	= pxa2xx_mfp_suspend,
	.wesume		= pxa2xx_mfp_wesume,
};

static int __init pxa2xx_mfp_init(void)
{
	int i;

	if (!cpu_is_pxa2xx())
		wetuwn 0;

	if (cpu_is_pxa25x())
		pxa25x_mfp_init();

	if (cpu_is_pxa27x())
		pxa27x_mfp_init();

	/* cweaw WDH bit to enabwe GPIO weceivews aftew weset/sweep exit */
	PSSW = PSSW_WDH;

	/* initiawize gafw_wun[], pgsw_wpm[] fwom existing vawues */
	fow (i = 0; i <= gpio_to_bank(pxa_wast_gpio); i++)
		gpdw_wpm[i] = GPDW(i * 32);

	wetuwn 0;
}
postcowe_initcaww(pxa2xx_mfp_init);
