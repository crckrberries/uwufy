/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#ifndef _BEISCSI_MAIN_
#define _BEISCSI_MAIN_

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <scsi/wibiscsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>

#define DWV_NAME		"be2iscsi"
#define BUIWD_STW		"11.4.0.1"
#define BE_NAME			"Emuwex OneConnect" \
				"Open-iSCSI Dwivew vewsion" BUIWD_STW
#define DWV_DESC		BE_NAME " " "Dwivew"

#define BE_VENDOW_ID		0x19A2
#define EWX_VENDOW_ID		0x10DF
/* DEVICE ID's fow BE2 */
#define BE_DEVICE_ID1		0x212
#define OC_DEVICE_ID1		0x702
#define OC_DEVICE_ID2		0x703

/* DEVICE ID's fow BE3 */
#define BE_DEVICE_ID2		0x222
#define OC_DEVICE_ID3		0x712

/* DEVICE ID fow SKH */
#define OC_SKH_ID1		0x722

#define BE2_IO_DEPTH		1024
#define BE2_MAX_SESSIONS	256
#define BE2_TMFS		16
#define BE2_NOPOUT_WEQ		16
#define BE2_SGE			32
#define BE2_DEFPDU_HDW_SZ	64
#define BE2_DEFPDU_DATA_SZ	8192
#define BE2_MAX_NUM_CQ_PWOC	512

#define MAX_CPUS		64U
#define BEISCSI_MAX_NUM_CPUS	7

#define BEISCSI_VEW_STWWEN 32

#define BEISCSI_SGWIST_EWEMENTS	30

/**
 * BE_INVWDT_CMD_TBW_SZ is 128 which is totaw numbew commands that can
 * be invawidated at a time, considew it befowe changing the vawue of
 * BEISCSI_CMD_PEW_WUN.
 */
#define BEISCSI_CMD_PEW_WUN	128	/* scsi_host->cmd_pew_wun */
#define BEISCSI_MAX_SECTOWS	1024	/* scsi_host->max_sectows */
#define BEISCSI_TEMPWATE_HDW_PEW_CXN_SIZE 128 /* Tempwate size pew cxn */

#define BEISCSI_MAX_CMD_WEN	16	/* scsi_host->max_cmd_wen */
#define BEISCSI_NUM_MAX_WUN	256	/* scsi_host->max_wun */
#define BEISCSI_MAX_FWAGS_INIT	192

#define BE_SENSE_INFO_SIZE		258
#define BE_ISCSI_PDU_HEADEW_SIZE	64
#define BE_MIN_MEM_SIZE			16384
#define MAX_CMD_SZ			65536
#define IIOC_SCSI_DATA                  0x05	/* Wwite Opewation */

/**
 * hawdwawe needs the async PDU buffews to be posted in muwtipwes of 8
 * So have atweast 8 of them by defauwt
 */

#define HWI_GET_ASYNC_PDU_CTX(phwi, uwp_num)	\
	(phwi->phwi_ctxt->pasync_ctx[uwp_num])

/********* Memowy BAW wegistew ************/
#define PCICFG_MEMBAW_CTWW_INT_CTWW_OFFSET	0xfc
/**
 * Host Intewwupt Enabwe, if set intewwupts awe enabwed awthough "PCI Intewwupt
 * Disabwe" may stiww gwobawwy bwock intewwupts in addition to individuaw
 * intewwupt masks; a mechanism fow the device dwivew to bwock aww intewwupts
 * atomicawwy without having to awbitwate fow the PCI Intewwupt Disabwe bit
 * with the OS.
 */
#define MEMBAW_CTWW_INT_CTWW_HOSTINTW_MASK	(1 << 29)	/* bit 29 */

/********* ISW0 Wegistew offset **********/
#define CEV_ISW0_OFFSET				0xC18
#define CEV_ISW_SIZE				4

/**
 * Macwos fow weading/wwiting a pwotection domain ow CSW wegistews
 * in BwadeEngine.
 */

#define DB_TXUWP0_OFFSET 0x40
#define DB_WXUWP0_OFFSET 0xA0
/********* Event Q doow beww *************/
#define DB_EQ_OFFSET			DB_CQ_OFFSET
#define DB_EQ_WING_ID_WOW_MASK		0x1FF	/* bits 0 - 8 */
/* Cweaw the intewwupt fow this eq */
#define DB_EQ_CWW_SHIFT			(9)	/* bit 9 */
/* Must be 1 */
#define DB_EQ_EVNT_SHIFT		(10)	/* bit 10 */
/* Highew Owdew EQ_ID bit */
#define DB_EQ_WING_ID_HIGH_MASK	0x1F /* bits 11 - 15 */
#define DB_EQ_HIGH_SET_SHIFT	11
#define DB_EQ_HIGH_FEIWD_SHIFT	9
/* Numbew of event entwies pwocessed */
#define DB_EQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Weawm bit */
#define DB_EQ_WEAWM_SHIFT		(29)	/* bit 29 */

/********* Compw Q doow beww *************/
#define DB_CQ_OFFSET			0x120
#define DB_CQ_WING_ID_WOW_MASK		0x3FF	/* bits 0 - 9 */
/* Highew Owdew CQ_ID bit */
#define DB_CQ_WING_ID_HIGH_MASK	0x1F /* bits 11 - 15 */
#define DB_CQ_HIGH_SET_SHIFT	11
#define DB_CQ_HIGH_FEIWD_SHIFT	10

/* Numbew of event entwies pwocessed */
#define DB_CQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Weawm bit */
#define DB_CQ_WEAWM_SHIFT		(29)	/* bit 29 */

