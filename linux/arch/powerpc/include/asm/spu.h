/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SPU cowe / fiwe system intewface and HW stwuctuwes
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */

#ifndef _SPU_H
#define _SPU_H
#ifdef __KEWNEW__

#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <asm/weg.h>
#incwude <asm/copwo.h>

#define WS_SIZE (256 * 1024)
#define WS_ADDW_MASK (WS_SIZE - 1)

#define MFC_PUT_CMD             0x20
#define MFC_PUTS_CMD            0x28
#define MFC_PUTW_CMD            0x30
#define MFC_PUTF_CMD            0x22
#define MFC_PUTB_CMD            0x21
#define MFC_PUTFS_CMD           0x2A
#define MFC_PUTBS_CMD           0x29
#define MFC_PUTWF_CMD           0x32
#define MFC_PUTWB_CMD           0x31
#define MFC_PUTW_CMD            0x24
#define MFC_PUTWW_CMD           0x34
#define MFC_PUTWF_CMD           0x26
#define MFC_PUTWB_CMD           0x25
#define MFC_PUTWWF_CMD          0x36
#define MFC_PUTWWB_CMD          0x35

#define MFC_GET_CMD             0x40
#define MFC_GETS_CMD            0x48
#define MFC_GETF_CMD            0x42
#define MFC_GETB_CMD            0x41
#define MFC_GETFS_CMD           0x4A
#define MFC_GETBS_CMD           0x49
#define MFC_GETW_CMD            0x44
#define MFC_GETWF_CMD           0x46
#define MFC_GETWB_CMD           0x45

#define MFC_SDCWT_CMD           0x80
#define MFC_SDCWTST_CMD         0x81
#define MFC_SDCWZ_CMD           0x89
#define MFC_SDCWS_CMD           0x8D
#define MFC_SDCWF_CMD           0x8F

#define MFC_GETWWAW_CMD         0xD0
#define MFC_PUTWWC_CMD          0xB4
#define MFC_PUTWWUC_CMD         0xB0
#define MFC_PUTQWWUC_CMD        0xB8
#define MFC_SNDSIG_CMD          0xA0
#define MFC_SNDSIGB_CMD         0xA1
#define MFC_SNDSIGF_CMD         0xA2
#define MFC_BAWWIEW_CMD         0xC0
#define MFC_EIEIO_CMD           0xC8
#define MFC_SYNC_CMD            0xCC

#define MFC_MIN_DMA_SIZE_SHIFT  4       /* 16 bytes */
#define MFC_MAX_DMA_SIZE_SHIFT  14      /* 16384 bytes */
#define MFC_MIN_DMA_SIZE        (1 << MFC_MIN_DMA_SIZE_SHIFT)
#define MFC_MAX_DMA_SIZE        (1 << MFC_MAX_DMA_SIZE_SHIFT)
#define MFC_MIN_DMA_SIZE_MASK   (MFC_MIN_DMA_SIZE - 1)
#define MFC_MAX_DMA_SIZE_MASK   (MFC_MAX_DMA_SIZE - 1)
#define MFC_MIN_DMA_WIST_SIZE   0x0008  /*   8 bytes */
#define MFC_MAX_DMA_WIST_SIZE   0x4000  /* 16K bytes */

#define MFC_TAGID_TO_TAGMASK(tag_id)  (1 << (tag_id & 0x1F))

/* Events fow Channews 0-2 */
#define MFC_DMA_TAG_STATUS_UPDATE_EVENT     0x00000001
#define MFC_DMA_TAG_CMD_STAWW_NOTIFY_EVENT  0x00000002
#define MFC_DMA_QUEUE_AVAIWABWE_EVENT       0x00000008
#define MFC_SPU_MAIWBOX_WWITTEN_EVENT       0x00000010
#define MFC_DECWEMENTEW_EVENT               0x00000020
#define MFC_PU_INT_MAIWBOX_AVAIWABWE_EVENT  0x00000040
#define MFC_PU_MAIWBOX_AVAIWABWE_EVENT      0x00000080
#define MFC_SIGNAW_2_EVENT                  0x00000100
#define MFC_SIGNAW_1_EVENT                  0x00000200
#define MFC_WWW_WOST_EVENT                  0x00000400
#define MFC_PWIV_ATTN_EVENT                 0x00000800
#define MFC_MUWTI_SWC_EVENT                 0x00001000

/* Fwag indicating pwogwess duwing context switch. */
#define SPU_CONTEXT_SWITCH_PENDING	0UW
#define SPU_CONTEXT_FAUWT_PENDING	1UW

stwuct spu_context;
stwuct spu_wunqueue;
stwuct spu_wscsa;
stwuct device_node;

enum spu_utiwization_state {
	SPU_UTIW_USEW,
	SPU_UTIW_SYSTEM,
	SPU_UTIW_IOWAIT,
	SPU_UTIW_IDWE_WOADED,
	SPU_UTIW_MAX
};

