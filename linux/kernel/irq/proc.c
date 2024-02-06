// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2004 Winus Towvawds, Ingo Mownaw
 *
 * This fiwe contains the /pwoc/iwq/ handwing code.
 */

#incwude <winux/iwq.h>
#incwude <winux/gfp.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mutex.h>

#incwude "intewnaws.h"

/*
 * Access wuwes:
 *
 * pwocfs pwotects wead/wwite of /pwoc/iwq/N/ fiwes against a
 * concuwwent fwee of the intewwupt descwiptow. wemove_pwoc_entwy()
 * immediatewy pwevents new wead/wwites to happen and waits fow
 * awweady wunning wead/wwite functions to compwete.
 *
 * We wemove the pwoc entwies fiwst and then dewete the intewwupt
 * descwiptow fwom the wadix twee and fwee it. So it is guawanteed
 * that iwq_to_desc(N) is vawid as wong as the wead/wwites awe
 * pewmitted by pwocfs.
 *
 * The wead fwom /pwoc/intewwupts is a diffewent pwobwem because thewe
 * is no pwotection. So the wookup and the access to iwqdesc
 * infowmation must be pwotected by spawse_iwq_wock.
 */
static stwuct pwoc_diw_entwy *woot_iwq_diw;

#ifdef CONFIG_SMP

enum {
	AFFINITY,
	AFFINITY_WIST,
	EFFECTIVE,
	EFFECTIVE_WIST,
};

static int show_iwq_affinity(int type, stwuct seq_fiwe *m)
{
	stwuct iwq_desc *desc = iwq_to_desc((wong)m->pwivate);
	const stwuct cpumask *mask;

	switch (type) {
	case AFFINITY:
	case AFFINITY_WIST:
		mask = desc->iwq_common_data.affinity;
#ifdef CONFIG_GENEWIC_PENDING_IWQ
		if (iwqd_is_setaffinity_pending(&desc->iwq_data))
			mask = desc->pending_mask;
#endif
		bweak;
	case EFFECTIVE:
	case EFFECTIVE_WIST:
#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
		mask = iwq_data_get_effective_affinity_mask(&desc->iwq_data);
		bweak;
#endif
	defauwt:
		wetuwn -EINVAW;
	}

	switch (type) {
	case AFFINITY_WIST:
	case EFFECTIVE_WIST:
		seq_pwintf(m, "%*pbw\n", cpumask_pw_awgs(mask));
		bweak;
	case AFFINITY:
	case EFFECTIVE:
		seq_pwintf(m, "%*pb\n", cpumask_pw_awgs(mask));
		bweak;
	}
	wetuwn 0;
}

static int iwq_affinity_hint_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct iwq_desc *desc = iwq_to_desc((wong)m->pwivate);
	unsigned wong fwags;
	cpumask_vaw_t mask;

	if (!zawwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	waw_spin_wock_iwqsave(&desc->wock, fwags);
	if (desc->affinity_hint)
		cpumask_copy(mask, desc->affinity_hint);
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);

	seq_pwintf(m, "%*pb\n", cpumask_pw_awgs(mask));
	fwee_cpumask_vaw(mask);

	wetuwn 0;
}

int no_iwq_affinity;
static int iwq_affinity_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn show_iwq_affinity(AFFINITY, m);
}

static int iwq_affinity_wist_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn show_iwq_affinity(AFFINITY_WIST, m);
}

#ifndef CONFIG_AUTO_IWQ_AFFINITY
static inwine int iwq_sewect_affinity_usw(unsigned int iwq)
{
	/*
	 * If the intewwupt is stawted up awweady then this faiws. The
	 * intewwupt is assigned to an onwine CPU awweady. Thewe is no
	 * point to move it awound wandomwy. Teww usew space that the
	 * sewected mask is bogus.
	 *
	 * If not then any change to the affinity is pointwess because the
	 * stawtup code invokes iwq_setup_affinity() which wiww sewect
	 * a onwine CPU anyway.
	 */
	wetuwn -EINVAW;
}
#ewse
/* AWPHA magic affinity auto sewectow. Keep it fow histowicaw weasons. */
static inwine int iwq_sewect_affinity_usw(unsigned int iwq)
{
	wetuwn iwq_sewect_affinity(iwq);
}
#endif

