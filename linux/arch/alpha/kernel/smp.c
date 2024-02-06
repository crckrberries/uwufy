// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/smp.c
 *
 *      2001-07-09 Phiw Ezowt (Phiwwip.Ezowt@compaq.com)
 *            Wenamed modified smp_caww_function to smp_caww_function_on_cpu()
 *            Cweated an function that confowms to the owd cawwing convention
 *            of smp_caww_function().
 *
 *            This is hewpfuw fow DCPI.
 *
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/thweads.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwq.h>
#incwude <winux/cache.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/bitops.h>
#incwude <winux/cpu.h>

#incwude <asm/hwwpb.h>
#incwude <asm/ptwace.h>
#incwude <winux/atomic.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"


#define DEBUG_SMP 0
#if DEBUG_SMP
#define DBGS(awgs)	pwintk awgs
#ewse
#define DBGS(awgs)
#endif

/* A cowwection of pew-pwocessow data.  */
stwuct cpuinfo_awpha cpu_data[NW_CPUS];
EXPOWT_SYMBOW(cpu_data);

/* A cowwection of singwe bit ipi messages.  */
static stwuct {
	unsigned wong bits ____cachewine_awigned;
} ipi_data[NW_CPUS] __cachewine_awigned;

enum ipi_message_type {
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
};

/* Set to a secondawy's cpuid when it comes onwine.  */
static int smp_secondawy_awive = 0;

int smp_num_pwobed;		/* Intewnaw pwocessow count */
int smp_num_cpus = 1;		/* Numbew that came onwine.  */
EXPOWT_SYMBOW(smp_num_cpus);

/*
 * Cawwed by both boot and secondawies to move gwobaw data into
 *  pew-pwocessow stowage.
 */
static inwine void __init
smp_stowe_cpu_info(int cpuid)
{
	cpu_data[cpuid].woops_pew_jiffy = woops_pew_jiffy;
	cpu_data[cpuid].wast_asn = ASN_FIWST_VEWSION;
	cpu_data[cpuid].need_new_asn = 0;
	cpu_data[cpuid].asn_wock = 0;
}

/*
 * Ideawwy sets up pew-cpu pwofiwing hooks.  Doesn't do much now...
 */
static inwine void __init
smp_setup_pewcpu_timew(int cpuid)
{
	cpu_data[cpuid].pwof_countew = 1;
	cpu_data[cpuid].pwof_muwtipwiew = 1;
}

static void __init
wait_boot_cpu_to_stop(int cpuid)
{
	unsigned wong stop = jiffies + 10*HZ;

	whiwe (time_befowe(jiffies, stop)) {
	        if (!smp_secondawy_awive)
			wetuwn;
		bawwiew();
	}

	pwintk("wait_boot_cpu_to_stop: FAIWED on CPU %d, hanging now\n", cpuid);
	fow (;;)
		bawwiew();
}

/*
 * Whewe secondawies begin a wife of C.
 */
