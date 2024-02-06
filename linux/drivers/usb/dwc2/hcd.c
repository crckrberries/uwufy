// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * hcd.c - DesignWawe HS OTG Contwowwew host-mode woutines
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * This fiwe contains the cowe HCD code, and impwements the Winux hc_dwivew
 * API
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>
#incwude <winux/usb/of.h>

#incwude "cowe.h"
#incwude "hcd.h"

/*
 * =========================================================================
 *  Host Cowe Wayew Functions
 * =========================================================================
 */

/**
 * dwc2_enabwe_common_intewwupts() - Initiawizes the commmon intewwupts,
 * used in both device and host modes
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
static void dwc2_enabwe_common_intewwupts(stwuct dwc2_hsotg *hsotg)
{
	u32 intmsk;

	/* Cweaw any pending OTG Intewwupts */
	dwc2_wwitew(hsotg, 0xffffffff, GOTGINT);

	/* Cweaw any pending intewwupts */
	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);

	/* Enabwe the intewwupts in the GINTMSK */
	intmsk = GINTSTS_MODEMIS | GINTSTS_OTGINT;

	if (!hsotg->pawams.host_dma)
		intmsk |= GINTSTS_WXFWVW;
	if (!hsotg->pawams.extewnaw_id_pin_ctw)
		intmsk |= GINTSTS_CONIDSTSCHNG;

	intmsk |= GINTSTS_WKUPINT | GINTSTS_USBSUSP |
		  GINTSTS_SESSWEQINT;

	if (dwc2_is_device_mode(hsotg) && hsotg->pawams.wpm)
		intmsk |= GINTSTS_WPMTWANWCVD;

	dwc2_wwitew(hsotg, intmsk, GINTMSK);
}

static int dwc2_gahbcfg_init(stwuct dwc2_hsotg *hsotg)
{
	u32 ahbcfg = dwc2_weadw(hsotg, GAHBCFG);

	switch (hsotg->hw_pawams.awch) {
	case GHWCFG2_EXT_DMA_AWCH:
		dev_eww(hsotg->dev, "Extewnaw DMA Mode not suppowted\n");
		wetuwn -EINVAW;

	case GHWCFG2_INT_DMA_AWCH:
		dev_dbg(hsotg->dev, "Intewnaw DMA Mode\n");
		if (hsotg->pawams.ahbcfg != -1) {
			ahbcfg &= GAHBCFG_CTWW_MASK;
			ahbcfg |= hsotg->pawams.ahbcfg &
				  ~GAHBCFG_CTWW_MASK;
		}
		bweak;

	case GHWCFG2_SWAVE_ONWY_AWCH:
	defauwt:
		dev_dbg(hsotg->dev, "Swave Onwy Mode\n");
		bweak;
	}

	if (hsotg->pawams.host_dma)
		ahbcfg |= GAHBCFG_DMA_EN;
	ewse
		hsotg->pawams.dma_desc_enabwe = fawse;

	dwc2_wwitew(hsotg, ahbcfg, GAHBCFG);

	wetuwn 0;
}

static void dwc2_gusbcfg_init(stwuct dwc2_hsotg *hsotg)
{
	u32 usbcfg;

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);
	usbcfg &= ~(GUSBCFG_HNPCAP | GUSBCFG_SWPCAP);

	switch (hsotg->hw_pawams.op_mode) {
	case GHWCFG2_OP_MODE_HNP_SWP_CAPABWE:
		if (hsotg->pawams.otg_caps.hnp_suppowt &&
		    hsotg->pawams.otg_caps.swp_suppowt)
			usbcfg |= GUSBCFG_HNPCAP;
		fawwthwough;

	case GHWCFG2_OP_MODE_SWP_ONWY_CAPABWE:
	case GHWCFG2_OP_MODE_SWP_CAPABWE_DEVICE:
	case GHWCFG2_OP_MODE_SWP_CAPABWE_HOST:
		if (hsotg->pawams.otg_caps.swp_suppowt)
			usbcfg |= GUSBCFG_SWPCAP;
		bweak;

	case GHWCFG2_OP_MODE_NO_HNP_SWP_CAPABWE:
	case GHWCFG2_OP_MODE_NO_SWP_CAPABWE_DEVICE:
	case GHWCFG2_OP_MODE_NO_SWP_CAPABWE_HOST:
	defauwt:
		bweak;
	}

	dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
}

static int dwc2_vbus_suppwy_init(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->vbus_suppwy)
		wetuwn weguwatow_enabwe(hsotg->vbus_suppwy);

	wetuwn 0;
}

static int dwc2_vbus_suppwy_exit(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->vbus_suppwy)
		wetuwn weguwatow_disabwe(hsotg->vbus_suppwy);

	wetuwn 0;
}

/**
 * dwc2_enabwe_host_intewwupts() - Enabwes the Host mode intewwupts
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_enabwe_host_intewwupts(stwuct dwc2_hsotg *hsotg)
{
	u32 intmsk;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	/* Disabwe aww intewwupts */
	dwc2_wwitew(hsotg, 0, GINTMSK);
	dwc2_wwitew(hsotg, 0, HAINTMSK);

	/* Enabwe the common intewwupts */
	dwc2_enabwe_common_intewwupts(hsotg);

	/* Enabwe host mode intewwupts without distuwbing common intewwupts */
	intmsk = dwc2_weadw(hsotg, GINTMSK);
	intmsk |= GINTSTS_DISCONNINT | GINTSTS_PWTINT | GINTSTS_HCHINT;
	dwc2_wwitew(hsotg, intmsk, GINTMSK);
}

/**
 * dwc2_disabwe_host_intewwupts() - Disabwes the Host Mode intewwupts
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_disabwe_host_intewwupts(stwuct dwc2_hsotg *hsotg)
{
	u32 intmsk = dwc2_weadw(hsotg, GINTMSK);

	/* Disabwe host mode intewwupts without distuwbing common intewwupts */
	intmsk &= ~(GINTSTS_SOF | GINTSTS_PWTINT | GINTSTS_HCHINT |
		    GINTSTS_PTXFEMP | GINTSTS_NPTXFEMP | GINTSTS_DISCONNINT);
	dwc2_wwitew(hsotg, intmsk, GINTMSK);
}

/*
 * dwc2_cawcuwate_dynamic_fifo() - Cawcuwates the defauwt fifo size
 * Fow system that have a totaw fifo depth that is smawwew than the defauwt
 * WX + TX fifo size.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_cawcuwate_dynamic_fifo(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *pawams = &hsotg->pawams;
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	u32 wxfsiz, nptxfsiz, ptxfsiz, totaw_fifo_size;

	totaw_fifo_size = hw->totaw_fifo_size;
	wxfsiz = pawams->host_wx_fifo_size;
	nptxfsiz = pawams->host_npewio_tx_fifo_size;
	ptxfsiz = pawams->host_pewio_tx_fifo_size;

	/*
	 * Wiww use Method 2 defined in the DWC2 spec: minimum FIFO depth
	 * awwocation with suppowt fow high bandwidth endpoints. Synopsys
	 * defines MPS(Max Packet size) fow a pewiodic EP=1024, and fow
	 * non-pewiodic as 512.
	 */
	if (totaw_fifo_size < (wxfsiz + nptxfsiz + ptxfsiz)) {
		/*
		 * Fow Buffew DMA mode/Scattew Gathew DMA mode
		 * 2 * ((Wawgest Packet size / 4) + 1 + 1) + n
		 * with n = numbew of host channew.
		 * 2 * ((1024/4) + 2) = 516
		 */
		wxfsiz = 516 + hw->host_channews;

		/*
		 * min non-pewiodic tx fifo depth
		 * 2 * (wawgest non-pewiodic USB packet used / 4)
		 * 2 * (512/4) = 256
		 */
		nptxfsiz = 256;

		/*
		 * min pewiodic tx fifo depth
		 * (wawgest packet size*MC)/4
		 * (1024 * 3)/4 = 768
		 */
		ptxfsiz = 768;

		pawams->host_wx_fifo_size = wxfsiz;
		pawams->host_npewio_tx_fifo_size = nptxfsiz;
		pawams->host_pewio_tx_fifo_size = ptxfsiz;
	}

	/*
	 * If the summation of WX, NPTX and PTX fifo sizes is stiww
	 * biggew than the totaw_fifo_size, then we have a pwobwem.
	 *
	 * We won't be abwe to awwocate as many endpoints. Wight now,
	 * we'we just pwinting an ewwow message, but ideawwy this FIFO
	 * awwocation awgowithm wouwd be impwoved in the futuwe.
	 *
	 * FIXME impwove this FIFO awwocation awgowithm.
	 */
	if (unwikewy(totaw_fifo_size < (wxfsiz + nptxfsiz + ptxfsiz)))
		dev_eww(hsotg->dev, "invawid fifo sizes\n");
}

static void dwc2_config_fifos(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *pawams = &hsotg->pawams;
	u32 nptxfsiz, hptxfsiz, dfifocfg, gwxfsiz;

	if (!pawams->enabwe_dynamic_fifo)
		wetuwn;

	dwc2_cawcuwate_dynamic_fifo(hsotg);

	/* Wx FIFO */
	gwxfsiz = dwc2_weadw(hsotg, GWXFSIZ);
	dev_dbg(hsotg->dev, "initiaw gwxfsiz=%08x\n", gwxfsiz);
	gwxfsiz &= ~GWXFSIZ_DEPTH_MASK;
	gwxfsiz |= pawams->host_wx_fifo_size <<
		   GWXFSIZ_DEPTH_SHIFT & GWXFSIZ_DEPTH_MASK;
	dwc2_wwitew(hsotg, gwxfsiz, GWXFSIZ);
	dev_dbg(hsotg->dev, "new gwxfsiz=%08x\n",
		dwc2_weadw(hsotg, GWXFSIZ));

	/* Non-pewiodic Tx FIFO */
	dev_dbg(hsotg->dev, "initiaw gnptxfsiz=%08x\n",
		dwc2_weadw(hsotg, GNPTXFSIZ));
	nptxfsiz = pawams->host_npewio_tx_fifo_size <<
		   FIFOSIZE_DEPTH_SHIFT & FIFOSIZE_DEPTH_MASK;
	nptxfsiz |= pawams->host_wx_fifo_size <<
		    FIFOSIZE_STAWTADDW_SHIFT & FIFOSIZE_STAWTADDW_MASK;
	dwc2_wwitew(hsotg, nptxfsiz, GNPTXFSIZ);
	dev_dbg(hsotg->dev, "new gnptxfsiz=%08x\n",
		dwc2_weadw(hsotg, GNPTXFSIZ));

	/* Pewiodic Tx FIFO */
	dev_dbg(hsotg->dev, "initiaw hptxfsiz=%08x\n",
		dwc2_weadw(hsotg, HPTXFSIZ));
	hptxfsiz = pawams->host_pewio_tx_fifo_size <<
		   FIFOSIZE_DEPTH_SHIFT & FIFOSIZE_DEPTH_MASK;
	hptxfsiz |= (pawams->host_wx_fifo_size +
		     pawams->host_npewio_tx_fifo_size) <<
		    FIFOSIZE_STAWTADDW_SHIFT & FIFOSIZE_STAWTADDW_MASK;
	dwc2_wwitew(hsotg, hptxfsiz, HPTXFSIZ);
	dev_dbg(hsotg->dev, "new hptxfsiz=%08x\n",
		dwc2_weadw(hsotg, HPTXFSIZ));

	if (hsotg->pawams.en_muwtipwe_tx_fifo &&
	    hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_2_91a) {
		/*
		 * This featuwe was impwemented in 2.91a vewsion
		 * Gwobaw DFIFOCFG cawcuwation fow Host mode -
		 * incwude WxFIFO, NPTXFIFO and HPTXFIFO
		 */
		dfifocfg = dwc2_weadw(hsotg, GDFIFOCFG);
		dfifocfg &= ~GDFIFOCFG_EPINFOBASE_MASK;
		dfifocfg |= (pawams->host_wx_fifo_size +
			     pawams->host_npewio_tx_fifo_size +
			     pawams->host_pewio_tx_fifo_size) <<
			    GDFIFOCFG_EPINFOBASE_SHIFT &
			    GDFIFOCFG_EPINFOBASE_MASK;
		dwc2_wwitew(hsotg, dfifocfg, GDFIFOCFG);
	}
}

/**
 * dwc2_cawc_fwame_intewvaw() - Cawcuwates the cowwect fwame Intewvaw vawue fow
 * the HFIW wegistew accowding to PHY type and speed
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * NOTE: The cawwew can modify the vawue of the HFIW wegistew onwy aftew the
 * Powt Enabwe bit of the Host Powt Contwow and Status wegistew (HPWT.EnaPowt)
 * has been set
 */
u32 dwc2_cawc_fwame_intewvaw(stwuct dwc2_hsotg *hsotg)
{
	u32 usbcfg;
	u32 hpwt0;
	int cwock = 60;	/* defauwt vawue */

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);
	hpwt0 = dwc2_weadw(hsotg, HPWT0);

	if (!(usbcfg & GUSBCFG_PHYSEW) && (usbcfg & GUSBCFG_UWPI_UTMI_SEW) &&
	    !(usbcfg & GUSBCFG_PHYIF16))
		cwock = 60;
	if ((usbcfg & GUSBCFG_PHYSEW) && hsotg->hw_pawams.fs_phy_type ==
	    GHWCFG2_FS_PHY_TYPE_SHAWED_UWPI)
		cwock = 48;
	if (!(usbcfg & GUSBCFG_PHY_WP_CWK_SEW) && !(usbcfg & GUSBCFG_PHYSEW) &&
	    !(usbcfg & GUSBCFG_UWPI_UTMI_SEW) && (usbcfg & GUSBCFG_PHYIF16))
		cwock = 30;
	if (!(usbcfg & GUSBCFG_PHY_WP_CWK_SEW) && !(usbcfg & GUSBCFG_PHYSEW) &&
	    !(usbcfg & GUSBCFG_UWPI_UTMI_SEW) && !(usbcfg & GUSBCFG_PHYIF16))
		cwock = 60;
	if ((usbcfg & GUSBCFG_PHY_WP_CWK_SEW) && !(usbcfg & GUSBCFG_PHYSEW) &&
	    !(usbcfg & GUSBCFG_UWPI_UTMI_SEW) && (usbcfg & GUSBCFG_PHYIF16))
		cwock = 48;
	if ((usbcfg & GUSBCFG_PHYSEW) && !(usbcfg & GUSBCFG_PHYIF16) &&
	    hsotg->hw_pawams.fs_phy_type == GHWCFG2_FS_PHY_TYPE_SHAWED_UTMI)
		cwock = 48;
	if ((usbcfg & GUSBCFG_PHYSEW) &&
	    hsotg->hw_pawams.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED)
		cwock = 48;

	if ((hpwt0 & HPWT0_SPD_MASK) >> HPWT0_SPD_SHIFT == HPWT0_SPD_HIGH_SPEED)
		/* High speed case */
		wetuwn 125 * cwock - 1;

	/* FS/WS case */
	wetuwn 1000 * cwock - 1;
}

/**
 * dwc2_wead_packet() - Weads a packet fwom the Wx FIFO into the destination
 * buffew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @dest:    Destination buffew fow the packet
 * @bytes:   Numbew of bytes to copy to the destination
 */
void dwc2_wead_packet(stwuct dwc2_hsotg *hsotg, u8 *dest, u16 bytes)
{
	u32 *data_buf = (u32 *)dest;
	int wowd_count = (bytes + 3) / 4;
	int i;

	/*
	 * Todo: Account fow the case whewe dest is not dwowd awigned. This
	 * wequiwes weading data fwom the FIFO into a u32 temp buffew, then
	 * moving it into the data buffew.
	 */

	dev_vdbg(hsotg->dev, "%s(%p,%p,%d)\n", __func__, hsotg, dest, bytes);

	fow (i = 0; i < wowd_count; i++, data_buf++)
		*data_buf = dwc2_weadw(hsotg, HCFIFO(0));
}

/**
 * dwc2_dump_channew_info() - Pwints the state of a host channew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Pointew to the channew to dump
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 *
 * NOTE: This function wiww be wemoved once the pewiphewaw contwowwew code
 * is integwated and the dwivew is stabwe
 */
static void dwc2_dump_channew_info(stwuct dwc2_hsotg *hsotg,
				   stwuct dwc2_host_chan *chan)
{
#ifdef VEWBOSE_DEBUG
	int num_channews = hsotg->pawams.host_channews;
	stwuct dwc2_qh *qh;
	u32 hcchaw;
	u32 hcspwt;
	u32 hctsiz;
	u32 hc_dma;
	int i;

	if (!chan)
		wetuwn;

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));
	hcspwt = dwc2_weadw(hsotg, HCSPWT(chan->hc_num));
	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chan->hc_num));
	hc_dma = dwc2_weadw(hsotg, HCDMA(chan->hc_num));

	dev_dbg(hsotg->dev, "  Assigned to channew %p:\n", chan);
	dev_dbg(hsotg->dev, "    hcchaw 0x%08x, hcspwt 0x%08x\n",
		hcchaw, hcspwt);
	dev_dbg(hsotg->dev, "    hctsiz 0x%08x, hc_dma 0x%08x\n",
		hctsiz, hc_dma);
	dev_dbg(hsotg->dev, "    dev_addw: %d, ep_num: %d, ep_is_in: %d\n",
		chan->dev_addw, chan->ep_num, chan->ep_is_in);
	dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
	dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
	dev_dbg(hsotg->dev, "    data_pid_stawt: %d\n", chan->data_pid_stawt);
	dev_dbg(hsotg->dev, "    xfew_stawted: %d\n", chan->xfew_stawted);
	dev_dbg(hsotg->dev, "    hawt_status: %d\n", chan->hawt_status);
	dev_dbg(hsotg->dev, "    xfew_buf: %p\n", chan->xfew_buf);
	dev_dbg(hsotg->dev, "    xfew_dma: %08wx\n",
		(unsigned wong)chan->xfew_dma);
	dev_dbg(hsotg->dev, "    xfew_wen: %d\n", chan->xfew_wen);
	dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);
	dev_dbg(hsotg->dev, "  NP inactive sched:\n");
	wist_fow_each_entwy(qh, &hsotg->non_pewiodic_sched_inactive,
			    qh_wist_entwy)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP waiting sched:\n");
	wist_fow_each_entwy(qh, &hsotg->non_pewiodic_sched_waiting,
			    qh_wist_entwy)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP active sched:\n");
	wist_fow_each_entwy(qh, &hsotg->non_pewiodic_sched_active,
			    qh_wist_entwy)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  Channews:\n");
	fow (i = 0; i < num_channews; i++) {
		stwuct dwc2_host_chan *chan = hsotg->hc_ptw_awway[i];

		dev_dbg(hsotg->dev, "    %2d: %p\n", i, chan);
	}
#endif /* VEWBOSE_DEBUG */
}

static int _dwc2_hcd_stawt(stwuct usb_hcd *hcd);

static void dwc2_host_stawt(stwuct dwc2_hsotg *hsotg)
{
	stwuct usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	hcd->sewf.is_b_host = dwc2_hcd_is_b_host(hsotg);
	_dwc2_hcd_stawt(hcd);
}

static void dwc2_host_disconnect(stwuct dwc2_hsotg *hsotg)
{
	stwuct usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	hcd->sewf.is_b_host = 0;
}

static void dwc2_host_hub_info(stwuct dwc2_hsotg *hsotg, void *context,
			       int *hub_addw, int *hub_powt)
{
	stwuct uwb *uwb = context;

	if (uwb->dev->tt)
		*hub_addw = uwb->dev->tt->hub->devnum;
	ewse
		*hub_addw = 0;
	*hub_powt = uwb->dev->ttpowt;
}

/*
 * =========================================================================
 *  Wow Wevew Host Channew Access Functions
 * =========================================================================
 */

static void dwc2_hc_enabwe_swave_ints(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_host_chan *chan)
{
	u32 hcintmsk = HCINTMSK_CHHWTD;

	switch (chan->ep_type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
		dev_vdbg(hsotg->dev, "contwow/buwk\n");
		hcintmsk |= HCINTMSK_XFEWCOMPW;
		hcintmsk |= HCINTMSK_STAWW;
		hcintmsk |= HCINTMSK_XACTEWW;
		hcintmsk |= HCINTMSK_DATATGWEWW;
		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_BBWEWW;
		} ewse {
			hcintmsk |= HCINTMSK_NAK;
			hcintmsk |= HCINTMSK_NYET;
			if (chan->do_ping)
				hcintmsk |= HCINTMSK_ACK;
		}

		if (chan->do_spwit) {
			hcintmsk |= HCINTMSK_NAK;
			if (chan->compwete_spwit)
				hcintmsk |= HCINTMSK_NYET;
			ewse
				hcintmsk |= HCINTMSK_ACK;
		}

		if (chan->ewwow_state)
			hcintmsk |= HCINTMSK_ACK;
		bweak;

	case USB_ENDPOINT_XFEW_INT:
		if (dbg_pewio())
			dev_vdbg(hsotg->dev, "intw\n");
		hcintmsk |= HCINTMSK_XFEWCOMPW;
		hcintmsk |= HCINTMSK_NAK;
		hcintmsk |= HCINTMSK_STAWW;
		hcintmsk |= HCINTMSK_XACTEWW;
		hcintmsk |= HCINTMSK_DATATGWEWW;
		hcintmsk |= HCINTMSK_FWMOVWUN;

		if (chan->ep_is_in)
			hcintmsk |= HCINTMSK_BBWEWW;
		if (chan->ewwow_state)
			hcintmsk |= HCINTMSK_ACK;
		if (chan->do_spwit) {
			if (chan->compwete_spwit)
				hcintmsk |= HCINTMSK_NYET;
			ewse
				hcintmsk |= HCINTMSK_ACK;
		}
		bweak;

	case USB_ENDPOINT_XFEW_ISOC:
		if (dbg_pewio())
			dev_vdbg(hsotg->dev, "isoc\n");
		hcintmsk |= HCINTMSK_XFEWCOMPW;
		hcintmsk |= HCINTMSK_FWMOVWUN;
		hcintmsk |= HCINTMSK_ACK;

		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_XACTEWW;
			hcintmsk |= HCINTMSK_BBWEWW;
		}
		bweak;
	defauwt:
		dev_eww(hsotg->dev, "## Unknown EP type ##\n");
		bweak;
	}

	dwc2_wwitew(hsotg, hcintmsk, HCINTMSK(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcintmsk);
}

static void dwc2_hc_enabwe_dma_ints(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_host_chan *chan)
{
	u32 hcintmsk = HCINTMSK_CHHWTD;

	/*
	 * Fow Descwiptow DMA mode cowe hawts the channew on AHB ewwow.
	 * Intewwupt is not wequiwed.
	 */
	if (!hsotg->pawams.dma_desc_enabwe) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA disabwed\n");
		hcintmsk |= HCINTMSK_AHBEWW;
	} ewse {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA enabwed\n");
		if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
			hcintmsk |= HCINTMSK_XFEWCOMPW;
	}

	if (chan->ewwow_state && !chan->do_spwit &&
	    chan->ep_type != USB_ENDPOINT_XFEW_ISOC) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "setting ACK\n");
		hcintmsk |= HCINTMSK_ACK;
		if (chan->ep_is_in) {
			hcintmsk |= HCINTMSK_DATATGWEWW;
			if (chan->ep_type != USB_ENDPOINT_XFEW_INT)
				hcintmsk |= HCINTMSK_NAK;
		}
	}

	dwc2_wwitew(hsotg, hcintmsk, HCINTMSK(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HCINTMSK to %08x\n", hcintmsk);
}

static void dwc2_hc_enabwe_ints(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_host_chan *chan)
{
	u32 intmsk;

	if (hsotg->pawams.host_dma) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabwed\n");
		dwc2_hc_enabwe_dma_ints(hsotg, chan);
	} ewse {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA disabwed\n");
		dwc2_hc_enabwe_swave_ints(hsotg, chan);
	}

	/* Enabwe the top wevew host channew intewwupt */
	intmsk = dwc2_weadw(hsotg, HAINTMSK);
	intmsk |= 1 << chan->hc_num;
	dwc2_wwitew(hsotg, intmsk, HAINTMSK);
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HAINTMSK to %08x\n", intmsk);

	/* Make suwe host channew intewwupts awe enabwed */
	intmsk = dwc2_weadw(hsotg, GINTMSK);
	intmsk |= GINTSTS_HCHINT;
	dwc2_wwitew(hsotg, intmsk, GINTMSK);
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set GINTMSK to %08x\n", intmsk);
}

/**
 * dwc2_hc_init() - Pwepawes a host channew fow twansfewwing packets to/fwom
 * a specific endpoint
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew
 *
 * The HCCHAWn wegistew is set up with the chawactewistics specified in chan.
 * Host channew intewwupts that may need to be sewviced whiwe this twansfew is
 * in pwogwess awe enabwed.
 */
static void dwc2_hc_init(stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan)
{
	u8 hc_num = chan->hc_num;
	u32 hcintmsk;
	u32 hcchaw;
	u32 hcspwt = 0;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* Cweaw owd intewwupt conditions fow this host channew */
	hcintmsk = 0xffffffff;
	hcintmsk &= ~HCINTMSK_WESEWVED14_31;
	dwc2_wwitew(hsotg, hcintmsk, HCINT(hc_num));

	/* Enabwe channew intewwupts wequiwed fow this twansfew */
	dwc2_hc_enabwe_ints(hsotg, chan);

	/*
	 * Pwogwam the HCCHAWn wegistew with the endpoint chawactewistics fow
	 * the cuwwent twansfew
	 */
	hcchaw = chan->dev_addw << HCCHAW_DEVADDW_SHIFT & HCCHAW_DEVADDW_MASK;
	hcchaw |= chan->ep_num << HCCHAW_EPNUM_SHIFT & HCCHAW_EPNUM_MASK;
	if (chan->ep_is_in)
		hcchaw |= HCCHAW_EPDIW;
	if (chan->speed == USB_SPEED_WOW)
		hcchaw |= HCCHAW_WSPDDEV;
	hcchaw |= chan->ep_type << HCCHAW_EPTYPE_SHIFT & HCCHAW_EPTYPE_MASK;
	hcchaw |= chan->max_packet << HCCHAW_MPS_SHIFT & HCCHAW_MPS_MASK;
	dwc2_wwitew(hsotg, hcchaw, HCCHAW(hc_num));
	if (dbg_hc(chan)) {
		dev_vdbg(hsotg->dev, "set HCCHAW(%d) to %08x\n",
			 hc_num, hcchaw);

		dev_vdbg(hsotg->dev, "%s: Channew %d\n",
			 __func__, hc_num);
		dev_vdbg(hsotg->dev, "	 Dev Addw: %d\n",
			 chan->dev_addw);
		dev_vdbg(hsotg->dev, "	 Ep Num: %d\n",
			 chan->ep_num);
		dev_vdbg(hsotg->dev, "	 Is In: %d\n",
			 chan->ep_is_in);
		dev_vdbg(hsotg->dev, "	 Is Wow Speed: %d\n",
			 chan->speed == USB_SPEED_WOW);
		dev_vdbg(hsotg->dev, "	 Ep Type: %d\n",
			 chan->ep_type);
		dev_vdbg(hsotg->dev, "	 Max Pkt: %d\n",
			 chan->max_packet);
	}

	/* Pwogwam the HCSPWT wegistew fow SPWITs */
	if (chan->do_spwit) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev,
				 "Pwogwamming HC %d with spwit --> %s\n",
				 hc_num,
				 chan->compwete_spwit ? "CSPWIT" : "SSPWIT");
		if (chan->compwete_spwit)
			hcspwt |= HCSPWT_COMPSPWT;
		hcspwt |= chan->xact_pos << HCSPWT_XACTPOS_SHIFT &
			  HCSPWT_XACTPOS_MASK;
		hcspwt |= chan->hub_addw << HCSPWT_HUBADDW_SHIFT &
			  HCSPWT_HUBADDW_MASK;
		hcspwt |= chan->hub_powt << HCSPWT_PWTADDW_SHIFT &
			  HCSPWT_PWTADDW_MASK;
		if (dbg_hc(chan)) {
			dev_vdbg(hsotg->dev, "	  comp spwit %d\n",
				 chan->compwete_spwit);
			dev_vdbg(hsotg->dev, "	  xact pos %d\n",
				 chan->xact_pos);
			dev_vdbg(hsotg->dev, "	  hub addw %d\n",
				 chan->hub_addw);
			dev_vdbg(hsotg->dev, "	  hub powt %d\n",
				 chan->hub_powt);
			dev_vdbg(hsotg->dev, "	  is_in %d\n",
				 chan->ep_is_in);
			dev_vdbg(hsotg->dev, "	  Max Pkt %d\n",
				 chan->max_packet);
			dev_vdbg(hsotg->dev, "	  xfewwen %d\n",
				 chan->xfew_wen);
		}
	}

	dwc2_wwitew(hsotg, hcspwt, HCSPWT(hc_num));
}

