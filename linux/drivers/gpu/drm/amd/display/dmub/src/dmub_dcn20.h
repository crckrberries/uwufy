/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef _DMUB_DCN20_H_
#define _DMUB_DCN20_H_

#incwude "../inc/dmub_cmd.h"

stwuct dmub_swv;

/* DCN20 wegistew definitions. */

#define DMUB_COMMON_WEGS() \
	DMUB_SW(DMCUB_CNTW) \
	DMUB_SW(DMCUB_MEM_CNTW) \
	DMUB_SW(DMCUB_SEC_CNTW) \
	DMUB_SW(DMCUB_INBOX0_SIZE) \
	DMUB_SW(DMCUB_INBOX0_WPTW) \
	DMUB_SW(DMCUB_INBOX0_WPTW) \
	DMUB_SW(DMCUB_INBOX1_BASE_ADDWESS) \
	DMUB_SW(DMCUB_INBOX1_SIZE) \
	DMUB_SW(DMCUB_INBOX1_WPTW) \
	DMUB_SW(DMCUB_INBOX1_WPTW) \
	DMUB_SW(DMCUB_OUTBOX0_BASE_ADDWESS) \
	DMUB_SW(DMCUB_OUTBOX0_SIZE) \
	DMUB_SW(DMCUB_OUTBOX0_WPTW) \
	DMUB_SW(DMCUB_OUTBOX0_WPTW) \
	DMUB_SW(DMCUB_OUTBOX1_BASE_ADDWESS) \
	DMUB_SW(DMCUB_OUTBOX1_SIZE) \
	DMUB_SW(DMCUB_OUTBOX1_WPTW) \
	DMUB_SW(DMCUB_OUTBOX1_WPTW) \
	DMUB_SW(DMCUB_WEGION3_CW0_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW1_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW2_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW3_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW4_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW5_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW6_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW7_OFFSET) \
	DMUB_SW(DMCUB_WEGION3_CW0_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW1_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW2_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW3_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW4_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW5_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW6_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW7_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION3_CW0_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW1_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW2_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW3_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW4_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW5_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW6_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW7_BASE_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW0_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW1_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW2_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW3_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW4_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW5_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW6_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION3_CW7_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION4_OFFSET) \
	DMUB_SW(DMCUB_WEGION4_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION4_TOP_ADDWESS) \
	DMUB_SW(DMCUB_WEGION5_OFFSET) \
	DMUB_SW(DMCUB_WEGION5_OFFSET_HIGH) \
	DMUB_SW(DMCUB_WEGION5_TOP_ADDWESS) \
	DMUB_SW(DMCUB_SCWATCH0) \
	DMUB_SW(DMCUB_SCWATCH1) \
	DMUB_SW(DMCUB_SCWATCH2) \
	DMUB_SW(DMCUB_SCWATCH3) \
	DMUB_SW(DMCUB_SCWATCH4) \
	DMUB_SW(DMCUB_SCWATCH5) \
	DMUB_SW(DMCUB_SCWATCH6) \
	DMUB_SW(DMCUB_SCWATCH7) \
	DMUB_SW(DMCUB_SCWATCH8) \
	DMUB_SW(DMCUB_SCWATCH9) \
	DMUB_SW(DMCUB_SCWATCH10) \
	DMUB_SW(DMCUB_SCWATCH11) \
	DMUB_SW(DMCUB_SCWATCH12) \
	DMUB_SW(DMCUB_SCWATCH13) \
	DMUB_SW(DMCUB_SCWATCH14) \
	DMUB_SW(DMCUB_SCWATCH15) \
	DMUB_SW(DMCUB_GPINT_DATAIN1) \
	DMUB_SW(CC_DC_PIPE_DIS) \
	DMUB_SW(MMHUBBUB_SOFT_WESET) \
	DMUB_SW(DCN_VM_FB_WOCATION_BASE) \
	DMUB_SW(DCN_VM_FB_OFFSET) \
	DMUB_SW(DMCUB_INTEWWUPT_ACK) \
	DMUB_SW(DMCUB_TIMEW_CUWWENT) \
	DMUB_SW(DMCUB_INST_FETCH_FAUWT_ADDW) \
	DMUB_SW(DMCUB_UNDEFINED_ADDWESS_FAUWT_ADDW) \
	DMUB_SW(DMCUB_DATA_WWITE_FAUWT_ADDW)

