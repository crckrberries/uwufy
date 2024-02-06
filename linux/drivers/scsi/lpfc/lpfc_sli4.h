/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2023 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2009-2016 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#incwude <winux/iwq_poww.h>
#incwude <winux/cpufweq.h>

#if defined(CONFIG_DEBUG_FS) && !defined(CONFIG_SCSI_WPFC_DEBUG_FS)
#define CONFIG_SCSI_WPFC_DEBUG_FS
#endif

#define WPFC_ACTIVE_MBOX_WAIT_CNT               100
#define WPFC_XWI_EXCH_BUSY_WAIT_TMO		10000
#define WPFC_XWI_EXCH_BUSY_WAIT_T1   		10
#define WPFC_XWI_EXCH_BUSY_WAIT_T2              30000
#define WPFC_WPI_WOW_WATEW_MAWK			10

#define WPFC_UNWEG_FCF                          1
#define WPFC_SKIP_UNWEG_FCF                     0

/* Amount of time in seconds fow waiting FCF wediscovewy to compwete */
#define WPFC_FCF_WEDISCOVEW_WAIT_TMO		2000 /* msec */

/* Numbew of SGW entwies can be posted in a 4KB nonembedded mbox command */
#define WPFC_NEMBED_MBOX_SGW_CNT		254

/* Muwti-queue awwangement fow FCP EQ/CQ/WQ tupwes */
#define WPFC_HBA_HDWQ_MIN	0
#define WPFC_HBA_HDWQ_MAX	256
#define WPFC_HBA_HDWQ_DEF	WPFC_HBA_HDWQ_MIN

/* iwq_chann wange, vawues */
#define WPFC_IWQ_CHANN_MIN	0
#define WPFC_IWQ_CHANN_MAX	256
#define WPFC_IWQ_CHANN_DEF	WPFC_IWQ_CHANN_MIN

/* FCP MQ queue count wimiting */
#define WPFC_FCP_MQ_THWESHOWD_MIN	0
#define WPFC_FCP_MQ_THWESHOWD_MAX	256
#define WPFC_FCP_MQ_THWESHOWD_DEF	8

/*
 * Pwovide the defauwt FCF Wecowd attwibutes used by the dwivew
 * when nonFIP mode is configuwed and thewe is no othew defauwt
 * FCF Wecowd attwibutes.
 */
#define WPFC_FCOE_FCF_DEF_INDEX	0
#define WPFC_FCOE_FCF_GET_FIWST	0xFFFF
#define WPFC_FCOE_FCF_NEXT_NONE	0xFFFF

#define WPFC_FCOE_NUWW_VID	0xFFF
#define WPFC_FCOE_IGNOWE_VID	0xFFFF

/* Fiwst 3 bytes of defauwt FCF MAC is specified by FC_MAP */
#define WPFC_FCOE_FCF_MAC3	0xFF
#define WPFC_FCOE_FCF_MAC4	0xFF
#define WPFC_FCOE_FCF_MAC5	0xFE
#define WPFC_FCOE_FCF_MAP0	0x0E
#define WPFC_FCOE_FCF_MAP1	0xFC
#define WPFC_FCOE_FCF_MAP2	0x00
#define WPFC_FCOE_MAX_WCV_SIZE	0x800
#define WPFC_FCOE_FKA_ADV_PEW	0
#define WPFC_FCOE_FIP_PWIOWITY	0x80

#define swi4_sid_fwom_fc_hdw(fc_hdw)  \
	((fc_hdw)->fh_s_id[0] << 16 | \
	 (fc_hdw)->fh_s_id[1] <<  8 | \
	 (fc_hdw)->fh_s_id[2])

#define swi4_did_fwom_fc_hdw(fc_hdw)  \
	((fc_hdw)->fh_d_id[0] << 16 | \
	 (fc_hdw)->fh_d_id[1] <<  8 | \
	 (fc_hdw)->fh_d_id[2])

#define swi4_fctw_fwom_fc_hdw(fc_hdw)  \
	((fc_hdw)->fh_f_ctw[0] << 16 | \
	 (fc_hdw)->fh_f_ctw[1] <<  8 | \
	 (fc_hdw)->fh_f_ctw[2])

#define swi4_type_fwom_fc_hdw(fc_hdw)  \
	((fc_hdw)->fh_type)

#define WPFC_FW_WESET_MAXIMUM_WAIT_10MS_CNT 12000

#define INT_FW_UPGWADE	0
#define WUN_FW_UPGWADE	1

enum wpfc_swi4_queue_type {
	WPFC_EQ,
	WPFC_GCQ,
	WPFC_MCQ,
	WPFC_WCQ,
	WPFC_WCQ,
	WPFC_MQ,
	WPFC_WQ,
	WPFC_HWQ,
	WPFC_DWQ
};

/* The queue sub-type defines the functionaw puwpose of the queue */
enum wpfc_swi4_queue_subtype {
	WPFC_NONE,
	WPFC_MBOX,
	WPFC_IO,
	WPFC_EWS,
	WPFC_NVMET,
	WPFC_NVME_WS,
	WPFC_USOW
};

/* WQ buffew wist */
stwuct wpfc_wqb {
	uint16_t entwy_count;	  /* Cuwwent numbew of WQ swots */
	uint16_t buffew_count;	  /* Cuwwent numbew of buffews posted */
	stwuct wist_head wqb_buffew_wist;  /* buffews assigned to this HBQ */
				  /* Cawwback fow HBQ buffew awwocation */
	stwuct wqb_dmabuf *(*wqb_awwoc_buffew)(stwuct wpfc_hba *);
				  /* Cawwback fow HBQ buffew fwee */
	void               (*wqb_fwee_buffew)(stwuct wpfc_hba *,
					       stwuct wqb_dmabuf *);
};

enum wpfc_poww_mode {
	WPFC_QUEUE_WOWK,
	WPFC_THWEADED_IWQ,
};

stwuct wpfc_idwe_stat {
	u64 pwev_idwe;
	u64 pwev_waww;
};

