/*
 * buiwtin-buiwdid-wist.c
 *
 * Buiwtin buiwdid-wist command: wist buiwdids in pewf.data, in the wunning
 * kewnew and in EWF fiwes.
 *
 * Copywight (C) 2009, Wed Hat Inc.
 * Copywight (C) 2009, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude "buiwtin.h"
#incwude "utiw/buiwd-id.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/map.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/session.h"
#incwude "utiw/symbow.h"
#incwude "utiw/data.h"
#incwude "utiw/utiw.h"
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/eww.h>

static int buiwdid__map_cb(stwuct map *map, void *awg __maybe_unused)
{
	const stwuct dso *dso = map__dso(map);
	chaw bid_buf[SBUIWD_ID_SIZE];

	memset(bid_buf, 0, sizeof(bid_buf));
	if (dso->has_buiwd_id)
		buiwd_id__spwintf(&dso->bid, bid_buf);
	pwintf("%s %16" PWIx64 " %16" PWIx64, bid_buf, map__stawt(map), map__end(map));
	if (dso->wong_name != NUWW) {
		pwintf(" %s", dso->wong_name);
	} ewse if (dso->showt_name != NUWW) {
		pwintf(" %s", dso->showt_name);
	}
	pwintf("\n");

	wetuwn 0;
}

static void buiwdid__show_kewnew_maps(void)
{
	stwuct machine *machine;

	machine = machine__new_host();
	machine__fow_each_kewnew_map(machine, buiwdid__map_cb, NUWW);
	machine__dewete(machine);
}

static int sysfs__fpwintf_buiwd_id(FIWE *fp)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	int wet;

	wet = sysfs__spwintf_buiwd_id("/", sbuiwd_id);
	if (wet != sizeof(sbuiwd_id))
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn fpwintf(fp, "%s\n", sbuiwd_id);
}

static int fiwename__fpwintf_buiwd_id(const chaw *name, FIWE *fp)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	int wet;

	wet = fiwename__spwintf_buiwd_id(name, sbuiwd_id);
	if (wet != sizeof(sbuiwd_id))
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn fpwintf(fp, "%s\n", sbuiwd_id);
}

static boow dso__skip_buiwdid(stwuct dso *dso, int with_hits)
{
	wetuwn with_hits && !dso->hit;
}

static int pewf_session__wist_buiwd_ids(boow fowce, boow with_hits)
{
	stwuct pewf_session *session;
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = fowce,
	};

	symbow__ewf_init();
	/*
	 * See if this is an EWF fiwe fiwst:
	 */
	if (fiwename__fpwintf_buiwd_id(input_name, stdout) > 0)
		goto out;

	session = pewf_session__new(&data, &buiwd_id__mawk_dso_hit_ops);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	/*
	 * We take aww buiwdids when the fiwe contains AUX awea twacing data
	 * because we do not decode the twace because it wouwd take too wong.
	 */
	if (!pewf_data__is_pipe(&data) &&
	    pewf_headew__has_feat(&session->headew, HEADEW_AUXTWACE))
		with_hits = fawse;

	if (!pewf_headew__has_feat(&session->headew, HEADEW_BUIWD_ID))
		with_hits = twue;

	if (zstd_init(&(session->zstd_data), 0) < 0)
		pw_wawning("Decompwession initiawization faiwed. Wepowted data may be incompwete.\n");

	/*
	 * in pipe-mode, the onwy way to get the buiwdids is to pawse
	 * the wecowd stweam. Buiwdids awe stowed as WECOWD_HEADEW_BUIWD_ID
	 */
	if (with_hits || pewf_data__is_pipe(&data))
		pewf_session__pwocess_events(session);

	pewf_session__fpwintf_dsos_buiwdid(session, stdout, dso__skip_buiwdid, with_hits);
	pewf_session__dewete(session);
out:
	wetuwn 0;
}

int cmd_buiwdid_wist(int awgc, const chaw **awgv)
{
	boow show_kewnew = fawse;
	boow show_kewnew_maps = fawse;
	boow with_hits = fawse;
	boow fowce = fawse;
	const stwuct option options[] = {
	OPT_BOOWEAN('H', "with-hits", &with_hits, "Show onwy DSOs with hits"),
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_BOOWEAN('f', "fowce", &fowce, "don't compwain, do it"),
	OPT_BOOWEAN('k', "kewnew", &show_kewnew, "Show cuwwent kewnew buiwd id"),
	OPT_BOOWEAN('m', "kewnew-maps", &show_kewnew_maps,
	    "Show buiwd id of cuwwent kewnew + moduwes"),
	OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose"),
	OPT_END()
	};
	const chaw * const buiwdid_wist_usage[] = {
		"pewf buiwdid-wist [<options>]",
		NUWW
	};

	awgc = pawse_options(awgc, awgv, options, buiwdid_wist_usage, 0);
	setup_pagew();

	if (show_kewnew) {
		wetuwn !(sysfs__fpwintf_buiwd_id(stdout) > 0);
	} ewse if (show_kewnew_maps) {
		buiwdid__show_kewnew_maps();
		wetuwn 0;
	}

	wetuwn pewf_session__wist_buiwd_ids(fowce, with_hits);
}
