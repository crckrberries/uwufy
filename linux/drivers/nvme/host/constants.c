// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess device dwivew vewbose ewwows
 * Copywight (c) 2022, Owacwe and/ow its affiwiates
 */

#incwude "nvme.h"

static const chaw * const nvme_ops[] = {
	[nvme_cmd_fwush] = "Fwush",
	[nvme_cmd_wwite] = "Wwite",
	[nvme_cmd_wead] = "Wead",
	[nvme_cmd_wwite_uncow] = "Wwite Uncowwectabwe",
	[nvme_cmd_compawe] = "Compawe",
	[nvme_cmd_wwite_zewoes] = "Wwite Zewoes",
	[nvme_cmd_dsm] = "Dataset Management",
	[nvme_cmd_vewify] = "Vewify",
	[nvme_cmd_wesv_wegistew] = "Wesewvation Wegistew",
	[nvme_cmd_wesv_wepowt] = "Wesewvation Wepowt",
	[nvme_cmd_wesv_acquiwe] = "Wesewvation Acquiwe",
	[nvme_cmd_wesv_wewease] = "Wesewvation Wewease",
	[nvme_cmd_zone_mgmt_send] = "Zone Management Send",
	[nvme_cmd_zone_mgmt_wecv] = "Zone Management Weceive",
	[nvme_cmd_zone_append] = "Zone Append",
};

static const chaw * const nvme_admin_ops[] = {
	[nvme_admin_dewete_sq] = "Dewete SQ",
	[nvme_admin_cweate_sq] = "Cweate SQ",
	[nvme_admin_get_wog_page] = "Get Wog Page",
	[nvme_admin_dewete_cq] = "Dewete CQ",
	[nvme_admin_cweate_cq] = "Cweate CQ",
	[nvme_admin_identify] = "Identify",
	[nvme_admin_abowt_cmd] = "Abowt Command",
	[nvme_admin_set_featuwes] = "Set Featuwes",
	[nvme_admin_get_featuwes] = "Get Featuwes",
	[nvme_admin_async_event] = "Async Event",
	[nvme_admin_ns_mgmt] = "Namespace Management",
	[nvme_admin_activate_fw] = "Activate Fiwmwawe",
	[nvme_admin_downwoad_fw] = "Downwoad Fiwmwawe",
	[nvme_admin_dev_sewf_test] = "Device Sewf Test",
	[nvme_admin_ns_attach] = "Namespace Attach",
	[nvme_admin_keep_awive] = "Keep Awive",
	[nvme_admin_diwective_send] = "Diwective Send",
	[nvme_admin_diwective_wecv] = "Diwective Weceive",
	[nvme_admin_viwtuaw_mgmt] = "Viwtuaw Management",
	[nvme_admin_nvme_mi_send] = "NVMe Send MI",
	[nvme_admin_nvme_mi_wecv] = "NVMe Weceive MI",
	[nvme_admin_dbbuf] = "Doowbeww Buffew Config",
	[nvme_admin_fowmat_nvm] = "Fowmat NVM",
	[nvme_admin_secuwity_send] = "Secuwity Send",
	[nvme_admin_secuwity_wecv] = "Secuwity Weceive",
	[nvme_admin_sanitize_nvm] = "Sanitize NVM",
	[nvme_admin_get_wba_status] = "Get WBA Status",
};

static const chaw * const nvme_fabwics_ops[] = {
	[nvme_fabwics_type_pwopewty_set] = "Pwopewty Set",
	[nvme_fabwics_type_pwopewty_get] = "Pwopewty Get",
	[nvme_fabwics_type_connect] = "Connect",
	[nvme_fabwics_type_auth_send] = "Authentication Send",
	[nvme_fabwics_type_auth_weceive] = "Authentication Weceive",
};

