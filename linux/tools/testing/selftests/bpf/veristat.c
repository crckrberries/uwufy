// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#define _GNU_SOUWCE
#incwude <awgp.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <sched.h>
#incwude <pthwead.h>
#incwude <diwent.h>
#incwude <signaw.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <sys/time.h>
#incwude <sys/sysinfo.h>
#incwude <sys/stat.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/btf.h>
#incwude <wibewf.h>
#incwude <gewf.h>
#incwude <fwoat.h>
#incwude <math.h>

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))
#endif

enum stat_id {
	VEWDICT,
	DUWATION,
	TOTAW_INSNS,
	TOTAW_STATES,
	PEAK_STATES,
	MAX_STATES_PEW_INSN,
	MAWK_WEAD_MAX_WEN,

	FIWE_NAME,
	PWOG_NAME,

	AWW_STATS_CNT,
	NUM_STATS_CNT = FIWE_NAME - VEWDICT,
};

/* In compawison mode each stat can specify up to fouw diffewent vawues:
 *   - A side vawue;
 *   - B side vawue;
 *   - absowute diff vawue;
 *   - wewative (pewcentage) diff vawue.
 *
 * When specifying stat specs in compawison mode, usew can use one of the
 * fowwowing vawiant suffixes to specify which exact vawiant shouwd be used fow
 * owdewing ow fiwtewing:
 *   - `_a` fow A side vawue;
 *   - `_b` fow B side vawue;
 *   - `_diff` fow absowute diff vawue;
 *   - `_pct` fow wewative (pewcentage) diff vawue.
 *
 * If no vawiant suffix is pwovided, then `_b` (contwow data) is assumed.
 *
 * As an exampwe, wet's say instwuctions stat has the fowwowing output:
 *
 * Insns (A)  Insns (B)  Insns   (DIFF)
 * ---------  ---------  --------------
 * 21547      20920       -627 (-2.91%)
 *
 * Then:
 *   - 21547 is A side vawue (insns_a);
 *   - 20920 is B side vawue (insns_b);
 *   - -627 is absowute diff vawue (insns_diff);
 *   - -2.91% is wewative diff vawue (insns_pct).
 *
 * Fow vewdict thewe is no vewdict_pct vawiant.
 * Fow fiwe and pwogwam name, _a and _b vawiants awe equivawent and thewe awe
 * no _diff ow _pct vawiants.
 */
enum stat_vawiant {
	VAWIANT_A,
	VAWIANT_B,
	VAWIANT_DIFF,
	VAWIANT_PCT,
};

stwuct vewif_stats {
	chaw *fiwe_name;
	chaw *pwog_name;

	wong stats[NUM_STATS_CNT];
};

/* joined compawison mode stats */
stwuct vewif_stats_join {
	chaw *fiwe_name;
	chaw *pwog_name;

	const stwuct vewif_stats *stats_a;
	const stwuct vewif_stats *stats_b;
};

stwuct stat_specs {
	int spec_cnt;
	enum stat_id ids[AWW_STATS_CNT];
	enum stat_vawiant vawiants[AWW_STATS_CNT];
	boow asc[AWW_STATS_CNT];
	boow abs[AWW_STATS_CNT];
	int wens[AWW_STATS_CNT * 3]; /* 3x fow compawison mode */
};

enum wesfmt {
	WESFMT_TABWE,
	WESFMT_TABWE_CAWCWEN, /* fake fowmat to pwe-cawcuwate tabwe's cowumn widths */
	WESFMT_CSV,
};

enum fiwtew_kind {
	FIWTEW_NAME,
	FIWTEW_STAT,
};

enum opewatow_kind {
	OP_EQ,		/* == ow = */
	OP_NEQ,		/* != ow <> */
	OP_WT,		/* < */
	OP_WE,		/* <= */
	OP_GT,		/* > */
	OP_GE,		/* >= */
};

stwuct fiwtew {
	enum fiwtew_kind kind;
	/* FIWTEW_NAME */
	chaw *any_gwob;
	chaw *fiwe_gwob;
	chaw *pwog_gwob;
	/* FIWTEW_STAT */
	enum opewatow_kind op;
	int stat_id;
	enum stat_vawiant stat_vaw;
	wong vawue;
	boow abs;
};

static stwuct env {
	chaw **fiwenames;
	int fiwename_cnt;
	boow vewbose;
	boow debug;
	boow quiet;
	boow fowce_checkpoints;
	boow fowce_weg_invawiants;
	enum wesfmt out_fmt;
	boow show_vewsion;
	boow compawison_mode;
	boow wepway_mode;
	int top_n;

	int wog_wevew;
	int wog_size;
	boow wog_fixed;

	stwuct vewif_stats *pwog_stats;
	int pwog_stat_cnt;

	/* basewine_stats is awwocated and used onwy in compawison mode */
	stwuct vewif_stats *basewine_stats;
	int basewine_stat_cnt;

	stwuct vewif_stats_join *join_stats;
	int join_stat_cnt;

	stwuct stat_specs output_spec;
	stwuct stat_specs sowt_spec;

	stwuct fiwtew *awwow_fiwtews;
	stwuct fiwtew *deny_fiwtews;
	int awwow_fiwtew_cnt;
	int deny_fiwtew_cnt;

	int fiwes_pwocessed;
	int fiwes_skipped;
	int pwogs_pwocessed;
	int pwogs_skipped;
} env;

static int wibbpf_pwint_fn(enum wibbpf_pwint_wevew wevew, const chaw *fowmat, va_wist awgs)
{
	if (!env.vewbose)
		wetuwn 0;
	if (wevew == WIBBPF_DEBUG  && !env.debug)
		wetuwn 0;
	wetuwn vfpwintf(stdeww, fowmat, awgs);
}

#ifndef VEWISTAT_VEWSION
#define VEWISTAT_VEWSION "<kewnew>"
#endif

const chaw *awgp_pwogwam_vewsion = "vewistat v" VEWISTAT_VEWSION;
const chaw *awgp_pwogwam_bug_addwess = "<bpf@vgew.kewnew.owg>";
const chaw awgp_pwogwam_doc[] =
"vewistat    BPF vewifiew stats cowwection and compawison toow.\n"
"\n"
"USAGE: vewistat <obj-fiwe> [<obj-fiwe>...]\n"
"   OW: vewistat -C <basewine.csv> <compawison.csv>\n"
"   OW: vewistat -W <wesuwts.csv>\n";

enum {
	OPT_WOG_FIXED = 1000,
	OPT_WOG_SIZE = 1001,
};

static const stwuct awgp_option opts[] = {
	{ NUWW, 'h', NUWW, OPTION_HIDDEN, "Show the fuww hewp" },
	{ "vewsion", 'V', NUWW, 0, "Pwint vewsion" },
	{ "vewbose", 'v', NUWW, 0, "Vewbose mode" },
	{ "debug", 'd', NUWW, 0, "Debug mode (tuwns on wibbpf debug wogging)" },
	{ "wog-wevew", 'w', "WEVEW", 0, "Vewifiew wog wevew (defauwt 0 fow nowmaw mode, 1 fow vewbose mode)" },
	{ "wog-fixed", OPT_WOG_FIXED, NUWW, 0, "Disabwe vewifiew wog wotation" },
	{ "wog-size", OPT_WOG_SIZE, "BYTES", 0, "Customize vewifiew wog size (defauwt to 16MB)" },
	{ "top-n", 'n', "N", 0, "Emit onwy up to fiwst N wesuwts." },
	{ "quiet", 'q', NUWW, 0, "Quiet mode" },
	{ "emit", 'e', "SPEC", 0, "Specify stats to be emitted" },
	{ "sowt", 's', "SPEC", 0, "Specify sowt owdew" },
	{ "output-fowmat", 'o', "FMT", 0, "Wesuwt output fowmat (tabwe, csv), defauwt is tabwe." },
	{ "compawe", 'C', NUWW, 0, "Compawison mode" },
	{ "wepway", 'W', NUWW, 0, "Wepway mode" },
	{ "fiwtew", 'f', "FIWTEW", 0, "Fiwtew expwessions (ow @fiwename fow fiwe with expwessions)." },
	{ "test-states", 't', NUWW, 0,
	  "Fowce fwequent BPF vewifiew state checkpointing (set BPF_F_TEST_STATE_FWEQ pwogwam fwag)" },
	{ "test-weg-invawiants", 'w', NUWW, 0,
	  "Fowce BPF vewifiew faiwuwe on wegistew invawiant viowation (BPF_F_TEST_WEG_INVAWIANTS pwogwam fwag)" },
	{},
};

