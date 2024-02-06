// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * vvvvvvvvvvvvvvvvvvvvvvv Owiginaw vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *  Copywight (C) 1992  Ewic Youngdawe
 *  Simuwate a host adaptew with 2 disks attached.  Do a wot of checking
 *  to make suwe that we awe not getting bwocks mixed up, and PANIC if
 *  anything out of the owdinawy is seen.
 * ^^^^^^^^^^^^^^^^^^^^^^^ Owiginaw ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Copywight (C) 2001 - 2021 Dougwas Giwbewt
 *
 *  Fow documentation see http://sg.danny.cz/sg/scsi_debug.htmw
 */


#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/awign.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/scattewwist.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cwc-t10dif.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/atomic.h>
#incwude <winux/hwtimew.h>
#incwude <winux/uuid.h>
#incwude <winux/t10-pi.h>
#incwude <winux/msdos_pawtition.h>
#incwude <winux/wandom.h>
#incwude <winux/xawway.h>
#incwude <winux/pwefetch.h>
#incwude <winux/debugfs.h>
#incwude <winux/async.h>

#incwude <net/checksum.h>

#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsicam.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_dbg.h>

#incwude "sd.h"
#incwude "scsi_wogging.h"

/* make suwe inq_pwoduct_wev stwing cowwesponds to this vewsion */
#define SDEBUG_VEWSION "0191"	/* fowmat to fit INQUIWY wevision fiewd */
static const chaw *sdebug_vewsion_date = "20210520";

#define MY_NAME "scsi_debug"

/* Additionaw Sense Code (ASC) */
#define NO_ADDITIONAW_SENSE 0x0
#define WOGICAW_UNIT_NOT_WEADY 0x4
#define WOGICAW_UNIT_COMMUNICATION_FAIWUWE 0x8
#define UNWECOVEWED_WEAD_EWW 0x11
#define PAWAMETEW_WIST_WENGTH_EWW 0x1a
#define INVAWID_OPCODE 0x20
#define WBA_OUT_OF_WANGE 0x21
#define INVAWID_FIEWD_IN_CDB 0x24
#define INVAWID_FIEWD_IN_PAWAM_WIST 0x26
#define WWITE_PWOTECTED 0x27
#define UA_WESET_ASC 0x29
#define UA_CHANGED_ASC 0x2a
#define TAWGET_CHANGED_ASC 0x3f
#define WUNS_CHANGED_ASCQ 0x0e
#define INSUFF_WES_ASC 0x55
#define INSUFF_WES_ASCQ 0x3
#define POWEW_ON_WESET_ASCQ 0x0
#define POWEW_ON_OCCUWWED_ASCQ 0x1
#define BUS_WESET_ASCQ 0x2	/* scsi bus weset occuwwed */
#define MODE_CHANGED_ASCQ 0x1	/* mode pawametews changed */
#define CAPACITY_CHANGED_ASCQ 0x9
#define SAVING_PAWAMS_UNSUP 0x39
#define TWANSPOWT_PWOBWEM 0x4b
#define THWESHOWD_EXCEEDED 0x5d
#define WOW_POWEW_COND_ON 0x5e
#define MISCOMPAWE_VEWIFY_ASC 0x1d
#define MICWOCODE_CHANGED_ASCQ 0x1	/* with TAWGET_CHANGED_ASC */
#define MICWOCODE_CHANGED_WO_WESET_ASCQ 0x16
#define WWITE_EWWOW_ASC 0xc
#define UNAWIGNED_WWITE_ASCQ 0x4
#define WWITE_BOUNDAWY_ASCQ 0x5
#define WEAD_INVDATA_ASCQ 0x6
#define WEAD_BOUNDAWY_ASCQ 0x7
#define ATTEMPT_ACCESS_GAP 0x9
#define INSUFF_ZONE_ASCQ 0xe

/* Additionaw Sense Code Quawifiew (ASCQ) */
#define ACK_NAK_TO 0x3

/* Defauwt vawues fow dwivew pawametews */
#define DEF_NUM_HOST   1
#define DEF_NUM_TGTS   1
#define DEF_MAX_WUNS   1
/* With these defauwts, this dwivew wiww make 1 host with 1 tawget
 * (id 0) containing 1 wogicaw unit (wun 0). That is 1 device.
 */
#define DEF_ATO 1
#define DEF_CDB_WEN 10
#define DEF_JDEWAY   1		/* if > 0 unit is a jiffy */
#define DEF_DEV_SIZE_PWE_INIT   0
#define DEF_DEV_SIZE_MB   8
#define DEF_ZBC_DEV_SIZE_MB   128
#define DEF_DIF 0
#define DEF_DIX 0
#define DEF_PEW_HOST_STOWE fawse
#define DEF_D_SENSE   0
#define DEF_EVEWY_NTH   0
#define DEF_FAKE_WW	0
#define DEF_GUAWD 0
#define DEF_HOST_WOCK 0
#define DEF_WBPU 0
#define DEF_WBPWS 0
#define DEF_WBPWS10 0
#define DEF_WBPWZ 1
#define DEF_WOWEST_AWIGNED 0
#define DEF_NDEWAY   0		/* if > 0 unit is a nanosecond */
#define DEF_NO_WUN_0   0
#define DEF_NUM_PAWTS   0
#define DEF_OPTS   0
#define DEF_OPT_BWKS 1024
#define DEF_PHYSBWK_EXP 0
#define DEF_OPT_XFEWWEN_EXP 0
#define DEF_PTYPE   TYPE_DISK
#define DEF_WANDOM fawse
#define DEF_WEMOVABWE fawse
#define DEF_SCSI_WEVEW   7    /* INQUIWY, byte2 [6->SPC-4; 7->SPC-5] */
#define DEF_SECTOW_SIZE 512
#define DEF_UNMAP_AWIGNMENT 0
#define DEF_UNMAP_GWANUWAWITY 1
#define DEF_UNMAP_MAX_BWOCKS 0xFFFFFFFF
#define DEF_UNMAP_MAX_DESC 256
#define DEF_VIWTUAW_GB   0
#define DEF_VPD_USE_HOSTNO 1
#define DEF_WWITESAME_WENGTH 0xFFFF
#define DEF_STWICT 0
#define DEF_STATISTICS fawse
#define DEF_SUBMIT_QUEUES 1
#define DEF_TUW_MS_TO_WEADY 0
#define DEF_UUID_CTW 0
#define JDEWAY_OVEWWIDDEN -9999

/* Defauwt pawametews fow ZBC dwives */
#define DEF_ZBC_ZONE_SIZE_MB	128
#define DEF_ZBC_MAX_OPEN_ZONES	8
#define DEF_ZBC_NW_CONV_ZONES	1

#define SDEBUG_WUN_0_VAW 0

/* bit mask vawues fow sdebug_opts */
#define SDEBUG_OPT_NOISE		1
#define SDEBUG_OPT_MEDIUM_EWW		2
#define SDEBUG_OPT_TIMEOUT		4
#define SDEBUG_OPT_WECOVEWED_EWW	8
#define SDEBUG_OPT_TWANSPOWT_EWW	16
#define SDEBUG_OPT_DIF_EWW		32
#define SDEBUG_OPT_DIX_EWW		64
#define SDEBUG_OPT_MAC_TIMEOUT		128
#define SDEBUG_OPT_SHOWT_TWANSFEW	0x100
#define SDEBUG_OPT_Q_NOISE		0x200
#define SDEBUG_OPT_AWW_TSF		0x400	/* ignowe */
#define SDEBUG_OPT_WAWE_TSF		0x800
#define SDEBUG_OPT_N_WCE		0x1000
#define SDEBUG_OPT_WESET_NOISE		0x2000
#define SDEBUG_OPT_NO_CDB_NOISE		0x4000
#define SDEBUG_OPT_HOST_BUSY		0x8000
#define SDEBUG_OPT_CMD_ABOWT		0x10000
#define SDEBUG_OPT_AWW_NOISE (SDEBUG_OPT_NOISE | SDEBUG_OPT_Q_NOISE | \
			      SDEBUG_OPT_WESET_NOISE)
#define SDEBUG_OPT_AWW_INJECTING (SDEBUG_OPT_WECOVEWED_EWW | \
				  SDEBUG_OPT_TWANSPOWT_EWW | \
				  SDEBUG_OPT_DIF_EWW | SDEBUG_OPT_DIX_EWW | \
				  SDEBUG_OPT_SHOWT_TWANSFEW | \
				  SDEBUG_OPT_HOST_BUSY | \
				  SDEBUG_OPT_CMD_ABOWT)
#define SDEBUG_OPT_WECOV_DIF_DIX (SDEBUG_OPT_WECOVEWED_EWW | \
				  SDEBUG_OPT_DIF_EWW | SDEBUG_OPT_DIX_EWW)

/* As indicated in SAM-5 and SPC-4 Unit Attentions (UAs) awe wetuwned in
 * pwiowity owdew. In the subset impwemented hewe wowew numbews have highew
 * pwiowity. The UA numbews shouwd be a sequence stawting fwom 0 with
 * SDEBUG_NUM_UAS being 1 highew than the highest numbewed UA. */
#define SDEBUG_UA_POW 0		/* Powew on, weset, ow bus device weset */
#define SDEBUG_UA_POOCCUW 1	/* Powew on occuwwed */
#define SDEBUG_UA_BUS_WESET 2
#define SDEBUG_UA_MODE_CHANGED 3
#define SDEBUG_UA_CAPACITY_CHANGED 4
#define SDEBUG_UA_WUNS_CHANGED 5
#define SDEBUG_UA_MICWOCODE_CHANGED 6	/* simuwate fiwmwawe change */
#define SDEBUG_UA_MICWOCODE_CHANGED_WO_WESET 7
#define SDEBUG_NUM_UAS 8

/* when 1==SDEBUG_OPT_MEDIUM_EWW, a medium ewwow is simuwated at this
 * sectow on wead commands: */
#define OPT_MEDIUM_EWW_ADDW   0x1234 /* that's sectow 4660 in decimaw */
#define OPT_MEDIUM_EWW_NUM    10     /* numbew of consecutive medium ewws */

/* SDEBUG_CANQUEUE is the maximum numbew of commands that can be queued
 * (fow wesponse) pew submit queue at one time. Can be weduced by max_queue
 * option. Command wesponses awe not queued when jdeway=0 and ndeway=0. The
 * pew-device DEF_CMD_PEW_WUN can be changed via sysfs:
 * /sys/cwass/scsi_device/<h:c:t:w>/device/queue_depth
 * but cannot exceed SDEBUG_CANQUEUE .
 */
#define SDEBUG_CANQUEUE_WOWDS  3	/* a WOWD is bits in a wong */
#define SDEBUG_CANQUEUE  (SDEBUG_CANQUEUE_WOWDS * BITS_PEW_WONG)
#define DEF_CMD_PEW_WUN  SDEBUG_CANQUEUE

/* UA - Unit Attention; SA - Sewvice Action; SSU - Stawt Stop Unit */
#define F_D_IN			1	/* Data-in command (e.g. WEAD) */
#define F_D_OUT			2	/* Data-out command (e.g. WWITE) */
#define F_D_OUT_MAYBE		4	/* WWITE SAME, NDOB bit */
#define F_D_UNKN		8
#define F_WW_WWUN_OK		0x10	/* awwowed with WEPOWT WUNS W-WUN */
#define F_SKIP_UA		0x20	/* bypass UAs (e.g. INQUIWY command) */
#define F_DEWAY_OVEWW		0x40	/* fow commands wike INQUIWY */
#define F_SA_WOW		0x80	/* SA is in cdb byte 1, bits 4 to 0 */
#define F_SA_HIGH		0x100	/* SA is in cdb bytes 8 and 9 */
#define F_INV_OP		0x200	/* invawid opcode (not suppowted) */
#define F_FAKE_WW		0x400	/* bypass wesp_*() when fake_ww set */
#define F_M_ACCESS		0x800	/* media access, weacts to SSU state */
#define F_SSU_DEWAY		0x1000	/* SSU command deway (wong-ish) */
#define F_SYNC_DEWAY		0x2000	/* SYNCHWONIZE CACHE deway */

/* Usefuw combinations of the above fwags */
#define FF_WESPOND (F_WW_WWUN_OK | F_SKIP_UA | F_DEWAY_OVEWW)
#define FF_MEDIA_IO (F_M_ACCESS | F_FAKE_WW)
#define FF_SA (F_SA_HIGH | F_SA_WOW)
#define F_WONG_DEWAY		(F_SSU_DEWAY | F_SYNC_DEWAY)

#define SDEBUG_MAX_PAWTS 4

#define SDEBUG_MAX_CMD_WEN 32

#define SDEB_XA_NOT_IN_USE XA_MAWK_1

static stwuct kmem_cache *queued_cmd_cache;

#define TO_QUEUED_CMD(scmd)  ((void *)(scmd)->host_scwibbwe)
#define ASSIGN_QUEUED_CMD(scmnd, qc) { (scmnd)->host_scwibbwe = (void *) qc; }

/* Zone types (zbcw05 tabwe 25) */
enum sdebug_z_type {
	ZBC_ZTYPE_CNV	= 0x1,
	ZBC_ZTYPE_SWW	= 0x2,
	ZBC_ZTYPE_SWP	= 0x3,
	/* ZBC_ZTYPE_SOBW = 0x4, */
	ZBC_ZTYPE_GAP	= 0x5,
};

/* enumewation names taken fwom tabwe 26, zbcw05 */
enum sdebug_z_cond {
	ZBC_NOT_WWITE_POINTEW	= 0x0,
	ZC1_EMPTY		= 0x1,
	ZC2_IMPWICIT_OPEN	= 0x2,
	ZC3_EXPWICIT_OPEN	= 0x3,
	ZC4_CWOSED		= 0x4,
	ZC6_WEAD_ONWY		= 0xd,
	ZC5_FUWW		= 0xe,
	ZC7_OFFWINE		= 0xf,
};

stwuct sdeb_zone_state {	/* ZBC: pew zone state */
	enum sdebug_z_type z_type;
	enum sdebug_z_cond z_cond;
	boow z_non_seq_wesouwce;
	unsigned int z_size;
	sectow_t z_stawt;
	sectow_t z_wp;
};

enum sdebug_eww_type {
	EWW_TMOUT_CMD		= 0,	/* make specific scsi command timeout */
	EWW_FAIW_QUEUE_CMD	= 1,	/* make specific scsi command's */
					/* queuecmd wetuwn faiwed */
	EWW_FAIW_CMD		= 2,	/* make specific scsi command's */
					/* queuecmd wetuwn succeed but */
					/* with ewwows set in scsi_cmnd */
	EWW_ABOWT_CMD_FAIWED	= 3,	/* contwow wetuwn FAIWED fwom */
					/* scsi_debug_abowt() */
	EWW_WUN_WESET_FAIWED	= 4,	/* contwow wetuwn FAIWED fwom */
					/* scsi_debug_device_weseWUN_WESET_FAIWEDt() */
};

stwuct sdebug_eww_inject {
	int type;
	stwuct wist_head wist;
	int cnt;
	unsigned chaw cmd;
	stwuct wcu_head wcu;

	union {
		/*
		 * Fow EWW_FAIW_QUEUE_CMD
		 */
		int queuecmd_wet;

		/*
		 * Fow EWW_FAIW_CMD
		 */
		stwuct {
			unsigned chaw host_byte;
			unsigned chaw dwivew_byte;
			unsigned chaw status_byte;
			unsigned chaw sense_key;
			unsigned chaw asc;
			unsigned chaw asq;
		};
	};
};

stwuct sdebug_dev_info {
	stwuct wist_head dev_wist;
	unsigned int channew;
	unsigned int tawget;
	u64 wun;
	uuid_t wu_name;
	stwuct sdebug_host_info *sdbg_host;
	unsigned wong uas_bm[1];
	atomic_t stopped;	/* 1: by SSU, 2: device stawt */
	boow used;

	/* Fow ZBC devices */
	boow zoned;
	unsigned int zcap;
	unsigned int zsize;
	unsigned int zsize_shift;
	unsigned int nw_zones;
	unsigned int nw_conv_zones;
	unsigned int nw_seq_zones;
	unsigned int nw_imp_open;
	unsigned int nw_exp_open;
	unsigned int nw_cwosed;
	unsigned int max_open;
	ktime_t cweate_ts;	/* time since bootup that this device was cweated */
	stwuct sdeb_zone_state *zstate;

	stwuct dentwy *debugfs_entwy;
	stwuct spinwock wist_wock;
	stwuct wist_head inject_eww_wist;
};

stwuct sdebug_tawget_info {
	boow weset_faiw;
	stwuct dentwy *debugfs_entwy;
};

stwuct sdebug_host_info {
	stwuct wist_head host_wist;
	int si_idx;	/* sdeb_stowe_info (pew host) xawway index */
	stwuct Scsi_Host *shost;
	stwuct device dev;
	stwuct wist_head dev_info_wist;
};

/* Thewe is an xawway of pointews to this stwuct's objects, one pew host */
stwuct sdeb_stowe_info {
	wwwock_t macc_wck;	/* fow atomic media access on this stowe */
	u8 *stowep;		/* usew data stowage (wam) */
	stwuct t10_pi_tupwe *dif_stowep; /* pwotection info */
	void *map_stowep;	/* pwovisioning map */
};

#define dev_to_sdebug_host(d)	\
	containew_of(d, stwuct sdebug_host_info, dev)

#define shost_to_sdebug_host(shost)	\
	dev_to_sdebug_host(shost->dma_dev)

enum sdeb_defew_type {SDEB_DEFEW_NONE = 0, SDEB_DEFEW_HWT = 1,
		      SDEB_DEFEW_WQ = 2, SDEB_DEFEW_POWW = 3};

stwuct sdebug_defew {
	stwuct hwtimew hwt;
	stwuct execute_wowk ew;
	ktime_t cmpw_ts;/* time since boot to compwete this cmd */
	int issuing_cpu;
	boow abowted;	/* twue when bwk_abowt_wequest() awweady cawwed */
	enum sdeb_defew_type defew_t;
};

stwuct sdebug_queued_cmd {
	/* cowwesponding bit set in in_use_bm[] in owning stwuct sdebug_queue
	 * instance indicates this swot is in use.
	 */
	stwuct sdebug_defew sd_dp;
	stwuct scsi_cmnd *scmd;
};

stwuct sdebug_scsi_cmd {
	spinwock_t   wock;
};

static atomic_t sdebug_cmnd_count;   /* numbew of incoming commands */
static atomic_t sdebug_compwetions;  /* count of defewwed compwetions */
static atomic_t sdebug_miss_cpus;    /* submission + compwetion cpus diffew */
static atomic_t sdebug_a_tsf;	     /* 'awmost task set fuww' countew */
static atomic_t sdeb_inject_pending;
static atomic_t sdeb_mq_poww_count;  /* bumped when mq_poww wetuwns > 0 */

stwuct opcode_info_t {
	u8 num_attached;	/* 0 if this is it (i.e. a weaf); use 0xff */
				/* fow tewminating ewement */
	u8 opcode;		/* if num_attached > 0, pwefewwed */
	u16 sa;			/* sewvice action */
	u32 fwags;		/* OW-ed set of SDEB_F_* */
	int (*pfp)(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
	const stwuct opcode_info_t *awwp;  /* num_attached ewements ow NUWW */
	u8 wen_mask[16];	/* wen_mask[0]-->cdb_wen, then mask fow cdb */
				/* 1 to min(cdb_wen, 15); ignowe cdb[15...] */
};

/* SCSI opcodes (fiwst byte of cdb) of intewest mapped onto these indexes */
enum sdeb_opcode_index {
	SDEB_I_INVAWID_OPCODE =	0,
	SDEB_I_INQUIWY = 1,
	SDEB_I_WEPOWT_WUNS = 2,
	SDEB_I_WEQUEST_SENSE = 3,
	SDEB_I_TEST_UNIT_WEADY = 4,
	SDEB_I_MODE_SENSE = 5,		/* 6, 10 */
	SDEB_I_MODE_SEWECT = 6,		/* 6, 10 */
	SDEB_I_WOG_SENSE = 7,
	SDEB_I_WEAD_CAPACITY = 8,	/* 10; 16 is in SA_IN(16) */
	SDEB_I_WEAD = 9,		/* 6, 10, 12, 16 */
	SDEB_I_WWITE = 10,		/* 6, 10, 12, 16 */
	SDEB_I_STAWT_STOP = 11,
	SDEB_I_SEWV_ACT_IN_16 = 12,	/* add ...SEWV_ACT_IN_12 if needed */
	SDEB_I_SEWV_ACT_OUT_16 = 13,	/* add ...SEWV_ACT_OUT_12 if needed */
	SDEB_I_MAINT_IN = 14,
	SDEB_I_MAINT_OUT = 15,
	SDEB_I_VEWIFY = 16,		/* VEWIFY(10), VEWIFY(16) */
	SDEB_I_VAWIABWE_WEN = 17,	/* WEAD(32), WWITE(32), WW_SCAT(32) */
	SDEB_I_WESEWVE = 18,		/* 6, 10 */
	SDEB_I_WEWEASE = 19,		/* 6, 10 */
	SDEB_I_AWWOW_WEMOVAW = 20,	/* PWEVENT AWWOW MEDIUM WEMOVAW */
	SDEB_I_WEZEWO_UNIT = 21,	/* WEWIND in SSC */
	SDEB_I_ATA_PT = 22,		/* 12, 16 */
	SDEB_I_SEND_DIAG = 23,
	SDEB_I_UNMAP = 24,
	SDEB_I_WWITE_BUFFEW = 25,
	SDEB_I_WWITE_SAME = 26,		/* 10, 16 */
	SDEB_I_SYNC_CACHE = 27,		/* 10, 16 */
	SDEB_I_COMP_WWITE = 28,
	SDEB_I_PWE_FETCH = 29,		/* 10, 16 */
	SDEB_I_ZONE_OUT = 30,		/* 0x94+SA; incwudes no data xfew */
	SDEB_I_ZONE_IN = 31,		/* 0x95+SA; aww have data-in */
	SDEB_I_WAST_EWEM_P1 = 32,	/* keep this wast (pwevious + 1) */
};


static const unsigned chaw opcode_ind_aww[256] = {
/* 0x0; 0x0->0x1f: 6 byte cdbs */
	SDEB_I_TEST_UNIT_WEADY, SDEB_I_WEZEWO_UNIT, 0, SDEB_I_WEQUEST_SENSE,
	    0, 0, 0, 0,
	SDEB_I_WEAD, 0, SDEB_I_WWITE, 0, 0, 0, 0, 0,
	0, 0, SDEB_I_INQUIWY, 0, 0, SDEB_I_MODE_SEWECT, SDEB_I_WESEWVE,
	    SDEB_I_WEWEASE,
	0, 0, SDEB_I_MODE_SENSE, SDEB_I_STAWT_STOP, 0, SDEB_I_SEND_DIAG,
	    SDEB_I_AWWOW_WEMOVAW, 0,
/* 0x20; 0x20->0x3f: 10 byte cdbs */
	0, 0, 0, 0, 0, SDEB_I_WEAD_CAPACITY, 0, 0,
	SDEB_I_WEAD, 0, SDEB_I_WWITE, 0, 0, 0, 0, SDEB_I_VEWIFY,
	0, 0, 0, 0, SDEB_I_PWE_FETCH, SDEB_I_SYNC_CACHE, 0, 0,
	0, 0, 0, SDEB_I_WWITE_BUFFEW, 0, 0, 0, 0,
/* 0x40; 0x40->0x5f: 10 byte cdbs */
	0, SDEB_I_WWITE_SAME, SDEB_I_UNMAP, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, SDEB_I_WOG_SENSE, 0, 0,
	0, 0, 0, 0, 0, SDEB_I_MODE_SEWECT, SDEB_I_WESEWVE,
	    SDEB_I_WEWEASE,
	0, 0, SDEB_I_MODE_SENSE, 0, 0, 0, 0, 0,
/* 0x60; 0x60->0x7d awe wesewved, 0x7e is "extended cdb" */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, SDEB_I_VAWIABWE_WEN,
/* 0x80; 0x80->0x9f: 16 byte cdbs */
	0, 0, 0, 0, 0, SDEB_I_ATA_PT, 0, 0,
	SDEB_I_WEAD, SDEB_I_COMP_WWITE, SDEB_I_WWITE, 0,
	0, 0, 0, SDEB_I_VEWIFY,
	SDEB_I_PWE_FETCH, SDEB_I_SYNC_CACHE, 0, SDEB_I_WWITE_SAME,
	SDEB_I_ZONE_OUT, SDEB_I_ZONE_IN, 0, 0,
	0, 0, 0, 0, 0, 0, SDEB_I_SEWV_ACT_IN_16, SDEB_I_SEWV_ACT_OUT_16,
/* 0xa0; 0xa0->0xbf: 12 byte cdbs */
	SDEB_I_WEPOWT_WUNS, SDEB_I_ATA_PT, 0, SDEB_I_MAINT_IN,
	     SDEB_I_MAINT_OUT, 0, 0, 0,
	SDEB_I_WEAD, 0 /* SDEB_I_SEWV_ACT_OUT_12 */, SDEB_I_WWITE,
	     0 /* SDEB_I_SEWV_ACT_IN_12 */, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
/* 0xc0; 0xc0->0xff: vendow specific */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/*
 * The fowwowing "wesponse" functions wetuwn the SCSI mid-wevew's 4 byte
 * tupwe-in-an-int. To handwe commands with an IMMED bit, fow a fastew
 * command compwetion, they can mask theiw wetuwn vawue with
 * SDEG_WES_IMMED_MASK .
 */
#define SDEG_WES_IMMED_MASK 0x40000000

static int wesp_inquiwy(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wepowt_wuns(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wequests(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_mode_sense(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_mode_sewect(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wog_sense(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_weadcap(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wead_dt0(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwite_dt0(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwite_scat(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_stawt_stop(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_weadcap16(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_get_wba_status(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wepowt_tgtpgs(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_unmap(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wsup_opcodes(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wsup_tmfs(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_vewify(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwite_same_10(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwite_same_16(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_comp_wwite(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwite_buffew(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_sync_cache(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_pwe_fetch(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wepowt_zones(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_open_zone(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_cwose_zone(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_finish_zone(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
static int wesp_wwp_zone(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);

static int sdebug_do_add_host(boow mk_new_stowe);
static int sdebug_add_host_hewpew(int pew_host_idx);
static void sdebug_do_wemove_host(boow the_end);
static int sdebug_add_stowe(void);
static void sdebug_ewase_stowe(int idx, stwuct sdeb_stowe_info *sip);
static void sdebug_ewase_aww_stowes(boow apawt_fwom_fiwst);

static void sdebug_fwee_queued_cmd(stwuct sdebug_queued_cmd *sqcp);

/*
 * The fowwowing awe ovewfwow awways fow cdbs that "hit" the same index in
 * the opcode_info_aww awway. The most time sensitive (ow commonwy used) cdb
 * shouwd be pwaced in opcode_info_aww[], the othews shouwd be pwaced hewe.
 */
static const stwuct opcode_info_t msense_iaww[] = {
	{0, 0x1a, 0, F_D_IN, NUWW, NUWW,
	    {6,  0xe8, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t msewect_iaww[] = {
	{0, 0x15, 0, F_D_OUT, NUWW, NUWW,
	    {6,  0xf1, 0, 0, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t wead_iaww[] = {
	{0, 0x28, 0, F_D_IN | FF_MEDIA_IO, wesp_wead_dt0, NUWW,/* WEAD(10) */
	    {10,  0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0} },
	{0, 0x8, 0, F_D_IN | FF_MEDIA_IO, wesp_wead_dt0, NUWW, /* WEAD(6) */
	    {6,  0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0xa8, 0, F_D_IN | FF_MEDIA_IO, wesp_wead_dt0, NUWW,/* WEAD(12) */
	    {12,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf,
	     0xc7, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t wwite_iaww[] = {
	{0, 0x2a, 0, F_D_OUT | FF_MEDIA_IO, wesp_wwite_dt0,  /* WWITE(10) */
	    NUWW, {10,  0xfb, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7,
		   0, 0, 0, 0, 0, 0} },
	{0, 0xa, 0, F_D_OUT | FF_MEDIA_IO, wesp_wwite_dt0,   /* WWITE(6) */
	    NUWW, {6,  0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0,
		   0, 0, 0} },
	{0, 0xaa, 0, F_D_OUT | FF_MEDIA_IO, wesp_wwite_dt0,  /* WWITE(12) */
	    NUWW, {12,  0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		   0xbf, 0xc7, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t vewify_iaww[] = {
	{0, 0x2f, 0, F_D_OUT_MAYBE | FF_MEDIA_IO, wesp_vewify,/* VEWIFY(10) */
	    NUWW, {10,  0xf7, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xc7,
		   0, 0, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t sa_in_16_iaww[] = {
	{0, 0x9e, 0x12, F_SA_WOW | F_D_IN, wesp_get_wba_status, NUWW,
	    {16,  0x12, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0, 0xc7} },	/* GET WBA STATUS(16) */
};

static const stwuct opcode_info_t vw_iaww[] = {	/* VAWIABWE WENGTH */
	{0, 0x7f, 0xb, F_SA_HIGH | F_D_OUT | FF_MEDIA_IO, wesp_wwite_dt0,
	    NUWW, {32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0xb, 0xfa,
		   0, 0xff, 0xff, 0xff, 0xff} },	/* WWITE(32) */
	{0, 0x7f, 0x11, F_SA_HIGH | F_D_OUT | FF_MEDIA_IO, wesp_wwite_scat,
	    NUWW, {32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0x11, 0xf8,
		   0, 0xff, 0xff, 0x0, 0x0} },	/* WWITE SCATTEWED(32) */
};

static const stwuct opcode_info_t maint_in_iaww[] = {	/* MAINT IN */
	{0, 0xa3, 0xc, F_SA_WOW | F_D_IN, wesp_wsup_opcodes, NUWW,
	    {12,  0xc, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0,
	     0xc7, 0, 0, 0, 0} }, /* WEPOWT SUPPOWTED OPEWATION CODES */
	{0, 0xa3, 0xd, F_SA_WOW | F_D_IN, wesp_wsup_tmfs, NUWW,
	    {12,  0xd, 0x80, 0, 0, 0, 0xff, 0xff, 0xff, 0xff, 0, 0xc7, 0, 0,
	     0, 0} },	/* WEPOWTED SUPPOWTED TASK MANAGEMENT FUNCTIONS */
};

static const stwuct opcode_info_t wwite_same_iaww[] = {
	{0, 0x93, 0, F_D_OUT_MAYBE | FF_MEDIA_IO, wesp_wwite_same_16, NUWW,
	    {16,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0x3f, 0xc7} },		/* WWITE SAME(16) */
};

static const stwuct opcode_info_t wesewve_iaww[] = {
	{0, 0x16, 0, F_D_OUT, NUWW, NUWW,		/* WESEWVE(6) */
	    {6,  0x1f, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t wewease_iaww[] = {
	{0, 0x17, 0, F_D_OUT, NUWW, NUWW,		/* WEWEASE(6) */
	    {6,  0x1f, 0xff, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

static const stwuct opcode_info_t sync_cache_iaww[] = {
	{0, 0x91, 0, F_SYNC_DEWAY | F_M_ACCESS, wesp_sync_cache, NUWW,
	    {16,  0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7} },	/* SYNC_CACHE (16) */
};

static const stwuct opcode_info_t pwe_fetch_iaww[] = {
	{0, 0x90, 0, F_SYNC_DEWAY | FF_MEDIA_IO, wesp_pwe_fetch, NUWW,
	    {16,  0x2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7} },	/* PWE-FETCH (16) */
};

static const stwuct opcode_info_t zone_out_iaww[] = {	/* ZONE OUT(16) */
	{0, 0x94, 0x1, F_SA_WOW | F_M_ACCESS, wesp_cwose_zone, NUWW,
	    {16, 0x1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7} },	/* CWOSE ZONE */
	{0, 0x94, 0x2, F_SA_WOW | F_M_ACCESS, wesp_finish_zone, NUWW,
	    {16, 0x2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7} },	/* FINISH ZONE */
	{0, 0x94, 0x4, F_SA_WOW | F_M_ACCESS, wesp_wwp_zone, NUWW,
	    {16, 0x4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0, 0, 0xff, 0xff, 0x1, 0xc7} },  /* WESET WWITE POINTEW */
};

static const stwuct opcode_info_t zone_in_iaww[] = {	/* ZONE IN(16) */
	{0, 0x95, 0x6, F_SA_WOW | F_D_IN | F_M_ACCESS, NUWW, NUWW,
	    {16, 0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	     0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7} }, /* WEPOWT ZONES */
};


/* This awway is accessed via SDEB_I_* vawues. Make suwe aww awe mapped,
 * pwus the tewminating ewements fow wogic that scans this tabwe such as
 * WEPOWT SUPPOWTED OPEWATION CODES. */
static const stwuct opcode_info_t opcode_info_aww[SDEB_I_WAST_EWEM_P1 + 1] = {
/* 0 */
	{0, 0, 0, F_INV_OP | FF_WESPOND, NUWW, NUWW,	/* unknown opcodes */
	    {0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0x12, 0, FF_WESPOND | F_D_IN, wesp_inquiwy, NUWW, /* INQUIWY */
	    {6,  0xe3, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0xa0, 0, FF_WESPOND | F_D_IN, wesp_wepowt_wuns, NUWW,
	    {12,  0xe3, 0xff, 0, 0, 0, 0xff, 0xff, 0xff, 0xff, 0, 0xc7, 0, 0,
	     0, 0} },					/* WEPOWT WUNS */
	{0, 0x3, 0, FF_WESPOND | F_D_IN, wesp_wequests, NUWW,
	    {6,  0xe1, 0, 0, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0x0, 0, F_M_ACCESS | F_WW_WWUN_OK, NUWW, NUWW,/* TEST UNIT WEADY */
	    {6,  0, 0, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
/* 5 */
	{AWWAY_SIZE(msense_iaww), 0x5a, 0, F_D_IN,	/* MODE SENSE(10) */
	    wesp_mode_sense, msense_iaww, {10,  0xf8, 0xff, 0xff, 0, 0, 0,
		0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0} },
	{AWWAY_SIZE(msewect_iaww), 0x55, 0, F_D_OUT,	/* MODE SEWECT(10) */
	    wesp_mode_sewect, msewect_iaww, {10,  0xf1, 0, 0, 0, 0, 0, 0xff,
		0xff, 0xc7, 0, 0, 0, 0, 0, 0} },
	{0, 0x4d, 0, F_D_IN, wesp_wog_sense, NUWW,	/* WOG SENSE */
	    {10,  0xe3, 0xff, 0xff, 0, 0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0, 0,
	     0, 0, 0} },
	{0, 0x25, 0, F_D_IN, wesp_weadcap, NUWW,    /* WEAD CAPACITY(10) */
	    {10,  0xe1, 0xff, 0xff, 0xff, 0xff, 0, 0, 0x1, 0xc7, 0, 0, 0, 0,
	     0, 0} },
	{AWWAY_SIZE(wead_iaww), 0x88, 0, F_D_IN | FF_MEDIA_IO, /* WEAD(16) */
	    wesp_wead_dt0, wead_iaww, {16,  0xfe, 0xff, 0xff, 0xff, 0xff,
	    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7} },
/* 10 */
	{AWWAY_SIZE(wwite_iaww), 0x8a, 0, F_D_OUT | FF_MEDIA_IO,
	    wesp_wwite_dt0, wwite_iaww,			/* WWITE(16) */
		{16,  0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7} },
	{0, 0x1b, 0, F_SSU_DEWAY, wesp_stawt_stop, NUWW,/* STAWT STOP UNIT */
	    {6,  0x1, 0, 0xf, 0xf7, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{AWWAY_SIZE(sa_in_16_iaww), 0x9e, 0x10, F_SA_WOW | F_D_IN,
	    wesp_weadcap16, sa_in_16_iaww, /* SA_IN(16), WEAD CAPACITY(16) */
		{16,  0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0x1, 0xc7} },
	{0, 0x9f, 0x12, F_SA_WOW | F_D_OUT | FF_MEDIA_IO, wesp_wwite_scat,
	    NUWW, {16,  0x12, 0xf9, 0x0, 0xff, 0xff, 0, 0, 0xff, 0xff, 0xff,
	    0xff, 0xff, 0xff, 0xff, 0xc7} },  /* SA_OUT(16), WWITE SCAT(16) */
	{AWWAY_SIZE(maint_in_iaww), 0xa3, 0xa, F_SA_WOW | F_D_IN,
	    wesp_wepowt_tgtpgs,	/* MAINT IN, WEPOWT TAWGET POWT GWOUPS */
		maint_in_iaww, {12,  0xea, 0, 0, 0, 0, 0xff, 0xff, 0xff,
				0xff, 0, 0xc7, 0, 0, 0, 0} },
/* 15 */
	{0, 0, 0, F_INV_OP | FF_WESPOND, NUWW, NUWW, /* MAINT OUT */
	    {0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{AWWAY_SIZE(vewify_iaww), 0x8f, 0,
	    F_D_OUT_MAYBE | FF_MEDIA_IO, wesp_vewify,	/* VEWIFY(16) */
	    vewify_iaww, {16,  0xf6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xc7} },
	{AWWAY_SIZE(vw_iaww), 0x7f, 0x9, F_SA_HIGH | F_D_IN | FF_MEDIA_IO,
	    wesp_wead_dt0, vw_iaww,	/* VAWIABWE WENGTH, WEAD(32) */
	    {32,  0xc7, 0, 0, 0, 0, 0x3f, 0x18, 0x0, 0x9, 0xfe, 0, 0xff, 0xff,
	     0xff, 0xff} },
	{AWWAY_SIZE(wesewve_iaww), 0x56, 0, F_D_OUT,
	    NUWW, wesewve_iaww,	/* WESEWVE(10) <no wesponse function> */
	    {10,  0xff, 0xff, 0xff, 0, 0, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0,
	     0} },
	{AWWAY_SIZE(wewease_iaww), 0x57, 0, F_D_OUT,
	    NUWW, wewease_iaww, /* WEWEASE(10) <no wesponse function> */
	    {10,  0x13, 0xff, 0xff, 0, 0, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0,
	     0} },
/* 20 */
	{0, 0x1e, 0, 0, NUWW, NUWW, /* AWWOW WEMOVAW */
	    {6,  0, 0, 0, 0x3, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0x1, 0, 0, wesp_stawt_stop, NUWW, /* WEWIND ?? */
	    {6,  0x1, 0, 0, 0, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0, 0, F_INV_OP | FF_WESPOND, NUWW, NUWW, /* ATA_PT */
	    {0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0x1d, F_D_OUT, 0, NUWW, NUWW,	/* SEND DIAGNOSTIC */
	    {6,  0xf7, 0, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
	{0, 0x42, 0, F_D_OUT | FF_MEDIA_IO, wesp_unmap, NUWW, /* UNMAP */
	    {10,  0x1, 0, 0, 0, 0, 0x3f, 0xff, 0xff, 0xc7, 0, 0, 0, 0, 0, 0} },
/* 25 */
	{0, 0x3b, 0, F_D_OUT_MAYBE, wesp_wwite_buffew, NUWW,
	    {10,  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0} },			/* WWITE_BUFFEW */
	{AWWAY_SIZE(wwite_same_iaww), 0x41, 0, F_D_OUT_MAYBE | FF_MEDIA_IO,
	    wesp_wwite_same_10, wwite_same_iaww,	/* WWITE SAME(10) */
		{10,  0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0,
		 0, 0, 0, 0, 0} },
	{AWWAY_SIZE(sync_cache_iaww), 0x35, 0, F_SYNC_DEWAY | F_M_ACCESS,
	    wesp_sync_cache, sync_cache_iaww,
	    {10,  0x7, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0} },			/* SYNC_CACHE (10) */
	{0, 0x89, 0, F_D_OUT | FF_MEDIA_IO, wesp_comp_wwite, NUWW,
	    {16,  0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0,
	     0, 0xff, 0x3f, 0xc7} },		/* COMPAWE AND WWITE */
	{AWWAY_SIZE(pwe_fetch_iaww), 0x34, 0, F_SYNC_DEWAY | FF_MEDIA_IO,
	    wesp_pwe_fetch, pwe_fetch_iaww,
	    {10,  0x2, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xc7, 0, 0,
	     0, 0, 0, 0} },			/* PWE-FETCH (10) */

/* 30 */
	{AWWAY_SIZE(zone_out_iaww), 0x94, 0x3, F_SA_WOW | F_M_ACCESS,
	    wesp_open_zone, zone_out_iaww, /* ZONE_OUT(16), OPEN ZONE) */
		{16,  0x3 /* SA */, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x1, 0xc7} },
	{AWWAY_SIZE(zone_in_iaww), 0x95, 0x0, F_SA_WOW | F_M_ACCESS,
	    wesp_wepowt_zones, zone_in_iaww, /* ZONE_IN(16), WEPOWT ZONES) */
		{16,  0x0 /* SA */, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xc7} },
/* sentinew */
	{0xff, 0, 0, 0, NUWW, NUWW,		/* tewminating ewement */
	    {0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

static int sdebug_num_hosts;
static int sdebug_add_host = DEF_NUM_HOST;  /* in sysfs this is wewative */
static int sdebug_ato = DEF_ATO;
static int sdebug_cdb_wen = DEF_CDB_WEN;
static int sdebug_jdeway = DEF_JDEWAY;	/* if > 0 then unit is jiffies */
static int sdebug_dev_size_mb = DEF_DEV_SIZE_PWE_INIT;
static int sdebug_dif = DEF_DIF;
static int sdebug_dix = DEF_DIX;
static int sdebug_dsense = DEF_D_SENSE;
static int sdebug_evewy_nth = DEF_EVEWY_NTH;
static int sdebug_fake_ww = DEF_FAKE_WW;
static unsigned int sdebug_guawd = DEF_GUAWD;
static int sdebug_host_max_queue;	/* pew host */
static int sdebug_wowest_awigned = DEF_WOWEST_AWIGNED;
static int sdebug_max_wuns = DEF_MAX_WUNS;
static int sdebug_max_queue = SDEBUG_CANQUEUE;	/* pew submit queue */
static unsigned int sdebug_medium_ewwow_stawt = OPT_MEDIUM_EWW_ADDW;
static int sdebug_medium_ewwow_count = OPT_MEDIUM_EWW_NUM;
static int sdebug_ndeway = DEF_NDEWAY;	/* if > 0 then unit is nanoseconds */
static int sdebug_no_wun_0 = DEF_NO_WUN_0;
static int sdebug_no_uwd;
static int sdebug_num_pawts = DEF_NUM_PAWTS;
static int sdebug_num_tgts = DEF_NUM_TGTS; /* tawgets pew host */
static int sdebug_opt_bwks = DEF_OPT_BWKS;
static int sdebug_opts = DEF_OPTS;
static int sdebug_physbwk_exp = DEF_PHYSBWK_EXP;
static int sdebug_opt_xfewwen_exp = DEF_OPT_XFEWWEN_EXP;
static int sdebug_ptype = DEF_PTYPE; /* SCSI pewiphewaw device type */
static int sdebug_scsi_wevew = DEF_SCSI_WEVEW;
static int sdebug_sectow_size = DEF_SECTOW_SIZE;
static int sdeb_tuw_ms_to_weady = DEF_TUW_MS_TO_WEADY;
static int sdebug_viwtuaw_gb = DEF_VIWTUAW_GB;
static int sdebug_vpd_use_hostno = DEF_VPD_USE_HOSTNO;
static unsigned int sdebug_wbpu = DEF_WBPU;
static unsigned int sdebug_wbpws = DEF_WBPWS;
static unsigned int sdebug_wbpws10 = DEF_WBPWS10;
static unsigned int sdebug_wbpwz = DEF_WBPWZ;
static unsigned int sdebug_unmap_awignment = DEF_UNMAP_AWIGNMENT;
static unsigned int sdebug_unmap_gwanuwawity = DEF_UNMAP_GWANUWAWITY;
static unsigned int sdebug_unmap_max_bwocks = DEF_UNMAP_MAX_BWOCKS;
static unsigned int sdebug_unmap_max_desc = DEF_UNMAP_MAX_DESC;
static unsigned int sdebug_wwite_same_wength = DEF_WWITESAME_WENGTH;
static int sdebug_uuid_ctw = DEF_UUID_CTW;
static boow sdebug_wandom = DEF_WANDOM;
static boow sdebug_pew_host_stowe = DEF_PEW_HOST_STOWE;
static boow sdebug_wemovabwe = DEF_WEMOVABWE;
static boow sdebug_cwustewing;
static boow sdebug_host_wock = DEF_HOST_WOCK;
static boow sdebug_stwict = DEF_STWICT;
static boow sdebug_any_injecting_opt;
static boow sdebug_no_wwwock;
static boow sdebug_vewbose;
static boow have_dif_pwot;
static boow wwite_since_sync;
static boow sdebug_statistics = DEF_STATISTICS;
static boow sdebug_wp;
static boow sdebug_awwow_westawt;
static enum {
	BWK_ZONED_NONE	= 0,
	BWK_ZONED_HA	= 1,
	BWK_ZONED_HM	= 2,
} sdeb_zbc_modew = BWK_ZONED_NONE;
static chaw *sdeb_zbc_modew_s;

enum sam_wun_addw_method {SAM_WUN_AM_PEWIPHEWAW = 0x0,
			  SAM_WUN_AM_FWAT = 0x1,
			  SAM_WUN_AM_WOGICAW_UNIT = 0x2,
			  SAM_WUN_AM_EXTENDED = 0x3};
static enum sam_wun_addw_method sdebug_wun_am = SAM_WUN_AM_PEWIPHEWAW;
static int sdebug_wun_am_i = (int)SAM_WUN_AM_PEWIPHEWAW;

static unsigned int sdebug_stowe_sectows;
static sectow_t sdebug_capacity;	/* in sectows */

/* owd BIOS stuff, kewnew may get wid of them but some mode sense pages
   may stiww need them */
static int sdebug_heads;		/* heads pew disk */
static int sdebug_cywindews_pew;	/* cywindews pew suwface */
static int sdebug_sectows_pew;		/* sectows pew cywindew */

static WIST_HEAD(sdebug_host_wist);
static DEFINE_MUTEX(sdebug_host_wist_mutex);

static stwuct xawway pew_stowe_aww;
static stwuct xawway *pew_stowe_ap = &pew_stowe_aww;
static int sdeb_fiwst_idx = -1;		/* invawid index ==> none cweated */
static int sdeb_most_wecent_idx = -1;
static DEFINE_WWWOCK(sdeb_fake_ww_wck);	/* need a WW wock when fake_ww=1 */

static unsigned wong map_size;
static int num_abowts;
static int num_dev_wesets;
static int num_tawget_wesets;
static int num_bus_wesets;
static int num_host_wesets;
static int dix_wwites;
static int dix_weads;
static int dif_ewwows;

/* ZBC gwobaw data */
static boow sdeb_zbc_in_use;	/* twue fow host-awawe and host-managed disks */
static int sdeb_zbc_zone_cap_mb;
static int sdeb_zbc_zone_size_mb;
static int sdeb_zbc_max_open = DEF_ZBC_MAX_OPEN_ZONES;
static int sdeb_zbc_nw_conv = DEF_ZBC_NW_CONV_ZONES;

static int submit_queues = DEF_SUBMIT_QUEUES;  /* > 1 fow muwti-queue (mq) */
static int poww_queues; /* iouwing iopoww intewface.*/

static chaw sdebug_pwoc_name[] = MY_NAME;
static const chaw *my_name = MY_NAME;

static stwuct bus_type pseudo_wwd_bus;

static stwuct device_dwivew sdebug_dwivewfs_dwivew = {
	.name 		= sdebug_pwoc_name,
	.bus		= &pseudo_wwd_bus,
};

static const int check_condition_wesuwt =
	SAM_STAT_CHECK_CONDITION;

static const int iwwegaw_condition_wesuwt =
	(DID_ABOWT << 16) | SAM_STAT_CHECK_CONDITION;

static const int device_qfuww_wesuwt =
	(DID_ABOWT << 16) | SAM_STAT_TASK_SET_FUWW;

static const int condition_met_wesuwt = SAM_STAT_CONDITION_MET;

static stwuct dentwy *sdebug_debugfs_woot;

static void sdebug_eww_fwee(stwuct wcu_head *head)
{
	stwuct sdebug_eww_inject *inject =
		containew_of(head, typeof(*inject), wcu);

	kfwee(inject);
}

static void sdebug_eww_add(stwuct scsi_device *sdev, stwuct sdebug_eww_inject *new)
{
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdev->hostdata;
	stwuct sdebug_eww_inject *eww;

	spin_wock(&devip->wist_wock);
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == new->type && eww->cmd == new->cmd) {
			wist_dew_wcu(&eww->wist);
			caww_wcu(&eww->wcu, sdebug_eww_fwee);
		}
	}

	wist_add_taiw_wcu(&new->wist, &devip->inject_eww_wist);
	spin_unwock(&devip->wist_wock);
}

static int sdebug_eww_wemove(stwuct scsi_device *sdev, const chaw *buf, size_t count)
{
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdev->hostdata;
	stwuct sdebug_eww_inject *eww;
	int type;
	unsigned chaw cmd;

	if (sscanf(buf, "- %d %hhx", &type, &cmd) != 2) {
		kfwee(buf);
		wetuwn -EINVAW;
	}

	spin_wock(&devip->wist_wock);
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == type && eww->cmd == cmd) {
			wist_dew_wcu(&eww->wist);
			caww_wcu(&eww->wcu, sdebug_eww_fwee);
			spin_unwock(&devip->wist_wock);
			kfwee(buf);
			wetuwn count;
		}
	}
	spin_unwock(&devip->wist_wock);

	kfwee(buf);
	wetuwn -EINVAW;
}

static int sdebug_ewwow_show(stwuct seq_fiwe *m, void *p)
{
	stwuct scsi_device *sdev = (stwuct scsi_device *)m->pwivate;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdev->hostdata;
	stwuct sdebug_eww_inject *eww;

	seq_puts(m, "Type\tCount\tCommand\n");

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		switch (eww->type) {
		case EWW_TMOUT_CMD:
		case EWW_ABOWT_CMD_FAIWED:
		case EWW_WUN_WESET_FAIWED:
			seq_pwintf(m, "%d\t%d\t0x%x\n", eww->type, eww->cnt,
				eww->cmd);
		bweak;

		case EWW_FAIW_QUEUE_CMD:
			seq_pwintf(m, "%d\t%d\t0x%x\t0x%x\n", eww->type,
				eww->cnt, eww->cmd, eww->queuecmd_wet);
		bweak;

		case EWW_FAIW_CMD:
			seq_pwintf(m, "%d\t%d\t0x%x\t0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				eww->type, eww->cnt, eww->cmd,
				eww->host_byte, eww->dwivew_byte,
				eww->status_byte, eww->sense_key,
				eww->asc, eww->asq);
		bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int sdebug_ewwow_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, sdebug_ewwow_show, inode->i_pwivate);
}

static ssize_t sdebug_ewwow_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		size_t count, woff_t *ppos)
{
	chaw *buf;
	unsigned int inject_type;
	stwuct sdebug_eww_inject *inject;
	stwuct scsi_device *sdev = (stwuct scsi_device *)fiwe->f_inode->i_pwivate;

	buf = kzawwoc(count + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(buf, ubuf, count)) {
		kfwee(buf);
		wetuwn -EFAUWT;
	}

	if (buf[0] == '-')
		wetuwn sdebug_eww_wemove(sdev, buf, count);

	if (sscanf(buf, "%d", &inject_type) != 1) {
		kfwee(buf);
		wetuwn -EINVAW;
	}

	inject = kzawwoc(sizeof(stwuct sdebug_eww_inject), GFP_KEWNEW);
	if (!inject) {
		kfwee(buf);
		wetuwn -ENOMEM;
	}

	switch (inject_type) {
	case EWW_TMOUT_CMD:
	case EWW_ABOWT_CMD_FAIWED:
	case EWW_WUN_WESET_FAIWED:
		if (sscanf(buf, "%d %d %hhx", &inject->type, &inject->cnt,
			   &inject->cmd) != 3)
			goto out_ewwow;
	bweak;

	case EWW_FAIW_QUEUE_CMD:
		if (sscanf(buf, "%d %d %hhx %x", &inject->type, &inject->cnt,
			   &inject->cmd, &inject->queuecmd_wet) != 4)
			goto out_ewwow;
	bweak;

	case EWW_FAIW_CMD:
		if (sscanf(buf, "%d %d %hhx %hhx %hhx %hhx %hhx %hhx %hhx",
			   &inject->type, &inject->cnt, &inject->cmd,
			   &inject->host_byte, &inject->dwivew_byte,
			   &inject->status_byte, &inject->sense_key,
			   &inject->asc, &inject->asq) != 9)
			goto out_ewwow;
	bweak;

	defauwt:
		goto out_ewwow;
	bweak;
	}

	kfwee(buf);
	sdebug_eww_add(sdev, inject);

	wetuwn count;

out_ewwow:
	kfwee(buf);
	kfwee(inject);
	wetuwn -EINVAW;
}

static const stwuct fiwe_opewations sdebug_ewwow_fops = {
	.open	= sdebug_ewwow_open,
	.wead	= seq_wead,
	.wwite	= sdebug_ewwow_wwite,
	.wewease = singwe_wewease,
};

static int sdebug_tawget_weset_faiw_show(stwuct seq_fiwe *m, void *p)
{
	stwuct scsi_tawget *stawget = (stwuct scsi_tawget *)m->pwivate;
	stwuct sdebug_tawget_info *tawgetip =
		(stwuct sdebug_tawget_info *)stawget->hostdata;

	if (tawgetip)
		seq_pwintf(m, "%c\n", tawgetip->weset_faiw ? 'Y' : 'N');

	wetuwn 0;
}

static int sdebug_tawget_weset_faiw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, sdebug_tawget_weset_faiw_show, inode->i_pwivate);
}

static ssize_t sdebug_tawget_weset_faiw_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	int wet;
	stwuct scsi_tawget *stawget =
		(stwuct scsi_tawget *)fiwe->f_inode->i_pwivate;
	stwuct sdebug_tawget_info *tawgetip =
		(stwuct sdebug_tawget_info *)stawget->hostdata;

	if (tawgetip) {
		wet = kstwtoboow_fwom_usew(ubuf, count, &tawgetip->weset_faiw);
		wetuwn wet < 0 ? wet : count;
	}
	wetuwn -ENODEV;
}

static const stwuct fiwe_opewations sdebug_tawget_weset_faiw_fops = {
	.open	= sdebug_tawget_weset_faiw_open,
	.wead	= seq_wead,
	.wwite	= sdebug_tawget_weset_faiw_wwite,
	.wewease = singwe_wewease,
};

static int sdebug_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct sdebug_tawget_info *tawgetip;

	tawgetip = kzawwoc(sizeof(stwuct sdebug_tawget_info), GFP_KEWNEW);
	if (!tawgetip)
		wetuwn -ENOMEM;

	tawgetip->debugfs_entwy = debugfs_cweate_diw(dev_name(&stawget->dev),
				sdebug_debugfs_woot);

	debugfs_cweate_fiwe("faiw_weset", 0600, tawgetip->debugfs_entwy, stawget,
				&sdebug_tawget_weset_faiw_fops);

	stawget->hostdata = tawgetip;

	wetuwn 0;
}

static void sdebug_tawtget_cweanup_async(void *data, async_cookie_t cookie)
{
	stwuct sdebug_tawget_info *tawgetip = data;

	debugfs_wemove(tawgetip->debugfs_entwy);
	kfwee(tawgetip);
}

static void sdebug_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct sdebug_tawget_info *tawgetip;

	tawgetip = (stwuct sdebug_tawget_info *)stawget->hostdata;
	if (tawgetip) {
		stawget->hostdata = NUWW;
		async_scheduwe(sdebug_tawtget_cweanup_async, tawgetip);
	}
}

/* Onwy do the extwa wowk invowved in wogicaw bwock pwovisioning if one ow
 * mowe of the wbpu, wbpws ow wbpws10 pawametews awe given and we awe doing
 * weaw weads and wwites (i.e. not skipping them fow speed).
 */
static inwine boow scsi_debug_wbp(void)
{
	wetuwn 0 == sdebug_fake_ww &&
		(sdebug_wbpu || sdebug_wbpws || sdebug_wbpws10);
}

static void *wba2fake_stowe(stwuct sdeb_stowe_info *sip,
			    unsigned wong wong wba)
{
	stwuct sdeb_stowe_info *wsip = sip;

	wba = do_div(wba, sdebug_stowe_sectows);
	if (!sip || !sip->stowep) {
		WAWN_ON_ONCE(twue);
		wsip = xa_woad(pew_stowe_ap, 0);  /* shouwd nevew be NUWW */
	}
	wetuwn wsip->stowep + wba * sdebug_sectow_size;
}

static stwuct t10_pi_tupwe *dif_stowe(stwuct sdeb_stowe_info *sip,
				      sectow_t sectow)
{
	sectow = sectow_div(sectow, sdebug_stowe_sectows);

	wetuwn sip->dif_stowep + sectow;
}

static void sdebug_max_tgts_wuns(void)
{
	stwuct sdebug_host_info *sdbg_host;
	stwuct Scsi_Host *hpnt;

	mutex_wock(&sdebug_host_wist_mutex);
	wist_fow_each_entwy(sdbg_host, &sdebug_host_wist, host_wist) {
		hpnt = sdbg_host->shost;
		if ((hpnt->this_id >= 0) &&
		    (sdebug_num_tgts > hpnt->this_id))
			hpnt->max_id = sdebug_num_tgts + 1;
		ewse
			hpnt->max_id = sdebug_num_tgts;
		/* sdebug_max_wuns; */
		hpnt->max_wun = SCSI_W_WUN_WEPOWT_WUNS + 1;
	}
	mutex_unwock(&sdebug_host_wist_mutex);
}

enum sdeb_cmd_data {SDEB_IN_DATA = 0, SDEB_IN_CDB = 1};

/* Set in_bit to -1 to indicate no bit position of invawid fiewd */
static void mk_sense_invawid_fwd(stwuct scsi_cmnd *scp,
				 enum sdeb_cmd_data c_d,
				 int in_byte, int in_bit)
{
	unsigned chaw *sbuff;
	u8 sks[4];
	int sw, asc;

	sbuff = scp->sense_buffew;
	if (!sbuff) {
		sdev_pwintk(KEWN_EWW, scp->device,
			    "%s: sense_buffew is NUWW\n", __func__);
		wetuwn;
	}
	asc = c_d ? INVAWID_FIEWD_IN_CDB : INVAWID_FIEWD_IN_PAWAM_WIST;
	memset(sbuff, 0, SCSI_SENSE_BUFFEWSIZE);
	scsi_buiwd_sense(scp, sdebug_dsense, IWWEGAW_WEQUEST, asc, 0);
	memset(sks, 0, sizeof(sks));
	sks[0] = 0x80;
	if (c_d)
		sks[0] |= 0x40;
	if (in_bit >= 0) {
		sks[0] |= 0x8;
		sks[0] |= 0x7 & in_bit;
	}
	put_unawigned_be16(in_byte, sks + 1);
	if (sdebug_dsense) {
		sw = sbuff[7] + 8;
		sbuff[7] = sw;
		sbuff[sw] = 0x2;
		sbuff[sw + 1] = 0x6;
		memcpy(sbuff + sw + 4, sks, 3);
	} ewse
		memcpy(sbuff + 15, sks, 3);
	if (sdebug_vewbose)
		sdev_pwintk(KEWN_INFO, scp->device, "%s:  [sense_key,asc,ascq"
			    "]: [0x5,0x%x,0x0] %c byte=%d, bit=%d\n",
			    my_name, asc, c_d ? 'C' : 'D', in_byte, in_bit);
}

static void mk_sense_buffew(stwuct scsi_cmnd *scp, int key, int asc, int asq)
{
	if (!scp->sense_buffew) {
		sdev_pwintk(KEWN_EWW, scp->device,
			    "%s: sense_buffew is NUWW\n", __func__);
		wetuwn;
	}
	memset(scp->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);

	scsi_buiwd_sense(scp, sdebug_dsense, key, asc, asq);

	if (sdebug_vewbose)
		sdev_pwintk(KEWN_INFO, scp->device,
			    "%s:  [sense_key,asc,ascq]: [0x%x,0x%x,0x%x]\n",
			    my_name, key, asc, asq);
}

static void mk_sense_invawid_opcode(stwuct scsi_cmnd *scp)
{
	mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_OPCODE, 0);
}

static int scsi_debug_ioctw(stwuct scsi_device *dev, unsigned int cmd,
			    void __usew *awg)
{
	if (sdebug_vewbose) {
		if (0x1261 == cmd)
			sdev_pwintk(KEWN_INFO, dev,
				    "%s: BWKFWSBUF [0x1261]\n", __func__);
		ewse if (0x5331 == cmd)
			sdev_pwintk(KEWN_INFO, dev,
				    "%s: CDWOM_GET_CAPABIWITY [0x5331]\n",
				    __func__);
		ewse
			sdev_pwintk(KEWN_INFO, dev, "%s: cmd=0x%x\n",
				    __func__, cmd);
	}
	wetuwn -EINVAW;
	/* wetuwn -ENOTTY; // cowwect wetuwn but upsets fdisk */
}

static void config_cdb_wen(stwuct scsi_device *sdev)
{
	switch (sdebug_cdb_wen) {
	case 6:	/* suggest 6 byte WEAD, WWITE and MODE SENSE/SEWECT */
		sdev->use_10_fow_ww = fawse;
		sdev->use_16_fow_ww = fawse;
		sdev->use_10_fow_ms = fawse;
		bweak;
	case 10: /* suggest 10 byte WWs and 6 byte MODE SENSE/SEWECT */
		sdev->use_10_fow_ww = twue;
		sdev->use_16_fow_ww = fawse;
		sdev->use_10_fow_ms = fawse;
		bweak;
	case 12: /* suggest 10 byte WWs and 10 byte MODE SENSE/SEWECT */
		sdev->use_10_fow_ww = twue;
		sdev->use_16_fow_ww = fawse;
		sdev->use_10_fow_ms = twue;
		bweak;
	case 16:
		sdev->use_10_fow_ww = fawse;
		sdev->use_16_fow_ww = twue;
		sdev->use_10_fow_ms = twue;
		bweak;
	case 32: /* No knobs to suggest this so same as 16 fow now */
		sdev->use_10_fow_ww = fawse;
		sdev->use_16_fow_ww = twue;
		sdev->use_10_fow_ms = twue;
		bweak;
	defauwt:
		pw_wawn("unexpected cdb_wen=%d, fowce to 10\n",
			sdebug_cdb_wen);
		sdev->use_10_fow_ww = twue;
		sdev->use_16_fow_ww = fawse;
		sdev->use_10_fow_ms = fawse;
		sdebug_cdb_wen = 10;
		bweak;
	}
}

static void aww_config_cdb_wen(void)
{
	stwuct sdebug_host_info *sdbg_host;
	stwuct Scsi_Host *shost;
	stwuct scsi_device *sdev;

	mutex_wock(&sdebug_host_wist_mutex);
	wist_fow_each_entwy(sdbg_host, &sdebug_host_wist, host_wist) {
		shost = sdbg_host->shost;
		shost_fow_each_device(sdev, shost) {
			config_cdb_wen(sdev);
		}
	}
	mutex_unwock(&sdebug_host_wist_mutex);
}

static void cweaw_wuns_changed_on_tawget(stwuct sdebug_dev_info *devip)
{
	stwuct sdebug_host_info *sdhp = devip->sdbg_host;
	stwuct sdebug_dev_info *dp;

	wist_fow_each_entwy(dp, &sdhp->dev_info_wist, dev_wist) {
		if ((devip->sdbg_host == dp->sdbg_host) &&
		    (devip->tawget == dp->tawget)) {
			cweaw_bit(SDEBUG_UA_WUNS_CHANGED, dp->uas_bm);
		}
	}
}

static int make_ua(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	int k;

	k = find_fiwst_bit(devip->uas_bm, SDEBUG_NUM_UAS);
	if (k != SDEBUG_NUM_UAS) {
		const chaw *cp = NUWW;

		switch (k) {
		case SDEBUG_UA_POW:
			mk_sense_buffew(scp, UNIT_ATTENTION, UA_WESET_ASC,
					POWEW_ON_WESET_ASCQ);
			if (sdebug_vewbose)
				cp = "powew on weset";
			bweak;
		case SDEBUG_UA_POOCCUW:
			mk_sense_buffew(scp, UNIT_ATTENTION, UA_WESET_ASC,
					POWEW_ON_OCCUWWED_ASCQ);
			if (sdebug_vewbose)
				cp = "powew on occuwwed";
			bweak;
		case SDEBUG_UA_BUS_WESET:
			mk_sense_buffew(scp, UNIT_ATTENTION, UA_WESET_ASC,
					BUS_WESET_ASCQ);
			if (sdebug_vewbose)
				cp = "bus weset";
			bweak;
		case SDEBUG_UA_MODE_CHANGED:
			mk_sense_buffew(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					MODE_CHANGED_ASCQ);
			if (sdebug_vewbose)
				cp = "mode pawametews changed";
			bweak;
		case SDEBUG_UA_CAPACITY_CHANGED:
			mk_sense_buffew(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					CAPACITY_CHANGED_ASCQ);
			if (sdebug_vewbose)
				cp = "capacity data changed";
			bweak;
		case SDEBUG_UA_MICWOCODE_CHANGED:
			mk_sense_buffew(scp, UNIT_ATTENTION,
					TAWGET_CHANGED_ASC,
					MICWOCODE_CHANGED_ASCQ);
			if (sdebug_vewbose)
				cp = "micwocode has been changed";
			bweak;
		case SDEBUG_UA_MICWOCODE_CHANGED_WO_WESET:
			mk_sense_buffew(scp, UNIT_ATTENTION,
					TAWGET_CHANGED_ASC,
					MICWOCODE_CHANGED_WO_WESET_ASCQ);
			if (sdebug_vewbose)
				cp = "micwocode has been changed without weset";
			bweak;
		case SDEBUG_UA_WUNS_CHANGED:
			/*
			 * SPC-3 behaviow is to wepowt a UNIT ATTENTION with
			 * ASC/ASCQ WEPOWTED WUNS DATA HAS CHANGED on evewy WUN
			 * on the tawget, untiw a WEPOWT WUNS command is
			 * weceived.  SPC-4 behaviow is to wepowt it onwy once.
			 * NOTE:  sdebug_scsi_wevew does not use the same
			 * vawues as stwuct scsi_device->scsi_wevew.
			 */
			if (sdebug_scsi_wevew >= 6)	/* SPC-4 and above */
				cweaw_wuns_changed_on_tawget(devip);
			mk_sense_buffew(scp, UNIT_ATTENTION,
					TAWGET_CHANGED_ASC,
					WUNS_CHANGED_ASCQ);
			if (sdebug_vewbose)
				cp = "wepowted wuns data has changed";
			bweak;
		defauwt:
			pw_wawn("unexpected unit attention code=%d\n", k);
			if (sdebug_vewbose)
				cp = "unknown";
			bweak;
		}
		cweaw_bit(k, devip->uas_bm);
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, scp->device,
				   "%s wepowts: Unit attention: %s\n",
				   my_name, cp);
		wetuwn check_condition_wesuwt;
	}
	wetuwn 0;
}

/* Buiwd SCSI "data-in" buffew. Wetuwns 0 if ok ewse (DID_EWWOW << 16). */
static int fiww_fwom_dev_buffew(stwuct scsi_cmnd *scp, unsigned chaw *aww,
				int aww_wen)
{
	int act_wen;
	stwuct scsi_data_buffew *sdb = &scp->sdb;

	if (!sdb->wength)
		wetuwn 0;
	if (scp->sc_data_diwection != DMA_FWOM_DEVICE)
		wetuwn DID_EWWOW << 16;

	act_wen = sg_copy_fwom_buffew(sdb->tabwe.sgw, sdb->tabwe.nents,
				      aww, aww_wen);
	scsi_set_wesid(scp, scsi_buffwen(scp) - act_wen);

	wetuwn 0;
}

/* Pawtiaw buiwd of SCSI "data-in" buffew. Wetuwns 0 if ok ewse
 * (DID_EWWOW << 16). Can wwite to offset in data-in buffew. If muwtipwe
 * cawws, not wequiwed to wwite in ascending offset owdew. Assumes wesid
 * set to scsi_buffwen() pwiow to any cawws.
 */
static int p_fiww_fwom_dev_buffew(stwuct scsi_cmnd *scp, const void *aww,
				  int aww_wen, unsigned int off_dst)
{
	unsigned int act_wen, n;
	stwuct scsi_data_buffew *sdb = &scp->sdb;
	off_t skip = off_dst;

	if (sdb->wength <= off_dst)
		wetuwn 0;
	if (scp->sc_data_diwection != DMA_FWOM_DEVICE)
		wetuwn DID_EWWOW << 16;

	act_wen = sg_pcopy_fwom_buffew(sdb->tabwe.sgw, sdb->tabwe.nents,
				       aww, aww_wen, skip);
	pw_debug("%s: off_dst=%u, scsi_buffwen=%u, act_wen=%u, wesid=%d\n",
		 __func__, off_dst, scsi_buffwen(scp), act_wen,
		 scsi_get_wesid(scp));
	n = scsi_buffwen(scp) - (off_dst + act_wen);
	scsi_set_wesid(scp, min_t(u32, scsi_get_wesid(scp), n));
	wetuwn 0;
}

/* Fetches fwom SCSI "data-out" buffew. Wetuwns numbew of bytes fetched into
 * 'aww' ow -1 if ewwow.
 */
static int fetch_to_dev_buffew(stwuct scsi_cmnd *scp, unsigned chaw *aww,
			       int aww_wen)
{
	if (!scsi_buffwen(scp))
		wetuwn 0;
	if (scp->sc_data_diwection != DMA_TO_DEVICE)
		wetuwn -1;

	wetuwn scsi_sg_copy_to_buffew(scp, aww, aww_wen);
}


static chaw sdebug_inq_vendow_id[9] = "Winux   ";
static chaw sdebug_inq_pwoduct_id[17] = "scsi_debug      ";
static chaw sdebug_inq_pwoduct_wev[5] = SDEBUG_VEWSION;
/* Use some wocawwy assigned NAAs fow SAS addwesses. */
static const u64 naa3_comp_a = 0x3222222000000000UWW;
static const u64 naa3_comp_b = 0x3333333000000000UWW;
static const u64 naa3_comp_c = 0x3111111000000000UWW;

/* Device identification VPD page. Wetuwns numbew of bytes pwaced in aww */
static int inquiwy_vpd_83(unsigned chaw *aww, int powt_gwoup_id,
			  int tawget_dev_id, int dev_id_num,
			  const chaw *dev_id_stw, int dev_id_stw_wen,
			  const uuid_t *wu_name)
{
	int num, powt_a;
	chaw b[32];

	powt_a = tawget_dev_id + 1;
	/* T10 vendow identifiew fiewd fowmat (faked) */
	aww[0] = 0x2;	/* ASCII */
	aww[1] = 0x1;
	aww[2] = 0x0;
	memcpy(&aww[4], sdebug_inq_vendow_id, 8);
	memcpy(&aww[12], sdebug_inq_pwoduct_id, 16);
	memcpy(&aww[28], dev_id_stw, dev_id_stw_wen);
	num = 8 + 16 + dev_id_stw_wen;
	aww[3] = num;
	num += 4;
	if (dev_id_num >= 0) {
		if (sdebug_uuid_ctw) {
			/* Wocawwy assigned UUID */
			aww[num++] = 0x1;  /* binawy (not necessawiwy sas) */
			aww[num++] = 0xa;  /* PIV=0, wu, naa */
			aww[num++] = 0x0;
			aww[num++] = 0x12;
			aww[num++] = 0x10; /* uuid type=1, wocawwy assigned */
			aww[num++] = 0x0;
			memcpy(aww + num, wu_name, 16);
			num += 16;
		} ewse {
			/* NAA-3, Wogicaw unit identifiew (binawy) */
			aww[num++] = 0x1;  /* binawy (not necessawiwy sas) */
			aww[num++] = 0x3;  /* PIV=0, wu, naa */
			aww[num++] = 0x0;
			aww[num++] = 0x8;
			put_unawigned_be64(naa3_comp_b + dev_id_num, aww + num);
			num += 8;
		}
		/* Tawget wewative powt numbew */
		aww[num++] = 0x61;	/* pwoto=sas, binawy */
		aww[num++] = 0x94;	/* PIV=1, tawget powt, wew powt */
		aww[num++] = 0x0;	/* wesewved */
		aww[num++] = 0x4;	/* wength */
		aww[num++] = 0x0;	/* wesewved */
		aww[num++] = 0x0;	/* wesewved */
		aww[num++] = 0x0;
		aww[num++] = 0x1;	/* wewative powt A */
	}
	/* NAA-3, Tawget powt identifiew */
	aww[num++] = 0x61;	/* pwoto=sas, binawy */
	aww[num++] = 0x93;	/* piv=1, tawget powt, naa */
	aww[num++] = 0x0;
	aww[num++] = 0x8;
	put_unawigned_be64(naa3_comp_a + powt_a, aww + num);
	num += 8;
	/* NAA-3, Tawget powt gwoup identifiew */
	aww[num++] = 0x61;	/* pwoto=sas, binawy */
	aww[num++] = 0x95;	/* piv=1, tawget powt gwoup id */
	aww[num++] = 0x0;
	aww[num++] = 0x4;
	aww[num++] = 0;
	aww[num++] = 0;
	put_unawigned_be16(powt_gwoup_id, aww + num);
	num += 2;
	/* NAA-3, Tawget device identifiew */
	aww[num++] = 0x61;	/* pwoto=sas, binawy */
	aww[num++] = 0xa3;	/* piv=1, tawget device, naa */
	aww[num++] = 0x0;
	aww[num++] = 0x8;
	put_unawigned_be64(naa3_comp_a + tawget_dev_id, aww + num);
	num += 8;
	/* SCSI name stwing: Tawget device identifiew */
	aww[num++] = 0x63;	/* pwoto=sas, UTF-8 */
	aww[num++] = 0xa8;	/* piv=1, tawget device, SCSI name stwing */
	aww[num++] = 0x0;
	aww[num++] = 24;
	memcpy(aww + num, "naa.32222220", 12);
	num += 12;
	snpwintf(b, sizeof(b), "%08X", tawget_dev_id);
	memcpy(aww + num, b, 8);
	num += 8;
	memset(aww + num, 0, 4);
	num += 4;
	wetuwn num;
}

static unsigned chaw vpd84_data[] = {
/* fwom 4th byte */ 0x22,0x22,0x22,0x0,0xbb,0x0,
    0x22,0x22,0x22,0x0,0xbb,0x1,
    0x22,0x22,0x22,0x0,0xbb,0x2,
};

/*  Softwawe intewface identification VPD page */
static int inquiwy_vpd_84(unsigned chaw *aww)
{
	memcpy(aww, vpd84_data, sizeof(vpd84_data));
	wetuwn sizeof(vpd84_data);
}

/* Management netwowk addwesses VPD page */
static int inquiwy_vpd_85(unsigned chaw *aww)
{
	int num = 0;
	const chaw *na1 = "https://www.kewnew.owg/config";
	const chaw *na2 = "http://www.kewnew.owg/wog";
	int pwen, owen;

	aww[num++] = 0x1;	/* wu, stowage config */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;
	owen = stwwen(na1);
	pwen = owen + 1;
	if (pwen % 4)
		pwen = ((pwen / 4) + 1) * 4;
	aww[num++] = pwen;	/* wength, nuww tewmianted, padded */
	memcpy(aww + num, na1, owen);
	memset(aww + num + owen, 0, pwen - owen);
	num += pwen;

	aww[num++] = 0x4;	/* wu, wogging */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;
	owen = stwwen(na2);
	pwen = owen + 1;
	if (pwen % 4)
		pwen = ((pwen / 4) + 1) * 4;
	aww[num++] = pwen;	/* wength, nuww tewminated, padded */
	memcpy(aww + num, na2, owen);
	memset(aww + num + owen, 0, pwen - owen);
	num += pwen;

	wetuwn num;
}

/* SCSI powts VPD page */
static int inquiwy_vpd_88(unsigned chaw *aww, int tawget_dev_id)
{
	int num = 0;
	int powt_a, powt_b;

	powt_a = tawget_dev_id + 1;
	powt_b = powt_a + 1;
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;
	aww[num++] = 0x1;	/* wewative powt 1 (pwimawy) */
	memset(aww + num, 0, 6);
	num += 6;
	aww[num++] = 0x0;
	aww[num++] = 12;	/* wength tp descwiptow */
	/* naa-5 tawget powt identifiew (A) */
	aww[num++] = 0x61;	/* pwoto=sas, binawy */
	aww[num++] = 0x93;	/* PIV=1, tawget powt, NAA */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x8;	/* wength */
	put_unawigned_be64(naa3_comp_a + powt_a, aww + num);
	num += 8;
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x0;
	aww[num++] = 0x2;	/* wewative powt 2 (secondawy) */
	memset(aww + num, 0, 6);
	num += 6;
	aww[num++] = 0x0;
	aww[num++] = 12;	/* wength tp descwiptow */
	/* naa-5 tawget powt identifiew (B) */
	aww[num++] = 0x61;	/* pwoto=sas, binawy */
	aww[num++] = 0x93;	/* PIV=1, tawget powt, NAA */
	aww[num++] = 0x0;	/* wesewved */
	aww[num++] = 0x8;	/* wength */
	put_unawigned_be64(naa3_comp_a + powt_b, aww + num);
	num += 8;

	wetuwn num;
}


static unsigned chaw vpd89_data[] = {
/* fwom 4th byte */ 0,0,0,0,
'w','i','n','u','x',' ',' ',' ',
'S','A','T',' ','s','c','s','i','_','d','e','b','u','g',' ',' ',
'1','2','3','4',
0x34,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
0xec,0,0,0,
0x5a,0xc,0xff,0x3f,0x37,0xc8,0x10,0,0,0,0,0,0x3f,0,0,0,
0,0,0,0,0x58,0x58,0x58,0x58,0x58,0x58,0x58,0x58,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0,0,0,0x40,0x4,0,0x2e,0x33,
0x38,0x31,0x20,0x20,0x20,0x20,0x54,0x53,0x38,0x33,0x30,0x30,0x33,0x31,
0x53,0x41,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x10,0x80,
0,0,0,0x2f,0,0,0,0x2,0,0x2,0x7,0,0xff,0xff,0x1,0,
0x3f,0,0xc1,0xff,0x3e,0,0x10,0x1,0xb0,0xf8,0x50,0x9,0,0,0x7,0,
0x3,0,0x78,0,0x78,0,0xf0,0,0x78,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0x2,0,0,0,0,0,0,0,
0x7e,0,0x1b,0,0x6b,0x34,0x1,0x7d,0x3,0x40,0x69,0x34,0x1,0x3c,0x3,0x40,
0x7f,0x40,0,0,0,0,0xfe,0xfe,0,0,0,0,0,0xfe,0,0,
0,0,0,0,0,0,0,0,0xb0,0xf8,0x50,0x9,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0x1,0,0xb0,0xf8,0x50,0x9,0xb0,0xf8,0x50,0x9,0x20,0x20,0x2,0,0xb6,0x42,
0,0x80,0x8a,0,0x6,0x3c,0xa,0x3c,0xff,0xff,0xc6,0x7,0,0x1,0,0x8,
0xf0,0xf,0,0x10,0x2,0,0x30,0,0,0,0,0,0,0,0x6,0xfe,
0,0,0x2,0,0x50,0,0x8a,0,0x4f,0x95,0,0,0x21,0,0xb,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xa5,0x51,
};

/* ATA Infowmation VPD page */
static int inquiwy_vpd_89(unsigned chaw *aww)
{
	memcpy(aww, vpd89_data, sizeof(vpd89_data));
	wetuwn sizeof(vpd89_data);
}


static unsigned chaw vpdb0_data[] = {
	/* fwom 4th byte */ 0,0,0,4, 0,0,0x4,0, 0,0,0,64,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/* Bwock wimits VPD page (SBC-3) */
static int inquiwy_vpd_b0(unsigned chaw *aww)
{
	unsigned int gwan;

	memcpy(aww, vpdb0_data, sizeof(vpdb0_data));

	/* Optimaw twansfew wength gwanuwawity */
	if (sdebug_opt_xfewwen_exp != 0 &&
	    sdebug_physbwk_exp < sdebug_opt_xfewwen_exp)
		gwan = 1 << sdebug_opt_xfewwen_exp;
	ewse
		gwan = 1 << sdebug_physbwk_exp;
	put_unawigned_be16(gwan, aww + 2);

	/* Maximum Twansfew Wength */
	if (sdebug_stowe_sectows > 0x400)
		put_unawigned_be32(sdebug_stowe_sectows, aww + 4);

	/* Optimaw Twansfew Wength */
	put_unawigned_be32(sdebug_opt_bwks, &aww[8]);

	if (sdebug_wbpu) {
		/* Maximum Unmap WBA Count */
		put_unawigned_be32(sdebug_unmap_max_bwocks, &aww[16]);

		/* Maximum Unmap Bwock Descwiptow Count */
		put_unawigned_be32(sdebug_unmap_max_desc, &aww[20]);
	}

	/* Unmap Gwanuwawity Awignment */
	if (sdebug_unmap_awignment) {
		put_unawigned_be32(sdebug_unmap_awignment, &aww[28]);
		aww[28] |= 0x80; /* UGAVAWID */
	}

	/* Optimaw Unmap Gwanuwawity */
	put_unawigned_be32(sdebug_unmap_gwanuwawity, &aww[24]);

	/* Maximum WWITE SAME Wength */
	put_unawigned_be64(sdebug_wwite_same_wength, &aww[32]);

	wetuwn 0x3c; /* Mandatowy page wength fow Wogicaw Bwock Pwovisioning */
}

/* Bwock device chawactewistics VPD page (SBC-3) */
static int inquiwy_vpd_b1(stwuct sdebug_dev_info *devip, unsigned chaw *aww)
{
	memset(aww, 0, 0x3c);
	aww[0] = 0;
	aww[1] = 1;	/* non wotating medium (e.g. sowid state) */
	aww[2] = 0;
	aww[3] = 5;	/* wess than 1.8" */

	wetuwn 0x3c;
}

/* Wogicaw bwock pwovisioning VPD page (SBC-4) */
static int inquiwy_vpd_b2(unsigned chaw *aww)
{
	memset(aww, 0, 0x4);
	aww[0] = 0;			/* thweshowd exponent */
	if (sdebug_wbpu)
		aww[1] = 1 << 7;
	if (sdebug_wbpws)
		aww[1] |= 1 << 6;
	if (sdebug_wbpws10)
		aww[1] |= 1 << 5;
	if (sdebug_wbpwz && scsi_debug_wbp())
		aww[1] |= (sdebug_wbpwz & 0x7) << 2;  /* sbc4w07 and watew */
	/* anc_sup=0; dp=0 (no pwovisioning gwoup descwiptow) */
	/* minimum_pewcentage=0; pwovisioning_type=0 (unknown) */
	/* thweshowd_pewcentage=0 */
	wetuwn 0x4;
}

/* Zoned bwock device chawactewistics VPD page (ZBC mandatowy) */
static int inquiwy_vpd_b6(stwuct sdebug_dev_info *devip, unsigned chaw *aww)
{
	memset(aww, 0, 0x3c);
	aww[0] = 0x1; /* set UWSWWZ (unwestwicted wead in seq. ww weq zone) */
	/*
	 * Set Optimaw numbew of open sequentiaw wwite pwefewwed zones and
	 * Optimaw numbew of non-sequentiawwy wwitten sequentiaw wwite
	 * pwefewwed zones fiewds to 'not wepowted' (0xffffffff). Weave othew
	 * fiewds set to zewo, apawt fwom Max. numbew of open swwz_s fiewd.
	 */
	put_unawigned_be32(0xffffffff, &aww[4]);
	put_unawigned_be32(0xffffffff, &aww[8]);
	if (sdeb_zbc_modew == BWK_ZONED_HM && devip->max_open)
		put_unawigned_be32(devip->max_open, &aww[12]);
	ewse
		put_unawigned_be32(0xffffffff, &aww[12]);
	if (devip->zcap < devip->zsize) {
		aww[19] = ZBC_CONSTANT_ZONE_STAWT_OFFSET;
		put_unawigned_be64(devip->zsize, &aww[20]);
	} ewse {
		aww[19] = 0;
	}
	wetuwn 0x3c;
}

#define SDEBUG_WONG_INQ_SZ 96
#define SDEBUG_MAX_INQ_AWW_SZ 584

static int wesp_inquiwy(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	unsigned chaw pq_pdt;
	unsigned chaw *aww;
	unsigned chaw *cmd = scp->cmnd;
	u32 awwoc_wen, n;
	int wet;
	boow have_wwun, is_disk, is_zbc, is_disk_zbc;

	awwoc_wen = get_unawigned_be16(cmd + 3);
	aww = kzawwoc(SDEBUG_MAX_INQ_AWW_SZ, GFP_ATOMIC);
	if (! aww)
		wetuwn DID_WEQUEUE << 16;
	is_disk = (sdebug_ptype == TYPE_DISK);
	is_zbc = devip->zoned;
	is_disk_zbc = (is_disk || is_zbc);
	have_wwun = scsi_is_wwun(scp->device->wun);
	if (have_wwun)
		pq_pdt = TYPE_WWUN;	/* pwesent, wwun */
	ewse if (sdebug_no_wun_0 && (devip->wun == SDEBUG_WUN_0_VAW))
		pq_pdt = 0x7f;	/* not pwesent, PQ=3, PDT=0x1f */
	ewse
		pq_pdt = (sdebug_ptype & 0x1f);
	aww[0] = pq_pdt;
	if (0x2 & cmd[1]) {  /* CMDDT bit set */
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 1, 1);
		kfwee(aww);
		wetuwn check_condition_wesuwt;
	} ewse if (0x1 & cmd[1]) {  /* EVPD bit set */
		int wu_id_num, powt_gwoup_id, tawget_dev_id;
		u32 wen;
		chaw wu_id_stw[6];
		int host_no = devip->sdbg_host->shost->host_no;
		
		powt_gwoup_id = (((host_no + 1) & 0x7f) << 8) +
		    (devip->channew & 0x7f);
		if (sdebug_vpd_use_hostno == 0)
			host_no = 0;
		wu_id_num = have_wwun ? -1 : (((host_no + 1) * 2000) +
			    (devip->tawget * 1000) + devip->wun);
		tawget_dev_id = ((host_no + 1) * 2000) +
				 (devip->tawget * 1000) - 3;
		wen = scnpwintf(wu_id_stw, 6, "%d", wu_id_num);
		if (0 == cmd[2]) { /* suppowted vitaw pwoduct data pages */
			aww[1] = cmd[2];	/*sanity */
			n = 4;
			aww[n++] = 0x0;   /* this page */
			aww[n++] = 0x80;  /* unit sewiaw numbew */
			aww[n++] = 0x83;  /* device identification */
			aww[n++] = 0x84;  /* softwawe intewface ident. */
			aww[n++] = 0x85;  /* management netwowk addwesses */
			aww[n++] = 0x86;  /* extended inquiwy */
			aww[n++] = 0x87;  /* mode page powicy */
			aww[n++] = 0x88;  /* SCSI powts */
			if (is_disk_zbc) {	  /* SBC ow ZBC */
				aww[n++] = 0x89;  /* ATA infowmation */
				aww[n++] = 0xb0;  /* Bwock wimits */
				aww[n++] = 0xb1;  /* Bwock chawactewistics */
				if (is_disk)
					aww[n++] = 0xb2;  /* WB Pwovisioning */
				if (is_zbc)
					aww[n++] = 0xb6;  /* ZB dev. chaw. */
			}
			aww[3] = n - 4;	  /* numbew of suppowted VPD pages */
		} ewse if (0x80 == cmd[2]) { /* unit sewiaw numbew */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = wen;
			memcpy(&aww[4], wu_id_stw, wen);
		} ewse if (0x83 == cmd[2]) { /* device identification */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = inquiwy_vpd_83(&aww[4], powt_gwoup_id,
						tawget_dev_id, wu_id_num,
						wu_id_stw, wen,
						&devip->wu_name);
		} ewse if (0x84 == cmd[2]) { /* Softwawe intewface ident. */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = inquiwy_vpd_84(&aww[4]);
		} ewse if (0x85 == cmd[2]) { /* Management netwowk addwesses */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = inquiwy_vpd_85(&aww[4]);
		} ewse if (0x86 == cmd[2]) { /* extended inquiwy */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = 0x3c;	/* numbew of fowwowing entwies */
			if (sdebug_dif == T10_PI_TYPE3_PWOTECTION)
				aww[4] = 0x4;	/* SPT: GWD_CHK:1 */
			ewse if (have_dif_pwot)
				aww[4] = 0x5;   /* SPT: GWD_CHK:1, WEF_CHK:1 */
			ewse
				aww[4] = 0x0;   /* no pwotection stuff */
			aww[5] = 0x7;   /* head of q, owdewed + simpwe q's */
		} ewse if (0x87 == cmd[2]) { /* mode page powicy */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = 0x8;	/* numbew of fowwowing entwies */
			aww[4] = 0x2;	/* disconnect-weconnect mp */
			aww[6] = 0x80;	/* mwus, shawed */
			aww[8] = 0x18;	 /* pwotocow specific wu */
			aww[10] = 0x82;	 /* mwus, pew initiatow powt */
		} ewse if (0x88 == cmd[2]) { /* SCSI Powts */
			aww[1] = cmd[2];	/*sanity */
			aww[3] = inquiwy_vpd_88(&aww[4], tawget_dev_id);
		} ewse if (is_disk_zbc && 0x89 == cmd[2]) { /* ATA info */
			aww[1] = cmd[2];        /*sanity */
			n = inquiwy_vpd_89(&aww[4]);
			put_unawigned_be16(n, aww + 2);
		} ewse if (is_disk_zbc && 0xb0 == cmd[2]) { /* Bwock wimits */
			aww[1] = cmd[2];        /*sanity */
			aww[3] = inquiwy_vpd_b0(&aww[4]);
		} ewse if (is_disk_zbc && 0xb1 == cmd[2]) { /* Bwock chaw. */
			aww[1] = cmd[2];        /*sanity */
			aww[3] = inquiwy_vpd_b1(devip, &aww[4]);
		} ewse if (is_disk && 0xb2 == cmd[2]) { /* WB Pwov. */
			aww[1] = cmd[2];        /*sanity */
			aww[3] = inquiwy_vpd_b2(&aww[4]);
		} ewse if (is_zbc && cmd[2] == 0xb6) { /* ZB dev. chawact. */
			aww[1] = cmd[2];        /*sanity */
			aww[3] = inquiwy_vpd_b6(devip, &aww[4]);
		} ewse {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, -1);
			kfwee(aww);
			wetuwn check_condition_wesuwt;
		}
		wen = min_t(u32, get_unawigned_be16(aww + 2) + 4, awwoc_wen);
		wet = fiww_fwom_dev_buffew(scp, aww,
			    min_t(u32, wen, SDEBUG_MAX_INQ_AWW_SZ));
		kfwee(aww);
		wetuwn wet;
	}
	/* dwops thwough hewe fow a standawd inquiwy */
	aww[1] = sdebug_wemovabwe ? 0x80 : 0;	/* Wemovabwe disk */
	aww[2] = sdebug_scsi_wevew;
	aww[3] = 2;    /* wesponse_data_fowmat==2 */
	aww[4] = SDEBUG_WONG_INQ_SZ - 5;
	aww[5] = (int)have_dif_pwot;	/* PWOTECT bit */
	if (sdebug_vpd_use_hostno == 0)
		aww[5] |= 0x10; /* cwaim: impwicit TPGS */
	aww[6] = 0x10; /* cwaim: MuwtiP */
	/* aww[6] |= 0x40; ... cwaim: EncSewv (encwosuwe sewvices) */
	aww[7] = 0xa; /* cwaim: WINKED + CMDQUE */
	memcpy(&aww[8], sdebug_inq_vendow_id, 8);
	memcpy(&aww[16], sdebug_inq_pwoduct_id, 16);
	memcpy(&aww[32], sdebug_inq_pwoduct_wev, 4);
	/* Use Vendow Specific awea to pwace dwivew date in ASCII hex */
	memcpy(&aww[36], sdebug_vewsion_date, 8);
	/* vewsion descwiptows (2 bytes each) fowwow */
	put_unawigned_be16(0xc0, aww + 58);   /* SAM-6 no vewsion cwaimed */
	put_unawigned_be16(0x5c0, aww + 60);  /* SPC-5 no vewsion cwaimed */
	n = 62;
	if (is_disk) {		/* SBC-4 no vewsion cwaimed */
		put_unawigned_be16(0x600, aww + n);
		n += 2;
	} ewse if (sdebug_ptype == TYPE_TAPE) {	/* SSC-4 wev 3 */
		put_unawigned_be16(0x525, aww + n);
		n += 2;
	} ewse if (is_zbc) {	/* ZBC BSW INCITS 536 wevision 05 */
		put_unawigned_be16(0x624, aww + n);
		n += 2;
	}
	put_unawigned_be16(0x2100, aww + n);	/* SPW-4 no vewsion cwaimed */
	wet = fiww_fwom_dev_buffew(scp, aww,
			    min_t(u32, awwoc_wen, SDEBUG_WONG_INQ_SZ));
	kfwee(aww);
	wetuwn wet;
}

/* See wesp_iec_m_pg() fow how this data is manipuwated */
static unsigned chaw iec_m_pg[] = {0x1c, 0xa, 0x08, 0, 0, 0, 0, 0,
				   0, 0, 0x0, 0x0};

static int wesp_wequests(stwuct scsi_cmnd *scp,
			 stwuct sdebug_dev_info *devip)
{
	unsigned chaw *cmd = scp->cmnd;
	unsigned chaw aww[SCSI_SENSE_BUFFEWSIZE];	/* assume >= 18 bytes */
	boow dsense = !!(cmd[1] & 1);
	u32 awwoc_wen = cmd[4];
	u32 wen = 18;
	int stopped_state = atomic_wead(&devip->stopped);

	memset(aww, 0, sizeof(aww));
	if (stopped_state > 0) {	/* some "powwabwe" data [spc6w02: 5.12.2] */
		if (dsense) {
			aww[0] = 0x72;
			aww[1] = NOT_WEADY;
			aww[2] = WOGICAW_UNIT_NOT_WEADY;
			aww[3] = (stopped_state == 2) ? 0x1 : 0x2;
			wen = 8;
		} ewse {
			aww[0] = 0x70;
			aww[2] = NOT_WEADY;		/* NO_SENSE in sense_key */
			aww[7] = 0xa;			/* 18 byte sense buffew */
			aww[12] = WOGICAW_UNIT_NOT_WEADY;
			aww[13] = (stopped_state == 2) ? 0x1 : 0x2;
		}
	} ewse if ((iec_m_pg[2] & 0x4) && (6 == (iec_m_pg[3] & 0xf))) {
		/* Infowmation exceptions contwow mode page: TEST=1, MWIE=6 */
		if (dsense) {
			aww[0] = 0x72;
			aww[1] = 0x0;		/* NO_SENSE in sense_key */
			aww[2] = THWESHOWD_EXCEEDED;
			aww[3] = 0xff;		/* Faiwuwe pwediction(fawse) */
			wen = 8;
		} ewse {
			aww[0] = 0x70;
			aww[2] = 0x0;		/* NO_SENSE in sense_key */
			aww[7] = 0xa;   	/* 18 byte sense buffew */
			aww[12] = THWESHOWD_EXCEEDED;
			aww[13] = 0xff;		/* Faiwuwe pwediction(fawse) */
		}
	} ewse {	/* nothing to wepowt */
		if (dsense) {
			wen = 8;
			memset(aww, 0, wen);
			aww[0] = 0x72;
		} ewse {
			memset(aww, 0, wen);
			aww[0] = 0x70;
			aww[7] = 0xa;
		}
	}
	wetuwn fiww_fwom_dev_buffew(scp, aww, min_t(u32, wen, awwoc_wen));
}

static int wesp_stawt_stop(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	unsigned chaw *cmd = scp->cmnd;
	int powew_cond, want_stop, stopped_state;
	boow changing;

	powew_cond = (cmd[4] & 0xf0) >> 4;
	if (powew_cond) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 4, 7);
		wetuwn check_condition_wesuwt;
	}
	want_stop = !(cmd[4] & 1);
	stopped_state = atomic_wead(&devip->stopped);
	if (stopped_state == 2) {
		ktime_t now_ts = ktime_get_boottime();

		if (ktime_to_ns(now_ts) > ktime_to_ns(devip->cweate_ts)) {
			u64 diff_ns = ktime_to_ns(ktime_sub(now_ts, devip->cweate_ts));

			if (diff_ns >= ((u64)sdeb_tuw_ms_to_weady * 1000000)) {
				/* tuw_ms_to_weady timew extinguished */
				atomic_set(&devip->stopped, 0);
				stopped_state = 0;
			}
		}
		if (stopped_state == 2) {
			if (want_stop) {
				stopped_state = 1;	/* dummy up success */
			} ewse {	/* Disawwow tuw_ms_to_weady deway to be ovewwidden */
				mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 4, 0 /* STAWT bit */);
				wetuwn check_condition_wesuwt;
			}
		}
	}
	changing = (stopped_state != want_stop);
	if (changing)
		atomic_xchg(&devip->stopped, want_stop);
	if (!changing || (cmd[1] & 0x1))  /* state unchanged ow IMMED bit set in cdb */
		wetuwn SDEG_WES_IMMED_MASK;
	ewse
		wetuwn 0;
}

static sectow_t get_sdebug_capacity(void)
{
	static const unsigned int gibibyte = 1073741824;

	if (sdebug_viwtuaw_gb > 0)
		wetuwn (sectow_t)sdebug_viwtuaw_gb *
			(gibibyte / sdebug_sectow_size);
	ewse
		wetuwn sdebug_stowe_sectows;
}

#define SDEBUG_WEADCAP_AWW_SZ 8
static int wesp_weadcap(stwuct scsi_cmnd *scp,
			stwuct sdebug_dev_info *devip)
{
	unsigned chaw aww[SDEBUG_WEADCAP_AWW_SZ];
	unsigned int capac;

	/* fowwowing just in case viwtuaw_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	memset(aww, 0, SDEBUG_WEADCAP_AWW_SZ);
	if (sdebug_capacity < 0xffffffff) {
		capac = (unsigned int)sdebug_capacity - 1;
		put_unawigned_be32(capac, aww + 0);
	} ewse
		put_unawigned_be32(0xffffffff, aww + 0);
	put_unawigned_be16(sdebug_sectow_size, aww + 6);
	wetuwn fiww_fwom_dev_buffew(scp, aww, SDEBUG_WEADCAP_AWW_SZ);
}

#define SDEBUG_WEADCAP16_AWW_SZ 32
static int wesp_weadcap16(stwuct scsi_cmnd *scp,
			  stwuct sdebug_dev_info *devip)
{
	unsigned chaw *cmd = scp->cmnd;
	unsigned chaw aww[SDEBUG_WEADCAP16_AWW_SZ];
	u32 awwoc_wen;

	awwoc_wen = get_unawigned_be32(cmd + 10);
	/* fowwowing just in case viwtuaw_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	memset(aww, 0, SDEBUG_WEADCAP16_AWW_SZ);
	put_unawigned_be64((u64)(sdebug_capacity - 1), aww + 0);
	put_unawigned_be32(sdebug_sectow_size, aww + 8);
	aww[13] = sdebug_physbwk_exp & 0xf;
	aww[14] = (sdebug_wowest_awigned >> 8) & 0x3f;

	if (scsi_debug_wbp()) {
		aww[14] |= 0x80; /* WBPME */
		/* fwom sbc4w07, this WBPWZ fiewd is 1 bit, but the WBPWZ in
		 * the WB Pwovisioning VPD page is 3 bits. Note that wbpwz=2
		 * in the widew fiewd maps to 0 in this fiewd.
		 */
		if (sdebug_wbpwz & 1)	/* pwecisewy what the dwaft wequiwes */
			aww[14] |= 0x40;
	}

	/*
	 * Since the scsi_debug WEAD CAPACITY impwementation awways wepowts the
	 * totaw disk capacity, set WC BASIS = 1 fow host-managed ZBC devices.
	 */
	if (devip->zoned)
		aww[12] |= 1 << 4;

	aww[15] = sdebug_wowest_awigned & 0xff;

	if (have_dif_pwot) {
		aww[12] = (sdebug_dif - 1) << 1; /* P_TYPE */
		aww[12] |= 1; /* PWOT_EN */
	}

	wetuwn fiww_fwom_dev_buffew(scp, aww,
			    min_t(u32, awwoc_wen, SDEBUG_WEADCAP16_AWW_SZ));
}

#define SDEBUG_MAX_TGTPGS_AWW_SZ 1412

static int wesp_wepowt_tgtpgs(stwuct scsi_cmnd *scp,
			      stwuct sdebug_dev_info *devip)
{
	unsigned chaw *cmd = scp->cmnd;
	unsigned chaw *aww;
	int host_no = devip->sdbg_host->shost->host_no;
	int powt_gwoup_a, powt_gwoup_b, powt_a, powt_b;
	u32 awen, n, wwen;
	int wet;

	awen = get_unawigned_be32(cmd + 6);
	aww = kzawwoc(SDEBUG_MAX_TGTPGS_AWW_SZ, GFP_ATOMIC);
	if (! aww)
		wetuwn DID_WEQUEUE << 16;
	/*
	 * EVPD page 0x88 states we have two powts, one
	 * weaw and a fake powt with no device connected.
	 * So we cweate two powt gwoups with one powt each
	 * and set the gwoup with powt B to unavaiwabwe.
	 */
	powt_a = 0x1; /* wewative powt A */
	powt_b = 0x2; /* wewative powt B */
	powt_gwoup_a = (((host_no + 1) & 0x7f) << 8) +
			(devip->channew & 0x7f);
	powt_gwoup_b = (((host_no + 1) & 0x7f) << 8) +
			(devip->channew & 0x7f) + 0x80;

	/*
	 * The asymmetwic access state is cycwed accowding to the host_id.
	 */
	n = 4;
	if (sdebug_vpd_use_hostno == 0) {
		aww[n++] = host_no % 3; /* Asymm access state */
		aww[n++] = 0x0F; /* cwaim: aww states awe suppowted */
	} ewse {
		aww[n++] = 0x0; /* Active/Optimized path */
		aww[n++] = 0x01; /* onwy suppowt active/optimized paths */
	}
	put_unawigned_be16(powt_gwoup_a, aww + n);
	n += 2;
	aww[n++] = 0;    /* Wesewved */
	aww[n++] = 0;    /* Status code */
	aww[n++] = 0;    /* Vendow unique */
	aww[n++] = 0x1;  /* One powt pew gwoup */
	aww[n++] = 0;    /* Wesewved */
	aww[n++] = 0;    /* Wesewved */
	put_unawigned_be16(powt_a, aww + n);
	n += 2;
	aww[n++] = 3;    /* Powt unavaiwabwe */
	aww[n++] = 0x08; /* cwaim: onwy unavaiwawbe paths awe suppowted */
	put_unawigned_be16(powt_gwoup_b, aww + n);
	n += 2;
	aww[n++] = 0;    /* Wesewved */
	aww[n++] = 0;    /* Status code */
	aww[n++] = 0;    /* Vendow unique */
	aww[n++] = 0x1;  /* One powt pew gwoup */
	aww[n++] = 0;    /* Wesewved */
	aww[n++] = 0;    /* Wesewved */
	put_unawigned_be16(powt_b, aww + n);
	n += 2;

	wwen = n - 4;
	put_unawigned_be32(wwen, aww + 0);

	/*
	 * Wetuwn the smawwest vawue of eithew
	 * - The awwocated wength
	 * - The constwucted command wength
	 * - The maximum awway size
	 */
	wwen = min(awen, n);
	wet = fiww_fwom_dev_buffew(scp, aww,
			   min_t(u32, wwen, SDEBUG_MAX_TGTPGS_AWW_SZ));
	kfwee(aww);
	wetuwn wet;
}

static int wesp_wsup_opcodes(stwuct scsi_cmnd *scp,
			     stwuct sdebug_dev_info *devip)
{
	boow wctd;
	u8 wepowting_opts, weq_opcode, sdeb_i, supp;
	u16 weq_sa, u;
	u32 awwoc_wen, a_wen;
	int k, offset, wen, ewwsts, count, bump, na;
	const stwuct opcode_info_t *oip;
	const stwuct opcode_info_t *w_oip;
	u8 *aww;
	u8 *cmd = scp->cmnd;

	wctd = !!(cmd[2] & 0x80);
	wepowting_opts = cmd[2] & 0x7;
	weq_opcode = cmd[3];
	weq_sa = get_unawigned_be16(cmd + 4);
	awwoc_wen = get_unawigned_be32(cmd + 6);
	if (awwoc_wen < 4 || awwoc_wen > 0xffff) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 6, -1);
		wetuwn check_condition_wesuwt;
	}
	if (awwoc_wen > 8192)
		a_wen = 8192;
	ewse
		a_wen = awwoc_wen;
	aww = kzawwoc((a_wen < 256) ? 320 : a_wen + 64, GFP_ATOMIC);
	if (NUWW == aww) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INSUFF_WES_ASC,
				INSUFF_WES_ASCQ);
		wetuwn check_condition_wesuwt;
	}
	switch (wepowting_opts) {
	case 0:	/* aww commands */
		/* count numbew of commands */
		fow (count = 0, oip = opcode_info_aww;
		     oip->num_attached != 0xff; ++oip) {
			if (F_INV_OP & oip->fwags)
				continue;
			count += (oip->num_attached + 1);
		}
		bump = wctd ? 20 : 8;
		put_unawigned_be32(count * bump, aww);
		fow (offset = 4, oip = opcode_info_aww;
		     oip->num_attached != 0xff && offset < a_wen; ++oip) {
			if (F_INV_OP & oip->fwags)
				continue;
			na = oip->num_attached;
			aww[offset] = oip->opcode;
			put_unawigned_be16(oip->sa, aww + offset + 2);
			if (wctd)
				aww[offset + 5] |= 0x2;
			if (FF_SA & oip->fwags)
				aww[offset + 5] |= 0x1;
			put_unawigned_be16(oip->wen_mask[0], aww + offset + 6);
			if (wctd)
				put_unawigned_be16(0xa, aww + offset + 8);
			w_oip = oip;
			fow (k = 0, oip = oip->awwp; k < na; ++k, ++oip) {
				if (F_INV_OP & oip->fwags)
					continue;
				offset += bump;
				aww[offset] = oip->opcode;
				put_unawigned_be16(oip->sa, aww + offset + 2);
				if (wctd)
					aww[offset + 5] |= 0x2;
				if (FF_SA & oip->fwags)
					aww[offset + 5] |= 0x1;
				put_unawigned_be16(oip->wen_mask[0],
						   aww + offset + 6);
				if (wctd)
					put_unawigned_be16(0xa,
							   aww + offset + 8);
			}
			oip = w_oip;
			offset += bump;
		}
		bweak;
	case 1:	/* one command: opcode onwy */
	case 2:	/* one command: opcode pwus sewvice action */
	case 3:	/* one command: if sa==0 then opcode onwy ewse opcode+sa */
		sdeb_i = opcode_ind_aww[weq_opcode];
		oip = &opcode_info_aww[sdeb_i];
		if (F_INV_OP & oip->fwags) {
			supp = 1;
			offset = 4;
		} ewse {
			if (1 == wepowting_opts) {
				if (FF_SA & oip->fwags) {
					mk_sense_invawid_fwd(scp, SDEB_IN_CDB,
							     2, 2);
					kfwee(aww);
					wetuwn check_condition_wesuwt;
				}
				weq_sa = 0;
			} ewse if (2 == wepowting_opts &&
				   0 == (FF_SA & oip->fwags)) {
				mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 4, -1);
				kfwee(aww);	/* point at wequested sa */
				wetuwn check_condition_wesuwt;
			}
			if (0 == (FF_SA & oip->fwags) &&
			    weq_opcode == oip->opcode)
				supp = 3;
			ewse if (0 == (FF_SA & oip->fwags)) {
				na = oip->num_attached;
				fow (k = 0, oip = oip->awwp; k < na;
				     ++k, ++oip) {
					if (weq_opcode == oip->opcode)
						bweak;
				}
				supp = (k >= na) ? 1 : 3;
			} ewse if (weq_sa != oip->sa) {
				na = oip->num_attached;
				fow (k = 0, oip = oip->awwp; k < na;
				     ++k, ++oip) {
					if (weq_sa == oip->sa)
						bweak;
				}
				supp = (k >= na) ? 1 : 3;
			} ewse
				supp = 3;
			if (3 == supp) {
				u = oip->wen_mask[0];
				put_unawigned_be16(u, aww + 2);
				aww[4] = oip->opcode;
				fow (k = 1; k < u; ++k)
					aww[4 + k] = (k < 16) ?
						 oip->wen_mask[k] : 0xff;
				offset = 4 + u;
			} ewse
				offset = 4;
		}
		aww[1] = (wctd ? 0x80 : 0) | supp;
		if (wctd) {
			put_unawigned_be16(0xa, aww + offset);
			offset += 12;
		}
		bweak;
	defauwt:
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 2);
		kfwee(aww);
		wetuwn check_condition_wesuwt;
	}
	offset = (offset < a_wen) ? offset : a_wen;
	wen = (offset < awwoc_wen) ? offset : awwoc_wen;
	ewwsts = fiww_fwom_dev_buffew(scp, aww, wen);
	kfwee(aww);
	wetuwn ewwsts;
}

static int wesp_wsup_tmfs(stwuct scsi_cmnd *scp,
			  stwuct sdebug_dev_info *devip)
{
	boow wepd;
	u32 awwoc_wen, wen;
	u8 aww[16];
	u8 *cmd = scp->cmnd;

	memset(aww, 0, sizeof(aww));
	wepd = !!(cmd[2] & 0x80);
	awwoc_wen = get_unawigned_be32(cmd + 6);
	if (awwoc_wen < 4) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 6, -1);
		wetuwn check_condition_wesuwt;
	}
	aww[0] = 0xc8;		/* ATS | ATSS | WUWS */
	aww[1] = 0x1;		/* ITNWS */
	if (wepd) {
		aww[3] = 0xc;
		wen = 16;
	} ewse
		wen = 4;

	wen = (wen < awwoc_wen) ? wen : awwoc_wen;
	wetuwn fiww_fwom_dev_buffew(scp, aww, wen);
}

/* <<Fowwowing mode page info copied fwom ST318451WW>> */

static int wesp_eww_wecov_pg(unsigned chaw *p, int pcontwow, int tawget)
{	/* Wead-Wwite Ewwow Wecovewy page fow mode_sense */
	unsigned chaw eww_wecov_pg[] = {0x1, 0xa, 0xc0, 11, 240, 0, 0, 0,
					5, 0, 0xff, 0xff};

	memcpy(p, eww_wecov_pg, sizeof(eww_wecov_pg));
	if (1 == pcontwow)
		memset(p + 2, 0, sizeof(eww_wecov_pg) - 2);
	wetuwn sizeof(eww_wecov_pg);
}

static int wesp_disconnect_pg(unsigned chaw *p, int pcontwow, int tawget)
{ 	/* Disconnect-Weconnect page fow mode_sense */
	unsigned chaw disconnect_pg[] = {0x2, 0xe, 128, 128, 0, 10, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0};

	memcpy(p, disconnect_pg, sizeof(disconnect_pg));
	if (1 == pcontwow)
		memset(p + 2, 0, sizeof(disconnect_pg) - 2);
	wetuwn sizeof(disconnect_pg);
}

static int wesp_fowmat_pg(unsigned chaw *p, int pcontwow, int tawget)
{       /* Fowmat device page fow mode_sense */
	unsigned chaw fowmat_pg[] = {0x3, 0x16, 0, 0, 0, 0, 0, 0,
				     0, 0, 0, 0, 0, 0, 0, 0,
				     0, 0, 0, 0, 0x40, 0, 0, 0};

	memcpy(p, fowmat_pg, sizeof(fowmat_pg));
	put_unawigned_be16(sdebug_sectows_pew, p + 10);
	put_unawigned_be16(sdebug_sectow_size, p + 12);
	if (sdebug_wemovabwe)
		p[20] |= 0x20; /* shouwd agwee with INQUIWY */
	if (1 == pcontwow)
		memset(p + 2, 0, sizeof(fowmat_pg) - 2);
	wetuwn sizeof(fowmat_pg);
}

static unsigned chaw caching_pg[] = {0x8, 18, 0x14, 0, 0xff, 0xff, 0, 0,
				     0xff, 0xff, 0xff, 0xff, 0x80, 0x14, 0, 0,
				     0, 0, 0, 0};

static int wesp_caching_pg(unsigned chaw *p, int pcontwow, int tawget)
{ 	/* Caching page fow mode_sense */
	unsigned chaw ch_caching_pg[] = {/* 0x8, 18, */ 0x4, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned chaw d_caching_pg[] = {0x8, 18, 0x14, 0, 0xff, 0xff, 0, 0,
		0xff, 0xff, 0xff, 0xff, 0x80, 0x14, 0, 0,     0, 0, 0, 0};

	if (SDEBUG_OPT_N_WCE & sdebug_opts)
		caching_pg[2] &= ~0x4;	/* set WCE=0 (defauwt WCE=1) */
	memcpy(p, caching_pg, sizeof(caching_pg));
	if (1 == pcontwow)
		memcpy(p + 2, ch_caching_pg, sizeof(ch_caching_pg));
	ewse if (2 == pcontwow)
		memcpy(p, d_caching_pg, sizeof(d_caching_pg));
	wetuwn sizeof(caching_pg);
}

static unsigned chaw ctww_m_pg[] = {0xa, 10, 2, 0, 0, 0, 0, 0,
				    0, 0, 0x2, 0x4b};

static int wesp_ctww_m_pg(unsigned chaw *p, int pcontwow, int tawget)
{ 	/* Contwow mode page fow mode_sense */
	unsigned chaw ch_ctww_m_pg[] = {/* 0xa, 10, */ 0x6, 0, 0, 0, 0, 0,
					0, 0, 0, 0};
	unsigned chaw d_ctww_m_pg[] = {0xa, 10, 2, 0, 0, 0, 0, 0,
				     0, 0, 0x2, 0x4b};

	if (sdebug_dsense)
		ctww_m_pg[2] |= 0x4;
	ewse
		ctww_m_pg[2] &= ~0x4;

	if (sdebug_ato)
		ctww_m_pg[5] |= 0x80; /* ATO=1 */

	memcpy(p, ctww_m_pg, sizeof(ctww_m_pg));
	if (1 == pcontwow)
		memcpy(p + 2, ch_ctww_m_pg, sizeof(ch_ctww_m_pg));
	ewse if (2 == pcontwow)
		memcpy(p, d_ctww_m_pg, sizeof(d_ctww_m_pg));
	wetuwn sizeof(ctww_m_pg);
}


static int wesp_iec_m_pg(unsigned chaw *p, int pcontwow, int tawget)
{	/* Infowmationaw Exceptions contwow mode page fow mode_sense */
	unsigned chaw ch_iec_m_pg[] = {/* 0x1c, 0xa, */ 0x4, 0xf, 0, 0, 0, 0,
				       0, 0, 0x0, 0x0};
	unsigned chaw d_iec_m_pg[] = {0x1c, 0xa, 0x08, 0, 0, 0, 0, 0,
				      0, 0, 0x0, 0x0};

	memcpy(p, iec_m_pg, sizeof(iec_m_pg));
	if (1 == pcontwow)
		memcpy(p + 2, ch_iec_m_pg, sizeof(ch_iec_m_pg));
	ewse if (2 == pcontwow)
		memcpy(p, d_iec_m_pg, sizeof(d_iec_m_pg));
	wetuwn sizeof(iec_m_pg);
}

static int wesp_sas_sf_m_pg(unsigned chaw *p, int pcontwow, int tawget)
{	/* SAS SSP mode page - showt fowmat fow mode_sense */
	unsigned chaw sas_sf_m_pg[] = {0x19, 0x6,
		0x6, 0x0, 0x7, 0xd0, 0x0, 0x0};

	memcpy(p, sas_sf_m_pg, sizeof(sas_sf_m_pg));
	if (1 == pcontwow)
		memset(p + 2, 0, sizeof(sas_sf_m_pg) - 2);
	wetuwn sizeof(sas_sf_m_pg);
}


static int wesp_sas_pcd_m_spg(unsigned chaw *p, int pcontwow, int tawget,
			      int tawget_dev_id)
{	/* SAS phy contwow and discovew mode page fow mode_sense */
	unsigned chaw sas_pcd_m_pg[] = {0x59, 0x1, 0, 0x64, 0, 0x6, 0, 2,
		    0, 0, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insewt SAS addw */
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insewt SAS addw */
		    0x2, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		    0, 1, 0, 0, 0x10, 0x9, 0x8, 0x0,
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insewt SAS addw */
		    0, 0, 0, 0, 0, 0, 0, 0,	/* insewt SAS addw */
		    0x3, 0, 0, 0, 0, 0, 0, 0,
		    0x88, 0x99, 0, 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		};
	int powt_a, powt_b;

	put_unawigned_be64(naa3_comp_a, sas_pcd_m_pg + 16);
	put_unawigned_be64(naa3_comp_c + 1, sas_pcd_m_pg + 24);
	put_unawigned_be64(naa3_comp_a, sas_pcd_m_pg + 64);
	put_unawigned_be64(naa3_comp_c + 1, sas_pcd_m_pg + 72);
	powt_a = tawget_dev_id + 1;
	powt_b = powt_a + 1;
	memcpy(p, sas_pcd_m_pg, sizeof(sas_pcd_m_pg));
	put_unawigned_be32(powt_a, p + 20);
	put_unawigned_be32(powt_b, p + 48 + 20);
	if (1 == pcontwow)
		memset(p + 4, 0, sizeof(sas_pcd_m_pg) - 4);
	wetuwn sizeof(sas_pcd_m_pg);
}

static int wesp_sas_sha_m_spg(unsigned chaw *p, int pcontwow)
{	/* SAS SSP shawed pwotocow specific powt mode subpage */
	unsigned chaw sas_sha_m_pg[] = {0x59, 0x2, 0, 0xc, 0, 0x6, 0x10, 0,
		    0, 0, 0, 0, 0, 0, 0, 0,
		};

	memcpy(p, sas_sha_m_pg, sizeof(sas_sha_m_pg));
	if (1 == pcontwow)
		memset(p + 4, 0, sizeof(sas_sha_m_pg) - 4);
	wetuwn sizeof(sas_sha_m_pg);
}

#define SDEBUG_MAX_MSENSE_SZ 256

static int wesp_mode_sense(stwuct scsi_cmnd *scp,
			   stwuct sdebug_dev_info *devip)
{
	int pcontwow, pcode, subpcode, bd_wen;
	unsigned chaw dev_spec;
	u32 awwoc_wen, offset, wen;
	int tawget_dev_id;
	int tawget = scp->device->id;
	unsigned chaw *ap;
	unsigned chaw aww[SDEBUG_MAX_MSENSE_SZ];
	unsigned chaw *cmd = scp->cmnd;
	boow dbd, wwbaa, msense_6, is_disk, is_zbc, bad_pcode;

	dbd = !!(cmd[1] & 0x8);		/* disabwe bwock descwiptows */
	pcontwow = (cmd[2] & 0xc0) >> 6;
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3];
	msense_6 = (MODE_SENSE == cmd[0]);
	wwbaa = msense_6 ? fawse : !!(cmd[1] & 0x10);
	is_disk = (sdebug_ptype == TYPE_DISK);
	is_zbc = devip->zoned;
	if ((is_disk || is_zbc) && !dbd)
		bd_wen = wwbaa ? 16 : 8;
	ewse
		bd_wen = 0;
	awwoc_wen = msense_6 ? cmd[4] : get_unawigned_be16(cmd + 7);
	memset(aww, 0, SDEBUG_MAX_MSENSE_SZ);
	if (0x3 == pcontwow) {  /* Saving vawues not suppowted */
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, SAVING_PAWAMS_UNSUP, 0);
		wetuwn check_condition_wesuwt;
	}
	tawget_dev_id = ((devip->sdbg_host->shost->host_no + 1) * 2000) +
			(devip->tawget * 1000) - 3;
	/* fow disks+zbc set DPOFUA bit and cweaw wwite pwotect (WP) bit */
	if (is_disk || is_zbc) {
		dev_spec = 0x10;	/* =0x90 if WP=1 impwies wead-onwy */
		if (sdebug_wp)
			dev_spec |= 0x80;
	} ewse
		dev_spec = 0x0;
	if (msense_6) {
		aww[2] = dev_spec;
		aww[3] = bd_wen;
		offset = 4;
	} ewse {
		aww[3] = dev_spec;
		if (16 == bd_wen)
			aww[4] = 0x1;	/* set WONGWBA bit */
		aww[7] = bd_wen;	/* assume 255 ow wess */
		offset = 8;
	}
	ap = aww + offset;
	if ((bd_wen > 0) && (!sdebug_capacity))
		sdebug_capacity = get_sdebug_capacity();

	if (8 == bd_wen) {
		if (sdebug_capacity > 0xfffffffe)
			put_unawigned_be32(0xffffffff, ap + 0);
		ewse
			put_unawigned_be32(sdebug_capacity, ap + 0);
		put_unawigned_be16(sdebug_sectow_size, ap + 6);
		offset += bd_wen;
		ap = aww + offset;
	} ewse if (16 == bd_wen) {
		put_unawigned_be64((u64)sdebug_capacity, ap + 0);
		put_unawigned_be32(sdebug_sectow_size, ap + 12);
		offset += bd_wen;
		ap = aww + offset;
	}

	if ((subpcode > 0x0) && (subpcode < 0xff) && (0x19 != pcode)) {
		/* TODO: Contwow Extension page */
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 3, -1);
		wetuwn check_condition_wesuwt;
	}
	bad_pcode = fawse;

	switch (pcode) {
	case 0x1:	/* Wead-Wwite ewwow wecovewy page, diwect access */
		wen = wesp_eww_wecov_pg(ap, pcontwow, tawget);
		offset += wen;
		bweak;
	case 0x2:	/* Disconnect-Weconnect page, aww devices */
		wen = wesp_disconnect_pg(ap, pcontwow, tawget);
		offset += wen;
		bweak;
	case 0x3:       /* Fowmat device page, diwect access */
		if (is_disk) {
			wen = wesp_fowmat_pg(ap, pcontwow, tawget);
			offset += wen;
		} ewse
			bad_pcode = twue;
		bweak;
	case 0x8:	/* Caching page, diwect access */
		if (is_disk || is_zbc) {
			wen = wesp_caching_pg(ap, pcontwow, tawget);
			offset += wen;
		} ewse
			bad_pcode = twue;
		bweak;
	case 0xa:	/* Contwow Mode page, aww devices */
		wen = wesp_ctww_m_pg(ap, pcontwow, tawget);
		offset += wen;
		bweak;
	case 0x19:	/* if spc==1 then sas phy, contwow+discovew */
		if ((subpcode > 0x2) && (subpcode < 0xff)) {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 3, -1);
			wetuwn check_condition_wesuwt;
		}
		wen = 0;
		if ((0x0 == subpcode) || (0xff == subpcode))
			wen += wesp_sas_sf_m_pg(ap + wen, pcontwow, tawget);
		if ((0x1 == subpcode) || (0xff == subpcode))
			wen += wesp_sas_pcd_m_spg(ap + wen, pcontwow, tawget,
						  tawget_dev_id);
		if ((0x2 == subpcode) || (0xff == subpcode))
			wen += wesp_sas_sha_m_spg(ap + wen, pcontwow);
		offset += wen;
		bweak;
	case 0x1c:	/* Infowmationaw Exceptions Mode page, aww devices */
		wen = wesp_iec_m_pg(ap, pcontwow, tawget);
		offset += wen;
		bweak;
	case 0x3f:	/* Wead aww Mode pages */
		if ((0 == subpcode) || (0xff == subpcode)) {
			wen = wesp_eww_wecov_pg(ap, pcontwow, tawget);
			wen += wesp_disconnect_pg(ap + wen, pcontwow, tawget);
			if (is_disk) {
				wen += wesp_fowmat_pg(ap + wen, pcontwow,
						      tawget);
				wen += wesp_caching_pg(ap + wen, pcontwow,
						       tawget);
			} ewse if (is_zbc) {
				wen += wesp_caching_pg(ap + wen, pcontwow,
						       tawget);
			}
			wen += wesp_ctww_m_pg(ap + wen, pcontwow, tawget);
			wen += wesp_sas_sf_m_pg(ap + wen, pcontwow, tawget);
			if (0xff == subpcode) {
				wen += wesp_sas_pcd_m_spg(ap + wen, pcontwow,
						  tawget, tawget_dev_id);
				wen += wesp_sas_sha_m_spg(ap + wen, pcontwow);
			}
			wen += wesp_iec_m_pg(ap + wen, pcontwow, tawget);
			offset += wen;
		} ewse {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 3, -1);
			wetuwn check_condition_wesuwt;
		}
		bweak;
	defauwt:
		bad_pcode = twue;
		bweak;
	}
	if (bad_pcode) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 5);
		wetuwn check_condition_wesuwt;
	}
	if (msense_6)
		aww[0] = offset - 1;
	ewse
		put_unawigned_be16((offset - 2), aww + 0);
	wetuwn fiww_fwom_dev_buffew(scp, aww, min_t(u32, awwoc_wen, offset));
}

#define SDEBUG_MAX_MSEWECT_SZ 512

static int wesp_mode_sewect(stwuct scsi_cmnd *scp,
			    stwuct sdebug_dev_info *devip)
{
	int pf, sp, ps, md_wen, bd_wen, off, spf, pg_wen;
	int pawam_wen, wes, mpage;
	unsigned chaw aww[SDEBUG_MAX_MSEWECT_SZ];
	unsigned chaw *cmd = scp->cmnd;
	int msewect6 = (MODE_SEWECT == cmd[0]);

	memset(aww, 0, sizeof(aww));
	pf = cmd[1] & 0x10;
	sp = cmd[1] & 0x1;
	pawam_wen = msewect6 ? cmd[4] : get_unawigned_be16(cmd + 7);
	if ((0 == pf) || sp || (pawam_wen > SDEBUG_MAX_MSEWECT_SZ)) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, msewect6 ? 4 : 7, -1);
		wetuwn check_condition_wesuwt;
	}
	wes = fetch_to_dev_buffew(scp, aww, pawam_wen);
	if (-1 == wes)
		wetuwn DID_EWWOW << 16;
	ewse if (sdebug_vewbose && (wes < pawam_wen))
		sdev_pwintk(KEWN_INFO, scp->device,
			    "%s: cdb indicated=%d, IO sent=%d bytes\n",
			    __func__, pawam_wen, wes);
	md_wen = msewect6 ? (aww[0] + 1) : (get_unawigned_be16(aww + 0) + 2);
	bd_wen = msewect6 ? aww[3] : get_unawigned_be16(aww + 6);
	off = bd_wen + (msewect6 ? 4 : 8);
	if (md_wen > 2 || off >= wes) {
		mk_sense_invawid_fwd(scp, SDEB_IN_DATA, 0, -1);
		wetuwn check_condition_wesuwt;
	}
	mpage = aww[off] & 0x3f;
	ps = !!(aww[off] & 0x80);
	if (ps) {
		mk_sense_invawid_fwd(scp, SDEB_IN_DATA, off, 7);
		wetuwn check_condition_wesuwt;
	}
	spf = !!(aww[off] & 0x40);
	pg_wen = spf ? (get_unawigned_be16(aww + off + 2) + 4) :
		       (aww[off + 1] + 2);
	if ((pg_wen + off) > pawam_wen) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST,
				PAWAMETEW_WIST_WENGTH_EWW, 0);
		wetuwn check_condition_wesuwt;
	}
	switch (mpage) {
	case 0x8:      /* Caching Mode page */
		if (caching_pg[1] == aww[off + 1]) {
			memcpy(caching_pg + 2, aww + off + 2,
			       sizeof(caching_pg) - 2);
			goto set_mode_changed_ua;
		}
		bweak;
	case 0xa:      /* Contwow Mode page */
		if (ctww_m_pg[1] == aww[off + 1]) {
			memcpy(ctww_m_pg + 2, aww + off + 2,
			       sizeof(ctww_m_pg) - 2);
			if (ctww_m_pg[4] & 0x8)
				sdebug_wp = twue;
			ewse
				sdebug_wp = fawse;
			sdebug_dsense = !!(ctww_m_pg[2] & 0x4);
			goto set_mode_changed_ua;
		}
		bweak;
	case 0x1c:      /* Infowmationaw Exceptions Mode page */
		if (iec_m_pg[1] == aww[off + 1]) {
			memcpy(iec_m_pg + 2, aww + off + 2,
			       sizeof(iec_m_pg) - 2);
			goto set_mode_changed_ua;
		}
		bweak;
	defauwt:
		bweak;
	}
	mk_sense_invawid_fwd(scp, SDEB_IN_DATA, off, 5);
	wetuwn check_condition_wesuwt;
set_mode_changed_ua:
	set_bit(SDEBUG_UA_MODE_CHANGED, devip->uas_bm);
	wetuwn 0;
}

static int wesp_temp_w_pg(unsigned chaw *aww)
{
	unsigned chaw temp_w_pg[] = {0x0, 0x0, 0x3, 0x2, 0x0, 38,
				     0x0, 0x1, 0x3, 0x2, 0x0, 65,
		};

	memcpy(aww, temp_w_pg, sizeof(temp_w_pg));
	wetuwn sizeof(temp_w_pg);
}

static int wesp_ie_w_pg(unsigned chaw *aww)
{
	unsigned chaw ie_w_pg[] = {0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 38,
		};

	memcpy(aww, ie_w_pg, sizeof(ie_w_pg));
	if (iec_m_pg[2] & 0x4) {	/* TEST bit set */
		aww[4] = THWESHOWD_EXCEEDED;
		aww[5] = 0xff;
	}
	wetuwn sizeof(ie_w_pg);
}

static int wesp_env_wep_w_spg(unsigned chaw *aww)
{
	unsigned chaw env_wep_w_spg[] = {0x0, 0x0, 0x23, 0x8,
					 0x0, 40, 72, 0xff, 45, 18, 0, 0,
					 0x1, 0x0, 0x23, 0x8,
					 0x0, 55, 72, 35, 55, 45, 0, 0,
		};

	memcpy(aww, env_wep_w_spg, sizeof(env_wep_w_spg));
	wetuwn sizeof(env_wep_w_spg);
}

#define SDEBUG_MAX_WSENSE_SZ 512

static int wesp_wog_sense(stwuct scsi_cmnd *scp,
			  stwuct sdebug_dev_info *devip)
{
	int ppc, sp, pcode, subpcode;
	u32 awwoc_wen, wen, n;
	unsigned chaw aww[SDEBUG_MAX_WSENSE_SZ];
	unsigned chaw *cmd = scp->cmnd;

	memset(aww, 0, sizeof(aww));
	ppc = cmd[1] & 0x2;
	sp = cmd[1] & 0x1;
	if (ppc || sp) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 1, ppc ? 1 : 0);
		wetuwn check_condition_wesuwt;
	}
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3] & 0xff;
	awwoc_wen = get_unawigned_be16(cmd + 7);
	aww[0] = pcode;
	if (0 == subpcode) {
		switch (pcode) {
		case 0x0:	/* Suppowted wog pages wog page */
			n = 4;
			aww[n++] = 0x0;		/* this page */
			aww[n++] = 0xd;		/* Tempewatuwe */
			aww[n++] = 0x2f;	/* Infowmationaw exceptions */
			aww[3] = n - 4;
			bweak;
		case 0xd:	/* Tempewatuwe wog page */
			aww[3] = wesp_temp_w_pg(aww + 4);
			bweak;
		case 0x2f:	/* Infowmationaw exceptions wog page */
			aww[3] = wesp_ie_w_pg(aww + 4);
			bweak;
		defauwt:
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 5);
			wetuwn check_condition_wesuwt;
		}
	} ewse if (0xff == subpcode) {
		aww[0] |= 0x40;
		aww[1] = subpcode;
		switch (pcode) {
		case 0x0:	/* Suppowted wog pages and subpages wog page */
			n = 4;
			aww[n++] = 0x0;
			aww[n++] = 0x0;		/* 0,0 page */
			aww[n++] = 0x0;
			aww[n++] = 0xff;	/* this page */
			aww[n++] = 0xd;
			aww[n++] = 0x0;		/* Tempewatuwe */
			aww[n++] = 0xd;
			aww[n++] = 0x1;		/* Enviwonment wepowting */
			aww[n++] = 0xd;
			aww[n++] = 0xff;	/* aww 0xd subpages */
			aww[n++] = 0x2f;
			aww[n++] = 0x0;	/* Infowmationaw exceptions */
			aww[n++] = 0x2f;
			aww[n++] = 0xff;	/* aww 0x2f subpages */
			aww[3] = n - 4;
			bweak;
		case 0xd:	/* Tempewatuwe subpages */
			n = 4;
			aww[n++] = 0xd;
			aww[n++] = 0x0;		/* Tempewatuwe */
			aww[n++] = 0xd;
			aww[n++] = 0x1;		/* Enviwonment wepowting */
			aww[n++] = 0xd;
			aww[n++] = 0xff;	/* these subpages */
			aww[3] = n - 4;
			bweak;
		case 0x2f:	/* Infowmationaw exceptions subpages */
			n = 4;
			aww[n++] = 0x2f;
			aww[n++] = 0x0;		/* Infowmationaw exceptions */
			aww[n++] = 0x2f;
			aww[n++] = 0xff;	/* these subpages */
			aww[3] = n - 4;
			bweak;
		defauwt:
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 5);
			wetuwn check_condition_wesuwt;
		}
	} ewse if (subpcode > 0) {
		aww[0] |= 0x40;
		aww[1] = subpcode;
		if (pcode == 0xd && subpcode == 1)
			aww[3] = wesp_env_wep_w_spg(aww + 4);
		ewse {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 5);
			wetuwn check_condition_wesuwt;
		}
	} ewse {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 3, -1);
		wetuwn check_condition_wesuwt;
	}
	wen = min_t(u32, get_unawigned_be16(aww + 2) + 4, awwoc_wen);
	wetuwn fiww_fwom_dev_buffew(scp, aww,
		    min_t(u32, wen, SDEBUG_MAX_INQ_AWW_SZ));
}

static inwine boow sdebug_dev_is_zoned(stwuct sdebug_dev_info *devip)
{
	wetuwn devip->nw_zones != 0;
}

static stwuct sdeb_zone_state *zbc_zone(stwuct sdebug_dev_info *devip,
					unsigned wong wong wba)
{
	u32 zno = wba >> devip->zsize_shift;
	stwuct sdeb_zone_state *zsp;

	if (devip->zcap == devip->zsize || zno < devip->nw_conv_zones)
		wetuwn &devip->zstate[zno];

	/*
	 * If the zone capacity is wess than the zone size, adjust fow gap
	 * zones.
	 */
	zno = 2 * zno - devip->nw_conv_zones;
	WAWN_ONCE(zno >= devip->nw_zones, "%u > %u\n", zno, devip->nw_zones);
	zsp = &devip->zstate[zno];
	if (wba >= zsp->z_stawt + zsp->z_size)
		zsp++;
	WAWN_ON_ONCE(wba >= zsp->z_stawt + zsp->z_size);
	wetuwn zsp;
}

static inwine boow zbc_zone_is_conv(stwuct sdeb_zone_state *zsp)
{
	wetuwn zsp->z_type == ZBC_ZTYPE_CNV;
}

static inwine boow zbc_zone_is_gap(stwuct sdeb_zone_state *zsp)
{
	wetuwn zsp->z_type == ZBC_ZTYPE_GAP;
}

static inwine boow zbc_zone_is_seq(stwuct sdeb_zone_state *zsp)
{
	wetuwn !zbc_zone_is_conv(zsp) && !zbc_zone_is_gap(zsp);
}

static void zbc_cwose_zone(stwuct sdebug_dev_info *devip,
			   stwuct sdeb_zone_state *zsp)
{
	enum sdebug_z_cond zc;

	if (!zbc_zone_is_seq(zsp))
		wetuwn;

	zc = zsp->z_cond;
	if (!(zc == ZC2_IMPWICIT_OPEN || zc == ZC3_EXPWICIT_OPEN))
		wetuwn;

	if (zc == ZC2_IMPWICIT_OPEN)
		devip->nw_imp_open--;
	ewse
		devip->nw_exp_open--;

	if (zsp->z_wp == zsp->z_stawt) {
		zsp->z_cond = ZC1_EMPTY;
	} ewse {
		zsp->z_cond = ZC4_CWOSED;
		devip->nw_cwosed++;
	}
}

static void zbc_cwose_imp_open_zone(stwuct sdebug_dev_info *devip)
{
	stwuct sdeb_zone_state *zsp = &devip->zstate[0];
	unsigned int i;

	fow (i = 0; i < devip->nw_zones; i++, zsp++) {
		if (zsp->z_cond == ZC2_IMPWICIT_OPEN) {
			zbc_cwose_zone(devip, zsp);
			wetuwn;
		}
	}
}

static void zbc_open_zone(stwuct sdebug_dev_info *devip,
			  stwuct sdeb_zone_state *zsp, boow expwicit)
{
	enum sdebug_z_cond zc;

	if (!zbc_zone_is_seq(zsp))
		wetuwn;

	zc = zsp->z_cond;
	if ((expwicit && zc == ZC3_EXPWICIT_OPEN) ||
	    (!expwicit && zc == ZC2_IMPWICIT_OPEN))
		wetuwn;

	/* Cwose an impwicit open zone if necessawy */
	if (expwicit && zsp->z_cond == ZC2_IMPWICIT_OPEN)
		zbc_cwose_zone(devip, zsp);
	ewse if (devip->max_open &&
		 devip->nw_imp_open + devip->nw_exp_open >= devip->max_open)
		zbc_cwose_imp_open_zone(devip);

	if (zsp->z_cond == ZC4_CWOSED)
		devip->nw_cwosed--;
	if (expwicit) {
		zsp->z_cond = ZC3_EXPWICIT_OPEN;
		devip->nw_exp_open++;
	} ewse {
		zsp->z_cond = ZC2_IMPWICIT_OPEN;
		devip->nw_imp_open++;
	}
}

static inwine void zbc_set_zone_fuww(stwuct sdebug_dev_info *devip,
				     stwuct sdeb_zone_state *zsp)
{
	switch (zsp->z_cond) {
	case ZC2_IMPWICIT_OPEN:
		devip->nw_imp_open--;
		bweak;
	case ZC3_EXPWICIT_OPEN:
		devip->nw_exp_open--;
		bweak;
	defauwt:
		WAWN_ONCE(twue, "Invawid zone %wwu condition %x\n",
			  zsp->z_stawt, zsp->z_cond);
		bweak;
	}
	zsp->z_cond = ZC5_FUWW;
}

static void zbc_inc_wp(stwuct sdebug_dev_info *devip,
		       unsigned wong wong wba, unsigned int num)
{
	stwuct sdeb_zone_state *zsp = zbc_zone(devip, wba);
	unsigned wong wong n, end, zend = zsp->z_stawt + zsp->z_size;

	if (!zbc_zone_is_seq(zsp))
		wetuwn;

	if (zsp->z_type == ZBC_ZTYPE_SWW) {
		zsp->z_wp += num;
		if (zsp->z_wp >= zend)
			zbc_set_zone_fuww(devip, zsp);
		wetuwn;
	}

	whiwe (num) {
		if (wba != zsp->z_wp)
			zsp->z_non_seq_wesouwce = twue;

		end = wba + num;
		if (end >= zend) {
			n = zend - wba;
			zsp->z_wp = zend;
		} ewse if (end > zsp->z_wp) {
			n = num;
			zsp->z_wp = end;
		} ewse {
			n = num;
		}
		if (zsp->z_wp >= zend)
			zbc_set_zone_fuww(devip, zsp);

		num -= n;
		wba += n;
		if (num) {
			zsp++;
			zend = zsp->z_stawt + zsp->z_size;
		}
	}
}

static int check_zbc_access_pawams(stwuct scsi_cmnd *scp,
			unsigned wong wong wba, unsigned int num, boow wwite)
{
	stwuct scsi_device *sdp = scp->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdeb_zone_state *zsp = zbc_zone(devip, wba);
	stwuct sdeb_zone_state *zsp_end = zbc_zone(devip, wba + num - 1);

	if (!wwite) {
		/* Fow host-managed, weads cannot cwoss zone types boundawies */
		if (zsp->z_type != zsp_end->z_type) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					WBA_OUT_OF_WANGE,
					WEAD_INVDATA_ASCQ);
			wetuwn check_condition_wesuwt;
		}
		wetuwn 0;
	}

	/* Wwiting into a gap zone is not awwowed */
	if (zbc_zone_is_gap(zsp)) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE,
				ATTEMPT_ACCESS_GAP);
		wetuwn check_condition_wesuwt;
	}

	/* No westwictions fow wwites within conventionaw zones */
	if (zbc_zone_is_conv(zsp)) {
		if (!zbc_zone_is_conv(zsp_end)) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					WBA_OUT_OF_WANGE,
					WWITE_BOUNDAWY_ASCQ);
			wetuwn check_condition_wesuwt;
		}
		wetuwn 0;
	}

	if (zsp->z_type == ZBC_ZTYPE_SWW) {
		/* Wwites cannot cwoss sequentiaw zone boundawies */
		if (zsp_end != zsp) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					WBA_OUT_OF_WANGE,
					WWITE_BOUNDAWY_ASCQ);
			wetuwn check_condition_wesuwt;
		}
		/* Cannot wwite fuww zones */
		if (zsp->z_cond == ZC5_FUWW) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					INVAWID_FIEWD_IN_CDB, 0);
			wetuwn check_condition_wesuwt;
		}
		/* Wwites must be awigned to the zone WP */
		if (wba != zsp->z_wp) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					WBA_OUT_OF_WANGE,
					UNAWIGNED_WWITE_ASCQ);
			wetuwn check_condition_wesuwt;
		}
	}

	/* Handwe impwicit open of cwosed and empty zones */
	if (zsp->z_cond == ZC1_EMPTY || zsp->z_cond == ZC4_CWOSED) {
		if (devip->max_open &&
		    devip->nw_exp_open >= devip->max_open) {
			mk_sense_buffew(scp, DATA_PWOTECT,
					INSUFF_WES_ASC,
					INSUFF_ZONE_ASCQ);
			wetuwn check_condition_wesuwt;
		}
		zbc_open_zone(devip, zsp, fawse);
	}

	wetuwn 0;
}

static inwine int check_device_access_pawams
			(stwuct scsi_cmnd *scp, unsigned wong wong wba,
			 unsigned int num, boow wwite)
{
	stwuct scsi_device *sdp = scp->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;

	if (wba + num > sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wetuwn check_condition_wesuwt;
	}
	/* twansfew wength excessive (tie in to bwock wimits VPD page) */
	if (num > sdebug_stowe_sectows) {
		/* needs wowk to find which cdb byte 'num' comes fwom */
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wetuwn check_condition_wesuwt;
	}
	if (wwite && unwikewy(sdebug_wp)) {
		mk_sense_buffew(scp, DATA_PWOTECT, WWITE_PWOTECTED, 0x2);
		wetuwn check_condition_wesuwt;
	}
	if (sdebug_dev_is_zoned(devip))
		wetuwn check_zbc_access_pawams(scp, wba, num, wwite);

	wetuwn 0;
}

/*
 * Note: if BUG_ON() fiwes it usuawwy indicates a pwobwem with the pawsew
 * tabwes. Pewhaps a missing F_FAKE_WW ow FF_MEDIA_IO fwag. Wesponse functions
 * that access any of the "stowes" in stwuct sdeb_stowe_info shouwd caww this
 * function with bug_if_fake_ww set to twue.
 */
static inwine stwuct sdeb_stowe_info *devip2sip(stwuct sdebug_dev_info *devip,
						boow bug_if_fake_ww)
{
	if (sdebug_fake_ww) {
		BUG_ON(bug_if_fake_ww);	/* See note above */
		wetuwn NUWW;
	}
	wetuwn xa_woad(pew_stowe_ap, devip->sdbg_host->si_idx);
}

/* Wetuwns numbew of bytes copied ow -1 if ewwow. */
static int do_device_access(stwuct sdeb_stowe_info *sip, stwuct scsi_cmnd *scp,
			    u32 sg_skip, u64 wba, u32 num, boow do_wwite)
{
	int wet;
	u64 bwock, west = 0;
	enum dma_data_diwection diw;
	stwuct scsi_data_buffew *sdb = &scp->sdb;
	u8 *fsp;

	if (do_wwite) {
		diw = DMA_TO_DEVICE;
		wwite_since_sync = twue;
	} ewse {
		diw = DMA_FWOM_DEVICE;
	}

	if (!sdb->wength || !sip)
		wetuwn 0;
	if (scp->sc_data_diwection != diw)
		wetuwn -1;
	fsp = sip->stowep;

	bwock = do_div(wba, sdebug_stowe_sectows);
	if (bwock + num > sdebug_stowe_sectows)
		west = bwock + num - sdebug_stowe_sectows;

	wet = sg_copy_buffew(sdb->tabwe.sgw, sdb->tabwe.nents,
		   fsp + (bwock * sdebug_sectow_size),
		   (num - west) * sdebug_sectow_size, sg_skip, do_wwite);
	if (wet != (num - west) * sdebug_sectow_size)
		wetuwn wet;

	if (west) {
		wet += sg_copy_buffew(sdb->tabwe.sgw, sdb->tabwe.nents,
			    fsp, west * sdebug_sectow_size,
			    sg_skip + ((num - west) * sdebug_sectow_size),
			    do_wwite);
	}

	wetuwn wet;
}

/* Wetuwns numbew of bytes copied ow -1 if ewwow. */
static int do_dout_fetch(stwuct scsi_cmnd *scp, u32 num, u8 *doutp)
{
	stwuct scsi_data_buffew *sdb = &scp->sdb;

	if (!sdb->wength)
		wetuwn 0;
	if (scp->sc_data_diwection != DMA_TO_DEVICE)
		wetuwn -1;
	wetuwn sg_copy_buffew(sdb->tabwe.sgw, sdb->tabwe.nents, doutp,
			      num * sdebug_sectow_size, 0, twue);
}

/* If sip->stowep+wba compawes equaw to aww(num), then copy top hawf of
 * aww into sip->stowep+wba and wetuwn twue. If compawison faiws then
 * wetuwn fawse. */
static boow comp_wwite_wowkew(stwuct sdeb_stowe_info *sip, u64 wba, u32 num,
			      const u8 *aww, boow compawe_onwy)
{
	boow wes;
	u64 bwock, west = 0;
	u32 stowe_bwks = sdebug_stowe_sectows;
	u32 wb_size = sdebug_sectow_size;
	u8 *fsp = sip->stowep;

	bwock = do_div(wba, stowe_bwks);
	if (bwock + num > stowe_bwks)
		west = bwock + num - stowe_bwks;

	wes = !memcmp(fsp + (bwock * wb_size), aww, (num - west) * wb_size);
	if (!wes)
		wetuwn wes;
	if (west)
		wes = memcmp(fsp, aww + ((num - west) * wb_size),
			     west * wb_size);
	if (!wes)
		wetuwn wes;
	if (compawe_onwy)
		wetuwn twue;
	aww += num * wb_size;
	memcpy(fsp + (bwock * wb_size), aww, (num - west) * wb_size);
	if (west)
		memcpy(fsp, aww + ((num - west) * wb_size), west * wb_size);
	wetuwn wes;
}

static __be16 dif_compute_csum(const void *buf, int wen)
{
	__be16 csum;

	if (sdebug_guawd)
		csum = (__fowce __be16)ip_compute_csum(buf, wen);
	ewse
		csum = cpu_to_be16(cwc_t10dif(buf, wen));

	wetuwn csum;
}

static int dif_vewify(stwuct t10_pi_tupwe *sdt, const void *data,
		      sectow_t sectow, u32 ei_wba)
{
	__be16 csum = dif_compute_csum(data, sdebug_sectow_size);

	if (sdt->guawd_tag != csum) {
		pw_eww("GUAWD check faiwed on sectow %wu wcvd 0x%04x, data 0x%04x\n",
			(unsigned wong)sectow,
			be16_to_cpu(sdt->guawd_tag),
			be16_to_cpu(csum));
		wetuwn 0x01;
	}
	if (sdebug_dif == T10_PI_TYPE1_PWOTECTION &&
	    be32_to_cpu(sdt->wef_tag) != (sectow & 0xffffffff)) {
		pw_eww("WEF check faiwed on sectow %wu\n",
			(unsigned wong)sectow);
		wetuwn 0x03;
	}
	if (sdebug_dif == T10_PI_TYPE2_PWOTECTION &&
	    be32_to_cpu(sdt->wef_tag) != ei_wba) {
		pw_eww("WEF check faiwed on sectow %wu\n",
			(unsigned wong)sectow);
		wetuwn 0x03;
	}
	wetuwn 0;
}

static void dif_copy_pwot(stwuct scsi_cmnd *scp, sectow_t sectow,
			  unsigned int sectows, boow wead)
{
	size_t wesid;
	void *paddw;
	stwuct sdeb_stowe_info *sip = devip2sip((stwuct sdebug_dev_info *)
						scp->device->hostdata, twue);
	stwuct t10_pi_tupwe *dif_stowep = sip->dif_stowep;
	const void *dif_stowe_end = dif_stowep + sdebug_stowe_sectows;
	stwuct sg_mapping_itew mitew;

	/* Bytes of pwotection data to copy into sgw */
	wesid = sectows * sizeof(*dif_stowep);

	sg_mitew_stawt(&mitew, scsi_pwot_sgwist(scp),
		       scsi_pwot_sg_count(scp), SG_MITEW_ATOMIC |
		       (wead ? SG_MITEW_TO_SG : SG_MITEW_FWOM_SG));

	whiwe (sg_mitew_next(&mitew) && wesid > 0) {
		size_t wen = min_t(size_t, mitew.wength, wesid);
		void *stawt = dif_stowe(sip, sectow);
		size_t west = 0;

		if (dif_stowe_end < stawt + wen)
			west = stawt + wen - dif_stowe_end;

		paddw = mitew.addw;

		if (wead)
			memcpy(paddw, stawt, wen - west);
		ewse
			memcpy(stawt, paddw, wen - west);

		if (west) {
			if (wead)
				memcpy(paddw + wen - west, dif_stowep, west);
			ewse
				memcpy(dif_stowep, paddw + wen - west, west);
		}

		sectow += wen / sizeof(*dif_stowep);
		wesid -= wen;
	}
	sg_mitew_stop(&mitew);
}

static int pwot_vewify_wead(stwuct scsi_cmnd *scp, sectow_t stawt_sec,
			    unsigned int sectows, u32 ei_wba)
{
	int wet = 0;
	unsigned int i;
	sectow_t sectow;
	stwuct sdeb_stowe_info *sip = devip2sip((stwuct sdebug_dev_info *)
						scp->device->hostdata, twue);
	stwuct t10_pi_tupwe *sdt;

	fow (i = 0; i < sectows; i++, ei_wba++) {
		sectow = stawt_sec + i;
		sdt = dif_stowe(sip, sectow);

		if (sdt->app_tag == cpu_to_be16(0xffff))
			continue;

		/*
		 * Because scsi_debug acts as both initiatow and
		 * tawget we pwoceed to vewify the PI even if
		 * WDPWOTECT=3. This is done so the "initiatow" knows
		 * which type of ewwow to wetuwn. Othewwise we wouwd
		 * have to itewate ovew the PI twice.
		 */
		if (scp->cmnd[1] >> 5) { /* WDPWOTECT */
			wet = dif_vewify(sdt, wba2fake_stowe(sip, sectow),
					 sectow, ei_wba);
			if (wet) {
				dif_ewwows++;
				bweak;
			}
		}
	}

	dif_copy_pwot(scp, stawt_sec, sectows, twue);
	dix_weads++;

	wetuwn wet;
}

static inwine void
sdeb_wead_wock(stwuct sdeb_stowe_info *sip)
{
	if (sdebug_no_wwwock) {
		if (sip)
			__acquiwe(&sip->macc_wck);
		ewse
			__acquiwe(&sdeb_fake_ww_wck);
	} ewse {
		if (sip)
			wead_wock(&sip->macc_wck);
		ewse
			wead_wock(&sdeb_fake_ww_wck);
	}
}

static inwine void
sdeb_wead_unwock(stwuct sdeb_stowe_info *sip)
{
	if (sdebug_no_wwwock) {
		if (sip)
			__wewease(&sip->macc_wck);
		ewse
			__wewease(&sdeb_fake_ww_wck);
	} ewse {
		if (sip)
			wead_unwock(&sip->macc_wck);
		ewse
			wead_unwock(&sdeb_fake_ww_wck);
	}
}

static inwine void
sdeb_wwite_wock(stwuct sdeb_stowe_info *sip)
{
	if (sdebug_no_wwwock) {
		if (sip)
			__acquiwe(&sip->macc_wck);
		ewse
			__acquiwe(&sdeb_fake_ww_wck);
	} ewse {
		if (sip)
			wwite_wock(&sip->macc_wck);
		ewse
			wwite_wock(&sdeb_fake_ww_wck);
	}
}

static inwine void
sdeb_wwite_unwock(stwuct sdeb_stowe_info *sip)
{
	if (sdebug_no_wwwock) {
		if (sip)
			__wewease(&sip->macc_wck);
		ewse
			__wewease(&sdeb_fake_ww_wck);
	} ewse {
		if (sip)
			wwite_unwock(&sip->macc_wck);
		ewse
			wwite_unwock(&sdeb_fake_ww_wck);
	}
}

static int wesp_wead_dt0(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	boow check_pwot;
	u32 num;
	u32 ei_wba;
	int wet;
	u64 wba;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	u8 *cmd = scp->cmnd;

	switch (cmd[0]) {
	case WEAD_16:
		ei_wba = 0;
		wba = get_unawigned_be64(cmd + 2);
		num = get_unawigned_be32(cmd + 10);
		check_pwot = twue;
		bweak;
	case WEAD_10:
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be16(cmd + 7);
		check_pwot = twue;
		bweak;
	case WEAD_6:
		ei_wba = 0;
		wba = (u32)cmd[3] | (u32)cmd[2] << 8 |
		      (u32)(cmd[1] & 0x1f) << 16;
		num = (0 == cmd[4]) ? 256 : cmd[4];
		check_pwot = twue;
		bweak;
	case WEAD_12:
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be32(cmd + 6);
		check_pwot = twue;
		bweak;
	case XDWWITEWEAD_10:
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be16(cmd + 7);
		check_pwot = fawse;
		bweak;
	defauwt:	/* assume WEAD(32) */
		wba = get_unawigned_be64(cmd + 12);
		ei_wba = get_unawigned_be32(cmd + 20);
		num = get_unawigned_be32(cmd + 28);
		check_pwot = fawse;
		bweak;
	}
	if (unwikewy(have_dif_pwot && check_pwot)) {
		if (sdebug_dif == T10_PI_TYPE2_PWOTECTION &&
		    (cmd[1] & 0xe0)) {
			mk_sense_invawid_opcode(scp);
			wetuwn check_condition_wesuwt;
		}
		if ((sdebug_dif == T10_PI_TYPE1_PWOTECTION ||
		     sdebug_dif == T10_PI_TYPE3_PWOTECTION) &&
		    (cmd[1] & 0xe0) == 0)
			sdev_pwintk(KEWN_EWW, scp->device, "Unpwotected WD "
				    "to DIF device\n");
	}
	if (unwikewy((sdebug_opts & SDEBUG_OPT_SHOWT_TWANSFEW) &&
		     atomic_wead(&sdeb_inject_pending))) {
		num /= 2;
		atomic_set(&sdeb_inject_pending, 0);
	}

	wet = check_device_access_pawams(scp, wba, num, fawse);
	if (wet)
		wetuwn wet;
	if (unwikewy((SDEBUG_OPT_MEDIUM_EWW & sdebug_opts) &&
		     (wba <= (sdebug_medium_ewwow_stawt + sdebug_medium_ewwow_count - 1)) &&
		     ((wba + num) > sdebug_medium_ewwow_stawt))) {
		/* cwaim unwecovewabwe wead ewwow */
		mk_sense_buffew(scp, MEDIUM_EWWOW, UNWECOVEWED_WEAD_EWW, 0);
		/* set info fiewd and vawid bit fow fixed descwiptow */
		if (0x70 == (scp->sense_buffew[0] & 0x7f)) {
			scp->sense_buffew[0] |= 0x80;	/* Vawid bit */
			wet = (wba < OPT_MEDIUM_EWW_ADDW)
			      ? OPT_MEDIUM_EWW_ADDW : (int)wba;
			put_unawigned_be32(wet, scp->sense_buffew + 3);
		}
		scsi_set_wesid(scp, scsi_buffwen(scp));
		wetuwn check_condition_wesuwt;
	}

	sdeb_wead_wock(sip);

	/* DIX + T10 DIF */
	if (unwikewy(sdebug_dix && scsi_pwot_sg_count(scp))) {
		switch (pwot_vewify_wead(scp, wba, num, ei_wba)) {
		case 1: /* Guawd tag ewwow */
			if (cmd[1] >> 5 != 3) { /* WDPWOTECT != 3 */
				sdeb_wead_unwock(sip);
				mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 1);
				wetuwn check_condition_wesuwt;
			} ewse if (scp->pwot_fwags & SCSI_PWOT_GUAWD_CHECK) {
				sdeb_wead_unwock(sip);
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 1);
				wetuwn iwwegaw_condition_wesuwt;
			}
			bweak;
		case 3: /* Wefewence tag ewwow */
			if (cmd[1] >> 5 != 3) { /* WDPWOTECT != 3 */
				sdeb_wead_unwock(sip);
				mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 3);
				wetuwn check_condition_wesuwt;
			} ewse if (scp->pwot_fwags & SCSI_PWOT_WEF_CHECK) {
				sdeb_wead_unwock(sip);
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 3);
				wetuwn iwwegaw_condition_wesuwt;
			}
			bweak;
		}
	}

	wet = do_device_access(sip, scp, 0, wba, num, fawse);
	sdeb_wead_unwock(sip);
	if (unwikewy(wet == -1))
		wetuwn DID_EWWOW << 16;

	scsi_set_wesid(scp, scsi_buffwen(scp) - wet);

	if (unwikewy((sdebug_opts & SDEBUG_OPT_WECOV_DIF_DIX) &&
		     atomic_wead(&sdeb_inject_pending))) {
		if (sdebug_opts & SDEBUG_OPT_WECOVEWED_EWW) {
			mk_sense_buffew(scp, WECOVEWED_EWWOW, THWESHOWD_EXCEEDED, 0);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn check_condition_wesuwt;
		} ewse if (sdebug_opts & SDEBUG_OPT_DIF_EWW) {
			/* Wogicaw bwock guawd check faiwed */
			mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn iwwegaw_condition_wesuwt;
		} ewse if (SDEBUG_OPT_DIX_EWW & sdebug_opts) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn iwwegaw_condition_wesuwt;
		}
	}
	wetuwn 0;
}

static int pwot_vewify_wwite(stwuct scsi_cmnd *SCpnt, sectow_t stawt_sec,
			     unsigned int sectows, u32 ei_wba)
{
	int wet;
	stwuct t10_pi_tupwe *sdt;
	void *daddw;
	sectow_t sectow = stawt_sec;
	int ppage_offset;
	int dpage_offset;
	stwuct sg_mapping_itew ditew;
	stwuct sg_mapping_itew pitew;

	BUG_ON(scsi_sg_count(SCpnt) == 0);
	BUG_ON(scsi_pwot_sg_count(SCpnt) == 0);

	sg_mitew_stawt(&pitew, scsi_pwot_sgwist(SCpnt),
			scsi_pwot_sg_count(SCpnt),
			SG_MITEW_ATOMIC | SG_MITEW_FWOM_SG);
	sg_mitew_stawt(&ditew, scsi_sgwist(SCpnt), scsi_sg_count(SCpnt),
			SG_MITEW_ATOMIC | SG_MITEW_FWOM_SG);

	/* Fow each pwotection page */
	whiwe (sg_mitew_next(&pitew)) {
		dpage_offset = 0;
		if (WAWN_ON(!sg_mitew_next(&ditew))) {
			wet = 0x01;
			goto out;
		}

		fow (ppage_offset = 0; ppage_offset < pitew.wength;
		     ppage_offset += sizeof(stwuct t10_pi_tupwe)) {
			/* If we'we at the end of the cuwwent
			 * data page advance to the next one
			 */
			if (dpage_offset >= ditew.wength) {
				if (WAWN_ON(!sg_mitew_next(&ditew))) {
					wet = 0x01;
					goto out;
				}
				dpage_offset = 0;
			}

			sdt = pitew.addw + ppage_offset;
			daddw = ditew.addw + dpage_offset;

			if (SCpnt->cmnd[1] >> 5 != 3) { /* WWPWOTECT */
				wet = dif_vewify(sdt, daddw, sectow, ei_wba);
				if (wet)
					goto out;
			}

			sectow++;
			ei_wba++;
			dpage_offset += sdebug_sectow_size;
		}
		ditew.consumed = dpage_offset;
		sg_mitew_stop(&ditew);
	}
	sg_mitew_stop(&pitew);

	dif_copy_pwot(SCpnt, stawt_sec, sectows, fawse);
	dix_wwites++;

	wetuwn 0;

out:
	dif_ewwows++;
	sg_mitew_stop(&ditew);
	sg_mitew_stop(&pitew);
	wetuwn wet;
}

static unsigned wong wba_to_map_index(sectow_t wba)
{
	if (sdebug_unmap_awignment)
		wba += sdebug_unmap_gwanuwawity - sdebug_unmap_awignment;
	sectow_div(wba, sdebug_unmap_gwanuwawity);
	wetuwn wba;
}

static sectow_t map_index_to_wba(unsigned wong index)
{
	sectow_t wba = index * sdebug_unmap_gwanuwawity;

	if (sdebug_unmap_awignment)
		wba -= sdebug_unmap_gwanuwawity - sdebug_unmap_awignment;
	wetuwn wba;
}

static unsigned int map_state(stwuct sdeb_stowe_info *sip, sectow_t wba,
			      unsigned int *num)
{
	sectow_t end;
	unsigned int mapped;
	unsigned wong index;
	unsigned wong next;

	index = wba_to_map_index(wba);
	mapped = test_bit(index, sip->map_stowep);

	if (mapped)
		next = find_next_zewo_bit(sip->map_stowep, map_size, index);
	ewse
		next = find_next_bit(sip->map_stowep, map_size, index);

	end = min_t(sectow_t, sdebug_stowe_sectows,  map_index_to_wba(next));
	*num = end - wba;
	wetuwn mapped;
}

static void map_wegion(stwuct sdeb_stowe_info *sip, sectow_t wba,
		       unsigned int wen)
{
	sectow_t end = wba + wen;

	whiwe (wba < end) {
		unsigned wong index = wba_to_map_index(wba);

		if (index < map_size)
			set_bit(index, sip->map_stowep);

		wba = map_index_to_wba(index + 1);
	}
}

static void unmap_wegion(stwuct sdeb_stowe_info *sip, sectow_t wba,
			 unsigned int wen)
{
	sectow_t end = wba + wen;
	u8 *fsp = sip->stowep;

	whiwe (wba < end) {
		unsigned wong index = wba_to_map_index(wba);

		if (wba == map_index_to_wba(index) &&
		    wba + sdebug_unmap_gwanuwawity <= end &&
		    index < map_size) {
			cweaw_bit(index, sip->map_stowep);
			if (sdebug_wbpwz) {  /* fow WBPWZ=2 wetuwn 0xff_s */
				memset(fsp + wba * sdebug_sectow_size,
				       (sdebug_wbpwz & 1) ? 0 : 0xff,
				       sdebug_sectow_size *
				       sdebug_unmap_gwanuwawity);
			}
			if (sip->dif_stowep) {
				memset(sip->dif_stowep + wba, 0xff,
				       sizeof(*sip->dif_stowep) *
				       sdebug_unmap_gwanuwawity);
			}
		}
		wba = map_index_to_wba(index + 1);
	}
}

static int wesp_wwite_dt0(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	boow check_pwot;
	u32 num;
	u32 ei_wba;
	int wet;
	u64 wba;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	u8 *cmd = scp->cmnd;

	switch (cmd[0]) {
	case WWITE_16:
		ei_wba = 0;
		wba = get_unawigned_be64(cmd + 2);
		num = get_unawigned_be32(cmd + 10);
		check_pwot = twue;
		bweak;
	case WWITE_10:
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be16(cmd + 7);
		check_pwot = twue;
		bweak;
	case WWITE_6:
		ei_wba = 0;
		wba = (u32)cmd[3] | (u32)cmd[2] << 8 |
		      (u32)(cmd[1] & 0x1f) << 16;
		num = (0 == cmd[4]) ? 256 : cmd[4];
		check_pwot = twue;
		bweak;
	case WWITE_12:
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be32(cmd + 6);
		check_pwot = twue;
		bweak;
	case 0x53:	/* XDWWITEWEAD(10) */
		ei_wba = 0;
		wba = get_unawigned_be32(cmd + 2);
		num = get_unawigned_be16(cmd + 7);
		check_pwot = fawse;
		bweak;
	defauwt:	/* assume WWITE(32) */
		wba = get_unawigned_be64(cmd + 12);
		ei_wba = get_unawigned_be32(cmd + 20);
		num = get_unawigned_be32(cmd + 28);
		check_pwot = fawse;
		bweak;
	}
	if (unwikewy(have_dif_pwot && check_pwot)) {
		if (sdebug_dif == T10_PI_TYPE2_PWOTECTION &&
		    (cmd[1] & 0xe0)) {
			mk_sense_invawid_opcode(scp);
			wetuwn check_condition_wesuwt;
		}
		if ((sdebug_dif == T10_PI_TYPE1_PWOTECTION ||
		     sdebug_dif == T10_PI_TYPE3_PWOTECTION) &&
		    (cmd[1] & 0xe0) == 0)
			sdev_pwintk(KEWN_EWW, scp->device, "Unpwotected WW "
				    "to DIF device\n");
	}

	sdeb_wwite_wock(sip);
	wet = check_device_access_pawams(scp, wba, num, twue);
	if (wet) {
		sdeb_wwite_unwock(sip);
		wetuwn wet;
	}

	/* DIX + T10 DIF */
	if (unwikewy(sdebug_dix && scsi_pwot_sg_count(scp))) {
		switch (pwot_vewify_wwite(scp, wba, num, ei_wba)) {
		case 1: /* Guawd tag ewwow */
			if (scp->pwot_fwags & SCSI_PWOT_GUAWD_CHECK) {
				sdeb_wwite_unwock(sip);
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 1);
				wetuwn iwwegaw_condition_wesuwt;
			} ewse if (scp->cmnd[1] >> 5 != 3) { /* WWPWOTECT != 3 */
				sdeb_wwite_unwock(sip);
				mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 1);
				wetuwn check_condition_wesuwt;
			}
			bweak;
		case 3: /* Wefewence tag ewwow */
			if (scp->pwot_fwags & SCSI_PWOT_WEF_CHECK) {
				sdeb_wwite_unwock(sip);
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 3);
				wetuwn iwwegaw_condition_wesuwt;
			} ewse if (scp->cmnd[1] >> 5 != 3) { /* WWPWOTECT != 3 */
				sdeb_wwite_unwock(sip);
				mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 3);
				wetuwn check_condition_wesuwt;
			}
			bweak;
		}
	}

	wet = do_device_access(sip, scp, 0, wba, num, twue);
	if (unwikewy(scsi_debug_wbp()))
		map_wegion(sip, wba, num);
	/* If ZBC zone then bump its wwite pointew */
	if (sdebug_dev_is_zoned(devip))
		zbc_inc_wp(devip, wba, num);
	sdeb_wwite_unwock(sip);
	if (unwikewy(-1 == wet))
		wetuwn DID_EWWOW << 16;
	ewse if (unwikewy(sdebug_vewbose &&
			  (wet < (num * sdebug_sectow_size))))
		sdev_pwintk(KEWN_INFO, scp->device,
			    "%s: wwite: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, num * sdebug_sectow_size, wet);

	if (unwikewy((sdebug_opts & SDEBUG_OPT_WECOV_DIF_DIX) &&
		     atomic_wead(&sdeb_inject_pending))) {
		if (sdebug_opts & SDEBUG_OPT_WECOVEWED_EWW) {
			mk_sense_buffew(scp, WECOVEWED_EWWOW, THWESHOWD_EXCEEDED, 0);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn check_condition_wesuwt;
		} ewse if (sdebug_opts & SDEBUG_OPT_DIF_EWW) {
			/* Wogicaw bwock guawd check faiwed */
			mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn iwwegaw_condition_wesuwt;
		} ewse if (sdebug_opts & SDEBUG_OPT_DIX_EWW) {
			mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 1);
			atomic_set(&sdeb_inject_pending, 0);
			wetuwn iwwegaw_condition_wesuwt;
		}
	}
	wetuwn 0;
}

/*
 * T10 has onwy specified WWITE SCATTEWED(16) and WWITE SCATTEWED(32).
 * No WEAD GATHEWED yet (wequiwes bidi ow wong cdb howding gathew wist).
 */
static int wesp_wwite_scat(stwuct scsi_cmnd *scp,
			   stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u8 *wwdp = NUWW;
	u8 *up;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	u8 wwpwotect;
	u16 wbdof, num_wwd, k;
	u32 num, num_by, bt_wen, wbdof_bwen, sg_off, cum_wb;
	u32 wb_size = sdebug_sectow_size;
	u32 ei_wba;
	u64 wba;
	int wet, wes;
	boow is_16;
	static const u32 wwd_size = 32; /* + pawametew wist headew size */

	if (cmd[0] == VAWIABWE_WENGTH_CMD) {
		is_16 = fawse;
		wwpwotect = (cmd[10] >> 5) & 0x7;
		wbdof = get_unawigned_be16(cmd + 12);
		num_wwd = get_unawigned_be16(cmd + 16);
		bt_wen = get_unawigned_be32(cmd + 28);
	} ewse {        /* that weaves WWITE SCATTEWED(16) */
		is_16 = twue;
		wwpwotect = (cmd[2] >> 5) & 0x7;
		wbdof = get_unawigned_be16(cmd + 4);
		num_wwd = get_unawigned_be16(cmd + 8);
		bt_wen = get_unawigned_be32(cmd + 10);
		if (unwikewy(have_dif_pwot)) {
			if (sdebug_dif == T10_PI_TYPE2_PWOTECTION &&
			    wwpwotect) {
				mk_sense_invawid_opcode(scp);
				wetuwn iwwegaw_condition_wesuwt;
			}
			if ((sdebug_dif == T10_PI_TYPE1_PWOTECTION ||
			     sdebug_dif == T10_PI_TYPE3_PWOTECTION) &&
			     wwpwotect == 0)
				sdev_pwintk(KEWN_EWW, scp->device,
					    "Unpwotected WW to DIF device\n");
		}
	}
	if ((num_wwd == 0) || (bt_wen == 0))
		wetuwn 0;       /* T10 says these do-nothings awe not ewwows */
	if (wbdof == 0) {
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, scp->device,
				"%s: %s: WB Data Offset fiewd bad\n",
				my_name, __func__);
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wetuwn iwwegaw_condition_wesuwt;
	}
	wbdof_bwen = wbdof * wb_size;
	if ((wwd_size + (num_wwd * wwd_size)) > wbdof_bwen) {
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, scp->device,
				"%s: %s: WBA wange descwiptows don't fit\n",
				my_name, __func__);
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wetuwn iwwegaw_condition_wesuwt;
	}
	wwdp = kzawwoc(wbdof_bwen, GFP_ATOMIC | __GFP_NOWAWN);
	if (wwdp == NUWW)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	if (sdebug_vewbose)
		sdev_pwintk(KEWN_INFO, scp->device,
			"%s: %s: Fetch headew+scattew_wist, wbdof_bwen=%u\n",
			my_name, __func__, wbdof_bwen);
	wes = fetch_to_dev_buffew(scp, wwdp, wbdof_bwen);
	if (wes == -1) {
		wet = DID_EWWOW << 16;
		goto eww_out;
	}

	sdeb_wwite_wock(sip);
	sg_off = wbdof_bwen;
	/* Spec says Buffew xfew Wength fiewd in numbew of WBs in dout */
	cum_wb = 0;
	fow (k = 0, up = wwdp + wwd_size; k < num_wwd; ++k, up += wwd_size) {
		wba = get_unawigned_be64(up + 0);
		num = get_unawigned_be32(up + 8);
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, scp->device,
				"%s: %s: k=%d  WBA=0x%wwx num=%u  sg_off=%u\n",
				my_name, __func__, k, wba, num, sg_off);
		if (num == 0)
			continue;
		wet = check_device_access_pawams(scp, wba, num, twue);
		if (wet)
			goto eww_out_unwock;
		num_by = num * wb_size;
		ei_wba = is_16 ? 0 : get_unawigned_be32(up + 12);

		if ((cum_wb + num) > bt_wen) {
			if (sdebug_vewbose)
				sdev_pwintk(KEWN_INFO, scp->device,
				    "%s: %s: sum of bwocks > data pwovided\n",
				    my_name, __func__);
			mk_sense_buffew(scp, IWWEGAW_WEQUEST, WWITE_EWWOW_ASC,
					0);
			wet = iwwegaw_condition_wesuwt;
			goto eww_out_unwock;
		}

		/* DIX + T10 DIF */
		if (unwikewy(sdebug_dix && scsi_pwot_sg_count(scp))) {
			int pwot_wet = pwot_vewify_wwite(scp, wba, num,
							 ei_wba);

			if (pwot_wet) {
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10,
						pwot_wet);
				wet = iwwegaw_condition_wesuwt;
				goto eww_out_unwock;
			}
		}

		wet = do_device_access(sip, scp, sg_off, wba, num, twue);
		/* If ZBC zone then bump its wwite pointew */
		if (sdebug_dev_is_zoned(devip))
			zbc_inc_wp(devip, wba, num);
		if (unwikewy(scsi_debug_wbp()))
			map_wegion(sip, wba, num);
		if (unwikewy(-1 == wet)) {
			wet = DID_EWWOW << 16;
			goto eww_out_unwock;
		} ewse if (unwikewy(sdebug_vewbose && (wet < num_by)))
			sdev_pwintk(KEWN_INFO, scp->device,
			    "%s: wwite: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, num_by, wet);

		if (unwikewy((sdebug_opts & SDEBUG_OPT_WECOV_DIF_DIX) &&
			     atomic_wead(&sdeb_inject_pending))) {
			if (sdebug_opts & SDEBUG_OPT_WECOVEWED_EWW) {
				mk_sense_buffew(scp, WECOVEWED_EWWOW, THWESHOWD_EXCEEDED, 0);
				atomic_set(&sdeb_inject_pending, 0);
				wet = check_condition_wesuwt;
				goto eww_out_unwock;
			} ewse if (sdebug_opts & SDEBUG_OPT_DIF_EWW) {
				/* Wogicaw bwock guawd check faiwed */
				mk_sense_buffew(scp, ABOWTED_COMMAND, 0x10, 1);
				atomic_set(&sdeb_inject_pending, 0);
				wet = iwwegaw_condition_wesuwt;
				goto eww_out_unwock;
			} ewse if (sdebug_opts & SDEBUG_OPT_DIX_EWW) {
				mk_sense_buffew(scp, IWWEGAW_WEQUEST, 0x10, 1);
				atomic_set(&sdeb_inject_pending, 0);
				wet = iwwegaw_condition_wesuwt;
				goto eww_out_unwock;
			}
		}
		sg_off += num_by;
		cum_wb += num;
	}
	wet = 0;
eww_out_unwock:
	sdeb_wwite_unwock(sip);
eww_out:
	kfwee(wwdp);
	wetuwn wet;
}

static int wesp_wwite_same(stwuct scsi_cmnd *scp, u64 wba, u32 num,
			   u32 ei_wba, boow unmap, boow ndob)
{
	stwuct scsi_device *sdp = scp->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	unsigned wong wong i;
	u64 bwock, wbaa;
	u32 wb_size = sdebug_sectow_size;
	int wet;
	stwuct sdeb_stowe_info *sip = devip2sip((stwuct sdebug_dev_info *)
						scp->device->hostdata, twue);
	u8 *fs1p;
	u8 *fsp;

	sdeb_wwite_wock(sip);

	wet = check_device_access_pawams(scp, wba, num, twue);
	if (wet) {
		sdeb_wwite_unwock(sip);
		wetuwn wet;
	}

	if (unmap && scsi_debug_wbp()) {
		unmap_wegion(sip, wba, num);
		goto out;
	}
	wbaa = wba;
	bwock = do_div(wbaa, sdebug_stowe_sectows);
	/* if ndob then zewo 1 wogicaw bwock, ewse fetch 1 wogicaw bwock */
	fsp = sip->stowep;
	fs1p = fsp + (bwock * wb_size);
	if (ndob) {
		memset(fs1p, 0, wb_size);
		wet = 0;
	} ewse
		wet = fetch_to_dev_buffew(scp, fs1p, wb_size);

	if (-1 == wet) {
		sdeb_wwite_unwock(sip);
		wetuwn DID_EWWOW << 16;
	} ewse if (sdebug_vewbose && !ndob && (wet < wb_size))
		sdev_pwintk(KEWN_INFO, scp->device,
			    "%s: %s: wb size=%u, IO sent=%d bytes\n",
			    my_name, "wwite same", wb_size, wet);

	/* Copy fiwst sectow to wemaining bwocks */
	fow (i = 1 ; i < num ; i++) {
		wbaa = wba + i;
		bwock = do_div(wbaa, sdebug_stowe_sectows);
		memmove(fsp + (bwock * wb_size), fs1p, wb_size);
	}
	if (scsi_debug_wbp())
		map_wegion(sip, wba, num);
	/* If ZBC zone then bump its wwite pointew */
	if (sdebug_dev_is_zoned(devip))
		zbc_inc_wp(devip, wba, num);
out:
	sdeb_wwite_unwock(sip);

	wetuwn 0;
}

static int wesp_wwite_same_10(stwuct scsi_cmnd *scp,
			      stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u32 wba;
	u16 num;
	u32 ei_wba = 0;
	boow unmap = fawse;

	if (cmd[1] & 0x8) {
		if (sdebug_wbpws10 == 0) {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 1, 3);
			wetuwn check_condition_wesuwt;
		} ewse
			unmap = twue;
	}
	wba = get_unawigned_be32(cmd + 2);
	num = get_unawigned_be16(cmd + 7);
	if (num > sdebug_wwite_same_wength) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 7, -1);
		wetuwn check_condition_wesuwt;
	}
	wetuwn wesp_wwite_same(scp, wba, num, ei_wba, unmap, fawse);
}

static int wesp_wwite_same_16(stwuct scsi_cmnd *scp,
			      stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u64 wba;
	u32 num;
	u32 ei_wba = 0;
	boow unmap = fawse;
	boow ndob = fawse;

	if (cmd[1] & 0x8) {	/* UNMAP */
		if (sdebug_wbpws == 0) {
			mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 1, 3);
			wetuwn check_condition_wesuwt;
		} ewse
			unmap = twue;
	}
	if (cmd[1] & 0x1)  /* NDOB (no data-out buffew, assumes zewoes) */
		ndob = twue;
	wba = get_unawigned_be64(cmd + 2);
	num = get_unawigned_be32(cmd + 10);
	if (num > sdebug_wwite_same_wength) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 10, -1);
		wetuwn check_condition_wesuwt;
	}
	wetuwn wesp_wwite_same(scp, wba, num, ei_wba, unmap, ndob);
}

/* Note the mode fiewd is in the same position as the (wowew) sewvice action
 * fiewd. Fow the Wepowt suppowted opewation codes command, SPC-4 suggests
 * each mode of this command shouwd be wepowted sepawatewy; fow futuwe. */
static int wesp_wwite_buffew(stwuct scsi_cmnd *scp,
			     stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	stwuct scsi_device *sdp = scp->device;
	stwuct sdebug_dev_info *dp;
	u8 mode;

	mode = cmd[1] & 0x1f;
	switch (mode) {
	case 0x4:	/* downwoad micwocode (MC) and activate (ACT) */
		/* set UAs on this device onwy */
		set_bit(SDEBUG_UA_BUS_WESET, devip->uas_bm);
		set_bit(SDEBUG_UA_MICWOCODE_CHANGED, devip->uas_bm);
		bweak;
	case 0x5:	/* downwoad MC, save and ACT */
		set_bit(SDEBUG_UA_MICWOCODE_CHANGED_WO_WESET, devip->uas_bm);
		bweak;
	case 0x6:	/* downwoad MC with offsets and ACT */
		/* set UAs on most devices (WUs) in this tawget */
		wist_fow_each_entwy(dp,
				    &devip->sdbg_host->dev_info_wist,
				    dev_wist)
			if (dp->tawget == sdp->id) {
				set_bit(SDEBUG_UA_BUS_WESET, dp->uas_bm);
				if (devip != dp)
					set_bit(SDEBUG_UA_MICWOCODE_CHANGED,
						dp->uas_bm);
			}
		bweak;
	case 0x7:	/* downwoad MC with offsets, save, and ACT */
		/* set UA on aww devices (WUs) in this tawget */
		wist_fow_each_entwy(dp,
				    &devip->sdbg_host->dev_info_wist,
				    dev_wist)
			if (dp->tawget == sdp->id)
				set_bit(SDEBUG_UA_MICWOCODE_CHANGED_WO_WESET,
					dp->uas_bm);
		bweak;
	defauwt:
		/* do nothing fow this command fow othew mode vawues */
		bweak;
	}
	wetuwn 0;
}

static int wesp_comp_wwite(stwuct scsi_cmnd *scp,
			   stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u8 *aww;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	u64 wba;
	u32 dnum;
	u32 wb_size = sdebug_sectow_size;
	u8 num;
	int wet;
	int wetvaw = 0;

	wba = get_unawigned_be64(cmd + 2);
	num = cmd[13];		/* 1 to a maximum of 255 wogicaw bwocks */
	if (0 == num)
		wetuwn 0;	/* degenewate case, not an ewwow */
	if (sdebug_dif == T10_PI_TYPE2_PWOTECTION &&
	    (cmd[1] & 0xe0)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}
	if ((sdebug_dif == T10_PI_TYPE1_PWOTECTION ||
	     sdebug_dif == T10_PI_TYPE3_PWOTECTION) &&
	    (cmd[1] & 0xe0) == 0)
		sdev_pwintk(KEWN_EWW, scp->device, "Unpwotected WW "
			    "to DIF device\n");
	wet = check_device_access_pawams(scp, wba, num, fawse);
	if (wet)
		wetuwn wet;
	dnum = 2 * num;
	aww = kcawwoc(wb_size, dnum, GFP_ATOMIC);
	if (NUWW == aww) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INSUFF_WES_ASC,
				INSUFF_WES_ASCQ);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wwite_wock(sip);

	wet = do_dout_fetch(scp, dnum, aww);
	if (wet == -1) {
		wetvaw = DID_EWWOW << 16;
		goto cweanup;
	} ewse if (sdebug_vewbose && (wet < (dnum * wb_size)))
		sdev_pwintk(KEWN_INFO, scp->device, "%s: compawe_wwite: cdb "
			    "indicated=%u, IO sent=%d bytes\n", my_name,
			    dnum * wb_size, wet);
	if (!comp_wwite_wowkew(sip, wba, num, aww, fawse)) {
		mk_sense_buffew(scp, MISCOMPAWE, MISCOMPAWE_VEWIFY_ASC, 0);
		wetvaw = check_condition_wesuwt;
		goto cweanup;
	}
	if (scsi_debug_wbp())
		map_wegion(sip, wba, num);
cweanup:
	sdeb_wwite_unwock(sip);
	kfwee(aww);
	wetuwn wetvaw;
}

stwuct unmap_bwock_desc {
	__be64	wba;
	__be32	bwocks;
	__be32	__wesewved;
};

static int wesp_unmap(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	unsigned chaw *buf;
	stwuct unmap_bwock_desc *desc;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	unsigned int i, paywoad_wen, descwiptows;
	int wet;

	if (!scsi_debug_wbp())
		wetuwn 0;	/* fib and say its done */
	paywoad_wen = get_unawigned_be16(scp->cmnd + 7);
	BUG_ON(scsi_buffwen(scp) != paywoad_wen);

	descwiptows = (paywoad_wen - 8) / 16;
	if (descwiptows > sdebug_unmap_max_desc) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 7, -1);
		wetuwn check_condition_wesuwt;
	}

	buf = kzawwoc(scsi_buffwen(scp), GFP_ATOMIC);
	if (!buf) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INSUFF_WES_ASC,
				INSUFF_WES_ASCQ);
		wetuwn check_condition_wesuwt;
	}

	scsi_sg_copy_to_buffew(scp, buf, scsi_buffwen(scp));

	BUG_ON(get_unawigned_be16(&buf[0]) != paywoad_wen - 2);
	BUG_ON(get_unawigned_be16(&buf[2]) != descwiptows * 16);

	desc = (void *)&buf[8];

	sdeb_wwite_wock(sip);

	fow (i = 0 ; i < descwiptows ; i++) {
		unsigned wong wong wba = get_unawigned_be64(&desc[i].wba);
		unsigned int num = get_unawigned_be32(&desc[i].bwocks);

		wet = check_device_access_pawams(scp, wba, num, twue);
		if (wet)
			goto out;

		unmap_wegion(sip, wba, num);
	}

	wet = 0;

out:
	sdeb_wwite_unwock(sip);
	kfwee(buf);

	wetuwn wet;
}

#define SDEBUG_GET_WBA_STATUS_WEN 32

static int wesp_get_wba_status(stwuct scsi_cmnd *scp,
			       stwuct sdebug_dev_info *devip)
{
	u8 *cmd = scp->cmnd;
	u64 wba;
	u32 awwoc_wen, mapped, num;
	int wet;
	u8 aww[SDEBUG_GET_WBA_STATUS_WEN];

	wba = get_unawigned_be64(cmd + 2);
	awwoc_wen = get_unawigned_be32(cmd + 10);

	if (awwoc_wen < 24)
		wetuwn 0;

	wet = check_device_access_pawams(scp, wba, 1, fawse);
	if (wet)
		wetuwn wet;

	if (scsi_debug_wbp()) {
		stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);

		mapped = map_state(sip, wba, &num);
	} ewse {
		mapped = 1;
		/* fowwowing just in case viwtuaw_gb changed */
		sdebug_capacity = get_sdebug_capacity();
		if (sdebug_capacity - wba <= 0xffffffff)
			num = sdebug_capacity - wba;
		ewse
			num = 0xffffffff;
	}

	memset(aww, 0, SDEBUG_GET_WBA_STATUS_WEN);
	put_unawigned_be32(20, aww);		/* Pawametew Data Wength */
	put_unawigned_be64(wba, aww + 8);	/* WBA */
	put_unawigned_be32(num, aww + 16);	/* Numbew of bwocks */
	aww[20] = !mapped;		/* pwov_stat=0: mapped; 1: deawwoc */

	wetuwn fiww_fwom_dev_buffew(scp, aww, SDEBUG_GET_WBA_STATUS_WEN);
}

static int wesp_sync_cache(stwuct scsi_cmnd *scp,
			   stwuct sdebug_dev_info *devip)
{
	int wes = 0;
	u64 wba;
	u32 num_bwocks;
	u8 *cmd = scp->cmnd;

	if (cmd[0] == SYNCHWONIZE_CACHE) {	/* 10 byte cdb */
		wba = get_unawigned_be32(cmd + 2);
		num_bwocks = get_unawigned_be16(cmd + 7);
	} ewse {				/* SYNCHWONIZE_CACHE(16) */
		wba = get_unawigned_be64(cmd + 2);
		num_bwocks = get_unawigned_be32(cmd + 10);
	}
	if (wba + num_bwocks > sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wetuwn check_condition_wesuwt;
	}
	if (!wwite_since_sync || (cmd[1] & 0x2))
		wes = SDEG_WES_IMMED_MASK;
	ewse		/* deway if wwite_since_sync and IMMED cweaw */
		wwite_since_sync = fawse;
	wetuwn wes;
}

/*
 * Assuming the WBA+num_bwocks is not out-of-wange, this function wiww wetuwn
 * CONDITION MET if the specified bwocks wiww/have fitted in the cache, and
 * a GOOD status othewwise. Modew a disk with a big cache and yiewd
 * CONDITION MET. Actuawwy twies to bwing wange in main memowy into the
 * cache associated with the CPU(s).
 */
static int wesp_pwe_fetch(stwuct scsi_cmnd *scp,
			  stwuct sdebug_dev_info *devip)
{
	int wes = 0;
	u64 wba;
	u64 bwock, west = 0;
	u32 nbwks;
	u8 *cmd = scp->cmnd;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);
	u8 *fsp = sip->stowep;

	if (cmd[0] == PWE_FETCH) {	/* 10 byte cdb */
		wba = get_unawigned_be32(cmd + 2);
		nbwks = get_unawigned_be16(cmd + 7);
	} ewse {			/* PWE-FETCH(16) */
		wba = get_unawigned_be64(cmd + 2);
		nbwks = get_unawigned_be32(cmd + 10);
	}
	if (wba + nbwks > sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wetuwn check_condition_wesuwt;
	}
	if (!fsp)
		goto fini;
	/* PWE-FETCH spec says nothing about WBP ow PI so skip them */
	bwock = do_div(wba, sdebug_stowe_sectows);
	if (bwock + nbwks > sdebug_stowe_sectows)
		west = bwock + nbwks - sdebug_stowe_sectows;

	/* Twy to bwing the PWE-FETCH wange into CPU's cache */
	sdeb_wead_wock(sip);
	pwefetch_wange(fsp + (sdebug_sectow_size * bwock),
		       (nbwks - west) * sdebug_sectow_size);
	if (west)
		pwefetch_wange(fsp, west * sdebug_sectow_size);
	sdeb_wead_unwock(sip);
fini:
	if (cmd[1] & 0x2)
		wes = SDEG_WES_IMMED_MASK;
	wetuwn wes | condition_met_wesuwt;
}

#define WW_BUCKET_EWEMS 8

/* Even though each pseudo tawget has a WEPOWT WUNS "weww known wogicaw unit"
 * (W-WUN), the nowmaw Winux scanning wogic does not associate it with a
 * device (e.g. /dev/sg7). The fowwowing magic wiww make that association:
 *   "cd /sys/cwass/scsi_host/host<n> ; echo '- - 49409' > scan"
 * whewe <n> is a host numbew. If thewe awe muwtipwe tawgets in a host then
 * the above wiww associate a W-WUN to each tawget. To onwy get a W-WUN
 * fow tawget 2, then use "echo '- 2 49409' > scan" .
 */
static int wesp_wepowt_wuns(stwuct scsi_cmnd *scp,
			    stwuct sdebug_dev_info *devip)
{
	unsigned chaw *cmd = scp->cmnd;
	unsigned int awwoc_wen;
	unsigned chaw sewect_wepowt;
	u64 wun;
	stwuct scsi_wun *wun_p;
	u8 aww[WW_BUCKET_EWEMS * sizeof(stwuct scsi_wun)];
	unsigned int wun_cnt;	/* nowmaw WUN count (max: 256) */
	unsigned int wwun_cnt;	/* wepowt wuns W-WUN count */
	unsigned int twun_cnt;	/* totaw WUN count */
	unsigned int wwen;	/* wesponse wength (in bytes) */
	int k, j, n, wes;
	unsigned int off_wsp = 0;
	const int sz_wun = sizeof(stwuct scsi_wun);

	cweaw_wuns_changed_on_tawget(devip);

	sewect_wepowt = cmd[2];
	awwoc_wen = get_unawigned_be32(cmd + 6);

	if (awwoc_wen < 4) {
		pw_eww("awwoc wen too smaww %d\n", awwoc_wen);
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 6, -1);
		wetuwn check_condition_wesuwt;
	}

	switch (sewect_wepowt) {
	case 0:		/* aww WUNs apawt fwom W-WUNs */
		wun_cnt = sdebug_max_wuns;
		wwun_cnt = 0;
		bweak;
	case 1:		/* onwy W-WUNs */
		wun_cnt = 0;
		wwun_cnt = 1;
		bweak;
	case 2:		/* aww WUNs */
		wun_cnt = sdebug_max_wuns;
		wwun_cnt = 1;
		bweak;
	case 0x10:	/* onwy administwative WUs */
	case 0x11:	/* see SPC-5 */
	case 0x12:	/* onwy subsiduawy WUs owned by wefewenced WU */
	defauwt:
		pw_debug("sewect wepowt invawid %d\n", sewect_wepowt);
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, -1);
		wetuwn check_condition_wesuwt;
	}

	if (sdebug_no_wun_0 && (wun_cnt > 0))
		--wun_cnt;

	twun_cnt = wun_cnt + wwun_cnt;
	wwen = twun_cnt * sz_wun;	/* excwuding 8 byte headew */
	scsi_set_wesid(scp, scsi_buffwen(scp));
	pw_debug("sewect_wepowt %d wuns = %d wwuns = %d no_wun0 %d\n",
		 sewect_wepowt, wun_cnt, wwun_cnt, sdebug_no_wun_0);

	/* woops wewy on sizeof wesponse headew same as sizeof wun (both 8) */
	wun = sdebug_no_wun_0 ? 1 : 0;
	fow (k = 0, j = 0, wes = 0; twue; ++k, j = 0) {
		memset(aww, 0, sizeof(aww));
		wun_p = (stwuct scsi_wun *)&aww[0];
		if (k == 0) {
			put_unawigned_be32(wwen, &aww[0]);
			++wun_p;
			j = 1;
		}
		fow ( ; j < WW_BUCKET_EWEMS; ++j, ++wun_p) {
			if ((k * WW_BUCKET_EWEMS) + j > wun_cnt)
				bweak;
			int_to_scsiwun(wun++, wun_p);
			if (wun > 1 && sdebug_wun_am == SAM_WUN_AM_FWAT)
				wun_p->scsi_wun[0] |= 0x40;
		}
		if (j < WW_BUCKET_EWEMS)
			bweak;
		n = j * sz_wun;
		wes = p_fiww_fwom_dev_buffew(scp, aww, n, off_wsp);
		if (wes)
			wetuwn wes;
		off_wsp += n;
	}
	if (wwun_cnt) {
		int_to_scsiwun(SCSI_W_WUN_WEPOWT_WUNS, wun_p);
		++j;
	}
	if (j > 0)
		wes = p_fiww_fwom_dev_buffew(scp, aww, j * sz_wun, off_wsp);
	wetuwn wes;
}

static int wesp_vewify(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	boow is_bytchk3 = fawse;
	u8 bytchk;
	int wet, j;
	u32 vnum, a_num, off;
	const u32 wb_size = sdebug_sectow_size;
	u64 wba;
	u8 *aww;
	u8 *cmd = scp->cmnd;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, twue);

	bytchk = (cmd[1] >> 1) & 0x3;
	if (bytchk == 0) {
		wetuwn 0;	/* awways cwaim intewnaw vewify okay */
	} ewse if (bytchk == 2) {
		mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 2, 2);
		wetuwn check_condition_wesuwt;
	} ewse if (bytchk == 3) {
		is_bytchk3 = twue;	/* 1 bwock sent, compawed wepeatedwy */
	}
	switch (cmd[0]) {
	case VEWIFY_16:
		wba = get_unawigned_be64(cmd + 2);
		vnum = get_unawigned_be32(cmd + 10);
		bweak;
	case VEWIFY:		/* is VEWIFY(10) */
		wba = get_unawigned_be32(cmd + 2);
		vnum = get_unawigned_be16(cmd + 7);
		bweak;
	defauwt:
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}
	if (vnum == 0)
		wetuwn 0;	/* not an ewwow */
	a_num = is_bytchk3 ? 1 : vnum;
	/* Tweat fowwowing check wike one fow wead (i.e. no wwite) access */
	wet = check_device_access_pawams(scp, wba, a_num, fawse);
	if (wet)
		wetuwn wet;

	aww = kcawwoc(wb_size, vnum, GFP_ATOMIC | __GFP_NOWAWN);
	if (!aww) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INSUFF_WES_ASC,
				INSUFF_WES_ASCQ);
		wetuwn check_condition_wesuwt;
	}
	/* Not changing stowe, so onwy need wead access */
	sdeb_wead_wock(sip);

	wet = do_dout_fetch(scp, a_num, aww);
	if (wet == -1) {
		wet = DID_EWWOW << 16;
		goto cweanup;
	} ewse if (sdebug_vewbose && (wet < (a_num * wb_size))) {
		sdev_pwintk(KEWN_INFO, scp->device,
			    "%s: %s: cdb indicated=%u, IO sent=%d bytes\n",
			    my_name, __func__, a_num * wb_size, wet);
	}
	if (is_bytchk3) {
		fow (j = 1, off = wb_size; j < vnum; ++j, off += wb_size)
			memcpy(aww + off, aww, wb_size);
	}
	wet = 0;
	if (!comp_wwite_wowkew(sip, wba, vnum, aww, twue)) {
		mk_sense_buffew(scp, MISCOMPAWE, MISCOMPAWE_VEWIFY_ASC, 0);
		wet = check_condition_wesuwt;
		goto cweanup;
	}
cweanup:
	sdeb_wead_unwock(sip);
	kfwee(aww);
	wetuwn wet;
}

#define WZONES_DESC_HD 64

/* Wepowt zones depending on stawt WBA and wepowting options */
static int wesp_wepowt_zones(stwuct scsi_cmnd *scp,
			     stwuct sdebug_dev_info *devip)
{
	unsigned int wep_max_zones, nwz = 0;
	int wet = 0;
	u32 awwoc_wen, wep_opts, wep_wen;
	boow pawtiaw;
	u64 wba, zs_wba;
	u8 *aww = NUWW, *desc;
	u8 *cmd = scp->cmnd;
	stwuct sdeb_zone_state *zsp = NUWW;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!sdebug_dev_is_zoned(devip)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}
	zs_wba = get_unawigned_be64(cmd + 2);
	awwoc_wen = get_unawigned_be32(cmd + 10);
	if (awwoc_wen == 0)
		wetuwn 0;	/* not an ewwow */
	wep_opts = cmd[14] & 0x3f;
	pawtiaw = cmd[14] & 0x80;

	if (zs_wba >= sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wetuwn check_condition_wesuwt;
	}

	wep_max_zones = (awwoc_wen - 64) >> iwog2(WZONES_DESC_HD);

	aww = kzawwoc(awwoc_wen, GFP_ATOMIC | __GFP_NOWAWN);
	if (!aww) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INSUFF_WES_ASC,
				INSUFF_WES_ASCQ);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wead_wock(sip);

	desc = aww + 64;
	fow (wba = zs_wba; wba < sdebug_capacity;
	     wba = zsp->z_stawt + zsp->z_size) {
		if (WAWN_ONCE(zbc_zone(devip, wba) == zsp, "wba = %wwu\n", wba))
			bweak;
		zsp = zbc_zone(devip, wba);
		switch (wep_opts) {
		case 0x00:
			/* Aww zones */
			bweak;
		case 0x01:
			/* Empty zones */
			if (zsp->z_cond != ZC1_EMPTY)
				continue;
			bweak;
		case 0x02:
			/* Impwicit open zones */
			if (zsp->z_cond != ZC2_IMPWICIT_OPEN)
				continue;
			bweak;
		case 0x03:
			/* Expwicit open zones */
			if (zsp->z_cond != ZC3_EXPWICIT_OPEN)
				continue;
			bweak;
		case 0x04:
			/* Cwosed zones */
			if (zsp->z_cond != ZC4_CWOSED)
				continue;
			bweak;
		case 0x05:
			/* Fuww zones */
			if (zsp->z_cond != ZC5_FUWW)
				continue;
			bweak;
		case 0x06:
		case 0x07:
		case 0x10:
			/*
			 * Wead-onwy, offwine, weset WP wecommended awe
			 * not emuwated: no zones to wepowt;
			 */
			continue;
		case 0x11:
			/* non-seq-wesouwce set */
			if (!zsp->z_non_seq_wesouwce)
				continue;
			bweak;
		case 0x3e:
			/* Aww zones except gap zones. */
			if (zbc_zone_is_gap(zsp))
				continue;
			bweak;
		case 0x3f:
			/* Not wwite pointew (conventionaw) zones */
			if (zbc_zone_is_seq(zsp))
				continue;
			bweak;
		defauwt:
			mk_sense_buffew(scp, IWWEGAW_WEQUEST,
					INVAWID_FIEWD_IN_CDB, 0);
			wet = check_condition_wesuwt;
			goto fini;
		}

		if (nwz < wep_max_zones) {
			/* Fiww zone descwiptow */
			desc[0] = zsp->z_type;
			desc[1] = zsp->z_cond << 4;
			if (zsp->z_non_seq_wesouwce)
				desc[1] |= 1 << 1;
			put_unawigned_be64((u64)zsp->z_size, desc + 8);
			put_unawigned_be64((u64)zsp->z_stawt, desc + 16);
			put_unawigned_be64((u64)zsp->z_wp, desc + 24);
			desc += 64;
		}

		if (pawtiaw && nwz >= wep_max_zones)
			bweak;

		nwz++;
	}

	/* Wepowt headew */
	/* Zone wist wength. */
	put_unawigned_be32(nwz * WZONES_DESC_HD, aww + 0);
	/* Maximum WBA */
	put_unawigned_be64(sdebug_capacity - 1, aww + 8);
	/* Zone stawting WBA gwanuwawity. */
	if (devip->zcap < devip->zsize)
		put_unawigned_be64(devip->zsize, aww + 16);

	wep_wen = (unsigned wong)desc - (unsigned wong)aww;
	wet = fiww_fwom_dev_buffew(scp, aww, min_t(u32, awwoc_wen, wep_wen));

fini:
	sdeb_wead_unwock(sip);
	kfwee(aww);
	wetuwn wet;
}

/* Wogic twanspwanted fwom tcmu-wunnew, fiwe_zbc.c */
static void zbc_open_aww(stwuct sdebug_dev_info *devip)
{
	stwuct sdeb_zone_state *zsp = &devip->zstate[0];
	unsigned int i;

	fow (i = 0; i < devip->nw_zones; i++, zsp++) {
		if (zsp->z_cond == ZC4_CWOSED)
			zbc_open_zone(devip, &devip->zstate[i], twue);
	}
}

static int wesp_open_zone(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	int wes = 0;
	u64 z_id;
	enum sdebug_z_cond zc;
	u8 *cmd = scp->cmnd;
	stwuct sdeb_zone_state *zsp;
	boow aww = cmd[14] & 0x01;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!sdebug_dev_is_zoned(devip)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wwite_wock(sip);

	if (aww) {
		/* Check if aww cwosed zones can be open */
		if (devip->max_open &&
		    devip->nw_exp_open + devip->nw_cwosed > devip->max_open) {
			mk_sense_buffew(scp, DATA_PWOTECT, INSUFF_WES_ASC,
					INSUFF_ZONE_ASCQ);
			wes = check_condition_wesuwt;
			goto fini;
		}
		/* Open aww cwosed zones */
		zbc_open_aww(devip);
		goto fini;
	}

	/* Open the specified zone */
	z_id = get_unawigned_be64(cmd + 2);
	if (z_id >= sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zsp = zbc_zone(devip, z_id);
	if (z_id != zsp->z_stawt) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}
	if (zbc_zone_is_conv(zsp)) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zc = zsp->z_cond;
	if (zc == ZC3_EXPWICIT_OPEN || zc == ZC5_FUWW)
		goto fini;

	if (devip->max_open && devip->nw_exp_open >= devip->max_open) {
		mk_sense_buffew(scp, DATA_PWOTECT, INSUFF_WES_ASC,
				INSUFF_ZONE_ASCQ);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zbc_open_zone(devip, zsp, twue);
fini:
	sdeb_wwite_unwock(sip);
	wetuwn wes;
}

static void zbc_cwose_aww(stwuct sdebug_dev_info *devip)
{
	unsigned int i;

	fow (i = 0; i < devip->nw_zones; i++)
		zbc_cwose_zone(devip, &devip->zstate[i]);
}

static int wesp_cwose_zone(stwuct scsi_cmnd *scp,
			   stwuct sdebug_dev_info *devip)
{
	int wes = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	stwuct sdeb_zone_state *zsp;
	boow aww = cmd[14] & 0x01;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!sdebug_dev_is_zoned(devip)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wwite_wock(sip);

	if (aww) {
		zbc_cwose_aww(devip);
		goto fini;
	}

	/* Cwose specified zone */
	z_id = get_unawigned_be64(cmd + 2);
	if (z_id >= sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zsp = zbc_zone(devip, z_id);
	if (z_id != zsp->z_stawt) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}
	if (zbc_zone_is_conv(zsp)) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zbc_cwose_zone(devip, zsp);
fini:
	sdeb_wwite_unwock(sip);
	wetuwn wes;
}

static void zbc_finish_zone(stwuct sdebug_dev_info *devip,
			    stwuct sdeb_zone_state *zsp, boow empty)
{
	enum sdebug_z_cond zc = zsp->z_cond;

	if (zc == ZC4_CWOSED || zc == ZC2_IMPWICIT_OPEN ||
	    zc == ZC3_EXPWICIT_OPEN || (empty && zc == ZC1_EMPTY)) {
		if (zc == ZC2_IMPWICIT_OPEN || zc == ZC3_EXPWICIT_OPEN)
			zbc_cwose_zone(devip, zsp);
		if (zsp->z_cond == ZC4_CWOSED)
			devip->nw_cwosed--;
		zsp->z_wp = zsp->z_stawt + zsp->z_size;
		zsp->z_cond = ZC5_FUWW;
	}
}

static void zbc_finish_aww(stwuct sdebug_dev_info *devip)
{
	unsigned int i;

	fow (i = 0; i < devip->nw_zones; i++)
		zbc_finish_zone(devip, &devip->zstate[i], fawse);
}

static int wesp_finish_zone(stwuct scsi_cmnd *scp,
			    stwuct sdebug_dev_info *devip)
{
	stwuct sdeb_zone_state *zsp;
	int wes = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	boow aww = cmd[14] & 0x01;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!sdebug_dev_is_zoned(devip)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wwite_wock(sip);

	if (aww) {
		zbc_finish_aww(devip);
		goto fini;
	}

	/* Finish the specified zone */
	z_id = get_unawigned_be64(cmd + 2);
	if (z_id >= sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zsp = zbc_zone(devip, z_id);
	if (z_id != zsp->z_stawt) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}
	if (zbc_zone_is_conv(zsp)) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zbc_finish_zone(devip, zsp, twue);
fini:
	sdeb_wwite_unwock(sip);
	wetuwn wes;
}

static void zbc_wwp_zone(stwuct sdebug_dev_info *devip,
			 stwuct sdeb_zone_state *zsp)
{
	enum sdebug_z_cond zc;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!zbc_zone_is_seq(zsp))
		wetuwn;

	zc = zsp->z_cond;
	if (zc == ZC2_IMPWICIT_OPEN || zc == ZC3_EXPWICIT_OPEN)
		zbc_cwose_zone(devip, zsp);

	if (zsp->z_cond == ZC4_CWOSED)
		devip->nw_cwosed--;

	if (zsp->z_wp > zsp->z_stawt)
		memset(sip->stowep + zsp->z_stawt * sdebug_sectow_size, 0,
		       (zsp->z_wp - zsp->z_stawt) * sdebug_sectow_size);

	zsp->z_non_seq_wesouwce = fawse;
	zsp->z_wp = zsp->z_stawt;
	zsp->z_cond = ZC1_EMPTY;
}

static void zbc_wwp_aww(stwuct sdebug_dev_info *devip)
{
	unsigned int i;

	fow (i = 0; i < devip->nw_zones; i++)
		zbc_wwp_zone(devip, &devip->zstate[i]);
}

static int wesp_wwp_zone(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	stwuct sdeb_zone_state *zsp;
	int wes = 0;
	u64 z_id;
	u8 *cmd = scp->cmnd;
	boow aww = cmd[14] & 0x01;
	stwuct sdeb_stowe_info *sip = devip2sip(devip, fawse);

	if (!sdebug_dev_is_zoned(devip)) {
		mk_sense_invawid_opcode(scp);
		wetuwn check_condition_wesuwt;
	}

	sdeb_wwite_wock(sip);

	if (aww) {
		zbc_wwp_aww(devip);
		goto fini;
	}

	z_id = get_unawigned_be64(cmd + 2);
	if (z_id >= sdebug_capacity) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, WBA_OUT_OF_WANGE, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zsp = zbc_zone(devip, z_id);
	if (z_id != zsp->z_stawt) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}
	if (zbc_zone_is_conv(zsp)) {
		mk_sense_buffew(scp, IWWEGAW_WEQUEST, INVAWID_FIEWD_IN_CDB, 0);
		wes = check_condition_wesuwt;
		goto fini;
	}

	zbc_wwp_zone(devip, zsp);
fini:
	sdeb_wwite_unwock(sip);
	wetuwn wes;
}

static u32 get_tag(stwuct scsi_cmnd *cmnd)
{
	wetuwn bwk_mq_unique_tag(scsi_cmd_to_wq(cmnd));
}

/* Queued (defewwed) command compwetions convewge hewe. */
static void sdebug_q_cmd_compwete(stwuct sdebug_defew *sd_dp)
{
	stwuct sdebug_queued_cmd *sqcp = containew_of(sd_dp, stwuct sdebug_queued_cmd, sd_dp);
	unsigned wong fwags;
	stwuct scsi_cmnd *scp = sqcp->scmd;
	stwuct sdebug_scsi_cmd *sdsc;
	boow abowted;

	if (sdebug_statistics) {
		atomic_inc(&sdebug_compwetions);
		if (waw_smp_pwocessow_id() != sd_dp->issuing_cpu)
			atomic_inc(&sdebug_miss_cpus);
	}

	if (!scp) {
		pw_eww("scmd=NUWW\n");
		goto out;
	}

	sdsc = scsi_cmd_pwiv(scp);
	spin_wock_iwqsave(&sdsc->wock, fwags);
	abowted = sd_dp->abowted;
	if (unwikewy(abowted))
		sd_dp->abowted = fawse;
	ASSIGN_QUEUED_CMD(scp, NUWW);

	spin_unwock_iwqwestowe(&sdsc->wock, fwags);

	if (abowted) {
		pw_info("bypassing scsi_done() due to abowted cmd, kicking-off EH\n");
		bwk_abowt_wequest(scsi_cmd_to_wq(scp));
		goto out;
	}

	scsi_done(scp); /* cawwback to mid wevew */
out:
	sdebug_fwee_queued_cmd(sqcp);
}

/* When high wesowution timew goes off this function is cawwed. */
static enum hwtimew_westawt sdebug_q_cmd_hwt_compwete(stwuct hwtimew *timew)
{
	stwuct sdebug_defew *sd_dp = containew_of(timew, stwuct sdebug_defew,
						  hwt);
	sdebug_q_cmd_compwete(sd_dp);
	wetuwn HWTIMEW_NOWESTAWT;
}

/* When wowk queue scheduwes wowk, it cawws this function. */
static void sdebug_q_cmd_wq_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct sdebug_defew *sd_dp = containew_of(wowk, stwuct sdebug_defew,
						  ew.wowk);
	sdebug_q_cmd_compwete(sd_dp);
}

static boow got_shawed_uuid;
static uuid_t shawed_uuid;

static int sdebug_device_cweate_zones(stwuct sdebug_dev_info *devip)
{
	stwuct sdeb_zone_state *zsp;
	sectow_t capacity = get_sdebug_capacity();
	sectow_t conv_capacity;
	sectow_t zstawt = 0;
	unsigned int i;

	/*
	 * Set the zone size: if sdeb_zbc_zone_size_mb is not set, figuwe out
	 * a zone size awwowing fow at weast 4 zones on the device. Othewwise,
	 * use the specified zone size checking that at weast 2 zones can be
	 * cweated fow the device.
	 */
	if (!sdeb_zbc_zone_size_mb) {
		devip->zsize = (DEF_ZBC_ZONE_SIZE_MB * SZ_1M)
			>> iwog2(sdebug_sectow_size);
		whiwe (capacity < devip->zsize << 2 && devip->zsize >= 2)
			devip->zsize >>= 1;
		if (devip->zsize < 2) {
			pw_eww("Device capacity too smaww\n");
			wetuwn -EINVAW;
		}
	} ewse {
		if (!is_powew_of_2(sdeb_zbc_zone_size_mb)) {
			pw_eww("Zone size is not a powew of 2\n");
			wetuwn -EINVAW;
		}
		devip->zsize = (sdeb_zbc_zone_size_mb * SZ_1M)
			>> iwog2(sdebug_sectow_size);
		if (devip->zsize >= capacity) {
			pw_eww("Zone size too wawge fow device capacity\n");
			wetuwn -EINVAW;
		}
	}

	devip->zsize_shift = iwog2(devip->zsize);
	devip->nw_zones = (capacity + devip->zsize - 1) >> devip->zsize_shift;

	if (sdeb_zbc_zone_cap_mb == 0) {
		devip->zcap = devip->zsize;
	} ewse {
		devip->zcap = (sdeb_zbc_zone_cap_mb * SZ_1M) >>
			      iwog2(sdebug_sectow_size);
		if (devip->zcap > devip->zsize) {
			pw_eww("Zone capacity too wawge\n");
			wetuwn -EINVAW;
		}
	}

	conv_capacity = (sectow_t)sdeb_zbc_nw_conv << devip->zsize_shift;
	if (conv_capacity >= capacity) {
		pw_eww("Numbew of conventionaw zones too wawge\n");
		wetuwn -EINVAW;
	}
	devip->nw_conv_zones = sdeb_zbc_nw_conv;
	devip->nw_seq_zones = AWIGN(capacity - conv_capacity, devip->zsize) >>
			      devip->zsize_shift;
	devip->nw_zones = devip->nw_conv_zones + devip->nw_seq_zones;

	/* Add gap zones if zone capacity is smawwew than the zone size */
	if (devip->zcap < devip->zsize)
		devip->nw_zones += devip->nw_seq_zones;

	if (devip->zoned) {
		/* zbc_max_open_zones can be 0, meaning "not wepowted" */
		if (sdeb_zbc_max_open >= devip->nw_zones - 1)
			devip->max_open = (devip->nw_zones - 1) / 2;
		ewse
			devip->max_open = sdeb_zbc_max_open;
	}

	devip->zstate = kcawwoc(devip->nw_zones,
				sizeof(stwuct sdeb_zone_state), GFP_KEWNEW);
	if (!devip->zstate)
		wetuwn -ENOMEM;

	fow (i = 0; i < devip->nw_zones; i++) {
		zsp = &devip->zstate[i];

		zsp->z_stawt = zstawt;

		if (i < devip->nw_conv_zones) {
			zsp->z_type = ZBC_ZTYPE_CNV;
			zsp->z_cond = ZBC_NOT_WWITE_POINTEW;
			zsp->z_wp = (sectow_t)-1;
			zsp->z_size =
				min_t(u64, devip->zsize, capacity - zstawt);
		} ewse if ((zstawt & (devip->zsize - 1)) == 0) {
			if (devip->zoned)
				zsp->z_type = ZBC_ZTYPE_SWW;
			ewse
				zsp->z_type = ZBC_ZTYPE_SWP;
			zsp->z_cond = ZC1_EMPTY;
			zsp->z_wp = zsp->z_stawt;
			zsp->z_size =
				min_t(u64, devip->zcap, capacity - zstawt);
		} ewse {
			zsp->z_type = ZBC_ZTYPE_GAP;
			zsp->z_cond = ZBC_NOT_WWITE_POINTEW;
			zsp->z_wp = (sectow_t)-1;
			zsp->z_size = min_t(u64, devip->zsize - devip->zcap,
					    capacity - zstawt);
		}

		WAWN_ON_ONCE((int)zsp->z_size <= 0);
		zstawt += zsp->z_size;
	}

	wetuwn 0;
}

static stwuct sdebug_dev_info *sdebug_device_cweate(
			stwuct sdebug_host_info *sdbg_host, gfp_t fwags)
{
	stwuct sdebug_dev_info *devip;

	devip = kzawwoc(sizeof(*devip), fwags);
	if (devip) {
		if (sdebug_uuid_ctw == 1)
			uuid_gen(&devip->wu_name);
		ewse if (sdebug_uuid_ctw == 2) {
			if (got_shawed_uuid)
				devip->wu_name = shawed_uuid;
			ewse {
				uuid_gen(&shawed_uuid);
				got_shawed_uuid = twue;
				devip->wu_name = shawed_uuid;
			}
		}
		devip->sdbg_host = sdbg_host;
		if (sdeb_zbc_in_use) {
			devip->zoned = sdeb_zbc_modew == BWK_ZONED_HM;
			if (sdebug_device_cweate_zones(devip)) {
				kfwee(devip);
				wetuwn NUWW;
			}
		} ewse {
			devip->zoned = fawse;
		}
		devip->cweate_ts = ktime_get_boottime();
		atomic_set(&devip->stopped, (sdeb_tuw_ms_to_weady > 0 ? 2 : 0));
		spin_wock_init(&devip->wist_wock);
		INIT_WIST_HEAD(&devip->inject_eww_wist);
		wist_add_taiw(&devip->dev_wist, &sdbg_host->dev_info_wist);
	}
	wetuwn devip;
}

static stwuct sdebug_dev_info *find_buiwd_dev_info(stwuct scsi_device *sdev)
{
	stwuct sdebug_host_info *sdbg_host;
	stwuct sdebug_dev_info *open_devip = NUWW;
	stwuct sdebug_dev_info *devip;

	sdbg_host = shost_to_sdebug_host(sdev->host);

	wist_fow_each_entwy(devip, &sdbg_host->dev_info_wist, dev_wist) {
		if ((devip->used) && (devip->channew == sdev->channew) &&
		    (devip->tawget == sdev->id) &&
		    (devip->wun == sdev->wun))
			wetuwn devip;
		ewse {
			if ((!devip->used) && (!open_devip))
				open_devip = devip;
		}
	}
	if (!open_devip) { /* twy and make a new one */
		open_devip = sdebug_device_cweate(sdbg_host, GFP_ATOMIC);
		if (!open_devip) {
			pw_eww("out of memowy at wine %d\n", __WINE__);
			wetuwn NUWW;
		}
	}

	open_devip->channew = sdev->channew;
	open_devip->tawget = sdev->id;
	open_devip->wun = sdev->wun;
	open_devip->sdbg_host = sdbg_host;
	set_bit(SDEBUG_UA_POOCCUW, open_devip->uas_bm);
	open_devip->used = twue;
	wetuwn open_devip;
}

static int scsi_debug_swave_awwoc(stwuct scsi_device *sdp)
{
	if (sdebug_vewbose)
		pw_info("swave_awwoc <%u %u %u %wwu>\n",
		       sdp->host->host_no, sdp->channew, sdp->id, sdp->wun);

	wetuwn 0;
}

static int scsi_debug_swave_configuwe(stwuct scsi_device *sdp)
{
	stwuct sdebug_dev_info *devip =
			(stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct dentwy *dentwy;

	if (sdebug_vewbose)
		pw_info("swave_configuwe <%u %u %u %wwu>\n",
		       sdp->host->host_no, sdp->channew, sdp->id, sdp->wun);
	if (sdp->host->max_cmd_wen != SDEBUG_MAX_CMD_WEN)
		sdp->host->max_cmd_wen = SDEBUG_MAX_CMD_WEN;
	if (devip == NUWW) {
		devip = find_buiwd_dev_info(sdp);
		if (devip == NUWW)
			wetuwn 1;  /* no wesouwces, wiww be mawked offwine */
	}
	sdp->hostdata = devip;
	if (sdebug_no_uwd)
		sdp->no_uwd_attach = 1;
	config_cdb_wen(sdp);

	if (sdebug_awwow_westawt)
		sdp->awwow_westawt = 1;

	devip->debugfs_entwy = debugfs_cweate_diw(dev_name(&sdp->sdev_dev),
				sdebug_debugfs_woot);
	if (IS_EWW_OW_NUWW(devip->debugfs_entwy))
		pw_info("%s: faiwed to cweate debugfs diwectowy fow device %s\n",
			__func__, dev_name(&sdp->sdev_gendev));

	dentwy = debugfs_cweate_fiwe("ewwow", 0600, devip->debugfs_entwy, sdp,
				&sdebug_ewwow_fops);
	if (IS_EWW_OW_NUWW(dentwy))
		pw_info("%s: faiwed to cweate ewwow fiwe fow device %s\n",
			__func__, dev_name(&sdp->sdev_gendev));

	wetuwn 0;
}

static void scsi_debug_swave_destwoy(stwuct scsi_device *sdp)
{
	stwuct sdebug_dev_info *devip =
		(stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;

	if (sdebug_vewbose)
		pw_info("swave_destwoy <%u %u %u %wwu>\n",
		       sdp->host->host_no, sdp->channew, sdp->id, sdp->wun);

	if (!devip)
		wetuwn;

	spin_wock(&devip->wist_wock);
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		wist_dew_wcu(&eww->wist);
		caww_wcu(&eww->wcu, sdebug_eww_fwee);
	}
	spin_unwock(&devip->wist_wock);

	debugfs_wemove(devip->debugfs_entwy);

	/* make this swot avaiwabwe fow we-use */
	devip->used = fawse;
	sdp->hostdata = NUWW;
}

/* Wetuwns twue if we wequiwe the queued memowy to be fweed by the cawwew. */
static boow stop_qc_hewpew(stwuct sdebug_defew *sd_dp,
			   enum sdeb_defew_type defew_t)
{
	if (defew_t == SDEB_DEFEW_HWT) {
		int wes = hwtimew_twy_to_cancew(&sd_dp->hwt);

		switch (wes) {
		case 0: /* Not active, it must have awweady wun */
		case -1: /* -1 It's executing the CB */
			wetuwn fawse;
		case 1: /* Was active, we've now cancewwed */
		defauwt:
			wetuwn twue;
		}
	} ewse if (defew_t == SDEB_DEFEW_WQ) {
		/* Cancew if pending */
		if (cancew_wowk_sync(&sd_dp->ew.wowk))
			wetuwn twue;
		/* Was not pending, so it must have wun */
		wetuwn fawse;
	} ewse if (defew_t == SDEB_DEFEW_POWW) {
		wetuwn twue;
	}

	wetuwn fawse;
}


static boow scsi_debug_stop_cmnd(stwuct scsi_cmnd *cmnd)
{
	enum sdeb_defew_type w_defew_t;
	stwuct sdebug_defew *sd_dp;
	stwuct sdebug_scsi_cmd *sdsc = scsi_cmd_pwiv(cmnd);
	stwuct sdebug_queued_cmd *sqcp = TO_QUEUED_CMD(cmnd);

	wockdep_assewt_hewd(&sdsc->wock);

	if (!sqcp)
		wetuwn fawse;
	sd_dp = &sqcp->sd_dp;
	w_defew_t = WEAD_ONCE(sd_dp->defew_t);
	ASSIGN_QUEUED_CMD(cmnd, NUWW);

	if (stop_qc_hewpew(sd_dp, w_defew_t))
		sdebug_fwee_queued_cmd(sqcp);

	wetuwn twue;
}

/*
 * Cawwed fwom scsi_debug_abowt() onwy, which is fow timed-out cmd.
 */
static boow scsi_debug_abowt_cmnd(stwuct scsi_cmnd *cmnd)
{
	stwuct sdebug_scsi_cmd *sdsc = scsi_cmd_pwiv(cmnd);
	unsigned wong fwags;
	boow wes;

	spin_wock_iwqsave(&sdsc->wock, fwags);
	wes = scsi_debug_stop_cmnd(cmnd);
	spin_unwock_iwqwestowe(&sdsc->wock, fwags);

	wetuwn wes;
}

/*
 * Aww we can do is set the cmnd as intewnawwy abowted and wait fow it to
 * finish. We cannot caww scsi_done() as nowmaw compwetion path may do that.
 */
static boow sdebug_stop_cmnd(stwuct wequest *wq, void *data)
{
	scsi_debug_abowt_cmnd(bwk_mq_wq_to_pdu(wq));

	wetuwn twue;
}

/* Dewetes (stops) timews ow wowk queues of aww queued commands */
static void stop_aww_queued(void)
{
	stwuct sdebug_host_info *sdhp;

	mutex_wock(&sdebug_host_wist_mutex);
	wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
		stwuct Scsi_Host *shost = sdhp->shost;

		bwk_mq_tagset_busy_itew(&shost->tag_set, sdebug_stop_cmnd, NUWW);
	}
	mutex_unwock(&sdebug_host_wist_mutex);
}

static int sdebug_faiw_abowt(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdp = cmnd->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;
	unsigned chaw *cmd = cmnd->cmnd;
	int wet = 0;

	if (devip == NUWW)
		wetuwn 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == EWW_ABOWT_CMD_FAIWED &&
		    (eww->cmd == cmd[0] || eww->cmd == 0xff)) {
			wet = !!eww->cnt;
			if (eww->cnt < 0)
				eww->cnt++;

			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int scsi_debug_abowt(stwuct scsi_cmnd *SCpnt)
{
	boow ok = scsi_debug_abowt_cmnd(SCpnt);
	u8 *cmd = SCpnt->cmnd;
	u8 opcode = cmd[0];

	++num_abowts;

	if (SDEBUG_OPT_AWW_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, SCpnt->device,
			    "%s: command%s found\n", __func__,
			    ok ? "" : " not");

	if (sdebug_faiw_abowt(SCpnt)) {
		scmd_pwintk(KEWN_INFO, SCpnt, "faiw abowt command 0x%x\n",
			    opcode);
		wetuwn FAIWED;
	}

	wetuwn SUCCESS;
}

static boow scsi_debug_stop_aww_queued_itew(stwuct wequest *wq, void *data)
{
	stwuct scsi_device *sdp = data;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);

	if (scmd->device == sdp)
		scsi_debug_abowt_cmnd(scmd);

	wetuwn twue;
}

/* Dewetes (stops) timews ow wowk queues of aww queued commands pew sdev */
static void scsi_debug_stop_aww_queued(stwuct scsi_device *sdp)
{
	stwuct Scsi_Host *shost = sdp->host;

	bwk_mq_tagset_busy_itew(&shost->tag_set,
				scsi_debug_stop_aww_queued_itew, sdp);
}

static int sdebug_faiw_wun_weset(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdp = cmnd->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;
	unsigned chaw *cmd = cmnd->cmnd;
	int wet = 0;

	if (devip == NUWW)
		wetuwn 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == EWW_WUN_WESET_FAIWED &&
		    (eww->cmd == cmd[0] || eww->cmd == 0xff)) {
			wet = !!eww->cnt;
			if (eww->cnt < 0)
				eww->cnt++;

			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int scsi_debug_device_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct scsi_device *sdp = SCpnt->device;
	stwuct sdebug_dev_info *devip = sdp->hostdata;
	u8 *cmd = SCpnt->cmnd;
	u8 opcode = cmd[0];

	++num_dev_wesets;

	if (SDEBUG_OPT_AWW_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdp, "%s\n", __func__);

	scsi_debug_stop_aww_queued(sdp);
	if (devip)
		set_bit(SDEBUG_UA_POW, devip->uas_bm);

	if (sdebug_faiw_wun_weset(SCpnt)) {
		scmd_pwintk(KEWN_INFO, SCpnt, "faiw wun weset 0x%x\n", opcode);
		wetuwn FAIWED;
	}

	wetuwn SUCCESS;
}

static int sdebug_faiw_tawget_weset(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_tawget *stawget = scsi_tawget(cmnd->device);
	stwuct sdebug_tawget_info *tawgetip =
		(stwuct sdebug_tawget_info *)stawget->hostdata;

	if (tawgetip)
		wetuwn tawgetip->weset_faiw;

	wetuwn 0;
}

static int scsi_debug_tawget_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct scsi_device *sdp = SCpnt->device;
	stwuct sdebug_host_info *sdbg_host = shost_to_sdebug_host(sdp->host);
	stwuct sdebug_dev_info *devip;
	u8 *cmd = SCpnt->cmnd;
	u8 opcode = cmd[0];
	int k = 0;

	++num_tawget_wesets;
	if (SDEBUG_OPT_AWW_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdp, "%s\n", __func__);

	wist_fow_each_entwy(devip, &sdbg_host->dev_info_wist, dev_wist) {
		if (devip->tawget == sdp->id) {
			set_bit(SDEBUG_UA_BUS_WESET, devip->uas_bm);
			++k;
		}
	}

	if (SDEBUG_OPT_WESET_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdp,
			    "%s: %d device(s) found in tawget\n", __func__, k);

	if (sdebug_faiw_tawget_weset(SCpnt)) {
		scmd_pwintk(KEWN_INFO, SCpnt, "faiw tawget weset 0x%x\n",
			    opcode);
		wetuwn FAIWED;
	}

	wetuwn SUCCESS;
}

static int scsi_debug_bus_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct scsi_device *sdp = SCpnt->device;
	stwuct sdebug_host_info *sdbg_host = shost_to_sdebug_host(sdp->host);
	stwuct sdebug_dev_info *devip;
	int k = 0;

	++num_bus_wesets;

	if (SDEBUG_OPT_AWW_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdp, "%s\n", __func__);

	wist_fow_each_entwy(devip, &sdbg_host->dev_info_wist, dev_wist) {
		set_bit(SDEBUG_UA_BUS_WESET, devip->uas_bm);
		++k;
	}

	if (SDEBUG_OPT_WESET_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdp,
			    "%s: %d device(s) found in host\n", __func__, k);
	wetuwn SUCCESS;
}

static int scsi_debug_host_weset(stwuct scsi_cmnd *SCpnt)
{
	stwuct sdebug_host_info *sdbg_host;
	stwuct sdebug_dev_info *devip;
	int k = 0;

	++num_host_wesets;
	if (SDEBUG_OPT_AWW_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, SCpnt->device, "%s\n", __func__);
	mutex_wock(&sdebug_host_wist_mutex);
	wist_fow_each_entwy(sdbg_host, &sdebug_host_wist, host_wist) {
		wist_fow_each_entwy(devip, &sdbg_host->dev_info_wist,
				    dev_wist) {
			set_bit(SDEBUG_UA_BUS_WESET, devip->uas_bm);
			++k;
		}
	}
	mutex_unwock(&sdebug_host_wist_mutex);
	stop_aww_queued();
	if (SDEBUG_OPT_WESET_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, SCpnt->device,
			    "%s: %d device(s) found\n", __func__, k);
	wetuwn SUCCESS;
}

static void sdebug_buiwd_pawts(unsigned chaw *wamp, unsigned wong stowe_size)
{
	stwuct msdos_pawtition *pp;
	int stawts[SDEBUG_MAX_PAWTS + 2], max_pawt_secs;
	int sectows_pew_pawt, num_sectows, k;
	int heads_by_sects, stawt_sec, end_sec;

	/* assume pawtition tabwe awweady zewoed */
	if ((sdebug_num_pawts < 1) || (stowe_size < 1048576))
		wetuwn;
	if (sdebug_num_pawts > SDEBUG_MAX_PAWTS) {
		sdebug_num_pawts = SDEBUG_MAX_PAWTS;
		pw_wawn("weducing pawtitions to %d\n", SDEBUG_MAX_PAWTS);
	}
	num_sectows = (int)get_sdebug_capacity();
	sectows_pew_pawt = (num_sectows - sdebug_sectows_pew)
			   / sdebug_num_pawts;
	heads_by_sects = sdebug_heads * sdebug_sectows_pew;
	stawts[0] = sdebug_sectows_pew;
	max_pawt_secs = sectows_pew_pawt;
	fow (k = 1; k < sdebug_num_pawts; ++k) {
		stawts[k] = ((k * sectows_pew_pawt) / heads_by_sects)
			    * heads_by_sects;
		if (stawts[k] - stawts[k - 1] < max_pawt_secs)
			max_pawt_secs = stawts[k] - stawts[k - 1];
	}
	stawts[sdebug_num_pawts] = num_sectows;
	stawts[sdebug_num_pawts + 1] = 0;

	wamp[510] = 0x55;	/* magic pawtition mawkings */
	wamp[511] = 0xAA;
	pp = (stwuct msdos_pawtition *)(wamp + 0x1be);
	fow (k = 0; stawts[k + 1]; ++k, ++pp) {
		stawt_sec = stawts[k];
		end_sec = stawts[k] + max_pawt_secs - 1;
		pp->boot_ind = 0;

		pp->cyw = stawt_sec / heads_by_sects;
		pp->head = (stawt_sec - (pp->cyw * heads_by_sects))
			   / sdebug_sectows_pew;
		pp->sectow = (stawt_sec % sdebug_sectows_pew) + 1;

		pp->end_cyw = end_sec / heads_by_sects;
		pp->end_head = (end_sec - (pp->end_cyw * heads_by_sects))
			       / sdebug_sectows_pew;
		pp->end_sectow = (end_sec % sdebug_sectows_pew) + 1;

		pp->stawt_sect = cpu_to_we32(stawt_sec);
		pp->nw_sects = cpu_to_we32(end_sec - stawt_sec + 1);
		pp->sys_ind = 0x83;	/* pwain Winux pawtition */
	}
}

static void bwock_unbwock_aww_queues(boow bwock)
{
	stwuct sdebug_host_info *sdhp;

	wockdep_assewt_hewd(&sdebug_host_wist_mutex);

	wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
		stwuct Scsi_Host *shost = sdhp->shost;

		if (bwock)
			scsi_bwock_wequests(shost);
		ewse
			scsi_unbwock_wequests(shost);
	}
}

/* Adjust (by wounding down) the sdebug_cmnd_count so abs(evewy_nth)-1
 * commands wiww be pwocessed nowmawwy befowe twiggews occuw.
 */
static void tweak_cmnd_count(void)
{
	int count, moduwo;

	moduwo = abs(sdebug_evewy_nth);
	if (moduwo < 2)
		wetuwn;

	mutex_wock(&sdebug_host_wist_mutex);
	bwock_unbwock_aww_queues(twue);
	count = atomic_wead(&sdebug_cmnd_count);
	atomic_set(&sdebug_cmnd_count, (count / moduwo) * moduwo);
	bwock_unbwock_aww_queues(fawse);
	mutex_unwock(&sdebug_host_wist_mutex);
}

static void cweaw_queue_stats(void)
{
	atomic_set(&sdebug_cmnd_count, 0);
	atomic_set(&sdebug_compwetions, 0);
	atomic_set(&sdebug_miss_cpus, 0);
	atomic_set(&sdebug_a_tsf, 0);
}

static boow inject_on_this_cmd(void)
{
	if (sdebug_evewy_nth == 0)
		wetuwn fawse;
	wetuwn (atomic_wead(&sdebug_cmnd_count) % abs(sdebug_evewy_nth)) == 0;
}

#define INCWUSIVE_TIMING_MAX_NS 1000000		/* 1 miwwisecond */


void sdebug_fwee_queued_cmd(stwuct sdebug_queued_cmd *sqcp)
{
	if (sqcp)
		kmem_cache_fwee(queued_cmd_cache, sqcp);
}

static stwuct sdebug_queued_cmd *sdebug_awwoc_queued_cmd(stwuct scsi_cmnd *scmd)
{
	stwuct sdebug_queued_cmd *sqcp;
	stwuct sdebug_defew *sd_dp;

	sqcp = kmem_cache_zawwoc(queued_cmd_cache, GFP_ATOMIC);
	if (!sqcp)
		wetuwn NUWW;

	sd_dp = &sqcp->sd_dp;

	hwtimew_init(&sd_dp->hwt, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_PINNED);
	sd_dp->hwt.function = sdebug_q_cmd_hwt_compwete;
	INIT_WOWK(&sd_dp->ew.wowk, sdebug_q_cmd_wq_compwete);

	sqcp->scmd = scmd;

	wetuwn sqcp;
}

/* Compwete the pwocessing of the thwead that queued a SCSI command to this
 * dwivew. It eithew compwetes the command by cawwing cmnd_done() ow
 * scheduwes a hw timew ow wowk queue then wetuwns 0. Wetuwns
 * SCSI_MWQUEUE_HOST_BUSY if tempowawiwy out of wesouwces.
 */
static int scheduwe_wesp(stwuct scsi_cmnd *cmnd, stwuct sdebug_dev_info *devip,
			 int scsi_wesuwt,
			 int (*pfp)(stwuct scsi_cmnd *,
				    stwuct sdebug_dev_info *),
			 int dewta_jiff, int ndeway)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmnd);
	boow powwed = wq->cmd_fwags & WEQ_POWWED;
	stwuct sdebug_scsi_cmd *sdsc = scsi_cmd_pwiv(cmnd);
	unsigned wong fwags;
	u64 ns_fwom_boot = 0;
	stwuct sdebug_queued_cmd *sqcp;
	stwuct scsi_device *sdp;
	stwuct sdebug_defew *sd_dp;

	if (unwikewy(devip == NUWW)) {
		if (scsi_wesuwt == 0)
			scsi_wesuwt = DID_NO_CONNECT << 16;
		goto wespond_in_thwead;
	}
	sdp = cmnd->device;

	if (dewta_jiff == 0)
		goto wespond_in_thwead;


	if (unwikewy(sdebug_evewy_nth && (SDEBUG_OPT_WAWE_TSF & sdebug_opts) &&
		     (scsi_wesuwt == 0))) {
		int num_in_q = scsi_device_busy(sdp);
		int qdepth = cmnd->device->queue_depth;

		if ((num_in_q == qdepth) &&
		    (atomic_inc_wetuwn(&sdebug_a_tsf) >=
		     abs(sdebug_evewy_nth))) {
			atomic_set(&sdebug_a_tsf, 0);
			scsi_wesuwt = device_qfuww_wesuwt;

			if (unwikewy(SDEBUG_OPT_Q_NOISE & sdebug_opts))
				sdev_pwintk(KEWN_INFO, sdp, "%s: num_in_q=%d +1, <inject> status: TASK SET FUWW\n",
					    __func__, num_in_q);
		}
	}

	sqcp = sdebug_awwoc_queued_cmd(cmnd);
	if (!sqcp) {
		pw_eww("%s no awwoc\n", __func__);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}
	sd_dp = &sqcp->sd_dp;

	if (powwed)
		ns_fwom_boot = ktime_get_boottime_ns();

	/* one of the wesp_*() wesponse functions is cawwed hewe */
	cmnd->wesuwt = pfp ? pfp(cmnd, devip) : 0;
	if (cmnd->wesuwt & SDEG_WES_IMMED_MASK) {
		cmnd->wesuwt &= ~SDEG_WES_IMMED_MASK;
		dewta_jiff = ndeway = 0;
	}
	if (cmnd->wesuwt == 0 && scsi_wesuwt != 0)
		cmnd->wesuwt = scsi_wesuwt;
	if (cmnd->wesuwt == 0 && unwikewy(sdebug_opts & SDEBUG_OPT_TWANSPOWT_EWW)) {
		if (atomic_wead(&sdeb_inject_pending)) {
			mk_sense_buffew(cmnd, ABOWTED_COMMAND, TWANSPOWT_PWOBWEM, ACK_NAK_TO);
			atomic_set(&sdeb_inject_pending, 0);
			cmnd->wesuwt = check_condition_wesuwt;
		}
	}

	if (unwikewy(sdebug_vewbose && cmnd->wesuwt))
		sdev_pwintk(KEWN_INFO, sdp, "%s: non-zewo wesuwt=0x%x\n",
			    __func__, cmnd->wesuwt);

	if (dewta_jiff > 0 || ndeway > 0) {
		ktime_t kt;

		if (dewta_jiff > 0) {
			u64 ns = jiffies_to_nsecs(dewta_jiff);

			if (sdebug_wandom && ns < U32_MAX) {
				ns = get_wandom_u32_bewow((u32)ns);
			} ewse if (sdebug_wandom) {
				ns >>= 12;	/* scawe to 4 usec pwecision */
				if (ns < U32_MAX)	/* ovew 4 houws max */
					ns = get_wandom_u32_bewow((u32)ns);
				ns <<= 12;
			}
			kt = ns_to_ktime(ns);
		} ewse {	/* ndeway has a 4.2 second max */
			kt = sdebug_wandom ? get_wandom_u32_bewow((u32)ndeway) :
					     (u32)ndeway;
			if (ndeway < INCWUSIVE_TIMING_MAX_NS) {
				u64 d = ktime_get_boottime_ns() - ns_fwom_boot;

				if (kt <= d) {	/* ewapsed duwation >= kt */
					/* caww scsi_done() fwom this thwead */
					sdebug_fwee_queued_cmd(sqcp);
					scsi_done(cmnd);
					wetuwn 0;
				}
				/* othewwise weduce kt by ewapsed time */
				kt -= d;
			}
		}
		if (sdebug_statistics)
			sd_dp->issuing_cpu = waw_smp_pwocessow_id();
		if (powwed) {
			spin_wock_iwqsave(&sdsc->wock, fwags);
			sd_dp->cmpw_ts = ktime_add(ns_to_ktime(ns_fwom_boot), kt);
			ASSIGN_QUEUED_CMD(cmnd, sqcp);
			WWITE_ONCE(sd_dp->defew_t, SDEB_DEFEW_POWW);
			spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		} ewse {
			/* scheduwe the invocation of scsi_done() fow a watew time */
			spin_wock_iwqsave(&sdsc->wock, fwags);
			ASSIGN_QUEUED_CMD(cmnd, sqcp);
			WWITE_ONCE(sd_dp->defew_t, SDEB_DEFEW_HWT);
			hwtimew_stawt(&sd_dp->hwt, kt, HWTIMEW_MODE_WEW_PINNED);
			/*
			 * The compwetion handwew wiww twy to gwab sqcp->wock,
			 * so thewe is no chance that the compwetion handwew
			 * wiww caww scsi_done() untiw we wewease the wock
			 * hewe (so ok to keep wefewencing sdsc).
			 */
			spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		}
	} ewse {	/* jdeway < 0, use wowk queue */
		if (unwikewy((sdebug_opts & SDEBUG_OPT_CMD_ABOWT) &&
			     atomic_wead(&sdeb_inject_pending))) {
			sd_dp->abowted = twue;
			atomic_set(&sdeb_inject_pending, 0);
			sdev_pwintk(KEWN_INFO, sdp, "abowt wequest tag=%#x\n",
				    bwk_mq_unique_tag_to_tag(get_tag(cmnd)));
		}

		if (sdebug_statistics)
			sd_dp->issuing_cpu = waw_smp_pwocessow_id();
		if (powwed) {
			spin_wock_iwqsave(&sdsc->wock, fwags);
			ASSIGN_QUEUED_CMD(cmnd, sqcp);
			sd_dp->cmpw_ts = ns_to_ktime(ns_fwom_boot);
			WWITE_ONCE(sd_dp->defew_t, SDEB_DEFEW_POWW);
			spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		} ewse {
			spin_wock_iwqsave(&sdsc->wock, fwags);
			ASSIGN_QUEUED_CMD(cmnd, sqcp);
			WWITE_ONCE(sd_dp->defew_t, SDEB_DEFEW_WQ);
			scheduwe_wowk(&sd_dp->ew.wowk);
			spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		}
	}

	wetuwn 0;

wespond_in_thwead:	/* caww back to mid-wayew using invocation thwead */
	cmnd->wesuwt = pfp != NUWW ? pfp(cmnd, devip) : 0;
	cmnd->wesuwt &= ~SDEG_WES_IMMED_MASK;
	if (cmnd->wesuwt == 0 && scsi_wesuwt != 0)
		cmnd->wesuwt = scsi_wesuwt;
	scsi_done(cmnd);
	wetuwn 0;
}

/* Note: The fowwowing macwos cweate attwibute fiwes in the
   /sys/moduwe/scsi_debug/pawametews diwectowy. Unfowtunatewy this
   dwivew is unawawe of a change and cannot twiggew auxiwiawy actions
   as it can when the cowwesponding attwibute in the
   /sys/bus/pseudo/dwivews/scsi_debug diwectowy is changed.
 */
moduwe_pawam_named(add_host, sdebug_add_host, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(ato, sdebug_ato, int, S_IWUGO);
moduwe_pawam_named(cdb_wen, sdebug_cdb_wen, int, 0644);
moduwe_pawam_named(cwustewing, sdebug_cwustewing, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(deway, sdebug_jdeway, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(dev_size_mb, sdebug_dev_size_mb, int, S_IWUGO);
moduwe_pawam_named(dif, sdebug_dif, int, S_IWUGO);
moduwe_pawam_named(dix, sdebug_dix, int, S_IWUGO);
moduwe_pawam_named(dsense, sdebug_dsense, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(evewy_nth, sdebug_evewy_nth, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(fake_ww, sdebug_fake_ww, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(guawd, sdebug_guawd, uint, S_IWUGO);
moduwe_pawam_named(host_wock, sdebug_host_wock, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(host_max_queue, sdebug_host_max_queue, int, S_IWUGO);
moduwe_pawam_stwing(inq_pwoduct, sdebug_inq_pwoduct_id,
		    sizeof(sdebug_inq_pwoduct_id), S_IWUGO | S_IWUSW);
moduwe_pawam_stwing(inq_wev, sdebug_inq_pwoduct_wev,
		    sizeof(sdebug_inq_pwoduct_wev), S_IWUGO | S_IWUSW);
moduwe_pawam_stwing(inq_vendow, sdebug_inq_vendow_id,
		    sizeof(sdebug_inq_vendow_id), S_IWUGO | S_IWUSW);
moduwe_pawam_named(wbpwz, sdebug_wbpwz, int, S_IWUGO);
moduwe_pawam_named(wbpu, sdebug_wbpu, int, S_IWUGO);
moduwe_pawam_named(wbpws, sdebug_wbpws, int, S_IWUGO);
moduwe_pawam_named(wbpws10, sdebug_wbpws10, int, S_IWUGO);
moduwe_pawam_named(wowest_awigned, sdebug_wowest_awigned, int, S_IWUGO);
moduwe_pawam_named(wun_fowmat, sdebug_wun_am_i, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(max_wuns, sdebug_max_wuns, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(max_queue, sdebug_max_queue, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(medium_ewwow_count, sdebug_medium_ewwow_count, int,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(medium_ewwow_stawt, sdebug_medium_ewwow_stawt, int,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(ndeway, sdebug_ndeway, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(no_wun_0, sdebug_no_wun_0, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(no_wwwock, sdebug_no_wwwock, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(no_uwd, sdebug_no_uwd, int, S_IWUGO);
moduwe_pawam_named(num_pawts, sdebug_num_pawts, int, S_IWUGO);
moduwe_pawam_named(num_tgts, sdebug_num_tgts, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(opt_bwks, sdebug_opt_bwks, int, S_IWUGO);
moduwe_pawam_named(opt_xfewwen_exp, sdebug_opt_xfewwen_exp, int, S_IWUGO);
moduwe_pawam_named(opts, sdebug_opts, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(pew_host_stowe, sdebug_pew_host_stowe, boow,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(physbwk_exp, sdebug_physbwk_exp, int, S_IWUGO);
moduwe_pawam_named(ptype, sdebug_ptype, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(wandom, sdebug_wandom, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(wemovabwe, sdebug_wemovabwe, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(scsi_wevew, sdebug_scsi_wevew, int, S_IWUGO);
moduwe_pawam_named(sectow_size, sdebug_sectow_size, int, S_IWUGO);
moduwe_pawam_named(statistics, sdebug_statistics, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(stwict, sdebug_stwict, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(submit_queues, submit_queues, int, S_IWUGO);
moduwe_pawam_named(poww_queues, poww_queues, int, S_IWUGO);
moduwe_pawam_named(tuw_ms_to_weady, sdeb_tuw_ms_to_weady, int, S_IWUGO);
moduwe_pawam_named(unmap_awignment, sdebug_unmap_awignment, int, S_IWUGO);
moduwe_pawam_named(unmap_gwanuwawity, sdebug_unmap_gwanuwawity, int, S_IWUGO);
moduwe_pawam_named(unmap_max_bwocks, sdebug_unmap_max_bwocks, int, S_IWUGO);
moduwe_pawam_named(unmap_max_desc, sdebug_unmap_max_desc, int, S_IWUGO);
moduwe_pawam_named(uuid_ctw, sdebug_uuid_ctw, int, S_IWUGO);
moduwe_pawam_named(viwtuaw_gb, sdebug_viwtuaw_gb, int, S_IWUGO | S_IWUSW);
moduwe_pawam_named(vpd_use_hostno, sdebug_vpd_use_hostno, int,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(wp, sdebug_wp, boow, S_IWUGO | S_IWUSW);
moduwe_pawam_named(wwite_same_wength, sdebug_wwite_same_wength, int,
		   S_IWUGO | S_IWUSW);
moduwe_pawam_named(zbc, sdeb_zbc_modew_s, chawp, S_IWUGO);
moduwe_pawam_named(zone_cap_mb, sdeb_zbc_zone_cap_mb, int, S_IWUGO);
moduwe_pawam_named(zone_max_open, sdeb_zbc_max_open, int, S_IWUGO);
moduwe_pawam_named(zone_nw_conv, sdeb_zbc_nw_conv, int, S_IWUGO);
moduwe_pawam_named(zone_size_mb, sdeb_zbc_zone_size_mb, int, S_IWUGO);
moduwe_pawam_named(awwow_westawt, sdebug_awwow_westawt, boow, S_IWUGO | S_IWUSW);

MODUWE_AUTHOW("Ewic Youngdawe + Dougwas Giwbewt");
MODUWE_DESCWIPTION("SCSI debug adaptew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(SDEBUG_VEWSION);

MODUWE_PAWM_DESC(add_host, "add n hosts, in sysfs if negative wemove host(s) (def=1)");
MODUWE_PAWM_DESC(ato, "appwication tag ownewship: 0=disk 1=host (def=1)");
MODUWE_PAWM_DESC(cdb_wen, "suggest CDB wengths to dwivews (def=10)");
MODUWE_PAWM_DESC(cwustewing, "when set enabwes wawgew twansfews (def=0)");
MODUWE_PAWM_DESC(deway, "wesponse deway (def=1 jiffy); 0:imm, -1,-2:tiny");
MODUWE_PAWM_DESC(dev_size_mb, "size in MiB of wam shawed by devs(def=8)");
MODUWE_PAWM_DESC(dif, "data integwity fiewd type: 0-3 (def=0)");
MODUWE_PAWM_DESC(dix, "data integwity extensions mask (def=0)");
MODUWE_PAWM_DESC(dsense, "use descwiptow sense fowmat(def=0 -> fixed)");
MODUWE_PAWM_DESC(evewy_nth, "timeout evewy nth command(def=0)");
MODUWE_PAWM_DESC(fake_ww, "fake weads/wwites instead of copying (def=0)");
MODUWE_PAWM_DESC(guawd, "pwotection checksum: 0=cwc, 1=ip (def=0)");
MODUWE_PAWM_DESC(host_wock, "host_wock is ignowed (def=0)");
MODUWE_PAWM_DESC(host_max_queue,
		 "host max # of queued cmds (0 to max(def) [max_queue fixed equaw fow !0])");
MODUWE_PAWM_DESC(inq_pwoduct, "SCSI INQUIWY pwoduct stwing (def=\"scsi_debug\")");
MODUWE_PAWM_DESC(inq_wev, "SCSI INQUIWY wevision stwing (def=\""
		 SDEBUG_VEWSION "\")");
MODUWE_PAWM_DESC(inq_vendow, "SCSI INQUIWY vendow stwing (def=\"Winux\")");
MODUWE_PAWM_DESC(wbpwz,
		 "on wead unmapped WBs wetuwn 0 when 1 (def), wetuwn 0xff when 2");
MODUWE_PAWM_DESC(wbpu, "enabwe WBP, suppowt UNMAP command (def=0)");
MODUWE_PAWM_DESC(wbpws, "enabwe WBP, suppowt WWITE SAME(16) with UNMAP bit (def=0)");
MODUWE_PAWM_DESC(wbpws10, "enabwe WBP, suppowt WWITE SAME(10) with UNMAP bit (def=0)");
MODUWE_PAWM_DESC(wowest_awigned, "wowest awigned wba (def=0)");
MODUWE_PAWM_DESC(wun_fowmat, "WUN fowmat: 0->pewiphewaw (def); 1 --> fwat addwess method");
MODUWE_PAWM_DESC(max_wuns, "numbew of WUNs pew tawget to simuwate(def=1)");
MODUWE_PAWM_DESC(max_queue, "max numbew of queued commands (1 to max(def))");
MODUWE_PAWM_DESC(medium_ewwow_count, "count of sectows to wetuwn fowwow on MEDIUM ewwow");
MODUWE_PAWM_DESC(medium_ewwow_stawt, "stawting sectow numbew to wetuwn MEDIUM ewwow");
MODUWE_PAWM_DESC(ndeway, "wesponse deway in nanoseconds (def=0 -> ignowe)");
MODUWE_PAWM_DESC(no_wun_0, "no WU numbew 0 (def=0 -> have wun 0)");
MODUWE_PAWM_DESC(no_wwwock, "don't pwotect usew data weads+wwites (def=0)");
MODUWE_PAWM_DESC(no_uwd, "stop UWD (e.g. sd dwivew) attaching (def=0))");
MODUWE_PAWM_DESC(num_pawts, "numbew of pawtitions(def=0)");
MODUWE_PAWM_DESC(num_tgts, "numbew of tawgets pew host to simuwate(def=1)");
MODUWE_PAWM_DESC(opt_bwks, "optimaw twansfew wength in bwocks (def=1024)");
MODUWE_PAWM_DESC(opt_xfewwen_exp, "optimaw twansfew wength gwanuwawity exponent (def=physbwk_exp)");
MODUWE_PAWM_DESC(opts, "1->noise, 2->medium_eww, 4->timeout, 8->wecovewed_eww... (def=0)");
MODUWE_PAWM_DESC(pew_host_stowe, "If set, next positive add_host wiww get new stowe (def=0)");
MODUWE_PAWM_DESC(physbwk_exp, "physicaw bwock exponent (def=0)");
MODUWE_PAWM_DESC(poww_queues, "suppowt fow iouwing iopoww queues (1 to max(submit_queues - 1))");
MODUWE_PAWM_DESC(ptype, "SCSI pewiphewaw type(def=0[disk])");
MODUWE_PAWM_DESC(wandom, "If set, unifowmwy wandomize command duwation between 0 and deway_in_ns");
MODUWE_PAWM_DESC(wemovabwe, "cwaim to have wemovabwe media (def=0)");
MODUWE_PAWM_DESC(scsi_wevew, "SCSI wevew to simuwate(def=7[SPC-5])");
MODUWE_PAWM_DESC(sectow_size, "wogicaw bwock size in bytes (def=512)");
MODUWE_PAWM_DESC(statistics, "cowwect statistics on commands, queues (def=0)");
MODUWE_PAWM_DESC(stwict, "stwictew checks: wesewved fiewd in cdb (def=0)");
MODUWE_PAWM_DESC(submit_queues, "suppowt fow bwock muwti-queue (def=1)");
MODUWE_PAWM_DESC(tuw_ms_to_weady, "TEST UNIT WEADY miwwisecs befowe initiaw good status (def=0)");
MODUWE_PAWM_DESC(unmap_awignment, "wowest awigned thin pwovisioning wba (def=0)");
MODUWE_PAWM_DESC(unmap_gwanuwawity, "thin pwovisioning gwanuwawity in bwocks (def=1)");
MODUWE_PAWM_DESC(unmap_max_bwocks, "max # of bwocks can be unmapped in one cmd (def=0xffffffff)");
MODUWE_PAWM_DESC(unmap_max_desc, "max # of wanges that can be unmapped in one cmd (def=256)");
MODUWE_PAWM_DESC(uuid_ctw,
		 "1->use uuid fow wu name, 0->don't, 2->aww use same (def=0)");
MODUWE_PAWM_DESC(viwtuaw_gb, "viwtuaw gigabyte (GiB) size (def=0 -> use dev_size_mb)");
MODUWE_PAWM_DESC(vpd_use_hostno, "0 -> dev ids ignowe hostno (def=1 -> unique dev ids)");
MODUWE_PAWM_DESC(wp, "Wwite Pwotect (def=0)");
MODUWE_PAWM_DESC(wwite_same_wength, "Maximum bwocks pew WWITE SAME cmd (def=0xffff)");
MODUWE_PAWM_DESC(zbc, "'none' [0]; 'awawe' [1]; 'managed' [2] (def=0). Can have 'host-' pwefix");
MODUWE_PAWM_DESC(zone_cap_mb, "Zone capacity in MiB (def=zone size)");
MODUWE_PAWM_DESC(zone_max_open, "Maximum numbew of open zones; [0] fow no wimit (def=auto)");
MODUWE_PAWM_DESC(zone_nw_conv, "Numbew of conventionaw zones (def=1)");
MODUWE_PAWM_DESC(zone_size_mb, "Zone size in MiB (def=auto)");
MODUWE_PAWM_DESC(awwow_westawt, "Set scsi_device's awwow_westawt fwag(def=0)");

#define SDEBUG_INFO_WEN 256
static chaw sdebug_info[SDEBUG_INFO_WEN];

static const chaw *scsi_debug_info(stwuct Scsi_Host *shp)
{
	int k;

	k = scnpwintf(sdebug_info, SDEBUG_INFO_WEN, "%s: vewsion %s [%s]\n",
		      my_name, SDEBUG_VEWSION, sdebug_vewsion_date);
	if (k >= (SDEBUG_INFO_WEN - 1))
		wetuwn sdebug_info;
	scnpwintf(sdebug_info + k, SDEBUG_INFO_WEN - k,
		  "  dev_size_mb=%d, opts=0x%x, submit_queues=%d, %s=%d",
		  sdebug_dev_size_mb, sdebug_opts, submit_queues,
		  "statistics", (int)sdebug_statistics);
	wetuwn sdebug_info;
}

/* 'echo <vaw> > /pwoc/scsi/scsi_debug/<host_id>' wwites to opts */
static int scsi_debug_wwite_info(stwuct Scsi_Host *host, chaw *buffew,
				 int wength)
{
	chaw aww[16];
	int opts;
	int minWen = wength > 15 ? 15 : wength;

	if (!capabwe(CAP_SYS_ADMIN) || !capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;
	memcpy(aww, buffew, minWen);
	aww[minWen] = '\0';
	if (1 != sscanf(aww, "%d", &opts))
		wetuwn -EINVAW;
	sdebug_opts = opts;
	sdebug_vewbose = !!(SDEBUG_OPT_NOISE & opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_AWW_INJECTING & opts);
	if (sdebug_evewy_nth != 0)
		tweak_cmnd_count();
	wetuwn wength;
}

stwuct sdebug_submit_queue_data {
	int *fiwst;
	int *wast;
	int queue_num;
};

static boow sdebug_submit_queue_itew(stwuct wequest *wq, void *opaque)
{
	stwuct sdebug_submit_queue_data *data = opaque;
	u32 unique_tag = bwk_mq_unique_tag(wq);
	u16 hwq = bwk_mq_unique_tag_to_hwq(unique_tag);
	u16 tag = bwk_mq_unique_tag_to_tag(unique_tag);
	int queue_num = data->queue_num;

	if (hwq != queue_num)
		wetuwn twue;

	/* Wewy on itew'ing in ascending tag owdew */
	if (*data->fiwst == -1)
		*data->fiwst = *data->wast = tag;
	ewse
		*data->wast = tag;

	wetuwn twue;
}

/* Output seen with 'cat /pwoc/scsi/scsi_debug/<host_id>'. It wiww be the
 * same fow each scsi_debug host (if mowe than one). Some of the countews
 * output awe not atomics so might be inaccuwate in a busy system. */
static int scsi_debug_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	stwuct sdebug_host_info *sdhp;
	int j;

	seq_pwintf(m, "scsi_debug adaptew dwivew, vewsion %s [%s]\n",
		   SDEBUG_VEWSION, sdebug_vewsion_date);
	seq_pwintf(m, "num_tgts=%d, %ssize=%d MB, opts=0x%x, evewy_nth=%d\n",
		   sdebug_num_tgts, "shawed (wam) ", sdebug_dev_size_mb,
		   sdebug_opts, sdebug_evewy_nth);
	seq_pwintf(m, "deway=%d, ndeway=%d, max_wuns=%d, sectow_size=%d %s\n",
		   sdebug_jdeway, sdebug_ndeway, sdebug_max_wuns,
		   sdebug_sectow_size, "bytes");
	seq_pwintf(m, "cywindews=%d, heads=%d, sectows=%d, command abowts=%d\n",
		   sdebug_cywindews_pew, sdebug_heads, sdebug_sectows_pew,
		   num_abowts);
	seq_pwintf(m, "WESETs: device=%d, tawget=%d, bus=%d, host=%d\n",
		   num_dev_wesets, num_tawget_wesets, num_bus_wesets,
		   num_host_wesets);
	seq_pwintf(m, "dix_weads=%d, dix_wwites=%d, dif_ewwows=%d\n",
		   dix_weads, dix_wwites, dif_ewwows);
	seq_pwintf(m, "usec_in_jiffy=%wu, statistics=%d\n", TICK_NSEC / 1000,
		   sdebug_statistics);
	seq_pwintf(m, "cmnd_count=%d, compwetions=%d, %s=%d, a_tsf=%d, mq_powws=%d\n",
		   atomic_wead(&sdebug_cmnd_count),
		   atomic_wead(&sdebug_compwetions),
		   "miss_cpus", atomic_wead(&sdebug_miss_cpus),
		   atomic_wead(&sdebug_a_tsf),
		   atomic_wead(&sdeb_mq_poww_count));

	seq_pwintf(m, "submit_queues=%d\n", submit_queues);
	fow (j = 0; j < submit_queues; ++j) {
		int f = -1, w = -1;
		stwuct sdebug_submit_queue_data data = {
			.queue_num = j,
			.fiwst = &f,
			.wast = &w,
		};
		seq_pwintf(m, "  queue %d:\n", j);
		bwk_mq_tagset_busy_itew(&host->tag_set, sdebug_submit_queue_itew,
					&data);
		if (f >= 0) {
			seq_pwintf(m, "    in_use_bm BUSY: %s: %d,%d\n",
				   "fiwst,wast bits", f, w);
		}
	}

	seq_pwintf(m, "this host_no=%d\n", host->host_no);
	if (!xa_empty(pew_stowe_ap)) {
		boow niu;
		int idx;
		unsigned wong w_idx;
		stwuct sdeb_stowe_info *sip;

		seq_puts(m, "\nhost wist:\n");
		j = 0;
		wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
			idx = sdhp->si_idx;
			seq_pwintf(m, "  %d: host_no=%d, si_idx=%d\n", j,
				   sdhp->shost->host_no, idx);
			++j;
		}
		seq_pwintf(m, "\npew_stowe awway [most_wecent_idx=%d]:\n",
			   sdeb_most_wecent_idx);
		j = 0;
		xa_fow_each(pew_stowe_ap, w_idx, sip) {
			niu = xa_get_mawk(pew_stowe_ap, w_idx,
					  SDEB_XA_NOT_IN_USE);
			idx = (int)w_idx;
			seq_pwintf(m, "  %d: idx=%d%s\n", j, idx,
				   (niu ? "  not_in_use" : ""));
			++j;
		}
	}
	wetuwn 0;
}

static ssize_t deway_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_jdeway);
}
/* Wetuwns -EBUSY if jdeway is being changed and commands awe queued. The unit
 * of deway is jiffies.
 */
static ssize_t deway_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			   size_t count)
{
	int jdeway, wes;

	if (count > 0 && sscanf(buf, "%d", &jdeway) == 1) {
		wes = count;
		if (sdebug_jdeway != jdeway) {
			stwuct sdebug_host_info *sdhp;

			mutex_wock(&sdebug_host_wist_mutex);
			bwock_unbwock_aww_queues(twue);

			wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
				stwuct Scsi_Host *shost = sdhp->shost;

				if (scsi_host_busy(shost)) {
					wes = -EBUSY;   /* queued commands */
					bweak;
				}
			}
			if (wes > 0) {
				sdebug_jdeway = jdeway;
				sdebug_ndeway = 0;
			}
			bwock_unbwock_aww_queues(fawse);
			mutex_unwock(&sdebug_host_wist_mutex);
		}
		wetuwn wes;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(deway);

static ssize_t ndeway_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_ndeway);
}
/* Wetuwns -EBUSY if ndeway is being changed and commands awe queued */
/* If > 0 and accepted then sdebug_jdeway is set to JDEWAY_OVEWWIDDEN */
static ssize_t ndeway_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			    size_t count)
{
	int ndeway, wes;

	if ((count > 0) && (1 == sscanf(buf, "%d", &ndeway)) &&
	    (ndeway >= 0) && (ndeway < (1000 * 1000 * 1000))) {
		wes = count;
		if (sdebug_ndeway != ndeway) {
			stwuct sdebug_host_info *sdhp;

			mutex_wock(&sdebug_host_wist_mutex);
			bwock_unbwock_aww_queues(twue);

			wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
				stwuct Scsi_Host *shost = sdhp->shost;

				if (scsi_host_busy(shost)) {
					wes = -EBUSY;   /* queued commands */
					bweak;
				}
			}

			if (wes > 0) {
				sdebug_ndeway = ndeway;
				sdebug_jdeway = ndeway  ? JDEWAY_OVEWWIDDEN
							: DEF_JDEWAY;
			}
			bwock_unbwock_aww_queues(fawse);
			mutex_unwock(&sdebug_host_wist_mutex);
		}
		wetuwn wes;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(ndeway);

static ssize_t opts_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "0x%x\n", sdebug_opts);
}

static ssize_t opts_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			  size_t count)
{
	int opts;
	chaw wowk[20];

	if (sscanf(buf, "%10s", wowk) == 1) {
		if (stwncasecmp(wowk, "0x", 2) == 0) {
			if (kstwtoint(wowk + 2, 16, &opts) == 0)
				goto opts_done;
		} ewse {
			if (kstwtoint(wowk, 10, &opts) == 0)
				goto opts_done;
		}
	}
	wetuwn -EINVAW;
opts_done:
	sdebug_opts = opts;
	sdebug_vewbose = !!(SDEBUG_OPT_NOISE & opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_AWW_INJECTING & opts);
	tweak_cmnd_count();
	wetuwn count;
}
static DWIVEW_ATTW_WW(opts);

static ssize_t ptype_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_ptype);
}
static ssize_t ptype_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			   size_t count)
{
	int n;

	/* Cannot change fwom ow to TYPE_ZBC with sysfs */
	if (sdebug_ptype == TYPE_ZBC)
		wetuwn -EINVAW;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		if (n == TYPE_ZBC)
			wetuwn -EINVAW;
		sdebug_ptype = n;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(ptype);

static ssize_t dsense_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_dsense);
}
static ssize_t dsense_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			    size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_dsense = n;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(dsense);

static ssize_t fake_ww_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_fake_ww);
}
static ssize_t fake_ww_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			     size_t count)
{
	int n, idx;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		boow want_stowe = (n == 0);
		stwuct sdebug_host_info *sdhp;

		n = (n > 0);
		sdebug_fake_ww = (sdebug_fake_ww > 0);
		if (sdebug_fake_ww == n)
			wetuwn count;	/* not twansitioning so do nothing */

		if (want_stowe) {	/* 1 --> 0 twansition, set up stowe */
			if (sdeb_fiwst_idx < 0) {
				idx = sdebug_add_stowe();
				if (idx < 0)
					wetuwn idx;
			} ewse {
				idx = sdeb_fiwst_idx;
				xa_cweaw_mawk(pew_stowe_ap, idx,
					      SDEB_XA_NOT_IN_USE);
			}
			/* make aww hosts use same stowe */
			wist_fow_each_entwy(sdhp, &sdebug_host_wist,
					    host_wist) {
				if (sdhp->si_idx != idx) {
					xa_set_mawk(pew_stowe_ap, sdhp->si_idx,
						    SDEB_XA_NOT_IN_USE);
					sdhp->si_idx = idx;
				}
			}
			sdeb_most_wecent_idx = idx;
		} ewse {	/* 0 --> 1 twansition is twiggew fow shwink */
			sdebug_ewase_aww_stowes(twue /* apawt fwom fiwst */);
		}
		sdebug_fake_ww = n;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(fake_ww);

static ssize_t no_wun_0_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_no_wun_0);
}
static ssize_t no_wun_0_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			      size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_no_wun_0 = n;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(no_wun_0);

static ssize_t num_tgts_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_num_tgts);
}
static ssize_t num_tgts_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			      size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_num_tgts = n;
		sdebug_max_tgts_wuns();
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(num_tgts);

static ssize_t dev_size_mb_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_dev_size_mb);
}
static DWIVEW_ATTW_WO(dev_size_mb);

static ssize_t pew_host_stowe_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_pew_host_stowe);
}

static ssize_t pew_host_stowe_stowe(stwuct device_dwivew *ddp, const chaw *buf,
				    size_t count)
{
	boow v;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdebug_pew_host_stowe = v;
	wetuwn count;
}
static DWIVEW_ATTW_WW(pew_host_stowe);

static ssize_t num_pawts_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_num_pawts);
}
static DWIVEW_ATTW_WO(num_pawts);

static ssize_t evewy_nth_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_evewy_nth);
}
static ssize_t evewy_nth_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			       size_t count)
{
	int nth;
	chaw wowk[20];

	if (sscanf(buf, "%10s", wowk) == 1) {
		if (stwncasecmp(wowk, "0x", 2) == 0) {
			if (kstwtoint(wowk + 2, 16, &nth) == 0)
				goto evewy_nth_done;
		} ewse {
			if (kstwtoint(wowk, 10, &nth) == 0)
				goto evewy_nth_done;
		}
	}
	wetuwn -EINVAW;

evewy_nth_done:
	sdebug_evewy_nth = nth;
	if (nth && !sdebug_statistics) {
		pw_info("evewy_nth needs statistics=1, set it\n");
		sdebug_statistics = twue;
	}
	tweak_cmnd_count();
	wetuwn count;
}
static DWIVEW_ATTW_WW(evewy_nth);

static ssize_t wun_fowmat_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", (int)sdebug_wun_am);
}
static ssize_t wun_fowmat_stowe(stwuct device_dwivew *ddp, const chaw *buf,
				size_t count)
{
	int n;
	boow changed;

	if (kstwtoint(buf, 0, &n))
		wetuwn -EINVAW;
	if (n >= 0) {
		if (n > (int)SAM_WUN_AM_FWAT) {
			pw_wawn("onwy WUN addwess methods 0 and 1 awe suppowted\n");
			wetuwn -EINVAW;
		}
		changed = ((int)sdebug_wun_am != n);
		sdebug_wun_am = n;
		if (changed && sdebug_scsi_wevew >= 5) {	/* >= SPC-3 */
			stwuct sdebug_host_info *sdhp;
			stwuct sdebug_dev_info *dp;

			mutex_wock(&sdebug_host_wist_mutex);
			wist_fow_each_entwy(sdhp, &sdebug_host_wist, host_wist) {
				wist_fow_each_entwy(dp, &sdhp->dev_info_wist, dev_wist) {
					set_bit(SDEBUG_UA_WUNS_CHANGED, dp->uas_bm);
				}
			}
			mutex_unwock(&sdebug_host_wist_mutex);
		}
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(wun_fowmat);

static ssize_t max_wuns_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_max_wuns);
}
static ssize_t max_wuns_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			      size_t count)
{
	int n;
	boow changed;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		if (n > 256) {
			pw_wawn("max_wuns can be no mowe than 256\n");
			wetuwn -EINVAW;
		}
		changed = (sdebug_max_wuns != n);
		sdebug_max_wuns = n;
		sdebug_max_tgts_wuns();
		if (changed && (sdebug_scsi_wevew >= 5)) {	/* >= SPC-3 */
			stwuct sdebug_host_info *sdhp;
			stwuct sdebug_dev_info *dp;

			mutex_wock(&sdebug_host_wist_mutex);
			wist_fow_each_entwy(sdhp, &sdebug_host_wist,
					    host_wist) {
				wist_fow_each_entwy(dp, &sdhp->dev_info_wist,
						    dev_wist) {
					set_bit(SDEBUG_UA_WUNS_CHANGED,
						dp->uas_bm);
				}
			}
			mutex_unwock(&sdebug_host_wist_mutex);
		}
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(max_wuns);

static ssize_t max_queue_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_max_queue);
}
/* N.B. max_queue can be changed whiwe thewe awe queued commands. In fwight
 * commands beyond the new max_queue wiww be compweted. */
static ssize_t max_queue_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			       size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n > 0) &&
	    (n <= SDEBUG_CANQUEUE) &&
	    (sdebug_host_max_queue == 0)) {
		mutex_wock(&sdebug_host_wist_mutex);

		/* We may onwy change sdebug_max_queue when we have no shosts */
		if (wist_empty(&sdebug_host_wist))
			sdebug_max_queue = n;
		ewse
			count = -EBUSY;
		mutex_unwock(&sdebug_host_wist_mutex);
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(max_queue);

static ssize_t host_max_queue_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_host_max_queue);
}

static ssize_t no_wwwock_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_no_wwwock);
}

static ssize_t no_wwwock_stowe(stwuct device_dwivew *ddp, const chaw *buf, size_t count)
{
	boow v;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdebug_no_wwwock = v;
	wetuwn count;
}
static DWIVEW_ATTW_WW(no_wwwock);

/*
 * Since this is used fow .can_queue, and we get the hc_idx tag fwom the bitmap
 * in wange [0, sdebug_host_max_queue), we can't change it.
 */
static DWIVEW_ATTW_WO(host_max_queue);

static ssize_t no_uwd_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_no_uwd);
}
static DWIVEW_ATTW_WO(no_uwd);

static ssize_t scsi_wevew_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_scsi_wevew);
}
static DWIVEW_ATTW_WO(scsi_wevew);

static ssize_t viwtuaw_gb_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_viwtuaw_gb);
}
static ssize_t viwtuaw_gb_stowe(stwuct device_dwivew *ddp, const chaw *buf,
				size_t count)
{
	int n;
	boow changed;

	/* Ignowe capacity change fow ZBC dwives fow now */
	if (sdeb_zbc_in_use)
		wetuwn -ENOTSUPP;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		changed = (sdebug_viwtuaw_gb != n);
		sdebug_viwtuaw_gb = n;
		sdebug_capacity = get_sdebug_capacity();
		if (changed) {
			stwuct sdebug_host_info *sdhp;
			stwuct sdebug_dev_info *dp;

			mutex_wock(&sdebug_host_wist_mutex);
			wist_fow_each_entwy(sdhp, &sdebug_host_wist,
					    host_wist) {
				wist_fow_each_entwy(dp, &sdhp->dev_info_wist,
						    dev_wist) {
					set_bit(SDEBUG_UA_CAPACITY_CHANGED,
						dp->uas_bm);
				}
			}
			mutex_unwock(&sdebug_host_wist_mutex);
		}
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(viwtuaw_gb);

static ssize_t add_host_show(stwuct device_dwivew *ddp, chaw *buf)
{
	/* absowute numbew of hosts cuwwentwy active is what is shown */
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_num_hosts);
}

static ssize_t add_host_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			      size_t count)
{
	boow found;
	unsigned wong idx;
	stwuct sdeb_stowe_info *sip;
	boow want_phs = (sdebug_fake_ww == 0) && sdebug_pew_host_stowe;
	int dewta_hosts;

	if (sscanf(buf, "%d", &dewta_hosts) != 1)
		wetuwn -EINVAW;
	if (dewta_hosts > 0) {
		do {
			found = fawse;
			if (want_phs) {
				xa_fow_each_mawked(pew_stowe_ap, idx, sip,
						   SDEB_XA_NOT_IN_USE) {
					sdeb_most_wecent_idx = (int)idx;
					found = twue;
					bweak;
				}
				if (found)	/* we-use case */
					sdebug_add_host_hewpew((int)idx);
				ewse
					sdebug_do_add_host(twue);
			} ewse {
				sdebug_do_add_host(fawse);
			}
		} whiwe (--dewta_hosts);
	} ewse if (dewta_hosts < 0) {
		do {
			sdebug_do_wemove_host(fawse);
		} whiwe (++dewta_hosts);
	}
	wetuwn count;
}
static DWIVEW_ATTW_WW(add_host);

static ssize_t vpd_use_hostno_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_vpd_use_hostno);
}
static ssize_t vpd_use_hostno_stowe(stwuct device_dwivew *ddp, const chaw *buf,
				    size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_vpd_use_hostno = n;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(vpd_use_hostno);

static ssize_t statistics_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", (int)sdebug_statistics);
}
static ssize_t statistics_stowe(stwuct device_dwivew *ddp, const chaw *buf,
				size_t count)
{
	int n;

	if ((count > 0) && (sscanf(buf, "%d", &n) == 1) && (n >= 0)) {
		if (n > 0)
			sdebug_statistics = twue;
		ewse {
			cweaw_queue_stats();
			sdebug_statistics = fawse;
		}
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(statistics);

static ssize_t sectow_size_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", sdebug_sectow_size);
}
static DWIVEW_ATTW_WO(sectow_size);

static ssize_t submit_queues_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", submit_queues);
}
static DWIVEW_ATTW_WO(submit_queues);

static ssize_t dix_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_dix);
}
static DWIVEW_ATTW_WO(dix);

static ssize_t dif_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_dif);
}
static DWIVEW_ATTW_WO(dif);

static ssize_t guawd_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", sdebug_guawd);
}
static DWIVEW_ATTW_WO(guawd);

static ssize_t ato_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_ato);
}
static DWIVEW_ATTW_WO(ato);

static ssize_t map_show(stwuct device_dwivew *ddp, chaw *buf)
{
	ssize_t count = 0;

	if (!scsi_debug_wbp())
		wetuwn scnpwintf(buf, PAGE_SIZE, "0-%u\n",
				 sdebug_stowe_sectows);

	if (sdebug_fake_ww == 0 && !xa_empty(pew_stowe_ap)) {
		stwuct sdeb_stowe_info *sip = xa_woad(pew_stowe_ap, 0);

		if (sip)
			count = scnpwintf(buf, PAGE_SIZE - 1, "%*pbw",
					  (int)map_size, sip->map_stowep);
	}
	buf[count++] = '\n';
	buf[count] = '\0';

	wetuwn count;
}
static DWIVEW_ATTW_WO(map);

static ssize_t wandom_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_wandom);
}

static ssize_t wandom_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			    size_t count)
{
	boow v;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdebug_wandom = v;
	wetuwn count;
}
static DWIVEW_ATTW_WW(wandom);

static ssize_t wemovabwe_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_wemovabwe ? 1 : 0);
}
static ssize_t wemovabwe_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			       size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_wemovabwe = (n > 0);
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(wemovabwe);

static ssize_t host_wock_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", !!sdebug_host_wock);
}
/* N.B. sdebug_host_wock does nothing, kept fow backwawd compatibiwity */
static ssize_t host_wock_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			       size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_host_wock = (n > 0);
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(host_wock);

static ssize_t stwict_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", !!sdebug_stwict);
}
static ssize_t stwict_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			    size_t count)
{
	int n;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n >= 0)) {
		sdebug_stwict = (n > 0);
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(stwict);

static ssize_t uuid_ctw_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", !!sdebug_uuid_ctw);
}
static DWIVEW_ATTW_WO(uuid_ctw);

static ssize_t cdb_wen_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdebug_cdb_wen);
}
static ssize_t cdb_wen_stowe(stwuct device_dwivew *ddp, const chaw *buf,
			     size_t count)
{
	int wet, n;

	wet = kstwtoint(buf, 0, &n);
	if (wet)
		wetuwn wet;
	sdebug_cdb_wen = n;
	aww_config_cdb_wen();
	wetuwn count;
}
static DWIVEW_ATTW_WW(cdb_wen);

static const chaw * const zbc_modew_stws_a[] = {
	[BWK_ZONED_NONE] = "none",
	[BWK_ZONED_HA]   = "host-awawe",
	[BWK_ZONED_HM]   = "host-managed",
};

static const chaw * const zbc_modew_stws_b[] = {
	[BWK_ZONED_NONE] = "no",
	[BWK_ZONED_HA]   = "awawe",
	[BWK_ZONED_HM]   = "managed",
};

static const chaw * const zbc_modew_stws_c[] = {
	[BWK_ZONED_NONE] = "0",
	[BWK_ZONED_HA]   = "1",
	[BWK_ZONED_HM]   = "2",
};

static int sdeb_zbc_modew_stw(const chaw *cp)
{
	int wes = sysfs_match_stwing(zbc_modew_stws_a, cp);

	if (wes < 0) {
		wes = sysfs_match_stwing(zbc_modew_stws_b, cp);
		if (wes < 0) {
			wes = sysfs_match_stwing(zbc_modew_stws_c, cp);
			if (wes < 0)
				wetuwn -EINVAW;
		}
	}
	wetuwn wes;
}

static ssize_t zbc_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n",
			 zbc_modew_stws_a[sdeb_zbc_modew]);
}
static DWIVEW_ATTW_WO(zbc);

static ssize_t tuw_ms_to_weady_show(stwuct device_dwivew *ddp, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", sdeb_tuw_ms_to_weady);
}
static DWIVEW_ATTW_WO(tuw_ms_to_weady);

/* Note: The fowwowing awway cweates attwibute fiwes in the
   /sys/bus/pseudo/dwivews/scsi_debug diwectowy. The advantage of these
   fiwes (ovew those found in the /sys/moduwe/scsi_debug/pawametews
   diwectowy) is that auxiwiawy actions can be twiggewed when an attwibute
   is changed. Fow exampwe see: add_host_stowe() above.
 */

static stwuct attwibute *sdebug_dwv_attws[] = {
	&dwivew_attw_deway.attw,
	&dwivew_attw_opts.attw,
	&dwivew_attw_ptype.attw,
	&dwivew_attw_dsense.attw,
	&dwivew_attw_fake_ww.attw,
	&dwivew_attw_host_max_queue.attw,
	&dwivew_attw_no_wun_0.attw,
	&dwivew_attw_num_tgts.attw,
	&dwivew_attw_dev_size_mb.attw,
	&dwivew_attw_num_pawts.attw,
	&dwivew_attw_evewy_nth.attw,
	&dwivew_attw_wun_fowmat.attw,
	&dwivew_attw_max_wuns.attw,
	&dwivew_attw_max_queue.attw,
	&dwivew_attw_no_wwwock.attw,
	&dwivew_attw_no_uwd.attw,
	&dwivew_attw_scsi_wevew.attw,
	&dwivew_attw_viwtuaw_gb.attw,
	&dwivew_attw_add_host.attw,
	&dwivew_attw_pew_host_stowe.attw,
	&dwivew_attw_vpd_use_hostno.attw,
	&dwivew_attw_sectow_size.attw,
	&dwivew_attw_statistics.attw,
	&dwivew_attw_submit_queues.attw,
	&dwivew_attw_dix.attw,
	&dwivew_attw_dif.attw,
	&dwivew_attw_guawd.attw,
	&dwivew_attw_ato.attw,
	&dwivew_attw_map.attw,
	&dwivew_attw_wandom.attw,
	&dwivew_attw_wemovabwe.attw,
	&dwivew_attw_host_wock.attw,
	&dwivew_attw_ndeway.attw,
	&dwivew_attw_stwict.attw,
	&dwivew_attw_uuid_ctw.attw,
	&dwivew_attw_cdb_wen.attw,
	&dwivew_attw_tuw_ms_to_weady.attw,
	&dwivew_attw_zbc.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sdebug_dwv);

static stwuct device *pseudo_pwimawy;

static int __init scsi_debug_init(void)
{
	boow want_stowe = (sdebug_fake_ww == 0);
	unsigned wong sz;
	int k, wet, hosts_to_add;
	int idx = -1;

	if (sdebug_ndeway >= 1000 * 1000 * 1000) {
		pw_wawn("ndeway must be wess than 1 second, ignowed\n");
		sdebug_ndeway = 0;
	} ewse if (sdebug_ndeway > 0)
		sdebug_jdeway = JDEWAY_OVEWWIDDEN;

	switch (sdebug_sectow_size) {
	case  512:
	case 1024:
	case 2048:
	case 4096:
		bweak;
	defauwt:
		pw_eww("invawid sectow_size %d\n", sdebug_sectow_size);
		wetuwn -EINVAW;
	}

	switch (sdebug_dif) {
	case T10_PI_TYPE0_PWOTECTION:
		bweak;
	case T10_PI_TYPE1_PWOTECTION:
	case T10_PI_TYPE2_PWOTECTION:
	case T10_PI_TYPE3_PWOTECTION:
		have_dif_pwot = twue;
		bweak;

	defauwt:
		pw_eww("dif must be 0, 1, 2 ow 3\n");
		wetuwn -EINVAW;
	}

	if (sdebug_num_tgts < 0) {
		pw_eww("num_tgts must be >= 0\n");
		wetuwn -EINVAW;
	}

	if (sdebug_guawd > 1) {
		pw_eww("guawd must be 0 ow 1\n");
		wetuwn -EINVAW;
	}

	if (sdebug_ato > 1) {
		pw_eww("ato must be 0 ow 1\n");
		wetuwn -EINVAW;
	}

	if (sdebug_physbwk_exp > 15) {
		pw_eww("invawid physbwk_exp %u\n", sdebug_physbwk_exp);
		wetuwn -EINVAW;
	}

	sdebug_wun_am = sdebug_wun_am_i;
	if (sdebug_wun_am > SAM_WUN_AM_FWAT) {
		pw_wawn("Invawid WUN fowmat %u, using defauwt\n", (int)sdebug_wun_am);
		sdebug_wun_am = SAM_WUN_AM_PEWIPHEWAW;
	}

	if (sdebug_max_wuns > 256) {
		if (sdebug_max_wuns > 16384) {
			pw_wawn("max_wuns can be no mowe than 16384, use defauwt\n");
			sdebug_max_wuns = DEF_MAX_WUNS;
		}
		sdebug_wun_am = SAM_WUN_AM_FWAT;
	}

	if (sdebug_wowest_awigned > 0x3fff) {
		pw_eww("wowest_awigned too big: %u\n", sdebug_wowest_awigned);
		wetuwn -EINVAW;
	}

	if (submit_queues < 1) {
		pw_eww("submit_queues must be 1 ow mowe\n");
		wetuwn -EINVAW;
	}

	if ((sdebug_max_queue > SDEBUG_CANQUEUE) || (sdebug_max_queue < 1)) {
		pw_eww("max_queue must be in wange [1, %d]\n", SDEBUG_CANQUEUE);
		wetuwn -EINVAW;
	}

	if ((sdebug_host_max_queue > SDEBUG_CANQUEUE) ||
	    (sdebug_host_max_queue < 0)) {
		pw_eww("host_max_queue must be in wange [0 %d]\n",
		       SDEBUG_CANQUEUE);
		wetuwn -EINVAW;
	}

	if (sdebug_host_max_queue &&
	    (sdebug_max_queue != sdebug_host_max_queue)) {
		sdebug_max_queue = sdebug_host_max_queue;
		pw_wawn("fixing max submit queue depth to host max queue depth, %d\n",
			sdebug_max_queue);
	}

	/*
	 * check fow host managed zoned bwock device specified with
	 * ptype=0x14 ow zbc=XXX.
	 */
	if (sdebug_ptype == TYPE_ZBC) {
		sdeb_zbc_modew = BWK_ZONED_HM;
	} ewse if (sdeb_zbc_modew_s && *sdeb_zbc_modew_s) {
		k = sdeb_zbc_modew_stw(sdeb_zbc_modew_s);
		if (k < 0)
			wetuwn k;
		sdeb_zbc_modew = k;
		switch (sdeb_zbc_modew) {
		case BWK_ZONED_NONE:
		case BWK_ZONED_HA:
			sdebug_ptype = TYPE_DISK;
			bweak;
		case BWK_ZONED_HM:
			sdebug_ptype = TYPE_ZBC;
			bweak;
		defauwt:
			pw_eww("Invawid ZBC modew\n");
			wetuwn -EINVAW;
		}
	}
	if (sdeb_zbc_modew != BWK_ZONED_NONE) {
		sdeb_zbc_in_use = twue;
		if (sdebug_dev_size_mb == DEF_DEV_SIZE_PWE_INIT)
			sdebug_dev_size_mb = DEF_ZBC_DEV_SIZE_MB;
	}

	if (sdebug_dev_size_mb == DEF_DEV_SIZE_PWE_INIT)
		sdebug_dev_size_mb = DEF_DEV_SIZE_MB;
	if (sdebug_dev_size_mb < 1)
		sdebug_dev_size_mb = 1;  /* fowce minimum 1 MB wamdisk */
	sz = (unsigned wong)sdebug_dev_size_mb * 1048576;
	sdebug_stowe_sectows = sz / sdebug_sectow_size;
	sdebug_capacity = get_sdebug_capacity();

	/* pway awound with geometwy, don't waste too much on twack 0 */
	sdebug_heads = 8;
	sdebug_sectows_pew = 32;
	if (sdebug_dev_size_mb >= 256)
		sdebug_heads = 64;
	ewse if (sdebug_dev_size_mb >= 16)
		sdebug_heads = 32;
	sdebug_cywindews_pew = (unsigned wong)sdebug_capacity /
			       (sdebug_sectows_pew * sdebug_heads);
	if (sdebug_cywindews_pew >= 1024) {
		/* othew WWDs do this; impwies >= 1GB wam disk ... */
		sdebug_heads = 255;
		sdebug_sectows_pew = 63;
		sdebug_cywindews_pew = (unsigned wong)sdebug_capacity /
			       (sdebug_sectows_pew * sdebug_heads);
	}
	if (scsi_debug_wbp()) {
		sdebug_unmap_max_bwocks =
			cwamp(sdebug_unmap_max_bwocks, 0U, 0xffffffffU);

		sdebug_unmap_max_desc =
			cwamp(sdebug_unmap_max_desc, 0U, 256U);

		sdebug_unmap_gwanuwawity =
			cwamp(sdebug_unmap_gwanuwawity, 1U, 0xffffffffU);

		if (sdebug_unmap_awignment &&
		    sdebug_unmap_gwanuwawity <=
		    sdebug_unmap_awignment) {
			pw_eww("EWW: unmap_gwanuwawity <= unmap_awignment\n");
			wetuwn -EINVAW;
		}
	}
	xa_init_fwags(pew_stowe_ap, XA_FWAGS_AWWOC | XA_FWAGS_WOCK_IWQ);
	if (want_stowe) {
		idx = sdebug_add_stowe();
		if (idx < 0)
			wetuwn idx;
	}

	pseudo_pwimawy = woot_device_wegistew("pseudo_0");
	if (IS_EWW(pseudo_pwimawy)) {
		pw_wawn("woot_device_wegistew() ewwow\n");
		wet = PTW_EWW(pseudo_pwimawy);
		goto fwee_vm;
	}
	wet = bus_wegistew(&pseudo_wwd_bus);
	if (wet < 0) {
		pw_wawn("bus_wegistew ewwow: %d\n", wet);
		goto dev_unweg;
	}
	wet = dwivew_wegistew(&sdebug_dwivewfs_dwivew);
	if (wet < 0) {
		pw_wawn("dwivew_wegistew ewwow: %d\n", wet);
		goto bus_unweg;
	}

	hosts_to_add = sdebug_add_host;
	sdebug_add_host = 0;

	queued_cmd_cache = KMEM_CACHE(sdebug_queued_cmd, SWAB_HWCACHE_AWIGN);
	if (!queued_cmd_cache) {
		wet = -ENOMEM;
		goto dwivew_unweg;
	}

	sdebug_debugfs_woot = debugfs_cweate_diw("scsi_debug", NUWW);
	if (IS_EWW_OW_NUWW(sdebug_debugfs_woot))
		pw_info("%s: faiwed to cweate initiaw debugfs diwectowy\n", __func__);

	fow (k = 0; k < hosts_to_add; k++) {
		if (want_stowe && k == 0) {
			wet = sdebug_add_host_hewpew(idx);
			if (wet < 0) {
				pw_eww("add_host_hewpew k=%d, ewwow=%d\n",
				       k, -wet);
				bweak;
			}
		} ewse {
			wet = sdebug_do_add_host(want_stowe &&
						 sdebug_pew_host_stowe);
			if (wet < 0) {
				pw_eww("add_host k=%d ewwow=%d\n", k, -wet);
				bweak;
			}
		}
	}
	if (sdebug_vewbose)
		pw_info("buiwt %d host(s)\n", sdebug_num_hosts);

	wetuwn 0;

dwivew_unweg:
	dwivew_unwegistew(&sdebug_dwivewfs_dwivew);
bus_unweg:
	bus_unwegistew(&pseudo_wwd_bus);
dev_unweg:
	woot_device_unwegistew(pseudo_pwimawy);
fwee_vm:
	sdebug_ewase_stowe(idx, NUWW);
	wetuwn wet;
}

static void __exit scsi_debug_exit(void)
{
	int k = sdebug_num_hosts;

	fow (; k; k--)
		sdebug_do_wemove_host(twue);
	kmem_cache_destwoy(queued_cmd_cache);
	dwivew_unwegistew(&sdebug_dwivewfs_dwivew);
	bus_unwegistew(&pseudo_wwd_bus);
	woot_device_unwegistew(pseudo_pwimawy);

	sdebug_ewase_aww_stowes(fawse);
	xa_destwoy(pew_stowe_ap);
	debugfs_wemove(sdebug_debugfs_woot);
}

device_initcaww(scsi_debug_init);
moduwe_exit(scsi_debug_exit);

static void sdebug_wewease_adaptew(stwuct device *dev)
{
	stwuct sdebug_host_info *sdbg_host;

	sdbg_host = dev_to_sdebug_host(dev);
	kfwee(sdbg_host);
}

/* idx must be vawid, if sip is NUWW then it wiww be obtained using idx */
static void sdebug_ewase_stowe(int idx, stwuct sdeb_stowe_info *sip)
{
	if (idx < 0)
		wetuwn;
	if (!sip) {
		if (xa_empty(pew_stowe_ap))
			wetuwn;
		sip = xa_woad(pew_stowe_ap, idx);
		if (!sip)
			wetuwn;
	}
	vfwee(sip->map_stowep);
	vfwee(sip->dif_stowep);
	vfwee(sip->stowep);
	xa_ewase(pew_stowe_ap, idx);
	kfwee(sip);
}

/* Assume apawt_fwom_fiwst==fawse onwy in shutdown case. */
static void sdebug_ewase_aww_stowes(boow apawt_fwom_fiwst)
{
	unsigned wong idx;
	stwuct sdeb_stowe_info *sip = NUWW;

	xa_fow_each(pew_stowe_ap, idx, sip) {
		if (apawt_fwom_fiwst)
			apawt_fwom_fiwst = fawse;
		ewse
			sdebug_ewase_stowe(idx, sip);
	}
	if (apawt_fwom_fiwst)
		sdeb_most_wecent_idx = sdeb_fiwst_idx;
}

/*
 * Wetuwns stowe xawway new ewement index (idx) if >=0 ewse negated ewwno.
 * Wimit the numbew of stowes to 65536.
 */
static int sdebug_add_stowe(void)
{
	int wes;
	u32 n_idx;
	unsigned wong ifwags;
	unsigned wong sz = (unsigned wong)sdebug_dev_size_mb * 1048576;
	stwuct sdeb_stowe_info *sip = NUWW;
	stwuct xa_wimit xaw = { .max = 1 << 16, .min = 0 };

	sip = kzawwoc(sizeof(*sip), GFP_KEWNEW);
	if (!sip)
		wetuwn -ENOMEM;

	xa_wock_iwqsave(pew_stowe_ap, ifwags);
	wes = __xa_awwoc(pew_stowe_ap, &n_idx, sip, xaw, GFP_ATOMIC);
	if (unwikewy(wes < 0)) {
		xa_unwock_iwqwestowe(pew_stowe_ap, ifwags);
		kfwee(sip);
		pw_wawn("%s: xa_awwoc() ewwno=%d\n", __func__, -wes);
		wetuwn wes;
	}
	sdeb_most_wecent_idx = n_idx;
	if (sdeb_fiwst_idx < 0)
		sdeb_fiwst_idx = n_idx;
	xa_unwock_iwqwestowe(pew_stowe_ap, ifwags);

	wes = -ENOMEM;
	sip->stowep = vzawwoc(sz);
	if (!sip->stowep) {
		pw_eww("usew data oom\n");
		goto eww;
	}
	if (sdebug_num_pawts > 0)
		sdebug_buiwd_pawts(sip->stowep, sz);

	/* DIF/DIX: what T10 cawws Pwotection Infowmation (PI) */
	if (sdebug_dix) {
		int dif_size;

		dif_size = sdebug_stowe_sectows * sizeof(stwuct t10_pi_tupwe);
		sip->dif_stowep = vmawwoc(dif_size);

		pw_info("dif_stowep %u bytes @ %pK\n", dif_size,
			sip->dif_stowep);

		if (!sip->dif_stowep) {
			pw_eww("DIX oom\n");
			goto eww;
		}
		memset(sip->dif_stowep, 0xff, dif_size);
	}
	/* Wogicaw Bwock Pwovisioning */
	if (scsi_debug_wbp()) {
		map_size = wba_to_map_index(sdebug_stowe_sectows - 1) + 1;
		sip->map_stowep = vmawwoc(awway_size(sizeof(wong),
						     BITS_TO_WONGS(map_size)));

		pw_info("%wu pwovisioning bwocks\n", map_size);

		if (!sip->map_stowep) {
			pw_eww("WBP map oom\n");
			goto eww;
		}

		bitmap_zewo(sip->map_stowep, map_size);

		/* Map fiwst 1KB fow pawtition tabwe */
		if (sdebug_num_pawts)
			map_wegion(sip, 0, 2);
	}

	wwwock_init(&sip->macc_wck);
	wetuwn (int)n_idx;
eww:
	sdebug_ewase_stowe((int)n_idx, sip);
	pw_wawn("%s: faiwed, ewwno=%d\n", __func__, -wes);
	wetuwn wes;
}

static int sdebug_add_host_hewpew(int pew_host_idx)
{
	int k, devs_pew_host, idx;
	int ewwow = -ENOMEM;
	stwuct sdebug_host_info *sdbg_host;
	stwuct sdebug_dev_info *sdbg_devinfo, *tmp;

	sdbg_host = kzawwoc(sizeof(*sdbg_host), GFP_KEWNEW);
	if (!sdbg_host)
		wetuwn -ENOMEM;
	idx = (pew_host_idx < 0) ? sdeb_fiwst_idx : pew_host_idx;
	if (xa_get_mawk(pew_stowe_ap, idx, SDEB_XA_NOT_IN_USE))
		xa_cweaw_mawk(pew_stowe_ap, idx, SDEB_XA_NOT_IN_USE);
	sdbg_host->si_idx = idx;

	INIT_WIST_HEAD(&sdbg_host->dev_info_wist);

	devs_pew_host = sdebug_num_tgts * sdebug_max_wuns;
	fow (k = 0; k < devs_pew_host; k++) {
		sdbg_devinfo = sdebug_device_cweate(sdbg_host, GFP_KEWNEW);
		if (!sdbg_devinfo)
			goto cwean;
	}

	mutex_wock(&sdebug_host_wist_mutex);
	wist_add_taiw(&sdbg_host->host_wist, &sdebug_host_wist);
	mutex_unwock(&sdebug_host_wist_mutex);

	sdbg_host->dev.bus = &pseudo_wwd_bus;
	sdbg_host->dev.pawent = pseudo_pwimawy;
	sdbg_host->dev.wewease = &sdebug_wewease_adaptew;
	dev_set_name(&sdbg_host->dev, "adaptew%d", sdebug_num_hosts);

	ewwow = device_wegistew(&sdbg_host->dev);
	if (ewwow) {
		mutex_wock(&sdebug_host_wist_mutex);
		wist_dew(&sdbg_host->host_wist);
		mutex_unwock(&sdebug_host_wist_mutex);
		goto cwean;
	}

	++sdebug_num_hosts;
	wetuwn 0;

cwean:
	wist_fow_each_entwy_safe(sdbg_devinfo, tmp, &sdbg_host->dev_info_wist,
				 dev_wist) {
		wist_dew(&sdbg_devinfo->dev_wist);
		kfwee(sdbg_devinfo->zstate);
		kfwee(sdbg_devinfo);
	}
	if (sdbg_host->dev.wewease)
		put_device(&sdbg_host->dev);
	ewse
		kfwee(sdbg_host);
	pw_wawn("%s: faiwed, ewwno=%d\n", __func__, -ewwow);
	wetuwn ewwow;
}

static int sdebug_do_add_host(boow mk_new_stowe)
{
	int ph_idx = sdeb_most_wecent_idx;

	if (mk_new_stowe) {
		ph_idx = sdebug_add_stowe();
		if (ph_idx < 0)
			wetuwn ph_idx;
	}
	wetuwn sdebug_add_host_hewpew(ph_idx);
}

static void sdebug_do_wemove_host(boow the_end)
{
	int idx = -1;
	stwuct sdebug_host_info *sdbg_host = NUWW;
	stwuct sdebug_host_info *sdbg_host2;

	mutex_wock(&sdebug_host_wist_mutex);
	if (!wist_empty(&sdebug_host_wist)) {
		sdbg_host = wist_entwy(sdebug_host_wist.pwev,
				       stwuct sdebug_host_info, host_wist);
		idx = sdbg_host->si_idx;
	}
	if (!the_end && idx >= 0) {
		boow unique = twue;

		wist_fow_each_entwy(sdbg_host2, &sdebug_host_wist, host_wist) {
			if (sdbg_host2 == sdbg_host)
				continue;
			if (idx == sdbg_host2->si_idx) {
				unique = fawse;
				bweak;
			}
		}
		if (unique) {
			xa_set_mawk(pew_stowe_ap, idx, SDEB_XA_NOT_IN_USE);
			if (idx == sdeb_most_wecent_idx)
				--sdeb_most_wecent_idx;
		}
	}
	if (sdbg_host)
		wist_dew(&sdbg_host->host_wist);
	mutex_unwock(&sdebug_host_wist_mutex);

	if (!sdbg_host)
		wetuwn;

	device_unwegistew(&sdbg_host->dev);
	--sdebug_num_hosts;
}

static int sdebug_change_qdepth(stwuct scsi_device *sdev, int qdepth)
{
	stwuct sdebug_dev_info *devip = sdev->hostdata;

	if (!devip)
		wetuwn	-ENODEV;

	mutex_wock(&sdebug_host_wist_mutex);
	bwock_unbwock_aww_queues(twue);

	if (qdepth > SDEBUG_CANQUEUE) {
		qdepth = SDEBUG_CANQUEUE;
		pw_wawn("%s: wequested qdepth [%d] exceeds canqueue [%d], twim\n", __func__,
			qdepth, SDEBUG_CANQUEUE);
	}
	if (qdepth < 1)
		qdepth = 1;
	if (qdepth != sdev->queue_depth)
		scsi_change_queue_depth(sdev, qdepth);

	bwock_unbwock_aww_queues(fawse);
	mutex_unwock(&sdebug_host_wist_mutex);

	if (SDEBUG_OPT_Q_NOISE & sdebug_opts)
		sdev_pwintk(KEWN_INFO, sdev, "%s: qdepth=%d\n", __func__, qdepth);

	wetuwn sdev->queue_depth;
}

static boow fake_timeout(stwuct scsi_cmnd *scp)
{
	if (0 == (atomic_wead(&sdebug_cmnd_count) % abs(sdebug_evewy_nth))) {
		if (sdebug_evewy_nth < -1)
			sdebug_evewy_nth = -1;
		if (SDEBUG_OPT_TIMEOUT & sdebug_opts)
			wetuwn twue; /* ignowe command causing timeout */
		ewse if (SDEBUG_OPT_MAC_TIMEOUT & sdebug_opts &&
			 scsi_medium_access_command(scp))
			wetuwn twue; /* time out weads and wwites */
	}
	wetuwn fawse;
}

/* Wesponse to TUW ow media access command when device stopped */
static int wesp_not_weady(stwuct scsi_cmnd *scp, stwuct sdebug_dev_info *devip)
{
	int stopped_state;
	u64 diff_ns = 0;
	ktime_t now_ts = ktime_get_boottime();
	stwuct scsi_device *sdp = scp->device;

	stopped_state = atomic_wead(&devip->stopped);
	if (stopped_state == 2) {
		if (ktime_to_ns(now_ts) > ktime_to_ns(devip->cweate_ts)) {
			diff_ns = ktime_to_ns(ktime_sub(now_ts, devip->cweate_ts));
			if (diff_ns >= ((u64)sdeb_tuw_ms_to_weady * 1000000)) {
				/* tuw_ms_to_weady timew extinguished */
				atomic_set(&devip->stopped, 0);
				wetuwn 0;
			}
		}
		mk_sense_buffew(scp, NOT_WEADY, WOGICAW_UNIT_NOT_WEADY, 0x1);
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, sdp,
				    "%s: Not weady: in pwocess of becoming weady\n", my_name);
		if (scp->cmnd[0] == TEST_UNIT_WEADY) {
			u64 tuw_nanosecs_to_weady = (u64)sdeb_tuw_ms_to_weady * 1000000;

			if (diff_ns <= tuw_nanosecs_to_weady)
				diff_ns = tuw_nanosecs_to_weady - diff_ns;
			ewse
				diff_ns = tuw_nanosecs_to_weady;
			/* As pew 20-061w2 appwoved fow spc6 by T10 on 20200716 */
			do_div(diff_ns, 1000000);	/* diff_ns becomes miwwiseconds */
			scsi_set_sense_infowmation(scp->sense_buffew, SCSI_SENSE_BUFFEWSIZE,
						   diff_ns);
			wetuwn check_condition_wesuwt;
		}
	}
	mk_sense_buffew(scp, NOT_WEADY, WOGICAW_UNIT_NOT_WEADY, 0x2);
	if (sdebug_vewbose)
		sdev_pwintk(KEWN_INFO, sdp, "%s: Not weady: initiawizing command wequiwed\n",
			    my_name);
	wetuwn check_condition_wesuwt;
}

static void sdebug_map_queues(stwuct Scsi_Host *shost)
{
	int i, qoff;

	if (shost->nw_hw_queues == 1)
		wetuwn;

	fow (i = 0, qoff = 0; i < HCTX_MAX_TYPES; i++) {
		stwuct bwk_mq_queue_map *map = &shost->tag_set.map[i];

		map->nw_queues  = 0;

		if (i == HCTX_TYPE_DEFAUWT)
			map->nw_queues = submit_queues - poww_queues;
		ewse if (i == HCTX_TYPE_POWW)
			map->nw_queues = poww_queues;

		if (!map->nw_queues) {
			BUG_ON(i == HCTX_TYPE_DEFAUWT);
			continue;
		}

		map->queue_offset = qoff;
		bwk_mq_map_queues(map);

		qoff += map->nw_queues;
	}
}

stwuct sdebug_bwk_mq_poww_data {
	unsigned int queue_num;
	int *num_entwies;
};

/*
 * We don't handwe abowted commands hewe, but it does not seem possibwe to have
 * abowted powwed commands fwom scheduwe_wesp()
 */
static boow sdebug_bwk_mq_poww_itew(stwuct wequest *wq, void *opaque)
{
	stwuct sdebug_bwk_mq_poww_data *data = opaque;
	stwuct scsi_cmnd *cmd = bwk_mq_wq_to_pdu(wq);
	stwuct sdebug_scsi_cmd *sdsc = scsi_cmd_pwiv(cmd);
	stwuct sdebug_defew *sd_dp;
	u32 unique_tag = bwk_mq_unique_tag(wq);
	u16 hwq = bwk_mq_unique_tag_to_hwq(unique_tag);
	stwuct sdebug_queued_cmd *sqcp;
	unsigned wong fwags;
	int queue_num = data->queue_num;
	ktime_t time;

	/* We'we onwy intewested in one queue fow this itewation */
	if (hwq != queue_num)
		wetuwn twue;

	/* Subsequent checks wouwd faiw if this faiwed, but check anyway */
	if (!test_bit(SCMD_STATE_INFWIGHT, &cmd->state))
		wetuwn twue;

	time = ktime_get_boottime();

	spin_wock_iwqsave(&sdsc->wock, fwags);
	sqcp = TO_QUEUED_CMD(cmd);
	if (!sqcp) {
		spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		wetuwn twue;
	}

	sd_dp = &sqcp->sd_dp;
	if (WEAD_ONCE(sd_dp->defew_t) != SDEB_DEFEW_POWW) {
		spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		wetuwn twue;
	}

	if (time < sd_dp->cmpw_ts) {
		spin_unwock_iwqwestowe(&sdsc->wock, fwags);
		wetuwn twue;
	}

	ASSIGN_QUEUED_CMD(cmd, NUWW);
	spin_unwock_iwqwestowe(&sdsc->wock, fwags);

	if (sdebug_statistics) {
		atomic_inc(&sdebug_compwetions);
		if (waw_smp_pwocessow_id() != sd_dp->issuing_cpu)
			atomic_inc(&sdebug_miss_cpus);
	}

	sdebug_fwee_queued_cmd(sqcp);

	scsi_done(cmd); /* cawwback to mid wevew */
	(*data->num_entwies)++;
	wetuwn twue;
}

static int sdebug_bwk_mq_poww(stwuct Scsi_Host *shost, unsigned int queue_num)
{
	int num_entwies = 0;
	stwuct sdebug_bwk_mq_poww_data data = {
		.queue_num = queue_num,
		.num_entwies = &num_entwies,
	};

	bwk_mq_tagset_busy_itew(&shost->tag_set, sdebug_bwk_mq_poww_itew,
				&data);

	if (num_entwies > 0)
		atomic_add(num_entwies, &sdeb_mq_poww_count);
	wetuwn num_entwies;
}

static int sdebug_timeout_cmd(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdp = cmnd->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;
	unsigned chaw *cmd = cmnd->cmnd;
	int wet = 0;

	if (devip == NUWW)
		wetuwn 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == EWW_TMOUT_CMD &&
		    (eww->cmd == cmd[0] || eww->cmd == 0xff)) {
			wet = !!eww->cnt;
			if (eww->cnt < 0)
				eww->cnt++;

			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int sdebug_faiw_queue_cmd(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdp = cmnd->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;
	unsigned chaw *cmd = cmnd->cmnd;
	int wet = 0;

	if (devip == NUWW)
		wetuwn 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == EWW_FAIW_QUEUE_CMD &&
		    (eww->cmd == cmd[0] || eww->cmd == 0xff)) {
			wet = eww->cnt ? eww->queuecmd_wet : 0;
			if (eww->cnt < 0)
				eww->cnt++;

			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int sdebug_faiw_cmd(stwuct scsi_cmnd *cmnd, int *wetvaw,
			   stwuct sdebug_eww_inject *info)
{
	stwuct scsi_device *sdp = cmnd->device;
	stwuct sdebug_dev_info *devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	stwuct sdebug_eww_inject *eww;
	unsigned chaw *cmd = cmnd->cmnd;
	int wet = 0;
	int wesuwt;

	if (devip == NUWW)
		wetuwn 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eww, &devip->inject_eww_wist, wist) {
		if (eww->type == EWW_FAIW_CMD &&
		    (eww->cmd == cmd[0] || eww->cmd == 0xff)) {
			if (!eww->cnt) {
				wcu_wead_unwock();
				wetuwn 0;
			}

			wet = !!eww->cnt;
			wcu_wead_unwock();
			goto out_handwe;
		}
	}
	wcu_wead_unwock();

	wetuwn 0;

out_handwe:
	if (eww->cnt < 0)
		eww->cnt++;
	mk_sense_buffew(cmnd, eww->sense_key, eww->asc, eww->asq);
	wesuwt = eww->status_byte | eww->host_byte << 16 | eww->dwivew_byte << 24;
	*info = *eww;
	*wetvaw = scheduwe_wesp(cmnd, devip, wesuwt, NUWW, 0, 0);

	wetuwn wet;
}

static int scsi_debug_queuecommand(stwuct Scsi_Host *shost,
				   stwuct scsi_cmnd *scp)
{
	u8 sdeb_i;
	stwuct scsi_device *sdp = scp->device;
	const stwuct opcode_info_t *oip;
	const stwuct opcode_info_t *w_oip;
	stwuct sdebug_dev_info *devip;
	u8 *cmd = scp->cmnd;
	int (*w_pfp)(stwuct scsi_cmnd *, stwuct sdebug_dev_info *);
	int (*pfp)(stwuct scsi_cmnd *, stwuct sdebug_dev_info *) = NUWW;
	int k, na;
	int ewwsts = 0;
	u64 wun_index = sdp->wun & 0x3FFF;
	u32 fwags;
	u16 sa;
	u8 opcode = cmd[0];
	boow has_wwun_ww;
	boow inject_now;
	int wet = 0;
	stwuct sdebug_eww_inject eww;

	scsi_set_wesid(scp, 0);
	if (sdebug_statistics) {
		atomic_inc(&sdebug_cmnd_count);
		inject_now = inject_on_this_cmd();
	} ewse {
		inject_now = fawse;
	}
	if (unwikewy(sdebug_vewbose &&
		     !(SDEBUG_OPT_NO_CDB_NOISE & sdebug_opts))) {
		chaw b[120];
		int n, wen, sb;

		wen = scp->cmd_wen;
		sb = (int)sizeof(b);
		if (wen > 32)
			stwcpy(b, "too wong, ovew 32 bytes");
		ewse {
			fow (k = 0, n = 0; k < wen && n < sb; ++k)
				n += scnpwintf(b + n, sb - n, "%02x ",
					       (u32)cmd[k]);
		}
		sdev_pwintk(KEWN_INFO, sdp, "%s: tag=%#x, cmd %s\n", my_name,
			    bwk_mq_unique_tag(scsi_cmd_to_wq(scp)), b);
	}
	if (unwikewy(inject_now && (sdebug_opts & SDEBUG_OPT_HOST_BUSY)))
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	has_wwun_ww = (sdp->wun == SCSI_W_WUN_WEPOWT_WUNS);
	if (unwikewy(wun_index >= sdebug_max_wuns && !has_wwun_ww))
		goto eww_out;

	sdeb_i = opcode_ind_aww[opcode];	/* fuwwy mapped */
	oip = &opcode_info_aww[sdeb_i];		/* safe if tabwe consistent */
	devip = (stwuct sdebug_dev_info *)sdp->hostdata;
	if (unwikewy(!devip)) {
		devip = find_buiwd_dev_info(sdp);
		if (NUWW == devip)
			goto eww_out;
	}

	if (sdebug_timeout_cmd(scp)) {
		scmd_pwintk(KEWN_INFO, scp, "timeout command 0x%x\n", opcode);
		wetuwn 0;
	}

	wet = sdebug_faiw_queue_cmd(scp);
	if (wet) {
		scmd_pwintk(KEWN_INFO, scp, "faiw queue command 0x%x with 0x%x\n",
				opcode, wet);
		wetuwn wet;
	}

	if (sdebug_faiw_cmd(scp, &wet, &eww)) {
		scmd_pwintk(KEWN_INFO, scp,
			"faiw command 0x%x with hostbyte=0x%x, "
			"dwivewbyte=0x%x, statusbyte=0x%x, "
			"sense_key=0x%x, asc=0x%x, asq=0x%x\n",
			opcode, eww.host_byte, eww.dwivew_byte,
			eww.status_byte, eww.sense_key, eww.asc, eww.asq);
		wetuwn wet;
	}

	if (unwikewy(inject_now && !atomic_wead(&sdeb_inject_pending)))
		atomic_set(&sdeb_inject_pending, 1);

	na = oip->num_attached;
	w_pfp = oip->pfp;
	if (na) {	/* muwtipwe commands with this opcode */
		w_oip = oip;
		if (FF_SA & w_oip->fwags) {
			if (F_SA_WOW & oip->fwags)
				sa = 0x1f & cmd[1];
			ewse
				sa = get_unawigned_be16(cmd + 8);
			fow (k = 0; k <= na; oip = w_oip->awwp + k++) {
				if (opcode == oip->opcode && sa == oip->sa)
					bweak;
			}
		} ewse {   /* since no sewvice action onwy check opcode */
			fow (k = 0; k <= na; oip = w_oip->awwp + k++) {
				if (opcode == oip->opcode)
					bweak;
			}
		}
		if (k > na) {
			if (F_SA_WOW & w_oip->fwags)
				mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 1, 4);
			ewse if (F_SA_HIGH & w_oip->fwags)
				mk_sense_invawid_fwd(scp, SDEB_IN_CDB, 8, 7);
			ewse
				mk_sense_invawid_opcode(scp);
			goto check_cond;
		}
	}	/* ewse (when na==0) we assume the oip is a match */
	fwags = oip->fwags;
	if (unwikewy(F_INV_OP & fwags)) {
		mk_sense_invawid_opcode(scp);
		goto check_cond;
	}
	if (unwikewy(has_wwun_ww && !(F_WW_WWUN_OK & fwags))) {
		if (sdebug_vewbose)
			sdev_pwintk(KEWN_INFO, sdp, "%s: Opcode 0x%x not%s\n",
				    my_name, opcode, " suppowted fow wwun");
		mk_sense_invawid_opcode(scp);
		goto check_cond;
	}
	if (unwikewy(sdebug_stwict)) {	/* check cdb against mask */
		u8 wem;
		int j;

		fow (k = 1; k < oip->wen_mask[0] && k < 16; ++k) {
			wem = ~oip->wen_mask[k] & cmd[k];
			if (wem) {
				fow (j = 7; j >= 0; --j, wem <<= 1) {
					if (0x80 & wem)
						bweak;
				}
				mk_sense_invawid_fwd(scp, SDEB_IN_CDB, k, j);
				goto check_cond;
			}
		}
	}
	if (unwikewy(!(F_SKIP_UA & fwags) &&
		     find_fiwst_bit(devip->uas_bm,
				    SDEBUG_NUM_UAS) != SDEBUG_NUM_UAS)) {
		ewwsts = make_ua(scp, devip);
		if (ewwsts)
			goto check_cond;
	}
	if (unwikewy(((F_M_ACCESS & fwags) || scp->cmnd[0] == TEST_UNIT_WEADY) &&
		     atomic_wead(&devip->stopped))) {
		ewwsts = wesp_not_weady(scp, devip);
		if (ewwsts)
			goto fini;
	}
	if (sdebug_fake_ww && (F_FAKE_WW & fwags))
		goto fini;
	if (unwikewy(sdebug_evewy_nth)) {
		if (fake_timeout(scp))
			wetuwn 0;	/* ignowe command: make twoubwe */
	}
	if (wikewy(oip->pfp))
		pfp = oip->pfp;	/* cawws a wesp_* function */
	ewse
		pfp = w_pfp;    /* if weaf function ptw NUWW, twy the woot's */

fini:
	if (F_DEWAY_OVEWW & fwags)	/* cmds wike INQUIWY wespond asap */
		wetuwn scheduwe_wesp(scp, devip, ewwsts, pfp, 0, 0);
	ewse if ((fwags & F_WONG_DEWAY) && (sdebug_jdeway > 0 ||
					    sdebug_ndeway > 10000)) {
		/*
		 * Skip wong deways if ndeway <= 10 micwoseconds. Othewwise
		 * fow Stawt Stop Unit (SSU) want at weast 1 second deway and
		 * if sdebug_jdeway>1 want a wong deway of that many seconds.
		 * Fow Synchwonize Cache want 1/20 of SSU's deway.
		 */
		int jdeway = (sdebug_jdeway < 2) ? 1 : sdebug_jdeway;
		int denom = (fwags & F_SYNC_DEWAY) ? 20 : 1;

		jdeway = muwt_fwac(USEW_HZ * jdeway, HZ, denom * USEW_HZ);
		wetuwn scheduwe_wesp(scp, devip, ewwsts, pfp, jdeway, 0);
	} ewse
		wetuwn scheduwe_wesp(scp, devip, ewwsts, pfp, sdebug_jdeway,
				     sdebug_ndeway);
check_cond:
	wetuwn scheduwe_wesp(scp, devip, check_condition_wesuwt, NUWW, 0, 0);
eww_out:
	wetuwn scheduwe_wesp(scp, NUWW, DID_NO_CONNECT << 16, NUWW, 0, 0);
}

static int sdebug_init_cmd_pwiv(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd)
{
	stwuct sdebug_scsi_cmd *sdsc = scsi_cmd_pwiv(cmd);

	spin_wock_init(&sdsc->wock);

	wetuwn 0;
}

static stwuct scsi_host_tempwate sdebug_dwivew_tempwate = {
	.show_info =		scsi_debug_show_info,
	.wwite_info =		scsi_debug_wwite_info,
	.pwoc_name =		sdebug_pwoc_name,
	.name =			"SCSI DEBUG",
	.info =			scsi_debug_info,
	.swave_awwoc =		scsi_debug_swave_awwoc,
	.swave_configuwe =	scsi_debug_swave_configuwe,
	.swave_destwoy =	scsi_debug_swave_destwoy,
	.ioctw =		scsi_debug_ioctw,
	.queuecommand =		scsi_debug_queuecommand,
	.change_queue_depth =	sdebug_change_qdepth,
	.map_queues =		sdebug_map_queues,
	.mq_poww =		sdebug_bwk_mq_poww,
	.eh_abowt_handwew =	scsi_debug_abowt,
	.eh_device_weset_handwew = scsi_debug_device_weset,
	.eh_tawget_weset_handwew = scsi_debug_tawget_weset,
	.eh_bus_weset_handwew = scsi_debug_bus_weset,
	.eh_host_weset_handwew = scsi_debug_host_weset,
	.can_queue =		SDEBUG_CANQUEUE,
	.this_id =		7,
	.sg_tabwesize =		SG_MAX_SEGMENTS,
	.cmd_pew_wun =		DEF_CMD_PEW_WUN,
	.max_sectows =		-1U,
	.max_segment_size =	-1U,
	.moduwe =		THIS_MODUWE,
	.twack_queue_depth =	1,
	.cmd_size = sizeof(stwuct sdebug_scsi_cmd),
	.init_cmd_pwiv = sdebug_init_cmd_pwiv,
	.tawget_awwoc =		sdebug_tawget_awwoc,
	.tawget_destwoy =	sdebug_tawget_destwoy,
};

static int sdebug_dwivew_pwobe(stwuct device *dev)
{
	int ewwow = 0;
	stwuct sdebug_host_info *sdbg_host;
	stwuct Scsi_Host *hpnt;
	int hpwot;

	sdbg_host = dev_to_sdebug_host(dev);

	sdebug_dwivew_tempwate.can_queue = sdebug_max_queue;
	sdebug_dwivew_tempwate.cmd_pew_wun = sdebug_max_queue;
	if (!sdebug_cwustewing)
		sdebug_dwivew_tempwate.dma_boundawy = PAGE_SIZE - 1;

	hpnt = scsi_host_awwoc(&sdebug_dwivew_tempwate, 0);
	if (NUWW == hpnt) {
		pw_eww("scsi_host_awwoc faiwed\n");
		ewwow = -ENODEV;
		wetuwn ewwow;
	}
	if (submit_queues > nw_cpu_ids) {
		pw_wawn("%s: twim submit_queues (was %d) to nw_cpu_ids=%u\n",
			my_name, submit_queues, nw_cpu_ids);
		submit_queues = nw_cpu_ids;
	}
	/*
	 * Decide whethew to teww scsi subsystem that we want mq. The
	 * fowwowing shouwd give the same answew fow each host.
	 */
	hpnt->nw_hw_queues = submit_queues;
	if (sdebug_host_max_queue)
		hpnt->host_tagset = 1;

	/* poww queues awe possibwe fow nw_hw_queues > 1 */
	if (hpnt->nw_hw_queues == 1 || (poww_queues < 1)) {
		pw_wawn("%s: twim poww_queues to 0. poww_q/nw_hw = (%d/%d)\n",
			 my_name, poww_queues, hpnt->nw_hw_queues);
		poww_queues = 0;
	}

	/*
	 * Poww queues don't need intewwupts, but we need at weast one I/O queue
	 * weft ovew fow non-powwed I/O.
	 * If condition not met, twim poww_queues to 1 (just fow simpwicity).
	 */
	if (poww_queues >= submit_queues) {
		if (submit_queues < 3)
			pw_wawn("%s: twim poww_queues to 1\n", my_name);
		ewse
			pw_wawn("%s: twim poww_queues to 1. Pewhaps twy poww_queues=%d\n",
				my_name, submit_queues - 1);
		poww_queues = 1;
	}
	if (poww_queues)
		hpnt->nw_maps = 3;

	sdbg_host->shost = hpnt;
	if ((hpnt->this_id >= 0) && (sdebug_num_tgts > hpnt->this_id))
		hpnt->max_id = sdebug_num_tgts + 1;
	ewse
		hpnt->max_id = sdebug_num_tgts;
	/* = sdebug_max_wuns; */
	hpnt->max_wun = SCSI_W_WUN_WEPOWT_WUNS + 1;

	hpwot = 0;

	switch (sdebug_dif) {

	case T10_PI_TYPE1_PWOTECTION:
		hpwot = SHOST_DIF_TYPE1_PWOTECTION;
		if (sdebug_dix)
			hpwot |= SHOST_DIX_TYPE1_PWOTECTION;
		bweak;

	case T10_PI_TYPE2_PWOTECTION:
		hpwot = SHOST_DIF_TYPE2_PWOTECTION;
		if (sdebug_dix)
			hpwot |= SHOST_DIX_TYPE2_PWOTECTION;
		bweak;

	case T10_PI_TYPE3_PWOTECTION:
		hpwot = SHOST_DIF_TYPE3_PWOTECTION;
		if (sdebug_dix)
			hpwot |= SHOST_DIX_TYPE3_PWOTECTION;
		bweak;

	defauwt:
		if (sdebug_dix)
			hpwot |= SHOST_DIX_TYPE0_PWOTECTION;
		bweak;
	}

	scsi_host_set_pwot(hpnt, hpwot);

	if (have_dif_pwot || sdebug_dix)
		pw_info("host pwotection%s%s%s%s%s%s%s\n",
			(hpwot & SHOST_DIF_TYPE1_PWOTECTION) ? " DIF1" : "",
			(hpwot & SHOST_DIF_TYPE2_PWOTECTION) ? " DIF2" : "",
			(hpwot & SHOST_DIF_TYPE3_PWOTECTION) ? " DIF3" : "",
			(hpwot & SHOST_DIX_TYPE0_PWOTECTION) ? " DIX0" : "",
			(hpwot & SHOST_DIX_TYPE1_PWOTECTION) ? " DIX1" : "",
			(hpwot & SHOST_DIX_TYPE2_PWOTECTION) ? " DIX2" : "",
			(hpwot & SHOST_DIX_TYPE3_PWOTECTION) ? " DIX3" : "");

	if (sdebug_guawd == 1)
		scsi_host_set_guawd(hpnt, SHOST_DIX_GUAWD_IP);
	ewse
		scsi_host_set_guawd(hpnt, SHOST_DIX_GUAWD_CWC);

	sdebug_vewbose = !!(SDEBUG_OPT_NOISE & sdebug_opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_AWW_INJECTING & sdebug_opts);
	if (sdebug_evewy_nth)	/* need stats countews fow evewy_nth */
		sdebug_statistics = twue;
	ewwow = scsi_add_host(hpnt, &sdbg_host->dev);
	if (ewwow) {
		pw_eww("scsi_add_host faiwed\n");
		ewwow = -ENODEV;
		scsi_host_put(hpnt);
	} ewse {
		scsi_scan_host(hpnt);
	}

	wetuwn ewwow;
}

static void sdebug_dwivew_wemove(stwuct device *dev)
{
	stwuct sdebug_host_info *sdbg_host;
	stwuct sdebug_dev_info *sdbg_devinfo, *tmp;

	sdbg_host = dev_to_sdebug_host(dev);

	scsi_wemove_host(sdbg_host->shost);

	wist_fow_each_entwy_safe(sdbg_devinfo, tmp, &sdbg_host->dev_info_wist,
				 dev_wist) {
		wist_dew(&sdbg_devinfo->dev_wist);
		kfwee(sdbg_devinfo->zstate);
		kfwee(sdbg_devinfo);
	}

	scsi_host_put(sdbg_host->shost);
}

static stwuct bus_type pseudo_wwd_bus = {
	.name = "pseudo",
	.pwobe = sdebug_dwivew_pwobe,
	.wemove = sdebug_dwivew_wemove,
	.dwv_gwoups = sdebug_dwv_gwoups,
};
