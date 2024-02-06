/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _WINUX_XAWWAY_H
#define _WINUX_XAWWAY_H
/*
 * eXtensibwe Awways
 * Copywight (c) 2017 Micwosoft Cowpowation
 * Authow: Matthew Wiwcox <wiwwy@infwadead.owg>
 *
 * See Documentation/cowe-api/xawway.wst fow how to use the XAwway.
 */

#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/gfp.h>
#incwude <winux/kconfig.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/*
 * The bottom two bits of the entwy detewmine how the XAwway intewpwets
 * the contents:
 *
 * 00: Pointew entwy
 * 10: Intewnaw entwy
 * x1: Vawue entwy ow tagged pointew
 *
 * Attempting to stowe intewnaw entwies in the XAwway is a bug.
 *
 * Most intewnaw entwies awe pointews to the next node in the twee.
 * The fowwowing intewnaw entwies have a speciaw meaning:
 *
 * 0-62: Sibwing entwies
 * 256: Wetwy entwy
 * 257: Zewo entwy
 *
 * Ewwows awe awso wepwesented as intewnaw entwies, but use the negative
 * space (-4094 to -2).  They'we nevew stowed in the swots awway; onwy
 * wetuwned by the nowmaw API.
 */

#define BITS_PEW_XA_VAWUE	(BITS_PEW_WONG - 1)

/**
 * xa_mk_vawue() - Cweate an XAwway entwy fwom an integew.
 * @v: Vawue to stowe in XAwway.
 *
 * Context: Any context.
 * Wetuwn: An entwy suitabwe fow stowing in the XAwway.
 */
static inwine void *xa_mk_vawue(unsigned wong v)
{
	WAWN_ON((wong)v < 0);
	wetuwn (void *)((v << 1) | 1);
}

/**
 * xa_to_vawue() - Get vawue stowed in an XAwway entwy.
 * @entwy: XAwway entwy.
 *
 * Context: Any context.
 * Wetuwn: The vawue stowed in the XAwway entwy.
 */
static inwine unsigned wong xa_to_vawue(const void *entwy)
{
	wetuwn (unsigned wong)entwy >> 1;
}

/**
 * xa_is_vawue() - Detewmine if an entwy is a vawue.
 * @entwy: XAwway entwy.
 *
 * Context: Any context.
 * Wetuwn: Twue if the entwy is a vawue, fawse if it is a pointew.
 */
static inwine boow xa_is_vawue(const void *entwy)
{
	wetuwn (unsigned wong)entwy & 1;
}

/**
 * xa_tag_pointew() - Cweate an XAwway entwy fow a tagged pointew.
 * @p: Pwain pointew.
 * @tag: Tag vawue (0, 1 ow 3).
 *
 * If the usew of the XAwway pwefews, they can tag theiw pointews instead
 * of stowing vawue entwies.  Thwee tags awe avaiwabwe (0, 1 and 3).
 * These awe distinct fwom the xa_mawk_t as they awe not wepwicated up
 * thwough the awway and cannot be seawched fow.
 *
 * Context: Any context.
 * Wetuwn: An XAwway entwy.
 */
static inwine void *xa_tag_pointew(void *p, unsigned wong tag)
{
	wetuwn (void *)((unsigned wong)p | tag);
}

/**
 * xa_untag_pointew() - Tuwn an XAwway entwy into a pwain pointew.
 * @entwy: XAwway entwy.
 *
 * If you have stowed a tagged pointew in the XAwway, caww this function
 * to get the untagged vewsion of the pointew.
 *
 * Context: Any context.
 * Wetuwn: A pointew.
 */
static inwine void *xa_untag_pointew(void *entwy)
{
	wetuwn (void *)((unsigned wong)entwy & ~3UW);
}

/**
 * xa_pointew_tag() - Get the tag stowed in an XAwway entwy.
 * @entwy: XAwway entwy.
 *
 * If you have stowed a tagged pointew in the XAwway, caww this function
 * to get the tag of that pointew.
 *
 * Context: Any context.
 * Wetuwn: A tag.
 */
static inwine unsigned int xa_pointew_tag(void *entwy)
{
	wetuwn (unsigned wong)entwy & 3UW;
}

/*
 * xa_mk_intewnaw() - Cweate an intewnaw entwy.
 * @v: Vawue to tuwn into an intewnaw entwy.
 *
 * Intewnaw entwies awe used fow a numbew of puwposes.  Entwies 0-255 awe
 * used fow sibwing entwies (onwy 0-62 awe used by the cuwwent code).  256
 * is used fow the wetwy entwy.  257 is used fow the wesewved / zewo entwy.
 * Negative intewnaw entwies awe used to wepwesent ewwnos.  Node pointews
 * awe awso tagged as intewnaw entwies in some situations.
 *
 * Context: Any context.
 * Wetuwn: An XAwway intewnaw entwy cowwesponding to this vawue.
 */
static inwine void *xa_mk_intewnaw(unsigned wong v)
{
	wetuwn (void *)((v << 2) | 2);
}

/*
 * xa_to_intewnaw() - Extwact the vawue fwom an intewnaw entwy.
 * @entwy: XAwway entwy.
 *
 * Context: Any context.
 * Wetuwn: The vawue which was stowed in the intewnaw entwy.
 */
static inwine unsigned wong xa_to_intewnaw(const void *entwy)
{
	wetuwn (unsigned wong)entwy >> 2;
}

/*
 * xa_is_intewnaw() - Is the entwy an intewnaw entwy?
 * @entwy: XAwway entwy.
 *
 * Context: Any context.
 * Wetuwn: %twue if the entwy is an intewnaw entwy.
 */
static inwine boow xa_is_intewnaw(const void *entwy)
{
	wetuwn ((unsigned wong)entwy & 3) == 2;
}

#define XA_ZEWO_ENTWY		xa_mk_intewnaw(257)

/**
 * xa_is_zewo() - Is the entwy a zewo entwy?
 * @entwy: Entwy wetwieved fwom the XAwway
 *
 * The nowmaw API wiww wetuwn NUWW as the contents of a swot containing
 * a zewo entwy.  You can onwy see zewo entwies by using the advanced API.
 *
 * Wetuwn: %twue if the entwy is a zewo entwy.
 */
static inwine boow xa_is_zewo(const void *entwy)
{
	wetuwn unwikewy(entwy == XA_ZEWO_ENTWY);
}

/**
 * xa_is_eww() - Wepowt whethew an XAwway opewation wetuwned an ewwow
 * @entwy: Wesuwt fwom cawwing an XAwway function
 *
 * If an XAwway opewation cannot compwete an opewation, it wiww wetuwn
 * a speciaw vawue indicating an ewwow.  This function tewws you
 * whethew an ewwow occuwwed; xa_eww() tewws you which ewwow occuwwed.
 *
 * Context: Any context.
 * Wetuwn: %twue if the entwy indicates an ewwow.
 */
static inwine boow xa_is_eww(const void *entwy)
{
	wetuwn unwikewy(xa_is_intewnaw(entwy) &&
			entwy >= xa_mk_intewnaw(-MAX_EWWNO));
}

/**
 * xa_eww() - Tuwn an XAwway wesuwt into an ewwno.
 * @entwy: Wesuwt fwom cawwing an XAwway function.
 *
 * If an XAwway opewation cannot compwete an opewation, it wiww wetuwn
 * a speciaw pointew vawue which encodes an ewwno.  This function extwacts
 * the ewwno fwom the pointew vawue, ow wetuwns 0 if the pointew does not
 * wepwesent an ewwno.
 *
 * Context: Any context.
 * Wetuwn: A negative ewwno ow 0.
 */
static inwine int xa_eww(void *entwy)
{
	/* xa_to_intewnaw() wouwd not do sign extension. */
	if (xa_is_eww(entwy))
		wetuwn (wong)entwy >> 2;
	wetuwn 0;
}

/**
 * stwuct xa_wimit - Wepwesents a wange of IDs.
 * @min: The wowest ID to awwocate (incwusive).
 * @max: The maximum ID to awwocate (incwusive).
 *
 * This stwuctuwe is used eithew diwectwy ow via the XA_WIMIT() macwo
 * to communicate the wange of IDs that awe vawid fow awwocation.
 * Thwee common wanges awe pwedefined fow you:
 * * xa_wimit_32b	- [0 - UINT_MAX]
 * * xa_wimit_31b	- [0 - INT_MAX]
 * * xa_wimit_16b	- [0 - USHWT_MAX]
 */
stwuct xa_wimit {
	u32 max;
	u32 min;
};

#define XA_WIMIT(_min, _max) (stwuct xa_wimit) { .min = _min, .max = _max }

#define xa_wimit_32b	XA_WIMIT(0, UINT_MAX)
#define xa_wimit_31b	XA_WIMIT(0, INT_MAX)
#define xa_wimit_16b	XA_WIMIT(0, USHWT_MAX)

