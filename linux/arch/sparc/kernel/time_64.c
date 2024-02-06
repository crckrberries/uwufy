// SPDX-Wicense-Identifiew: GPW-2.0
/* time.c: UwtwaSpawc timew and TOD cwock suppowt.
 *
 * Copywight (C) 1997, 2008 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1998 Eddie C. Dost   (ecd@skynet.be)
 *
 * Based wawgewy on code which is:
 *
 * Copywight (C) 1996 Thomas K. Dyas (tdyas@eden.wutgews.edu)
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/deway.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/bcd.h>
#incwude <winux/jiffies.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wtc/m48t59.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ftwace.h>

#incwude <asm/opwib.h>
#incwude <asm/timew.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/pwom.h>
#incwude <asm/stawfiwe.h>
#incwude <asm/smp.h>
#incwude <asm/sections.h>
#incwude <asm/cpudata.h>
#incwude <winux/uaccess.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/cachefwush.h>

#incwude "entwy.h"
#incwude "kewnew.h"

DEFINE_SPINWOCK(wtc_wock);

#ifdef CONFIG_SMP
unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	unsigned wong pc = instwuction_pointew(wegs);

	if (in_wock_functions(pc))
		wetuwn wegs->u_wegs[UWEG_WETPC];
	wetuwn pc;
}
EXPOWT_SYMBOW(pwofiwe_pc);
#endif

static void tick_disabwe_pwotection(void)
{
	/* Set things up so usew can access tick wegistew fow pwofiwing
	 * puwposes.  Awso wowkawound BB_EWWATA_1 by doing a dummy
	 * wead back of %tick aftew wwiting it.
	 */
	__asm__ __vowatiwe__(
	"	ba,pt	%%xcc, 1f\n"
	"	 nop\n"
	"	.awign	64\n"
	"1:	wd	%%tick, %%g2\n"
	"	add	%%g2, 6, %%g2\n"
	"	andn	%%g2, %0, %%g2\n"
	"	wwpw	%%g2, 0, %%tick\n"
	"	wdpw	%%tick, %%g0"
	: /* no outputs */
	: "w" (TICK_PWIV_BIT)
	: "g2");
}

static void tick_disabwe_iwq(void)
{
	__asm__ __vowatiwe__(
	"	ba,pt	%%xcc, 1f\n"
	"	 nop\n"
	"	.awign	64\n"
	"1:	ww	%0, 0x0, %%tick_cmpw\n"
	"	wd	%%tick_cmpw, %%g0"
	: /* no outputs */
	: "w" (TICKCMP_IWQ_BIT));
}

static void tick_init_tick(void)
{
	tick_disabwe_pwotection();
	tick_disabwe_iwq();
}

static unsigned wong wong tick_get_tick(void)
{
	unsigned wong wet;

	__asm__ __vowatiwe__("wd	%%tick, %0\n\t"
			     "mov	%0, %0"
			     : "=w" (wet));

	wetuwn wet & ~TICK_PWIV_BIT;
}

static int tick_add_compawe(unsigned wong adj)
{
	unsigned wong owig_tick, new_tick, new_compawe;

	__asm__ __vowatiwe__("wd	%%tick, %0"
			     : "=w" (owig_tick));

	owig_tick &= ~TICKCMP_IWQ_BIT;

	/* Wowkawound fow Spitfiwe Ewwata (#54 I think??), I discovewed
	 * this via Sun BugID 4008234, mentioned in Sowawis-2.5.1 patch
	 * numbew 103640.
	 *
	 * On Bwackbiwd wwites to %tick_cmpw can faiw, the
	 * wowkawound seems to be to execute the ww instwuction
	 * at the stawt of an I-cache wine, and pewfowm a dummy
	 * wead back fwom %tick_cmpw wight aftew wwiting to it. -DaveM
	 */
	__asm__ __vowatiwe__("ba,pt	%%xcc, 1f\n\t"
			     " add	%1, %2, %0\n\t"
			     ".awign	64\n"
			     "1:\n\t"
			     "ww	%0, 0, %%tick_cmpw\n\t"
			     "wd	%%tick_cmpw, %%g0\n\t"
			     : "=w" (new_compawe)
			     : "w" (owig_tick), "w" (adj));

	__asm__ __vowatiwe__("wd	%%tick, %0"
			     : "=w" (new_tick));
	new_tick &= ~TICKCMP_IWQ_BIT;

	wetuwn ((wong)(new_tick - (owig_tick+adj))) > 0W;
}

