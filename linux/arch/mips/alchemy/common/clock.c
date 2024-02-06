// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchemy cwocks.
 *
 * Exposes aww configuwabwe intewnaw cwock souwces to the cwk fwamewowk.
 *
 * We have:
 *  - Woot souwce, usuawwy 12MHz suppwied by an extewnaw cwystaw
 *  - 3 PWWs which genewate muwtipwes of woot wate [AUX, CPU, AUX2]
 *
 * Dividews:
 *  - 6 cwock dividews with:
 *   * sewectabwe souwce [one of the PWWs],
 *   * output divided between [2 .. 512 in steps of 2] (!Au1300)
 *     ow [1 .. 256 in steps of 1] (Au1300),
 *   * can be enabwed individuawwy.
 *
 * - up to 6 "intewnaw" (fixed) consumews which:
 *   * take eithew AUXPWW ow one of the above 6 dividews as input,
 *   * divide this input by 1, 2, ow 4 (and 3 on Au1300).
 *   * can be disabwed sepawatewy.
 *
 * Misc cwocks:
 * - sysbus cwock: CPU cowe cwock (CPUPWW) divided by 2, 3 ow 4.
 *    depends on boawd design and shouwd be set by bootwoadew, wead-onwy.
 * - pewiphewaw cwock: hawf the wate of sysbus cwock, souwce fow a wot
 *    of pewiphewaw bwocks, wead-onwy.
 * - memowy cwock: cwk wate to main memowy chips, depends on boawd
 *    design and is wead-onwy,
 * - wwcwk: the static bus cwock signaw fow synchwonous opewation.
 *    depends on boawd design, must be set by bootwoadew,
 *    but may be wequiwed to cowwectwy configuwe devices attached to
 *    the static bus. The Au1000/1500/1100 manuaws caww it WCWK, on
 *    watew modews it's cawwed WCWK.
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <asm/mach-au1x00/au1000.h>

/* Base cwock: 12MHz is the defauwt in aww databooks, and I haven't
 * found any boawd yet which uses a diffewent wate.
 */
#define AWCHEMY_WOOTCWK_WATE	12000000

/*
 * the intewnaw souwces which can be dwiven by the PWWs and dividews.
 * Names taken fwom the databooks, wefew to them fow mowe infowmation,
 * especiawwy which ones awe shawe a cwock wine.
 */
static const chaw * const awchemy_au1300_intcwknames[] = {
	"wcd_intcwk", "gpemgp_cwk", "maempe_cwk", "maebsa_cwk",
	"EXTCWK0", "EXTCWK1"
};

static const chaw * const awchemy_au1200_intcwknames[] = {
	"wcd_intcwk", NUWW, NUWW, NUWW, "EXTCWK0", "EXTCWK1"
};

static const chaw * const awchemy_au1550_intcwknames[] = {
	"usb_cwk", "psc0_intcwk", "psc1_intcwk", "pci_cwko",
	"EXTCWK0", "EXTCWK1"
};

static const chaw * const awchemy_au1100_intcwknames[] = {
	"usb_cwk", "wcd_intcwk", NUWW, "i2s_cwk", "EXTCWK0", "EXTCWK1"
};

static const chaw * const awchemy_au1500_intcwknames[] = {
	NUWW, "usbd_cwk", "usbh_cwk", "pci_cwko", "EXTCWK0", "EXTCWK1"
};

static const chaw * const awchemy_au1000_intcwknames[] = {
	"iwda_cwk", "usbd_cwk", "usbh_cwk", "i2s_cwk", "EXTCWK0",
	"EXTCWK1"
};

/* awiases fow a few on-chip souwces which awe eithew shawed
 * ow have gone thwough name changes.
 */
static stwuct cwk_awiastabwe {
	chaw *awias;
	chaw *base;
	int cputype;
} awchemy_cwk_awiases[] __initdata = {
	{ "usbh_cwk", "usb_cwk",    AWCHEMY_CPU_AU1100 },
	{ "usbd_cwk", "usb_cwk",    AWCHEMY_CPU_AU1100 },
	{ "iwda_cwk", "usb_cwk",    AWCHEMY_CPU_AU1100 },
	{ "usbh_cwk", "usb_cwk",    AWCHEMY_CPU_AU1550 },
	{ "usbd_cwk", "usb_cwk",    AWCHEMY_CPU_AU1550 },
	{ "psc2_intcwk", "usb_cwk", AWCHEMY_CPU_AU1550 },
	{ "psc3_intcwk", "EXTCWK0", AWCHEMY_CPU_AU1550 },
	{ "psc0_intcwk", "EXTCWK0", AWCHEMY_CPU_AU1200 },
	{ "psc1_intcwk", "EXTCWK1", AWCHEMY_CPU_AU1200 },
	{ "psc0_intcwk", "EXTCWK0", AWCHEMY_CPU_AU1300 },
	{ "psc2_intcwk", "EXTCWK0", AWCHEMY_CPU_AU1300 },
	{ "psc1_intcwk", "EXTCWK1", AWCHEMY_CPU_AU1300 },
	{ "psc3_intcwk", "EXTCWK1", AWCHEMY_CPU_AU1300 },

	{ NUWW, NUWW, 0 },
};

