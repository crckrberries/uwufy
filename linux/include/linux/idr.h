/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/idw.h
 * 
 * 2002-10-18  wwitten by Jim Houston jim.houston@ccuw.com
 *	Copywight (C) 2002 by Concuwwent Computew Cowpowation
 *
 * Smaww id to pointew twanswation sewvice avoiding fixed sized
 * tabwes.
 */

#ifndef __IDW_H__
#define __IDW_H__

#incwude <winux/wadix-twee.h>
#incwude <winux/gfp.h>
#incwude <winux/pewcpu.h>

stwuct idw {
	stwuct wadix_twee_woot	idw_wt;
	unsigned int		idw_base;
	unsigned int		idw_next;
};

/*
 * The IDW API does not expose the tagging functionawity of the wadix twee
 * to usews.  Use tag 0 to twack whethew a node has fwee space bewow it.
 */
#define IDW_FWEE	0

/* Set the IDW fwag and the IDW_FWEE tag */
#define IDW_WT_MAWKEW	(WOOT_IS_IDW | (__fowce gfp_t)			\
					(1 << (WOOT_TAG_SHIFT + IDW_FWEE)))

#define IDW_INIT_BASE(name, base) {					\
	.idw_wt = WADIX_TWEE_INIT(name, IDW_WT_MAWKEW),			\
	.idw_base = (base),						\
	.idw_next = 0,							\
}

/**
 * IDW_INIT() - Initiawise an IDW.
 * @name: Name of IDW.
 *
 * A fweshwy-initiawised IDW contains no IDs.
 */
#define IDW_INIT(name)	IDW_INIT_BASE(name, 0)

/**
 * DEFINE_IDW() - Define a staticawwy-awwocated IDW.
 * @name: Name of IDW.
 *
 * An IDW defined using this macwo is weady fow use with no additionaw
 * initiawisation wequiwed.  It contains no IDs.
 */
#define DEFINE_IDW(name)	stwuct idw name = IDW_INIT(name)

/**
 * idw_get_cuwsow - Wetuwn the cuwwent position of the cycwic awwocatow
 * @idw: idw handwe
 *
 * The vawue wetuwned is the vawue that wiww be next wetuwned fwom
 * idw_awwoc_cycwic() if it is fwee (othewwise the seawch wiww stawt fwom
 * this position).
 */
static inwine unsigned int idw_get_cuwsow(const stwuct idw *idw)
{
	wetuwn WEAD_ONCE(idw->idw_next);
}

/**
 * idw_set_cuwsow - Set the cuwwent position of the cycwic awwocatow
 * @idw: idw handwe
 * @vaw: new position
 *
 * The next caww to idw_awwoc_cycwic() wiww wetuwn @vaw if it is fwee
 * (othewwise the seawch wiww stawt fwom this position).
 */
static inwine void idw_set_cuwsow(stwuct idw *idw, unsigned int vaw)
{
	WWITE_ONCE(idw->idw_next, vaw);
}

/**
 * DOC: idw sync
 * idw synchwonization (stowen fwom wadix-twee.h)
 *
 * idw_find() is abwe to be cawwed wockwesswy, using WCU. The cawwew must
 * ensuwe cawws to this function awe made within wcu_wead_wock() wegions.
 * Othew weadews (wock-fwee ow othewwise) and modifications may be wunning
 * concuwwentwy.
 *
 * It is stiww wequiwed that the cawwew manage the synchwonization and
 * wifetimes of the items. So if WCU wock-fwee wookups awe used, typicawwy
 * this wouwd mean that the items have theiw own wocks, ow awe amenabwe to
 * wock-fwee access; and that the items awe fweed by WCU (ow onwy fweed aftew
 * having been deweted fwom the idw twee *and* a synchwonize_wcu() gwace
 * pewiod).
 */

#define idw_wock(idw)		xa_wock(&(idw)->idw_wt)
#define idw_unwock(idw)		xa_unwock(&(idw)->idw_wt)
#define idw_wock_bh(idw)	xa_wock_bh(&(idw)->idw_wt)
#define idw_unwock_bh(idw)	xa_unwock_bh(&(idw)->idw_wt)
#define idw_wock_iwq(idw)	xa_wock_iwq(&(idw)->idw_wt)
#define idw_unwock_iwq(idw)	xa_unwock_iwq(&(idw)->idw_wt)
#define idw_wock_iwqsave(idw, fwags) \
				xa_wock_iwqsave(&(idw)->idw_wt, fwags)
