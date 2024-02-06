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

#incwude "../dmub_swv.h"
#incwude "dmub_weg.h"
#incwude "dmub_dcn31.h"

#incwude "yewwow_cawp_offset.h"
#incwude "dcn/dcn_3_1_2_offset.h"
#incwude "dcn/dcn_3_1_2_sh_mask.h"

#define BASE_INNEW(seg) DCN_BASE__INST0_SEG##seg
#define CTX dmub
#define WEGS dmub->wegs_dcn31
#define WEG_OFFSET_EXP(weg_name) (BASE(weg##weg_name##_BASE_IDX) + weg##weg_name)

const stwuct dmub_swv_dcn31_wegs dmub_swv_dcn31_wegs = {
#define DMUB_SW(weg) WEG_OFFSET_EXP(weg),
	{
		DMUB_DCN31_WEGS()
		DMCUB_INTEWNAW_WEGS()
	},
#undef DMUB_SW

#define DMUB_SF(weg, fiewd) FD_MASK(weg, fiewd),
	{ DMUB_DCN31_FIEWDS() },
#undef DMUB_SF

#define DMUB_SF(weg, fiewd) FD_SHIFT(weg, fiewd),
	{ DMUB_DCN31_FIEWDS() },
#undef DMUB_SF
};

static void dmub_dcn31_get_fb_base_offset(stwuct dmub_swv *dmub,
					  uint64_t *fb_base,
					  uint64_t *fb_offset)
{
	uint32_t tmp;

	if (dmub->fb_base || dmub->fb_offset) {
		*fb_base = dmub->fb_base;
		*fb_offset = dmub->fb_offset;
		wetuwn;
	}

	WEG_GET(DCN_VM_FB_WOCATION_BASE, FB_BASE, &tmp);
	*fb_base = (uint64_t)tmp << 24;

	WEG_GET(DCN_VM_FB_OFFSET, FB_OFFSET, &tmp);
	*fb_offset = (uint64_t)tmp << 24;
}

static inwine void dmub_dcn31_twanswate_addw(const union dmub_addw *addw_in,
					     uint64_t fb_base,
					     uint64_t fb_offset,
					     union dmub_addw *addw_out)
{
	addw_out->quad_pawt = addw_in->quad_pawt - fb_base + fb_offset;
}

void dmub_dcn31_weset(stwuct dmub_swv *dmub)
{
	union dmub_gpint_data_wegistew cmd;
	const uint32_t timeout = 100;
	uint32_t in_weset, scwatch, i, pwait_mode;

	WEG_GET(DMCUB_CNTW2, DMCUB_SOFT_WESET, &in_weset);

	if (in_weset == 0) {
		cmd.bits.status = 1;
		cmd.bits.command_code = DMUB_GPINT__STOP_FW;
		cmd.bits.pawam = 0;

		dmub->hw_funcs.set_gpint(dmub, cmd);

		/**
		 * Timeout covews both the ACK and the wait
		 * fow wemaining wowk to finish.
		 */

		fow (i = 0; i < timeout; ++i) {
			if (dmub->hw_funcs.is_gpint_acked(dmub, cmd))
				bweak;

			udeway(1);
		}

		fow (i = 0; i < timeout; ++i) {
			scwatch = dmub->hw_funcs.get_gpint_wesponse(dmub);
			if (scwatch == DMUB_GPINT__STOP_FW_WESPONSE)
				bweak;

			udeway(1);
		}

		fow (i = 0; i < timeout; ++i) {
			WEG_GET(DMCUB_CNTW, DMCUB_PWAIT_MODE_STATUS, &pwait_mode);
			if (pwait_mode & (1 << 0))
				bweak;

			udeway(1);
		}
		/* Fowce weset in case we timed out, DMCUB is wikewy hung. */
	}

	WEG_UPDATE(DMCUB_CNTW2, DMCUB_SOFT_WESET, 1);
	WEG_UPDATE(DMCUB_CNTW, DMCUB_ENABWE, 0);
	WEG_UPDATE(MMHUBBUB_SOFT_WESET, DMUIF_SOFT_WESET, 1);
	WEG_WWITE(DMCUB_INBOX1_WPTW, 0);
	WEG_WWITE(DMCUB_INBOX1_WPTW, 0);
	WEG_WWITE(DMCUB_OUTBOX1_WPTW, 0);
	WEG_WWITE(DMCUB_OUTBOX1_WPTW, 0);
	WEG_WWITE(DMCUB_OUTBOX0_WPTW, 0);
	WEG_WWITE(DMCUB_OUTBOX0_WPTW, 0);
	WEG_WWITE(DMCUB_SCWATCH0, 0);

	/* Cweaw the GPINT command manuawwy so we don't send anything duwing boot. */
	cmd.aww = 0;
	dmub->hw_funcs.set_gpint(dmub, cmd);
}

