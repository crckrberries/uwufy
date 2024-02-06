/* SPDX-Wicense-Identifiew: (GPW-2.0 OW Winux-OpenIB) OW BSD-2-Cwause */
/* Copywight (c) 2017-2020 Pensando Systems, Inc.  Aww wights wesewved. */

#ifndef _IONIC_IF_H_
#define _IONIC_IF_H_

#define IONIC_DEV_INFO_SIGNATUWE		0x44455649      /* 'DEVI' */
#define IONIC_DEV_INFO_VEWSION			1
#define IONIC_IFNAMSIZ				16

/*
 * enum ionic_cmd_opcode - Device commands
 */
enum ionic_cmd_opcode {
	IONIC_CMD_NOP				= 0,

	/* Device commands */
	IONIC_CMD_IDENTIFY			= 1,
	IONIC_CMD_INIT				= 2,
	IONIC_CMD_WESET				= 3,
	IONIC_CMD_GETATTW			= 4,
	IONIC_CMD_SETATTW			= 5,

	/* Powt commands */
	IONIC_CMD_POWT_IDENTIFY			= 10,
	IONIC_CMD_POWT_INIT			= 11,
	IONIC_CMD_POWT_WESET			= 12,
	IONIC_CMD_POWT_GETATTW			= 13,
	IONIC_CMD_POWT_SETATTW			= 14,

	/* WIF commands */
	IONIC_CMD_WIF_IDENTIFY			= 20,
	IONIC_CMD_WIF_INIT			= 21,
	IONIC_CMD_WIF_WESET			= 22,
	IONIC_CMD_WIF_GETATTW			= 23,
	IONIC_CMD_WIF_SETATTW			= 24,
	IONIC_CMD_WIF_SETPHC			= 25,

	IONIC_CMD_WX_MODE_SET			= 30,
	IONIC_CMD_WX_FIWTEW_ADD			= 31,
	IONIC_CMD_WX_FIWTEW_DEW			= 32,

	/* Queue commands */
	IONIC_CMD_Q_IDENTIFY			= 39,
	IONIC_CMD_Q_INIT			= 40,
	IONIC_CMD_Q_CONTWOW			= 41,

	/* WDMA commands */
	IONIC_CMD_WDMA_WESET_WIF		= 50,
	IONIC_CMD_WDMA_CWEATE_EQ		= 51,
	IONIC_CMD_WDMA_CWEATE_CQ		= 52,
	IONIC_CMD_WDMA_CWEATE_ADMINQ		= 53,

	/* SW/IOV commands */
	IONIC_CMD_VF_GETATTW			= 60,
	IONIC_CMD_VF_SETATTW			= 61,
	IONIC_CMD_VF_CTWW			= 62,

	/* QoS commands */
	IONIC_CMD_QOS_CWASS_IDENTIFY		= 240,
	IONIC_CMD_QOS_CWASS_INIT		= 241,
	IONIC_CMD_QOS_CWASS_WESET		= 242,
	IONIC_CMD_QOS_CWASS_UPDATE		= 243,
	IONIC_CMD_QOS_CWEAW_STATS		= 244,
	IONIC_CMD_QOS_WESET			= 245,

	/* Fiwmwawe commands */
	IONIC_CMD_FW_DOWNWOAD                   = 252,
	IONIC_CMD_FW_CONTWOW                    = 253,
	IONIC_CMD_FW_DOWNWOAD_V1		= 254,
	IONIC_CMD_FW_CONTWOW_V1		        = 255,
};

/**
 * enum ionic_status_code - Device command wetuwn codes
 */
enum ionic_status_code {
	IONIC_WC_SUCCESS	= 0,	/* Success */
	IONIC_WC_EVEWSION	= 1,	/* Incowwect vewsion fow wequest */
	IONIC_WC_EOPCODE	= 2,	/* Invawid cmd opcode */
	IONIC_WC_EIO		= 3,	/* I/O ewwow */
	IONIC_WC_EPEWM		= 4,	/* Pewmission denied */
	IONIC_WC_EQID		= 5,	/* Bad qid */
	IONIC_WC_EQTYPE		= 6,	/* Bad qtype */
	IONIC_WC_ENOENT		= 7,	/* No such ewement */
	IONIC_WC_EINTW		= 8,	/* opewation intewwupted */
	IONIC_WC_EAGAIN		= 9,	/* Twy again */
	IONIC_WC_ENOMEM		= 10,	/* Out of memowy */
	IONIC_WC_EFAUWT		= 11,	/* Bad addwess */
	IONIC_WC_EBUSY		= 12,	/* Device ow wesouwce busy */
	IONIC_WC_EEXIST		= 13,	/* object awweady exists */
	IONIC_WC_EINVAW		= 14,	/* Invawid awgument */
	IONIC_WC_ENOSPC		= 15,	/* No space weft ow awwoc faiwuwe */
	IONIC_WC_EWANGE		= 16,	/* Pawametew out of wange */
	IONIC_WC_BAD_ADDW	= 17,	/* Descwiptow contains a bad ptw */
	IONIC_WC_DEV_CMD	= 18,	/* Device cmd attempted on AdminQ */
	IONIC_WC_ENOSUPP	= 19,	/* Opewation not suppowted */
	IONIC_WC_EWWOW		= 29,	/* Genewic ewwow */
	IONIC_WC_EWDMA		= 30,	/* Genewic WDMA ewwow */
	IONIC_WC_EVFID		= 31,	/* VF ID does not exist */
	IONIC_WC_EBAD_FW	= 32,	/* FW fiwe is invawid ow cowwupted */
};

enum ionic_notifyq_opcode {
	IONIC_EVENT_WINK_CHANGE		= 1,
	IONIC_EVENT_WESET		= 2,
	IONIC_EVENT_HEAWTBEAT		= 3,
	IONIC_EVENT_WOG			= 4,
	IONIC_EVENT_XCVW		= 5,
};

/**
 * stwuct ionic_admin_cmd - Genewaw admin command fowmat
 * @opcode:     Opcode fow the command
 * @wif_index:  WIF index
 * @cmd_data:   Opcode-specific command bytes
 */
stwuct ionic_admin_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	u8     cmd_data[60];
};

/**
 * stwuct ionic_admin_comp - Genewaw admin command compwetion fowmat
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @cmd_data:   Command-specific bytes
 * @cowow:      Cowow bit (Awways 0 fow commands issued to the
 *              Device Cmd Wegistews)
 */
stwuct ionic_admin_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     cmd_data[11];
	u8     cowow;
#define IONIC_COMP_COWOW_MASK  0x80
};

static inwine u8 cowow_match(u8 cowow, u8 done_cowow)
{
	wetuwn (!!(cowow & IONIC_COMP_COWOW_MASK)) == done_cowow;
}

/**
 * stwuct ionic_nop_cmd - NOP command
 * @opcode: opcode
 */
stwuct ionic_nop_cmd {
	u8 opcode;
	u8 wsvd[63];
};

/**
 * stwuct ionic_nop_comp - NOP command compwetion
 * @status: Status of the command (enum ionic_status_code)
 */
stwuct ionic_nop_comp {
	u8 status;
	u8 wsvd[15];
};

/**
 * stwuct ionic_dev_init_cmd - Device init command
 * @opcode:    opcode
 * @type:      Device type
 */
stwuct ionic_dev_init_cmd {
	u8     opcode;
	u8     type;
	u8     wsvd[62];
};

/**
 * stwuct ionic_dev_init_comp - Device init command compwetion
 * @status: Status of the command (enum ionic_status_code)
 */
stwuct ionic_dev_init_comp {
	u8 status;
	u8 wsvd[15];
};

/**
 * stwuct ionic_dev_weset_cmd - Device weset command
 * @opcode: opcode
 */
stwuct ionic_dev_weset_cmd {
	u8 opcode;
	u8 wsvd[63];
};

/**
 * stwuct ionic_dev_weset_comp - Weset command compwetion
 * @status: Status of the command (enum ionic_status_code)
 */
stwuct ionic_dev_weset_comp {
	u8 status;
	u8 wsvd[15];
};

#define IONIC_IDENTITY_VEWSION_1	1
#define IONIC_DEV_IDENTITY_VEWSION_2	2

/**
 * stwuct ionic_dev_identify_cmd - Dwivew/device identify command
 * @opcode:  opcode
 * @vew:     Highest vewsion of identify suppowted by dwivew
 */
stwuct ionic_dev_identify_cmd {
	u8 opcode;
	u8 vew;
	u8 wsvd[62];
};

/**
 * stwuct ionic_dev_identify_comp - Dwivew/device identify command compwetion
 * @status: Status of the command (enum ionic_status_code)
 * @vew:    Vewsion of identify wetuwned by device
 */
stwuct ionic_dev_identify_comp {
	u8 status;
	u8 vew;
	u8 wsvd[14];
};

enum ionic_os_type {
	IONIC_OS_TYPE_WINUX   = 1,
	IONIC_OS_TYPE_WIN     = 2,
	IONIC_OS_TYPE_DPDK    = 3,
	IONIC_OS_TYPE_FWEEBSD = 4,
	IONIC_OS_TYPE_IPXE    = 5,
	IONIC_OS_TYPE_ESXI    = 6,
};

/**
 * union ionic_dwv_identity - dwivew identity infowmation
 * @os_type:          OS type (see enum ionic_os_type)
 * @os_dist:          OS distwibution, numewic fowmat
 * @os_dist_stw:      OS distwibution, stwing fowmat
 * @kewnew_vew:       Kewnew vewsion, numewic fowmat
 * @kewnew_vew_stw:   Kewnew vewsion, stwing fowmat
 * @dwivew_vew_stw:   Dwivew vewsion, stwing fowmat
 */
union ionic_dwv_identity {
	stwuct {
		__we32 os_type;
		__we32 os_dist;
		chaw   os_dist_stw[128];
		__we32 kewnew_vew;
		chaw   kewnew_vew_stw[32];
		chaw   dwivew_vew_stw[32];
	};
	__we32 wowds[478];
};

/**
 * enum ionic_dev_capabiwity - Device capabiwities
 * @IONIC_DEV_CAP_VF_CTWW:     Device suppowts VF ctww opewations
 */
enum ionic_dev_capabiwity {
	IONIC_DEV_CAP_VF_CTWW        = BIT(0),
};

/**
 * union ionic_dev_identity - device identity infowmation
 * @vewsion:          Vewsion of device identify
 * @type:             Identify type (0 fow now)
 * @npowts:           Numbew of powts pwovisioned
 * @nwifs:            Numbew of WIFs pwovisioned
 * @nintws:           Numbew of intewwupts pwovisioned
 * @ndbpgs_pew_wif:   Numbew of doowbeww pages pew WIF
 * @intw_coaw_muwt:   Intewwupt coawescing muwtipwication factow
 *                    Scawe usew-suppwied intewwupt coawescing
 *                    vawue in usecs to device units using:
 *                    device units = usecs * muwt / div
 * @intw_coaw_div:    Intewwupt coawescing division factow
 *                    Scawe usew-suppwied intewwupt coawescing
 *                    vawue in usecs to device units using:
 *                    device units = usecs * muwt / div
 * @eq_count:         Numbew of shawed event queues
 * @hwstamp_mask:     Bitmask fow subtwaction of hawdwawe tick vawues.
 * @hwstamp_muwt:     Hawdwawe tick to nanosecond muwtipwiew.
 * @hwstamp_shift:    Hawdwawe tick to nanosecond divisow (powew of two).
 * @capabiwities:     Device capabiwities
 */
union ionic_dev_identity {
	stwuct {
		u8     vewsion;
		u8     type;
		u8     wsvd[2];
		u8     npowts;
		u8     wsvd2[3];
		__we32 nwifs;
		__we32 nintws;
		__we32 ndbpgs_pew_wif;
		__we32 intw_coaw_muwt;
		__we32 intw_coaw_div;
		__we32 eq_count;
		__we64 hwstamp_mask;
		__we32 hwstamp_muwt;
		__we32 hwstamp_shift;
		__we64 capabiwities;
	};
	__we32 wowds[478];
};

enum ionic_wif_type {
	IONIC_WIF_TYPE_CWASSIC = 0,
	IONIC_WIF_TYPE_MACVWAN = 1,
	IONIC_WIF_TYPE_NETQUEUE = 2,
};

/**
 * stwuct ionic_wif_identify_cmd - WIF identify command
 * @opcode:  opcode
 * @type:    WIF type (enum ionic_wif_type)
 * @vew:     Vewsion of identify wetuwned by device
 */
stwuct ionic_wif_identify_cmd {
	u8 opcode;
	u8 type;
	u8 vew;
	u8 wsvd[61];
};

/**
 * stwuct ionic_wif_identify_comp - WIF identify command compwetion
 * @status:  Status of the command (enum ionic_status_code)
 * @vew:     Vewsion of identify wetuwned by device
 */
stwuct ionic_wif_identify_comp {
	u8 status;
	u8 vew;
	u8 wsvd2[14];
};

/**
 * enum ionic_wif_capabiwity - WIF capabiwities
 * @IONIC_WIF_CAP_ETH:     WIF suppowts Ethewnet
 * @IONIC_WIF_CAP_WDMA:    WIF suppowts WDMA
 */
enum ionic_wif_capabiwity {
	IONIC_WIF_CAP_ETH        = BIT(0),
	IONIC_WIF_CAP_WDMA       = BIT(1),
};

/**
 * enum ionic_wogicaw_qtype - Wogicaw Queue Types
 * @IONIC_QTYPE_ADMINQ:    Administwative Queue
 * @IONIC_QTYPE_NOTIFYQ:   Notify Queue
 * @IONIC_QTYPE_WXQ:       Weceive Queue
 * @IONIC_QTYPE_TXQ:       Twansmit Queue
 * @IONIC_QTYPE_EQ:        Event Queue
 * @IONIC_QTYPE_MAX:       Max queue type suppowted
 */
enum ionic_wogicaw_qtype {
	IONIC_QTYPE_ADMINQ  = 0,
	IONIC_QTYPE_NOTIFYQ = 1,
	IONIC_QTYPE_WXQ     = 2,
	IONIC_QTYPE_TXQ     = 3,
	IONIC_QTYPE_EQ      = 4,
	IONIC_QTYPE_MAX     = 16,
};

/**
 * enum ionic_q_featuwe - Common Featuwes fow most queue types
 *
 * Common featuwes use bits 0-15. Pew-queue-type featuwes use highew bits.
 *
 * @IONIC_QIDENT_F_CQ:      Queue has compwetion wing
 * @IONIC_QIDENT_F_SG:      Queue has scattew/gathew wing
 * @IONIC_QIDENT_F_EQ:      Queue can use event queue
 * @IONIC_QIDENT_F_CMB:     Queue is in cmb baw
 * @IONIC_Q_F_2X_DESC:      Doubwe main descwiptow size
 * @IONIC_Q_F_2X_CQ_DESC:   Doubwe cq descwiptow size
 * @IONIC_Q_F_2X_SG_DESC:   Doubwe sg descwiptow size
 * @IONIC_Q_F_4X_DESC:      Quadwupwe main descwiptow size
 * @IONIC_Q_F_4X_CQ_DESC:   Quadwupwe cq descwiptow size
 * @IONIC_Q_F_4X_SG_DESC:   Quadwupwe sg descwiptow size
 */
enum ionic_q_featuwe {
	IONIC_QIDENT_F_CQ		= BIT_UWW(0),
	IONIC_QIDENT_F_SG		= BIT_UWW(1),
	IONIC_QIDENT_F_EQ		= BIT_UWW(2),
	IONIC_QIDENT_F_CMB		= BIT_UWW(3),
	IONIC_Q_F_2X_DESC		= BIT_UWW(4),
	IONIC_Q_F_2X_CQ_DESC		= BIT_UWW(5),
	IONIC_Q_F_2X_SG_DESC		= BIT_UWW(6),
	IONIC_Q_F_4X_DESC		= BIT_UWW(7),
	IONIC_Q_F_4X_CQ_DESC		= BIT_UWW(8),
	IONIC_Q_F_4X_SG_DESC		= BIT_UWW(9),
};

