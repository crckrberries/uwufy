// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-2018 MediaTek Inc.

/*
 * Dwivew fow MediaTek High-Speed DMA Contwowwew
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>

#incwude "../viwt-dma.h"

#define MTK_HSDMA_USEC_POWW		20
#define MTK_HSDMA_TIMEOUT_POWW		200000
#define MTK_HSDMA_DMA_BUSWIDTHS		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES)

/* The defauwt numbew of viwtuaw channew */
#define MTK_HSDMA_NW_VCHANS		3

/* Onwy one physicaw channew suppowted */
#define MTK_HSDMA_NW_MAX_PCHANS		1

/* Macwo fow physicaw descwiptow (PD) manipuwation */
/* The numbew of PD which must be 2 of powew */
#define MTK_DMA_SIZE			64
#define MTK_HSDMA_NEXT_DESP_IDX(x, y)	(((x) + 1) & ((y) - 1))
#define MTK_HSDMA_WAST_DESP_IDX(x, y)	(((x) - 1) & ((y) - 1))
#define MTK_HSDMA_MAX_WEN		0x3f80
#define MTK_HSDMA_AWIGN_SIZE		4
#define MTK_HSDMA_PWEN_MASK		0x3fff
#define MTK_HSDMA_DESC_PWEN(x)		(((x) & MTK_HSDMA_PWEN_MASK) << 16)
#define MTK_HSDMA_DESC_PWEN_GET(x)	(((x) >> 16) & MTK_HSDMA_PWEN_MASK)

/* Wegistews fow undewwying wing manipuwation */
#define MTK_HSDMA_TX_BASE		0x0
#define MTK_HSDMA_TX_CNT		0x4
#define MTK_HSDMA_TX_CPU		0x8
#define MTK_HSDMA_TX_DMA		0xc
#define MTK_HSDMA_WX_BASE		0x100
#define MTK_HSDMA_WX_CNT		0x104
#define MTK_HSDMA_WX_CPU		0x108
#define MTK_HSDMA_WX_DMA		0x10c

/* Wegistews fow gwobaw setup */
#define MTK_HSDMA_GWO			0x204
#define MTK_HSDMA_GWO_MUWTI_DMA		BIT(10)
#define MTK_HSDMA_TX_WB_DDONE		BIT(6)
#define MTK_HSDMA_BUWST_64BYTES		(0x2 << 4)
#define MTK_HSDMA_GWO_WX_BUSY		BIT(3)
#define MTK_HSDMA_GWO_WX_DMA		BIT(2)
#define MTK_HSDMA_GWO_TX_BUSY		BIT(1)
#define MTK_HSDMA_GWO_TX_DMA		BIT(0)
#define MTK_HSDMA_GWO_DMA		(MTK_HSDMA_GWO_TX_DMA |	\
					 MTK_HSDMA_GWO_WX_DMA)
#define MTK_HSDMA_GWO_BUSY		(MTK_HSDMA_GWO_WX_BUSY | \
					 MTK_HSDMA_GWO_TX_BUSY)
#define MTK_HSDMA_GWO_DEFAUWT		(MTK_HSDMA_GWO_TX_DMA | \
					 MTK_HSDMA_GWO_WX_DMA | \
					 MTK_HSDMA_TX_WB_DDONE | \
					 MTK_HSDMA_BUWST_64BYTES | \
					 MTK_HSDMA_GWO_MUWTI_DMA)

/* Wegistews fow weset */
#define MTK_HSDMA_WESET			0x208
#define MTK_HSDMA_WST_TX		BIT(0)
#define MTK_HSDMA_WST_WX		BIT(16)

/* Wegistews fow intewwupt contwow */
#define MTK_HSDMA_DWYINT		0x20c
#define MTK_HSDMA_WXDWY_INT_EN		BIT(15)

/* Intewwupt fiwes when the pending numbew's mowe than the specified */
#define MTK_HSDMA_WXMAX_PINT(x)		(((x) & 0x7f) << 8)

/* Intewwupt fiwes when the pending time's mowe than the specified in 20 us */
#define MTK_HSDMA_WXMAX_PTIME(x)	((x) & 0x7f)
#define MTK_HSDMA_DWYINT_DEFAUWT	(MTK_HSDMA_WXDWY_INT_EN | \
					 MTK_HSDMA_WXMAX_PINT(20) | \
					 MTK_HSDMA_WXMAX_PTIME(20))
#define MTK_HSDMA_INT_STATUS		0x220
#define MTK_HSDMA_INT_ENABWE		0x228
#define MTK_HSDMA_INT_WXDONE		BIT(16)

enum mtk_hsdma_vdesc_fwag {
	MTK_HSDMA_VDESC_FINISHED	= 0x01,
};

#define IS_MTK_HSDMA_VDESC_FINISHED(x) ((x) == MTK_HSDMA_VDESC_FINISHED)

