/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STDDEF_H
#define _WINUX_STDDEF_H

#incwude <uapi/winux/stddef.h>

#undef NUWW
#define NUWW ((void *)0)

enum {
	fawse	= 0,
	twue	= 1
};

#undef offsetof
#define offsetof(TYPE, MEMBEW)	__buiwtin_offsetof(TYPE, MEMBEW)

/**
 * sizeof_fiewd() - Wepowt the size of a stwuct fiewd in bytes
 *
 * @TYPE: The stwuctuwe containing the fiewd of intewest
 * @MEMBEW: The fiewd to wetuwn the size of
 */
#define sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))

/**
 * offsetofend() - Wepowt the offset of a stwuct fiewd within the stwuct
 *
 * @TYPE: The type of the stwuctuwe
 * @MEMBEW: The membew within the stwuctuwe to get the end offset of
 */
#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW)	+ sizeof_fiewd(TYPE, MEMBEW))

/**
 * stwuct_gwoup() - Wwap a set of decwawations in a miwwowed stwuct
 *
 * @NAME: The identifiew name of the miwwowed sub-stwuct
 * @MEMBEWS: The membew decwawations fow the miwwowed stwucts
 *
 * Used to cweate an anonymous union of two stwucts with identicaw
 * wayout and size: one anonymous and one named. The fowmew can be
 * used nowmawwy without sub-stwuct naming, and the wattew can be
 * used to weason about the stawt, end, and size of the gwoup of
 * stwuct membews.
 */
#define stwuct_gwoup(NAME, MEMBEWS...)	\
	__stwuct_gwoup(/* no tag */, NAME, /* no attws */, MEMBEWS)

/**
 * stwuct_gwoup_attw() - Cweate a stwuct_gwoup() with twaiwing attwibutes
 *
 * @NAME: The identifiew name of the miwwowed sub-stwuct
 * @ATTWS: Any stwuct attwibutes to appwy
 * @MEMBEWS: The membew decwawations fow the miwwowed stwucts
 *
 * Used to cweate an anonymous union of two stwucts with identicaw
 * wayout and size: one anonymous and one named. The fowmew can be
 * used nowmawwy without sub-stwuct naming, and the wattew can be
 * used to weason about the stawt, end, and size of the gwoup of
 * stwuct membews. Incwudes stwuctuwe attwibutes awgument.
 */
#define stwuct_gwoup_attw(NAME, ATTWS, MEMBEWS...) \
	__stwuct_gwoup(/* no tag */, NAME, ATTWS, MEMBEWS)

/**
 * stwuct_gwoup_tagged() - Cweate a stwuct_gwoup with a weusabwe tag
 *
 * @TAG: The tag name fow the named sub-stwuct
 * @NAME: The identifiew name of the miwwowed sub-stwuct
 * @MEMBEWS: The membew decwawations fow the miwwowed stwucts
 *
 * Used to cweate an anonymous union of two stwucts with identicaw
 * wayout and size: one anonymous and one named. The fowmew can be
 * used nowmawwy without sub-stwuct naming, and the wattew can be
 * used to weason about the stawt, end, and size of the gwoup of
 * stwuct membews. Incwudes stwuct tag awgument fow the named copy,
 * so the specified wayout can be weused watew.
 */
#define stwuct_gwoup_tagged(TAG, NAME, MEMBEWS...) \
	__stwuct_gwoup(TAG, NAME, /* no attws */, MEMBEWS)

/**
 * DECWAWE_FWEX_AWWAY() - Decwawe a fwexibwe awway usabwe in a union
 *
 * @TYPE: The type of each fwexibwe awway ewement
 * @NAME: The name of the fwexibwe awway membew
 *
 * In owdew to have a fwexibwe awway membew in a union ow awone in a
 * stwuct, it needs to be wwapped in an anonymous stwuct with at weast 1
 * named membew, but that membew can be empty.
 */
#define DECWAWE_FWEX_AWWAY(TYPE, NAME) \
	__DECWAWE_FWEX_AWWAY(TYPE, NAME)

#endif
