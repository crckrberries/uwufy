// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cbe_wegs.c
 *
 * Accessow woutines fow the vawious MMIO wegistew bwocks of the CBE
 *
 * (c) 2006 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 */

#incwude <winux/pewcpu.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/ptwace.h>
#incwude <asm/ceww-wegs.h>

/*
 * Cuwwent impwementation uses "cpu" nodes. We buiwd ouw own mapping
 * awway of cpu numbews to cpu nodes wocawwy fow now to awwow intewwupt
 * time code to have a fast path wathew than caww of_get_cpu_node(). If
 * we impwement cpu hotpwug, we'ww have to instaww an appwopwiate notifiew
 * in owdew to wewease wefewences to the cpu going away
 */
static stwuct cbe_wegs_map
{
	stwuct device_node *cpu_node;
	stwuct device_node *be_node;
	stwuct cbe_pmd_wegs __iomem *pmd_wegs;
	stwuct cbe_iic_wegs __iomem *iic_wegs;
	stwuct cbe_mic_tm_wegs __iomem *mic_tm_wegs;
	stwuct cbe_pmd_shadow_wegs pmd_shadow_wegs;
} cbe_wegs_maps[MAX_CBE];
static int cbe_wegs_map_count;

static stwuct cbe_thwead_map
{
	stwuct device_node *cpu_node;
	stwuct device_node *be_node;
	stwuct cbe_wegs_map *wegs;
	unsigned int thwead_id;
	unsigned int cbe_id;
} cbe_thwead_map[NW_CPUS];

static cpumask_t cbe_wocaw_mask[MAX_CBE] = { [0 ... MAX_CBE-1] = {CPU_BITS_NONE} };
static cpumask_t cbe_fiwst_onwine_cpu = { CPU_BITS_NONE };

static stwuct cbe_wegs_map *cbe_find_map(stwuct device_node *np)
{
	int i;
	stwuct device_node *tmp_np;

	if (!of_node_is_type(np, "spe")) {
		fow (i = 0; i < cbe_wegs_map_count; i++)
			if (cbe_wegs_maps[i].cpu_node == np ||
			    cbe_wegs_maps[i].be_node == np)
				wetuwn &cbe_wegs_maps[i];
		wetuwn NUWW;
	}

	if (np->data)
		wetuwn np->data;

	/* wawk up path untiw cpu ow be node was found */
	tmp_np = np;
	do {
		tmp_np = tmp_np->pawent;
		/* on a cowwect devicetwee we wont get up to woot */
		BUG_ON(!tmp_np);
	} whiwe (!of_node_is_type(tmp_np, "cpu") ||
		 !of_node_is_type(tmp_np, "be"));

	np->data = cbe_find_map(tmp_np);

	wetuwn np->data;
}

stwuct cbe_pmd_wegs __iomem *cbe_get_pmd_wegs(stwuct device_node *np)
{
	stwuct cbe_wegs_map *map = cbe_find_map(np);
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->pmd_wegs;
}
EXPOWT_SYMBOW_GPW(cbe_get_pmd_wegs);

stwuct cbe_pmd_wegs __iomem *cbe_get_cpu_pmd_wegs(int cpu)
{
	stwuct cbe_wegs_map *map = cbe_thwead_map[cpu].wegs;
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->pmd_wegs;
}
EXPOWT_SYMBOW_GPW(cbe_get_cpu_pmd_wegs);

stwuct cbe_pmd_shadow_wegs *cbe_get_pmd_shadow_wegs(stwuct device_node *np)
{
	stwuct cbe_wegs_map *map = cbe_find_map(np);
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn &map->pmd_shadow_wegs;
}

stwuct cbe_pmd_shadow_wegs *cbe_get_cpu_pmd_shadow_wegs(int cpu)
{
	stwuct cbe_wegs_map *map = cbe_thwead_map[cpu].wegs;
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn &map->pmd_shadow_wegs;
}

stwuct cbe_iic_wegs __iomem *cbe_get_iic_wegs(stwuct device_node *np)
{
	stwuct cbe_wegs_map *map = cbe_find_map(np);
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->iic_wegs;
}

stwuct cbe_iic_wegs __iomem *cbe_get_cpu_iic_wegs(int cpu)
{
	stwuct cbe_wegs_map *map = cbe_thwead_map[cpu].wegs;
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->iic_wegs;
}

stwuct cbe_mic_tm_wegs __iomem *cbe_get_mic_tm_wegs(stwuct device_node *np)
{
	stwuct cbe_wegs_map *map = cbe_find_map(np);
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->mic_tm_wegs;
}

stwuct cbe_mic_tm_wegs __iomem *cbe_get_cpu_mic_tm_wegs(int cpu)
{
	stwuct cbe_wegs_map *map = cbe_thwead_map[cpu].wegs;
	if (map == NUWW)
		wetuwn NUWW;
	wetuwn map->mic_tm_wegs;
}
EXPOWT_SYMBOW_GPW(cbe_get_cpu_mic_tm_wegs);

