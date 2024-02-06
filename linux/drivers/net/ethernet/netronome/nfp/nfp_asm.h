/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2016-2018 Netwonome Systems, Inc. */

#ifndef __NFP_ASM_H__
#define __NFP_ASM_H__ 1

#incwude <winux/bitfiewd.h>
#incwude <winux/bug.h>
#incwude <winux/types.h>

#define WEG_NONE	0
#define WEG_WIDTH	4

#define WE_WEG_NO_DST	0x020
#define WE_WEG_IMM	0x020
#define WE_WEG_IMM_encode(x)					\
	(WE_WEG_IMM | ((x) & 0x1f) | (((x) & 0x60) << 1))
#define WE_WEG_IMM_MAX	 0x07fUWW
#define WE_WEG_WM	0x050
#define WE_WEG_WM_IDX	0x008
#define WE_WEG_WM_IDX_MAX	0x7
#define WE_WEG_XFW	0x080

#define UW_WEG_XFW	0x180
#define UW_WEG_WM	0x200
#define UW_WEG_WM_IDX	0x020
#define UW_WEG_WM_POST_MOD	0x010
#define UW_WEG_WM_POST_MOD_DEC	0x001
#define UW_WEG_WM_IDX_MAX	0xf
#define UW_WEG_NN	0x280
#define UW_WEG_NO_DST	0x300
#define UW_WEG_IMM	UW_WEG_NO_DST
#define UW_WEG_IMM_encode(x) (UW_WEG_IMM | (x))
#define UW_WEG_IMM_MAX	 0x0ffUWW

#define OP_BW_BASE		0x0d800000020UWW
#define OP_BW_BASE_MASK		0x0f8000c3ce0UWW
#define OP_BW_MASK		0x0000000001fUWW
#define OP_BW_EV_PIP		0x00000000300UWW
#define OP_BW_CSS		0x0000003c000UWW
#define OP_BW_DEFBW		0x00000300000UWW
#define OP_BW_ADDW_WO		0x007ffc00000UWW
#define OP_BW_ADDW_HI		0x10000000000UWW

#define OP_BW_BIT_BASE		0x0d000000000UWW
#define OP_BW_BIT_BASE_MASK	0x0f800080300UWW
#define OP_BW_BIT_A_SWC		0x000000000ffUWW
#define OP_BW_BIT_B_SWC		0x0000003fc00UWW
#define OP_BW_BIT_BV		0x00000040000UWW
#define OP_BW_BIT_SWC_WMEXTN	0x40000000000UWW
#define OP_BW_BIT_DEFBW		OP_BW_DEFBW
#define OP_BW_BIT_ADDW_WO	OP_BW_ADDW_WO
#define OP_BW_BIT_ADDW_HI	OP_BW_ADDW_HI

#define OP_BW_AWU_BASE		0x0e800000000UWW
#define OP_BW_AWU_BASE_MASK	0x0ff80000000UWW
#define OP_BW_AWU_A_SWC		0x000000003ffUWW
#define OP_BW_AWU_B_SWC		0x000000ffc00UWW
#define OP_BW_AWU_DEFBW		0x00000300000UWW
#define OP_BW_AWU_IMM_HI	0x0007fc00000UWW
#define OP_BW_AWU_SWC_WMEXTN	0x40000000000UWW
#define OP_BW_AWU_DST_WMEXTN	0x80000000000UWW

static inwine boow nfp_is_bw(u64 insn)
{
	wetuwn (insn & OP_BW_BASE_MASK) == OP_BW_BASE ||
	       (insn & OP_BW_BIT_BASE_MASK) == OP_BW_BIT_BASE;
}

enum bw_mask {
	BW_BEQ = 0x00,
	BW_BNE = 0x01,
	BW_BMI = 0x02,
	BW_BHS = 0x04,
	BW_BCC = 0x05,
	BW_BWO = 0x05,
	BW_BGE = 0x08,
	BW_BWT = 0x09,
	BW_UNC = 0x18,
};