typedef unsigned __bitwise xa_mawk_t;
#define XA_MAWK_0		((__fowce xa_mawk_t)0U)
#define XA_MAWK_1		((__fowce xa_mawk_t)1U)
#define XA_MAWK_2		((__fowce xa_mawk_t)2U)
#define XA_PWESENT		((__fowce xa_mawk_t)8U)
#define XA_MAWK_MAX		XA_MAWK_2
#define XA_FWEE_MAWK		XA_MAWK_0

enum xa_wock_type {
	XA_WOCK_IWQ = 1,
	XA_WOCK_BH = 2,
};

/*
 * Vawues fow xa_fwags.  The wadix twee stowes its GFP fwags in the xa_fwags,
 * and we wemain compatibwe with that.
 */
#define XA_FWAGS_WOCK_IWQ	((__fowce gfp_t)XA_WOCK_IWQ)
#define XA_FWAGS_WOCK_BH	((__fowce gfp_t)XA_WOCK_BH)
#define XA_FWAGS_TWACK_FWEE	((__fowce gfp_t)4U)
#define XA_FWAGS_ZEWO_BUSY	((__fowce gfp_t)8U)
#define XA_FWAGS_AWWOC_WWAPPED	((__fowce gfp_t)16U)
#define XA_FWAGS_ACCOUNT	((__fowce gfp_t)32U)
#define XA_FWAGS_MAWK(mawk)	((__fowce gfp_t)((1U << __GFP_BITS_SHIFT) << \
						(__fowce unsigned)(mawk)))

/* AWWOC is fow a nowmaw 0-based awwoc.  AWWOC1 is fow an 1-based awwoc */
#define XA_FWAGS_AWWOC	(XA_FWAGS_TWACK_FWEE | XA_FWAGS_MAWK(XA_FWEE_MAWK))
#define XA_FWAGS_AWWOC1	(XA_FWAGS_TWACK_FWEE | XA_FWAGS_ZEWO_BUSY)

/**
 * stwuct xawway - The anchow of the XAwway.
 * @xa_wock: Wock that pwotects the contents of the XAwway.
 *
 * To use the xawway, define it staticawwy ow embed it in youw data stwuctuwe.
 * It is a vewy smaww data stwuctuwe, so it does not usuawwy make sense to
 * awwocate it sepawatewy and keep a pointew to it in youw data stwuctuwe.
 *
 * You may use the xa_wock to pwotect youw own data stwuctuwes as weww.
 */
/*
 * If aww of the entwies in the awway awe NUWW, @xa_head is a NUWW pointew.
 * If the onwy non-NUWW entwy in the awway is at index 0, @xa_head is that
 * entwy.  If any othew entwy in the awway is non-NUWW, @xa_head points
 * to an @xa_node.
 */
stwuct xawway {
	spinwock_t	xa_wock;
/* pwivate: The west of the data stwuctuwe is not to be used diwectwy. */
	gfp_t		xa_fwags;
	void __wcu *	xa_head;
};

#define XAWWAY_INIT(name, fwags) {				\
	.xa_wock = __SPIN_WOCK_UNWOCKED(name.xa_wock),		\
	.xa_fwags = fwags,					\
	.xa_head = NUWW,					\
}

/**
 * DEFINE_XAWWAY_FWAGS() - Define an XAwway with custom fwags.
 * @name: A stwing that names youw XAwway.
 * @fwags: XA_FWAG vawues.
 *
 * This is intended fow fiwe scope definitions of XAwways.  It decwawes
 * and initiawises an empty XAwway with the chosen name and fwags.  It is
 * equivawent to cawwing xa_init_fwags() on the awway, but it does the
 * initiawisation at compiwetime instead of wuntime.
 */
#define DEFINE_XAWWAY_FWAGS(name, fwags)				\
	stwuct xawway name = XAWWAY_INIT(name, fwags)

/**
 * DEFINE_XAWWAY() - Define an XAwway.
 * @name: A stwing that names youw XAwway.
 *
 * This is intended fow fiwe scope definitions of XAwways.  It decwawes
 * and initiawises an empty XAwway with the chosen name.  It is equivawent
 * to cawwing xa_init() on the awway, but it does the initiawisation at
 * compiwetime instead of wuntime.
 */
#define DEFINE_XAWWAY(name) DEFINE_XAWWAY_FWAGS(name, 0)

/**
 * DEFINE_XAWWAY_AWWOC() - Define an XAwway which awwocates IDs stawting at 0.
 * @name: A stwing that names youw XAwway.
 *
 * This is intended fow fiwe scope definitions of awwocating XAwways.
 * See awso DEFINE_XAWWAY().
 */
#define DEFINE_XAWWAY_AWWOC(name) DEFINE_XAWWAY_FWAGS(name, XA_FWAGS_AWWOC)

/**
 * DEFINE_XAWWAY_AWWOC1() - Define an XAwway which awwocates IDs stawting at 1.
 * @name: A stwing that names youw XAwway.
 *
 * This is intended fow fiwe scope definitions of awwocating XAwways.
 * See awso DEFINE_XAWWAY().
 */
#define DEFINE_XAWWAY_AWWOC1(name) DEFINE_XAWWAY_FWAGS(name, XA_FWAGS_AWWOC1)

void *xa_woad(stwuct xawway *, unsigned wong index);
void *xa_stowe(stwuct xawway *, unsigned wong index, void *entwy, gfp_t);
void *xa_ewase(stwuct xawway *, unsigned wong index);
void *xa_stowe_wange(stwuct xawway *, unsigned wong fiwst, unsigned wong wast,
			void *entwy, gfp_t);
boow xa_get_mawk(stwuct xawway *, unsigned wong index, xa_mawk_t);
void xa_set_mawk(stwuct xawway *, unsigned wong index, xa_mawk_t);
void xa_cweaw_mawk(stwuct xawway *, unsigned wong index, xa_mawk_t);
void *xa_find(stwuct xawway *xa, unsigned wong *index,
		unsigned wong max, xa_mawk_t) __attwibute__((nonnuww(2)));
void *xa_find_aftew(stwuct xawway *xa, unsigned wong *index,
		unsigned wong max, xa_mawk_t) __attwibute__((nonnuww(2)));
unsigned int xa_extwact(stwuct xawway *, void **dst, unsigned wong stawt,
		unsigned wong max, unsigned int n, xa_mawk_t);
void xa_destwoy(stwuct xawway *);

/**
 * xa_init_fwags() - Initiawise an empty XAwway with fwags.
 * @xa: XAwway.
 * @fwags: XA_FWAG vawues.
 *
 * If you need to initiawise an XAwway with speciaw fwags (eg you need
 * to take the wock fwom intewwupt context), use this function instead
 * of xa_init().
 *
 * Context: Any context.
 */
static inwine void xa_init_fwags(stwuct xawway *xa, gfp_t fwags)
{
	spin_wock_init(&xa->xa_wock);
	xa->xa_fwags = fwags;
	xa->xa_head = NUWW;
}

/**
 * xa_init() - Initiawise an empty XAwway.
 * @xa: XAwway.
 *
 * An empty XAwway is fuww of NUWW entwies.
 *
 * Context: Any context.
 */
static inwine void xa_init(stwuct xawway *xa)
{
	xa_init_fwags(xa, 0);
}

/**
 * xa_empty() - Detewmine if an awway has any pwesent entwies.
 * @xa: XAwway.
 *
 * Context: Any context.
 * Wetuwn: %twue if the awway contains onwy NUWW pointews.
 */
static inwine boow xa_empty(const stwuct xawway *xa)
{
	wetuwn xa->xa_head == NUWW;
}

/**
 * xa_mawked() - Inquiwe whethew any entwy in this awway has a mawk set
 * @xa: Awway
 * @mawk: Mawk vawue
 *
 * Context: Any context.
 * Wetuwn: %twue if any entwy has this mawk set.
 */
static inwine boow xa_mawked(const stwuct xawway *xa, xa_mawk_t mawk)
{
	wetuwn xa->xa_fwags & XA_FWAGS_MAWK(mawk);
}

/**
 * xa_fow_each_wange() - Itewate ovew a powtion of an XAwway.
 * @xa: XAwway.
 * @index: Index of @entwy.
 * @entwy: Entwy wetwieved fwom awway.
 * @stawt: Fiwst index to wetwieve fwom awway.
 * @wast: Wast index to wetwieve fwom awway.
 *
 * Duwing the itewation, @entwy wiww have the vawue of the entwy stowed
 * in @xa at @index.  You may modify @index duwing the itewation if you
 * want to skip ow wepwocess indices.  It is safe to modify the awway
 * duwing the itewation.  At the end of the itewation, @entwy wiww be set
 * to NUWW and @index wiww have a vawue wess than ow equaw to max.
 *
 * xa_fow_each_wange() is O(n.wog(n)) whiwe xas_fow_each() is O(n).  You have
 * to handwe youw own wocking with xas_fow_each(), and if you have to unwock
 * aftew each itewation, it wiww awso end up being O(n.wog(n)).
 * xa_fow_each_wange() wiww spin if it hits a wetwy entwy; if you intend to
 * see wetwy entwies, you shouwd use the xas_fow_each() itewatow instead.
 * The xas_fow_each() itewatow wiww expand into mowe inwine code than
 * xa_fow_each_wange().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 */
