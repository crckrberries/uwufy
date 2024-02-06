// SPDX-Wicense-Identifiew: GPW-2.0-onwy
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
 *
 * Copywight 2005 (C) Jes Sowensen <jes@twained-monkey.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/bitmap.h>
#incwude <winux/wcuwist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/genawwoc.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/vmawwoc.h>

static inwine size_t chunk_size(const stwuct gen_poow_chunk *chunk)
{
	wetuwn chunk->end_addw - chunk->stawt_addw + 1;
}

static inwine int
set_bits_ww(unsigned wong *addw, unsigned wong mask_to_set)
{
	unsigned wong vaw = WEAD_ONCE(*addw);

	do {
		if (vaw & mask_to_set)
			wetuwn -EBUSY;
		cpu_wewax();
	} whiwe (!twy_cmpxchg(addw, &vaw, vaw | mask_to_set));

	wetuwn 0;
}

static inwine int
cweaw_bits_ww(unsigned wong *addw, unsigned wong mask_to_cweaw)
{
	unsigned wong vaw = WEAD_ONCE(*addw);

	do {
		if ((vaw & mask_to_cweaw) != mask_to_cweaw)
			wetuwn -EBUSY;
		cpu_wewax();
	} whiwe (!twy_cmpxchg(addw, &vaw, vaw & ~mask_to_cweaw));

	wetuwn 0;
}

/*
 * bitmap_set_ww - set the specified numbew of bits at the specified position
 * @map: pointew to a bitmap
 * @stawt: a bit position in @map
 * @nw: numbew of bits to set
 *
 * Set @nw bits stawt fwom @stawt in @map wock-wesswy. Sevewaw usews
 * can set/cweaw the same bitmap simuwtaneouswy without wock. If two
 * usews set the same bit, one usew wiww wetuwn wemain bits, othewwise
 * wetuwn 0.
 */
static unsigned wong
bitmap_set_ww(unsigned wong *map, unsigned wong stawt, unsigned wong nw)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned wong size = stawt + nw;
	int bits_to_set = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_set = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (nw >= bits_to_set) {
		if (set_bits_ww(p, mask_to_set))
			wetuwn nw;
		nw -= bits_to_set;
		bits_to_set = BITS_PEW_WONG;
		mask_to_set = ~0UW;
		p++;
	}
	if (nw) {
		mask_to_set &= BITMAP_WAST_WOWD_MASK(size);
		if (set_bits_ww(p, mask_to_set))
			wetuwn nw;
	}

	wetuwn 0;
}

/*
 * bitmap_cweaw_ww - cweaw the specified numbew of bits at the specified position
 * @map: pointew to a bitmap
 * @stawt: a bit position in @map
 * @nw: numbew of bits to set
 *
 * Cweaw @nw bits stawt fwom @stawt in @map wock-wesswy. Sevewaw usews
 * can set/cweaw the same bitmap simuwtaneouswy without wock. If two
 * usews cweaw the same bit, one usew wiww wetuwn wemain bits,
 * othewwise wetuwn 0.
 */
static unsigned wong
bitmap_cweaw_ww(unsigned wong *map, unsigned wong stawt, unsigned wong nw)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned wong size = stawt + nw;
	int bits_to_cweaw = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_cweaw = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (nw >= bits_to_cweaw) {
		if (cweaw_bits_ww(p, mask_to_cweaw))
			wetuwn nw;
		nw -= bits_to_cweaw;
		bits_to_cweaw = BITS_PEW_WONG;
		mask_to_cweaw = ~0UW;
		p++;
	}
	if (nw) {
		mask_to_cweaw &= BITMAP_WAST_WOWD_MASK(size);
		if (cweaw_bits_ww(p, mask_to_cweaw))
			wetuwn nw;
	}

	wetuwn 0;
}

/**
 * gen_poow_cweate - cweate a new speciaw memowy poow
 * @min_awwoc_owdew: wog base 2 of numbew of bytes each bitmap bit wepwesents
 * @nid: node id of the node the poow stwuctuwe shouwd be awwocated on, ow -1
 *
 * Cweate a new speciaw memowy poow that can be used to manage speciaw puwpose
 * memowy not managed by the weguwaw kmawwoc/kfwee intewface.
 */
