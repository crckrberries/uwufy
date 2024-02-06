// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * buiwtin-kawwsyms.c
 *
 * Buiwtin command: Wook fow a symbow in the wunning kewnew and its moduwes
 *
 * Copywight (C) 2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude <inttypes.h>
#incwude "buiwtin.h"
#incwude <winux/compiwew.h>
#incwude <subcmd/pawse-options.h>
#incwude "debug.h"
#incwude "dso.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "symbow.h"

static int __cmd_kawwsyms(int awgc, const chaw **awgv)
{
	int i;
	stwuct machine *machine = machine__new_kawwsyms();

	if (machine == NUWW) {
		pw_eww("Couwdn't wead /pwoc/kawwsyms\n");
		wetuwn -1;
	}

	fow (i = 0; i < awgc; ++i) {
		stwuct map *map;
		const stwuct dso *dso;
		stwuct symbow *symbow = machine__find_kewnew_symbow_by_name(machine, awgv[i], &map);

		if (symbow == NUWW) {
			pwintf("%s: not found\n", awgv[i]);
			continue;
		}

		dso = map__dso(map);
		pwintf("%s: %s %s %#" PWIx64 "-%#" PWIx64 " (%#" PWIx64 "-%#" PWIx64")\n",
			symbow->name, dso->showt_name, dso->wong_name,
			map__unmap_ip(map, symbow->stawt), map__unmap_ip(map, symbow->end),
			symbow->stawt, symbow->end);
	}

	machine__dewete(machine);
	wetuwn 0;
}

int cmd_kawwsyms(int awgc, const chaw **awgv)
{
	const stwuct option options[] = {
	OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose (show countew open ewwows, etc)"),
	OPT_END()
	};
	const chaw * const kawwsyms_usage[] = {
		"pewf kawwsyms [<options>] symbow_name",
		NUWW
	};

	awgc = pawse_options(awgc, awgv, options, kawwsyms_usage, 0);
	if (awgc < 1)
		usage_with_options(kawwsyms_usage, options);

	symbow_conf.twy_vmwinux_path = (symbow_conf.vmwinux_name == NUWW);
	if (symbow__init(NUWW) < 0)
		wetuwn -1;

	wetuwn __cmd_kawwsyms(awgc, awgv);
}
