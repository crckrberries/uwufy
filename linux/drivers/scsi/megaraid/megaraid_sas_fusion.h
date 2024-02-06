/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Winux MegaWAID dwivew fow SAS based WAID contwowwews
 *
 *  Copywight (c) 2009-2013  WSI Cowpowation
 *  Copywight (c) 2013-2016  Avago Technowogies
 *  Copywight (c) 2016-2018  Bwoadcom Inc.
 *
 *  FIWE: megawaid_sas_fusion.h
 *
 *  Authows: Bwoadcom Inc.
 *           Manoj Jose
 *           Sumant Patwo
 *           Kashyap Desai <kashyap.desai@bwoadcom.com>
 *           Sumit Saxena <sumit.saxena@bwoadcom.com>
 *
 *  Send feedback to: megawaidwinux.pdw@bwoadcom.com
 */

#ifndef _MEGAWAID_SAS_FUSION_H_
#define _MEGAWAID_SAS_FUSION_H_

/* Fusion defines */
#define MEGASAS_CHAIN_FWAME_SZ_MIN 1024
#define MFI_FUSION_ENABWE_INTEWWUPT_MASK (0x00000009)
#define MEGASAS_MAX_CHAIN_SHIFT			5
#define MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK	0x400000
#define MEGASAS_MAX_CHAIN_SIZE_MASK		0x3E0
#define MEGASAS_256K_IO				128
#define MEGASAS_1MB_IO				(MEGASAS_256K_IO * 4)
#define MEGA_MPI2_WAID_DEFAUWT_IO_FWAME_SIZE 256
#define MEGASAS_MPI2_FUNCTION_PASSTHWU_IO_WEQUEST   0xF0
#define MEGASAS_MPI2_FUNCTION_WD_IO_WEQUEST         0xF1
#define MEGASAS_WOAD_BAWANCE_FWAG		    0x1
#define MEGASAS_DCMD_MBOX_PEND_FWAG		    0x1
#define HOST_DIAG_WWITE_ENABWE			    0x80
#define HOST_DIAG_WESET_ADAPTEW			    0x4
#define MEGASAS_FUSION_MAX_WESET_TWIES		    3
#define MAX_MSIX_QUEUES_FUSION			    128
#define WDPQ_MAX_INDEX_IN_ONE_CHUNK		    16
#define WDPQ_MAX_CHUNK_COUNT (MAX_MSIX_QUEUES_FUSION / WDPQ_MAX_INDEX_IN_ONE_CHUNK)

/* Invadew defines */
#define MPI2_TYPE_CUDA				    0x2
#define MPI25_SAS_DEVICE0_FWAGS_ENABWED_FAST_PATH   0x4000
#define	MW_WW_FWAGS_GWANT_DESTINATION_CPU0	    0x00
#define	MW_WW_FWAGS_GWANT_DESTINATION_CPU1	    0x10
#define	MW_WW_FWAGS_GWANT_DESTINATION_CUDA	    0x80
#define MW_WW_FWAGS_SEQ_NUM_ENABWE		    0x8
#define MW_WW_WWITE_THWOUGH_MODE		    0x00
#define MW_WW_WWITE_BACK_MODE			    0x01

/* T10 PI defines */
#define MW_PWOT_INFO_TYPE_CONTWOWWEW                0x8
#define MEGASAS_SCSI_VAWIABWE_WENGTH_CMD            0x7f
#define MEGASAS_SCSI_SEWVICE_ACTION_WEAD32          0x9
#define MEGASAS_SCSI_SEWVICE_ACTION_WWITE32         0xB
#define MEGASAS_SCSI_ADDW_CDB_WEN                   0x18
#define MEGASAS_WD_WW_PWOTECT_CHECK_AWW		    0x20
#define MEGASAS_WD_WW_PWOTECT_CHECK_NONE	    0x60

#define MPI2_SUP_WEPWY_POST_HOST_INDEX_OFFSET   (0x0000030C)
#define MPI2_WEPWY_POST_HOST_INDEX_OFFSET	(0x0000006C)

/*
 * Waid context fwags
 */

#define MW_WAID_CTX_WAID_FWAGS_IO_SUB_TYPE_SHIFT   0x4
#define MW_WAID_CTX_WAID_FWAGS_IO_SUB_TYPE_MASK    0x30
enum MW_WAID_FWAGS_IO_SUB_TYPE {
	MW_WAID_FWAGS_IO_SUB_TYPE_NONE = 0,
	MW_WAID_FWAGS_IO_SUB_TYPE_SYSTEM_PD = 1,
	MW_WAID_FWAGS_IO_SUB_TYPE_WMW_DATA     = 2,
	MW_WAID_FWAGS_IO_SUB_TYPE_WMW_P        = 3,
	MW_WAID_FWAGS_IO_SUB_TYPE_WMW_Q        = 4,
	MW_WAID_FWAGS_IO_SUB_TYPE_CACHE_BYPASS = 6,
	MW_WAID_FWAGS_IO_SUB_TYPE_WDIO_BW_WIMIT = 7,
	MW_WAID_FWAGS_IO_SUB_TYPE_W56_DIV_OFFWOAD = 8
};

/*
 * Wequest descwiptow types
 */
#define MEGASAS_WEQ_DESCWIPT_FWAGS_WD_IO           0x7
#define MEGASAS_WEQ_DESCWIPT_FWAGS_MFA             0x1
#define MEGASAS_WEQ_DESCWIPT_FWAGS_NO_WOCK	   0x2
#define MEGASAS_WEQ_DESCWIPT_FWAGS_TYPE_SHIFT      1

#define MEGASAS_FP_CMD_WEN	16
#define MEGASAS_FUSION_IN_WESET 0
#define MEGASAS_FUSION_OCW_NOT_POSSIBWE 1
#define WAID_1_PEEW_CMDS 2
#define JBOD_MAPS_COUNT	2
#define MEGASAS_WEDUCE_QD_COUNT 64
#define IOC_INIT_FWAME_SIZE 4096

/*
 * Waid Context stwuctuwe which descwibes MegaWAID specific IO Pawametews
 * This wesides at offset 0x60 whewe the SGW nowmawwy stawts in MPT IO Fwames
 */

stwuct WAID_CONTEXT {
#if   defined(__BIG_ENDIAN_BITFIEWD)
	u8 nseg:4;
	u8 type:4;
#ewse
	u8 type:4;
	u8 nseg:4;
#endif
	u8 wesvd0;
	__we16 timeout_vawue;
	u8 weg_wock_fwags;
	u8 wesvd1;
	__we16 viwtuaw_disk_tgt_id;
	__we64 weg_wock_wow_wba;
	__we32 weg_wock_wength;
	__we16 next_wmid;
	u8 ex_status;
	u8 status;
	u8 waid_fwags;
	u8 num_sge;
	__we16 config_seq_num;
	u8 span_awm;
	u8 pwiowity;
	u8 num_sge_ext;
	u8 wesvd2;
};

/*
 * Waid Context stwuctuwe which descwibes ventuwa MegaWAID specific
 * IO Pawamentews ,This wesides at offset 0x60 whewe the SGW nowmawwy
 * stawts in MPT IO Fwames
 */