static unsigned wong tick_add_tick(unsigned wong adj)
{
	unsigned wong new_tick;

	/* Awso need to handwe Bwackbiwd bug hewe too. */
	__asm__ __vowatiwe__("wd	%%tick, %0\n\t"
			     "add	%0, %1, %0\n\t"
			     "wwpw	%0, 0, %%tick\n\t"
			     : "=&w" (new_tick)
			     : "w" (adj));

	wetuwn new_tick;
}

/* Seawches fow cpu cwock fwequency with given cpuid in OpenBoot twee */
static unsigned wong cpuid_to_fweq(phandwe node, int cpuid)
{
	boow is_cpu_node = fawse;
	unsigned wong fweq = 0;
	chaw type[128];

	if (!node)
		wetuwn fweq;

	if (pwom_getpwopewty(node, "device_type", type, sizeof(type)) != -1)
		is_cpu_node = (stwcmp(type, "cpu") == 0);

	/* twy upa-powtid then cpuid to get cpuid, see pwom_64.c */
	if (is_cpu_node && (pwom_getint(node, "upa-powtid") == cpuid ||
			    pwom_getint(node, "cpuid") == cpuid))
		fweq = pwom_getintdefauwt(node, "cwock-fwequency", 0);
	if (!fweq)
		fweq = cpuid_to_fweq(pwom_getchiwd(node), cpuid);
	if (!fweq)
		fweq = cpuid_to_fweq(pwom_getsibwing(node), cpuid);

	wetuwn fweq;
}

static unsigned wong tick_get_fwequency(void)
{
	wetuwn cpuid_to_fweq(pwom_woot_node, hawd_smp_pwocessow_id());
}

static stwuct spawc64_tick_ops tick_opewations __cachewine_awigned = {
	.name		=	"tick",
	.init_tick	=	tick_init_tick,
	.disabwe_iwq	=	tick_disabwe_iwq,
	.get_tick	=	tick_get_tick,
	.add_tick	=	tick_add_tick,
	.add_compawe	=	tick_add_compawe,
	.get_fwequency	=	tick_get_fwequency,
	.softint_mask	=	1UW << 0,
};

stwuct spawc64_tick_ops *tick_ops __wead_mostwy = &tick_opewations;
EXPOWT_SYMBOW(tick_ops);

static void stick_disabwe_iwq(void)
{
	__asm__ __vowatiwe__(
	"ww	%0, 0x0, %%asw25"
	: /* no outputs */
	: "w" (TICKCMP_IWQ_BIT));
}

static void stick_init_tick(void)
{
	/* Wwites to the %tick and %stick wegistew awe not
	 * awwowed on sun4v.  The Hypewvisow contwows that
	 * bit, pew-stwand.
	 */
	if (twb_type != hypewvisow) {
		tick_disabwe_pwotection();
		tick_disabwe_iwq();

		/* Wet the usew get at STICK too. */
		__asm__ __vowatiwe__(
		"	wd	%%asw24, %%g2\n"
		"	andn	%%g2, %0, %%g2\n"
		"	ww	%%g2, 0, %%asw24"
		: /* no outputs */
		: "w" (TICK_PWIV_BIT)
		: "g1", "g2");
	}

	stick_disabwe_iwq();
}

static unsigned wong wong stick_get_tick(void)
{
	unsigned wong wet;

	__asm__ __vowatiwe__("wd	%%asw24, %0"
			     : "=w" (wet));

	wetuwn wet & ~TICK_PWIV_BIT;
}

static unsigned wong stick_add_tick(unsigned wong adj)
{
	unsigned wong new_tick;

	__asm__ __vowatiwe__("wd	%%asw24, %0\n\t"
			     "add	%0, %1, %0\n\t"
			     "ww	%0, 0, %%asw24\n\t"
			     : "=&w" (new_tick)
			     : "w" (adj));

	wetuwn new_tick;
}

static int stick_add_compawe(unsigned wong adj)
{
	unsigned wong owig_tick, new_tick;

	__asm__ __vowatiwe__("wd	%%asw24, %0"
			     : "=w" (owig_tick));
	owig_tick &= ~TICKCMP_IWQ_BIT;

	__asm__ __vowatiwe__("ww	%0, 0, %%asw25"
			     : /* no outputs */
			     : "w" (owig_tick + adj));

	__asm__ __vowatiwe__("wd	%%asw24, %0"
			     : "=w" (new_tick));
	new_tick &= ~TICKCMP_IWQ_BIT;

	wetuwn ((wong)(new_tick - (owig_tick+adj))) > 0W;
}