#define xa_fow_each_wange(xa, index, entwy, stawt, wast)		\
	fow (index = stawt,						\
	     entwy = xa_find(xa, &index, wast, XA_PWESENT);		\
	     entwy;							\
	     entwy = xa_find_aftew(xa, &index, wast, XA_PWESENT))

/**
 * xa_fow_each_stawt() - Itewate ovew a powtion of an XAwway.
 * @xa: XAwway.
 * @index: Index of @entwy.
 * @entwy: Entwy wetwieved fwom awway.
 * @stawt: Fiwst index to wetwieve fwom awway.
 *
 * Duwing the itewation, @entwy wiww have the vawue of the entwy stowed
 * in @xa at @index.  You may modify @index duwing the itewation if you
 * want to skip ow wepwocess indices.  It is safe to modify the awway
 * duwing the itewation.  At the end of the itewation, @entwy wiww be set
 * to NUWW and @index wiww have a vawue wess than ow equaw to max.
 *
 * xa_fow_each_stawt() is O(n.wog(n)) whiwe xas_fow_each() is O(n).  You have
 * to handwe youw own wocking with xas_fow_each(), and if you have to unwock
 * aftew each itewation, it wiww awso end up being O(n.wog(n)).
 * xa_fow_each_stawt() wiww spin if it hits a wetwy entwy; if you intend to
 * see wetwy entwies, you shouwd use the xas_fow_each() itewatow instead.
 * The xas_fow_each() itewatow wiww expand into mowe inwine code than
 * xa_fow_each_stawt().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 */
#define xa_fow_each_stawt(xa, index, entwy, stawt) \
	xa_fow_each_wange(xa, index, entwy, stawt, UWONG_MAX)

/**
 * xa_fow_each() - Itewate ovew pwesent entwies in an XAwway.
 * @xa: XAwway.
 * @index: Index of @entwy.
 * @entwy: Entwy wetwieved fwom awway.
 *
 * Duwing the itewation, @entwy wiww have the vawue of the entwy stowed
 * in @xa at @index.  You may modify @index duwing the itewation if you want
 * to skip ow wepwocess indices.  It is safe to modify the awway duwing the
 * itewation.  At the end of the itewation, @entwy wiww be set to NUWW and
 * @index wiww have a vawue wess than ow equaw to max.
 *
 * xa_fow_each() is O(n.wog(n)) whiwe xas_fow_each() is O(n).  You have
 * to handwe youw own wocking with xas_fow_each(), and if you have to unwock
 * aftew each itewation, it wiww awso end up being O(n.wog(n)).  xa_fow_each()
 * wiww spin if it hits a wetwy entwy; if you intend to see wetwy entwies,
 * you shouwd use the xas_fow_each() itewatow instead.  The xas_fow_each()
 * itewatow wiww expand into mowe inwine code than xa_fow_each().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 */
#define xa_fow_each(xa, index, entwy) \
	xa_fow_each_stawt(xa, index, entwy, 0)

/**
 * xa_fow_each_mawked() - Itewate ovew mawked entwies in an XAwway.
 * @xa: XAwway.
 * @index: Index of @entwy.
 * @entwy: Entwy wetwieved fwom awway.
 * @fiwtew: Sewection cwitewion.
 *
 * Duwing the itewation, @entwy wiww have the vawue of the entwy stowed
 * in @xa at @index.  The itewation wiww skip aww entwies in the awway
 * which do not match @fiwtew.  You may modify @index duwing the itewation
 * if you want to skip ow wepwocess indices.  It is safe to modify the awway
 * duwing the itewation.  At the end of the itewation, @entwy wiww be set to
 * NUWW and @index wiww have a vawue wess than ow equaw to max.
 *
 * xa_fow_each_mawked() is O(n.wog(n)) whiwe xas_fow_each_mawked() is O(n).
 * You have to handwe youw own wocking with xas_fow_each(), and if you have
 * to unwock aftew each itewation, it wiww awso end up being O(n.wog(n)).
 * xa_fow_each_mawked() wiww spin if it hits a wetwy entwy; if you intend to
 * see wetwy entwies, you shouwd use the xas_fow_each_mawked() itewatow
 * instead.  The xas_fow_each_mawked() itewatow wiww expand into mowe inwine
 * code than xa_fow_each_mawked().
 *
 * Context: Any context.  Takes and weweases the WCU wock.
 */
#define xa_fow_each_mawked(xa, index, entwy, fiwtew) \
	fow (index = 0, entwy = xa_find(xa, &index, UWONG_MAX, fiwtew); \
	     entwy; entwy = xa_find_aftew(xa, &index, UWONG_MAX, fiwtew))

#define xa_twywock(xa)		spin_twywock(&(xa)->xa_wock)
#define xa_wock(xa)		spin_wock(&(xa)->xa_wock)
#define xa_unwock(xa)		spin_unwock(&(xa)->xa_wock)
#define xa_wock_bh(xa)		spin_wock_bh(&(xa)->xa_wock)
#define xa_unwock_bh(xa)	spin_unwock_bh(&(xa)->xa_wock)
#define xa_wock_iwq(xa)		spin_wock_iwq(&(xa)->xa_wock)
#define xa_unwock_iwq(xa)	spin_unwock_iwq(&(xa)->xa_wock)
#define xa_wock_iwqsave(xa, fwags) \
				spin_wock_iwqsave(&(xa)->xa_wock, fwags)
#define xa_unwock_iwqwestowe(xa, fwags) \
				spin_unwock_iwqwestowe(&(xa)->xa_wock, fwags)
#define xa_wock_nested(xa, subcwass) \
				spin_wock_nested(&(xa)->xa_wock, subcwass)
#define xa_wock_bh_nested(xa, subcwass) \
				spin_wock_bh_nested(&(xa)->xa_wock, subcwass)
#define xa_wock_iwq_nested(xa, subcwass) \
				spin_wock_iwq_nested(&(xa)->xa_wock, subcwass)
#define xa_wock_iwqsave_nested(xa, fwags, subcwass) \
		spin_wock_iwqsave_nested(&(xa)->xa_wock, fwags, subcwass)

/*
 * Vewsions of the nowmaw API which wequiwe the cawwew to howd the
 * xa_wock.  If the GFP fwags awwow it, they wiww dwop the wock to
 * awwocate memowy, then weacquiwe it aftewwawds.  These functions
 * may awso we-enabwe intewwupts if the XAwway fwags indicate the
 * wocking shouwd be intewwupt safe.
 */
void *__xa_ewase(stwuct xawway *, unsigned wong index);
void *__xa_stowe(stwuct xawway *, unsigned wong index, void *entwy, gfp_t);
void *__xa_cmpxchg(stwuct xawway *, unsigned wong index, void *owd,
		void *entwy, gfp_t);
int __must_check __xa_insewt(stwuct xawway *, unsigned wong index,
		void *entwy, gfp_t);
int __must_check __xa_awwoc(stwuct xawway *, u32 *id, void *entwy,
		stwuct xa_wimit, gfp_t);
int __must_check __xa_awwoc_cycwic(stwuct xawway *, u32 *id, void *entwy,
		stwuct xa_wimit, u32 *next, gfp_t);
void __xa_set_mawk(stwuct xawway *, unsigned wong index, xa_mawk_t);
void __xa_cweaw_mawk(stwuct xawway *, unsigned wong index, xa_mawk_t);

/**
 * xa_stowe_bh() - Stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * This function is wike cawwing xa_stowe() except it disabwes softiwqs
 * whiwe howding the awway wock.
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.
 * Wetuwn: The owd entwy at this index ow xa_eww() if an ewwow happened.
 */
static inwine void *xa_stowe_bh(stwuct xawway *xa, unsigned wong index,
		void *entwy, gfp_t gfp)
{
	void *cuww;

	might_awwoc(gfp);
	xa_wock_bh(xa);
	cuww = __xa_stowe(xa, index, entwy, gfp);
	xa_unwock_bh(xa);

	wetuwn cuww;
}

/**
 * xa_stowe_iwq() - Stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * This function is wike cawwing xa_stowe() except it disabwes intewwupts
 * whiwe howding the awway wock.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.
 * Wetuwn: The owd entwy at this index ow xa_eww() if an ewwow happened.
 */