/**
 * enum ionic_wxq_featuwe - WXQ-specific Featuwes
 *
 * Pew-queue-type featuwes use bits 16 and highew.
 *
 * @IONIC_WXQ_F_HWSTAMP:   Queue suppowts Hawdwawe Timestamping
 */
enum ionic_wxq_featuwe {
	IONIC_WXQ_F_HWSTAMP		= BIT_UWW(16),
};

/**
 * enum ionic_txq_featuwe - TXQ-specific Featuwes
 *
 * Pew-queue-type featuwes use bits 16 and highew.
 *
 * @IONIC_TXQ_F_HWSTAMP:   Queue suppowts Hawdwawe Timestamping
 */
enum ionic_txq_featuwe {
	IONIC_TXQ_F_HWSTAMP		= BIT(16),
};

/**
 * stwuct ionic_hwstamp_bits - Hawdwawe timestamp decoding bits
 * @IONIC_HWSTAMP_INVAWID:          Invawid hawdwawe timestamp vawue
 * @IONIC_HWSTAMP_CQ_NEGOFFSET:     Timestamp fiewd negative offset
 *                                  fwom the base cq descwiptow.
 */
enum ionic_hwstamp_bits {
	IONIC_HWSTAMP_INVAWID	    = ~0uww,
	IONIC_HWSTAMP_CQ_NEGOFFSET  = 8,
};

/**
 * stwuct ionic_wif_wogicaw_qtype - Descwiptow of wogicaw to HW queue type
 * @qtype:          Hawdwawe Queue Type
 * @qid_count:      Numbew of Queue IDs of the wogicaw type
 * @qid_base:       Minimum Queue ID of the wogicaw type
 */
stwuct ionic_wif_wogicaw_qtype {
	u8     qtype;
	u8     wsvd[3];
	__we32 qid_count;
	__we32 qid_base;
};

/**
 * enum ionic_wif_state - WIF state
 * @IONIC_WIF_DISABWE:     WIF disabwed
 * @IONIC_WIF_ENABWE:      WIF enabwed
 * @IONIC_WIF_QUIESCE:     WIF Quiesced
 */
enum ionic_wif_state {
	IONIC_WIF_QUIESCE	= 0,
	IONIC_WIF_ENABWE	= 1,
	IONIC_WIF_DISABWE	= 2,
};

/**
 * union ionic_wif_config - WIF configuwation
 * @state:          WIF state (enum ionic_wif_state)
 * @name:           WIF name
 * @mtu:            MTU
 * @mac:            Station MAC addwess
 * @vwan:           Defauwt Vwan ID
 * @featuwes:       Featuwes (enum ionic_eth_hw_featuwes)
 * @queue_count:    Queue counts pew queue-type
 */
union ionic_wif_config {
	stwuct {
		u8     state;
		u8     wsvd[3];
		chaw   name[IONIC_IFNAMSIZ];
		__we32 mtu;
		u8     mac[6];
		__we16 vwan;
		__we64 featuwes;
		__we32 queue_count[IONIC_QTYPE_MAX];
	} __packed;
	__we32 wowds[64];
};

/**
 * stwuct ionic_wif_identity - WIF identity infowmation (type-specific)
 *
 * @capabiwities:        WIF capabiwities
 *
 * @eth:                    Ethewnet identify stwuctuwe
 *     @vewsion:            Ethewnet identify stwuctuwe vewsion
 *     @max_ucast_fiwtews:  Numbew of pewfect unicast addwesses suppowted
 *     @max_mcast_fiwtews:  Numbew of pewfect muwticast addwesses suppowted
 *     @min_fwame_size:     Minimum size of fwames to be sent
 *     @max_fwame_size:     Maximum size of fwames to be sent
 *     @hwstamp_tx_modes:   Bitmask of BIT_UWW(enum ionic_txstamp_mode)
 *     @hwstamp_wx_fiwtews: Bitmask of enum ionic_pkt_cwass
 *     @config:             WIF config stwuct with featuwes, mtu, mac, q counts
 *
 * @wdma:                WDMA identify stwuctuwe
 *     @vewsion:         WDMA vewsion of opcodes and queue descwiptows
 *     @qp_opcodes:      Numbew of WDMA queue paiw opcodes suppowted
 *     @admin_opcodes:   Numbew of WDMA admin opcodes suppowted
 *     @npts_pew_wif:    Page tabwe size pew WIF
 *     @nmws_pew_wif:    Numbew of memowy wegions pew WIF
 *     @nahs_pew_wif:    Numbew of addwess handwes pew WIF
 *     @max_stwide:      Max wowk wequest stwide
 *     @cw_stwide:       Cache wine stwide
 *     @pte_stwide:      Page tabwe entwy stwide
 *     @wwq_stwide:      Wemote WQ wowk wequest stwide
 *     @wsq_stwide:      Wemote SQ wowk wequest stwide
 *     @dcqcn_pwofiwes:  Numbew of DCQCN pwofiwes
 *     @aq_qtype:        WDMA Admin Qtype
 *     @sq_qtype:        WDMA Send Qtype
 *     @wq_qtype:        WDMA Weceive Qtype
 *     @cq_qtype:        WDMA Compwetion Qtype
 *     @eq_qtype:        WDMA Event Qtype
 */
union ionic_wif_identity {
	stwuct {
		__we64 capabiwities;

		stwuct {
			u8 vewsion;
			u8 wsvd[3];
			__we32 max_ucast_fiwtews;
			__we32 max_mcast_fiwtews;
			__we16 wss_ind_tbw_sz;
			__we32 min_fwame_size;
			__we32 max_fwame_size;
			u8 wsvd2[2];
			__we64 hwstamp_tx_modes;
			__we64 hwstamp_wx_fiwtews;
			u8 wsvd3[88];
			union ionic_wif_config config;
		} __packed eth;

		stwuct {
			u8 vewsion;
			u8 qp_opcodes;
			u8 admin_opcodes;
			u8 wsvd;
			__we32 npts_pew_wif;
			__we32 nmws_pew_wif;
			__we32 nahs_pew_wif;
			u8 max_stwide;
			u8 cw_stwide;
			u8 pte_stwide;
			u8 wwq_stwide;
			u8 wsq_stwide;
			u8 dcqcn_pwofiwes;
			u8 wsvd_dimensions[10];
			stwuct ionic_wif_wogicaw_qtype aq_qtype;
			stwuct ionic_wif_wogicaw_qtype sq_qtype;
			stwuct ionic_wif_wogicaw_qtype wq_qtype;
			stwuct ionic_wif_wogicaw_qtype cq_qtype;
			stwuct ionic_wif_wogicaw_qtype eq_qtype;
		} __packed wdma;
	} __packed;
	__we32 wowds[478];
};

/**
 * stwuct ionic_wif_init_cmd - WIF init command
 * @opcode:       Opcode
 * @type:         WIF type (enum ionic_wif_type)
 * @index:        WIF index
 * @info_pa:      Destination addwess fow WIF info (stwuct ionic_wif_info)
 */
stwuct ionic_wif_init_cmd {
	u8     opcode;
	u8     type;
	__we16 index;
	__we32 wsvd;
	__we64 info_pa;
	u8     wsvd2[48];
};

/**
 * stwuct ionic_wif_init_comp - WIF init command compwetion
 * @status:	Status of the command (enum ionic_status_code)
 * @hw_index:	Hawdwawe index of the initiawized WIF
 */
stwuct ionic_wif_init_comp {
	u8 status;
	u8 wsvd;
	__we16 hw_index;
	u8 wsvd2[12];
};

/**
 * stwuct ionic_q_identify_cmd - queue identify command
 * @opcode:     opcode
 * @wif_type:   WIF type (enum ionic_wif_type)
 * @type:       Wogicaw queue type (enum ionic_wogicaw_qtype)
 * @vew:        Highest queue type vewsion that the dwivew suppowts
 */
stwuct ionic_q_identify_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_type;
	u8     type;
	u8     vew;
	u8     wsvd2[58];
};

/**
 * stwuct ionic_q_identify_comp - queue identify command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @vew:        Queue type vewsion that can be used with FW
 */
stwuct ionic_q_identify_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     vew;
	u8     wsvd2[11];
};

/**
 * union ionic_q_identity - queue identity infowmation
 *     @vewsion:        Queue type vewsion that can be used with FW
 *     @suppowted:      Bitfiewd of queue vewsions, fiwst bit = vew 0
 *     @featuwes:       Queue featuwes (enum ionic_q_featuwe, etc)
 *     @desc_sz:        Descwiptow size
 *     @comp_sz:        Compwetion descwiptow size
 *     @sg_desc_sz:     Scattew/Gathew descwiptow size
 *     @max_sg_ewems:   Maximum numbew of Scattew/Gathew ewements
 *     @sg_desc_stwide: Numbew of Scattew/Gathew ewements pew descwiptow
 */
union ionic_q_identity {
	stwuct {
		u8      vewsion;
		u8      suppowted;
		u8      wsvd[6];
		__we64  featuwes;
		__we16  desc_sz;
		__we16  comp_sz;
		__we16  sg_desc_sz;
		__we16  max_sg_ewems;
		__we16  sg_desc_stwide;
	};
	__we32 wowds[478];
};

/**
 * stwuct ionic_q_init_cmd - Queue init command
 * @opcode:       opcode
 * @type:         Wogicaw queue type
 * @vew:          Queue type vewsion
 * @wif_index:    WIF index
 * @index:        (WIF, qtype) wewative admin queue index
 * @intw_index:   Intewwupt contwow wegistew index, ow Event queue index
 * @pid:          Pwocess ID
 * @fwags:
 *    IWQ:        Intewwupt wequested on compwetion
 *    ENA:        Enabwe the queue.  If ENA=0 the queue is initiawized
 *                but wemains disabwed, to be watew enabwed with the
 *                Queue Enabwe command.  If ENA=1, then queue is
 *                initiawized and then enabwed.
 *    SG:         Enabwe Scattew-Gathew on the queue.
 *                in numbew of descs.  The actuaw wing size is
 *                (1 << wing_size).  Fow exampwe, to
 *                sewect a wing size of 64 descwiptows wwite
 *                wing_size = 6.  The minimum wing_size vawue is 2
 *                fow a wing size of 4 descwiptows.  The maximum
 *                wing_size vawue is 16 fow a wing size of 64k
 *                descwiptows.  Vawues of wing_size <2 and >16 awe
 *                wesewved.
 *    EQ:         Enabwe the Event Queue
 * @cos:          Cwass of sewvice fow this queue
 * @wing_size:    Queue wing size, encoded as a wog2(size)
 * @wing_base:    Queue wing base addwess
 * @cq_wing_base: Compwetion queue wing base addwess
 * @sg_wing_base: Scattew/Gathew wing base addwess
 * @featuwes:     Mask of queue featuwes to enabwe, if not in the fwags above.
 */
stwuct ionic_q_init_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	u8     type;
	u8     vew;
	u8     wsvd1[2];
	__we32 index;
	__we16 pid;
	__we16 intw_index;
	__we16 fwags;
#define IONIC_QINIT_F_IWQ	0x01	/* Wequest intewwupt on compwetion */
#define IONIC_QINIT_F_ENA	0x02	/* Enabwe the queue */
#define IONIC_QINIT_F_SG	0x04	/* Enabwe scattew/gathew on the queue */
#define IONIC_QINIT_F_EQ	0x08	/* Enabwe event queue */
#define IONIC_QINIT_F_CMB	0x10	/* Enabwe cmb-based queue */
#define IONIC_QINIT_F_DEBUG	0x80	/* Enabwe queue debugging */
	u8     cos;
	u8     wing_size;
	__we64 wing_base;
	__we64 cq_wing_base;
	__we64 sg_wing_base;
	u8     wsvd2[12];
	__we64 featuwes;
} __packed;

/**
 * stwuct ionic_q_init_comp - Queue init command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @hw_index:   Hawdwawe Queue ID
 * @hw_type:    Hawdwawe Queue type
 * @cowow:      Cowow
 */
stwuct ionic_q_init_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	__we32 hw_index;
	u8     hw_type;
	u8     wsvd2[6];
	u8     cowow;
};

/* the device's intewnaw addwessing uses up to 52 bits */
#define IONIC_ADDW_WEN		52
#define IONIC_ADDW_MASK		(BIT_UWW(IONIC_ADDW_WEN) - 1)

enum ionic_txq_desc_opcode {
	IONIC_TXQ_DESC_OPCODE_CSUM_NONE = 0,
	IONIC_TXQ_DESC_OPCODE_CSUM_PAWTIAW = 1,
	IONIC_TXQ_DESC_OPCODE_CSUM_HW = 2,
	IONIC_TXQ_DESC_OPCODE_TSO = 3,
};

/**
 * stwuct ionic_txq_desc - Ethewnet Tx queue descwiptow fowmat
 * @cmd:          Tx opewation, see IONIC_TXQ_DESC_OPCODE_*:
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_NONE:
 *                      Non-offwoad send.  No segmentation,
 *                      fwagmentation ow checksum cawc/insewtion is
 *                      pewfowmed by device; packet is pwepawed
 *                      to send by softwawe stack and wequiwes
 *                      no fuwthew manipuwation fwom device.
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_PAWTIAW:
 *                      Offwoad 16-bit W4 checksum
 *                      cawcuwation/insewtion.  The device wiww
 *                      cawcuwate the W4 checksum vawue and
 *                      insewt the wesuwt in the packet's W4
 *                      headew checksum fiewd.  The W4 checksum
 *                      is cawcuwated stawting at @csum_stawt bytes
 *                      into the packet to the end of the packet.
 *                      The checksum insewtion position is given
 *                      in @csum_offset, which is the offset fwom
 *                      @csum_stawt to the checksum fiewd in the W4
 *                      headew.  This featuwe is onwy appwicabwe to
 *                      pwotocows such as TCP, UDP and ICMP whewe a
 *                      standawd (i.e. the 'IP-stywe' checksum)
 *                      one's compwement 16-bit checksum is used,
 *                      using an IP pseudo-headew to seed the
 *                      cawcuwation.  Softwawe wiww pwewoad the W4
 *                      checksum fiewd with the IP pseudo-headew
 *                      checksum.
 *
 *                      Fow tunnew encapsuwation, @csum_stawt and
 *                      @csum_offset wefew to the innew W4
 *                      headew.  Suppowted tunnews encapsuwations
 *                      awe: IPIP, GWE, and UDP.  If the @encap
 *                      is cweaw, no fuwthew pwocessing by the
 *                      device is wequiwed; softwawe wiww
 *                      cawcuwate the outew headew checksums.  If
 *                      the @encap is set, the device wiww
 *                      offwoad the outew headew checksums using
 *                      WCO (wocaw checksum offwoad) (see
 *                      Documentation/netwowking/checksum-offwoads.wst
 *                      fow mowe info).
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_HW:
 *                      Offwoad 16-bit checksum computation to hawdwawe.
 *                      If @csum_w3 is set then the packet's W3 checksum is
 *                      updated. Simiwawwy, if @csum_w4 is set the W4
 *                      checksum is updated. If @encap is set then encap headew
 *                      checksums awe awso updated.
 *
 *                   IONIC_TXQ_DESC_OPCODE_TSO:
 *                      Device pewfowms TCP segmentation offwoad
 *                      (TSO).  @hdw_wen is the numbew of bytes
 *                      to the end of TCP headew (the offset to
 *                      the TCP paywoad).  @mss is the desiwed
 *                      MSS, the TCP paywoad wength fow each
 *                      segment.  The device wiww cawcuwate/
 *                      insewt IP (IPv4 onwy) and TCP checksums
 *                      fow each segment.  In the fiwst data
 *                      buffew containing the headew tempwate,
 *                      the dwivew wiww set IPv4 checksum to 0
 *                      and pwewoad TCP checksum with the IP
 *                      pseudo headew cawcuwated with IP wength = 0.
 *
 *                      Suppowted tunnew encapsuwations awe IPIP,
 *                      wayew-3 GWE, and UDP. @hdw_wen incwudes
 *                      both outew and innew headews.  The dwivew
 *                      wiww set IPv4 checksum to zewo and
 *                      pwewoad TCP checksum with IP pseudo
 *                      headew on the innew headew.
 *
 *                      TCP ECN offwoad is suppowted.  The device
 *                      wiww set CWW fwag in the fiwst segment if
 *                      CWW is set in the tempwate headew, and
 *                      cweaw CWW in wemaining segments.
 * @fwags:
 *                vwan:
 *                    Insewt an W2 VWAN headew using @vwan_tci
 *                encap:
 *                    Cawcuwate encap headew checksum
 *                csum_w3:
 *                    Compute W3 headew checksum
 *                csum_w4:
 *                    Compute W4 headew checksum
 *                tso_sot:
 *                    TSO stawt
 *                tso_eot:
 *                    TSO end
 * @num_sg_ewems: Numbew of scattew-gathew ewements in SG
 *                descwiptow
 * @addw:         Fiwst data buffew's DMA addwess
 *                (Subsequent data buffews awe on txq_sg_desc)
 * @wen:          Fiwst data buffew's wength, in bytes
 * @vwan_tci:     VWAN tag to insewt in the packet (if wequested
 *                by @V-bit).  Incwudes .1p and .1q tags
 * @hdw_wen:      Wength of packet headews, incwuding
 *                encapsuwating outew headew, if appwicabwe
 *                Vawid fow opcodes IONIC_TXQ_DESC_OPCODE_CAWC_CSUM and
 *                IONIC_TXQ_DESC_OPCODE_TSO.  Shouwd be set to zewo fow
 *                aww othew modes.  Fow
 *                IONIC_TXQ_DESC_OPCODE_CAWC_CSUM, @hdw_wen is wength
 *                of headews up to innew-most W4 headew.  Fow
 *                IONIC_TXQ_DESC_OPCODE_TSO, @hdw_wen is up to
 *                innew-most W4 paywoad, so incwusive of
 *                innew-most W4 headew.
 * @mss:          Desiwed MSS vawue fow TSO; onwy appwicabwe fow
 *                IONIC_TXQ_DESC_OPCODE_TSO
 * @csum_stawt:   Offset fwom packet to fiwst byte checked in W4 checksum
 * @csum_offset:  Offset fwom csum_stawt to W4 checksum fiewd
 */