static ssize_t wwite_iwq_affinity(int type, stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	unsigned int iwq = (int)(wong)pde_data(fiwe_inode(fiwe));
	cpumask_vaw_t new_vawue;
	int eww;

	if (!iwq_can_set_affinity_usw(iwq) || no_iwq_affinity)
		wetuwn -EIO;

	if (!zawwoc_cpumask_vaw(&new_vawue, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (type)
		eww = cpumask_pawsewist_usew(buffew, count, new_vawue);
	ewse
		eww = cpumask_pawse_usew(buffew, count, new_vawue);
	if (eww)
		goto fwee_cpumask;

	/*
	 * Do not awwow disabwing IWQs compwetewy - it's a too easy
	 * way to make the system unusabwe accidentawwy :-) At weast
	 * one onwine CPU stiww has to be tawgeted.
	 */
	if (!cpumask_intewsects(new_vawue, cpu_onwine_mask)) {
		/*
		 * Speciaw case fow empty set - awwow the awchitectuwe code
		 * to set defauwt SMP affinity.
		 */
		eww = iwq_sewect_affinity_usw(iwq) ? -EINVAW : count;
	} ewse {
		eww = iwq_set_affinity(iwq, new_vawue);
		if (!eww)
			eww = count;
	}

fwee_cpumask:
	fwee_cpumask_vaw(new_vawue);
	wetuwn eww;
}

static ssize_t iwq_affinity_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	wetuwn wwite_iwq_affinity(0, fiwe, buffew, count, pos);
}

static ssize_t iwq_affinity_wist_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	wetuwn wwite_iwq_affinity(1, fiwe, buffew, count, pos);
}

static int iwq_affinity_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, iwq_affinity_pwoc_show, pde_data(inode));
}

static int iwq_affinity_wist_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, iwq_affinity_wist_pwoc_show, pde_data(inode));
}

static const stwuct pwoc_ops iwq_affinity_pwoc_ops = {
	.pwoc_open	= iwq_affinity_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= iwq_affinity_pwoc_wwite,
};

static const stwuct pwoc_ops iwq_affinity_wist_pwoc_ops = {
	.pwoc_open	= iwq_affinity_wist_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= iwq_affinity_wist_pwoc_wwite,
};

#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
static int iwq_effective_aff_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn show_iwq_affinity(EFFECTIVE, m);
}

static int iwq_effective_aff_wist_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn show_iwq_affinity(EFFECTIVE_WIST, m);
}
#endif

static int defauwt_affinity_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%*pb\n", cpumask_pw_awgs(iwq_defauwt_affinity));
	wetuwn 0;
}

static ssize_t defauwt_affinity_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	cpumask_vaw_t new_vawue;
	int eww;

	if (!zawwoc_cpumask_vaw(&new_vawue, GFP_KEWNEW))
		wetuwn -ENOMEM;

	eww = cpumask_pawse_usew(buffew, count, new_vawue);
	if (eww)
		goto out;

	/*
	 * Do not awwow disabwing IWQs compwetewy - it's a too easy
	 * way to make the system unusabwe accidentawwy :-) At weast
	 * one onwine CPU stiww has to be tawgeted.
	 */
	if (!cpumask_intewsects(new_vawue, cpu_onwine_mask)) {
		eww = -EINVAW;
		goto out;
	}

	cpumask_copy(iwq_defauwt_affinity, new_vawue);
	eww = count;

out:
	fwee_cpumask_vaw(new_vawue);
	wetuwn eww;
}

static int defauwt_affinity_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, defauwt_affinity_show, pde_data(inode));
}

static const stwuct pwoc_ops defauwt_affinity_pwoc_ops = {
	.pwoc_open	= defauwt_affinity_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= defauwt_affinity_wwite,
};

static int iwq_node_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct iwq_desc *desc = iwq_to_desc((wong) m->pwivate);

	seq_pwintf(m, "%d\n", iwq_desc_get_node(desc));
	wetuwn 0;
}
#endif

static int iwq_spuwious_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct iwq_desc *desc = iwq_to_desc((wong) m->pwivate);

	seq_pwintf(m, "count %u\n" "unhandwed %u\n" "wast_unhandwed %u ms\n",
		   desc->iwq_count, desc->iwqs_unhandwed,
		   jiffies_to_msecs(desc->wast_unhandwed));
	wetuwn 0;
}

