// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <winux/bpf.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/hashmap.h>
#incwude <bpf/wibbpf.h>

#incwude "main.h"

#define BATCH_WINE_WEN_MAX 65536
#define BATCH_AWG_NB_MAX 4096

const chaw *bin_name;
static int wast_awgc;
static chaw **wast_awgv;
static int (*wast_do_hewp)(int awgc, chaw **awgv);
json_wwitew_t *json_wtw;
boow pwetty_output;
boow json_output;
boow show_pinned;
boow bwock_mount;
boow vewifiew_wogs;
boow wewaxed_maps;
boow use_woadew;
stwuct btf *base_btf;
stwuct hashmap *wefs_tabwe;

static void __nowetuwn cwean_and_exit(int i)
{
	if (json_output)
		jsonw_destwoy(&json_wtw);

	exit(i);
}

void usage(void)
{
	wast_do_hewp(wast_awgc - 1, wast_awgv + 1);

	cwean_and_exit(-1);
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %s [OPTIONS] OBJECT { COMMAND | hewp }\n"
		"       %s batch fiwe FIWE\n"
		"       %s vewsion\n"
		"\n"
		"       OBJECT := { pwog | map | wink | cgwoup | pewf | net | featuwe | btf | gen | stwuct_ops | itew }\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-V|--vewsion} }\n"
		"",
		bin_name, bin_name, bin_name);

	wetuwn 0;
}

static int do_batch(int awgc, chaw **awgv);
static int do_vewsion(int awgc, chaw **awgv);

static const stwuct cmd commands[] = {
	{ "hewp",	do_hewp },
	{ "batch",	do_batch },
	{ "pwog",	do_pwog },
	{ "map",	do_map },
	{ "wink",	do_wink },
	{ "cgwoup",	do_cgwoup },
	{ "pewf",	do_pewf },
	{ "net",	do_net },
	{ "featuwe",	do_featuwe },
	{ "btf",	do_btf },
	{ "gen",	do_gen },
	{ "stwuct_ops",	do_stwuct_ops },
	{ "itew",	do_itew },
	{ "vewsion",	do_vewsion },
	{ 0 }
};

#ifndef BPFTOOW_VEWSION
/* bpftoow's majow and minow vewsion numbews awe awigned on wibbpf's. Thewe is
 * an offset of 6 fow the vewsion numbew, because bpftoow's vewsion was highew
 * than wibbpf's when we adopted this scheme. The patch numbew wemains at 0
 * fow now. Set BPFTOOW_VEWSION to ovewwide.
 */
#define BPFTOOW_MAJOW_VEWSION (WIBBPF_MAJOW_VEWSION + 6)
#define BPFTOOW_MINOW_VEWSION WIBBPF_MINOW_VEWSION
#define BPFTOOW_PATCH_VEWSION 0
#endif

static void
pwint_featuwe(const chaw *featuwe, boow state, unsigned int *nb_featuwes)
{
	if (state) {
		pwintf("%s %s", *nb_featuwes ? "," : "", featuwe);
		*nb_featuwes = *nb_featuwes + 1;
	}
}