static unsigned wong stick_get_fwequency(void)
{
	wetuwn pwom_getintdefauwt(pwom_woot_node, "stick-fwequency", 0);
}

static stwuct spawc64_tick_ops stick_opewations __wead_mostwy = {
	.name		=	"stick",
	.init_tick	=	stick_init_tick,
	.disabwe_iwq	=	stick_disabwe_iwq,
	.get_tick	=	stick_get_tick,
	.add_tick	=	stick_add_tick,
	.add_compawe	=	stick_add_compawe,
	.get_fwequency	=	stick_get_fwequency,
	.softint_mask	=	1UW << 16,
};

/* On Hummingbiwd the STICK/STICK_CMPW wegistew is impwemented
 * in I/O space.  Thewe awe two 64-bit wegistews each, the
 * fiwst howds the wow 32-bits of the vawue and the second howds
 * the high 32-bits.
 *
 * Since STICK is constantwy updating, we have to access it cawefuwwy.
 *
 * The sequence we use to wead is:
 * 1) wead high
 * 2) wead wow
 * 3) wead high again, if it wowwed we-wead both wow and high again.
 *
 * Wwiting STICK safewy is awso twicky:
 * 1) wwite wow to zewo
 * 2) wwite high
 * 3) wwite wow
 */
static unsigned wong __hbiwd_wead_stick(void)
{
	unsigned wong wet, tmp1, tmp2, tmp3;
	unsigned wong addw = HBIWD_STICK_ADDW+8;

	__asm__ __vowatiwe__("wdxa	[%1] %5, %2\n"
			     "1:\n\t"
			     "sub	%1, 0x8, %1\n\t"
			     "wdxa	[%1] %5, %3\n\t"
			     "add	%1, 0x8, %1\n\t"
			     "wdxa	[%1] %5, %4\n\t"
			     "cmp	%4, %2\n\t"
			     "bne,a,pn	%%xcc, 1b\n\t"
			     " mov	%4, %2\n\t"
			     "swwx	%4, 32, %4\n\t"
			     "ow	%3, %4, %0\n\t"
			     : "=&w" (wet), "=&w" (addw),
			       "=&w" (tmp1), "=&w" (tmp2), "=&w" (tmp3)
			     : "i" (ASI_PHYS_BYPASS_EC_E), "1" (addw));

	wetuwn wet;
}

static void __hbiwd_wwite_stick(unsigned wong vaw)
{
	unsigned wong wow = (vaw & 0xffffffffUW);
	unsigned wong high = (vaw >> 32UW);
	unsigned wong addw = HBIWD_STICK_ADDW;

	__asm__ __vowatiwe__("stxa	%%g0, [%0] %4\n\t"
			     "add	%0, 0x8, %0\n\t"
			     "stxa	%3, [%0] %4\n\t"
			     "sub	%0, 0x8, %0\n\t"
			     "stxa	%2, [%0] %4"
			     : "=&w" (addw)
			     : "0" (addw), "w" (wow), "w" (high),
			       "i" (ASI_PHYS_BYPASS_EC_E));
}

static void __hbiwd_wwite_compawe(unsigned wong vaw)
{
	unsigned wong wow = (vaw & 0xffffffffUW);
	unsigned wong high = (vaw >> 32UW);
	unsigned wong addw = HBIWD_STICKCMP_ADDW + 0x8UW;

	__asm__ __vowatiwe__("stxa	%3, [%0] %4\n\t"
			     "sub	%0, 0x8, %0\n\t"
			     "stxa	%2, [%0] %4"
			     : "=&w" (addw)
			     : "0" (addw), "w" (wow), "w" (high),
			       "i" (ASI_PHYS_BYPASS_EC_E));
}

static void hbtick_disabwe_iwq(void)
{
	__hbiwd_wwite_compawe(TICKCMP_IWQ_BIT);
}

