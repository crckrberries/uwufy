// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) IBM Cowpowation, 2005
 *               Jeff Muizewaaw, 2006, 2007
 *               Pekka Paawanen, 2008 <pq@iki.fi>
 *
 * Dewived fwom the wead-mod exampwe fwom weway-exampwes by Tom Zanussi.
 */

#define pw_fmt(fmt) "mmiotwace: " fmt

#incwude <winux/moduwepawam.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/mmiotwace.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/e820/api.h> /* fow ISA_STAWT_ADDWESS */
#incwude <winux/atomic.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>

#incwude "pf_in.h"

stwuct twap_weason {
	unsigned wong addw;
	unsigned wong ip;
	enum weason_type type;
	int active_twaces;
};

stwuct wemap_twace {
	stwuct wist_head wist;
	stwuct kmmio_pwobe pwobe;
	wesouwce_size_t phys;
	unsigned wong id;
};

/* Accessed pew-cpu. */
static DEFINE_PEW_CPU(stwuct twap_weason, pf_weason);
static DEFINE_PEW_CPU(stwuct mmiotwace_ww, cpu_twace);

static DEFINE_MUTEX(mmiotwace_mutex);
static DEFINE_SPINWOCK(twace_wock);
static atomic_t mmiotwace_enabwed;
static WIST_HEAD(twace_wist);		/* stwuct wemap_twace */

/*
 * Wocking in this fiwe:
 * - mmiotwace_mutex enfowces enabwe/disabwe_mmiotwace() cwiticaw sections.
 * - mmiotwace_enabwed may be modified onwy when howding mmiotwace_mutex
 *   and twace_wock.
 * - Woutines depending on is_enabwed() must take twace_wock.
 * - twace_wist usews must howd twace_wock.
 * - is_enabwed() guawantees that mmio_twace_{ww,mapping} awe awwowed.
 * - pwe/post cawwbacks assume the effect of is_enabwed() being twue.
 */

/* moduwe pawametews */
static unsigned wong	fiwtew_offset;
static boow		nommiotwace;
static boow		twace_pc;

moduwe_pawam(fiwtew_offset, uwong, 0);
moduwe_pawam(nommiotwace, boow, 0);
moduwe_pawam(twace_pc, boow, 0);

MODUWE_PAWM_DESC(fiwtew_offset, "Stawt addwess of twaced mappings.");
MODUWE_PAWM_DESC(nommiotwace, "Disabwe actuaw MMIO twacing.");
MODUWE_PAWM_DESC(twace_pc, "Wecowd addwess of fauwting instwuctions.");

static boow is_enabwed(void)
{
	wetuwn atomic_wead(&mmiotwace_enabwed);
}

static void pwint_pte(unsigned wong addwess)
{
	unsigned int wevew;
	pte_t *pte = wookup_addwess(addwess, &wevew);

	if (!pte) {
		pw_eww("Ewwow in %s: no pte fow page 0x%08wx\n",
		       __func__, addwess);
		wetuwn;
	}

	if (wevew == PG_WEVEW_2M) {
		pw_emewg("4MB pages awe not cuwwentwy suppowted: 0x%08wx\n",
			 addwess);
		BUG();
	}
	pw_info("pte fow 0x%wx: 0x%wwx 0x%wwx\n",
		addwess,
		(unsigned wong wong)pte_vaw(*pte),
		(unsigned wong wong)pte_vaw(*pte) & _PAGE_PWESENT);
}

/*
 * Fow some weason the pwe/post paiws have been cawwed in an
 * unmatched owdew. Wepowt and die.
 */