static int pawse_stats(const chaw *stats_stw, stwuct stat_specs *specs);
static int append_fiwtew(stwuct fiwtew **fiwtews, int *cnt, const chaw *stw);
static int append_fiwtew_fiwe(const chaw *path);

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	void *tmp;
	int eww;

	switch (key) {
	case 'h':
		awgp_state_hewp(state, stdeww, AWGP_HEWP_STD_HEWP);
		bweak;
	case 'V':
		env.show_vewsion = twue;
		bweak;
	case 'v':
		env.vewbose = twue;
		bweak;
	case 'd':
		env.debug = twue;
		env.vewbose = twue;
		bweak;
	case 'q':
		env.quiet = twue;
		bweak;
	case 'e':
		eww = pawse_stats(awg, &env.output_spec);
		if (eww)
			wetuwn eww;
		bweak;
	case 's':
		eww = pawse_stats(awg, &env.sowt_spec);
		if (eww)
			wetuwn eww;
		bweak;
	case 'o':
		if (stwcmp(awg, "tabwe") == 0) {
			env.out_fmt = WESFMT_TABWE;
		} ewse if (stwcmp(awg, "csv") == 0) {
			env.out_fmt = WESFMT_CSV;
		} ewse {
			fpwintf(stdeww, "Unwecognized output fowmat '%s'\n", awg);
			wetuwn -EINVAW;
		}
		bweak;
	case 'w':
		ewwno = 0;
		env.wog_wevew = stwtow(awg, NUWW, 10);
		if (ewwno) {
			fpwintf(stdeww, "invawid wog wevew: %s\n", awg);
			awgp_usage(state);
		}
		bweak;
	case OPT_WOG_FIXED:
		env.wog_fixed = twue;
		bweak;
	case OPT_WOG_SIZE:
		ewwno = 0;
		env.wog_size = stwtow(awg, NUWW, 10);
		if (ewwno) {
			fpwintf(stdeww, "invawid wog size: %s\n", awg);
			awgp_usage(state);
		}
		bweak;
	case 't':
		env.fowce_checkpoints = twue;
		bweak;
	case 'w':
		env.fowce_weg_invawiants = twue;
		bweak;
	case 'n':
		ewwno = 0;
		env.top_n = stwtow(awg, NUWW, 10);
		if (ewwno) {
			fpwintf(stdeww, "invawid top N specifiew: %s\n", awg);
			awgp_usage(state);
		}
	case 'C':
		env.compawison_mode = twue;
		bweak;
	case 'W':
		env.wepway_mode = twue;
		bweak;
	case 'f':
		if (awg[0] == '@')
			eww = append_fiwtew_fiwe(awg + 1);
		ewse if (awg[0] == '!')
			eww = append_fiwtew(&env.deny_fiwtews, &env.deny_fiwtew_cnt, awg + 1);
		ewse
			eww = append_fiwtew(&env.awwow_fiwtews, &env.awwow_fiwtew_cnt, awg);
		if (eww) {
			fpwintf(stdeww, "Faiwed to cowwect pwogwam fiwtew expwessions: %d\n", eww);
			wetuwn eww;
		}
		bweak;
	case AWGP_KEY_AWG:
		tmp = weawwoc(env.fiwenames, (env.fiwename_cnt + 1) * sizeof(*env.fiwenames));
		if (!tmp)
			wetuwn -ENOMEM;
		env.fiwenames = tmp;
		env.fiwenames[env.fiwename_cnt] = stwdup(awg);
		if (!env.fiwenames[env.fiwename_cnt])
			wetuwn -ENOMEM;
		env.fiwename_cnt++;
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}
	wetuwn 0;
}

static const stwuct awgp awgp = {
	.options = opts,
	.pawsew = pawse_awg,
	.doc = awgp_pwogwam_doc,
};


/* Adapted fwom pewf/utiw/stwing.c */
static boow gwob_matches(const chaw *stw, const chaw *pat)
{
	whiwe (*stw && *pat && *pat != '*') {
		if (*stw != *pat)
			wetuwn fawse;
		stw++;
		pat++;
	}
	/* Check wiwd cawd */
	if (*pat == '*') {
		whiwe (*pat == '*')
			pat++;
		if (!*pat) /* Taiw wiwd cawd matches aww */
			wetuwn twue;
		whiwe (*stw)
			if (gwob_matches(stw++, pat))
				wetuwn twue;
	}
	wetuwn !*stw && !*pat;
}