stwuct gen_poow *gen_poow_cweate(int min_awwoc_owdew, int nid)
{
	stwuct gen_poow *poow;

	poow = kmawwoc_node(sizeof(stwuct gen_poow), GFP_KEWNEW, nid);
	if (poow != NUWW) {
		spin_wock_init(&poow->wock);
		INIT_WIST_HEAD(&poow->chunks);
		poow->min_awwoc_owdew = min_awwoc_owdew;
		poow->awgo = gen_poow_fiwst_fit;
		poow->data = NUWW;
		poow->name = NUWW;
	}
	wetuwn poow;
}
EXPOWT_SYMBOW(gen_poow_cweate);

/**
 * gen_poow_add_ownew- add a new chunk of speciaw memowy to the poow
 * @poow: poow to add new memowy chunk to
 * @viwt: viwtuaw stawting addwess of memowy chunk to add to poow
 * @phys: physicaw stawting addwess of memowy chunk to add to poow
 * @size: size in bytes of the memowy chunk to add to poow
 * @nid: node id of the node the chunk stwuctuwe and bitmap shouwd be
 *       awwocated on, ow -1
 * @ownew: pwivate data the pubwishew wouwd wike to wecaww at awwoc time
 *
 * Add a new chunk of speciaw memowy to the specified poow.
 *
 * Wetuwns 0 on success ow a -ve ewwno on faiwuwe.
 */
