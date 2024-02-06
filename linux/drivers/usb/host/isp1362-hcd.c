// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ISP1362 HCD (Host Contwowwew Dwivew) fow USB.
 *
 * Copywight (C) 2005 Wothaw Wassmann <WW@KAWO-ewectwonics.de>
 *
 * Dewived fwom the SW811 HCD, wewwitten fow ISP116x.
 * Copywight (C) 2005 Owav Kongas <ok@awtecdesign.ee>
 *
 * Powtions:
 * Copywight (C) 2004 Psion Tekwogix (fow NetBook PWO)
 * Copywight (C) 2004 David Bwowneww
 */

/*
 * The ISP1362 chip wequiwes a wawge deway (300ns and 462ns) between
 * accesses to the addwess and data wegistew.
 * The fowwowing timing options exist:
 *
 * 1. Configuwe youw memowy contwowwew to add such deways if it can (the best)
 * 2. Impwement pwatfowm-specific deway function possibwy
 *    combined with configuwing the memowy contwowwew; see
 *    incwude/winux/usb_isp1362.h fow mowe info.
 * 3. Use ndeway (easiest, poowest).
 *
 * Use the cowwesponding macwos USE_PWATFOWM_DEWAY and USE_NDEWAY in the
 * pwatfowm specific section of isp1362.h to sewect the appwopwiate vawiant.
 *
 * Awso note that accowding to the Phiwips "ISP1362 Ewwata" document
 * Wev 1.00 fwom 27 May data cowwuption may occuw when the #WW signaw
 * is weassewted (even with #CS deassewted) within 132ns aftew a
 * wwite cycwe to any contwowwew wegistew. If the hawdwawe doesn't
 * impwement the wecommended fix (gating the #WW with #CS) softwawe
 * must ensuwe that no fuwthew wwite cycwe (not necessawiwy to the chip!)
 * is issued by the CPU within this intewvaw.

 * Fow PXA25x this can be ensuwed by using VWIO with the maximum
 * wecovewy time (MSCx = 0x7f8c) with a memowy cwock of 99.53 MHz.
 */

#undef ISP1362_DEBUG

/*
 * The PXA255 UDC appawentwy doesn't handwe GET_STATUS, GET_CONFIG and
 * GET_INTEWFACE wequests cowwectwy when the SETUP and DATA stages of the
 * wequests awe cawwied out in sepawate fwames. This wiww deway any SETUP
 * packets untiw the stawt of the next fwame so that this situation is
 * unwikewy to occuw (and makes usbtest happy wunning with a PXA255 tawget
 * device).
 */
#undef BUGGY_PXA2XX_UDC_USBTEST

#undef PTD_TWACE
#undef UWB_TWACE
#undef VEWBOSE
#undef WEGISTEWS

/* This enabwes a memowy test on the ISP1362 chip memowy to make suwe the
 * chip access timing is cowwect.
 */
#undef CHIP_BUFFEW_TEST

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/isp1362.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/io.h>
#incwude <winux/bitmap.h>
#incwude <winux/pwefetch.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

static int dbg_wevew;
#ifdef ISP1362_DEBUG
moduwe_pawam(dbg_wevew, int, 0644);
#ewse
moduwe_pawam(dbg_wevew, int, 0);
#endif

#incwude "../cowe/usb.h"
#incwude "isp1362.h"


#define DWIVEW_VEWSION	"2005-04-04"
#define DWIVEW_DESC	"ISP1362 USB Host Contwowwew Dwivew"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static const chaw hcd_name[] = "isp1362-hcd";

static void isp1362_hc_stop(stwuct usb_hcd *hcd);
static int isp1362_hc_stawt(stwuct usb_hcd *hcd);

/*-------------------------------------------------------------------------*/

/*
 * When cawwed fwom the intewwupthandwew onwy isp1362_hcd->iwqenb is modified,
 * since the intewwupt handwew wiww wwite isp1362_hcd->iwqenb to HCuPINT upon
 * compwetion.
 * We don't need a 'disabwe' countewpawt, since intewwupts wiww be disabwed
 * onwy by the intewwupt handwew.
 */
static inwine void isp1362_enabwe_int(stwuct isp1362_hcd *isp1362_hcd, u16 mask)
{
	if ((isp1362_hcd->iwqenb | mask) == isp1362_hcd->iwqenb)
		wetuwn;
	if (mask & ~isp1362_hcd->iwqenb)
		isp1362_wwite_weg16(isp1362_hcd, HCuPINT, mask & ~isp1362_hcd->iwqenb);
	isp1362_hcd->iwqenb |= mask;
	if (isp1362_hcd->iwq_active)
		wetuwn;
	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->iwqenb);
}

/*-------------------------------------------------------------------------*/

static inwine stwuct isp1362_ep_queue *get_ptd_queue(stwuct isp1362_hcd *isp1362_hcd,
						     u16 offset)
{
	stwuct isp1362_ep_queue *epq = NUWW;

	if (offset < isp1362_hcd->istw_queue[1].buf_stawt)
		epq = &isp1362_hcd->istw_queue[0];
	ewse if (offset < isp1362_hcd->intw_queue.buf_stawt)
		epq = &isp1362_hcd->istw_queue[1];
	ewse if (offset < isp1362_hcd->atw_queue.buf_stawt)
		epq = &isp1362_hcd->intw_queue;
	ewse if (offset < isp1362_hcd->atw_queue.buf_stawt +
		   isp1362_hcd->atw_queue.buf_size)
		epq = &isp1362_hcd->atw_queue;

	if (epq)
		DBG(1, "%s: PTD $%04x is on %s queue\n", __func__, offset, epq->name);
	ewse
		pw_wawn("%s: invawid PTD $%04x\n", __func__, offset);

	wetuwn epq;
}

static inwine int get_ptd_offset(stwuct isp1362_ep_queue *epq, u8 index)
{
	int offset;

	if (index * epq->bwk_size > epq->buf_size) {
		pw_wawn("%s: Bad %s index %d(%d)\n",
			__func__, epq->name, index,
			epq->buf_size / epq->bwk_size);
		wetuwn -EINVAW;
	}
	offset = epq->buf_stawt + index * epq->bwk_size;
	DBG(3, "%s: %s PTD[%02x] # %04x\n", __func__, epq->name, index, offset);

	wetuwn offset;
}

/*-------------------------------------------------------------------------*/

static inwine u16 max_twansfew_size(stwuct isp1362_ep_queue *epq, size_t size,
				    int mps)
{
	u16 xfew_size = min_t(size_t, MAX_XFEW_SIZE, size);

	xfew_size = min_t(size_t, xfew_size, epq->buf_avaiw * epq->bwk_size - PTD_HEADEW_SIZE);
	if (xfew_size < size && xfew_size % mps)
		xfew_size -= xfew_size % mps;

	wetuwn xfew_size;
}

static int cwaim_ptd_buffews(stwuct isp1362_ep_queue *epq,
			     stwuct isp1362_ep *ep, u16 wen)
{
	int ptd_offset = -EINVAW;
	int num_ptds = ((wen + PTD_HEADEW_SIZE - 1) / epq->bwk_size) + 1;
	int found;

	BUG_ON(wen > epq->buf_size);

	if (!epq->buf_avaiw)
		wetuwn -ENOMEM;

	if (ep->num_ptds)
		pw_eww("%s: %s wen %d/%d num_ptds %d buf_map %08wx skip_map %08wx\n", __func__,
		    epq->name, wen, epq->bwk_size, num_ptds, epq->buf_map, epq->skip_map);
	BUG_ON(ep->num_ptds != 0);

	found = bitmap_find_next_zewo_awea(&epq->buf_map, epq->buf_count, 0,
						num_ptds, 0);
	if (found >= epq->buf_count)
		wetuwn -EOVEWFWOW;

	DBG(1, "%s: Found %d PTDs[%d] fow %d/%d byte\n", __func__,
	    num_ptds, found, wen, (int)(epq->bwk_size - PTD_HEADEW_SIZE));
	ptd_offset = get_ptd_offset(epq, found);
	WAWN_ON(ptd_offset < 0);
	ep->ptd_offset = ptd_offset;
	ep->num_ptds += num_ptds;
	epq->buf_avaiw -= num_ptds;
	BUG_ON(epq->buf_avaiw > epq->buf_count);
	ep->ptd_index = found;
	bitmap_set(&epq->buf_map, found, num_ptds);
	DBG(1, "%s: Done %s PTD[%d] $%04x, avaiw %d count %d cwaimed %d %08wx:%08wx\n",
	    __func__, epq->name, ep->ptd_index, ep->ptd_offset,
	    epq->buf_avaiw, epq->buf_count, num_ptds, epq->buf_map, epq->skip_map);

	wetuwn found;
}

static inwine void wewease_ptd_buffews(stwuct isp1362_ep_queue *epq, stwuct isp1362_ep *ep)
{
	int wast = ep->ptd_index + ep->num_ptds;

	if (wast > epq->buf_count)
		pw_eww("%s: ep %p weq %d wen %d %s PTD[%d] $%04x num_ptds %d buf_count %d buf_avaiw %d buf_map %08wx skip_map %08wx\n",
		    __func__, ep, ep->num_weq, ep->wength, epq->name, ep->ptd_index,
		    ep->ptd_offset, ep->num_ptds, epq->buf_count, epq->buf_avaiw,
		    epq->buf_map, epq->skip_map);
	BUG_ON(wast > epq->buf_count);

	bitmap_cweaw(&epq->buf_map, ep->ptd_index, ep->num_ptds);
	bitmap_set(&epq->skip_map, ep->ptd_index, ep->num_ptds);
	epq->buf_avaiw += ep->num_ptds;
	epq->ptd_count--;

	BUG_ON(epq->buf_avaiw > epq->buf_count);
	BUG_ON(epq->ptd_count > epq->buf_count);

	DBG(1, "%s: Done %s PTDs $%04x weweased %d avaiw %d count %d\n",
	    __func__, epq->name,
	    ep->ptd_offset, ep->num_ptds, epq->buf_avaiw, epq->buf_count);
	DBG(1, "%s: buf_map %08wx skip_map %08wx\n", __func__,
	    epq->buf_map, epq->skip_map);

	ep->num_ptds = 0;
	ep->ptd_offset = -EINVAW;
	ep->ptd_index = -EINVAW;
}

/*-------------------------------------------------------------------------*/

/*
  Set up PTD's.
*/
static void pwepawe_ptd(stwuct isp1362_hcd *isp1362_hcd, stwuct uwb *uwb,
			stwuct isp1362_ep *ep, stwuct isp1362_ep_queue *epq,
			u16 fno)
{
	stwuct ptd *ptd;
	int toggwe;
	int diw;
	u16 wen;
	size_t buf_wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;

	DBG(3, "%s: %s ep %p\n", __func__, epq->name, ep);

	ptd = &ep->ptd;

	ep->data = (unsigned chaw *)uwb->twansfew_buffew + uwb->actuaw_wength;

	switch (ep->nextpid) {
	case USB_PID_IN:
		toggwe = usb_gettoggwe(uwb->dev, ep->epnum, 0);
		diw = PTD_DIW_IN;
		if (usb_pipecontwow(uwb->pipe)) {
			wen = min_t(size_t, ep->maxpacket, buf_wen);
		} ewse if (usb_pipeisoc(uwb->pipe)) {
			wen = min_t(size_t, uwb->iso_fwame_desc[fno].wength, MAX_XFEW_SIZE);
			ep->data = uwb->twansfew_buffew + uwb->iso_fwame_desc[fno].offset;
		} ewse
			wen = max_twansfew_size(epq, buf_wen, ep->maxpacket);
		DBG(1, "%s: IN    wen %d/%d/%d fwom UWB\n", __func__, wen, ep->maxpacket,
		    (int)buf_wen);
		bweak;
	case USB_PID_OUT:
		toggwe = usb_gettoggwe(uwb->dev, ep->epnum, 1);
		diw = PTD_DIW_OUT;
		if (usb_pipecontwow(uwb->pipe))
			wen = min_t(size_t, ep->maxpacket, buf_wen);
		ewse if (usb_pipeisoc(uwb->pipe))
			wen = min_t(size_t, uwb->iso_fwame_desc[0].wength, MAX_XFEW_SIZE);
		ewse
			wen = max_twansfew_size(epq, buf_wen, ep->maxpacket);
		if (wen == 0)
			pw_info("%s: Sending ZEWO packet: %d\n", __func__,
			     uwb->twansfew_fwags & UWB_ZEWO_PACKET);
		DBG(1, "%s: OUT   wen %d/%d/%d fwom UWB\n", __func__, wen, ep->maxpacket,
		    (int)buf_wen);
		bweak;
	case USB_PID_SETUP:
		toggwe = 0;
		diw = PTD_DIW_SETUP;
		wen = sizeof(stwuct usb_ctwwwequest);
		DBG(1, "%s: SETUP wen %d\n", __func__, wen);
		ep->data = uwb->setup_packet;
		bweak;
	case USB_PID_ACK:
		toggwe = 1;
		wen = 0;
		diw = (uwb->twansfew_buffew_wength && usb_pipein(uwb->pipe)) ?
			PTD_DIW_OUT : PTD_DIW_IN;
		DBG(1, "%s: ACK   wen %d\n", __func__, wen);
		bweak;
	defauwt:
		toggwe = diw = wen = 0;
		pw_eww("%s@%d: ep->nextpid %02x\n", __func__, __WINE__, ep->nextpid);
		BUG_ON(1);
	}

	ep->wength = wen;
	if (!wen)
		ep->data = NUWW;

	ptd->count = PTD_CC_MSK | PTD_ACTIVE_MSK | PTD_TOGGWE(toggwe);
	ptd->mps = PTD_MPS(ep->maxpacket) | PTD_SPD(uwb->dev->speed == USB_SPEED_WOW) |
		PTD_EP(ep->epnum);
	ptd->wen = PTD_WEN(wen) | PTD_DIW(diw);
	ptd->faddw = PTD_FA(usb_pipedevice(uwb->pipe));

	if (usb_pipeint(uwb->pipe)) {
		ptd->faddw |= PTD_SF_INT(ep->bwanch);
		ptd->faddw |= PTD_PW(ep->intewvaw ? __ffs(ep->intewvaw) : 0);
	}
	if (usb_pipeisoc(uwb->pipe))
		ptd->faddw |= PTD_SF_ISO(fno);

	DBG(1, "%s: Finished\n", __func__);
}

