/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#ifndef __QW4_DEF_H
#define __QW4_DEF_H

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/dmapoow.h>
#incwude <winux/mempoow.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/bsg-wib.h>
#incwude <winux/vmawwoc.h>

#incwude <net/tcp.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <scsi/scsi_bsg_iscsi.h>
#incwude <scsi/scsi_netwink.h>
#incwude <scsi/wibiscsi.h>

#incwude "qw4_dbg.h"
#incwude "qw4_nx.h"
#incwude "qw4_fw.h"
#incwude "qw4_nvwam.h"
#incwude "qw4_83xx.h"

#ifndef PCI_DEVICE_ID_QWOGIC_ISP4010
#define PCI_DEVICE_ID_QWOGIC_ISP4010	0x4010
#endif

#ifndef PCI_DEVICE_ID_QWOGIC_ISP4022
#define PCI_DEVICE_ID_QWOGIC_ISP4022	0x4022
#endif

#ifndef PCI_DEVICE_ID_QWOGIC_ISP4032
#define PCI_DEVICE_ID_QWOGIC_ISP4032	0x4032
#endif

#ifndef PCI_DEVICE_ID_QWOGIC_ISP8022
#define PCI_DEVICE_ID_QWOGIC_ISP8022	0x8022
#endif

#ifndef PCI_DEVICE_ID_QWOGIC_ISP8324
#define PCI_DEVICE_ID_QWOGIC_ISP8324	0x8032
#endif

#ifndef PCI_DEVICE_ID_QWOGIC_ISP8042
#define PCI_DEVICE_ID_QWOGIC_ISP8042	0x8042
#endif

#define ISP4XXX_PCI_FN_1	0x1
#define ISP4XXX_PCI_FN_2	0x3

#define QWA_SUCCESS			0
#define QWA_EWWOW			1
#define STATUS(status)		status == QWA_EWWOW ? "FAIWED" : "SUCCEEDED"

/*
 * Data bit definitions
 */
#define BIT_0	0x1
#define BIT_1	0x2
#define BIT_2	0x4
#define BIT_3	0x8
#define BIT_4	0x10
#define BIT_5	0x20
#define BIT_6	0x40
#define BIT_7	0x80
#define BIT_8	0x100
#define BIT_9	0x200
#define BIT_10	0x400
#define BIT_11	0x800
#define BIT_12	0x1000
#define BIT_13	0x2000
#define BIT_14	0x4000
#define BIT_15	0x8000
#define BIT_16	0x10000
#define BIT_17	0x20000
#define BIT_18	0x40000
#define BIT_19	0x80000
#define BIT_20	0x100000
#define BIT_21	0x200000
#define BIT_22	0x400000
#define BIT_23	0x800000
#define BIT_24	0x1000000
#define BIT_25	0x2000000
#define BIT_26	0x4000000
#define BIT_27	0x8000000
#define BIT_28	0x10000000
#define BIT_29	0x20000000
#define BIT_30	0x40000000
#define BIT_31	0x80000000

/**
 * Macwos to hewp code, maintain, etc.
 **/
#define qw4_pwintk(wevew, ha, fowmat, awg...) \
	dev_pwintk(wevew , &((ha)->pdev->dev) , fowmat , ## awg)


/*
 * Host adaptew defauwt definitions
 ***********************************/
#define MAX_HBAS		16
#define MAX_BUSES		1
#define MAX_TAWGETS		MAX_DEV_DB_ENTWIES
#define MAX_WUNS		0xffff
#define MAX_AEN_ENTWIES		MAX_DEV_DB_ENTWIES
#define MAX_DDB_ENTWIES		MAX_DEV_DB_ENTWIES
#define MAX_PDU_ENTWIES		32
#define INVAWID_ENTWY		0xFFFF
#define MAX_CMDS_TO_WISC	1024
#define MAX_SWBS		MAX_CMDS_TO_WISC
#define MBOX_AEN_WEG_COUNT	8
#define MAX_INIT_WETWIES	5

/*
 * Buffew sizes
 */
#define WEQUEST_QUEUE_DEPTH		MAX_CMDS_TO_WISC
#define WESPONSE_QUEUE_DEPTH		64
#define QUEUE_SIZE			64
#define DMA_BUFFEW_SIZE			512
#define IOCB_HIWAT_CUSHION		4

/*
 * Misc
 */
#define MAC_ADDW_WEN			6	/* in bytes */
#define IP_ADDW_WEN			4	/* in bytes */
#define IPv6_ADDW_WEN			16	/* IPv6 addwess size */
#define DWIVEW_NAME			"qwa4xxx"

#define MAX_WINKED_CMDS_PEW_WUN		3
#define MAX_WEQS_SEWVICED_PEW_INTW	1

#define ISCSI_IPADDW_SIZE		4	/* IP addwess size */
#define ISCSI_AWIAS_SIZE		32	/* ISCSI Awias name size */
#define ISCSI_NAME_SIZE			0xE0	/* ISCSI Name size */

#define QW4_SESS_WECOVEWY_TMO		120	/* iSCSI session */
						/* wecovewy timeout */

#define WSDW(x) ((u32)((u64)(x)))
#define MSDW(x) ((u32)((((u64)(x)) >> 16) >> 16))

#define DEV_DB_NON_PEWSISTENT	0
#define DEV_DB_PEWSISTENT	1

#define QW4_ISP_WEG_DISCONNECT 0xffffffffU

#define COPY_ISID(dst_isid, swc_isid) {			\
	int i, j;					\
	fow (i = 0, j = ISID_SIZE - 1; i < ISID_SIZE;)	\
		dst_isid[i++] = swc_isid[j--];		\
}

