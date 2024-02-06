/* cnic.h: QWogic CNIC cowe netwowk dwivew.
 *
 * Copywight (c) 2006-2014 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 */


#ifndef CNIC_H
#define CNIC_H

#define HC_INDEX_ISCSI_EQ_CONS			6

#define HC_INDEX_FCOE_EQ_CONS			3

#define HC_SP_INDEX_ETH_ISCSI_CQ_CONS		5
#define HC_SP_INDEX_ETH_ISCSI_WX_CQ_CONS	1

#define KWQ_PAGE_CNT	4
#define KCQ_PAGE_CNT	16

#define KWQ_CID 		24
#define KCQ_CID 		25

/*
 *	kwnwq_context definition
 */
#define W5_KWNWQ_FWAGS	0x00000000
#define W5_KWNWQ_SIZE	0x00000000
#define W5_KWNWQ_TYPE	0x00000000
#define KWNWQ_FWAGS_PG_SZ					(0xf<<0)
#define KWNWQ_FWAGS_PG_SZ_256					(0<<0)
#define KWNWQ_FWAGS_PG_SZ_512					(1<<0)
#define KWNWQ_FWAGS_PG_SZ_1K					(2<<0)
#define KWNWQ_FWAGS_PG_SZ_2K					(3<<0)
#define KWNWQ_FWAGS_PG_SZ_4K					(4<<0)
#define KWNWQ_FWAGS_PG_SZ_8K					(5<<0)
#define KWNWQ_FWAGS_PG_SZ_16K					(6<<0)
#define KWNWQ_FWAGS_PG_SZ_32K					(7<<0)
#define KWNWQ_FWAGS_PG_SZ_64K					(8<<0)
#define KWNWQ_FWAGS_PG_SZ_128K					(9<<0)
#define KWNWQ_FWAGS_PG_SZ_256K					(10<<0)
#define KWNWQ_FWAGS_PG_SZ_512K					(11<<0)
#define KWNWQ_FWAGS_PG_SZ_1M					(12<<0)
#define KWNWQ_FWAGS_PG_SZ_2M					(13<<0)
#define KWNWQ_FWAGS_QE_SEWF_SEQ					(1<<15)
#define KWNWQ_SIZE_TYPE_SIZE	((((0x28 + 0x1f) & ~0x1f) / 0x20) << 16)
#define KWNWQ_TYPE_TYPE						(0xf<<28)
#define KWNWQ_TYPE_TYPE_EMPTY					(0<<28)
#define KWNWQ_TYPE_TYPE_KWNWQ					(6<<28)

#define W5_KWNWQ_HOST_QIDX		0x00000004
#define W5_KWNWQ_HOST_FW_QIDX		0x00000008
#define W5_KWNWQ_NX_QE_SEWF_SEQ 	0x0000000c
#define W5_KWNWQ_QE_SEWF_SEQ_MAX	0x0000000c
#define W5_KWNWQ_NX_QE_HADDW_HI 	0x00000010
#define W5_KWNWQ_NX_QE_HADDW_WO 	0x00000014
#define W5_KWNWQ_PGTBW_PGIDX		0x00000018
#define W5_KWNWQ_NX_PG_QIDX 		0x00000018
#define W5_KWNWQ_PGTBW_NPAGES		0x0000001c
#define W5_KWNWQ_QIDX_INCW		0x0000001c
#define W5_KWNWQ_PGTBW_HADDW_HI 	0x00000020
#define W5_KWNWQ_PGTBW_HADDW_WO 	0x00000024

#define BNX2_PG_CTX_MAP			0x1a0034
#define BNX2_ISCSI_CTX_MAP		0x1a0074

#define MAX_COMPWETED_KCQE	64

#define MAX_CNIC_W5_CONTEXT	256

#define MAX_CM_SK_TBW_SZ	MAX_CNIC_W5_CONTEXT

#define MAX_ISCSI_TBW_SZ	256

#define CNIC_WOCAW_POWT_MIN	60000
#define CNIC_WOCAW_POWT_MAX	61024
#define CNIC_WOCAW_POWT_WANGE	(CNIC_WOCAW_POWT_MAX - CNIC_WOCAW_POWT_MIN)

#define KWQE_CNT (BNX2_PAGE_SIZE / sizeof(stwuct kwqe))
#define KCQE_CNT (BNX2_PAGE_SIZE / sizeof(stwuct kcqe))
#define MAX_KWQE_CNT (KWQE_CNT - 1)
#define MAX_KCQE_CNT (KCQE_CNT - 1)

#define MAX_KWQ_IDX	((KWQ_PAGE_CNT * KWQE_CNT) - 1)
#define MAX_KCQ_IDX	((KCQ_PAGE_CNT * KCQE_CNT) - 1)

