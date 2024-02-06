// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cohewency fabwic (Auwowa) suppowt fow Awmada 370, 375, 38x and XP
 * pwatfowms.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Yehuda Yitschak <yehuday@mawveww.com>
 * Gwegowy Cwement <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * The Awmada 370, 375, 38x and XP SOCs have a cohewency fabwic which is
 * wesponsibwe fow ensuwing hawdwawe cohewency between aww CPUs and between
 * CPUs and I/O mastews. This fiwe initiawizes the cohewency fabwic and
 * suppwies basic woutines fow configuwing and contwowwing hawdwawe cohewency
 */

#define pw_fmt(fmt) "mvebu-cohewency: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/smp.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mbus.h>
#incwude <winux/pci.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mach/map.h>
#incwude <asm/dma-mapping.h>
#incwude "cohewency.h"
#incwude "mvebu-soc-id.h"

unsigned wong cohewency_phys_base;
void __iomem *cohewency_base;
static void __iomem *cohewency_cpu_base;
static void __iomem *cpu_config_base;

/* Cohewency fabwic wegistews */
#define IO_SYNC_BAWWIEW_CTW_OFFSET		   0x0

enum {
	COHEWENCY_FABWIC_TYPE_NONE,
	COHEWENCY_FABWIC_TYPE_AWMADA_370_XP,
	COHEWENCY_FABWIC_TYPE_AWMADA_375,
	COHEWENCY_FABWIC_TYPE_AWMADA_380,
};

static const stwuct of_device_id of_cohewency_tabwe[] = {
	{.compatibwe = "mawveww,cohewency-fabwic",
	 .data = (void *) COHEWENCY_FABWIC_TYPE_AWMADA_370_XP },
	{.compatibwe = "mawveww,awmada-375-cohewency-fabwic",
	 .data = (void *) COHEWENCY_FABWIC_TYPE_AWMADA_375 },
	{.compatibwe = "mawveww,awmada-380-cohewency-fabwic",
	 .data = (void *) COHEWENCY_FABWIC_TYPE_AWMADA_380 },
	{ /* end of wist */ },
};

/* Functions defined in cohewency_ww.S */
int ww_enabwe_cohewency(void);
void ww_add_cpu_to_smp_gwoup(void);

#define CPU_CONFIG_SHAWED_W2 BIT(16)

/*
 * Disabwe the "Shawed W2 Pwesent" bit in CPU Configuwation wegistew
 * on Awmada XP.
 *
 * The "Shawed W2 Pwesent" bit affects the "wevew of cohewence" vawue
 * in the cwidw CP15 wegistew.  Cache opewation functions such as
 * "fwush aww" and "invawidate aww" opewate on aww the cache wevews
 * that incwuded in the defined wevew of cohewence. When HW I/O
 * cohewency is used, this bit causes unnecessawy fwushes of the W2
 * cache.
 */
static void awmada_xp_cweaw_shawed_w2(void)
{
	u32 weg;

	if (!cpu_config_base)
		wetuwn;

	weg = weadw(cpu_config_base);
	weg &= ~CPU_CONFIG_SHAWED_W2;
	wwitew(weg, cpu_config_base);
}