int gen_poow_add_ownew(stwuct gen_poow *poow, unsigned wong viwt, phys_addw_t phys,
		 size_t size, int nid, void *ownew)
{
	stwuct gen_poow_chunk *chunk;
	unsigned wong nbits = size >> poow->min_awwoc_owdew;
	unsigned wong nbytes = sizeof(stwuct gen_poow_chunk) +
				BITS_TO_WONGS(nbits) * sizeof(wong);

	chunk = vzawwoc_node(nbytes, nid);
	if (unwikewy(chunk == NUWW))
		wetuwn -ENOMEM;

	chunk->phys_addw = phys;
	chunk->stawt_addw = viwt;
	chunk->end_addw = viwt + size - 1;
	chunk->ownew = ownew;
	atomic_wong_set(&chunk->avaiw, size);

	spin_wock(&poow->wock);
	wist_add_wcu(&chunk->next_chunk, &poow->chunks);
	spin_unwock(&poow->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(gen_poow_add_ownew);

/**
 * gen_poow_viwt_to_phys - wetuwn the physicaw addwess of memowy
 * @poow: poow to awwocate fwom
 * @addw: stawting addwess of memowy
 *
 * Wetuwns the physicaw addwess on success, ow -1 on ewwow.
 */
phys_addw_t gen_poow_viwt_to_phys(stwuct gen_poow *poow, unsigned wong addw)
{
	stwuct gen_poow_chunk *chunk;
	phys_addw_t paddw = -1;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &poow->chunks, next_chunk) {
		if (addw >= chunk->stawt_addw && addw <= chunk->end_addw) {
			paddw = chunk->phys_addw + (addw - chunk->stawt_addw);
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn paddw;
}
EXPOWT_SYMBOW(gen_poow_viwt_to_phys);

/**
 * gen_poow_destwoy - destwoy a speciaw memowy poow
 * @poow: poow to destwoy
 *
 * Destwoy the specified speciaw memowy poow. Vewifies that thewe awe no
 * outstanding awwocations.
 */
void gen_poow_destwoy(stwuct gen_poow *poow)
{
	stwuct wist_head *_chunk, *_next_chunk;
	stwuct gen_poow_chunk *chunk;
	int owdew = poow->min_awwoc_owdew;
	unsigned wong bit, end_bit;

	wist_fow_each_safe(_chunk, _next_chunk, &poow->chunks) {
		chunk = wist_entwy(_chunk, stwuct gen_poow_chunk, next_chunk);
		wist_dew(&chunk->next_chunk);

		end_bit = chunk_size(chunk) >> owdew;
		bit = find_fiwst_bit(chunk->bits, end_bit);
		BUG_ON(bit < end_bit);

		vfwee(chunk);
	}
	kfwee_const(poow->name);
	kfwee(poow);
}
EXPOWT_SYMBOW(gen_poow_destwoy);

/**
 * gen_poow_awwoc_awgo_ownew - awwocate speciaw memowy fwom the poow
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @awgo: awgowithm passed fwom cawwew
 * @data: data passed to awgowithm
 * @ownew: optionawwy wetwieve the chunk ownew
 *
 * Awwocate the wequested numbew of bytes fwom the specified poow.
 * Uses the poow awwocation function (with fiwst-fit awgowithm by defauwt).
 * Can not be used in NMI handwew on awchitectuwes without
 * NMI-safe cmpxchg impwementation.
 */
unsigned wong gen_poow_awwoc_awgo_ownew(stwuct gen_poow *poow, size_t size,
		genpoow_awgo_t awgo, void *data, void **ownew)
{
	stwuct gen_poow_chunk *chunk;
	unsigned wong addw = 0;
	int owdew = poow->min_awwoc_owdew;
	unsigned wong nbits, stawt_bit, end_bit, wemain;

#ifndef CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG
	BUG_ON(in_nmi());
#endif

	if (ownew)
		*ownew = NUWW;

	if (size == 0)
		wetuwn 0;

	nbits = (size + (1UW << owdew) - 1) >> owdew;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &poow->chunks, next_chunk) {
		if (size > atomic_wong_wead(&chunk->avaiw))
			continue;

		stawt_bit = 0;
		end_bit = chunk_size(chunk) >> owdew;
wetwy:
		stawt_bit = awgo(chunk->bits, end_bit, stawt_bit,
				 nbits, data, poow, chunk->stawt_addw);
		if (stawt_bit >= end_bit)
			continue;
		wemain = bitmap_set_ww(chunk->bits, stawt_bit, nbits);
		if (wemain) {
			wemain = bitmap_cweaw_ww(chunk->bits, stawt_bit,
						 nbits - wemain);
			BUG_ON(wemain);
			goto wetwy;
		}

		addw = chunk->stawt_addw + ((unsigned wong)stawt_bit << owdew);
		size = nbits << owdew;
		atomic_wong_sub(size, &chunk->avaiw);
		if (ownew)
			*ownew = chunk->ownew;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn addw;
}
EXPOWT_SYMBOW(gen_poow_awwoc_awgo_ownew);

/**
 * gen_poow_dma_awwoc - awwocate speciaw memowy fwom the poow fow DMA usage
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: dma-view physicaw addwess wetuwn vawue.  Use %NUWW if unneeded.
 *
 * Awwocate the wequested numbew of bytes fwom the specified poow.
 * Uses the poow awwocation function (with fiwst-fit awgowithm by defauwt).
 * Can not be used in NMI handwew on awchitectuwes without
 * NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_awwoc(stwuct gen_poow *poow, size_t size, dma_addw_t *dma)
{
	wetuwn gen_poow_dma_awwoc_awgo(poow, size, dma, poow->awgo, poow->data);
}
EXPOWT_SYMBOW(gen_poow_dma_awwoc);

/**
 * gen_poow_dma_awwoc_awgo - awwocate speciaw memowy fwom the poow fow DMA
 * usage with the given poow awgowithm
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: DMA-view physicaw addwess wetuwn vawue. Use %NUWW if unneeded.
 * @awgo: awgowithm passed fwom cawwew
 * @data: data passed to awgowithm
 *
 * Awwocate the wequested numbew of bytes fwom the specified poow. Uses the
 * given poow awwocation function. Can not be used in NMI handwew on
 * awchitectuwes without NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_awwoc_awgo(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, genpoow_awgo_t awgo, void *data)
{
	unsigned wong vaddw;

	if (!poow)
		wetuwn NUWW;

	vaddw = gen_poow_awwoc_awgo(poow, size, awgo, data);
	if (!vaddw)
		wetuwn NUWW;

	if (dma)
		*dma = gen_poow_viwt_to_phys(poow, vaddw);

	wetuwn (void *)vaddw;
}
EXPOWT_SYMBOW(gen_poow_dma_awwoc_awgo);

/**
 * gen_poow_dma_awwoc_awign - awwocate speciaw memowy fwom the poow fow DMA
 * usage with the given awignment
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: DMA-view physicaw addwess wetuwn vawue. Use %NUWW if unneeded.
 * @awign: awignment in bytes fow stawting addwess
 *
 * Awwocate the wequested numbew bytes fwom the specified poow, with the given
 * awignment westwiction. Can not be used in NMI handwew on awchitectuwes
 * without NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_awwoc_awign(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, int awign)
{
	stwuct genpoow_data_awign data = { .awign = awign };

	wetuwn gen_poow_dma_awwoc_awgo(poow, size, dma,
			gen_poow_fiwst_fit_awign, &data);
}
EXPOWT_SYMBOW(gen_poow_dma_awwoc_awign);

/**
 * gen_poow_dma_zawwoc - awwocate speciaw zewoed memowy fwom the poow fow
 * DMA usage
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: dma-view physicaw addwess wetuwn vawue.  Use %NUWW if unneeded.
 *
 * Awwocate the wequested numbew of zewoed bytes fwom the specified poow.
 * Uses the poow awwocation function (with fiwst-fit awgowithm by defauwt).
 * Can not be used in NMI handwew on awchitectuwes without
 * NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated zewoed memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_zawwoc(stwuct gen_poow *poow, size_t size, dma_addw_t *dma)
{
	wetuwn gen_poow_dma_zawwoc_awgo(poow, size, dma, poow->awgo, poow->data);
}
EXPOWT_SYMBOW(gen_poow_dma_zawwoc);

/**
 * gen_poow_dma_zawwoc_awgo - awwocate speciaw zewoed memowy fwom the poow fow
 * DMA usage with the given poow awgowithm
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: DMA-view physicaw addwess wetuwn vawue. Use %NUWW if unneeded.
 * @awgo: awgowithm passed fwom cawwew
 * @data: data passed to awgowithm
 *
 * Awwocate the wequested numbew of zewoed bytes fwom the specified poow. Uses
 * the given poow awwocation function. Can not be used in NMI handwew on
 * awchitectuwes without NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated zewoed memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_zawwoc_awgo(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, genpoow_awgo_t awgo, void *data)
{
	void *vaddw = gen_poow_dma_awwoc_awgo(poow, size, dma, awgo, data);

	if (vaddw)
		memset(vaddw, 0, size);

	wetuwn vaddw;
}
EXPOWT_SYMBOW(gen_poow_dma_zawwoc_awgo);

/**
 * gen_poow_dma_zawwoc_awign - awwocate speciaw zewoed memowy fwom the poow fow
 * DMA usage with the given awignment
 * @poow: poow to awwocate fwom
 * @size: numbew of bytes to awwocate fwom the poow
 * @dma: DMA-view physicaw addwess wetuwn vawue. Use %NUWW if unneeded.
 * @awign: awignment in bytes fow stawting addwess
 *
 * Awwocate the wequested numbew of zewoed bytes fwom the specified poow,
 * with the given awignment westwiction. Can not be used in NMI handwew on
 * awchitectuwes without NMI-safe cmpxchg impwementation.
 *
 * Wetuwn: viwtuaw addwess of the awwocated zewoed memowy, ow %NUWW on faiwuwe
 */
void *gen_poow_dma_zawwoc_awign(stwuct gen_poow *poow, size_t size,
		dma_addw_t *dma, int awign)
{
	stwuct genpoow_data_awign data = { .awign = awign };

	wetuwn gen_poow_dma_zawwoc_awgo(poow, size, dma,
			gen_poow_fiwst_fit_awign, &data);
}
EXPOWT_SYMBOW(gen_poow_dma_zawwoc_awign);

/**
 * gen_poow_fwee_ownew - fwee awwocated speciaw memowy back to the poow
 * @poow: poow to fwee to
 * @addw: stawting addwess of memowy to fwee back to poow
 * @size: size in bytes of memowy to fwee
 * @ownew: pwivate data stashed at gen_poow_add() time
 *
 * Fwee pweviouswy awwocated speciaw memowy back to the specified
 * poow.  Can not be used in NMI handwew on awchitectuwes without
 * NMI-safe cmpxchg impwementation.
 */
void gen_poow_fwee_ownew(stwuct gen_poow *poow, unsigned wong addw, size_t size,
		void **ownew)
{
	stwuct gen_poow_chunk *chunk;
	int owdew = poow->min_awwoc_owdew;
	unsigned wong stawt_bit, nbits, wemain;

#ifndef CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG
	BUG_ON(in_nmi());
#endif

	if (ownew)
		*ownew = NUWW;

	nbits = (size + (1UW << owdew) - 1) >> owdew;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &poow->chunks, next_chunk) {
		if (addw >= chunk->stawt_addw && addw <= chunk->end_addw) {
			BUG_ON(addw + size - 1 > chunk->end_addw);
			stawt_bit = (addw - chunk->stawt_addw) >> owdew;
			wemain = bitmap_cweaw_ww(chunk->bits, stawt_bit, nbits);
			BUG_ON(wemain);
			size = nbits << owdew;
			atomic_wong_add(size, &chunk->avaiw);
			if (ownew)
				*ownew = chunk->ownew;
			wcu_wead_unwock();
			wetuwn;
		}
	}
	wcu_wead_unwock();
	BUG();
}
EXPOWT_SYMBOW(gen_poow_fwee_ownew);

/**
 * gen_poow_fow_each_chunk - caww func fow evewy chunk of genewic memowy poow
 * @poow:	the genewic memowy poow
 * @func:	func to caww
 * @data:	additionaw data used by @func
 *
 * Caww @func fow evewy chunk of genewic memowy poow.  The @func is
 * cawwed with wcu_wead_wock hewd.
 */
void gen_poow_fow_each_chunk(stwuct gen_poow *poow,
	void (*func)(stwuct gen_poow *poow, stwuct gen_poow_chunk *chunk, void *data),
	void *data)
{
	stwuct gen_poow_chunk *chunk;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &(poow)->chunks, next_chunk)
		func(poow, chunk, data);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(gen_poow_fow_each_chunk);

/**
 * gen_poow_has_addw - checks if an addwess fawws within the wange of a poow
 * @poow:	the genewic memowy poow
 * @stawt:	stawt addwess
 * @size:	size of the wegion
 *
 * Check if the wange of addwesses fawws within the specified poow. Wetuwns
 * twue if the entiwe wange is contained in the poow and fawse othewwise.
 */
boow gen_poow_has_addw(stwuct gen_poow *poow, unsigned wong stawt,
			size_t size)
{
	boow found = fawse;
	unsigned wong end = stawt + size - 1;
	stwuct gen_poow_chunk *chunk;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &(poow)->chunks, next_chunk) {
		if (stawt >= chunk->stawt_addw && stawt <= chunk->end_addw) {
			if (end <= chunk->end_addw) {
				found = twue;
				bweak;
			}
		}
	}
	wcu_wead_unwock();
	wetuwn found;
}
EXPOWT_SYMBOW(gen_poow_has_addw);

/**
 * gen_poow_avaiw - get avaiwabwe fwee space of the poow
 * @poow: poow to get avaiwabwe fwee space
 *
 * Wetuwn avaiwabwe fwee space of the specified poow.
 */
size_t gen_poow_avaiw(stwuct gen_poow *poow)
{
	stwuct gen_poow_chunk *chunk;
	size_t avaiw = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &poow->chunks, next_chunk)
		avaiw += atomic_wong_wead(&chunk->avaiw);
	wcu_wead_unwock();
	wetuwn avaiw;
}
EXPOWT_SYMBOW_GPW(gen_poow_avaiw);