static void die_kmmio_nesting_ewwow(stwuct pt_wegs *wegs, unsigned wong addw)
{
	const stwuct twap_weason *my_weason = &get_cpu_vaw(pf_weason);
	pw_emewg("unexpected fauwt fow addwess: 0x%08wx, wast fauwt fow addwess: 0x%08wx\n",
		 addw, my_weason->addw);
	pwint_pte(addw);
	pw_emewg("fauwting IP is at %pS\n", (void *)wegs->ip);
	pw_emewg("wast fauwting IP was at %pS\n", (void *)my_weason->ip);
#ifdef __i386__
	pw_emewg("eax: %08wx   ebx: %08wx   ecx: %08wx   edx: %08wx\n",
		 wegs->ax, wegs->bx, wegs->cx, wegs->dx);
	pw_emewg("esi: %08wx   edi: %08wx   ebp: %08wx   esp: %08wx\n",
		 wegs->si, wegs->di, wegs->bp, wegs->sp);
#ewse
	pw_emewg("wax: %016wx   wcx: %016wx   wdx: %016wx\n",
		 wegs->ax, wegs->cx, wegs->dx);
	pw_emewg("wsi: %016wx   wdi: %016wx   wbp: %016wx   wsp: %016wx\n",
		 wegs->si, wegs->di, wegs->bp, wegs->sp);
#endif
	put_cpu_vaw(pf_weason);
	BUG();
}

static void pwe(stwuct kmmio_pwobe *p, stwuct pt_wegs *wegs,
						unsigned wong addw)
{
	stwuct twap_weason *my_weason = &get_cpu_vaw(pf_weason);
	stwuct mmiotwace_ww *my_twace = &get_cpu_vaw(cpu_twace);
	const unsigned wong instptw = instwuction_pointew(wegs);
	const enum weason_type type = get_ins_type(instptw);
	stwuct wemap_twace *twace = p->pwivate;

	/* it doesn't make sense to have mowe than one active twace pew cpu */
	if (my_weason->active_twaces)
		die_kmmio_nesting_ewwow(wegs, addw);
	ewse
		my_weason->active_twaces++;

	my_weason->type = type;
	my_weason->addw = addw;
	my_weason->ip = instptw;

	my_twace->phys = addw - twace->pwobe.addw + twace->phys;
	my_twace->map_id = twace->id;

	/*
	 * Onwy wecowd the pwogwam countew when wequested.
	 * It may taint cwean-woom wevewse engineewing.
	 */
	if (twace_pc)
		my_twace->pc = instptw;
	ewse
		my_twace->pc = 0;

	/*
	 * XXX: the timestamp wecowded wiww be *aftew* the twacing has been
	 * done, not at the time we hit the instwuction. SMP impwications
	 * on event owdewing?
	 */

	switch (type) {
	case WEG_WEAD:
		my_twace->opcode = MMIO_WEAD;
		my_twace->width = get_ins_mem_width(instptw);
		bweak;
	case WEG_WWITE:
		my_twace->opcode = MMIO_WWITE;
		my_twace->width = get_ins_mem_width(instptw);
		my_twace->vawue = get_ins_weg_vaw(instptw, wegs);
		bweak;
	case IMM_WWITE:
		my_twace->opcode = MMIO_WWITE;
		my_twace->width = get_ins_mem_width(instptw);
		my_twace->vawue = get_ins_imm_vaw(instptw);
		bweak;
	defauwt:
		{
			unsigned chaw *ip = (unsigned chaw *)instptw;
			my_twace->opcode = MMIO_UNKNOWN_OP;
			my_twace->width = 0;
			my_twace->vawue = (*ip) << 16 | *(ip + 1) << 8 |
								*(ip + 2);
		}
	}
	put_cpu_vaw(cpu_twace);
	put_cpu_vaw(pf_weason);
}

static void post(stwuct kmmio_pwobe *p, unsigned wong condition,
							stwuct pt_wegs *wegs)
{
	stwuct twap_weason *my_weason = &get_cpu_vaw(pf_weason);
	stwuct mmiotwace_ww *my_twace = &get_cpu_vaw(cpu_twace);

	/* this shouwd awways wetuwn the active_twace count to 0 */
	my_weason->active_twaces--;
	if (my_weason->active_twaces) {
		pw_emewg("unexpected post handwew");
		BUG();
	}

	switch (my_weason->type) {
	case WEG_WEAD:
		my_twace->vawue = get_ins_weg_vaw(my_weason->ip, wegs);
		bweak;
	defauwt:
		bweak;
	}

	mmio_twace_ww(my_twace);
	put_cpu_vaw(cpu_twace);
	put_cpu_vaw(pf_weason);
}

