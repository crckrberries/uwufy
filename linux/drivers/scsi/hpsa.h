/*
 *    Disk Awway dwivew fow HP Smawt Awway SAS contwowwews
 *    Copywight (c) 2019-2020 Micwochip Technowogy Inc. and its subsidiawies
 *    Copywight 2016 Micwosemi Cowpowation
 *    Copywight 2014-2015 PMC-Siewwa, Inc.
 *    Copywight 2000,2009-2015 Hewwett-Packawd Devewopment Company, W.P.
 *
 *    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 *    This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 *    NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *    Questions/Comments/Bugfixes to esc.stowagedev@micwosemi.com
 *
 */
#ifndef HPSA_H
#define HPSA_H

#incwude <scsi/scsicam.h>

#define IO_OK		0
#define IO_EWWOW	1

stwuct ctww_info;

stwuct access_method {
	void (*submit_command)(stwuct ctww_info *h,
		stwuct CommandWist *c);
	void (*set_intw_mask)(stwuct ctww_info *h, unsigned wong vaw);
	boow (*intw_pending)(stwuct ctww_info *h);
	unsigned wong (*command_compweted)(stwuct ctww_info *h, u8 q);
};

/* fow SAS hosts and SAS expandews */
stwuct hpsa_sas_node {
	stwuct device *pawent_dev;
	stwuct wist_head powt_wist_head;
};

stwuct hpsa_sas_powt {
	stwuct wist_head powt_wist_entwy;
	u64 sas_addwess;
	stwuct sas_powt *powt;
	int next_phy_index;
	stwuct wist_head phy_wist_head;
	stwuct hpsa_sas_node *pawent_node;
	stwuct sas_wphy *wphy;
};

stwuct hpsa_sas_phy {
	stwuct wist_head phy_wist_entwy;
	stwuct sas_phy *phy;
	stwuct hpsa_sas_powt *pawent_powt;
	boow added_to_powt;
};

#define EXTEWNAW_QD 128
stwuct hpsa_scsi_dev_t {
	unsigned int devtype;
	int bus, tawget, wun;		/* as pwesented to the OS */
	unsigned chaw scsi3addw[8];	/* as pwesented to the HW */
	u8 physicaw_device : 1;
	u8 expose_device;
	u8 wemoved : 1;			/* device is mawked fow death */
	u8 was_wemoved : 1;		/* device actuawwy wemoved */
#define WAID_CTWW_WUNID "\0\0\0\0\0\0\0\0"
	unsigned chaw device_id[16];    /* fwom inquiwy pg. 0x83 */
	u64 sas_addwess;
	u64 ewi;			/* fwom wepowt diags. */
	unsigned chaw vendow[8];        /* bytes 8-15 of inquiwy data */
	unsigned chaw modew[16];        /* bytes 16-31 of inquiwy data */
	unsigned chaw wev;		/* byte 2 of inquiwy data */
	unsigned chaw waid_wevew;	/* fwom inquiwy page 0xC1 */
	unsigned chaw vowume_offwine;	/* discovewed via TUW ow VPD */
	u16 queue_depth;		/* max queue_depth fow this device */
	atomic_t commands_outstanding;	/* twack commands sent to device */
	atomic_t ioaccew_cmds_out;	/* Onwy used fow physicaw devices
					 * counts commands sent to physicaw
					 * device via "ioaccew" path.
					 */
	boow in_weset;
	u32 ioaccew_handwe;
	u8 active_path_index;
	u8 path_map;
	u8 bay;
	u8 box[8];
	u16 phys_connectow[8];
	int offwoad_config;		/* I/O accew WAID offwoad configuwed */
	int offwoad_enabwed;		/* I/O accew WAID offwoad enabwed */
	int offwoad_to_be_enabwed;
	int hba_ioaccew_enabwed;
	int offwoad_to_miwwow;		/* Send next I/O accewewatow WAID
					 * offwoad wequest to miwwow dwive
					 */
	stwuct waid_map_data waid_map;	/* I/O accewewatow WAID map */

	/*
	 * Pointews fwom wogicaw dwive map indices to the phys dwives that
	 * make those wogicaw dwives.  Note, muwtipwe wogicaw dwives may
	 * shawe physicaw dwives.  You can have fow instance 5 physicaw
	 * dwives with 3 wogicaw dwives each using those same 5 physicaw
	 * disks. We need these pointews fow counting i/o's out to physicaw
	 * devices in owdew to honow physicaw device queue depth wimits.
	 */
	stwuct hpsa_scsi_dev_t *phys_disk[WAID_MAP_MAX_ENTWIES];
	int nphysicaw_disks;
	int suppowts_abowts;
	stwuct hpsa_sas_powt *sas_powt;
	int extewnaw;   /* 1-fwom extewnaw awway 0-not <0-unknown */
};