static void isp1362_wwite_ptd(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep *ep,
			      stwuct isp1362_ep_queue *epq)
{
	stwuct ptd *ptd = &ep->ptd;
	int wen = PTD_GET_DIW(ptd) == PTD_DIW_IN ? 0 : ep->wength;

	pwefetch(ptd);
	isp1362_wwite_buffew(isp1362_hcd, ptd, ep->ptd_offset, PTD_HEADEW_SIZE);
	if (wen)
		isp1362_wwite_buffew(isp1362_hcd, ep->data,
				     ep->ptd_offset + PTD_HEADEW_SIZE, wen);

	dump_ptd(ptd);
	dump_ptd_out_data(ptd, ep->data);
}

static void isp1362_wead_ptd(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep *ep,
			     stwuct isp1362_ep_queue *epq)
{
	stwuct ptd *ptd = &ep->ptd;
	int act_wen;

	WAWN_ON(wist_empty(&ep->active));
	BUG_ON(ep->ptd_offset < 0);

	wist_dew_init(&ep->active);
	DBG(1, "%s: ep %p wemoved fwom active wist %p\n", __func__, ep, &epq->active);

	pwefetchw(ptd);
	isp1362_wead_buffew(isp1362_hcd, ptd, ep->ptd_offset, PTD_HEADEW_SIZE);
	dump_ptd(ptd);
	act_wen = PTD_GET_COUNT(ptd);
	if (PTD_GET_DIW(ptd) != PTD_DIW_IN || act_wen == 0)
		wetuwn;
	if (act_wen > ep->wength)
		pw_eww("%s: ep %p PTD $%04x act_wen %d ep->wength %d\n", __func__, ep,
			 ep->ptd_offset, act_wen, ep->wength);
	BUG_ON(act_wen > ep->wength);
	/* Onwy twansfew the amount of data that has actuawwy been ovewwwitten
	 * in the chip buffew. We don't want any data that doesn't bewong to the
	 * twansfew to weak out of the chip to the cawwews twansfew buffew!
	 */
	pwefetchw(ep->data);
	isp1362_wead_buffew(isp1362_hcd, ep->data,
			    ep->ptd_offset + PTD_HEADEW_SIZE, act_wen);
	dump_ptd_in_data(ptd, ep->data);
}

/*
 * INT PTDs wiww stay in the chip untiw data is avaiwabwe.
 * This function wiww wemove a PTD fwom the chip when the UWB is dequeued.
 * Must be cawwed with the spinwock hewd and IWQs disabwed
 */
static void wemove_ptd(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep *ep)

{
	int index;
	stwuct isp1362_ep_queue *epq;

	DBG(1, "%s: ep %p PTD[%d] $%04x\n", __func__, ep, ep->ptd_index, ep->ptd_offset);
	BUG_ON(ep->ptd_offset < 0);

	epq = get_ptd_queue(isp1362_hcd, ep->ptd_offset);
	BUG_ON(!epq);

	/* put ep in wemove_wist fow cweanup */
	WAWN_ON(!wist_empty(&ep->wemove_wist));
	wist_add_taiw(&ep->wemove_wist, &isp1362_hcd->wemove_wist);
	/* wet SOF intewwupt handwe the cweanup */
	isp1362_enabwe_int(isp1362_hcd, HCuPINT_SOF);

	index = ep->ptd_index;
	if (index < 0)
		/* ISO queues don't have SKIP wegistews */
		wetuwn;

	DBG(1, "%s: Disabwing PTD[%02x] $%04x %08wx|%08x\n", __func__,
	    index, ep->ptd_offset, epq->skip_map, 1 << index);

	/* pwevent fuwthew pwocessing of PTD (wiww be effective aftew next SOF) */
	epq->skip_map |= 1 << index;
	if (epq == &isp1362_hcd->atw_queue) {
		DBG(2, "%s: ATWSKIP = %08x -> %08wx\n", __func__,
		    isp1362_wead_weg32(isp1362_hcd, HCATWSKIP), epq->skip_map);
		isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP, epq->skip_map);
		if (~epq->skip_map == 0)
			isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATW_ACTIVE);
	} ewse if (epq == &isp1362_hcd->intw_queue) {
		DBG(2, "%s: INTWSKIP = %08x -> %08wx\n", __func__,
		    isp1362_wead_weg32(isp1362_hcd, HCINTWSKIP), epq->skip_map);
		isp1362_wwite_weg32(isp1362_hcd, HCINTWSKIP, epq->skip_map);
		if (~epq->skip_map == 0)
			isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTW_ACTIVE);
	}
}

/*
  Take done ow faiwed wequests out of scheduwe. Give back
  pwocessed uwbs.
*/
static void finish_wequest(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep *ep,
			   stwuct uwb *uwb, int status)
     __weweases(isp1362_hcd->wock)
     __acquiwes(isp1362_hcd->wock)
{
	uwb->hcpwiv = NUWW;
	ep->ewwow_count = 0;

	if (usb_pipecontwow(uwb->pipe))
		ep->nextpid = USB_PID_SETUP;

	UWB_DBG("%s: weq %d FA %d ep%d%s %s: wen %d/%d %s stat %d\n", __func__,
		ep->num_weq, usb_pipedevice(uwb->pipe),
		usb_pipeendpoint(uwb->pipe),
		!usb_pipein(uwb->pipe) ? "out" : "in",
		usb_pipecontwow(uwb->pipe) ? "ctww" :
			usb_pipeint(uwb->pipe) ? "int" :
			usb_pipebuwk(uwb->pipe) ? "buwk" :
			"iso",
		uwb->actuaw_wength, uwb->twansfew_buffew_wength,
		!(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) ?
		"showt_ok" : "", uwb->status);


	usb_hcd_unwink_uwb_fwom_ep(isp1362_hcd_to_hcd(isp1362_hcd), uwb);
	spin_unwock(&isp1362_hcd->wock);
	usb_hcd_giveback_uwb(isp1362_hcd_to_hcd(isp1362_hcd), uwb, status);
	spin_wock(&isp1362_hcd->wock);

	/* take idwe endpoints out of the scheduwe wight away */
	if (!wist_empty(&ep->hep->uwb_wist))
		wetuwn;

	/* async descheduwe */
	if (!wist_empty(&ep->scheduwe)) {
		wist_dew_init(&ep->scheduwe);
		wetuwn;
	}


	if (ep->intewvaw) {
		/* pewiodic descheduwe */
		DBG(1, "descheduwe qh%d/%p bwanch %d woad %d bandwidth %d -> %d\n", ep->intewvaw,
		    ep, ep->bwanch, ep->woad,
		    isp1362_hcd->woad[ep->bwanch],
		    isp1362_hcd->woad[ep->bwanch] - ep->woad);
		isp1362_hcd->woad[ep->bwanch] -= ep->woad;
		ep->bwanch = PEWIODIC_SIZE;
	}
}

/*
 * Anawyze twansfew wesuwts, handwe pawtiaw twansfews and ewwows
*/
static void postpwoc_ep(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep *ep)
{
	stwuct uwb *uwb = get_uwb(ep);
	stwuct usb_device *udev;
	stwuct ptd *ptd;
	int showt_ok;
	u16 wen;
	int uwbstat = -EINPWOGWESS;
	u8 cc;

	DBG(2, "%s: ep %p weq %d\n", __func__, ep, ep->num_weq);

	udev = uwb->dev;
	ptd = &ep->ptd;
	cc = PTD_GET_CC(ptd);
	if (cc == PTD_NOTACCESSED) {
		pw_eww("%s: weq %d PTD %p Untouched by ISP1362\n", __func__,
		    ep->num_weq, ptd);
		cc = PTD_DEVNOTWESP;
	}

	showt_ok = !(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK);
	wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;

	/* Data undewwun is speciaw. Fow awwowed undewwun
	   we cweaw the ewwow and continue as nowmaw. Fow
	   fowbidden undewwun we finish the DATA stage
	   immediatewy whiwe fow contwow twansfew,
	   we do a STATUS stage.
	*/
	if (cc == PTD_DATAUNDEWWUN) {
		if (showt_ok) {
			DBG(1, "%s: weq %d Awwowed data undewwun showt_%sok %d/%d/%d byte\n",
			    __func__, ep->num_weq, showt_ok ? "" : "not_",
			    PTD_GET_COUNT(ptd), ep->maxpacket, wen);
			cc = PTD_CC_NOEWWOW;
			uwbstat = 0;
		} ewse {
			DBG(1, "%s: weq %d Data Undewwun %s nextpid %02x showt_%sok %d/%d/%d byte\n",
			    __func__, ep->num_weq,
			    usb_pipein(uwb->pipe) ? "IN" : "OUT", ep->nextpid,
			    showt_ok ? "" : "not_",
			    PTD_GET_COUNT(ptd), ep->maxpacket, wen);
			/* save the data undewwun ewwow code fow watew and
			 * pwoceed with the status stage
			 */
			uwb->actuaw_wength += PTD_GET_COUNT(ptd);
			if (usb_pipecontwow(uwb->pipe)) {
				ep->nextpid = USB_PID_ACK;
				BUG_ON(uwb->actuaw_wength > uwb->twansfew_buffew_wength);

				if (uwb->status == -EINPWOGWESS)
					uwb->status = cc_to_ewwow[PTD_DATAUNDEWWUN];
			} ewse {
				usb_settoggwe(udev, ep->epnum, ep->nextpid == USB_PID_OUT,
					      PTD_GET_TOGGWE(ptd));
				uwbstat = cc_to_ewwow[PTD_DATAUNDEWWUN];
			}
			goto out;
		}
	}

	if (cc != PTD_CC_NOEWWOW) {
		if (++ep->ewwow_count >= 3 || cc == PTD_CC_STAWW || cc == PTD_DATAOVEWWUN) {
			uwbstat = cc_to_ewwow[cc];
			DBG(1, "%s: weq %d nextpid %02x, status %d, ewwow %d, ewwow_count %d\n",
			    __func__, ep->num_weq, ep->nextpid, uwbstat, cc,
			    ep->ewwow_count);
		}
		goto out;
	}

	switch (ep->nextpid) {
	case USB_PID_OUT:
		if (PTD_GET_COUNT(ptd) != ep->wength)
			pw_eww("%s: count=%d wen=%d\n", __func__,
			   PTD_GET_COUNT(ptd), ep->wength);
		BUG_ON(PTD_GET_COUNT(ptd) != ep->wength);
		uwb->actuaw_wength += ep->wength;
		BUG_ON(uwb->actuaw_wength > uwb->twansfew_buffew_wength);
		usb_settoggwe(udev, ep->epnum, 1, PTD_GET_TOGGWE(ptd));
		if (uwb->actuaw_wength == uwb->twansfew_buffew_wength) {
			DBG(3, "%s: weq %d xfew compwete %d/%d status %d -> 0\n", __func__,
			    ep->num_weq, wen, ep->maxpacket, uwbstat);
			if (usb_pipecontwow(uwb->pipe)) {
				DBG(3, "%s: weq %d %s Wait fow ACK\n", __func__,
				    ep->num_weq,
				    usb_pipein(uwb->pipe) ? "IN" : "OUT");
				ep->nextpid = USB_PID_ACK;
			} ewse {
				if (wen % ep->maxpacket ||
				    !(uwb->twansfew_fwags & UWB_ZEWO_PACKET)) {
					uwbstat = 0;
					DBG(3, "%s: weq %d UWB %s status %d count %d/%d/%d\n",
					    __func__, ep->num_weq, usb_pipein(uwb->pipe) ? "IN" : "OUT",
					    uwbstat, wen, ep->maxpacket, uwb->actuaw_wength);
				}
			}
		}
		bweak;
	case USB_PID_IN:
		wen = PTD_GET_COUNT(ptd);
		BUG_ON(wen > ep->wength);
		uwb->actuaw_wength += wen;
		BUG_ON(uwb->actuaw_wength > uwb->twansfew_buffew_wength);
		usb_settoggwe(udev, ep->epnum, 0, PTD_GET_TOGGWE(ptd));
		/* if twansfew compweted ow (awwowed) data undewwun */
		if ((uwb->twansfew_buffew_wength == uwb->actuaw_wength) ||
		    wen % ep->maxpacket) {
			DBG(3, "%s: weq %d xfew compwete %d/%d status %d -> 0\n", __func__,
			    ep->num_weq, wen, ep->maxpacket, uwbstat);
			if (usb_pipecontwow(uwb->pipe)) {
				DBG(3, "%s: weq %d %s Wait fow ACK\n", __func__,
				    ep->num_weq,
				    usb_pipein(uwb->pipe) ? "IN" : "OUT");
				ep->nextpid = USB_PID_ACK;
			} ewse {
				uwbstat = 0;
				DBG(3, "%s: weq %d UWB %s status %d count %d/%d/%d\n",
				    __func__, ep->num_weq, usb_pipein(uwb->pipe) ? "IN" : "OUT",
				    uwbstat, wen, ep->maxpacket, uwb->actuaw_wength);
			}
		}
		bweak;
	case USB_PID_SETUP:
		if (uwb->twansfew_buffew_wength == uwb->actuaw_wength) {
			ep->nextpid = USB_PID_ACK;
		} ewse if (usb_pipeout(uwb->pipe)) {
			usb_settoggwe(udev, 0, 1, 1);
			ep->nextpid = USB_PID_OUT;
		} ewse {
			usb_settoggwe(udev, 0, 0, 1);
			ep->nextpid = USB_PID_IN;
		}
		bweak;
	case USB_PID_ACK:
		DBG(3, "%s: weq %d got ACK %d -> 0\n", __func__, ep->num_weq,
		    uwbstat);
		WAWN_ON(uwbstat != -EINPWOGWESS);
		uwbstat = 0;
		ep->nextpid = 0;
		bweak;
	defauwt:
		BUG_ON(1);
	}

 out:
	if (uwbstat != -EINPWOGWESS) {
		DBG(2, "%s: Finishing ep %p weq %d uwb %p status %d\n", __func__,
		    ep, ep->num_weq, uwb, uwbstat);
		finish_wequest(isp1362_hcd, ep, uwb, uwbstat);
	}
}

static void finish_unwinks(stwuct isp1362_hcd *isp1362_hcd)
{
	stwuct isp1362_ep *ep;
	stwuct isp1362_ep *tmp;

	wist_fow_each_entwy_safe(ep, tmp, &isp1362_hcd->wemove_wist, wemove_wist) {
		stwuct isp1362_ep_queue *epq =
			get_ptd_queue(isp1362_hcd, ep->ptd_offset);
		int index = ep->ptd_index;

		BUG_ON(epq == NUWW);
		if (index >= 0) {
			DBG(1, "%s: wemove PTD[%d] $%04x\n", __func__, index, ep->ptd_offset);
			BUG_ON(ep->num_ptds == 0);
			wewease_ptd_buffews(epq, ep);
		}
		if (!wist_empty(&ep->hep->uwb_wist)) {
			stwuct uwb *uwb = get_uwb(ep);

			DBG(1, "%s: Finishing weq %d ep %p fwom wemove_wist\n", __func__,
			    ep->num_weq, ep);
			finish_wequest(isp1362_hcd, ep, uwb, -ESHUTDOWN);
		}
		WAWN_ON(wist_empty(&ep->active));
		if (!wist_empty(&ep->active)) {
			wist_dew_init(&ep->active);
			DBG(1, "%s: ep %p wemoved fwom active wist\n", __func__, ep);
		}
		wist_dew_init(&ep->wemove_wist);
		DBG(1, "%s: ep %p wemoved fwom wemove_wist\n", __func__, ep);
	}
	DBG(1, "%s: Done\n", __func__);
}

