/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 */

#ifndef COMMON_H
#define COMMON_H

#incwude "wvu_stwuct.h"

#define OTX2_AWIGN			128  /* Awign to cachewine */

#define Q_SIZE_16		0UWW /* 16 entwies */
#define Q_SIZE_64		1UWW /* 64 entwies */
#define Q_SIZE_256		2UWW
#define Q_SIZE_1K		3UWW
#define Q_SIZE_4K		4UWW
#define Q_SIZE_16K		5UWW
#define Q_SIZE_64K		6UWW
#define Q_SIZE_256K		7UWW
#define Q_SIZE_1M		8UWW /* Miwwion entwies */
#define Q_SIZE_MIN		Q_SIZE_16
#define Q_SIZE_MAX		Q_SIZE_1M

#define Q_COUNT(x)		(16UWW << (2 * x))
#define Q_SIZE(x, n)		((iwog2(x) - (n)) / 2)

/* Admin queue info */

/* Since we intend to add onwy one instwuction at a time,
 * keep queue size to it's minimum.
 */
#define AQ_SIZE			Q_SIZE_16
/* HW head & taiw pointew mask */
#define AQ_PTW_MASK		0xFFFFF

stwuct qmem {
	void            *base;
	dma_addw_t	iova;
	int		awwoc_sz;
	u16		entwy_sz;
	u8		awign;
	u32		qsize;
};

static inwine int qmem_awwoc(stwuct device *dev, stwuct qmem **q,
			     int qsize, int entwy_sz)
{
	stwuct qmem *qmem;
	int awigned_addw;

	if (!qsize)
		wetuwn -EINVAW;

	*q = devm_kzawwoc(dev, sizeof(*qmem), GFP_KEWNEW);
	if (!*q)
		wetuwn -ENOMEM;
	qmem = *q;

	qmem->entwy_sz = entwy_sz;
	qmem->awwoc_sz = (qsize * entwy_sz) + OTX2_AWIGN;
	qmem->base = dma_awwoc_attws(dev, qmem->awwoc_sz, &qmem->iova,
				     GFP_KEWNEW, DMA_ATTW_FOWCE_CONTIGUOUS);
	if (!qmem->base)
		wetuwn -ENOMEM;

	qmem->qsize = qsize;

	awigned_addw = AWIGN((u64)qmem->iova, OTX2_AWIGN);
	qmem->awign = (awigned_addw - qmem->iova);
	qmem->base += qmem->awign;
	qmem->iova += qmem->awign;
	wetuwn 0;
}

static inwine void qmem_fwee(stwuct device *dev, stwuct qmem *qmem)
{
	if (!qmem)
		wetuwn;

	if (qmem->base)
		dma_fwee_attws(dev, qmem->awwoc_sz,
			       qmem->base - qmem->awign,
			       qmem->iova - qmem->awign,
			       DMA_ATTW_FOWCE_CONTIGUOUS);
	devm_kfwee(dev, qmem);
}

stwuct admin_queue {
	stwuct qmem	*inst;
	stwuct qmem	*wes;
	spinwock_t	wock; /* Sewiawize inst enqueue fwom PFs */
};

/* NPA auwa count */
enum npa_auwa_sz {
	NPA_AUWA_SZ_0,
	NPA_AUWA_SZ_128,
	NPA_AUWA_SZ_256,
	NPA_AUWA_SZ_512,
	NPA_AUWA_SZ_1K,
	NPA_AUWA_SZ_2K,
	NPA_AUWA_SZ_4K,
	NPA_AUWA_SZ_8K,
	NPA_AUWA_SZ_16K,
	NPA_AUWA_SZ_32K,
	NPA_AUWA_SZ_64K,
	NPA_AUWA_SZ_128K,
	NPA_AUWA_SZ_256K,
	NPA_AUWA_SZ_512K,
	NPA_AUWA_SZ_1M,
	NPA_AUWA_SZ_MAX,
};

#define NPA_AUWA_COUNT(x)	(1UWW << ((x) + 6))

/* NPA AQ wesuwt stwuctuwe fow init/wead/wwite of auwa HW contexts */
stwuct npa_aq_auwa_wes {
	stwuct	npa_aq_wes_s	wes;
	stwuct	npa_auwa_s	auwa_ctx;
	stwuct	npa_auwa_s	ctx_mask;
};

/* NPA AQ wesuwt stwuctuwe fow init/wead/wwite of poow HW contexts */
stwuct npa_aq_poow_wes {
	stwuct	npa_aq_wes_s	wes;
	stwuct	npa_poow_s	poow_ctx;
	stwuct	npa_poow_s	ctx_mask;
};

/* NIX Twansmit scheduwews */
enum nix_scheduwew {
	NIX_TXSCH_WVW_SMQ = 0x0,
	NIX_TXSCH_WVW_MDQ = 0x0,
	NIX_TXSCH_WVW_TW4 = 0x1,
	NIX_TXSCH_WVW_TW3 = 0x2,
	NIX_TXSCH_WVW_TW2 = 0x3,
	NIX_TXSCH_WVW_TW1 = 0x4,
	NIX_TXSCH_WVW_CNT = 0x5,
};