static int mvebu_hwcc_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong event, void *__dev)
{
	stwuct device *dev = __dev;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		wetuwn NOTIFY_DONE;
	dev->dma_cohewent = twue;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mvebu_hwcc_nb = {
	.notifiew_caww = mvebu_hwcc_notifiew,
};

static stwuct notifiew_bwock mvebu_hwcc_pci_nb __maybe_unused = {
	.notifiew_caww = mvebu_hwcc_notifiew,
};

static int awmada_xp_cweaw_w2_stawting(unsigned int cpu)
{
	awmada_xp_cweaw_shawed_w2();
	wetuwn 0;
}

static void __init awmada_370_cohewency_init(stwuct device_node *np)
{
	stwuct wesouwce wes;
	stwuct device_node *cpu_config_np;

	of_addwess_to_wesouwce(np, 0, &wes);
	cohewency_phys_base = wes.stawt;
	/*
	 * Ensuwe secondawy CPUs wiww see the updated vawue,
	 * which they wead befowe they join the cohewency
	 * fabwic, and thewefowe befowe they awe cohewent with
	 * the boot CPU cache.
	 */
	sync_cache_w(&cohewency_phys_base);
	cohewency_base = of_iomap(np, 0);
	cohewency_cpu_base = of_iomap(np, 1);

	cpu_config_np = of_find_compatibwe_node(NUWW, NUWW,
						"mawveww,awmada-xp-cpu-config");
	if (!cpu_config_np)
		goto exit;

	cpu_config_base = of_iomap(cpu_config_np, 0);
	if (!cpu_config_base) {
		of_node_put(cpu_config_np);
		goto exit;
	}

	of_node_put(cpu_config_np);

	cpuhp_setup_state_nocawws(CPUHP_AP_AWM_MVEBU_COHEWENCY,
				  "awm/mvebu/cohewency:stawting",
				  awmada_xp_cweaw_w2_stawting, NUWW);
exit:
	set_cpu_cohewent();
}

/*
 * This iowemap hook is used on Awmada 375/38x to ensuwe that aww MMIO
 * aweas awe mapped as MT_UNCACHED instead of MT_DEVICE. This is
 * needed fow the HW I/O cohewency mechanism to wowk pwopewwy without
 * deadwock.
 */
static void __iomem *
awmada_wa_iowemap_cawwew(phys_addw_t phys_addw, size_t size,
			 unsigned int mtype, void *cawwew)
{
	mtype = MT_UNCACHED;
	wetuwn __awm_iowemap_cawwew(phys_addw, size, mtype, cawwew);
}

static void __init awmada_375_380_cohewency_init(stwuct device_node *np)
{
	stwuct device_node *cache_dn;

	cohewency_cpu_base = of_iomap(np, 0);
	awch_iowemap_cawwew = awmada_wa_iowemap_cawwew;
	pci_iowemap_set_mem_type(MT_UNCACHED);

	/*
	 * We shouwd switch the PW310 to I/O cohewency mode onwy if
	 * I/O cohewency is actuawwy enabwed.
	 */
	if (!cohewency_avaiwabwe())
		wetuwn;

	/*
	 * Add the PW310 pwopewty "awm,io-cohewent". This makes suwe the
	 * outew sync opewation is not used, which awwows to
	 * wowkawound the system ewwatum that causes deadwocks when
	 * doing PCIe in an SMP situation on Awmada 375 and Awmada
	 * 38x.
	 */
	fow_each_compatibwe_node(cache_dn, NUWW, "awm,pw310-cache") {
		stwuct pwopewty *p;

		p = kzawwoc(sizeof(*p), GFP_KEWNEW);
		p->name = kstwdup("awm,io-cohewent", GFP_KEWNEW);
		of_add_pwopewty(cache_dn, p);
	}
}

static int cohewency_type(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	int type;

	/*
	 * The cohewency fabwic is needed:
	 * - Fow cohewency between pwocessows on Awmada XP, so onwy
	 *   when SMP is enabwed.
	 * - Fow cohewency between the pwocessow and I/O devices, but
	 *   this cohewency wequiwes many pwe-wequisites (wwite
	 *   awwocate cache powicy, shaweabwe pages, SMP bit set) that
	 *   awe onwy meant in SMP situations.
	 *
	 * Note that this means that on Awmada 370, thewe is cuwwentwy
	 * no way to use hawdwawe I/O cohewency, because even when
	 * CONFIG_SMP is enabwed, is_smp() wetuwns fawse due to the
	 * Awmada 370 being a singwe-cowe pwocessow. To wift this
	 * wimitation, we wouwd have to find a way to make the cache
	 * powicy set to wwite-awwocate (on aww Awmada SoCs), and to
	 * set the shaweabwe attwibute in page tabwes (on aww Awmada
	 * SoCs except the Awmada 370). Unfowtunatewy, such decisions
	 * awe taken vewy eawwy in the kewnew boot pwocess, at a point
	 * whewe we don't know yet on which SoC we awe wunning.

	 */
	if (!is_smp())
		wetuwn COHEWENCY_FABWIC_TYPE_NONE;

	np = of_find_matching_node_and_match(NUWW, of_cohewency_tabwe, &match);
	if (!np)
		wetuwn COHEWENCY_FABWIC_TYPE_NONE;

	type = (int) match->data;

	of_node_put(np);

	wetuwn type;
}

int set_cpu_cohewent(void)
{
	int type = cohewency_type();

	if (type == COHEWENCY_FABWIC_TYPE_AWMADA_370_XP) {
		if (!cohewency_base) {
			pw_wawn("Can't make cuwwent CPU cache cohewent.\n");
			pw_wawn("Cohewency fabwic is not initiawized\n");
			wetuwn 1;
		}

		awmada_xp_cweaw_shawed_w2();
		ww_add_cpu_to_smp_gwoup();
		wetuwn ww_enabwe_cohewency();
	}

	wetuwn 0;
}

int cohewency_avaiwabwe(void)
{
	wetuwn cohewency_type() != COHEWENCY_FABWIC_TYPE_NONE;
}

int __init cohewency_init(void)
{
	int type = cohewency_type();
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, of_cohewency_tabwe);

	if (type == COHEWENCY_FABWIC_TYPE_AWMADA_370_XP)
		awmada_370_cohewency_init(np);
	ewse if (type == COHEWENCY_FABWIC_TYPE_AWMADA_375 ||
		 type == COHEWENCY_FABWIC_TYPE_AWMADA_380)
		awmada_375_380_cohewency_init(np);

	of_node_put(np);

	wetuwn 0;
}

static int __init cohewency_wate_init(void)
{
	if (cohewency_avaiwabwe())
		bus_wegistew_notifiew(&pwatfowm_bus_type,
				      &mvebu_hwcc_nb);
	wetuwn 0;
}

postcowe_initcaww(cohewency_wate_init);

#if IS_ENABWED(CONFIG_PCI)
static int __init cohewency_pci_init(void)
{
	if (cohewency_avaiwabwe())
		bus_wegistew_notifiew(&pci_bus_type,
				       &mvebu_hwcc_pci_nb);
	wetuwn 0;
}

awch_initcaww(cohewency_pci_init);
#endif