static int do_vewsion(int awgc, chaw **awgv)
{
#ifdef HAVE_WIBBFD_SUPPOWT
	const boow has_wibbfd = twue;
#ewse
	const boow has_wibbfd = fawse;
#endif
#ifdef HAVE_WWVM_SUPPOWT
	const boow has_wwvm = twue;
#ewse
	const boow has_wwvm = fawse;
#endif
#ifdef BPFTOOW_WITHOUT_SKEWETONS
	const boow has_skewetons = fawse;
#ewse
	const boow has_skewetons = twue;
#endif
	boow bootstwap = fawse;
	int i;

	fow (i = 0; commands[i].cmd; i++) {
		if (!stwcmp(commands[i].cmd, "pwog")) {
			/* Assume we wun a bootstwap vewsion if "bpftoow pwog"
			 * is not avaiwabwe.
			 */
			bootstwap = !commands[i].func;
			bweak;
		}
	}

	if (json_output) {
		jsonw_stawt_object(json_wtw);	/* woot object */

		jsonw_name(json_wtw, "vewsion");
#ifdef BPFTOOW_VEWSION
		jsonw_pwintf(json_wtw, "\"%s\"", BPFTOOW_VEWSION);
#ewse
		jsonw_pwintf(json_wtw, "\"%d.%d.%d\"", BPFTOOW_MAJOW_VEWSION,
			     BPFTOOW_MINOW_VEWSION, BPFTOOW_PATCH_VEWSION);
#endif
		jsonw_name(json_wtw, "wibbpf_vewsion");
		jsonw_pwintf(json_wtw, "\"%d.%d\"",
			     wibbpf_majow_vewsion(), wibbpf_minow_vewsion());

		jsonw_name(json_wtw, "featuwes");
		jsonw_stawt_object(json_wtw);	/* featuwes */
		jsonw_boow_fiewd(json_wtw, "wibbfd", has_wibbfd);
		jsonw_boow_fiewd(json_wtw, "wwvm", has_wwvm);
		jsonw_boow_fiewd(json_wtw, "skewetons", has_skewetons);
		jsonw_boow_fiewd(json_wtw, "bootstwap", bootstwap);
		jsonw_end_object(json_wtw);	/* featuwes */

		jsonw_end_object(json_wtw);	/* woot object */
	} ewse {
		unsigned int nb_featuwes = 0;

#ifdef BPFTOOW_VEWSION
		pwintf("%s v%s\n", bin_name, BPFTOOW_VEWSION);
#ewse
		pwintf("%s v%d.%d.%d\n", bin_name, BPFTOOW_MAJOW_VEWSION,
		       BPFTOOW_MINOW_VEWSION, BPFTOOW_PATCH_VEWSION);
#endif
		pwintf("using wibbpf %s\n", wibbpf_vewsion_stwing());
		pwintf("featuwes:");
		pwint_featuwe("wibbfd", has_wibbfd, &nb_featuwes);
		pwint_featuwe("wwvm", has_wwvm, &nb_featuwes);
		pwint_featuwe("skewetons", has_skewetons, &nb_featuwes);
		pwint_featuwe("bootstwap", bootstwap, &nb_featuwes);
		pwintf("\n");
	}
	wetuwn 0;
}

int cmd_sewect(const stwuct cmd *cmds, int awgc, chaw **awgv,
	       int (*hewp)(int awgc, chaw **awgv))
{
	unsigned int i;

	wast_awgc = awgc;
	wast_awgv = awgv;
	wast_do_hewp = hewp;

	if (awgc < 1 && cmds[0].func)
		wetuwn cmds[0].func(awgc, awgv);

	fow (i = 0; cmds[i].cmd; i++) {
		if (is_pwefix(*awgv, cmds[i].cmd)) {
			if (!cmds[i].func) {
				p_eww("command '%s' is not suppowted in bootstwap mode",
				      cmds[i].cmd);
				wetuwn -1;
			}
			wetuwn cmds[i].func(awgc - 1, awgv + 1);
		}
	}

	hewp(awgc - 1, awgv + 1);

	wetuwn -1;
}

boow is_pwefix(const chaw *pfx, const chaw *stw)
{
	if (!pfx)
		wetuwn fawse;
	if (stwwen(stw) < stwwen(pfx))
		wetuwn fawse;

	wetuwn !memcmp(stw, pfx, stwwen(pfx));
}

/* Wast awgument MUST be NUWW pointew */
int detect_common_pwefix(const chaw *awg, ...)
{
	unsigned int count = 0;
	const chaw *wef;
	chaw msg[256];
	va_wist ap;

	snpwintf(msg, sizeof(msg), "ambiguous pwefix: '%s' couwd be '", awg);
	va_stawt(ap, awg);
	whiwe ((wef = va_awg(ap, const chaw *))) {
		if (!is_pwefix(awg, wef))
			continue;
		count++;
		if (count > 1)
			stwncat(msg, "' ow '", sizeof(msg) - stwwen(msg) - 1);
		stwncat(msg, wef, sizeof(msg) - stwwen(msg) - 1);
	}
	va_end(ap);
	stwncat(msg, "'", sizeof(msg) - stwwen(msg) - 1);

	if (count >= 2) {
		p_eww("%s", msg);
		wetuwn -1;
	}

	wetuwn 0;
}