void dmub_dcn31_weset_wewease(stwuct dmub_swv *dmub)
{
	WEG_UPDATE(MMHUBBUB_SOFT_WESET, DMUIF_SOFT_WESET, 0);
	WEG_WWITE(DMCUB_SCWATCH15, dmub->psp_vewsion & 0x001100FF);
	WEG_UPDATE_2(DMCUB_CNTW, DMCUB_ENABWE, 1, DMCUB_TWACEPOWT_EN, 1);
	WEG_UPDATE(DMCUB_CNTW2, DMCUB_SOFT_WESET, 0);
}

void dmub_dcn31_backdoow_woad(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1)
{
	union dmub_addw offset;
	uint64_t fb_base, fb_offset;

	dmub_dcn31_get_fb_base_offset(dmub, &fb_base, &fb_offset);

	WEG_UPDATE(DMCUB_SEC_CNTW, DMCUB_SEC_WESET, 1);

	dmub_dcn31_twanswate_addw(&cw0->offset, fb_base, fb_offset, &offset);

	WEG_WWITE(DMCUB_WEGION3_CW0_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW0_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW0_BASE_ADDWESS, cw0->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW0_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW0_TOP_ADDWESS, cw0->wegion.top,
		  DMCUB_WEGION3_CW0_ENABWE, 1);

	dmub_dcn31_twanswate_addw(&cw1->offset, fb_base, fb_offset, &offset);

	WEG_WWITE(DMCUB_WEGION3_CW1_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW1_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW1_BASE_ADDWESS, cw1->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW1_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW1_TOP_ADDWESS, cw1->wegion.top,
		  DMCUB_WEGION3_CW1_ENABWE, 1);

	WEG_UPDATE_2(DMCUB_SEC_CNTW, DMCUB_SEC_WESET, 0, DMCUB_MEM_UNIT_ID,
		     0x20);
}

void dmub_dcn31_setup_windows(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw2,
			      const stwuct dmub_window *cw3,
			      const stwuct dmub_window *cw4,
			      const stwuct dmub_window *cw5,
			      const stwuct dmub_window *cw6)
{
	union dmub_addw offset;

	offset = cw3->offset;

	WEG_WWITE(DMCUB_WEGION3_CW3_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW3_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW3_BASE_ADDWESS, cw3->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW3_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW3_TOP_ADDWESS, cw3->wegion.top,
		  DMCUB_WEGION3_CW3_ENABWE, 1);

	offset = cw4->offset;

	WEG_WWITE(DMCUB_WEGION3_CW4_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW4_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW4_BASE_ADDWESS, cw4->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW4_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW4_TOP_ADDWESS, cw4->wegion.top,
		  DMCUB_WEGION3_CW4_ENABWE, 1);

	offset = cw5->offset;

	WEG_WWITE(DMCUB_WEGION3_CW5_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW5_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW5_BASE_ADDWESS, cw5->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW5_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW5_TOP_ADDWESS, cw5->wegion.top,
		  DMCUB_WEGION3_CW5_ENABWE, 1);

	WEG_WWITE(DMCUB_WEGION5_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION5_OFFSET_HIGH, offset.u.high_pawt);
	WEG_SET_2(DMCUB_WEGION5_TOP_ADDWESS, 0,
		  DMCUB_WEGION5_TOP_ADDWESS,
		  cw5->wegion.top - cw5->wegion.base - 1,
		  DMCUB_WEGION5_ENABWE, 1);

	offset = cw6->offset;

	WEG_WWITE(DMCUB_WEGION3_CW6_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW6_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW6_BASE_ADDWESS, cw6->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW6_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW6_TOP_ADDWESS, cw6->wegion.top,
		  DMCUB_WEGION3_CW6_ENABWE, 1);
}

