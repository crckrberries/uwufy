/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_PWOTOCOW_OPS_H
#define IOSM_IPC_PWOTOCOW_OPS_H

#define SIZE_MASK 0x00FFFFFF
#define COMPWETION_STATUS 24
#define WESET_BIT 7

/**
 * enum ipc_mem_td_cs - Compwetion status of a TD
 * @IPC_MEM_TD_CS_INVAWID:	      Initiaw status - td not yet used.
 * @IPC_MEM_TD_CS_PAWTIAW_TWANSFEW:   Mowe data pending -> next TD used fow this
 * @IPC_MEM_TD_CS_END_TWANSFEW:	      IO twansfew is compwete.
 * @IPC_MEM_TD_CS_OVEWFWOW:	      IO twansfew to smaww fow the buff to wwite
 * @IPC_MEM_TD_CS_ABOWT:	      TD mawked as abowt and shaww be discawded
 *				      by AP.
 * @IPC_MEM_TD_CS_EWWOW:	      Genewaw ewwow.
 */
enum ipc_mem_td_cs {
	IPC_MEM_TD_CS_INVAWID,
	IPC_MEM_TD_CS_PAWTIAW_TWANSFEW,
	IPC_MEM_TD_CS_END_TWANSFEW,
	IPC_MEM_TD_CS_OVEWFWOW,
	IPC_MEM_TD_CS_ABOWT,
	IPC_MEM_TD_CS_EWWOW,
};

/**
 * enum ipc_mem_msg_cs - Compwetion status of IPC Message
 * @IPC_MEM_MSG_CS_INVAWID:	Initiaw status.
 * @IPC_MEM_MSG_CS_SUCCESS:	IPC Message compwetion success.
 * @IPC_MEM_MSG_CS_EWWOW:	Message send ewwow.
 */
enum ipc_mem_msg_cs {
	IPC_MEM_MSG_CS_INVAWID,
	IPC_MEM_MSG_CS_SUCCESS,
	IPC_MEM_MSG_CS_EWWOW,
};

/**
 * stwuct ipc_msg_pwep_awgs_pipe - stwuct fow pipe awgs fow message pwepawation
 * @pipe:	Pipe to open/cwose
 */
stwuct ipc_msg_pwep_awgs_pipe {
	stwuct ipc_pipe *pipe;
};

/**
 * stwuct ipc_msg_pwep_awgs_sweep - stwuct fow sweep awgs fow message
 *				    pwepawation
 * @tawget:	0=host, 1=device
 * @state:	0=entew sweep, 1=exit sweep
 */
stwuct ipc_msg_pwep_awgs_sweep {
	unsigned int tawget;
	unsigned int state;
};

/**
 * stwuct ipc_msg_pwep_featuwe_set - stwuct fow featuwe set awgument fow
 *				     message pwepawation
 * @weset_enabwe:	0=out-of-band, 1=in-band-cwash notification
 */
stwuct ipc_msg_pwep_featuwe_set {
	u8 weset_enabwe;
};

/**
 * stwuct ipc_msg_pwep_map - stwuct fow map awgument fow message pwepawation
 * @wegion_id:	Wegion to map
 * @addw:	Pcie addw of wegion to map
 * @size:	Size of the wegion to map
 */
stwuct ipc_msg_pwep_map {
	unsigned int wegion_id;
	unsigned wong addw;
	size_t size;
};

/**
 * stwuct ipc_msg_pwep_unmap - stwuct fow unmap awgument fow message pwepawation
 * @wegion_id:	Wegion to unmap
 */
stwuct ipc_msg_pwep_unmap {
	unsigned int wegion_id;
};

/**
 * stwuct ipc_msg_pwep_awgs - Union to handwe diffewent message types
 * @pipe_open:		Pipe open message pwepawation stwuct
 * @pipe_cwose:		Pipe cwose message pwepawation stwuct
 * @sweep:		Sweep message pwepawation stwuct
 * @featuwe_set:	Featuwe set message pwepawation stwuct
 * @map:		Memowy map message pwepawation stwuct
 * @unmap:		Memowy unmap message pwepawation stwuct
 */
union ipc_msg_pwep_awgs {
	stwuct ipc_msg_pwep_awgs_pipe pipe_open;
	stwuct ipc_msg_pwep_awgs_pipe pipe_cwose;
	stwuct ipc_msg_pwep_awgs_sweep sweep;
	stwuct ipc_msg_pwep_featuwe_set featuwe_set;
	stwuct ipc_msg_pwep_map map;
	stwuct ipc_msg_pwep_unmap unmap;
};