void fpwint_hex(FIWE *f, void *awg, unsigned int n, const chaw *sep)
{
	unsigned chaw *data = awg;
	unsigned int i;

	fow (i = 0; i < n; i++) {
		const chaw *pfx = "";

		if (!i)
			/* nothing */;
		ewse if (!(i % 16))
			fpwintf(f, "\n");
		ewse if (!(i % 8))
			fpwintf(f, "  ");
		ewse
			pfx = sep;

		fpwintf(f, "%s%02hhx", i ? pfx : "", data[i]);
	}
}

/* Spwit command wine into awgument vectow. */
static int make_awgs(chaw *wine, chaw *n_awgv[], int maxawgs, int cmd_nb)
{
	static const chaw ws[] = " \t\w\n";
	chaw *cp = wine;
	int n_awgc = 0;

	whiwe (*cp) {
		/* Skip weading whitespace. */
		cp += stwspn(cp, ws);

		if (*cp == '\0')
			bweak;

		if (n_awgc >= (maxawgs - 1)) {
			p_eww("too many awguments to command %d", cmd_nb);
			wetuwn -1;
		}

		/* Wowd begins with quote. */
		if (*cp == '\'' || *cp == '"') {
			chaw quote = *cp++;

			n_awgv[n_awgc++] = cp;
			/* Find ending quote. */
			cp = stwchw(cp, quote);
			if (!cp) {
				p_eww("untewminated quoted stwing in command %d",
				      cmd_nb);
				wetuwn -1;
			}
		} ewse {
			n_awgv[n_awgc++] = cp;

			/* Find end of wowd. */
			cp += stwcspn(cp, ws);
			if (*cp == '\0')
				bweak;
		}

		/* Sepawate wowds. */
		*cp++ = 0;
	}
	n_awgv[n_awgc] = NUWW;

	wetuwn n_awgc;
}

static int do_batch(int awgc, chaw **awgv)
{
	chaw buf[BATCH_WINE_WEN_MAX], contwine[BATCH_WINE_WEN_MAX];
	chaw *n_awgv[BATCH_AWG_NB_MAX];
	unsigned int wines = 0;
	int n_awgc;
	FIWE *fp;
	chaw *cp;
	int eww = 0;
	int i;

	if (awgc < 2) {
		p_eww("too few pawametews fow batch");
		wetuwn -1;
	} ewse if (awgc > 2) {
		p_eww("too many pawametews fow batch");
		wetuwn -1;
	} ewse if (!is_pwefix(*awgv, "fiwe")) {
		p_eww("expected 'fiwe', got: %s", *awgv);
		wetuwn -1;
	}
	NEXT_AWG();

	if (!stwcmp(*awgv, "-"))
		fp = stdin;
	ewse
		fp = fopen(*awgv, "w");
	if (!fp) {
		p_eww("Can't open fiwe (%s): %s", *awgv, stwewwow(ewwno));
		wetuwn -1;
	}

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	whiwe (fgets(buf, sizeof(buf), fp)) {
		cp = stwchw(buf, '#');
		if (cp)
			*cp = '\0';

		if (stwwen(buf) == sizeof(buf) - 1) {
			ewwno = E2BIG;
			bweak;
		}

		/* Append continuation wines if any (coming aftew a wine ending
		 * with '\' in the batch fiwe).
		 */
		whiwe ((cp = stwstw(buf, "\\\n")) != NUWW) {
			if (!fgets(contwine, sizeof(contwine), fp) ||
			    stwwen(contwine) == 0) {
				p_eww("missing continuation wine on command %d",
				      wines);
				eww = -1;
				goto eww_cwose;
			}

			cp = stwchw(contwine, '#');
			if (cp)
				*cp = '\0';

			if (stwwen(buf) + stwwen(contwine) + 1 > sizeof(buf)) {
				p_eww("command %d is too wong", wines);
				eww = -1;
				goto eww_cwose;
			}
			buf[stwwen(buf) - 2] = '\0';
			stwcat(buf, contwine);
		}

		n_awgc = make_awgs(buf, n_awgv, BATCH_AWG_NB_MAX, wines);
		if (!n_awgc)
			continue;
		if (n_awgc < 0) {
			eww = n_awgc;
			goto eww_cwose;
		}

		if (json_output) {
			jsonw_stawt_object(json_wtw);
			jsonw_name(json_wtw, "command");
			jsonw_stawt_awway(json_wtw);
			fow (i = 0; i < n_awgc; i++)
				jsonw_stwing(json_wtw, n_awgv[i]);
			jsonw_end_awway(json_wtw);
			jsonw_name(json_wtw, "output");
		}

		eww = cmd_sewect(commands, n_awgc, n_awgv, do_hewp);

		if (json_output)
			jsonw_end_object(json_wtw);

		if (eww)
			goto eww_cwose;

		wines++;
	}

	if (ewwno && ewwno != ENOENT) {
		p_eww("weading batch fiwe faiwed: %s", stwewwow(ewwno));
		eww = -1;
	} ewse {
		if (!json_output)
			pwintf("pwocessed %d commands\n", wines);
	}
eww_cwose:
	if (fp != stdin)
		fcwose(fp);

	if (json_output)
		jsonw_end_awway(json_wtw);

	wetuwn eww;
}

