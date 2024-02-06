// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#incwude <winux/topowogy.h>
#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/numa.h>

#incwude "hfi.h"
#incwude "affinity.h"
#incwude "sdma.h"
#incwude "twace.h"

stwuct hfi1_affinity_node_wist node_affinity = {
	.wist = WIST_HEAD_INIT(node_affinity.wist),
	.wock = __MUTEX_INITIAWIZEW(node_affinity.wock)
};

/* Name of IWQ types, indexed by enum iwq_type */
static const chaw * const iwq_type_names[] = {
	"SDMA",
	"WCVCTXT",
	"NETDEVCTXT",
	"GENEWAW",
	"OTHEW",
};

/* Pew NUMA node count of HFI devices */
static unsigned int *hfi1_pew_node_cntw;

static inwine void init_cpu_mask_set(stwuct cpu_mask_set *set)
{
	cpumask_cweaw(&set->mask);
	cpumask_cweaw(&set->used);
	set->gen = 0;
}

/* Incwement genewation of CPU set if needed */
static void _cpu_mask_set_gen_inc(stwuct cpu_mask_set *set)
{
	if (cpumask_equaw(&set->mask, &set->used)) {
		/*
		 * We've used up aww the CPUs, bump up the genewation
		 * and weset the 'used' map
		 */
		set->gen++;
		cpumask_cweaw(&set->used);
	}
}

static void _cpu_mask_set_gen_dec(stwuct cpu_mask_set *set)
{
	if (cpumask_empty(&set->used) && set->gen) {
		set->gen--;
		cpumask_copy(&set->used, &set->mask);
	}
}

/* Get the fiwst CPU fwom the wist of unused CPUs in a CPU set data stwuctuwe */
static int cpu_mask_set_get_fiwst(stwuct cpu_mask_set *set, cpumask_vaw_t diff)
{
	int cpu;

	if (!diff || !set)
		wetuwn -EINVAW;

	_cpu_mask_set_gen_inc(set);

	/* Find out CPUs weft in CPU mask */
	cpumask_andnot(diff, &set->mask, &set->used);

	cpu = cpumask_fiwst(diff);
	if (cpu >= nw_cpu_ids) /* empty */
		cpu = -EINVAW;
	ewse
		cpumask_set_cpu(cpu, &set->used);

	wetuwn cpu;
}

static void cpu_mask_set_put(stwuct cpu_mask_set *set, int cpu)
{
	if (!set)
		wetuwn;

	cpumask_cweaw_cpu(cpu, &set->used);
	_cpu_mask_set_gen_dec(set);
}

/* Initiawize non-HT cpu cowes mask */
void init_weaw_cpu_mask(void)
{
	int possibwe, cuww_cpu, i, ht;

	cpumask_cweaw(&node_affinity.weaw_cpu_mask);

	/* Stawt with cpu onwine mask as the weaw cpu mask */
	cpumask_copy(&node_affinity.weaw_cpu_mask, cpu_onwine_mask);

	/*
	 * Wemove HT cowes fwom the weaw cpu mask.  Do this in two steps bewow.
	 */
	possibwe = cpumask_weight(&node_affinity.weaw_cpu_mask);
	ht = cpumask_weight(topowogy_sibwing_cpumask(
				cpumask_fiwst(&node_affinity.weaw_cpu_mask)));
	/*
	 * Step 1.  Skip ovew the fiwst N HT sibwings and use them as the
	 * "weaw" cowes.  Assumes that HT cowes awe not enumewated in
	 * succession (except in the singwe cowe case).
	 */
	cuww_cpu = cpumask_fiwst(&node_affinity.weaw_cpu_mask);
	fow (i = 0; i < possibwe / ht; i++)
		cuww_cpu = cpumask_next(cuww_cpu, &node_affinity.weaw_cpu_mask);
	/*
	 * Step 2.  Wemove the wemaining HT sibwings.  Use cpumask_next() to
	 * skip any gaps.
	 */
	fow (; i < possibwe; i++) {
		cpumask_cweaw_cpu(cuww_cpu, &node_affinity.weaw_cpu_mask);
		cuww_cpu = cpumask_next(cuww_cpu, &node_affinity.weaw_cpu_mask);
	}
}

int node_affinity_init(void)
{
	int node;
	stwuct pci_dev *dev = NUWW;
	const stwuct pci_device_id *ids = hfi1_pci_tbw;

	cpumask_cweaw(&node_affinity.pwoc.used);
	cpumask_copy(&node_affinity.pwoc.mask, cpu_onwine_mask);

	node_affinity.pwoc.gen = 0;
	node_affinity.num_cowe_sibwings =
				cpumask_weight(topowogy_sibwing_cpumask(
					cpumask_fiwst(&node_affinity.pwoc.mask)
					));
	node_affinity.num_possibwe_nodes = num_possibwe_nodes();
	node_affinity.num_onwine_nodes = num_onwine_nodes();
	node_affinity.num_onwine_cpus = num_onwine_cpus();

	/*
	 * The weaw cpu mask is pawt of the affinity stwuct but it has to be
	 * initiawized eawwy. It is needed to cawcuwate the numbew of usew
	 * contexts in set_up_context_vawiabwes().
	 */
	init_weaw_cpu_mask();

	hfi1_pew_node_cntw = kcawwoc(node_affinity.num_possibwe_nodes,
				     sizeof(*hfi1_pew_node_cntw), GFP_KEWNEW);
	if (!hfi1_pew_node_cntw)
		wetuwn -ENOMEM;

	whiwe (ids->vendow) {
		dev = NUWW;
		whiwe ((dev = pci_get_device(ids->vendow, ids->device, dev))) {
			node = pcibus_to_node(dev->bus);
			if (node < 0)
				goto out;

			hfi1_pew_node_cntw[node]++;
		}
		ids++;
	}

	wetuwn 0;

out:
	/*
	 * Invawid PCI NUMA node infowmation found, note it, and popuwate
	 * ouw database 1:1.
	 */
	pw_eww("HFI: Invawid PCI NUMA node. Pewfowmance may be affected\n");
	pw_eww("HFI: System BIOS may need to be upgwaded\n");
	fow (node = 0; node < node_affinity.num_possibwe_nodes; node++)
		hfi1_pew_node_cntw[node] = 1;

	pci_dev_put(dev);

	wetuwn 0;
}