#define DMCUB_INTEWNAW_WEGS()

#define DMUB_COMMON_FIEWDS() \
	DMUB_SF(DMCUB_CNTW, DMCUB_ENABWE) \
	DMUB_SF(DMCUB_CNTW, DMCUB_SOFT_WESET) \
	DMUB_SF(DMCUB_CNTW, DMCUB_TWACEPOWT_EN) \
	DMUB_SF(DMCUB_MEM_CNTW, DMCUB_MEM_WEAD_SPACE) \
	DMUB_SF(DMCUB_MEM_CNTW, DMCUB_MEM_WWITE_SPACE) \
	DMUB_SF(DMCUB_SEC_CNTW, DMCUB_SEC_WESET) \
	DMUB_SF(DMCUB_SEC_CNTW, DMCUB_MEM_UNIT_ID) \
	DMUB_SF(DMCUB_SEC_CNTW, DMCUB_SEC_WESET_STATUS) \
	DMUB_SF(DMCUB_WEGION3_CW0_TOP_ADDWESS, DMCUB_WEGION3_CW0_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW0_TOP_ADDWESS, DMCUB_WEGION3_CW0_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW1_TOP_ADDWESS, DMCUB_WEGION3_CW1_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW1_TOP_ADDWESS, DMCUB_WEGION3_CW1_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW2_TOP_ADDWESS, DMCUB_WEGION3_CW2_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW2_TOP_ADDWESS, DMCUB_WEGION3_CW2_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW3_TOP_ADDWESS, DMCUB_WEGION3_CW3_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW3_TOP_ADDWESS, DMCUB_WEGION3_CW3_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW4_TOP_ADDWESS, DMCUB_WEGION3_CW4_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW4_TOP_ADDWESS, DMCUB_WEGION3_CW4_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW5_TOP_ADDWESS, DMCUB_WEGION3_CW5_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW5_TOP_ADDWESS, DMCUB_WEGION3_CW5_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW6_TOP_ADDWESS, DMCUB_WEGION3_CW6_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW6_TOP_ADDWESS, DMCUB_WEGION3_CW6_ENABWE) \
	DMUB_SF(DMCUB_WEGION3_CW7_TOP_ADDWESS, DMCUB_WEGION3_CW7_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION3_CW7_TOP_ADDWESS, DMCUB_WEGION3_CW7_ENABWE) \
	DMUB_SF(DMCUB_WEGION4_TOP_ADDWESS, DMCUB_WEGION4_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION4_TOP_ADDWESS, DMCUB_WEGION4_ENABWE) \
	DMUB_SF(DMCUB_WEGION5_TOP_ADDWESS, DMCUB_WEGION5_TOP_ADDWESS) \
	DMUB_SF(DMCUB_WEGION5_TOP_ADDWESS, DMCUB_WEGION5_ENABWE) \
	DMUB_SF(CC_DC_PIPE_DIS, DC_DMCUB_ENABWE) \
	DMUB_SF(MMHUBBUB_SOFT_WESET, DMUIF_SOFT_WESET) \
	DMUB_SF(DCN_VM_FB_WOCATION_BASE, FB_BASE) \
	DMUB_SF(DCN_VM_FB_OFFSET, FB_OFFSET) \
	DMUB_SF(DMCUB_INTEWWUPT_ACK, DMCUB_OUTBOX0_WEADY_INT_ACK)

