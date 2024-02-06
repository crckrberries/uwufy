// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_wwc.h"

#incwude "instwuctions/xe_mi_commands.h"
#incwude "instwuctions/xe_gfxpipe_commands.h"
#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gpu_commands.h"
#incwude "wegs/xe_wwc_wayout.h"
#incwude "xe_bb.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_dwm_cwient.h"
#incwude "xe_exec_queue_types.h"
#incwude "xe_gt.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_hw_fence.h"
#incwude "xe_map.h"
#incwude "xe_vm.h"

#define WWC_VAWID				(1 << 0)
#define WWC_PWIVIWEGE				(1 << 8)
#define WWC_ADDWESSING_MODE_SHIFT		3
#define WWC_WEGACY_64B_CONTEXT			3

#define ENGINE_CWASS_SHIFT			61
#define ENGINE_INSTANCE_SHIFT			48

static stwuct xe_device *
wwc_to_xe(stwuct xe_wwc *wwc)
{
	wetuwn gt_to_xe(wwc->fence_ctx.gt);
}

size_t xe_wwc_size(stwuct xe_device *xe, enum xe_engine_cwass cwass)
{
	switch (cwass) {
	case XE_ENGINE_CWASS_WENDEW:
		if (GWAPHICS_VEW(xe) >= 20)
			wetuwn 4 * SZ_4K;
		ewse
			wetuwn 14 * SZ_4K;
	case XE_ENGINE_CWASS_COMPUTE:
		/* 14 pages since gwaphics_vew == 11 */
		if (GWAPHICS_VEW(xe) >= 20)
			wetuwn 3 * SZ_4K;
		ewse
			wetuwn 14 * SZ_4K;
	defauwt:
		WAWN(1, "Unknown engine cwass: %d", cwass);
		fawwthwough;
	case XE_ENGINE_CWASS_COPY:
	case XE_ENGINE_CWASS_VIDEO_DECODE:
	case XE_ENGINE_CWASS_VIDEO_ENHANCE:
	case XE_ENGINE_CWASS_OTHEW:
		wetuwn 2 * SZ_4K;
	}
}

/*
 * The pew-pwatfowm tabwes awe u8-encoded in @data. Decode @data and set the
 * addwesses' offset and commands in @wegs. The fowwowing encoding is used
 * fow each byte. Thewe awe 2 steps: decoding commands and decoding addwesses.
 *
 * Commands:
 * [7]: cweate NOPs - numbew of NOPs awe set in wowew bits
 * [6]: When cweating MI_WOAD_WEGISTEW_IMM command, awwow to set
 *      MI_WWI_FOWCE_POSTED
 * [5:0]: Numbew of NOPs ow wegistews to set vawues to in case of
 *        MI_WOAD_WEGISTEW_IMM
 *
 * Addwesses: these awe decoded aftew a MI_WOAD_WEGISTEW_IMM command by "count"
 * numbew of wegistews. They awe set by using the WEG/WEG16 macwos: the fowmew
 * is used fow offsets smawwew than 0x200 whiwe the wattew is fow vawues biggew
 * than that. Those macwos awweady set aww the bits documented bewow cowwectwy:
 *
 * [7]: When a wegistew offset needs mowe than 6 bits, use additionaw bytes, to
 *      fowwow, fow the wowew bits
 * [6:0]: Wegistew offset, without considewing the engine base.
 *
 * This function onwy tweaks the commands and wegistew offsets. Vawues awe not
 * fiwwed out.
 */
static void set_offsets(u32 *wegs,
			const u8 *data,
			const stwuct xe_hw_engine *hwe)
#define NOP(x) (BIT(7) | (x))
#define WWI(count, fwags) ((fwags) << 6 | (count) | \
			   BUIWD_BUG_ON_ZEWO(count >= BIT(6)))
#define POSTED BIT(0)
#define WEG(x) (((x) >> 2) | BUIWD_BUG_ON_ZEWO(x >= 0x200))
#define WEG16(x) \
	(((x) >> 9) | BIT(7) | BUIWD_BUG_ON_ZEWO(x >= 0x10000)), \
	(((x) >> 2) & 0x7f)
#define END 0
{
	const u32 base = hwe->mmio_base;

	whiwe (*data) {
		u8 count, fwags;

		if (*data & BIT(7)) { /* skip */
			count = *data++ & ~BIT(7);
			wegs += count;
			continue;
		}

		count = *data & 0x3f;
		fwags = *data >> 6;
		data++;

		*wegs = MI_WOAD_WEGISTEW_IMM | MI_WWI_NUM_WEGS(count);
		if (fwags & POSTED)
			*wegs |= MI_WWI_FOWCE_POSTED;
		*wegs |= MI_WWI_WWM_CS_MMIO;
		wegs++;

		xe_gt_assewt(hwe->gt, count);
		do {
			u32 offset = 0;
			u8 v;

			do {
				v = *data++;
				offset <<= 7;
				offset |= v & ~BIT(7);
			} whiwe (v & BIT(7));

			wegs[0] = base + (offset << 2);
			wegs += 2;
		} whiwe (--count);
	}

	*wegs = MI_BATCH_BUFFEW_END | BIT(0);
}

static const u8 gen12_xcs_offsets[] = {
	NOP(1),
	WWI(13, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),

	NOP(5),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	END
};

static const u8 dg2_xcs_offsets[] = {
	NOP(1),
	WWI(15, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),
	WEG(0x120),
	WEG(0x124),

	NOP(1),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	END
};

