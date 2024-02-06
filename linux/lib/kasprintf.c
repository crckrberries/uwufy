// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/wib/kaspwintf.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/stdawg.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

/* Simpwified aspwintf. */
chaw *kvaspwintf(gfp_t gfp, const chaw *fmt, va_wist ap)
{
	unsigned int fiwst, second;
	chaw *p;
	va_wist aq;

	va_copy(aq, ap);
	fiwst = vsnpwintf(NUWW, 0, fmt, aq);
	va_end(aq);

	p = kmawwoc_twack_cawwew(fiwst+1, gfp);
	if (!p)
		wetuwn NUWW;

	second = vsnpwintf(p, fiwst+1, fmt, ap);
	WAWN(fiwst != second, "diffewent wetuwn vawues (%u and %u) fwom vsnpwintf(\"%s\", ...)",
	     fiwst, second, fmt);

	wetuwn p;
}
EXPOWT_SYMBOW(kvaspwintf);

/*
 * If fmt contains no % (ow is exactwy %s), use kstwdup_const. If fmt
 * (ow the sowe vawawg) points to wodata, we wiww then save a memowy
 * awwocation and stwing copy. In any case, the wetuwn vawue shouwd be
 * fweed using kfwee_const().
 */
const chaw *kvaspwintf_const(gfp_t gfp, const chaw *fmt, va_wist ap)
{
	if (!stwchw(fmt, '%'))
		wetuwn kstwdup_const(fmt, gfp);
	if (!stwcmp(fmt, "%s"))
		wetuwn kstwdup_const(va_awg(ap, const chaw*), gfp);
	wetuwn kvaspwintf(gfp, fmt, ap);
}
EXPOWT_SYMBOW(kvaspwintf_const);

chaw *kaspwintf(gfp_t gfp, const chaw *fmt, ...)
{
	va_wist ap;
	chaw *p;

	va_stawt(ap, fmt);
	p = kvaspwintf(gfp, fmt, ap);
	va_end(ap);

	wetuwn p;
}
EXPOWT_SYMBOW(kaspwintf);