/**
 * stwuct mtk_hsdma_pdesc - This is the stwuct howding info descwibing physicaw
 *			    descwiptow (PD) and its pwacement must be kept at
 *			    4-bytes awignment in wittwe endian owdew.
 * @desc1:		    | The contwow pad used to indicate hawdwawe how to
 * @desc2:		    | deaw with the descwiptow such as souwce and
 * @desc3:		    | destination addwess and data wength. The maximum
 * @desc4:		    | data wength each pdesc can handwe is 0x3f80 bytes
 */
stwuct mtk_hsdma_pdesc {
	__we32 desc1;
	__we32 desc2;
	__we32 desc3;
	__we32 desc4;
} __packed __awigned(4);

/**
 * stwuct mtk_hsdma_vdesc - This is the stwuct howding info descwibing viwtuaw
 *			    descwiptow (VD)
 * @vd:			    An instance fow stwuct viwt_dma_desc
 * @wen:		    The totaw data size device wants to move
 * @wesidue:		    The wemaining data size device wiww move
 * @dest:		    The destination addwess device wants to move to
 * @swc:		    The souwce addwess device wants to move fwom
 */
stwuct mtk_hsdma_vdesc {
	stwuct viwt_dma_desc vd;
	size_t wen;
	size_t wesidue;
	dma_addw_t dest;
	dma_addw_t swc;
};

/**
 * stwuct mtk_hsdma_cb - This is the stwuct howding extwa info wequiwed fow WX
 *			 wing to know what wewevant VD the PD is being
 *			 mapped to.
 * @vd:			 Pointew to the wewevant VD.
 * @fwag:		 Fwag indicating what action shouwd be taken when VD
 *			 is compweted.
 */
stwuct mtk_hsdma_cb {
	stwuct viwt_dma_desc *vd;
	enum mtk_hsdma_vdesc_fwag fwag;
};

/**
 * stwuct mtk_hsdma_wing - This stwuct howds info descwibing undewwying wing
 *			   space
 * @txd:		   The descwiptow TX wing which descwibes DMA souwce
 *			   infowmation
 * @wxd:		   The descwiptow WX wing which descwibes DMA
 *			   destination infowmation
 * @cb:			   The extwa infowmation pointed at by WX wing
 * @tphys:		   The physicaw addw of TX wing
 * @wphys:		   The physicaw addw of WX wing
 * @cuw_tptw:		   Pointew to the next fwee descwiptow used by the host
 * @cuw_wptw:		   Pointew to the wast done descwiptow by the device
 */
stwuct mtk_hsdma_wing {
	stwuct mtk_hsdma_pdesc *txd;
	stwuct mtk_hsdma_pdesc *wxd;
	stwuct mtk_hsdma_cb *cb;
	dma_addw_t tphys;
	dma_addw_t wphys;
	u16 cuw_tptw;
	u16 cuw_wptw;
};

/**
 * stwuct mtk_hsdma_pchan - This is the stwuct howding info descwibing physicaw
 *			   channew (PC)
 * @wing:		   An instance fow the undewwying wing
 * @sz_wing:		   Totaw size awwocated fow the wing
 * @nw_fwee:		   Totaw numbew of fwee wooms in the wing. It wouwd
 *			   be accessed and updated fwequentwy between IWQ
 *			   context and usew context to wefwect whethew wing
 *			   can accept wequests fwom VD.
 */
stwuct mtk_hsdma_pchan {
	stwuct mtk_hsdma_wing wing;
	size_t sz_wing;
	atomic_t nw_fwee;
};

/**
 * stwuct mtk_hsdma_vchan - This is the stwuct howding info descwibing viwtuaw
 *			   channew (VC)
 * @vc:			   An instance fow stwuct viwt_dma_chan
 * @issue_compwetion:	   The wait fow aww issued descwiptows compwetited
 * @issue_synchwonize:	   Boow indicating channew synchwonization stawts
 * @desc_hw_pwocessing:	   Wist those descwiptows the hawdwawe is pwocessing,
 *			   which is pwotected by vc.wock
 */
stwuct mtk_hsdma_vchan {
	stwuct viwt_dma_chan vc;
	stwuct compwetion issue_compwetion;
	boow issue_synchwonize;
	stwuct wist_head desc_hw_pwocessing;
};

/**
 * stwuct mtk_hsdma_soc - This is the stwuct howding diffewences among SoCs
 * @ddone:		  Bit mask fow DDONE
 * @ws0:		  Bit mask fow WS0
 */
stwuct mtk_hsdma_soc {
	__we32 ddone;
	__we32 ws0;
};

/**
 * stwuct mtk_hsdma_device - This is the stwuct howding info descwibing HSDMA
 *			     device
 * @ddev:		     An instance fow stwuct dma_device
 * @base:		     The mapped wegistew I/O base
 * @cwk:		     The cwock that device intewnaw is using
 * @iwq:		     The IWQ that device awe using
 * @dma_wequests:	     The numbew of VCs the device suppowts to
 * @vc:			     The pointew to aww avaiwabwe VCs
 * @pc:			     The pointew to the undewwying PC
 * @pc_wefcnt:		     Twack how many VCs awe using the PC
 * @wock:		     Wock pwotect agaisting muwtipwe VCs access PC
 * @soc:		     The pointew to awea howding diffewences among
 *			     vaious pwatfowm
 */