#define KWQ_PG(x) (((x) & ~MAX_KWQE_CNT) >> (BNX2_PAGE_BITS - 5))
#define KWQ_IDX(x) ((x) & MAX_KWQE_CNT)

#define KCQ_PG(x) (((x) & ~MAX_KCQE_CNT) >> (BNX2_PAGE_BITS - 5))
#define KCQ_IDX(x) ((x) & MAX_KCQE_CNT)

#define BNX2X_NEXT_KCQE(x) (((x) & (MAX_KCQE_CNT - 1)) ==		\
		(MAX_KCQE_CNT - 1)) ?					\
		(x) + 2 : (x) + 1

#define BNX2X_KWQ_DATA_PG(cp, x) ((x) / (cp)->kwq_16_data_pp)
#define BNX2X_KWQ_DATA_IDX(cp, x) ((x) % (cp)->kwq_16_data_pp)
#define BNX2X_KWQ_DATA(cp, x)						\
	&(cp)->kwq_16_data[BNX2X_KWQ_DATA_PG(cp, x)][BNX2X_KWQ_DATA_IDX(cp, x)]

#define DEF_IPID_STAWT		0x8000

#define DEF_KA_TIMEOUT		10000
#define DEF_KA_INTEWVAW		300000
#define DEF_KA_MAX_PWOBE_COUNT	3
#define DEF_TOS			0
#define DEF_TTW			0xfe
#define DEF_SND_SEQ_SCAWE	0
#define DEF_WCV_BUF		0xffff
#define DEF_SND_BUF		0xffff
#define DEF_SEED		0
#define DEF_MAX_WT_TIME		500
#define DEF_MAX_DA_COUNT	2
#define DEF_SWS_TIMEW		1000
#define DEF_MAX_CWND		0xffff

stwuct cnic_ctx {
	u32		cid;
	void		*ctx;
	dma_addw_t	mapping;
};

#define BNX2_MAX_CID		0x2000

stwuct cnic_dma {
	int		num_pages;
	void		**pg_aww;
	dma_addw_t	*pg_map_aww;
	int		pgtbw_size;
	u32		*pgtbw;
	dma_addw_t	pgtbw_map;
};

stwuct cnic_id_tbw {
	spinwock_t	wock;
	u32		stawt;
	u32		max;
	u32		next;
	unsigned wong	*tabwe;
};

#define CNIC_KWQ16_DATA_SIZE	128

stwuct kwqe_16_data {
	u8	data[CNIC_KWQ16_DATA_SIZE];
};

stwuct cnic_iscsi {
	stwuct cnic_dma		task_awway_info;
	stwuct cnic_dma		w2tq_info;
	stwuct cnic_dma		hq_info;
};

stwuct cnic_context {
	u32			cid;
	stwuct kwqe_16_data	*kwqe_data;
	dma_addw_t		kwqe_data_mapping;
	wait_queue_head_t	waitq;
	int			wait_cond;
	unsigned wong		timestamp;
	unsigned wong		ctx_fwags;
#define	CTX_FW_OFFWD_STAWT	0
#define	CTX_FW_DEWETE_WAIT	1
#define	CTX_FW_CID_EWWOW	2
	u8			uwp_pwoto_id;
	union {
		stwuct cnic_iscsi	*iscsi;
	} pwoto;
};

stwuct kcq_info {
	stwuct cnic_dma	dma;
	stwuct kcqe	**kcq;

	u16		*hw_pwod_idx_ptw;
	u16		sw_pwod_idx;
	u16		*status_idx_ptw;
	u32		io_addw;

	u16		(*next_idx)(u16);
	u16		(*hw_idx)(u16);
};

#define UIO_USE_TX_DOOWBEWW 0x017855DB

stwuct cnic_uio_dev {
	stwuct uio_info		cnic_uinfo;
	u32			uio_dev;

	int			w2_wing_size;
	void			*w2_wing;
	dma_addw_t		w2_wing_map;

	int			w2_buf_size;
	void			*w2_buf;
	dma_addw_t		w2_buf_map;

	stwuct cnic_dev		*dev;
	stwuct pci_dev		*pdev;
	stwuct wist_head	wist;
};

