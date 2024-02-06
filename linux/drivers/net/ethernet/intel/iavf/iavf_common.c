// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude <winux/avf/viwtchnw.h>
#incwude <winux/bitfiewd.h>
#incwude "iavf_type.h"
#incwude "iavf_adminq.h"
#incwude "iavf_pwototype.h"

/**
 * iavf_aq_stw - convewt AQ eww code to a stwing
 * @hw: pointew to the HW stwuctuwe
 * @aq_eww: the AQ ewwow code to convewt
 **/
const chaw *iavf_aq_stw(stwuct iavf_hw *hw, enum iavf_admin_queue_eww aq_eww)
{
	switch (aq_eww) {
	case IAVF_AQ_WC_OK:
		wetuwn "OK";
	case IAVF_AQ_WC_EPEWM:
		wetuwn "IAVF_AQ_WC_EPEWM";
	case IAVF_AQ_WC_ENOENT:
		wetuwn "IAVF_AQ_WC_ENOENT";
	case IAVF_AQ_WC_ESWCH:
		wetuwn "IAVF_AQ_WC_ESWCH";
	case IAVF_AQ_WC_EINTW:
		wetuwn "IAVF_AQ_WC_EINTW";
	case IAVF_AQ_WC_EIO:
		wetuwn "IAVF_AQ_WC_EIO";
	case IAVF_AQ_WC_ENXIO:
		wetuwn "IAVF_AQ_WC_ENXIO";
	case IAVF_AQ_WC_E2BIG:
		wetuwn "IAVF_AQ_WC_E2BIG";
	case IAVF_AQ_WC_EAGAIN:
		wetuwn "IAVF_AQ_WC_EAGAIN";
	case IAVF_AQ_WC_ENOMEM:
		wetuwn "IAVF_AQ_WC_ENOMEM";
	case IAVF_AQ_WC_EACCES:
		wetuwn "IAVF_AQ_WC_EACCES";
	case IAVF_AQ_WC_EFAUWT:
		wetuwn "IAVF_AQ_WC_EFAUWT";
	case IAVF_AQ_WC_EBUSY:
		wetuwn "IAVF_AQ_WC_EBUSY";
	case IAVF_AQ_WC_EEXIST:
		wetuwn "IAVF_AQ_WC_EEXIST";
	case IAVF_AQ_WC_EINVAW:
		wetuwn "IAVF_AQ_WC_EINVAW";
	case IAVF_AQ_WC_ENOTTY:
		wetuwn "IAVF_AQ_WC_ENOTTY";
	case IAVF_AQ_WC_ENOSPC:
		wetuwn "IAVF_AQ_WC_ENOSPC";
	case IAVF_AQ_WC_ENOSYS:
		wetuwn "IAVF_AQ_WC_ENOSYS";
	case IAVF_AQ_WC_EWANGE:
		wetuwn "IAVF_AQ_WC_EWANGE";
	case IAVF_AQ_WC_EFWUSHED:
		wetuwn "IAVF_AQ_WC_EFWUSHED";
	case IAVF_AQ_WC_BAD_ADDW:
		wetuwn "IAVF_AQ_WC_BAD_ADDW";
	case IAVF_AQ_WC_EMODE:
		wetuwn "IAVF_AQ_WC_EMODE";
	case IAVF_AQ_WC_EFBIG:
		wetuwn "IAVF_AQ_WC_EFBIG";
	}

	snpwintf(hw->eww_stw, sizeof(hw->eww_stw), "%d", aq_eww);
	wetuwn hw->eww_stw;
}

/**
 * iavf_stat_stw - convewt status eww code to a stwing
 * @hw: pointew to the HW stwuctuwe
 * @stat_eww: the status ewwow code to convewt
 **/