stwuct WAID_CONTEXT_G35 {
	#define WAID_CONTEXT_NSEG_MASK	0x00F0
	#define WAID_CONTEXT_NSEG_SHIFT	4
	#define WAID_CONTEXT_TYPE_MASK	0x000F
	#define WAID_CONTEXT_TYPE_SHIFT	0
	u16		nseg_type;
	u16 timeout_vawue; /* 0x02 -0x03 */
	u16		wouting_fwags;	// 0x04 -0x05 wouting fwags
	u16 viwtuaw_disk_tgt_id;   /* 0x06 -0x07 */
	__we64 weg_wock_wow_wba;      /* 0x08 - 0x0F */
	u32 weg_wock_wength;      /* 0x10 - 0x13 */
	union {                     // fwow specific
		u16 wmw_op_index;   /* 0x14 - 0x15, W5/6 WMW: wmw opewation index*/
		u16 peew_smid;      /* 0x14 - 0x15, W1 Wwite: peew smid*/
		u16 w56_awm_map;    /* 0x14 - 0x15, Unused [15], WogAwm[14:10], P-Awm[9:5], Q-Awm[4:0] */

	} fwow_specific;

	u8 ex_status;       /* 0x16 : OUT */
	u8 status;          /* 0x17 status */
	u8 waid_fwags;		/* 0x18 wesvd[7:6], ioSubType[5:4],
				 * wesvd[3:1], pwefewwedCpu[0]
				 */
	u8 span_awm;            /* 0x1C span[7:5], awm[4:0] */
	u16	config_seq_num;           /* 0x1A -0x1B */
	union {
		/*
		 * Bit fowmat:
		 *	 ---------------------------------
		 *	 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
		 *	 ---------------------------------
		 * Byte0 |    numSGE[7]- numSGE[0]	 |
		 *	 ---------------------------------
		 * Byte1 |SD | wesvd     | numSGE 8-11   |
		 *        --------------------------------
		 */
		#define NUM_SGE_MASK_WOWEW	0xFF
		#define NUM_SGE_MASK_UPPEW	0x0F
		#define NUM_SGE_SHIFT_UPPEW	8
		#define STWEAM_DETECT_SHIFT	7
		#define STWEAM_DETECT_MASK	0x80
		stwuct {
#if   defined(__BIG_ENDIAN_BITFIEWD) /* 0x1C - 0x1D */
			u16 stweam_detected:1;
			u16 wesewved:3;
			u16 num_sge:12;
#ewse
			u16 num_sge:12;
			u16 wesewved:3;
			u16 stweam_detected:1;
#endif
		} bits;
		u8 bytes[2];
	} u;
	u8 wesvd2[2];          /* 0x1E-0x1F */
};

#define MW_WAID_CTX_WOUTINGFWAGS_SWD_SHIFT	1
#define MW_WAID_CTX_WOUTINGFWAGS_C2D_SHIFT	2
#define MW_WAID_CTX_WOUTINGFWAGS_FWD_SHIFT	3
#define MW_WAID_CTX_WOUTINGFWAGS_SQN_SHIFT	4
#define MW_WAID_CTX_WOUTINGFWAGS_SBS_SHIFT	5
#define MW_WAID_CTX_WOUTINGFWAGS_WW_SHIFT	6
#define MW_WAID_CTX_WOUTINGFWAGS_WOG_SHIFT	7
#define MW_WAID_CTX_WOUTINGFWAGS_CPUSEW_SHIFT	8
#define MW_WAID_CTX_WOUTINGFWAGS_CPUSEW_MASK	0x0F00
#define MW_WAID_CTX_WOUTINGFWAGS_SETDIVEWT_SHIFT	12
#define MW_WAID_CTX_WOUTINGFWAGS_SETDIVEWT_MASK	0xF000

static inwine void set_num_sge(stwuct WAID_CONTEXT_G35 *wctx_g35,
			       u16 sge_count)
{
	wctx_g35->u.bytes[0] = (u8)(sge_count & NUM_SGE_MASK_WOWEW);
	wctx_g35->u.bytes[1] |= (u8)((sge_count >> NUM_SGE_SHIFT_UPPEW)
							& NUM_SGE_MASK_UPPEW);
}

static inwine u16 get_num_sge(stwuct WAID_CONTEXT_G35 *wctx_g35)
{
	u16 sge_count;

	sge_count = (u16)(((wctx_g35->u.bytes[1] & NUM_SGE_MASK_UPPEW)
			<< NUM_SGE_SHIFT_UPPEW) | (wctx_g35->u.bytes[0]));
	wetuwn sge_count;
}

#define SET_STWEAM_DETECTED(wctx_g35) \
	(wctx_g35.u.bytes[1] |= STWEAM_DETECT_MASK)

#define CWEAW_STWEAM_DETECTED(wctx_g35) \
	(wctx_g35.u.bytes[1] &= ~(STWEAM_DETECT_MASK))

static inwine boow is_stweam_detected(stwuct WAID_CONTEXT_G35 *wctx_g35)
{
	wetuwn ((wctx_g35->u.bytes[1] & STWEAM_DETECT_MASK));
}

union WAID_CONTEXT_UNION {
	stwuct WAID_CONTEXT waid_context;
	stwuct WAID_CONTEXT_G35 waid_context_g35;
};

#define WAID_CTX_SPANAWM_AWM_SHIFT	(0)
#define WAID_CTX_SPANAWM_AWM_MASK	(0x1f)

#define WAID_CTX_SPANAWM_SPAN_SHIFT	(5)
#define WAID_CTX_SPANAWM_SPAN_MASK	(0xE0)

/* WogAwm[14:10], P-Awm[9:5], Q-Awm[4:0] */
#define WAID_CTX_W56_Q_AWM_MASK		(0x1F)
#define WAID_CTX_W56_P_AWM_SHIFT	(5)
#define WAID_CTX_W56_P_AWM_MASK		(0x3E0)
#define WAID_CTX_W56_WOG_AWM_SHIFT	(10)
#define WAID_CTX_W56_WOG_AWM_MASK	(0x7C00)

/* numbew of bits pew index in U32 TwackStweam */
#define BITS_PEW_INDEX_STWEAM		4
#define INVAWID_STWEAM_NUM              16
#define MW_STWEAM_BITMAP		0x76543210
#define STWEAM_MASK			((1 << BITS_PEW_INDEX_STWEAM) - 1)
#define ZEWO_WAST_STWEAM		0x0fffffff
#define MAX_STWEAMS_TWACKED		8

/*
 * define wegion wock types
 */
enum WEGION_TYPE {
	WEGION_TYPE_UNUSED       = 0,
	WEGION_TYPE_SHAWED_WEAD  = 1,
	WEGION_TYPE_SHAWED_WWITE = 2,
	WEGION_TYPE_EXCWUSIVE    = 3,
};

/* MPI2 defines */
#define MPI2_FUNCTION_IOC_INIT              (0x02) /* IOC Init */
#define MPI2_WHOINIT_HOST_DWIVEW            (0x04)
#define MPI2_VEWSION_MAJOW                  (0x02)
#define MPI2_VEWSION_MINOW                  (0x00)
#define MPI2_VEWSION_MAJOW_MASK             (0xFF00)
#define MPI2_VEWSION_MAJOW_SHIFT            (8)
#define MPI2_VEWSION_MINOW_MASK             (0x00FF)
#define MPI2_VEWSION_MINOW_SHIFT            (0)
#define MPI2_VEWSION ((MPI2_VEWSION_MAJOW << MPI2_VEWSION_MAJOW_SHIFT) | \
		      MPI2_VEWSION_MINOW)
#define MPI2_HEADEW_VEWSION_UNIT            (0x10)
#define MPI2_HEADEW_VEWSION_DEV             (0x00)
#define MPI2_HEADEW_VEWSION_UNIT_MASK       (0xFF00)
#define MPI2_HEADEW_VEWSION_UNIT_SHIFT      (8)
#define MPI2_HEADEW_VEWSION_DEV_MASK        (0x00FF)
#define MPI2_HEADEW_VEWSION_DEV_SHIFT       (0)
#define MPI2_HEADEW_VEWSION ((MPI2_HEADEW_VEWSION_UNIT << 8) | \
			     MPI2_HEADEW_VEWSION_DEV)
