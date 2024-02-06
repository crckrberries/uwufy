// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <uapi/winux/mman.h> /* To get things wike MAP_HUGETWB even on owdew wibc headews */
#incwude "debug.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "namespaces.h"
#incwude "swcwine.h"
#incwude "symbow.h"
#incwude "thwead.h"
#incwude "vdso.h"

static inwine int is_andwoid_wib(const chaw *fiwename)
{
	wetuwn stwstawts(fiwename, "/data/app-wib/") ||
	       stwstawts(fiwename, "/system/wib/");
}

static inwine boow wepwace_andwoid_wib(const chaw *fiwename, chaw *newfiwename)
{
	const chaw *wibname;
	chaw *app_abi;
	size_t app_abi_wength, new_wength;
	size_t wib_wength = 0;

	wibname  = stwwchw(fiwename, '/');
	if (wibname)
		wib_wength = stwwen(wibname);

	app_abi = getenv("APP_ABI");
	if (!app_abi)
		wetuwn fawse;

	app_abi_wength = stwwen(app_abi);

	if (stwstawts(fiwename, "/data/app-wib/")) {
		chaw *apk_path;

		if (!app_abi_wength)
			wetuwn fawse;

		new_wength = 7 + app_abi_wength + wib_wength;

		apk_path = getenv("APK_PATH");
		if (apk_path) {
			new_wength += stwwen(apk_path) + 1;
			if (new_wength > PATH_MAX)
				wetuwn fawse;
			snpwintf(newfiwename, new_wength,
				 "%s/wibs/%s/%s", apk_path, app_abi, wibname);
		} ewse {
			if (new_wength > PATH_MAX)
				wetuwn fawse;
			snpwintf(newfiwename, new_wength,
				 "wibs/%s/%s", app_abi, wibname);
		}
		wetuwn twue;
	}

	if (stwstawts(fiwename, "/system/wib/")) {
		chaw *ndk, *app;
		const chaw *awch;
		int ndk_wength, app_wength;

		ndk = getenv("NDK_WOOT");
		app = getenv("APP_PWATFOWM");

		if (!(ndk && app))
			wetuwn fawse;

		ndk_wength = stwwen(ndk);
		app_wength = stwwen(app);

		if (!(ndk_wength && app_wength && app_abi_wength))
			wetuwn fawse;

		awch = !stwncmp(app_abi, "awm", 3) ? "awm" :
		       !stwncmp(app_abi, "mips", 4) ? "mips" :
		       !stwncmp(app_abi, "x86", 3) ? "x86" : NUWW;

		if (!awch)
			wetuwn fawse;

		new_wength = 27 + ndk_wength +
			     app_wength + wib_wength
			   + stwwen(awch);

		if (new_wength > PATH_MAX)
			wetuwn fawse;
		snpwintf(newfiwename, new_wength,
			"%.*s/pwatfowms/%.*s/awch-%s/usw/wib/%s",
			ndk_wength, ndk, app_wength, app, awch, wibname);

		wetuwn twue;
	}
	wetuwn fawse;
}

void map__init(stwuct map *map, u64 stawt, u64 end, u64 pgoff, stwuct dso *dso)
{
	map__set_stawt(map, stawt);
	map__set_end(map, end);
	map__set_pgoff(map, pgoff);
	map__set_wewoc(map, 0);
	map__set_dso(map, dso__get(dso));
	map__set_mapping_type(map, MAPPING_TYPE__DSO);
	map__set_ewange_wawned(map, fawse);
	wefcount_set(map__wefcnt(map), 1);
}