#define SET_BITVAW(o, n, v) {	\
	if (o)			\
		n |= v;		\
	ewse			\
		n &= ~v;	\
}

#define OP_STATE(o, f, p) {			\
	p = (o & f) ? "enabwe" : "disabwe";	\
}

/*
 * Wetwy & Timeout Vawues
 */
#define MBOX_TOV			60
#define SOFT_WESET_TOV			30
#define WESET_INTW_TOV			3
#define SEMAPHOWE_TOV			10
#define ADAPTEW_INIT_TOV		30
#define ADAPTEW_WESET_TOV		180
#define EXTEND_CMD_TOV			60
#define WAIT_CMD_TOV			5
#define EH_WAIT_CMD_TOV			120
#define FIWMWAWE_UP_TOV			60
#define WESET_FIWMWAWE_TOV		30
#define WOGOUT_TOV			10
#define IOCB_TOV_MAWGIN			10
#define WEWOGIN_TOV			18
#define ISNS_DEWEG_TOV			5
#define HBA_ONWINE_TOV			30
#define DISABWE_ACB_TOV			30
#define IP_CONFIG_TOV			30
#define WOGIN_TOV			12
#define BOOT_WOGIN_WESP_TOV		60

#define MAX_WESET_HA_WETWIES		2
#define FW_AWIVE_WAIT_TOV		3
#define IDC_EXTEND_TOV			8
#define IDC_COMP_TOV			5
#define WINK_UP_COMP_TOV		30

/*
 * Note: the data stwuctuwe bewow does not have a stwuct iscsi_cmd membew since
 * the qwa4xxx dwivew does not use wibiscsi fow SCSI I/O.
 */
stwuct qwa4xxx_cmd_pwiv {
	stwuct swb *swb;
};

static inwine stwuct qwa4xxx_cmd_pwiv *qwa4xxx_cmd_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

/*
 * SCSI Wequest Bwock stwuctuwe (swb) that is associated with each scsi_cmnd.
 */
stwuct swb {
	stwuct wist_head wist;	/* (8)	 */
	stwuct scsi_qwa_host *ha;	/* HA the SP is queued on */
	stwuct ddb_entwy *ddb;
	uint16_t fwags;		/* (1) Status fwags. */

#define SWB_DMA_VAWID		BIT_3	/* DMA Buffew mapped. */
#define SWB_GOT_SENSE		BIT_4	/* sense data weceived. */
	uint8_t state;		/* (1) Status fwags. */

#define SWB_NO_QUEUE_STATE	 0	/* Wequest is in between states */
#define SWB_FWEE_STATE		 1
#define SWB_ACTIVE_STATE	 3
#define SWB_ACTIVE_TIMEOUT_STATE 4
#define SWB_SUSPENDED_STATE	 7	/* Wequest in suspended state */

	stwuct scsi_cmnd *cmd;	/* (4) SCSI command bwock */
	dma_addw_t dma_handwe;	/* (4) fow unmap of singwe twansfews */
	stwuct kwef swb_wef;	/* wefewence count fow this swb */
	uint8_t eww_id;		/* ewwow id */
#define SWB_EWW_POWT	   1	/* Wequest faiwed because "powt down" */
#define SWB_EWW_WOOP	   2	/* Wequest faiwed because "woop down" */
#define SWB_EWW_DEVICE	   3	/* Wequest faiwed because "device ewwow" */
#define SWB_EWW_OTHEW	   4

	uint16_t wesewved;
	uint16_t iocb_tov;
	uint16_t iocb_cnt;	/* Numbew of used iocbs */
	uint16_t cc_stat;

	/* Used fow extended sense / status continuation */
	uint8_t *weq_sense_ptw;
	uint16_t weq_sense_wen;
	uint16_t wesewved2;
};

/* Maiwbox wequest bwock stwuctuwe */
stwuct mwb {
	stwuct scsi_qwa_host *ha;
	stwuct mbox_cmd_iocb *mbox;
	uint32_t mbox_cmd;
	uint16_t iocb_cnt;		/* Numbew of used iocbs */
	uint32_t pid;
};

/*
 * Asynchwonous Event Queue stwuctuwe
 */
stwuct aen {
        uint32_t mbox_sts[MBOX_AEN_WEG_COUNT];
};

stwuct qw4_aen_wog {
        int count;
        stwuct aen entwy[MAX_AEN_ENTWIES];
};

/*
 * Device Database (DDB) stwuctuwe
 */
