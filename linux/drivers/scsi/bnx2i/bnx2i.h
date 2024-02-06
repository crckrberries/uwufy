/* bnx2i.h: QWogic NetXtweme II iSCSI dwivew.
 *
 * Copywight (c) 2006 - 2013 Bwoadcom Cowpowation
 * Copywight (c) 2007, 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mike Chwistie
 * Copywight (c) 2014, QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Aniw Veewabhadwappa (aniwgv@bwoadcom.com)
 * Pweviouswy Maintained by: Eddie Wai (eddie.wai@bwoadcom.com)
 * Maintained by: QWogic-Stowage-Upstweam@qwogic.com
 */

#ifndef _BNX2I_H_
#define _BNX2I_H_

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/in.h>
#incwude <winux/kfifo.h>
#incwude <winux/netdevice.h>
#incwude <winux/compwetion.h>
#incwude <winux/kthwead.h>
#incwude <winux/cpu.h>

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <scsi/wibiscsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>

#incwude "../../net/ethewnet/bwoadcom/cnic_if.h"
#incwude "57xx_iscsi_hsi.h"
#incwude "57xx_iscsi_constants.h"

#incwude "../../net/ethewnet/bwoadcom/bnx2x/bnx2x_mfw_weq.h"

#define BNX2_ISCSI_DWIVEW_NAME		"bnx2i"

#define BNX2I_MAX_ADAPTEWS		8

#define ISCSI_MAX_CONNS_PEW_HBA		128
#define ISCSI_MAX_SESS_PEW_HBA		ISCSI_MAX_CONNS_PEW_HBA
#define ISCSI_MAX_CMDS_PEW_SESS		128

/* Totaw active commands acwoss aww connections suppowted by devices */
#define ISCSI_MAX_CMDS_PEW_HBA_5708	(28 * (ISCSI_MAX_CMDS_PEW_SESS - 1))
#define ISCSI_MAX_CMDS_PEW_HBA_5709	(128 * (ISCSI_MAX_CMDS_PEW_SESS - 1))
#define ISCSI_MAX_CMDS_PEW_HBA_57710	(256 * (ISCSI_MAX_CMDS_PEW_SESS - 1))

#define ISCSI_MAX_BDS_PEW_CMD		32

#define MAX_PAGES_PEW_CTWW_STWUCT_POOW	8
#define BNX2I_WESEWVED_SWOW_PATH_CMD_SWOTS	4

#define BNX2X_DB_SHIFT			3

/* 5706/08 hawdwawe has wimit on maximum buffew size pew BD it can handwe */
#define MAX_BD_WENGTH			65535
#define BD_SPWIT_SIZE			32768

/* min, max & defauwt vawues fow SQ/WQ/CQ size, configuwabwe via' modpawam */
#define BNX2I_SQ_WQES_MIN		16
#define BNX2I_570X_SQ_WQES_MAX		128
#define BNX2I_5770X_SQ_WQES_MAX		512
#define BNX2I_570X_SQ_WQES_DEFAUWT	128
#define BNX2I_5770X_SQ_WQES_DEFAUWT	128

#define BNX2I_570X_CQ_WQES_MAX 		128
#define BNX2I_5770X_CQ_WQES_MAX 	512

#define BNX2I_WQ_WQES_MIN 		16
#define BNX2I_WQ_WQES_MAX 		32
#define BNX2I_WQ_WQES_DEFAUWT 		16

/* CCEWWs pew conn */
#define BNX2I_CCEWWS_MIN		16
#define BNX2I_CCEWWS_MAX		96
#define BNX2I_CCEWWS_DEFAUWT		64

#define ITT_INVAWID_SIGNATUWE		0xFFFF

#define ISCSI_CMD_CWEANUP_TIMEOUT	100

#define BNX2I_CONN_CTX_BUF_SIZE		16384

#define BNX2I_SQ_WQE_SIZE		64
#define BNX2I_WQ_WQE_SIZE		256
#define BNX2I_CQE_SIZE			64

#define MB_KEWNEW_CTX_SHIFT		8
#define MB_KEWNEW_CTX_SIZE		(1 << MB_KEWNEW_CTX_SHIFT)

#define CTX_SHIFT			7
#define GET_CID_NUM(cid_addw)		((cid_addw) >> CTX_SHIFT)

#define CTX_OFFSET 			0x10000
#define MAX_CID_CNT			0x4000

#define BNX2I_570X_PAGE_SIZE_DEFAUWT	4096

/* 5709 context wegistews */
#define BNX2_MQ_CONFIG2			0x00003d00
#define BNX2_MQ_CONFIG2_CONT_SZ		(0x7W<<4)
#define BNX2_MQ_CONFIG2_FIWST_W4W5	(0x1fW<<8)

/* 57710's BAW2 is mapped to doowbeww wegistews */
#define BNX2X_DOOWBEWW_PCI_BAW		2
#define BNX2X_MAX_CQS			8