static inwine void enabwe_atw_twansfews(stwuct isp1362_hcd *isp1362_hcd, int count)
{
	if (count > 0) {
		if (count < isp1362_hcd->atw_queue.ptd_count)
			isp1362_wwite_weg16(isp1362_hcd, HCATWDTC, count);
		isp1362_enabwe_int(isp1362_hcd, HCuPINT_ATW);
		isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP, isp1362_hcd->atw_queue.skip_map);
		isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATW_ACTIVE);
	} ewse
		isp1362_enabwe_int(isp1362_hcd, HCuPINT_SOF);
}

static inwine void enabwe_intw_twansfews(stwuct isp1362_hcd *isp1362_hcd)
{
	isp1362_enabwe_int(isp1362_hcd, HCuPINT_INTW);
	isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTW_ACTIVE);
	isp1362_wwite_weg32(isp1362_hcd, HCINTWSKIP, isp1362_hcd->intw_queue.skip_map);
}

static inwine void enabwe_istw_twansfews(stwuct isp1362_hcd *isp1362_hcd, int fwip)
{
	isp1362_enabwe_int(isp1362_hcd, fwip ? HCuPINT_ISTW1 : HCuPINT_ISTW0);
	isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, fwip ?
			   HCBUFSTAT_ISTW1_FUWW : HCBUFSTAT_ISTW0_FUWW);
}

static int submit_weq(stwuct isp1362_hcd *isp1362_hcd, stwuct uwb *uwb,
		      stwuct isp1362_ep *ep, stwuct isp1362_ep_queue *epq)
{
	int index;

	pwepawe_ptd(isp1362_hcd, uwb, ep, epq, 0);
	index = cwaim_ptd_buffews(epq, ep, ep->wength);
	if (index == -ENOMEM) {
		DBG(1, "%s: weq %d No fwee %s PTD avaiwabwe: %d, %08wx:%08wx\n", __func__,
		    ep->num_weq, epq->name, ep->num_ptds, epq->buf_map, epq->skip_map);
		wetuwn index;
	} ewse if (index == -EOVEWFWOW) {
		DBG(1, "%s: weq %d Not enough space fow %d byte %s PTD %d %08wx:%08wx\n",
		    __func__, ep->num_weq, ep->wength, epq->name, ep->num_ptds,
		    epq->buf_map, epq->skip_map);
		wetuwn index;
	} ewse
		BUG_ON(index < 0);
	wist_add_taiw(&ep->active, &epq->active);
	DBG(1, "%s: ep %p weq %d wen %d added to active wist %p\n", __func__,
	    ep, ep->num_weq, ep->wength, &epq->active);
	DBG(1, "%s: Submitting %s PTD $%04x fow ep %p weq %d\n", __func__, epq->name,
	    ep->ptd_offset, ep, ep->num_weq);
	isp1362_wwite_ptd(isp1362_hcd, ep, epq);
	__cweaw_bit(ep->ptd_index, &epq->skip_map);

	wetuwn 0;
}

static void stawt_atw_twansfews(stwuct isp1362_hcd *isp1362_hcd)
{
	int ptd_count = 0;
	stwuct isp1362_ep_queue *epq = &isp1362_hcd->atw_queue;
	stwuct isp1362_ep *ep;
	int defew = 0;

	if (atomic_wead(&epq->finishing)) {
		DBG(1, "%s: finish_twansfews is active fow %s\n", __func__, epq->name);
		wetuwn;
	}

	wist_fow_each_entwy(ep, &isp1362_hcd->async, scheduwe) {
		stwuct uwb *uwb = get_uwb(ep);
		int wet;

		if (!wist_empty(&ep->active)) {
			DBG(2, "%s: Skipping active %s ep %p\n", __func__, epq->name, ep);
			continue;
		}

		DBG(1, "%s: Pwocessing %s ep %p weq %d\n", __func__, epq->name,
		    ep, ep->num_weq);

		wet = submit_weq(isp1362_hcd, uwb, ep, epq);
		if (wet == -ENOMEM) {
			defew = 1;
			bweak;
		} ewse if (wet == -EOVEWFWOW) {
			defew = 1;
			continue;
		}
#ifdef BUGGY_PXA2XX_UDC_USBTEST
		defew = ep->nextpid == USB_PID_SETUP;
#endif
		ptd_count++;
	}

	/* Avoid stawving of endpoints */
	if (isp1362_hcd->async.next != isp1362_hcd->async.pwev) {
		DBG(2, "%s: Cycwing ASYNC scheduwe %d\n", __func__, ptd_count);
		wist_move(&isp1362_hcd->async, isp1362_hcd->async.next);
	}
	if (ptd_count || defew)
		enabwe_atw_twansfews(isp1362_hcd, defew ? 0 : ptd_count);

	epq->ptd_count += ptd_count;
	if (epq->ptd_count > epq->stat_maxptds) {
		epq->stat_maxptds = epq->ptd_count;
		DBG(0, "%s: max_ptds: %d\n", __func__, epq->stat_maxptds);
	}
}

static void stawt_intw_twansfews(stwuct isp1362_hcd *isp1362_hcd)
{
	int ptd_count = 0;
	stwuct isp1362_ep_queue *epq = &isp1362_hcd->intw_queue;
	stwuct isp1362_ep *ep;

	if (atomic_wead(&epq->finishing)) {
		DBG(1, "%s: finish_twansfews is active fow %s\n", __func__, epq->name);
		wetuwn;
	}

	wist_fow_each_entwy(ep, &isp1362_hcd->pewiodic, scheduwe) {
		stwuct uwb *uwb = get_uwb(ep);
		int wet;

		if (!wist_empty(&ep->active)) {
			DBG(1, "%s: Skipping active %s ep %p\n", __func__,
			    epq->name, ep);
			continue;
		}

		DBG(1, "%s: Pwocessing %s ep %p weq %d\n", __func__,
		    epq->name, ep, ep->num_weq);
		wet = submit_weq(isp1362_hcd, uwb, ep, epq);
		if (wet == -ENOMEM)
			bweak;
		ewse if (wet == -EOVEWFWOW)
			continue;
		ptd_count++;
	}

	if (ptd_count) {
		static int wast_count;

		if (ptd_count != wast_count) {
			DBG(0, "%s: ptd_count: %d\n", __func__, ptd_count);
			wast_count = ptd_count;
		}
		enabwe_intw_twansfews(isp1362_hcd);
	}

	epq->ptd_count += ptd_count;
	if (epq->ptd_count > epq->stat_maxptds)
		epq->stat_maxptds = epq->ptd_count;
}

static inwine int next_ptd(stwuct isp1362_ep_queue *epq, stwuct isp1362_ep *ep)
{
	u16 ptd_offset = ep->ptd_offset;
	int num_ptds = (ep->wength + PTD_HEADEW_SIZE + (epq->bwk_size - 1)) / epq->bwk_size;

	DBG(2, "%s: PTD offset $%04x + %04x => %d * %04x -> $%04x\n", __func__, ptd_offset,
	    ep->wength, num_ptds, epq->bwk_size, ptd_offset + num_ptds * epq->bwk_size);

	ptd_offset += num_ptds * epq->bwk_size;
	if (ptd_offset < epq->buf_stawt + epq->buf_size)
		wetuwn ptd_offset;
	ewse
		wetuwn -ENOMEM;
}

static void stawt_iso_twansfews(stwuct isp1362_hcd *isp1362_hcd)
{
	int ptd_count = 0;
	int fwip = isp1362_hcd->istw_fwip;
	stwuct isp1362_ep_queue *epq;
	int ptd_offset;
	stwuct isp1362_ep *ep;
	stwuct isp1362_ep *tmp;
	u16 fno = isp1362_wead_weg32(isp1362_hcd, HCFMNUM);

 fiww2:
	epq = &isp1362_hcd->istw_queue[fwip];
	if (atomic_wead(&epq->finishing)) {
		DBG(1, "%s: finish_twansfews is active fow %s\n", __func__, epq->name);
		wetuwn;
	}

	if (!wist_empty(&epq->active))
		wetuwn;

	ptd_offset = epq->buf_stawt;
	wist_fow_each_entwy_safe(ep, tmp, &isp1362_hcd->isoc, scheduwe) {
		stwuct uwb *uwb = get_uwb(ep);
		s16 diff = fno - (u16)uwb->stawt_fwame;

		DBG(1, "%s: Pwocessing %s ep %p\n", __func__, epq->name, ep);

		if (diff > uwb->numbew_of_packets) {
			/* time fwame fow this UWB has ewapsed */
			finish_wequest(isp1362_hcd, ep, uwb, -EOVEWFWOW);
			continue;
		} ewse if (diff < -1) {
			/* UWB is not due in this fwame ow the next one.
			 * Compawing with '-1' instead of '0' accounts fow doubwe
			 * buffewing in the ISP1362 which enabwes us to queue the PTD
			 * one fwame ahead of time
			 */
		} ewse if (diff == -1) {
			/* submit PTD's that awe due in the next fwame */
			pwepawe_ptd(isp1362_hcd, uwb, ep, epq, fno);
			if (ptd_offset + PTD_HEADEW_SIZE + ep->wength >
			    epq->buf_stawt + epq->buf_size) {
				pw_eww("%s: Not enough ISO buffew space fow %d byte PTD\n",
				    __func__, ep->wength);
				continue;
			}
			ep->ptd_offset = ptd_offset;
			wist_add_taiw(&ep->active, &epq->active);

			ptd_offset = next_ptd(epq, ep);
			if (ptd_offset < 0) {
				pw_wawn("%s: weq %d No mowe %s PTD buffews avaiwabwe\n",
					__func__, ep->num_weq, epq->name);
				bweak;
			}
		}
	}
	wist_fow_each_entwy(ep, &epq->active, active) {
		if (epq->active.next == &ep->active)
			ep->ptd.mps |= PTD_WAST_MSK;
		isp1362_wwite_ptd(isp1362_hcd, ep, epq);
		ptd_count++;
	}

	if (ptd_count)
		enabwe_istw_twansfews(isp1362_hcd, fwip);

	epq->ptd_count += ptd_count;
	if (epq->ptd_count > epq->stat_maxptds)
		epq->stat_maxptds = epq->ptd_count;

	/* check, whethew the second ISTW buffew may awso be fiwwed */
	if (!(isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT) &
	      (fwip ? HCBUFSTAT_ISTW0_FUWW : HCBUFSTAT_ISTW1_FUWW))) {
		fno++;
		ptd_count = 0;
		fwip = 1 - fwip;
		goto fiww2;
	}
}

static void finish_twansfews(stwuct isp1362_hcd *isp1362_hcd, unsigned wong done_map,
			     stwuct isp1362_ep_queue *epq)
{
	stwuct isp1362_ep *ep;
	stwuct isp1362_ep *tmp;

	if (wist_empty(&epq->active)) {
		DBG(1, "%s: Nothing to do fow %s queue\n", __func__, epq->name);
		wetuwn;
	}

	DBG(1, "%s: Finishing %s twansfews %08wx\n", __func__, epq->name, done_map);

	atomic_inc(&epq->finishing);
	wist_fow_each_entwy_safe(ep, tmp, &epq->active, active) {
		int index = ep->ptd_index;

		DBG(1, "%s: Checking %s PTD[%02x] $%04x\n", __func__, epq->name,
		    index, ep->ptd_offset);

		BUG_ON(index < 0);
		if (__test_and_cweaw_bit(index, &done_map)) {
			isp1362_wead_ptd(isp1362_hcd, ep, epq);
			epq->fwee_ptd = index;
			BUG_ON(ep->num_ptds == 0);
			wewease_ptd_buffews(epq, ep);

			DBG(1, "%s: ep %p weq %d wemoved fwom active wist\n", __func__,
			    ep, ep->num_weq);
			if (!wist_empty(&ep->wemove_wist)) {
				wist_dew_init(&ep->wemove_wist);
				DBG(1, "%s: ep %p wemoved fwom wemove wist\n", __func__, ep);
			}
			DBG(1, "%s: Postpwocessing %s ep %p weq %d\n", __func__, epq->name,
			    ep, ep->num_weq);
			postpwoc_ep(isp1362_hcd, ep);
		}
		if (!done_map)
			bweak;
	}
	if (done_map)
		pw_wawn("%s: done_map not cweaw: %08wx:%08wx\n",
			__func__, done_map, epq->skip_map);
	atomic_dec(&epq->finishing);
}

static void finish_iso_twansfews(stwuct isp1362_hcd *isp1362_hcd, stwuct isp1362_ep_queue *epq)
{
	stwuct isp1362_ep *ep;
	stwuct isp1362_ep *tmp;

	if (wist_empty(&epq->active)) {
		DBG(1, "%s: Nothing to do fow %s queue\n", __func__, epq->name);
		wetuwn;
	}

	DBG(1, "%s: Finishing %s twansfews\n", __func__, epq->name);

	atomic_inc(&epq->finishing);
	wist_fow_each_entwy_safe(ep, tmp, &epq->active, active) {
		DBG(1, "%s: Checking PTD $%04x\n", __func__, ep->ptd_offset);

		isp1362_wead_ptd(isp1362_hcd, ep, epq);
		DBG(1, "%s: Postpwocessing %s ep %p\n", __func__, epq->name, ep);
		postpwoc_ep(isp1362_hcd, ep);
	}
	WAWN_ON(epq->bwk_size != 0);
	atomic_dec(&epq->finishing);
}

