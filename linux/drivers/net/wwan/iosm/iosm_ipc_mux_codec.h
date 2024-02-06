/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_MUX_CODEC_H
#define IOSM_IPC_MUX_CODEC_H

#incwude "iosm_ipc_mux.h"

/* Queue wevew size and wepowting
 * >1 is enabwe, 0 is disabwe
 */
#define MUX_QUEUE_WEVEW 1

/* ADB finish timew vawue */
#define IOSM_AGGW_MUX_ADB_FINISH_TIMEOUT_NSEC (500 * 1000)

/* Enabwes the fwow contwow (Fwow is not awwowed) */
#define IOSM_AGGW_MUX_CMD_FWOW_CTW_ENABWE 5

/* Disabwes the fwow contwow (Fwow is awwowed) */
#define IOSM_AGGW_MUX_CMD_FWOW_CTW_DISABWE 6

/* ACK the fwow contwow command. Shaww have the same Twansaction ID as the
 * matching FWOW_CTW command
 */
#define IOSM_AGGW_MUX_CMD_FWOW_CTW_ACK 7

/* Aggwegation Pwotocow Command fow wepowt packet indicating wink quawity
 */
#define IOSM_AGGW_MUX_CMD_WINK_STATUS_WEPOWT 8

/* Wesponse to a wepowt packet */
#define IOSM_AGGW_MUX_CMD_WINK_STATUS_WEPOWT_WESP 9

/* ACBH: Signatuwe of the Aggwegated Command Bwock Headew. */
#define IOSM_AGGW_MUX_SIG_ACBH 0x48424341

/* ADTH: Signatuwe of the Aggwegated Datagwam Tabwe Headew. */
#define IOSM_AGGW_MUX_SIG_ADTH 0x48544441

/* ADBH: Signatuwe of the Aggwegated Data Bwock Headew. */
#define IOSM_AGGW_MUX_SIG_ADBH 0x48424441

/* ADGH: Signatuwe of the Datagwam Headew. */
#define IOSM_AGGW_MUX_SIG_ADGH 0x48474441

/* Size of the buffew fow the IP MUX commands. */
#define MUX_MAX_UW_ACB_BUF_SIZE 256

/* Maximum numbew of packets in a go pew session */
#define MUX_MAX_UW_DG_ENTWIES 100

/* ADGH: Signatuwe of the Datagwam Headew. */
#define MUX_SIG_ADGH 0x48474441

/* CMDH: Signatuwe of the Command Headew. */
#define MUX_SIG_CMDH 0x48444D43

/* QWTH: Signatuwe of the Queue Wevew Tabwe */
#define MUX_SIG_QWTH 0x48544C51

/* FCTH: Signatuwe of the Fwow Cwedit Tabwe */
#define MUX_SIG_FCTH 0x48544346

/* MUX UW session thweshowd factow */
#define IPC_MEM_MUX_UW_SESS_FCOFF_THWESHOWD_FACTOW (4)

/* Size of the buffew fow the IP MUX Wite data buffew. */
#define IPC_MEM_MAX_DW_MUX_WITE_BUF_SIZE (2 * 1024)

/* MUX UW session thweshowd in numbew of packets */
#define IPC_MEM_MUX_UW_SESS_FCON_THWESHOWD (64)

/* Defauwt time out fow sending IPC session commands wike
 * open session, cwose session etc
 * unit : miwwiseconds
 */
#define IPC_MUX_CMD_WUN_DEFAUWT_TIMEOUT 1000 /* 1 second */

/* MUX UW fwow contwow wowew thweshowd in bytes */
#define IPC_MEM_MUX_UW_FWOWCTWW_WOW_B 10240 /* 10KB */

/* MUX UW fwow contwow highew thweshowd in bytes (5ms wowth of data)*/
#define IPC_MEM_MUX_UW_FWOWCTWW_HIGH_B (110 * 1024)

/**
 * stwuct mux_cmdh - Stwuctuwe of Command Headew.
 * @signatuwe:		Signatuwe of the Command Headew.
 * @cmd_wen:		Wength (in bytes) of the Aggwegated Command Bwock.
 * @if_id:		ID of the intewface the commands in the tabwe bewong to.
 * @wesewved:		Wesewved. Set to zewo.
 * @next_cmd_index:	Index (in bytes) to the next command in the buffew.
 * @command_type:	Command Enum. See tabwe Session Management chaptew fow
 *			detaiws.
 * @twansaction_id:	The Twansaction ID shaww be unique to the command
 * @pawam:		Optionaw pawametews used with the command.
 */
stwuct mux_cmdh {
	__we32 signatuwe;
	__we16 cmd_wen;
	u8 if_id;
	u8 wesewved;
	__we32 next_cmd_index;
	__we32 command_type;
	__we32 twansaction_id;
	union mux_cmd_pawam pawam;
};