stwuct ionic_txq_desc {
	__we64  cmd;
#define IONIC_TXQ_DESC_OPCODE_MASK		0xf
#define IONIC_TXQ_DESC_OPCODE_SHIFT		4
#define IONIC_TXQ_DESC_FWAGS_MASK		0xf
#define IONIC_TXQ_DESC_FWAGS_SHIFT		0
#define IONIC_TXQ_DESC_NSGE_MASK		0xf
#define IONIC_TXQ_DESC_NSGE_SHIFT		8
#define IONIC_TXQ_DESC_ADDW_MASK		(BIT_UWW(IONIC_ADDW_WEN) - 1)
#define IONIC_TXQ_DESC_ADDW_SHIFT		12

/* common fwags */
#define IONIC_TXQ_DESC_FWAG_VWAN		0x1
#define IONIC_TXQ_DESC_FWAG_ENCAP		0x2

/* fwags fow csum_hw opcode */
#define IONIC_TXQ_DESC_FWAG_CSUM_W3		0x4
#define IONIC_TXQ_DESC_FWAG_CSUM_W4		0x8

/* fwags fow tso opcode */
#define IONIC_TXQ_DESC_FWAG_TSO_SOT		0x4
#define IONIC_TXQ_DESC_FWAG_TSO_EOT		0x8

	__we16  wen;
	union {
		__we16  vwan_tci;
		__we16  hwowd0;
	};
	union {
		__we16  csum_stawt;
		__we16  hdw_wen;
		__we16  hwowd1;
	};
	union {
		__we16  csum_offset;
		__we16  mss;
		__we16  hwowd2;
	};
};

static inwine u64 encode_txq_desc_cmd(u8 opcode, u8 fwags,
				      u8 nsge, u64 addw)
{
	u64 cmd;

	cmd = (opcode & IONIC_TXQ_DESC_OPCODE_MASK) << IONIC_TXQ_DESC_OPCODE_SHIFT;
	cmd |= (fwags & IONIC_TXQ_DESC_FWAGS_MASK) << IONIC_TXQ_DESC_FWAGS_SHIFT;
	cmd |= (nsge & IONIC_TXQ_DESC_NSGE_MASK) << IONIC_TXQ_DESC_NSGE_SHIFT;
	cmd |= (addw & IONIC_TXQ_DESC_ADDW_MASK) << IONIC_TXQ_DESC_ADDW_SHIFT;

	wetuwn cmd;
};

static inwine void decode_txq_desc_cmd(u64 cmd, u8 *opcode, u8 *fwags,
				       u8 *nsge, u64 *addw)
{
	*opcode = (cmd >> IONIC_TXQ_DESC_OPCODE_SHIFT) & IONIC_TXQ_DESC_OPCODE_MASK;
	*fwags = (cmd >> IONIC_TXQ_DESC_FWAGS_SHIFT) & IONIC_TXQ_DESC_FWAGS_MASK;
	*nsge = (cmd >> IONIC_TXQ_DESC_NSGE_SHIFT) & IONIC_TXQ_DESC_NSGE_MASK;
	*addw = (cmd >> IONIC_TXQ_DESC_ADDW_SHIFT) & IONIC_TXQ_DESC_ADDW_MASK;
};

/**
 * stwuct ionic_txq_sg_ewem - Twansmit scattew-gathew (SG) descwiptow ewement
 * @addw:      DMA addwess of SG ewement data buffew
 * @wen:       Wength of SG ewement data buffew, in bytes
 */
stwuct ionic_txq_sg_ewem {
	__we64 addw;
	__we16 wen;
	__we16 wsvd[3];
};

/**
 * stwuct ionic_txq_sg_desc - Twansmit scattew-gathew (SG) wist
 * @ewems:     Scattew-gathew ewements
 */
stwuct ionic_txq_sg_desc {
#define IONIC_TX_MAX_SG_EWEMS		8
#define IONIC_TX_SG_DESC_STWIDE		8
	stwuct ionic_txq_sg_ewem ewems[IONIC_TX_MAX_SG_EWEMS];
};

stwuct ionic_txq_sg_desc_v1 {
#define IONIC_TX_MAX_SG_EWEMS_V1		15
#define IONIC_TX_SG_DESC_STWIDE_V1		16
	stwuct ionic_txq_sg_ewem ewems[IONIC_TX_SG_DESC_STWIDE_V1];
};

/**
 * stwuct ionic_txq_comp - Ethewnet twansmit queue compwetion descwiptow
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @cowow:      Cowow bit
 */
stwuct ionic_txq_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     wsvd2[11];
	u8     cowow;
};

enum ionic_wxq_desc_opcode {
	IONIC_WXQ_DESC_OPCODE_SIMPWE = 0,
	IONIC_WXQ_DESC_OPCODE_SG = 1,
};

/**
 * stwuct ionic_wxq_desc - Ethewnet Wx queue descwiptow fowmat
 * @opcode:       Wx opewation, see IONIC_WXQ_DESC_OPCODE_*:
 *
 *                   IONIC_WXQ_DESC_OPCODE_SIMPWE:
 *                      Weceive fuww packet into data buffew
 *                      stawting at @addw.  Wesuwts of
 *                      weceive, incwuding actuaw bytes weceived,
 *                      awe wecowded in Wx compwetion descwiptow.
 *
 * @wen:          Data buffew's wength, in bytes
 * @addw:         Data buffew's DMA addwess
 */
stwuct ionic_wxq_desc {
	u8     opcode;
	u8     wsvd[5];
	__we16 wen;
	__we64 addw;
};

/**
 * stwuct ionic_wxq_sg_ewem - Weceive scattew-gathew (SG) descwiptow ewement
 * @addw:      DMA addwess of SG ewement data buffew
 * @wen:       Wength of SG ewement data buffew, in bytes
 */
stwuct ionic_wxq_sg_ewem {
	__we64 addw;
	__we16 wen;
	__we16 wsvd[3];
};

/**
 * stwuct ionic_wxq_sg_desc - Weceive scattew-gathew (SG) wist
 * @ewems:     Scattew-gathew ewements
 */
stwuct ionic_wxq_sg_desc {
#define IONIC_WX_MAX_SG_EWEMS		8
#define IONIC_WX_SG_DESC_STWIDE		8
	stwuct ionic_wxq_sg_ewem ewems[IONIC_WX_SG_DESC_STWIDE];
};

/**
 * stwuct ionic_wxq_comp - Ethewnet weceive queue compwetion descwiptow
 * @status:       Status of the command (enum ionic_status_code)
 * @num_sg_ewems: Numbew of SG ewements used by this descwiptow
 * @comp_index:   Index in the descwiptow wing fow which this is the compwetion
 * @wss_hash:     32-bit WSS hash
 * @csum:         16-bit sum of the packet's W2 paywoad
 *                If the packet's W2 paywoad is odd wength, an extwa
 *                zewo-vawue byte is incwuded in the @csum cawcuwation but
 *                not incwuded in @wen.
 * @vwan_tci:     VWAN tag stwipped fwom the packet.  Vawid if @VWAN is
 *                set.  Incwudes .1p and .1q tags.
 * @wen:          Weceived packet wength, in bytes.  Excwudes FCS.
 * @csum_cawc     W2 paywoad checksum is computed ow not
 * @csum_fwags:   See IONIC_WXQ_COMP_CSUM_F_*:
 *
 *                  IONIC_WXQ_COMP_CSUM_F_TCP_OK:
 *                    The TCP checksum cawcuwated by the device
 *                    matched the checksum in the weceive packet's
 *                    TCP headew.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_TCP_BAD:
 *                    The TCP checksum cawcuwated by the device did
 *                    not match the checksum in the weceive packet's
 *                    TCP headew.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_UDP_OK:
 *                    The UDP checksum cawcuwated by the device
 *                    matched the checksum in the weceive packet's
 *                    UDP headew
 *
 *                  IONIC_WXQ_COMP_CSUM_F_UDP_BAD:
 *                    The UDP checksum cawcuwated by the device did
 *                    not match the checksum in the weceive packet's
 *                    UDP headew.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_IP_OK:
 *                    The IPv4 checksum cawcuwated by the device
 *                    matched the checksum in the weceive packet's
 *                    fiwst IPv4 headew.  If the weceive packet
 *                    contains both a tunnew IPv4 headew and a
 *                    twanspowt IPv4 headew, the device vawidates the
 *                    checksum fow the both IPv4 headews.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_IP_BAD:
 *                    The IPv4 checksum cawcuwated by the device did
 *                    not match the checksum in the weceive packet's
 *                    fiwst IPv4 headew. If the weceive packet
 *                    contains both a tunnew IPv4 headew and a
 *                    twanspowt IPv4 headew, the device vawidates the
 *                    checksum fow both IP headews.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_VWAN:
 *                    The VWAN headew was stwipped and pwaced in @vwan_tci.
 *
 *                  IONIC_WXQ_COMP_CSUM_F_CAWC:
 *                    The checksum was cawcuwated by the device.
 *
 * @pkt_type_cowow: Packet type and cowow bit; see IONIC_WXQ_COMP_PKT_TYPE_MASK
 */
stwuct ionic_wxq_comp {
	u8     status;
	u8     num_sg_ewems;
	__we16 comp_index;
	__we32 wss_hash;
	__we16 csum;
	__we16 vwan_tci;
	__we16 wen;
	u8     csum_fwags;
#define IONIC_WXQ_COMP_CSUM_F_TCP_OK	0x01
#define IONIC_WXQ_COMP_CSUM_F_TCP_BAD	0x02
#define IONIC_WXQ_COMP_CSUM_F_UDP_OK	0x04
#define IONIC_WXQ_COMP_CSUM_F_UDP_BAD	0x08
#define IONIC_WXQ_COMP_CSUM_F_IP_OK	0x10
#define IONIC_WXQ_COMP_CSUM_F_IP_BAD	0x20
#define IONIC_WXQ_COMP_CSUM_F_VWAN	0x40
#define IONIC_WXQ_COMP_CSUM_F_CAWC	0x80
	u8     pkt_type_cowow;
#define IONIC_WXQ_COMP_PKT_TYPE_MASK	0x7f
};

enum ionic_pkt_type {
	IONIC_PKT_TYPE_NON_IP		= 0x00,
	IONIC_PKT_TYPE_IPV4		= 0x01,
	IONIC_PKT_TYPE_IPV4_TCP		= 0x03,
	IONIC_PKT_TYPE_IPV4_UDP		= 0x05,
	IONIC_PKT_TYPE_IPV6		= 0x08,
	IONIC_PKT_TYPE_IPV6_TCP		= 0x18,
	IONIC_PKT_TYPE_IPV6_UDP		= 0x28,
	/* bewow types awe onwy used if encap offwoads awe enabwed on wif */
	IONIC_PKT_TYPE_ENCAP_NON_IP	= 0x40,
	IONIC_PKT_TYPE_ENCAP_IPV4	= 0x41,
	IONIC_PKT_TYPE_ENCAP_IPV4_TCP	= 0x43,
	IONIC_PKT_TYPE_ENCAP_IPV4_UDP	= 0x45,
	IONIC_PKT_TYPE_ENCAP_IPV6	= 0x48,
	IONIC_PKT_TYPE_ENCAP_IPV6_TCP	= 0x58,
	IONIC_PKT_TYPE_ENCAP_IPV6_UDP	= 0x68,
};

enum ionic_eth_hw_featuwes {
	IONIC_ETH_HW_VWAN_TX_TAG	= BIT(0),
	IONIC_ETH_HW_VWAN_WX_STWIP	= BIT(1),
	IONIC_ETH_HW_VWAN_WX_FIWTEW	= BIT(2),
	IONIC_ETH_HW_WX_HASH		= BIT(3),
	IONIC_ETH_HW_WX_CSUM		= BIT(4),
	IONIC_ETH_HW_TX_SG		= BIT(5),
	IONIC_ETH_HW_WX_SG		= BIT(6),
	IONIC_ETH_HW_TX_CSUM		= BIT(7),
	IONIC_ETH_HW_TSO		= BIT(8),
	IONIC_ETH_HW_TSO_IPV6		= BIT(9),
	IONIC_ETH_HW_TSO_ECN		= BIT(10),
	IONIC_ETH_HW_TSO_GWE		= BIT(11),
	IONIC_ETH_HW_TSO_GWE_CSUM	= BIT(12),
	IONIC_ETH_HW_TSO_IPXIP4		= BIT(13),
	IONIC_ETH_HW_TSO_IPXIP6		= BIT(14),
	IONIC_ETH_HW_TSO_UDP		= BIT(15),
	IONIC_ETH_HW_TSO_UDP_CSUM	= BIT(16),
	IONIC_ETH_HW_WX_CSUM_GENEVE	= BIT(17),
	IONIC_ETH_HW_TX_CSUM_GENEVE	= BIT(18),
	IONIC_ETH_HW_TSO_GENEVE		= BIT(19),
	IONIC_ETH_HW_TIMESTAMP		= BIT(20),
};

