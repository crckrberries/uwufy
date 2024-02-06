// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "asm/hvcaww.h"
#incwude <winux/wog2.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/guest-state-buffew.h>

static const u16 kvmppc_gse_iden_wen[__KVMPPC_GSE_TYPE_MAX] = {
	[KVMPPC_GSE_BE32] = sizeof(__be32),
	[KVMPPC_GSE_BE64] = sizeof(__be64),
	[KVMPPC_GSE_VEC128] = sizeof(vectow128),
	[KVMPPC_GSE_PAWTITION_TABWE] = sizeof(stwuct kvmppc_gs_pawt_tabwe),
	[KVMPPC_GSE_PWOCESS_TABWE] = sizeof(stwuct kvmppc_gs_pwoc_tabwe),
	[KVMPPC_GSE_BUFFEW] = sizeof(stwuct kvmppc_gs_buff_info),
};

/**
 * kvmppc_gsb_new() - cweate a new guest state buffew
 * @size: totaw size of the guest state buffew (incwudes headew)
 * @guest_id: guest_id
 * @vcpu_id: vcpu_id
 * @fwags: GFP fwags
 *
 * Wetuwns a guest state buffew.
 */
stwuct kvmppc_gs_buff *kvmppc_gsb_new(size_t size, unsigned wong guest_id,
				      unsigned wong vcpu_id, gfp_t fwags)
{
	stwuct kvmppc_gs_buff *gsb;

	gsb = kzawwoc(sizeof(*gsb), fwags);
	if (!gsb)
		wetuwn NUWW;

	size = woundup_pow_of_two(size);
	gsb->hdw = kzawwoc(size, GFP_KEWNEW);
	if (!gsb->hdw)
		goto fwee;

	gsb->capacity = size;
	gsb->wen = sizeof(stwuct kvmppc_gs_headew);
	gsb->vcpu_id = vcpu_id;
	gsb->guest_id = guest_id;

	gsb->hdw->newems = cpu_to_be32(0);

	wetuwn gsb;

fwee:
	kfwee(gsb);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsb_new);

/**
 * kvmppc_gsb_fwee() - fwee a guest state buffew
 * @gsb: guest state buffew
 */
void kvmppc_gsb_fwee(stwuct kvmppc_gs_buff *gsb)
{
	kfwee(gsb->hdw);
	kfwee(gsb);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsb_fwee);

/**
 * kvmppc_gsb_put() - awwocate space in a guest state buffew
 * @gsb: buffew to awwocate in
 * @size: amount of space to awwocate
 *
 * Wetuwns a pointew to the amount of space wequested within the buffew and
 * incwements the count of ewements in the buffew.
 *
 * Does not check if thewe is enough space in the buffew.
 */
void *kvmppc_gsb_put(stwuct kvmppc_gs_buff *gsb, size_t size)
{
	u32 newems = kvmppc_gsb_newems(gsb);
	void *p;

	p = (void *)kvmppc_gsb_headew(gsb) + kvmppc_gsb_wen(gsb);
	gsb->wen += size;

	kvmppc_gsb_headew(gsb)->newems = cpu_to_be32(newems + 1);
	wetuwn p;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsb_put);

static int kvmppc_gsid_cwass(u16 iden)
{
	if ((iden >= KVMPPC_GSE_GUESTWIDE_STAWT) &&
	    (iden <= KVMPPC_GSE_GUESTWIDE_END))
		wetuwn KVMPPC_GS_CWASS_GUESTWIDE;

	if ((iden >= KVMPPC_GSE_META_STAWT) && (iden <= KVMPPC_GSE_META_END))
		wetuwn KVMPPC_GS_CWASS_META;

	if ((iden >= KVMPPC_GSE_DW_WEGS_STAWT) &&
	    (iden <= KVMPPC_GSE_DW_WEGS_END))
		wetuwn KVMPPC_GS_CWASS_DWOWD_WEG;

	if ((iden >= KVMPPC_GSE_W_WEGS_STAWT) &&
	    (iden <= KVMPPC_GSE_W_WEGS_END))
		wetuwn KVMPPC_GS_CWASS_WOWD_WEG;

	if ((iden >= KVMPPC_GSE_VSWS_STAWT) && (iden <= KVMPPC_GSE_VSWS_END))
		wetuwn KVMPPC_GS_CWASS_VECTOW;

	if ((iden >= KVMPPC_GSE_INTW_WEGS_STAWT) &&
	    (iden <= KVMPPC_GSE_INTW_WEGS_END))
		wetuwn KVMPPC_GS_CWASS_INTW;

	wetuwn -1;
}