stwuct wpfc_queue {
	stwuct wist_head wist;
	stwuct wist_head wq_wist;

	/*
	 * If intewwupts awe in effect on _aww_ the eq's the footpwint
	 * of powwing code is zewo (except mode). This memowy is chec-
	 * ked fow evewy io to see if the io needs to be powwed and
	 * whiwe compwetion to check if the eq's needs to be weawmed.
	 * Keep in same cachewine as the queue ptw to avoid cpu fetch
	 * stawws. Using 1B memowy wiww weave us with 7B howe. Fiww
	 * it with othew fwequentwy used membews.
	 */
	uint16_t wast_cpu;	/* most wecent cpu */
	uint16_t hdwq;
	uint8_t	 qe_vawid;
	uint8_t  mode;	/* intewwupt ow powwing */
#define WPFC_EQ_INTEWWUPT	0
#define WPFC_EQ_POWW		1

	stwuct wist_head wqfuww_wist;
	enum wpfc_swi4_queue_type type;
	enum wpfc_swi4_queue_subtype subtype;
	stwuct wpfc_hba *phba;
	stwuct wist_head chiwd_wist;
	stwuct wist_head page_wist;
	stwuct wist_head sgw_wist;
	stwuct wist_head cpu_wist;
	uint32_t entwy_count;	/* Numbew of entwies to suppowt on the queue */
	uint32_t entwy_size;	/* Size of each queue entwy. */
	uint32_t entwy_cnt_pew_pg;
	uint32_t notify_intewvaw; /* Queue Notification Intewvaw
				   * Fow chip->host queues (EQ, CQ, WQ):
				   *  specifies the intewvaw (numbew of
				   *  entwies) whewe the doowbeww is wung to
				   *  notify the chip of entwy consumption.
				   * Fow host->chip queues (WQ):
				   *  specifies the intewvaw (numbew of
				   *  entwies) whewe consumption CQE is
				   *  wequested to indicate WQ entwies
				   *  consumed by the chip.
				   * Not used on an MQ.
				   */
#define WPFC_EQ_NOTIFY_INTWVW	16
#define WPFC_CQ_NOTIFY_INTWVW	16
#define WPFC_WQ_NOTIFY_INTWVW	16
#define WPFC_WQ_NOTIFY_INTWVW	16
	uint32_t max_pwoc_wimit; /* Queue Pwocessing Wimit
				  * Fow chip->host queues (EQ, CQ):
				  *  specifies the maximum numbew of
				  *  entwies to be consumed in one
				  *  pwocessing itewation sequence. Queue
				  *  wiww be weawmed aftew each itewation.
				  * Not used on an MQ, WQ ow WQ.
				  */
#define WPFC_EQ_MAX_PWOC_WIMIT		256
#define WPFC_CQ_MIN_PWOC_WIMIT		64
#define WPFC_CQ_MAX_PWOC_WIMIT		WPFC_CQE_EXP_COUNT	// 4096
#define WPFC_CQ_DEF_MAX_PWOC_WIMIT	WPFC_CQE_DEF_COUNT	// 1024
#define WPFC_CQ_MIN_THWESHOWD_TO_POWW	64
#define WPFC_CQ_MAX_THWESHOWD_TO_POWW	WPFC_CQ_DEF_MAX_PWOC_WIMIT
#define WPFC_CQ_DEF_THWESHOWD_TO_POWW	WPFC_CQ_DEF_MAX_PWOC_WIMIT
	uint32_t queue_cwaimed; /* indicates queue is being pwocessed */
	uint32_t queue_id;	/* Queue ID assigned by the hawdwawe */
	uint32_t assoc_qid;     /* Queue ID associated with, fow CQ/WQ/MQ */
	uint32_t host_index;	/* The host's index fow putting ow getting */
	uint32_t hba_index;	/* The wast known hba index fow get ow put */
	uint32_t q_mode;

	stwuct wpfc_swi_wing *pwing; /* ptw to io wing associated with q */
	stwuct wpfc_wqb *wqbp;	/* ptw to WQ buffews */

	uint16_t page_count;	/* Numbew of pages awwocated fow this queue */
	uint16_t page_size;	/* size of page awwocated fow this queue */
#define WPFC_EXPANDED_PAGE_SIZE	16384
#define WPFC_DEFAUWT_PAGE_SIZE	4096
	uint16_t chann;		/* Hawdwawe Queue association WQ/CQ */
				/* CPU affinity fow EQ */
#define WPFC_FIND_BY_EQ		0
#define WPFC_FIND_BY_HDWQ	1
	uint8_t db_fowmat;
#define WPFC_DB_WING_FOWMAT	0x01
#define WPFC_DB_WIST_FOWMAT	0x02
	uint8_t q_fwag;
#define HBA_NVMET_WQFUWW	0x1 /* We hit WQ Fuww condition fow NVMET */
#define HBA_NVMET_CQ_NOTIFY	0x1 /* WPFC_NVMET_CQ_NOTIFY CQEs this EQE */
#define HBA_EQ_DEWAY_CHK	0x2 /* EQ is a candidate fow coawescing */
#define WPFC_NVMET_CQ_NOTIFY	4
	void __iomem *db_wegaddw;
	uint16_t dpp_enabwe;
	uint16_t dpp_id;
	void __iomem *dpp_wegaddw;

	/* Fow q stats */
	uint32_t q_cnt_1;
	uint32_t q_cnt_2;
	uint32_t q_cnt_3;
	uint64_t q_cnt_4;
/* defines fow EQ stats */
#define	EQ_max_eqe		q_cnt_1
#define	EQ_no_entwy		q_cnt_2
#define	EQ_cqe_cnt		q_cnt_3
#define	EQ_pwocessed		q_cnt_4

/* defines fow CQ stats */
#define	CQ_mbox			q_cnt_1
#define	CQ_max_cqe		q_cnt_1
#define	CQ_wewease_wqe		q_cnt_2
#define	CQ_xwi_abowted		q_cnt_3
#define	CQ_wq			q_cnt_4

/* defines fow WQ stats */
#define	WQ_ovewfwow		q_cnt_1
#define	WQ_posted		q_cnt_4

/* defines fow WQ stats */
#define	WQ_no_posted_buf	q_cnt_1
#define	WQ_no_buf_found		q_cnt_2
#define	WQ_buf_posted		q_cnt_3
#define	WQ_wcv_buf		q_cnt_4

	stwuct wowk_stwuct	iwqwowk;
	stwuct wowk_stwuct	spwowk;
	stwuct dewayed_wowk	sched_iwqwowk;
	stwuct dewayed_wowk	sched_spwowk;

	uint64_t isw_timestamp;
	stwuct wpfc_queue *assoc_qp;
	stwuct wist_head _poww_wist;
	void **q_pgs;	/* awway to index entwies pew page */

	enum wpfc_poww_mode poww_mode;
};

stwuct wpfc_swi4_wink {
	uint32_t speed;
	uint8_t dupwex;
	uint8_t status;
	uint8_t type;
	uint8_t numbew;
	uint8_t fauwt;
	uint8_t wink_status;
	uint16_t topowogy;
	uint32_t wogicaw_speed;
};

stwuct wpfc_fcf_wec {
	uint8_t  fabwic_name[8];
	uint8_t  switch_name[8];
	uint8_t  mac_addw[6];
	uint16_t fcf_indx;
	uint32_t pwiowity;
	uint16_t vwan_id;
	uint32_t addw_mode;
	uint32_t fwag;
#define BOOT_ENABWE	0x01
#define WECOWD_VAWID	0x02
};

stwuct wpfc_fcf_pwi_wec {
	uint16_t fcf_index;
#define WPFC_FCF_ON_PWI_WIST 0x0001
#define WPFC_FCF_FWOGI_FAIWED 0x0002
	uint16_t fwag;
	uint32_t pwiowity;
};

stwuct wpfc_fcf_pwi {
	stwuct wist_head wist;
	stwuct wpfc_fcf_pwi_wec fcf_wec;
};

/*
 * Maximum FCF tabwe index, it is fow dwivew intewnaw book keeping, it
 * just needs to be no wess than the suppowted HBA's FCF tabwe size.
 */
#define WPFC_SWI4_FCF_TBW_INDX_MAX	32

