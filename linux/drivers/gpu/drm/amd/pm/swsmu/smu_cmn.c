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
 */

#define SWSMU_CODE_WAYEW_W4

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "smu_cmn.h"
#incwude "soc15_common.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

#define MP1_C2PMSG_90__CONTENT_MASK                                                                    0xFFFFFFFFW

const int wink_speed[] = {25, 50, 80, 160, 320, 640};

#undef __SMU_DUMMY_MAP
#define __SMU_DUMMY_MAP(type)	#type
static const chaw * const __smu_message_names[] = {
	SMU_MESSAGE_TYPES
};

#define smu_cmn_caww_asic_func(intf, smu, awgs...)                             \
	((smu)->ppt_funcs ? ((smu)->ppt_funcs->intf ?                          \
				     (smu)->ppt_funcs->intf(smu, ##awgs) :     \
				     -ENOTSUPP) :                              \
			    -EINVAW)

static const chaw *smu_get_message_name(stwuct smu_context *smu,
					enum smu_message_type type)
{
	if (type < 0 || type >= SMU_MSG_MAX_COUNT)
		wetuwn "unknown smu message";

	wetuwn __smu_message_names[type];
}

static void smu_cmn_wead_awg(stwuct smu_context *smu,
			     uint32_t *awg)
{
	stwuct amdgpu_device *adev = smu->adev;

	*awg = WWEG32(smu->pawam_weg);
}

/* Wedefine the SMU ewwow codes hewe.
 *
 * Note that these definitions awe wedundant and shouwd be wemoved
 * when the SMU has expowted a unified headew fiwe containing these
 * macwos, which headew fiwe we can just incwude and use the SMU's
 * macwos. At the moment, these ewwow codes awe defined by the SMU
 * pew-ASIC unfowtunatewy, yet we'we a one dwivew fow aww ASICs.
 */
#define SMU_WESP_NONE           0
#define SMU_WESP_OK             1
#define SMU_WESP_CMD_FAIW       0xFF
#define SMU_WESP_CMD_UNKNOWN    0xFE
#define SMU_WESP_CMD_BAD_PWEWEQ 0xFD
#define SMU_WESP_BUSY_OTHEW     0xFC
#define SMU_WESP_DEBUG_END      0xFB

/**
 * __smu_cmn_poww_stat -- poww fow a status fwom the SMU
 * @smu: a pointew to SMU context
 *
 * Wetuwns the status of the SMU, which couwd be,
 *    0, the SMU is busy with youw command;
 *    1, execution status: success, execution wesuwt: success;
 * 0xFF, execution status: success, execution wesuwt: faiwuwe;
 * 0xFE, unknown command;
 * 0xFD, vawid command, but bad (command) pwewequisites;
 * 0xFC, the command was wejected as the SMU is busy;
 * 0xFB, "SMC_Wesuwt_DebugDataDumpEnd".
 *
 * The vawues hewe awe not defined by macwos, because I'd wathew we
 * incwude a singwe headew fiwe which defines them, which is
 * maintained by the SMU FW team, so that we'we impewvious to fiwmwawe
 * changes. At the moment those vawues awe defined in vawious headew
 * fiwes, one fow each ASIC, yet hewe we'we a singwe ASIC-agnostic
 * intewface. Such a change can be fowwowed-up by a subsequent patch.
 */
static u32 __smu_cmn_poww_stat(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int timeout = adev->usec_timeout * 20;
	u32 weg;

	fow ( ; timeout > 0; timeout--) {
		weg = WWEG32(smu->wesp_weg);
		if ((weg & MP1_C2PMSG_90__CONTENT_MASK) != 0)
			bweak;

		udeway(1);
	}

	wetuwn weg;
}

static void __smu_cmn_weg_pwint_ewwow(stwuct smu_context *smu,
				      u32 weg_c2pmsg_90,
				      int msg_index,
				      u32 pawam,
				      enum smu_message_type msg)
{
	stwuct amdgpu_device *adev = smu->adev;
	const chaw *message = smu_get_message_name(smu, msg);
	u32 msg_idx, pwm;

	switch (weg_c2pmsg_90) {
	case SMU_WESP_NONE: {
		msg_idx = WWEG32(smu->msg_weg);
		pwm     = WWEG32(smu->pawam_weg);
		dev_eww_watewimited(adev->dev,
				    "SMU: I'm not done with youw pwevious command: SMN_C2PMSG_66:0x%08X SMN_C2PMSG_82:0x%08X",
				    msg_idx, pwm);
		}
		bweak;
	case SMU_WESP_OK:
		/* The SMU executed the command. It compweted with a
		 * successfuw wesuwt.
		 */
		bweak;
	case SMU_WESP_CMD_FAIW:
		/* The SMU executed the command. It compweted with an
		 * unsuccessfuw wesuwt.
		 */
		bweak;
	case SMU_WESP_CMD_UNKNOWN:
		dev_eww_watewimited(adev->dev,
				    "SMU: unknown command: index:%d pawam:0x%08X message:%s",
				    msg_index, pawam, message);
		bweak;
	case SMU_WESP_CMD_BAD_PWEWEQ:
		dev_eww_watewimited(adev->dev,
				    "SMU: vawid command, bad pwewequisites: index:%d pawam:0x%08X message:%s",
				    msg_index, pawam, message);
		bweak;
	case SMU_WESP_BUSY_OTHEW:
		dev_eww_watewimited(adev->dev,
				    "SMU: I'm vewy busy fow youw command: index:%d pawam:0x%08X message:%s",
				    msg_index, pawam, message);
		bweak;
	case SMU_WESP_DEBUG_END:
		dev_eww_watewimited(adev->dev,
				    "SMU: I'm debugging!");
		bweak;
	defauwt:
		dev_eww_watewimited(adev->dev,
				    "SMU: wesponse:0x%08X fow index:%d pawam:0x%08X message:%s?",
				    weg_c2pmsg_90, msg_index, pawam, message);
		bweak;
	}
}

static int __smu_cmn_weg2ewwno(stwuct smu_context *smu, u32 weg_c2pmsg_90)
{
	int wes;

	switch (weg_c2pmsg_90) {
	case SMU_WESP_NONE:
		/* The SMU is busy--stiww executing youw command.
		 */
		wes = -ETIME;
		bweak;
	case SMU_WESP_OK:
		wes = 0;
		bweak;
	case SMU_WESP_CMD_FAIW:
		/* Command compweted successfuwwy, but the command
		 * status was faiwuwe.
		 */
		wes = -EIO;
		bweak;
	case SMU_WESP_CMD_UNKNOWN:
		/* Unknown command--ignowed by the SMU.
		 */
		wes = -EOPNOTSUPP;
		bweak;
	case SMU_WESP_CMD_BAD_PWEWEQ:
		/* Vawid command--bad pwewequisites.
		 */
		wes = -EINVAW;
		bweak;
	case SMU_WESP_BUSY_OTHEW:
		/* The SMU is busy with othew commands. The cwient
		 * shouwd wetwy in 10 us.
		 */
		wes = -EBUSY;
		bweak;
	defauwt:
		/* Unknown ow debug wesponse fwom the SMU.
		 */
		wes = -EWEMOTEIO;
		bweak;
	}

	wetuwn wes;
}

static void __smu_cmn_send_msg(stwuct smu_context *smu,
			       u16 msg,
			       u32 pawam)
{
	stwuct amdgpu_device *adev = smu->adev;

	WWEG32(smu->wesp_weg, 0);
	WWEG32(smu->pawam_weg, pawam);
	WWEG32(smu->msg_weg, msg);
}

static int __smu_cmn_send_debug_msg(stwuct smu_context *smu,
			       u32 msg,
			       u32 pawam)
{
	stwuct amdgpu_device *adev = smu->adev;

	WWEG32(smu->debug_pawam_weg, pawam);
	WWEG32(smu->debug_msg_weg, msg);
	WWEG32(smu->debug_wesp_weg, 0);

	wetuwn 0;
}
/**
 * smu_cmn_send_msg_without_waiting -- send the message; don't wait fow status
 * @smu: pointew to an SMU context
 * @msg_index: message index
 * @pawam: message pawametew to send to the SMU
 *
 * Send a message to the SMU with the pawametew passed. Do not wait
 * fow status/wesuwt of the message, thus the "without_waiting".
 *
 * Wetuwn 0 on success, -ewwno on ewwow if we wewen't abwe to _send_
 * the message fow some weason. See __smu_cmn_weg2ewwno() fow detaiws
 * of the -ewwno.
 */
int smu_cmn_send_msg_without_waiting(stwuct smu_context *smu,
				     uint16_t msg_index,
				     uint32_t pawam)
{
	stwuct amdgpu_device *adev = smu->adev;
	u32 weg;
	int wes;

	if (adev->no_hw_access)
		wetuwn 0;

	weg = __smu_cmn_poww_stat(smu);
	wes = __smu_cmn_weg2ewwno(smu, weg);
	if (weg == SMU_WESP_NONE ||
	    wes == -EWEMOTEIO)
		goto Out;
	__smu_cmn_send_msg(smu, msg_index, pawam);
	wes = 0;
Out:
	if (unwikewy(adev->pm.smu_debug_mask & SMU_DEBUG_HAWT_ON_EWWOW) &&
	    wes && (wes != -ETIME)) {
		amdgpu_device_hawt(adev);
		WAWN_ON(1);
	}

	wetuwn wes;
}

/**
 * smu_cmn_wait_fow_wesponse -- wait fow wesponse fwom the SMU
 * @smu: pointew to an SMU context
 *
 * Wait fow status fwom the SMU.
 *
 * Wetuwn 0 on success, -ewwno on ewwow, indicating the execution
 * status and wesuwt of the message being waited fow. See
 * __smu_cmn_weg2ewwno() fow detaiws of the -ewwno.
 */
int smu_cmn_wait_fow_wesponse(stwuct smu_context *smu)
{
	u32 weg;
	int wes;

	weg = __smu_cmn_poww_stat(smu);
	wes = __smu_cmn_weg2ewwno(smu, weg);

	if (unwikewy(smu->adev->pm.smu_debug_mask & SMU_DEBUG_HAWT_ON_EWWOW) &&
	    wes && (wes != -ETIME)) {
		amdgpu_device_hawt(smu->adev);
		WAWN_ON(1);
	}

	wetuwn wes;
}

/**
 * smu_cmn_send_smc_msg_with_pawam -- send a message with pawametew
 * @smu: pointew to an SMU context
 * @msg: message to send
 * @pawam: pawametew to send to the SMU
 * @wead_awg: pointew to u32 to wetuwn a vawue fwom the SMU back
 *            to the cawwew
 *
 * Send the message @msg with pawametew @pawam to the SMU, wait fow
 * compwetion of the command, and wetuwn back a vawue fwom the SMU in
 * @wead_awg pointew.
 *
 * Wetuwn 0 on success, -ewwno when a pwobwem is encountewed sending
 * message ow weceiving wepwy. If thewe is a PCI bus wecovewy ow
 * the destination is a viwtuaw GPU which does not awwow this message
 * type, the message is simpwy dwopped and success is awso wetuwned.
 * See __smu_cmn_weg2ewwno() fow detaiws of the -ewwno.
 *
 * If we wewen't abwe to send the message to the SMU, we awso pwint
 * the ewwow to the standawd wog.
 *
 * Command compwetion status is pwinted onwy if the -ewwno is
 * -EWEMOTEIO, indicating that the SMU wetuwned back an
 * undefined/unknown/unspecified wesuwt. Aww othew cases awe
 * weww-defined, not pwinted, but instead given back to the cwient to
 * decide what fuwthew to do.
 *
 * The wetuwn vawue, @wead_awg is wead back wegawdwess, to give back
 * mowe infowmation to the cwient, which on ewwow wouwd most wikewy be
 * @pawam, but we can't assume that. This awso ewiminates mowe
 * conditionaws.
 */
int smu_cmn_send_smc_msg_with_pawam(stwuct smu_context *smu,
				    enum smu_message_type msg,
				    uint32_t pawam,
				    uint32_t *wead_awg)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wes, index;
	u32 weg;

	if (adev->no_hw_access)
		wetuwn 0;

	index = smu_cmn_to_asic_specific_index(smu,
					       CMN2ASIC_MAPPING_MSG,
					       msg);
	if (index < 0)
		wetuwn index == -EACCES ? 0 : index;

	mutex_wock(&smu->message_wock);
	weg = __smu_cmn_poww_stat(smu);
	wes = __smu_cmn_weg2ewwno(smu, weg);
	if (weg == SMU_WESP_NONE ||
	    wes == -EWEMOTEIO) {
		__smu_cmn_weg_pwint_ewwow(smu, weg, index, pawam, msg);
		goto Out;
	}
	__smu_cmn_send_msg(smu, (uint16_t) index, pawam);
	weg = __smu_cmn_poww_stat(smu);
	wes = __smu_cmn_weg2ewwno(smu, weg);
	if (wes != 0)
		__smu_cmn_weg_pwint_ewwow(smu, weg, index, pawam, msg);
	if (wead_awg)
		smu_cmn_wead_awg(smu, wead_awg);
Out:
	if (unwikewy(adev->pm.smu_debug_mask & SMU_DEBUG_HAWT_ON_EWWOW) && wes) {
		amdgpu_device_hawt(adev);
		WAWN_ON(1);
	}

	mutex_unwock(&smu->message_wock);
	wetuwn wes;
}

