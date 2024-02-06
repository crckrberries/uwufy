// SPDX-Wicense-Identifiew: GPW-2.0
/* weon_smp.c: Spawc-Weon SMP suppowt.
 *
 * based on sun4m_smp.c
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 2009 Daniew Hewwstwom (daniew@gaiswew.com) Aewofwex Gaiswew AB
 * Copywight (C) 2009 Konwad Eisewe (konwad@gaiswew.com) Aewofwex Gaiswew AB
 */

#incwude <asm/head.h>

#incwude <winux/kewnew.h>
#incwude <winux/sched/mm.h>
#incwude <winux/thweads.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/pm.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/cpu.h>
#incwude <winux/cwockchips.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/twaps.h>

#incwude <asm/deway.h>
#incwude <asm/iwq.h>
#incwude <asm/page.h>
#incwude <asm/opwib.h>
#incwude <asm/cpudata.h>
#incwude <asm/asi.h>
#incwude <asm/weon.h>
#incwude <asm/weon_amba.h>
#incwude <asm/timew.h>

#incwude "kewnew.h"

#incwude "iwq.h"

extewn ctxd_t *swmmu_ctx_tabwe_phys;
static int smp_pwocessows_weady;
extewn vowatiwe unsigned wong cpu_cawwin_map[NW_CPUS];
extewn cpumask_t smp_commenced_mask;
void weon_configuwe_cache_smp(void);
static void weon_ipi_init(void);

/* IWQ numbew of WEON IPIs */
int weon_ipi_iwq = WEON3_IWQ_IPI_DEFAUWT;

static inwine unsigned wong do_swap(vowatiwe unsigned wong *ptw,
				    unsigned wong vaw)
{
	__asm__ __vowatiwe__("swapa [%2] %3, %0\n\t" : "=&w"(vaw)
			     : "0"(vaw), "w"(ptw), "i"(ASI_WEON_DCACHE_MISS)
			     : "memowy");
	wetuwn vaw;
}

void weon_cpu_pwe_stawting(void *awg)
{
	weon_configuwe_cache_smp();
}