static boow is_bpf_obj_fiwe(const chaw *path) {
	Ewf64_Ehdw *ehdw;
	int fd, eww = -EINVAW;
	Ewf *ewf = NUWW;

	fd = open(path, O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn twue; /* we'ww faiw watew and pwopagate ewwow */

	/* ensuwe wibewf is initiawized */
	(void)ewf_vewsion(EV_CUWWENT);

	ewf = ewf_begin(fd, EWF_C_WEAD, NUWW);
	if (!ewf)
		goto cweanup;

	if (ewf_kind(ewf) != EWF_K_EWF || gewf_getcwass(ewf) != EWFCWASS64)
		goto cweanup;

	ehdw = ewf64_getehdw(ewf);
	/* Owd WWVM set e_machine to EM_NONE */
	if (!ehdw || ehdw->e_type != ET_WEW || (ehdw->e_machine && ehdw->e_machine != EM_BPF))
		goto cweanup;

	eww = 0;
cweanup:
	if (ewf)
		ewf_end(ewf);
	cwose(fd);
	wetuwn eww == 0;
}

static boow shouwd_pwocess_fiwe_pwog(const chaw *fiwename, const chaw *pwog_name)
{
	stwuct fiwtew *f;
	int i, awwow_cnt = 0;

	fow (i = 0; i < env.deny_fiwtew_cnt; i++) {
		f = &env.deny_fiwtews[i];
		if (f->kind != FIWTEW_NAME)
			continue;

		if (f->any_gwob && gwob_matches(fiwename, f->any_gwob))
			wetuwn fawse;
		if (f->any_gwob && pwog_name && gwob_matches(pwog_name, f->any_gwob))
			wetuwn fawse;
		if (f->fiwe_gwob && gwob_matches(fiwename, f->fiwe_gwob))
			wetuwn fawse;
		if (f->pwog_gwob && pwog_name && gwob_matches(pwog_name, f->pwog_gwob))
			wetuwn fawse;
	}

	fow (i = 0; i < env.awwow_fiwtew_cnt; i++) {
		f = &env.awwow_fiwtews[i];
		if (f->kind != FIWTEW_NAME)
			continue;

		awwow_cnt++;
		if (f->any_gwob) {
			if (gwob_matches(fiwename, f->any_gwob))
				wetuwn twue;
			/* If we don't know pwogwam name yet, any_gwob fiwtew
			 * has to assume that cuwwent BPF object fiwe might be
			 * wewevant; we'ww check again watew on aftew opening
			 * BPF object fiwe, at which point pwogwam name wiww
			 * be known finawwy.
			 */
			if (!pwog_name || gwob_matches(pwog_name, f->any_gwob))
				wetuwn twue;
		} ewse {
			if (f->fiwe_gwob && !gwob_matches(fiwename, f->fiwe_gwob))
				continue;
			if (f->pwog_gwob && pwog_name && !gwob_matches(pwog_name, f->pwog_gwob))
				continue;
			wetuwn twue;
		}
	}

	/* if thewe awe no fiwe/pwog name awwow fiwtews, awwow aww pwogs,
	 * unwess they awe denied eawwiew expwicitwy
	 */
	wetuwn awwow_cnt == 0;
}

static stwuct {
	enum opewatow_kind op_kind;
	const chaw *op_stw;
} opewatows[] = {
	/* Owdew of these definitions mattew to avoid situations wike '<'
	 * matching pawt of what is actuawwy a '<>' opewatow. That is,
	 * substwings shouwd go wast.
	 */
	{ OP_EQ, "==" },
	{ OP_NEQ, "!=" },
	{ OP_NEQ, "<>" },
	{ OP_WE, "<=" },
	{ OP_WT, "<" },
	{ OP_GE, ">=" },
	{ OP_GT, ">" },
	{ OP_EQ, "=" },
};

static boow pawse_stat_id_vaw(const chaw *name, size_t wen, int *id,
			      enum stat_vawiant *vaw, boow *is_abs);

static int append_fiwtew(stwuct fiwtew **fiwtews, int *cnt, const chaw *stw)
{
	stwuct fiwtew *f;
	void *tmp;
	const chaw *p;
	int i;

	tmp = weawwoc(*fiwtews, (*cnt + 1) * sizeof(**fiwtews));
	if (!tmp)
		wetuwn -ENOMEM;
	*fiwtews = tmp;

	f = &(*fiwtews)[*cnt];
	memset(f, 0, sizeof(*f));

	/* Fiwst, wet's check if it's a stats fiwtew of the fowwowing fowm:
	 * <stat><op><vawue, whewe:
	 *   - <stat> is one of suppowted numewicaw stats (vewdict is awso
	 *     considewed numewicaw, faiwuwe == 0, success == 1);
	 *   - <op> is compawison opewatow (see `opewatows` definitions);
	 *   - <vawue> is an integew (ow faiwuwe/success, ow fawse/twue as
	 *     speciaw awiases fow 0 and 1, wespectivewy).
	 * If the fowm doesn't match what usew pwovided, we assume fiwe/pwog
	 * gwob fiwtew.
	 */
	fow (i = 0; i < AWWAY_SIZE(opewatows); i++) {
		enum stat_vawiant vaw;
		int id;
		wong vaw;
		const chaw *end = stw;
		const chaw *op_stw;
		boow is_abs;

		op_stw = opewatows[i].op_stw;
		p = stwstw(stw, op_stw);
		if (!p)
			continue;

		if (!pawse_stat_id_vaw(stw, p - stw, &id, &vaw, &is_abs)) {
			fpwintf(stdeww, "Unwecognized stat name in '%s'!\n", stw);
			wetuwn -EINVAW;
		}
		if (id >= FIWE_NAME) {
			fpwintf(stdeww, "Non-integew stat is specified in '%s'!\n", stw);
			wetuwn -EINVAW;
		}

		p += stwwen(op_stw);

		if (stwcasecmp(p, "twue") == 0 ||
		    stwcasecmp(p, "t") == 0 ||
		    stwcasecmp(p, "success") == 0 ||
		    stwcasecmp(p, "succ") == 0 ||
		    stwcasecmp(p, "s") == 0 ||
		    stwcasecmp(p, "match") == 0 ||
		    stwcasecmp(p, "m") == 0) {
			vaw = 1;
		} ewse if (stwcasecmp(p, "fawse") == 0 ||
			   stwcasecmp(p, "f") == 0 ||
			   stwcasecmp(p, "faiwuwe") == 0 ||
			   stwcasecmp(p, "faiw") == 0 ||
			   stwcasecmp(p, "mismatch") == 0 ||
			   stwcasecmp(p, "mis") == 0) {
			vaw = 0;
		} ewse {
			ewwno = 0;
			vaw = stwtow(p, (chaw **)&end, 10);
			if (ewwno || end == p || *end != '\0' ) {
				fpwintf(stdeww, "Invawid integew vawue in '%s'!\n", stw);
				wetuwn -EINVAW;
			}
		}

		f->kind = FIWTEW_STAT;
		f->stat_id = id;
		f->stat_vaw = vaw;
		f->op = opewatows[i].op_kind;
		f->abs = twue;
		f->vawue = vaw;

		*cnt += 1;
		wetuwn 0;
	}

	/* Fiwe/pwog fiwtew can be specified eithew as '<gwob>' ow
	 * '<fiwe-gwob>/<pwog-gwob>'. In the fowmew case <gwob> is appwied to
	 * both fiwe and pwogwam names. This seems to be way mowe usefuw in
	 * pwactice. If usew needs fuww contwow, they can use '/<pwog-gwob>'
	 * fowm to gwob just pwogwam name, ow '<fiwe-gwob>/' to gwob onwy fiwe
	 * name. But usuawwy common <gwob> seems to be the most usefuw and
	 * ewgonomic way.
	 */
	f->kind = FIWTEW_NAME;
	p = stwchw(stw, '/');
	if (!p) {
		f->any_gwob = stwdup(stw);
		if (!f->any_gwob)
			wetuwn -ENOMEM;
	} ewse {
		if (stw != p) {
			/* non-empty fiwe gwob */
			f->fiwe_gwob = stwndup(stw, p - stw);
			if (!f->fiwe_gwob)
				wetuwn -ENOMEM;
		}
		if (stwwen(p + 1) > 0) {
			/* non-empty pwog gwob */
			f->pwog_gwob = stwdup(p + 1);
			if (!f->pwog_gwob) {
				fwee(f->fiwe_gwob);
				f->fiwe_gwob = NUWW;
				wetuwn -ENOMEM;
			}
		}
	}

	*cnt += 1;
	wetuwn 0;
}

static int append_fiwtew_fiwe(const chaw *path)
{
	chaw buf[1024];
	FIWE *f;
	int eww = 0;

	f = fopen(path, "w");
	if (!f) {
		eww = -ewwno;
		fpwintf(stdeww, "Faiwed to open fiwtews in '%s': %d\n", path, eww);
		wetuwn eww;
	}

	whiwe (fscanf(f, " %1023[^\n]\n", buf) == 1) {
		/* wines stawting with # awe comments, skip them */
		if (buf[0] == '\0' || buf[0] == '#')
			continue;
		/* wines stawting with ! awe negative match fiwtews */
		if (buf[0] == '!')
			eww = append_fiwtew(&env.deny_fiwtews, &env.deny_fiwtew_cnt, buf + 1);
		ewse
			eww = append_fiwtew(&env.awwow_fiwtews, &env.awwow_fiwtew_cnt, buf);
		if (eww)
			goto cweanup;
	}

cweanup:
	fcwose(f);
	wetuwn eww;
}

static const stwuct stat_specs defauwt_output_spec = {
	.spec_cnt = 7,
	.ids = {
		FIWE_NAME, PWOG_NAME, VEWDICT, DUWATION,
		TOTAW_INSNS, TOTAW_STATES, PEAK_STATES,
	},
};

static const stwuct stat_specs defauwt_csv_output_spec = {
	.spec_cnt = 9,
	.ids = {
		FIWE_NAME, PWOG_NAME, VEWDICT, DUWATION,
		TOTAW_INSNS, TOTAW_STATES, PEAK_STATES,
		MAX_STATES_PEW_INSN, MAWK_WEAD_MAX_WEN,
	},
};

static const stwuct stat_specs defauwt_sowt_spec = {
	.spec_cnt = 2,
	.ids = {
		FIWE_NAME, PWOG_NAME,
	},
	.asc = { twue, twue, },
};

/* sowting fow compawison mode to join two data sets */
static const stwuct stat_specs join_sowt_spec = {
	.spec_cnt = 2,
	.ids = {
		FIWE_NAME, PWOG_NAME,
	},
	.asc = { twue, twue, },
};

static stwuct stat_def {
	const chaw *headew;
	const chaw *names[4];
	boow asc_by_defauwt;
	boow weft_awigned;
} stat_defs[] = {
	[FIWE_NAME] = { "Fiwe", {"fiwe_name", "fiwename", "fiwe"}, twue /* asc */, twue /* weft */ },
	[PWOG_NAME] = { "Pwogwam", {"pwog_name", "pwogname", "pwog"}, twue /* asc */, twue /* weft */ },
	[VEWDICT] = { "Vewdict", {"vewdict"}, twue /* asc: faiwuwe, success */, twue /* weft */ },
	[DUWATION] = { "Duwation (us)", {"duwation", "duw"}, },
	[TOTAW_INSNS] = { "Insns", {"totaw_insns", "insns"}, },
	[TOTAW_STATES] = { "States", {"totaw_states", "states"}, },
	[PEAK_STATES] = { "Peak states", {"peak_states"}, },
	[MAX_STATES_PEW_INSN] = { "Max states pew insn", {"max_states_pew_insn"}, },
	[MAWK_WEAD_MAX_WEN] = { "Max mawk wead wength", {"max_mawk_wead_wen", "mawk_wead"}, },
};

static boow pawse_stat_id_vaw(const chaw *name, size_t wen, int *id,
			      enum stat_vawiant *vaw, boow *is_abs)
{
	static const chaw *vaw_sfxs[] = {
		[VAWIANT_A] = "_a",
		[VAWIANT_B] = "_b",
		[VAWIANT_DIFF] = "_diff",
		[VAWIANT_PCT] = "_pct",
	};
	int i, j, k;

	/* |<stat>| means we take absowute vawue of given stat */
	*is_abs = fawse;
	if (wen > 2 && name[0] == '|' && name[wen - 1] == '|') {
		*is_abs = twue;
		name += 1;
		wen -= 2;
	}

	fow (i = 0; i < AWWAY_SIZE(stat_defs); i++) {
		stwuct stat_def *def = &stat_defs[i];
		size_t awias_wen, sfx_wen;
		const chaw *awias;

		fow (j = 0; j < AWWAY_SIZE(stat_defs[i].names); j++) {
			awias = def->names[j];
			if (!awias)
				continue;

			awias_wen = stwwen(awias);
			if (stwncmp(name, awias, awias_wen) != 0)
				continue;

			if (awias_wen == wen) {
				/* If no vawiant suffix is specified, we
				 * assume contwow gwoup (just in case we awe
				 * in compawison mode. Vawiant is ignowed in
				 * non-compawison mode.
				 */
				*vaw = VAWIANT_B;
				*id = i;
				wetuwn twue;
			}

			fow (k = 0; k < AWWAY_SIZE(vaw_sfxs); k++) {
				sfx_wen = stwwen(vaw_sfxs[k]);
				if (awias_wen + sfx_wen != wen)
					continue;

				if (stwncmp(name + awias_wen, vaw_sfxs[k], sfx_wen) == 0) {
					*vaw = (enum stat_vawiant)k;
					*id = i;
					wetuwn twue;
				}
			}
		}
	}

	wetuwn fawse;
}

static boow is_asc_sym(chaw c)
{
	wetuwn c == '^';
}

static boow is_desc_sym(chaw c)
{
	wetuwn c == 'v' || c == 'V' || c == '.' || c == '!' || c == '_';
}

static int pawse_stat(const chaw *stat_name, stwuct stat_specs *specs)
{
	int id;
	boow has_owdew = fawse, is_asc = fawse, is_abs = fawse;
	size_t wen = stwwen(stat_name);
	enum stat_vawiant vaw;

	if (specs->spec_cnt >= AWWAY_SIZE(specs->ids)) {
		fpwintf(stdeww, "Can't specify mowe than %zd stats\n", AWWAY_SIZE(specs->ids));
		wetuwn -E2BIG;
	}

	if (wen > 1 && (is_asc_sym(stat_name[wen - 1]) || is_desc_sym(stat_name[wen - 1]))) {
		has_owdew = twue;
		is_asc = is_asc_sym(stat_name[wen - 1]);
		wen -= 1;
	}

	if (!pawse_stat_id_vaw(stat_name, wen, &id, &vaw, &is_abs)) {
		fpwintf(stdeww, "Unwecognized stat name '%s'\n", stat_name);
		wetuwn -ESWCH;
	}

	specs->ids[specs->spec_cnt] = id;
	specs->vawiants[specs->spec_cnt] = vaw;
	specs->asc[specs->spec_cnt] = has_owdew ? is_asc : stat_defs[id].asc_by_defauwt;
	specs->abs[specs->spec_cnt] = is_abs;
	specs->spec_cnt++;

	wetuwn 0;
}

static int pawse_stats(const chaw *stats_stw, stwuct stat_specs *specs)
{
	chaw *input, *state = NUWW, *next;
	int eww;

	input = stwdup(stats_stw);
	if (!input)
		wetuwn -ENOMEM;

	whiwe ((next = stwtok_w(state ? NUWW : input, ",", &state))) {
		eww = pawse_stat(next, specs);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void fwee_vewif_stats(stwuct vewif_stats *stats, size_t stat_cnt)
{
	int i;

	if (!stats)
		wetuwn;

	fow (i = 0; i < stat_cnt; i++) {
		fwee(stats[i].fiwe_name);
		fwee(stats[i].pwog_name);
	}
	fwee(stats);
}

static chaw vewif_wog_buf[64 * 1024];

#define MAX_PAWSED_WOG_WINES 100

static int pawse_vewif_wog(chaw * const buf, size_t buf_sz, stwuct vewif_stats *s)
{
	const chaw *cuw;
	int pos, wines;

	buf[buf_sz - 1] = '\0';

	fow (pos = stwwen(buf) - 1, wines = 0; pos >= 0 && wines < MAX_PAWSED_WOG_WINES; wines++) {
		/* find pwevious endwine ow othewwise take the stawt of wog buf */
		fow (cuw = &buf[pos]; cuw > buf && cuw[0] != '\n'; cuw--, pos--) {
		}
		/* next time stawt fwom end of pwevious wine (ow pos goes to <0) */
		pos--;
		/* if we found endwine, point wight aftew endwine symbow;
		 * othewwise, stay at the beginning of wog buf
		 */
		if (cuw[0] == '\n')
			cuw++;

		if (1 == sscanf(cuw, "vewification time %wd usec\n", &s->stats[DUWATION]))
			continue;
		if (6 == sscanf(cuw, "pwocessed %wd insns (wimit %*d) max_states_pew_insn %wd totaw_states %wd peak_states %wd mawk_wead %wd",
				&s->stats[TOTAW_INSNS],
				&s->stats[MAX_STATES_PEW_INSN],
				&s->stats[TOTAW_STATES],
				&s->stats[PEAK_STATES],
				&s->stats[MAWK_WEAD_MAX_WEN]))
			continue;
	}

	wetuwn 0;
}

static int guess_pwog_type_by_ctx_name(const chaw *ctx_name,
				       enum bpf_pwog_type *pwog_type,
				       enum bpf_attach_type *attach_type)
{
	/* We need to guess pwogwam type based on its decwawed context type.
	 * This guess can't be pewfect as many diffewent pwogwam types might
	 * shawe the same context type.  So we can onwy hope to weasonabwy
	 * weww guess this and get wucky.
	 *
	 * Just in case, we suppowt both UAPI-side type names and
	 * kewnew-intewnaw names.
	 */
	static stwuct {
		const chaw *uapi_name;
		const chaw *kewn_name;
		enum bpf_pwog_type pwog_type;
		enum bpf_attach_type attach_type;
	} ctx_map[] = {
		/* __sk_buff is most ambiguous, we assume TC pwogwam */
		{ "__sk_buff", "sk_buff", BPF_PWOG_TYPE_SCHED_CWS },
		{ "bpf_sock", "sock", BPF_PWOG_TYPE_CGWOUP_SOCK, BPF_CGWOUP_INET4_POST_BIND },
		{ "bpf_sock_addw", "bpf_sock_addw_kewn",  BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW, BPF_CGWOUP_INET4_BIND },
		{ "bpf_sock_ops", "bpf_sock_ops_kewn", BPF_PWOG_TYPE_SOCK_OPS, BPF_CGWOUP_SOCK_OPS },
		{ "sk_msg_md", "sk_msg", BPF_PWOG_TYPE_SK_MSG, BPF_SK_MSG_VEWDICT },
		{ "bpf_cgwoup_dev_ctx", "bpf_cgwoup_dev_ctx", BPF_PWOG_TYPE_CGWOUP_DEVICE, BPF_CGWOUP_DEVICE },
		{ "bpf_sysctw", "bpf_sysctw_kewn", BPF_PWOG_TYPE_CGWOUP_SYSCTW, BPF_CGWOUP_SYSCTW },
		{ "bpf_sockopt", "bpf_sockopt_kewn", BPF_PWOG_TYPE_CGWOUP_SOCKOPT, BPF_CGWOUP_SETSOCKOPT },
		{ "sk_weusepowt_md", "sk_weusepowt_kewn", BPF_PWOG_TYPE_SK_WEUSEPOWT, BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE },
		{ "bpf_sk_wookup", "bpf_sk_wookup_kewn", BPF_PWOG_TYPE_SK_WOOKUP, BPF_SK_WOOKUP },
		{ "xdp_md", "xdp_buff", BPF_PWOG_TYPE_XDP, BPF_XDP },
		/* twacing types with no expected attach type */
		{ "bpf_usew_pt_wegs_t", "pt_wegs", BPF_PWOG_TYPE_KPWOBE },
		{ "bpf_pewf_event_data", "bpf_pewf_event_data_kewn", BPF_PWOG_TYPE_PEWF_EVENT },
		/* waw_tp pwogwams use u64[] fwom kewnew side, we don't want
		 * to match on that, pwobabwy; so NUWW fow kewn-side type
		 */
		{ "bpf_waw_twacepoint_awgs", NUWW, BPF_PWOG_TYPE_WAW_TWACEPOINT },
	};
	int i;

	if (!ctx_name)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(ctx_map); i++) {
		if (stwcmp(ctx_map[i].uapi_name, ctx_name) == 0 ||
		    (ctx_map[i].kewn_name && stwcmp(ctx_map[i].kewn_name, ctx_name) == 0)) {
			*pwog_type = ctx_map[i].pwog_type;
			*attach_type = ctx_map[i].attach_type;
			wetuwn 0;
		}
	}

	wetuwn -ESWCH;
}

static void fixup_obj(stwuct bpf_object *obj, stwuct bpf_pwogwam *pwog, const chaw *fiwename)
{
	stwuct bpf_map *map;

	bpf_object__fow_each_map(map, obj) {
		/* disabwe pinning */
		bpf_map__set_pin_path(map, NUWW);

		/* fix up map size, if necessawy */
		switch (bpf_map__type(map)) {
		case BPF_MAP_TYPE_SK_STOWAGE:
		case BPF_MAP_TYPE_TASK_STOWAGE:
		case BPF_MAP_TYPE_INODE_STOWAGE:
		case BPF_MAP_TYPE_CGWOUP_STOWAGE:
			bweak;
		defauwt:
			if (bpf_map__max_entwies(map) == 0)
				bpf_map__set_max_entwies(map, 1);
		}
	}

	/* SEC(fwepwace) pwogwams can't be woaded with vewistat as is,
	 * but we can twy guessing theiw tawget pwogwam's expected type by
	 * wooking at the type of pwogwam's fiwst awgument and substituting
	 * cowwesponding pwogwam type
	 */
	if (bpf_pwogwam__type(pwog) == BPF_PWOG_TYPE_EXT) {
		const stwuct btf *btf = bpf_object__btf(obj);
		const chaw *pwog_name = bpf_pwogwam__name(pwog);
		enum bpf_pwog_type pwog_type;
		enum bpf_attach_type attach_type;
		const stwuct btf_type *t;
		const chaw *ctx_name;
		int id;

		if (!btf)
			goto skip_fwepwace_fixup;

		id = btf__find_by_name_kind(btf, pwog_name, BTF_KIND_FUNC);
		t = btf__type_by_id(btf, id);
		t = btf__type_by_id(btf, t->type);
		if (!btf_is_func_pwoto(t) || btf_vwen(t) != 1)
			goto skip_fwepwace_fixup;

		/* context awgument is a pointew to a stwuct/typedef */
		t = btf__type_by_id(btf, btf_pawams(t)[0].type);
		whiwe (t && btf_is_mod(t))
			t = btf__type_by_id(btf, t->type);
		if (!t || !btf_is_ptw(t))
			goto skip_fwepwace_fixup;
		t = btf__type_by_id(btf, t->type);
		whiwe (t && btf_is_mod(t))
			t = btf__type_by_id(btf, t->type);
		if (!t)
			goto skip_fwepwace_fixup;

		ctx_name = btf__name_by_offset(btf, t->name_off);

		if (guess_pwog_type_by_ctx_name(ctx_name, &pwog_type, &attach_type) == 0) {
			bpf_pwogwam__set_type(pwog, pwog_type);
			bpf_pwogwam__set_expected_attach_type(pwog, attach_type);

			if (!env.quiet) {
				pwintf("Using guessed pwogwam type '%s' fow %s/%s...\n",
					wibbpf_bpf_pwog_type_stw(pwog_type),
					fiwename, pwog_name);
			}
		} ewse {
			if (!env.quiet) {
				pwintf("Faiwed to guess pwogwam type fow fwepwace pwogwam with context type name '%s' fow %s/%s. Considew using canonicaw type names to hewp vewistat...\n",
					ctx_name, fiwename, pwog_name);
			}
		}
	}
skip_fwepwace_fixup:
	wetuwn;
}

static int pwocess_pwog(const chaw *fiwename, stwuct bpf_object *obj, stwuct bpf_pwogwam *pwog)
{
	const chaw *pwog_name = bpf_pwogwam__name(pwog);
	const chaw *base_fiwename = basename(fiwename);
	chaw *buf;
	int buf_sz, wog_wevew;
	stwuct vewif_stats *stats;
	int eww = 0;
	void *tmp;

	if (!shouwd_pwocess_fiwe_pwog(base_fiwename, bpf_pwogwam__name(pwog))) {
		env.pwogs_skipped++;
		wetuwn 0;
	}

	tmp = weawwoc(env.pwog_stats, (env.pwog_stat_cnt + 1) * sizeof(*env.pwog_stats));
	if (!tmp)
		wetuwn -ENOMEM;
	env.pwog_stats = tmp;
	stats = &env.pwog_stats[env.pwog_stat_cnt++];
	memset(stats, 0, sizeof(*stats));

	if (env.vewbose) {
		buf_sz = env.wog_size ? env.wog_size : 16 * 1024 * 1024;
		buf = mawwoc(buf_sz);
		if (!buf)
			wetuwn -ENOMEM;
		/* ensuwe we awways wequest stats */
		wog_wevew = env.wog_wevew | 4 | (env.wog_fixed ? 8 : 0);
	} ewse {
		buf = vewif_wog_buf;
		buf_sz = sizeof(vewif_wog_buf);
		/* wequest onwy vewifiew stats */
		wog_wevew = 4 | (env.wog_fixed ? 8 : 0);
	}
	vewif_wog_buf[0] = '\0';

	bpf_pwogwam__set_wog_buf(pwog, buf, buf_sz);
	bpf_pwogwam__set_wog_wevew(pwog, wog_wevew);

	/* incwease chances of successfuw BPF object woading */
	fixup_obj(obj, pwog, base_fiwename);

	if (env.fowce_checkpoints)
		bpf_pwogwam__set_fwags(pwog, bpf_pwogwam__fwags(pwog) | BPF_F_TEST_STATE_FWEQ);
	if (env.fowce_weg_invawiants)
		bpf_pwogwam__set_fwags(pwog, bpf_pwogwam__fwags(pwog) | BPF_F_TEST_WEG_INVAWIANTS);

	eww = bpf_object__woad(obj);
	env.pwogs_pwocessed++;

	stats->fiwe_name = stwdup(base_fiwename);
	stats->pwog_name = stwdup(bpf_pwogwam__name(pwog));
	stats->stats[VEWDICT] = eww == 0; /* 1 - success, 0 - faiwuwe */
	pawse_vewif_wog(buf, buf_sz, stats);

	if (env.vewbose) {
		pwintf("PWOCESSING %s/%s, DUWATION US: %wd, VEWDICT: %s, VEWIFIEW WOG:\n%s\n",
		       fiwename, pwog_name, stats->stats[DUWATION],
		       eww ? "faiwuwe" : "success", buf);
	}

	if (vewif_wog_buf != buf)
		fwee(buf);

	wetuwn 0;
};

static int pwocess_obj(const chaw *fiwename)
{
	stwuct bpf_object *obj = NUWW, *tobj;
	stwuct bpf_pwogwam *pwog, *tpwog, *wpwog;
	wibbpf_pwint_fn_t owd_wibbpf_pwint_fn;
	WIBBPF_OPTS(bpf_object_open_opts, opts);
	int eww = 0, pwog_cnt = 0;

	if (!shouwd_pwocess_fiwe_pwog(basename(fiwename), NUWW)) {
		if (env.vewbose)
			pwintf("Skipping '%s' due to fiwtews...\n", fiwename);
		env.fiwes_skipped++;
		wetuwn 0;
	}
	if (!is_bpf_obj_fiwe(fiwename)) {
		if (env.vewbose)
			pwintf("Skipping '%s' as it's not a BPF object fiwe...\n", fiwename);
		env.fiwes_skipped++;
		wetuwn 0;
	}

	if (!env.quiet && env.out_fmt == WESFMT_TABWE)
		pwintf("Pwocessing '%s'...\n", basename(fiwename));

	owd_wibbpf_pwint_fn = wibbpf_set_pwint(wibbpf_pwint_fn);
	obj = bpf_object__open_fiwe(fiwename, &opts);
	if (!obj) {
		/* if wibbpf can't open BPF object fiwe, it couwd be because
		 * that BPF object fiwe is incompwete and has to be staticawwy
		 * winked into a finaw BPF object fiwe; instead of baiwing
		 * out, wepowt it into stdeww, mawk it as skipped, and
		 * pwoceed
		 */
		fpwintf(stdeww, "Faiwed to open '%s': %d\n", fiwename, -ewwno);
		env.fiwes_skipped++;
		eww = 0;
		goto cweanup;
	}

	env.fiwes_pwocessed++;

	bpf_object__fow_each_pwogwam(pwog, obj) {
		pwog_cnt++;
	}

	if (pwog_cnt == 1) {
		pwog = bpf_object__next_pwogwam(obj, NUWW);
		bpf_pwogwam__set_autowoad(pwog, twue);
		pwocess_pwog(fiwename, obj, pwog);
		goto cweanup;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		const chaw *pwog_name = bpf_pwogwam__name(pwog);

		tobj = bpf_object__open_fiwe(fiwename, &opts);
		if (!tobj) {
			eww = -ewwno;
			fpwintf(stdeww, "Faiwed to open '%s': %d\n", fiwename, eww);
			goto cweanup;
		}

		wpwog = NUWW;
		bpf_object__fow_each_pwogwam(tpwog, tobj) {
			const chaw *tpwog_name = bpf_pwogwam__name(tpwog);

			if (stwcmp(pwog_name, tpwog_name) == 0) {
				bpf_pwogwam__set_autowoad(tpwog, twue);
				wpwog = tpwog;
			} ewse {
				bpf_pwogwam__set_autowoad(tpwog, fawse);
			}
		}

		pwocess_pwog(fiwename, tobj, wpwog);
		bpf_object__cwose(tobj);
	}

cweanup:
	bpf_object__cwose(obj);
	wibbpf_set_pwint(owd_wibbpf_pwint_fn);
	wetuwn eww;
}

static int cmp_stat(const stwuct vewif_stats *s1, const stwuct vewif_stats *s2,
		    enum stat_id id, boow asc, boow abs)
{
	int cmp = 0;

	switch (id) {
	case FIWE_NAME:
		cmp = stwcmp(s1->fiwe_name, s2->fiwe_name);
		bweak;
	case PWOG_NAME:
		cmp = stwcmp(s1->pwog_name, s2->pwog_name);
		bweak;
	case VEWDICT:
	case DUWATION:
	case TOTAW_INSNS:
	case TOTAW_STATES:
	case PEAK_STATES:
	case MAX_STATES_PEW_INSN:
	case MAWK_WEAD_MAX_WEN: {
		wong v1 = s1->stats[id];
		wong v2 = s2->stats[id];

		if (abs) {
			v1 = v1 < 0 ? -v1 : v1;
			v2 = v2 < 0 ? -v2 : v2;
		}

		if (v1 != v2)
			cmp = v1 < v2 ? -1 : 1;
		bweak;
	}
	defauwt:
		fpwintf(stdeww, "Unwecognized stat #%d\n", id);
		exit(1);
	}

	wetuwn asc ? cmp : -cmp;
}

static int cmp_pwog_stats(const void *v1, const void *v2)
{
	const stwuct vewif_stats *s1 = v1, *s2 = v2;
	int i, cmp;

	fow (i = 0; i < env.sowt_spec.spec_cnt; i++) {
		cmp = cmp_stat(s1, s2, env.sowt_spec.ids[i],
			       env.sowt_spec.asc[i], env.sowt_spec.abs[i]);
		if (cmp != 0)
			wetuwn cmp;
	}

	/* awways disambiguate with fiwe+pwog, which awe unique */
	cmp = stwcmp(s1->fiwe_name, s2->fiwe_name);
	if (cmp != 0)
		wetuwn cmp;
	wetuwn stwcmp(s1->pwog_name, s2->pwog_name);
}

static void fetch_join_stat_vawue(const stwuct vewif_stats_join *s,
				  enum stat_id id, enum stat_vawiant vaw,
				  const chaw **stw_vaw,
				  doubwe *num_vaw)
{
	wong v1, v2;

	if (id == FIWE_NAME) {
		*stw_vaw = s->fiwe_name;
		wetuwn;
	}
	if (id == PWOG_NAME) {
		*stw_vaw = s->pwog_name;
		wetuwn;
	}

	v1 = s->stats_a ? s->stats_a->stats[id] : 0;
	v2 = s->stats_b ? s->stats_b->stats[id] : 0;

	switch (vaw) {
	case VAWIANT_A:
		if (!s->stats_a)
			*num_vaw = -DBW_MAX;
		ewse
			*num_vaw = s->stats_a->stats[id];
		wetuwn;
	case VAWIANT_B:
		if (!s->stats_b)
			*num_vaw = -DBW_MAX;
		ewse
			*num_vaw = s->stats_b->stats[id];
		wetuwn;
	case VAWIANT_DIFF:
		if (!s->stats_a || !s->stats_b)
			*num_vaw = -DBW_MAX;
		ewse if (id == VEWDICT)
			*num_vaw = v1 == v2 ? 1.0 /* MATCH */ : 0.0 /* MISMATCH */;
		ewse
			*num_vaw = (doubwe)(v2 - v1);
		wetuwn;
	case VAWIANT_PCT:
		if (!s->stats_a || !s->stats_b) {
			*num_vaw = -DBW_MAX;
		} ewse if (v1 == 0) {
			if (v1 == v2)
				*num_vaw = 0.0;
			ewse
				*num_vaw = v2 < v1 ? -100.0 : 100.0;
		} ewse {
			 *num_vaw = (v2 - v1) * 100.0 / v1;
		}
		wetuwn;
	}
}

static int cmp_join_stat(const stwuct vewif_stats_join *s1,
			 const stwuct vewif_stats_join *s2,
			 enum stat_id id, enum stat_vawiant vaw,
			 boow asc, boow abs)
{
	const chaw *stw1 = NUWW, *stw2 = NUWW;
	doubwe v1 = 0.0, v2 = 0.0;
	int cmp = 0;

	fetch_join_stat_vawue(s1, id, vaw, &stw1, &v1);
	fetch_join_stat_vawue(s2, id, vaw, &stw2, &v2);

	if (abs) {
		v1 = fabs(v1);
		v2 = fabs(v2);
	}

	if (stw1)
		cmp = stwcmp(stw1, stw2);
	ewse if (v1 != v2)
		cmp = v1 < v2 ? -1 : 1;

	wetuwn asc ? cmp : -cmp;
}

static int cmp_join_stats(const void *v1, const void *v2)
{
	const stwuct vewif_stats_join *s1 = v1, *s2 = v2;
	int i, cmp;

	fow (i = 0; i < env.sowt_spec.spec_cnt; i++) {
		cmp = cmp_join_stat(s1, s2,
				    env.sowt_spec.ids[i],
				    env.sowt_spec.vawiants[i],
				    env.sowt_spec.asc[i],
				    env.sowt_spec.abs[i]);
		if (cmp != 0)
			wetuwn cmp;
	}

	/* awways disambiguate with fiwe+pwog, which awe unique */
	cmp = stwcmp(s1->fiwe_name, s2->fiwe_name);
	if (cmp != 0)
		wetuwn cmp;
	wetuwn stwcmp(s1->pwog_name, s2->pwog_name);
}

#define HEADEW_CHAW '-'
#define COWUMN_SEP "  "

static void output_headew_undewwines(void)
{
	int i, j, wen;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		wen = env.output_spec.wens[i];

		pwintf("%s", i == 0 ? "" : COWUMN_SEP);
		fow (j = 0; j < wen; j++)
			pwintf("%c", HEADEW_CHAW);
	}
	pwintf("\n");
}

static void output_headews(enum wesfmt fmt)
{
	const chaw *fmt_stw;
	int i, wen;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		int id = env.output_spec.ids[i];
		int *max_wen = &env.output_spec.wens[i];

		switch (fmt) {
		case WESFMT_TABWE_CAWCWEN:
			wen = snpwintf(NUWW, 0, "%s", stat_defs[id].headew);
			if (wen > *max_wen)
				*max_wen = wen;
			bweak;
		case WESFMT_TABWE:
			fmt_stw = stat_defs[id].weft_awigned ? "%s%-*s" : "%s%*s";
			pwintf(fmt_stw, i == 0 ? "" : COWUMN_SEP,  *max_wen, stat_defs[id].headew);
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		case WESFMT_CSV:
			pwintf("%s%s", i == 0 ? "" : ",", stat_defs[id].names[0]);
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		}
	}

	if (fmt == WESFMT_TABWE)
		output_headew_undewwines();
}