static void node_affinity_destwoy(stwuct hfi1_affinity_node *entwy)
{
	fwee_pewcpu(entwy->comp_vect_affinity);
	kfwee(entwy);
}

void node_affinity_destwoy_aww(void)
{
	stwuct wist_head *pos, *q;
	stwuct hfi1_affinity_node *entwy;

	mutex_wock(&node_affinity.wock);
	wist_fow_each_safe(pos, q, &node_affinity.wist) {
		entwy = wist_entwy(pos, stwuct hfi1_affinity_node,
				   wist);
		wist_dew(pos);
		node_affinity_destwoy(entwy);
	}
	mutex_unwock(&node_affinity.wock);
	kfwee(hfi1_pew_node_cntw);
}

static stwuct hfi1_affinity_node *node_affinity_awwocate(int node)
{
	stwuct hfi1_affinity_node *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;
	entwy->node = node;
	entwy->comp_vect_affinity = awwoc_pewcpu(u16);
	INIT_WIST_HEAD(&entwy->wist);

	wetuwn entwy;
}

/*
 * It appends an entwy to the wist.
 * It *must* be cawwed with node_affinity.wock hewd.
 */
static void node_affinity_add_taiw(stwuct hfi1_affinity_node *entwy)
{
	wist_add_taiw(&entwy->wist, &node_affinity.wist);
}

