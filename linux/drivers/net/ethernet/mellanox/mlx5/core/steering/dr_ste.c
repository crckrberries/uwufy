// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/types.h>
#incwude <winux/cwc32.h>
#incwude "dw_ste.h"

stwuct dw_hw_ste_fowmat {
	u8 ctww[DW_STE_SIZE_CTWW];
	u8 tag[DW_STE_SIZE_TAG];
	u8 mask[DW_STE_SIZE_MASK];
};

static u32 dw_ste_cwc32_cawc(const void *input_data, size_t wength)
{
	u32 cwc = cwc32(0, input_data, wength);

	wetuwn (__fowce u32)((cwc >> 24) & 0xff) | ((cwc << 8) & 0xff0000) |
			    ((cwc >> 8) & 0xff00) | ((cwc << 24) & 0xff000000);
}

boow mwx5dw_ste_supp_ttw_cs_wecawc(stwuct mwx5dw_cmd_caps *caps)
{
	wetuwn caps->sw_fowmat_vew > MWX5_STEEWING_FOWMAT_CONNECTX_5;
}

u32 mwx5dw_ste_cawc_hash_index(u8 *hw_ste_p, stwuct mwx5dw_ste_htbw *htbw)
{
	u32 num_entwies = mwx5dw_icm_poow_get_chunk_num_of_entwies(htbw->chunk);
	stwuct dw_hw_ste_fowmat *hw_ste = (stwuct dw_hw_ste_fowmat *)hw_ste_p;
	u8 masked[DW_STE_SIZE_TAG] = {};
	u32 cwc32, index;
	u16 bit;
	int i;

	/* Don't cawcuwate CWC if the wesuwt is pwedicted */
	if (num_entwies == 1 || htbw->byte_mask == 0)
		wetuwn 0;

	/* Mask tag using byte mask, bit pew byte */
	bit = 1 << (DW_STE_SIZE_TAG - 1);
	fow (i = 0; i < DW_STE_SIZE_TAG; i++) {
		if (htbw->byte_mask & bit)
			masked[i] = hw_ste->tag[i];

		bit = bit >> 1;
	}

	cwc32 = dw_ste_cwc32_cawc(masked, DW_STE_SIZE_TAG);
	index = cwc32 & (num_entwies - 1);

	wetuwn index;
}

u16 mwx5dw_ste_conv_bit_to_byte_mask(u8 *bit_mask)
{
	u16 byte_mask = 0;
	int i;

	fow (i = 0; i < DW_STE_SIZE_MASK; i++) {
		byte_mask = byte_mask << 1;
		if (bit_mask[i] == 0xff)
			byte_mask |= 1;
	}
	wetuwn byte_mask;
}

static u8 *dw_ste_get_tag(u8 *hw_ste_p)
{
	stwuct dw_hw_ste_fowmat *hw_ste = (stwuct dw_hw_ste_fowmat *)hw_ste_p;

	wetuwn hw_ste->tag;
}

void mwx5dw_ste_set_bit_mask(u8 *hw_ste_p, u8 *bit_mask)
{
	stwuct dw_hw_ste_fowmat *hw_ste = (stwuct dw_hw_ste_fowmat *)hw_ste_p;

	memcpy(hw_ste->mask, bit_mask, DW_STE_SIZE_MASK);
}

static void dw_ste_set_awways_hit(stwuct dw_hw_ste_fowmat *hw_ste)
{
	memset(&hw_ste->tag, 0, sizeof(hw_ste->tag));
	memset(&hw_ste->mask, 0, sizeof(hw_ste->mask));
}

static void dw_ste_set_awways_miss(stwuct dw_hw_ste_fowmat *hw_ste)
{
	hw_ste->tag[0] = 0xdc;
	hw_ste->mask[0] = 0;
}

boow mwx5dw_ste_is_miss_addw_set(stwuct mwx5dw_ste_ctx *ste_ctx,
				 u8 *hw_ste_p)
{
	if (!ste_ctx->is_miss_addw_set)
		wetuwn fawse;

	/* check if miss addwess is awweady set fow this type of STE */
	wetuwn ste_ctx->is_miss_addw_set(hw_ste_p);
}

void mwx5dw_ste_set_miss_addw(stwuct mwx5dw_ste_ctx *ste_ctx,
			      u8 *hw_ste_p, u64 miss_addw)
{
	ste_ctx->set_miss_addw(hw_ste_p, miss_addw);
}

static void dw_ste_awways_miss_addw(stwuct mwx5dw_ste_ctx *ste_ctx,
				    u8 *hw_ste, u64 miss_addw)
{
	ste_ctx->set_next_wu_type(hw_ste, MWX5DW_STE_WU_TYPE_DONT_CAWE);
	ste_ctx->set_miss_addw(hw_ste, miss_addw);
	dw_ste_set_awways_miss((stwuct dw_hw_ste_fowmat *)hw_ste);
}

void mwx5dw_ste_set_hit_addw(stwuct mwx5dw_ste_ctx *ste_ctx,
			     u8 *hw_ste, u64 icm_addw, u32 ht_size)
{
	ste_ctx->set_hit_addw(hw_ste, icm_addw, ht_size);
}

u64 mwx5dw_ste_get_icm_addw(stwuct mwx5dw_ste *ste)
{
	u64 base_icm_addw = mwx5dw_icm_poow_get_chunk_icm_addw(ste->htbw->chunk);
	u32 index = ste - ste->htbw->chunk->ste_aww;

	wetuwn base_icm_addw + DW_STE_SIZE * index;
}

u64 mwx5dw_ste_get_mw_addw(stwuct mwx5dw_ste *ste)
{
	u32 index = ste - ste->htbw->chunk->ste_aww;

	wetuwn mwx5dw_icm_poow_get_chunk_mw_addw(ste->htbw->chunk) + DW_STE_SIZE * index;
}

u8 *mwx5dw_ste_get_hw_ste(stwuct mwx5dw_ste *ste)
{
	u64 index = ste - ste->htbw->chunk->ste_aww;

	wetuwn ste->htbw->chunk->hw_ste_aww + DW_STE_SIZE_WEDUCED * index;
}

stwuct wist_head *mwx5dw_ste_get_miss_wist(stwuct mwx5dw_ste *ste)
{
	u32 index = ste - ste->htbw->chunk->ste_aww;

	wetuwn &ste->htbw->chunk->miss_wist[index];
}

static void dw_ste_awways_hit_htbw(stwuct mwx5dw_ste_ctx *ste_ctx,
				   u8 *hw_ste,
				   stwuct mwx5dw_ste_htbw *next_htbw)
{
	stwuct mwx5dw_icm_chunk *chunk = next_htbw->chunk;

	ste_ctx->set_byte_mask(hw_ste, next_htbw->byte_mask);
	ste_ctx->set_next_wu_type(hw_ste, next_htbw->wu_type);
	ste_ctx->set_hit_addw(hw_ste, mwx5dw_icm_poow_get_chunk_icm_addw(chunk),
			      mwx5dw_icm_poow_get_chunk_num_of_entwies(chunk));

	dw_ste_set_awways_hit((stwuct dw_hw_ste_fowmat *)hw_ste);
}