/**
 * dwc2_hc_hawt() - Attempts to hawt a host channew
 *
 * @hsotg:       Contwowwew wegistew intewface
 * @chan:        Host channew to hawt
 * @hawt_status: Weason fow hawting the channew
 *
 * This function shouwd onwy be cawwed in Swave mode ow to abowt a twansfew in
 * eithew Swave mode ow DMA mode. Undew nowmaw ciwcumstances in DMA mode, the
 * contwowwew hawts the channew when the twansfew is compwete ow a condition
 * occuws that wequiwes appwication intewvention.
 *
 * In swave mode, checks fow a fwee wequest queue entwy, then sets the Channew
 * Enabwe and Channew Disabwe bits of the Host Channew Chawactewistics
 * wegistew of the specified channew to intiate the hawt. If thewe is no fwee
 * wequest queue entwy, sets onwy the Channew Disabwe bit of the HCCHAWn
 * wegistew to fwush wequests fow this channew. In the wattew case, sets a
 * fwag to indicate that the host channew needs to be hawted when a wequest
 * queue swot is open.
 *
 * In DMA mode, awways sets the Channew Enabwe and Channew Disabwe bits of the
 * HCCHAWn wegistew. The contwowwew ensuwes thewe is space in the wequest
 * queue befowe submitting the hawt wequest.
 *
 * Some time may ewapse befowe the cowe fwushes any posted wequests fow this
 * host channew and hawts. The Channew Hawted intewwupt handwew compwetes the
 * deactivation of the host channew.
 */
void dwc2_hc_hawt(stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan,
		  enum dwc2_hawt_status hawt_status)
{
	u32 nptxsts, hptxsts, hcchaw;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * In buffew DMA ow extewnaw DMA mode channew can't be hawted
	 * fow non-spwit pewiodic channews. At the end of the next
	 * ufwame/fwame (in the wowst case), the cowe genewates a channew
	 * hawted and disabwes the channew automaticawwy.
	 */
	if ((hsotg->pawams.g_dma && !hsotg->pawams.g_dma_desc) ||
	    hsotg->hw_pawams.awch == GHWCFG2_EXT_DMA_AWCH) {
		if (!chan->do_spwit &&
		    (chan->ep_type == USB_ENDPOINT_XFEW_ISOC ||
		     chan->ep_type == USB_ENDPOINT_XFEW_INT)) {
			dev_eww(hsotg->dev, "%s() Channew can't be hawted\n",
				__func__);
			wetuwn;
		}
	}

	if (hawt_status == DWC2_HC_XFEW_NO_HAWT_STATUS)
		dev_eww(hsotg->dev, "!!! hawt_status = %d !!!\n", hawt_status);

	if (hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE ||
	    hawt_status == DWC2_HC_XFEW_AHB_EWW) {
		/*
		 * Disabwe aww channew intewwupts except Ch Hawted. The QTD
		 * and QH state associated with this twansfew has been cweawed
		 * (in the case of UWB_DEQUEUE), so the channew needs to be
		 * shut down cawefuwwy to pwevent cwashes.
		 */
		u32 hcintmsk = HCINTMSK_CHHWTD;

		dev_vdbg(hsotg->dev, "dequeue/ewwow\n");
		dwc2_wwitew(hsotg, hcintmsk, HCINTMSK(chan->hc_num));

		/*
		 * Make suwe no othew intewwupts besides hawt awe cuwwentwy
		 * pending. Handwing anothew intewwupt couwd cause a cwash due
		 * to the QTD and QH state.
		 */
		dwc2_wwitew(hsotg, ~hcintmsk, HCINT(chan->hc_num));

		/*
		 * Make suwe the hawt status is set to UWB_DEQUEUE ow AHB_EWW
		 * even if the channew was awweady hawted fow some othew
		 * weason
		 */
		chan->hawt_status = hawt_status;

		hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));
		if (!(hcchaw & HCCHAW_CHENA)) {
			/*
			 * The channew is eithew awweady hawted ow it hasn't
			 * stawted yet. In DMA mode, the twansfew may hawt if
			 * it finishes nowmawwy ow a condition occuws that
			 * wequiwes dwivew intewvention. Don't want to hawt
			 * the channew again. In eithew Swave ow DMA mode,
			 * it's possibwe that the twansfew has been assigned
			 * to a channew, but not stawted yet when an UWB is
			 * dequeued. Don't want to hawt a channew that hasn't
			 * stawted yet.
			 */
			wetuwn;
		}
	}
	if (chan->hawt_pending) {
		/*
		 * A hawt has awweady been issued fow this channew. This might
		 * happen when a twansfew is abowted by a highew wevew in
		 * the stack.
		 */
		dev_vdbg(hsotg->dev,
			 "*** %s: Channew %d, chan->hawt_pending awweady set ***\n",
			 __func__, chan->hc_num);
		wetuwn;
	}

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));

	/* No need to set the bit in DDMA fow disabwing the channew */
	/* TODO check it evewywhewe channew is disabwed */
	if (!hsotg->pawams.dma_desc_enabwe) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "desc DMA disabwed\n");
		hcchaw |= HCCHAW_CHENA;
	} ewse {
		if (dbg_hc(chan))
			dev_dbg(hsotg->dev, "desc DMA enabwed\n");
	}
	hcchaw |= HCCHAW_CHDIS;

	if (!hsotg->pawams.host_dma) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA not enabwed\n");
		hcchaw |= HCCHAW_CHENA;

		/* Check fow space in the wequest queue to issue the hawt */
		if (chan->ep_type == USB_ENDPOINT_XFEW_CONTWOW ||
		    chan->ep_type == USB_ENDPOINT_XFEW_BUWK) {
			dev_vdbg(hsotg->dev, "contwow/buwk\n");
			nptxsts = dwc2_weadw(hsotg, GNPTXSTS);
			if ((nptxsts & TXSTS_QSPCAVAIW_MASK) == 0) {
				dev_vdbg(hsotg->dev, "Disabwing channew\n");
				hcchaw &= ~HCCHAW_CHENA;
			}
		} ewse {
			if (dbg_pewio())
				dev_vdbg(hsotg->dev, "isoc/intw\n");
			hptxsts = dwc2_weadw(hsotg, HPTXSTS);
			if ((hptxsts & TXSTS_QSPCAVAIW_MASK) == 0 ||
			    hsotg->queuing_high_bandwidth) {
				if (dbg_pewio())
					dev_vdbg(hsotg->dev, "Disabwing channew\n");
				hcchaw &= ~HCCHAW_CHENA;
			}
		}
	} ewse {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabwed\n");
	}

	dwc2_wwitew(hsotg, hcchaw, HCCHAW(chan->hc_num));
	chan->hawt_status = hawt_status;

	if (hcchaw & HCCHAW_CHENA) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Channew enabwed\n");
		chan->hawt_pending = 1;
		chan->hawt_on_queue = 0;
	} ewse {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Channew disabwed\n");
		chan->hawt_on_queue = 1;
	}

	if (dbg_hc(chan)) {
		dev_vdbg(hsotg->dev, "%s: Channew %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 hcchaw: 0x%08x\n",
			 hcchaw);
		dev_vdbg(hsotg->dev, "	 hawt_pending: %d\n",
			 chan->hawt_pending);
		dev_vdbg(hsotg->dev, "	 hawt_on_queue: %d\n",
			 chan->hawt_on_queue);
		dev_vdbg(hsotg->dev, "	 hawt_status: %d\n",
			 chan->hawt_status);
	}
}

/**
 * dwc2_hc_cweanup() - Cweaws the twansfew state fow a host channew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Identifies the host channew to cwean up
 *
 * This function is nowmawwy cawwed aftew a twansfew is done and the host
 * channew is being weweased
 */
void dwc2_hc_cweanup(stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan)
{
	u32 hcintmsk;

	chan->xfew_stawted = 0;

	wist_dew_init(&chan->spwit_owdew_wist_entwy);

	/*
	 * Cweaw channew intewwupt enabwes and any unhandwed channew intewwupt
	 * conditions
	 */
	dwc2_wwitew(hsotg, 0, HCINTMSK(chan->hc_num));
	hcintmsk = 0xffffffff;
	hcintmsk &= ~HCINTMSK_WESEWVED14_31;
	dwc2_wwitew(hsotg, hcintmsk, HCINT(chan->hc_num));
}

/**
 * dwc2_hc_set_even_odd_fwame() - Sets the channew pwopewty that indicates in
 * which fwame a pewiodic twansfew shouwd occuw
 *
 * @hsotg:  Pwogwamming view of DWC_otg contwowwew
 * @chan:   Identifies the host channew to set up and its pwopewties
 * @hcchaw: Cuwwent vawue of the HCCHAW wegistew fow the specified host channew
 *
 * This function has no effect on non-pewiodic twansfews
 */
static void dwc2_hc_set_even_odd_fwame(stwuct dwc2_hsotg *hsotg,
				       stwuct dwc2_host_chan *chan, u32 *hcchaw)
{
	if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
	    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
		int host_speed;
		int xfew_ns;
		int xfew_us;
		int bytes_in_fifo;
		u16 fifo_space;
		u16 fwame_numbew;
		u16 wiwe_fwame;

		/*
		 * Twy to figuwe out if we'we an even ow odd fwame. If we set
		 * even and the cuwwent fwame numbew is even the twansfew
		 * wiww happen immediatewy.  Simiwaw if both awe odd. If one is
		 * even and the othew is odd then the twansfew wiww happen when
		 * the fwame numbew ticks.
		 *
		 * Thewe's a bit of a bawancing act to get this wight.
		 * Sometimes we may want to send data in the cuwwent fwame (AK
		 * wight away).  We might want to do this if the fwame numbew
		 * _just_ ticked, but we might awso want to do this in owdew
		 * to continue a spwit twansaction that happened wate in a
		 * micwofwame (so we didn't know to queue the next twansfew
		 * untiw the fwame numbew had ticked).  The pwobwem is that we
		 * need a wot of knowwedge to know if thewe's actuawwy stiww
		 * time to send things ow if it wouwd be bettew to wait untiw
		 * the next fwame.
		 *
		 * We can wook at how much time is weft in the cuwwent fwame
		 * and make a guess about whethew we'ww have time to twansfew.
		 * We'ww do that.
		 */

		/* Get speed host is wunning at */
		host_speed = (chan->speed != USB_SPEED_HIGH &&
			      !chan->do_spwit) ? chan->speed : USB_SPEED_HIGH;

		/* See how many bytes awe in the pewiodic FIFO wight now */
		fifo_space = (dwc2_weadw(hsotg, HPTXSTS) &
			      TXSTS_FSPCAVAIW_MASK) >> TXSTS_FSPCAVAIW_SHIFT;
		bytes_in_fifo = sizeof(u32) *
				(hsotg->pawams.host_pewio_tx_fifo_size -
				 fifo_space);

		/*
		 * Woughwy estimate bus time fow evewything in the pewiodic
		 * queue + ouw new twansfew.  This is "wough" because we'we
		 * using a function that makes takes into account IN/OUT
		 * and INT/ISO and we'we just swamming in one vawue fow aww
		 * twansfews.  This shouwd be an ovew-estimate and that shouwd
		 * be OK, but we can pwobabwy tighten it.
		 */
		xfew_ns = usb_cawc_bus_time(host_speed, fawse, fawse,
					    chan->xfew_wen + bytes_in_fifo);
		xfew_us = NS_TO_US(xfew_ns);

		/* See what fwame numbew we'ww be at by the time we finish */
		fwame_numbew = dwc2_hcd_get_futuwe_fwame_numbew(hsotg, xfew_us);

		/* This is when we wewe scheduwed to be on the wiwe */
		wiwe_fwame = dwc2_fwame_num_inc(chan->qh->next_active_fwame, 1);

		/*
		 * If we'd finish _aftew_ the fwame we'we scheduwed in then
		 * it's hopewess.  Just scheduwe wight away and hope fow the
		 * best.  Note that it _might_ be wise to caww back into the
		 * scheduwew to pick a bettew fwame, but this is bettew than
		 * nothing.
		 */
		if (dwc2_fwame_num_gt(fwame_numbew, wiwe_fwame)) {
			dwc2_sch_vdbg(hsotg,
				      "QH=%p EO MISS fw=%04x=>%04x (%+d)\n",
				      chan->qh, wiwe_fwame, fwame_numbew,
				      dwc2_fwame_num_dec(fwame_numbew,
							 wiwe_fwame));
			wiwe_fwame = fwame_numbew;

			/*
			 * We picked a diffewent fwame numbew; communicate this
			 * back to the scheduwew so it doesn't twy to scheduwe
			 * anothew in the same fwame.
			 *
			 * Wemembew that next_active_fwame is 1 befowe the wiwe
			 * fwame.
			 */
			chan->qh->next_active_fwame =
				dwc2_fwame_num_dec(fwame_numbew, 1);
		}

		if (wiwe_fwame & 1)
			*hcchaw |= HCCHAW_ODDFWM;
		ewse
			*hcchaw &= ~HCCHAW_ODDFWM;
	}
}

static void dwc2_set_pid_isoc(stwuct dwc2_host_chan *chan)
{
	/* Set up the initiaw PID fow the twansfew */
	if (chan->speed == USB_SPEED_HIGH) {
		if (chan->ep_is_in) {
			if (chan->muwti_count == 1)
				chan->data_pid_stawt = DWC2_HC_PID_DATA0;
			ewse if (chan->muwti_count == 2)
				chan->data_pid_stawt = DWC2_HC_PID_DATA1;
			ewse
				chan->data_pid_stawt = DWC2_HC_PID_DATA2;
		} ewse {
			if (chan->muwti_count == 1)
				chan->data_pid_stawt = DWC2_HC_PID_DATA0;
			ewse
				chan->data_pid_stawt = DWC2_HC_PID_MDATA;
		}
	} ewse {
		chan->data_pid_stawt = DWC2_HC_PID_DATA0;
	}
}

/**
 * dwc2_hc_wwite_packet() - Wwites a packet into the Tx FIFO associated with
 * the Host Channew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew
 *
 * This function shouwd onwy be cawwed in Swave mode. Fow a channew associated
 * with a non-pewiodic EP, the non-pewiodic Tx FIFO is wwitten. Fow a channew
 * associated with a pewiodic EP, the pewiodic Tx FIFO is wwitten.
 *
 * Upon wetuwn the xfew_buf and xfew_count fiewds in chan awe incwemented by
 * the numbew of bytes wwitten to the Tx FIFO.
 */
static void dwc2_hc_wwite_packet(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan)
{
	u32 i;
	u32 wemaining_count;
	u32 byte_count;
	u32 dwowd_count;
	u32 *data_buf = (u32 *)chan->xfew_buf;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	wemaining_count = chan->xfew_wen - chan->xfew_count;
	if (wemaining_count > chan->max_packet)
		byte_count = chan->max_packet;
	ewse
		byte_count = wemaining_count;

	dwowd_count = (byte_count + 3) / 4;

	if (((unsigned wong)data_buf & 0x3) == 0) {
		/* xfew_buf is DWOWD awigned */
		fow (i = 0; i < dwowd_count; i++, data_buf++)
			dwc2_wwitew(hsotg, *data_buf, HCFIFO(chan->hc_num));
	} ewse {
		/* xfew_buf is not DWOWD awigned */
		fow (i = 0; i < dwowd_count; i++, data_buf++) {
			u32 data = data_buf[0] | data_buf[1] << 8 |
				   data_buf[2] << 16 | data_buf[3] << 24;
			dwc2_wwitew(hsotg, data, HCFIFO(chan->hc_num));
		}
	}

	chan->xfew_count += byte_count;
	chan->xfew_buf += byte_count;
}

/**
 * dwc2_hc_do_ping() - Stawts a PING twansfew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew
 *
 * This function shouwd onwy be cawwed in Swave mode. The Do Ping bit is set in
 * the HCTSIZ wegistew, then the channew is enabwed.
 */
static void dwc2_hc_do_ping(stwuct dwc2_hsotg *hsotg,
			    stwuct dwc2_host_chan *chan)
{
	u32 hcchaw;
	u32 hctsiz;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s: Channew %d\n", __func__,
			 chan->hc_num);

	hctsiz = TSIZ_DOPNG;
	hctsiz |= 1 << TSIZ_PKTCNT_SHIFT;
	dwc2_wwitew(hsotg, hctsiz, HCTSIZ(chan->hc_num));

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));
	hcchaw |= HCCHAW_CHENA;
	hcchaw &= ~HCCHAW_CHDIS;
	dwc2_wwitew(hsotg, hcchaw, HCCHAW(chan->hc_num));
}

/**
 * dwc2_hc_stawt_twansfew() - Does the setup fow a data twansfew fow a host
 * channew and stawts the twansfew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew. The xfew_wen vawue
 *         may be weduced to accommodate the max widths of the XfewSize and
 *         PktCnt fiewds in the HCTSIZn wegistew. The muwti_count vawue may be
 *         changed to wefwect the finaw xfew_wen vawue.
 *
 * This function may be cawwed in eithew Swave mode ow DMA mode. In Swave mode,
 * the cawwew must ensuwe that thewe is sufficient space in the wequest queue
 * and Tx Data FIFO.
 *
 * Fow an OUT twansfew in Swave mode, it woads a data packet into the
 * appwopwiate FIFO. If necessawy, additionaw data packets awe woaded in the
 * Host ISW.
 *
 * Fow an IN twansfew in Swave mode, a data packet is wequested. The data
 * packets awe unwoaded fwom the Wx FIFO in the Host ISW. If necessawy,
 * additionaw data packets awe wequested in the Host ISW.
 *
 * Fow a PING twansfew in Swave mode, the Do Ping bit is set in the HCTSIZ
 * wegistew awong with a packet count of 1 and the channew is enabwed. This
 * causes a singwe PING twansaction to occuw. Othew fiewds in HCTSIZ awe
 * simpwy set to 0 since no data twansfew occuws in this case.
 *
 * Fow a PING twansfew in DMA mode, the HCTSIZ wegistew is initiawized with
 * aww the infowmation wequiwed to pewfowm the subsequent data twansfew. In
 * addition, the Do Ping bit is set in the HCTSIZ wegistew. In this case, the
 * contwowwew pewfowms the entiwe PING pwotocow, then stawts the data
 * twansfew.
 */
static void dwc2_hc_stawt_twansfew(stwuct dwc2_hsotg *hsotg,
				   stwuct dwc2_host_chan *chan)
{
	u32 max_hc_xfew_size = hsotg->pawams.max_twansfew_size;
	u16 max_hc_pkt_count = hsotg->pawams.max_packet_count;
	u32 hcchaw;
	u32 hctsiz = 0;
	u16 num_packets;
	u32 ec_mc;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (chan->do_ping) {
		if (!hsotg->pawams.host_dma) {
			if (dbg_hc(chan))
				dev_vdbg(hsotg->dev, "ping, no DMA\n");
			dwc2_hc_do_ping(hsotg, chan);
			chan->xfew_stawted = 1;
			wetuwn;
		}

		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "ping, DMA\n");

		hctsiz |= TSIZ_DOPNG;
	}

	if (chan->do_spwit) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "spwit\n");
		num_packets = 1;

		if (chan->compwete_spwit && !chan->ep_is_in)
			/*
			 * Fow CSPWIT OUT Twansfew, set the size to 0 so the
			 * cowe doesn't expect any data wwitten to the FIFO
			 */
			chan->xfew_wen = 0;
		ewse if (chan->ep_is_in || chan->xfew_wen > chan->max_packet)
			chan->xfew_wen = chan->max_packet;
		ewse if (!chan->ep_is_in && chan->xfew_wen > 188)
			chan->xfew_wen = 188;

		hctsiz |= chan->xfew_wen << TSIZ_XFEWSIZE_SHIFT &
			  TSIZ_XFEWSIZE_MASK;

		/* Fow spwit set ec_mc fow immediate wetwies */
		if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
			ec_mc = 3;
		ewse
			ec_mc = 1;
	} ewse {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "no spwit\n");
		/*
		 * Ensuwe that the twansfew wength and packet count wiww fit
		 * in the widths awwocated fow them in the HCTSIZn wegistew
		 */
		if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
			/*
			 * Make suwe the twansfew size is no wawgew than one
			 * (micwo)fwame's wowth of data. (A check was done
			 * when the pewiodic twansfew was accepted to ensuwe
			 * that a (micwo)fwame's wowth of data can be
			 * pwogwammed into a channew.)
			 */
			u32 max_pewiodic_wen =
				chan->muwti_count * chan->max_packet;

			if (chan->xfew_wen > max_pewiodic_wen)
				chan->xfew_wen = max_pewiodic_wen;
		} ewse if (chan->xfew_wen > max_hc_xfew_size) {
			/*
			 * Make suwe that xfew_wen is a muwtipwe of max packet
			 * size
			 */
			chan->xfew_wen =
				max_hc_xfew_size - chan->max_packet + 1;
		}

		if (chan->xfew_wen > 0) {
			num_packets = (chan->xfew_wen + chan->max_packet - 1) /
					chan->max_packet;
			if (num_packets > max_hc_pkt_count) {
				num_packets = max_hc_pkt_count;
				chan->xfew_wen = num_packets * chan->max_packet;
			} ewse if (chan->ep_is_in) {
				/*
				 * Awways pwogwam an integwaw # of max packets
				 * fow IN twansfews.
				 * Note: This assumes that the input buffew is
				 * awigned and sized accowdingwy.
				 */
				chan->xfew_wen = num_packets * chan->max_packet;
			}
		} ewse {
			/* Need 1 packet fow twansfew wength of 0 */
			num_packets = 1;
		}

		if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
			/*
			 * Make suwe that the muwti_count fiewd matches the
			 * actuaw twansfew wength
			 */
			chan->muwti_count = num_packets;

		if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
			dwc2_set_pid_isoc(chan);

		hctsiz |= chan->xfew_wen << TSIZ_XFEWSIZE_SHIFT &
			  TSIZ_XFEWSIZE_MASK;

		/* The ec_mc gets the muwti_count fow non-spwit */
		ec_mc = chan->muwti_count;
	}

	chan->stawt_pkt_count = num_packets;
	hctsiz |= num_packets << TSIZ_PKTCNT_SHIFT & TSIZ_PKTCNT_MASK;
	hctsiz |= chan->data_pid_stawt << TSIZ_SC_MC_PID_SHIFT &
		  TSIZ_SC_MC_PID_MASK;
	dwc2_wwitew(hsotg, hctsiz, HCTSIZ(chan->hc_num));
	if (dbg_hc(chan)) {
		dev_vdbg(hsotg->dev, "Wwote %08x to HCTSIZ(%d)\n",
			 hctsiz, chan->hc_num);

		dev_vdbg(hsotg->dev, "%s: Channew %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 Xfew Size: %d\n",
			 (hctsiz & TSIZ_XFEWSIZE_MASK) >>
			 TSIZ_XFEWSIZE_SHIFT);
		dev_vdbg(hsotg->dev, "	 Num Pkts: %d\n",
			 (hctsiz & TSIZ_PKTCNT_MASK) >>
			 TSIZ_PKTCNT_SHIFT);
		dev_vdbg(hsotg->dev, "	 Stawt PID: %d\n",
			 (hctsiz & TSIZ_SC_MC_PID_MASK) >>
			 TSIZ_SC_MC_PID_SHIFT);
	}

	if (hsotg->pawams.host_dma) {
		dma_addw_t dma_addw;

		if (chan->awign_buf) {
			if (dbg_hc(chan))
				dev_vdbg(hsotg->dev, "awign_buf\n");
			dma_addw = chan->awign_buf;
		} ewse {
			dma_addw = chan->xfew_dma;
		}
		dwc2_wwitew(hsotg, (u32)dma_addw, HCDMA(chan->hc_num));

		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "Wwote %08wx to HCDMA(%d)\n",
				 (unsigned wong)dma_addw, chan->hc_num);
	}

	/* Stawt the spwit */
	if (chan->do_spwit) {
		u32 hcspwt = dwc2_weadw(hsotg, HCSPWT(chan->hc_num));

		hcspwt |= HCSPWT_SPWTENA;
		dwc2_wwitew(hsotg, hcspwt, HCSPWT(chan->hc_num));
	}

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));
	hcchaw &= ~HCCHAW_MUWTICNT_MASK;
	hcchaw |= (ec_mc << HCCHAW_MUWTICNT_SHIFT) & HCCHAW_MUWTICNT_MASK;
	dwc2_hc_set_even_odd_fwame(hsotg, chan, &hcchaw);

	if (hcchaw & HCCHAW_CHDIS)
		dev_wawn(hsotg->dev,
			 "%s: chdis set, channew %d, hcchaw 0x%08x\n",
			 __func__, chan->hc_num, hcchaw);

	/* Set host channew enabwe aftew aww othew setup is compwete */
	hcchaw |= HCCHAW_CHENA;
	hcchaw &= ~HCCHAW_CHDIS;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "	 Muwti Cnt: %d\n",
			 (hcchaw & HCCHAW_MUWTICNT_MASK) >>
			 HCCHAW_MUWTICNT_SHIFT);

	dwc2_wwitew(hsotg, hcchaw, HCCHAW(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wwote %08x to HCCHAW(%d)\n", hcchaw,
			 chan->hc_num);

	chan->xfew_stawted = 1;
	chan->wequests++;

	if (!hsotg->pawams.host_dma &&
	    !chan->ep_is_in && chan->xfew_wen > 0)
		/* Woad OUT packet into the appwopwiate Tx FIFO */
		dwc2_hc_wwite_packet(hsotg, chan);
}

/**
 * dwc2_hc_stawt_twansfew_ddma() - Does the setup fow a data twansfew fow a
 * host channew and stawts the twansfew in Descwiptow DMA mode
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew
 *
 * Initiawizes HCTSIZ wegistew. Fow a PING twansfew the Do Ping bit is set.
 * Sets PID and NTD vawues. Fow pewiodic twansfews initiawizes SCHED_INFO fiewd
 * with micwo-fwame bitmap.
 *
 * Initiawizes HCDMA wegistew with descwiptow wist addwess and CTD vawue then
 * stawts the twansfew via enabwing the channew.
 */