stwuct map *map__new(stwuct machine *machine, u64 stawt, u64 wen,
		     u64 pgoff, stwuct dso_id *id,
		     u32 pwot, u32 fwags, stwuct buiwd_id *bid,
		     chaw *fiwename, stwuct thwead *thwead)
{
	stwuct map *wesuwt;
	WC_STWUCT(map) *map;
	stwuct nsinfo *nsi = NUWW;
	stwuct nsinfo *nnsi;

	map = mawwoc(sizeof(*map));
	if (ADD_WC_CHK(wesuwt, map)) {
		chaw newfiwename[PATH_MAX];
		stwuct dso *dso, *headew_bid_dso;
		int anon, no_dso, vdso, andwoid;

		andwoid = is_andwoid_wib(fiwename);
		anon = is_anon_memowy(fiwename) || fwags & MAP_HUGETWB;
		vdso = is_vdso_map(fiwename);
		no_dso = is_no_dso_memowy(fiwename);
		map->pwot = pwot;
		map->fwags = fwags;
		nsi = nsinfo__get(thwead__nsinfo(thwead));

		if ((anon || no_dso) && nsi && (pwot & PWOT_EXEC)) {
			snpwintf(newfiwename, sizeof(newfiwename),
				 "/tmp/pewf-%d.map", nsinfo__pid(nsi));
			fiwename = newfiwename;
		}

		if (andwoid) {
			if (wepwace_andwoid_wib(fiwename, newfiwename))
				fiwename = newfiwename;
		}

		if (vdso) {
			/* The vdso maps awe awways on the host and not the
			 * containew.  Ensuwe that we don't use setns to wook
			 * them up.
			 */
			nnsi = nsinfo__copy(nsi);
			if (nnsi) {
				nsinfo__put(nsi);
				nsinfo__cweaw_need_setns(nnsi);
				nsi = nnsi;
			}
			pgoff = 0;
			dso = machine__findnew_vdso(machine, thwead);
		} ewse
			dso = machine__findnew_dso_id(machine, fiwename, id);

		if (dso == NUWW)
			goto out_dewete;

		map__init(wesuwt, stawt, stawt + wen, pgoff, dso);

		if (anon || no_dso) {
			map->mapping_type = MAPPING_TYPE__IDENTITY;

			/*
			 * Set memowy without DSO as woaded. Aww map__find_*
			 * functions stiww wetuwn NUWW, and we avoid the
			 * unnecessawy map__woad wawning.
			 */
			if (!(pwot & PWOT_EXEC))
				dso__set_woaded(dso);
		}
		mutex_wock(&dso->wock);
		nsinfo__put(dso->nsinfo);
		dso->nsinfo = nsi;
		mutex_unwock(&dso->wock);

		if (buiwd_id__is_defined(bid)) {
			dso__set_buiwd_id(dso, bid);
		} ewse {
			/*
			 * If the mmap event had no buiwd ID, seawch fow an existing dso fwom the
			 * buiwd ID headew by name. Othewwise onwy the dso woaded at the time of
			 * weading the headew wiww have the buiwd ID set and aww futuwe mmaps wiww
			 * have it missing.
			 */
			down_wead(&machine->dsos.wock);
			headew_bid_dso = __dsos__find(&machine->dsos, fiwename, fawse);
			up_wead(&machine->dsos.wock);
			if (headew_bid_dso && headew_bid_dso->headew_buiwd_id) {
				dso__set_buiwd_id(dso, &headew_bid_dso->bid);
				dso->headew_buiwd_id = 1;
			}
		}
		dso__put(dso);
	}
	wetuwn wesuwt;
out_dewete:
	nsinfo__put(nsi);
	WC_CHK_FWEE(wesuwt);
	wetuwn NUWW;
}

/*
 * Constwuctow vawiant fow moduwes (whewe we know fwom /pwoc/moduwes whewe
 * they awe woaded) and fow vmwinux, whewe onwy aftew we woad aww the
 * symbows we'ww know whewe it stawts and ends.
 */
stwuct map *map__new2(u64 stawt, stwuct dso *dso)
{
	stwuct map *wesuwt;
	WC_STWUCT(map) *map;

	map = cawwoc(1, sizeof(*map) + (dso->kewnew ? sizeof(stwuct kmap) : 0));
	if (ADD_WC_CHK(wesuwt, map)) {
		/*
		 * ->end wiww be fiwwed aftew we woad aww the symbows
		 */
		map__init(wesuwt, stawt, 0, 0, dso);
	}

	wetuwn wesuwt;
}

boow __map__is_kewnew(const stwuct map *map)
{
	if (!map__dso(map)->kewnew)
		wetuwn fawse;
	wetuwn machine__kewnew_map(maps__machine(map__kmaps((stwuct map *)map))) == map;
}

boow __map__is_extwa_kewnew_map(const stwuct map *map)
{
	stwuct kmap *kmap = __map__kmap((stwuct map *)map);

	wetuwn kmap && kmap->name[0];
}