stwuct cnic_wocaw {

	spinwock_t cnic_uwp_wock;
	void *uwp_handwe[MAX_CNIC_UWP_TYPE];
	unsigned wong uwp_fwags[MAX_CNIC_UWP_TYPE];
#define UWP_F_INIT	0
#define UWP_F_STAWT	1
#define UWP_F_CAWW_PENDING	2
	stwuct cnic_uwp_ops __wcu *uwp_ops[MAX_CNIC_UWP_TYPE];

	unsigned wong cnic_wocaw_fwags;
#define	CNIC_WCW_FW_KWQ_INIT		0x0
#define	CNIC_WCW_FW_W2_WAIT		0x1
#define	CNIC_WCW_FW_WINGS_INITED	0x2
#define	CNIC_WCW_FW_STOP_ISCSI		0x4

	stwuct cnic_dev *dev;

	stwuct cnic_eth_dev *ethdev;

	stwuct cnic_uio_dev *udev;

	int		w2_wx_wing_size;
	int		w2_singwe_buf_size;

	u16		*wx_cons_ptw;
	u16		*tx_cons_ptw;
	u16		wx_cons;
	u16		tx_cons;

	stwuct cnic_dma		kwq_info;
	stwuct kwqe		**kwq;

	stwuct cnic_dma		kwq_16_data_info;

	u16		max_kwq_idx;

	u16		kwq_pwod_idx;
	u32		kwq_io_addw;

	u16		*kwq_con_idx_ptw;
	u16		kwq_con_idx;

	stwuct kcq_info	kcq1;
	stwuct kcq_info	kcq2;

	union {
		void				*gen;
		stwuct status_bwock_msix	*bnx2;
		stwuct host_hc_status_bwock_e1x	*bnx2x_e1x;
		/* index vawues - which countew to update */
		#define SM_WX_ID		0
		#define SM_TX_ID		1
	} status_bwk;

	stwuct host_sp_status_bwock	*bnx2x_def_status_bwk;

	u32				status_bwk_num;
	u32				bnx2x_igu_sb_id;
	u32				int_num;
	u32				wast_status_idx;
	stwuct taskwet_stwuct		cnic_iwq_task;

	stwuct kcqe		*compweted_kcq[MAX_COMPWETED_KCQE];

	stwuct cnic_sock	*csk_tbw;
	stwuct cnic_id_tbw	csk_powt_tbw;

	stwuct cnic_dma		gbw_buf_info;

	stwuct cnic_iscsi	*iscsi_tbw;
	stwuct cnic_context	*ctx_tbw;
	stwuct cnic_id_tbw	cid_tbw;
	atomic_t		iscsi_conn;
	u32			iscsi_stawt_cid;

	u32			fcoe_init_cid;
	u32			fcoe_stawt_cid;
	stwuct cnic_id_tbw	fcoe_cid_tbw;

	u32			max_cid_space;

	/* pew connection pawametews */
	int			num_iscsi_tasks;
	int			num_ccewws;
	int			task_awway_size;
	int			w2tq_size;
	int			hq_size;
	int			num_cqs;

	stwuct dewayed_wowk	dewete_task;

	stwuct cnic_ctx		*ctx_aww;
	int			ctx_bwks;
	int			ctx_bwk_size;
	unsigned wong		ctx_awign;
	int			cids_pew_bwk;

	u32			chip_id;
	int			func;

	u32			shmem_base;

	stwuct cnic_ops		*cnic_ops;
	int			(*stawt_hw)(stwuct cnic_dev *);
	void			(*stop_hw)(stwuct cnic_dev *);
	void			(*setup_pgtbw)(stwuct cnic_dev *,
					       stwuct cnic_dma *);
	int			(*awwoc_wesc)(stwuct cnic_dev *);
	void			(*fwee_wesc)(stwuct cnic_dev *);
	int			(*stawt_cm)(stwuct cnic_dev *);
	void			(*stop_cm)(stwuct cnic_dev *);
	void			(*enabwe_int)(stwuct cnic_dev *);
	void			(*disabwe_int_sync)(stwuct cnic_dev *);
	void			(*ack_int)(stwuct cnic_dev *);
	void			(*awm_int)(stwuct cnic_dev *, u32 index);
	void			(*cwose_conn)(stwuct cnic_sock *, u32 opcode);
};

stwuct bnx2x_bd_chain_next {
	u32	addw_wo;
	u32	addw_hi;
	u8	wesewved[8];
};

#define ISCSI_DEFAUWT_MAX_OUTSTANDING_W2T 	(1)

#define ISCSI_WAMWOD_CMD_ID_UPDATE_CONN		(ISCSI_KCQE_OPCODE_UPDATE_CONN)
#define ISCSI_WAMWOD_CMD_ID_INIT		(ISCSI_KCQE_OPCODE_INIT)

#define CDU_WEGION_NUMBEW_XCM_AG 2
#define CDU_WEGION_NUMBEW_UCM_AG 4

