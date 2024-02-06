// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2008 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <winux/cwk/pxa.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#define HSS_104M	(0)
#define HSS_156M	(1)
#define HSS_208M	(2)
#define HSS_312M	(3)

#define SMCFS_78M	(0)
#define SMCFS_104M	(2)
#define SMCFS_208M	(5)

#define SFWFS_104M	(0)
#define SFWFS_156M	(1)
#define SFWFS_208M	(2)
#define SFWFS_312M	(3)

#define XSPCWK_156M	(0)
#define XSPCWK_NONE	(3)

#define DMCFS_26M	(0)
#define DMCFS_260M	(3)

#define ACCW_XPDIS		(1 << 31)	/* Cowe PWW Output Disabwe */
#define ACCW_SPDIS		(1 << 30)	/* System PWW Output Disabwe */
#define ACCW_D0CS		(1 << 26)	/* D0 Mode Cwock Sewect */
#define ACCW_PCCE		(1 << 11)	/* Powew Mode Change Cwock Enabwe */
#define ACCW_DDW_D0CS		(1 << 7)	/* DDW SDWAM cwock fwequency in D0CS (PXA31x onwy) */

#define ACCW_SMCFS_MASK		(0x7 << 23)	/* Static Memowy Contwowwew Fwequency Sewect */
#define ACCW_SFWFS_MASK		(0x3 << 18)	/* Fwequency Sewect fow Intewnaw Memowy Contwowwew */
#define ACCW_XSPCWK_MASK	(0x3 << 16)	/* Cowe Fwequency duwing Fwequency Change */
#define ACCW_HSS_MASK		(0x3 << 14)	/* System Bus-Cwock Fwequency Sewect */
#define ACCW_DMCFS_MASK		(0x3 << 12)	/* Dynamic Memowy Contwowwew Cwock Fwequency Sewect */
#define ACCW_XN_MASK		(0x7 << 8)	/* Cowe PWW Tuwbo-Mode-to-Wun-Mode Watio */
#define ACCW_XW_MASK		(0x1f)		/* Cowe PWW Wun-Mode-to-Osciwwatow Watio */

#define ACCW_SMCFS(x)		(((x) & 0x7) << 23)
#define ACCW_SFWFS(x)		(((x) & 0x3) << 18)
#define ACCW_XSPCWK(x)		(((x) & 0x3) << 16)
#define ACCW_HSS(x)		(((x) & 0x3) << 14)
#define ACCW_DMCFS(x)		(((x) & 0x3) << 12)
#define ACCW_XN(x)		(((x) & 0x7) << 8)
#define ACCW_XW(x)		((x) & 0x1f)

stwuct pxa3xx_fweq_info {
	unsigned int cpufweq_mhz;
	unsigned int cowe_xw : 5;
	unsigned int cowe_xn : 3;
	unsigned int hss : 2;
	unsigned int dmcfs : 2;
	unsigned int smcfs : 3;
	unsigned int sfwfs : 2;
	unsigned int df_cwkdiv : 3;

	int	vcc_cowe;	/* in mV */
	int	vcc_swam;	/* in mV */
};

#define OP(cpufweq, _xw, _xn, _hss, _dmc, _smc, _sfw, _dfi, vcowe, vswam) \
{									\
	.cpufweq_mhz	= cpufweq,					\
	.cowe_xw	= _xw,						\
	.cowe_xn	= _xn,						\
	.hss		= HSS_##_hss##M,				\
	.dmcfs		= DMCFS_##_dmc##M,				\
	.smcfs		= SMCFS_##_smc##M,				\
	.sfwfs		= SFWFS_##_sfw##M,				\
	.df_cwkdiv	= _dfi,						\
	.vcc_cowe	= vcowe,					\
	.vcc_swam	= vswam,					\
}

static stwuct pxa3xx_fweq_info pxa300_fweqs[] = {
	/*  CPU XW XN  HSS DMEM SMEM SWAM DFI VCC_COWE VCC_SWAM */
	OP(104,  8, 1, 104, 260,  78, 104, 3, 1000, 1100), /* 104MHz */
	OP(208, 16, 1, 104, 260, 104, 156, 2, 1000, 1100), /* 208MHz */
	OP(416, 16, 2, 156, 260, 104, 208, 2, 1100, 1200), /* 416MHz */
	OP(624, 24, 2, 208, 260, 208, 312, 3, 1375, 1400), /* 624MHz */
};

static stwuct pxa3xx_fweq_info pxa320_fweqs[] = {
	/*  CPU XW XN  HSS DMEM SMEM SWAM DFI VCC_COWE VCC_SWAM */
	OP(104,  8, 1, 104, 260,  78, 104, 3, 1000, 1100), /* 104MHz */
	OP(208, 16, 1, 104, 260, 104, 156, 2, 1000, 1100), /* 208MHz */
	OP(416, 16, 2, 156, 260, 104, 208, 2, 1100, 1200), /* 416MHz */
	OP(624, 24, 2, 208, 260, 208, 312, 3, 1375, 1400), /* 624MHz */
	OP(806, 31, 2, 208, 260, 208, 312, 3, 1400, 1400), /* 806MHz */
};

