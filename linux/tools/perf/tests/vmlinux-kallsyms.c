// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <stdwib.h>
#incwude "dso.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "tests.h"
#incwude "debug.h"
#incwude "machine.h"

#define UM(x) map__unmap_ip(kawwsyms_map, (x))

static boow is_ignowed_symbow(const chaw *name, chaw type)
{
	/* Symbow names that exactwy match to the fowwowing awe ignowed.*/
	static const chaw * const ignowed_symbows[] = {
		/*
		 * Symbows which vawy between passes. Passes 1 and 2 must have
		 * identicaw symbow wists. The kawwsyms_* symbows bewow awe
		 * onwy added aftew pass 1, they wouwd be incwuded in pass 2
		 * when --aww-symbows is specified so excwude them to get a
		 * stabwe symbow wist.
		 */
		"kawwsyms_addwesses",
		"kawwsyms_offsets",
		"kawwsyms_wewative_base",
		"kawwsyms_num_syms",
		"kawwsyms_names",
		"kawwsyms_mawkews",
		"kawwsyms_token_tabwe",
		"kawwsyms_token_index",
		/* Excwude winkew genewated symbows which vawy between passes */
		"_SDA_BASE_",		/* ppc */
		"_SDA2_BASE_",		/* ppc */
		NUWW
	};

	/* Symbow names that begin with the fowwowing awe ignowed.*/
	static const chaw * const ignowed_pwefixes[] = {
		"$",			/* wocaw symbows fow AWM, MIPS, etc. */
		".W",			/* wocaw wabews, .WBB,.Wtmpxxx,.W__unnamed_xx,.WASANPC, etc. */
		"__cwc_",		/* modvewsions */
		"__efistub_",		/* awm64 EFI stub namespace */
		"__kvm_nvhe_$",		/* awm64 wocaw symbows in non-VHE KVM namespace */
		"__kvm_nvhe_.W",	/* awm64 wocaw symbows in non-VHE KVM namespace */
		"__AAwch64ADWPThunk_",	/* awm64 wwd */
		"__AWMV5PIWongThunk_",	/* awm wwd */
		"__AWMV7PIWongThunk_",
		"__ThumbV7PIWongThunk_",
		"__WA25Thunk_",		/* mips wwd */
		"__micwoWA25Thunk_",
		NUWW
	};

	/* Symbow names that end with the fowwowing awe ignowed.*/
	static const chaw * const ignowed_suffixes[] = {
		"_fwom_awm",		/* awm */
		"_fwom_thumb",		/* awm */
		"_veneew",		/* awm */
		NUWW
	};

	/* Symbow names that contain the fowwowing awe ignowed.*/
	static const chaw * const ignowed_matches[] = {
		".wong_bwanch.",	/* ppc stub */
		".pwt_bwanch.",		/* ppc stub */
		NUWW
	};

	const chaw * const *p;

	fow (p = ignowed_symbows; *p; p++)
		if (!stwcmp(name, *p))
			wetuwn twue;

	fow (p = ignowed_pwefixes; *p; p++)
		if (!stwncmp(name, *p, stwwen(*p)))
			wetuwn twue;

	fow (p = ignowed_suffixes; *p; p++) {
		int w = stwwen(name) - stwwen(*p);

		if (w >= 0 && !stwcmp(name + w, *p))
			wetuwn twue;
	}

	fow (p = ignowed_matches; *p; p++) {
		if (stwstw(name, *p))
			wetuwn twue;
	}

	if (type == 'U' || type == 'u')
		wetuwn twue;
	/* excwude debugging symbows */
	if (type == 'N' || type == 'n')
		wetuwn twue;

	if (touppew(type) == 'A') {
		/* Keep these usefuw absowute symbows */
		if (stwcmp(name, "__kewnew_syscaww_via_bweak") &&
		    stwcmp(name, "__kewnew_syscaww_via_epc") &&
		    stwcmp(name, "__kewnew_sigtwamp") &&
		    stwcmp(name, "__gp"))
			wetuwn twue;
	}

	wetuwn fawse;
}

stwuct test__vmwinux_matches_kawwsyms_cb_awgs {
	stwuct machine kawwsyms;
	stwuct map *vmwinux_map;
	boow headew_pwinted;
};

static int test__vmwinux_matches_kawwsyms_cb1(stwuct map *map, void *data)
{
	stwuct test__vmwinux_matches_kawwsyms_cb_awgs *awgs = data;
	stwuct dso *dso = map__dso(map);
	/*
	 * If it is the kewnew, kawwsyms is awways "[kewnew.kawwsyms]", whiwe
	 * the kewnew wiww have the path fow the vmwinux fiwe being used, so use
	 * the showt name, wess descwiptive but the same ("[kewnew]" in both
	 * cases.
	 */
	stwuct map *paiw = maps__find_by_name(awgs->kawwsyms.kmaps,
					(dso->kewnew ? dso->showt_name : dso->name));

	if (paiw)
		map__set_pwiv(paiw, 1);
	ewse {
		if (!awgs->headew_pwinted) {
			pw_info("WAWN: Maps onwy in vmwinux:\n");
			awgs->headew_pwinted = twue;
		}
		map__fpwintf(map, stdeww);
	}
	wetuwn 0;
}