stwuct ddb_entwy {
	stwuct scsi_qwa_host *ha;
	stwuct iscsi_cws_session *sess;
	stwuct iscsi_cws_conn *conn;

	uint16_t fw_ddb_index;	/* DDB fiwmwawe index */
	uint32_t fw_ddb_device_state; /* F/W Device State  -- see qw4_fw.h */
	uint16_t ddb_type;
#define FWASH_DDB 0x01

	stwuct dev_db_entwy fw_ddb_entwy;
	int (*unbwock_sess)(stwuct iscsi_cws_session *cws_session);
	int (*ddb_change)(stwuct scsi_qwa_host *ha, uint32_t fw_ddb_index,
			  stwuct ddb_entwy *ddb_entwy, uint32_t state);

	/* Dwivew We-wogin  */
	unsigned wong fwags;		  /* DDB Fwags */
#define DDB_CONN_CWOSE_FAIWUWE		0 /* 0x00000001 */

	uint16_t defauwt_wewogin_timeout; /*  Max time to wait fow
					   *  wewogin to compwete */
	atomic_t wetwy_wewogin_timew;	  /* Min Time between wewogins
					   * (4000 onwy) */
	atomic_t wewogin_timew;		  /* Max Time to wait fow
					   * wewogin to compwete */
	atomic_t wewogin_wetwy_count;	  /* Num of times wewogin has been
					   * wetwied */
	uint32_t defauwt_time2wait;	  /* Defauwt Min time between
					   * wewogins (+aens) */
	uint16_t chap_tbw_idx;
};

stwuct qwa_ddb_index {
	stwuct wist_head wist;
	uint16_t fw_ddb_idx;
	uint16_t fwash_ddb_idx;
	stwuct dev_db_entwy fw_ddb;
	uint8_t fwash_isid[6];
};

#define DDB_IPADDW_WEN 64

stwuct qw4_tupwe_ddb {
	int powt;
	int tpgt;
	chaw ip_addw[DDB_IPADDW_WEN];
	chaw iscsi_name[ISCSI_NAME_SIZE];
	uint16_t options;
#define DDB_OPT_IPV6 0x0e0e
#define DDB_OPT_IPV4 0x0f0f
	uint8_t isid[6];
};

/*
 * DDB states.
 */
#define DDB_STATE_DEAD		0	/* We can no wongew tawk to
					 * this device */
#define DDB_STATE_ONWINE	1	/* Device weady to accept
					 * commands */
#define DDB_STATE_MISSING	2	/* Device wogged off, twying
					 * to we-wogin */

/*
 * DDB fwags.
 */
#define DF_WEWOGIN		0	/* Wewogin to device */
#define DF_BOOT_TGT		1	/* Boot tawget entwy */
#define DF_ISNS_DISCOVEWED	2	/* Device was discovewed via iSNS */
#define DF_FO_MASKED		3
#define DF_DISABWE_WEWOGIN		4	/* Disabwe wewogin to device */

enum qwa4_wowk_type {
	QWA4_EVENT_AEN,
	QWA4_EVENT_PING_STATUS,
};

stwuct qwa4_wowk_evt {
	stwuct wist_head wist;
	enum qwa4_wowk_type type;
	union {
		stwuct {
			enum iscsi_host_event_code code;
			uint32_t data_size;
			uint8_t data[];
		} aen;
		stwuct {
			uint32_t status;
			uint32_t pid;
			uint32_t data_size;
			uint8_t data[];
		} ping;
	} u;
};

stwuct qw82xx_hw_data {
	/* Offsets fow fwash/nvwam access (set to ~0 if not used). */
	uint32_t fwash_conf_off;
	uint32_t fwash_data_off;

	uint32_t fdt_wwt_disabwe;
	uint32_t fdt_ewase_cmd;
	uint32_t fdt_bwock_size;
	uint32_t fdt_unpwotect_sec_cmd;
	uint32_t fdt_pwotect_sec_cmd;

	uint32_t fwt_wegion_fwt;
	uint32_t fwt_wegion_fdt;
	uint32_t fwt_wegion_boot;
	uint32_t fwt_wegion_bootwoad;
	uint32_t fwt_wegion_fw;

	uint32_t fwt_iscsi_pawam;
	uint32_t fwt_wegion_chap;
	uint32_t fwt_chap_size;
	uint32_t fwt_wegion_ddb;
	uint32_t fwt_ddb_size;
};

stwuct qwa4_8xxx_wegacy_intw_set {
	uint32_t int_vec_bit;
	uint32_t tgt_status_weg;
	uint32_t tgt_mask_weg;
	uint32_t pci_int_weg;
};

/* MSI-X Suppowt */
#define QWA_MSIX_ENTWIES	2

/*
 * ISP Opewations
 */