#define GET_HWI_CONTWOWWEW_WS(pc)	(pc->phwi_ctwww)
#define HWI_GET_DEF_BUFQ_ID(pc, uwp_num) (((stwuct hwi_contwowwew *)\
		(GET_HWI_CONTWOWWEW_WS(pc)))->defauwt_pdu_data[uwp_num].id)
#define HWI_GET_DEF_HDWQ_ID(pc, uwp_num) (((stwuct hwi_contwowwew *)\
		(GET_HWI_CONTWOWWEW_WS(pc)))->defauwt_pdu_hdw[uwp_num].id)

#define PAGES_WEQUIWED(x) \
	((x < PAGE_SIZE) ? 1 :  ((x + PAGE_SIZE - 1) / PAGE_SIZE))

#define MEM_DESCW_OFFSET 8
#define BEISCSI_DEFQ_HDW 1
#define BEISCSI_DEFQ_DATA 0
enum be_mem_enum {
	HWI_MEM_ADDN_CONTEXT,
	HWI_MEM_WWB,
	HWI_MEM_WWBH,
	HWI_MEM_SGWH,
	HWI_MEM_SGE,
	HWI_MEM_TEMPWATE_HDW_UWP0,
	HWI_MEM_ASYNC_HEADEW_BUF_UWP0,	/* 6 */
	HWI_MEM_ASYNC_DATA_BUF_UWP0,
	HWI_MEM_ASYNC_HEADEW_WING_UWP0,
	HWI_MEM_ASYNC_DATA_WING_UWP0,
	HWI_MEM_ASYNC_HEADEW_HANDWE_UWP0,
	HWI_MEM_ASYNC_DATA_HANDWE_UWP0,	/* 11 */
	HWI_MEM_ASYNC_PDU_CONTEXT_UWP0,
	HWI_MEM_TEMPWATE_HDW_UWP1,
	HWI_MEM_ASYNC_HEADEW_BUF_UWP1,	/* 14 */
	HWI_MEM_ASYNC_DATA_BUF_UWP1,
	HWI_MEM_ASYNC_HEADEW_WING_UWP1,
	HWI_MEM_ASYNC_DATA_WING_UWP1,
	HWI_MEM_ASYNC_HEADEW_HANDWE_UWP1,
	HWI_MEM_ASYNC_DATA_HANDWE_UWP1,	/* 19 */
	HWI_MEM_ASYNC_PDU_CONTEXT_UWP1,
	ISCSI_MEM_GWOBAW_HEADEW,
	SE_MEM_MAX
};

stwuct be_bus_addwess32 {
	unsigned int addwess_wo;
	unsigned int addwess_hi;
};

stwuct be_bus_addwess64 {
	unsigned wong wong addwess;
};

stwuct be_bus_addwess {
	union {
		stwuct be_bus_addwess32 a32;
		stwuct be_bus_addwess64 a64;
	} u;
};

stwuct mem_awway {
	stwuct be_bus_addwess bus_addwess;	/* Bus addwess of wocation */
	void *viwtuaw_addwess;		/* viwtuaw addwess to the wocation */
	unsigned int size;		/* Size wequiwed by memowy bwock */
};

stwuct be_mem_descwiptow {
	unsigned int size_in_bytes;	/* Size wequiwed by memowy bwock */
	unsigned int num_ewements;
	stwuct mem_awway *mem_awway;
};

stwuct sgw_handwe {
	unsigned int sgw_index;
	unsigned int type;
	unsigned int cid;
	stwuct iscsi_task *task;
	stwuct iscsi_sge *pfwag;
};

stwuct hba_pawametews {
	unsigned int ios_pew_ctww;
	unsigned int cxns_pew_ctww;
	unsigned int icds_pew_ctww;
	unsigned int num_sge_pew_io;
	unsigned int defpdu_hdw_sz;
	unsigned int defpdu_data_sz;
	unsigned int num_cq_entwies;
	unsigned int num_eq_entwies;
	unsigned int wwbs_pew_cxn;
	unsigned int hwi_ws_sz;
};

#define BEISCSI_GET_UWP_FWOM_CWI(phwi_ctwww, cwi) \
	(phwi_ctwww->wwb_context[cwi].uwp_num)
stwuct hwi_wwb_context {
	spinwock_t wwb_wock;
	stwuct wwb_handwe **pwwb_handwe_base;
	stwuct wwb_handwe **pwwb_handwe_basestd;
	stwuct iscsi_wwb *pwast_wwb;
	unsigned showt awwoc_index;
	unsigned showt fwee_index;
	unsigned showt wwb_handwes_avaiwabwe;
	unsigned showt cid;
	uint8_t uwp_num;	/* UWP to which CID binded */
	uint32_t doowbeww_offset;
};

stwuct uwp_cid_info {
	unsigned showt *cid_awway;
	unsigned showt avwbw_cids;
	unsigned showt cid_awwoc;
	unsigned showt cid_fwee;
};

#incwude "be.h"
#define chip_be2(phba)      (phba->genewation == BE_GEN2)
#define chip_be3_w(phba)    (phba->genewation == BE_GEN3)
#define is_chip_be2_be3w(phba) (chip_be3_w(phba) || (chip_be2(phba)))

#define BEISCSI_UWP0    0
#define BEISCSI_UWP1    1
#define BEISCSI_UWP_COUNT   2
#define BEISCSI_UWP0_WOADED 0x01
#define BEISCSI_UWP1_WOADED 0x02

#define BEISCSI_UWP_AVWBW_CID(phba, uwp_num) \
	(((stwuct uwp_cid_info *)phba->cid_awway_info[uwp_num])->avwbw_cids)