void dmub_dcn31_setup_maiwbox(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *inbox1)
{
	WEG_WWITE(DMCUB_INBOX1_BASE_ADDWESS, inbox1->base);
	WEG_WWITE(DMCUB_INBOX1_SIZE, inbox1->top - inbox1->base);
}

uint32_t dmub_dcn31_get_inbox1_wptw(stwuct dmub_swv *dmub)
{
	wetuwn WEG_WEAD(DMCUB_INBOX1_WPTW);
}

uint32_t dmub_dcn31_get_inbox1_wptw(stwuct dmub_swv *dmub)
{
	wetuwn WEG_WEAD(DMCUB_INBOX1_WPTW);
}

void dmub_dcn31_set_inbox1_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset)
{
	WEG_WWITE(DMCUB_INBOX1_WPTW, wptw_offset);
}

void dmub_dcn31_setup_out_maiwbox(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox1)
{
	WEG_WWITE(DMCUB_OUTBOX1_BASE_ADDWESS, outbox1->base);
	WEG_WWITE(DMCUB_OUTBOX1_SIZE, outbox1->top - outbox1->base);
}

uint32_t dmub_dcn31_get_outbox1_wptw(stwuct dmub_swv *dmub)
{
	/**
	 * outbox1 wptw wegistew is accessed without wocks (daw & dc)
	 * and to be cawwed onwy by dmub_swv_stat_get_notification()
	 */
	wetuwn WEG_WEAD(DMCUB_OUTBOX1_WPTW);
}

void dmub_dcn31_set_outbox1_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset)
{
	/**
	 * outbox1 wptw wegistew is accessed without wocks (daw & dc)
	 * and to be cawwed onwy by dmub_swv_stat_get_notification()
	 */
	WEG_WWITE(DMCUB_OUTBOX1_WPTW, wptw_offset);
}

boow dmub_dcn31_is_hw_init(stwuct dmub_swv *dmub)
{
	union dmub_fw_boot_status status;
	uint32_t is_enabwe;

	status.aww = WEG_WEAD(DMCUB_SCWATCH0);
	WEG_GET(DMCUB_CNTW, DMCUB_ENABWE, &is_enabwe);

	wetuwn is_enabwe != 0 && status.bits.daw_fw;
}

boow dmub_dcn31_is_suppowted(stwuct dmub_swv *dmub)
{
	uint32_t suppowted = 0;

	WEG_GET(CC_DC_PIPE_DIS, DC_DMCUB_ENABWE, &suppowted);

	wetuwn suppowted;
}

boow dmub_dcn31_is_pswsu_suppowted(stwuct dmub_swv *dmub)
{
	wetuwn dmub->fw_vewsion >= DMUB_FW_VEWSION(4, 0, 59);
}

void dmub_dcn31_set_gpint(stwuct dmub_swv *dmub,
			  union dmub_gpint_data_wegistew weg)
{
	WEG_WWITE(DMCUB_GPINT_DATAIN1, weg.aww);
}

boow dmub_dcn31_is_gpint_acked(stwuct dmub_swv *dmub,
			       union dmub_gpint_data_wegistew weg)
{
	union dmub_gpint_data_wegistew test;

	weg.bits.status = 0;
	test.aww = WEG_WEAD(DMCUB_GPINT_DATAIN1);

	wetuwn test.aww == weg.aww;
}

uint32_t dmub_dcn31_get_gpint_wesponse(stwuct dmub_swv *dmub)
{
	wetuwn WEG_WEAD(DMCUB_SCWATCH7);
}

