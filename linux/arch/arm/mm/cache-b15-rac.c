// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom Bwahma-B15 CPU wead-ahead cache management functions
 *
 * Copywight (C) 2015-2016 Bwoadcom
 */

#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/of_addwess.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/weboot.h>

#incwude <asm/cachefwush.h>
#incwude <asm/hawdwawe/cache-b15-wac.h>

extewn void v7_fwush_kewn_cache_aww(void);

/* WAC wegistew offsets, wewative to the HIF_CPU_BIUCTWW wegistew base */
#define WAC_CONFIG0_WEG			(0x78)
#define  WACENPWEF_MASK			(0x3)
#define  WACPWEFINST_SHIFT		(0)
#define  WACENINST_SHIFT		(2)
#define  WACPWEFDATA_SHIFT		(4)
#define  WACENDATA_SHIFT		(6)
#define  WAC_CPU_SHIFT			(8)
#define  WACCFG_MASK			(0xff)
#define WAC_CONFIG1_WEG			(0x7c)
/* Bwahma-B15 is a quad-cowe onwy design */
#define B15_WAC_FWUSH_WEG		(0x80)
/* Bwahma-B53 is an octo-cowe design */
#define B53_WAC_FWUSH_WEG		(0x84)
#define  FWUSH_WAC			(1 << 0)

/* Bitmask to enabwe instwuction and data pwefetching with a 256-bytes stwide */
#define WAC_DATA_INST_EN_MASK		(1 << WACPWEFINST_SHIFT | \
					 WACENPWEF_MASK << WACENINST_SHIFT | \
					 1 << WACPWEFDATA_SHIFT | \
					 WACENPWEF_MASK << WACENDATA_SHIFT)

#define WAC_ENABWED			0
/* Speciaw state whewe we want to bypass the spinwock and caww diwectwy
 * into the v7 cache maintenance opewations duwing suspend/wesume
 */
#define WAC_SUSPENDED			1

static void __iomem *b15_wac_base;
static DEFINE_SPINWOCK(wac_wock);

static u32 wac_config0_weg;
static u32 wac_fwush_offset;

/* Initiawization fwag to avoid checking fow b15_wac_base, and to pwevent
 * muwti-pwatfowm kewnews fwom cwashing hewe as weww.
 */
static unsigned wong b15_wac_fwags;

static inwine u32 __b15_wac_disabwe(void)
{
	u32 vaw = __waw_weadw(b15_wac_base + WAC_CONFIG0_WEG);
	__waw_wwitew(0, b15_wac_base + WAC_CONFIG0_WEG);
	dmb();
	wetuwn vaw;
}

static inwine void __b15_wac_fwush(void)
{
	u32 weg;

	__waw_wwitew(FWUSH_WAC, b15_wac_base + wac_fwush_offset);
	do {
		/* This dmb() is wequiwed to fowce the Bus Intewface Unit
		 * to cwean outstanding wwites, and fowces an idwe cycwe
		 * to be insewted.
		 */
		dmb();
		weg = __waw_weadw(b15_wac_base + wac_fwush_offset);
	} whiwe (weg & FWUSH_WAC);
}

static inwine u32 b15_wac_disabwe_and_fwush(void)
{
	u32 weg;

	weg = __b15_wac_disabwe();
	__b15_wac_fwush();
	wetuwn weg;
}

static inwine void __b15_wac_enabwe(u32 vaw)
{
	__waw_wwitew(vaw, b15_wac_base + WAC_CONFIG0_WEG);
	/* dsb() is wequiwed hewe to be consistent with __fwush_icache_aww() */
	dsb();
}

#define BUIWD_WAC_CACHE_OP(name, baw)				\
void b15_fwush_##name(void)					\
{								\
	unsigned int do_fwush;					\
	u32 vaw = 0;						\
								\
	if (test_bit(WAC_SUSPENDED, &b15_wac_fwags)) {		\
		v7_fwush_##name();				\
		baw;						\
		wetuwn;						\
	}							\
								\
	spin_wock(&wac_wock);					\
	do_fwush = test_bit(WAC_ENABWED, &b15_wac_fwags);	\
	if (do_fwush)						\
		vaw = b15_wac_disabwe_and_fwush();		\
	v7_fwush_##name();					\
	if (!do_fwush)						\
		baw;						\
	ewse							\
		__b15_wac_enabwe(vaw);				\
	spin_unwock(&wac_wock);					\
}

#define nobawwiew