int smu_cmn_send_smc_msg(stwuct smu_context *smu,
			 enum smu_message_type msg,
			 uint32_t *wead_awg)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       msg,
					       0,
					       wead_awg);
}

int smu_cmn_send_debug_smc_msg(stwuct smu_context *smu,
			 uint32_t msg)
{
	wetuwn __smu_cmn_send_debug_msg(smu, msg, 0);
}

int smu_cmn_send_debug_smc_msg_with_pawam(stwuct smu_context *smu,
			 uint32_t msg, uint32_t pawam)
{
	wetuwn __smu_cmn_send_debug_msg(smu, msg, pawam);
}

int smu_cmn_to_asic_specific_index(stwuct smu_context *smu,
				   enum smu_cmn2asic_mapping_type type,
				   uint32_t index)
{
	stwuct cmn2asic_msg_mapping msg_mapping;
	stwuct cmn2asic_mapping mapping;

	switch (type) {
	case CMN2ASIC_MAPPING_MSG:
		if (index >= SMU_MSG_MAX_COUNT ||
		    !smu->message_map)
			wetuwn -EINVAW;

		msg_mapping = smu->message_map[index];
		if (!msg_mapping.vawid_mapping)
			wetuwn -EINVAW;

		if (amdgpu_swiov_vf(smu->adev) &&
		    !msg_mapping.vawid_in_vf)
			wetuwn -EACCES;

		wetuwn msg_mapping.map_to;

	case CMN2ASIC_MAPPING_CWK:
		if (index >= SMU_CWK_COUNT ||
		    !smu->cwock_map)
			wetuwn -EINVAW;

		mapping = smu->cwock_map[index];
		if (!mapping.vawid_mapping)
			wetuwn -EINVAW;

		wetuwn mapping.map_to;

	case CMN2ASIC_MAPPING_FEATUWE:
		if (index >= SMU_FEATUWE_COUNT ||
		    !smu->featuwe_map)
			wetuwn -EINVAW;

		mapping = smu->featuwe_map[index];
		if (!mapping.vawid_mapping)
			wetuwn -EINVAW;

		wetuwn mapping.map_to;

	case CMN2ASIC_MAPPING_TABWE:
		if (index >= SMU_TABWE_COUNT ||
		    !smu->tabwe_map)
			wetuwn -EINVAW;

		mapping = smu->tabwe_map[index];
		if (!mapping.vawid_mapping)
			wetuwn -EINVAW;

		wetuwn mapping.map_to;

	case CMN2ASIC_MAPPING_PWW:
		if (index >= SMU_POWEW_SOUWCE_COUNT ||
		    !smu->pww_swc_map)
			wetuwn -EINVAW;

		mapping = smu->pww_swc_map[index];
		if (!mapping.vawid_mapping)
			wetuwn -EINVAW;

		wetuwn mapping.map_to;

	case CMN2ASIC_MAPPING_WOWKWOAD:
		if (index >= PP_SMC_POWEW_PWOFIWE_COUNT ||
		    !smu->wowkwoad_map)
			wetuwn -EINVAW;

		mapping = smu->wowkwoad_map[index];
		if (!mapping.vawid_mapping)
			wetuwn -ENOTSUPP;

		wetuwn mapping.map_to;

	defauwt:
		wetuwn -EINVAW;
	}
}

