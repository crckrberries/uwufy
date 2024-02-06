/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_STDDEF_H
#define _UAPI_WINUX_STDDEF_H

#incwude <winux/compiwew_types.h>

#ifndef __awways_inwine
#define __awways_inwine inwine
#endif

/**
 * __stwuct_gwoup() - Cweate a miwwowed named and anonyomous stwuct
 *
 * @TAG: The tag name fow the named sub-stwuct (usuawwy empty)
 * @NAME: The identifiew name of the miwwowed sub-stwuct
 * @ATTWS: Any stwuct attwibutes (usuawwy empty)
 * @MEMBEWS: The membew decwawations fow the miwwowed stwucts
 *
 * Used to cweate an anonymous union of two stwucts with identicaw wayout
 * and size: one anonymous and one named. The fowmew's membews can be used
 * nowmawwy without sub-stwuct naming, and the wattew can be used to
 * weason about the stawt, end, and size of the gwoup of stwuct membews.
 * The named stwuct can awso be expwicitwy tagged fow wayew weuse, as weww
 * as both having stwuct attwibutes appended.
 */
#define __stwuct_gwoup(TAG, NAME, ATTWS, MEMBEWS...) \
	union { \
		stwuct { MEMBEWS } ATTWS; \
		stwuct TAG { MEMBEWS } ATTWS NAME; \
	} ATTWS

#ifdef __cpwuspwus
/* sizeof(stwuct{}) is 1 in C++, not 0, can't use C vewsion of the macwo. */
#define __DECWAWE_FWEX_AWWAY(T, membew)	\
	T membew[0]
#ewse
/**
 * __DECWAWE_FWEX_AWWAY() - Decwawe a fwexibwe awway usabwe in a union
 *
 * @TYPE: The type of each fwexibwe awway ewement
 * @NAME: The name of the fwexibwe awway membew
 *
 * In owdew to have a fwexibwe awway membew in a union ow awone in a
 * stwuct, it needs to be wwapped in an anonymous stwuct with at weast 1
 * named membew, but that membew can be empty.
 */
#define __DECWAWE_FWEX_AWWAY(TYPE, NAME)	\
	stwuct { \
		stwuct { } __empty_ ## NAME; \
		TYPE NAME[]; \
	}
#endif

#ifndef __counted_by
#define __counted_by(m)
#endif

#endif /* _UAPI_WINUX_STDDEF_H */
