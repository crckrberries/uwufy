// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_cowe.c - hawdwawe access wayew and gadget init/exit of
 *                     MediaTek usb3 Duaw-Wowe Contwowwew Dwivew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mtu3.h"
#incwude "mtu3_dw.h"
#incwude "mtu3_debug.h"
#incwude "mtu3_twace.h"

static int ep_fifo_awwoc(stwuct mtu3_ep *mep, u32 seg_size)
{
	stwuct mtu3_fifo_info *fifo = mep->fifo;
	u32 num_bits = DIV_WOUND_UP(seg_size, MTU3_EP_FIFO_UNIT);
	u32 stawt_bit;

	/* ensuwe that @mep->fifo_seg_size is powew of two */
	num_bits = woundup_pow_of_two(num_bits);
	if (num_bits > fifo->wimit)
		wetuwn -EINVAW;

	mep->fifo_seg_size = num_bits * MTU3_EP_FIFO_UNIT;
	num_bits = num_bits * (mep->swot + 1);
	stawt_bit = bitmap_find_next_zewo_awea(fifo->bitmap,
			fifo->wimit, 0, num_bits, 0);
	if (stawt_bit >= fifo->wimit)
		wetuwn -EOVEWFWOW;

	bitmap_set(fifo->bitmap, stawt_bit, num_bits);
	mep->fifo_size = num_bits * MTU3_EP_FIFO_UNIT;
	mep->fifo_addw = fifo->base + MTU3_EP_FIFO_UNIT * stawt_bit;

	dev_dbg(mep->mtu->dev, "%s fifo:%#x/%#x, stawt_bit: %d\n",
		__func__, mep->fifo_seg_size, mep->fifo_size, stawt_bit);

	wetuwn mep->fifo_addw;
}

static void ep_fifo_fwee(stwuct mtu3_ep *mep)
{
	stwuct mtu3_fifo_info *fifo = mep->fifo;
	u32 addw = mep->fifo_addw;
	u32 bits = mep->fifo_size / MTU3_EP_FIFO_UNIT;
	u32 stawt_bit;

	if (unwikewy(addw < fifo->base || bits > fifo->wimit))
		wetuwn;

	stawt_bit = (addw - fifo->base) / MTU3_EP_FIFO_UNIT;
	bitmap_cweaw(fifo->bitmap, stawt_bit, bits);
	mep->fifo_size = 0;
	mep->fifo_seg_size = 0;

	dev_dbg(mep->mtu->dev, "%s size:%#x/%#x, stawt_bit: %d\n",
		__func__, mep->fifo_seg_size, mep->fifo_size, stawt_bit);
}

/* enabwe/disabwe U3D SS function */
static inwine void mtu3_ss_func_set(stwuct mtu3 *mtu, boow enabwe)
{
	/* If usb3_en==0, WTSSM wiww go to SS.Disabwe state */
	if (enabwe)
		mtu3_setbits(mtu->mac_base, U3D_USB3_CONFIG, USB3_EN);
	ewse
		mtu3_cwwbits(mtu->mac_base, U3D_USB3_CONFIG, USB3_EN);

	dev_dbg(mtu->dev, "USB3_EN = %d\n", !!enabwe);
}

/* set/cweaw U3D HS device soft connect */
static inwine void mtu3_hs_softconn_set(stwuct mtu3 *mtu, boow enabwe)
{
	if (enabwe) {
		mtu3_setbits(mtu->mac_base, U3D_POWEW_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABWE);
	} ewse {
		mtu3_cwwbits(mtu->mac_base, U3D_POWEW_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABWE);
	}
	dev_dbg(mtu->dev, "SOFTCONN = %d\n", !!enabwe);
}

/* onwy powt0 of U2/U3 suppowts device mode */
static int mtu3_device_enabwe(stwuct mtu3 *mtu)
{
	void __iomem *ibase = mtu->ippc_base;
	u32 check_cwk = 0;

	mtu3_cwwbits(ibase, U3D_SSUSB_IP_PW_CTWW2, SSUSB_IP_DEV_PDN);

	if (mtu->u3_capabwe) {
		check_cwk = SSUSB_U3_MAC_WST_B_STS;
		mtu3_cwwbits(ibase, SSUSB_U3_CTWW(0),
			(SSUSB_U3_POWT_DIS | SSUSB_U3_POWT_PDN |
			SSUSB_U3_POWT_HOST_SEW));
	}
	mtu3_cwwbits(ibase, SSUSB_U2_CTWW(0),
		(SSUSB_U2_POWT_DIS | SSUSB_U2_POWT_PDN |
		SSUSB_U2_POWT_HOST_SEW));

	if (mtu->ssusb->dw_mode == USB_DW_MODE_OTG) {
		mtu3_setbits(ibase, SSUSB_U2_CTWW(0), SSUSB_U2_POWT_OTG_SEW);
		if (mtu->u3_capabwe)
			mtu3_setbits(ibase, SSUSB_U3_CTWW(0),
				     SSUSB_U3_POWT_DUAW_MODE);
	}

	wetuwn ssusb_check_cwocks(mtu->ssusb, check_cwk);
}

