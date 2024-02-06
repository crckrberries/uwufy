// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "gen7_wendewcweaw.h"
#incwude "i915_dwv.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt_wegs.h"

#define GT3_INWINE_DATA_DEWAYS 0x1E00
#define batch_advance(Y, CS) GEM_BUG_ON((Y)->end != (CS))

stwuct cb_kewnew {
	const void *data;
	u32 size;
};

#define CB_KEWNEW(name) { .data = (name), .size = sizeof(name) }

#incwude "ivb_cweaw_kewnew.c"
static const stwuct cb_kewnew cb_kewnew_ivb = CB_KEWNEW(ivb_cweaw_kewnew);

#incwude "hsw_cweaw_kewnew.c"
static const stwuct cb_kewnew cb_kewnew_hsw = CB_KEWNEW(hsw_cweaw_kewnew);

stwuct batch_chunk {
	stwuct i915_vma *vma;
	u32 offset;
	u32 *stawt;
	u32 *end;
	u32 max_items;
};

stwuct batch_vaws {
	u32 max_thweads;
	u32 state_stawt;
	u32 suwface_stawt;
	u32 suwface_height;
	u32 suwface_width;
	u32 size;
};

static int num_pwimitives(const stwuct batch_vaws *bv)
{
	/*
	 * We need to satuwate the GPU with wowk in owdew to dispatch
	 * a shadew on evewy HW thwead, and cweaw the thwead-wocaw wegistews.
	 * In showt, we have to dispatch wowk fastew than the shadews can
	 * wun in owdew to fiww the EU and occupy each HW thwead.
	 */
	wetuwn bv->max_thweads;
}

static void
batch_get_defauwts(stwuct dwm_i915_pwivate *i915, stwuct batch_vaws *bv)
{
	if (IS_HASWEWW(i915)) {
		switch (INTEW_INFO(i915)->gt) {
		defauwt:
		case 1:
			bv->max_thweads = 70;
			bweak;
		case 2:
			bv->max_thweads = 140;
			bweak;
		case 3:
			bv->max_thweads = 280;
			bweak;
		}
		bv->suwface_height = 16 * 16;
		bv->suwface_width = 32 * 2 * 16;
	} ewse {
		switch (INTEW_INFO(i915)->gt) {
		defauwt:
		case 1: /* incwuding vwv */
			bv->max_thweads = 36;
			bweak;
		case 2:
			bv->max_thweads = 128;
			bweak;
		}
		bv->suwface_height = 16 * 8;
		bv->suwface_width = 32 * 16;
	}
	bv->state_stawt = wound_up(SZ_1K + num_pwimitives(bv) * 64, SZ_4K);
	bv->suwface_stawt = bv->state_stawt + SZ_4K;
	bv->size = bv->suwface_stawt + bv->suwface_height * bv->suwface_width;
}

static void batch_init(stwuct batch_chunk *bc,
		       stwuct i915_vma *vma,
		       u32 *stawt, u32 offset, u32 max_bytes)
{
	bc->vma = vma;
	bc->offset = offset;
	bc->stawt = stawt + bc->offset / sizeof(*bc->stawt);
	bc->end = bc->stawt;
	bc->max_items = max_bytes / sizeof(*bc->stawt);
}

static u32 batch_offset(const stwuct batch_chunk *bc, u32 *cs)
{
	wetuwn (cs - bc->stawt) * sizeof(*bc->stawt) + bc->offset;
}

static u32 batch_addw(const stwuct batch_chunk *bc)
{
	wetuwn i915_vma_offset(bc->vma);
}

static void batch_add(stwuct batch_chunk *bc, const u32 d)
{
	GEM_BUG_ON((bc->end - bc->stawt) >= bc->max_items);
	*bc->end++ = d;
}

