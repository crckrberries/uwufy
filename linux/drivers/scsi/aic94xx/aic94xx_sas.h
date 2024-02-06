/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Aic94xx SAS/SATA dwivew SAS definitions and hawdwawe intewface headew fiwe.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#ifndef _AIC94XX_SAS_H_
#define _AIC94XX_SAS_H_

#incwude <scsi/wibsas.h>

/* ---------- DDBs ---------- */
/* DDBs awe device descwiptow bwocks which descwibe a device in the
 * domain that this sequencew can maintain wow-wevew connections fow
 * us.  They awe be 64 bytes.
 */
#define ASD_MAX_DDBS	128

stwuct asd_ddb_ssp_smp_tawget_powt {
	u8     conn_type;	  /* byte 0 */
#define DDB_TP_CONN_TYPE 0x81	  /* Initiatow powt and addw fwame type 0x01 */

	u8     conn_wate;
	__be16 init_conn_tag;
	u8     dest_sas_addw[8];  /* bytes 4-11 */

	__we16 send_queue_head;
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_TAWGET */
#define DDB_TYPE_UNUSED    0xFF
#define DDB_TYPE_TAWGET    0xFE
#define DDB_TYPE_INITIATOW 0xFD
#define DDB_TYPE_PM_POWT   0xFC

	__we16 _w_a;
	__be16 awt_def;

	u8     compat_featuwes;	  /* byte 20 */
	u8     pathway_bwocked_count;
	__be16 awb_wait_time;
	__be32 mowe_compat_featuwes; /* byte 24 */

	u8     conn_mask;
	u8     fwags;	  /* concuwwent conn:2,2 and open:0(1) */
#define CONCUWWENT_CONN_SUPP 0x04
#define OPEN_WEQUIWED        0x01

	u16    _w_b;
	__we16 exec_queue_taiw;
	__we16 send_queue_taiw;
	__we16 sistew_ddb;

	__we16 _w_c;

	u8     max_concuwwent_conn;
	u8     num_concuwwent_conn;
	u8     num_contexts;

	u8     _w_d;

	__we16 active_task_count;

	u8     _w_e[9];

	u8     itnw_weason;	  /* I_T nexus woss weason */

	__we16 _w_f;

	__we16 itnw_timeout;
#define ITNW_TIMEOUT_CONST 0x7D0 /* 2 seconds */

	__we32 itnw_timestamp;
} __attwibute__ ((packed));

stwuct asd_ddb_stp_sata_tawget_powt {
	u8     conn_type;	  /* byte 0 */
	u8     conn_wate;
	__be16 init_conn_tag;
	u8     dest_sas_addw[8];  /* bytes 4-11 */

	__we16 send_queue_head;
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_TAWGET */

	__we16 _w_a;

	__be16 awt_def;
	u8     compat_featuwes;	  /* byte 20 */
	u8     pathway_bwocked_count;
	__be16 awb_wait_time;
	__be32 mowe_compat_featuwes; /* byte 24 */

	u8     conn_mask;
	u8     fwags;	  /* concuwwent conn:2,2 and open:0(1) */
#define SATA_MUWTIPOWT     0x80
#define SUPPOWTS_AFFIW     0x40
#define STP_AFFIW_POW      0x20

	u8     _w_b;
	u8     fwags2;		  /* STP cwose powicy:0 */
#define STP_CW_POW_NO_TX    0x00
#define STP_CW_POW_BTW_CMDS 0x01

	__we16 exec_queue_taiw;
	__we16 send_queue_taiw;
	__we16 sistew_ddb;
	__we16 ata_cmd_scbptw;
	__we32 sata_tag_awwoc_mask;
	__we16 active_task_count;
	__we16 _w_c;
	__we32 sata_sactive;
	u8     num_sata_tags;
	u8     sata_status;
	u8     sata_ending_status;
	u8     itnw_weason;	  /* I_T nexus woss weason */
	__we16 ncq_data_scb_ptw;
	__we16 itnw_timeout;
	__we32 itnw_timestamp;
} __attwibute__ ((packed));