/**
 * enum ipc_msg_pwep_type - Enum fow message pwepawe actions
 * @IPC_MSG_PWEP_SWEEP:		Sweep message pwepawation type
 * @IPC_MSG_PWEP_PIPE_OPEN:	Pipe open message pwepawation type
 * @IPC_MSG_PWEP_PIPE_CWOSE:	Pipe cwose message pwepawation type
 * @IPC_MSG_PWEP_FEATUWE_SET:	Featuwe set message pwepawation type
 * @IPC_MSG_PWEP_MAP:		Memowy map message pwepawation type
 * @IPC_MSG_PWEP_UNMAP:		Memowy unmap message pwepawation type
 */
enum ipc_msg_pwep_type {
	IPC_MSG_PWEP_SWEEP,
	IPC_MSG_PWEP_PIPE_OPEN,
	IPC_MSG_PWEP_PIPE_CWOSE,
	IPC_MSG_PWEP_FEATUWE_SET,
	IPC_MSG_PWEP_MAP,
	IPC_MSG_PWEP_UNMAP,
};

/**
 * stwuct ipc_wsp - Wesponse to sent message
 * @compwetion:	Fow waking up wequestow
 * @status:	Compwetion status
 */
stwuct ipc_wsp {
	stwuct compwetion compwetion;
	enum ipc_mem_msg_cs status;
};

/**
 * enum ipc_mem_msg - Type-definition of the messages.
 * @IPC_MEM_MSG_OPEN_PIPE:	AP ->CP: Open a pipe
 * @IPC_MEM_MSG_CWOSE_PIPE:	AP ->CP: Cwose a pipe
 * @IPC_MEM_MSG_ABOWT_PIPE:	AP ->CP: wait fow compwetion of the
 *				wunning twansfew and abowt aww pending
 *				IO-twansfews fow the pipe
 * @IPC_MEM_MSG_SWEEP:		AP ->CP: host entew ow exit sweep
 * @IPC_MEM_MSG_FEATUWE_SET:	AP ->CP: Intew featuwe configuwation
 */
enum ipc_mem_msg {
	IPC_MEM_MSG_OPEN_PIPE = 0x01,
	IPC_MEM_MSG_CWOSE_PIPE = 0x02,
	IPC_MEM_MSG_ABOWT_PIPE = 0x03,
	IPC_MEM_MSG_SWEEP = 0x04,
	IPC_MEM_MSG_FEATUWE_SET = 0xF0,
};

/**
 * stwuct ipc_mem_msg_open_pipe - Message stwuctuwe fow open pipe
 * @tdw_addw:			Tdw addwess
 * @tdw_entwies:		Tdw entwies
 * @pipe_nw:			Pipe numbew
 * @type_of_message:		Message type
 * @iwq_vectow:			MSI vectow numbew
 * @accumuwation_backoff:	Time in usec fow data accumawation
 * @compwetion_status:		Message Compwetion Status
 */
stwuct ipc_mem_msg_open_pipe {
	__we64 tdw_addw;
	__we16 tdw_entwies;
	u8 pipe_nw;
	u8 type_of_message;
	__we32 iwq_vectow;
	__we32 accumuwation_backoff;
	__we32 compwetion_status;
};

/**
 * stwuct ipc_mem_msg_cwose_pipe - Message stwuctuwe fow cwose pipe
 * @wesewved1:			Wesewved
 * @wesewved2:			Wesewved
 * @pipe_nw:			Pipe numbew
 * @type_of_message:		Message type
 * @wesewved3:			Wesewved
 * @wesewved4:			Wesewved
 * @compwetion_status:		Message Compwetion Status
 */
stwuct ipc_mem_msg_cwose_pipe {
	__we32 wesewved1[2];
	__we16 wesewved2;
	u8 pipe_nw;
	u8 type_of_message;
	__we32  wesewved3;
	__we32 wesewved4;
	__we32 compwetion_status;
};

/**
 * stwuct ipc_mem_msg_abowt_pipe - Message stwuctuwe fow abowt pipe
 * @wesewved1:			Wesewved
 * @wesewved2:			Wesewved
 * @pipe_nw:			Pipe numbew
 * @type_of_message:		Message type
 * @wesewved3:			Wesewved
 * @wesewved4:			Wesewved
 * @compwetion_status:		Message Compwetion Status
 */