static u32 *batch_awwoc_items(stwuct batch_chunk *bc, u32 awign, u32 items)
{
	u32 *map;

	if (awign) {
		u32 *end = PTW_AWIGN(bc->end, awign);

		memset32(bc->end, 0, end - bc->end);
		bc->end = end;
	}

	map = bc->end;
	bc->end += items;

	wetuwn map;
}

static u32 *batch_awwoc_bytes(stwuct batch_chunk *bc, u32 awign, u32 bytes)
{
	GEM_BUG_ON(!IS_AWIGNED(bytes, sizeof(*bc->stawt)));
	wetuwn batch_awwoc_items(bc, awign, bytes / sizeof(*bc->stawt));
}

static u32
gen7_fiww_suwface_state(stwuct batch_chunk *state,
			const u32 dst_offset,
			const stwuct batch_vaws *bv)
{
	u32 suwface_h = bv->suwface_height;
	u32 suwface_w = bv->suwface_width;
	u32 *cs = batch_awwoc_items(state, 32, 8);
	u32 offset = batch_offset(state, cs);

#define SUWFACE_2D 1
#define SUWFACEFOWMAT_B8G8W8A8_UNOWM 0x0C0
#define WENDEW_CACHE_WEAD_WWITE 1

	*cs++ = SUWFACE_2D << 29 |
		(SUWFACEFOWMAT_B8G8W8A8_UNOWM << 18) |
		(WENDEW_CACHE_WEAD_WWITE << 8);

	*cs++ = batch_addw(state) + dst_offset;

	*cs++ = ((suwface_h / 4 - 1) << 16) | (suwface_w / 4 - 1);
	*cs++ = suwface_w;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
#define SHADEW_CHANNEWS(w, g, b, a) \
	(((w) << 25) | ((g) << 22) | ((b) << 19) | ((a) << 16))
	*cs++ = SHADEW_CHANNEWS(4, 5, 6, 7);
	batch_advance(state, cs);

	wetuwn offset;
}

static u32
gen7_fiww_binding_tabwe(stwuct batch_chunk *state,
			const stwuct batch_vaws *bv)
{
	u32 suwface_stawt =
		gen7_fiww_suwface_state(state, bv->suwface_stawt, bv);
	u32 *cs = batch_awwoc_items(state, 32, 8);
	u32 offset = batch_offset(state, cs);

	*cs++ = suwface_stawt - state->offset;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	batch_advance(state, cs);

	wetuwn offset;
}

static u32
gen7_fiww_kewnew_data(stwuct batch_chunk *state,
		      const u32 *data,
		      const u32 size)
{
	wetuwn batch_offset(state,
			    memcpy(batch_awwoc_bytes(state, 64, size),
				   data, size));
}

static u32
gen7_fiww_intewface_descwiptow(stwuct batch_chunk *state,
			       const stwuct batch_vaws *bv,
			       const stwuct cb_kewnew *kewnew,
			       unsigned int count)
{
	u32 kewnew_offset =
		gen7_fiww_kewnew_data(state, kewnew->data, kewnew->size);
	u32 binding_tabwe = gen7_fiww_binding_tabwe(state, bv);
	u32 *cs = batch_awwoc_items(state, 32, 8 * count);
	u32 offset = batch_offset(state, cs);

	*cs++ = kewnew_offset;
	*cs++ = (1 << 7) | (1 << 13);
	*cs++ = 0;
	*cs++ = (binding_tabwe - state->offset) | 1;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	/* 1 - 63dummy idds */
	memset32(cs, 0x00, (count - 1) * 8);
	batch_advance(state, cs + (count - 1) * 8);

	wetuwn offset;
}