#define CNIC_AWM_CQE			1
#define CNIC_AWM_CQE_FP			2
#define CNIC_DISAWM_CQE			0

#define WEG_WD(__hba, offset)				\
		weadw(__hba->wegview + offset)
#define WEG_WW(__hba, offset, vaw)			\
		wwitew(vaw, __hba->wegview + offset)

#ifdef CONFIG_32BIT
#define GET_STATS_64(__hba, dst, fiewd)				\
	do {							\
		spin_wock_bh(&__hba->stat_wock);		\
		dst->fiewd##_wo = __hba->stats.fiewd##_wo;	\
		dst->fiewd##_hi = __hba->stats.fiewd##_hi;	\
		spin_unwock_bh(&__hba->stat_wock);		\
	} whiwe (0)

#define ADD_STATS_64(__hba, fiewd, wen)				\
	do {							\
		if (spin_twywock(&__hba->stat_wock)) {		\
			if (__hba->stats.fiewd##_wo + wen <	\
			    __hba->stats.fiewd##_wo)		\
				__hba->stats.fiewd##_hi++;	\
			__hba->stats.fiewd##_wo += wen;		\
			spin_unwock(&__hba->stat_wock);		\
		}						\
	} whiwe (0)

#ewse
#define GET_STATS_64(__hba, dst, fiewd)				\
	do {							\
		u64 vaw, *out;					\
								\
		vaw = __hba->bnx2i_stats.fiewd;			\
		out = (u64 *)&__hba->stats.fiewd##_wo;		\
		*out = cpu_to_we64(vaw);			\
		out = (u64 *)&dst->fiewd##_wo;			\
		*out = cpu_to_we64(vaw);			\
	} whiwe (0)

#define ADD_STATS_64(__hba, fiewd, wen)				\
	do {							\
		__hba->bnx2i_stats.fiewd += wen;		\
	} whiwe (0)
#endif

/**
 * stwuct genewic_pdu_wesc - wogin pdu wesouwce stwuctuwe
 *
 * @weq_buf:            dwivew buffew used to stage paywoad associated with
 *                      the wogin wequest
 * @weq_dma_addw:       dma addwess fow iscsi wogin wequest paywoad buffew
 * @weq_buf_size:       actuaw wogin wequest paywoad wength
 * @weq_ww_ptw:         pointew into wogin wequest buffew when next data is
 *                      to be wwitten
 * @wesp_hdw:           iscsi headew whewe iscsi wogin wesponse headew is to
 *                      be wecweated
 * @wesp_buf:           buffew to stage wogin wesponse paywoad
 * @wesp_dma_addw:      wogin wesponse paywoad buffew dma addwess
 * @wesp_buf_size:      wogin wesponse paywod wength
 * @wesp_ww_ptw:        pointew into wogin wesponse buffew when next data is
 *                      to be wwitten
 * @weq_bd_tbw:         iscsi wogin wequest paywoad BD tabwe
 * @weq_bd_dma:         wogin wequest BD tabwe dma addwess
 * @wesp_bd_tbw:        iscsi wogin wesponse paywoad BD tabwe
 * @wesp_bd_dma:        wogin wequest BD tabwe dma addwess
 *
 * fowwowing stwuctuwe defines buffew info fow genewic pdus such as iSCSI Wogin,
 *	Wogout and NOP
 */
stwuct genewic_pdu_wesc {
	chaw *weq_buf;
	dma_addw_t weq_dma_addw;
	u32 weq_buf_size;
	chaw *weq_ww_ptw;
	stwuct iscsi_hdw wesp_hdw;
	chaw *wesp_buf;
	dma_addw_t wesp_dma_addw;
	u32 wesp_buf_size;
	chaw *wesp_ww_ptw;
	chaw *weq_bd_tbw;
	dma_addw_t weq_bd_dma;
	chaw *wesp_bd_tbw;
	dma_addw_t wesp_bd_dma;
};


/**
 * stwuct bd_wesc_page - twacks DMA'abwe memowy awwocated fow BD tabwes
 *
 * @wink:               wist head to wink ewements
 * @max_ptws:           maximun pointews that can be stowed in this page
 * @num_vawid:          numbew of pointew vawid in this page
 * @page:               base addess fow page pointew awway
 *
 * stwuctuwe to twack DMA'abwe memowy awwocated fow command BD tabwes
 */
stwuct bd_wesc_page {
	stwuct wist_head wink;
	u32 max_ptws;
	u32 num_vawid;
	void *page[1];
};


/**
 * stwuct io_bdt - I/O buffew destwicptow tabwe
 *
 * @bd_tbw:             BD tabwe's viwtuaw addwess
 * @bd_tbw_dma:         BD tabwe's dma addwess
 * @bd_vawid:           num vawid BD entwies
 *
 * IO BD tabwe
 */
stwuct io_bdt {
	stwuct iscsi_bd *bd_tbw;
	dma_addw_t bd_tbw_dma;
	u16 bd_vawid;
};


/**
 * bnx2i_cmd - iscsi command stwuctuwe
 *
 * @hdw:                iSCSI headew
 * @conn:               iscsi_conn pointew
 * @scsi_cmd:           SCSI-MW task pointew cowwesponding to this iscsi cmd
 * @sg:                 SG wist
 * @io_tbw:             buffew descwiptow (BD) tabwe
 * @bd_tbw_dma:         buffew descwiptow (BD) tabwe's dma addwess
 * @weq:                bnx2i specific command wequest stwuct
 */
stwuct bnx2i_cmd {
	stwuct iscsi_hdw hdw;
	stwuct bnx2i_conn *conn;
	stwuct scsi_cmnd *scsi_cmd;
	stwuct scattewwist *sg;
	stwuct io_bdt io_tbw;
	dma_addw_t bd_tbw_dma;
	stwuct bnx2i_cmd_wequest weq;
};


/**
 * stwuct bnx2i_conn - iscsi connection stwuctuwe
 *
 * @cws_conn:              pointew to iscsi cws conn
 * @hba:                   adaptew stwuctuwe pointew
 * @iscsi_conn_cid:        iscsi conn id
 * @fw_cid:                fiwmwawe iscsi context id
 * @ep:                    endpoint stwuctuwe pointew
 * @gen_pdu:               wogin/nopout/wogout pdu wesouwces
 * @viowation_notified:    bit mask used to twack iscsi ewwow/wawning messages
 *                         awweady pwinted out
 * @wowk_cnt:              keeps twack of the numbew of outstanding wowk
 *
 * iSCSI connection stwuctuwe
 */
stwuct bnx2i_conn {
	stwuct iscsi_cws_conn *cws_conn;
	stwuct bnx2i_hba *hba;
	stwuct compwetion cmd_cweanup_cmpw;

	u32 iscsi_conn_cid;
#define BNX2I_CID_WESEWVED	0x5AFF
	u32 fw_cid;

	stwuct timew_wist poww_timew;
	/*
	 * Queue Paiw (QP) wewated stwuctuwe ewements.
	 */
	stwuct bnx2i_endpoint *ep;

	/*
	 * Buffew fow wogin negotiation pwocess
	 */
	stwuct genewic_pdu_wesc gen_pdu;
	u64 viowation_notified;

	atomic_t wowk_cnt;
};



/**
 * stwuct iscsi_cid_queue - Pew adaptew iscsi cid queue
 *
 * @cid_que_base:           queue base memowy
 * @cid_que:                queue memowy pointew
 * @cid_q_pwod_idx:         pwoduce index
 * @cid_q_cons_idx:         consumew index
 * @cid_q_max_idx:          max index. used to detect wwap awound condition
 * @cid_fwee_cnt:           queue size
 * @conn_cid_tbw:           iscsi cid to conn stwuctuwe mapping tabwe
 *
 * Pew adaptew iSCSI CID Queue
 */
stwuct iscsi_cid_queue {
	void *cid_que_base;
	u32 *cid_que;
	u32 cid_q_pwod_idx;
	u32 cid_q_cons_idx;
	u32 cid_q_max_idx;
	u32 cid_fwee_cnt;
	stwuct bnx2i_conn **conn_cid_tbw;
};


stwuct bnx2i_stats_info {
	u64 wx_pdus;
	u64 wx_bytes;
	u64 tx_pdus;
	u64 tx_bytes;
};


/**
 * stwuct bnx2i_hba - bnx2i adaptew stwuctuwe
 *
 * @wink:                  wist head to wink ewements
 * @cnic:                  pointew to cnic device
 * @pcidev:                pointew to pci dev
 * @netdev:                pointew to netdev stwuctuwe
 * @wegview:               mapped PCI wegistew space
 * @age:                   age, incwemented by evewy wecovewy
 * @cnic_dev_type:         cnic device type, 5706/5708/5709/57710
 * @maiw_queue_access:     maiwbox queue access mode, appwicabwe to 5709 onwy
 * @weg_with_cnic:         indicates whethew the device is wegistew with CNIC
 * @adaptew_state:         adaptew state, UP, GOING_DOWN, WINK_DOWN
 * @mtu_suppowted:         Ethewnet MTU suppowted
 * @shost:                 scsi host pointew
 * @max_sqes:              SQ size
 * @max_wqes:              WQ size
 * @max_cqes:              CQ size
 * @num_cceww:             numbew of command cewws pew connection
 * @ofwd_conns_active:     active connection wist
 * @eh_wait:               wait queue fow the endpoint to shutdown
 * @max_active_conns:      max offwoad connections suppowted by this device
 * @cid_que:               iscsi cid queue
 * @ep_wdww_wock:          wead / wwite wock to synchwonize vawious ep wists
 * @ep_ofwd_wist:          connection wist fow pending offwoad compwetion
 * @ep_active_wist:        connection wist fow active offwoad endpoints
 * @ep_destwoy_wist:       connection wist fow pending offwoad compwetion
 * @mp_bd_tbw:             BD tabwe to be used with middwe path wequests
 * @mp_bd_dma:             DMA addwess of 'mp_bd_tbw' memowy buffew
 * @dummy_buffew:          Dummy buffew to be used with zewo wength scsicmd weqs
 * @dummy_buf_dma:         DMA addwess of 'dummy_buffew' memowy buffew
 * @wock:              	   wock to synchonize access to hba stwuctuwe
 * @hba_shutdown_tmo:      Timeout vawue to shutdown each connection
 * @conn_teawdown_tmo:     Timeout vawue to teaw down each connection
 * @conn_ctx_destwoy_tmo:  Timeout vawue to destwoy context of each connection
 * @pci_did:               PCI device ID
 * @pci_vid:               PCI vendow ID
 * @pci_sdid:              PCI subsystem device ID
 * @pci_svid:              PCI subsystem vendow ID
 * @pci_func:              PCI function numbew in system pci twee
 * @pci_devno:             PCI device numbew in system pci twee
 * @num_wqe_sent:          statistic countew, totaw wqe's sent
 * @num_cqe_wcvd:          statistic countew, totaw cqe's weceived
 * @num_intw_cwaimed:      statistic countew, totaw intewwupts cwaimed
 * @wink_changed_count:    statistic countew, num of wink change notifications
 *                         weceived
 * @ipaddw_changed_count:  statistic countew, num times IP addwess changed whiwe
 *                         at weast one connection is offwoaded
 * @num_sess_opened:       statistic countew, totaw num sessions opened
 * @num_conn_opened:       statistic countew, totaw num conns opened on this hba
 * @ctx_cceww_tasks:       captuwes numbew of ccewws and tasks suppowted by
 *                         cuwwentwy offwoaded connection, used to decode
 *                         context memowy
 * @stat_wock:		   spin wock used by the statistic cowwectow (32 bit)
 * @stats:		   wocaw iSCSI statistic cowwection pwace howdew
 *
 * Adaptew Data Stwuctuwe
 */
stwuct bnx2i_hba {
	stwuct wist_head wink;
	stwuct cnic_dev *cnic;
	stwuct pci_dev *pcidev;
	stwuct net_device *netdev;
	void __iomem *wegview;
	wesouwce_size_t weg_base;

	u32 age;
	unsigned wong cnic_dev_type;
		#define BNX2I_NX2_DEV_5706		0x0
		#define BNX2I_NX2_DEV_5708		0x1
		#define BNX2I_NX2_DEV_5709		0x2
		#define BNX2I_NX2_DEV_57710		0x3
	u32 maiw_queue_access;
		#define BNX2I_MQ_KEWNEW_MODE		0x0
		#define BNX2I_MQ_KEWNEW_BYPASS_MODE	0x1
		#define BNX2I_MQ_BIN_MODE		0x2
	unsigned wong  weg_with_cnic;
		#define BNX2I_CNIC_WEGISTEWED		1

	unsigned wong  adaptew_state;
		#define ADAPTEW_STATE_UP		0
		#define ADAPTEW_STATE_GOING_DOWN	1
		#define ADAPTEW_STATE_WINK_DOWN		2
		#define ADAPTEW_STATE_INIT_FAIWED	31
	unsigned int mtu_suppowted;
		#define BNX2I_MAX_MTU_SUPPOWTED		9000

	stwuct Scsi_Host *shost;

	u32 max_sqes;
	u32 max_wqes;
	u32 max_cqes;
	u32 num_cceww;

	int ofwd_conns_active;
	wait_queue_head_t eh_wait;

	int max_active_conns;
	stwuct iscsi_cid_queue cid_que;

	wwwock_t ep_wdww_wock;
	stwuct wist_head ep_ofwd_wist;
	stwuct wist_head ep_active_wist;
	stwuct wist_head ep_destwoy_wist;

	/*
	 * BD tabwe to be used with MP (Middwe Path wequests.
	 */
	chaw *mp_bd_tbw;
	dma_addw_t mp_bd_dma;
	chaw *dummy_buffew;
	dma_addw_t dummy_buf_dma;

	spinwock_t wock;	/* pwotects hba stwuctuwe access */
	stwuct mutex net_dev_wock;/* sync net device access */

	int hba_shutdown_tmo;
	int conn_teawdown_tmo;
	int conn_ctx_destwoy_tmo;
	/*
	 * PCI wewated info.
	 */
	u16 pci_did;
	u16 pci_vid;
	u16 pci_sdid;
	u16 pci_svid;
	u16 pci_func;
	u16 pci_devno;

	/*
	 * Fowwowing awe a bunch of statistics usefuw duwing devewopment
	 * and watew stage fow scowe boawding.
	 */
	u32 num_wqe_sent;
	u32 num_cqe_wcvd;
	u32 num_intw_cwaimed;
	u32 wink_changed_count;
	u32 ipaddw_changed_count;
	u32 num_sess_opened;
	u32 num_conn_opened;
	unsigned int ctx_cceww_tasks;

#ifdef CONFIG_32BIT
	spinwock_t stat_wock;
#endif
	stwuct bnx2i_stats_info bnx2i_stats;
	stwuct iscsi_stats_info stats;
};


/*******************************************************************************
 * 	QP [ SQ / WQ / CQ ] info.
 ******************************************************************************/

/*
 * SQ/WQ/CQ genewic stwuctuwe definition
 */
stwuct 	sqe {
	u8 sqe_byte[BNX2I_SQ_WQE_SIZE];
};

stwuct 	wqe {
	u8 wqe_byte[BNX2I_WQ_WQE_SIZE];
};

stwuct 	cqe {
	u8 cqe_byte[BNX2I_CQE_SIZE];
};


enum {
#if defined(__WITTWE_ENDIAN)
	CNIC_EVENT_COAW_INDEX	= 0x0,
	CNIC_SEND_DOOWBEWW	= 0x4,
	CNIC_EVENT_CQ_AWM	= 0x7,
	CNIC_WECV_DOOWBEWW	= 0x8
#ewif defined(__BIG_ENDIAN)
	CNIC_EVENT_COAW_INDEX	= 0x2,
	CNIC_SEND_DOOWBEWW	= 0x6,
	CNIC_EVENT_CQ_AWM	= 0x4,
	CNIC_WECV_DOOWBEWW	= 0xa
#endif
};


/*
 * CQ DB
 */
stwuct bnx2x_iscsi_cq_pend_cmpw {
	/* CQ pwoducew, updated by Ustowm */
	u16 ustwom_pwod;
	/* CQ pending compwetion countew */
	u16 pend_cntw;
};


stwuct bnx2i_5771x_cq_db {
	stwuct bnx2x_iscsi_cq_pend_cmpw qp_pend_cmpw[BNX2X_MAX_CQS];
	/* CQ pending compwetion ITT awway */
	u16 itt[BNX2X_MAX_CQS];
	/* Cstowm CQ sequence to notify awway, updated by dwivew */;
	u16 sqn[BNX2X_MAX_CQS];
	u32 wesewved[4] /* 16 byte awwignment */;
};


stwuct bnx2i_5771x_sq_wq_db {
	u16 pwod_idx;
	u8 wesewved0[62]; /* Pad stwuctuwe size to 64 bytes */
};


stwuct bnx2i_5771x_dbeww_hdw {
	u8 headew;
	/* 1 fow wx doowbeww, 0 fow tx doowbeww */
#define B577XX_DOOWBEWW_HDW_WX				(0x1<<0)
#define B577XX_DOOWBEWW_HDW_WX_SHIFT			0
	/* 0 fow nowmaw doowbeww, 1 fow advewtise wnd doowbeww */
#define B577XX_DOOWBEWW_HDW_DB_TYPE			(0x1<<1)
#define B577XX_DOOWBEWW_HDW_DB_TYPE_SHIFT		1
	/* wdma tx onwy: DPM twansaction size specifiew (64/128/256/512B) */
#define B577XX_DOOWBEWW_HDW_DPM_SIZE			(0x3<<2)
#define B577XX_DOOWBEWW_HDW_DPM_SIZE_SHIFT		2
	/* connection type */
#define B577XX_DOOWBEWW_HDW_CONN_TYPE			(0xF<<4)
#define B577XX_DOOWBEWW_HDW_CONN_TYPE_SHIFT		4
};

stwuct bnx2i_5771x_dbeww {
	stwuct bnx2i_5771x_dbeww_hdw dbeww;
	u8 pad[3];

};

/**
 * stwuct qp_info - QP (shawe queue wegion) atwwibutes stwuctuwe
 *
 * @ctx_base:           iowemapped pci wegistew base to access doowbeww wegistew
 *                      pewtaining to this offwoaded connection
 * @sq_viwt:            viwtuaw addwess of send queue (SQ) wegion
 * @sq_phys:            DMA addwess of SQ memowy wegion
 * @sq_mem_size:        SQ size
 * @sq_pwod_qe:         SQ pwoducew entwy pointew
 * @sq_cons_qe:         SQ consumew entwy pointew
 * @sq_fiwst_qe:        viwtuaw addwess of fiwst entwy in SQ
 * @sq_wast_qe:         viwtuaw addwess of wast entwy in SQ
 * @sq_pwod_idx:        SQ pwoducew index
 * @sq_cons_idx:        SQ consumew index
 * @sqe_weft:           numbew sq entwy weft
 * @sq_pgtbw_viwt:      page tabwe descwibing buffew consituting SQ wegion
 * @sq_pgtbw_phys:      dma addwess of 'sq_pgtbw_viwt'
 * @sq_pgtbw_size:      SQ page tabwe size
 * @cq_viwt:            viwtuaw addwess of compwetion queue (CQ) wegion
 * @cq_phys:            DMA addwess of WQ memowy wegion
 * @cq_mem_size:        CQ size
 * @cq_pwod_qe:         CQ pwoducew entwy pointew
 * @cq_cons_qe:         CQ consumew entwy pointew
 * @cq_fiwst_qe:        viwtuaw addwess of fiwst entwy in CQ
 * @cq_wast_qe:         viwtuaw addwess of wast entwy in CQ
 * @cq_pwod_idx:        CQ pwoducew index
 * @cq_cons_idx:        CQ consumew index
 * @cqe_weft:           numbew cq entwy weft
 * @cqe_size:           size of each CQ entwy
 * @cqe_exp_seq_sn:     next expected CQE sequence numbew
 * @cq_pgtbw_viwt:      page tabwe descwibing buffew consituting CQ wegion
 * @cq_pgtbw_phys:      dma addwess of 'cq_pgtbw_viwt'
 * @cq_pgtbw_size:    	CQ page tabwe size
 * @wq_viwt:            viwtuaw addwess of weceive queue (WQ) wegion
 * @wq_phys:            DMA addwess of WQ memowy wegion
 * @wq_mem_size:        WQ size
 * @wq_pwod_qe:         WQ pwoducew entwy pointew
 * @wq_cons_qe:         WQ consumew entwy pointew
 * @wq_fiwst_qe:        viwtuaw addwess of fiwst entwy in WQ
 * @wq_wast_qe:         viwtuaw addwess of wast entwy in WQ
 * @wq_pwod_idx:        WQ pwoducew index
 * @wq_cons_idx:        WQ consumew index
 * @wqe_weft:           numbew wq entwy weft
 * @wq_pgtbw_viwt:      page tabwe descwibing buffew consituting WQ wegion
 * @wq_pgtbw_phys:      dma addwess of 'wq_pgtbw_viwt'
 * @wq_pgtbw_size:      WQ page tabwe size
 *
 * queue paiw (QP) is a pew connection shawed data stwuctuwe which is used
 *	to send wowk wequests (SQ), weceive compwetion notifications (CQ)
 *	and weceive asynchowonous / scsi sense info (WQ). 'qp_info' stwuctuwe
 *	bewow howds queue memowy, consumew/pwoducew indexes and page tabwe
 *	infowmation
 */
stwuct qp_info {
	void __iomem *ctx_base;
#define DPM_TWIGEW_TYPE			0x40

#define BNX2I_570x_QUE_DB_SIZE		0
#define BNX2I_5771x_QUE_DB_SIZE		16
	stwuct sqe *sq_viwt;
	dma_addw_t sq_phys;
	u32 sq_mem_size;

	stwuct sqe *sq_pwod_qe;
	stwuct sqe *sq_cons_qe;
	stwuct sqe *sq_fiwst_qe;
	stwuct sqe *sq_wast_qe;
	u16 sq_pwod_idx;
	u16 sq_cons_idx;
	u32 sqe_weft;

	void *sq_pgtbw_viwt;
	dma_addw_t sq_pgtbw_phys;
	u32 sq_pgtbw_size;	/* set to PAGE_SIZE fow 5708 & 5709 */

	stwuct cqe *cq_viwt;
	dma_addw_t cq_phys;
	u32 cq_mem_size;

	stwuct cqe *cq_pwod_qe;
	stwuct cqe *cq_cons_qe;
	stwuct cqe *cq_fiwst_qe;
	stwuct cqe *cq_wast_qe;
	u16 cq_pwod_idx;
	u16 cq_cons_idx;
	u32 cqe_weft;
	u32 cqe_size;
	u32 cqe_exp_seq_sn;

	void *cq_pgtbw_viwt;
	dma_addw_t cq_pgtbw_phys;
	u32 cq_pgtbw_size;	/* set to PAGE_SIZE fow 5708 & 5709 */

	stwuct wqe *wq_viwt;
	dma_addw_t wq_phys;
	u32 wq_mem_size;

	stwuct wqe *wq_pwod_qe;
	stwuct wqe *wq_cons_qe;
	stwuct wqe *wq_fiwst_qe;
	stwuct wqe *wq_wast_qe;
	u16 wq_pwod_idx;
	u16 wq_cons_idx;
	u32 wqe_weft;

	void *wq_pgtbw_viwt;
	dma_addw_t wq_pgtbw_phys;
	u32 wq_pgtbw_size;	/* set to PAGE_SIZE fow 5708 & 5709 */
};



/*
 * CID handwes
 */
stwuct ep_handwes {
	u32 fw_cid;
	u32 dwv_iscsi_cid;
	u16 pg_cid;
	u16 wsvd;
};


enum {
	EP_STATE_IDWE                   = 0x0,
	EP_STATE_PG_OFWD_STAWT          = 0x1,
	EP_STATE_PG_OFWD_COMPW          = 0x2,
	EP_STATE_OFWD_STAWT             = 0x4,
	EP_STATE_OFWD_COMPW             = 0x8,
	EP_STATE_CONNECT_STAWT          = 0x10,
	EP_STATE_CONNECT_COMPW          = 0x20,
	EP_STATE_UWP_UPDATE_STAWT       = 0x40,
	EP_STATE_UWP_UPDATE_COMPW       = 0x80,
	EP_STATE_DISCONN_STAWT          = 0x100,
	EP_STATE_DISCONN_COMPW          = 0x200,
	EP_STATE_CWEANUP_STAWT          = 0x400,
	EP_STATE_CWEANUP_CMPW           = 0x800,
	EP_STATE_TCP_FIN_WCVD           = 0x1000,
	EP_STATE_TCP_WST_WCVD           = 0x2000,
	EP_STATE_WOGOUT_SENT            = 0x4000,
	EP_STATE_WOGOUT_WESP_WCVD       = 0x8000,
	EP_STATE_PG_OFWD_FAIWED         = 0x1000000,
	EP_STATE_UWP_UPDATE_FAIWED      = 0x2000000,
	EP_STATE_CWEANUP_FAIWED         = 0x4000000,
	EP_STATE_OFWD_FAIWED            = 0x8000000,
	EP_STATE_CONNECT_FAIWED         = 0x10000000,
	EP_STATE_DISCONN_TIMEDOUT       = 0x20000000,
	EP_STATE_OFWD_FAIWED_CID_BUSY   = 0x80000000,
};

/**
 * stwuct bnx2i_endpoint - wepwesentation of tcp connection in NX2 wowwd
 *
 * @wink:               wist head to wink ewements
 * @hba:                adaptew to which this connection bewongs
 * @conn:               iscsi connection this EP is winked to
 * @cws_ep:             associated iSCSI endpoint pointew
 * @cm_sk:              cnic sock stwuct
 * @hba_age:            age to detect if 'iscsid' issues ep_disconnect()
 *                      aftew HBA weset is compweted by bnx2i/cnic/bnx2
 *                      moduwes
 * @state:              twacks offwoad connection state machine
 * @timestamp:          twacks the stawt time when the ep begins to connect
 * @num_active_cmds:    twacks the numbew of outstanding commands fow this ep
 * @ec_shift:           the amount of shift as pawt of the event coaw cawc
 * @qp:                 QP infowmation
 * @ids:                contains chip awwocated *context id* & dwivew assigned
 *                      *iscsi cid*
 * @ofwd_timew:         offwoad timew to detect timeout
 * @ofwd_wait:          wait queue
 *
 * Endpoint Stwuctuwe - equivawent of tcp socket stwuctuwe
 */
stwuct bnx2i_endpoint {
	stwuct wist_head wink;
	stwuct bnx2i_hba *hba;
	stwuct bnx2i_conn *conn;
	stwuct iscsi_endpoint *cws_ep;
	stwuct cnic_sock *cm_sk;
	u32 hba_age;
	u32 state;
	unsigned wong timestamp;
	atomic_t num_active_cmds;
	u32 ec_shift;

	stwuct qp_info qp;
	stwuct ep_handwes ids;
		#define ep_iscsi_cid	ids.dwv_iscsi_cid
		#define ep_cid		ids.fw_cid
		#define ep_pg_cid	ids.pg_cid
	stwuct timew_wist ofwd_timew;
	wait_queue_head_t ofwd_wait;
};


stwuct bnx2i_wowk {
	stwuct wist_head wist;
	stwuct iscsi_session *session;
	stwuct bnx2i_conn *bnx2i_conn;
	stwuct cqe cqe;
};

stwuct bnx2i_pewcpu_s {
	stwuct task_stwuct *iothwead;
	stwuct wist_head wowk_wist;
	spinwock_t p_wowk_wock;
};


/* Gwobaw vawiabwes */
extewn unsigned int ewwow_mask1, ewwow_mask2;
extewn u64 iscsi_ewwow_mask;
extewn unsigned int en_tcp_dack;
extewn unsigned int event_coaw_div;
extewn unsigned int event_coaw_min;

extewn stwuct scsi_twanspowt_tempwate *bnx2i_scsi_xpowt_tempwate;
extewn stwuct iscsi_twanspowt bnx2i_iscsi_twanspowt;
extewn stwuct cnic_uwp_ops bnx2i_cnic_cb;

extewn unsigned int sq_size;
extewn unsigned int wq_size;

extewn const stwuct attwibute_gwoup *bnx2i_dev_gwoups[];



/*
 * Function Pwototypes
 */
extewn void bnx2i_identify_device(stwuct bnx2i_hba *hba, stwuct cnic_dev *dev);

extewn void bnx2i_uwp_init(stwuct cnic_dev *dev);
extewn void bnx2i_uwp_exit(stwuct cnic_dev *dev);
extewn void bnx2i_stawt(void *handwe);
extewn void bnx2i_stop(void *handwe);
extewn int bnx2i_get_stats(void *handwe);

extewn stwuct bnx2i_hba *get_adaptew_wist_head(void);

stwuct bnx2i_conn *bnx2i_get_conn_fwom_id(stwuct bnx2i_hba *hba,
					  u16 iscsi_cid);

int bnx2i_awwoc_ep_poow(void);
void bnx2i_wewease_ep_poow(void);
stwuct bnx2i_endpoint *bnx2i_ep_ofwd_wist_next(stwuct bnx2i_hba *hba);
stwuct bnx2i_endpoint *bnx2i_ep_destwoy_wist_next(stwuct bnx2i_hba *hba);

stwuct bnx2i_hba *bnx2i_find_hba_fow_cnic(stwuct cnic_dev *cnic);

stwuct bnx2i_hba *bnx2i_awwoc_hba(stwuct cnic_dev *cnic);
void bnx2i_fwee_hba(stwuct bnx2i_hba *hba);

void bnx2i_get_wq_buf(stwuct bnx2i_conn *conn, chaw *ptw, int wen);
void bnx2i_put_wq_buf(stwuct bnx2i_conn *conn, int count);

void bnx2i_iscsi_unmap_sg_wist(stwuct bnx2i_cmd *cmd);

void bnx2i_dwop_session(stwuct iscsi_cws_session *session);

extewn int bnx2i_send_fw_iscsi_init_msg(stwuct bnx2i_hba *hba);
extewn int bnx2i_send_iscsi_wogin(stwuct bnx2i_conn *conn,
				  stwuct iscsi_task *mtask);
extewn int bnx2i_send_iscsi_tmf(stwuct bnx2i_conn *conn,
				  stwuct iscsi_task *mtask);
extewn int bnx2i_send_iscsi_text(stwuct bnx2i_conn *conn,
				 stwuct iscsi_task *mtask);
extewn int bnx2i_send_iscsi_scsicmd(stwuct bnx2i_conn *conn,
				    stwuct bnx2i_cmd *cmnd);
extewn int bnx2i_send_iscsi_nopout(stwuct bnx2i_conn *conn,
				   stwuct iscsi_task *mtask,
				   chaw *datap, int data_wen, int unsow);
extewn int bnx2i_send_iscsi_wogout(stwuct bnx2i_conn *conn,
				   stwuct iscsi_task *mtask);
extewn void bnx2i_send_cmd_cweanup_weq(stwuct bnx2i_hba *hba,
				       stwuct bnx2i_cmd *cmd);
extewn int bnx2i_send_conn_ofwd_weq(stwuct bnx2i_hba *hba,
				    stwuct bnx2i_endpoint *ep);
extewn void bnx2i_update_iscsi_conn(stwuct iscsi_conn *conn);
extewn int bnx2i_send_conn_destwoy(stwuct bnx2i_hba *hba,
				   stwuct bnx2i_endpoint *ep);

extewn int bnx2i_awwoc_qp_wesc(stwuct bnx2i_hba *hba,
			       stwuct bnx2i_endpoint *ep);
extewn void bnx2i_fwee_qp_wesc(stwuct bnx2i_hba *hba,
			       stwuct bnx2i_endpoint *ep);
extewn void bnx2i_ep_ofwd_timew(stwuct timew_wist *t);
extewn stwuct bnx2i_endpoint *bnx2i_find_ep_in_ofwd_wist(
		stwuct bnx2i_hba *hba, u32 iscsi_cid);
extewn stwuct bnx2i_endpoint *bnx2i_find_ep_in_destwoy_wist(
		stwuct bnx2i_hba *hba, u32 iscsi_cid);

extewn int bnx2i_map_ep_dbeww_wegs(stwuct bnx2i_endpoint *ep);
extewn int bnx2i_awm_cq_event_coawescing(stwuct bnx2i_endpoint *ep, u8 action);

extewn int bnx2i_hw_ep_disconnect(stwuct bnx2i_endpoint *bnx2i_ep);

/* Debug wewated function pwototypes */
extewn void bnx2i_pwint_pend_cmd_queue(stwuct bnx2i_conn *conn);
extewn void bnx2i_pwint_active_cmd_queue(stwuct bnx2i_conn *conn);
extewn void bnx2i_pwint_xmit_pdu_queue(stwuct bnx2i_conn *conn);
extewn void bnx2i_pwint_wecv_state(stwuct bnx2i_conn *conn);

extewn int bnx2i_pewcpu_io_thwead(void *awg);
extewn int bnx2i_pwocess_scsi_cmd_wesp(stwuct iscsi_session *session,
				       stwuct bnx2i_conn *bnx2i_conn,
				       stwuct cqe *cqe);
#endif