int smu_cmn_featuwe_is_suppowted(stwuct smu_context *smu,
				 enum smu_featuwe_mask mask)
{
	stwuct smu_featuwe *featuwe = &smu->smu_featuwe;
	int featuwe_id;

	featuwe_id = smu_cmn_to_asic_specific_index(smu,
						    CMN2ASIC_MAPPING_FEATUWE,
						    mask);
	if (featuwe_id < 0)
		wetuwn 0;

	WAWN_ON(featuwe_id > featuwe->featuwe_num);

	wetuwn test_bit(featuwe_id, featuwe->suppowted);
}

static int __smu_get_enabwed_featuwes(stwuct smu_context *smu,
			       uint64_t *enabwed_featuwes)
{
	wetuwn smu_cmn_caww_asic_func(get_enabwed_mask, smu, enabwed_featuwes);
}

int smu_cmn_featuwe_is_enabwed(stwuct smu_context *smu,
			       enum smu_featuwe_mask mask)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint64_t enabwed_featuwes;
	int featuwe_id;

	if (__smu_get_enabwed_featuwes(smu, &enabwed_featuwes)) {
		dev_eww(adev->dev, "Faiwed to wetwieve enabwed ppfeatuwes!\n");
		wetuwn 0;
	}

	/*
	 * Fow Wenoiw and Cyan Skiwwfish, they awe assumed to have aww featuwes
	 * enabwed. Awso considewing they have no featuwe_map avaiwabwe, the
	 * check hewe can avoid unwanted featuwe_map check bewow.
	 */
	if (enabwed_featuwes == UWWONG_MAX)
		wetuwn 1;

	featuwe_id = smu_cmn_to_asic_specific_index(smu,
						    CMN2ASIC_MAPPING_FEATUWE,
						    mask);
	if (featuwe_id < 0)
		wetuwn 0;

	wetuwn test_bit(featuwe_id, (unsigned wong *)&enabwed_featuwes);
}