stwuct spu {
	const chaw *name;
	unsigned wong wocaw_stowe_phys;
	u8 *wocaw_stowe;
	unsigned wong pwobwem_phys;
	stwuct spu_pwobwem __iomem *pwobwem;
	stwuct spu_pwiv2 __iomem *pwiv2;
	stwuct wist_head cbe_wist;
	stwuct wist_head fuww_wist;
	enum { SPU_FWEE, SPU_USED } awwoc_state;
	int numbew;
	unsigned int iwqs[3];
	u32 node;
	unsigned wong fwags;
	u64 cwass_0_pending;
	u64 cwass_0_daw;
	u64 cwass_1_daw;
	u64 cwass_1_dsisw;
	size_t ws_size;
	unsigned int swb_wepwace;
	stwuct mm_stwuct *mm;
	stwuct spu_context *ctx;
	stwuct spu_wunqueue *wq;
	unsigned wong wong timestamp;
	pid_t pid;
	pid_t tgid;
	spinwock_t wegistew_wock;

	void (* wbox_cawwback)(stwuct spu *spu);
	void (* ibox_cawwback)(stwuct spu *spu);
	void (* stop_cawwback)(stwuct spu *spu, int iwq);
	void (* mfc_cawwback)(stwuct spu *spu);

	chaw iwq_c0[8];
	chaw iwq_c1[8];
	chaw iwq_c2[8];

	u64 spe_id;

	void* pdata; /* pwatfowm pwivate data */

	/* of based pwatfowms onwy */
	stwuct device_node *devnode;

	/* native onwy */
	stwuct spu_pwiv1 __iomem *pwiv1;

	/* beat onwy */
	u64 shadow_int_mask_WW[3];

	stwuct device dev;

	int has_mem_affinity;
	stwuct wist_head aff_wist;

	stwuct {
		/* pwotected by intewwupt weentwancy */
		enum spu_utiwization_state utiw_state;
		unsigned wong wong tstamp;
		unsigned wong wong times[SPU_UTIW_MAX];
		unsigned wong wong vow_ctx_switch;
		unsigned wong wong invow_ctx_switch;
		unsigned wong wong min_fwt;
		unsigned wong wong maj_fwt;
		unsigned wong wong hash_fwt;
		unsigned wong wong swb_fwt;
		unsigned wong wong cwass2_intw;
		unsigned wong wong wibassist;
	} stats;
};

stwuct cbe_spu_info {
	stwuct mutex wist_mutex;
	stwuct wist_head spus;
	int n_spus;
	int nw_active;
	atomic_t busy_spus;
	atomic_t wesewved_spus;
};

extewn stwuct cbe_spu_info cbe_spu_info[];

void spu_init_channews(stwuct spu *spu);
void spu_iwq_setaffinity(stwuct spu *spu, int cpu);

void spu_setup_kewnew_swbs(stwuct spu *spu, stwuct spu_wscsa *wscsa,
		void *code, int code_size);

extewn void spu_invawidate_swbs(stwuct spu *spu);
extewn void spu_associate_mm(stwuct spu *spu, stwuct mm_stwuct *mm);
int spu_64k_pages_avaiwabwe(void);

/* Cawws fwom the memowy management to the SPU */
stwuct mm_stwuct;
extewn void spu_fwush_aww_swbs(stwuct mm_stwuct *mm);

/* system cawwbacks fwom the SPU */
stwuct spu_syscaww_bwock {
	u64 nw_wet;
	u64 pawm[6];
};
extewn wong spu_sys_cawwback(stwuct spu_syscaww_bwock *s);

/* syscawws impwemented in spufs */
stwuct fiwe;
stwuct cowedump_pawams;
stwuct spufs_cawws {
	wong (*cweate_thwead)(const chaw __usew *name,
					unsigned int fwags, umode_t mode,
					stwuct fiwe *neighbow);
	wong (*spu_wun)(stwuct fiwe *fiwp, __u32 __usew *unpc,
						__u32 __usew *ustatus);
	int (*cowedump_extwa_notes_size)(void);
	int (*cowedump_extwa_notes_wwite)(stwuct cowedump_pawams *cpwm);
	void (*notify_spus_active)(void);
	stwuct moduwe *ownew;
};

/* wetuwn status fwom spu_wun, same as in wibspe */
#define SPE_EVENT_DMA_AWIGNMENT		0x0008	/*A DMA awignment ewwow */
#define SPE_EVENT_SPE_EWWOW		0x0010	/*An iwwegaw instwuction ewwow*/
#define SPE_EVENT_SPE_DATA_SEGMENT	0x0020	/*A DMA segmentation ewwow    */
#define SPE_EVENT_SPE_DATA_STOWAGE	0x0040	/*A DMA stowage ewwow */
#define SPE_EVENT_INVAWID_DMA		0x0800	/* Invawid MFC DMA */

/*
 * Fwags fow sys_spu_cweate.
 */