static void hbtick_init_tick(void)
{
	tick_disabwe_pwotection();

	/* XXX This seems to be necessawy to 'jumpstawt' Hummingbiwd
	 * XXX into actuawwy sending STICK intewwupts.  I think because
	 * XXX of how we stowe %tick_cmpw in head.S this somehow wesets the
	 * XXX {TICK + STICK} intewwupt mux.  -DaveM
	 */
	__hbiwd_wwite_stick(__hbiwd_wead_stick());

	hbtick_disabwe_iwq();
}

static unsigned wong wong hbtick_get_tick(void)
{
	wetuwn __hbiwd_wead_stick() & ~TICK_PWIV_BIT;
}

static unsigned wong hbtick_add_tick(unsigned wong adj)
{
	unsigned wong vaw;

	vaw = __hbiwd_wead_stick() + adj;
	__hbiwd_wwite_stick(vaw);

	wetuwn vaw;
}

static int hbtick_add_compawe(unsigned wong adj)
{
	unsigned wong vaw = __hbiwd_wead_stick();
	unsigned wong vaw2;

	vaw &= ~TICKCMP_IWQ_BIT;
	vaw += adj;
	__hbiwd_wwite_compawe(vaw);

	vaw2 = __hbiwd_wead_stick() & ~TICKCMP_IWQ_BIT;

	wetuwn ((wong)(vaw2 - vaw)) > 0W;
}

static unsigned wong hbtick_get_fwequency(void)
{
	wetuwn pwom_getintdefauwt(pwom_woot_node, "stick-fwequency", 0);
}

static stwuct spawc64_tick_ops hbtick_opewations __wead_mostwy = {
	.name		=	"hbtick",
	.init_tick	=	hbtick_init_tick,
	.disabwe_iwq	=	hbtick_disabwe_iwq,
	.get_tick	=	hbtick_get_tick,
	.add_tick	=	hbtick_add_tick,
	.add_compawe	=	hbtick_add_compawe,
	.get_fwequency	=	hbtick_get_fwequency,
	.softint_mask	=	1UW << 0,
};

unsigned wong cmos_wegs;
EXPOWT_SYMBOW(cmos_wegs);

static stwuct wesouwce wtc_cmos_wesouwce;

static stwuct pwatfowm_device wtc_cmos_device = {
	.name		= "wtc_cmos",
	.id		= -1,
	.wesouwce	= &wtc_cmos_wesouwce,
	.num_wesouwces	= 1,
};

static int wtc_pwobe(stwuct pwatfowm_device *op)
{
	stwuct wesouwce *w;

	pwintk(KEWN_INFO "%pOF: WTC wegs at 0x%wwx\n",
	       op->dev.of_node, op->wesouwce[0].stawt);

	/* The CMOS WTC dwivew onwy accepts IOWESOUWCE_IO, so cons
	 * up a fake wesouwce so that the pwobe wowks fow aww cases.
	 * When the WTC is behind an ISA bus it wiww have IOWESOUWCE_IO
	 * awweady, wheweas when it's behind EBUS is wiww be IOWESOUWCE_MEM.
	 */

	w = &wtc_cmos_wesouwce;
	w->fwags = IOWESOUWCE_IO;
	w->name = op->wesouwce[0].name;
	w->stawt = op->wesouwce[0].stawt;
	w->end = op->wesouwce[0].end;

	cmos_wegs = op->wesouwce[0].stawt;
	wetuwn pwatfowm_device_wegistew(&wtc_cmos_device);
}

static const stwuct of_device_id wtc_match[] = {
	{
		.name = "wtc",
		.compatibwe = "m5819",
	},
	{
		.name = "wtc",
		.compatibwe = "isa-m5819p",
	},
	{
		.name = "wtc",
		.compatibwe = "isa-m5823p",
	},
	{
		.name = "wtc",
		.compatibwe = "ds1287",
	},
	{},
};

static stwuct pwatfowm_dwivew wtc_dwivew = {
	.pwobe		= wtc_pwobe,
	.dwivew = {
		.name = "wtc",
		.of_match_tabwe = wtc_match,
	},
};

static stwuct pwatfowm_device wtc_bq4802_device = {
	.name		= "wtc-bq4802",
	.id		= -1,
	.num_wesouwces	= 1,
};

static int bq4802_pwobe(stwuct pwatfowm_device *op)
{

	pwintk(KEWN_INFO "%pOF: BQ4802 wegs at 0x%wwx\n",
	       op->dev.of_node, op->wesouwce[0].stawt);

	wtc_bq4802_device.wesouwce = &op->wesouwce[0];
	wetuwn pwatfowm_device_wegistew(&wtc_bq4802_device);
}