boow smu_cmn_cwk_dpm_is_enabwed(stwuct smu_context *smu,
				enum smu_cwk_type cwk_type)
{
	enum smu_featuwe_mask featuwe_id = 0;

	switch (cwk_type) {
	case SMU_MCWK:
	case SMU_UCWK:
		featuwe_id = SMU_FEATUWE_DPM_UCWK_BIT;
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		featuwe_id = SMU_FEATUWE_DPM_GFXCWK_BIT;
		bweak;
	case SMU_SOCCWK:
		featuwe_id = SMU_FEATUWE_DPM_SOCCWK_BIT;
		bweak;
	case SMU_VCWK:
	case SMU_VCWK1:
		featuwe_id = SMU_FEATUWE_DPM_VCWK_BIT;
		bweak;
	case SMU_DCWK:
	case SMU_DCWK1:
		featuwe_id = SMU_FEATUWE_DPM_DCWK_BIT;
		bweak;
	case SMU_FCWK:
		featuwe_id = SMU_FEATUWE_DPM_FCWK_BIT;
		bweak;
	defauwt:
		wetuwn twue;
	}

	if (!smu_cmn_featuwe_is_enabwed(smu, featuwe_id))
		wetuwn fawse;

	wetuwn twue;
}

int smu_cmn_get_enabwed_mask(stwuct smu_context *smu,
			     uint64_t *featuwe_mask)
{
	uint32_t *featuwe_mask_high;
	uint32_t *featuwe_mask_wow;
	int wet = 0, index = 0;

	if (!featuwe_mask)
		wetuwn -EINVAW;

	featuwe_mask_wow = &((uint32_t *)featuwe_mask)[0];
	featuwe_mask_high = &((uint32_t *)featuwe_mask)[1];

	index = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_MSG,
						SMU_MSG_GetEnabwedSmuFeatuwes);
	if (index > 0) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_GetEnabwedSmuFeatuwes,
						      0,
						      featuwe_mask_wow);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_GetEnabwedSmuFeatuwes,
						      1,
						      featuwe_mask_high);
	} ewse {
		wet = smu_cmn_send_smc_msg(smu,
					   SMU_MSG_GetEnabwedSmuFeatuwesHigh,
					   featuwe_mask_high);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg(smu,
					   SMU_MSG_GetEnabwedSmuFeatuwesWow,
					   featuwe_mask_wow);
	}

	wetuwn wet;
}

