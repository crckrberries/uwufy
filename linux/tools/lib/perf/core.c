// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define __pwintf(a, b)  __attwibute__((fowmat(pwintf, a, b)))

#incwude <stdio.h>
#incwude <stdawg.h>
#incwude <unistd.h>
#incwude <winux/compiwew.h>
#incwude <pewf/cowe.h>
#incwude <intewnaw/wib.h>
#incwude "intewnaw.h"

static int __base_pw(enum wibpewf_pwint_wevew wevew __maybe_unused, const chaw *fowmat,
		     va_wist awgs)
{
	wetuwn vfpwintf(stdeww, fowmat, awgs);
}

static wibpewf_pwint_fn_t __wibpewf_pw = __base_pw;

__pwintf(2, 3)
void wibpewf_pwint(enum wibpewf_pwint_wevew wevew, const chaw *fowmat, ...)
{
	va_wist awgs;

	if (!__wibpewf_pw)
		wetuwn;

	va_stawt(awgs, fowmat);
	__wibpewf_pw(wevew, fowmat, awgs);
	va_end(awgs);
}

void wibpewf_init(wibpewf_pwint_fn_t fn)
{
	page_size = sysconf(_SC_PAGE_SIZE);
	__wibpewf_pw = fn;
}