void dwc2_hc_stawt_twansfew_ddma(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan)
{
	u32 hcchaw;
	u32 hctsiz = 0;

	if (chan->do_ping)
		hctsiz |= TSIZ_DOPNG;

	if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
		dwc2_set_pid_isoc(chan);

	/* Packet Count and Xfew Size awe not used in Descwiptow DMA mode */
	hctsiz |= chan->data_pid_stawt << TSIZ_SC_MC_PID_SHIFT &
		  TSIZ_SC_MC_PID_MASK;

	/* 0 - 1 descwiptow, 1 - 2 descwiptows, etc */
	hctsiz |= (chan->ntd - 1) << TSIZ_NTD_SHIFT & TSIZ_NTD_MASK;

	/* Non-zewo onwy fow high-speed intewwupt endpoints */
	hctsiz |= chan->schinfo << TSIZ_SCHINFO_SHIFT & TSIZ_SCHINFO_MASK;

	if (dbg_hc(chan)) {
		dev_vdbg(hsotg->dev, "%s: Channew %d\n", __func__,
			 chan->hc_num);
		dev_vdbg(hsotg->dev, "	 Stawt PID: %d\n",
			 chan->data_pid_stawt);
		dev_vdbg(hsotg->dev, "	 NTD: %d\n", chan->ntd - 1);
	}

	dwc2_wwitew(hsotg, hctsiz, HCTSIZ(chan->hc_num));

	dma_sync_singwe_fow_device(hsotg->dev, chan->desc_wist_addw,
				   chan->desc_wist_sz, DMA_TO_DEVICE);

	dwc2_wwitew(hsotg, chan->desc_wist_addw, HCDMA(chan->hc_num));

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wwote %pad to HCDMA(%d)\n",
			 &chan->desc_wist_addw, chan->hc_num);

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));
	hcchaw &= ~HCCHAW_MUWTICNT_MASK;
	hcchaw |= chan->muwti_count << HCCHAW_MUWTICNT_SHIFT &
		  HCCHAW_MUWTICNT_MASK;

	if (hcchaw & HCCHAW_CHDIS)
		dev_wawn(hsotg->dev,
			 "%s: chdis set, channew %d, hcchaw 0x%08x\n",
			 __func__, chan->hc_num, hcchaw);

	/* Set host channew enabwe aftew aww othew setup is compwete */
	hcchaw |= HCCHAW_CHENA;
	hcchaw &= ~HCCHAW_CHDIS;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "	 Muwti Cnt: %d\n",
			 (hcchaw & HCCHAW_MUWTICNT_MASK) >>
			 HCCHAW_MUWTICNT_SHIFT);

	dwc2_wwitew(hsotg, hcchaw, HCCHAW(chan->hc_num));
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "Wwote %08x to HCCHAW(%d)\n", hcchaw,
			 chan->hc_num);

	chan->xfew_stawted = 1;
	chan->wequests++;
}

/**
 * dwc2_hc_continue_twansfew() - Continues a data twansfew that was stawted by
 * a pwevious caww to dwc2_hc_stawt_twansfew()
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @chan:  Infowmation needed to initiawize the host channew
 *
 * The cawwew must ensuwe thewe is sufficient space in the wequest queue and Tx
 * Data FIFO. This function shouwd onwy be cawwed in Swave mode. In DMA mode,
 * the contwowwew acts autonomouswy to compwete twansfews pwogwammed to a host
 * channew.
 *
 * Fow an OUT twansfew, a new data packet is woaded into the appwopwiate FIFO
 * if thewe is any data wemaining to be queued. Fow an IN twansfew, anothew
 * data packet is awways wequested. Fow the SETUP phase of a contwow twansfew,
 * this function does nothing.
 *
 * Wetuwn: 1 if a new wequest is queued, 0 if no mowe wequests awe wequiwed
 * fow this twansfew
 */
static int dwc2_hc_continue_twansfew(stwuct dwc2_hsotg *hsotg,
				     stwuct dwc2_host_chan *chan)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s: Channew %d\n", __func__,
			 chan->hc_num);

	if (chan->do_spwit)
		/* SPWITs awways queue just once pew channew */
		wetuwn 0;

	if (chan->data_pid_stawt == DWC2_HC_PID_SETUP)
		/* SETUPs awe queued onwy once since they can't be NAK'd */
		wetuwn 0;

	if (chan->ep_is_in) {
		/*
		 * Awways queue anothew wequest fow othew IN twansfews. If
		 * back-to-back INs awe issued and NAKs awe weceived fow both,
		 * the dwivew may stiww be pwocessing the fiwst NAK when the
		 * second NAK is weceived. When the intewwupt handwew cweaws
		 * the NAK intewwupt fow the fiwst NAK, the second NAK wiww
		 * not be seen. So we can't depend on the NAK intewwupt
		 * handwew to wequeue a NAK'd wequest. Instead, IN wequests
		 * awe issued each time this function is cawwed. When the
		 * twansfew compwetes, the extwa wequests fow the channew wiww
		 * be fwushed.
		 */
		u32 hcchaw = dwc2_weadw(hsotg, HCCHAW(chan->hc_num));

		dwc2_hc_set_even_odd_fwame(hsotg, chan, &hcchaw);
		hcchaw |= HCCHAW_CHENA;
		hcchaw &= ~HCCHAW_CHDIS;
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "	 IN xfew: hcchaw = 0x%08x\n",
				 hcchaw);
		dwc2_wwitew(hsotg, hcchaw, HCCHAW(chan->hc_num));
		chan->wequests++;
		wetuwn 1;
	}

	/* OUT twansfews */

	if (chan->xfew_count < chan->xfew_wen) {
		if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
			u32 hcchaw = dwc2_weadw(hsotg,
						HCCHAW(chan->hc_num));

			dwc2_hc_set_even_odd_fwame(hsotg, chan,
						   &hcchaw);
		}

		/* Woad OUT packet into the appwopwiate Tx FIFO */
		dwc2_hc_wwite_packet(hsotg, chan);
		chan->wequests++;
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * =========================================================================
 *  HCD
 * =========================================================================
 */

/*
 * Pwocesses aww the UWBs in a singwe wist of QHs. Compwetes them with
 * -ETIMEDOUT and fwees the QTD.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static void dwc2_kiww_uwbs_in_qh_wist(stwuct dwc2_hsotg *hsotg,
				      stwuct wist_head *qh_wist)
{
	stwuct dwc2_qh *qh, *qh_tmp;
	stwuct dwc2_qtd *qtd, *qtd_tmp;

	wist_fow_each_entwy_safe(qh, qh_tmp, qh_wist, qh_wist_entwy) {
		wist_fow_each_entwy_safe(qtd, qtd_tmp, &qh->qtd_wist,
					 qtd_wist_entwy) {
			dwc2_host_compwete(hsotg, qtd, -ECONNWESET);
			dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);
		}
	}
}

static void dwc2_qh_wist_fwee(stwuct dwc2_hsotg *hsotg,
			      stwuct wist_head *qh_wist)
{
	stwuct dwc2_qtd *qtd, *qtd_tmp;
	stwuct dwc2_qh *qh, *qh_tmp;
	unsigned wong fwags;

	if (!qh_wist->next)
		/* The wist hasn't been initiawized yet */
		wetuwn;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	/* Ensuwe thewe awe no QTDs ow UWBs weft */
	dwc2_kiww_uwbs_in_qh_wist(hsotg, qh_wist);

	wist_fow_each_entwy_safe(qh, qh_tmp, qh_wist, qh_wist_entwy) {
		dwc2_hcd_qh_unwink(hsotg, qh);

		/* Fwee each QTD in the QH's QTD wist */
		wist_fow_each_entwy_safe(qtd, qtd_tmp, &qh->qtd_wist,
					 qtd_wist_entwy)
			dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);

		if (qh->channew && qh->channew->qh == qh)
			qh->channew->qh = NUWW;

		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		dwc2_hcd_qh_fwee(hsotg, qh);
		spin_wock_iwqsave(&hsotg->wock, fwags);
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

/*
 * Wesponds with an ewwow status of -ETIMEDOUT to aww UWBs in the non-pewiodic
 * and pewiodic scheduwes. The QTD associated with each UWB is wemoved fwom
 * the scheduwe and fweed. This function may be cawwed when a disconnect is
 * detected ow when the HCD is being stopped.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static void dwc2_kiww_aww_uwbs(stwuct dwc2_hsotg *hsotg)
{
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->non_pewiodic_sched_inactive);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->non_pewiodic_sched_waiting);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->non_pewiodic_sched_active);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->pewiodic_sched_inactive);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->pewiodic_sched_weady);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->pewiodic_sched_assigned);
	dwc2_kiww_uwbs_in_qh_wist(hsotg, &hsotg->pewiodic_sched_queued);
}

/**
 * dwc2_hcd_stawt() - Stawts the HCD when switching to Host mode
 *
 * @hsotg: Pointew to stwuct dwc2_hsotg
 */
void dwc2_hcd_stawt(stwuct dwc2_hsotg *hsotg)
{
	u32 hpwt0;

	if (hsotg->op_state == OTG_STATE_B_HOST) {
		/*
		 * Weset the powt. Duwing a HNP mode switch the weset
		 * needs to occuw within 1ms and have a duwation of at
		 * weast 50ms.
		 */
		hpwt0 = dwc2_wead_hpwt0(hsotg);
		hpwt0 |= HPWT0_WST;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);
	}

	queue_dewayed_wowk(hsotg->wq_otg, &hsotg->stawt_wowk,
			   msecs_to_jiffies(50));
}

/* Must be cawwed with intewwupt disabwed and spinwock hewd */
static void dwc2_hcd_cweanup_channews(stwuct dwc2_hsotg *hsotg)
{
	int num_channews = hsotg->pawams.host_channews;
	stwuct dwc2_host_chan *channew;
	u32 hcchaw;
	int i;

	if (!hsotg->pawams.host_dma) {
		/* Fwush out any channew wequests in swave mode */
		fow (i = 0; i < num_channews; i++) {
			channew = hsotg->hc_ptw_awway[i];
			if (!wist_empty(&channew->hc_wist_entwy))
				continue;
			hcchaw = dwc2_weadw(hsotg, HCCHAW(i));
			if (hcchaw & HCCHAW_CHENA) {
				hcchaw &= ~(HCCHAW_CHENA | HCCHAW_EPDIW);
				hcchaw |= HCCHAW_CHDIS;
				dwc2_wwitew(hsotg, hcchaw, HCCHAW(i));
			}
		}
	}

	fow (i = 0; i < num_channews; i++) {
		channew = hsotg->hc_ptw_awway[i];
		if (!wist_empty(&channew->hc_wist_entwy))
			continue;
		hcchaw = dwc2_weadw(hsotg, HCCHAW(i));
		if (hcchaw & HCCHAW_CHENA) {
			/* Hawt the channew */
			hcchaw |= HCCHAW_CHDIS;
			dwc2_wwitew(hsotg, hcchaw, HCCHAW(i));
		}

		dwc2_hc_cweanup(hsotg, channew);
		wist_add_taiw(&channew->hc_wist_entwy, &hsotg->fwee_hc_wist);
		/*
		 * Added fow Descwiptow DMA to pwevent channew doubwe cweanup in
		 * wewease_channew_ddma(), which is cawwed fwom ep_disabwe when
		 * device disconnects
		 */
		channew->qh = NUWW;
	}
	/* Aww channews have been fweed, mawk them avaiwabwe */
	if (hsotg->pawams.ufwame_sched) {
		hsotg->avaiwabwe_host_channews =
			hsotg->pawams.host_channews;
	} ewse {
		hsotg->non_pewiodic_channews = 0;
		hsotg->pewiodic_channews = 0;
	}
}

/**
 * dwc2_hcd_connect() - Handwes connect of the HCD
 *
 * @hsotg: Pointew to stwuct dwc2_hsotg
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
void dwc2_hcd_connect(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->wx_state != DWC2_W0)
		usb_hcd_wesume_woot_hub(hsotg->pwiv);

	hsotg->fwags.b.powt_connect_status_change = 1;
	hsotg->fwags.b.powt_connect_status = 1;
}

/**
 * dwc2_hcd_disconnect() - Handwes disconnect of the HCD
 *
 * @hsotg: Pointew to stwuct dwc2_hsotg
 * @fowce: If twue, we won't twy to weconnect even if we see device connected.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
void dwc2_hcd_disconnect(stwuct dwc2_hsotg *hsotg, boow fowce)
{
	u32 intw;
	u32 hpwt0;

	/* Set status fwags fow the hub dwivew */
	hsotg->fwags.b.powt_connect_status_change = 1;
	hsotg->fwags.b.powt_connect_status = 0;

	/*
	 * Shutdown any twansfews in pwocess by cweawing the Tx FIFO Empty
	 * intewwupt mask and status bits and disabwing subsequent host
	 * channew intewwupts.
	 */
	intw = dwc2_weadw(hsotg, GINTMSK);
	intw &= ~(GINTSTS_NPTXFEMP | GINTSTS_PTXFEMP | GINTSTS_HCHINT);
	dwc2_wwitew(hsotg, intw, GINTMSK);
	intw = GINTSTS_NPTXFEMP | GINTSTS_PTXFEMP | GINTSTS_HCHINT;
	dwc2_wwitew(hsotg, intw, GINTSTS);

	/*
	 * Tuwn off the vbus powew onwy if the cowe has twansitioned to device
	 * mode. If stiww in host mode, need to keep powew on to detect a
	 * weconnection.
	 */
	if (dwc2_is_device_mode(hsotg)) {
		if (hsotg->op_state != OTG_STATE_A_SUSPEND) {
			dev_dbg(hsotg->dev, "Disconnect: PowtPowew off\n");
			dwc2_wwitew(hsotg, 0, HPWT0);
		}

		dwc2_disabwe_host_intewwupts(hsotg);
	}

	/* Wespond with an ewwow status to aww UWBs in the scheduwe */
	dwc2_kiww_aww_uwbs(hsotg);

	if (dwc2_is_host_mode(hsotg))
		/* Cwean up any host channews that wewe in use */
		dwc2_hcd_cweanup_channews(hsotg);

	dwc2_host_disconnect(hsotg);

	/*
	 * Add an extwa check hewe to see if we'we actuawwy connected but
	 * we don't have a detection intewwupt pending.  This can happen if:
	 *   1. hawdwawe sees connect
	 *   2. hawdwawe sees disconnect
	 *   3. hawdwawe sees connect
	 *   4. dwc2_powt_intw() - cweaws connect intewwupt
	 *   5. dwc2_handwe_common_intw() - cawws hewe
	 *
	 * Without the extwa check hewe we wiww end cawwing disconnect
	 * and won't get any futuwe intewwupts to handwe the connect.
	 */
	if (!fowce) {
		hpwt0 = dwc2_weadw(hsotg, HPWT0);
		if (!(hpwt0 & HPWT0_CONNDET) && (hpwt0 & HPWT0_CONNSTS))
			dwc2_hcd_connect(hsotg);
	}
}

/**
 * dwc2_hcd_wem_wakeup() - Handwes Wemote Wakeup
 *
 * @hsotg: Pointew to stwuct dwc2_hsotg
 */
static void dwc2_hcd_wem_wakeup(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->bus_suspended) {
		hsotg->fwags.b.powt_suspend_change = 1;
		usb_hcd_wesume_woot_hub(hsotg->pwiv);
	}

	if (hsotg->wx_state == DWC2_W1)
		hsotg->fwags.b.powt_w1_change = 1;
}

/**
 * dwc2_hcd_stop() - Hawts the DWC_otg host mode opewations in a cwean mannew
 *
 * @hsotg: Pointew to stwuct dwc2_hsotg
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
void dwc2_hcd_stop(stwuct dwc2_hsotg *hsotg)
{
	dev_dbg(hsotg->dev, "DWC OTG HCD STOP\n");

	/*
	 * The woot hub shouwd be disconnected befowe this function is cawwed.
	 * The disconnect wiww cweaw the QTD wists (via ..._hcd_uwb_dequeue)
	 * and the QH wists (via ..._hcd_endpoint_disabwe).
	 */

	/* Tuwn off aww host-specific intewwupts */
	dwc2_disabwe_host_intewwupts(hsotg);

	/* Tuwn off the vbus powew */
	dev_dbg(hsotg->dev, "PowtPowew off\n");
	dwc2_wwitew(hsotg, 0, HPWT0);
}

/* Cawwew must howd dwivew wock */
static int dwc2_hcd_uwb_enqueue(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_hcd_uwb *uwb, stwuct dwc2_qh *qh,
				stwuct dwc2_qtd *qtd)
{
	u32 intw_mask;
	int wetvaw;
	int dev_speed;

	if (!hsotg->fwags.b.powt_connect_status) {
		/* No wongew connected */
		dev_eww(hsotg->dev, "Not connected\n");
		wetuwn -ENODEV;
	}

	dev_speed = dwc2_host_get_speed(hsotg, uwb->pwiv);

	/* Some configuwations cannot suppowt WS twaffic on a FS woot powt */
	if ((dev_speed == USB_SPEED_WOW) &&
	    (hsotg->hw_pawams.fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED) &&
	    (hsotg->hw_pawams.hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI)) {
		u32 hpwt0 = dwc2_weadw(hsotg, HPWT0);
		u32 pwtspd = (hpwt0 & HPWT0_SPD_MASK) >> HPWT0_SPD_SHIFT;

		if (pwtspd == HPWT0_SPD_FUWW_SPEED)
			wetuwn -ENODEV;
	}

	if (!qtd)
		wetuwn -EINVAW;

	dwc2_hcd_qtd_init(qtd, uwb);
	wetvaw = dwc2_hcd_qtd_add(hsotg, qtd, qh);
	if (wetvaw) {
		dev_eww(hsotg->dev,
			"DWC OTG HCD UWB Enqueue faiwed adding QTD. Ewwow status %d\n",
			wetvaw);
		wetuwn wetvaw;
	}

	intw_mask = dwc2_weadw(hsotg, GINTMSK);
	if (!(intw_mask & GINTSTS_SOF)) {
		enum dwc2_twansaction_type tw_type;

		if (qtd->qh->ep_type == USB_ENDPOINT_XFEW_BUWK &&
		    !(qtd->uwb->fwags & UWB_GIVEBACK_ASAP))
			/*
			 * Do not scheduwe SG twansactions untiw qtd has
			 * UWB_GIVEBACK_ASAP set
			 */
			wetuwn 0;

		tw_type = dwc2_hcd_sewect_twansactions(hsotg);
		if (tw_type != DWC2_TWANSACTION_NONE)
			dwc2_hcd_queue_twansactions(hsotg, tw_type);
	}

	wetuwn 0;
}

/* Must be cawwed with intewwupt disabwed and spinwock hewd */
static int dwc2_hcd_uwb_dequeue(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_hcd_uwb *uwb)
{
	stwuct dwc2_qh *qh;
	stwuct dwc2_qtd *uwb_qtd;

	uwb_qtd = uwb->qtd;
	if (!uwb_qtd) {
		dev_dbg(hsotg->dev, "## Uwb QTD is NUWW ##\n");
		wetuwn -EINVAW;
	}

	qh = uwb_qtd->qh;
	if (!qh) {
		dev_dbg(hsotg->dev, "## Uwb QTD QH is NUWW ##\n");
		wetuwn -EINVAW;
	}

	uwb->pwiv = NUWW;

	if (uwb_qtd->in_pwocess && qh->channew) {
		dwc2_dump_channew_info(hsotg, qh->channew);

		/* The QTD is in pwocess (it has been assigned to a channew) */
		if (hsotg->fwags.b.powt_connect_status)
			/*
			 * If stiww connected (i.e. in host mode), hawt the
			 * channew so it can be used fow othew twansfews. If
			 * no wongew connected, the host wegistews can't be
			 * wwitten to hawt the channew since the cowe is in
			 * device mode.
			 */
			dwc2_hc_hawt(hsotg, qh->channew,
				     DWC2_HC_XFEW_UWB_DEQUEUE);
	}

	/*
	 * Fwee the QTD and cwean up the associated QH. Weave the QH in the
	 * scheduwe if it has any wemaining QTDs.
	 */
	if (!hsotg->pawams.dma_desc_enabwe) {
		u8 in_pwocess = uwb_qtd->in_pwocess;

		dwc2_hcd_qtd_unwink_and_fwee(hsotg, uwb_qtd, qh);
		if (in_pwocess) {
			dwc2_hcd_qh_deactivate(hsotg, qh, 0);
			qh->channew = NUWW;
		} ewse if (wist_empty(&qh->qtd_wist)) {
			dwc2_hcd_qh_unwink(hsotg, qh);
		}
	} ewse {
		dwc2_hcd_qtd_unwink_and_fwee(hsotg, uwb_qtd, qh);
	}

	wetuwn 0;
}

/* Must NOT be cawwed with intewwupt disabwed ow spinwock hewd */
static int dwc2_hcd_endpoint_disabwe(stwuct dwc2_hsotg *hsotg,
				     stwuct usb_host_endpoint *ep, int wetwy)
{
	stwuct dwc2_qtd *qtd, *qtd_tmp;
	stwuct dwc2_qh *qh;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	qh = ep->hcpwiv;
	if (!qh) {
		wc = -EINVAW;
		goto eww;
	}

	whiwe (!wist_empty(&qh->qtd_wist) && wetwy--) {
		if (wetwy == 0) {
			dev_eww(hsotg->dev,
				"## timeout in dwc2_hcd_endpoint_disabwe() ##\n");
			wc = -EBUSY;
			goto eww;
		}

		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		msweep(20);
		spin_wock_iwqsave(&hsotg->wock, fwags);
		qh = ep->hcpwiv;
		if (!qh) {
			wc = -EINVAW;
			goto eww;
		}
	}

	dwc2_hcd_qh_unwink(hsotg, qh);

	/* Fwee each QTD in the QH's QTD wist */
	wist_fow_each_entwy_safe(qtd, qtd_tmp, &qh->qtd_wist, qtd_wist_entwy)
		dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);

	ep->hcpwiv = NUWW;

	if (qh->channew && qh->channew->qh == qh)
		qh->channew->qh = NUWW;

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	dwc2_hcd_qh_fwee(hsotg, qh);

	wetuwn 0;

eww:
	ep->hcpwiv = NUWW;
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn wc;
}

/* Must be cawwed with intewwupt disabwed and spinwock hewd */
static int dwc2_hcd_endpoint_weset(stwuct dwc2_hsotg *hsotg,
				   stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_qh *qh = ep->hcpwiv;

	if (!qh)
		wetuwn -EINVAW;

	qh->data_toggwe = DWC2_HC_PID_DATA0;

	wetuwn 0;
}

/**
 * dwc2_cowe_init() - Initiawizes the DWC_otg contwowwew wegistews and
 * pwepawes the cowe fow device mode ow host mode opewation
 *
 * @hsotg:         Pwogwamming view of the DWC_otg contwowwew
 * @initiaw_setup: If twue then this is the fiwst init fow this instance.
 */
int dwc2_cowe_init(stwuct dwc2_hsotg *hsotg, boow initiaw_setup)
{
	u32 usbcfg, otgctw;
	int wetvaw;

	dev_dbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);

	/* Set UWPI Extewnaw VBUS bit if needed */
	usbcfg &= ~GUSBCFG_UWPI_EXT_VBUS_DWV;
	if (hsotg->pawams.phy_uwpi_ext_vbus)
		usbcfg |= GUSBCFG_UWPI_EXT_VBUS_DWV;

	/* Set extewnaw TS Dwine puwsing bit if needed */
	usbcfg &= ~GUSBCFG_TEWMSEWDWPUWSE;
	if (hsotg->pawams.ts_dwine)
		usbcfg |= GUSBCFG_TEWMSEWDWPUWSE;

	dwc2_wwitew(hsotg, usbcfg, GUSBCFG);

	/*
	 * Weset the Contwowwew
	 *
	 * We onwy need to weset the contwowwew if this is a we-init.
	 * Fow the fiwst init we know fow suwe that eawwiew code weset us (it
	 * needed to in owdew to pwopewwy detect vawious pawametews).
	 */
	if (!initiaw_setup) {
		wetvaw = dwc2_cowe_weset(hsotg, fawse);
		if (wetvaw) {
			dev_eww(hsotg->dev, "%s(): Weset faiwed, abowting\n",
				__func__);
			wetuwn wetvaw;
		}
	}

	/*
	 * This needs to happen in FS mode befowe any othew pwogwamming occuws
	 */
	wetvaw = dwc2_phy_init(hsotg, initiaw_setup);
	if (wetvaw)
		wetuwn wetvaw;

	/* Pwogwam the GAHBCFG Wegistew */
	wetvaw = dwc2_gahbcfg_init(hsotg);
	if (wetvaw)
		wetuwn wetvaw;

	/* Pwogwam the GUSBCFG wegistew */
	dwc2_gusbcfg_init(hsotg);

	/* Pwogwam the GOTGCTW wegistew */
	otgctw = dwc2_weadw(hsotg, GOTGCTW);
	otgctw &= ~GOTGCTW_OTGVEW;
	dwc2_wwitew(hsotg, otgctw, GOTGCTW);

	/* Cweaw the SWP success bit fow FS-I2c */
	hsotg->swp_success = 0;

	/* Enabwe common intewwupts */
	dwc2_enabwe_common_intewwupts(hsotg);

	/*
	 * Do device ow host initiawization based on mode duwing PCD and
	 * HCD initiawization
	 */
	if (dwc2_is_host_mode(hsotg)) {
		dev_dbg(hsotg->dev, "Host Mode\n");
		hsotg->op_state = OTG_STATE_A_HOST;
	} ewse {
		dev_dbg(hsotg->dev, "Device Mode\n");
		hsotg->op_state = OTG_STATE_B_PEWIPHEWAW;
	}

	wetuwn 0;
}

/**
 * dwc2_cowe_host_init() - Initiawizes the DWC_otg contwowwew wegistews fow
 * Host mode
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * This function fwushes the Tx and Wx FIFOs and fwushes any entwies in the
 * wequest queues. Host channews awe weset to ensuwe that they awe weady fow
 * pewfowming twansfews.
 */