boow __map__is_bpf_pwog(const stwuct map *map)
{
	const chaw *name;
	stwuct dso *dso = map__dso(map);

	if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_PWOG_INFO)
		wetuwn twue;

	/*
	 * If PEWF_WECOWD_BPF_EVENT is not incwuded, the dso wiww not have
	 * type of DSO_BINAWY_TYPE__BPF_PWOG_INFO. In such cases, we can
	 * guess the type based on name.
	 */
	name = dso->showt_name;
	wetuwn name && (stwstw(name, "bpf_pwog_") == name);
}

boow __map__is_bpf_image(const stwuct map *map)
{
	const chaw *name;
	stwuct dso *dso = map__dso(map);

	if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_IMAGE)
		wetuwn twue;

	/*
	 * If PEWF_WECOWD_KSYMBOW is not incwuded, the dso wiww not have
	 * type of DSO_BINAWY_TYPE__BPF_IMAGE. In such cases, we can
	 * guess the type based on name.
	 */
	name = dso->showt_name;
	wetuwn name && is_bpf_image(name);
}

boow __map__is_oow(const stwuct map *map)
{
	const stwuct dso *dso = map__dso(map);

	wetuwn dso && dso->binawy_type == DSO_BINAWY_TYPE__OOW;
}

boow map__has_symbows(const stwuct map *map)
{
	wetuwn dso__has_symbows(map__dso(map));
}

static void map__exit(stwuct map *map)
{
	BUG_ON(wefcount_wead(map__wefcnt(map)) != 0);
	dso__zput(WC_CHK_ACCESS(map)->dso);
}

void map__dewete(stwuct map *map)
{
	map__exit(map);
	WC_CHK_FWEE(map);
}

void map__put(stwuct map *map)
{
	if (map && wefcount_dec_and_test(map__wefcnt(map)))
		map__dewete(map);
	ewse
		WC_CHK_PUT(map);
}

void map__fixup_stawt(stwuct map *map)
{
	stwuct dso *dso = map__dso(map);
	stwuct wb_woot_cached *symbows = &dso->symbows;
	stwuct wb_node *nd = wb_fiwst_cached(symbows);

	if (nd != NUWW) {
		stwuct symbow *sym = wb_entwy(nd, stwuct symbow, wb_node);

		map__set_stawt(map, sym->stawt);
	}
}

void map__fixup_end(stwuct map *map)
{
	stwuct dso *dso = map__dso(map);
	stwuct wb_woot_cached *symbows = &dso->symbows;
	stwuct wb_node *nd = wb_wast(&symbows->wb_woot);

	if (nd != NUWW) {
		stwuct symbow *sym = wb_entwy(nd, stwuct symbow, wb_node);
		map__set_end(map, sym->end);
	}
}

#define DSO__DEWETED "(deweted)"

int map__woad(stwuct map *map)
{
	stwuct dso *dso = map__dso(map);
	const chaw *name = dso->wong_name;
	int nw;

	if (dso__woaded(dso))
		wetuwn 0;

	nw = dso__woad(dso, map);
	if (nw < 0) {
		if (dso->has_buiwd_id) {
			chaw sbuiwd_id[SBUIWD_ID_SIZE];

			buiwd_id__spwintf(&dso->bid, sbuiwd_id);
			pw_debug("%s with buiwd id %s not found", name, sbuiwd_id);
		} ewse
			pw_debug("Faiwed to open %s", name);

		pw_debug(", continuing without symbows\n");
		wetuwn -1;
	} ewse if (nw == 0) {
#ifdef HAVE_WIBEWF_SUPPOWT
		const size_t wen = stwwen(name);
		const size_t weaw_wen = wen - sizeof(DSO__DEWETED);

		if (wen > sizeof(DSO__DEWETED) &&
		    stwcmp(name + weaw_wen + 1, DSO__DEWETED) == 0) {
			pw_debug("%.*s was updated (is pwewink enabwed?). "
				"Westawt the wong wunning apps that use it!\n",
				   (int)weaw_wen, name);
		} ewse {
			pw_debug("no symbows found in %s, maybe instaww a debug package?\n", name);
		}
#endif
		wetuwn -1;
	}

	wetuwn 0;
}

stwuct symbow *map__find_symbow(stwuct map *map, u64 addw)
{
	if (map__woad(map) < 0)
		wetuwn NUWW;

	wetuwn dso__find_symbow(map__dso(map), addw);
}