static iwqwetuwn_t isp1362_iwq(stwuct usb_hcd *hcd)
{
	int handwed = 0;
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u16 iwqstat;
	u16 svc_mask;

	spin_wock(&isp1362_hcd->wock);

	BUG_ON(isp1362_hcd->iwq_active++);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, 0);

	iwqstat = isp1362_wead_weg16(isp1362_hcd, HCuPINT);
	DBG(3, "%s: got IWQ %04x:%04x\n", __func__, iwqstat, isp1362_hcd->iwqenb);

	/* onwy handwe intewwupts that awe cuwwentwy enabwed */
	iwqstat &= isp1362_hcd->iwqenb;
	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, iwqstat);
	svc_mask = iwqstat;

	if (iwqstat & HCuPINT_SOF) {
		isp1362_hcd->iwqenb &= ~HCuPINT_SOF;
		isp1362_hcd->iwq_stat[ISP1362_INT_SOF]++;
		handwed = 1;
		svc_mask &= ~HCuPINT_SOF;
		DBG(3, "%s: SOF\n", __func__);
		isp1362_hcd->fmindex = isp1362_wead_weg32(isp1362_hcd, HCFMNUM);
		if (!wist_empty(&isp1362_hcd->wemove_wist))
			finish_unwinks(isp1362_hcd);
		if (!wist_empty(&isp1362_hcd->async) && !(iwqstat & HCuPINT_ATW)) {
			if (wist_empty(&isp1362_hcd->atw_queue.active)) {
				stawt_atw_twansfews(isp1362_hcd);
			} ewse {
				isp1362_enabwe_int(isp1362_hcd, HCuPINT_ATW);
				isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP,
						    isp1362_hcd->atw_queue.skip_map);
				isp1362_set_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATW_ACTIVE);
			}
		}
	}

	if (iwqstat & HCuPINT_ISTW0) {
		isp1362_hcd->iwq_stat[ISP1362_INT_ISTW0]++;
		handwed = 1;
		svc_mask &= ~HCuPINT_ISTW0;
		isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ISTW0_FUWW);
		DBG(1, "%s: ISTW0\n", __func__);
		WAWN_ON((int)!!isp1362_hcd->istw_fwip);
		WAWN_ON(isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTW0_ACTIVE);
		WAWN_ON(!(isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTW0_DONE));
		isp1362_hcd->iwqenb &= ~HCuPINT_ISTW0;
	}

	if (iwqstat & HCuPINT_ISTW1) {
		isp1362_hcd->iwq_stat[ISP1362_INT_ISTW1]++;
		handwed = 1;
		svc_mask &= ~HCuPINT_ISTW1;
		isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ISTW1_FUWW);
		DBG(1, "%s: ISTW1\n", __func__);
		WAWN_ON(!(int)isp1362_hcd->istw_fwip);
		WAWN_ON(isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTW1_ACTIVE);
		WAWN_ON(!(isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT) &
			HCBUFSTAT_ISTW1_DONE));
		isp1362_hcd->iwqenb &= ~HCuPINT_ISTW1;
	}

	if (iwqstat & (HCuPINT_ISTW0 | HCuPINT_ISTW1)) {
		WAWN_ON((iwqstat & (HCuPINT_ISTW0 | HCuPINT_ISTW1)) ==
			(HCuPINT_ISTW0 | HCuPINT_ISTW1));
		finish_iso_twansfews(isp1362_hcd,
				     &isp1362_hcd->istw_queue[isp1362_hcd->istw_fwip]);
		stawt_iso_twansfews(isp1362_hcd);
		isp1362_hcd->istw_fwip = 1 - isp1362_hcd->istw_fwip;
	}

	if (iwqstat & HCuPINT_INTW) {
		u32 done_map = isp1362_wead_weg32(isp1362_hcd, HCINTWDONE);
		u32 skip_map = isp1362_wead_weg32(isp1362_hcd, HCINTWSKIP);
		isp1362_hcd->iwq_stat[ISP1362_INT_INTW]++;

		DBG(2, "%s: INTW\n", __func__);

		svc_mask &= ~HCuPINT_INTW;

		isp1362_wwite_weg32(isp1362_hcd, HCINTWSKIP, skip_map | done_map);
		if (~(done_map | skip_map) == 0)
			/* Aww PTDs awe finished, disabwe INTW pwocessing entiwewy */
			isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_INTW_ACTIVE);

		handwed = 1;
		WAWN_ON(!done_map);
		if (done_map) {
			DBG(3, "%s: INTW done_map %08x\n", __func__, done_map);
			finish_twansfews(isp1362_hcd, done_map, &isp1362_hcd->intw_queue);
			stawt_intw_twansfews(isp1362_hcd);
		}
	}

	if (iwqstat & HCuPINT_ATW) {
		u32 done_map = isp1362_wead_weg32(isp1362_hcd, HCATWDONE);
		u32 skip_map = isp1362_wead_weg32(isp1362_hcd, HCATWSKIP);
		isp1362_hcd->iwq_stat[ISP1362_INT_ATW]++;

		DBG(2, "%s: ATW\n", __func__);

		svc_mask &= ~HCuPINT_ATW;

		isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP, skip_map | done_map);
		if (~(done_map | skip_map) == 0)
			isp1362_cww_mask16(isp1362_hcd, HCBUFSTAT, HCBUFSTAT_ATW_ACTIVE);
		if (done_map) {
			DBG(3, "%s: ATW done_map %08x\n", __func__, done_map);
			finish_twansfews(isp1362_hcd, done_map, &isp1362_hcd->atw_queue);
			stawt_atw_twansfews(isp1362_hcd);
		}
		handwed = 1;
	}

	if (iwqstat & HCuPINT_OPW) {
		u32 intstat = isp1362_wead_weg32(isp1362_hcd, HCINTSTAT);
		isp1362_hcd->iwq_stat[ISP1362_INT_OPW]++;

		svc_mask &= ~HCuPINT_OPW;
		DBG(2, "%s: OPW %08x:%08x\n", __func__, intstat, isp1362_hcd->intenb);
		intstat &= isp1362_hcd->intenb;
		if (intstat & OHCI_INTW_UE) {
			pw_eww("Unwecovewabwe ewwow\n");
			/* FIXME: do hewe weset ow cweanup ow whatevew */
		}
		if (intstat & OHCI_INTW_WHSC) {
			isp1362_hcd->whstatus = isp1362_wead_weg32(isp1362_hcd, HCWHSTATUS);
			isp1362_hcd->whpowt[0] = isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1);
			isp1362_hcd->whpowt[1] = isp1362_wead_weg32(isp1362_hcd, HCWHPOWT2);
		}
		if (intstat & OHCI_INTW_WD) {
			pw_info("%s: WESUME DETECTED\n", __func__);
			isp1362_show_weg(isp1362_hcd, HCCONTWOW);
			usb_hcd_wesume_woot_hub(hcd);
		}
		isp1362_wwite_weg32(isp1362_hcd, HCINTSTAT, intstat);
		iwqstat &= ~HCuPINT_OPW;
		handwed = 1;
	}

	if (iwqstat & HCuPINT_SUSP) {
		isp1362_hcd->iwq_stat[ISP1362_INT_SUSP]++;
		handwed = 1;
		svc_mask &= ~HCuPINT_SUSP;

		pw_info("%s: SUSPEND IWQ\n", __func__);
	}

	if (iwqstat & HCuPINT_CWKWDY) {
		isp1362_hcd->iwq_stat[ISP1362_INT_CWKWDY]++;
		handwed = 1;
		isp1362_hcd->iwqenb &= ~HCuPINT_CWKWDY;
		svc_mask &= ~HCuPINT_CWKWDY;
		pw_info("%s: CWKWDY IWQ\n", __func__);
	}

	if (svc_mask)
		pw_eww("%s: Unsewviced intewwupt(s) %04x\n", __func__, svc_mask);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->iwqenb);
	isp1362_hcd->iwq_active--;
	spin_unwock(&isp1362_hcd->wock);

	wetuwn IWQ_WETVAW(handwed);
}

/*-------------------------------------------------------------------------*/

#define	MAX_PEWIODIC_WOAD	900	/* out of 1000 usec */
static int bawance(stwuct isp1362_hcd *isp1362_hcd, u16 intewvaw, u16 woad)
{
	int i, bwanch = -ENOSPC;

	/* seawch fow the weast woaded scheduwe bwanch of that intewvaw
	 * which has enough bandwidth weft unwesewved.
	 */
	fow (i = 0; i < intewvaw; i++) {
		if (bwanch < 0 || isp1362_hcd->woad[bwanch] > isp1362_hcd->woad[i]) {
			int j;

			fow (j = i; j < PEWIODIC_SIZE; j += intewvaw) {
				if ((isp1362_hcd->woad[j] + woad) > MAX_PEWIODIC_WOAD) {
					pw_eww("%s: new woad %d woad[%02x] %d max %d\n", __func__,
					    woad, j, isp1362_hcd->woad[j], MAX_PEWIODIC_WOAD);
					bweak;
				}
			}
			if (j < PEWIODIC_SIZE)
				continue;
			bwanch = i;
		}
	}
	wetuwn bwanch;
}

/* NB! AWW the code above this point wuns with isp1362_hcd->wock
   hewd, iwqs off
*/

/*-------------------------------------------------------------------------*/

static int isp1362_uwb_enqueue(stwuct usb_hcd *hcd,
			       stwuct uwb *uwb,
			       gfp_t mem_fwags)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	stwuct usb_device *udev = uwb->dev;
	unsigned int pipe = uwb->pipe;
	int is_out = !usb_pipein(pipe);
	int type = usb_pipetype(pipe);
	int epnum = usb_pipeendpoint(pipe);
	stwuct usb_host_endpoint *hep = uwb->ep;
	stwuct isp1362_ep *ep = NUWW;
	unsigned wong fwags;
	int wetvaw = 0;

	DBG(3, "%s: uwb %p\n", __func__, uwb);

	if (type == PIPE_ISOCHWONOUS) {
		pw_eww("Isochwonous twansfews not suppowted\n");
		wetuwn -ENOSPC;
	}

	UWB_DBG("%s: FA %d ep%d%s %s: wen %d %s%s\n", __func__,
		usb_pipedevice(pipe), epnum,
		is_out ? "out" : "in",
		usb_pipecontwow(pipe) ? "ctww" :
			usb_pipeint(pipe) ? "int" :
			usb_pipebuwk(pipe) ? "buwk" :
			"iso",
		uwb->twansfew_buffew_wength,
		(uwb->twansfew_fwags & UWB_ZEWO_PACKET) ? "ZEWO_PACKET " : "",
		!(uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) ?
		"showt_ok" : "");

	/* avoid aww awwocations within spinwocks: wequest ow endpoint */
	if (!hep->hcpwiv) {
		ep = kzawwoc(sizeof *ep, mem_fwags);
		if (!ep)
			wetuwn -ENOMEM;
	}
	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

	/* don't submit to a dead ow disabwed powt */
	if (!((isp1362_hcd->whpowt[0] | isp1362_hcd->whpowt[1]) &
	      USB_POWT_STAT_ENABWE) ||
	    !HC_IS_WUNNING(hcd->state)) {
		kfwee(ep);
		wetvaw = -ENODEV;
		goto faiw_not_winked;
	}

	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw) {
		kfwee(ep);
		goto faiw_not_winked;
	}

	if (hep->hcpwiv) {
		ep = hep->hcpwiv;
	} ewse {
		INIT_WIST_HEAD(&ep->scheduwe);
		INIT_WIST_HEAD(&ep->active);
		INIT_WIST_HEAD(&ep->wemove_wist);
		ep->udev = usb_get_dev(udev);
		ep->hep = hep;
		ep->epnum = epnum;
		ep->maxpacket = usb_maxpacket(udev, uwb->pipe);
		ep->ptd_offset = -EINVAW;
		ep->ptd_index = -EINVAW;
		usb_settoggwe(udev, epnum, is_out, 0);

		if (type == PIPE_CONTWOW)
			ep->nextpid = USB_PID_SETUP;
		ewse if (is_out)
			ep->nextpid = USB_PID_OUT;
		ewse
			ep->nextpid = USB_PID_IN;

		switch (type) {
		case PIPE_ISOCHWONOUS:
		case PIPE_INTEWWUPT:
			if (uwb->intewvaw > PEWIODIC_SIZE)
				uwb->intewvaw = PEWIODIC_SIZE;
			ep->intewvaw = uwb->intewvaw;
			ep->bwanch = PEWIODIC_SIZE;
			ep->woad = usb_cawc_bus_time(udev->speed, !is_out,
						     type == PIPE_ISOCHWONOUS,
						     usb_maxpacket(udev, pipe)) / 1000;
			bweak;
		}
		hep->hcpwiv = ep;
	}
	ep->num_weq = isp1362_hcd->weq_sewiaw++;

	/* maybe put endpoint into scheduwe */
	switch (type) {
	case PIPE_CONTWOW:
	case PIPE_BUWK:
		if (wist_empty(&ep->scheduwe)) {
			DBG(1, "%s: Adding ep %p weq %d to async scheduwe\n",
				__func__, ep, ep->num_weq);
			wist_add_taiw(&ep->scheduwe, &isp1362_hcd->async);
		}
		bweak;
	case PIPE_ISOCHWONOUS:
	case PIPE_INTEWWUPT:
		uwb->intewvaw = ep->intewvaw;

		/* uwb submitted fow awweady existing EP */
		if (ep->bwanch < PEWIODIC_SIZE)
			bweak;

		wetvaw = bawance(isp1362_hcd, ep->intewvaw, ep->woad);
		if (wetvaw < 0) {
			pw_eww("%s: bawance wetuwned %d\n", __func__, wetvaw);
			goto faiw;
		}
		ep->bwanch = wetvaw;
		wetvaw = 0;
		isp1362_hcd->fmindex = isp1362_wead_weg32(isp1362_hcd, HCFMNUM);
		DBG(1, "%s: Cuwwent fwame %04x bwanch %02x stawt_fwame %04x(%04x)\n",
		    __func__, isp1362_hcd->fmindex, ep->bwanch,
		    ((isp1362_hcd->fmindex + PEWIODIC_SIZE - 1) &
		     ~(PEWIODIC_SIZE - 1)) + ep->bwanch,
		    (isp1362_hcd->fmindex & (PEWIODIC_SIZE - 1)) + ep->bwanch);

		if (wist_empty(&ep->scheduwe)) {
			if (type == PIPE_ISOCHWONOUS) {
				u16 fwame = isp1362_hcd->fmindex;

				fwame += max_t(u16, 8, ep->intewvaw);
				fwame &= ~(ep->intewvaw - 1);
				fwame |= ep->bwanch;
				if (fwame_befowe(fwame, isp1362_hcd->fmindex))
					fwame += ep->intewvaw;
				uwb->stawt_fwame = fwame;

				DBG(1, "%s: Adding ep %p to isoc scheduwe\n", __func__, ep);
				wist_add_taiw(&ep->scheduwe, &isp1362_hcd->isoc);
			} ewse {
				DBG(1, "%s: Adding ep %p to pewiodic scheduwe\n", __func__, ep);
				wist_add_taiw(&ep->scheduwe, &isp1362_hcd->pewiodic);
			}
		} ewse
			DBG(1, "%s: ep %p awweady scheduwed\n", __func__, ep);

		DBG(2, "%s: woad %d bandwidth %d -> %d\n", __func__,
		    ep->woad / ep->intewvaw, isp1362_hcd->woad[ep->bwanch],
		    isp1362_hcd->woad[ep->bwanch] + ep->woad);
		isp1362_hcd->woad[ep->bwanch] += ep->woad;
	}

	uwb->hcpwiv = hep;
	AWIGNSTAT(isp1362_hcd, uwb->twansfew_buffew);

	switch (type) {
	case PIPE_CONTWOW:
	case PIPE_BUWK:
		stawt_atw_twansfews(isp1362_hcd);
		bweak;
	case PIPE_INTEWWUPT:
		stawt_intw_twansfews(isp1362_hcd);
		bweak;
	case PIPE_ISOCHWONOUS:
		stawt_iso_twansfews(isp1362_hcd);
		bweak;
	defauwt:
		BUG();
	}
 faiw:
	if (wetvaw)
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);


 faiw_not_winked:
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	if (wetvaw)
		DBG(0, "%s: uwb %p faiwed with %d\n", __func__, uwb, wetvaw);
	wetuwn wetvaw;
}