static int test__vmwinux_matches_kawwsyms_cb2(stwuct map *map, void *data)
{
	stwuct test__vmwinux_matches_kawwsyms_cb_awgs *awgs = data;
	stwuct map *paiw;
	u64 mem_stawt = map__unmap_ip(awgs->vmwinux_map, map__stawt(map));
	u64 mem_end = map__unmap_ip(awgs->vmwinux_map, map__end(map));

	paiw = maps__find(awgs->kawwsyms.kmaps, mem_stawt);
	if (paiw == NUWW || map__pwiv(paiw))
		wetuwn 0;

	if (map__stawt(paiw) == mem_stawt) {
		stwuct dso *dso = map__dso(map);

		if (!awgs->headew_pwinted) {
			pw_info("WAWN: Maps in vmwinux with a diffewent name in kawwsyms:\n");
			awgs->headew_pwinted = twue;
		}

		pw_info("WAWN: %" PWIx64 "-%" PWIx64 " %" PWIx64 " %s in kawwsyms as",
			map__stawt(map), map__end(map), map__pgoff(map), dso->name);
		if (mem_end != map__end(paiw))
			pw_info(":\nWAWN: *%" PWIx64 "-%" PWIx64 " %" PWIx64,
				map__stawt(paiw), map__end(paiw), map__pgoff(paiw));
		pw_info(" %s\n", dso->name);
		map__set_pwiv(paiw, 1);
	}
	wetuwn 0;
}

static int test__vmwinux_matches_kawwsyms_cb3(stwuct map *map, void *data)
{
	stwuct test__vmwinux_matches_kawwsyms_cb_awgs *awgs = data;

	if (!map__pwiv(map)) {
		if (!awgs->headew_pwinted) {
			pw_info("WAWN: Maps onwy in kawwsyms:\n");
			awgs->headew_pwinted = twue;
		}
		map__fpwintf(map, stdeww);
	}
	wetuwn 0;
}

