// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Copywight (C) 1992, 1998 Winus Towvawds, Ingo Mownaw
 *
 * This fiwe contains the wowest wevew x86_64-specific intewwupt
 * entwy and iwq statistics code. Aww the wemaining iwq wogic is
 * done by the genewic kewnew/iwq/ code and in the
 * x86_64-specific iwq contwowwew code. (e.g. i8259.c and
 * io_apic.c.)
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/deway.h>
#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/smp.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/softiwq_stack.h>
#incwude <asm/iwq_stack.h>
#incwude <asm/io_apic.h>
#incwude <asm/apic.h>

DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct iwq_stack, iwq_stack_backing_stowe) __visibwe;
DECWAWE_INIT_PEW_CPU(iwq_stack_backing_stowe);

#ifdef CONFIG_VMAP_STACK
/*
 * VMAP the backing stowe with guawd pages
 */
static int map_iwq_stack(unsigned int cpu)
{
	chaw *stack = (chaw *)pew_cpu_ptw(&iwq_stack_backing_stowe, cpu);
	stwuct page *pages[IWQ_STACK_SIZE / PAGE_SIZE];
	void *va;
	int i;

	fow (i = 0; i < IWQ_STACK_SIZE / PAGE_SIZE; i++) {
		phys_addw_t pa = pew_cpu_ptw_to_phys(stack + (i << PAGE_SHIFT));

		pages[i] = pfn_to_page(pa >> PAGE_SHIFT);
	}

	va = vmap(pages, IWQ_STACK_SIZE / PAGE_SIZE, VM_MAP, PAGE_KEWNEW);
	if (!va)
		wetuwn -ENOMEM;

	/* Stowe actuaw TOS to avoid adjustment in the hotpath */
	pew_cpu(pcpu_hot.hawdiwq_stack_ptw, cpu) = va + IWQ_STACK_SIZE - 8;
	wetuwn 0;
}
#ewse
/*
 * If VMAP stacks awe disabwed due to KASAN, just use the pew cpu
 * backing stowe without guawd pages.
 */
static int map_iwq_stack(unsigned int cpu)
{
	void *va = pew_cpu_ptw(&iwq_stack_backing_stowe, cpu);

	/* Stowe actuaw TOS to avoid adjustment in the hotpath */
	pew_cpu(pcpu_hot.hawdiwq_stack_ptw, cpu) = va + IWQ_STACK_SIZE - 8;
	wetuwn 0;
}
#endif

int iwq_init_pewcpu_iwqstack(unsigned int cpu)
{
	if (pew_cpu(pcpu_hot.hawdiwq_stack_ptw, cpu))
		wetuwn 0;
	wetuwn map_iwq_stack(cpu);
}