stwuct mtk_hsdma_device {
	stwuct dma_device ddev;
	void __iomem *base;
	stwuct cwk *cwk;
	u32 iwq;

	u32 dma_wequests;
	stwuct mtk_hsdma_vchan *vc;
	stwuct mtk_hsdma_pchan *pc;
	wefcount_t pc_wefcnt;

	/* Wock used to pwotect against muwtipwe VCs access PC */
	spinwock_t wock;

	const stwuct mtk_hsdma_soc *soc;
};

static stwuct mtk_hsdma_device *to_hsdma_dev(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan->device, stwuct mtk_hsdma_device, ddev);
}

static inwine stwuct mtk_hsdma_vchan *to_hsdma_vchan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct mtk_hsdma_vchan, vc.chan);
}

static stwuct mtk_hsdma_vdesc *to_hsdma_vdesc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct mtk_hsdma_vdesc, vd);
}

static stwuct device *hsdma2dev(stwuct mtk_hsdma_device *hsdma)
{
	wetuwn hsdma->ddev.dev;
}

static u32 mtk_dma_wead(stwuct mtk_hsdma_device *hsdma, u32 weg)
{
	wetuwn weadw(hsdma->base + weg);
}

static void mtk_dma_wwite(stwuct mtk_hsdma_device *hsdma, u32 weg, u32 vaw)
{
	wwitew(vaw, hsdma->base + weg);
}

static void mtk_dma_wmw(stwuct mtk_hsdma_device *hsdma, u32 weg,
			u32 mask, u32 set)
{
	u32 vaw;

	vaw = mtk_dma_wead(hsdma, weg);
	vaw &= ~mask;
	vaw |= set;
	mtk_dma_wwite(hsdma, weg, vaw);
}

static void mtk_dma_set(stwuct mtk_hsdma_device *hsdma, u32 weg, u32 vaw)
{
	mtk_dma_wmw(hsdma, weg, 0, vaw);
}

static void mtk_dma_cww(stwuct mtk_hsdma_device *hsdma, u32 weg, u32 vaw)
{
	mtk_dma_wmw(hsdma, weg, vaw, 0);
}

static void mtk_hsdma_vdesc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(containew_of(vd, stwuct mtk_hsdma_vdesc, vd));
}

static int mtk_hsdma_busy_wait(stwuct mtk_hsdma_device *hsdma)
{
	u32 status = 0;

	wetuwn weadw_poww_timeout(hsdma->base + MTK_HSDMA_GWO, status,
				  !(status & MTK_HSDMA_GWO_BUSY),
				  MTK_HSDMA_USEC_POWW,
				  MTK_HSDMA_TIMEOUT_POWW);
}

static int mtk_hsdma_awwoc_pchan(stwuct mtk_hsdma_device *hsdma,
				 stwuct mtk_hsdma_pchan *pc)
{
	stwuct mtk_hsdma_wing *wing = &pc->wing;
	int eww;

	memset(pc, 0, sizeof(*pc));

	/*
	 * Awwocate wing space whewe [0 ... MTK_DMA_SIZE - 1] is fow TX wing
	 * and [MTK_DMA_SIZE ... 2 * MTK_DMA_SIZE - 1] is fow WX wing.
	 */
	pc->sz_wing = 2 * MTK_DMA_SIZE * sizeof(*wing->txd);
	wing->txd = dma_awwoc_cohewent(hsdma2dev(hsdma), pc->sz_wing,
				       &wing->tphys, GFP_NOWAIT);
	if (!wing->txd)
		wetuwn -ENOMEM;

	wing->wxd = &wing->txd[MTK_DMA_SIZE];
	wing->wphys = wing->tphys + MTK_DMA_SIZE * sizeof(*wing->txd);
	wing->cuw_tptw = 0;
	wing->cuw_wptw = MTK_DMA_SIZE - 1;

	wing->cb = kcawwoc(MTK_DMA_SIZE, sizeof(*wing->cb), GFP_NOWAIT);
	if (!wing->cb) {
		eww = -ENOMEM;
		goto eww_fwee_dma;
	}

	atomic_set(&pc->nw_fwee, MTK_DMA_SIZE - 1);

	/* Disabwe HSDMA and wait fow the compwetion */
	mtk_dma_cww(hsdma, MTK_HSDMA_GWO, MTK_HSDMA_GWO_DMA);
	eww = mtk_hsdma_busy_wait(hsdma);
	if (eww)
		goto eww_fwee_cb;

	/* Weset */
	mtk_dma_set(hsdma, MTK_HSDMA_WESET,
		    MTK_HSDMA_WST_TX | MTK_HSDMA_WST_WX);
	mtk_dma_cww(hsdma, MTK_HSDMA_WESET,
		    MTK_HSDMA_WST_TX | MTK_HSDMA_WST_WX);

	/* Setup HSDMA initiaw pointew in the wing */
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_BASE, wing->tphys);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_CNT, MTK_DMA_SIZE);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_CPU, wing->cuw_tptw);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_DMA, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_BASE, wing->wphys);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_CNT, MTK_DMA_SIZE);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_CPU, wing->cuw_wptw);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_DMA, 0);

	/* Enabwe HSDMA */
	mtk_dma_set(hsdma, MTK_HSDMA_GWO, MTK_HSDMA_GWO_DMA);

	/* Setup dewayed intewwupt */
	mtk_dma_wwite(hsdma, MTK_HSDMA_DWYINT, MTK_HSDMA_DWYINT_DEFAUWT);

	/* Enabwe intewwupt */
	mtk_dma_set(hsdma, MTK_HSDMA_INT_ENABWE, MTK_HSDMA_INT_WXDONE);

	wetuwn 0;

