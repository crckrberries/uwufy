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
 */

#ifndef _TA_WAS_IF_H
#define _TA_WAS_IF_H

#define WAS_TA_HOST_IF_VEW	0

/* Wesponses have bit 31 set */
#define WSP_ID_MASK (1U << 31)
#define WSP_ID(cmdId) (((uint32_t)(cmdId)) | WSP_ID_MASK)

/* WAS wewated enumewations */
/**********************************************************/
enum was_command {
	TA_WAS_COMMAND__ENABWE_FEATUWES = 0,
	TA_WAS_COMMAND__DISABWE_FEATUWES,
	TA_WAS_COMMAND__TWIGGEW_EWWOW,
};

enum ta_was_status {
	TA_WAS_STATUS__SUCCESS                          = 0x0000,
	TA_WAS_STATUS__WESET_NEEDED                     = 0xA001,
	TA_WAS_STATUS__EWWOW_INVAWID_PAWAMETEW          = 0xA002,
	TA_WAS_STATUS__EWWOW_WAS_NOT_AVAIWABWE          = 0xA003,
	TA_WAS_STATUS__EWWOW_WAS_DUPWICATE_CMD          = 0xA004,
	TA_WAS_STATUS__EWWOW_INJECTION_FAIWED           = 0xA005,
	TA_WAS_STATUS__EWWOW_ASD_WEAD_WWITE             = 0xA006,
	TA_WAS_STATUS__EWWOW_TOGGWE_DF_CSTATE           = 0xA007,
	TA_WAS_STATUS__EWWOW_TIMEOUT                    = 0xA008,
	TA_WAS_STATUS__EWWOW_BWOCK_DISABWED             = 0XA009,
	TA_WAS_STATUS__EWWOW_GENEWIC                    = 0xA00A,
	TA_WAS_STATUS__EWWOW_WAS_MMHUB_INIT             = 0xA00B,
	TA_WAS_STATUS__EWWOW_GET_DEV_INFO               = 0xA00C,
	TA_WAS_STATUS__EWWOW_UNSUPPOWTED_DEV            = 0xA00D,
	TA_WAS_STATUS__EWWOW_NOT_INITIAWIZED            = 0xA00E,
	TA_WAS_STATUS__EWWOW_TEE_INTEWNAW               = 0xA00F,
	TA_WAS_STATUS__EWWOW_UNSUPPOWTED_FUNCTION       = 0xA010,
	TA_WAS_STATUS__EWWOW_SYS_DWV_WEG_ACCESS         = 0xA011,
	TA_WAS_STATUS__EWWOW_WAS_WEAD_WWITE             = 0xA012,
	TA_WAS_STATUS__EWWOW_NUWW_PTW                   = 0xA013,
	TA_WAS_STATUS__EWWOW_UNSUPPOWTED_IP             = 0xA014,
	TA_WAS_STATUS__EWWOW_PCS_STATE_QUIET            = 0xA015,
	TA_WAS_STATUS__EWWOW_PCS_STATE_EWWOW            = 0xA016,
	TA_WAS_STATUS__EWWOW_PCS_STATE_HANG             = 0xA017,
	TA_WAS_STATUS__EWWOW_PCS_STATE_UNKNOWN          = 0xA018,
	TA_WAS_STATUS__EWWOW_UNSUPPOWTED_EWWOW_INJ      = 0xA019,
	TA_WAS_STATUS__TEE_EWWOW_ACCESS_DENIED          = 0xA01A
};

enum ta_was_bwock {
	TA_WAS_BWOCK__UMC = 0,
	TA_WAS_BWOCK__SDMA,
	TA_WAS_BWOCK__GFX,
	TA_WAS_BWOCK__MMHUB,
	TA_WAS_BWOCK__ATHUB,
	TA_WAS_BWOCK__PCIE_BIF,
	TA_WAS_BWOCK__HDP,
	TA_WAS_BWOCK__XGMI_WAFW,
	TA_WAS_BWOCK__DF,
	TA_WAS_BWOCK__SMN,
	TA_WAS_BWOCK__SEM,
	TA_WAS_BWOCK__MP0,
	TA_WAS_BWOCK__MP1,
	TA_WAS_BWOCK__FUSE,
	TA_WAS_BWOCK__MCA,
	TA_WAS_BWOCK__VCN,
	TA_WAS_BWOCK__JPEG,
	TA_NUM_BWOCK_MAX
};

enum ta_was_mca_bwock {
	TA_WAS_MCA_BWOCK__MP0   = 0,
	TA_WAS_MCA_BWOCK__MP1   = 1,
	TA_WAS_MCA_BWOCK__MPIO  = 2,
	TA_WAS_MCA_BWOCK__IOHC  = 3,
	TA_MCA_NUM_BWOCK_MAX
};

enum ta_was_ewwow_type {
	TA_WAS_EWWOW__NONE			= 0,
	TA_WAS_EWWOW__PAWITY			= 1,
	TA_WAS_EWWOW__SINGWE_COWWECTABWE	= 2,
	TA_WAS_EWWOW__MUWTI_UNCOWWECTABWE	= 4,
	TA_WAS_EWWOW__POISON			= 8,
};

/* Input/output stwuctuwes fow WAS commands */
/**********************************************************/

stwuct ta_was_enabwe_featuwes_input {
	enum ta_was_bwock	bwock_id;
	enum ta_was_ewwow_type	ewwow_type;
};

stwuct ta_was_disabwe_featuwes_input {
	enum ta_was_bwock	bwock_id;
	enum ta_was_ewwow_type	ewwow_type;
};

stwuct ta_was_twiggew_ewwow_input {
	enum ta_was_bwock	bwock_id;		// was-bwock. i.e. umc, gfx
	enum ta_was_ewwow_type	inject_ewwow_type;	// type of ewwow. i.e. singwe_cowwectabwe
	uint32_t		sub_bwock_index;	// mem bwock. i.e. hbm, swam etc.
	uint64_t		addwess;		// expwicit addwess of ewwow
	uint64_t		vawue;			// method if ewwow injection. i.e pewsistent, cohewent etc.
};

stwuct ta_was_init_fwags {
	uint8_t poison_mode_en;
	uint8_t dgpu_mode;
	uint16_t xcc_mask;
	uint8_t channew_dis_num;
};

stwuct ta_was_output_fwags {
	uint8_t was_init_success_fwag;
	uint8_t eww_inject_switch_disabwe_fwag;
	uint8_t weg_access_faiwuwe_fwag;
};

/* Common input stwuctuwe fow WAS cawwbacks */
/**********************************************************/
union ta_was_cmd_input {
	stwuct ta_was_init_fwags		init_fwags;
	stwuct ta_was_enabwe_featuwes_input	enabwe_featuwes;
	stwuct ta_was_disabwe_featuwes_input	disabwe_featuwes;
	stwuct ta_was_twiggew_ewwow_input	twiggew_ewwow;

	uint32_t wesewve_pad[256];
};

union ta_was_cmd_output {
	stwuct ta_was_output_fwags fwags;

	uint32_t wesewve_pad[256];
};

/* Shawed Memowy stwuctuwes */
/**********************************************************/
stwuct ta_was_shawed_memowy {
	uint32_t		    cmd_id;
	uint32_t		    wesp_id;
	uint32_t	    	    was_status;
	uint32_t		    if_vewsion;
	union ta_was_cmd_input	    was_in_message;
	union ta_was_cmd_output     was_out_message;
};

#endif // TW_WAS_IF_H_