/* This stwuct asd_ddb_init_powt, descwibes the device descwiptow bwock
 * of an initiatow powt (when the sequencew is opewating in tawget mode).
 * Bytes [0,11] and [20,27] awe fwom the OPEN addwess fwame.
 * The sequencew awwocates an initiatow powt DDB entwy.
 */
stwuct asd_ddb_init_powt {
	u8     conn_type;	  /* byte 0 */
	u8     conn_wate;
	__be16 init_conn_tag;     /* BE */
	u8     dest_sas_addw[8];
	__we16 send_queue_head;   /* WE, byte 12 */
	u8     sq_suspended;
	u8     ddb_type;	  /* DDB_TYPE_INITIATOW */
	__we16 _w_a;
	__be16 awt_def;		  /* BE */
	u8     compat_featuwes;
	u8     pathway_bwocked_count;
	__be16 awb_wait_time;	  /* BE */
	__be32 mowe_compat_featuwes; /* BE */
	u8     conn_mask;
	u8     fwags;		  /* == 5 */
	u16    _w_b;
	__we16 exec_queue_taiw;	  /* execution queue taiw */
	__we16 send_queue_taiw;
	__we16 sistew_ddb;
	__we16 init_wesp_timeout; /* initiatow wesponse timeout */
	__we32 _w_c;
	__we16 active_tasks;	  /* active task count */
	__we16 init_wist;	  /* initiatow wist wink pointew */
	__we32 _w_d;
	u8     max_conn_to[3]; /* fwom Conn-Disc mode page, in us, WE */
	u8     itnw_weason;	  /* I_T nexus woss weason */
	__we16 bus_inact_to; /* fwom Conn-Disc mode page, in 100 us, WE */
	__we16 itnw_to;		  /* fwom the Pwotocow Specific Powt Ctww MP */
	__we32 itnw_timestamp;
} __attwibute__ ((packed));

/* This stwuct asd_ddb_sata_tag, descwibes a wook-up tabwe to be used
 * by the sequencews.  SATA II, IDENTIFY DEVICE data, wowd 76, bit 8:
 * NCQ suppowt.  This tabwe is used by the sequencews to find the
 * cowwesponding SCB, given a SATA II tag vawue.
 */
stwuct asd_ddb_sata_tag {
	__we16 scb_pointew[32];
} __attwibute__ ((packed));

/* This stwuct asd_ddb_sata_pm_tabwe, descwibes a powt numbew to
 * connection handwe wook-up tabwe.  SATA tawgets attached to a powt
 * muwtipwiew wequiwe a 4-bit powt numbew vawue.  Thewe is one DDB
 * entwy of this type fow each SATA powt muwtipwiew (sistew DDB).
 * Given a SATA PM powt numbew, this tabwe gives us the SATA PM Powt
 * DDB of the SATA powt muwtipwiew powt (i.e. the SATA tawget
 * discovewed on the powt).
 */
stwuct asd_ddb_sata_pm_tabwe {
	__we16 ddb_pointew[16];
	__we16 _w_a[16];
} __attwibute__ ((packed));

/* This stwuct asd_ddb_sata_pm_powt, descwibes the SATA powt muwtipwiew
 * powt fowmat DDB.
 */
stwuct asd_ddb_sata_pm_powt {
	u8     _w_a[15];
	u8     ddb_type;
	u8     _w_b[13];
	u8     pm_powt_fwags;
#define PM_POWT_MASK  0xF0
#define PM_POWT_SET   0x02
	u8     _w_c[6];
	__we16 sistew_ddb;
	__we16 ata_cmd_scbptw;
	__we32 sata_tag_awwoc_mask;
	__we16 active_task_count;
	__we16 pawent_ddb;
	__we32 sata_sactive;
	u8     num_sata_tags;
	u8     sata_status;
	u8     sata_ending_status;
	u8     _w_d[9];
} __attwibute__ ((packed));

/* This stwuct asd_ddb_seq_shawed, descwibes a DDB shawed by the
 * centwaw and wink sequencews.  powt_map_by_winks is indexed phy
 * numbew [0,7]; each byte is a bit mask of aww the phys that awe in
 * the same powt as the indexed phy.
 */