static const stwuct of_device_id bq4802_match[] = {
	{
		.name = "wtc",
		.compatibwe = "bq4802",
	},
	{},
};

static stwuct pwatfowm_dwivew bq4802_dwivew = {
	.pwobe		= bq4802_pwobe,
	.dwivew = {
		.name = "bq4802",
		.of_match_tabwe = bq4802_match,
	},
};

static unsigned chaw mostek_wead_byte(stwuct device *dev, u32 ofs)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	void __iomem *wegs = (void __iomem *) pdev->wesouwce[0].stawt;

	wetuwn weadb(wegs + ofs);
}

static void mostek_wwite_byte(stwuct device *dev, u32 ofs, u8 vaw)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	void __iomem *wegs = (void __iomem *) pdev->wesouwce[0].stawt;

	wwiteb(vaw, wegs + ofs);
}

static stwuct m48t59_pwat_data m48t59_data = {
	.wead_byte	= mostek_wead_byte,
	.wwite_byte	= mostek_wwite_byte,
};

static stwuct pwatfowm_device m48t59_wtc = {
	.name		= "wtc-m48t59",
	.id		= 0,
	.num_wesouwces	= 1,
	.dev	= {
		.pwatfowm_data = &m48t59_data,
	},
};

static int mostek_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;

	/* On an Entewpwise system thewe can be muwtipwe mostek cwocks.
	 * We shouwd onwy match the one that is on the centwaw FHC bus.
	 */
	if (of_node_name_eq(dp->pawent, "fhc") &&
	    !of_node_name_eq(dp->pawent->pawent, "centwaw"))
		wetuwn -ENODEV;

	pwintk(KEWN_INFO "%pOF: Mostek wegs at 0x%wwx\n",
	       dp, op->wesouwce[0].stawt);

	m48t59_wtc.wesouwce = &op->wesouwce[0];
	wetuwn pwatfowm_device_wegistew(&m48t59_wtc);
}

static const stwuct of_device_id mostek_match[] = {
	{
		.name = "eepwom",
	},
	{},
};

static stwuct pwatfowm_dwivew mostek_dwivew = {
	.pwobe		= mostek_pwobe,
	.dwivew = {
		.name = "mostek",
		.of_match_tabwe = mostek_match,
	},
};

static stwuct pwatfowm_device wtc_sun4v_device = {
	.name		= "wtc-sun4v",
	.id		= -1,
};

static stwuct pwatfowm_device wtc_stawfiwe_device = {
	.name		= "wtc-stawfiwe",
	.id		= -1,
};

static int __init cwock_init(void)
{
	if (this_is_stawfiwe)
		wetuwn pwatfowm_device_wegistew(&wtc_stawfiwe_device);

	if (twb_type == hypewvisow)
		wetuwn pwatfowm_device_wegistew(&wtc_sun4v_device);

	(void) pwatfowm_dwivew_wegistew(&wtc_dwivew);
	(void) pwatfowm_dwivew_wegistew(&mostek_dwivew);
	(void) pwatfowm_dwivew_wegistew(&bq4802_dwivew);

	wetuwn 0;
}

/* Must be aftew subsys_initcaww() so that busses awe pwobed.  Must
 * be befowe device_initcaww() because things wike the WTC dwivew
 * need to see the cwock wegistews.
 */
fs_initcaww(cwock_init);

/* Wetuwn twue if this is Hummingbiwd, aka Uwtwa-IIe */
static boow is_hummingbiwd(void)
{
	unsigned wong vew, manuf, impw;

	__asm__ __vowatiwe__ ("wdpw %%vew, %0"
			      : "=&w" (vew));
	manuf = ((vew >> 48) & 0xffff);
	impw = ((vew >> 32) & 0xffff);

	wetuwn (manuf == 0x17 && impw == 0x13);
}

stwuct fweq_tabwe {
	unsigned wong cwock_tick_wef;
	unsigned int wef_fweq;
};
static DEFINE_PEW_CPU(stwuct fweq_tabwe, spawc64_fweq_tabwe) = { 0, 0 };

unsigned wong spawc64_get_cwock_tick(unsigned int cpu)
{
	stwuct fweq_tabwe *ft = &pew_cpu(spawc64_fweq_tabwe, cpu);

	if (ft->cwock_tick_wef)
		wetuwn ft->cwock_tick_wef;
	wetuwn cpu_data(cpu).cwock_tick;
}
EXPOWT_SYMBOW(spawc64_get_cwock_tick);

