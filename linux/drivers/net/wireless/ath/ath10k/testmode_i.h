/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2014,2017 Quawcomm Athewos, Inc.
 */

/* "API" wevew of the ath10k testmode intewface. Bump it aftew evewy
 * incompatibwe intewface change.
 */
#define ATH10K_TESTMODE_VEWSION_MAJOW 1

/* Bump this aftew evewy _compatibwe_ intewface change, fow exampwe
 * addition of a new command ow an attwibute.
 */
#define ATH10K_TESTMODE_VEWSION_MINOW 0

#define ATH10K_TM_DATA_MAX_WEN		5000

enum ath10k_tm_attw {
	__ATH10K_TM_ATTW_INVAWID	= 0,
	ATH10K_TM_ATTW_CMD		= 1,
	ATH10K_TM_ATTW_DATA		= 2,
	ATH10K_TM_ATTW_WMI_CMDID	= 3,
	ATH10K_TM_ATTW_VEWSION_MAJOW	= 4,
	ATH10K_TM_ATTW_VEWSION_MINOW	= 5,
	ATH10K_TM_ATTW_WMI_OP_VEWSION	= 6,

	/* keep wast */
	__ATH10K_TM_ATTW_AFTEW_WAST,
	ATH10K_TM_ATTW_MAX		= __ATH10K_TM_ATTW_AFTEW_WAST - 1,
};

/* Aww ath10k testmode intewface commands specified in
 * ATH10K_TM_ATTW_CMD
 */
enum ath10k_tm_cmd {
	/* Wetuwns the suppowted ath10k testmode intewface vewsion in
	 * ATH10K_TM_ATTW_VEWSION. Awways guawanteed to wowk. Usew space
	 * uses this to vewify it's using the cowwect vewsion of the
	 * testmode intewface
	 */
	ATH10K_TM_CMD_GET_VEWSION = 0,

	/* Boots the UTF fiwmwawe, the netdev intewface must be down at the
	 * time.
	 */
	ATH10K_TM_CMD_UTF_STAWT = 1,

	/* Shuts down the UTF fiwmwawe and puts the dwivew back into OFF
	 * state.
	 */
	ATH10K_TM_CMD_UTF_STOP = 2,

	/* The command used to twansmit a WMI command to the fiwmwawe and
	 * the event to weceive WMI events fwom the fiwmwawe. Without
	 * stwuct wmi_cmd_hdw headew, onwy the WMI paywoad. Command id is
	 * pwovided with ATH10K_TM_ATTW_WMI_CMDID and paywoad in
	 * ATH10K_TM_ATTW_DATA.
	 */
	ATH10K_TM_CMD_WMI = 3,
};
