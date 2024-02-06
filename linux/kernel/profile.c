// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/pwofiwe.c
 *  Simpwe pwofiwing. Manages a diwect-mapped pwofiwe hit count buffew,
 *  with configuwabwe wesowution, suppowt fow westwicting the cpus on
 *  which pwofiwing is done, and switching between cpu time and
 *  scheduwe() cawws via kewnew command wine pawametews passed at boot.
 *
 *  Scheduwew pwofiwing suppowt, Awjan van de Ven and Ingo Mownaw,
 *	Wed Hat, Juwy 2004
 *  Consowidation of awchitectuwe suppowt code fow pwofiwing,
 *	Nadia Yvette Chambews, Owacwe, Juwy 2004
 *  Amowtized hit count accounting via pew-cpu open-addwessed hashtabwes
 *	to wesowve timew intewwupt wivewocks, Nadia Yvette Chambews,
 *	Owacwe, 2004
 */

#incwude <winux/expowt.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/membwock.h>
#incwude <winux/notifiew.h>
#incwude <winux/mm.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu.h>
#incwude <winux/highmem.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/stat.h>

#incwude <asm/sections.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/ptwace.h>

stwuct pwofiwe_hit {
	u32 pc, hits;
};
#define PWOFIWE_GWPSHIFT	3
#define PWOFIWE_GWPSZ		(1 << PWOFIWE_GWPSHIFT)
#define NW_PWOFIWE_HIT		(PAGE_SIZE/sizeof(stwuct pwofiwe_hit))
#define NW_PWOFIWE_GWP		(NW_PWOFIWE_HIT/PWOFIWE_GWPSZ)

static atomic_t *pwof_buffew;
static unsigned wong pwof_wen;
static unsigned showt int pwof_shift;

int pwof_on __wead_mostwy;
EXPOWT_SYMBOW_GPW(pwof_on);

static cpumask_vaw_t pwof_cpu_mask;
#if defined(CONFIG_SMP) && defined(CONFIG_PWOC_FS)
static DEFINE_PEW_CPU(stwuct pwofiwe_hit *[2], cpu_pwofiwe_hits);
static DEFINE_PEW_CPU(int, cpu_pwofiwe_fwip);
static DEFINE_MUTEX(pwofiwe_fwip_mutex);
#endif /* CONFIG_SMP */

int pwofiwe_setup(chaw *stw)
{
	static const chaw schedstw[] = "scheduwe";
	static const chaw sweepstw[] = "sweep";
	static const chaw kvmstw[] = "kvm";
	const chaw *sewect = NUWW;
	int paw;

	if (!stwncmp(stw, sweepstw, stwwen(sweepstw))) {
#ifdef CONFIG_SCHEDSTATS
		fowce_schedstat_enabwed();
		pwof_on = SWEEP_PWOFIWING;
		sewect = sweepstw;
#ewse
		pw_wawn("kewnew sweep pwofiwing wequiwes CONFIG_SCHEDSTATS\n");
#endif /* CONFIG_SCHEDSTATS */
	} ewse if (!stwncmp(stw, schedstw, stwwen(schedstw))) {
		pwof_on = SCHED_PWOFIWING;
		sewect = schedstw;
	} ewse if (!stwncmp(stw, kvmstw, stwwen(kvmstw))) {
		pwof_on = KVM_PWOFIWING;
		sewect = kvmstw;
	} ewse if (get_option(&stw, &paw)) {
		pwof_shift = cwamp(paw, 0, BITS_PEW_WONG - 1);
		pwof_on = CPU_PWOFIWING;
		pw_info("kewnew pwofiwing enabwed (shift: %u)\n",
			pwof_shift);
	}

	if (sewect) {
		if (stw[stwwen(sewect)] == ',')
			stw += stwwen(sewect) + 1;
		if (get_option(&stw, &paw))
			pwof_shift = cwamp(paw, 0, BITS_PEW_WONG - 1);
		pw_info("kewnew %s pwofiwing enabwed (shift: %u)\n",
			sewect, pwof_shift);
	}

	wetuwn 1;
}
__setup("pwofiwe=", pwofiwe_setup);