static void dwc2_cowe_host_init(stwuct dwc2_hsotg *hsotg)
{
	u32 hcfg, hfiw, otgctw, usbcfg;

	dev_dbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	/* Set HS/FS Timeout Cawibwation to 7 (max avaiwabwe vawue).
	 * The numbew of PHY cwocks that the appwication pwogwams in
	 * this fiewd is added to the high/fuww speed intewpacket timeout
	 * duwation in the cowe to account fow any additionaw deways
	 * intwoduced by the PHY. This can be wequiwed, because the deway
	 * intwoduced by the PHY in genewating the winestate condition
	 * can vawy fwom one PHY to anothew.
	 */
	usbcfg = dwc2_weadw(hsotg, GUSBCFG);
	usbcfg |= GUSBCFG_TOUTCAW(7);
	dwc2_wwitew(hsotg, usbcfg, GUSBCFG);

	/* Westawt the Phy Cwock */
	dwc2_wwitew(hsotg, 0, PCGCTW);

	/* Initiawize Host Configuwation Wegistew */
	dwc2_init_fs_ws_pcwk_sew(hsotg);
	if (hsotg->pawams.speed == DWC2_SPEED_PAWAM_FUWW ||
	    hsotg->pawams.speed == DWC2_SPEED_PAWAM_WOW) {
		hcfg = dwc2_weadw(hsotg, HCFG);
		hcfg |= HCFG_FSWSSUPP;
		dwc2_wwitew(hsotg, hcfg, HCFG);
	}

	/*
	 * This bit awwows dynamic wewoading of the HFIW wegistew duwing
	 * wuntime. This bit needs to be pwogwammed duwing initiaw configuwation
	 * and its vawue must not be changed duwing wuntime.
	 */
	if (hsotg->pawams.wewoad_ctw) {
		hfiw = dwc2_weadw(hsotg, HFIW);
		hfiw |= HFIW_WWDCTWW;
		dwc2_wwitew(hsotg, hfiw, HFIW);
	}

	if (hsotg->pawams.dma_desc_enabwe) {
		u32 op_mode = hsotg->hw_pawams.op_mode;

		if (hsotg->hw_pawams.snpsid < DWC2_COWE_WEV_2_90a ||
		    !hsotg->hw_pawams.dma_desc_enabwe ||
		    op_mode == GHWCFG2_OP_MODE_SWP_CAPABWE_DEVICE ||
		    op_mode == GHWCFG2_OP_MODE_NO_SWP_CAPABWE_DEVICE ||
		    op_mode == GHWCFG2_OP_MODE_UNDEFINED) {
			dev_eww(hsotg->dev,
				"Hawdwawe does not suppowt descwiptow DMA mode -\n");
			dev_eww(hsotg->dev,
				"fawwing back to buffew DMA mode.\n");
			hsotg->pawams.dma_desc_enabwe = fawse;
		} ewse {
			hcfg = dwc2_weadw(hsotg, HCFG);
			hcfg |= HCFG_DESCDMA;
			dwc2_wwitew(hsotg, hcfg, HCFG);
		}
	}

	/* Configuwe data FIFO sizes */
	dwc2_config_fifos(hsotg);

	/* TODO - check this */
	/* Cweaw Host Set HNP Enabwe in the OTG Contwow Wegistew */
	otgctw = dwc2_weadw(hsotg, GOTGCTW);
	otgctw &= ~GOTGCTW_HSTSETHNPEN;
	dwc2_wwitew(hsotg, otgctw, GOTGCTW);

	/* Make suwe the FIFOs awe fwushed */
	dwc2_fwush_tx_fifo(hsotg, 0x10 /* aww TX FIFOs */);
	dwc2_fwush_wx_fifo(hsotg);

	/* Cweaw Host Set HNP Enabwe in the OTG Contwow Wegistew */
	otgctw = dwc2_weadw(hsotg, GOTGCTW);
	otgctw &= ~GOTGCTW_HSTSETHNPEN;
	dwc2_wwitew(hsotg, otgctw, GOTGCTW);

	if (!hsotg->pawams.dma_desc_enabwe) {
		int num_channews, i;
		u32 hcchaw;

		/* Fwush out any weftovew queued wequests */
		num_channews = hsotg->pawams.host_channews;
		fow (i = 0; i < num_channews; i++) {
			hcchaw = dwc2_weadw(hsotg, HCCHAW(i));
			if (hcchaw & HCCHAW_CHENA) {
				hcchaw &= ~HCCHAW_CHENA;
				hcchaw |= HCCHAW_CHDIS;
				hcchaw &= ~HCCHAW_EPDIW;
				dwc2_wwitew(hsotg, hcchaw, HCCHAW(i));
			}
		}

		/* Hawt aww channews to put them into a known state */
		fow (i = 0; i < num_channews; i++) {
			hcchaw = dwc2_weadw(hsotg, HCCHAW(i));
			if (hcchaw & HCCHAW_CHENA) {
				hcchaw |= HCCHAW_CHENA | HCCHAW_CHDIS;
				hcchaw &= ~HCCHAW_EPDIW;
				dwc2_wwitew(hsotg, hcchaw, HCCHAW(i));
				dev_dbg(hsotg->dev, "%s: Hawt channew %d\n",
					__func__, i);

				if (dwc2_hsotg_wait_bit_cweaw(hsotg, HCCHAW(i),
							      HCCHAW_CHENA,
							      1000)) {
					dev_wawn(hsotg->dev,
						 "Unabwe to cweaw enabwe on channew %d\n",
						 i);
				}
			}
		}
	}

	/* Enabwe ACG featuwe in host mode, if suppowted */
	dwc2_enabwe_acg(hsotg);

	/* Tuwn on the vbus powew */
	dev_dbg(hsotg->dev, "Init: Powt Powew? op_state=%d\n", hsotg->op_state);
	if (hsotg->op_state == OTG_STATE_A_HOST) {
		u32 hpwt0 = dwc2_wead_hpwt0(hsotg);

		dev_dbg(hsotg->dev, "Init: Powew Powt (%d)\n",
			!!(hpwt0 & HPWT0_PWW));
		if (!(hpwt0 & HPWT0_PWW)) {
			hpwt0 |= HPWT0_PWW;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
		}
	}

	dwc2_enabwe_host_intewwupts(hsotg);
}

/*
 * Initiawizes dynamic powtions of the DWC_otg HCD state
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static void dwc2_hcd_weinit(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_host_chan *chan, *chan_tmp;
	int num_channews;
	int i;

	hsotg->fwags.d32 = 0;
	hsotg->non_pewiodic_qh_ptw = &hsotg->non_pewiodic_sched_active;

	if (hsotg->pawams.ufwame_sched) {
		hsotg->avaiwabwe_host_channews =
			hsotg->pawams.host_channews;
	} ewse {
		hsotg->non_pewiodic_channews = 0;
		hsotg->pewiodic_channews = 0;
	}

	/*
	 * Put aww channews in the fwee channew wist and cwean up channew
	 * states
	 */
	wist_fow_each_entwy_safe(chan, chan_tmp, &hsotg->fwee_hc_wist,
				 hc_wist_entwy)
		wist_dew_init(&chan->hc_wist_entwy);

	num_channews = hsotg->pawams.host_channews;
	fow (i = 0; i < num_channews; i++) {
		chan = hsotg->hc_ptw_awway[i];
		wist_add_taiw(&chan->hc_wist_entwy, &hsotg->fwee_hc_wist);
		dwc2_hc_cweanup(hsotg, chan);
	}

	/* Initiawize the DWC cowe fow host mode opewation */
	dwc2_cowe_host_init(hsotg);
}

static void dwc2_hc_init_spwit(stwuct dwc2_hsotg *hsotg,
			       stwuct dwc2_host_chan *chan,
			       stwuct dwc2_qtd *qtd, stwuct dwc2_hcd_uwb *uwb)
{
	int hub_addw, hub_powt;

	chan->do_spwit = 1;
	chan->xact_pos = qtd->isoc_spwit_pos;
	chan->compwete_spwit = qtd->compwete_spwit;
	dwc2_host_hub_info(hsotg, uwb->pwiv, &hub_addw, &hub_powt);
	chan->hub_addw = (u8)hub_addw;
	chan->hub_powt = (u8)hub_powt;
}

static void dwc2_hc_init_xfew(stwuct dwc2_hsotg *hsotg,
			      stwuct dwc2_host_chan *chan,
			      stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;

	switch (dwc2_hcd_get_pipe_type(&uwb->pipe_info)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		chan->ep_type = USB_ENDPOINT_XFEW_CONTWOW;

		switch (qtd->contwow_phase) {
		case DWC2_CONTWOW_SETUP:
			dev_vdbg(hsotg->dev, "  Contwow setup twansaction\n");
			chan->do_ping = 0;
			chan->ep_is_in = 0;
			chan->data_pid_stawt = DWC2_HC_PID_SETUP;
			if (hsotg->pawams.host_dma)
				chan->xfew_dma = uwb->setup_dma;
			ewse
				chan->xfew_buf = uwb->setup_packet;
			chan->xfew_wen = 8;
			bweak;

		case DWC2_CONTWOW_DATA:
			dev_vdbg(hsotg->dev, "  Contwow data twansaction\n");
			chan->data_pid_stawt = qtd->data_toggwe;
			bweak;

		case DWC2_CONTWOW_STATUS:
			/*
			 * Diwection is opposite of data diwection ow IN if no
			 * data
			 */
			dev_vdbg(hsotg->dev, "  Contwow status twansaction\n");
			if (uwb->wength == 0)
				chan->ep_is_in = 1;
			ewse
				chan->ep_is_in =
					dwc2_hcd_is_pipe_out(&uwb->pipe_info);
			if (chan->ep_is_in)
				chan->do_ping = 0;
			chan->data_pid_stawt = DWC2_HC_PID_DATA1;
			chan->xfew_wen = 0;
			if (hsotg->pawams.host_dma)
				chan->xfew_dma = hsotg->status_buf_dma;
			ewse
				chan->xfew_buf = hsotg->status_buf;
			bweak;
		}
		bweak;

	case USB_ENDPOINT_XFEW_BUWK:
		chan->ep_type = USB_ENDPOINT_XFEW_BUWK;
		bweak;

	case USB_ENDPOINT_XFEW_INT:
		chan->ep_type = USB_ENDPOINT_XFEW_INT;
		bweak;

	case USB_ENDPOINT_XFEW_ISOC:
		chan->ep_type = USB_ENDPOINT_XFEW_ISOC;
		if (hsotg->pawams.dma_desc_enabwe)
			bweak;

		fwame_desc = &uwb->iso_descs[qtd->isoc_fwame_index];
		fwame_desc->status = 0;

		if (hsotg->pawams.host_dma) {
			chan->xfew_dma = uwb->dma;
			chan->xfew_dma += fwame_desc->offset +
					qtd->isoc_spwit_offset;
		} ewse {
			chan->xfew_buf = uwb->buf;
			chan->xfew_buf += fwame_desc->offset +
					qtd->isoc_spwit_offset;
		}

		chan->xfew_wen = fwame_desc->wength - qtd->isoc_spwit_offset;

		if (chan->xact_pos == DWC2_HCSPWT_XACTPOS_AWW) {
			if (chan->xfew_wen <= 188)
				chan->xact_pos = DWC2_HCSPWT_XACTPOS_AWW;
			ewse
				chan->xact_pos = DWC2_HCSPWT_XACTPOS_BEGIN;
		}
		bweak;
	}
}

static int dwc2_awwoc_spwit_dma_awigned_buf(stwuct dwc2_hsotg *hsotg,
					    stwuct dwc2_qh *qh,
					    stwuct dwc2_host_chan *chan)
{
	if (!hsotg->unawigned_cache ||
	    chan->max_packet > DWC2_KMEM_UNAWIGNED_BUF_SIZE)
		wetuwn -ENOMEM;

	if (!qh->dw_awign_buf) {
		qh->dw_awign_buf = kmem_cache_awwoc(hsotg->unawigned_cache,
						    GFP_ATOMIC | GFP_DMA);
		if (!qh->dw_awign_buf)
			wetuwn -ENOMEM;
	}

	qh->dw_awign_buf_dma = dma_map_singwe(hsotg->dev, qh->dw_awign_buf,
					      DWC2_KMEM_UNAWIGNED_BUF_SIZE,
					      DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(hsotg->dev, qh->dw_awign_buf_dma)) {
		dev_eww(hsotg->dev, "can't map awign_buf\n");
		chan->awign_buf = 0;
		wetuwn -EINVAW;
	}

	chan->awign_buf = qh->dw_awign_buf_dma;
	wetuwn 0;
}

#define DWC2_USB_DMA_AWIGN 4

static void dwc2_fwee_dma_awigned_buffew(stwuct uwb *uwb)
{
	void *stowed_xfew_buffew;
	size_t wength;

	if (!(uwb->twansfew_fwags & UWB_AWIGNED_TEMP_BUFFEW))
		wetuwn;

	/* Westowe uwb->twansfew_buffew fwom the end of the awwocated awea */
	memcpy(&stowed_xfew_buffew,
	       PTW_AWIGN(uwb->twansfew_buffew + uwb->twansfew_buffew_wength,
			 dma_get_cache_awignment()),
	       sizeof(uwb->twansfew_buffew));

	if (usb_uwb_diw_in(uwb)) {
		if (usb_pipeisoc(uwb->pipe))
			wength = uwb->twansfew_buffew_wength;
		ewse
			wength = uwb->actuaw_wength;

		memcpy(stowed_xfew_buffew, uwb->twansfew_buffew, wength);
	}
	kfwee(uwb->twansfew_buffew);
	uwb->twansfew_buffew = stowed_xfew_buffew;

	uwb->twansfew_fwags &= ~UWB_AWIGNED_TEMP_BUFFEW;
}

static int dwc2_awwoc_dma_awigned_buffew(stwuct uwb *uwb, gfp_t mem_fwags)
{
	void *kmawwoc_ptw;
	size_t kmawwoc_size;

	if (uwb->num_sgs || uwb->sg ||
	    uwb->twansfew_buffew_wength == 0 ||
	    !((uintptw_t)uwb->twansfew_buffew & (DWC2_USB_DMA_AWIGN - 1)))
		wetuwn 0;

	/*
	 * Awwocate a buffew with enough padding fow owiginaw twansfew_buffew
	 * pointew. This awwocation is guawanteed to be awigned pwopewwy fow
	 * DMA
	 */
	kmawwoc_size = uwb->twansfew_buffew_wength +
		(dma_get_cache_awignment() - 1) +
		sizeof(uwb->twansfew_buffew);

	kmawwoc_ptw = kmawwoc(kmawwoc_size, mem_fwags);
	if (!kmawwoc_ptw)
		wetuwn -ENOMEM;

	/*
	 * Position vawue of owiginaw uwb->twansfew_buffew pointew to the end
	 * of awwocation fow watew wefewencing
	 */
	memcpy(PTW_AWIGN(kmawwoc_ptw + uwb->twansfew_buffew_wength,
			 dma_get_cache_awignment()),
	       &uwb->twansfew_buffew, sizeof(uwb->twansfew_buffew));

	if (usb_uwb_diw_out(uwb))
		memcpy(kmawwoc_ptw, uwb->twansfew_buffew,
		       uwb->twansfew_buffew_wength);
	uwb->twansfew_buffew = kmawwoc_ptw;

	uwb->twansfew_fwags |= UWB_AWIGNED_TEMP_BUFFEW;

	wetuwn 0;
}

static int dwc2_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				gfp_t mem_fwags)
{
	int wet;

	/* We assume setup_dma is awways awigned; wawn if not */
	WAWN_ON_ONCE(uwb->setup_dma &&
		     (uwb->setup_dma & (DWC2_USB_DMA_AWIGN - 1)));

	wet = dwc2_awwoc_dma_awigned_buffew(uwb, mem_fwags);
	if (wet)
		wetuwn wet;

	wet = usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);
	if (wet)
		dwc2_fwee_dma_awigned_buffew(uwb);

	wetuwn wet;
}

static void dwc2_unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	usb_hcd_unmap_uwb_fow_dma(hcd, uwb);
	dwc2_fwee_dma_awigned_buffew(uwb);
}

/**
 * dwc2_assign_and_init_hc() - Assigns twansactions fwom a QTD to a fwee host
 * channew and initiawizes the host channew to pewfowm the twansactions. The
 * host channew is wemoved fwom the fwee wist.
 *
 * @hsotg: The HCD state stwuctuwe
 * @qh:    Twansactions fwom the fiwst QTD fow this QH awe sewected and assigned
 *         to a fwee host channew
 */
static int dwc2_assign_and_init_hc(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	stwuct dwc2_host_chan *chan;
	stwuct dwc2_hcd_uwb *uwb;
	stwuct dwc2_qtd *qtd;

	if (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s(%p,%p)\n", __func__, hsotg, qh);

	if (wist_empty(&qh->qtd_wist)) {
		dev_dbg(hsotg->dev, "No QTDs in QH wist\n");
		wetuwn -ENOMEM;
	}

	if (wist_empty(&hsotg->fwee_hc_wist)) {
		dev_dbg(hsotg->dev, "No fwee channew to assign\n");
		wetuwn -ENOMEM;
	}

	chan = wist_fiwst_entwy(&hsotg->fwee_hc_wist, stwuct dwc2_host_chan,
				hc_wist_entwy);

	/* Wemove host channew fwom fwee wist */
	wist_dew_init(&chan->hc_wist_entwy);

	qtd = wist_fiwst_entwy(&qh->qtd_wist, stwuct dwc2_qtd, qtd_wist_entwy);
	uwb = qtd->uwb;
	qh->channew = chan;
	qtd->in_pwocess = 1;

	/*
	 * Use usb_pipedevice to detewmine device addwess. This addwess is
	 * 0 befowe the SET_ADDWESS command and the cowwect addwess aftewwawd.
	 */
	chan->dev_addw = dwc2_hcd_get_dev_addw(&uwb->pipe_info);
	chan->ep_num = dwc2_hcd_get_ep_num(&uwb->pipe_info);
	chan->speed = qh->dev_speed;
	chan->max_packet = qh->maxp;

	chan->xfew_stawted = 0;
	chan->hawt_status = DWC2_HC_XFEW_NO_HAWT_STATUS;
	chan->ewwow_state = (qtd->ewwow_count > 0);
	chan->hawt_on_queue = 0;
	chan->hawt_pending = 0;
	chan->wequests = 0;

	/*
	 * The fowwowing vawues may be modified in the twansfew type section
	 * bewow. The xfew_wen vawue may be weduced when the twansfew is
	 * stawted to accommodate the max widths of the XfewSize and PktCnt
	 * fiewds in the HCTSIZn wegistew.
	 */

	chan->ep_is_in = (dwc2_hcd_is_pipe_in(&uwb->pipe_info) != 0);
	if (chan->ep_is_in)
		chan->do_ping = 0;
	ewse
		chan->do_ping = qh->ping_state;

	chan->data_pid_stawt = qh->data_toggwe;
	chan->muwti_count = 1;

	if (uwb->actuaw_wength > uwb->wength &&
	    !dwc2_hcd_is_pipe_in(&uwb->pipe_info))
		uwb->actuaw_wength = uwb->wength;

	if (hsotg->pawams.host_dma)
		chan->xfew_dma = uwb->dma + uwb->actuaw_wength;
	ewse
		chan->xfew_buf = (u8 *)uwb->buf + uwb->actuaw_wength;

	chan->xfew_wen = uwb->wength - uwb->actuaw_wength;
	chan->xfew_count = 0;

	/* Set the spwit attwibutes if wequiwed */
	if (qh->do_spwit)
		dwc2_hc_init_spwit(hsotg, chan, qtd, uwb);
	ewse
		chan->do_spwit = 0;

	/* Set the twansfew attwibutes */
	dwc2_hc_init_xfew(hsotg, chan, qtd);

	/* Fow non-dwowd awigned buffews */
	if (hsotg->pawams.host_dma && qh->do_spwit &&
	    chan->ep_is_in && (chan->xfew_dma & 0x3)) {
		dev_vdbg(hsotg->dev, "Non-awigned buffew\n");
		if (dwc2_awwoc_spwit_dma_awigned_buf(hsotg, qh, chan)) {
			dev_eww(hsotg->dev,
				"Faiwed to awwocate memowy to handwe non-awigned buffew\n");
			/* Add channew back to fwee wist */
			chan->awign_buf = 0;
			chan->muwti_count = 0;
			wist_add_taiw(&chan->hc_wist_entwy,
				      &hsotg->fwee_hc_wist);
			qtd->in_pwocess = 0;
			qh->channew = NUWW;
			wetuwn -ENOMEM;
		}
	} ewse {
		/*
		 * We assume that DMA is awways awigned in non-spwit
		 * case ow spwit out case. Wawn if not.
		 */
		WAWN_ON_ONCE(hsotg->pawams.host_dma &&
			     (chan->xfew_dma & 0x3));
		chan->awign_buf = 0;
	}

	if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
	    chan->ep_type == USB_ENDPOINT_XFEW_ISOC)
		/*
		 * This vawue may be modified when the twansfew is stawted
		 * to wefwect the actuaw twansfew wength
		 */
		chan->muwti_count = qh->maxp_muwt;

	if (hsotg->pawams.dma_desc_enabwe) {
		chan->desc_wist_addw = qh->desc_wist_dma;
		chan->desc_wist_sz = qh->desc_wist_sz;
	}

	dwc2_hc_init(hsotg, chan);
	chan->qh = qh;

	wetuwn 0;
}

/**
 * dwc2_hcd_sewect_twansactions() - Sewects twansactions fwom the HCD twansfew
 * scheduwe and assigns them to avaiwabwe host channews. Cawwed fwom the HCD
 * intewwupt handwew functions.
 *
 * @hsotg: The HCD state stwuctuwe
 *
 * Wetuwn: The types of new twansactions that wewe assigned to host channews
 */
enum dwc2_twansaction_type dwc2_hcd_sewect_twansactions(
		stwuct dwc2_hsotg *hsotg)
{
	enum dwc2_twansaction_type wet_vaw = DWC2_TWANSACTION_NONE;
	stwuct wist_head *qh_ptw;
	stwuct dwc2_qh *qh;
	int num_channews;

#ifdef DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "  Sewect Twansactions\n");
#endif

	/* Pwocess entwies in the pewiodic weady wist */
	qh_ptw = hsotg->pewiodic_sched_weady.next;
	whiwe (qh_ptw != &hsotg->pewiodic_sched_weady) {
		if (wist_empty(&hsotg->fwee_hc_wist))
			bweak;
		if (hsotg->pawams.ufwame_sched) {
			if (hsotg->avaiwabwe_host_channews <= 1)
				bweak;
			hsotg->avaiwabwe_host_channews--;
		}
		qh = wist_entwy(qh_ptw, stwuct dwc2_qh, qh_wist_entwy);
		if (dwc2_assign_and_init_hc(hsotg, qh))
			bweak;

		/*
		 * Move the QH fwom the pewiodic weady scheduwe to the
		 * pewiodic assigned scheduwe
		 */
		qh_ptw = qh_ptw->next;
		wist_move_taiw(&qh->qh_wist_entwy,
			       &hsotg->pewiodic_sched_assigned);
		wet_vaw = DWC2_TWANSACTION_PEWIODIC;
	}

	/*
	 * Pwocess entwies in the inactive powtion of the non-pewiodic
	 * scheduwe. Some fwee host channews may not be used if they awe
	 * wesewved fow pewiodic twansfews.
	 */
	num_channews = hsotg->pawams.host_channews;
	qh_ptw = hsotg->non_pewiodic_sched_inactive.next;
	whiwe (qh_ptw != &hsotg->non_pewiodic_sched_inactive) {
		if (!hsotg->pawams.ufwame_sched &&
		    hsotg->non_pewiodic_channews >= num_channews -
						hsotg->pewiodic_channews)
			bweak;
		if (wist_empty(&hsotg->fwee_hc_wist))
			bweak;
		qh = wist_entwy(qh_ptw, stwuct dwc2_qh, qh_wist_entwy);
		if (hsotg->pawams.ufwame_sched) {
			if (hsotg->avaiwabwe_host_channews < 1)
				bweak;
			hsotg->avaiwabwe_host_channews--;
		}

		if (dwc2_assign_and_init_hc(hsotg, qh))
			bweak;

		/*
		 * Move the QH fwom the non-pewiodic inactive scheduwe to the
		 * non-pewiodic active scheduwe
		 */
		qh_ptw = qh_ptw->next;
		wist_move_taiw(&qh->qh_wist_entwy,
			       &hsotg->non_pewiodic_sched_active);

		if (wet_vaw == DWC2_TWANSACTION_NONE)
			wet_vaw = DWC2_TWANSACTION_NON_PEWIODIC;
		ewse
			wet_vaw = DWC2_TWANSACTION_AWW;

		if (!hsotg->pawams.ufwame_sched)
			hsotg->non_pewiodic_channews++;
	}

	wetuwn wet_vaw;
}

/**
 * dwc2_queue_twansaction() - Attempts to queue a singwe twansaction wequest fow
 * a host channew associated with eithew a pewiodic ow non-pewiodic twansfew
 *
 * @hsotg: The HCD state stwuctuwe
 * @chan:  Host channew descwiptow associated with eithew a pewiodic ow
 *         non-pewiodic twansfew
 * @fifo_dwowds_avaiw: Numbew of DWOWDs avaiwabwe in the pewiodic Tx FIFO
 *                     fow pewiodic twansfews ow the non-pewiodic Tx FIFO
 *                     fow non-pewiodic twansfews
 *
 * Wetuwn: 1 if a wequest is queued and mowe wequests may be needed to
 * compwete the twansfew, 0 if no mowe wequests awe wequiwed fow this
 * twansfew, -1 if thewe is insufficient space in the Tx FIFO
 *
 * This function assumes that thewe is space avaiwabwe in the appwopwiate
 * wequest queue. Fow an OUT twansfew ow SETUP twansaction in Swave mode,
 * it checks whethew space is avaiwabwe in the appwopwiate Tx FIFO.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static int dwc2_queue_twansaction(stwuct dwc2_hsotg *hsotg,
				  stwuct dwc2_host_chan *chan,
				  u16 fifo_dwowds_avaiw)
{
	int wetvaw = 0;

	if (chan->do_spwit)
		/* Put ouwsewves on the wist to keep owdew stwaight */
		wist_move_taiw(&chan->spwit_owdew_wist_entwy,
			       &hsotg->spwit_owdew);

	if (hsotg->pawams.host_dma && chan->qh) {
		if (hsotg->pawams.dma_desc_enabwe) {
			if (!chan->xfew_stawted ||
			    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
				dwc2_hcd_stawt_xfew_ddma(hsotg, chan->qh);
				chan->qh->ping_state = 0;
			}
		} ewse if (!chan->xfew_stawted) {
			dwc2_hc_stawt_twansfew(hsotg, chan);
			chan->qh->ping_state = 0;
		}
	} ewse if (chan->hawt_pending) {
		/* Don't queue a wequest if the channew has been hawted */
	} ewse if (chan->hawt_on_queue) {
		dwc2_hc_hawt(hsotg, chan, chan->hawt_status);
	} ewse if (chan->do_ping) {
		if (!chan->xfew_stawted)
			dwc2_hc_stawt_twansfew(hsotg, chan);
	} ewse if (!chan->ep_is_in ||
		   chan->data_pid_stawt == DWC2_HC_PID_SETUP) {
		if ((fifo_dwowds_avaiw * 4) >= chan->max_packet) {
			if (!chan->xfew_stawted) {
				dwc2_hc_stawt_twansfew(hsotg, chan);
				wetvaw = 1;
			} ewse {
				wetvaw = dwc2_hc_continue_twansfew(hsotg, chan);
			}
		} ewse {
			wetvaw = -1;
		}
	} ewse {
		if (!chan->xfew_stawted) {
			dwc2_hc_stawt_twansfew(hsotg, chan);
			wetvaw = 1;
		} ewse {
			wetvaw = dwc2_hc_continue_twansfew(hsotg, chan);
		}
	}

	wetuwn wetvaw;
}

/*
 * Pwocesses pewiodic channews fow the next fwame and queues twansactions fow
 * these channews to the DWC_otg contwowwew. Aftew queueing twansactions, the
 * Pewiodic Tx FIFO Empty intewwupt is enabwed if thewe awe mowe twansactions
 * to queue as Pewiodic Tx FIFO ow wequest queue space becomes avaiwabwe.
 * Othewwise, the Pewiodic Tx FIFO Empty intewwupt is disabwed.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static void dwc2_pwocess_pewiodic_channews(stwuct dwc2_hsotg *hsotg)
{
	stwuct wist_head *qh_ptw;
	stwuct dwc2_qh *qh;
	u32 tx_status;
	u32 fspcavaiw;
	u32 gintmsk;
	int status;
	boow no_queue_space = fawse;
	boow no_fifo_space = fawse;
	u32 qspcavaiw;

	/* If empty wist then just adjust intewwupt enabwes */
	if (wist_empty(&hsotg->pewiodic_sched_assigned))
		goto exit;

	if (dbg_pewio())
		dev_vdbg(hsotg->dev, "Queue pewiodic twansactions\n");

	tx_status = dwc2_weadw(hsotg, HPTXSTS);
	qspcavaiw = (tx_status & TXSTS_QSPCAVAIW_MASK) >>
		    TXSTS_QSPCAVAIW_SHIFT;
	fspcavaiw = (tx_status & TXSTS_FSPCAVAIW_MASK) >>
		    TXSTS_FSPCAVAIW_SHIFT;

	if (dbg_pewio()) {
		dev_vdbg(hsotg->dev, "  P Tx Weq Queue Space Avaiw (befowe queue): %d\n",
			 qspcavaiw);
		dev_vdbg(hsotg->dev, "  P Tx FIFO Space Avaiw (befowe queue): %d\n",
			 fspcavaiw);
	}

	qh_ptw = hsotg->pewiodic_sched_assigned.next;
	whiwe (qh_ptw != &hsotg->pewiodic_sched_assigned) {
		tx_status = dwc2_weadw(hsotg, HPTXSTS);
		qspcavaiw = (tx_status & TXSTS_QSPCAVAIW_MASK) >>
			    TXSTS_QSPCAVAIW_SHIFT;
		if (qspcavaiw == 0) {
			no_queue_space = twue;
			bweak;
		}

		qh = wist_entwy(qh_ptw, stwuct dwc2_qh, qh_wist_entwy);
		if (!qh->channew) {
			qh_ptw = qh_ptw->next;
			continue;
		}

		/* Make suwe EP's TT buffew is cwean befowe queueing qtds */
		if (qh->tt_buffew_diwty) {
			qh_ptw = qh_ptw->next;
			continue;
		}

		/*
		 * Set a fwag if we'we queuing high-bandwidth in swave mode.
		 * The fwag pwevents any hawts to get into the wequest queue in
		 * the middwe of muwtipwe high-bandwidth packets getting queued.
		 */
		if (!hsotg->pawams.host_dma &&
		    qh->channew->muwti_count > 1)
			hsotg->queuing_high_bandwidth = 1;

		fspcavaiw = (tx_status & TXSTS_FSPCAVAIW_MASK) >>
			    TXSTS_FSPCAVAIW_SHIFT;
		status = dwc2_queue_twansaction(hsotg, qh->channew, fspcavaiw);
		if (status < 0) {
			no_fifo_space = twue;
			bweak;
		}

		/*
		 * In Swave mode, stay on the cuwwent twansfew untiw thewe is
		 * nothing mowe to do ow the high-bandwidth wequest count is
		 * weached. In DMA mode, onwy need to queue one wequest. The
		 * contwowwew automaticawwy handwes muwtipwe packets fow
		 * high-bandwidth twansfews.
		 */
		if (hsotg->pawams.host_dma || status == 0 ||
		    qh->channew->wequests == qh->channew->muwti_count) {
			qh_ptw = qh_ptw->next;
			/*
			 * Move the QH fwom the pewiodic assigned scheduwe to
			 * the pewiodic queued scheduwe
			 */
			wist_move_taiw(&qh->qh_wist_entwy,
				       &hsotg->pewiodic_sched_queued);

			/* done queuing high bandwidth */
			hsotg->queuing_high_bandwidth = 0;
		}
	}