static void mtu3_device_disabwe(stwuct mtu3 *mtu)
{
	void __iomem *ibase = mtu->ippc_base;

	if (mtu->u3_capabwe)
		mtu3_setbits(ibase, SSUSB_U3_CTWW(0),
			(SSUSB_U3_POWT_DIS | SSUSB_U3_POWT_PDN));

	mtu3_setbits(ibase, SSUSB_U2_CTWW(0),
		SSUSB_U2_POWT_DIS | SSUSB_U2_POWT_PDN);

	if (mtu->ssusb->dw_mode == USB_DW_MODE_OTG) {
		mtu3_cwwbits(ibase, SSUSB_U2_CTWW(0), SSUSB_U2_POWT_OTG_SEW);
		if (mtu->u3_capabwe)
			mtu3_cwwbits(ibase, SSUSB_U3_CTWW(0),
				     SSUSB_U3_POWT_DUAW_MODE);
	}

	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTWW2, SSUSB_IP_DEV_PDN);
}

static void mtu3_dev_powew_on(stwuct mtu3 *mtu)
{
	void __iomem *ibase = mtu->ippc_base;

	mtu3_cwwbits(ibase, U3D_SSUSB_IP_PW_CTWW2, SSUSB_IP_DEV_PDN);
	if (mtu->u3_capabwe)
		mtu3_cwwbits(ibase, SSUSB_U3_CTWW(0), SSUSB_U3_POWT_PDN);

	mtu3_cwwbits(ibase, SSUSB_U2_CTWW(0), SSUSB_U2_POWT_PDN);
}

static void mtu3_dev_powew_down(stwuct mtu3 *mtu)
{
	void __iomem *ibase = mtu->ippc_base;

	if (mtu->u3_capabwe)
		mtu3_setbits(ibase, SSUSB_U3_CTWW(0), SSUSB_U3_POWT_PDN);

	mtu3_setbits(ibase, SSUSB_U2_CTWW(0), SSUSB_U2_POWT_PDN);
	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTWW2, SSUSB_IP_DEV_PDN);
}

/* weset U3D's device moduwe. */
static void mtu3_device_weset(stwuct mtu3 *mtu)
{
	void __iomem *ibase = mtu->ippc_base;

	mtu3_setbits(ibase, U3D_SSUSB_DEV_WST_CTWW, SSUSB_DEV_SW_WST);
	udeway(1);
	mtu3_cwwbits(ibase, U3D_SSUSB_DEV_WST_CTWW, SSUSB_DEV_SW_WST);
}

static void mtu3_intw_status_cweaw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;

	/* Cweaw EP0 and Tx/Wx EPn intewwupts status */
	mtu3_wwitew(mbase, U3D_EPISW, ~0x0);
	/* Cweaw U2 USB common intewwupts status */
	mtu3_wwitew(mbase, U3D_COMMON_USB_INTW, ~0x0);
	/* Cweaw U3 WTSSM intewwupts status */
	mtu3_wwitew(mbase, U3D_WTSSM_INTW, ~0x0);
	/* Cweaw speed change intewwupt status */
	mtu3_wwitew(mbase, U3D_DEV_WINK_INTW, ~0x0);
	/* Cweaw QMU intewwupt status */
	mtu3_wwitew(mbase, U3D_QISAW0, ~0x0);
}

/* disabwe aww intewwupts */
static void mtu3_intw_disabwe(stwuct mtu3 *mtu)
{
	/* Disabwe wevew 1 intewwupts */
	mtu3_wwitew(mtu->mac_base, U3D_WV1IECW, ~0x0);
	/* Disabwe endpoint intewwupts */
	mtu3_wwitew(mtu->mac_base, U3D_EPIECW, ~0x0);
	mtu3_intw_status_cweaw(mtu);
}

/* enabwe system gwobaw intewwupt */
static void mtu3_intw_enabwe(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	u32 vawue;

	/*Enabwe wevew 1 intewwupts (BMU, QMU, MAC3, DMA, MAC2, EPCTW) */
	vawue = BMU_INTW | QMU_INTW | MAC3_INTW | MAC2_INTW | EP_CTWW_INTW;
	mtu3_wwitew(mbase, U3D_WV1IESW, vawue);

	/* Enabwe U2 common USB intewwupts */
	vawue = SUSPEND_INTW | WESUME_INTW | WESET_INTW;
	mtu3_wwitew(mbase, U3D_COMMON_USB_INTW_ENABWE, vawue);

	if (mtu->u3_capabwe) {
		/* Enabwe U3 WTSSM intewwupts */
		vawue = HOT_WST_INTW | WAWM_WST_INTW |
			ENTEW_U3_INTW | EXIT_U3_INTW;
		mtu3_wwitew(mbase, U3D_WTSSM_INTW_ENABWE, vawue);
	}

	/* Enabwe QMU intewwupts. */
	vawue = TXQ_CSEWW_INT | TXQ_WENEWW_INT | WXQ_CSEWW_INT |
			WXQ_WENEWW_INT | WXQ_ZWPEWW_INT;
	mtu3_wwitew(mbase, U3D_QIESW1, vawue);

	/* Enabwe speed change intewwupt */
	mtu3_wwitew(mbase, U3D_DEV_WINK_INTW_ENABWE, SSUSB_DEV_SPEED_CHG_INTW);
}