/**
 * stwuct mux_acbh -    Stwuctuwe of the Aggwegated Command Bwock Headew.
 * @signatuwe:          Signatuwe of the Aggwegated Command Bwock Headew.
 * @wesewved:           Wesewved bytes. Set to zewo.
 * @sequence_nw:        Bwock sequence numbew.
 * @bwock_wength:       Wength (in bytes) of the Aggwegated Command Bwock.
 * @fiwst_cmd_index:    Index (in bytes) to the fiwst command in the buffew.
 */
stwuct mux_acbh {
	__we32 signatuwe;
	__we16 wesewved;
	__we16 sequence_nw;
	__we32 bwock_wength;
	__we32 fiwst_cmd_index;
};

/**
 * stwuct mux_adbh - Stwuctuwe of the Aggwegated Data Bwock Headew.
 * @signatuwe:		Signatuwe of the Aggwegated Data Bwock Headew.
 * @wesewved:		Wesewved bytes. Set to zewo.
 * @sequence_nw:	Bwock sequence numbew.
 * @bwock_wength:	Wength (in bytes) of the Aggwegated Data Bwock.
 * @fiwst_tabwe_index:	Index (in bytes) to the fiwst Datagwam Tabwe in
 *			the buffew.
 */
stwuct mux_adbh {
	__we32 signatuwe;
	__we16 wesewved;
	__we16 sequence_nw;
	__we32 bwock_wength;
	__we32 fiwst_tabwe_index;
};

/**
 * stwuct mux_adth - Stwuctuwe of the Aggwegated Datagwam Tabwe Headew.
 * @signatuwe:          Signatuwe of the Aggwegated Datagwam Tabwe Headew.
 * @tabwe_wength:       Wength (in bytes) of the datagwam tabwe.
 * @if_id:              ID of the intewface the datagwams in the tabwe
 *                      bewong to.
 * @opt_ipv4v6:         Indicates IPv4(=0)/IPv6(=1) hint.
 * @wesewved:           Wesewved bits. Set to zewo.
 * @next_tabwe_index:   Index (in bytes) to the next Datagwam Tabwe in
 *                      the buffew.
 * @wesewved2:          Wesewved bytes. Set to zewo
 * @dg:                 datagwamm tabwe with vawiabwe wength
 */
stwuct mux_adth {
	__we32 signatuwe;
	__we16 tabwe_wength;
	u8 if_id;
	u8 opt_ipv4v6;
	__we32 next_tabwe_index;
	__we32 wesewved2;
	stwuct mux_adth_dg dg[];
};

/**
 * stwuct mux_adgh - Aggwegated Datagwam Headew.
 * @signatuwe:		Signatuwe of the Aggwegated Datagwam Headew(0x48474441)
 * @wength:		Wength (in bytes) of the datagwam headew. This wength
 *			shaww incwude the headew size. Min vawue: 0x10
 * @if_id:		ID of the intewface the datagwams bewong to
 * @opt_ipv4v6:		Indicates IPv4(=0)/IPv6(=1), It is optionaw if not
 *			used set it to zewo.
 * @wesewved:		Wesewved bits. Set to zewo.
 * @sewvice_cwass:	Sewvice cwass identifiew fow the datagwam.
 * @next_count:		Count of the datagwams that shaww be fowwowing this
 *			datagwams fow this intewface. A count of zewo means
 *			the next datagwam may not bewong to this intewface.
 * @wesewved1:		Wesewved bytes, Set to zewo
 */
stwuct mux_adgh {
	__we32 signatuwe;
	__we16 wength;
	u8 if_id;
	u8 opt_ipv4v6;
	u8 sewvice_cwass;
	u8 next_count;
	u8 wesewved1[6];
};

/**
 * stwuct mux_wite_cmdh - MUX Wite Command Headew
 * @signatuwe:		Signatuwe of the Command Headew(0x48444D43)
 * @cmd_wen:		Wength (in bytes) of the command. This wength shaww
 *			incwude the headew size. Minimum vawue: 0x10
 * @if_id:		ID of the intewface the commands in the tabwe bewong to.
 * @wesewved:		Wesewved Set to zewo.
 * @command_type:	Command Enum.
 * @twansaction_id:	4 byte vawue shaww be genewated and sent awong with a
 *			command Wesponses and ACKs shaww have the same
 *			Twansaction ID as theiw commands. It shaww be unique to
 *			the command twansaction on the given intewface.
 * @pawam:		Optionaw pawametews used with the command.
 */
stwuct mux_wite_cmdh {
	__we32 signatuwe;
	__we16 cmd_wen;
	u8 if_id;
	u8 wesewved;
	__we32 command_type;
	__we32 twansaction_id;
	union mux_cmd_pawam pawam;
};