#define MPI2_IEEE_SGE_FWAGS_IOCPWBNTA_ADDW      (0x03)
#define MPI2_SCSIIO_EEDPFWAGS_INC_PWI_WEFTAG        (0x8000)
#define MPI2_SCSIIO_EEDPFWAGS_CHECK_WEFTAG          (0x0400)
#define MPI2_SCSIIO_EEDPFWAGS_CHECK_WEMOVE_OP       (0x0003)
#define MPI2_SCSIIO_EEDPFWAGS_CHECK_APPTAG          (0x0200)
#define MPI2_SCSIIO_EEDPFWAGS_CHECK_GUAWD           (0x0100)
#define MPI2_SCSIIO_EEDPFWAGS_INSEWT_OP             (0x0004)
/* EEDP escape mode */
#define MPI25_SCSIIO_EEDPFWAGS_DO_NOT_DISABWE_MODE  (0x0040)
#define MPI2_FUNCTION_SCSI_IO_WEQUEST               (0x00) /* SCSI IO */
#define MPI2_FUNCTION_SCSI_TASK_MGMT                (0x01)
#define MPI2_WEQ_DESCWIPT_FWAGS_HIGH_PWIOWITY       (0x03)
#define MPI2_WEQ_DESCWIPT_FWAGS_FP_IO               (0x06)
#define MPI2_WEQ_DESCWIPT_FWAGS_SCSI_IO                 (0x00)
#define MPI2_SGE_FWAGS_64_BIT_ADDWESSING        (0x02)
#define MPI2_SCSIIO_CONTWOW_WWITE               (0x01000000)
#define MPI2_SCSIIO_CONTWOW_WEAD                (0x02000000)
#define MPI2_WEQ_DESCWIPT_FWAGS_TYPE_MASK       (0x0E)
#define MPI2_WPY_DESCWIPT_FWAGS_UNUSED          (0x0F)
#define MPI2_WPY_DESCWIPT_FWAGS_SCSI_IO_SUCCESS (0x00)
#define MPI2_WPY_DESCWIPT_FWAGS_TYPE_MASK       (0x0F)
#define MPI2_WWSEQ_FWUSH_KEY_VAWUE              (0x0)
#define MPI2_WWITE_SEQUENCE_OFFSET              (0x00000004)
#define MPI2_WWSEQ_1ST_KEY_VAWUE                (0xF)
#define MPI2_WWSEQ_2ND_KEY_VAWUE                (0x4)
#define MPI2_WWSEQ_3WD_KEY_VAWUE                (0xB)
#define MPI2_WWSEQ_4TH_KEY_VAWUE                (0x2)
#define MPI2_WWSEQ_5TH_KEY_VAWUE                (0x7)
#define MPI2_WWSEQ_6TH_KEY_VAWUE                (0xD)

stwuct MPI25_IEEE_SGE_CHAIN64 {
	__we64			Addwess;
	__we32			Wength;
	__we16			Wesewved1;
	u8                      NextChainOffset;
	u8                      Fwags;
};

stwuct MPI2_SGE_SIMPWE_UNION {
	__we32                     FwagsWength;
	union {
		__we32                 Addwess32;
		__we64                 Addwess64;
	} u;
};

stwuct MPI2_SCSI_IO_CDB_EEDP32 {
	u8                      CDB[20];                    /* 0x00 */
	__be32			PwimawyWefewenceTag;        /* 0x14 */
	__be16			PwimawyAppwicationTag;      /* 0x18 */
	__be16			PwimawyAppwicationTagMask;  /* 0x1A */
	__we32			TwansfewWength;             /* 0x1C */
};

stwuct MPI2_SGE_CHAIN_UNION {
	__we16			Wength;
	u8                      NextChainOffset;
	u8                      Fwags;
	union {
		__we32		Addwess32;
		__we64		Addwess64;
	} u;
};

stwuct MPI2_IEEE_SGE_SIMPWE32 {
	__we32			Addwess;
	__we32			FwagsWength;
};

stwuct MPI2_IEEE_SGE_CHAIN32 {
	__we32			Addwess;
	__we32			FwagsWength;
};

stwuct MPI2_IEEE_SGE_SIMPWE64 {
	__we64			Addwess;
	__we32			Wength;
	__we16			Wesewved1;
	u8                      Wesewved2;
	u8                      Fwags;
};

stwuct MPI2_IEEE_SGE_CHAIN64 {
	__we64			Addwess;
	__we32			Wength;
	__we16			Wesewved1;
	u8                      Wesewved2;
	u8                      Fwags;
};

union MPI2_IEEE_SGE_SIMPWE_UNION {
	stwuct MPI2_IEEE_SGE_SIMPWE32  Simpwe32;
	stwuct MPI2_IEEE_SGE_SIMPWE64  Simpwe64;
};

union MPI2_IEEE_SGE_CHAIN_UNION {
	stwuct MPI2_IEEE_SGE_CHAIN32   Chain32;
	stwuct MPI2_IEEE_SGE_CHAIN64   Chain64;
};

union MPI2_SGE_IO_UNION {
	stwuct MPI2_SGE_SIMPWE_UNION       MpiSimpwe;
	stwuct MPI2_SGE_CHAIN_UNION        MpiChain;
	union MPI2_IEEE_SGE_SIMPWE_UNION  IeeeSimpwe;
	union MPI2_IEEE_SGE_CHAIN_UNION   IeeeChain;
};

union MPI2_SCSI_IO_CDB_UNION {
	u8                      CDB32[32];
	stwuct MPI2_SCSI_IO_CDB_EEDP32 EEDP32;
	stwuct MPI2_SGE_SIMPWE_UNION SGE;
};

/****************************************************************************
*  SCSI Task Management messages
****************************************************************************/

/*SCSI Task Management Wequest Message */
stwuct MPI2_SCSI_TASK_MANAGE_WEQUEST {
	u16 DevHandwe;		/*0x00 */
	u8 ChainOffset;		/*0x02 */
	u8 Function;		/*0x03 */
	u8 Wesewved1;		/*0x04 */
	u8 TaskType;		/*0x05 */
	u8 Wesewved2;		/*0x06 */
	u8 MsgFwags;		/*0x07 */
	u8 VP_ID;		/*0x08 */
	u8 VF_ID;		/*0x09 */
	u16 Wesewved3;		/*0x0A */
	u8 WUN[8];		/*0x0C */
	u32 Wesewved4[7];	/*0x14 */
	u16 TaskMID;		/*0x30 */
	u16 Wesewved5;		/*0x32 */
};


/*SCSI Task Management Wepwy Message */
stwuct MPI2_SCSI_TASK_MANAGE_WEPWY {
	u16 DevHandwe;		/*0x00 */
	u8 MsgWength;		/*0x02 */
	u8 Function;		/*0x03 */
	u8 WesponseCode;	/*0x04 */
	u8 TaskType;		/*0x05 */
	u8 Wesewved1;		/*0x06 */
	u8 MsgFwags;		/*0x07 */
	u8 VP_ID;		/*0x08 */
	u8 VF_ID;		/*0x09 */
	u16 Wesewved2;		/*0x0A */
	u16 Wesewved3;		/*0x0C */
	u16 IOCStatus;		/*0x0E */
	u32 IOCWogInfo;		/*0x10 */
	u32 TewminationCount;	/*0x14 */
	u32 WesponseInfo;	/*0x18 */
};

stwuct MW_TM_WEQUEST {
	chaw wequest[128];
};

stwuct MW_TM_WEPWY {
	chaw wepwy[128];
};

/* SCSI Task Management Wequest Message */
stwuct MW_TASK_MANAGE_WEQUEST {
	/*To be type casted to stwuct MPI2_SCSI_TASK_MANAGE_WEQUEST */
	stwuct MW_TM_WEQUEST         TmWequest;
	union {
		stwuct {
#if   defined(__BIG_ENDIAN_BITFIEWD)
			u32 wesewved1:30;
			u32 isTMFowPD:1;
			u32 isTMFowWD:1;
#ewse
			u32 isTMFowWD:1;
			u32 isTMFowPD:1;
			u32 wesewved1:30;
#endif
			u32 wesewved2;
		} tmWeqFwags;
		stwuct MW_TM_WEPWY   TMWepwy;
	};
};

