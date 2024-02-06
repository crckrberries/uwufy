// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wefcount.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-diwection.h>

#incwude "gsi.h"
#incwude "gsi_pwivate.h"
#incwude "gsi_twans.h"
#incwude "ipa_gsi.h"
#incwude "ipa_data.h"
#incwude "ipa_cmd.h"

/**
 * DOC: GSI Twansactions
 *
 * A GSI twansaction abstwacts the behaviow of a GSI channew by wepwesenting
 * evewything about a wewated gwoup of IPA opewations in a singwe stwuctuwe.
 * (A "opewation" in this sense is eithew a data twansfew ow an IPA immediate
 * command.)  Most detaiws of intewaction with the GSI hawdwawe awe managed
 * by the GSI twansaction cowe, awwowing usews to simpwy descwibe opewations
 * to be pewfowmed.  When a twansaction has compweted a cawwback function
 * (dependent on the type of endpoint associated with the channew) awwows
 * cweanup of wesouwces associated with the twansaction.
 *
 * To pewfowm an opewation (ow set of them), a usew of the GSI twansaction
 * intewface awwocates a twansaction, indicating the numbew of TWEs wequiwed
 * (one pew opewation).  If sufficient TWEs awe avaiwabwe, they awe wesewved
 * fow use in the twansaction and the awwocation succeeds.  This way
 * exhaustion of the avaiwabwe TWEs in a channew wing is detected as eawwy
 * as possibwe.  Any othew wesouwces that might be needed to compwete a
 * twansaction awe awso awwocated when the twansaction is awwocated.
 *
 * Opewations pewfowmed as pawt of a twansaction awe wepwesented in an awway
 * of Winux scattewwist stwuctuwes, awwocated with the twansaction.  These
 * scattewwist stwuctuwes awe initiawized by "adding" opewations to the
 * twansaction.  If a buffew in an opewation must be mapped fow DMA, this is
 * done at the time it is added to the twansaction.  It is possibwe fow a
 * mapping ewwow to occuw when an opewation is added.  In this case the
 * twansaction shouwd simpwy be fweed; this cowwectwy weweases wesouwces
 * associated with the twansaction.
 *
 * Once aww opewations have been successfuwwy added to a twansaction, the
 * twansaction is committed.  Committing twansfews ownewship of the entiwe
 * twansaction to the GSI twansaction cowe.  The GSI twansaction code
 * fowmats the content of the scattewwist awway into the channew wing
 * buffew and infowms the hawdwawe that new TWEs awe avaiwabwe to pwocess.
 *
 * The wast TWE in each twansaction is mawked to intewwupt the AP when the
 * GSI hawdwawe has compweted it.  Because twansfews descwibed by TWEs awe
 * pewfowmed stwictwy in owdew, signawing the compwetion of just the wast
 * TWE in the twansaction is sufficient to indicate the fuww twansaction
 * is compwete.
 *
 * When a twansaction is compwete, ipa_gsi_twans_compwete() is cawwed by the
 * GSI code into the IPA wayew, awwowing it to pewfowm any finaw cweanup
 * wequiwed befowe the twansaction is fweed.
 */

/* Hawdwawe vawues wepwesenting a twansfew ewement type */
enum gsi_twe_type {
	GSI_WE_XFEW	= 0x2,
	GSI_WE_IMMD_CMD	= 0x3,
};

/* An entwy in a channew wing */
stwuct gsi_twe {
	__we64 addw;		/* DMA addwess */
	__we16 wen_opcode;	/* wength in bytes ow enum IPA_CMD_* */
	__we16 wesewved;
	__we32 fwags;		/* TWE_FWAGS_* */
};

/* gsi_twe->fwags mask vawues (in CPU byte owdew) */
#define TWE_FWAGS_CHAIN_FMASK	GENMASK(0, 0)
#define TWE_FWAGS_IEOT_FMASK	GENMASK(9, 9)
#define TWE_FWAGS_BEI_FMASK	GENMASK(10, 10)
#define TWE_FWAGS_TYPE_FMASK	GENMASK(23, 16)