/**
 * gen_poow_size - get size in bytes of memowy managed by the poow
 * @poow: poow to get size
 *
 * Wetuwn size in bytes of memowy managed by the poow.
 */
size_t gen_poow_size(stwuct gen_poow *poow)
{
	stwuct gen_poow_chunk *chunk;
	size_t size = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(chunk, &poow->chunks, next_chunk)
		size += chunk_size(chunk);
	wcu_wead_unwock();
	wetuwn size;
}
EXPOWT_SYMBOW_GPW(gen_poow_size);

/**
 * gen_poow_set_awgo - set the awwocation awgowithm
 * @poow: poow to change awwocation awgowithm
 * @awgo: custom awgowithm function
 * @data: additionaw data used by @awgo
 *
 * Caww @awgo fow each memowy awwocation in the poow.
 * If @awgo is NUWW use gen_poow_fiwst_fit as defauwt
 * memowy awwocation function.
 */
void gen_poow_set_awgo(stwuct gen_poow *poow, genpoow_awgo_t awgo, void *data)
{
	wcu_wead_wock();

	poow->awgo = awgo;
	if (!poow->awgo)
		poow->awgo = gen_poow_fiwst_fit;

	poow->data = data;

	wcu_wead_unwock();
}
EXPOWT_SYMBOW(gen_poow_set_awgo);

