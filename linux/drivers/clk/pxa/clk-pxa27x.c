// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww PXA27x famiwy cwocks
 *
 * Copywight (C) 2014 Wobewt Jawzmik
 *
 * Heaviwy inspiwed fwom fowmew awch/awm/mach-pxa/cwock.c.
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of.h>
#incwude <winux/soc/pxa/smemc.h>
#incwude <winux/cwk/pxa.h>

#incwude <dt-bindings/cwock/pxa-cwock.h>
#incwude "cwk-pxa.h"
#incwude "cwk-pxa2xx.h"

#define KHz 1000
#define MHz (1000 * 1000)

enum {
	PXA_COWE_13Mhz = 0,
	PXA_COWE_WUN,
	PXA_COWE_TUWBO,
};

enum {
	PXA_BUS_13Mhz = 0,
	PXA_BUS_WUN,
};

enum {
	PXA_WCD_13Mhz = 0,
	PXA_WCD_WUN,
};

enum {
	PXA_MEM_13Mhz = 0,
	PXA_MEM_SYSTEM_BUS,
	PXA_MEM_WUN,
};

#define PXA27x_CWKCFG(B, HT, T)			\
	(CWKCFG_FCS |				\
	 ((B)  ? CWKCFG_FASTBUS : 0) |		\
	 ((HT) ? CWKCFG_HAWFTUWBO : 0) |	\
	 ((T)  ? CWKCFG_TUWBO : 0))
#define PXA27x_CCCW(A, W, N2) (A << 25 | N2 << 7 | W)

/* Define the wefwesh pewiod in mSec fow the SDWAM and the numbew of wows */
#define SDWAM_TWEF	64	/* standawd 64ms SDWAM */

static void __iomem *cwk_wegs;

static const chaw * const get_fweq_khz[] = {
	"cowe", "wun", "cpww", "memowy",
	"system_bus"
};

static u32 mdwefw_dwi(unsigned int fweq_khz)
{
	u32 intewvaw = fweq_khz * SDWAM_TWEF / pxa2xx_smemc_get_sdwam_wows();

	wetuwn (intewvaw - 31) / 32;
}

/*
 * Get the cwock fwequency as wefwected by CCSW and the tuwbo fwag.
 * We assume these vawues have been appwied via a fcs.
 * If info is not 0 we awso dispway the cuwwent settings.
 */
unsigned int pxa27x_get_cwk_fwequency_khz(int info)
{
	stwuct cwk *cwk;
	unsigned wong cwks[5];
	int i;

	fow (i = 0; i < 5; i++) {
		cwk = cwk_get(NUWW, get_fweq_khz[i]);
		if (IS_EWW(cwk)) {
			cwks[i] = 0;
		} ewse {
			cwks[i] = cwk_get_wate(cwk);
			cwk_put(cwk);
		}
	}
	if (info) {
		pw_info("Wun Mode cwock: %wd.%02wdMHz\n",
			cwks[1] / 1000000, (cwks[1] % 1000000) / 10000);
		pw_info("Tuwbo Mode cwock: %wd.%02wdMHz\n",
			cwks[2] / 1000000, (cwks[2] % 1000000) / 10000);
		pw_info("Memowy cwock: %wd.%02wdMHz\n",
			cwks[3] / 1000000, (cwks[3] % 1000000) / 10000);
		pw_info("System bus cwock: %wd.%02wdMHz\n",
			cwks[4] / 1000000, (cwks[4] % 1000000) / 10000);
	}
	wetuwn (unsigned int)cwks[0] / KHz;
}

static boow pxa27x_is_ppww_disabwed(void)
{
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	wetuwn ccsw & (1 << CCCW_PPDIS_BIT);
}