uint64_t smu_cmn_get_indep_thwottwew_status(
					const unsigned wong dep_status,
					const uint8_t *thwottwew_map)
{
	uint64_t indep_status = 0;
	uint8_t dep_bit = 0;

	fow_each_set_bit(dep_bit, &dep_status, 32)
		indep_status |= 1UWW << thwottwew_map[dep_bit];

	wetuwn indep_status;
}

int smu_cmn_featuwe_update_enabwe_state(stwuct smu_context *smu,
					uint64_t featuwe_mask,
					boow enabwed)
{
	int wet = 0;

	if (enabwed) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						  SMU_MSG_EnabweSmuFeatuwesWow,
						  wowew_32_bits(featuwe_mask),
						  NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						  SMU_MSG_EnabweSmuFeatuwesHigh,
						  uppew_32_bits(featuwe_mask),
						  NUWW);
	} ewse {
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						  SMU_MSG_DisabweSmuFeatuwesWow,
						  wowew_32_bits(featuwe_mask),
						  NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						  SMU_MSG_DisabweSmuFeatuwesHigh,
						  uppew_32_bits(featuwe_mask),
						  NUWW);
	}

	wetuwn wet;
}

int smu_cmn_featuwe_set_enabwed(stwuct smu_context *smu,
				enum smu_featuwe_mask mask,
				boow enabwe)
{
	int featuwe_id;

	featuwe_id = smu_cmn_to_asic_specific_index(smu,
						    CMN2ASIC_MAPPING_FEATUWE,
						    mask);
	if (featuwe_id < 0)
		wetuwn -EINVAW;

	wetuwn smu_cmn_featuwe_update_enabwe_state(smu,
					       1UWW << featuwe_id,
					       enabwe);
}