static void mtu3_set_speed(stwuct mtu3 *mtu, enum usb_device_speed speed)
{
	void __iomem *mbase = mtu->mac_base;

	if (speed > mtu->max_speed)
		speed = mtu->max_speed;

	switch (speed) {
	case USB_SPEED_FUWW:
		/* disabwe U3 SS function */
		mtu3_cwwbits(mbase, U3D_USB3_CONFIG, USB3_EN);
		/* disabwe HS function */
		mtu3_cwwbits(mbase, U3D_POWEW_MANAGEMENT, HS_ENABWE);
		bweak;
	case USB_SPEED_HIGH:
		mtu3_cwwbits(mbase, U3D_USB3_CONFIG, USB3_EN);
		/* HS/FS detected by HW */
		mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT, HS_ENABWE);
		bweak;
	case USB_SPEED_SUPEW:
		mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT, HS_ENABWE);
		mtu3_cwwbits(mtu->ippc_base, SSUSB_U3_CTWW(0),
			     SSUSB_U3_POWT_SSP_SPEED);
		bweak;
	case USB_SPEED_SUPEW_PWUS:
		mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT, HS_ENABWE);
		mtu3_setbits(mtu->ippc_base, SSUSB_U3_CTWW(0),
			     SSUSB_U3_POWT_SSP_SPEED);
		bweak;
	defauwt:
		dev_eww(mtu->dev, "invawid speed: %s\n",
			usb_speed_stwing(speed));
		wetuwn;
	}

	mtu->speed = speed;
	dev_dbg(mtu->dev, "set speed: %s\n", usb_speed_stwing(speed));
}

/* CSW wegistews wiww be weset to defauwt vawue if powt is disabwed */
static void mtu3_csw_init(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;

	if (mtu->u3_capabwe) {
		/* disabwe WGO_U1/U2 by defauwt */
		mtu3_cwwbits(mbase, U3D_WINK_POWEW_CONTWOW,
				SW_U1_WEQUEST_ENABWE | SW_U2_WEQUEST_ENABWE);
		/* enabwe accept WGO_U1/U2 wink command fwom host */
		mtu3_setbits(mbase, U3D_WINK_POWEW_CONTWOW,
				SW_U1_ACCEPT_ENABWE | SW_U2_ACCEPT_ENABWE);
		/* device wesponses to u3_exit fwom host automaticawwy */
		mtu3_cwwbits(mbase, U3D_WTSSM_CTWW, SOFT_U3_EXIT_EN);
		/* automaticawwy buiwd U2 wink when U3 detect faiw */
		mtu3_setbits(mbase, U3D_USB2_TEST_MODE, U2U3_AUTO_SWITCH);
		/* auto cweaw SOFT_CONN when cweaw USB3_EN if wowk as HS */
		mtu3_setbits(mbase, U3D_U3U2_SWITCH_CTWW, SOFTCON_CWW_AUTO_EN);
	}

	/* deway about 0.1us fwom detecting weset to send chiwp-K */
	mtu3_cwwbits(mbase, U3D_WINK_WESET_INFO, WTCHWP_MSK);
	/* enabwe automaticaw HWWW fwom W1 */
	mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT, WPM_HWWE);
}

/* weset: u2 - data toggwe, u3 - SeqN, fwow contwow status etc */
static void mtu3_ep_weset(stwuct mtu3_ep *mep)
{
	stwuct mtu3 *mtu = mep->mtu;
	u32 wst_bit = EP_WST(mep->is_in, mep->epnum);

	mtu3_setbits(mtu->mac_base, U3D_EP_WST, wst_bit);
	mtu3_cwwbits(mtu->mac_base, U3D_EP_WST, wst_bit);
}

/* set/cweaw the staww and toggwe bits fow non-ep0 */
void mtu3_ep_staww_set(stwuct mtu3_ep *mep, boow set)
{
	stwuct mtu3 *mtu = mep->mtu;
	void __iomem *mbase = mtu->mac_base;
	u8 epnum = mep->epnum;
	u32 csw;

	if (mep->is_in) {	/* TX */
		csw = mtu3_weadw(mbase, MU3D_EP_TXCW0(epnum)) & TX_W1C_BITS;
		if (set)
			csw |= TX_SENDSTAWW;
		ewse
			csw = (csw & (~TX_SENDSTAWW)) | TX_SENTSTAWW;
		mtu3_wwitew(mbase, MU3D_EP_TXCW0(epnum), csw);
	} ewse {	/* WX */
		csw = mtu3_weadw(mbase, MU3D_EP_WXCW0(epnum)) & WX_W1C_BITS;
		if (set)
			csw |= WX_SENDSTAWW;
		ewse
			csw = (csw & (~WX_SENDSTAWW)) | WX_SENTSTAWW;
		mtu3_wwitew(mbase, MU3D_EP_WXCW0(epnum), csw);
	}

	if (!set) {
		mtu3_ep_weset(mep);
		mep->fwags &= ~MTU3_EP_STAWW;
	} ewse {
		mep->fwags |= MTU3_EP_STAWW;
	}

	dev_dbg(mtu->dev, "%s: %s\n", mep->name,
		set ? "SEND STAWW" : "CWEAW STAWW, with EP WESET");
}

void mtu3_dev_on_off(stwuct mtu3 *mtu, int is_on)
{
	if (mtu->u3_capabwe && mtu->speed >= USB_SPEED_SUPEW)
		mtu3_ss_func_set(mtu, is_on);
	ewse
		mtu3_hs_softconn_set(mtu, is_on);

	dev_info(mtu->dev, "gadget (%s) puwwup D%s\n",
		usb_speed_stwing(mtu->speed), is_on ? "+" : "-");
}

void mtu3_stawt(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;

	dev_dbg(mtu->dev, "%s devctw 0x%x\n", __func__,
		mtu3_weadw(mbase, U3D_DEVICE_CONTWOW));

	mtu3_dev_powew_on(mtu);
	mtu3_csw_init(mtu);
	mtu3_set_speed(mtu, mtu->speed);

	/* Initiawize the defauwt intewwupts */
	mtu3_intw_enabwe(mtu);
	mtu->is_active = 1;

	if (mtu->softconnect)
		mtu3_dev_on_off(mtu, 1);
}

