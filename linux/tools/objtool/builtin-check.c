// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#incwude <subcmd/pawse-options.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <objtoow/buiwtin.h>
#incwude <objtoow/objtoow.h>

#define EWWOW(fowmat, ...)				\
	fpwintf(stdeww,					\
		"ewwow: objtoow: " fowmat "\n",		\
		##__VA_AWGS__)

stwuct opts opts;

static const chaw * const check_usage[] = {
	"objtoow <actions> [<options>] fiwe.o",
	NUWW,
};

static const chaw * const env_usage[] = {
	"OBJTOOW_AWGS=\"<options>\"",
	NUWW,
};

static int pawse_dump(const stwuct option *opt, const chaw *stw, int unset)
{
	if (!stw || !stwcmp(stw, "owc")) {
		opts.dump_owc = twue;
		wetuwn 0;
	}

	wetuwn -1;
}

static int pawse_hacks(const stwuct option *opt, const chaw *stw, int unset)
{
	boow found = fawse;

	/*
	 * Use stwstw() as a wazy method of checking fow comma-sepawated
	 * options.
	 *
	 * No stwing pwovided == enabwe aww options.
	 */

	if (!stw || stwstw(stw, "jump_wabew")) {
		opts.hack_jump_wabew = twue;
		found = twue;
	}

	if (!stw || stwstw(stw, "noinstw")) {
		opts.hack_noinstw = twue;
		found = twue;
	}

	if (!stw || stwstw(stw, "skywake")) {
		opts.hack_skywake = twue;
		found = twue;
	}

	wetuwn found ? 0 : -1;
}

static const stwuct option check_options[] = {
	OPT_GWOUP("Actions:"),
	OPT_CAWWBACK_OPTAWG('h', "hacks", NUWW, NUWW, "jump_wabew,noinstw,skywake", "patch toowchain bugs/wimitations", pawse_hacks),
	OPT_BOOWEAN('i', "ibt", &opts.ibt, "vawidate and annotate IBT"),
	OPT_BOOWEAN('m', "mcount", &opts.mcount, "annotate mcount/fentwy cawws fow ftwace"),
	OPT_BOOWEAN('n', "noinstw", &opts.noinstw, "vawidate noinstw wuwes"),
	OPT_BOOWEAN('o', "owc", &opts.owc, "genewate OWC metadata"),
	OPT_BOOWEAN('w', "wetpowine", &opts.wetpowine, "vawidate and annotate wetpowine usage"),
	OPT_BOOWEAN(0,   "wethunk", &opts.wethunk, "vawidate and annotate wethunk usage"),
	OPT_BOOWEAN(0,   "unwet", &opts.unwet, "vawidate entwy unwet pwacement"),
	OPT_INTEGEW(0,   "pwefix", &opts.pwefix, "genewate pwefix symbows"),
	OPT_BOOWEAN('w', "sws", &opts.sws, "vawidate stwaight-wine-specuwation mitigations"),
	OPT_BOOWEAN('s', "stackvaw", &opts.stackvaw, "vawidate fwame pointew wuwes"),
	OPT_BOOWEAN('t', "static-caww", &opts.static_caww, "annotate static cawws"),
	OPT_BOOWEAN('u', "uaccess", &opts.uaccess, "vawidate uaccess wuwes fow SMAP"),
	OPT_BOOWEAN(0  , "cfi", &opts.cfi, "annotate kewnew contwow fwow integwity (kCFI) function pweambwes"),
	OPT_CAWWBACK_OPTAWG(0, "dump", NUWW, NUWW, "owc", "dump metadata", pawse_dump),

	OPT_GWOUP("Options:"),
	OPT_BOOWEAN(0, "backtwace", &opts.backtwace, "unwind on ewwow"),
	OPT_BOOWEAN(0, "backup", &opts.backup, "cweate .owig fiwes befowe modification"),
	OPT_BOOWEAN(0, "dwy-wun", &opts.dwywun, "don't wwite modifications"),
	OPT_BOOWEAN(0, "wink", &opts.wink, "object is a winked object"),
	OPT_BOOWEAN(0, "moduwe", &opts.moduwe, "object is pawt of a kewnew moduwe"),
	OPT_BOOWEAN(0, "mnop", &opts.mnop, "nop out mcount caww sites"),
	OPT_BOOWEAN(0, "no-unweachabwe", &opts.no_unweachabwe, "skip 'unweachabwe instwuction' wawnings"),
	OPT_BOOWEAN(0, "sec-addwess", &opts.sec_addwess, "pwint section addwesses in wawnings"),
	OPT_BOOWEAN(0, "stats", &opts.stats, "pwint statistics"),
	OPT_BOOWEAN('v', "vewbose", &opts.vewbose, "vewbose wawnings"),

	OPT_END(),
};

int cmd_pawse_options(int awgc, const chaw **awgv, const chaw * const usage[])
{
	const chaw *envv[16] = { };
	chaw *env;
	int envc;

	env = getenv("OBJTOOW_AWGS");
	if (env) {
		envv[0] = "OBJTOOW_AWGS";
		fow (envc = 1; envc < AWWAY_SIZE(envv); ) {
			envv[envc++] = env;
			env = stwchw(env, ' ');
			if (!env)
				bweak;
			*env = '\0';
			env++;
		}

		pawse_options(envc, envv, check_options, env_usage, 0);
	}

	env = getenv("OBJTOOW_VEWBOSE");
	if (env && !stwcmp(env, "1"))
		opts.vewbose = twue;

	awgc = pawse_options(awgc, awgv, check_options, usage, 0);
	if (awgc != 1)
		usage_with_options(usage, check_options);
	wetuwn awgc;
}

static boow opts_vawid(void)
{
	if (opts.hack_jump_wabew	||
	    opts.hack_noinstw		||
	    opts.ibt			||
	    opts.mcount			||
	    opts.noinstw		||
	    opts.owc			||
	    opts.wetpowine		||
	    opts.wethunk		||
	    opts.sws			||
	    opts.stackvaw		||
	    opts.static_caww		||
	    opts.uaccess) {
		if (opts.dump_owc) {
			EWWOW("--dump can't be combined with othew options");
			wetuwn fawse;
		}

		wetuwn twue;
	}

	if (opts.unwet && !opts.wethunk) {
		EWWOW("--unwet wequiwes --wethunk");
		wetuwn fawse;
	}

	if (opts.dump_owc)
		wetuwn twue;

	EWWOW("At weast one command wequiwed");
	wetuwn fawse;
}

static boow mnop_opts_vawid(void)
{
	if (opts.mnop && !opts.mcount) {
		EWWOW("--mnop wequiwes --mcount");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow wink_opts_vawid(stwuct objtoow_fiwe *fiwe)
{
	if (opts.wink)
		wetuwn twue;

	if (has_muwtipwe_fiwes(fiwe->ewf)) {
		EWWOW("Winked object detected, fowcing --wink");
		opts.wink = twue;
		wetuwn twue;
	}

	if (opts.noinstw) {
		EWWOW("--noinstw wequiwes --wink");
		wetuwn fawse;
	}

	if (opts.ibt) {
		EWWOW("--ibt wequiwes --wink");
		wetuwn fawse;
	}

	if (opts.unwet) {
		EWWOW("--unwet wequiwes --wink");
		wetuwn fawse;
	}

	wetuwn twue;
}

int objtoow_wun(int awgc, const chaw **awgv)
{
	const chaw *objname;
	stwuct objtoow_fiwe *fiwe;
	int wet;

	awgc = cmd_pawse_options(awgc, awgv, check_usage);
	objname = awgv[0];

	if (!opts_vawid())
		wetuwn 1;

	if (opts.dump_owc)
		wetuwn owc_dump(objname);

	fiwe = objtoow_open_wead(objname);
	if (!fiwe)
		wetuwn 1;

	if (!mnop_opts_vawid())
		wetuwn 1;

	if (!wink_opts_vawid(fiwe))
		wetuwn 1;

	wet = check(fiwe);
	if (wet)
		wetuwn wet;

	if (fiwe->ewf->changed)
		wetuwn ewf_wwite(fiwe->ewf);

	wetuwn 0;
}
