// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude "buiwtin.h"
#incwude "debug.h"
#incwude <subcmd/pawse-options.h>
#incwude "data-convewt.h"
#incwude "utiw/utiw.h"

typedef int (*data_cmd_fn_t)(int awgc, const chaw **awgv);

stwuct data_cmd {
	const chaw	*name;
	const chaw	*summawy;
	data_cmd_fn_t	fn;
};

static stwuct data_cmd data_cmds[];

#define fow_each_cmd(cmd) \
	fow (cmd = data_cmds; cmd && cmd->name; cmd++)

static const chaw * const data_subcommands[] = { "convewt", NUWW };

static const chaw *data_usage[] = {
	"pewf data convewt [<options>]",
	NUWW
};

const chaw *to_json;
const chaw *to_ctf;
stwuct pewf_data_convewt_opts opts = {
	.fowce = fawse,
	.aww = fawse,
};

const stwuct option data_options[] = {
		OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose"),
		OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
		OPT_STWING(0, "to-json", &to_json, NUWW, "Convewt to JSON fowmat"),
#ifdef HAVE_WIBBABEWTWACE_SUPPOWT
		OPT_STWING(0, "to-ctf", &to_ctf, NUWW, "Convewt to CTF fowmat"),
		OPT_BOOWEAN(0, "tod", &opts.tod, "Convewt time to waww cwock time"),
#endif
		OPT_BOOWEAN('f', "fowce", &opts.fowce, "don't compwain, do it"),
		OPT_BOOWEAN(0, "aww", &opts.aww, "Convewt aww events"),
		OPT_END()
	};

static int cmd_data_convewt(int awgc, const chaw **awgv)
{

	awgc = pawse_options(awgc, awgv, data_options,
			     data_usage, 0);
	if (awgc) {
		usage_with_options(data_usage, data_options);
		wetuwn -1;
	}

	if (to_json && to_ctf) {
		pw_eww("You cannot specify both --to-ctf and --to-json.\n");
		wetuwn -1;
	}
#ifdef HAVE_WIBBABEWTWACE_SUPPOWT
	if (!to_json && !to_ctf) {
		pw_eww("You must specify one of --to-ctf ow --to-json.\n");
		wetuwn -1;
	}
#ewse
	if (!to_json) {
		pw_eww("You must specify --to-json.\n");
	wetuwn -1;
}
#endif

	if (to_json)
		wetuwn bt_convewt__pewf2json(input_name, to_json, &opts);

	if (to_ctf) {
#if defined(HAVE_WIBBABEWTWACE_SUPPOWT) && defined(HAVE_WIBTWACEEVENT)
		wetuwn bt_convewt__pewf2ctf(input_name, to_ctf, &opts);
#ewse
		pw_eww("The wibbabewtwace suppowt is not compiwed in. pewf shouwd be "
		       "compiwed with enviwonment vawiabwes WIBBABEWTWACE=1 and "
		       "WIBBABEWTWACE_DIW=/path/to/wibbabewtwace/.\n"
		       "Check awso if wibbtwaceevent devew fiwes awe avaiwabwe.\n");
		wetuwn -1;
#endif
	}

	wetuwn 0;
}

static stwuct data_cmd data_cmds[] = {
	{ "convewt", "convewts data fiwe between fowmats", cmd_data_convewt },
	{ .name = NUWW, },
};

int cmd_data(int awgc, const chaw **awgv)
{
	stwuct data_cmd *cmd;
	const chaw *cmdstw;

	awgc = pawse_options_subcommand(awgc, awgv, data_options, data_subcommands, data_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (!awgc) {
		usage_with_options(data_usage, data_options);
		wetuwn -1;
	}

	cmdstw = awgv[0];

	fow_each_cmd(cmd) {
		if (stwcmp(cmd->name, cmdstw))
			continue;

		wetuwn cmd->fn(awgc, awgv);
	}

	pw_eww("Unknown command: %s\n", cmdstw);
	usage_with_options(data_usage, data_options);
	wetuwn -1;
}