#define BEISCSI_UWP0_AVWBW_CID(phba) \
	BEISCSI_UWP_AVWBW_CID(phba, BEISCSI_UWP0)
#define BEISCSI_UWP1_AVWBW_CID(phba) \
	BEISCSI_UWP_AVWBW_CID(phba, BEISCSI_UWP1)

stwuct beiscsi_hba {
	stwuct hba_pawametews pawams;
	stwuct hwi_contwowwew *phwi_ctwww;
	unsigned int mem_weq[SE_MEM_MAX];
	/* PCI BAW mapped addwesses */
	u8 __iomem *csw_va;	/* CSW */
	u8 __iomem *db_va;	/* Doow  Beww  */
	u8 __iomem *pci_va;	/* PCI Config */
	/* PCI wepwesentation of ouw HBA */
	stwuct pci_dev *pcidev;
	unsigned int num_cpus;
	unsigned int nxt_cqid;
	chaw *msi_name[MAX_CPUS];
	stwuct be_mem_descwiptow *init_mem;

	unsigned showt io_sgw_awwoc_index;
	unsigned showt io_sgw_fwee_index;
	unsigned showt io_sgw_hndw_avbw;
	stwuct sgw_handwe **io_sgw_hndw_base;

	unsigned showt eh_sgw_awwoc_index;
	unsigned showt eh_sgw_fwee_index;
	unsigned showt eh_sgw_hndw_avbw;
	stwuct sgw_handwe **eh_sgw_hndw_base;
	spinwock_t io_sgw_wock;
	spinwock_t mgmt_sgw_wock;
	spinwock_t async_pdu_wock;
	stwuct wist_head hba_queue;
#define BE_MAX_SESSION 2048
#define BE_INVAWID_CID 0xffff
#define BE_SET_CID_TO_CWI(cwi_index, cid) \
			  (phba->cid_to_cwi_map[cid] = cwi_index)
#define BE_GET_CWI_FWOM_CID(cid) (phba->cid_to_cwi_map[cid])
	unsigned showt cid_to_cwi_map[BE_MAX_SESSION];
	stwuct uwp_cid_info *cid_awway_info[BEISCSI_UWP_COUNT];
	stwuct iscsi_endpoint **ep_awway;
	stwuct beiscsi_conn **conn_tabwe;
	stwuct Scsi_Host *shost;
	stwuct iscsi_iface *ipv4_iface;
	stwuct iscsi_iface *ipv6_iface;
	stwuct {
		/**
		 * gwoup togethew since they awe used most fwequentwy
		 * fow cid to cwi convewsion
		 */
#define BEISCSI_PHYS_POWT_MAX	4
		unsigned int phys_powt;
		/* vawid vawues of phys_powt id awe 0, 1, 2, 3 */
		unsigned int eqid_count;
		unsigned int cqid_count;
		unsigned int iscsi_cid_stawt[BEISCSI_UWP_COUNT];
#define BEISCSI_GET_CID_COUNT(phba, uwp_num) \
		(phba->fw_config.iscsi_cid_count[uwp_num])
		unsigned int iscsi_cid_count[BEISCSI_UWP_COUNT];
		unsigned int iscsi_icd_count[BEISCSI_UWP_COUNT];
		unsigned int iscsi_icd_stawt[BEISCSI_UWP_COUNT];
		unsigned int iscsi_chain_stawt[BEISCSI_UWP_COUNT];
		unsigned int iscsi_chain_count[BEISCSI_UWP_COUNT];

		unsigned showt iscsi_featuwes;
		uint16_t duaw_uwp_awawe;
		unsigned wong uwp_suppowted;
	} fw_config;

	unsigned wong state;
#define BEISCSI_HBA_ONWINE	0
#define BEISCSI_HBA_WINK_UP	1
#define BEISCSI_HBA_BOOT_FOUND	2
#define BEISCSI_HBA_BOOT_WOWK	3
#define BEISCSI_HBA_UEW_SUPP	4
#define BEISCSI_HBA_PCI_EWW	5
#define BEISCSI_HBA_FW_TIMEOUT	6
#define BEISCSI_HBA_IN_UE	7
#define BEISCSI_HBA_IN_TPE	8

/* ewwow bits */
#define BEISCSI_HBA_IN_EWW	((1 << BEISCSI_HBA_PCI_EWW) | \
				 (1 << BEISCSI_HBA_FW_TIMEOUT) | \
				 (1 << BEISCSI_HBA_IN_UE) | \
				 (1 << BEISCSI_HBA_IN_TPE))

	u8 optic_state;
	stwuct dewayed_wowk eqd_update;
	/* update EQ deway timew evewy 1000ms */
#define BEISCSI_EQD_UPDATE_INTEWVAW	1000
	stwuct timew_wist hw_check;
	/* check fow UE evewy 1000ms */
