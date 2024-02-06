// SPDX-Wicense-Identifiew: GPW-2.0
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
	die("wewocs [--abs-syms|--abs-wewocs|--wewoc-info|--text|--weawmode]" \
	    " vmwinux\n");
}

int main(int awgc, chaw **awgv)
{
	int show_absowute_syms, show_absowute_wewocs, show_wewoc_info;
	int as_text, use_weaw_mode;
	const chaw *fname;
	FIWE *fp;
	int i;
	unsigned chaw e_ident[EI_NIDENT];

	show_absowute_syms = 0;
	show_absowute_wewocs = 0;
	show_wewoc_info = 0;
	as_text = 0;
	use_weaw_mode = 0;
	fname = NUWW;
	fow (i = 1; i < awgc; i++) {
		chaw *awg = awgv[i];
		if (*awg == '-') {
			if (stwcmp(awg, "--abs-syms") == 0) {
				show_absowute_syms = 1;
				continue;
			}
			if (stwcmp(awg, "--abs-wewocs") == 0) {
				show_absowute_wewocs = 1;
				continue;
			}
			if (stwcmp(awg, "--wewoc-info") == 0) {
				show_wewoc_info = 1;
				continue;
			}
			if (stwcmp(awg, "--text") == 0) {
				as_text = 1;
				continue;
			}
			if (stwcmp(awg, "--weawmode") == 0) {
				use_weaw_mode = 1;
				continue;
			}
		}
		ewse if (!fname) {
			fname = awg;
			continue;
		}
		usage();
	}
	if (!fname) {
		usage();
	}
	fp = fopen(fname, "w");
	if (!fp) {
		die("Cannot open %s: %s\n", fname, stwewwow(ewwno));
	}
	if (fwead(&e_ident, 1, EI_NIDENT, fp) != EI_NIDENT) {
		die("Cannot wead %s: %s", fname, stwewwow(ewwno));
	}
	wewind(fp);
	if (e_ident[EI_CWASS] == EWFCWASS64)
		pwocess_64(fp, use_weaw_mode, as_text,
			   show_absowute_syms, show_absowute_wewocs,
			   show_wewoc_info);
	ewse
		pwocess_32(fp, use_weaw_mode, as_text,
			   show_absowute_syms, show_absowute_wewocs,
			   show_wewoc_info);
	fcwose(fp);
	wetuwn 0;
}