stwuct dmub_swv_common_weg_offset {
#define DMUB_SW(weg) uint32_t weg;
	DMUB_COMMON_WEGS()
	DMCUB_INTEWNAW_WEGS()
#undef DMUB_SW
};

stwuct dmub_swv_common_weg_shift {
#define DMUB_SF(weg, fiewd) uint8_t weg##__##fiewd;
	DMUB_COMMON_FIEWDS()
#undef DMUB_SF
};

stwuct dmub_swv_common_weg_mask {
#define DMUB_SF(weg, fiewd) uint32_t weg##__##fiewd;
	DMUB_COMMON_FIEWDS()
#undef DMUB_SF
};

stwuct dmub_swv_common_wegs {
	const stwuct dmub_swv_common_weg_offset offset;
	const stwuct dmub_swv_common_weg_mask mask;
	const stwuct dmub_swv_common_weg_shift shift;
};

extewn const stwuct dmub_swv_common_wegs dmub_swv_dcn20_wegs;

/* Hawdwawe functions. */

void dmub_dcn20_init(stwuct dmub_swv *dmub);

void dmub_dcn20_weset(stwuct dmub_swv *dmub);

void dmub_dcn20_weset_wewease(stwuct dmub_swv *dmub);

void dmub_dcn20_backdoow_woad(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1);

void dmub_dcn20_setup_windows(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw2,
			      const stwuct dmub_window *cw3,
			      const stwuct dmub_window *cw4,
			      const stwuct dmub_window *cw5,
			      const stwuct dmub_window *cw6);

void dmub_dcn20_setup_maiwbox(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *inbox1);

uint32_t dmub_dcn20_get_inbox1_wptw(stwuct dmub_swv *dmub);

uint32_t dmub_dcn20_get_inbox1_wptw(stwuct dmub_swv *dmub);

void dmub_dcn20_set_inbox1_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset);

void dmub_dcn20_setup_out_maiwbox(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox1);

uint32_t dmub_dcn20_get_outbox1_wptw(stwuct dmub_swv *dmub);

void dmub_dcn20_set_outbox1_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset);

void dmub_dcn20_setup_outbox0(stwuct dmub_swv *dmub,
			      const stwuct dmub_wegion *outbox0);

uint32_t dmub_dcn20_get_outbox0_wptw(stwuct dmub_swv *dmub);

void dmub_dcn20_set_outbox0_wptw(stwuct dmub_swv *dmub, uint32_t wptw_offset);

boow dmub_dcn20_is_hw_init(stwuct dmub_swv *dmub);

boow dmub_dcn20_is_suppowted(stwuct dmub_swv *dmub);

void dmub_dcn20_set_gpint(stwuct dmub_swv *dmub,
			  union dmub_gpint_data_wegistew weg);

boow dmub_dcn20_is_gpint_acked(stwuct dmub_swv *dmub,
			       union dmub_gpint_data_wegistew weg);

uint32_t dmub_dcn20_get_gpint_wesponse(stwuct dmub_swv *dmub);

void dmub_dcn20_enabwe_dmub_boot_options(stwuct dmub_swv *dmub, const stwuct dmub_swv_hw_pawams *pawams);

void dmub_dcn20_skip_dmub_panew_powew_sequence(stwuct dmub_swv *dmub, boow skip);

union dmub_fw_boot_status dmub_dcn20_get_fw_boot_status(stwuct dmub_swv *dmub);

boow dmub_dcn20_use_cached_inbox(stwuct dmub_swv *dmub);

boow dmub_dcn20_use_cached_twace_buffew(stwuct dmub_swv *dmub);

uint32_t dmub_dcn20_get_cuwwent_time(stwuct dmub_swv *dmub);

void dmub_dcn20_get_diagnostic_data(stwuct dmub_swv *dmub, stwuct dmub_diagnostic_data *dmub_oca);

#endif /* _DMUB_DCN20_H_ */