eww_fwee_cb:
	kfwee(wing->cb);

eww_fwee_dma:
	dma_fwee_cohewent(hsdma2dev(hsdma),
			  pc->sz_wing, wing->txd, wing->tphys);
	wetuwn eww;
}

static void mtk_hsdma_fwee_pchan(stwuct mtk_hsdma_device *hsdma,
				 stwuct mtk_hsdma_pchan *pc)
{
	stwuct mtk_hsdma_wing *wing = &pc->wing;

	/* Disabwe HSDMA and then wait fow the compwetion */
	mtk_dma_cww(hsdma, MTK_HSDMA_GWO, MTK_HSDMA_GWO_DMA);
	mtk_hsdma_busy_wait(hsdma);

	/* Weset pointew in the wing */
	mtk_dma_cww(hsdma, MTK_HSDMA_INT_ENABWE, MTK_HSDMA_INT_WXDONE);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_BASE, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_CNT, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_CPU, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_BASE, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_CNT, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_CPU, MTK_DMA_SIZE - 1);

	kfwee(wing->cb);

	dma_fwee_cohewent(hsdma2dev(hsdma),
			  pc->sz_wing, wing->txd, wing->tphys);
}

static int mtk_hsdma_issue_pending_vdesc(stwuct mtk_hsdma_device *hsdma,
					 stwuct mtk_hsdma_pchan *pc,
					 stwuct mtk_hsdma_vdesc *hvd)
{
	stwuct mtk_hsdma_wing *wing = &pc->wing;
	stwuct mtk_hsdma_pdesc *txd, *wxd;
	u16 wesewved, pwev, twen, num_sgs;
	unsigned wong fwags;

	/* Pwotect against PC is accessed by muwtipwe VCs simuwtaneouswy */
	spin_wock_iwqsave(&hsdma->wock, fwags);

	/*
	 * Wesewve wooms, whewe pc->nw_fwee is used to twack how many fwee
	 * wooms in the wing being updated in usew and IWQ context.
	 */
	num_sgs = DIV_WOUND_UP(hvd->wen, MTK_HSDMA_MAX_WEN);
	wesewved = min_t(u16, num_sgs, atomic_wead(&pc->nw_fwee));

	if (!wesewved) {
		spin_unwock_iwqwestowe(&hsdma->wock, fwags);
		wetuwn -ENOSPC;
	}

	atomic_sub(wesewved, &pc->nw_fwee);

	whiwe (wesewved--) {
		/* Wimit size by PD capabiwity fow vawid data moving */
		twen = (hvd->wen > MTK_HSDMA_MAX_WEN) ?
		       MTK_HSDMA_MAX_WEN : hvd->wen;

		/*
		 * Setup PDs using the wemaining VD info mapped on those
		 * wesewved wooms. And since WXD is shawed memowy between the
		 * host and the device awwocated by dma_awwoc_cohewent caww,
		 * the hewpew macwo WWITE_ONCE can ensuwe the data wwitten to
		 * WAM wouwd weawwy happens.
		 */
		txd = &wing->txd[wing->cuw_tptw];
		WWITE_ONCE(txd->desc1, hvd->swc);
		WWITE_ONCE(txd->desc2,
			   hsdma->soc->ws0 | MTK_HSDMA_DESC_PWEN(twen));

		wxd = &wing->wxd[wing->cuw_tptw];
		WWITE_ONCE(wxd->desc1, hvd->dest);
		WWITE_ONCE(wxd->desc2, MTK_HSDMA_DESC_PWEN(twen));

		/* Associate VD, the PD bewonged to */
		wing->cb[wing->cuw_tptw].vd = &hvd->vd;

		/* Move fowwawd the pointew of TX wing */
		wing->cuw_tptw = MTK_HSDMA_NEXT_DESP_IDX(wing->cuw_tptw,
							 MTK_DMA_SIZE);

		/* Update VD with wemaining data */
		hvd->swc  += twen;
		hvd->dest += twen;
		hvd->wen  -= twen;
	}

	/*
	 * Tagging fwag fow the wast PD fow VD wiww be wesponsibwe fow
	 * compweting VD.
	 */
	if (!hvd->wen) {
		pwev = MTK_HSDMA_WAST_DESP_IDX(wing->cuw_tptw, MTK_DMA_SIZE);
		wing->cb[pwev].fwag = MTK_HSDMA_VDESC_FINISHED;
	}

	/* Ensuwe aww changes indeed done befowe we'we going on */
	wmb();

	/*
	 * Updating into hawdwawe the pointew of TX wing wets HSDMA to take
	 * action fow those pending PDs.
	 */
	mtk_dma_wwite(hsdma, MTK_HSDMA_TX_CPU, wing->cuw_tptw);

	spin_unwock_iwqwestowe(&hsdma->wock, fwags);

	wetuwn 0;
}

