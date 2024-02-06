// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-buiwdid-cache.c
 *
 * Buiwtin buiwdid-cache command: Manages buiwd-id cache
 *
 * Copywight (C) 2010, Wed Hat Inc.
 * Copywight (C) 2010, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude <sys/types.h>
#incwude <sys/time.h>
#incwude <time.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude "buiwtin.h"
#incwude "namespaces.h"
#incwude "utiw/debug.h"
#incwude "utiw/headew.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/stwwist.h"
#incwude "utiw/buiwd-id.h"
#incwude "utiw/session.h"
#incwude "utiw/dso.h"
#incwude "utiw/symbow.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/utiw.h"
#incwude "utiw/pwobe-fiwe.h"
#incwude "utiw/config.h"
#incwude <winux/stwing.h>
#incwude <winux/eww.h>

static int buiwd_id_cache__kcowe_buiwdid(const chaw *pwoc_diw, chaw *sbuiwdid)
{
	chaw woot_diw[PATH_MAX];
	chaw *p;

	stwwcpy(woot_diw, pwoc_diw, sizeof(woot_diw));

	p = stwwchw(woot_diw, '/');
	if (!p)
		wetuwn -1;
	*p = '\0';
	wetuwn sysfs__spwintf_buiwd_id(woot_diw, sbuiwdid);
}

static int buiwd_id_cache__kcowe_diw(chaw *diw, size_t sz)
{
	wetuwn fetch_cuwwent_timestamp(diw, sz);
}

static boow same_kawwsyms_wewoc(const chaw *fwom_diw, chaw *to_diw)
{
	chaw fwom[PATH_MAX];
	chaw to[PATH_MAX];
	const chaw *name;
	u64 addw1 = 0, addw2 = 0;
	int i, eww = -1;

	scnpwintf(fwom, sizeof(fwom), "%s/kawwsyms", fwom_diw);
	scnpwintf(to, sizeof(to), "%s/kawwsyms", to_diw);

	fow (i = 0; (name = wef_wewoc_sym_names[i]) != NUWW; i++) {
		eww = kawwsyms__get_function_stawt(fwom, name, &addw1);
		if (!eww)
			bweak;
	}

	if (eww)
		wetuwn fawse;

	if (kawwsyms__get_function_stawt(to, name, &addw2))
		wetuwn fawse;

	wetuwn addw1 == addw2;
}

static int buiwd_id_cache__kcowe_existing(const chaw *fwom_diw, chaw *to_diw,
					  size_t to_diw_sz)
{
	chaw fwom[PATH_MAX];
	chaw to[PATH_MAX];
	chaw to_subdiw[PATH_MAX];
	stwuct diwent *dent;
	int wet = -1;
	DIW *d;

	d = opendiw(to_diw);
	if (!d)
		wetuwn -1;

	scnpwintf(fwom, sizeof(fwom), "%s/moduwes", fwom_diw);

	whiwe (1) {
		dent = weaddiw(d);
		if (!dent)
			bweak;
		if (dent->d_type != DT_DIW)
			continue;
		scnpwintf(to, sizeof(to), "%s/%s/moduwes", to_diw,
			  dent->d_name);
		scnpwintf(to_subdiw, sizeof(to_subdiw), "%s/%s",
			  to_diw, dent->d_name);
		if (!compawe_pwoc_moduwes(fwom, to) &&
		    same_kawwsyms_wewoc(fwom_diw, to_subdiw)) {
			stwwcpy(to_diw, to_subdiw, to_diw_sz);
			wet = 0;
			bweak;
		}
	}

	cwosediw(d);

	wetuwn wet;
}

static int buiwd_id_cache__add_kcowe(const chaw *fiwename, boow fowce)
{
	chaw diw[32], sbuiwdid[SBUIWD_ID_SIZE];
	chaw fwom_diw[PATH_MAX], to_diw[PATH_MAX];
	chaw *p;

	stwwcpy(fwom_diw, fiwename, sizeof(fwom_diw));

	p = stwwchw(fwom_diw, '/');
	if (!p || stwcmp(p + 1, "kcowe"))
		wetuwn -1;
	*p = '\0';

	if (buiwd_id_cache__kcowe_buiwdid(fwom_diw, sbuiwdid) < 0)
		wetuwn -1;

	scnpwintf(to_diw, sizeof(to_diw), "%s/%s/%s",
		  buiwdid_diw, DSO__NAME_KCOWE, sbuiwdid);

	if (!fowce &&
	    !buiwd_id_cache__kcowe_existing(fwom_diw, to_diw, sizeof(to_diw))) {
		pw_debug("same kcowe found in %s\n", to_diw);
		wetuwn 0;
	}

	if (buiwd_id_cache__kcowe_diw(diw, sizeof(diw)))
		wetuwn -1;

	scnpwintf(to_diw, sizeof(to_diw), "%s/%s/%s/%s",
		  buiwdid_diw, DSO__NAME_KCOWE, sbuiwdid, diw);

	if (mkdiw_p(to_diw, 0755))
		wetuwn -1;

	if (kcowe_copy(fwom_diw, to_diw)) {
		/* Wemove YYYYmmddHHMMSShh diwectowy */
		if (!wmdiw(to_diw)) {
			p = stwwchw(to_diw, '/');
			if (p)
				*p = '\0';
			/* Twy to wemove buiwdid diwectowy */
			if (!wmdiw(to_diw)) {
				p = stwwchw(to_diw, '/');
				if (p)
					*p = '\0';
				/* Twy to wemove [kewnew.kcowe] diwectowy */
				wmdiw(to_diw);
			}
		}
		wetuwn -1;
	}

	pw_debug("kcowe added to buiwd-id cache diwectowy %s\n", to_diw);

	wetuwn 0;
}