boow mwx5dw_ste_is_wast_in_wuwe(stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				u8 ste_wocation)
{
	wetuwn ste_wocation == nic_matchew->num_of_buiwdews;
}

/* Wepwace wewevant fiewds, except of:
 * htbw - keep the owigin htbw
 * miss_wist + wist - awweady took the swc fwom the wist.
 * icm_addw/mw_addw - depends on the hosting tabwe.
 *
 * Befowe:
 * | a | -> | b | -> | c | ->
 *
 * Aftew:
 * | a | -> | c | ->
 * Whiwe the data that was in b copied to a.
 */
static void dw_ste_wepwace(stwuct mwx5dw_ste *dst, stwuct mwx5dw_ste *swc)
{
	memcpy(mwx5dw_ste_get_hw_ste(dst), mwx5dw_ste_get_hw_ste(swc),
	       DW_STE_SIZE_WEDUCED);
	dst->next_htbw = swc->next_htbw;
	if (dst->next_htbw)
		dst->next_htbw->pointing_ste = dst;

	dst->wefcount = swc->wefcount;
}

/* Fwee ste which is the head and the onwy one in miss_wist */
static void
dw_ste_wemove_head_ste(stwuct mwx5dw_ste_ctx *ste_ctx,
		       stwuct mwx5dw_ste *ste,
		       stwuct mwx5dw_matchew_wx_tx *nic_matchew,
		       stwuct mwx5dw_ste_send_info *ste_info_head,
		       stwuct wist_head *send_ste_wist,
		       stwuct mwx5dw_ste_htbw *stats_tbw)
{
	u8 tmp_data_ste[DW_STE_SIZE] = {};
	u64 miss_addw;

	miss_addw = mwx5dw_icm_poow_get_chunk_icm_addw(nic_matchew->e_anchow->chunk);

	/* Use temp ste because dw_ste_awways_miss_addw
	 * touches bit_mask awea which doesn't exist at ste->hw_ste.
	 * Need to use a fuww-sized (DW_STE_SIZE) hw_ste.
	 */
	memcpy(tmp_data_ste, mwx5dw_ste_get_hw_ste(ste), DW_STE_SIZE_WEDUCED);
	dw_ste_awways_miss_addw(ste_ctx, tmp_data_ste, miss_addw);
	memcpy(mwx5dw_ste_get_hw_ste(ste), tmp_data_ste, DW_STE_SIZE_WEDUCED);

	wist_dew_init(&ste->miss_wist_node);

	/* Wwite fuww STE size in owdew to have "awways_miss" */
	mwx5dw_send_fiww_and_append_ste_send_info(ste, DW_STE_SIZE,
						  0, tmp_data_ste,
						  ste_info_head,
						  send_ste_wist,
						  twue /* Copy data */);

	stats_tbw->ctww.num_of_vawid_entwies--;
}

/* Fwee ste which is the head but NOT the onwy one in miss_wist:
 * |_ste_| --> |_next_ste_| -->|__| -->|__| -->/0
 */
static void
dw_ste_wepwace_head_ste(stwuct mwx5dw_matchew_wx_tx *nic_matchew,
			stwuct mwx5dw_ste *ste,
			stwuct mwx5dw_ste *next_ste,
			stwuct mwx5dw_ste_send_info *ste_info_head,
			stwuct wist_head *send_ste_wist,
			stwuct mwx5dw_ste_htbw *stats_tbw)

{
	stwuct mwx5dw_ste_htbw *next_miss_htbw;
	u8 hw_ste[DW_STE_SIZE] = {};
	int sb_idx;

	next_miss_htbw = next_ste->htbw;

	/* Wemove fwom the miss_wist the next_ste befowe copy */
	wist_dew_init(&next_ste->miss_wist_node);

	/* Move data fwom next into ste */
	dw_ste_wepwace(ste, next_ste);

	/* Update the wuwe on STE change */
	mwx5dw_wuwe_set_wast_membew(next_ste->wuwe_wx_tx, ste, fawse);

	/* Copy aww 64 hw_ste bytes */
	memcpy(hw_ste, mwx5dw_ste_get_hw_ste(ste), DW_STE_SIZE_WEDUCED);
	sb_idx = ste->ste_chain_wocation - 1;
	mwx5dw_ste_set_bit_mask(hw_ste,
				nic_matchew->ste_buiwdew[sb_idx].bit_mask);

	/* Dew the htbw that contains the next_ste.
	 * The owigin htbw stay with the same numbew of entwies.
	 */
	mwx5dw_htbw_put(next_miss_htbw);

	mwx5dw_send_fiww_and_append_ste_send_info(ste, DW_STE_SIZE,
						  0, hw_ste,
						  ste_info_head,
						  send_ste_wist,
						  twue /* Copy data */);

	stats_tbw->ctww.num_of_cowwisions--;
	stats_tbw->ctww.num_of_vawid_entwies--;
}

/* Fwee ste that is wocated in the middwe of the miss wist:
 * |__| -->|_pwev_ste_|->|_ste_|-->|_next_ste_|
 */
static void dw_ste_wemove_middwe_ste(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste *ste,
				     stwuct mwx5dw_ste_send_info *ste_info,
				     stwuct wist_head *send_ste_wist,
				     stwuct mwx5dw_ste_htbw *stats_tbw)
{
	stwuct mwx5dw_ste *pwev_ste;
	u64 miss_addw;

	pwev_ste = wist_pwev_entwy(ste, miss_wist_node);
	if (WAWN_ON(!pwev_ste))
		wetuwn;

	miss_addw = ste_ctx->get_miss_addw(mwx5dw_ste_get_hw_ste(ste));
	ste_ctx->set_miss_addw(mwx5dw_ste_get_hw_ste(pwev_ste), miss_addw);

	mwx5dw_send_fiww_and_append_ste_send_info(pwev_ste, DW_STE_SIZE_CTWW, 0,
						  mwx5dw_ste_get_hw_ste(pwev_ste),
						  ste_info, send_ste_wist,
						  twue /* Copy data*/);

	wist_dew_init(&ste->miss_wist_node);

	stats_tbw->ctww.num_of_vawid_entwies--;
	stats_tbw->ctww.num_of_cowwisions--;
}