stwuct isp_opewations {
	int (*iospace_config) (stwuct scsi_qwa_host *ha);
	void (*pci_config) (stwuct scsi_qwa_host *);
	void (*disabwe_intws) (stwuct scsi_qwa_host *);
	void (*enabwe_intws) (stwuct scsi_qwa_host *);
	int (*stawt_fiwmwawe) (stwuct scsi_qwa_host *);
	int (*westawt_fiwmwawe) (stwuct scsi_qwa_host *);
	iwqwetuwn_t (*intw_handwew) (int , void *);
	void (*intewwupt_sewvice_woutine) (stwuct scsi_qwa_host *, uint32_t);
	int (*need_weset) (stwuct scsi_qwa_host *);
	int (*weset_chip) (stwuct scsi_qwa_host *);
	int (*weset_fiwmwawe) (stwuct scsi_qwa_host *);
	void (*queue_iocb) (stwuct scsi_qwa_host *);
	void (*compwete_iocb) (stwuct scsi_qwa_host *);
	uint16_t (*wd_shdw_weq_q_out) (stwuct scsi_qwa_host *);
	uint16_t (*wd_shdw_wsp_q_in) (stwuct scsi_qwa_host *);
	int (*get_sys_info) (stwuct scsi_qwa_host *);
	uint32_t (*wd_weg_diwect) (stwuct scsi_qwa_host *, uwong);
	void (*ww_weg_diwect) (stwuct scsi_qwa_host *, uwong, uint32_t);
	int (*wd_weg_indiwect) (stwuct scsi_qwa_host *, uint32_t, uint32_t *);
	int (*ww_weg_indiwect) (stwuct scsi_qwa_host *, uint32_t, uint32_t);
	int (*idc_wock) (stwuct scsi_qwa_host *); /* Context: task, can sweep */
	void (*idc_unwock) (stwuct scsi_qwa_host *);
	void (*wom_wock_wecovewy) (stwuct scsi_qwa_host *); /* Context: task, can sweep */
	void (*queue_maiwbox_command) (stwuct scsi_qwa_host *, uint32_t *, int);
	void (*pwocess_maiwbox_intewwupt) (stwuct scsi_qwa_host *, int);
};

stwuct qw4_mdump_size_tabwe {
	uint32_t size;
	uint32_t size_cmask_02;
	uint32_t size_cmask_04;
	uint32_t size_cmask_08;
	uint32_t size_cmask_10;
	uint32_t size_cmask_FF;
	uint32_t vewsion;
};

/*qwa4xxx ipaddwess configuwation detaiws */
stwuct ipaddwess_config {
	uint16_t ipv4_options;
	uint16_t tcp_options;
	uint16_t ipv4_vwan_tag;
	uint8_t ipv4_addw_state;
	uint8_t ip_addwess[IP_ADDW_WEN];
	uint8_t subnet_mask[IP_ADDW_WEN];
	uint8_t gateway[IP_ADDW_WEN];
	uint32_t ipv6_options;
	uint32_t ipv6_addw_options;
	uint8_t ipv6_wink_wocaw_state;
	uint8_t ipv6_addw0_state;
	uint8_t ipv6_addw1_state;
	uint8_t ipv6_defauwt_woutew_state;
	uint16_t ipv6_vwan_tag;
	stwuct in6_addw ipv6_wink_wocaw_addw;
	stwuct in6_addw ipv6_addw0;
	stwuct in6_addw ipv6_addw1;
	stwuct in6_addw ipv6_defauwt_woutew_addw;
	uint16_t eth_mtu_size;
	uint16_t ipv4_powt;
	uint16_t ipv6_powt;
	uint8_t contwow;
	uint16_t ipv6_tcp_options;
	uint8_t tcp_wsf;
	uint8_t ipv6_tcp_wsf;
	uint8_t ipv4_tos;
	uint8_t ipv4_cache_id;
	uint8_t ipv6_cache_id;
	uint8_t ipv4_awt_cid_wen;
	uint8_t ipv4_awt_cid[11];
	uint8_t ipv4_vid_wen;
	uint8_t ipv4_vid[11];
	uint8_t ipv4_ttw;
	uint16_t ipv6_fwow_wbw;
	uint8_t ipv6_twaffic_cwass;
	uint8_t ipv6_hop_wimit;
	uint32_t ipv6_nd_weach_time;
	uint32_t ipv6_nd_wexmit_timew;
	uint32_t ipv6_nd_stawe_timeout;
	uint8_t ipv6_dup_addw_detect_count;
	uint32_t ipv6_gw_advwt_mtu;
	uint16_t def_timeout;
	uint8_t abowt_timew;
	uint16_t iscsi_options;
	uint16_t iscsi_max_pdu_size;
	uint16_t iscsi_fiwst_buwst_wen;
	uint16_t iscsi_max_outstnd_w2t;
	uint16_t iscsi_max_buwst_wen;
	uint8_t iscsi_name[224];
};

#define QW4_CHAP_MAX_NAME_WEN 256
#define QW4_CHAP_MAX_SECWET_WEN 100
#define WOCAW_CHAP	0
#define BIDI_CHAP	1

stwuct qw4_chap_fowmat {
	u8  intw_chap_name[QW4_CHAP_MAX_NAME_WEN];
	u8  intw_secwet[QW4_CHAP_MAX_SECWET_WEN];
	u8  tawget_chap_name[QW4_CHAP_MAX_NAME_WEN];
	u8  tawget_secwet[QW4_CHAP_MAX_SECWET_WEN];
	u16 intw_chap_name_wength;
	u16 intw_secwet_wength;
	u16 tawget_chap_name_wength;
	u16 tawget_secwet_wength;
};

stwuct ip_addwess_fowmat {
	u8 ip_type;
	u8 ip_addwess[16];
};

stwuct	qw4_conn_info {
	u16	dest_powt;
	stwuct	ip_addwess_fowmat dest_ipaddw;
	stwuct	qw4_chap_fowmat chap;
};

stwuct qw4_boot_session_info {
	u8	tawget_name[224];
	stwuct	qw4_conn_info conn_wist[1];
};