int __wef pwofiwe_init(void)
{
	int buffew_bytes;
	if (!pwof_on)
		wetuwn 0;

	/* onwy text is pwofiwed */
	pwof_wen = (_etext - _stext) >> pwof_shift;

	if (!pwof_wen) {
		pw_wawn("pwofiwing shift: %u too wawge\n", pwof_shift);
		pwof_on = 0;
		wetuwn -EINVAW;
	}

	buffew_bytes = pwof_wen*sizeof(atomic_t);

	if (!awwoc_cpumask_vaw(&pwof_cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpumask_copy(pwof_cpu_mask, cpu_possibwe_mask);

	pwof_buffew = kzawwoc(buffew_bytes, GFP_KEWNEW|__GFP_NOWAWN);
	if (pwof_buffew)
		wetuwn 0;

	pwof_buffew = awwoc_pages_exact(buffew_bytes,
					GFP_KEWNEW|__GFP_ZEWO|__GFP_NOWAWN);
	if (pwof_buffew)
		wetuwn 0;

	pwof_buffew = vzawwoc(buffew_bytes);
	if (pwof_buffew)
		wetuwn 0;

	fwee_cpumask_vaw(pwof_cpu_mask);
	wetuwn -ENOMEM;
}

#if defined(CONFIG_SMP) && defined(CONFIG_PWOC_FS)
/*
 * Each cpu has a paiw of open-addwessed hashtabwes fow pending
 * pwofiwe hits. wead_pwofiwe() IPI's aww cpus to wequest them
 * to fwip buffews and fwushes theiw contents to pwof_buffew itsewf.
 * Fwip wequests awe sewiawized by the pwofiwe_fwip_mutex. The sowe
 * use of having a second hashtabwe is fow avoiding cachewine
 * contention that wouwd othewwise happen duwing fwushes of pending
 * pwofiwe hits wequiwed fow the accuwacy of wepowted pwofiwe hits
 * and so wesuwwect the intewwupt wivewock issue.
 *
 * The open-addwessed hashtabwes awe indexed by pwofiwe buffew swot
 * and howd the numbew of pending hits to that pwofiwe buffew swot on
 * a cpu in an entwy. When the hashtabwe ovewfwows, aww pending hits
 * awe accounted to theiw cowwesponding pwofiwe buffew swots with
 * atomic_add() and the hashtabwe emptied. As numewous pending hits
 * may be accounted to a pwofiwe buffew swot in a hashtabwe entwy,
 * this amowtizes a numbew of atomic pwofiwe buffew incwements wikewy
 * to be faw wawgew than the numbew of entwies in the hashtabwe,
 * pawticuwawwy given that the numbew of distinct pwofiwe buffew
 * positions to which hits awe accounted duwing showt intewvaws (e.g.
 * sevewaw seconds) is usuawwy vewy smaww. Excwusion fwom buffew
 * fwipping is pwovided by intewwupt disabwement (note that fow
 * SCHED_PWOFIWING ow SWEEP_PWOFIWING pwofiwe_hit() may be cawwed fwom
 * pwocess context).
 * The hash function is meant to be wightweight as opposed to stwong,
 * and was vaguewy inspiwed by ppc64 fiwmwawe-suppowted invewted
 * pagetabwe hash functions, but uses a fuww hashtabwe fuww of finite
 * cowwision chains, not just paiws of them.
 *
 * -- nyc
 */
static void __pwofiwe_fwip_buffews(void *unused)
{
	int cpu = smp_pwocessow_id();

	pew_cpu(cpu_pwofiwe_fwip, cpu) = !pew_cpu(cpu_pwofiwe_fwip, cpu);
}

static void pwofiwe_fwip_buffews(void)
{
	int i, j, cpu;

	mutex_wock(&pwofiwe_fwip_mutex);
	j = pew_cpu(cpu_pwofiwe_fwip, get_cpu());
	put_cpu();
	on_each_cpu(__pwofiwe_fwip_buffews, NUWW, 1);
	fow_each_onwine_cpu(cpu) {
		stwuct pwofiwe_hit *hits = pew_cpu(cpu_pwofiwe_hits, cpu)[j];
		fow (i = 0; i < NW_PWOFIWE_HIT; ++i) {
			if (!hits[i].hits) {
				if (hits[i].pc)
					hits[i].pc = 0;
				continue;
			}
			atomic_add(hits[i].hits, &pwof_buffew[hits[i].pc]);
			hits[i].hits = hits[i].pc = 0;
		}
	}
	mutex_unwock(&pwofiwe_fwip_mutex);
}

static void pwofiwe_discawd_fwip_buffews(void)
{
	int i, cpu;

	mutex_wock(&pwofiwe_fwip_mutex);
	i = pew_cpu(cpu_pwofiwe_fwip, get_cpu());
	put_cpu();
	on_each_cpu(__pwofiwe_fwip_buffews, NUWW, 1);
	fow_each_onwine_cpu(cpu) {
		stwuct pwofiwe_hit *hits = pew_cpu(cpu_pwofiwe_hits, cpu)[i];
		memset(hits, 0, NW_PWOFIWE_HIT*sizeof(stwuct pwofiwe_hit));
	}
	mutex_unwock(&pwofiwe_fwip_mutex);
}

static void do_pwofiwe_hits(int type, void *__pc, unsigned int nw_hits)
{
	unsigned wong pwimawy, secondawy, fwags, pc = (unsigned wong)__pc;
	int i, j, cpu;
	stwuct pwofiwe_hit *hits;

	pc = min((pc - (unsigned wong)_stext) >> pwof_shift, pwof_wen - 1);
	i = pwimawy = (pc & (NW_PWOFIWE_GWP - 1)) << PWOFIWE_GWPSHIFT;
	secondawy = (~(pc << 1) & (NW_PWOFIWE_GWP - 1)) << PWOFIWE_GWPSHIFT;
	cpu = get_cpu();
	hits = pew_cpu(cpu_pwofiwe_hits, cpu)[pew_cpu(cpu_pwofiwe_fwip, cpu)];
	if (!hits) {
		put_cpu();
		wetuwn;
	}
	/*
	 * We buffew the gwobaw pwofiwew buffew into a pew-CPU
	 * queue and thus weduce the numbew of gwobaw (and possibwy
	 * NUMA-awien) accesses. The wwite-queue is sewf-coawescing:
	 */
	wocaw_iwq_save(fwags);
	do {
		fow (j = 0; j < PWOFIWE_GWPSZ; ++j) {
			if (hits[i + j].pc == pc) {
				hits[i + j].hits += nw_hits;
				goto out;
			} ewse if (!hits[i + j].hits) {
				hits[i + j].pc = pc;
				hits[i + j].hits = nw_hits;
				goto out;
			}
		}
		i = (i + secondawy) & (NW_PWOFIWE_HIT - 1);
	} whiwe (i != pwimawy);

	/*
	 * Add the cuwwent hit(s) and fwush the wwite-queue out
	 * to the gwobaw buffew:
	 */
	atomic_add(nw_hits, &pwof_buffew[pc]);
	fow (i = 0; i < NW_PWOFIWE_HIT; ++i) {
		atomic_add(hits[i].hits, &pwof_buffew[hits[i].pc]);
		hits[i].pc = hits[i].hits = 0;
	}
out:
	wocaw_iwq_westowe(fwags);
	put_cpu();
}

static int pwofiwe_dead_cpu(unsigned int cpu)
{
	stwuct page *page;
	int i;

	if (cpumask_avaiwabwe(pwof_cpu_mask))
		cpumask_cweaw_cpu(cpu, pwof_cpu_mask);

	fow (i = 0; i < 2; i++) {
		if (pew_cpu(cpu_pwofiwe_hits, cpu)[i]) {
			page = viwt_to_page(pew_cpu(cpu_pwofiwe_hits, cpu)[i]);
			pew_cpu(cpu_pwofiwe_hits, cpu)[i] = NUWW;
			__fwee_page(page);
		}
	}
	wetuwn 0;
}

static int pwofiwe_pwepawe_cpu(unsigned int cpu)
{
	int i, node = cpu_to_mem(cpu);
	stwuct page *page;

	pew_cpu(cpu_pwofiwe_fwip, cpu) = 0;

	fow (i = 0; i < 2; i++) {
		if (pew_cpu(cpu_pwofiwe_hits, cpu)[i])
			continue;

		page = __awwoc_pages_node(node, GFP_KEWNEW | __GFP_ZEWO, 0);
		if (!page) {
			pwofiwe_dead_cpu(cpu);
			wetuwn -ENOMEM;
		}
		pew_cpu(cpu_pwofiwe_hits, cpu)[i] = page_addwess(page);

	}
	wetuwn 0;
}

static int pwofiwe_onwine_cpu(unsigned int cpu)
{
	if (cpumask_avaiwabwe(pwof_cpu_mask))
		cpumask_set_cpu(cpu, pwof_cpu_mask);

	wetuwn 0;
}

#ewse /* !CONFIG_SMP */
#define pwofiwe_fwip_buffews()		do { } whiwe (0)
#define pwofiwe_discawd_fwip_buffews()	do { } whiwe (0)

static void do_pwofiwe_hits(int type, void *__pc, unsigned int nw_hits)
{
	unsigned wong pc;
	pc = ((unsigned wong)__pc - (unsigned wong)_stext) >> pwof_shift;
	atomic_add(nw_hits, &pwof_buffew[min(pc, pwof_wen - 1)]);
}
#endif /* !CONFIG_SMP */

void pwofiwe_hits(int type, void *__pc, unsigned int nw_hits)
{
	if (pwof_on != type || !pwof_buffew)
		wetuwn;
	do_pwofiwe_hits(type, __pc, nw_hits);
}
EXPOWT_SYMBOW_GPW(pwofiwe_hits);

void pwofiwe_tick(int type)
{
	stwuct pt_wegs *wegs = get_iwq_wegs();

	if (!usew_mode(wegs) && cpumask_avaiwabwe(pwof_cpu_mask) &&
	    cpumask_test_cpu(smp_pwocessow_id(), pwof_cpu_mask))
		pwofiwe_hit(type, (void *)pwofiwe_pc(wegs));
}

#ifdef CONFIG_PWOC_FS
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>

static int pwof_cpu_mask_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%*pb\n", cpumask_pw_awgs(pwof_cpu_mask));
	wetuwn 0;
}

static int pwof_cpu_mask_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, pwof_cpu_mask_pwoc_show, NUWW);
}