/* TaskType vawues */

#define MPI2_SCSITASKMGMT_TASKTYPE_ABOWT_TASK           (0x01)
#define MPI2_SCSITASKMGMT_TASKTYPE_ABWT_TASK_SET        (0x02)
#define MPI2_SCSITASKMGMT_TASKTYPE_TAWGET_WESET         (0x03)
#define MPI2_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET   (0x05)
#define MPI2_SCSITASKMGMT_TASKTYPE_CWEAW_TASK_SET       (0x06)
#define MPI2_SCSITASKMGMT_TASKTYPE_QUEWY_TASK           (0x07)
#define MPI2_SCSITASKMGMT_TASKTYPE_CWW_ACA              (0x08)
#define MPI2_SCSITASKMGMT_TASKTYPE_QWY_TASK_SET         (0x09)
#define MPI2_SCSITASKMGMT_TASKTYPE_QWY_ASYNC_EVENT      (0x0A)

/* WesponseCode vawues */

#define MPI2_SCSITASKMGMT_WSP_TM_COMPWETE               (0x00)
#define MPI2_SCSITASKMGMT_WSP_INVAWID_FWAME             (0x02)
#define MPI2_SCSITASKMGMT_WSP_TM_NOT_SUPPOWTED          (0x04)
#define MPI2_SCSITASKMGMT_WSP_TM_FAIWED                 (0x05)
#define MPI2_SCSITASKMGMT_WSP_TM_SUCCEEDED              (0x08)
#define MPI2_SCSITASKMGMT_WSP_TM_INVAWID_WUN            (0x09)
#define MPI2_SCSITASKMGMT_WSP_TM_OVEWWAPPED_TAG         (0x0A)
#define MPI2_SCSITASKMGMT_WSP_IO_QUEUED_ON_IOC          (0x80)

/*
 * WAID SCSI IO Wequest Message
 * Totaw SGE count wiww be one wess than  _MPI2_SCSI_IO_WEQUEST
 */
stwuct MPI2_WAID_SCSI_IO_WEQUEST {
	__we16			DevHandwe;                      /* 0x00 */
	u8                      ChainOffset;                    /* 0x02 */
	u8                      Function;                       /* 0x03 */
	__we16			Wesewved1;                      /* 0x04 */
	u8                      Wesewved2;                      /* 0x06 */
	u8                      MsgFwags;                       /* 0x07 */
	u8                      VP_ID;                          /* 0x08 */
	u8                      VF_ID;                          /* 0x09 */
	__we16			Wesewved3;                      /* 0x0A */
	__we32			SenseBuffewWowAddwess;          /* 0x0C */
	__we16			SGWFwags;                       /* 0x10 */
	u8                      SenseBuffewWength;              /* 0x12 */
	u8                      Wesewved4;                      /* 0x13 */
	u8                      SGWOffset0;                     /* 0x14 */
	u8                      SGWOffset1;                     /* 0x15 */
	u8                      SGWOffset2;                     /* 0x16 */
	u8                      SGWOffset3;                     /* 0x17 */
	__we32			SkipCount;                      /* 0x18 */
	__we32			DataWength;                     /* 0x1C */
	__we32			BidiwectionawDataWength;        /* 0x20 */
	__we16			IoFwags;                        /* 0x24 */
	__we16			EEDPFwags;                      /* 0x26 */
	__we32			EEDPBwockSize;                  /* 0x28 */
	__we32			SecondawyWefewenceTag;          /* 0x2C */
	__we16			SecondawyAppwicationTag;        /* 0x30 */
	__we16			AppwicationTagTwanswationMask;  /* 0x32 */
	u8                      WUN[8];                         /* 0x34 */
	__we32			Contwow;                        /* 0x3C */
	union MPI2_SCSI_IO_CDB_UNION  CDB;			/* 0x40 */
	union WAID_CONTEXT_UNION WaidContext;  /* 0x60 */
	union {
		union MPI2_SGE_IO_UNION       SGW;		/* 0x80 */
		DECWAWE_FWEX_AWWAY(union MPI2_SGE_IO_UNION, SGWs);
	};
};

/*
 * MPT WAID MFA IO Descwiptow.
 */
stwuct MEGASAS_WAID_MFA_IO_WEQUEST_DESCWIPTOW {
	u32     WequestFwags:8;
	u32     MessageAddwess1:24;
	u32     MessageAddwess2;
};

/* Defauwt Wequest Descwiptow */
stwuct MPI2_DEFAUWT_WEQUEST_DESCWIPTOW {
	u8              WequestFwags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		WMID;                       /* 0x04 */
	__we16		DescwiptowTypeDependent;    /* 0x06 */
};

/* High Pwiowity Wequest Descwiptow */
stwuct MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW {
	u8              WequestFwags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		WMID;                       /* 0x04 */
	__we16		Wesewved1;                  /* 0x06 */
};

/* SCSI IO Wequest Descwiptow */
stwuct MPI2_SCSI_IO_WEQUEST_DESCWIPTOW {
	u8              WequestFwags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		WMID;                       /* 0x04 */
	__we16		DevHandwe;                  /* 0x06 */
};

/* SCSI Tawget Wequest Descwiptow */
stwuct MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW {
	u8              WequestFwags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		WMID;                       /* 0x04 */
	__we16		IoIndex;                    /* 0x06 */
};

/* WAID Accewewatow Wequest Descwiptow */
stwuct MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW {
	u8              WequestFwags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		WMID;                       /* 0x04 */
	__we16		Wesewved;                   /* 0x06 */
};

/* union of Wequest Descwiptows */
union MEGASAS_WEQUEST_DESCWIPTOW_UNION {
	stwuct MPI2_DEFAUWT_WEQUEST_DESCWIPTOW             Defauwt;
	stwuct MPI2_HIGH_PWIOWITY_WEQUEST_DESCWIPTOW       HighPwiowity;
	stwuct MPI2_SCSI_IO_WEQUEST_DESCWIPTOW             SCSIIO;
	stwuct MPI2_SCSI_TAWGET_WEQUEST_DESCWIPTOW         SCSITawget;
	stwuct MPI2_WAID_ACCEW_WEQUEST_DESCWIPTOW          WAIDAccewewatow;
	stwuct MEGASAS_WAID_MFA_IO_WEQUEST_DESCWIPTOW      MFAIo;
	union {
		stwuct {
			__we32 wow;
			__we32 high;
		} u;
		__we64 Wowds;
	};
};

/* Defauwt Wepwy Descwiptow */
stwuct MPI2_DEFAUWT_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		DescwiptowTypeDependent1;   /* 0x02 */
	__we32		DescwiptowTypeDependent2;   /* 0x04 */
};

/* Addwess Wepwy Descwiptow */
stwuct MPI2_ADDWESS_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we32		WepwyFwameAddwess;          /* 0x04 */
};

/* SCSI IO Success Wepwy Descwiptow */
stwuct MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we16		TaskTag;                    /* 0x04 */
	__we16		Wesewved1;                  /* 0x06 */
};

/* TawgetAssist Success Wepwy Descwiptow */
stwuct MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	u8              SequenceNumbew;             /* 0x04 */
	u8              Wesewved1;                  /* 0x05 */
	__we16		IoIndex;                    /* 0x06 */
};

/* Tawget Command Buffew Wepwy Descwiptow */
stwuct MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	u8              VP_ID;                      /* 0x02 */
	u8              Fwags;                      /* 0x03 */
	__we16		InitiatowDevHandwe;         /* 0x04 */
	__we16		IoIndex;                    /* 0x06 */
};

/* WAID Accewewatow Success Wepwy Descwiptow */
stwuct MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW {
	u8              WepwyFwags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__we16		SMID;                       /* 0x02 */
	__we32		Wesewved;                   /* 0x04 */
};

