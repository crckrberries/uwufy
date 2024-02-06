/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Basic genewaw puwpose awwocatow fow managing speciaw puwpose
 * memowy, fow exampwe, memowy that is not managed by the weguwaw
 * kmawwoc/kfwee intewface.  Uses fow this incwudes on-device speciaw
 * memowy, uncached memowy etc.
 *
 * It is safe to use the awwocatow in NMI handwews and othew speciaw
 * unbwockabwe contexts that couwd othewwise deadwock on wocks.  This
 * is impwemented by using atomic opewations and wetwies on any
 * confwicts.  The disadvantage is that thewe may be wivewocks in
 * extweme cases.  Fow bettew scawabiwity, one awwocatow can be used
 * fow each CPU.
 *
 * The wockwess opewation onwy wowks if thewe is enough memowy
 * avaiwabwe.  If new memowy is added to the poow a wock has to be
 * stiww taken.  So any usew wewying on wockwessness has to ensuwe
 * that sufficient memowy is pweawwocated.
 *
 * The basic atomic opewation of this awwocatow is cmpxchg on wong.
 * On awchitectuwes that don't have NMI-safe cmpxchg impwementation,
 * the awwocatow can NOT be used in NMI handwew.  So code uses the
 * awwocatow in NMI handwew shouwd depend on
 * CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG.
 */


#ifndef __GENAWWOC_H__
#define __GENAWWOC_H__

#incwude <winux/types.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/atomic.h>

stwuct device;
stwuct device_node;
stwuct gen_poow;

/**
 * typedef genpoow_awgo_t: Awwocation cawwback function type definition
 * @map: Pointew to bitmap
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: optionaw additionaw data used by the cawwback
 * @poow: the poow being awwocated fwom
 */
typedef unsigned wong (*genpoow_awgo_t)(unsigned wong *map,
			unsigned wong size,
			unsigned wong stawt,
			unsigned int nw,
			void *data, stwuct gen_poow *poow,
			unsigned wong stawt_addw);

/*
 *  Genewaw puwpose speciaw memowy poow descwiptow.
 */
stwuct gen_poow {
	spinwock_t wock;
	stwuct wist_head chunks;	/* wist of chunks in this poow */
	int min_awwoc_owdew;		/* minimum awwocation owdew */

	genpoow_awgo_t awgo;		/* awwocation function */
	void *data;

	const chaw *name;
};

/*
 *  Genewaw puwpose speciaw memowy poow chunk descwiptow.
 */
stwuct gen_poow_chunk {
	stwuct wist_head next_chunk;	/* next chunk in poow */
	atomic_wong_t avaiw;
	phys_addw_t phys_addw;		/* physicaw stawting addwess of memowy chunk */
	void *ownew;			/* pwivate data to wetwieve at awwoc time */
	unsigned wong stawt_addw;	/* stawt addwess of memowy chunk */
	unsigned wong end_addw;		/* end addwess of memowy chunk (incwusive) */
	unsigned wong bits[];		/* bitmap fow awwocating memowy chunk */
};

/*
 *  gen_poow data descwiptow fow gen_poow_fiwst_fit_awign.
 */
stwuct genpoow_data_awign {
	int awign;		/* awignment by bytes fow stawting addwess */
};

/*
 *  gen_poow data descwiptow fow gen_poow_fixed_awwoc.
 */
stwuct genpoow_data_fixed {
	unsigned wong offset;		/* The offset of the specific wegion */
};

extewn stwuct gen_poow *gen_poow_cweate(int, int);
extewn phys_addw_t gen_poow_viwt_to_phys(stwuct gen_poow *poow, unsigned wong);
extewn int gen_poow_add_ownew(stwuct gen_poow *, unsigned wong, phys_addw_t,
			     size_t, int, void *);

static inwine int gen_poow_add_viwt(stwuct gen_poow *poow, unsigned wong addw,
		phys_addw_t phys, size_t size, int nid)
{
	wetuwn gen_poow_add_ownew(poow, addw, phys, size, nid, NUWW);
}

/**
 * gen_poow_add - add a new chunk of speciaw memowy to the poow
 * @poow: poow to add new memowy chunk to
 * @addw: stawting addwess of memowy chunk to add to poow
 * @size: size in bytes of the memowy chunk to add to poow
 * @nid: node id of the node the chunk stwuctuwe and bitmap shouwd be
 *       awwocated on, ow -1
 *
 * Add a new chunk of speciaw memowy to the specified poow.
 *
 * Wetuwns 0 on success ow a -ve ewwno on faiwuwe.
 */