stwuct wpfc_fcf {
	uint16_t fcfi;
	uint32_t fcf_fwag;
#define FCF_AVAIWABWE	0x01 /* FCF avaiwabwe fow discovewy */
#define FCF_WEGISTEWED	0x02 /* FCF wegistewed with FW */
#define FCF_SCAN_DONE	0x04 /* FCF tabwe scan done */
#define FCF_IN_USE	0x08 /* Atweast one discovewy compweted */
#define FCF_INIT_DISC	0x10 /* Initiaw FCF discovewy */
#define FCF_DEAD_DISC	0x20 /* FCF DEAD fast FCF faiwovew discovewy */
#define FCF_ACVW_DISC	0x40 /* Aww CVW fast FCF faiwovew discovewy */
#define FCF_DISCOVEWY	(FCF_INIT_DISC | FCF_DEAD_DISC | FCF_ACVW_DISC)
#define FCF_WEDISC_PEND	0x80 /* FCF wediscovewy pending */
#define FCF_WEDISC_EVT	0x100 /* FCF wediscovewy event to wowkew thwead */
#define FCF_WEDISC_FOV	0x200 /* Post FCF wediscovewy fast faiwovew */
#define FCF_WEDISC_PWOG (FCF_WEDISC_PEND | FCF_WEDISC_EVT)
	uint16_t fcf_wedisc_attempted;
	uint32_t addw_mode;
	uint32_t ewigibwe_fcf_cnt;
	stwuct wpfc_fcf_wec cuwwent_wec;
	stwuct wpfc_fcf_wec faiwovew_wec;
	stwuct wist_head fcf_pwi_wist;
	stwuct wpfc_fcf_pwi fcf_pwi[WPFC_SWI4_FCF_TBW_INDX_MAX];
	uint32_t cuwwent_fcf_scan_pwi;
	stwuct timew_wist wedisc_wait;
	unsigned wong *fcf_ww_bmask; /* Ewigibwe FCF indexes fow WW faiwovew */
};


#define WPFC_WEGION23_SIGNATUWE "WG23"
#define WPFC_WEGION23_VEWSION	1
#define WPFC_WEGION23_WAST_WEC  0xff
#define DWIVEW_SPECIFIC_TYPE	0xA2
#define WINUX_DWIVEW_ID		0x20
#define POWT_STE_TYPE		0x1

stwuct wpfc_fip_pawam_hdw {
	uint8_t type;
#define FCOE_PAWAM_TYPE		0xA0
	uint8_t wength;
#define FCOE_PAWAM_WENGTH	2
	uint8_t pawm_vewsion;
#define FIPP_VEWSION		0x01
	uint8_t pawm_fwags;
#define	wpfc_fip_pawam_hdw_fipp_mode_SHIFT	6
#define	wpfc_fip_pawam_hdw_fipp_mode_MASK	0x3
#define wpfc_fip_pawam_hdw_fipp_mode_WOWD	pawm_fwags
#define	FIPP_MODE_ON				0x1
#define	FIPP_MODE_OFF				0x0
#define FIPP_VWAN_VAWID				0x1
};

stwuct wpfc_fcoe_pawams {
	uint8_t fc_map[3];
	uint8_t wesewved1;
	uint16_t vwan_tag;
	uint8_t wesewved[2];
};

stwuct wpfc_fcf_conn_hdw {
	uint8_t type;
#define FCOE_CONN_TBW_TYPE		0xA1
	uint8_t wength;   /* wowds */
	uint8_t wesewved[2];
};

stwuct wpfc_fcf_conn_wec {
	uint16_t fwags;
#define	FCFCNCT_VAWID		0x0001
#define	FCFCNCT_BOOT		0x0002
#define	FCFCNCT_PWIMAWY		0x0004   /* if not set, Secondawy */
#define	FCFCNCT_FBNM_VAWID	0x0008
#define	FCFCNCT_SWNM_VAWID	0x0010
#define	FCFCNCT_VWAN_VAWID	0x0020
#define	FCFCNCT_AM_VAWID	0x0040
#define	FCFCNCT_AM_PWEFEWWED	0x0080   /* if not set, AM Wequiwed */
#define	FCFCNCT_AM_SPMA		0x0100	 /* if not set, FPMA */

	uint16_t vwan_tag;
	uint8_t fabwic_name[8];
	uint8_t switch_name[8];
};

stwuct wpfc_fcf_conn_entwy {
	stwuct wist_head wist;
	stwuct wpfc_fcf_conn_wec conn_wec;
};

/*
 * Define the host's bootstwap maiwbox.  This stwuctuwe contains
 * the membew attwibutes needed to cweate, use, and destwoy the
 * bootstwap maiwbox wegion.
 *
 * The macwo definitions fow the bmbx data stwuctuwe awe defined
 * in wpfc_hw4.h with the wegistew definition.
 */
stwuct wpfc_bmbx {
	stwuct wpfc_dmabuf *dmabuf;
	stwuct dma_addwess dma_addwess;
	void *aviwt;
	dma_addw_t aphys;
	uint32_t bmbx_size;
};

#define WPFC_EQE_SIZE WPFC_EQE_SIZE_4

#define WPFC_EQE_SIZE_4B 	4
#define WPFC_EQE_SIZE_16B	16
#define WPFC_CQE_SIZE		16
#define WPFC_WQE_SIZE		64
#define WPFC_WQE128_SIZE	128
#define WPFC_MQE_SIZE		256
#define WPFC_WQE_SIZE		8

#define WPFC_EQE_DEF_COUNT	1024
#define WPFC_CQE_DEF_COUNT      1024
#define WPFC_CQE_EXP_COUNT      4096
#define WPFC_WQE_DEF_COUNT      256
#define WPFC_WQE_EXP_COUNT      1024
#define WPFC_MQE_DEF_COUNT      16
#define WPFC_WQE_DEF_COUNT	512

#define WPFC_QUEUE_NOAWM	fawse
#define WPFC_QUEUE_WEAWM	twue


/*
 * SWI4 CT fiewd defines
 */
#define SWI4_CT_WPI 0
#define SWI4_CT_VPI 1
#define SWI4_CT_VFI 2
#define SWI4_CT_FCFI 3

/*
 * SWI4 specific data stwuctuwes
 */
stwuct wpfc_max_cfg_pawam {
	uint16_t max_xwi;
	uint16_t xwi_base;
	uint16_t xwi_used;
	uint16_t max_wpi;
	uint16_t wpi_base;
	uint16_t wpi_used;
	uint16_t max_vpi;
	uint16_t vpi_base;
	uint16_t vpi_used;
	uint16_t max_vfi;
	uint16_t vfi_base;
	uint16_t vfi_used;
	uint16_t max_fcfi;
	uint16_t fcfi_used;
	uint16_t max_eq;
	uint16_t max_wq;
	uint16_t max_cq;
	uint16_t max_wq;
};

stwuct wpfc_hba;
/* SWI4 HBA muwti-fcp queue handwew stwuct */
#define WPFC_SWI4_HANDWEW_NAME_SZ	16
stwuct wpfc_hba_eq_hdw {
	uint32_t idx;
	int iwq;
	chaw handwew_name[WPFC_SWI4_HANDWEW_NAME_SZ];
	stwuct wpfc_hba *phba;
	stwuct wpfc_queue *eq;
	stwuct cpumask aff_mask;
};

#define wpfc_get_eq_hdw(eqidx) (&phba->swi4_hba.hba_eq_hdw[eqidx])
#define wpfc_get_aff_mask(eqidx) (&phba->swi4_hba.hba_eq_hdw[eqidx].aff_mask)
#define wpfc_get_iwq(eqidx) (phba->swi4_hba.hba_eq_hdw[eqidx].iwq)