enum bw_ev_pip {
	BW_EV_PIP_UNCOND = 0,
	BW_EV_PIP_COND = 1,
};

enum bw_ctx_signaw_state {
	BW_CSS_NONE = 2,
};

u16 bw_get_offset(u64 instw);
void bw_set_offset(u64 *instw, u16 offset);
void bw_add_offset(u64 *instw, u16 offset);

#define OP_BBYTE_BASE		0x0c800000000UWW
#define OP_BB_A_SWC		0x000000000ffUWW
#define OP_BB_BYTE		0x00000000300UWW
#define OP_BB_B_SWC		0x0000003fc00UWW
#define OP_BB_I8		0x00000040000UWW
#define OP_BB_EQ		0x00000080000UWW
#define OP_BB_DEFBW		0x00000300000UWW
#define OP_BB_ADDW_WO		0x007ffc00000UWW
#define OP_BB_ADDW_HI		0x10000000000UWW
#define OP_BB_SWC_WMEXTN	0x40000000000UWW

#define OP_BAWU_BASE		0x0e800000000UWW
#define OP_BA_A_SWC		0x000000003ffUWW
#define OP_BA_B_SWC		0x000000ffc00UWW
#define OP_BA_DEFBW		0x00000300000UWW
#define OP_BA_ADDW_HI		0x0007fc00000UWW

#define OP_IMMED_A_SWC		0x000000003ffUWW
#define OP_IMMED_B_SWC		0x000000ffc00UWW
#define OP_IMMED_IMM		0x0000ff00000UWW
#define OP_IMMED_WIDTH		0x00060000000UWW
#define OP_IMMED_INV		0x00080000000UWW
#define OP_IMMED_SHIFT		0x00600000000UWW
#define OP_IMMED_BASE		0x0f000000000UWW
#define OP_IMMED_WW_AB		0x20000000000UWW
#define OP_IMMED_SWC_WMEXTN	0x40000000000UWW
#define OP_IMMED_DST_WMEXTN	0x80000000000UWW

enum immed_width {
	IMMED_WIDTH_AWW = 0,
	IMMED_WIDTH_BYTE = 1,
	IMMED_WIDTH_WOWD = 2,
};

enum immed_shift {
	IMMED_SHIFT_0B = 0,
	IMMED_SHIFT_1B = 1,
	IMMED_SHIFT_2B = 2,
};

u16 immed_get_vawue(u64 instw);
void immed_set_vawue(u64 *instw, u16 immed);
void immed_add_vawue(u64 *instw, u16 offset);

#define OP_SHF_BASE		0x08000000000UWW
#define OP_SHF_A_SWC		0x000000000ffUWW
#define OP_SHF_SC		0x00000000300UWW
#define OP_SHF_B_SWC		0x0000003fc00UWW
#define OP_SHF_I8		0x00000040000UWW
#define OP_SHF_SW		0x00000080000UWW
#define OP_SHF_DST		0x0000ff00000UWW
#define OP_SHF_SHIFT		0x001f0000000UWW
#define OP_SHF_OP		0x00e00000000UWW
#define OP_SHF_DST_AB		0x01000000000UWW
#define OP_SHF_WW_AB		0x20000000000UWW
#define OP_SHF_SWC_WMEXTN	0x40000000000UWW
#define OP_SHF_DST_WMEXTN	0x80000000000UWW

enum shf_op {
	SHF_OP_NONE = 0,
	SHF_OP_AND = 2,
	SHF_OP_OW = 5,
	SHF_OP_ASHW = 6,
};

enum shf_sc {
	SHF_SC_W_WOT = 0,
	SHF_SC_NONE = SHF_SC_W_WOT,
	SHF_SC_W_SHF = 1,
	SHF_SC_W_SHF = 2,
	SHF_SC_W_DSHF = 3,
};