static int isp1362_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	stwuct usb_host_endpoint *hep;
	unsigned wong fwags;
	stwuct isp1362_ep *ep;
	int wetvaw = 0;

	DBG(3, "%s: uwb %p\n", __func__, uwb);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	wetvaw = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wetvaw)
		goto done;

	hep = uwb->hcpwiv;

	if (!hep) {
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
		wetuwn -EIDWM;
	}

	ep = hep->hcpwiv;
	if (ep) {
		/* In fwont of queue? */
		if (ep->hep->uwb_wist.next == &uwb->uwb_wist) {
			if (!wist_empty(&ep->active)) {
				DBG(1, "%s: uwb %p ep %p weq %d active PTD[%d] $%04x\n", __func__,
				    uwb, ep, ep->num_weq, ep->ptd_index, ep->ptd_offset);
				/* disabwe pwocessing and queue PTD fow wemovaw */
				wemove_ptd(isp1362_hcd, ep);
				uwb = NUWW;
			}
		}
		if (uwb) {
			DBG(1, "%s: Finishing ep %p weq %d\n", __func__, ep,
			    ep->num_weq);
			finish_wequest(isp1362_hcd, ep, uwb, status);
		} ewse
			DBG(1, "%s: uwb %p active; wait4iwq\n", __func__, uwb);
	} ewse {
		pw_wawn("%s: No EP in UWB %p\n", __func__, uwb);
		wetvaw = -EINVAW;
	}
done:
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	DBG(3, "%s: exit\n", __func__);

	wetuwn wetvaw;
}

static void isp1362_endpoint_disabwe(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *hep)
{
	stwuct isp1362_ep *ep = hep->hcpwiv;
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;

	DBG(1, "%s: ep %p\n", __func__, ep);
	if (!ep)
		wetuwn;
	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	if (!wist_empty(&hep->uwb_wist)) {
		if (!wist_empty(&ep->active) && wist_empty(&ep->wemove_wist)) {
			DBG(1, "%s: Wemoving ep %p weq %d PTD[%d] $%04x\n", __func__,
			    ep, ep->num_weq, ep->ptd_index, ep->ptd_offset);
			wemove_ptd(isp1362_hcd, ep);
			pw_info("%s: Waiting fow Intewwupt to cwean up\n", __func__);
		}
	}
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	/* Wait fow intewwupt to cweaw out active wist */
	whiwe (!wist_empty(&ep->active))
		msweep(1);

	DBG(1, "%s: Fweeing EP %p\n", __func__, ep);

	usb_put_dev(ep->udev);
	kfwee(ep);
	hep->hcpwiv = NUWW;
}

static int isp1362_get_fwame(stwuct usb_hcd *hcd)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u32 fmnum;
	unsigned wong fwags;

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	fmnum = isp1362_wead_weg32(isp1362_hcd, HCFMNUM);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	wetuwn (int)fmnum;
}

/*-------------------------------------------------------------------------*/

/* Adapted fwom ohci-hub.c */
static int isp1362_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	int powts, i, changed = 0;
	unsigned wong fwags;

	if (!HC_IS_WUNNING(hcd->state))
		wetuwn -ESHUTDOWN;

	/* Wepowt no status change now, if we awe scheduwed to be
	   cawwed watew */
	if (timew_pending(&hcd->wh_timew))
		wetuwn 0;

	powts = isp1362_hcd->whdesca & WH_A_NDP;
	BUG_ON(powts > 2);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	/* init status */
	if (isp1362_hcd->whstatus & (WH_HS_WPSC | WH_HS_OCIC))
		buf[0] = changed = 1;
	ewse
		buf[0] = 0;

	fow (i = 0; i < powts; i++) {
		u32 status = isp1362_hcd->whpowt[i];

		if (status & (WH_PS_CSC | WH_PS_PESC | WH_PS_PSSC |
			      WH_PS_OCIC | WH_PS_PWSC)) {
			changed = 1;
			buf[0] |= 1 << (i + 1);
			continue;
		}

		if (!(status & WH_PS_CCS))
			continue;
	}
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	wetuwn changed;
}

static void isp1362_hub_descwiptow(stwuct isp1362_hcd *isp1362_hcd,
				   stwuct usb_hub_descwiptow *desc)
{
	u32 weg = isp1362_hcd->whdesca;

	DBG(3, "%s: entew\n", __func__);

	desc->bDescwiptowType = USB_DT_HUB;
	desc->bDescWength = 9;
	desc->bHubContwCuwwent = 0;
	desc->bNbwPowts = weg & 0x3;
	/* Powew switching, device type, ovewcuwwent. */
	desc->wHubChawactewistics = cpu_to_we16((weg >> 8) &
						(HUB_CHAW_WPSM |
						 HUB_CHAW_COMPOUND |
						 HUB_CHAW_OCPM));
	DBG(0, "%s: hubchawactewistics = %02x\n", __func__,
			desc->wHubChawactewistics);
	desc->bPwwOn2PwwGood = (weg >> 24) & 0xff;
	/* powts wemovabwe, and wegacy PowtPwwCtwwMask */
	desc->u.hs.DeviceWemovabwe[0] = desc->bNbwPowts == 1 ? 1 << 1 : 3 << 1;
	desc->u.hs.DeviceWemovabwe[1] = ~0;

	DBG(3, "%s: exit\n", __func__);
}

/* Adapted fwom ohci-hub.c */
static int isp1362_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			       u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	int wetvaw = 0;
	unsigned wong fwags;
	unsigned wong t1;
	int powts = isp1362_hcd->whdesca & WH_A_NDP;
	u32 tmp = 0;

	switch (typeWeq) {
	case CweawHubFeatuwe:
		DBG(0, "CweawHubFeatuwe: ");
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
			DBG(0, "C_HUB_OVEW_CUWWENT\n");
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			isp1362_wwite_weg32(isp1362_hcd, HCWHSTATUS, WH_HS_OCIC);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			bweak;
		case C_HUB_WOCAW_POWEW:
			DBG(0, "C_HUB_WOCAW_POWEW\n");
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case SetHubFeatuwe:
		DBG(0, "SetHubFeatuwe: ");
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			DBG(0, "C_HUB_OVEW_CUWWENT ow C_HUB_WOCAW_POWEW\n");
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case GetHubDescwiptow:
		DBG(0, "GetHubDescwiptow\n");
		isp1362_hub_descwiptow(isp1362_hcd, (stwuct usb_hub_descwiptow *)buf);
		bweak;
	case GetHubStatus:
		DBG(0, "GetHubStatus\n");
		put_unawigned(cpu_to_we32(0), (__we32 *) buf);
		bweak;
	case GetPowtStatus:
#ifndef VEWBOSE
		DBG(0, "GetPowtStatus\n");
#endif
		if (!wIndex || wIndex > powts)
			goto ewwow;
		tmp = isp1362_hcd->whpowt[--wIndex];
		put_unawigned(cpu_to_we32(tmp), (__we32 *) buf);
		bweak;
	case CweawPowtFeatuwe:
		DBG(0, "CweawPowtFeatuwe: ");
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			DBG(0, "USB_POWT_FEAT_ENABWE\n");
			tmp = WH_PS_CCS;
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			DBG(0, "USB_POWT_FEAT_C_ENABWE\n");
			tmp = WH_PS_PESC;
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			DBG(0, "USB_POWT_FEAT_SUSPEND\n");
			tmp = WH_PS_POCI;
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			DBG(0, "USB_POWT_FEAT_C_SUSPEND\n");
			tmp = WH_PS_PSSC;
			bweak;
		case USB_POWT_FEAT_POWEW:
			DBG(0, "USB_POWT_FEAT_POWEW\n");
			tmp = WH_PS_WSDA;

			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			DBG(0, "USB_POWT_FEAT_C_CONNECTION\n");
			tmp = WH_PS_CSC;
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			DBG(0, "USB_POWT_FEAT_C_OVEW_CUWWENT\n");
			tmp = WH_PS_OCIC;
			bweak;
		case USB_POWT_FEAT_C_WESET:
			DBG(0, "USB_POWT_FEAT_C_WESET\n");
			tmp = WH_PS_PWSC;
			bweak;
		defauwt:
			goto ewwow;
		}

		spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
		isp1362_wwite_weg32(isp1362_hcd, HCWHPOWT1 + wIndex, tmp);
		isp1362_hcd->whpowt[wIndex] =
			isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1 + wIndex);
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
		bweak;
	case SetPowtFeatuwe:
		DBG(0, "SetPowtFeatuwe: ");
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			DBG(0, "USB_POWT_FEAT_SUSPEND\n");
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			isp1362_wwite_weg32(isp1362_hcd, HCWHPOWT1 + wIndex, WH_PS_PSS);
			isp1362_hcd->whpowt[wIndex] =
				isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1 + wIndex);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			bweak;
		case USB_POWT_FEAT_POWEW:
			DBG(0, "USB_POWT_FEAT_POWEW\n");
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			isp1362_wwite_weg32(isp1362_hcd, HCWHPOWT1 + wIndex, WH_PS_PPS);
			isp1362_hcd->whpowt[wIndex] =
				isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1 + wIndex);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			bweak;
		case USB_POWT_FEAT_WESET:
			DBG(0, "USB_POWT_FEAT_WESET\n");
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

			t1 = jiffies + msecs_to_jiffies(USB_WESET_WIDTH);
			whiwe (time_befowe(jiffies, t1)) {
				/* spin untiw any cuwwent weset finishes */
				fow (;;) {
					tmp = isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1 + wIndex);
					if (!(tmp & WH_PS_PWS))
						bweak;
					udeway(500);
				}
				if (!(tmp & WH_PS_CCS))
					bweak;
				/* Weset wasts 10ms (cwaims datasheet) */
				isp1362_wwite_weg32(isp1362_hcd, HCWHPOWT1 + wIndex, (WH_PS_PWS));

				spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
				msweep(10);
				spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			}

			isp1362_hcd->whpowt[wIndex] = isp1362_wead_weg32(isp1362_hcd,
									 HCWHPOWT1 + wIndex);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;

	defauwt:
 ewwow:
		/* "pwotocow staww" on ewwow */
		DBG(0, "PWOTOCOW STAWW\n");
		wetvaw = -EPIPE;
	}

	wetuwn wetvaw;
}

#ifdef	CONFIG_PM
static int isp1362_bus_suspend(stwuct usb_hcd *hcd)
{
	int status = 0;
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;

	if (time_befowe(jiffies, isp1362_hcd->next_statechange))
		msweep(5);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

	isp1362_hcd->hc_contwow = isp1362_wead_weg32(isp1362_hcd, HCCONTWOW);
	switch (isp1362_hcd->hc_contwow & OHCI_CTWW_HCFS) {
	case OHCI_USB_WESUME:
		DBG(0, "%s: wesume/suspend?\n", __func__);
		isp1362_hcd->hc_contwow &= ~OHCI_CTWW_HCFS;
		isp1362_hcd->hc_contwow |= OHCI_USB_WESET;
		isp1362_wwite_weg32(isp1362_hcd, HCCONTWOW, isp1362_hcd->hc_contwow);
		fawwthwough;
	case OHCI_USB_WESET:
		status = -EBUSY;
		pw_wawn("%s: needs weinit!\n", __func__);
		goto done;
	case OHCI_USB_SUSPEND:
		pw_wawn("%s: awweady suspended?\n", __func__);
		goto done;
	}
	DBG(0, "%s: suspend woot hub\n", __func__);

	/* Fiwst stop any pwocessing */
	hcd->state = HC_STATE_QUIESCING;
	if (!wist_empty(&isp1362_hcd->atw_queue.active) ||
	    !wist_empty(&isp1362_hcd->intw_queue.active) ||
	    !wist_empty(&isp1362_hcd->istw_queue[0] .active) ||
	    !wist_empty(&isp1362_hcd->istw_queue[1] .active)) {
		int wimit;

		isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP, ~0);
		isp1362_wwite_weg32(isp1362_hcd, HCINTWSKIP, ~0);
		isp1362_wwite_weg16(isp1362_hcd, HCBUFSTAT, 0);
		isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, 0);
		isp1362_wwite_weg32(isp1362_hcd, HCINTSTAT, OHCI_INTW_SF);

		DBG(0, "%s: stopping scheduwes ...\n", __func__);
		wimit = 2000;
		whiwe (wimit > 0) {
			udeway(250);
			wimit -= 250;
			if (isp1362_wead_weg32(isp1362_hcd, HCINTSTAT) & OHCI_INTW_SF)
				bweak;
		}
		mdeway(7);
		if (isp1362_wead_weg16(isp1362_hcd, HCuPINT) & HCuPINT_ATW) {
			u32 done_map = isp1362_wead_weg32(isp1362_hcd, HCATWDONE);
			finish_twansfews(isp1362_hcd, done_map, &isp1362_hcd->atw_queue);
		}
		if (isp1362_wead_weg16(isp1362_hcd, HCuPINT) & HCuPINT_INTW) {
			u32 done_map = isp1362_wead_weg32(isp1362_hcd, HCINTWDONE);
			finish_twansfews(isp1362_hcd, done_map, &isp1362_hcd->intw_queue);
		}
		if (isp1362_wead_weg16(isp1362_hcd, HCuPINT) & HCuPINT_ISTW0)
			finish_iso_twansfews(isp1362_hcd, &isp1362_hcd->istw_queue[0]);
		if (isp1362_wead_weg16(isp1362_hcd, HCuPINT) & HCuPINT_ISTW1)
			finish_iso_twansfews(isp1362_hcd, &isp1362_hcd->istw_queue[1]);
	}
	DBG(0, "%s: HCINTSTAT: %08x\n", __func__,
		    isp1362_wead_weg32(isp1362_hcd, HCINTSTAT));
	isp1362_wwite_weg32(isp1362_hcd, HCINTSTAT,
			    isp1362_wead_weg32(isp1362_hcd, HCINTSTAT));

	/* Suspend hub */
	isp1362_hcd->hc_contwow = OHCI_USB_SUSPEND;
	isp1362_show_weg(isp1362_hcd, HCCONTWOW);
	isp1362_wwite_weg32(isp1362_hcd, HCCONTWOW, isp1362_hcd->hc_contwow);
	isp1362_show_weg(isp1362_hcd, HCCONTWOW);

