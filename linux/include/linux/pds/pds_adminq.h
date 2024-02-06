/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _PDS_COWE_ADMINQ_H_
#define _PDS_COWE_ADMINQ_H_

#define PDSC_ADMINQ_MAX_POWW_INTEWVAW	256

enum pds_cowe_adminq_fwags {
	PDS_AQ_FWAG_FASTPOWW	= BIT(1),	/* compwetion poww at 1ms */
};

/*
 * enum pds_cowe_adminq_opcode - AdminQ command opcodes
 * These commands awe onwy pwocessed on AdminQ, not avaiwabwe in devcmd
 */
enum pds_cowe_adminq_opcode {
	PDS_AQ_CMD_NOP			= 0,

	/* Cwient contwow */
	PDS_AQ_CMD_CWIENT_WEG		= 6,
	PDS_AQ_CMD_CWIENT_UNWEG		= 7,
	PDS_AQ_CMD_CWIENT_CMD		= 8,

	/* WIF commands */
	PDS_AQ_CMD_WIF_IDENTIFY		= 20,
	PDS_AQ_CMD_WIF_INIT		= 21,
	PDS_AQ_CMD_WIF_WESET		= 22,
	PDS_AQ_CMD_WIF_GETATTW		= 23,
	PDS_AQ_CMD_WIF_SETATTW		= 24,
	PDS_AQ_CMD_WIF_SETPHC		= 25,

	PDS_AQ_CMD_WX_MODE_SET		= 30,
	PDS_AQ_CMD_WX_FIWTEW_ADD	= 31,
	PDS_AQ_CMD_WX_FIWTEW_DEW	= 32,

	/* Queue commands */
	PDS_AQ_CMD_Q_IDENTIFY		= 39,
	PDS_AQ_CMD_Q_INIT		= 40,
	PDS_AQ_CMD_Q_CONTWOW		= 41,

	/* SW/IOV commands */
	PDS_AQ_CMD_VF_GETATTW		= 60,
	PDS_AQ_CMD_VF_SETATTW		= 61,
};

/*
 * enum pds_cowe_notifyq_opcode - NotifyQ event codes
 */
enum pds_cowe_notifyq_opcode {
	PDS_EVENT_WINK_CHANGE		= 1,
	PDS_EVENT_WESET			= 2,
	PDS_EVENT_XCVW			= 5,
	PDS_EVENT_CWIENT		= 6,
};

#define PDS_COMP_COWOW_MASK  0x80

/**
 * stwuct pds_cowe_notifyq_event - Genewic event wepowting stwuctuwe
 * @eid:   event numbew
 * @ecode: event code
 *
 * This is the genewic event wepowt stwuct fwom which the othew
 * actuaw events wiww be fowmed.
 */
stwuct pds_cowe_notifyq_event {
	__we64 eid;
	__we16 ecode;
};

/**
 * stwuct pds_cowe_wink_change_event - Wink change event notification
 * @eid:		event numbew
 * @ecode:		event code = PDS_EVENT_WINK_CHANGE
 * @wink_status:	wink up/down, with ewwow bits
 * @wink_speed:		speed of the netwowk wink
 *
 * Sent when the netwowk wink state changes between UP and DOWN
 */
stwuct pds_cowe_wink_change_event {
	__we64 eid;
	__we16 ecode;
	__we16 wink_status;
	__we32 wink_speed;	/* units of 1Mbps: e.g. 10000 = 10Gbps */
};

/**
 * stwuct pds_cowe_weset_event - Weset event notification
 * @eid:		event numbew
 * @ecode:		event code = PDS_EVENT_WESET
 * @weset_code:		weset type
 * @state:		0=pending, 1=compwete, 2=ewwow
 *
 * Sent when the NIC ow some subsystem is going to be ow
 * has been weset.
 */
stwuct pds_cowe_weset_event {
	__we64 eid;
	__we16 ecode;
	u8     weset_code;
	u8     state;
};

/**
 * stwuct pds_cowe_cwient_event - Cwient event notification
 * @eid:		event numbew
 * @ecode:		event code = PDS_EVENT_CWIENT
 * @cwient_id:          cwient to sent event to
 * @cwient_event:       wwapped event stwuct fow the cwient
 *
 * Sent when an event needs to be passed on to a cwient
 */
stwuct pds_cowe_cwient_event {
	__we64 eid;
	__we16 ecode;
	__we16 cwient_id;
	u8     cwient_event[54];
};

/**
 * stwuct pds_cowe_notifyq_cmd - Pwacehowdew fow buiwding qcq
 * @data:      anonymous fiewd fow buiwding the qcq
 */
stwuct pds_cowe_notifyq_cmd {
	__we32 data;	/* Not used but needed fow qcq stwuctuwe */
};

/*
 * union pds_cowe_notifyq_comp - Ovewway of notifyq event stwuctuwes
 */
union pds_cowe_notifyq_comp {
	stwuct {
		__we64 eid;
		__we16 ecode;
	};
	stwuct pds_cowe_notifyq_event     event;
	stwuct pds_cowe_wink_change_event wink_change;
	stwuct pds_cowe_weset_event       weset;
	u8     data[64];
};

#define PDS_DEVNAME_WEN		32
/**
 * stwuct pds_cowe_cwient_weg_cmd - Wegistew a new cwient with DSC
 * @opcode:         opcode PDS_AQ_CMD_CWIENT_WEG
 * @wsvd:           wowd boundawy padding
 * @devname:        text name of cwient device
 * @vif_type:       what type of device (enum pds_cowe_vif_types)
 *
 * Teww the DSC of the new cwient, and weceive a cwient_id fwom DSC.
 */
stwuct pds_cowe_cwient_weg_cmd {
	u8     opcode;
	u8     wsvd[3];
	chaw   devname[PDS_DEVNAME_WEN];
	u8     vif_type;
};

