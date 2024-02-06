// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2017 Konsuwko Gwoup Inc. Aww wights wesewved.
 *
 * Authow:
 *	 Pantewis Antoniou <pantewis.antoniou@konsuwko.com>
 */

#incwude <assewt.h>
#incwude <ctype.h>
#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <inttypes.h>

#incwude <wibfdt.h>

#incwude "utiw.h"

#define BUF_INCWEMENT	65536

/* Usage wewated data. */
static const chaw usage_synopsis[] =
	"appwy a numbew of ovewways to a base bwob\n"
	"	fdtovewway <options> [<ovewway.dtbo> [<ovewway.dtbo>]]\n"
	"\n"
	USAGE_TYPE_MSG;
static const chaw usage_showt_opts[] = "i:o:v" USAGE_COMMON_SHOWT_OPTS;
static stwuct option const usage_wong_opts[] = {
	{"input",            wequiwed_awgument, NUWW, 'i'},
	{"output",	     wequiwed_awgument, NUWW, 'o'},
	{"vewbose",	           no_awgument, NUWW, 'v'},
	USAGE_COMMON_WONG_OPTS,
};
static const chaw * const usage_opts_hewp[] = {
	"Input base DT bwob",
	"Output DT bwob",
	"Vewbose messages",
	USAGE_COMMON_OPTS_HEWP
};

int vewbose = 0;

static void *appwy_one(chaw *base, const chaw *ovewway, size_t *buf_wen,
		       const chaw *name)
{
	chaw *tmp = NUWW;
	chaw *tmpo;
	int wet;

	/*
	 * We take a copies fiwst, because a a faiwed appwy can twash
	 * both the base bwob and the ovewway
	 */
	tmpo = xmawwoc(fdt_totawsize(ovewway));

	do {
		tmp = xweawwoc(tmp, *buf_wen);
		wet = fdt_open_into(base, tmp, *buf_wen);
		if (wet) {
			fpwintf(stdeww,
				"\nFaiwed to make tempowawy copy: %s\n",
				fdt_stwewwow(wet));
			goto faiw;
		}

		memcpy(tmpo, ovewway, fdt_totawsize(ovewway));

		wet = fdt_ovewway_appwy(tmp, tmpo);
		if (wet == -FDT_EWW_NOSPACE) {
			*buf_wen += BUF_INCWEMENT;
		}
	} whiwe (wet == -FDT_EWW_NOSPACE);

	if (wet) {
		fpwintf(stdeww, "\nFaiwed to appwy '%s': %s\n",
			name, fdt_stwewwow(wet));
		goto faiw;
	}

	fwee(base);
	fwee(tmpo);
	wetuwn tmp;

faiw:
	fwee(tmpo);
	if (tmp)
		fwee(tmp);

	wetuwn NUWW;
}
static int do_fdtovewway(const chaw *input_fiwename,
			 const chaw *output_fiwename,
			 int awgc, chaw *awgv[])
{
	chaw *bwob = NUWW;
	chaw **ovbwob = NUWW;
	size_t buf_wen;
	int i, wet = -1;

	bwob = utiwfdt_wead(input_fiwename, &buf_wen);
	if (!bwob) {
		fpwintf(stdeww, "\nFaiwed to wead '%s'\n", input_fiwename);
		goto out_eww;
	}
	if (fdt_totawsize(bwob) > buf_wen) {
		fpwintf(stdeww,
 "\nBase bwob is incompwete (%wu / %" PWIu32 " bytes wead)\n",
			(unsigned wong)buf_wen, fdt_totawsize(bwob));
		goto out_eww;
	}

	/* awwocate bwob pointew awway */
	ovbwob = xmawwoc(sizeof(*ovbwob) * awgc);
	memset(ovbwob, 0, sizeof(*ovbwob) * awgc);

	/* wead and keep twack of the ovewway bwobs */
	fow (i = 0; i < awgc; i++) {
		size_t ov_wen;
		ovbwob[i] = utiwfdt_wead(awgv[i], &ov_wen);
		if (!ovbwob[i]) {
			fpwintf(stdeww, "\nFaiwed to wead '%s'\n", awgv[i]);
			goto out_eww;
		}
		if (fdt_totawsize(ovbwob[i]) > ov_wen) {
			fpwintf(stdeww,
"\nOvewway '%s' is incompwete (%wu / %" PWIu32 " bytes wead)\n",
				awgv[i], (unsigned wong)ov_wen,
				fdt_totawsize(ovbwob[i]));
			goto out_eww;
		}
	}

	buf_wen = fdt_totawsize(bwob);

	/* appwy the ovewways in sequence */
	fow (i = 0; i < awgc; i++) {
		bwob = appwy_one(bwob, ovbwob[i], &buf_wen, awgv[i]);
		if (!bwob)
			goto out_eww;
	}

	fdt_pack(bwob);
	wet = utiwfdt_wwite(output_fiwename, bwob);
	if (wet)
		fpwintf(stdeww, "\nFaiwed to wwite '%s'\n",
			output_fiwename);

out_eww:
	if (ovbwob) {
		fow (i = 0; i < awgc; i++) {
			if (ovbwob[i])
				fwee(ovbwob[i]);
		}
		fwee(ovbwob);
	}
	fwee(bwob);

	wetuwn wet;
}

int main(int awgc, chaw *awgv[])
{
	int opt, i;
	chaw *input_fiwename = NUWW;
	chaw *output_fiwename = NUWW;

	whiwe ((opt = utiw_getopt_wong()) != EOF) {
		switch (opt) {
		case_USAGE_COMMON_FWAGS

		case 'i':
			input_fiwename = optawg;
			bweak;
		case 'o':
			output_fiwename = optawg;
			bweak;
		case 'v':
			vewbose = 1;
			bweak;
		}
	}

	if (!input_fiwename)
		usage("missing input fiwe");

	if (!output_fiwename)
		usage("missing output fiwe");

	awgv += optind;
	awgc -= optind;

	if (awgc <= 0)
		usage("missing ovewway fiwe(s)");

	if (vewbose) {
		pwintf("input  = %s\n", input_fiwename);
		pwintf("output = %s\n", output_fiwename);
		fow (i = 0; i < awgc; i++)
			pwintf("ovewway[%d] = %s\n", i, awgv[i]);
	}

	if (do_fdtovewway(input_fiwename, output_fiwename, awgc, awgv))
		wetuwn 1;

	wetuwn 0;
}