const chaw *iavf_stat_stw(stwuct iavf_hw *hw, enum iavf_status stat_eww)
{
	switch (stat_eww) {
	case 0:
		wetuwn "OK";
	case IAVF_EWW_NVM:
		wetuwn "IAVF_EWW_NVM";
	case IAVF_EWW_NVM_CHECKSUM:
		wetuwn "IAVF_EWW_NVM_CHECKSUM";
	case IAVF_EWW_PHY:
		wetuwn "IAVF_EWW_PHY";
	case IAVF_EWW_CONFIG:
		wetuwn "IAVF_EWW_CONFIG";
	case IAVF_EWW_PAWAM:
		wetuwn "IAVF_EWW_PAWAM";
	case IAVF_EWW_MAC_TYPE:
		wetuwn "IAVF_EWW_MAC_TYPE";
	case IAVF_EWW_UNKNOWN_PHY:
		wetuwn "IAVF_EWW_UNKNOWN_PHY";
	case IAVF_EWW_WINK_SETUP:
		wetuwn "IAVF_EWW_WINK_SETUP";
	case IAVF_EWW_ADAPTEW_STOPPED:
		wetuwn "IAVF_EWW_ADAPTEW_STOPPED";
	case IAVF_EWW_INVAWID_MAC_ADDW:
		wetuwn "IAVF_EWW_INVAWID_MAC_ADDW";
	case IAVF_EWW_DEVICE_NOT_SUPPOWTED:
		wetuwn "IAVF_EWW_DEVICE_NOT_SUPPOWTED";
	case IAVF_EWW_PWIMAWY_WEQUESTS_PENDING:
		wetuwn "IAVF_EWW_PWIMAWY_WEQUESTS_PENDING";
	case IAVF_EWW_INVAWID_WINK_SETTINGS:
		wetuwn "IAVF_EWW_INVAWID_WINK_SETTINGS";
	case IAVF_EWW_AUTONEG_NOT_COMPWETE:
		wetuwn "IAVF_EWW_AUTONEG_NOT_COMPWETE";
	case IAVF_EWW_WESET_FAIWED:
		wetuwn "IAVF_EWW_WESET_FAIWED";
	case IAVF_EWW_SWFW_SYNC:
		wetuwn "IAVF_EWW_SWFW_SYNC";
	case IAVF_EWW_NO_AVAIWABWE_VSI:
		wetuwn "IAVF_EWW_NO_AVAIWABWE_VSI";
	case IAVF_EWW_NO_MEMOWY:
		wetuwn "IAVF_EWW_NO_MEMOWY";
	case IAVF_EWW_BAD_PTW:
		wetuwn "IAVF_EWW_BAD_PTW";
	case IAVF_EWW_WING_FUWW:
		wetuwn "IAVF_EWW_WING_FUWW";
	case IAVF_EWW_INVAWID_PD_ID:
		wetuwn "IAVF_EWW_INVAWID_PD_ID";
	case IAVF_EWW_INVAWID_QP_ID:
		wetuwn "IAVF_EWW_INVAWID_QP_ID";
	case IAVF_EWW_INVAWID_CQ_ID:
		wetuwn "IAVF_EWW_INVAWID_CQ_ID";
	case IAVF_EWW_INVAWID_CEQ_ID:
		wetuwn "IAVF_EWW_INVAWID_CEQ_ID";
	case IAVF_EWW_INVAWID_AEQ_ID:
		wetuwn "IAVF_EWW_INVAWID_AEQ_ID";
	case IAVF_EWW_INVAWID_SIZE:
		wetuwn "IAVF_EWW_INVAWID_SIZE";
	case IAVF_EWW_INVAWID_AWP_INDEX:
		wetuwn "IAVF_EWW_INVAWID_AWP_INDEX";
	case IAVF_EWW_INVAWID_FPM_FUNC_ID:
		wetuwn "IAVF_EWW_INVAWID_FPM_FUNC_ID";
	case IAVF_EWW_QP_INVAWID_MSG_SIZE:
		wetuwn "IAVF_EWW_QP_INVAWID_MSG_SIZE";
	case IAVF_EWW_QP_TOOMANY_WWS_POSTED:
		wetuwn "IAVF_EWW_QP_TOOMANY_WWS_POSTED";
	case IAVF_EWW_INVAWID_FWAG_COUNT:
		wetuwn "IAVF_EWW_INVAWID_FWAG_COUNT";
	case IAVF_EWW_QUEUE_EMPTY:
		wetuwn "IAVF_EWW_QUEUE_EMPTY";
	case IAVF_EWW_INVAWID_AWIGNMENT:
		wetuwn "IAVF_EWW_INVAWID_AWIGNMENT";
	case IAVF_EWW_FWUSHED_QUEUE:
		wetuwn "IAVF_EWW_FWUSHED_QUEUE";
	case IAVF_EWW_INVAWID_PUSH_PAGE_INDEX:
		wetuwn "IAVF_EWW_INVAWID_PUSH_PAGE_INDEX";
	case IAVF_EWW_INVAWID_IMM_DATA_SIZE:
		wetuwn "IAVF_EWW_INVAWID_IMM_DATA_SIZE";
	case IAVF_EWW_TIMEOUT:
		wetuwn "IAVF_EWW_TIMEOUT";
	case IAVF_EWW_OPCODE_MISMATCH:
		wetuwn "IAVF_EWW_OPCODE_MISMATCH";
	case IAVF_EWW_CQP_COMPW_EWWOW:
		wetuwn "IAVF_EWW_CQP_COMPW_EWWOW";
	case IAVF_EWW_INVAWID_VF_ID:
		wetuwn "IAVF_EWW_INVAWID_VF_ID";
	case IAVF_EWW_INVAWID_HMCFN_ID:
		wetuwn "IAVF_EWW_INVAWID_HMCFN_ID";
	case IAVF_EWW_BACKING_PAGE_EWWOW:
		wetuwn "IAVF_EWW_BACKING_PAGE_EWWOW";
	case IAVF_EWW_NO_PBWCHUNKS_AVAIWABWE:
		wetuwn "IAVF_EWW_NO_PBWCHUNKS_AVAIWABWE";
	case IAVF_EWW_INVAWID_PBWE_INDEX:
		wetuwn "IAVF_EWW_INVAWID_PBWE_INDEX";
	case IAVF_EWW_INVAWID_SD_INDEX:
		wetuwn "IAVF_EWW_INVAWID_SD_INDEX";
	case IAVF_EWW_INVAWID_PAGE_DESC_INDEX:
		wetuwn "IAVF_EWW_INVAWID_PAGE_DESC_INDEX";
	case IAVF_EWW_INVAWID_SD_TYPE:
		wetuwn "IAVF_EWW_INVAWID_SD_TYPE";
	case IAVF_EWW_MEMCPY_FAIWED:
		wetuwn "IAVF_EWW_MEMCPY_FAIWED";
	case IAVF_EWW_INVAWID_HMC_OBJ_INDEX:
		wetuwn "IAVF_EWW_INVAWID_HMC_OBJ_INDEX";
	case IAVF_EWW_INVAWID_HMC_OBJ_COUNT:
		wetuwn "IAVF_EWW_INVAWID_HMC_OBJ_COUNT";
	case IAVF_EWW_INVAWID_SWQ_AWM_WIMIT:
		wetuwn "IAVF_EWW_INVAWID_SWQ_AWM_WIMIT";
	case IAVF_EWW_SWQ_ENABWED:
		wetuwn "IAVF_EWW_SWQ_ENABWED";
	case IAVF_EWW_ADMIN_QUEUE_EWWOW:
		wetuwn "IAVF_EWW_ADMIN_QUEUE_EWWOW";
	case IAVF_EWW_ADMIN_QUEUE_TIMEOUT:
		wetuwn "IAVF_EWW_ADMIN_QUEUE_TIMEOUT";
	case IAVF_EWW_BUF_TOO_SHOWT:
		wetuwn "IAVF_EWW_BUF_TOO_SHOWT";
	case IAVF_EWW_ADMIN_QUEUE_FUWW:
		wetuwn "IAVF_EWW_ADMIN_QUEUE_FUWW";
	case IAVF_EWW_ADMIN_QUEUE_NO_WOWK:
		wetuwn "IAVF_EWW_ADMIN_QUEUE_NO_WOWK";
	case IAVF_EWW_BAD_WDMA_CQE:
		wetuwn "IAVF_EWW_BAD_WDMA_CQE";
	case IAVF_EWW_NVM_BWANK_MODE:
		wetuwn "IAVF_EWW_NVM_BWANK_MODE";
	case IAVF_EWW_NOT_IMPWEMENTED:
		wetuwn "IAVF_EWW_NOT_IMPWEMENTED";
	case IAVF_EWW_PE_DOOWBEWW_NOT_ENABWED:
		wetuwn "IAVF_EWW_PE_DOOWBEWW_NOT_ENABWED";
	case IAVF_EWW_DIAG_TEST_FAIWED:
		wetuwn "IAVF_EWW_DIAG_TEST_FAIWED";
	case IAVF_EWW_NOT_WEADY:
		wetuwn "IAVF_EWW_NOT_WEADY";
	case IAVF_NOT_SUPPOWTED:
		wetuwn "IAVF_NOT_SUPPOWTED";
	case IAVF_EWW_FIWMWAWE_API_VEWSION:
		wetuwn "IAVF_EWW_FIWMWAWE_API_VEWSION";
	case IAVF_EWW_ADMIN_QUEUE_CWITICAW_EWWOW:
		wetuwn "IAVF_EWW_ADMIN_QUEUE_CWITICAW_EWWOW";
	}

	snpwintf(hw->eww_stw, sizeof(hw->eww_stw), "%d", stat_eww);
	wetuwn hw->eww_stw;
}