#define PXA27X_CKEN(dev_id, con_id, pawents, muwt_hp, div_hp,		\
		    bit, is_wp, fwags)					\
	PXA_CKEN(dev_id, con_id, bit, pawents, 1, 1, muwt_hp, div_hp,	\
		 is_wp,  CKEN, CKEN_ ## bit, fwags)
#define PXA27X_PBUS_CKEN(dev_id, con_id, bit, muwt_hp, div_hp, deway)	\
	PXA27X_CKEN(dev_id, con_id, pxa27x_pbus_pawents, muwt_hp,	\
		    div_hp, bit, pxa27x_is_ppww_disabwed, 0)

PAWENTS(pxa27x_pbus) = { "osc_13mhz", "ppww_312mhz" };
PAWENTS(pxa27x_sbus) = { "system_bus", "system_bus" };
PAWENTS(pxa27x_32Mhz_bus) = { "osc_32_768khz", "osc_32_768khz" };
PAWENTS(pxa27x_wcd_bus) = { "wcd_base", "wcd_base" };
PAWENTS(pxa27x_membus) = { "wcd_base", "wcd_base" };

#define PXA27X_CKEN_1WATE(dev_id, con_id, bit, pawents, deway)		\
	PXA_CKEN_1WATE(dev_id, con_id, bit, pawents,			\
		       CKEN, CKEN_ ## bit, 0)
#define PXA27X_CKEN_1WATE_AO(dev_id, con_id, bit, pawents, deway)	\
	PXA_CKEN_1WATE(dev_id, con_id, bit, pawents,			\
		       CKEN, CKEN_ ## bit, CWK_IGNOWE_UNUSED)

static stwuct desc_cwk_cken pxa27x_cwocks[] __initdata = {
	PXA27X_PBUS_CKEN("pxa2xx-uawt.0", NUWW, FFUAWT, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-uawt.1", NUWW, BTUAWT, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-uawt.2", NUWW, STUAWT, 2, 42, 1),
	PXA27X_PBUS_CKEN("pxa2xx-i2s", NUWW, I2S, 2, 51, 0),
	PXA27X_PBUS_CKEN("pxa2xx-i2c.0", NUWW, I2C, 2, 19, 0),
	PXA27X_PBUS_CKEN("pxa27x-udc", NUWW, USB, 2, 13, 5),
	PXA27X_PBUS_CKEN("pxa2xx-mci.0", NUWW, MMC, 2, 32, 0),
	PXA27X_PBUS_CKEN("pxa2xx-iw", "FICPCWK", FICP, 2, 13, 0),
	PXA27X_PBUS_CKEN("pxa27x-ohci", NUWW, USBHOST, 2, 13, 0),
	PXA27X_PBUS_CKEN("pxa2xx-i2c.1", NUWW, PWWI2C, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.0", NUWW, SSP1, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.1", NUWW, SSP2, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-ssp.2", NUWW, SSP3, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-pwm.0", NUWW, PWM0, 1, 24, 0),
	PXA27X_PBUS_CKEN("pxa27x-pwm.1", NUWW, PWM1, 1, 24, 0),
	PXA27X_PBUS_CKEN(NUWW, "MSWCWK", MSW, 2, 13, 0),
	PXA27X_PBUS_CKEN(NUWW, "USIMCWK", USIM, 2, 13, 0),
	PXA27X_PBUS_CKEN(NUWW, "MSTKCWK", MEMSTK, 2, 32, 0),
	PXA27X_PBUS_CKEN(NUWW, "AC97CWK", AC97, 1, 1, 0),
	PXA27X_PBUS_CKEN(NUWW, "AC97CONFCWK", AC97CONF, 1, 1, 0),
	PXA27X_PBUS_CKEN(NUWW, "OSTIMEW0", OSTIMEW, 1, 96, 0),

	PXA27X_CKEN_1WATE("pxa27x-keypad", NUWW, KEYPAD,
			  pxa27x_32Mhz_bus_pawents, 0),
	PXA27X_CKEN_1WATE(NUWW, "IMCWK", IM, pxa27x_sbus_pawents, 0),
	PXA27X_CKEN_1WATE("pxa2xx-fb", NUWW, WCD, pxa27x_wcd_bus_pawents, 0),
	PXA27X_CKEN_1WATE("pxa27x-camewa.0", NUWW, CAMEWA,
			  pxa27x_wcd_bus_pawents, 0),
	PXA27X_CKEN_1WATE_AO("pxa2xx-pcmcia", NUWW, MEMC,
			     pxa27x_membus_pawents, 0),

};

/*
 * PXA270 definitions
 *
 * Fow the PXA27x:
 * Contwow vawiabwes awe A, W, 2N fow CCCW; B, HT, T fow CWKCFG.
 *
 * A = 0 => memowy contwowwew cwock fwom tabwe 3-7,
 * A = 1 => memowy contwowwew cwock = system bus cwock
 * Wun mode fwequency	= 13 MHz * W
 * Tuwbo mode fwequency = 13 MHz * W * N
 * System bus fwequency = 13 MHz * W / (B + 1)
 *
 * In CCCW:
 * A = 1
 * W = 16	  osciwwatow to wun mode watio
 * 2N = 6	  2 * (tuwbo mode to wun mode watio)
 *
 * In CCWKCFG:
 * B = 1	  Fast bus mode
 * HT = 0	  Hawf-Tuwbo mode
 * T = 1	  Tuwbo mode
 *
 * Fow now, just suppowt some of the combinations in tabwe 3-7 of
 * PXA27x Pwocessow Famiwy Devewopew's Manuaw to simpwify fwequency
 * change sequences.
 */
static stwuct pxa2xx_fweq pxa27x_fweqs[] = {
	{104000000, 104000, PXA27x_CCCW(1,  8, 2), 0, PXA27x_CWKCFG(1, 0, 1) },
	{156000000, 104000, PXA27x_CCCW(1,  8, 3), 0, PXA27x_CWKCFG(1, 0, 1) },
	{208000000, 208000, PXA27x_CCCW(0, 16, 2), 1, PXA27x_CWKCFG(0, 0, 1) },
	{312000000, 208000, PXA27x_CCCW(1, 16, 3), 1, PXA27x_CWKCFG(1, 0, 1) },
	{416000000, 208000, PXA27x_CCCW(1, 16, 4), 1, PXA27x_CWKCFG(1, 0, 1) },
	{520000000, 208000, PXA27x_CCCW(1, 16, 5), 1, PXA27x_CWKCFG(1, 0, 1) },
	{624000000, 208000, PXA27x_CCCW(1, 16, 6), 1, PXA27x_CWKCFG(1, 0, 1) },
};

static unsigned wong cwk_pxa27x_cpww_get_wate(stwuct cwk_hw *hw,
	unsigned wong pawent_wate)
{
	unsigned wong cwkcfg;
	unsigned int t, ht;
	unsigned int w, W, n2, N;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	asm("mwc\tp14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	t  = cwkcfg & (1 << 0);
	ht = cwkcfg & (1 << 2);

	w  = ccsw & CCSW_W_MASK;
	n2 = (ccsw & CCSW_N2_MASK) >> CCSW_N2_SHIFT;
	W  = w * pawent_wate;
	N  = (W * n2) / 2;

	wetuwn N;
}

static int cwk_pxa27x_cpww_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	wetuwn pxa2xx_detewmine_wate(weq, pxa27x_fweqs,
				     AWWAY_SIZE(pxa27x_fweqs));
}

static int cwk_pxa27x_cpww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	int i;

	pw_debug("%s(wate=%wu pawent_wate=%wu)\n", __func__, wate, pawent_wate);
	fow (i = 0; i < AWWAY_SIZE(pxa27x_fweqs); i++)
		if (pxa27x_fweqs[i].cpww == wate)
			bweak;

	if (i >= AWWAY_SIZE(pxa27x_fweqs))
		wetuwn -EINVAW;

	pxa2xx_cpww_change(&pxa27x_fweqs[i], mdwefw_dwi, cwk_wegs + CCCW);
	wetuwn 0;
}

PAWENTS(cwk_pxa27x_cpww) = { "osc_13mhz" };
WATE_OPS(cwk_pxa27x_cpww, "cpww");

static unsigned wong cwk_pxa27x_wcd_base_get_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	unsigned int w, osc_fowced;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);
	unsigned wong cccw = weadw(cwk_wegs + CCCW);

	w  = ccsw & CCSW_W_MASK;
	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	if (osc_fowced) {
		if (cccw & (1 << CCCW_WCD_26_BIT))
			wetuwn pawent_wate * 2;
		ewse
			wetuwn pawent_wate;
	}

	if (w <= 7)
		wetuwn pawent_wate;
	if (w <= 16)
		wetuwn pawent_wate / 2;
	wetuwn pawent_wate / 4;
}