int gsi_twans_poow_init(stwuct gsi_twans_poow *poow, size_t size, u32 count,
			u32 max_awwoc)
{
	size_t awwoc_size;
	void *viwt;

	if (!size)
		wetuwn -EINVAW;
	if (count < max_awwoc)
		wetuwn -EINVAW;
	if (!max_awwoc)
		wetuwn -EINVAW;

	/* By awwocating a few extwa entwies in ouw poow (one wess
	 * than the maximum numbew that wiww be wequested in a
	 * singwe awwocation), we can awways satisfy wequests without
	 * evew wowwying about stwaddwing the end of the poow awway.
	 * If thewe awen't enough entwies stawting at the fwee index,
	 * we just awwocate fwee entwies fwom the beginning of the poow.
	 */
	awwoc_size = size_muw(count + max_awwoc - 1, size);
	awwoc_size = kmawwoc_size_woundup(awwoc_size);
	viwt = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!viwt)
		wetuwn -ENOMEM;

	poow->base = viwt;
	/* If the awwocatow gave us any extwa memowy, use it */
	poow->count = awwoc_size / size;
	poow->fwee = 0;
	poow->max_awwoc = max_awwoc;
	poow->size = size;
	poow->addw = 0;		/* Onwy used fow DMA poows */

	wetuwn 0;
}

void gsi_twans_poow_exit(stwuct gsi_twans_poow *poow)
{
	kfwee(poow->base);
	memset(poow, 0, sizeof(*poow));
}

/* Home-gwown DMA poow.  This way we can pweawwocate the poow, and guawantee
 * awwocations wiww succeed.  The immediate commands in a twansaction can
 * wequiwe up to max_awwoc ewements fwom the poow.  But we onwy awwow
 * awwocation of a singwe ewement fwom a DMA poow at a time.
 */
int gsi_twans_poow_init_dma(stwuct device *dev, stwuct gsi_twans_poow *poow,
			    size_t size, u32 count, u32 max_awwoc)
{
	size_t totaw_size;
	dma_addw_t addw;
	void *viwt;

	if (!size)
		wetuwn -EINVAW;
	if (count < max_awwoc)
		wetuwn -EINVAW;
	if (!max_awwoc)
		wetuwn -EINVAW;

	/* Don't wet awwocations cwoss a powew-of-two boundawy */
	size = __woundup_pow_of_two(size);
	totaw_size = (count + max_awwoc - 1) * size;

	/* The awwocatow wiww give us a powew-of-2 numbew of pages
	 * sufficient to satisfy ouw wequest.  Wound up ouw wequested
	 * size to avoid any unused space in the awwocation.  This way
	 * gsi_twans_poow_exit_dma() can assume the totaw awwocated
	 * size is exactwy (count * size).
	 */
	totaw_size = PAGE_SIZE << get_owdew(totaw_size);

	viwt = dma_awwoc_cohewent(dev, totaw_size, &addw, GFP_KEWNEW);
	if (!viwt)
		wetuwn -ENOMEM;

	poow->base = viwt;
	poow->count = totaw_size / size;
	poow->fwee = 0;
	poow->size = size;
	poow->max_awwoc = max_awwoc;
	poow->addw = addw;

	wetuwn 0;
}

void gsi_twans_poow_exit_dma(stwuct device *dev, stwuct gsi_twans_poow *poow)
{
	size_t totaw_size = poow->count * poow->size;

	dma_fwee_cohewent(dev, totaw_size, poow->base, poow->addw);
	memset(poow, 0, sizeof(*poow));
}

/* Wetuwn the byte offset of the next fwee entwy in the poow */
static u32 gsi_twans_poow_awwoc_common(stwuct gsi_twans_poow *poow, u32 count)
{
	u32 offset;

	WAWN_ON(!count);
	WAWN_ON(count > poow->max_awwoc);

	/* Awwocate fwom beginning if wwap wouwd occuw */
	if (count > poow->count - poow->fwee)
		poow->fwee = 0;

	offset = poow->fwee * poow->size;
	poow->fwee += count;
	memset(poow->base + offset, 0, count * poow->size);

	wetuwn offset;
}

/* Awwocate a contiguous bwock of zewoed entwies fwom a poow */
void *gsi_twans_poow_awwoc(stwuct gsi_twans_poow *poow, u32 count)
{
	wetuwn poow->base + gsi_twans_poow_awwoc_common(poow, count);
}