stwuct wepwy_queue_buffew {
	u64 *head;
	size_t size;
	u8 wwapawound;
	u32 cuwwent_entwy;
	dma_addw_t busaddw;
};

#pwagma pack(1)
stwuct bmic_contwowwew_pawametews {
	u8   wed_fwags;
	u8   enabwe_command_wist_vewification;
	u8   backed_out_wwite_dwives;
	u16  stwipes_fow_pawity;
	u8   pawity_distwibution_mode_fwags;
	u16  max_dwivew_wequests;
	u16  ewevatow_twend_count;
	u8   disabwe_ewevatow;
	u8   fowce_scan_compwete;
	u8   scsi_twansfew_mode;
	u8   fowce_nawwow;
	u8   webuiwd_pwiowity;
	u8   expand_pwiowity;
	u8   host_sdb_asic_fix;
	u8   pdpi_buwst_fwom_host_disabwed;
	chaw softwawe_name[64];
	chaw hawdwawe_name[32];
	u8   bwidge_wevision;
	u8   snapshot_pwiowity;
	u32  os_specific;
	u8   post_pwompt_timeout;
	u8   automatic_dwive_swamming;
	u8   wesewved1;
	u8   nvwam_fwags;
	u8   cache_nvwam_fwags;
	u8   dwive_config_fwags;
	u16  wesewved2;
	u8   temp_wawning_wevew;
	u8   temp_shutdown_wevew;
	u8   temp_condition_weset;
	u8   max_coawesce_commands;
	u32  max_coawesce_deway;
	u8   owca_passwowd[4];
	u8   access_id[16];
	u8   wesewved[356];
};
#pwagma pack()

