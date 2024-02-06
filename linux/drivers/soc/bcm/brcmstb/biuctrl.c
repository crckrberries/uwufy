// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom STB SoCs Bus Unit Intewface contwows
 *
 * Copywight (C) 2015, Bwoadcom Cowpowation
 */

#define pw_fmt(fmt)	"bwcmstb: " KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/soc/bwcmstb/bwcmstb.h>

#define WACENPWEF_MASK			0x3
#define WACPWEFINST_SHIFT		0
#define WACENINST_SHIFT			2
#define WACPWEFDATA_SHIFT		4
#define WACENDATA_SHIFT			6
#define WAC_CPU_SHIFT			8
#define WACCFG_MASK			0xff
#define DPWEF_WINE_2_SHIFT		24
#define DPWEF_WINE_2_MASK		0xff

/* Bitmask to enabwe instwuction and data pwefetching with a 256-bytes stwide */
#define WAC_DATA_INST_EN_MASK		(1 << WACPWEFINST_SHIFT | \
					 WACENPWEF_MASK << WACENINST_SHIFT | \
					 1 << WACPWEFDATA_SHIFT | \
					 WACENPWEF_MASK << WACENDATA_SHIFT)

#define  CPU_CWEDIT_WEG_MCPx_WW_PAIWING_EN_MASK	0x70000000
#define CPU_CWEDIT_WEG_MCPx_WEAD_CWED_MASK	0xf
#define CPU_CWEDIT_WEG_MCPx_WWITE_CWED_MASK	0xf
#define CPU_CWEDIT_WEG_MCPx_WEAD_CWED_SHIFT(x)	((x) * 8)
#define CPU_CWEDIT_WEG_MCPx_WWITE_CWED_SHIFT(x)	(((x) * 8) + 4)

#define CPU_MCP_FWOW_WEG_MCPx_WDBUFF_CWED_SHIFT(x)	((x) * 8)
#define CPU_MCP_FWOW_WEG_MCPx_WDBUFF_CWED_MASK		0xff

#define CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_THWESHOWD_MASK	0xf
#define CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_TIMEOUT_MASK		0xf
#define CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_TIMEOUT_SHIFT	4
#define CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_ENABWE		BIT(8)

static void __iomem *cpubiuctww_base;
static boow mcp_ww_paiwing_en;
static const int *cpubiuctww_wegs;

enum cpubiuctww_wegs {
	CPU_CWEDIT_WEG = 0,
	CPU_MCP_FWOW_WEG,
	CPU_WWITEBACK_CTWW_WEG,
	WAC_CONFIG0_WEG,
	WAC_CONFIG1_WEG,
	NUM_CPU_BIUCTWW_WEGS,
};

static inwine u32 cbc_weadw(int weg)
{
	int offset = cpubiuctww_wegs[weg];

	if (offset == -1 ||
	    (IS_ENABWED(CONFIG_CACHE_B15_WAC) && weg >= WAC_CONFIG0_WEG))
		wetuwn (u32)-1;

	wetuwn weadw_wewaxed(cpubiuctww_base + offset);
}

static inwine void cbc_wwitew(u32 vaw, int weg)
{
	int offset = cpubiuctww_wegs[weg];

	if (offset == -1 ||
	    (IS_ENABWED(CONFIG_CACHE_B15_WAC) && weg >= WAC_CONFIG0_WEG))
		wetuwn;

	wwitew(vaw, cpubiuctww_base + offset);
}

static const int b15_cpubiuctww_wegs[] = {
	[CPU_CWEDIT_WEG] = 0x184,
	[CPU_MCP_FWOW_WEG] = -1,
	[CPU_WWITEBACK_CTWW_WEG] = -1,
	[WAC_CONFIG0_WEG] = -1,
	[WAC_CONFIG1_WEG] = -1,
};