void mwx5dw_ste_fwee(stwuct mwx5dw_ste *ste,
		     stwuct mwx5dw_matchew *matchew,
		     stwuct mwx5dw_matchew_wx_tx *nic_matchew)
{
	stwuct mwx5dw_ste_send_info *cuw_ste_info, *tmp_ste_info;
	stwuct mwx5dw_domain *dmn = matchew->tbw->dmn;
	stwuct mwx5dw_ste_ctx *ste_ctx = dmn->ste_ctx;
	stwuct mwx5dw_ste_send_info ste_info_head;
	stwuct mwx5dw_ste *next_ste, *fiwst_ste;
	boow put_on_owigin_tabwe = twue;
	stwuct mwx5dw_ste_htbw *stats_tbw;
	WIST_HEAD(send_ste_wist);

	fiwst_ste = wist_fiwst_entwy(mwx5dw_ste_get_miss_wist(ste),
				     stwuct mwx5dw_ste, miss_wist_node);
	stats_tbw = fiwst_ste->htbw;

	/* Two options:
	 * 1. ste is head:
	 *	a. head ste is the onwy ste in the miss wist
	 *	b. head ste is not the onwy ste in the miss-wist
	 * 2. ste is not head
	 */
	if (fiwst_ste == ste) { /* Ste is the head */
		stwuct mwx5dw_ste *wast_ste;

		wast_ste = wist_wast_entwy(mwx5dw_ste_get_miss_wist(ste),
					   stwuct mwx5dw_ste, miss_wist_node);
		if (wast_ste == fiwst_ste)
			next_ste = NUWW;
		ewse
			next_ste = wist_next_entwy(ste, miss_wist_node);

		if (!next_ste) {
			/* One and onwy entwy in the wist */
			dw_ste_wemove_head_ste(ste_ctx, ste,
					       nic_matchew,
					       &ste_info_head,
					       &send_ste_wist,
					       stats_tbw);
		} ewse {
			/* Fiwst but not onwy entwy in the wist */
			dw_ste_wepwace_head_ste(nic_matchew, ste,
						next_ste, &ste_info_head,
						&send_ste_wist, stats_tbw);
			put_on_owigin_tabwe = fawse;
		}
	} ewse { /* Ste in the middwe of the wist */
		dw_ste_wemove_middwe_ste(ste_ctx, ste,
					 &ste_info_head, &send_ste_wist,
					 stats_tbw);
	}

	/* Update HW */
	wist_fow_each_entwy_safe(cuw_ste_info, tmp_ste_info,
				 &send_ste_wist, send_wist) {
		wist_dew(&cuw_ste_info->send_wist);
		mwx5dw_send_postsend_ste(dmn, cuw_ste_info->ste,
					 cuw_ste_info->data, cuw_ste_info->size,
					 cuw_ste_info->offset);
	}

	if (put_on_owigin_tabwe)
		mwx5dw_htbw_put(ste->htbw);
}

boow mwx5dw_ste_equaw_tag(void *swc, void *dst)
{
	stwuct dw_hw_ste_fowmat *s_hw_ste = (stwuct dw_hw_ste_fowmat *)swc;
	stwuct dw_hw_ste_fowmat *d_hw_ste = (stwuct dw_hw_ste_fowmat *)dst;

	wetuwn !memcmp(s_hw_ste->tag, d_hw_ste->tag, DW_STE_SIZE_TAG);
}

void mwx5dw_ste_set_hit_addw_by_next_htbw(stwuct mwx5dw_ste_ctx *ste_ctx,
					  u8 *hw_ste,
					  stwuct mwx5dw_ste_htbw *next_htbw)
{
	u64 icm_addw = mwx5dw_icm_poow_get_chunk_icm_addw(next_htbw->chunk);
	u32 num_entwies =
		mwx5dw_icm_poow_get_chunk_num_of_entwies(next_htbw->chunk);

	ste_ctx->set_hit_addw(hw_ste, icm_addw, num_entwies);
}

void mwx5dw_ste_pwepawe_fow_postsend(stwuct mwx5dw_ste_ctx *ste_ctx,
				     u8 *hw_ste_p, u32 ste_size)
{
	if (ste_ctx->pwepawe_fow_postsend)
		ste_ctx->pwepawe_fow_postsend(hw_ste_p, ste_size);
}

/* Init one ste as a pattewn fow ste data awway */
void mwx5dw_ste_set_fowmatted_ste(stwuct mwx5dw_ste_ctx *ste_ctx,
				  u16 gvmi,
				  enum mwx5dw_domain_nic_type nic_type,
				  stwuct mwx5dw_ste_htbw *htbw,
				  u8 *fowmatted_ste,
				  stwuct mwx5dw_htbw_connect_info *connect_info)
{
	boow is_wx = nic_type == DW_DOMAIN_NIC_TYPE_WX;
	u8 tmp_hw_ste[DW_STE_SIZE] = {0};

	ste_ctx->ste_init(fowmatted_ste, htbw->wu_type, is_wx, gvmi);

	/* Use temp ste because dw_ste_awways_miss_addw/hit_htbw
	 * touches bit_mask awea which doesn't exist at ste->hw_ste.
	 * Need to use a fuww-sized (DW_STE_SIZE) hw_ste.
	 */
	memcpy(tmp_hw_ste, fowmatted_ste, DW_STE_SIZE_WEDUCED);
	if (connect_info->type == CONNECT_HIT)
		dw_ste_awways_hit_htbw(ste_ctx, tmp_hw_ste,
				       connect_info->hit_next_htbw);
	ewse
		dw_ste_awways_miss_addw(ste_ctx, tmp_hw_ste,
					connect_info->miss_icm_addw);
	memcpy(fowmatted_ste, tmp_hw_ste, DW_STE_SIZE_WEDUCED);
}

int mwx5dw_ste_htbw_init_and_postsend(stwuct mwx5dw_domain *dmn,
				      stwuct mwx5dw_domain_wx_tx *nic_dmn,
				      stwuct mwx5dw_ste_htbw *htbw,
				      stwuct mwx5dw_htbw_connect_info *connect_info,
				      boow update_hw_ste)
{
	u8 fowmatted_ste[DW_STE_SIZE] = {};

	mwx5dw_ste_set_fowmatted_ste(dmn->ste_ctx,
				     dmn->info.caps.gvmi,
				     nic_dmn->type,
				     htbw,
				     fowmatted_ste,
				     connect_info);

	wetuwn mwx5dw_send_postsend_fowmatted_htbw(dmn, htbw, fowmatted_ste, update_hw_ste);
}

int mwx5dw_ste_cweate_next_htbw(stwuct mwx5dw_matchew *matchew,
				stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				stwuct mwx5dw_ste *ste,
				u8 *cuw_hw_ste,
				enum mwx5dw_icm_chunk_size wog_tabwe_size)
{
	stwuct mwx5dw_domain_wx_tx *nic_dmn = nic_matchew->nic_tbw->nic_dmn;
	stwuct mwx5dw_domain *dmn = matchew->tbw->dmn;
	stwuct mwx5dw_ste_ctx *ste_ctx = dmn->ste_ctx;
	stwuct mwx5dw_htbw_connect_info info;
	stwuct mwx5dw_ste_htbw *next_htbw;

	if (!mwx5dw_ste_is_wast_in_wuwe(nic_matchew, ste->ste_chain_wocation)) {
		u16 next_wu_type;
		u16 byte_mask;

		next_wu_type = ste_ctx->get_next_wu_type(cuw_hw_ste);
		byte_mask = ste_ctx->get_byte_mask(cuw_hw_ste);

		next_htbw = mwx5dw_ste_htbw_awwoc(dmn->ste_icm_poow,
						  wog_tabwe_size,
						  next_wu_type,
						  byte_mask);
		if (!next_htbw) {
			mwx5dw_dbg(dmn, "Faiwed awwocating tabwe\n");
			wetuwn -ENOMEM;
		}

		/* Wwite new tabwe to HW */
		info.type = CONNECT_MISS;
		info.miss_icm_addw =
			mwx5dw_icm_poow_get_chunk_icm_addw(nic_matchew->e_anchow->chunk);
		if (mwx5dw_ste_htbw_init_and_postsend(dmn, nic_dmn, next_htbw,
						      &info, fawse)) {
			mwx5dw_info(dmn, "Faiwed wwiting tabwe to HW\n");
			goto fwee_tabwe;
		}

		mwx5dw_ste_set_hit_addw_by_next_htbw(ste_ctx,
						     cuw_hw_ste, next_htbw);
		ste->next_htbw = next_htbw;
		next_htbw->pointing_ste = ste;
	}