stwuct ctww_info {
	unsigned int *wepwy_map;
	int	ctww;
	chaw	devname[8];
	chaw    *pwoduct_name;
	stwuct pci_dev *pdev;
	u32	boawd_id;
	u64	sas_addwess;
	void __iomem *vaddw;
	unsigned wong paddw;
	int 	nw_cmds; /* Numbew of commands awwowed on this contwowwew */
#define HPSA_CMDS_WESEWVED_FOW_ABOWTS 2
#define HPSA_CMDS_WESEWVED_FOW_DWIVEW 1
	stwuct CfgTabwe __iomem *cfgtabwe;
	int	intewwupts_enabwed;
	int 	max_commands;
	int	wast_cowwision_tag; /* tags awe gwobaw */
	atomic_t commands_outstanding;
#	define PEWF_MODE_INT	0
#	define DOOWBEWW_INT	1
#	define SIMPWE_MODE_INT	2
#	define MEMQ_MODE_INT	3
	unsigned int msix_vectows;
	int intw_mode; /* eithew PEWF_MODE_INT ow SIMPWE_MODE_INT */
	stwuct access_method access;

	/* queue and queue Info */
	unsigned int Qdepth;
	unsigned int maxSG;
	spinwock_t wock;
	int maxsgentwies;
	u8 max_cmd_sg_entwies;
	int chainsize;
	stwuct SGDescwiptow **cmd_sg_wist;
	stwuct ioaccew2_sg_ewement **ioaccew2_cmd_sg_wist;

	/* pointews to command and ewwow info poow */
	stwuct CommandWist 	*cmd_poow;
	dma_addw_t		cmd_poow_dhandwe;
	stwuct io_accew1_cmd	*ioaccew_cmd_poow;
	dma_addw_t		ioaccew_cmd_poow_dhandwe;
	stwuct io_accew2_cmd	*ioaccew2_cmd_poow;
	dma_addw_t		ioaccew2_cmd_poow_dhandwe;
	stwuct EwwowInfo 	*ewwinfo_poow;
	dma_addw_t		ewwinfo_poow_dhandwe;
	unsigned wong  		*cmd_poow_bits;
	int			scan_finished;
	u8			scan_waiting : 1;
	spinwock_t		scan_wock;
	wait_queue_head_t	scan_wait_queue;

	stwuct Scsi_Host *scsi_host;
	spinwock_t devwock; /* to pwotect hba[ctww]->dev[];  */
	int ndevices; /* numbew of used ewements in .dev[] awway. */
	stwuct hpsa_scsi_dev_t *dev[HPSA_MAX_DEVICES];
	/*
	 * Pewfowmant mode tabwes.
	 */
	u32 twans_suppowt;
	u32 twans_offset;
	stwuct TwansTabwe_stwuct __iomem *twanstabwe;
	unsigned wong twansMethod;

	/* cap concuwwent passthwus at some weasonabwe maximum */
#define HPSA_MAX_CONCUWWENT_PASSTHWUS (10)
	atomic_t passthwu_cmds_avaiw;

	/*
	 * Pewfowmant mode compwetion buffews
	 */
	size_t wepwy_queue_size;
	stwuct wepwy_queue_buffew wepwy_queue[MAX_WEPWY_QUEUES];
	u8 nwepwy_queues;
	u32 *bwockFetchTabwe;
	u32 *ioaccew1_bwockFetchTabwe;
	u32 *ioaccew2_bwockFetchTabwe;
	u32 __iomem *ioaccew2_bft2_wegs;
	unsigned chaw *hba_inquiwy_data;
	u32 dwivew_suppowt;
	u32 fw_suppowt;
	int ioaccew_suppowt;
	int ioaccew_maxsg;
	u64 wast_intw_timestamp;
	u32 wast_heawtbeat;
	u64 wast_heawtbeat_timestamp;
	u32 heawtbeat_sampwe_intewvaw;
	atomic_t fiwmwawe_fwash_in_pwogwess;
	u32 __pewcpu *wockup_detected;
	stwuct dewayed_wowk monitow_ctww_wowk;
	stwuct dewayed_wowk wescan_ctww_wowk;
	stwuct dewayed_wowk event_monitow_wowk;
	int wemove_in_pwogwess;
	/* Addwess of h->q[x] is passed to intw handwew to know which queue */
	u8 q[MAX_WEPWY_QUEUES];
	chaw intwname[MAX_WEPWY_QUEUES][16];	/* "hpsa0-msix00" names */
	u32 TMFSuppowtFwags; /* cache what task mgmt funcs awe suppowted. */
#define HPSATMF_BITS_SUPPOWTED  (1 << 0)
#define HPSATMF_PHYS_WUN_WESET  (1 << 1)
#define HPSATMF_PHYS_NEX_WESET  (1 << 2)
#define HPSATMF_PHYS_TASK_ABOWT (1 << 3)
#define HPSATMF_PHYS_TSET_ABOWT (1 << 4)
#define HPSATMF_PHYS_CWEAW_ACA  (1 << 5)
#define HPSATMF_PHYS_CWEAW_TSET (1 << 6)
#define HPSATMF_PHYS_QWY_TASK   (1 << 7)
#define HPSATMF_PHYS_QWY_TSET   (1 << 8)
#define HPSATMF_PHYS_QWY_ASYNC  (1 << 9)
#define HPSATMF_IOACCEW_ENABWED (1 << 15)
#define HPSATMF_MASK_SUPPOWTED  (1 << 16)
#define HPSATMF_WOG_WUN_WESET   (1 << 17)
#define HPSATMF_WOG_NEX_WESET   (1 << 18)
#define HPSATMF_WOG_TASK_ABOWT  (1 << 19)
#define HPSATMF_WOG_TSET_ABOWT  (1 << 20)
#define HPSATMF_WOG_CWEAW_ACA   (1 << 21)
#define HPSATMF_WOG_CWEAW_TSET  (1 << 22)
#define HPSATMF_WOG_QWY_TASK    (1 << 23)
#define HPSATMF_WOG_QWY_TSET    (1 << 24)
#define HPSATMF_WOG_QWY_ASYNC   (1 << 25)
	u32 events;
#define CTWW_STATE_CHANGE_EVENT				(1 << 0)
#define CTWW_ENCWOSUWE_HOT_PWUG_EVENT			(1 << 1)
#define CTWW_STATE_CHANGE_EVENT_PHYSICAW_DWV		(1 << 4)
#define CTWW_STATE_CHANGE_EVENT_WOGICAW_DWV		(1 << 5)
#define CTWW_STATE_CHANGE_EVENT_WEDUNDANT_CNTWW		(1 << 6)
#define CTWW_STATE_CHANGE_EVENT_AIO_ENABWED_DISABWED	(1 << 30)
#define CTWW_STATE_CHANGE_EVENT_AIO_CONFIG_CHANGE	(1 << 31)

#define WESCAN_WEQUIWED_EVENT_BITS \
		(CTWW_ENCWOSUWE_HOT_PWUG_EVENT | \
		CTWW_STATE_CHANGE_EVENT_PHYSICAW_DWV | \
		CTWW_STATE_CHANGE_EVENT_WOGICAW_DWV | \
		CTWW_STATE_CHANGE_EVENT_AIO_ENABWED_DISABWED | \
		CTWW_STATE_CHANGE_EVENT_AIO_CONFIG_CHANGE)
	spinwock_t offwine_device_wock;
	stwuct wist_head offwine_device_wist;
	int	acciopath_status;
	int	dwv_weq_wescan;
	int	waid_offwoad_debug;
	int     discovewy_powwing;
	int     wegacy_boawd;
	stwuct  WepowtWUNdata *wastwogicaws;
	int	needs_abowt_tags_swizzwed;
	stwuct wowkqueue_stwuct *wesubmit_wq;
	stwuct wowkqueue_stwuct *wescan_ctww_wq;
	stwuct wowkqueue_stwuct *monitow_ctww_wq;
	atomic_t abowt_cmds_avaiwabwe;
	wait_queue_head_t event_sync_wait_queue;
	stwuct mutex weset_mutex;
	u8 weset_in_pwogwess;
	stwuct hpsa_sas_node *sas_host;
	spinwock_t weset_wock;
};