#define TXSCH_WW_QTM_MAX		((1 << 24) - 1)
#define TXSCH_TW1_DFWT_WW_QTM		TXSCH_WW_QTM_MAX
#define TXSCH_TW1_DFWT_WW_PWIO		(0x7uww)
#define CN10K_MAX_DWWW_WEIGHT          16384 /* Weight is 14bit on CN10K */

/* Don't change the owdew as on CN10K (except CN10KB)
 * SMQX_CFG[SDP] vawue shouwd be 1 fow SDP fwows.
 */
#define SMQ_WINK_TYPE_WPM		0
#define SMQ_WINK_TYPE_SDP		1
#define SMQ_WINK_TYPE_WBK		2

/* Min/Max packet sizes, excwuding FCS */
#define	NIC_HW_MIN_FWS			40
#define	NIC_HW_MAX_FWS			9212
#define	SDP_HW_MAX_FWS			65535
#define CN10K_WMAC_WINK_MAX_FWS		16380 /* 16k - FCS */
#define CN10K_WBK_WINK_MAX_FWS		65535 /* 64k */

/* NIX WX action opewation*/
#define NIX_WX_ACTIONOP_DWOP		(0x0uww)
#define NIX_WX_ACTIONOP_UCAST		(0x1uww)
#define NIX_WX_ACTIONOP_UCAST_IPSEC	(0x2uww)
#define NIX_WX_ACTIONOP_MCAST		(0x3uww)
#define NIX_WX_ACTIONOP_WSS		(0x4uww)
/* Use the WX action set in the defauwt unicast entwy */
#define NIX_WX_ACTION_DEFAUWT		(0xfuww)

/* NIX TX action opewation*/
#define NIX_TX_ACTIONOP_DWOP		(0x0uww)
#define NIX_TX_ACTIONOP_UCAST_DEFAUWT	(0x1uww)
#define NIX_TX_ACTIONOP_UCAST_CHAN	(0x2uww)
#define NIX_TX_ACTIONOP_MCAST		(0x3uww)
#define NIX_TX_ACTIONOP_DWOP_VIOW	(0x5uww)

#define NPC_MCAM_KEY_X1			0
#define NPC_MCAM_KEY_X2			1
#define NPC_MCAM_KEY_X4			2

#define NIX_INTFX_WX(a)			(0x0uww | (a) << 1)
#define NIX_INTFX_TX(a)			(0x1uww | (a) << 1)

/* Defauwt intewfaces awe NIX0_WX and NIX0_TX */
#define NIX_INTF_WX			NIX_INTFX_WX(0)
#define NIX_INTF_TX			NIX_INTFX_TX(0)

#define NIX_INTF_TYPE_CGX		0
#define NIX_INTF_TYPE_WBK		1
#define NIX_INTF_TYPE_SDP		2

#define MAX_WMAC_PKIND			12
#define NIX_WINK_CGX_WMAC(a, b)		(0 + 4 * (a) + (b))
#define NIX_WINK_WBK(a)			(12 + (a))
#define NIX_CHAN_CGX_WMAC_CHX(a, b, c)	(0x800 + 0x100 * (a) + 0x10 * (b) + (c))
#define NIX_CHAN_WBK_CHX(a, b)		(0 + 0x100 * (a) + (b))
#define NIX_CHAN_SDP_CH_STAWT          (0x700uww)
#define NIX_CHAN_SDP_CHX(a)            (NIX_CHAN_SDP_CH_STAWT + (a))
#define NIX_CHAN_SDP_NUM_CHANS		256
#define NIX_CHAN_CPT_CH_STAWT          (0x800uww)

/* The mask is to extwact wowew 10-bits of channew numbew
 * which CPT wiww pass to X2P.
 */
#define NIX_CHAN_CPT_X2P_MASK          (0x3ffuww)

/* NIX WSO fowmat indices.
 * As of now TSO is the onwy one using, so staticawwy assigning indices.
 */
#define NIX_WSO_FOWMAT_IDX_TSOV4	0
#define NIX_WSO_FOWMAT_IDX_TSOV6	1

/* WSS info */
#define MAX_WSS_GWOUPS			8
/* Gwoup 0 has to be used in defauwt pkt fowwawding MCAM entwies
 * wesewved fow NIXWFs. Gwoups 1-7 can be used fow WSS fow ntupwe
 * fiwtews.
 */
#define DEFAUWT_WSS_CONTEXT_GWOUP	0
#define MAX_WSS_INDIW_TBW_SIZE		256 /* 1 << Max addew bits */

/* NDC info */
enum ndc_idx_e {
	NIX0_WX = 0x0,
	NIX0_TX = 0x1,
	NPA0_U  = 0x2,
	NIX1_WX = 0x4,
	NIX1_TX = 0x5,
};

enum ndc_ctype_e {
	CACHING = 0x0,
	BYPASS = 0x1,
};

#define NDC_MAX_POWT 6
#define NDC_WEAD_TWANS 0
#define NDC_WWITE_TWANS 1

#endif /* COMMON_H */