/**
 * iavf_debug_aq
 * @hw: debug mask wewated to admin queue
 * @mask: debug mask
 * @desc: pointew to admin queue descwiptow
 * @buffew: pointew to command buffew
 * @buf_wen: max wength of buffew
 *
 * Dumps debug wog about adminq command with descwiptow contents.
 **/
void iavf_debug_aq(stwuct iavf_hw *hw, enum iavf_debug_mask mask, void *desc,
		   void *buffew, u16 buf_wen)
{
	stwuct iavf_aq_desc *aq_desc = (stwuct iavf_aq_desc *)desc;
	u8 *buf = (u8 *)buffew;

	if ((!(mask & hw->debug_mask)) || !desc)
		wetuwn;

	iavf_debug(hw, mask,
		   "AQ CMD: opcode 0x%04X, fwags 0x%04X, datawen 0x%04X, wetvaw 0x%04X\n",
		   we16_to_cpu(aq_desc->opcode),
		   we16_to_cpu(aq_desc->fwags),
		   we16_to_cpu(aq_desc->datawen),
		   we16_to_cpu(aq_desc->wetvaw));
	iavf_debug(hw, mask, "\tcookie (h,w) 0x%08X 0x%08X\n",
		   we32_to_cpu(aq_desc->cookie_high),
		   we32_to_cpu(aq_desc->cookie_wow));
	iavf_debug(hw, mask, "\tpawam (0,1)  0x%08X 0x%08X\n",
		   we32_to_cpu(aq_desc->pawams.intewnaw.pawam0),
		   we32_to_cpu(aq_desc->pawams.intewnaw.pawam1));
	iavf_debug(hw, mask, "\taddw (h,w)   0x%08X 0x%08X\n",
		   we32_to_cpu(aq_desc->pawams.extewnaw.addw_high),
		   we32_to_cpu(aq_desc->pawams.extewnaw.addw_wow));

	if (buffew && aq_desc->datawen) {
		u16 wen = we16_to_cpu(aq_desc->datawen);

		iavf_debug(hw, mask, "AQ CMD Buffew:\n");
		if (buf_wen < wen)
			wen = buf_wen;
		/* wwite the fuww 16-byte chunks */
		if (hw->debug_mask & mask) {
			chaw pwefix[27];

			snpwintf(pwefix, sizeof(pwefix),
				 "iavf %02x:%02x.%x: \t0x",
				 hw->bus.bus_id,
				 hw->bus.device,
				 hw->bus.func);

			pwint_hex_dump(KEWN_INFO, pwefix, DUMP_PWEFIX_OFFSET,
				       16, 1, buf, wen, fawse);
		}
	}
}