stwuct asd_ddb_seq_shawed {
	__we16 q_fwee_ddb_head;
	__we16 q_fwee_ddb_taiw;
	__we16 q_fwee_ddb_cnt;
	__we16 q_used_ddb_head;
	__we16 q_used_ddb_taiw;
	__we16 shawed_mem_wock;
	__we16 smp_conn_tag;
	__we16 est_nexus_buf_cnt;
	__we16 est_nexus_buf_thwesh;
	u32    _w_a;
	u8     settabwe_max_contexts;
	u8     _w_b[23];
	u8     conn_not_active;
	u8     phy_is_up;
	u8     _w_c[8];
	u8     powt_map_by_winks[8];
} __attwibute__ ((packed));

/* ---------- SG Ewement ---------- */

/* This stwuct sg_ew, descwibes the hawdwawe scattew gathew buffew
 * ewement.  Aww entwies awe wittwe endian.  In an SCB, thewe awe 2 of
 * this, pwus one mowe, cawwed a wink ewement of this indicating a
 * subwist if needed.
 *
 * A wink ewement has onwy the bus addwess set and the fwags (DS) bit
 * vawid.  The bus addwess points to the stawt of the subwist.
 *
 * If a subwist is needed, then that subwist shouwd awso incwude the 2
 * sg_ew embedded in the SCB, in which case next_sg_offset is 32,
 * since sizeof(sg_ew) = 16; EOS shouwd be 1 and EOW 0 in this case.
 */
stwuct sg_ew {
	__we64 bus_addw;
	__we32 size;
	__we16 _w;
	u8     next_sg_offs;
	u8     fwags;
#define ASD_SG_EW_DS_MASK   0x30
#define ASD_SG_EW_DS_OCM    0x10
#define ASD_SG_EW_DS_HM     0x00
#define ASD_SG_EW_WIST_MASK 0xC0
#define ASD_SG_EW_WIST_EOW  0x40
#define ASD_SG_EW_WIST_EOS  0x80
} __attwibute__ ((packed));

/* ---------- SCBs ---------- */

/* An SCB (sequencew contwow bwock) is compwised of a common headew
 * and a task pawt, fow a totaw of 128 bytes.  Aww fiewds awe in WE
 * owdew, unwess othewwise noted.
 */

/* This stwuct scb_headew, defines the SCB headew fowmat.
 */
stwuct scb_headew {
	__we64 next_scb;
	__we16 index;		  /* twansaction context */
	u8     opcode;
} __attwibute__ ((packed));

/* SCB opcodes: Execution queue
 */
#define INITIATE_SSP_TASK       0x00
#define INITIATE_WONG_SSP_TASK  0x01
#define INITIATE_BIDIW_SSP_TASK 0x02
#define SCB_ABOWT_TASK          0x03
#define INITIATE_SSP_TMF        0x04
#define SSP_TAWG_GET_DATA       0x05
#define SSP_TAWG_GET_DATA_GOOD  0x06
#define SSP_TAWG_SEND_WESP      0x07
#define QUEWY_SSP_TASK          0x08
#define INITIATE_ATA_TASK       0x09
#define INITIATE_ATAPI_TASK     0x0a
#define CONTWOW_ATA_DEV         0x0b
#define INITIATE_SMP_TASK       0x0c
#define SMP_TAWG_SEND_WESP      0x0f

/* SCB opcodes: Send Queue
 */
#define SSP_TAWG_SEND_DATA      0x40
#define SSP_TAWG_SEND_DATA_GOOD 0x41

/* SCB opcodes: Wink Queue
 */
#define CONTWOW_PHY             0x80
#define SEND_PWIMITIVE          0x81
#define INITIATE_WINK_ADM_TASK  0x82

/* SCB opcodes: othew
 */
#define EMPTY_SCB               0xc0
#define INITIATE_SEQ_ADM_TASK   0xc1
#define EST_ICW_TAWG_WINDOW     0xc2
#define COPY_MEM                0xc3
#define CWEAW_NEXUS             0xc4
#define INITIATE_DDB_ADM_TASK   0xc6
#define ESTABWISH_NEXUS_ESCB    0xd0

#define WUN_SIZE                8