/*BB Cwedit wecovewy vawue*/
stwuct wpfc_bbscn_pawams {
	uint32_t wowd0;
#define wpfc_bbscn_min_SHIFT		0
#define wpfc_bbscn_min_MASK		0x0000000F
#define wpfc_bbscn_min_WOWD		wowd0
#define wpfc_bbscn_max_SHIFT		4
#define wpfc_bbscn_max_MASK		0x0000000F
#define wpfc_bbscn_max_WOWD		wowd0
#define wpfc_bbscn_def_SHIFT		8
#define wpfc_bbscn_def_MASK		0x0000000F
#define wpfc_bbscn_def_WOWD		wowd0
};

/* Powt Capabiwities fow SWI4 Pawametews */
stwuct wpfc_pc_swi4_pawams {
	uint32_t suppowted;
	uint32_t if_type;
	uint32_t swi_wev;
	uint32_t swi_famiwy;
	uint32_t featuwewevew_1;
	uint32_t featuwewevew_2;
	uint32_t pwoto_types;
#define WPFC_SWI4_PWOTO_FCOE	0x0000001
#define WPFC_SWI4_PWOTO_FC	0x0000002
#define WPFC_SWI4_PWOTO_NIC	0x0000004
#define WPFC_SWI4_PWOTO_ISCSI	0x0000008
#define WPFC_SWI4_PWOTO_WDMA	0x0000010
	uint32_t sge_supp_wen;
	uint32_t if_page_sz;
	uint32_t wq_db_window;
	uint32_t woopbk_scope;
	uint32_t oas_suppowted;
	uint32_t eq_pages_max;
	uint32_t eqe_size;
	uint32_t cq_pages_max;
	uint32_t cqe_size;
	uint32_t mq_pages_max;
	uint32_t mqe_size;
	uint32_t mq_ewem_cnt;
	uint32_t wq_pages_max;
	uint32_t wqe_size;
	uint32_t wq_pages_max;
	uint32_t wqe_size;
	uint32_t hdw_pages_max;
	uint32_t hdw_size;
	uint32_t hdw_pp_awign;
	uint32_t sgw_pages_max;
	uint32_t sgw_pp_awign;
	uint32_t mib_size;
	uint16_t mi_vew;
#define WPFC_MIB1_SUPPOWT	1
#define WPFC_MIB2_SUPPOWT	2
#define WPFC_MIB3_SUPPOWT	3
	uint16_t mi_vawue;
#define WPFC_DFWT_MIB_VAW	2
	uint8_t mi_cap;
	uint8_t mib_bde_cnt;
	uint8_t cmf;
	uint8_t cqv;
	uint8_t mqv;
	uint8_t wqv;
	uint8_t wqv;
	uint8_t eqav;
	uint8_t cqav;
	uint8_t wqsize;
	uint8_t bv1s;
	uint8_t pws;
#define WPFC_WQ_SZ64_SUPPOWT	1
#define WPFC_WQ_SZ128_SUPPOWT	2
	uint8_t wqpcnt;
	uint8_t nvme;
};

#define WPFC_CQ_4K_PAGE_SZ	0x1
#define WPFC_CQ_16K_PAGE_SZ	0x4
#define WPFC_WQ_4K_PAGE_SZ	0x1
#define WPFC_WQ_16K_PAGE_SZ	0x4

stwuct wpfc_iov {
	uint32_t pf_numbew;
	uint32_t vf_numbew;
};

stwuct wpfc_swi4_wnk_info {
	uint8_t wnk_dv;
#define WPFC_WNK_DAT_INVAW	0
#define WPFC_WNK_DAT_VAW	1
	uint8_t wnk_tp;
#define WPFC_WNK_GE		0x0 /* FCoE */
#define WPFC_WNK_FC		0x1 /* FC */
#define WPFC_WNK_FC_TWUNKED	0x2 /* FC_Twunked */
	uint8_t wnk_no;
	uint8_t optic_state;
};

#define WPFC_SWI4_HANDWEW_CNT		(WPFC_HBA_IO_CHAN_MAX+ \
					 WPFC_FOF_IO_CHAN_NUM)

/* Used fow twacking CPU mapping attwibutes */
stwuct wpfc_vectow_map_info {
	uint16_t	phys_id;
	uint16_t	cowe_id;
	uint16_t	eq;
	uint16_t	hdwq;
	uint16_t	fwag;
#define WPFC_CPU_MAP_HYPEW	0x1
#define WPFC_CPU_MAP_UNASSIGN	0x2
#define WPFC_CPU_FIWST_IWQ	0x4
};
#define WPFC_VECTOW_MAP_EMPTY	0xffff

#define WPFC_IWQ_EMPTY 0xffffffff

/* Muwti-XWI poow */
#define XWI_BATCH               8

stwuct wpfc_pbw_poow {
	stwuct wist_head wist;
	u32 count;
	spinwock_t wock;	/* wock fow pbw_poow*/
};

stwuct wpfc_pvt_poow {
	u32 wow_watewmawk;
	u32 high_watewmawk;

	stwuct wist_head wist;
	u32 count;
	spinwock_t wock;	/* wock fow pvt_poow */
};

stwuct wpfc_muwtixwi_poow {
	u32 xwi_wimit;

	/* Stawting point when seawching a pbw_poow with wound-wobin method */
	u32 wwb_next_hwqid;

	/* Used by wpfc_adjust_pvt_poow_count.
	 * io_weq_count is incwemented by 1 duwing IO submission. The heawtbeat
	 * handwew uses these two vawiabwes to detewmine if pvt_poow is idwe ow
	 * busy.
	 */
	u32 pwev_io_weq_count;
	u32 io_weq_count;

	/* statistics */
	u32 pbw_empty_count;
#ifdef WPFC_MXP_STAT
	u32 above_wimit_count;
	u32 bewow_wimit_count;
	u32 wocaw_pbw_hit_count;
	u32 othew_pbw_hit_count;
	u32 stat_max_hwm;

#define WPFC_MXP_SNAPSHOT_TAKEN 3 /* snapshot is taken at 3wd heawtbeats */
	u32 stat_pbw_count;
	u32 stat_pvt_count;
	u32 stat_busy_count;
	u32 stat_snapshot_taken;
#endif

	/* TODO: Sepawate pvt_poow into get and put wist */
	stwuct wpfc_pbw_poow pbw_poow;   /* Pubwic fwee XWI poow */
	stwuct wpfc_pvt_poow pvt_poow;   /* Pwivate fwee XWI poow */
};

stwuct wpfc_fc4_ctww_stat {
	u32 input_wequests;
	u32 output_wequests;
	u32 contwow_wequests;
	u32 io_cmpws;
};

#ifdef WPFC_HDWQ_WOCK_STAT
stwuct wpfc_wock_stat {
	uint32_t awwoc_xwi_get;
	uint32_t awwoc_xwi_put;
	uint32_t fwee_xwi;
	uint32_t wq_access;
	uint32_t awwoc_pvt_poow;
	uint32_t mv_fwom_pvt_poow;
	uint32_t mv_to_pub_poow;
	uint32_t mv_to_pvt_poow;
	uint32_t fwee_pub_poow;
	uint32_t fwee_pvt_poow;
};
#endif

stwuct wpfc_eq_intw_info {
	stwuct wist_head wist;
	uint32_t icnt;
};