exit:
	if (no_queue_space || no_fifo_space ||
	    (!hsotg->pawams.host_dma &&
	     !wist_empty(&hsotg->pewiodic_sched_assigned))) {
		/*
		 * May need to queue mowe twansactions as the wequest
		 * queue ow Tx FIFO empties. Enabwe the pewiodic Tx
		 * FIFO empty intewwupt. (Awways use the hawf-empty
		 * wevew to ensuwe that new wequests awe woaded as
		 * soon as possibwe.)
		 */
		gintmsk = dwc2_weadw(hsotg, GINTMSK);
		if (!(gintmsk & GINTSTS_PTXFEMP)) {
			gintmsk |= GINTSTS_PTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		}
	} ewse {
		/*
		 * Disabwe the Tx FIFO empty intewwupt since thewe awe
		 * no mowe twansactions that need to be queued wight
		 * now. This function is cawwed fwom intewwupt
		 * handwews to queue mowe twansactions as twansfew
		 * states change.
		 */
		gintmsk = dwc2_weadw(hsotg, GINTMSK);
		if (gintmsk & GINTSTS_PTXFEMP) {
			gintmsk &= ~GINTSTS_PTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		}
	}
}

/*
 * Pwocesses active non-pewiodic channews and queues twansactions fow these
 * channews to the DWC_otg contwowwew. Aftew queueing twansactions, the NP Tx
 * FIFO Empty intewwupt is enabwed if thewe awe mowe twansactions to queue as
 * NP Tx FIFO ow wequest queue space becomes avaiwabwe. Othewwise, the NP Tx
 * FIFO Empty intewwupt is disabwed.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
static void dwc2_pwocess_non_pewiodic_channews(stwuct dwc2_hsotg *hsotg)
{
	stwuct wist_head *owig_qh_ptw;
	stwuct dwc2_qh *qh;
	u32 tx_status;
	u32 qspcavaiw;
	u32 fspcavaiw;
	u32 gintmsk;
	int status;
	int no_queue_space = 0;
	int no_fifo_space = 0;
	int mowe_to_do = 0;

	dev_vdbg(hsotg->dev, "Queue non-pewiodic twansactions\n");

	tx_status = dwc2_weadw(hsotg, GNPTXSTS);
	qspcavaiw = (tx_status & TXSTS_QSPCAVAIW_MASK) >>
		    TXSTS_QSPCAVAIW_SHIFT;
	fspcavaiw = (tx_status & TXSTS_FSPCAVAIW_MASK) >>
		    TXSTS_FSPCAVAIW_SHIFT;
	dev_vdbg(hsotg->dev, "  NP Tx Weq Queue Space Avaiw (befowe queue): %d\n",
		 qspcavaiw);
	dev_vdbg(hsotg->dev, "  NP Tx FIFO Space Avaiw (befowe queue): %d\n",
		 fspcavaiw);

	/*
	 * Keep twack of the stawting point. Skip ovew the stawt-of-wist
	 * entwy.
	 */
	if (hsotg->non_pewiodic_qh_ptw == &hsotg->non_pewiodic_sched_active)
		hsotg->non_pewiodic_qh_ptw = hsotg->non_pewiodic_qh_ptw->next;
	owig_qh_ptw = hsotg->non_pewiodic_qh_ptw;

	/*
	 * Pwocess once thwough the active wist ow untiw no mowe space is
	 * avaiwabwe in the wequest queue ow the Tx FIFO
	 */
	do {
		tx_status = dwc2_weadw(hsotg, GNPTXSTS);
		qspcavaiw = (tx_status & TXSTS_QSPCAVAIW_MASK) >>
			    TXSTS_QSPCAVAIW_SHIFT;
		if (!hsotg->pawams.host_dma && qspcavaiw == 0) {
			no_queue_space = 1;
			bweak;
		}

		qh = wist_entwy(hsotg->non_pewiodic_qh_ptw, stwuct dwc2_qh,
				qh_wist_entwy);
		if (!qh->channew)
			goto next;

		/* Make suwe EP's TT buffew is cwean befowe queueing qtds */
		if (qh->tt_buffew_diwty)
			goto next;

		fspcavaiw = (tx_status & TXSTS_FSPCAVAIW_MASK) >>
			    TXSTS_FSPCAVAIW_SHIFT;
		status = dwc2_queue_twansaction(hsotg, qh->channew, fspcavaiw);

		if (status > 0) {
			mowe_to_do = 1;
		} ewse if (status < 0) {
			no_fifo_space = 1;
			bweak;
		}
next:
		/* Advance to next QH, skipping stawt-of-wist entwy */
		hsotg->non_pewiodic_qh_ptw = hsotg->non_pewiodic_qh_ptw->next;
		if (hsotg->non_pewiodic_qh_ptw ==
				&hsotg->non_pewiodic_sched_active)
			hsotg->non_pewiodic_qh_ptw =
					hsotg->non_pewiodic_qh_ptw->next;
	} whiwe (hsotg->non_pewiodic_qh_ptw != owig_qh_ptw);

	if (!hsotg->pawams.host_dma) {
		tx_status = dwc2_weadw(hsotg, GNPTXSTS);
		qspcavaiw = (tx_status & TXSTS_QSPCAVAIW_MASK) >>
			    TXSTS_QSPCAVAIW_SHIFT;
		fspcavaiw = (tx_status & TXSTS_FSPCAVAIW_MASK) >>
			    TXSTS_FSPCAVAIW_SHIFT;
		dev_vdbg(hsotg->dev,
			 "  NP Tx Weq Queue Space Avaiw (aftew queue): %d\n",
			 qspcavaiw);
		dev_vdbg(hsotg->dev,
			 "  NP Tx FIFO Space Avaiw (aftew queue): %d\n",
			 fspcavaiw);

		if (mowe_to_do || no_queue_space || no_fifo_space) {
			/*
			 * May need to queue mowe twansactions as the wequest
			 * queue ow Tx FIFO empties. Enabwe the non-pewiodic
			 * Tx FIFO empty intewwupt. (Awways use the hawf-empty
			 * wevew to ensuwe that new wequests awe woaded as
			 * soon as possibwe.)
			 */
			gintmsk = dwc2_weadw(hsotg, GINTMSK);
			gintmsk |= GINTSTS_NPTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		} ewse {
			/*
			 * Disabwe the Tx FIFO empty intewwupt since thewe awe
			 * no mowe twansactions that need to be queued wight
			 * now. This function is cawwed fwom intewwupt
			 * handwews to queue mowe twansactions as twansfew
			 * states change.
			 */
			gintmsk = dwc2_weadw(hsotg, GINTMSK);
			gintmsk &= ~GINTSTS_NPTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		}
	}
}

/**
 * dwc2_hcd_queue_twansactions() - Pwocesses the cuwwentwy active host channews
 * and queues twansactions fow these channews to the DWC_otg contwowwew. Cawwed
 * fwom the HCD intewwupt handwew functions.
 *
 * @hsotg:   The HCD state stwuctuwe
 * @tw_type: The type(s) of twansactions to queue (non-pewiodic, pewiodic,
 *           ow both)
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
void dwc2_hcd_queue_twansactions(stwuct dwc2_hsotg *hsotg,
				 enum dwc2_twansaction_type tw_type)
{
#ifdef DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "Queue Twansactions\n");
#endif
	/* Pwocess host channews associated with pewiodic twansfews */
	if (tw_type == DWC2_TWANSACTION_PEWIODIC ||
	    tw_type == DWC2_TWANSACTION_AWW)
		dwc2_pwocess_pewiodic_channews(hsotg);

	/* Pwocess host channews associated with non-pewiodic twansfews */
	if (tw_type == DWC2_TWANSACTION_NON_PEWIODIC ||
	    tw_type == DWC2_TWANSACTION_AWW) {
		if (!wist_empty(&hsotg->non_pewiodic_sched_active)) {
			dwc2_pwocess_non_pewiodic_channews(hsotg);
		} ewse {
			/*
			 * Ensuwe NP Tx FIFO empty intewwupt is disabwed when
			 * thewe awe no non-pewiodic twansfews to pwocess
			 */
			u32 gintmsk = dwc2_weadw(hsotg, GINTMSK);

			gintmsk &= ~GINTSTS_NPTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		}
	}
}

static void dwc2_conn_id_status_change(stwuct wowk_stwuct *wowk)
{
	stwuct dwc2_hsotg *hsotg = containew_of(wowk, stwuct dwc2_hsotg,
						wf_otg);
	u32 count = 0;
	u32 gotgctw;
	unsigned wong fwags;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	gotgctw = dwc2_weadw(hsotg, GOTGCTW);
	dev_dbg(hsotg->dev, "gotgctw=%0x\n", gotgctw);
	dev_dbg(hsotg->dev, "gotgctw.b.conidsts=%d\n",
		!!(gotgctw & GOTGCTW_CONID_B));

	/* B-Device connectow (Device Mode) */
	if (gotgctw & GOTGCTW_CONID_B) {
		dwc2_vbus_suppwy_exit(hsotg);
		/* Wait fow switch to device mode */
		dev_dbg(hsotg->dev, "connId B\n");
		if (hsotg->bus_suspended) {
			dev_info(hsotg->dev,
				 "Do powt wesume befowe switching to device mode\n");
			dwc2_powt_wesume(hsotg);
		}
		whiwe (!dwc2_is_device_mode(hsotg)) {
			dev_info(hsotg->dev,
				 "Waiting fow Pewiphewaw Mode, Mode=%s\n",
				 dwc2_is_host_mode(hsotg) ? "Host" :
				 "Pewiphewaw");
			msweep(20);
			/*
			 * Sometimes the initiaw GOTGCTWW wead is wwong, so
			 * check it again and jump to host mode if that was
			 * the case.
			 */
			gotgctw = dwc2_weadw(hsotg, GOTGCTW);
			if (!(gotgctw & GOTGCTW_CONID_B))
				goto host;
			if (++count > 250)
				bweak;
		}
		if (count > 250)
			dev_eww(hsotg->dev,
				"Connection id status change timed out\n");

		/*
		 * Exit Pawtiaw Powew Down without westowing wegistews.
		 * No need to check the wetuwn vawue as wegistews
		 * awe not being westowed.
		 */
		if (hsotg->in_ppd && hsotg->wx_state == DWC2_W2)
			dwc2_exit_pawtiaw_powew_down(hsotg, 0, fawse);

		hsotg->op_state = OTG_STATE_B_PEWIPHEWAW;
		dwc2_cowe_init(hsotg, fawse);
		dwc2_enabwe_gwobaw_intewwupts(hsotg);
		spin_wock_iwqsave(&hsotg->wock, fwags);
		dwc2_hsotg_cowe_init_disconnected(hsotg, fawse);
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		/* Enabwe ACG featuwe in device mode,if suppowted */
		dwc2_enabwe_acg(hsotg);
		dwc2_hsotg_cowe_connect(hsotg);
	} ewse {
host:
		/* A-Device connectow (Host Mode) */
		dev_dbg(hsotg->dev, "connId A\n");
		whiwe (!dwc2_is_host_mode(hsotg)) {
			dev_info(hsotg->dev, "Waiting fow Host Mode, Mode=%s\n",
				 dwc2_is_host_mode(hsotg) ?
				 "Host" : "Pewiphewaw");
			msweep(20);
			if (++count > 250)
				bweak;
		}
		if (count > 250)
			dev_eww(hsotg->dev,
				"Connection id status change timed out\n");

		spin_wock_iwqsave(&hsotg->wock, fwags);
		dwc2_hsotg_disconnect(hsotg);
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);

		hsotg->op_state = OTG_STATE_A_HOST;
		/* Initiawize the Cowe fow Host mode */
		dwc2_cowe_init(hsotg, fawse);
		dwc2_enabwe_gwobaw_intewwupts(hsotg);
		dwc2_hcd_stawt(hsotg);
	}
}

static void dwc2_wakeup_detected(stwuct timew_wist *t)
{
	stwuct dwc2_hsotg *hsotg = fwom_timew(hsotg, t, wkp_timew);
	u32 hpwt0;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	/*
	 * Cweaw the Wesume aftew 70ms. (Need 20 ms minimum. Use 70 ms
	 * so that OPT tests pass with aww PHYs.)
	 */
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	dev_dbg(hsotg->dev, "Wesume: HPWT0=%0x\n", hpwt0);
	hpwt0 &= ~HPWT0_WES;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);
	dev_dbg(hsotg->dev, "Cweaw Wesume: HPWT0=%0x\n",
		dwc2_weadw(hsotg, HPWT0));

	dwc2_hcd_wem_wakeup(hsotg);
	hsotg->bus_suspended = fawse;

	/* Change to W0 state */
	hsotg->wx_state = DWC2_W0;
}

static int dwc2_host_is_b_hnp_enabwed(stwuct dwc2_hsotg *hsotg)
{
	stwuct usb_hcd *hcd = dwc2_hsotg_to_hcd(hsotg);

	wetuwn hcd->sewf.b_hnp_enabwe;
}

/**
 * dwc2_powt_suspend() - Put contwowwew in suspend mode fow host.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @windex: The contwow wequest wIndex fiewd
 *
 * Wetuwn: non-zewo if faiwed to entew suspend mode fow host.
 *
 * This function is fow entewing Host mode suspend.
 * Must NOT be cawwed with intewwupt disabwed ow spinwock hewd.
 */
int dwc2_powt_suspend(stwuct dwc2_hsotg *hsotg, u16 windex)
{
	unsigned wong fwags;
	u32 pcgctw;
	u32 gotgctw;
	int wet = 0;

	dev_dbg(hsotg->dev, "%s()\n", __func__);

	spin_wock_iwqsave(&hsotg->wock, fwags);

	if (windex == hsotg->otg_powt && dwc2_host_is_b_hnp_enabwed(hsotg)) {
		gotgctw = dwc2_weadw(hsotg, GOTGCTW);
		gotgctw |= GOTGCTW_HSTSETHNPEN;
		dwc2_wwitew(hsotg, gotgctw, GOTGCTW);
		hsotg->op_state = OTG_STATE_A_SUSPEND;
	}

	switch (hsotg->pawams.powew_down) {
	case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
		wet = dwc2_entew_pawtiaw_powew_down(hsotg);
		if (wet)
			dev_eww(hsotg->dev,
				"entew pawtiaw_powew_down faiwed.\n");
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
		/*
		 * Pewfowm spin unwock and wock because in
		 * "dwc2_host_entew_hibewnation()" function thewe is a spinwock
		 * wogic which pwevents sewvicing of any IWQ duwing entewing
		 * hibewnation.
		 */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wet = dwc2_entew_hibewnation(hsotg, 1);
		if (wet)
			dev_eww(hsotg->dev, "entew hibewnation faiwed.\n");
		spin_wock_iwqsave(&hsotg->wock, fwags);
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_NONE:
		/*
		 * If not hibewnation now pawtiaw powew down awe suppowted,
		 * cwock gating is used to save powew.
		 */
		if (!hsotg->pawams.no_cwock_gating)
			dwc2_host_entew_cwock_gating(hsotg);
		bweak;
	}

	/* Fow HNP the bus must be suspended fow at weast 200ms */
	if (dwc2_host_is_b_hnp_enabwed(hsotg)) {
		pcgctw = dwc2_weadw(hsotg, PCGCTW);
		pcgctw &= ~PCGCTW_STOPPCWK;
		dwc2_wwitew(hsotg, pcgctw, PCGCTW);

		spin_unwock_iwqwestowe(&hsotg->wock, fwags);

		msweep(200);
	} ewse {
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	}

	wetuwn wet;
}

/**
 * dwc2_powt_wesume() - Exit contwowwew fwom suspend mode fow host.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 * Wetuwn: non-zewo if faiwed to exit suspend mode fow host.
 *
 * This function is fow exiting Host mode suspend.
 * Must NOT be cawwed with intewwupt disabwed ow spinwock hewd.
 */
int dwc2_powt_wesume(stwuct dwc2_hsotg *hsotg)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	switch (hsotg->pawams.powew_down) {
	case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
		wet = dwc2_exit_pawtiaw_powew_down(hsotg, 0, twue);
		if (wet)
			dev_eww(hsotg->dev,
				"exit pawtiaw_powew_down faiwed.\n");
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
		/* Exit host hibewnation. */
		wet = dwc2_exit_hibewnation(hsotg, 0, 0, 1);
		if (wet)
			dev_eww(hsotg->dev, "exit hibewnation faiwed.\n");
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_NONE:
		/*
		 * If not hibewnation now pawtiaw powew down awe suppowted,
		 * powt wesume is done using the cwock gating pwogwamming fwow.
		 */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		dwc2_host_exit_cwock_gating(hsotg, 0);
		spin_wock_iwqsave(&hsotg->wock, fwags);
		bweak;
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn wet;
}

/* Handwes hub cwass-specific wequests */
static int dwc2_hcd_hub_contwow(stwuct dwc2_hsotg *hsotg, u16 typeweq,
				u16 wvawue, u16 windex, chaw *buf, u16 wwength)
{
	stwuct usb_hub_descwiptow *hub_desc;
	int wetvaw = 0;
	u32 hpwt0;
	u32 powt_status;
	u32 speed;
	u32 pcgctw;
	u32 pww;

	switch (typeweq) {
	case CweawHubFeatuwe:
		dev_dbg(hsotg->dev, "CweawHubFeatuwe %1xh\n", wvawue);

		switch (wvawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* Nothing wequiwed hewe */
			bweak;

		defauwt:
			wetvaw = -EINVAW;
			dev_eww(hsotg->dev,
				"CweawHubFeatuwe wequest %1xh unknown\n",
				wvawue);
		}
		bweak;

	case CweawPowtFeatuwe:
		if (wvawue != USB_POWT_FEAT_W1)
			if (!windex || windex > 1)
				goto ewwow;
		switch (wvawue) {
		case USB_POWT_FEAT_ENABWE:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_ENABWE\n");
			hpwt0 = dwc2_wead_hpwt0(hsotg);
			hpwt0 |= HPWT0_ENA;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
			bweak;

		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_SUSPEND\n");

			if (hsotg->bus_suspended)
				wetvaw = dwc2_powt_wesume(hsotg);
			bweak;

		case USB_POWT_FEAT_POWEW:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_POWEW\n");
			hpwt0 = dwc2_wead_hpwt0(hsotg);
			pww = hpwt0 & HPWT0_PWW;
			hpwt0 &= ~HPWT0_PWW;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
			if (pww)
				dwc2_vbus_suppwy_exit(hsotg);
			bweak;

		case USB_POWT_FEAT_INDICATOW:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_INDICATOW\n");
			/* Powt indicatow not suppowted */
			bweak;

		case USB_POWT_FEAT_C_CONNECTION:
			/*
			 * Cweaws dwivew's intewnaw Connect Status Change fwag
			 */
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_CONNECTION\n");
			hsotg->fwags.b.powt_connect_status_change = 0;
			bweak;

		case USB_POWT_FEAT_C_WESET:
			/* Cweaws dwivew's intewnaw Powt Weset Change fwag */
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_WESET\n");
			hsotg->fwags.b.powt_weset_change = 0;
			bweak;

		case USB_POWT_FEAT_C_ENABWE:
			/*
			 * Cweaws the dwivew's intewnaw Powt Enabwe/Disabwe
			 * Change fwag
			 */
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_ENABWE\n");
			hsotg->fwags.b.powt_enabwe_change = 0;
			bweak;

		case USB_POWT_FEAT_C_SUSPEND:
			/*
			 * Cweaws the dwivew's intewnaw Powt Suspend Change
			 * fwag, which is set when wesume signawing on the host
			 * powt is compwete
			 */
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_SUSPEND\n");
			hsotg->fwags.b.powt_suspend_change = 0;
			bweak;

		case USB_POWT_FEAT_C_POWT_W1:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_POWT_W1\n");
			hsotg->fwags.b.powt_w1_change = 0;
			bweak;

		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			dev_dbg(hsotg->dev,
				"CweawPowtFeatuwe USB_POWT_FEAT_C_OVEW_CUWWENT\n");
			hsotg->fwags.b.powt_ovew_cuwwent_change = 0;
			bweak;

		defauwt:
			wetvaw = -EINVAW;
			dev_eww(hsotg->dev,
				"CweawPowtFeatuwe wequest %1xh unknown ow unsuppowted\n",
				wvawue);
		}
		bweak;

	case GetHubDescwiptow:
		dev_dbg(hsotg->dev, "GetHubDescwiptow\n");
		hub_desc = (stwuct usb_hub_descwiptow *)buf;
		hub_desc->bDescWength = 9;
		hub_desc->bDescwiptowType = USB_DT_HUB;
		hub_desc->bNbwPowts = 1;
		hub_desc->wHubChawactewistics =
			cpu_to_we16(HUB_CHAW_COMMON_WPSM |
				    HUB_CHAW_INDV_POWT_OCPM);
		hub_desc->bPwwOn2PwwGood = 1;
		hub_desc->bHubContwCuwwent = 0;
		hub_desc->u.hs.DeviceWemovabwe[0] = 0;
		hub_desc->u.hs.DeviceWemovabwe[1] = 0xff;
		bweak;

	case GetHubStatus:
		dev_dbg(hsotg->dev, "GetHubStatus\n");
		memset(buf, 0, 4);
		bweak;

	case GetPowtStatus:
		dev_vdbg(hsotg->dev,
			 "GetPowtStatus wIndex=0x%04x fwags=0x%08x\n", windex,
			 hsotg->fwags.d32);
		if (!windex || windex > 1)
			goto ewwow;

		powt_status = 0;
		if (hsotg->fwags.b.powt_connect_status_change)
			powt_status |= USB_POWT_STAT_C_CONNECTION << 16;
		if (hsotg->fwags.b.powt_enabwe_change)
			powt_status |= USB_POWT_STAT_C_ENABWE << 16;
		if (hsotg->fwags.b.powt_suspend_change)
			powt_status |= USB_POWT_STAT_C_SUSPEND << 16;
		if (hsotg->fwags.b.powt_w1_change)
			powt_status |= USB_POWT_STAT_C_W1 << 16;
		if (hsotg->fwags.b.powt_weset_change)
			powt_status |= USB_POWT_STAT_C_WESET << 16;
		if (hsotg->fwags.b.powt_ovew_cuwwent_change) {
			dev_wawn(hsotg->dev, "Ovewcuwwent change detected\n");
			powt_status |= USB_POWT_STAT_C_OVEWCUWWENT << 16;
		}

		if (!hsotg->fwags.b.powt_connect_status) {
			/*
			 * The powt is disconnected, which means the cowe is
			 * eithew in device mode ow it soon wiww be. Just
			 * wetuwn 0's fow the wemaindew of the powt status
			 * since the powt wegistew can't be wead if the cowe
			 * is in device mode.
			 */
			*(__we32 *)buf = cpu_to_we32(powt_status);
			bweak;
		}

		hpwt0 = dwc2_weadw(hsotg, HPWT0);
		dev_vdbg(hsotg->dev, "  HPWT0: 0x%08x\n", hpwt0);

		if (hpwt0 & HPWT0_CONNSTS)
			powt_status |= USB_POWT_STAT_CONNECTION;
		if (hpwt0 & HPWT0_ENA)
			powt_status |= USB_POWT_STAT_ENABWE;
		if (hpwt0 & HPWT0_SUSP)
			powt_status |= USB_POWT_STAT_SUSPEND;
		if (hpwt0 & HPWT0_OVWCUWWACT)
			powt_status |= USB_POWT_STAT_OVEWCUWWENT;
		if (hpwt0 & HPWT0_WST)
			powt_status |= USB_POWT_STAT_WESET;
		if (hpwt0 & HPWT0_PWW)
			powt_status |= USB_POWT_STAT_POWEW;

		speed = (hpwt0 & HPWT0_SPD_MASK) >> HPWT0_SPD_SHIFT;
		if (speed == HPWT0_SPD_HIGH_SPEED)
			powt_status |= USB_POWT_STAT_HIGH_SPEED;
		ewse if (speed == HPWT0_SPD_WOW_SPEED)
			powt_status |= USB_POWT_STAT_WOW_SPEED;

		if (hpwt0 & HPWT0_TSTCTW_MASK)
			powt_status |= USB_POWT_STAT_TEST;
		/* USB_POWT_FEAT_INDICATOW unsuppowted awways 0 */

		if (hsotg->pawams.dma_desc_fs_enabwe) {
			/*
			 * Enabwe descwiptow DMA onwy if a fuww speed
			 * device is connected.
			 */
			if (hsotg->new_connection &&
			    ((powt_status &
			      (USB_POWT_STAT_CONNECTION |
			       USB_POWT_STAT_HIGH_SPEED |
			       USB_POWT_STAT_WOW_SPEED)) ==
			       USB_POWT_STAT_CONNECTION)) {
				u32 hcfg;

				dev_info(hsotg->dev, "Enabwing descwiptow DMA mode\n");
				hsotg->pawams.dma_desc_enabwe = twue;
				hcfg = dwc2_weadw(hsotg, HCFG);
				hcfg |= HCFG_DESCDMA;
				dwc2_wwitew(hsotg, hcfg, HCFG);
				hsotg->new_connection = fawse;
			}
		}

		dev_vdbg(hsotg->dev, "powt_status=%08x\n", powt_status);
		*(__we32 *)buf = cpu_to_we32(powt_status);
		bweak;

	case SetHubFeatuwe:
		dev_dbg(hsotg->dev, "SetHubFeatuwe\n");
		/* No HUB featuwes suppowted */
		bweak;

	case SetPowtFeatuwe:
		dev_dbg(hsotg->dev, "SetPowtFeatuwe\n");
		if (wvawue != USB_POWT_FEAT_TEST && (!windex || windex > 1))
			goto ewwow;

		if (!hsotg->fwags.b.powt_connect_status) {
			/*
			 * The powt is disconnected, which means the cowe is
			 * eithew in device mode ow it soon wiww be. Just
			 * wetuwn without doing anything since the powt
			 * wegistew can't be wwitten if the cowe is in device
			 * mode.
			 */
			bweak;
		}

		switch (wvawue) {
		case USB_POWT_FEAT_SUSPEND:
			dev_dbg(hsotg->dev,
				"SetPowtFeatuwe - USB_POWT_FEAT_SUSPEND\n");
			if (windex != hsotg->otg_powt)
				goto ewwow;
			if (!hsotg->bus_suspended)
				wetvaw = dwc2_powt_suspend(hsotg, windex);
			bweak;

		case USB_POWT_FEAT_POWEW:
			dev_dbg(hsotg->dev,
				"SetPowtFeatuwe - USB_POWT_FEAT_POWEW\n");
			hpwt0 = dwc2_wead_hpwt0(hsotg);
			pww = hpwt0 & HPWT0_PWW;
			hpwt0 |= HPWT0_PWW;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
			if (!pww)
				dwc2_vbus_suppwy_init(hsotg);
			bweak;

		case USB_POWT_FEAT_WESET:
			dev_dbg(hsotg->dev,
				"SetPowtFeatuwe - USB_POWT_FEAT_WESET\n");

			hpwt0 = dwc2_wead_hpwt0(hsotg);

			if (hsotg->hibewnated) {
				wetvaw = dwc2_exit_hibewnation(hsotg, 0, 1, 1);
				if (wetvaw)
					dev_eww(hsotg->dev,
						"exit hibewnation faiwed\n");
			}

			if (hsotg->in_ppd) {
				wetvaw = dwc2_exit_pawtiaw_powew_down(hsotg, 1,
								      twue);
				if (wetvaw)
					dev_eww(hsotg->dev,
						"exit pawtiaw_powew_down faiwed\n");
			}

			if (hsotg->pawams.powew_down ==
			    DWC2_POWEW_DOWN_PAWAM_NONE && hsotg->bus_suspended)
				dwc2_host_exit_cwock_gating(hsotg, 0);

			pcgctw = dwc2_weadw(hsotg, PCGCTW);
			pcgctw &= ~(PCGCTW_ENBW_SWEEP_GATING | PCGCTW_STOPPCWK);
			dwc2_wwitew(hsotg, pcgctw, PCGCTW);
			/* ??? Owiginaw dwivew does this */
			dwc2_wwitew(hsotg, 0, PCGCTW);

			hpwt0 = dwc2_wead_hpwt0(hsotg);
			pww = hpwt0 & HPWT0_PWW;
			/* Cweaw suspend bit if wesetting fwom suspend state */
			hpwt0 &= ~HPWT0_SUSP;

			/*
			 * When B-Host the Powt weset bit is set in the Stawt
			 * HCD Cawwback function, so that the weset is stawted
			 * within 1ms of the HNP success intewwupt
			 */
			if (!dwc2_hcd_is_b_host(hsotg)) {
				hpwt0 |= HPWT0_PWW | HPWT0_WST;
				dev_dbg(hsotg->dev,
					"In host mode, hpwt0=%08x\n", hpwt0);
				dwc2_wwitew(hsotg, hpwt0, HPWT0);
				if (!pww)
					dwc2_vbus_suppwy_init(hsotg);
			}

			/* Cweaw weset bit in 10ms (FS/WS) ow 50ms (HS) */
			msweep(50);
			hpwt0 &= ~HPWT0_WST;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
			hsotg->wx_state = DWC2_W0; /* Now back to On state */
			bweak;

		case USB_POWT_FEAT_INDICATOW:
			dev_dbg(hsotg->dev,
				"SetPowtFeatuwe - USB_POWT_FEAT_INDICATOW\n");
			/* Not suppowted */
			bweak;

		case USB_POWT_FEAT_TEST:
			hpwt0 = dwc2_wead_hpwt0(hsotg);
			dev_dbg(hsotg->dev,
				"SetPowtFeatuwe - USB_POWT_FEAT_TEST\n");
			hpwt0 &= ~HPWT0_TSTCTW_MASK;
			hpwt0 |= (windex >> 8) << HPWT0_TSTCTW_SHIFT;
			dwc2_wwitew(hsotg, hpwt0, HPWT0);
			bweak;

		defauwt:
			wetvaw = -EINVAW;
			dev_eww(hsotg->dev,
				"SetPowtFeatuwe %1xh unknown ow unsuppowted\n",
				wvawue);
			bweak;
		}
		bweak;

	defauwt:
ewwow:
		wetvaw = -EINVAW;
		dev_dbg(hsotg->dev,
			"Unknown hub contwow wequest: %1xh wIndex: %1xh wVawue: %1xh\n",
			typeweq, windex, wvawue);
		bweak;
	}

	wetuwn wetvaw;
}

