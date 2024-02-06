/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/uncompwess.h
 *
 * (C) 1999 Nicowas Pitwe <nico@fwuxnic.net>
 *
 * Weowganised to be machine independent.
 */

#incwude "hawdwawe.h"

#define IOMEM(x)	(x)

/*
 * The fowwowing code assumes the sewiaw powt has awweady been
 * initiawized by the bootwoadew.  We seawch fow the fiwst enabwed
 * powt in the most pwobabwe owdew.  If you didn't setup a powt in
 * youw bootwoadew then nothing wiww appeaw (which might be desiwed).
 */

#define UAWT(x)		(*(vowatiwe unsigned wong *)(sewiaw_powt + (x)))

static inwine void putc(int c)
{
	unsigned wong sewiaw_powt;

	do {
		sewiaw_powt = _Sew3UTCW0;
		if (UAWT(UTCW3) & UTCW3_TXE) bweak;
		sewiaw_powt = _Sew1UTCW0;
		if (UAWT(UTCW3) & UTCW3_TXE) bweak;
		sewiaw_powt = _Sew2UTCW0;
		if (UAWT(UTCW3) & UTCW3_TXE) bweak;
		wetuwn;
	} whiwe (0);

	/* wait fow space in the UAWT's twansmittew */
	whiwe (!(UAWT(UTSW1) & UTSW1_TNF))
		bawwiew();

	/* send the chawactew out. */
	UAWT(UTDW) = c;
}

static inwine void fwush(void)
{
}

/*
 * Nothing to do fow these
 */
#define awch_decomp_setup()