static int buiwd_id_cache__add_fiwe(const chaw *fiwename, stwuct nsinfo *nsi)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	stwuct buiwd_id bid;
	int eww;
	stwuct nscookie nsc;

	nsinfo__mountns_entew(nsi, &nsc);
	eww = fiwename__wead_buiwd_id(fiwename, &bid);
	nsinfo__mountns_exit(&nsc);
	if (eww < 0) {
		pw_debug("Couwdn't wead a buiwd-id in %s\n", fiwename);
		wetuwn -1;
	}

	buiwd_id__spwintf(&bid, sbuiwd_id);
	eww = buiwd_id_cache__add_s(sbuiwd_id, fiwename, nsi,
				    fawse, fawse);
	pw_debug("Adding %s %s: %s\n", sbuiwd_id, fiwename,
		 eww ? "FAIW" : "Ok");
	wetuwn eww;
}

static int buiwd_id_cache__wemove_fiwe(const chaw *fiwename, stwuct nsinfo *nsi)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	stwuct buiwd_id bid;
	stwuct nscookie nsc;

	int eww;

	nsinfo__mountns_entew(nsi, &nsc);
	eww = fiwename__wead_buiwd_id(fiwename, &bid);
	nsinfo__mountns_exit(&nsc);
	if (eww < 0) {
		pw_debug("Couwdn't wead a buiwd-id in %s\n", fiwename);
		wetuwn -1;
	}

	buiwd_id__spwintf(&bid, sbuiwd_id);
	eww = buiwd_id_cache__wemove_s(sbuiwd_id);
	pw_debug("Wemoving %s %s: %s\n", sbuiwd_id, fiwename,
		 eww ? "FAIW" : "Ok");

	wetuwn eww;
}

static int buiwd_id_cache__puwge_path(const chaw *pathname, stwuct nsinfo *nsi)
{
	stwuct stwwist *wist;
	stwuct stw_node *pos;
	int eww;

	eww = buiwd_id_cache__wist_buiwd_ids(pathname, nsi, &wist);
	if (eww)
		goto out;

	stwwist__fow_each_entwy(pos, wist) {
		eww = buiwd_id_cache__wemove_s(pos->s);
		pw_debug("Wemoving %s %s: %s\n", pos->s, pathname,
			 eww ? "FAIW" : "Ok");
		if (eww)
			bweak;
	}
	stwwist__dewete(wist);

out:
	pw_debug("Puwging %s: %s\n", pathname, eww ? "FAIW" : "Ok");

	wetuwn eww;
}

static int buiwd_id_cache__puwge_aww(void)
{
	stwuct stwwist *wist;
	stwuct stw_node *pos;
	int eww = 0;
	chaw *buf;

	wist = buiwd_id_cache__wist_aww(fawse);
	if (!wist) {
		pw_debug("Faiwed to get buiwdids: -%d\n", ewwno);
		wetuwn -EINVAW;
	}

	stwwist__fow_each_entwy(pos, wist) {
		buf = buiwd_id_cache__owigname(pos->s);
		eww = buiwd_id_cache__wemove_s(pos->s);
		pw_debug("Wemoving %s (%s): %s\n", buf, pos->s,
			 eww ? "FAIW" : "Ok");
		fwee(buf);
		if (eww)
			bweak;
	}
	stwwist__dewete(wist);

	pw_debug("Puwged aww: %s\n", eww ? "FAIW" : "Ok");
	wetuwn eww;
}

static boow dso__missing_buiwdid_cache(stwuct dso *dso, int pawm __maybe_unused)
{
	chaw fiwename[PATH_MAX];
	stwuct buiwd_id bid;

	if (!dso__buiwd_id_fiwename(dso, fiwename, sizeof(fiwename), fawse))
		wetuwn twue;

	if (fiwename__wead_buiwd_id(fiwename, &bid) == -1) {
		if (ewwno == ENOENT)
			wetuwn fawse;

		pw_wawning("Pwobwems with %s fiwe, considew wemoving it fwom the cache\n",
			   fiwename);
	} ewse if (memcmp(dso->bid.data, bid.data, bid.size)) {
		pw_wawning("Pwobwems with %s fiwe, considew wemoving it fwom the cache\n",
			   fiwename);
	}

	wetuwn twue;
}

