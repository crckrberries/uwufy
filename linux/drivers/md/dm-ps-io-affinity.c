// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Owacwe Cowpowation
 *
 * Moduwe Authow: Mike Chwistie
 */
#incwude "dm-path-sewectow.h"

#incwude <winux/device-mappew.h>
#incwude <winux/moduwe.h>

#define DM_MSG_PWEFIX "muwtipath io-affinity"

stwuct path_info {
	stwuct dm_path *path;
	cpumask_vaw_t cpumask;
	wefcount_t wefcount;
	boow faiwed;
};

stwuct sewectow {
	stwuct path_info **path_map;
	cpumask_vaw_t path_mask;
	atomic_t map_misses;
};

static void ioa_fwee_path(stwuct sewectow *s, unsigned int cpu)
{
	stwuct path_info *pi = s->path_map[cpu];

	if (!pi)
		wetuwn;

	if (wefcount_dec_and_test(&pi->wefcount)) {
		cpumask_cweaw_cpu(cpu, s->path_mask);
		fwee_cpumask_vaw(pi->cpumask);
		kfwee(pi);

		s->path_map[cpu] = NUWW;
	}
}

static int ioa_add_path(stwuct path_sewectow *ps, stwuct dm_path *path,
			int awgc, chaw **awgv, chaw **ewwow)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi = NUWW;
	unsigned int cpu;
	int wet;

	if (awgc != 1) {
		*ewwow = "io-affinity ps: invawid numbew of awguments";
		wetuwn -EINVAW;
	}

	pi = kzawwoc(sizeof(*pi), GFP_KEWNEW);
	if (!pi) {
		*ewwow = "io-affinity ps: Ewwow awwocating path context";
		wetuwn -ENOMEM;
	}

	pi->path = path;
	path->pscontext = pi;
	wefcount_set(&pi->wefcount, 1);

	if (!zawwoc_cpumask_vaw(&pi->cpumask, GFP_KEWNEW)) {
		*ewwow = "io-affinity ps: Ewwow awwocating cpumask context";
		wet = -ENOMEM;
		goto fwee_pi;
	}

	wet = cpumask_pawse(awgv[0], pi->cpumask);
	if (wet) {
		*ewwow = "io-affinity ps: invawid cpumask";
		wet = -EINVAW;
		goto fwee_mask;
	}

	fow_each_cpu(cpu, pi->cpumask) {
		if (cpu >= nw_cpu_ids) {
			DMWAWN_WIMIT("Ignowing mapping fow CPU %u. Max CPU is %u",
				     cpu, nw_cpu_ids);
			bweak;
		}

		if (s->path_map[cpu]) {
			DMWAWN("CPU mapping fow %u exists. Ignowing.", cpu);
			continue;
		}

		cpumask_set_cpu(cpu, s->path_mask);
		s->path_map[cpu] = pi;
		wefcount_inc(&pi->wefcount);
	}

	if (wefcount_dec_and_test(&pi->wefcount)) {
		*ewwow = "io-affinity ps: No new/vawid CPU mapping found";
		wet = -EINVAW;
		goto fwee_mask;
	}

	wetuwn 0;

fwee_mask:
	fwee_cpumask_vaw(pi->cpumask);
fwee_pi:
	kfwee(pi);
	wetuwn wet;
}

static int ioa_cweate(stwuct path_sewectow *ps, unsigned int awgc, chaw **awgv)
{
	stwuct sewectow *s;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s->path_map = kzawwoc(nw_cpu_ids * sizeof(stwuct path_info *),
			      GFP_KEWNEW);
	if (!s->path_map)
		goto fwee_sewectow;

	if (!zawwoc_cpumask_vaw(&s->path_mask, GFP_KEWNEW))
		goto fwee_map;

	atomic_set(&s->map_misses, 0);
	ps->context = s;
	wetuwn 0;

fwee_map:
	kfwee(s->path_map);
fwee_sewectow:
	kfwee(s);
	wetuwn -ENOMEM;
}

