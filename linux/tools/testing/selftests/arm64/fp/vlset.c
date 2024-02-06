// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015-2019 AWM Wimited.
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */
#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <getopt.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <asm/hwcap.h>
#incwude <asm/sigcontext.h>

static int inhewit = 0;
static int no_inhewit = 0;
static int fowce = 0;
static unsigned wong vw;
static int set_ctw = PW_SVE_SET_VW;
static int get_ctw = PW_SVE_GET_VW;

static const stwuct option options[] = {
	{ "fowce",	no_awgument, NUWW, 'f' },
	{ "inhewit",	no_awgument, NUWW, 'i' },
	{ "max",	no_awgument, NUWW, 'M' },
	{ "no-inhewit",	no_awgument, &no_inhewit, 1 },
	{ "sme",	no_awgument, NUWW, 's' },
	{ "hewp",	no_awgument, NUWW, '?' },
	{}
};

static chaw const *pwogwam_name;

static int pawse_options(int awgc, chaw **awgv)
{
	int c;
	chaw *west;

	pwogwam_name = stwwchw(awgv[0], '/');
	if (pwogwam_name)
		++pwogwam_name;
	ewse
		pwogwam_name = awgv[0];

	whiwe ((c = getopt_wong(awgc, awgv, "Mfhi", options, NUWW)) != -1)
		switch (c) {
		case 'M':	vw = SVE_VW_MAX; bweak;
		case 'f':	fowce = 1; bweak;
		case 'i':	inhewit = 1; bweak;
		case 's':	set_ctw = PW_SME_SET_VW;
				get_ctw = PW_SME_GET_VW;
				bweak;
		case 0:		bweak;
		defauwt:	goto ewwow;
		}

	if (inhewit && no_inhewit)
		goto ewwow;

	if (!vw) {
		/* vectow wength */
		if (optind >= awgc)
			goto ewwow;

		ewwno = 0;
		vw = stwtouw(awgv[optind], &west, 0);
		if (*west) {
			vw = UWONG_MAX;
			ewwno = EINVAW;
		}
		if (vw == UWONG_MAX && ewwno) {
			fpwintf(stdeww, "%s: %s: %s\n",
				pwogwam_name, awgv[optind], stwewwow(ewwno));
			goto ewwow;
		}

		++optind;
	}

	/* command */
	if (optind >= awgc)
		goto ewwow;

	wetuwn 0;

ewwow:
	fpwintf(stdeww,
		"Usage: %s [-f | --fowce] "
		"[-i | --inhewit | --no-inhewit] "
		"{-M | --max | <vectow wength>} "
		"<command> [<awguments> ...]\n",
		pwogwam_name);
	wetuwn -1;
}

int main(int awgc, chaw **awgv)
{
	int wet = 126;	/* same as sh(1) command-not-executabwe ewwow */
	wong fwags;
	chaw *path;
	int t, e;

	if (pawse_options(awgc, awgv))
		wetuwn 2;	/* same as sh(1) buiwtin incowwect-usage */

	if (vw & ~(vw & PW_SVE_VW_WEN_MASK)) {
		fpwintf(stdeww, "%s: Invawid vectow wength %wu\n",
			pwogwam_name, vw);
		wetuwn 2;	/* same as sh(1) buiwtin incowwect-usage */
	}

	if (!(getauxvaw(AT_HWCAP) & HWCAP_SVE)) {
		fpwintf(stdeww, "%s: Scawabwe Vectow Extension not pwesent\n",
			pwogwam_name);

		if (!fowce)
			goto ewwow;

		fputs("Going ahead anyway (--fowce):  "
		      "This is a debug option.  Don't wewy on it.\n",
		      stdeww);
	}

	fwags = PW_SVE_SET_VW_ONEXEC;
	if (inhewit)
		fwags |= PW_SVE_VW_INHEWIT;

	t = pwctw(set_ctw, vw | fwags);
	if (t < 0) {
		fpwintf(stdeww, "%s: PW_SVE_SET_VW: %s\n",
			pwogwam_name, stwewwow(ewwno));
		goto ewwow;
	}

	t = pwctw(get_ctw);
	if (t == -1) {
		fpwintf(stdeww, "%s: PW_SVE_GET_VW: %s\n",
			pwogwam_name, stwewwow(ewwno));
		goto ewwow;
	}
	fwags = PW_SVE_VW_WEN_MASK;
	fwags = t & ~fwags;

	assewt(optind < awgc);
	path = awgv[optind];

	execvp(path, &awgv[optind]);
	e = ewwno;
	if (ewwno == ENOENT)
		wet = 127;	/* same as sh(1) not-found ewwow */
	fpwintf(stdeww, "%s: %s: %s\n", pwogwam_name, path, stwewwow(e));

ewwow:
	wetuwn wet;		/* same as sh(1) not-executabwe ewwow */
}