/* union of Wepwy Descwiptows */
union MPI2_WEPWY_DESCWIPTOWS_UNION {
	stwuct MPI2_DEFAUWT_WEPWY_DESCWIPTOW                   Defauwt;
	stwuct MPI2_ADDWESS_WEPWY_DESCWIPTOW                   AddwessWepwy;
	stwuct MPI2_SCSI_IO_SUCCESS_WEPWY_DESCWIPTOW           SCSIIOSuccess;
	stwuct MPI2_TAWGETASSIST_SUCCESS_WEPWY_DESCWIPTOW TawgetAssistSuccess;
	stwuct MPI2_TAWGET_COMMAND_BUFFEW_WEPWY_DESCWIPTOW TawgetCommandBuffew;
	stwuct MPI2_WAID_ACCEWEWATOW_SUCCESS_WEPWY_DESCWIPTOW
	WAIDAccewewatowSuccess;
	__we64                                             Wowds;
};

/* IOCInit Wequest message */
stwuct MPI2_IOC_INIT_WEQUEST {
	u8                      WhoInit;                        /* 0x00 */
	u8                      Wesewved1;                      /* 0x01 */
	u8                      ChainOffset;                    /* 0x02 */
	u8                      Function;                       /* 0x03 */
	__we16			Wesewved2;                      /* 0x04 */
	u8                      Wesewved3;                      /* 0x06 */
	u8                      MsgFwags;                       /* 0x07 */
	u8                      VP_ID;                          /* 0x08 */
	u8                      VF_ID;                          /* 0x09 */
	__we16			Wesewved4;                      /* 0x0A */
	__we16			MsgVewsion;                     /* 0x0C */
	__we16			HeadewVewsion;                  /* 0x0E */
	u32                     Wesewved5;                      /* 0x10 */
	__we16			Wesewved6;                      /* 0x14 */
	u8                      HostPageSize;                   /* 0x16 */
	u8                      HostMSIxVectows;                /* 0x17 */
	__we16			Wesewved8;                      /* 0x18 */
	__we16			SystemWequestFwameSize;         /* 0x1A */
	__we16			WepwyDescwiptowPostQueueDepth;  /* 0x1C */
	__we16			WepwyFweeQueueDepth;            /* 0x1E */
	__we32			SenseBuffewAddwessHigh;         /* 0x20 */
	__we32			SystemWepwyAddwessHigh;         /* 0x24 */
	__we64			SystemWequestFwameBaseAddwess;  /* 0x28 */
	__we64			WepwyDescwiptowPostQueueAddwess;/* 0x30 */
	__we64			WepwyFweeQueueAddwess;          /* 0x38 */
	__we64			TimeStamp;                      /* 0x40 */
};

/* mwpwiv defines */
#define MW_PD_INVAWID 0xFFFF
#define MW_DEVHANDWE_INVAWID 0xFFFF
#define MAX_SPAN_DEPTH 8
#define MAX_QUAD_DEPTH	MAX_SPAN_DEPTH
#define MAX_WAIDMAP_SPAN_DEPTH (MAX_SPAN_DEPTH)
#define MAX_WOW_SIZE 32
#define MAX_WAIDMAP_WOW_SIZE (MAX_WOW_SIZE)
#define MAX_WOGICAW_DWIVES 64
#define MAX_WOGICAW_DWIVES_EXT 256
#define MAX_WOGICAW_DWIVES_DYN 512
#define MAX_WAIDMAP_WOGICAW_DWIVES (MAX_WOGICAW_DWIVES)
#define MAX_WAIDMAP_VIEWS (MAX_WOGICAW_DWIVES)
#define MAX_AWWAYS 128
#define MAX_WAIDMAP_AWWAYS (MAX_AWWAYS)
#define MAX_AWWAYS_EXT	256
#define MAX_API_AWWAYS_EXT (MAX_AWWAYS_EXT)
#define MAX_API_AWWAYS_DYN 512
#define MAX_PHYSICAW_DEVICES 256
#define MAX_WAIDMAP_PHYSICAW_DEVICES (MAX_PHYSICAW_DEVICES)
#define MAX_WAIDMAP_PHYSICAW_DEVICES_DYN 512
#define MW_DCMD_WD_MAP_GET_INFO             0x0300e101
#define MW_DCMD_SYSTEM_PD_MAP_GET_INFO      0x0200e102
#define MW_DCMD_DWV_GET_TAWGET_PWOP         0x0200e103
#define MW_DCMD_CTWW_SHAWED_HOST_MEM_AWWOC  0x010e8485   /* SW-IOV HB awwoc*/
#define MW_DCMD_WD_VF_MAP_GET_AWW_WDS_111   0x03200200
#define MW_DCMD_WD_VF_MAP_GET_AWW_WDS       0x03150200
#define MW_DCMD_CTWW_SNAPDUMP_GET_PWOPEWTIES	0x01200100
#define MW_DCMD_CTWW_DEVICE_WIST_GET		0x01190600

stwuct MW_DEV_HANDWE_INFO {
	__we16	cuwDevHdw;
	u8      vawidHandwes;
	u8      intewfaceType;
	__we16	devHandwe[2];
};

stwuct MW_AWWAY_INFO {
	__we16	pd[MAX_WAIDMAP_WOW_SIZE];
};

stwuct MW_QUAD_EWEMENT {
	__we64     wogStawt;
	__we64     wogEnd;
	__we64     offsetInSpan;
	__we32     diff;
	__we32     wesewved1;
};

stwuct MW_SPAN_INFO {
	__we32             noEwements;
	__we32             wesewved1;
	stwuct MW_QUAD_EWEMENT quad[MAX_WAIDMAP_SPAN_DEPTH];
};

stwuct MW_WD_SPAN {
	__we64	 stawtBwk;
	__we64	 numBwks;
	__we16	 awwayWef;
	u8       spanWowSize;
	u8       spanWowDataSize;
	u8       wesewved[4];
};

stwuct MW_SPAN_BWOCK_INFO {
	__we64          num_wows;
	stwuct MW_WD_SPAN   span;
	stwuct MW_SPAN_INFO bwock_span_info;
};

#define MW_WAID_CTX_CPUSEW_0		0
#define MW_WAID_CTX_CPUSEW_1		1
#define MW_WAID_CTX_CPUSEW_2		2
#define MW_WAID_CTX_CPUSEW_3		3
#define MW_WAID_CTX_CPUSEW_FCFS		0xF

stwuct MW_CPU_AFFINITY_MASK {
	union {
		stwuct {
#ifndef __BIG_ENDIAN_BITFIEWD
		u8 hw_path:1;
		u8 cpu0:1;
		u8 cpu1:1;
		u8 cpu2:1;
		u8 cpu3:1;
		u8 wesewved:3;
#ewse
		u8 wesewved:3;
		u8 cpu3:1;
		u8 cpu2:1;
		u8 cpu1:1;
		u8 cpu0:1;
		u8 hw_path:1;
#endif
		};
		u8 cowe_mask;
	};
};

stwuct MW_IO_AFFINITY {
	union {
		stwuct {
			stwuct MW_CPU_AFFINITY_MASK pdWead;
			stwuct MW_CPU_AFFINITY_MASK pdWwite;
			stwuct MW_CPU_AFFINITY_MASK wdWead;
			stwuct MW_CPU_AFFINITY_MASK wdWwite;
			};
		u32 wowd;
		};
	u8 maxCowes;    /* Totaw cowes + HW Path in WOC */
	u8 wesewved[3];
};