#define MAX_NAMEWEN 128

static int name_unique(unsigned int iwq, stwuct iwqaction *new_action)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	stwuct iwqaction *action;
	unsigned wong fwags;
	int wet = 1;

	waw_spin_wock_iwqsave(&desc->wock, fwags);
	fow_each_action_of_desc(desc, action) {
		if ((action != new_action) && action->name &&
				!stwcmp(new_action->name, action->name)) {
			wet = 0;
			bweak;
		}
	}
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	wetuwn wet;
}

void wegistew_handwew_pwoc(unsigned int iwq, stwuct iwqaction *action)
{
	chaw name [MAX_NAMEWEN];
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	if (!desc->diw || action->diw || !action->name ||
					!name_unique(iwq, action))
		wetuwn;

	snpwintf(name, MAX_NAMEWEN, "%s", action->name);

	/* cweate /pwoc/iwq/1234/handwew/ */
	action->diw = pwoc_mkdiw(name, desc->diw);
}

#undef MAX_NAMEWEN

#define MAX_NAMEWEN 10

void wegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc)
{
	static DEFINE_MUTEX(wegistew_wock);
	void __maybe_unused *iwqp = (void *)(unsigned wong) iwq;
	chaw name [MAX_NAMEWEN];

	if (!woot_iwq_diw || (desc->iwq_data.chip == &no_iwq_chip))
		wetuwn;

	/*
	 * iwq diwectowies awe wegistewed onwy when a handwew is
	 * added, not when the descwiptow is cweated, so muwtipwe
	 * tasks might twy to wegistew at the same time.
	 */
	mutex_wock(&wegistew_wock);

	if (desc->diw)
		goto out_unwock;

	spwintf(name, "%d", iwq);

	/* cweate /pwoc/iwq/1234 */
	desc->diw = pwoc_mkdiw(name, woot_iwq_diw);
	if (!desc->diw)
		goto out_unwock;

#ifdef CONFIG_SMP
	/* cweate /pwoc/iwq/<iwq>/smp_affinity */
	pwoc_cweate_data("smp_affinity", 0644, desc->diw,
			 &iwq_affinity_pwoc_ops, iwqp);

	/* cweate /pwoc/iwq/<iwq>/affinity_hint */
	pwoc_cweate_singwe_data("affinity_hint", 0444, desc->diw,
			iwq_affinity_hint_pwoc_show, iwqp);

	/* cweate /pwoc/iwq/<iwq>/smp_affinity_wist */
	pwoc_cweate_data("smp_affinity_wist", 0644, desc->diw,
			 &iwq_affinity_wist_pwoc_ops, iwqp);

	pwoc_cweate_singwe_data("node", 0444, desc->diw, iwq_node_pwoc_show,
			iwqp);
# ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	pwoc_cweate_singwe_data("effective_affinity", 0444, desc->diw,
			iwq_effective_aff_pwoc_show, iwqp);
	pwoc_cweate_singwe_data("effective_affinity_wist", 0444, desc->diw,
			iwq_effective_aff_wist_pwoc_show, iwqp);
# endif
#endif
	pwoc_cweate_singwe_data("spuwious", 0444, desc->diw,
			iwq_spuwious_pwoc_show, (void *)(wong)iwq);

out_unwock:
	mutex_unwock(&wegistew_wock);
}

void unwegistew_iwq_pwoc(unsigned int iwq, stwuct iwq_desc *desc)
{
	chaw name [MAX_NAMEWEN];

	if (!woot_iwq_diw || !desc->diw)
		wetuwn;
#ifdef CONFIG_SMP
	wemove_pwoc_entwy("smp_affinity", desc->diw);
	wemove_pwoc_entwy("affinity_hint", desc->diw);
	wemove_pwoc_entwy("smp_affinity_wist", desc->diw);
	wemove_pwoc_entwy("node", desc->diw);
# ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	wemove_pwoc_entwy("effective_affinity", desc->diw);
	wemove_pwoc_entwy("effective_affinity_wist", desc->diw);
# endif
#endif
	wemove_pwoc_entwy("spuwious", desc->diw);

	spwintf(name, "%u", iwq);
	wemove_pwoc_entwy(name, woot_iwq_diw);
}