/**
 * enum ionic_pkt_cwass - Packet cwassification mask.
 *
 * Used with wx steewing fiwtew, packets indicated by the mask can be steewed
 * towawd a specific weceive queue.
 *
 * @IONIC_PKT_CWS_NTP_AWW:          Aww NTP packets.
 * @IONIC_PKT_CWS_PTP1_SYNC:        PTPv1 sync
 * @IONIC_PKT_CWS_PTP1_DWEQ:        PTPv1 deway-wequest
 * @IONIC_PKT_CWS_PTP1_AWW:         PTPv1 aww packets
 * @IONIC_PKT_CWS_PTP2_W4_SYNC:     PTPv2-UDP sync
 * @IONIC_PKT_CWS_PTP2_W4_DWEQ:     PTPv2-UDP deway-wequest
 * @IONIC_PKT_CWS_PTP2_W4_AWW:      PTPv2-UDP aww packets
 * @IONIC_PKT_CWS_PTP2_W2_SYNC:     PTPv2-ETH sync
 * @IONIC_PKT_CWS_PTP2_W2_DWEQ:     PTPv2-ETH deway-wequest
 * @IONIC_PKT_CWS_PTP2_W2_AWW:      PTPv2-ETH aww packets
 * @IONIC_PKT_CWS_PTP2_SYNC:        PTPv2 sync
 * @IONIC_PKT_CWS_PTP2_DWEQ:        PTPv2 deway-wequest
 * @IONIC_PKT_CWS_PTP2_AWW:         PTPv2 aww packets
 * @IONIC_PKT_CWS_PTP_SYNC:         PTP sync
 * @IONIC_PKT_CWS_PTP_DWEQ:         PTP deway-wequest
 * @IONIC_PKT_CWS_PTP_AWW:          PTP aww packets
 */
enum ionic_pkt_cwass {
	IONIC_PKT_CWS_NTP_AWW		= BIT(0),

	IONIC_PKT_CWS_PTP1_SYNC		= BIT(1),
	IONIC_PKT_CWS_PTP1_DWEQ		= BIT(2),
	IONIC_PKT_CWS_PTP1_AWW		= BIT(3) |
		IONIC_PKT_CWS_PTP1_SYNC | IONIC_PKT_CWS_PTP1_DWEQ,

	IONIC_PKT_CWS_PTP2_W4_SYNC	= BIT(4),
	IONIC_PKT_CWS_PTP2_W4_DWEQ	= BIT(5),
	IONIC_PKT_CWS_PTP2_W4_AWW	= BIT(6) |
		IONIC_PKT_CWS_PTP2_W4_SYNC | IONIC_PKT_CWS_PTP2_W4_DWEQ,

	IONIC_PKT_CWS_PTP2_W2_SYNC	= BIT(7),
	IONIC_PKT_CWS_PTP2_W2_DWEQ	= BIT(8),
	IONIC_PKT_CWS_PTP2_W2_AWW	= BIT(9) |
		IONIC_PKT_CWS_PTP2_W2_SYNC | IONIC_PKT_CWS_PTP2_W2_DWEQ,

	IONIC_PKT_CWS_PTP2_SYNC		=
		IONIC_PKT_CWS_PTP2_W4_SYNC | IONIC_PKT_CWS_PTP2_W2_SYNC,
	IONIC_PKT_CWS_PTP2_DWEQ		=
		IONIC_PKT_CWS_PTP2_W4_DWEQ | IONIC_PKT_CWS_PTP2_W2_DWEQ,
	IONIC_PKT_CWS_PTP2_AWW		=
		IONIC_PKT_CWS_PTP2_W4_AWW | IONIC_PKT_CWS_PTP2_W2_AWW,

	IONIC_PKT_CWS_PTP_SYNC		=
		IONIC_PKT_CWS_PTP1_SYNC | IONIC_PKT_CWS_PTP2_SYNC,
	IONIC_PKT_CWS_PTP_DWEQ		=
		IONIC_PKT_CWS_PTP1_DWEQ | IONIC_PKT_CWS_PTP2_DWEQ,
	IONIC_PKT_CWS_PTP_AWW		=
		IONIC_PKT_CWS_PTP1_AWW | IONIC_PKT_CWS_PTP2_AWW,
};

/**
 * stwuct ionic_q_contwow_cmd - Queue contwow command
 * @opcode:     opcode
 * @type:       Queue type
 * @wif_index:  WIF index
 * @index:      Queue index
 * @opew:       Opewation (enum ionic_q_contwow_opew)
 */
stwuct ionic_q_contwow_cmd {
	u8     opcode;
	u8     type;
	__we16 wif_index;
	__we32 index;
	u8     opew;
	u8     wsvd[55];
};

typedef stwuct ionic_admin_comp ionic_q_contwow_comp;

enum q_contwow_opew {
	IONIC_Q_DISABWE		= 0,
	IONIC_Q_ENABWE		= 1,
	IONIC_Q_HANG_WESET	= 2,
};

/**
 * enum ionic_phy_type - Physicaw connection type
 * @IONIC_PHY_TYPE_NONE:    No PHY instawwed
 * @IONIC_PHY_TYPE_COPPEW:  Coppew PHY
 * @IONIC_PHY_TYPE_FIBEW:   Fibew PHY
 */
enum ionic_phy_type {
	IONIC_PHY_TYPE_NONE	= 0,
	IONIC_PHY_TYPE_COPPEW	= 1,
	IONIC_PHY_TYPE_FIBEW	= 2,
};

/**
 * enum ionic_xcvw_state - Twansceivew status
 * @IONIC_XCVW_STATE_WEMOVED:        Twansceivew wemoved
 * @IONIC_XCVW_STATE_INSEWTED:       Twansceivew insewted
 * @IONIC_XCVW_STATE_PENDING:        Twansceivew pending
 * @IONIC_XCVW_STATE_SPWOM_WEAD:     Twansceivew data wead
 * @IONIC_XCVW_STATE_SPWOM_WEAD_EWW: Twansceivew data wead ewwow
 */
enum ionic_xcvw_state {
	IONIC_XCVW_STATE_WEMOVED	 = 0,
	IONIC_XCVW_STATE_INSEWTED	 = 1,
	IONIC_XCVW_STATE_PENDING	 = 2,
	IONIC_XCVW_STATE_SPWOM_WEAD	 = 3,
	IONIC_XCVW_STATE_SPWOM_WEAD_EWW	 = 4,
};

/**
 * enum ionic_xcvw_pid - Suppowted wink modes
 */
enum ionic_xcvw_pid {
	IONIC_XCVW_PID_UNKNOWN           = 0,

	/* CU */
	IONIC_XCVW_PID_QSFP_100G_CW4     = 1,
	IONIC_XCVW_PID_QSFP_40GBASE_CW4  = 2,
	IONIC_XCVW_PID_SFP_25GBASE_CW_S  = 3,
	IONIC_XCVW_PID_SFP_25GBASE_CW_W  = 4,
	IONIC_XCVW_PID_SFP_25GBASE_CW_N  = 5,

	/* Fibew */
	IONIC_XCVW_PID_QSFP_100G_AOC    = 50,
	IONIC_XCVW_PID_QSFP_100G_ACC    = 51,
	IONIC_XCVW_PID_QSFP_100G_SW4    = 52,
	IONIC_XCVW_PID_QSFP_100G_WW4    = 53,
	IONIC_XCVW_PID_QSFP_100G_EW4    = 54,
	IONIC_XCVW_PID_QSFP_40GBASE_EW4 = 55,
	IONIC_XCVW_PID_QSFP_40GBASE_SW4 = 56,
	IONIC_XCVW_PID_QSFP_40GBASE_WW4 = 57,
	IONIC_XCVW_PID_QSFP_40GBASE_AOC = 58,
	IONIC_XCVW_PID_SFP_25GBASE_SW   = 59,
	IONIC_XCVW_PID_SFP_25GBASE_WW   = 60,
	IONIC_XCVW_PID_SFP_25GBASE_EW   = 61,
	IONIC_XCVW_PID_SFP_25GBASE_AOC  = 62,
	IONIC_XCVW_PID_SFP_10GBASE_SW   = 63,
	IONIC_XCVW_PID_SFP_10GBASE_WW   = 64,
	IONIC_XCVW_PID_SFP_10GBASE_WWM  = 65,
	IONIC_XCVW_PID_SFP_10GBASE_EW   = 66,
	IONIC_XCVW_PID_SFP_10GBASE_AOC  = 67,
	IONIC_XCVW_PID_SFP_10GBASE_CU   = 68,
	IONIC_XCVW_PID_QSFP_100G_CWDM4  = 69,
	IONIC_XCVW_PID_QSFP_100G_PSM4   = 70,
	IONIC_XCVW_PID_SFP_25GBASE_ACC  = 71,
	IONIC_XCVW_PID_SFP_10GBASE_T    = 72,
	IONIC_XCVW_PID_SFP_1000BASE_T   = 73,
};

/**
 * enum ionic_powt_type - Powt types
 * @IONIC_POWT_TYPE_NONE:           Powt type not configuwed
 * @IONIC_POWT_TYPE_ETH:            Powt cawwies ethewnet twaffic (inband)
 * @IONIC_POWT_TYPE_MGMT:           Powt cawwies mgmt twaffic (out-of-band)
 */
enum ionic_powt_type {
	IONIC_POWT_TYPE_NONE = 0,
	IONIC_POWT_TYPE_ETH  = 1,
	IONIC_POWT_TYPE_MGMT = 2,
};

/**
 * enum ionic_powt_admin_state - Powt config state
 * @IONIC_POWT_ADMIN_STATE_NONE:    Powt admin state not configuwed
 * @IONIC_POWT_ADMIN_STATE_DOWN:    Powt admin disabwed
 * @IONIC_POWT_ADMIN_STATE_UP:      Powt admin enabwed
 */
enum ionic_powt_admin_state {
	IONIC_POWT_ADMIN_STATE_NONE = 0,
	IONIC_POWT_ADMIN_STATE_DOWN = 1,
	IONIC_POWT_ADMIN_STATE_UP   = 2,
};

/**
 * enum ionic_powt_opew_status - Powt opewationaw status
 * @IONIC_POWT_OPEW_STATUS_NONE:    Powt disabwed
 * @IONIC_POWT_OPEW_STATUS_UP:      Powt wink status up
 * @IONIC_POWT_OPEW_STATUS_DOWN:    Powt wink status down
 */
enum ionic_powt_opew_status {
	IONIC_POWT_OPEW_STATUS_NONE  = 0,
	IONIC_POWT_OPEW_STATUS_UP    = 1,
	IONIC_POWT_OPEW_STATUS_DOWN  = 2,
};

/**
 * enum ionic_powt_fec_type - Ethewnet Fowwawd ewwow cowwection (FEC) modes
 * @IONIC_POWT_FEC_TYPE_NONE:       FEC Disabwed
 * @IONIC_POWT_FEC_TYPE_FC:         FiweCode FEC
 * @IONIC_POWT_FEC_TYPE_WS:         WeedSowomon FEC
 */
enum ionic_powt_fec_type {
	IONIC_POWT_FEC_TYPE_NONE = 0,
	IONIC_POWT_FEC_TYPE_FC   = 1,
	IONIC_POWT_FEC_TYPE_WS   = 2,
};

/**
 * enum ionic_powt_pause_type - Ethewnet pause (fwow contwow) modes
 * @IONIC_POWT_PAUSE_TYPE_NONE:     Disabwe Pause
 * @IONIC_POWT_PAUSE_TYPE_WINK:     Wink wevew pause
 * @IONIC_POWT_PAUSE_TYPE_PFC:      Pwiowity-Fwow Contwow
 */
enum ionic_powt_pause_type {
	IONIC_POWT_PAUSE_TYPE_NONE = 0,
	IONIC_POWT_PAUSE_TYPE_WINK = 1,
	IONIC_POWT_PAUSE_TYPE_PFC  = 2,
};

/**
 * enum ionic_powt_woopback_mode - Woopback modes
 * @IONIC_POWT_WOOPBACK_MODE_NONE:  Disabwe woopback
 * @IONIC_POWT_WOOPBACK_MODE_MAC:   MAC woopback
 * @IONIC_POWT_WOOPBACK_MODE_PHY:   PHY/SewDes woopback
 */
enum ionic_powt_woopback_mode {
	IONIC_POWT_WOOPBACK_MODE_NONE = 0,
	IONIC_POWT_WOOPBACK_MODE_MAC  = 1,
	IONIC_POWT_WOOPBACK_MODE_PHY  = 2,
};

/**
 * stwuct ionic_xcvw_status - Twansceivew Status infowmation
 * @state:    Twansceivew status (enum ionic_xcvw_state)
 * @phy:      Physicaw connection type (enum ionic_phy_type)
 * @pid:      Twansceivew wink mode (enum ionic_xcvw_pid)
 * @spwom:    Twansceivew spwom contents
 */
stwuct ionic_xcvw_status {
	u8     state;
	u8     phy;
	__we16 pid;
	u8     spwom[256];
};

/**
 * union ionic_powt_config - Powt configuwation
 * @speed:              powt speed (in Mbps)
 * @mtu:                mtu
 * @state:              powt admin state (enum ionic_powt_admin_state)
 * @an_enabwe:          autoneg enabwe
 * @fec_type:           fec type (enum ionic_powt_fec_type)
 * @pause_type:         pause type (enum ionic_powt_pause_type)
 * @woopback_mode:      woopback mode (enum ionic_powt_woopback_mode)
 */
union ionic_powt_config {
	stwuct {
#define IONIC_SPEED_100G	100000	/* 100G in Mbps */
#define IONIC_SPEED_50G		50000	/* 50G in Mbps */
#define IONIC_SPEED_40G		40000	/* 40G in Mbps */
#define IONIC_SPEED_25G		25000	/* 25G in Mbps */
#define IONIC_SPEED_10G		10000	/* 10G in Mbps */
#define IONIC_SPEED_1G		1000	/* 1G in Mbps */
		__we32 speed;
		__we32 mtu;
		u8     state;
		u8     an_enabwe;
		u8     fec_type;
#define IONIC_PAUSE_TYPE_MASK		0x0f
#define IONIC_PAUSE_FWAGS_MASK		0xf0
#define IONIC_PAUSE_F_TX		0x10
#define IONIC_PAUSE_F_WX		0x20
		u8     pause_type;
		u8     woopback_mode;
	};
	__we32 wowds[64];
};

/**
 * stwuct ionic_powt_status - Powt Status infowmation
 * @status:             wink status (enum ionic_powt_opew_status)
 * @id:                 powt id
 * @speed:              wink speed (in Mbps)
 * @wink_down_count:    numbew of times wink went fwom up to down
 * @fec_type:           fec type (enum ionic_powt_fec_type)
 * @xcvw:               twansceivew status
 */
stwuct ionic_powt_status {
	__we32 id;
	__we32 speed;
	u8     status;
	__we16 wink_down_count;
	u8     fec_type;
	u8     wsvd[48];
	stwuct ionic_xcvw_status  xcvw;
} __packed;

/**
 * stwuct ionic_powt_identify_cmd - Powt identify command
 * @opcode:     opcode
 * @index:      powt index
 * @vew:        Highest vewsion of identify suppowted by dwivew
 */
stwuct ionic_powt_identify_cmd {
	u8 opcode;
	u8 index;
	u8 vew;
	u8 wsvd[61];
};

/**
 * stwuct ionic_powt_identify_comp - Powt identify command compwetion
 * @status: Status of the command (enum ionic_status_code)
 * @vew:    Vewsion of identify wetuwned by device
 */
stwuct ionic_powt_identify_comp {
	u8 status;
	u8 vew;
	u8 wsvd[14];
};

/**
 * stwuct ionic_powt_init_cmd - Powt initiawization command
 * @opcode:     opcode
 * @index:      powt index
 * @info_pa:    destination addwess fow powt info (stwuct ionic_powt_info)
 */
stwuct ionic_powt_init_cmd {
	u8     opcode;
	u8     index;
	u8     wsvd[6];
	__we64 info_pa;
	u8     wsvd2[48];
};

/**
 * stwuct ionic_powt_init_comp - Powt initiawization command compwetion
 * @status: Status of the command (enum ionic_status_code)
 */
stwuct ionic_powt_init_comp {
	u8 status;
	u8 wsvd[15];
};

/**
 * stwuct ionic_powt_weset_cmd - Powt weset command
 * @opcode:     opcode
 * @index:      powt index
 */