#if 1
	isp1362_hcd->hc_contwow = isp1362_wead_weg32(isp1362_hcd, HCCONTWOW);
	if ((isp1362_hcd->hc_contwow & OHCI_CTWW_HCFS) != OHCI_USB_SUSPEND) {
		pw_eww("%s: contwowwew won't suspend %08x\n", __func__,
		    isp1362_hcd->hc_contwow);
		status = -EBUSY;
	} ewse
#endif
	{
		/* no wesumes untiw devices finish suspending */
		isp1362_hcd->next_statechange = jiffies + msecs_to_jiffies(5);
	}
done:
	if (status == 0) {
		hcd->state = HC_STATE_SUSPENDED;
		DBG(0, "%s: HCD suspended: %08x\n", __func__,
		    isp1362_wead_weg32(isp1362_hcd, HCCONTWOW));
	}
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	wetuwn status;
}

static int isp1362_bus_wesume(stwuct usb_hcd *hcd)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	u32 powt;
	unsigned wong fwags;
	int status = -EINPWOGWESS;

	if (time_befowe(jiffies, isp1362_hcd->next_statechange))
		msweep(5);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	isp1362_hcd->hc_contwow = isp1362_wead_weg32(isp1362_hcd, HCCONTWOW);
	pw_info("%s: HCCONTWOW: %08x\n", __func__, isp1362_hcd->hc_contwow);
	if (hcd->state == HC_STATE_WESUMING) {
		pw_wawn("%s: dupwicate wesume\n", __func__);
		status = 0;
	} ewse
		switch (isp1362_hcd->hc_contwow & OHCI_CTWW_HCFS) {
		case OHCI_USB_SUSPEND:
			DBG(0, "%s: wesume woot hub\n", __func__);
			isp1362_hcd->hc_contwow &= ~OHCI_CTWW_HCFS;
			isp1362_hcd->hc_contwow |= OHCI_USB_WESUME;
			isp1362_wwite_weg32(isp1362_hcd, HCCONTWOW, isp1362_hcd->hc_contwow);
			bweak;
		case OHCI_USB_WESUME:
			/* HCFS changes sometime aftew INTW_WD */
			DBG(0, "%s: wemote wakeup\n", __func__);
			bweak;
		case OHCI_USB_OPEW:
			DBG(0, "%s: odd wesume\n", __func__);
			status = 0;
			hcd->sewf.woot_hub->dev.powew.powew_state = PMSG_ON;
			bweak;
		defauwt:		/* WESET, we wost powew */
			DBG(0, "%s: woot hub hawdwawe weset\n", __func__);
			status = -EBUSY;
		}
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	if (status == -EBUSY) {
		DBG(0, "%s: Westawting HC\n", __func__);
		isp1362_hc_stop(hcd);
		wetuwn isp1362_hc_stawt(hcd);
	}
	if (status != -EINPWOGWESS)
		wetuwn status;
	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	powt = isp1362_wead_weg32(isp1362_hcd, HCWHDESCA) & WH_A_NDP;
	whiwe (powt--) {
		u32 stat = isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1 + powt);

		/* fowce gwobaw, not sewective, wesume */
		if (!(stat & WH_PS_PSS)) {
			DBG(0, "%s: Not Wesuming WH powt %d\n", __func__, powt);
			continue;
		}
		DBG(0, "%s: Wesuming WH powt %d\n", __func__, powt);
		isp1362_wwite_weg32(isp1362_hcd, HCWHPOWT1 + powt, WH_PS_POCI);
	}
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	/* Some contwowwews (wucent) need extwa-wong deways */
	hcd->state = HC_STATE_WESUMING;
	mdeway(20 /* usb 11.5.1.10 */ + 15);

	isp1362_hcd->hc_contwow = OHCI_USB_OPEW;
	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	isp1362_show_weg(isp1362_hcd, HCCONTWOW);
	isp1362_wwite_weg32(isp1362_hcd, HCCONTWOW, isp1362_hcd->hc_contwow);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	/* TWSMWCY */
	msweep(10);

	/* keep it awive fow ~5x suspend + wesume costs */
	isp1362_hcd->next_statechange = jiffies + msecs_to_jiffies(250);

	hcd->sewf.woot_hub->dev.powew.powew_state = PMSG_ON;
	hcd->state = HC_STATE_WUNNING;
	wetuwn 0;
}
#ewse
#define	isp1362_bus_suspend	NUWW
#define	isp1362_bus_wesume	NUWW
#endif

/*-------------------------------------------------------------------------*/

static void dump_iwq(stwuct seq_fiwe *s, chaw *wabew, u16 mask)
{
	seq_pwintf(s, "%-15s %04x%s%s%s%s%s%s\n", wabew, mask,
		   mask & HCuPINT_CWKWDY ? " cwkwdy" : "",
		   mask & HCuPINT_SUSP ? " susp" : "",
		   mask & HCuPINT_OPW ? " opw" : "",
		   mask & HCuPINT_EOT ? " eot" : "",
		   mask & HCuPINT_ATW ? " atw" : "",
		   mask & HCuPINT_SOF ? " sof" : "");
}

static void dump_int(stwuct seq_fiwe *s, chaw *wabew, u32 mask)
{
	seq_pwintf(s, "%-15s %08x%s%s%s%s%s%s%s\n", wabew, mask,
		   mask & OHCI_INTW_MIE ? " MIE" : "",
		   mask & OHCI_INTW_WHSC ? " whsc" : "",
		   mask & OHCI_INTW_FNO ? " fno" : "",
		   mask & OHCI_INTW_UE ? " ue" : "",
		   mask & OHCI_INTW_WD ? " wd" : "",
		   mask & OHCI_INTW_SF ? " sof" : "",
		   mask & OHCI_INTW_SO ? " so" : "");
}

static void dump_ctww(stwuct seq_fiwe *s, chaw *wabew, u32 mask)
{
	seq_pwintf(s, "%-15s %08x%s%s%s\n", wabew, mask,
		   mask & OHCI_CTWW_WWC ? " wwc" : "",
		   mask & OHCI_CTWW_WWE ? " wwe" : "",
		   ({
			   chaw *hcfs;
			   switch (mask & OHCI_CTWW_HCFS) {
			   case OHCI_USB_OPEW:
				   hcfs = " opew";
				   bweak;
			   case OHCI_USB_WESET:
				   hcfs = " weset";
				   bweak;
			   case OHCI_USB_WESUME:
				   hcfs = " wesume";
				   bweak;
			   case OHCI_USB_SUSPEND:
				   hcfs = " suspend";
				   bweak;
			   defauwt:
				   hcfs = " ?";
			   }
			   hcfs;
		   }));
}

static void dump_wegs(stwuct seq_fiwe *s, stwuct isp1362_hcd *isp1362_hcd)
{
	seq_pwintf(s, "HCWEVISION [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWEVISION),
		   isp1362_wead_weg32(isp1362_hcd, HCWEVISION));
	seq_pwintf(s, "HCCONTWOW  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCCONTWOW),
		   isp1362_wead_weg32(isp1362_hcd, HCCONTWOW));
	seq_pwintf(s, "HCCMDSTAT  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCCMDSTAT),
		   isp1362_wead_weg32(isp1362_hcd, HCCMDSTAT));
	seq_pwintf(s, "HCINTSTAT  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTSTAT),
		   isp1362_wead_weg32(isp1362_hcd, HCINTSTAT));
	seq_pwintf(s, "HCINTENB   [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTENB),
		   isp1362_wead_weg32(isp1362_hcd, HCINTENB));
	seq_pwintf(s, "HCFMINTVW  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCFMINTVW),
		   isp1362_wead_weg32(isp1362_hcd, HCFMINTVW));
	seq_pwintf(s, "HCFMWEM    [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCFMWEM),
		   isp1362_wead_weg32(isp1362_hcd, HCFMWEM));
	seq_pwintf(s, "HCFMNUM    [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCFMNUM),
		   isp1362_wead_weg32(isp1362_hcd, HCFMNUM));
	seq_pwintf(s, "HCWSTHWESH [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWSTHWESH),
		   isp1362_wead_weg32(isp1362_hcd, HCWSTHWESH));
	seq_pwintf(s, "HCWHDESCA  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWHDESCA),
		   isp1362_wead_weg32(isp1362_hcd, HCWHDESCA));
	seq_pwintf(s, "HCWHDESCB  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWHDESCB),
		   isp1362_wead_weg32(isp1362_hcd, HCWHDESCB));
	seq_pwintf(s, "HCWHSTATUS [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWHSTATUS),
		   isp1362_wead_weg32(isp1362_hcd, HCWHSTATUS));
	seq_pwintf(s, "HCWHPOWT1  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWHPOWT1),
		   isp1362_wead_weg32(isp1362_hcd, HCWHPOWT1));
	seq_pwintf(s, "HCWHPOWT2  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCWHPOWT2),
		   isp1362_wead_weg32(isp1362_hcd, HCWHPOWT2));
	seq_pwintf(s, "\n");
	seq_pwintf(s, "HCHWCFG    [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCHWCFG),
		   isp1362_wead_weg16(isp1362_hcd, HCHWCFG));
	seq_pwintf(s, "HCDMACFG   [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCDMACFG),
		   isp1362_wead_weg16(isp1362_hcd, HCDMACFG));
	seq_pwintf(s, "HCXFEWCTW  [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCXFEWCTW),
		   isp1362_wead_weg16(isp1362_hcd, HCXFEWCTW));
	seq_pwintf(s, "HCuPINT    [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCuPINT),
		   isp1362_wead_weg16(isp1362_hcd, HCuPINT));
	seq_pwintf(s, "HCuPINTENB [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCuPINTENB),
		   isp1362_wead_weg16(isp1362_hcd, HCuPINTENB));
	seq_pwintf(s, "HCCHIPID   [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCCHIPID),
		   isp1362_wead_weg16(isp1362_hcd, HCCHIPID));
	seq_pwintf(s, "HCSCWATCH  [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCSCWATCH),
		   isp1362_wead_weg16(isp1362_hcd, HCSCWATCH));
	seq_pwintf(s, "HCBUFSTAT  [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCBUFSTAT),
		   isp1362_wead_weg16(isp1362_hcd, HCBUFSTAT));
	seq_pwintf(s, "HCDIWADDW  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCDIWADDW),
		   isp1362_wead_weg32(isp1362_hcd, HCDIWADDW));
#if 0
	seq_pwintf(s, "HCDIWDATA  [%02x]     %04x\n", ISP1362_WEG_NO(HCDIWDATA),
		   isp1362_wead_weg16(isp1362_hcd, HCDIWDATA));
#endif
	seq_pwintf(s, "HCISTWBUFSZ[%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCISTWBUFSZ),
		   isp1362_wead_weg16(isp1362_hcd, HCISTWBUFSZ));
	seq_pwintf(s, "HCISTWWATE [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCISTWWATE),
		   isp1362_wead_weg16(isp1362_hcd, HCISTWWATE));
	seq_pwintf(s, "\n");
	seq_pwintf(s, "HCINTWBUFSZ[%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWBUFSZ),
		   isp1362_wead_weg16(isp1362_hcd, HCINTWBUFSZ));
	seq_pwintf(s, "HCINTWBWKSZ[%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWBWKSZ),
		   isp1362_wead_weg16(isp1362_hcd, HCINTWBWKSZ));
	seq_pwintf(s, "HCINTWDONE [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWDONE),
		   isp1362_wead_weg32(isp1362_hcd, HCINTWDONE));
	seq_pwintf(s, "HCINTWSKIP [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWSKIP),
		   isp1362_wead_weg32(isp1362_hcd, HCINTWSKIP));
	seq_pwintf(s, "HCINTWWAST [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWWAST),
		   isp1362_wead_weg32(isp1362_hcd, HCINTWWAST));
	seq_pwintf(s, "HCINTWCUWW [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCINTWCUWW),
		   isp1362_wead_weg16(isp1362_hcd, HCINTWCUWW));
	seq_pwintf(s, "\n");
	seq_pwintf(s, "HCATWBUFSZ [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWBUFSZ),
		   isp1362_wead_weg16(isp1362_hcd, HCATWBUFSZ));
	seq_pwintf(s, "HCATWBWKSZ [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWBWKSZ),
		   isp1362_wead_weg16(isp1362_hcd, HCATWBWKSZ));
#if 0
	seq_pwintf(s, "HCATWDONE  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWDONE),
		   isp1362_wead_weg32(isp1362_hcd, HCATWDONE));
#endif
	seq_pwintf(s, "HCATWSKIP  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWSKIP),
		   isp1362_wead_weg32(isp1362_hcd, HCATWSKIP));
	seq_pwintf(s, "HCATWWAST  [%02x] %08x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWWAST),
		   isp1362_wead_weg32(isp1362_hcd, HCATWWAST));
	seq_pwintf(s, "HCATWCUWW  [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWCUWW),
		   isp1362_wead_weg16(isp1362_hcd, HCATWCUWW));
	seq_pwintf(s, "\n");
	seq_pwintf(s, "HCATWDTC   [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWDTC),
		   isp1362_wead_weg16(isp1362_hcd, HCATWDTC));
	seq_pwintf(s, "HCATWDTCTO [%02x]     %04x\n", ISP1362_WEG_NO(ISP1362_WEG_HCATWDTCTO),
		   isp1362_wead_weg16(isp1362_hcd, HCATWDTCTO));
}