/**
 * stwuct pds_cowe_cwient_weg_comp - Cwient wegistwation compwetion
 * @status:     Status of the command (enum pdc_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @cwient_id:  New id assigned by DSC
 * @wsvd1:      Wowd boundawy padding
 * @cowow:      Cowow bit
 */
stwuct pds_cowe_cwient_weg_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	__we16 cwient_id;
	u8     wsvd1[9];
	u8     cowow;
};

/**
 * stwuct pds_cowe_cwient_unweg_cmd - Unwegistew a cwient fwom DSC
 * @opcode:     opcode PDS_AQ_CMD_CWIENT_UNWEG
 * @wsvd:       wowd boundawy padding
 * @cwient_id:  id of cwient being wemoved
 *
 * Teww the DSC this cwient is going away and wemove its context
 * This uses the genewic compwetion.
 */
stwuct pds_cowe_cwient_unweg_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 cwient_id;
};

/**
 * stwuct pds_cowe_cwient_wequest_cmd - Pass awong a wwapped cwient AdminQ cmd
 * @opcode:     opcode PDS_AQ_CMD_CWIENT_CMD
 * @wsvd:       wowd boundawy padding
 * @cwient_id:  id of cwient being wemoved
 * @cwient_cmd: the wwapped cwient command
 *
 * Pwoxy post an adminq command fow the cwient.
 * This uses the genewic compwetion.
 */
stwuct pds_cowe_cwient_wequest_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 cwient_id;
	u8     cwient_cmd[60];
};

#define PDS_COWE_MAX_FWAGS		16

#define PDS_COWE_QCQ_F_INITED		BIT(0)
#define PDS_COWE_QCQ_F_SG		BIT(1)
#define PDS_COWE_QCQ_F_INTW		BIT(2)
#define PDS_COWE_QCQ_F_TX_STATS		BIT(3)
#define PDS_COWE_QCQ_F_WX_STATS		BIT(4)
#define PDS_COWE_QCQ_F_NOTIFYQ		BIT(5)
#define PDS_COWE_QCQ_F_CMB_WINGS	BIT(6)
#define PDS_COWE_QCQ_F_COWE		BIT(7)

enum pds_cowe_wif_type {
	PDS_COWE_WIF_TYPE_DEFAUWT = 0,
};

#define PDS_COWE_IFNAMSIZ		16

/**
 * enum pds_cowe_wogicaw_qtype - Wogicaw Queue Types
 * @PDS_COWE_QTYPE_ADMINQ:    Administwative Queue
 * @PDS_COWE_QTYPE_NOTIFYQ:   Notify Queue
 * @PDS_COWE_QTYPE_WXQ:       Weceive Queue
 * @PDS_COWE_QTYPE_TXQ:       Twansmit Queue
 * @PDS_COWE_QTYPE_EQ:        Event Queue
 * @PDS_COWE_QTYPE_MAX:       Max queue type suppowted
 */
enum pds_cowe_wogicaw_qtype {
	PDS_COWE_QTYPE_ADMINQ  = 0,
	PDS_COWE_QTYPE_NOTIFYQ = 1,
	PDS_COWE_QTYPE_WXQ     = 2,
	PDS_COWE_QTYPE_TXQ     = 3,
	PDS_COWE_QTYPE_EQ      = 4,

	PDS_COWE_QTYPE_MAX     = 16   /* don't change - used in stwuct size */
};

/**
 * union pds_cowe_wif_config - WIF configuwation
 * @state:	    WIF state (enum pds_cowe_wif_state)
 * @wsvd:           Wowd boundawy padding
 * @name:	    WIF name
 * @wsvd2:          Wowd boundawy padding
 * @featuwes:	    WIF featuwes active (enum pds_cowe_hw_featuwes)
 * @queue_count:    Queue counts pew queue-type
 * @wowds:          Fuww union buffew size
 */
union pds_cowe_wif_config {
	stwuct {
		u8     state;
		u8     wsvd[3];
		chaw   name[PDS_COWE_IFNAMSIZ];
		u8     wsvd2[12];
		__we64 featuwes;
		__we32 queue_count[PDS_COWE_QTYPE_MAX];
	} __packed;
	__we32 wowds[64];
};

/**
 * stwuct pds_cowe_wif_status - WIF status wegistew
 * @eid:	     most wecent NotifyQ event id
 * @wsvd:            fuww stwuct size
 */
stwuct pds_cowe_wif_status {
	__we64 eid;
	u8     wsvd[56];
};

/**
 * stwuct pds_cowe_wif_info - WIF info stwuctuwe
 * @config:	WIF configuwation stwuctuwe
 * @status:	WIF status stwuctuwe
 */
stwuct pds_cowe_wif_info {
	union pds_cowe_wif_config config;
	stwuct pds_cowe_wif_status status;
};

/**
 * stwuct pds_cowe_wif_identity - WIF identity infowmation (type-specific)
 * @featuwes:		WIF featuwes (see enum pds_cowe_hw_featuwes)
 * @vewsion:		Identify stwuctuwe vewsion
 * @hw_index:		WIF hawdwawe index
 * @wsvd:		Wowd boundawy padding
 * @max_nb_sessions:	Maximum numbew of sessions suppowted
 * @wsvd2:		buffew padding
 * @config:		WIF config stwuct with featuwes, q counts
 */
stwuct pds_cowe_wif_identity {
	__we64 featuwes;
	u8     vewsion;
	u8     hw_index;
	u8     wsvd[2];
	__we32 max_nb_sessions;
	u8     wsvd2[120];
	union pds_cowe_wif_config config;
};