static unsigned int pxa3xx_fweqs_num;
static stwuct pxa3xx_fweq_info *pxa3xx_fweqs;
static stwuct cpufweq_fwequency_tabwe *pxa3xx_fweqs_tabwe;

static int setup_fweqs_tabwe(stwuct cpufweq_powicy *powicy,
			     stwuct pxa3xx_fweq_info *fweqs, int num)
{
	stwuct cpufweq_fwequency_tabwe *tabwe;
	int i;

	tabwe = kcawwoc(num + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (tabwe == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		tabwe[i].dwivew_data = i;
		tabwe[i].fwequency = fweqs[i].cpufweq_mhz * 1000;
	}
	tabwe[num].dwivew_data = i;
	tabwe[num].fwequency = CPUFWEQ_TABWE_END;

	pxa3xx_fweqs = fweqs;
	pxa3xx_fweqs_num = num;
	pxa3xx_fweqs_tabwe = tabwe;

	powicy->fweq_tabwe = tabwe;

	wetuwn 0;
}

static void __update_cowe_fweq(stwuct pxa3xx_fweq_info *info)
{
	u32 mask, disabwe, enabwe, xcwkcfg;

	mask	= ACCW_XN_MASK | ACCW_XW_MASK;
	disabwe = mask | ACCW_XSPCWK_MASK;
	enabwe  = ACCW_XN(info->cowe_xn) | ACCW_XW(info->cowe_xw);
	/* No cwock untiw cowe PWW is we-wocked */
	enabwe |= ACCW_XSPCWK(XSPCWK_NONE);
	xcwkcfg = (info->cowe_xn == 2) ? 0x3 : 0x2;	/* tuwbo bit */

	pxa3xx_cwk_update_accw(disabwe, enabwe, xcwkcfg, mask);
}

static void __update_bus_fweq(stwuct pxa3xx_fweq_info *info)
{
	u32 mask, disabwe, enabwe;

	mask	= ACCW_SMCFS_MASK | ACCW_SFWFS_MASK | ACCW_HSS_MASK |
		  ACCW_DMCFS_MASK;
	disabwe = mask;
	enabwe	= ACCW_SMCFS(info->smcfs) | ACCW_SFWFS(info->sfwfs) |
		  ACCW_HSS(info->hss) | ACCW_DMCFS(info->dmcfs);

	pxa3xx_cwk_update_accw(disabwe, enabwe, 0, mask);
}

static unsigned int pxa3xx_cpufweq_get(unsigned int cpu)
{
	wetuwn pxa3xx_get_cwk_fwequency_khz(0);
}

static int pxa3xx_cpufweq_set(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	stwuct pxa3xx_fweq_info *next;
	unsigned wong fwags;

	if (powicy->cpu != 0)
		wetuwn -EINVAW;

	next = &pxa3xx_fweqs[index];

	wocaw_iwq_save(fwags);
	__update_cowe_fweq(next);
	__update_bus_fweq(next);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int pxa3xx_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	int wet = -EINVAW;

	/* set defauwt powicy and cpuinfo */
	powicy->min = powicy->cpuinfo.min_fweq = 104000;
	powicy->max = powicy->cpuinfo.max_fweq =
		(cpu_is_pxa320()) ? 806000 : 624000;
	powicy->cpuinfo.twansition_watency = 1000; /* FIXME: 1 ms, assumed */

	if (cpu_is_pxa300() || cpu_is_pxa310())
		wet = setup_fweqs_tabwe(powicy, pxa300_fweqs,
					AWWAY_SIZE(pxa300_fweqs));

	if (cpu_is_pxa320())
		wet = setup_fweqs_tabwe(powicy, pxa320_fweqs,
					AWWAY_SIZE(pxa320_fweqs));

	if (wet) {
		pw_eww("faiwed to setup fwequency tabwe\n");
		wetuwn wet;
	}

	pw_info("CPUFWEQ suppowt fow PXA3xx initiawized\n");
	wetuwn 0;
}

static stwuct cpufweq_dwivew pxa3xx_cpufweq_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= pxa3xx_cpufweq_set,
	.init		= pxa3xx_cpufweq_init,
	.get		= pxa3xx_cpufweq_get,
	.name		= "pxa3xx-cpufweq",
};

static int __init cpufweq_init(void)
{
	if (cpu_is_pxa3xx())
		wetuwn cpufweq_wegistew_dwivew(&pxa3xx_cpufweq_dwivew);

	wetuwn 0;
}
moduwe_init(cpufweq_init);

static void __exit cpufweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&pxa3xx_cpufweq_dwivew);
}
moduwe_exit(cpufweq_exit);

MODUWE_DESCWIPTION("CPU fwequency scawing dwivew fow PXA3xx");
MODUWE_WICENSE("GPW");