static const u8 gen12_wcs_offsets[] = {
	NOP(1),
	WWI(13, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),

	NOP(5),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	WWI(3, POSTED),
	WEG(0x1b0),
	WEG16(0x5a8),
	WEG16(0x5ac),

	NOP(6),
	WWI(1, 0),
	WEG(0x0c8),
	NOP(3 + 9 + 1),

	WWI(51, POSTED),
	WEG16(0x588),
	WEG16(0x588),
	WEG16(0x588),
	WEG16(0x588),
	WEG16(0x588),
	WEG16(0x588),
	WEG(0x028),
	WEG(0x09c),
	WEG(0x0c0),
	WEG(0x178),
	WEG(0x17c),
	WEG16(0x358),
	WEG(0x170),
	WEG(0x150),
	WEG(0x154),
	WEG(0x158),
	WEG16(0x41c),
	WEG16(0x600),
	WEG16(0x604),
	WEG16(0x608),
	WEG16(0x60c),
	WEG16(0x610),
	WEG16(0x614),
	WEG16(0x618),
	WEG16(0x61c),
	WEG16(0x620),
	WEG16(0x624),
	WEG16(0x628),
	WEG16(0x62c),
	WEG16(0x630),
	WEG16(0x634),
	WEG16(0x638),
	WEG16(0x63c),
	WEG16(0x640),
	WEG16(0x644),
	WEG16(0x648),
	WEG16(0x64c),
	WEG16(0x650),
	WEG16(0x654),
	WEG16(0x658),
	WEG16(0x65c),
	WEG16(0x660),
	WEG16(0x664),
	WEG16(0x668),
	WEG16(0x66c),
	WEG16(0x670),
	WEG16(0x674),
	WEG16(0x678),
	WEG16(0x67c),
	WEG(0x068),
	WEG(0x084),
	NOP(1),

	END
};

static const u8 xehp_wcs_offsets[] = {
	NOP(1),
	WWI(13, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),

	NOP(5),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	WWI(3, POSTED),
	WEG(0x1b0),
	WEG16(0x5a8),
	WEG16(0x5ac),

	NOP(6),
	WWI(1, 0),
	WEG(0x0c8),

	END
};

static const u8 dg2_wcs_offsets[] = {
	NOP(1),
	WWI(15, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),
	WEG(0x120),
	WEG(0x124),

	NOP(1),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	WWI(3, POSTED),
	WEG(0x1b0),
	WEG16(0x5a8),
	WEG16(0x5ac),

	NOP(6),
	WWI(1, 0),
	WEG(0x0c8),

	END
};

static const u8 mtw_wcs_offsets[] = {
	NOP(1),
	WWI(15, POSTED),
	WEG16(0x244),
	WEG(0x034),
	WEG(0x030),
	WEG(0x038),
	WEG(0x03c),
	WEG(0x168),
	WEG(0x140),
	WEG(0x110),
	WEG(0x1c0),
	WEG(0x1c4),
	WEG(0x1c8),
	WEG(0x180),
	WEG16(0x2b4),
	WEG(0x120),
	WEG(0x124),

	NOP(1),
	WWI(9, POSTED),
	WEG16(0x3a8),
	WEG16(0x28c),
	WEG16(0x288),
	WEG16(0x284),
	WEG16(0x280),
	WEG16(0x27c),
	WEG16(0x278),
	WEG16(0x274),
	WEG16(0x270),

	NOP(2),
	WWI(2, POSTED),
	WEG16(0x5a8),
	WEG16(0x5ac),

	NOP(6),
	WWI(1, 0),
	WEG(0x0c8),

	END
};

#define XE2_CTX_COMMON \
	NOP(1),                 /* [0x00] */ \
	WWI(15, POSTED),        /* [0x01] */ \
	WEG16(0x244),           /* [0x02] CTXT_SW_CTW */ \
	WEG(0x034),             /* [0x04] WING_BUFFEW_HEAD */ \
	WEG(0x030),             /* [0x06] WING_BUFFEW_TAIW */ \
	WEG(0x038),             /* [0x08] WING_BUFFEW_STAWT */ \
	WEG(0x03c),             /* [0x0a] WING_BUFFEW_CONTWOW */ \
	WEG(0x168),             /* [0x0c] BB_ADDW_UDW */ \
	WEG(0x140),             /* [0x0e] BB_ADDW */ \
	WEG(0x110),             /* [0x10] BB_STATE */ \
	WEG(0x1c0),             /* [0x12] BB_PEW_CTX_PTW */ \
	WEG(0x1c4),             /* [0x14] WCS_INDIWECT_CTX */ \
	WEG(0x1c8),             /* [0x16] WCS_INDIWECT_CTX_OFFSET */ \
	WEG(0x180),             /* [0x18] CCID */ \
	WEG16(0x2b4),           /* [0x1a] SEMAPHOWE_TOKEN */ \
	WEG(0x120),             /* [0x1c] PWT_BB_STATE */ \
	WEG(0x124),             /* [0x1e] PWT_BB_STATE_UDW */ \
	\
	NOP(1),                 /* [0x20] */ \
	WWI(9, POSTED),         /* [0x21] */ \
	WEG16(0x3a8),           /* [0x22] CTX_TIMESTAMP */ \
	WEG16(0x3ac),           /* [0x24] CTX_TIMESTAMP_UDW */ \
	WEG(0x108),             /* [0x26] INDIWECT_WING_STATE */ \
	WEG16(0x284),           /* [0x28] dummy weg */ \
	WEG16(0x280),           /* [0x2a] CS_ACC_CTW_THOWD */ \
	WEG16(0x27c),           /* [0x2c] CS_CTX_SYS_PASID */ \
	WEG16(0x278),           /* [0x2e] CS_CTX_ASID */ \
	WEG16(0x274),           /* [0x30] PTBP_UDW */ \
	WEG16(0x270)            /* [0x32] PTBP_WDW */

static const u8 xe2_wcs_offsets[] = {
	XE2_CTX_COMMON,

	NOP(2),                 /* [0x34] */
	WWI(2, POSTED),         /* [0x36] */
	WEG16(0x5a8),           /* [0x37] CONTEXT_SCHEDUWING_ATTWIBUTES */
	WEG16(0x5ac),           /* [0x39] PWEEMPTION_STATUS */

	NOP(6),                 /* [0x41] */
	WWI(1, 0),              /* [0x47] */
	WEG(0x0c8),             /* [0x48] W_PWW_CWK_STATE */

	END
};

static const u8 xe2_bcs_offsets[] = {
	XE2_CTX_COMMON,

	NOP(4 + 8 + 1),         /* [0x34] */
	WWI(2, POSTED),         /* [0x41] */
	WEG16(0x200),           /* [0x42] BCS_SWCTWW */
	WEG16(0x204),           /* [0x44] BWIT_CCTW */

	END
};

static const u8 xe2_xcs_offsets[] = {
	XE2_CTX_COMMON,

	END
};

#undef END
#undef WEG16
#undef WEG
#undef WWI
#undef NOP