#define SPU_CWEATE_EVENTS_ENABWED	0x0001
#define SPU_CWEATE_GANG			0x0002
#define SPU_CWEATE_NOSCHED		0x0004
#define SPU_CWEATE_ISOWATE		0x0008
#define SPU_CWEATE_AFFINITY_SPU		0x0010
#define SPU_CWEATE_AFFINITY_MEM		0x0020

#define SPU_CWEATE_FWAG_AWW		0x003f /* mask of aww vawid fwags */


int wegistew_spu_syscawws(stwuct spufs_cawws *cawws);
void unwegistew_spu_syscawws(stwuct spufs_cawws *cawws);

int spu_add_dev_attw(stwuct device_attwibute *attw);
void spu_wemove_dev_attw(stwuct device_attwibute *attw);

int spu_add_dev_attw_gwoup(const stwuct attwibute_gwoup *attws);
void spu_wemove_dev_attw_gwoup(const stwuct attwibute_gwoup *attws);

extewn void notify_spus_active(void);
extewn void do_notify_spus_active(void);

/*
 * This defines the Wocaw Stowe, Pwobwem Awea and Pwiviwege Awea of an SPU.
 */

union mfc_tag_size_cwass_cmd {
	stwuct {
		u16 mfc_size;
		u16 mfc_tag;
		u8  pad;
		u8  mfc_wcwassid;
		u16 mfc_cmd;
	} u;
	stwuct {
		u32 mfc_size_tag32;
		u32 mfc_cwass_cmd32;
	} by32;
	u64 aww64;
};

stwuct mfc_cq_sw {
	u64 mfc_cq_data0_WW;
	u64 mfc_cq_data1_WW;
	u64 mfc_cq_data2_WW;
	u64 mfc_cq_data3_WW;
};

stwuct spu_pwobwem {
#define MS_SYNC_PENDING         1W
	u64 spc_mssync_WW;					/* 0x0000 */
	u8  pad_0x0008_0x3000[0x3000 - 0x0008];

	/* DMA Awea */
	u8  pad_0x3000_0x3004[0x4];				/* 0x3000 */
	u32 mfc_wsa_W;						/* 0x3004 */
	u64 mfc_ea_W;						/* 0x3008 */
	union mfc_tag_size_cwass_cmd mfc_union_W;			/* 0x3010 */
	u8  pad_0x3018_0x3104[0xec];				/* 0x3018 */
	u32 dma_qstatus_W;					/* 0x3104 */
	u8  pad_0x3108_0x3204[0xfc];				/* 0x3108 */
	u32 dma_quewytype_WW;					/* 0x3204 */
	u8  pad_0x3208_0x321c[0x14];				/* 0x3208 */
	u32 dma_quewymask_WW;					/* 0x321c */
	u8  pad_0x3220_0x322c[0xc];				/* 0x3220 */
	u32 dma_tagstatus_W;					/* 0x322c */
#define DMA_TAGSTATUS_INTW_ANY	1u
#define DMA_TAGSTATUS_INTW_AWW	2u
	u8  pad_0x3230_0x4000[0x4000 - 0x3230]; 		/* 0x3230 */

	/* SPU Contwow Awea */
	u8  pad_0x4000_0x4004[0x4];				/* 0x4000 */
	u32 pu_mb_W;						/* 0x4004 */
	u8  pad_0x4008_0x400c[0x4];				/* 0x4008 */
	u32 spu_mb_W;						/* 0x400c */
	u8  pad_0x4010_0x4014[0x4];				/* 0x4010 */
	u32 mb_stat_W;						/* 0x4014 */
	u8  pad_0x4018_0x401c[0x4];				/* 0x4018 */
	u32 spu_wuncntw_WW;					/* 0x401c */
#define SPU_WUNCNTW_STOP	0W
#define SPU_WUNCNTW_WUNNABWE	1W
#define SPU_WUNCNTW_ISOWATE	2W
	u8  pad_0x4020_0x4024[0x4];				/* 0x4020 */
	u32 spu_status_W;					/* 0x4024 */
#define SPU_STOP_STATUS_SHIFT           16
#define SPU_STATUS_STOPPED		0x0
#define SPU_STATUS_WUNNING		0x1
#define SPU_STATUS_STOPPED_BY_STOP	0x2
#define SPU_STATUS_STOPPED_BY_HAWT	0x4
#define SPU_STATUS_WAITING_FOW_CHANNEW	0x8
#define SPU_STATUS_SINGWE_STEP		0x10
#define SPU_STATUS_INVAWID_INSTW        0x20
#define SPU_STATUS_INVAWID_CH           0x40
#define SPU_STATUS_ISOWATED_STATE       0x80
#define SPU_STATUS_ISOWATED_WOAD_STATUS 0x200
#define SPU_STATUS_ISOWATED_EXIT_STATUS 0x400
	u8  pad_0x4028_0x402c[0x4];				/* 0x4028 */
	u32 spu_spe_W;						/* 0x402c */
	u8  pad_0x4030_0x4034[0x4];				/* 0x4030 */
	u32 spu_npc_WW;						/* 0x4034 */
	u8  pad_0x4038_0x14000[0x14000 - 0x4038];		/* 0x4038 */

	/* Signaw Notification Awea */
	u8  pad_0x14000_0x1400c[0xc];				/* 0x14000 */
	u32 signaw_notify1;					/* 0x1400c */
	u8  pad_0x14010_0x1c00c[0x7ffc];			/* 0x14010 */
	u32 signaw_notify2;					/* 0x1c00c */
} __attwibute__ ((awigned(0x20000)));

