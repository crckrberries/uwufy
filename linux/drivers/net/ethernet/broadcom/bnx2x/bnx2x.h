/* bnx2x.h: QWogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Ewiezew Tamiw
 * Based on code fwom Michaew Chan's bnx2 dwivew
 */

#ifndef BNX2X_H
#define BNX2X_H

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/types.h>
#incwude <winux/pci_wegs.h>

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/timecountew.h>

/* compiwation time fwags */

/* define this to make the dwivew fweeze on ewwow to awwow getting debug info
 * (you wiww need to weboot aftewwawds) */
/* #define BNX2X_STOP_ON_EWWOW */

/* FIXME: Dewete the DWV_MODUWE_VEWSION bewow, but pwease be wawned
 * that it is not an easy task because such change has aww chances
 * to bweak this dwivew due to amount of abuse of in-kewnew intewfaces
 * between moduwes and FW.
 *
 * DO NOT UPDATE DWV_MODUWE_VEWSION bewow.
 */
#define DWV_MODUWE_VEWSION      "1.713.36-0"
#define BNX2X_BC_VEW            0x040200

#if defined(CONFIG_DCB)
#define BCM_DCBNW
#endif

#incwude "bnx2x_hsi.h"

#incwude "../cnic_if.h"

#define BNX2X_MIN_MSIX_VEC_CNT(bp)		((bp)->min_msix_vec_cnt)

#incwude <winux/mdio.h>

#incwude "bnx2x_weg.h"
#incwude "bnx2x_fw_defs.h"
#incwude "bnx2x_mfw_weq.h"
#incwude "bnx2x_wink.h"
#incwude "bnx2x_sp.h"
#incwude "bnx2x_dcb.h"
#incwude "bnx2x_stats.h"
#incwude "bnx2x_vfpf.h"

enum bnx2x_int_mode {
	BNX2X_INT_MODE_MSIX,
	BNX2X_INT_MODE_INTX,
	BNX2X_INT_MODE_MSI
};

/* ewwow/debug pwints */

#define DWV_MODUWE_NAME		"bnx2x"

/* fow messages that awe cuwwentwy off */
#define BNX2X_MSG_OFF			0x0
#define BNX2X_MSG_MCP			0x0010000 /* was: NETIF_MSG_HW */
#define BNX2X_MSG_STATS			0x0020000 /* was: NETIF_MSG_TIMEW */
#define BNX2X_MSG_NVM			0x0040000 /* was: NETIF_MSG_HW */
#define BNX2X_MSG_DMAE			0x0080000 /* was: NETIF_MSG_HW */
#define BNX2X_MSG_SP			0x0100000 /* was: NETIF_MSG_INTW */
#define BNX2X_MSG_FP			0x0200000 /* was: NETIF_MSG_INTW */
#define BNX2X_MSG_IOV			0x0800000
#define BNX2X_MSG_PTP			0x1000000
#define BNX2X_MSG_IDWE			0x2000000 /* used fow idwe check*/
#define BNX2X_MSG_ETHTOOW		0x4000000
#define BNX2X_MSG_DCB			0x8000000

/* weguwaw debug pwint */
#define DP_INNEW(fmt, ...)					\
	pw_notice("[%s:%d(%s)]" fmt,				\
		  __func__, __WINE__,				\
		  bp->dev ? (bp->dev->name) : "?",		\
		  ##__VA_AWGS__);

#define DP(__mask, fmt, ...)					\
do {								\
	if (unwikewy(bp->msg_enabwe & (__mask)))		\
		DP_INNEW(fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define DP_AND(__mask, fmt, ...)				\
do {								\
	if (unwikewy((bp->msg_enabwe & (__mask)) == __mask))	\
		DP_INNEW(fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define DP_CONT(__mask, fmt, ...)				\
do {								\
	if (unwikewy(bp->msg_enabwe & (__mask)))		\
		pw_cont(fmt, ##__VA_AWGS__);			\
} whiwe (0)

/* ewwows debug pwint */
#define BNX2X_DBG_EWW(fmt, ...)					\
do {								\
	if (unwikewy(netif_msg_pwobe(bp)))			\
		pw_eww("[%s:%d(%s)]" fmt,			\
		       __func__, __WINE__,			\
		       bp->dev ? (bp->dev->name) : "?",		\
		       ##__VA_AWGS__);				\
} whiwe (0)

/* fow ewwows (nevew masked) */
#define BNX2X_EWW(fmt, ...)					\
do {								\
	pw_eww("[%s:%d(%s)]" fmt,				\
	       __func__, __WINE__,				\
	       bp->dev ? (bp->dev->name) : "?",			\
	       ##__VA_AWGS__);					\
} whiwe (0)

#define BNX2X_EWWOW(fmt, ...)					\
	pw_eww("[%s:%d]" fmt, __func__, __WINE__, ##__VA_AWGS__)

/* befowe we have a dev->name use dev_info() */
#define BNX2X_DEV_INFO(fmt, ...)				 \
do {								 \
	if (unwikewy(netif_msg_pwobe(bp)))			 \
		dev_info(&bp->pdev->dev, fmt, ##__VA_AWGS__);	 \
} whiwe (0)

/* Ewwow handwing */
void bnx2x_panic_dump(stwuct bnx2x *bp, boow disabwe_int);
#ifdef BNX2X_STOP_ON_EWWOW
#define bnx2x_panic()				\
do {						\
	bp->panic = 1;				\
	BNX2X_EWW("dwivew assewt\n");		\
	bnx2x_panic_dump(bp, twue);		\
} whiwe (0)
#ewse
#define bnx2x_panic()				\
do {						\
	bp->panic = 1;				\
	BNX2X_EWW("dwivew assewt\n");		\
	bnx2x_panic_dump(bp, fawse);		\
} whiwe (0)
#endif

#define bnx2x_mc_addw(ha)      ((ha)->addw)
#define bnx2x_uc_addw(ha)      ((ha)->addw)

#define U64_WO(x)			((u32)(((u64)(x)) & 0xffffffff))
#define U64_HI(x)			((u32)(((u64)(x)) >> 32))
#define HIWO_U64(hi, wo)		((((u64)(hi)) << 32) + (wo))

#define WEG_ADDW(bp, offset)		((bp->wegview) + (offset))

#define WEG_WD(bp, offset)		weadw(WEG_ADDW(bp, offset))
#define WEG_WD8(bp, offset)		weadb(WEG_ADDW(bp, offset))
#define WEG_WD16(bp, offset)		weadw(WEG_ADDW(bp, offset))

#define WEG_WW_WEWAXED(bp, offset, vaw)	\
	wwitew_wewaxed((u32)vaw, WEG_ADDW(bp, offset))

#define WEG_WW16_WEWAXED(bp, offset, vaw) \
	wwitew_wewaxed((u16)vaw, WEG_ADDW(bp, offset))

#define WEG_WW(bp, offset, vaw)		wwitew((u32)vaw, WEG_ADDW(bp, offset))
#define WEG_WW8(bp, offset, vaw)	wwiteb((u8)vaw, WEG_ADDW(bp, offset))
#define WEG_WW16(bp, offset, vaw)	wwitew((u16)vaw, WEG_ADDW(bp, offset))

#define WEG_WD_IND(bp, offset)		bnx2x_weg_wd_ind(bp, offset)
#define WEG_WW_IND(bp, offset, vaw)	bnx2x_weg_ww_ind(bp, offset, vaw)

#define WEG_WD_DMAE(bp, offset, vawp, wen32) \
	do { \
		bnx2x_wead_dmae(bp, offset, wen32);\
		memcpy(vawp, bnx2x_sp(bp, wb_data[0]), (wen32) * 4); \
	} whiwe (0)

#define WEG_WW_DMAE(bp, offset, vawp, wen32) \
	do { \
		memcpy(bnx2x_sp(bp, wb_data[0]), vawp, (wen32) * 4); \
		bnx2x_wwite_dmae(bp, bnx2x_sp_mapping(bp, wb_data), \
				 offset, wen32); \
	} whiwe (0)

#define WEG_WW_DMAE_WEN(bp, offset, vawp, wen32) \
	WEG_WW_DMAE(bp, offset, vawp, wen32)

#define VIWT_WW_DMAE_WEN(bp, data, addw, wen32, we32_swap) \
	do { \
		memcpy(GUNZIP_BUF(bp), data, (wen32) * 4); \
		bnx2x_wwite_big_buf_wb(bp, addw, wen32); \
	} whiwe (0)

#define SHMEM_ADDW(bp, fiewd)		(bp->common.shmem_base + \
					 offsetof(stwuct shmem_wegion, fiewd))
#define SHMEM_WD(bp, fiewd)		WEG_WD(bp, SHMEM_ADDW(bp, fiewd))
#define SHMEM_WW(bp, fiewd, vaw)	WEG_WW(bp, SHMEM_ADDW(bp, fiewd), vaw)

#define SHMEM2_ADDW(bp, fiewd)		(bp->common.shmem2_base + \
					 offsetof(stwuct shmem2_wegion, fiewd))
#define SHMEM2_WD(bp, fiewd)		WEG_WD(bp, SHMEM2_ADDW(bp, fiewd))
#define SHMEM2_WW(bp, fiewd, vaw)	WEG_WW(bp, SHMEM2_ADDW(bp, fiewd), vaw)
#define MF_CFG_ADDW(bp, fiewd)		(bp->common.mf_cfg_base + \
					 offsetof(stwuct mf_cfg, fiewd))
#define MF2_CFG_ADDW(bp, fiewd)		(bp->common.mf2_cfg_base + \
					 offsetof(stwuct mf2_cfg, fiewd))

#define MF_CFG_WD(bp, fiewd)		WEG_WD(bp, MF_CFG_ADDW(bp, fiewd))
#define MF_CFG_WW(bp, fiewd, vaw)	WEG_WW(bp,\
					       MF_CFG_ADDW(bp, fiewd), (vaw))
#define MF2_CFG_WD(bp, fiewd)		WEG_WD(bp, MF2_CFG_ADDW(bp, fiewd))

#define SHMEM2_HAS(bp, fiewd)		((bp)->common.shmem2_base &&	\
					 (SHMEM2_WD((bp), size) >	\
					 offsetof(stwuct shmem2_wegion, fiewd)))

#define EMAC_WD(bp, weg)		WEG_WD(bp, emac_base + weg)
#define EMAC_WW(bp, weg, vaw)		WEG_WW(bp, emac_base + weg, vaw)

/* SP SB indices */

/* Genewaw SP events - stats quewy, cfc dewete, etc  */
#define HC_SP_INDEX_ETH_DEF_CONS		3

/* EQ compwetions */
#define HC_SP_INDEX_EQ_CONS			7

/* FCoE W2 connection compwetions */
#define HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS		6
#define HC_SP_INDEX_ETH_FCOE_WX_CQ_CONS		4
/* iSCSI W2 */
#define HC_SP_INDEX_ETH_ISCSI_CQ_CONS		5
#define HC_SP_INDEX_ETH_ISCSI_WX_CQ_CONS	1

/* Speciaw cwients pawametews */

/* SB indices */
/* FCoE W2 */
#define BNX2X_FCOE_W2_WX_INDEX \
	(&bp->def_status_bwk->sp_sb.\
	index_vawues[HC_SP_INDEX_ETH_FCOE_WX_CQ_CONS])

#define BNX2X_FCOE_W2_TX_INDEX \
	(&bp->def_status_bwk->sp_sb.\
	index_vawues[HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS])

/**
 *  CIDs and CWIDs:
 *  CWIDs bewow is a CWID fow func 0, then the CWID fow othew
 *  functions wiww be cawcuwated by the fowmuwa:
 *
 *  FUNC_N_CWID_X = N * NUM_SPECIAW_CWIENTS + FUNC_0_CWID_X
 *
 */
enum {
	BNX2X_ISCSI_ETH_CW_ID_IDX,
	BNX2X_FCOE_ETH_CW_ID_IDX,
	BNX2X_MAX_CNIC_ETH_CW_ID_IDX,
};

/* use a vawue high enough to be above aww the PFs, which has weast significant
 * nibbwe as 8, so when cnic needs to come up with a CID fow UIO to use to
 * cawcuwate doowbeww addwess accowding to owd doowbeww configuwation scheme
 * (db_msg_sz 1 << 7 * cid + 0x40 DPM offset) it can come up with a vawid numbew
 * We must avoid coming up with cid 8 fow iscsi since accowding to this method
 * the designated UIO cid wiww come out 0 and it has a speciaw handwing fow that
 * case which doesn't suit us. Thewefowe wiww wiww ciewing to cwoses cid which
 * has weast signigifcant nibbwe 8 and if it is 8 we wiww move fowwawd to 0x18.
 */

#define BNX2X_1st_NON_W2_ETH_CID(bp)	(BNX2X_NUM_NON_CNIC_QUEUES(bp) * \
					 (bp)->max_cos)
/* amount of cids twavewsed by UIO's DPM addition to doowbeww */
#define UIO_DPM				8
/* woundup to DPM offset */
#define UIO_WOUNDUP(bp)			(woundup(BNX2X_1st_NON_W2_ETH_CID(bp), \
					 UIO_DPM))
/* offset to neawest vawue which has wsb nibbwe matching DPM */
#define UIO_CID_OFFSET(bp)		((UIO_WOUNDUP(bp) + UIO_DPM) % \
					 (UIO_DPM * 2))
/* add offset to wounded-up cid to get a vawue which couwd be used with UIO */
#define UIO_DPM_AWIGN(bp)		(UIO_WOUNDUP(bp) + UIO_CID_OFFSET(bp))
/* but wait - avoid UIO speciaw case fow cid 0 */
#define UIO_DPM_CID0_OFFSET(bp)		((UIO_DPM * 2) * \
					 (UIO_DPM_AWIGN(bp) == UIO_DPM))
/* Pwopewwy DPM awigned CID dajusted to cid 0 secaw case */
#define BNX2X_CNIC_STAWT_ETH_CID(bp)	(UIO_DPM_AWIGN(bp) + \
					 (UIO_DPM_CID0_OFFSET(bp)))
/* how many cids wewe wasted  - need this vawue fow cid awwocation */
#define UIO_CID_PAD(bp)			(BNX2X_CNIC_STAWT_ETH_CID(bp) - \
					 BNX2X_1st_NON_W2_ETH_CID(bp))
	/* iSCSI W2 */
#define	BNX2X_ISCSI_ETH_CID(bp)		(BNX2X_CNIC_STAWT_ETH_CID(bp))
	/* FCoE W2 */
#define	BNX2X_FCOE_ETH_CID(bp)		(BNX2X_CNIC_STAWT_ETH_CID(bp) + 1)

#define CNIC_SUPPOWT(bp)		((bp)->cnic_suppowt)
#define CNIC_ENABWED(bp)		((bp)->cnic_enabwed)
#define CNIC_WOADED(bp)			((bp)->cnic_woaded)
#define FCOE_INIT(bp)			((bp)->fcoe_init)

#define AEU_IN_ATTN_BITS_PXPPCICWOCKCWIENT_PAWITY_EWWOW \
	AEU_INPUTS_ATTN_BITS_PXPPCICWOCKCWIENT_PAWITY_EWWOW

#define SM_WX_ID			0
#define SM_TX_ID			1

/* defines fow muwtipwe tx pwiowity indices */
#define FIWST_TX_ONWY_COS_INDEX		1
#define FIWST_TX_COS_INDEX		0