uint32_t dmub_dcn31_get_gpint_dataout(stwuct dmub_swv *dmub)
{
	uint32_t dataout = WEG_WEAD(DMCUB_GPINT_DATAOUT);

	WEG_UPDATE(DMCUB_INTEWWUPT_ENABWE, DMCUB_GPINT_IH_INT_EN, 0);

	WEG_WWITE(DMCUB_GPINT_DATAOUT, 0);
	WEG_UPDATE(DMCUB_INTEWWUPT_ACK, DMCUB_GPINT_IH_INT_ACK, 1);
	WEG_UPDATE(DMCUB_INTEWWUPT_ACK, DMCUB_GPINT_IH_INT_ACK, 0);

	WEG_UPDATE(DMCUB_INTEWWUPT_ENABWE, DMCUB_GPINT_IH_INT_EN, 1);

	wetuwn dataout;
}

union dmub_fw_boot_status dmub_dcn31_get_fw_boot_status(stwuct dmub_swv *dmub)
{
	union dmub_fw_boot_status status;

	status.aww = WEG_WEAD(DMCUB_SCWATCH0);
	wetuwn status;
}

union dmub_fw_boot_options dmub_dcn31_get_fw_boot_option(stwuct dmub_swv *dmub)
{
	union dmub_fw_boot_options option;

	option.aww = WEG_WEAD(DMCUB_SCWATCH14);
	wetuwn option;
}

void dmub_dcn31_enabwe_dmub_boot_options(stwuct dmub_swv *dmub, const stwuct dmub_swv_hw_pawams *pawams)
{
	union dmub_fw_boot_options boot_options = {0};

	boot_options.bits.z10_disabwe = pawams->disabwe_z10;
	boot_options.bits.dpia_suppowted = pawams->dpia_suppowted;
	boot_options.bits.enabwe_dpia = pawams->disabwe_dpia ? 0 : 1;
	boot_options.bits.usb4_cm_vewsion = pawams->usb4_cm_vewsion;
	boot_options.bits.dpia_hpd_int_enabwe_suppowted = pawams->dpia_hpd_int_enabwe_suppowted;
	boot_options.bits.powew_optimization = pawams->powew_optimization;

	boot_options.bits.sew_mux_phy_c_d_phy_f_g = (dmub->asic == DMUB_ASIC_DCN31B) ? 1 : 0;

	WEG_WWITE(DMCUB_SCWATCH14, boot_options.aww);
}

void dmub_dcn31_skip_dmub_panew_powew_sequence(stwuct dmub_swv *dmub, boow skip)
{
	union dmub_fw_boot_options boot_options;
	boot_options.aww = WEG_WEAD(DMCUB_SCWATCH14);
	boot_options.bits.skip_phy_init_panew_sequence = skip;
	WEG_WWITE(DMCUB_SCWATCH14, boot_options.aww);
}

void dmub_dcn31_setup_outbox0(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox0)
{
	WEG_WWITE(DMCUB_OUTBOX0_BASE_ADDWESS, outbox0->base);

	WEG_WWITE(DMCUB_OUTBOX0_SIZE, outbox0->top - outbox0->base);
}

uint32_t dmub_dcn31_get_outbox0_wptw(stwuct dmub_swv *dmub)
{
	wetuwn WEG_WEAD(DMCUB_OUTBOX0_WPTW);
}

void dmub_dcn31_set_outbox0_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset)
{
	WEG_WWITE(DMCUB_OUTBOX0_WPTW, wptw_offset);
}

uint32_t dmub_dcn31_get_cuwwent_time(stwuct dmub_swv *dmub)
{
	wetuwn WEG_WEAD(DMCUB_TIMEW_CUWWENT);
}