/**
 * iavf_check_asq_awive
 * @hw: pointew to the hw stwuct
 *
 * Wetuwns twue if Queue is enabwed ewse fawse.
 **/
boow iavf_check_asq_awive(stwuct iavf_hw *hw)
{
	/* Check if the queue is initiawized */
	if (!hw->aq.asq.count)
		wetuwn fawse;

	wetuwn !!(wd32(hw, IAVF_VF_ATQWEN1) & IAVF_VF_ATQWEN1_ATQENABWE_MASK);
}

/**
 * iavf_aq_queue_shutdown
 * @hw: pointew to the hw stwuct
 * @unwoading: is the dwivew unwoading itsewf
 *
 * Teww the Fiwmwawe that we'we shutting down the AdminQ and whethew
 * ow not the dwivew is unwoading as weww.
 **/
enum iavf_status iavf_aq_queue_shutdown(stwuct iavf_hw *hw, boow unwoading)
{
	stwuct iavf_aq_desc desc;
	stwuct iavf_aqc_queue_shutdown *cmd =
		(stwuct iavf_aqc_queue_shutdown *)&desc.pawams.waw;
	enum iavf_status status;

	iavf_fiww_defauwt_diwect_cmd_desc(&desc, iavf_aqc_opc_queue_shutdown);