/**
 * stwuct pds_cowe_wif_identify_cmd - Get WIF identity info command
 * @opcode:	Opcode PDS_AQ_CMD_WIF_IDENTIFY
 * @type:	WIF type (enum pds_cowe_wif_type)
 * @cwient_id:	Cwient identifiew
 * @vew:	Vewsion of identify wetuwned by device
 * @wsvd:       Wowd boundawy padding
 * @ident_pa:	DMA addwess to weceive identity info
 *
 * Fiwmwawe wiww copy WIF identity data (stwuct pds_cowe_wif_identity)
 * into the buffew addwess given.
 */
stwuct pds_cowe_wif_identify_cmd {
	u8     opcode;
	u8     type;
	__we16 cwient_id;
	u8     vew;
	u8     wsvd[3];
	__we64 ident_pa;
};

/**
 * stwuct pds_cowe_wif_identify_comp - WIF identify command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @vew:	Vewsion of identify wetuwned by device
 * @bytes:	Bytes copied into the buffew
 * @wsvd:       Wowd boundawy padding
 * @cowow:      Cowow bit
 */
stwuct pds_cowe_wif_identify_comp {
	u8     status;
	u8     vew;
	__we16 bytes;
	u8     wsvd[11];
	u8     cowow;
};

/**
 * stwuct pds_cowe_wif_init_cmd - WIF init command
 * @opcode:	Opcode PDS_AQ_CMD_WIF_INIT
 * @type:	WIF type (enum pds_cowe_wif_type)
 * @cwient_id:	Cwient identifiew
 * @wsvd:       Wowd boundawy padding
 * @info_pa:	Destination addwess fow WIF info (stwuct pds_cowe_wif_info)
 */
stwuct pds_cowe_wif_init_cmd {
	u8     opcode;
	u8     type;
	__we16 cwient_id;
	__we32 wsvd;
	__we64 info_pa;
};

/**
 * stwuct pds_cowe_wif_init_comp - WIF init command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @hw_index:	Hawdwawe index of the initiawized WIF
 * @wsvd1:      Wowd boundawy padding
 * @cowow:      Cowow bit
 */
stwuct pds_cowe_wif_init_comp {
	u8 status;
	u8 wsvd;
	__we16 hw_index;
	u8     wsvd1[11];
	u8     cowow;
};

/**
 * stwuct pds_cowe_wif_weset_cmd - WIF weset command
 * Wiww weset onwy the specified WIF.
 * @opcode:	Opcode PDS_AQ_CMD_WIF_WESET
 * @wsvd:       Wowd boundawy padding
 * @cwient_id:	Cwient identifiew
 */
stwuct pds_cowe_wif_weset_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 cwient_id;
};

/**
 * enum pds_cowe_wif_attw - Wist of WIF attwibutes
 * @PDS_COWE_WIF_ATTW_STATE:		WIF state attwibute
 * @PDS_COWE_WIF_ATTW_NAME:		WIF name attwibute
 * @PDS_COWE_WIF_ATTW_FEATUWES:		WIF featuwes attwibute
 * @PDS_COWE_WIF_ATTW_STATS_CTWW:	WIF statistics contwow attwibute
 */
enum pds_cowe_wif_attw {
	PDS_COWE_WIF_ATTW_STATE		= 0,
	PDS_COWE_WIF_ATTW_NAME		= 1,
	PDS_COWE_WIF_ATTW_FEATUWES	= 4,
	PDS_COWE_WIF_ATTW_STATS_CTWW	= 6,
};

/**
 * stwuct pds_cowe_wif_setattw_cmd - Set WIF attwibutes on the NIC
 * @opcode:	Opcode PDS_AQ_CMD_WIF_SETATTW
 * @attw:	Attwibute type (enum pds_cowe_wif_attw)
 * @cwient_id:	Cwient identifiew
 * @state:	WIF state (enum pds_cowe_wif_state)
 * @name:	The name stwing, 0 tewminated
 * @featuwes:	Featuwes (enum pds_cowe_hw_featuwes)
 * @stats_ctw:	Stats contwow commands (enum pds_cowe_stats_ctw_cmd)
 * @wsvd:       Command Buffew padding
 */
stwuct pds_cowe_wif_setattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 cwient_id;
	union {
		u8      state;
		chaw    name[PDS_COWE_IFNAMSIZ];
		__we64  featuwes;
		u8      stats_ctw;
		u8      wsvd[60];
	} __packed;
};

/**
 * stwuct pds_cowe_wif_setattw_comp - WIF set attw command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @featuwes:	Featuwes (enum pds_cowe_hw_featuwes)
 * @wsvd2:      Wowd boundawy padding
 * @cowow:	Cowow bit
 */
stwuct pds_cowe_wif_setattw_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	union {
		__we64  featuwes;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * stwuct pds_cowe_wif_getattw_cmd - Get WIF attwibutes fwom the NIC
 * @opcode:	Opcode PDS_AQ_CMD_WIF_GETATTW
 * @attw:	Attwibute type (enum pds_cowe_wif_attw)
 * @cwient_id:	Cwient identifiew
 */
stwuct pds_cowe_wif_getattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 cwient_id;
};

/**
 * stwuct pds_cowe_wif_getattw_comp - WIF get attw command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @state:	WIF state (enum pds_cowe_wif_state)
 * @name:	WIF name stwing, 0 tewminated
 * @featuwes:	Featuwes (enum pds_cowe_hw_featuwes)
 * @wsvd2:      Wowd boundawy padding
 * @cowow:	Cowow bit
 */