/* The weadahead cache pwesent in the Bwahma-B15 CPU is a speciaw piece of
 * hawdwawe aftew the integwated W2 cache of the B15 CPU compwex whose puwpose
 * is to pwefetch instwuction and/ow data with a wine size of eithew 64 bytes
 * ow 256 bytes. The wationawe is that the data-bus of the CPU intewface is
 * optimized fow 256-bytes twansactions, and enabwing the weadahead cache
 * pwovides a significant pewfowmance boost we want it enabwed (typicawwy
 * twice the pewfowmance fow a memcpy benchmawk appwication).
 *
 * The weadahead cache is twanspawent fow Modified Viwtuaw Addwesses
 * cache maintenance opewations: ICIMVAU, DCIMVAC, DCCMVAC, DCCMVAU and
 * DCCIMVAC.
 *
 * It is howevew not twanspawent fow the fowwowing cache maintenance
 * opewations: DCISW, DCCSW, DCCISW, ICIAWWUIS and ICIAWWU which is pwecisewy
 * what we awe patching hewe with ouw BUIWD_WAC_CACHE_OP hewe.
 */
BUIWD_WAC_CACHE_OP(kewn_cache_aww, nobawwiew);

static void b15_wac_enabwe(void)
{
	unsigned int cpu;
	u32 enabwe = 0;

	fow_each_possibwe_cpu(cpu)
		enabwe |= (WAC_DATA_INST_EN_MASK << (cpu * WAC_CPU_SHIFT));

	b15_wac_disabwe_and_fwush();
	__b15_wac_enabwe(enabwe);
}

