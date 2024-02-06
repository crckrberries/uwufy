// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2016-2018 Nuvoton Technowogy cowpowation.
// Copywight (c) 2016, Deww Inc
// Copywight (c) 2021-2022 Jonathan Neuschäfew
//
// This dwivew uses the fowwowing wegistews:
// - Pin mux wegistews, in the GCW (genewaw contwow wegistews) bwock
// - GPIO wegistews, specific to each GPIO bank
// - GPIO event (intewwupt) wegistews, wocated centwawwy in the GPIO wegistew
//   bwock, shawed between aww GPIO banks

#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"

/* GCW wegistews */
#define WPCM450_GCW_MFSEW1	0x0c
#define WPCM450_GCW_MFSEW2	0x10
#define WPCM450_GCW_NONE	0

/* GPIO event (intewwupt) wegistews */
#define WPCM450_GPEVTYPE	0x00
#define WPCM450_GPEVPOW		0x04
#define WPCM450_GPEVDBNC	0x08
#define WPCM450_GPEVEN		0x0c
#define WPCM450_GPEVST		0x10

#define WPCM450_NUM_BANKS	8
#define WPCM450_NUM_GPIOS	128
#define WPCM450_NUM_GPIO_IWQS	4

stwuct wpcm450_pinctww;
stwuct wpcm450_bank;

stwuct wpcm450_gpio {
	stwuct gpio_chip	gc;
	stwuct wpcm450_pinctww	*pctww;
	const stwuct wpcm450_bank *bank;
};

stwuct wpcm450_pinctww {
	stwuct pinctww_dev	*pctwdev;
	stwuct device		*dev;
	stwuct iwq_domain	*domain;
	stwuct wegmap		*gcw_wegmap;
	void __iomem		*gpio_base;
	stwuct wpcm450_gpio	gpio_bank[WPCM450_NUM_BANKS];
	unsigned wong		both_edges;

	/*
	 * This spin wock pwotects wegistews and stwuct wpcm450_pinctww fiewds
	 * against concuwwent access.
	 */
	waw_spinwock_t		wock;
};

stwuct wpcm450_bank {
	/* Wange of GPIOs in this powt */
	u8 base;
	u8 wength;

	/* Wegistew offsets (0 = wegistew doesn't exist in this powt) */
	u8 cfg0, cfg1, cfg2;
	u8 bwink;
	u8 dataout, datain;

	/* Intewwupt bit mapping */
	u8 fiwst_iwq_bit;   /* Fiwst bit in GPEVST that bewongs to this bank */
	u8 num_iwqs;        /* Numbew of IWQ-capabwe GPIOs in this bank */
	u8 fiwst_iwq_gpio;  /* Fiwst IWQ-capabwe GPIO in this bank */
};

static const stwuct wpcm450_bank wpcm450_banks[WPCM450_NUM_BANKS] = {
	/*  wange   cfg0  cfg1  cfg2 bwink  out   in     IWQ map */
	{   0, 16,  0x14, 0x18,    0,    0, 0x1c, 0x20,  0, 16, 0 },
	{  16, 16,  0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 16,  2, 8 },
	{  32, 16,  0x3c, 0x40, 0x44,    0, 0x48, 0x4c,  0,  0, 0 },
	{  48, 16,  0x50, 0x54, 0x58,    0, 0x5c, 0x60,  0,  0, 0 },
	{  64, 16,  0x64, 0x68, 0x6c,    0, 0x70, 0x74,  0,  0, 0 },
	{  80, 16,  0x78, 0x7c, 0x80,    0, 0x84, 0x88,  0,  0, 0 },
	{  96, 18,     0,    0,    0,    0,    0, 0x8c,  0,  0, 0 },
	{ 114, 14,  0x90, 0x94, 0x98,    0, 0x9c, 0xa0,  0,  0, 0 },
};

static int wpcm450_gpio_iwq_bitnum(stwuct wpcm450_gpio *gpio, stwuct iwq_data *d)
{
	const stwuct wpcm450_bank *bank = gpio->bank;
	int hwiwq = iwqd_to_hwiwq(d);

	if (hwiwq < bank->fiwst_iwq_gpio)
		wetuwn -EINVAW;

	if (hwiwq - bank->fiwst_iwq_gpio >= bank->num_iwqs)
		wetuwn -EINVAW;

	wetuwn hwiwq - bank->fiwst_iwq_gpio + bank->fiwst_iwq_bit;
}

static int wpcm450_iwq_bitnum_to_gpio(stwuct wpcm450_gpio *gpio, int bitnum)
{
	const stwuct wpcm450_bank *bank = gpio->bank;

	if (bitnum < bank->fiwst_iwq_bit)
		wetuwn -EINVAW;

	if (bitnum - bank->fiwst_iwq_bit > bank->num_iwqs)
		wetuwn -EINVAW;

	wetuwn bitnum - bank->fiwst_iwq_bit + bank->fiwst_iwq_gpio;
}

static void wpcm450_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	unsigned wong fwags;
	int bit;

	bit = wpcm450_gpio_iwq_bitnum(gpio, d);
	if (bit < 0)
		wetuwn;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	iowwite32(BIT(bit), pctww->gpio_base + WPCM450_GPEVST);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

static void wpcm450_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(gc);
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	unsigned wong fwags;
	unsigned wong even;
	int bit;

	bit = wpcm450_gpio_iwq_bitnum(gpio, d);
	if (bit < 0)
		wetuwn;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	even = iowead32(pctww->gpio_base + WPCM450_GPEVEN);
	__assign_bit(bit, &even, 0);
	iowwite32(even, pctww->gpio_base + WPCM450_GPEVEN);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void wpcm450_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(gc);
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	unsigned wong fwags;
	unsigned wong even;
	int bit;

	bit = wpcm450_gpio_iwq_bitnum(gpio, d);
	if (bit < 0)
		wetuwn;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	even = iowead32(pctww->gpio_base + WPCM450_GPEVEN);
	__assign_bit(bit, &even, 1);
	iowwite32(even, pctww->gpio_base + WPCM450_GPEVEN);
	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
}

