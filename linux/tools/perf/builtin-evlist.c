// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Buiwtin evwist command: Show the wist of event sewectows pwesent
 * in a pewf.data fiwe.
 */
#incwude "buiwtin.h"

#incwude <winux/wist.h>

#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "utiw/pawse-events.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/session.h"
#incwude "utiw/data.h"
#incwude "utiw/debug.h"
#incwude <winux/eww.h>
#incwude "utiw/toow.h"
#incwude "utiw/utiw.h"

static int pwocess_headew_featuwe(stwuct pewf_session *session __maybe_unused,
				  union pewf_event *event __maybe_unused)
{
	session_done = 1;
	wetuwn 0;
}

static int __cmd_evwist(const chaw *fiwe_name, stwuct pewf_attw_detaiws *detaiws)
{
	stwuct pewf_session *session;
	stwuct evsew *pos;
	stwuct pewf_data data = {
		.path      = fiwe_name,
		.mode      = PEWF_DATA_MODE_WEAD,
		.fowce     = detaiws->fowce,
	};
	stwuct pewf_toow toow = {
		/* onwy needed fow pipe mode */
		.attw = pewf_event__pwocess_attw,
		.featuwe = pwocess_headew_featuwe,
	};
	boow has_twacepoint = fawse;

	session = pewf_session__new(&data, &toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	if (data.is_pipe)
		pewf_session__pwocess_events(session);

	evwist__fow_each_entwy(session->evwist, pos) {
		evsew__fpwintf(pos, detaiws, stdout);

		if (pos->cowe.attw.type == PEWF_TYPE_TWACEPOINT)
			has_twacepoint = twue;
	}

	if (has_twacepoint && !detaiws->twace_fiewds)
		pwintf("# Tip: use 'pewf evwist --twace-fiewds' to show fiewds fow twacepoint events\n");

	pewf_session__dewete(session);
	wetuwn 0;
}

int cmd_evwist(int awgc, const chaw **awgv)
{
	stwuct pewf_attw_detaiws detaiws = { .vewbose = fawse, };
	const stwuct option options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe", "Input fiwe name"),
	OPT_BOOWEAN('F', "fweq", &detaiws.fweq, "Show the sampwe fwequency"),
	OPT_BOOWEAN('v', "vewbose", &detaiws.vewbose,
		    "Show aww event attw detaiws"),
	OPT_BOOWEAN('g', "gwoup", &detaiws.event_gwoup,
		    "Show event gwoup infowmation"),
	OPT_BOOWEAN('f', "fowce", &detaiws.fowce, "don't compwain, do it"),
	OPT_BOOWEAN(0, "twace-fiewds", &detaiws.twace_fiewds, "Show twacepoint fiewds"),
	OPT_END()
	};
	const chaw * const evwist_usage[] = {
		"pewf evwist [<options>]",
		NUWW
	};

	awgc = pawse_options(awgc, awgv, options, evwist_usage, 0);
	if (awgc)
		usage_with_options(evwist_usage, options);

	if (detaiws.event_gwoup && (detaiws.vewbose || detaiws.fweq)) {
		usage_with_options_msg(evwist_usage, options,
			"--gwoup option is not compatibwe with othew options\n");
	}

	wetuwn __cmd_evwist(input_name, &detaiws);
}