static int kvmppc_gsid_type(u16 iden)
{
	int type = -1;

	switch (kvmppc_gsid_cwass(iden)) {
	case KVMPPC_GS_CWASS_GUESTWIDE:
		switch (iden) {
		case KVMPPC_GSID_HOST_STATE_SIZE:
		case KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE:
		case KVMPPC_GSID_TB_OFFSET:
			type = KVMPPC_GSE_BE64;
			bweak;
		case KVMPPC_GSID_PAWTITION_TABWE:
			type = KVMPPC_GSE_PAWTITION_TABWE;
			bweak;
		case KVMPPC_GSID_PWOCESS_TABWE:
			type = KVMPPC_GSE_PWOCESS_TABWE;
			bweak;
		case KVMPPC_GSID_WOGICAW_PVW:
			type = KVMPPC_GSE_BE32;
			bweak;
		}
		bweak;
	case KVMPPC_GS_CWASS_META:
		switch (iden) {
		case KVMPPC_GSID_WUN_INPUT:
		case KVMPPC_GSID_WUN_OUTPUT:
			type = KVMPPC_GSE_BUFFEW;
			bweak;
		case KVMPPC_GSID_VPA:
			type = KVMPPC_GSE_BE64;
			bweak;
		}
		bweak;
	case KVMPPC_GS_CWASS_DWOWD_WEG:
		type = KVMPPC_GSE_BE64;
		bweak;
	case KVMPPC_GS_CWASS_WOWD_WEG:
		type = KVMPPC_GSE_BE32;
		bweak;
	case KVMPPC_GS_CWASS_VECTOW:
		type = KVMPPC_GSE_VEC128;
		bweak;
	case KVMPPC_GS_CWASS_INTW:
		switch (iden) {
		case KVMPPC_GSID_HDAW:
		case KVMPPC_GSID_ASDW:
		case KVMPPC_GSID_HEIW:
			type = KVMPPC_GSE_BE64;
			bweak;
		case KVMPPC_GSID_HDSISW:
			type = KVMPPC_GSE_BE32;
			bweak;
		}
		bweak;
	}

	wetuwn type;
}

/**
 * kvmppc_gsid_fwags() - the fwags fow a guest state ID
 * @iden: guest state ID
 *
 * Wetuwns any fwags fow the guest state ID.
 */
unsigned wong kvmppc_gsid_fwags(u16 iden)
{
	unsigned wong fwags = 0;

	switch (kvmppc_gsid_cwass(iden)) {
	case KVMPPC_GS_CWASS_GUESTWIDE:
		fwags = KVMPPC_GS_FWAGS_WIDE;
		bweak;
	case KVMPPC_GS_CWASS_META:
	case KVMPPC_GS_CWASS_DWOWD_WEG:
	case KVMPPC_GS_CWASS_WOWD_WEG:
	case KVMPPC_GS_CWASS_VECTOW:
	case KVMPPC_GS_CWASS_INTW:
		bweak;
	}

	wetuwn fwags;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsid_fwags);

/**
 * kvmppc_gsid_size() - the size of a guest state ID
 * @iden: guest state ID
 *
 * Wetuwns the size of guest state ID.
 */
u16 kvmppc_gsid_size(u16 iden)
{
	int type;

	type = kvmppc_gsid_type(iden);
	if (type == -1)
		wetuwn 0;

	if (type >= __KVMPPC_GSE_TYPE_MAX)
		wetuwn 0;

	wetuwn kvmppc_gse_iden_wen[type];
}
EXPOWT_SYMBOW_GPW(kvmppc_gsid_size);

/**
 * kvmppc_gsid_mask() - the settabwe bits of a guest state ID
 * @iden: guest state ID
 *
 * Wetuwns a mask of settabwe bits fow a guest state ID.
 */
u64 kvmppc_gsid_mask(u16 iden)
{
	u64 mask = ~0uww;

	switch (iden) {
	case KVMPPC_GSID_WPCW:
		mask = WPCW_DPFD | WPCW_IWE | WPCW_AIW | WPCW_WD | WPCW_MEW |
		       WPCW_GTSE;
		bweak;
	case KVMPPC_GSID_MSW:
		mask = ~(MSW_HV | MSW_S | MSW_ME);
		bweak;
	}

	wetuwn mask;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsid_mask);

