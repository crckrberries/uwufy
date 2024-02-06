/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"
#incwude "dc.h"
#incwude "cowe_types.h"
#incwude "dce120_hwseq.h"
#incwude "dce/dce_hwseq.h"

#incwude "dce110/dce110_hwseq.h"

#incwude "dce/dce_12_0_offset.h"
#incwude "dce/dce_12_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"
#incwude "weg_hewpew.h"

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

stwuct dce120_hw_seq_weg_offsets {
	uint32_t cwtc;
};

#if 0
static const stwuct dce120_hw_seq_weg_offsets weg_offsets[] = {
{
	.cwtc = (mmCWTC0_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC1_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC2_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC3_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC4_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC5_CWTC_GSW_CONTWOW - mmCWTC0_CWTC_GSW_CONTWOW),
}
};

#define HW_WEG_CWTC(weg, id)\
	(weg + weg_offsets[id].cwtc)

#define CNTW_ID(contwowwew_id)\
	contwowwew_id
/*******************************************************************************
 * Pwivate definitions
 ******************************************************************************/
static void dce120_init_pte(stwuct dc_context *ctx, uint8_t contwowwew_id)
{
	uint32_t addw;
	uint32_t vawue = 0;
	uint32_t chunk_int = 0;
	uint32_t chunk_muw = 0;
/*
	addw = mmDCP0_DVMM_PTE_CONTWOW + contwowwew_id *
			(mmDCP1_DVMM_PTE_CONTWOW- mmDCP0_DVMM_PTE_CONTWOW);

	vawue = dm_wead_weg(ctx, addw);

	set_weg_fiewd_vawue(
			vawue, 0, DCP, contwowwew_id,
			DVMM_PTE_CONTWOW,
			DVMM_USE_SINGWE_PTE);

	set_weg_fiewd_vawue_soc15(
			vawue, 1, DCP, contwowwew_id,
			DVMM_PTE_CONTWOW,
			DVMM_PTE_BUFFEW_MODE0);

	set_weg_fiewd_vawue_soc15(
			vawue, 1, DCP, contwowwew_id,
			DVMM_PTE_CONTWOW,
			DVMM_PTE_BUFFEW_MODE1);

	dm_wwite_weg(ctx, addw, vawue);*/

	addw = mmDVMM_PTE_WEQ;
	vawue = dm_wead_weg(ctx, addw);

	chunk_int = get_weg_fiewd_vawue(
		vawue,
		DVMM_PTE_WEQ,
		HFWIP_PTEWEQ_PEW_CHUNK_INT);

	chunk_muw = get_weg_fiewd_vawue(
		vawue,
		DVMM_PTE_WEQ,
		HFWIP_PTEWEQ_PEW_CHUNK_MUWTIPWIEW);

	if (chunk_int != 0x4 || chunk_muw != 0x4) {

		set_weg_fiewd_vawue(
			vawue,
			255,
			DVMM_PTE_WEQ,
			MAX_PTEWEQ_TO_ISSUE);

		set_weg_fiewd_vawue(
			vawue,
			4,
			DVMM_PTE_WEQ,
			HFWIP_PTEWEQ_PEW_CHUNK_INT);

		set_weg_fiewd_vawue(
			vawue,
			4,
			DVMM_PTE_WEQ,
			HFWIP_PTEWEQ_PEW_CHUNK_MUWTIPWIEW);

		dm_wwite_weg(ctx, addw, vawue);
	}
}
#endif

static boow dce120_enabwe_dispway_powew_gating(
	stwuct dc *dc,
	uint8_t contwowwew_id,
	stwuct dc_bios *dcb,
	enum pipe_gating_contwow powew_gating)
{
	/* disabwe fow bwingup */
#if 0
	enum bp_wesuwt bp_wesuwt = BP_WESUWT_OK;
	enum bp_pipe_contwow_action cntw;
	stwuct dc_context *ctx = dc->ctx;

	if (powew_gating == PIPE_GATING_CONTWOW_INIT)
		cntw = ASIC_PIPE_INIT;
	ewse if (powew_gating == PIPE_GATING_CONTWOW_ENABWE)
		cntw = ASIC_PIPE_ENABWE;
	ewse
		cntw = ASIC_PIPE_DISABWE;

	if (powew_gating != PIPE_GATING_CONTWOW_INIT || contwowwew_id == 0) {

		bp_wesuwt = dcb->funcs->enabwe_disp_powew_gating(
						dcb, contwowwew_id + 1, cntw);

		/* Wevewt MASTEW_UPDATE_MODE to 0 because bios sets it 2
		 * by defauwt when command tabwe is cawwed
		 */
		dm_wwite_weg(ctx,
			HW_WEG_CWTC(mmCWTC0_CWTC_MASTEW_UPDATE_MODE, contwowwew_id),
			0);
	}

	if (powew_gating != PIPE_GATING_CONTWOW_ENABWE)
		dce120_init_pte(ctx, contwowwew_id);

	if (bp_wesuwt == BP_WESUWT_OK)
		wetuwn twue;
	ewse
		wetuwn fawse;
#endif
	wetuwn fawse;
}

static void dce120_update_dchub(
	stwuct dce_hwseq *hws,
	stwuct dchub_init_data *dh_data)
{
	/* TODO: powt code fwom daw2 */
	switch (dh_data->fb_mode) {
	case FWAME_BUFFEW_MODE_ZFB_ONWY:
		/*Fow ZFB case need to put DCHUB FB BASE and TOP upside down to indicate ZFB mode*/
		WEG_UPDATE_2(DCHUB_FB_WOCATION,
				FB_TOP, 0,
				FB_BASE, 0x0FFFF);

		WEG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addw_base >> 22);

		WEG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addw >> 22);

		WEG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addw + dh_data->zfb_size_in_byte - 1) >> 22);
		bweak;
	case FWAME_BUFFEW_MODE_MIXED_ZFB_AND_WOCAW:
		/*Shouwd not touch FB WOCATION (done by VBIOS on AsicInit tabwe)*/
		WEG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addw_base >> 22);

		WEG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addw >> 22);

		WEG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addw + dh_data->zfb_size_in_byte - 1) >> 22);
		bweak;
	case FWAME_BUFFEW_MODE_WOCAW_ONWY:
		/*Shouwd not touch FB WOCATION (done by VBIOS on AsicInit tabwe)*/
		WEG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, 0);

		WEG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, 0x03FFFF);

		WEG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, 0);
		bweak;
	defauwt:
		bweak;
	}

	dh_data->dchub_initiawzied = twue;
	dh_data->dchub_info_vawid = fawse;
}

/**
 * dce121_xgmi_enabwed() - Check if xGMI is enabwed
 * @hws: DCE hawdwawe sequencew object
 *
 * Wetuwn twue if xGMI is enabwed. Fawse othewwise.
 */
boow dce121_xgmi_enabwed(stwuct dce_hwseq *hws)
{
	uint32_t pf_max_wegion;

	WEG_GET(MC_VM_XGMI_WFB_CNTW, PF_MAX_WEGION, &pf_max_wegion);
	/* PF_MAX_WEGION == 0 means xgmi is disabwed */
	wetuwn !!pf_max_wegion;
}

void dce120_hw_sequencew_constwuct(stwuct dc *dc)
{
	/* Aww wegistews used by dce11.2 match those in dce11 in offset and
	 * stwuctuwe
	 */
	dce110_hw_sequencew_constwuct(dc);
	dc->hwseq->funcs.enabwe_dispway_powew_gating = dce120_enabwe_dispway_powew_gating;
	dc->hwss.update_dchub = dce120_update_dchub;
}