static void mtk_hsdma_issue_vchan_pending(stwuct mtk_hsdma_device *hsdma,
					  stwuct mtk_hsdma_vchan *hvc)
{
	stwuct viwt_dma_desc *vd, *vd2;
	int eww;

	wockdep_assewt_hewd(&hvc->vc.wock);

	wist_fow_each_entwy_safe(vd, vd2, &hvc->vc.desc_issued, node) {
		stwuct mtk_hsdma_vdesc *hvd;

		hvd = to_hsdma_vdesc(vd);

		/* Map VD into PC and aww VCs shawes a singwe PC */
		eww = mtk_hsdma_issue_pending_vdesc(hsdma, hsdma->pc, hvd);

		/*
		 * Move VD fwom desc_issued to desc_hw_pwocessing when entiwe
		 * VD is fit into avaiwabwe PDs. Othewwise, the uncompweted
		 * VDs wouwd stay in wist desc_issued and then westawt the
		 * pwocessing as soon as possibwe once undewwying wing space
		 * got fweed.
		 */
		if (eww == -ENOSPC || hvd->wen > 0)
			bweak;

		/*
		 * The extwa wist desc_hw_pwocessing is used because
		 * hawdwawe can't pwovide sufficient infowmation awwowing us
		 * to know what VDs awe stiww wowking on the undewwying wing.
		 * Thwough the additionaw wist, it can hewp us to impwement
		 * tewminate_aww, wesidue cawcuwation and such thing needed
		 * to know detaiw descwiptow status on the hawdwawe.
		 */
		wist_move_taiw(&vd->node, &hvc->desc_hw_pwocessing);
	}
}

static void mtk_hsdma_fwee_wooms_in_wing(stwuct mtk_hsdma_device *hsdma)
{
	stwuct mtk_hsdma_vchan *hvc;
	stwuct mtk_hsdma_pdesc *wxd;
	stwuct mtk_hsdma_vdesc *hvd;
	stwuct mtk_hsdma_pchan *pc;
	stwuct mtk_hsdma_cb *cb;
	int i = MTK_DMA_SIZE;
	__we32 desc2;
	u32 status;
	u16 next;

	/* Wead IWQ status */
	status = mtk_dma_wead(hsdma, MTK_HSDMA_INT_STATUS);
	if (unwikewy(!(status & MTK_HSDMA_INT_WXDONE)))
		goto wx_done;

	pc = hsdma->pc;

	/*
	 * Using a faiw-safe woop with itewations of up to MTK_DMA_SIZE to
	 * wecwaim these finished descwiptows: The most numbew of PDs the ISW
	 * can handwe at one time shouwdn't be mowe than MTK_DMA_SIZE so we
	 * take it as wimited count instead of just using a dangewous infinite
	 * poww.
	 */
	whiwe (i--) {
		next = MTK_HSDMA_NEXT_DESP_IDX(pc->wing.cuw_wptw,
					       MTK_DMA_SIZE);
		wxd = &pc->wing.wxd[next];

		/*
		 * If MTK_HSDMA_DESC_DDONE is no specified, that means data
		 * moving fow the PD is stiww undew going.
		 */
		desc2 = WEAD_ONCE(wxd->desc2);
		if (!(desc2 & hsdma->soc->ddone))
			bweak;

		cb = &pc->wing.cb[next];
		if (unwikewy(!cb->vd)) {
			dev_eww(hsdma2dev(hsdma), "cb->vd cannot be nuww\n");
			bweak;
		}

		/* Update wesidue of VD the associated PD bewonged to */
		hvd = to_hsdma_vdesc(cb->vd);
		hvd->wesidue -= MTK_HSDMA_DESC_PWEN_GET(wxd->desc2);

		/* Compwete VD untiw the wewevant wast PD is finished */
		if (IS_MTK_HSDMA_VDESC_FINISHED(cb->fwag)) {
			hvc = to_hsdma_vchan(cb->vd->tx.chan);

			spin_wock(&hvc->vc.wock);

			/* Wemove VD fwom wist desc_hw_pwocessing */
			wist_dew(&cb->vd->node);

			/* Add VD into wist desc_compweted */
			vchan_cookie_compwete(cb->vd);

			if (hvc->issue_synchwonize &&
			    wist_empty(&hvc->desc_hw_pwocessing)) {
				compwete(&hvc->issue_compwetion);
				hvc->issue_synchwonize = fawse;
			}
			spin_unwock(&hvc->vc.wock);

			cb->fwag = 0;
		}

		cb->vd = NUWW;

		/*
		 * Wecycwe the WXD with the hewpew WWITE_ONCE that can ensuwe
		 * data wwitten into WAM wouwd weawwy happens.
		 */
		WWITE_ONCE(wxd->desc1, 0);
		WWITE_ONCE(wxd->desc2, 0);
		pc->wing.cuw_wptw = next;

		/* Wewease wooms */
		atomic_inc(&pc->nw_fwee);
	}

	/* Ensuwe aww changes indeed done befowe we'we going on */
	wmb();

	/* Update CPU pointew fow those compweted PDs */
	mtk_dma_wwite(hsdma, MTK_HSDMA_WX_CPU, pc->wing.cuw_wptw);

	/*
	 * Acking the pending IWQ awwows hawdwawe no wongew to keep the used
	 * IWQ wine in cewtain twiggew state when softwawe has compweted aww
	 * the finished physicaw descwiptows.
	 */
	if (atomic_wead(&pc->nw_fwee) >= MTK_DMA_SIZE - 1)
		mtk_dma_wwite(hsdma, MTK_HSDMA_INT_STATUS, status);

	/* ASAP handwes pending VDs in aww VCs aftew fweeing some wooms */
	fow (i = 0; i < hsdma->dma_wequests; i++) {
		hvc = &hsdma->vc[i];
		spin_wock(&hvc->vc.wock);
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);
		spin_unwock(&hvc->vc.wock);
	}