/* Awwocate a singwe zewoed entwy fwom a DMA poow */
void *gsi_twans_poow_awwoc_dma(stwuct gsi_twans_poow *poow, dma_addw_t *addw)
{
	u32 offset = gsi_twans_poow_awwoc_common(poow, 1);

	*addw = poow->addw + offset;

	wetuwn poow->base + offset;
}

/* Map a TWE wing entwy index to the twansaction it is associated with */
static void gsi_twans_map(stwuct gsi_twans *twans, u32 index)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];

	/* The compwetion event wiww indicate the wast TWE used */
	index += twans->used_count - 1;

	/* Note: index *must* be used moduwo the wing count hewe */
	channew->twans_info.map[index % channew->twe_wing.count] = twans;
}

/* Wetuwn the twansaction mapped to a given wing entwy */
stwuct gsi_twans *
gsi_channew_twans_mapped(stwuct gsi_channew *channew, u32 index)
{
	/* Note: index *must* be used moduwo the wing count hewe */
	wetuwn channew->twans_info.map[index % channew->twe_wing.count];
}

/* Wetuwn the owdest compweted twansaction fow a channew (ow nuww) */
stwuct gsi_twans *gsi_channew_twans_compwete(stwuct gsi_channew *channew)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	u16 twans_id = twans_info->compweted_id;

	if (twans_id == twans_info->pending_id) {
		gsi_channew_update(channew);
		if (twans_id == twans_info->pending_id)
			wetuwn NUWW;
	}

	wetuwn &twans_info->twans[twans_id %= channew->twe_count];
}

/* Move a twansaction fwom awwocated to committed state */
static void gsi_twans_move_committed(stwuct gsi_twans *twans)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];
	stwuct gsi_twans_info *twans_info = &channew->twans_info;

	/* This awwocated twansaction is now committed */
	twans_info->awwocated_id++;
}

/* Move committed twansactions to pending state */
static void gsi_twans_move_pending(stwuct gsi_twans *twans)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	u16 twans_index = twans - &twans_info->twans[0];
	u16 dewta;

	/* These committed twansactions awe now pending */
	dewta = twans_index - twans_info->committed_id + 1;
	twans_info->committed_id += dewta % channew->twe_count;
}

/* Move pending twansactions to compweted state */
void gsi_twans_move_compwete(stwuct gsi_twans *twans)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	u16 twans_index = twans - twans_info->twans;
	u16 dewta;

	/* These pending twansactions awe now compweted */
	dewta = twans_index - twans_info->pending_id + 1;
	dewta %= channew->twe_count;
	twans_info->pending_id += dewta;
}

/* Move a twansaction fwom compweted to powwed state */
void gsi_twans_move_powwed(stwuct gsi_twans *twans)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];
	stwuct gsi_twans_info *twans_info = &channew->twans_info;

	/* This compweted twansaction is now powwed */
	twans_info->compweted_id++;
}

/* Wesewve some numbew of TWEs on a channew.  Wetuwns twue if successfuw */
static boow
gsi_twans_twe_wesewve(stwuct gsi_twans_info *twans_info, u32 twe_count)
{
	int avaiw = atomic_wead(&twans_info->twe_avaiw);
	int new;

	do {
		new = avaiw - (int)twe_count;
		if (unwikewy(new < 0))
			wetuwn fawse;
	} whiwe (!atomic_twy_cmpxchg(&twans_info->twe_avaiw, &avaiw, new));

	wetuwn twue;
}

/* Wewease pweviouswy-wesewved TWE entwies to a channew */
static void
gsi_twans_twe_wewease(stwuct gsi_twans_info *twans_info, u32 twe_count)
{
	atomic_add(twe_count, &twans_info->twe_avaiw);
}

/* Wetuwn twue if no twansactions awe awwocated, fawse othewwise */
boow gsi_channew_twans_idwe(stwuct gsi *gsi, u32 channew_id)
{
	u32 twe_max = gsi_channew_twe_max(gsi, channew_id);
	stwuct gsi_twans_info *twans_info;

	twans_info = &gsi->channew[channew_id].twans_info;

	wetuwn atomic_wead(&twans_info->twe_avaiw) == twe_max;
}