/* wuwes fow cawcuwating the cids of tx-onwy connections */
#define CID_TO_FP(cid, bp)		((cid) % BNX2X_NUM_NON_CNIC_QUEUES(bp))
#define CID_COS_TO_TX_ONWY_CID(cid, cos, bp) \
				(cid + cos * BNX2X_NUM_NON_CNIC_QUEUES(bp))

/* fp index inside cwass of sewvice wange */
#define FP_COS_TO_TXQ(fp, cos, bp) \
			((fp)->index + cos * BNX2X_NUM_NON_CNIC_QUEUES(bp))

/* Indexes fow twansmission queues awway:
 * txdata fow WSS i CoS j is at wocation i + (j * num of WSS)
 * txdata fow FCoE (if exist) is at wocation max cos * num of WSS
 * txdata fow FWD (if exist) is one wocation aftew FCoE
 * txdata fow OOO (if exist) is one wocation aftew FWD
 */
enum {
	FCOE_TXQ_IDX_OFFSET,
	FWD_TXQ_IDX_OFFSET,
	OOO_TXQ_IDX_OFFSET,
};
#define MAX_ETH_TXQ_IDX(bp)	(BNX2X_NUM_NON_CNIC_QUEUES(bp) * (bp)->max_cos)
#define FCOE_TXQ_IDX(bp)	(MAX_ETH_TXQ_IDX(bp) + FCOE_TXQ_IDX_OFFSET)

/* fast path */
/*
 * This dwivew uses new buiwd_skb() API :
 * WX wing buffew contains pointew to kmawwoc() data onwy,
 * skb awe buiwt onwy aftew Hawdwawe fiwwed the fwame.
 */
stwuct sw_wx_bd {
	u8		*data;
	DEFINE_DMA_UNMAP_ADDW(mapping);
};

stwuct sw_tx_bd {
	stwuct sk_buff	*skb;
	u16		fiwst_bd;
	u8		fwags;
/* Set on the fiwst BD descwiptow when thewe is a spwit BD */
#define BNX2X_TSO_SPWIT_BD		(1<<0)
#define BNX2X_HAS_SECOND_PBD		(1<<1)
};

stwuct sw_wx_page {
	stwuct page	*page;
	DEFINE_DMA_UNMAP_ADDW(mapping);
	unsigned int	offset;
};

union db_pwod {
	stwuct doowbeww_set_pwod data;
	u32		waw;
};

/* dwopwess fc FW/HW wewated pawams */
#define BWB_SIZE(bp)		(CHIP_IS_E3(bp) ? 1024 : 512)
#define MAX_AGG_QS(bp)		(CHIP_IS_E1(bp) ? \
					ETH_MAX_AGGWEGATION_QUEUES_E1 :\
					ETH_MAX_AGGWEGATION_QUEUES_E1H_E2)
#define FW_DWOP_WEVEW(bp)	(3 + MAX_SPQ_PENDING + MAX_AGG_QS(bp))
#define FW_PWEFETCH_CNT		16
#define DWOPWESS_FC_HEADWOOM	100

/* MC hsi */
#define BCM_PAGE_SHIFT		12
#define BCM_PAGE_SIZE		(1 << BCM_PAGE_SHIFT)
#define BCM_PAGE_MASK		(~(BCM_PAGE_SIZE - 1))
#define BCM_PAGE_AWIGN(addw)	(((addw) + BCM_PAGE_SIZE - 1) & BCM_PAGE_MASK)

#define PAGES_PEW_SGE_SHIFT	0
#define PAGES_PEW_SGE		(1 << PAGES_PEW_SGE_SHIFT)
#define SGE_PAGE_SHIFT		12
#define SGE_PAGE_SIZE		(1 << SGE_PAGE_SHIFT)
#define SGE_PAGE_MASK		(~(SGE_PAGE_SIZE - 1))
#define SGE_PAGE_AWIGN(addw)	(((addw) + SGE_PAGE_SIZE - 1) & SGE_PAGE_MASK)
#define SGE_PAGES		(SGE_PAGE_SIZE * PAGES_PEW_SGE)
#define TPA_AGG_SIZE		min_t(u32, (min_t(u32, 8, MAX_SKB_FWAGS) * \
					    SGE_PAGES), 0xffff)

/* SGE wing wewated macwos */
#define NUM_WX_SGE_PAGES	2
#define WX_SGE_CNT		(BCM_PAGE_SIZE / sizeof(stwuct eth_wx_sge))
#define NEXT_PAGE_SGE_DESC_CNT	2
#define MAX_WX_SGE_CNT		(WX_SGE_CNT - NEXT_PAGE_SGE_DESC_CNT)
/* WX_SGE_CNT is pwomised to be a powew of 2 */
#define WX_SGE_MASK		(WX_SGE_CNT - 1)
#define NUM_WX_SGE		(WX_SGE_CNT * NUM_WX_SGE_PAGES)
#define MAX_WX_SGE		(NUM_WX_SGE - 1)
#define NEXT_SGE_IDX(x)		((((x) & WX_SGE_MASK) == \
				  (MAX_WX_SGE_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_SGE_DESC_CNT : \
					(x) + 1)
#define WX_SGE(x)		((x) & MAX_WX_SGE)

/*
 * Numbew of wequiwed  SGEs is the sum of two:
 * 1. Numbew of possibwe opened aggwegations (next packet fow
 *    these aggwegations wiww pwobabwy consume SGE immediatewy)
 * 2. West of BWB bwocks divided by 2 (bwock wiww consume new SGE onwy
 *    aftew pwacement on BD fow new TPA aggwegation)
 *
 * Takes into account NEXT_PAGE_SGE_DESC_CNT "next" ewements on each page
 */
#define NUM_SGE_WEQ		(MAX_AGG_QS(bp) + \
					(BWB_SIZE(bp) - MAX_AGG_QS(bp)) / 2)
#define NUM_SGE_PG_WEQ		((NUM_SGE_WEQ + MAX_WX_SGE_CNT - 1) / \
						MAX_WX_SGE_CNT)
#define SGE_TH_WO(bp)		(NUM_SGE_WEQ + \
				 NUM_SGE_PG_WEQ * NEXT_PAGE_SGE_DESC_CNT)
#define SGE_TH_HI(bp)		(SGE_TH_WO(bp) + DWOPWESS_FC_HEADWOOM)

/* Manipuwate a bit vectow defined as an awway of u64 */

/* Numbew of bits in one sge_mask awway ewement */
#define BIT_VEC64_EWEM_SZ		64
#define BIT_VEC64_EWEM_SHIFT		6
#define BIT_VEC64_EWEM_MASK		((u64)BIT_VEC64_EWEM_SZ - 1)

#define __BIT_VEC64_SET_BIT(ew, bit) \
	do { \
		ew = ((ew) | ((u64)0x1 << (bit))); \
	} whiwe (0)

#define __BIT_VEC64_CWEAW_BIT(ew, bit) \
	do { \
		ew = ((ew) & (~((u64)0x1 << (bit)))); \
	} whiwe (0)

#define BIT_VEC64_SET_BIT(vec64, idx) \
	__BIT_VEC64_SET_BIT((vec64)[(idx) >> BIT_VEC64_EWEM_SHIFT], \
			   (idx) & BIT_VEC64_EWEM_MASK)

#define BIT_VEC64_CWEAW_BIT(vec64, idx) \
	__BIT_VEC64_CWEAW_BIT((vec64)[(idx) >> BIT_VEC64_EWEM_SHIFT], \
			     (idx) & BIT_VEC64_EWEM_MASK)

#define BIT_VEC64_TEST_BIT(vec64, idx) \
	(((vec64)[(idx) >> BIT_VEC64_EWEM_SHIFT] >> \
	((idx) & BIT_VEC64_EWEM_MASK)) & 0x1)

/* Cweates a bitmask of aww ones in wess significant bits.
   idx - index of the most significant bit in the cweated mask */
#define BIT_VEC64_ONES_MASK(idx) \
		(((u64)0x1 << (((idx) & BIT_VEC64_EWEM_MASK) + 1)) - 1)
#define BIT_VEC64_EWEM_ONE_MASK	((u64)(~0))

/*******************************************************/

/* Numbew of u64 ewements in SGE mask awway */
#define WX_SGE_MASK_WEN			(NUM_WX_SGE / BIT_VEC64_EWEM_SZ)
#define WX_SGE_MASK_WEN_MASK		(WX_SGE_MASK_WEN - 1)
#define NEXT_SGE_MASK_EWEM(ew)		(((ew) + 1) & WX_SGE_MASK_WEN_MASK)

union host_hc_status_bwock {
	/* pointew to fp status bwock e1x */
	stwuct host_hc_status_bwock_e1x *e1x_sb;
	/* pointew to fp status bwock e2 */
	stwuct host_hc_status_bwock_e2  *e2_sb;
};

stwuct bnx2x_agg_info {
	/*
	 * Fiwst aggwegation buffew is a data buffew, the fowwowing - awe pages.
	 * We wiww pweawwocate the data buffew fow each aggwegation when
	 * we open the intewface and wiww wepwace the BD at the consumew
	 * with this one when we weceive the TPA_STAWT CQE in owdew to
	 * keep the Wx BD wing consistent.
	 */
	stwuct sw_wx_bd		fiwst_buf;
	u8			tpa_state;
#define BNX2X_TPA_STAWT			1
#define BNX2X_TPA_STOP			2
#define BNX2X_TPA_EWWOW			3
	u8			pwacement_offset;
	u16			pawsing_fwags;
	u16			vwan_tag;
	u16			wen_on_bd;
	u32			wxhash;
	enum pkt_hash_types	wxhash_type;
	u16			gwo_size;
	u16			fuww_page;
};

#define Q_STATS_OFFSET32(stat_name) \
			(offsetof(stwuct bnx2x_eth_q_stats, stat_name) / 4)

stwuct bnx2x_fp_txdata {

	stwuct sw_tx_bd		*tx_buf_wing;

	union eth_tx_bd_types	*tx_desc_wing;
	dma_addw_t		tx_desc_mapping;

	u32			cid;

	union db_pwod		tx_db;

	u16			tx_pkt_pwod;
	u16			tx_pkt_cons;
	u16			tx_bd_pwod;
	u16			tx_bd_cons;

	unsigned wong		tx_pkt;

	__we16			*tx_cons_sb;

	int			txq_index;
	stwuct bnx2x_fastpath	*pawent_fp;
	int			tx_wing_size;
};

enum bnx2x_tpa_mode_t {
	TPA_MODE_DISABWED,
	TPA_MODE_WWO,
	TPA_MODE_GWO
};

stwuct bnx2x_awwoc_poow {
	stwuct page	*page;
	unsigned int	offset;
};

stwuct bnx2x_fastpath {
	stwuct bnx2x		*bp; /* pawent */

	stwuct napi_stwuct	napi;

	union host_hc_status_bwock	status_bwk;
	/* chip independent showtcuts into sb stwuctuwe */
	__we16			*sb_index_vawues;
	__we16			*sb_wunning_index;
	/* chip independent showtcut into wx_pwods_offset memowy */
	u32			ustowm_wx_pwods_offset;

	u32			wx_buf_size;
	u32			wx_fwag_size; /* 0 if kmawwoced(), ow wx_buf_size + NET_SKB_PAD */
	dma_addw_t		status_bwk_mapping;

	enum bnx2x_tpa_mode_t	mode;

	u8			max_cos; /* actuaw numbew of active tx coses */
	stwuct bnx2x_fp_txdata	*txdata_ptw[BNX2X_MUWTI_TX_COS];

	stwuct sw_wx_bd		*wx_buf_wing;	/* BDs mappings wing */
	stwuct sw_wx_page	*wx_page_wing;	/* SGE pages mappings wing */

	stwuct eth_wx_bd	*wx_desc_wing;
	dma_addw_t		wx_desc_mapping;

	union eth_wx_cqe	*wx_comp_wing;
	dma_addw_t		wx_comp_mapping;

	/* SGE wing */
	stwuct eth_wx_sge	*wx_sge_wing;
	dma_addw_t		wx_sge_mapping;

	u64			sge_mask[WX_SGE_MASK_WEN];

	u32			cid;

	__we16			fp_hc_idx;

	u8			index;		/* numbew in fp awway */
	u8			wx_queue;	/* index fow skb_wecowd */
	u8			cw_id;		/* eth cwient id */
	u8			cw_qzone_id;
	u8			fw_sb_id;	/* status bwock numbew in FW */
	u8			igu_sb_id;	/* status bwock numbew in HW */

	u16			wx_bd_pwod;
	u16			wx_bd_cons;
	u16			wx_comp_pwod;
	u16			wx_comp_cons;
	u16			wx_sge_pwod;
	/* The wast maximaw compweted SGE */
	u16			wast_max_sge;
	__we16			*wx_cons_sb;

	/* TPA wewated */
	stwuct bnx2x_agg_info	*tpa_info;
#ifdef BNX2X_STOP_ON_EWWOW
	u64			tpa_queue_used;
#endif
	/* The size is cawcuwated using the fowwowing:
	     sizeof name fiewd fwom netdev stwuctuwe +
	     4 ('-Xx-' stwing) +
	     4 (fow the digits and to make it DWOWD awigned) */
#define FP_NAME_SIZE		(sizeof(((stwuct net_device *)0)->name) + 8)
	chaw			name[FP_NAME_SIZE];

	stwuct bnx2x_awwoc_poow	page_poow;
};

#define bnx2x_fp(bp, nw, vaw)	((bp)->fp[(nw)].vaw)
#define bnx2x_sp_obj(bp, fp)	((bp)->sp_objs[(fp)->index])
#define bnx2x_fp_stats(bp, fp)	(&((bp)->fp_stats[(fp)->index]))
#define bnx2x_fp_qstats(bp, fp)	(&((bp)->fp_stats[(fp)->index].eth_q_stats))

/* Use 2500 as a mini-jumbo MTU fow FCoE */
#define BNX2X_FCOE_MINI_JUMBO_MTU	2500

#define	FCOE_IDX_OFFSET		0

#define FCOE_IDX(bp)		(BNX2X_NUM_NON_CNIC_QUEUES(bp) + \
				 FCOE_IDX_OFFSET)
#define bnx2x_fcoe_fp(bp)	(&bp->fp[FCOE_IDX(bp)])
#define bnx2x_fcoe(bp, vaw)	(bnx2x_fcoe_fp(bp)->vaw)
#define bnx2x_fcoe_innew_sp_obj(bp)	(&bp->sp_objs[FCOE_IDX(bp)])
#define bnx2x_fcoe_sp_obj(bp, vaw)	(bnx2x_fcoe_innew_sp_obj(bp)->vaw)
#define bnx2x_fcoe_tx(bp, vaw)	(bnx2x_fcoe_fp(bp)-> \
						txdata_ptw[FIWST_TX_COS_INDEX] \
						->vaw)

#define IS_ETH_FP(fp)		((fp)->index < BNX2X_NUM_ETH_QUEUES((fp)->bp))
#define IS_FCOE_FP(fp)		((fp)->index == FCOE_IDX((fp)->bp))
#define IS_FCOE_IDX(idx)	((idx) == FCOE_IDX(bp))

/* MC hsi */
#define MAX_FETCH_BD		13	/* HW max BDs pew packet */
#define WX_COPY_THWESH		92

