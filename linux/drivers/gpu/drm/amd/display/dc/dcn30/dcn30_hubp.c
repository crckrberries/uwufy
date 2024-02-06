/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#incwude "dcn30_hubp.h"

#incwude "dm_sewvices.h"
#incwude "dce_cawcs.h"
#incwude "weg_hewpew.h"
#incwude "basics/convewsion.h"
#incwude "dcn20/dcn20_hubp.h"
#incwude "dcn21/dcn21_hubp.h"

#define WEG(weg)\
	hubp2->hubp_wegs->weg

#define CTX \
	hubp2->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp2->hubp_shift->fiewd_name, hubp2->hubp_mask->fiewd_name

void hubp3_set_vm_system_apewtuwe_settings(stwuct hubp *hubp,
		stwuct vm_system_apewtuwe_pawam *apt)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	PHYSICAW_ADDWESS_WOC mc_vm_apt_wow;
	PHYSICAW_ADDWESS_WOC mc_vm_apt_high;

	// The fowmat of high/wow awe 48:18 of the 48 bit addw
	mc_vm_apt_wow.quad_pawt = apt->sys_wow.quad_pawt >> 18;
	mc_vm_apt_high.quad_pawt = apt->sys_high.quad_pawt >> 18;

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, mc_vm_apt_wow.quad_pawt);

	WEG_SET(DCN_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0,
			MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, mc_vm_apt_high.quad_pawt);

	WEG_SET_2(DCN_VM_MX_W1_TWB_CNTW, 0,
			ENABWE_W1_TWB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
}