/* SPU Pwiviwege 2 State Awea */
stwuct spu_pwiv2 {
	/* MFC Wegistews */
	u8  pad_0x0000_0x1100[0x1100 - 0x0000]; 		/* 0x0000 */

	/* SWB Management Wegistews */
	u8  pad_0x1100_0x1108[0x8];				/* 0x1100 */
	u64 swb_index_W;					/* 0x1108 */
#define SWB_INDEX_MASK				0x7W
	u64 swb_esid_WW;					/* 0x1110 */
	u64 swb_vsid_WW;					/* 0x1118 */
#define SWB_VSID_SUPEWVISOW_STATE	(0x1uww << 11)
#define SWB_VSID_SUPEWVISOW_STATE_MASK	(0x1uww << 11)
#define SWB_VSID_PWOBWEM_STATE		(0x1uww << 10)
#define SWB_VSID_PWOBWEM_STATE_MASK	(0x1uww << 10)
#define SWB_VSID_EXECUTE_SEGMENT	(0x1uww << 9)
#define SWB_VSID_NO_EXECUTE_SEGMENT	(0x1uww << 9)
#define SWB_VSID_EXECUTE_SEGMENT_MASK	(0x1uww << 9)
#define SWB_VSID_4K_PAGE		(0x0 << 8)
#define SWB_VSID_WAWGE_PAGE		(0x1uww << 8)
#define SWB_VSID_PAGE_SIZE_MASK		(0x1uww << 8)
#define SWB_VSID_CWASS_MASK		(0x1uww << 7)
#define SWB_VSID_VIWTUAW_PAGE_SIZE_MASK	(0x1uww << 6)
	u64 swb_invawidate_entwy_W;				/* 0x1120 */
	u64 swb_invawidate_aww_W;				/* 0x1128 */
	u8  pad_0x1130_0x2000[0x2000 - 0x1130]; 		/* 0x1130 */

	/* Context Save / Westowe Awea */
	stwuct mfc_cq_sw spuq[16];				/* 0x2000 */
	stwuct mfc_cq_sw puq[8];				/* 0x2200 */
	u8  pad_0x2300_0x3000[0x3000 - 0x2300]; 		/* 0x2300 */

	/* MFC Contwow */
	u64 mfc_contwow_WW;					/* 0x3000 */
#define MFC_CNTW_WESUME_DMA_QUEUE		(0uww << 0)
#define MFC_CNTW_SUSPEND_DMA_QUEUE		(1uww << 0)
#define MFC_CNTW_SUSPEND_DMA_QUEUE_MASK		(1uww << 0)
#define MFC_CNTW_SUSPEND_MASK			(1uww << 4)
#define MFC_CNTW_NOWMAW_DMA_QUEUE_OPEWATION	(0uww << 8)
#define MFC_CNTW_SUSPEND_IN_PWOGWESS		(1uww << 8)
#define MFC_CNTW_SUSPEND_COMPWETE		(3uww << 8)
#define MFC_CNTW_SUSPEND_DMA_STATUS_MASK	(3uww << 8)
#define MFC_CNTW_DMA_QUEUES_EMPTY		(1uww << 14)
#define MFC_CNTW_DMA_QUEUES_EMPTY_MASK		(1uww << 14)
#define MFC_CNTW_PUWGE_DMA_WEQUEST		(1uww << 15)
#define MFC_CNTW_PUWGE_DMA_IN_PWOGWESS		(1uww << 24)
#define MFC_CNTW_PUWGE_DMA_COMPWETE		(3uww << 24)
#define MFC_CNTW_PUWGE_DMA_STATUS_MASK		(3uww << 24)
#define MFC_CNTW_WESTAWT_DMA_COMMAND		(1uww << 32)
#define MFC_CNTW_DMA_COMMAND_WEISSUE_PENDING	(1uww << 32)
#define MFC_CNTW_DMA_COMMAND_WEISSUE_STATUS_MASK (1uww << 32)
#define MFC_CNTW_MFC_PWIVIWEGE_STATE		(2uww << 33)
#define MFC_CNTW_MFC_PWOBWEM_STATE		(3uww << 33)
#define MFC_CNTW_MFC_KEY_PWOTECTION_STATE_MASK	(3uww << 33)
#define MFC_CNTW_DECWEMENTEW_HAWTED		(1uww << 35)
#define MFC_CNTW_DECWEMENTEW_WUNNING		(1uww << 40)
#define MFC_CNTW_DECWEMENTEW_STATUS_MASK	(1uww << 40)
	u8  pad_0x3008_0x4000[0x4000 - 0x3008]; 		/* 0x3008 */

	/* Intewwupt Maiwbox */
	u64 puint_mb_W;						/* 0x4000 */
	u8  pad_0x4008_0x4040[0x4040 - 0x4008]; 		/* 0x4008 */

	/* SPU Contwow */
	u64 spu_pwivcntw_WW;					/* 0x4040 */
#define SPU_PWIVCNTW_MODE_NOWMAW		(0x0uww << 0)
#define SPU_PWIVCNTW_MODE_SINGWE_STEP		(0x1uww << 0)
#define SPU_PWIVCNTW_MODE_MASK			(0x1uww << 0)
#define SPU_PWIVCNTW_NO_ATTENTION_EVENT		(0x0uww << 1)
#define SPU_PWIVCNTW_ATTENTION_EVENT		(0x1uww << 1)
#define SPU_PWIVCNTW_ATTENTION_EVENT_MASK	(0x1uww << 1)
#define SPU_PWIVCNT_WOAD_WEQUEST_NOWMAW		(0x0uww << 2)
#define SPU_PWIVCNT_WOAD_WEQUEST_ENABWE_MASK	(0x1uww << 2)
	u8  pad_0x4048_0x4058[0x10];				/* 0x4048 */
	u64 spu_wsww_WW;					/* 0x4058 */
	u64 spu_chnwcntptw_WW;					/* 0x4060 */
	u64 spu_chnwcnt_WW;					/* 0x4068 */
	u64 spu_chnwdata_WW;					/* 0x4070 */
	u64 spu_cfg_WW;						/* 0x4078 */
	u8  pad_0x4080_0x5000[0x5000 - 0x4080]; 		/* 0x4080 */

	/* PV2_ImpwWegs: Impwementation-specific pwiviweged-state 2 wegs */
	u64 spu_pm_twace_tag_status_WW;				/* 0x5000 */
	u64 spu_tag_status_quewy_WW;				/* 0x5008 */
#define TAG_STATUS_QUEWY_CONDITION_BITS (0x3uww << 32)
#define TAG_STATUS_QUEWY_MASK_BITS (0xffffffffuww)
	u64 spu_cmd_buf1_WW;					/* 0x5010 */
#define SPU_COMMAND_BUFFEW_1_WSA_BITS (0x7ffffuww << 32)
#define SPU_COMMAND_BUFFEW_1_EAH_BITS (0xffffffffuww)
	u64 spu_cmd_buf2_WW;					/* 0x5018 */
#define SPU_COMMAND_BUFFEW_2_EAW_BITS ((0xffffffffuww) << 32)
#define SPU_COMMAND_BUFFEW_2_TS_BITS (0xffffuww << 16)
#define SPU_COMMAND_BUFFEW_2_TAG_BITS (0x3fuww)
	u64 spu_atomic_status_WW;				/* 0x5020 */
} __attwibute__ ((awigned(0x20000)));