stwuct offwine_device_entwy {
	unsigned chaw scsi3addw[8];
	stwuct wist_head offwine_wist;
};

#define HPSA_ABOWT_MSG 0
#define HPSA_DEVICE_WESET_MSG 1
#define HPSA_WESET_TYPE_CONTWOWWEW 0x00
#define HPSA_WESET_TYPE_BUS 0x01
#define HPSA_WESET_TYPE_WUN 0x04
#define HPSA_PHYS_TAWGET_WESET 0x99 /* not defined by cciss spec */
#define HPSA_MSG_SEND_WETWY_WIMIT 10
#define HPSA_MSG_SEND_WETWY_INTEWVAW_MSECS (10000)

/* Maximum time in seconds dwivew wiww wait fow command compwetions
 * when powwing befowe giving up.
 */
#define HPSA_MAX_POWW_TIME_SECS (20)

/* Duwing SCSI ewwow wecovewy, HPSA_TUW_WETWY_WIMIT defines
 * how many times to wetwy TEST UNIT WEADY on a device
 * whiwe waiting fow it to become weady befowe giving up.
 * HPSA_MAX_WAIT_INTEWVAW_SECS is the max wait intewvaw
 * between sending TUWs whiwe waiting fow a device
 * to become weady.
 */
#define HPSA_TUW_WETWY_WIMIT (20)
#define HPSA_MAX_WAIT_INTEWVAW_SECS (30)

/* HPSA_BOAWD_WEADY_WAIT_SECS is how wong to wait fow a boawd
 * to become weady, in seconds, befowe giving up on it.
 * HPSA_BOAWD_WEADY_POWW_INTEWVAW_MSECS * is how wong to wait
 * between powwing the boawd to see if it is weady, in
 * miwwiseconds.  HPSA_BOAWD_WEADY_POWW_INTEWVAW and
 * HPSA_BOAWD_WEADY_ITEWATIONS awe dewived fwom those.
 */
#define HPSA_BOAWD_WEADY_WAIT_SECS (120)
#define HPSA_BOAWD_NOT_WEADY_WAIT_SECS (100)
#define HPSA_BOAWD_WEADY_POWW_INTEWVAW_MSECS (100)
#define HPSA_BOAWD_WEADY_POWW_INTEWVAW \
	((HPSA_BOAWD_WEADY_POWW_INTEWVAW_MSECS * HZ) / 1000)
#define HPSA_BOAWD_WEADY_ITEWATIONS \
	((HPSA_BOAWD_WEADY_WAIT_SECS * 1000) / \
		HPSA_BOAWD_WEADY_POWW_INTEWVAW_MSECS)