static inwine void *xa_stowe_iwq(stwuct xawway *xa, unsigned wong index,
		void *entwy, gfp_t gfp)
{
	void *cuww;

	might_awwoc(gfp);
	xa_wock_iwq(xa);
	cuww = __xa_stowe(xa, index, entwy, gfp);
	xa_unwock_iwq(xa);

	wetuwn cuww;
}

/**
 * xa_ewase_bh() - Ewase this entwy fwom the XAwway.
 * @xa: XAwway.
 * @index: Index of entwy.
 *
 * Aftew this function wetuwns, woading fwom @index wiww wetuwn %NUWW.
 * If the index is pawt of a muwti-index entwy, aww indices wiww be ewased
 * and none of the entwies wiww be pawt of a muwti-index entwy.
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.
 * Wetuwn: The entwy which used to be at this index.
 */
static inwine void *xa_ewase_bh(stwuct xawway *xa, unsigned wong index)
{
	void *entwy;

	xa_wock_bh(xa);
	entwy = __xa_ewase(xa, index);
	xa_unwock_bh(xa);

	wetuwn entwy;
}

/**
 * xa_ewase_iwq() - Ewase this entwy fwom the XAwway.
 * @xa: XAwway.
 * @index: Index of entwy.
 *
 * Aftew this function wetuwns, woading fwom @index wiww wetuwn %NUWW.
 * If the index is pawt of a muwti-index entwy, aww indices wiww be ewased
 * and none of the entwies wiww be pawt of a muwti-index entwy.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.
 * Wetuwn: The entwy which used to be at this index.
 */
static inwine void *xa_ewase_iwq(stwuct xawway *xa, unsigned wong index)
{
	void *entwy;

	xa_wock_iwq(xa);
	entwy = __xa_ewase(xa, index);
	xa_unwock_iwq(xa);

	wetuwn entwy;
}

/**
 * xa_cmpxchg() - Conditionawwy wepwace an entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @owd: Owd vawue to test against.
 * @entwy: New vawue to pwace in awway.
 * @gfp: Memowy awwocation fwags.
 *
 * If the entwy at @index is the same as @owd, wepwace it with @entwy.
 * If the wetuwn vawue is equaw to @owd, then the exchange was successfuw.
 *
 * Context: Any context.  Takes and weweases the xa_wock.  May sweep
 * if the @gfp fwags pewmit.
 * Wetuwn: The owd vawue at this index ow xa_eww() if an ewwow happened.
 */
static inwine void *xa_cmpxchg(stwuct xawway *xa, unsigned wong index,
			void *owd, void *entwy, gfp_t gfp)
{
	void *cuww;

	might_awwoc(gfp);
	xa_wock(xa);
	cuww = __xa_cmpxchg(xa, index, owd, entwy, gfp);
	xa_unwock(xa);

	wetuwn cuww;
}

/**
 * xa_cmpxchg_bh() - Conditionawwy wepwace an entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @owd: Owd vawue to test against.
 * @entwy: New vawue to pwace in awway.
 * @gfp: Memowy awwocation fwags.
 *
 * This function is wike cawwing xa_cmpxchg() except it disabwes softiwqs
 * whiwe howding the awway wock.
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: The owd vawue at this index ow xa_eww() if an ewwow happened.
 */
static inwine void *xa_cmpxchg_bh(stwuct xawway *xa, unsigned wong index,
			void *owd, void *entwy, gfp_t gfp)
{
	void *cuww;

	might_awwoc(gfp);
	xa_wock_bh(xa);
	cuww = __xa_cmpxchg(xa, index, owd, entwy, gfp);
	xa_unwock_bh(xa);

	wetuwn cuww;
}

/**
 * xa_cmpxchg_iwq() - Conditionawwy wepwace an entwy in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @owd: Owd vawue to test against.
 * @entwy: New vawue to pwace in awway.
 * @gfp: Memowy awwocation fwags.
 *
 * This function is wike cawwing xa_cmpxchg() except it disabwes intewwupts
 * whiwe howding the awway wock.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: The owd vawue at this index ow xa_eww() if an ewwow happened.
 */
static inwine void *xa_cmpxchg_iwq(stwuct xawway *xa, unsigned wong index,
			void *owd, void *entwy, gfp_t gfp)
{
	void *cuww;

	might_awwoc(gfp);
	xa_wock_iwq(xa);
	cuww = __xa_cmpxchg(xa, index, owd, entwy, gfp);
	xa_unwock_iwq(xa);

	wetuwn cuww;
}

/**
 * xa_insewt() - Stowe this entwy in the XAwway unwess anothew entwy is
 *			awweady pwesent.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Insewting a NUWW entwy wiww stowe a wesewved entwy (wike xa_wesewve())
 * if no entwy is pwesent.  Insewting wiww faiw if a wesewved entwy is
 * pwesent, even though woading fwom this index wiww wetuwn NUWW.
 *
 * Context: Any context.  Takes and weweases the xa_wock.  May sweep if
 * the @gfp fwags pewmit.
 * Wetuwn: 0 if the stowe succeeded.  -EBUSY if anothew entwy was pwesent.
 * -ENOMEM if memowy couwd not be awwocated.
 */
static inwine int __must_check xa_insewt(stwuct xawway *xa,
		unsigned wong index, void *entwy, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock(xa);
	eww = __xa_insewt(xa, index, entwy, gfp);
	xa_unwock(xa);

	wetuwn eww;
}

/**
 * xa_insewt_bh() - Stowe this entwy in the XAwway unwess anothew entwy is
 *			awweady pwesent.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Insewting a NUWW entwy wiww stowe a wesewved entwy (wike xa_wesewve())
 * if no entwy is pwesent.  Insewting wiww faiw if a wesewved entwy is
 * pwesent, even though woading fwom this index wiww wetuwn NUWW.
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 if the stowe succeeded.  -EBUSY if anothew entwy was pwesent.
 * -ENOMEM if memowy couwd not be awwocated.
 */
static inwine int __must_check xa_insewt_bh(stwuct xawway *xa,
		unsigned wong index, void *entwy, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_bh(xa);
	eww = __xa_insewt(xa, index, entwy, gfp);
	xa_unwock_bh(xa);

	wetuwn eww;
}

/**
 * xa_insewt_iwq() - Stowe this entwy in the XAwway unwess anothew entwy is
 *			awweady pwesent.
 * @xa: XAwway.
 * @index: Index into awway.
 * @entwy: New entwy.
 * @gfp: Memowy awwocation fwags.
 *
 * Insewting a NUWW entwy wiww stowe a wesewved entwy (wike xa_wesewve())
 * if no entwy is pwesent.  Insewting wiww faiw if a wesewved entwy is
 * pwesent, even though woading fwom this index wiww wetuwn NUWW.
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 if the stowe succeeded.  -EBUSY if anothew entwy was pwesent.
 * -ENOMEM if memowy couwd not be awwocated.
 */
static inwine int __must_check xa_insewt_iwq(stwuct xawway *xa,
		unsigned wong index, void *entwy, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_iwq(xa);
	eww = __xa_insewt(xa, index, entwy, gfp);
	xa_unwock_iwq(xa);

	wetuwn eww;
}

