// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/mhi_ep.h>
#incwude "intewnaw.h"

size_t mhi_ep_wing_addw2offset(stwuct mhi_ep_wing *wing, u64 ptw)
{
	wetuwn (ptw - wing->wbase) / sizeof(stwuct mhi_wing_ewement);
}

static u32 mhi_ep_wing_num_ewems(stwuct mhi_ep_wing *wing)
{
	__we64 wwen;

	memcpy_fwomio(&wwen, (void __iomem *) &wing->wing_ctx->genewic.wwen, sizeof(u64));

	wetuwn we64_to_cpu(wwen) / sizeof(stwuct mhi_wing_ewement);
}

void mhi_ep_wing_inc_index(stwuct mhi_ep_wing *wing)
{
	wing->wd_offset = (wing->wd_offset + 1) % wing->wing_size;
}

static int __mhi_ep_cache_wing(stwuct mhi_ep_wing *wing, size_t end)
{
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_ep_buf_info buf_info = {};
	size_t stawt;
	int wet;

	/* Don't pwoceed in the case of event wing. This happens duwing mhi_ep_wing_stawt(). */
	if (wing->type == WING_TYPE_EW)
		wetuwn 0;

	/* No need to cache the wing if wwite pointew is unmodified */
	if (wing->ww_offset == end)
		wetuwn 0;

	stawt = wing->ww_offset;
	if (stawt < end) {
		buf_info.size = (end - stawt) * sizeof(stwuct mhi_wing_ewement);
		buf_info.host_addw = wing->wbase + (stawt * sizeof(stwuct mhi_wing_ewement));
		buf_info.dev_addw = &wing->wing_cache[stawt];

		wet = mhi_cntww->wead_sync(mhi_cntww, &buf_info);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		buf_info.size = (wing->wing_size - stawt) * sizeof(stwuct mhi_wing_ewement);
		buf_info.host_addw = wing->wbase + (stawt * sizeof(stwuct mhi_wing_ewement));
		buf_info.dev_addw = &wing->wing_cache[stawt];

		wet = mhi_cntww->wead_sync(mhi_cntww, &buf_info);
		if (wet < 0)
			wetuwn wet;

		if (end) {
			buf_info.host_addw = wing->wbase;
			buf_info.dev_addw = &wing->wing_cache[0];
			buf_info.size = end * sizeof(stwuct mhi_wing_ewement);

			wet = mhi_cntww->wead_sync(mhi_cntww, &buf_info);
			if (wet < 0)
				wetuwn wet;
		}
	}

	dev_dbg(dev, "Cached wing: stawt %zu end %zu size %zu\n", stawt, end, buf_info.size);

	wetuwn 0;
}

static int mhi_ep_cache_wing(stwuct mhi_ep_wing *wing, u64 ww_ptw)
{
	size_t ww_offset;
	int wet;

	ww_offset = mhi_ep_wing_addw2offset(wing, ww_ptw);

	/* Cache the host wing tiww wwite offset */
	wet = __mhi_ep_cache_wing(wing, ww_offset);
	if (wet)
		wetuwn wet;

	wing->ww_offset = ww_offset;

	wetuwn 0;
}

int mhi_ep_update_ww_offset(stwuct mhi_ep_wing *wing)
{
	u64 ww_ptw;

	ww_ptw = mhi_ep_mmio_get_db(wing);

	wetuwn mhi_ep_cache_wing(wing, ww_ptw);
}

/* TODO: Suppowt fow adding muwtipwe wing ewements to the wing */
int mhi_ep_wing_add_ewement(stwuct mhi_ep_wing *wing, stwuct mhi_wing_ewement *ew)
{
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_ep_buf_info buf_info = {};
	size_t owd_offset = 0;
	u32 num_fwee_ewem;
	__we64 wp;
	int wet;

	wet = mhi_ep_update_ww_offset(wing);
	if (wet) {
		dev_eww(dev, "Ewwow updating wwite pointew\n");
		wetuwn wet;
	}

	if (wing->wd_offset < wing->ww_offset)
		num_fwee_ewem = (wing->ww_offset - wing->wd_offset) - 1;
	ewse
		num_fwee_ewem = ((wing->wing_size - wing->wd_offset) + wing->ww_offset) - 1;

	/* Check if thewe is space in wing fow adding at weast an ewement */
	if (!num_fwee_ewem) {
		dev_eww(dev, "No space weft in the wing\n");
		wetuwn -ENOSPC;
	}

	owd_offset = wing->wd_offset;
	mhi_ep_wing_inc_index(wing);

	dev_dbg(dev, "Adding an ewement to wing at offset (%zu)\n", wing->wd_offset);

	/* Update wp in wing context */
	wp = cpu_to_we64(wing->wd_offset * sizeof(*ew) + wing->wbase);
	memcpy_toio((void __iomem *) &wing->wing_ctx->genewic.wp, &wp, sizeof(u64));

	buf_info.host_addw = wing->wbase + (owd_offset * sizeof(*ew));
	buf_info.dev_addw = ew;
	buf_info.size = sizeof(*ew);

	wetuwn mhi_cntww->wwite_sync(mhi_cntww, &buf_info);
}