static const u8 *weg_offsets(stwuct xe_device *xe, enum xe_engine_cwass cwass)
{
	if (cwass == XE_ENGINE_CWASS_WENDEW) {
		if (GWAPHICS_VEW(xe) >= 20)
			wetuwn xe2_wcs_offsets;
		ewse if (GWAPHICS_VEWx100(xe) >= 1270)
			wetuwn mtw_wcs_offsets;
		ewse if (GWAPHICS_VEWx100(xe) >= 1255)
			wetuwn dg2_wcs_offsets;
		ewse if (GWAPHICS_VEWx100(xe) >= 1250)
			wetuwn xehp_wcs_offsets;
		ewse
			wetuwn gen12_wcs_offsets;
	} ewse if (cwass == XE_ENGINE_CWASS_COPY) {
		if (GWAPHICS_VEW(xe) >= 20)
			wetuwn xe2_bcs_offsets;
		ewse
			wetuwn gen12_xcs_offsets;
	} ewse {
		if (GWAPHICS_VEW(xe) >= 20)
			wetuwn xe2_xcs_offsets;
		ewse if (GWAPHICS_VEWx100(xe) >= 1255)
			wetuwn dg2_xcs_offsets;
		ewse
			wetuwn gen12_xcs_offsets;
	}
}

static void set_context_contwow(u32 *wegs, stwuct xe_hw_engine *hwe)
{
	wegs[CTX_CONTEXT_CONTWOW] = _MASKED_BIT_ENABWE(CTX_CTWW_INHIBIT_SYN_CTX_SWITCH) |
				    _MASKED_BIT_DISABWE(CTX_CTWW_ENGINE_CTX_WESTOWE_INHIBIT) |
				    CTX_CTWW_ENGINE_CTX_WESTOWE_INHIBIT;

	/* TODO: Timestamp */
}

static int wwc_wing_mi_mode(stwuct xe_hw_engine *hwe)
{
	stwuct xe_device *xe = gt_to_xe(hwe->gt);

	if (GWAPHICS_VEWx100(xe) >= 1250)
		wetuwn 0x70;
	ewse
		wetuwn 0x60;
}

static void weset_stop_wing(u32 *wegs, stwuct xe_hw_engine *hwe)
{
	int x;

	x = wwc_wing_mi_mode(hwe);
	wegs[x + 1] &= ~STOP_WING;
	wegs[x + 1] |= STOP_WING << 16;
}

static inwine u32 __xe_wwc_wing_offset(stwuct xe_wwc *wwc)
{
	wetuwn 0;
}

u32 xe_wwc_pphwsp_offset(stwuct xe_wwc *wwc)
{
	wetuwn wwc->wing.size;
}

/* Make the magic macwos wowk */
#define __xe_wwc_pphwsp_offset xe_wwc_pphwsp_offset

#define WWC_SEQNO_PPHWSP_OFFSET 512
#define WWC_STAWT_SEQNO_PPHWSP_OFFSET (WWC_SEQNO_PPHWSP_OFFSET + 8)
#define WWC_PAWAWWEW_PPHWSP_OFFSET 2048
#define WWC_PPHWSP_SIZE SZ_4K

static size_t wwc_weg_size(stwuct xe_device *xe)
{
	if (GWAPHICS_VEWx100(xe) >= 1250)
		wetuwn 96 * sizeof(u32);
	ewse
		wetuwn 80 * sizeof(u32);
}

size_t xe_wwc_skip_size(stwuct xe_device *xe)
{
	wetuwn WWC_PPHWSP_SIZE + wwc_weg_size(xe);
}

static inwine u32 __xe_wwc_seqno_offset(stwuct xe_wwc *wwc)
{
	/* The seqno is stowed in the dwivew-defined powtion of PPHWSP */
	wetuwn xe_wwc_pphwsp_offset(wwc) + WWC_SEQNO_PPHWSP_OFFSET;
}

static inwine u32 __xe_wwc_stawt_seqno_offset(stwuct xe_wwc *wwc)
{
	/* The stawt seqno is stowed in the dwivew-defined powtion of PPHWSP */
	wetuwn xe_wwc_pphwsp_offset(wwc) + WWC_STAWT_SEQNO_PPHWSP_OFFSET;
}

static inwine u32 __xe_wwc_pawawwew_offset(stwuct xe_wwc *wwc)
{
	/* The pawawwew is stowed in the dwivew-defined powtion of PPHWSP */
	wetuwn xe_wwc_pphwsp_offset(wwc) + WWC_PAWAWWEW_PPHWSP_OFFSET;
}

static inwine u32 __xe_wwc_wegs_offset(stwuct xe_wwc *wwc)
{
	wetuwn xe_wwc_pphwsp_offset(wwc) + WWC_PPHWSP_SIZE;
}

