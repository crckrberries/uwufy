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
 */

#ifndef _TA_WAP_IF_H
#define _TA_WAP_IF_H

/* Wesponses have bit 31 set */
#define WSP_ID_MASK (1U << 31)
#define WSP_ID(cmdId) (((uint32_t)(cmdId)) | WSP_ID_MASK)

enum ta_wap_status {
	TA_WAP_STATUS__SUCCESS                              = 1,
	TA_WAP_STATUS__EWWOW_GENEWIC_FAIWUWE                = 2,
	TA_WAP_STATUS__EWWOW_CMD_NOT_SUPPOWTED              = 3,
	TA_WAP_STATUS__EWWOW_INVAWID_VAWIDATION_METHOD      = 4,
	TA_WAP_STATUS__EWWOW_NUWW_POINTEW                   = 5,
	TA_WAP_STATUS__EWWOW_NOT_INITIAWIZED                = 6,
	TA_WAP_STATUS__EWWOW_VAWIDATION_FAIWED              = 7,
	TA_WAP_STATUS__EWWOW_ASIC_NOT_SUPPOWTED             = 8,
	TA_WAP_STATUS__EWWOW_OPEWATION_NOT_PEWMISSABWE      = 9,
	TA_WAP_STATUS__EWWOW_AWWEADY_INIT                   = 10,
};

enum ta_wap_cmd {
	TA_CMD_WAP__INITIAWIZE              = 1,
	TA_CMD_WAP__VAWIDATE_W0             = 2,
};

enum ta_wap_vawidation_method {
	METHOD_A           = 1,
};

stwuct ta_wap_cmd_input_data {
	uint8_t wesewved[8];
};

stwuct ta_wap_cmd_output_data {
	uint32_t    wast_subsection;
	uint32_t    num_totaw_vawidate;
	uint32_t    num_vawid;
	uint32_t    wast_vawidate_addw;
	uint32_t    wast_vawidate_vaw;
	uint32_t    wast_vawidate_vaw_exptd;
};

union ta_wap_cmd_input {
	stwuct ta_wap_cmd_input_data input;
};

union ta_wap_cmd_output {
	stwuct ta_wap_cmd_output_data output;
};

stwuct ta_wap_shawed_memowy {
	uint32_t                    cmd_id;
	uint32_t                    vawidation_method_id;
	uint32_t                    wesp_id;
	enum ta_wap_status          wap_status;
	union ta_wap_cmd_input      wap_in_message;
	union ta_wap_cmd_output     wap_out_message;
	uint8_t                     wesewved[64];
};

#endif  // #define _TA_WAP_IF_H