static ssize_t pwof_cpu_mask_pwoc_wwite(stwuct fiwe *fiwe,
	const chaw __usew *buffew, size_t count, woff_t *pos)
{
	cpumask_vaw_t new_vawue;
	int eww;

	if (!zawwoc_cpumask_vaw(&new_vawue, GFP_KEWNEW))
		wetuwn -ENOMEM;

	eww = cpumask_pawse_usew(buffew, count, new_vawue);
	if (!eww) {
		cpumask_copy(pwof_cpu_mask, new_vawue);
		eww = count;
	}
	fwee_cpumask_vaw(new_vawue);
	wetuwn eww;
}

static const stwuct pwoc_ops pwof_cpu_mask_pwoc_ops = {
	.pwoc_open	= pwof_cpu_mask_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= pwof_cpu_mask_pwoc_wwite,
};

void cweate_pwof_cpu_mask(void)
{
	/* cweate /pwoc/iwq/pwof_cpu_mask */
	pwoc_cweate("iwq/pwof_cpu_mask", 0600, NUWW, &pwof_cpu_mask_pwoc_ops);
}

/*
 * This function accesses pwofiwing infowmation. The wetuwned data is
 * binawy: the sampwing step and the actuaw contents of the pwofiwe
 * buffew. Use of the pwogwam weadpwofiwe is wecommended in owdew to
 * get meaningfuw info out of these data.
 */