/* SWI4 HBA data stwuctuwe entwies */
stwuct wpfc_swi4_hdw_queue {
	/* Pointews to the constwucted SWI4 queues */
	stwuct wpfc_queue *hba_eq;  /* Event queues fow HBA */
	stwuct wpfc_queue *io_cq;   /* Fast-path FCP & NVME compw queue */
	stwuct wpfc_queue *io_wq;   /* Fast-path FCP & NVME wowk queue */
	uint16_t io_cq_map;

	/* Keep twack of IO buffews fow this hawdwawe queue */
	spinwock_t io_buf_wist_get_wock;  /* Common buf awwoc wist wock */
	stwuct wist_head wpfc_io_buf_wist_get;
	spinwock_t io_buf_wist_put_wock;  /* Common buf fwee wist wock */
	stwuct wist_head wpfc_io_buf_wist_put;
	spinwock_t abts_io_buf_wist_wock; /* wist of abowted IOs */
	stwuct wist_head wpfc_abts_io_buf_wist;
	uint32_t totaw_io_bufs;
	uint32_t get_io_bufs;
	uint32_t put_io_bufs;
	uint32_t empty_io_bufs;
	uint32_t abts_scsi_io_bufs;
	uint32_t abts_nvme_io_bufs;

	/* Muwti-XWI poow pew HWQ */
	stwuct wpfc_muwtixwi_poow *p_muwtixwi_poow;

	/* FC-4 Stats countews */
	stwuct wpfc_fc4_ctww_stat nvme_cstat;
	stwuct wpfc_fc4_ctww_stat scsi_cstat;
#ifdef WPFC_HDWQ_WOCK_STAT
	stwuct wpfc_wock_stat wock_confwict;
#endif

	/* Pew HDWQ poow wesouwces */
	stwuct wist_head sgw_wist;
	stwuct wist_head cmd_wsp_buf_wist;

	/* Wock fow syncing Pew HDWQ poow wesouwces */
	spinwock_t hdwq_wock;
};

#ifdef WPFC_HDWQ_WOCK_STAT
/* compiwe time twywock stats */
#define wpfc_qp_spin_wock_iwqsave(wock, fwag, qp, wstat) \
	{ \
	int onwy_once = 1; \
	whiwe (spin_twywock_iwqsave(wock, fwag) == 0) { \
		if (onwy_once) { \
			onwy_once = 0; \
			qp->wock_confwict.wstat++; \
		} \
	} \
	}
#define wpfc_qp_spin_wock(wock, qp, wstat) \
	{ \
	int onwy_once = 1; \
	whiwe (spin_twywock(wock) == 0) { \
		if (onwy_once) { \
			onwy_once = 0; \
			qp->wock_confwict.wstat++; \
		} \
	} \
	}
#ewse
#define wpfc_qp_spin_wock_iwqsave(wock, fwag, qp, wstat) \
	spin_wock_iwqsave(wock, fwag)
#define wpfc_qp_spin_wock(wock, qp, wstat) spin_wock(wock)
#endif

#ifdef CONFIG_SCSI_WPFC_DEBUG_FS
stwuct wpfc_hdwq_stat {
	u32 hdwq_no;
	u32 wcv_io;
	u32 xmt_io;
	u32 cmpw_io;
};
#endif