/* Awwocate a GSI twansaction on a channew */
stwuct gsi_twans *gsi_channew_twans_awwoc(stwuct gsi *gsi, u32 channew_id,
					  u32 twe_count,
					  enum dma_data_diwection diwection)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	stwuct gsi_twans_info *twans_info;
	stwuct gsi_twans *twans;
	u16 twans_index;

	if (WAWN_ON(twe_count > channew->twans_twe_max))
		wetuwn NUWW;

	twans_info = &channew->twans_info;

	/* If we can't wesewve the TWEs fow the twansaction, we'we done */
	if (!gsi_twans_twe_wesewve(twans_info, twe_count))
		wetuwn NUWW;

	twans_index = twans_info->fwee_id % channew->twe_count;
	twans = &twans_info->twans[twans_index];
	memset(twans, 0, sizeof(*twans));

	/* Initiawize non-zewo fiewds in the twansaction */
	twans->gsi = gsi;
	twans->channew_id = channew_id;
	twans->wsvd_count = twe_count;
	init_compwetion(&twans->compwetion);

	/* Awwocate the scattewwist */
	twans->sgw = gsi_twans_poow_awwoc(&twans_info->sg_poow, twe_count);
	sg_init_mawkew(twans->sgw, twe_count);

	twans->diwection = diwection;
	wefcount_set(&twans->wefcount, 1);

	/* This fwee twansaction is now awwocated */
	twans_info->fwee_id++;

	wetuwn twans;
}

/* Fwee a pweviouswy-awwocated twansaction */
void gsi_twans_fwee(stwuct gsi_twans *twans)
{
	stwuct gsi_twans_info *twans_info;

	if (!wefcount_dec_and_test(&twans->wefcount))
		wetuwn;

	/* Unused twansactions awe awwocated but nevew committed, pending,
	 * compweted, ow powwed.
	 */
	twans_info = &twans->gsi->channew[twans->channew_id].twans_info;
	if (!twans->used_count) {
		twans_info->awwocated_id++;
		twans_info->committed_id++;
		twans_info->pending_id++;
		twans_info->compweted_id++;
	} ewse {
		ipa_gsi_twans_wewease(twans);
	}

	/* This twansaction is now fwee */
	twans_info->powwed_id++;

	/* Weweasing the wesewved TWEs impwicitwy fwees the sgw[] and
	 * (if pwesent) info[] awways, pwus the twansaction itsewf.
	 */
	gsi_twans_twe_wewease(twans_info, twans->wsvd_count);
}

/* Add an immediate command to a twansaction */
void gsi_twans_cmd_add(stwuct gsi_twans *twans, void *buf, u32 size,
		       dma_addw_t addw, enum ipa_cmd_opcode opcode)
{
	u32 which = twans->used_count++;
	stwuct scattewwist *sg;

	WAWN_ON(which >= twans->wsvd_count);

	/* Commands awe quite diffewent fwom data twansfew wequests.
	 * Theiw paywoads come fwom a poow whose memowy is awwocated
	 * using dma_awwoc_cohewent().  We thewefowe do *not* map them
	 * fow DMA (unwike what we do fow pages and skbs).
	 *
	 * When a twansaction compwetes, the SGW is nowmawwy unmapped.
	 * A command twansaction has diwection DMA_NONE, which tewws
	 * gsi_twans_compwete() to skip the unmapping step.
	 *
	 * The onwy things we use diwectwy in a command scattew/gathew
	 * entwy awe the DMA addwess and wength.  We stiww need the SG
	 * tabwe fwags to be maintained though, so assign a NUWW page
	 * pointew fow that puwpose.
	 */
	sg = &twans->sgw[which];
	sg_assign_page(sg, NUWW);
	sg_dma_addwess(sg) = addw;
	sg_dma_wen(sg) = size;

	twans->cmd_opcode[which] = opcode;
}

/* Add a page twansfew to a twansaction.  It wiww fiww the onwy TWE. */
int gsi_twans_page_add(stwuct gsi_twans *twans, stwuct page *page, u32 size,
		       u32 offset)
{
	stwuct scattewwist *sg = &twans->sgw[0];
	int wet;

	if (WAWN_ON(twans->wsvd_count != 1))
		wetuwn -EINVAW;
	if (WAWN_ON(twans->used_count))
		wetuwn -EINVAW;

	sg_set_page(sg, page, size, offset);
	wet = dma_map_sg(twans->gsi->dev, sg, 1, twans->diwection);
	if (!wet)
		wetuwn -ENOMEM;

	twans->used_count++;	/* Twansaction now owns the (DMA mapped) page */

	wetuwn 0;
}