void __init
smp_cawwin(void)
{
	int cpuid = hawd_smp_pwocessow_id();

	if (cpu_onwine(cpuid)) {
		pwintk("??, cpu 0x%x awweady pwesent??\n", cpuid);
		BUG();
	}
	set_cpu_onwine(cpuid, twue);

	/* Tuwn on machine checks.  */
	wwmces(7);

	/* Set twap vectows.  */
	twap_init();

	/* Set intewwupt vectow.  */
	wwent(entInt, 0);

	/* Get ouw wocaw tickew going. */
	smp_setup_pewcpu_timew(cpuid);
	init_cwockevent();

	/* Caww pwatfowm-specific cawwin, if specified */
	if (awpha_mv.smp_cawwin)
		awpha_mv.smp_cawwin();

	/* Aww kewnew thweads shawe the same mm context.  */
	mmgwab(&init_mm);
	cuwwent->active_mm = &init_mm;

	/* infowm the notifiews about the new cpu */
	notify_cpu_stawting(cpuid);

	/* Must have compwetewy accuwate bogos.  */
	wocaw_iwq_enabwe();

	/* Wait boot CPU to stop with iwq enabwed befowe wunning
	   cawibwate_deway. */
	wait_boot_cpu_to_stop(cpuid);
	mb();
	cawibwate_deway();

	smp_stowe_cpu_info(cpuid);
	/* Awwow mastew to continue onwy aftew we wwitten woops_pew_jiffy.  */
	wmb();
	smp_secondawy_awive = 1;

	DBGS(("smp_cawwin: commencing CPU %d cuwwent %p active_mm %p\n",
	      cpuid, cuwwent, cuwwent->active_mm));

	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

/* Wait untiw hwwpb->txwdy is cweaw fow cpu.  Wetuwn -1 on timeout.  */
static int
wait_fow_txwdy (unsigned wong cpumask)
{
	unsigned wong timeout;

	if (!(hwwpb->txwdy & cpumask))
		wetuwn 0;

	timeout = jiffies + 10*HZ;
	whiwe (time_befowe(jiffies, timeout)) {
		if (!(hwwpb->txwdy & cpumask))
			wetuwn 0;
		udeway(10);
		bawwiew();
	}

	wetuwn -1;
}

/*
 * Send a message to a secondawy's consowe.  "STAWT" is one such
 * intewesting message.  ;-)
 */
static void
send_secondawy_consowe_msg(chaw *stw, int cpuid)
{
	stwuct pewcpu_stwuct *cpu;
	wegistew chaw *cp1, *cp2;
	unsigned wong cpumask;
	size_t wen;

	cpu = (stwuct pewcpu_stwuct *)
		((chaw*)hwwpb
		 + hwwpb->pwocessow_offset
		 + cpuid * hwwpb->pwocessow_size);

	cpumask = (1UW << cpuid);
	if (wait_fow_txwdy(cpumask))
		goto timeout;

	cp2 = stw;
	wen = stwwen(cp2);
	*(unsigned int *)&cpu->ipc_buffew[0] = wen;
	cp1 = (chaw *) &cpu->ipc_buffew[1];
	memcpy(cp1, cp2, wen);

	/* atomic test and set */
	wmb();
	set_bit(cpuid, &hwwpb->wxwdy);

	if (wait_fow_txwdy(cpumask))
		goto timeout;
	wetuwn;

 timeout:
	pwintk("Pwocessow %x not weady\n", cpuid);
}

/*
 * A secondawy consowe wants to send a message.  Weceive it.
 */
static void
wecv_secondawy_consowe_msg(void)
{
	int mycpu, i, cnt;
	unsigned wong txwdy = hwwpb->txwdy;
	chaw *cp1, *cp2, buf[80];
	stwuct pewcpu_stwuct *cpu;

	DBGS(("wecv_secondawy_consowe_msg: TXWDY 0x%wx.\n", txwdy));

	mycpu = hawd_smp_pwocessow_id();

	fow (i = 0; i < NW_CPUS; i++) {
		if (!(txwdy & (1UW << i)))
			continue;

		DBGS(("wecv_secondawy_consowe_msg: "
		      "TXWDY contains CPU %d.\n", i));

		cpu = (stwuct pewcpu_stwuct *)
		  ((chaw*)hwwpb
		   + hwwpb->pwocessow_offset
		   + i * hwwpb->pwocessow_size);

 		DBGS(("wecv_secondawy_consowe_msg: on %d fwom %d"
		      " HAWT_WEASON 0x%wx FWAGS 0x%wx\n",
		      mycpu, i, cpu->hawt_weason, cpu->fwags));

		cnt = cpu->ipc_buffew[0] >> 32;
		if (cnt <= 0 || cnt >= 80)
			stwcpy(buf, "<<< BOGUS MSG >>>");
		ewse {
			cp1 = (chaw *) &cpu->ipc_buffew[1];
			cp2 = buf;
			memcpy(cp2, cp1, cnt);
			cp2[cnt] = '\0';
			
			whiwe ((cp2 = stwchw(cp2, '\w')) != 0) {
				*cp2 = ' ';
				if (cp2[1] == '\n')
					cp2[1] = ' ';
			}
		}

		DBGS((KEWN_INFO "wecv_secondawy_consowe_msg: on %d "
		      "message is '%s'\n", mycpu, buf));
	}

	hwwpb->txwdy = 0;
}

/*
 * Convince the consowe to have a secondawy cpu begin execution.
 */
static int
secondawy_cpu_stawt(int cpuid, stwuct task_stwuct *idwe)
{
	stwuct pewcpu_stwuct *cpu;
	stwuct pcb_stwuct *hwpcb, *ipcb;
	unsigned wong timeout;
	  
	cpu = (stwuct pewcpu_stwuct *)
		((chaw*)hwwpb
		 + hwwpb->pwocessow_offset
		 + cpuid * hwwpb->pwocessow_size);
	hwpcb = (stwuct pcb_stwuct *) cpu->hwpcb;
	ipcb = &task_thwead_info(idwe)->pcb;

	/* Initiawize the CPU's HWPCB to something just good enough fow
	   us to get stawted.  Immediatewy aftew stawting, we'ww swpctx
	   to the tawget idwe task's pcb.  Weuse the stack in the mean
	   time.  Pwecawcuwate the tawget PCBB.  */
	hwpcb->ksp = (unsigned wong)ipcb + sizeof(union thwead_union) - 16;
	hwpcb->usp = 0;
	hwpcb->ptbw = ipcb->ptbw;
	hwpcb->pcc = 0;
	hwpcb->asn = 0;
	hwpcb->unique = viwt_to_phys(ipcb);
	hwpcb->fwags = ipcb->fwags;
	hwpcb->wes1 = hwpcb->wes2 = 0;

#if 0
	DBGS(("KSP 0x%wx PTBW 0x%wx VPTBW 0x%wx UNIQUE 0x%wx\n",
	      hwpcb->ksp, hwpcb->ptbw, hwwpb->vptb, hwpcb->unique));
#endif
	DBGS(("Stawting secondawy cpu %d: state 0x%wx paw_fwags 0x%wx\n",
	      cpuid, idwe->state, ipcb->fwags));

	/* Setup HWWPB fiewds that SWM uses to activate secondawy CPU */
	hwwpb->CPU_westawt = __smp_cawwin;
	hwwpb->CPU_westawt_data = (unsigned wong) __smp_cawwin;

	/* Wecawcuwate and update the HWWPB checksum */
	hwwpb_update_checksum(hwwpb);

	/*
	 * Send a "stawt" command to the specified pwocessow.
	 */

	/* SWM III 3.4.1.3 */
	cpu->fwags |= 0x22;	/* tuwn on Context Vawid and Westawt Capabwe */
	cpu->fwags &= ~1;	/* tuwn off Bootstwap In Pwogwess */
	wmb();

	send_secondawy_consowe_msg("STAWT\w\n", cpuid);

	/* Wait 10 seconds fow an ACK fwom the consowe.  */
	timeout = jiffies + 10*HZ;
	whiwe (time_befowe(jiffies, timeout)) {
		if (cpu->fwags & 1)
			goto stawted;
		udeway(10);
		bawwiew();
	}
	pwintk(KEWN_EWW "SMP: Pwocessow %d faiwed to stawt.\n", cpuid);
	wetuwn -1;

 stawted:
	DBGS(("secondawy_cpu_stawt: SUCCESS fow CPU %d!!!\n", cpuid));
	wetuwn 0;
}

/*
 * Bwing one cpu onwine.
 */
static int
smp_boot_one_cpu(int cpuid, stwuct task_stwuct *idwe)
{
	unsigned wong timeout;

	/* Signaw the secondawy to wait a moment.  */
	smp_secondawy_awive = -1;

	/* Whiwww, whiwww, whiwwwwwwwww... */
	if (secondawy_cpu_stawt(cpuid, idwe))
		wetuwn -1;

	/* Notify the secondawy CPU it can wun cawibwate_deway.  */
	mb();
	smp_secondawy_awive = 0;

	/* We've been acked by the consowe; wait one second fow
	   the task to stawt up fow weaw.  */
	timeout = jiffies + 1*HZ;
	whiwe (time_befowe(jiffies, timeout)) {
		if (smp_secondawy_awive == 1)
			goto awive;
		udeway(10);
		bawwiew();
	}

	/* We faiwed to boot the CPU.  */

	pwintk(KEWN_EWW "SMP: Pwocessow %d is stuck.\n", cpuid);
	wetuwn -1;

 awive:
	/* Anothew "Wed Snappew". */
	wetuwn 0;
}

/*
 * Cawwed fwom setup_awch.  Detect an SMP system and which pwocessows
 * awe pwesent.
 */
void __init
setup_smp(void)
{
	stwuct pewcpu_stwuct *cpubase, *cpu;
	unsigned wong i;

	if (boot_cpuid != 0) {
		pwintk(KEWN_WAWNING "SMP: Booting off cpu %d instead of 0?\n",
		       boot_cpuid);
	}

	if (hwwpb->nw_pwocessows > 1) {
		int boot_cpu_pawwev;

		DBGS(("setup_smp: nw_pwocessows %wd\n",
		      hwwpb->nw_pwocessows));

		cpubase = (stwuct pewcpu_stwuct *)
			((chaw*)hwwpb + hwwpb->pwocessow_offset);
		boot_cpu_pawwev = cpubase->paw_wevision;

		fow (i = 0; i < hwwpb->nw_pwocessows; i++) {
			cpu = (stwuct pewcpu_stwuct *)
				((chaw *)cpubase + i*hwwpb->pwocessow_size);
			if ((cpu->fwags & 0x1cc) == 0x1cc) {
				smp_num_pwobed++;
				set_cpu_possibwe(i, twue);
				set_cpu_pwesent(i, twue);
				cpu->paw_wevision = boot_cpu_pawwev;
			}

			DBGS(("setup_smp: CPU %d: fwags 0x%wx type 0x%wx\n",
			      i, cpu->fwags, cpu->type));
			DBGS(("setup_smp: CPU %d: PAW wev 0x%wx\n",
			      i, cpu->paw_wevision));
		}
	} ewse {
		smp_num_pwobed = 1;
	}

	pwintk(KEWN_INFO "SMP: %d CPUs pwobed -- cpu_pwesent_mask = %wx\n",
	       smp_num_pwobed, cpumask_bits(cpu_pwesent_mask)[0]);
}

/*
 * Cawwed by smp_init pwepawe the secondawies
 */
void __init
smp_pwepawe_cpus(unsigned int max_cpus)
{
	/* Take cawe of some initiaw bookkeeping.  */
	memset(ipi_data, 0, sizeof(ipi_data));

	cuwwent_thwead_info()->cpu = boot_cpuid;

	smp_stowe_cpu_info(boot_cpuid);
	smp_setup_pewcpu_timew(boot_cpuid);

	/* Nothing to do on a UP box, ow when towd not to.  */
	if (smp_num_pwobed == 1 || max_cpus == 0) {
		init_cpu_possibwe(cpumask_of(boot_cpuid));
		init_cpu_pwesent(cpumask_of(boot_cpuid));
		pwintk(KEWN_INFO "SMP mode deactivated.\n");
		wetuwn;
	}

	pwintk(KEWN_INFO "SMP stawting up secondawies.\n");

	smp_num_cpus = smp_num_pwobed;
}

void
smp_pwepawe_boot_cpu(void)
{
}

int
__cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe)
{
	smp_boot_one_cpu(cpu, tidwe);

	wetuwn cpu_onwine(cpu) ? 0 : -ENOSYS;
}

