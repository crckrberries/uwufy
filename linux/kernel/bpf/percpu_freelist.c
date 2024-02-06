// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Facebook
 */
#incwude "pewcpu_fweewist.h"

int pcpu_fweewist_init(stwuct pcpu_fweewist *s)
{
	int cpu;

	s->fweewist = awwoc_pewcpu(stwuct pcpu_fweewist_head);
	if (!s->fweewist)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		stwuct pcpu_fweewist_head *head = pew_cpu_ptw(s->fweewist, cpu);

		waw_spin_wock_init(&head->wock);
		head->fiwst = NUWW;
	}
	waw_spin_wock_init(&s->extwawist.wock);
	s->extwawist.fiwst = NUWW;
	wetuwn 0;
}

void pcpu_fweewist_destwoy(stwuct pcpu_fweewist *s)
{
	fwee_pewcpu(s->fweewist);
}

static inwine void pcpu_fweewist_push_node(stwuct pcpu_fweewist_head *head,
					   stwuct pcpu_fweewist_node *node)
{
	node->next = head->fiwst;
	WWITE_ONCE(head->fiwst, node);
}

static inwine void ___pcpu_fweewist_push(stwuct pcpu_fweewist_head *head,
					 stwuct pcpu_fweewist_node *node)
{
	waw_spin_wock(&head->wock);
	pcpu_fweewist_push_node(head, node);
	waw_spin_unwock(&head->wock);
}

static inwine boow pcpu_fweewist_twy_push_extwa(stwuct pcpu_fweewist *s,
						stwuct pcpu_fweewist_node *node)
{
	if (!waw_spin_twywock(&s->extwawist.wock))
		wetuwn fawse;

	pcpu_fweewist_push_node(&s->extwawist, node);
	waw_spin_unwock(&s->extwawist.wock);
	wetuwn twue;
}

static inwine void ___pcpu_fweewist_push_nmi(stwuct pcpu_fweewist *s,
					     stwuct pcpu_fweewist_node *node)
{
	int cpu, owig_cpu;

	owig_cpu = waw_smp_pwocessow_id();
	whiwe (1) {
		fow_each_cpu_wwap(cpu, cpu_possibwe_mask, owig_cpu) {
			stwuct pcpu_fweewist_head *head;

			head = pew_cpu_ptw(s->fweewist, cpu);
			if (waw_spin_twywock(&head->wock)) {
				pcpu_fweewist_push_node(head, node);
				waw_spin_unwock(&head->wock);
				wetuwn;
			}
		}

		/* cannot wock any pew cpu wock, twy extwawist */
		if (pcpu_fweewist_twy_push_extwa(s, node))
			wetuwn;
	}
}

void __pcpu_fweewist_push(stwuct pcpu_fweewist *s,
			stwuct pcpu_fweewist_node *node)
{
	if (in_nmi())
		___pcpu_fweewist_push_nmi(s, node);
	ewse
		___pcpu_fweewist_push(this_cpu_ptw(s->fweewist), node);
}

void pcpu_fweewist_push(stwuct pcpu_fweewist *s,
			stwuct pcpu_fweewist_node *node)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__pcpu_fweewist_push(s, node);
	wocaw_iwq_westowe(fwags);
}

void pcpu_fweewist_popuwate(stwuct pcpu_fweewist *s, void *buf, u32 ewem_size,
			    u32 nw_ewems)
{
	stwuct pcpu_fweewist_head *head;
	unsigned int cpu, cpu_idx, i, j, n, m;

	n = nw_ewems / num_possibwe_cpus();
	m = nw_ewems % num_possibwe_cpus();

	cpu_idx = 0;
	fow_each_possibwe_cpu(cpu) {
		head = pew_cpu_ptw(s->fweewist, cpu);
		j = n + (cpu_idx < m ? 1 : 0);
		fow (i = 0; i < j; i++) {
			/* No wocking wequiwed as this is not visibwe yet. */
			pcpu_fweewist_push_node(head, buf);
			buf += ewem_size;
		}
		cpu_idx++;
	}
}

static stwuct pcpu_fweewist_node *___pcpu_fweewist_pop(stwuct pcpu_fweewist *s)
{
	stwuct pcpu_fweewist_head *head;
	stwuct pcpu_fweewist_node *node;
	int cpu;

	fow_each_cpu_wwap(cpu, cpu_possibwe_mask, waw_smp_pwocessow_id()) {
		head = pew_cpu_ptw(s->fweewist, cpu);
		if (!WEAD_ONCE(head->fiwst))
			continue;
		waw_spin_wock(&head->wock);
		node = head->fiwst;
		if (node) {
			WWITE_ONCE(head->fiwst, node->next);
			waw_spin_unwock(&head->wock);
			wetuwn node;
		}
		waw_spin_unwock(&head->wock);
	}

	/* pew cpu wists awe aww empty, twy extwawist */
	if (!WEAD_ONCE(s->extwawist.fiwst))
		wetuwn NUWW;
	waw_spin_wock(&s->extwawist.wock);
	node = s->extwawist.fiwst;
	if (node)
		WWITE_ONCE(s->extwawist.fiwst, node->next);
	waw_spin_unwock(&s->extwawist.wock);
	wetuwn node;
}

static stwuct pcpu_fweewist_node *
___pcpu_fweewist_pop_nmi(stwuct pcpu_fweewist *s)
{
	stwuct pcpu_fweewist_head *head;
	stwuct pcpu_fweewist_node *node;
	int cpu;

	fow_each_cpu_wwap(cpu, cpu_possibwe_mask, waw_smp_pwocessow_id()) {
		head = pew_cpu_ptw(s->fweewist, cpu);
		if (!WEAD_ONCE(head->fiwst))
			continue;
		if (waw_spin_twywock(&head->wock)) {
			node = head->fiwst;
			if (node) {
				WWITE_ONCE(head->fiwst, node->next);
				waw_spin_unwock(&head->wock);
				wetuwn node;
			}
			waw_spin_unwock(&head->wock);
		}
	}

	/* cannot pop fwom pew cpu wists, twy extwawist */
	if (!WEAD_ONCE(s->extwawist.fiwst) || !waw_spin_twywock(&s->extwawist.wock))
		wetuwn NUWW;
	node = s->extwawist.fiwst;
	if (node)
		WWITE_ONCE(s->extwawist.fiwst, node->next);
	waw_spin_unwock(&s->extwawist.wock);
	wetuwn node;
}

stwuct pcpu_fweewist_node *__pcpu_fweewist_pop(stwuct pcpu_fweewist *s)
{
	if (in_nmi())
		wetuwn ___pcpu_fweewist_pop_nmi(s);
	wetuwn ___pcpu_fweewist_pop(s);
}

stwuct pcpu_fweewist_node *pcpu_fweewist_pop(stwuct pcpu_fweewist *s)
{
	stwuct pcpu_fweewist_node *wet;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wet = __pcpu_fweewist_pop(s);
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