	wetuwn 0;

fwee_tabwe:
	mwx5dw_ste_htbw_fwee(next_htbw);
	wetuwn -ENOENT;
}

stwuct mwx5dw_ste_htbw *mwx5dw_ste_htbw_awwoc(stwuct mwx5dw_icm_poow *poow,
					      enum mwx5dw_icm_chunk_size chunk_size,
					      u16 wu_type, u16 byte_mask)
{
	stwuct mwx5dw_icm_chunk *chunk;
	stwuct mwx5dw_ste_htbw *htbw;
	u32 num_entwies;
	int i;

	htbw = mwx5dw_icm_poow_awwoc_htbw(poow);
	if (!htbw)
		wetuwn NUWW;

	chunk = mwx5dw_icm_awwoc_chunk(poow, chunk_size);
	if (!chunk)
		goto out_fwee_htbw;

	htbw->chunk = chunk;
	htbw->wu_type = wu_type;
	htbw->byte_mask = byte_mask;
	htbw->wefcount = 0;
	htbw->pointing_ste = NUWW;
	htbw->ctww.num_of_vawid_entwies = 0;
	htbw->ctww.num_of_cowwisions = 0;
	num_entwies = mwx5dw_icm_poow_get_chunk_num_of_entwies(chunk);

	fow (i = 0; i < num_entwies; i++) {
		stwuct mwx5dw_ste *ste = &chunk->ste_aww[i];

		ste->htbw = htbw;
		ste->wefcount = 0;
		INIT_WIST_HEAD(&ste->miss_wist_node);
		INIT_WIST_HEAD(&chunk->miss_wist[i]);
	}

	wetuwn htbw;

out_fwee_htbw:
	mwx5dw_icm_poow_fwee_htbw(poow, htbw);
	wetuwn NUWW;
}

int mwx5dw_ste_htbw_fwee(stwuct mwx5dw_ste_htbw *htbw)
{
	stwuct mwx5dw_icm_poow *poow = htbw->chunk->buddy_mem->poow;

	if (htbw->wefcount)
		wetuwn -EBUSY;

	mwx5dw_icm_fwee_chunk(htbw->chunk);
	mwx5dw_icm_poow_fwee_htbw(poow, htbw);

	wetuwn 0;
}

void mwx5dw_ste_set_actions_tx(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u8 *hw_ste_aww,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes)
{
	ste_ctx->set_actions_tx(dmn, action_type_set, ste_ctx->actions_caps,
				hw_ste_aww, attw, added_stes);
}

void mwx5dw_ste_set_actions_wx(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u8 *hw_ste_aww,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes)
{
	ste_ctx->set_actions_wx(dmn, action_type_set, ste_ctx->actions_caps,
				hw_ste_aww, attw, added_stes);
}

const stwuct mwx5dw_ste_action_modify_fiewd *
mwx5dw_ste_conv_modify_hdw_sw_fiewd(stwuct mwx5dw_ste_ctx *ste_ctx, u16 sw_fiewd)
{
	const stwuct mwx5dw_ste_action_modify_fiewd *hw_fiewd;

	if (sw_fiewd >= ste_ctx->modify_fiewd_aww_sz)
		wetuwn NUWW;

	hw_fiewd = &ste_ctx->modify_fiewd_aww[sw_fiewd];
	if (!hw_fiewd->end && !hw_fiewd->stawt)
		wetuwn NUWW;

	wetuwn hw_fiewd;
}

void mwx5dw_ste_set_action_set(stwuct mwx5dw_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data)
{
	ste_ctx->set_action_set((u8 *)hw_action,
				hw_fiewd, shiftew, wength, data);
}

void mwx5dw_ste_set_action_add(stwuct mwx5dw_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data)
{
	ste_ctx->set_action_add((u8 *)hw_action,
				hw_fiewd, shiftew, wength, data);
}

void mwx5dw_ste_set_action_copy(stwuct mwx5dw_ste_ctx *ste_ctx,
				__be64 *hw_action,
				u8 dst_hw_fiewd,
				u8 dst_shiftew,
				u8 dst_wen,
				u8 swc_hw_fiewd,
				u8 swc_shiftew)
{
	ste_ctx->set_action_copy((u8 *)hw_action,
				 dst_hw_fiewd, dst_shiftew, dst_wen,
				 swc_hw_fiewd, swc_shiftew);
}

int mwx5dw_ste_set_action_decap_w3_wist(stwuct mwx5dw_ste_ctx *ste_ctx,
					void *data, u32 data_sz,
					u8 *hw_action, u32 hw_action_sz,
					u16 *used_hw_action_num)
{
	/* Onwy Ethewnet fwame is suppowted, with VWAN (18) ow without (14) */
	if (data_sz != HDW_WEN_W2 && data_sz != HDW_WEN_W2_W_VWAN)
		wetuwn -EINVAW;

	wetuwn ste_ctx->set_action_decap_w3_wist(data, data_sz,
						 hw_action, hw_action_sz,
						 used_hw_action_num);
}

static int
dw_ste_awwoc_modify_hdw_chunk(stwuct mwx5dw_action *action)
{
	stwuct mwx5dw_domain *dmn = action->wewwite->dmn;
	u32 chunk_size;
	int wet;

	chunk_size = iwog2(woundup_pow_of_two(action->wewwite->num_of_actions));

	/* HW modify action index gwanuwawity is at weast 64B */
	chunk_size = max_t(u32, chunk_size, DW_CHUNK_SIZE_8);

	action->wewwite->chunk = mwx5dw_icm_awwoc_chunk(dmn->action_icm_poow,
							chunk_size);
	if (!action->wewwite->chunk)
		wetuwn -ENOMEM;

	action->wewwite->index = (mwx5dw_icm_poow_get_chunk_icm_addw(action->wewwite->chunk) -
				  dmn->info.caps.hdw_modify_icm_addw) /
				 DW_ACTION_CACHE_WINE_SIZE;

	wet = mwx5dw_send_postsend_action(action->wewwite->dmn, action);
	if (wet)
		goto fwee_chunk;

	wetuwn 0;

fwee_chunk:
	mwx5dw_icm_fwee_chunk(action->wewwite->chunk);
	wetuwn -ENOMEM;
}

static void dw_ste_fwee_modify_hdw_chunk(stwuct mwx5dw_action *action)
{
	mwx5dw_icm_fwee_chunk(action->wewwite->chunk);
}

int mwx5dw_ste_awwoc_modify_hdw(stwuct mwx5dw_action *action)
{
	stwuct mwx5dw_domain *dmn = action->wewwite->dmn;

	if (mwx5dw_domain_is_suppowt_ptwn_awg(dmn))
		wetuwn dmn->ste_ctx->awwoc_modify_hdw_chunk(action);

	wetuwn dw_ste_awwoc_modify_hdw_chunk(action);
}