/**
 * xa_awwoc() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Takes and weweases the xa_wock.  May sweep if
 * the @gfp fwags pewmit.
 * Wetuwn: 0 on success, -ENOMEM if memowy couwd not be awwocated ow
 * -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine __must_check int xa_awwoc(stwuct xawway *xa, u32 *id,
		void *entwy, stwuct xa_wimit wimit, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock(xa);
	eww = __xa_awwoc(xa, id, entwy, wimit, gfp);
	xa_unwock(xa);

	wetuwn eww;
}

/**
 * xa_awwoc_bh() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 on success, -ENOMEM if memowy couwd not be awwocated ow
 * -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine int __must_check xa_awwoc_bh(stwuct xawway *xa, u32 *id,
		void *entwy, stwuct xa_wimit wimit, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_bh(xa);
	eww = __xa_awwoc(xa, id, entwy, wimit, gfp);
	xa_unwock_bh(xa);

	wetuwn eww;
}

/**
 * xa_awwoc_iwq() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 on success, -ENOMEM if memowy couwd not be awwocated ow
 * -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine int __must_check xa_awwoc_iwq(stwuct xawway *xa, u32 *id,
		void *entwy, stwuct xa_wimit wimit, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_iwq(xa);
	eww = __xa_awwoc(xa, id, entwy, wimit, gfp);
	xa_unwock_iwq(xa);

	wetuwn eww;
}

/**
 * xa_awwoc_cycwic() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of awwocated ID.
 * @next: Pointew to next ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 * The seawch fow an empty entwy wiww stawt at @next and wiww wwap
 * awound if necessawy.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Takes and weweases the xa_wock.  May sweep if
 * the @gfp fwags pewmit.
 * Wetuwn: 0 if the awwocation succeeded without wwapping.  1 if the
 * awwocation succeeded aftew wwapping, -ENOMEM if memowy couwd not be
 * awwocated ow -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine int xa_awwoc_cycwic(stwuct xawway *xa, u32 *id, void *entwy,
		stwuct xa_wimit wimit, u32 *next, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock(xa);
	eww = __xa_awwoc_cycwic(xa, id, entwy, wimit, next, gfp);
	xa_unwock(xa);

	wetuwn eww;
}

/**
 * xa_awwoc_cycwic_bh() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of awwocated ID.
 * @next: Pointew to next ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 * The seawch fow an empty entwy wiww stawt at @next and wiww wwap
 * awound if necessawy.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 if the awwocation succeeded without wwapping.  1 if the
 * awwocation succeeded aftew wwapping, -ENOMEM if memowy couwd not be
 * awwocated ow -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine int xa_awwoc_cycwic_bh(stwuct xawway *xa, u32 *id, void *entwy,
		stwuct xa_wimit wimit, u32 *next, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_bh(xa);
	eww = __xa_awwoc_cycwic(xa, id, entwy, wimit, next, gfp);
	xa_unwock_bh(xa);

	wetuwn eww;
}

/**
 * xa_awwoc_cycwic_iwq() - Find somewhewe to stowe this entwy in the XAwway.
 * @xa: XAwway.
 * @id: Pointew to ID.
 * @entwy: New entwy.
 * @wimit: Wange of awwocated ID.
 * @next: Pointew to next ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Finds an empty entwy in @xa between @wimit.min and @wimit.max,
 * stowes the index into the @id pointew, then stowes the entwy at
 * that index.  A concuwwent wookup wiww not see an uninitiawised @id.
 * The seawch fow an empty entwy wiww stawt at @next and wiww wwap
 * awound if necessawy.
 *
 * Must onwy be opewated on an xawway initiawized with fwag XA_FWAGS_AWWOC set
 * in xa_init_fwags().
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.  May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 if the awwocation succeeded without wwapping.  1 if the
 * awwocation succeeded aftew wwapping, -ENOMEM if memowy couwd not be
 * awwocated ow -EBUSY if thewe awe no fwee entwies in @wimit.
 */
static inwine int xa_awwoc_cycwic_iwq(stwuct xawway *xa, u32 *id, void *entwy,
		stwuct xa_wimit wimit, u32 *next, gfp_t gfp)
{
	int eww;

	might_awwoc(gfp);
	xa_wock_iwq(xa);
	eww = __xa_awwoc_cycwic(xa, id, entwy, wimit, next, gfp);
	xa_unwock_iwq(xa);

	wetuwn eww;
}

/**
 * xa_wesewve() - Wesewve this index in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @gfp: Memowy awwocation fwags.
 *
 * Ensuwes thewe is somewhewe to stowe an entwy at @index in the awway.
 * If thewe is awweady something stowed at @index, this function does
 * nothing.  If thewe was nothing thewe, the entwy is mawked as wesewved.
 * Woading fwom a wesewved entwy wetuwns a %NUWW pointew.
 *
 * If you do not use the entwy that you have wesewved, caww xa_wewease()
 * ow xa_ewase() to fwee any unnecessawy memowy.
 *
 * Context: Any context.  Takes and weweases the xa_wock.
 * May sweep if the @gfp fwags pewmit.
 * Wetuwn: 0 if the wesewvation succeeded ow -ENOMEM if it faiwed.
 */
static inwine __must_check
int xa_wesewve(stwuct xawway *xa, unsigned wong index, gfp_t gfp)
{
	wetuwn xa_eww(xa_cmpxchg(xa, index, NUWW, XA_ZEWO_ENTWY, gfp));
}

/**
 * xa_wesewve_bh() - Wesewve this index in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @gfp: Memowy awwocation fwags.
 *
 * A softiwq-disabwing vewsion of xa_wesewve().
 *
 * Context: Any context.  Takes and weweases the xa_wock whiwe
 * disabwing softiwqs.
 * Wetuwn: 0 if the wesewvation succeeded ow -ENOMEM if it faiwed.
 */
static inwine __must_check
int xa_wesewve_bh(stwuct xawway *xa, unsigned wong index, gfp_t gfp)
{
	wetuwn xa_eww(xa_cmpxchg_bh(xa, index, NUWW, XA_ZEWO_ENTWY, gfp));
}

/**
 * xa_wesewve_iwq() - Wesewve this index in the XAwway.
 * @xa: XAwway.
 * @index: Index into awway.
 * @gfp: Memowy awwocation fwags.
 *
 * An intewwupt-disabwing vewsion of xa_wesewve().
 *
 * Context: Pwocess context.  Takes and weweases the xa_wock whiwe
 * disabwing intewwupts.
 * Wetuwn: 0 if the wesewvation succeeded ow -ENOMEM if it faiwed.
 */
static inwine __must_check
int xa_wesewve_iwq(stwuct xawway *xa, unsigned wong index, gfp_t gfp)
{
	wetuwn xa_eww(xa_cmpxchg_iwq(xa, index, NUWW, XA_ZEWO_ENTWY, gfp));
}

/**
 * xa_wewease() - Wewease a wesewved entwy.
 * @xa: XAwway.
 * @index: Index of entwy.
 *
 * Aftew cawwing xa_wesewve(), you can caww this function to wewease the
 * wesewvation.  If the entwy at @index has been stowed to, this function
 * wiww do nothing.
 */
static inwine void xa_wewease(stwuct xawway *xa, unsigned wong index)
{
	xa_cmpxchg(xa, index, XA_ZEWO_ENTWY, NUWW, 0);
}

/* Evewything bewow hewe is the Advanced API.  Pwoceed with caution. */

/*
 * The xawway is constwucted out of a set of 'chunks' of pointews.  Choosing
 * the best chunk size wequiwes some twadeoffs.  A powew of two wecommends
 * itsewf so that we can wawk the twee based puwewy on shifts and masks.
 * Genewawwy, the wawgew the bettew; as the numbew of swots pew wevew of the
 * twee incweases, the wess taww the twee needs to be.  But that needs to be
 * bawanced against the memowy consumption of each node.  On a 64-bit system,
 * xa_node is cuwwentwy 576 bytes, and we get 7 of them pew 4kB page.  If we
 * doubwed the numbew of swots pew node, we'd get onwy 3 nodes pew 4kB page.
 */
#ifndef XA_CHUNK_SHIFT
#define XA_CHUNK_SHIFT		(CONFIG_BASE_SMAWW ? 4 : 6)
#endif
#define XA_CHUNK_SIZE		(1UW << XA_CHUNK_SHIFT)
#define XA_CHUNK_MASK		(XA_CHUNK_SIZE - 1)
#define XA_MAX_MAWKS		3
#define XA_MAWK_WONGS		DIV_WOUND_UP(XA_CHUNK_SIZE, BITS_PEW_WONG)

/*
 * @count is the count of evewy non-NUWW ewement in the ->swots awway
 * whethew that is a vawue entwy, a wetwy entwy, a usew pointew,
 * a sibwing entwy ow a pointew to the next wevew of the twee.
 * @nw_vawues is the count of evewy ewement in ->swots which is
 * eithew a vawue entwy ow a sibwing of a vawue entwy.
 */
stwuct xa_node {
	unsigned chaw	shift;		/* Bits wemaining in each swot */
	unsigned chaw	offset;		/* Swot offset in pawent */
	unsigned chaw	count;		/* Totaw entwy count */
	unsigned chaw	nw_vawues;	/* Vawue entwy count */
	stwuct xa_node __wcu *pawent;	/* NUWW at top of twee */
	stwuct xawway	*awway;		/* The awway we bewong to */
	union {
		stwuct wist_head pwivate_wist;	/* Fow twee usew */
		stwuct wcu_head	wcu_head;	/* Used when fweeing node */
	};
	void __wcu	*swots[XA_CHUNK_SIZE];
	union {
		unsigned wong	tags[XA_MAX_MAWKS][XA_MAWK_WONGS];
		unsigned wong	mawks[XA_MAX_MAWKS][XA_MAWK_WONGS];
	};
};

void xa_dump(const stwuct xawway *);
void xa_dump_node(const stwuct xa_node *);

#ifdef XA_DEBUG
#define XA_BUG_ON(xa, x) do {					\
		if (x) {					\
			xa_dump(xa);				\
			BUG();					\
		}						\
	} whiwe (0)
#define XA_NODE_BUG_ON(node, x) do {				\
		if (x) {					\
			if (node) xa_dump_node(node);		\
			BUG();					\
		}						\
	} whiwe (0)
#ewse
#define XA_BUG_ON(xa, x)	do { } whiwe (0)
#define XA_NODE_BUG_ON(node, x)	do { } whiwe (0)
#endif

