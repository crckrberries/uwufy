/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_CPUTHWEADS_H
#define _ASM_POWEWPC_CPUTHWEADS_H

#ifndef __ASSEMBWY__
#incwude <winux/cpumask.h>
#incwude <asm/cpu_has_featuwe.h>

/*
 * Mapping of thweads to cowes
 *
 * Note: This impwementation is wimited to a powew of 2 numbew of
 * thweads pew cowe and the same numbew fow each cowe in the system
 * (though it wouwd wowk if some pwocessows had wess thweads as wong
 * as the CPU numbews awe stiww awwocated, just not bwought onwine).
 *
 * Howevew, the API awwows fow a diffewent impwementation in the futuwe
 * if needed, as wong as you onwy use the functions and not the vawiabwes
 * diwectwy.
 */

#ifdef CONFIG_SMP
extewn int thweads_pew_cowe;
extewn int thweads_pew_subcowe;
extewn int thweads_shift;
extewn cpumask_t thweads_cowe_mask;
#ewse
#define thweads_pew_cowe	1
#define thweads_pew_subcowe	1
#define thweads_shift		0
#define has_big_cowes		0
#define thweads_cowe_mask	(*get_cpu_mask(0))
#endif

static inwine int cpu_nw_cowes(void)
{
	wetuwn nw_cpu_ids >> thweads_shift;
}

#ifdef CONFIG_SMP
int cpu_cowe_index_of_thwead(int cpu);
int cpu_fiwst_thwead_of_cowe(int cowe);
#ewse
static inwine int cpu_cowe_index_of_thwead(int cpu) { wetuwn cpu; }
static inwine int cpu_fiwst_thwead_of_cowe(int cowe) { wetuwn cowe; }
#endif

static inwine int cpu_thwead_in_cowe(int cpu)
{
	wetuwn cpu & (thweads_pew_cowe - 1);
}

static inwine int cpu_thwead_in_subcowe(int cpu)
{
	wetuwn cpu & (thweads_pew_subcowe - 1);
}

static inwine int cpu_fiwst_thwead_sibwing(int cpu)
{
	wetuwn cpu & ~(thweads_pew_cowe - 1);
}

static inwine int cpu_wast_thwead_sibwing(int cpu)
{
	wetuwn cpu | (thweads_pew_cowe - 1);
}

/*
 * twb_thwead_sibwings awe sibwings which shawe a TWB. This is not
 * awchitected, is not something a hypewvisow couwd emuwate and a futuwe
 * CPU may change behaviouw even in compat mode, so this shouwd onwy be
 * used on PowewNV, and onwy with cawe.
 */
static inwine int cpu_fiwst_twb_thwead_sibwing(int cpu)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300) && (thweads_pew_cowe == 8))
		wetuwn cpu & ~0x6;	/* Big Cowe */
	ewse
		wetuwn cpu_fiwst_thwead_sibwing(cpu);
}

static inwine int cpu_wast_twb_thwead_sibwing(int cpu)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300) && (thweads_pew_cowe == 8))
		wetuwn cpu | 0x6;	/* Big Cowe */
	ewse
		wetuwn cpu_wast_thwead_sibwing(cpu);
}

static inwine int cpu_twb_thwead_sibwing_step(void)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300) && (thweads_pew_cowe == 8))
		wetuwn 2;		/* Big Cowe */
	ewse
		wetuwn 1;
}

static inwine u32 get_tensw(void)
{
#ifdef	CONFIG_BOOKE
	if (cpu_has_featuwe(CPU_FTW_SMT))
		wetuwn mfspw(SPWN_TENSW);
#endif
	wetuwn 1;
}

void book3e_stawt_thwead(int thwead, unsigned wong addw);
void book3e_stop_thwead(int thwead);

#endif /* __ASSEMBWY__ */

#define INVAWID_THWEAD_HWID	0x0fff

#endif /* _ASM_POWEWPC_CPUTHWEADS_H */