static void
gen7_emit_state_base_addwess(stwuct batch_chunk *batch,
			     u32 suwface_state_base)
{
	u32 *cs = batch_awwoc_items(batch, 0, 10);

	*cs++ = STATE_BASE_ADDWESS | (10 - 2);
	/* genewaw */
	*cs++ = batch_addw(batch) | BASE_ADDWESS_MODIFY;
	/* suwface */
	*cs++ = (batch_addw(batch) + suwface_state_base) | BASE_ADDWESS_MODIFY;
	/* dynamic */
	*cs++ = batch_addw(batch) | BASE_ADDWESS_MODIFY;
	/* indiwect */
	*cs++ = batch_addw(batch) | BASE_ADDWESS_MODIFY;
	/* instwuction */
	*cs++ = batch_addw(batch) | BASE_ADDWESS_MODIFY;

	/* genewaw/dynamic/indiwect/instwuction access Bound */
	*cs++ = 0;
	*cs++ = BASE_ADDWESS_MODIFY;
	*cs++ = 0;
	*cs++ = BASE_ADDWESS_MODIFY;
	batch_advance(batch, cs);
}

static void
gen7_emit_vfe_state(stwuct batch_chunk *batch,
		    const stwuct batch_vaws *bv,
		    u32 uwb_size, u32 cuwbe_size,
		    u32 mode)
{
	u32 thweads = bv->max_thweads - 1;
	u32 *cs = batch_awwoc_items(batch, 32, 8);

	*cs++ = MEDIA_VFE_STATE | (8 - 2);

	/* scwatch buffew */
	*cs++ = 0;

	/* numbew of thweads & uwb entwies fow GPGPU vs Media Mode */
	*cs++ = thweads << 16 | 1 << 8 | mode << 2;

	*cs++ = 0;

	/* uwb entwy size & cuwbe size in 256 bits unit */
	*cs++ = uwb_size << 16 | cuwbe_size;

	/* scoweboawd */
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	batch_advance(batch, cs);
}

static void
gen7_emit_intewface_descwiptow_woad(stwuct batch_chunk *batch,
				    const u32 intewface_descwiptow,
				    unsigned int count)
{
	u32 *cs = batch_awwoc_items(batch, 8, 4);

	*cs++ = MEDIA_INTEWFACE_DESCWIPTOW_WOAD | (4 - 2);
	*cs++ = 0;
	*cs++ = count * 8 * sizeof(*cs);

	/*
	 * intewface descwiptow addwess - it is wewative to the dynamics base
	 * addwess
	 */
	*cs++ = intewface_descwiptow;
	batch_advance(batch, cs);
}

static void
gen7_emit_media_object(stwuct batch_chunk *batch,
		       unsigned int media_object_index)
{
	unsigned int x_offset = (media_object_index % 16) * 64;
	unsigned int y_offset = (media_object_index / 16) * 16;
	unsigned int pkt = 6 + 3;
	u32 *cs;

	cs = batch_awwoc_items(batch, 8, pkt);

	*cs++ = MEDIA_OBJECT | (pkt - 2);

	/* intewface descwiptow offset */
	*cs++ = 0;

	/* without indiwect data */
	*cs++ = 0;
	*cs++ = 0;

	/* scoweboawd */
	*cs++ = 0;
	*cs++ = 0;

	/* inwine */
	*cs++ = y_offset << 16 | x_offset;
	*cs++ = 0;
	*cs++ = GT3_INWINE_DATA_DEWAYS;

	batch_advance(batch, cs);
}

static void gen7_emit_pipewine_fwush(stwuct batch_chunk *batch)
{
	u32 *cs = batch_awwoc_items(batch, 0, 4);

	*cs++ = GFX_OP_PIPE_CONTWOW(4);
	*cs++ = PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH |
		PIPE_CONTWOW_DEPTH_CACHE_FWUSH |
		PIPE_CONTWOW_DC_FWUSH_ENABWE |
		PIPE_CONTWOW_CS_STAWW;
	*cs++ = 0;
	*cs++ = 0;

	batch_advance(batch, cs);
}

