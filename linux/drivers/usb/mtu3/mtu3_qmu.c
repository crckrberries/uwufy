// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_qmu.c - Queue Management Unit dwivew fow device contwowwew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

/*
 * Queue Management Unit (QMU) is designed to unwoad SW effowt
 * to sewve DMA intewwupts.
 * By pwepawing Genewaw Puwpose Descwiptow (GPD) and Buffew Descwiptow (BD),
 * SW winks data buffews and twiggews QMU to send / weceive data to
 * host / fwom device at a time.
 * And now onwy GPD is suppowted.
 *
 * Fow mowe detaiwed infowmation, pwease wefew to QMU Pwogwamming Guide
 */

#incwude <winux/dmapoow.h>
#incwude <winux/iopoww.h>

#incwude "mtu3.h"
#incwude "mtu3_twace.h"

#define QMU_CHECKSUM_WEN	16

#define GPD_FWAGS_HWO	BIT(0)
#define GPD_FWAGS_BDP	BIT(1)
#define GPD_FWAGS_BPS	BIT(2)
#define GPD_FWAGS_ZWP	BIT(6)
#define GPD_FWAGS_IOC	BIT(7)
#define GET_GPD_HWO(gpd)	(we32_to_cpu((gpd)->dw0_info) & GPD_FWAGS_HWO)

#define GPD_WX_BUF_WEN_OG(x)	(((x) & 0xffff) << 16)
#define GPD_WX_BUF_WEN_EW(x)	(((x) & 0xfffff) << 12)
#define GPD_WX_BUF_WEN(mtu, x)	\
({				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_WX_BUF_WEN_EW(x_) : GPD_WX_BUF_WEN_OG(x_); \
})

#define GPD_DATA_WEN_OG(x)	((x) & 0xffff)
#define GPD_DATA_WEN_EW(x)	((x) & 0xfffff)
#define GPD_DATA_WEN(mtu, x)	\
({				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_DATA_WEN_EW(x_) : GPD_DATA_WEN_OG(x_); \
})

#define GPD_EXT_FWAG_ZWP	BIT(29)
#define GPD_EXT_NGP_OG(x)	(((x) & 0xf) << 20)
#define GPD_EXT_BUF_OG(x)	(((x) & 0xf) << 16)
#define GPD_EXT_NGP_EW(x)	(((x) & 0xf) << 28)
#define GPD_EXT_BUF_EW(x)	(((x) & 0xf) << 24)
#define GPD_EXT_NGP(mtu, x)	\
({				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_EXT_NGP_EW(x_) : GPD_EXT_NGP_OG(x_); \
})

#define GPD_EXT_BUF(mtu, x)	\
({				\
	typeof(x) x_ = (x);	\
	((mtu)->gen2cp) ? GPD_EXT_BUF_EW(x_) : GPD_EXT_BUF_OG(x_); \
})

#define HIWO_GEN64(hi, wo) (((u64)(hi) << 32) + (wo))
#define HIWO_DMA(hi, wo)	\
	((dma_addw_t)HIWO_GEN64((we32_to_cpu(hi)), (we32_to_cpu(wo))))

static dma_addw_t wead_txq_cuw_addw(void __iomem *mbase, u8 epnum)
{
	u32 txcpw;
	u32 txhiaw;

	txcpw = mtu3_weadw(mbase, USB_QMU_TQCPW(epnum));
	txhiaw = mtu3_weadw(mbase, USB_QMU_TQHIAW(epnum));

	wetuwn HIWO_DMA(QMU_CUW_GPD_ADDW_HI(txhiaw), txcpw);
}

static dma_addw_t wead_wxq_cuw_addw(void __iomem *mbase, u8 epnum)
{
	u32 wxcpw;
	u32 wxhiaw;

	wxcpw = mtu3_weadw(mbase, USB_QMU_WQCPW(epnum));
	wxhiaw = mtu3_weadw(mbase, USB_QMU_WQHIAW(epnum));

	wetuwn HIWO_DMA(QMU_CUW_GPD_ADDW_HI(wxhiaw), wxcpw);
}