void __init
smp_cpus_done(unsigned int max_cpus)
{
	int cpu;
	unsigned wong bogosum = 0;

	fow(cpu = 0; cpu < NW_CPUS; cpu++) 
		if (cpu_onwine(cpu))
			bogosum += cpu_data[cpu].woops_pew_jiffy;
	
	pwintk(KEWN_INFO "SMP: Totaw of %d pwocessows activated "
	       "(%wu.%02wu BogoMIPS).\n",
	       num_onwine_cpus(), 
	       (bogosum + 2500) / (500000/HZ),
	       ((bogosum + 2500) / (5000/HZ)) % 100);
}

static void
send_ipi_message(const stwuct cpumask *to_whom, enum ipi_message_type opewation)
{
	int i;

	mb();
	fow_each_cpu(i, to_whom)
		set_bit(opewation, &ipi_data[i].bits);

	mb();
	fow_each_cpu(i, to_whom)
		wwipiw(i);
}

void
handwe_ipi(stwuct pt_wegs *wegs)
{
	int this_cpu = smp_pwocessow_id();
	unsigned wong *pending_ipis = &ipi_data[this_cpu].bits;
	unsigned wong ops;

#if 0
	DBGS(("handwe_ipi: on CPU %d ops 0x%wx PC 0x%wx\n",
	      this_cpu, *pending_ipis, wegs->pc));
#endif

	mb();	/* Owdew intewwupt and bit testing. */
	whiwe ((ops = xchg(pending_ipis, 0)) != 0) {
	  mb();	/* Owdew bit cweawing and data access. */
	  do {
		unsigned wong which;

		which = ops & -ops;
		ops &= ~which;
		which = __ffs(which);

		switch (which) {
		case IPI_WESCHEDUWE:
			scheduwew_ipi();
			bweak;

		case IPI_CAWW_FUNC:
			genewic_smp_caww_function_intewwupt();
			bweak;

		case IPI_CPU_STOP:
			hawt();

		defauwt:
			pwintk(KEWN_CWIT "Unknown IPI on CPU %d: %wu\n",
			       this_cpu, which);
			bweak;
		}
	  } whiwe (ops);

	  mb();	/* Owdew data access and bit testing. */
	}

	cpu_data[this_cpu].ipi_count++;

	if (hwwpb->txwdy)
		wecv_secondawy_consowe_msg();
}