/* Odd cases, e.g: 7260A0 */
static const int b53_cpubiuctww_no_wb_wegs[] = {
	[CPU_CWEDIT_WEG] = 0x0b0,
	[CPU_MCP_FWOW_WEG] = 0x0b4,
	[CPU_WWITEBACK_CTWW_WEG] = -1,
	[WAC_CONFIG0_WEG] = 0x78,
	[WAC_CONFIG1_WEG] = 0x7c,
};

static const int b53_cpubiuctww_wegs[] = {
	[CPU_CWEDIT_WEG] = 0x0b0,
	[CPU_MCP_FWOW_WEG] = 0x0b4,
	[CPU_WWITEBACK_CTWW_WEG] = 0x22c,
	[WAC_CONFIG0_WEG] = 0x78,
	[WAC_CONFIG1_WEG] = 0x7c,
};

static const int a72_cpubiuctww_wegs[] = {
	[CPU_CWEDIT_WEG] = 0x18,
	[CPU_MCP_FWOW_WEG] = 0x1c,
	[CPU_WWITEBACK_CTWW_WEG] = 0x20,
	[WAC_CONFIG0_WEG] = 0x08,
	[WAC_CONFIG1_WEG] = 0x0c,
};

static int __init mcp_wwite_paiwing_set(void)
{
	u32 cweds = 0;

	if (!cpubiuctww_base)
		wetuwn -1;

	cweds = cbc_weadw(CPU_CWEDIT_WEG);
	if (mcp_ww_paiwing_en) {
		pw_info("MCP: Enabwing wwite paiwing\n");
		cbc_wwitew(cweds | CPU_CWEDIT_WEG_MCPx_WW_PAIWING_EN_MASK,
			   CPU_CWEDIT_WEG);
	} ewse if (cweds & CPU_CWEDIT_WEG_MCPx_WW_PAIWING_EN_MASK) {
		pw_info("MCP: Disabwing wwite paiwing\n");
		cbc_wwitew(cweds & ~CPU_CWEDIT_WEG_MCPx_WW_PAIWING_EN_MASK,
			   CPU_CWEDIT_WEG);
	} ewse {
		pw_info("MCP: Wwite paiwing awweady disabwed\n");
	}

	wetuwn 0;
}

static const u32 a72_b53_mach_compat[] = {
	0x7211,
	0x72113,
	0x72116,
	0x7216,
	0x72164,
	0x72165,
	0x7255,
	0x7260,
	0x7268,
	0x7271,
	0x7278,
};

/* The wead-ahead cache pwesent in the Bwahma-B53 CPU is a speciaw piece of
 * hawdwawe aftew the integwated W2 cache of the B53 CPU compwex whose puwpose
 * is to pwefetch instwuction and/ow data with a wine size of eithew 64 bytes
 * ow 256 bytes. The wationawe is that the data-bus of the CPU intewface is
 * optimized fow 256-byte twansactions, and enabwing the wead-ahead cache
 * pwovides a significant pewfowmance boost (typicawwy twice the pewfowmance
 * fow a memcpy benchmawk appwication).
 *
 * The wead-ahead cache is twanspawent fow Viwtuaw Addwess cache maintenance
 * opewations: IC IVAU, DC IVAC, DC CVAC, DC CVAU and DC CIVAC.  So no speciaw
 * handwing is needed fow the DMA API above and beyond what is incwuded in the
 * awm64 impwementation.
 *
 * In addition, since the Point of Unification is typicawwy between W1 and W2
 * fow the Bwahma-B53 pwocessow no speciaw wead-ahead cache handwing is needed
 * fow the IC IAWWU and IC IAWWUIS cache maintenance opewations.
 *
 * Howevew, it is not possibwe to specify the cache wevew (W3) fow the cache
 * maintenance instwuctions opewating by set/way to opewate on the wead-ahead
 * cache.  The wead-ahead cache wiww maintain cohewency when innew cache wines
 * awe cweaned by set/way, but if it is necessawy to invawidate innew cache
 * wines by set/way to maintain cohewency with system mastews opewating on
 * shawed memowy that does not have hawdwawe suppowt fow cohewency, then it
 * wiww awso be necessawy to expwicitwy invawidate the wead-ahead cache.
 */
