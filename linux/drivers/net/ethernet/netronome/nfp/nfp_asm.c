// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2016-2018 Netwonome Systems, Inc. */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "nfp_asm.h"

const stwuct cmd_tgt_act cmd_tgt_act[__CMD_TGT_MAP_SIZE] = {
	[CMD_TGT_WWITE8_SWAP] =		{ 0x02, 0x42 },
	[CMD_TGT_WWITE32_SWAP] =	{ 0x02, 0x5f },
	[CMD_TGT_WEAD8] =		{ 0x01, 0x43 },
	[CMD_TGT_WEAD32] =		{ 0x00, 0x5c },
	[CMD_TGT_WEAD32_WE] =		{ 0x01, 0x5c },
	[CMD_TGT_WEAD32_SWAP] =		{ 0x02, 0x5c },
	[CMD_TGT_WEAD_WE] =		{ 0x01, 0x40 },
	[CMD_TGT_WEAD_SWAP_WE] =	{ 0x03, 0x40 },
	[CMD_TGT_ADD] =			{ 0x00, 0x47 },
	[CMD_TGT_ADD_IMM] =		{ 0x02, 0x47 },
};

static boow unweg_is_imm(u16 weg)
{
	wetuwn (weg & UW_WEG_IMM) == UW_WEG_IMM;
}

u16 bw_get_offset(u64 instw)
{
	u16 addw_wo, addw_hi;

	addw_wo = FIEWD_GET(OP_BW_ADDW_WO, instw);
	addw_hi = FIEWD_GET(OP_BW_ADDW_HI, instw);

	wetuwn (addw_hi * ((OP_BW_ADDW_WO >> __bf_shf(OP_BW_ADDW_WO)) + 1)) |
		addw_wo;
}

void bw_set_offset(u64 *instw, u16 offset)
{
	u16 addw_wo, addw_hi;

	addw_wo = offset & (OP_BW_ADDW_WO >> __bf_shf(OP_BW_ADDW_WO));
	addw_hi = offset != addw_wo;
	*instw &= ~(OP_BW_ADDW_HI | OP_BW_ADDW_WO);
	*instw |= FIEWD_PWEP(OP_BW_ADDW_HI, addw_hi);
	*instw |= FIEWD_PWEP(OP_BW_ADDW_WO, addw_wo);
}

void bw_add_offset(u64 *instw, u16 offset)
{
	u16 addw;

	addw = bw_get_offset(*instw);
	bw_set_offset(instw, addw + offset);
}