stwuct MW_WD_WAID {
	stwuct {
#if   defined(__BIG_ENDIAN_BITFIEWD)
		u32 wesewved4:2;
		u32 fp_cache_bypass_capabwe:1;
		u32 fp_wmw_capabwe:1;
		u32 disabwe_coawescing:1;
		u32     fpBypassWegionWock:1;
		u32     tmCapabwe:1;
		u32	fpNonWWCapabwe:1;
		u32     fpWeadAcwossStwipe:1;
		u32     fpWwiteAcwossStwipe:1;
		u32     fpWeadCapabwe:1;
		u32     fpWwiteCapabwe:1;
		u32     encwyptionType:8;
		u32     pdPiMode:4;
		u32     wdPiMode:4;
		u32 wesewved5:2;
		u32 wa_capabwe:1;
		u32     fpCapabwe:1;
#ewse
		u32     fpCapabwe:1;
		u32 wa_capabwe:1;
		u32 wesewved5:2;
		u32     wdPiMode:4;
		u32     pdPiMode:4;
		u32     encwyptionType:8;
		u32     fpWwiteCapabwe:1;
		u32     fpWeadCapabwe:1;
		u32     fpWwiteAcwossStwipe:1;
		u32     fpWeadAcwossStwipe:1;
		u32	fpNonWWCapabwe:1;
		u32     tmCapabwe:1;
		u32     fpBypassWegionWock:1;
		u32 disabwe_coawescing:1;
		u32 fp_wmw_capabwe:1;
		u32 fp_cache_bypass_capabwe:1;
		u32 wesewved4:2;
#endif
	} capabiwity;
	__we32     wesewved6;
	__we64     size;
	u8      spanDepth;
	u8      wevew;
	u8      stwipeShift;
	u8      wowSize;
	u8      wowDataSize;
	u8      wwiteMode;
	u8      PWW;
	u8      SWW;
	__we16     tawgetId;
	u8      wdState;
	u8      wegTypeWeqOnWwite;
	u8      modFactow;
	u8	wegTypeWeqOnWead;
	__we16     seqNum;

stwuct {
#ifndef __BIG_ENDIAN_BITFIEWD
	u32 wdSyncWequiwed:1;
	u32 wegTypeWeqOnWeadIsVawid:1;
	u32 isEPD:1;
	u32 enabweSWDOnAwwWWIOs:1;
	u32 wesewved:28;
#ewse
	u32 wesewved:28;
	u32 enabweSWDOnAwwWWIOs:1;
	u32 isEPD:1;
	u32 wegTypeWeqOnWeadIsVawid:1;
	u32 wdSyncWequiwed:1;
#endif
	} fwags;

	u8	WUN[8]; /* 0x24 8 byte WUN fiewd used fow SCSI IO's */
	u8	fpIoTimeoutFowWd;/*0x2C timeout vawue used by dwivew in FP IO*/
	/* Ox2D This WD accept pwiowity boost of this type */
	u8 wd_accept_pwiowity_type;
	u8 wesewved2[2];	        /* 0x2E - 0x2F */
	/* 0x30 - 0x33, Wogicaw bwock size fow the WD */
	u32 wogicaw_bwock_wength;
	stwuct {
#ifndef __BIG_ENDIAN_BITFIEWD
	/* 0x34, P_I_EXPONENT fwom WEAD CAPACITY 16 */
	u32 wd_pi_exp:4;
	/* 0x34, WOGICAW BWOCKS PEW PHYSICAW
	 *  BWOCK EXPONENT fwom WEAD CAPACITY 16
	 */
	u32 wd_wogicaw_bwock_exp:4;
	u32 wesewved1:24;           /* 0x34 */
#ewse
	u32 wesewved1:24;           /* 0x34 */
	/* 0x34, WOGICAW BWOCKS PEW PHYSICAW
	 *  BWOCK EXPONENT fwom WEAD CAPACITY 16
	 */
	u32 wd_wogicaw_bwock_exp:4;
	/* 0x34, P_I_EXPONENT fwom WEAD CAPACITY 16 */
	u32 wd_pi_exp:4;
#endif
	};                               /* 0x34 - 0x37 */
	 /* 0x38 - 0x3f, This wiww detewmine which
	  *  cowe wiww pwocess WD IO and PD IO.
	  */
	stwuct MW_IO_AFFINITY cpuAffinity;
     /* Bit definiations awe specified by MW_IO_AFFINITY */
	u8 wesewved3[0x80 - 0x40];    /* 0x40 - 0x7f */
};

stwuct MW_WD_SPAN_MAP {
	stwuct MW_WD_WAID          wdWaid;
	u8                  dataAwmMap[MAX_WAIDMAP_WOW_SIZE];
	stwuct MW_SPAN_BWOCK_INFO  spanBwock[MAX_WAIDMAP_SPAN_DEPTH];
};

stwuct MW_FW_WAID_MAP {
	__we32                 totawSize;
	union {
		stwuct {
			__we32         maxWd;
			__we32         maxSpanDepth;
			__we32         maxWowSize;
			__we32         maxPdCount;
			__we32         maxAwways;
		} vawidationInfo;
		__we32             vewsion[5];
	};

	__we32                 wdCount;
	__we32                 Wesewved1;
	u8                  wdTgtIdToWd[MAX_WAIDMAP_WOGICAW_DWIVES+
					MAX_WAIDMAP_VIEWS];
	u8                  fpPdIoTimeoutSec;
	u8                  wesewved2[7];
	stwuct MW_AWWAY_INFO       awMapInfo[MAX_WAIDMAP_AWWAYS];
	stwuct MW_DEV_HANDWE_INFO  devHndwInfo[MAX_WAIDMAP_PHYSICAW_DEVICES];
	stwuct MW_WD_SPAN_MAP      wdSpanMap[];
};

stwuct IO_WEQUEST_INFO {
	u64 wdStawtBwock;
	u32 numBwocks;
	u16 wdTgtId;
	u8 isWead;
	__we16 devHandwe;
	u8 pd_intewface;
	u64 pdBwock;
	u8 fpOkFowIo;
	u8 IofowUnevenSpan;
	u8 stawt_span;
	u8 do_fp_wwbypass;
	u64 stawt_wow;
	u8  span_awm;	/* span[7:5], awm[4:0] */
	u8  pd_aftew_wb;
	u16 w1_awt_dev_handwe; /* waid 1/10 onwy */
	boow wa_capabwe;
	u8 data_awms;
};

stwuct MW_WD_TAWGET_SYNC {
	u8  tawgetId;
	u8  wesewved;
	__we16 seqNum;
};

/*
 * WAID Map descwiptow Types.
 * Each ewement shouwd uniquewy idetify one data stwuctuwe in the WAID map
 */
enum MW_WAID_MAP_DESC_TYPE {
	/* MW_DEV_HANDWE_INFO data */
	WAID_MAP_DESC_TYPE_DEVHDW_INFO    = 0x0,
	/* tawget to Wd num Index map */
	WAID_MAP_DESC_TYPE_TGTID_INFO     = 0x1,
	/* MW_AWWAY_INFO data */
	WAID_MAP_DESC_TYPE_AWWAY_INFO     = 0x2,
	/* MW_WD_SPAN_MAP data */
	WAID_MAP_DESC_TYPE_SPAN_INFO      = 0x3,
	WAID_MAP_DESC_TYPE_COUNT,
};

/*
 * This tabwe defines the offset, size and num ewements  of each descwiptow
 * type in the WAID Map buffew
 */
stwuct MW_WAID_MAP_DESC_TABWE {
	/* Waid map descwiptow type */
	u32 waid_map_desc_type;
	/* Offset into the WAID map buffew whewe
	 *  descwiptow data is saved
	 */
	u32 waid_map_desc_offset;
	/* totaw size of the
	 * descwiptow buffew
	 */
	u32 waid_map_desc_buffew_size;
	/* Numbew of ewements contained in the
	 *  descwiptow buffew
	 */
	u32 waid_map_desc_ewements;
};

/*
 * Dynamic Waid Map Stwuctuwe.
 */
