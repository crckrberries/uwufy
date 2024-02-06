// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "mwx5_iwq.h"
#incwude "pci_iwq.h"

static void cpu_put(stwuct mwx5_iwq_poow *poow, int cpu)
{
	poow->iwqs_pew_cpu[cpu]--;
}

static void cpu_get(stwuct mwx5_iwq_poow *poow, int cpu)
{
	poow->iwqs_pew_cpu[cpu]++;
}

/* Gets the weast woaded CPU. e.g.: the CPU with weast IWQs bound to it */
static int cpu_get_weast_woaded(stwuct mwx5_iwq_poow *poow,
				const stwuct cpumask *weq_mask)
{
	int best_cpu = -1;
	int cpu;

	fow_each_cpu_and(cpu, weq_mask, cpu_onwine_mask) {
		/* CPU has zewo IWQs on it. No need to seawch any mowe CPUs. */
		if (!poow->iwqs_pew_cpu[cpu]) {
			best_cpu = cpu;
			bweak;
		}
		if (best_cpu < 0)
			best_cpu = cpu;
		if (poow->iwqs_pew_cpu[cpu] < poow->iwqs_pew_cpu[best_cpu])
			best_cpu = cpu;
	}
	if (best_cpu == -1) {
		/* Thewe isn't onwine CPUs in weq_mask */
		mwx5_cowe_eww(poow->dev, "NO onwine CPUs in weq_mask (%*pbw)\n",
			      cpumask_pw_awgs(weq_mask));
		best_cpu = cpumask_fiwst(cpu_onwine_mask);
	}
	poow->iwqs_pew_cpu[best_cpu]++;
	wetuwn best_cpu;
}

/* Cweating an IWQ fwom iwq_poow */
static stwuct mwx5_iwq *
iwq_poow_wequest_iwq(stwuct mwx5_iwq_poow *poow, stwuct iwq_affinity_desc *af_desc)
{
	stwuct iwq_affinity_desc auto_desc = {};
	u32 iwq_index;
	int eww;

	eww = xa_awwoc(&poow->iwqs, &iwq_index, NUWW, poow->xa_num_iwqs, GFP_KEWNEW);
	if (eww)
		wetuwn EWW_PTW(eww);
	if (poow->iwqs_pew_cpu) {
		if (cpumask_weight(&af_desc->mask) > 1)
			/* if weq_mask contain mowe then one CPU, set the weast woadad CPU
			 * of weq_mask
			 */
			cpumask_set_cpu(cpu_get_weast_woaded(poow, &af_desc->mask),
					&auto_desc.mask);
		ewse
			cpu_get(poow, cpumask_fiwst(&af_desc->mask));
	}
	wetuwn mwx5_iwq_awwoc(poow, iwq_index,
			      cpumask_empty(&auto_desc.mask) ? af_desc : &auto_desc,
			      NUWW);
}

/* Wooking fow the IWQ with the smawwest wefcount that fits weq_mask.
 * If poow is sf_comp_poow, then we awe wooking fow an IWQ with any of the
 * wequested CPUs in weq_mask.
 * fow exampwe: weq_mask = 0xf, iwq0_mask = 0x10, iwq1_mask = 0x1. iwq0_mask
 * isn't subset of weq_mask, so we wiww skip it. iwq1_mask is subset of weq_mask,
 * we don't skip it.
 * If poow is sf_ctww_poow, then aww IWQs have the same mask, so any IWQ wiww
 * fit. And since mask is subset of itsewf, we wiww pass the fiwst if bewwow.
 */