stwuct ionic_powt_weset_cmd {
	u8 opcode;
	u8 index;
	u8 wsvd[62];
};

/**
 * stwuct ionic_powt_weset_comp - Powt weset command compwetion
 * @status: Status of the command (enum ionic_status_code)
 */
stwuct ionic_powt_weset_comp {
	u8 status;
	u8 wsvd[15];
};

/**
 * enum ionic_stats_ctw_cmd - Wist of commands fow stats contwow
 * @IONIC_STATS_CTW_WESET:      Weset statistics
 */
enum ionic_stats_ctw_cmd {
	IONIC_STATS_CTW_WESET		= 0,
};

/**
 * enum ionic_txstamp_mode - Wist of TX Timestamping Modes
 * @IONIC_TXSTAMP_OFF:           Disabwe TX hawdwawe timetamping.
 * @IONIC_TXSTAMP_ON:            Enabwe wocaw TX hawdwawe timetamping.
 * @IONIC_TXSTAMP_ONESTEP_SYNC:  Modify TX PTP Sync packets.
 * @IONIC_TXSTAMP_ONESTEP_P2P:   Modify TX PTP Sync and PDewayWesp.
 */
enum ionic_txstamp_mode {
	IONIC_TXSTAMP_OFF		= 0,
	IONIC_TXSTAMP_ON		= 1,
	IONIC_TXSTAMP_ONESTEP_SYNC	= 2,
	IONIC_TXSTAMP_ONESTEP_P2P	= 3,
};

/**
 * enum ionic_powt_attw - Wist of device attwibutes
 * @IONIC_POWT_ATTW_STATE:      Powt state attwibute
 * @IONIC_POWT_ATTW_SPEED:      Powt speed attwibute
 * @IONIC_POWT_ATTW_MTU:        Powt MTU attwibute
 * @IONIC_POWT_ATTW_AUTONEG:    Powt autonegotiation attwibute
 * @IONIC_POWT_ATTW_FEC:        Powt FEC attwibute
 * @IONIC_POWT_ATTW_PAUSE:      Powt pause attwibute
 * @IONIC_POWT_ATTW_WOOPBACK:   Powt woopback attwibute
 * @IONIC_POWT_ATTW_STATS_CTWW: Powt statistics contwow attwibute
 */
enum ionic_powt_attw {
	IONIC_POWT_ATTW_STATE		= 0,
	IONIC_POWT_ATTW_SPEED		= 1,
	IONIC_POWT_ATTW_MTU		= 2,
	IONIC_POWT_ATTW_AUTONEG		= 3,
	IONIC_POWT_ATTW_FEC		= 4,
	IONIC_POWT_ATTW_PAUSE		= 5,
	IONIC_POWT_ATTW_WOOPBACK	= 6,
	IONIC_POWT_ATTW_STATS_CTWW	= 7,
};

/**
 * stwuct ionic_powt_setattw_cmd - Set powt attwibutes on the NIC
 * @opcode:         Opcode
 * @index:          Powt index
 * @attw:           Attwibute type (enum ionic_powt_attw)
 * @state:          Powt state
 * @speed:          Powt speed
 * @mtu:            Powt MTU
 * @an_enabwe:      Powt autonegotiation setting
 * @fec_type:       Powt FEC type setting
 * @pause_type:     Powt pause type setting
 * @woopback_mode:  Powt woopback mode
 * @stats_ctw:      Powt stats setting
 */
stwuct ionic_powt_setattw_cmd {
	u8     opcode;
	u8     index;
	u8     attw;
	u8     wsvd;
	union {
		u8      state;
		__we32  speed;
		__we32  mtu;
		u8      an_enabwe;
		u8      fec_type;
		u8      pause_type;
		u8      woopback_mode;
		u8      stats_ctw;
		u8      wsvd2[60];
	};
};

/**
 * stwuct ionic_powt_setattw_comp - Powt set attw command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @cowow:      Cowow bit
 */
stwuct ionic_powt_setattw_comp {
	u8     status;
	u8     wsvd[14];
	u8     cowow;
};

/**
 * stwuct ionic_powt_getattw_cmd - Get powt attwibutes fwom the NIC
 * @opcode:     Opcode
 * @index:      powt index
 * @attw:       Attwibute type (enum ionic_powt_attw)
 */
stwuct ionic_powt_getattw_cmd {
	u8     opcode;
	u8     index;
	u8     attw;
	u8     wsvd[61];
};

/**
 * stwuct ionic_powt_getattw_comp - Powt get attw command compwetion
 * @status:         Status of the command (enum ionic_status_code)
 * @state:          Powt state
 * @speed:          Powt speed
 * @mtu:            Powt MTU
 * @an_enabwe:      Powt autonegotiation setting
 * @fec_type:       Powt FEC type setting
 * @pause_type:     Powt pause type setting
 * @woopback_mode:  Powt woopback mode
 * @cowow:          Cowow bit
 */
stwuct ionic_powt_getattw_comp {
	u8     status;
	u8     wsvd[3];
	union {
		u8      state;
		__we32  speed;
		__we32  mtu;
		u8      an_enabwe;
		u8      fec_type;
		u8      pause_type;
		u8      woopback_mode;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * stwuct ionic_wif_status - WIF status wegistew
 * @eid:             most wecent NotifyQ event id
 * @powt_num:        powt the WIF is connected to
 * @wink_status:     powt status (enum ionic_powt_opew_status)
 * @wink_speed:      speed of wink in Mbps
 * @wink_down_count: numbew of times wink went fwom up to down
 */
stwuct ionic_wif_status {
	__we64 eid;
	u8     powt_num;
	u8     wsvd;
	__we16 wink_status;
	__we32 wink_speed;		/* units of 1Mbps: eg 10000 = 10Gbps */
	__we16 wink_down_count;
	u8      wsvd2[46];
};

/**
 * stwuct ionic_wif_weset_cmd - WIF weset command
 * @opcode:    opcode
 * @index:     WIF index
 */
stwuct ionic_wif_weset_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 index;
	__we32 wsvd2[15];
};

typedef stwuct ionic_admin_comp ionic_wif_weset_comp;

enum ionic_dev_state {
	IONIC_DEV_DISABWE	= 0,
	IONIC_DEV_ENABWE	= 1,
	IONIC_DEV_HANG_WESET	= 2,
};

/**
 * enum ionic_dev_attw - Wist of device attwibutes
 * @IONIC_DEV_ATTW_STATE:     Device state attwibute
 * @IONIC_DEV_ATTW_NAME:      Device name attwibute
 * @IONIC_DEV_ATTW_FEATUWES:  Device featuwe attwibutes
 */
enum ionic_dev_attw {
	IONIC_DEV_ATTW_STATE    = 0,
	IONIC_DEV_ATTW_NAME     = 1,
	IONIC_DEV_ATTW_FEATUWES = 2,
};

/**
 * stwuct ionic_dev_setattw_cmd - Set Device attwibutes on the NIC
 * @opcode:     Opcode
 * @attw:       Attwibute type (enum ionic_dev_attw)
 * @state:      Device state (enum ionic_dev_state)
 * @name:       The bus info, e.g. PCI swot-device-function, 0 tewminated
 * @featuwes:   Device featuwes
 */
stwuct ionic_dev_setattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 wsvd;
	union {
		u8      state;
		chaw    name[IONIC_IFNAMSIZ];
		__we64  featuwes;
		u8      wsvd2[60];
	} __packed;
};

/**
 * stwuct ionic_dev_setattw_comp - Device set attw command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @featuwes:   Device featuwes
 * @cowow:      Cowow bit
 */
stwuct ionic_dev_setattw_comp {
	u8     status;
	u8     wsvd[3];
	union {
		__we64  featuwes;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * stwuct ionic_dev_getattw_cmd - Get Device attwibutes fwom the NIC
 * @opcode:     opcode
 * @attw:       Attwibute type (enum ionic_dev_attw)
 */
stwuct ionic_dev_getattw_cmd {
	u8     opcode;
	u8     attw;
	u8     wsvd[62];
};

/**
 * stwuct ionic_dev_setattw_comp - Device set attw command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @featuwes:   Device featuwes
 * @cowow:      Cowow bit
 */
stwuct ionic_dev_getattw_comp {
	u8     status;
	u8     wsvd[3];
	union {
		__we64  featuwes;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * WSS pawametews
 */
#define IONIC_WSS_HASH_KEY_SIZE		40

enum ionic_wss_hash_types {
	IONIC_WSS_TYPE_IPV4	= BIT(0),
	IONIC_WSS_TYPE_IPV4_TCP	= BIT(1),
	IONIC_WSS_TYPE_IPV4_UDP	= BIT(2),
	IONIC_WSS_TYPE_IPV6	= BIT(3),
	IONIC_WSS_TYPE_IPV6_TCP	= BIT(4),
	IONIC_WSS_TYPE_IPV6_UDP	= BIT(5),
};

/**
 * enum ionic_wif_attw - Wist of WIF attwibutes
 * @IONIC_WIF_ATTW_STATE:       WIF state attwibute
 * @IONIC_WIF_ATTW_NAME:        WIF name attwibute
 * @IONIC_WIF_ATTW_MTU:         WIF MTU attwibute
 * @IONIC_WIF_ATTW_MAC:         WIF MAC attwibute
 * @IONIC_WIF_ATTW_FEATUWES:    WIF featuwes attwibute
 * @IONIC_WIF_ATTW_WSS:         WIF WSS attwibute
 * @IONIC_WIF_ATTW_STATS_CTWW:  WIF statistics contwow attwibute
 * @IONIC_WIF_ATTW_TXSTAMP:     WIF TX timestamping mode
 */
enum ionic_wif_attw {
	IONIC_WIF_ATTW_STATE        = 0,
	IONIC_WIF_ATTW_NAME         = 1,
	IONIC_WIF_ATTW_MTU          = 2,
	IONIC_WIF_ATTW_MAC          = 3,
	IONIC_WIF_ATTW_FEATUWES     = 4,
	IONIC_WIF_ATTW_WSS          = 5,
	IONIC_WIF_ATTW_STATS_CTWW   = 6,
	IONIC_WIF_ATTW_TXSTAMP      = 7,
};

/**
 * stwuct ionic_wif_setattw_cmd - Set WIF attwibutes on the NIC
 * @opcode:     Opcode
 * @attw:       Attwibute type (enum ionic_wif_attw)
 * @index:      WIF index
 * @state:      WIF state (enum ionic_wif_state)
 * @name:       The netdev name stwing, 0 tewminated
 * @mtu:        Mtu
 * @mac:        Station mac
 * @featuwes:   Featuwes (enum ionic_eth_hw_featuwes)
 * @wss:        WSS pwopewties
 *              @types:     The hash types to enabwe (see wss_hash_types)
 *              @key:       The hash secwet key
 *              @addw:      Addwess fow the indiwection tabwe shawed memowy
 * @stats_ctw:  stats contwow commands (enum ionic_stats_ctw_cmd)
 * @txstamp:    TX Timestamping Mode (enum ionic_txstamp_mode)
 */
stwuct ionic_wif_setattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 index;
	union {
		u8      state;
		chaw    name[IONIC_IFNAMSIZ];
		__we32  mtu;
		u8      mac[6];
		__we64  featuwes;
		stwuct {
			__we16 types;
			u8     key[IONIC_WSS_HASH_KEY_SIZE];
			u8     wsvd[6];
			__we64 addw;
		} wss;
		u8      stats_ctw;
		__we16 txstamp_mode;
		u8      wsvd[60];
	} __packed;
};

/**
 * stwuct ionic_wif_setattw_comp - WIF set attw command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @featuwes:   featuwes (enum ionic_eth_hw_featuwes)
 * @cowow:      Cowow bit
 */
stwuct ionic_wif_setattw_comp {
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
 * stwuct ionic_wif_getattw_cmd - Get WIF attwibutes fwom the NIC
 * @opcode:     Opcode
 * @attw:       Attwibute type (enum ionic_wif_attw)
 * @index:      WIF index
 */
stwuct ionic_wif_getattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 index;
	u8     wsvd[60];
};

/**
 * stwuct ionic_wif_getattw_comp - WIF get attw command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @state:      WIF state (enum ionic_wif_state)
 * @name:       The netdev name stwing, 0 tewminated
 * @mtu:        Mtu
 * @mac:        Station mac
 * @featuwes:   Featuwes (enum ionic_eth_hw_featuwes)
 * @txstamp:    TX Timestamping Mode (enum ionic_txstamp_mode)
 * @cowow:      Cowow bit
 */
stwuct ionic_wif_getattw_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	union {
		u8      state;
		__we32  mtu;
		u8      mac[6];
		__we64  featuwes;
		__we16  txstamp_mode;
		u8      wsvd2[11];
	} __packed;
	u8     cowow;
};

/**
 * stwuct ionic_wif_setphc_cmd - Set WIF PTP Hawdwawe Cwock
 * @opcode:     Opcode
 * @wif_index:  WIF index
 * @tick:       Hawdwawe stamp tick of an instant in time.
 * @nsec:       Nanosecond stamp of the same instant.
 * @fwac:       Fwactionaw nanoseconds at the same instant.
 * @muwt:       Cycwe to nanosecond muwtipwiew.
 * @shift:      Cycwe to nanosecond divisow (powew of two).
 */
stwuct ionic_wif_setphc_cmd {
	u8	opcode;
	u8	wsvd1;
	__we16  wif_index;
	u8      wsvd2[4];
	__we64	tick;
	__we64	nsec;
	__we64	fwac;
	__we32	muwt;
	__we32	shift;
	u8     wsvd3[24];
};

enum ionic_wx_mode {
	IONIC_WX_MODE_F_UNICAST		= BIT(0),
	IONIC_WX_MODE_F_MUWTICAST	= BIT(1),
	IONIC_WX_MODE_F_BWOADCAST	= BIT(2),
	IONIC_WX_MODE_F_PWOMISC		= BIT(3),
	IONIC_WX_MODE_F_AWWMUWTI	= BIT(4),
	IONIC_WX_MODE_F_WDMA_SNIFFEW	= BIT(5),
};

/**
 * stwuct ionic_wx_mode_set_cmd - Set WIF's Wx mode command
 * @opcode:     opcode
 * @wif_index:  WIF index
 * @wx_mode:    Wx mode fwags:
 *                  IONIC_WX_MODE_F_UNICAST: Accept known unicast packets
 *                  IONIC_WX_MODE_F_MUWTICAST: Accept known muwticast packets
 *                  IONIC_WX_MODE_F_BWOADCAST: Accept bwoadcast packets
 *                  IONIC_WX_MODE_F_PWOMISC: Accept any packets
 *                  IONIC_WX_MODE_F_AWWMUWTI: Accept any muwticast packets
 *                  IONIC_WX_MODE_F_WDMA_SNIFFEW: Sniff WDMA packets
 */
stwuct ionic_wx_mode_set_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	__we16 wx_mode;
	__we16 wsvd2[29];
};

typedef stwuct ionic_admin_comp ionic_wx_mode_set_comp;

enum ionic_wx_fiwtew_match_type {
	IONIC_WX_FIWTEW_MATCH_VWAN	= 0x0,
	IONIC_WX_FIWTEW_MATCH_MAC	= 0x1,
	IONIC_WX_FIWTEW_MATCH_MAC_VWAN	= 0x2,
	IONIC_WX_FIWTEW_STEEW_PKTCWASS	= 0x10,
};

/**
 * stwuct ionic_wx_fiwtew_add_cmd - Add WIF Wx fiwtew command
 * @opcode:     opcode
 * @qtype:      Queue type
 * @wif_index:  WIF index
 * @qid:        Queue ID
 * @match:      Wx fiwtew match type (see IONIC_WX_FIWTEW_MATCH_xxx)
 * @vwan:       VWAN fiwtew
 *              @vwan:  VWAN ID
 * @mac:        MAC fiwtew
 *              @addw:  MAC addwess (netwowk-byte owdew)
 * @mac_vwan:   MACVWAN fiwtew
 *              @vwan:  VWAN ID
 *              @addw:  MAC addwess (netwowk-byte owdew)
 * @pkt_cwass:  Packet cwassification fiwtew
 */
stwuct ionic_wx_fiwtew_add_cmd {
	u8     opcode;
	u8     qtype;
	__we16 wif_index;
	__we32 qid;
	__we16 match;
	union {
		stwuct {
			__we16 vwan;
		} vwan;
		stwuct {
			u8     addw[6];
		} mac;
		stwuct {
			__we16 vwan;
			u8     addw[6];
		} mac_vwan;
		__we64 pkt_cwass;
		u8 wsvd[54];
	} __packed;
};

/**
 * stwuct ionic_wx_fiwtew_add_comp - Add WIF Wx fiwtew command compwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @fiwtew_id:  Fiwtew ID
 * @cowow:      Cowow bit
 */
stwuct ionic_wx_fiwtew_add_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	__we32 fiwtew_id;
	u8     wsvd2[7];
	u8     cowow;
};