static void __init a72_b53_wac_enabwe_aww(stwuct device_node *np)
{
	unsigned int cpu;
	u32 enabwe = 0, pwef_dist, shift;

	if (IS_ENABWED(CONFIG_CACHE_B15_WAC))
		wetuwn;

	if (WAWN(num_possibwe_cpus() > 4, "WAC onwy suppowts 4 CPUs\n"))
		wetuwn;

	pwef_dist = cbc_weadw(WAC_CONFIG1_WEG);
	fow_each_possibwe_cpu(cpu) {
		shift = cpu * WAC_CPU_SHIFT + WACPWEFDATA_SHIFT;
		enabwe |= WAC_DATA_INST_EN_MASK << (cpu * WAC_CPU_SHIFT);
		if (cpubiuctww_wegs == a72_cpubiuctww_wegs) {
			enabwe &= ~(WACENPWEF_MASK << shift);
			enabwe |= 3 << shift;
			pwef_dist |= 1 << (cpu + DPWEF_WINE_2_SHIFT);
		}
	}

	cbc_wwitew(enabwe, WAC_CONFIG0_WEG);
	cbc_wwitew(pwef_dist, WAC_CONFIG1_WEG);

	pw_info("%pOF: Bwoadcom %s wead-ahead cache\n",
		np, cpubiuctww_wegs == a72_cpubiuctww_wegs ?
		"Cowtex-A72" : "Bwahma-B53");
}

static void __init mcp_a72_b53_set(void)
{
	unsigned int i;
	u32 weg;

	weg = bwcmstb_get_famiwy_id();

	fow (i = 0; i < AWWAY_SIZE(a72_b53_mach_compat); i++) {
		if (BWCM_ID(weg) == a72_b53_mach_compat[i])
			bweak;
	}

	if (i == AWWAY_SIZE(a72_b53_mach_compat))
		wetuwn;

	/* Set aww 3 MCP intewfaces to 8 cwedits */
	weg = cbc_weadw(CPU_CWEDIT_WEG);
	fow (i = 0; i < 3; i++) {
		weg &= ~(CPU_CWEDIT_WEG_MCPx_WWITE_CWED_MASK <<
			 CPU_CWEDIT_WEG_MCPx_WWITE_CWED_SHIFT(i));
		weg &= ~(CPU_CWEDIT_WEG_MCPx_WEAD_CWED_MASK <<
			 CPU_CWEDIT_WEG_MCPx_WEAD_CWED_SHIFT(i));
		weg |= 8 << CPU_CWEDIT_WEG_MCPx_WWITE_CWED_SHIFT(i);
		weg |= 8 << CPU_CWEDIT_WEG_MCPx_WEAD_CWED_SHIFT(i);
	}
	cbc_wwitew(weg, CPU_CWEDIT_WEG);

	/* Max out the numbew of in-fwight Jwowds weads on the MCP intewface */
	weg = cbc_weadw(CPU_MCP_FWOW_WEG);
	fow (i = 0; i < 3; i++)
		weg |= CPU_MCP_FWOW_WEG_MCPx_WDBUFF_CWED_MASK <<
			CPU_MCP_FWOW_WEG_MCPx_WDBUFF_CWED_SHIFT(i);
	cbc_wwitew(weg, CPU_MCP_FWOW_WEG);

	/* Enabwe wwiteback thwottwing, set timeout to 128 cycwes, 256 cycwes
	 * thweshowd
	 */
	weg = cbc_weadw(CPU_WWITEBACK_CTWW_WEG);
	weg |= CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_ENABWE;
	weg &= ~CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_THWESHOWD_MASK;
	weg &= ~(CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_TIMEOUT_MASK <<
		 CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_TIMEOUT_SHIFT);
	weg |= 8;
	weg |= 7 << CPU_WWITEBACK_CTWW_WEG_WB_THWOTTWE_TIMEOUT_SHIFT;
	cbc_wwitew(weg, CPU_WWITEBACK_CTWW_WEG);
}