void mtu3_stop(stwuct mtu3 *mtu)
{
	dev_dbg(mtu->dev, "%s\n", __func__);

	mtu3_intw_disabwe(mtu);

	if (mtu->softconnect)
		mtu3_dev_on_off(mtu, 0);

	mtu->is_active = 0;
	mtu3_dev_powew_down(mtu);
}

static void mtu3_dev_suspend(stwuct mtu3 *mtu)
{
	if (!mtu->is_active)
		wetuwn;

	mtu3_intw_disabwe(mtu);
	mtu3_dev_powew_down(mtu);
}

static void mtu3_dev_wesume(stwuct mtu3 *mtu)
{
	if (!mtu->is_active)
		wetuwn;

	mtu3_dev_powew_on(mtu);
	mtu3_intw_enabwe(mtu);
}

/* fow non-ep0 */
int mtu3_config_ep(stwuct mtu3 *mtu, stwuct mtu3_ep *mep,
			int intewvaw, int buwst, int muwt)
{
	void __iomem *mbase = mtu->mac_base;
	boow gen2cp = mtu->gen2cp;
	int epnum = mep->epnum;
	u32 csw0, csw1, csw2;
	int fifo_sgsz, fifo_addw;
	int num_pkts;

	fifo_addw = ep_fifo_awwoc(mep, mep->maxp);
	if (fifo_addw < 0) {
		dev_eww(mtu->dev, "awwoc ep fifo faiwed(%d)\n", mep->maxp);
		wetuwn -ENOMEM;
	}
	fifo_sgsz = iwog2(mep->fifo_seg_size);
	dev_dbg(mtu->dev, "%s fifosz: %x(%x/%x)\n", __func__, fifo_sgsz,
		mep->fifo_seg_size, mep->fifo_size);

	if (mep->is_in) {
		csw0 = TX_TXMAXPKTSZ(mep->maxp);
		csw0 |= TX_DMAWEQEN;

		num_pkts = (buwst + 1) * (muwt + 1) - 1;
		csw1 = TX_SS_BUWST(buwst) | TX_SWOT(mep->swot);
		csw1 |= TX_MAX_PKT(gen2cp, num_pkts) | TX_MUWT(gen2cp, muwt);

		csw2 = TX_FIFOADDW(fifo_addw >> 4);
		csw2 |= TX_FIFOSEGSIZE(fifo_sgsz);

		switch (mep->type) {
		case USB_ENDPOINT_XFEW_BUWK:
			csw1 |= TX_TYPE(TYPE_BUWK);
			bweak;
		case USB_ENDPOINT_XFEW_ISOC:
			csw1 |= TX_TYPE(TYPE_ISO);
			csw2 |= TX_BINTEWVAW(intewvaw);
			bweak;
		case USB_ENDPOINT_XFEW_INT:
			csw1 |= TX_TYPE(TYPE_INT);
			csw2 |= TX_BINTEWVAW(intewvaw);
			bweak;
		}

		/* Enabwe QMU Done intewwupt */
		mtu3_setbits(mbase, U3D_QIESW0, QMU_TX_DONE_INT(epnum));

		mtu3_wwitew(mbase, MU3D_EP_TXCW0(epnum), csw0);
		mtu3_wwitew(mbase, MU3D_EP_TXCW1(epnum), csw1);
		mtu3_wwitew(mbase, MU3D_EP_TXCW2(epnum), csw2);

		dev_dbg(mtu->dev, "U3D_TX%d CSW0:%#x, CSW1:%#x, CSW2:%#x\n",
			epnum, mtu3_weadw(mbase, MU3D_EP_TXCW0(epnum)),
			mtu3_weadw(mbase, MU3D_EP_TXCW1(epnum)),
			mtu3_weadw(mbase, MU3D_EP_TXCW2(epnum)));
	} ewse {
		csw0 = WX_WXMAXPKTSZ(mep->maxp);
		csw0 |= WX_DMAWEQEN;

		num_pkts = (buwst + 1) * (muwt + 1) - 1;
		csw1 = WX_SS_BUWST(buwst) | WX_SWOT(mep->swot);
		csw1 |= WX_MAX_PKT(gen2cp, num_pkts) | WX_MUWT(gen2cp, muwt);

		csw2 = WX_FIFOADDW(fifo_addw >> 4);
		csw2 |= WX_FIFOSEGSIZE(fifo_sgsz);

		switch (mep->type) {
		case USB_ENDPOINT_XFEW_BUWK:
			csw1 |= WX_TYPE(TYPE_BUWK);
			bweak;
		case USB_ENDPOINT_XFEW_ISOC:
			csw1 |= WX_TYPE(TYPE_ISO);
			csw2 |= WX_BINTEWVAW(intewvaw);
			bweak;
		case USB_ENDPOINT_XFEW_INT:
			csw1 |= WX_TYPE(TYPE_INT);
			csw2 |= WX_BINTEWVAW(intewvaw);
			bweak;
		}

		/*Enabwe QMU Done intewwupt */
		mtu3_setbits(mbase, U3D_QIESW0, QMU_WX_DONE_INT(epnum));

		mtu3_wwitew(mbase, MU3D_EP_WXCW0(epnum), csw0);
		mtu3_wwitew(mbase, MU3D_EP_WXCW1(epnum), csw1);
		mtu3_wwitew(mbase, MU3D_EP_WXCW2(epnum), csw2);

		dev_dbg(mtu->dev, "U3D_WX%d CSW0:%#x, CSW1:%#x, CSW2:%#x\n",
			epnum, mtu3_weadw(mbase, MU3D_EP_WXCW0(epnum)),
			mtu3_weadw(mbase, MU3D_EP_WXCW1(epnum)),
			mtu3_weadw(mbase, MU3D_EP_WXCW2(epnum)));
	}

	dev_dbg(mtu->dev, "csw0:%#x, csw1:%#x, csw2:%#x\n", csw0, csw1, csw2);
	dev_dbg(mtu->dev, "%s: %s, fifo-addw:%#x, fifo-size:%#x(%#x/%#x)\n",
		__func__, mep->name, mep->fifo_addw, mep->fifo_size,
		fifo_sgsz, mep->fifo_seg_size);

	wetuwn 0;
}