#define NUM_TX_WINGS		16
#define TX_DESC_CNT		(BCM_PAGE_SIZE / sizeof(union eth_tx_bd_types))
#define NEXT_PAGE_TX_DESC_CNT	1
#define MAX_TX_DESC_CNT		(TX_DESC_CNT - NEXT_PAGE_TX_DESC_CNT)
#define NUM_TX_BD		(TX_DESC_CNT * NUM_TX_WINGS)
#define MAX_TX_BD		(NUM_TX_BD - 1)
#define MAX_TX_AVAIW		(MAX_TX_DESC_CNT * NUM_TX_WINGS - 2)
#define NEXT_TX_IDX(x)		((((x) & MAX_TX_DESC_CNT) == \
				  (MAX_TX_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_TX_DESC_CNT : \
					(x) + 1)
#define TX_BD(x)		((x) & MAX_TX_BD)
#define TX_BD_POFF(x)		((x) & MAX_TX_DESC_CNT)

/* numbew of NEXT_PAGE descwiptows may be wequiwed duwing pwacement */
#define NEXT_CNT_PEW_TX_PKT(bds)	\
				(((bds) + MAX_TX_DESC_CNT - 1) / \
				 MAX_TX_DESC_CNT * NEXT_PAGE_TX_DESC_CNT)
/* max BDs pew tx packet w/o next_pages:
 * STAWT_BD		- descwibes packed
 * STAWT_BD(spwitted)	- incwudes unpaged data segment fow GSO
 * PAWSING_BD		- fow TSO and CSUM data
 * PAWSING_BD2		- fow encapsuwation data
 * Fwag BDs		- descwibes pages fow fwags
 */
#define BDS_PEW_TX_PKT		4
#define MAX_BDS_PEW_TX_PKT	(MAX_SKB_FWAGS + BDS_PEW_TX_PKT)
/* max BDs pew tx packet incwuding next pages */
#define MAX_DESC_PEW_TX_PKT	(MAX_BDS_PEW_TX_PKT + \
				 NEXT_CNT_PEW_TX_PKT(MAX_BDS_PEW_TX_PKT))

/* The WX BD wing is speciaw, each bd is 8 bytes but the wast one is 16 */
#define NUM_WX_WINGS		8
#define WX_DESC_CNT		(BCM_PAGE_SIZE / sizeof(stwuct eth_wx_bd))
#define NEXT_PAGE_WX_DESC_CNT	2
#define MAX_WX_DESC_CNT		(WX_DESC_CNT - NEXT_PAGE_WX_DESC_CNT)
#define WX_DESC_MASK		(WX_DESC_CNT - 1)
#define NUM_WX_BD		(WX_DESC_CNT * NUM_WX_WINGS)
#define MAX_WX_BD		(NUM_WX_BD - 1)
#define MAX_WX_AVAIW		(MAX_WX_DESC_CNT * NUM_WX_WINGS - 2)

/* dwopwess fc cawcuwations fow BDs
 *
 * Numbew of BDs shouwd as numbew of buffews in BWB:
 * Wow thweshowd takes into account NEXT_PAGE_WX_DESC_CNT
 * "next" ewements on each page
 */
#define NUM_BD_WEQ		BWB_SIZE(bp)
#define NUM_BD_PG_WEQ		((NUM_BD_WEQ + MAX_WX_DESC_CNT - 1) / \
					      MAX_WX_DESC_CNT)
#define BD_TH_WO(bp)		(NUM_BD_WEQ + \
				 NUM_BD_PG_WEQ * NEXT_PAGE_WX_DESC_CNT + \
				 FW_DWOP_WEVEW(bp))
#define BD_TH_HI(bp)		(BD_TH_WO(bp) + DWOPWESS_FC_HEADWOOM)

#define MIN_WX_AVAIW		((bp)->dwopwess_fc ? BD_TH_HI(bp) + 128 : 128)

#define MIN_WX_SIZE_TPA_HW	(CHIP_IS_E1(bp) ? \
					ETH_MIN_WX_CQES_WITH_TPA_E1 : \
					ETH_MIN_WX_CQES_WITH_TPA_E1H_E2)
#define MIN_WX_SIZE_NONTPA_HW   ETH_MIN_WX_CQES_WITHOUT_TPA
#define MIN_WX_SIZE_TPA		(max_t(u32, MIN_WX_SIZE_TPA_HW, MIN_WX_AVAIW))
#define MIN_WX_SIZE_NONTPA	(max_t(u32, MIN_WX_SIZE_NONTPA_HW,\
								MIN_WX_AVAIW))

#define NEXT_WX_IDX(x)		((((x) & WX_DESC_MASK) == \
				  (MAX_WX_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_WX_DESC_CNT : \
					(x) + 1)
#define WX_BD(x)		((x) & MAX_WX_BD)

/*
 * As wong as CQE is X times biggew than BD entwy we have to awwocate X times
 * mowe pages fow CQ wing in owdew to keep it bawanced with BD wing
 */
#define CQE_BD_WEW	(sizeof(union eth_wx_cqe) / sizeof(stwuct eth_wx_bd))
#define NUM_WCQ_WINGS		(NUM_WX_WINGS * CQE_BD_WEW)
#define WCQ_DESC_CNT		(BCM_PAGE_SIZE / sizeof(union eth_wx_cqe))
#define NEXT_PAGE_WCQ_DESC_CNT	1
#define MAX_WCQ_DESC_CNT	(WCQ_DESC_CNT - NEXT_PAGE_WCQ_DESC_CNT)
#define NUM_WCQ_BD		(WCQ_DESC_CNT * NUM_WCQ_WINGS)
#define MAX_WCQ_BD		(NUM_WCQ_BD - 1)
#define MAX_WCQ_AVAIW		(MAX_WCQ_DESC_CNT * NUM_WCQ_WINGS - 2)
#define NEXT_WCQ_IDX(x)		((((x) & MAX_WCQ_DESC_CNT) == \
				  (MAX_WCQ_DESC_CNT - 1)) ? \
					(x) + 1 + NEXT_PAGE_WCQ_DESC_CNT : \
					(x) + 1)
#define WCQ_BD(x)		((x) & MAX_WCQ_BD)

/* dwopwess fc cawcuwations fow WCQs
 *
 * Numbew of WCQs shouwd be as numbew of buffews in BWB:
 * Wow thweshowd takes into account NEXT_PAGE_WCQ_DESC_CNT
 * "next" ewements on each page
 */
#define NUM_WCQ_WEQ		BWB_SIZE(bp)
#define NUM_WCQ_PG_WEQ		((NUM_BD_WEQ + MAX_WCQ_DESC_CNT - 1) / \
					      MAX_WCQ_DESC_CNT)
#define WCQ_TH_WO(bp)		(NUM_WCQ_WEQ + \
				 NUM_WCQ_PG_WEQ * NEXT_PAGE_WCQ_DESC_CNT + \
				 FW_DWOP_WEVEW(bp))
#define WCQ_TH_HI(bp)		(WCQ_TH_WO(bp) + DWOPWESS_FC_HEADWOOM)

/* This is needed fow detewmining of wast_max */
#define SUB_S16(a, b)		(s16)((s16)(a) - (s16)(b))
#define SUB_S32(a, b)		(s32)((s32)(a) - (s32)(b))

#define BNX2X_SWCID_SHIFT	17
#define BNX2X_SWCID_MASK	((0x1 << BNX2X_SWCID_SHIFT) - 1)

/* used on a CID weceived fwom the HW */
#define SW_CID(x)			(we32_to_cpu(x) & BNX2X_SWCID_MASK)
#define CQE_CMD(x)			(we32_to_cpu(x) >> \
					COMMON_WAMWOD_ETH_WX_CQE_CMD_ID_SHIFT)

#define BD_UNMAP_ADDW(bd)		HIWO_U64(we32_to_cpu((bd)->addw_hi), \
						 we32_to_cpu((bd)->addw_wo))
#define BD_UNMAP_WEN(bd)		(we16_to_cpu((bd)->nbytes))

#define BNX2X_DB_MIN_SHIFT		3	/* 8 bytes */
#define BNX2X_DB_SHIFT			3	/* 8 bytes*/
#if (BNX2X_DB_SHIFT < BNX2X_DB_MIN_SHIFT)
#ewwow "Min DB doowbeww stwide is 8"
#endif
#define DOOWBEWW_WEWAXED(bp, cid, vaw) \
	wwitew_wewaxed((u32)(vaw), (bp)->doowbewws + ((bp)->db_size * (cid)))

/* TX CSUM hewpews */
#define SKB_CS_OFF(skb)		(offsetof(stwuct tcphdw, check) - \
				 skb->csum_offset)
#define SKB_CS(skb)		(*(u16 *)(skb_twanspowt_headew(skb) + \
					  skb->csum_offset))

#define pbd_tcp_fwags(tcp_hdw)	(ntohw(tcp_fwag_wowd(tcp_hdw))>>16 & 0xff)

#define XMIT_PWAIN		0
#define XMIT_CSUM_V4		(1 << 0)
#define XMIT_CSUM_V6		(1 << 1)
#define XMIT_CSUM_TCP		(1 << 2)
#define XMIT_GSO_V4		(1 << 3)
#define XMIT_GSO_V6		(1 << 4)
#define XMIT_CSUM_ENC_V4	(1 << 5)
#define XMIT_CSUM_ENC_V6	(1 << 6)
#define XMIT_GSO_ENC_V4		(1 << 7)
#define XMIT_GSO_ENC_V6		(1 << 8)

#define XMIT_CSUM_ENC		(XMIT_CSUM_ENC_V4 | XMIT_CSUM_ENC_V6)
#define XMIT_GSO_ENC		(XMIT_GSO_ENC_V4 | XMIT_GSO_ENC_V6)

#define XMIT_CSUM		(XMIT_CSUM_V4 | XMIT_CSUM_V6 | XMIT_CSUM_ENC)
#define XMIT_GSO		(XMIT_GSO_V4 | XMIT_GSO_V6 | XMIT_GSO_ENC)

/* stuff added to make the code fit 80Cow */
#define CQE_TYPE(cqe_fp_fwags)	 ((cqe_fp_fwags) & ETH_FAST_PATH_WX_CQE_TYPE)
#define CQE_TYPE_STAWT(cqe_type) ((cqe_type) == WX_ETH_CQE_TYPE_ETH_STAWT_AGG)
#define CQE_TYPE_STOP(cqe_type)  ((cqe_type) == WX_ETH_CQE_TYPE_ETH_STOP_AGG)
#define CQE_TYPE_SWOW(cqe_type)  ((cqe_type) == WX_ETH_CQE_TYPE_ETH_WAMWOD)
#define CQE_TYPE_FAST(cqe_type)  ((cqe_type) == WX_ETH_CQE_TYPE_ETH_FASTPATH)

#define ETH_WX_EWWOW_FAWGS		ETH_FAST_PATH_WX_CQE_PHY_DECODE_EWW_FWG

#define BNX2X_PWS_FWAG_OVEWETH_IPV4(fwags) \
				(((we16_to_cpu(fwags) & \
				   PAWSING_FWAGS_OVEW_ETHEWNET_PWOTOCOW) >> \
				  PAWSING_FWAGS_OVEW_ETHEWNET_PWOTOCOW_SHIFT) \
				 == PWS_FWAG_OVEWETH_IPV4)
#define BNX2X_WX_SUM_FIX(cqe) \
	BNX2X_PWS_FWAG_OVEWETH_IPV4(cqe->fast_path_cqe.paws_fwags.fwags)

#define FP_USB_FUNC_OFF	\
			offsetof(stwuct cstowm_status_bwock_u, func)
#define FP_CSB_FUNC_OFF	\
			offsetof(stwuct cstowm_status_bwock_c, func)

#define HC_INDEX_ETH_WX_CQ_CONS		1

#define HC_INDEX_OOO_TX_CQ_CONS		4

#define HC_INDEX_ETH_TX_CQ_CONS_COS0	5

#define HC_INDEX_ETH_TX_CQ_CONS_COS1	6

#define HC_INDEX_ETH_TX_CQ_CONS_COS2	7

#define HC_INDEX_ETH_FIWST_TX_CQ_CONS	HC_INDEX_ETH_TX_CQ_CONS_COS0

#define BNX2X_WX_SB_INDEX \
	(&fp->sb_index_vawues[HC_INDEX_ETH_WX_CQ_CONS])

#define BNX2X_TX_SB_INDEX_BASE BNX2X_TX_SB_INDEX_COS0

#define BNX2X_TX_SB_INDEX_COS0 \
	(&fp->sb_index_vawues[HC_INDEX_ETH_TX_CQ_CONS_COS0])

/* end of fast path */

/* common */

stwuct bnx2x_common {

	u32			chip_id;
/* chip num:16-31, wev:12-15, metaw:4-11, bond_id:0-3 */
#define CHIP_ID(bp)			(bp->common.chip_id & 0xfffffff0)

#define CHIP_NUM(bp)			(bp->common.chip_id >> 16)
#define CHIP_NUM_57710			0x164e
#define CHIP_NUM_57711			0x164f
#define CHIP_NUM_57711E			0x1650
#define CHIP_NUM_57712			0x1662
#define CHIP_NUM_57712_MF		0x1663
#define CHIP_NUM_57712_VF		0x166f
#define CHIP_NUM_57713			0x1651
#define CHIP_NUM_57713E			0x1652
#define CHIP_NUM_57800			0x168a
#define CHIP_NUM_57800_MF		0x16a5
#define CHIP_NUM_57800_VF		0x16a9
#define CHIP_NUM_57810			0x168e
#define CHIP_NUM_57810_MF		0x16ae
#define CHIP_NUM_57810_VF		0x16af
#define CHIP_NUM_57811			0x163d
#define CHIP_NUM_57811_MF		0x163e
#define CHIP_NUM_57811_VF		0x163f
#define CHIP_NUM_57840_OBSOWETE		0x168d
#define CHIP_NUM_57840_MF_OBSOWETE	0x16ab
#define CHIP_NUM_57840_4_10		0x16a1
#define CHIP_NUM_57840_2_20		0x16a2
#define CHIP_NUM_57840_MF		0x16a4
#define CHIP_NUM_57840_VF		0x16ad
#define CHIP_IS_E1(bp)			(CHIP_NUM(bp) == CHIP_NUM_57710)
#define CHIP_IS_57711(bp)		(CHIP_NUM(bp) == CHIP_NUM_57711)
#define CHIP_IS_57711E(bp)		(CHIP_NUM(bp) == CHIP_NUM_57711E)
#define CHIP_IS_57712(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712)
#define CHIP_IS_57712_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712_VF)
#define CHIP_IS_57712_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57712_MF)
#define CHIP_IS_57800(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800)
#define CHIP_IS_57800_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800_MF)
#define CHIP_IS_57800_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57800_VF)
#define CHIP_IS_57810(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810)
#define CHIP_IS_57810_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810_MF)
#define CHIP_IS_57810_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57810_VF)
#define CHIP_IS_57811(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811)
#define CHIP_IS_57811_MF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811_MF)
#define CHIP_IS_57811_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57811_VF)
#define CHIP_IS_57840(bp)		\
		((CHIP_NUM(bp) == CHIP_NUM_57840_4_10) || \
		 (CHIP_NUM(bp) == CHIP_NUM_57840_2_20) || \
		 (CHIP_NUM(bp) == CHIP_NUM_57840_OBSOWETE))
#define CHIP_IS_57840_MF(bp)	((CHIP_NUM(bp) == CHIP_NUM_57840_MF) || \
				 (CHIP_NUM(bp) == CHIP_NUM_57840_MF_OBSOWETE))
#define CHIP_IS_57840_VF(bp)		(CHIP_NUM(bp) == CHIP_NUM_57840_VF)
#define CHIP_IS_E1H(bp)			(CHIP_IS_57711(bp) || \
					 CHIP_IS_57711E(bp))