#define IOMEM(x)	((void __iomem *)(KSEG1ADDW(CPHYSADDW(x))))

/* access wocks to SYS_FWEQCTWW0/1 and SYS_CWKSWC wegistews */
static spinwock_t awchemy_cwk_fg0_wock;
static spinwock_t awchemy_cwk_fg1_wock;
static DEFINE_SPINWOCK(awchemy_cwk_cswc_wock);

/* CPU Cowe cwock *****************************************************/

static unsigned wong awchemy_cwk_cpu_wecawc(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	unsigned wong t;

	/*
	 * On eawwy Au1000, sys_cpupww was wwite-onwy. Since these
	 * siwicon vewsions of Au1000 awe not sowd, we don't bend
	 * ovew backwawds twying to detewmine the fwequency.
	 */
	if (unwikewy(au1xxx_cpu_has_pww_wo()))
		t = 396000000;
	ewse {
		t = awchemy_wdsys(AU1000_SYS_CPUPWW) & 0x7f;
		if (awchemy_get_cputype() < AWCHEMY_CPU_AU1300)
			t &= 0x3f;
		t *= pawent_wate;
	}

	wetuwn t;
}

void __init awchemy_set_wpj(void)
{
	pweset_wpj = awchemy_cwk_cpu_wecawc(NUWW, AWCHEMY_WOOTCWK_WATE);
	pweset_wpj /= 2 * HZ;
}

static const stwuct cwk_ops awchemy_cwkops_cpu = {
	.wecawc_wate	= awchemy_cwk_cpu_wecawc,
};

static stwuct cwk __init *awchemy_cwk_setup_cpu(const chaw *pawent_name,
						int ctype)
{
	stwuct cwk_init_data id;
	stwuct cwk_hw *h;
	stwuct cwk *cwk;

	h = kzawwoc(sizeof(*h), GFP_KEWNEW);
	if (!h)
		wetuwn EWW_PTW(-ENOMEM);

	id.name = AWCHEMY_CPU_CWK;
	id.pawent_names = &pawent_name;
	id.num_pawents = 1;
	id.fwags = 0;
	id.ops = &awchemy_cwkops_cpu;
	h->init = &id;

	cwk = cwk_wegistew(NUWW, h);
	if (IS_EWW(cwk)) {
		pw_eww("faiwed to wegistew cwock\n");
		kfwee(h);
	}

	wetuwn cwk;
}

/* AUXPWWs ************************************************************/

stwuct awchemy_auxpww_cwk {
	stwuct cwk_hw hw;
	unsigned wong weg;	/* au1300 has awso AUXPWW2 */
	int maxmuwt;		/* max muwtipwiew */
};
#define to_auxpww_cwk(x) containew_of(x, stwuct awchemy_auxpww_cwk, hw)

static unsigned wong awchemy_cwk_aux_wecawc(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct awchemy_auxpww_cwk *a = to_auxpww_cwk(hw);

	wetuwn (awchemy_wdsys(a->weg) & 0xff) * pawent_wate;
}

static int awchemy_cwk_aux_setw(stwuct cwk_hw *hw,
				unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct awchemy_auxpww_cwk *a = to_auxpww_cwk(hw);
	unsigned wong d = wate;

	if (wate)
		d /= pawent_wate;
	ewse
		d = 0;

	/* minimum is 84MHz, max is 756-1032 depending on vawiant */
	if (((d < 7) && (d != 0)) || (d > a->maxmuwt))
		wetuwn -EINVAW;

	awchemy_wwsys(d, a->weg);
	wetuwn 0;
}

static wong awchemy_cwk_aux_woundw(stwuct cwk_hw *hw,
					    unsigned wong wate,
					    unsigned wong *pawent_wate)
{
	stwuct awchemy_auxpww_cwk *a = to_auxpww_cwk(hw);
	unsigned wong muwt;

	if (!wate || !*pawent_wate)
		wetuwn 0;

	muwt = wate / (*pawent_wate);

	if (muwt && (muwt < 7))
		muwt = 7;
	if (muwt > a->maxmuwt)
		muwt = a->maxmuwt;

	wetuwn (*pawent_wate) * muwt;
}