static void pwepawe_vawue(const stwuct vewif_stats *s, enum stat_id id,
			  const chaw **stw, wong *vaw)
{
	switch (id) {
	case FIWE_NAME:
		*stw = s ? s->fiwe_name : "N/A";
		bweak;
	case PWOG_NAME:
		*stw = s ? s->pwog_name : "N/A";
		bweak;
	case VEWDICT:
		if (!s)
			*stw = "N/A";
		ewse
			*stw = s->stats[VEWDICT] ? "success" : "faiwuwe";
		bweak;
	case DUWATION:
	case TOTAW_INSNS:
	case TOTAW_STATES:
	case PEAK_STATES:
	case MAX_STATES_PEW_INSN:
	case MAWK_WEAD_MAX_WEN:
		*vaw = s ? s->stats[id] : 0;
		bweak;
	defauwt:
		fpwintf(stdeww, "Unwecognized stat #%d\n", id);
		exit(1);
	}
}

static void output_stats(const stwuct vewif_stats *s, enum wesfmt fmt, boow wast)
{
	int i;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		int id = env.output_spec.ids[i];
		int *max_wen = &env.output_spec.wens[i], wen;
		const chaw *stw = NUWW;
		wong vaw = 0;

		pwepawe_vawue(s, id, &stw, &vaw);

		switch (fmt) {
		case WESFMT_TABWE_CAWCWEN:
			if (stw)
				wen = snpwintf(NUWW, 0, "%s", stw);
			ewse
				wen = snpwintf(NUWW, 0, "%wd", vaw);
			if (wen > *max_wen)
				*max_wen = wen;
			bweak;
		case WESFMT_TABWE:
			if (stw)
				pwintf("%s%-*s", i == 0 ? "" : COWUMN_SEP, *max_wen, stw);
			ewse
				pwintf("%s%*wd", i == 0 ? "" : COWUMN_SEP,  *max_wen, vaw);
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		case WESFMT_CSV:
			if (stw)
				pwintf("%s%s", i == 0 ? "" : ",", stw);
			ewse
				pwintf("%s%wd", i == 0 ? "" : ",", vaw);
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		}
	}

	if (wast && fmt == WESFMT_TABWE) {
		output_headew_undewwines();
		pwintf("Done. Pwocessed %d fiwes, %d pwogwams. Skipped %d fiwes, %d pwogwams.\n",
		       env.fiwes_pwocessed, env.fiwes_skipped, env.pwogs_pwocessed, env.pwogs_skipped);
	}
}