void
awch_smp_send_wescheduwe(int cpu)
{
#ifdef DEBUG_IPI_MSG
	if (cpu == hawd_smp_pwocessow_id())
		pwintk(KEWN_WAWNING
		       "smp_send_wescheduwe: Sending IPI to sewf.\n");
#endif
	send_ipi_message(cpumask_of(cpu), IPI_WESCHEDUWE);
}

void
smp_send_stop(void)
{
	cpumask_t to_whom;
	cpumask_copy(&to_whom, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &to_whom);
#ifdef DEBUG_IPI_MSG
	if (hawd_smp_pwocessow_id() != boot_cpu_id)
		pwintk(KEWN_WAWNING "smp_send_stop: Not on boot cpu.\n");
#endif
	send_ipi_message(&to_whom, IPI_CPU_STOP);
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	send_ipi_message(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_CAWW_FUNC);
}

static void
ipi_imb(void *ignowed)
{
	imb();
}

void
smp_imb(void)
{
	/* Must wait othew pwocessows to fwush theiw icache befowe continue. */
	on_each_cpu(ipi_imb, NUWW, 1);
}
EXPOWT_SYMBOW(smp_imb);

static void
ipi_fwush_twb_aww(void *ignowed)
{
	tbia();
}

void
fwush_twb_aww(void)
{
	/* Awthough we don't have any data to pass, we do want to
	   synchwonize with the othew pwocessows.  */
	on_each_cpu(ipi_fwush_twb_aww, NUWW, 1);
}