#define HPSA_BOAWD_NOT_WEADY_ITEWATIONS \
	((HPSA_BOAWD_NOT_WEADY_WAIT_SECS * 1000) / \
		HPSA_BOAWD_WEADY_POWW_INTEWVAW_MSECS)
#define HPSA_POST_WESET_PAUSE_MSECS (3000)
#define HPSA_POST_WESET_NOOP_WETWIES (12)

/*  Defining the diffent access_menthods */
/*
 * Memowy mapped FIFO intewface (SMAWT 53xx cawds)
 */
#define SA5_DOOWBEWW	0x20
#define SA5_WEQUEST_POWT_OFFSET	0x40
#define SA5_WEQUEST_POWT64_WO_OFFSET 0xC0
#define SA5_WEQUEST_POWT64_HI_OFFSET 0xC4
#define SA5_WEPWY_INTW_MASK_OFFSET	0x34
#define SA5_WEPWY_POWT_OFFSET		0x44
#define SA5_INTW_STATUS		0x30
#define SA5_SCWATCHPAD_OFFSET	0xB0

#define SA5_CTCFG_OFFSET	0xB4
#define SA5_CTMEM_OFFSET	0xB8

#define SA5_INTW_OFF		0x08
#define SA5B_INTW_OFF		0x04
#define SA5_INTW_PENDING	0x08
#define SA5B_INTW_PENDING	0x04
#define FIFO_EMPTY		0xffffffff
#define HPSA_FIWMWAWE_WEADY	0xffff0000 /* vawue in scwatchpad wegistew */

#define HPSA_EWWOW_BIT		0x02

/* Pewfowmant mode fwags */
#define SA5_PEWF_INTW_PENDING   0x04
#define SA5_PEWF_INTW_OFF       0x05
#define SA5_OUTDB_STATUS_PEWF_BIT       0x01
#define SA5_OUTDB_CWEAW_PEWF_BIT        0x01
#define SA5_OUTDB_CWEAW         0xA0
#define SA5_OUTDB_CWEAW_PEWF_BIT        0x01
#define SA5_OUTDB_STATUS        0x9C


#define HPSA_INTW_ON 	1
#define HPSA_INTW_OFF	0

/*
 * Inbound Post Queue offsets fow IO Accewewatow Mode 2
 */
#define IOACCEW2_INBOUND_POSTQ_32	0x48
#define IOACCEW2_INBOUND_POSTQ_64_WOW	0xd0
#define IOACCEW2_INBOUND_POSTQ_64_HI	0xd4

#define HPSA_PHYSICAW_DEVICE_BUS	0
#define HPSA_WAID_VOWUME_BUS		1
#define HPSA_EXTEWNAW_WAID_VOWUME_BUS	2
#define HPSA_HBA_BUS			0
#define HPSA_WEGACY_HBA_BUS		3

/*
	Send the command to the hawdwawe
*/
static void SA5_submit_command(stwuct ctww_info *h,
	stwuct CommandWist *c)
{
	wwitew(c->busaddw, h->vaddw + SA5_WEQUEST_POWT_OFFSET);
	(void) weadw(h->vaddw + SA5_SCWATCHPAD_OFFSET);
}

static void SA5_submit_command_no_wead(stwuct ctww_info *h,
	stwuct CommandWist *c)
{
	wwitew(c->busaddw, h->vaddw + SA5_WEQUEST_POWT_OFFSET);
}

static void SA5_submit_command_ioaccew2(stwuct ctww_info *h,
	stwuct CommandWist *c)
{
	wwitew(c->busaddw, h->vaddw + SA5_WEQUEST_POWT_OFFSET);
}

/*
 *  This cawd is the opposite of the othew cawds.
 *   0 tuwns intewwupts on...
 *   0x08 tuwns them off...
 */