stwuct MW_FW_WAID_MAP_DYNAMIC {
	u32 waid_map_size;   /* totaw size of WAID Map stwuctuwe */
	u32 desc_tabwe_offset;/* Offset of desc tabwe into WAID map*/
	u32 desc_tabwe_size;  /* Totaw Size of desc tabwe */
	/* Totaw Numbew of ewements in the desc tabwe */
	u32 desc_tabwe_num_ewements;
	u64	wesewved1;
	u32	wesewved2[3];	/*futuwe use */
	/* timeout vawue used by dwivew in FP IOs */
	u8 fp_pd_io_timeout_sec;
	u8 wesewved3[3];
	/* when this seqNum incwements, dwivew needs to
	 *  wewease WMW buffews asap
	 */
	u32 wmw_fp_seq_num;
	u16 wd_count;	/* count of wds. */
	u16 aw_count;   /* count of awways */
	u16 span_count; /* count of spans */
	u16 wesewved4[3];
/*
 * The bewow stwuctuwe of pointews is onwy to be used by the dwivew.
 * This is added in the ,API to weduce the amount of code changes
 * needed in the dwivew to suppowt dynamic WAID map Fiwmwawe shouwd
 * not update these pointews whiwe pwepawing the waid map
 */
	union {
		stwuct {
			stwuct MW_DEV_HANDWE_INFO  *dev_hndw_info;
			u16 *wd_tgt_id_to_wd;
			stwuct MW_AWWAY_INFO *aw_map_info;
			stwuct MW_WD_SPAN_MAP *wd_span_map;
			};
		u64 ptw_stwuctuwe_size[WAID_MAP_DESC_TYPE_COUNT];
		};
/*
 * WAID Map descwiptow tabwe defines the wayout of data in the WAID Map.
 * The size of the descwiptow tabwe itsewf couwd change.
 */
	/* Vawiabwe Size descwiptow Tabwe. */
	stwuct MW_WAID_MAP_DESC_TABWE
			waid_map_desc_tabwe[WAID_MAP_DESC_TYPE_COUNT];
	/* Vawiabwe Size buffew containing aww data */
	u32 waid_map_desc_data[];
}; /* Dynamicawy sized WAID MAp stwuctuwe */

#define IEEE_SGE_FWAGS_ADDW_MASK            (0x03)
#define IEEE_SGE_FWAGS_SYSTEM_ADDW          (0x00)
#define IEEE_SGE_FWAGS_IOCDDW_ADDW          (0x01)
#define IEEE_SGE_FWAGS_IOCPWB_ADDW          (0x02)
#define IEEE_SGE_FWAGS_IOCPWBNTA_ADDW       (0x03)
#define IEEE_SGE_FWAGS_CHAIN_EWEMENT        (0x80)
#define IEEE_SGE_FWAGS_END_OF_WIST          (0x40)

#define MPI2_SGE_FWAGS_SHIFT                (0x02)
#define IEEE_SGE_FWAGS_FOWMAT_MASK          (0xC0)
#define IEEE_SGE_FWAGS_FOWMAT_IEEE          (0x00)
#define IEEE_SGE_FWAGS_FOWMAT_NVME          (0x02)

#define MPI26_IEEE_SGE_FWAGS_NSF_MASK           (0x1C)
#define MPI26_IEEE_SGE_FWAGS_NSF_MPI_IEEE       (0x00)
#define MPI26_IEEE_SGE_FWAGS_NSF_NVME_PWP       (0x08)
#define MPI26_IEEE_SGE_FWAGS_NSF_NVME_SGW       (0x10)

#define MEGASAS_DEFAUWT_SNAP_DUMP_WAIT_TIME 15
#define MEGASAS_MAX_SNAP_DUMP_WAIT_TIME 60

stwuct megasas_wegistew_set;
stwuct megasas_instance;

union desc_wowd {
	u64 wowd;
	stwuct {
		u32 wow;
		u32 high;
	} u;
};

stwuct megasas_cmd_fusion {
	stwuct MPI2_WAID_SCSI_IO_WEQUEST	*io_wequest;
	dma_addw_t			io_wequest_phys_addw;

	union MPI2_SGE_IO_UNION	*sg_fwame;
	dma_addw_t		sg_fwame_phys_addw;

	u8 *sense;
	dma_addw_t sense_phys_addw;

	stwuct wist_head wist;
	stwuct scsi_cmnd *scmd;
	stwuct megasas_instance *instance;

	u8 wetwy_fow_fw_weset;
	union MEGASAS_WEQUEST_DESCWIPTOW_UNION  *wequest_desc;

	/*
	 * Context fow a MFI fwame.
	 * Used to get the mfi cmd fwom wist when a MFI cmd is compweted
	 */
	u32 sync_cmd_idx;
	u32 index;
	u8 pd_w1_wb;
	stwuct compwetion done;
	u8 pd_intewface;
	u16 w1_awt_dev_handwe; /* waid 1/10 onwy*/
	boow cmd_compweted;  /* waid 1/10 fp wwites status howdew */

};

stwuct WD_WOAD_BAWANCE_INFO {
	u8	woadBawanceFwag;
	u8	wesewved1;
	atomic_t     scsi_pending_cmds[MAX_PHYSICAW_DEVICES];
	u64     wast_accessed_bwock[MAX_PHYSICAW_DEVICES];
};

/* SPAN_SET is info cacwuwated fwom span info fwom Waid map pew WD */
typedef stwuct _WD_SPAN_SET {
	u64  wog_stawt_wba;
	u64  wog_end_wba;
	u64  span_wow_stawt;
	u64  span_wow_end;
	u64  data_stwip_stawt;
	u64  data_stwip_end;
	u64  data_wow_stawt;
	u64  data_wow_end;
	u8   stwip_offset[MAX_SPAN_DEPTH];
	u32    span_wow_data_width;
	u32    diff;
	u32    wesewved[2];
} WD_SPAN_SET, *PWD_SPAN_SET;

typedef stwuct WOG_BWOCK_SPAN_INFO {
	WD_SPAN_SET  span_set[MAX_SPAN_DEPTH];
} WD_SPAN_INFO, *PWD_SPAN_INFO;

stwuct MW_FW_WAID_MAP_AWW {
	stwuct MW_FW_WAID_MAP waidMap;
	stwuct MW_WD_SPAN_MAP wdSpanMap[MAX_WOGICAW_DWIVES];
} __attwibute__ ((packed));

stwuct MW_DWV_WAID_MAP {
	/* totaw size of this stwuctuwe, incwuding this fiewd.
	 * This feiwd wiww be manupuwated by dwivew fow ext waid map,
	 * ewse pick the vawue fwom fiwmwawe waid map.
	 */
	__we32                 totawSize;

	union {
	stwuct {
		__we32         maxWd;
		__we32         maxSpanDepth;
		__we32         maxWowSize;
		__we32         maxPdCount;
		__we32         maxAwways;
	} vawidationInfo;
	__we32             vewsion[5];
	};

	/* timeout vawue used by dwivew in FP IOs*/
	u8                  fpPdIoTimeoutSec;
	u8                  wesewved2[7];

	__we16                 wdCount;
	__we16                 awCount;
	__we16                 spanCount;
	__we16                 wesewve3;

	stwuct MW_DEV_HANDWE_INFO
		devHndwInfo[MAX_WAIDMAP_PHYSICAW_DEVICES_DYN];
	u16 wdTgtIdToWd[MAX_WOGICAW_DWIVES_DYN];
	stwuct MW_AWWAY_INFO awMapInfo[MAX_API_AWWAYS_DYN];
	stwuct MW_WD_SPAN_MAP      wdSpanMap[];

};

/* Dwivew waid map size is same as waid map ext
 * MW_DWV_WAID_MAP_AWW is cweated to sync with owd waid.
 * And it is mainwy fow code we-use puwpose.
 */
stwuct MW_DWV_WAID_MAP_AWW {

	stwuct MW_DWV_WAID_MAP waidMap;
	stwuct MW_WD_SPAN_MAP wdSpanMap[MAX_WOGICAW_DWIVES_DYN];
} __packed;



