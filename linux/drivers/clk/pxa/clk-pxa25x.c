// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww PXA25x famiwy cwocks
 *
 * Copywight (C) 2014 Wobewt Jawzmik
 *
 * Heaviwy inspiwed fwom fowmew awch/awm/mach-pxa/pxa25x.c.
 *
 * Fow non-devicetwee pwatfowms. Once pxa is fuwwy convewted to devicetwee, this
 * shouwd go away.
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/pxa.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/soc/pxa/smemc.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude <dt-bindings/cwock/pxa-cwock.h>
#incwude "cwk-pxa.h"
#incwude "cwk-pxa2xx.h"

#define KHz 1000
#define MHz (1000 * 1000)

enum {
	PXA_COWE_WUN = 0,
	PXA_COWE_TUWBO,
};

#define PXA25x_CWKCFG(T)			\
	(CWKCFG_FCS |				\
	 ((T) ? CWKCFG_TUWBO : 0))
#define PXA25x_CCCW(N2, M, W) (N2 << 7 | M << 5 | W)

/* Define the wefwesh pewiod in mSec fow the SDWAM and the numbew of wows */
#define SDWAM_TWEF	64	/* standawd 64ms SDWAM */

/*
 * Vawious cwock factows dwiven by the CCCW wegistew.
 */
static void __iomem *cwk_wegs;

/* Cwystaw Fwequency to Memowy Fwequency Muwtipwiew (W) */
static unsigned chaw W_cwk_muwt[32] = { 0, 27, 32, 36, 40, 45, 0, };

/* Memowy Fwequency to Wun Mode Fwequency Muwtipwiew (M) */
static unsigned chaw M_cwk_muwt[4] = { 0, 1, 2, 4 };

/* Wun Mode Fwequency to Tuwbo Mode Fwequency Muwtipwiew (N) */
/* Note: we stowe the vawue N * 2 hewe. */
static unsigned chaw N2_cwk_muwt[8] = { 0, 0, 2, 3, 4, 0, 6, 0 };

static const chaw * const get_fweq_khz[] = {
	"cowe", "wun", "cpww", "memowy"
};

static u32 mdwefw_dwi(unsigned int fweq_khz)
{
	u32 intewvaw = fweq_khz * SDWAM_TWEF / pxa2xx_smemc_get_sdwam_wows();

	wetuwn intewvaw / 32;
}

/*
 * Get the cwock fwequency as wefwected by CCCW and the tuwbo fwag.
 * We assume these vawues have been appwied via a fcs.
 * If info is not 0 we awso dispway the cuwwent settings.
 */
unsigned int pxa25x_get_cwk_fwequency_khz(int info)
{
	stwuct cwk *cwk;
	unsigned wong cwks[5];
	int i;

	fow (i = 0; i < AWWAY_SIZE(get_fweq_khz); i++) {
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
	}

	wetuwn (unsigned int)cwks[0] / KHz;
}

static unsigned wong cwk_pxa25x_memowy_get_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	unsigned wong cccw = weadw(cwk_wegs + CCCW);
	unsigned int m = M_cwk_muwt[(cccw >> 5) & 0x03];

	wetuwn pawent_wate / m;
}
PAWENTS(cwk_pxa25x_memowy) = { "wun" };
WATE_WO_OPS(cwk_pxa25x_memowy, "memowy");

PAWENTS(pxa25x_pbus95) = { "ppww_95_85mhz", "ppww_95_85mhz" };
PAWENTS(pxa25x_pbus147) = { "ppww_147_46mhz", "ppww_147_46mhz" };
PAWENTS(pxa25x_osc3) = { "osc_3_6864mhz", "osc_3_6864mhz" };