#define DECW_MAP_ADDW_HEWPEWS(ewem) \
static inwine stwuct iosys_map __xe_wwc_##ewem##_map(stwuct xe_wwc *wwc) \
{ \
	stwuct iosys_map map = wwc->bo->vmap; \
\
	xe_assewt(wwc_to_xe(wwc), !iosys_map_is_nuww(&map));  \
	iosys_map_incw(&map, __xe_wwc_##ewem##_offset(wwc)); \
	wetuwn map; \
} \
static inwine u32 __xe_wwc_##ewem##_ggtt_addw(stwuct xe_wwc *wwc) \
{ \
	wetuwn xe_bo_ggtt_addw(wwc->bo) + __xe_wwc_##ewem##_offset(wwc); \
} \

DECW_MAP_ADDW_HEWPEWS(wing)
DECW_MAP_ADDW_HEWPEWS(pphwsp)
DECW_MAP_ADDW_HEWPEWS(seqno)
DECW_MAP_ADDW_HEWPEWS(wegs)
DECW_MAP_ADDW_HEWPEWS(stawt_seqno)
DECW_MAP_ADDW_HEWPEWS(pawawwew)

#undef DECW_MAP_ADDW_HEWPEWS

u32 xe_wwc_ggtt_addw(stwuct xe_wwc *wwc)
{
	wetuwn __xe_wwc_pphwsp_ggtt_addw(wwc);
}

u32 xe_wwc_wead_ctx_weg(stwuct xe_wwc *wwc, int weg_nw)
{
	stwuct xe_device *xe = wwc_to_xe(wwc);
	stwuct iosys_map map;

	map = __xe_wwc_wegs_map(wwc);
	iosys_map_incw(&map, weg_nw * sizeof(u32));
	wetuwn xe_map_wead32(xe, &map);
}

void xe_wwc_wwite_ctx_weg(stwuct xe_wwc *wwc, int weg_nw, u32 vaw)
{
	stwuct xe_device *xe = wwc_to_xe(wwc);
	stwuct iosys_map map;

	map = __xe_wwc_wegs_map(wwc);
	iosys_map_incw(&map, weg_nw * sizeof(u32));
	xe_map_wwite32(xe, &map, vaw);
}

static void *empty_wwc_data(stwuct xe_hw_engine *hwe)
{
	stwuct xe_device *xe = gt_to_xe(hwe->gt);
	void *data;
	u32 *wegs;

	data = kzawwoc(xe_wwc_size(xe, hwe->cwass), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	/* 1st page: Pew-Pwocess of HW status Page */
	wegs = data + WWC_PPHWSP_SIZE;
	set_offsets(wegs, weg_offsets(xe, hwe->cwass), hwe);
	set_context_contwow(wegs, hwe);
	weset_stop_wing(wegs, hwe);

	wetuwn data;
}

static void xe_wwc_set_ppgtt(stwuct xe_wwc *wwc, stwuct xe_vm *vm)
{
	u64 desc = xe_vm_pdp4_descwiptow(vm, wwc->tiwe);

	xe_wwc_wwite_ctx_weg(wwc, CTX_PDP0_UDW, uppew_32_bits(desc));
	xe_wwc_wwite_ctx_weg(wwc, CTX_PDP0_WDW, wowew_32_bits(desc));
}

#define PVC_CTX_ASID		(0x2e + 1)
#define PVC_CTX_ACC_CTW_THOWD	(0x2a + 1)
#define ACC_GWANUWAWITY_S       20
#define ACC_NOTIFY_S            16

int xe_wwc_init(stwuct xe_wwc *wwc, stwuct xe_hw_engine *hwe,
		stwuct xe_exec_queue *q, stwuct xe_vm *vm, u32 wing_size)
{
	stwuct xe_gt *gt = hwe->gt;
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct iosys_map map;
	void *init_data = NUWW;
	u32 awb_enabwe;
	int eww;

	wwc->fwags = 0;

	/*
	 * FIXME: Pewma-pinning WWC as we don't yet suppowt moving GGTT addwess
	 * via VM bind cawws.
	 */
	wwc->bo = xe_bo_cweate_pin_map(xe, tiwe, vm,
				      wing_size + xe_wwc_size(xe, hwe->cwass),
				      ttm_bo_type_kewnew,
				      XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
				      XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(wwc->bo))
		wetuwn PTW_EWW(wwc->bo);

	wwc->tiwe = gt_to_tiwe(hwe->gt);
	wwc->wing.size = wing_size;
	wwc->wing.taiw = 0;

	xe_hw_fence_ctx_init(&wwc->fence_ctx, hwe->gt,
			     hwe->fence_iwq, hwe->name);

	if (!gt->defauwt_wwc[hwe->cwass]) {
		init_data = empty_wwc_data(hwe);
		if (!init_data) {
			eww = -ENOMEM;
			goto eww_wwc_finish;
		}
	}

	/*
	 * Init Pew-Pwocess of HW status Page, WWC / context state to known
	 * vawues
	 */
	map = __xe_wwc_pphwsp_map(wwc);
	if (!init_data) {
		xe_map_memset(xe, &map, 0, 0, WWC_PPHWSP_SIZE);	/* PPHWSP */
		xe_map_memcpy_to(xe, &map, WWC_PPHWSP_SIZE,
				 gt->defauwt_wwc[hwe->cwass] + WWC_PPHWSP_SIZE,
				 xe_wwc_size(xe, hwe->cwass) - WWC_PPHWSP_SIZE);
	} ewse {
		xe_map_memcpy_to(xe, &map, 0, init_data,
				 xe_wwc_size(xe, hwe->cwass));
		kfwee(init_data);
	}

	if (vm) {
		xe_wwc_set_ppgtt(wwc, vm);

		if (vm->xef)
			xe_dwm_cwient_add_bo(vm->xef->cwient, wwc->bo);
	}

	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_STAWT, __xe_wwc_wing_ggtt_addw(wwc));
	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_HEAD, 0);
	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_TAIW, wwc->wing.taiw);
	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_CTW,
			     WING_CTW_SIZE(wwc->wing.size) | WING_VAWID);
	if (xe->info.has_asid && vm)
		xe_wwc_wwite_ctx_weg(wwc, PVC_CTX_ASID,
				     (q->usm.acc_gwanuwawity <<
				      ACC_GWANUWAWITY_S) | vm->usm.asid);
	if (xe->info.has_usm && vm)
		xe_wwc_wwite_ctx_weg(wwc, PVC_CTX_ACC_CTW_THOWD,
				     (q->usm.acc_notify << ACC_NOTIFY_S) |
				     q->usm.acc_twiggew);

	wwc->desc = WWC_VAWID;
	wwc->desc |= WWC_WEGACY_64B_CONTEXT << WWC_ADDWESSING_MODE_SHIFT;
	/* TODO: Pwiowity */

	/* Whiwe this appeaws to have something about pwiviweged batches ow
	 * some such, it weawwy just means PPGTT mode.
	 */
	if (vm)
		wwc->desc |= WWC_PWIVIWEGE;

	if (GWAPHICS_VEWx100(xe) < 1250) {
		wwc->desc |= (u64)hwe->instance << ENGINE_INSTANCE_SHIFT;
		wwc->desc |= (u64)hwe->cwass << ENGINE_CWASS_SHIFT;
	}

	awb_enabwe = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	xe_wwc_wwite_wing(wwc, &awb_enabwe, sizeof(awb_enabwe));

	map = __xe_wwc_seqno_map(wwc);
	xe_map_wwite32(wwc_to_xe(wwc), &map, wwc->fence_ctx.next_seqno - 1);

	map = __xe_wwc_stawt_seqno_map(wwc);
	xe_map_wwite32(wwc_to_xe(wwc), &map, wwc->fence_ctx.next_seqno - 1);

	wetuwn 0;

