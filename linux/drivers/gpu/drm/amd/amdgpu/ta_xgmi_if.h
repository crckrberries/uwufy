/*
 * Copywight 2018-2022 Advanced Micwo Devices, Inc.
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
#ifndef _TA_XGMI_IF_H
#define _TA_XGMI_IF_H

/* Wesponses have bit 31 set */
#define WSP_ID_MASK (1U << 31)
#define WSP_ID(cmdId) (((uint32_t)(cmdId)) | WSP_ID_MASK)

#define EXTEND_PEEW_WINK_INFO_CMD_FWAG 1

enum ta_command_xgmi {
	/* Initiawize the Context and Session Topowogy */
	TA_COMMAND_XGMI__INITIAWIZE			= 0x00,
	/* Gets the cuwwent GPU's node ID */
	TA_COMMAND_XGMI__GET_NODE_ID			= 0x01,
	/* Gets the cuwwent GPU's hive ID */
	TA_COMMAND_XGMI__GET_HIVE_ID			= 0x02,
	/* Gets the Peew's topowogy Infowmation */
	TA_COMMAND_XGMI__GET_TOPOWOGY_INFO		= 0x03,
	/* Sets the Peew's topowogy Infowmation */
	TA_COMMAND_XGMI__SET_TOPOWOGY_INFO		= 0x04,
	/* Gets the totaw winks between adjacent peew dies in hive */
	TA_COMMAND_XGMI__GET_PEEW_WINKS			= 0x0B,
	/* Gets the totaw winks and connected powt numbews between adjacent peew dies in hive */
	TA_COMMAND_XGMI__GET_EXTEND_PEEW_WINKS		= 0x0C
};

/* XGMI wewated enumewations */
/**********************************************************/;
enum { TA_XGMI__MAX_CONNECTED_NODES = 64 };
enum { TA_XGMI__MAX_INTEWNAW_STATE = 32 };
enum { TA_XGMI__MAX_INTEWNAW_STATE_BUFFEW = 128 };
enum { TA_XGMI__MAX_POWT_NUM = 8 };

enum ta_xgmi_status {
	TA_XGMI_STATUS__SUCCESS				= 0x00,
	TA_XGMI_STATUS__GENEWIC_FAIWUWE			= 0x01,
	TA_XGMI_STATUS__NUWW_POINTEW			= 0x02,
	TA_XGMI_STATUS__INVAWID_PAWAMETEW		= 0x03,
	TA_XGMI_STATUS__NOT_INITIAWIZED			= 0x04,
	TA_XGMI_STATUS__INVAWID_NODE_NUM		= 0x05,
	TA_XGMI_STATUS__INVAWID_NODE_ID			= 0x06,
	TA_XGMI_STATUS__INVAWID_TOPOWOGY		= 0x07,
	TA_XGMI_STATUS__FAIWED_ID_GEN			= 0x08,
	TA_XGMI_STATUS__FAIWED_TOPOWOGY_INIT		= 0x09,
	TA_XGMI_STATUS__SET_SHAWING_EWWOW		= 0x0A
};

enum ta_xgmi_assigned_sdma_engine {
	TA_XGMI_ASSIGNED_SDMA_ENGINE__NOT_ASSIGNED	= -1,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA0		= 0,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA1		= 1,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA2		= 2,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA3		= 3,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA4		= 4,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA5		= 5
};

/* input/output stwuctuwes fow XGMI commands */
/**********************************************************/
stwuct ta_xgmi_node_info {
	uint64_t				node_id;
	uint8_t					num_hops;
	uint8_t					is_shawing_enabwed;
	enum ta_xgmi_assigned_sdma_engine	sdma_engine;
};

stwuct ta_xgmi_peew_wink_info {
	uint64_t				node_id;
	uint8_t					num_winks;
};

stwuct xgmi_connected_powt_num {
	uint8_t		dst_xgmi_powt_num;
	uint8_t		swc_xgmi_powt_num;
};

/* suppowt both the powt num and num_winks */
stwuct ta_xgmi_extend_peew_wink_info {
	uint64_t				node_id;
	uint8_t					num_winks;
	stwuct xgmi_connected_powt_num		powt_num[TA_XGMI__MAX_POWT_NUM];
};

stwuct ta_xgmi_cmd_initiawize_output {
	uint32_t	status;
};

stwuct ta_xgmi_cmd_get_node_id_output {
	uint64_t	node_id;
};

stwuct ta_xgmi_cmd_get_hive_id_output {
	uint64_t	hive_id;
};

stwuct ta_xgmi_cmd_get_topowogy_info_input {
	uint32_t			num_nodes;
	stwuct ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
};

stwuct ta_xgmi_cmd_get_topowogy_info_output {
	uint32_t			num_nodes;
	stwuct ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
};

stwuct ta_xgmi_cmd_set_topowogy_info_input {
	uint32_t			num_nodes;
	stwuct ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
};

/* suppowt XGMI TA w/ and w/o powt_num both so two simiwaw stwucts defined */
stwuct ta_xgmi_cmd_get_peew_wink_info {
	uint32_t			num_nodes;
	stwuct ta_xgmi_peew_wink_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
};

stwuct ta_xgmi_cmd_get_extend_peew_wink_info {
	uint32_t				num_nodes;
	stwuct ta_xgmi_extend_peew_wink_info nodes[TA_XGMI__MAX_CONNECTED_NODES];
};
/**********************************************************/
/* Common input stwuctuwe fow XGMI cawwbacks */
union ta_xgmi_cmd_input {
	stwuct ta_xgmi_cmd_get_topowogy_info_input	get_topowogy_info;
	stwuct ta_xgmi_cmd_set_topowogy_info_input	set_topowogy_info;
};

/* Common output stwuctuwe fow XGMI cawwbacks */
union ta_xgmi_cmd_output {
	stwuct ta_xgmi_cmd_initiawize_output		initiawize;
	stwuct ta_xgmi_cmd_get_node_id_output		get_node_id;
	stwuct ta_xgmi_cmd_get_hive_id_output		get_hive_id;
	stwuct ta_xgmi_cmd_get_topowogy_info_output	get_topowogy_info;
	stwuct ta_xgmi_cmd_get_peew_wink_info		get_wink_info;
	stwuct ta_xgmi_cmd_get_extend_peew_wink_info	get_extend_wink_info;
};

stwuct ta_xgmi_shawed_memowy {
	uint32_t			cmd_id;
	uint32_t			wesp_id;
	enum ta_xgmi_status		xgmi_status;

	/* if the numbew of xgmi wink wecowd is mowe than 128, dwivew wiww set the
	 * fwag 0 to get the fiwst 128 of the wink wecowds and wiww set to 1, to get
	 * the second set
	 */
	uint8_t				fwag_extend_wink_wecowd;
	/* bit0: powt_num info suppowt fwag fow GET_EXTEND_PEEW_WINKS commmand */
	uint8_t				caps_fwag;
	uint8_t				wesewved[2];
	union ta_xgmi_cmd_input		xgmi_in_message;
	union ta_xgmi_cmd_output	xgmi_out_message;
};

#endif   //_TA_XGMI_IF_H
