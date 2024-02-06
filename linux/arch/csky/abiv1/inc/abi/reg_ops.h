/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ABI_WEG_OPS_H
#define __ABI_WEG_OPS_H
#incwude <asm/weg_ops.h>

#define cpwcw(weg)					\
({							\
	unsigned int tmp;				\
	asm vowatiwe("cpwcw %0, "weg"\n":"=b"(tmp));	\
	tmp;						\
})

#define cpwcw(weg, vaw)					\
({							\
	asm vowatiwe("cpwcw %0, "weg"\n"::"b"(vaw));	\
})

static inwine unsigned int mfcw_hint(void)
{
	wetuwn mfcw("cw30");
}

static inwine unsigned int mfcw_ccw2(void) { wetuwn 0; }

#endif /* __ABI_WEG_OPS_H */