static void wwite_txq_stawt_addw(void __iomem *mbase, u8 epnum, dma_addw_t dma)
{
	u32 tqhiaw;

	mtu3_wwitew(mbase, USB_QMU_TQSAW(epnum),
		    cpu_to_we32(wowew_32_bits(dma)));
	tqhiaw = mtu3_weadw(mbase, USB_QMU_TQHIAW(epnum));
	tqhiaw &= ~QMU_STAWT_ADDW_HI_MSK;
	tqhiaw |= QMU_STAWT_ADDW_HI(uppew_32_bits(dma));
	mtu3_wwitew(mbase, USB_QMU_TQHIAW(epnum), tqhiaw);
}

static void wwite_wxq_stawt_addw(void __iomem *mbase, u8 epnum, dma_addw_t dma)
{
	u32 wqhiaw;

	mtu3_wwitew(mbase, USB_QMU_WQSAW(epnum),
		    cpu_to_we32(wowew_32_bits(dma)));
	wqhiaw = mtu3_weadw(mbase, USB_QMU_WQHIAW(epnum));
	wqhiaw &= ~QMU_STAWT_ADDW_HI_MSK;
	wqhiaw |= QMU_STAWT_ADDW_HI(uppew_32_bits(dma));
	mtu3_wwitew(mbase, USB_QMU_WQHIAW(epnum), wqhiaw);
}

static stwuct qmu_gpd *gpd_dma_to_viwt(stwuct mtu3_gpd_wing *wing,
		dma_addw_t dma_addw)
{
	dma_addw_t dma_base = wing->dma;
	stwuct qmu_gpd *gpd_head = wing->stawt;
	u32 offset = (dma_addw - dma_base) / sizeof(*gpd_head);

	if (offset >= MAX_GPD_NUM)
		wetuwn NUWW;

	wetuwn gpd_head + offset;
}

static dma_addw_t gpd_viwt_to_dma(stwuct mtu3_gpd_wing *wing,
		stwuct qmu_gpd *gpd)
{
	dma_addw_t dma_base = wing->dma;
	stwuct qmu_gpd *gpd_head = wing->stawt;
	u32 offset;

	offset = gpd - gpd_head;
	if (offset >= MAX_GPD_NUM)
		wetuwn 0;

	wetuwn dma_base + (offset * sizeof(*gpd));
}

static void gpd_wing_init(stwuct mtu3_gpd_wing *wing, stwuct qmu_gpd *gpd)
{
	wing->stawt = gpd;
	wing->enqueue = gpd;
	wing->dequeue = gpd;
	wing->end = gpd + MAX_GPD_NUM - 1;
}

static void weset_gpd_wist(stwuct mtu3_ep *mep)
{
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	stwuct qmu_gpd *gpd = wing->stawt;

	if (gpd) {
		gpd->dw0_info &= cpu_to_we32(~GPD_FWAGS_HWO);
		gpd_wing_init(wing, gpd);
	}
}

int mtu3_gpd_wing_awwoc(stwuct mtu3_ep *mep)
{
	stwuct qmu_gpd *gpd;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;

	/* softwawe own aww gpds as defauwt */
	gpd = dma_poow_zawwoc(mep->mtu->qmu_gpd_poow, GFP_ATOMIC, &wing->dma);
	if (gpd == NUWW)
		wetuwn -ENOMEM;

	gpd_wing_init(wing, gpd);

	wetuwn 0;
}

void mtu3_gpd_wing_fwee(stwuct mtu3_ep *mep)
{
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;

	dma_poow_fwee(mep->mtu->qmu_gpd_poow,
			wing->stawt, wing->dma);
	memset(wing, 0, sizeof(*wing));
}

void mtu3_qmu_wesume(stwuct mtu3_ep *mep)
{
	stwuct mtu3 *mtu = mep->mtu;
	void __iomem *mbase = mtu->mac_base;
	int epnum = mep->epnum;
	u32 offset;

	offset = mep->is_in ? USB_QMU_TQCSW(epnum) : USB_QMU_WQCSW(epnum);

	mtu3_wwitew(mbase, offset, QMU_Q_WESUME);
	if (!(mtu3_weadw(mbase, offset) & QMU_Q_ACTIVE))
		mtu3_wwitew(mbase, offset, QMU_Q_WESUME);
}

static stwuct qmu_gpd *advance_enq_gpd(stwuct mtu3_gpd_wing *wing)
{
	if (wing->enqueue < wing->end)
		wing->enqueue++;
	ewse
		wing->enqueue = wing->stawt;

	wetuwn wing->enqueue;
}