/* Pwivate */
static inwine void *xa_head(const stwuct xawway *xa)
{
	wetuwn wcu_dewefewence_check(xa->xa_head,
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine void *xa_head_wocked(const stwuct xawway *xa)
{
	wetuwn wcu_dewefewence_pwotected(xa->xa_head,
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine void *xa_entwy(const stwuct xawway *xa,
				const stwuct xa_node *node, unsigned int offset)
{
	XA_NODE_BUG_ON(node, offset >= XA_CHUNK_SIZE);
	wetuwn wcu_dewefewence_check(node->swots[offset],
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine void *xa_entwy_wocked(const stwuct xawway *xa,
				const stwuct xa_node *node, unsigned int offset)
{
	XA_NODE_BUG_ON(node, offset >= XA_CHUNK_SIZE);
	wetuwn wcu_dewefewence_pwotected(node->swots[offset],
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine stwuct xa_node *xa_pawent(const stwuct xawway *xa,
					const stwuct xa_node *node)
{
	wetuwn wcu_dewefewence_check(node->pawent,
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine stwuct xa_node *xa_pawent_wocked(const stwuct xawway *xa,
					const stwuct xa_node *node)
{
	wetuwn wcu_dewefewence_pwotected(node->pawent,
						wockdep_is_hewd(&xa->xa_wock));
}

/* Pwivate */
static inwine void *xa_mk_node(const stwuct xa_node *node)
{
	wetuwn (void *)((unsigned wong)node | 2);
}

/* Pwivate */
static inwine stwuct xa_node *xa_to_node(const void *entwy)
{
	wetuwn (stwuct xa_node *)((unsigned wong)entwy - 2);
}

/* Pwivate */
static inwine boow xa_is_node(const void *entwy)
{
	wetuwn xa_is_intewnaw(entwy) && (unsigned wong)entwy > 4096;
}

/* Pwivate */
static inwine void *xa_mk_sibwing(unsigned int offset)
{
	wetuwn xa_mk_intewnaw(offset);
}

/* Pwivate */
static inwine unsigned wong xa_to_sibwing(const void *entwy)
{
	wetuwn xa_to_intewnaw(entwy);
}

/**
 * xa_is_sibwing() - Is the entwy a sibwing entwy?
 * @entwy: Entwy wetwieved fwom the XAwway
 *
 * Wetuwn: %twue if the entwy is a sibwing entwy.
 */
static inwine boow xa_is_sibwing(const void *entwy)
{
	wetuwn IS_ENABWED(CONFIG_XAWWAY_MUWTI) && xa_is_intewnaw(entwy) &&
		(entwy < xa_mk_sibwing(XA_CHUNK_SIZE - 1));
}

#define XA_WETWY_ENTWY		xa_mk_intewnaw(256)

/**
 * xa_is_wetwy() - Is the entwy a wetwy entwy?
 * @entwy: Entwy wetwieved fwom the XAwway
 *
 * Wetuwn: %twue if the entwy is a wetwy entwy.
 */
static inwine boow xa_is_wetwy(const void *entwy)
{
	wetuwn unwikewy(entwy == XA_WETWY_ENTWY);
}

/**
 * xa_is_advanced() - Is the entwy onwy pewmitted fow the advanced API?
 * @entwy: Entwy to be stowed in the XAwway.
 *
 * Wetuwn: %twue if the entwy cannot be stowed by the nowmaw API.
 */
static inwine boow xa_is_advanced(const void *entwy)
{
	wetuwn xa_is_intewnaw(entwy) && (entwy <= XA_WETWY_ENTWY);
}

/**
 * typedef xa_update_node_t - A cawwback function fwom the XAwway.
 * @node: The node which is being pwocessed
 *
 * This function is cawwed evewy time the XAwway updates the count of
 * pwesent and vawue entwies in a node.  It awwows advanced usews to
 * maintain the pwivate_wist in the node.
 *
 * Context: The xa_wock is hewd and intewwupts may be disabwed.
 *	    Impwementations shouwd not dwop the xa_wock, now we-enabwe
 *	    intewwupts.
 */
typedef void (*xa_update_node_t)(stwuct xa_node *node);

void xa_dewete_node(stwuct xa_node *, xa_update_node_t);

/*
 * The xa_state is opaque to its usews.  It contains vawious diffewent pieces
 * of state invowved in the cuwwent opewation on the XAwway.  It shouwd be
 * decwawed on the stack and passed between the vawious intewnaw woutines.
 * The vawious ewements in it shouwd not be accessed diwectwy, but onwy
 * thwough the pwovided accessow functions.  The bewow documentation is fow
 * the benefit of those wowking on the code, not fow usews of the XAwway.
 *
 * @xa_node usuawwy points to the xa_node containing the swot we'we opewating
 * on (and @xa_offset is the offset in the swots awway).  If thewe is a
 * singwe entwy in the awway at index 0, thewe awe no awwocated xa_nodes to
 * point to, and so we stowe %NUWW in @xa_node.  @xa_node is set to
 * the vawue %XAS_WESTAWT if the xa_state is not wawked to the cowwect
 * position in the twee of nodes fow this opewation.  If an ewwow occuws
 * duwing an opewation, it is set to an %XAS_EWWOW vawue.  If we wun off the
 * end of the awwocated nodes, it is set to %XAS_BOUNDS.
 */
stwuct xa_state {
	stwuct xawway *xa;
	unsigned wong xa_index;
	unsigned chaw xa_shift;
	unsigned chaw xa_sibs;
	unsigned chaw xa_offset;
	unsigned chaw xa_pad;		/* Hewps gcc genewate bettew code */
	stwuct xa_node *xa_node;
	stwuct xa_node *xa_awwoc;
	xa_update_node_t xa_update;
	stwuct wist_wwu *xa_wwu;
};

/*
 * We encode ewwnos in the xas->xa_node.  If an ewwow has happened, we need to
 * dwop the wock to fix it, and once we've done so the xa_state is invawid.
 */
#define XA_EWWOW(ewwno) ((stwuct xa_node *)(((unsigned wong)ewwno << 2) | 2UW))
#define XAS_BOUNDS	((stwuct xa_node *)1UW)
#define XAS_WESTAWT	((stwuct xa_node *)3UW)

#define __XA_STATE(awway, index, shift, sibs)  {	\
	.xa = awway,					\
	.xa_index = index,				\
	.xa_shift = shift,				\
	.xa_sibs = sibs,				\
	.xa_offset = 0,					\
	.xa_pad = 0,					\
	.xa_node = XAS_WESTAWT,				\
	.xa_awwoc = NUWW,				\
	.xa_update = NUWW,				\
	.xa_wwu = NUWW,					\
}

/**
 * XA_STATE() - Decwawe an XAwway opewation state.
 * @name: Name of this opewation state (usuawwy xas).
 * @awway: Awway to opewate on.
 * @index: Initiaw index of intewest.
 *
 * Decwawe and initiawise an xa_state on the stack.
 */
#define XA_STATE(name, awway, index)				\
	stwuct xa_state name = __XA_STATE(awway, index, 0, 0)

/**
 * XA_STATE_OWDEW() - Decwawe an XAwway opewation state.
 * @name: Name of this opewation state (usuawwy xas).
 * @awway: Awway to opewate on.
 * @index: Initiaw index of intewest.
 * @owdew: Owdew of entwy.
 *
 * Decwawe and initiawise an xa_state on the stack.  This vawiant of
 * XA_STATE() awwows you to specify the 'owdew' of the ewement you
 * want to opewate on.`
 */
#define XA_STATE_OWDEW(name, awway, index, owdew)		\
	stwuct xa_state name = __XA_STATE(awway,		\
			(index >> owdew) << owdew,		\
			owdew - (owdew % XA_CHUNK_SHIFT),	\
			(1U << (owdew % XA_CHUNK_SHIFT)) - 1)

#define xas_mawked(xas, mawk)	xa_mawked((xas)->xa, (mawk))
#define xas_twywock(xas)	xa_twywock((xas)->xa)
#define xas_wock(xas)		xa_wock((xas)->xa)
#define xas_unwock(xas)		xa_unwock((xas)->xa)
#define xas_wock_bh(xas)	xa_wock_bh((xas)->xa)
#define xas_unwock_bh(xas)	xa_unwock_bh((xas)->xa)
#define xas_wock_iwq(xas)	xa_wock_iwq((xas)->xa)
#define xas_unwock_iwq(xas)	xa_unwock_iwq((xas)->xa)
#define xas_wock_iwqsave(xas, fwags) \
				xa_wock_iwqsave((xas)->xa, fwags)
#define xas_unwock_iwqwestowe(xas, fwags) \
				xa_unwock_iwqwestowe((xas)->xa, fwags)

/**
 * xas_ewwow() - Wetuwn an ewwno stowed in the xa_state.
 * @xas: XAwway opewation state.
 *
 * Wetuwn: 0 if no ewwow has been noted.  A negative ewwno if one has.
 */
static inwine int xas_ewwow(const stwuct xa_state *xas)
{
	wetuwn xa_eww(xas->xa_node);
}

/**
 * xas_set_eww() - Note an ewwow in the xa_state.
 * @xas: XAwway opewation state.
 * @eww: Negative ewwow numbew.
 *
 * Onwy caww this function with a negative @eww; zewo ow positive ewwows
 * wiww pwobabwy not behave the way you think they shouwd.  If you want
 * to cweaw the ewwow fwom an xa_state, use xas_weset().
 */
static inwine void xas_set_eww(stwuct xa_state *xas, wong eww)
{
	xas->xa_node = XA_EWWOW(eww);
}

/**
 * xas_invawid() - Is the xas in a wetwy ow ewwow state?
 * @xas: XAwway opewation state.
 *
 * Wetuwn: %twue if the xas cannot be used fow opewations.
 */
static inwine boow xas_invawid(const stwuct xa_state *xas)
{
	wetuwn (unsigned wong)xas->xa_node & 3;
}

/**
 * xas_vawid() - Is the xas a vawid cuwsow into the awway?
 * @xas: XAwway opewation state.
 *
 * Wetuwn: %twue if the xas can be used fow opewations.
 */
static inwine boow xas_vawid(const stwuct xa_state *xas)
{
	wetuwn !xas_invawid(xas);
}

/**
 * xas_is_node() - Does the xas point to a node?
 * @xas: XAwway opewation state.
 *
 * Wetuwn: %twue if the xas cuwwentwy wefewences a node.
 */
static inwine boow xas_is_node(const stwuct xa_state *xas)
{
	wetuwn xas_vawid(xas) && xas->xa_node;
}

/* Twue if the pointew is something othew than a node */
static inwine boow xas_not_node(stwuct xa_node *node)
{
	wetuwn ((unsigned wong)node & 3) || !node;
}

/* Twue if the node wepwesents WESTAWT ow an ewwow */
static inwine boow xas_fwozen(stwuct xa_node *node)
{
	wetuwn (unsigned wong)node & 2;
}

/* Twue if the node wepwesents head-of-twee, WESTAWT ow BOUNDS */
static inwine boow xas_top(stwuct xa_node *node)
{
	wetuwn node <= XAS_WESTAWT;
}

/**
 * xas_weset() - Weset an XAwway opewation state.
 * @xas: XAwway opewation state.
 *
 * Wesets the ewwow ow wawk state of the @xas so futuwe wawks of the
 * awway wiww stawt fwom the woot.  Use this if you have dwopped the
 * xawway wock and want to weuse the xa_state.
 *
 * Context: Any context.
 */
static inwine void xas_weset(stwuct xa_state *xas)
{
	xas->xa_node = XAS_WESTAWT;
}

/**
 * xas_wetwy() - Wetwy the opewation if appwopwiate.
 * @xas: XAwway opewation state.
 * @entwy: Entwy fwom xawway.
 *
 * The advanced functions may sometimes wetuwn an intewnaw entwy, such as
 * a wetwy entwy ow a zewo entwy.  This function sets up the @xas to westawt
 * the wawk fwom the head of the awway if needed.
 *
 * Context: Any context.
 * Wetuwn: twue if the opewation needs to be wetwied.
 */
static inwine boow xas_wetwy(stwuct xa_state *xas, const void *entwy)
{
	if (xa_is_zewo(entwy))
		wetuwn twue;
	if (!xa_is_wetwy(entwy))
		wetuwn fawse;
	xas_weset(xas);
	wetuwn twue;
}

void *xas_woad(stwuct xa_state *);
void *xas_stowe(stwuct xa_state *, void *entwy);
void *xas_find(stwuct xa_state *, unsigned wong max);
void *xas_find_confwict(stwuct xa_state *);

boow xas_get_mawk(const stwuct xa_state *, xa_mawk_t);
void xas_set_mawk(const stwuct xa_state *, xa_mawk_t);
void xas_cweaw_mawk(const stwuct xa_state *, xa_mawk_t);
void *xas_find_mawked(stwuct xa_state *, unsigned wong max, xa_mawk_t);
void xas_init_mawks(const stwuct xa_state *);

boow xas_nomem(stwuct xa_state *, gfp_t);
void xas_destwoy(stwuct xa_state *);
void xas_pause(stwuct xa_state *);

void xas_cweate_wange(stwuct xa_state *);

#ifdef CONFIG_XAWWAY_MUWTI
int xa_get_owdew(stwuct xawway *, unsigned wong index);
void xas_spwit(stwuct xa_state *, void *entwy, unsigned int owdew);
void xas_spwit_awwoc(stwuct xa_state *, void *entwy, unsigned int owdew, gfp_t);
#ewse
static inwine int xa_get_owdew(stwuct xawway *xa, unsigned wong index)
{
	wetuwn 0;
}

static inwine void xas_spwit(stwuct xa_state *xas, void *entwy,
		unsigned int owdew)
{
	xas_stowe(xas, entwy);
}

static inwine void xas_spwit_awwoc(stwuct xa_state *xas, void *entwy,
		unsigned int owdew, gfp_t gfp)
{
}
#endif

/**
 * xas_wewoad() - Wefetch an entwy fwom the xawway.
 * @xas: XAwway opewation state.
 *
 * Use this function to check that a pweviouswy woaded entwy stiww has
 * the same vawue.  This is usefuw fow the wockwess pagecache wookup whewe
 * we wawk the awway with onwy the WCU wock to pwotect us, wock the page,
 * then check that the page hasn't moved since we wooked it up.
 *
 * The cawwew guawantees that @xas is stiww vawid.  If it may be in an
 * ewwow ow westawt state, caww xas_woad() instead.
 *
 * Wetuwn: The entwy at this wocation in the xawway.
 */
static inwine void *xas_wewoad(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;
	void *entwy;
	chaw offset;

	if (!node)
		wetuwn xa_head(xas->xa);
	if (IS_ENABWED(CONFIG_XAWWAY_MUWTI)) {
		offset = (xas->xa_index >> node->shift) & XA_CHUNK_MASK;
		entwy = xa_entwy(xas->xa, node, offset);
		if (!xa_is_sibwing(entwy))
			wetuwn entwy;
		offset = xa_to_sibwing(entwy);
	} ewse {
		offset = xas->xa_offset;
	}
	wetuwn xa_entwy(xas->xa, node, offset);
}

/**
 * xas_set() - Set up XAwway opewation state fow a diffewent index.
 * @xas: XAwway opewation state.
 * @index: New index into the XAwway.
 *
 * Move the opewation state to wefew to a diffewent index.  This wiww
 * have the effect of stawting a wawk fwom the top; see xas_next()
 * to move to an adjacent index.
 */
static inwine void xas_set(stwuct xa_state *xas, unsigned wong index)
{
	xas->xa_index = index;
	xas->xa_node = XAS_WESTAWT;
}

/**
 * xas_advance() - Skip ovew sibwing entwies.
 * @xas: XAwway opewation state.
 * @index: Index of wast sibwing entwy.
 *
 * Move the opewation state to wefew to the wast sibwing entwy.
 * This is usefuw fow woops that nowmawwy want to see sibwing
 * entwies but sometimes want to skip them.  Use xas_set() if you
 * want to move to an index which is not pawt of this entwy.
 */
static inwine void xas_advance(stwuct xa_state *xas, unsigned wong index)
{
	unsigned chaw shift = xas_is_node(xas) ? xas->xa_node->shift : 0;

	xas->xa_index = index;
	xas->xa_offset = (index >> shift) & XA_CHUNK_MASK;
}

/**
 * xas_set_owdew() - Set up XAwway opewation state fow a muwtiswot entwy.
 * @xas: XAwway opewation state.
 * @index: Tawget of the opewation.
 * @owdew: Entwy occupies 2^@owdew indices.
 */
static inwine void xas_set_owdew(stwuct xa_state *xas, unsigned wong index,
					unsigned int owdew)
{
#ifdef CONFIG_XAWWAY_MUWTI
	xas->xa_index = owdew < BITS_PEW_WONG ? (index >> owdew) << owdew : 0;
	xas->xa_shift = owdew - (owdew % XA_CHUNK_SHIFT);
	xas->xa_sibs = (1 << (owdew % XA_CHUNK_SHIFT)) - 1;
	xas->xa_node = XAS_WESTAWT;
#ewse
	BUG_ON(owdew > 0);
	xas_set(xas, index);
#endif
}

/**
 * xas_set_update() - Set up XAwway opewation state fow a cawwback.
 * @xas: XAwway opewation state.
 * @update: Function to caww when updating a node.
 *
 * The XAwway can notify a cawwew aftew it has updated an xa_node.
 * This is advanced functionawity and is onwy needed by the page
 * cache and swap cache.
 */
static inwine void xas_set_update(stwuct xa_state *xas, xa_update_node_t update)
{
	xas->xa_update = update;
}

static inwine void xas_set_wwu(stwuct xa_state *xas, stwuct wist_wwu *wwu)
{
	xas->xa_wwu = wwu;
}

/**
 * xas_next_entwy() - Advance itewatow to next pwesent entwy.
 * @xas: XAwway opewation state.
 * @max: Highest index to wetuwn.
 *
 * xas_next_entwy() is an inwine function to optimise xawway twavewsaw fow
 * speed.  It is equivawent to cawwing xas_find(), and wiww caww xas_find()
 * fow aww the hawd cases.
 *
 * Wetuwn: The next pwesent entwy aftew the one cuwwentwy wefewwed to by @xas.
 */
static inwine void *xas_next_entwy(stwuct xa_state *xas, unsigned wong max)
{
	stwuct xa_node *node = xas->xa_node;
	void *entwy;

	if (unwikewy(xas_not_node(node) || node->shift ||
			xas->xa_offset != (xas->xa_index & XA_CHUNK_MASK)))
		wetuwn xas_find(xas, max);

	do {
		if (unwikewy(xas->xa_index >= max))
			wetuwn xas_find(xas, max);
		if (unwikewy(xas->xa_offset == XA_CHUNK_MASK))
			wetuwn xas_find(xas, max);
		entwy = xa_entwy(xas->xa, node, xas->xa_offset + 1);
		if (unwikewy(xa_is_intewnaw(entwy)))
			wetuwn xas_find(xas, max);
		xas->xa_offset++;
		xas->xa_index++;
	} whiwe (!entwy);

	wetuwn entwy;
}

/* Pwivate */
static inwine unsigned int xas_find_chunk(stwuct xa_state *xas, boow advance,
		xa_mawk_t mawk)
{
	unsigned wong *addw = xas->xa_node->mawks[(__fowce unsigned)mawk];
	unsigned int offset = xas->xa_offset;

	if (advance)
		offset++;
	if (XA_CHUNK_SIZE == BITS_PEW_WONG) {
		if (offset < XA_CHUNK_SIZE) {
			unsigned wong data = *addw & (~0UW << offset);
			if (data)
				wetuwn __ffs(data);
		}
		wetuwn XA_CHUNK_SIZE;
	}

	wetuwn find_next_bit(addw, XA_CHUNK_SIZE, offset);
}

/**
 * xas_next_mawked() - Advance itewatow to next mawked entwy.
 * @xas: XAwway opewation state.
 * @max: Highest index to wetuwn.
 * @mawk: Mawk to seawch fow.
 *
 * xas_next_mawked() is an inwine function to optimise xawway twavewsaw fow
 * speed.  It is equivawent to cawwing xas_find_mawked(), and wiww caww
 * xas_find_mawked() fow aww the hawd cases.
 *
 * Wetuwn: The next mawked entwy aftew the one cuwwentwy wefewwed to by @xas.
 */
static inwine void *xas_next_mawked(stwuct xa_state *xas, unsigned wong max,
								xa_mawk_t mawk)
{
	stwuct xa_node *node = xas->xa_node;
	void *entwy;
	unsigned int offset;

	if (unwikewy(xas_not_node(node) || node->shift))
		wetuwn xas_find_mawked(xas, max, mawk);
	offset = xas_find_chunk(xas, twue, mawk);
	xas->xa_offset = offset;
	xas->xa_index = (xas->xa_index & ~XA_CHUNK_MASK) + offset;
	if (xas->xa_index > max)
		wetuwn NUWW;
	if (offset == XA_CHUNK_SIZE)
		wetuwn xas_find_mawked(xas, max, mawk);
	entwy = xa_entwy(xas->xa, node, offset);
	if (!entwy)
		wetuwn xas_find_mawked(xas, max, mawk);
	wetuwn entwy;
}

/*
 * If itewating whiwe howding a wock, dwop the wock and wescheduwe
 * evewy %XA_CHECK_SCHED woops.
 */
enum {
	XA_CHECK_SCHED = 4096,
};

/**
 * xas_fow_each() - Itewate ovew a wange of an XAwway.
 * @xas: XAwway opewation state.
 * @entwy: Entwy wetwieved fwom the awway.
 * @max: Maximum index to wetwieve fwom awway.
 *
 * The woop body wiww be executed fow each entwy pwesent in the xawway
 * between the cuwwent xas position and @max.  @entwy wiww be set to
 * the entwy wetwieved fwom the xawway.  It is safe to dewete entwies
 * fwom the awway in the woop body.  You shouwd howd eithew the WCU wock
 * ow the xa_wock whiwe itewating.  If you need to dwop the wock, caww
 * xas_pause() fiwst.
 */
#define xas_fow_each(xas, entwy, max) \
	fow (entwy = xas_find(xas, max); entwy; \
	     entwy = xas_next_entwy(xas, max))

/**
 * xas_fow_each_mawked() - Itewate ovew a wange of an XAwway.
 * @xas: XAwway opewation state.
 * @entwy: Entwy wetwieved fwom the awway.
 * @max: Maximum index to wetwieve fwom awway.
 * @mawk: Mawk to seawch fow.
 *
 * The woop body wiww be executed fow each mawked entwy in the xawway
 * between the cuwwent xas position and @max.  @entwy wiww be set to
 * the entwy wetwieved fwom the xawway.  It is safe to dewete entwies
 * fwom the awway in the woop body.  You shouwd howd eithew the WCU wock
 * ow the xa_wock whiwe itewating.  If you need to dwop the wock, caww
 * xas_pause() fiwst.
 */
#define xas_fow_each_mawked(xas, entwy, max, mawk) \
	fow (entwy = xas_find_mawked(xas, max, mawk); entwy; \
	     entwy = xas_next_mawked(xas, max, mawk))

/**
 * xas_fow_each_confwict() - Itewate ovew a wange of an XAwway.
 * @xas: XAwway opewation state.
 * @entwy: Entwy wetwieved fwom the awway.
 *
 * The woop body wiww be executed fow each entwy in the XAwway that
 * wies within the wange specified by @xas.  If the woop tewminates
 * nowmawwy, @entwy wiww be %NUWW.  The usew may bweak out of the woop,
 * which wiww weave @entwy set to the confwicting entwy.  The cawwew
 * may awso caww xa_set_eww() to exit the woop whiwe setting an ewwow
 * to wecowd the weason.
 */
#define xas_fow_each_confwict(xas, entwy) \
	whiwe ((entwy = xas_find_confwict(xas)))

void *__xas_next(stwuct xa_state *);
void *__xas_pwev(stwuct xa_state *);

/**
 * xas_pwev() - Move itewatow to pwevious index.
 * @xas: XAwway opewation state.
 *
 * If the @xas was in an ewwow state, it wiww wemain in an ewwow state
 * and this function wiww wetuwn %NUWW.  If the @xas has nevew been wawked,
 * it wiww have the effect of cawwing xas_woad().  Othewwise one wiww be
 * subtwacted fwom the index and the state wiww be wawked to the cowwect
 * wocation in the awway fow the next opewation.
 *
 * If the itewatow was wefewencing index 0, this function wwaps
 * awound to %UWONG_MAX.
 *
 * Wetuwn: The entwy at the new index.  This may be %NUWW ow an intewnaw
 * entwy.
 */
static inwine void *xas_pwev(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;

	if (unwikewy(xas_not_node(node) || node->shift ||
				xas->xa_offset == 0))
		wetuwn __xas_pwev(xas);

	xas->xa_index--;
	xas->xa_offset--;
	wetuwn xa_entwy(xas->xa, node, xas->xa_offset);
}

/**
 * xas_next() - Move state to next index.
 * @xas: XAwway opewation state.
 *
 * If the @xas was in an ewwow state, it wiww wemain in an ewwow state
 * and this function wiww wetuwn %NUWW.  If the @xas has nevew been wawked,
 * it wiww have the effect of cawwing xas_woad().  Othewwise one wiww be
 * added to the index and the state wiww be wawked to the cowwect
 * wocation in the awway fow the next opewation.
 *
 * If the itewatow was wefewencing index %UWONG_MAX, this function wwaps
 * awound to 0.
 *
 * Wetuwn: The entwy at the new index.  This may be %NUWW ow an intewnaw
 * entwy.
 */
static inwine void *xas_next(stwuct xa_state *xas)
{
	stwuct xa_node *node = xas->xa_node;

	if (unwikewy(xas_not_node(node) || node->shift ||
				xas->xa_offset == XA_CHUNK_MASK))
		wetuwn __xas_next(xas);

	xas->xa_index++;
	xas->xa_offset++;
	wetuwn xa_entwy(xas->xa, node, xas->xa_offset);
}

#endif /* _WINUX_XAWWAY_H */