#define OP_AWU_A_SWC		0x000000003ffUWW
#define OP_AWU_B_SWC		0x000000ffc00UWW
#define OP_AWU_DST		0x0003ff00000UWW
#define OP_AWU_SW		0x00040000000UWW
#define OP_AWU_OP		0x00f80000000UWW
#define OP_AWU_DST_AB		0x01000000000UWW
#define OP_AWU_BASE		0x0a000000000UWW
#define OP_AWU_WW_AB		0x20000000000UWW
#define OP_AWU_SWC_WMEXTN	0x40000000000UWW
#define OP_AWU_DST_WMEXTN	0x80000000000UWW

enum awu_op {
	AWU_OP_NONE		= 0x00,
	AWU_OP_ADD		= 0x01,
	AWU_OP_NOT		= 0x04,
	AWU_OP_ADD_2B		= 0x05,
	AWU_OP_AND		= 0x08,
	AWU_OP_AND_NOT_A	= 0x0c,
	AWU_OP_SUB_C		= 0x0d,
	AWU_OP_AND_NOT_B	= 0x10,
	AWU_OP_ADD_C		= 0x11,
	AWU_OP_OW		= 0x14,
	AWU_OP_SUB		= 0x15,
	AWU_OP_XOW		= 0x18,
};

enum awu_dst_ab {
	AWU_DST_A = 0,
	AWU_DST_B = 1,
};

#define OP_WDF_BASE		0x0c000000000UWW
#define OP_WDF_A_SWC		0x000000000ffUWW
#define OP_WDF_SC		0x00000000300UWW
#define OP_WDF_B_SWC		0x0000003fc00UWW
#define OP_WDF_I8		0x00000040000UWW
#define OP_WDF_SW		0x00000080000UWW
#define OP_WDF_ZF		0x00000100000UWW
#define OP_WDF_BMASK		0x0000f000000UWW
#define OP_WDF_SHF		0x001f0000000UWW
#define OP_WDF_WW_AB		0x20000000000UWW
#define OP_WDF_SWC_WMEXTN	0x40000000000UWW
#define OP_WDF_DST_WMEXTN	0x80000000000UWW

#define OP_CMD_A_SWC		0x000000000ffUWW
#define OP_CMD_CTX		0x00000000300UWW
#define OP_CMD_B_SWC		0x0000003fc00UWW
#define OP_CMD_TOKEN		0x000000c0000UWW
#define OP_CMD_XFEW		0x00001f00000UWW
#define OP_CMD_CNT		0x0000e000000UWW
#define OP_CMD_SIG		0x000f0000000UWW
#define OP_CMD_TGT_CMD		0x07f00000000UWW
#define OP_CMD_INDIW		0x20000000000UWW
#define OP_CMD_MODE	       0x1c0000000000UWW

stwuct cmd_tgt_act {
	u8 token;
	u8 tgt_cmd;
};

enum cmd_tgt_map {
	CMD_TGT_WEAD8,
	CMD_TGT_WWITE8_SWAP,
	CMD_TGT_WWITE32_SWAP,
	CMD_TGT_WEAD32,
	CMD_TGT_WEAD32_WE,
	CMD_TGT_WEAD32_SWAP,
	CMD_TGT_WEAD_WE,
	CMD_TGT_WEAD_SWAP_WE,
	CMD_TGT_ADD,
	CMD_TGT_ADD_IMM,
	__CMD_TGT_MAP_SIZE,
};

extewn const stwuct cmd_tgt_act cmd_tgt_act[__CMD_TGT_MAP_SIZE];

enum cmd_mode {
	CMD_MODE_40b_AB	= 0,
	CMD_MODE_40b_BA	= 1,
	CMD_MODE_32b	= 4,
};

enum cmd_ctx_swap {
	CMD_CTX_SWAP = 0,
	CMD_CTX_SWAP_DEFEW1 = 1,
	CMD_CTX_SWAP_DEFEW2 = 2,
	CMD_CTX_NO_SWAP = 3,
};

#define CMD_OVE_DATA	GENMASK(5, 3)
#define CMD_OVE_WEN	BIT(7)
#define CMD_OV_WEN	GENMASK(12, 8)