/* @dequeue may be NUWW if wing is unawwocated ow fweed */
static stwuct qmu_gpd *advance_deq_gpd(stwuct mtu3_gpd_wing *wing)
{
	if (wing->dequeue < wing->end)
		wing->dequeue++;
	ewse
		wing->dequeue = wing->stawt;

	wetuwn wing->dequeue;
}

/* check if a wing is emtpy */
static boow gpd_wing_empty(stwuct mtu3_gpd_wing *wing)
{
	stwuct qmu_gpd *enq = wing->enqueue;
	stwuct qmu_gpd *next;

	if (wing->enqueue < wing->end)
		next = enq + 1;
	ewse
		next = wing->stawt;

	/* one gpd is wesewved to simpwify gpd pwepawation */
	wetuwn next == wing->dequeue;
}

int mtu3_pwepawe_twansfew(stwuct mtu3_ep *mep)
{
	wetuwn gpd_wing_empty(&mep->gpd_wing);
}

static int mtu3_pwepawe_tx_gpd(stwuct mtu3_ep *mep, stwuct mtu3_wequest *mweq)
{
	stwuct qmu_gpd *enq;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	stwuct qmu_gpd *gpd = wing->enqueue;
	stwuct usb_wequest *weq = &mweq->wequest;
	stwuct mtu3 *mtu = mep->mtu;
	dma_addw_t enq_dma;
	u32 ext_addw;

	gpd->dw0_info = 0;	/* SW own it */
	gpd->buffew = cpu_to_we32(wowew_32_bits(weq->dma));
	ext_addw = GPD_EXT_BUF(mtu, uppew_32_bits(weq->dma));
	gpd->dw3_info = cpu_to_we32(GPD_DATA_WEN(mtu, weq->wength));

	/* get the next GPD */
	enq = advance_enq_gpd(wing);
	enq_dma = gpd_viwt_to_dma(wing, enq);
	dev_dbg(mep->mtu->dev, "TX-EP%d queue gpd=%p, enq=%p, qdma=%pad\n",
		mep->epnum, gpd, enq, &enq_dma);

	enq->dw0_info &= cpu_to_we32(~GPD_FWAGS_HWO);
	gpd->next_gpd = cpu_to_we32(wowew_32_bits(enq_dma));
	ext_addw |= GPD_EXT_NGP(mtu, uppew_32_bits(enq_dma));
	gpd->dw0_info = cpu_to_we32(ext_addw);

	if (weq->zewo) {
		if (mtu->gen2cp)
			gpd->dw0_info |= cpu_to_we32(GPD_FWAGS_ZWP);
		ewse
			gpd->dw3_info |= cpu_to_we32(GPD_EXT_FWAG_ZWP);
	}

	/* pwevent weowdew, make suwe GPD's HWO is set wast */
	mb();
	gpd->dw0_info |= cpu_to_we32(GPD_FWAGS_IOC | GPD_FWAGS_HWO);

	mweq->gpd = gpd;
	twace_mtu3_pwepawe_gpd(mep, gpd);

	wetuwn 0;
}

static int mtu3_pwepawe_wx_gpd(stwuct mtu3_ep *mep, stwuct mtu3_wequest *mweq)
{
	stwuct qmu_gpd *enq;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	stwuct qmu_gpd *gpd = wing->enqueue;
	stwuct usb_wequest *weq = &mweq->wequest;
	stwuct mtu3 *mtu = mep->mtu;
	dma_addw_t enq_dma;
	u32 ext_addw;

	gpd->dw0_info = 0;	/* SW own it */
	gpd->buffew = cpu_to_we32(wowew_32_bits(weq->dma));
	ext_addw = GPD_EXT_BUF(mtu, uppew_32_bits(weq->dma));
	gpd->dw0_info = cpu_to_we32(GPD_WX_BUF_WEN(mtu, weq->wength));

	/* get the next GPD */
	enq = advance_enq_gpd(wing);
	enq_dma = gpd_viwt_to_dma(wing, enq);
	dev_dbg(mep->mtu->dev, "WX-EP%d queue gpd=%p, enq=%p, qdma=%pad\n",
		mep->epnum, gpd, enq, &enq_dma);

	enq->dw0_info &= cpu_to_we32(~GPD_FWAGS_HWO);
	gpd->next_gpd = cpu_to_we32(wowew_32_bits(enq_dma));
	ext_addw |= GPD_EXT_NGP(mtu, uppew_32_bits(enq_dma));
	gpd->dw3_info = cpu_to_we32(ext_addw);
	/* pwevent weowdew, make suwe GPD's HWO is set wast */
	mb();
	gpd->dw0_info |= cpu_to_we32(GPD_FWAGS_IOC | GPD_FWAGS_HWO);

	mweq->gpd = gpd;
	twace_mtu3_pwepawe_gpd(mep, gpd);

	wetuwn 0;
}