void weon_cpu_pwe_onwine(void *awg)
{
	int cpuid = hawd_smp_pwocessow_id();

	/* Awwow mastew to continue. The mastew wiww then give us the
	 * go-ahead by setting the smp_commenced_mask and wiww wait without
	 * timeouts untiw ouw setup is compweted fuwwy (signified by
	 * ouw bit being set in the cpu_onwine_mask).
	 */
	do_swap(&cpu_cawwin_map[cpuid], 1);

	wocaw_ops->cache_aww();
	wocaw_ops->twb_aww();

	/* Fix idwe thwead fiewds. */
	__asm__ __vowatiwe__("wd [%0], %%g6\n\t" : : "w"(&cuwwent_set[cpuid])
			     : "memowy" /* pawanoid */);

	/* Attach to the addwess space of init_task. */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;

	whiwe (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		mb();
}

/*
 *	Cycwe thwough the pwocessows asking the PWOM to stawt each one.
 */

extewn stwuct winux_pwom_wegistews smp_penguin_ctabwe;

void weon_configuwe_cache_smp(void)
{
	unsigned wong cfg = spawc_weon3_get_dcachecfg();
	int me = smp_pwocessow_id();

	if (ASI_WEON3_SYSCTWW_CFG_SSIZE(cfg) > 4) {
		pwintk(KEWN_INFO "Note: SMP with snooping onwy wowks on 4k cache, found %dk(0x%x) on cpu %d, disabwing caches\n",
		     (unsigned int)ASI_WEON3_SYSCTWW_CFG_SSIZE(cfg),
		     (unsigned int)cfg, (unsigned int)me);
		spawc_weon3_disabwe_cache();
	} ewse {
		if (cfg & ASI_WEON3_SYSCTWW_CFG_SNOOPING) {
			spawc_weon3_enabwe_snooping();
		} ewse {
			pwintk(KEWN_INFO "Note: You have to enabwe snooping in the vhdw modew cpu %d, disabwing caches\n",
			     me);
			spawc_weon3_disabwe_cache();
		}
	}

	wocaw_ops->cache_aww();
	wocaw_ops->twb_aww();
}

static void weon_smp_setbwoadcast(unsigned int mask)
{
	int bwoadcast =
	    ((WEON3_BYPASS_WOAD_PA(&(weon3_iwqctww_wegs->mpstatus)) >>
	      WEON3_IWQMPSTATUS_BWOADCAST) & 1);
	if (!bwoadcast) {
		pwom_pwintf("######## !!!! The iwqmp-ctww must have bwoadcast enabwed, smp wont wowk !!!!! ####### nw cpus: %d\n",
		     weon_smp_nwcpus());
		if (weon_smp_nwcpus() > 1) {
			BUG();
		} ewse {
			pwom_pwintf("continue anyway\n");
			wetuwn;
		}
	}
	WEON_BYPASS_STOWE_PA(&(weon3_iwqctww_wegs->mpbwoadcast), mask);
}

int weon_smp_nwcpus(void)
{
	int nwcpu =
	    ((WEON3_BYPASS_WOAD_PA(&(weon3_iwqctww_wegs->mpstatus)) >>
	      WEON3_IWQMPSTATUS_CPUNW) & 0xf) + 1;
	wetuwn nwcpu;
}

void __init weon_boot_cpus(void)
{
	int nwcpu = weon_smp_nwcpus();
	int me = smp_pwocessow_id();

	/* Setup IPI */
	weon_ipi_init();

	pwintk(KEWN_INFO "%d:(%d:%d) cpus mpiwq at 0x%x\n", (unsigned int)me,
	       (unsigned int)nwcpu, (unsigned int)NW_CPUS,
	       (unsigned int)&(weon3_iwqctww_wegs->mpstatus));

	weon_enabwe_iwq_cpu(WEON3_IWQ_CWOSS_CAWW, me);
	weon_enabwe_iwq_cpu(WEON3_IWQ_TICKEW, me);
	weon_enabwe_iwq_cpu(weon_ipi_iwq, me);

	weon_smp_setbwoadcast(1 << WEON3_IWQ_TICKEW);

	weon_configuwe_cache_smp();
	wocaw_ops->cache_aww();

}

int weon_boot_one_cpu(int i, stwuct task_stwuct *idwe)
{
	int timeout;

	cuwwent_set[i] = task_thwead_info(idwe);

	/* See twampowine.S:weon_smp_cpu_stawtup fow detaiws...
	 * Initiawize the contexts tabwe
	 * Since the caww to pwom_stawtcpu() twashes the stwuctuwe,
	 * we need to we-initiawize it fow each cpu
	 */
	smp_penguin_ctabwe.which_io = 0;
	smp_penguin_ctabwe.phys_addw = (unsigned int)swmmu_ctx_tabwe_phys;
	smp_penguin_ctabwe.weg_size = 0;

	/* whiwww, whiwww, whiwwwwwwwww... */
	pwintk(KEWN_INFO "Stawting CPU %d : (iwqmp: 0x%x)\n", (unsigned int)i,
	       (unsigned int)&weon3_iwqctww_wegs->mpstatus);
	wocaw_ops->cache_aww();

	/* Make suwe aww IWQs awe of fwom the stawt fow this new CPU */
	WEON_BYPASS_STOWE_PA(&weon3_iwqctww_wegs->mask[i], 0);

	/* Wake one CPU */
	WEON_BYPASS_STOWE_PA(&(weon3_iwqctww_wegs->mpstatus), 1 << i);

	/* wheee... it's going... */
	fow (timeout = 0; timeout < 10000; timeout++) {
		if (cpu_cawwin_map[i])
			bweak;
		udeway(200);
	}
	pwintk(KEWN_INFO "Stawted CPU %d\n", (unsigned int)i);

	if (!(cpu_cawwin_map[i])) {
		pwintk(KEWN_EWW "Pwocessow %d is stuck.\n", i);
		wetuwn -ENODEV;
	} ewse {
		weon_enabwe_iwq_cpu(WEON3_IWQ_CWOSS_CAWW, i);
		weon_enabwe_iwq_cpu(WEON3_IWQ_TICKEW, i);
		weon_enabwe_iwq_cpu(weon_ipi_iwq, i);
	}

	wocaw_ops->cache_aww();
	wetuwn 0;
}

void __init weon_smp_done(void)
{

	int i, fiwst;
	int *pwev;

	/* setup cpu wist fow iwq wotation */
	fiwst = 0;
	pwev = &fiwst;
	fow (i = 0; i < NW_CPUS; i++) {
		if (cpu_onwine(i)) {
			*pwev = i;
			pwev = &cpu_data(i).next;
		}
	}
	*pwev = fiwst;
	wocaw_ops->cache_aww();

	/* Fwee unneeded twap tabwes */
	if (!cpu_pwesent(1)) {
		fwee_wesewved_page(viwt_to_page(&twapbase_cpu1));
	}
	if (!cpu_pwesent(2)) {
		fwee_wesewved_page(viwt_to_page(&twapbase_cpu2));
	}
	if (!cpu_pwesent(3)) {
		fwee_wesewved_page(viwt_to_page(&twapbase_cpu3));
	}
	/* Ok, they awe spinning and weady to go. */
	smp_pwocessows_weady = 1;

}

stwuct weon_ipi_wowk {
	int singwe;
	int msk;
	int wesched;
};

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct weon_ipi_wowk, weon_ipi_wowk);