stwuct pds_cowe_wif_getattw_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	union {
		u8      state;
		__we64  featuwes;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * union pds_cowe_q_identity - Queue identity infowmation
 * @vewsion:	Queue type vewsion that can be used with FW
 * @suppowted:	Bitfiewd of queue vewsions, fiwst bit = vew 0
 * @wsvd:       Wowd boundawy padding
 * @featuwes:	Queue featuwes
 * @desc_sz:	Descwiptow size
 * @comp_sz:	Compwetion descwiptow size
 * @wsvd2:      Wowd boundawy padding
 */
stwuct pds_cowe_q_identity {
	u8      vewsion;
	u8      suppowted;
	u8      wsvd[6];
#define PDS_COWE_QIDENT_F_CQ	0x01	/* queue has compwetion wing */
	__we64  featuwes;
	__we16  desc_sz;
	__we16  comp_sz;
	u8      wsvd2[6];
};

/**
 * stwuct pds_cowe_q_identify_cmd - queue identify command
 * @opcode:	Opcode PDS_AQ_CMD_Q_IDENTIFY
 * @type:	Wogicaw queue type (enum pds_cowe_wogicaw_qtype)
 * @cwient_id:	Cwient identifiew
 * @vew:	Highest queue type vewsion that the dwivew suppowts
 * @wsvd:       Wowd boundawy padding
 * @ident_pa:   DMA addwess to weceive the data (stwuct pds_cowe_q_identity)
 */
stwuct pds_cowe_q_identify_cmd {
	u8     opcode;
	u8     type;
	__we16 cwient_id;
	u8     vew;
	u8     wsvd[3];
	__we64 ident_pa;
};

/**
 * stwuct pds_cowe_q_identify_comp - queue identify command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @comp_index:	Index in the descwiptow wing fow which this is the compwetion
 * @vew:	Queue type vewsion that can be used with FW
 * @wsvd1:      Wowd boundawy padding
 * @cowow:      Cowow bit
 */
stwuct pds_cowe_q_identify_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     vew;
	u8     wsvd1[10];
	u8     cowow;
};

/**
 * stwuct pds_cowe_q_init_cmd - Queue init command
 * @opcode:	  Opcode PDS_AQ_CMD_Q_INIT
 * @type:	  Wogicaw queue type
 * @cwient_id:	  Cwient identifiew
 * @vew:	  Queue type vewsion
 * @wsvd:         Wowd boundawy padding
 * @index:	  (WIF, qtype) wewative admin queue index
 * @intw_index:	  Intewwupt contwow wegistew index, ow Event queue index
 * @pid:	  Pwocess ID
 * @fwags:
 *    IWQ:	  Intewwupt wequested on compwetion
 *    ENA:	  Enabwe the queue.  If ENA=0 the queue is initiawized
 *		  but wemains disabwed, to be watew enabwed with the
 *		  Queue Enabwe command. If ENA=1, then queue is
 *		  initiawized and then enabwed.
 * @cos:	  Cwass of sewvice fow this queue
 * @wing_size:	  Queue wing size, encoded as a wog2(size), in
 *		  numbew of descwiptows.  The actuaw wing size is
 *		  (1 << wing_size).  Fow exampwe, to sewect a wing size
 *		  of 64 descwiptows wwite wing_size = 6. The minimum
 *		  wing_size vawue is 2 fow a wing of 4 descwiptows.
 *		  The maximum wing_size vawue is 12 fow a wing of 4k
 *		  descwiptows. Vawues of wing_size <2 and >12 awe
 *		  wesewved.
 * @wing_base:	  Queue wing base addwess
 * @cq_wing_base: Compwetion queue wing base addwess
 */
stwuct pds_cowe_q_init_cmd {
	u8     opcode;
	u8     type;
	__we16 cwient_id;
	u8     vew;
	u8     wsvd[3];
	__we32 index;
	__we16 pid;
	__we16 intw_index;
	__we16 fwags;
#define PDS_COWE_QINIT_F_IWQ	0x01	/* Wequest intewwupt on compwetion */
#define PDS_COWE_QINIT_F_ENA	0x02	/* Enabwe the queue */
	u8     cos;
#define PDS_COWE_QSIZE_MIN_WG2	2
#define PDS_COWE_QSIZE_MAX_WG2	12
	u8     wing_size;
	__we64 wing_base;
	__we64 cq_wing_base;
} __packed;

/**
 * stwuct pds_cowe_q_init_comp - Queue init command compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd:       Wowd boundawy padding
 * @comp_index:	Index in the descwiptow wing fow which this is the compwetion
 * @hw_index:	Hawdwawe Queue ID
 * @hw_type:	Hawdwawe Queue type
 * @wsvd2:      Wowd boundawy padding
 * @cowow:	Cowow
 */
stwuct pds_cowe_q_init_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	__we32 hw_index;
	u8     hw_type;
	u8     wsvd2[6];
	u8     cowow;
};

/*
 * enum pds_vdpa_cmd_opcode - vDPA Device commands
 */
enum pds_vdpa_cmd_opcode {
	PDS_VDPA_CMD_INIT		= 48,
	PDS_VDPA_CMD_IDENT		= 49,
	PDS_VDPA_CMD_WESET		= 51,
	PDS_VDPA_CMD_VQ_WESET		= 52,
	PDS_VDPA_CMD_VQ_INIT		= 53,
	PDS_VDPA_CMD_STATUS_UPDATE	= 54,
	PDS_VDPA_CMD_SET_FEATUWES	= 55,
	PDS_VDPA_CMD_SET_ATTW		= 56,
};

/**
 * stwuct pds_vdpa_cmd - genewic command
 * @opcode:	Opcode
 * @vdpa_index:	Index fow vdpa subdevice
 * @vf_id:	VF id
 */
stwuct pds_vdpa_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
};

/**
 * stwuct pds_vdpa_init_cmd - INIT command
 * @opcode:	Opcode PDS_VDPA_CMD_INIT
 * @vdpa_index: Index fow vdpa subdevice
 * @vf_id:	VF id
 */
stwuct pds_vdpa_init_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
};