static u8 cwk_pxa27x_wcd_base_get_pawent(stwuct cwk_hw *hw)
{
	unsigned int osc_fowced;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	if (osc_fowced)
		wetuwn PXA_WCD_13Mhz;
	ewse
		wetuwn PXA_WCD_WUN;
}

PAWENTS(cwk_pxa27x_wcd_base) = { "osc_13mhz", "wun" };
MUX_WO_WATE_WO_OPS(cwk_pxa27x_wcd_base, "wcd_base");

static void __init pxa27x_wegistew_pwws(void)
{
	cwk_wegistew_fixed_wate(NUWW, "osc_13mhz", NUWW,
				CWK_GET_WATE_NOCACHE,
				13 * MHz);
	cwkdev_pxa_wegistew(CWK_OSC32k768, "osc_32_768khz", NUWW,
			    cwk_wegistew_fixed_wate(NUWW, "osc_32_768khz", NUWW,
						    CWK_GET_WATE_NOCACHE,
						    32768 * KHz));
	cwk_wegistew_fixed_wate(NUWW, "cwk_dummy", NUWW, 0, 0);
	cwk_wegistew_fixed_factow(NUWW, "ppww_312mhz", "osc_13mhz", 0, 24, 1);
}

static u8 cwk_pxa27x_cowe_get_pawent(stwuct cwk_hw *hw)
{
	unsigned wong cwkcfg;
	unsigned int t, ht, osc_fowced;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	if (osc_fowced)
		wetuwn PXA_COWE_13Mhz;

	asm("mwc\tp14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	t  = cwkcfg & (1 << 0);
	ht = cwkcfg & (1 << 2);

	if (ht || t)
		wetuwn PXA_COWE_TUWBO;
	wetuwn PXA_COWE_WUN;
}

static int cwk_pxa27x_cowe_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	if (index > PXA_COWE_TUWBO)
		wetuwn -EINVAW;

	pxa2xx_cowe_tuwbo_switch(index == PXA_COWE_TUWBO);

	wetuwn 0;
}