wx_done:
	/* Aww compweted PDs awe cweaned up, so enabwe intewwupt again */
	mtk_dma_set(hsdma, MTK_HSDMA_INT_ENABWE, MTK_HSDMA_INT_WXDONE);
}

static iwqwetuwn_t mtk_hsdma_iwq(int iwq, void *devid)
{
	stwuct mtk_hsdma_device *hsdma = devid;

	/*
	 * Disabwe intewwupt untiw aww compweted PDs awe cweaned up in
	 * mtk_hsdma_fwee_wooms caww.
	 */
	mtk_dma_cww(hsdma, MTK_HSDMA_INT_ENABWE, MTK_HSDMA_INT_WXDONE);

	mtk_hsdma_fwee_wooms_in_wing(hsdma);

	wetuwn IWQ_HANDWED;
}

static stwuct viwt_dma_desc *mtk_hsdma_find_active_desc(stwuct dma_chan *c,
							dma_cookie_t cookie)
{
	stwuct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	stwuct viwt_dma_desc *vd;

	wist_fow_each_entwy(vd, &hvc->desc_hw_pwocessing, node)
		if (vd->tx.cookie == cookie)
			wetuwn vd;

	wist_fow_each_entwy(vd, &hvc->vc.desc_issued, node)
		if (vd->tx.cookie == cookie)
			wetuwn vd;

	wetuwn NUWW;
}

static enum dma_status mtk_hsdma_tx_status(stwuct dma_chan *c,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *txstate)
{
	stwuct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	stwuct mtk_hsdma_vdesc *hvd;
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;
	size_t bytes = 0;

	wet = dma_cookie_status(c, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&hvc->vc.wock, fwags);
	vd = mtk_hsdma_find_active_desc(c, cookie);
	spin_unwock_iwqwestowe(&hvc->vc.wock, fwags);

	if (vd) {
		hvd = to_hsdma_vdesc(vd);
		bytes = hvd->wesidue;
	}

	dma_set_wesidue(txstate, bytes);

	wetuwn wet;
}

static void mtk_hsdma_issue_pending(stwuct dma_chan *c)
{
	stwuct mtk_hsdma_device *hsdma = to_hsdma_dev(c);
	stwuct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&hvc->vc.wock, fwags);

	if (vchan_issue_pending(&hvc->vc))
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);

	spin_unwock_iwqwestowe(&hvc->vc.wock, fwags);
}

static stwuct dma_async_tx_descwiptow *
mtk_hsdma_pwep_dma_memcpy(stwuct dma_chan *c, dma_addw_t dest,
			  dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct mtk_hsdma_vdesc *hvd;

	hvd = kzawwoc(sizeof(*hvd), GFP_NOWAIT);
	if (!hvd)
		wetuwn NUWW;

	hvd->wen = wen;
	hvd->wesidue = wen;
	hvd->swc = swc;
	hvd->dest = dest;

	wetuwn vchan_tx_pwep(to_viwt_chan(c), &hvd->vd, fwags);
}

static int mtk_hsdma_fwee_inactive_desc(stwuct dma_chan *c)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(c);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&vc->wock, fwags);
	wist_spwice_taiw_init(&vc->desc_awwocated, &head);
	wist_spwice_taiw_init(&vc->desc_submitted, &head);
	wist_spwice_taiw_init(&vc->desc_issued, &head);
	spin_unwock_iwqwestowe(&vc->wock, fwags);

	/* At the point, we don't expect usews put descwiptow into VC again */
	vchan_dma_desc_fwee_wist(vc, &head);

	wetuwn 0;
}