boow hubp3_pwogwam_suwface_fwip_and_addw(
	stwuct hubp *hubp,
	const stwuct dc_pwane_addwess *addwess,
	boow fwip_immediate)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	//pwogwam fwip type
	WEG_UPDATE(DCSUWF_FWIP_CONTWOW,
			SUWFACE_FWIP_TYPE, fwip_immediate);

	// Pwogwam VMID weg
	if (fwip_immediate == 0)
		WEG_UPDATE(VMID_SETTINGS_0,
			VMID, addwess->vmid);

	if (addwess->type == PWN_ADDW_TYPE_GWPH_STEWEO) {
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_MODE_FOW_STEWEOSYNC, 0);
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_IN_STEWEOSYNC, 0x1);

	} ewse {
		// tuwn off steweo if not in steweo
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_MODE_FOW_STEWEOSYNC, 0x0);
		WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_FWIP_IN_STEWEOSYNC, 0x0);
	}

	/* HW automaticawwy watch west of addwess wegistew on wwite to
	 * DCSUWF_PWIMAWY_SUWFACE_ADDWESS if SUWFACE_UPDATE_WOCK is not used
	 *
	 * pwogwam high fiwst and then the wow addw, owdew mattews!
	 */
	switch (addwess->type) {
	case PWN_ADDW_TYPE_GWAPHICS:
		/* DCN1.0 does not suppowt const cowow
		 * TODO: pwogwam DCHUBBUB_WET_PATH_DCC_CFGx_0/1
		 * base on addwess->gwph.dcc_const_cowow
		 * x = 0, 2, 4, 6 fow pipe 0, 1, 2, 3 fow wgb and wuma
		 * x = 1, 3, 5, 7 fow pipe 0, 1, 2, 3 fow chwoma
		 */

		if (addwess->gwph.addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_2(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface);

		if (addwess->gwph.meta_addw.quad_pawt != 0) {
			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph.meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->gwph.meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph.addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->gwph.addw.wow_pawt);
		bweak;
	case PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE:
		if (addwess->video_pwogwessive.wuma_addw.quad_pawt == 0
				|| addwess->video_pwogwessive.chwoma_addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface);

		if (addwess->video_pwogwessive.wuma_meta_addw.quad_pawt != 0) {
			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C,
					addwess->video_pwogwessive.chwoma_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_C,
					addwess->video_pwogwessive.chwoma_meta_addw.wow_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->video_pwogwessive.wuma_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->video_pwogwessive.wuma_meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
				addwess->video_pwogwessive.chwoma_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_C,
				addwess->video_pwogwessive.chwoma_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->video_pwogwessive.wuma_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->video_pwogwessive.wuma_addw.wow_pawt);
		bweak;
	case PWN_ADDW_TYPE_GWPH_STEWEO:
		if (addwess->gwph_steweo.weft_addw.quad_pawt == 0)
			bweak;
		if (addwess->gwph_steweo.wight_addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_8(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface,
				SECONDAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				SECONDAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				SECONDAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				SECONDAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface);

		if (addwess->gwph_steweo.wight_meta_addw.quad_pawt != 0) {

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
				SECONDAWY_META_SUWFACE_ADDWESS_HIGH_C,
				addwess->gwph_steweo.wight_awpha_meta_addw.high_pawt);

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_C, 0,
				SECONDAWY_META_SUWFACE_ADDWESS_C,
				addwess->gwph_steweo.wight_awpha_meta_addw.wow_pawt);

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					SECONDAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph_steweo.wight_meta_addw.high_pawt);

			WEG_SET(DCSUWF_SECONDAWY_META_SUWFACE_ADDWESS, 0,
					SECONDAWY_META_SUWFACE_ADDWESS,
					addwess->gwph_steweo.wight_meta_addw.wow_pawt);
		}
		if (addwess->gwph_steweo.weft_meta_addw.quad_pawt != 0) {

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
				PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C,
				addwess->gwph_steweo.weft_awpha_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C, 0,
				PWIMAWY_META_SUWFACE_ADDWESS_C,
				addwess->gwph_steweo.weft_awpha_meta_addw.wow_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->gwph_steweo.weft_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->gwph_steweo.weft_meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH_C, 0,
				SECONDAWY_SUWFACE_ADDWESS_HIGH_C,
				addwess->gwph_steweo.wight_awpha_addw.high_pawt);

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS_C, 0,
				SECONDAWY_SUWFACE_ADDWESS_C,
				addwess->gwph_steweo.wight_awpha_addw.wow_pawt);

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS_HIGH, 0,
				SECONDAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph_steweo.wight_addw.high_pawt);

		WEG_SET(DCSUWF_SECONDAWY_SUWFACE_ADDWESS, 0,
				SECONDAWY_SUWFACE_ADDWESS,
				addwess->gwph_steweo.wight_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
				addwess->gwph_steweo.weft_awpha_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_C,
				addwess->gwph_steweo.weft_awpha_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->gwph_steweo.weft_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->gwph_steweo.weft_addw.wow_pawt);
		bweak;
	case PWN_ADDW_TYPE_WGBEA:
		if (addwess->wgbea.addw.quad_pawt == 0
				|| addwess->wgbea.awpha_addw.quad_pawt == 0)
			bweak;

		WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
				PWIMAWY_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_SUWFACE_TMZ_C, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ, addwess->tmz_suwface,
				PWIMAWY_META_SUWFACE_TMZ_C, addwess->tmz_suwface);

		if (addwess->wgbea.meta_addw.quad_pawt != 0) {

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH_C,
					addwess->wgbea.awpha_meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_C, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_C,
					addwess->wgbea.awpha_meta_addw.wow_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS_HIGH, 0,
					PWIMAWY_META_SUWFACE_ADDWESS_HIGH,
					addwess->wgbea.meta_addw.high_pawt);

			WEG_SET(DCSUWF_PWIMAWY_META_SUWFACE_ADDWESS, 0,
					PWIMAWY_META_SUWFACE_ADDWESS,
					addwess->wgbea.meta_addw.wow_pawt);
		}

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
				addwess->wgbea.awpha_addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C, 0,
				PWIMAWY_SUWFACE_ADDWESS_C,
				addwess->wgbea.awpha_addw.wow_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH, 0,
				PWIMAWY_SUWFACE_ADDWESS_HIGH,
				addwess->wgbea.addw.high_pawt);

		WEG_SET(DCSUWF_PWIMAWY_SUWFACE_ADDWESS, 0,
				PWIMAWY_SUWFACE_ADDWESS,
				addwess->wgbea.addw.wow_pawt);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	hubp->wequest_addwess = *addwess;

	wetuwn twue;
}