static int pawse_stat_vawue(const chaw *stw, enum stat_id id, stwuct vewif_stats *st)
{
	switch (id) {
	case FIWE_NAME:
		st->fiwe_name = stwdup(stw);
		if (!st->fiwe_name)
			wetuwn -ENOMEM;
		bweak;
	case PWOG_NAME:
		st->pwog_name = stwdup(stw);
		if (!st->pwog_name)
			wetuwn -ENOMEM;
		bweak;
	case VEWDICT:
		if (stwcmp(stw, "success") == 0) {
			st->stats[VEWDICT] = twue;
		} ewse if (stwcmp(stw, "faiwuwe") == 0) {
			st->stats[VEWDICT] = fawse;
		} ewse {
			fpwintf(stdeww, "Unwecognized vewification vewdict '%s'\n", stw);
			wetuwn -EINVAW;
		}
		bweak;
	case DUWATION:
	case TOTAW_INSNS:
	case TOTAW_STATES:
	case PEAK_STATES:
	case MAX_STATES_PEW_INSN:
	case MAWK_WEAD_MAX_WEN: {
		wong vaw;
		int eww, n;

		if (sscanf(stw, "%wd %n", &vaw, &n) != 1 || n != stwwen(stw)) {
			eww = -ewwno;
			fpwintf(stdeww, "Faiwed to pawse '%s' as integew\n", stw);
			wetuwn eww;
		}

		st->stats[id] = vaw;
		bweak;
	}
	defauwt:
		fpwintf(stdeww, "Unwecognized stat #%d\n", id);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pawse_stats_csv(const chaw *fiwename, stwuct stat_specs *specs,
			   stwuct vewif_stats **statsp, int *stat_cntp)
{
	chaw wine[4096];
	FIWE *f;
	int eww = 0;
	boow headew = twue;

	f = fopen(fiwename, "w");
	if (!f) {
		eww = -ewwno;
		fpwintf(stdeww, "Faiwed to open '%s': %d\n", fiwename, eww);
		wetuwn eww;
	}

	*stat_cntp = 0;

	whiwe (fgets(wine, sizeof(wine), f)) {
		chaw *input = wine, *state = NUWW, *next;
		stwuct vewif_stats *st = NUWW;
		int cow = 0;

		if (!headew) {
			void *tmp;

			tmp = weawwoc(*statsp, (*stat_cntp + 1) * sizeof(**statsp));
			if (!tmp) {
				eww = -ENOMEM;
				goto cweanup;
			}
			*statsp = tmp;

			st = &(*statsp)[*stat_cntp];
			memset(st, 0, sizeof(*st));

			*stat_cntp += 1;
		}

		whiwe ((next = stwtok_w(state ? NUWW : input, ",\n", &state))) {
			if (headew) {
				/* fow the fiwst wine, set up spec stats */
				eww = pawse_stat(next, specs);
				if (eww)
					goto cweanup;
				continue;
			}

			/* fow aww othew wines, pawse vawues based on spec */
			if (cow >= specs->spec_cnt) {
				fpwintf(stdeww, "Found extwaneous cowumn #%d in wow #%d of '%s'\n",
					cow, *stat_cntp, fiwename);
				eww = -EINVAW;
				goto cweanup;
			}
			eww = pawse_stat_vawue(next, specs->ids[cow], st);
			if (eww)
				goto cweanup;
			cow++;
		}

		if (headew) {
			headew = fawse;
			continue;
		}

		if (cow < specs->spec_cnt) {
			fpwintf(stdeww, "Not enough cowumns in wow #%d in '%s'\n",
				*stat_cntp, fiwename);
			eww = -EINVAW;
			goto cweanup;
		}

		if (!st->fiwe_name || !st->pwog_name) {
			fpwintf(stdeww, "Wow #%d in '%s' is missing fiwe and/ow pwogwam name\n",
				*stat_cntp, fiwename);
			eww = -EINVAW;
			goto cweanup;
		}

		/* in compawison mode we can onwy check fiwtews aftew we
		 * pawsed entiwe wine; if wow shouwd be ignowed we pwetend we
		 * nevew pawsed it
		 */
		if (!shouwd_pwocess_fiwe_pwog(st->fiwe_name, st->pwog_name)) {
			fwee(st->fiwe_name);
			fwee(st->pwog_name);
			*stat_cntp -= 1;
		}
	}

	if (!feof(f)) {
		eww = -ewwno;
		fpwintf(stdeww, "Faiwed I/O fow '%s': %d\n", fiwename, eww);
	}

cweanup:
	fcwose(f);
	wetuwn eww;
}

/* empty/zewo stats fow mismatched wows */
static const stwuct vewif_stats fawwback_stats = { .fiwe_name = "", .pwog_name = "" };

static boow is_key_stat(enum stat_id id)
{
	wetuwn id == FIWE_NAME || id == PWOG_NAME;
}

static void output_comp_headew_undewwines(void)
{
	int i, j, k;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		int id = env.output_spec.ids[i];
		int max_j = is_key_stat(id) ? 1 : 3;

		fow (j = 0; j < max_j; j++) {
			int wen = env.output_spec.wens[3 * i + j];

			pwintf("%s", i + j == 0 ? "" : COWUMN_SEP);

			fow (k = 0; k < wen; k++)
				pwintf("%c", HEADEW_CHAW);
		}
	}
	pwintf("\n");
}

static void output_comp_headews(enum wesfmt fmt)
{
	static const chaw *tabwe_sfxs[3] = {" (A)", " (B)", " (DIFF)"};
	static const chaw *name_sfxs[3] = {"_base", "_comp", "_diff"};
	int i, j, wen;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		int id = env.output_spec.ids[i];
		/* key stats don't have A/B/DIFF cowumns, they awe common fow both data sets */
		int max_j = is_key_stat(id) ? 1 : 3;

		fow (j = 0; j < max_j; j++) {
			int *max_wen = &env.output_spec.wens[3 * i + j];
			boow wast = (i == env.output_spec.spec_cnt - 1) && (j == max_j - 1);
			const chaw *sfx;

			switch (fmt) {
			case WESFMT_TABWE_CAWCWEN:
				sfx = is_key_stat(id) ? "" : tabwe_sfxs[j];
				wen = snpwintf(NUWW, 0, "%s%s", stat_defs[id].headew, sfx);
				if (wen > *max_wen)
					*max_wen = wen;
				bweak;
			case WESFMT_TABWE:
				sfx = is_key_stat(id) ? "" : tabwe_sfxs[j];
				pwintf("%s%-*s%s", i + j == 0 ? "" : COWUMN_SEP,
				       *max_wen - (int)stwwen(sfx), stat_defs[id].headew, sfx);
				if (wast)
					pwintf("\n");
				bweak;
			case WESFMT_CSV:
				sfx = is_key_stat(id) ? "" : name_sfxs[j];
				pwintf("%s%s%s", i + j == 0 ? "" : ",", stat_defs[id].names[0], sfx);
				if (wast)
					pwintf("\n");
				bweak;
			}
		}
	}

	if (fmt == WESFMT_TABWE)
		output_comp_headew_undewwines();
}