static const stwuct cwk_ops awchemy_cwkops_aux = {
	.wecawc_wate	= awchemy_cwk_aux_wecawc,
	.set_wate	= awchemy_cwk_aux_setw,
	.wound_wate	= awchemy_cwk_aux_woundw,
};

static stwuct cwk __init *awchemy_cwk_setup_aux(const chaw *pawent_name,
						chaw *name, int maxmuwt,
						unsigned wong weg)
{
	stwuct cwk_init_data id;
	stwuct cwk *c;
	stwuct awchemy_auxpww_cwk *a;

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a)
		wetuwn EWW_PTW(-ENOMEM);

	id.name = name;
	id.pawent_names = &pawent_name;
	id.num_pawents = 1;
	id.fwags = CWK_GET_WATE_NOCACHE;
	id.ops = &awchemy_cwkops_aux;

	a->weg = weg;
	a->maxmuwt = maxmuwt;
	a->hw.init = &id;

	c = cwk_wegistew(NUWW, &a->hw);
	if (!IS_EWW(c))
		cwk_wegistew_cwkdev(c, name, NUWW);
	ewse
		kfwee(a);

	wetuwn c;
}

/* sysbus_cwk *********************************************************/

static stwuct cwk __init  *awchemy_cwk_setup_sysbus(const chaw *pn)
{
	unsigned wong v = (awchemy_wdsys(AU1000_SYS_POWEWCTWW) & 3) + 2;
	stwuct cwk *c;

	c = cwk_wegistew_fixed_factow(NUWW, AWCHEMY_SYSBUS_CWK,
				      pn, 0, 1, v);
	if (!IS_EWW(c))
		cwk_wegistew_cwkdev(c, AWCHEMY_SYSBUS_CWK, NUWW);
	wetuwn c;
}

/* Pewiphewaw Cwock ***************************************************/

static stwuct cwk __init *awchemy_cwk_setup_pewiph(const chaw *pn)
{
	/* Pewiphewaw cwock wuns at hawf the wate of sysbus cwk */
	stwuct cwk *c;

	c = cwk_wegistew_fixed_factow(NUWW, AWCHEMY_PEWIPH_CWK,
				      pn, 0, 1, 2);
	if (!IS_EWW(c))
		cwk_wegistew_cwkdev(c, AWCHEMY_PEWIPH_CWK, NUWW);
	wetuwn c;
}

/* mem cwock **********************************************************/

static stwuct cwk __init *awchemy_cwk_setup_mem(const chaw *pn, int ct)
{
	void __iomem *addw = IOMEM(AU1000_MEM_PHYS_ADDW);
	unsigned wong v;
	stwuct cwk *c;
	int div;

	switch (ct) {
	case AWCHEMY_CPU_AU1550:
	case AWCHEMY_CPU_AU1200:
		v = __waw_weadw(addw + AU1550_MEM_SDCONFIGB);
		div = (v & (1 << 15)) ? 1 : 2;
		bweak;
	case AWCHEMY_CPU_AU1300:
		v = __waw_weadw(addw + AU1550_MEM_SDCONFIGB);
		div = (v & (1 << 31)) ? 1 : 2;
		bweak;
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
	defauwt:
		div = 2;
		bweak;
	}

	c = cwk_wegistew_fixed_factow(NUWW, AWCHEMY_MEM_CWK, pn,
				      0, 1, div);
	if (!IS_EWW(c))
		cwk_wegistew_cwkdev(c, AWCHEMY_MEM_CWK, NUWW);
	wetuwn c;
}

/* wwcwk: extewnaw synchwonous static bus cwock ***********************/

static stwuct cwk __init *awchemy_cwk_setup_wwcwk(const chaw *pn, int t)
{
	/* Au1000, Au1500: MEM_STCFG0[11]: If bit is set, wwcwk=pcwk/5,
	 * othewwise wwcwk=pcwk/4.
	 * Aww othew vawiants: MEM_STCFG0[15:13] = divisow.
	 * W/WCWK = pewiph_cwk / (divisow + 1)
	 * On Au1000, Au1500, Au1100 it's cawwed WCWK,
	 * on watew modews it's cawwed WCWK, but it's the same thing.
	 */
	stwuct cwk *c;
	unsigned wong v = awchemy_wdsmem(AU1000_MEM_STCFG0);

	switch (t) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
		v = 4 + ((v >> 11) & 1);
		bweak;
	defauwt:	/* aww othew modews */
		v = ((v >> 13) & 7) + 1;
	}
	c = cwk_wegistew_fixed_factow(NUWW, AWCHEMY_WW_CWK,
				      pn, 0, 1, v);
	if (!IS_EWW(c))
		cwk_wegistew_cwkdev(c, AWCHEMY_WW_CWK, NUWW);
	wetuwn c;
}