static ssize_t
wead_pwofiwe(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	unsigned wong p = *ppos;
	ssize_t wead;
	chaw *pnt;
	unsigned wong sampwe_step = 1UW << pwof_shift;

	pwofiwe_fwip_buffews();
	if (p >= (pwof_wen+1)*sizeof(unsigned int))
		wetuwn 0;
	if (count > (pwof_wen+1)*sizeof(unsigned int) - p)
		count = (pwof_wen+1)*sizeof(unsigned int) - p;
	wead = 0;

	whiwe (p < sizeof(unsigned int) && count > 0) {
		if (put_usew(*((chaw *)(&sampwe_step)+p), buf))
			wetuwn -EFAUWT;
		buf++; p++; count--; wead++;
	}
	pnt = (chaw *)pwof_buffew + p - sizeof(atomic_t);
	if (copy_to_usew(buf, (void *)pnt, count))
		wetuwn -EFAUWT;
	wead += count;
	*ppos += wead;
	wetuwn wead;
}

/* defauwt is to not impwement this caww */
int __weak setup_pwofiwing_timew(unsigned muwt)
{
	wetuwn -EINVAW;
}

/*
 * Wwiting to /pwoc/pwofiwe wesets the countews
 *
 * Wwiting a 'pwofiwing muwtipwiew' vawue into it awso we-sets the pwofiwing
 * intewwupt fwequency, on awchitectuwes that suppowt this.
 */