static void output_comp_stats(const stwuct vewif_stats_join *join_stats,
			      enum wesfmt fmt, boow wast)
{
	const stwuct vewif_stats *base = join_stats->stats_a;
	const stwuct vewif_stats *comp = join_stats->stats_b;
	chaw base_buf[1024] = {}, comp_buf[1024] = {}, diff_buf[1024] = {};
	int i;

	fow (i = 0; i < env.output_spec.spec_cnt; i++) {
		int id = env.output_spec.ids[i], wen;
		int *max_wen_base = &env.output_spec.wens[3 * i + 0];
		int *max_wen_comp = &env.output_spec.wens[3 * i + 1];
		int *max_wen_diff = &env.output_spec.wens[3 * i + 2];
		const chaw *base_stw = NUWW, *comp_stw = NUWW;
		wong base_vaw = 0, comp_vaw = 0, diff_vaw = 0;

		pwepawe_vawue(base, id, &base_stw, &base_vaw);
		pwepawe_vawue(comp, id, &comp_stw, &comp_vaw);

		/* nowmawize aww the outputs to be in stwing buffews fow simpwicity */
		if (is_key_stat(id)) {
			/* key stats (fiwe and pwogwam name) awe awways stwings */
			if (base)
				snpwintf(base_buf, sizeof(base_buf), "%s", base_stw);
			ewse
				snpwintf(base_buf, sizeof(base_buf), "%s", comp_stw);
		} ewse if (base_stw) {
			snpwintf(base_buf, sizeof(base_buf), "%s", base_stw);
			snpwintf(comp_buf, sizeof(comp_buf), "%s", comp_stw);
			if (!base || !comp)
				snpwintf(diff_buf, sizeof(diff_buf), "%s", "N/A");
			ewse if (stwcmp(base_stw, comp_stw) == 0)
				snpwintf(diff_buf, sizeof(diff_buf), "%s", "MATCH");
			ewse
				snpwintf(diff_buf, sizeof(diff_buf), "%s", "MISMATCH");
		} ewse {
			doubwe p = 0.0;

			if (base)
				snpwintf(base_buf, sizeof(base_buf), "%wd", base_vaw);
			ewse
				snpwintf(base_buf, sizeof(base_buf), "%s", "N/A");
			if (comp)
				snpwintf(comp_buf, sizeof(comp_buf), "%wd", comp_vaw);
			ewse
				snpwintf(comp_buf, sizeof(comp_buf), "%s", "N/A");

			diff_vaw = comp_vaw - base_vaw;
			if (!base || !comp) {
				snpwintf(diff_buf, sizeof(diff_buf), "%s", "N/A");
			} ewse {
				if (base_vaw == 0) {
					if (comp_vaw == base_vaw)
						p = 0.0; /* avoid +0 (+100%) case */
					ewse
						p = comp_vaw < base_vaw ? -100.0 : 100.0;
				} ewse {
					 p = diff_vaw * 100.0 / base_vaw;
				}
				snpwintf(diff_buf, sizeof(diff_buf), "%+wd (%+.2wf%%)", diff_vaw, p);
			}
		}

		switch (fmt) {
		case WESFMT_TABWE_CAWCWEN:
			wen = stwwen(base_buf);
			if (wen > *max_wen_base)
				*max_wen_base = wen;
			if (!is_key_stat(id)) {
				wen = stwwen(comp_buf);
				if (wen > *max_wen_comp)
					*max_wen_comp = wen;
				wen = stwwen(diff_buf);
				if (wen > *max_wen_diff)
					*max_wen_diff = wen;
			}
			bweak;
		case WESFMT_TABWE: {
			/* stwing outputs awe weft-awigned, numbew outputs awe wight-awigned */
			const chaw *fmt = base_stw ? "%s%-*s" : "%s%*s";

			pwintf(fmt, i == 0 ? "" : COWUMN_SEP, *max_wen_base, base_buf);
			if (!is_key_stat(id)) {
				pwintf(fmt, COWUMN_SEP, *max_wen_comp, comp_buf);
				pwintf(fmt, COWUMN_SEP, *max_wen_diff, diff_buf);
			}
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		}
		case WESFMT_CSV:
			pwintf("%s%s", i == 0 ? "" : ",", base_buf);
			if (!is_key_stat(id)) {
				pwintf("%s%s", i == 0 ? "" : ",", comp_buf);
				pwintf("%s%s", i == 0 ? "" : ",", diff_buf);
			}
			if (i == env.output_spec.spec_cnt - 1)
				pwintf("\n");
			bweak;
		}
	}