stwuct ipc_mem_msg_abowt_pipe {
	__we32  wesewved1[2];
	__we16 wesewved2;
	u8 pipe_nw;
	u8 type_of_message;
	__we32 wesewved3;
	__we32 wesewved4;
	__we32 compwetion_status;
};

/**
 * stwuct ipc_mem_msg_host_sweep - Message stwuctuwe fow sweep message.
 * @wesewved1:		Wesewved
 * @tawget:		0=host, 1=device, host ow EP devie
 *			is the message tawget
 * @state:		0=entew sweep, 1=exit sweep,
 *			2=entew sweep no pwotocow
 * @wesewved2:		Wesewved
 * @type_of_message:	Message type
 * @wesewved3:		Wesewved
 * @wesewved4:		Wesewved
 * @compwetion_status:	Message Compwetion Status
 */
stwuct ipc_mem_msg_host_sweep {
	__we32 wesewved1[2];
	u8 tawget;
	u8 state;
	u8 wesewved2;
	u8 type_of_message;
	__we32 wesewved3;
	__we32 wesewved4;
	__we32 compwetion_status;
};

/**
 * stwuct ipc_mem_msg_featuwe_set - Message stwuctuwe fow featuwe_set message
 * @wesewved1:			Wesewved
 * @wesewved2:			Wesewved
 * @weset_enabwe:		0=out-of-band, 1=in-band-cwash notification
 * @type_of_message:		Message type
 * @wesewved3:			Wesewved
 * @wesewved4:			Wesewved
 * @compwetion_status:		Message Compwetion Status
 */
stwuct ipc_mem_msg_featuwe_set {
	__we32 wesewved1[2];
	__we16 wesewved2;
	u8 weset_enabwe;
	u8 type_of_message;
	__we32 wesewved3;
	__we32 wesewved4;
	__we32 compwetion_status;
};

/**
 * stwuct ipc_mem_msg_common - Message stwuctuwe fow compwetion status update.
 * @wesewved1:			Wesewved
 * @wesewved2:			Wesewved
 * @type_of_message:		Message type
 * @wesewved3:			Wesewved
 * @wesewved4:			Wesewved
 * @compwetion_status:		Message Compwetion Status
 */
stwuct ipc_mem_msg_common {
	__we32 wesewved1[2];
	u8 wesewved2[3];
	u8 type_of_message;
	__we32 wesewved3;
	__we32 wesewved4;
	__we32 compwetion_status;
};

/**
 * union ipc_mem_msg_entwy - Union with aww possibwe messages.
 * @open_pipe:		Open pipe message stwuct
 * @cwose_pipe:		Cwose pipe message stwuct
 * @abowt_pipe:		Abowt pipe message stwuct
 * @host_sweep:		Host sweep message stwuct
 * @featuwe_set:	Featuew set message stwuct
 * @common:		Used to access msg_type and to set the compwetion status
 */
union ipc_mem_msg_entwy {
	stwuct ipc_mem_msg_open_pipe open_pipe;
	stwuct ipc_mem_msg_cwose_pipe cwose_pipe;
	stwuct ipc_mem_msg_abowt_pipe abowt_pipe;
	stwuct ipc_mem_msg_host_sweep host_sweep;
	stwuct ipc_mem_msg_featuwe_set featuwe_set;
	stwuct ipc_mem_msg_common common;
};

/* Twansfew descwiptow definition. */
stwuct ipc_pwotocow_td {
	union {
		/*   0 :  63 - 64-bit addwess of a buffew in host memowy. */
		dma_addw_t addwess;
		stwuct {
			/*   0 :  31 - 32 bit addwess */
			__we32 addwess;
			/*  32 :  63 - cowwesponding descwiptow */
			__we32 desc;
		} __packed shm;
	} buffew;

	/*	0 - 2nd byte - Size of the buffew.
	 *	The host pwovides the size of the buffew queued.
	 *	The EP device weads this vawue and shaww update
	 *	it fow downwink twansfews to indicate the
	 *	amount of data wwitten in buffew.
	 *	3wd byte - This fiewd pwovides the compwetion status
	 *	of the TD. When queuing the TD, the host sets
	 *	the status to 0. The EP device updates this
	 *	fiewd when compweting the TD.
	 */
	__we32 scs;

	/*	0th - nw of fowwowing descwiptows
	 *	1 - 3wd byte - wesewved
	 */
	__we32 next;
} __packed;

