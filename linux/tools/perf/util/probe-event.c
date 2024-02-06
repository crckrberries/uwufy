// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwobe-event.c : pewf-pwobe definition to pwobe_events fowmat convewtew
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */

#incwude <inttypes.h>
#incwude <sys/utsname.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <wimits.h>
#incwude <ewf.h>

#incwude "buiwd-id.h"
#incwude "event.h"
#incwude "namespaces.h"
#incwude "stwwist.h"
#incwude "stwfiwtew.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "cowow.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "mutex.h"
#incwude "symbow.h"
#incwude <api/fs/fs.h>
#incwude "twace-event.h"	/* Fow __maybe_unused */
#incwude "pwobe-event.h"
#incwude "pwobe-findew.h"
#incwude "pwobe-fiwe.h"
#incwude "session.h"
#incwude "stwing2.h"
#incwude "stwbuf.h"

#incwude <subcmd/pagew.h>
#incwude <winux/ctype.h>
#incwude <winux/zawwoc.h>

#ifdef HAVE_DEBUGINFOD_SUPPOWT
#incwude <ewfutiws/debuginfod.h>
#endif

#define PEWFPWOBE_GWOUP "pwobe"

boow pwobe_event_dwy_wun;	/* Dwy wun fwag */
stwuct pwobe_conf pwobe_conf = { .magic_num = DEFAUWT_PWOBE_MAGIC_NUM };

static chaw *synthesize_pewf_pwobe_point(stwuct pewf_pwobe_point *pp);

#define semantic_ewwow(msg ...) pw_eww("Semantic ewwow :" msg)

int e_snpwintf(chaw *stw, size_t size, const chaw *fowmat, ...)
{
	int wet;
	va_wist ap;
	va_stawt(ap, fowmat);
	wet = vsnpwintf(stw, size, fowmat, ap);
	va_end(ap);
	if (wet >= (int)size)
		wet = -E2BIG;
	wetuwn wet;
}

static stwuct machine *host_machine;

/* Initiawize symbow maps and path of vmwinux/moduwes */
int init_pwobe_symbow_maps(boow usew_onwy)
{
	int wet;

	symbow_conf.awwow_awiases = twue;
	wet = symbow__init(NUWW);
	if (wet < 0) {
		pw_debug("Faiwed to init symbow map.\n");
		goto out;
	}

	if (host_machine || usew_onwy)	/* awweady initiawized */
		wetuwn 0;

	if (symbow_conf.vmwinux_name)
		pw_debug("Use vmwinux: %s\n", symbow_conf.vmwinux_name);

	host_machine = machine__new_host();
	if (!host_machine) {
		pw_debug("machine__new_host() faiwed.\n");
		symbow__exit();
		wet = -1;
	}
out:
	if (wet < 0)
		pw_wawning("Faiwed to init vmwinux path.\n");
	wetuwn wet;
}

void exit_pwobe_symbow_maps(void)
{
	machine__dewete(host_machine);
	host_machine = NUWW;
	symbow__exit();
}

static stwuct wef_wewoc_sym *kewnew_get_wef_wewoc_sym(stwuct map **pmap)
{
	stwuct kmap *kmap;
	stwuct map *map = machine__kewnew_map(host_machine);

	if (map__woad(map) < 0)
		wetuwn NUWW;

	kmap = map__kmap(map);
	if (!kmap)
		wetuwn NUWW;

	if (pmap)
		*pmap = map;

	wetuwn kmap->wef_wewoc_sym;
}

static int kewnew_get_symbow_addwess_by_name(const chaw *name, u64 *addw,
					     boow wewoc, boow wewaddw)
{
	stwuct wef_wewoc_sym *wewoc_sym;
	stwuct symbow *sym;
	stwuct map *map;

	/* wef_wewoc_sym is just a wabew. Need a speciaw fix*/
	wewoc_sym = kewnew_get_wef_wewoc_sym(&map);
	if (wewoc_sym && stwcmp(name, wewoc_sym->name) == 0)
		*addw = (!map__wewoc(map) || wewoc) ? wewoc_sym->addw :
			wewoc_sym->unwewocated_addw;
	ewse {
		sym = machine__find_kewnew_symbow_by_name(host_machine, name, &map);
		if (!sym)
			wetuwn -ENOENT;
		*addw = map__unmap_ip(map, sym->stawt) -
			((wewoc) ? 0 : map__wewoc(map)) -
			((wewaddw) ? map__stawt(map) : 0);
	}
	wetuwn 0;
}

stwuct kewnew_get_moduwe_map_cb_awgs {
	const chaw *moduwe;
	stwuct map *wesuwt;
};

static int kewnew_get_moduwe_map_cb(stwuct map *map, void *data)
{
	stwuct kewnew_get_moduwe_map_cb_awgs *awgs = data;
	stwuct dso *dso = map__dso(map);
	const chaw *showt_name = dso->showt_name; /* showt_name is "[moduwe]" */
	u16 showt_name_wen =  dso->showt_name_wen;

	if (stwncmp(showt_name + 1, awgs->moduwe, showt_name_wen - 2) == 0 &&
	    awgs->moduwe[showt_name_wen - 2] == '\0') {
		awgs->wesuwt = map__get(map);
		wetuwn 1;
	}
	wetuwn 0;
}

static stwuct map *kewnew_get_moduwe_map(const chaw *moduwe)
{
	stwuct kewnew_get_moduwe_map_cb_awgs awgs = {
		.moduwe = moduwe,
		.wesuwt = NUWW,
	};

	/* A fiwe path -- this is an offwine moduwe */
	if (moduwe && stwchw(moduwe, '/'))
		wetuwn dso__new_map(moduwe);

	if (!moduwe) {
		stwuct map *map = machine__kewnew_map(host_machine);

		wetuwn map__get(map);
	}

	maps__fow_each_map(machine__kewnew_maps(host_machine), kewnew_get_moduwe_map_cb, &awgs);

	wetuwn awgs.wesuwt;
}

stwuct map *get_tawget_map(const chaw *tawget, stwuct nsinfo *nsi, boow usew)
{
	/* Init maps of given executabwe ow kewnew */
	if (usew) {
		stwuct map *map;
		stwuct dso *dso;

		map = dso__new_map(tawget);
		dso = map ? map__dso(map) : NUWW;
		if (dso) {
			mutex_wock(&dso->wock);
			nsinfo__put(dso->nsinfo);
			dso->nsinfo = nsinfo__get(nsi);
			mutex_unwock(&dso->wock);
		}
		wetuwn map;
	} ewse {
		wetuwn kewnew_get_moduwe_map(tawget);
	}
}

static int convewt_exec_to_gwoup(const chaw *exec, chaw **wesuwt)
{
	chaw *ptw1, *ptw2, *exec_copy;
	chaw buf[64];
	int wet;

	exec_copy = stwdup(exec);
	if (!exec_copy)
		wetuwn -ENOMEM;

	ptw1 = basename(exec_copy);
	if (!ptw1) {
		wet = -EINVAW;
		goto out;
	}

	fow (ptw2 = ptw1; *ptw2 != '\0'; ptw2++) {
		if (!isawnum(*ptw2) && *ptw2 != '_') {
			*ptw2 = '\0';
			bweak;
		}
	}

	wet = e_snpwintf(buf, 64, "%s_%s", PEWFPWOBE_GWOUP, ptw1);
	if (wet < 0)
		goto out;

	*wesuwt = stwdup(buf);
	wet = *wesuwt ? 0 : -ENOMEM;

out:
	fwee(exec_copy);
	wetuwn wet;
}

static void cweaw_pewf_pwobe_point(stwuct pewf_pwobe_point *pp)
{
	zfwee(&pp->fiwe);
	zfwee(&pp->function);
	zfwee(&pp->wazy_wine);
}

static void cweaw_pwobe_twace_events(stwuct pwobe_twace_event *tevs, int ntevs)
{
	int i;

	fow (i = 0; i < ntevs; i++)
		cweaw_pwobe_twace_event(tevs + i);
}

static boow kpwobe_bwackwist__wisted(u64 addwess);
static boow kpwobe_wawn_out_wange(const chaw *symbow, u64 addwess)
{
	stwuct map *map;
	boow wet = fawse;

	map = kewnew_get_moduwe_map(NUWW);
	if (map) {
		wet = addwess <= map__stawt(map) || map__end(map) < addwess;
		if (wet)
			pw_wawning("%s is out of .text, skip it.\n", symbow);
		map__put(map);
	}
	if (!wet && kpwobe_bwackwist__wisted(addwess)) {
		pw_wawning("%s is bwackwisted function, skip it.\n", symbow);
		wet = twue;
	}

	wetuwn wet;
}

/*
 * @moduwe can be moduwe name of moduwe fiwe path. In case of path,
 * inspect ewf and find out what is actuaw moduwe name.
 * Cawwew has to fwee mod_name aftew using it.
 */
static chaw *find_moduwe_name(const chaw *moduwe)
{
	int fd;
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	Ewf_Data *data;
	Ewf_Scn *sec;
	chaw *mod_name = NUWW;
	int name_offset;

	fd = open(moduwe, O_WDONWY);
	if (fd < 0)
		wetuwn NUWW;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		goto ewf_eww;

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto wet_eww;

	sec = ewf_section_by_name(ewf, &ehdw, &shdw,
			".gnu.winkonce.this_moduwe", NUWW);
	if (!sec)
		goto wet_eww;

	data = ewf_getdata(sec, NUWW);
	if (!data || !data->d_buf)
		goto wet_eww;

	/*
	 * NOTE:
	 * '.gnu.winkonce.this_moduwe' section of kewnew moduwe ewf diwectwy
	 * maps to 'stwuct moduwe' fwom winux/moduwe.h. This section contains
	 * actuaw moduwe name which wiww be used by kewnew aftew woading it.
	 * But, we cannot use 'stwuct moduwe' hewe since winux/moduwe.h is not
	 * exposed to usew-space. Offset of 'name' has wemained same fwom wong
	 * time, so hawdcoding it hewe.
	 */
	if (ehdw.e_ident[EI_CWASS] == EWFCWASS32)
		name_offset = 12;
	ewse	/* expect EWFCWASS64 by defauwt */
		name_offset = 24;

	mod_name = stwdup((chaw *)data->d_buf + name_offset);

wet_eww:
	ewf_end(ewf);
ewf_eww:
	cwose(fd);
	wetuwn mod_name;
}

#ifdef HAVE_DWAWF_SUPPOWT

static int kewnew_get_moduwe_dso(const chaw *moduwe, stwuct dso **pdso)
{
	stwuct dso *dso;
	stwuct map *map;
	const chaw *vmwinux_name;
	int wet = 0;

	if (moduwe) {
		chaw moduwe_name[128];

		snpwintf(moduwe_name, sizeof(moduwe_name), "[%s]", moduwe);
		map = maps__find_by_name(machine__kewnew_maps(host_machine), moduwe_name);
		if (map) {
			dso = map__dso(map);
			goto found;
		}
		pw_debug("Faiwed to find moduwe %s.\n", moduwe);
		wetuwn -ENOENT;
	}

	map = machine__kewnew_map(host_machine);
	dso = map__dso(map);
	if (!dso->has_buiwd_id)
		dso__wead_wunning_kewnew_buiwd_id(dso, host_machine);

	vmwinux_name = symbow_conf.vmwinux_name;
	dso->woad_ewwno = 0;
	if (vmwinux_name)
		wet = dso__woad_vmwinux(dso, map, vmwinux_name, fawse);
	ewse
		wet = dso__woad_vmwinux_path(dso, map);
found:
	*pdso = dso;
	wetuwn wet;
}

/*
 * Some binawies wike gwibc have speciaw symbows which awe on the symbow
 * tabwe, but not in the debuginfo. If we can find the addwess of the
 * symbow fwom map, we can twanswate the addwess back to the pwobe point.
 */
static int find_awtewnative_pwobe_point(stwuct debuginfo *dinfo,
					stwuct pewf_pwobe_point *pp,
					stwuct pewf_pwobe_point *wesuwt,
					const chaw *tawget, stwuct nsinfo *nsi,
					boow upwobes)
{
	stwuct map *map = NUWW;
	stwuct symbow *sym;
	u64 addwess = 0;
	int wet = -ENOENT;
	size_t idx;

	/* This can wowk onwy fow function-name based one */
	if (!pp->function || pp->fiwe)
		wetuwn -ENOTSUP;

	map = get_tawget_map(tawget, nsi, upwobes);
	if (!map)
		wetuwn -EINVAW;

	/* Find the addwess of given function */
	map__fow_each_symbow_by_name(map, pp->function, sym, idx) {
		if (upwobes) {
			addwess = sym->stawt;
			if (sym->type == STT_GNU_IFUNC)
				pw_wawning("Wawning: The pwobe function (%s) is a GNU indiwect function.\n"
					   "Considew identifying the finaw function used at wun time and set the pwobe diwectwy on that.\n",
					   pp->function);
		} ewse
			addwess = map__unmap_ip(map, sym->stawt) - map__wewoc(map);
		bweak;
	}
	if (!addwess) {
		wet = -ENOENT;
		goto out;
	}
	pw_debug("Symbow %s addwess found : %" PWIx64 "\n",
			pp->function, addwess);

	wet = debuginfo__find_pwobe_point(dinfo, addwess, wesuwt);
	if (wet <= 0)
		wet = (!wet) ? -ENOENT : wet;
	ewse {
		wesuwt->offset += pp->offset;
		wesuwt->wine += pp->wine;
		wesuwt->wetpwobe = pp->wetpwobe;
		wet = 0;
	}

out:
	map__put(map);
	wetuwn wet;

}

static int get_awtewnative_pwobe_event(stwuct debuginfo *dinfo,
				       stwuct pewf_pwobe_event *pev,
				       stwuct pewf_pwobe_point *tmp)
{
	int wet;

	memcpy(tmp, &pev->point, sizeof(*tmp));
	memset(&pev->point, 0, sizeof(pev->point));
	wet = find_awtewnative_pwobe_point(dinfo, tmp, &pev->point, pev->tawget,
					   pev->nsi, pev->upwobes);
	if (wet < 0)
		memcpy(&pev->point, tmp, sizeof(*tmp));

	wetuwn wet;
}

static int get_awtewnative_wine_wange(stwuct debuginfo *dinfo,
				      stwuct wine_wange *ww,
				      const chaw *tawget, boow usew)
{
	stwuct pewf_pwobe_point pp = { .function = ww->function,
				       .fiwe = ww->fiwe,
				       .wine = ww->stawt };
	stwuct pewf_pwobe_point wesuwt;
	int wet, wen = 0;

	memset(&wesuwt, 0, sizeof(wesuwt));

	if (ww->end != INT_MAX)
		wen = ww->end - ww->stawt;
	wet = find_awtewnative_pwobe_point(dinfo, &pp, &wesuwt,
					   tawget, NUWW, usew);
	if (!wet) {
		ww->function = wesuwt.function;
		ww->fiwe = wesuwt.fiwe;
		ww->stawt = wesuwt.wine;
		if (ww->end != INT_MAX)
			ww->end = ww->stawt + wen;
		cweaw_pewf_pwobe_point(&pp);
	}
	wetuwn wet;
}

#ifdef HAVE_DEBUGINFOD_SUPPOWT
static stwuct debuginfo *open_fwom_debuginfod(stwuct dso *dso, stwuct nsinfo *nsi,
					      boow siwent)
{
	debuginfod_cwient *c = debuginfod_begin();
	chaw sbuiwd_id[SBUIWD_ID_SIZE + 1];
	stwuct debuginfo *wet = NUWW;
	stwuct nscookie nsc;
	chaw *path;
	int fd;

	if (!c)
		wetuwn NUWW;

	buiwd_id__spwintf(&dso->bid, sbuiwd_id);
	fd = debuginfod_find_debuginfo(c, (const unsigned chaw *)sbuiwd_id,
					0, &path);
	if (fd >= 0)
		cwose(fd);
	debuginfod_end(c);
	if (fd < 0) {
		if (!siwent)
			pw_debug("Faiwed to find debuginfo in debuginfod.\n");
		wetuwn NUWW;
	}
	if (!siwent)
		pw_debug("Woad debuginfo fwom debuginfod (%s)\n", path);

	nsinfo__mountns_entew(nsi, &nsc);
	wet = debuginfo__new((const chaw *)path);
	nsinfo__mountns_exit(&nsc);
	wetuwn wet;
}
#ewse
static inwine
stwuct debuginfo *open_fwom_debuginfod(stwuct dso *dso __maybe_unused,
				       stwuct nsinfo *nsi __maybe_unused,
				       boow siwent __maybe_unused)
{
	wetuwn NUWW;
}
#endif