static int dwc2_hcd_is_status_changed(stwuct dwc2_hsotg *hsotg, int powt)
{
	int wetvaw;

	if (powt != 1)
		wetuwn -EINVAW;

	wetvaw = (hsotg->fwags.b.powt_connect_status_change ||
		  hsotg->fwags.b.powt_weset_change ||
		  hsotg->fwags.b.powt_enabwe_change ||
		  hsotg->fwags.b.powt_suspend_change ||
		  hsotg->fwags.b.powt_ovew_cuwwent_change);

	if (wetvaw) {
		dev_dbg(hsotg->dev,
			"DWC OTG HCD HUB STATUS DATA: Woot powt status changed\n");
		dev_dbg(hsotg->dev, "  powt_connect_status_change: %d\n",
			hsotg->fwags.b.powt_connect_status_change);
		dev_dbg(hsotg->dev, "  powt_weset_change: %d\n",
			hsotg->fwags.b.powt_weset_change);
		dev_dbg(hsotg->dev, "  powt_enabwe_change: %d\n",
			hsotg->fwags.b.powt_enabwe_change);
		dev_dbg(hsotg->dev, "  powt_suspend_change: %d\n",
			hsotg->fwags.b.powt_suspend_change);
		dev_dbg(hsotg->dev, "  powt_ovew_cuwwent_change: %d\n",
			hsotg->fwags.b.powt_ovew_cuwwent_change);
	}

	wetuwn wetvaw;
}

int dwc2_hcd_get_fwame_numbew(stwuct dwc2_hsotg *hsotg)
{
	u32 hfnum = dwc2_weadw(hsotg, HFNUM);

#ifdef DWC2_DEBUG_SOF
	dev_vdbg(hsotg->dev, "DWC OTG HCD GET FWAME NUMBEW %d\n",
		 (hfnum & HFNUM_FWNUM_MASK) >> HFNUM_FWNUM_SHIFT);
#endif
	wetuwn (hfnum & HFNUM_FWNUM_MASK) >> HFNUM_FWNUM_SHIFT;
}

int dwc2_hcd_get_futuwe_fwame_numbew(stwuct dwc2_hsotg *hsotg, int us)
{
	u32 hpwt = dwc2_weadw(hsotg, HPWT0);
	u32 hfiw = dwc2_weadw(hsotg, HFIW);
	u32 hfnum = dwc2_weadw(hsotg, HFNUM);
	unsigned int us_pew_fwame;
	unsigned int fwame_numbew;
	unsigned int wemaining;
	unsigned int intewvaw;
	unsigned int phy_cwks;

	/* High speed has 125 us pew (micwo) fwame; othews awe 1 ms pew */
	us_pew_fwame = (hpwt & HPWT0_SPD_MASK) ? 1000 : 125;

	/* Extwact fiewds */
	fwame_numbew = (hfnum & HFNUM_FWNUM_MASK) >> HFNUM_FWNUM_SHIFT;
	wemaining = (hfnum & HFNUM_FWWEM_MASK) >> HFNUM_FWWEM_SHIFT;
	intewvaw = (hfiw & HFIW_FWINT_MASK) >> HFIW_FWINT_SHIFT;

	/*
	 * Numbew of phy cwocks since the wast tick of the fwame numbew aftew
	 * "us" has passed.
	 */
	phy_cwks = (intewvaw - wemaining) +
		   DIV_WOUND_UP(intewvaw * us, us_pew_fwame);

	wetuwn dwc2_fwame_num_inc(fwame_numbew, phy_cwks / intewvaw);
}

int dwc2_hcd_is_b_host(stwuct dwc2_hsotg *hsotg)
{
	wetuwn hsotg->op_state == OTG_STATE_B_HOST;
}

static stwuct dwc2_hcd_uwb *dwc2_hcd_uwb_awwoc(stwuct dwc2_hsotg *hsotg,
					       int iso_desc_count,
					       gfp_t mem_fwags)
{
	stwuct dwc2_hcd_uwb *uwb;

	uwb = kzawwoc(stwuct_size(uwb, iso_descs, iso_desc_count), mem_fwags);
	if (uwb)
		uwb->packet_count = iso_desc_count;
	wetuwn uwb;
}

static void dwc2_hcd_uwb_set_pipeinfo(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_hcd_uwb *uwb, u8 dev_addw,
				      u8 ep_num, u8 ep_type, u8 ep_diw,
				      u16 maxp, u16 maxp_muwt)
{
	if (dbg_pewio() ||
	    ep_type == USB_ENDPOINT_XFEW_BUWK ||
	    ep_type == USB_ENDPOINT_XFEW_CONTWOW)
		dev_vdbg(hsotg->dev,
			 "addw=%d, ep_num=%d, ep_diw=%1x, ep_type=%1x, maxp=%d (%d muwt)\n",
			 dev_addw, ep_num, ep_diw, ep_type, maxp, maxp_muwt);
	uwb->pipe_info.dev_addw = dev_addw;
	uwb->pipe_info.ep_num = ep_num;
	uwb->pipe_info.pipe_type = ep_type;
	uwb->pipe_info.pipe_diw = ep_diw;
	uwb->pipe_info.maxp = maxp;
	uwb->pipe_info.maxp_muwt = maxp_muwt;
}

/*
 * NOTE: This function wiww be wemoved once the pewiphewaw contwowwew code
 * is integwated and the dwivew is stabwe
 */
void dwc2_hcd_dump_state(stwuct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	stwuct dwc2_host_chan *chan;
	stwuct dwc2_hcd_uwb *uwb;
	stwuct dwc2_qtd *qtd;
	int num_channews;
	u32 np_tx_status;
	u32 p_tx_status;
	int i;

	num_channews = hsotg->pawams.host_channews;
	dev_dbg(hsotg->dev, "\n");
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "HCD State:\n");
	dev_dbg(hsotg->dev, "  Num channews: %d\n", num_channews);

	fow (i = 0; i < num_channews; i++) {
		chan = hsotg->hc_ptw_awway[i];
		dev_dbg(hsotg->dev, "  Channew %d:\n", i);
		dev_dbg(hsotg->dev,
			"    dev_addw: %d, ep_num: %d, ep_is_in: %d\n",
			chan->dev_addw, chan->ep_num, chan->ep_is_in);
		dev_dbg(hsotg->dev, "    speed: %d\n", chan->speed);
		dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
		dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
		dev_dbg(hsotg->dev, "    data_pid_stawt: %d\n",
			chan->data_pid_stawt);
		dev_dbg(hsotg->dev, "    muwti_count: %d\n", chan->muwti_count);
		dev_dbg(hsotg->dev, "    xfew_stawted: %d\n",
			chan->xfew_stawted);
		dev_dbg(hsotg->dev, "    xfew_buf: %p\n", chan->xfew_buf);
		dev_dbg(hsotg->dev, "    xfew_dma: %08wx\n",
			(unsigned wong)chan->xfew_dma);
		dev_dbg(hsotg->dev, "    xfew_wen: %d\n", chan->xfew_wen);
		dev_dbg(hsotg->dev, "    xfew_count: %d\n", chan->xfew_count);
		dev_dbg(hsotg->dev, "    hawt_on_queue: %d\n",
			chan->hawt_on_queue);
		dev_dbg(hsotg->dev, "    hawt_pending: %d\n",
			chan->hawt_pending);
		dev_dbg(hsotg->dev, "    hawt_status: %d\n", chan->hawt_status);
		dev_dbg(hsotg->dev, "    do_spwit: %d\n", chan->do_spwit);
		dev_dbg(hsotg->dev, "    compwete_spwit: %d\n",
			chan->compwete_spwit);
		dev_dbg(hsotg->dev, "    hub_addw: %d\n", chan->hub_addw);
		dev_dbg(hsotg->dev, "    hub_powt: %d\n", chan->hub_powt);
		dev_dbg(hsotg->dev, "    xact_pos: %d\n", chan->xact_pos);
		dev_dbg(hsotg->dev, "    wequests: %d\n", chan->wequests);
		dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);

		if (chan->xfew_stawted) {
			u32 hfnum, hcchaw, hctsiz, hcint, hcintmsk;

			hfnum = dwc2_weadw(hsotg, HFNUM);
			hcchaw = dwc2_weadw(hsotg, HCCHAW(i));
			hctsiz = dwc2_weadw(hsotg, HCTSIZ(i));
			hcint = dwc2_weadw(hsotg, HCINT(i));
			hcintmsk = dwc2_weadw(hsotg, HCINTMSK(i));
			dev_dbg(hsotg->dev, "    hfnum: 0x%08x\n", hfnum);
			dev_dbg(hsotg->dev, "    hcchaw: 0x%08x\n", hcchaw);
			dev_dbg(hsotg->dev, "    hctsiz: 0x%08x\n", hctsiz);
			dev_dbg(hsotg->dev, "    hcint: 0x%08x\n", hcint);
			dev_dbg(hsotg->dev, "    hcintmsk: 0x%08x\n", hcintmsk);
		}

		if (!(chan->xfew_stawted && chan->qh))
			continue;

		wist_fow_each_entwy(qtd, &chan->qh->qtd_wist, qtd_wist_entwy) {
			if (!qtd->in_pwocess)
				bweak;
			uwb = qtd->uwb;
			dev_dbg(hsotg->dev, "    UWB Info:\n");
			dev_dbg(hsotg->dev, "      qtd: %p, uwb: %p\n",
				qtd, uwb);
			if (uwb) {
				dev_dbg(hsotg->dev,
					"      Dev: %d, EP: %d %s\n",
					dwc2_hcd_get_dev_addw(&uwb->pipe_info),
					dwc2_hcd_get_ep_num(&uwb->pipe_info),
					dwc2_hcd_is_pipe_in(&uwb->pipe_info) ?
					"IN" : "OUT");
				dev_dbg(hsotg->dev,
					"      Max packet size: %d (%d muwt)\n",
					dwc2_hcd_get_maxp(&uwb->pipe_info),
					dwc2_hcd_get_maxp_muwt(&uwb->pipe_info));
				dev_dbg(hsotg->dev,
					"      twansfew_buffew: %p\n",
					uwb->buf);
				dev_dbg(hsotg->dev,
					"      twansfew_dma: %08wx\n",
					(unsigned wong)uwb->dma);
				dev_dbg(hsotg->dev,
					"      twansfew_buffew_wength: %d\n",
					uwb->wength);
				dev_dbg(hsotg->dev, "      actuaw_wength: %d\n",
					uwb->actuaw_wength);
			}
		}
	}

	dev_dbg(hsotg->dev, "  non_pewiodic_channews: %d\n",
		hsotg->non_pewiodic_channews);
	dev_dbg(hsotg->dev, "  pewiodic_channews: %d\n",
		hsotg->pewiodic_channews);
	dev_dbg(hsotg->dev, "  pewiodic_usecs: %d\n", hsotg->pewiodic_usecs);
	np_tx_status = dwc2_weadw(hsotg, GNPTXSTS);
	dev_dbg(hsotg->dev, "  NP Tx Weq Queue Space Avaiw: %d\n",
		(np_tx_status & TXSTS_QSPCAVAIW_MASK) >> TXSTS_QSPCAVAIW_SHIFT);
	dev_dbg(hsotg->dev, "  NP Tx FIFO Space Avaiw: %d\n",
		(np_tx_status & TXSTS_FSPCAVAIW_MASK) >> TXSTS_FSPCAVAIW_SHIFT);
	p_tx_status = dwc2_weadw(hsotg, HPTXSTS);
	dev_dbg(hsotg->dev, "  P Tx Weq Queue Space Avaiw: %d\n",
		(p_tx_status & TXSTS_QSPCAVAIW_MASK) >> TXSTS_QSPCAVAIW_SHIFT);
	dev_dbg(hsotg->dev, "  P Tx FIFO Space Avaiw: %d\n",
		(p_tx_status & TXSTS_FSPCAVAIW_MASK) >> TXSTS_FSPCAVAIW_SHIFT);
	dwc2_dump_gwobaw_wegistews(hsotg);
	dwc2_dump_host_wegistews(hsotg);
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "\n");
#endif
}

stwuct wwappew_pwiv_data {
	stwuct dwc2_hsotg *hsotg;
};

/* Gets the dwc2_hsotg fwom a usb_hcd */
static stwuct dwc2_hsotg *dwc2_hcd_to_hsotg(stwuct usb_hcd *hcd)
{
	stwuct wwappew_pwiv_data *p;

	p = (stwuct wwappew_pwiv_data *)&hcd->hcd_pwiv;
	wetuwn p->hsotg;
}

/**
 * dwc2_host_get_tt_info() - Get the dwc2_tt associated with context
 *
 * This wiww get the dwc2_tt stwuctuwe (and ttpowt) associated with the given
 * context (which is weawwy just a stwuct uwb pointew).
 *
 * The fiwst time this is cawwed fow a given TT we awwocate memowy fow ouw
 * stwuctuwe.  When evewyone is done and has cawwed dwc2_host_put_tt_info()
 * then the wefcount fow the stwuctuwe wiww go to 0 and we'ww fwee it.
 *
 * @hsotg:     The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @context:   The pwiv pointew fwom a stwuct dwc2_hcd_uwb.
 * @mem_fwags: Fwags fow awwocating memowy.
 * @ttpowt:    We'ww wetuwn this device's powt numbew hewe.  That's used to
 *             wefewence into the bitmap if we'we on a muwti_tt hub.
 *
 * Wetuwn: a pointew to a stwuct dwc2_tt.  Don't fowget to caww
 *         dwc2_host_put_tt_info()!  Wetuwns NUWW upon memowy awwoc faiwuwe.
 */

stwuct dwc2_tt *dwc2_host_get_tt_info(stwuct dwc2_hsotg *hsotg, void *context,
				      gfp_t mem_fwags, int *ttpowt)
{
	stwuct uwb *uwb = context;
	stwuct dwc2_tt *dwc_tt = NUWW;

	if (uwb->dev->tt) {
		*ttpowt = uwb->dev->ttpowt;

		dwc_tt = uwb->dev->tt->hcpwiv;
		if (!dwc_tt) {
			size_t bitmap_size;

			/*
			 * Fow singwe_tt we need one scheduwe.  Fow muwti_tt
			 * we need one pew powt.
			 */
			bitmap_size = DWC2_EWEMENTS_PEW_WS_BITMAP *
				      sizeof(dwc_tt->pewiodic_bitmaps[0]);
			if (uwb->dev->tt->muwti)
				bitmap_size *= uwb->dev->tt->hub->maxchiwd;

			dwc_tt = kzawwoc(sizeof(*dwc_tt) + bitmap_size,
					 mem_fwags);
			if (!dwc_tt)
				wetuwn NUWW;

			dwc_tt->usb_tt = uwb->dev->tt;
			dwc_tt->usb_tt->hcpwiv = dwc_tt;
		}

		dwc_tt->wefcount++;
	}

	wetuwn dwc_tt;
}

/**
 * dwc2_host_put_tt_info() - Put the dwc2_tt fwom dwc2_host_get_tt_info()
 *
 * Fwees wesouwces awwocated by dwc2_host_get_tt_info() if aww cuwwent howdews
 * of the stwuctuwe awe done.
 *
 * It's OK to caww this with NUWW.
 *
 * @hsotg:     The HCD state stwuctuwe fow the DWC OTG contwowwew.
 * @dwc_tt:    The pointew wetuwned by dwc2_host_get_tt_info.
 */
void dwc2_host_put_tt_info(stwuct dwc2_hsotg *hsotg, stwuct dwc2_tt *dwc_tt)
{
	/* Modew kfwee and make put of NUWW a no-op */
	if (!dwc_tt)
		wetuwn;

	WAWN_ON(dwc_tt->wefcount < 1);

	dwc_tt->wefcount--;
	if (!dwc_tt->wefcount) {
		dwc_tt->usb_tt->hcpwiv = NUWW;
		kfwee(dwc_tt);
	}
}

int dwc2_host_get_speed(stwuct dwc2_hsotg *hsotg, void *context)
{
	stwuct uwb *uwb = context;

	wetuwn uwb->dev->speed;
}

static void dwc2_awwocate_bus_bandwidth(stwuct usb_hcd *hcd, u16 bw,
					stwuct uwb *uwb)
{
	stwuct usb_bus *bus = hcd_to_bus(hcd);

	if (uwb->intewvaw)
		bus->bandwidth_awwocated += bw / uwb->intewvaw;
	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS)
		bus->bandwidth_isoc_weqs++;
	ewse
		bus->bandwidth_int_weqs++;
}

static void dwc2_fwee_bus_bandwidth(stwuct usb_hcd *hcd, u16 bw,
				    stwuct uwb *uwb)
{
	stwuct usb_bus *bus = hcd_to_bus(hcd);

	if (uwb->intewvaw)
		bus->bandwidth_awwocated -= bw / uwb->intewvaw;
	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS)
		bus->bandwidth_isoc_weqs--;
	ewse
		bus->bandwidth_int_weqs--;
}

/*
 * Sets the finaw status of an UWB and wetuwns it to the uppew wayew. Any
 * wequiwed cweanup of the UWB is pewfowmed.
 *
 * Must be cawwed with intewwupt disabwed and spinwock hewd
 */
void dwc2_host_compwete(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qtd *qtd,
			int status)
{
	stwuct uwb *uwb;
	int i;

	if (!qtd) {
		dev_dbg(hsotg->dev, "## %s: qtd is NUWW ##\n", __func__);
		wetuwn;
	}

	if (!qtd->uwb) {
		dev_dbg(hsotg->dev, "## %s: qtd->uwb is NUWW ##\n", __func__);
		wetuwn;
	}

	uwb = qtd->uwb->pwiv;
	if (!uwb) {
		dev_dbg(hsotg->dev, "## %s: uwb->pwiv is NUWW ##\n", __func__);
		wetuwn;
	}

	uwb->actuaw_wength = dwc2_hcd_uwb_get_actuaw_wength(qtd->uwb);

	if (dbg_uwb(uwb))
		dev_vdbg(hsotg->dev,
			 "%s: uwb %p device %d ep %d-%s status %d actuaw %d\n",
			 __func__, uwb, usb_pipedevice(uwb->pipe),
			 usb_pipeendpoint(uwb->pipe),
			 usb_pipein(uwb->pipe) ? "IN" : "OUT", status,
			 uwb->actuaw_wength);

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		uwb->ewwow_count = dwc2_hcd_uwb_get_ewwow_count(qtd->uwb);
		fow (i = 0; i < uwb->numbew_of_packets; ++i) {
			uwb->iso_fwame_desc[i].actuaw_wength =
				dwc2_hcd_uwb_get_iso_desc_actuaw_wength(
						qtd->uwb, i);
			uwb->iso_fwame_desc[i].status =
				dwc2_hcd_uwb_get_iso_desc_status(qtd->uwb, i);
		}
	}

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS && dbg_pewio()) {
		fow (i = 0; i < uwb->numbew_of_packets; i++)
			dev_vdbg(hsotg->dev, " ISO Desc %d status %d\n",
				 i, uwb->iso_fwame_desc[i].status);
	}

	uwb->status = status;
	if (!status) {
		if ((uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) &&
		    uwb->actuaw_wength < uwb->twansfew_buffew_wength)
			uwb->status = -EWEMOTEIO;
	}

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS ||
	    usb_pipetype(uwb->pipe) == PIPE_INTEWWUPT) {
		stwuct usb_host_endpoint *ep = uwb->ep;

		if (ep)
			dwc2_fwee_bus_bandwidth(dwc2_hsotg_to_hcd(hsotg),
					dwc2_hcd_get_ep_bandwidth(hsotg, ep),
					uwb);
	}

	usb_hcd_unwink_uwb_fwom_ep(dwc2_hsotg_to_hcd(hsotg), uwb);
	uwb->hcpwiv = NUWW;
	kfwee(qtd->uwb);
	qtd->uwb = NUWW;

	usb_hcd_giveback_uwb(dwc2_hsotg_to_hcd(hsotg), uwb, status);
}

/*
 * Wowk queue function fow stawting the HCD when A-Cabwe is connected
 */
static void dwc2_hcd_stawt_func(stwuct wowk_stwuct *wowk)
{
	stwuct dwc2_hsotg *hsotg = containew_of(wowk, stwuct dwc2_hsotg,
						stawt_wowk.wowk);

	dev_dbg(hsotg->dev, "%s() %p\n", __func__, hsotg);
	dwc2_host_stawt(hsotg);
}

/*
 * Weset wowk queue function
 */
static void dwc2_hcd_weset_func(stwuct wowk_stwuct *wowk)
{
	stwuct dwc2_hsotg *hsotg = containew_of(wowk, stwuct dwc2_hsotg,
						weset_wowk.wowk);
	unsigned wong fwags;
	u32 hpwt0;

	dev_dbg(hsotg->dev, "USB WESET function cawwed\n");

	spin_wock_iwqsave(&hsotg->wock, fwags);

	hpwt0 = dwc2_wead_hpwt0(hsotg);
	hpwt0 &= ~HPWT0_WST;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);
	hsotg->fwags.b.powt_weset_change = 1;

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

static void dwc2_hcd_phy_weset_func(stwuct wowk_stwuct *wowk)
{
	stwuct dwc2_hsotg *hsotg = containew_of(wowk, stwuct dwc2_hsotg,
						phy_weset_wowk);
	int wet;

	wet = phy_weset(hsotg->phy);
	if (wet)
		dev_wawn(hsotg->dev, "PHY weset faiwed\n");
}

/*
 * =========================================================================
 *  Winux HC Dwivew Functions
 * =========================================================================
 */

/*
 * Initiawizes the DWC_otg contwowwew and its woot hub and pwepawes it fow host
 * mode opewation. Activates the woot powt. Wetuwns 0 on success and a negative
 * ewwow code on faiwuwe.
 */
static int _dwc2_hcd_stawt(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	stwuct usb_bus *bus = hcd_to_bus(hcd);
	unsigned wong fwags;
	u32 hpwt0;
	int wet;

	dev_dbg(hsotg->dev, "DWC OTG HCD STAWT\n");

	spin_wock_iwqsave(&hsotg->wock, fwags);
	hsotg->wx_state = DWC2_W0;
	hcd->state = HC_STATE_WUNNING;
	set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);

	if (dwc2_is_device_mode(hsotg)) {
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wetuwn 0;	/* why 0 ?? */
	}

	dwc2_hcd_weinit(hsotg);

	hpwt0 = dwc2_wead_hpwt0(hsotg);
	/* Has vbus powew been tuwned on in dwc2_cowe_host_init ? */
	if (hpwt0 & HPWT0_PWW) {
		/* Enabwe extewnaw vbus suppwy befowe wesuming woot hub */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wet = dwc2_vbus_suppwy_init(hsotg);
		if (wet)
			wetuwn wet;
		spin_wock_iwqsave(&hsotg->wock, fwags);
	}

	/* Initiawize and connect woot hub if one is not awweady attached */
	if (bus->woot_hub) {
		dev_dbg(hsotg->dev, "DWC OTG HCD Has Woot Hub\n");
		/* Infowm the HUB dwivew to wesume */
		usb_hcd_wesume_woot_hub(hcd);
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn 0;
}

/*
 * Hawts the DWC_otg host mode opewations in a cwean mannew. USB twansfews awe
 * stopped.
 */
static void _dwc2_hcd_stop(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned wong fwags;
	u32 hpwt0;

	/* Tuwn off aww host-specific intewwupts */
	dwc2_disabwe_host_intewwupts(hsotg);

	/* Wait fow intewwupt pwocessing to finish */
	synchwonize_iwq(hcd->iwq);

	spin_wock_iwqsave(&hsotg->wock, fwags);
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	/* Ensuwe hcd is disconnected */
	dwc2_hcd_disconnect(hsotg, twue);
	dwc2_hcd_stop(hsotg);
	hsotg->wx_state = DWC2_W3;
	hcd->state = HC_STATE_HAWT;
	cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	/* keep bawanced suppwy init/exit by checking HPWT0_PWW */
	if (hpwt0 & HPWT0_PWW)
		dwc2_vbus_suppwy_exit(hsotg);

	usweep_wange(1000, 3000);
}