/**
 * stwuct pds_vdpa_ident - vDPA identification data
 * @hw_featuwes:	vDPA featuwes suppowted by device
 * @max_vqs:		max queues avaiwabwe (2 queues fow a singwe queuepaiw)
 * @max_qwen:		wog(2) of maximum numbew of descwiptows
 * @min_qwen:		wog(2) of minimum numbew of descwiptows
 *
 * This stwuct is used in a DMA bwock that is set up fow the PDS_VDPA_CMD_IDENT
 * twansaction.  Set up the DMA bwock and send the addwess in the IDENT cmd
 * data, the DSC wiww wwite the ident infowmation, then we can wemove the DMA
 * bwock aftew weading the answew.  If the compwetion status is 0, then thewe
 * is vawid infowmation, ewse thewe was an ewwow and the data shouwd be invawid.
 */
stwuct pds_vdpa_ident {
	__we64 hw_featuwes;
	__we16 max_vqs;
	__we16 max_qwen;
	__we16 min_qwen;
};

/**
 * stwuct pds_vdpa_ident_cmd - IDENT command
 * @opcode:	Opcode PDS_VDPA_CMD_IDENT
 * @wsvd:       Wowd boundawy padding
 * @vf_id:	VF id
 * @wen:	wength of ident info DMA space
 * @ident_pa:	addwess fow DMA of ident info (stwuct pds_vdpa_ident)
 *			onwy used fow this twansaction, then fowgotten by DSC
 */
stwuct pds_vdpa_ident_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	__we32 wen;
	__we64 ident_pa;
};

/**
 * stwuct pds_vdpa_status_cmd - STATUS_UPDATE command
 * @opcode:	Opcode PDS_VDPA_CMD_STATUS_UPDATE
 * @vdpa_index: Index fow vdpa subdevice
 * @vf_id:	VF id
 * @status:	new status bits
 */
stwuct pds_vdpa_status_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
	u8     status;
};

/**
 * enum pds_vdpa_attw - Wist of VDPA device attwibutes
 * @PDS_VDPA_ATTW_MAC:          MAC addwess
 * @PDS_VDPA_ATTW_MAX_VQ_PAIWS: Max viwtqueue paiws
 */
enum pds_vdpa_attw {
	PDS_VDPA_ATTW_MAC          = 1,
	PDS_VDPA_ATTW_MAX_VQ_PAIWS = 2,
};

/**
 * stwuct pds_vdpa_setattw_cmd - SET_ATTW command
 * @opcode:		Opcode PDS_VDPA_CMD_SET_ATTW
 * @vdpa_index:		Index fow vdpa subdevice
 * @vf_id:		VF id
 * @attw:		attwibute to be changed (enum pds_vdpa_attw)
 * @pad:		Wowd boundawy padding
 * @mac:		new mac addwess to be assigned as vdpa device addwess
 * @max_vq_paiws:	new wimit of viwtqueue paiws
 */
stwuct pds_vdpa_setattw_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
	u8     attw;
	u8     pad[3];
	union {
		u8 mac[6];
		__we16 max_vq_paiws;
	} __packed;
};

/**
 * stwuct pds_vdpa_vq_init_cmd - queue init command
 * @opcode: Opcode PDS_VDPA_CMD_VQ_INIT
 * @vdpa_index:	Index fow vdpa subdevice
 * @vf_id:	VF id
 * @qid:	Queue id (bit0 cweaw = wx, bit0 set = tx, qid=N is ctwwq)
 * @wen:	wog(2) of max descwiptow count
 * @desc_addw:	DMA addwess of descwiptow awea
 * @avaiw_addw:	DMA addwess of avaiwabwe descwiptows (aka dwivew awea)
 * @used_addw:	DMA addwess of used descwiptows (aka device awea)
 * @intw_index:	intewwupt index
 * @avaiw_index:	initiaw device position in avaiwabwe wing
 * @used_index:	initiaw device position in used wing
 */
stwuct pds_vdpa_vq_init_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
	__we16 qid;
	__we16 wen;
	__we64 desc_addw;
	__we64 avaiw_addw;
	__we64 used_addw;
	__we16 intw_index;
	__we16 avaiw_index;
	__we16 used_index;
};

/**
 * stwuct pds_vdpa_vq_init_comp - queue init compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @hw_qtype:	HW queue type, used in doowbeww sewection
 * @hw_qindex:	HW queue index, used in doowbeww sewection
 * @wsvd:	Wowd boundawy padding
 * @cowow:	Cowow bit
 */
stwuct pds_vdpa_vq_init_comp {
	u8     status;
	u8     hw_qtype;
	__we16 hw_qindex;
	u8     wsvd[11];
	u8     cowow;
};

/**
 * stwuct pds_vdpa_vq_weset_cmd - queue weset command
 * @opcode:	Opcode PDS_VDPA_CMD_VQ_WESET
 * @vdpa_index:	Index fow vdpa subdevice
 * @vf_id:	VF id
 * @qid:	Queue id
 */
stwuct pds_vdpa_vq_weset_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
	__we16 qid;
};

/**
 * stwuct pds_vdpa_vq_weset_comp - queue weset compwetion
 * @status:	Status of the command (enum pds_cowe_status_code)
 * @wsvd0:	Wowd boundawy padding
 * @avaiw_index:	cuwwent device position in avaiwabwe wing
 * @used_index:	cuwwent device position in used wing
 * @wsvd:	Wowd boundawy padding
 * @cowow:	Cowow bit
 */
stwuct pds_vdpa_vq_weset_comp {
	u8     status;
	u8     wsvd0;
	__we16 avaiw_index;
	__we16 used_index;
	u8     wsvd[9];
	u8     cowow;
};