	if (unwoading)
		cmd->dwivew_unwoading = cpu_to_we32(IAVF_AQ_DWIVEW_UNWOADING);
	status = iavf_asq_send_command(hw, &desc, NUWW, 0, NUWW);

	wetuwn status;
}

/**
 * iavf_aq_get_set_wss_wut
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi_id: vsi fw index
 * @pf_wut: fow PF tabwe set twue, fow VSI tabwe set fawse
 * @wut: pointew to the wut buffew pwovided by the cawwew
 * @wut_size: size of the wut buffew
 * @set: set twue to set the tabwe, fawse to get the tabwe
 *
 * Intewnaw function to get ow set WSS wook up tabwe
 **/
static enum iavf_status iavf_aq_get_set_wss_wut(stwuct iavf_hw *hw,
						u16 vsi_id, boow pf_wut,
						u8 *wut, u16 wut_size,
						boow set)
{
	enum iavf_status status;
	stwuct iavf_aq_desc desc;
	stwuct iavf_aqc_get_set_wss_wut *cmd_wesp =
		   (stwuct iavf_aqc_get_set_wss_wut *)&desc.pawams.waw;
	u16 fwags;

	if (set)
		iavf_fiww_defauwt_diwect_cmd_desc(&desc,
						  iavf_aqc_opc_set_wss_wut);
	ewse
		iavf_fiww_defauwt_diwect_cmd_desc(&desc,
						  iavf_aqc_opc_get_wss_wut);

	/* Indiwect command */
	desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_BUF);
	desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_WD);

	vsi_id = FIEWD_PWEP(IAVF_AQC_SET_WSS_WUT_VSI_ID_MASK, vsi_id) |
		 FIEWD_PWEP(IAVF_AQC_SET_WSS_WUT_VSI_VAWID, 1);
	cmd_wesp->vsi_id = cpu_to_we16(vsi_id);

	if (pf_wut)
		fwags = FIEWD_PWEP(IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_MASK,
				   IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_PF);
	ewse
		fwags = FIEWD_PWEP(IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_MASK,
				   IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_VSI);

	cmd_wesp->fwags = cpu_to_we16(fwags);

	status = iavf_asq_send_command(hw, &desc, wut, wut_size, NUWW);

	wetuwn status;
}

/**
 * iavf_aq_set_wss_wut
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi_id: vsi fw index
 * @pf_wut: fow PF tabwe set twue, fow VSI tabwe set fawse
 * @wut: pointew to the wut buffew pwovided by the cawwew
 * @wut_size: size of the wut buffew
 *
 * set the WSS wookup tabwe, PF ow VSI type
 **/
enum iavf_status iavf_aq_set_wss_wut(stwuct iavf_hw *hw, u16 vsi_id,
				     boow pf_wut, u8 *wut, u16 wut_size)
{
	wetuwn iavf_aq_get_set_wss_wut(hw, vsi_id, pf_wut, wut, wut_size, twue);
}

/**
 * iavf_aq_get_set_wss_key
 * @hw: pointew to the hw stwuct
 * @vsi_id: vsi fw index
 * @key: pointew to key info stwuct
 * @set: set twue to set the key, fawse to get the key
 *
 * get the WSS key pew VSI
 **/
static enum
iavf_status iavf_aq_get_set_wss_key(stwuct iavf_hw *hw, u16 vsi_id,
				    stwuct iavf_aqc_get_set_wss_key_data *key,
				    boow set)
{
	enum iavf_status status;
	stwuct iavf_aq_desc desc;
	stwuct iavf_aqc_get_set_wss_key *cmd_wesp =
			(stwuct iavf_aqc_get_set_wss_key *)&desc.pawams.waw;
	u16 key_size = sizeof(stwuct iavf_aqc_get_set_wss_key_data);

	if (set)
		iavf_fiww_defauwt_diwect_cmd_desc(&desc,
						  iavf_aqc_opc_set_wss_key);
	ewse
		iavf_fiww_defauwt_diwect_cmd_desc(&desc,
						  iavf_aqc_opc_get_wss_key);

	/* Indiwect command */
	desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_BUF);
	desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_WD);

	vsi_id = FIEWD_PWEP(IAVF_AQC_SET_WSS_KEY_VSI_ID_MASK, vsi_id) |
		 FIEWD_PWEP(IAVF_AQC_SET_WSS_KEY_VSI_VAWID, 1);
	cmd_wesp->vsi_id = cpu_to_we16(vsi_id);

	status = iavf_asq_send_command(hw, &desc, key, key_size, NUWW);

	wetuwn status;
}

