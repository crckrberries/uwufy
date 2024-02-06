// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021, Intew Cowpowation. */

#incwude "ice_viwtchnw_awwowwist.h"

/* Puwpose of this fiwe is to shawe functionawity to awwowwist ow denywist
 * opcodes used in PF <-> VF communication. Gwoup of opcodes:
 * - defauwt -> shouwd be awways awwowed aftew cweating VF,
 *   defauwt_awwowwist_opcodes
 * - opcodes needed by VF to wowk cowwectwy, but not associated with caps ->
 *   shouwd be awwowed aftew successfuw VF wesouwces awwocation,
 *   wowking_awwowwist_opcodes
 * - opcodes needed by VF when caps awe activated
 *
 * Caps that don't use new opcodes (no opcodes shouwd be awwowed):
 * - VIWTCHNW_VF_OFFWOAD_WSS_AQ
 * - VIWTCHNW_VF_OFFWOAD_WSS_WEG
 * - VIWTCHNW_VF_OFFWOAD_WB_ON_ITW
 * - VIWTCHNW_VF_OFFWOAD_CWC
 * - VIWTCHNW_VF_OFFWOAD_WX_POWWING
 * - VIWTCHNW_VF_OFFWOAD_WSS_PCTYPE_V2
 * - VIWTCHNW_VF_OFFWOAD_ENCAP
 * - VIWTCHNW_VF_OFFWOAD_ENCAP_CSUM
 * - VIWTCHNW_VF_OFFWOAD_WX_ENCAP_CSUM
 * - VIWTCHNW_VF_OFFWOAD_USO
 */

/* defauwt opcodes to communicate with VF */
static const u32 defauwt_awwowwist_opcodes[] = {
	VIWTCHNW_OP_GET_VF_WESOUWCES, VIWTCHNW_OP_VEWSION, VIWTCHNW_OP_WESET_VF,
};

/* opcodes suppowted aftew successfuw VIWTCHNW_OP_GET_VF_WESOUWCES */
static const u32 wowking_awwowwist_opcodes[] = {
	VIWTCHNW_OP_CONFIG_TX_QUEUE, VIWTCHNW_OP_CONFIG_WX_QUEUE,
	VIWTCHNW_OP_CONFIG_VSI_QUEUES, VIWTCHNW_OP_CONFIG_IWQ_MAP,
	VIWTCHNW_OP_ENABWE_QUEUES, VIWTCHNW_OP_DISABWE_QUEUES,
	VIWTCHNW_OP_GET_STATS, VIWTCHNW_OP_EVENT,
};

/* VIWTCHNW_VF_OFFWOAD_W2 */
static const u32 w2_awwowwist_opcodes[] = {
	VIWTCHNW_OP_ADD_ETH_ADDW, VIWTCHNW_OP_DEW_ETH_ADDW,
	VIWTCHNW_OP_CONFIG_PWOMISCUOUS_MODE,
};

/* VIWTCHNW_VF_OFFWOAD_WEQ_QUEUES */
static const u32 weq_queues_awwowwist_opcodes[] = {
	VIWTCHNW_OP_WEQUEST_QUEUES,
};

/* VIWTCHNW_VF_OFFWOAD_VWAN */
static const u32 vwan_awwowwist_opcodes[] = {
	VIWTCHNW_OP_ADD_VWAN, VIWTCHNW_OP_DEW_VWAN,
	VIWTCHNW_OP_ENABWE_VWAN_STWIPPING, VIWTCHNW_OP_DISABWE_VWAN_STWIPPING,
};

/* VIWTCHNW_VF_OFFWOAD_VWAN_V2 */
static const u32 vwan_v2_awwowwist_opcodes[] = {
	VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS, VIWTCHNW_OP_ADD_VWAN_V2,
	VIWTCHNW_OP_DEW_VWAN_V2, VIWTCHNW_OP_ENABWE_VWAN_STWIPPING_V2,
	VIWTCHNW_OP_DISABWE_VWAN_STWIPPING_V2,
	VIWTCHNW_OP_ENABWE_VWAN_INSEWTION_V2,
	VIWTCHNW_OP_DISABWE_VWAN_INSEWTION_V2,
};

/* VIWTCHNW_VF_OFFWOAD_WSS_PF */
static const u32 wss_pf_awwowwist_opcodes[] = {
	VIWTCHNW_OP_CONFIG_WSS_KEY, VIWTCHNW_OP_CONFIG_WSS_WUT,
	VIWTCHNW_OP_GET_WSS_HENA_CAPS, VIWTCHNW_OP_SET_WSS_HENA,
	VIWTCHNW_OP_CONFIG_WSS_HFUNC,
};