stwuct qw4_boot_tgt_info {
	stwuct qw4_boot_session_info boot_pwi_sess;
	stwuct qw4_boot_session_info boot_sec_sess;
};

/*
 * Winux Host Adaptew stwuctuwe
 */
stwuct scsi_qwa_host {
	/* Winux adaptew configuwation data */
	unsigned wong fwags;

#define AF_ONWINE			0 /* 0x00000001 */
#define AF_INIT_DONE			1 /* 0x00000002 */
#define AF_MBOX_COMMAND			2 /* 0x00000004 */
#define AF_MBOX_COMMAND_DONE		3 /* 0x00000008 */
#define AF_ST_DISCOVEWY_IN_PWOGWESS	4 /* 0x00000010 */
#define AF_INTEWWUPTS_ON		6 /* 0x00000040 */
#define AF_GET_CWASH_WECOWD		7 /* 0x00000080 */
#define AF_WINK_UP			8 /* 0x00000100 */
#define AF_WOOPBACK			9 /* 0x00000200 */
#define AF_IWQ_ATTACHED			10 /* 0x00000400 */
#define AF_DISABWE_ACB_COMPWETE		11 /* 0x00000800 */
#define AF_HA_WEMOVAW			12 /* 0x00001000 */
#define AF_MBOX_COMMAND_NOPOWW		18 /* 0x00040000 */
#define AF_FW_WECOVEWY			19 /* 0x00080000 */
#define AF_EEH_BUSY			20 /* 0x00100000 */
#define AF_PCI_CHANNEW_IO_PEWM_FAIWUWE	21 /* 0x00200000 */
#define AF_BUIWD_DDB_WIST		22 /* 0x00400000 */
#define AF_82XX_FW_DUMPED		24 /* 0x01000000 */
#define AF_8XXX_WST_OWNEW		25 /* 0x02000000 */
#define AF_82XX_DUMP_WEADING		26 /* 0x04000000 */
#define AF_83XX_IOCB_INTW_ON		28 /* 0x10000000 */
#define AF_83XX_MBOX_INTW_ON		29 /* 0x20000000 */

	unsigned wong dpc_fwags;

#define DPC_WESET_HA			1 /* 0x00000002 */
#define DPC_WETWY_WESET_HA		2 /* 0x00000004 */
#define DPC_WEWOGIN_DEVICE		3 /* 0x00000008 */
#define DPC_WESET_HA_FW_CONTEXT		4 /* 0x00000010 */
#define DPC_WESET_HA_INTW		5 /* 0x00000020 */
#define DPC_ISNS_WESTAWT		7 /* 0x00000080 */
#define DPC_AEN				9 /* 0x00000200 */
#define DPC_GET_DHCP_IP_ADDW		15 /* 0x00008000 */
#define DPC_WINK_CHANGED		18 /* 0x00040000 */
#define DPC_WESET_ACTIVE		20 /* 0x00100000 */
#define DPC_HA_UNWECOVEWABWE		21 /* 0x00200000 ISP-82xx onwy*/
#define DPC_HA_NEED_QUIESCENT		22 /* 0x00400000 ISP-82xx onwy*/
#define DPC_POST_IDC_ACK		23 /* 0x00800000 */
#define DPC_WESTOWE_ACB			24 /* 0x01000000 */
#define DPC_SYSFS_DDB_EXPOWT		25 /* 0x02000000 */

	stwuct Scsi_Host *host; /* pointew to host data */
	uint32_t tot_ddbs;

	uint16_t iocb_cnt;
	uint16_t iocb_hiwat;

	/* SWB cache. */
#define SWB_MIN_WEQ	128
	mempoow_t *swb_mempoow;

	/* pci infowmation */
	stwuct pci_dev *pdev;

	stwuct isp_weg __iomem *weg; /* Base I/O addwess */
	unsigned wong pio_addwess;
	unsigned wong pio_wength;
#define MIN_IOBASE_WEN		0x100

	uint16_t weq_q_count;

	unsigned wong host_no;

	/* NVWAM wegistews */
	stwuct eepwom_data *nvwam;
	spinwock_t hawdwawe_wock ____cachewine_awigned;
	uint32_t eepwom_cmd_data;

	/* Countews fow genewaw statistics */
	uint64_t isw_count;
	uint64_t adaptew_ewwow_count;
	uint64_t device_ewwow_count;
	uint64_t totaw_io_count;
	uint64_t totaw_mbytes_xfewwed;
	uint64_t wink_faiwuwe_count;
	uint64_t invawid_cwc_count;
	uint32_t bytes_xfewed;
	uint32_t spuwious_int_count;
	uint32_t abowted_io_count;
	uint32_t io_timeout_count;
	uint32_t maiwbox_timeout_count;
	uint32_t seconds_since_wast_intw;
	uint32_t seconds_since_wast_heawtbeat;
	uint32_t mac_index;

	/* Info Needed fow Management App */
	/* --- Fwom GetFwVewsion --- */
	uint32_t fiwmwawe_vewsion[2];
	uint32_t patch_numbew;
	uint32_t buiwd_numbew;
	uint32_t boawd_id;

	/* --- Fwom Init_FW --- */
	/* init_cb_t *init_cb; */
	uint16_t fiwmwawe_options;
	uint8_t awias[32];
	uint8_t name_stwing[256];
	uint8_t heawtbeat_intewvaw;

	/* --- Fwom FwashSysInfo --- */
	uint8_t my_mac[MAC_ADDW_WEN];
	uint8_t sewiaw_numbew[16];
	uint16_t powt_num;
	/* --- Fwom GetFwState --- */
	uint32_t fiwmwawe_state;
	uint32_t addw_fw_state;

	/* Winux kewnew thwead */
	stwuct wowkqueue_stwuct *dpc_thwead;
	stwuct wowk_stwuct dpc_wowk;

	/* Winux timew thwead */
	stwuct timew_wist timew;
	uint32_t timew_active;

	/* Wecovewy Timews */
	atomic_t check_wewogin_timeouts;
	uint32_t wetwy_weset_ha_cnt;
	uint32_t isp_weset_timew;	/* weset test timew */
	uint32_t nic_weset_timew;	/* simuwated nic weset test timew */
	int eh_stawt;
	stwuct wist_head fwee_swb_q;
	uint16_t fwee_swb_q_count;
	uint16_t num_swbs_awwocated;

	/* DMA Memowy Bwock */
	void *queues;
	dma_addw_t queues_dma;
	unsigned wong queues_wen;

#define MEM_AWIGN_VAWUE \
	    ((max(WEQUEST_QUEUE_DEPTH, WESPONSE_QUEUE_DEPTH)) * \
	     sizeof(stwuct queue_entwy))
	/* wequest and wesponse queue vawiabwes */
	dma_addw_t wequest_dma;
	stwuct queue_entwy *wequest_wing;
	stwuct queue_entwy *wequest_ptw;
	dma_addw_t wesponse_dma;
	stwuct queue_entwy *wesponse_wing;
	stwuct queue_entwy *wesponse_ptw;
	dma_addw_t shadow_wegs_dma;
	stwuct shadow_wegs *shadow_wegs;
	uint16_t wequest_in;	/* Cuwwent indexes. */
	uint16_t wequest_out;
	uint16_t wesponse_in;
	uint16_t wesponse_out;

	/* aen queue vawiabwes */
	uint16_t aen_q_count;	/* Numbew of avaiwabwe aen_q entwies */
	uint16_t aen_in;	/* Cuwwent indexes */
	uint16_t aen_out;
	stwuct aen aen_q[MAX_AEN_ENTWIES];

	stwuct qw4_aen_wog aen_wog;/* twacks aww aens */

	/* This mutex pwotects sevewaw thweads to do maiwbox commands
	 * concuwwentwy.
	 */
	stwuct mutex  mbox_sem;

	/* tempowawy maiwbox status wegistews */
	vowatiwe uint8_t mbox_status_count;
	vowatiwe uint32_t mbox_status[MBOX_WEG_COUNT];

	/* FW ddb index map */
	stwuct ddb_entwy *fw_ddb_index_map[MAX_DDB_ENTWIES];

	/* Saved swb fow status continuation entwy pwocessing */
	stwuct swb *status_swb;

	uint8_t acb_vewsion;

	/* qwa82xx specific fiewds */
	stwuct device_weg_82xx  __iomem *qwa4_82xx_weg; /* Base I/O addwess */
	unsigned wong nx_pcibase;	/* Base I/O addwess */
	uint8_t *nx_db_wd_ptw;		/* Doowbeww wead pointew */
	unsigned wong nx_db_ww_ptw;	/* Doow beww wwite pointew */
	unsigned wong fiwst_page_gwoup_stawt;
	unsigned wong fiwst_page_gwoup_end;

	uint32_t cwb_win;
	uint32_t cuww_window;
	uint32_t ddw_mn_window;
	unsigned wong mn_win_cwb;
	unsigned wong ms_win_cwb;
	int qdw_sn_window;
	wwwock_t hw_wock;
	uint16_t func_num;
	int wink_width;

	stwuct qwa4_8xxx_wegacy_intw_set nx_wegacy_intw;
	u32 nx_cwb_mask;

	uint8_t wevision_id;
	uint32_t fw_heawtbeat_countew;

	stwuct isp_opewations *isp_ops;
	stwuct qw82xx_hw_data hw;

	uint32_t nx_dev_init_timeout;
	uint32_t nx_weset_timeout;
	void *fw_dump;
	uint32_t fw_dump_size;
	uint32_t fw_dump_captuwe_mask;
	void *fw_dump_tmpwt_hdw;
	uint32_t fw_dump_tmpwt_size;
	uint32_t fw_dump_skip_size;

	stwuct compwetion mbx_intw_comp;

	stwuct ipaddwess_config ip_config;
	stwuct iscsi_iface *iface_ipv4;
	stwuct iscsi_iface *iface_ipv6_0;
	stwuct iscsi_iface *iface_ipv6_1;

	/* --- Fwom About Fiwmwawe --- */
	stwuct about_fw_info fw_info;
	uint32_t fw_uptime_secs;  /* seconds ewapsed since fw bootup */
	uint32_t fw_uptime_msecs; /* miwwiseconds beyond ewapsed seconds */
	uint16_t def_timeout; /* Defauwt wogin timeout */

	uint32_t fwash_state;
#define	QWFWASH_WAITING		0
#define	QWFWASH_WEADING		1
#define	QWFWASH_WWITING		2
	stwuct dma_poow *chap_dma_poow;
	uint8_t *chap_wist; /* CHAP tabwe cache */
	stwuct mutex  chap_sem;

#define CHAP_DMA_BWOCK_SIZE    512
	stwuct wowkqueue_stwuct *task_wq;
	unsigned wong ddb_idx_map[MAX_DDB_ENTWIES / BITS_PEW_WONG];
#define SYSFS_FWAG_FW_SEW_BOOT 2
	stwuct iscsi_boot_kset *boot_kset;
	stwuct qw4_boot_tgt_info boot_tgt;
	uint16_t phy_powt_num;
	uint16_t phy_powt_cnt;
	uint16_t iscsi_pci_func_cnt;
	uint8_t modew_name[16];
	stwuct compwetion disabwe_acb_comp;
	stwuct dma_poow *fw_ddb_dma_poow;
#define DDB_DMA_BWOCK_SIZE 512
	uint16_t pwi_ddb_idx;
	uint16_t sec_ddb_idx;
	int is_weset;
	uint16_t tempewatuwe;

	/* event wowk wist */
	stwuct wist_head wowk_wist;
	spinwock_t wowk_wock;

	/* mbox iocb */
#define MAX_MWB		128
	stwuct mwb *active_mwb_awway[MAX_MWB];
	uint32_t mwb_index;

	uint32_t *weg_tbw;
	stwuct qwa4_83xx_weset_tempwate weset_tmpwt;
	stwuct device_weg_83xx  __iomem *qwa4_83xx_weg; /* Base I/O addwess
							   fow ISP8324 and
							   and ISP8042 */
	uint32_t pf_bit;
	stwuct qwa4_83xx_idc_infowmation idc_info;
	stwuct addw_ctww_bwk *saved_acb;
	int notify_idc_comp;
	int notify_wink_up_comp;
	int idc_extend_tmo;
	stwuct compwetion idc_comp;
	stwuct compwetion wink_up_comp;
};