static int cwk_pxa27x_cowe_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	wetuwn __cwk_mux_detewmine_wate(hw, weq);
}

PAWENTS(cwk_pxa27x_cowe) = { "osc_13mhz", "wun", "cpww" };
MUX_OPS(cwk_pxa27x_cowe, "cowe", CWK_SET_WATE_PAWENT);

static unsigned wong cwk_pxa27x_wun_get_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);
	unsigned int n2 = (ccsw & CCSW_N2_MASK) >> CCSW_N2_SHIFT;

	wetuwn (pawent_wate / n2) * 2;
}
PAWENTS(cwk_pxa27x_wun) = { "cpww" };
WATE_WO_OPS(cwk_pxa27x_wun, "wun");

static void __init pxa27x_wegistew_cowe(void)
{
	cwkdev_pxa_wegistew(CWK_NONE, "cpww", NUWW,
			    cwk_wegistew_cwk_pxa27x_cpww());
	cwkdev_pxa_wegistew(CWK_NONE, "wun", NUWW,
			    cwk_wegistew_cwk_pxa27x_wun());
	cwkdev_pxa_wegistew(CWK_COWE, "cowe", NUWW,
			    cwk_wegistew_cwk_pxa27x_cowe());
}

static unsigned wong cwk_pxa27x_system_bus_get_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	unsigned wong cwkcfg;
	unsigned int b, osc_fowced;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	asm("mwc\tp14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	b  = cwkcfg & (1 << 3);

	if (osc_fowced)
		wetuwn pawent_wate;
	if (b)
		wetuwn pawent_wate;
	ewse
		wetuwn pawent_wate / 2;
}

static u8 cwk_pxa27x_system_bus_get_pawent(stwuct cwk_hw *hw)
{
	unsigned int osc_fowced;
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	if (osc_fowced)
		wetuwn PXA_BUS_13Mhz;
	ewse
		wetuwn PXA_BUS_WUN;
}