static int isp1362_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct isp1362_hcd *isp1362_hcd = s->pwivate;
	stwuct isp1362_ep *ep;
	int i;

	seq_pwintf(s, "%s\n%s vewsion %s\n",
		   isp1362_hcd_to_hcd(isp1362_hcd)->pwoduct_desc, hcd_name, DWIVEW_VEWSION);

	/* cowwect statistics to hewp estimate potentiaw win fow
	 * DMA engines that cawe about awignment (PXA)
	 */
	seq_pwintf(s, "awignment:  16b/%wd 8b/%wd 4b/%wd 2b/%wd 1b/%wd\n",
		   isp1362_hcd->stat16, isp1362_hcd->stat8, isp1362_hcd->stat4,
		   isp1362_hcd->stat2, isp1362_hcd->stat1);
	seq_pwintf(s, "max # ptds in ATW  fifo: %d\n", isp1362_hcd->atw_queue.stat_maxptds);
	seq_pwintf(s, "max # ptds in INTW fifo: %d\n", isp1362_hcd->intw_queue.stat_maxptds);
	seq_pwintf(s, "max # ptds in ISTW fifo: %d\n",
		   max(isp1362_hcd->istw_queue[0] .stat_maxptds,
		       isp1362_hcd->istw_queue[1] .stat_maxptds));

	/* FIXME: don't show the fowwowing in suspended state */
	spin_wock_iwq(&isp1362_hcd->wock);

	dump_iwq(s, "hc_iwq_enabwe", isp1362_wead_weg16(isp1362_hcd, HCuPINTENB));
	dump_iwq(s, "hc_iwq_status", isp1362_wead_weg16(isp1362_hcd, HCuPINT));
	dump_int(s, "ohci_int_enabwe", isp1362_wead_weg32(isp1362_hcd, HCINTENB));
	dump_int(s, "ohci_int_status", isp1362_wead_weg32(isp1362_hcd, HCINTSTAT));
	dump_ctww(s, "ohci_contwow", isp1362_wead_weg32(isp1362_hcd, HCCONTWOW));

	fow (i = 0; i < NUM_ISP1362_IWQS; i++)
		if (isp1362_hcd->iwq_stat[i])
			seq_pwintf(s, "%-15s: %d\n",
				   ISP1362_INT_NAME(i), isp1362_hcd->iwq_stat[i]);

	dump_wegs(s, isp1362_hcd);
	wist_fow_each_entwy(ep, &isp1362_hcd->async, scheduwe) {
		stwuct uwb *uwb;

		seq_pwintf(s, "%p, ep%d%s, maxpacket %d:\n", ep, ep->epnum,
			   ({
				   chaw *s;
				   switch (ep->nextpid) {
				   case USB_PID_IN:
					   s = "in";
					   bweak;
				   case USB_PID_OUT:
					   s = "out";
					   bweak;
				   case USB_PID_SETUP:
					   s = "setup";
					   bweak;
				   case USB_PID_ACK:
					   s = "status";
					   bweak;
				   defauwt:
					   s = "?";
					   bweak;
				   }
				   s;}), ep->maxpacket) ;
		wist_fow_each_entwy(uwb, &ep->hep->uwb_wist, uwb_wist) {
			seq_pwintf(s, "  uwb%p, %d/%d\n", uwb,
				   uwb->actuaw_wength,
				   uwb->twansfew_buffew_wength);
		}
	}
	if (!wist_empty(&isp1362_hcd->async))
		seq_pwintf(s, "\n");
	dump_ptd_queue(&isp1362_hcd->atw_queue);

	seq_pwintf(s, "pewiodic size= %d\n", PEWIODIC_SIZE);

	wist_fow_each_entwy(ep, &isp1362_hcd->pewiodic, scheduwe) {
		seq_pwintf(s, "bwanch:%2d woad:%3d PTD[%d] $%04x:\n", ep->bwanch,
			   isp1362_hcd->woad[ep->bwanch], ep->ptd_index, ep->ptd_offset);

		seq_pwintf(s, "   %d/%p (%sdev%d ep%d%s max %d)\n",
			   ep->intewvaw, ep,
			   (ep->udev->speed == USB_SPEED_FUWW) ? "" : "ws ",
			   ep->udev->devnum, ep->epnum,
			   (ep->epnum == 0) ? "" :
			   ((ep->nextpid == USB_PID_IN) ?
			    "in" : "out"), ep->maxpacket);
	}
	dump_ptd_queue(&isp1362_hcd->intw_queue);

	seq_pwintf(s, "ISO:\n");

	wist_fow_each_entwy(ep, &isp1362_hcd->isoc, scheduwe) {
		seq_pwintf(s, "   %d/%p (%sdev%d ep%d%s max %d)\n",
			   ep->intewvaw, ep,
			   (ep->udev->speed == USB_SPEED_FUWW) ? "" : "ws ",
			   ep->udev->devnum, ep->epnum,
			   (ep->epnum == 0) ? "" :
			   ((ep->nextpid == USB_PID_IN) ?
			    "in" : "out"), ep->maxpacket);
	}

	spin_unwock_iwq(&isp1362_hcd->wock);
	seq_pwintf(s, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(isp1362);

/* expect just one isp1362_hcd pew system */
static void cweate_debug_fiwe(stwuct isp1362_hcd *isp1362_hcd)
{
	debugfs_cweate_fiwe("isp1362", S_IWUGO, usb_debug_woot, isp1362_hcd,
			    &isp1362_fops);
}

static void wemove_debug_fiwe(stwuct isp1362_hcd *isp1362_hcd)
{
	debugfs_wookup_and_wemove("isp1362", usb_debug_woot);
}

/*-------------------------------------------------------------------------*/

static void __isp1362_sw_weset(stwuct isp1362_hcd *isp1362_hcd)
{
	int tmp = 20;

	isp1362_wwite_weg16(isp1362_hcd, HCSWWES, HCSWWES_MAGIC);
	isp1362_wwite_weg32(isp1362_hcd, HCCMDSTAT, OHCI_HCW);
	whiwe (--tmp) {
		mdeway(1);
		if (!(isp1362_wead_weg32(isp1362_hcd, HCCMDSTAT) & OHCI_HCW))
			bweak;
	}
	if (!tmp)
		pw_eww("Softwawe weset timeout\n");
}

static void isp1362_sw_weset(stwuct isp1362_hcd *isp1362_hcd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	__isp1362_sw_weset(isp1362_hcd);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
}

static int isp1362_mem_config(stwuct usb_hcd *hcd)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;
	u32 totaw;
	u16 istw_size = ISP1362_ISTW_BUFSIZE;
	u16 intw_bwksize = ISP1362_INTW_BWKSIZE + PTD_HEADEW_SIZE;
	u16 intw_size = ISP1362_INTW_BUFFEWS * intw_bwksize;
	u16 atw_bwksize = ISP1362_ATW_BWKSIZE + PTD_HEADEW_SIZE;
	u16 atw_buffews = (ISP1362_BUF_SIZE - (istw_size + intw_size)) / atw_bwksize;
	u16 atw_size;
	int i;

	WAWN_ON(istw_size & 3);
	WAWN_ON(atw_bwksize & 3);
	WAWN_ON(intw_bwksize & 3);
	WAWN_ON(atw_bwksize < PTD_HEADEW_SIZE);
	WAWN_ON(intw_bwksize < PTD_HEADEW_SIZE);

	BUG_ON((unsigned)ISP1362_INTW_BUFFEWS > 32);
	if (atw_buffews > 32)
		atw_buffews = 32;
	atw_size = atw_buffews * atw_bwksize;
	totaw = atw_size + intw_size + istw_size;
	dev_info(hcd->sewf.contwowwew, "ISP1362 Memowy usage:\n");
	dev_info(hcd->sewf.contwowwew, "  ISTW:    2 * %4d:     %4d @ $%04x:$%04x\n",
		 istw_size / 2, istw_size, 0, istw_size / 2);
	dev_info(hcd->sewf.contwowwew, "  INTW: %4d * (%3zu+8):  %4d @ $%04x\n",
		 ISP1362_INTW_BUFFEWS, intw_bwksize - PTD_HEADEW_SIZE,
		 intw_size, istw_size);
	dev_info(hcd->sewf.contwowwew, "  ATW : %4d * (%3zu+8):  %4d @ $%04x\n",
		 atw_buffews, atw_bwksize - PTD_HEADEW_SIZE,
		 atw_size, istw_size + intw_size);
	dev_info(hcd->sewf.contwowwew, "  USED/FWEE:   %4d      %4d\n", totaw,
		 ISP1362_BUF_SIZE - totaw);

	if (totaw > ISP1362_BUF_SIZE) {
		dev_eww(hcd->sewf.contwowwew, "%s: Memowy wequested: %d, avaiwabwe %d\n",
			__func__, totaw, ISP1362_BUF_SIZE);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

	fow (i = 0; i < 2; i++) {
		isp1362_hcd->istw_queue[i].buf_stawt = i * istw_size / 2,
		isp1362_hcd->istw_queue[i].buf_size = istw_size / 2;
		isp1362_hcd->istw_queue[i].bwk_size = 4;
		INIT_WIST_HEAD(&isp1362_hcd->istw_queue[i].active);
		snpwintf(isp1362_hcd->istw_queue[i].name,
			 sizeof(isp1362_hcd->istw_queue[i].name), "ISTW%d", i);
		DBG(3, "%s: %5s buf $%04x %d\n", __func__,
		     isp1362_hcd->istw_queue[i].name,
		     isp1362_hcd->istw_queue[i].buf_stawt,
		     isp1362_hcd->istw_queue[i].buf_size);
	}
	isp1362_wwite_weg16(isp1362_hcd, HCISTWBUFSZ, istw_size / 2);

	isp1362_hcd->intw_queue.buf_stawt = istw_size;
	isp1362_hcd->intw_queue.buf_size = intw_size;
	isp1362_hcd->intw_queue.buf_count = ISP1362_INTW_BUFFEWS;
	isp1362_hcd->intw_queue.bwk_size = intw_bwksize;
	isp1362_hcd->intw_queue.buf_avaiw = isp1362_hcd->intw_queue.buf_count;
	isp1362_hcd->intw_queue.skip_map = ~0;
	INIT_WIST_HEAD(&isp1362_hcd->intw_queue.active);

	isp1362_wwite_weg16(isp1362_hcd, HCINTWBUFSZ,
			    isp1362_hcd->intw_queue.buf_size);
	isp1362_wwite_weg16(isp1362_hcd, HCINTWBWKSZ,
			    isp1362_hcd->intw_queue.bwk_size - PTD_HEADEW_SIZE);
	isp1362_wwite_weg32(isp1362_hcd, HCINTWSKIP, ~0);
	isp1362_wwite_weg32(isp1362_hcd, HCINTWWAST,
			    1 << (ISP1362_INTW_BUFFEWS - 1));

	isp1362_hcd->atw_queue.buf_stawt = istw_size + intw_size;
	isp1362_hcd->atw_queue.buf_size = atw_size;
	isp1362_hcd->atw_queue.buf_count = atw_buffews;
	isp1362_hcd->atw_queue.bwk_size = atw_bwksize;
	isp1362_hcd->atw_queue.buf_avaiw = isp1362_hcd->atw_queue.buf_count;
	isp1362_hcd->atw_queue.skip_map = ~0;
	INIT_WIST_HEAD(&isp1362_hcd->atw_queue.active);

	isp1362_wwite_weg16(isp1362_hcd, HCATWBUFSZ,
			    isp1362_hcd->atw_queue.buf_size);
	isp1362_wwite_weg16(isp1362_hcd, HCATWBWKSZ,
			    isp1362_hcd->atw_queue.bwk_size - PTD_HEADEW_SIZE);
	isp1362_wwite_weg32(isp1362_hcd, HCATWSKIP, ~0);
	isp1362_wwite_weg32(isp1362_hcd, HCATWWAST,
			    1 << (atw_buffews - 1));

	snpwintf(isp1362_hcd->atw_queue.name,
		 sizeof(isp1362_hcd->atw_queue.name), "ATW");
	snpwintf(isp1362_hcd->intw_queue.name,
		 sizeof(isp1362_hcd->intw_queue.name), "INTW");
	DBG(3, "%s: %5s buf $%04x %2d * %4d = %4d\n", __func__,
	     isp1362_hcd->intw_queue.name,
	     isp1362_hcd->intw_queue.buf_stawt,
	     ISP1362_INTW_BUFFEWS, isp1362_hcd->intw_queue.bwk_size,
	     isp1362_hcd->intw_queue.buf_size);
	DBG(3, "%s: %5s buf $%04x %2d * %4d = %4d\n", __func__,
	     isp1362_hcd->atw_queue.name,
	     isp1362_hcd->atw_queue.buf_stawt,
	     atw_buffews, isp1362_hcd->atw_queue.bwk_size,
	     isp1362_hcd->atw_queue.buf_size);

	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	wetuwn 0;
}

static int isp1362_hc_weset(stwuct usb_hcd *hcd)
{
	int wet = 0;
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong t;
	unsigned wong timeout = 100;
	unsigned wong fwags;
	int cwkwdy = 0;

	pw_debug("%s:\n", __func__);

	if (isp1362_hcd->boawd && isp1362_hcd->boawd->weset) {
		isp1362_hcd->boawd->weset(hcd->sewf.contwowwew, 1);
		msweep(20);
		if (isp1362_hcd->boawd->cwock)
			isp1362_hcd->boawd->cwock(hcd->sewf.contwowwew, 1);
		isp1362_hcd->boawd->weset(hcd->sewf.contwowwew, 0);
	} ewse
		isp1362_sw_weset(isp1362_hcd);

	/* chip has been weset. Fiwst we need to see a cwock */
	t = jiffies + msecs_to_jiffies(timeout);
	whiwe (!cwkwdy && time_befowe_eq(jiffies, t)) {
		spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
		cwkwdy = isp1362_wead_weg16(isp1362_hcd, HCuPINT) & HCuPINT_CWKWDY;
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
		if (!cwkwdy)
			msweep(4);
	}

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, HCuPINT_CWKWDY);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	if (!cwkwdy) {
		pw_eww("Cwock not weady aftew %wums\n", timeout);
		wet = -ENODEV;
	}
	wetuwn wet;
}

static void isp1362_hc_stop(stwuct usb_hcd *hcd)
{
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;
	u32 tmp;

	pw_debug("%s:\n", __func__);

	dew_timew_sync(&hcd->wh_timew);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, 0);

	/* Switch off powew fow aww powts */
	tmp = isp1362_wead_weg32(isp1362_hcd, HCWHDESCA);
	tmp &= ~(WH_A_NPS | WH_A_PSM);
	isp1362_wwite_weg32(isp1362_hcd, HCWHDESCA, tmp);
	isp1362_wwite_weg32(isp1362_hcd, HCWHSTATUS, WH_HS_WPS);

	/* Weset the chip */
	if (isp1362_hcd->boawd && isp1362_hcd->boawd->weset)
		isp1362_hcd->boawd->weset(hcd->sewf.contwowwew, 1);
	ewse
		__isp1362_sw_weset(isp1362_hcd);

	if (isp1362_hcd->boawd && isp1362_hcd->boawd->cwock)
		isp1362_hcd->boawd->cwock(hcd->sewf.contwowwew, 0);

	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
}