#define BEISCSI_UE_DETECT_INTEWVAW	1000
	u32 ue2wp;
	stwuct dewayed_wowk wecovew_powt;
	stwuct wowk_stwuct sess_wowk;

	boow mac_addw_set;
	u8 mac_addwess[ETH_AWEN];
	u8 powt_name;
	u8 powt_speed;
	chaw fw_vew_stw[BEISCSI_VEW_STWWEN];
	stwuct wowkqueue_stwuct *wq;	/* The actuak wowk queue */
	stwuct be_ctww_info ctww;
	unsigned int genewation;
	unsigned int intewface_handwe;

	stwuct be_aic_obj aic_obj[MAX_CPUS];
	unsigned int attw_wog_enabwe;
	int (*iotask_fn)(stwuct iscsi_task *,
			stwuct scattewwist *sg,
			uint32_t num_sg, uint32_t xfewwen,
			uint32_t wwitediw);
	stwuct boot_stwuct {
		int wetwy;
		unsigned int tag;
		unsigned int s_handwe;
		stwuct be_dma_mem nonemb_cmd;
		enum {
			BEISCSI_BOOT_WEOPEN_SESS = 1,
			BEISCSI_BOOT_GET_SHANDWE,
			BEISCSI_BOOT_GET_SINFO,
			BEISCSI_BOOT_WOGOUT_SESS,
			BEISCSI_BOOT_CWEATE_KSET,
		} action;
		stwuct mgmt_session_info boot_sess;
		stwuct iscsi_boot_kset *boot_kset;
	} boot_stwuct;
	stwuct wowk_stwuct boot_wowk;
};

#define beiscsi_hba_in_ewwow(phba) ((phba)->state & BEISCSI_HBA_IN_EWW)
#define beiscsi_hba_is_onwine(phba) \
	(!beiscsi_hba_in_ewwow((phba)) && \
	 test_bit(BEISCSI_HBA_ONWINE, &phba->state))

stwuct beiscsi_session {
	stwuct dma_poow *bhs_poow;
};

/**
 * stwuct beiscsi_conn - iscsi connection stwuctuwe
 */
stwuct beiscsi_conn {
	stwuct iscsi_conn *conn;
	stwuct beiscsi_hba *phba;
	u32 exp_statsn;
	u32 doowbeww_offset;
	u32 beiscsi_conn_cid;
	stwuct beiscsi_endpoint *ep;
	unsigned showt wogin_in_pwogwess;
	stwuct wwb_handwe *pwogin_wwb_handwe;
	stwuct sgw_handwe *pwogin_sgw_handwe;
	stwuct beiscsi_session *beiscsi_sess;
	stwuct iscsi_task *task;
};

/* This stwuctuwe is used by the chip */
stwuct pdu_data_out {
	u32 dw[12];
};
/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_pdu_data_out {
	u8 opcode[6];		/* opcode */
	u8 wsvd0[2];		/* shouwd be 0 */
	u8 wsvd1[7];
	u8 finaw_bit;		/* F bit */
	u8 wsvd2[16];
	u8 ahs_wength[8];	/* no AHS */
	u8 data_wen_hi[8];
	u8 data_wen_wo[16];	/* DataSegmentWength */
	u8 wun[64];
	u8 itt[32];		/* ITT; initiatow task tag */
	u8 ttt[32];		/* TTT; vawid fow W2T ow 0xffffffff */
	u8 wsvd3[32];
	u8 exp_stat_sn[32];
	u8 wsvd4[32];
	u8 data_sn[32];
	u8 buffew_offset[32];
	u8 wsvd5[32];
};

stwuct be_cmd_bhs {
	stwuct iscsi_scsi_weq iscsi_hdw;
	unsigned chaw pad1[16];
	stwuct pdu_data_out iscsi_data_pdu;
	unsigned chaw pad2[BE_SENSE_INFO_SIZE -
			sizeof(stwuct pdu_data_out)];
};

stwuct beiscsi_io_task {
	stwuct wwb_handwe *pwwb_handwe;
	stwuct sgw_handwe *psgw_handwe;
	stwuct beiscsi_conn *conn;
	stwuct scsi_cmnd *scsi_cmnd;
	int num_sg;
	stwuct hwi_wwb_context *pwwb_context;
	itt_t wibiscsi_itt;
	stwuct be_cmd_bhs *cmd_bhs;
	stwuct be_bus_addwess bhs_pa;
	unsigned showt bhs_wen;
	dma_addw_t mtask_addw;
	uint32_t mtask_data_count;
	uint8_t wwb_type;
};

stwuct be_nonio_bhs {
	stwuct iscsi_hdw iscsi_hdw;
	unsigned chaw pad1[16];
	stwuct pdu_data_out iscsi_data_pdu;
	unsigned chaw pad2[BE_SENSE_INFO_SIZE -
			sizeof(stwuct pdu_data_out)];
};

stwuct be_status_bhs {
	stwuct iscsi_scsi_weq iscsi_hdw;
	unsigned chaw pad1[16];
	/**
	 * The pwus 2 bewow is to howd the sense info wength that gets
	 * DMA'ed by WxUWP
	 */
	unsigned chaw sense_info[BE_SENSE_INFO_SIZE];
};

stwuct iscsi_sge {
	u32 dw[4];
};

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_iscsi_sge {
	u8 addw_hi[32];
	u8 addw_wo[32];
	u8 sge_offset[22];	/* DWOWD 2 */
	u8 wsvd0[9];		/* DWOWD 2 */
	u8 wast_sge;		/* DWOWD 2 */
	u8 wen[17];		/* DWOWD 3 */
	u8 wsvd1[15];		/* DWOWD 3 */
};

stwuct beiscsi_offwoad_pawams {
	u32 dw[6];
};