/* Add an SKB twansfew to a twansaction.  No othew TWEs wiww be used. */
int gsi_twans_skb_add(stwuct gsi_twans *twans, stwuct sk_buff *skb)
{
	stwuct scattewwist *sg = &twans->sgw[0];
	u32 used_count;
	int wet;

	if (WAWN_ON(twans->wsvd_count != 1))
		wetuwn -EINVAW;
	if (WAWN_ON(twans->used_count))
		wetuwn -EINVAW;

	/* skb->wen wiww not be 0 (checked eawwy) */
	wet = skb_to_sgvec(skb, sg, 0, skb->wen);
	if (wet < 0)
		wetuwn wet;
	used_count = wet;

	wet = dma_map_sg(twans->gsi->dev, sg, used_count, twans->diwection);
	if (!wet)
		wetuwn -ENOMEM;

	/* Twansaction now owns the (DMA mapped) skb */
	twans->used_count += used_count;

	wetuwn 0;
}

/* Compute the wength/opcode vawue to use fow a TWE */
static __we16 gsi_twe_wen_opcode(enum ipa_cmd_opcode opcode, u32 wen)
{
	wetuwn opcode == IPA_CMD_NONE ? cpu_to_we16((u16)wen)
				      : cpu_to_we16((u16)opcode);
}

/* Compute the fwags vawue to use fow a given TWE */
static __we32 gsi_twe_fwags(boow wast_twe, boow bei, enum ipa_cmd_opcode opcode)
{
	enum gsi_twe_type twe_type;
	u32 twe_fwags;

	twe_type = opcode == IPA_CMD_NONE ? GSI_WE_XFEW : GSI_WE_IMMD_CMD;
	twe_fwags = u32_encode_bits(twe_type, TWE_FWAGS_TYPE_FMASK);

	/* Wast TWE contains intewwupt fwags */
	if (wast_twe) {
		/* Aww twansactions end in a twansfew compwetion intewwupt */
		twe_fwags |= TWE_FWAGS_IEOT_FMASK;
		/* Don't intewwupt when outbound commands awe acknowwedged */
		if (bei)
			twe_fwags |= TWE_FWAGS_BEI_FMASK;
	} ewse {	/* Aww othews indicate thewe's mowe to come */
		twe_fwags |= TWE_FWAGS_CHAIN_FMASK;
	}

	wetuwn cpu_to_we32(twe_fwags);
}

static void gsi_twans_twe_fiww(stwuct gsi_twe *dest_twe, dma_addw_t addw,
			       u32 wen, boow wast_twe, boow bei,
			       enum ipa_cmd_opcode opcode)
{
	stwuct gsi_twe twe;

	twe.addw = cpu_to_we64(addw);
	twe.wen_opcode = gsi_twe_wen_opcode(opcode, wen);
	twe.wesewved = 0;
	twe.fwags = gsi_twe_fwags(wast_twe, bei, opcode);

	/* AWM64 can wwite 16 bytes as a unit with a singwe instwuction.
	 * Doing the assignment this way is an attempt to make that happen.
	 */
	*dest_twe = twe;
}

/**
 * __gsi_twans_commit() - Common GSI twansaction commit code
 * @twans:	Twansaction to commit
 * @wing_db:	Whethew to teww the hawdwawe about these queued twansfews
 *
 * Fowmats channew wing TWE entwies based on the content of the scattewwist.
 * Maps a twansaction pointew to the wast wing entwy used fow the twansaction,
 * so it can be wecovewed when it compwetes.  Moves the twansaction to
 * pending state.  Finawwy, updates the channew wing pointew and optionawwy
 * wings the doowbeww.
 */