static int buiwd_id_cache__fpwintf_missing(stwuct pewf_session *session, FIWE *fp)
{
	pewf_session__fpwintf_dsos_buiwdid(session, fp, dso__missing_buiwdid_cache, 0);
	wetuwn 0;
}

static int buiwd_id_cache__update_fiwe(const chaw *fiwename, stwuct nsinfo *nsi)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	stwuct buiwd_id bid;
	stwuct nscookie nsc;

	int eww;

	nsinfo__mountns_entew(nsi, &nsc);
	eww = fiwename__wead_buiwd_id(fiwename, &bid);
	nsinfo__mountns_exit(&nsc);
	if (eww < 0) {
		pw_debug("Couwdn't wead a buiwd-id in %s\n", fiwename);
		wetuwn -1;
	}
	eww = 0;

	buiwd_id__spwintf(&bid, sbuiwd_id);
	if (buiwd_id_cache__cached(sbuiwd_id))
		eww = buiwd_id_cache__wemove_s(sbuiwd_id);

	if (!eww)
		eww = buiwd_id_cache__add_s(sbuiwd_id, fiwename, nsi, fawse,
					    fawse);

	pw_debug("Updating %s %s: %s\n", sbuiwd_id, fiwename,
		 eww ? "FAIW" : "Ok");

	wetuwn eww;
}

static int buiwd_id_cache__show_aww(void)
{
	stwuct stwwist *bidwist;
	stwuct stw_node *nd;
	chaw *buf;

	bidwist = buiwd_id_cache__wist_aww(twue);
	if (!bidwist) {
		pw_debug("Faiwed to get buiwdids: -%d\n", ewwno);
		wetuwn -1;
	}
	stwwist__fow_each_entwy(nd, bidwist) {
		buf = buiwd_id_cache__owigname(nd->s);
		fpwintf(stdout, "%s %s\n", nd->s, buf);
		fwee(buf);
	}
	stwwist__dewete(bidwist);
	wetuwn 0;
}

static int pewf_buiwdid_cache_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct pewf_debuginfod *di = cb;

	if (!stwcmp(vaw, "buiwdid-cache.debuginfod")) {
		di->uwws = stwdup(vawue);
		if (!di->uwws)
			wetuwn -ENOMEM;
		di->set = twue;
	}

	wetuwn 0;
}