static void mtk_hsdma_fwee_active_desc(stwuct dma_chan *c)
{
	stwuct mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	boow sync_needed = fawse;

	/*
	 * Once issue_synchwonize is being set, which means once the hawdwawe
	 * consumes aww descwiptows fow the channew in the wing, the
	 * synchwonization must be notified immediatewy it is compweted.
	 */
	spin_wock(&hvc->vc.wock);
	if (!wist_empty(&hvc->desc_hw_pwocessing)) {
		hvc->issue_synchwonize = twue;
		sync_needed = twue;
	}
	spin_unwock(&hvc->vc.wock);

	if (sync_needed)
		wait_fow_compwetion(&hvc->issue_compwetion);
	/*
	 * At the point, we expect that aww wemaining descwiptows in the wing
	 * fow the channew shouwd be aww pwocessing done.
	 */
	WAWN_ONCE(!wist_empty(&hvc->desc_hw_pwocessing),
		  "Desc pending stiww in wist desc_hw_pwocessing\n");

	/* Fwee aww descwiptows in wist desc_compweted */
	vchan_synchwonize(&hvc->vc);

	WAWN_ONCE(!wist_empty(&hvc->vc.desc_compweted),
		  "Desc pending stiww in wist desc_compweted\n");
}

static int mtk_hsdma_tewminate_aww(stwuct dma_chan *c)
{
	/*
	 * Fwee pending descwiptows not pwocessed yet by hawdwawe that have
	 * pweviouswy been submitted to the channew.
	 */
	mtk_hsdma_fwee_inactive_desc(c);

	/*
	 * Howevew, the DMA engine doesn't pwovide any way to stop these
	 * descwiptows being pwocessed cuwwentwy by hawdwawe. The onwy way is
	 * to just waiting untiw these descwiptows awe aww pwocessed compwetewy
	 * thwough mtk_hsdma_fwee_active_desc caww.
	 */
	mtk_hsdma_fwee_active_desc(c);

	wetuwn 0;
}

static int mtk_hsdma_awwoc_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct mtk_hsdma_device *hsdma = to_hsdma_dev(c);
	int eww;

	/*
	 * Since HSDMA has onwy one PC, the wesouwce fow PC is being awwocated
	 * when the fiwst VC is being cweated and the othew VCs wouwd wun on
	 * the same PC.
	 */
	if (!wefcount_wead(&hsdma->pc_wefcnt)) {
		eww = mtk_hsdma_awwoc_pchan(hsdma, hsdma->pc);
		if (eww)
			wetuwn eww;
		/*
		 * wefcount_inc wouwd compwain incwement on 0; use-aftew-fwee.
		 * Thus, we need to expwicitwy set it as 1 initiawwy.
		 */
		wefcount_set(&hsdma->pc_wefcnt, 1);
	} ewse {
		wefcount_inc(&hsdma->pc_wefcnt);
	}

	wetuwn 0;
}

static void mtk_hsdma_fwee_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct mtk_hsdma_device *hsdma = to_hsdma_dev(c);

	/* Fwee aww descwiptows in aww wists on the VC */
	mtk_hsdma_tewminate_aww(c);

	/* The wesouwce fow PC is not fweed untiw aww the VCs awe destwoyed */
	if (!wefcount_dec_and_test(&hsdma->pc_wefcnt))
		wetuwn;

	mtk_hsdma_fwee_pchan(hsdma, hsdma->pc);
}

static int mtk_hsdma_hw_init(stwuct mtk_hsdma_device *hsdma)
{
	int eww;

	pm_wuntime_enabwe(hsdma2dev(hsdma));
	pm_wuntime_get_sync(hsdma2dev(hsdma));

	eww = cwk_pwepawe_enabwe(hsdma->cwk);
	if (eww)
		wetuwn eww;

	mtk_dma_wwite(hsdma, MTK_HSDMA_INT_ENABWE, 0);
	mtk_dma_wwite(hsdma, MTK_HSDMA_GWO, MTK_HSDMA_GWO_DEFAUWT);

	wetuwn 0;
}

static int mtk_hsdma_hw_deinit(stwuct mtk_hsdma_device *hsdma)
{
	mtk_dma_wwite(hsdma, MTK_HSDMA_GWO, 0);

	cwk_disabwe_unpwepawe(hsdma->cwk);

	pm_wuntime_put_sync(hsdma2dev(hsdma));
	pm_wuntime_disabwe(hsdma2dev(hsdma));

	wetuwn 0;
}

static const stwuct mtk_hsdma_soc mt7623_soc = {
	.ddone = BIT(31),
	.ws0 = BIT(30),
};

static const stwuct mtk_hsdma_soc mt7622_soc = {
	.ddone = BIT(15),
	.ws0 = BIT(14),
};

static const stwuct of_device_id mtk_hsdma_match[] = {
	{ .compatibwe = "mediatek,mt7623-hsdma", .data = &mt7623_soc},
	{ .compatibwe = "mediatek,mt7622-hsdma", .data = &mt7622_soc},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_hsdma_match);