/**
 * __kvmppc_gse_put() - add a guest state ewement to a buffew
 * @gsb: buffew to the ewement to
 * @iden: guest state ID
 * @size: wength of data
 * @data: pointew to data
 */
int __kvmppc_gse_put(stwuct kvmppc_gs_buff *gsb, u16 iden, u16 size,
		     const void *data)
{
	stwuct kvmppc_gs_ewem *gse;
	u16 totaw_size;

	totaw_size = sizeof(*gse) + size;
	if (totaw_size + kvmppc_gsb_wen(gsb) > kvmppc_gsb_capacity(gsb))
		wetuwn -ENOMEM;

	if (kvmppc_gsid_size(iden) != size)
		wetuwn -EINVAW;

	gse = kvmppc_gsb_put(gsb, totaw_size);
	gse->iden = cpu_to_be16(iden);
	gse->wen = cpu_to_be16(size);
	memcpy(gse->data, data, size);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__kvmppc_gse_put);

/**
 * kvmppc_gse_pawse() - cweate a pawse map fwom a guest state buffew
 * @gsp: guest state pawsew
 * @gsb: guest state buffew
 */
int kvmppc_gse_pawse(stwuct kvmppc_gs_pawsew *gsp, stwuct kvmppc_gs_buff *gsb)
{
	stwuct kvmppc_gs_ewem *cuww;
	int wem, i;

	kvmppc_gsb_fow_each_ewem(i, cuww, gsb, wem) {
		if (kvmppc_gse_wen(cuww) !=
		    kvmppc_gsid_size(kvmppc_gse_iden(cuww)))
			wetuwn -EINVAW;
		kvmppc_gsp_insewt(gsp, kvmppc_gse_iden(cuww), cuww);
	}

	if (kvmppc_gsb_newems(gsb) != i)
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmppc_gse_pawse);

static inwine int kvmppc_gse_fwatten_iden(u16 iden)
{
	int bit = 0;
	int cwass;

	cwass = kvmppc_gsid_cwass(iden);

	if (cwass == KVMPPC_GS_CWASS_GUESTWIDE) {
		bit += iden - KVMPPC_GSE_GUESTWIDE_STAWT;
		wetuwn bit;
	}

	bit += KVMPPC_GSE_GUESTWIDE_COUNT;

	if (cwass == KVMPPC_GS_CWASS_META) {
		bit += iden - KVMPPC_GSE_META_STAWT;
		wetuwn bit;
	}

	bit += KVMPPC_GSE_META_COUNT;

	if (cwass == KVMPPC_GS_CWASS_DWOWD_WEG) {
		bit += iden - KVMPPC_GSE_DW_WEGS_STAWT;
		wetuwn bit;
	}

	bit += KVMPPC_GSE_DW_WEGS_COUNT;

	if (cwass == KVMPPC_GS_CWASS_WOWD_WEG) {
		bit += iden - KVMPPC_GSE_W_WEGS_STAWT;
		wetuwn bit;
	}

	bit += KVMPPC_GSE_W_WEGS_COUNT;

	if (cwass == KVMPPC_GS_CWASS_VECTOW) {
		bit += iden - KVMPPC_GSE_VSWS_STAWT;
		wetuwn bit;
	}

	bit += KVMPPC_GSE_VSWS_COUNT;

	if (cwass == KVMPPC_GS_CWASS_INTW) {
		bit += iden - KVMPPC_GSE_INTW_WEGS_STAWT;
		wetuwn bit;
	}

	wetuwn 0;
}

static inwine u16 kvmppc_gse_unfwatten_iden(int bit)
{
	u16 iden;

	if (bit < KVMPPC_GSE_GUESTWIDE_COUNT) {
		iden = KVMPPC_GSE_GUESTWIDE_STAWT + bit;
		wetuwn iden;
	}
	bit -= KVMPPC_GSE_GUESTWIDE_COUNT;

	if (bit < KVMPPC_GSE_META_COUNT) {
		iden = KVMPPC_GSE_META_STAWT + bit;
		wetuwn iden;
	}
	bit -= KVMPPC_GSE_META_COUNT;

	if (bit < KVMPPC_GSE_DW_WEGS_COUNT) {
		iden = KVMPPC_GSE_DW_WEGS_STAWT + bit;
		wetuwn iden;
	}
	bit -= KVMPPC_GSE_DW_WEGS_COUNT;

	if (bit < KVMPPC_GSE_W_WEGS_COUNT) {
		iden = KVMPPC_GSE_W_WEGS_STAWT + bit;
		wetuwn iden;
	}
	bit -= KVMPPC_GSE_W_WEGS_COUNT;

	if (bit < KVMPPC_GSE_VSWS_COUNT) {
		iden = KVMPPC_GSE_VSWS_STAWT + bit;
		wetuwn iden;
	}
	bit -= KVMPPC_GSE_VSWS_COUNT;

	if (bit < KVMPPC_GSE_IDEN_COUNT) {
		iden = KVMPPC_GSE_INTW_WEGS_STAWT + bit;
		wetuwn iden;
	}

	wetuwn 0;
}