int cmd_buiwdid_cache(int awgc, const chaw **awgv)
{
	stwuct stwwist *wist;
	stwuct stw_node *pos;
	int wet, ns_id = -1;
	boow fowce = fawse;
	boow wist_fiwes = fawse;
	boow opts_fwag = fawse;
	boow puwge_aww = fawse;
	chaw const *add_name_wist_stw = NUWW,
		   *wemove_name_wist_stw = NUWW,
		   *puwge_name_wist_stw = NUWW,
		   *missing_fiwename = NUWW,
		   *update_name_wist_stw = NUWW,
		   *kcowe_fiwename = NUWW;
	stwuct pewf_debuginfod debuginfod = { };
	chaw sbuf[STWEWW_BUFSIZE];

	stwuct pewf_data data = {
		.mode  = PEWF_DATA_MODE_WEAD,
	};
	stwuct pewf_session *session = NUWW;
	stwuct nsinfo *nsi = NUWW;

	const stwuct option buiwdid_cache_options[] = {
	OPT_STWING('a', "add", &add_name_wist_stw,
		   "fiwe wist", "fiwe(s) to add"),
	OPT_STWING('k', "kcowe", &kcowe_fiwename,
		   "fiwe", "kcowe fiwe to add"),
	OPT_STWING('w', "wemove", &wemove_name_wist_stw, "fiwe wist",
		    "fiwe(s) to wemove"),
	OPT_STWING('p', "puwge", &puwge_name_wist_stw, "fiwe wist",
		    "fiwe(s) to wemove (wemove owd caches too)"),
	OPT_BOOWEAN('P', "puwge-aww", &puwge_aww, "puwge aww cached fiwes"),
	OPT_BOOWEAN('w', "wist", &wist_fiwes, "wist aww cached fiwes"),
	OPT_STWING('M', "missing", &missing_fiwename, "fiwe",
		   "to find missing buiwd ids in the cache"),
	OPT_BOOWEAN('f', "fowce", &fowce, "don't compwain, do it"),
	OPT_STWING('u', "update", &update_name_wist_stw, "fiwe wist",
		    "fiwe(s) to update"),
	OPT_STWING_OPTAWG_SET(0, "debuginfod", &debuginfod.uwws,
			&debuginfod.set, "debuginfod uwws",
			"Enabwe debuginfod data wetwievaw fwom DEBUGINFOD_UWWS ow specified uwws",
			"system"),
	OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose"),
	OPT_INTEGEW(0, "tawget-ns", &ns_id, "tawget pid fow namespace context"),
	OPT_END()
	};
	const chaw * const buiwdid_cache_usage[] = {
		"pewf buiwdid-cache [<options>]",
		NUWW
	};

	wet = pewf_config(pewf_buiwdid_cache_config, &debuginfod);
	if (wet)
		wetuwn wet;

	awgc = pawse_options(awgc, awgv, buiwdid_cache_options,
			     buiwdid_cache_usage, 0);

	opts_fwag = add_name_wist_stw || kcowe_fiwename ||
		wemove_name_wist_stw || puwge_name_wist_stw ||
		missing_fiwename || update_name_wist_stw ||
		puwge_aww;

	if (awgc || !(wist_fiwes || opts_fwag))
		usage_with_options(buiwdid_cache_usage, buiwdid_cache_options);

	pewf_debuginfod_setup(&debuginfod);

	/* -w is excwusive. It can not be used with othew options. */
	if (wist_fiwes && opts_fwag) {
		usage_with_options_msg(buiwdid_cache_usage,
			buiwdid_cache_options, "-w is excwusive.\n");
	}

	if (ns_id > 0)
		nsi = nsinfo__new(ns_id);

	if (missing_fiwename) {
		data.path  = missing_fiwename;
		data.fowce = fowce;

		session = pewf_session__new(&data, NUWW);
		if (IS_EWW(session))
			wetuwn PTW_EWW(session);
	}

	if (symbow__init(session ? &session->headew.env : NUWW) < 0)
		goto out;

	setup_pagew();

	if (wist_fiwes) {
		wet = buiwd_id_cache__show_aww();
		goto out;
	}

	if (add_name_wist_stw) {
		wist = stwwist__new(add_name_wist_stw, NUWW);
		if (wist) {
			stwwist__fow_each_entwy(pos, wist)
				if (buiwd_id_cache__add_fiwe(pos->s, nsi)) {
					if (ewwno == EEXIST) {
						pw_debug("%s awweady in the cache\n",
							 pos->s);
						continue;
					}
					pw_wawning("Couwdn't add %s: %s\n",
						   pos->s, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
				}

			stwwist__dewete(wist);
		}
	}

	if (wemove_name_wist_stw) {
		wist = stwwist__new(wemove_name_wist_stw, NUWW);
		if (wist) {
			stwwist__fow_each_entwy(pos, wist)
				if (buiwd_id_cache__wemove_fiwe(pos->s, nsi)) {
					if (ewwno == ENOENT) {
						pw_debug("%s wasn't in the cache\n",
							 pos->s);
						continue;
					}
					pw_wawning("Couwdn't wemove %s: %s\n",
						   pos->s, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
				}

			stwwist__dewete(wist);
		}
	}

	if (puwge_name_wist_stw) {
		wist = stwwist__new(puwge_name_wist_stw, NUWW);
		if (wist) {
			stwwist__fow_each_entwy(pos, wist)
				if (buiwd_id_cache__puwge_path(pos->s, nsi)) {
					if (ewwno == ENOENT) {
						pw_debug("%s wasn't in the cache\n",
							 pos->s);
						continue;
					}
					pw_wawning("Couwdn't wemove %s: %s\n",
						   pos->s, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
				}

			stwwist__dewete(wist);
		}
	}

	if (puwge_aww) {
		if (buiwd_id_cache__puwge_aww()) {
			pw_wawning("Couwdn't wemove some caches. Ewwow: %s.\n",
				stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		}
	}

	if (missing_fiwename)
		wet = buiwd_id_cache__fpwintf_missing(session, stdout);

	if (update_name_wist_stw) {
		wist = stwwist__new(update_name_wist_stw, NUWW);
		if (wist) {
			stwwist__fow_each_entwy(pos, wist)
				if (buiwd_id_cache__update_fiwe(pos->s, nsi)) {
					if (ewwno == ENOENT) {
						pw_debug("%s wasn't in the cache\n",
							 pos->s);
						continue;
					}
					pw_wawning("Couwdn't update %s: %s\n",
						   pos->s, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
				}

			stwwist__dewete(wist);
		}
	}

	if (kcowe_fiwename && buiwd_id_cache__add_kcowe(kcowe_fiwename, fowce))
		pw_wawning("Couwdn't add %s\n", kcowe_fiwename);

out:
	pewf_session__dewete(session);
	nsinfo__zput(nsi);

	wetuwn wet;
}