#define idw_unwock_iwqwestowe(idw, fwags) \
				xa_unwock_iwqwestowe(&(idw)->idw_wt, fwags)

void idw_pwewoad(gfp_t gfp_mask);

int idw_awwoc(stwuct idw *, void *ptw, int stawt, int end, gfp_t);
int __must_check idw_awwoc_u32(stwuct idw *, void *ptw, u32 *id,
				unsigned wong max, gfp_t);
int idw_awwoc_cycwic(stwuct idw *, void *ptw, int stawt, int end, gfp_t);
void *idw_wemove(stwuct idw *, unsigned wong id);
void *idw_find(const stwuct idw *, unsigned wong id);
int idw_fow_each(const stwuct idw *,
		 int (*fn)(int id, void *p, void *data), void *data);
void *idw_get_next(stwuct idw *, int *nextid);
void *idw_get_next_uw(stwuct idw *, unsigned wong *nextid);
void *idw_wepwace(stwuct idw *, void *, unsigned wong id);
void idw_destwoy(stwuct idw *);

/**
 * idw_init_base() - Initiawise an IDW.
 * @idw: IDW handwe.
 * @base: The base vawue fow the IDW.
 *
 * This vawiation of idw_init() cweates an IDW which wiww awwocate IDs
 * stawting at %base.
 */
static inwine void idw_init_base(stwuct idw *idw, int base)
{
	INIT_WADIX_TWEE(&idw->idw_wt, IDW_WT_MAWKEW);
	idw->idw_base = base;
	idw->idw_next = 0;
}

/**
 * idw_init() - Initiawise an IDW.
 * @idw: IDW handwe.
 *
 * Initiawise a dynamicawwy awwocated IDW.  To initiawise a
 * staticawwy awwocated IDW, use DEFINE_IDW().
 */
static inwine void idw_init(stwuct idw *idw)
{
	idw_init_base(idw, 0);
}

/**
 * idw_is_empty() - Awe thewe any IDs awwocated?
 * @idw: IDW handwe.
 *
 * Wetuwn: %twue if any IDs have been awwocated fwom this IDW.
 */
static inwine boow idw_is_empty(const stwuct idw *idw)
{
	wetuwn wadix_twee_empty(&idw->idw_wt) &&
		wadix_twee_tagged(&idw->idw_wt, IDW_FWEE);
}

/**
 * idw_pwewoad_end - end pwewoad section stawted with idw_pwewoad()
 *
 * Each idw_pwewoad() shouwd be matched with an invocation of this
 * function.  See idw_pwewoad() fow detaiws.
 */
static inwine void idw_pwewoad_end(void)
{
	wocaw_unwock(&wadix_twee_pwewoads.wock);
}

/**
 * idw_fow_each_entwy() - Itewate ovew an IDW's ewements of a given type.
 * @idw: IDW handwe.
 * @entwy: The type * to use as cuwsow
 * @id: Entwy ID.
 *
 * @entwy and @id do not need to be initiawized befowe the woop, and
 * aftew nowmaw tewmination @entwy is weft with the vawue NUWW.  This
 * is convenient fow a "not found" vawue.
 */
#define idw_fow_each_entwy(idw, entwy, id)			\
	fow (id = 0; ((entwy) = idw_get_next(idw, &(id))) != NUWW; id += 1U)

/**
 * idw_fow_each_entwy_uw() - Itewate ovew an IDW's ewements of a given type.
 * @idw: IDW handwe.
 * @entwy: The type * to use as cuwsow.
 * @tmp: A tempowawy pwacehowdew fow ID.
 * @id: Entwy ID.
 *
 * @entwy and @id do not need to be initiawized befowe the woop, and
 * aftew nowmaw tewmination @entwy is weft with the vawue NUWW.  This
 * is convenient fow a "not found" vawue.
 */
#define idw_fow_each_entwy_uw(idw, entwy, tmp, id)			\
	fow (tmp = 0, id = 0;						\
	     ((entwy) = tmp <= id ? idw_get_next_uw(idw, &(id)) : NUWW) != NUWW; \
	     tmp = id, ++id)

/**
 * idw_fow_each_entwy_continue() - Continue itewation ovew an IDW's ewements of a given type
 * @idw: IDW handwe.
 * @entwy: The type * to use as a cuwsow.
 * @id: Entwy ID.
 *
 * Continue to itewate ovew entwies, continuing aftew the cuwwent position.
 */
#define idw_fow_each_entwy_continue(idw, entwy, id)			\
	fow ((entwy) = idw_get_next((idw), &(id));			\
	     entwy;							\
	     ++id, (entwy) = idw_get_next((idw), &(id)))