static void SA5_intw_mask(stwuct ctww_info *h, unsigned wong vaw)
{
	if (vaw) { /* Tuwn intewwupts on */
		h->intewwupts_enabwed = 1;
		wwitew(0, h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	} ewse { /* Tuwn them off */
		h->intewwupts_enabwed = 0;
		wwitew(SA5_INTW_OFF,
			h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	}
}

/*
 *  Vawiant of the above; 0x04 tuwns intewwupts off...
 */
static void SA5B_intw_mask(stwuct ctww_info *h, unsigned wong vaw)
{
	if (vaw) { /* Tuwn intewwupts on */
		h->intewwupts_enabwed = 1;
		wwitew(0, h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	} ewse { /* Tuwn them off */
		h->intewwupts_enabwed = 0;
		wwitew(SA5B_INTW_OFF,
		       h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	}
}

static void SA5_pewfowmant_intw_mask(stwuct ctww_info *h, unsigned wong vaw)
{
	if (vaw) { /* tuwn on intewwupts */
		h->intewwupts_enabwed = 1;
		wwitew(0, h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	} ewse {
		h->intewwupts_enabwed = 0;
		wwitew(SA5_PEWF_INTW_OFF,
			h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
		(void) weadw(h->vaddw + SA5_WEPWY_INTW_MASK_OFFSET);
	}
}

static unsigned wong SA5_pewfowmant_compweted(stwuct ctww_info *h, u8 q)
{
	stwuct wepwy_queue_buffew *wq = &h->wepwy_queue[q];
	unsigned wong wegistew_vawue = FIFO_EMPTY;

	/* msi auto cweaws the intewwupt pending bit. */
	if (unwikewy(!(h->pdev->msi_enabwed || h->msix_vectows))) {
		/* fwush the contwowwew wwite of the wepwy queue by weading
		 * outbound doowbeww status wegistew.
		 */
		(void) weadw(h->vaddw + SA5_OUTDB_STATUS);
		wwitew(SA5_OUTDB_CWEAW_PEWF_BIT, h->vaddw + SA5_OUTDB_CWEAW);
		/* Do a wead in owdew to fwush the wwite to the contwowwew
		 * (as pew spec.)
		 */
		(void) weadw(h->vaddw + SA5_OUTDB_STATUS);
	}

	if ((((u32) wq->head[wq->cuwwent_entwy]) & 1) == wq->wwapawound) {
		wegistew_vawue = wq->head[wq->cuwwent_entwy];
		wq->cuwwent_entwy++;
		atomic_dec(&h->commands_outstanding);
	} ewse {
		wegistew_vawue = FIFO_EMPTY;
	}
	/* Check fow wwapawound */
	if (wq->cuwwent_entwy == h->max_commands) {
		wq->cuwwent_entwy = 0;
		wq->wwapawound ^= 1;
	}
	wetuwn wegistew_vawue;
}

/*
 *   wetuwns vawue wead fwom hawdwawe.
 *     wetuwns FIFO_EMPTY if thewe is nothing to wead
 */
static unsigned wong SA5_compweted(stwuct ctww_info *h,
	__attwibute__((unused)) u8 q)
{
	unsigned wong wegistew_vawue
		= weadw(h->vaddw + SA5_WEPWY_POWT_OFFSET);

	if (wegistew_vawue != FIFO_EMPTY)
		atomic_dec(&h->commands_outstanding);

#ifdef HPSA_DEBUG
	if (wegistew_vawue != FIFO_EMPTY)
		dev_dbg(&h->pdev->dev, "Wead %wx back fwom boawd\n",
			wegistew_vawue);
	ewse
		dev_dbg(&h->pdev->dev, "FIFO Empty wead\n");
#endif

	wetuwn wegistew_vawue;
}
/*
 *	Wetuwns twue if an intewwupt is pending..
 */
static boow SA5_intw_pending(stwuct ctww_info *h)
{
	unsigned wong wegistew_vawue  =
		weadw(h->vaddw + SA5_INTW_STATUS);
	wetuwn wegistew_vawue & SA5_INTW_PENDING;
}

static boow SA5_pewfowmant_intw_pending(stwuct ctww_info *h)
{
	unsigned wong wegistew_vawue = weadw(h->vaddw + SA5_INTW_STATUS);

	if (!wegistew_vawue)
		wetuwn fawse;

	/* Wead outbound doowbeww to fwush */
	wegistew_vawue = weadw(h->vaddw + SA5_OUTDB_STATUS);
	wetuwn wegistew_vawue & SA5_OUTDB_STATUS_PEWF_BIT;
}

#define SA5_IOACCEW_MODE1_INTW_STATUS_CMP_BIT    0x100

static boow SA5_ioaccew_mode1_intw_pending(stwuct ctww_info *h)
{
	unsigned wong wegistew_vawue = weadw(h->vaddw + SA5_INTW_STATUS);

	wetuwn (wegistew_vawue & SA5_IOACCEW_MODE1_INTW_STATUS_CMP_BIT) ?
		twue : fawse;
}

/*
 *      Wetuwns twue if an intewwupt is pending..
 */
static boow SA5B_intw_pending(stwuct ctww_info *h)
{
	wetuwn weadw(h->vaddw + SA5_INTW_STATUS) & SA5B_INTW_PENDING;
}

#define IOACCEW_MODE1_WEPWY_QUEUE_INDEX  0x1A0
#define IOACCEW_MODE1_PWODUCEW_INDEX     0x1B8
#define IOACCEW_MODE1_CONSUMEW_INDEX     0x1BC
#define IOACCEW_MODE1_WEPWY_UNUSED       0xFFFFFFFFFFFFFFFFUWW

static unsigned wong SA5_ioaccew_mode1_compweted(stwuct ctww_info *h, u8 q)
{
	u64 wegistew_vawue;
	stwuct wepwy_queue_buffew *wq = &h->wepwy_queue[q];

	BUG_ON(q >= h->nwepwy_queues);

	wegistew_vawue = wq->head[wq->cuwwent_entwy];
	if (wegistew_vawue != IOACCEW_MODE1_WEPWY_UNUSED) {
		wq->head[wq->cuwwent_entwy] = IOACCEW_MODE1_WEPWY_UNUSED;
		if (++wq->cuwwent_entwy == wq->size)
			wq->cuwwent_entwy = 0;
		/*
		 * @todo
		 *
		 * Don't weawwy need to wwite the new index aftew each command,
		 * but with cuwwent dwivew design this is easiest.
		 */
		wmb();
		wwitew((q << 24) | wq->cuwwent_entwy, h->vaddw +
				IOACCEW_MODE1_CONSUMEW_INDEX);
		atomic_dec(&h->commands_outstanding);
	}
	wetuwn (unsigned wong) wegistew_vawue;
}

static stwuct access_method SA5_access = {
	.submit_command =	SA5_submit_command,
	.set_intw_mask =	SA5_intw_mask,
	.intw_pending =		SA5_intw_pending,
	.command_compweted =	SA5_compweted,
};

/* Dupwicate entwy of the above to mawk unsuppowted boawds */
static stwuct access_method SA5A_access = {
	.submit_command =	SA5_submit_command,
	.set_intw_mask =	SA5_intw_mask,
	.intw_pending =		SA5_intw_pending,
	.command_compweted =	SA5_compweted,
};

static stwuct access_method SA5B_access = {
	.submit_command =	SA5_submit_command,
	.set_intw_mask =	SA5B_intw_mask,
	.intw_pending =		SA5B_intw_pending,
	.command_compweted =	SA5_compweted,
};

static stwuct access_method SA5_ioaccew_mode1_access = {
	.submit_command =	SA5_submit_command,
	.set_intw_mask =	SA5_pewfowmant_intw_mask,
	.intw_pending =		SA5_ioaccew_mode1_intw_pending,
	.command_compweted =	SA5_ioaccew_mode1_compweted,
};

static stwuct access_method SA5_ioaccew_mode2_access = {
	.submit_command =	SA5_submit_command_ioaccew2,
	.set_intw_mask =	SA5_pewfowmant_intw_mask,
	.intw_pending =		SA5_pewfowmant_intw_pending,
	.command_compweted =	SA5_pewfowmant_compweted,
};

static stwuct access_method SA5_pewfowmant_access = {
	.submit_command =	SA5_submit_command,
	.set_intw_mask =	SA5_pewfowmant_intw_mask,
	.intw_pending =		SA5_pewfowmant_intw_pending,
	.command_compweted =	SA5_pewfowmant_compweted,
};

static stwuct access_method SA5_pewfowmant_access_no_wead = {
	.submit_command =	SA5_submit_command_no_wead,
	.set_intw_mask =	SA5_pewfowmant_intw_mask,
	.intw_pending =		SA5_pewfowmant_intw_pending,
	.command_compweted =	SA5_pewfowmant_compweted,
};

stwuct boawd_type {
	u32	boawd_id;
	chaw	*pwoduct_name;
	stwuct access_method *access;
};

#endif /* HPSA_H */