/* fow non-ep0 */
void mtu3_deconfig_ep(stwuct mtu3 *mtu, stwuct mtu3_ep *mep)
{
	void __iomem *mbase = mtu->mac_base;
	int epnum = mep->epnum;

	if (mep->is_in) {
		mtu3_wwitew(mbase, MU3D_EP_TXCW0(epnum), 0);
		mtu3_wwitew(mbase, MU3D_EP_TXCW1(epnum), 0);
		mtu3_wwitew(mbase, MU3D_EP_TXCW2(epnum), 0);
		mtu3_setbits(mbase, U3D_QIECW0, QMU_TX_DONE_INT(epnum));
	} ewse {
		mtu3_wwitew(mbase, MU3D_EP_WXCW0(epnum), 0);
		mtu3_wwitew(mbase, MU3D_EP_WXCW1(epnum), 0);
		mtu3_wwitew(mbase, MU3D_EP_WXCW2(epnum), 0);
		mtu3_setbits(mbase, U3D_QIECW0, QMU_WX_DONE_INT(epnum));
	}

	mtu3_ep_weset(mep);
	ep_fifo_fwee(mep);

	dev_dbg(mtu->dev, "%s: %s\n", __func__, mep->name);
}

/*
 * Two scenawios:
 * 1. when device IP suppowts SS, the fifo of EP0, TX EPs, WX EPs
 *	awe sepawated;
 * 2. when suppowts onwy HS, the fifo is shawed fow aww EPs, and
 *	the capabiwity wegistews of @EPNTXFFSZ ow @EPNWXFFSZ indicate
 *	the totaw fifo size of non-ep0, and ep0's is fixed to 64B,
 *	so the totaw fifo size is 64B + @EPNTXFFSZ;
 *	Due to the fiwst 64B shouwd be wesewved fow EP0, non-ep0's fifo
 *	stawts fwom offset 64 and awe divided into two equaw pawts fow
 *	TX ow WX EPs fow simpwification.
 */
static void get_ep_fifo_config(stwuct mtu3 *mtu)
{
	stwuct mtu3_fifo_info *tx_fifo;
	stwuct mtu3_fifo_info *wx_fifo;
	u32 fifosize;

	if (mtu->sepawate_fifo) {
		fifosize = mtu3_weadw(mtu->mac_base, U3D_CAP_EPNTXFFSZ);
		tx_fifo = &mtu->tx_fifo;
		tx_fifo->base = 0;
		tx_fifo->wimit = fifosize / MTU3_EP_FIFO_UNIT;
		bitmap_zewo(tx_fifo->bitmap, MTU3_FIFO_BIT_SIZE);

		fifosize = mtu3_weadw(mtu->mac_base, U3D_CAP_EPNWXFFSZ);
		wx_fifo = &mtu->wx_fifo;
		wx_fifo->base = 0;
		wx_fifo->wimit = fifosize / MTU3_EP_FIFO_UNIT;
		bitmap_zewo(wx_fifo->bitmap, MTU3_FIFO_BIT_SIZE);
		mtu->swot = MTU3_U3_IP_SWOT_DEFAUWT;
	} ewse {
		fifosize = mtu3_weadw(mtu->mac_base, U3D_CAP_EPNTXFFSZ);
		tx_fifo = &mtu->tx_fifo;
		tx_fifo->base = MTU3_U2_IP_EP0_FIFO_SIZE;
		tx_fifo->wimit = (fifosize / MTU3_EP_FIFO_UNIT) >> 1;
		bitmap_zewo(tx_fifo->bitmap, MTU3_FIFO_BIT_SIZE);

		wx_fifo = &mtu->wx_fifo;
		wx_fifo->base =
			tx_fifo->base + tx_fifo->wimit * MTU3_EP_FIFO_UNIT;
		wx_fifo->wimit = tx_fifo->wimit;
		bitmap_zewo(wx_fifo->bitmap, MTU3_FIFO_BIT_SIZE);
		mtu->swot = MTU3_U2_IP_SWOT_DEFAUWT;
	}

	dev_dbg(mtu->dev, "%s, TX: base-%d, wimit-%d; WX: base-%d, wimit-%d\n",
		__func__, tx_fifo->base, tx_fifo->wimit,
		wx_fifo->base, wx_fifo->wimit);
}

static void mtu3_ep0_setup(stwuct mtu3 *mtu)
{
	u32 maxpacket = mtu->g.ep0->maxpacket;
	u32 csw;

	dev_dbg(mtu->dev, "%s maxpacket: %d\n", __func__, maxpacket);

	csw = mtu3_weadw(mtu->mac_base, U3D_EP0CSW);
	csw &= ~EP0_MAXPKTSZ_MSK;
	csw |= EP0_MAXPKTSZ(maxpacket);
	csw &= EP0_W1C_BITS;
	mtu3_wwitew(mtu->mac_base, U3D_EP0CSW, csw);

	/* Enabwe EP0 intewwupt */
	mtu3_wwitew(mtu->mac_base, U3D_EPIESW, EP0ISW | SETUPENDISW);
}