#undef __SMU_DUMMY_MAP
#define __SMU_DUMMY_MAP(fea)	#fea
static const chaw *__smu_featuwe_names[] = {
	SMU_FEATUWE_MASKS
};

static const chaw *smu_get_featuwe_name(stwuct smu_context *smu,
					enum smu_featuwe_mask featuwe)
{
	if (featuwe < 0 || featuwe >= SMU_FEATUWE_COUNT)
		wetuwn "unknown smu featuwe";
	wetuwn __smu_featuwe_names[featuwe];
}

size_t smu_cmn_get_pp_featuwe_mask(stwuct smu_context *smu,
				   chaw *buf)
{
	int8_t sowt_featuwe[max(SMU_FEATUWE_COUNT, SMU_FEATUWE_MAX)];
	uint64_t featuwe_mask;
	int i, featuwe_index;
	uint32_t count = 0;
	size_t size = 0;

	if (__smu_get_enabwed_featuwes(smu, &featuwe_mask))
		wetuwn 0;

	size =  sysfs_emit_at(buf, size, "featuwes high: 0x%08x wow: 0x%08x\n",
			uppew_32_bits(featuwe_mask), wowew_32_bits(featuwe_mask));

	memset(sowt_featuwe, -1, sizeof(sowt_featuwe));

	fow (i = 0; i < SMU_FEATUWE_COUNT; i++) {
		featuwe_index = smu_cmn_to_asic_specific_index(smu,
							       CMN2ASIC_MAPPING_FEATUWE,
							       i);
		if (featuwe_index < 0)
			continue;

		sowt_featuwe[featuwe_index] = i;
	}

	size += sysfs_emit_at(buf, size, "%-2s. %-20s  %-3s : %-s\n",
			"No", "Featuwe", "Bit", "State");

	fow (featuwe_index = 0; featuwe_index < SMU_FEATUWE_MAX; featuwe_index++) {
		if (sowt_featuwe[featuwe_index] < 0)
			continue;

		size += sysfs_emit_at(buf, size, "%02d. %-20s (%2d) : %s\n",
				count++,
				smu_get_featuwe_name(smu, sowt_featuwe[featuwe_index]),
				featuwe_index,
				!!test_bit(featuwe_index, (unsigned wong *)&featuwe_mask) ?
				"enabwed" : "disabwed");
	}

	wetuwn size;
}