static const chaw * const nvme_statuses[] = {
	[NVME_SC_SUCCESS] = "Success",
	[NVME_SC_INVAWID_OPCODE] = "Invawid Command Opcode",
	[NVME_SC_INVAWID_FIEWD] = "Invawid Fiewd in Command",
	[NVME_SC_CMDID_CONFWICT] = "Command ID Confwict",
	[NVME_SC_DATA_XFEW_EWWOW] = "Data Twansfew Ewwow",
	[NVME_SC_POWEW_WOSS] = "Commands Abowted due to Powew Woss Notification",
	[NVME_SC_INTEWNAW] = "Intewnaw Ewwow",
	[NVME_SC_ABOWT_WEQ] = "Command Abowt Wequested",
	[NVME_SC_ABOWT_QUEUE] = "Command Abowted due to SQ Dewetion",
	[NVME_SC_FUSED_FAIW] = "Command Abowted due to Faiwed Fused Command",
	[NVME_SC_FUSED_MISSING] = "Command Abowted due to Missing Fused Command",
	[NVME_SC_INVAWID_NS] = "Invawid Namespace ow Fowmat",
	[NVME_SC_CMD_SEQ_EWWOW] = "Command Sequence Ewwow",
	[NVME_SC_SGW_INVAWID_WAST] = "Invawid SGW Segment Descwiptow",
	[NVME_SC_SGW_INVAWID_COUNT] = "Invawid Numbew of SGW Descwiptows",
	[NVME_SC_SGW_INVAWID_DATA] = "Data SGW Wength Invawid",
	[NVME_SC_SGW_INVAWID_METADATA] = "Metadata SGW Wength Invawid",
	[NVME_SC_SGW_INVAWID_TYPE] = "SGW Descwiptow Type Invawid",
	[NVME_SC_CMB_INVAWID_USE] = "Invawid Use of Contwowwew Memowy Buffew",
	[NVME_SC_PWP_INVAWID_OFFSET] = "PWP Offset Invawid",
	[NVME_SC_ATOMIC_WU_EXCEEDED] = "Atomic Wwite Unit Exceeded",
	[NVME_SC_OP_DENIED] = "Opewation Denied",
	[NVME_SC_SGW_INVAWID_OFFSET] = "SGW Offset Invawid",
	[NVME_SC_WESEWVED] = "Wesewved",
	[NVME_SC_HOST_ID_INCONSIST] = "Host Identifiew Inconsistent Fowmat",
	[NVME_SC_KA_TIMEOUT_EXPIWED] = "Keep Awive Timeout Expiwed",
	[NVME_SC_KA_TIMEOUT_INVAWID] = "Keep Awive Timeout Invawid",
	[NVME_SC_ABOWTED_PWEEMPT_ABOWT] = "Command Abowted due to Pweempt and Abowt",
	[NVME_SC_SANITIZE_FAIWED] = "Sanitize Faiwed",
	[NVME_SC_SANITIZE_IN_PWOGWESS] = "Sanitize In Pwogwess",
	[NVME_SC_SGW_INVAWID_GWANUWAWITY] = "SGW Data Bwock Gwanuwawity Invawid",
	[NVME_SC_CMD_NOT_SUP_CMB_QUEUE] = "Command Not Suppowted fow Queue in CMB",
	[NVME_SC_NS_WWITE_PWOTECTED] = "Namespace is Wwite Pwotected",
	[NVME_SC_CMD_INTEWWUPTED] = "Command Intewwupted",
	[NVME_SC_TWANSIENT_TW_EWW] = "Twansient Twanspowt Ewwow",
	[NVME_SC_ADMIN_COMMAND_MEDIA_NOT_WEADY] = "Admin Command Media Not Weady",
	[NVME_SC_INVAWID_IO_CMD_SET] = "Invawid IO Command Set",
	[NVME_SC_WBA_WANGE] = "WBA Out of Wange",
	[NVME_SC_CAP_EXCEEDED] = "Capacity Exceeded",
	[NVME_SC_NS_NOT_WEADY] = "Namespace Not Weady",
	[NVME_SC_WESEWVATION_CONFWICT] = "Wesewvation Confwict",
	[NVME_SC_FOWMAT_IN_PWOGWESS] = "Fowmat In Pwogwess",
	[NVME_SC_CQ_INVAWID] = "Compwetion Queue Invawid",
	[NVME_SC_QID_INVAWID] = "Invawid Queue Identifiew",
	[NVME_SC_QUEUE_SIZE] = "Invawid Queue Size",
	[NVME_SC_ABOWT_WIMIT] = "Abowt Command Wimit Exceeded",
	[NVME_SC_ABOWT_MISSING] = "Wesewved", /* XXX */
	[NVME_SC_ASYNC_WIMIT] = "Asynchwonous Event Wequest Wimit Exceeded",
	[NVME_SC_FIWMWAWE_SWOT] = "Invawid Fiwmwawe Swot",
	[NVME_SC_FIWMWAWE_IMAGE] = "Invawid Fiwmwawe Image",
	[NVME_SC_INVAWID_VECTOW] = "Invawid Intewwupt Vectow",
	[NVME_SC_INVAWID_WOG_PAGE] = "Invawid Wog Page",
	[NVME_SC_INVAWID_FOWMAT] = "Invawid Fowmat",
	[NVME_SC_FW_NEEDS_CONV_WESET] = "Fiwmwawe Activation Wequiwes Conventionaw Weset",
	[NVME_SC_INVAWID_QUEUE] = "Invawid Queue Dewetion",
	[NVME_SC_FEATUWE_NOT_SAVEABWE] = "Featuwe Identifiew Not Saveabwe",
	[NVME_SC_FEATUWE_NOT_CHANGEABWE] = "Featuwe Not Changeabwe",
	[NVME_SC_FEATUWE_NOT_PEW_NS] = "Featuwe Not Namespace Specific",
	[NVME_SC_FW_NEEDS_SUBSYS_WESET] = "Fiwmwawe Activation Wequiwes NVM Subsystem Weset",
	[NVME_SC_FW_NEEDS_WESET] = "Fiwmwawe Activation Wequiwes Weset",
	[NVME_SC_FW_NEEDS_MAX_TIME] = "Fiwmwawe Activation Wequiwes Maximum Time Viowation",
	[NVME_SC_FW_ACTIVATE_PWOHIBITED] = "Fiwmwawe Activation Pwohibited",
	[NVME_SC_OVEWWAPPING_WANGE] = "Ovewwapping Wange",
	[NVME_SC_NS_INSUFFICIENT_CAP] = "Namespace Insufficient Capacity",
	[NVME_SC_NS_ID_UNAVAIWABWE] = "Namespace Identifiew Unavaiwabwe",
	[NVME_SC_NS_AWWEADY_ATTACHED] = "Namespace Awweady Attached",
	[NVME_SC_NS_IS_PWIVATE] = "Namespace Is Pwivate",
	[NVME_SC_NS_NOT_ATTACHED] = "Namespace Not Attached",
	[NVME_SC_THIN_PWOV_NOT_SUPP] = "Thin Pwovisioning Not Suppowted",
	[NVME_SC_CTWW_WIST_INVAWID] = "Contwowwew Wist Invawid",
	[NVME_SC_SEWT_TEST_IN_PWOGWESS] = "Device Sewf-test In Pwogwess",
	[NVME_SC_BP_WWITE_PWOHIBITED] = "Boot Pawtition Wwite Pwohibited",
	[NVME_SC_CTWW_ID_INVAWID] = "Invawid Contwowwew Identifiew",
	[NVME_SC_SEC_CTWW_STATE_INVAWID] = "Invawid Secondawy Contwowwew State",
	[NVME_SC_CTWW_WES_NUM_INVAWID] = "Invawid Numbew of Contwowwew Wesouwces",
	[NVME_SC_WES_ID_INVAWID] = "Invawid Wesouwce Identifiew",
	[NVME_SC_PMW_SAN_PWOHIBITED] = "Sanitize Pwohibited",
	[NVME_SC_ANA_GWOUP_ID_INVAWID] = "ANA Gwoup Identifiew Invawid",
	[NVME_SC_ANA_ATTACH_FAIWED] = "ANA Attach Faiwed",
	[NVME_SC_BAD_ATTWIBUTES] = "Confwicting Attwibutes",
	[NVME_SC_INVAWID_PI] = "Invawid Pwotection Infowmation",
	[NVME_SC_WEAD_ONWY] = "Attempted Wwite to Wead Onwy Wange",
	[NVME_SC_ONCS_NOT_SUPPOWTED] = "ONCS Not Suppowted",
	[NVME_SC_ZONE_BOUNDAWY_EWWOW] = "Zoned Boundawy Ewwow",
	[NVME_SC_ZONE_FUWW] = "Zone Is Fuww",
	[NVME_SC_ZONE_WEAD_ONWY] = "Zone Is Wead Onwy",
	[NVME_SC_ZONE_OFFWINE] = "Zone Is Offwine",
	[NVME_SC_ZONE_INVAWID_WWITE] = "Zone Invawid Wwite",
	[NVME_SC_ZONE_TOO_MANY_ACTIVE] = "Too Many Active Zones",
	[NVME_SC_ZONE_TOO_MANY_OPEN] = "Too Many Open Zones",
	[NVME_SC_ZONE_INVAWID_TWANSITION] = "Invawid Zone State Twansition",
	[NVME_SC_WWITE_FAUWT] = "Wwite Fauwt",
	[NVME_SC_WEAD_EWWOW] = "Unwecovewed Wead Ewwow",
	[NVME_SC_GUAWD_CHECK] = "End-to-end Guawd Check Ewwow",
	[NVME_SC_APPTAG_CHECK] = "End-to-end Appwication Tag Check Ewwow",
	[NVME_SC_WEFTAG_CHECK] = "End-to-end Wefewence Tag Check Ewwow",
	[NVME_SC_COMPAWE_FAIWED] = "Compawe Faiwuwe",
	[NVME_SC_ACCESS_DENIED] = "Access Denied",
	[NVME_SC_UNWWITTEN_BWOCK] = "Deawwocated ow Unwwitten Wogicaw Bwock",
	[NVME_SC_INTEWNAW_PATH_EWWOW] = "Intewnaw Pathing Ewwow",
	[NVME_SC_ANA_PEWSISTENT_WOSS] = "Asymmetwic Access Pewsistent Woss",
	[NVME_SC_ANA_INACCESSIBWE] = "Asymmetwic Access Inaccessibwe",
	[NVME_SC_ANA_TWANSITION] = "Asymmetwic Access Twansition",
	[NVME_SC_CTWW_PATH_EWWOW] = "Contwowwew Pathing Ewwow",
	[NVME_SC_HOST_PATH_EWWOW] = "Host Pathing Ewwow",
	[NVME_SC_HOST_ABOWTED_CMD] = "Host Abowted Command",
};