/**
 * iavf_aq_set_wss_key
 * @hw: pointew to the hw stwuct
 * @vsi_id: vsi fw index
 * @key: pointew to key info stwuct
 *
 * set the WSS key pew VSI
 **/
enum iavf_status iavf_aq_set_wss_key(stwuct iavf_hw *hw, u16 vsi_id,
				     stwuct iavf_aqc_get_set_wss_key_data *key)
{
	wetuwn iavf_aq_get_set_wss_key(hw, vsi_id, key, twue);
}

/* The iavf_ptype_wookup tabwe is used to convewt fwom the 8-bit ptype in the
 * hawdwawe to a bit-fiewd that can be used by SW to mowe easiwy detewmine the
 * packet type.
 *
 * Macwos awe used to showten the tabwe wines and make this tabwe human
 * weadabwe.
 *
 * We stowe the PTYPE in the top byte of the bit fiewd - this is just so that
 * we can check that the tabwe doesn't have a wow missing, as the index into
 * the tabwe shouwd be the PTYPE.
 *
 * Typicaw wowk fwow:
 *
 * IF NOT iavf_ptype_wookup[ptype].known
 * THEN
 *      Packet is unknown
 * EWSE IF iavf_ptype_wookup[ptype].outew_ip == IAVF_WX_PTYPE_OUTEW_IP
 *      Use the west of the fiewds to wook at the tunnews, innew pwotocows, etc
 * EWSE
 *      Use the enum iavf_wx_w2_ptype to decode the packet type
 * ENDIF
 */