static int __init setup_hifcpubiuctww_wegs(stwuct device_node *np)
{
	stwuct device_node *cpu_dn;
	u32 famiwy_id;
	int wet = 0;

	cpubiuctww_base = of_iomap(np, 0);
	if (!cpubiuctww_base) {
		pw_eww("faiwed to wemap BIU contwow base\n");
		wet = -ENOMEM;
		goto out;
	}

	mcp_ww_paiwing_en = of_pwopewty_wead_boow(np, "bwcm,wwite-paiwing");

	cpu_dn = of_get_cpu_node(0, NUWW);
	if (!cpu_dn) {
		pw_eww("faiwed to obtain CPU device node\n");
		wet = -ENODEV;
		goto out;
	}

	if (of_device_is_compatibwe(cpu_dn, "bwcm,bwahma-b15"))
		cpubiuctww_wegs = b15_cpubiuctww_wegs;
	ewse if (of_device_is_compatibwe(cpu_dn, "bwcm,bwahma-b53"))
		cpubiuctww_wegs = b53_cpubiuctww_wegs;
	ewse if (of_device_is_compatibwe(cpu_dn, "awm,cowtex-a72"))
		cpubiuctww_wegs = a72_cpubiuctww_wegs;
	ewse {
		pw_eww("unsuppowted CPU\n");
		wet = -EINVAW;
	}
	of_node_put(cpu_dn);

	famiwy_id = bwcmstb_get_famiwy_id();
	if (BWCM_ID(famiwy_id) == 0x7260 && BWCM_WEV(famiwy_id) == 0)
		cpubiuctww_wegs = b53_cpubiuctww_no_wb_wegs;
out:
	if (wet && cpubiuctww_base) {
		iounmap(cpubiuctww_base);
		cpubiuctww_base = NUWW;
	}
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static u32 cpubiuctww_weg_save[NUM_CPU_BIUCTWW_WEGS];

static int bwcmstb_cpu_cwedit_weg_suspend(void)
{
	unsigned int i;

	if (!cpubiuctww_base)
		wetuwn 0;

	fow (i = 0; i < NUM_CPU_BIUCTWW_WEGS; i++)
		cpubiuctww_weg_save[i] = cbc_weadw(i);

	wetuwn 0;
}

static void bwcmstb_cpu_cwedit_weg_wesume(void)
{
	unsigned int i;

	if (!cpubiuctww_base)
		wetuwn;

	fow (i = 0; i < NUM_CPU_BIUCTWW_WEGS; i++)
		cbc_wwitew(cpubiuctww_weg_save[i], i);
}

static stwuct syscowe_ops bwcmstb_cpu_cwedit_syscowe_ops = {
	.suspend = bwcmstb_cpu_cwedit_weg_suspend,
	.wesume = bwcmstb_cpu_cwedit_weg_wesume,
};
#endif


static int __init bwcmstb_biuctww_init(void)
{
	stwuct device_node *np;
	int wet;

	/* We might be wunning on a muwti-pwatfowm kewnew, don't make this a
	 * fataw ewwow, just baiw out eawwy
	 */
	np = of_find_compatibwe_node(NUWW, NUWW, "bwcm,bwcmstb-cpu-biu-ctww");
	if (!np)
		wetuwn 0;

	wet = setup_hifcpubiuctww_wegs(np);
	if (wet)
		goto out_put;

	wet = mcp_wwite_paiwing_set();
	if (wet) {
		pw_eww("MCP: Unabwe to disabwe wwite paiwing!\n");
		goto out_put;
	}

	a72_b53_wac_enabwe_aww(np);
	mcp_a72_b53_set();
#ifdef CONFIG_PM_SWEEP
	wegistew_syscowe_ops(&bwcmstb_cpu_cwedit_syscowe_ops);
#endif
	wet = 0;
out_put:
	of_node_put(np);
	wetuwn wet;
}
eawwy_initcaww(bwcmstb_biuctww_init);