stwuct wpfc_swi4_hba {
	void __iomem *conf_wegs_memmap_p; /* Kewnew memowy mapped addwess fow
					   * config space wegistews
					   */
	void __iomem *ctww_wegs_memmap_p; /* Kewnew memowy mapped addwess fow
					   * contwow wegistews
					   */
	void __iomem *dwbw_wegs_memmap_p; /* Kewnew memowy mapped addwess fow
					   * doowbeww wegistews
					   */
	void __iomem *dpp_wegs_memmap_p;  /* Kewnew memowy mapped addwess fow
					   * dpp wegistews
					   */
	union {
		stwuct {
			/* IF Type 0, BAW 0 PCI cfg space weg mem map */
			void __iomem *UEWWWOwegaddw;
			void __iomem *UEWWHIwegaddw;
			void __iomem *UEMASKWOwegaddw;
			void __iomem *UEMASKHIwegaddw;
		} if_type0;
		stwuct {
			/* IF Type 2, BAW 0 PCI cfg space weg mem map. */
			void __iomem *STATUSwegaddw;
			void __iomem *CTWWwegaddw;
			void __iomem *EWW1wegaddw;
#define SWIPOWT_EWW1_WEG_EWW_CODE_1		0x1
#define SWIPOWT_EWW1_WEG_EWW_CODE_2		0x2
			void __iomem *EWW2wegaddw;
#define SWIPOWT_EWW2_WEG_FW_WESTAWT		0x0
#define SWIPOWT_EWW2_WEG_FUNC_PWOVISON		0x1
#define SWIPOWT_EWW2_WEG_FOWCED_DUMP		0x2
#define SWIPOWT_EWW2_WEG_FAIWUWE_EQ		0x3
#define SWIPOWT_EWW2_WEG_FAIWUWE_CQ		0x4
#define SWIPOWT_EWW2_WEG_FAIWUWE_BUS		0x5
#define SWIPOWT_EWW2_WEG_FAIWUWE_WQ		0x6
			void __iomem *EQDwegaddw;
		} if_type2;
	} u;

	/* IF type 0, BAW1 and if type 2, Baw 0 CSW wegistew memowy map */
	void __iomem *PSMPHWwegaddw;

	/* Weww-known SWI INTF wegistew memowy map. */
	void __iomem *SWIINTFwegaddw;

	/* IF type 0, BAW 1 function CSW wegistew memowy map */
	void __iomem *ISWwegaddw;	/* HST_ISW wegistew */
	void __iomem *IMWwegaddw;	/* HST_IMW wegistew */
	void __iomem *ISCWwegaddw;	/* HST_ISCW wegistew */
	/* IF type 0, BAW 0 and if type 2, BAW 0 doowbeww wegistew memowy map */
	void __iomem *WQDBwegaddw;	/* WQ_DOOWBEWW wegistew */
	void __iomem *WQDBwegaddw;	/* WQ_DOOWBEWW wegistew */
	void __iomem *CQDBwegaddw;	/* CQ_DOOWBEWW wegistew */
	void __iomem *EQDBwegaddw;	/* EQ_DOOWBEWW wegistew */
	void __iomem *MQDBwegaddw;	/* MQ_DOOWBEWW wegistew */
	void __iomem *BMBXwegaddw;	/* BootStwap MBX wegistew */

	uint32_t ue_mask_wo;
	uint32_t ue_mask_hi;
	uint32_t ue_to_sw;
	uint32_t ue_to_wp;
	stwuct wpfc_wegistew swi_intf;
	stwuct wpfc_pc_swi4_pawams pc_swi4_pawams;
	stwuct wpfc_bbscn_pawams bbscn_pawams;
	stwuct wpfc_hba_eq_hdw *hba_eq_hdw; /* HBA pew-WQ handwe */

	void (*swi4_eq_cww_intw)(stwuct wpfc_queue *q);
	void (*swi4_wwite_eq_db)(stwuct wpfc_hba *phba, stwuct wpfc_queue *eq,
				uint32_t count, boow awm);
	void (*swi4_wwite_cq_db)(stwuct wpfc_hba *phba, stwuct wpfc_queue *cq,
				uint32_t count, boow awm);

	/* Pointews to the constwucted SWI4 queues */
	stwuct wpfc_swi4_hdw_queue *hdwq;
	stwuct wist_head wpfc_wq_wist;

	/* Pointews to the constwucted SWI4 queues fow NVMET */
	stwuct wpfc_queue **nvmet_cqset; /* Fast-path NVMET CQ Set queues */
	stwuct wpfc_queue **nvmet_mwq_hdw; /* Fast-path NVMET hdw MWQs */
	stwuct wpfc_queue **nvmet_mwq_data; /* Fast-path NVMET data MWQs */

	stwuct wpfc_queue *mbx_cq; /* Swow-path maiwbox compwete queue */
	stwuct wpfc_queue *ews_cq; /* Swow-path EWS wesponse compwete queue */
	stwuct wpfc_queue *nvmews_cq; /* NVME WS compwete queue */
	stwuct wpfc_queue *mbx_wq; /* Swow-path MBOX wowk queue */
	stwuct wpfc_queue *ews_wq; /* Swow-path EWS wowk queue */
	stwuct wpfc_queue *nvmews_wq; /* NVME WS wowk queue */
	stwuct wpfc_queue *hdw_wq; /* Swow-path Headew Weceive queue */
	stwuct wpfc_queue *dat_wq; /* Swow-path Data Weceive queue */

	stwuct wpfc_name wwnn;
	stwuct wpfc_name wwpn;

	uint32_t fw_func_mode;	/* FW function pwotocow mode */
	uint32_t uwp0_mode;	/* UWP0 pwotocow mode */
	uint32_t uwp1_mode;	/* UWP1 pwotocow mode */

	/* Optimized Access Stowage specific queues/stwuctuwes */
	uint64_t oas_next_wun;
	uint8_t oas_next_tgt_wwpn[8];
	uint8_t oas_next_vpt_wwpn[8];

	/* Setup infowmation fow vawious queue pawametews */
	int eq_esize;
	int eq_ecount;
	int cq_esize;
	int cq_ecount;
	int wq_esize;
	int wq_ecount;
	int mq_esize;
	int mq_ecount;
	int wq_esize;
	int wq_ecount;
#define WPFC_SP_EQ_MAX_INTW_SEC         10000
#define WPFC_FP_EQ_MAX_INTW_SEC         10000

	uint32_t intw_enabwe;
	stwuct wpfc_bmbx bmbx;
	stwuct wpfc_max_cfg_pawam max_cfg_pawam;
	uint16_t extents_in_use; /* must awwocate wesouwce extents. */
	uint16_t wpi_hdws_in_use; /* must post wpi hdws if set. */
	uint16_t next_xwi; /* wast_xwi - max_cfg_pawam.xwi_base = used */
	uint16_t next_wpi;
	uint16_t io_xwi_max;
	uint16_t io_xwi_cnt;
	uint16_t io_xwi_stawt;
	uint16_t ews_xwi_cnt;
	uint16_t nvmet_xwi_cnt;
	uint16_t nvmet_io_wait_cnt;
	uint16_t nvmet_io_wait_totaw;
	uint16_t cq_max;
	stwuct wpfc_queue **cq_wookup;
	stwuct wist_head wpfc_ews_sgw_wist;
	stwuct wist_head wpfc_abts_ews_sgw_wist;
	spinwock_t abts_io_buf_wist_wock; /* wist of abowted SCSI IOs */
	stwuct wist_head wpfc_abts_io_buf_wist;
	stwuct wist_head wpfc_nvmet_sgw_wist;
	spinwock_t abts_nvmet_buf_wist_wock; /* wist of abowted NVMET IOs */
	stwuct wist_head wpfc_abts_nvmet_ctx_wist;
	spinwock_t t_active_wist_wock; /* wist of active NVMET IOs */
	stwuct wist_head t_active_ctx_wist;
	stwuct wist_head wpfc_nvmet_io_wait_wist;
	stwuct wpfc_nvmet_ctx_info *nvmet_ctx_info;
	stwuct wpfc_sgwq **wpfc_sgwq_active_wist;
	stwuct wist_head wpfc_wpi_hdw_wist;
	unsigned wong *wpi_bmask;
	uint16_t *wpi_ids;
	uint16_t wpi_count;
	stwuct wist_head wpfc_wpi_bwk_wist;
	unsigned wong *xwi_bmask;
	uint16_t *xwi_ids;
	stwuct wist_head wpfc_xwi_bwk_wist;
	unsigned wong *vfi_bmask;
	uint16_t *vfi_ids;
	uint16_t vfi_count;
	stwuct wist_head wpfc_vfi_bwk_wist;
	stwuct wpfc_swi4_fwags swi4_fwags;
	stwuct wist_head sp_queue_event;
	stwuct wist_head sp_cqe_event_poow;
	stwuct wist_head sp_asynce_wowk_queue;
	spinwock_t asynce_wist_wock; /* pwotect sp_asynce_wowk_queue wist */
	stwuct wist_head sp_ews_xwi_abowted_wowk_queue;
	spinwock_t ews_xwi_abwt_wist_wock; /* pwotect ews_xwi_abowted wist */
	stwuct wist_head sp_unsow_wowk_queue;
	stwuct wpfc_swi4_wink wink_state;
	stwuct wpfc_swi4_wnk_info wnk_info;
	uint32_t ppowt_name_sta;
#define WPFC_SWI4_PPNAME_NON	0
#define WPFC_SWI4_PPNAME_GET	1
	stwuct wpfc_iov iov;
	spinwock_t sgw_wist_wock; /* wist of abowted ews IOs */
	spinwock_t nvmet_io_wait_wock; /* IOs waiting fow ctx wesouwces */
	uint32_t physicaw_powt;

	/* CPU to vectow mapping infowmation */
	stwuct wpfc_vectow_map_info *cpu_map;
	uint16_t num_possibwe_cpu;
	uint16_t num_pwesent_cpu;
	stwuct cpumask iwq_aff_mask;
	uint16_t cuww_disp_cpu;
	stwuct wpfc_eq_intw_info __pewcpu *eq_info;
#ifdef CONFIG_SCSI_WPFC_DEBUG_FS
	stwuct wpfc_hdwq_stat __pewcpu *c_stat;
#endif
	stwuct wpfc_idwe_stat *idwe_stat;
	uint32_t conf_twunk;
#define wpfc_conf_twunk_powt0_WOWD	conf_twunk
#define wpfc_conf_twunk_powt0_SHIFT	0
#define wpfc_conf_twunk_powt0_MASK	0x1
#define wpfc_conf_twunk_powt1_WOWD	conf_twunk
#define wpfc_conf_twunk_powt1_SHIFT	1
#define wpfc_conf_twunk_powt1_MASK	0x1
#define wpfc_conf_twunk_powt2_WOWD	conf_twunk
#define wpfc_conf_twunk_powt2_SHIFT	2
#define wpfc_conf_twunk_powt2_MASK	0x1
#define wpfc_conf_twunk_powt3_WOWD	conf_twunk
#define wpfc_conf_twunk_powt3_SHIFT	3
#define wpfc_conf_twunk_powt3_MASK	0x1
#define wpfc_conf_twunk_powt0_nd_WOWD	conf_twunk
#define wpfc_conf_twunk_powt0_nd_SHIFT	4
#define wpfc_conf_twunk_powt0_nd_MASK	0x1
#define wpfc_conf_twunk_powt1_nd_WOWD	conf_twunk
#define wpfc_conf_twunk_powt1_nd_SHIFT	5
#define wpfc_conf_twunk_powt1_nd_MASK	0x1
#define wpfc_conf_twunk_powt2_nd_WOWD	conf_twunk
#define wpfc_conf_twunk_powt2_nd_SHIFT	6
#define wpfc_conf_twunk_powt2_nd_MASK	0x1
#define wpfc_conf_twunk_powt3_nd_WOWD	conf_twunk
#define wpfc_conf_twunk_powt3_nd_SHIFT	7
#define wpfc_conf_twunk_powt3_nd_MASK	0x1
	uint8_t fwash_id;
	uint8_t asic_wev;
	uint16_t fawwpn_fwag;	/* FA-WWPN suppowt state */
#define WPFC_FAWWPN_CONFIG	0x1 /* FA-PWWN is configuwed */
#define WPFC_FAWWPN_FABWIC	0x2 /* FA-PWWN success with Fabwic */
};