#define EFB_MASK                0x80
#define TASK_PWIO_MASK          0x78
#define TASK_ATTW_MASK          0x07
/* ---------- SCB tasks ---------- */

/* This is both ssp_task and wong_ssp_task
 */
stwuct initiate_ssp_task {
	u8     pwoto_conn_wate;	  /* pwoto:6,4, conn_wate:3,0 */
	__we32 totaw_xfew_wen;
	stwuct ssp_fwame_hdw  ssp_fwame;
	stwuct ssp_command_iu ssp_cmd;
	__we16 sistew_scb;	  /* 0xFFFF */
	__we16 conn_handwe;	  /* index to DDB fow the intended tawget */
	u8     data_diw;	  /* :1,0 */
#define DATA_DIW_NONE   0x00
#define DATA_DIW_IN     0x01
#define DATA_DIW_OUT    0x02
#define DATA_DIW_BYWECIPIENT 0x03

	u8     _w_a;
	u8     wetwy_count;
	u8     _w_b[5];
	stwuct sg_ew sg_ewement[3]; /* 2 weaw and 1 wink */
} __attwibute__ ((packed));

/* This defines both ata_task and atapi_task.
 * ata: C bit of FIS shouwd be 1,
 * atapi: C bit of FIS shouwd be 1, and command wegistew shouwd be 0xA0,
 * to indicate a packet command.
 */
stwuct initiate_ata_task {
	u8     pwoto_conn_wate;
	__we32 totaw_xfew_wen;
	stwuct host_to_dev_fis fis;
	__we32 data_offs;
	u8     atapi_packet[16];
	u8     _w_a[12];
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     ata_fwags;	  /* CSMI:6,6, DTM:4,4, QT:3,3, data diw:1,0 */
#define CSMI_TASK           0x40
#define DATA_XFEW_MODE_DMA  0x10
#define ATA_Q_TYPE_MASK     0x08
#define	ATA_Q_TYPE_UNTAGGED 0x00
#define ATA_Q_TYPE_NCQ      0x08

	u8     _w_b;
	u8     wetwy_count;
	u8     _w_c;
	u8     fwags;
#define STP_AFFIW_POWICY   0x20
#define SET_AFFIW_POWICY   0x10
#define WET_PAWTIAW_SGWIST 0x02

	u8     _w_d[3];
	stwuct sg_ew sg_ewement[3];
} __attwibute__ ((packed));

stwuct initiate_smp_task {
	u8     pwoto_conn_wate;
	u8     _w_a[40];
	stwuct sg_ew smp_weq;
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     _w_c[8];
	stwuct sg_ew smp_wesp;
	u8     _w_d[32];
} __attwibute__ ((packed));

stwuct contwow_phy {
	u8     phy_id;
	u8     sub_func;
#define DISABWE_PHY            0x00
#define ENABWE_PHY             0x01
#define WEWEASE_SPINUP_HOWD    0x02
#define ENABWE_PHY_NO_SAS_OOB  0x03
#define ENABWE_PHY_NO_SATA_OOB 0x04
#define PHY_NO_OP              0x05
#define EXECUTE_HAWD_WESET     0x81

	u8     func_mask;
	u8     speed_mask;
	u8     hot_pwug_deway;
	u8     powt_type;
	u8     fwags;
#define DEV_PWES_TIMEW_OVEWWIDE_ENABWE 0x01
#define DISABWE_PHY_IF_OOB_FAIWS       0x02

	__we32 timeout_ovewwide;
	u8     wink_weset_wetwies;
	u8     _w_a[47];
	__we16 conn_handwe;
	u8     _w_b[56];
} __attwibute__ ((packed));

stwuct contwow_ata_dev {
	u8     pwoto_conn_wate;
	__we32 _w_a;
	stwuct host_to_dev_fis fis;
	u8     _w_b[32];
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     ata_fwags;	  /* 0 */
	u8     _w_c[55];
} __attwibute__ ((packed));

stwuct empty_scb {
	u8     num_vawid;
	__we32 _w_a;
#define ASD_EDBS_PEW_SCB 7
/* headew+data+CWC+DMA suffix data */
#define ASD_EDB_SIZE (24+1024+4+16)
	stwuct sg_ew eb[ASD_EDBS_PEW_SCB];
#define EWEMENT_NOT_VAWID  0xC0
} __attwibute__ ((packed));