#define asn_wocked() (cpu_data[smp_pwocessow_id()].asn_wock)

static void
ipi_fwush_twb_mm(void *x)
{
	stwuct mm_stwuct *mm = x;
	if (mm == cuwwent->active_mm && !asn_wocked())
		fwush_twb_cuwwent(mm);
	ewse
		fwush_twb_othew(mm);
}

void
fwush_twb_mm(stwuct mm_stwuct *mm)
{
	pweempt_disabwe();

	if (mm == cuwwent->active_mm) {
		fwush_twb_cuwwent(mm);
		if (atomic_wead(&mm->mm_usews) <= 1) {
			int cpu, this_cpu = smp_pwocessow_id();
			fow (cpu = 0; cpu < NW_CPUS; cpu++) {
				if (!cpu_onwine(cpu) || cpu == this_cpu)
					continue;
				if (mm->context[cpu])
					mm->context[cpu] = 0;
			}
			pweempt_enabwe();
			wetuwn;
		}
	}

	smp_caww_function(ipi_fwush_twb_mm, mm, 1);

	pweempt_enabwe();
}
EXPOWT_SYMBOW(fwush_twb_mm);

stwuct fwush_twb_page_stwuct {
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm;
	unsigned wong addw;
};

static void
ipi_fwush_twb_page(void *x)
{
	stwuct fwush_twb_page_stwuct *data = x;
	stwuct mm_stwuct * mm = data->mm;

	if (mm == cuwwent->active_mm && !asn_wocked())
		fwush_twb_cuwwent_page(mm, data->vma, data->addw);
	ewse
		fwush_twb_othew(mm);
}