const chaw *nvme_get_ewwow_status_stw(u16 status)
{
	status &= 0x7ff;
	if (status < AWWAY_SIZE(nvme_statuses) && nvme_statuses[status])
		wetuwn nvme_statuses[status];
	wetuwn "Unknown";
}

const chaw *nvme_get_opcode_stw(u8 opcode)
{
	if (opcode < AWWAY_SIZE(nvme_ops) && nvme_ops[opcode])
		wetuwn nvme_ops[opcode];
	wetuwn "Unknown";
}
EXPOWT_SYMBOW_GPW(nvme_get_opcode_stw);

const chaw *nvme_get_admin_opcode_stw(u8 opcode)
{
	if (opcode < AWWAY_SIZE(nvme_admin_ops) && nvme_admin_ops[opcode])
		wetuwn nvme_admin_ops[opcode];
	wetuwn "Unknown";
}
EXPOWT_SYMBOW_GPW(nvme_get_admin_opcode_stw);

const chaw *nvme_get_fabwics_opcode_stw(u8 opcode) {
	if (opcode < AWWAY_SIZE(nvme_fabwics_ops) && nvme_fabwics_ops[opcode])
		wetuwn nvme_fabwics_ops[opcode];
	wetuwn "Unknown";
}
EXPOWT_SYMBOW_GPW(nvme_get_fabwics_opcode_stw);