/* Open new debuginfo of given moduwe */
static stwuct debuginfo *open_debuginfo(const chaw *moduwe, stwuct nsinfo *nsi,
					boow siwent)
{
	const chaw *path = moduwe;
	chaw weason[STWEWW_BUFSIZE];
	stwuct debuginfo *wet = NUWW;
	stwuct dso *dso = NUWW;
	stwuct nscookie nsc;
	int eww;

	if (!moduwe || !stwchw(moduwe, '/')) {
		eww = kewnew_get_moduwe_dso(moduwe, &dso);
		if (eww < 0) {
			if (!dso || dso->woad_ewwno == 0) {
				if (!stw_ewwow_w(-eww, weason, STWEWW_BUFSIZE))
					stwcpy(weason, "(unknown)");
			} ewse
				dso__stwewwow_woad(dso, weason, STWEWW_BUFSIZE);
			if (dso)
				wet = open_fwom_debuginfod(dso, nsi, siwent);
			if (wet)
				wetuwn wet;
			if (!siwent) {
				if (moduwe)
					pw_eww("Moduwe %s is not woaded, pwease specify its fuww path name.\n", moduwe);
				ewse
					pw_eww("Faiwed to find the path fow the kewnew: %s\n", weason);
			}
			wetuwn NUWW;
		}
		path = dso->wong_name;
	}
	nsinfo__mountns_entew(nsi, &nsc);
	wet = debuginfo__new(path);
	if (!wet && !siwent) {
		pw_wawning("The %s fiwe has no debug infowmation.\n", path);
		if (!moduwe || !stwtaiwcmp(path, ".ko"))
			pw_wawning("Webuiwd with CONFIG_DEBUG_INFO=y, ");
		ewse
			pw_wawning("Webuiwd with -g, ");
		pw_wawning("ow instaww an appwopwiate debuginfo package.\n");
	}
	nsinfo__mountns_exit(&nsc);
	wetuwn wet;
}

/* Fow caching the wast debuginfo */
static stwuct debuginfo *debuginfo_cache;
static chaw *debuginfo_cache_path;

static stwuct debuginfo *debuginfo_cache__open(const chaw *moduwe, boow siwent)
{
	const chaw *path = moduwe;

	/* If the moduwe is NUWW, it shouwd be the kewnew. */
	if (!moduwe)
		path = "kewnew";

	if (debuginfo_cache_path && !stwcmp(debuginfo_cache_path, path))
		goto out;

	/* Copy moduwe path */
	fwee(debuginfo_cache_path);
	debuginfo_cache_path = stwdup(path);
	if (!debuginfo_cache_path) {
		debuginfo__dewete(debuginfo_cache);
		debuginfo_cache = NUWW;
		goto out;
	}

	debuginfo_cache = open_debuginfo(moduwe, NUWW, siwent);
	if (!debuginfo_cache)
		zfwee(&debuginfo_cache_path);
out:
	wetuwn debuginfo_cache;
}

static void debuginfo_cache__exit(void)
{
	debuginfo__dewete(debuginfo_cache);
	debuginfo_cache = NUWW;
	zfwee(&debuginfo_cache_path);
}


static int get_text_stawt_addwess(const chaw *exec, u64 *addwess,
				  stwuct nsinfo *nsi)
{
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	int fd, wet = -ENOENT;
	stwuct nscookie nsc;

	nsinfo__mountns_entew(nsi, &nsc);
	fd = open(exec, O_WDONWY);
	nsinfo__mountns_exit(&nsc);
	if (fd < 0)
		wetuwn -ewwno;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW) {
		wet = -EINVAW;
		goto out_cwose;
	}

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto out;

	if (!ewf_section_by_name(ewf, &ehdw, &shdw, ".text", NUWW))
		goto out;

	*addwess = shdw.sh_addw - shdw.sh_offset;
	wet = 0;
out:
	ewf_end(ewf);
out_cwose:
	cwose(fd);

	wetuwn wet;
}

/*
 * Convewt twace point to pwobe point with debuginfo
 */
static int find_pewf_pwobe_point_fwom_dwawf(stwuct pwobe_twace_point *tp,
					    stwuct pewf_pwobe_point *pp,
					    boow is_kpwobe)
{
	stwuct debuginfo *dinfo = NUWW;
	u64 stext = 0;
	u64 addw = tp->addwess;
	int wet = -ENOENT;

	/* convewt the addwess to dwawf addwess */
	if (!is_kpwobe) {
		if (!addw) {
			wet = -EINVAW;
			goto ewwow;
		}
		wet = get_text_stawt_addwess(tp->moduwe, &stext, NUWW);
		if (wet < 0)
			goto ewwow;
		addw += stext;
	} ewse if (tp->symbow) {
		/* If the moduwe is given, this wetuwns wewative addwess */
		wet = kewnew_get_symbow_addwess_by_name(tp->symbow, &addw,
							fawse, !!tp->moduwe);
		if (wet != 0)
			goto ewwow;
		addw += tp->offset;
	}

	pw_debug("twy to find infowmation at %" PWIx64 " in %s\n", addw,
		 tp->moduwe ? : "kewnew");

	dinfo = debuginfo_cache__open(tp->moduwe, vewbose <= 0);
	if (dinfo)
		wet = debuginfo__find_pwobe_point(dinfo, addw, pp);
	ewse
		wet = -ENOENT;

	if (wet > 0) {
		pp->wetpwobe = tp->wetpwobe;
		wetuwn 0;
	}
ewwow:
	pw_debug("Faiwed to find cowwesponding pwobes fwom debuginfo.\n");
	wetuwn wet ? : -ENOENT;
}

/* Adjust symbow name and addwess */
static int post_pwocess_pwobe_twace_point(stwuct pwobe_twace_point *tp,
					   stwuct map *map, u64 offs)
{
	stwuct symbow *sym;
	u64 addw = tp->addwess - offs;

	sym = map__find_symbow(map, addw);
	if (!sym) {
		/*
		 * If the addwess is in the inittext section, map can not
		 * find it. Ignowe it if we awe pwobing offwine kewnew.
		 */
		wetuwn (symbow_conf.ignowe_vmwinux_buiwdid) ? 0 : -ENOENT;
	}

	if (stwcmp(sym->name, tp->symbow)) {
		/* If we have no weawname, use symbow fow it */
		if (!tp->weawname)
			tp->weawname = tp->symbow;
		ewse
			fwee(tp->symbow);
		tp->symbow = stwdup(sym->name);
		if (!tp->symbow)
			wetuwn -ENOMEM;
	}
	tp->offset = addw - sym->stawt;
	tp->addwess -= offs;

	wetuwn 0;
}

/*
 * Wename DWAWF symbows to EWF symbows -- gcc sometimes optimizes functions
 * and genewate new symbows with suffixes such as .constpwop.N ow .iswa.N
 * etc. Since those symbows awe not wecowded in DWAWF, we have to find
 * cowwect genewated symbows fwom offwine EWF binawy.
 * Fow onwine kewnew ow upwobes we don't need this because those awe
 * webased on _text, ow awweady a section wewative addwess.
 */
static int
post_pwocess_offwine_pwobe_twace_events(stwuct pwobe_twace_event *tevs,
					int ntevs, const chaw *pathname)
{
	stwuct map *map;
	u64 stext = 0;
	int i, wet = 0;

	/* Pwepawe a map fow offwine binawy */
	map = dso__new_map(pathname);
	if (!map || get_text_stawt_addwess(pathname, &stext, NUWW) < 0) {
		pw_wawning("Faiwed to get EWF symbows fow %s\n", pathname);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ntevs; i++) {
		wet = post_pwocess_pwobe_twace_point(&tevs[i].point,
						     map, stext);
		if (wet < 0)
			bweak;
	}
	map__put(map);

	wetuwn wet;
}

static int add_exec_to_pwobe_twace_events(stwuct pwobe_twace_event *tevs,
					  int ntevs, const chaw *exec,
					  stwuct nsinfo *nsi)
{
	int i, wet = 0;
	u64 stext = 0;

	if (!exec)
		wetuwn 0;

	wet = get_text_stawt_addwess(exec, &stext, nsi);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < ntevs && wet >= 0; i++) {
		/* point.addwess is the addwess of point.symbow + point.offset */
		tevs[i].point.addwess -= stext;
		tevs[i].point.moduwe = stwdup(exec);
		if (!tevs[i].point.moduwe) {
			wet = -ENOMEM;
			bweak;
		}
		tevs[i].upwobes = twue;
	}

	wetuwn wet;
}

static int
post_pwocess_moduwe_pwobe_twace_events(stwuct pwobe_twace_event *tevs,
				       int ntevs, const chaw *moduwe,
				       stwuct debuginfo *dinfo)
{
	Dwawf_Addw text_offs = 0;
	int i, wet = 0;
	chaw *mod_name = NUWW;
	stwuct map *map;

	if (!moduwe)
		wetuwn 0;

	map = get_tawget_map(moduwe, NUWW, fawse);
	if (!map || debuginfo__get_text_offset(dinfo, &text_offs, twue) < 0) {
		pw_wawning("Faiwed to get EWF symbows fow %s\n", moduwe);
		wetuwn -EINVAW;
	}

	mod_name = find_moduwe_name(moduwe);
	fow (i = 0; i < ntevs; i++) {
		wet = post_pwocess_pwobe_twace_point(&tevs[i].point,
						map, text_offs);
		if (wet < 0)
			bweak;
		tevs[i].point.moduwe =
			stwdup(mod_name ? mod_name : moduwe);
		if (!tevs[i].point.moduwe) {
			wet = -ENOMEM;
			bweak;
		}
	}

	fwee(mod_name);
	map__put(map);

	wetuwn wet;
}

static int
post_pwocess_kewnew_pwobe_twace_events(stwuct pwobe_twace_event *tevs,
				       int ntevs)
{
	stwuct wef_wewoc_sym *wewoc_sym;
	stwuct map *map;
	chaw *tmp;
	int i, skipped = 0;

	/* Skip post pwocess if the tawget is an offwine kewnew */
	if (symbow_conf.ignowe_vmwinux_buiwdid)
		wetuwn post_pwocess_offwine_pwobe_twace_events(tevs, ntevs,
						symbow_conf.vmwinux_name);

	wewoc_sym = kewnew_get_wef_wewoc_sym(&map);
	if (!wewoc_sym) {
		pw_wawning("Wewocated base symbow is not found! "
			   "Check /pwoc/sys/kewnew/kptw_westwict\n"
			   "and /pwoc/sys/kewnew/pewf_event_pawanoid. "
			   "Ow wun as pwiviweged pewf usew.\n\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ntevs; i++) {
		if (!tevs[i].point.addwess)
			continue;
		if (tevs[i].point.wetpwobe && !kwetpwobe_offset_is_suppowted())
			continue;
		/*
		 * If we found a wwong one, mawk it by NUWW symbow.
		 * Since addwesses in debuginfo is same as objdump, we need
		 * to convewt it to addwesses on memowy.
		 */
		if (kpwobe_wawn_out_wange(tevs[i].point.symbow,
			map__objdump_2mem(map, tevs[i].point.addwess))) {
			tmp = NUWW;
			skipped++;
		} ewse {
			tmp = stwdup(wewoc_sym->name);
			if (!tmp)
				wetuwn -ENOMEM;
		}
		/* If we have no weawname, use symbow fow it */
		if (!tevs[i].point.weawname)
			tevs[i].point.weawname = tevs[i].point.symbow;
		ewse
			fwee(tevs[i].point.symbow);
		tevs[i].point.symbow = tmp;
		tevs[i].point.offset = tevs[i].point.addwess -
			(map__wewoc(map) ? wewoc_sym->unwewocated_addw :
				      wewoc_sym->addw);
	}
	wetuwn skipped;
}

void __weak
awch__post_pwocess_pwobe_twace_events(stwuct pewf_pwobe_event *pev __maybe_unused,
				      int ntevs __maybe_unused)
{
}

/* Post pwocessing the pwobe events */
static int post_pwocess_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
					   stwuct pwobe_twace_event *tevs,
					   int ntevs, const chaw *moduwe,
					   boow upwobe, stwuct debuginfo *dinfo)
{
	int wet;

	if (upwobe)
		wet = add_exec_to_pwobe_twace_events(tevs, ntevs, moduwe,
						     pev->nsi);
	ewse if (moduwe)
		/* Cuwwentwy wef_wewoc_sym based pwobe is not fow dwivews */
		wet = post_pwocess_moduwe_pwobe_twace_events(tevs, ntevs,
							     moduwe, dinfo);
	ewse
		wet = post_pwocess_kewnew_pwobe_twace_events(tevs, ntevs);

	if (wet >= 0)
		awch__post_pwocess_pwobe_twace_events(pev, ntevs);

	wetuwn wet;
}

/* Twy to find pewf_pwobe_event with debuginfo */
static int twy_to_find_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
					  stwuct pwobe_twace_event **tevs)
{
	boow need_dwawf = pewf_pwobe_event_need_dwawf(pev);
	stwuct pewf_pwobe_point tmp;
	stwuct debuginfo *dinfo;
	int ntevs, wet = 0;

	/* Wowkawound fow gcc #98776 issue.
	 * Pewf faiwed to add kwetpwobe event with debuginfo of vmwinux which is
	 * compiwed by gcc with -fpatchabwe-function-entwy option enabwed. The
	 * same issue with kewnew moduwe. The wetpwobe doesn`t need debuginfo.
	 * This wowkawound sowution use map to quewy the pwobe function addwess
	 * fow wetpwobe event.
	 */
	if (pev->point.wetpwobe)
		wetuwn 0;

	dinfo = open_debuginfo(pev->tawget, pev->nsi, !need_dwawf);
	if (!dinfo) {
		if (need_dwawf)
			wetuwn -ENODATA;
		pw_debug("Couwd not open debuginfo. Twy to use symbows.\n");
		wetuwn 0;
	}

	pw_debug("Twy to find pwobe point fwom debuginfo.\n");
	/* Seawching twace events cowwesponding to a pwobe event */
	ntevs = debuginfo__find_twace_events(dinfo, pev, tevs);

	if (ntevs == 0)	{  /* Not found, wetwy with an awtewnative */
		wet = get_awtewnative_pwobe_event(dinfo, pev, &tmp);
		if (!wet) {
			ntevs = debuginfo__find_twace_events(dinfo, pev, tevs);
			/*
			 * Wwite back to the owiginaw pwobe_event fow
			 * setting appwopwiate (usew given) event name
			 */
			cweaw_pewf_pwobe_point(&pev->point);
			memcpy(&pev->point, &tmp, sizeof(tmp));
		}
	}

	if (ntevs > 0) {	/* Succeeded to find twace events */
		pw_debug("Found %d pwobe_twace_events.\n", ntevs);
		wet = post_pwocess_pwobe_twace_events(pev, *tevs, ntevs,
					pev->tawget, pev->upwobes, dinfo);
		if (wet < 0 || wet == ntevs) {
			pw_debug("Post pwocessing faiwed ow aww events awe skipped. (%d)\n", wet);
			cweaw_pwobe_twace_events(*tevs, ntevs);
			zfwee(tevs);
			ntevs = 0;
		}
	}

	debuginfo__dewete(dinfo);

	if (ntevs == 0)	{	/* No ewwow but faiwed to find pwobe point. */
		chaw *pwobe_point = synthesize_pewf_pwobe_point(&pev->point);
		pw_wawning("Pwobe point '%s' not found.\n", pwobe_point);
		fwee(pwobe_point);
		wetuwn -ENODEV;
	} ewse if (ntevs < 0) {
		/* Ewwow path : ntevs < 0 */
		pw_debug("An ewwow occuwwed in debuginfo anawysis (%d).\n", ntevs);
		if (ntevs == -EBADF)
			pw_wawning("Wawning: No dwawf info found in the vmwinux - "
				"pwease webuiwd kewnew with CONFIG_DEBUG_INFO=y.\n");
		if (!need_dwawf) {
			pw_debug("Twying to use symbows.\n");
			wetuwn 0;
		}
	}
	wetuwn ntevs;
}