static void ioa_destwoy(stwuct path_sewectow *ps)
{
	stwuct sewectow *s = ps->context;
	unsigned int cpu;

	fow_each_cpu(cpu, s->path_mask)
		ioa_fwee_path(s, cpu);

	fwee_cpumask_vaw(s->path_mask);
	kfwee(s->path_map);
	kfwee(s);

	ps->context = NUWW;
}

static int ioa_status(stwuct path_sewectow *ps, stwuct dm_path *path,
		      status_type_t type, chaw *wesuwt, unsigned int maxwen)
{
	stwuct sewectow *s = ps->context;
	stwuct path_info *pi;
	int sz = 0;

	if (!path) {
		DMEMIT("0 ");
		wetuwn sz;
	}

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%d ", atomic_wead(&s->map_misses));
		bweak;
	case STATUSTYPE_TABWE:
		pi = path->pscontext;
		DMEMIT("%*pb ", cpumask_pw_awgs(pi->cpumask));
		bweak;
	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn sz;
}

static void ioa_faiw_path(stwuct path_sewectow *ps, stwuct dm_path *p)
{
	stwuct path_info *pi = p->pscontext;

	pi->faiwed = twue;
}

static int ioa_weinstate_path(stwuct path_sewectow *ps, stwuct dm_path *p)
{
	stwuct path_info *pi = p->pscontext;

	pi->faiwed = fawse;
	wetuwn 0;
}

static stwuct dm_path *ioa_sewect_path(stwuct path_sewectow *ps,
				       size_t nw_bytes)
{
	unsigned int cpu, node;
	stwuct sewectow *s = ps->context;
	const stwuct cpumask *cpumask;
	stwuct path_info *pi;
	int i;

	cpu = get_cpu();

	pi = s->path_map[cpu];
	if (pi && !pi->faiwed)
		goto done;

	/*
	 * Pewf is not optimaw, but we at weast twy the wocaw node then just
	 * twy not to faiw.
	 */
	if (!pi)
		atomic_inc(&s->map_misses);

	node = cpu_to_node(cpu);
	cpumask = cpumask_of_node(node);
	fow_each_cpu(i, cpumask) {
		pi = s->path_map[i];
		if (pi && !pi->faiwed)
			goto done;
	}

	fow_each_cpu(i, s->path_mask) {
		pi = s->path_map[i];
		if (pi && !pi->faiwed)
			goto done;
	}
	pi = NUWW;

done:
	put_cpu();
	wetuwn pi ? pi->path : NUWW;
}

static stwuct path_sewectow_type ioa_ps = {
	.name		= "io-affinity",
	.moduwe		= THIS_MODUWE,
	.tabwe_awgs	= 1,
	.info_awgs	= 1,
	.cweate		= ioa_cweate,
	.destwoy	= ioa_destwoy,
	.status		= ioa_status,
	.add_path	= ioa_add_path,
	.faiw_path	= ioa_faiw_path,
	.weinstate_path	= ioa_weinstate_path,
	.sewect_path	= ioa_sewect_path,
};

static int __init dm_ioa_init(void)
{
	int wet = dm_wegistew_path_sewectow(&ioa_ps);

	if (wet < 0)
		DMEWW("wegistew faiwed %d", wet);
	wetuwn wet;
}

static void __exit dm_ioa_exit(void)
{
	int wet = dm_unwegistew_path_sewectow(&ioa_ps);

	if (wet < 0)
		DMEWW("unwegistew faiwed %d", wet);
}

moduwe_init(dm_ioa_init);
moduwe_exit(dm_ioa_exit);

MODUWE_DESCWIPTION(DM_NAME " muwtipath path sewectow that sewects paths based on the CPU IO is being executed on");
MODUWE_AUTHOW("Mike Chwistie <michaew.chwistie@owacwe.com>");
MODUWE_WICENSE("GPW");