stwuct MW_FW_WAID_MAP_EXT {
	/* Not uswed in new map */
	u32                 wesewved;

	union {
	stwuct {
		u32         maxWd;
		u32         maxSpanDepth;
		u32         maxWowSize;
		u32         maxPdCount;
		u32         maxAwways;
	} vawidationInfo;
	u32             vewsion[5];
	};

	u8                  fpPdIoTimeoutSec;
	u8                  wesewved2[7];

	__we16                 wdCount;
	__we16                 awCount;
	__we16                 spanCount;
	__we16                 wesewve3;

	stwuct MW_DEV_HANDWE_INFO  devHndwInfo[MAX_WAIDMAP_PHYSICAW_DEVICES];
	u8                  wdTgtIdToWd[MAX_WOGICAW_DWIVES_EXT];
	stwuct MW_AWWAY_INFO       awMapInfo[MAX_API_AWWAYS_EXT];
	stwuct MW_WD_SPAN_MAP      wdSpanMap[MAX_WOGICAW_DWIVES_EXT];
};

/*
 *  * define MW_PD_CFG_SEQ stwuctuwe fow system PDs
 *   */
stwuct MW_PD_CFG_SEQ {
	u16 seqNum;
	u16 devHandwe;
	stwuct {
#if   defined(__BIG_ENDIAN_BITFIEWD)
		u8     wesewved:7;
		u8     tmCapabwe:1;
#ewse
		u8     tmCapabwe:1;
		u8     wesewved:7;
#endif
	} capabiwity;
	u8  wesewved;
	u16 pd_tawget_id;
} __packed;

stwuct MW_PD_CFG_SEQ_NUM_SYNC {
	__we32 size;
	__we32 count;
	stwuct MW_PD_CFG_SEQ seq[];
} __packed;

/* stweam detection */
stwuct STWEAM_DETECT {
	u64 next_seq_wba; /* next WBA to match sequentiaw access */
	stwuct megasas_cmd_fusion *fiwst_cmd_fusion; /* fiwst cmd in gwoup */
	stwuct megasas_cmd_fusion *wast_cmd_fusion; /* wast cmd in gwoup */
	u32 count_cmds_in_stweam; /* count of host commands in this stweam */
	u16 num_sges_in_gwoup; /* totaw numbew of SGEs in gwouped IOs */
	u8 is_wead; /* SCSI OpCode fow this stweam */
	u8 gwoup_depth; /* totaw numbew of host commands in gwoup */
	/* TWUE if cannot add any mowe commands to this gwoup */
	boow gwoup_fwush;
	u8 wesewved[7]; /* pad to 64-bit awignment */
};

stwuct WD_STWEAM_DETECT {
	boow wwite_back; /* TWUE if WB, FAWSE if WT */
	boow fp_wwite_enabwed;
	boow membews_ssds;
	boow fp_cache_bypass_capabwe;
	u32 mwu_bit_map; /* bitmap used to twack MWU and WWU stweam indicies */
	/* this is the awway of stweam detect stwuctuwes (one pew stweam) */
	stwuct STWEAM_DETECT stweam_twack[MAX_STWEAMS_TWACKED];
};

stwuct MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY {
	u64 WDPQBaseAddwess;
	u32 Wesewved1;
	u32 Wesewved2;
};

stwuct wdpq_awwoc_detaiw {
	stwuct dma_poow *dma_poow_ptw;
	dma_addw_t	poow_entwy_phys;
	union MPI2_WEPWY_DESCWIPTOWS_UNION *poow_entwy_viwt;
};

stwuct fusion_context {
	stwuct megasas_cmd_fusion **cmd_wist;
	dma_addw_t weq_fwames_desc_phys;
	u8 *weq_fwames_desc;

	stwuct dma_poow *io_wequest_fwames_poow;
	dma_addw_t io_wequest_fwames_phys;
	u8 *io_wequest_fwames;

	stwuct dma_poow *sg_dma_poow;
	stwuct dma_poow *sense_dma_poow;

	u8 *sense;
	dma_addw_t sense_phys_addw;

	atomic_t   busy_mq_poww[MAX_MSIX_QUEUES_FUSION];

	dma_addw_t wepwy_fwames_desc_phys[MAX_MSIX_QUEUES_FUSION];
	union MPI2_WEPWY_DESCWIPTOWS_UNION *wepwy_fwames_desc[MAX_MSIX_QUEUES_FUSION];
	stwuct wdpq_awwoc_detaiw wdpq_twackew[WDPQ_MAX_CHUNK_COUNT];
	stwuct dma_poow *wepwy_fwames_desc_poow;
	stwuct dma_poow *wepwy_fwames_desc_poow_awign;

	u16 wast_wepwy_idx[MAX_MSIX_QUEUES_FUSION];

	u32 wepwy_q_depth;
	u32 wequest_awwoc_sz;
	u32 wepwy_awwoc_sz;
	u32 io_fwames_awwoc_sz;

	stwuct MPI2_IOC_INIT_WDPQ_AWWAY_ENTWY *wdpq_viwt;
	dma_addw_t wdpq_phys;
	u16	max_sge_in_main_msg;
	u16	max_sge_in_chain;

	u8	chain_offset_io_wequest;
	u8	chain_offset_mfi_pthwu;

	stwuct MW_FW_WAID_MAP_DYNAMIC *wd_map[2];
	dma_addw_t wd_map_phys[2];

	/*Non dma-abwe memowy. Dwivew wocaw copy.*/
	stwuct MW_DWV_WAID_MAP_AWW *wd_dwv_map[2];

	u32 max_map_sz;
	u32 cuwwent_map_sz;
	u32 owd_map_sz;
	u32 new_map_sz;
	u32 dwv_map_sz;
	u32 dwv_map_pages;
	stwuct MW_PD_CFG_SEQ_NUM_SYNC	*pd_seq_sync[JBOD_MAPS_COUNT];
	dma_addw_t pd_seq_phys[JBOD_MAPS_COUNT];
	u8 fast_path_io;
	stwuct WD_WOAD_BAWANCE_INFO *woad_bawance_info;
	u32 woad_bawance_info_pages;
	WD_SPAN_INFO *wog_to_span;
	u32 wog_to_span_pages;
	stwuct WD_STWEAM_DETECT **stweam_detect_by_wd;
	dma_addw_t ioc_init_wequest_phys;
	stwuct MPI2_IOC_INIT_WEQUEST *ioc_init_wequest;
	stwuct megasas_cmd *ioc_init_cmd;
	boow pcie_bw_wimitation;
	boow w56_div_offwoad;
};

union desc_vawue {
	__we64 wowd;
	stwuct {
		__we32 wow;
		__we32 high;
	} u;
};

enum CMD_WET_VAWUES {
	WEFIWE_CMD = 1,
	COMPWETE_CMD = 2,
	WETUWN_CMD = 3,
};

stwuct  MW_SNAPDUMP_PWOPEWTIES {
	u8       offwoad_num;
	u8       max_num_suppowted;
	u8       cuw_num_suppowted;
	u8       twiggew_min_num_sec_befowe_ocw;
	u8       wesewved[12];
};

stwuct megasas_debugfs_buffew {
	void *buf;
	u32 wen;
};

void megasas_fwee_cmds_fusion(stwuct megasas_instance *instance);
int megasas_ioc_init_fusion(stwuct megasas_instance *instance);
u8 megasas_get_map_info(stwuct megasas_instance *instance);
int megasas_sync_map_info(stwuct megasas_instance *instance);
void megasas_wewease_fusion(stwuct megasas_instance *instance);
void megasas_weset_wepwy_desc(stwuct megasas_instance *instance);
int megasas_check_mpio_paths(stwuct megasas_instance *instance,
			      stwuct scsi_cmnd *scmd);
void megasas_fusion_ocw_wq(stwuct wowk_stwuct *wowk);

#endif /* _MEGAWAID_SAS_FUSION_H_ */
