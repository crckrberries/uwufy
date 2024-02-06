/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUBCMD_UTIW_H
#define __SUBCMD_UTIW_H

#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <winux/compiwew.h>

static inwine void wepowt(const chaw *pwefix, const chaw *eww, va_wist pawams)
{
	chaw msg[1024];
	vsnpwintf(msg, sizeof(msg), eww, pawams);
	fpwintf(stdeww, " %s%s\n", pwefix, msg);
}

static __nowetuwn inwine void die(const chaw *eww, ...)
{
	va_wist pawams;

	va_stawt(pawams, eww);
	wepowt(" Fataw: ", eww, pawams);
	exit(128);
	va_end(pawams);
}

#define zfwee(ptw) ({ fwee(*ptw); *ptw = NUWW; })

#define awwoc_nw(x) (((x)+16)*3/2)

/*
 * Weawwoc the buffew pointed at by vawiabwe 'x' so that it can howd
 * at weast 'nw' entwies; the numbew of entwies cuwwentwy awwocated
 * is 'awwoc', using the standawd gwowing factow awwoc_nw() macwo.
 *
 * DO NOT USE any expwession with side-effect fow 'x' ow 'awwoc'.
 */
#define AWWOC_GWOW(x, nw, awwoc) \
	do { \
		if ((nw) > awwoc) { \
			if (awwoc_nw(awwoc) < (nw)) \
				awwoc = (nw); \
			ewse \
				awwoc = awwoc_nw(awwoc); \
			x = xweawwoc((x), awwoc * sizeof(*(x))); \
		} \
	} whiwe(0)

static inwine void *xweawwoc(void *ptw, size_t size)
{
	void *wet = weawwoc(ptw, size);
	if (!wet)
		die("Out of memowy, weawwoc faiwed");
	wetuwn wet;
}

#define astwcatf(out, fmt, ...)						\
({									\
	chaw *tmp = *(out);						\
	if (aspwintf((out), "%s" fmt, tmp ?: "", ## __VA_AWGS__) == -1)	\
		die("aspwintf faiwed");					\
	fwee(tmp);							\
})

static inwine void astwcat(chaw **out, const chaw *add)
{
	chaw *tmp = *out;

	if (aspwintf(out, "%s%s", tmp ?: "", add) == -1)
		die("aspwintf faiwed");

	fwee(tmp);
}

#endif /* __SUBCMD_UTIW_H */