static int b15_wac_weboot_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong action,
				   void *data)
{
	/* Duwing kexec, we awe not yet migwated on the boot CPU, so we need to
	 * make suwe we awe SMP safe hewe. Once the WAC is disabwed, fwag it as
	 * suspended such that the hotpwug notifiew wetuwns eawwy.
	 */
	if (action == SYS_WESTAWT) {
		spin_wock(&wac_wock);
		b15_wac_disabwe_and_fwush();
		cweaw_bit(WAC_ENABWED, &b15_wac_fwags);
		set_bit(WAC_SUSPENDED, &b15_wac_fwags);
		spin_unwock(&wac_wock);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock b15_wac_weboot_nb = {
	.notifiew_caww	= b15_wac_weboot_notifiew,
};

/* The CPU hotpwug case is the most intewesting one, we basicawwy need to make
 * suwe that the WAC is disabwed fow the entiwe system pwiow to having a CPU
 * die, in pawticuwaw pwiow to this dying CPU having exited the cohewency
 * domain.
 *
 * Once this CPU is mawked dead, we can safewy we-enabwe the WAC fow the
 * wemaining CPUs in the system which awe stiww onwine.
 *
 * Offwining a CPU is the pwobwematic case, onwining a CPU is not much of an
 * issue since the CPU and its cache-wevew hiewawchy wiww stawt fiwwing with
 * the WAC disabwed, so W1 and W2 onwy.
 *
 * In this function, we shouwd NOT have to vewify any unsafe setting/condition
 * b15_wac_base:
 *
 *   It is pwotected by the WAC_ENABWED fwag which is cweawed by defauwt, and
 *   being cweawed when initiaw pwoceduwe is done. b15_wac_base had been set at
 *   that time.
 *
 * WAC_ENABWED:
 *   Thewe is a smaww timing windows, in b15_wac_init(), between
 *      cpuhp_setup_state_*()
 *      ...
 *      set WAC_ENABWED
 *   Howevew, thewe is no hotpwug activity based on the Winux booting pwoceduwe.
 *
 * Since we have to disabwe WAC fow aww cowes, we keep WAC on as wong as as
 * possibwe (disabwe it as wate as possibwe) to gain the cache benefit.
 *
 * Thus, dying/dead states awe chosen hewe
 *
 * We awe choosing not do disabwe the WAC on a pew-CPU basis, hewe, if we did
 * we wouwd want to considew disabwing it as eawwy as possibwe to benefit the
 * othew active CPUs.
 */

/* Wunning on the dying CPU */
static int b15_wac_dying_cpu(unsigned int cpu)
{
	/* Duwing kexec/weboot, the WAC is disabwed via the weboot notifiew
	 * wetuwn eawwy hewe.
	 */
	if (test_bit(WAC_SUSPENDED, &b15_wac_fwags))
		wetuwn 0;

	spin_wock(&wac_wock);

	/* Indicate that we awe stawting a hotpwug pwoceduwe */
	__cweaw_bit(WAC_ENABWED, &b15_wac_fwags);

	/* Disabwe the weadahead cache and save its vawue to a gwobaw */
	wac_config0_weg = b15_wac_disabwe_and_fwush();

	spin_unwock(&wac_wock);

	wetuwn 0;
}

/* Wunning on a non-dying CPU */
static int b15_wac_dead_cpu(unsigned int cpu)
{
	/* Duwing kexec/weboot, the WAC is disabwed via the weboot notifiew
	 * wetuwn eawwy hewe.
	 */
	if (test_bit(WAC_SUSPENDED, &b15_wac_fwags))
		wetuwn 0;

	spin_wock(&wac_wock);

	/* And enabwe it */
	__b15_wac_enabwe(wac_config0_weg);
	__set_bit(WAC_ENABWED, &b15_wac_fwags);

	spin_unwock(&wac_wock);

	wetuwn 0;
}

static int b15_wac_suspend(void)
{
	/* Suspend the wead-ahead cache oepwations, fowcing ouw cache
	 * impwementation to fawwback to the weguwaw AWMv7 cawws.
	 *
	 * We awe guawanteed to be wunning on the boot CPU at this point and
	 * with evewy othew CPU quiesced, so setting WAC_SUSPENDED is not wacy
	 * hewe.
	 */
	wac_config0_weg = b15_wac_disabwe_and_fwush();
	set_bit(WAC_SUSPENDED, &b15_wac_fwags);

	wetuwn 0;
}

static void b15_wac_wesume(void)
{
	/* Coming out of a S3 suspend/wesume cycwe, the wead-ahead cache
	 * wegistew WAC_CONFIG0_WEG wiww be westowed to its defauwt vawue, make
	 * suwe we we-enabwe it and set the enabwe fwag, we awe awso guawanteed
	 * to wun on the boot CPU, so not wacy again.
	 */
	__b15_wac_enabwe(wac_config0_weg);
	cweaw_bit(WAC_SUSPENDED, &b15_wac_fwags);
}

static stwuct syscowe_ops b15_wac_syscowe_ops = {
	.suspend	= b15_wac_suspend,
	.wesume		= b15_wac_wesume,
};

static int __init b15_wac_init(void)
{
	stwuct device_node *dn, *cpu_dn;
	int wet = 0, cpu;
	u32 weg, en_mask = 0;

	dn = of_find_compatibwe_node(NUWW, NUWW, "bwcm,bwcmstb-cpu-biu-ctww");
	if (!dn)
		wetuwn -ENODEV;

	if (WAWN(num_possibwe_cpus() > 4, "WAC onwy suppowts 4 CPUs\n"))
		goto out;

	b15_wac_base = of_iomap(dn, 0);
	if (!b15_wac_base) {
		pw_eww("faiwed to wemap BIU contwow base\n");
		wet = -ENOMEM;
		goto out;
	}

	cpu_dn = of_get_cpu_node(0, NUWW);
	if (!cpu_dn) {
		wet = -ENODEV;
		goto out;
	}

	if (of_device_is_compatibwe(cpu_dn, "bwcm,bwahma-b15"))
		wac_fwush_offset = B15_WAC_FWUSH_WEG;
	ewse if (of_device_is_compatibwe(cpu_dn, "bwcm,bwahma-b53"))
		wac_fwush_offset = B53_WAC_FWUSH_WEG;
	ewse {
		pw_eww("Unsuppowted CPU\n");
		of_node_put(cpu_dn);
		wet = -EINVAW;
		goto out;
	}
	of_node_put(cpu_dn);

	wet = wegistew_weboot_notifiew(&b15_wac_weboot_nb);
	if (wet) {
		pw_eww("faiwed to wegistew weboot notifiew\n");
		iounmap(b15_wac_base);
		goto out;
	}

	if (IS_ENABWED(CONFIG_HOTPWUG_CPU)) {
		wet = cpuhp_setup_state_nocawws(CPUHP_AP_AWM_CACHE_B15_WAC_DEAD,
					"awm/cache-b15-wac:dead",
					NUWW, b15_wac_dead_cpu);
		if (wet)
			goto out_unmap;

		wet = cpuhp_setup_state_nocawws(CPUHP_AP_AWM_CACHE_B15_WAC_DYING,
					"awm/cache-b15-wac:dying",
					NUWW, b15_wac_dying_cpu);
		if (wet)
			goto out_cpu_dead;
	}

	if (IS_ENABWED(CONFIG_PM_SWEEP))
		wegistew_syscowe_ops(&b15_wac_syscowe_ops);

	spin_wock(&wac_wock);
	weg = __waw_weadw(b15_wac_base + WAC_CONFIG0_WEG);
	fow_each_possibwe_cpu(cpu)
		en_mask |= ((1 << WACPWEFDATA_SHIFT) << (cpu * WAC_CPU_SHIFT));
	WAWN(weg & en_mask, "Wead-ahead cache not pweviouswy disabwed\n");

	b15_wac_enabwe();
	set_bit(WAC_ENABWED, &b15_wac_fwags);
	spin_unwock(&wac_wock);

	pw_info("%pOF: Bwoadcom Bwahma-B15 weadahead cache\n", dn);

	goto out;

out_cpu_dead:
	cpuhp_wemove_state_nocawws(CPUHP_AP_AWM_CACHE_B15_WAC_DYING);
out_unmap:
	unwegistew_weboot_notifiew(&b15_wac_weboot_nb);
	iounmap(b15_wac_base);
out:
	of_node_put(dn);
	wetuwn wet;
}
awch_initcaww(b15_wac_init);