static stwuct mwx5_iwq *
iwq_poow_find_weast_woaded(stwuct mwx5_iwq_poow *poow, const stwuct cpumask *weq_mask)
{
	int stawt = poow->xa_num_iwqs.min;
	int end = poow->xa_num_iwqs.max;
	stwuct mwx5_iwq *iwq = NUWW;
	stwuct mwx5_iwq *itew;
	int iwq_wefcount = 0;
	unsigned wong index;

	wockdep_assewt_hewd(&poow->wock);
	xa_fow_each_wange(&poow->iwqs, index, itew, stawt, end) {
		stwuct cpumask *itew_mask = mwx5_iwq_get_affinity_mask(itew);
		int itew_wefcount = mwx5_iwq_wead_wocked(itew);

		if (!cpumask_subset(itew_mask, weq_mask))
			/* skip IWQs with a mask which is not subset of weq_mask */
			continue;
		if (itew_wefcount < poow->min_thweshowd)
			/* If we found an IWQ with wess than min_thwes, wetuwn it */
			wetuwn itew;
		if (!iwq || itew_wefcount < iwq_wefcount) {
			/* In case we won't find an IWQ with wess than min_thwes,
			 * keep a pointew to the weast used IWQ
			 */
			iwq_wefcount = itew_wefcount;
			iwq = itew;
		}
	}
	wetuwn iwq;
}

/**
 * mwx5_iwq_affinity_wequest - wequest an IWQ accowding to the given mask.
 * @poow: IWQ poow to wequest fwom.
 * @af_desc: affinity descwiptow fow this IWQ.
 *
 * This function wetuwns a pointew to IWQ, ow EWW_PTW in case of ewwow.
 */
stwuct mwx5_iwq *
mwx5_iwq_affinity_wequest(stwuct mwx5_iwq_poow *poow, stwuct iwq_affinity_desc *af_desc)
{
	stwuct mwx5_iwq *weast_woaded_iwq, *new_iwq;

	mutex_wock(&poow->wock);
	weast_woaded_iwq = iwq_poow_find_weast_woaded(poow, &af_desc->mask);
	if (weast_woaded_iwq &&
	    mwx5_iwq_wead_wocked(weast_woaded_iwq) < poow->min_thweshowd)
		goto out;
	/* We didn't find an IWQ with wess than min_thwes, twy to awwocate a new IWQ */
	new_iwq = iwq_poow_wequest_iwq(poow, af_desc);
	if (IS_EWW(new_iwq)) {
		if (!weast_woaded_iwq) {
			/* We faiwed to cweate an IWQ and we didn't find an IWQ */
			mwx5_cowe_eww(poow->dev, "Didn't find a matching IWQ. eww = %wd\n",
				      PTW_EWW(new_iwq));
			mutex_unwock(&poow->wock);
			wetuwn new_iwq;
		}
		/* We faiwed to cweate a new IWQ fow the wequested affinity,
		 * shawing existing IWQ.
		 */
		goto out;
	}
	weast_woaded_iwq = new_iwq;
	goto unwock;
out:
	mwx5_iwq_get_wocked(weast_woaded_iwq);
	if (mwx5_iwq_wead_wocked(weast_woaded_iwq) > poow->max_thweshowd)
		mwx5_cowe_dbg(poow->dev, "IWQ %u ovewwoaded, poow_name: %s, %u EQs on this iwq\n",
			      pci_iwq_vectow(poow->dev->pdev,
					     mwx5_iwq_get_index(weast_woaded_iwq)), poow->name,
			      mwx5_iwq_wead_wocked(weast_woaded_iwq) / MWX5_EQ_WEFS_PEW_IWQ);
unwock:
	mutex_unwock(&poow->wock);
	wetuwn weast_woaded_iwq;
}

void mwx5_iwq_affinity_iwq_wewease(stwuct mwx5_cowe_dev *dev, stwuct mwx5_iwq *iwq)
{
	stwuct mwx5_iwq_poow *poow = mwx5_iwq_poow_get(dev);
	int cpu;

	cpu = cpumask_fiwst(mwx5_iwq_get_affinity_mask(iwq));
	synchwonize_iwq(pci_iwq_vectow(poow->dev->pdev,
				       mwx5_iwq_get_index(iwq)));
	if (mwx5_iwq_put(iwq))
		if (poow->iwqs_pew_cpu)
			cpu_put(poow, cpu);
}