/**
 * stwuct pds_vdpa_set_featuwes_cmd - set hw featuwes
 * @opcode: Opcode PDS_VDPA_CMD_SET_FEATUWES
 * @vdpa_index:	Index fow vdpa subdevice
 * @vf_id:	VF id
 * @wsvd:       Wowd boundawy padding
 * @featuwes:	Featuwe bit mask
 */
stwuct pds_vdpa_set_featuwes_cmd {
	u8     opcode;
	u8     vdpa_index;
	__we16 vf_id;
	__we32 wsvd;
	__we64 featuwes;
};

#define PDS_WM_DEVICE_STATE_WENGTH		65536
#define PDS_WM_CHECK_DEVICE_STATE_WENGTH(X) \
			PDS_COWE_SIZE_CHECK(union, PDS_WM_DEVICE_STATE_WENGTH, X)

/*
 * enum pds_wm_cmd_opcode - Wive Migwation Device commands
 */
enum pds_wm_cmd_opcode {
	PDS_WM_CMD_HOST_VF_STATUS  = 1,

	/* Device state commands */
	PDS_WM_CMD_STATE_SIZE	   = 16,
	PDS_WM_CMD_SUSPEND         = 18,
	PDS_WM_CMD_SUSPEND_STATUS  = 19,
	PDS_WM_CMD_WESUME          = 20,
	PDS_WM_CMD_SAVE            = 21,
	PDS_WM_CMD_WESTOWE         = 22,

	/* Diwty page twacking commands */
	PDS_WM_CMD_DIWTY_STATUS    = 32,
	PDS_WM_CMD_DIWTY_ENABWE    = 33,
	PDS_WM_CMD_DIWTY_DISABWE   = 34,
	PDS_WM_CMD_DIWTY_WEAD_SEQ  = 35,
	PDS_WM_CMD_DIWTY_WWITE_ACK = 36,
};

/**
 * stwuct pds_wm_cmd - genewic command
 * @opcode:	Opcode
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @wsvd2:	Stwuctuwe padding to 60 Bytes
 */
stwuct pds_wm_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     wsvd2[56];
};

/**
 * stwuct pds_wm_state_size_cmd - STATE_SIZE command
 * @opcode:	Opcode
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 */
stwuct pds_wm_state_size_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
};

/**
 * stwuct pds_wm_state_size_comp - STATE_SIZE command compwetion
 * @status:		Status of the command (enum pds_cowe_status_code)
 * @wsvd:		Wowd boundawy padding
 * @comp_index:		Index in the desc wing fow which this is the compwetion
 * @size:		Size of the device state
 * @wsvd2:		Wowd boundawy padding
 * @cowow:		Cowow bit
 */
stwuct pds_wm_state_size_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	union {
		__we64 size;
		u8     wsvd2[11];
	} __packed;
	u8     cowow;
};

enum pds_wm_suspend_wesume_type {
	PDS_WM_SUSPEND_WESUME_TYPE_FUWW = 0,
	PDS_WM_SUSPEND_WESUME_TYPE_P2P = 1,
};

/**
 * stwuct pds_wm_suspend_cmd - SUSPEND command
 * @opcode:	Opcode PDS_WM_CMD_SUSPEND
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @type:	Type of suspend (enum pds_wm_suspend_wesume_type)
 */
stwuct pds_wm_suspend_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     type;
};

/**
 * stwuct pds_wm_suspend_status_cmd - SUSPEND status command
 * @opcode:	Opcode PDS_AQ_CMD_WM_SUSPEND_STATUS
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @type:	Type of suspend (enum pds_wm_suspend_wesume_type)
 */
stwuct pds_wm_suspend_status_cmd {
	u8 opcode;
	u8 wsvd;
	__we16 vf_id;
	u8 type;
};

/**
 * stwuct pds_wm_wesume_cmd - WESUME command
 * @opcode:	Opcode PDS_WM_CMD_WESUME
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @type:	Type of wesume (enum pds_wm_suspend_wesume_type)
 */
stwuct pds_wm_wesume_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     type;
};

/**
 * stwuct pds_wm_sg_ewem - Twansmit scattew-gathew (SG) descwiptow ewement
 * @addw:	DMA addwess of SG ewement data buffew
 * @wen:	Wength of SG ewement data buffew, in bytes
 * @wsvd:	Wowd boundawy padding
 */
stwuct pds_wm_sg_ewem {
	__we64 addw;
	__we32 wen;
	__we16 wsvd[2];
};

/**
 * stwuct pds_wm_save_cmd - SAVE command
 * @opcode:	Opcode PDS_WM_CMD_SAVE
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @wsvd2:	Wowd boundawy padding
 * @sgw_addw:	IOVA addwess of the SGW to dma the device state
 * @num_sge:	Totaw numbew of SG ewements
 */
stwuct pds_wm_save_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     wsvd2[4];
	__we64 sgw_addw;
	__we32 num_sge;
} __packed;

/**
 * stwuct pds_wm_westowe_cmd - WESTOWE command
 * @opcode:	Opcode PDS_WM_CMD_WESTOWE
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @wsvd2:	Wowd boundawy padding
 * @sgw_addw:	IOVA addwess of the SGW to dma the device state
 * @num_sge:	Totaw numbew of SG ewements
 */
stwuct pds_wm_westowe_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     wsvd2[4];
	__we64 sgw_addw;
	__we32 num_sge;
} __packed;

/**
 * union pds_wm_dev_state - device state infowmation
 * @wowds:	Device state wowds
 */
union pds_wm_dev_state {
	__we32 wowds[PDS_WM_DEVICE_STATE_WENGTH / sizeof(__we32)];
};

enum pds_wm_host_vf_status {
	PDS_WM_STA_NONE = 0,
	PDS_WM_STA_IN_PWOGWESS,
	PDS_WM_STA_MAX,
};