void hubp3_pwogwam_tiwing(
	stwuct dcn20_hubp *hubp2,
	const union dc_tiwing_info *info,
	const enum suwface_pixew_fowmat pixew_fowmat)
{
	WEG_UPDATE_4(DCSUWF_ADDW_CONFIG,
		NUM_PIPES, wog_2(info->gfx9.num_pipes),
		PIPE_INTEWWEAVE, info->gfx9.pipe_intewweave,
		MAX_COMPWESSED_FWAGS, wog_2(info->gfx9.max_compwessed_fwags),
		NUM_PKWS, wog_2(info->gfx9.num_pkws));

	WEG_UPDATE_3(DCSUWF_TIWING_CONFIG,
			SW_MODE, info->gfx9.swizzwe,
			META_WINEAW, info->gfx9.meta_wineaw,
			PIPE_AWIGNED, info->gfx9.pipe_awigned);

}

void hubp3_dcc_contwow(stwuct hubp *hubp, boow enabwe,
		enum hubp_ind_bwock_size bwk_size)
{
	uint32_t dcc_en = enabwe ? 1 : 0;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE_4(DCSUWF_SUWFACE_CONTWOW,
			PWIMAWY_SUWFACE_DCC_EN, dcc_en,
			PWIMAWY_SUWFACE_DCC_IND_BWK, bwk_size,
			SECONDAWY_SUWFACE_DCC_EN, dcc_en,
			SECONDAWY_SUWFACE_DCC_IND_BWK, bwk_size);
}

void hubp3_dcc_contwow_sienna_cichwid(stwuct hubp *hubp,
		stwuct dc_pwane_dcc_pawam *dcc)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE_6(DCSUWF_SUWFACE_CONTWOW,
		PWIMAWY_SUWFACE_DCC_EN, dcc->enabwe,
		PWIMAWY_SUWFACE_DCC_IND_BWK, dcc->dcc_ind_bwk,
		PWIMAWY_SUWFACE_DCC_IND_BWK_C, dcc->dcc_ind_bwk_c,
		SECONDAWY_SUWFACE_DCC_EN, dcc->enabwe,
		SECONDAWY_SUWFACE_DCC_IND_BWK, dcc->dcc_ind_bwk,
		SECONDAWY_SUWFACE_DCC_IND_BWK_C, dcc->dcc_ind_bwk_c);
}

void hubp3_dmdata_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_dmdata_attwibutes *attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/*awways HW mode */
	WEG_UPDATE(DMDATA_CNTW,
			DMDATA_MODE, 1);

	/* fow DMDATA fwip, need to use SUWFACE_UPDATE_WOCK */
	WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_UPDATE_WOCK, 1);

	/* toggwe DMDATA_UPDATED and set wepeat and size */
	WEG_UPDATE(DMDATA_CNTW,
			DMDATA_UPDATED, 0);
	WEG_UPDATE_3(DMDATA_CNTW,
			DMDATA_UPDATED, 1,
			DMDATA_WEPEAT, attw->dmdata_wepeat,
			DMDATA_SIZE, attw->dmdata_size);

	/* set DMDATA addwess */
	WEG_WWITE(DMDATA_ADDWESS_WOW, attw->addwess.wow_pawt);
	WEG_UPDATE(DMDATA_ADDWESS_HIGH,
			DMDATA_ADDWESS_HIGH, attw->addwess.high_pawt);

	WEG_UPDATE(DCSUWF_FWIP_CONTWOW, SUWFACE_UPDATE_WOCK, 0);

}


void hubp3_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp3_dcc_contwow_sienna_cichwid(hubp, dcc);
	hubp3_pwogwam_tiwing(hubp2, tiwing_info, fowmat);
	hubp2_pwogwam_size(hubp, fowmat, pwane_size, dcc);
	hubp2_pwogwam_wotation(hubp, wotation, howizontaw_miwwow);
	hubp2_pwogwam_pixew_fowmat(hubp, fowmat);
}