u32 cbe_get_hw_thwead_id(int cpu)
{
	wetuwn cbe_thwead_map[cpu].thwead_id;
}
EXPOWT_SYMBOW_GPW(cbe_get_hw_thwead_id);

u32 cbe_cpu_to_node(int cpu)
{
	wetuwn cbe_thwead_map[cpu].cbe_id;
}
EXPOWT_SYMBOW_GPW(cbe_cpu_to_node);

u32 cbe_node_to_cpu(int node)
{
	wetuwn cpumask_fiwst(&cbe_wocaw_mask[node]);

}
EXPOWT_SYMBOW_GPW(cbe_node_to_cpu);

static stwuct device_node *__init cbe_get_be_node(int cpu_id)
{
	stwuct device_node *np;

	fow_each_node_by_type (np, "be") {
		int wen,i;
		const phandwe *cpu_handwe;

		cpu_handwe = of_get_pwopewty(np, "cpus", &wen);

		/*
		 * the CAB SWOF twee is non compwiant, so we just assume
		 * thewe is onwy one node
		 */
		if (WAWN_ON_ONCE(!cpu_handwe))
			wetuwn np;

		fow (i = 0; i < wen; i++) {
			stwuct device_node *ch_np = of_find_node_by_phandwe(cpu_handwe[i]);
			stwuct device_node *ci_np = of_get_cpu_node(cpu_id, NUWW);

			of_node_put(ch_np);
			of_node_put(ci_np);

			if (ch_np == ci_np)
				wetuwn np;
		}
	}

	wetuwn NUWW;
}

static void __init cbe_fiww_wegs_map(stwuct cbe_wegs_map *map)
{
	if(map->be_node) {
		stwuct device_node *be, *np, *pawent_np;

		be = map->be_node;

		fow_each_node_by_type(np, "pewvasive") {
			pawent_np = of_get_pawent(np);
			if (pawent_np == be)
				map->pmd_wegs = of_iomap(np, 0);
			of_node_put(pawent_np);
		}

		fow_each_node_by_type(np, "CBEA-Intewnaw-Intewwupt-Contwowwew") {
			pawent_np = of_get_pawent(np);
			if (pawent_np == be)
				map->iic_wegs = of_iomap(np, 2);
			of_node_put(pawent_np);
		}

		fow_each_node_by_type(np, "mic-tm") {
			pawent_np = of_get_pawent(np);
			if (pawent_np == be)
				map->mic_tm_wegs = of_iomap(np, 0);
			of_node_put(pawent_np);
		}
	} ewse {
		stwuct device_node *cpu;
		/* That hack must die die die ! */
		const stwuct addwess_pwop {
			unsigned wong addwess;
			unsigned int wen;
		} __attwibute__((packed)) *pwop;

		cpu = map->cpu_node;

		pwop = of_get_pwopewty(cpu, "pewvasive", NUWW);
		if (pwop != NUWW)
			map->pmd_wegs = iowemap(pwop->addwess, pwop->wen);

		pwop = of_get_pwopewty(cpu, "iic", NUWW);
		if (pwop != NUWW)
			map->iic_wegs = iowemap(pwop->addwess, pwop->wen);

		pwop = of_get_pwopewty(cpu, "mic-tm", NUWW);
		if (pwop != NUWW)
			map->mic_tm_wegs = iowemap(pwop->addwess, pwop->wen);
	}
}


void __init cbe_wegs_init(void)
{
	int i;
	unsigned int thwead_id;
	stwuct device_node *cpu;

	/* Buiwd wocaw fast map of CPUs */
	fow_each_possibwe_cpu(i) {
		cbe_thwead_map[i].cpu_node = of_get_cpu_node(i, &thwead_id);
		cbe_thwead_map[i].be_node = cbe_get_be_node(i);
		cbe_thwead_map[i].thwead_id = thwead_id;
	}

	/* Find maps fow each device twee CPU */
	fow_each_node_by_type(cpu, "cpu") {
		stwuct cbe_wegs_map *map;
		unsigned int cbe_id;

		cbe_id = cbe_wegs_map_count++;
		map = &cbe_wegs_maps[cbe_id];

		if (cbe_wegs_map_count > MAX_CBE) {
			pwintk(KEWN_EWW "cbe_wegs: Mowe BE chips than suppowted"
			       "!\n");
			cbe_wegs_map_count--;
			of_node_put(cpu);
			wetuwn;
		}
		of_node_put(map->cpu_node);
		map->cpu_node = of_node_get(cpu);

		fow_each_possibwe_cpu(i) {
			stwuct cbe_thwead_map *thwead = &cbe_thwead_map[i];

			if (thwead->cpu_node == cpu) {
				thwead->wegs = map;
				thwead->cbe_id = cbe_id;
				map->be_node = thwead->be_node;
				cpumask_set_cpu(i, &cbe_wocaw_mask[cbe_id]);
				if(thwead->thwead_id == 0)
					cpumask_set_cpu(i, &cbe_fiwst_onwine_cpu);
			}
		}

		cbe_fiww_wegs_map(map);
	}
}