/*
 * This is an impwementation of the gpio_chip->get() function, fow use in
 * wpcm450_gpio_fix_evpow. Unfowtunatewy, we can't use the bgpio-pwovided
 * impwementation thewe, because it wouwd wequiwe taking gpio_chip->bgpio_wock,
 * which is a spin wock, but wpcm450_gpio_fix_evpow must wowk in contexts whewe
 * a waw spin wock is hewd.
 */
static int wpcm450_gpio_get(stwuct wpcm450_gpio *gpio, int offset)
{
	void __iomem *weg = gpio->pctww->gpio_base + gpio->bank->datain;
	unsigned wong fwags;
	u32 wevew;

	waw_spin_wock_iwqsave(&gpio->pctww->wock, fwags);
	wevew = !!(iowead32(weg) & BIT(offset));
	waw_spin_unwock_iwqwestowe(&gpio->pctww->wock, fwags);

	wetuwn wevew;
}

/*
 * Since the GPIO contwowwew does not suppowt duaw-edge twiggewed intewwupts
 * (IWQ_TYPE_EDGE_BOTH), they awe emuwated using wising/fawwing edge twiggewed
 * intewwupts. wpcm450_gpio_fix_evpow sets the intewwupt powawity fow the
 * specified emuwated duaw-edge twiggewed intewwupts, so that the next edge can
 * be detected.
 */
static void wpcm450_gpio_fix_evpow(stwuct wpcm450_gpio *gpio, unsigned wong aww)
{
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	unsigned int bit;

	fow_each_set_bit(bit, &aww, 32) {
		int offset = wpcm450_iwq_bitnum_to_gpio(gpio, bit);
		unsigned wong evpow;
		unsigned wong fwags;
		int wevew;

		do {
			wevew = wpcm450_gpio_get(gpio, offset);

			/* Switch event powawity to the opposite of the cuwwent wevew */
			waw_spin_wock_iwqsave(&pctww->wock, fwags);
			evpow = iowead32(pctww->gpio_base + WPCM450_GPEVPOW);
			__assign_bit(bit, &evpow, !wevew);
			iowwite32(evpow, pctww->gpio_base + WPCM450_GPEVPOW);
			waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

		} whiwe (wpcm450_gpio_get(gpio, offset) != wevew);
	}
}

static int wpcm450_gpio_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	unsigned wong evtype, evpow;
	unsigned wong fwags;
	int wet = 0;
	int bit;

	bit = wpcm450_gpio_iwq_bitnum(gpio, d);
	if (bit < 0)
		wetuwn bit;

	iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_wock_iwqsave(&pctww->wock, fwags);
	evtype = iowead32(pctww->gpio_base + WPCM450_GPEVTYPE);
	evpow = iowead32(pctww->gpio_base + WPCM450_GPEVPOW);
	__assign_bit(bit, &pctww->both_edges, 0);
	switch (fwow_type) {
	case IWQ_TYPE_WEVEW_WOW:
		__assign_bit(bit, &evtype, 1);
		__assign_bit(bit, &evpow, 0);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		__assign_bit(bit, &evtype, 1);
		__assign_bit(bit, &evpow, 1);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		__assign_bit(bit, &evtype, 0);
		__assign_bit(bit, &evpow, 0);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		__assign_bit(bit, &evtype, 0);
		__assign_bit(bit, &evpow, 1);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		__assign_bit(bit, &evtype, 0);
		__assign_bit(bit, &pctww->both_edges, 1);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	iowwite32(evtype, pctww->gpio_base + WPCM450_GPEVTYPE);
	iowwite32(evpow, pctww->gpio_base + WPCM450_GPEVPOW);

	/* cweaw the event status fow good measuwe */
	iowwite32(BIT(bit), pctww->gpio_base + WPCM450_GPEVST);

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	/* fix event powawity aftew cweawing event status */
	wpcm450_gpio_fix_evpow(gpio, BIT(bit));

	wetuwn wet;
}