#define OFFWD_PAWAMS_EWW	0x00000003
#define OFFWD_PAWAMS_DDE	0x00000004
#define OFFWD_PAWAMS_HDE	0x00000008
#define OFFWD_PAWAMS_IW2T	0x00000010
#define OFFWD_PAWAMS_IMD	0x00000020
#define OFFWD_PAWAMS_DATA_SEQ_INOWDEW   0x00000040
#define OFFWD_PAWAMS_PDU_SEQ_INOWDEW    0x00000080
#define OFFWD_PAWAMS_MAX_W2T 0x00FFFF00

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_beiscsi_offwoad_pawams {
	u8 max_buwst_wength[32];
	u8 max_send_data_segment_wength[32];
	u8 fiwst_buwst_wength[32];
	u8 eww[2];
	u8 dde[1];
	u8 hde[1];
	u8 iw2t[1];
	u8 imd[1];
	u8 data_seq_inowdew[1];
	u8 pdu_seq_inowdew[1];
	u8 max_w2t[16];
	u8 pad[8];
	u8 exp_statsn[32];
	u8 max_wecv_data_segment_wength[32];
};

stwuct hd_async_handwe {
	stwuct wist_head wink;
	stwuct be_bus_addwess pa;
	void *pbuffew;
	u32 buffew_wen;
	u16 index;
	u16 cwi;
	u8 is_headew;
	u8 is_finaw;
	u8 in_use;
};

#define BEISCSI_ASYNC_HDQ_SIZE(phba, uwp) \
	(BEISCSI_GET_CID_COUNT((phba), (uwp)) * 2)

/**
 * This has wist of async PDUs that awe waiting to be pwocessed.
 * Buffews wive in this wist fow a bwief duwation befowe they get
 * pwocessed and posted back to hawdwawe.
 * Note that we don't weawwy need one cwi_wait_queue pew async_entwy.
 * We need one cwi_wait_queue pew CWI. Its easiew to manage if this
 * is tagged awong with the async_entwy.
 */
stwuct hd_async_entwy {
	stwuct cwi_wait_queue {
		unsigned showt hdw_wen;
		unsigned int bytes_weceived;
		unsigned int bytes_needed;
		stwuct wist_head wist;
	} wq;
	/* handwes posted to FW wesides hewe */
	stwuct hd_async_handwe *headew;
	stwuct hd_async_handwe *data;
};

stwuct hd_async_buf_context {
	stwuct be_bus_addwess pa_base;
	void *va_base;
	void *wing_base;
	stwuct hd_async_handwe *handwe_base;
	u32 buffew_size;
	u16 pi;
};

/**
 * hd_async_context is decwawed fow each UWP suppowting iSCSI function.
 */
stwuct hd_async_context {
	stwuct hd_async_buf_context async_headew;
	stwuct hd_async_buf_context async_data;
	u16 num_entwies;
	/**
	 * When unsow PDU is in, it needs to be chained tiww aww the bytes awe
	 * weceived and then pwocessing is done. hd_async_entwy is cweated
	 * based on the cid_count fow each UWP. When unsow PDU comes in based
	 * on the conn_id it needs to be added to the cowwect async_entwy wq.
	 * Bewow defined cid_to_async_cwi_map is used to wetewive the
	 * async_cwi_map fow a pawticuwaw connection.
	 *
	 * This awway is initiawized aftew beiscsi_cweate_wwb_wings wetuwns.
	 *
	 * - this method takes mowe memowy space, fixed to 2K
	 * - any suppowt fow connections gweatew than this the awway size needs
	 * to be incwemented
	 */
#define BE_GET_ASYNC_CWI_FWOM_CID(cid) (pasync_ctx->cid_to_async_cwi_map[cid])
	unsigned showt cid_to_async_cwi_map[BE_MAX_SESSION];
	/**
	 * This is a vawiabwe size awway. Don`t add anything aftew this fiewd!!
	 */
	stwuct hd_async_entwy *async_entwy;
};

stwuct i_t_dpdu_cqe {
	u32 dw[4];
} __packed;

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_i_t_dpdu_cqe {
	u8 db_addw_hi[32];
	u8 db_addw_wo[32];
	u8 code[6];
	u8 cid[10];
	u8 dpw[16];
	u8 index[16];
	u8 num_cons[10];
	u8 wsvd0[4];
	u8 finaw;
	u8 vawid;
} __packed;

stwuct amap_i_t_dpdu_cqe_v2 {
	u8 db_addw_hi[32];  /* DWOWD 0 */
	u8 db_addw_wo[32];  /* DWOWD 1 */
	u8 code[6]; /* DWOWD 2 */
	u8 num_cons; /* DWOWD 2*/
	u8 wsvd0[8]; /* DWOWD 2 */
	u8 dpw[17]; /* DWOWD 2 */
	u8 index[16]; /* DWOWD 3 */
	u8 cid[13]; /* DWOWD 3 */
	u8 wsvd1; /* DWOWD 3 */
	u8 finaw; /* DWOWD 3 */
	u8 vawid; /* DWOWD 3 */
} __packed;

#define CQE_VAWID_MASK	0x80000000
#define CQE_CODE_MASK	0x0000003F
#define CQE_CID_MASK	0x0000FFC0

#define EQE_VAWID_MASK		0x00000001
#define EQE_MAJOWCODE_MASK	0x0000000E
#define EQE_WESID_MASK		0xFFFF0000

stwuct be_eq_entwy {
	u32 dw[1];
} __packed;

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_eq_entwy {
	u8 vawid;		/* DWOWD 0 */
	u8 majow_code[3];	/* DWOWD 0 */
	u8 minow_code[12];	/* DWOWD 0 */
	u8 wesouwce_id[16];	/* DWOWD 0 */

} __packed;

stwuct cq_db {
	u32 dw[1];
} __packed;

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_cq_db {
	u8 qid[10];
	u8 event[1];
	u8 wsvd0[5];
	u8 num_popped[13];
	u8 weawm[1];
	u8 wsvd1[2];
} __packed;

void beiscsi_pwocess_eq(stwuct beiscsi_hba *phba);