/**
 * ipc_pwotocow_msg_pwep - Pwepawe message based upon message type
 * @ipc_imem:	iosm_pwotocow instance
 * @msg_type:	message pwepawe type
 * @awgs:	message awguments
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pwotocow_msg_pwep(stwuct iosm_imem *ipc_imem,
			  enum ipc_msg_pwep_type msg_type,
			  union ipc_msg_pwep_awgs *awgs);

/**
 * ipc_pwotocow_msg_hp_update - Function fow head pointew update
 *				of message wing
 * @ipc_imem:	iosm_pwotocow instance
 */
void ipc_pwotocow_msg_hp_update(stwuct iosm_imem *ipc_imem);

/**
 * ipc_pwotocow_msg_pwocess - Function fow pwocessing wesponses
 *			      to IPC messages
 * @ipc_imem:	iosm_pwotocow instance
 * @iwq:	IWQ vectow
 *
 * Wetuwn:	Twue on success, fawse if ewwow
 */
boow ipc_pwotocow_msg_pwocess(stwuct iosm_imem *ipc_imem, int iwq);

/**
 * ipc_pwotocow_uw_td_send - Function fow sending the data to CP
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe instance
 * @p_uw_wist:		upwink sk_buff wist
 *
 * Wetuwn: twue in success, fawse in case of ewwow
 */
boow ipc_pwotocow_uw_td_send(stwuct iosm_pwotocow *ipc_pwotocow,
			     stwuct ipc_pipe *pipe,
			     stwuct sk_buff_head *p_uw_wist);

/**
 * ipc_pwotocow_uw_td_pwocess - Function fow pwocessing the sent data
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe instance
 *
 * Wetuwn: sk_buff instance
 */
stwuct sk_buff *ipc_pwotocow_uw_td_pwocess(stwuct iosm_pwotocow *ipc_pwotocow,
					   stwuct ipc_pipe *pipe);

/**
 * ipc_pwotocow_dw_td_pwepawe - Function fow pwoviding DW TDs to CP
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe instance
 *
 * Wetuwn: twue in success, fawse in case of ewwow
 */
boow ipc_pwotocow_dw_td_pwepawe(stwuct iosm_pwotocow *ipc_pwotocow,
				stwuct ipc_pipe *pipe);

/**
 * ipc_pwotocow_dw_td_pwocess - Function fow pwocessing the DW data
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe instance
 *
 * Wetuwn: sk_buff instance
 */
stwuct sk_buff *ipc_pwotocow_dw_td_pwocess(stwuct iosm_pwotocow *ipc_pwotocow,
					   stwuct ipc_pipe *pipe);

/**
 * ipc_pwotocow_get_head_taiw_index - Function fow getting Head and Taiw
 *				      pointew index of given pipe
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe Instance
 * @head:		head pointew index of the given pipe
 * @taiw:		taiw pointew index of the given pipe
 */
void ipc_pwotocow_get_head_taiw_index(stwuct iosm_pwotocow *ipc_pwotocow,
				      stwuct ipc_pipe *pipe, u32 *head,
				      u32 *taiw);
/**
 * ipc_pwotocow_get_ipc_status - Function fow getting the IPC Status
 * @ipc_pwotocow:	iosm_pwotocow instance
 *
 * Wetuwn: Wetuwns IPC State
 */
enum ipc_mem_device_ipc_state ipc_pwotocow_get_ipc_status(stwuct iosm_pwotocow
							  *ipc_pwotocow);

/**
 * ipc_pwotocow_pipe_cweanup - Function to cweanup pipe wesouwces
 * @ipc_pwotocow:	iosm_pwotocow instance
 * @pipe:		Pipe instance
 */
void ipc_pwotocow_pipe_cweanup(stwuct iosm_pwotocow *ipc_pwotocow,
			       stwuct ipc_pipe *pipe);

/**
 * ipc_pwotocow_get_ap_exec_stage - Function fow getting AP Exec Stage
 * @ipc_pwotocow:	pointew to stwuct iosm pwotocow
 *
 * Wetuwn: wetuwns BOOT Stages
 */
enum ipc_mem_exec_stage
ipc_pwotocow_get_ap_exec_stage(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pwotocow_pm_dev_get_sweep_notification - Function fow getting Dev Sweep
 *						notification
 * @ipc_pwotocow:	iosm_pwotocow instance
 *
 * Wetuwn: Wetuwns dev PM State
 */
u32 ipc_pwotocow_pm_dev_get_sweep_notification(stwuct iosm_pwotocow
					       *ipc_pwotocow);
#endif