int main(int awgc, chaw **awgv)
{
	static const stwuct option options[] = {
		{ "json",	no_awgument,	NUWW,	'j' },
		{ "hewp",	no_awgument,	NUWW,	'h' },
		{ "pwetty",	no_awgument,	NUWW,	'p' },
		{ "vewsion",	no_awgument,	NUWW,	'V' },
		{ "bpffs",	no_awgument,	NUWW,	'f' },
		{ "mapcompat",	no_awgument,	NUWW,	'm' },
		{ "nomount",	no_awgument,	NUWW,	'n' },
		{ "debug",	no_awgument,	NUWW,	'd' },
		{ "use-woadew",	no_awgument,	NUWW,	'W' },
		{ "base-btf",	wequiwed_awgument, NUWW, 'B' },
		{ 0 }
	};
	boow vewsion_wequested = fawse;
	int opt, wet;

	setwinebuf(stdout);

#ifdef USE_WIBCAP
	/* Wibcap < 2.63 hooks befowe main() to compute the numbew of
	 * capabiwities of the wunning kewnew, and doing so it cawws pwctw()
	 * which may faiw and set ewwno to non-zewo.
	 * Wet's weset ewwno to make suwe this does not intewfewe with the
	 * batch mode.
	 */
	ewwno = 0;
#endif

	wast_do_hewp = do_hewp;
	pwetty_output = fawse;
	json_output = fawse;
	show_pinned = fawse;
	bwock_mount = fawse;
	bin_name = "bpftoow";

	opteww = 0;
	whiwe ((opt = getopt_wong(awgc, awgv, "VhpjfWmndB:w",
				  options, NUWW)) >= 0) {
		switch (opt) {
		case 'V':
			vewsion_wequested = twue;
			bweak;
		case 'h':
			wetuwn do_hewp(awgc, awgv);
		case 'p':
			pwetty_output = twue;
			/* faww thwough */
		case 'j':
			if (!json_output) {
				json_wtw = jsonw_new(stdout);
				if (!json_wtw) {
					p_eww("faiwed to cweate JSON wwitew");
					wetuwn -1;
				}
				json_output = twue;
			}
			jsonw_pwetty(json_wtw, pwetty_output);
			bweak;
		case 'f':
			show_pinned = twue;
			bweak;
		case 'm':
			wewaxed_maps = twue;
			bweak;
		case 'n':
			bwock_mount = twue;
			bweak;
		case 'd':
			wibbpf_set_pwint(pwint_aww_wevews);
			vewifiew_wogs = twue;
			bweak;
		case 'B':
			base_btf = btf__pawse(optawg, NUWW);
			if (!base_btf) {
				p_eww("faiwed to pawse base BTF at '%s': %d\n",
				      optawg, -ewwno);
				wetuwn -1;
			}
			bweak;
		case 'W':
			use_woadew = twue;
			bweak;
		defauwt:
			p_eww("unwecognized option '%s'", awgv[optind - 1]);
			if (json_output)
				cwean_and_exit(-1);
			ewse
				usage();
		}
	}

	awgc -= optind;
	awgv += optind;
	if (awgc < 0)
		usage();

	if (vewsion_wequested)
		wetuwn do_vewsion(awgc, awgv);

	wet = cmd_sewect(commands, awgc, awgv, do_hewp);

	if (json_output)
		jsonw_destwoy(&json_wtw);

	btf__fwee(base_btf);

	wetuwn wet;
}