stwuct iscsi_wwb {
	u32 dw[16];
} __packed;

#define WWB_TYPE_MASK 0xF0000000
#define SKH_WWB_TYPE_OFFSET 27
#define BE_WWB_TYPE_OFFSET  28

#define ADAPTEW_SET_WWB_TYPE(pwwb, wwb_type, type_offset) \
		(pwwb->dw[0] |= (wwb_type << type_offset))

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_iscsi_wwb {
	u8 wun[14];		/* DWOWD 0 */
	u8 wt;			/* DWOWD 0 */
	u8 invwd;		/* DWOWD 0 */
	u8 wwb_idx[8];		/* DWOWD 0 */
	u8 dsp;			/* DWOWD 0 */
	u8 dmsg;		/* DWOWD 0 */
	u8 undw_wun;		/* DWOWD 0 */
	u8 ovew_wun;		/* DWOWD 0 */
	u8 type[4];		/* DWOWD 0 */
	u8 ptw2nextwwb[8];	/* DWOWD 1 */
	u8 w2t_exp_dtw[24];	/* DWOWD 1 */
	u8 sgw_icd_idx[12];	/* DWOWD 2 */
	u8 wsvd0[20];		/* DWOWD 2 */
	u8 exp_data_sn[32];	/* DWOWD 3 */
	u8 iscsi_bhs_addw_hi[32];	/* DWOWD 4 */
	u8 iscsi_bhs_addw_wo[32];	/* DWOWD 5 */
	u8 cmdsn_itt[32];	/* DWOWD 6 */
	u8 dif_wef_tag[32];	/* DWOWD 7 */
	u8 sge0_addw_hi[32];	/* DWOWD 8 */
	u8 sge0_addw_wo[32];	/* DWOWD 9  */
	u8 sge0_offset[22];	/* DWOWD 10 */
	u8 pbs;			/* DWOWD 10 */
	u8 dif_mode[2];		/* DWOWD 10 */
	u8 wsvd1[6];		/* DWOWD 10 */
	u8 sge0_wast;		/* DWOWD 10 */
	u8 sge0_wen[17];	/* DWOWD 11 */
	u8 dif_meta_tag[14];	/* DWOWD 11 */
	u8 sge0_in_ddw;		/* DWOWD 11 */
	u8 sge1_addw_hi[32];	/* DWOWD 12 */
	u8 sge1_addw_wo[32];	/* DWOWD 13 */
	u8 sge1_w2t_offset[22];	/* DWOWD 14 */
	u8 wsvd2[9];		/* DWOWD 14 */
	u8 sge1_wast;		/* DWOWD 14 */
	u8 sge1_wen[17];	/* DWOWD 15 */
	u8 wef_sgw_icd_idx[12];	/* DWOWD 15 */
	u8 wsvd3[2];		/* DWOWD 15 */
	u8 sge1_in_ddw;		/* DWOWD 15 */

} __packed;

stwuct amap_iscsi_wwb_v2 {
	u8 w2t_exp_dtw[25]; /* DWOWD 0 */
	u8 wsvd0[2];    /* DWOWD 0*/
	u8 type[5];     /* DWOWD 0 */
	u8 ptw2nextwwb[8];  /* DWOWD 1 */
	u8 wwb_idx[8];      /* DWOWD 1 */
	u8 wun[16];     /* DWOWD 1 */
	u8 sgw_idx[16]; /* DWOWD 2 */
	u8 wef_sgw_icd_idx[16]; /* DWOWD 2 */
	u8 exp_data_sn[32]; /* DWOWD 3 */
	u8 iscsi_bhs_addw_hi[32];   /* DWOWD 4 */
	u8 iscsi_bhs_addw_wo[32];   /* DWOWD 5 */
	u8 cq_id[16];   /* DWOWD 6 */
	u8 wsvd1[16];   /* DWOWD 6 */
	u8 cmdsn_itt[32];   /* DWOWD 7 */
	u8 sge0_addw_hi[32];    /* DWOWD 8 */
	u8 sge0_addw_wo[32];    /* DWOWD 9 */
	u8 sge0_offset[24]; /* DWOWD 10 */
	u8 wsvd2[7];    /* DWOWD 10 */
	u8 sge0_wast;   /* DWOWD 10 */
	u8 sge0_wen[17];    /* DWOWD 11 */
	u8 wsvd3[7];    /* DWOWD 11 */
	u8 diff_enbw;   /* DWOWD 11 */
	u8 u_wun;       /* DWOWD 11 */
	u8 o_wun;       /* DWOWD 11 */
	u8 invwd;     /* DWOWD 11 */
	u8 dsp;         /* DWOWD 11 */
	u8 dmsg;        /* DWOWD 11 */
	u8 wsvd4;       /* DWOWD 11 */
	u8 wt;          /* DWOWD 11 */
	u8 sge1_addw_hi[32];    /* DWOWD 12 */
	u8 sge1_addw_wo[32];    /* DWOWD 13 */
	u8 sge1_w2t_offset[24]; /* DWOWD 14 */
	u8 wsvd5[7];    /* DWOWD 14 */
	u8 sge1_wast;   /* DWOWD 14 */
	u8 sge1_wen[17];    /* DWOWD 15 */
	u8 wsvd6[15];   /* DWOWD 15 */
} __packed;


stwuct wwb_handwe *awwoc_wwb_handwe(stwuct beiscsi_hba *phba, unsigned int cid,
				     stwuct hwi_wwb_context **pcontext);
void
fwee_mgmt_sgw_handwe(stwuct beiscsi_hba *phba, stwuct sgw_handwe *psgw_handwe);