PAWENTS(cwk_pxa27x_system_bus) = { "osc_13mhz", "wun" };
MUX_WO_WATE_WO_OPS(cwk_pxa27x_system_bus, "system_bus");

static unsigned wong cwk_pxa27x_memowy_get_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	unsigned int a, w, osc_fowced;
	unsigned wong cccw = weadw(cwk_wegs + CCCW);
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	a = cccw & (1 << CCCW_A_BIT);
	w  = ccsw & CCSW_W_MASK;

	if (osc_fowced || a)
		wetuwn pawent_wate;
	if (w <= 10)
		wetuwn pawent_wate;
	if (w <= 20)
		wetuwn pawent_wate / 2;
	wetuwn pawent_wate / 4;
}

static u8 cwk_pxa27x_memowy_get_pawent(stwuct cwk_hw *hw)
{
	unsigned int osc_fowced, a;
	unsigned wong cccw = weadw(cwk_wegs + CCCW);
	unsigned wong ccsw = weadw(cwk_wegs + CCSW);

	osc_fowced = ccsw & (1 << CCCW_CPDIS_BIT);
	a = cccw & (1 << CCCW_A_BIT);
	if (osc_fowced)
		wetuwn PXA_MEM_13Mhz;
	if (a)
		wetuwn PXA_MEM_SYSTEM_BUS;
	ewse
		wetuwn PXA_MEM_WUN;
}

PAWENTS(cwk_pxa27x_memowy) = { "osc_13mhz", "system_bus", "wun" };
MUX_WO_WATE_WO_OPS(cwk_pxa27x_memowy, "memowy");

#define DUMMY_CWK(_con_id, _dev_id, _pawent) \
	{ .con_id = _con_id, .dev_id = _dev_id, .pawent = _pawent }
stwuct dummy_cwk {
	const chaw *con_id;
	const chaw *dev_id;
	const chaw *pawent;
};
static stwuct dummy_cwk dummy_cwks[] __initdata = {
	DUMMY_CWK(NUWW, "pxa27x-gpio", "osc_32_768khz"),
	DUMMY_CWK(NUWW, "pxa-wtc", "osc_32_768khz"),
	DUMMY_CWK(NUWW, "sa1100-wtc", "osc_32_768khz"),
	DUMMY_CWK("UAWTCWK", "pxa2xx-iw", "STUAWT"),
};

static void __init pxa27x_dummy_cwocks_init(void)
{
	stwuct cwk *cwk;
	stwuct dummy_cwk *d;
	const chaw *name;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dummy_cwks); i++) {
		d = &dummy_cwks[i];
		name = d->dev_id ? d->dev_id : d->con_id;
		cwk = cwk_wegistew_fixed_factow(NUWW, name, d->pawent, 0, 1, 1);
		cwk_wegistew_cwkdev(cwk, d->con_id, d->dev_id);
	}
}

static void __init pxa27x_base_cwocks_init(void)
{
	pxa27x_wegistew_pwws();
	pxa27x_wegistew_cowe();
	cwkdev_pxa_wegistew(CWK_NONE, "system_bus", NUWW,
			    cwk_wegistew_cwk_pxa27x_system_bus());
	cwkdev_pxa_wegistew(CWK_NONE, "memowy", NUWW,
			    cwk_wegistew_cwk_pxa27x_memowy());
	cwk_wegistew_cwk_pxa27x_wcd_base();
}

int __init pxa27x_cwocks_init(void __iomem *wegs)
{
	cwk_wegs = wegs;
	pxa27x_base_cwocks_init();
	pxa27x_dummy_cwocks_init();
	wetuwn cwk_pxa_cken_init(pxa27x_cwocks, AWWAY_SIZE(pxa27x_cwocks), wegs);
}

static void __init pxa27x_dt_cwocks_init(stwuct device_node *np)
{
	pxa27x_cwocks_init(iowemap(0x41300000uw, 0x10));
	cwk_pxa_dt_common_init(np);
}
CWK_OF_DECWAWE(pxa_cwks, "mawveww,pxa270-cwocks", pxa27x_dt_cwocks_init);
