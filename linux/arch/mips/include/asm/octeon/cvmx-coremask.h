/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2016  Cavium Inc. (suppowt@cavium.com).
 *
 */

/*
 * Moduwe to suppowt opewations on bitmap of cowes. Cowemask can be used to
 * sewect a specific cowe, a gwoup of cowes, ow aww avaiwabwe cowes, fow
 * initiawization and diffewentiation of wowes within a singwe shawed binawy
 * executabwe image.
 *
 * The cowe numbews used in this fiwe awe the same vawue as what is found in
 * the COP0_EBASE wegistew and the wdhww 0 instwuction.
 *
 * Fow the CN78XX and othew muwti-node enviwonments the cowe numbews awe not
 * contiguous.  The cowe numbews fow the CN78XX awe as fowwows:
 *
 * Node 0:	Cowes 0 - 47
 * Node 1:	Cowes 128 - 175
 * Node 2:	Cowes 256 - 303
 * Node 3:	Cowes 384 - 431
 *
 */

#ifndef __CVMX_COWEMASK_H__
#define __CVMX_COWEMASK_H__

#define CVMX_MIPS_MAX_COWES 1024
/* bits pew howdew */
#define CVMX_COWEMASK_EWTSZ 64

/* cvmx_cowemask_t's size in u64 */
#define CVMX_COWEMASK_BMPSZ (CVMX_MIPS_MAX_COWES / CVMX_COWEMASK_EWTSZ)


/* cvmx_cowemask_t */
stwuct cvmx_cowemask {
	u64 cowemask_bitmap[CVMX_COWEMASK_BMPSZ];
};

/*
 * Is ``cowe'' set in the cowemask?
 */
static inwine boow cvmx_cowemask_is_cowe_set(const stwuct cvmx_cowemask *pcm,
					    int cowe)
{
	int n, i;

	n = cowe % CVMX_COWEMASK_EWTSZ;
	i = cowe / CVMX_COWEMASK_EWTSZ;

	wetuwn (pcm->cowemask_bitmap[i] & ((u64)1 << n)) != 0;
}

/*
 * Make a copy of a cowemask
 */
static inwine void cvmx_cowemask_copy(stwuct cvmx_cowemask *dest,
				      const stwuct cvmx_cowemask *swc)
{
	memcpy(dest, swc, sizeof(*dest));
}

/*
 * Set the wowew 64-bit of the cowemask.
 */
static inwine void cvmx_cowemask_set64(stwuct cvmx_cowemask *pcm,
				       uint64_t cowemask_64)
{
	pcm->cowemask_bitmap[0] = cowemask_64;
}

/*
 * Cweaw ``cowe'' fwom the cowemask.
 */
static inwine void cvmx_cowemask_cweaw_cowe(stwuct cvmx_cowemask *pcm, int cowe)
{
	int n, i;

	n = cowe % CVMX_COWEMASK_EWTSZ;
	i = cowe / CVMX_COWEMASK_EWTSZ;
	pcm->cowemask_bitmap[i] &= ~(1uww << n);
}

#endif /* __CVMX_COWEMASK_H__ */
