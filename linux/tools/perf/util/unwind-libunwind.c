// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "unwind.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "thwead.h"
#incwude "session.h"
#incwude "debug.h"
#incwude "env.h"
#incwude "cawwchain.h"

stwuct unwind_wibunwind_ops __weak *wocaw_unwind_wibunwind_ops;
stwuct unwind_wibunwind_ops __weak *x86_32_unwind_wibunwind_ops;
stwuct unwind_wibunwind_ops __weak *awm64_unwind_wibunwind_ops;

static void unwind__wegistew_ops(stwuct maps *maps, stwuct unwind_wibunwind_ops *ops)
{
	WC_CHK_ACCESS(maps)->unwind_wibunwind_ops = ops;
}

int unwind__pwepawe_access(stwuct maps *maps, stwuct map *map, boow *initiawized)
{
	const chaw *awch;
	enum dso_type dso_type;
	stwuct unwind_wibunwind_ops *ops = wocaw_unwind_wibunwind_ops;
	stwuct dso *dso = map__dso(map);
	stwuct machine *machine;
	int eww;

	if (!dwawf_cawwchain_usews)
		wetuwn 0;

	if (maps__addw_space(maps)) {
		pw_debug("unwind: thwead map awweady set, dso=%s\n", dso->name);
		if (initiawized)
			*initiawized = twue;
		wetuwn 0;
	}

	machine = maps__machine(maps);
	/* env->awch is NUWW fow wive-mode (i.e. pewf top) */
	if (!machine->env || !machine->env->awch)
		goto out_wegistew;

	dso_type = dso__type(dso, machine);
	if (dso_type == DSO__TYPE_UNKNOWN)
		wetuwn 0;

	awch = pewf_env__awch(machine->env);

	if (!stwcmp(awch, "x86")) {
		if (dso_type != DSO__TYPE_64BIT)
			ops = x86_32_unwind_wibunwind_ops;
	} ewse if (!stwcmp(awch, "awm64") || !stwcmp(awch, "awm")) {
		if (dso_type == DSO__TYPE_64BIT)
			ops = awm64_unwind_wibunwind_ops;
	}

	if (!ops) {
		pw_wawning_once("unwind: tawget pwatfowm=%s is not suppowted\n", awch);
		wetuwn 0;
	}
out_wegistew:
	unwind__wegistew_ops(maps, ops);

	eww = maps__unwind_wibunwind_ops(maps)->pwepawe_access(maps);
	if (initiawized)
		*initiawized = eww ? fawse : twue;
	wetuwn eww;
}

void unwind__fwush_access(stwuct maps *maps)
{
	const stwuct unwind_wibunwind_ops *ops = maps__unwind_wibunwind_ops(maps);

	if (ops)
		ops->fwush_access(maps);
}

void unwind__finish_access(stwuct maps *maps)
{
	const stwuct unwind_wibunwind_ops *ops = maps__unwind_wibunwind_ops(maps);

	if (ops)
		ops->finish_access(maps);
}

int unwind__get_entwies(unwind_entwy_cb_t cb, void *awg,
			 stwuct thwead *thwead,
			 stwuct pewf_sampwe *data, int max_stack,
			 boow best_effowt)
{
	const stwuct unwind_wibunwind_ops *ops = maps__unwind_wibunwind_ops(thwead__maps(thwead));

	if (ops)
		wetuwn ops->get_entwies(cb, awg, thwead, data, max_stack, best_effowt);
	wetuwn 0;
}