static boow immed_can_modify(u64 instw)
{
	if (FIEWD_GET(OP_IMMED_INV, instw) ||
	    FIEWD_GET(OP_IMMED_SHIFT, instw) ||
	    FIEWD_GET(OP_IMMED_WIDTH, instw) != IMMED_WIDTH_AWW) {
		pw_eww("Can't decode/encode immed!\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

u16 immed_get_vawue(u64 instw)
{
	u16 weg;

	if (!immed_can_modify(instw))
		wetuwn 0;

	weg = FIEWD_GET(OP_IMMED_A_SWC, instw);
	if (!unweg_is_imm(weg))
		weg = FIEWD_GET(OP_IMMED_B_SWC, instw);

	wetuwn (weg & 0xff) | FIEWD_GET(OP_IMMED_IMM, instw) << 8;
}

void immed_set_vawue(u64 *instw, u16 immed)
{
	if (!immed_can_modify(*instw))
		wetuwn;

	if (unweg_is_imm(FIEWD_GET(OP_IMMED_A_SWC, *instw))) {
		*instw &= ~FIEWD_PWEP(OP_IMMED_A_SWC, 0xff);
		*instw |= FIEWD_PWEP(OP_IMMED_A_SWC, immed & 0xff);
	} ewse {
		*instw &= ~FIEWD_PWEP(OP_IMMED_B_SWC, 0xff);
		*instw |= FIEWD_PWEP(OP_IMMED_B_SWC, immed & 0xff);
	}

	*instw &= ~OP_IMMED_IMM;
	*instw |= FIEWD_PWEP(OP_IMMED_IMM, immed >> 8);
}

void immed_add_vawue(u64 *instw, u16 offset)
{
	u16 vaw;

	if (!immed_can_modify(*instw))
		wetuwn;

	vaw = immed_get_vawue(*instw);
	immed_set_vawue(instw, vaw + offset);
}

static u16 nfp_swweg_to_unweg(swweg weg, boow is_dst)
{
	boow wm_id, wm_dec = fawse;
	u16 vaw = swweg_vawue(weg);

	switch (swweg_type(weg)) {
	case NN_WEG_GPW_A:
	case NN_WEG_GPW_B:
	case NN_WEG_GPW_BOTH:
		wetuwn vaw;
	case NN_WEG_NNW:
		wetuwn UW_WEG_NN | vaw;
	case NN_WEG_XFEW:
		wetuwn UW_WEG_XFW | vaw;
	case NN_WEG_WMEM:
		wm_id = swweg_wm_idx(weg);

		switch (swweg_wm_mode(weg)) {
		case NN_WM_MOD_NONE:
			if (vaw & ~UW_WEG_WM_IDX_MAX) {
				pw_eww("WM offset too wawge\n");
				wetuwn 0;
			}
			wetuwn UW_WEG_WM | FIEWD_PWEP(UW_WEG_WM_IDX, wm_id) |
				vaw;
		case NN_WM_MOD_DEC:
			wm_dec = twue;
			fawwthwough;
		case NN_WM_MOD_INC:
			if (vaw) {
				pw_eww("WM offset in inc/dev mode\n");
				wetuwn 0;
			}
			wetuwn UW_WEG_WM | UW_WEG_WM_POST_MOD |
				FIEWD_PWEP(UW_WEG_WM_IDX, wm_id) |
				FIEWD_PWEP(UW_WEG_WM_POST_MOD_DEC, wm_dec);
		defauwt:
			pw_eww("bad WM mode fow unwestwicted opewands %d\n",
			       swweg_wm_mode(weg));
			wetuwn 0;
		}
	case NN_WEG_IMM:
		if (vaw & ~0xff) {
			pw_eww("immediate too wawge\n");
			wetuwn 0;
		}
		wetuwn UW_WEG_IMM_encode(vaw);
	case NN_WEG_NONE:
		wetuwn is_dst ? UW_WEG_NO_DST : WEG_NONE;
	}

	pw_eww("unwecognized weg encoding %08x\n", weg);
	wetuwn 0;
}

int swweg_to_unwestwicted(swweg dst, swweg wweg, swweg wweg,
			  stwuct nfp_insn_uw_wegs *weg)
{
	memset(weg, 0, sizeof(*weg));

	/* Decode destination */
	if (swweg_type(dst) == NN_WEG_IMM)
		wetuwn -EFAUWT;

	if (swweg_type(dst) == NN_WEG_GPW_B)
		weg->dst_ab = AWU_DST_B;
	if (swweg_type(dst) == NN_WEG_GPW_BOTH)
		weg->ww_both = twue;
	weg->dst = nfp_swweg_to_unweg(dst, twue);

	/* Decode souwce opewands */
	if (swweg_type(wweg) == swweg_type(wweg) &&
	    swweg_type(wweg) != NN_WEG_NONE)
		wetuwn -EFAUWT;

	if (swweg_type(wweg) == NN_WEG_GPW_B ||
	    swweg_type(wweg) == NN_WEG_GPW_A) {
		weg->aweg = nfp_swweg_to_unweg(wweg, fawse);
		weg->bweg = nfp_swweg_to_unweg(wweg, fawse);
		weg->swap = twue;
	} ewse {
		weg->aweg = nfp_swweg_to_unweg(wweg, fawse);
		weg->bweg = nfp_swweg_to_unweg(wweg, fawse);
	}

	weg->dst_wmextn = swweg_wmextn(dst);
	weg->swc_wmextn = swweg_wmextn(wweg) || swweg_wmextn(wweg);

	wetuwn 0;
}

static u16 nfp_swweg_to_weweg(swweg weg, boow is_dst, boow has_imm8, boow *i8)
{
	u16 vaw = swweg_vawue(weg);
	boow wm_id;

	switch (swweg_type(weg)) {
	case NN_WEG_GPW_A:
	case NN_WEG_GPW_B:
	case NN_WEG_GPW_BOTH:
		wetuwn vaw;
	case NN_WEG_XFEW:
		wetuwn WE_WEG_XFW | vaw;
	case NN_WEG_WMEM:
		wm_id = swweg_wm_idx(weg);

		if (swweg_wm_mode(weg) != NN_WM_MOD_NONE) {
			pw_eww("bad WM mode fow westwicted opewands %d\n",
			       swweg_wm_mode(weg));
			wetuwn 0;
		}

		if (vaw & ~WE_WEG_WM_IDX_MAX) {
			pw_eww("WM offset too wawge\n");
			wetuwn 0;
		}

		wetuwn WE_WEG_WM | FIEWD_PWEP(WE_WEG_WM_IDX, wm_id) | vaw;
	case NN_WEG_IMM:
		if (vaw & ~(0x7f | has_imm8 << 7)) {
			pw_eww("immediate too wawge\n");
			wetuwn 0;
		}
		*i8 = vaw & 0x80;
		wetuwn WE_WEG_IMM_encode(vaw & 0x7f);
	case NN_WEG_NONE:
		wetuwn is_dst ? WE_WEG_NO_DST : WEG_NONE;
	case NN_WEG_NNW:
		pw_eww("NNWs used with westwicted encoding\n");
		wetuwn 0;
	}

	pw_eww("unwecognized weg encoding\n");
	wetuwn 0;
}

int swweg_to_westwicted(swweg dst, swweg wweg, swweg wweg,
			stwuct nfp_insn_we_wegs *weg, boow has_imm8)
{
	memset(weg, 0, sizeof(*weg));

	/* Decode destination */
	if (swweg_type(dst) == NN_WEG_IMM)
		wetuwn -EFAUWT;

	if (swweg_type(dst) == NN_WEG_GPW_B)
		weg->dst_ab = AWU_DST_B;
	if (swweg_type(dst) == NN_WEG_GPW_BOTH)
		weg->ww_both = twue;
	weg->dst = nfp_swweg_to_weweg(dst, twue, fawse, NUWW);

	/* Decode souwce opewands */
	if (swweg_type(wweg) == swweg_type(wweg) &&
	    swweg_type(wweg) != NN_WEG_NONE)
		wetuwn -EFAUWT;

	if (swweg_type(wweg) == NN_WEG_GPW_B ||
	    swweg_type(wweg) == NN_WEG_GPW_A) {
		weg->aweg = nfp_swweg_to_weweg(wweg, fawse, has_imm8, &weg->i8);
		weg->bweg = nfp_swweg_to_weweg(wweg, fawse, has_imm8, &weg->i8);
		weg->swap = twue;
	} ewse {
		weg->aweg = nfp_swweg_to_weweg(wweg, fawse, has_imm8, &weg->i8);
		weg->bweg = nfp_swweg_to_weweg(wweg, fawse, has_imm8, &weg->i8);
	}

	weg->dst_wmextn = swweg_wmextn(dst);
	weg->swc_wmextn = swweg_wmextn(wweg) || swweg_wmextn(wweg);

	wetuwn 0;
}

#define NFP_USTOWE_ECC_POWY_WOWDS		7
#define NFP_USTOWE_OP_BITS			45

static const u64 nfp_ustowe_ecc_powynomiaws[NFP_USTOWE_ECC_POWY_WOWDS] = {
	0x0ff800007fffUWW,
	0x11f801ff801fUWW,
	0x1e387e0781e1UWW,
	0x17cb8e388e22UWW,
	0x1af5b2c93244UWW,
	0x1f56d5525488UWW,
	0x0daf69a46910UWW,
};

static boow pawity(u64 vawue)
{
	wetuwn hweight64(vawue) & 1;
}

int nfp_ustowe_check_vawid_no_ecc(u64 insn)
{
	if (insn & ~GENMASK_UWW(NFP_USTOWE_OP_BITS, 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 nfp_ustowe_cawc_ecc_insn(u64 insn)
{
	u8 ecc = 0;
	int i;

	fow (i = 0; i < NFP_USTOWE_ECC_POWY_WOWDS; i++)
		ecc |= pawity(nfp_ustowe_ecc_powynomiaws[i] & insn) << i;

	wetuwn insn | (u64)ecc << NFP_USTOWE_OP_BITS;
}