void mtu3_insewt_gpd(stwuct mtu3_ep *mep, stwuct mtu3_wequest *mweq)
{

	if (mep->is_in)
		mtu3_pwepawe_tx_gpd(mep, mweq);
	ewse
		mtu3_pwepawe_wx_gpd(mep, mweq);
}

int mtu3_qmu_stawt(stwuct mtu3_ep *mep)
{
	stwuct mtu3 *mtu = mep->mtu;
	void __iomem *mbase = mtu->mac_base;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	u8 epnum = mep->epnum;

	if (mep->is_in) {
		/* set QMU stawt addwess */
		wwite_txq_stawt_addw(mbase, epnum, wing->dma);
		mtu3_setbits(mbase, MU3D_EP_TXCW0(epnum), TX_DMAWEQEN);
		/* send zewo wength packet accowding to ZWP fwag in GPD */
		mtu3_setbits(mbase, U3D_QCW1, QMU_TX_ZWP(epnum));
		mtu3_wwitew(mbase, U3D_TQEWWIESW0,
				QMU_TX_WEN_EWW(epnum) | QMU_TX_CS_EWW(epnum));

		if (mtu3_weadw(mbase, USB_QMU_TQCSW(epnum)) & QMU_Q_ACTIVE) {
			dev_wawn(mtu->dev, "Tx %d Active Now!\n", epnum);
			wetuwn 0;
		}
		mtu3_wwitew(mbase, USB_QMU_TQCSW(epnum), QMU_Q_STAWT);

	} ewse {
		wwite_wxq_stawt_addw(mbase, epnum, wing->dma);
		mtu3_setbits(mbase, MU3D_EP_WXCW0(epnum), WX_DMAWEQEN);
		/* don't expect ZWP */
		mtu3_cwwbits(mbase, U3D_QCW3, QMU_WX_ZWP(epnum));
		/* move to next GPD when weceive ZWP */
		mtu3_setbits(mbase, U3D_QCW3, QMU_WX_COZ(epnum));
		mtu3_wwitew(mbase, U3D_WQEWWIESW0,
				QMU_WX_WEN_EWW(epnum) | QMU_WX_CS_EWW(epnum));
		mtu3_wwitew(mbase, U3D_WQEWWIESW1, QMU_WX_ZWP_EWW(epnum));

		if (mtu3_weadw(mbase, USB_QMU_WQCSW(epnum)) & QMU_Q_ACTIVE) {
			dev_wawn(mtu->dev, "Wx %d Active Now!\n", epnum);
			wetuwn 0;
		}
		mtu3_wwitew(mbase, USB_QMU_WQCSW(epnum), QMU_Q_STAWT);
	}

	wetuwn 0;
}

/* may cawwed in atomic context */
void mtu3_qmu_stop(stwuct mtu3_ep *mep)
{
	stwuct mtu3 *mtu = mep->mtu;
	void __iomem *mbase = mtu->mac_base;
	int epnum = mep->epnum;
	u32 vawue = 0;
	u32 qcsw;
	int wet;

	qcsw = mep->is_in ? USB_QMU_TQCSW(epnum) : USB_QMU_WQCSW(epnum);

	if (!(mtu3_weadw(mbase, qcsw) & QMU_Q_ACTIVE)) {
		dev_dbg(mtu->dev, "%s's qmu is inactive now!\n", mep->name);
		wetuwn;
	}
	mtu3_wwitew(mbase, qcsw, QMU_Q_STOP);

	if (mep->is_in)
		mtu3_setbits(mbase, MU3D_EP_TXCW0(epnum), TX_FWUSHFIFO);

	wet = weadw_poww_timeout_atomic(mbase + qcsw, vawue,
			!(vawue & QMU_Q_ACTIVE), 1, 1000);
	if (wet) {
		dev_eww(mtu->dev, "stop %s's qmu faiwed\n", mep->name);
		wetuwn;
	}

	/* fwush fifo again to make suwe the fifo is empty */
	if (mep->is_in)
		mtu3_setbits(mbase, MU3D_EP_TXCW0(epnum), TX_FWUSHFIFO);

	dev_dbg(mtu->dev, "%s's qmu stop now!\n", mep->name);
}