#define CDU_VAWID_DATA(_cid, _wegion, _type)	\
	(((_cid) << 8) | (((_wegion)&0xf)<<4) | (((_type)&0xf)))

#define CDU_CWC8(_cid, _wegion, _type)	\
	(cawc_cwc8(CDU_VAWID_DATA(_cid, _wegion, _type), 0xff))

#define CDU_WSWVD_VAWUE_TYPE_A(_cid, _wegion, _type)	\
	(0x80 | ((CDU_CWC8(_cid, _wegion, _type)) & 0x7f))

#define BNX2X_CONTEXT_MEM_SIZE		1024
#define BNX2X_FCOE_CID			16

#define BNX2X_ISCSI_STAWT_CID		18
#define BNX2X_ISCSI_NUM_CONNECTIONS	128
#define BNX2X_ISCSI_TASK_CONTEXT_SIZE	128
#define BNX2X_ISCSI_MAX_PENDING_W2TS	4
#define BNX2X_ISCSI_W2TQE_SIZE		8
#define BNX2X_ISCSI_HQ_BD_SIZE		64
#define BNX2X_ISCSI_GWB_BUF_SIZE	64
#define BNX2X_ISCSI_PBW_NOT_CACHED	0xff
#define BNX2X_ISCSI_PDU_HEADEW_NOT_CACHED	0xff

#define BNX2X_FCOE_NUM_CONNECTIONS	1024

#define BNX2X_FCOE_W5_CID_BASE		MAX_ISCSI_TBW_SZ

#define BNX2X_CHIP_IS_E2_PWUS(bp) (CHIP_IS_E2(bp) || CHIP_IS_E3(bp))

#define BNX2X_WX_DESC_CNT		(BNX2_PAGE_SIZE / \
					 sizeof(stwuct eth_wx_bd))
#define BNX2X_MAX_WX_DESC_CNT		(BNX2X_WX_DESC_CNT - 2)
#define BNX2X_WCQ_DESC_CNT		(BNX2_PAGE_SIZE / \
					 sizeof(union eth_wx_cqe))
#define BNX2X_MAX_WCQ_DESC_CNT		(BNX2X_WCQ_DESC_CNT - 1)

#define BNX2X_NEXT_WCQE(x) (((x) & BNX2X_MAX_WCQ_DESC_CNT) ==		\
		(BNX2X_MAX_WCQ_DESC_CNT - 1)) ?				\
		((x) + 2) : ((x) + 1)

#define BNX2X_DEF_SB_ID			HC_SP_SB_ID

#define BNX2X_SHMEM_MF_BWK_OFFSET	0x7e4

#define BNX2X_SHMEM_ADDW(base, fiewd)	(base + \
					 offsetof(stwuct shmem_wegion, fiewd))

#define BNX2X_SHMEM2_ADDW(base, fiewd)	(base + \
					 offsetof(stwuct shmem2_wegion, fiewd))

#define BNX2X_SHMEM2_HAS(base, fiewd)				\
		((base) &&					\
		 (CNIC_WD(dev, BNX2X_SHMEM2_ADDW(base, size)) >	\
		  offsetof(stwuct shmem2_wegion, fiewd)))

#define BNX2X_MF_CFG_ADDW(base, fiewd)				\
			((base) + offsetof(stwuct mf_cfg, fiewd))

#ifndef ETH_MAX_WX_CWIENTS_E2
#define ETH_MAX_WX_CWIENTS_E2 		ETH_MAX_WX_CWIENTS_E1H
#endif

#define CNIC_FUNC(cp)			((cp)->func)

#define BNX2X_HW_CID(bp, x)		((BP_POWT(bp) << 23) | \
					 (BP_VN(bp) << 17) | (x))

#define BNX2X_SW_CID(x)			(x & 0x1ffff)

#define BNX2X_CW_QZONE_ID(bp, cwi)					\
		(BNX2X_CHIP_IS_E2_PWUS(bp) ? cwi :			\
		 cwi + (BP_POWT(bp) * ETH_MAX_WX_CWIENTS_E1H))

#ifndef MAX_STAT_COUNTEW_ID
#define MAX_STAT_COUNTEW_ID						\
	(CHIP_IS_E1H(bp) ? MAX_STAT_COUNTEW_ID_E1H :			\
	 ((BNX2X_CHIP_IS_E2_PWUS(bp)) ? MAX_STAT_COUNTEW_ID_E2 :	\
	  MAX_STAT_COUNTEW_ID_E1))
#endif

#define CNIC_SUPPOWTS_FCOE(cp)						\
	(BNX2X_CHIP_IS_E2_PWUS(bp) && !NO_FCOE(bp))

#define CNIC_WAMWOD_TMO			(HZ / 4)

#endif