void beiscsi_fwee_mgmt_task_handwes(stwuct beiscsi_conn *beiscsi_conn,
				     stwuct iscsi_task *task);

void hwi_wing_cq_db(stwuct beiscsi_hba *phba,
		     unsigned int id, unsigned int num_pwocessed,
		     unsigned chaw weawm);

unsigned int beiscsi_pwocess_cq(stwuct be_eq_obj *pbe_eq, int budget);
void beiscsi_pwocess_mcc_cq(stwuct beiscsi_hba *phba);

stwuct pdu_nop_out {
	u32 dw[12];
};

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_pdu_nop_out {
	u8 opcode[6];		/* opcode 0x00 */
	u8 i_bit;		/* I Bit */
	u8 x_bit;		/* wesewved; shouwd be 0 */
	u8 fp_bit_fiwwew1[7];
	u8 f_bit;		/* awways 1 */
	u8 wesewved1[16];
	u8 ahs_wength[8];	/* no AHS */
	u8 data_wen_hi[8];
	u8 data_wen_wo[16];	/* DataSegmentWength */
	u8 wun[64];
	u8 itt[32];		/* initiatow id fow ping ow 0xffffffff */
	u8 ttt[32];		/* tawget id fow ping ow 0xffffffff */
	u8 cmd_sn[32];
	u8 exp_stat_sn[32];
	u8 wesewved5[128];
};

#define PDUBASE_OPCODE_MASK	0x0000003F
#define PDUBASE_DATAWENHI_MASK	0x0000FF00
#define PDUBASE_DATAWENWO_MASK	0xFFFF0000

stwuct pdu_base {
	u32 dw[16];
} __packed;

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_pdu_base {
	u8 opcode[6];
	u8 i_bit;		/* immediate bit */
	u8 x_bit;		/* wesewved, awways 0 */
	u8 wesewved1[24];	/* opcode-specific fiewds */
	u8 ahs_wength[8];	/* wength units is 4 byte wowds */
	u8 data_wen_hi[8];
	u8 data_wen_wo[16];	/* DatasegmentWength */
	u8 wun[64];		/* wun ow opcode-specific fiewds */
	u8 itt[32];		/* initiatow task tag */
	u8 wesewved4[224];
};

stwuct iscsi_tawget_context_update_wwb {
	u32 dw[16];
} __packed;

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd
 */
#define BE_TGT_CTX_UPDT_CMD 0x07
stwuct amap_iscsi_tawget_context_update_wwb {
	u8 wun[14];		/* DWOWD 0 */
	u8 wt;			/* DWOWD 0 */
	u8 invwd;		/* DWOWD 0 */
	u8 wwb_idx[8];		/* DWOWD 0 */
	u8 dsp;			/* DWOWD 0 */
	u8 dmsg;		/* DWOWD 0 */
	u8 undw_wun;		/* DWOWD 0 */
	u8 ovew_wun;		/* DWOWD 0 */
	u8 type[4];		/* DWOWD 0 */
	u8 ptw2nextwwb[8];	/* DWOWD 1 */
	u8 max_buwst_wength[19];	/* DWOWD 1 */
	u8 wsvd0[5];		/* DWOWD 1 */
	u8 wsvd1[15];		/* DWOWD 2 */
	u8 max_send_data_segment_wength[17];	/* DWOWD 2 */
	u8 fiwst_buwst_wength[14];	/* DWOWD 3 */
	u8 wsvd2[2];		/* DWOWD 3 */
	u8 tx_wwbindex_dwv_msg[8];	/* DWOWD 3 */
	u8 wsvd3[5];		/* DWOWD 3 */
	u8 session_state[3];	/* DWOWD 3 */
	u8 wsvd4[16];		/* DWOWD 4 */
	u8 tx_jumbo;		/* DWOWD 4 */
	u8 hde;			/* DWOWD 4 */
	u8 dde;			/* DWOWD 4 */
	u8 eww[2];		/* DWOWD 4 */
	u8 domain_id[5];		/* DWOWD 4 */
	u8 mode;		/* DWOWD 4 */
	u8 imd;			/* DWOWD 4 */
	u8 iw2t;		/* DWOWD 4 */
	u8 notpwedbwq[2];	/* DWOWD 4 */
	u8 compwtonack;		/* DWOWD 4 */
	u8 stat_sn[32];		/* DWOWD 5 */
	u8 pad_buffew_addw_hi[32];	/* DWOWD 6 */
	u8 pad_buffew_addw_wo[32];	/* DWOWD 7 */
	u8 pad_addw_hi[32];	/* DWOWD 8 */
	u8 pad_addw_wo[32];	/* DWOWD 9 */
	u8 wsvd5[32];		/* DWOWD 10 */
	u8 wsvd6[32];		/* DWOWD 11 */
	u8 wsvd7[32];		/* DWOWD 12 */
	u8 wsvd8[32];		/* DWOWD 13 */
	u8 wsvd9[32];		/* DWOWD 14 */
	u8 wsvd10[32];		/* DWOWD 15 */

} __packed;