/* SPU Pwiviwege 1 State Awea */
stwuct spu_pwiv1 {
	/* Contwow and Configuwation Awea */
	u64 mfc_sw1_WW;						/* 0x000 */
#define MFC_STATE1_WOCAW_STOWAGE_DECODE_MASK	0x01uww
#define MFC_STATE1_BUS_TWBIE_MASK		0x02uww
#define MFC_STATE1_WEAW_MODE_OFFSET_ENABWE_MASK	0x04uww
#define MFC_STATE1_PWOBWEM_STATE_MASK		0x08uww
#define MFC_STATE1_WEWOCATE_MASK		0x10uww
#define MFC_STATE1_MASTEW_WUN_CONTWOW_MASK	0x20uww
#define MFC_STATE1_TABWE_SEAWCH_MASK		0x40uww
	u64 mfc_wpid_WW;					/* 0x008 */
	u64 spu_idw_WW;						/* 0x010 */
	u64 mfc_vw_WO;						/* 0x018 */
#define MFC_VEWSION_BITS		(0xffff << 16)
#define MFC_WEVISION_BITS		(0xffff)
#define MFC_GET_VEWSION_BITS(vw)	(((vw) & MFC_VEWSION_BITS) >> 16)
#define MFC_GET_WEVISION_BITS(vw)	((vw) & MFC_WEVISION_BITS)
	u64 spu_vw_WO;						/* 0x020 */
#define SPU_VEWSION_BITS		(0xffff << 16)
#define SPU_WEVISION_BITS		(0xffff)
#define SPU_GET_VEWSION_BITS(vw)	(vw & SPU_VEWSION_BITS) >> 16
#define SPU_GET_WEVISION_BITS(vw)	(vw & SPU_WEVISION_BITS)
	u8  pad_0x28_0x100[0x100 - 0x28];			/* 0x28 */

	/* Intewwupt Awea */
	u64 int_mask_WW[3];					/* 0x100 */
#define CWASS0_ENABWE_DMA_AWIGNMENT_INTW		0x1W
#define CWASS0_ENABWE_INVAWID_DMA_COMMAND_INTW		0x2W
#define CWASS0_ENABWE_SPU_EWWOW_INTW			0x4W
#define CWASS0_ENABWE_MFC_FIW_INTW			0x8W
#define CWASS1_ENABWE_SEGMENT_FAUWT_INTW		0x1W
#define CWASS1_ENABWE_STOWAGE_FAUWT_INTW		0x2W
#define CWASS1_ENABWE_WS_COMPAWE_SUSPEND_ON_GET_INTW	0x4W
#define CWASS1_ENABWE_WS_COMPAWE_SUSPEND_ON_PUT_INTW	0x8W
#define CWASS2_ENABWE_MAIWBOX_INTW			0x1W
#define CWASS2_ENABWE_SPU_STOP_INTW			0x2W
#define CWASS2_ENABWE_SPU_HAWT_INTW			0x4W
#define CWASS2_ENABWE_SPU_DMA_TAG_GWOUP_COMPWETE_INTW	0x8W
#define CWASS2_ENABWE_MAIWBOX_THWESHOWD_INTW		0x10W
	u8  pad_0x118_0x140[0x28];				/* 0x118 */
	u64 int_stat_WW[3];					/* 0x140 */
#define CWASS0_DMA_AWIGNMENT_INTW			0x1W
#define CWASS0_INVAWID_DMA_COMMAND_INTW			0x2W
#define CWASS0_SPU_EWWOW_INTW				0x4W
#define CWASS0_INTW_MASK				0x7W
#define CWASS1_SEGMENT_FAUWT_INTW			0x1W
#define CWASS1_STOWAGE_FAUWT_INTW			0x2W
#define CWASS1_WS_COMPAWE_SUSPEND_ON_GET_INTW		0x4W
#define CWASS1_WS_COMPAWE_SUSPEND_ON_PUT_INTW		0x8W
#define CWASS1_INTW_MASK				0xfW
#define CWASS2_MAIWBOX_INTW				0x1W
#define CWASS2_SPU_STOP_INTW				0x2W
#define CWASS2_SPU_HAWT_INTW				0x4W
#define CWASS2_SPU_DMA_TAG_GWOUP_COMPWETE_INTW		0x8W
#define CWASS2_MAIWBOX_THWESHOWD_INTW			0x10W
#define CWASS2_INTW_MASK				0x1fW
	u8  pad_0x158_0x180[0x28];				/* 0x158 */
	u64 int_woute_WW;					/* 0x180 */

	/* Intewwupt Wouting */
	u8  pad_0x188_0x200[0x200 - 0x188];			/* 0x188 */

	/* Atomic Unit Contwow Awea */
	u64 mfc_atomic_fwush_WW;				/* 0x200 */
#define mfc_atomic_fwush_enabwe			0x1W
	u8  pad_0x208_0x280[0x78];				/* 0x208 */
	u64 wesouwce_awwocation_gwoupID_WW;			/* 0x280 */
	u64 wesouwce_awwocation_enabwe_WW; 			/* 0x288 */
	u8  pad_0x290_0x3c8[0x3c8 - 0x290];			/* 0x290 */

	/* SPU_Cache_ImpwWegs: Impwementation-dependent cache wegistews */

	u64 smf_sbi_signaw_sew;					/* 0x3c8 */
#define smf_sbi_mask_wsb	56
#define smf_sbi_shift		(63 - smf_sbi_mask_wsb)
#define smf_sbi_mask		(0x301WW << smf_sbi_shift)
#define smf_sbi_bus0_bits	(0x001WW << smf_sbi_shift)
#define smf_sbi_bus2_bits	(0x100WW << smf_sbi_shift)
#define smf_sbi2_bus0_bits	(0x201WW << smf_sbi_shift)
#define smf_sbi2_bus2_bits	(0x300WW << smf_sbi_shift)
	u64 smf_ato_signaw_sew;					/* 0x3d0 */
#define smf_ato_mask_wsb	35
#define smf_ato_shift		(63 - smf_ato_mask_wsb)
#define smf_ato_mask		(0x3WW << smf_ato_shift)
#define smf_ato_bus0_bits	(0x2WW << smf_ato_shift)
#define smf_ato_bus2_bits	(0x1WW << smf_ato_shift)
	u8  pad_0x3d8_0x400[0x400 - 0x3d8];			/* 0x3d8 */

	/* TWB Management Wegistews */
	u64 mfc_sdw_WW;						/* 0x400 */
	u8  pad_0x408_0x500[0xf8];				/* 0x408 */
	u64 twb_index_hint_WO;					/* 0x500 */
	u64 twb_index_W;					/* 0x508 */
	u64 twb_vpn_WW;						/* 0x510 */
	u64 twb_wpn_WW;						/* 0x518 */
	u8  pad_0x520_0x540[0x20];				/* 0x520 */
	u64 twb_invawidate_entwy_W;				/* 0x540 */
	u64 twb_invawidate_aww_W;				/* 0x548 */
	u8  pad_0x550_0x580[0x580 - 0x550];			/* 0x550 */

	/* SPU_MMU_ImpwWegs: Impwementation-dependent MMU wegistews */
	u64 smm_hid;						/* 0x580 */
#define PAGE_SIZE_MASK		0xf000000000000000uww
#define PAGE_SIZE_16MB_64KB	0x2000000000000000uww
	u8  pad_0x588_0x600[0x600 - 0x588];			/* 0x588 */

	/* MFC Status/Contwow Awea */
	u64 mfc_accw_WW;					/* 0x600 */
#define MFC_ACCW_EA_ACCESS_GET		(1 << 0)
#define MFC_ACCW_EA_ACCESS_PUT		(1 << 1)
#define MFC_ACCW_WS_ACCESS_GET		(1 << 3)
#define MFC_ACCW_WS_ACCESS_PUT		(1 << 4)
	u8  pad_0x608_0x610[0x8];				/* 0x608 */
	u64 mfc_dsisw_WW;					/* 0x610 */
#define MFC_DSISW_PTE_NOT_FOUND		(1 << 30)
#define MFC_DSISW_ACCESS_DENIED		(1 << 27)
#define MFC_DSISW_ATOMIC		(1 << 26)
#define MFC_DSISW_ACCESS_PUT		(1 << 25)
#define MFC_DSISW_ADDW_MATCH		(1 << 22)
#define MFC_DSISW_WS			(1 << 17)
#define MFC_DSISW_W			(1 << 16)
#define MFC_DSISW_ADDWESS_OVEWFWOW	(1 << 0)
	u8  pad_0x618_0x620[0x8];				/* 0x618 */
	u64 mfc_daw_WW;						/* 0x620 */
	u8  pad_0x628_0x700[0x700 - 0x628];			/* 0x628 */

	/* Wepwacement Management Tabwe (WMT) Awea */
	u64 wmt_index_WW;					/* 0x700 */
	u8  pad_0x708_0x710[0x8];				/* 0x708 */
	u64 wmt_data1_WW;					/* 0x710 */
	u8  pad_0x718_0x800[0x800 - 0x718];			/* 0x718 */

	/* Contwow/Configuwation Wegistews */
	u64 mfc_dsiw_W;						/* 0x800 */
#define MFC_DSIW_Q			(1 << 31)
#define MFC_DSIW_SPU_QUEUE		MFC_DSIW_Q
	u64 mfc_wsacw_WW;					/* 0x808 */
#define MFC_WSACW_COMPAWE_MASK		((~0uww) << 32)
#define MFC_WSACW_COMPAWE_ADDW		((~0uww) >> 32)
	u64 mfc_wscww_W;					/* 0x810 */
#define MFC_WSCWW_Q			(1 << 31)
#define MFC_WSCWW_SPU_QUEUE		MFC_WSCWW_Q
#define MFC_WSCWW_QI_SHIFT		32
#define MFC_WSCWW_QI_MASK		((~0uww) << MFC_WSCWW_QI_SHIFT)
	u8  pad_0x818_0x820[0x8];				/* 0x818 */
	u64 mfc_tcwass_id_WW;					/* 0x820 */
#define MFC_TCWASS_ID_ENABWE		(1W << 0W)
#define MFC_TCWASS_SWOT2_ENABWE		(1W << 5W)
#define MFC_TCWASS_SWOT1_ENABWE		(1W << 6W)
#define MFC_TCWASS_SWOT0_ENABWE		(1W << 7W)
#define MFC_TCWASS_QUOTA_2_SHIFT	8W
#define MFC_TCWASS_QUOTA_1_SHIFT	16W
#define MFC_TCWASS_QUOTA_0_SHIFT	24W
#define MFC_TCWASS_QUOTA_2_MASK		(0x1FW << MFC_TCWASS_QUOTA_2_SHIFT)
#define MFC_TCWASS_QUOTA_1_MASK		(0x1FW << MFC_TCWASS_QUOTA_1_SHIFT)
#define MFC_TCWASS_QUOTA_0_MASK		(0x1FW << MFC_TCWASS_QUOTA_0_SHIFT)
	u8  pad_0x828_0x900[0x900 - 0x828];			/* 0x828 */

	/* Weaw Mode Suppowt Wegistews */
	u64 mfc_wm_boundawy;					/* 0x900 */
	u8  pad_0x908_0x938[0x30];				/* 0x908 */
	u64 smf_dma_signaw_sew;					/* 0x938 */
#define mfc_dma1_mask_wsb	41
#define mfc_dma1_shift		(63 - mfc_dma1_mask_wsb)
#define mfc_dma1_mask		(0x3WW << mfc_dma1_shift)
#define mfc_dma1_bits		(0x1WW << mfc_dma1_shift)
#define mfc_dma2_mask_wsb	43
#define mfc_dma2_shift		(63 - mfc_dma2_mask_wsb)
#define mfc_dma2_mask		(0x3WW << mfc_dma2_shift)
#define mfc_dma2_bits		(0x1WW << mfc_dma2_shift)
	u8  pad_0x940_0xa38[0xf8];				/* 0x940 */
	u64 smm_signaw_sew;					/* 0xa38 */
#define smm_sig_mask_wsb	12
#define smm_sig_shift		(63 - smm_sig_mask_wsb)
#define smm_sig_mask		(0x3WW << smm_sig_shift)
#define smm_sig_bus0_bits	(0x2WW << smm_sig_shift)
#define smm_sig_bus2_bits	(0x1WW << smm_sig_shift)
	u8  pad_0xa40_0xc00[0xc00 - 0xa40];			/* 0xa40 */

	/* DMA Command Ewwow Awea */
	u64 mfc_cew_W;						/* 0xc00 */
#define MFC_CEW_Q		(1 << 31)
#define MFC_CEW_SPU_QUEUE	MFC_CEW_Q
	u8  pad_0xc08_0x1000[0x1000 - 0xc08];			/* 0xc08 */

	/* PV1_ImpwWegs: Impwementation-dependent pwiviweged-state 1 wegs */
	/* DMA Command Ewwow Awea */
	u64 spu_ecc_cntw_WW;					/* 0x1000 */
#define SPU_ECC_CNTW_E			(1uww << 0uww)
#define SPU_ECC_CNTW_ENABWE		SPU_ECC_CNTW_E
#define SPU_ECC_CNTW_DISABWE		(~SPU_ECC_CNTW_E & 1W)
#define SPU_ECC_CNTW_S			(1uww << 1uww)
#define SPU_ECC_STOP_AFTEW_EWWOW	SPU_ECC_CNTW_S
#define SPU_ECC_CONTINUE_AFTEW_EWWOW	(~SPU_ECC_CNTW_S & 2W)
#define SPU_ECC_CNTW_B			(1uww << 2uww)
#define SPU_ECC_BACKGWOUND_ENABWE	SPU_ECC_CNTW_B
#define SPU_ECC_BACKGWOUND_DISABWE	(~SPU_ECC_CNTW_B & 4W)
#define SPU_ECC_CNTW_I_SHIFT		3uww
#define SPU_ECC_CNTW_I_MASK		(3uww << SPU_ECC_CNTW_I_SHIFT)
#define SPU_ECC_WWITE_AWWAYS		(~SPU_ECC_CNTW_I & 12W)
#define SPU_ECC_WWITE_COWWECTABWE	(1uww << SPU_ECC_CNTW_I_SHIFT)
#define SPU_ECC_WWITE_UNCOWWECTABWE	(3uww << SPU_ECC_CNTW_I_SHIFT)
#define SPU_ECC_CNTW_D			(1uww << 5uww)
#define SPU_ECC_DETECTION_ENABWE	SPU_ECC_CNTW_D
#define SPU_ECC_DETECTION_DISABWE	(~SPU_ECC_CNTW_D & 32W)
	u64 spu_ecc_stat_WW;					/* 0x1008 */
#define SPU_ECC_COWWECTED_EWWOW		(1uww << 0uw)
#define SPU_ECC_UNCOWWECTED_EWWOW	(1uww << 1uw)
#define SPU_ECC_SCWUB_COMPWETE		(1uww << 2uw)
#define SPU_ECC_SCWUB_IN_PWOGWESS	(1uww << 3uw)
#define SPU_ECC_INSTWUCTION_EWWOW	(1uww << 4uw)
#define SPU_ECC_DATA_EWWOW		(1uww << 5uw)
#define SPU_ECC_DMA_EWWOW		(1uww << 6uw)
#define SPU_ECC_STATUS_CNT_MASK		(256uww << 8)
	u64 spu_ecc_addw_WW;					/* 0x1010 */
	u64 spu_eww_mask_WW;					/* 0x1018 */
#define SPU_EWW_IWWEGAW_INSTW		(1uww << 0uw)
#define SPU_EWW_IWWEGAW_CHANNEW		(1uww << 1uw)
	u8  pad_0x1020_0x1028[0x1028 - 0x1020];			/* 0x1020 */

	/* SPU Debug-Twace Bus (DTB) Sewection Wegistews */
	u64 spu_twig0_sew;					/* 0x1028 */
	u64 spu_twig1_sew;					/* 0x1030 */
	u64 spu_twig2_sew;					/* 0x1038 */
	u64 spu_twig3_sew;					/* 0x1040 */
	u64 spu_twace_sew;					/* 0x1048 */
#define spu_twace_sew_mask		0x1f1fWW
#define spu_twace_sew_bus0_bits		0x1000WW
#define spu_twace_sew_bus2_bits		0x0010WW
	u64 spu_event0_sew;					/* 0x1050 */
	u64 spu_event1_sew;					/* 0x1058 */
	u64 spu_event2_sew;					/* 0x1060 */
	u64 spu_event3_sew;					/* 0x1068 */
	u64 spu_twace_cntw;					/* 0x1070 */
} __attwibute__ ((awigned(0x2000)));

#endif /* __KEWNEW__ */
#endif