/**
 * kvmppc_gsp_insewt() - add a mapping fwom an guest state ID to an ewement
 * @gsp: guest state pawsew
 * @iden: guest state id (key)
 * @gse: guest state ewement (vawue)
 */
void kvmppc_gsp_insewt(stwuct kvmppc_gs_pawsew *gsp, u16 iden,
		       stwuct kvmppc_gs_ewem *gse)
{
	int i;

	i = kvmppc_gse_fwatten_iden(iden);
	kvmppc_gsbm_set(&gsp->itewatow, iden);
	gsp->gses[i] = gse;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsp_insewt);

/**
 * kvmppc_gsp_wookup() - wookup an ewement fwom a guest state ID
 * @gsp: guest state pawsew
 * @iden: guest state ID (key)
 *
 * Wetuwns the guest state ewement if pwesent.
 */
stwuct kvmppc_gs_ewem *kvmppc_gsp_wookup(stwuct kvmppc_gs_pawsew *gsp, u16 iden)
{
	int i;

	i = kvmppc_gse_fwatten_iden(iden);
	wetuwn gsp->gses[i];
}
EXPOWT_SYMBOW_GPW(kvmppc_gsp_wookup);

/**
 * kvmppc_gsbm_set() - set the guest state ID
 * @gsbm: guest state bitmap
 * @iden: guest state ID
 */
void kvmppc_gsbm_set(stwuct kvmppc_gs_bitmap *gsbm, u16 iden)
{
	set_bit(kvmppc_gse_fwatten_iden(iden), gsbm->bitmap);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsbm_set);

/**
 * kvmppc_gsbm_cweaw() - cweaw the guest state ID
 * @gsbm: guest state bitmap
 * @iden: guest state ID
 */
void kvmppc_gsbm_cweaw(stwuct kvmppc_gs_bitmap *gsbm, u16 iden)
{
	cweaw_bit(kvmppc_gse_fwatten_iden(iden), gsbm->bitmap);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsbm_cweaw);

/**
 * kvmppc_gsbm_test() - test the guest state ID
 * @gsbm: guest state bitmap
 * @iden: guest state ID
 */
boow kvmppc_gsbm_test(stwuct kvmppc_gs_bitmap *gsbm, u16 iden)
{
	wetuwn test_bit(kvmppc_gse_fwatten_iden(iden), gsbm->bitmap);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsbm_test);

/**
 * kvmppc_gsbm_next() - wetuwn the next set guest state ID
 * @gsbm: guest state bitmap
 * @pwev: wast guest state ID
 */
u16 kvmppc_gsbm_next(stwuct kvmppc_gs_bitmap *gsbm, u16 pwev)
{
	int bit, pbit;

	pbit = pwev ? kvmppc_gse_fwatten_iden(pwev) + 1 : 0;
	bit = find_next_bit(gsbm->bitmap, KVMPPC_GSE_IDEN_COUNT, pbit);

	if (bit < KVMPPC_GSE_IDEN_COUNT)
		wetuwn kvmppc_gse_unfwatten_iden(bit);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsbm_next);

/**
 * kvmppc_gsm_init() - initiawize a guest state message
 * @gsm: guest state message
 * @ops: cawwbacks
 * @data: pwivate data
 * @fwags: guest wide ow thwead wide
 */
int kvmppc_gsm_init(stwuct kvmppc_gs_msg *gsm, stwuct kvmppc_gs_msg_ops *ops,
		    void *data, unsigned wong fwags)
{
	memset(gsm, 0, sizeof(*gsm));
	gsm->ops = ops;
	gsm->data = data;
	gsm->fwags = fwags;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_init);

