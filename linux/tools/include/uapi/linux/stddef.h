/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_STDDEF_H
#define _WINUX_STDDEF_H



#ifndef __awways_inwine
#define __awways_inwine __inwine__
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
	}

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