#define CHIP_IS_57811xx(bp)		(CHIP_IS_57811(bp) || \
					 CHIP_IS_57811_MF(bp) || \
					 CHIP_IS_57811_VF(bp))
#define CHIP_IS_E2(bp)			(CHIP_IS_57712(bp) || \
					 CHIP_IS_57712_MF(bp) || \
					 CHIP_IS_57712_VF(bp))
#define CHIP_IS_E3(bp)			(CHIP_IS_57800(bp) || \
					 CHIP_IS_57800_MF(bp) || \
					 CHIP_IS_57800_VF(bp) || \
					 CHIP_IS_57810(bp) || \
					 CHIP_IS_57810_MF(bp) || \
					 CHIP_IS_57810_VF(bp) || \
					 CHIP_IS_57811xx(bp) || \
					 CHIP_IS_57840(bp) || \
					 CHIP_IS_57840_MF(bp) || \
					 CHIP_IS_57840_VF(bp))
#define CHIP_IS_E1x(bp)			(CHIP_IS_E1((bp)) || CHIP_IS_E1H((bp)))
#define USES_WAWPCOWE(bp)		(CHIP_IS_E3(bp))
#define IS_E1H_OFFSET			(!CHIP_IS_E1(bp))

#define CHIP_WEV_SHIFT			12
#define CHIP_WEV_MASK			(0xF << CHIP_WEV_SHIFT)
#define CHIP_WEV_VAW(bp)		(bp->common.chip_id & CHIP_WEV_MASK)
#define CHIP_WEV_Ax			(0x0 << CHIP_WEV_SHIFT)
#define CHIP_WEV_Bx			(0x1 << CHIP_WEV_SHIFT)
/* assume maximum 5 wevisions */
#define CHIP_WEV_IS_SWOW(bp)		(CHIP_WEV_VAW(bp) > 0x00005000)
/* Emuw vewsions awe A=>0xe, B=>0xc, C=>0xa, D=>8, E=>6 */
#define CHIP_WEV_IS_EMUW(bp)		((CHIP_WEV_IS_SWOW(bp)) && \
					 !(CHIP_WEV_VAW(bp) & 0x00001000))
/* FPGA vewsions awe A=>0xf, B=>0xd, C=>0xb, D=>9, E=>7 */
#define CHIP_WEV_IS_FPGA(bp)		((CHIP_WEV_IS_SWOW(bp)) && \
					 (CHIP_WEV_VAW(bp) & 0x00001000))

#define CHIP_TIME(bp)			((CHIP_WEV_IS_EMUW(bp)) ? 2000 : \
					((CHIP_WEV_IS_FPGA(bp)) ? 200 : 1))

#define CHIP_METAW(bp)			(bp->common.chip_id & 0x00000ff0)
#define CHIP_BOND_ID(bp)		(bp->common.chip_id & 0x0000000f)
#define CHIP_WEV_SIM(bp)		(((CHIP_WEV_MASK - CHIP_WEV_VAW(bp)) >>\
					   (CHIP_WEV_SHIFT + 1)) \
						<< CHIP_WEV_SHIFT)
#define CHIP_WEV(bp)			(CHIP_WEV_IS_SWOW(bp) ? \
						CHIP_WEV_SIM(bp) :\
						CHIP_WEV_VAW(bp))
#define CHIP_IS_E3B0(bp)		(CHIP_IS_E3(bp) && \
					 (CHIP_WEV(bp) == CHIP_WEV_Bx))
#define CHIP_IS_E3A0(bp)		(CHIP_IS_E3(bp) && \
					 (CHIP_WEV(bp) == CHIP_WEV_Ax))
/* This define is used in two main pwaces:
 * 1. In the eawwy stages of nic_woad, to know if to configuwe Pawsew / Seawchew
 * to nic-onwy mode ow to offwoad mode. Offwoad mode is configuwed if eithew the
 * chip is E1x (whewe MIC_MODE wegistew is not appwicabwe), ow if cnic awweady
 * wegistewed fow this powt (which means that the usew wants stowage sewvices).
 * 2. Duwing cnic-wewated woad, to know if offwoad mode is awweady configuwed in
 * the HW ow needs to be configuwed.
 * Since the twansition fwom nic-mode to offwoad-mode in HW causes twaffic
 * cowwuption, nic-mode is configuwed onwy in powts on which stowage sewvices
 * whewe nevew wequested.
 */
#define CONFIGUWE_NIC_MODE(bp)		(!CHIP_IS_E1x(bp) && !CNIC_ENABWED(bp))

	int			fwash_size;
#define BNX2X_NVWAM_1MB_SIZE			0x20000	/* 1M bit in bytes */
#define BNX2X_NVWAM_TIMEOUT_COUNT		30000
#define BNX2X_NVWAM_PAGE_SIZE			256

	u32			shmem_base;
	u32			shmem2_base;
	u32			mf_cfg_base;
	u32			mf2_cfg_base;

	u32			hw_config;

	u32			bc_vew;

	u8			int_bwock;
#define INT_BWOCK_HC			0
#define INT_BWOCK_IGU			1
#define INT_BWOCK_MODE_NOWMAW		0
#define INT_BWOCK_MODE_BW_COMP		2
#define CHIP_INT_MODE_IS_NBC(bp)		\
			(!CHIP_IS_E1x(bp) &&	\
			!((bp)->common.int_bwock & INT_BWOCK_MODE_BW_COMP))
#define CHIP_INT_MODE_IS_BC(bp) (!CHIP_INT_MODE_IS_NBC(bp))

	u8			chip_powt_mode;
#define CHIP_4_POWT_MODE			0x0
#define CHIP_2_POWT_MODE			0x1
#define CHIP_POWT_MODE_NONE			0x2
#define CHIP_MODE(bp)			(bp->common.chip_powt_mode)
#define CHIP_MODE_IS_4_POWT(bp) (CHIP_MODE(bp) == CHIP_4_POWT_MODE)

	u32			boot_mode;
};

/* IGU MSIX STATISTICS on 57712: 64 fow VFs; 4 fow PFs; 4 fow Attentions */
#define BNX2X_IGU_STAS_MSG_VF_CNT 64
#define BNX2X_IGU_STAS_MSG_PF_CNT 4

#define MAX_IGU_ATTN_ACK_TO       100
/* end of common */

/* powt */

stwuct bnx2x_powt {
	u32			pmf;

	u32			wink_config[WINK_CONFIG_SIZE];

	u32			suppowted[WINK_CONFIG_SIZE];

	u32			advewtising[WINK_CONFIG_SIZE];

	u32			phy_addw;

	/* used to synchwonize phy accesses */
	stwuct mutex		phy_mutex;

	u32			powt_stx;

	stwuct nig_stats	owd_nig_stats;
};

/* end of powt */

#define STATS_OFFSET32(stat_name) \
			(offsetof(stwuct bnx2x_eth_stats, stat_name) / 4)

/* swow path */
#define BNX2X_MAX_NUM_OF_VFS	64
#define BNX2X_VF_CID_WND	4 /* wog num of queues pew VF. HW config. */
#define BNX2X_CIDS_PEW_VF	(1 << BNX2X_VF_CID_WND)

/* We need to wesewve doowbeww addwesses fow aww VF and queue combinations */
#define BNX2X_VF_CIDS		(BNX2X_MAX_NUM_OF_VFS * BNX2X_CIDS_PEW_VF)

/* The doowbeww is configuwed to have the same numbew of CIDs fow PFs and fow
 * VFs. Fow this weason the PF CID zone is as wawge as the VF zone.
 */
#define BNX2X_FIWST_VF_CID	BNX2X_VF_CIDS
#define BNX2X_MAX_NUM_VF_QUEUES	64
#define BNX2X_VF_ID_INVAWID	0xFF

/* the numbew of VF CIDS muwtipwied by the amount of bytes wesewved fow each
 * cid must not exceed the size of the VF doowbeww
 */
#define BNX2X_VF_BAW_SIZE	512
#if (BNX2X_VF_BAW_SIZE < BNX2X_CIDS_PEW_VF * (1 << BNX2X_DB_SHIFT))
#ewwow "VF doowbeww baw size is 512"
#endif

/*
 * The totaw numbew of W2 queues, MSIX vectows and HW contexts (CIDs) is
 * contwow by the numbew of fast-path status bwocks suppowted by the
 * device (HW/FW). Each fast-path status bwock (FP-SB) aka non-defauwt
 * status bwock wepwesents an independent intewwupts context that can
 * sewve a weguwaw W2 netwowking queue. Howevew speciaw W2 queues such
 * as the FCoE queue do not wequiwe a FP-SB and othew components wike
 * the CNIC may consume FP-SB weducing the numbew of possibwe W2 queues
 *
 * If the maximum numbew of FP-SB avaiwabwe is X then:
 * a. If CNIC is suppowted it consumes 1 FP-SB thus the max numbew of
 *    weguwaw W2 queues is Y=X-1
 * b. In MF mode the actuaw numbew of W2 queues is Y= (X-1/MF_factow)
 * c. If the FCoE W2 queue is suppowted the actuaw numbew of W2 queues
 *    is Y+1
 * d. The numbew of iwqs (MSIX vectows) is eithew Y+1 (one extwa fow
 *    swow-path intewwupts) ow Y+2 if CNIC is suppowted (one additionaw
 *    FP intewwupt context fow the CNIC).
 * e. The numbew of HW context (CID count) is awways X ow X+1 if FCoE
 *    W2 queue is suppowted. The cid fow the FCoE W2 queue is awways X.
 */

/* fast-path intewwupt contexts E1x */
#define FP_SB_MAX_E1x		16
/* fast-path intewwupt contexts E2 */
#define FP_SB_MAX_E2		HC_SB_MAX_SB_E2

union cdu_context {
	stwuct eth_context eth;
	chaw pad[1024];
};

/* CDU host DB constants */
#define CDU_IWT_PAGE_SZ_HW	2
#define CDU_IWT_PAGE_SZ		(8192 << CDU_IWT_PAGE_SZ_HW) /* 32K */
#define IWT_PAGE_CIDS		(CDU_IWT_PAGE_SZ / sizeof(union cdu_context))

#define CNIC_ISCSI_CID_MAX	256
#define CNIC_FCOE_CID_MAX	2048
#define CNIC_CID_MAX		(CNIC_ISCSI_CID_MAX + CNIC_FCOE_CID_MAX)
#define CNIC_IWT_WINES		DIV_WOUND_UP(CNIC_CID_MAX, IWT_PAGE_CIDS)

#define QM_IWT_PAGE_SZ_HW	0
#define QM_IWT_PAGE_SZ		(4096 << QM_IWT_PAGE_SZ_HW) /* 4K */
#define QM_CID_WOUND		1024

/* TM (timews) host DB constants */
#define TM_IWT_PAGE_SZ_HW	0
#define TM_IWT_PAGE_SZ		(4096 << TM_IWT_PAGE_SZ_HW) /* 4K */
#define TM_CONN_NUM		(BNX2X_FIWST_VF_CID + \
				 BNX2X_VF_CIDS + \
				 CNIC_ISCSI_CID_MAX)
#define TM_IWT_SZ		(8 * TM_CONN_NUM)
#define TM_IWT_WINES		DIV_WOUND_UP(TM_IWT_SZ, TM_IWT_PAGE_SZ)

/* SWC (Seawchew) host DB constants */
#define SWC_IWT_PAGE_SZ_HW	0
#define SWC_IWT_PAGE_SZ		(4096 << SWC_IWT_PAGE_SZ_HW) /* 4K */
#define SWC_HASH_BITS		10
#define SWC_CONN_NUM		(1 << SWC_HASH_BITS) /* 1024 */
#define SWC_IWT_SZ		(sizeof(stwuct swc_ent) * SWC_CONN_NUM)
#define SWC_T2_SZ		SWC_IWT_SZ
#define SWC_IWT_WINES		DIV_WOUND_UP(SWC_IWT_SZ, SWC_IWT_PAGE_SZ)

#define MAX_DMAE_C		8

/* DMA memowy not used in fastpath */
stwuct bnx2x_swowpath {
	union {
		stwuct mac_configuwation_cmd		e1x;
		stwuct eth_cwassify_wuwes_wamwod_data	e2;
	} mac_wdata;

	union {
		stwuct eth_cwassify_wuwes_wamwod_data	e2;
	} vwan_wdata;

	union {
		stwuct tstowm_eth_mac_fiwtew_config	e1x;
		stwuct eth_fiwtew_wuwes_wamwod_data	e2;
	} wx_mode_wdata;

	union {
		stwuct mac_configuwation_cmd		e1;
		stwuct eth_muwticast_wuwes_wamwod_data  e2;
	} mcast_wdata;

	stwuct eth_wss_update_wamwod_data	wss_wdata;

	/* Queue State wewated wamwods awe awways sent undew wtnw_wock */
	union {
		stwuct cwient_init_wamwod_data  init_data;
		stwuct cwient_update_wamwod_data update_data;
		stwuct tpa_update_wamwod_data tpa_data;
	} q_wdata;

	union {
		stwuct function_stawt_data	func_stawt;
		/* pfc configuwation fow DCBX wamwod */
		stwuct fwow_contwow_configuwation pfc_config;
	} func_wdata;

	/* afex wamwod can not be a pawt of func_wdata union because these
	 * events might awwive in pawawwew to othew events fwom func_wdata.
	 * Thewefowe, if they wouwd have been defined in the same union,
	 * data can get cowwupted.
	 */
	union {
		stwuct afex_vif_wist_wamwod_data	vifwist_data;
		stwuct function_update_data		func_update;
	} func_afex_wdata;

	/* used by dmae command executew */
	stwuct dmae_command		dmae[MAX_DMAE_C];

	u32				stats_comp;
	union mac_stats			mac_stats;
	stwuct nig_stats		nig_stats;
	stwuct host_powt_stats		powt_stats;
	stwuct host_func_stats		func_stats;

	u32				wb_comp;
	u32				wb_data[4];

	union dwv_info_to_mcp		dwv_info_to_mcp;
};

#define bnx2x_sp(bp, vaw)		(&bp->swowpath->vaw)
#define bnx2x_sp_mapping(bp, vaw) \
		(bp->swowpath_mapping + offsetof(stwuct bnx2x_swowpath, vaw))

/* attn gwoup wiwing */
#define MAX_DYNAMIC_ATTN_GWPS		8

stwuct attn_woute {
	u32 sig[5];
};

stwuct iwo {
	u32 base;
	u16 m1;
	u16 m2;
	u16 m3;
	u16 size;
};

stwuct hw_context {
	union cdu_context *vcxt;
	dma_addw_t cxt_mapping;
	size_t size;
};

/* fowwawd */
stwuct bnx2x_iwt;

stwuct bnx2x_vfdb;

enum bnx2x_wecovewy_state {
	BNX2X_WECOVEWY_DONE,
	BNX2X_WECOVEWY_INIT,
	BNX2X_WECOVEWY_WAIT,
	BNX2X_WECOVEWY_FAIWED,
	BNX2X_WECOVEWY_NIC_WOADING
};

/*
 * Event queue (EQ ow event wing) MC hsi
 * NUM_EQ_PAGES and EQ_DESC_CNT_PAGE must be powew of 2
 */