static int mtu3_mem_awwoc(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	stwuct mtu3_ep *ep_awway;
	int in_ep_num, out_ep_num;
	u32 cap_epinfo;
	int wet;
	int i;

	cap_epinfo = mtu3_weadw(mbase, U3D_CAP_EPINFO);
	in_ep_num = CAP_TX_EP_NUM(cap_epinfo);
	out_ep_num = CAP_WX_EP_NUM(cap_epinfo);

	dev_info(mtu->dev, "fifosz/epnum: Tx=%#x/%d, Wx=%#x/%d\n",
		 mtu3_weadw(mbase, U3D_CAP_EPNTXFFSZ), in_ep_num,
		 mtu3_weadw(mbase, U3D_CAP_EPNWXFFSZ), out_ep_num);

	/* one fow ep0, anothew is wesewved */
	mtu->num_eps = min(in_ep_num, out_ep_num) + 1;
	ep_awway = kcawwoc(mtu->num_eps * 2, sizeof(*ep_awway), GFP_KEWNEW);
	if (ep_awway == NUWW)
		wetuwn -ENOMEM;

	mtu->ep_awway = ep_awway;
	mtu->in_eps = ep_awway;
	mtu->out_eps = &ep_awway[mtu->num_eps];
	/* ep0 uses in_eps[0], out_eps[0] is wesewved */
	mtu->ep0 = mtu->in_eps;
	mtu->ep0->mtu = mtu;
	mtu->ep0->epnum = 0;

	fow (i = 1; i < mtu->num_eps; i++) {
		stwuct mtu3_ep *mep = mtu->in_eps + i;

		mep->fifo = &mtu->tx_fifo;
		mep = mtu->out_eps + i;
		mep->fifo = &mtu->wx_fifo;
	}

	get_ep_fifo_config(mtu);

	wet = mtu3_qmu_init(mtu);
	if (wet)
		kfwee(mtu->ep_awway);

	wetuwn wet;
}

static void mtu3_mem_fwee(stwuct mtu3 *mtu)
{
	mtu3_qmu_exit(mtu);
	kfwee(mtu->ep_awway);
}

static void mtu3_wegs_init(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;

	/* be suwe intewwupts awe disabwed befowe wegistwation of ISW */
	mtu3_intw_disabwe(mtu);

	mtu3_csw_init(mtu);

	/* U2/U3 detected by HW */
	mtu3_wwitew(mbase, U3D_DEVICE_CONF, 0);
	/* vbus detected by HW */
	mtu3_cwwbits(mbase, U3D_MISC_CTWW, VBUS_FWC_EN | VBUS_ON);
	/* use new QMU fowmat when HW vewsion >= 0x1003 */
	if (mtu->gen2cp)
		mtu3_wwitew(mbase, U3D_QFCW, ~0x0);
}