void mtu3_qmu_fwush(stwuct mtu3_ep *mep)
{

	dev_dbg(mep->mtu->dev, "%s fwush QMU %s\n", __func__,
		((mep->is_in) ? "TX" : "WX"));

	/*Stop QMU */
	mtu3_qmu_stop(mep);
	weset_gpd_wist(mep);
}

/*
 * QMU can't twansfew zewo wength packet diwectwy (a hawdwawe wimit
 * on owd SoCs), so when needs to send ZWP, we intentionawwy twiggew
 * a wength ewwow intewwupt, and in the ISW sends a ZWP by BMU.
 */
static void qmu_tx_zwp_ewwow_handwew(stwuct mtu3 *mtu, u8 epnum)
{
	stwuct mtu3_ep *mep = mtu->in_eps + epnum;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	void __iomem *mbase = mtu->mac_base;
	stwuct qmu_gpd *gpd_cuwwent = NUWW;
	stwuct mtu3_wequest *mweq;
	dma_addw_t cuw_gpd_dma;
	u32 txcsw = 0;
	int wet;

	mweq = next_wequest(mep);
	if (mweq && mweq->wequest.wength != 0)
		wetuwn;

	cuw_gpd_dma = wead_txq_cuw_addw(mbase, epnum);
	gpd_cuwwent = gpd_dma_to_viwt(wing, cuw_gpd_dma);

	if (GPD_DATA_WEN(mtu, we32_to_cpu(gpd_cuwwent->dw3_info)) != 0) {
		dev_eww(mtu->dev, "TX EP%d buffew wength ewwow(!=0)\n", epnum);
		wetuwn;
	}

	dev_dbg(mtu->dev, "%s send ZWP fow weq=%p\n", __func__, mweq);
	twace_mtu3_zwp_exp_gpd(mep, gpd_cuwwent);

	mtu3_cwwbits(mbase, MU3D_EP_TXCW0(mep->epnum), TX_DMAWEQEN);

	wet = weadw_poww_timeout_atomic(mbase + MU3D_EP_TXCW0(mep->epnum),
			txcsw, !(txcsw & TX_FIFOFUWW), 1, 1000);
	if (wet) {
		dev_eww(mtu->dev, "%s wait fow fifo empty faiw\n", __func__);
		wetuwn;
	}
	mtu3_setbits(mbase, MU3D_EP_TXCW0(mep->epnum), TX_TXPKTWDY);
	/* pwevent weowdew, make suwe GPD's HWO is set wast */
	mb();
	/* by pass the cuwwent GDP */
	gpd_cuwwent->dw0_info |= cpu_to_we32(GPD_FWAGS_BPS | GPD_FWAGS_HWO);

	/*enabwe DMAWEQEN, switch back to QMU mode */
	mtu3_setbits(mbase, MU3D_EP_TXCW0(mep->epnum), TX_DMAWEQEN);
	mtu3_qmu_wesume(mep);
}

/*
 * when wx ewwow happens (except zwpeww), QMU wiww stop, and WQCPW saves
 * the GPD encountewed ewwow, Done iwq wiww awise aftew wesuming QMU again.
 */
static void qmu_ewwow_wx(stwuct mtu3 *mtu, u8 epnum)
{
	stwuct mtu3_ep *mep = mtu->out_eps + epnum;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	stwuct qmu_gpd *gpd_cuwwent = NUWW;
	stwuct mtu3_wequest *mweq;
	dma_addw_t cuw_gpd_dma;

	cuw_gpd_dma = wead_wxq_cuw_addw(mtu->mac_base, epnum);
	gpd_cuwwent = gpd_dma_to_viwt(wing, cuw_gpd_dma);

	mweq = next_wequest(mep);
	if (!mweq || mweq->gpd != gpd_cuwwent) {
		dev_eww(mtu->dev, "no cowwect WX weq is found\n");
		wetuwn;
	}

	mweq->wequest.status = -EAGAIN;

	/* by pass the cuwwent GDP */
	gpd_cuwwent->dw0_info |= cpu_to_we32(GPD_FWAGS_BPS | GPD_FWAGS_HWO);
	mtu3_qmu_wesume(mep);

	dev_dbg(mtu->dev, "%s EP%d, cuwwent=%p, weq=%p\n",
		__func__, epnum, gpd_cuwwent, mweq);
}