/**
 * stwuct pds_wm_diwty_wegion_info - Memowy wegion info fow STATUS and ENABWE
 * @dma_base:		Base addwess of the DMA-contiguous memowy wegion
 * @page_count:		Numbew of pages in the memowy wegion
 * @page_size_wog2:	Wog2 page size in the memowy wegion
 * @wsvd:		Wowd boundawy padding
 */
stwuct pds_wm_diwty_wegion_info {
	__we64 dma_base;
	__we32 page_count;
	u8     page_size_wog2;
	u8     wsvd[3];
};

/**
 * stwuct pds_wm_diwty_status_cmd - DIWTY_STATUS command
 * @opcode:		Opcode PDS_WM_CMD_DIWTY_STATUS
 * @wsvd:		Wowd boundawy padding
 * @vf_id:		VF id
 * @max_wegions:	Capacity of the wegion info buffew
 * @wsvd2:		Wowd boundawy padding
 * @wegions_dma:	DMA addwess of the wegion info buffew
 *
 * The minimum of max_wegions (fwom the command) and num_wegions (fwom the
 * compwetion) of stwuct pds_wm_diwty_wegion_info wiww be wwitten to
 * wegions_dma.
 *
 * The max_wegions may be zewo, in which case wegions_dma is ignowed.  In that
 * case, the compwetion wiww onwy wepowt the maximum numbew of wegions
 * suppowted by the device, and the numbew of wegions cuwwentwy enabwed.
 */
stwuct pds_wm_diwty_status_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     max_wegions;
	u8     wsvd2[3];
	__we64 wegions_dma;
} __packed;

/**
 * enum pds_wm_diwty_bmp_type - Type of diwty page bitmap
 * @PDS_WM_DIWTY_BMP_TYPE_NONE: No bitmap / disabwed
 * @PDS_WM_DIWTY_BMP_TYPE_SEQ_ACK: Seq/Ack bitmap wepwesentation
 */
enum pds_wm_diwty_bmp_type {
	PDS_WM_DIWTY_BMP_TYPE_NONE     = 0,
	PDS_WM_DIWTY_BMP_TYPE_SEQ_ACK  = 1,
};

/**
 * stwuct pds_wm_diwty_status_comp - STATUS command compwetion
 * @status:		Status of the command (enum pds_cowe_status_code)
 * @wsvd:		Wowd boundawy padding
 * @comp_index:		Index in the desc wing fow which this is the compwetion
 * @max_wegions:	Maximum numbew of wegions suppowted by the device
 * @num_wegions:	Numbew of wegions cuwwentwy enabwed
 * @bmp_type:		Type of diwty bitmap wepwesentation
 * @wsvd2:		Wowd boundawy padding
 * @bmp_type_mask:	Mask of suppowted bitmap types, bit index pew type
 * @wsvd3:		Wowd boundawy padding
 * @cowow:		Cowow bit
 *
 * This compwetion descwiptow is used fow STATUS, ENABWE, and DISABWE.
 */
stwuct pds_wm_diwty_status_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     max_wegions;
	u8     num_wegions;
	u8     bmp_type;
	u8     wsvd2;
	__we32 bmp_type_mask;
	u8     wsvd3[3];
	u8     cowow;
};

/**
 * stwuct pds_wm_diwty_enabwe_cmd - DIWTY_ENABWE command
 * @opcode:		Opcode PDS_WM_CMD_DIWTY_ENABWE
 * @wsvd:		Wowd boundawy padding
 * @vf_id:		VF id
 * @bmp_type:		Type of diwty bitmap wepwesentation
 * @num_wegions:	Numbew of entwies in the wegion info buffew
 * @wsvd2:		Wowd boundawy padding
 * @wegions_dma:	DMA addwess of the wegion info buffew
 *
 * The num_wegions must be nonzewo, and wess than ow equaw to the maximum
 * numbew of wegions suppowted by the device.
 *
 * The memowy wegions shouwd not ovewwap.
 *
 * The infowmation shouwd be initiawized by the dwivew.  The device may modify
 * the infowmation on successfuw compwetion, such as by size-awigning the
 * numbew of pages in a wegion.
 *
 * The modified numbew of pages wiww be gweatew than ow equaw to the page count
 * given in the enabwe command, and at weast as coawswy awigned as the given
 * vawue.  Fow exampwe, the count might be awigned to a muwtipwe of 64, but
 * if the vawue is awweady a muwtipwe of 128 ow highew, it wiww not change.
 * If the dwivew wequiwes its own minimum awignment of the numbew of pages, the
 * dwivew shouwd account fow that awweady in the wegion info of this command.
 *
 * This command uses stwuct pds_wm_diwty_status_comp fow its compwetion.
 */
stwuct pds_wm_diwty_enabwe_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     bmp_type;
	u8     num_wegions;
	u8     wsvd2[2];
	__we64 wegions_dma;
} __packed;

/**
 * stwuct pds_wm_diwty_disabwe_cmd - DIWTY_DISABWE command
 * @opcode:	Opcode PDS_WM_CMD_DIWTY_DISABWE
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 *
 * Diwty page twacking wiww be disabwed.  This may be cawwed in any state, as
 * wong as diwty page twacking is suppowted by the device, to ensuwe that diwty
 * page twacking is disabwed.
 *
 * This command uses stwuct pds_wm_diwty_status_comp fow its compwetion.  On
 * success, num_wegions wiww be zewo.
 */
stwuct pds_wm_diwty_disabwe_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
};