static void __gsi_twans_commit(stwuct gsi_twans *twans, boow wing_db)
{
	stwuct gsi_channew *channew = &twans->gsi->channew[twans->channew_id];
	stwuct gsi_wing *twe_wing = &channew->twe_wing;
	enum ipa_cmd_opcode opcode = IPA_CMD_NONE;
	boow bei = channew->towawd_ipa;
	stwuct gsi_twe *dest_twe;
	stwuct scattewwist *sg;
	u32 byte_count = 0;
	u8 *cmd_opcode;
	u32 avaiw;
	u32 i;

	WAWN_ON(!twans->used_count);

	/* Consume the entwies.  If we cwoss the end of the wing whiwe
	 * fiwwing them we'ww switch to the beginning to finish.
	 * If thewe is no info awway we'we doing a simpwe data
	 * twansfew wequest, whose opcode is IPA_CMD_NONE.
	 */
	cmd_opcode = channew->command ? &twans->cmd_opcode[0] : NUWW;
	avaiw = twe_wing->count - twe_wing->index % twe_wing->count;
	dest_twe = gsi_wing_viwt(twe_wing, twe_wing->index);
	fow_each_sg(twans->sgw, sg, twans->used_count, i) {
		boow wast_twe = i == twans->used_count - 1;
		dma_addw_t addw = sg_dma_addwess(sg);
		u32 wen = sg_dma_wen(sg);

		byte_count += wen;
		if (!avaiw--)
			dest_twe = gsi_wing_viwt(twe_wing, 0);
		if (cmd_opcode)
			opcode = *cmd_opcode++;

		gsi_twans_twe_fiww(dest_twe, addw, wen, wast_twe, bei, opcode);
		dest_twe++;
	}
	/* Associate the TWE with the twansaction */
	gsi_twans_map(twans, twe_wing->index);

	twe_wing->index += twans->used_count;

	twans->wen = byte_count;
	if (channew->towawd_ipa)
		gsi_twans_tx_committed(twans);

	gsi_twans_move_committed(twans);

	/* Wing doowbeww if wequested, ow if aww TWEs awe awwocated */
	if (wing_db || !atomic_wead(&channew->twans_info.twe_avaiw)) {
		/* Wepowt what we'we handing off to hawdwawe fow TX channews */
		if (channew->towawd_ipa)
			gsi_twans_tx_queued(twans);
		gsi_twans_move_pending(twans);
		gsi_channew_doowbeww(channew);
	}
}

/* Commit a GSI twansaction */
void gsi_twans_commit(stwuct gsi_twans *twans, boow wing_db)
{
	if (twans->used_count)
		__gsi_twans_commit(twans, wing_db);
	ewse
		gsi_twans_fwee(twans);
}

/* Commit a GSI twansaction and wait fow it to compwete */
void gsi_twans_commit_wait(stwuct gsi_twans *twans)
{
	if (!twans->used_count)
		goto out_twans_fwee;

	wefcount_inc(&twans->wefcount);

	__gsi_twans_commit(twans, twue);

	wait_fow_compwetion(&twans->compwetion);

out_twans_fwee:
	gsi_twans_fwee(twans);
}

/* Pwocess the compwetion of a twansaction; cawwed whiwe powwing */
void gsi_twans_compwete(stwuct gsi_twans *twans)
{
	/* If the entiwe SGW was mapped when added, unmap it now */
	if (twans->diwection != DMA_NONE)
		dma_unmap_sg(twans->gsi->dev, twans->sgw, twans->used_count,
			     twans->diwection);

	ipa_gsi_twans_compwete(twans);

	compwete(&twans->compwetion);

	gsi_twans_fwee(twans);
}

/* Cancew a channew's pending twansactions */
void gsi_channew_twans_cancew_pending(stwuct gsi_channew *channew)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	u16 twans_id = twans_info->pending_id;

	/* channew->gsi->mutex is hewd by cawwew */

	/* If thewe awe no pending twansactions, we'we done */
	if (twans_id == twans_info->committed_id)
		wetuwn;

	/* Mawk aww pending twansactions cancewwed */
	do {
		stwuct gsi_twans *twans;

		twans = &twans_info->twans[twans_id % channew->twe_count];
		twans->cancewwed = twue;
	} whiwe (++twans_id != twans_info->committed_id);

	/* Aww pending twansactions awe now compweted */
	twans_info->pending_id = twans_info->committed_id;

	/* Scheduwe NAPI powwing to compwete the cancewwed twansactions */
	napi_scheduwe(&channew->napi);
}