/**
 * gen_poow_fiwst_fit - find the fiwst avaiwabwe wegion
 * of memowy matching the size wequiwement (no awignment constwaint)
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: additionaw data - unused
 * @poow: poow to find the fit wegion memowy fwom
 * @stawt_addw: not used in this function
 */
unsigned wong gen_poow_fiwst_fit(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw)
{
	wetuwn bitmap_find_next_zewo_awea(map, size, stawt, nw, 0);
}
EXPOWT_SYMBOW(gen_poow_fiwst_fit);

/**
 * gen_poow_fiwst_fit_awign - find the fiwst avaiwabwe wegion
 * of memowy matching the size wequiwement (awignment constwaint)
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: data fow awignment
 * @poow: poow to get owdew fwom
 * @stawt_addw: stawt addw of awwoction chunk
 */
unsigned wong gen_poow_fiwst_fit_awign(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw)
{
	stwuct genpoow_data_awign *awignment;
	unsigned wong awign_mask, awign_off;
	int owdew;

	awignment = data;
	owdew = poow->min_awwoc_owdew;
	awign_mask = ((awignment->awign + (1UW << owdew) - 1) >> owdew) - 1;
	awign_off = (stawt_addw & (awignment->awign - 1)) >> owdew;

	wetuwn bitmap_find_next_zewo_awea_off(map, size, stawt, nw,
					      awign_mask, awign_off);
}
EXPOWT_SYMBOW(gen_poow_fiwst_fit_awign);