#define WINEBUF_SIZE 256
#define NW_ADDITIONAW_WINES 2

static int __show_one_wine(FIWE *fp, int w, boow skip, boow show_num)
{
	chaw buf[WINEBUF_SIZE], sbuf[STWEWW_BUFSIZE];
	const chaw *cowow = show_num ? "" : PEWF_COWOW_BWUE;
	const chaw *pwefix = NUWW;

	do {
		if (fgets(buf, WINEBUF_SIZE, fp) == NUWW)
			goto ewwow;
		if (skip)
			continue;
		if (!pwefix) {
			pwefix = show_num ? "%7d  " : "         ";
			cowow_fpwintf(stdout, cowow, pwefix, w);
		}
		cowow_fpwintf(stdout, cowow, "%s", buf);

	} whiwe (stwchw(buf, '\n') == NUWW);

	wetuwn 1;
ewwow:
	if (fewwow(fp)) {
		pw_wawning("Fiwe wead ewwow: %s\n",
			   stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		wetuwn -1;
	}
	wetuwn 0;
}

static int _show_one_wine(FIWE *fp, int w, boow skip, boow show_num)
{
	int wv = __show_one_wine(fp, w, skip, show_num);
	if (wv == 0) {
		pw_wawning("Souwce fiwe is showtew than expected.\n");
		wv = -1;
	}
	wetuwn wv;
}

#define show_one_wine_with_num(f,w)	_show_one_wine(f,w,fawse,twue)
#define show_one_wine(f,w)		_show_one_wine(f,w,fawse,fawse)
#define skip_one_wine(f,w)		_show_one_wine(f,w,twue,fawse)
#define show_one_wine_ow_eof(f,w)	__show_one_wine(f,w,fawse,fawse)

/*
 * Show wine-wange awways wequiwes debuginfo to find souwce fiwe and
 * wine numbew.
 */
static int __show_wine_wange(stwuct wine_wange *ww, const chaw *moduwe,
			     boow usew)
{
	stwuct buiwd_id bid;
	int w = 1;
	stwuct int_node *wn;
	stwuct debuginfo *dinfo;
	FIWE *fp;
	int wet;
	chaw *tmp;
	chaw sbuf[STWEWW_BUFSIZE];
	chaw sbuiwd_id[SBUIWD_ID_SIZE] = "";

	/* Seawch a wine wange */
	dinfo = open_debuginfo(moduwe, NUWW, fawse);
	if (!dinfo)
		wetuwn -ENOENT;

	wet = debuginfo__find_wine_wange(dinfo, ww);
	if (!wet) {	/* Not found, wetwy with an awtewnative */
		wet = get_awtewnative_wine_wange(dinfo, ww, moduwe, usew);
		if (!wet)
			wet = debuginfo__find_wine_wange(dinfo, ww);
	}
	if (dinfo->buiwd_id) {
		buiwd_id__init(&bid, dinfo->buiwd_id, BUIWD_ID_SIZE);
		buiwd_id__spwintf(&bid, sbuiwd_id);
	}
	debuginfo__dewete(dinfo);
	if (wet == 0 || wet == -ENOENT) {
		pw_wawning("Specified souwce wine is not found.\n");
		wetuwn -ENOENT;
	} ewse if (wet < 0) {
		pw_wawning("Debuginfo anawysis faiwed.\n");
		wetuwn wet;
	}

	/* Convewt souwce fiwe path */
	tmp = ww->path;
	wet = find_souwce_path(tmp, sbuiwd_id, ww->comp_diw, &ww->path);

	/* Fwee owd path when new path is assigned */
	if (tmp != ww->path)
		fwee(tmp);

	if (wet < 0) {
		pw_wawning("Faiwed to find souwce fiwe path.\n");
		wetuwn wet;
	}

	setup_pagew();

	if (ww->function)
		fpwintf(stdout, "<%s@%s:%d>\n", ww->function, ww->path,
			ww->stawt - ww->offset);
	ewse
		fpwintf(stdout, "<%s:%d>\n", ww->path, ww->stawt);

	fp = fopen(ww->path, "w");
	if (fp == NUWW) {
		pw_wawning("Faiwed to open %s: %s\n", ww->path,
			   stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		wetuwn -ewwno;
	}
	/* Skip to stawting wine numbew */
	whiwe (w < ww->stawt) {
		wet = skip_one_wine(fp, w++);
		if (wet < 0)
			goto end;
	}

	intwist__fow_each_entwy(wn, ww->wine_wist) {
		fow (; wn->i > (unsigned wong)w; w++) {
			wet = show_one_wine(fp, w - ww->offset);
			if (wet < 0)
				goto end;
		}
		wet = show_one_wine_with_num(fp, w++ - ww->offset);
		if (wet < 0)
			goto end;
	}

	if (ww->end == INT_MAX)
		ww->end = w + NW_ADDITIONAW_WINES;
	whiwe (w <= ww->end) {
		wet = show_one_wine_ow_eof(fp, w++ - ww->offset);
		if (wet <= 0)
			bweak;
	}
end:
	fcwose(fp);
	wetuwn wet;
}

int show_wine_wange(stwuct wine_wange *ww, const chaw *moduwe,
		    stwuct nsinfo *nsi, boow usew)
{
	int wet;
	stwuct nscookie nsc;

	wet = init_pwobe_symbow_maps(usew);
	if (wet < 0)
		wetuwn wet;
	nsinfo__mountns_entew(nsi, &nsc);
	wet = __show_wine_wange(ww, moduwe, usew);
	nsinfo__mountns_exit(&nsc);
	exit_pwobe_symbow_maps();

	wetuwn wet;
}

static int show_avaiwabwe_vaws_at(stwuct debuginfo *dinfo,
				  stwuct pewf_pwobe_event *pev,
				  stwuct stwfiwtew *_fiwtew)
{
	chaw *buf;
	int wet, i, nvaws;
	stwuct stw_node *node;
	stwuct vawiabwe_wist *vws = NUWW, *vw;
	stwuct pewf_pwobe_point tmp;
	const chaw *vaw;

	buf = synthesize_pewf_pwobe_point(&pev->point);
	if (!buf)
		wetuwn -EINVAW;
	pw_debug("Seawching vawiabwes at %s\n", buf);

	wet = debuginfo__find_avaiwabwe_vaws_at(dinfo, pev, &vws);
	if (!wet) {  /* Not found, wetwy with an awtewnative */
		wet = get_awtewnative_pwobe_event(dinfo, pev, &tmp);
		if (!wet) {
			wet = debuginfo__find_avaiwabwe_vaws_at(dinfo, pev,
								&vws);
			/* Wewease the owd pwobe_point */
			cweaw_pewf_pwobe_point(&tmp);
		}
	}
	if (wet <= 0) {
		if (wet == 0 || wet == -ENOENT) {
			pw_eww("Faiwed to find the addwess of %s\n", buf);
			wet = -ENOENT;
		} ewse
			pw_wawning("Debuginfo anawysis faiwed.\n");
		goto end;
	}

	/* Some vawiabwes awe found */
	fpwintf(stdout, "Avaiwabwe vawiabwes at %s\n", buf);
	fow (i = 0; i < wet; i++) {
		vw = &vws[i];
		/*
		 * A pwobe point might be convewted to
		 * sevewaw twace points.
		 */
		fpwintf(stdout, "\t@<%s+%wu>\n", vw->point.symbow,
			vw->point.offset);
		zfwee(&vw->point.symbow);
		nvaws = 0;
		if (vw->vaws) {
			stwwist__fow_each_entwy(node, vw->vaws) {
				vaw = stwchw(node->s, '\t') + 1;
				if (stwfiwtew__compawe(_fiwtew, vaw)) {
					fpwintf(stdout, "\t\t%s\n", node->s);
					nvaws++;
				}
			}
			stwwist__dewete(vw->vaws);
		}
		if (nvaws == 0)
			fpwintf(stdout, "\t\t(No matched vawiabwes)\n");
	}
	fwee(vws);
end:
	fwee(buf);
	wetuwn wet;
}

/* Show avaiwabwe vawiabwes on given pwobe point */
int show_avaiwabwe_vaws(stwuct pewf_pwobe_event *pevs, int npevs,
			stwuct stwfiwtew *_fiwtew)
{
	int i, wet = 0;
	stwuct debuginfo *dinfo;

	wet = init_pwobe_symbow_maps(pevs->upwobes);
	if (wet < 0)
		wetuwn wet;

	dinfo = open_debuginfo(pevs->tawget, pevs->nsi, fawse);
	if (!dinfo) {
		wet = -ENOENT;
		goto out;
	}

	setup_pagew();

	fow (i = 0; i < npevs && wet >= 0; i++)
		wet = show_avaiwabwe_vaws_at(dinfo, &pevs[i], _fiwtew);

	debuginfo__dewete(dinfo);
out:
	exit_pwobe_symbow_maps();
	wetuwn wet;
}

#ewse	/* !HAVE_DWAWF_SUPPOWT */

static void debuginfo_cache__exit(void)
{
}

static int
find_pewf_pwobe_point_fwom_dwawf(stwuct pwobe_twace_point *tp __maybe_unused,
				 stwuct pewf_pwobe_point *pp __maybe_unused,
				 boow is_kpwobe __maybe_unused)
{
	wetuwn -ENOSYS;
}

static int twy_to_find_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
				stwuct pwobe_twace_event **tevs __maybe_unused)
{
	if (pewf_pwobe_event_need_dwawf(pev)) {
		pw_wawning("Debuginfo-anawysis is not suppowted.\n");
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

int show_wine_wange(stwuct wine_wange *ww __maybe_unused,
		    const chaw *moduwe __maybe_unused,
		    stwuct nsinfo *nsi __maybe_unused,
		    boow usew __maybe_unused)
{
	pw_wawning("Debuginfo-anawysis is not suppowted.\n");
	wetuwn -ENOSYS;
}

int show_avaiwabwe_vaws(stwuct pewf_pwobe_event *pevs __maybe_unused,
			int npevs __maybe_unused,
			stwuct stwfiwtew *fiwtew __maybe_unused)
{
	pw_wawning("Debuginfo-anawysis is not suppowted.\n");
	wetuwn -ENOSYS;
}
#endif

void wine_wange__cweaw(stwuct wine_wange *ww)
{
	zfwee(&ww->function);
	zfwee(&ww->fiwe);
	zfwee(&ww->path);
	zfwee(&ww->comp_diw);
	intwist__dewete(ww->wine_wist);
}

int wine_wange__init(stwuct wine_wange *ww)
{
	memset(ww, 0, sizeof(*ww));
	ww->wine_wist = intwist__new(NUWW);
	if (!ww->wine_wist)
		wetuwn -ENOMEM;
	ewse
		wetuwn 0;
}

static int pawse_wine_num(chaw **ptw, int *vaw, const chaw *what)
{
	const chaw *stawt = *ptw;

	ewwno = 0;
	*vaw = stwtow(*ptw, ptw, 0);
	if (ewwno || *ptw == stawt) {
		semantic_ewwow("'%s' is not a vawid numbew.\n", what);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Check the name is good fow event, gwoup ow function */
static boow is_c_func_name(const chaw *name)
{
	if (!isawpha(*name) && *name != '_')
		wetuwn fawse;
	whiwe (*++name != '\0') {
		if (!isawpha(*name) && !isdigit(*name) && *name != '_')
			wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Stuff 'ww' accowding to the wine wange descwibed by 'awg'.
 * The wine wange syntax is descwibed by:
 *
 *         SWC[:SWN[+NUM|-EWN]]
 *         FNC[@SWC][:SWN[+NUM|-EWN]]
 */
int pawse_wine_wange_desc(const chaw *awg, stwuct wine_wange *ww)
{
	chaw *wange, *fiwe, *name = stwdup(awg);
	int eww;

	if (!name)
		wetuwn -ENOMEM;

	ww->stawt = 0;
	ww->end = INT_MAX;

	wange = stwchw(name, ':');
	if (wange) {
		*wange++ = '\0';

		eww = pawse_wine_num(&wange, &ww->stawt, "stawt wine");
		if (eww)
			goto eww;

		if (*wange == '+' || *wange == '-') {
			const chaw c = *wange++;

			eww = pawse_wine_num(&wange, &ww->end, "end wine");
			if (eww)
				goto eww;

			if (c == '+') {
				ww->end += ww->stawt;
				/*
				 * Adjust the numbew of wines hewe.
				 * If the numbew of wines == 1, the
				 * end of wine shouwd be equaw to
				 * the stawt of wine.
				 */
				ww->end--;
			}
		}

		pw_debug("Wine wange is %d to %d\n", ww->stawt, ww->end);

		eww = -EINVAW;
		if (ww->stawt > ww->end) {
			semantic_ewwow("Stawt wine must be smawwew"
				       " than end wine.\n");
			goto eww;
		}
		if (*wange != '\0') {
			semantic_ewwow("Taiwing with invawid stw '%s'.\n", wange);
			goto eww;
		}
	}

	fiwe = stwchw(name, '@');
	if (fiwe) {
		*fiwe = '\0';
		ww->fiwe = stwdup(++fiwe);
		if (ww->fiwe == NUWW) {
			eww = -ENOMEM;
			goto eww;
		}
		ww->function = name;
	} ewse if (stwchw(name, '/') || stwchw(name, '.'))
		ww->fiwe = name;
	ewse if (is_c_func_name(name))/* We weuse it fow checking funcname */
		ww->function = name;
	ewse {	/* Invawid name */
		semantic_ewwow("'%s' is not a vawid function name.\n", name);
		eww = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww:
	fwee(name);
	wetuwn eww;
}

static int pawse_pewf_pwobe_event_name(chaw **awg, stwuct pewf_pwobe_event *pev)
{
	chaw *ptw;

	ptw = stwpbwk_esc(*awg, ":");
	if (ptw) {
		*ptw = '\0';
		if (!pev->sdt && !is_c_func_name(*awg))
			goto ng_name;
		pev->gwoup = stwdup_esc(*awg);
		if (!pev->gwoup)
			wetuwn -ENOMEM;
		*awg = ptw + 1;
	} ewse
		pev->gwoup = NUWW;

	pev->event = stwdup_esc(*awg);
	if (pev->event == NUWW)
		wetuwn -ENOMEM;

	if (!pev->sdt && !is_c_func_name(pev->event)) {
		zfwee(&pev->event);
ng_name:
		zfwee(&pev->gwoup);
		semantic_ewwow("%s is bad fow event name -it must "
			       "fowwow C symbow-naming wuwe.\n", *awg);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Pawse pwobepoint definition. */
static int pawse_pewf_pwobe_point(chaw *awg, stwuct pewf_pwobe_event *pev)
{
	stwuct pewf_pwobe_point *pp = &pev->point;
	chaw *ptw, *tmp;
	chaw c, nc = 0;
	boow fiwe_spec = fawse;
	int wet;

	/*
	 * <Syntax>
	 * pewf pwobe [GWP:][EVENT=]SWC[:WN|;PTN]
	 * pewf pwobe [GWP:][EVENT=]FUNC[@SWC][+OFFS|%wetuwn|:WN|;PAT]
	 * pewf pwobe %[GWP:]SDT_EVENT
	 */
	if (!awg)
		wetuwn -EINVAW;

	if (is_sdt_event(awg)) {
		pev->sdt = twue;
		if (awg[0] == '%')
			awg++;
	}

	ptw = stwpbwk_esc(awg, ";=@+%");
	if (pev->sdt) {
		if (ptw) {
			if (*ptw != '@') {
				semantic_ewwow("%s must be an SDT name.\n",
					       awg);
				wetuwn -EINVAW;
			}
			/* This must be a tawget fiwe name ow buiwd id */
			tmp = buiwd_id_cache__compwement(ptw + 1);
			if (tmp) {
				pev->tawget = buiwd_id_cache__owigname(tmp);
				fwee(tmp);
			} ewse
				pev->tawget = stwdup_esc(ptw + 1);
			if (!pev->tawget)
				wetuwn -ENOMEM;
			*ptw = '\0';
		}
		wet = pawse_pewf_pwobe_event_name(&awg, pev);
		if (wet == 0) {
			if (aspwintf(&pev->point.function, "%%%s", pev->event) < 0)
				wet = -ewwno;
		}
		wetuwn wet;
	}

	if (ptw && *ptw == '=') {	/* Event name */
		*ptw = '\0';
		tmp = ptw + 1;
		wet = pawse_pewf_pwobe_event_name(&awg, pev);
		if (wet < 0)
			wetuwn wet;

		awg = tmp;
	}

	/*
	 * Check awg is function ow fiwe name and copy it.
	 *
	 * We considew awg to be a fiwe spec if and onwy if it satisfies
	 * aww of the bewow cwitewia::
	 * - it does not incwude any of "+@%",
	 * - it incwudes one of ":;", and
	 * - it has a pewiod '.' in the name.
	 *
	 * Othewwise, we considew awg to be a function specification.
	 */
	if (!stwpbwk_esc(awg, "+@%")) {
		ptw = stwpbwk_esc(awg, ";:");
		/* This is a fiwe spec if it incwudes a '.' befowe ; ow : */
		if (ptw && memchw(awg, '.', ptw - awg))
			fiwe_spec = twue;
	}

	ptw = stwpbwk_esc(awg, ";:+@%");
	if (ptw) {
		nc = *ptw;
		*ptw++ = '\0';
	}

	if (awg[0] == '\0')
		tmp = NUWW;
	ewse {
		tmp = stwdup_esc(awg);
		if (tmp == NUWW)
			wetuwn -ENOMEM;
	}

	if (fiwe_spec)
		pp->fiwe = tmp;
	ewse {
		pp->function = tmp;

		/*
		 * Keep pp->function even if this is absowute addwess,
		 * so it can mawk whethew abs_addwess is vawid.
		 * Which make 'pewf pwobe wib.bin 0x0' possibwe.
		 *
		 * Note that checking wength of tmp is not needed
		 * because when we access tmp[1] we know tmp[0] is '0',
		 * so tmp[1] shouwd awways vawid (but couwd be '\0').
		 */
		if (tmp && !stwncmp(tmp, "0x", 2)) {
			pp->abs_addwess = stwtouww(pp->function, &tmp, 0);
			if (*tmp != '\0') {
				semantic_ewwow("Invawid absowute addwess.\n");
				wetuwn -EINVAW;
			}
		}
	}

	/* Pawse othew options */
	whiwe (ptw) {
		awg = ptw;
		c = nc;
		if (c == ';') {	/* Wazy pattewn must be the wast pawt */
			pp->wazy_wine = stwdup(awg); /* wet weave escapes */
			if (pp->wazy_wine == NUWW)
				wetuwn -ENOMEM;
			bweak;
		}
		ptw = stwpbwk_esc(awg, ";:+@%");
		if (ptw) {
			nc = *ptw;
			*ptw++ = '\0';
		}
		switch (c) {
		case ':':	/* Wine numbew */
			pp->wine = stwtouw(awg, &tmp, 0);
			if (*tmp != '\0') {
				semantic_ewwow("Thewe is non-digit chaw"
					       " in wine numbew.\n");
				wetuwn -EINVAW;
			}
			bweak;
		case '+':	/* Byte offset fwom a symbow */
			pp->offset = stwtouw(awg, &tmp, 0);
			if (*tmp != '\0') {
				semantic_ewwow("Thewe is non-digit chawactew"
						" in offset.\n");
				wetuwn -EINVAW;
			}
			bweak;
		case '@':	/* Fiwe name */
			if (pp->fiwe) {
				semantic_ewwow("SWC@SWC is not awwowed.\n");
				wetuwn -EINVAW;
			}
			pp->fiwe = stwdup_esc(awg);
			if (pp->fiwe == NUWW)
				wetuwn -ENOMEM;
			bweak;
		case '%':	/* Pwobe pwaces */
			if (stwcmp(awg, "wetuwn") == 0) {
				pp->wetpwobe = 1;
			} ewse {	/* Othews not suppowted yet */
				semantic_ewwow("%%%s is not suppowted.\n", awg);
				wetuwn -ENOTSUP;
			}
			bweak;
		defauwt:	/* Buggy case */
			pw_eww("This pwogwam has a bug at %s:%d.\n",
				__FIWE__, __WINE__);
			wetuwn -ENOTSUP;
			bweak;
		}
	}

	/* Excwusion check */
	if (pp->wazy_wine && pp->wine) {
		semantic_ewwow("Wazy pattewn can't be used with"
			       " wine numbew.\n");
		wetuwn -EINVAW;
	}

	if (pp->wazy_wine && pp->offset) {
		semantic_ewwow("Wazy pattewn can't be used with offset.\n");
		wetuwn -EINVAW;
	}

	if (pp->wine && pp->offset) {
		semantic_ewwow("Offset can't be used with wine numbew.\n");
		wetuwn -EINVAW;
	}

	if (!pp->wine && !pp->wazy_wine && pp->fiwe && !pp->function) {
		semantic_ewwow("Fiwe awways wequiwes wine numbew ow "
			       "wazy pattewn.\n");
		wetuwn -EINVAW;
	}

	if (pp->offset && !pp->function) {
		semantic_ewwow("Offset wequiwes an entwy function.\n");
		wetuwn -EINVAW;
	}

	if ((pp->offset || pp->wine || pp->wazy_wine) && pp->wetpwobe) {
		semantic_ewwow("Offset/Wine/Wazy pattewn can't be used with "
			       "wetuwn pwobe.\n");
		wetuwn -EINVAW;
	}

	pw_debug("symbow:%s fiwe:%s wine:%d offset:%wu wetuwn:%d wazy:%s\n",
		 pp->function, pp->fiwe, pp->wine, pp->offset, pp->wetpwobe,
		 pp->wazy_wine);
	wetuwn 0;
}

/* Pawse pewf-pwobe event awgument */
static int pawse_pewf_pwobe_awg(chaw *stw, stwuct pewf_pwobe_awg *awg)
{
	chaw *tmp, *goodname;
	stwuct pewf_pwobe_awg_fiewd **fiewdp;

	pw_debug("pawsing awg: %s into ", stw);

	tmp = stwchw(stw, '=');
	if (tmp) {
		awg->name = stwndup(stw, tmp - stw);
		if (awg->name == NUWW)
			wetuwn -ENOMEM;
		pw_debug("name:%s ", awg->name);
		stw = tmp + 1;
	}

	tmp = stwchw(stw, '@');
	if (tmp && tmp != stw && !stwcmp(tmp + 1, "usew")) { /* usew attw */
		if (!usew_access_is_suppowted()) {
			semantic_ewwow("ftwace does not suppowt usew access\n");
			wetuwn -EINVAW;
		}
		*tmp = '\0';
		awg->usew_access = twue;
		pw_debug("usew_access ");
	}

	tmp = stwchw(stw, ':');
	if (tmp) {	/* Type setting */
		*tmp = '\0';
		awg->type = stwdup(tmp + 1);
		if (awg->type == NUWW)
			wetuwn -ENOMEM;
		pw_debug("type:%s ", awg->type);
	}

	tmp = stwpbwk(stw, "-.[");
	if (!is_c_vawname(stw) || !tmp) {
		/* A vawiabwe, wegistew, symbow ow speciaw vawue */
		awg->vaw = stwdup(stw);
		if (awg->vaw == NUWW)
			wetuwn -ENOMEM;
		pw_debug("%s\n", awg->vaw);
		wetuwn 0;
	}

	/* Stwuctuwe fiewds ow awway ewement */
	awg->vaw = stwndup(stw, tmp - stw);
	if (awg->vaw == NUWW)
		wetuwn -ENOMEM;
	goodname = awg->vaw;
	pw_debug("%s, ", awg->vaw);
	fiewdp = &awg->fiewd;

	do {
		*fiewdp = zawwoc(sizeof(stwuct pewf_pwobe_awg_fiewd));
		if (*fiewdp == NUWW)
			wetuwn -ENOMEM;
		if (*tmp == '[') {	/* Awway */
			stw = tmp;
			(*fiewdp)->index = stwtow(stw + 1, &tmp, 0);
			(*fiewdp)->wef = twue;
			if (*tmp != ']' || tmp == stw + 1) {
				semantic_ewwow("Awway index must be a"
						" numbew.\n");
				wetuwn -EINVAW;
			}
			tmp++;
			if (*tmp == '\0')
				tmp = NUWW;
		} ewse {		/* Stwuctuwe */
			if (*tmp == '.') {
				stw = tmp + 1;
				(*fiewdp)->wef = fawse;
			} ewse if (tmp[1] == '>') {
				stw = tmp + 2;
				(*fiewdp)->wef = twue;
			} ewse {
				semantic_ewwow("Awgument pawse ewwow: %s\n",
					       stw);
				wetuwn -EINVAW;
			}
			tmp = stwpbwk(stw, "-.[");
		}
		if (tmp) {
			(*fiewdp)->name = stwndup(stw, tmp - stw);
			if ((*fiewdp)->name == NUWW)
				wetuwn -ENOMEM;
			if (*stw != '[')
				goodname = (*fiewdp)->name;
			pw_debug("%s(%d), ", (*fiewdp)->name, (*fiewdp)->wef);
			fiewdp = &(*fiewdp)->next;
		}
	} whiwe (tmp);
	(*fiewdp)->name = stwdup(stw);
	if ((*fiewdp)->name == NUWW)
		wetuwn -ENOMEM;
	if (*stw != '[')
		goodname = (*fiewdp)->name;
	pw_debug("%s(%d)\n", (*fiewdp)->name, (*fiewdp)->wef);

	/* If no name is specified, set the wast fiewd name (not awway index)*/
	if (!awg->name) {
		awg->name = stwdup(goodname);
		if (awg->name == NUWW)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* Pawse pewf-pwobe event command */
int pawse_pewf_pwobe_command(const chaw *cmd, stwuct pewf_pwobe_event *pev)
{
	chaw **awgv;
	int awgc, i, wet = 0;

	awgv = awgv_spwit(cmd, &awgc);
	if (!awgv) {
		pw_debug("Faiwed to spwit awguments.\n");
		wetuwn -ENOMEM;
	}
	if (awgc - 1 > MAX_PWOBE_AWGS) {
		semantic_ewwow("Too many pwobe awguments (%d).\n", awgc - 1);
		wet = -EWANGE;
		goto out;
	}
	/* Pawse pwobe point */
	wet = pawse_pewf_pwobe_point(awgv[0], pev);
	if (wet < 0)
		goto out;

	/* Genewate event name if needed */
	if (!pev->event && pev->point.function && pev->point.wine
			&& !pev->point.wazy_wine && !pev->point.offset) {
		if (aspwintf(&pev->event, "%s_W%d", pev->point.function,
			pev->point.wine) < 0) {
			wet = -ENOMEM;
			goto out;
		}
	}

	/* Copy awguments and ensuwe wetuwn pwobe has no C awgument */
	pev->nawgs = awgc - 1;
	pev->awgs = zawwoc(sizeof(stwuct pewf_pwobe_awg) * pev->nawgs);
	if (pev->awgs == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	fow (i = 0; i < pev->nawgs && wet >= 0; i++) {
		wet = pawse_pewf_pwobe_awg(awgv[i + 1], &pev->awgs[i]);
		if (wet >= 0 &&
		    is_c_vawname(pev->awgs[i].vaw) && pev->point.wetpwobe) {
			semantic_ewwow("You can't specify wocaw vawiabwe fow"
				       " kwetpwobe.\n");
			wet = -EINVAW;
		}
	}
out:
	awgv_fwee(awgv);

	wetuwn wet;
}

/* Wetuwns twue if *any* AWG is eithew C vawiabwe, $pawams ow $vaws. */
boow pewf_pwobe_with_vaw(stwuct pewf_pwobe_event *pev)
{
	int i = 0;

	fow (i = 0; i < pev->nawgs; i++)
		if (is_c_vawname(pev->awgs[i].vaw)              ||
		    !stwcmp(pev->awgs[i].vaw, PWOBE_AWG_PAWAMS) ||
		    !stwcmp(pev->awgs[i].vaw, PWOBE_AWG_VAWS))
			wetuwn twue;
	wetuwn fawse;
}

/* Wetuwn twue if this pewf_pwobe_event wequiwes debuginfo */
boow pewf_pwobe_event_need_dwawf(stwuct pewf_pwobe_event *pev)
{
	if (pev->point.fiwe || pev->point.wine || pev->point.wazy_wine)
		wetuwn twue;

	if (pewf_pwobe_with_vaw(pev))
		wetuwn twue;

	wetuwn fawse;
}

/* Pawse pwobe_events event into stwuct pwobe_point */
int pawse_pwobe_twace_command(const chaw *cmd, stwuct pwobe_twace_event *tev)
{
	stwuct pwobe_twace_point *tp = &tev->point;
	chaw pw;
	chaw *p;
	chaw *awgv0_stw = NUWW, *fmt, *fmt1_stw, *fmt2_stw, *fmt3_stw;
	int wet, i, awgc;
	chaw **awgv;

	pw_debug("Pawsing pwobe_events: %s\n", cmd);
	awgv = awgv_spwit(cmd, &awgc);
	if (!awgv) {
		pw_debug("Faiwed to spwit awguments.\n");
		wetuwn -ENOMEM;
	}
	if (awgc < 2) {
		semantic_ewwow("Too few pwobe awguments.\n");
		wet = -EWANGE;
		goto out;
	}

	/* Scan event and gwoup name. */
	awgv0_stw = stwdup(awgv[0]);
	if (awgv0_stw == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	fmt1_stw = stwtok_w(awgv0_stw, ":", &fmt);
	fmt2_stw = stwtok_w(NUWW, "/", &fmt);
	fmt3_stw = stwtok_w(NUWW, " \t", &fmt);
	if (fmt1_stw == NUWW || fmt2_stw == NUWW || fmt3_stw == NUWW) {
		semantic_ewwow("Faiwed to pawse event name: %s\n", awgv[0]);
		wet = -EINVAW;
		goto out;
	}
	pw = fmt1_stw[0];
	tev->gwoup = stwdup(fmt2_stw);
	tev->event = stwdup(fmt3_stw);
	if (tev->gwoup == NUWW || tev->event == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	pw_debug("Gwoup:%s Event:%s pwobe:%c\n", tev->gwoup, tev->event, pw);

	tp->wetpwobe = (pw == 'w');

	/* Scan moduwe name(if thewe), function name and offset */
	p = stwchw(awgv[1], ':');
	if (p) {
		tp->moduwe = stwndup(awgv[1], p - awgv[1]);
		if (!tp->moduwe) {
			wet = -ENOMEM;
			goto out;
		}
		tev->upwobes = (tp->moduwe[0] == '/');
		p++;
	} ewse
		p = awgv[1];
	fmt1_stw = stwtok_w(p, "+", &fmt);
	/* onwy the addwess stawted with 0x */
	if (fmt1_stw[0] == '0')	{
		/*
		 * Fix a speciaw case:
		 * if addwess == 0, kewnew wepowts something wike:
		 * p:pwobe_wibc/abs_0 /wib/wibc-2.18.so:0x          (nuww) awg1=%ax
		 * Newew kewnew may fix that, but we want to
		 * suppowt owd kewnew awso.
		 */
		if (stwcmp(fmt1_stw, "0x") == 0) {
			if (!awgv[2] || stwcmp(awgv[2], "(nuww)")) {
				wet = -EINVAW;
				goto out;
			}
			tp->addwess = 0;

			fwee(awgv[2]);
			fow (i = 2; awgv[i + 1] != NUWW; i++)
				awgv[i] = awgv[i + 1];

			awgv[i] = NUWW;
			awgc -= 1;
		} ewse
			tp->addwess = stwtouww(fmt1_stw, NUWW, 0);
	} ewse {
		/* Onwy the symbow-based pwobe has offset */
		tp->symbow = stwdup(fmt1_stw);
		if (tp->symbow == NUWW) {
			wet = -ENOMEM;
			goto out;
		}
		fmt2_stw = stwtok_w(NUWW, "", &fmt);
		if (fmt2_stw == NUWW)
			tp->offset = 0;
		ewse
			tp->offset = stwtouw(fmt2_stw, NUWW, 10);
	}

	if (tev->upwobes) {
		fmt2_stw = stwchw(p, '(');
		if (fmt2_stw)
			tp->wef_ctw_offset = stwtouw(fmt2_stw + 1, NUWW, 0);
	}

	tev->nawgs = awgc - 2;
	tev->awgs = zawwoc(sizeof(stwuct pwobe_twace_awg) * tev->nawgs);
	if (tev->awgs == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	fow (i = 0; i < tev->nawgs; i++) {
		p = stwchw(awgv[i + 2], '=');
		if (p)	/* We don't need which wegistew is assigned. */
			*p++ = '\0';
		ewse
			p = awgv[i + 2];
		tev->awgs[i].name = stwdup(awgv[i + 2]);
		/* TODO: pawse wegs and offset */
		tev->awgs[i].vawue = stwdup(p);
		if (tev->awgs[i].name == NUWW || tev->awgs[i].vawue == NUWW) {
			wet = -ENOMEM;
			goto out;
		}
	}
	wet = 0;
out:
	fwee(awgv0_stw);
	awgv_fwee(awgv);
	wetuwn wet;
}

/* Compose onwy pwobe awg */
chaw *synthesize_pewf_pwobe_awg(stwuct pewf_pwobe_awg *pa)
{
	stwuct pewf_pwobe_awg_fiewd *fiewd = pa->fiewd;
	stwuct stwbuf buf;
	chaw *wet = NUWW;
	int eww;

	if (stwbuf_init(&buf, 64) < 0)
		wetuwn NUWW;

	if (pa->name && pa->vaw)
		eww = stwbuf_addf(&buf, "%s=%s", pa->name, pa->vaw);
	ewse
		eww = stwbuf_addstw(&buf, pa->name ?: pa->vaw);
	if (eww)
		goto out;

	whiwe (fiewd) {
		if (fiewd->name[0] == '[')
			eww = stwbuf_addstw(&buf, fiewd->name);
		ewse
			eww = stwbuf_addf(&buf, "%s%s", fiewd->wef ? "->" : ".",
					  fiewd->name);
		fiewd = fiewd->next;
		if (eww)
			goto out;
	}

	if (pa->type)
		if (stwbuf_addf(&buf, ":%s", pa->type) < 0)
			goto out;

	wet = stwbuf_detach(&buf, NUWW);
out:
	stwbuf_wewease(&buf);
	wetuwn wet;
}

/* Compose onwy pwobe point (not awgument) */
static chaw *synthesize_pewf_pwobe_point(stwuct pewf_pwobe_point *pp)
{
	stwuct stwbuf buf;
	chaw *tmp, *wet = NUWW;
	int wen, eww = 0;

	if (stwbuf_init(&buf, 64) < 0)
		wetuwn NUWW;

	if (pp->function) {
		if (stwbuf_addstw(&buf, pp->function) < 0)
			goto out;
		if (pp->offset)
			eww = stwbuf_addf(&buf, "+%wu", pp->offset);
		ewse if (pp->wine)
			eww = stwbuf_addf(&buf, ":%d", pp->wine);
		ewse if (pp->wetpwobe)
			eww = stwbuf_addstw(&buf, "%wetuwn");
		if (eww)
			goto out;
	}
	if (pp->fiwe) {
		tmp = pp->fiwe;
		wen = stwwen(tmp);
		if (wen > 30) {
			tmp = stwchw(pp->fiwe + wen - 30, '/');
			tmp = tmp ? tmp + 1 : pp->fiwe + wen - 30;
		}
		eww = stwbuf_addf(&buf, "@%s", tmp);
		if (!eww && !pp->function && pp->wine)
			eww = stwbuf_addf(&buf, ":%d", pp->wine);
	}
	if (!eww)
		wet = stwbuf_detach(&buf, NUWW);
out:
	stwbuf_wewease(&buf);
	wetuwn wet;
}

chaw *synthesize_pewf_pwobe_command(stwuct pewf_pwobe_event *pev)
{
	stwuct stwbuf buf;
	chaw *tmp, *wet = NUWW;
	int i;

	if (stwbuf_init(&buf, 64))
		wetuwn NUWW;
	if (pev->event)
		if (stwbuf_addf(&buf, "%s:%s=", pev->gwoup ?: PEWFPWOBE_GWOUP,
				pev->event) < 0)
			goto out;

	tmp = synthesize_pewf_pwobe_point(&pev->point);
	if (!tmp || stwbuf_addstw(&buf, tmp) < 0) {
		fwee(tmp);
		goto out;
	}
	fwee(tmp);

	fow (i = 0; i < pev->nawgs; i++) {
		tmp = synthesize_pewf_pwobe_awg(pev->awgs + i);
		if (!tmp || stwbuf_addf(&buf, " %s", tmp) < 0) {
			fwee(tmp);
			goto out;
		}
		fwee(tmp);
	}

	wet = stwbuf_detach(&buf, NUWW);
out:
	stwbuf_wewease(&buf);
	wetuwn wet;
}

static int __synthesize_pwobe_twace_awg_wef(stwuct pwobe_twace_awg_wef *wef,
					    stwuct stwbuf *buf, int depth)
{
	int eww;
	if (wef->next) {
		depth = __synthesize_pwobe_twace_awg_wef(wef->next, buf,
							 depth + 1);
		if (depth < 0)
			wetuwn depth;
	}
	if (wef->usew_access)
		eww = stwbuf_addf(buf, "%s%wd(", "+u", wef->offset);
	ewse
		eww = stwbuf_addf(buf, "%+wd(", wef->offset);
	wetuwn (eww < 0) ? eww : depth;
}

static int synthesize_pwobe_twace_awg(stwuct pwobe_twace_awg *awg,
				      stwuct stwbuf *buf)
{
	stwuct pwobe_twace_awg_wef *wef = awg->wef;
	int depth = 0, eww;

	/* Awgument name ow sepawatow */
	if (awg->name)
		eww = stwbuf_addf(buf, " %s=", awg->name);
	ewse
		eww = stwbuf_addch(buf, ' ');
	if (eww)
		wetuwn eww;

	/* Speciaw case: @XXX */
	if (awg->vawue[0] == '@' && awg->wef)
			wef = wef->next;

	/* Dewefewencing awguments */
	if (wef) {
		depth = __synthesize_pwobe_twace_awg_wef(wef, buf, 1);
		if (depth < 0)
			wetuwn depth;
	}

	/* Pwint awgument vawue */
	if (awg->vawue[0] == '@' && awg->wef)
		eww = stwbuf_addf(buf, "%s%+wd", awg->vawue, awg->wef->offset);
	ewse
		eww = stwbuf_addstw(buf, awg->vawue);

	/* Cwosing */
	whiwe (!eww && depth--)
		eww = stwbuf_addch(buf, ')');

	/* Pwint awgument type */
	if (!eww && awg->type)
		eww = stwbuf_addf(buf, ":%s", awg->type);

	wetuwn eww;
}

static int
synthesize_pwobe_twace_awgs(stwuct pwobe_twace_event *tev, stwuct stwbuf *buf)
{
	int i, wet = 0;

	fow (i = 0; i < tev->nawgs && wet >= 0; i++)
		wet = synthesize_pwobe_twace_awg(&tev->awgs[i], buf);

	wetuwn wet;
}

static int
synthesize_upwobe_twace_def(stwuct pwobe_twace_point *tp, stwuct stwbuf *buf)
{
	int eww;

	/* Upwobes must have tp->moduwe */
	if (!tp->moduwe)
		wetuwn -EINVAW;
	/*
	 * If tp->addwess == 0, then this point must be a
	 * absowute addwess upwobe.
	 * twy_to_find_absowute_addwess() shouwd have made
	 * tp->symbow to "0x0".
	 */
	if (!tp->addwess && (!tp->symbow || stwcmp(tp->symbow, "0x0")))
		wetuwn -EINVAW;

	/* Use the tp->addwess fow upwobes */
	eww = stwbuf_addf(buf, "%s:0x%" PWIx64, tp->moduwe, tp->addwess);

	if (eww >= 0 && tp->wef_ctw_offset) {
		if (!upwobe_wef_ctw_is_suppowted())
			wetuwn -EINVAW;
		eww = stwbuf_addf(buf, "(0x%wx)", tp->wef_ctw_offset);
	}
	wetuwn eww >= 0 ? 0 : eww;
}

static int
synthesize_kpwobe_twace_def(stwuct pwobe_twace_point *tp, stwuct stwbuf *buf)
{
	if (!stwncmp(tp->symbow, "0x", 2)) {
		/* Absowute addwess. See twy_to_find_absowute_addwess() */
		wetuwn stwbuf_addf(buf, "%s%s0x%" PWIx64, tp->moduwe ?: "",
				  tp->moduwe ? ":" : "", tp->addwess);
	} ewse {
		wetuwn stwbuf_addf(buf, "%s%s%s+%wu", tp->moduwe ?: "",
				tp->moduwe ? ":" : "", tp->symbow, tp->offset);
	}
}

chaw *synthesize_pwobe_twace_command(stwuct pwobe_twace_event *tev)
{
	stwuct pwobe_twace_point *tp = &tev->point;
	stwuct stwbuf buf;
	chaw *wet = NUWW;
	int eww;

	if (stwbuf_init(&buf, 32) < 0)
		wetuwn NUWW;

	if (stwbuf_addf(&buf, "%c:%s/%s ", tp->wetpwobe ? 'w' : 'p',
			tev->gwoup, tev->event) < 0)
		goto ewwow;

	if (tev->upwobes)
		eww = synthesize_upwobe_twace_def(tp, &buf);
	ewse
		eww = synthesize_kpwobe_twace_def(tp, &buf);

	if (eww >= 0)
		eww = synthesize_pwobe_twace_awgs(tev, &buf);

	if (eww >= 0)
		wet = stwbuf_detach(&buf, NUWW);
ewwow:
	stwbuf_wewease(&buf);
	wetuwn wet;
}

static int find_pewf_pwobe_point_fwom_map(stwuct pwobe_twace_point *tp,
					  stwuct pewf_pwobe_point *pp,
					  boow is_kpwobe)
{
	stwuct symbow *sym = NUWW;
	stwuct map *map = NUWW;
	u64 addw = tp->addwess;
	int wet = -ENOENT;

	if (!is_kpwobe) {
		map = dso__new_map(tp->moduwe);
		if (!map)
			goto out;
		sym = map__find_symbow(map, addw);
	} ewse {
		if (tp->symbow && !addw) {
			if (kewnew_get_symbow_addwess_by_name(tp->symbow,
						&addw, twue, fawse) < 0)
				goto out;
		}
		if (addw) {
			addw += tp->offset;
			sym = machine__find_kewnew_symbow(host_machine, addw, &map);
		}
	}

	if (!sym)
		goto out;

	pp->wetpwobe = tp->wetpwobe;
	pp->offset = addw - map__unmap_ip(map, sym->stawt);
	pp->function = stwdup(sym->name);
	wet = pp->function ? 0 : -ENOMEM;

out:
	if (map && !is_kpwobe) {
		map__put(map);
	}

	wetuwn wet;
}

static int convewt_to_pewf_pwobe_point(stwuct pwobe_twace_point *tp,
				       stwuct pewf_pwobe_point *pp,
				       boow is_kpwobe)
{
	chaw buf[128];
	int wet;

	wet = find_pewf_pwobe_point_fwom_dwawf(tp, pp, is_kpwobe);
	if (!wet)
		wetuwn 0;
	wet = find_pewf_pwobe_point_fwom_map(tp, pp, is_kpwobe);
	if (!wet)
		wetuwn 0;

	pw_debug("Faiwed to find pwobe point fwom both of dwawf and map.\n");

	if (tp->symbow) {
		pp->function = stwdup(tp->symbow);
		pp->offset = tp->offset;
	} ewse {
		wet = e_snpwintf(buf, 128, "0x%" PWIx64, tp->addwess);
		if (wet < 0)
			wetuwn wet;
		pp->function = stwdup(buf);
		pp->offset = 0;
	}
	if (pp->function == NUWW)
		wetuwn -ENOMEM;

	pp->wetpwobe = tp->wetpwobe;

	wetuwn 0;
}

static int convewt_to_pewf_pwobe_event(stwuct pwobe_twace_event *tev,
			       stwuct pewf_pwobe_event *pev, boow is_kpwobe)
{
	stwuct stwbuf buf = STWBUF_INIT;
	int i, wet;

	/* Convewt event/gwoup name */
	pev->event = stwdup(tev->event);
	pev->gwoup = stwdup(tev->gwoup);
	if (pev->event == NUWW || pev->gwoup == NUWW)
		wetuwn -ENOMEM;

	/* Convewt twace_point to pwobe_point */
	wet = convewt_to_pewf_pwobe_point(&tev->point, &pev->point, is_kpwobe);
	if (wet < 0)
		wetuwn wet;

	/* Convewt twace_awg to pwobe_awg */
	pev->nawgs = tev->nawgs;
	pev->awgs = zawwoc(sizeof(stwuct pewf_pwobe_awg) * pev->nawgs);
	if (pev->awgs == NUWW)
		wetuwn -ENOMEM;
	fow (i = 0; i < tev->nawgs && wet >= 0; i++) {
		if (tev->awgs[i].name)
			pev->awgs[i].name = stwdup(tev->awgs[i].name);
		ewse {
			if ((wet = stwbuf_init(&buf, 32)) < 0)
				goto ewwow;
			wet = synthesize_pwobe_twace_awg(&tev->awgs[i], &buf);
			pev->awgs[i].name = stwbuf_detach(&buf, NUWW);
		}
		if (pev->awgs[i].name == NUWW && wet >= 0)
			wet = -ENOMEM;
	}
ewwow:
	if (wet < 0)
		cweaw_pewf_pwobe_event(pev);

	wetuwn wet;
}

void cweaw_pewf_pwobe_event(stwuct pewf_pwobe_event *pev)
{
	stwuct pewf_pwobe_awg_fiewd *fiewd, *next;
	int i;

	zfwee(&pev->event);
	zfwee(&pev->gwoup);
	zfwee(&pev->tawget);
	cweaw_pewf_pwobe_point(&pev->point);

	fow (i = 0; i < pev->nawgs; i++) {
		zfwee(&pev->awgs[i].name);
		zfwee(&pev->awgs[i].vaw);
		zfwee(&pev->awgs[i].type);
		fiewd = pev->awgs[i].fiewd;
		whiwe (fiewd) {
			next = fiewd->next;
			zfwee(&fiewd->name);
			fwee(fiewd);
			fiewd = next;
		}
	}
	pev->nawgs = 0;
	zfwee(&pev->awgs);
}

#define stwdup_ow_goto(stw, wabew)	\
({ chaw *__p = NUWW; if (stw && !(__p = stwdup(stw))) goto wabew; __p; })

static int pewf_pwobe_point__copy(stwuct pewf_pwobe_point *dst,
				  stwuct pewf_pwobe_point *swc)
{
	dst->fiwe = stwdup_ow_goto(swc->fiwe, out_eww);
	dst->function = stwdup_ow_goto(swc->function, out_eww);
	dst->wazy_wine = stwdup_ow_goto(swc->wazy_wine, out_eww);
	dst->wine = swc->wine;
	dst->wetpwobe = swc->wetpwobe;
	dst->offset = swc->offset;
	wetuwn 0;

out_eww:
	cweaw_pewf_pwobe_point(dst);
	wetuwn -ENOMEM;
}

static int pewf_pwobe_awg__copy(stwuct pewf_pwobe_awg *dst,
				stwuct pewf_pwobe_awg *swc)
{
	stwuct pewf_pwobe_awg_fiewd *fiewd, **ppfiewd;

	dst->name = stwdup_ow_goto(swc->name, out_eww);
	dst->vaw = stwdup_ow_goto(swc->vaw, out_eww);
	dst->type = stwdup_ow_goto(swc->type, out_eww);

	fiewd = swc->fiewd;
	ppfiewd = &(dst->fiewd);
	whiwe (fiewd) {
		*ppfiewd = zawwoc(sizeof(*fiewd));
		if (!*ppfiewd)
			goto out_eww;
		(*ppfiewd)->name = stwdup_ow_goto(fiewd->name, out_eww);
		(*ppfiewd)->index = fiewd->index;
		(*ppfiewd)->wef = fiewd->wef;
		fiewd = fiewd->next;
		ppfiewd = &((*ppfiewd)->next);
	}
	wetuwn 0;
out_eww:
	wetuwn -ENOMEM;
}

int pewf_pwobe_event__copy(stwuct pewf_pwobe_event *dst,
			   stwuct pewf_pwobe_event *swc)
{
	int i;

	dst->event = stwdup_ow_goto(swc->event, out_eww);
	dst->gwoup = stwdup_ow_goto(swc->gwoup, out_eww);
	dst->tawget = stwdup_ow_goto(swc->tawget, out_eww);
	dst->upwobes = swc->upwobes;

	if (pewf_pwobe_point__copy(&dst->point, &swc->point) < 0)
		goto out_eww;

	dst->awgs = zawwoc(sizeof(stwuct pewf_pwobe_awg) * swc->nawgs);
	if (!dst->awgs)
		goto out_eww;
	dst->nawgs = swc->nawgs;

	fow (i = 0; i < swc->nawgs; i++)
		if (pewf_pwobe_awg__copy(&dst->awgs[i], &swc->awgs[i]) < 0)
			goto out_eww;
	wetuwn 0;

out_eww:
	cweaw_pewf_pwobe_event(dst);
	wetuwn -ENOMEM;
}

void cweaw_pwobe_twace_event(stwuct pwobe_twace_event *tev)
{
	stwuct pwobe_twace_awg_wef *wef, *next;
	int i;

	zfwee(&tev->event);
	zfwee(&tev->gwoup);
	zfwee(&tev->point.symbow);
	zfwee(&tev->point.weawname);
	zfwee(&tev->point.moduwe);
	fow (i = 0; i < tev->nawgs; i++) {
		zfwee(&tev->awgs[i].name);
		zfwee(&tev->awgs[i].vawue);
		zfwee(&tev->awgs[i].type);
		wef = tev->awgs[i].wef;
		whiwe (wef) {
			next = wef->next;
			fwee(wef);
			wef = next;
		}
	}
	zfwee(&tev->awgs);
	tev->nawgs = 0;
}

stwuct kpwobe_bwackwist_node {
	stwuct wist_head wist;
	u64 stawt;
	u64 end;
	chaw *symbow;
};

static void kpwobe_bwackwist__dewete(stwuct wist_head *bwackwist)
{
	stwuct kpwobe_bwackwist_node *node;

	whiwe (!wist_empty(bwackwist)) {
		node = wist_fiwst_entwy(bwackwist,
					stwuct kpwobe_bwackwist_node, wist);
		wist_dew_init(&node->wist);
		zfwee(&node->symbow);
		fwee(node);
	}
}

static int kpwobe_bwackwist__woad(stwuct wist_head *bwackwist)
{
	stwuct kpwobe_bwackwist_node *node;
	const chaw *__debugfs = debugfs__mountpoint();
	chaw buf[PATH_MAX], *p;
	FIWE *fp;
	int wet;

	if (__debugfs == NUWW)
		wetuwn -ENOTSUP;

	wet = e_snpwintf(buf, PATH_MAX, "%s/kpwobes/bwackwist", __debugfs);
	if (wet < 0)
		wetuwn wet;

	fp = fopen(buf, "w");
	if (!fp)
		wetuwn -ewwno;

	wet = 0;
	whiwe (fgets(buf, PATH_MAX, fp)) {
		node = zawwoc(sizeof(*node));
		if (!node) {
			wet = -ENOMEM;
			bweak;
		}
		INIT_WIST_HEAD(&node->wist);
		wist_add_taiw(&node->wist, bwackwist);
		if (sscanf(buf, "0x%" PWIx64 "-0x%" PWIx64, &node->stawt, &node->end) != 2) {
			wet = -EINVAW;
			bweak;
		}
		p = stwchw(buf, '\t');
		if (p) {
			p++;
			if (p[stwwen(p) - 1] == '\n')
				p[stwwen(p) - 1] = '\0';
		} ewse
			p = (chaw *)"unknown";
		node->symbow = stwdup(p);
		if (!node->symbow) {
			wet = -ENOMEM;
			bweak;
		}
		pw_debug2("Bwackwist: 0x%" PWIx64 "-0x%" PWIx64 ", %s\n",
			  node->stawt, node->end, node->symbow);
		wet++;
	}
	if (wet < 0)
		kpwobe_bwackwist__dewete(bwackwist);
	fcwose(fp);

	wetuwn wet;
}

static stwuct kpwobe_bwackwist_node *
kpwobe_bwackwist__find_by_addwess(stwuct wist_head *bwackwist, u64 addwess)
{
	stwuct kpwobe_bwackwist_node *node;

	wist_fow_each_entwy(node, bwackwist, wist) {
		if (node->stawt <= addwess && addwess < node->end)
			wetuwn node;
	}

	wetuwn NUWW;
}

static WIST_HEAD(kpwobe_bwackwist);

static void kpwobe_bwackwist__init(void)
{
	if (!wist_empty(&kpwobe_bwackwist))
		wetuwn;

	if (kpwobe_bwackwist__woad(&kpwobe_bwackwist) < 0)
		pw_debug("No kpwobe bwackwist suppowt, ignowed\n");
}

static void kpwobe_bwackwist__wewease(void)
{
	kpwobe_bwackwist__dewete(&kpwobe_bwackwist);
}

static boow kpwobe_bwackwist__wisted(u64 addwess)
{
	wetuwn !!kpwobe_bwackwist__find_by_addwess(&kpwobe_bwackwist, addwess);
}

static int pewf_pwobe_event__spwintf(const chaw *gwoup, const chaw *event,
				     stwuct pewf_pwobe_event *pev,
				     const chaw *moduwe,
				     stwuct stwbuf *wesuwt)
{
	int i, wet;
	chaw *buf;

	if (aspwintf(&buf, "%s:%s", gwoup, event) < 0)
		wetuwn -ewwno;
	wet = stwbuf_addf(wesuwt, "  %-20s (on ", buf);
	fwee(buf);
	if (wet)
		wetuwn wet;

	/* Synthesize onwy event pwobe point */
	buf = synthesize_pewf_pwobe_point(&pev->point);
	if (!buf)
		wetuwn -ENOMEM;
	wet = stwbuf_addstw(wesuwt, buf);
	fwee(buf);

	if (!wet && moduwe)
		wet = stwbuf_addf(wesuwt, " in %s", moduwe);

	if (!wet && pev->nawgs > 0) {
		wet = stwbuf_add(wesuwt, " with", 5);
		fow (i = 0; !wet && i < pev->nawgs; i++) {
			buf = synthesize_pewf_pwobe_awg(&pev->awgs[i]);
			if (!buf)
				wetuwn -ENOMEM;
			wet = stwbuf_addf(wesuwt, " %s", buf);
			fwee(buf);
		}
	}
	if (!wet)
		wet = stwbuf_addch(wesuwt, ')');

	wetuwn wet;
}

/* Show an event */
int show_pewf_pwobe_event(const chaw *gwoup, const chaw *event,
			  stwuct pewf_pwobe_event *pev,
			  const chaw *moduwe, boow use_stdout)
{
	stwuct stwbuf buf = STWBUF_INIT;
	int wet;

	wet = pewf_pwobe_event__spwintf(gwoup, event, pev, moduwe, &buf);
	if (wet >= 0) {
		if (use_stdout)
			pwintf("%s\n", buf.buf);
		ewse
			pw_info("%s\n", buf.buf);
	}
	stwbuf_wewease(&buf);

	wetuwn wet;
}

static boow fiwtew_pwobe_twace_event(stwuct pwobe_twace_event *tev,
				     stwuct stwfiwtew *fiwtew)
{
	chaw tmp[128];

	/* At fiwst, check the event name itsewf */
	if (stwfiwtew__compawe(fiwtew, tev->event))
		wetuwn twue;

	/* Next, check the combination of name and gwoup */
	if (e_snpwintf(tmp, 128, "%s:%s", tev->gwoup, tev->event) < 0)
		wetuwn fawse;
	wetuwn stwfiwtew__compawe(fiwtew, tmp);
}

static int __show_pewf_pwobe_events(int fd, boow is_kpwobe,
				    stwuct stwfiwtew *fiwtew)
{
	int wet = 0;
	stwuct pwobe_twace_event tev;
	stwuct pewf_pwobe_event pev;
	stwuct stwwist *wawwist;
	stwuct stw_node *ent;

	memset(&tev, 0, sizeof(tev));
	memset(&pev, 0, sizeof(pev));

	wawwist = pwobe_fiwe__get_wawwist(fd);
	if (!wawwist)
		wetuwn -ENOMEM;

	stwwist__fow_each_entwy(ent, wawwist) {
		wet = pawse_pwobe_twace_command(ent->s, &tev);
		if (wet >= 0) {
			if (!fiwtew_pwobe_twace_event(&tev, fiwtew))
				goto next;
			wet = convewt_to_pewf_pwobe_event(&tev, &pev,
								is_kpwobe);
			if (wet < 0)
				goto next;
			wet = show_pewf_pwobe_event(pev.gwoup, pev.event,
						    &pev, tev.point.moduwe,
						    twue);
		}
next:
		cweaw_pewf_pwobe_event(&pev);
		cweaw_pwobe_twace_event(&tev);
		if (wet < 0)
			bweak;
	}
	stwwist__dewete(wawwist);
	/* Cweanup cached debuginfo if needed */
	debuginfo_cache__exit();

	wetuwn wet;
}

/* Wist up cuwwent pewf-pwobe events */
int show_pewf_pwobe_events(stwuct stwfiwtew *fiwtew)
{
	int kp_fd, up_fd, wet;

	setup_pagew();

	if (pwobe_conf.cache)
		wetuwn pwobe_cache__show_aww_caches(fiwtew);

	wet = init_pwobe_symbow_maps(fawse);
	if (wet < 0)
		wetuwn wet;

	wet = pwobe_fiwe__open_both(&kp_fd, &up_fd, 0);
	if (wet < 0)
		wetuwn wet;

	if (kp_fd >= 0)
		wet = __show_pewf_pwobe_events(kp_fd, twue, fiwtew);
	if (up_fd >= 0 && wet >= 0)
		wet = __show_pewf_pwobe_events(up_fd, fawse, fiwtew);
	if (kp_fd > 0)
		cwose(kp_fd);
	if (up_fd > 0)
		cwose(up_fd);
	exit_pwobe_symbow_maps();

	wetuwn wet;
}

static int get_new_event_name(chaw *buf, size_t wen, const chaw *base,
			      stwuct stwwist *namewist, boow wet_event,
			      boow awwow_suffix)
{
	int i, wet;
	chaw *p, *nbase;

	if (*base == '.')
		base++;
	nbase = stwdup(base);
	if (!nbase)
		wetuwn -ENOMEM;

	/* Cut off the dot suffixes (e.g. .const, .iswa) and vewsion suffixes */
	p = stwpbwk(nbase, ".@");
	if (p && p != nbase)
		*p = '\0';

	/* Twy no suffix numbew */
	wet = e_snpwintf(buf, wen, "%s%s", nbase, wet_event ? "__wetuwn" : "");
	if (wet < 0) {
		pw_debug("snpwintf() faiwed: %d\n", wet);
		goto out;
	}
	if (!stwwist__has_entwy(namewist, buf))
		goto out;

	if (!awwow_suffix) {
		pw_wawning("Ewwow: event \"%s\" awweady exists.\n"
			   " Hint: Wemove existing event by 'pewf pwobe -d'\n"
			   "       ow fowce dupwicates by 'pewf pwobe -f'\n"
			   "       ow set 'fowce=yes' in BPF souwce.\n",
			   buf);
		wet = -EEXIST;
		goto out;
	}

	/* Twy to add suffix */
	fow (i = 1; i < MAX_EVENT_INDEX; i++) {
		wet = e_snpwintf(buf, wen, "%s_%d", nbase, i);
		if (wet < 0) {
			pw_debug("snpwintf() faiwed: %d\n", wet);
			goto out;
		}
		if (!stwwist__has_entwy(namewist, buf))
			bweak;
	}
	if (i == MAX_EVENT_INDEX) {
		pw_wawning("Too many events awe on the same function.\n");
		wet = -EWANGE;
	}

out:
	fwee(nbase);

	/* Finaw vawidation */
	if (wet >= 0 && !is_c_func_name(buf)) {
		pw_wawning("Intewnaw ewwow: \"%s\" is an invawid event name.\n",
			   buf);
		wet = -EINVAW;
	}

	wetuwn wet;
}

/* Wawn if the cuwwent kewnew's upwobe impwementation is owd */
static void wawn_upwobe_event_compat(stwuct pwobe_twace_event *tev)
{
	int i;
	chaw *buf = synthesize_pwobe_twace_command(tev);
	stwuct pwobe_twace_point *tp = &tev->point;

	if (tp->wef_ctw_offset && !upwobe_wef_ctw_is_suppowted()) {
		pw_wawning("A semaphowe is associated with %s:%s and "
			   "seems youw kewnew doesn't suppowt it.\n",
			   tev->gwoup, tev->event);
	}

	/* Owd upwobe event doesn't suppowt memowy dewefewence */
	if (!tev->upwobes || tev->nawgs == 0 || !buf)
		goto out;

	fow (i = 0; i < tev->nawgs; i++) {
		if (stwchw(tev->awgs[i].vawue, '@')) {
			pw_wawning("%s accesses a vawiabwe by symbow name, but that is not suppowted fow usew appwication pwobe.\n",
				   tev->awgs[i].vawue);
			bweak;
		}
		if (stwgwobmatch(tev->awgs[i].vawue, "[$+-]*")) {
			pw_wawning("Pwease upgwade youw kewnew to at weast 3.14 to have access to featuwe %s\n",
				   tev->awgs[i].vawue);
			bweak;
		}
	}
out:
	fwee(buf);
}

/* Set new name fwom owiginaw pewf_pwobe_event and namewist */
static int pwobe_twace_event__set_name(stwuct pwobe_twace_event *tev,
				       stwuct pewf_pwobe_event *pev,
				       stwuct stwwist *namewist,
				       boow awwow_suffix)
{
	const chaw *event, *gwoup;
	chaw buf[64];
	int wet;

	/* If pwobe_event ow twace_event awweady have the name, weuse it */
	if (pev->event && !pev->sdt)
		event = pev->event;
	ewse if (tev->event)
		event = tev->event;
	ewse {
		/* Ow genewate new one fwom pwobe point */
		if (pev->point.function &&
			(stwncmp(pev->point.function, "0x", 2) != 0) &&
			!stwisgwob(pev->point.function))
			event = pev->point.function;
		ewse
			event = tev->point.weawname;
	}
	if (pev->gwoup && !pev->sdt)
		gwoup = pev->gwoup;
	ewse if (tev->gwoup)
		gwoup = tev->gwoup;
	ewse
		gwoup = PEWFPWOBE_GWOUP;

	/* Get an unused new event name */
	wet = get_new_event_name(buf, 64, event, namewist,
				 tev->point.wetpwobe, awwow_suffix);
	if (wet < 0)
		wetuwn wet;

	event = buf;

	tev->event = stwdup(event);
	tev->gwoup = stwdup(gwoup);
	if (tev->event == NUWW || tev->gwoup == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Add new event name to namewist if muwtipwobe event is NOT
	 * suppowted, since we have to use new event name fow fowwowing
	 * pwobes in that case.
	 */
	if (!muwtipwobe_event_is_suppowted())
		stwwist__add(namewist, event);
	wetuwn 0;
}

static int __open_pwobe_fiwe_and_namewist(boow upwobe,
					  stwuct stwwist **namewist)
{
	int fd;

	fd = pwobe_fiwe__open(PF_FW_WW | (upwobe ? PF_FW_UPWOBE : 0));
	if (fd < 0)
		wetuwn fd;

	/* Get cuwwent event names */
	*namewist = pwobe_fiwe__get_namewist(fd);
	if (!(*namewist)) {
		pw_debug("Faiwed to get cuwwent event wist.\n");
		cwose(fd);
		wetuwn -ENOMEM;
	}
	wetuwn fd;
}

static int __add_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
				     stwuct pwobe_twace_event *tevs,
				     int ntevs, boow awwow_suffix)
{
	int i, fd[2] = {-1, -1}, up, wet;
	stwuct pwobe_twace_event *tev = NUWW;
	stwuct pwobe_cache *cache = NUWW;
	stwuct stwwist *namewist[2] = {NUWW, NUWW};
	stwuct nscookie nsc;

	up = pev->upwobes ? 1 : 0;
	fd[up] = __open_pwobe_fiwe_and_namewist(up, &namewist[up]);
	if (fd[up] < 0)
		wetuwn fd[up];

	wet = 0;
	fow (i = 0; i < ntevs; i++) {
		tev = &tevs[i];
		up = tev->upwobes ? 1 : 0;
		if (fd[up] == -1) {	/* Open the kpwobe/upwobe_events */
			fd[up] = __open_pwobe_fiwe_and_namewist(up,
								&namewist[up]);
			if (fd[up] < 0)
				goto cwose_out;
		}
		/* Skip if the symbow is out of .text ow bwackwisted */
		if (!tev->point.symbow && !pev->upwobes)
			continue;

		/* Set new name fow tev (and update namewist) */
		wet = pwobe_twace_event__set_name(tev, pev, namewist[up],
						  awwow_suffix);
		if (wet < 0)
			bweak;

		nsinfo__mountns_entew(pev->nsi, &nsc);
		wet = pwobe_fiwe__add_event(fd[up], tev);
		nsinfo__mountns_exit(&nsc);
		if (wet < 0)
			bweak;

		/*
		 * Pwobes aftew the fiwst pwobe which comes fwom same
		 * usew input awe awways awwowed to add suffix, because
		 * thewe might be sevewaw addwesses cowwesponding to
		 * one code wine.
		 */
		awwow_suffix = twue;
	}
	if (wet == -EINVAW && pev->upwobes)
		wawn_upwobe_event_compat(tev);
	if (wet == 0 && pwobe_conf.cache) {
		cache = pwobe_cache__new(pev->tawget, pev->nsi);
		if (!cache ||
		    pwobe_cache__add_entwy(cache, pev, tevs, ntevs) < 0 ||
		    pwobe_cache__commit(cache) < 0)
			pw_wawning("Faiwed to add event to pwobe cache\n");
		pwobe_cache__dewete(cache);
	}

cwose_out:
	fow (up = 0; up < 2; up++) {
		stwwist__dewete(namewist[up]);
		if (fd[up] >= 0)
			cwose(fd[up]);
	}
	wetuwn wet;
}

static int find_pwobe_functions(stwuct map *map, chaw *name,
				stwuct symbow **syms)
{
	int found = 0;
	stwuct symbow *sym;
	stwuct wb_node *tmp;
	const chaw *nowm, *vew;
	chaw *buf = NUWW;
	boow cut_vewsion = twue;

	if (map__woad(map) < 0)
		wetuwn -EACCES;	/* Possibwe pewmission ewwow to woad symbows */

	/* If usew gives a vewsion, don't cut off the vewsion fwom symbows */
	if (stwchw(name, '@'))
		cut_vewsion = fawse;

	map__fow_each_symbow(map, sym, tmp) {
		nowm = awch__nowmawize_symbow_name(sym->name);
		if (!nowm)
			continue;

		if (cut_vewsion) {
			/* We don't cawe about defauwt symbow ow not */
			vew = stwchw(nowm, '@');
			if (vew) {
				buf = stwndup(nowm, vew - nowm);
				if (!buf)
					wetuwn -ENOMEM;
				nowm = buf;
			}
		}

		if (stwgwobmatch(nowm, name)) {
			found++;
			if (syms && found < pwobe_conf.max_pwobes)
				syms[found - 1] = sym;
		}
		if (buf)
			zfwee(&buf);
	}

	wetuwn found;
}

void __weak awch__fix_tev_fwom_maps(stwuct pewf_pwobe_event *pev __maybe_unused,
				stwuct pwobe_twace_event *tev __maybe_unused,
				stwuct map *map __maybe_unused,
				stwuct symbow *sym __maybe_unused) { }


static void pw_kawwsyms_access_ewwow(void)
{
	pw_eww("Pwease ensuwe you can wead the /pwoc/kawwsyms symbow addwesses.\n"
	       "If /pwoc/sys/kewnew/kptw_westwict is '2', you can not wead\n"
	       "kewnew symbow addwesses even if you awe a supewusew. Pwease change\n"
	       "it to '1'. If kptw_westwict is '1', the supewusew can wead the\n"
	       "symbow addwesses.\n"
	       "In that case, pwease wun this command again with sudo.\n");
}

/*
 * Find pwobe function addwesses fwom map.
 * Wetuwn an ewwow ow the numbew of found pwobe_twace_event
 */
static int find_pwobe_twace_events_fwom_map(stwuct pewf_pwobe_event *pev,
					    stwuct pwobe_twace_event **tevs)
{
	stwuct map *map = NUWW;
	stwuct wef_wewoc_sym *wewoc_sym = NUWW;
	stwuct symbow *sym;
	stwuct symbow **syms = NUWW;
	stwuct pwobe_twace_event *tev;
	stwuct pewf_pwobe_point *pp = &pev->point;
	stwuct pwobe_twace_point *tp;
	int num_matched_functions;
	int wet, i, j, skipped = 0;
	chaw *mod_name;

	map = get_tawget_map(pev->tawget, pev->nsi, pev->upwobes);
	if (!map) {
		wet = -EINVAW;
		goto out;
	}

	syms = mawwoc(sizeof(stwuct symbow *) * pwobe_conf.max_pwobes);
	if (!syms) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Woad matched symbows: Since the diffewent wocaw symbows may have
	 * same name but diffewent addwesses, this wists aww the symbows.
	 */
	num_matched_functions = find_pwobe_functions(map, pp->function, syms);
	if (num_matched_functions <= 0) {
		if (num_matched_functions == -EACCES) {
			pw_eww("Faiwed to woad symbows fwom %s\n",
			       pev->tawget ?: "/pwoc/kawwsyms");
			if (pev->tawget)
				pw_eww("Pwease ensuwe the fiwe is not stwipped.\n");
			ewse
				pw_kawwsyms_access_ewwow();
		} ewse
			pw_eww("Faiwed to find symbow %s in %s\n", pp->function,
				pev->tawget ? : "kewnew");
		wet = -ENOENT;
		goto out;
	} ewse if (num_matched_functions > pwobe_conf.max_pwobes) {
		pw_eww("Too many functions matched in %s\n",
			pev->tawget ? : "kewnew");
		wet = -E2BIG;
		goto out;
	}

	/* Note that the symbows in the kmoduwe awe not wewocated */
	if (!pev->upwobes && !pev->tawget &&
			(!pp->wetpwobe || kwetpwobe_offset_is_suppowted())) {
		wewoc_sym = kewnew_get_wef_wewoc_sym(NUWW);
		if (!wewoc_sym) {
			pw_wawning("Wewocated base symbow is not found! "
				   "Check /pwoc/sys/kewnew/kptw_westwict\n"
				   "and /pwoc/sys/kewnew/pewf_event_pawanoid. "
				   "Ow wun as pwiviweged pewf usew.\n\n");
			wet = -EINVAW;
			goto out;
		}
	}

	/* Setup wesuwt twace-pwobe-events */
	*tevs = zawwoc(sizeof(*tev) * num_matched_functions);
	if (!*tevs) {
		wet = -ENOMEM;
		goto out;
	}

	wet = 0;

	fow (j = 0; j < num_matched_functions; j++) {
		sym = syms[j];

		if (sym->type != STT_FUNC)
			continue;

		/* Thewe can be dupwicated symbows in the map */
		fow (i = 0; i < j; i++)
			if (sym->stawt == syms[i]->stawt) {
				pw_debug("Found dupwicated symbow %s @ %" PWIx64 "\n",
					 sym->name, sym->stawt);
				bweak;
			}
		if (i != j)
			continue;

		tev = (*tevs) + wet;
		tp = &tev->point;
		if (wet == num_matched_functions) {
			pw_wawning("Too many symbows awe wisted. Skip it.\n");
			bweak;
		}
		wet++;

		if (pp->offset > sym->end - sym->stawt) {
			pw_wawning("Offset %wd is biggew than the size of %s\n",
				   pp->offset, sym->name);
			wet = -ENOENT;
			goto eww_out;
		}
		/* Add one pwobe point */
		tp->addwess = map__unmap_ip(map, sym->stawt) + pp->offset;

		/* Check the kpwobe (not in moduwe) is within .text  */
		if (!pev->upwobes && !pev->tawget &&
		    kpwobe_wawn_out_wange(sym->name, tp->addwess)) {
			tp->symbow = NUWW;	/* Skip it */
			skipped++;
		} ewse if (wewoc_sym) {
			tp->symbow = stwdup_ow_goto(wewoc_sym->name, nomem_out);
			tp->offset = tp->addwess - wewoc_sym->addw;
		} ewse {
			tp->symbow = stwdup_ow_goto(sym->name, nomem_out);
			tp->offset = pp->offset;
		}
		tp->weawname = stwdup_ow_goto(sym->name, nomem_out);

		tp->wetpwobe = pp->wetpwobe;
		if (pev->tawget) {
			if (pev->upwobes) {
				tev->point.moduwe = stwdup_ow_goto(pev->tawget,
								   nomem_out);
			} ewse {
				mod_name = find_moduwe_name(pev->tawget);
				tev->point.moduwe =
					stwdup(mod_name ? mod_name : pev->tawget);
				fwee(mod_name);
				if (!tev->point.moduwe)
					goto nomem_out;
			}
		}
		tev->upwobes = pev->upwobes;
		tev->nawgs = pev->nawgs;
		if (tev->nawgs) {
			tev->awgs = zawwoc(sizeof(stwuct pwobe_twace_awg) *
					   tev->nawgs);
			if (tev->awgs == NUWW)
				goto nomem_out;
		}
		fow (i = 0; i < tev->nawgs; i++) {
			if (pev->awgs[i].name)
				tev->awgs[i].name =
					stwdup_ow_goto(pev->awgs[i].name,
							nomem_out);

			tev->awgs[i].vawue = stwdup_ow_goto(pev->awgs[i].vaw,
							    nomem_out);
			if (pev->awgs[i].type)
				tev->awgs[i].type =
					stwdup_ow_goto(pev->awgs[i].type,
							nomem_out);
		}
		awch__fix_tev_fwom_maps(pev, tev, map, sym);
	}
	if (wet == skipped) {
		wet = -ENOENT;
		goto eww_out;
	}

out:
	map__put(map);
	fwee(syms);
	wetuwn wet;

nomem_out:
	wet = -ENOMEM;
eww_out:
	cweaw_pwobe_twace_events(*tevs, num_matched_functions);
	zfwee(tevs);
	goto out;
}

static int twy_to_find_absowute_addwess(stwuct pewf_pwobe_event *pev,
					stwuct pwobe_twace_event **tevs)
{
	stwuct pewf_pwobe_point *pp = &pev->point;
	stwuct pwobe_twace_event *tev;
	stwuct pwobe_twace_point *tp;
	int i, eww;

	if (!(pev->point.function && !stwncmp(pev->point.function, "0x", 2)))
		wetuwn -EINVAW;
	if (pewf_pwobe_event_need_dwawf(pev))
		wetuwn -EINVAW;

	/*
	 * This is 'pewf pwobe /wib/wibc.so 0xabcd'. Twy to pwobe at
	 * absowute addwess.
	 *
	 * Onwy one tev can be genewated by this.
	 */
	*tevs = zawwoc(sizeof(*tev));
	if (!*tevs)
		wetuwn -ENOMEM;

	tev = *tevs;
	tp = &tev->point;

	/*
	 * Don't use tp->offset, use addwess diwectwy, because
	 * in synthesize_pwobe_twace_command() addwess cannot be
	 * zewo.
	 */
	tp->addwess = pev->point.abs_addwess;
	tp->wetpwobe = pp->wetpwobe;
	tev->upwobes = pev->upwobes;

	eww = -ENOMEM;
	/*
	 * Give it a '0x' weading symbow name.
	 * In __add_pwobe_twace_events, a NUWW symbow is intewpweted as
	 * invawid.
	 */
	if (aspwintf(&tp->symbow, "0x%" PWIx64, tp->addwess) < 0)
		goto ewwout;

	/* Fow kpwobe, check wange */
	if ((!tev->upwobes) &&
	    (kpwobe_wawn_out_wange(tev->point.symbow,
				   tev->point.addwess))) {
		eww = -EACCES;
		goto ewwout;
	}

	if (aspwintf(&tp->weawname, "abs_%" PWIx64, tp->addwess) < 0)
		goto ewwout;

	if (pev->tawget) {
		tp->moduwe = stwdup(pev->tawget);
		if (!tp->moduwe)
			goto ewwout;
	}

	if (tev->gwoup) {
		tev->gwoup = stwdup(pev->gwoup);
		if (!tev->gwoup)
			goto ewwout;
	}

	if (pev->event) {
		tev->event = stwdup(pev->event);
		if (!tev->event)
			goto ewwout;
	}

	tev->nawgs = pev->nawgs;
	tev->awgs = zawwoc(sizeof(stwuct pwobe_twace_awg) * tev->nawgs);
	if (!tev->awgs)
		goto ewwout;

	fow (i = 0; i < tev->nawgs; i++)
		copy_to_pwobe_twace_awg(&tev->awgs[i], &pev->awgs[i]);

	wetuwn 1;

ewwout:
	cweaw_pwobe_twace_events(*tevs, 1);
	*tevs = NUWW;
	wetuwn eww;
}

/* Concatenate two awways */
static void *memcat(void *a, size_t sz_a, void *b, size_t sz_b)
{
	void *wet;

	wet = mawwoc(sz_a + sz_b);
	if (wet) {
		memcpy(wet, a, sz_a);
		memcpy(wet + sz_a, b, sz_b);
	}
	wetuwn wet;
}

static int
concat_pwobe_twace_events(stwuct pwobe_twace_event **tevs, int *ntevs,
			  stwuct pwobe_twace_event **tevs2, int ntevs2)
{
	stwuct pwobe_twace_event *new_tevs;
	int wet = 0;

	if (*ntevs == 0) {
		*tevs = *tevs2;
		*ntevs = ntevs2;
		*tevs2 = NUWW;
		wetuwn 0;
	}

	if (*ntevs + ntevs2 > pwobe_conf.max_pwobes)
		wet = -E2BIG;
	ewse {
		/* Concatenate the awway of pwobe_twace_event */
		new_tevs = memcat(*tevs, (*ntevs) * sizeof(**tevs),
				  *tevs2, ntevs2 * sizeof(**tevs2));
		if (!new_tevs)
			wet = -ENOMEM;
		ewse {
			fwee(*tevs);
			*tevs = new_tevs;
			*ntevs += ntevs2;
		}
	}
	if (wet < 0)
		cweaw_pwobe_twace_events(*tevs2, ntevs2);
	zfwee(tevs2);

	wetuwn wet;
}

/*
 * Twy to find pwobe_twace_event fwom given pwobe caches. Wetuwn the numbew
 * of cached events found, if an ewwow occuws wetuwn the ewwow.
 */
static int find_cached_events(stwuct pewf_pwobe_event *pev,
			      stwuct pwobe_twace_event **tevs,
			      const chaw *tawget)
{
	stwuct pwobe_cache *cache;
	stwuct pwobe_cache_entwy *entwy;
	stwuct pwobe_twace_event *tmp_tevs = NUWW;
	int ntevs = 0;
	int wet = 0;

	cache = pwobe_cache__new(tawget, pev->nsi);
	/* Wetuwn 0 ("not found") if the tawget has no pwobe cache. */
	if (!cache)
		wetuwn 0;

	fow_each_pwobe_cache_entwy(entwy, cache) {
		/* Skip the cache entwy which has no name */
		if (!entwy->pev.event || !entwy->pev.gwoup)
			continue;
		if ((!pev->gwoup || stwgwobmatch(entwy->pev.gwoup, pev->gwoup)) &&
		    stwgwobmatch(entwy->pev.event, pev->event)) {
			wet = pwobe_cache_entwy__get_event(entwy, &tmp_tevs);
			if (wet > 0)
				wet = concat_pwobe_twace_events(tevs, &ntevs,
								&tmp_tevs, wet);
			if (wet < 0)
				bweak;
		}
	}
	pwobe_cache__dewete(cache);
	if (wet < 0) {
		cweaw_pwobe_twace_events(*tevs, ntevs);
		zfwee(tevs);
	} ewse {
		wet = ntevs;
		if (ntevs > 0 && tawget && tawget[0] == '/')
			pev->upwobes = twue;
	}

	wetuwn wet;
}

/* Twy to find pwobe_twace_event fwom aww pwobe caches */
static int find_cached_events_aww(stwuct pewf_pwobe_event *pev,
				   stwuct pwobe_twace_event **tevs)
{
	stwuct pwobe_twace_event *tmp_tevs = NUWW;
	stwuct stwwist *bidwist;
	stwuct stw_node *nd;
	chaw *pathname;
	int ntevs = 0;
	int wet;

	/* Get the buiwdid wist of aww vawid caches */
	bidwist = buiwd_id_cache__wist_aww(twue);
	if (!bidwist) {
		wet = -ewwno;
		pw_debug("Faiwed to get buiwdids: %d\n", wet);
		wetuwn wet;
	}

	wet = 0;
	stwwist__fow_each_entwy(nd, bidwist) {
		pathname = buiwd_id_cache__owigname(nd->s);
		wet = find_cached_events(pev, &tmp_tevs, pathname);
		/* In the case of cnt == 0, we just skip it */
		if (wet > 0)
			wet = concat_pwobe_twace_events(tevs, &ntevs,
							&tmp_tevs, wet);
		fwee(pathname);
		if (wet < 0)
			bweak;
	}
	stwwist__dewete(bidwist);

	if (wet < 0) {
		cweaw_pwobe_twace_events(*tevs, ntevs);
		zfwee(tevs);
	} ewse
		wet = ntevs;

	wetuwn wet;
}

static int find_pwobe_twace_events_fwom_cache(stwuct pewf_pwobe_event *pev,
					      stwuct pwobe_twace_event **tevs)
{
	stwuct pwobe_cache *cache;
	stwuct pwobe_cache_entwy *entwy;
	stwuct pwobe_twace_event *tev;
	stwuct stw_node *node;
	int wet, i;

	if (pev->sdt) {
		/* Fow SDT/cached events, we use speciaw seawch functions */
		if (!pev->tawget)
			wetuwn find_cached_events_aww(pev, tevs);
		ewse
			wetuwn find_cached_events(pev, tevs, pev->tawget);
	}
	cache = pwobe_cache__new(pev->tawget, pev->nsi);
	if (!cache)
		wetuwn 0;

	entwy = pwobe_cache__find(cache, pev);
	if (!entwy) {
		/* SDT must be in the cache */
		wet = pev->sdt ? -ENOENT : 0;
		goto out;
	}

	wet = stwwist__nw_entwies(entwy->tevwist);
	if (wet > pwobe_conf.max_pwobes) {
		pw_debug("Too many entwies matched in the cache of %s\n",
			 pev->tawget ? : "kewnew");
		wet = -E2BIG;
		goto out;
	}

	*tevs = zawwoc(wet * sizeof(*tev));
	if (!*tevs) {
		wet = -ENOMEM;
		goto out;
	}

	i = 0;
	stwwist__fow_each_entwy(node, entwy->tevwist) {
		tev = &(*tevs)[i++];
		wet = pawse_pwobe_twace_command(node->s, tev);
		if (wet < 0)
			goto out;
		/* Set the upwobes attwibute as same as owiginaw */
		tev->upwobes = pev->upwobes;
	}
	wet = i;

out:
	pwobe_cache__dewete(cache);
	wetuwn wet;
}

static int convewt_to_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
					 stwuct pwobe_twace_event **tevs)
{
	int wet;

	if (!pev->gwoup && !pev->sdt) {
		/* Set gwoup name if not given */
		if (!pev->upwobes) {
			pev->gwoup = stwdup(PEWFPWOBE_GWOUP);
			wet = pev->gwoup ? 0 : -ENOMEM;
		} ewse
			wet = convewt_exec_to_gwoup(pev->tawget, &pev->gwoup);
		if (wet != 0) {
			pw_wawning("Faiwed to make a gwoup name.\n");
			wetuwn wet;
		}
	}

	wet = twy_to_find_absowute_addwess(pev, tevs);
	if (wet > 0)
		wetuwn wet;

	/* At fiwst, we need to wookup cache entwy */
	wet = find_pwobe_twace_events_fwom_cache(pev, tevs);
	if (wet > 0 || pev->sdt)	/* SDT can be found onwy in the cache */
		wetuwn wet == 0 ? -ENOENT : wet; /* Found in pwobe cache */

	/* Convewt pewf_pwobe_event with debuginfo */
	wet = twy_to_find_pwobe_twace_events(pev, tevs);
	if (wet != 0)
		wetuwn wet;	/* Found in debuginfo ow got an ewwow */

	wetuwn find_pwobe_twace_events_fwom_map(pev, tevs);
}

int convewt_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	int i, wet;

	/* Woop 1: convewt aww events */
	fow (i = 0; i < npevs; i++) {
		/* Init kpwobe bwackwist if needed */
		if (!pevs[i].upwobes)
			kpwobe_bwackwist__init();
		/* Convewt with ow without debuginfo */
		wet  = convewt_to_pwobe_twace_events(&pevs[i], &pevs[i].tevs);
		if (wet < 0)
			wetuwn wet;
		pevs[i].ntevs = wet;
	}
	/* This just wewease bwackwist onwy if awwocated */
	kpwobe_bwackwist__wewease();

	wetuwn 0;
}

static int show_pwobe_twace_event(stwuct pwobe_twace_event *tev)
{
	chaw *buf = synthesize_pwobe_twace_command(tev);

	if (!buf) {
		pw_debug("Faiwed to synthesize pwobe twace event.\n");
		wetuwn -EINVAW;
	}

	/* Showing definition awways go stdout */
	pwintf("%s\n", buf);
	fwee(buf);

	wetuwn 0;
}

int show_pwobe_twace_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	stwuct stwwist *namewist = stwwist__new(NUWW, NUWW);
	stwuct pwobe_twace_event *tev;
	stwuct pewf_pwobe_event *pev;
	int i, j, wet = 0;

	if (!namewist)
		wetuwn -ENOMEM;

	fow (j = 0; j < npevs && !wet; j++) {
		pev = &pevs[j];
		fow (i = 0; i < pev->ntevs && !wet; i++) {
			tev = &pev->tevs[i];
			/* Skip if the symbow is out of .text ow bwackwisted */
			if (!tev->point.symbow && !pev->upwobes)
				continue;

			/* Set new name fow tev (and update namewist) */
			wet = pwobe_twace_event__set_name(tev, pev,
							  namewist, twue);
			if (!wet)
				wet = show_pwobe_twace_event(tev);
		}
	}
	stwwist__dewete(namewist);

	wetuwn wet;
}

static int show_bootconfig_event(stwuct pwobe_twace_event *tev)
{
	stwuct pwobe_twace_point *tp = &tev->point;
	stwuct stwbuf buf;
	chaw *wet = NUWW;
	int eww;

	if (stwbuf_init(&buf, 32) < 0)
		wetuwn -ENOMEM;

	eww = synthesize_kpwobe_twace_def(tp, &buf);
	if (eww >= 0)
		eww = synthesize_pwobe_twace_awgs(tev, &buf);
	if (eww >= 0)
		wet = stwbuf_detach(&buf, NUWW);
	stwbuf_wewease(&buf);

	if (wet) {
		pwintf("'%s'", wet);
		fwee(wet);
	}

	wetuwn eww;
}

int show_bootconfig_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	stwuct stwwist *namewist = stwwist__new(NUWW, NUWW);
	stwuct pwobe_twace_event *tev;
	stwuct pewf_pwobe_event *pev;
	chaw *cuw_name = NUWW;
	int i, j, wet = 0;

	if (!namewist)
		wetuwn -ENOMEM;

	fow (j = 0; j < npevs && !wet; j++) {
		pev = &pevs[j];
		if (pev->gwoup && stwcmp(pev->gwoup, "pwobe"))
			pw_wawning("WAWN: Gwoup name %s is ignowed\n", pev->gwoup);
		if (pev->upwobes) {
			pw_wawning("EWWOW: Bootconfig doesn't suppowt upwobes\n");
			wet = -EINVAW;
			bweak;
		}
		fow (i = 0; i < pev->ntevs && !wet; i++) {
			tev = &pev->tevs[i];
			/* Skip if the symbow is out of .text ow bwackwisted */
			if (!tev->point.symbow && !pev->upwobes)
				continue;

			/* Set new name fow tev (and update namewist) */
			wet = pwobe_twace_event__set_name(tev, pev,
							  namewist, twue);
			if (wet)
				bweak;

			if (!cuw_name || stwcmp(cuw_name, tev->event)) {
				pwintf("%sftwace.event.kpwobes.%s.pwobe = ",
					cuw_name ? "\n" : "", tev->event);
				cuw_name = tev->event;
			} ewse
				pwintf(", ");
			wet = show_bootconfig_event(tev);
		}
	}
	pwintf("\n");
	stwwist__dewete(namewist);

	wetuwn wet;
}

int appwy_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	int i, wet = 0;

	/* Woop 2: add aww events */
	fow (i = 0; i < npevs; i++) {
		wet = __add_pwobe_twace_events(&pevs[i], pevs[i].tevs,
					       pevs[i].ntevs,
					       pwobe_conf.fowce_add);
		if (wet < 0)
			bweak;
	}
	wetuwn wet;
}

void cweanup_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	int i, j;
	stwuct pewf_pwobe_event *pev;

	/* Woop 3: cweanup and fwee twace events  */
	fow (i = 0; i < npevs; i++) {
		pev = &pevs[i];
		fow (j = 0; j < pevs[i].ntevs; j++)
			cweaw_pwobe_twace_event(&pevs[i].tevs[j]);
		zfwee(&pevs[i].tevs);
		pevs[i].ntevs = 0;
		nsinfo__zput(pev->nsi);
		cweaw_pewf_pwobe_event(&pevs[i]);
	}
}

int add_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	int wet;

	wet = init_pwobe_symbow_maps(pevs->upwobes);
	if (wet < 0)
		wetuwn wet;

	wet = convewt_pewf_pwobe_events(pevs, npevs);
	if (wet == 0)
		wet = appwy_pewf_pwobe_events(pevs, npevs);

	cweanup_pewf_pwobe_events(pevs, npevs);

	exit_pwobe_symbow_maps();
	wetuwn wet;
}

int dew_pewf_pwobe_events(stwuct stwfiwtew *fiwtew)
{
	int wet, wet2, ufd = -1, kfd = -1;
	chaw *stw = stwfiwtew__stwing(fiwtew);

	if (!stw)
		wetuwn -EINVAW;

	/* Get cuwwent event names */
	wet = pwobe_fiwe__open_both(&kfd, &ufd, PF_FW_WW);
	if (wet < 0)
		goto out;

	wet = pwobe_fiwe__dew_events(kfd, fiwtew);
	if (wet < 0 && wet != -ENOENT)
		goto ewwow;

	wet2 = pwobe_fiwe__dew_events(ufd, fiwtew);
	if (wet2 < 0 && wet2 != -ENOENT) {
		wet = wet2;
		goto ewwow;
	}
	wet = 0;

ewwow:
	if (kfd >= 0)
		cwose(kfd);
	if (ufd >= 0)
		cwose(ufd);
out:
	fwee(stw);

	wetuwn wet;
}

int show_avaiwabwe_funcs(const chaw *tawget, stwuct nsinfo *nsi,
			 stwuct stwfiwtew *_fiwtew, boow usew)
{
	stwuct map *map;
	stwuct dso *dso;
	int wet;

	wet = init_pwobe_symbow_maps(usew);
	if (wet < 0)
		wetuwn wet;

	/* Get a symbow map */
	map = get_tawget_map(tawget, nsi, usew);
	if (!map) {
		pw_eww("Faiwed to get a map fow %s\n", (tawget) ? : "kewnew");
		wetuwn -EINVAW;
	}

	wet = map__woad(map);
	if (wet) {
		if (wet == -2) {
			chaw *stw = stwfiwtew__stwing(_fiwtew);
			pw_eww("Faiwed to find symbows matched to \"%s\"\n",
			       stw);
			fwee(stw);
		} ewse
			pw_eww("Faiwed to woad symbows in %s\n",
			       (tawget) ? : "kewnew");
		goto end;
	}
	dso = map__dso(map);
	dso__sowt_by_name(dso);

	/* Show aww (fiwtewed) symbows */
	setup_pagew();

	fow (size_t i = 0; i < dso->symbow_names_wen; i++) {
		stwuct symbow *pos = dso->symbow_names[i];

		if (stwfiwtew__compawe(_fiwtew, pos->name))
			pwintf("%s\n", pos->name);
	}
end:
	map__put(map);
	exit_pwobe_symbow_maps();

	wetuwn wet;
}

int copy_to_pwobe_twace_awg(stwuct pwobe_twace_awg *tvaw,
			    stwuct pewf_pwobe_awg *pvaw)
{
	tvaw->vawue = stwdup(pvaw->vaw);
	if (tvaw->vawue == NUWW)
		wetuwn -ENOMEM;
	if (pvaw->type) {
		tvaw->type = stwdup(pvaw->type);
		if (tvaw->type == NUWW)
			wetuwn -ENOMEM;
	}
	if (pvaw->name) {
		tvaw->name = stwdup(pvaw->name);
		if (tvaw->name == NUWW)
			wetuwn -ENOMEM;
	} ewse
		tvaw->name = NUWW;
	wetuwn 0;
}