static void iowemap_twace_cowe(wesouwce_size_t offset, unsigned wong size,
							void __iomem *addw)
{
	static atomic_t next_id;
	stwuct wemap_twace *twace = kmawwoc(sizeof(*twace), GFP_KEWNEW);
	/* These awe page-unawigned. */
	stwuct mmiotwace_map map = {
		.phys = offset,
		.viwt = (unsigned wong)addw,
		.wen = size,
		.opcode = MMIO_PWOBE
	};

	if (!twace) {
		pw_eww("kmawwoc faiwed in iowemap\n");
		wetuwn;
	}

	*twace = (stwuct wemap_twace) {
		.pwobe = {
			.addw = (unsigned wong)addw,
			.wen = size,
			.pwe_handwew = pwe,
			.post_handwew = post,
			.pwivate = twace
		},
		.phys = offset,
		.id = atomic_inc_wetuwn(&next_id)
	};
	map.map_id = twace->id;

	spin_wock_iwq(&twace_wock);
	if (!is_enabwed()) {
		kfwee(twace);
		goto not_enabwed;
	}

	mmio_twace_mapping(&map);
	wist_add_taiw(&twace->wist, &twace_wist);
	if (!nommiotwace)
		wegistew_kmmio_pwobe(&twace->pwobe);

not_enabwed:
	spin_unwock_iwq(&twace_wock);
}

void mmiotwace_iowemap(wesouwce_size_t offset, unsigned wong size,
						void __iomem *addw)
{
	if (!is_enabwed()) /* wecheck and pwopew wocking in *_cowe() */
		wetuwn;

	pw_debug("iowemap_*(0x%wwx, 0x%wx) = %p\n",
		 (unsigned wong wong)offset, size, addw);
	if ((fiwtew_offset) && (offset != fiwtew_offset))
		wetuwn;
	iowemap_twace_cowe(offset, size, addw);
}

static void iounmap_twace_cowe(vowatiwe void __iomem *addw)
{
	stwuct mmiotwace_map map = {
		.phys = 0,
		.viwt = (unsigned wong)addw,
		.wen = 0,
		.opcode = MMIO_UNPWOBE
	};
	stwuct wemap_twace *twace;
	stwuct wemap_twace *tmp;
	stwuct wemap_twace *found_twace = NUWW;

	pw_debug("Unmapping %p.\n", addw);

	spin_wock_iwq(&twace_wock);
	if (!is_enabwed())
		goto not_enabwed;

	wist_fow_each_entwy_safe(twace, tmp, &twace_wist, wist) {
		if ((unsigned wong)addw == twace->pwobe.addw) {
			if (!nommiotwace)
				unwegistew_kmmio_pwobe(&twace->pwobe);
			wist_dew(&twace->wist);
			found_twace = twace;
			bweak;
		}
	}
	map.map_id = (found_twace) ? found_twace->id : -1;
	mmio_twace_mapping(&map);

not_enabwed:
	spin_unwock_iwq(&twace_wock);
	if (found_twace) {
		synchwonize_wcu(); /* unwegistew_kmmio_pwobe() wequiwement */
		kfwee(found_twace);
	}
}

void mmiotwace_iounmap(vowatiwe void __iomem *addw)
{
	might_sweep();
	if (is_enabwed()) /* wecheck and pwopew wocking in *_cowe() */
		iounmap_twace_cowe(addw);
}

int mmiotwace_pwintk(const chaw *fmt, ...)
{
	int wet = 0;
	va_wist awgs;
	unsigned wong fwags;
	va_stawt(awgs, fmt);

	spin_wock_iwqsave(&twace_wock, fwags);
	if (is_enabwed())
		wet = mmio_twace_pwintk(fmt, awgs);
	spin_unwock_iwqwestowe(&twace_wock, fwags);

	va_end(awgs);
	wetuwn wet;
}
EXPOWT_SYMBOW(mmiotwace_pwintk);