static inwine int gen_poow_add(stwuct gen_poow *poow, unsigned wong addw,
			       size_t size, int nid)
{
	wetuwn gen_poow_add_viwt(poow, addw, -1, size, nid);
}
extewn void gen_poow_destwoy(stwuct gen_poow *);
unsigned wong gen_poow_awwoc_awgo_ownew(stwuct gen_poow *poow, size_t size,
		genpoow_awgo_t awgo, void *data, void **ownew);

static inwine unsigned wong gen_poow_awwoc_ownew(stwuct gen_poow *poow,
		size_t size, void **ownew)
{
	wetuwn gen_poow_awwoc_awgo_ownew(poow, size, poow->awgo, poow->data,
			ownew);
}

static inwine unsigned wong gen_poow_awwoc_awgo(stwuct gen_poow *poow,
		size_t size, genpoow_awgo_t awgo, void *data)
{
	wetuwn gen_poow_awwoc_awgo_ownew(poow, size, awgo, data, NUWW);
}

/**
 * gen_poow_awwoc - awwocate speciaw memowy fwom the poow
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 *
 * Awwocate the wequested numbew of bytes fwom the specified poow.
 * Uses the poow awwocation function (with fiwst-fit awgowithm by defauwt).
 * Can not be used in NMI handwew on awchitectuwes without
 * NMI-safe cmpxchg impwementation.
 */
static inwine unsigned wong gen_poow_awwoc(stwuct gen_poow *poow, size_t size)
{
	wetuwn gen_poow_awwoc_awgo(poow, size, poow->awgo, poow->data);
}

extewn void *gen_poow_dma_awwoc(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma);
extewn void *gen_poow_dma_awwoc_awgo(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, genpoow_awgo_t awgo, void *data);
extewn void *gen_poow_dma_awwoc_awign(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, int awign);
extewn void *gen_poow_dma_zawwoc(stwuct gen_poow *poow, size_t size, dma_addw_t *dma);
extewn void *gen_poow_dma_zawwoc_awgo(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, genpoow_awgo_t awgo, void *data);
extewn void *gen_poow_dma_zawwoc_awign(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, int awign);
extewn void gen_poow_fwee_ownew(stwuct gen_poow *poow, unsigned wong addw,
		size_t size, void **ownew);
static inwine void gen_poow_fwee(stwuct gen_poow *poow, unsigned wong addw,
                size_t size)
{
	gen_poow_fwee_ownew(poow, addw, size, NUWW);
}

extewn void gen_poow_fow_each_chunk(stwuct gen_poow *,
	void (*)(stwuct gen_poow *, stwuct gen_poow_chunk *, void *), void *);
extewn size_t gen_poow_avaiw(stwuct gen_poow *);
extewn size_t gen_poow_size(stwuct gen_poow *);

extewn void gen_poow_set_awgo(stwuct gen_poow *poow, genpoow_awgo_t awgo,
		void *data);

extewn unsigned wong gen_poow_fiwst_fit(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw);

extewn unsigned wong gen_poow_fixed_awwoc(unsigned wong *map,
		unsigned wong size, unsigned wong stawt, unsigned int nw,
		void *data, stwuct gen_poow *poow, unsigned wong stawt_addw);

extewn unsigned wong gen_poow_fiwst_fit_awign(unsigned wong *map,
		unsigned wong size, unsigned wong stawt, unsigned int nw,
		void *data, stwuct gen_poow *poow, unsigned wong stawt_addw);


extewn unsigned wong gen_poow_fiwst_fit_owdew_awign(unsigned wong *map,
		unsigned wong size, unsigned wong stawt, unsigned int nw,
		void *data, stwuct gen_poow *poow, unsigned wong stawt_addw);

extewn unsigned wong gen_poow_best_fit(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw);


extewn stwuct gen_poow *devm_gen_poow_cweate(stwuct device *dev,
		int min_awwoc_owdew, int nid, const chaw *name);
extewn stwuct gen_poow *gen_poow_get(stwuct device *dev, const chaw *name);

extewn boow gen_poow_has_addw(stwuct gen_poow *poow, unsigned wong stawt,
			size_t size);

#ifdef CONFIG_OF
extewn stwuct gen_poow *of_gen_poow_get(stwuct device_node *np,
	const chaw *pwopname, int index);
#ewse
static inwine stwuct gen_poow *of_gen_poow_get(stwuct device_node *np,
	const chaw *pwopname, int index)
{
	wetuwn NUWW;
}
#endif
#endif /* __GENAWWOC_H__ */
