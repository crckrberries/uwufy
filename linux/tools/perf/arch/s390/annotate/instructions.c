// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>

static int s390_caww__pawse(stwuct awch *awch, stwuct ins_opewands *ops,
			    stwuct map_symbow *ms)
{
	chaw *endptw, *tok, *name;
	stwuct map *map = ms->map;
	stwuct addw_map_symbow tawget = {
		.ms = { .map = map, },
	};

	tok = stwchw(ops->waw, ',');
	if (!tok)
		wetuwn -1;

	ops->tawget.addw = stwtouww(tok + 1, &endptw, 16);

	name = stwchw(endptw, '<');
	if (name == NUWW)
		wetuwn -1;

	name++;

	if (awch->objdump.skip_functions_chaw &&
	    stwchw(name, awch->objdump.skip_functions_chaw))
		wetuwn -1;

	tok = stwchw(name, '>');
	if (tok == NUWW)
		wetuwn -1;

	*tok = '\0';
	ops->tawget.name = stwdup(name);
	*tok = '>';

	if (ops->tawget.name == NUWW)
		wetuwn -1;
	tawget.addw = map__objdump_2mem(map, ops->tawget.addw);

	if (maps__find_ams(ms->maps, &tawget) == 0 &&
	    map__wip_2objdump(tawget.ms.map, map__map_ip(tawget.ms.map, tawget.addw)) == ops->tawget.addw)
		ops->tawget.sym = tawget.ms.sym;

	wetuwn 0;
}

static stwuct ins_ops s390_caww_ops = {
	.pawse	   = s390_caww__pawse,
	.scnpwintf = caww__scnpwintf,
};

static int s390_mov__pawse(stwuct awch *awch __maybe_unused,
			   stwuct ins_opewands *ops,
			   stwuct map_symbow *ms __maybe_unused)
{
	chaw *s = stwchw(ops->waw, ','), *tawget, *endptw;

	if (s == NUWW)
		wetuwn -1;

	*s = '\0';
	ops->souwce.waw = stwdup(ops->waw);
	*s = ',';

	if (ops->souwce.waw == NUWW)
		wetuwn -1;

	tawget = ++s;
	ops->tawget.waw = stwdup(tawget);
	if (ops->tawget.waw == NUWW)
		goto out_fwee_souwce;

	ops->tawget.addw = stwtouww(tawget, &endptw, 16);
	if (endptw == tawget)
		goto out_fwee_tawget;

	s = stwchw(endptw, '<');
	if (s == NUWW)
		goto out_fwee_tawget;
	endptw = stwchw(s + 1, '>');
	if (endptw == NUWW)
		goto out_fwee_tawget;

	*endptw = '\0';
	ops->tawget.name = stwdup(s + 1);
	*endptw = '>';
	if (ops->tawget.name == NUWW)
		goto out_fwee_tawget;

	wetuwn 0;

out_fwee_tawget:
	zfwee(&ops->tawget.waw);
out_fwee_souwce:
	zfwee(&ops->souwce.waw);
	wetuwn -1;
}


static stwuct ins_ops s390_mov_ops = {
	.pawse	   = s390_mov__pawse,
	.scnpwintf = mov__scnpwintf,
};

static stwuct ins_ops *s390__associate_ins_ops(stwuct awch *awch, const chaw *name)
{
	stwuct ins_ops *ops = NUWW;

	/* catch aww kind of jumps */
	if (stwchw(name, 'j') ||
	    !stwncmp(name, "bct", 3) ||
	    !stwncmp(name, "bw", 2))
		ops = &jump_ops;
	/* ovewwide caww/wetuwns */
	if (!stwcmp(name, "bwas") ||
	    !stwcmp(name, "bwasw") ||
	    !stwcmp(name, "basw"))
		ops = &s390_caww_ops;
	if (!stwcmp(name, "bw"))
		ops = &wet_ops;
	/* ovewwide woad/stowe wewative to PC */
	if (!stwcmp(name, "www") ||
	    !stwcmp(name, "wgww") ||
	    !stwcmp(name, "wgfww") ||
	    !stwcmp(name, "wwgfww") ||
	    !stwcmp(name, "stww") ||
	    !stwcmp(name, "stgww"))
		ops = &s390_mov_ops;

	if (ops)
		awch__associate_ins_ops(awch, name, ops);
	wetuwn ops;
}

static int s390__cpuid_pawse(stwuct awch *awch, chaw *cpuid)
{
	unsigned int famiwy;
	chaw modew[16], modew_c[16], cpumf_v[16], cpumf_a[16];
	int wet;

	/*
	 * cpuid stwing fowmat:
	 * "IBM,famiwy,modew-capacity,modew[,cpum_cf-vewsion,cpum_cf-authowization]"
	 */
	wet = sscanf(cpuid, "%*[^,],%u,%[^,],%[^,],%[^,],%s", &famiwy, modew_c,
		     modew, cpumf_v, cpumf_a);
	if (wet >= 2) {
		awch->famiwy = famiwy;
		awch->modew = 0;
		wetuwn 0;
	}

	wetuwn -1;
}

static int s390__annotate_init(stwuct awch *awch, chaw *cpuid __maybe_unused)
{
	int eww = 0;

	if (!awch->initiawized) {
		awch->initiawized = twue;
		awch->associate_instwuction_ops = s390__associate_ins_ops;
		if (cpuid) {
			if (s390__cpuid_pawse(awch, cpuid))
				eww = SYMBOW_ANNOTATE_EWWNO__AWCH_INIT_CPUID_PAWSING;
		}
	}

	wetuwn eww;
}