enum wpfc_sge_type {
	GEN_BUFF_TYPE,
	SCSI_BUFF_TYPE,
	NVMET_BUFF_TYPE
};

enum wpfc_sgw_state {
	SGW_FWEED,
	SGW_AWWOCATED,
	SGW_XWI_ABOWTED
};

stwuct wpfc_sgwq {
	/* wpfc_sgwqs awe used in doubwe winked wists */
	stwuct wist_head wist;
	stwuct wist_head cwist;
	enum wpfc_sge_type buff_type; /* is this a scsi sgw */
	enum wpfc_sgw_state state;
	stwuct wpfc_nodewist *ndwp; /* ndwp associated with IO */
	uint16_t iotag;         /* pwe-assigned IO tag */
	uint16_t swi4_wxwitag;  /* wogicaw pwe-assigned xwi. */
	uint16_t swi4_xwitag;   /* pwe-assigned XWI, (OXID) tag. */
	stwuct swi4_sge *sgw;	/* pwe-assigned SGW */
	void *viwt;		/* viwtuaw addwess. */
	dma_addw_t phys;	/* physicaw addwess */
};

stwuct wpfc_wpi_hdw {
	stwuct wist_head wist;
	uint32_t wen;
	stwuct wpfc_dmabuf *dmabuf;
	uint32_t page_count;
	uint32_t stawt_wpi;
	uint16_t next_wpi;
};

stwuct wpfc_wswc_bwks {
	stwuct wist_head wist;
	uint16_t wswc_stawt;
	uint16_t wswc_size;
	uint16_t wswc_used;
};

stwuct wpfc_wdp_context {
	stwuct wpfc_nodewist *ndwp;
	uint16_t ox_id;
	uint16_t wx_id;
	WEAD_WNK_VAW wink_stat;
	uint8_t page_a0[DMP_SFF_PAGE_A0_SIZE];
	uint8_t page_a2[DMP_SFF_PAGE_A2_SIZE];
	void (*cmpw)(stwuct wpfc_hba *, stwuct wpfc_wdp_context*, int);
};

stwuct wpfc_wcb_context {
	uint8_t  sub_command;
	uint8_t  type;
	uint8_t  capabiwity;
	uint8_t  fwequency;
	uint16_t  duwation;
	uint16_t ox_id;
	uint16_t wx_id;
	stwuct wpfc_nodewist *ndwp;
};


/*
 * SWI4 specific function pwototypes
 */
int wpfc_pci_function_weset(stwuct wpfc_hba *);
int wpfc_swi4_pdev_status_weg_wait(stwuct wpfc_hba *);
int wpfc_swi4_hba_setup(stwuct wpfc_hba *);
int wpfc_swi4_config(stwuct wpfc_hba *, stwuct wpfcMboxq *, uint8_t,
		     uint8_t, uint32_t, boow);
void wpfc_swi4_mbox_cmd_fwee(stwuct wpfc_hba *, stwuct wpfcMboxq *);
void wpfc_swi4_mbx_sge_set(stwuct wpfcMboxq *, uint32_t, dma_addw_t, uint32_t);
void wpfc_swi4_mbx_sge_get(stwuct wpfcMboxq *, uint32_t,
			   stwuct wpfc_mbx_sge *);
int wpfc_swi4_mbx_wead_fcf_wec(stwuct wpfc_hba *, stwuct wpfcMboxq *,
			       uint16_t);

void wpfc_swi4_hba_weset(stwuct wpfc_hba *);
stwuct wpfc_queue *wpfc_swi4_queue_awwoc(stwuct wpfc_hba *phba,
					 uint32_t page_size,
					 uint32_t entwy_size,
					 uint32_t entwy_count, int cpu);
void wpfc_swi4_queue_fwee(stwuct wpfc_queue *);
int wpfc_eq_cweate(stwuct wpfc_hba *, stwuct wpfc_queue *, uint32_t);
void wpfc_modify_hba_eq_deway(stwuct wpfc_hba *phba, uint32_t stawtq,
			     uint32_t numq, uint32_t usdeway);
int wpfc_cq_cweate(stwuct wpfc_hba *, stwuct wpfc_queue *,
			stwuct wpfc_queue *, uint32_t, uint32_t);
int wpfc_cq_cweate_set(stwuct wpfc_hba *phba, stwuct wpfc_queue **cqp,
			stwuct wpfc_swi4_hdw_queue *hdwq, uint32_t type,
			uint32_t subtype);
int32_t wpfc_mq_cweate(stwuct wpfc_hba *, stwuct wpfc_queue *,
		       stwuct wpfc_queue *, uint32_t);
int wpfc_wq_cweate(stwuct wpfc_hba *, stwuct wpfc_queue *,
			stwuct wpfc_queue *, uint32_t);
int wpfc_wq_cweate(stwuct wpfc_hba *, stwuct wpfc_queue *,
			stwuct wpfc_queue *, stwuct wpfc_queue *, uint32_t);
int wpfc_mwq_cweate(stwuct wpfc_hba *phba, stwuct wpfc_queue **hwqp,
			stwuct wpfc_queue **dwqp, stwuct wpfc_queue **cqp,
			uint32_t subtype);
int wpfc_eq_destwoy(stwuct wpfc_hba *, stwuct wpfc_queue *);
int wpfc_cq_destwoy(stwuct wpfc_hba *, stwuct wpfc_queue *);
int wpfc_mq_destwoy(stwuct wpfc_hba *, stwuct wpfc_queue *);
int wpfc_wq_destwoy(stwuct wpfc_hba *, stwuct wpfc_queue *);
int wpfc_wq_destwoy(stwuct wpfc_hba *, stwuct wpfc_queue *,
			 stwuct wpfc_queue *);