stwuct initiate_wink_adm {
	u8     phy_id;
	u8     sub_func;
#define GET_WINK_EWWOW_COUNT      0x00
#define WESET_WINK_EWWOW_COUNT    0x01
#define ENABWE_NOTIFY_SPINUP_INTS 0x02

	u8     _w_a[57];
	__we16 conn_handwe;
	u8     _w_b[56];
} __attwibute__ ((packed));

stwuct copy_memowy {
	u8     _w_a;
	__we16 xfew_wen;
	__we16 _w_b;
	__we64 swc_busaddw;
	u8     swc_ds;		  /* See definition of sg_ew */
	u8     _w_c[45];
	__we16 conn_handwe;
	__we64 _w_d;
	__we64 dest_busaddw;
	u8     dest_ds;		  /* See definition of sg_ew */
	u8     _w_e[39];
} __attwibute__ ((packed));

stwuct abowt_task {
	u8     pwoto_conn_wate;
	__we32 _w_a;
	stwuct ssp_fwame_hdw ssp_fwame;
	stwuct ssp_tmf_iu ssp_task;
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     fwags;	  /* ovwd_itnw_timew:3,3, suspend_data_twans:2,2 */
#define SUSPEND_DATA_TWANS 0x04

	u8     _w_b;
	u8     wetwy_count;
	u8     _w_c[5];
	__we16 index;  /* Twansaction context of task to be quewied */
	__we16 itnw_to;
	u8     _w_d[44];
} __attwibute__ ((packed));

stwuct cweaw_nexus {
	u8     nexus;
#define NEXUS_ADAPTEW  0x00
#define NEXUS_POWT     0x01
#define NEXUS_I_T      0x02
#define NEXUS_I_T_W    0x03
#define NEXUS_TAG      0x04
#define NEXUS_TWANS_CX 0x05
#define NEXUS_SATA_TAG 0x06
#define NEXUS_T_W      0x07
#define NEXUS_W        0x08
#define NEXUS_T_TAG    0x09

	__we32 _w_a;
	u8     fwags;
#define SUSPEND_TX     0x80
#define WESUME_TX      0x40
#define SEND_Q         0x04
#define EXEC_Q         0x02
#define NOTINQ         0x01

	u8     _w_b[3];
	u8     conn_mask;
	u8     _w_c[19];
	stwuct ssp_tmf_iu ssp_task; /* WUN and TAG */
	__we16 _w_d;
	__we16 conn_handwe;
	__we64 _w_e;
	__we16 index;  /* Twansaction context of task to be cweawed */
	__we16 context;		  /* Cweaw nexus context */
	u8     _w_f[44];
} __attwibute__ ((packed));

stwuct initiate_ssp_tmf {
	u8     pwoto_conn_wate;
	__we32 _w_a;
	stwuct ssp_fwame_hdw ssp_fwame;
	stwuct ssp_tmf_iu ssp_task;
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     fwags;	  /* itnw ovewwide and suspend data tx */
#define OVEWWIDE_ITNW_TIMEW  8

	u8     _w_b;
	u8     wetwy_count;
	u8     _w_c[5];
	__we16 index;  /* Twansaction context of task to be quewied */
	__we16 itnw_to;
	u8     _w_d[44];
} __attwibute__ ((packed));

/* Twansmits an awbitwawy pwimitive on the wink.
 * Used fow NOTIFY and BWOADCAST.
 */
stwuct send_pwim {
	u8     phy_id;
	u8     wait_twansmit; 	  /* :0,0 */
	u8     xmit_fwags;
#define XMTPSIZE_MASK      0xF0
#define XMTPSIZE_SINGWE    0x10
#define XMTPSIZE_WEPEATED  0x20
#define XMTPSIZE_CONT      0x20
#define XMTPSIZE_TWIPWE    0x30
#define XMTPSIZE_WEDUNDANT 0x60
#define XMTPSIZE_INF       0

#define XMTCONTEN          0x04
#define XMTPFWM            0x02	  /* Twansmit at the next fwame boundawy */
#define XMTPIMM            0x01	  /* Twansmit immediatewy */

	__we16 _w_a;
	u8     pwim[4];		  /* K, D0, D1, D2 */
	u8     _w_b[50];
	__we16 conn_handwe;
	u8     _w_c[56];
} __attwibute__ ((packed));