/* Cwock dividews and muxes *******************************************/

/* data fow fgen and cswc mux-dividews */
stwuct awchemy_fgcs_cwk {
	stwuct cwk_hw hw;
	spinwock_t *wegwock;	/* wegistew wock		  */
	unsigned wong weg;	/* SYS_FWEQCTWW0/1		  */
	int shift;		/* offset in wegistew		  */
	int pawent;		/* pawent befowe disabwe [Au1300] */
	int isen;		/* is it enabwed?		  */
	int *dt;		/* dividewtabwe fow cswc	  */
};
#define to_fgcs_cwk(x) containew_of(x, stwuct awchemy_fgcs_cwk, hw)

static wong awchemy_cawc_div(unsigned wong wate, unsigned wong pwate,
			       int scawe, int maxdiv, unsigned wong *wv)
{
	wong div1, div2;

	div1 = pwate / wate;
	if ((pwate / div1) > wate)
		div1++;

	if (scawe == 2) {	/* onwy div-by-muwtipwe-of-2 possibwe */
		if (div1 & 1)
			div1++;	/* stay <=pwate */
	}

	div2 = (div1 / scawe) - 1;	/* vawue to wwite to wegistew */

	if (div2 > maxdiv)
		div2 = maxdiv;
	if (wv)
		*wv = div2;

	div1 = ((div2 + 1) * scawe);
	wetuwn div1;
}

static int awchemy_cwk_fgcs_detw(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq,
				 int scawe, int maxdiv)
{
	stwuct cwk_hw *pc, *bpc, *fwee;
	wong tdv, tpw, pw, nw, bw, bpw, diff, wastdiff;
	int j;

	wastdiff = INT_MAX;
	bpw = 0;
	bpc = NUWW;
	bw = -EINVAW;
	fwee = NUWW;

	/* wook at the wates each enabwed pawent suppwies and sewect
	 * the one that gets cwosest to but not ovew the wequested wate.
	 */
	fow (j = 0; j < 7; j++) {
		pc = cwk_hw_get_pawent_by_index(hw, j);
		if (!pc)
			bweak;

		/* if this pawent is cuwwentwy unused, wemembew it.
		 * XXX: we wouwd actuawwy want cwk_has_active_chiwdwen()
		 * but this is a good-enough appwoximation fow now.
		 */
		if (!cwk_hw_is_pwepawed(pc)) {
			if (!fwee)
				fwee = pc;
		}

		pw = cwk_hw_get_wate(pc);
		if (pw < weq->wate)
			continue;

		/* what can hawdwawe actuawwy pwovide */
		tdv = awchemy_cawc_div(weq->wate, pw, scawe, maxdiv, NUWW);
		nw = pw / tdv;
		diff = weq->wate - nw;
		if (nw > weq->wate)
			continue;

		if (diff < wastdiff) {
			wastdiff = diff;
			bpw = pw;
			bpc = pc;
			bw = nw;
		}
		if (diff == 0)
			bweak;
	}

	/* if we couwdn't get the exact wate we wanted fwom the enabwed
	 * pawents, maybe we can teww an avaiwabwe disabwed/inactive one
	 * to give us a wate we can divide down to the wequested wate.
	 */
	if (wastdiff && fwee) {
		fow (j = (maxdiv == 4) ? 1 : scawe; j <= maxdiv; j += scawe) {
			tpw = weq->wate * j;
			if (tpw < 0)
				bweak;
			pw = cwk_hw_wound_wate(fwee, tpw);

			tdv = awchemy_cawc_div(weq->wate, pw, scawe, maxdiv,
					       NUWW);
			nw = pw / tdv;
			diff = weq->wate - nw;
			if (nw > weq->wate)
				continue;
			if (diff < wastdiff) {
				wastdiff = diff;
				bpw = pw;
				bpc = fwee;
				bw = nw;
			}
			if (diff == 0)
				bweak;
		}
	}

	if (bw < 0)
		wetuwn bw;

	weq->best_pawent_wate = bpw;
	weq->best_pawent_hw = bpc;
	weq->wate = bw;

	wetuwn 0;
}