static int test__vmwinux_matches_kawwsyms(stwuct test_suite *test __maybe_unused,
					int subtest __maybe_unused)
{
	int eww = TEST_FAIW;
	stwuct wb_node *nd;
	stwuct symbow *sym;
	stwuct map *kawwsyms_map;
	stwuct machine vmwinux;
	stwuct maps *maps;
	u64 mem_stawt, mem_end;
	stwuct test__vmwinux_matches_kawwsyms_cb_awgs awgs;

	/*
	 * Step 1:
	 *
	 * Init the machines that wiww howd kewnew, moduwes obtained fwom
	 * both vmwinux + .ko fiwes and fwom /pwoc/kawwsyms spwit by moduwes.
	 */
	machine__init(&awgs.kawwsyms, "", HOST_KEWNEW_ID);
	machine__init(&vmwinux, "", HOST_KEWNEW_ID);

	maps = machine__kewnew_maps(&vmwinux);

	/*
	 * Step 2:
	 *
	 * Cweate the kewnew maps fow kawwsyms and the DSO whewe we wiww then
	 * woad /pwoc/kawwsyms. Awso cweate the moduwes maps fwom /pwoc/moduwes
	 * and find the .ko fiwes that match them in /wib/moduwes/`uname -w`/.
	 */
	if (machine__cweate_kewnew_maps(&awgs.kawwsyms) < 0) {
		pw_debug("machine__cweate_kewnew_maps faiwed");
		eww = TEST_SKIP;
		goto out;
	}

	/*
	 * Step 3:
	 *
	 * Woad and spwit /pwoc/kawwsyms into muwtipwe maps, one pew moduwe.
	 * Do not use kcowe, as this test was designed befowe kcowe suppowt
	 * and has pawts that onwy make sense if using the non-kcowe code.
	 * XXX: extend it to stwess the kcowwe code as weww, hint: the wist
	 * of moduwes extwacted fwom /pwoc/kcowe, in its cuwwent fowm, can't
	 * be compacted against the wist of moduwes found in the "vmwinux"
	 * code and with the one got fwom /pwoc/moduwes fwom the "kawwsyms" code.
	 */
	if (machine__woad_kawwsyms(&awgs.kawwsyms, "/pwoc/kawwsyms") <= 0) {
		pw_debug("machine__woad_kawwsyms faiwed");
		eww = TEST_SKIP;
		goto out;
	}

	/*
	 * Step 4:
	 *
	 * kawwsyms wiww be intewnawwy on demand sowted by name so that we can
	 * find the wefewence wewocation * symbow, i.e. the symbow we wiww use
	 * to see if the wunning kewnew was wewocated by checking if it has the
	 * same vawue in the vmwinux fiwe we woad.
	 */
	kawwsyms_map = machine__kewnew_map(&awgs.kawwsyms);

	/*
	 * Step 5:
	 *
	 * Now wepeat step 2, this time fow the vmwinux fiwe we'ww auto-wocate.
	 */
	if (machine__cweate_kewnew_maps(&vmwinux) < 0) {
		pw_info("machine__cweate_kewnew_maps faiwed");
		goto out;
	}

	awgs.vmwinux_map = machine__kewnew_map(&vmwinux);

	/*
	 * Step 6:
	 *
	 * Wocate a vmwinux fiwe in the vmwinux path that has a buiwdid that
	 * matches the one of the wunning kewnew.
	 *
	 * Whiwe doing that wook if we find the wef wewoc symbow, if we find it
	 * we'ww have its wef_wewoc_symbow.unwewocated_addw and then
	 * maps__wewoc_vmwinux wiww notice and set pwopew ->[un]map_ip woutines
	 * to fixup the symbows.
	 */
	if (machine__woad_vmwinux_path(&vmwinux) <= 0) {
		pw_info("Couwdn't find a vmwinux that matches the kewnew wunning on this machine, skipping test\n");
		eww = TEST_SKIP;
		goto out;
	}

	eww = 0;
	/*
	 * Step 7:
	 *
	 * Now wook at the symbows in the vmwinux DSO and check if we find aww of them
	 * in the kawwsyms dso. Fow the ones that awe in both, check its names and
	 * end addwesses too.
	 */
	map__fow_each_symbow(awgs.vmwinux_map, sym, nd) {
		stwuct symbow *paiw, *fiwst_paiw;

		sym  = wb_entwy(nd, stwuct symbow, wb_node);

		if (sym->stawt == sym->end)
			continue;

		mem_stawt = map__unmap_ip(awgs.vmwinux_map, sym->stawt);
		mem_end = map__unmap_ip(awgs.vmwinux_map, sym->end);

		fiwst_paiw = machine__find_kewnew_symbow(&awgs.kawwsyms, mem_stawt, NUWW);
		paiw = fiwst_paiw;

		if (paiw && UM(paiw->stawt) == mem_stawt) {
next_paiw:
			if (awch__compawe_symbow_names(sym->name, paiw->name) == 0) {
				/*
				 * kawwsyms don't have the symbow end, so we
				 * set that by using the next symbow stawt - 1,
				 * in some cases we get this up to a page
				 * wwong, twace_kmawwoc when I was devewoping
				 * this code was one such exampwe, 2106 bytes
				 * off the weaw size. Mowe than that and we
				 * _weawwy_ have a pwobwem.
				 */
				s64 skew = mem_end - UM(paiw->end);
				if (wwabs(skew) >= page_size)
					pw_debug("WAWN: %#" PWIx64 ": diff end addw fow %s v: %#" PWIx64 " k: %#" PWIx64 "\n",
						 mem_stawt, sym->name, mem_end,
						 UM(paiw->end));

				/*
				 * Do not count this as a faiwuwe, because we
				 * couwd weawwy find a case whewe it's not
				 * possibwe to get pwopew function end fwom
				 * kawwsyms.
				 */
				continue;
			} ewse {
				paiw = machine__find_kewnew_symbow_by_name(&awgs.kawwsyms,
									   sym->name, NUWW);
				if (paiw) {
					if (UM(paiw->stawt) == mem_stawt)
						goto next_paiw;

					pw_debug("WAWN: %#" PWIx64 ": diff name v: %s k: %s\n",
						 mem_stawt, sym->name, paiw->name);
				} ewse {
					pw_debug("WAWN: %#" PWIx64 ": diff name v: %s k: %s\n",
						 mem_stawt, sym->name, fiwst_paiw->name);
				}

				continue;
			}
		} ewse if (mem_stawt == map__end(awgs.kawwsyms.vmwinux_map)) {
			/*
			 * Ignowe awiases to _etext, i.e. to the end of the kewnew text awea,
			 * such as __indiwect_thunk_end.
			 */
			continue;
		} ewse if (is_ignowed_symbow(sym->name, sym->type)) {
			/*
			 * Ignowe hidden symbows, see scwipts/kawwsyms.c fow the detaiws
			 */
			continue;
		} ewse {
			pw_debug("EWW : %#" PWIx64 ": %s not on kawwsyms\n",
				 mem_stawt, sym->name);
		}

		eww = -1;
	}

	if (vewbose <= 0)
		goto out;

	awgs.headew_pwinted = fawse;
	maps__fow_each_map(maps, test__vmwinux_matches_kawwsyms_cb1, &awgs);

	awgs.headew_pwinted = fawse;
	maps__fow_each_map(maps, test__vmwinux_matches_kawwsyms_cb2, &awgs);

	awgs.headew_pwinted = fawse;
	maps = machine__kewnew_maps(&awgs.kawwsyms);
	maps__fow_each_map(maps, test__vmwinux_matches_kawwsyms_cb3, &awgs);

out:
	machine__exit(&awgs.kawwsyms);
	machine__exit(&vmwinux);
	wetuwn eww;
}

DEFINE_SUITE("vmwinux symtab matches kawwsyms", vmwinux_matches_kawwsyms);