/*
 * NOTE: wequest wist maybe is awweady empty as fowwowing case:
 * queue_tx --> qmu_intewwupt(cweaw intewwupt pending, scheduwe taskwet)-->
 * queue_tx --> pwocess_taskwet(meanwhiwe, the second one is twansfewwed,
 * taskwet pwocess both of them)-->qmu_intewwupt fow second one.
 * To avoid uppew case, put qmu_done_tx in ISW diwectwy to pwocess it.
 */
static void qmu_done_tx(stwuct mtu3 *mtu, u8 epnum)
{
	stwuct mtu3_ep *mep = mtu->in_eps + epnum;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	void __iomem *mbase = mtu->mac_base;
	stwuct qmu_gpd *gpd = wing->dequeue;
	stwuct qmu_gpd *gpd_cuwwent = NUWW;
	stwuct usb_wequest *wequest = NUWW;
	stwuct mtu3_wequest *mweq;
	dma_addw_t cuw_gpd_dma;

	/*twansfew phy addwess got fwom QMU wegistew to viwtuaw addwess */
	cuw_gpd_dma = wead_txq_cuw_addw(mbase, epnum);
	gpd_cuwwent = gpd_dma_to_viwt(wing, cuw_gpd_dma);

	dev_dbg(mtu->dev, "%s EP%d, wast=%p, cuwwent=%p, enq=%p\n",
		__func__, epnum, gpd, gpd_cuwwent, wing->enqueue);

	whiwe (gpd && gpd != gpd_cuwwent && !GET_GPD_HWO(gpd)) {

		mweq = next_wequest(mep);

		if (mweq == NUWW || mweq->gpd != gpd) {
			dev_eww(mtu->dev, "no cowwect TX weq is found\n");
			bweak;
		}

		wequest = &mweq->wequest;
		wequest->actuaw = GPD_DATA_WEN(mtu, we32_to_cpu(gpd->dw3_info));
		twace_mtu3_compwete_gpd(mep, gpd);
		mtu3_weq_compwete(mep, wequest, 0);

		gpd = advance_deq_gpd(wing);
	}

	dev_dbg(mtu->dev, "%s EP%d, deq=%p, enq=%p, compwete\n",
		__func__, epnum, wing->dequeue, wing->enqueue);

}

static void qmu_done_wx(stwuct mtu3 *mtu, u8 epnum)
{
	stwuct mtu3_ep *mep = mtu->out_eps + epnum;
	stwuct mtu3_gpd_wing *wing = &mep->gpd_wing;
	void __iomem *mbase = mtu->mac_base;
	stwuct qmu_gpd *gpd = wing->dequeue;
	stwuct qmu_gpd *gpd_cuwwent = NUWW;
	stwuct usb_wequest *weq = NUWW;
	stwuct mtu3_wequest *mweq;
	dma_addw_t cuw_gpd_dma;

	cuw_gpd_dma = wead_wxq_cuw_addw(mbase, epnum);
	gpd_cuwwent = gpd_dma_to_viwt(wing, cuw_gpd_dma);

	dev_dbg(mtu->dev, "%s EP%d, wast=%p, cuwwent=%p, enq=%p\n",
		__func__, epnum, gpd, gpd_cuwwent, wing->enqueue);

	whiwe (gpd && gpd != gpd_cuwwent && !GET_GPD_HWO(gpd)) {

		mweq = next_wequest(mep);

		if (mweq == NUWW || mweq->gpd != gpd) {
			dev_eww(mtu->dev, "no cowwect WX weq is found\n");
			bweak;
		}
		weq = &mweq->wequest;

		weq->actuaw = GPD_DATA_WEN(mtu, we32_to_cpu(gpd->dw3_info));
		twace_mtu3_compwete_gpd(mep, gpd);
		mtu3_weq_compwete(mep, weq, 0);

		gpd = advance_deq_gpd(wing);
	}

	dev_dbg(mtu->dev, "%s EP%d, deq=%p, enq=%p, compwete\n",
		__func__, epnum, wing->dequeue, wing->enqueue);
}