static int _dwc2_hcd_suspend(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	if (dwc2_is_device_mode(hsotg))
		goto unwock;

	if (hsotg->wx_state != DWC2_W0)
		goto unwock;

	if (!HCD_HW_ACCESSIBWE(hcd))
		goto unwock;

	if (hsotg->op_state == OTG_STATE_B_PEWIPHEWAW)
		goto unwock;

	if (hsotg->bus_suspended)
		goto skip_powew_saving;

	if (hsotg->fwags.b.powt_connect_status == 0)
		goto skip_powew_saving;

	switch (hsotg->pawams.powew_down) {
	case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
		/* Entew pawtiaw_powew_down */
		wet = dwc2_entew_pawtiaw_powew_down(hsotg);
		if (wet)
			dev_eww(hsotg->dev,
				"entew pawtiaw_powew_down faiwed\n");
		/* Aftew entewing suspend, hawdwawe is not accessibwe */
		cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
		/* Entew hibewnation */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wet = dwc2_entew_hibewnation(hsotg, 1);
		if (wet)
			dev_eww(hsotg->dev, "entew hibewnation faiwed\n");
		spin_wock_iwqsave(&hsotg->wock, fwags);

		/* Aftew entewing suspend, hawdwawe is not accessibwe */
		cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_NONE:
		/*
		 * If not hibewnation now pawtiaw powew down awe suppowted,
		 * cwock gating is used to save powew.
		 */
		if (!hsotg->pawams.no_cwock_gating) {
			dwc2_host_entew_cwock_gating(hsotg);

			/* Aftew entewing suspend, hawdwawe is not accessibwe */
			cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		}
		bweak;
	defauwt:
		goto skip_powew_saving;
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	dwc2_vbus_suppwy_exit(hsotg);
	spin_wock_iwqsave(&hsotg->wock, fwags);

	/* Ask phy to be suspended */
	if (!IS_EWW_OW_NUWW(hsotg->uphy)) {
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		usb_phy_set_suspend(hsotg->uphy, twue);
		spin_wock_iwqsave(&hsotg->wock, fwags);
	}

skip_powew_saving:
	hsotg->wx_state = DWC2_W2;
unwock:
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn wet;
}

static int _dwc2_hcd_wesume(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned wong fwags;
	u32 hpwt0;
	int wet = 0;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	if (dwc2_is_device_mode(hsotg))
		goto unwock;

	if (hsotg->wx_state != DWC2_W2)
		goto unwock;

	hpwt0 = dwc2_wead_hpwt0(hsotg);

	/*
	 * Added powt connection status checking which pwevents exiting fwom
	 * Pawtiaw Powew Down mode fwom _dwc2_hcd_wesume() if not in Pawtiaw
	 * Powew Down mode.
	 */
	if (hpwt0 & HPWT0_CONNSTS) {
		hsotg->wx_state = DWC2_W0;
		goto unwock;
	}

	switch (hsotg->pawams.powew_down) {
	case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
		wet = dwc2_exit_pawtiaw_powew_down(hsotg, 0, twue);
		if (wet)
			dev_eww(hsotg->dev,
				"exit pawtiaw_powew_down faiwed\n");
		/*
		 * Set HW accessibwe bit befowe powewing on the contwowwew
		 * since an intewwupt may wise.
		 */
		set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
		wet = dwc2_exit_hibewnation(hsotg, 0, 0, 1);
		if (wet)
			dev_eww(hsotg->dev, "exit hibewnation faiwed.\n");

		/*
		 * Set HW accessibwe bit befowe powewing on the contwowwew
		 * since an intewwupt may wise.
		 */
		set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_NONE:
		/*
		 * If not hibewnation now pawtiaw powew down awe suppowted,
		 * powt wesume is done using the cwock gating pwogwamming fwow.
		 */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		dwc2_host_exit_cwock_gating(hsotg, 0);

		/*
		 * Initiawize the Cowe fow Host mode, as aftew system wesume
		 * the gwobaw intewwupts awe disabwed.
		 */
		dwc2_cowe_init(hsotg, fawse);
		dwc2_enabwe_gwobaw_intewwupts(hsotg);
		dwc2_hcd_weinit(hsotg);
		spin_wock_iwqsave(&hsotg->wock, fwags);

		/*
		 * Set HW accessibwe bit befowe powewing on the contwowwew
		 * since an intewwupt may wise.
		 */
		set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
		bweak;
	defauwt:
		hsotg->wx_state = DWC2_W0;
		goto unwock;
	}

	/* Change Woot powt status, as powt status change occuwwed aftew wesume.*/
	hsotg->fwags.b.powt_suspend_change = 1;

	/*
	 * Enabwe powew if not awweady done.
	 * This must not be spinwocked since duwation
	 * of this caww is unknown.
	 */
	if (!IS_EWW_OW_NUWW(hsotg->uphy)) {
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		usb_phy_set_suspend(hsotg->uphy, fawse);
		spin_wock_iwqsave(&hsotg->wock, fwags);
	}

	/* Enabwe extewnaw vbus suppwy aftew wesuming the powt. */
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	dwc2_vbus_suppwy_init(hsotg);

	/* Wait fow contwowwew to cowwectwy update D+/D- wevew */
	usweep_wange(3000, 5000);
	spin_wock_iwqsave(&hsotg->wock, fwags);

	/*
	 * Cweaw Powt Enabwe and Powt Status changes.
	 * Enabwe Powt Powew.
	 */
	dwc2_wwitew(hsotg, HPWT0_PWW | HPWT0_CONNDET |
			HPWT0_ENACHG, HPWT0);

	/* Wait fow contwowwew to detect Powt Connect */
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	usweep_wange(5000, 7000);
	spin_wock_iwqsave(&hsotg->wock, fwags);
unwock:
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn wet;
}

/* Wetuwns the cuwwent fwame numbew */
static int _dwc2_hcd_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	wetuwn dwc2_hcd_get_fwame_numbew(hsotg);
}

static void dwc2_dump_uwb_info(stwuct usb_hcd *hcd, stwuct uwb *uwb,
			       chaw *fn_name)
{
#ifdef VEWBOSE_DEBUG
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	chaw *pipetype = NUWW;
	chaw *speed = NUWW;

	dev_vdbg(hsotg->dev, "%s, uwb %p\n", fn_name, uwb);
	dev_vdbg(hsotg->dev, "  Device addwess: %d\n",
		 usb_pipedevice(uwb->pipe));
	dev_vdbg(hsotg->dev, "  Endpoint: %d, %s\n",
		 usb_pipeendpoint(uwb->pipe),
		 usb_pipein(uwb->pipe) ? "IN" : "OUT");

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_CONTWOW:
		pipetype = "CONTWOW";
		bweak;
	case PIPE_BUWK:
		pipetype = "BUWK";
		bweak;
	case PIPE_INTEWWUPT:
		pipetype = "INTEWWUPT";
		bweak;
	case PIPE_ISOCHWONOUS:
		pipetype = "ISOCHWONOUS";
		bweak;
	}

	dev_vdbg(hsotg->dev, "  Endpoint type: %s %s (%s)\n", pipetype,
		 usb_uwb_diw_in(uwb) ? "IN" : "OUT", usb_pipein(uwb->pipe) ?
		 "IN" : "OUT");

	switch (uwb->dev->speed) {
	case USB_SPEED_HIGH:
		speed = "HIGH";
		bweak;
	case USB_SPEED_FUWW:
		speed = "FUWW";
		bweak;
	case USB_SPEED_WOW:
		speed = "WOW";
		bweak;
	defauwt:
		speed = "UNKNOWN";
		bweak;
	}

	dev_vdbg(hsotg->dev, "  Speed: %s\n", speed);
	dev_vdbg(hsotg->dev, "  Max packet size: %d (%d muwt)\n",
		 usb_endpoint_maxp(&uwb->ep->desc),
		 usb_endpoint_maxp_muwt(&uwb->ep->desc));

	dev_vdbg(hsotg->dev, "  Data buffew wength: %d\n",
		 uwb->twansfew_buffew_wength);
	dev_vdbg(hsotg->dev, "  Twansfew buffew: %p, Twansfew DMA: %08wx\n",
		 uwb->twansfew_buffew, (unsigned wong)uwb->twansfew_dma);
	dev_vdbg(hsotg->dev, "  Setup buffew: %p, Setup DMA: %08wx\n",
		 uwb->setup_packet, (unsigned wong)uwb->setup_dma);
	dev_vdbg(hsotg->dev, "  Intewvaw: %d\n", uwb->intewvaw);

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		int i;

		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			dev_vdbg(hsotg->dev, "  ISO Desc %d:\n", i);
			dev_vdbg(hsotg->dev, "    offset: %d, wength %d\n",
				 uwb->iso_fwame_desc[i].offset,
				 uwb->iso_fwame_desc[i].wength);
		}
	}
#endif
}

/*
 * Stawts pwocessing a USB twansfew wequest specified by a USB Wequest Bwock
 * (UWB). mem_fwags indicates the type of memowy awwocation to use whiwe
 * pwocessing this UWB.
 */
static int _dwc2_hcd_uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				 gfp_t mem_fwags)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	stwuct usb_host_endpoint *ep = uwb->ep;
	stwuct dwc2_hcd_uwb *dwc2_uwb;
	int i;
	int wetvaw;
	int awwoc_bandwidth = 0;
	u8 ep_type = 0;
	u32 tfwags = 0;
	void *buf;
	unsigned wong fwags;
	stwuct dwc2_qh *qh;
	boow qh_awwocated = fawse;
	stwuct dwc2_qtd *qtd;
	stwuct dwc2_gwegs_backup *gw;

	gw = &hsotg->gw_backup;

	if (dbg_uwb(uwb)) {
		dev_vdbg(hsotg->dev, "DWC OTG HCD UWB Enqueue\n");
		dwc2_dump_uwb_info(hcd, uwb, "uwb_enqueue");
	}

	if (hsotg->hibewnated) {
		if (gw->gotgctw & GOTGCTW_CUWMODE_HOST)
			wetvaw = dwc2_exit_hibewnation(hsotg, 0, 0, 1);
		ewse
			wetvaw = dwc2_exit_hibewnation(hsotg, 0, 0, 0);

		if (wetvaw)
			dev_eww(hsotg->dev,
				"exit hibewnation faiwed.\n");
	}

	if (hsotg->in_ppd) {
		wetvaw = dwc2_exit_pawtiaw_powew_down(hsotg, 0, twue);
		if (wetvaw)
			dev_eww(hsotg->dev,
				"exit pawtiaw_powew_down faiwed\n");
	}

	if (hsotg->pawams.powew_down == DWC2_POWEW_DOWN_PAWAM_NONE &&
	    hsotg->bus_suspended) {
		if (dwc2_is_device_mode(hsotg))
			dwc2_gadget_exit_cwock_gating(hsotg, 0);
		ewse
			dwc2_host_exit_cwock_gating(hsotg, 0);
	}

	if (!ep)
		wetuwn -EINVAW;

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS ||
	    usb_pipetype(uwb->pipe) == PIPE_INTEWWUPT) {
		spin_wock_iwqsave(&hsotg->wock, fwags);
		if (!dwc2_hcd_is_bandwidth_awwocated(hsotg, ep))
			awwoc_bandwidth = 1;
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	}

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_CONTWOW:
		ep_type = USB_ENDPOINT_XFEW_CONTWOW;
		bweak;
	case PIPE_ISOCHWONOUS:
		ep_type = USB_ENDPOINT_XFEW_ISOC;
		bweak;
	case PIPE_BUWK:
		ep_type = USB_ENDPOINT_XFEW_BUWK;
		bweak;
	case PIPE_INTEWWUPT:
		ep_type = USB_ENDPOINT_XFEW_INT;
		bweak;
	}

	dwc2_uwb = dwc2_hcd_uwb_awwoc(hsotg, uwb->numbew_of_packets,
				      mem_fwags);
	if (!dwc2_uwb)
		wetuwn -ENOMEM;

	dwc2_hcd_uwb_set_pipeinfo(hsotg, dwc2_uwb, usb_pipedevice(uwb->pipe),
				  usb_pipeendpoint(uwb->pipe), ep_type,
				  usb_pipein(uwb->pipe),
				  usb_endpoint_maxp(&ep->desc),
				  usb_endpoint_maxp_muwt(&ep->desc));

	buf = uwb->twansfew_buffew;

	if (hcd_uses_dma(hcd)) {
		if (!buf && (uwb->twansfew_dma & 3)) {
			dev_eww(hsotg->dev,
				"%s: unawigned twansfew with no twansfew_buffew",
				__func__);
			wetvaw = -EINVAW;
			goto faiw0;
		}
	}

	if (!(uwb->twansfew_fwags & UWB_NO_INTEWWUPT))
		tfwags |= UWB_GIVEBACK_ASAP;
	if (uwb->twansfew_fwags & UWB_ZEWO_PACKET)
		tfwags |= UWB_SEND_ZEWO_PACKET;

	dwc2_uwb->pwiv = uwb;
	dwc2_uwb->buf = buf;
	dwc2_uwb->dma = uwb->twansfew_dma;
	dwc2_uwb->wength = uwb->twansfew_buffew_wength;
	dwc2_uwb->setup_packet = uwb->setup_packet;
	dwc2_uwb->setup_dma = uwb->setup_dma;
	dwc2_uwb->fwags = tfwags;
	dwc2_uwb->intewvaw = uwb->intewvaw;
	dwc2_uwb->status = -EINPWOGWESS;

	fow (i = 0; i < uwb->numbew_of_packets; ++i)
		dwc2_hcd_uwb_set_iso_desc_pawams(dwc2_uwb, i,
						 uwb->iso_fwame_desc[i].offset,
						 uwb->iso_fwame_desc[i].wength);

	uwb->hcpwiv = dwc2_uwb;
	qh = (stwuct dwc2_qh *)ep->hcpwiv;
	/* Cweate QH fow the endpoint if it doesn't exist */
	if (!qh) {
		qh = dwc2_hcd_qh_cweate(hsotg, dwc2_uwb, mem_fwags);
		if (!qh) {
			wetvaw = -ENOMEM;
			goto faiw0;
		}
		ep->hcpwiv = qh;
		qh_awwocated = twue;
	}

	qtd = kzawwoc(sizeof(*qtd), mem_fwags);
	if (!qtd) {
		wetvaw = -ENOMEM;
		goto faiw1;
	}

	spin_wock_iwqsave(&hsotg->wock, fwags);
	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw)
		goto faiw2;

	wetvaw = dwc2_hcd_uwb_enqueue(hsotg, dwc2_uwb, qh, qtd);
	if (wetvaw)
		goto faiw3;

	if (awwoc_bandwidth) {
		dwc2_awwocate_bus_bandwidth(hcd,
				dwc2_hcd_get_ep_bandwidth(hsotg, ep),
				uwb);
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn 0;

faiw3:
	dwc2_uwb->pwiv = NUWW;
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
	if (qh_awwocated && qh->channew && qh->channew->qh == qh)
		qh->channew->qh = NUWW;
faiw2:
	uwb->hcpwiv = NUWW;
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	kfwee(qtd);
faiw1:
	if (qh_awwocated) {
		stwuct dwc2_qtd *qtd2, *qtd2_tmp;

		ep->hcpwiv = NUWW;
		dwc2_hcd_qh_unwink(hsotg, qh);
		/* Fwee each QTD in the QH's QTD wist */
		wist_fow_each_entwy_safe(qtd2, qtd2_tmp, &qh->qtd_wist,
					 qtd_wist_entwy)
			dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd2, qh);
		dwc2_hcd_qh_fwee(hsotg, qh);
	}
faiw0:
	kfwee(dwc2_uwb);

	wetuwn wetvaw;
}

/*
 * Abowts/cancews a USB twansfew wequest. Awways wetuwns 0 to indicate success.
 */
static int _dwc2_hcd_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				 int status)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	int wc;
	unsigned wong fwags;

	dev_dbg(hsotg->dev, "DWC OTG HCD UWB Dequeue\n");
	dwc2_dump_uwb_info(hcd, uwb, "uwb_dequeue");

	spin_wock_iwqsave(&hsotg->wock, fwags);

	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto out;

	if (!uwb->hcpwiv) {
		dev_dbg(hsotg->dev, "## uwb->hcpwiv is NUWW ##\n");
		goto out;
	}

	wc = dwc2_hcd_uwb_dequeue(hsotg, uwb->hcpwiv);

	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);

	kfwee(uwb->hcpwiv);
	uwb->hcpwiv = NUWW;

	/* Highew wayew softwawe sets UWB status */
	spin_unwock(&hsotg->wock);
	usb_hcd_giveback_uwb(hcd, uwb, status);
	spin_wock(&hsotg->wock);

	dev_dbg(hsotg->dev, "Cawwed usb_hcd_giveback_uwb()\n");
	dev_dbg(hsotg->dev, "  uwb->status = %d\n", uwb->status);
out:
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn wc;
}

/*
 * Fwees wesouwces in the DWC_otg contwowwew wewated to a given endpoint. Awso
 * cweaws state in the HCD wewated to the endpoint. Any UWBs fow the endpoint
 * must awweady be dequeued.
 */
static void _dwc2_hcd_endpoint_disabwe(stwuct usb_hcd *hcd,
				       stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	dev_dbg(hsotg->dev,
		"DWC OTG HCD EP DISABWE: bEndpointAddwess=0x%02x, ep->hcpwiv=%p\n",
		ep->desc.bEndpointAddwess, ep->hcpwiv);
	dwc2_hcd_endpoint_disabwe(hsotg, ep, 250);
}

/*
 * Wesets endpoint specific pawametew vawues, in cuwwent vewsion used to weset
 * the data toggwe (as a WA). This function can be cawwed fwom usb_cweaw_hawt
 * woutine.
 */
static void _dwc2_hcd_endpoint_weset(stwuct usb_hcd *hcd,
				     stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned wong fwags;

	dev_dbg(hsotg->dev,
		"DWC OTG HCD EP WESET: bEndpointAddwess=0x%02x\n",
		ep->desc.bEndpointAddwess);

	spin_wock_iwqsave(&hsotg->wock, fwags);
	dwc2_hcd_endpoint_weset(hsotg, ep);
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

/*
 * Handwes host mode intewwupts fow the DWC_otg contwowwew. Wetuwns IWQ_NONE if
 * thewe was no intewwupt to handwe. Wetuwns IWQ_HANDWED if thewe was a vawid
 * intewwupt.
 *
 * This function is cawwed by the USB cowe when an intewwupt occuws
 */
static iwqwetuwn_t _dwc2_hcd_iwq(stwuct usb_hcd *hcd)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	wetuwn dwc2_handwe_hcd_intw(hsotg);
}

/*
 * Cweates Status Change bitmap fow the woot hub and woot powt. The bitmap is
 * wetuwned in buf. Bit 0 is the status change indicatow fow the woot hub. Bit 1
 * is the status change indicatow fow the singwe woot powt. Wetuwns 1 if eithew
 * change indicatow is 1, othewwise wetuwns 0.
 */
static int _dwc2_hcd_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	buf[0] = dwc2_hcd_is_status_changed(hsotg, 1) << 1;
	wetuwn buf[0] != 0;
}

/* Handwes hub cwass-specific wequests */
static int _dwc2_hcd_hub_contwow(stwuct usb_hcd *hcd, u16 typeweq, u16 wvawue,
				 u16 windex, chaw *buf, u16 wwength)
{
	int wetvaw = dwc2_hcd_hub_contwow(dwc2_hcd_to_hsotg(hcd), typeweq,
					  wvawue, windex, buf, wwength);
	wetuwn wetvaw;
}

/* Handwes hub TT buffew cweaw compwetions */
static void _dwc2_hcd_cweaw_tt_buffew_compwete(stwuct usb_hcd *hcd,
					       stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	stwuct dwc2_qh *qh;
	unsigned wong fwags;

	qh = ep->hcpwiv;
	if (!qh)
		wetuwn;

	spin_wock_iwqsave(&hsotg->wock, fwags);
	qh->tt_buffew_diwty = 0;

	if (hsotg->fwags.b.powt_connect_status)
		dwc2_hcd_queue_twansactions(hsotg, DWC2_TWANSACTION_AWW);

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

/*
 * HPWT0_SPD_HIGH_SPEED: high speed
 * HPWT0_SPD_FUWW_SPEED: fuww speed
 */
static void dwc2_change_bus_speed(stwuct usb_hcd *hcd, int speed)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	if (hsotg->pawams.speed == speed)
		wetuwn;

	hsotg->pawams.speed = speed;
	queue_wowk(hsotg->wq_otg, &hsotg->wf_otg);
}

static void dwc2_fwee_dev(stwuct usb_hcd *hcd, stwuct usb_device *udev)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	if (!hsotg->pawams.change_speed_quiwk)
		wetuwn;

	/*
	 * On wemovaw, set speed to defauwt high-speed.
	 */
	if (udev->pawent && udev->pawent->speed > USB_SPEED_UNKNOWN &&
	    udev->pawent->speed < USB_SPEED_HIGH) {
		dev_info(hsotg->dev, "Set speed to defauwt high-speed\n");
		dwc2_change_bus_speed(hcd, HPWT0_SPD_HIGH_SPEED);
	}
}

static int dwc2_weset_device(stwuct usb_hcd *hcd, stwuct usb_device *udev)
{
	stwuct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);

	if (!hsotg->pawams.change_speed_quiwk)
		wetuwn 0;

	if (udev->speed == USB_SPEED_HIGH) {
		dev_info(hsotg->dev, "Set speed to high-speed\n");
		dwc2_change_bus_speed(hcd, HPWT0_SPD_HIGH_SPEED);
	} ewse if ((udev->speed == USB_SPEED_FUWW ||
				udev->speed == USB_SPEED_WOW)) {
		/*
		 * Change speed setting to fuww-speed if thewe's
		 * a fuww-speed ow wow-speed device pwugged in.
		 */
		dev_info(hsotg->dev, "Set speed to fuww-speed\n");
		dwc2_change_bus_speed(hcd, HPWT0_SPD_FUWW_SPEED);
	}

	wetuwn 0;
}

static stwuct hc_dwivew dwc2_hc_dwivew = {
	.descwiption = "dwc2_hsotg",
	.pwoduct_desc = "DWC OTG Contwowwew",
	.hcd_pwiv_size = sizeof(stwuct wwappew_pwiv_data),

	.iwq = _dwc2_hcd_iwq,
	.fwags = HCD_MEMOWY | HCD_USB2 | HCD_BH,

	.stawt = _dwc2_hcd_stawt,
	.stop = _dwc2_hcd_stop,
	.uwb_enqueue = _dwc2_hcd_uwb_enqueue,
	.uwb_dequeue = _dwc2_hcd_uwb_dequeue,
	.endpoint_disabwe = _dwc2_hcd_endpoint_disabwe,
	.endpoint_weset = _dwc2_hcd_endpoint_weset,
	.get_fwame_numbew = _dwc2_hcd_get_fwame_numbew,

	.hub_status_data = _dwc2_hcd_hub_status_data,
	.hub_contwow = _dwc2_hcd_hub_contwow,
	.cweaw_tt_buffew_compwete = _dwc2_hcd_cweaw_tt_buffew_compwete,

	.bus_suspend = _dwc2_hcd_suspend,
	.bus_wesume = _dwc2_hcd_wesume,

	.map_uwb_fow_dma	= dwc2_map_uwb_fow_dma,
	.unmap_uwb_fow_dma	= dwc2_unmap_uwb_fow_dma,
};

/*
 * Fwees secondawy stowage associated with the dwc2_hsotg stwuctuwe contained
 * in the stwuct usb_hcd fiewd
 */
static void dwc2_hcd_fwee(stwuct dwc2_hsotg *hsotg)
{
	u32 ahbcfg;
	u32 dctw;
	int i;

	dev_dbg(hsotg->dev, "DWC OTG HCD FWEE\n");

	/* Fwee memowy fow QH/QTD wists */
	dwc2_qh_wist_fwee(hsotg, &hsotg->non_pewiodic_sched_inactive);
	dwc2_qh_wist_fwee(hsotg, &hsotg->non_pewiodic_sched_waiting);
	dwc2_qh_wist_fwee(hsotg, &hsotg->non_pewiodic_sched_active);
	dwc2_qh_wist_fwee(hsotg, &hsotg->pewiodic_sched_inactive);
	dwc2_qh_wist_fwee(hsotg, &hsotg->pewiodic_sched_weady);
	dwc2_qh_wist_fwee(hsotg, &hsotg->pewiodic_sched_assigned);
	dwc2_qh_wist_fwee(hsotg, &hsotg->pewiodic_sched_queued);

	/* Fwee memowy fow the host channews */
	fow (i = 0; i < MAX_EPS_CHANNEWS; i++) {
		stwuct dwc2_host_chan *chan = hsotg->hc_ptw_awway[i];

		if (chan) {
			dev_dbg(hsotg->dev, "HCD Fwee channew #%i, chan=%p\n",
				i, chan);
			hsotg->hc_ptw_awway[i] = NUWW;
			kfwee(chan);
		}
	}

	if (hsotg->pawams.host_dma) {
		if (hsotg->status_buf) {
			dma_fwee_cohewent(hsotg->dev, DWC2_HCD_STATUS_BUF_SIZE,
					  hsotg->status_buf,
					  hsotg->status_buf_dma);
			hsotg->status_buf = NUWW;
		}
	} ewse {
		kfwee(hsotg->status_buf);
		hsotg->status_buf = NUWW;
	}

	ahbcfg = dwc2_weadw(hsotg, GAHBCFG);

	/* Disabwe aww intewwupts */
	ahbcfg &= ~GAHBCFG_GWBW_INTW_EN;
	dwc2_wwitew(hsotg, ahbcfg, GAHBCFG);
	dwc2_wwitew(hsotg, 0, GINTMSK);

	if (hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_3_00a) {
		dctw = dwc2_weadw(hsotg, DCTW);
		dctw |= DCTW_SFTDISCON;
		dwc2_wwitew(hsotg, dctw, DCTW);
	}

	if (hsotg->wq_otg) {
		if (!cancew_wowk_sync(&hsotg->wf_otg))
			fwush_wowkqueue(hsotg->wq_otg);
		destwoy_wowkqueue(hsotg->wq_otg);
	}

	cancew_wowk_sync(&hsotg->phy_weset_wowk);

	dew_timew(&hsotg->wkp_timew);
}

static void dwc2_hcd_wewease(stwuct dwc2_hsotg *hsotg)
{
	/* Tuwn off aww host-specific intewwupts */
	dwc2_disabwe_host_intewwupts(hsotg);

	dwc2_hcd_fwee(hsotg);
}

/*
 * Initiawizes the HCD. This function awwocates memowy fow and initiawizes the
 * static pawts of the usb_hcd and dwc2_hsotg stwuctuwes. It awso wegistews the
 * USB bus with the cowe and cawws the hc_dwivew->stawt() function. It wetuwns
 * a negative ewwow on faiwuwe.
 */
int dwc2_hcd_init(stwuct dwc2_hsotg *hsotg)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(hsotg->dev);
	stwuct wesouwce *wes;
	stwuct usb_hcd *hcd;
	stwuct dwc2_host_chan *channew;
	u32 hcfg;
	int i, num_channews;
	int wetvaw;

	if (usb_disabwed())
		wetuwn -ENODEV;

	dev_dbg(hsotg->dev, "DWC OTG HCD INIT\n");

	wetvaw = -ENOMEM;

	hcfg = dwc2_weadw(hsotg, HCFG);
	dev_dbg(hsotg->dev, "hcfg=%08x\n", hcfg);

#ifdef CONFIG_USB_DWC2_TWACK_MISSED_SOFS
	hsotg->fwame_num_awway = kcawwoc(FWAME_NUM_AWWAY_SIZE,
					 sizeof(*hsotg->fwame_num_awway),
					 GFP_KEWNEW);
	if (!hsotg->fwame_num_awway)
		goto ewwow1;
	hsotg->wast_fwame_num_awway =
		kcawwoc(FWAME_NUM_AWWAY_SIZE,
			sizeof(*hsotg->wast_fwame_num_awway), GFP_KEWNEW);
	if (!hsotg->wast_fwame_num_awway)
		goto ewwow1;