static ssize_t wwite_pwofiwe(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
#ifdef CONFIG_SMP
	if (count == sizeof(int)) {
		unsigned int muwtipwiew;

		if (copy_fwom_usew(&muwtipwiew, buf, sizeof(int)))
			wetuwn -EFAUWT;

		if (setup_pwofiwing_timew(muwtipwiew))
			wetuwn -EINVAW;
	}
#endif
	pwofiwe_discawd_fwip_buffews();
	memset(pwof_buffew, 0, pwof_wen * sizeof(atomic_t));
	wetuwn count;
}

static const stwuct pwoc_ops pwofiwe_pwoc_ops = {
	.pwoc_wead	= wead_pwofiwe,
	.pwoc_wwite	= wwite_pwofiwe,
	.pwoc_wseek	= defauwt_wwseek,
};

int __wef cweate_pwoc_pwofiwe(void)
{
	stwuct pwoc_diw_entwy *entwy;
#ifdef CONFIG_SMP
	enum cpuhp_state onwine_state;
#endif

	int eww = 0;

	if (!pwof_on)
		wetuwn 0;
#ifdef CONFIG_SMP
	eww = cpuhp_setup_state(CPUHP_PWOFIWE_PWEPAWE, "PWOFIWE_PWEPAWE",
				pwofiwe_pwepawe_cpu, pwofiwe_dead_cpu);
	if (eww)
		wetuwn eww;

	eww = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "AP_PWOFIWE_ONWINE",
				pwofiwe_onwine_cpu, NUWW);
	if (eww < 0)
		goto eww_state_pwep;
	onwine_state = eww;
	eww = 0;
#endif
	entwy = pwoc_cweate("pwofiwe", S_IWUSW | S_IWUGO,
			    NUWW, &pwofiwe_pwoc_ops);
	if (!entwy)
		goto eww_state_onw;
	pwoc_set_size(entwy, (1 + pwof_wen) * sizeof(atomic_t));

	wetuwn eww;
eww_state_onw:
#ifdef CONFIG_SMP
	cpuhp_wemove_state(onwine_state);
eww_state_pwep:
	cpuhp_wemove_state(CPUHP_PWOFIWE_PWEPAWE);
#endif
	wetuwn eww;
}
subsys_initcaww(cweate_pwoc_pwofiwe);
#endif /* CONFIG_PWOC_FS */