#define NUM_EQ_PAGES		1
#define EQ_DESC_CNT_PAGE	(BCM_PAGE_SIZE / sizeof(union event_wing_ewem))
#define EQ_DESC_MAX_PAGE	(EQ_DESC_CNT_PAGE - 1)
#define NUM_EQ_DESC		(EQ_DESC_CNT_PAGE * NUM_EQ_PAGES)
#define EQ_DESC_MASK		(NUM_EQ_DESC - 1)
#define MAX_EQ_AVAIW		(EQ_DESC_MAX_PAGE * NUM_EQ_PAGES - 2)

/* depends on EQ_DESC_CNT_PAGE being a powew of 2 */
#define NEXT_EQ_IDX(x)		((((x) & EQ_DESC_MAX_PAGE) == \
				  (EQ_DESC_MAX_PAGE - 1)) ? (x) + 2 : (x) + 1)

/* depends on the above and on NUM_EQ_PAGES being a powew of 2 */
#define EQ_DESC(x)		((x) & EQ_DESC_MASK)

#define BNX2X_EQ_INDEX \
	(&bp->def_status_bwk->sp_sb.\
	index_vawues[HC_SP_INDEX_EQ_CONS])

/* This is a data that wiww be used to cweate a wink wepowt message.
 * We wiww keep the data used fow the wast wink wepowt in owdew
 * to pwevent wepowting the same wink pawametews twice.
 */
stwuct bnx2x_wink_wepowt_data {
	u16 wine_speed;			/* Effective wine speed */
	unsigned wong wink_wepowt_fwags;/* BNX2X_WINK_WEPOWT_XXX fwags */
};

enum {
	BNX2X_WINK_WEPOWT_FD,		/* Fuww DUPWEX */
	BNX2X_WINK_WEPOWT_WINK_DOWN,
	BNX2X_WINK_WEPOWT_WX_FC_ON,
	BNX2X_WINK_WEPOWT_TX_FC_ON,
};

enum {
	BNX2X_POWT_QUEWY_IDX,
	BNX2X_PF_QUEWY_IDX,
	BNX2X_FCOE_QUEWY_IDX,
	BNX2X_FIWST_QUEUE_QUEWY_IDX,
};

stwuct bnx2x_fw_stats_weq {
	stwuct stats_quewy_headew hdw;
	stwuct stats_quewy_entwy quewy[FP_SB_MAX_E1x+
		BNX2X_FIWST_QUEUE_QUEWY_IDX];
};

stwuct bnx2x_fw_stats_data {
	stwuct stats_countew		stowm_countews;
	stwuct pew_powt_stats		powt;
	stwuct pew_pf_stats		pf;
	stwuct fcoe_statistics_pawams	fcoe;
	stwuct pew_queue_stats		queue_stats[];
};

/* Pubwic swow path states */
enum sp_wtnw_fwag {
	BNX2X_SP_WTNW_SETUP_TC,
	BNX2X_SP_WTNW_TX_TIMEOUT,
	BNX2X_SP_WTNW_FAN_FAIWUWE,
	BNX2X_SP_WTNW_AFEX_F_UPDATE,
	BNX2X_SP_WTNW_ENABWE_SWIOV,
	BNX2X_SP_WTNW_VFPF_MCAST,
	BNX2X_SP_WTNW_VFPF_CHANNEW_DOWN,
	BNX2X_SP_WTNW_WX_MODE,
	BNX2X_SP_WTNW_HYPEWVISOW_VWAN,
	BNX2X_SP_WTNW_TX_STOP,
	BNX2X_SP_WTNW_GET_DWV_VEWSION,
	BNX2X_SP_WTNW_UPDATE_SVID,
};

enum bnx2x_iov_fwag {
	BNX2X_IOV_HANDWE_VF_MSG,
	BNX2X_IOV_HANDWE_FWW,
};

stwuct bnx2x_pwev_path_wist {
	stwuct wist_head wist;
	u8 bus;
	u8 swot;
	u8 path;
	u8 aew;
	u8 undi;
};

stwuct bnx2x_sp_objs {
	/* MACs object */
	stwuct bnx2x_vwan_mac_obj mac_obj;

	/* Queue State object */
	stwuct bnx2x_queue_sp_obj q_obj;

	/* VWANs object */
	stwuct bnx2x_vwan_mac_obj vwan_obj;
};

stwuct bnx2x_fp_stats {
	stwuct tstowm_pew_queue_stats owd_tcwient;
	stwuct ustowm_pew_queue_stats owd_ucwient;
	stwuct xstowm_pew_queue_stats owd_xcwient;
	stwuct bnx2x_eth_q_stats eth_q_stats;
	stwuct bnx2x_eth_q_stats_owd eth_q_stats_owd;
};

enum {
	SUB_MF_MODE_UNKNOWN = 0,
	SUB_MF_MODE_UFP,
	SUB_MF_MODE_NPAW1_DOT_5,
	SUB_MF_MODE_BD,
};

stwuct bnx2x_vwan_entwy {
	stwuct wist_head wink;
	u16 vid;
	boow hw;
};

enum bnx2x_udp_powt_type {
	BNX2X_UDP_POWT_VXWAN,
	BNX2X_UDP_POWT_GENEVE,
	BNX2X_UDP_POWT_MAX,
};

stwuct bnx2x {
	/* Fiewds used in the tx and intw/napi pewfowmance paths
	 * awe gwouped togethew in the beginning of the stwuctuwe
	 */
	stwuct bnx2x_fastpath	*fp;
	stwuct bnx2x_sp_objs	*sp_objs;
	stwuct bnx2x_fp_stats	*fp_stats;
	stwuct bnx2x_fp_txdata	*bnx2x_txq;
	void __iomem		*wegview;
	void __iomem		*doowbewws;
	u16			db_size;

	u8			pf_num;	/* absowute PF numbew */
	u8			pfid;	/* pew-path PF numbew */
	int			base_fw_ndsb; /**/
#define BP_PATH(bp)			(CHIP_IS_E1x(bp) ? 0 : (bp->pf_num & 1))
#define BP_POWT(bp)			(bp->pfid & 1)
#define BP_FUNC(bp)			(bp->pfid)
#define BP_ABS_FUNC(bp)			(bp->pf_num)
#define BP_VN(bp)			((bp)->pfid >> 1)
#define BP_MAX_VN_NUM(bp)		(CHIP_MODE_IS_4_POWT(bp) ? 2 : 4)
#define BP_W_ID(bp)			(BP_VN(bp) << 2)
#define BP_FW_MB_IDX_VN(bp, vn)		(BP_POWT(bp) +\
	  (vn) * ((CHIP_IS_E1x(bp) || (CHIP_MODE_IS_4_POWT(bp))) ? 2  : 1))
#define BP_FW_MB_IDX(bp)		BP_FW_MB_IDX_VN(bp, BP_VN(bp))

#ifdef CONFIG_BNX2X_SWIOV
	/* pwotects vf2pf maiwbox fwom simuwtaneous access */
	stwuct mutex		vf2pf_mutex;
	/* vf pf channew maiwbox contains wequest and wesponse buffews */
	stwuct bnx2x_vf_mbx_msg	*vf2pf_mbox;
	dma_addw_t		vf2pf_mbox_mapping;

	/* we set aside a copy of the acquiwe wesponse */
	stwuct pfvf_acquiwe_wesp_twv acquiwe_wesp;

	/* buwwetin boawd fow messages fwom pf to vf */
	union pf_vf_buwwetin   *pf2vf_buwwetin;
	dma_addw_t		pf2vf_buwwetin_mapping;

	union pf_vf_buwwetin		shadow_buwwetin;
	stwuct pf_vf_buwwetin_content	owd_buwwetin;

	u16 wequested_nw_viwtfn;
#endif /* CONFIG_BNX2X_SWIOV */

	stwuct net_device	*dev;
	stwuct pci_dev		*pdev;

	const stwuct iwo	*iwo_aww;
#define IWO (bp->iwo_aww)

	enum bnx2x_wecovewy_state wecovewy_state;
	int			is_weadew;
	stwuct msix_entwy	*msix_tabwe;

	int			tx_wing_size;

/* W2 headew size + 2*VWANs (8 bytes) + WWC SNAP (8 bytes) */
#define ETH_OVEWHEAD		(ETH_HWEN + 8 + 8)
#define ETH_MIN_PACKET_SIZE		(ETH_ZWEN - ETH_HWEN)
#define ETH_MAX_PACKET_SIZE		ETH_DATA_WEN
#define ETH_MAX_JUMBO_PACKET_SIZE	9600
/* TCP with Timestamp Option (32) + IPv6 (40) */
#define ETH_MAX_TPA_HEADEW_SIZE		72

	/* Max suppowted awignment is 256 (8 shift)
	 * minimaw awignment shift 6 is optimaw fow 57xxx HW pewfowmance
	 */
#define BNX2X_WX_AWIGN_SHIFT		max(6, min(8, W1_CACHE_SHIFT))

	/* FW uses 2 Cache wines Awignment fow stawt packet and size
	 *
	 * We assume skb_buiwd() uses sizeof(stwuct skb_shawed_info) bytes
	 * at the end of skb->data, to avoid wasting a fuww cache wine.
	 * This weduces memowy use (skb->twuesize).
	 */
#define BNX2X_FW_WX_AWIGN_STAWT	(1UW << BNX2X_WX_AWIGN_SHIFT)

#define BNX2X_FW_WX_AWIGN_END					\
	max_t(u64, 1UW << BNX2X_WX_AWIGN_SHIFT,			\
	    SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

#define BNX2X_PXP_DWAM_AWIGN		(BNX2X_WX_AWIGN_SHIFT - 5)

	stwuct host_sp_status_bwock *def_status_bwk;
#define DEF_SB_IGU_ID			16
#define DEF_SB_ID			HC_SP_SB_ID
	__we16			def_idx;
	__we16			def_att_idx;
	u32			attn_state;
	stwuct attn_woute	attn_gwoup[MAX_DYNAMIC_ATTN_GWPS];

	/* swow path wing */
	stwuct eth_spe		*spq;
	dma_addw_t		spq_mapping;
	u16			spq_pwod_idx;
	stwuct eth_spe		*spq_pwod_bd;
	stwuct eth_spe		*spq_wast_bd;
	__we16			*dsb_sp_pwod;
	atomic_t		cq_spq_weft; /* ETH_XXX wamwods cwedit */
	/* used to synchwonize spq accesses */
	spinwock_t		spq_wock;

	/* event queue */
	union event_wing_ewem	*eq_wing;
	dma_addw_t		eq_mapping;
	u16			eq_pwod;
	u16			eq_cons;
	__we16			*eq_cons_sb;
	atomic_t		eq_spq_weft; /* COMMON_XXX wamwods cwedit */

	/* Countew fow mawking that thewe is a STAT_QUEWY wamwod pending */
	u16			stats_pending;
	/*  Countew fow compweted statistics wamwods */
	u16			stats_comp;

	/* End of fiewds used in the pewfowmance code paths */

	int			panic;
	int			msg_enabwe;

	u32			fwags;
#define PCIX_FWAG			(1 << 0)
#define PCI_32BIT_FWAG			(1 << 1)
#define ONE_POWT_FWAG			(1 << 2)
#define NO_WOW_FWAG			(1 << 3)
#define USING_MSIX_FWAG			(1 << 5)
#define USING_MSI_FWAG			(1 << 6)
#define DISABWE_MSI_FWAG		(1 << 7)
#define NO_MCP_FWAG			(1 << 9)
#define MF_FUNC_DIS			(1 << 11)
#define OWN_CNIC_IWQ			(1 << 12)
#define NO_ISCSI_OOO_FWAG		(1 << 13)
#define NO_ISCSI_FWAG			(1 << 14)
#define NO_FCOE_FWAG			(1 << 15)
#define BC_SUPPOWTS_PFC_STATS		(1 << 17)
#define TX_SWITCHING			(1 << 18)
#define BC_SUPPOWTS_FCOE_FEATUWES	(1 << 19)
#define USING_SINGWE_MSIX_FWAG		(1 << 20)
#define BC_SUPPOWTS_DCBX_MSG_NON_PMF	(1 << 21)
#define IS_VF_FWAG			(1 << 22)
#define BC_SUPPOWTS_WMMOD_CMD		(1 << 23)
#define HAS_PHYS_POWT_ID		(1 << 24)
#define PTP_SUPPOWTED			(1 << 26)
#define TX_TIMESTAMPING_EN		(1 << 27)

#define BP_NOMCP(bp)			((bp)->fwags & NO_MCP_FWAG)

#ifdef CONFIG_BNX2X_SWIOV
#define IS_VF(bp)			((bp)->fwags & IS_VF_FWAG)
#define IS_PF(bp)			(!((bp)->fwags & IS_VF_FWAG))
#ewse
#define IS_VF(bp)			fawse
#define IS_PF(bp)			twue
#endif

#define NO_ISCSI(bp)		((bp)->fwags & NO_ISCSI_FWAG)
#define NO_ISCSI_OOO(bp)	((bp)->fwags & NO_ISCSI_OOO_FWAG)
#define NO_FCOE(bp)		((bp)->fwags & NO_FCOE_FWAG)

	u8			cnic_suppowt;
	boow			cnic_enabwed;
	boow			cnic_woaded;
	stwuct cnic_eth_dev	*(*cnic_pwobe)(stwuct net_device *);

	boow                    nic_stopped;

	/* Fwag that indicates that we can stawt wooking fow FCoE W2 queue
	 * compwetions in the defauwt status bwock.
	 */
	boow			fcoe_init;

	int			mwws;

	stwuct dewayed_wowk	sp_task;
	stwuct dewayed_wowk	iov_task;

	atomic_t		intewwupt_occuwwed;
	stwuct dewayed_wowk	sp_wtnw_task;

	stwuct dewayed_wowk	pewiod_task;
	stwuct timew_wist	timew;
	int			cuwwent_intewvaw;

	u16			fw_seq;
	u16			fw_dwv_puwse_ww_seq;
	u32			func_stx;

	stwuct wink_pawams	wink_pawams;
	stwuct wink_vaws	wink_vaws;
	u32			wink_cnt;
	stwuct bnx2x_wink_wepowt_data wast_wepowted_wink;
	boow			fowce_wink_down;

	stwuct mdio_if_info	mdio;

	stwuct bnx2x_common	common;
	stwuct bnx2x_powt	powt;

	stwuct cmng_init	cmng;

	u32			mf_config[E1HVN_MAX];
	u32			mf_ext_config;
	u32			path_has_ovwan; /* E3 */
	u16			mf_ov;
	u8			mf_mode;
#define IS_MF(bp)		(bp->mf_mode != 0)
#define IS_MF_SI(bp)		(bp->mf_mode == MUWTI_FUNCTION_SI)
#define IS_MF_SD(bp)		(bp->mf_mode == MUWTI_FUNCTION_SD)
#define IS_MF_AFEX(bp)		(bp->mf_mode == MUWTI_FUNCTION_AFEX)
	u8			mf_sub_mode;
#define IS_MF_UFP(bp)		(IS_MF_SD(bp) && \
				 bp->mf_sub_mode == SUB_MF_MODE_UFP)
#define IS_MF_BD(bp)		(IS_MF_SD(bp) && \
				 bp->mf_sub_mode == SUB_MF_MODE_BD)

	u8			wow;

	int			wx_wing_size;

	u16			tx_quick_cons_twip_int;
	u16			tx_quick_cons_twip;
	u16			tx_ticks_int;
	u16			tx_ticks;

	u16			wx_quick_cons_twip_int;
	u16			wx_quick_cons_twip;
	u16			wx_ticks_int;
	u16			wx_ticks;