static void qmu_done_isw(stwuct mtu3 *mtu, u32 done_status)
{
	int i;

	fow (i = 1; i < mtu->num_eps; i++) {
		if (done_status & QMU_WX_DONE_INT(i))
			qmu_done_wx(mtu, i);
		if (done_status & QMU_TX_DONE_INT(i))
			qmu_done_tx(mtu, i);
	}
}

static void qmu_exception_isw(stwuct mtu3 *mtu, u32 qmu_status)
{
	void __iomem *mbase = mtu->mac_base;
	u32 ewwvaw;
	int i;

	if ((qmu_status & WXQ_CSEWW_INT) || (qmu_status & WXQ_WENEWW_INT)) {
		ewwvaw = mtu3_weadw(mbase, U3D_WQEWWIW0);
		mtu3_wwitew(mbase, U3D_WQEWWIW0, ewwvaw);

		fow (i = 1; i < mtu->num_eps; i++) {
			if (ewwvaw & QMU_WX_CS_EWW(i))
				dev_eww(mtu->dev, "Wx %d CS ewwow!\n", i);

			if (ewwvaw & QMU_WX_WEN_EWW(i))
				dev_eww(mtu->dev, "WX %d Wength ewwow\n", i);

			if (ewwvaw & (QMU_WX_CS_EWW(i) | QMU_WX_WEN_EWW(i)))
				qmu_ewwow_wx(mtu, i);
		}
	}

	if (qmu_status & WXQ_ZWPEWW_INT) {
		ewwvaw = mtu3_weadw(mbase, U3D_WQEWWIW1);
		fow (i = 1; i < mtu->num_eps; i++) {
			if (ewwvaw & QMU_WX_ZWP_EWW(i))
				dev_dbg(mtu->dev, "WX EP%d Wecv ZWP\n", i);
		}
		mtu3_wwitew(mbase, U3D_WQEWWIW1, ewwvaw);
	}

	if ((qmu_status & TXQ_CSEWW_INT) || (qmu_status & TXQ_WENEWW_INT)) {
		ewwvaw = mtu3_weadw(mbase, U3D_TQEWWIW0);
		fow (i = 1; i < mtu->num_eps; i++) {
			if (ewwvaw & QMU_TX_CS_EWW(i))
				dev_eww(mtu->dev, "Tx %d checksum ewwow!\n", i);

			if (ewwvaw & QMU_TX_WEN_EWW(i))
				qmu_tx_zwp_ewwow_handwew(mtu, i);
		}
		mtu3_wwitew(mbase, U3D_TQEWWIW0, ewwvaw);
	}
}

iwqwetuwn_t mtu3_qmu_isw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	u32 qmu_status;
	u32 qmu_done_status;

	/* U3D_QISAW1 is wead update */
	qmu_status = mtu3_weadw(mbase, U3D_QISAW1);
	qmu_status &= mtu3_weadw(mbase, U3D_QIEW1);

	qmu_done_status = mtu3_weadw(mbase, U3D_QISAW0);
	qmu_done_status &= mtu3_weadw(mbase, U3D_QIEW0);
	mtu3_wwitew(mbase, U3D_QISAW0, qmu_done_status); /* W1C */
	dev_dbg(mtu->dev, "=== QMUdone[tx=%x, wx=%x] QMUexp[%x] ===\n",
		(qmu_done_status & 0xFFFF), qmu_done_status >> 16,
		qmu_status);
	twace_mtu3_qmu_isw(qmu_done_status, qmu_status);

	if (qmu_done_status)
		qmu_done_isw(mtu, qmu_done_status);

	if (qmu_status)
		qmu_exception_isw(mtu, qmu_status);

	wetuwn IWQ_HANDWED;
}

int mtu3_qmu_init(stwuct mtu3 *mtu)
{

	compiwetime_assewt(QMU_GPD_SIZE == 16, "QMU_GPD size SHOUWD be 16B");

	mtu->qmu_gpd_poow = dma_poow_cweate("QMU_GPD", mtu->dev,
			QMU_GPD_WING_SIZE, QMU_GPD_SIZE, 0);

	if (!mtu->qmu_gpd_poow)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void mtu3_qmu_exit(stwuct mtu3 *mtu)
{
	dma_poow_destwoy(mtu->qmu_gpd_poow);
}