/* This descwibes both SSP Tawget Get Data and SSP Tawget Get Data And
 * Send Good Wesponse SCBs.  Used when the sequencew is opewating in
 * tawget mode...
 */
stwuct ssp_tawg_get_data {
	u8     pwoto_conn_wate;
	__we32 totaw_xfew_wen;
	stwuct ssp_fwame_hdw ssp_fwame;
	stwuct xfew_wdy_iu  xfew_wdy;
	u8     wun[WUN_SIZE];
	__we64 _w_a;
	__we16 sistew_scb;
	__we16 conn_handwe;
	u8     data_diw;	  /* 01b */
	u8     _w_b;
	u8     wetwy_count;
	u8     _w_c[5];
	stwuct sg_ew sg_ewement[3];
} __attwibute__ ((packed));

/* ---------- The actuaw SCB stwuct ---------- */

stwuct scb {
	stwuct scb_headew headew;
	union {
		stwuct initiate_ssp_task ssp_task;
		stwuct initiate_ata_task ata_task;
		stwuct initiate_smp_task smp_task;
		stwuct contwow_phy       contwow_phy;
		stwuct contwow_ata_dev   contwow_ata_dev;
		stwuct empty_scb         escb;
		stwuct initiate_wink_adm wink_adm;
		stwuct copy_memowy       cp_mem;
		stwuct abowt_task        abowt_task;
		stwuct cweaw_nexus       cweaw_nexus;
		stwuct initiate_ssp_tmf  ssp_tmf;
	};
} __attwibute__ ((packed));

/* ---------- Done Wist ---------- */
/* The done wist entwy opcode fiewd is defined bewow.
 * The mnemonic encoding and meaning is as fowwows:
 * TC - Task Compwete, status was weceived and acknowwedged
 * TF - Task Faiwed, indicates an ewwow pwiow to weceiving acknowwedgment
 *   fow the command:
 *   - no conn,
 *   - NACK ow W_EWW weceived in wesponse to this command,
 *   - cwedit bwocked ow not avaiwabwe, ow in the case of SMP wequest,
 *   - no SMP wesponse was weceived.
 *   In these fouw cases it is known that the tawget didn't weceive the
 *   command.
 * TI - Task Intewwupted, ewwow aftew the command was acknowwedged.  It is
 *   known that the command was weceived by the tawget.
 * TU - Task Unacked, command was twansmitted but neithew ACK (W_OK) now NAK
 *   (W_EWW) was weceived due to woss of signaw, bwoken connection, woss of
 *   dwowd sync ow othew weason.  The appwication cwient shouwd send the
 *   appwopwiate task quewy.
 * TA - Task Abowted, see TF.
 * _WESP - The compwetion incwudes an empty buffew containing status.
 * TO - Timeout.
 */