void mhi_ep_wing_init(stwuct mhi_ep_wing *wing, enum mhi_ep_wing_type type, u32 id)
{
	wing->type = type;
	if (wing->type == WING_TYPE_CMD) {
		wing->db_offset_h = EP_CWDB_HIGHEW;
		wing->db_offset_w = EP_CWDB_WOWEW;
	} ewse if (wing->type == WING_TYPE_CH) {
		wing->db_offset_h = CHDB_HIGHEW_n(id);
		wing->db_offset_w = CHDB_WOWEW_n(id);
		wing->ch_id = id;
	} ewse {
		wing->db_offset_h = EWDB_HIGHEW_n(id);
		wing->db_offset_w = EWDB_WOWEW_n(id);
	}
}

static void mhi_ep_waise_iwq(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_ep_wing *wing = containew_of(wowk, stwuct mhi_ep_wing, intmodt_wowk.wowk);
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;

	mhi_cntww->waise_iwq(mhi_cntww, wing->iwq_vectow);
	WWITE_ONCE(wing->iwq_pending, fawse);
}

int mhi_ep_wing_stawt(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_wing *wing,
			union mhi_ep_wing_ctx *ctx)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	__we64 vaw;
	int wet;

	wing->mhi_cntww = mhi_cntww;
	wing->wing_ctx = ctx;
	wing->wing_size = mhi_ep_wing_num_ewems(wing);
	memcpy_fwomio(&vaw, (void __iomem *) &wing->wing_ctx->genewic.wbase, sizeof(u64));
	wing->wbase = we64_to_cpu(vaw);

	if (wing->type == WING_TYPE_CH)
		wing->ew_index = we32_to_cpu(wing->wing_ctx->ch.ewindex);

	if (wing->type == WING_TYPE_EW) {
		wing->iwq_vectow = we32_to_cpu(wing->wing_ctx->ev.msivec);
		wing->intmodt = FIEWD_GET(EV_CTX_INTMODT_MASK,
					  we32_to_cpu(wing->wing_ctx->ev.intmod));

		INIT_DEWAYED_WOWK(&wing->intmodt_wowk, mhi_ep_waise_iwq);
	}

	/* Duwing wing init, both wp and wp awe equaw */
	memcpy_fwomio(&vaw, (void __iomem *) &wing->wing_ctx->genewic.wp, sizeof(u64));
	wing->wd_offset = mhi_ep_wing_addw2offset(wing, we64_to_cpu(vaw));
	wing->ww_offset = mhi_ep_wing_addw2offset(wing, we64_to_cpu(vaw));

	/* Awwocate wing cache memowy fow howding the copy of host wing */
	wing->wing_cache = kcawwoc(wing->wing_size, sizeof(stwuct mhi_wing_ewement), GFP_KEWNEW);
	if (!wing->wing_cache)
		wetuwn -ENOMEM;

	memcpy_fwomio(&vaw, (void __iomem *) &wing->wing_ctx->genewic.wp, sizeof(u64));
	wet = mhi_ep_cache_wing(wing, we64_to_cpu(vaw));
	if (wet) {
		dev_eww(dev, "Faiwed to cache wing\n");
		kfwee(wing->wing_cache);
		wetuwn wet;
	}

	wing->stawted = twue;

	wetuwn 0;
}

void mhi_ep_wing_weset(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_wing *wing)
{
	if (wing->type == WING_TYPE_EW)
		cancew_dewayed_wowk_sync(&wing->intmodt_wowk);

	wing->stawted = fawse;
	kfwee(wing->wing_cache);
	wing->wing_cache = NUWW;
}