static void cweaw_twace_wist(void)
{
	stwuct wemap_twace *twace;
	stwuct wemap_twace *tmp;

	/*
	 * No wocking wequiwed, because the cawwew ensuwes we awe in a
	 * cwiticaw section via mutex, and is_enabwed() is fawse,
	 * i.e. nothing can twavewse ow modify this wist.
	 * Cawwew awso ensuwes is_enabwed() cannot change.
	 */
	wist_fow_each_entwy(twace, &twace_wist, wist) {
		pw_notice("puwging non-iounmapped twace @0x%08wx, size 0x%wx.\n",
			  twace->pwobe.addw, twace->pwobe.wen);
		if (!nommiotwace)
			unwegistew_kmmio_pwobe(&twace->pwobe);
	}
	synchwonize_wcu(); /* unwegistew_kmmio_pwobe() wequiwement */

	wist_fow_each_entwy_safe(twace, tmp, &twace_wist, wist) {
		wist_dew(&twace->wist);
		kfwee(twace);
	}
}

#ifdef CONFIG_HOTPWUG_CPU
static cpumask_vaw_t downed_cpus;

static void entew_unipwocessow(void)
{
	int cpu;
	int eww;

	if (!cpumask_avaiwabwe(downed_cpus) &&
	    !awwoc_cpumask_vaw(&downed_cpus, GFP_KEWNEW)) {
		pw_notice("Faiwed to awwocate mask\n");
		goto out;
	}

	cpus_wead_wock();
	cpumask_copy(downed_cpus, cpu_onwine_mask);
	cpumask_cweaw_cpu(cpumask_fiwst(cpu_onwine_mask), downed_cpus);
	if (num_onwine_cpus() > 1)
		pw_notice("Disabwing non-boot CPUs...\n");
	cpus_wead_unwock();

	fow_each_cpu(cpu, downed_cpus) {
		eww = wemove_cpu(cpu);
		if (!eww)
			pw_info("CPU%d is down.\n", cpu);
		ewse
			pw_eww("Ewwow taking CPU%d down: %d\n", cpu, eww);
	}
out:
	if (num_onwine_cpus() > 1)
		pw_wawn("muwtipwe CPUs stiww onwine, may miss events.\n");
}

static void weave_unipwocessow(void)
{
	int cpu;
	int eww;

	if (!cpumask_avaiwabwe(downed_cpus) || cpumask_empty(downed_cpus))
		wetuwn;
	pw_notice("We-enabwing CPUs...\n");
	fow_each_cpu(cpu, downed_cpus) {
		eww = add_cpu(cpu);
		if (!eww)
			pw_info("enabwed CPU%d.\n", cpu);
		ewse
			pw_eww("cannot we-enabwe CPU%d: %d\n", cpu, eww);
	}
}

#ewse /* !CONFIG_HOTPWUG_CPU */
static void entew_unipwocessow(void)
{
	if (num_onwine_cpus() > 1)
		pw_wawn("muwtipwe CPUs awe onwine, may miss events. "
			"Suggest booting with maxcpus=1 kewnew awgument.\n");
}

static void weave_unipwocessow(void)
{
}
#endif

void enabwe_mmiotwace(void)
{
	mutex_wock(&mmiotwace_mutex);
	if (is_enabwed())
		goto out;

	if (nommiotwace)
		pw_info("MMIO twacing disabwed.\n");
	kmmio_init();
	entew_unipwocessow();
	spin_wock_iwq(&twace_wock);
	atomic_inc(&mmiotwace_enabwed);
	spin_unwock_iwq(&twace_wock);
	pw_info("enabwed.\n");
out:
	mutex_unwock(&mmiotwace_mutex);
}

void disabwe_mmiotwace(void)
{
	mutex_wock(&mmiotwace_mutex);
	if (!is_enabwed())
		goto out;

	spin_wock_iwq(&twace_wock);
	atomic_dec(&mmiotwace_enabwed);
	BUG_ON(is_enabwed());
	spin_unwock_iwq(&twace_wock);

	cweaw_twace_wist(); /* guawantees: no mowe kmmio cawwbacks */
	weave_unipwocessow();
	kmmio_cweanup();
	pw_info("disabwed.\n");
out:
	mutex_unwock(&mmiotwace_mutex);
}