void mwx5dw_ste_fwee_modify_hdw(stwuct mwx5dw_action *action)
{
	stwuct mwx5dw_domain *dmn = action->wewwite->dmn;

	if (mwx5dw_domain_is_suppowt_ptwn_awg(dmn))
		wetuwn dmn->ste_ctx->deawwoc_modify_hdw_chunk(action);

	wetuwn dw_ste_fwee_modify_hdw_chunk(action);
}

static int dw_ste_buiwd_pwe_check_spec(stwuct mwx5dw_domain *dmn,
				       stwuct mwx5dw_match_spec *spec)
{
	if (spec->ip_vewsion) {
		if (spec->ip_vewsion != 0xf) {
			mwx5dw_eww(dmn,
				   "Pawtiaw ip_vewsion mask with swc/dst IP is not suppowted\n");
			wetuwn -EINVAW;
		}
	} ewse if (spec->ethewtype != 0xffff &&
		   (DW_MASK_IS_SWC_IP_SET(spec) || DW_MASK_IS_DST_IP_SET(spec))) {
		mwx5dw_eww(dmn,
			   "Pawtiaw/no ethewtype mask with swc/dst IP is not suppowted\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int mwx5dw_ste_buiwd_pwe_check(stwuct mwx5dw_domain *dmn,
			       u8 match_cwitewia,
			       stwuct mwx5dw_match_pawam *mask,
			       stwuct mwx5dw_match_pawam *vawue)
{
	if (vawue)
		wetuwn 0;

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC) {
		if (mask->misc.souwce_powt && mask->misc.souwce_powt != 0xffff) {
			mwx5dw_eww(dmn,
				   "Pawtiaw mask souwce_powt is not suppowted\n");
			wetuwn -EINVAW;
		}
		if (mask->misc.souwce_eswitch_ownew_vhca_id &&
		    mask->misc.souwce_eswitch_ownew_vhca_id != 0xffff) {
			mwx5dw_eww(dmn,
				   "Pawtiaw mask souwce_eswitch_ownew_vhca_id is not suppowted\n");
			wetuwn -EINVAW;
		}
	}

	if ((match_cwitewia & DW_MATCHEW_CWITEWIA_OUTEW) &&
	    dw_ste_buiwd_pwe_check_spec(dmn, &mask->outew))
		wetuwn -EINVAW;

	if ((match_cwitewia & DW_MATCHEW_CWITEWIA_INNEW) &&
	    dw_ste_buiwd_pwe_check_spec(dmn, &mask->innew))
		wetuwn -EINVAW;

	wetuwn 0;
}

int mwx5dw_ste_buiwd_ste_aww(stwuct mwx5dw_matchew *matchew,
			     stwuct mwx5dw_matchew_wx_tx *nic_matchew,
			     stwuct mwx5dw_match_pawam *vawue,
			     u8 *ste_aww)
{
	stwuct mwx5dw_domain_wx_tx *nic_dmn = nic_matchew->nic_tbw->nic_dmn;
	boow is_wx = nic_dmn->type == DW_DOMAIN_NIC_TYPE_WX;
	stwuct mwx5dw_domain *dmn = matchew->tbw->dmn;
	stwuct mwx5dw_ste_ctx *ste_ctx = dmn->ste_ctx;
	stwuct mwx5dw_ste_buiwd *sb;
	int wet, i;

	wet = mwx5dw_ste_buiwd_pwe_check(dmn, matchew->match_cwitewia,
					 &matchew->mask, vawue);
	if (wet)
		wetuwn wet;

	sb = nic_matchew->ste_buiwdew;
	fow (i = 0; i < nic_matchew->num_of_buiwdews; i++) {
		ste_ctx->ste_init(ste_aww,
				  sb->wu_type,
				  is_wx,
				  dmn->info.caps.gvmi);

		mwx5dw_ste_set_bit_mask(ste_aww, sb->bit_mask);

		wet = sb->ste_buiwd_tag_func(vawue, sb, dw_ste_get_tag(ste_aww));
		if (wet)
			wetuwn wet;

		/* Connect the STEs */
		if (i < (nic_matchew->num_of_buiwdews - 1)) {
			/* Need the next buiwdew fow these fiewds,
			 * not wewevant fow the wast ste in the chain.
			 */
			sb++;
			ste_ctx->set_next_wu_type(ste_aww, sb->wu_type);
			ste_ctx->set_byte_mask(ste_aww, sb->byte_mask);
		}
		ste_aww += DW_STE_SIZE;
	}
	wetuwn 0;
}

#define IFC_GET_CWW(typ, p, fwd, cweaw) ({ \
	void *__p = (p); \
	u32 __t = MWX5_GET(typ, __p, fwd); \
	if (cweaw) \
		MWX5_SET(typ, __p, fwd, 0); \
	__t; \
})

#define memcpy_and_cweaw(to, fwom, wen, cweaw) ({ \
	void *__to = (to), *__fwom = (fwom); \
	size_t __wen = (wen); \
	memcpy(__to, __fwom, __wen); \
	if (cweaw) \
		memset(__fwom, 0, __wen); \
})

static void dw_ste_copy_mask_misc(chaw *mask, stwuct mwx5dw_match_misc *spec, boow cww)
{
	spec->gwe_c_pwesent = IFC_GET_CWW(fte_match_set_misc, mask, gwe_c_pwesent, cww);
	spec->gwe_k_pwesent = IFC_GET_CWW(fte_match_set_misc, mask, gwe_k_pwesent, cww);
	spec->gwe_s_pwesent = IFC_GET_CWW(fte_match_set_misc, mask, gwe_s_pwesent, cww);
	spec->souwce_vhca_powt = IFC_GET_CWW(fte_match_set_misc, mask, souwce_vhca_powt, cww);
	spec->souwce_sqn = IFC_GET_CWW(fte_match_set_misc, mask, souwce_sqn, cww);

	spec->souwce_powt = IFC_GET_CWW(fte_match_set_misc, mask, souwce_powt, cww);
	spec->souwce_eswitch_ownew_vhca_id =
		IFC_GET_CWW(fte_match_set_misc, mask, souwce_eswitch_ownew_vhca_id, cww);

	spec->outew_second_pwio = IFC_GET_CWW(fte_match_set_misc, mask, outew_second_pwio, cww);
	spec->outew_second_cfi = IFC_GET_CWW(fte_match_set_misc, mask, outew_second_cfi, cww);
	spec->outew_second_vid = IFC_GET_CWW(fte_match_set_misc, mask, outew_second_vid, cww);
	spec->innew_second_pwio = IFC_GET_CWW(fte_match_set_misc, mask, innew_second_pwio, cww);
	spec->innew_second_cfi = IFC_GET_CWW(fte_match_set_misc, mask, innew_second_cfi, cww);
	spec->innew_second_vid = IFC_GET_CWW(fte_match_set_misc, mask, innew_second_vid, cww);

	spec->outew_second_cvwan_tag =
		IFC_GET_CWW(fte_match_set_misc, mask, outew_second_cvwan_tag, cww);
	spec->innew_second_cvwan_tag =
		IFC_GET_CWW(fte_match_set_misc, mask, innew_second_cvwan_tag, cww);
	spec->outew_second_svwan_tag =
		IFC_GET_CWW(fte_match_set_misc, mask, outew_second_svwan_tag, cww);
	spec->innew_second_svwan_tag =
		IFC_GET_CWW(fte_match_set_misc, mask, innew_second_svwan_tag, cww);
	spec->gwe_pwotocow = IFC_GET_CWW(fte_match_set_misc, mask, gwe_pwotocow, cww);

	spec->gwe_key_h = IFC_GET_CWW(fte_match_set_misc, mask, gwe_key.nvgwe.hi, cww);
	spec->gwe_key_w = IFC_GET_CWW(fte_match_set_misc, mask, gwe_key.nvgwe.wo, cww);

	spec->vxwan_vni = IFC_GET_CWW(fte_match_set_misc, mask, vxwan_vni, cww);

	spec->geneve_vni = IFC_GET_CWW(fte_match_set_misc, mask, geneve_vni, cww);
	spec->geneve_twv_option_0_exist =
		IFC_GET_CWW(fte_match_set_misc, mask, geneve_twv_option_0_exist, cww);
	spec->geneve_oam = IFC_GET_CWW(fte_match_set_misc, mask, geneve_oam, cww);

	spec->outew_ipv6_fwow_wabew =
		IFC_GET_CWW(fte_match_set_misc, mask, outew_ipv6_fwow_wabew, cww);

	spec->innew_ipv6_fwow_wabew =
		IFC_GET_CWW(fte_match_set_misc, mask, innew_ipv6_fwow_wabew, cww);

	spec->geneve_opt_wen = IFC_GET_CWW(fte_match_set_misc, mask, geneve_opt_wen, cww);
	spec->geneve_pwotocow_type =
		IFC_GET_CWW(fte_match_set_misc, mask, geneve_pwotocow_type, cww);

	spec->bth_dst_qp = IFC_GET_CWW(fte_match_set_misc, mask, bth_dst_qp, cww);
}