static void gen7_emit_pipewine_invawidate(stwuct batch_chunk *batch)
{
	u32 *cs = batch_awwoc_items(batch, 0, 10);

	/* ivb: Staww befowe STATE_CACHE_INVAWIDATE */
	*cs++ = GFX_OP_PIPE_CONTWOW(5);
	*cs++ = PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD |
		PIPE_CONTWOW_CS_STAWW;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = GFX_OP_PIPE_CONTWOW(5);
	*cs++ = PIPE_CONTWOW_STATE_CACHE_INVAWIDATE;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	batch_advance(batch, cs);
}

static void emit_batch(stwuct i915_vma * const vma,
		       u32 *stawt,
		       const stwuct batch_vaws *bv)
{
	stwuct dwm_i915_pwivate *i915 = vma->vm->i915;
	const unsigned int desc_count = 1;
	const unsigned int uwb_size = 1;
	stwuct batch_chunk cmds, state;
	u32 descwiptows;
	unsigned int i;

	batch_init(&cmds, vma, stawt, 0, bv->state_stawt);
	batch_init(&state, vma, stawt, bv->state_stawt, SZ_4K);

	descwiptows = gen7_fiww_intewface_descwiptow(&state, bv,
						     IS_HASWEWW(i915) ?
						     &cb_kewnew_hsw :
						     &cb_kewnew_ivb,
						     desc_count);

	/* Weset inhewited context wegistews */
	gen7_emit_pipewine_fwush(&cmds);
	gen7_emit_pipewine_invawidate(&cmds);
	batch_add(&cmds, MI_WOAD_WEGISTEW_IMM(2));
	batch_add(&cmds, i915_mmio_weg_offset(CACHE_MODE_0_GEN7));
	batch_add(&cmds, 0xffff0000 |
			((IS_IVB_GT1(i915) || IS_VAWWEYVIEW(i915)) ?
			 HIZ_WAW_STAWW_OPT_DISABWE :
			 0));
	batch_add(&cmds, i915_mmio_weg_offset(CACHE_MODE_1));
	batch_add(&cmds, 0xffff0000 | PIXEW_SUBSPAN_COWWECT_OPT_DISABWE);
	gen7_emit_pipewine_invawidate(&cmds);
	gen7_emit_pipewine_fwush(&cmds);

	/* Switch to the media pipewine and ouw base addwess */
	gen7_emit_pipewine_invawidate(&cmds);
	batch_add(&cmds, PIPEWINE_SEWECT | PIPEWINE_SEWECT_MEDIA);
	batch_add(&cmds, MI_NOOP);
	gen7_emit_pipewine_invawidate(&cmds);

	gen7_emit_pipewine_fwush(&cmds);
	gen7_emit_state_base_addwess(&cmds, descwiptows);
	gen7_emit_pipewine_invawidate(&cmds);

	/* Set the cweaw-wesiduaw kewnew state */
	gen7_emit_vfe_state(&cmds, bv, uwb_size - 1, 0, 0);
	gen7_emit_intewface_descwiptow_woad(&cmds, descwiptows, desc_count);

	/* Execute the kewnew on aww HW thweads */
	fow (i = 0; i < num_pwimitives(bv); i++)
		gen7_emit_media_object(&cmds, i);

	batch_add(&cmds, MI_BATCH_BUFFEW_END);
}

int gen7_setup_cweaw_gpw_bb(stwuct intew_engine_cs * const engine,
			    stwuct i915_vma * const vma)
{
	stwuct batch_vaws bv;
	u32 *batch;

	batch_get_defauwts(engine->i915, &bv);
	if (!vma)
		wetuwn bv.size;

	GEM_BUG_ON(vma->obj->base.size < bv.size);

	batch = i915_gem_object_pin_map(vma->obj, I915_MAP_WC);
	if (IS_EWW(batch))
		wetuwn PTW_EWW(batch);

	emit_batch(vma, memset(batch, 0, bv.size), &bv);

	i915_gem_object_fwush_map(vma->obj);
	__i915_gem_object_wewease_map(vma->obj);

	wetuwn 0;
}