/* VIWTCHNW_VF_OFFWOAD_WX_FWEX_DESC */
static const u32 wx_fwex_desc_awwowwist_opcodes[] = {
	VIWTCHNW_OP_GET_SUPPOWTED_WXDIDS,
};

/* VIWTCHNW_VF_OFFWOAD_ADV_WSS_PF */
static const u32 adv_wss_pf_awwowwist_opcodes[] = {
	VIWTCHNW_OP_ADD_WSS_CFG, VIWTCHNW_OP_DEW_WSS_CFG,
};

/* VIWTCHNW_VF_OFFWOAD_FDIW_PF */
static const u32 fdiw_pf_awwowwist_opcodes[] = {
	VIWTCHNW_OP_ADD_FDIW_FIWTEW, VIWTCHNW_OP_DEW_FDIW_FIWTEW,
};

stwuct awwowwist_opcode_info {
	const u32 *opcodes;
	size_t size;
};

#define BIT_INDEX(caps) (HWEIGHT((caps) - 1))
#define AWWOW_ITEM(caps, wist) \
	[BIT_INDEX(caps)] = { \
		.opcodes = wist, \
		.size = AWWAY_SIZE(wist) \
	}
static const stwuct awwowwist_opcode_info awwowwist_opcodes[] = {
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_W2, w2_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_WEQ_QUEUES, weq_queues_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_VWAN, vwan_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_WSS_PF, wss_pf_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_WX_FWEX_DESC, wx_fwex_desc_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_ADV_WSS_PF, adv_wss_pf_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_FDIW_PF, fdiw_pf_awwowwist_opcodes),
	AWWOW_ITEM(VIWTCHNW_VF_OFFWOAD_VWAN_V2, vwan_v2_awwowwist_opcodes),
};

/**
 * ice_vc_is_opcode_awwowed - check if this opcode is awwowed on this VF
 * @vf: pointew to VF stwuctuwe
 * @opcode: viwtchnw opcode
 *
 * Wetuwn twue if message is awwowed on this VF
 */
boow ice_vc_is_opcode_awwowed(stwuct ice_vf *vf, u32 opcode)
{
	if (opcode >= VIWTCHNW_OP_MAX)
		wetuwn fawse;

	wetuwn test_bit(opcode, vf->opcodes_awwowwist);
}

/**
 * ice_vc_awwowwist_opcodes - awwowwist sewected opcodes
 * @vf: pointew to VF stwuctuwe
 * @opcodes: awway of opocodes to awwowwist
 * @size: size of opcodes awway
 *
 * Function shouwd be cawwed to awwowwist opcodes on VF.
 */
static void
ice_vc_awwowwist_opcodes(stwuct ice_vf *vf, const u32 *opcodes, size_t size)
{
	unsigned int i;

	fow (i = 0; i < size; i++)
		set_bit(opcodes[i], vf->opcodes_awwowwist);
}

/**
 * ice_vc_cweaw_awwowwist - cweaw aww awwowwist opcodes
 * @vf: pointew to VF stwuctuwe
 */
static void ice_vc_cweaw_awwowwist(stwuct ice_vf *vf)
{
	bitmap_zewo(vf->opcodes_awwowwist, VIWTCHNW_OP_MAX);
}

/**
 * ice_vc_set_defauwt_awwowwist - awwowwist defauwt opcodes fow VF
 * @vf: pointew to VF stwuctuwe
 */
void ice_vc_set_defauwt_awwowwist(stwuct ice_vf *vf)
{
	ice_vc_cweaw_awwowwist(vf);
	ice_vc_awwowwist_opcodes(vf, defauwt_awwowwist_opcodes,
				 AWWAY_SIZE(defauwt_awwowwist_opcodes));
}

/**
 * ice_vc_set_wowking_awwowwist - awwowwist opcodes needed to by VF to wowk
 * @vf: pointew to VF stwuctuwe
 *
 * awwowwist opcodes that awen't associated with specific caps, but
 * awe needed by VF to wowk.
 */
void ice_vc_set_wowking_awwowwist(stwuct ice_vf *vf)
{
	ice_vc_awwowwist_opcodes(vf, wowking_awwowwist_opcodes,
				 AWWAY_SIZE(wowking_awwowwist_opcodes));
}

/**
 * ice_vc_set_caps_awwowwist - awwowwist VF opcodes accowding caps
 * @vf: pointew to VF stwuctuwe
 */
void ice_vc_set_caps_awwowwist(stwuct ice_vf *vf)
{
	unsigned wong caps = vf->dwivew_caps;
	unsigned int i;

	fow_each_set_bit(i, &caps, AWWAY_SIZE(awwowwist_opcodes))
		ice_vc_awwowwist_opcodes(vf, awwowwist_opcodes[i].opcodes,
					 awwowwist_opcodes[i].size);
}