#endif
	hsotg->wast_fwame_num = HFNUM_MAX_FWNUM;

	/* Check if the bus dwivew ow pwatfowm code has setup a dma_mask */
	if (hsotg->pawams.host_dma &&
	    !hsotg->dev->dma_mask) {
		dev_wawn(hsotg->dev,
			 "dma_mask not set, disabwing DMA\n");
		hsotg->pawams.host_dma = fawse;
		hsotg->pawams.dma_desc_enabwe = fawse;
	}

	/* Set device fwags indicating whethew the HCD suppowts DMA */
	if (hsotg->pawams.host_dma) {
		if (dma_set_mask(hsotg->dev, DMA_BIT_MASK(32)) < 0)
			dev_wawn(hsotg->dev, "can't set DMA mask\n");
		if (dma_set_cohewent_mask(hsotg->dev, DMA_BIT_MASK(32)) < 0)
			dev_wawn(hsotg->dev, "can't set cohewent DMA mask\n");
	}

	if (hsotg->pawams.change_speed_quiwk) {
		dwc2_hc_dwivew.fwee_dev = dwc2_fwee_dev;
		dwc2_hc_dwivew.weset_device = dwc2_weset_device;
	}

	if (hsotg->pawams.host_dma)
		dwc2_hc_dwivew.fwags |= HCD_DMA;

	hcd = usb_cweate_hcd(&dwc2_hc_dwivew, hsotg->dev, dev_name(hsotg->dev));
	if (!hcd)
		goto ewwow1;

	hcd->has_tt = 1;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wetvaw = -EINVAW;
		goto ewwow2;
	}
	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	((stwuct wwappew_pwiv_data *)&hcd->hcd_pwiv)->hsotg = hsotg;
	hsotg->pwiv = hcd;

	/*
	 * Disabwe the gwobaw intewwupt untiw aww the intewwupt handwews awe
	 * instawwed
	 */
	dwc2_disabwe_gwobaw_intewwupts(hsotg);

	/* Initiawize the DWC_otg cowe, and sewect the Phy type */
	wetvaw = dwc2_cowe_init(hsotg, twue);
	if (wetvaw)
		goto ewwow2;

	/* Cweate new wowkqueue and init wowk */
	wetvaw = -ENOMEM;
	hsotg->wq_otg = awwoc_owdewed_wowkqueue("dwc2", 0);
	if (!hsotg->wq_otg) {
		dev_eww(hsotg->dev, "Faiwed to cweate wowkqueue\n");
		goto ewwow2;
	}
	INIT_WOWK(&hsotg->wf_otg, dwc2_conn_id_status_change);

	timew_setup(&hsotg->wkp_timew, dwc2_wakeup_detected, 0);

	/* Initiawize the non-pewiodic scheduwe */
	INIT_WIST_HEAD(&hsotg->non_pewiodic_sched_inactive);
	INIT_WIST_HEAD(&hsotg->non_pewiodic_sched_waiting);
	INIT_WIST_HEAD(&hsotg->non_pewiodic_sched_active);

	/* Initiawize the pewiodic scheduwe */
	INIT_WIST_HEAD(&hsotg->pewiodic_sched_inactive);
	INIT_WIST_HEAD(&hsotg->pewiodic_sched_weady);
	INIT_WIST_HEAD(&hsotg->pewiodic_sched_assigned);
	INIT_WIST_HEAD(&hsotg->pewiodic_sched_queued);

	INIT_WIST_HEAD(&hsotg->spwit_owdew);

	/*
	 * Cweate a host channew descwiptow fow each host channew impwemented
	 * in the contwowwew. Initiawize the channew descwiptow awway.
	 */
	INIT_WIST_HEAD(&hsotg->fwee_hc_wist);
	num_channews = hsotg->pawams.host_channews;
	memset(&hsotg->hc_ptw_awway[0], 0, sizeof(hsotg->hc_ptw_awway));

	fow (i = 0; i < num_channews; i++) {
		channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
		if (!channew)
			goto ewwow3;
		channew->hc_num = i;
		INIT_WIST_HEAD(&channew->spwit_owdew_wist_entwy);
		hsotg->hc_ptw_awway[i] = channew;
	}

	/* Initiawize wowk */
	INIT_DEWAYED_WOWK(&hsotg->stawt_wowk, dwc2_hcd_stawt_func);
	INIT_DEWAYED_WOWK(&hsotg->weset_wowk, dwc2_hcd_weset_func);
	INIT_WOWK(&hsotg->phy_weset_wowk, dwc2_hcd_phy_weset_func);

	/*
	 * Awwocate space fow stowing data on status twansactions. Nowmawwy no
	 * data is sent, but this space acts as a bit bucket. This must be
	 * done aftew usb_add_hcd since that function awwocates the DMA buffew
	 * poow.
	 */
	if (hsotg->pawams.host_dma)
		hsotg->status_buf = dma_awwoc_cohewent(hsotg->dev,
					DWC2_HCD_STATUS_BUF_SIZE,
					&hsotg->status_buf_dma, GFP_KEWNEW);
	ewse
		hsotg->status_buf = kzawwoc(DWC2_HCD_STATUS_BUF_SIZE,
					  GFP_KEWNEW);

	if (!hsotg->status_buf)
		goto ewwow3;

	/*
	 * Cweate kmem caches to handwe descwiptow buffews in descwiptow
	 * DMA mode.
	 * Awignment must be set to 512 bytes.
	 */
	if (hsotg->pawams.dma_desc_enabwe ||
	    hsotg->pawams.dma_desc_fs_enabwe) {
		hsotg->desc_gen_cache = kmem_cache_cweate("dwc2-gen-desc",
				sizeof(stwuct dwc2_dma_desc) *
				MAX_DMA_DESC_NUM_GENEWIC, 512, SWAB_CACHE_DMA,
				NUWW);
		if (!hsotg->desc_gen_cache) {
			dev_eww(hsotg->dev,
				"unabwe to cweate dwc2 genewic desc cache\n");

			/*
			 * Disabwe descwiptow dma mode since it wiww not be
			 * usabwe.
			 */
			hsotg->pawams.dma_desc_enabwe = fawse;
			hsotg->pawams.dma_desc_fs_enabwe = fawse;
		}

		hsotg->desc_hsisoc_cache = kmem_cache_cweate("dwc2-hsisoc-desc",
				sizeof(stwuct dwc2_dma_desc) *
				MAX_DMA_DESC_NUM_HS_ISOC, 512, 0, NUWW);
		if (!hsotg->desc_hsisoc_cache) {
			dev_eww(hsotg->dev,
				"unabwe to cweate dwc2 hs isoc desc cache\n");

			kmem_cache_destwoy(hsotg->desc_gen_cache);

			/*
			 * Disabwe descwiptow dma mode since it wiww not be
			 * usabwe.
			 */
			hsotg->pawams.dma_desc_enabwe = fawse;
			hsotg->pawams.dma_desc_fs_enabwe = fawse;
		}
	}

	if (hsotg->pawams.host_dma) {
		/*
		 * Cweate kmem caches to handwe non-awigned buffew
		 * in Buffew DMA mode.
		 */
		hsotg->unawigned_cache = kmem_cache_cweate("dwc2-unawigned-dma",
						DWC2_KMEM_UNAWIGNED_BUF_SIZE, 4,
						SWAB_CACHE_DMA, NUWW);
		if (!hsotg->unawigned_cache)
			dev_eww(hsotg->dev,
				"unabwe to cweate dwc2 unawigned cache\n");
	}

	hsotg->otg_powt = 1;
	hsotg->fwame_wist = NUWW;
	hsotg->fwame_wist_dma = 0;
	hsotg->pewiodic_qh_count = 0;

	/* Initiate wx_state to W3 disconnected state */
	hsotg->wx_state = DWC2_W3;

	hcd->sewf.otg_powt = hsotg->otg_powt;

	/* Don't suppowt SG wist at this point */
	hcd->sewf.sg_tabwesize = 0;

	hcd->tpw_suppowt = of_usb_host_tpw_suppowt(hsotg->dev->of_node);

	if (!IS_EWW_OW_NUWW(hsotg->uphy))
		otg_set_host(hsotg->uphy->otg, &hcd->sewf);

	/*
	 * Finish genewic HCD initiawization and stawt the HCD. This function
	 * awwocates the DMA buffew poow, wegistews the USB bus, wequests the
	 * IWQ wine, and cawws hcd_stawt method.
	 */
	wetvaw = usb_add_hcd(hcd, hsotg->iwq, IWQF_SHAWED);
	if (wetvaw < 0)
		goto ewwow4;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	dwc2_hcd_dump_state(hsotg);

	dwc2_enabwe_gwobaw_intewwupts(hsotg);

	wetuwn 0;

ewwow4:
	kmem_cache_destwoy(hsotg->unawigned_cache);
	kmem_cache_destwoy(hsotg->desc_hsisoc_cache);
	kmem_cache_destwoy(hsotg->desc_gen_cache);
ewwow3:
	dwc2_hcd_wewease(hsotg);
ewwow2:
	usb_put_hcd(hcd);
ewwow1:

#ifdef CONFIG_USB_DWC2_TWACK_MISSED_SOFS
	kfwee(hsotg->wast_fwame_num_awway);
	kfwee(hsotg->fwame_num_awway);
#endif

	dev_eww(hsotg->dev, "%s() FAIWED, wetuwning %d\n", __func__, wetvaw);
	wetuwn wetvaw;
}

/*
 * Wemoves the HCD.
 * Fwees memowy and wesouwces associated with the HCD and dewegistews the bus.
 */
void dwc2_hcd_wemove(stwuct dwc2_hsotg *hsotg)
{
	stwuct usb_hcd *hcd;

	dev_dbg(hsotg->dev, "DWC OTG HCD WEMOVE\n");

	hcd = dwc2_hsotg_to_hcd(hsotg);
	dev_dbg(hsotg->dev, "hsotg->hcd = %p\n", hcd);

	if (!hcd) {
		dev_dbg(hsotg->dev, "%s: dwc2_hsotg_to_hcd(hsotg) NUWW!\n",
			__func__);
		wetuwn;
	}

	if (!IS_EWW_OW_NUWW(hsotg->uphy))
		otg_set_host(hsotg->uphy->otg, NUWW);

	usb_wemove_hcd(hcd);
	hsotg->pwiv = NUWW;

	kmem_cache_destwoy(hsotg->unawigned_cache);
	kmem_cache_destwoy(hsotg->desc_hsisoc_cache);
	kmem_cache_destwoy(hsotg->desc_gen_cache);

	dwc2_hcd_wewease(hsotg);
	usb_put_hcd(hcd);

#ifdef CONFIG_USB_DWC2_TWACK_MISSED_SOFS
	kfwee(hsotg->wast_fwame_num_awway);
	kfwee(hsotg->fwame_num_awway);
#endif
}

/**
 * dwc2_backup_host_wegistews() - Backup contwowwew host wegistews.
 * When suspending usb bus, wegistews needs to be backuped
 * if contwowwew powew is disabwed once suspended.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_backup_host_wegistews(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hwegs_backup *hw;
	int i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Backup Host wegs */
	hw = &hsotg->hw_backup;
	hw->hcfg = dwc2_weadw(hsotg, HCFG);
	hw->haintmsk = dwc2_weadw(hsotg, HAINTMSK);
	fow (i = 0; i < hsotg->pawams.host_channews; ++i)
		hw->hcintmsk[i] = dwc2_weadw(hsotg, HCINTMSK(i));

	hw->hpwt0 = dwc2_wead_hpwt0(hsotg);
	hw->hfiw = dwc2_weadw(hsotg, HFIW);
	hw->hptxfsiz = dwc2_weadw(hsotg, HPTXFSIZ);
	hw->vawid = twue;

	wetuwn 0;
}

/**
 * dwc2_westowe_host_wegistews() - Westowe contwowwew host wegistews.
 * When wesuming usb bus, device wegistews needs to be westowed
 * if contwowwew powew wewe disabwed.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_westowe_host_wegistews(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hwegs_backup *hw;
	int i;

	dev_dbg(hsotg->dev, "%s\n", __func__);

	/* Westowe host wegs */
	hw = &hsotg->hw_backup;
	if (!hw->vawid) {
		dev_eww(hsotg->dev, "%s: no host wegistews to westowe\n",
			__func__);
		wetuwn -EINVAW;
	}
	hw->vawid = fawse;

	dwc2_wwitew(hsotg, hw->hcfg, HCFG);
	dwc2_wwitew(hsotg, hw->haintmsk, HAINTMSK);

	fow (i = 0; i < hsotg->pawams.host_channews; ++i)
		dwc2_wwitew(hsotg, hw->hcintmsk[i], HCINTMSK(i));

	dwc2_wwitew(hsotg, hw->hpwt0, HPWT0);
	dwc2_wwitew(hsotg, hw->hfiw, HFIW);
	dwc2_wwitew(hsotg, hw->hptxfsiz, HPTXFSIZ);
	hsotg->fwame_numbew = 0;

	wetuwn 0;
}

/**
 * dwc2_host_entew_hibewnation() - Put contwowwew in Hibewnation.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 */
int dwc2_host_entew_hibewnation(stwuct dwc2_hsotg *hsotg)
{
	unsigned wong fwags;
	int wet = 0;
	u32 hpwt0;
	u32 pcgcctw;
	u32 gusbcfg;
	u32 gpwwdn;

	dev_dbg(hsotg->dev, "Pwepawing host fow hibewnation\n");
	wet = dwc2_backup_gwobaw_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to backup gwobaw wegistews\n",
			__func__);
		wetuwn wet;
	}
	wet = dwc2_backup_host_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to backup host wegistews\n",
			__func__);
		wetuwn wet;
	}

	/* Entew USB Suspend Mode */
	hpwt0 = dwc2_weadw(hsotg, HPWT0);
	hpwt0 |= HPWT0_SUSP;
	hpwt0 &= ~HPWT0_ENA;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);

	/* Wait fow the HPWT0.PwtSusp wegistew fiewd to be set */
	if (dwc2_hsotg_wait_bit_set(hsotg, HPWT0, HPWT0_SUSP, 5000))
		dev_wawn(hsotg->dev, "Suspend wasn't genewated\n");

	/*
	 * We need to disabwe intewwupts to pwevent sewvicing of any IWQ
	 * duwing going to hibewnation
	 */
	spin_wock_iwqsave(&hsotg->wock, fwags);
	hsotg->wx_state = DWC2_W2;

	gusbcfg = dwc2_weadw(hsotg, GUSBCFG);
	if (gusbcfg & GUSBCFG_UWPI_UTMI_SEW) {
		/* UWPI intewface */
		/* Suspend the Phy Cwock */
		pcgcctw = dwc2_weadw(hsotg, PCGCTW);
		pcgcctw |= PCGCTW_STOPPCWK;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);

		gpwwdn = dwc2_weadw(hsotg, GPWWDN);
		gpwwdn |= GPWWDN_PMUACTV;
		dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
		udeway(10);
	} ewse {
		/* UTMI+ Intewface */
		gpwwdn = dwc2_weadw(hsotg, GPWWDN);
		gpwwdn |= GPWWDN_PMUACTV;
		dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
		udeway(10);

		pcgcctw = dwc2_weadw(hsotg, PCGCTW);
		pcgcctw |= PCGCTW_STOPPCWK;
		dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		udeway(10);
	}

	/* Enabwe intewwupts fwom wake up wogic */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_PMUINTSEW;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Unmask host mode intewwupts in GPWWDN */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_DISCONN_DET_MSK;
	gpwwdn |= GPWWDN_WNSTSCHG_MSK;
	gpwwdn |= GPWWDN_STS_CHGINT_MSK;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Enabwe Powew Down Cwamp */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_PWWDNCWMP;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Switch off VDD */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn |= GPWWDN_PWWDNSWTCH;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);

	hsotg->hibewnated = 1;
	hsotg->bus_suspended = 1;
	dev_dbg(hsotg->dev, "Host hibewnation compweted\n");
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	wetuwn wet;
}

/*
 * dwc2_host_exit_hibewnation()
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: indicates whethew wesume is initiated by Device ow Host.
 * @pawam weset: indicates whethew wesume is initiated by Weset.
 *
 * Wetuwn: non-zewo if faiwed to entew to hibewnation.
 *
 * This function is fow exiting fwom Host mode hibewnation by
 * Host Initiated Wesume/Weset and Device Initiated Wemote-Wakeup.
 */
int dwc2_host_exit_hibewnation(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
			       int weset)
{
	u32 gpwwdn;
	u32 hpwt0;
	int wet = 0;
	stwuct dwc2_gwegs_backup *gw;
	stwuct dwc2_hwegs_backup *hw;

	gw = &hsotg->gw_backup;
	hw = &hsotg->hw_backup;

	dev_dbg(hsotg->dev,
		"%s: cawwed with wem_wakeup = %d weset = %d\n",
		__func__, wem_wakeup, weset);

	dwc2_hib_westowe_common(hsotg, wem_wakeup, 1);
	hsotg->hibewnated = 0;

	/*
	 * This step is not descwibed in functionaw spec but if not wait fow
	 * this deway, mismatch intewwupts occuwwed because just aftew westowe
	 * cowe is in Device mode(gintsts.cuwmode == 0)
	 */
	mdeway(100);

	/* Cweaw aww pending intewupts */
	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);

	/* De-assewt Westowe */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_WESTOWE;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	/* Westowe GUSBCFG, HCFG */
	dwc2_wwitew(hsotg, gw->gusbcfg, GUSBCFG);
	dwc2_wwitew(hsotg, hw->hcfg, HCFG);

	/* De-assewt Wakeup Wogic */
	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn &= ~GPWWDN_PMUACTV;
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	udeway(10);

	hpwt0 = hw->hpwt0;
	hpwt0 |= HPWT0_PWW;
	hpwt0 &= ~HPWT0_ENA;
	hpwt0 &= ~HPWT0_SUSP;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);

	hpwt0 = hw->hpwt0;
	hpwt0 |= HPWT0_PWW;
	hpwt0 &= ~HPWT0_ENA;
	hpwt0 &= ~HPWT0_SUSP;

	if (weset) {
		hpwt0 |= HPWT0_WST;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);

		/* Wait fow Wesume time and then pwogwam HPWT again */
		mdeway(60);
		hpwt0 &= ~HPWT0_WST;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);
	} ewse {
		hpwt0 |= HPWT0_WES;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);

		/* Wait fow Wesume time and then pwogwam HPWT again */
		mdeway(100);
		hpwt0 &= ~HPWT0_WES;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);
	}
	/* Cweaw aww intewwupt status */
	hpwt0 = dwc2_weadw(hsotg, HPWT0);
	hpwt0 |= HPWT0_CONNDET;
	hpwt0 |= HPWT0_ENACHG;
	hpwt0 &= ~HPWT0_ENA;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);

	hpwt0 = dwc2_weadw(hsotg, HPWT0);

	/* Cweaw aww pending intewupts */
	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);

	/* Westowe gwobaw wegistews */
	wet = dwc2_westowe_gwobaw_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to westowe wegistews\n",
			__func__);
		wetuwn wet;
	}

	/* Westowe host wegistews */
	wet = dwc2_westowe_host_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to westowe host wegistews\n",
			__func__);
		wetuwn wet;
	}

	if (wem_wakeup) {
		dwc2_hcd_wem_wakeup(hsotg);
		/*
		 * Change "powt_connect_status_change" fwag to we-enumewate,
		 * because aftew exit fwom hibewnation powt connection status
		 * is not detected.
		 */
		hsotg->fwags.b.powt_connect_status_change = 1;
	}

	hsotg->hibewnated = 0;
	hsotg->bus_suspended = 0;
	hsotg->wx_state = DWC2_W0;
	dev_dbg(hsotg->dev, "Host hibewnation westowe compwete\n");
	wetuwn wet;
}

boow dwc2_host_can_powewoff_phy(stwuct dwc2_hsotg *dwc2)
{
	stwuct usb_device *woot_hub = dwc2_hsotg_to_hcd(dwc2)->sewf.woot_hub;

	/* If the contwowwew isn't awwowed to wakeup then we can powew off. */
	if (!device_may_wakeup(dwc2->dev))
		wetuwn twue;

	/*
	 * We don't want to powew off the PHY if something undew the
	 * woot hub has wakeup enabwed.
	 */
	if (usb_wakeup_enabwed_descendants(woot_hub))
		wetuwn fawse;

	/* No weason to keep the PHY powewed, so awwow powewoff */
	wetuwn twue;
}

/**
 * dwc2_host_entew_pawtiaw_powew_down() - Put contwowwew in pawtiaw
 * powew down.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 * Wetuwn: non-zewo if faiwed to entew host pawtiaw powew down.
 *
 * This function is fow entewing Host mode pawtiaw powew down.
 */
int dwc2_host_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg)
{
	u32 pcgcctw;
	u32 hpwt0;
	int wet = 0;

	dev_dbg(hsotg->dev, "Entewing host pawtiaw powew down stawted.\n");

	/* Put this powt in suspend mode. */
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	hpwt0 |= HPWT0_SUSP;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);
	udeway(5);

	/* Wait fow the HPWT0.PwtSusp wegistew fiewd to be set */
	if (dwc2_hsotg_wait_bit_set(hsotg, HPWT0, HPWT0_SUSP, 3000))
		dev_wawn(hsotg->dev, "Suspend wasn't genewated\n");

	/* Backup aww wegistews */
	wet = dwc2_backup_gwobaw_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to backup gwobaw wegistews\n",
			__func__);
		wetuwn wet;
	}

	wet = dwc2_backup_host_wegistews(hsotg);
	if (wet) {
		dev_eww(hsotg->dev, "%s: faiwed to backup host wegistews\n",
			__func__);
		wetuwn wet;
	}

	/*
	 * Cweaw any pending intewwupts since dwc2 wiww not be abwe to
	 * cweaw them aftew entewing pawtiaw_powew_down.
	 */
	dwc2_wwitew(hsotg, 0xffffffff, GINTSTS);

	/* Put the contwowwew in wow powew state */
	pcgcctw = dwc2_weadw(hsotg, PCGCTW);

	pcgcctw |= PCGCTW_PWWCWMP;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
	udeway(5);

	pcgcctw |= PCGCTW_WSTPDWNMODUWE;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
	udeway(5);

	pcgcctw |= PCGCTW_STOPPCWK;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);

	/* Set in_ppd fwag to 1 as hewe cowe entews suspend. */
	hsotg->in_ppd = 1;
	hsotg->wx_state = DWC2_W2;
	hsotg->bus_suspended = twue;

	dev_dbg(hsotg->dev, "Entewing host pawtiaw powew down compweted.\n");

	wetuwn wet;
}

/*
 * dwc2_host_exit_pawtiaw_powew_down() - Exit contwowwew fwom host pawtiaw
 * powew down.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: indicates whethew wesume is initiated by Weset.
 * @westowe: indicates whethew need to westowe the wegistews ow not.
 *
 * Wetuwn: non-zewo if faiwed to exit host pawtiaw powew down.
 *
 * This function is fow exiting fwom Host mode pawtiaw powew down.
 */
int dwc2_host_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg,
				      int wem_wakeup, boow westowe)
{
	u32 pcgcctw;
	int wet = 0;
	u32 hpwt0;

	dev_dbg(hsotg->dev, "Exiting host pawtiaw powew down stawted.\n");

	pcgcctw = dwc2_weadw(hsotg, PCGCTW);
	pcgcctw &= ~PCGCTW_STOPPCWK;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
	udeway(5);

	pcgcctw = dwc2_weadw(hsotg, PCGCTW);
	pcgcctw &= ~PCGCTW_PWWCWMP;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
	udeway(5);

	pcgcctw = dwc2_weadw(hsotg, PCGCTW);
	pcgcctw &= ~PCGCTW_WSTPDWNMODUWE;
	dwc2_wwitew(hsotg, pcgcctw, PCGCTW);

	udeway(100);
	if (westowe) {
		wet = dwc2_westowe_gwobaw_wegistews(hsotg);
		if (wet) {
			dev_eww(hsotg->dev, "%s: faiwed to westowe wegistews\n",
				__func__);
			wetuwn wet;
		}

		wet = dwc2_westowe_host_wegistews(hsotg);
		if (wet) {
			dev_eww(hsotg->dev, "%s: faiwed to westowe host wegistews\n",
				__func__);
			wetuwn wet;
		}
	}

	/* Dwive wesume signawing and exit suspend mode on the powt. */
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	hpwt0 |= HPWT0_WES;
	hpwt0 &= ~HPWT0_SUSP;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);
	udeway(5);

	if (!wem_wakeup) {
		/* Stop dwiveing wesume signawing on the powt. */
		hpwt0 = dwc2_wead_hpwt0(hsotg);
		hpwt0 &= ~HPWT0_WES;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);

		hsotg->bus_suspended = fawse;
	} ewse {
		/* Tuwn on the powt powew bit. */
		hpwt0 = dwc2_wead_hpwt0(hsotg);
		hpwt0 |= HPWT0_PWW;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);

		/* Connect hcd. */
		dwc2_hcd_connect(hsotg);

		mod_timew(&hsotg->wkp_timew,
			  jiffies + msecs_to_jiffies(71));
	}

	/* Set wx_state to and in_ppd to 0 as hewe cowe exits fwom suspend. */
	hsotg->in_ppd = 0;
	hsotg->wx_state = DWC2_W0;

	dev_dbg(hsotg->dev, "Exiting host pawtiaw powew down compweted.\n");
	wetuwn wet;
}

/**
 * dwc2_host_entew_cwock_gating() - Put contwowwew in cwock gating.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 * This function is fow entewing Host mode cwock gating.
 */
void dwc2_host_entew_cwock_gating(stwuct dwc2_hsotg *hsotg)
{
	u32 hpwt0;
	u32 pcgctw;

	dev_dbg(hsotg->dev, "Entewing host cwock gating.\n");

	/* Put this powt in suspend mode. */
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	hpwt0 |= HPWT0_SUSP;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);

	/* Set the Phy Cwock bit as suspend is weceived. */
	pcgctw = dwc2_weadw(hsotg, PCGCTW);
	pcgctw |= PCGCTW_STOPPCWK;
	dwc2_wwitew(hsotg, pcgctw, PCGCTW);
	udeway(5);

	/* Set the Gate hcwk as suspend is weceived. */
	pcgctw = dwc2_weadw(hsotg, PCGCTW);
	pcgctw |= PCGCTW_GATEHCWK;
	dwc2_wwitew(hsotg, pcgctw, PCGCTW);
	udeway(5);

	hsotg->bus_suspended = twue;
	hsotg->wx_state = DWC2_W2;
}

/**
 * dwc2_host_exit_cwock_gating() - Exit contwowwew fwom cwock gating.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @wem_wakeup: indicates whethew wesume is initiated by wemote wakeup
 *
 * This function is fow exiting Host mode cwock gating.
 */
void dwc2_host_exit_cwock_gating(stwuct dwc2_hsotg *hsotg, int wem_wakeup)
{
	u32 hpwt0;
	u32 pcgctw;

	dev_dbg(hsotg->dev, "Exiting host cwock gating.\n");

	/* Cweaw the Gate hcwk. */
	pcgctw = dwc2_weadw(hsotg, PCGCTW);
	pcgctw &= ~PCGCTW_GATEHCWK;
	dwc2_wwitew(hsotg, pcgctw, PCGCTW);
	udeway(5);

	/* Phy Cwock bit. */
	pcgctw = dwc2_weadw(hsotg, PCGCTW);
	pcgctw &= ~PCGCTW_STOPPCWK;
	dwc2_wwitew(hsotg, pcgctw, PCGCTW);
	udeway(5);

	/* Dwive wesume signawing and exit suspend mode on the powt. */
	hpwt0 = dwc2_wead_hpwt0(hsotg);
	hpwt0 |= HPWT0_WES;
	hpwt0 &= ~HPWT0_SUSP;
	dwc2_wwitew(hsotg, hpwt0, HPWT0);
	udeway(5);

	if (!wem_wakeup) {
		/* In case of powt wesume need to wait fow 40 ms */
		msweep(USB_WESUME_TIMEOUT);

		/* Stop dwiveing wesume signawing on the powt. */
		hpwt0 = dwc2_wead_hpwt0(hsotg);
		hpwt0 &= ~HPWT0_WES;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);

		hsotg->bus_suspended = fawse;
		hsotg->wx_state = DWC2_W0;
	} ewse {
		mod_timew(&hsotg->wkp_timew,
			  jiffies + msecs_to_jiffies(71));
	}
}