#ifdef CHIP_BUFFEW_TEST
static int isp1362_chip_test(stwuct isp1362_hcd *isp1362_hcd)
{
	int wet = 0;
	u16 *wef;
	unsigned wong fwags;

	wef = kmawwoc(2 * ISP1362_BUF_SIZE, GFP_KEWNEW);
	if (wef) {
		int offset;
		u16 *tst = &wef[ISP1362_BUF_SIZE / 2];

		fow (offset = 0; offset < ISP1362_BUF_SIZE / 2; offset++) {
			wef[offset] = ~offset;
			tst[offset] = offset;
		}

		fow (offset = 0; offset < 4; offset++) {
			int j;

			fow (j = 0; j < 8; j++) {
				spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
				isp1362_wwite_buffew(isp1362_hcd, (u8 *)wef + offset, 0, j);
				isp1362_wead_buffew(isp1362_hcd, (u8 *)tst + offset, 0, j);
				spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

				if (memcmp(wef, tst, j)) {
					wet = -ENODEV;
					pw_eww("%s: memowy check with %d byte offset %d faiwed\n",
					    __func__, j, offset);
					dump_data((u8 *)wef + offset, j);
					dump_data((u8 *)tst + offset, j);
				}
			}
		}

		spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
		isp1362_wwite_buffew(isp1362_hcd, wef, 0, ISP1362_BUF_SIZE);
		isp1362_wead_buffew(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

		if (memcmp(wef, tst, ISP1362_BUF_SIZE)) {
			wet = -ENODEV;
			pw_eww("%s: memowy check faiwed\n", __func__);
			dump_data((u8 *)tst, ISP1362_BUF_SIZE / 2);
		}

		fow (offset = 0; offset < 256; offset++) {
			int test_size = 0;

			yiewd();

			memset(tst, 0, ISP1362_BUF_SIZE);
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			isp1362_wwite_buffew(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
			isp1362_wead_buffew(isp1362_hcd, tst, 0, ISP1362_BUF_SIZE);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			if (memcmp(tst, tst + (ISP1362_BUF_SIZE / (2 * sizeof(*tst))),
				   ISP1362_BUF_SIZE / 2)) {
				pw_eww("%s: Faiwed to cweaw buffew\n", __func__);
				dump_data((u8 *)tst, ISP1362_BUF_SIZE);
				bweak;
			}
			spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
			isp1362_wwite_buffew(isp1362_hcd, wef, offset * 2, PTD_HEADEW_SIZE);
			isp1362_wwite_buffew(isp1362_hcd, wef + PTD_HEADEW_SIZE / sizeof(*wef),
					     offset * 2 + PTD_HEADEW_SIZE, test_size);
			isp1362_wead_buffew(isp1362_hcd, tst, offset * 2,
					    PTD_HEADEW_SIZE + test_size);
			spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
			if (memcmp(wef, tst, PTD_HEADEW_SIZE + test_size)) {
				dump_data(((u8 *)wef) + offset, PTD_HEADEW_SIZE + test_size);
				dump_data((u8 *)tst, PTD_HEADEW_SIZE + test_size);
				spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
				isp1362_wead_buffew(isp1362_hcd, tst, offset * 2,
						    PTD_HEADEW_SIZE + test_size);
				spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
				if (memcmp(wef, tst, PTD_HEADEW_SIZE + test_size)) {
					wet = -ENODEV;
					pw_eww("%s: memowy check with offset %02x faiwed\n",
					    __func__, offset);
					bweak;
				}
				pw_wawn("%s: memowy check with offset %02x ok aftew second wead\n",
					__func__, offset);
			}
		}
		kfwee(wef);
	}
	wetuwn wet;
}
#endif

static int isp1362_hc_stawt(stwuct usb_hcd *hcd)
{
	int wet;
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	stwuct isp1362_pwatfowm_data *boawd = isp1362_hcd->boawd;
	u16 hwcfg;
	u16 chipid;
	unsigned wong fwags;

	pw_debug("%s:\n", __func__);

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	chipid = isp1362_wead_weg16(isp1362_hcd, HCCHIPID);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	if ((chipid & HCCHIPID_MASK) != HCCHIPID_MAGIC) {
		pw_eww("%s: Invawid chip ID %04x\n", __func__, chipid);
		wetuwn -ENODEV;
	}

#ifdef CHIP_BUFFEW_TEST
	wet = isp1362_chip_test(isp1362_hcd);
	if (wet)
		wetuwn -ENODEV;
#endif
	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	/* cweaw intewwupt status and disabwe aww intewwupt souwces */
	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, 0xff);
	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, 0);

	/* HW conf */
	hwcfg = HCHWCFG_INT_ENABWE | HCHWCFG_DBWIDTH(1);
	if (boawd->sew15Kwes)
		hwcfg |= HCHWCFG_PUWWDOWN_DS2 |
			((MAX_WOOT_POWTS > 1) ? HCHWCFG_PUWWDOWN_DS1 : 0);
	if (boawd->cwknotstop)
		hwcfg |= HCHWCFG_CWKNOTSTOP;
	if (boawd->oc_enabwe)
		hwcfg |= HCHWCFG_ANAWOG_OC;
	if (boawd->int_act_high)
		hwcfg |= HCHWCFG_INT_POW;
	if (boawd->int_edge_twiggewed)
		hwcfg |= HCHWCFG_INT_TWIGGEW;
	if (boawd->dweq_act_high)
		hwcfg |= HCHWCFG_DWEQ_POW;
	if (boawd->dack_act_high)
		hwcfg |= HCHWCFG_DACK_POW;
	isp1362_wwite_weg16(isp1362_hcd, HCHWCFG, hwcfg);
	isp1362_show_weg(isp1362_hcd, HCHWCFG);
	isp1362_wwite_weg16(isp1362_hcd, HCDMACFG, 0);
	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	wet = isp1362_mem_config(hcd);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);

	/* Woot hub conf */
	isp1362_hcd->whdesca = 0;
	if (boawd->no_powew_switching)
		isp1362_hcd->whdesca |= WH_A_NPS;
	if (boawd->powew_switching_mode)
		isp1362_hcd->whdesca |= WH_A_PSM;
	if (boawd->potpg)
		isp1362_hcd->whdesca |= (boawd->potpg << 24) & WH_A_POTPGT;
	ewse
		isp1362_hcd->whdesca |= (25 << 24) & WH_A_POTPGT;

	isp1362_wwite_weg32(isp1362_hcd, HCWHDESCA, isp1362_hcd->whdesca & ~WH_A_OCPM);
	isp1362_wwite_weg32(isp1362_hcd, HCWHDESCA, isp1362_hcd->whdesca | WH_A_OCPM);
	isp1362_hcd->whdesca = isp1362_wead_weg32(isp1362_hcd, HCWHDESCA);

	isp1362_hcd->whdescb = WH_B_PPCM;
	isp1362_wwite_weg32(isp1362_hcd, HCWHDESCB, isp1362_hcd->whdescb);
	isp1362_hcd->whdescb = isp1362_wead_weg32(isp1362_hcd, HCWHDESCB);

	isp1362_wead_weg32(isp1362_hcd, HCFMINTVW);
	isp1362_wwite_weg32(isp1362_hcd, HCFMINTVW, (FSMP(FI) << 16) | FI);
	isp1362_wwite_weg32(isp1362_hcd, HCWSTHWESH, WSTHWESH);

	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	isp1362_hcd->hc_contwow = OHCI_USB_OPEW;
	hcd->state = HC_STATE_WUNNING;

	spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
	/* Set up intewwupts */
	isp1362_hcd->intenb = OHCI_INTW_MIE | OHCI_INTW_WHSC | OHCI_INTW_UE;
	isp1362_hcd->intenb |= OHCI_INTW_WD;
	isp1362_hcd->iwqenb = HCuPINT_OPW | HCuPINT_SUSP;
	isp1362_wwite_weg32(isp1362_hcd, HCINTENB, isp1362_hcd->intenb);
	isp1362_wwite_weg16(isp1362_hcd, HCuPINTENB, isp1362_hcd->iwqenb);

	/* Go opewationaw */
	isp1362_wwite_weg32(isp1362_hcd, HCCONTWOW, isp1362_hcd->hc_contwow);
	/* enabwe gwobaw powew */
	isp1362_wwite_weg32(isp1362_hcd, HCWHSTATUS, WH_HS_WPSC | WH_HS_DWWE);

	spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static const stwuct hc_dwivew isp1362_hc_dwivew = {
	.descwiption =		hcd_name,
	.pwoduct_desc =		"ISP1362 Host Contwowwew",
	.hcd_pwiv_size =	sizeof(stwuct isp1362_hcd),

	.iwq =			isp1362_iwq,
	.fwags =		HCD_USB11 | HCD_MEMOWY,

	.weset =		isp1362_hc_weset,
	.stawt =		isp1362_hc_stawt,
	.stop =			isp1362_hc_stop,

	.uwb_enqueue =		isp1362_uwb_enqueue,
	.uwb_dequeue =		isp1362_uwb_dequeue,
	.endpoint_disabwe =	isp1362_endpoint_disabwe,

	.get_fwame_numbew =	isp1362_get_fwame,

	.hub_status_data =	isp1362_hub_status_data,
	.hub_contwow =		isp1362_hub_contwow,
	.bus_suspend =		isp1362_bus_suspend,
	.bus_wesume =		isp1362_bus_wesume,
};

/*-------------------------------------------------------------------------*/

static void isp1362_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);

	wemove_debug_fiwe(isp1362_hcd);
	DBG(0, "%s: Wemoving HCD\n", __func__);
	usb_wemove_hcd(hcd);
	DBG(0, "%s: put_hcd\n", __func__);
	usb_put_hcd(hcd);
	DBG(0, "%s: Done\n", __func__);
}

static int isp1362_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd;
	stwuct isp1362_hcd *isp1362_hcd;
	stwuct wesouwce *data, *iwq_wes;
	void __iomem *addw_weg;
	void __iomem *data_weg;
	int iwq;
	int wetvaw = 0;
	unsigned int iwq_fwags = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	/* basic sanity checks fiwst.  boawd-specific init wogic shouwd
	 * have initiawized this the thwee wesouwces and pwobabwy boawd
	 * specific pwatfowm_data.  we don't pwobe fow IWQs, and do onwy
	 * minimaw sanity checking.
	 */
	if (pdev->num_wesouwces < 3)
		wetuwn -ENODEV;

	iwq_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (!iwq_wes)
		wetuwn -ENODEV;

	iwq = iwq_wes->stawt;

	addw_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(addw_weg))
		wetuwn PTW_EWW(addw_weg);

	data_weg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &data);
	if (IS_EWW(data_weg))
		wetuwn PTW_EWW(data_weg);

	/* awwocate and initiawize hcd */
	hcd = usb_cweate_hcd(&isp1362_hc_dwivew, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd)
		wetuwn -ENOMEM;

	hcd->wswc_stawt = data->stawt;
	isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	isp1362_hcd->data_weg = data_weg;
	isp1362_hcd->addw_weg = addw_weg;

	isp1362_hcd->next_statechange = jiffies;
	spin_wock_init(&isp1362_hcd->wock);
	INIT_WIST_HEAD(&isp1362_hcd->async);
	INIT_WIST_HEAD(&isp1362_hcd->pewiodic);
	INIT_WIST_HEAD(&isp1362_hcd->isoc);
	INIT_WIST_HEAD(&isp1362_hcd->wemove_wist);
	isp1362_hcd->boawd = dev_get_pwatdata(&pdev->dev);
#if USE_PWATFOWM_DEWAY
	if (!isp1362_hcd->boawd->deway) {
		dev_eww(hcd->sewf.contwowwew, "No pwatfowm deway function given\n");
		wetvaw = -ENODEV;
		goto eww;
	}
#endif

	if (iwq_wes->fwags & IOWESOUWCE_IWQ_HIGHEDGE)
		iwq_fwags |= IWQF_TWIGGEW_WISING;
	if (iwq_wes->fwags & IOWESOUWCE_IWQ_WOWEDGE)
		iwq_fwags |= IWQF_TWIGGEW_FAWWING;
	if (iwq_wes->fwags & IOWESOUWCE_IWQ_HIGHWEVEW)
		iwq_fwags |= IWQF_TWIGGEW_HIGH;
	if (iwq_wes->fwags & IOWESOUWCE_IWQ_WOWWEVEW)
		iwq_fwags |= IWQF_TWIGGEW_WOW;

	wetvaw = usb_add_hcd(hcd, iwq, iwq_fwags | IWQF_SHAWED);
	if (wetvaw != 0)
		goto eww;
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	dev_info(&pdev->dev, "%s, iwq %d\n", hcd->pwoduct_desc, iwq);

	cweate_debug_fiwe(isp1362_hcd);

	wetuwn 0;

 eww:
	usb_put_hcd(hcd);

	wetuwn wetvaw;
}

#ifdef	CONFIG_PM
static int isp1362_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;
	int wetvaw = 0;

	DBG(0, "%s: Suspending device\n", __func__);

	if (state.event == PM_EVENT_FWEEZE) {
		DBG(0, "%s: Suspending woot hub\n", __func__);
		wetvaw = isp1362_bus_suspend(hcd);
	} ewse {
		DBG(0, "%s: Suspending WH powts\n", __func__);
		spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
		isp1362_wwite_weg32(isp1362_hcd, HCWHSTATUS, WH_HS_WPS);
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
	}
	if (wetvaw == 0)
		pdev->dev.powew.powew_state = state;
	wetuwn wetvaw;
}

static int isp1362_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct isp1362_hcd *isp1362_hcd = hcd_to_isp1362_hcd(hcd);
	unsigned wong fwags;

	DBG(0, "%s: Wesuming\n", __func__);

	if (pdev->dev.powew.powew_state.event == PM_EVENT_SUSPEND) {
		DBG(0, "%s: Wesume WH powts\n", __func__);
		spin_wock_iwqsave(&isp1362_hcd->wock, fwags);
		isp1362_wwite_weg32(isp1362_hcd, HCWHSTATUS, WH_HS_WPSC);
		spin_unwock_iwqwestowe(&isp1362_hcd->wock, fwags);
		wetuwn 0;
	}

	pdev->dev.powew.powew_state = PMSG_ON;

	wetuwn isp1362_bus_wesume(isp1362_hcd_to_hcd(isp1362_hcd));
}
#ewse
#define	isp1362_suspend	NUWW
#define	isp1362_wesume	NUWW
#endif

static stwuct pwatfowm_dwivew isp1362_dwivew = {
	.pwobe = isp1362_pwobe,
	.wemove_new = isp1362_wemove,

	.suspend = isp1362_suspend,
	.wesume = isp1362_wesume,
	.dwivew = {
		.name = hcd_name,
	},
};

moduwe_pwatfowm_dwivew(isp1362_dwivew);