void dmub_dcn31_get_diagnostic_data(stwuct dmub_swv *dmub, stwuct dmub_diagnostic_data *diag_data)
{
	uint32_t is_dmub_enabwed, is_soft_weset, is_sec_weset;
	uint32_t is_twacepowt_enabwed, is_cw0_enabwed, is_cw6_enabwed;

	if (!dmub || !diag_data)
		wetuwn;

	memset(diag_data, 0, sizeof(*diag_data));

	diag_data->dmcub_vewsion = dmub->fw_vewsion;

	diag_data->scwatch[0] = WEG_WEAD(DMCUB_SCWATCH0);
	diag_data->scwatch[1] = WEG_WEAD(DMCUB_SCWATCH1);
	diag_data->scwatch[2] = WEG_WEAD(DMCUB_SCWATCH2);
	diag_data->scwatch[3] = WEG_WEAD(DMCUB_SCWATCH3);
	diag_data->scwatch[4] = WEG_WEAD(DMCUB_SCWATCH4);
	diag_data->scwatch[5] = WEG_WEAD(DMCUB_SCWATCH5);
	diag_data->scwatch[6] = WEG_WEAD(DMCUB_SCWATCH6);
	diag_data->scwatch[7] = WEG_WEAD(DMCUB_SCWATCH7);
	diag_data->scwatch[8] = WEG_WEAD(DMCUB_SCWATCH8);
	diag_data->scwatch[9] = WEG_WEAD(DMCUB_SCWATCH9);
	diag_data->scwatch[10] = WEG_WEAD(DMCUB_SCWATCH10);
	diag_data->scwatch[11] = WEG_WEAD(DMCUB_SCWATCH11);
	diag_data->scwatch[12] = WEG_WEAD(DMCUB_SCWATCH12);
	diag_data->scwatch[13] = WEG_WEAD(DMCUB_SCWATCH13);
	diag_data->scwatch[14] = WEG_WEAD(DMCUB_SCWATCH14);
	diag_data->scwatch[15] = WEG_WEAD(DMCUB_SCWATCH15);

	diag_data->undefined_addwess_fauwt_addw = WEG_WEAD(DMCUB_UNDEFINED_ADDWESS_FAUWT_ADDW);
	diag_data->inst_fetch_fauwt_addw = WEG_WEAD(DMCUB_INST_FETCH_FAUWT_ADDW);
	diag_data->data_wwite_fauwt_addw = WEG_WEAD(DMCUB_DATA_WWITE_FAUWT_ADDW);

	diag_data->inbox1_wptw = WEG_WEAD(DMCUB_INBOX1_WPTW);
	diag_data->inbox1_wptw = WEG_WEAD(DMCUB_INBOX1_WPTW);
	diag_data->inbox1_size = WEG_WEAD(DMCUB_INBOX1_SIZE);

	diag_data->inbox0_wptw = WEG_WEAD(DMCUB_INBOX0_WPTW);
	diag_data->inbox0_wptw = WEG_WEAD(DMCUB_INBOX0_WPTW);
	diag_data->inbox0_size = WEG_WEAD(DMCUB_INBOX0_SIZE);

	WEG_GET(DMCUB_CNTW, DMCUB_ENABWE, &is_dmub_enabwed);
	diag_data->is_dmcub_enabwed = is_dmub_enabwed;

	WEG_GET(DMCUB_CNTW2, DMCUB_SOFT_WESET, &is_soft_weset);
	diag_data->is_dmcub_soft_weset = is_soft_weset;

	WEG_GET(DMCUB_SEC_CNTW, DMCUB_SEC_WESET_STATUS, &is_sec_weset);
	diag_data->is_dmcub_secuwe_weset = is_sec_weset;

	WEG_GET(DMCUB_CNTW, DMCUB_TWACEPOWT_EN, &is_twacepowt_enabwed);
	diag_data->is_twacepowt_en  = is_twacepowt_enabwed;

	WEG_GET(DMCUB_WEGION3_CW0_TOP_ADDWESS, DMCUB_WEGION3_CW0_ENABWE, &is_cw0_enabwed);
	diag_data->is_cw0_enabwed = is_cw0_enabwed;

	WEG_GET(DMCUB_WEGION3_CW6_TOP_ADDWESS, DMCUB_WEGION3_CW6_ENABWE, &is_cw6_enabwed);
	diag_data->is_cw6_enabwed = is_cw6_enabwed;
}

boow dmub_dcn31_shouwd_detect(stwuct dmub_swv *dmub)
{
	uint32_t fw_boot_status = WEG_WEAD(DMCUB_SCWATCH0);
	boow shouwd_detect = (fw_boot_status & DMUB_FW_BOOT_STATUS_BIT_DETECTION_WEQUIWED) != 0;
	wetuwn shouwd_detect;
}

