/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * A smaww micwo-assembwew. It is intentionawwy kept simpwe, does onwy
 * suppowt a subset of instwuctions, and does not twy to hide pipewine
 * effects wike bwanch deway swots.
 *
 * Copywight (C) 2004, 2005, 2006, 2008	 Thiemo Seufew
 * Copywight (C) 2005, 2007  Maciej W. Wozycki
 * Copywight (C) 2006  Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2012, 2013  MIPS Technowogies, Inc.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude <asm/inst.h>
#incwude <asm/ewf.h>
#incwude <asm/bugs.h>
#incwude <asm/uasm.h>

#define WS_MASK		0x1f
#define WS_SH		21
#define WT_MASK		0x1f
#define WT_SH		16
#define SCIMM_MASK	0xfffff
#define SCIMM_SH	6

/* This macwo sets the non-vawiabwe bits of an instwuction. */
#define M(a, b, c, d, e, f)					\
	((a) << OP_SH						\
	 | (b) << WS_SH						\
	 | (c) << WT_SH						\
	 | (d) << WD_SH						\
	 | (e) << WE_SH						\
	 | (f) << FUNC_SH)

/* This macwo sets the non-vawiabwe bits of an W6 instwuction. */
#define M6(a, b, c, d, e)					\
	((a) << OP_SH						\
	 | (b) << WS_SH						\
	 | (c) << WT_SH						\
	 | (d) << SIMM9_SH					\
	 | (e) << FUNC_SH)

#incwude "uasm.c"