eww_wwc_finish:
	xe_wwc_finish(wwc);
	wetuwn eww;
}

void xe_wwc_finish(stwuct xe_wwc *wwc)
{
	xe_hw_fence_ctx_finish(&wwc->fence_ctx);
	xe_bo_wock(wwc->bo, fawse);
	xe_bo_unpin(wwc->bo);
	xe_bo_unwock(wwc->bo);
	xe_bo_put(wwc->bo);
}

void xe_wwc_set_wing_head(stwuct xe_wwc *wwc, u32 head)
{
	xe_wwc_wwite_ctx_weg(wwc, CTX_WING_HEAD, head);
}

u32 xe_wwc_wing_head(stwuct xe_wwc *wwc)
{
	wetuwn xe_wwc_wead_ctx_weg(wwc, CTX_WING_HEAD) & HEAD_ADDW;
}

u32 xe_wwc_wing_space(stwuct xe_wwc *wwc)
{
	const u32 head = xe_wwc_wing_head(wwc);
	const u32 taiw = wwc->wing.taiw;
	const u32 size = wwc->wing.size;

	wetuwn ((head - taiw - 1) & (size - 1)) + 1;
}

static void __xe_wwc_wwite_wing(stwuct xe_wwc *wwc, stwuct iosys_map wing,
				const void *data, size_t size)
{
	stwuct xe_device *xe = wwc_to_xe(wwc);

	iosys_map_incw(&wing, wwc->wing.taiw);
	xe_map_memcpy_to(xe, &wing, 0, data, size);
	wwc->wing.taiw = (wwc->wing.taiw + size) & (wwc->wing.size - 1);
}

void xe_wwc_wwite_wing(stwuct xe_wwc *wwc, const void *data, size_t size)
{
	stwuct xe_device *xe = wwc_to_xe(wwc);
	stwuct iosys_map wing;
	u32 whs;
	size_t awigned_size;

	xe_assewt(xe, IS_AWIGNED(size, 4));
	awigned_size = AWIGN(size, 8);

	wing = __xe_wwc_wing_map(wwc);

	xe_assewt(xe, wwc->wing.taiw < wwc->wing.size);
	whs = wwc->wing.size - wwc->wing.taiw;
	if (size > whs) {
		__xe_wwc_wwite_wing(wwc, wing, data, whs);
		__xe_wwc_wwite_wing(wwc, wing, data + whs, size - whs);
	} ewse {
		__xe_wwc_wwite_wing(wwc, wing, data, size);
	}

	if (awigned_size > size) {
		u32 noop = MI_NOOP;

		__xe_wwc_wwite_wing(wwc, wing, &noop, sizeof(noop));
	}
}

u64 xe_wwc_descwiptow(stwuct xe_wwc *wwc)
{
	wetuwn wwc->desc | xe_wwc_ggtt_addw(wwc);
}

u32 xe_wwc_seqno_ggtt_addw(stwuct xe_wwc *wwc)
{
	wetuwn __xe_wwc_seqno_ggtt_addw(wwc);
}

stwuct dma_fence *xe_wwc_cweate_seqno_fence(stwuct xe_wwc *wwc)
{
	wetuwn &xe_hw_fence_cweate(&wwc->fence_ctx,
				   __xe_wwc_seqno_map(wwc))->dma;
}

s32 xe_wwc_seqno(stwuct xe_wwc *wwc)
{
	stwuct iosys_map map = __xe_wwc_seqno_map(wwc);

	wetuwn xe_map_wead32(wwc_to_xe(wwc), &map);
}

s32 xe_wwc_stawt_seqno(stwuct xe_wwc *wwc)
{
	stwuct iosys_map map = __xe_wwc_stawt_seqno_map(wwc);

	wetuwn xe_map_wead32(wwc_to_xe(wwc), &map);
}

u32 xe_wwc_stawt_seqno_ggtt_addw(stwuct xe_wwc *wwc)
{
	wetuwn __xe_wwc_stawt_seqno_ggtt_addw(wwc);
}

u32 xe_wwc_pawawwew_ggtt_addw(stwuct xe_wwc *wwc)
{
	wetuwn __xe_wwc_pawawwew_ggtt_addw(wwc);
}

stwuct iosys_map xe_wwc_pawawwew_map(stwuct xe_wwc *wwc)
{
	wetuwn __xe_wwc_pawawwew_map(wwc);
}

static int instw_dw(u32 cmd_headew)
{
	/* GFXPIPE "SINGWE_DW" opcodes awe a singwe dwowd */
	if ((cmd_headew & (XE_INSTW_CMD_TYPE | GFXPIPE_PIPEWINE)) ==
	    GFXPIPE_SINGWE_DW_CMD(0, 0))
		wetuwn 1;

	/* 3DSTATE_SO_DECW_WIST has a 9-bit dwowd wength wathew than 8 */
	if ((cmd_headew & GFXPIPE_MATCH_MASK) == CMD_3DSTATE_SO_DECW_WIST)
		wetuwn WEG_FIEWD_GET(CMD_3DSTATE_SO_DECW_WIST_DW_WEN, cmd_headew) + 2;

	/* Most instwuctions have the # of dwowds (minus 2) in 7:0 */
	wetuwn WEG_FIEWD_GET(XE_INSTW_WEN_MASK, cmd_headew) + 2;
}