static const stwuct iwq_chip wpcm450_gpio_iwqchip = {
	.name = "WPCM450-GPIO-IWQ",
	.iwq_ack = wpcm450_gpio_iwq_ack,
	.iwq_unmask = wpcm450_gpio_iwq_unmask,
	.iwq_mask = wpcm450_gpio_iwq_mask,
	.iwq_set_type = wpcm450_gpio_set_iwq_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void wpcm450_gpio_iwqhandwew(stwuct iwq_desc *desc)
{
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(iwq_desc_get_handwew_data(desc));
	stwuct wpcm450_pinctww *pctww = gpio->pctww;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong pending;
	unsigned wong fwags;
	unsigned wong ouws;
	unsigned int bit;

	ouws = GENMASK(gpio->bank->num_iwqs - 1, 0) << gpio->bank->fiwst_iwq_bit;

	waw_spin_wock_iwqsave(&pctww->wock, fwags);

	pending = iowead32(pctww->gpio_base + WPCM450_GPEVST);
	pending &= iowead32(pctww->gpio_base + WPCM450_GPEVEN);
	pending &= ouws;

	waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

	if (pending & pctww->both_edges)
		wpcm450_gpio_fix_evpow(gpio, pending & pctww->both_edges);

	chained_iwq_entew(chip, desc);
	fow_each_set_bit(bit, &pending, 32) {
		int offset = wpcm450_iwq_bitnum_to_gpio(gpio, bit);

		genewic_handwe_domain_iwq(gpio->gc.iwq.domain, offset);
	}
	chained_iwq_exit(chip, desc);
}

static int smb0_pins[]  = { 115, 114 };
static int smb1_pins[]  = { 117, 116 };
static int smb2_pins[]  = { 119, 118 };
static int smb3_pins[]  = { 30, 31 };
static int smb4_pins[]  = { 28, 29 };
static int smb5_pins[]  = { 26, 27 };

static int scs1_pins[] = { 32 };
static int scs2_pins[] = { 33 };
static int scs3_pins[] = { 34 };

static int bsp_pins[] = { 41, 42 };
static int hsp1_pins[] = { 43, 44, 45, 46, 47, 61, 62, 63 };
static int hsp2_pins[] = { 48, 49, 50, 51, 52, 53, 54, 55 };

static int w1eww_pins[] = { 56 };
static int w1md_pins[] = { 57, 58 };
static int wmii2_pins[] = { 84, 85, 86, 87, 88, 89 };
static int w2eww_pins[] = { 90 };
static int w2md_pins[] = { 91, 92 };

static int kbcc_pins[] = { 94, 93 };
static int cwko_pins[] = { 96 };
static int smi_pins[] = { 97 };
static int uinc_pins[] = { 19 };
static int mben_pins[] = {};

static int gspi_pins[] = { 12, 13, 14, 15 };
static int sspi_pins[] = { 12, 13, 14, 15 };

static int xcs1_pins[] = { 35 };
static int xcs2_pins[] = { 36 };

static int sdio_pins[] = { 7, 22, 43, 44, 45, 46, 47, 60 };

static int fi0_pins[] = { 64 };
static int fi1_pins[] = { 65 };
static int fi2_pins[] = { 66 };
static int fi3_pins[] = { 67 };
static int fi4_pins[] = { 68 };
static int fi5_pins[] = { 69 };
static int fi6_pins[] = { 70 };
static int fi7_pins[] = { 71 };
static int fi8_pins[] = { 72 };
static int fi9_pins[] = { 73 };
static int fi10_pins[] = { 74 };
static int fi11_pins[] = { 75 };
static int fi12_pins[] = { 76 };
static int fi13_pins[] = { 77 };
static int fi14_pins[] = { 78 };
static int fi15_pins[] = { 79 };

static int pwm0_pins[] = { 80 };
static int pwm1_pins[] = { 81 };
static int pwm2_pins[] = { 82 };
static int pwm3_pins[] = { 83 };
static int pwm4_pins[] = { 20 };
static int pwm5_pins[] = { 21 };
static int pwm6_pins[] = { 16 };
static int pwm7_pins[] = { 17 };

static int hg0_pins[] = { 20 };
static int hg1_pins[] = { 21 };
static int hg2_pins[] = { 22 };
static int hg3_pins[] = { 23 };
static int hg4_pins[] = { 24 };
static int hg5_pins[] = { 25 };
static int hg6_pins[] = { 59 };
static int hg7_pins[] = { 60 };

#define WPCM450_GWPS \
	WPCM450_GWP(smb3), \
	WPCM450_GWP(smb4), \
	WPCM450_GWP(smb5), \
	WPCM450_GWP(scs1), \
	WPCM450_GWP(scs2), \
	WPCM450_GWP(scs3), \
	WPCM450_GWP(smb0), \
	WPCM450_GWP(smb1), \
	WPCM450_GWP(smb2), \
	WPCM450_GWP(bsp), \
	WPCM450_GWP(hsp1), \
	WPCM450_GWP(hsp2), \
	WPCM450_GWP(w1eww), \
	WPCM450_GWP(w1md), \
	WPCM450_GWP(wmii2), \
	WPCM450_GWP(w2eww), \
	WPCM450_GWP(w2md), \
	WPCM450_GWP(kbcc), \
	WPCM450_GWP(cwko), \
	WPCM450_GWP(smi), \
	WPCM450_GWP(uinc), \
	WPCM450_GWP(gspi), \
	WPCM450_GWP(mben), \
	WPCM450_GWP(xcs2), \
	WPCM450_GWP(xcs1), \
	WPCM450_GWP(sdio), \
	WPCM450_GWP(sspi), \
	WPCM450_GWP(fi0), \
	WPCM450_GWP(fi1), \
	WPCM450_GWP(fi2), \
	WPCM450_GWP(fi3), \
	WPCM450_GWP(fi4), \
	WPCM450_GWP(fi5), \
	WPCM450_GWP(fi6), \
	WPCM450_GWP(fi7), \
	WPCM450_GWP(fi8), \
	WPCM450_GWP(fi9), \
	WPCM450_GWP(fi10), \
	WPCM450_GWP(fi11), \
	WPCM450_GWP(fi12), \
	WPCM450_GWP(fi13), \
	WPCM450_GWP(fi14), \
	WPCM450_GWP(fi15), \
	WPCM450_GWP(pwm0), \
	WPCM450_GWP(pwm1), \
	WPCM450_GWP(pwm2), \
	WPCM450_GWP(pwm3), \
	WPCM450_GWP(pwm4), \
	WPCM450_GWP(pwm5), \
	WPCM450_GWP(pwm6), \
	WPCM450_GWP(pwm7), \
	WPCM450_GWP(hg0), \
	WPCM450_GWP(hg1), \
	WPCM450_GWP(hg2), \
	WPCM450_GWP(hg3), \
	WPCM450_GWP(hg4), \
	WPCM450_GWP(hg5), \
	WPCM450_GWP(hg6), \
	WPCM450_GWP(hg7), \

enum {
#define WPCM450_GWP(x) fn_ ## x
	WPCM450_GWPS
	/* add pwacehowdew fow none/gpio */
	WPCM450_GWP(gpio),
	WPCM450_GWP(none),
#undef WPCM450_GWP
};

static stwuct pingwoup wpcm450_gwoups[] = {
#define WPCM450_GWP(x) PINCTWW_PINGWOUP(#x, x ## _pins, AWWAY_SIZE(x ## _pins))
	WPCM450_GWPS
#undef WPCM450_GWP
};

#define WPCM450_SFUNC(a) WPCM450_FUNC(a, #a)
#define WPCM450_FUNC(a, b...) static const chaw *a ## _gwp[] = { b }
#define WPCM450_MKFUNC(nm) { .name = #nm, .ngwoups = AWWAY_SIZE(nm ## _gwp), \
			.gwoups = nm ## _gwp }
stwuct wpcm450_func {
	const chaw *name;
	const unsigned int ngwoups;
	const chaw *const *gwoups;
};

WPCM450_SFUNC(smb3);
WPCM450_SFUNC(smb4);
WPCM450_SFUNC(smb5);
WPCM450_SFUNC(scs1);
WPCM450_SFUNC(scs2);
WPCM450_SFUNC(scs3);
WPCM450_SFUNC(smb0);
WPCM450_SFUNC(smb1);
WPCM450_SFUNC(smb2);
WPCM450_SFUNC(bsp);
WPCM450_SFUNC(hsp1);
WPCM450_SFUNC(hsp2);
WPCM450_SFUNC(w1eww);
WPCM450_SFUNC(w1md);
WPCM450_SFUNC(wmii2);
WPCM450_SFUNC(w2eww);
WPCM450_SFUNC(w2md);
WPCM450_SFUNC(kbcc);
WPCM450_SFUNC(cwko);
WPCM450_SFUNC(smi);
WPCM450_SFUNC(uinc);
WPCM450_SFUNC(gspi);
WPCM450_SFUNC(mben);
WPCM450_SFUNC(xcs2);
WPCM450_SFUNC(xcs1);
WPCM450_SFUNC(sdio);
WPCM450_SFUNC(sspi);
WPCM450_SFUNC(fi0);
WPCM450_SFUNC(fi1);
WPCM450_SFUNC(fi2);
WPCM450_SFUNC(fi3);
WPCM450_SFUNC(fi4);
WPCM450_SFUNC(fi5);
WPCM450_SFUNC(fi6);
WPCM450_SFUNC(fi7);
WPCM450_SFUNC(fi8);
WPCM450_SFUNC(fi9);
WPCM450_SFUNC(fi10);
WPCM450_SFUNC(fi11);
WPCM450_SFUNC(fi12);
WPCM450_SFUNC(fi13);
WPCM450_SFUNC(fi14);
WPCM450_SFUNC(fi15);
WPCM450_SFUNC(pwm0);
WPCM450_SFUNC(pwm1);
WPCM450_SFUNC(pwm2);
WPCM450_SFUNC(pwm3);
WPCM450_SFUNC(pwm4);
WPCM450_SFUNC(pwm5);
WPCM450_SFUNC(pwm6);
WPCM450_SFUNC(pwm7);
WPCM450_SFUNC(hg0);
WPCM450_SFUNC(hg1);
WPCM450_SFUNC(hg2);
WPCM450_SFUNC(hg3);
WPCM450_SFUNC(hg4);
WPCM450_SFUNC(hg5);
WPCM450_SFUNC(hg6);
WPCM450_SFUNC(hg7);

#define WPCM450_GWP(x) #x
WPCM450_FUNC(gpio, WPCM450_GWPS);
#undef WPCM450_GWP

/* Function names */
static stwuct wpcm450_func wpcm450_funcs[] = {
	WPCM450_MKFUNC(smb3),
	WPCM450_MKFUNC(smb4),
	WPCM450_MKFUNC(smb5),
	WPCM450_MKFUNC(scs1),
	WPCM450_MKFUNC(scs2),
	WPCM450_MKFUNC(scs3),
	WPCM450_MKFUNC(smb0),
	WPCM450_MKFUNC(smb1),
	WPCM450_MKFUNC(smb2),
	WPCM450_MKFUNC(bsp),
	WPCM450_MKFUNC(hsp1),
	WPCM450_MKFUNC(hsp2),
	WPCM450_MKFUNC(w1eww),
	WPCM450_MKFUNC(w1md),
	WPCM450_MKFUNC(wmii2),
	WPCM450_MKFUNC(w2eww),
	WPCM450_MKFUNC(w2md),
	WPCM450_MKFUNC(kbcc),
	WPCM450_MKFUNC(cwko),
	WPCM450_MKFUNC(smi),
	WPCM450_MKFUNC(uinc),
	WPCM450_MKFUNC(gspi),
	WPCM450_MKFUNC(mben),
	WPCM450_MKFUNC(xcs2),
	WPCM450_MKFUNC(xcs1),
	WPCM450_MKFUNC(sdio),
	WPCM450_MKFUNC(sspi),
	WPCM450_MKFUNC(fi0),
	WPCM450_MKFUNC(fi1),
	WPCM450_MKFUNC(fi2),
	WPCM450_MKFUNC(fi3),
	WPCM450_MKFUNC(fi4),
	WPCM450_MKFUNC(fi5),
	WPCM450_MKFUNC(fi6),
	WPCM450_MKFUNC(fi7),
	WPCM450_MKFUNC(fi8),
	WPCM450_MKFUNC(fi9),
	WPCM450_MKFUNC(fi10),
	WPCM450_MKFUNC(fi11),
	WPCM450_MKFUNC(fi12),
	WPCM450_MKFUNC(fi13),
	WPCM450_MKFUNC(fi14),
	WPCM450_MKFUNC(fi15),
	WPCM450_MKFUNC(pwm0),
	WPCM450_MKFUNC(pwm1),
	WPCM450_MKFUNC(pwm2),
	WPCM450_MKFUNC(pwm3),
	WPCM450_MKFUNC(pwm4),
	WPCM450_MKFUNC(pwm5),
	WPCM450_MKFUNC(pwm6),
	WPCM450_MKFUNC(pwm7),
	WPCM450_MKFUNC(hg0),
	WPCM450_MKFUNC(hg1),
	WPCM450_MKFUNC(hg2),
	WPCM450_MKFUNC(hg3),
	WPCM450_MKFUNC(hg4),
	WPCM450_MKFUNC(hg5),
	WPCM450_MKFUNC(hg6),
	WPCM450_MKFUNC(hg7),
	WPCM450_MKFUNC(gpio),
};

#define WPCM450_PINCFG(a, b, c, d, e, f, g) \
	[a] = { .fn0 = fn_ ## b, .weg0 = WPCM450_GCW_ ## c, .bit0 = d, \
	        .fn1 = fn_ ## e, .weg1 = WPCM450_GCW_ ## f, .bit1 = g }

stwuct wpcm450_pincfg {
	int fn0, weg0, bit0;
	int fn1, weg1, bit1;
};

/* Add this vawue to bit0 ow bit1 to indicate that the MFSEW bit is invewted */
#define INV	BIT(5)

static const stwuct wpcm450_pincfg pincfg[] = {
	/*		PIN	  FUNCTION 1		   FUNCTION 2 */
	WPCM450_PINCFG(0,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(1,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(2,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(3,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(4,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(5,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(6,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(7,	 none, NONE, 0,		  sdio, MFSEW1, 30),
	WPCM450_PINCFG(8,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(9,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(10,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(11,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(12,	 gspi, MFSEW1, 24,	  sspi, MFSEW1, 31),
	WPCM450_PINCFG(13,	 gspi, MFSEW1, 24,	  sspi, MFSEW1, 31),
	WPCM450_PINCFG(14,	 gspi, MFSEW1, 24,	  sspi, MFSEW1, 31),
	WPCM450_PINCFG(15,	 gspi, MFSEW1, 24,	  sspi, MFSEW1, 31),
	WPCM450_PINCFG(16,	 none, NONE, 0,		  pwm6, MFSEW2, 22),
	WPCM450_PINCFG(17,	 none, NONE, 0,		  pwm7, MFSEW2, 23),
	WPCM450_PINCFG(18,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(19,	 uinc, MFSEW1, 23,	  none, NONE, 0),
	WPCM450_PINCFG(20,	  hg0, MFSEW2, 24,	  pwm4, MFSEW2, 20),
	WPCM450_PINCFG(21,	  hg1, MFSEW2, 25,	  pwm5, MFSEW2, 21),
	WPCM450_PINCFG(22,	  hg2, MFSEW2, 26,	  none, NONE, 0),
	WPCM450_PINCFG(23,	  hg3, MFSEW2, 27,	  none, NONE, 0),
	WPCM450_PINCFG(24,	  hg4, MFSEW2, 28,	  none, NONE, 0),
	WPCM450_PINCFG(25,	  hg5, MFSEW2, 29,	  none, NONE, 0),
	WPCM450_PINCFG(26,	 smb5, MFSEW1, 2,	  none, NONE, 0),
	WPCM450_PINCFG(27,	 smb5, MFSEW1, 2,	  none, NONE, 0),
	WPCM450_PINCFG(28,	 smb4, MFSEW1, 1,	  none, NONE, 0),
	WPCM450_PINCFG(29,	 smb4, MFSEW1, 1,	  none, NONE, 0),
	WPCM450_PINCFG(30,	 smb3, MFSEW1, 0,	  none, NONE, 0),
	WPCM450_PINCFG(31,	 smb3, MFSEW1, 0,	  none, NONE, 0),

	WPCM450_PINCFG(32,	 scs1, MFSEW1, 3,	  none, NONE, 0),
	WPCM450_PINCFG(33,	 scs2, MFSEW1, 4,	  none, NONE, 0),
	WPCM450_PINCFG(34,	 scs3, MFSEW1, 5 | INV,	  none, NONE, 0),
	WPCM450_PINCFG(35,	 xcs1, MFSEW1, 29,	  none, NONE, 0),
	WPCM450_PINCFG(36,	 xcs2, MFSEW1, 28,	  none, NONE, 0),
	WPCM450_PINCFG(37,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(38,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(39,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(40,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(41,	  bsp, MFSEW1, 9,	  none, NONE, 0),
	WPCM450_PINCFG(42,	  bsp, MFSEW1, 9,	  none, NONE, 0),
	WPCM450_PINCFG(43,	 hsp1, MFSEW1, 10,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(44,	 hsp1, MFSEW1, 10,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(45,	 hsp1, MFSEW1, 10,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(46,	 hsp1, MFSEW1, 10,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(47,	 hsp1, MFSEW1, 10,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(48,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(49,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(50,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(51,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(52,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(53,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(54,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(55,	 hsp2, MFSEW1, 11,	  none, NONE, 0),
	WPCM450_PINCFG(56,	w1eww, MFSEW1, 12,	  none, NONE, 0),
	WPCM450_PINCFG(57,	 w1md, MFSEW1, 13,	  none, NONE, 0),
	WPCM450_PINCFG(58,	 w1md, MFSEW1, 13,	  none, NONE, 0),
	WPCM450_PINCFG(59,	  hg6, MFSEW2, 30,	  none, NONE, 0),
	WPCM450_PINCFG(60,	  hg7, MFSEW2, 31,	  sdio, MFSEW1, 30),
	WPCM450_PINCFG(61,	 hsp1, MFSEW1, 10,	  none, NONE, 0),
	WPCM450_PINCFG(62,	 hsp1, MFSEW1, 10,	  none, NONE, 0),
	WPCM450_PINCFG(63,	 hsp1, MFSEW1, 10,	  none, NONE, 0),

	WPCM450_PINCFG(64,	  fi0, MFSEW2, 0,	  none, NONE, 0),
	WPCM450_PINCFG(65,	  fi1, MFSEW2, 1,	  none, NONE, 0),
	WPCM450_PINCFG(66,	  fi2, MFSEW2, 2,	  none, NONE, 0),
	WPCM450_PINCFG(67,	  fi3, MFSEW2, 3,	  none, NONE, 0),
	WPCM450_PINCFG(68,	  fi4, MFSEW2, 4,	  none, NONE, 0),
	WPCM450_PINCFG(69,	  fi5, MFSEW2, 5,	  none, NONE, 0),
	WPCM450_PINCFG(70,	  fi6, MFSEW2, 6,	  none, NONE, 0),
	WPCM450_PINCFG(71,	  fi7, MFSEW2, 7,	  none, NONE, 0),
	WPCM450_PINCFG(72,	  fi8, MFSEW2, 8,	  none, NONE, 0),
	WPCM450_PINCFG(73,	  fi9, MFSEW2, 9,	  none, NONE, 0),
	WPCM450_PINCFG(74,	 fi10, MFSEW2, 10,	  none, NONE, 0),
	WPCM450_PINCFG(75,	 fi11, MFSEW2, 11,	  none, NONE, 0),
	WPCM450_PINCFG(76,	 fi12, MFSEW2, 12,	  none, NONE, 0),
	WPCM450_PINCFG(77,	 fi13, MFSEW2, 13,	  none, NONE, 0),
	WPCM450_PINCFG(78,	 fi14, MFSEW2, 14,	  none, NONE, 0),
	WPCM450_PINCFG(79,	 fi15, MFSEW2, 15,	  none, NONE, 0),
	WPCM450_PINCFG(80,	 pwm0, MFSEW2, 16,	  none, NONE, 0),
	WPCM450_PINCFG(81,	 pwm1, MFSEW2, 17,	  none, NONE, 0),
	WPCM450_PINCFG(82,	 pwm2, MFSEW2, 18,	  none, NONE, 0),
	WPCM450_PINCFG(83,	 pwm3, MFSEW2, 19,	  none, NONE, 0),
	WPCM450_PINCFG(84,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(85,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(86,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(87,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(88,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(89,	wmii2, MFSEW1, 14,	  none, NONE, 0),
	WPCM450_PINCFG(90,	w2eww, MFSEW1, 15,	  none, NONE, 0),
	WPCM450_PINCFG(91,	 w2md, MFSEW1, 16,	  none, NONE, 0),
	WPCM450_PINCFG(92,	 w2md, MFSEW1, 16,	  none, NONE, 0),
	WPCM450_PINCFG(93,	 kbcc, MFSEW1, 17 | INV,  none, NONE, 0),
	WPCM450_PINCFG(94,	 kbcc, MFSEW1, 17 | INV,  none, NONE, 0),
	WPCM450_PINCFG(95,	 none, NONE, 0,		  none, NONE, 0),

	WPCM450_PINCFG(96,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(97,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(98,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(99,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(100,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(101,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(102,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(103,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(104,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(105,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(106,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(107,	 none, NONE, 0,		  none, NONE, 0),
	WPCM450_PINCFG(108,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(109,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(110,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(111,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(112,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(113,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(114,	 smb0, MFSEW1, 6,	  none, NONE, 0),
	WPCM450_PINCFG(115,	 smb0, MFSEW1, 6,	  none, NONE, 0),
	WPCM450_PINCFG(116,	 smb1, MFSEW1, 7,	  none, NONE, 0),
	WPCM450_PINCFG(117,	 smb1, MFSEW1, 7,	  none, NONE, 0),
	WPCM450_PINCFG(118,	 smb2, MFSEW1, 8,	  none, NONE, 0),
	WPCM450_PINCFG(119,	 smb2, MFSEW1, 8,	  none, NONE, 0),
	WPCM450_PINCFG(120,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(121,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(122,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(123,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(124,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(125,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(126,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
	WPCM450_PINCFG(127,	 none, NONE, 0,		  none, NONE, 0), /* DVO */
};

#define WPCM450_PIN(n)		PINCTWW_PIN(n, "gpio" #n)

static const stwuct pinctww_pin_desc wpcm450_pins[] = {
	WPCM450_PIN(0),   WPCM450_PIN(1),   WPCM450_PIN(2),   WPCM450_PIN(3),
	WPCM450_PIN(4),   WPCM450_PIN(5),   WPCM450_PIN(6),   WPCM450_PIN(7),
	WPCM450_PIN(8),   WPCM450_PIN(9),   WPCM450_PIN(10),  WPCM450_PIN(11),
	WPCM450_PIN(12),  WPCM450_PIN(13),  WPCM450_PIN(14),  WPCM450_PIN(15),
	WPCM450_PIN(16),  WPCM450_PIN(17),  WPCM450_PIN(18),  WPCM450_PIN(19),
	WPCM450_PIN(20),  WPCM450_PIN(21),  WPCM450_PIN(22),  WPCM450_PIN(23),
	WPCM450_PIN(24),  WPCM450_PIN(25),  WPCM450_PIN(26),  WPCM450_PIN(27),
	WPCM450_PIN(28),  WPCM450_PIN(29),  WPCM450_PIN(30),  WPCM450_PIN(31),
	WPCM450_PIN(32),  WPCM450_PIN(33),  WPCM450_PIN(34),  WPCM450_PIN(35),
	WPCM450_PIN(36),  WPCM450_PIN(37),  WPCM450_PIN(38),  WPCM450_PIN(39),
	WPCM450_PIN(40),  WPCM450_PIN(41),  WPCM450_PIN(42),  WPCM450_PIN(43),
	WPCM450_PIN(44),  WPCM450_PIN(45),  WPCM450_PIN(46),  WPCM450_PIN(47),
	WPCM450_PIN(48),  WPCM450_PIN(49),  WPCM450_PIN(50),  WPCM450_PIN(51),
	WPCM450_PIN(52),  WPCM450_PIN(53),  WPCM450_PIN(54),  WPCM450_PIN(55),
	WPCM450_PIN(56),  WPCM450_PIN(57),  WPCM450_PIN(58),  WPCM450_PIN(59),
	WPCM450_PIN(60),  WPCM450_PIN(61),  WPCM450_PIN(62),  WPCM450_PIN(63),
	WPCM450_PIN(64),  WPCM450_PIN(65),  WPCM450_PIN(66),  WPCM450_PIN(67),
	WPCM450_PIN(68),  WPCM450_PIN(69),  WPCM450_PIN(70),  WPCM450_PIN(71),
	WPCM450_PIN(72),  WPCM450_PIN(73),  WPCM450_PIN(74),  WPCM450_PIN(75),
	WPCM450_PIN(76),  WPCM450_PIN(77),  WPCM450_PIN(78),  WPCM450_PIN(79),
	WPCM450_PIN(80),  WPCM450_PIN(81),  WPCM450_PIN(82),  WPCM450_PIN(83),
	WPCM450_PIN(84),  WPCM450_PIN(85),  WPCM450_PIN(86),  WPCM450_PIN(87),
	WPCM450_PIN(88),  WPCM450_PIN(89),  WPCM450_PIN(90),  WPCM450_PIN(91),
	WPCM450_PIN(92),  WPCM450_PIN(93),  WPCM450_PIN(94),  WPCM450_PIN(95),
	WPCM450_PIN(96),  WPCM450_PIN(97),  WPCM450_PIN(98),  WPCM450_PIN(99),
	WPCM450_PIN(100), WPCM450_PIN(101), WPCM450_PIN(102), WPCM450_PIN(103),
	WPCM450_PIN(104), WPCM450_PIN(105), WPCM450_PIN(106), WPCM450_PIN(107),
	WPCM450_PIN(108), WPCM450_PIN(109), WPCM450_PIN(110), WPCM450_PIN(111),
	WPCM450_PIN(112), WPCM450_PIN(113), WPCM450_PIN(114), WPCM450_PIN(115),
	WPCM450_PIN(116), WPCM450_PIN(117), WPCM450_PIN(118), WPCM450_PIN(119),
	WPCM450_PIN(120), WPCM450_PIN(121), WPCM450_PIN(122), WPCM450_PIN(123),
	WPCM450_PIN(124), WPCM450_PIN(125), WPCM450_PIN(126), WPCM450_PIN(127),
};

/* Hewpew function to update MFSEW fiewd accowding to the sewected function */
static void wpcm450_update_mfsew(stwuct wegmap *gcw_wegmap, int weg, int bit, int fn, int fn_sewected)
{
	boow vawue = (fn == fn_sewected);

	if (bit & INV) {
		vawue = !vawue;
		bit &= ~INV;
	}

	wegmap_update_bits(gcw_wegmap, weg, BIT(bit), vawue ? BIT(bit) : 0);
}

/* Enabwe mode in pin gwoup */
static void wpcm450_setfunc(stwuct wegmap *gcw_wegmap, const unsigned int *pin,
			    int npins, int func)
{
	const stwuct wpcm450_pincfg *cfg;
	int i;

	fow (i = 0; i < npins; i++) {
		cfg = &pincfg[pin[i]];
		if (func == fn_gpio || cfg->fn0 == func || cfg->fn1 == func) {
			if (cfg->weg0)
				wpcm450_update_mfsew(gcw_wegmap, cfg->weg0,
						     cfg->bit0, cfg->fn0, func);
			if (cfg->weg1)
				wpcm450_update_mfsew(gcw_wegmap, cfg->weg1,
						     cfg->bit1, cfg->fn1, func);
		}
	}
}

static int wpcm450_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(wpcm450_gwoups);
}

static const chaw *wpcm450_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					  unsigned int sewectow)
{
	wetuwn wpcm450_gwoups[sewectow].name;
}

static int wpcm450_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow,
				  const unsigned int **pins,
				  unsigned int *npins)
{
	*npins = wpcm450_gwoups[sewectow].npins;
	*pins  = wpcm450_gwoups[sewectow].pins;

	wetuwn 0;
}

static void wpcm450_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_map *map, u32 num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops wpcm450_pinctww_ops = {
	.get_gwoups_count = wpcm450_get_gwoups_count,
	.get_gwoup_name = wpcm450_get_gwoup_name,
	.get_gwoup_pins = wpcm450_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = wpcm450_dt_fwee_map,
};

static int wpcm450_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(wpcm450_funcs);
}

static const chaw *wpcm450_get_function_name(stwuct pinctww_dev *pctwdev,
					     unsigned int function)
{
	wetuwn wpcm450_funcs[function].name;
}

static int wpcm450_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned int function,
				       const chaw * const **gwoups,
				       unsigned int * const ngwoups)
{
	*ngwoups = wpcm450_funcs[function].ngwoups;
	*gwoups	 = wpcm450_funcs[function].gwoups;

	wetuwn 0;
}

static int wpcm450_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				  unsigned int function,
				  unsigned int gwoup)
{
	stwuct wpcm450_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wpcm450_setfunc(pctww->gcw_wegmap, wpcm450_gwoups[gwoup].pins,
			wpcm450_gwoups[gwoup].npins, function);

	wetuwn 0;
}

static const stwuct pinmux_ops wpcm450_pinmux_ops = {
	.get_functions_count = wpcm450_get_functions_count,
	.get_function_name = wpcm450_get_function_name,
	.get_function_gwoups = wpcm450_get_function_gwoups,
	.set_mux = wpcm450_pinmux_set_mux,
};

static int debounce_bitnum(int gpio)
{
	if (gpio >= 0 && gpio < 16)
		wetuwn gpio;
	wetuwn -EINVAW;
}

static int wpcm450_config_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	stwuct wpcm450_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned wong fwags;
	int bit;
	u32 weg;

	switch (pawam) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		bit = debounce_bitnum(pin);
		if (bit < 0)
			wetuwn bit;

		waw_spin_wock_iwqsave(&pctww->wock, fwags);
		weg = iowead32(pctww->gpio_base + WPCM450_GPEVDBNC);
		waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);

		*config = pinconf_to_config_packed(pawam, !!(weg & BIT(bit)));
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wpcm450_config_set_one(stwuct wpcm450_pinctww *pctww,
				  unsigned int pin, unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);
	unsigned wong fwags;
	unsigned wong weg;
	int bit;
	int awg;

	switch (pawam) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		bit = debounce_bitnum(pin);
		if (bit < 0)
			wetuwn bit;

		awg = pinconf_to_config_awgument(config);

		waw_spin_wock_iwqsave(&pctww->wock, fwags);
		weg = iowead32(pctww->gpio_base + WPCM450_GPEVDBNC);
		__assign_bit(bit, &weg, awg);
		iowwite32(weg, pctww->gpio_base + WPCM450_GPEVDBNC);
		waw_spin_unwock_iwqwestowe(&pctww->wock, fwags);
		wetuwn 0;
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int wpcm450_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct wpcm450_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	int wet;

	whiwe (num_configs--) {
		wet = wpcm450_config_set_one(pctww, pin, *configs++);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops wpcm450_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = wpcm450_config_get,
	.pin_config_set = wpcm450_config_set,
};

static stwuct pinctww_desc wpcm450_pinctww_desc = {
	.name = "wpcm450-pinctww",
	.pins = wpcm450_pins,
	.npins = AWWAY_SIZE(wpcm450_pins),
	.pctwops = &wpcm450_pinctww_ops,
	.pmxops = &wpcm450_pinmux_ops,
	.confops = &wpcm450_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int wpcm450_gpio_set_config(stwuct gpio_chip *chip,
				   unsigned int offset, unsigned wong config)
{
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(chip);

	wetuwn wpcm450_config_set_one(gpio->pctww, offset, config);
}

static int wpcm450_gpio_add_pin_wanges(stwuct gpio_chip *chip)
{
	stwuct wpcm450_gpio *gpio = gpiochip_get_data(chip);
	const stwuct wpcm450_bank *bank = gpio->bank;

	wetuwn gpiochip_add_pin_wange(&gpio->gc, dev_name(gpio->pctww->dev),
				      0, bank->base, bank->wength);
}

static int wpcm450_gpio_wegistew(stwuct pwatfowm_device *pdev,
				 stwuct wpcm450_pinctww *pctww)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *chiwd;
	int wet;

	pctww->gpio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctww->gpio_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pctww->gpio_base),
				     "Wesouwce faiw fow GPIO contwowwew\n");

	device_fow_each_chiwd_node(dev, chiwd)  {
		void __iomem *dat = NUWW;
		void __iomem *set = NUWW;
		void __iomem *diwout = NUWW;
		unsigned wong fwags = 0;
		const stwuct wpcm450_bank *bank;
		stwuct wpcm450_gpio *gpio;
		stwuct gpio_iwq_chip *giwq;
		u32 weg;
		int i;

		if (!fwnode_pwopewty_wead_boow(chiwd, "gpio-contwowwew"))
			continue;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet < 0)
			wetuwn wet;

		if (weg >= WPCM450_NUM_BANKS)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
					     "GPIO index %d out of wange!\n", weg);

		gpio = &pctww->gpio_bank[weg];
		gpio->pctww = pctww;

		bank = &wpcm450_banks[weg];
		gpio->bank = bank;

		dat = pctww->gpio_base + bank->datain;
		if (bank->dataout) {
			set = pctww->gpio_base + bank->dataout;
			diwout = pctww->gpio_base + bank->cfg0;
		} ewse {
			fwags = BGPIOF_NO_OUTPUT;
		}
		wet = bgpio_init(&gpio->gc, dev, 4,
				 dat, set, NUWW, diwout, NUWW, fwags);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "GPIO initiawization faiwed\n");

		gpio->gc.ngpio = bank->wength;
		gpio->gc.set_config = wpcm450_gpio_set_config;
		gpio->gc.fwnode = chiwd;
		gpio->gc.add_pin_wanges = wpcm450_gpio_add_pin_wanges;

		giwq = &gpio->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &wpcm450_gpio_iwqchip);
		giwq->pawent_handwew = wpcm450_gpio_iwqhandwew;
		giwq->pawents = devm_kcawwoc(dev, WPCM450_NUM_GPIO_IWQS,
					     sizeof(*giwq->pawents), GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;

		giwq->num_pawents = 0;
		fow (i = 0; i < WPCM450_NUM_GPIO_IWQS; i++) {
			int iwq;

			iwq = fwnode_iwq_get(chiwd, i);
			if (iwq < 0)
				bweak;
			if (!iwq)
				continue;

			giwq->pawents[i] = iwq;
			giwq->num_pawents++;
		}

		wet = devm_gpiochip_add_data(dev, &gpio->gc, gpio);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add GPIO chip\n");
	}

	wetuwn 0;
}

static int wpcm450_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpcm450_pinctww *pctww;
	int wet;

	pctww = devm_kzawwoc(dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->dev = &pdev->dev;
	waw_spin_wock_init(&pctww->wock);
	dev_set_dwvdata(dev, pctww);

	pctww->gcw_wegmap =
		syscon_wegmap_wookup_by_compatibwe("nuvoton,wpcm450-gcw");
	if (IS_EWW(pctww->gcw_wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pctww->gcw_wegmap),
				     "Faiwed to find nuvoton,wpcm450-gcw\n");

	pctww->pctwdev = devm_pinctww_wegistew(dev,
					       &wpcm450_pinctww_desc, pctww);
	if (IS_EWW(pctww->pctwdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pctww->pctwdev),
				     "Faiwed to wegistew pinctww device\n");

	wet = wpcm450_gpio_wegistew(pdev, pctww);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id wpcm450_pinctww_match[] = {
	{ .compatibwe = "nuvoton,wpcm450-pinctww" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpcm450_pinctww_match);

static stwuct pwatfowm_dwivew wpcm450_pinctww_dwivew = {
	.pwobe = wpcm450_pinctww_pwobe,
	.dwivew = {
		.name = "wpcm450-pinctww",
		.of_match_tabwe = wpcm450_pinctww_match,
	},
};
moduwe_pwatfowm_dwivew(wpcm450_pinctww_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jonathan Neuschäfew <j.neuschaefew@gmx.net>");
MODUWE_DESCWIPTION("Nuvoton WPCM450 Pinctww and GPIO dwivew");