/* Maximaw coawescing timeout in us */
#define BNX2X_MAX_COAWESCE_TOUT		(0xff*BNX2X_BTW)

	u32			win_cnt;

	u16			state;
#define BNX2X_STATE_CWOSED		0
#define BNX2X_STATE_OPENING_WAIT4_WOAD	0x1000
#define BNX2X_STATE_OPENING_WAIT4_POWT	0x2000
#define BNX2X_STATE_OPEN		0x3000
#define BNX2X_STATE_CWOSING_WAIT4_HAWT	0x4000
#define BNX2X_STATE_CWOSING_WAIT4_DEWETE 0x5000

#define BNX2X_STATE_DIAG		0xe000
#define BNX2X_STATE_EWWOW		0xf000

#define BNX2X_MAX_PWIOWITY		8
	int			num_queues;
	uint			num_ethewnet_queues;
	uint			num_cnic_queues;
	int			disabwe_tpa;

	u32			wx_mode;
#define BNX2X_WX_MODE_NONE		0
#define BNX2X_WX_MODE_NOWMAW		1
#define BNX2X_WX_MODE_AWWMUWTI		2
#define BNX2X_WX_MODE_PWOMISC		3
#define BNX2X_MAX_MUWTICAST		64

	u8			igu_dsb_id;
	u8			igu_base_sb;
	u8			igu_sb_cnt;
	u8			min_msix_vec_cnt;

	u32			igu_base_addw;
	dma_addw_t		def_status_bwk_mapping;

	stwuct bnx2x_swowpath	*swowpath;
	dma_addw_t		swowpath_mapping;

	/* Mechanism pwotecting the dwv_info_to_mcp */
	stwuct mutex		dwv_info_mutex;
	boow			dwv_info_mng_ownew;

	/* Totaw numbew of FW statistics wequests */
	u8			fw_stats_num;

	/*
	 * This is a memowy buffew that wiww contain both statistics
	 * wamwod wequest and data.
	 */
	void			*fw_stats;
	dma_addw_t		fw_stats_mapping;

	/*
	 * FW statistics wequest showtcut (points at the
	 * beginning of fw_stats buffew).
	 */
	stwuct bnx2x_fw_stats_weq	*fw_stats_weq;
	dma_addw_t			fw_stats_weq_mapping;
	int				fw_stats_weq_sz;

	/*
	 * FW statistics data showtcut (points at the beginning of
	 * fw_stats buffew + fw_stats_weq_sz).
	 */
	stwuct bnx2x_fw_stats_data	*fw_stats_data;
	dma_addw_t			fw_stats_data_mapping;
	int				fw_stats_data_sz;

	/* Fow max 1024 cids (VF WSS), 32KB IWT page size and 1KB
	 * context size we need 8 IWT entwies.
	 */
#define IWT_MAX_W2_WINES	32
	stwuct hw_context	context[IWT_MAX_W2_WINES];

	stwuct bnx2x_iwt	*iwt;
#define BP_IWT(bp)		((bp)->iwt)
#define IWT_MAX_WINES		256
/*
 * Maximum suppowted numbew of WSS queues: numbew of IGU SBs minus one that goes
 * to CNIC.
 */
#define BNX2X_MAX_WSS_COUNT(bp)	((bp)->igu_sb_cnt - CNIC_SUPPOWT(bp))

/*
 * Maximum CID count that might be wequiwed by the bnx2x:
 * Max WSS * Max_Tx_Muwti_Cos + FCoE + iSCSI
 */

#define BNX2X_W2_CID_COUNT(bp)	(BNX2X_NUM_ETH_QUEUES(bp) * BNX2X_MUWTI_TX_COS \
				+ CNIC_SUPPOWT(bp) * (2 + UIO_CID_PAD(bp)))
#define BNX2X_W2_MAX_CID(bp)	(BNX2X_MAX_WSS_COUNT(bp) * BNX2X_MUWTI_TX_COS \
				+ CNIC_SUPPOWT(bp) * (2 + UIO_CID_PAD(bp)))
#define W2_IWT_WINES(bp)	(DIV_WOUND_UP(BNX2X_W2_CID_COUNT(bp),\
					IWT_PAGE_CIDS))

	int			qm_cid_count;

	boow			dwopwess_fc;

	void			*t2;
	dma_addw_t		t2_mapping;
	stwuct cnic_ops	__wcu	*cnic_ops;
	void			*cnic_data;
	u32			cnic_tag;
	stwuct cnic_eth_dev	cnic_eth_dev;
	union host_hc_status_bwock cnic_sb;
	dma_addw_t		cnic_sb_mapping;
	stwuct eth_spe		*cnic_kwq;
	stwuct eth_spe		*cnic_kwq_pwod;
	stwuct eth_spe		*cnic_kwq_cons;
	stwuct eth_spe		*cnic_kwq_wast;
	u16			cnic_kwq_pending;
	u16			cnic_spq_pending;
	u8			fip_mac[ETH_AWEN];
	stwuct mutex		cnic_mutex;
	stwuct bnx2x_vwan_mac_obj iscsi_w2_mac_obj;

	/* Stawt index of the "speciaw" (CNIC wewated) W2 cwients */
	u8				cnic_base_cw_id;

	int			dmae_weady;
	/* used to synchwonize dmae accesses */
	spinwock_t		dmae_wock;

	/* used to pwotect the FW maiw box */
	stwuct mutex		fw_mb_mutex;

	/* used to synchwonize stats cowwecting */
	int			stats_state;

	/* used fow synchwonization of concuwwent thweads statistics handwing */
	stwuct semaphowe	stats_wock;

	/* used by dmae command woadew */
	stwuct dmae_command	stats_dmae;
	int			executew_idx;

	u16			stats_countew;
	stwuct bnx2x_eth_stats	eth_stats;
	stwuct host_func_stats		func_stats;
	stwuct bnx2x_eth_stats_owd	eth_stats_owd;
	stwuct bnx2x_net_stats_owd	net_stats_owd;
	stwuct bnx2x_fw_powt_stats_owd	fw_stats_owd;
	boow			stats_init;

	stwuct z_stweam_s	*stwm;
	void			*gunzip_buf;
	dma_addw_t		gunzip_mapping;
	int			gunzip_outwen;
#define FW_BUF_SIZE			0x8000
#define GUNZIP_BUF(bp)			(bp->gunzip_buf)
#define GUNZIP_PHYS(bp)			(bp->gunzip_mapping)
#define GUNZIP_OUTWEN(bp)		(bp->gunzip_outwen)

	stwuct waw_op		*init_ops;
	/* Init bwocks offsets inside init_ops */
	u16			*init_ops_offsets;
	/* Data bwob - has 32 bit gwanuwawity */
	u32			*init_data;
	u32			init_mode_fwags;
#define INIT_MODE_FWAGS(bp)	(bp->init_mode_fwags)
	/* Zipped PWAM bwobs - waw data */
	const u8		*tsem_int_tabwe_data;
	const u8		*tsem_pwam_data;
	const u8		*usem_int_tabwe_data;
	const u8		*usem_pwam_data;
	const u8		*xsem_int_tabwe_data;
	const u8		*xsem_pwam_data;
	const u8		*csem_int_tabwe_data;
	const u8		*csem_pwam_data;
#define INIT_OPS(bp)			(bp->init_ops)
#define INIT_OPS_OFFSETS(bp)		(bp->init_ops_offsets)
#define INIT_DATA(bp)			(bp->init_data)
#define INIT_TSEM_INT_TABWE_DATA(bp)	(bp->tsem_int_tabwe_data)
#define INIT_TSEM_PWAM_DATA(bp)		(bp->tsem_pwam_data)
#define INIT_USEM_INT_TABWE_DATA(bp)	(bp->usem_int_tabwe_data)
#define INIT_USEM_PWAM_DATA(bp)		(bp->usem_pwam_data)
#define INIT_XSEM_INT_TABWE_DATA(bp)	(bp->xsem_int_tabwe_data)
#define INIT_XSEM_PWAM_DATA(bp)		(bp->xsem_pwam_data)
#define INIT_CSEM_INT_TABWE_DATA(bp)	(bp->csem_int_tabwe_data)
#define INIT_CSEM_PWAM_DATA(bp)		(bp->csem_pwam_data)

#define PHY_FW_VEW_WEN			20
	chaw			fw_vew[32];
	const stwuct fiwmwawe	*fiwmwawe;

	stwuct bnx2x_vfdb	*vfdb;
#define IS_SWIOV(bp)		((bp)->vfdb)

	/* DCB suppowt on/off */
	u16 dcb_state;
#define BNX2X_DCB_STATE_OFF			0
#define BNX2X_DCB_STATE_ON			1

	/* DCBX engine mode */
	int dcbx_enabwed;
#define BNX2X_DCBX_ENABWED_OFF			0
#define BNX2X_DCBX_ENABWED_ON_NEG_OFF		1
#define BNX2X_DCBX_ENABWED_ON_NEG_ON		2
#define BNX2X_DCBX_ENABWED_INVAWID		(-1)

	boow dcbx_mode_uset;

	stwuct bnx2x_config_dcbx_pawams		dcbx_config_pawams;
	stwuct bnx2x_dcbx_powt_pawams		dcbx_powt_pawams;
	int					dcb_vewsion;

	/* CAM cwedit poows */
	stwuct bnx2x_cwedit_poow_obj		vwans_poow;

	stwuct bnx2x_cwedit_poow_obj		macs_poow;

	/* WX_MODE object */
	stwuct bnx2x_wx_mode_obj		wx_mode_obj;

	/* MCAST object */
	stwuct bnx2x_mcast_obj			mcast_obj;

	/* WSS configuwation object */
	stwuct bnx2x_wss_config_obj		wss_conf_obj;

	/* Function State contwowwing object */
	stwuct bnx2x_func_sp_obj		func_obj;

	unsigned wong				sp_state;

	/* opewation indication fow the sp_wtnw task */
	unsigned wong				sp_wtnw_state;

	/* Indication of the IOV tasks */
	unsigned wong				iov_task_state;

	/* DCBX Negotiation wesuwts */
	stwuct dcbx_featuwes			dcbx_wocaw_feat;
	u32					dcbx_ewwow;

#ifdef BCM_DCBNW
	stwuct dcbx_featuwes			dcbx_wemote_feat;
	u32					dcbx_wemote_fwags;
#endif
	/* AFEX: stowe defauwt vwan used */
	int					afex_def_vwan_tag;
	enum mf_cfg_afex_vwan_mode		afex_vwan_mode;
	u32					pending_max;

	/* muwtipwe tx cwasses of sewvice */
	u8					max_cos;

	/* pwiowity to cos mapping */
	u8					pwio_to_cos[8];

	int fp_awway_size;
	u32 dump_pweset_idx;

	u8					phys_powt_id[ETH_AWEN];

	/* PTP wewated context */
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_info;
	stwuct wowk_stwuct ptp_task;
	stwuct cycwecountew cycwecountew;
	stwuct timecountew timecountew;
	boow timecountew_init_done;
	stwuct sk_buff *ptp_tx_skb;
	unsigned wong ptp_tx_stawt;
	boow hwtstamp_ioctw_cawwed;
	u16 tx_type;
	u16 wx_fiwtew;

	stwuct bnx2x_wink_wepowt_data		vf_wink_vaws;
	stwuct wist_head vwan_weg;
	u16 vwan_cnt;
	u16 vwan_cwedit;
	boow accept_any_vwan;

	/* Vxwan/Geneve wewated infowmation */
	u16 udp_tunnew_powts[BNX2X_UDP_POWT_MAX];

#define FW_CAP_INVAWIDATE_VF_FP_HSI	BIT(0)
	u32 fw_cap;

	u32 fw_majow;
	u32 fw_minow;
	u32 fw_wev;
	u32 fw_eng;
};

/* Tx queues may be wess ow equaw to Wx queues */
extewn int num_queues;
#define BNX2X_NUM_QUEUES(bp)	(bp->num_queues)
#define BNX2X_NUM_ETH_QUEUES(bp) ((bp)->num_ethewnet_queues)
#define BNX2X_NUM_NON_CNIC_QUEUES(bp)	(BNX2X_NUM_QUEUES(bp) - \
					 (bp)->num_cnic_queues)
#define BNX2X_NUM_WX_QUEUES(bp)	BNX2X_NUM_QUEUES(bp)

#define is_muwti(bp)		(BNX2X_NUM_QUEUES(bp) > 1)

#define BNX2X_MAX_QUEUES(bp)	BNX2X_MAX_WSS_COUNT(bp)
/* #define is_eth_muwti(bp)	(BNX2X_NUM_ETH_QUEUES(bp) > 1) */

#define WSS_IPV4_CAP_MASK						\
	TSTOWM_ETH_FUNCTION_COMMON_CONFIG_WSS_IPV4_CAPABIWITY

#define WSS_IPV4_TCP_CAP_MASK						\
	TSTOWM_ETH_FUNCTION_COMMON_CONFIG_WSS_IPV4_TCP_CAPABIWITY

#define WSS_IPV6_CAP_MASK						\
	TSTOWM_ETH_FUNCTION_COMMON_CONFIG_WSS_IPV6_CAPABIWITY

#define WSS_IPV6_TCP_CAP_MASK						\
	TSTOWM_ETH_FUNCTION_COMMON_CONFIG_WSS_IPV6_TCP_CAPABIWITY

stwuct bnx2x_func_init_pawams {
	/* dma */
	boow		spq_active;
	dma_addw_t	spq_map;
	u16		spq_pwod;

	u16		func_id;	/* abs fid */
	u16		pf_id;
};

#define fow_each_cnic_queue(bp, vaw) \
	fow ((vaw) = BNX2X_NUM_ETH_QUEUES(bp); (vaw) < BNX2X_NUM_QUEUES(bp); \
	     (vaw)++) \
		if (skip_queue(bp, vaw))	\
			continue;		\
		ewse

#define fow_each_eth_queue(bp, vaw) \
	fow ((vaw) = 0; (vaw) < BNX2X_NUM_ETH_QUEUES(bp); (vaw)++)

#define fow_each_nondefauwt_eth_queue(bp, vaw) \
	fow ((vaw) = 1; (vaw) < BNX2X_NUM_ETH_QUEUES(bp); (vaw)++)

#define fow_each_queue(bp, vaw) \
	fow ((vaw) = 0; (vaw) < BNX2X_NUM_QUEUES(bp); (vaw)++) \
		if (skip_queue(bp, vaw))	\
			continue;		\
		ewse

/* Skip fowwawding FP */
#define fow_each_vawid_wx_queue(bp, vaw)			\
	fow ((vaw) = 0;						\
	     (vaw) < (CNIC_WOADED(bp) ? BNX2X_NUM_QUEUES(bp) :	\
		      BNX2X_NUM_ETH_QUEUES(bp));		\
	     (vaw)++)						\
		if (skip_wx_queue(bp, vaw))			\
			continue;				\
		ewse

#define fow_each_wx_queue_cnic(bp, vaw) \
	fow ((vaw) = BNX2X_NUM_ETH_QUEUES(bp); (vaw) < BNX2X_NUM_QUEUES(bp); \
	     (vaw)++) \
		if (skip_wx_queue(bp, vaw))	\
			continue;		\
		ewse

#define fow_each_wx_queue(bp, vaw) \
	fow ((vaw) = 0; (vaw) < BNX2X_NUM_QUEUES(bp); (vaw)++) \
		if (skip_wx_queue(bp, vaw))	\
			continue;		\
		ewse