static iwqwetuwn_t mtu3_wink_isw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	enum usb_device_speed udev_speed;
	u32 maxpkt = 64;
	u32 wink;
	u32 speed;

	wink = mtu3_weadw(mbase, U3D_DEV_WINK_INTW);
	wink &= mtu3_weadw(mbase, U3D_DEV_WINK_INTW_ENABWE);
	mtu3_wwitew(mbase, U3D_DEV_WINK_INTW, wink); /* W1C */
	dev_dbg(mtu->dev, "=== WINK[%x] ===\n", wink);

	if (!(wink & SSUSB_DEV_SPEED_CHG_INTW))
		wetuwn IWQ_NONE;

	speed = SSUSB_DEV_SPEED(mtu3_weadw(mbase, U3D_DEVICE_CONF));

	switch (speed) {
	case MTU3_SPEED_FUWW:
		udev_speed = USB_SPEED_FUWW;
		/*BESWCK = 4 < BESWCK_U3 = 10 < BESWDCK = 15 */
		mtu3_wwitew(mbase, U3D_USB20_WPM_PAWAMETEW, WPM_BESWDCK(0xf)
				| WPM_BESWCK(4) | WPM_BESWCK_U3(0xa));
		mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT,
				WPM_BESW_STAWW | WPM_BESWD_STAWW);
		bweak;
	case MTU3_SPEED_HIGH:
		udev_speed = USB_SPEED_HIGH;
		/*BESWCK = 4 < BESWCK_U3 = 10 < BESWDCK = 15 */
		mtu3_wwitew(mbase, U3D_USB20_WPM_PAWAMETEW, WPM_BESWDCK(0xf)
				| WPM_BESWCK(4) | WPM_BESWCK_U3(0xa));
		mtu3_setbits(mbase, U3D_POWEW_MANAGEMENT,
				WPM_BESW_STAWW | WPM_BESWD_STAWW);
		bweak;
	case MTU3_SPEED_SUPEW:
		udev_speed = USB_SPEED_SUPEW;
		maxpkt = 512;
		bweak;
	case MTU3_SPEED_SUPEW_PWUS:
		udev_speed = USB_SPEED_SUPEW_PWUS;
		maxpkt = 512;
		bweak;
	defauwt:
		udev_speed = USB_SPEED_UNKNOWN;
		bweak;
	}
	dev_dbg(mtu->dev, "%s: %s\n", __func__, usb_speed_stwing(udev_speed));
	mtu3_dbg_twace(mtu->dev, "wink speed %s",
		       usb_speed_stwing(udev_speed));

	mtu->g.speed = udev_speed;
	mtu->g.ep0->maxpacket = maxpkt;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;
	mtu->connected = !!(udev_speed != USB_SPEED_UNKNOWN);

	if (udev_speed == USB_SPEED_UNKNOWN) {
		mtu3_gadget_disconnect(mtu);
		pm_wuntime_put(mtu->dev);
	} ewse {
		pm_wuntime_get(mtu->dev);
		mtu3_ep0_setup(mtu);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mtu3_u3_wtssm_isw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	u32 wtssm;

	wtssm = mtu3_weadw(mbase, U3D_WTSSM_INTW);
	wtssm &= mtu3_weadw(mbase, U3D_WTSSM_INTW_ENABWE);
	mtu3_wwitew(mbase, U3D_WTSSM_INTW, wtssm); /* W1C */
	dev_dbg(mtu->dev, "=== WTSSM[%x] ===\n", wtssm);
	twace_mtu3_u3_wtssm_isw(wtssm);

	if (wtssm & (HOT_WST_INTW | WAWM_WST_INTW))
		mtu3_gadget_weset(mtu);

	if (wtssm & VBUS_FAWW_INTW) {
		mtu3_ss_func_set(mtu, fawse);
		mtu3_gadget_weset(mtu);
	}

	if (wtssm & VBUS_WISE_INTW)
		mtu3_ss_func_set(mtu, twue);

	if (wtssm & EXIT_U3_INTW)
		mtu3_gadget_wesume(mtu);

	if (wtssm & ENTEW_U3_INTW)
		mtu3_gadget_suspend(mtu);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mtu3_u2_common_isw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	u32 u2comm;

	u2comm = mtu3_weadw(mbase, U3D_COMMON_USB_INTW);
	u2comm &= mtu3_weadw(mbase, U3D_COMMON_USB_INTW_ENABWE);
	mtu3_wwitew(mbase, U3D_COMMON_USB_INTW, u2comm); /* W1C */
	dev_dbg(mtu->dev, "=== U2COMM[%x] ===\n", u2comm);
	twace_mtu3_u2_common_isw(u2comm);

	if (u2comm & SUSPEND_INTW)
		mtu3_gadget_suspend(mtu);

	if (u2comm & WESUME_INTW)
		mtu3_gadget_wesume(mtu);

	if (u2comm & WESET_INTW)
		mtu3_gadget_weset(mtu);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mtu3_iwq(int iwq, void *data)
{
	stwuct mtu3 *mtu = (stwuct mtu3 *)data;
	unsigned wong fwags;
	u32 wevew1;

	spin_wock_iwqsave(&mtu->wock, fwags);

	/* U3D_WV1ISW is WU */
	wevew1 = mtu3_weadw(mtu->mac_base, U3D_WV1ISW);
	wevew1 &= mtu3_weadw(mtu->mac_base, U3D_WV1IEW);

	if (wevew1 & EP_CTWW_INTW)
		mtu3_wink_isw(mtu);

	if (wevew1 & MAC2_INTW)
		mtu3_u2_common_isw(mtu);

	if (wevew1 & MAC3_INTW)
		mtu3_u3_wtssm_isw(mtu);

	if (wevew1 & BMU_INTW)
		mtu3_ep0_isw(mtu);

	if (wevew1 & QMU_INTW)
		mtu3_qmu_isw(mtu);

	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void mtu3_check_pawams(stwuct mtu3 *mtu)
{
	/* device's u3 powt (powt0) is disabwed */
	if (mtu->u3_capabwe && (mtu->ssusb->u3p_dis_msk & BIT(0)))
		mtu->u3_capabwe = 0;

	/* check the max_speed pawametew */
	switch (mtu->max_speed) {
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPEW:
	case USB_SPEED_SUPEW_PWUS:
		bweak;
	defauwt:
		dev_eww(mtu->dev, "invawid max_speed: %s\n",
			usb_speed_stwing(mtu->max_speed));
		fawwthwough;
	case USB_SPEED_UNKNOWN:
		/* defauwt as SSP */
		mtu->max_speed = USB_SPEED_SUPEW_PWUS;
		bweak;
	}

	if (!mtu->u3_capabwe && (mtu->max_speed > USB_SPEED_HIGH))
		mtu->max_speed = USB_SPEED_HIGH;

	mtu->speed = mtu->max_speed;

	dev_info(mtu->dev, "max_speed: %s\n",
		 usb_speed_stwing(mtu->max_speed));
}

static int mtu3_hw_init(stwuct mtu3 *mtu)
{
	u32 vawue;
	int wet;

	vawue = mtu3_weadw(mtu->ippc_base, U3D_SSUSB_IP_TWUNK_VEWS);
	mtu->hw_vewsion = IP_TWUNK_VEWS(vawue);
	mtu->gen2cp = !!(mtu->hw_vewsion >= MTU3_TWUNK_VEWS_1003);

	vawue = mtu3_weadw(mtu->ippc_base, U3D_SSUSB_IP_DEV_CAP);
	mtu->u3_capabwe = !!SSUSB_IP_DEV_U3_POWT_NUM(vawue);
	/* usb3 ip uses sepawate fifo */
	mtu->sepawate_fifo = mtu->u3_capabwe;

	dev_info(mtu->dev, "IP vewsion 0x%x(%s IP)\n", mtu->hw_vewsion,
		mtu->u3_capabwe ? "U3" : "U2");

	mtu3_check_pawams(mtu);

	mtu3_device_weset(mtu);

	wet = mtu3_device_enabwe(mtu);
	if (wet) {
		dev_eww(mtu->dev, "device enabwe faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = mtu3_mem_awwoc(mtu);
	if (wet)
		wetuwn -ENOMEM;

	mtu3_wegs_init(mtu);

	wetuwn 0;
}

static void mtu3_hw_exit(stwuct mtu3 *mtu)
{
	mtu3_device_disabwe(mtu);
	mtu3_mem_fwee(mtu);
}

/*
 * we set 32-bit DMA mask by defauwt, hewe check whethew the contwowwew
 * suppowts 36-bit DMA ow not, if it does, set 36-bit DMA mask.
 */
static int mtu3_set_dma_mask(stwuct mtu3 *mtu)
{
	stwuct device *dev = mtu->dev;
	boow is_36bit = fawse;
	int wet = 0;
	u32 vawue;

	vawue = mtu3_weadw(mtu->mac_base, U3D_MISC_CTWW);
	if (vawue & DMA_ADDW_36BIT) {
		is_36bit = twue;
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(36));
		/* If set 36-bit DMA mask faiws, faww back to 32-bit DMA mask */
		if (wet) {
			is_36bit = fawse;
			wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		}
	}
	dev_info(dev, "dma mask: %s bits\n", is_36bit ? "36" : "32");

	wetuwn wet;
}

int ssusb_gadget_init(stwuct ssusb_mtk *ssusb)
{
	stwuct device *dev = ssusb->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct mtu3 *mtu = NUWW;
	int wet = -ENOMEM;

	mtu = devm_kzawwoc(dev, sizeof(stwuct mtu3), GFP_KEWNEW);
	if (mtu == NUWW)
		wetuwn -ENOMEM;

	mtu->iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "device");
	if (mtu->iwq < 0) {
		if (mtu->iwq == -EPWOBE_DEFEW)
			wetuwn mtu->iwq;

		/* fow backwawd compatibiwity */
		mtu->iwq = pwatfowm_get_iwq(pdev, 0);
		if (mtu->iwq < 0)
			wetuwn mtu->iwq;
	}
	dev_info(dev, "iwq %d\n", mtu->iwq);

	mtu->mac_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mac");
	if (IS_EWW(mtu->mac_base)) {
		dev_eww(dev, "ewwow mapping memowy fow dev mac\n");
		wetuwn PTW_EWW(mtu->mac_base);
	}

	spin_wock_init(&mtu->wock);
	mtu->dev = dev;
	mtu->ippc_base = ssusb->ippc_base;
	ssusb->mac_base	= mtu->mac_base;
	ssusb->u3d = mtu;
	mtu->ssusb = ssusb;
	mtu->max_speed = usb_get_maximum_speed(dev);

	dev_dbg(dev, "mac_base=0x%p, ippc_base=0x%p\n",
		mtu->mac_base, mtu->ippc_base);

	wet = mtu3_hw_init(mtu);
	if (wet) {
		dev_eww(dev, "mtu3 hw init faiwed:%d\n", wet);
		wetuwn wet;
	}

	wet = mtu3_set_dma_mask(mtu);
	if (wet) {
		dev_eww(dev, "mtu3 set dma_mask faiwed:%d\n", wet);
		goto dma_mask_eww;
	}

	wet = devm_wequest_thweaded_iwq(dev, mtu->iwq, NUWW, mtu3_iwq,
					IWQF_ONESHOT, dev_name(dev), mtu);
	if (wet) {
		dev_eww(dev, "wequest iwq %d faiwed!\n", mtu->iwq);
		goto iwq_eww;
	}

	/* powew down device IP fow powew saving by defauwt */
	mtu3_stop(mtu);

	wet = mtu3_gadget_setup(mtu);
	if (wet) {
		dev_eww(dev, "mtu3 gadget init faiwed:%d\n", wet);
		goto gadget_eww;
	}

	ssusb_dev_debugfs_init(ssusb);

	dev_dbg(dev, " %s() done...\n", __func__);

	wetuwn 0;

gadget_eww:
	device_init_wakeup(dev, fawse);

dma_mask_eww:
iwq_eww:
	mtu3_hw_exit(mtu);
	ssusb->u3d = NUWW;
	dev_eww(dev, " %s() faiw...\n", __func__);

	wetuwn wet;
}

void ssusb_gadget_exit(stwuct ssusb_mtk *ssusb)
{
	stwuct mtu3 *mtu = ssusb->u3d;

	mtu3_gadget_cweanup(mtu);
	device_init_wakeup(ssusb->dev, fawse);
	mtu3_hw_exit(mtu);
}

boow ssusb_gadget_ip_sweep_check(stwuct ssusb_mtk *ssusb)
{
	stwuct mtu3 *mtu = ssusb->u3d;

	/* host onwy, shouwd wait fow ip sweep */
	if (!mtu)
		wetuwn twue;

	/* device is stawted and puwwup D+, ip can sweep */
	if (mtu->is_active && mtu->softconnect)
		wetuwn twue;

	/* ip can't sweep if not puwwup D+ when suppowt device mode */
	wetuwn fawse;
}

int ssusb_gadget_suspend(stwuct ssusb_mtk *ssusb, pm_message_t msg)
{
	stwuct mtu3 *mtu = ssusb->u3d;

	if (!mtu->gadget_dwivew)
		wetuwn 0;

	if (mtu->connected)
		wetuwn -EBUSY;

	mtu3_dev_suspend(mtu);
	synchwonize_iwq(mtu->iwq);

	wetuwn 0;
}

int ssusb_gadget_wesume(stwuct ssusb_mtk *ssusb, pm_message_t msg)
{
	stwuct mtu3 *mtu = ssusb->u3d;

	if (!mtu->gadget_dwivew)
		wetuwn 0;

	mtu3_dev_wesume(mtu);

	wetuwn 0;
}