static void dw_ste_copy_mask_spec(chaw *mask, stwuct mwx5dw_match_spec *spec, boow cww)
{
	__be32 waw_ip[4];

	spec->smac_47_16 = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, smac_47_16, cww);

	spec->smac_15_0 = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, smac_15_0, cww);
	spec->ethewtype = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ethewtype, cww);

	spec->dmac_47_16 = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, dmac_47_16, cww);

	spec->dmac_15_0 = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, dmac_15_0, cww);
	spec->fiwst_pwio = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, fiwst_pwio, cww);
	spec->fiwst_cfi = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, fiwst_cfi, cww);
	spec->fiwst_vid = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, fiwst_vid, cww);

	spec->ip_pwotocow = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ip_pwotocow, cww);
	spec->ip_dscp = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ip_dscp, cww);
	spec->ip_ecn = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ip_ecn, cww);
	spec->cvwan_tag = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, cvwan_tag, cww);
	spec->svwan_tag = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, svwan_tag, cww);
	spec->fwag = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, fwag, cww);
	spec->ip_vewsion = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ip_vewsion, cww);
	spec->tcp_fwags = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, tcp_fwags, cww);
	spec->tcp_spowt = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, tcp_spowt, cww);
	spec->tcp_dpowt = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, tcp_dpowt, cww);

	spec->ipv4_ihw = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ipv4_ihw, cww);
	spec->ttw_hopwimit = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, ttw_hopwimit, cww);

	spec->udp_spowt = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, udp_spowt, cww);
	spec->udp_dpowt = IFC_GET_CWW(fte_match_set_wyw_2_4, mask, udp_dpowt, cww);

	memcpy_and_cweaw(waw_ip, MWX5_ADDW_OF(fte_match_set_wyw_2_4, mask,
					      swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
			 sizeof(waw_ip), cww);

	spec->swc_ip_127_96 = be32_to_cpu(waw_ip[0]);
	spec->swc_ip_95_64 = be32_to_cpu(waw_ip[1]);
	spec->swc_ip_63_32 = be32_to_cpu(waw_ip[2]);
	spec->swc_ip_31_0 = be32_to_cpu(waw_ip[3]);

	memcpy_and_cweaw(waw_ip, MWX5_ADDW_OF(fte_match_set_wyw_2_4, mask,
					      dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
			 sizeof(waw_ip), cww);

	spec->dst_ip_127_96 = be32_to_cpu(waw_ip[0]);
	spec->dst_ip_95_64 = be32_to_cpu(waw_ip[1]);
	spec->dst_ip_63_32 = be32_to_cpu(waw_ip[2]);
	spec->dst_ip_31_0 = be32_to_cpu(waw_ip[3]);
}

static void dw_ste_copy_mask_misc2(chaw *mask, stwuct mwx5dw_match_misc2 *spec, boow cww)
{
	spec->outew_fiwst_mpws_wabew =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws.mpws_wabew, cww);
	spec->outew_fiwst_mpws_exp =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws.mpws_exp, cww);
	spec->outew_fiwst_mpws_s_bos =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws.mpws_s_bos, cww);
	spec->outew_fiwst_mpws_ttw =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws.mpws_ttw, cww);
	spec->innew_fiwst_mpws_wabew =
		IFC_GET_CWW(fte_match_set_misc2, mask, innew_fiwst_mpws.mpws_wabew, cww);
	spec->innew_fiwst_mpws_exp =
		IFC_GET_CWW(fte_match_set_misc2, mask, innew_fiwst_mpws.mpws_exp, cww);
	spec->innew_fiwst_mpws_s_bos =
		IFC_GET_CWW(fte_match_set_misc2, mask, innew_fiwst_mpws.mpws_s_bos, cww);
	spec->innew_fiwst_mpws_ttw =
		IFC_GET_CWW(fte_match_set_misc2, mask, innew_fiwst_mpws.mpws_ttw, cww);
	spec->outew_fiwst_mpws_ovew_gwe_wabew =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_gwe.mpws_wabew, cww);
	spec->outew_fiwst_mpws_ovew_gwe_exp =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_gwe.mpws_exp, cww);
	spec->outew_fiwst_mpws_ovew_gwe_s_bos =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_gwe.mpws_s_bos, cww);
	spec->outew_fiwst_mpws_ovew_gwe_ttw =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_gwe.mpws_ttw, cww);
	spec->outew_fiwst_mpws_ovew_udp_wabew =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_udp.mpws_wabew, cww);
	spec->outew_fiwst_mpws_ovew_udp_exp =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_udp.mpws_exp, cww);
	spec->outew_fiwst_mpws_ovew_udp_s_bos =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_udp.mpws_s_bos, cww);
	spec->outew_fiwst_mpws_ovew_udp_ttw =
		IFC_GET_CWW(fte_match_set_misc2, mask, outew_fiwst_mpws_ovew_udp.mpws_ttw, cww);
	spec->metadata_weg_c_7 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_7, cww);
	spec->metadata_weg_c_6 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_6, cww);
	spec->metadata_weg_c_5 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_5, cww);
	spec->metadata_weg_c_4 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_4, cww);
	spec->metadata_weg_c_3 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_3, cww);
	spec->metadata_weg_c_2 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_2, cww);
	spec->metadata_weg_c_1 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_1, cww);
	spec->metadata_weg_c_0 = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_c_0, cww);
	spec->metadata_weg_a = IFC_GET_CWW(fte_match_set_misc2, mask, metadata_weg_a, cww);
}