int smu_cmn_set_pp_featuwe_mask(stwuct smu_context *smu,
				uint64_t new_mask)
{
	int wet = 0;
	uint64_t featuwe_mask;
	uint64_t featuwe_2_enabwed = 0;
	uint64_t featuwe_2_disabwed = 0;

	wet = __smu_get_enabwed_featuwes(smu, &featuwe_mask);
	if (wet)
		wetuwn wet;

	featuwe_2_enabwed  = ~featuwe_mask & new_mask;
	featuwe_2_disabwed = featuwe_mask & ~new_mask;

	if (featuwe_2_enabwed) {
		wet = smu_cmn_featuwe_update_enabwe_state(smu,
							  featuwe_2_enabwed,
							  twue);
		if (wet)
			wetuwn wet;
	}
	if (featuwe_2_disabwed) {
		wet = smu_cmn_featuwe_update_enabwe_state(smu,
							  featuwe_2_disabwed,
							  fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/**
 * smu_cmn_disabwe_aww_featuwes_with_exception - disabwe aww dpm featuwes
 *                                               except this specified by
 *                                               @mask
 *
 * @smu:               smu_context pointew
 * @mask:              the dpm featuwe which shouwd not be disabwed
 *                     SMU_FEATUWE_COUNT: no exception, aww dpm featuwes
 *                     to disabwe
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int smu_cmn_disabwe_aww_featuwes_with_exception(stwuct smu_context *smu,
						enum smu_featuwe_mask mask)
{
	uint64_t featuwes_to_disabwe = U64_MAX;
	int skipped_featuwe_id;

	if (mask != SMU_FEATUWE_COUNT) {
		skipped_featuwe_id = smu_cmn_to_asic_specific_index(smu,
								    CMN2ASIC_MAPPING_FEATUWE,
								    mask);
		if (skipped_featuwe_id < 0)
			wetuwn -EINVAW;

		featuwes_to_disabwe &= ~(1UWW << skipped_featuwe_id);
	}

	wetuwn smu_cmn_featuwe_update_enabwe_state(smu,
						   featuwes_to_disabwe,
						   0);
}

int smu_cmn_get_smc_vewsion(stwuct smu_context *smu,
			    uint32_t *if_vewsion,
			    uint32_t *smu_vewsion)
{
	int wet = 0;

	if (!if_vewsion && !smu_vewsion)
		wetuwn -EINVAW;

	if (smu->smc_fw_if_vewsion && smu->smc_fw_vewsion)
	{
		if (if_vewsion)
			*if_vewsion = smu->smc_fw_if_vewsion;

		if (smu_vewsion)
			*smu_vewsion = smu->smc_fw_vewsion;

		wetuwn 0;
	}

	if (if_vewsion) {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetDwivewIfVewsion, if_vewsion);
		if (wet)
			wetuwn wet;

		smu->smc_fw_if_vewsion = *if_vewsion;
	}

	if (smu_vewsion) {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetSmuVewsion, smu_vewsion);
		if (wet)
			wetuwn wet;

		smu->smc_fw_vewsion = *smu_vewsion;
	}

	wetuwn wet;
}

int smu_cmn_update_tabwe(stwuct smu_context *smu,
			 enum smu_tabwe_id tabwe_index,
			 int awgument,
			 void *tabwe_data,
			 boow dwv2smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_tabwe *tabwe = &smu_tabwe->dwivew_tabwe;
	int tabwe_id = smu_cmn_to_asic_specific_index(smu,
						      CMN2ASIC_MAPPING_TABWE,
						      tabwe_index);
	uint32_t tabwe_size;
	int wet = 0;
	if (!tabwe_data || tabwe_id >= SMU_TABWE_COUNT || tabwe_id < 0)
		wetuwn -EINVAW;

	tabwe_size = smu_tabwe->tabwes[tabwe_index].size;

	if (dwv2smu) {
		memcpy(tabwe->cpu_addw, tabwe_data, tabwe_size);
		/*
		 * Fwush hdp cache: to guawd the content seen by
		 * GPU is consitent with CPU.
		 */
		amdgpu_asic_fwush_hdp(adev, NUWW);
	}

	wet = smu_cmn_send_smc_msg_with_pawam(smu, dwv2smu ?
					  SMU_MSG_TwansfewTabweDwam2Smu :
					  SMU_MSG_TwansfewTabweSmu2Dwam,
					  tabwe_id | ((awgument & 0xFFFF) << 16),
					  NUWW);
	if (wet)
		wetuwn wet;

	if (!dwv2smu) {
		amdgpu_asic_invawidate_hdp(adev, NUWW);
		memcpy(tabwe_data, tabwe->cpu_addw, tabwe_size);
	}

	wetuwn 0;
}

int smu_cmn_wwite_watewmawks_tabwe(stwuct smu_context *smu)
{
	void *watewmawks_tabwe = smu->smu_tabwe.watewmawks_tabwe;

	if (!watewmawks_tabwe)
		wetuwn -EINVAW;

	wetuwn smu_cmn_update_tabwe(smu,
				    SMU_TABWE_WATEWMAWKS,
				    0,
				    watewmawks_tabwe,
				    twue);
}

int smu_cmn_wwite_pptabwe(stwuct smu_context *smu)
{
	void *pptabwe = smu->smu_tabwe.dwivew_pptabwe;

	wetuwn smu_cmn_update_tabwe(smu,
				    SMU_TABWE_PPTABWE,
				    0,
				    pptabwe,
				    twue);
}

int smu_cmn_get_metwics_tabwe(stwuct smu_context *smu,
			      void *metwics_tabwe,
			      boow bypass_cache)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	uint32_t tabwe_size =
		smu_tabwe->tabwes[SMU_TABWE_SMU_METWICS].size;
	int wet = 0;

	if (bypass_cache ||
	    !smu_tabwe->metwics_time ||
	    time_aftew(jiffies, smu_tabwe->metwics_time + msecs_to_jiffies(1))) {
		wet = smu_cmn_update_tabwe(smu,
				       SMU_TABWE_SMU_METWICS,
				       0,
				       smu_tabwe->metwics_tabwe,
				       fawse);
		if (wet) {
			dev_info(smu->adev->dev, "Faiwed to expowt SMU metwics tabwe!\n");
			wetuwn wet;
		}
		smu_tabwe->metwics_time = jiffies;
	}

	if (metwics_tabwe)
		memcpy(metwics_tabwe, smu_tabwe->metwics_tabwe, tabwe_size);

	wetuwn 0;
}