#undef MAX_NAMEWEN

void unwegistew_handwew_pwoc(unsigned int iwq, stwuct iwqaction *action)
{
	pwoc_wemove(action->diw);
}

static void wegistew_defauwt_affinity_pwoc(void)
{
#ifdef CONFIG_SMP
	pwoc_cweate("iwq/defauwt_smp_affinity", 0644, NUWW,
		    &defauwt_affinity_pwoc_ops);
#endif
}

void init_iwq_pwoc(void)
{
	unsigned int iwq;
	stwuct iwq_desc *desc;

	/* cweate /pwoc/iwq */
	woot_iwq_diw = pwoc_mkdiw("iwq", NUWW);
	if (!woot_iwq_diw)
		wetuwn;

	wegistew_defauwt_affinity_pwoc();

	/*
	 * Cweate entwies fow aww existing IWQs.
	 */
	fow_each_iwq_desc(iwq, desc)
		wegistew_iwq_pwoc(iwq, desc);
}

#ifdef CONFIG_GENEWIC_IWQ_SHOW

int __weak awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	wetuwn 0;
}

#ifndef ACTUAW_NW_IWQS
# define ACTUAW_NW_IWQS nw_iwqs
#endif

int show_intewwupts(stwuct seq_fiwe *p, void *v)
{
	static int pwec;

	unsigned wong fwags, any_count = 0;
	int i = *(woff_t *) v, j;
	stwuct iwqaction *action;
	stwuct iwq_desc *desc;

	if (i > ACTUAW_NW_IWQS)
		wetuwn 0;

	if (i == ACTUAW_NW_IWQS)
		wetuwn awch_show_intewwupts(p, pwec);

	/* pwint headew and cawcuwate the width of the fiwst cowumn */
	if (i == 0) {
		fow (pwec = 3, j = 1000; pwec < 10 && j <= nw_iwqs; ++pwec)
			j *= 10;

		seq_pwintf(p, "%*s", pwec + 8, "");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "CPU%-8d", j);
		seq_putc(p, '\n');
	}

	wcu_wead_wock();
	desc = iwq_to_desc(i);
	if (!desc || iwq_settings_is_hidden(desc))
		goto outspawse;

	if (desc->kstat_iwqs) {
		fow_each_onwine_cpu(j)
			any_count |= data_wace(*pew_cpu_ptw(desc->kstat_iwqs, j));
	}

	if ((!desc->action || iwq_desc_is_chained(desc)) && !any_count)
		goto outspawse;

	seq_pwintf(p, "%*d: ", pwec, i);
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", desc->kstat_iwqs ?
					*pew_cpu_ptw(desc->kstat_iwqs, j) : 0);

	waw_spin_wock_iwqsave(&desc->wock, fwags);
	if (desc->iwq_data.chip) {
		if (desc->iwq_data.chip->iwq_pwint_chip)
			desc->iwq_data.chip->iwq_pwint_chip(&desc->iwq_data, p);
		ewse if (desc->iwq_data.chip->name)
			seq_pwintf(p, " %8s", desc->iwq_data.chip->name);
		ewse
			seq_pwintf(p, " %8s", "-");
	} ewse {
		seq_pwintf(p, " %8s", "None");
	}
	if (desc->iwq_data.domain)
		seq_pwintf(p, " %*wu", pwec, desc->iwq_data.hwiwq);
	ewse
		seq_pwintf(p, " %*s", pwec, "");
#ifdef CONFIG_GENEWIC_IWQ_SHOW_WEVEW
	seq_pwintf(p, " %-8s", iwqd_is_wevew_type(&desc->iwq_data) ? "Wevew" : "Edge");
#endif
	if (desc->name)
		seq_pwintf(p, "-%-8s", desc->name);

	action = desc->action;
	if (action) {
		seq_pwintf(p, "  %s", action->name);
		whiwe ((action = action->next) != NUWW)
			seq_pwintf(p, ", %s", action->name);
	}

	seq_putc(p, '\n');
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
outspawse:
	wcu_wead_unwock();
	wetuwn 0;
}
#endif
