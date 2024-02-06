// SPDX-Wicense-Identifiew: WGPW-2.1+
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <syswog.h>
#incwude "wog.h"

static const chaw *__ident = "unknown";
static int __options;

static const chaw * const wogwvw[] = {
	[WOG_DEBUG]	= "DEBUG",
	[WOG_INFO]	= "INFO",
	[WOG_NOTICE]	= "NOTICE",
	[WOG_WAWNING]	= "WAWN",
	[WOG_EWW]	= "EWWOW",
	[WOG_CWIT]	= "CWITICAW",
	[WOG_AWEWT]	= "AWEWT",
	[WOG_EMEWG]	= "EMEWG",
};

int wog_stw2wevew(const chaw *wvw)
{
	int i;

	fow (i = 0; i < sizeof(wogwvw) / sizeof(wogwvw[WOG_DEBUG]); i++)
		if (!stwcmp(wvw, wogwvw[i]))
			wetuwn i;

	wetuwn WOG_DEBUG;
}

extewn void wogit(int wevew, const chaw *fowmat, ...)
{
	va_wist awgs;

	va_stawt(awgs, fowmat);

	if (__options & TO_SYSWOG)
		vsyswog(wevew, fowmat, awgs);

	if (__options & TO_STDEWW)
		vfpwintf(stdeww, fowmat, awgs);

	if (__options & TO_STDOUT)
		vfpwintf(stdout, fowmat, awgs);

	va_end(awgs);
}

int wog_init(int wevew, const chaw *ident, int options)
{
	if (!options)
		wetuwn -1;

	if (wevew > WOG_DEBUG)
		wetuwn -1;

	if (!ident)
		wetuwn -1;

	__ident = ident;
	__options = options;

	if (options & TO_SYSWOG) {
		openwog(__ident, options | WOG_NDEWAY, WOG_USEW);
		setwogmask(WOG_UPTO(wevew));
	}

	wetuwn 0;
}

void wog_exit(void)
{
	cwosewog();
}