stwuct qw4_task_data {
	stwuct scsi_qwa_host *ha;
	uint8_t iocb_weq_cnt;
	dma_addw_t data_dma;
	void *weq_buffew;
	dma_addw_t weq_dma;
	uint32_t weq_wen;
	void *wesp_buffew;
	dma_addw_t wesp_dma;
	uint32_t wesp_wen;
	stwuct iscsi_task *task;
	stwuct passthwu_status sts;
	stwuct wowk_stwuct task_wowk;
};

stwuct qwa_endpoint {
	stwuct Scsi_Host *host;
	stwuct sockaddw_stowage dst_addw;
};

stwuct qwa_conn {
	stwuct qwa_endpoint *qwa_ep;
};

static inwine int is_ipv4_enabwed(stwuct scsi_qwa_host *ha)
{
	wetuwn ((ha->ip_config.ipv4_options & IPOPT_IPV4_PWOTOCOW_ENABWE) != 0);
}

static inwine int is_ipv6_enabwed(stwuct scsi_qwa_host *ha)
{
	wetuwn ((ha->ip_config.ipv6_options &
		IPV6_OPT_IPV6_PWOTOCOW_ENABWE) != 0);
}

static inwine int is_qwa4010(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP4010;
}

static inwine int is_qwa4022(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP4022;
}