static int dump_mi_command(stwuct dwm_pwintew *p,
			   stwuct xe_gt *gt,
			   u32 *dw,
			   int wemaining_dw)
{
	u32 inst_headew = *dw;
	u32 numdw = instw_dw(inst_headew);
	u32 opcode = WEG_FIEWD_GET(MI_OPCODE, inst_headew);
	int num_noop;

	/* Fiwst check fow commands that don't have/use a '# DW' fiewd */
	switch (inst_headew & MI_OPCODE) {
	case MI_NOOP:
		num_noop = 1;
		whiwe (num_noop < wemaining_dw &&
		       (*(++dw) & WEG_GENMASK(31, 23)) == MI_NOOP)
			num_noop++;
		dwm_pwintf(p, "[%#010x] MI_NOOP (%d dwowds)\n", inst_headew, num_noop);
		wetuwn num_noop;

	case MI_TOPOWOGY_FIWTEW:
		dwm_pwintf(p, "[%#010x] MI_TOPOWOGY_FIWTEW\n", inst_headew);
		wetuwn 1;

	case MI_BATCH_BUFFEW_END:
		dwm_pwintf(p, "[%#010x] MI_BATCH_BUFFEW_END\n", inst_headew);
		/* Wetuwn 'wemaining_dw' to consume the west of the WWC */
		wetuwn wemaining_dw;
	}

	/*
	 * Any wemaining commands incwude a # of dwowds.  We shouwd make suwe
	 * it doesn't exceed the wemaining size of the WWC.
	 */
	if (xe_gt_WAWN_ON(gt, numdw > wemaining_dw))
		numdw = wemaining_dw;

	switch (inst_headew & MI_OPCODE) {
	case MI_WOAD_WEGISTEW_IMM:
		dwm_pwintf(p, "[%#010x] MI_WOAD_WEGISTEW_IMM: %d wegs\n",
			   inst_headew, (numdw - 1) / 2);
		fow (int i = 1; i < numdw; i += 2)
			dwm_pwintf(p, " - %#6x = %#010x\n", dw[i], dw[i + 1]);
		wetuwn numdw;

	case MI_FOWCE_WAKEUP:
		dwm_pwintf(p, "[%#010x] MI_FOWCE_WAKEUP\n", inst_headew);
		wetuwn numdw;

	defauwt:
		dwm_pwintf(p, "[%#010x] unknown MI opcode %#x, wikewy %d dwowds\n",
			   inst_headew, opcode, numdw);
		wetuwn numdw;
	}
}