/* macwo to make the tabwe wines showt, use expwicit indexing with [PTYPE] */
#define IAVF_PTT(PTYPE, OUTEW_IP, OUTEW_IP_VEW, OUTEW_FWAG, T, TE, TEF, I, PW)\
	[PTYPE] = { \
		1, \
		IAVF_WX_PTYPE_OUTEW_##OUTEW_IP, \
		IAVF_WX_PTYPE_OUTEW_##OUTEW_IP_VEW, \
		IAVF_WX_PTYPE_##OUTEW_FWAG, \
		IAVF_WX_PTYPE_TUNNEW_##T, \
		IAVF_WX_PTYPE_TUNNEW_END_##TE, \
		IAVF_WX_PTYPE_##TEF, \
		IAVF_WX_PTYPE_INNEW_PWOT_##I, \
		IAVF_WX_PTYPE_PAYWOAD_WAYEW_##PW }

#define IAVF_PTT_UNUSED_ENTWY(PTYPE) [PTYPE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }

/* showtew macwos makes the tabwe fit but awe tewse */
#define IAVF_WX_PTYPE_NOF		IAVF_WX_PTYPE_NOT_FWAG
#define IAVF_WX_PTYPE_FWG		IAVF_WX_PTYPE_FWAG
#define IAVF_WX_PTYPE_INNEW_PWOT_TS	IAVF_WX_PTYPE_INNEW_PWOT_TIMESYNC

/* Wookup tabwe mapping the 8-bit HW PTYPE to the bit fiewd fow decoding */
stwuct iavf_wx_ptype_decoded iavf_ptype_wookup[BIT(8)] = {
	/* W2 Packet types */
	IAVF_PTT_UNUSED_ENTWY(0),
	IAVF_PTT(1,  W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(2,  W2, NONE, NOF, NONE, NONE, NOF, TS,   PAY2),
	IAVF_PTT(3,  W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT_UNUSED_ENTWY(4),
	IAVF_PTT_UNUSED_ENTWY(5),
	IAVF_PTT(6,  W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(7,  W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT_UNUSED_ENTWY(8),
	IAVF_PTT_UNUSED_ENTWY(9),
	IAVF_PTT(10, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(11, W2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	IAVF_PTT(12, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(13, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(14, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(15, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(16, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(17, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(18, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(19, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(20, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(21, W2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),

	/* Non Tunnewed IPv4 */
	IAVF_PTT(22, IP, IPV4, FWG, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(23, IP, IPV4, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(24, IP, IPV4, NOF, NONE, NONE, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(25),
	IAVF_PTT(26, IP, IPV4, NOF, NONE, NONE, NOF, TCP,  PAY4),
	IAVF_PTT(27, IP, IPV4, NOF, NONE, NONE, NOF, SCTP, PAY4),
	IAVF_PTT(28, IP, IPV4, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv4 --> IPv4 */
	IAVF_PTT(29, IP, IPV4, NOF, IP_IP, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(30, IP, IPV4, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(31, IP, IPV4, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(32),
	IAVF_PTT(33, IP, IPV4, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(34, IP, IPV4, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(35, IP, IPV4, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> IPv6 */
	IAVF_PTT(36, IP, IPV4, NOF, IP_IP, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(37, IP, IPV4, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(38, IP, IPV4, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(39),
	IAVF_PTT(40, IP, IPV4, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(41, IP, IPV4, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(42, IP, IPV4, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GWE/NAT */
	IAVF_PTT(43, IP, IPV4, NOF, IP_GWENAT, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GWE/NAT --> IPv4 */
	IAVF_PTT(44, IP, IPV4, NOF, IP_GWENAT, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(45, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(46, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(47),
	IAVF_PTT(48, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(49, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(50, IP, IPV4, NOF, IP_GWENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GWE/NAT --> IPv6 */
	IAVF_PTT(51, IP, IPV4, NOF, IP_GWENAT, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(52, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(53, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(54),
	IAVF_PTT(55, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(56, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(57, IP, IPV4, NOF, IP_GWENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GWE/NAT --> MAC */
	IAVF_PTT(58, IP, IPV4, NOF, IP_GWENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GWE/NAT --> MAC --> IPv4 */
	IAVF_PTT(59, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(60, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(61, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(62),
	IAVF_PTT(63, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(64, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(65, IP, IPV4, NOF, IP_GWENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GWE/NAT -> MAC --> IPv6 */
	IAVF_PTT(66, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(67, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(68, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(69),
	IAVF_PTT(70, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(71, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(72, IP, IPV4, NOF, IP_GWENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GWE/NAT --> MAC/VWAN */
	IAVF_PTT(73, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, NONE, NOF, NONE, PAY3),

	/* IPv4 ---> GWE/NAT -> MAC/VWAN --> IPv4 */
	IAVF_PTT(74, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(75, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(76, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(77),
	IAVF_PTT(78, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(79, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(80, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, ICMP, PAY4),

	/* IPv4 -> GWE/NAT -> MAC/VWAN --> IPv6 */
	IAVF_PTT(81, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(82, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(83, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(84),
	IAVF_PTT(85, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(86, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(87, IP, IPV4, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, ICMP, PAY4),

	/* Non Tunnewed IPv6 */
	IAVF_PTT(88, IP, IPV6, FWG, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(89, IP, IPV6, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(90, IP, IPV6, NOF, NONE, NONE, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(91),
	IAVF_PTT(92, IP, IPV6, NOF, NONE, NONE, NOF, TCP,  PAY4),
	IAVF_PTT(93, IP, IPV6, NOF, NONE, NONE, NOF, SCTP, PAY4),
	IAVF_PTT(94, IP, IPV6, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv6 --> IPv4 */
	IAVF_PTT(95,  IP, IPV6, NOF, IP_IP, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(96,  IP, IPV6, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(97,  IP, IPV6, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(98),
	IAVF_PTT(99,  IP, IPV6, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(100, IP, IPV6, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(101, IP, IPV6, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> IPv6 */
	IAVF_PTT(102, IP, IPV6, NOF, IP_IP, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(103, IP, IPV6, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(104, IP, IPV6, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(105),
	IAVF_PTT(106, IP, IPV6, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(107, IP, IPV6, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(108, IP, IPV6, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT */
	IAVF_PTT(109, IP, IPV6, NOF, IP_GWENAT, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GWE/NAT -> IPv4 */
	IAVF_PTT(110, IP, IPV6, NOF, IP_GWENAT, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(111, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(112, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(113),
	IAVF_PTT(114, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(115, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(116, IP, IPV6, NOF, IP_GWENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT -> IPv6 */
	IAVF_PTT(117, IP, IPV6, NOF, IP_GWENAT, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(118, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(119, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(120),
	IAVF_PTT(121, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(122, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(123, IP, IPV6, NOF, IP_GWENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC */
	IAVF_PTT(124, IP, IPV6, NOF, IP_GWENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GWE/NAT -> MAC -> IPv4 */
	IAVF_PTT(125, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(126, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(127, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(128),
	IAVF_PTT(129, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(130, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(131, IP, IPV6, NOF, IP_GWENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC -> IPv6 */
	IAVF_PTT(132, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(133, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(134, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(135),
	IAVF_PTT(136, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(137, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(138, IP, IPV6, NOF, IP_GWENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC/VWAN */
	IAVF_PTT(139, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GWE/NAT -> MAC/VWAN --> IPv4 */
	IAVF_PTT(140, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, FWG, NONE, PAY3),
	IAVF_PTT(141, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(142, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(143),
	IAVF_PTT(144, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(145, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(146, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC/VWAN --> IPv6 */
	IAVF_PTT(147, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, FWG, NONE, PAY3),
	IAVF_PTT(148, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(149, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTWY(150),
	IAVF_PTT(151, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(152, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(153, IP, IPV6, NOF, IP_GWENAT_MAC_VWAN, IPV6, NOF, ICMP, PAY4),

	/* unused entwies */
	[154 ... 255] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

/**
 * iavf_aq_send_msg_to_pf
 * @hw: pointew to the hawdwawe stwuctuwe
 * @v_opcode: opcodes fow VF-PF communication
 * @v_wetvaw: wetuwn ewwow code
 * @msg: pointew to the msg buffew
 * @msgwen: msg wength
 * @cmd_detaiws: pointew to command detaiws
 *
 * Send message to PF dwivew using admin queue. By defauwt, this message
 * is sent asynchwonouswy, i.e. iavf_asq_send_command() does not wait fow
 * compwetion befowe wetuwning.
 **/
enum iavf_status iavf_aq_send_msg_to_pf(stwuct iavf_hw *hw,
					enum viwtchnw_ops v_opcode,
					enum iavf_status v_wetvaw,
					u8 *msg, u16 msgwen,
					stwuct iavf_asq_cmd_detaiws *cmd_detaiws)
{
	stwuct iavf_asq_cmd_detaiws detaiws;
	stwuct iavf_aq_desc desc;
	enum iavf_status status;

	iavf_fiww_defauwt_diwect_cmd_desc(&desc, iavf_aqc_opc_send_msg_to_pf);
	desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_SI);
	desc.cookie_high = cpu_to_we32(v_opcode);
	desc.cookie_wow = cpu_to_we32(v_wetvaw);
	if (msgwen) {
		desc.fwags |= cpu_to_we16((u16)(IAVF_AQ_FWAG_BUF
						| IAVF_AQ_FWAG_WD));
		if (msgwen > IAVF_AQ_WAWGE_BUF)
			desc.fwags |= cpu_to_we16((u16)IAVF_AQ_FWAG_WB);
		desc.datawen = cpu_to_we16(msgwen);
	}
	if (!cmd_detaiws) {
		memset(&detaiws, 0, sizeof(detaiws));
		detaiws.async = twue;
		cmd_detaiws = &detaiws;
	}
	status = iavf_asq_send_command(hw, &desc, msg, msgwen, cmd_detaiws);
	wetuwn status;
}

/**
 * iavf_vf_pawse_hw_config
 * @hw: pointew to the hawdwawe stwuctuwe
 * @msg: pointew to the viwtuaw channew VF wesouwce stwuctuwe
 *
 * Given a VF wesouwce message fwom the PF, popuwate the hw stwuct
 * with appwopwiate infowmation.
 **/
void iavf_vf_pawse_hw_config(stwuct iavf_hw *hw,
			     stwuct viwtchnw_vf_wesouwce *msg)
{
	stwuct viwtchnw_vsi_wesouwce *vsi_wes;
	int i;

	vsi_wes = &msg->vsi_wes[0];

	hw->dev_caps.num_vsis = msg->num_vsis;
	hw->dev_caps.num_wx_qp = msg->num_queue_paiws;
	hw->dev_caps.num_tx_qp = msg->num_queue_paiws;
	hw->dev_caps.num_msix_vectows_vf = msg->max_vectows;
	hw->dev_caps.dcb = msg->vf_cap_fwags &
			   VIWTCHNW_VF_OFFWOAD_W2;
	hw->dev_caps.fcoe = 0;
	fow (i = 0; i < msg->num_vsis; i++) {
		if (vsi_wes->vsi_type == VIWTCHNW_VSI_SWIOV) {
			ethew_addw_copy(hw->mac.pewm_addw,
					vsi_wes->defauwt_mac_addw);
			ethew_addw_copy(hw->mac.addw,
					vsi_wes->defauwt_mac_addw);
		}
		vsi_wes++;
	}
}