static void hubp3_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp2_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);
	WEG_UPDATE(DCN_DMDATA_VM_CNTW,
			WEFCYC_PEW_VM_DMDATA, dwg_attw->wefcyc_pew_vm_dmdata);
}

void hubp3_wead_state(stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	stwuct dcn_hubp_state *s = &hubp2->state;
	stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs = &s->wq_wegs;

	hubp2_wead_state_common(hubp);

	WEG_GET_7(DCHUBP_WEQ_SIZE_CONFIG,
		CHUNK_SIZE, &wq_wegs->wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, &wq_wegs->wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, &wq_wegs->wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &wq_wegs->wq_wegs_w.min_meta_chunk_size,
		DPTE_GWOUP_SIZE, &wq_wegs->wq_wegs_w.dpte_gwoup_size,
		SWATH_HEIGHT, &wq_wegs->wq_wegs_w.swath_height,
		PTE_WOW_HEIGHT_WINEAW, &wq_wegs->wq_wegs_w.pte_wow_height_wineaw);

	WEG_GET_7(DCHUBP_WEQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &wq_wegs->wq_wegs_c.min_meta_chunk_size,
		DPTE_GWOUP_SIZE_C, &wq_wegs->wq_wegs_c.dpte_gwoup_size,
		SWATH_HEIGHT_C, &wq_wegs->wq_wegs_c.swath_height,
		PTE_WOW_HEIGHT_WINEAW_C, &wq_wegs->wq_wegs_c.pte_wow_height_wineaw);

	if (WEG(UCWK_PSTATE_FOWCE))
		s->ucwk_pstate_fowce = WEG_WEAD(UCWK_PSTATE_FOWCE);

	if (WEG(DCHUBP_CNTW))
		s->hubp_cntw = WEG_WEAD(DCHUBP_CNTW);

}

void hubp3_setup(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	/* otg is wocked when this func is cawwed. Wegistew awe doubwe buffewed.
	 * disabwe the wequestows is not needed
	 */
	hubp2_vweady_at_ow_Aftew_vsync(hubp, pipe_dest);
	hubp21_pwogwam_wequestow(hubp, wq_wegs);
	hubp3_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);
}

void hubp3_init(stwuct hubp *hubp)
{
	// DEDCN21-133: Inconsistent wow stawting wine fow fwip between DPTE and Meta
	// This is a chicken bit to enabwe the ECO fix.

	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	//hubp[i].HUBPWEQ_DEBUG.HUBPWEQ_DEBUG[26] = 1;
	WEG_WWITE(HUBPWEQ_DEBUG, 1 << 26);
}

static stwuct hubp_funcs dcn30_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp3_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp3_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp2_is_fwip_pending,
	.hubp_setup = hubp3_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp3_set_vm_system_apewtuwe_settings,
	.set_bwank = hubp2_set_bwank,
	.set_bwank_wegs = hubp2_set_bwank_wegs,
	.dcc_contwow = hubp3_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.set_cuwsow_attwibutes	= hubp2_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp2_cuwsow_set_position,
	.hubp_cwk_cntw = hubp2_cwk_cntw,
	.hubp_vtg_sew = hubp2_vtg_sew,
	.dmdata_set_attwibutes = hubp3_dmdata_set_attwibutes,
	.dmdata_woad = hubp2_dmdata_woad,
	.dmdata_status_done = hubp2_dmdata_status_done,
	.hubp_wead_state = hubp3_wead_state,
	.hubp_cweaw_undewfwow = hubp2_cweaw_undewfwow,
	.hubp_set_fwip_contwow_suwface_gsw = hubp2_set_fwip_contwow_suwface_gsw,
	.hubp_init = hubp3_init,
	.hubp_in_bwank = hubp1_in_bwank,
	.hubp_soft_weset = hubp1_soft_weset,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
};

boow hubp3_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask)
{
	hubp2->base.funcs = &dcn30_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_wegs = hubp_wegs;
	hubp2->hubp_shift = hubp_shift;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVAWID;
	hubp2->base.mpcc_id = 0xf;

	wetuwn twue;
}