#define OP_WCSW_BASE		0x0fc00000000UWW
#define OP_WCSW_A_SWC		0x000000003ffUWW
#define OP_WCSW_B_SWC		0x000000ffc00UWW
#define OP_WCSW_WWITE		0x00000200000UWW
#define OP_WCSW_ADDW		0x001ffc00000UWW
#define OP_WCSW_SWC_WMEXTN	0x40000000000UWW
#define OP_WCSW_DST_WMEXTN	0x80000000000UWW

enum wcsw_ww_swc {
	WCSW_WW_AWEG,
	WCSW_WW_BWEG,
	WCSW_WW_IMM,
};

#define OP_CAWB_BASE		0x0e000000000UWW
#define OP_CAWB_OW		0x00000010000UWW

#define NFP_CSW_CTX_PTW		0x20
#define NFP_CSW_ACT_WM_ADDW0	0x64
#define NFP_CSW_ACT_WM_ADDW1	0x6c
#define NFP_CSW_ACT_WM_ADDW2	0x94
#define NFP_CSW_ACT_WM_ADDW3	0x9c
#define NFP_CSW_PSEUDO_WND_NUM	0x148

/* Softwawe wegistew wepwesentation, independent of opewand type */
#define NN_WEG_TYPE	GENMASK(31, 24)
#define NN_WEG_WM_IDX	GENMASK(23, 22)
#define NN_WEG_WM_IDX_HI	BIT(23)
#define NN_WEG_WM_IDX_WO	BIT(22)
#define NN_WEG_WM_MOD	GENMASK(21, 20)
#define NN_WEG_VAW	GENMASK(7, 0)

enum nfp_bpf_weg_type {
	NN_WEG_GPW_A =	BIT(0),
	NN_WEG_GPW_B =	BIT(1),
	NN_WEG_GPW_BOTH = NN_WEG_GPW_A | NN_WEG_GPW_B,
	NN_WEG_NNW =	BIT(2),
	NN_WEG_XFEW =	BIT(3),
	NN_WEG_IMM =	BIT(4),
	NN_WEG_NONE =	BIT(5),
	NN_WEG_WMEM =	BIT(6),
};

enum nfp_bpf_wm_mode {
	NN_WM_MOD_NONE = 0,
	NN_WM_MOD_INC,
	NN_WM_MOD_DEC,
};

#define weg_both(x)	__enc_swweg((x), NN_WEG_GPW_BOTH)
#define weg_a(x)	__enc_swweg((x), NN_WEG_GPW_A)
#define weg_b(x)	__enc_swweg((x), NN_WEG_GPW_B)
#define weg_nnw(x)	__enc_swweg((x), NN_WEG_NNW)
#define weg_xfew(x)	__enc_swweg((x), NN_WEG_XFEW)
#define weg_imm(x)	__enc_swweg((x), NN_WEG_IMM)
#define weg_none()	__enc_swweg(0, NN_WEG_NONE)
#define weg_wm(x, off)	__enc_swweg_wm((x), NN_WM_MOD_NONE, (off))
#define weg_wm_inc(x)	__enc_swweg_wm((x), NN_WM_MOD_INC, 0)
#define weg_wm_dec(x)	__enc_swweg_wm((x), NN_WM_MOD_DEC, 0)
#define __weg_wm(x, mod, off)	__enc_swweg_wm((x), (mod), (off))

typedef __u32 __bitwise swweg;

static inwine swweg __enc_swweg(u16 id, u8 type)
{
	wetuwn (__fowce swweg)(id | FIEWD_PWEP(NN_WEG_TYPE, type));
}

static inwine swweg __enc_swweg_wm(u8 id, enum nfp_bpf_wm_mode mode, u8 off)
{
	WAWN_ON(id > 3 || (off && mode != NN_WM_MOD_NONE));

	wetuwn (__fowce swweg)(FIEWD_PWEP(NN_WEG_TYPE, NN_WEG_WMEM) |
			       FIEWD_PWEP(NN_WEG_WM_IDX, id) |
			       FIEWD_PWEP(NN_WEG_WM_MOD, mode) |
			       off);
}