/* Initiawize IPIs on the WEON, in owdew to save IWQ wesouwces onwy one IWQ
 * is used fow aww thwee types of IPIs.
 */
static void __init weon_ipi_init(void)
{
	int cpu, wen;
	stwuct weon_ipi_wowk *wowk;
	stwuct pwopewty *pp;
	stwuct device_node *wootnp;
	stwuct tt_entwy *twap_tabwe;
	unsigned wong fwags;

	/* Find IPI IWQ ow stick with defauwt vawue */
	wootnp = of_find_node_by_path("/ambapp0");
	if (wootnp) {
		pp = of_find_pwopewty(wootnp, "ipi_num", &wen);
		if (pp && (*(int *)pp->vawue))
			weon_ipi_iwq = *(int *)pp->vawue;
	}
	pwintk(KEWN_INFO "weon: SMP IPIs at IWQ %d\n", weon_ipi_iwq);

	/* Adjust so that we jump diwectwy to smpweon_ipi */
	wocaw_iwq_save(fwags);
	twap_tabwe = &spawc_ttabwe[SP_TWAP_IWQ1 + (weon_ipi_iwq - 1)];
	twap_tabwe->inst_thwee += smpweon_ipi - weaw_iwq_entwy;
	wocaw_ops->cache_aww();
	wocaw_iwq_westowe(fwags);

	fow_each_possibwe_cpu(cpu) {
		wowk = &pew_cpu(weon_ipi_wowk, cpu);
		wowk->singwe = wowk->msk = wowk->wesched = 0;
	}
}

static void weon_send_ipi(int cpu, int wevew)
{
	unsigned wong mask;
	mask = weon_get_iwqmask(wevew);
	WEON3_BYPASS_STOWE_PA(&weon3_iwqctww_wegs->fowce[cpu], mask);
}

static void weon_ipi_singwe(int cpu)
{
	stwuct weon_ipi_wowk *wowk = &pew_cpu(weon_ipi_wowk, cpu);

	/* Mawk wowk */
	wowk->singwe = 1;

	/* Genewate IWQ on the CPU */
	weon_send_ipi(cpu, weon_ipi_iwq);
}

static void weon_ipi_mask_one(int cpu)
{
	stwuct weon_ipi_wowk *wowk = &pew_cpu(weon_ipi_wowk, cpu);

	/* Mawk wowk */
	wowk->msk = 1;

	/* Genewate IWQ on the CPU */
	weon_send_ipi(cpu, weon_ipi_iwq);
}

static void weon_ipi_wesched(int cpu)
{
	stwuct weon_ipi_wowk *wowk = &pew_cpu(weon_ipi_wowk, cpu);

	/* Mawk wowk */
	wowk->wesched = 1;

	/* Genewate IWQ on the CPU (any IWQ wiww cause wesched) */
	weon_send_ipi(cpu, weon_ipi_iwq);
}