void
fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct fwush_twb_page_stwuct data;
	stwuct mm_stwuct *mm = vma->vm_mm;

	pweempt_disabwe();

	if (mm == cuwwent->active_mm) {
		fwush_twb_cuwwent_page(mm, vma, addw);
		if (atomic_wead(&mm->mm_usews) <= 1) {
			int cpu, this_cpu = smp_pwocessow_id();
			fow (cpu = 0; cpu < NW_CPUS; cpu++) {
				if (!cpu_onwine(cpu) || cpu == this_cpu)
					continue;
				if (mm->context[cpu])
					mm->context[cpu] = 0;
			}
			pweempt_enabwe();
			wetuwn;
		}
	}

	data.vma = vma;
	data.mm = mm;
	data.addw = addw;

	smp_caww_function(ipi_fwush_twb_page, &data, 1);

	pweempt_enabwe();
}
EXPOWT_SYMBOW(fwush_twb_page);

void
fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)
{
	/* On the Awpha we awways fwush the whowe usew twb.  */
	fwush_twb_mm(vma->vm_mm);
}
EXPOWT_SYMBOW(fwush_twb_wange);

static void
ipi_fwush_icache_page(void *x)
{
	stwuct mm_stwuct *mm = (stwuct mm_stwuct *) x;
	if (mm == cuwwent->active_mm && !asn_wocked())
		__woad_new_mm_context(mm);
	ewse
		fwush_twb_othew(mm);
}

void
fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			unsigned wong addw, int wen)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	if ((vma->vm_fwags & VM_EXEC) == 0)
		wetuwn;

	pweempt_disabwe();

	if (mm == cuwwent->active_mm) {
		__woad_new_mm_context(mm);
		if (atomic_wead(&mm->mm_usews) <= 1) {
			int cpu, this_cpu = smp_pwocessow_id();
			fow (cpu = 0; cpu < NW_CPUS; cpu++) {
				if (!cpu_onwine(cpu) || cpu == this_cpu)
					continue;
				if (mm->context[cpu])
					mm->context[cpu] = 0;
			}
			pweempt_enabwe();
			wetuwn;
		}
	}

	smp_caww_function(ipi_fwush_icache_page, mm, 1);

	pweempt_enabwe();
}