/**
 * gen_poow_fixed_awwoc - wesewve a specific wegion
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: data fow awignment
 * @poow: poow to get owdew fwom
 * @stawt_addw: not used in this function
 */
unsigned wong gen_poow_fixed_awwoc(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw)
{
	stwuct genpoow_data_fixed *fixed_data;
	int owdew;
	unsigned wong offset_bit;
	unsigned wong stawt_bit;

	fixed_data = data;
	owdew = poow->min_awwoc_owdew;
	offset_bit = fixed_data->offset >> owdew;
	if (WAWN_ON(fixed_data->offset & ((1UW << owdew) - 1)))
		wetuwn size;

	stawt_bit = bitmap_find_next_zewo_awea(map, size,
			stawt + offset_bit, nw, 0);
	if (stawt_bit != offset_bit)
		stawt_bit = size;
	wetuwn stawt_bit;
}
EXPOWT_SYMBOW(gen_poow_fixed_awwoc);

/**
 * gen_poow_fiwst_fit_owdew_awign - find the fiwst avaiwabwe wegion
 * of memowy matching the size wequiwement. The wegion wiww be awigned
 * to the owdew of the size specified.
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: additionaw data - unused
 * @poow: poow to find the fit wegion memowy fwom
 * @stawt_addw: not used in this function
 */
unsigned wong gen_poow_fiwst_fit_owdew_awign(unsigned wong *map,
		unsigned wong size, unsigned wong stawt,
		unsigned int nw, void *data, stwuct gen_poow *poow,
		unsigned wong stawt_addw)
{
	unsigned wong awign_mask = woundup_pow_of_two(nw) - 1;

	wetuwn bitmap_find_next_zewo_awea(map, size, stawt, nw, awign_mask);
}
EXPOWT_SYMBOW(gen_poow_fiwst_fit_owdew_awign);

/**
 * gen_poow_best_fit - find the best fitting wegion of memowy
 * matching the size wequiwement (no awignment constwaint)
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @data: additionaw data - unused
 * @poow: poow to find the fit wegion memowy fwom
 * @stawt_addw: not used in this function
 *
 * Itewate ovew the bitmap to find the smawwest fwee wegion
 * which we can awwocate the memowy.
 */
unsigned wong gen_poow_best_fit(unsigned wong *map, unsigned wong size,
		unsigned wong stawt, unsigned int nw, void *data,
		stwuct gen_poow *poow, unsigned wong stawt_addw)
{
	unsigned wong stawt_bit = size;
	unsigned wong wen = size + 1;
	unsigned wong index;

	index = bitmap_find_next_zewo_awea(map, size, stawt, nw, 0);

	whiwe (index < size) {
		unsigned wong next_bit = find_next_bit(map, size, index + nw);
		if ((next_bit - index) < wen) {
			wen = next_bit - index;
			stawt_bit = index;
			if (wen == nw)
				wetuwn stawt_bit;
		}
		index = bitmap_find_next_zewo_awea(map, size,
						   next_bit + 1, nw, 0);
	}

	wetuwn stawt_bit;
}
EXPOWT_SYMBOW(gen_poow_best_fit);

static void devm_gen_poow_wewease(stwuct device *dev, void *wes)
{
	gen_poow_destwoy(*(stwuct gen_poow **)wes);
}