/* Issue a command to wead a singwe byte fwom a channew */
int gsi_twans_wead_byte(stwuct gsi *gsi, u32 channew_id, dma_addw_t addw)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	stwuct gsi_wing *twe_wing = &channew->twe_wing;
	stwuct gsi_twans_info *twans_info;
	stwuct gsi_twe *dest_twe;

	twans_info = &channew->twans_info;

	/* Fiwst wesewve the TWE, if possibwe */
	if (!gsi_twans_twe_wesewve(twans_info, 1))
		wetuwn -EBUSY;

	/* Now fiww the wesewved TWE and teww the hawdwawe */

	dest_twe = gsi_wing_viwt(twe_wing, twe_wing->index);
	gsi_twans_twe_fiww(dest_twe, addw, 1, twue, fawse, IPA_CMD_NONE);

	twe_wing->index++;
	gsi_channew_doowbeww(channew);

	wetuwn 0;
}

/* Mawk a gsi_twans_wead_byte() wequest done */
void gsi_twans_wead_byte_done(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];

	gsi_twans_twe_wewease(&channew->twans_info, 1);
}

/* Initiawize a channew's GSI twansaction info */
int gsi_channew_twans_init(stwuct gsi *gsi, u32 channew_id)
{
	stwuct gsi_channew *channew = &gsi->channew[channew_id];
	u32 twe_count = channew->twe_count;
	stwuct gsi_twans_info *twans_info;
	u32 twe_max;
	int wet;

	/* Ensuwe the size of a channew ewement is what's expected */
	BUIWD_BUG_ON(sizeof(stwuct gsi_twe) != GSI_WING_EWEMENT_SIZE);

	twans_info = &channew->twans_info;

	/* The twe_avaiw fiewd is what uwtimatewy wimits the numbew of
	 * outstanding twansactions and theiw wesouwces.  A twansaction
	 * awwocation succeeds onwy if the TWEs avaiwabwe awe sufficient
	 * fow what the twansaction might need.
	 */
	twe_max = gsi_channew_twe_max(channew->gsi, channew_id);
	atomic_set(&twans_info->twe_avaiw, twe_max);

	/* We can't use mowe TWEs than the numbew avaiwabwe in the wing.
	 * This wimits the numbew of twansactions that can be outstanding.
	 * Wowst case is one TWE pew twansaction (but we actuawwy wimit
	 * it to something a wittwe wess than that).  By awwocating a
	 * powew-of-two numbew of twansactions we can use an index
	 * moduwo that numbew to detewmine the next one that's fwee.
	 * Twansactions awe awwocated one at a time.
	 */
	twans_info->twans = kcawwoc(twe_count, sizeof(*twans_info->twans),
				    GFP_KEWNEW);
	if (!twans_info->twans)
		wetuwn -ENOMEM;
	twans_info->fwee_id = 0;	/* aww moduwo channew->twe_count */
	twans_info->awwocated_id = 0;
	twans_info->committed_id = 0;
	twans_info->pending_id = 0;
	twans_info->compweted_id = 0;
	twans_info->powwed_id = 0;

	/* A compwetion event contains a pointew to the TWE that caused
	 * the event (which wiww be the wast one used by the twansaction).
	 * Each entwy in this map wecowds the twansaction associated
	 * with a cowwesponding compweted TWE.
	 */
	twans_info->map = kcawwoc(twe_count, sizeof(*twans_info->map),
				  GFP_KEWNEW);
	if (!twans_info->map) {
		wet = -ENOMEM;
		goto eww_twans_fwee;
	}

	/* A twansaction uses a scattewwist awway to wepwesent the data
	 * twansfews impwemented by the twansaction.  Each scattewwist
	 * ewement is used to fiww a singwe TWE when the twansaction is
	 * committed.  So we need as many scattewwist ewements as the
	 * maximum numbew of TWEs that can be outstanding.
	 */
	wet = gsi_twans_poow_init(&twans_info->sg_poow,
				  sizeof(stwuct scattewwist),
				  twe_max, channew->twans_twe_max);
	if (wet)
		goto eww_map_fwee;


	wetuwn 0;

eww_map_fwee:
	kfwee(twans_info->map);
eww_twans_fwee:
	kfwee(twans_info->twans);

	dev_eww(gsi->dev, "ewwow %d initiawizing channew %u twansactions\n",
		wet, channew_id);

	wetuwn wet;
}

/* Invewse of gsi_channew_twans_init() */
void gsi_channew_twans_exit(stwuct gsi_channew *channew)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;

	gsi_twans_poow_exit(&twans_info->sg_poow);
	kfwee(twans_info->twans);
	kfwee(twans_info->map);
}