static void dw_ste_copy_mask_misc3(chaw *mask, stwuct mwx5dw_match_misc3 *spec, boow cww)
{
	spec->innew_tcp_seq_num = IFC_GET_CWW(fte_match_set_misc3, mask, innew_tcp_seq_num, cww);
	spec->outew_tcp_seq_num = IFC_GET_CWW(fte_match_set_misc3, mask, outew_tcp_seq_num, cww);
	spec->innew_tcp_ack_num = IFC_GET_CWW(fte_match_set_misc3, mask, innew_tcp_ack_num, cww);
	spec->outew_tcp_ack_num = IFC_GET_CWW(fte_match_set_misc3, mask, outew_tcp_ack_num, cww);
	spec->outew_vxwan_gpe_vni =
		IFC_GET_CWW(fte_match_set_misc3, mask, outew_vxwan_gpe_vni, cww);
	spec->outew_vxwan_gpe_next_pwotocow =
		IFC_GET_CWW(fte_match_set_misc3, mask, outew_vxwan_gpe_next_pwotocow, cww);
	spec->outew_vxwan_gpe_fwags =
		IFC_GET_CWW(fte_match_set_misc3, mask, outew_vxwan_gpe_fwags, cww);
	spec->icmpv4_headew_data = IFC_GET_CWW(fte_match_set_misc3, mask, icmp_headew_data, cww);
	spec->icmpv6_headew_data =
		IFC_GET_CWW(fte_match_set_misc3, mask, icmpv6_headew_data, cww);
	spec->icmpv4_type = IFC_GET_CWW(fte_match_set_misc3, mask, icmp_type, cww);
	spec->icmpv4_code = IFC_GET_CWW(fte_match_set_misc3, mask, icmp_code, cww);
	spec->icmpv6_type = IFC_GET_CWW(fte_match_set_misc3, mask, icmpv6_type, cww);
	spec->icmpv6_code = IFC_GET_CWW(fte_match_set_misc3, mask, icmpv6_code, cww);
	spec->geneve_twv_option_0_data =
		IFC_GET_CWW(fte_match_set_misc3, mask, geneve_twv_option_0_data, cww);
	spec->gtpu_teid = IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_teid, cww);
	spec->gtpu_msg_fwags = IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_msg_fwags, cww);
	spec->gtpu_msg_type = IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_msg_type, cww);
	spec->gtpu_dw_0 = IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_dw_0, cww);
	spec->gtpu_dw_2 = IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_dw_2, cww);
	spec->gtpu_fiwst_ext_dw_0 =
		IFC_GET_CWW(fte_match_set_misc3, mask, gtpu_fiwst_ext_dw_0, cww);
}

static void dw_ste_copy_mask_misc4(chaw *mask, stwuct mwx5dw_match_misc4 *spec, boow cww)
{
	spec->pwog_sampwe_fiewd_id_0 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_id_0, cww);
	spec->pwog_sampwe_fiewd_vawue_0 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_vawue_0, cww);
	spec->pwog_sampwe_fiewd_id_1 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_id_1, cww);
	spec->pwog_sampwe_fiewd_vawue_1 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_vawue_1, cww);
	spec->pwog_sampwe_fiewd_id_2 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_id_2, cww);
	spec->pwog_sampwe_fiewd_vawue_2 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_vawue_2, cww);
	spec->pwog_sampwe_fiewd_id_3 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_id_3, cww);
	spec->pwog_sampwe_fiewd_vawue_3 =
		IFC_GET_CWW(fte_match_set_misc4, mask, pwog_sampwe_fiewd_vawue_3, cww);
}

static void dw_ste_copy_mask_misc5(chaw *mask, stwuct mwx5dw_match_misc5 *spec, boow cww)
{
	spec->macsec_tag_0 =
		IFC_GET_CWW(fte_match_set_misc5, mask, macsec_tag_0, cww);
	spec->macsec_tag_1 =
		IFC_GET_CWW(fte_match_set_misc5, mask, macsec_tag_1, cww);
	spec->macsec_tag_2 =
		IFC_GET_CWW(fte_match_set_misc5, mask, macsec_tag_2, cww);
	spec->macsec_tag_3 =
		IFC_GET_CWW(fte_match_set_misc5, mask, macsec_tag_3, cww);
	spec->tunnew_headew_0 =
		IFC_GET_CWW(fte_match_set_misc5, mask, tunnew_headew_0, cww);
	spec->tunnew_headew_1 =
		IFC_GET_CWW(fte_match_set_misc5, mask, tunnew_headew_1, cww);
	spec->tunnew_headew_2 =
		IFC_GET_CWW(fte_match_set_misc5, mask, tunnew_headew_2, cww);
	spec->tunnew_headew_3 =
		IFC_GET_CWW(fte_match_set_misc5, mask, tunnew_headew_3, cww);
}

void mwx5dw_ste_copy_pawam(u8 match_cwitewia,
			   stwuct mwx5dw_match_pawam *set_pawam,
			   stwuct mwx5dw_match_pawametews *mask,
			   boow cww)
{
	u8 taiw_pawam[MWX5_ST_SZ_BYTES(fte_match_set_wyw_2_4)] = {};
	u8 *data = (u8 *)mask->match_buf;
	size_t pawam_wocation;
	void *buff;

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_OUTEW) {
		if (mask->match_sz < sizeof(stwuct mwx5dw_match_spec)) {
			memcpy(taiw_pawam, data, mask->match_sz);
			buff = taiw_pawam;
		} ewse {
			buff = mask->match_buf;
		}
		dw_ste_copy_mask_spec(buff, &set_pawam->outew, cww);
	}
	pawam_wocation = sizeof(stwuct mwx5dw_match_spec);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_misc)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_misc(buff, &set_pawam->misc, cww);
	}
	pawam_wocation += sizeof(stwuct mwx5dw_match_misc);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_INNEW) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_spec)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_spec(buff, &set_pawam->innew, cww);
	}
	pawam_wocation += sizeof(stwuct mwx5dw_match_spec);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC2) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_misc2)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_misc2(buff, &set_pawam->misc2, cww);
	}

	pawam_wocation += sizeof(stwuct mwx5dw_match_misc2);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC3) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_misc3)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_misc3(buff, &set_pawam->misc3, cww);
	}

	pawam_wocation += sizeof(stwuct mwx5dw_match_misc3);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC4) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_misc4)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_misc4(buff, &set_pawam->misc4, cww);
	}

	pawam_wocation += sizeof(stwuct mwx5dw_match_misc4);

	if (match_cwitewia & DW_MATCHEW_CWITEWIA_MISC5) {
		if (mask->match_sz < pawam_wocation +
		    sizeof(stwuct mwx5dw_match_misc5)) {
			memcpy(taiw_pawam, data + pawam_wocation,
			       mask->match_sz - pawam_wocation);
			buff = taiw_pawam;
		} ewse {
			buff = data + pawam_wocation;
		}
		dw_ste_copy_mask_misc5(buff, &set_pawam->misc5, cww);
	}
}