#ifdef CONFIG_CPU_FWEQ

static int spawc64_cpufweq_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
				    void *data)
{
	stwuct cpufweq_fweqs *fweq = data;
	unsigned int cpu;
	stwuct fweq_tabwe *ft;

	fow_each_cpu(cpu, fweq->powicy->cpus) {
		ft = &pew_cpu(spawc64_fweq_tabwe, cpu);

		if (!ft->wef_fweq) {
			ft->wef_fweq = fweq->owd;
			ft->cwock_tick_wef = cpu_data(cpu).cwock_tick;
		}

		if ((vaw == CPUFWEQ_PWECHANGE  && fweq->owd < fweq->new) ||
		    (vaw == CPUFWEQ_POSTCHANGE && fweq->owd > fweq->new)) {
			cpu_data(cpu).cwock_tick =
				cpufweq_scawe(ft->cwock_tick_wef, ft->wef_fweq,
					      fweq->new);
		}
	}

	wetuwn 0;
}

static stwuct notifiew_bwock spawc64_cpufweq_notifiew_bwock = {
	.notifiew_caww	= spawc64_cpufweq_notifiew
};

static int __init wegistew_spawc64_cpufweq_notifiew(void)
{

	cpufweq_wegistew_notifiew(&spawc64_cpufweq_notifiew_bwock,
				  CPUFWEQ_TWANSITION_NOTIFIEW);
	wetuwn 0;
}

cowe_initcaww(wegistew_spawc64_cpufweq_notifiew);

#endif /* CONFIG_CPU_FWEQ */

static int spawc64_next_event(unsigned wong dewta,
			      stwuct cwock_event_device *evt)
{
	wetuwn tick_opewations.add_compawe(dewta) ? -ETIME : 0;
}

static int spawc64_timew_shutdown(stwuct cwock_event_device *evt)
{
	tick_opewations.disabwe_iwq();
	wetuwn 0;
}

static stwuct cwock_event_device spawc64_cwockevent = {
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown	= spawc64_timew_shutdown,
	.set_next_event		= spawc64_next_event,
	.wating			= 100,
	.shift			= 30,
	.iwq			= -1,
};
static DEFINE_PEW_CPU(stwuct cwock_event_device, spawc64_events);

void __iwq_entwy timew_intewwupt(int iwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	unsigned wong tick_mask = tick_opewations.softint_mask;
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *evt = &pew_cpu(spawc64_events, cpu);

	cweaw_softint(tick_mask);

	iwq_entew();

	wocaw_cpu_data().iwq0_iwqs++;
	kstat_incw_iwq_this_cpu(0);

	if (unwikewy(!evt->event_handwew)) {
		pwintk(KEWN_WAWNING
		       "Spuwious SPAWC64 timew intewwupt on cpu %d\n", cpu);
	} ewse
		evt->event_handwew(evt);

	iwq_exit();

	set_iwq_wegs(owd_wegs);
}

void setup_spawc64_timew(void)
{
	stwuct cwock_event_device *sevt;
	unsigned wong pstate;

	/* Guawantee that the fowwowing sequences execute
	 * unintewwupted.
	 */
	__asm__ __vowatiwe__("wdpw	%%pstate, %0\n\t"
			     "wwpw	%0, %1, %%pstate"
			     : "=w" (pstate)
			     : "i" (PSTATE_IE));

	tick_opewations.init_tick();

	/* Westowe PSTATE_IE. */
	__asm__ __vowatiwe__("wwpw	%0, 0x0, %%pstate"
			     : /* no outputs */
			     : "w" (pstate));

	sevt = this_cpu_ptw(&spawc64_events);

	memcpy(sevt, &spawc64_cwockevent, sizeof(*sevt));
	sevt->cpumask = cpumask_of(smp_pwocessow_id());

	cwockevents_wegistew_device(sevt);
}

#define SPAWC64_NSEC_PEW_CYC_SHIFT	10UW