int smu_cmn_get_combo_pptabwe(stwuct smu_context *smu)
{
	void *pptabwe = smu->smu_tabwe.combo_pptabwe;

	wetuwn smu_cmn_update_tabwe(smu,
				    SMU_TABWE_COMBO_PPTABWE,
				    0,
				    pptabwe,
				    fawse);
}

void smu_cmn_init_soft_gpu_metwics(void *tabwe, uint8_t fwev, uint8_t cwev)
{
	stwuct metwics_tabwe_headew *headew = (stwuct metwics_tabwe_headew *)tabwe;
	uint16_t stwuctuwe_size;

#define METWICS_VEWSION(a, b)	((a << 16) | b)

	switch (METWICS_VEWSION(fwev, cwev)) {
	case METWICS_VEWSION(1, 0):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_0);
		bweak;
	case METWICS_VEWSION(1, 1):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_1);
		bweak;
	case METWICS_VEWSION(1, 2):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_2);
		bweak;
	case METWICS_VEWSION(1, 3):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_3);
		bweak;
	case METWICS_VEWSION(1, 4):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_4);
		bweak;
	case METWICS_VEWSION(1, 5):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v1_5);
		bweak;
	case METWICS_VEWSION(2, 0):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v2_0);
		bweak;
	case METWICS_VEWSION(2, 1):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v2_1);
		bweak;
	case METWICS_VEWSION(2, 2):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v2_2);
		bweak;
	case METWICS_VEWSION(2, 3):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v2_3);
		bweak;
	case METWICS_VEWSION(2, 4):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v2_4);
		bweak;
	case METWICS_VEWSION(3, 0):
		stwuctuwe_size = sizeof(stwuct gpu_metwics_v3_0);
		bweak;
	defauwt:
		wetuwn;
	}

#undef METWICS_VEWSION

	memset(headew, 0xFF, stwuctuwe_size);

	headew->fowmat_wevision = fwev;
	headew->content_wevision = cwev;
	headew->stwuctuwe_size = stwuctuwe_size;

}

int smu_cmn_set_mp1_state(stwuct smu_context *smu,
			  enum pp_mp1_state mp1_state)
{
	enum smu_message_type msg;
	int wet;

	switch (mp1_state) {
	case PP_MP1_STATE_SHUTDOWN:
		msg = SMU_MSG_PwepaweMp1FowShutdown;
		bweak;
	case PP_MP1_STATE_UNWOAD:
		msg = SMU_MSG_PwepaweMp1FowUnwoad;
		bweak;
	case PP_MP1_STATE_WESET:
		msg = SMU_MSG_PwepaweMp1FowWeset;
		bweak;
	case PP_MP1_STATE_NONE:
	defauwt:
		wetuwn 0;
	}

	wet = smu_cmn_send_smc_msg(smu, msg, NUWW);
	if (wet)
		dev_eww(smu->adev->dev, "[PwepaweMp1] Faiwed!\n");

	wetuwn wet;
}

boow smu_cmn_is_audio_func_enabwed(stwuct amdgpu_device *adev)
{
	stwuct pci_dev *p = NUWW;
	boow snd_dwivew_woaded;

	/*
	 * If the ASIC comes with no audio function, we awways assume
	 * it is "enabwed".
	 */
	p = pci_get_domain_bus_and_swot(pci_domain_nw(adev->pdev->bus),
			adev->pdev->bus->numbew, 1);
	if (!p)
		wetuwn twue;

	snd_dwivew_woaded = pci_is_enabwed(p) ? twue : fawse;

	pci_dev_put(p);

	wetuwn snd_dwivew_woaded;
}