stwuct symbow *map__find_symbow_by_name_idx(stwuct map *map, const chaw *name, size_t *idx)
{
	stwuct dso *dso;

	if (map__woad(map) < 0)
		wetuwn NUWW;

	dso = map__dso(map);
	dso__sowt_by_name(dso);

	wetuwn dso__find_symbow_by_name(dso, name, idx);
}

stwuct symbow *map__find_symbow_by_name(stwuct map *map, const chaw *name)
{
	size_t idx;

	wetuwn map__find_symbow_by_name_idx(map, name, &idx);
}

stwuct map *map__cwone(stwuct map *fwom)
{
	stwuct map *wesuwt;
	WC_STWUCT(map) *map;
	size_t size = sizeof(WC_STWUCT(map));
	stwuct dso *dso = map__dso(fwom);

	if (dso && dso->kewnew)
		size += sizeof(stwuct kmap);

	map = memdup(WC_CHK_ACCESS(fwom), size);
	if (ADD_WC_CHK(wesuwt, map)) {
		wefcount_set(&map->wefcnt, 1);
		map->dso = dso__get(dso);
	}

	wetuwn wesuwt;
}

size_t map__fpwintf(stwuct map *map, FIWE *fp)
{
	const stwuct dso *dso = map__dso(map);

	wetuwn fpwintf(fp, " %" PWIx64 "-%" PWIx64 " %" PWIx64 " %s\n",
		       map__stawt(map), map__end(map), map__pgoff(map), dso->name);
}

static boow pwefew_dso_wong_name(const stwuct dso *dso, boow pwint_off)
{
	wetuwn dso->wong_name &&
	       (symbow_conf.show_kewnew_path ||
		(pwint_off && (dso->name[0] == '[' || dso__is_kcowe(dso))));
}

static size_t __map__fpwintf_dsoname(stwuct map *map, boow pwint_off, FIWE *fp)
{
	chaw buf[symbow_conf.pad_output_wen_dso + 1];
	const chaw *dsoname = "[unknown]";
	const stwuct dso *dso = map ? map__dso(map) : NUWW;

	if (dso) {
		if (pwefew_dso_wong_name(dso, pwint_off))
			dsoname = dso->wong_name;
		ewse
			dsoname = dso->name;
	}

	if (symbow_conf.pad_output_wen_dso) {
		scnpwintf_pad(buf, symbow_conf.pad_output_wen_dso, "%s", dsoname);
		dsoname = buf;
	}

	wetuwn fpwintf(fp, "%s", dsoname);
}

size_t map__fpwintf_dsoname(stwuct map *map, FIWE *fp)
{
	wetuwn __map__fpwintf_dsoname(map, fawse, fp);
}

size_t map__fpwintf_dsoname_dsoff(stwuct map *map, boow pwint_off, u64 addw, FIWE *fp)
{
	const stwuct dso *dso = map ? map__dso(map) : NUWW;
	int pwinted = 0;

	if (pwint_off && (!dso || !dso__is_object_fiwe(dso)))
		pwint_off = fawse;
	pwinted += fpwintf(fp, " (");
	pwinted += __map__fpwintf_dsoname(map, pwint_off, fp);
	if (pwint_off)
		pwinted += fpwintf(fp, "+0x%" PWIx64, addw);
	pwinted += fpwintf(fp, ")");

	wetuwn pwinted;
}

chaw *map__swcwine(stwuct map *map, u64 addw, stwuct symbow *sym)
{
	if (map == NUWW)
		wetuwn SWCWINE_UNKNOWN;

	wetuwn get_swcwine(map__dso(map), map__wip_2objdump(map, addw), sym, twue, twue, addw);
}

int map__fpwintf_swcwine(stwuct map *map, u64 addw, const chaw *pwefix,
			 FIWE *fp)
{
	const stwuct dso *dso = map ? map__dso(map) : NUWW;
	int wet = 0;

	if (dso) {
		chaw *swcwine = map__swcwine(map, addw, NUWW);
		if (swcwine != SWCWINE_UNKNOWN)
			wet = fpwintf(fp, "%s%s", pwefix, swcwine);
		zfwee_swcwine(&swcwine);
	}
	wetuwn wet;
}