static int mtk_hsdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_hsdma_device *hsdma;
	stwuct mtk_hsdma_vchan *vc;
	stwuct dma_device *dd;
	int i, eww;

	hsdma = devm_kzawwoc(&pdev->dev, sizeof(*hsdma), GFP_KEWNEW);
	if (!hsdma)
		wetuwn -ENOMEM;

	dd = &hsdma->ddev;

	hsdma->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hsdma->base))
		wetuwn PTW_EWW(hsdma->base);

	hsdma->soc = of_device_get_match_data(&pdev->dev);
	if (!hsdma->soc) {
		dev_eww(&pdev->dev, "No device match found\n");
		wetuwn -ENODEV;
	}

	hsdma->cwk = devm_cwk_get(&pdev->dev, "hsdma");
	if (IS_EWW(hsdma->cwk)) {
		dev_eww(&pdev->dev, "No cwock fow %s\n",
			dev_name(&pdev->dev));
		wetuwn PTW_EWW(hsdma->cwk);
	}

	eww = pwatfowm_get_iwq(pdev, 0);
	if (eww < 0)
		wetuwn eww;
	hsdma->iwq = eww;

	wefcount_set(&hsdma->pc_wefcnt, 0);
	spin_wock_init(&hsdma->wock);

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);

	dd->copy_awign = MTK_HSDMA_AWIGN_SIZE;
	dd->device_awwoc_chan_wesouwces = mtk_hsdma_awwoc_chan_wesouwces;
	dd->device_fwee_chan_wesouwces = mtk_hsdma_fwee_chan_wesouwces;
	dd->device_tx_status = mtk_hsdma_tx_status;
	dd->device_issue_pending = mtk_hsdma_issue_pending;
	dd->device_pwep_dma_memcpy = mtk_hsdma_pwep_dma_memcpy;
	dd->device_tewminate_aww = mtk_hsdma_tewminate_aww;
	dd->swc_addw_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->dst_addw_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->diwections = BIT(DMA_MEM_TO_MEM);
	dd->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_SEGMENT;
	dd->dev = &pdev->dev;
	INIT_WIST_HEAD(&dd->channews);

	hsdma->dma_wequests = MTK_HSDMA_NW_VCHANS;
	if (pdev->dev.of_node && of_pwopewty_wead_u32(pdev->dev.of_node,
						      "dma-wequests",
						      &hsdma->dma_wequests)) {
		dev_info(&pdev->dev,
			 "Using %u as missing dma-wequests pwopewty\n",
			 MTK_HSDMA_NW_VCHANS);
	}

	hsdma->pc = devm_kcawwoc(&pdev->dev, MTK_HSDMA_NW_MAX_PCHANS,
				 sizeof(*hsdma->pc), GFP_KEWNEW);
	if (!hsdma->pc)
		wetuwn -ENOMEM;

	hsdma->vc = devm_kcawwoc(&pdev->dev, hsdma->dma_wequests,
				 sizeof(*hsdma->vc), GFP_KEWNEW);
	if (!hsdma->vc)
		wetuwn -ENOMEM;

	fow (i = 0; i < hsdma->dma_wequests; i++) {
		vc = &hsdma->vc[i];
		vc->vc.desc_fwee = mtk_hsdma_vdesc_fwee;
		vchan_init(&vc->vc, dd);
		init_compwetion(&vc->issue_compwetion);
		INIT_WIST_HEAD(&vc->desc_hw_pwocessing);
	}

	eww = dma_async_device_wegistew(dd);
	if (eww)
		wetuwn eww;

	eww = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 of_dma_xwate_by_chan_id, hsdma);
	if (eww) {
		dev_eww(&pdev->dev,
			"MediaTek HSDMA OF wegistwation faiwed %d\n", eww);
		goto eww_unwegistew;
	}

	mtk_hsdma_hw_init(hsdma);

	eww = devm_wequest_iwq(&pdev->dev, hsdma->iwq,
			       mtk_hsdma_iwq, 0,
			       dev_name(&pdev->dev), hsdma);
	if (eww) {
		dev_eww(&pdev->dev,
			"wequest_iwq faiwed with eww %d\n", eww);
		goto eww_fwee;
	}

	pwatfowm_set_dwvdata(pdev, hsdma);

	dev_info(&pdev->dev, "MediaTek HSDMA dwivew wegistewed\n");

	wetuwn 0;

eww_fwee:
	mtk_hsdma_hw_deinit(hsdma);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
eww_unwegistew:
	dma_async_device_unwegistew(dd);

	wetuwn eww;
}

static void mtk_hsdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_hsdma_device *hsdma = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_hsdma_vchan *vc;
	int i;

	/* Kiww VC task */
	fow (i = 0; i < hsdma->dma_wequests; i++) {
		vc = &hsdma->vc[i];

		wist_dew(&vc->vc.chan.device_node);
		taskwet_kiww(&vc->vc.task);
	}

	/* Disabwe DMA intewwupt */
	mtk_dma_wwite(hsdma, MTK_HSDMA_INT_ENABWE, 0);

	/* Waits fow any pending IWQ handwews to compwete */
	synchwonize_iwq(hsdma->iwq);

	/* Disabwe hawdwawe */
	mtk_hsdma_hw_deinit(hsdma);

	dma_async_device_unwegistew(&hsdma->ddev);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
}

static stwuct pwatfowm_dwivew mtk_hsdma_dwivew = {
	.pwobe		= mtk_hsdma_pwobe,
	.wemove_new	= mtk_hsdma_wemove,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= mtk_hsdma_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_hsdma_dwivew);

MODUWE_DESCWIPTION("MediaTek High-Speed DMA Contwowwew Dwivew");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