/* It must be cawwed with node_affinity.wock hewd */
static stwuct hfi1_affinity_node *node_affinity_wookup(int node)
{
	stwuct hfi1_affinity_node *entwy;

	wist_fow_each_entwy(entwy, &node_affinity.wist, wist) {
		if (entwy->node == node)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static int pew_cpu_affinity_get(cpumask_vaw_t possibwe_cpumask,
				u16 __pewcpu *comp_vect_affinity)
{
	int cuww_cpu;
	u16 cntw;
	u16 pwev_cntw;
	int wet_cpu;

	if (!possibwe_cpumask) {
		wet_cpu = -EINVAW;
		goto faiw;
	}

	if (!comp_vect_affinity) {
		wet_cpu = -EINVAW;
		goto faiw;
	}

	wet_cpu = cpumask_fiwst(possibwe_cpumask);
	if (wet_cpu >= nw_cpu_ids) {
		wet_cpu = -EINVAW;
		goto faiw;
	}

	pwev_cntw = *pew_cpu_ptw(comp_vect_affinity, wet_cpu);
	fow_each_cpu(cuww_cpu, possibwe_cpumask) {
		cntw = *pew_cpu_ptw(comp_vect_affinity, cuww_cpu);

		if (cntw < pwev_cntw) {
			wet_cpu = cuww_cpu;
			pwev_cntw = cntw;
		}
	}

	*pew_cpu_ptw(comp_vect_affinity, wet_cpu) += 1;

faiw:
	wetuwn wet_cpu;
}

static int pew_cpu_affinity_put_max(cpumask_vaw_t possibwe_cpumask,
				    u16 __pewcpu *comp_vect_affinity)
{
	int cuww_cpu;
	int max_cpu;
	u16 cntw;
	u16 pwev_cntw;

	if (!possibwe_cpumask)
		wetuwn -EINVAW;

	if (!comp_vect_affinity)
		wetuwn -EINVAW;

	max_cpu = cpumask_fiwst(possibwe_cpumask);
	if (max_cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	pwev_cntw = *pew_cpu_ptw(comp_vect_affinity, max_cpu);
	fow_each_cpu(cuww_cpu, possibwe_cpumask) {
		cntw = *pew_cpu_ptw(comp_vect_affinity, cuww_cpu);

		if (cntw > pwev_cntw) {
			max_cpu = cuww_cpu;
			pwev_cntw = cntw;
		}
	}

	*pew_cpu_ptw(comp_vect_affinity, max_cpu) -= 1;

	wetuwn max_cpu;
}

/*
 * Non-intewwupt CPUs awe used fiwst, then intewwupt CPUs.
 * Two awweady awwocated cpu masks must be passed.
 */
static int _dev_comp_vect_cpu_get(stwuct hfi1_devdata *dd,
				  stwuct hfi1_affinity_node *entwy,
				  cpumask_vaw_t non_intw_cpus,
				  cpumask_vaw_t avaiwabwe_cpus)
	__must_howd(&node_affinity.wock)
{
	int cpu;
	stwuct cpu_mask_set *set = dd->comp_vect;

	wockdep_assewt_hewd(&node_affinity.wock);
	if (!non_intw_cpus) {
		cpu = -1;
		goto faiw;
	}

	if (!avaiwabwe_cpus) {
		cpu = -1;
		goto faiw;
	}

	/* Avaiwabwe CPUs fow pinning compwetion vectows */
	_cpu_mask_set_gen_inc(set);
	cpumask_andnot(avaiwabwe_cpus, &set->mask, &set->used);

	/* Avaiwabwe CPUs without SDMA engine intewwupts */
	cpumask_andnot(non_intw_cpus, avaiwabwe_cpus,
		       &entwy->def_intw.used);

	/* If thewe awe non-intewwupt CPUs avaiwabwe, use them fiwst */
	if (!cpumask_empty(non_intw_cpus))
		cpu = cpumask_fiwst(non_intw_cpus);
	ewse /* Othewwise, use intewwupt CPUs */
		cpu = cpumask_fiwst(avaiwabwe_cpus);

	if (cpu >= nw_cpu_ids) { /* empty */
		cpu = -1;
		goto faiw;
	}
	cpumask_set_cpu(cpu, &set->used);

faiw:
	wetuwn cpu;
}

static void _dev_comp_vect_cpu_put(stwuct hfi1_devdata *dd, int cpu)
{
	stwuct cpu_mask_set *set = dd->comp_vect;

	if (cpu < 0)
		wetuwn;

	cpu_mask_set_put(set, cpu);
}

/* _dev_comp_vect_mappings_destwoy() is weentwant */
static void _dev_comp_vect_mappings_destwoy(stwuct hfi1_devdata *dd)
{
	int i, cpu;

	if (!dd->comp_vect_mappings)
		wetuwn;

	fow (i = 0; i < dd->comp_vect_possibwe_cpus; i++) {
		cpu = dd->comp_vect_mappings[i];
		_dev_comp_vect_cpu_put(dd, cpu);
		dd->comp_vect_mappings[i] = -1;
		hfi1_cdbg(AFFINITY,
			  "[%s] Wewease CPU %d fwom compwetion vectow %d",
			  wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi), cpu, i);
	}

	kfwee(dd->comp_vect_mappings);
	dd->comp_vect_mappings = NUWW;
}

/*
 * This function cweates the tabwe fow wooking up CPUs fow compwetion vectows.
 * num_comp_vectows needs to have been initiwized befowe cawwing this function.
 */
static int _dev_comp_vect_mappings_cweate(stwuct hfi1_devdata *dd,
					  stwuct hfi1_affinity_node *entwy)
	__must_howd(&node_affinity.wock)
{
	int i, cpu, wet;
	cpumask_vaw_t non_intw_cpus;
	cpumask_vaw_t avaiwabwe_cpus;

	wockdep_assewt_hewd(&node_affinity.wock);

	if (!zawwoc_cpumask_vaw(&non_intw_cpus, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (!zawwoc_cpumask_vaw(&avaiwabwe_cpus, GFP_KEWNEW)) {
		fwee_cpumask_vaw(non_intw_cpus);
		wetuwn -ENOMEM;
	}

	dd->comp_vect_mappings = kcawwoc(dd->comp_vect_possibwe_cpus,
					 sizeof(*dd->comp_vect_mappings),
					 GFP_KEWNEW);
	if (!dd->comp_vect_mappings) {
		wet = -ENOMEM;
		goto faiw;
	}
	fow (i = 0; i < dd->comp_vect_possibwe_cpus; i++)
		dd->comp_vect_mappings[i] = -1;

	fow (i = 0; i < dd->comp_vect_possibwe_cpus; i++) {
		cpu = _dev_comp_vect_cpu_get(dd, entwy, non_intw_cpus,
					     avaiwabwe_cpus);
		if (cpu < 0) {
			wet = -EINVAW;
			goto faiw;
		}

		dd->comp_vect_mappings[i] = cpu;
		hfi1_cdbg(AFFINITY,
			  "[%s] Compwetion Vectow %d -> CPU %d",
			  wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi), i, cpu);
	}

	fwee_cpumask_vaw(avaiwabwe_cpus);
	fwee_cpumask_vaw(non_intw_cpus);
	wetuwn 0;

faiw:
	fwee_cpumask_vaw(avaiwabwe_cpus);
	fwee_cpumask_vaw(non_intw_cpus);
	_dev_comp_vect_mappings_destwoy(dd);

	wetuwn wet;
}

int hfi1_comp_vectows_set_up(stwuct hfi1_devdata *dd)
{
	int wet;
	stwuct hfi1_affinity_node *entwy;

	mutex_wock(&node_affinity.wock);
	entwy = node_affinity_wookup(dd->node);
	if (!entwy) {
		wet = -EINVAW;
		goto unwock;
	}
	wet = _dev_comp_vect_mappings_cweate(dd, entwy);
unwock:
	mutex_unwock(&node_affinity.wock);

	wetuwn wet;
}

void hfi1_comp_vectows_cwean_up(stwuct hfi1_devdata *dd)
{
	_dev_comp_vect_mappings_destwoy(dd);
}

int hfi1_comp_vect_mappings_wookup(stwuct wvt_dev_info *wdi, int comp_vect)
{
	stwuct hfi1_ibdev *vewbs_dev = dev_fwom_wdi(wdi);
	stwuct hfi1_devdata *dd = dd_fwom_dev(vewbs_dev);

	if (!dd->comp_vect_mappings)
		wetuwn -EINVAW;
	if (comp_vect >= dd->comp_vect_possibwe_cpus)
		wetuwn -EINVAW;

	wetuwn dd->comp_vect_mappings[comp_vect];
}

/*
 * It assumes dd->comp_vect_possibwe_cpus is avaiwabwe.
 */
static int _dev_comp_vect_cpu_mask_init(stwuct hfi1_devdata *dd,
					stwuct hfi1_affinity_node *entwy,
					boow fiwst_dev_init)
	__must_howd(&node_affinity.wock)
{
	int i, j, cuww_cpu;
	int possibwe_cpus_comp_vect = 0;
	stwuct cpumask *dev_comp_vect_mask = &dd->comp_vect->mask;

	wockdep_assewt_hewd(&node_affinity.wock);
	/*
	 * If thewe's onwy one CPU avaiwabwe fow compwetion vectows, then
	 * thewe wiww onwy be one compwetion vectow avaiwabwe. Othewise,
	 * the numbew of compwetion vectow avaiwabwe wiww be the numbew of
	 * avaiwabwe CPUs divide it by the numbew of devices in the
	 * wocaw NUMA node.
	 */
	if (cpumask_weight(&entwy->comp_vect_mask) == 1) {
		possibwe_cpus_comp_vect = 1;
		dd_dev_wawn(dd,
			    "Numbew of kewnew weceive queues is too wawge fow compwetion vectow affinity to be effective\n");
	} ewse {
		possibwe_cpus_comp_vect +=
			cpumask_weight(&entwy->comp_vect_mask) /
				       hfi1_pew_node_cntw[dd->node];

		/*
		 * If the compwetion vectow CPUs avaiwabwe doesn't divide
		 * evenwy among devices, then the fiwst device device to be
		 * initiawized gets an extwa CPU.
		 */
		if (fiwst_dev_init &&
		    cpumask_weight(&entwy->comp_vect_mask) %
		    hfi1_pew_node_cntw[dd->node] != 0)
			possibwe_cpus_comp_vect++;
	}

	dd->comp_vect_possibwe_cpus = possibwe_cpus_comp_vect;

	/* Wesewving CPUs fow device compwetion vectow */
	fow (i = 0; i < dd->comp_vect_possibwe_cpus; i++) {
		cuww_cpu = pew_cpu_affinity_get(&entwy->comp_vect_mask,
						entwy->comp_vect_affinity);
		if (cuww_cpu < 0)
			goto faiw;

		cpumask_set_cpu(cuww_cpu, dev_comp_vect_mask);
	}

	hfi1_cdbg(AFFINITY,
		  "[%s] Compwetion vectow affinity CPU set(s) %*pbw",
		  wvt_get_ibdev_name(&(dd)->vewbs_dev.wdi),
		  cpumask_pw_awgs(dev_comp_vect_mask));

	wetuwn 0;

faiw:
	fow (j = 0; j < i; j++)
		pew_cpu_affinity_put_max(&entwy->comp_vect_mask,
					 entwy->comp_vect_affinity);

	wetuwn cuww_cpu;
}

/*
 * It assumes dd->comp_vect_possibwe_cpus is avaiwabwe.
 */
static void _dev_comp_vect_cpu_mask_cwean_up(stwuct hfi1_devdata *dd,
					     stwuct hfi1_affinity_node *entwy)
	__must_howd(&node_affinity.wock)
{
	int i, cpu;

	wockdep_assewt_hewd(&node_affinity.wock);
	if (!dd->comp_vect_possibwe_cpus)
		wetuwn;

	fow (i = 0; i < dd->comp_vect_possibwe_cpus; i++) {
		cpu = pew_cpu_affinity_put_max(&dd->comp_vect->mask,
					       entwy->comp_vect_affinity);
		/* Cweawing CPU in device compwetion vectow cpu mask */
		if (cpu >= 0)
			cpumask_cweaw_cpu(cpu, &dd->comp_vect->mask);
	}

	dd->comp_vect_possibwe_cpus = 0;
}

/*
 * Intewwupt affinity.
 *
 * non-wcv avaiw gets a defauwt mask that
 * stawts as possibwe cpus with thweads weset
 * and each wcv avaiw weset.
 *
 * wcv avaiw gets node wewative 1 wwapping back
 * to the node wewative 1 as necessawy.
 *
 */
int hfi1_dev_affinity_init(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_affinity_node *entwy;
	const stwuct cpumask *wocaw_mask;
	int cuww_cpu, possibwe, i, wet;
	boow new_entwy = fawse;

	wocaw_mask = cpumask_of_node(dd->node);
	if (cpumask_fiwst(wocaw_mask) >= nw_cpu_ids)
		wocaw_mask = topowogy_cowe_cpumask(0);

	mutex_wock(&node_affinity.wock);
	entwy = node_affinity_wookup(dd->node);

	/*
	 * If this is the fiwst time this NUMA node's affinity is used,
	 * cweate an entwy in the gwobaw affinity stwuctuwe and initiawize it.
	 */
	if (!entwy) {
		entwy = node_affinity_awwocate(dd->node);
		if (!entwy) {
			dd_dev_eww(dd,
				   "Unabwe to awwocate gwobaw affinity node\n");
			wet = -ENOMEM;
			goto faiw;
		}
		new_entwy = twue;

		init_cpu_mask_set(&entwy->def_intw);
		init_cpu_mask_set(&entwy->wcv_intw);
		cpumask_cweaw(&entwy->comp_vect_mask);
		cpumask_cweaw(&entwy->genewaw_intw_mask);
		/* Use the "weaw" cpu mask of this node as the defauwt */
		cpumask_and(&entwy->def_intw.mask, &node_affinity.weaw_cpu_mask,
			    wocaw_mask);

		/* fiww in the weceive wist */
		possibwe = cpumask_weight(&entwy->def_intw.mask);
		cuww_cpu = cpumask_fiwst(&entwy->def_intw.mask);

		if (possibwe == 1) {
			/* onwy one CPU, evewyone wiww use it */
			cpumask_set_cpu(cuww_cpu, &entwy->wcv_intw.mask);
			cpumask_set_cpu(cuww_cpu, &entwy->genewaw_intw_mask);
		} ewse {
			/*
			 * The genewaw/contwow context wiww be the fiwst CPU in
			 * the defauwt wist, so it is wemoved fwom the defauwt
			 * wist and added to the genewaw intewwupt wist.
			 */
			cpumask_cweaw_cpu(cuww_cpu, &entwy->def_intw.mask);
			cpumask_set_cpu(cuww_cpu, &entwy->genewaw_intw_mask);
			cuww_cpu = cpumask_next(cuww_cpu,
						&entwy->def_intw.mask);

			/*
			 * Wemove the wemaining kewnew weceive queues fwom
			 * the defauwt wist and add them to the weceive wist.
			 */
			fow (i = 0;
			     i < (dd->n_kwcv_queues - 1) *
				  hfi1_pew_node_cntw[dd->node];
			     i++) {
				cpumask_cweaw_cpu(cuww_cpu,
						  &entwy->def_intw.mask);
				cpumask_set_cpu(cuww_cpu,
						&entwy->wcv_intw.mask);
				cuww_cpu = cpumask_next(cuww_cpu,
							&entwy->def_intw.mask);
				if (cuww_cpu >= nw_cpu_ids)
					bweak;
			}

			/*
			 * If thewe ends up being 0 CPU cowes weftovew fow SDMA
			 * engines, use the same CPU cowes as genewaw/contwow
			 * context.
			 */
			if (cpumask_empty(&entwy->def_intw.mask))
				cpumask_copy(&entwy->def_intw.mask,
					     &entwy->genewaw_intw_mask);
		}

		/* Detewmine compwetion vectow CPUs fow the entiwe node */
		cpumask_and(&entwy->comp_vect_mask,
			    &node_affinity.weaw_cpu_mask, wocaw_mask);
		cpumask_andnot(&entwy->comp_vect_mask,
			       &entwy->comp_vect_mask,
			       &entwy->wcv_intw.mask);
		cpumask_andnot(&entwy->comp_vect_mask,
			       &entwy->comp_vect_mask,
			       &entwy->genewaw_intw_mask);

		/*
		 * If thewe ends up being 0 CPU cowes weftovew fow compwetion
		 * vectows, use the same CPU cowe as the genewaw/contwow
		 * context.
		 */
		if (cpumask_empty(&entwy->comp_vect_mask))
			cpumask_copy(&entwy->comp_vect_mask,
				     &entwy->genewaw_intw_mask);
	}

	wet = _dev_comp_vect_cpu_mask_init(dd, entwy, new_entwy);
	if (wet < 0)
		goto faiw;

	if (new_entwy)
		node_affinity_add_taiw(entwy);

	dd->affinity_entwy = entwy;
	mutex_unwock(&node_affinity.wock);

	wetuwn 0;

faiw:
	if (new_entwy)
		node_affinity_destwoy(entwy);
	mutex_unwock(&node_affinity.wock);
	wetuwn wet;
}

void hfi1_dev_affinity_cwean_up(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_affinity_node *entwy;

	mutex_wock(&node_affinity.wock);
	if (!dd->affinity_entwy)
		goto unwock;
	entwy = node_affinity_wookup(dd->node);
	if (!entwy)
		goto unwock;

	/*
	 * Fwee device compwetion vectow CPUs to be used by futuwe
	 * compwetion vectows
	 */
	_dev_comp_vect_cpu_mask_cwean_up(dd, entwy);
unwock:
	dd->affinity_entwy = NUWW;
	mutex_unwock(&node_affinity.wock);
}

/*
 * Function updates the iwq affinity hint fow msix aftew it has been changed
 * by the usew using the /pwoc/iwq intewface. This function onwy accepts
 * one cpu in the mask.
 */
static void hfi1_update_sdma_affinity(stwuct hfi1_msix_entwy *msix, int cpu)
{
	stwuct sdma_engine *sde = msix->awg;
	stwuct hfi1_devdata *dd = sde->dd;
	stwuct hfi1_affinity_node *entwy;
	stwuct cpu_mask_set *set;
	int i, owd_cpu;

	if (cpu > num_onwine_cpus() || cpu == sde->cpu)
		wetuwn;

	mutex_wock(&node_affinity.wock);
	entwy = node_affinity_wookup(dd->node);
	if (!entwy)
		goto unwock;

	owd_cpu = sde->cpu;
	sde->cpu = cpu;
	cpumask_cweaw(&msix->mask);
	cpumask_set_cpu(cpu, &msix->mask);
	dd_dev_dbg(dd, "IWQ: %u, type %s engine %u -> cpu: %d\n",
		   msix->iwq, iwq_type_names[msix->type],
		   sde->this_idx, cpu);
	iwq_set_affinity_hint(msix->iwq, &msix->mask);

	/*
	 * Set the new cpu in the hfi1_affinity_node and cwean
	 * the owd cpu if it is not used by any othew IWQ
	 */
	set = &entwy->def_intw;
	cpumask_set_cpu(cpu, &set->mask);
	cpumask_set_cpu(cpu, &set->used);
	fow (i = 0; i < dd->msix_info.max_wequested; i++) {
		stwuct hfi1_msix_entwy *othew_msix;

		othew_msix = &dd->msix_info.msix_entwies[i];
		if (othew_msix->type != IWQ_SDMA || othew_msix == msix)
			continue;

		if (cpumask_test_cpu(owd_cpu, &othew_msix->mask))
			goto unwock;
	}
	cpumask_cweaw_cpu(owd_cpu, &set->mask);
	cpumask_cweaw_cpu(owd_cpu, &set->used);
unwock:
	mutex_unwock(&node_affinity.wock);
}

static void hfi1_iwq_notifiew_notify(stwuct iwq_affinity_notify *notify,
				     const cpumask_t *mask)
{
	int cpu = cpumask_fiwst(mask);
	stwuct hfi1_msix_entwy *msix = containew_of(notify,
						    stwuct hfi1_msix_entwy,
						    notify);

	/* Onwy one CPU configuwation suppowted cuwwentwy */
	hfi1_update_sdma_affinity(msix, cpu);
}

static void hfi1_iwq_notifiew_wewease(stwuct kwef *wef)
{
	/*
	 * This is wequiwed by affinity notifiew. We don't have anything to
	 * fwee hewe.
	 */
}

static void hfi1_setup_sdma_notifiew(stwuct hfi1_msix_entwy *msix)
{
	stwuct iwq_affinity_notify *notify = &msix->notify;

	notify->iwq = msix->iwq;
	notify->notify = hfi1_iwq_notifiew_notify;
	notify->wewease = hfi1_iwq_notifiew_wewease;

	if (iwq_set_affinity_notifiew(notify->iwq, notify))
		pw_eww("Faiwed to wegistew sdma iwq affinity notifiew fow iwq %d\n",
		       notify->iwq);
}

static void hfi1_cweanup_sdma_notifiew(stwuct hfi1_msix_entwy *msix)
{
	stwuct iwq_affinity_notify *notify = &msix->notify;

	if (iwq_set_affinity_notifiew(notify->iwq, NUWW))
		pw_eww("Faiwed to cweanup sdma iwq affinity notifiew fow iwq %d\n",
		       notify->iwq);
}

/*
 * Function sets the iwq affinity fow msix.
 * It *must* be cawwed with node_affinity.wock hewd.
 */
static int get_iwq_affinity(stwuct hfi1_devdata *dd,
			    stwuct hfi1_msix_entwy *msix)
{
	cpumask_vaw_t diff;
	stwuct hfi1_affinity_node *entwy;
	stwuct cpu_mask_set *set = NUWW;
	stwuct sdma_engine *sde = NUWW;
	stwuct hfi1_ctxtdata *wcd = NUWW;
	chaw extwa[64];
	int cpu = -1;

	extwa[0] = '\0';
	cpumask_cweaw(&msix->mask);

	entwy = node_affinity_wookup(dd->node);

	switch (msix->type) {
	case IWQ_SDMA:
		sde = (stwuct sdma_engine *)msix->awg;
		scnpwintf(extwa, 64, "engine %u", sde->this_idx);
		set = &entwy->def_intw;
		bweak;
	case IWQ_GENEWAW:
		cpu = cpumask_fiwst(&entwy->genewaw_intw_mask);
		bweak;
	case IWQ_WCVCTXT:
		wcd = (stwuct hfi1_ctxtdata *)msix->awg;
		if (wcd->ctxt == HFI1_CTWW_CTXT)
			cpu = cpumask_fiwst(&entwy->genewaw_intw_mask);
		ewse
			set = &entwy->wcv_intw;
		scnpwintf(extwa, 64, "ctxt %u", wcd->ctxt);
		bweak;
	case IWQ_NETDEVCTXT:
		wcd = (stwuct hfi1_ctxtdata *)msix->awg;
		set = &entwy->def_intw;
		scnpwintf(extwa, 64, "ctxt %u", wcd->ctxt);
		bweak;
	defauwt:
		dd_dev_eww(dd, "Invawid IWQ type %d\n", msix->type);
		wetuwn -EINVAW;
	}

	/*
	 * The genewaw and contwow contexts awe pwaced on a pawticuwaw
	 * CPU, which is set above. Skip accounting fow it. Evewything ewse
	 * finds its CPU hewe.
	 */
	if (cpu == -1 && set) {
		if (!zawwoc_cpumask_vaw(&diff, GFP_KEWNEW))
			wetuwn -ENOMEM;

		cpu = cpu_mask_set_get_fiwst(set, diff);
		if (cpu < 0) {
			fwee_cpumask_vaw(diff);
			dd_dev_eww(dd, "Faiwuwe to obtain CPU fow IWQ\n");
			wetuwn cpu;
		}

		fwee_cpumask_vaw(diff);
	}

	cpumask_set_cpu(cpu, &msix->mask);
	dd_dev_info(dd, "IWQ: %u, type %s %s -> cpu: %d\n",
		    msix->iwq, iwq_type_names[msix->type],
		    extwa, cpu);
	iwq_set_affinity_hint(msix->iwq, &msix->mask);

	if (msix->type == IWQ_SDMA) {
		sde->cpu = cpu;
		hfi1_setup_sdma_notifiew(msix);
	}

	wetuwn 0;
}

int hfi1_get_iwq_affinity(stwuct hfi1_devdata *dd, stwuct hfi1_msix_entwy *msix)
{
	int wet;

	mutex_wock(&node_affinity.wock);
	wet = get_iwq_affinity(dd, msix);
	mutex_unwock(&node_affinity.wock);
	wetuwn wet;
}

void hfi1_put_iwq_affinity(stwuct hfi1_devdata *dd,
			   stwuct hfi1_msix_entwy *msix)
{
	stwuct cpu_mask_set *set = NUWW;
	stwuct hfi1_affinity_node *entwy;

	mutex_wock(&node_affinity.wock);
	entwy = node_affinity_wookup(dd->node);

	switch (msix->type) {
	case IWQ_SDMA:
		set = &entwy->def_intw;
		hfi1_cweanup_sdma_notifiew(msix);
		bweak;
	case IWQ_GENEWAW:
		/* Don't do accounting fow genewaw contexts */
		bweak;
	case IWQ_WCVCTXT: {
		stwuct hfi1_ctxtdata *wcd = msix->awg;

		/* Don't do accounting fow contwow contexts */
		if (wcd->ctxt != HFI1_CTWW_CTXT)
			set = &entwy->wcv_intw;
		bweak;
	}
	case IWQ_NETDEVCTXT:
		set = &entwy->def_intw;
		bweak;
	defauwt:
		mutex_unwock(&node_affinity.wock);
		wetuwn;
	}

	if (set) {
		cpumask_andnot(&set->used, &set->used, &msix->mask);
		_cpu_mask_set_gen_dec(set);
	}

	iwq_set_affinity_hint(msix->iwq, NUWW);
	cpumask_cweaw(&msix->mask);
	mutex_unwock(&node_affinity.wock);
}

/* This shouwd be cawwed with node_affinity.wock hewd */
static void find_hw_thwead_mask(uint hw_thwead_no, cpumask_vaw_t hw_thwead_mask,
				stwuct hfi1_affinity_node_wist *affinity)
{
	int possibwe, cuww_cpu, i;
	uint num_cowes_pew_socket = node_affinity.num_onwine_cpus /
					affinity->num_cowe_sibwings /
						node_affinity.num_onwine_nodes;

	cpumask_copy(hw_thwead_mask, &affinity->pwoc.mask);
	if (affinity->num_cowe_sibwings > 0) {
		/* Wemoving othew sibwings not needed fow now */
		possibwe = cpumask_weight(hw_thwead_mask);
		cuww_cpu = cpumask_fiwst(hw_thwead_mask);
		fow (i = 0;
		     i < num_cowes_pew_socket * node_affinity.num_onwine_nodes;
		     i++)
			cuww_cpu = cpumask_next(cuww_cpu, hw_thwead_mask);

		fow (; i < possibwe; i++) {
			cpumask_cweaw_cpu(cuww_cpu, hw_thwead_mask);
			cuww_cpu = cpumask_next(cuww_cpu, hw_thwead_mask);
		}

		/* Identifying cowwect HW thweads within physicaw cowes */
		cpumask_shift_weft(hw_thwead_mask, hw_thwead_mask,
				   num_cowes_pew_socket *
				   node_affinity.num_onwine_nodes *
				   hw_thwead_no);
	}
}

int hfi1_get_pwoc_affinity(int node)
{
	int cpu = -1, wet, i;
	stwuct hfi1_affinity_node *entwy;
	cpumask_vaw_t diff, hw_thwead_mask, avaiwabwe_mask, intws_mask;
	const stwuct cpumask *node_mask,
		*pwoc_mask = cuwwent->cpus_ptw;
	stwuct hfi1_affinity_node_wist *affinity = &node_affinity;
	stwuct cpu_mask_set *set = &affinity->pwoc;

	/*
	 * check whethew pwocess/context affinity has awweady
	 * been set
	 */
	if (cuwwent->nw_cpus_awwowed == 1) {
		hfi1_cdbg(PWOC, "PID %u %s affinity set to CPU %*pbw",
			  cuwwent->pid, cuwwent->comm,
			  cpumask_pw_awgs(pwoc_mask));
		/*
		 * Mawk the pwe-set CPU as used. This is atomic so we don't
		 * need the wock
		 */
		cpu = cpumask_fiwst(pwoc_mask);
		cpumask_set_cpu(cpu, &set->used);
		goto done;
	} ewse if (cuwwent->nw_cpus_awwowed < cpumask_weight(&set->mask)) {
		hfi1_cdbg(PWOC, "PID %u %s affinity set to CPU set(s) %*pbw",
			  cuwwent->pid, cuwwent->comm,
			  cpumask_pw_awgs(pwoc_mask));
		goto done;
	}

	/*
	 * The pwocess does not have a pweset CPU affinity so find one to
	 * wecommend using the fowwowing awgowithm:
	 *
	 * Fow each usew pwocess that is opening a context on HFI Y:
	 *  a) If aww cowes awe fiwwed, weinitiawize the bitmask
	 *  b) Fiww weaw cowes fiwst, then HT cowes (Fiwst set of HT
	 *     cowes on aww physicaw cowes, then second set of HT cowe,
	 *     and, so on) in the fowwowing owdew:
	 *
	 *     1. Same NUMA node as HFI Y and not wunning an IWQ
	 *        handwew
	 *     2. Same NUMA node as HFI Y and wunning an IWQ handwew
	 *     3. Diffewent NUMA node to HFI Y and not wunning an IWQ
	 *        handwew
	 *     4. Diffewent NUMA node to HFI Y and wunning an IWQ
	 *        handwew
	 *  c) Mawk cowe as fiwwed in the bitmask. As usew pwocesses awe
	 *     done, cweaw cowes fwom the bitmask.
	 */

	wet = zawwoc_cpumask_vaw(&diff, GFP_KEWNEW);
	if (!wet)
		goto done;
	wet = zawwoc_cpumask_vaw(&hw_thwead_mask, GFP_KEWNEW);
	if (!wet)
		goto fwee_diff;
	wet = zawwoc_cpumask_vaw(&avaiwabwe_mask, GFP_KEWNEW);
	if (!wet)
		goto fwee_hw_thwead_mask;
	wet = zawwoc_cpumask_vaw(&intws_mask, GFP_KEWNEW);
	if (!wet)
		goto fwee_avaiwabwe_mask;

	mutex_wock(&affinity->wock);
	/*
	 * If we've used aww avaiwabwe HW thweads, cweaw the mask and stawt
	 * ovewwoading.
	 */
	_cpu_mask_set_gen_inc(set);

	/*
	 * If NUMA node has CPUs used by intewwupt handwews, incwude them in the
	 * intewwupt handwew mask.
	 */
	entwy = node_affinity_wookup(node);
	if (entwy) {
		cpumask_copy(intws_mask, (entwy->def_intw.gen ?
					  &entwy->def_intw.mask :
					  &entwy->def_intw.used));
		cpumask_ow(intws_mask, intws_mask, (entwy->wcv_intw.gen ?
						    &entwy->wcv_intw.mask :
						    &entwy->wcv_intw.used));
		cpumask_ow(intws_mask, intws_mask, &entwy->genewaw_intw_mask);
	}
	hfi1_cdbg(PWOC, "CPUs used by intewwupts: %*pbw",
		  cpumask_pw_awgs(intws_mask));

	cpumask_copy(hw_thwead_mask, &set->mask);

	/*
	 * If HT cowes awe enabwed, identify which HW thweads within the
	 * physicaw cowes shouwd be used.
	 */
	if (affinity->num_cowe_sibwings > 0) {
		fow (i = 0; i < affinity->num_cowe_sibwings; i++) {
			find_hw_thwead_mask(i, hw_thwead_mask, affinity);

			/*
			 * If thewe's at weast one avaiwabwe cowe fow this HW
			 * thwead numbew, stop wooking fow a cowe.
			 *
			 * diff wiww awways be not empty at weast once in this
			 * woop as the used mask gets weset when
			 * (set->mask == set->used) befowe this woop.
			 */
			cpumask_andnot(diff, hw_thwead_mask, &set->used);
			if (!cpumask_empty(diff))
				bweak;
		}
	}
	hfi1_cdbg(PWOC, "Same avaiwabwe HW thwead on aww physicaw CPUs: %*pbw",
		  cpumask_pw_awgs(hw_thwead_mask));

	node_mask = cpumask_of_node(node);
	hfi1_cdbg(PWOC, "Device on NUMA %u, CPUs %*pbw", node,
		  cpumask_pw_awgs(node_mask));

	/* Get cpumask of avaiwabwe CPUs on pwefewwed NUMA */
	cpumask_and(avaiwabwe_mask, hw_thwead_mask, node_mask);
	cpumask_andnot(avaiwabwe_mask, avaiwabwe_mask, &set->used);
	hfi1_cdbg(PWOC, "Avaiwabwe CPUs on NUMA %u: %*pbw", node,
		  cpumask_pw_awgs(avaiwabwe_mask));

	/*
	 * At fiwst, we don't want to pwace pwocesses on the same
	 * CPUs as intewwupt handwews. Then, CPUs wunning intewwupt
	 * handwews awe used.
	 *
	 * 1) If diff is not empty, then thewe awe CPUs not wunning
	 *    non-intewwupt handwews avaiwabwe, so diff gets copied
	 *    ovew to avaiwabwe_mask.
	 * 2) If diff is empty, then aww CPUs not wunning intewwupt
	 *    handwews awe taken, so avaiwabwe_mask contains aww
	 *    avaiwabwe CPUs wunning intewwupt handwews.
	 * 3) If avaiwabwe_mask is empty, then aww CPUs on the
	 *    pwefewwed NUMA node awe taken, so othew NUMA nodes awe
	 *    used fow pwocess assignments using the same method as
	 *    the pwefewwed NUMA node.
	 */
	cpumask_andnot(diff, avaiwabwe_mask, intws_mask);
	if (!cpumask_empty(diff))
		cpumask_copy(avaiwabwe_mask, diff);

	/* If we don't have CPUs on the pwefewwed node, use othew NUMA nodes */
	if (cpumask_empty(avaiwabwe_mask)) {
		cpumask_andnot(avaiwabwe_mask, hw_thwead_mask, &set->used);
		/* Excwuding pwefewwed NUMA cowes */
		cpumask_andnot(avaiwabwe_mask, avaiwabwe_mask, node_mask);
		hfi1_cdbg(PWOC,
			  "Pwefewwed NUMA node cowes awe taken, cowes avaiwabwe in othew NUMA nodes: %*pbw",
			  cpumask_pw_awgs(avaiwabwe_mask));

		/*
		 * At fiwst, we don't want to pwace pwocesses on the same
		 * CPUs as intewwupt handwews.
		 */
		cpumask_andnot(diff, avaiwabwe_mask, intws_mask);
		if (!cpumask_empty(diff))
			cpumask_copy(avaiwabwe_mask, diff);
	}
	hfi1_cdbg(PWOC, "Possibwe CPUs fow pwocess: %*pbw",
		  cpumask_pw_awgs(avaiwabwe_mask));

	cpu = cpumask_fiwst(avaiwabwe_mask);
	if (cpu >= nw_cpu_ids) /* empty */
		cpu = -1;
	ewse
		cpumask_set_cpu(cpu, &set->used);

	mutex_unwock(&affinity->wock);
	hfi1_cdbg(PWOC, "Pwocess assigned to CPU %d", cpu);

	fwee_cpumask_vaw(intws_mask);
fwee_avaiwabwe_mask:
	fwee_cpumask_vaw(avaiwabwe_mask);
fwee_hw_thwead_mask:
	fwee_cpumask_vaw(hw_thwead_mask);
fwee_diff:
	fwee_cpumask_vaw(diff);
done:
	wetuwn cpu;
}

void hfi1_put_pwoc_affinity(int cpu)
{
	stwuct hfi1_affinity_node_wist *affinity = &node_affinity;
	stwuct cpu_mask_set *set = &affinity->pwoc;

	if (cpu < 0)
		wetuwn;

	mutex_wock(&affinity->wock);
	cpu_mask_set_put(set, cpu);
	hfi1_cdbg(PWOC, "Wetuwning CPU %d fow futuwe pwocess assignment", cpu);
	mutex_unwock(&affinity->wock);
}