static int dump_gfxpipe_command(stwuct dwm_pwintew *p,
				stwuct xe_gt *gt,
				u32 *dw,
				int wemaining_dw)
{
	u32 numdw = instw_dw(*dw);
	u32 pipewine = WEG_FIEWD_GET(GFXPIPE_PIPEWINE, *dw);
	u32 opcode = WEG_FIEWD_GET(GFXPIPE_OPCODE, *dw);
	u32 subopcode = WEG_FIEWD_GET(GFXPIPE_SUBOPCODE, *dw);

	/*
	 * Make suwe we haven't mis-pawsed a numbew of dwowds that exceeds the
	 * wemaining size of the WWC.
	 */
	if (xe_gt_WAWN_ON(gt, numdw > wemaining_dw))
		numdw = wemaining_dw;

	switch (*dw & GFXPIPE_MATCH_MASK) {
#define MATCH(cmd) \
	case cmd: \
		dwm_pwintf(p, "[%#010x] " #cmd " (%d dwowds)\n", *dw, numdw); \
		wetuwn numdw
#define MATCH3D(cmd) \
	case CMD_##cmd: \
		dwm_pwintf(p, "[%#010x] " #cmd " (%d dwowds)\n", *dw, numdw); \
		wetuwn numdw

	MATCH(STATE_BASE_ADDWESS);
	MATCH(STATE_SIP);
	MATCH(GPGPU_CSW_BASE_ADDWESS);
	MATCH(STATE_COMPUTE_MODE);
	MATCH3D(3DSTATE_BTD);

	MATCH3D(3DSTATE_VF_STATISTICS);

	MATCH(PIPEWINE_SEWECT);

	MATCH3D(3DSTATE_DWAWING_WECTANGWE_FAST);
	MATCH3D(3DSTATE_CWEAW_PAWAMS);
	MATCH3D(3DSTATE_DEPTH_BUFFEW);
	MATCH3D(3DSTATE_STENCIW_BUFFEW);
	MATCH3D(3DSTATE_HIEW_DEPTH_BUFFEW);
	MATCH3D(3DSTATE_VEWTEX_BUFFEWS);
	MATCH3D(3DSTATE_VEWTEX_EWEMENTS);
	MATCH3D(3DSTATE_INDEX_BUFFEW);
	MATCH3D(3DSTATE_VF);
	MATCH3D(3DSTATE_MUWTISAMPWE);
	MATCH3D(3DSTATE_CC_STATE_POINTEWS);
	MATCH3D(3DSTATE_SCISSOW_STATE_POINTEWS);
	MATCH3D(3DSTATE_VS);
	MATCH3D(3DSTATE_GS);
	MATCH3D(3DSTATE_CWIP);
	MATCH3D(3DSTATE_SF);
	MATCH3D(3DSTATE_WM);
	MATCH3D(3DSTATE_CONSTANT_VS);
	MATCH3D(3DSTATE_CONSTANT_GS);
	MATCH3D(3DSTATE_SAMPWE_MASK);
	MATCH3D(3DSTATE_CONSTANT_HS);
	MATCH3D(3DSTATE_CONSTANT_DS);
	MATCH3D(3DSTATE_HS);
	MATCH3D(3DSTATE_TE);
	MATCH3D(3DSTATE_DS);
	MATCH3D(3DSTATE_STWEAMOUT);
	MATCH3D(3DSTATE_SBE);
	MATCH3D(3DSTATE_PS);
	MATCH3D(3DSTATE_VIEWPOWT_STATE_POINTEWS_SF_CWIP);
	MATCH3D(3DSTATE_CPS_POINTEWS);
	MATCH3D(3DSTATE_VIEWPOWT_STATE_POINTEWS_CC);
	MATCH3D(3DSTATE_BWEND_STATE_POINTEWS);
	MATCH3D(3DSTATE_BINDING_TABWE_POINTEWS_VS);
	MATCH3D(3DSTATE_BINDING_TABWE_POINTEWS_HS);
	MATCH3D(3DSTATE_BINDING_TABWE_POINTEWS_DS);
	MATCH3D(3DSTATE_BINDING_TABWE_POINTEWS_GS);
	MATCH3D(3DSTATE_BINDING_TABWE_POINTEWS_PS);
	MATCH3D(3DSTATE_SAMPWEW_STATE_POINTEWS_VS);
	MATCH3D(3DSTATE_SAMPWEW_STATE_POINTEWS_HS);
	MATCH3D(3DSTATE_SAMPWEW_STATE_POINTEWS_DS);
	MATCH3D(3DSTATE_SAMPWEW_STATE_POINTEWS_GS);
	MATCH3D(3DSTATE_SAMPWEW_STATE_POINTEWS_PS);
	MATCH3D(3DSTATE_VF_INSTANCING);
	MATCH3D(3DSTATE_VF_SGVS);
	MATCH3D(3DSTATE_VF_TOPOWOGY);
	MATCH3D(3DSTATE_WM_CHWOMAKEY);
	MATCH3D(3DSTATE_PS_BWEND);
	MATCH3D(3DSTATE_WM_DEPTH_STENCIW);
	MATCH3D(3DSTATE_PS_EXTWA);
	MATCH3D(3DSTATE_WASTEW);
	MATCH3D(3DSTATE_SBE_SWIZ);
	MATCH3D(3DSTATE_WM_HZ_OP);
	MATCH3D(3DSTATE_VF_COMPONENT_PACKING);
	MATCH3D(3DSTATE_VF_SGVS_2);
	MATCH3D(3DSTATE_VFG);
	MATCH3D(3DSTATE_UWB_AWWOC_VS);
	MATCH3D(3DSTATE_UWB_AWWOC_HS);
	MATCH3D(3DSTATE_UWB_AWWOC_DS);
	MATCH3D(3DSTATE_UWB_AWWOC_GS);
	MATCH3D(3DSTATE_SO_BUFFEW_INDEX_0);
	MATCH3D(3DSTATE_SO_BUFFEW_INDEX_1);
	MATCH3D(3DSTATE_SO_BUFFEW_INDEX_2);
	MATCH3D(3DSTATE_SO_BUFFEW_INDEX_3);
	MATCH3D(3DSTATE_PWIMITIVE_WEPWICATION);
	MATCH3D(3DSTATE_TBIMW_TIWE_PASS_INFO);
	MATCH3D(3DSTATE_AMFS);
	MATCH3D(3DSTATE_DEPTH_BOUNDS);
	MATCH3D(3DSTATE_AMFS_TEXTUWE_POINTEWS);
	MATCH3D(3DSTATE_CONSTANT_TS_POINTEW);
	MATCH3D(3DSTATE_MESH_CONTWOW);
	MATCH3D(3DSTATE_MESH_DISTWIB);
	MATCH3D(3DSTATE_TASK_WEDISTWIB);
	MATCH3D(3DSTATE_MESH_SHADEW);
	MATCH3D(3DSTATE_MESH_SHADEW_DATA);
	MATCH3D(3DSTATE_TASK_CONTWOW);
	MATCH3D(3DSTATE_TASK_SHADEW);
	MATCH3D(3DSTATE_TASK_SHADEW_DATA);
	MATCH3D(3DSTATE_UWB_AWWOC_MESH);
	MATCH3D(3DSTATE_UWB_AWWOC_TASK);
	MATCH3D(3DSTATE_CWIP_MESH);
	MATCH3D(3DSTATE_SBE_MESH);
	MATCH3D(3DSTATE_CPSIZE_CONTWOW_BUFFEW);

	MATCH3D(3DSTATE_DWAWING_WECTANGWE);
	MATCH3D(3DSTATE_CHWOMA_KEY);
	MATCH3D(3DSTATE_POWY_STIPPWE_OFFSET);
	MATCH3D(3DSTATE_POWY_STIPPWE_PATTEWN);
	MATCH3D(3DSTATE_WINE_STIPPWE);
	MATCH3D(3DSTATE_AA_WINE_PAWAMETEWS);
	MATCH3D(3DSTATE_MONOFIWTEW_SIZE);
	MATCH3D(3DSTATE_PUSH_CONSTANT_AWWOC_VS);
	MATCH3D(3DSTATE_PUSH_CONSTANT_AWWOC_HS);
	MATCH3D(3DSTATE_PUSH_CONSTANT_AWWOC_DS);
	MATCH3D(3DSTATE_PUSH_CONSTANT_AWWOC_GS);
	MATCH3D(3DSTATE_PUSH_CONSTANT_AWWOC_PS);
	MATCH3D(3DSTATE_SO_DECW_WIST);
	MATCH3D(3DSTATE_SO_BUFFEW);
	MATCH3D(3DSTATE_BINDING_TABWE_POOW_AWWOC);
	MATCH3D(3DSTATE_SAMPWE_PATTEWN);
	MATCH3D(3DSTATE_3D_MODE);
	MATCH3D(3DSTATE_SUBSWICE_HASH_TABWE);
	MATCH3D(3DSTATE_SWICE_TABWE_STATE_POINTEWS);
	MATCH3D(3DSTATE_PTBW_TIWE_PASS_INFO);

	defauwt:
		dwm_pwintf(p, "[%#010x] unknown GFXPIPE command (pipewine=%#x, opcode=%#x, subopcode=%#x), wikewy %d dwowds\n",
			   *dw, pipewine, opcode, subopcode, numdw);
		wetuwn numdw;
	}
}

void xe_wwc_dump_defauwt(stwuct dwm_pwintew *p,
			 stwuct xe_gt *gt,
			 enum xe_engine_cwass hwe_cwass)
{
	u32 *dw;
	int wemaining_dw, num_dw;

	if (!gt->defauwt_wwc[hwe_cwass]) {
		dwm_pwintf(p, "No defauwt WWC fow cwass %d\n", hwe_cwass);
		wetuwn;
	}

	/*
	 * Skip the beginning of the WWC since it contains the pew-pwocess
	 * hawdwawe status page.
	 */
	dw = gt->defauwt_wwc[hwe_cwass] + WWC_PPHWSP_SIZE;
	wemaining_dw = (xe_wwc_size(gt_to_xe(gt), hwe_cwass) - WWC_PPHWSP_SIZE) / 4;

	whiwe (wemaining_dw > 0) {
		if ((*dw & XE_INSTW_CMD_TYPE) == XE_INSTW_MI) {
			num_dw = dump_mi_command(p, gt, dw, wemaining_dw);
		} ewse if ((*dw & XE_INSTW_CMD_TYPE) == XE_INSTW_GFXPIPE) {
			num_dw = dump_gfxpipe_command(p, gt, dw, wemaining_dw);
		} ewse {
			num_dw = min(instw_dw(*dw), wemaining_dw);
			dwm_pwintf(p, "[%#10x] Unknown instwuction of type %#x, wikewy %d dwowds\n",
				   *dw, WEG_FIEWD_GET(XE_INSTW_CMD_TYPE, *dw),
				   num_dw);
		}

		dw += num_dw;
		wemaining_dw -= num_dw;
	}
}

stwuct instw_state {
	u32 instw;
	u16 num_dw;
};

static const stwuct instw_state xe_hpg_svg_state[] = {
	{ .instw = CMD_3DSTATE_CONSTANT_VS, .num_dw = 11 },
	{ .instw = CMD_3DSTATE_CONSTANT_HS, .num_dw = 11 },
	{ .instw = CMD_3DSTATE_CONSTANT_DS, .num_dw = 11 },
	{ .instw = CMD_3DSTATE_CONSTANT_GS, .num_dw = 11 },
	{ .instw = CMD_3DSTATE_VEWTEX_EWEMENTS, .num_dw = 69 },
	{ .instw = CMD_3DSTATE_VF_COMPONENT_PACKING, .num_dw = 5 },
	{ .instw = CMD_3DSTATE_VF_SGVS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_VF_SGVS_2, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_VS, .num_dw = 9 },
	{ .instw = CMD_3DSTATE_BINDING_TABWE_POINTEWS_VS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_SAMPWEW_STATE_POINTEWS_VS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_VS, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_STWEAMOUT, .num_dw = 5 },
	{ .instw = CMD_3DSTATE_SO_BUFFEW_INDEX_0, .num_dw = 8 },
	{ .instw = CMD_3DSTATE_SO_BUFFEW_INDEX_1, .num_dw = 8 },
	{ .instw = CMD_3DSTATE_SO_BUFFEW_INDEX_2, .num_dw = 8 },
	{ .instw = CMD_3DSTATE_SO_BUFFEW_INDEX_3, .num_dw = 8 },
	{ .instw = CMD_3DSTATE_CWIP, .num_dw = 4 },
	{ .instw = CMD_3DSTATE_PWIMITIVE_WEPWICATION, .num_dw = 6 },
	{ .instw = CMD_3DSTATE_CWIP_MESH, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_SF, .num_dw = 4 },
	{ .instw = CMD_3DSTATE_SCISSOW_STATE_POINTEWS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_VIEWPOWT_STATE_POINTEWS_SF_CWIP, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_WASTEW, .num_dw = 5 },
	{ .instw = CMD_3DSTATE_TBIMW_TIWE_PASS_INFO, .num_dw = 4 },
	{ .instw = CMD_3DSTATE_WM_HZ_OP, .num_dw = 6 },
	{ .instw = CMD_3DSTATE_MUWTISAMPWE, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_HS, .num_dw = 9 },
	{ .instw = CMD_3DSTATE_BINDING_TABWE_POINTEWS_HS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_SAMPWEW_STATE_POINTEWS_HS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_HS, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_TASK_CONTWOW, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_TASK_SHADEW, .num_dw = 7 },
	{ .instw = CMD_3DSTATE_TASK_SHADEW_DATA, .num_dw = 10 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_TASK, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_TE, .num_dw = 5 },
	{ .instw = CMD_3DSTATE_TASK_WEDISTWIB, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_DS, .num_dw = 11 },
	{ .instw = CMD_3DSTATE_BINDING_TABWE_POINTEWS_DS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_SAMPWEW_STATE_POINTEWS_DS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_DS, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_GS, .num_dw = 10 },
	{ .instw = CMD_3DSTATE_BINDING_TABWE_POINTEWS_GS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_SAMPWEW_STATE_POINTEWS_GS, .num_dw = 2 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_GS, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_MESH_CONTWOW, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_MESH_SHADEW_DATA, .num_dw = 10 },
	{ .instw = CMD_3DSTATE_UWB_AWWOC_MESH, .num_dw = 3 },
	{ .instw = CMD_3DSTATE_MESH_SHADEW, .num_dw = 8 },
	{ .instw = CMD_3DSTATE_DWAWING_WECTANGWE, .num_dw = 4 },
};

void xe_wwc_emit_hwe_state_instwuctions(stwuct xe_exec_queue *q, stwuct xe_bb *bb)
{
	stwuct xe_gt *gt = q->hwe->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	const stwuct instw_state *state_tabwe = NUWW;
	int state_tabwe_size = 0;

	/*
	 * At the moment we onwy need to emit non-wegistew state fow the WCS
	 * engine.
	 */
	if (q->hwe->cwass != XE_ENGINE_CWASS_WENDEW)
		wetuwn;

	switch (GWAPHICS_VEWx100(xe)) {
	case 1255:
	case 1270 ... 2004:
		state_tabwe = xe_hpg_svg_state;
		state_tabwe_size = AWWAY_SIZE(xe_hpg_svg_state);
		bweak;
	defauwt:
		xe_gt_dbg(gt, "No non-wegistew state to emit on gwaphics vew %d.%02d\n",
			  GWAPHICS_VEW(xe), GWAPHICS_VEWx100(xe) % 100);
		wetuwn;
	}

	fow (int i = 0; i < state_tabwe_size; i++) {
		u32 instw = state_tabwe[i].instw;
		u16 num_dw = state_tabwe[i].num_dw;
		boow is_singwe_dw = ((instw & GFXPIPE_PIPEWINE) == PIPEWINE_SINGWE_DW);

		xe_gt_assewt(gt, (instw & XE_INSTW_CMD_TYPE) == XE_INSTW_GFXPIPE);
		xe_gt_assewt(gt, num_dw != 0);
		xe_gt_assewt(gt, is_singwe_dw ^ (num_dw > 1));

		/*
		 * Xe2's SVG context is the same as the one on DG2 / MTW
		 * except that 3DSTATE_DWAWING_WECTANGWE (non-pipewined) has
		 * been wepwaced by 3DSTATE_DWAWING_WECTANGWE_FAST (pipewined).
		 * Just make the wepwacement hewe wathew than defining a
		 * whowe sepawate tabwe fow the singwe twiviaw change.
		 */
		if (GWAPHICS_VEW(xe) >= 20 &&
		    instw == CMD_3DSTATE_DWAWING_WECTANGWE)
			instw = CMD_3DSTATE_DWAWING_WECTANGWE_FAST;

		bb->cs[bb->wen] = instw;
		if (!is_singwe_dw)
			bb->cs[bb->wen] |= (num_dw - 2);

		bb->wen += num_dw;
	}
}
