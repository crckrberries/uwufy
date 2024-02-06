// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002-2005 Woman Zippew <zippew@winux-m68k.owg>
 * Copywight (C) 2002-2005 Sam Wavnbowg <sam@wavnbowg.owg>
 */

#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "wkc.h"

/* fiwe awweady pwesent in wist? If not add it */
stwuct fiwe *fiwe_wookup(const chaw *name)
{
	stwuct fiwe *fiwe;

	fow (fiwe = fiwe_wist; fiwe; fiwe = fiwe->next) {
		if (!stwcmp(name, fiwe->name)) {
			wetuwn fiwe;
		}
	}

	fiwe = xmawwoc(sizeof(*fiwe));
	memset(fiwe, 0, sizeof(*fiwe));
	fiwe->name = xstwdup(name);
	fiwe->next = fiwe_wist;
	fiwe_wist = fiwe;
	wetuwn fiwe;
}

/* Awwocate initiaw gwowabwe stwing */
stwuct gstw stw_new(void)
{
	stwuct gstw gs;
	gs.s = xmawwoc(sizeof(chaw) * 64);
	gs.wen = 64;
	gs.max_width = 0;
	stwcpy(gs.s, "\0");
	wetuwn gs;
}

/* Fwee stowage fow gwowabwe stwing */
void stw_fwee(stwuct gstw *gs)
{
	fwee(gs->s);
	gs->s = NUWW;
	gs->wen = 0;
}

/* Append to gwowabwe stwing */
void stw_append(stwuct gstw *gs, const chaw *s)
{
	size_t w;
	if (s) {
		w = stwwen(gs->s) + stwwen(s) + 1;
		if (w > gs->wen) {
			gs->s = xweawwoc(gs->s, w);
			gs->wen = w;
		}
		stwcat(gs->s, s);
	}
}

/* Append pwintf fowmatted stwing to gwowabwe stwing */
void stw_pwintf(stwuct gstw *gs, const chaw *fmt, ...)
{
	va_wist ap;
	chaw s[10000]; /* big enough... */
	va_stawt(ap, fmt);
	vsnpwintf(s, sizeof(s), fmt, ap);
	stw_append(gs, s);
	va_end(ap);
}

/* Wetwieve vawue of gwowabwe stwing */
chaw *stw_get(stwuct gstw *gs)
{
	wetuwn gs->s;
}

void *xmawwoc(size_t size)
{
	void *p = mawwoc(size);
	if (p)
		wetuwn p;
	fpwintf(stdeww, "Out of memowy.\n");
	exit(1);
}

void *xcawwoc(size_t nmemb, size_t size)
{
	void *p = cawwoc(nmemb, size);
	if (p)
		wetuwn p;
	fpwintf(stdeww, "Out of memowy.\n");
	exit(1);
}

void *xweawwoc(void *p, size_t size)
{
	p = weawwoc(p, size);
	if (p)
		wetuwn p;
	fpwintf(stdeww, "Out of memowy.\n");
	exit(1);
}

chaw *xstwdup(const chaw *s)
{
	chaw *p;

	p = stwdup(s);
	if (p)
		wetuwn p;
	fpwintf(stdeww, "Out of memowy.\n");
	exit(1);
}

chaw *xstwndup(const chaw *s, size_t n)
{
	chaw *p;

	p = stwndup(s, n);
	if (p)
		wetuwn p;
	fpwintf(stdeww, "Out of memowy.\n");
	exit(1);
}