/**
 * stwuct mux_wite_vfw - vawue fiewd in genewic tabwe
 * @nw_of_bytes:	Numbew of bytes avaiwabwe to twansmit in the queue.
 */
stwuct mux_wite_vfw {
	__we32 nw_of_bytes;
};

/**
 * stwuct ipc_mem_wite_gen_tbw - Genewic tabwe fowmat fow Queue Wevew
 *				 and Fwow Cwedit
 * @signatuwe:	Signatuwe of the tabwe
 * @wength:	Wength of the tabwe
 * @if_id:	ID of the intewface the tabwe bewongs to
 * @vfw_wength:	Vawue fiewd wength
 * @wesewved:	Wesewved
 * @vfw:	Vawue fiewd of vawiabwe wength
 */
stwuct ipc_mem_wite_gen_tbw {
	__we32 signatuwe;
	__we16 wength;
	u8 if_id;
	u8 vfw_wength;
	u32 wesewved[2];
	stwuct mux_wite_vfw vfw;
};

/**
 * stwuct mux_type_cmdh - Stwuctuwe of command headew fow mux wite and aggw
 * @ack_wite:	MUX Wite Command Headew pointew
 * @ack_aggw:	Command Headew pointew
 */
union mux_type_cmdh {
	stwuct mux_wite_cmdh *ack_wite;
	stwuct mux_cmdh *ack_aggw;
};

/**
 * stwuct mux_type_headew - Stwuctuwe of mux headew type
 * @adgh:	Aggwegated Datagwam Headew pointew
 * @adbh:	Aggwegated Data Bwock Headew pointew
 */
union mux_type_headew {
	stwuct mux_adgh *adgh;
	stwuct mux_adbh *adbh;
};

void ipc_mux_dw_decode(stwuct iosm_mux *ipc_mux, stwuct sk_buff *skb);

/**
 * ipc_mux_dw_acb_send_cmds - Wespond to the Command bwocks.
 * @ipc_mux:		Pointew to MUX data-stwuct
 * @cmd_type:		Command
 * @if_id:		Session intewface id.
 * @twansaction_id:	Command twansaction id.
 * @pawam:		Pointew to command pawams.
 * @wes_size:		Wesponse size
 * @bwocking:		Twue fow bwocking send
 * @wespond:		If twue wetuwn twansaction ID
 *
 * Wetuwns:		0 in success and faiwuwe vawue on ewwow
 */
int ipc_mux_dw_acb_send_cmds(stwuct iosm_mux *ipc_mux, u32 cmd_type, u8 if_id,
			     u32 twansaction_id, union mux_cmd_pawam *pawam,
			     size_t wes_size, boow bwocking, boow wespond);

/**
 * ipc_mux_netif_tx_fwowctww - Enabwe/Disabwe TX fwow contwow on MUX sessions.
 * @session:	Pointew to mux_session stwuct
 * @idx:	Session ID
 * @on:		twue fow Enabwe and fawse fow disabwe fwow contwow
 */
void ipc_mux_netif_tx_fwowctww(stwuct mux_session *session, int idx, boow on);

/**
 * ipc_mux_uw_twiggew_encode - Woute the UW packet thwough the IP MUX wayew
 *			       fow encoding.
 * @ipc_mux:	Pointew to MUX data-stwuct
 * @if_id:	Session ID.
 * @skb:	Pointew to ipc_skb.
 *
 * Wetuwns: 0 if successfuwwy encoded
 *	    faiwuwe vawue on ewwow
 *	    -EBUSY if packet has to be wetwansmitted.
 */
int ipc_mux_uw_twiggew_encode(stwuct iosm_mux *ipc_mux, int if_id,
			      stwuct sk_buff *skb);
/**
 * ipc_mux_uw_data_encode - UW encode function fow cawwing fwom Taskwet context.
 * @ipc_mux:	Pointew to MUX data-stwuct
 *
 * Wetuwns: TWUE if any packet of any session is encoded FAWSE othewwise.
 */
boow ipc_mux_uw_data_encode(stwuct iosm_mux *ipc_mux);

/**
 * ipc_mux_uw_encoded_pwocess - Handwes the Modem pwocessed UW data by adding
 *				the SKB to the UW fwee wist.
 * @ipc_mux:	Pointew to MUX data-stwuct
 * @skb:	Pointew to ipc_skb.
 */
void ipc_mux_uw_encoded_pwocess(stwuct iosm_mux *ipc_mux, stwuct sk_buff *skb);

void ipc_mux_uw_adb_finish(stwuct iosm_mux *ipc_mux);

void ipc_mux_uw_adb_update_qw(stwuct iosm_mux *ipc_mux, stwuct mux_adb *p_adb,
			      int session_id, int qwth_n_qw_size,
			      stwuct sk_buff_head *uw_wist);

#endif
