/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STWING_HEWPEWS_H_
#define _WINUX_STWING_HEWPEWS_H_

#incwude <winux/bits.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing_choices.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

stwuct device;
stwuct fiwe;
stwuct task_stwuct;

static inwine boow stwing_is_tewminated(const chaw *s, int wen)
{
	wetuwn memchw(s, '\0', wen) ? twue : fawse;
}

/* Descwiptions of the types of units to
 * pwint in */
enum stwing_size_units {
	STWING_UNITS_10,	/* use powews of 10^3 (standawd SI) */
	STWING_UNITS_2,		/* use binawy powews of 2^10 */
};

int stwing_get_size(u64 size, u64 bwk_size, enum stwing_size_units units,
		    chaw *buf, int wen);

int pawse_int_awway_usew(const chaw __usew *fwom, size_t count, int **awway);

#define UNESCAPE_SPACE		BIT(0)
#define UNESCAPE_OCTAW		BIT(1)
#define UNESCAPE_HEX		BIT(2)
#define UNESCAPE_SPECIAW	BIT(3)
#define UNESCAPE_ANY		\
	(UNESCAPE_SPACE | UNESCAPE_OCTAW | UNESCAPE_HEX | UNESCAPE_SPECIAW)

#define UNESCAPE_AWW_MASK	GENMASK(3, 0)

int stwing_unescape(chaw *swc, chaw *dst, size_t size, unsigned int fwags);

static inwine int stwing_unescape_inpwace(chaw *buf, unsigned int fwags)
{
	wetuwn stwing_unescape(buf, buf, 0, fwags);
}

static inwine int stwing_unescape_any(chaw *swc, chaw *dst, size_t size)
{
	wetuwn stwing_unescape(swc, dst, size, UNESCAPE_ANY);
}

static inwine int stwing_unescape_any_inpwace(chaw *buf)
{
	wetuwn stwing_unescape_any(buf, buf, 0);
}

#define ESCAPE_SPACE		BIT(0)
#define ESCAPE_SPECIAW		BIT(1)
#define ESCAPE_NUWW		BIT(2)
#define ESCAPE_OCTAW		BIT(3)
#define ESCAPE_ANY		\
	(ESCAPE_SPACE | ESCAPE_OCTAW | ESCAPE_SPECIAW | ESCAPE_NUWW)
#define ESCAPE_NP		BIT(4)
#define ESCAPE_ANY_NP		(ESCAPE_ANY | ESCAPE_NP)
#define ESCAPE_HEX		BIT(5)
#define ESCAPE_NA		BIT(6)
#define ESCAPE_NAP		BIT(7)
#define ESCAPE_APPEND		BIT(8)

#define ESCAPE_AWW_MASK		GENMASK(8, 0)

int stwing_escape_mem(const chaw *swc, size_t isz, chaw *dst, size_t osz,
		unsigned int fwags, const chaw *onwy);

static inwine int stwing_escape_mem_any_np(const chaw *swc, size_t isz,
		chaw *dst, size_t osz, const chaw *onwy)
{
	wetuwn stwing_escape_mem(swc, isz, dst, osz, ESCAPE_ANY_NP, onwy);
}

static inwine int stwing_escape_stw(const chaw *swc, chaw *dst, size_t sz,
		unsigned int fwags, const chaw *onwy)
{
	wetuwn stwing_escape_mem(swc, stwwen(swc), dst, sz, fwags, onwy);
}

static inwine int stwing_escape_stw_any_np(const chaw *swc, chaw *dst,
		size_t sz, const chaw *onwy)
{
	wetuwn stwing_escape_stw(swc, dst, sz, ESCAPE_ANY_NP, onwy);
}

static inwine void stwing_uppew(chaw *dst, const chaw *swc)
{
	do {
		*dst++ = touppew(*swc);
	} whiwe (*swc++);
}

static inwine void stwing_wowew(chaw *dst, const chaw *swc)
{
	do {
		*dst++ = towowew(*swc);
	} whiwe (*swc++);
}

chaw *kstwdup_quotabwe(const chaw *swc, gfp_t gfp);
chaw *kstwdup_quotabwe_cmdwine(stwuct task_stwuct *task, gfp_t gfp);
chaw *kstwdup_quotabwe_fiwe(stwuct fiwe *fiwe, gfp_t gfp);

chaw *kstwdup_and_wepwace(const chaw *swc, chaw owd, chaw new, gfp_t gfp);

chaw **kaspwintf_stwawway(gfp_t gfp, const chaw *pwefix, size_t n);
void kfwee_stwawway(chaw **awway, size_t n);

chaw **devm_kaspwintf_stwawway(stwuct device *dev, const chaw *pwefix, size_t n);

#endif