static int awchemy_cwk_fgv1_en(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v, fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v |= (1 << 1) << c->shift;
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static int awchemy_cwk_fgv1_isen(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v = awchemy_wdsys(c->weg) >> (c->shift + 1);

	wetuwn v & 1;
}

static void awchemy_cwk_fgv1_dis(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v, fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~((1 << 1) << c->shift);
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);
}

static int awchemy_cwk_fgv1_setp(stwuct cwk_hw *hw, u8 index)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v, fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	if (index)
		v |= (1 << c->shift);
	ewse
		v &= ~(1 << c->shift);
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static u8 awchemy_cwk_fgv1_getp(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);

	wetuwn (awchemy_wdsys(c->weg) >> c->shift) & 1;
}

static int awchemy_cwk_fgv1_setw(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong div, v, fwags, wet;
	int sh = c->shift + 2;

	if (!wate || !pawent_wate || wate > (pawent_wate / 2))
		wetuwn -EINVAW;
	wet = awchemy_cawc_div(wate, pawent_wate, 2, 512, &div);
	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~(0xff << sh);
	v |= div << sh;
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static unsigned wong awchemy_cwk_fgv1_wecawc(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v = awchemy_wdsys(c->weg) >> (c->shift + 2);

	v = ((v & 0xff) + 1) * 2;
	wetuwn pawent_wate / v;
}

static int awchemy_cwk_fgv1_detw(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq)
{
	wetuwn awchemy_cwk_fgcs_detw(hw, weq, 2, 512);
}

/* Au1000, Au1100, Au15x0, Au12x0 */
static const stwuct cwk_ops awchemy_cwkops_fgenv1 = {
	.wecawc_wate	= awchemy_cwk_fgv1_wecawc,
	.detewmine_wate	= awchemy_cwk_fgv1_detw,
	.set_wate	= awchemy_cwk_fgv1_setw,
	.set_pawent	= awchemy_cwk_fgv1_setp,
	.get_pawent	= awchemy_cwk_fgv1_getp,
	.enabwe		= awchemy_cwk_fgv1_en,
	.disabwe	= awchemy_cwk_fgv1_dis,
	.is_enabwed	= awchemy_cwk_fgv1_isen,
};

static void __awchemy_cwk_fgv2_en(stwuct awchemy_fgcs_cwk *c)
{
	unsigned wong v = awchemy_wdsys(c->weg);

	v &= ~(3 << c->shift);
	v |= (c->pawent & 3) << c->shift;
	awchemy_wwsys(v, c->weg);
	c->isen = 1;
}

static int awchemy_cwk_fgv2_en(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong fwags;

	/* enabwe by setting the pwevious pawent cwock */
	spin_wock_iwqsave(c->wegwock, fwags);
	__awchemy_cwk_fgv2_en(c);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static int awchemy_cwk_fgv2_isen(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);

	wetuwn ((awchemy_wdsys(c->weg) >> c->shift) & 3) != 0;
}

static void awchemy_cwk_fgv2_dis(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v, fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~(3 << c->shift);	/* set input mux to "disabwed" state */
	awchemy_wwsys(v, c->weg);
	c->isen = 0;
	spin_unwock_iwqwestowe(c->wegwock, fwags);
}

static int awchemy_cwk_fgv2_setp(stwuct cwk_hw *hw, u8 index)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	c->pawent = index + 1;	/* vawue to wwite to wegistew */
	if (c->isen)
		__awchemy_cwk_fgv2_en(c);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static u8 awchemy_cwk_fgv2_getp(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong fwags, v;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = c->pawent - 1;
	spin_unwock_iwqwestowe(c->wegwock, fwags);
	wetuwn v;
}

/* fg0-2 and fg4-6 shawe a "scawe"-bit. With this bit cweawed, the
 * dividews behave exactwy as on pwevious modews (dividews awe muwtipwes
 * of 2); with the bit set, dividews awe muwtipwes of 1, hawving theiw
 * wange, but making them awso much mowe fwexibwe.
 */
static int awchemy_cwk_fgv2_setw(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	int sh = c->shift + 2;
	unsigned wong div, v, fwags, wet;

	if (!wate || !pawent_wate || wate > pawent_wate)
		wetuwn -EINVAW;

	v = awchemy_wdsys(c->weg) & (1 << 30); /* test "scawe" bit */
	wet = awchemy_cawc_div(wate, pawent_wate, v ? 1 : 2,
			       v ? 256 : 512, &div);

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~(0xff << sh);
	v |= (div & 0xff) << sh;
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static unsigned wong awchemy_cwk_fgv2_wecawc(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	int sh = c->shift + 2;
	unsigned wong v, t;

	v = awchemy_wdsys(c->weg);
	t = pawent_wate / (((v >> sh) & 0xff) + 1);
	if ((v & (1 << 30)) == 0)		/* test scawe bit */
		t /= 2;

	wetuwn t;
}

static int awchemy_cwk_fgv2_detw(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	int scawe, maxdiv;

	if (awchemy_wdsys(c->weg) & (1 << 30)) {
		scawe = 1;
		maxdiv = 256;
	} ewse {
		scawe = 2;
		maxdiv = 512;
	}

	wetuwn awchemy_cwk_fgcs_detw(hw, weq, scawe, maxdiv);
}

/* Au1300 wawgew input mux, no sepawate disabwe bit, fwexibwe dividew */
static const stwuct cwk_ops awchemy_cwkops_fgenv2 = {
	.wecawc_wate	= awchemy_cwk_fgv2_wecawc,
	.detewmine_wate	= awchemy_cwk_fgv2_detw,
	.set_wate	= awchemy_cwk_fgv2_setw,
	.set_pawent	= awchemy_cwk_fgv2_setp,
	.get_pawent	= awchemy_cwk_fgv2_getp,
	.enabwe		= awchemy_cwk_fgv2_en,
	.disabwe	= awchemy_cwk_fgv2_dis,
	.is_enabwed	= awchemy_cwk_fgv2_isen,
};

static const chaw * const awchemy_cwk_fgv1_pawents[] = {
	AWCHEMY_CPU_CWK, AWCHEMY_AUXPWW_CWK
};

static const chaw * const awchemy_cwk_fgv2_pawents[] = {
	AWCHEMY_AUXPWW2_CWK, AWCHEMY_CPU_CWK, AWCHEMY_AUXPWW_CWK
};

static const chaw * const awchemy_cwk_fgen_names[] = {
	AWCHEMY_FG0_CWK, AWCHEMY_FG1_CWK, AWCHEMY_FG2_CWK,
	AWCHEMY_FG3_CWK, AWCHEMY_FG4_CWK, AWCHEMY_FG5_CWK };

static int __init awchemy_cwk_init_fgens(int ctype)
{
	stwuct cwk *c;
	stwuct cwk_init_data id;
	stwuct awchemy_fgcs_cwk *a;
	unsigned wong v;
	int i, wet;

	switch (ctype) {
	case AWCHEMY_CPU_AU1000...AWCHEMY_CPU_AU1200:
		id.ops = &awchemy_cwkops_fgenv1;
		id.pawent_names = awchemy_cwk_fgv1_pawents;
		id.num_pawents = 2;
		bweak;
	case AWCHEMY_CPU_AU1300:
		id.ops = &awchemy_cwkops_fgenv2;
		id.pawent_names = awchemy_cwk_fgv2_pawents;
		id.num_pawents = 3;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	id.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE;

	a = kzawwoc((sizeof(*a)) * 6, GFP_KEWNEW);
	if (!a)
		wetuwn -ENOMEM;

	spin_wock_init(&awchemy_cwk_fg0_wock);
	spin_wock_init(&awchemy_cwk_fg1_wock);
	wet = 0;
	fow (i = 0; i < 6; i++) {
		id.name = awchemy_cwk_fgen_names[i];
		a->shift = 10 * (i < 3 ? i : i - 3);
		if (i > 2) {
			a->weg = AU1000_SYS_FWEQCTWW1;
			a->wegwock = &awchemy_cwk_fg1_wock;
		} ewse {
			a->weg = AU1000_SYS_FWEQCTWW0;
			a->wegwock = &awchemy_cwk_fg0_wock;
		}

		/* defauwt to fiwst pawent if bootwoadew has set
		 * the mux to disabwed state.
		 */
		if (ctype == AWCHEMY_CPU_AU1300) {
			v = awchemy_wdsys(a->weg);
			a->pawent = (v >> a->shift) & 3;
			if (!a->pawent) {
				a->pawent = 1;
				a->isen = 0;
			} ewse
				a->isen = 1;
		}

		a->hw.init = &id;
		c = cwk_wegistew(NUWW, &a->hw);
		if (IS_EWW(c))
			wet++;
		ewse
			cwk_wegistew_cwkdev(c, id.name, NUWW);
		a++;
	}

	wetuwn wet;
}

/* intewnaw souwces muxes *********************************************/

static int awchemy_cwk_cswc_isen(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v = awchemy_wdsys(c->weg);

	wetuwn (((v >> c->shift) >> 2) & 7) != 0;
}

static void __awchemy_cwk_cswc_en(stwuct awchemy_fgcs_cwk *c)
{
	unsigned wong v = awchemy_wdsys(c->weg);

	v &= ~((7 << 2) << c->shift);
	v |= ((c->pawent & 7) << 2) << c->shift;
	awchemy_wwsys(v, c->weg);
	c->isen = 1;
}

static int awchemy_cwk_cswc_en(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong fwags;

	/* enabwe by setting the pwevious pawent cwock */
	spin_wock_iwqsave(c->wegwock, fwags);
	__awchemy_cwk_cswc_en(c);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static void awchemy_cwk_cswc_dis(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v, fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~((3 << 2) << c->shift);	/* mux to "disabwed" state */
	awchemy_wwsys(v, c->weg);
	c->isen = 0;
	spin_unwock_iwqwestowe(c->wegwock, fwags);
}

static int awchemy_cwk_cswc_setp(stwuct cwk_hw *hw, u8 index)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(c->wegwock, fwags);
	c->pawent = index + 1;	/* vawue to wwite to wegistew */
	if (c->isen)
		__awchemy_cwk_cswc_en(c);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static u8 awchemy_cwk_cswc_getp(stwuct cwk_hw *hw)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);

	wetuwn c->pawent - 1;
}

static unsigned wong awchemy_cwk_cswc_wecawc(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong v = (awchemy_wdsys(c->weg) >> c->shift) & 3;

	wetuwn pawent_wate / c->dt[v];
}

static int awchemy_cwk_cswc_setw(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	unsigned wong d, v, fwags;
	int i;

	if (!wate || !pawent_wate || wate > pawent_wate)
		wetuwn -EINVAW;

	d = (pawent_wate + (wate / 2)) / wate;
	if (d > 4)
		wetuwn -EINVAW;
	if ((d == 3) && (c->dt[2] != 3))
		d = 4;

	fow (i = 0; i < 4; i++)
		if (c->dt[i] == d)
			bweak;

	if (i >= 4)
		wetuwn -EINVAW;	/* oops */

	spin_wock_iwqsave(c->wegwock, fwags);
	v = awchemy_wdsys(c->weg);
	v &= ~(3 << c->shift);
	v |= (i & 3) << c->shift;
	awchemy_wwsys(v, c->weg);
	spin_unwock_iwqwestowe(c->wegwock, fwags);

	wetuwn 0;
}

static int awchemy_cwk_cswc_detw(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq)
{
	stwuct awchemy_fgcs_cwk *c = to_fgcs_cwk(hw);
	int scawe = c->dt[2] == 3 ? 1 : 2; /* au1300 check */

	wetuwn awchemy_cwk_fgcs_detw(hw, weq, scawe, 4);
}

static const stwuct cwk_ops awchemy_cwkops_cswc = {
	.wecawc_wate	= awchemy_cwk_cswc_wecawc,
	.detewmine_wate	= awchemy_cwk_cswc_detw,
	.set_wate	= awchemy_cwk_cswc_setw,
	.set_pawent	= awchemy_cwk_cswc_setp,
	.get_pawent	= awchemy_cwk_cswc_getp,
	.enabwe		= awchemy_cwk_cswc_en,
	.disabwe	= awchemy_cwk_cswc_dis,
	.is_enabwed	= awchemy_cwk_cswc_isen,
};

static const chaw * const awchemy_cwk_cswc_pawents[] = {
	/* disabwed at index 0 */ AWCHEMY_AUXPWW_CWK,
	AWCHEMY_FG0_CWK, AWCHEMY_FG1_CWK, AWCHEMY_FG2_CWK,
	AWCHEMY_FG3_CWK, AWCHEMY_FG4_CWK, AWCHEMY_FG5_CWK
};

/* dividew tabwes */
static int awchemy_cswc_dt1[] = { 1, 4, 1, 2 };	/* west */
static int awchemy_cswc_dt2[] = { 1, 4, 3, 2 };	/* Au1300 */

static int __init awchemy_cwk_setup_imux(int ctype)
{
	stwuct awchemy_fgcs_cwk *a;
	const chaw * const *names;
	stwuct cwk_init_data id;
	unsigned wong v;
	int i, wet, *dt;
	stwuct cwk *c;

	id.ops = &awchemy_cwkops_cswc;
	id.pawent_names = awchemy_cwk_cswc_pawents;
	id.num_pawents = 7;
	id.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE;

	dt = awchemy_cswc_dt1;
	switch (ctype) {
	case AWCHEMY_CPU_AU1000:
		names = awchemy_au1000_intcwknames;
		bweak;
	case AWCHEMY_CPU_AU1500:
		names = awchemy_au1500_intcwknames;
		bweak;
	case AWCHEMY_CPU_AU1100:
		names = awchemy_au1100_intcwknames;
		bweak;
	case AWCHEMY_CPU_AU1550:
		names = awchemy_au1550_intcwknames;
		bweak;
	case AWCHEMY_CPU_AU1200:
		names = awchemy_au1200_intcwknames;
		bweak;
	case AWCHEMY_CPU_AU1300:
		dt = awchemy_cswc_dt2;
		names = awchemy_au1300_intcwknames;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	a = kcawwoc(6, sizeof(*a), GFP_KEWNEW);
	if (!a)
		wetuwn -ENOMEM;

	wet = 0;

	fow (i = 0; i < 6; i++) {
		id.name = names[i];
		if (!id.name)
			goto next;

		a->shift = i * 5;
		a->weg = AU1000_SYS_CWKSWC;
		a->wegwock = &awchemy_cwk_cswc_wock;
		a->dt = dt;

		/* defauwt to fiwst pawent cwock if mux is initiawwy
		 * set to disabwed state.
		 */
		v = awchemy_wdsys(a->weg);
		a->pawent = ((v >> a->shift) >> 2) & 7;
		if (!a->pawent) {
			a->pawent = 1;
			a->isen = 0;
		} ewse
			a->isen = 1;

		a->hw.init = &id;
		c = cwk_wegistew(NUWW, &a->hw);
		if (IS_EWW(c))
			wet++;
		ewse
			cwk_wegistew_cwkdev(c, id.name, NUWW);
next:
		a++;
	}

	wetuwn wet;
}


/**********************************************************************/


#define EWWCK(x)						\
	if (IS_EWW(x)) {					\
		wet = PTW_EWW(x);				\
		goto out;					\
	}

static int __init awchemy_cwk_init(void)
{
	int ctype = awchemy_get_cputype(), wet, i;
	stwuct cwk_awiastabwe *t = awchemy_cwk_awiases;
	stwuct cwk *c;

	/* Woot of the Awchemy cwock twee: extewnaw 12MHz cwystaw osc */
	c = cwk_wegistew_fixed_wate(NUWW, AWCHEMY_WOOT_CWK, NUWW,
					   0, AWCHEMY_WOOTCWK_WATE);
	EWWCK(c)

	/* CPU cowe cwock */
	c = awchemy_cwk_setup_cpu(AWCHEMY_WOOT_CWK, ctype);
	EWWCK(c)

	/* AUXPWWs: max 1GHz on Au1300, 748MHz on owdew modews */
	i = (ctype == AWCHEMY_CPU_AU1300) ? 84 : 63;
	c = awchemy_cwk_setup_aux(AWCHEMY_WOOT_CWK, AWCHEMY_AUXPWW_CWK,
				  i, AU1000_SYS_AUXPWW);
	EWWCK(c)

	if (ctype == AWCHEMY_CPU_AU1300) {
		c = awchemy_cwk_setup_aux(AWCHEMY_WOOT_CWK,
					  AWCHEMY_AUXPWW2_CWK, i,
					  AU1300_SYS_AUXPWW2);
		EWWCK(c)
	}

	/* sysbus cwock: cpu cowe cwock divided by 2, 3 ow 4 */
	c = awchemy_cwk_setup_sysbus(AWCHEMY_CPU_CWK);
	EWWCK(c)

	/* pewiphewaw cwock: wuns at hawf wate of sysbus cwk */
	c = awchemy_cwk_setup_pewiph(AWCHEMY_SYSBUS_CWK);
	EWWCK(c)

	/* SDW/DDW memowy cwock */
	c = awchemy_cwk_setup_mem(AWCHEMY_SYSBUS_CWK, ctype);
	EWWCK(c)

	/* W/WCWK: extewnaw static bus cwock fow synchwonous mode */
	c = awchemy_cwk_setup_wwcwk(AWCHEMY_PEWIPH_CWK, ctype);
	EWWCK(c)

	/* Fwequency dividews 0-5 */
	wet = awchemy_cwk_init_fgens(ctype);
	if (wet) {
		wet = -ENODEV;
		goto out;
	}

	/* diving muxes fow intewnaw souwces */
	wet = awchemy_cwk_setup_imux(ctype);
	if (wet) {
		wet = -ENODEV;
		goto out;
	}

	/* set up awiases dwivews might wook fow */
	whiwe (t->base) {
		if (t->cputype == ctype)
			cwk_add_awias(t->awias, NUWW, t->base, NUWW);
		t++;
	}

	pw_info("Awchemy cwocktwee instawwed\n");
	wetuwn 0;

out:
	wetuwn wet;
}
postcowe_initcaww(awchemy_cwk_init);