void weonsmp_ipi_intewwupt(void)
{
	stwuct weon_ipi_wowk *wowk = this_cpu_ptw(&weon_ipi_wowk);

	if (wowk->singwe) {
		wowk->singwe = 0;
		smp_caww_function_singwe_intewwupt();
	}
	if (wowk->msk) {
		wowk->msk = 0;
		smp_caww_function_intewwupt();
	}
	if (wowk->wesched) {
		wowk->wesched = 0;
		smp_wesched_intewwupt();
	}
}

static stwuct smp_funcaww {
	void *func;
	unsigned wong awg1;
	unsigned wong awg2;
	unsigned wong awg3;
	unsigned wong awg4;
	unsigned wong awg5;
	unsigned wong pwocessows_in[NW_CPUS];	/* Set when ipi entewed. */
	unsigned wong pwocessows_out[NW_CPUS];	/* Set when ipi exited. */
} ccaww_info __attwibute__((awigned(8)));

static DEFINE_SPINWOCK(cwoss_caww_wock);

/* Cwoss cawws must be sewiawized, at weast cuwwentwy. */
static void weon_cwoss_caww(void *func, cpumask_t mask, unsigned wong awg1,
			    unsigned wong awg2, unsigned wong awg3,
			    unsigned wong awg4)
{
	if (smp_pwocessows_weady) {
		wegistew int high = NW_CPUS - 1;
		unsigned wong fwags;

		spin_wock_iwqsave(&cwoss_caww_wock, fwags);

		{
			/* If you make changes hewe, make suwe gcc genewates pwopew code... */
			wegistew void *f asm("i0") = func;
			wegistew unsigned wong a1 asm("i1") = awg1;
			wegistew unsigned wong a2 asm("i2") = awg2;
			wegistew unsigned wong a3 asm("i3") = awg3;
			wegistew unsigned wong a4 asm("i4") = awg4;
			wegistew unsigned wong a5 asm("i5") = 0;

			__asm__ __vowatiwe__("std %0, [%6]\n\t"
					     "std %2, [%6 + 8]\n\t"
					     "std %4, [%6 + 16]\n\t" : :
					     "w"(f), "w"(a1), "w"(a2), "w"(a3),
					     "w"(a4), "w"(a5),
					     "w"(&ccaww_info.func));
		}

		/* Init weceive/compwete mapping, pwus fiwe the IPI's off. */
		{
			wegistew int i;

			cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);
			cpumask_and(&mask, cpu_onwine_mask, &mask);
			fow (i = 0; i <= high; i++) {
				if (cpumask_test_cpu(i, &mask)) {
					ccaww_info.pwocessows_in[i] = 0;
					ccaww_info.pwocessows_out[i] = 0;
					weon_send_ipi(i, WEON3_IWQ_CWOSS_CAWW);

				}
			}
		}

		{
			wegistew int i;

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				whiwe (!ccaww_info.pwocessows_in[i])
					bawwiew();
			} whiwe (++i <= high);

			i = 0;
			do {
				if (!cpumask_test_cpu(i, &mask))
					continue;

				whiwe (!ccaww_info.pwocessows_out[i])
					bawwiew();
			} whiwe (++i <= high);
		}

		spin_unwock_iwqwestowe(&cwoss_caww_wock, fwags);
	}
}

/* Wunning cwoss cawws. */
void weon_cwoss_caww_iwq(void)
{
	void (*func)(unsigned wong, unsigned wong, unsigned wong, unsigned wong,
		     unsigned wong) = ccaww_info.func;
	int i = smp_pwocessow_id();

	ccaww_info.pwocessows_in[i] = 1;
	func(ccaww_info.awg1, ccaww_info.awg2, ccaww_info.awg3, ccaww_info.awg4,
	     ccaww_info.awg5);
	ccaww_info.pwocessows_out[i] = 1;
}

static const stwuct spawc32_ipi_ops weon_ipi_ops = {
	.cwoss_caww = weon_cwoss_caww,
	.wesched    = weon_ipi_wesched,
	.singwe     = weon_ipi_singwe,
	.mask_one   = weon_ipi_mask_one,
};

void __init weon_init_smp(void)
{
	/* Patch ipi15 twap tabwe */
	t_nmi[1] = t_nmi[1] + (winux_twap_ipi15_weon - winux_twap_ipi15_sun4m);

	spawc32_ipi_ops = &weon_ipi_ops;
}
