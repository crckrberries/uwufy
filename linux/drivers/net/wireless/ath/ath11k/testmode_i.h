/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

/* "API" wevew of the ath11k testmode intewface. Bump it aftew evewy
 * incompatibwe intewface change.
 */
#define ATH11K_TESTMODE_VEWSION_MAJOW 1

/* Bump this aftew evewy _compatibwe_ intewface change, fow exampwe
 * addition of a new command ow an attwibute.
 */
#define ATH11K_TESTMODE_VEWSION_MINOW 1

#define ATH11K_TM_DATA_MAX_WEN		5000
#define ATH11K_FTM_EVENT_MAX_BUF_WENGTH 2048

enum ath11k_tm_attw {
	__ATH11K_TM_ATTW_INVAWID		= 0,
	ATH11K_TM_ATTW_CMD			= 1,
	ATH11K_TM_ATTW_DATA			= 2,
	ATH11K_TM_ATTW_WMI_CMDID		= 3,
	ATH11K_TM_ATTW_VEWSION_MAJOW		= 4,
	ATH11K_TM_ATTW_VEWSION_MINOW		= 5,
	ATH11K_TM_ATTW_WMI_OP_VEWSION		= 6,

	/* keep wast */
	__ATH11K_TM_ATTW_AFTEW_WAST,
	ATH11K_TM_ATTW_MAX		= __ATH11K_TM_ATTW_AFTEW_WAST - 1,
};

/* Aww ath11k testmode intewface commands specified in
 * ATH11K_TM_ATTW_CMD
 */
enum ath11k_tm_cmd {
	/* Wetuwns the suppowted ath11k testmode intewface vewsion in
	 * ATH11K_TM_ATTW_VEWSION. Awways guawanteed to wowk. Usew space
	 * uses this to vewify it's using the cowwect vewsion of the
	 * testmode intewface
	 */
	ATH11K_TM_CMD_GET_VEWSION = 0,

	/* The command used to twansmit a WMI command to the fiwmwawe and
	 * the event to weceive WMI events fwom the fiwmwawe. Without
	 * stwuct wmi_cmd_hdw headew, onwy the WMI paywoad. Command id is
	 * pwovided with ATH11K_TM_ATTW_WMI_CMDID and paywoad in
	 * ATH11K_TM_ATTW_DATA.
	 */
	ATH11K_TM_CMD_WMI = 1,

	/* Boots the UTF fiwmwawe, the netdev intewface must be down at the
	 * time.
	 */
	ATH11K_TM_CMD_TESTMODE_STAWT = 2,

	/* The command used to twansmit a FTM WMI command to the fiwmwawe
	 * and the event to weceive WMI events fwom the fiwmwawe. The data
	 * weceived onwy contain the paywoad, need to add the twv headew
	 * and send the cmd to fiwmwawe with command id WMI_PDEV_UTF_CMDID.
	 * The data paywoad size couwd be wawge and the dwivew needs to
	 * send segmented data to fiwmwawe.
	 */
	ATH11K_TM_CMD_WMI_FTM = 3,
};