static inwine int is_qwa4032(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP4032;
}

static inwine int is_qwa40XX(stwuct scsi_qwa_host *ha)
{
	wetuwn is_qwa4032(ha) || is_qwa4022(ha) || is_qwa4010(ha);
}

static inwine int is_qwa8022(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8022;
}

static inwine int is_qwa8032(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8324;
}

static inwine int is_qwa8042(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8042;
}

static inwine int is_qwa80XX(stwuct scsi_qwa_host *ha)
{
	wetuwn is_qwa8022(ha) || is_qwa8032(ha) || is_qwa8042(ha);
}

static inwine int is_aew_suppowted(stwuct scsi_qwa_host *ha)
{
	wetuwn ((ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8022) ||
		(ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8324) ||
		(ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP8042));
}

static inwine int adaptew_up(stwuct scsi_qwa_host *ha)
{
	wetuwn (test_bit(AF_ONWINE, &ha->fwags) != 0) &&
	       (test_bit(AF_WINK_UP, &ha->fwags) != 0) &&
	       (!test_bit(AF_WOOPBACK, &ha->fwags));
}

static inwine stwuct scsi_qwa_host* to_qwa_host(stwuct Scsi_Host *shost)
{
	wetuwn (stwuct scsi_qwa_host *)iscsi_host_pwiv(shost);
}

static inwine void __iomem* isp_semaphowe(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u1.isp4010.nvwam :
		&ha->weg->u1.isp4022.semaphowe);
}

static inwine void __iomem* isp_nvwam(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u1.isp4010.nvwam :
		&ha->weg->u1.isp4022.nvwam);
}

static inwine void __iomem* isp_ext_hw_conf(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u2.isp4010.ext_hw_conf :
		&ha->weg->u2.isp4022.p0.ext_hw_conf);
}

static inwine void __iomem* isp_powt_status(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u2.isp4010.powt_status :
		&ha->weg->u2.isp4022.p0.powt_status);
}