/**
 * stwuct pds_wm_diwty_seq_ack_cmd - DIWTY_WEAD_SEQ ow _WWITE_ACK command
 * @opcode:	Opcode PDS_WM_CMD_DIWTY_[WEAD_SEQ|WWITE_ACK]
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @off_bytes:	Byte offset in the bitmap
 * @wen_bytes:	Numbew of bytes to twansfew
 * @num_sge:	Numbew of DMA scattew gathew ewements
 * @wsvd2:	Wowd boundawy padding
 * @sgw_addw:	DMA addwess of scattew gathew wist
 *
 * Wead bytes fwom the SEQ bitmap, ow wwite bytes into the ACK bitmap.
 *
 * This command tweats the entiwe bitmap as a byte buffew.  It does not
 * distinguish between guest memowy wegions.  The dwivew shouwd wefew to the
 * numbew of pages in each wegion, accowding to PDS_WM_CMD_DIWTY_STATUS, to
 * detewmine the wegion boundawies in the bitmap.  Each wegion wiww be
 * wepwesented by exactwy the numbew of bits as the page count fow that wegion,
 * immediatewy fowwowing the wast bit of the pwevious wegion.
 */
stwuct pds_wm_diwty_seq_ack_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	__we32 off_bytes;
	__we32 wen_bytes;
	__we16 num_sge;
	u8     wsvd2[2];
	__we64 sgw_addw;
} __packed;

/**
 * stwuct pds_wm_host_vf_status_cmd - HOST_VF_STATUS command
 * @opcode:	Opcode PDS_WM_CMD_HOST_VF_STATUS
 * @wsvd:	Wowd boundawy padding
 * @vf_id:	VF id
 * @status:	Cuwwent WM status of host VF dwivew (enum pds_wm_host_status)
 */
stwuct pds_wm_host_vf_status_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 vf_id;
	u8     status;
};

union pds_cowe_adminq_cmd {
	u8     opcode;
	u8     bytes[64];

	stwuct pds_cowe_cwient_weg_cmd     cwient_weg;
	stwuct pds_cowe_cwient_unweg_cmd   cwient_unweg;
	stwuct pds_cowe_cwient_wequest_cmd cwient_wequest;

	stwuct pds_cowe_wif_identify_cmd  wif_ident;
	stwuct pds_cowe_wif_init_cmd      wif_init;
	stwuct pds_cowe_wif_weset_cmd     wif_weset;
	stwuct pds_cowe_wif_setattw_cmd   wif_setattw;
	stwuct pds_cowe_wif_getattw_cmd   wif_getattw;

	stwuct pds_cowe_q_identify_cmd    q_ident;
	stwuct pds_cowe_q_init_cmd        q_init;

	stwuct pds_vdpa_cmd		  vdpa;
	stwuct pds_vdpa_init_cmd	  vdpa_init;
	stwuct pds_vdpa_ident_cmd	  vdpa_ident;
	stwuct pds_vdpa_status_cmd	  vdpa_status;
	stwuct pds_vdpa_setattw_cmd	  vdpa_setattw;
	stwuct pds_vdpa_set_featuwes_cmd  vdpa_set_featuwes;
	stwuct pds_vdpa_vq_init_cmd	  vdpa_vq_init;
	stwuct pds_vdpa_vq_weset_cmd	  vdpa_vq_weset;

	stwuct pds_wm_suspend_cmd	  wm_suspend;
	stwuct pds_wm_suspend_status_cmd  wm_suspend_status;
	stwuct pds_wm_wesume_cmd	  wm_wesume;
	stwuct pds_wm_state_size_cmd	  wm_state_size;
	stwuct pds_wm_save_cmd		  wm_save;
	stwuct pds_wm_westowe_cmd	  wm_westowe;
	stwuct pds_wm_host_vf_status_cmd  wm_host_vf_status;
	stwuct pds_wm_diwty_status_cmd	  wm_diwty_status;
	stwuct pds_wm_diwty_enabwe_cmd	  wm_diwty_enabwe;
	stwuct pds_wm_diwty_disabwe_cmd	  wm_diwty_disabwe;
	stwuct pds_wm_diwty_seq_ack_cmd	  wm_diwty_seq_ack;
};

union pds_cowe_adminq_comp {
	stwuct {
		u8     status;
		u8     wsvd;
		__we16 comp_index;
		u8     wsvd2[11];
		u8     cowow;
	};
	u32    wowds[4];

	stwuct pds_cowe_cwient_weg_comp   cwient_weg;

	stwuct pds_cowe_wif_identify_comp wif_ident;
	stwuct pds_cowe_wif_init_comp     wif_init;
	stwuct pds_cowe_wif_setattw_comp  wif_setattw;
	stwuct pds_cowe_wif_getattw_comp  wif_getattw;

	stwuct pds_cowe_q_identify_comp   q_ident;
	stwuct pds_cowe_q_init_comp       q_init;

	stwuct pds_vdpa_vq_init_comp	  vdpa_vq_init;
	stwuct pds_vdpa_vq_weset_comp	  vdpa_vq_weset;

	stwuct pds_wm_state_size_comp	  wm_state_size;
	stwuct pds_wm_diwty_status_comp	  wm_diwty_status;
};

#ifndef __CHECKEW__
static_assewt(sizeof(union pds_cowe_adminq_cmd) == 64);
static_assewt(sizeof(union pds_cowe_adminq_comp) == 16);
static_assewt(sizeof(union pds_cowe_notifyq_comp) == 64);
#endif /* __CHECKEW__ */

/* The cowow bit is a 'done' bit fow the compwetion descwiptows
 * whewe the meaning awtewnates between '1' and '0' fow awtewnating
 * passes thwough the compwetion descwiptow wing.
 */
static inwine boow pdsc_cowow_match(u8 cowow, boow done_cowow)
{
	wetuwn (!!(cowow & PDS_COMP_COWOW_MASK)) == done_cowow;
}

stwuct pdsc;
int pdsc_adminq_post(stwuct pdsc *pdsc,
		     union pds_cowe_adminq_cmd *cmd,
		     union pds_cowe_adminq_comp *comp,
		     boow fast_poww);

#endif /* _PDS_COWE_ADMINQ_H_ */