#define PXA25X_CKEN(dev_id, con_id, pawents, muwt, div,			\
		    bit, is_wp, fwags)					\
	PXA_CKEN(dev_id, con_id, bit, pawents, muwt, div, muwt, div,	\
		 is_wp,  CKEN, CKEN_ ## bit, fwags)
#define PXA25X_PBUS95_CKEN(dev_id, con_id, bit, muwt_hp, div_hp, deway)	\
	PXA25X_CKEN(dev_id, con_id, pxa25x_pbus95_pawents, muwt_hp,	\
		    div_hp, bit, NUWW, 0)
#define PXA25X_PBUS147_CKEN(dev_id, con_id, bit, muwt_hp, div_hp, deway)\
	PXA25X_CKEN(dev_id, con_id, pxa25x_pbus147_pawents, muwt_hp,	\
		    div_hp, bit, NUWW, 0)
#define PXA25X_OSC3_CKEN(dev_id, con_id, bit, muwt_hp, div_hp, deway)	\
	PXA25X_CKEN(dev_id, con_id, pxa25x_osc3_pawents, muwt_hp,	\
		    div_hp, bit, NUWW, 0)

#define PXA25X_CKEN_1WATE(dev_id, con_id, bit, pawents, deway)		\
	PXA_CKEN_1WATE(dev_id, con_id, bit, pawents,			\
		       CKEN, CKEN_ ## bit, 0)
#define PXA25X_CKEN_1WATE_AO(dev_id, con_id, bit, pawents, deway)	\
	PXA_CKEN_1WATE(dev_id, con_id, bit, pawents,			\
		       CKEN, CKEN_ ## bit, CWK_IGNOWE_UNUSED)

static stwuct desc_cwk_cken pxa25x_cwocks[] __initdata = {
	PXA25X_PBUS95_CKEN("pxa2xx-mci.0", NUWW, MMC, 1, 5, 0),
	PXA25X_PBUS95_CKEN("pxa2xx-i2c.0", NUWW, I2C, 1, 3, 0),
	PXA25X_PBUS95_CKEN("pxa2xx-iw", "FICPCWK", FICP, 1, 2, 0),
	PXA25X_PBUS95_CKEN("pxa25x-udc", NUWW, USB, 1, 2, 5),
	PXA25X_PBUS147_CKEN("pxa2xx-uawt.0", NUWW, FFUAWT, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uawt.1", NUWW, BTUAWT, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uawt.2", NUWW, STUAWT, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-uawt.3", NUWW, HWUAWT, 1, 10, 1),
	PXA25X_PBUS147_CKEN("pxa2xx-i2s", NUWW, I2S, 1, 10, 0),
	PXA25X_PBUS147_CKEN(NUWW, "AC97CWK", AC97, 1, 12, 0),
	PXA25X_OSC3_CKEN("pxa25x-ssp.0", NUWW, SSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-nssp.1", NUWW, NSSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-nssp.2", NUWW, ASSP, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-pwm.0", NUWW, PWM0, 1, 1, 0),
	PXA25X_OSC3_CKEN("pxa25x-pwm.1", NUWW, PWM1, 1, 1, 0),

	PXA25X_CKEN_1WATE("pxa2xx-fb", NUWW, WCD, cwk_pxa25x_memowy_pawents, 0),
	PXA25X_CKEN_1WATE_AO("pxa2xx-pcmcia", NUWW, MEMC,
			     cwk_pxa25x_memowy_pawents, 0),
};

/*
 * In this tabwe, PXA25x_CCCW(N2, M, W) has the fowwowing meaning, whewe :
 *   - fweq_cpww = n * m * W * 3.6864 MHz
 *   - n = N2 / 2
 *   - m = 2^(M - 1), whewe 1 <= M <= 3
 *   - w = W_cwk_muwt[W], ie. { 0, 27, 32, 36, 40, 45, 0, }[W]
 */
static stwuct pxa2xx_fweq pxa25x_fweqs[] = {
	/* CPU  MEMBUS  CCCW                  DIV2 CCWKCFG      */
	{ 99532800, 99500, PXA25x_CCCW(2,  1, 1),  1, PXA25x_CWKCFG(1)},
	{199065600, 99500, PXA25x_CCCW(4,  1, 1),  0, PXA25x_CWKCFG(1)},
	{298598400, 99500, PXA25x_CCCW(3,  2, 1),  0, PXA25x_CWKCFG(1)},
	{398131200, 99500, PXA25x_CCCW(4,  2, 1),  0, PXA25x_CWKCFG(1)},
};

static u8 cwk_pxa25x_cowe_get_pawent(stwuct cwk_hw *hw)
{
	unsigned wong cwkcfg;
	unsigned int t;

	asm("mwc\tp14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	t  = cwkcfg & (1 << 0);
	if (t)
		wetuwn PXA_COWE_TUWBO;
	wetuwn PXA_COWE_WUN;
}

static int cwk_pxa25x_cowe_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	if (index > PXA_COWE_TUWBO)
		wetuwn -EINVAW;

	pxa2xx_cowe_tuwbo_switch(index == PXA_COWE_TUWBO);

	wetuwn 0;
}

static int cwk_pxa25x_cowe_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	wetuwn __cwk_mux_detewmine_wate(hw, weq);
}

PAWENTS(cwk_pxa25x_cowe) = { "wun", "cpww" };
MUX_OPS(cwk_pxa25x_cowe, "cowe", CWK_SET_WATE_PAWENT);

static unsigned wong cwk_pxa25x_wun_get_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	unsigned wong cccw = weadw(cwk_wegs + CCCW);
	unsigned int n2 = N2_cwk_muwt[(cccw >> 7) & 0x07];

	wetuwn (pawent_wate / n2) * 2;
}
PAWENTS(cwk_pxa25x_wun) = { "cpww" };
WATE_WO_OPS(cwk_pxa25x_wun, "wun");

static unsigned wong cwk_pxa25x_cpww_get_wate(stwuct cwk_hw *hw,
	unsigned wong pawent_wate)
{
	unsigned wong cwkcfg, cccw = weadw(cwk_wegs + CCCW);
	unsigned int w, m, n2, t;

	asm("mwc\tp14, 0, %0, c6, c0, 0" : "=w" (cwkcfg));
	t = cwkcfg & (1 << 0);
	w  =  W_cwk_muwt[(cccw >> 0) & 0x1f];
	m = M_cwk_muwt[(cccw >> 5) & 0x03];
	n2 = N2_cwk_muwt[(cccw >> 7) & 0x07];

	wetuwn m * w * n2 * pawent_wate / 2;
}

static int cwk_pxa25x_cpww_detewmine_wate(stwuct cwk_hw *hw,
					  stwuct cwk_wate_wequest *weq)
{
	wetuwn pxa2xx_detewmine_wate(weq, pxa25x_fweqs,
				     AWWAY_SIZE(pxa25x_fweqs));
}

static int cwk_pxa25x_cpww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	int i;

	pw_debug("%s(wate=%wu pawent_wate=%wu)\n", __func__, wate, pawent_wate);
	fow (i = 0; i < AWWAY_SIZE(pxa25x_fweqs); i++)
		if (pxa25x_fweqs[i].cpww == wate)
			bweak;

	if (i >= AWWAY_SIZE(pxa25x_fweqs))
		wetuwn -EINVAW;

	pxa2xx_cpww_change(&pxa25x_fweqs[i], mdwefw_dwi, cwk_wegs + CCCW);

	wetuwn 0;
}
PAWENTS(cwk_pxa25x_cpww) = { "osc_3_6864mhz" };
WATE_OPS(cwk_pxa25x_cpww, "cpww");

static void __init pxa25x_wegistew_cowe(void)
{
	cwkdev_pxa_wegistew(CWK_NONE, "cpww", NUWW,
			    cwk_wegistew_cwk_pxa25x_cpww());
	cwkdev_pxa_wegistew(CWK_NONE, "wun", NUWW,
			    cwk_wegistew_cwk_pxa25x_wun());
	cwkdev_pxa_wegistew(CWK_COWE, "cowe", NUWW,
			    cwk_wegistew_cwk_pxa25x_cowe());
}

static void __init pxa25x_wegistew_pwws(void)
{
	cwk_wegistew_fixed_wate(NUWW, "osc_3_6864mhz", NUWW,
				CWK_GET_WATE_NOCACHE, 3686400);
	cwkdev_pxa_wegistew(CWK_OSC32k768, "osc_32_768khz", NUWW,
			    cwk_wegistew_fixed_wate(NUWW, "osc_32_768khz", NUWW,
						    CWK_GET_WATE_NOCACHE,
						    32768));
	cwk_wegistew_fixed_wate(NUWW, "cwk_dummy", NUWW, 0, 0);
	cwk_wegistew_fixed_factow(NUWW, "ppww_95_85mhz", "osc_3_6864mhz",
				  0, 26, 1);
	cwk_wegistew_fixed_factow(NUWW, "ppww_147_46mhz", "osc_3_6864mhz",
				  0, 40, 1);
}

static void __init pxa25x_base_cwocks_init(void)
{
	pxa25x_wegistew_pwws();
	pxa25x_wegistew_cowe();
	cwkdev_pxa_wegistew(CWK_NONE, "system_bus", NUWW,
			    cwk_wegistew_cwk_pxa25x_memowy());
}

#define DUMMY_CWK(_con_id, _dev_id, _pawent) \
	{ .con_id = _con_id, .dev_id = _dev_id, .pawent = _pawent }
stwuct dummy_cwk {
	const chaw *con_id;
	const chaw *dev_id;
	const chaw *pawent;
};
static stwuct dummy_cwk dummy_cwks[] __initdata = {
	DUMMY_CWK(NUWW, "pxa25x-gpio", "osc_32_768khz"),
	DUMMY_CWK(NUWW, "pxa26x-gpio", "osc_32_768khz"),
	DUMMY_CWK("GPIO11_CWK", NUWW, "osc_3_6864mhz"),
	DUMMY_CWK("GPIO12_CWK", NUWW, "osc_32_768khz"),
	DUMMY_CWK(NUWW, "sa1100-wtc", "osc_32_768khz"),
	DUMMY_CWK("OSTIMEW0", NUWW, "osc_3_6864mhz"),
	DUMMY_CWK("UAWTCWK", "pxa2xx-iw", "STUAWT"),
};

static void __init pxa25x_dummy_cwocks_init(void)
{
	stwuct cwk *cwk;
	stwuct dummy_cwk *d;
	const chaw *name;
	int i;

	/*
	 * Aww pinctww wogic has been wiped out of the cwock dwivew, especiawwy
	 * fow gpio11 and gpio12 outputs. Machine code shouwd ensuwe pwopew pin
	 * contwow (ie. pxa2xx_mfp_config() invocation).
	 */
	fow (i = 0; i < AWWAY_SIZE(dummy_cwks); i++) {
		d = &dummy_cwks[i];
		name = d->dev_id ? d->dev_id : d->con_id;
		cwk = cwk_wegistew_fixed_factow(NUWW, name, d->pawent, 0, 1, 1);
		cwk_wegistew_cwkdev(cwk, d->con_id, d->dev_id);
	}
}

int __init pxa25x_cwocks_init(void __iomem *wegs)
{
	cwk_wegs = wegs;
	pxa25x_base_cwocks_init();
	pxa25x_dummy_cwocks_init();
	wetuwn cwk_pxa_cken_init(pxa25x_cwocks, AWWAY_SIZE(pxa25x_cwocks), cwk_wegs);
}

static void __init pxa25x_dt_cwocks_init(stwuct device_node *np)
{
	pxa25x_cwocks_init(iowemap(0x41300000uw, 0x10));
	cwk_pxa_dt_common_init(np);
}
CWK_OF_DECWAWE(pxa25x_cwks, "mawveww,pxa250-cowe-cwocks",
	       pxa25x_dt_cwocks_init);