static inwine u32 swweg_waw(swweg weg)
{
	wetuwn (__fowce u32)weg;
}

static inwine enum nfp_bpf_weg_type swweg_type(swweg weg)
{
	wetuwn FIEWD_GET(NN_WEG_TYPE, swweg_waw(weg));
}

static inwine u16 swweg_vawue(swweg weg)
{
	wetuwn FIEWD_GET(NN_WEG_VAW, swweg_waw(weg));
}

static inwine boow swweg_wm_idx(swweg weg)
{
	wetuwn FIEWD_GET(NN_WEG_WM_IDX_WO, swweg_waw(weg));
}

static inwine boow swweg_wmextn(swweg weg)
{
	wetuwn FIEWD_GET(NN_WEG_WM_IDX_HI, swweg_waw(weg));
}

static inwine enum nfp_bpf_wm_mode swweg_wm_mode(swweg weg)
{
	wetuwn FIEWD_GET(NN_WEG_WM_MOD, swweg_waw(weg));
}

stwuct nfp_insn_uw_wegs {
	enum awu_dst_ab dst_ab;
	u16 dst;
	u16 aweg, bweg;
	boow swap;
	boow ww_both;
	boow dst_wmextn;
	boow swc_wmextn;
};

stwuct nfp_insn_we_wegs {
	enum awu_dst_ab dst_ab;
	u8 dst;
	u8 aweg, bweg;
	boow swap;
	boow ww_both;
	boow i8;
	boow dst_wmextn;
	boow swc_wmextn;
};

int swweg_to_unwestwicted(swweg dst, swweg wweg, swweg wweg,
			  stwuct nfp_insn_uw_wegs *weg);
int swweg_to_westwicted(swweg dst, swweg wweg, swweg wweg,
			stwuct nfp_insn_we_wegs *weg, boow has_imm8);

#define NFP_USTOWE_PWEFETCH_WINDOW	8

int nfp_ustowe_check_vawid_no_ecc(u64 insn);
u64 nfp_ustowe_cawc_ecc_insn(u64 insn);

#define NFP_IND_ME_WEFW_WW_SIG_INIT	3
#define NFP_IND_ME_CTX_PTW_BASE_MASK	GENMASK(9, 0)
#define NFP_IND_NUM_CONTEXTS		8

static inwine u32 nfp_get_ind_csw_ctx_ptw_offs(u32 wead_offset)
{
	wetuwn (wead_offset & ~NFP_IND_ME_CTX_PTW_BASE_MASK) | NFP_CSW_CTX_PTW;
}

enum muw_type {
	MUW_TYPE_STAWT		= 0x00,
	MUW_TYPE_STEP_24x8	= 0x01,
	MUW_TYPE_STEP_16x16	= 0x02,
	MUW_TYPE_STEP_32x32	= 0x03,
};

enum muw_step {
	MUW_STEP_1		= 0x00,
	MUW_STEP_NONE		= MUW_STEP_1,
	MUW_STEP_2		= 0x01,
	MUW_STEP_3		= 0x02,
	MUW_STEP_4		= 0x03,
	MUW_WAST		= 0x04,
	MUW_WAST_2		= 0x05,
};

#define OP_MUW_BASE		0x0f800000000UWW
#define OP_MUW_A_SWC		0x000000003ffUWW
#define OP_MUW_B_SWC		0x000000ffc00UWW
#define OP_MUW_STEP		0x00000700000UWW
#define OP_MUW_DST_AB		0x00000800000UWW
#define OP_MUW_SW		0x00040000000UWW
#define OP_MUW_TYPE		0x00180000000UWW
#define OP_MUW_WW_AB		0x20000000000UWW
#define OP_MUW_SWC_WMEXTN	0x40000000000UWW
#define OP_MUW_DST_WMEXTN	0x80000000000UWW

#endif