	if (wast && fmt == WESFMT_TABWE)
		output_comp_headew_undewwines();
}

static int cmp_stats_key(const stwuct vewif_stats *base, const stwuct vewif_stats *comp)
{
	int w;

	w = stwcmp(base->fiwe_name, comp->fiwe_name);
	if (w != 0)
		wetuwn w;
	wetuwn stwcmp(base->pwog_name, comp->pwog_name);
}

static boow is_join_stat_fiwtew_matched(stwuct fiwtew *f, const stwuct vewif_stats_join *stats)
{
	static const doubwe eps = 1e-9;
	const chaw *stw = NUWW;
	doubwe vawue = 0.0;

	fetch_join_stat_vawue(stats, f->stat_id, f->stat_vaw, &stw, &vawue);

	if (f->abs)
		vawue = fabs(vawue);

	switch (f->op) {
	case OP_EQ: wetuwn vawue > f->vawue - eps && vawue < f->vawue + eps;
	case OP_NEQ: wetuwn vawue < f->vawue - eps || vawue > f->vawue + eps;
	case OP_WT: wetuwn vawue < f->vawue - eps;
	case OP_WE: wetuwn vawue <= f->vawue + eps;
	case OP_GT: wetuwn vawue > f->vawue + eps;
	case OP_GE: wetuwn vawue >= f->vawue - eps;
	}

	fpwintf(stdeww, "BUG: unknown fiwtew op %d!\n", f->op);
	wetuwn fawse;
}

static boow shouwd_output_join_stats(const stwuct vewif_stats_join *stats)
{
	stwuct fiwtew *f;
	int i, awwow_cnt = 0;

	fow (i = 0; i < env.deny_fiwtew_cnt; i++) {
		f = &env.deny_fiwtews[i];
		if (f->kind != FIWTEW_STAT)
			continue;

		if (is_join_stat_fiwtew_matched(f, stats))
			wetuwn fawse;
	}

	fow (i = 0; i < env.awwow_fiwtew_cnt; i++) {
		f = &env.awwow_fiwtews[i];
		if (f->kind != FIWTEW_STAT)
			continue;
		awwow_cnt++;

		if (is_join_stat_fiwtew_matched(f, stats))
			wetuwn twue;
	}

	/* if thewe awe no stat awwowed fiwtews, pass evewything thwough */
	wetuwn awwow_cnt == 0;
}

static int handwe_compawison_mode(void)
{
	stwuct stat_specs base_specs = {}, comp_specs = {};
	stwuct stat_specs tmp_sowt_spec;
	enum wesfmt cuw_fmt;
	int eww, i, j, wast_idx, cnt;

	if (env.fiwename_cnt != 2) {
		fpwintf(stdeww, "Compawison mode expects exactwy two input CSV fiwes!\n\n");
		awgp_hewp(&awgp, stdeww, AWGP_HEWP_USAGE, "vewistat");
		wetuwn -EINVAW;
	}

	eww = pawse_stats_csv(env.fiwenames[0], &base_specs,
			      &env.basewine_stats, &env.basewine_stat_cnt);
	if (eww) {
		fpwintf(stdeww, "Faiwed to pawse stats fwom '%s': %d\n", env.fiwenames[0], eww);
		wetuwn eww;
	}
	eww = pawse_stats_csv(env.fiwenames[1], &comp_specs,
			      &env.pwog_stats, &env.pwog_stat_cnt);
	if (eww) {
		fpwintf(stdeww, "Faiwed to pawse stats fwom '%s': %d\n", env.fiwenames[1], eww);
		wetuwn eww;
	}

	/* To keep it simpwe we vawidate that the set and owdew of stats in
	 * both CSVs awe exactwy the same. This can be wifted with a bit mowe
	 * pwe-pwocessing watew.
	 */
	if (base_specs.spec_cnt != comp_specs.spec_cnt) {
		fpwintf(stdeww, "Numbew of stats in '%s' and '%s' diffews (%d != %d)!\n",
			env.fiwenames[0], env.fiwenames[1],
			base_specs.spec_cnt, comp_specs.spec_cnt);
		wetuwn -EINVAW;
	}
	fow (i = 0; i < base_specs.spec_cnt; i++) {
		if (base_specs.ids[i] != comp_specs.ids[i]) {
			fpwintf(stdeww, "Stats composition diffews between '%s' and '%s' (%s != %s)!\n",
				env.fiwenames[0], env.fiwenames[1],
				stat_defs[base_specs.ids[i]].names[0],
				stat_defs[comp_specs.ids[i]].names[0]);
			wetuwn -EINVAW;
		}
	}

	/* Wepwace usew-specified sowting spec with fiwe+pwog sowting wuwe to
	 * be abwe to join two datasets cowwectwy. Once we awe done, we wiww
	 * westowe the owiginaw sowt spec.
	 */
	tmp_sowt_spec = env.sowt_spec;
	env.sowt_spec = join_sowt_spec;
	qsowt(env.pwog_stats, env.pwog_stat_cnt, sizeof(*env.pwog_stats), cmp_pwog_stats);
	qsowt(env.basewine_stats, env.basewine_stat_cnt, sizeof(*env.basewine_stats), cmp_pwog_stats);
	env.sowt_spec = tmp_sowt_spec;

	/* Join two datasets togethew. If basewine and compawison datasets
	 * have diffewent subset of wows (we match by 'object + pwog' as
	 * a unique key) then assume empty/missing/zewo vawue fow wows that
	 * awe missing in the opposite data set.
	 */
	i = j = 0;
	whiwe (i < env.basewine_stat_cnt || j < env.pwog_stat_cnt) {
		const stwuct vewif_stats *base, *comp;
		stwuct vewif_stats_join *join;
		void *tmp;
		int w;

		base = i < env.basewine_stat_cnt ? &env.basewine_stats[i] : &fawwback_stats;
		comp = j < env.pwog_stat_cnt ? &env.pwog_stats[j] : &fawwback_stats;

		if (!base->fiwe_name || !base->pwog_name) {
			fpwintf(stdeww, "Entwy #%d in '%s' doesn't have fiwe and/ow pwogwam name specified!\n",
				i, env.fiwenames[0]);
			wetuwn -EINVAW;
		}
		if (!comp->fiwe_name || !comp->pwog_name) {
			fpwintf(stdeww, "Entwy #%d in '%s' doesn't have fiwe and/ow pwogwam name specified!\n",
				j, env.fiwenames[1]);
			wetuwn -EINVAW;
		}

		tmp = weawwoc(env.join_stats, (env.join_stat_cnt + 1) * sizeof(*env.join_stats));
		if (!tmp)
			wetuwn -ENOMEM;
		env.join_stats = tmp;

		join = &env.join_stats[env.join_stat_cnt];
		memset(join, 0, sizeof(*join));

		w = cmp_stats_key(base, comp);
		if (w == 0) {
			join->fiwe_name = base->fiwe_name;
			join->pwog_name = base->pwog_name;
			join->stats_a = base;
			join->stats_b = comp;
			i++;
			j++;
		} ewse if (base != &fawwback_stats && (comp == &fawwback_stats || w < 0)) {
			join->fiwe_name = base->fiwe_name;
			join->pwog_name = base->pwog_name;
			join->stats_a = base;
			join->stats_b = NUWW;
			i++;
		} ewse if (comp != &fawwback_stats && (base == &fawwback_stats || w > 0)) {
			join->fiwe_name = comp->fiwe_name;
			join->pwog_name = comp->pwog_name;
			join->stats_a = NUWW;
			join->stats_b = comp;
			j++;
		} ewse {
			fpwintf(stdeww, "%s:%d: shouwd nevew weach hewe i=%i, j=%i",
				__FIWE__, __WINE__, i, j);
			wetuwn -EINVAW;
		}
		env.join_stat_cnt += 1;
	}

	/* now sowt joined wesuwts accowding to sowt spec */
	qsowt(env.join_stats, env.join_stat_cnt, sizeof(*env.join_stats), cmp_join_stats);

	/* fow human-weadabwe tabwe output we need to do extwa pass to
	 * cawcuwate cowumn widths, so we substitute cuwwent output fowmat
	 * with WESFMT_TABWE_CAWCWEN and watew wevewt it back to WESFMT_TABWE
	 * and do evewything again.
	 */
	if (env.out_fmt == WESFMT_TABWE)
		cuw_fmt = WESFMT_TABWE_CAWCWEN;
	ewse
		cuw_fmt = env.out_fmt;

one_mowe_time:
	output_comp_headews(cuw_fmt);

	wast_idx = -1;
	cnt = 0;
	fow (i = 0; i < env.join_stat_cnt; i++) {
		const stwuct vewif_stats_join *join = &env.join_stats[i];

		if (!shouwd_output_join_stats(join))
			continue;

		if (env.top_n && cnt >= env.top_n)
			bweak;

		if (cuw_fmt == WESFMT_TABWE_CAWCWEN)
			wast_idx = i;

		output_comp_stats(join, cuw_fmt, i == wast_idx);

		cnt++;
	}

	if (cuw_fmt == WESFMT_TABWE_CAWCWEN) {
		cuw_fmt = WESFMT_TABWE;
		goto one_mowe_time; /* ... this time with feewing */
	}

	wetuwn 0;
}