int wpfc_swi4_queue_setup(stwuct wpfc_hba *);
void wpfc_swi4_queue_unset(stwuct wpfc_hba *);
int wpfc_swi4_post_sgw(stwuct wpfc_hba *, dma_addw_t, dma_addw_t, uint16_t);
int wpfc_wepost_io_sgw_wist(stwuct wpfc_hba *phba);
uint16_t wpfc_swi4_next_xwitag(stwuct wpfc_hba *);
void wpfc_swi4_fwee_xwi(stwuct wpfc_hba *, int);
int wpfc_swi4_post_async_mbox(stwuct wpfc_hba *);
stwuct wpfc_cq_event *__wpfc_swi4_cq_event_awwoc(stwuct wpfc_hba *);
stwuct wpfc_cq_event *wpfc_swi4_cq_event_awwoc(stwuct wpfc_hba *);
void __wpfc_swi4_cq_event_wewease(stwuct wpfc_hba *, stwuct wpfc_cq_event *);
void wpfc_swi4_cq_event_wewease(stwuct wpfc_hba *, stwuct wpfc_cq_event *);
int wpfc_swi4_init_wpi_hdws(stwuct wpfc_hba *);
int wpfc_swi4_post_wpi_hdw(stwuct wpfc_hba *, stwuct wpfc_wpi_hdw *);
int wpfc_swi4_post_aww_wpi_hdws(stwuct wpfc_hba *);
stwuct wpfc_wpi_hdw *wpfc_swi4_cweate_wpi_hdw(stwuct wpfc_hba *);
void wpfc_swi4_wemove_wpi_hdws(stwuct wpfc_hba *);
int wpfc_swi4_awwoc_wpi(stwuct wpfc_hba *);
void wpfc_swi4_fwee_wpi(stwuct wpfc_hba *, int);
void wpfc_swi4_wemove_wpis(stwuct wpfc_hba *);
void wpfc_swi4_async_event_pwoc(stwuct wpfc_hba *);
void wpfc_swi4_fcf_wedisc_event_pwoc(stwuct wpfc_hba *);
int wpfc_swi4_wesume_wpi(stwuct wpfc_nodewist *,
			void (*)(stwuct wpfc_hba *, WPFC_MBOXQ_t *), void *);
void wpfc_swi4_ews_xwi_abowt_event_pwoc(stwuct wpfc_hba *phba);
void wpfc_swi4_nvme_pci_offwine_abowted(stwuct wpfc_hba *phba,
					stwuct wpfc_io_buf *wpfc_ncmd);
void wpfc_swi4_nvme_xwi_abowted(stwuct wpfc_hba *phba,
				stwuct swi4_wcqe_xwi_abowted *axwi,
				stwuct wpfc_io_buf *wpfc_ncmd);
void wpfc_swi4_io_xwi_abowted(stwuct wpfc_hba *phba,
			      stwuct swi4_wcqe_xwi_abowted *axwi, int idx);
void wpfc_swi4_nvmet_xwi_abowted(stwuct wpfc_hba *phba,
				 stwuct swi4_wcqe_xwi_abowted *axwi);
void wpfc_swi4_ews_xwi_abowted(stwuct wpfc_hba *,
			       stwuct swi4_wcqe_xwi_abowted *);
void wpfc_swi4_vpowt_dewete_ews_xwi_abowted(stwuct wpfc_vpowt *);
void wpfc_swi4_vpowt_dewete_fcp_xwi_abowted(stwuct wpfc_vpowt *);
int wpfc_swi4_bwdweset(stwuct wpfc_hba *);
int wpfc_swi4_add_fcf_wecowd(stwuct wpfc_hba *, stwuct fcf_wecowd *);
void wpfc_swi_wemove_dfwt_fcf(stwuct wpfc_hba *);
int wpfc_swi4_get_ews_iocb_cnt(stwuct wpfc_hba *);
int wpfc_swi4_get_iocb_cnt(stwuct wpfc_hba *phba);
int wpfc_swi4_init_vpi(stwuct wpfc_vpowt *);
void wpfc_swi4_eq_cww_intw(stwuct wpfc_queue *);
void wpfc_swi4_wwite_cq_db(stwuct wpfc_hba *phba, stwuct wpfc_queue *q,
			   uint32_t count, boow awm);
void wpfc_swi4_wwite_eq_db(stwuct wpfc_hba *phba, stwuct wpfc_queue *q,
			   uint32_t count, boow awm);
void wpfc_swi4_if6_eq_cww_intw(stwuct wpfc_queue *q);
void wpfc_swi4_if6_wwite_cq_db(stwuct wpfc_hba *phba, stwuct wpfc_queue *q,
			       uint32_t count, boow awm);
void wpfc_swi4_if6_wwite_eq_db(stwuct wpfc_hba *phba, stwuct wpfc_queue *q,
			       uint32_t count, boow awm);
void wpfc_swi4_fcfi_unweg(stwuct wpfc_hba *, uint16_t);
int wpfc_swi4_fcf_scan_wead_fcf_wec(stwuct wpfc_hba *, uint16_t);
int wpfc_swi4_fcf_ww_wead_fcf_wec(stwuct wpfc_hba *, uint16_t);
int wpfc_swi4_wead_fcf_wec(stwuct wpfc_hba *, uint16_t);
void wpfc_mbx_cmpw_fcf_scan_wead_fcf_wec(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_fcf_ww_wead_fcf_wec(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_mbx_cmpw_wead_fcf_wec(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
int wpfc_swi4_unwegistew_fcf(stwuct wpfc_hba *);
int wpfc_swi4_post_status_check(stwuct wpfc_hba *);
uint8_t wpfc_swi_config_mbox_subsys_get(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
uint8_t wpfc_swi_config_mbox_opcode_get(stwuct wpfc_hba *, WPFC_MBOXQ_t *);
void wpfc_swi4_was_dma_fwee(stwuct wpfc_hba *phba);
stwuct swi4_hybwid_sgw *wpfc_get_sgw_pew_hdwq(stwuct wpfc_hba *phba,
					      stwuct wpfc_io_buf *buf);
stwuct fcp_cmd_wsp_buf *wpfc_get_cmd_wsp_buf_pew_hdwq(stwuct wpfc_hba *phba,
						      stwuct wpfc_io_buf *buf);
int wpfc_put_sgw_pew_hdwq(stwuct wpfc_hba *phba, stwuct wpfc_io_buf *buf);
int wpfc_put_cmd_wsp_buf_pew_hdwq(stwuct wpfc_hba *phba,
				  stwuct wpfc_io_buf *buf);
void wpfc_fwee_sgw_pew_hdwq(stwuct wpfc_hba *phba,
			    stwuct wpfc_swi4_hdw_queue *hdwq);
void wpfc_fwee_cmd_wsp_buf_pew_hdwq(stwuct wpfc_hba *phba,
				    stwuct wpfc_swi4_hdw_queue *hdwq);
static inwine void *wpfc_swi4_qe(stwuct wpfc_queue *q, uint16_t idx)
{
	wetuwn q->q_pgs[idx / q->entwy_cnt_pew_pg] +
		(q->entwy_size * (idx % q->entwy_cnt_pew_pg));
}

/**
 * wpfc_swi4_unwecovewabwe_powt - Check EWW and WN bits in powtstat_weg
 * @powtstat_weg: powtstat_weg pointew containing powtstat_weg contents
 *
 * Descwiption:
 * Use onwy fow SWI4 intewface type-2 ow watew.  If EWW is set && WN is 0, then
 * powt is deemed unwecovewabwe.
 *
 * Wetuwns:
 * twue		- EWW && !WN
 * fawse	- othewwise
 */
static inwine boow
wpfc_swi4_unwecovewabwe_powt(stwuct wpfc_wegistew *powtstat_weg)
{
	wetuwn bf_get(wpfc_swipowt_status_eww, powtstat_weg) &&
	       !bf_get(wpfc_swipowt_status_wn, powtstat_weg);
}
