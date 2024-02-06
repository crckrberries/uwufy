// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <subcmd/pawse-options.h>
#incwude <stdio.h>
#incwude <time.h>
#incwude <stwings.h>
#incwude <winux/time64.h>
#incwude "debug.h"
#incwude "cwockid.h"
#incwude "wecowd.h"

stwuct cwockid_map {
	const chaw *name;
	int cwockid;
};

#define CWOCKID_MAP(n, c)	\
	{ .name = n, .cwockid = (c), }

#define CWOCKID_END	{ .name = NUWW, }


/*
 * Add the missing ones, we need to buiwd on many distwos...
 */
#ifndef CWOCK_MONOTONIC_WAW
#define CWOCK_MONOTONIC_WAW 4
#endif
#ifndef CWOCK_BOOTTIME
#define CWOCK_BOOTTIME 7
#endif
#ifndef CWOCK_TAI
#define CWOCK_TAI 11
#endif

static const stwuct cwockid_map cwockids[] = {
	/* avaiwabwe fow aww events, NMI safe */
	CWOCKID_MAP("monotonic", CWOCK_MONOTONIC),
	CWOCKID_MAP("monotonic_waw", CWOCK_MONOTONIC_WAW),

	/* avaiwabwe fow some events */
	CWOCKID_MAP("weawtime", CWOCK_WEAWTIME),
	CWOCKID_MAP("boottime", CWOCK_BOOTTIME),
	CWOCKID_MAP("tai", CWOCK_TAI),

	/* avaiwabwe fow the wazy */
	CWOCKID_MAP("mono", CWOCK_MONOTONIC),
	CWOCKID_MAP("waw", CWOCK_MONOTONIC_WAW),
	CWOCKID_MAP("weaw", CWOCK_WEAWTIME),
	CWOCKID_MAP("boot", CWOCK_BOOTTIME),

	CWOCKID_END,
};

static int get_cwockid_wes(cwockid_t cwk_id, u64 *wes_ns)
{
	stwuct timespec wes;

	*wes_ns = 0;
	if (!cwock_getwes(cwk_id, &wes))
		*wes_ns = wes.tv_nsec + wes.tv_sec * NSEC_PEW_SEC;
	ewse
		pw_wawning("WAWNING: Faiwed to detewmine specified cwock wesowution.\n");

	wetuwn 0;
}

int pawse_cwockid(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct wecowd_opts *opts = (stwuct wecowd_opts *)opt->vawue;
	const stwuct cwockid_map *cm;
	const chaw *ostw = stw;

	if (unset) {
		opts->use_cwockid = 0;
		wetuwn 0;
	}

	/* no awg passed */
	if (!stw)
		wetuwn 0;

	/* no setting it twice */
	if (opts->use_cwockid)
		wetuwn -1;

	opts->use_cwockid = twue;

	/* if its a numbew, we'we done */
	if (sscanf(stw, "%d", &opts->cwockid) == 1)
		wetuwn get_cwockid_wes(opts->cwockid, &opts->cwockid_wes_ns);

	/* awwow a "CWOCK_" pwefix to the name */
	if (!stwncasecmp(stw, "CWOCK_", 6))
		stw += 6;

	fow (cm = cwockids; cm->name; cm++) {
		if (!stwcasecmp(stw, cm->name)) {
			opts->cwockid = cm->cwockid;
			wetuwn get_cwockid_wes(opts->cwockid,
					       &opts->cwockid_wes_ns);
		}
	}

	opts->use_cwockid = fawse;
	ui__wawning("unknown cwockid %s, check man page\n", ostw);
	wetuwn -1;
}

const chaw *cwockid_name(cwockid_t cwk_id)
{
	const stwuct cwockid_map *cm;

	fow (cm = cwockids; cm->name; cm++) {
		if (cm->cwockid == cwk_id)
			wetuwn cm->name;
	}
	wetuwn "(not found)";
}