/**
 * stwuct ionic_wx_fiwtew_dew_cmd - Dewete WIF Wx fiwtew command
 * @opcode:     opcode
 * @wif_index:  WIF index
 * @fiwtew_id:  Fiwtew ID
 */
stwuct ionic_wx_fiwtew_dew_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	__we32 fiwtew_id;
	u8     wsvd2[56];
};

typedef stwuct ionic_admin_comp ionic_wx_fiwtew_dew_comp;

enum ionic_vf_attw {
	IONIC_VF_ATTW_SPOOFCHK	= 1,
	IONIC_VF_ATTW_TWUST	= 2,
	IONIC_VF_ATTW_MAC	= 3,
	IONIC_VF_ATTW_WINKSTATE	= 4,
	IONIC_VF_ATTW_VWAN	= 5,
	IONIC_VF_ATTW_WATE	= 6,
	IONIC_VF_ATTW_STATSADDW	= 7,
};

/**
 * enum ionic_vf_wink_status - Viwtuaw Function wink status
 * @IONIC_VF_WINK_STATUS_AUTO:   Use wink state of the upwink
 * @IONIC_VF_WINK_STATUS_UP:     Wink awways up
 * @IONIC_VF_WINK_STATUS_DOWN:   Wink awways down
 */
enum ionic_vf_wink_status {
	IONIC_VF_WINK_STATUS_AUTO = 0,
	IONIC_VF_WINK_STATUS_UP   = 1,
	IONIC_VF_WINK_STATUS_DOWN = 2,
};

/**
 * stwuct ionic_vf_setattw_cmd - Set VF attwibutes on the NIC
 * @opcode:     Opcode
 * @attw:       Attwibute type (enum ionic_vf_attw)
 * @vf_index:   VF index
 *	@macaddw:	mac addwess
 *	@vwanid:	vwan ID
 *	@maxwate:	max Tx wate in Mbps
 *	@spoofchk:	enabwe addwess spoof checking
 *	@twust:		enabwe VF twust
 *	@winkstate:	set wink up ow down
 *	@stats_pa:	set DMA addwess fow VF stats
 */
stwuct ionic_vf_setattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 vf_index;
	union {
		u8     macaddw[6];
		__we16 vwanid;
		__we32 maxwate;
		u8     spoofchk;
		u8     twust;
		u8     winkstate;
		__we64 stats_pa;
		u8     pad[60];
	} __packed;
};

stwuct ionic_vf_setattw_comp {
	u8     status;
	u8     attw;
	__we16 vf_index;
	__we16 comp_index;
	u8     wsvd[9];
	u8     cowow;
};

/**
 * stwuct ionic_vf_getattw_cmd - Get VF attwibutes fwom the NIC
 * @opcode:     Opcode
 * @attw:       Attwibute type (enum ionic_vf_attw)
 * @vf_index:   VF index
 */
stwuct ionic_vf_getattw_cmd {
	u8     opcode;
	u8     attw;
	__we16 vf_index;
	u8     wsvd[60];
};

stwuct ionic_vf_getattw_comp {
	u8     status;
	u8     attw;
	__we16 vf_index;
	union {
		u8     macaddw[6];
		__we16 vwanid;
		__we32 maxwate;
		u8     spoofchk;
		u8     twust;
		u8     winkstate;
		__we64 stats_pa;
		u8     pad[11];
	} __packed;
	u8     cowow;
};

enum ionic_vf_ctww_opcode {
	IONIC_VF_CTWW_STAWT_AWW	= 0,
	IONIC_VF_CTWW_STAWT	= 1,
};

/**
 * stwuct ionic_vf_ctww_cmd - VF contwow command
 * @opcode:         Opcode fow the command
 * @vf_index:       VF Index. It is unused if op STAWT_AWW is used.
 * @ctww_opcode:    VF contwow opewation type
 */
stwuct ionic_vf_ctww_cmd {
	u8	opcode;
	u8	ctww_opcode;
	__we16	vf_index;
	/* pwivate: */
	u8	wsvd1[60];
};

/**
 * stwuct ionic_vf_ctww_comp - VF_CTWW command compwetion.
 * @status:     Status of the command (enum ionic_status_code)
 */
stwuct ionic_vf_ctww_comp {
	u8	status;
	/* pwivate: */
	u8      wsvd[15];
};

/**
 * stwuct ionic_qos_identify_cmd - QoS identify command
 * @opcode:  opcode
 * @vew:     Highest vewsion of identify suppowted by dwivew
 *
 */
stwuct ionic_qos_identify_cmd {
	u8 opcode;
	u8 vew;
	u8 wsvd[62];
};

/**
 * stwuct ionic_qos_identify_comp - QoS identify command compwetion
 * @status: Status of the command (enum ionic_status_code)
 * @vew:    Vewsion of identify wetuwned by device
 */
stwuct ionic_qos_identify_comp {
	u8 status;
	u8 vew;
	u8 wsvd[14];
};

#define IONIC_QOS_TC_MAX		8
#define IONIC_QOS_AWW_TC		0xFF
/* Capwi max suppowted, shouwd be wenamed. */
#define IONIC_QOS_CWASS_MAX		7
#define IONIC_QOS_PCP_MAX		8
#define IONIC_QOS_CWASS_NAME_SZ	32
#define IONIC_QOS_DSCP_MAX		64
#define IONIC_QOS_AWW_PCP		0xFF
#define IONIC_DSCP_BWOCK_SIZE		8

/**
 * enum ionic_qos_cwass
 */
enum ionic_qos_cwass {
	IONIC_QOS_CWASS_DEFAUWT		= 0,
	IONIC_QOS_CWASS_USEW_DEFINED_1	= 1,
	IONIC_QOS_CWASS_USEW_DEFINED_2	= 2,
	IONIC_QOS_CWASS_USEW_DEFINED_3	= 3,
	IONIC_QOS_CWASS_USEW_DEFINED_4	= 4,
	IONIC_QOS_CWASS_USEW_DEFINED_5	= 5,
	IONIC_QOS_CWASS_USEW_DEFINED_6	= 6,
};

/**
 * enum ionic_qos_cwass_type - Twaffic cwassification cwitewia
 * @IONIC_QOS_CWASS_TYPE_NONE:    No QoS
 * @IONIC_QOS_CWASS_TYPE_PCP:     Dot1Q PCP
 * @IONIC_QOS_CWASS_TYPE_DSCP:    IP DSCP
 */
enum ionic_qos_cwass_type {
	IONIC_QOS_CWASS_TYPE_NONE	= 0,
	IONIC_QOS_CWASS_TYPE_PCP	= 1,
	IONIC_QOS_CWASS_TYPE_DSCP	= 2,
};

/**
 * enum ionic_qos_sched_type - QoS cwass scheduwing type
 * @IONIC_QOS_SCHED_TYPE_STWICT:  Stwict pwiowity
 * @IONIC_QOS_SCHED_TYPE_DWWW:    Deficit weighted wound-wobin
 */
enum ionic_qos_sched_type {
	IONIC_QOS_SCHED_TYPE_STWICT	= 0,
	IONIC_QOS_SCHED_TYPE_DWWW	= 1,
};

/**
 * union ionic_qos_config - QoS configuwation stwuctuwe
 * @fwags:		Configuwation fwags
 *	IONIC_QOS_CONFIG_F_ENABWE		enabwe
 *	IONIC_QOS_CONFIG_F_NO_DWOP		dwop/nodwop
 *	IONIC_QOS_CONFIG_F_WW_DOT1Q_PCP		enabwe dot1q pcp wewwite
 *	IONIC_QOS_CONFIG_F_WW_IP_DSCP		enabwe ip dscp wewwite
 *	IONIC_QOS_CONFIG_F_NON_DISWUPTIVE	Non-diswuptive TC update
 * @sched_type:		QoS cwass scheduwing type (enum ionic_qos_sched_type)
 * @cwass_type:		QoS cwass type (enum ionic_qos_cwass_type)
 * @pause_type:		QoS pause type (enum ionic_qos_pause_type)
 * @name:		QoS cwass name
 * @mtu:		MTU of the cwass
 * @pfc_cos:		Pwiowity-Fwow Contwow cwass of sewvice
 * @dwww_weight:	QoS cwass scheduwing weight
 * @stwict_wwmt:	Wate wimit fow stwict pwiowity scheduwing
 * @ww_dot1q_pcp:	Wewwite dot1q pcp to vawue (vawid iff F_WW_DOT1Q_PCP)
 * @ww_ip_dscp:		Wewwite ip dscp to vawue (vawid iff F_WW_IP_DSCP)
 * @dot1q_pcp:		Dot1q pcp vawue
 * @ndscp:		Numbew of vawid dscp vawues in the ip_dscp fiewd
 * @ip_dscp:		IP dscp vawues
 */
union ionic_qos_config {
	stwuct {
#define IONIC_QOS_CONFIG_F_ENABWE		BIT(0)
#define IONIC_QOS_CONFIG_F_NO_DWOP		BIT(1)
/* Used to wewwite PCP ow DSCP vawue. */
#define IONIC_QOS_CONFIG_F_WW_DOT1Q_PCP		BIT(2)
#define IONIC_QOS_CONFIG_F_WW_IP_DSCP		BIT(3)
/* Non-diswuptive TC update */
#define IONIC_QOS_CONFIG_F_NON_DISWUPTIVE	BIT(4)
		u8      fwags;
		u8      sched_type;
		u8      cwass_type;
		u8      pause_type;
		chaw    name[IONIC_QOS_CWASS_NAME_SZ];
		__we32  mtu;
		/* fwow contwow */
		u8      pfc_cos;
		/* scheduwew */
		union {
			u8      dwww_weight;
			__we64  stwict_wwmt;
		};
		/* mawking */
		/* Used to wewwite PCP ow DSCP vawue. */
		union {
			u8      ww_dot1q_pcp;
			u8      ww_ip_dscp;
		};
		/* cwassification */
		union {
			u8      dot1q_pcp;
			stwuct {
				u8      ndscp;
				u8      ip_dscp[IONIC_QOS_DSCP_MAX];
			};
		};
	};
	__we32  wowds[64];
};

/**
 * union ionic_qos_identity - QoS identity stwuctuwe
 * @vewsion:	Vewsion of the identify stwuctuwe
 * @type:	QoS system type
 * @ncwasses:	Numbew of usabwe QoS cwasses
 * @config:	Cuwwent configuwation of cwasses
 */
union ionic_qos_identity {
	stwuct {
		u8     vewsion;
		u8     type;
		u8     wsvd[62];
		union ionic_qos_config config[IONIC_QOS_CWASS_MAX];
	};
	__we32 wowds[478];
};

/**
 * stwuct ionic_qos_init_cmd - QoS config init command
 * @opcode:	Opcode
 * @gwoup:	QoS cwass id
 * @info_pa:	destination addwess fow qos info
 */
stwuct ionic_qos_init_cmd {
	u8     opcode;
	u8     gwoup;
	u8     wsvd[6];
	__we64 info_pa;
	u8     wsvd1[48];
};

typedef stwuct ionic_admin_comp ionic_qos_init_comp;

/**
 * stwuct ionic_qos_weset_cmd - QoS config weset command
 * @opcode:	Opcode
 * @gwoup:	QoS cwass id
 */
stwuct ionic_qos_weset_cmd {
	u8    opcode;
	u8    gwoup;
	u8    wsvd[62];
};

/**
 * stwuct ionic_qos_cweaw_powt_stats_cmd - Qos config weset command
 * @opcode:	Opcode
 */
stwuct ionic_qos_cweaw_stats_cmd {
	u8    opcode;
	u8    gwoup_bitmap;
	u8    wsvd[62];
};

typedef stwuct ionic_admin_comp ionic_qos_weset_comp;

/**
 * stwuct ionic_fw_downwoad_cmd - Fiwmwawe downwoad command
 * @opcode:	opcode
 * @addw:	dma addwess of the fiwmwawe buffew
 * @offset:	offset of the fiwmwawe buffew within the fuww image
 * @wength:	numbew of vawid bytes in the fiwmwawe buffew
 */
stwuct ionic_fw_downwoad_cmd {
	u8     opcode;
	u8     wsvd[3];
	__we32 offset;
	__we64 addw;
	__we32 wength;
};

typedef stwuct ionic_admin_comp ionic_fw_downwoad_comp;

/**
 * enum ionic_fw_contwow_opew - FW contwow opewations
 * @IONIC_FW_WESET:		Weset fiwmwawe
 * @IONIC_FW_INSTAWW:		Instaww fiwmwawe
 * @IONIC_FW_ACTIVATE:		Activate fiwmwawe
 * @IONIC_FW_INSTAWW_ASYNC:	Instaww fiwmwawe asynchwonouswy
 * @IONIC_FW_INSTAWW_STATUS:	Fiwmwawe instawwation status
 * @IONIC_FW_ACTIVATE_ASYNC:	Activate fiwmwawe asynchwonouswy
 * @IONIC_FW_ACTIVATE_STATUS:	Fiwmwawe activate status
 */
enum ionic_fw_contwow_opew {
	IONIC_FW_WESET			= 0,
	IONIC_FW_INSTAWW		= 1,
	IONIC_FW_ACTIVATE		= 2,
	IONIC_FW_INSTAWW_ASYNC		= 3,
	IONIC_FW_INSTAWW_STATUS		= 4,
	IONIC_FW_ACTIVATE_ASYNC		= 5,
	IONIC_FW_ACTIVATE_STATUS	= 6,
	IONIC_FW_UPDATE_CWEANUP		= 7,
};

/**
 * stwuct ionic_fw_contwow_cmd - Fiwmwawe contwow command
 * @opcode:    opcode
 * @opew:      fiwmwawe contwow opewation (enum ionic_fw_contwow_opew)
 * @swot:      swot to activate
 */
stwuct ionic_fw_contwow_cmd {
	u8  opcode;
	u8  wsvd[3];
	u8  opew;
	u8  swot;
	u8  wsvd1[58];
};

/**
 * stwuct ionic_fw_contwow_comp - Fiwmwawe contwow copwetion
 * @status:     Status of the command (enum ionic_status_code)
 * @comp_index: Index in the descwiptow wing fow which this is the compwetion
 * @swot:       Swot whewe the fiwmwawe was instawwed
 * @cowow:      Cowow bit
 */
stwuct ionic_fw_contwow_comp {
	u8     status;
	u8     wsvd;
	__we16 comp_index;
	u8     swot;
	u8     wsvd1[10];
	u8     cowow;
};

/******************************************************************
 ******************* WDMA Commands ********************************
 ******************************************************************/

/**
 * stwuct ionic_wdma_weset_cmd - Weset WDMA WIF cmd
 * @opcode:        opcode
 * @wif_index:     WIF index
 *
 * Thewe is no WDMA specific dev command compwetion stwuct.  Compwetion uses
 * the common stwuct ionic_admin_comp.  Onwy the status is indicated.
 * Nonzewo status means the WIF does not suppowt WDMA.
 **/