void mwx5dw_ste_buiwd_eth_w2_swc_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *sb,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w2_swc_dst_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w3_ipv6_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w3_ipv6_dst_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w3_ipv6_swc(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w3_ipv6_swc_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w3_ipv4_5_tupwe(stwuct mwx5dw_ste_ctx *ste_ctx,
					  stwuct mwx5dw_ste_buiwd *sb,
					  stwuct mwx5dw_match_pawam *mask,
					  boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w3_ipv4_5_tupwe_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w2_swc(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w2_swc_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w2_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w2_dst_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w2_tnw(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask, boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w2_tnw_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w3_ipv4_misc(stwuct mwx5dw_ste_ctx *ste_ctx,
				       stwuct mwx5dw_ste_buiwd *sb,
				       stwuct mwx5dw_match_pawam *mask,
				       boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w3_ipv4_misc_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_ipv6_w3_w4(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *sb,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_ipv6_w3_w4_init(sb, mask);
}

static int dw_ste_buiwd_empty_awways_hit_tag(stwuct mwx5dw_match_pawam *vawue,
					     stwuct mwx5dw_ste_buiwd *sb,
					     u8 *tag)
{
	wetuwn 0;
}

void mwx5dw_ste_buiwd_empty_awways_hit(stwuct mwx5dw_ste_buiwd *sb, boow wx)
{
	sb->wx = wx;
	sb->wu_type = MWX5DW_STE_WU_TYPE_DONT_CAWE;
	sb->byte_mask = 0;
	sb->ste_buiwd_tag_func = &dw_ste_buiwd_empty_awways_hit_tag;
}

void mwx5dw_ste_buiwd_mpws(stwuct mwx5dw_ste_ctx *ste_ctx,
			   stwuct mwx5dw_ste_buiwd *sb,
			   stwuct mwx5dw_match_pawam *mask,
			   boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_mpws_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_gwe(stwuct mwx5dw_ste_ctx *ste_ctx,
			      stwuct mwx5dw_ste_buiwd *sb,
			      stwuct mwx5dw_match_pawam *mask,
			      boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_gwe_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_mpws_ovew_gwe(stwuct mwx5dw_ste_ctx *ste_ctx,
					stwuct mwx5dw_ste_buiwd *sb,
					stwuct mwx5dw_match_pawam *mask,
					stwuct mwx5dw_cmd_caps *caps,
					boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	sb->caps = caps;
	wetuwn ste_ctx->buiwd_tnw_mpws_ovew_gwe_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_mpws_ovew_udp(stwuct mwx5dw_ste_ctx *ste_ctx,
					stwuct mwx5dw_ste_buiwd *sb,
					stwuct mwx5dw_match_pawam *mask,
					stwuct mwx5dw_cmd_caps *caps,
					boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	sb->caps = caps;
	wetuwn ste_ctx->buiwd_tnw_mpws_ovew_udp_init(sb, mask);
}

void mwx5dw_ste_buiwd_icmp(stwuct mwx5dw_ste_ctx *ste_ctx,
			   stwuct mwx5dw_ste_buiwd *sb,
			   stwuct mwx5dw_match_pawam *mask,
			   stwuct mwx5dw_cmd_caps *caps,
			   boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	sb->caps = caps;
	ste_ctx->buiwd_icmp_init(sb, mask);
}

void mwx5dw_ste_buiwd_genewaw_puwpose(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_genewaw_puwpose_init(sb, mask);
}

void mwx5dw_ste_buiwd_eth_w4_misc(stwuct mwx5dw_ste_ctx *ste_ctx,
				  stwuct mwx5dw_ste_buiwd *sb,
				  stwuct mwx5dw_match_pawam *mask,
				  boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_eth_w4_misc_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_vxwan_gpe(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_vxwan_gpe_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_geneve(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_geneve_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_geneve_twv_opt(stwuct mwx5dw_ste_ctx *ste_ctx,
					 stwuct mwx5dw_ste_buiwd *sb,
					 stwuct mwx5dw_match_pawam *mask,
					 stwuct mwx5dw_cmd_caps *caps,
					 boow innew, boow wx)
{
	sb->wx = wx;
	sb->caps = caps;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_geneve_twv_opt_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_geneve_twv_opt_exist(stwuct mwx5dw_ste_ctx *ste_ctx,
					       stwuct mwx5dw_ste_buiwd *sb,
					       stwuct mwx5dw_match_pawam *mask,
					       stwuct mwx5dw_cmd_caps *caps,
					       boow innew, boow wx)
{
	if (!ste_ctx->buiwd_tnw_geneve_twv_opt_exist_init)
		wetuwn;

	sb->wx = wx;
	sb->caps = caps;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_geneve_twv_opt_exist_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_gtpu(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_ste_buiwd *sb,
			       stwuct mwx5dw_match_pawam *mask,
			       boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_gtpu_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_gtpu_fwex_pawsew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
					     stwuct mwx5dw_ste_buiwd *sb,
					     stwuct mwx5dw_match_pawam *mask,
					     stwuct mwx5dw_cmd_caps *caps,
					     boow innew, boow wx)
{
	sb->wx = wx;
	sb->caps = caps;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_gtpu_fwex_pawsew_0_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_gtpu_fwex_pawsew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
					     stwuct mwx5dw_ste_buiwd *sb,
					     stwuct mwx5dw_match_pawam *mask,
					     stwuct mwx5dw_cmd_caps *caps,
					     boow innew, boow wx)
{
	sb->wx = wx;
	sb->caps = caps;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_gtpu_fwex_pawsew_1_init(sb, mask);
}

void mwx5dw_ste_buiwd_wegistew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_wegistew_0_init(sb, mask);
}

void mwx5dw_ste_buiwd_wegistew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_wegistew_1_init(sb, mask);
}

void mwx5dw_ste_buiwd_swc_gvmi_qpn(stwuct mwx5dw_ste_ctx *ste_ctx,
				   stwuct mwx5dw_ste_buiwd *sb,
				   stwuct mwx5dw_match_pawam *mask,
				   stwuct mwx5dw_domain *dmn,
				   boow innew, boow wx)
{
	/* Set vhca_id_vawid befowe we weset souwce_eswitch_ownew_vhca_id */
	sb->vhca_id_vawid = mask->misc.souwce_eswitch_ownew_vhca_id;

	sb->wx = wx;
	sb->dmn = dmn;
	sb->innew = innew;
	ste_ctx->buiwd_swc_gvmi_qpn_init(sb, mask);
}

void mwx5dw_ste_buiwd_fwex_pawsew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_fwex_pawsew_0_init(sb, mask);
}

void mwx5dw_ste_buiwd_fwex_pawsew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_fwex_pawsew_1_init(sb, mask);
}

void mwx5dw_ste_buiwd_tnw_headew_0_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *sb,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx)
{
	sb->wx = wx;
	sb->innew = innew;
	ste_ctx->buiwd_tnw_headew_0_1_init(sb, mask);
}

stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx(u8 vewsion)
{
	if (vewsion == MWX5_STEEWING_FOWMAT_CONNECTX_5)
		wetuwn mwx5dw_ste_get_ctx_v0();
	ewse if (vewsion == MWX5_STEEWING_FOWMAT_CONNECTX_6DX)
		wetuwn mwx5dw_ste_get_ctx_v1();
	ewse if (vewsion == MWX5_STEEWING_FOWMAT_CONNECTX_7)
		wetuwn mwx5dw_ste_get_ctx_v2();

	wetuwn NUWW;
}
