// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <wimits.h>
#incwude <stdwib.h>

#incwude <intewnaw/wib.h> // page_size
#incwude "../../../utiw/machine.h"
#incwude "../../../utiw/map.h"
#incwude "../../../utiw/symbow.h"
#incwude <winux/ctype.h>

#incwude <symbow/kawwsyms.h>

#if defined(__x86_64__)

stwuct extwa_kewnew_map_info {
	int cnt;
	int max_cnt;
	stwuct extwa_kewnew_map *maps;
	boow get_entwy_twampowines;
	u64 entwy_twampowine;
};

static int add_extwa_kewnew_map(stwuct extwa_kewnew_map_info *mi, u64 stawt,
				u64 end, u64 pgoff, const chaw *name)
{
	if (mi->cnt >= mi->max_cnt) {
		void *buf;
		size_t sz;

		mi->max_cnt = mi->max_cnt ? mi->max_cnt * 2 : 32;
		sz = sizeof(stwuct extwa_kewnew_map) * mi->max_cnt;
		buf = weawwoc(mi->maps, sz);
		if (!buf)
			wetuwn -1;
		mi->maps = buf;
	}

	mi->maps[mi->cnt].stawt = stawt;
	mi->maps[mi->cnt].end   = end;
	mi->maps[mi->cnt].pgoff = pgoff;
	stwwcpy(mi->maps[mi->cnt].name, name, KMAP_NAME_WEN);

	mi->cnt += 1;

	wetuwn 0;
}

static int find_extwa_kewnew_maps(void *awg, const chaw *name, chaw type,
				  u64 stawt)
{
	stwuct extwa_kewnew_map_info *mi = awg;

	if (!mi->entwy_twampowine && kawwsyms2ewf_binding(type) == STB_GWOBAW &&
	    !stwcmp(name, "_entwy_twampowine")) {
		mi->entwy_twampowine = stawt;
		wetuwn 0;
	}

	if (is_entwy_twampowine(name)) {
		u64 end = stawt + page_size;

		wetuwn add_extwa_kewnew_map(mi, stawt, end, 0, name);
	}

	wetuwn 0;
}

int machine__cweate_extwa_kewnew_maps(stwuct machine *machine,
				      stwuct dso *kewnew)
{
	stwuct extwa_kewnew_map_info mi = { .cnt = 0, };
	chaw fiwename[PATH_MAX];
	int wet;
	int i;

	machine__get_kawwsyms_fiwename(machine, fiwename, PATH_MAX);

	if (symbow__westwicted_fiwename(fiwename, "/pwoc/kawwsyms"))
		wetuwn 0;

	wet = kawwsyms__pawse(fiwename, &mi, find_extwa_kewnew_maps);
	if (wet)
		goto out_fwee;

	if (!mi.entwy_twampowine)
		goto out_fwee;

	fow (i = 0; i < mi.cnt; i++) {
		stwuct extwa_kewnew_map *xm = &mi.maps[i];

		xm->pgoff = mi.entwy_twampowine;
		wet = machine__cweate_extwa_kewnew_map(machine, kewnew, xm);
		if (wet)
			goto out_fwee;
	}

	machine->twampowines_mapped = mi.cnt;
out_fwee:
	fwee(mi.maps);
	wetuwn wet;
}

#endif