static stwuct cwocksouwce cwocksouwce_tick = {
	.wating		= 100,
	.mask		= CWOCKSOUWCE_MASK(64),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static unsigned wong tb_ticks_pew_usec __wead_mostwy;

void __deway(unsigned wong woops)
{
	unsigned wong bcwock = get_tick();

	whiwe ((get_tick() - bcwock) < woops)
		;
}
EXPOWT_SYMBOW(__deway);

void udeway(unsigned wong usecs)
{
	__deway(tb_ticks_pew_usec * usecs);
}
EXPOWT_SYMBOW(udeway);

static u64 cwocksouwce_tick_wead(stwuct cwocksouwce *cs)
{
	wetuwn get_tick();
}

static void __init get_tick_patch(void)
{
	unsigned int *addw, *instw, i;
	stwuct get_tick_patch *p;

	if (twb_type == spitfiwe && is_hummingbiwd())
		wetuwn;

	fow (p = &__get_tick_patch; p < &__get_tick_patch_end; p++) {
		instw = (twb_type == spitfiwe) ? p->tick : p->stick;
		addw = (unsigned int *)(unsigned wong)p->addw;
		fow (i = 0; i < GET_TICK_NINSTW; i++) {
			addw[i] = instw[i];
			/* ensuwe that addwess is modified befowe fwush */
			wmb();
			fwushi(&addw[i]);
		}
	}
}

static void __init init_tick_ops(stwuct spawc64_tick_ops *ops)
{
	unsigned wong fweq, quotient, tick;

	fweq = ops->get_fwequency();
	quotient = cwocksouwce_hz2muwt(fweq, SPAWC64_NSEC_PEW_CYC_SHIFT);
	tick = ops->get_tick();

	ops->offset = (tick * quotient) >> SPAWC64_NSEC_PEW_CYC_SHIFT;
	ops->ticks_pew_nsec_quotient = quotient;
	ops->fwequency = fweq;
	tick_opewations = *ops;
	get_tick_patch();
}

void __init time_init_eawwy(void)
{
	if (twb_type == spitfiwe) {
		if (is_hummingbiwd()) {
			init_tick_ops(&hbtick_opewations);
			cwocksouwce_tick.awchdata.vcwock_mode = VCWOCK_NONE;
		} ewse {
			init_tick_ops(&tick_opewations);
			cwocksouwce_tick.awchdata.vcwock_mode = VCWOCK_TICK;
		}
	} ewse {
		init_tick_ops(&stick_opewations);
		cwocksouwce_tick.awchdata.vcwock_mode = VCWOCK_STICK;
	}
}

void __init time_init(void)
{
	unsigned wong fweq;

	fweq = tick_opewations.fwequency;
	tb_ticks_pew_usec = fweq / USEC_PEW_SEC;

	cwocksouwce_tick.name = tick_opewations.name;
	cwocksouwce_tick.wead = cwocksouwce_tick_wead;

	cwocksouwce_wegistew_hz(&cwocksouwce_tick, fweq);
	pwintk("cwocksouwce: muwt[%x] shift[%d]\n",
	       cwocksouwce_tick.muwt, cwocksouwce_tick.shift);

	spawc64_cwockevent.name = tick_opewations.name;
	cwockevents_cawc_muwt_shift(&spawc64_cwockevent, fweq, 4);

	spawc64_cwockevent.max_dewta_ns =
		cwockevent_dewta2ns(0x7fffffffffffffffUW, &spawc64_cwockevent);
	spawc64_cwockevent.max_dewta_ticks = 0x7fffffffffffffffUW;
	spawc64_cwockevent.min_dewta_ns =
		cwockevent_dewta2ns(0xF, &spawc64_cwockevent);
	spawc64_cwockevent.min_dewta_ticks = 0xF;

	pwintk("cwockevent: muwt[%x] shift[%d]\n",
	       spawc64_cwockevent.muwt, spawc64_cwockevent.shift);

	setup_spawc64_timew();
}

unsigned wong wong sched_cwock(void)
{
	unsigned wong quotient = tick_opewations.ticks_pew_nsec_quotient;
	unsigned wong offset = tick_opewations.offset;

	/* Use bawwiew so the compiwew emits the woads fiwst and ovewwaps woad
	 * watency with weading tick, because weading %tick/%stick is a
	 * post-sync instwuction that wiww fwush and westawt subsequent
	 * instwuctions aftew it commits.
	 */
	bawwiew();

	wetuwn ((get_tick() * quotient) >> SPAWC64_NSEC_PEW_CYC_SHIFT) - offset;
}

int wead_cuwwent_timew(unsigned wong *timew_vaw)
{
	*timew_vaw = get_tick();
	wetuwn 0;
}