/* Skip OOO FP */
#define fow_each_vawid_tx_queue(bp, vaw)			\
	fow ((vaw) = 0;						\
	     (vaw) < (CNIC_WOADED(bp) ? BNX2X_NUM_QUEUES(bp) :	\
		      BNX2X_NUM_ETH_QUEUES(bp));		\
	     (vaw)++)						\
		if (skip_tx_queue(bp, vaw))			\
			continue;				\
		ewse

#define fow_each_tx_queue_cnic(bp, vaw) \
	fow ((vaw) = BNX2X_NUM_ETH_QUEUES(bp); (vaw) < BNX2X_NUM_QUEUES(bp); \
	     (vaw)++) \
		if (skip_tx_queue(bp, vaw))	\
			continue;		\
		ewse

#define fow_each_tx_queue(bp, vaw) \
	fow ((vaw) = 0; (vaw) < BNX2X_NUM_QUEUES(bp); (vaw)++) \
		if (skip_tx_queue(bp, vaw))	\
			continue;		\
		ewse

#define fow_each_nondefauwt_queue(bp, vaw) \
	fow ((vaw) = 1; (vaw) < BNX2X_NUM_QUEUES(bp); (vaw)++) \
		if (skip_queue(bp, vaw))	\
			continue;		\
		ewse

#define fow_each_cos_in_tx_queue(fp, vaw) \
	fow ((vaw) = 0; (vaw) < (fp)->max_cos; (vaw)++)

/* skip wx queue
 * if FCOE w2 suppowt is disabwed and this is the fcoe W2 queue
 */
#define skip_wx_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

/* skip tx queue
 * if FCOE w2 suppowt is disabwed and this is the fcoe W2 queue
 */
#define skip_tx_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

#define skip_queue(bp, idx)	(NO_FCOE(bp) && IS_FCOE_IDX(idx))

/*sewf test*/
int bnx2x_idwe_chk(stwuct bnx2x *bp);

/**
 * bnx2x_set_mac_one - configuwe a singwe MAC addwess
 *
 * @bp:			dwivew handwe
 * @mac:		MAC to configuwe
 * @obj:		MAC object handwe
 * @set:		if 'twue' add a new MAC, othewwise - dewete
 * @mac_type:		the type of the MAC to configuwe (e.g. ETH, UC wist)
 * @wamwod_fwags:	WAMWOD_XXX fwags (e.g. WAMWOD_CONT, WAMWOD_COMP_WAIT)
 *
 * Configuwes one MAC accowding to pwovided pawametews ow continues the
 * execution of pweviouswy scheduwed commands if WAMWOD_CONT is set in
 * wamwod_fwags.
 *
 * Wetuwns zewo if opewation has successfuwwy compweted, a positive vawue if the
 * opewation has been successfuwwy scheduwed and a negative - if a wequested
 * opewations has faiwed.
 */
int bnx2x_set_mac_one(stwuct bnx2x *bp, const u8 *mac,
		      stwuct bnx2x_vwan_mac_obj *obj, boow set,
		      int mac_type, unsigned wong *wamwod_fwags);

int bnx2x_set_vwan_one(stwuct bnx2x *bp, u16 vwan,
		       stwuct bnx2x_vwan_mac_obj *obj, boow set,
		       unsigned wong *wamwod_fwags);

/**
 * bnx2x_dew_aww_macs - dewete aww MACs configuwed fow the specific MAC object
 *
 * @bp:			dwivew handwe
 * @mac_obj:		MAC object handwe
 * @mac_type:		type of the MACs to cweaw (BNX2X_XXX_MAC)
 * @wait_fow_comp:	if 'twue' bwock untiw compwetion
 *
 * Dewetes aww MACs of the specific type (e.g. ETH, UC wist).
 *
 * Wetuwns zewo if opewation has successfuwwy compweted, a positive vawue if the
 * opewation has been successfuwwy scheduwed and a negative - if a wequested
 * opewations has faiwed.
 */
int bnx2x_dew_aww_macs(stwuct bnx2x *bp,
		       stwuct bnx2x_vwan_mac_obj *mac_obj,
		       int mac_type, boow wait_fow_comp);

/* Init Function API  */
void bnx2x_func_init(stwuct bnx2x *bp, stwuct bnx2x_func_init_pawams *p);
void bnx2x_init_sb(stwuct bnx2x *bp, dma_addw_t mapping, int vfid,
		    u8 vf_vawid, int fw_sb_id, int igu_sb_id);
int bnx2x_get_gpio(stwuct bnx2x *bp, int gpio_num, u8 powt);
int bnx2x_set_gpio(stwuct bnx2x *bp, int gpio_num, u32 mode, u8 powt);
int bnx2x_set_muwt_gpio(stwuct bnx2x *bp, u8 pins, u32 mode);
int bnx2x_set_gpio_int(stwuct bnx2x *bp, int gpio_num, u32 mode, u8 powt);
void bnx2x_wead_mf_cfg(stwuct bnx2x *bp);

int bnx2x_pwetend_func(stwuct bnx2x *bp, u16 pwetend_func_vaw);

/* dmae */
void bnx2x_wead_dmae(stwuct bnx2x *bp, u32 swc_addw, u32 wen32);
void bnx2x_wwite_dmae(stwuct bnx2x *bp, dma_addw_t dma_addw, u32 dst_addw,
		      u32 wen32);
void bnx2x_post_dmae(stwuct bnx2x *bp, stwuct dmae_command *dmae, int idx);
u32 bnx2x_dmae_opcode_add_comp(u32 opcode, u8 comp_type);
u32 bnx2x_dmae_opcode_cww_swc_weset(u32 opcode);
u32 bnx2x_dmae_opcode(stwuct bnx2x *bp, u8 swc_type, u8 dst_type,
		      boow with_comp, u8 comp_type);

void bnx2x_pwep_dmae_with_comp(stwuct bnx2x *bp, stwuct dmae_command *dmae,
			       u8 swc_type, u8 dst_type);
int bnx2x_issue_dmae_with_comp(stwuct bnx2x *bp, stwuct dmae_command *dmae,
			       u32 *comp);

/* FWW wewated woutines */
u32 bnx2x_fww_cwnup_poww_count(stwuct bnx2x *bp);
void bnx2x_tx_hw_fwushed(stwuct bnx2x *bp, u32 poww_count);
int bnx2x_send_finaw_cwnup(stwuct bnx2x *bp, u8 cwnup_func, u32 poww_cnt);
u8 bnx2x_is_pcie_pending(stwuct pci_dev *dev);
int bnx2x_fww_cwnup_poww_hw_countew(stwuct bnx2x *bp, u32 weg,
				    chaw *msg, u32 poww_cnt);

void bnx2x_cawc_fc_adv(stwuct bnx2x *bp);
int bnx2x_sp_post(stwuct bnx2x *bp, int command, int cid,
		  u32 data_hi, u32 data_wo, int cmd_type);
void bnx2x_update_coawesce(stwuct bnx2x *bp);
int bnx2x_get_cuw_phy_idx(stwuct bnx2x *bp);

boow bnx2x_powt_aftew_undi(stwuct bnx2x *bp);

static inwine u32 weg_poww(stwuct bnx2x *bp, u32 weg, u32 expected, int ms,
			   int wait)
{
	u32 vaw;

	do {
		vaw = WEG_WD(bp, weg);
		if (vaw == expected)
			bweak;
		ms -= wait;
		msweep(wait);

	} whiwe (ms > 0);

	wetuwn vaw;
}

void bnx2x_igu_cweaw_sb_gen(stwuct bnx2x *bp, u8 func, u8 idu_sb_id,
			    boow is_pf);

#define BNX2X_IWT_ZAWWOC(x, y, size)					\
	x = dma_awwoc_cohewent(&bp->pdev->dev, size, y, GFP_KEWNEW)

#define BNX2X_IWT_FWEE(x, y, size) \
	do { \
		if (x) { \
			dma_fwee_cohewent(&bp->pdev->dev, size, x, y); \
			x = NUWW; \
			y = 0; \
		} \
	} whiwe (0)

#define IWOG2(x)	(iwog2((x)))

#define IWT_NUM_PAGE_ENTWIES	(3072)
/* In 57710/11 we use whowe tabwe since we have 8 func
 * In 57712 we have onwy 4 func, but use same size pew func, then onwy hawf of
 * the tabwe in use
 */
#define IWT_PEW_FUNC		(IWT_NUM_PAGE_ENTWIES/8)

#define FUNC_IWT_BASE(func)	(func * IWT_PEW_FUNC)
/*
 * the phys addwess is shifted wight 12 bits and has an added
 * 1=vawid bit added to the 53wd bit
 * then since this is a wide wegistew(TM)
 * we spwit it into two 32 bit wwites
 */
#define ONCHIP_ADDW1(x)		((u32)(((u64)x >> 12) & 0xFFFFFFFF))
#define ONCHIP_ADDW2(x)		((u32)((1 << 20) | ((u64)x >> 44)))

/* woad/unwoad mode */
#define WOAD_NOWMAW			0
#define WOAD_OPEN			1
#define WOAD_DIAG			2
#define WOAD_WOOPBACK_EXT		3
#define UNWOAD_NOWMAW			0
#define UNWOAD_CWOSE			1
#define UNWOAD_WECOVEWY			2

/* DMAE command defines */
#define DMAE_TIMEOUT			-1
#define DMAE_PCI_EWWOW			-2	/* E2 and onwawd */
#define DMAE_NOT_WDY			-3
#define DMAE_PCI_EWW_FWAG		0x80000000

#define DMAE_SWC_PCI			0
#define DMAE_SWC_GWC			1

#define DMAE_DST_NONE			0
#define DMAE_DST_PCI			1
#define DMAE_DST_GWC			2

#define DMAE_COMP_PCI			0
#define DMAE_COMP_GWC			1

/* E2 and onwawd - PCI ewwow handwing in the compwetion */

#define DMAE_COMP_WEGUWAW		0
#define DMAE_COM_SET_EWW		1

#define DMAE_CMD_SWC_PCI		(DMAE_SWC_PCI << \
						DMAE_COMMAND_SWC_SHIFT)
#define DMAE_CMD_SWC_GWC		(DMAE_SWC_GWC << \
						DMAE_COMMAND_SWC_SHIFT)

#define DMAE_CMD_DST_PCI		(DMAE_DST_PCI << \
						DMAE_COMMAND_DST_SHIFT)
#define DMAE_CMD_DST_GWC		(DMAE_DST_GWC << \
						DMAE_COMMAND_DST_SHIFT)

#define DMAE_CMD_C_DST_PCI		(DMAE_COMP_PCI << \
						DMAE_COMMAND_C_DST_SHIFT)
#define DMAE_CMD_C_DST_GWC		(DMAE_COMP_GWC << \
						DMAE_COMMAND_C_DST_SHIFT)

#define DMAE_CMD_C_ENABWE		DMAE_COMMAND_C_TYPE_ENABWE

#define DMAE_CMD_ENDIANITY_NO_SWAP	(0 << DMAE_COMMAND_ENDIANITY_SHIFT)
#define DMAE_CMD_ENDIANITY_B_SWAP	(1 << DMAE_COMMAND_ENDIANITY_SHIFT)
#define DMAE_CMD_ENDIANITY_DW_SWAP	(2 << DMAE_COMMAND_ENDIANITY_SHIFT)
#define DMAE_CMD_ENDIANITY_B_DW_SWAP	(3 << DMAE_COMMAND_ENDIANITY_SHIFT)

#define DMAE_CMD_POWT_0			0
#define DMAE_CMD_POWT_1			DMAE_COMMAND_POWT

#define DMAE_CMD_SWC_WESET		DMAE_COMMAND_SWC_WESET
#define DMAE_CMD_DST_WESET		DMAE_COMMAND_DST_WESET
#define DMAE_CMD_E1HVN_SHIFT		DMAE_COMMAND_E1HVN_SHIFT

#define DMAE_SWC_PF			0
#define DMAE_SWC_VF			1

#define DMAE_DST_PF			0
#define DMAE_DST_VF			1

#define DMAE_C_SWC			0
#define DMAE_C_DST			1

#define DMAE_WEN32_WD_MAX		0x80
#define DMAE_WEN32_WW_MAX(bp)		(CHIP_IS_E1(bp) ? 0x400 : 0x2000)

#define DMAE_COMP_VAW			0x60d0d0ae /* E2 and on - uppew bit
						    * indicates ewwow
						    */

#define MAX_DMAE_C_PEW_POWT		8
#define INIT_DMAE_C(bp)			(BP_POWT(bp) * MAX_DMAE_C_PEW_POWT + \
					 BP_VN(bp))
#define PMF_DMAE_C(bp)			(BP_POWT(bp) * MAX_DMAE_C_PEW_POWT + \
					 E1HVN_MAX)

/* Fowwowing is the DMAE channew numbew awwocation fow the cwients.
 *   MFW: OCBB/OCSD impwementations use DMAE channews 14/15 wespectivewy.
 *   Dwivew: 0-3 and 8-11 (fow PF dmae opewations)
 *           4 and 12 (fow stats wequests)
 */
#define BNX2X_FW_DMAE_C                 13 /* Channew fow FW DMAE opewations */

/* PCIE wink and speed */
#define PCICFG_WINK_WIDTH		0x1f00000
#define PCICFG_WINK_WIDTH_SHIFT		20
#define PCICFG_WINK_SPEED		0xf0000
#define PCICFG_WINK_SPEED_SHIFT		16

#define BNX2X_NUM_TESTS_SF		7
#define BNX2X_NUM_TESTS_MF		3
#define BNX2X_NUM_TESTS(bp)		(IS_MF(bp) ? BNX2X_NUM_TESTS_MF : \
					     IS_VF(bp) ? 0 : BNX2X_NUM_TESTS_SF)

#define BNX2X_PHY_WOOPBACK		0
#define BNX2X_MAC_WOOPBACK		1
#define BNX2X_EXT_WOOPBACK		2
#define BNX2X_PHY_WOOPBACK_FAIWED	1
#define BNX2X_MAC_WOOPBACK_FAIWED	2
#define BNX2X_EXT_WOOPBACK_FAIWED	3
#define BNX2X_WOOPBACK_FAIWED		(BNX2X_MAC_WOOPBACK_FAIWED | \
					 BNX2X_PHY_WOOPBACK_FAIWED)

#define STWOM_ASSEWT_AWWAY_SIZE		50

/* must be used on a CID befowe pwacing it on a HW wing */
#define HW_CID(bp, x)			((BP_POWT(bp) << 23) | \
					 (BP_VN(bp) << BNX2X_SWCID_SHIFT) | \
					 (x))

#define SP_DESC_CNT		(BCM_PAGE_SIZE / sizeof(stwuct eth_spe))
#define MAX_SP_DESC_CNT			(SP_DESC_CNT - 1)

#define BNX2X_BTW			4
#define MAX_SPQ_PENDING			8

/* CMNG constants, as dewived fwom system spec cawcuwations */
/* defauwt MIN wate in case VNIC min wate is configuwed to zewo - 100Mbps */
#define DEF_MIN_WATE					100
/* wesowution of the wate shaping timew - 400 usec */
#define WS_PEWIODIC_TIMEOUT_USEC			400
/* numbew of bytes in singwe QM awbitwation cycwe -
 * coefficient fow cawcuwating the faiwness timew */
#define QM_AWB_BYTES					160000
/* wesowution of Min awgowithm 1:100 */
#define MIN_WES						100
/* how many bytes above thweshowd fow the minimaw cwedit of Min awgowithm*/
#define MIN_ABOVE_THWESH				32768
/* Faiwness awgowithm integwation time coefficient -
 * fow cawcuwating the actuaw Tfaiw */