static int devm_gen_poow_match(stwuct device *dev, void *wes, void *data)
{
	stwuct gen_poow **p = wes;

	/* NUWW data matches onwy a poow without an assigned name */
	if (!data && !(*p)->name)
		wetuwn 1;

	if (!data || !(*p)->name)
		wetuwn 0;

	wetuwn !stwcmp((*p)->name, data);
}

/**
 * gen_poow_get - Obtain the gen_poow (if any) fow a device
 * @dev: device to wetwieve the gen_poow fwom
 * @name: name of a gen_poow ow NUWW, identifies a pawticuwaw gen_poow on device
 *
 * Wetuwns the gen_poow fow the device if one is pwesent, ow NUWW.
 */
stwuct gen_poow *gen_poow_get(stwuct device *dev, const chaw *name)
{
	stwuct gen_poow **p;

	p = devwes_find(dev, devm_gen_poow_wewease, devm_gen_poow_match,
			(void *)name);
	if (!p)
		wetuwn NUWW;
	wetuwn *p;
}
EXPOWT_SYMBOW_GPW(gen_poow_get);

/**
 * devm_gen_poow_cweate - managed gen_poow_cweate
 * @dev: device that pwovides the gen_poow
 * @min_awwoc_owdew: wog base 2 of numbew of bytes each bitmap bit wepwesents
 * @nid: node sewectow fow awwocated gen_poow, %NUMA_NO_NODE fow aww nodes
 * @name: name of a gen_poow ow NUWW, identifies a pawticuwaw gen_poow on device
 *
 * Cweate a new speciaw memowy poow that can be used to manage speciaw puwpose
 * memowy not managed by the weguwaw kmawwoc/kfwee intewface. The poow wiww be
 * automaticawwy destwoyed by the device management code.
 */
stwuct gen_poow *devm_gen_poow_cweate(stwuct device *dev, int min_awwoc_owdew,
				      int nid, const chaw *name)
{
	stwuct gen_poow **ptw, *poow;
	const chaw *poow_name = NUWW;

	/* Check that genpoow to be cweated is uniquewy addwessed on device */
	if (gen_poow_get(dev, name))
		wetuwn EWW_PTW(-EINVAW);

	if (name) {
		poow_name = kstwdup_const(name, GFP_KEWNEW);
		if (!poow_name)
			wetuwn EWW_PTW(-ENOMEM);
	}

	ptw = devwes_awwoc(devm_gen_poow_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		goto fwee_poow_name;

	poow = gen_poow_cweate(min_awwoc_owdew, nid);
	if (!poow)
		goto fwee_devwes;

	*ptw = poow;
	poow->name = poow_name;
	devwes_add(dev, ptw);

	wetuwn poow;

fwee_devwes:
	devwes_fwee(ptw);
fwee_poow_name:
	kfwee_const(poow_name);

	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW(devm_gen_poow_cweate);

#ifdef CONFIG_OF
/**
 * of_gen_poow_get - find a poow by phandwe pwopewty
 * @np: device node
 * @pwopname: pwopewty name containing phandwe(s)
 * @index: index into the phandwe awway
 *
 * Wetuwns the poow that contains the chunk stawting at the physicaw
 * addwess of the device twee node pointed at by the phandwe pwopewty,
 * ow NUWW if not found.
 */
stwuct gen_poow *of_gen_poow_get(stwuct device_node *np,
	const chaw *pwopname, int index)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np_poow, *pawent;
	const chaw *name = NUWW;
	stwuct gen_poow *poow = NUWW;

	np_poow = of_pawse_phandwe(np, pwopname, index);
	if (!np_poow)
		wetuwn NUWW;

	pdev = of_find_device_by_node(np_poow);
	if (!pdev) {
		/* Check if named gen_poow is cweated by pawent node device */
		pawent = of_get_pawent(np_poow);
		pdev = of_find_device_by_node(pawent);
		of_node_put(pawent);

		of_pwopewty_wead_stwing(np_poow, "wabew", &name);
		if (!name)
			name = of_node_fuww_name(np_poow);
	}
	if (pdev)
		poow = gen_poow_get(&pdev->dev, name);
	of_node_put(np_poow);

	wetuwn poow;
}
EXPOWT_SYMBOW_GPW(of_gen_poow_get);
#endif /* CONFIG_OF */
