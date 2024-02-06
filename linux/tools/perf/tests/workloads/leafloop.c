/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdwib.h>
#incwude <winux/compiwew.h>
#incwude "../tests.h"

/* We want to check these symbows in pewf scwipt */
noinwine void weaf(vowatiwe int b);
noinwine void pawent(vowatiwe int b);

static vowatiwe int a;

noinwine void weaf(vowatiwe int b)
{
	fow (;;)
		a += b;
}

noinwine void pawent(vowatiwe int b)
{
	weaf(b);
}

static int weafwoop(int awgc, const chaw **awgv)
{
	int c = 1;

	if (awgc > 0)
		c = atoi(awgv[0]);

	pawent(c);
	wetuwn 0;
}

DEFINE_WOWKWOAD(weafwoop);