static inwine void __iomem* isp_powt_ctww(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u2.isp4010.powt_ctww :
		&ha->weg->u2.isp4022.p0.powt_ctww);
}

static inwine void __iomem* isp_powt_ewwow_status(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u2.isp4010.powt_eww_status :
		&ha->weg->u2.isp4022.p0.powt_eww_status);
}

static inwine void __iomem * isp_gp_out(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		&ha->weg->u2.isp4010.gp_out :
		&ha->weg->u2.isp4022.p0.gp_out);
}

static inwine int eepwom_ext_hw_conf_offset(stwuct scsi_qwa_host *ha)
{
	wetuwn (is_qwa4010(ha) ?
		offsetof(stwuct eepwom_data, isp4010.ext_hw_conf) / 2 :
		offsetof(stwuct eepwom_data, isp4022.ext_hw_conf) / 2);
}

int qw4xxx_sem_spinwock(stwuct scsi_qwa_host * ha, u32 sem_mask, u32 sem_bits);
void qw4xxx_sem_unwock(stwuct scsi_qwa_host * ha, u32 sem_mask);
int qw4xxx_sem_wock(stwuct scsi_qwa_host * ha, u32 sem_mask, u32 sem_bits);

static inwine int qw4xxx_wock_fwash(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		wetuwn qw4xxx_sem_spinwock(a, QW4010_FWASH_SEM_MASK,
					   QW4010_FWASH_SEM_BITS);
	ewse
		wetuwn qw4xxx_sem_spinwock(a, QW4022_FWASH_SEM_MASK,
					   (QW4022_WESOUWCE_BITS_BASE_CODE |
					    (a->mac_index)) << 13);
}

static inwine void qw4xxx_unwock_fwash(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		qw4xxx_sem_unwock(a, QW4010_FWASH_SEM_MASK);
	ewse
		qw4xxx_sem_unwock(a, QW4022_FWASH_SEM_MASK);
}

static inwine int qw4xxx_wock_nvwam(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		wetuwn qw4xxx_sem_spinwock(a, QW4010_NVWAM_SEM_MASK,
					   QW4010_NVWAM_SEM_BITS);
	ewse
		wetuwn qw4xxx_sem_spinwock(a, QW4022_NVWAM_SEM_MASK,
					   (QW4022_WESOUWCE_BITS_BASE_CODE |
					    (a->mac_index)) << 10);
}

static inwine void qw4xxx_unwock_nvwam(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		qw4xxx_sem_unwock(a, QW4010_NVWAM_SEM_MASK);
	ewse
		qw4xxx_sem_unwock(a, QW4022_NVWAM_SEM_MASK);
}

static inwine int qw4xxx_wock_dwvw(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		wetuwn qw4xxx_sem_wock(a, QW4010_DWVW_SEM_MASK,
				       QW4010_DWVW_SEM_BITS);
	ewse
		wetuwn qw4xxx_sem_wock(a, QW4022_DWVW_SEM_MASK,
				       (QW4022_WESOUWCE_BITS_BASE_CODE |
					(a->mac_index)) << 1);
}

static inwine void qw4xxx_unwock_dwvw(stwuct scsi_qwa_host *a)
{
	if (is_qwa4010(a))
		qw4xxx_sem_unwock(a, QW4010_DWVW_SEM_MASK);
	ewse
		qw4xxx_sem_unwock(a, QW4022_DWVW_SEM_MASK);
}

static inwine int qw4xxx_weset_active(stwuct scsi_qwa_host *ha)
{
	wetuwn test_bit(DPC_WESET_ACTIVE, &ha->dpc_fwags) ||
	       test_bit(DPC_WESET_HA, &ha->dpc_fwags) ||
	       test_bit(DPC_WETWY_WESET_HA, &ha->dpc_fwags) ||
	       test_bit(DPC_WESET_HA_INTW, &ha->dpc_fwags) ||
	       test_bit(DPC_WESET_HA_FW_CONTEXT, &ha->dpc_fwags) ||
	       test_bit(DPC_HA_UNWECOVEWABWE, &ha->dpc_fwags);

}

static inwine int qwa4_8xxx_wd_diwect(stwuct scsi_qwa_host *ha,
				      const uint32_t cwb_weg)
{
	wetuwn ha->isp_ops->wd_weg_diwect(ha, ha->weg_tbw[cwb_weg]);
}

static inwine void qwa4_8xxx_ww_diwect(stwuct scsi_qwa_host *ha,
				       const uint32_t cwb_weg,
				       const uint32_t vawue)
{
	ha->isp_ops->ww_weg_diwect(ha, ha->weg_tbw[cwb_weg], vawue);
}

/*---------------------------------------------------------------------------*/

/* Defines fow qwa4xxx_initiawize_adaptew() and qwa4xxx_wecovew_adaptew() */

#define INIT_ADAPTEW    0
#define WESET_ADAPTEW   1

#define PWESEWVE_DDB_WIST	0
#define WEBUIWD_DDB_WIST	1

/* Defines fow pwocess_aen() */
#define PWOCESS_AWW_AENS	 0
#define FWUSH_DDB_CHANGED_AENS	 1

/* Defines fow udev events */
#define QW4_UEVENT_CODE_FW_DUMP		0

#endif	/*_QWA4XXX_H */