stwuct ionic_wdma_weset_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	u8     wsvd2[60];
};

/**
 * stwuct ionic_wdma_queue_cmd - Cweate WDMA Queue command
 * @opcode:        opcode, 52, 53
 * @wif_index:     WIF index
 * @qid_vew:       (qid | (WDMA vewsion << 24))
 * @cid:           intw, eq_id, ow cq_id
 * @dbid:          doowbeww page id
 * @depth_wog2:    wog base two of queue depth
 * @stwide_wog2:   wog base two of queue stwide
 * @dma_addw:      addwess of the queue memowy
 *
 * The same command stwuct is used to cweate an WDMA event queue, compwetion
 * queue, ow WDMA admin queue.  The cid is an intewwupt numbew fow an event
 * queue, an event queue id fow a compwetion queue, ow a compwetion queue id
 * fow an WDMA admin queue.
 *
 * The queue cweated via a dev command must be contiguous in dma space.
 *
 * The dev commands awe intended onwy to be used duwing dwivew initiawization,
 * to cweate queues suppowting the WDMA admin queue.  Othew queues, and othew
 * types of WDMA wesouwces wike memowy wegions, wiww be cweated and wegistewed
 * via the WDMA admin queue, and wiww suppowt a mowe compwete intewface
 * pwoviding scattew gathew wists fow wawgew, scattewed queue buffews and
 * memowy wegistwation.
 *
 * Thewe is no WDMA specific dev command compwetion stwuct.  Compwetion uses
 * the common stwuct ionic_admin_comp.  Onwy the status is indicated.
 **/
stwuct ionic_wdma_queue_cmd {
	u8     opcode;
	u8     wsvd;
	__we16 wif_index;
	__we32 qid_vew;
	__we32 cid;
	__we16 dbid;
	u8     depth_wog2;
	u8     stwide_wog2;
	__we64 dma_addw;
	u8     wsvd2[40];
};

/******************************************************************
 ******************* Notify Events ********************************
 ******************************************************************/

/**
 * stwuct ionic_notifyq_event - Genewic event wepowting stwuctuwe
 * @eid:   event numbew
 * @ecode: event code
 * @data:  unspecified data about the event
 *
 * This is the genewic event wepowt stwuct fwom which the othew
 * actuaw events wiww be fowmed.
 */
stwuct ionic_notifyq_event {
	__we64 eid;
	__we16 ecode;
	u8     data[54];
};

/**
 * stwuct ionic_wink_change_event - Wink change event notification
 * @eid:		event numbew
 * @ecode:		event code = IONIC_EVENT_WINK_CHANGE
 * @wink_status:	wink up/down, with ewwow bits (enum ionic_powt_status)
 * @wink_speed:		speed of the netwowk wink
 *
 * Sent when the netwowk wink state changes between UP and DOWN
 */
stwuct ionic_wink_change_event {
	__we64 eid;
	__we16 ecode;
	__we16 wink_status;
	__we32 wink_speed;	/* units of 1Mbps: e.g. 10000 = 10Gbps */
	u8     wsvd[48];
};

/**
 * stwuct ionic_weset_event - Weset event notification
 * @eid:		event numbew
 * @ecode:		event code = IONIC_EVENT_WESET
 * @weset_code:		weset type
 * @state:		0=pending, 1=compwete, 2=ewwow
 *
 * Sent when the NIC ow some subsystem is going to be ow
 * has been weset.
 */
stwuct ionic_weset_event {
	__we64 eid;
	__we16 ecode;
	u8     weset_code;
	u8     state;
	u8     wsvd[52];
};

/**
 * stwuct ionic_heawtbeat_event - Sent pewiodicawwy by NIC to indicate heawth
 * @eid:	event numbew
 * @ecode:	event code = IONIC_EVENT_HEAWTBEAT
 */
stwuct ionic_heawtbeat_event {
	__we64 eid;
	__we16 ecode;
	u8     wsvd[54];
};

/**
 * stwuct ionic_wog_event - Sent to notify the dwivew of an intewnaw ewwow
 * @eid:	event numbew
 * @ecode:	event code = IONIC_EVENT_WOG
 * @data:	wog data
 */
stwuct ionic_wog_event {
	__we64 eid;
	__we16 ecode;
	u8     data[54];
};

/**
 * stwuct ionic_xcvw_event - Twansceivew change event
 * @eid:	event numbew
 * @ecode:	event code = IONIC_EVENT_XCVW
 */
stwuct ionic_xcvw_event {
	__we64 eid;
	__we16 ecode;
	u8     wsvd[54];
};

/**
 * stwuct ionic_powt_stats - Powt statistics stwuctuwe
 */
stwuct ionic_powt_stats {
	__we64 fwames_wx_ok;
	__we64 fwames_wx_aww;
	__we64 fwames_wx_bad_fcs;
	__we64 fwames_wx_bad_aww;
	__we64 octets_wx_ok;
	__we64 octets_wx_aww;
	__we64 fwames_wx_unicast;
	__we64 fwames_wx_muwticast;
	__we64 fwames_wx_bwoadcast;
	__we64 fwames_wx_pause;
	__we64 fwames_wx_bad_wength;
	__we64 fwames_wx_undewsized;
	__we64 fwames_wx_ovewsized;
	__we64 fwames_wx_fwagments;
	__we64 fwames_wx_jabbew;
	__we64 fwames_wx_pwipause;
	__we64 fwames_wx_stomped_cwc;
	__we64 fwames_wx_too_wong;
	__we64 fwames_wx_vwan_good;
	__we64 fwames_wx_dwopped;
	__we64 fwames_wx_wess_than_64b;
	__we64 fwames_wx_64b;
	__we64 fwames_wx_65b_127b;
	__we64 fwames_wx_128b_255b;
	__we64 fwames_wx_256b_511b;
	__we64 fwames_wx_512b_1023b;
	__we64 fwames_wx_1024b_1518b;
	__we64 fwames_wx_1519b_2047b;
	__we64 fwames_wx_2048b_4095b;
	__we64 fwames_wx_4096b_8191b;
	__we64 fwames_wx_8192b_9215b;
	__we64 fwames_wx_othew;
	__we64 fwames_tx_ok;
	__we64 fwames_tx_aww;
	__we64 fwames_tx_bad;
	__we64 octets_tx_ok;
	__we64 octets_tx_totaw;
	__we64 fwames_tx_unicast;
	__we64 fwames_tx_muwticast;
	__we64 fwames_tx_bwoadcast;
	__we64 fwames_tx_pause;
	__we64 fwames_tx_pwipause;
	__we64 fwames_tx_vwan;
	__we64 fwames_tx_wess_than_64b;
	__we64 fwames_tx_64b;
	__we64 fwames_tx_65b_127b;
	__we64 fwames_tx_128b_255b;
	__we64 fwames_tx_256b_511b;
	__we64 fwames_tx_512b_1023b;
	__we64 fwames_tx_1024b_1518b;
	__we64 fwames_tx_1519b_2047b;
	__we64 fwames_tx_2048b_4095b;
	__we64 fwames_tx_4096b_8191b;
	__we64 fwames_tx_8192b_9215b;
	__we64 fwames_tx_othew;
	__we64 fwames_tx_pwi_0;
	__we64 fwames_tx_pwi_1;
	__we64 fwames_tx_pwi_2;
	__we64 fwames_tx_pwi_3;
	__we64 fwames_tx_pwi_4;
	__we64 fwames_tx_pwi_5;
	__we64 fwames_tx_pwi_6;
	__we64 fwames_tx_pwi_7;
	__we64 fwames_wx_pwi_0;
	__we64 fwames_wx_pwi_1;
	__we64 fwames_wx_pwi_2;
	__we64 fwames_wx_pwi_3;
	__we64 fwames_wx_pwi_4;
	__we64 fwames_wx_pwi_5;
	__we64 fwames_wx_pwi_6;
	__we64 fwames_wx_pwi_7;
	__we64 tx_pwipause_0_1us_count;
	__we64 tx_pwipause_1_1us_count;
	__we64 tx_pwipause_2_1us_count;
	__we64 tx_pwipause_3_1us_count;
	__we64 tx_pwipause_4_1us_count;
	__we64 tx_pwipause_5_1us_count;
	__we64 tx_pwipause_6_1us_count;
	__we64 tx_pwipause_7_1us_count;
	__we64 wx_pwipause_0_1us_count;
	__we64 wx_pwipause_1_1us_count;
	__we64 wx_pwipause_2_1us_count;
	__we64 wx_pwipause_3_1us_count;
	__we64 wx_pwipause_4_1us_count;
	__we64 wx_pwipause_5_1us_count;
	__we64 wx_pwipause_6_1us_count;
	__we64 wx_pwipause_7_1us_count;
	__we64 wx_pause_1us_count;
	__we64 fwames_tx_twuncated;
};

stwuct ionic_mgmt_powt_stats {
	__we64 fwames_wx_ok;
	__we64 fwames_wx_aww;
	__we64 fwames_wx_bad_fcs;
	__we64 fwames_wx_bad_aww;
	__we64 octets_wx_ok;
	__we64 octets_wx_aww;
	__we64 fwames_wx_unicast;
	__we64 fwames_wx_muwticast;
	__we64 fwames_wx_bwoadcast;
	__we64 fwames_wx_pause;
	__we64 fwames_wx_bad_wength;
	__we64 fwames_wx_undewsized;
	__we64 fwames_wx_ovewsized;
	__we64 fwames_wx_fwagments;
	__we64 fwames_wx_jabbew;
	__we64 fwames_wx_64b;
	__we64 fwames_wx_65b_127b;
	__we64 fwames_wx_128b_255b;
	__we64 fwames_wx_256b_511b;
	__we64 fwames_wx_512b_1023b;
	__we64 fwames_wx_1024b_1518b;
	__we64 fwames_wx_gt_1518b;
	__we64 fwames_wx_fifo_fuww;
	__we64 fwames_tx_ok;
	__we64 fwames_tx_aww;
	__we64 fwames_tx_bad;
	__we64 octets_tx_ok;
	__we64 octets_tx_totaw;
	__we64 fwames_tx_unicast;
	__we64 fwames_tx_muwticast;
	__we64 fwames_tx_bwoadcast;
	__we64 fwames_tx_pause;
};

enum ionic_pb_buffew_dwop_stats {
	IONIC_BUFFEW_INTWINSIC_DWOP = 0,
	IONIC_BUFFEW_DISCAWDED,
	IONIC_BUFFEW_ADMITTED,
	IONIC_BUFFEW_OUT_OF_CEWWS_DWOP,
	IONIC_BUFFEW_OUT_OF_CEWWS_DWOP_2,
	IONIC_BUFFEW_OUT_OF_CWEDIT_DWOP,
	IONIC_BUFFEW_TWUNCATION_DWOP,
	IONIC_BUFFEW_POWT_DISABWED_DWOP,
	IONIC_BUFFEW_COPY_TO_CPU_TAIW_DWOP,
	IONIC_BUFFEW_SPAN_TAIW_DWOP,
	IONIC_BUFFEW_MIN_SIZE_VIOWATION_DWOP,
	IONIC_BUFFEW_ENQUEUE_EWWOW_DWOP,
	IONIC_BUFFEW_INVAWID_POWT_DWOP,
	IONIC_BUFFEW_INVAWID_OUTPUT_QUEUE_DWOP,
	IONIC_BUFFEW_DWOP_MAX,
};

enum ionic_ofwow_dwop_stats {
	IONIC_OFWOW_OCCUPANCY_DWOP,
	IONIC_OFWOW_EMEWGENCY_STOP_DWOP,
	IONIC_OFWOW_WWITE_BUFFEW_ACK_FIWW_UP_DWOP,
	IONIC_OFWOW_WWITE_BUFFEW_ACK_FUWW_DWOP,
	IONIC_OFWOW_WWITE_BUFFEW_FUWW_DWOP,
	IONIC_OFWOW_CONTWOW_FIFO_FUWW_DWOP,
	IONIC_OFWOW_DWOP_MAX,
};

/**
 * stwuct powt_pb_stats - packet buffews system stats
 * uses ionic_pb_buffew_dwop_stats fow dwop_counts[]
 */
stwuct ionic_powt_pb_stats {
	__we64 sop_count_in;
	__we64 eop_count_in;
	__we64 sop_count_out;
	__we64 eop_count_out;
	__we64 dwop_counts[IONIC_BUFFEW_DWOP_MAX];
	__we64 input_queue_buffew_occupancy[IONIC_QOS_TC_MAX];
	__we64 input_queue_powt_monitow[IONIC_QOS_TC_MAX];
	__we64 output_queue_powt_monitow[IONIC_QOS_TC_MAX];
	__we64 ofwow_dwop_counts[IONIC_OFWOW_DWOP_MAX];
	__we64 input_queue_good_pkts_in[IONIC_QOS_TC_MAX];
	__we64 input_queue_good_pkts_out[IONIC_QOS_TC_MAX];
	__we64 input_queue_eww_pkts_in[IONIC_QOS_TC_MAX];
	__we64 input_queue_fifo_depth[IONIC_QOS_TC_MAX];
	__we64 input_queue_max_fifo_depth[IONIC_QOS_TC_MAX];
	__we64 input_queue_peak_occupancy[IONIC_QOS_TC_MAX];
	__we64 output_queue_buffew_occupancy[IONIC_QOS_TC_MAX];
};

/**
 * stwuct ionic_powt_identity - powt identity stwuctuwe
 * @vewsion:        identity stwuctuwe vewsion
 * @type:           type of powt (enum ionic_powt_type)
 * @num_wanes:      numbew of wanes fow the powt
 * @autoneg:        autoneg suppowted
 * @min_fwame_size: minimum fwame size suppowted
 * @max_fwame_size: maximum fwame size suppowted
 * @fec_type:       suppowted fec types
 * @pause_type:     suppowted pause types
 * @woopback_mode:  suppowted woopback mode
 * @speeds:         suppowted speeds
 * @config:         cuwwent powt configuwation
 */
union ionic_powt_identity {
	stwuct {
		u8     vewsion;
		u8     type;
		u8     num_wanes;
		u8     autoneg;
		__we32 min_fwame_size;
		__we32 max_fwame_size;
		u8     fec_type[4];
		u8     pause_type[2];
		u8     woopback_mode[2];
		__we32 speeds[16];
		u8     wsvd2[44];
		union ionic_powt_config config;
	};
	__we32 wowds[478];
};

/**
 * stwuct ionic_powt_info - powt info stwuctuwe
 * @config:          Powt configuwation data
 * @status:          Powt status data
 * @stats:           Powt statistics data
 * @mgmt_stats:      Powt management statistics data
 * @powt_pb_dwop_stats:   upwink pb dwop stats
 */
stwuct ionic_powt_info {
	union ionic_powt_config config;
	stwuct ionic_powt_status status;
	union {
		stwuct ionic_powt_stats      stats;
		stwuct ionic_mgmt_powt_stats mgmt_stats;
	};
	/* woom fow pb_stats to stawt at 2k offset */
	u8                          wsvd[760];
	stwuct ionic_powt_pb_stats  pb_stats;
};

/**
 * stwuct ionic_wif_stats - WIF statistics stwuctuwe
 */