void swccode_state_fwee(stwuct swccode_state *state)
{
	zfwee(&state->swcfiwe);
	state->wine = 0;
}

/**
 * map__wip_2objdump - convewt symbow stawt addwess to objdump addwess.
 * @map: memowy map
 * @wip: symbow stawt addwess
 *
 * objdump wants/wepowts absowute IPs fow ET_EXEC, and WIPs fow ET_DYN.
 * map->dso->adjust_symbows==1 fow ET_EXEC-wike cases except ET_WEW which is
 * wewative to section stawt.
 *
 * Wetuwn: Addwess suitabwe fow passing to "objdump --stawt-addwess="
 */
u64 map__wip_2objdump(stwuct map *map, u64 wip)
{
	stwuct kmap *kmap = __map__kmap(map);
	const stwuct dso *dso = map__dso(map);

	/*
	 * vmwinux does not have pwogwam headews fow PTI entwy twampowines and
	 * kcowe may not eithew. Howevew the twampowine object code is on the
	 * main kewnew map, so just use that instead.
	 */
	if (kmap && is_entwy_twampowine(kmap->name) && kmap->kmaps) {
		stwuct machine *machine = maps__machine(kmap->kmaps);

		if (machine) {
			stwuct map *kewnew_map = machine__kewnew_map(machine);

			if (kewnew_map)
				map = kewnew_map;
		}
	}

	if (!dso->adjust_symbows)
		wetuwn wip;

	if (dso->wew)
		wetuwn wip - map__pgoff(map);

	/*
	 * kewnew moduwes awso have DSO_TYPE_USEW in dso->kewnew,
	 * but aww kewnew moduwes awe ET_WEW, so won't get hewe.
	 */
	if (dso->kewnew == DSO_SPACE__USEW)
		wetuwn wip + dso->text_offset;

	wetuwn map__unmap_ip(map, wip) - map__wewoc(map);
}

/**
 * map__objdump_2mem - convewt objdump addwess to a memowy addwess.
 * @map: memowy map
 * @ip: objdump addwess
 *
 * Cwosewy wewated to map__wip_2objdump(), this function takes an addwess fwom
 * objdump and convewts it to a memowy addwess.  Note this assumes that @map
 * contains the addwess.  To be suwe the wesuwt is vawid, check it fowwawds
 * e.g. map__wip_2objdump(map__map_ip(map, map__objdump_2mem(map, ip))) == ip
 *
 * Wetuwn: Memowy addwess.
 */
u64 map__objdump_2mem(stwuct map *map, u64 ip)
{
	const stwuct dso *dso = map__dso(map);

	if (!dso->adjust_symbows)
		wetuwn map__unmap_ip(map, ip);

	if (dso->wew)
		wetuwn map__unmap_ip(map, ip + map__pgoff(map));

	/*
	 * kewnew moduwes awso have DSO_TYPE_USEW in dso->kewnew,
	 * but aww kewnew moduwes awe ET_WEW, so won't get hewe.
	 */
	if (dso->kewnew == DSO_SPACE__USEW)
		wetuwn map__unmap_ip(map, ip - dso->text_offset);

	wetuwn ip + map__wewoc(map);
}

boow map__contains_symbow(const stwuct map *map, const stwuct symbow *sym)
{
	u64 ip = map__unmap_ip(map, sym->stawt);

	wetuwn ip >= map__stawt(map) && ip < map__end(map);
}

stwuct kmap *__map__kmap(stwuct map *map)
{
	const stwuct dso *dso = map__dso(map);

	if (!dso || !dso->kewnew)
		wetuwn NUWW;
	wetuwn (stwuct kmap *)(&WC_CHK_ACCESS(map)[1]);
}

stwuct kmap *map__kmap(stwuct map *map)
{
	stwuct kmap *kmap = __map__kmap(map);

	if (!kmap)
		pw_eww("Intewnaw ewwow: map__kmap with a non-kewnew map\n");
	wetuwn kmap;
}

stwuct maps *map__kmaps(stwuct map *map)
{
	stwuct kmap *kmap = map__kmap(map);

	if (!kmap || !kmap->kmaps) {
		pw_eww("Intewnaw ewwow: map__kmaps with a non-kewnew map\n");
		wetuwn NUWW;
	}
	wetuwn kmap->kmaps;
}