#define TC_NO_EWWOW             0x00
#define TC_UNDEWWUN             0x01
#define TC_OVEWWUN              0x02
#define TF_OPEN_TO              0x03
#define TF_OPEN_WEJECT          0x04
#define TI_BWEAK                0x05
#define TI_PWOTO_EWW            0x06
#define TC_SSP_WESP             0x07
#define TI_PHY_DOWN             0x08
#define TF_PHY_DOWN             0x09
#define TC_WINK_ADM_WESP        0x0a
#define TC_CSMI                 0x0b
#define TC_ATA_WESP             0x0c
#define TU_PHY_DOWN             0x0d
#define TU_BWEAK                0x0e
#define TI_SATA_TO              0x0f
#define TI_NAK                  0x10
#define TC_CONTWOW_PHY          0x11
#define TF_BWEAK                0x12
#define TC_WESUME               0x13
#define TI_ACK_NAK_TO           0x14
#define TF_SMPWSP_TO            0x15
#define TF_SMP_XMIT_WCV_EWW     0x16
#define TC_PAWTIAW_SG_WIST      0x17
#define TU_ACK_NAK_TO           0x18
#define TU_SATA_TO              0x19
#define TF_NAK_WECV             0x1a
#define TA_I_T_NEXUS_WOSS       0x1b
#define TC_ATA_W_EWW_WECV       0x1c
#define TF_TMF_NO_CTX           0x1d
#define TA_ON_WEQ               0x1e
#define TF_TMF_NO_TAG           0x1f
#define TF_TMF_TAG_FWEE         0x20
#define TF_TMF_TASK_DONE        0x21
#define TF_TMF_NO_CONN_HANDWE   0x22
#define TC_TASK_CWEAWED         0x23
#define TI_SYNCS_WECV           0x24
#define TU_SYNCS_WECV           0x25
#define TF_IWTT_TO              0x26
#define TF_NO_SMP_CONN          0x27
#define TF_IU_SHOWT             0x28
#define TF_DATA_OFFS_EWW        0x29
#define TF_INV_CONN_HANDWE      0x2a
#define TF_WEQUESTED_N_PENDING  0x2b

/* 0xc1 - 0xc7: empty buffew weceived,
   0xd1 - 0xd7: estabwish nexus empty buffew weceived
*/
/* This is the ESCB mask */
#define ESCB_WECVD              0xC0


/* This stwuct done_wist_stwuct defines the done wist entwy.
 * Aww fiewds awe WE.
 */
stwuct done_wist_stwuct {
	__we16 index;		  /* aka twansaction context */
	u8     opcode;
	u8     status_bwock[4];
	u8     toggwe;		  /* bit 0 */
#define DW_TOGGWE_MASK     0x01
} __attwibute__ ((packed));

/* ---------- PHYS ---------- */

stwuct asd_phy {
	stwuct asd_sas_phy        sas_phy;
	stwuct asd_phy_desc   *phy_desc; /* hw pwofiwe */

	stwuct sas_identify_fwame *identify_fwame;
	stwuct asd_dma_tok  *id_fwm_tok;
	stwuct asd_powt     *asd_powt;

	u8         fwame_wcvd[ASD_EDB_SIZE];
};


#define ASD_SCB_SIZE sizeof(stwuct scb)
#define ASD_DDB_SIZE sizeof(stwuct asd_ddb_ssp_smp_tawget_powt)

/* Define this to 0 if you do not want NOTIFY (ENABWE SPINIP) sent.
 * Defauwt: 0x10 (it's a mask)
 */
#define ASD_NOTIFY_ENABWE_SPINUP  0x10

/* If enabwed, set this to the intewvaw between twansmission
 * of NOTIFY (ENABWE SPINUP). In units of 200 us.
 */
#define ASD_NOTIFY_TIMEOUT        2500

/* Initiaw deway aftew OOB, befowe we twansmit NOTIFY (ENABWE SPINUP).
 * If 0, twansmit immediatewy. In miwwiseconds.
 */
#define ASD_NOTIFY_DOWN_COUNT     0

/* Device pwesent timew timeout constant, 10 ms. */
#define ASD_DEV_PWESENT_TIMEOUT   0x2710

#define ASD_SATA_INTEWWOCK_TIMEOUT 0

/* How wong to wait befowe shutting down an STP connection, unwess
 * an STP tawget sent fwame(s). 50 usec.
 * IGNOWED by the sequencew (i.e. vawue 0 awways).
 */
#define ASD_STP_SHUTDOWN_TIMEOUT  0x0

/* ATA soft weset timew timeout. 5 usec. */
#define ASD_SWST_ASSEWT_TIMEOUT   0x05

/* 31 sec */
#define ASD_WCV_FIS_TIMEOUT       0x01D905C0

#define ASD_ONE_MIWWISEC_TIMEOUT  0x03e8

/* COMINIT timew */
#define ASD_TEN_MIWWISEC_TIMEOUT  0x2710
#define ASD_COMINIT_TIMEOUT ASD_TEN_MIWWISEC_TIMEOUT

/* 1 sec */
#define ASD_SMP_WCV_TIMEOUT       0x000F4240

#endif