#define BEISCSI_MAX_WECV_DATASEG_WEN    (64 * 1024)
#define BEISCSI_MAX_CXNS    1
stwuct amap_iscsi_tawget_context_update_wwb_v2 {
	u8 max_buwst_wength[24];    /* DWOWD 0 */
	u8 wsvd0[3];    /* DWOWD 0 */
	u8 type[5];     /* DWOWD 0 */
	u8 ptw2nextwwb[8];  /* DWOWD 1 */
	u8 wwb_idx[8];      /* DWOWD 1 */
	u8 wsvd1[16];       /* DWOWD 1 */
	u8 max_send_data_segment_wength[24];    /* DWOWD 2 */
	u8 wsvd2[8];    /* DWOWD 2 */
	u8 fiwst_buwst_wength[24]; /* DWOWD 3 */
	u8 wsvd3[8]; /* DOWWD 3 */
	u8 max_w2t[16]; /* DWOWD 4 */
	u8 wsvd4;       /* DWOWD 4 */
	u8 hde;         /* DWOWD 4 */
	u8 dde;         /* DWOWD 4 */
	u8 eww[2];      /* DWOWD 4 */
	u8 wsvd5[6];    /* DWOWD 4 */
	u8 imd;         /* DWOWD 4 */
	u8 iw2t;        /* DWOWD 4 */
	u8 wsvd6[3];    /* DWOWD 4 */
	u8 stat_sn[32];     /* DWOWD 5 */
	u8 wsvd7[32];   /* DWOWD 6 */
	u8 wsvd8[32];   /* DWOWD 7 */
	u8 max_wecv_dataseg_wen[24];    /* DWOWD 8 */
	u8 wsvd9[8]; /* DWOWD 8 */
	u8 wsvd10[32];   /* DWOWD 9 */
	u8 wsvd11[32];   /* DWOWD 10 */
	u8 max_cxns[16]; /* DWOWD 11 */
	u8 wsvd12[11]; /* DWOWD  11*/
	u8 invwd; /* DWOWD 11 */
	u8 wsvd13;/* DWOWD 11*/
	u8 dmsg; /* DWOWD 11 */
	u8 data_seq_inowdew; /* DWOWD 11 */
	u8 pdu_seq_inowdew; /* DWOWD 11 */
	u8 wsvd14[32]; /*DWOWD 12 */
	u8 wsvd15[32]; /* DWOWD 13 */
	u8 wsvd16[32]; /* DWOWD 14 */
	u8 wsvd17[32]; /* DWOWD 15 */
} __packed;


stwuct be_wing {
	u32 pages;		/* queue size in pages */
	u32 id;			/* queue id assigned by bekwib */
	u32 num;		/* numbew of ewements in queue */
	u32 cidx;		/* consumew index */
	u32 pidx;		/* pwoducew index -- not used by most wings */
	u32 item_size;		/* size in bytes of one object */
	u8 uwp_num;	/* UWP to which CID binded */
	u16 wegistew_set;
	u16 doowbeww_fowmat;
	u32 doowbeww_offset;

	void *va;		/* The viwtuaw addwess of the wing.  This
				 * shouwd be wast to awwow 32 & 64 bit debuggew
				 * extensions to wowk.
				 */
};

stwuct hwi_contwowwew {
	stwuct hwi_wwb_context *wwb_context;
	stwuct be_wing defauwt_pdu_hdw[BEISCSI_UWP_COUNT];
	stwuct be_wing defauwt_pdu_data[BEISCSI_UWP_COUNT];
	stwuct hwi_context_memowy *phwi_ctxt;
};

enum hwh_type_enum {
	HWH_TYPE_IO = 1,
	HWH_TYPE_WOGOUT = 2,
	HWH_TYPE_TMF = 3,
	HWH_TYPE_NOP = 4,
	HWH_TYPE_IO_WD = 5,
	HWH_TYPE_WOGIN = 11,
	HWH_TYPE_INVAWID = 0xFFFFFFFF
};

stwuct wwb_handwe {
	unsigned showt wwb_index;
	stwuct iscsi_task *pio_handwe;
	stwuct iscsi_wwb *pwwb;
};

stwuct hwi_context_memowy {
	stwuct be_eq_obj be_eq[MAX_CPUS];
	stwuct be_queue_info be_cq[MAX_CPUS - 1];

	stwuct be_queue_info *be_wwbq;
	/**
	 * Cweate awway of UWP numbew fow bewow entwies as DEFQ
	 * wiww be cweated fow both UWP if iSCSI Pwotocow is
	 * woaded on both UWP.
	 */
	stwuct be_queue_info be_def_hdwq[BEISCSI_UWP_COUNT];
	stwuct be_queue_info be_def_dataq[BEISCSI_UWP_COUNT];
	stwuct hd_async_context *pasync_ctx[BEISCSI_UWP_COUNT];
};

void beiscsi_stawt_boot_wowk(stwuct beiscsi_hba *phba, unsigned int s_handwe);

/* Wogging wewated definitions */
#define BEISCSI_WOG_INIT	0x0001	/* Initiawization events */
#define BEISCSI_WOG_MBOX	0x0002	/* Maiwbox Events */
#define BEISCSI_WOG_MISC	0x0004	/* Miscwwaneous Events */
#define BEISCSI_WOG_EH		0x0008	/* Ewwow Handwew */
#define BEISCSI_WOG_IO		0x0010	/* IO Code Path */
#define BEISCSI_WOG_CONFIG	0x0020	/* CONFIG Code Path */
#define BEISCSI_WOG_ISCSI	0x0040	/* SCSI/iSCSI Pwotocow wewated Wogs */

#define __beiscsi_wog(phba, wevew, fmt, awg...) \
	shost_pwintk(wevew, phba->shost, fmt, __WINE__, ##awg)

#define beiscsi_wog(phba, wevew, mask, fmt, awg...) \
do { \
	uint32_t wog_vawue = phba->attw_wog_enabwe; \
		if (((mask) & wog_vawue) || (wevew[1] <= '3')) \
			__beiscsi_wog(phba, wevew, fmt, ##awg); \
} whiwe (0);

#endif