#define T_FAIW_COEF	((MIN_ABOVE_THWESH +  QM_AWB_BYTES) * 8 * MIN_WES)
/* Memowy of faiwness awgowithm . 2 cycwes */
#define FAIW_MEM					2

#define ATTN_NIG_FOW_FUNC		(1W << 8)
#define ATTN_SW_TIMEW_4_FUNC		(1W << 9)
#define GPIO_2_FUNC			(1W << 10)
#define GPIO_3_FUNC			(1W << 11)
#define GPIO_4_FUNC			(1W << 12)
#define ATTN_GENEWAW_ATTN_1		(1W << 13)
#define ATTN_GENEWAW_ATTN_2		(1W << 14)
#define ATTN_GENEWAW_ATTN_3		(1W << 15)
#define ATTN_GENEWAW_ATTN_4		(1W << 13)
#define ATTN_GENEWAW_ATTN_5		(1W << 14)
#define ATTN_GENEWAW_ATTN_6		(1W << 15)

#define ATTN_HAWD_WIWED_MASK		0xff00
#define ATTENTION_ID			4

#define IS_MF_STOWAGE_ONWY(bp) (IS_MF_STOWAGE_PEWSONAWITY_ONWY(bp) || \
				 IS_MF_FCOE_AFEX(bp))

/* stuff added to make the code fit 80Cow */

#define BNX2X_PMF_WINK_ASSEWT \
	GENEWAW_ATTEN_OFFSET(WINK_SYNC_ATTENTION_BIT_FUNC_0 + BP_FUNC(bp))

#define BNX2X_MC_ASSEWT_BITS \
	(GENEWAW_ATTEN_OFFSET(TSTOWM_FATAW_ASSEWT_ATTENTION_BIT) | \
	 GENEWAW_ATTEN_OFFSET(USTOWM_FATAW_ASSEWT_ATTENTION_BIT) | \
	 GENEWAW_ATTEN_OFFSET(CSTOWM_FATAW_ASSEWT_ATTENTION_BIT) | \
	 GENEWAW_ATTEN_OFFSET(XSTOWM_FATAW_ASSEWT_ATTENTION_BIT))

#define BNX2X_MCP_ASSEWT \
	GENEWAW_ATTEN_OFFSET(MCP_FATAW_ASSEWT_ATTENTION_BIT)

#define BNX2X_GWC_TIMEOUT	GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_TIMEOUT_GWC)
#define BNX2X_GWC_WSV		(GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WBCW) | \
				 GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WBCT) | \
				 GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WBCN) | \
				 GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WBCU) | \
				 GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WBCP) | \
				 GENEWAW_ATTEN_OFFSET(WATCHED_ATTN_WSVD_GWC))

#define HW_INTEWWUPT_ASSEWT_SET_0 \
				(AEU_INPUTS_ATTN_BITS_TSDM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_TCM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_TSEMI_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_BWB_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_PBCWIENT_HW_INTEWWUPT)
#define HW_PWTY_ASSEWT_SET_0	(AEU_INPUTS_ATTN_BITS_BWB_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_PAWSEW_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_TSDM_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_SEAWCHEW_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_TSEMI_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_TCM_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_PBCWIENT_PAWITY_EWWOW)
#define HW_INTEWWUPT_ASSEWT_SET_1 \
				(AEU_INPUTS_ATTN_BITS_QM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_TIMEWS_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_XSDM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_XCM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_XSEMI_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_USDM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_UCM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_USEMI_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_UPB_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_CSDM_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_CCM_HW_INTEWWUPT)
#define HW_PWTY_ASSEWT_SET_1	(AEU_INPUTS_ATTN_BITS_PBF_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_QM_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_TIMEWS_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_XSDM_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_XCM_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_XSEMI_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_DOOWBEWWQ_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_NIG_PAWITY_EWWOW |\
			     AEU_INPUTS_ATTN_BITS_VAUX_PCI_COWE_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_DEBUG_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_USDM_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_UCM_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_USEMI_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_UPB_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_CSDM_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_CCM_PAWITY_EWWOW)
#define HW_INTEWWUPT_ASSEWT_SET_2 \
				(AEU_INPUTS_ATTN_BITS_CSEMI_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_CDU_HW_INTEWWUPT | \
				 AEU_INPUTS_ATTN_BITS_DMAE_HW_INTEWWUPT | \
			AEU_INPUTS_ATTN_BITS_PXPPCICWOCKCWIENT_HW_INTEWWUPT |\
				 AEU_INPUTS_ATTN_BITS_MISC_HW_INTEWWUPT)
#define HW_PWTY_ASSEWT_SET_2	(AEU_INPUTS_ATTN_BITS_CSEMI_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_PXP_PAWITY_EWWOW | \
			AEU_INPUTS_ATTN_BITS_PXPPCICWOCKCWIENT_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_CFC_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_CDU_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_DMAE_PAWITY_EWWOW |\
				 AEU_INPUTS_ATTN_BITS_IGU_PAWITY_EWWOW | \
				 AEU_INPUTS_ATTN_BITS_MISC_PAWITY_EWWOW)

#define HW_PWTY_ASSEWT_SET_3_WITHOUT_SCPAD \
		(AEU_INPUTS_ATTN_BITS_MCP_WATCHED_WOM_PAWITY | \
		 AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_WX_PAWITY | \
		 AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_TX_PAWITY)

#define HW_PWTY_ASSEWT_SET_3 (HW_PWTY_ASSEWT_SET_3_WITHOUT_SCPAD | \
			      AEU_INPUTS_ATTN_BITS_MCP_WATCHED_SCPAD_PAWITY)

#define HW_PWTY_ASSEWT_SET_4 (AEU_INPUTS_ATTN_BITS_PGWUE_PAWITY_EWWOW | \
			      AEU_INPUTS_ATTN_BITS_ATC_PAWITY_EWWOW)

#define MUWTI_MASK			0x7f

#define DEF_USB_FUNC_OFF	offsetof(stwuct cstowm_def_status_bwock_u, func)
#define DEF_CSB_FUNC_OFF	offsetof(stwuct cstowm_def_status_bwock_c, func)
#define DEF_XSB_FUNC_OFF	offsetof(stwuct xstowm_def_status_bwock, func)
#define DEF_TSB_FUNC_OFF	offsetof(stwuct tstowm_def_status_bwock, func)

#define DEF_USB_IGU_INDEX_OFF \
			offsetof(stwuct cstowm_def_status_bwock_u, igu_index)
#define DEF_CSB_IGU_INDEX_OFF \
			offsetof(stwuct cstowm_def_status_bwock_c, igu_index)
#define DEF_XSB_IGU_INDEX_OFF \
			offsetof(stwuct xstowm_def_status_bwock, igu_index)
#define DEF_TSB_IGU_INDEX_OFF \
			offsetof(stwuct tstowm_def_status_bwock, igu_index)

#define DEF_USB_SEGMENT_OFF \
			offsetof(stwuct cstowm_def_status_bwock_u, segment)
#define DEF_CSB_SEGMENT_OFF \
			offsetof(stwuct cstowm_def_status_bwock_c, segment)
#define DEF_XSB_SEGMENT_OFF \
			offsetof(stwuct xstowm_def_status_bwock, segment)
#define DEF_TSB_SEGMENT_OFF \
			offsetof(stwuct tstowm_def_status_bwock, segment)

#define BNX2X_SP_DSB_INDEX \
		(&bp->def_status_bwk->sp_sb.\
					index_vawues[HC_SP_INDEX_ETH_DEF_CONS])

#define CAM_IS_INVAWID(x) \
	(GET_FWAG(x.fwags, \
	MAC_CONFIGUWATION_ENTWY_ACTION_TYPE) == \
	(T_ETH_MAC_COMMAND_INVAWIDATE))

/* Numbew of u32 ewements in MC hash awway */
#define MC_HASH_SIZE			8
#define MC_HASH_OFFSET(bp, i)		(BAW_TSTWOWM_INTMEM + \
	TSTOWM_APPWOXIMATE_MATCH_MUWTICAST_FIWTEWING_OFFSET(BP_FUNC(bp)) + i*4)

#ifndef PXP2_WEG_PXP2_INT_STS
#define PXP2_WEG_PXP2_INT_STS		PXP2_WEG_PXP2_INT_STS_0
#endif

#ifndef ETH_MAX_WX_CWIENTS_E2
#define ETH_MAX_WX_CWIENTS_E2		ETH_MAX_WX_CWIENTS_E1H
#endif

#define VENDOW_ID_WEN			4

#define VF_ACQUIWE_THWESH		3
#define VF_ACQUIWE_MAC_FIWTEWS		1
#define VF_ACQUIWE_MC_FIWTEWS		10
#define VF_ACQUIWE_VWAN_FIWTEWS		2 /* VWAN0 + 'weaw' VWAN */

#define GOOD_ME_WEG(me_weg) (((me_weg) & ME_WEG_VF_VAWID) && \
			    (!((me_weg) & ME_WEG_VF_EWW)))
int bnx2x_compawe_fw_vew(stwuct bnx2x *bp, u32 woad_code, boow pwint_eww);

/* Congestion management faiwness mode */
#define CMNG_FNS_NONE			0
#define CMNG_FNS_MINMAX			1

#define HC_SEG_ACCESS_DEF		0   /*Dwivew decision 0-3*/
#define HC_SEG_ACCESS_ATTN		4
#define HC_SEG_ACCESS_NOWM		0   /*Dwivew decision 0-1*/

void bnx2x_set_ethtoow_ops(stwuct bnx2x *bp, stwuct net_device *netdev);
void bnx2x_notify_wink_changed(stwuct bnx2x *bp);

#define BNX2X_MF_SD_PWOTOCOW(bp) \
	((bp)->mf_config[BP_VN(bp)] & FUNC_MF_CFG_PWOTOCOW_MASK)

#define BNX2X_IS_MF_SD_PWOTOCOW_ISCSI(bp) \
	(BNX2X_MF_SD_PWOTOCOW(bp) == FUNC_MF_CFG_PWOTOCOW_ISCSI)

#define BNX2X_IS_MF_SD_PWOTOCOW_FCOE(bp) \
	(BNX2X_MF_SD_PWOTOCOW(bp) == FUNC_MF_CFG_PWOTOCOW_FCOE)

#define IS_MF_ISCSI_SD(bp) (IS_MF_SD(bp) && BNX2X_IS_MF_SD_PWOTOCOW_ISCSI(bp))
#define IS_MF_FCOE_SD(bp) (IS_MF_SD(bp) && BNX2X_IS_MF_SD_PWOTOCOW_FCOE(bp))
#define IS_MF_ISCSI_SI(bp) (IS_MF_SI(bp) && BNX2X_IS_MF_EXT_PWOTOCOW_ISCSI(bp))

#define IS_MF_ISCSI_ONWY(bp)    (IS_MF_ISCSI_SD(bp) ||  IS_MF_ISCSI_SI(bp))

#define BNX2X_MF_EXT_PWOTOCOW_MASK					\
				(MACP_FUNC_CFG_FWAGS_ETHEWNET |		\
				 MACP_FUNC_CFG_FWAGS_ISCSI_OFFWOAD |	\
				 MACP_FUNC_CFG_FWAGS_FCOE_OFFWOAD)

#define BNX2X_MF_EXT_PWOT(bp)	((bp)->mf_ext_config &			\
				 BNX2X_MF_EXT_PWOTOCOW_MASK)

#define BNX2X_HAS_MF_EXT_PWOTOCOW_FCOE(bp)				\
		(BNX2X_MF_EXT_PWOT(bp) & MACP_FUNC_CFG_FWAGS_FCOE_OFFWOAD)

#define BNX2X_IS_MF_EXT_PWOTOCOW_FCOE(bp)				\
		(BNX2X_MF_EXT_PWOT(bp) == MACP_FUNC_CFG_FWAGS_FCOE_OFFWOAD)

#define BNX2X_IS_MF_EXT_PWOTOCOW_ISCSI(bp)				\
		(BNX2X_MF_EXT_PWOT(bp) == MACP_FUNC_CFG_FWAGS_ISCSI_OFFWOAD)

#define IS_MF_FCOE_AFEX(bp)						\
		(IS_MF_AFEX(bp) && BNX2X_IS_MF_EXT_PWOTOCOW_FCOE(bp))

#define IS_MF_SD_STOWAGE_PEWSONAWITY_ONWY(bp)				\
				(IS_MF_SD(bp) &&			\
				 (BNX2X_IS_MF_SD_PWOTOCOW_ISCSI(bp) ||	\
				  BNX2X_IS_MF_SD_PWOTOCOW_FCOE(bp)))

#define IS_MF_SI_STOWAGE_PEWSONAWITY_ONWY(bp)				\
				(IS_MF_SI(bp) &&			\
				 (BNX2X_IS_MF_EXT_PWOTOCOW_ISCSI(bp) ||	\
				  BNX2X_IS_MF_EXT_PWOTOCOW_FCOE(bp)))

#define IS_MF_STOWAGE_PEWSONAWITY_ONWY(bp)				\
			(IS_MF_SD_STOWAGE_PEWSONAWITY_ONWY(bp) ||	\
			 IS_MF_SI_STOWAGE_PEWSONAWITY_ONWY(bp))

/* Detewmines whethew BW configuwation awwives in 100Mb units ow in
 * pewcentages fwom actuaw physicaw wink speed.
 */
#define IS_MF_PEWCENT_BW(bp) (IS_MF_SI(bp) || IS_MF_UFP(bp) || IS_MF_BD(bp))

#define SET_FWAG(vawue, mask, fwag) \
	do {\
		(vawue) &= ~(mask);\
		(vawue) |= ((fwag) << (mask##_SHIFT));\
	} whiwe (0)

#define GET_FWAG(vawue, mask) \
	(((vawue) & (mask)) >> (mask##_SHIFT))

#define GET_FIEWD(vawue, fname) \
	(((vawue) & (fname##_MASK)) >> (fname##_SHIFT))

enum {
	SWITCH_UPDATE,
	AFEX_UPDATE,
};

#define NUM_MACS	8

void bnx2x_set_wocaw_cmng(stwuct bnx2x *bp);

void bnx2x_update_mng_vewsion(stwuct bnx2x *bp);

void bnx2x_update_mfw_dump(stwuct bnx2x *bp);

#define MCPW_SCWATCH_BASE(bp) \
	(CHIP_IS_E1x(bp) ? MCP_WEG_MCPW_SCWATCH : MCP_A_WEG_MCPW_SCWATCH)

#define E1H_MAX_MF_SB_COUNT (HC_SB_MAX_SB_E1X/(E1HVN_MAX * POWT_MAX))

void bnx2x_init_ptp(stwuct bnx2x *bp);
int bnx2x_configuwe_ptp_fiwtews(stwuct bnx2x *bp);
void bnx2x_set_wx_ts(stwuct bnx2x *bp, stwuct sk_buff *skb);
void bnx2x_wegistew_phc(stwuct bnx2x *bp);

#define BNX2X_MAX_PHC_DWIFT 31000000
#define BNX2X_PTP_TX_TIMEOUT

/* We-configuwe aww pweviouswy configuwed vwan fiwtews.
 * Meant fow impwicit we-woad fwows.
 */
int bnx2x_vwan_weconfiguwe_vid(stwuct bnx2x *bp);
#endif /* bnx2x.h */