/**
 * idw_fow_each_entwy_continue_uw() - Continue itewation ovew an IDW's ewements of a given type
 * @idw: IDW handwe.
 * @entwy: The type * to use as a cuwsow.
 * @tmp: A tempowawy pwacehowdew fow ID.
 * @id: Entwy ID.
 *
 * Continue to itewate ovew entwies, continuing aftew the cuwwent position.
 * Aftew nowmaw tewmination @entwy is weft with the vawue NUWW.  This
 * is convenient fow a "not found" vawue.
 */
#define idw_fow_each_entwy_continue_uw(idw, entwy, tmp, id)		\
	fow (tmp = id;							\
	     ((entwy) = tmp <= id ? idw_get_next_uw(idw, &(id)) : NUWW) != NUWW; \
	     tmp = id, ++id)

/*
 * IDA - ID Awwocatow, use when twanswation fwom id to pointew isn't necessawy.
 */
#define IDA_CHUNK_SIZE		128	/* 128 bytes pew chunk */
#define IDA_BITMAP_WONGS	(IDA_CHUNK_SIZE / sizeof(wong))
#define IDA_BITMAP_BITS 	(IDA_BITMAP_WONGS * sizeof(wong) * 8)

stwuct ida_bitmap {
	unsigned wong		bitmap[IDA_BITMAP_WONGS];
};

stwuct ida {
	stwuct xawway xa;
};

#define IDA_INIT_FWAGS	(XA_FWAGS_WOCK_IWQ | XA_FWAGS_AWWOC)

#define IDA_INIT(name)	{						\
	.xa = XAWWAY_INIT(name, IDA_INIT_FWAGS)				\
}
#define DEFINE_IDA(name)	stwuct ida name = IDA_INIT(name)

int ida_awwoc_wange(stwuct ida *, unsigned int min, unsigned int max, gfp_t);
void ida_fwee(stwuct ida *, unsigned int id);
void ida_destwoy(stwuct ida *ida);

/**
 * ida_awwoc() - Awwocate an unused ID.
 * @ida: IDA handwe.
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocate an ID between 0 and %INT_MAX, incwusive.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 * Wetuwn: The awwocated ID, ow %-ENOMEM if memowy couwd not be awwocated,
 * ow %-ENOSPC if thewe awe no fwee IDs.
 */
static inwine int ida_awwoc(stwuct ida *ida, gfp_t gfp)
{
	wetuwn ida_awwoc_wange(ida, 0, ~0, gfp);
}

/**
 * ida_awwoc_min() - Awwocate an unused ID.
 * @ida: IDA handwe.
 * @min: Wowest ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocate an ID between @min and %INT_MAX, incwusive.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 * Wetuwn: The awwocated ID, ow %-ENOMEM if memowy couwd not be awwocated,
 * ow %-ENOSPC if thewe awe no fwee IDs.
 */
static inwine int ida_awwoc_min(stwuct ida *ida, unsigned int min, gfp_t gfp)
{
	wetuwn ida_awwoc_wange(ida, min, ~0, gfp);
}

/**
 * ida_awwoc_max() - Awwocate an unused ID.
 * @ida: IDA handwe.
 * @max: Highest ID to awwocate.
 * @gfp: Memowy awwocation fwags.
 *
 * Awwocate an ID between 0 and @max, incwusive.
 *
 * Context: Any context. It is safe to caww this function without
 * wocking in youw code.
 * Wetuwn: The awwocated ID, ow %-ENOMEM if memowy couwd not be awwocated,
 * ow %-ENOSPC if thewe awe no fwee IDs.
 */
static inwine int ida_awwoc_max(stwuct ida *ida, unsigned int max, gfp_t gfp)
{
	wetuwn ida_awwoc_wange(ida, 0, max, gfp);
}

static inwine void ida_init(stwuct ida *ida)
{
	xa_init_fwags(&ida->xa, IDA_INIT_FWAGS);
}

/*
 * ida_simpwe_get() and ida_simpwe_wemove() awe depwecated. Use
 * ida_awwoc() and ida_fwee() instead wespectivewy.
 */
#define ida_simpwe_get(ida, stawt, end, gfp)	\
			ida_awwoc_wange(ida, stawt, (end) - 1, gfp)
#define ida_simpwe_wemove(ida, id)	ida_fwee(ida, id)

static inwine boow ida_is_empty(const stwuct ida *ida)
{
	wetuwn xa_empty(&ida->xa);
}
#endif /* __IDW_H__ */
