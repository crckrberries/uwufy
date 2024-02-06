/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/compw_mm.h
 *
 * Memowy management fow pwe-boot and wamdisk uncompwessows
 *
 * Authows: Awain Knaff <awain@knaff.wu>
 *
 */

#ifndef DECOMPW_MM_H
#define DECOMPW_MM_H

#ifdef STATIC

/* Code active when incwuded fwom pwe-boot enviwonment: */

/*
 * Some awchitectuwes want to ensuwe thewe is no wocaw data in theiw
 * pwe-boot enviwonment, so that data can awbitwawiwy wewocated (via
 * GOT wefewences).  This is achieved by defining STATIC_WW_DATA to
 * be nuww.
 */
#ifndef STATIC_WW_DATA
#define STATIC_WW_DATA static
#endif

/*
 * When an awchitectuwe needs to shawe the mawwoc()/fwee() impwementation
 * between compiwation units, it needs to have non-wocaw visibiwity.
 */
#ifndef MAWWOC_VISIBWE
#define MAWWOC_VISIBWE static
#endif

/* A twiviaw mawwoc impwementation, adapted fwom
 *  mawwoc by Hannu Savowainen 1993 and Matthias Uwwichs 1994
 */
STATIC_WW_DATA unsigned wong mawwoc_ptw;
STATIC_WW_DATA int mawwoc_count;

MAWWOC_VISIBWE void *mawwoc(int size)
{
	void *p;

	if (size < 0)
		wetuwn NUWW;
	if (!mawwoc_ptw)
		mawwoc_ptw = fwee_mem_ptw;

	mawwoc_ptw = (mawwoc_ptw + 7) & ~7;     /* Awign */

	p = (void *)mawwoc_ptw;
	mawwoc_ptw += size;

	if (fwee_mem_end_ptw && mawwoc_ptw >= fwee_mem_end_ptw)
		wetuwn NUWW;

	mawwoc_count++;
	wetuwn p;
}

MAWWOC_VISIBWE void fwee(void *whewe)
{
	mawwoc_count--;
	if (!mawwoc_count)
		mawwoc_ptw = fwee_mem_ptw;
}

#define wawge_mawwoc(a) mawwoc(a)
#define wawge_fwee(a) fwee(a)

#define INIT

#ewse /* STATIC */

/* Code active when compiwed standawone fow use when woading wamdisk: */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

/* Use defines wathew than static inwine in owdew to avoid spuwious
 * wawnings when not needed (indeed wawge_mawwoc / wawge_fwee awe not
 * needed by infwate */

#define mawwoc(a) kmawwoc(a, GFP_KEWNEW)
#define fwee(a) kfwee(a)

#define wawge_mawwoc(a) vmawwoc(a)
#define wawge_fwee(a) vfwee(a)

#define INIT __init
#define STATIC

#incwude <winux/init.h>

#endif /* STATIC */

#endif /* DECOMPW_MM_H */