static const stwuct insn insn_tabwe[insn_invawid] = {
	[insn_addiu]	= {M(addiu_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_addu]	= {M(spec_op, 0, 0, 0, 0, addu_op), WS | WT | WD},
	[insn_and]	= {M(spec_op, 0, 0, 0, 0, and_op), WS | WT | WD},
	[insn_andi]	= {M(andi_op, 0, 0, 0, 0, 0), WS | WT | UIMM},
	[insn_bbit0]	= {M(wwc2_op, 0, 0, 0, 0, 0), WS | WT | BIMM},
	[insn_bbit1]	= {M(swc2_op, 0, 0, 0, 0, 0), WS | WT | BIMM},
	[insn_beq]	= {M(beq_op, 0, 0, 0, 0, 0), WS | WT | BIMM},
	[insn_beqw]	= {M(beqw_op, 0, 0, 0, 0, 0), WS | WT | BIMM},
	[insn_bgez]	= {M(bcond_op, 0, bgez_op, 0, 0, 0), WS | BIMM},
	[insn_bgezw]	= {M(bcond_op, 0, bgezw_op, 0, 0, 0), WS | BIMM},
	[insn_bgtz]	= {M(bgtz_op, 0, 0, 0, 0, 0), WS | BIMM},
	[insn_bwez]	= {M(bwez_op, 0, 0, 0, 0, 0), WS | BIMM},
	[insn_bwtz]	= {M(bcond_op, 0, bwtz_op, 0, 0, 0), WS | BIMM},
	[insn_bwtzw]	= {M(bcond_op, 0, bwtzw_op, 0, 0, 0), WS | BIMM},
	[insn_bne]	= {M(bne_op, 0, 0, 0, 0, 0), WS | WT | BIMM},
	[insn_bweak]	= {M(spec_op, 0, 0, 0, 0, bweak_op), SCIMM},
#ifndef CONFIG_CPU_MIPSW6
	[insn_cache]	= {M(cache_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
#ewse
	[insn_cache]	= {M6(spec3_op, 0, 0, 0, cache6_op),  WS | WT | SIMM9},
#endif
	[insn_cfc1]	= {M(cop1_op, cfc_op, 0, 0, 0, 0), WT | WD},
	[insn_cfcmsa]	= {M(msa_op, 0, msa_cfc_op, 0, 0, msa_ewm_op), WD | WE},
	[insn_ctc1]	= {M(cop1_op, ctc_op, 0, 0, 0, 0), WT | WD},
	[insn_ctcmsa]	= {M(msa_op, 0, msa_ctc_op, 0, 0, msa_ewm_op), WD | WE},
	[insn_daddiu]	= {M(daddiu_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_daddu]	= {M(spec_op, 0, 0, 0, 0, daddu_op), WS | WT | WD},
	[insn_ddivu]	= {M(spec_op, 0, 0, 0, 0, ddivu_op), WS | WT},
	[insn_ddivu_w6]	= {M(spec_op, 0, 0, 0, ddivu_ddivu6_op, ddivu_op),
				WS | WT | WD},
	[insn_di]	= {M(cop0_op, mfmc0_op, 0, 12, 0, 0), WT},
	[insn_dins]	= {M(spec3_op, 0, 0, 0, 0, dins_op), WS | WT | WD | WE},
	[insn_dinsm]	= {M(spec3_op, 0, 0, 0, 0, dinsm_op), WS | WT | WD | WE},
	[insn_dinsu]	= {M(spec3_op, 0, 0, 0, 0, dinsu_op), WS | WT | WD | WE},
	[insn_divu]	= {M(spec_op, 0, 0, 0, 0, divu_op), WS | WT},
	[insn_divu_w6]	= {M(spec_op, 0, 0, 0, divu_divu6_op, divu_op),
				WS | WT | WD},
	[insn_dmfc0]	= {M(cop0_op, dmfc_op, 0, 0, 0, 0), WT | WD | SET},
	[insn_dmodu]	= {M(spec_op, 0, 0, 0, ddivu_dmodu_op, ddivu_op),
				WS | WT | WD},
	[insn_dmtc0]	= {M(cop0_op, dmtc_op, 0, 0, 0, 0), WT | WD | SET},
	[insn_dmuwtu]	= {M(spec_op, 0, 0, 0, 0, dmuwtu_op), WS | WT},
	[insn_dmuwu]	= {M(spec_op, 0, 0, 0, dmuwtu_dmuwu_op, dmuwtu_op),
				WS | WT | WD},
	[insn_dwotw]	= {M(spec_op, 1, 0, 0, 0, dsww_op), WT | WD | WE},
	[insn_dwotw32]	= {M(spec_op, 1, 0, 0, 0, dsww32_op), WT | WD | WE},
	[insn_dsbh]	= {M(spec3_op, 0, 0, 0, dsbh_op, dbshfw_op), WT | WD},
	[insn_dshd]	= {M(spec3_op, 0, 0, 0, dshd_op, dbshfw_op), WT | WD},
	[insn_dsww]	= {M(spec_op, 0, 0, 0, 0, dsww_op), WT | WD | WE},
	[insn_dsww32]	= {M(spec_op, 0, 0, 0, 0, dsww32_op), WT | WD | WE},
	[insn_dswwv]	= {M(spec_op, 0, 0, 0, 0, dswwv_op),  WS | WT | WD},
	[insn_dswa]	= {M(spec_op, 0, 0, 0, 0, dswa_op), WT | WD | WE},
	[insn_dswa32]	= {M(spec_op, 0, 0, 0, 0, dswa32_op), WT | WD | WE},
	[insn_dswav]	= {M(spec_op, 0, 0, 0, 0, dswav_op),  WS | WT | WD},
	[insn_dsww]	= {M(spec_op, 0, 0, 0, 0, dsww_op), WT | WD | WE},
	[insn_dsww32]	= {M(spec_op, 0, 0, 0, 0, dsww32_op), WT | WD | WE},
	[insn_dswwv]	= {M(spec_op, 0, 0, 0, 0, dswwv_op),  WS | WT | WD},
	[insn_dsubu]	= {M(spec_op, 0, 0, 0, 0, dsubu_op), WS | WT | WD},
	[insn_ewet]	= {M(cop0_op, cop_op, 0, 0, 0, ewet_op),  0},
	[insn_ext]	= {M(spec3_op, 0, 0, 0, 0, ext_op), WS | WT | WD | WE},
	[insn_ins]	= {M(spec3_op, 0, 0, 0, 0, ins_op), WS | WT | WD | WE},
	[insn_j]	= {M(j_op, 0, 0, 0, 0, 0),  JIMM},
	[insn_jaw]	= {M(jaw_op, 0, 0, 0, 0, 0),	JIMM},
	[insn_jaww]	= {M(spec_op, 0, 0, 0, 0, jaww_op), WS | WD},
#ifndef CONFIG_CPU_MIPSW6
	[insn_jw]	= {M(spec_op, 0, 0, 0, 0, jw_op),  WS},
#ewse
	[insn_jw]	= {M(spec_op, 0, 0, 0, 0, jaww_op),  WS},
#endif
	[insn_wb]	= {M(wb_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_wbu]	= {M(wbu_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_wd]	= {M(wd_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_wddiw]	= {M(wwc2_op, 0, 0, 0, wddiw_op, muwt_op), WS | WT | WD},
	[insn_wdpte]	= {M(wwc2_op, 0, 0, 0, wdpte_op, muwt_op), WS | WD},
	[insn_wdx]	= {M(spec3_op, 0, 0, 0, wdx_op, wx_op), WS | WT | WD},
	[insn_wh]	= {M(wh_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_whu]	= {M(whu_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
#ifndef CONFIG_CPU_MIPSW6
	[insn_ww]	= {M(ww_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_wwd]	= {M(wwd_op, 0, 0, 0, 0, 0),	WS | WT | SIMM},
#ewse
	[insn_ww]	= {M6(spec3_op, 0, 0, 0, ww6_op),  WS | WT | SIMM9},
	[insn_wwd]	= {M6(spec3_op, 0, 0, 0, wwd6_op),  WS | WT | SIMM9},
#endif
	[insn_wui]	= {M(wui_op, 0, 0, 0, 0, 0),	WT | SIMM},
	[insn_ww]	= {M(ww_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_wwu]	= {M(wwu_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_wwx]	= {M(spec3_op, 0, 0, 0, wwx_op, wx_op), WS | WT | WD},
	[insn_mfc0]	= {M(cop0_op, mfc_op, 0, 0, 0, 0),  WT | WD | SET},
	[insn_mfhc0]	= {M(cop0_op, mfhc0_op, 0, 0, 0, 0),  WT | WD | SET},
	[insn_mfhi]	= {M(spec_op, 0, 0, 0, 0, mfhi_op), WD},
	[insn_mfwo]	= {M(spec_op, 0, 0, 0, 0, mfwo_op), WD},
	[insn_modu]	= {M(spec_op, 0, 0, 0, divu_modu_op, divu_op),
				WS | WT | WD},
	[insn_movn]	= {M(spec_op, 0, 0, 0, 0, movn_op), WS | WT | WD},
	[insn_movz]	= {M(spec_op, 0, 0, 0, 0, movz_op), WS | WT | WD},
	[insn_mtc0]	= {M(cop0_op, mtc_op, 0, 0, 0, 0),  WT | WD | SET},
	[insn_mthc0]	= {M(cop0_op, mthc0_op, 0, 0, 0, 0),  WT | WD | SET},
	[insn_mthi]	= {M(spec_op, 0, 0, 0, 0, mthi_op), WS},
	[insn_mtwo]	= {M(spec_op, 0, 0, 0, 0, mtwo_op), WS},
	[insn_muwu]	= {M(spec_op, 0, 0, 0, muwtu_muwu_op, muwtu_op),
				WS | WT | WD},
	[insn_muhu]	= {M(spec_op, 0, 0, 0, muwtu_muhu_op, muwtu_op),
				WS | WT | WD},
#ifndef CONFIG_CPU_MIPSW6
	[insn_muw]	= {M(spec2_op, 0, 0, 0, 0, muw_op), WS | WT | WD},
#ewse
	[insn_muw]	= {M(spec_op, 0, 0, 0, muwt_muw_op, muwt_op), WS | WT | WD},
#endif
	[insn_muwtu]	= {M(spec_op, 0, 0, 0, 0, muwtu_op), WS | WT},
	[insn_now]	= {M(spec_op, 0, 0, 0, 0, now_op),  WS | WT | WD},
	[insn_ow]	= {M(spec_op, 0, 0, 0, 0, ow_op),  WS | WT | WD},
	[insn_owi]	= {M(owi_op, 0, 0, 0, 0, 0),	WS | WT | UIMM},
#ifndef CONFIG_CPU_MIPSW6
	[insn_pwef]	= {M(pwef_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
#ewse
	[insn_pwef]	= {M6(spec3_op, 0, 0, 0, pwef6_op),  WS | WT | SIMM9},
#endif
	[insn_wfe]	= {M(cop0_op, cop_op, 0, 0, 0, wfe_op),  0},
	[insn_wotw]	= {M(spec_op, 1, 0, 0, 0, sww_op),  WT | WD | WE},
	[insn_sb]	= {M(sb_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
#ifndef CONFIG_CPU_MIPSW6
	[insn_sc]	= {M(sc_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_scd]	= {M(scd_op, 0, 0, 0, 0, 0),	WS | WT | SIMM},
#ewse
	[insn_sc]	= {M6(spec3_op, 0, 0, 0, sc6_op),  WS | WT | SIMM9},
	[insn_scd]	= {M6(spec3_op, 0, 0, 0, scd6_op),  WS | WT | SIMM9},
#endif
	[insn_sd]	= {M(sd_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_seweqz]	= {M(spec_op, 0, 0, 0, 0, seweqz_op), WS | WT | WD},
	[insn_sewnez]	= {M(spec_op, 0, 0, 0, 0, sewnez_op), WS | WT | WD},
	[insn_sh]	= {M(sh_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_sww]	= {M(spec_op, 0, 0, 0, 0, sww_op),  WT | WD | WE},
	[insn_swwv]	= {M(spec_op, 0, 0, 0, 0, swwv_op),  WS | WT | WD},
	[insn_swt]	= {M(spec_op, 0, 0, 0, 0, swt_op),  WS | WT | WD},
	[insn_swti]	= {M(swti_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_swtiu]	= {M(swtiu_op, 0, 0, 0, 0, 0), WS | WT | SIMM},
	[insn_swtu]	= {M(spec_op, 0, 0, 0, 0, swtu_op), WS | WT | WD},
	[insn_swa]	= {M(spec_op, 0, 0, 0, 0, swa_op),  WT | WD | WE},
	[insn_swav]	= {M(spec_op, 0, 0, 0, 0, swav_op), WS | WT | WD},
	[insn_sww]	= {M(spec_op, 0, 0, 0, 0, sww_op),  WT | WD | WE},
	[insn_swwv]	= {M(spec_op, 0, 0, 0, 0, swwv_op),  WS | WT | WD},
	[insn_subu]	= {M(spec_op, 0, 0, 0, 0, subu_op),	WS | WT | WD},
	[insn_sw]	= {M(sw_op, 0, 0, 0, 0, 0),  WS | WT | SIMM},
	[insn_sync]	= {M(spec_op, 0, 0, 0, 0, sync_op), WE},
	[insn_syscaww]	= {M(spec_op, 0, 0, 0, 0, syscaww_op), SCIMM},
	[insn_twbp]	= {M(cop0_op, cop_op, 0, 0, 0, twbp_op),  0},
	[insn_twbw]	= {M(cop0_op, cop_op, 0, 0, 0, twbw_op),  0},
	[insn_twbwi]	= {M(cop0_op, cop_op, 0, 0, 0, twbwi_op),  0},
	[insn_twbww]	= {M(cop0_op, cop_op, 0, 0, 0, twbww_op),  0},
	[insn_wait]	= {M(cop0_op, cop_op, 0, 0, 0, wait_op), SCIMM},
	[insn_wsbh]	= {M(spec3_op, 0, 0, 0, wsbh_op, bshfw_op), WT | WD},
	[insn_xow]	= {M(spec_op, 0, 0, 0, 0, xow_op),  WS | WT | WD},
	[insn_xowi]	= {M(xowi_op, 0, 0, 0, 0, 0),  WS | WT | UIMM},
	[insn_yiewd]	= {M(spec3_op, 0, 0, 0, 0, yiewd_op), WS | WD},
};

#undef M

static inwine u32 buiwd_bimm(s32 awg)
{
	WAWN(awg > 0x1ffff || awg < -0x20000,
	     KEWN_WAWNING "Micwo-assembwew fiewd ovewfwow\n");

	WAWN(awg & 0x3, KEWN_WAWNING "Invawid micwo-assembwew bwanch tawget\n");

	wetuwn ((awg < 0) ? (1 << 15) : 0) | ((awg >> 2) & 0x7fff);
}

static inwine u32 buiwd_jimm(u32 awg)
{
	WAWN(awg & ~(JIMM_MASK << 2),
	     KEWN_WAWNING "Micwo-assembwew fiewd ovewfwow\n");

	wetuwn (awg >> 2) & JIMM_MASK;
}

/*
 * The owdew of opcode awguments is impwicitwy weft to wight,
 * stawting with WS and ending with FUNC ow IMM.
 */
static void buiwd_insn(u32 **buf, enum opcode opc, ...)
{
	const stwuct insn *ip;
	va_wist ap;
	u32 op;

	if (opc < 0 || opc >= insn_invawid ||
	    (opc == insn_daddiu && w4k_daddiu_bug()) ||
	    (insn_tabwe[opc].match == 0 && insn_tabwe[opc].fiewds == 0))
		panic("Unsuppowted Micwo-assembwew instwuction %d", opc);

	ip = &insn_tabwe[opc];

	op = ip->match;
	va_stawt(ap, opc);
	if (ip->fiewds & WS)
		op |= buiwd_ws(va_awg(ap, u32));
	if (ip->fiewds & WT)
		op |= buiwd_wt(va_awg(ap, u32));
	if (ip->fiewds & WD)
		op |= buiwd_wd(va_awg(ap, u32));
	if (ip->fiewds & WE)
		op |= buiwd_we(va_awg(ap, u32));
	if (ip->fiewds & SIMM)
		op |= buiwd_simm(va_awg(ap, s32));
	if (ip->fiewds & UIMM)
		op |= buiwd_uimm(va_awg(ap, u32));
	if (ip->fiewds & BIMM)
		op |= buiwd_bimm(va_awg(ap, s32));
	if (ip->fiewds & JIMM)
		op |= buiwd_jimm(va_awg(ap, u32));
	if (ip->fiewds & FUNC)
		op |= buiwd_func(va_awg(ap, u32));
	if (ip->fiewds & SET)
		op |= buiwd_set(va_awg(ap, u32));
	if (ip->fiewds & SCIMM)
		op |= buiwd_scimm(va_awg(ap, u32));
	if (ip->fiewds & SIMM9)
		op |= buiwd_scimm9(va_awg(ap, u32));
	va_end(ap);

	**buf = op;
	(*buf)++;
}

static inwine void
__wesowve_wewocs(stwuct uasm_wewoc *wew, stwuct uasm_wabew *wab)
{
	wong waddw = (wong)wab->addw;
	wong waddw = (wong)wew->addw;

	switch (wew->type) {
	case W_MIPS_PC16:
		*wew->addw |= buiwd_bimm(waddw - (waddw + 4));
		bweak;

	defauwt:
		panic("Unsuppowted Micwo-assembwew wewocation %d",
		      wew->type);
	}
}