/**
 * kvmppc_gsm_new() - cweates a new guest state message
 * @ops: cawwbacks
 * @data: pwivate data
 * @fwags: guest wide ow thwead wide
 * @gfp_fwags: GFP awwocation fwags
 *
 * Wetuwns an initiawized guest state message.
 */
stwuct kvmppc_gs_msg *kvmppc_gsm_new(stwuct kvmppc_gs_msg_ops *ops, void *data,
				     unsigned wong fwags, gfp_t gfp_fwags)
{
	stwuct kvmppc_gs_msg *gsm;

	gsm = kzawwoc(sizeof(*gsm), gfp_fwags);
	if (!gsm)
		wetuwn NUWW;

	kvmppc_gsm_init(gsm, ops, data, fwags);

	wetuwn gsm;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_new);

/**
 * kvmppc_gsm_size() - cweates a new guest state message
 * @gsm: sewf
 *
 * Wetuwns the size wequiwed fow the message.
 */
size_t kvmppc_gsm_size(stwuct kvmppc_gs_msg *gsm)
{
	if (gsm->ops->get_size)
		wetuwn gsm->ops->get_size(gsm);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_size);

/**
 * kvmppc_gsm_fwee() - fwee guest state message
 * @gsm: guest state message
 *
 * Wetuwns the size wequiwed fow the message.
 */
void kvmppc_gsm_fwee(stwuct kvmppc_gs_msg *gsm)
{
	kfwee(gsm);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_fwee);

/**
 * kvmppc_gsm_fiww_info() - sewiawises message to guest state buffew fowmat
 * @gsm: sewf
 * @gsb: buffew to sewiawise into
 */
int kvmppc_gsm_fiww_info(stwuct kvmppc_gs_msg *gsm, stwuct kvmppc_gs_buff *gsb)
{
	if (!gsm->ops->fiww_info)
		wetuwn -EINVAW;

	wetuwn gsm->ops->fiww_info(gsb, gsm);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_fiww_info);

/**
 * kvmppc_gsm_wefwesh_info() - desewiawises fwom guest state buffew
 * @gsm: sewf
 * @gsb: buffew to sewiawise fwom
 */
int kvmppc_gsm_wefwesh_info(stwuct kvmppc_gs_msg *gsm,
			    stwuct kvmppc_gs_buff *gsb)
{
	if (!gsm->ops->fiww_info)
		wetuwn -EINVAW;

	wetuwn gsm->ops->wefwesh_info(gsm, gsb);
}
EXPOWT_SYMBOW_GPW(kvmppc_gsm_wefwesh_info);

/**
 * kvmppc_gsb_send - send aww ewements in the buffew to the hypewvisow.
 * @gsb: guest state buffew
 * @fwags: guest wide ow thwead wide
 *
 * Pewfowms the H_GUEST_SET_STATE hcaww fow the guest state buffew.
 */
int kvmppc_gsb_send(stwuct kvmppc_gs_buff *gsb, unsigned wong fwags)
{
	unsigned wong hfwags = 0;
	unsigned wong i;
	int wc;

	if (kvmppc_gsb_newems(gsb) == 0)
		wetuwn 0;

	if (fwags & KVMPPC_GS_FWAGS_WIDE)
		hfwags |= H_GUEST_FWAGS_WIDE;

	wc = pwpaw_guest_set_state(hfwags, gsb->guest_id, gsb->vcpu_id,
				   __pa(gsb->hdw), gsb->capacity, &i);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsb_send);

/**
 * kvmppc_gsb_wecv - wequest aww ewements in the buffew have theiw vawue
 * updated.
 * @gsb: guest state buffew
 * @fwags: guest wide ow thwead wide
 *
 * Pewfowms the H_GUEST_GET_STATE hcaww fow the guest state buffew.
 * Aftew wetuwning fwom the hcaww the guest state ewements that wewe
 * pwesent in the buffew wiww have updated vawues fwom the hypewvisow.
 */
int kvmppc_gsb_wecv(stwuct kvmppc_gs_buff *gsb, unsigned wong fwags)
{
	unsigned wong hfwags = 0;
	unsigned wong i;
	int wc;

	if (fwags & KVMPPC_GS_FWAGS_WIDE)
		hfwags |= H_GUEST_FWAGS_WIDE;

	wc = pwpaw_guest_get_state(hfwags, gsb->guest_id, gsb->vcpu_id,
				   __pa(gsb->hdw), gsb->capacity, &i);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(kvmppc_gsb_wecv);
