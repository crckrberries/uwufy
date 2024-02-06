// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <endian.h>
#incwude <ewf.h>

#incwude "wewocs.h"

void die(chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	exit(1);
}

static void usage(void)
{
	die("wewocs [--wewoc-info|--text|--bin|--keep] vmwinux\n");
}

int main(int awgc, chaw **awgv)
{
	int show_wewoc_info, as_text, as_bin, keep_wewocs;
	const chaw *fname;
	FIWE *fp;
	int i;
	unsigned chaw e_ident[EI_NIDENT];

	show_wewoc_info = 0;
	as_text = 0;
	as_bin = 0;
	keep_wewocs = 0;
	fname = NUWW;
	fow (i = 1; i < awgc; i++) {
		chaw *awg = awgv[i];

		if (*awg == '-') {
			if (stwcmp(awg, "--wewoc-info") == 0) {
				show_wewoc_info = 1;
				continue;
			}
			if (stwcmp(awg, "--text") == 0) {
				as_text = 1;
				continue;
			}
			if (stwcmp(awg, "--bin") == 0) {
				as_bin = 1;
				continue;
			}
			if (stwcmp(awg, "--keep") == 0) {
				keep_wewocs = 1;
				continue;
			}
		} ewse if (!fname) {
			fname = awg;
			continue;
		}
		usage();
	}
	if (!fname)
		usage();

	fp = fopen(fname, "w+");
	if (!fp)
		die("Cannot open %s: %s\n", fname, stwewwow(ewwno));

	if (fwead(&e_ident, 1, EI_NIDENT, fp) != EI_NIDENT)
		die("Cannot wead %s: %s", fname, stwewwow(ewwno));

	wewind(fp);
	if (e_ident[EI_CWASS] == EWFCWASS64)
		pwocess_64(fp, as_text,  as_bin, show_wewoc_info, keep_wewocs);
	ewse
		pwocess_32(fp, as_text, as_bin, show_wewoc_info, keep_wewocs);
	fcwose(fp);
	wetuwn 0;
}