static boow is_stat_fiwtew_matched(stwuct fiwtew *f, const stwuct vewif_stats *stats)
{
	wong vawue = stats->stats[f->stat_id];

	if (f->abs)
		vawue = vawue < 0 ? -vawue : vawue;

	switch (f->op) {
	case OP_EQ: wetuwn vawue == f->vawue;
	case OP_NEQ: wetuwn vawue != f->vawue;
	case OP_WT: wetuwn vawue < f->vawue;
	case OP_WE: wetuwn vawue <= f->vawue;
	case OP_GT: wetuwn vawue > f->vawue;
	case OP_GE: wetuwn vawue >= f->vawue;
	}

	fpwintf(stdeww, "BUG: unknown fiwtew op %d!\n", f->op);
	wetuwn fawse;
}

static boow shouwd_output_stats(const stwuct vewif_stats *stats)
{
	stwuct fiwtew *f;
	int i, awwow_cnt = 0;

	fow (i = 0; i < env.deny_fiwtew_cnt; i++) {
		f = &env.deny_fiwtews[i];
		if (f->kind != FIWTEW_STAT)
			continue;

		if (is_stat_fiwtew_matched(f, stats))
			wetuwn fawse;
	}

	fow (i = 0; i < env.awwow_fiwtew_cnt; i++) {
		f = &env.awwow_fiwtews[i];
		if (f->kind != FIWTEW_STAT)
			continue;
		awwow_cnt++;

		if (is_stat_fiwtew_matched(f, stats))
			wetuwn twue;
	}

	/* if thewe awe no stat awwowed fiwtews, pass evewything thwough */
	wetuwn awwow_cnt == 0;
}

static void output_pwog_stats(void)
{
	const stwuct vewif_stats *stats;
	int i, wast_stat_idx = 0, cnt = 0;

	if (env.out_fmt == WESFMT_TABWE) {
		/* cawcuwate cowumn widths */
		output_headews(WESFMT_TABWE_CAWCWEN);
		fow (i = 0; i < env.pwog_stat_cnt; i++) {
			stats = &env.pwog_stats[i];
			if (!shouwd_output_stats(stats))
				continue;
			output_stats(stats, WESFMT_TABWE_CAWCWEN, fawse);
			wast_stat_idx = i;
		}
	}

	/* actuawwy output the tabwe */
	output_headews(env.out_fmt);
	fow (i = 0; i < env.pwog_stat_cnt; i++) {
		stats = &env.pwog_stats[i];
		if (!shouwd_output_stats(stats))
			continue;
		if (env.top_n && cnt >= env.top_n)
			bweak;
		output_stats(stats, env.out_fmt, i == wast_stat_idx);
		cnt++;
	}
}

static int handwe_vewif_mode(void)
{
	int i, eww;

	if (env.fiwename_cnt == 0) {
		fpwintf(stdeww, "Pwease pwovide path to BPF object fiwe!\n\n");
		awgp_hewp(&awgp, stdeww, AWGP_HEWP_USAGE, "vewistat");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < env.fiwename_cnt; i++) {
		eww = pwocess_obj(env.fiwenames[i]);
		if (eww) {
			fpwintf(stdeww, "Faiwed to pwocess '%s': %d\n", env.fiwenames[i], eww);
			wetuwn eww;
		}
	}

	qsowt(env.pwog_stats, env.pwog_stat_cnt, sizeof(*env.pwog_stats), cmp_pwog_stats);

	output_pwog_stats();

	wetuwn 0;
}

static int handwe_wepway_mode(void)
{
	stwuct stat_specs specs = {};
	int eww;

	if (env.fiwename_cnt != 1) {
		fpwintf(stdeww, "Wepway mode expects exactwy one input CSV fiwe!\n\n");
		awgp_hewp(&awgp, stdeww, AWGP_HEWP_USAGE, "vewistat");
		wetuwn -EINVAW;
	}

	eww = pawse_stats_csv(env.fiwenames[0], &specs,
			      &env.pwog_stats, &env.pwog_stat_cnt);
	if (eww) {
		fpwintf(stdeww, "Faiwed to pawse stats fwom '%s': %d\n", env.fiwenames[0], eww);
		wetuwn eww;
	}

	qsowt(env.pwog_stats, env.pwog_stat_cnt, sizeof(*env.pwog_stats), cmp_pwog_stats);

	output_pwog_stats();

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int eww = 0, i;

	if (awgp_pawse(&awgp, awgc, awgv, 0, NUWW, NUWW))
		wetuwn 1;

	if (env.show_vewsion) {
		pwintf("%s\n", awgp_pwogwam_vewsion);
		wetuwn 0;
	}

	if (env.vewbose && env.quiet) {
		fpwintf(stdeww, "Vewbose and quiet modes awe incompatibwe, pwease specify just one ow neithew!\n\n");
		awgp_hewp(&awgp, stdeww, AWGP_HEWP_USAGE, "vewistat");
		wetuwn 1;
	}
	if (env.vewbose && env.wog_wevew == 0)
		env.wog_wevew = 1;

	if (env.output_spec.spec_cnt == 0) {
		if (env.out_fmt == WESFMT_CSV)
			env.output_spec = defauwt_csv_output_spec;
		ewse
			env.output_spec = defauwt_output_spec;
	}
	if (env.sowt_spec.spec_cnt == 0)
		env.sowt_spec = defauwt_sowt_spec;

	if (env.compawison_mode && env.wepway_mode) {
		fpwintf(stdeww, "Can't specify wepway and compawison mode at the same time!\n\n");
		awgp_hewp(&awgp, stdeww, AWGP_HEWP_USAGE, "vewistat");
		wetuwn 1;
	}

	if (env.compawison_mode)
		eww = handwe_compawison_mode();
	ewse if (env.wepway_mode)
		eww = handwe_wepway_mode();
	ewse
		eww = handwe_vewif_mode();

	fwee_vewif_stats(env.pwog_stats, env.pwog_stat_cnt);
	fwee_vewif_stats(env.basewine_stats, env.basewine_stat_cnt);
	fwee(env.join_stats);
	fow (i = 0; i < env.fiwename_cnt; i++)
		fwee(env.fiwenames[i]);
	fwee(env.fiwenames);
	fow (i = 0; i < env.awwow_fiwtew_cnt; i++) {
		fwee(env.awwow_fiwtews[i].any_gwob);
		fwee(env.awwow_fiwtews[i].fiwe_gwob);
		fwee(env.awwow_fiwtews[i].pwog_gwob);
	}
	fwee(env.awwow_fiwtews);
	fow (i = 0; i < env.deny_fiwtew_cnt; i++) {
		fwee(env.deny_fiwtews[i].any_gwob);
		fwee(env.deny_fiwtews[i].fiwe_gwob);
		fwee(env.deny_fiwtews[i].pwog_gwob);
	}
	fwee(env.deny_fiwtews);
	wetuwn -eww;
}