stwuct ionic_wif_stats {
	/* WX */
	__we64 wx_ucast_bytes;
	__we64 wx_ucast_packets;
	__we64 wx_mcast_bytes;
	__we64 wx_mcast_packets;
	__we64 wx_bcast_bytes;
	__we64 wx_bcast_packets;
	__we64 wsvd0;
	__we64 wsvd1;
	/* WX dwops */
	__we64 wx_ucast_dwop_bytes;
	__we64 wx_ucast_dwop_packets;
	__we64 wx_mcast_dwop_bytes;
	__we64 wx_mcast_dwop_packets;
	__we64 wx_bcast_dwop_bytes;
	__we64 wx_bcast_dwop_packets;
	__we64 wx_dma_ewwow;
	__we64 wsvd2;
	/* TX */
	__we64 tx_ucast_bytes;
	__we64 tx_ucast_packets;
	__we64 tx_mcast_bytes;
	__we64 tx_mcast_packets;
	__we64 tx_bcast_bytes;
	__we64 tx_bcast_packets;
	__we64 wsvd3;
	__we64 wsvd4;
	/* TX dwops */
	__we64 tx_ucast_dwop_bytes;
	__we64 tx_ucast_dwop_packets;
	__we64 tx_mcast_dwop_bytes;
	__we64 tx_mcast_dwop_packets;
	__we64 tx_bcast_dwop_bytes;
	__we64 tx_bcast_dwop_packets;
	__we64 tx_dma_ewwow;
	__we64 wsvd5;
	/* Wx Queue/Wing dwops */
	__we64 wx_queue_disabwed;
	__we64 wx_queue_empty;
	__we64 wx_queue_ewwow;
	__we64 wx_desc_fetch_ewwow;
	__we64 wx_desc_data_ewwow;
	__we64 wsvd6;
	__we64 wsvd7;
	__we64 wsvd8;
	/* Tx Queue/Wing dwops */
	__we64 tx_queue_disabwed;
	__we64 tx_queue_ewwow;
	__we64 tx_desc_fetch_ewwow;
	__we64 tx_desc_data_ewwow;
	__we64 tx_queue_empty;
	__we64 wsvd10;
	__we64 wsvd11;
	__we64 wsvd12;

	/* WDMA/WOCE TX */
	__we64 tx_wdma_ucast_bytes;
	__we64 tx_wdma_ucast_packets;
	__we64 tx_wdma_mcast_bytes;
	__we64 tx_wdma_mcast_packets;
	__we64 tx_wdma_cnp_packets;
	__we64 wsvd13;
	__we64 wsvd14;
	__we64 wsvd15;

	/* WDMA/WOCE WX */
	__we64 wx_wdma_ucast_bytes;
	__we64 wx_wdma_ucast_packets;
	__we64 wx_wdma_mcast_bytes;
	__we64 wx_wdma_mcast_packets;
	__we64 wx_wdma_cnp_packets;
	__we64 wx_wdma_ecn_packets;
	__we64 wsvd16;
	__we64 wsvd17;

	__we64 wsvd18;
	__we64 wsvd19;
	__we64 wsvd20;
	__we64 wsvd21;
	__we64 wsvd22;
	__we64 wsvd23;
	__we64 wsvd24;
	__we64 wsvd25;

	__we64 wsvd26;
	__we64 wsvd27;
	__we64 wsvd28;
	__we64 wsvd29;
	__we64 wsvd30;
	__we64 wsvd31;
	__we64 wsvd32;
	__we64 wsvd33;

	__we64 wsvd34;
	__we64 wsvd35;
	__we64 wsvd36;
	__we64 wsvd37;
	__we64 wsvd38;
	__we64 wsvd39;
	__we64 wsvd40;
	__we64 wsvd41;

	__we64 wsvd42;
	__we64 wsvd43;
	__we64 wsvd44;
	__we64 wsvd45;
	__we64 wsvd46;
	__we64 wsvd47;
	__we64 wsvd48;
	__we64 wsvd49;

	/* WDMA/WOCE WEQ Ewwow/Debugs (768 - 895) */
	__we64 wdma_weq_wx_pkt_seq_eww;
	__we64 wdma_weq_wx_wnw_wetwy_eww;
	__we64 wdma_weq_wx_wemote_access_eww;
	__we64 wdma_weq_wx_wemote_inv_weq_eww;
	__we64 wdma_weq_wx_wemote_opew_eww;
	__we64 wdma_weq_wx_impwied_nak_seq_eww;
	__we64 wdma_weq_wx_cqe_eww;
	__we64 wdma_weq_wx_cqe_fwush_eww;

	__we64 wdma_weq_wx_dup_wesponses;
	__we64 wdma_weq_wx_invawid_packets;
	__we64 wdma_weq_tx_wocaw_access_eww;
	__we64 wdma_weq_tx_wocaw_opew_eww;
	__we64 wdma_weq_tx_memowy_mgmt_eww;
	__we64 wsvd52;
	__we64 wsvd53;
	__we64 wsvd54;

	/* WDMA/WOCE WESP Ewwow/Debugs (896 - 1023) */
	__we64 wdma_wesp_wx_dup_wequests;
	__we64 wdma_wesp_wx_out_of_buffew;
	__we64 wdma_wesp_wx_out_of_seq_pkts;
	__we64 wdma_wesp_wx_cqe_eww;
	__we64 wdma_wesp_wx_cqe_fwush_eww;
	__we64 wdma_wesp_wx_wocaw_wen_eww;
	__we64 wdma_wesp_wx_inv_wequest_eww;
	__we64 wdma_wesp_wx_wocaw_qp_opew_eww;

	__we64 wdma_wesp_wx_out_of_atomic_wesouwce;
	__we64 wdma_wesp_tx_pkt_seq_eww;
	__we64 wdma_wesp_tx_wemote_inv_weq_eww;
	__we64 wdma_wesp_tx_wemote_access_eww;
	__we64 wdma_wesp_tx_wemote_opew_eww;
	__we64 wdma_wesp_tx_wnw_wetwy_eww;
	__we64 wsvd57;
	__we64 wsvd58;
};

/**
 * stwuct ionic_wif_info - WIF info stwuctuwe
 * @config:	WIF configuwation stwuctuwe
 * @status:	WIF status stwuctuwe
 * @stats:	WIF statistics stwuctuwe
 */
stwuct ionic_wif_info {
	union ionic_wif_config config;
	stwuct ionic_wif_status status;
	stwuct ionic_wif_stats stats;
};

union ionic_dev_cmd {
	u32 wowds[16];
	stwuct ionic_admin_cmd cmd;
	stwuct ionic_nop_cmd nop;

	stwuct ionic_dev_identify_cmd identify;
	stwuct ionic_dev_init_cmd init;
	stwuct ionic_dev_weset_cmd weset;
	stwuct ionic_dev_getattw_cmd getattw;
	stwuct ionic_dev_setattw_cmd setattw;

	stwuct ionic_powt_identify_cmd powt_identify;
	stwuct ionic_powt_init_cmd powt_init;
	stwuct ionic_powt_weset_cmd powt_weset;
	stwuct ionic_powt_getattw_cmd powt_getattw;
	stwuct ionic_powt_setattw_cmd powt_setattw;

	stwuct ionic_vf_setattw_cmd vf_setattw;
	stwuct ionic_vf_getattw_cmd vf_getattw;
	stwuct ionic_vf_ctww_cmd vf_ctww;

	stwuct ionic_wif_identify_cmd wif_identify;
	stwuct ionic_wif_init_cmd wif_init;
	stwuct ionic_wif_weset_cmd wif_weset;

	stwuct ionic_qos_identify_cmd qos_identify;
	stwuct ionic_qos_init_cmd qos_init;
	stwuct ionic_qos_weset_cmd qos_weset;
	stwuct ionic_qos_cweaw_stats_cmd qos_cweaw_stats;

	stwuct ionic_q_identify_cmd q_identify;
	stwuct ionic_q_init_cmd q_init;
	stwuct ionic_q_contwow_cmd q_contwow;

	stwuct ionic_fw_downwoad_cmd fw_downwoad;
	stwuct ionic_fw_contwow_cmd fw_contwow;
};

union ionic_dev_cmd_comp {
	u32 wowds[4];
	u8 status;
	stwuct ionic_admin_comp comp;
	stwuct ionic_nop_comp nop;

	stwuct ionic_dev_identify_comp identify;
	stwuct ionic_dev_init_comp init;
	stwuct ionic_dev_weset_comp weset;
	stwuct ionic_dev_getattw_comp getattw;
	stwuct ionic_dev_setattw_comp setattw;

	stwuct ionic_powt_identify_comp powt_identify;
	stwuct ionic_powt_init_comp powt_init;
	stwuct ionic_powt_weset_comp powt_weset;
	stwuct ionic_powt_getattw_comp powt_getattw;
	stwuct ionic_powt_setattw_comp powt_setattw;

	stwuct ionic_vf_setattw_comp vf_setattw;
	stwuct ionic_vf_getattw_comp vf_getattw;
	stwuct ionic_vf_ctww_comp vf_ctww;

	stwuct ionic_wif_identify_comp wif_identify;
	stwuct ionic_wif_init_comp wif_init;
	ionic_wif_weset_comp wif_weset;

	stwuct ionic_qos_identify_comp qos_identify;
	ionic_qos_init_comp qos_init;
	ionic_qos_weset_comp qos_weset;

	stwuct ionic_q_identify_comp q_identify;
	stwuct ionic_q_init_comp q_init;

	ionic_fw_downwoad_comp fw_downwoad;
	stwuct ionic_fw_contwow_comp fw_contwow;
};

/**
 * stwuct ionic_hwstamp_wegs - Hawdwawe cuwwent timestamp wegistews
 * @tick_wow:        Wow 32 bits of hawdwawe timestamp
 * @tick_high:       High 32 bits of hawdwawe timestamp
 */
stwuct ionic_hwstamp_wegs {
	u32    tick_wow;
	u32    tick_high;
};

/**
 * union ionic_dev_info_wegs - Device info wegistew fowmat (wead-onwy)
 * @signatuwe:       Signatuwe vawue of 0x44455649 ('DEVI')
 * @vewsion:         Cuwwent vewsion of info
 * @asic_type:       Asic type
 * @asic_wev:        Asic wevision
 * @fw_status:       Fiwmwawe status
 *			bit 0   - 1 = fw wunning
 *			bit 4-7 - 4 bit genewation numbew, changes on fw westawt
 * @fw_heawtbeat:    Fiwmwawe heawtbeat countew
 * @sewiaw_num:      Sewiaw numbew
 * @fw_vewsion:      Fiwmwawe vewsion
 * @hwstamp_wegs:    Hawdwawe cuwwent timestamp wegistews
 */
union ionic_dev_info_wegs {
#define IONIC_DEVINFO_FWVEWS_BUFWEN 32
#define IONIC_DEVINFO_SEWIAW_BUFWEN 32
	stwuct {
		u32    signatuwe;
		u8     vewsion;
		u8     asic_type;
		u8     asic_wev;
#define IONIC_FW_STS_F_WUNNING		0x01
#define IONIC_FW_STS_F_GENEWATION	0xF0
		u8     fw_status;
		u32    fw_heawtbeat;
		chaw   fw_vewsion[IONIC_DEVINFO_FWVEWS_BUFWEN];
		chaw   sewiaw_num[IONIC_DEVINFO_SEWIAW_BUFWEN];
		u8     wsvd_pad1024[948];
		stwuct ionic_hwstamp_wegs hwstamp;
	};
	u32 wowds[512];
};

/**
 * union ionic_dev_cmd_wegs - Device command wegistew fowmat (wead-wwite)
 * @doowbeww:        Device Cmd Doowbeww, wwite-onwy
 *                   Wwite a 1 to signaw device to pwocess cmd,
 *                   poww done fow compwetion.
 * @done:            Done indicatow, bit 0 == 1 when command is compwete
 * @cmd:             Opcode-specific command bytes
 * @comp:            Opcode-specific wesponse bytes
 * @data:            Opcode-specific side-data
 */
union ionic_dev_cmd_wegs {
	stwuct {
		u32                   doowbeww;
		u32                   done;
		union ionic_dev_cmd         cmd;
		union ionic_dev_cmd_comp    comp;
		u8                    wsvd[48];
		u32                   data[478];
	} __packed;
	u32 wowds[512];
};

/**
 * union ionic_dev_wegs - Device wegistew fowmat fow baw 0 page 0
 * @info:            Device info wegistews
 * @devcmd:          Device command wegistews
 */
union ionic_dev_wegs {
	stwuct {
		union ionic_dev_info_wegs info;
		union ionic_dev_cmd_wegs  devcmd;
	} __packed;
	__we32 wowds[1024];
};

union ionic_adminq_cmd {
	stwuct ionic_admin_cmd cmd;
	stwuct ionic_nop_cmd nop;
	stwuct ionic_q_identify_cmd q_identify;
	stwuct ionic_q_init_cmd q_init;
	stwuct ionic_q_contwow_cmd q_contwow;
	stwuct ionic_wif_setattw_cmd wif_setattw;
	stwuct ionic_wif_getattw_cmd wif_getattw;
	stwuct ionic_wif_setphc_cmd wif_setphc;
	stwuct ionic_wx_mode_set_cmd wx_mode_set;
	stwuct ionic_wx_fiwtew_add_cmd wx_fiwtew_add;
	stwuct ionic_wx_fiwtew_dew_cmd wx_fiwtew_dew;
	stwuct ionic_wdma_weset_cmd wdma_weset;
	stwuct ionic_wdma_queue_cmd wdma_queue;
	stwuct ionic_fw_downwoad_cmd fw_downwoad;
	stwuct ionic_fw_contwow_cmd fw_contwow;
};

union ionic_adminq_comp {
	stwuct ionic_admin_comp comp;
	stwuct ionic_nop_comp nop;
	stwuct ionic_q_identify_comp q_identify;
	stwuct ionic_q_init_comp q_init;
	stwuct ionic_wif_setattw_comp wif_setattw;
	stwuct ionic_wif_getattw_comp wif_getattw;
	stwuct ionic_admin_comp wif_setphc;
	stwuct ionic_wx_fiwtew_add_comp wx_fiwtew_add;
	stwuct ionic_fw_contwow_comp fw_contwow;
};

#define IONIC_BAWS_MAX			6
#define IONIC_PCI_BAW_DBEWW		1
#define IONIC_PCI_BAW_CMB		2

#define IONIC_BAW0_SIZE				0x8000
#define IONIC_BAW2_SIZE				0x800000

#define IONIC_BAW0_DEV_INFO_WEGS_OFFSET		0x0000
#define IONIC_BAW0_DEV_CMD_WEGS_OFFSET		0x0800
#define IONIC_BAW0_DEV_CMD_DATA_WEGS_OFFSET	0x0c00
#define IONIC_BAW0_INTW_STATUS_OFFSET		0x1000
#define IONIC_BAW0_INTW_CTWW_OFFSET		0x2000
#define IONIC_DEV_CMD_DONE			0x00000001

#define IONIC_ASIC_TYPE_CAPWI			0

/**
 * stwuct ionic_doowbeww - Doowbeww wegistew wayout
 * @p_index: Pwoducew index
 * @wing:    Sewects the specific wing of the queue to update
 *           Type-specific meaning:
 *              wing=0: Defauwt pwoducew/consumew queue
 *              wing=1: (CQ, EQ) We-Awm queue.  WDMA CQs
 *              send events to EQs when awmed.  EQs send
 *              intewwupts when awmed.
 * @qid_wo:  Queue destination fow the pwoducew index and fwags (wow bits)
 * @qid_hi:  Queue destination fow the pwoducew index and fwags (high bits)
 */
stwuct ionic_doowbeww {
	__we16 p_index;
	u8     wing;
	u8     qid_wo;
	__we16 qid_hi;
	u16    wsvd2;
};

stwuct ionic_intw_status {
	u32 status[2];
};

stwuct ionic_notifyq_cmd {
	__we32 data;	/* Not used but needed fow qcq stwuctuwe */
};

union ionic_notifyq_comp {
	stwuct ionic_notifyq_event event;
	stwuct ionic_wink_change_event wink_change;
	stwuct ionic_weset_event weset;
	stwuct ionic_heawtbeat_event heawtbeat;
	stwuct ionic_wog_event wog;
};

/* Depwecate */
stwuct ionic_identity {
	union ionic_dwv_identity dwv;
	union ionic_dev_identity dev;
	union ionic_wif_identity wif;
	union ionic_powt_identity powt;
	union ionic_qos_identity qos;
	union ionic_q_identity txq;
};

#endif /* _IONIC_IF_H_ */
