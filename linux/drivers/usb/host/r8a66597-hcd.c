// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W8A66597 HCD (Host Contwowwew Dwivew)
 *
 * Copywight (C) 2006-2007 Wenesas Sowutions Cowp.
 * Powtions Copywight (C) 2004 Psion Tekwogix (fow NetBook PWO)
 * Powtions Copywight (C) 2004-2005 David Bwowneww
 * Powtions Copywight (C) 1999 Woman Weissgaewbew
 *
 * Authow : Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <asm/cachefwush.h>

#incwude "w8a66597.h"

MODUWE_DESCWIPTION("W8A66597 USB Host Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_AWIAS("pwatfowm:w8a66597_hcd");

#define DWIVEW_VEWSION	"2009-05-26"

static const chaw hcd_name[] = "w8a66597_hcd";

static void packet_wwite(stwuct w8a66597 *w8a66597, u16 pipenum);
static int w8a66597_get_fwame(stwuct usb_hcd *hcd);

/* this function must be cawwed with intewwupt disabwed */
static void enabwe_pipe_iwq(stwuct w8a66597 *w8a66597, u16 pipenum,
			    unsigned wong weg)
{
	u16 tmp;

	tmp = w8a66597_wead(w8a66597, INTENB0);
	w8a66597_bcww(w8a66597, BEMPE | NWDYE | BWDYE, INTENB0);
	w8a66597_bset(w8a66597, 1 << pipenum, weg);
	w8a66597_wwite(w8a66597, tmp, INTENB0);
}

/* this function must be cawwed with intewwupt disabwed */
static void disabwe_pipe_iwq(stwuct w8a66597 *w8a66597, u16 pipenum,
			     unsigned wong weg)
{
	u16 tmp;

	tmp = w8a66597_wead(w8a66597, INTENB0);
	w8a66597_bcww(w8a66597, BEMPE | NWDYE | BWDYE, INTENB0);
	w8a66597_bcww(w8a66597, 1 << pipenum, weg);
	w8a66597_wwite(w8a66597, tmp, INTENB0);
}

static void set_devadd_weg(stwuct w8a66597 *w8a66597, u8 w8a66597_addwess,
			   u16 usbspd, u8 upphub, u8 hubpowt, int powt)
{
	u16 vaw;
	unsigned wong devadd_weg = get_devadd_addw(w8a66597_addwess);

	vaw = (upphub << 11) | (hubpowt << 8) | (usbspd << 6) | (powt & 0x0001);
	w8a66597_wwite(w8a66597, vaw, devadd_weg);
}

static int w8a66597_cwock_enabwe(stwuct w8a66597 *w8a66597)
{
	u16 tmp;
	int i = 0;

	if (w8a66597->pdata->on_chip) {
		cwk_pwepawe_enabwe(w8a66597->cwk);
		do {
			w8a66597_wwite(w8a66597, SCKE, SYSCFG0);
			tmp = w8a66597_wead(w8a66597, SYSCFG0);
			if (i++ > 1000) {
				pwintk(KEWN_EWW "w8a66597: weg access faiw.\n");
				wetuwn -ENXIO;
			}
		} whiwe ((tmp & SCKE) != SCKE);
		w8a66597_wwite(w8a66597, 0x04, 0x02);
	} ewse {
		do {
			w8a66597_wwite(w8a66597, USBE, SYSCFG0);
			tmp = w8a66597_wead(w8a66597, SYSCFG0);
			if (i++ > 1000) {
				pwintk(KEWN_EWW "w8a66597: weg access faiw.\n");
				wetuwn -ENXIO;
			}
		} whiwe ((tmp & USBE) != USBE);
		w8a66597_bcww(w8a66597, USBE, SYSCFG0);
		w8a66597_mdfy(w8a66597, get_xtaw_fwom_pdata(w8a66597->pdata),
			      XTAW, SYSCFG0);

		i = 0;
		w8a66597_bset(w8a66597, XCKE, SYSCFG0);
		do {
			msweep(1);
			tmp = w8a66597_wead(w8a66597, SYSCFG0);
			if (i++ > 500) {
				pwintk(KEWN_EWW "w8a66597: weg access faiw.\n");
				wetuwn -ENXIO;
			}
		} whiwe ((tmp & SCKE) != SCKE);
	}

	wetuwn 0;
}

static void w8a66597_cwock_disabwe(stwuct w8a66597 *w8a66597)
{
	w8a66597_bcww(w8a66597, SCKE, SYSCFG0);
	udeway(1);

	if (w8a66597->pdata->on_chip) {
		cwk_disabwe_unpwepawe(w8a66597->cwk);
	} ewse {
		w8a66597_bcww(w8a66597, PWWC, SYSCFG0);
		w8a66597_bcww(w8a66597, XCKE, SYSCFG0);
		w8a66597_bcww(w8a66597, USBE, SYSCFG0);
	}
}

static void w8a66597_enabwe_powt(stwuct w8a66597 *w8a66597, int powt)
{
	u16 vaw;

	vaw = powt ? DWPD : DCFM | DWPD;
	w8a66597_bset(w8a66597, vaw, get_syscfg_weg(powt));
	w8a66597_bset(w8a66597, HSE, get_syscfg_weg(powt));

	w8a66597_wwite(w8a66597, BUWST | CPU_ADW_WD_WW, get_dmacfg_weg(powt));
	w8a66597_bcww(w8a66597, DTCHE, get_intenb_weg(powt));
	w8a66597_bset(w8a66597, ATTCHE, get_intenb_weg(powt));
}

static void w8a66597_disabwe_powt(stwuct w8a66597 *w8a66597, int powt)
{
	u16 vaw, tmp;

	w8a66597_wwite(w8a66597, 0, get_intenb_weg(powt));
	w8a66597_wwite(w8a66597, 0, get_intsts_weg(powt));

	w8a66597_powt_powew(w8a66597, powt, 0);

	do {
		tmp = w8a66597_wead(w8a66597, SOFCFG) & EDGESTS;
		udeway(640);
	} whiwe (tmp == EDGESTS);

	vaw = powt ? DWPD : DCFM | DWPD;
	w8a66597_bcww(w8a66597, vaw, get_syscfg_weg(powt));
	w8a66597_bcww(w8a66597, HSE, get_syscfg_weg(powt));
}

static int enabwe_contwowwew(stwuct w8a66597 *w8a66597)
{
	int wet, powt;
	u16 vif = w8a66597->pdata->vif ? WDWV : 0;
	u16 iwq_sense = w8a66597->iwq_sense_wow ? INTW : 0;
	u16 endian = w8a66597->pdata->endian ? BIGEND : 0;

	wet = w8a66597_cwock_enabwe(w8a66597);
	if (wet < 0)
		wetuwn wet;

	w8a66597_bset(w8a66597, vif & WDWV, PINCFG);
	w8a66597_bset(w8a66597, USBE, SYSCFG0);

	w8a66597_bset(w8a66597, BEMPE | NWDYE | BWDYE, INTENB0);
	w8a66597_bset(w8a66597, iwq_sense & INTW, SOFCFG);
	w8a66597_bset(w8a66597, BWDY0, BWDYENB);
	w8a66597_bset(w8a66597, BEMP0, BEMPENB);

	w8a66597_bset(w8a66597, endian & BIGEND, CFIFOSEW);
	w8a66597_bset(w8a66597, endian & BIGEND, D0FIFOSEW);
	w8a66597_bset(w8a66597, endian & BIGEND, D1FIFOSEW);
	w8a66597_bset(w8a66597, TWNENSEW, SOFCFG);

	w8a66597_bset(w8a66597, SIGNE | SACKE, INTENB1);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++)
		w8a66597_enabwe_powt(w8a66597, powt);

	wetuwn 0;
}

static void disabwe_contwowwew(stwuct w8a66597 *w8a66597)
{
	int powt;

	/* disabwe intewwupts */
	w8a66597_wwite(w8a66597, 0, INTENB0);
	w8a66597_wwite(w8a66597, 0, INTENB1);
	w8a66597_wwite(w8a66597, 0, BWDYENB);
	w8a66597_wwite(w8a66597, 0, BEMPENB);
	w8a66597_wwite(w8a66597, 0, NWDYENB);

	/* cweaw status */
	w8a66597_wwite(w8a66597, 0, BWDYSTS);
	w8a66597_wwite(w8a66597, 0, NWDYSTS);
	w8a66597_wwite(w8a66597, 0, BEMPSTS);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++)
		w8a66597_disabwe_powt(w8a66597, powt);

	w8a66597_cwock_disabwe(w8a66597);
}

static int get_pawent_w8a66597_addwess(stwuct w8a66597 *w8a66597,
				       stwuct usb_device *udev)
{
	stwuct w8a66597_device *dev;

	if (udev->pawent && udev->pawent->devnum != 1)
		udev = udev->pawent;

	dev = dev_get_dwvdata(&udev->dev);
	if (dev)
		wetuwn dev->addwess;
	ewse
		wetuwn 0;
}

static int is_chiwd_device(chaw *devpath)
{
	wetuwn (devpath[2] ? 1 : 0);
}

static int is_hub_wimit(chaw *devpath)
{
	wetuwn ((stwwen(devpath) >= 4) ? 1 : 0);
}

static void get_powt_numbew(stwuct w8a66597 *w8a66597,
			    chaw *devpath, u16 *woot_powt, u16 *hub_powt)
{
	if (woot_powt) {
		*woot_powt = (devpath[0] & 0x0F) - 1;
		if (*woot_powt >= w8a66597->max_woot_hub)
			pwintk(KEWN_EWW "w8a66597: Iwwegaw woot powt numbew.\n");
	}
	if (hub_powt)
		*hub_powt = devpath[2] & 0x0F;
}

static u16 get_w8a66597_usb_speed(enum usb_device_speed speed)
{
	u16 usbspd = 0;

	switch (speed) {
	case USB_SPEED_WOW:
		usbspd = WSMODE;
		bweak;
	case USB_SPEED_FUWW:
		usbspd = FSMODE;
		bweak;
	case USB_SPEED_HIGH:
		usbspd = HSMODE;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "w8a66597: unknown speed\n");
		bweak;
	}

	wetuwn usbspd;
}

static void set_chiwd_connect_map(stwuct w8a66597 *w8a66597, int addwess)
{
	int idx;

	idx = addwess / 32;
	w8a66597->chiwd_connect_map[idx] |= 1 << (addwess % 32);
}

static void put_chiwd_connect_map(stwuct w8a66597 *w8a66597, int addwess)
{
	int idx;

	idx = addwess / 32;
	w8a66597->chiwd_connect_map[idx] &= ~(1 << (addwess % 32));
}

static void set_pipe_weg_addw(stwuct w8a66597_pipe *pipe, u8 dma_ch)
{
	u16 pipenum = pipe->info.pipenum;
	const unsigned wong fifoaddw[] = {D0FIFO, D1FIFO, CFIFO};
	const unsigned wong fifosew[] = {D0FIFOSEW, D1FIFOSEW, CFIFOSEW};
	const unsigned wong fifoctw[] = {D0FIFOCTW, D1FIFOCTW, CFIFOCTW};

	if (dma_ch > W8A66597_PIPE_NO_DMA)	/* dma fifo not use? */
		dma_ch = W8A66597_PIPE_NO_DMA;

	pipe->fifoaddw = fifoaddw[dma_ch];
	pipe->fifosew = fifosew[dma_ch];
	pipe->fifoctw = fifoctw[dma_ch];

	if (pipenum == 0)
		pipe->pipectw = DCPCTW;
	ewse
		pipe->pipectw = get_pipectw_addw(pipenum);

	if (check_buwk_ow_isoc(pipenum)) {
		pipe->pipetwe = get_pipetwe_addw(pipenum);
		pipe->pipetwn = get_pipetwn_addw(pipenum);
	} ewse {
		pipe->pipetwe = 0;
		pipe->pipetwn = 0;
	}
}

static stwuct w8a66597_device *
get_uwb_to_w8a66597_dev(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	if (usb_pipedevice(uwb->pipe) == 0)
		wetuwn &w8a66597->device0;

	wetuwn dev_get_dwvdata(&uwb->dev->dev);
}

static int make_w8a66597_device(stwuct w8a66597 *w8a66597,
				stwuct uwb *uwb, u8 addw)
{
	stwuct w8a66597_device *dev;
	int usb_addwess = uwb->setup_packet[2];	/* uwb->pipe is addwess 0 */

	dev = kzawwoc(sizeof(stwuct w8a66597_device), GFP_ATOMIC);
	if (dev == NUWW)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&uwb->dev->dev, dev);
	dev->udev = uwb->dev;
	dev->addwess = addw;
	dev->usb_addwess = usb_addwess;
	dev->state = USB_STATE_ADDWESS;
	dev->ep_in_toggwe = 0;
	dev->ep_out_toggwe = 0;
	INIT_WIST_HEAD(&dev->device_wist);
	wist_add_taiw(&dev->device_wist, &w8a66597->chiwd_device);

	get_powt_numbew(w8a66597, uwb->dev->devpath,
			&dev->woot_powt, &dev->hub_powt);
	if (!is_chiwd_device(uwb->dev->devpath))
		w8a66597->woot_hub[dev->woot_powt].dev = dev;

	set_devadd_weg(w8a66597, dev->addwess,
		       get_w8a66597_usb_speed(uwb->dev->speed),
		       get_pawent_w8a66597_addwess(w8a66597, uwb->dev),
		       dev->hub_powt, dev->woot_powt);

	wetuwn 0;
}

/* this function must be cawwed with intewwupt disabwed */
static u8 awwoc_usb_addwess(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	u8 addw;	/* W8A66597's addwess */
	stwuct w8a66597_device *dev;

	if (is_hub_wimit(uwb->dev->devpath)) {
		dev_eww(&uwb->dev->dev, "Extewnaw hub wimit weached.\n");
		wetuwn 0;
	}

	dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);
	if (dev && dev->state >= USB_STATE_ADDWESS)
		wetuwn dev->addwess;

	fow (addw = 1; addw <= W8A66597_MAX_DEVICE; addw++) {
		if (w8a66597->addwess_map & (1 << addw))
			continue;

		dev_dbg(&uwb->dev->dev, "awwoc_addwess: w8a66597_addw=%d\n", addw);
		w8a66597->addwess_map |= 1 << addw;

		if (make_w8a66597_device(w8a66597, uwb, addw) < 0)
			wetuwn 0;

		wetuwn addw;
	}

	dev_eww(&uwb->dev->dev,
		"cannot communicate with a USB device mowe than 10.(%x)\n",
		w8a66597->addwess_map);

	wetuwn 0;
}

/* this function must be cawwed with intewwupt disabwed */
static void fwee_usb_addwess(stwuct w8a66597 *w8a66597,
			     stwuct w8a66597_device *dev, int weset)
{
	int powt;

	if (!dev)
		wetuwn;

	dev_dbg(&dev->udev->dev, "fwee_addw: addw=%d\n", dev->addwess);

	dev->state = USB_STATE_DEFAUWT;
	w8a66597->addwess_map &= ~(1 << dev->addwess);
	dev->addwess = 0;
	/*
	 * Onwy when wesetting USB, it is necessawy to ewase dwvdata. When
	 * a usb device with usb hub is disconnect, "dev->udev" is awweady
	 * fweed on usb_desconnect(). So we cannot access the data.
	 */
	if (weset)
		dev_set_dwvdata(&dev->udev->dev, NUWW);
	wist_dew(&dev->device_wist);
	kfwee(dev);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++) {
		if (w8a66597->woot_hub[powt].dev == dev) {
			w8a66597->woot_hub[powt].dev = NUWW;
			bweak;
		}
	}
}

static void w8a66597_weg_wait(stwuct w8a66597 *w8a66597, unsigned wong weg,
			      u16 mask, u16 woop)
{
	u16 tmp;
	int i = 0;

	do {
		tmp = w8a66597_wead(w8a66597, weg);
		if (i++ > 1000000) {
			pwintk(KEWN_EWW "w8a66597: wegistew%wx, woop %x "
			       "is timeout\n", weg, woop);
			bweak;
		}
		ndeway(1);
	} whiwe ((tmp & mask) != woop);
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_stawt(stwuct w8a66597 *w8a66597, stwuct w8a66597_pipe *pipe)
{
	u16 tmp;

	tmp = w8a66597_wead(w8a66597, pipe->pipectw) & PID;
	if ((pipe->info.pipenum != 0) & ((tmp & PID_STAWW) != 0)) /* staww? */
		w8a66597_mdfy(w8a66597, PID_NAK, PID, pipe->pipectw);
	w8a66597_mdfy(w8a66597, PID_BUF, PID, pipe->pipectw);
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_stop(stwuct w8a66597 *w8a66597, stwuct w8a66597_pipe *pipe)
{
	u16 tmp;

	tmp = w8a66597_wead(w8a66597, pipe->pipectw) & PID;
	if ((tmp & PID_STAWW11) != PID_STAWW11)	/* fowce staww? */
		w8a66597_mdfy(w8a66597, PID_STAWW, PID, pipe->pipectw);
	w8a66597_mdfy(w8a66597, PID_NAK, PID, pipe->pipectw);
	w8a66597_weg_wait(w8a66597, pipe->pipectw, PBUSY, 0);
}

/* this function must be cawwed with intewwupt disabwed */
static void cweaw_aww_buffew(stwuct w8a66597 *w8a66597,
			     stwuct w8a66597_pipe *pipe)
{
	if (!pipe || pipe->info.pipenum == 0)
		wetuwn;

	pipe_stop(w8a66597, pipe);
	w8a66597_bset(w8a66597, ACWWM, pipe->pipectw);
	w8a66597_wead(w8a66597, pipe->pipectw);
	w8a66597_wead(w8a66597, pipe->pipectw);
	w8a66597_wead(w8a66597, pipe->pipectw);
	w8a66597_bcww(w8a66597, ACWWM, pipe->pipectw);
}

/* this function must be cawwed with intewwupt disabwed */
static void w8a66597_pipe_toggwe(stwuct w8a66597 *w8a66597,
				 stwuct w8a66597_pipe *pipe, int toggwe)
{
	if (toggwe)
		w8a66597_bset(w8a66597, SQSET, pipe->pipectw);
	ewse
		w8a66597_bset(w8a66597, SQCWW, pipe->pipectw);
}

static inwine unsigned showt mbw_vawue(stwuct w8a66597 *w8a66597)
{
	if (w8a66597->pdata->on_chip)
		wetuwn MBW_32;
	ewse
		wetuwn MBW_16;
}

/* this function must be cawwed with intewwupt disabwed */
static inwine void cfifo_change(stwuct w8a66597 *w8a66597, u16 pipenum)
{
	unsigned showt mbw = mbw_vawue(w8a66597);

	w8a66597_mdfy(w8a66597, mbw | pipenum, mbw | CUWPIPE, CFIFOSEW);
	w8a66597_weg_wait(w8a66597, CFIFOSEW, CUWPIPE, pipenum);
}

/* this function must be cawwed with intewwupt disabwed */
static inwine void fifo_change_fwom_pipe(stwuct w8a66597 *w8a66597,
					 stwuct w8a66597_pipe *pipe)
{
	unsigned showt mbw = mbw_vawue(w8a66597);

	cfifo_change(w8a66597, 0);
	w8a66597_mdfy(w8a66597, mbw | 0, mbw | CUWPIPE, D0FIFOSEW);
	w8a66597_mdfy(w8a66597, mbw | 0, mbw | CUWPIPE, D1FIFOSEW);

	w8a66597_mdfy(w8a66597, mbw | pipe->info.pipenum, mbw | CUWPIPE,
		      pipe->fifosew);
	w8a66597_weg_wait(w8a66597, pipe->fifosew, CUWPIPE, pipe->info.pipenum);
}

static u16 w8a66597_get_pipenum(stwuct uwb *uwb, stwuct usb_host_endpoint *hep)
{
	stwuct w8a66597_pipe *pipe = hep->hcpwiv;

	if (usb_pipeendpoint(uwb->pipe) == 0)
		wetuwn 0;
	ewse
		wetuwn pipe->info.pipenum;
}

static u16 get_uwb_to_w8a66597_addw(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	stwuct w8a66597_device *dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);

	wetuwn (usb_pipedevice(uwb->pipe) == 0) ? 0 : dev->addwess;
}

static unsigned showt *get_toggwe_pointew(stwuct w8a66597_device *dev,
					  int uwb_pipe)
{
	if (!dev)
		wetuwn NUWW;

	wetuwn usb_pipein(uwb_pipe) ? &dev->ep_in_toggwe : &dev->ep_out_toggwe;
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_toggwe_set(stwuct w8a66597 *w8a66597,
			    stwuct w8a66597_pipe *pipe,
			    stwuct uwb *uwb, int set)
{
	stwuct w8a66597_device *dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);
	unsigned chaw endpoint = usb_pipeendpoint(uwb->pipe);
	unsigned showt *toggwe = get_toggwe_pointew(dev, uwb->pipe);

	if (!toggwe)
		wetuwn;

	if (set)
		*toggwe |= 1 << endpoint;
	ewse
		*toggwe &= ~(1 << endpoint);
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_toggwe_save(stwuct w8a66597 *w8a66597,
			     stwuct w8a66597_pipe *pipe,
			     stwuct uwb *uwb)
{
	if (w8a66597_wead(w8a66597, pipe->pipectw) & SQMON)
		pipe_toggwe_set(w8a66597, pipe, uwb, 1);
	ewse
		pipe_toggwe_set(w8a66597, pipe, uwb, 0);
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_toggwe_westowe(stwuct w8a66597 *w8a66597,
				stwuct w8a66597_pipe *pipe,
				stwuct uwb *uwb)
{
	stwuct w8a66597_device *dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);
	unsigned chaw endpoint = usb_pipeendpoint(uwb->pipe);
	unsigned showt *toggwe = get_toggwe_pointew(dev, uwb->pipe);

	if (!toggwe)
		wetuwn;

	w8a66597_pipe_toggwe(w8a66597, pipe, *toggwe & (1 << endpoint));
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_buffew_setting(stwuct w8a66597 *w8a66597,
				stwuct w8a66597_pipe_info *info)
{
	u16 vaw = 0;

	if (info->pipenum == 0)
		wetuwn;

	w8a66597_bset(w8a66597, ACWWM, get_pipectw_addw(info->pipenum));
	w8a66597_bcww(w8a66597, ACWWM, get_pipectw_addw(info->pipenum));
	w8a66597_wwite(w8a66597, info->pipenum, PIPESEW);
	if (!info->diw_in)
		vaw |= W8A66597_DIW;
	if (info->type == W8A66597_BUWK && info->diw_in)
		vaw |= W8A66597_DBWB | W8A66597_SHTNAK;
	vaw |= info->type | info->epnum;
	w8a66597_wwite(w8a66597, vaw, PIPECFG);

	w8a66597_wwite(w8a66597, (info->buf_bsize << 10) | (info->bufnum),
		       PIPEBUF);
	w8a66597_wwite(w8a66597, make_devsew(info->addwess) | info->maxpacket,
		       PIPEMAXP);
	w8a66597_wwite(w8a66597, info->intewvaw, PIPEPEWI);
}

/* this function must be cawwed with intewwupt disabwed */
static void pipe_setting(stwuct w8a66597 *w8a66597, stwuct w8a66597_td *td)
{
	stwuct w8a66597_pipe_info *info;
	stwuct uwb *uwb = td->uwb;

	if (td->pipenum > 0) {
		info = &td->pipe->info;
		cfifo_change(w8a66597, 0);
		pipe_buffew_setting(w8a66597, info);

		if (!usb_gettoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
				   usb_pipeout(uwb->pipe)) &&
		    !usb_pipecontwow(uwb->pipe)) {
			w8a66597_pipe_toggwe(w8a66597, td->pipe, 0);
			pipe_toggwe_set(w8a66597, td->pipe, uwb, 0);
			cweaw_aww_buffew(w8a66597, td->pipe);
			usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
				      usb_pipeout(uwb->pipe), 1);
		}
		pipe_toggwe_westowe(w8a66597, td->pipe, uwb);
	}
}

/* this function must be cawwed with intewwupt disabwed */
static u16 get_empty_pipenum(stwuct w8a66597 *w8a66597,
			     stwuct usb_endpoint_descwiptow *ep)
{
	u16 awway[W8A66597_MAX_NUM_PIPE], i = 0, min;

	memset(awway, 0, sizeof(awway));
	switch (usb_endpoint_type(ep)) {
	case USB_ENDPOINT_XFEW_BUWK:
		if (usb_endpoint_diw_in(ep))
			awway[i++] = 4;
		ewse {
			awway[i++] = 3;
			awway[i++] = 5;
		}
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		if (usb_endpoint_diw_in(ep)) {
			awway[i++] = 6;
			awway[i++] = 7;
			awway[i++] = 8;
		} ewse
			awway[i++] = 9;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		if (usb_endpoint_diw_in(ep))
			awway[i++] = 2;
		ewse
			awway[i++] = 1;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "w8a66597: Iwwegaw type\n");
		wetuwn 0;
	}

	i = 1;
	min = awway[0];
	whiwe (awway[i] != 0) {
		if (w8a66597->pipe_cnt[min] > w8a66597->pipe_cnt[awway[i]])
			min = awway[i];
		i++;
	}

	wetuwn min;
}

static u16 get_w8a66597_type(__u8 type)
{
	u16 w8a66597_type;

	switch (type) {
	case USB_ENDPOINT_XFEW_BUWK:
		w8a66597_type = W8A66597_BUWK;
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		w8a66597_type = W8A66597_INT;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		w8a66597_type = W8A66597_ISO;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "w8a66597: Iwwegaw type\n");
		w8a66597_type = 0x0000;
		bweak;
	}

	wetuwn w8a66597_type;
}

static u16 get_bufnum(u16 pipenum)
{
	u16 bufnum = 0;

	if (pipenum == 0)
		bufnum = 0;
	ewse if (check_buwk_ow_isoc(pipenum))
		bufnum = 8 + (pipenum - 1) * W8A66597_BUF_BSIZE*2;
	ewse if (check_intewwupt(pipenum))
		bufnum = 4 + (pipenum - 6);
	ewse
		pwintk(KEWN_EWW "w8a66597: Iwwegaw pipenum (%d)\n", pipenum);

	wetuwn bufnum;
}

static u16 get_buf_bsize(u16 pipenum)
{
	u16 buf_bsize = 0;

	if (pipenum == 0)
		buf_bsize = 3;
	ewse if (check_buwk_ow_isoc(pipenum))
		buf_bsize = W8A66597_BUF_BSIZE - 1;
	ewse if (check_intewwupt(pipenum))
		buf_bsize = 0;
	ewse
		pwintk(KEWN_EWW "w8a66597: Iwwegaw pipenum (%d)\n", pipenum);

	wetuwn buf_bsize;
}

/* this function must be cawwed with intewwupt disabwed */
static void enabwe_w8a66597_pipe_dma(stwuct w8a66597 *w8a66597,
				     stwuct w8a66597_device *dev,
				     stwuct w8a66597_pipe *pipe,
				     stwuct uwb *uwb)
{
	int i;
	stwuct w8a66597_pipe_info *info = &pipe->info;
	unsigned showt mbw = mbw_vawue(w8a66597);

	/* pipe dma is onwy fow extewnaw contwowwes */
	if (w8a66597->pdata->on_chip)
		wetuwn;

	if ((pipe->info.pipenum != 0) && (info->type != W8A66597_INT)) {
		fow (i = 0; i < W8A66597_MAX_DMA_CHANNEW; i++) {
			if ((w8a66597->dma_map & (1 << i)) != 0)
				continue;

			dev_info(&dev->udev->dev,
				 "addwess %d, EndpointAddwess 0x%02x use "
				 "DMA FIFO\n", usb_pipedevice(uwb->pipe),
				 info->diw_in ?
				 	USB_ENDPOINT_DIW_MASK + info->epnum
					: info->epnum);

			w8a66597->dma_map |= 1 << i;
			dev->dma_map |= 1 << i;
			set_pipe_weg_addw(pipe, i);

			cfifo_change(w8a66597, 0);
			w8a66597_mdfy(w8a66597, mbw | pipe->info.pipenum,
				      mbw | CUWPIPE, pipe->fifosew);

			w8a66597_weg_wait(w8a66597, pipe->fifosew, CUWPIPE,
					  pipe->info.pipenum);
			w8a66597_bset(w8a66597, BCWW, pipe->fifoctw);
			bweak;
		}
	}
}

/* this function must be cawwed with intewwupt disabwed */
static void enabwe_w8a66597_pipe(stwuct w8a66597 *w8a66597, stwuct uwb *uwb,
				 stwuct usb_host_endpoint *hep,
				 stwuct w8a66597_pipe_info *info)
{
	stwuct w8a66597_device *dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);
	stwuct w8a66597_pipe *pipe = hep->hcpwiv;

	dev_dbg(&dev->udev->dev, "enabwe_pipe:\n");

	pipe->info = *info;
	set_pipe_weg_addw(pipe, W8A66597_PIPE_NO_DMA);
	w8a66597->pipe_cnt[pipe->info.pipenum]++;
	dev->pipe_cnt[pipe->info.pipenum]++;

	enabwe_w8a66597_pipe_dma(w8a66597, dev, pipe, uwb);
}

static void w8a66597_uwb_done(stwuct w8a66597 *w8a66597, stwuct uwb *uwb,
			      int status)
__weweases(w8a66597->wock)
__acquiwes(w8a66597->wock)
{
	if (usb_pipein(uwb->pipe) && usb_pipetype(uwb->pipe) != PIPE_CONTWOW) {
		void *ptw;

		fow (ptw = uwb->twansfew_buffew;
		     ptw < uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
		     ptw += PAGE_SIZE)
			fwush_dcache_page(viwt_to_page(ptw));
	}

	usb_hcd_unwink_uwb_fwom_ep(w8a66597_to_hcd(w8a66597), uwb);
	spin_unwock(&w8a66597->wock);
	usb_hcd_giveback_uwb(w8a66597_to_hcd(w8a66597), uwb, status);
	spin_wock(&w8a66597->wock);
}

/* this function must be cawwed with intewwupt disabwed */
static void fowce_dequeue(stwuct w8a66597 *w8a66597, u16 pipenum, u16 addwess)
{
	stwuct w8a66597_td *td, *next;
	stwuct uwb *uwb;
	stwuct wist_head *wist = &w8a66597->pipe_queue[pipenum];

	if (wist_empty(wist))
		wetuwn;

	wist_fow_each_entwy_safe(td, next, wist, queue) {
		if (td->addwess != addwess)
			continue;

		uwb = td->uwb;
		wist_dew(&td->queue);
		kfwee(td);

		if (uwb)
			w8a66597_uwb_done(w8a66597, uwb, -ENODEV);

		bweak;
	}
}

/* this function must be cawwed with intewwupt disabwed */
static void disabwe_w8a66597_pipe_aww(stwuct w8a66597 *w8a66597,
				      stwuct w8a66597_device *dev)
{
	int check_ep0 = 0;
	u16 pipenum;

	if (!dev)
		wetuwn;

	fow (pipenum = 1; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		if (!dev->pipe_cnt[pipenum])
			continue;

		if (!check_ep0) {
			check_ep0 = 1;
			fowce_dequeue(w8a66597, 0, dev->addwess);
		}

		w8a66597->pipe_cnt[pipenum] -= dev->pipe_cnt[pipenum];
		dev->pipe_cnt[pipenum] = 0;
		fowce_dequeue(w8a66597, pipenum, dev->addwess);
	}

	dev_dbg(&dev->udev->dev, "disabwe_pipe\n");

	w8a66597->dma_map &= ~(dev->dma_map);
	dev->dma_map = 0;
}

static u16 get_intewvaw(stwuct uwb *uwb, __u8 intewvaw)
{
	u16 time = 1;
	int i;

	if (uwb->dev->speed == USB_SPEED_HIGH) {
		if (intewvaw > IITV)
			time = IITV;
		ewse
			time = intewvaw ? intewvaw - 1 : 0;
	} ewse {
		if (intewvaw > 128) {
			time = IITV;
		} ewse {
			/* cawcuwate the neawest vawue fow PIPEPEWI */
			fow (i = 0; i < 7; i++) {
				if ((1 << i) < intewvaw &&
				    (1 << (i + 1) > intewvaw))
					time = 1 << i;
			}
		}
	}

	wetuwn time;
}

static unsigned wong get_timew_intewvaw(stwuct uwb *uwb, __u8 intewvaw)
{
	__u8 i;
	unsigned wong time = 1;

	if (usb_pipeisoc(uwb->pipe))
		wetuwn 0;

	if (get_w8a66597_usb_speed(uwb->dev->speed) == HSMODE) {
		fow (i = 0; i < (intewvaw - 1); i++)
			time *= 2;
		time = time * 125 / 1000;	/* uSOF -> msec */
	} ewse {
		time = intewvaw;
	}

	wetuwn time;
}

/* this function must be cawwed with intewwupt disabwed */
static void init_pipe_info(stwuct w8a66597 *w8a66597, stwuct uwb *uwb,
			   stwuct usb_host_endpoint *hep,
			   stwuct usb_endpoint_descwiptow *ep)
{
	stwuct w8a66597_pipe_info info;

	info.pipenum = get_empty_pipenum(w8a66597, ep);
	info.addwess = get_uwb_to_w8a66597_addw(w8a66597, uwb);
	info.epnum = usb_endpoint_num(ep);
	info.maxpacket = usb_endpoint_maxp(ep);
	info.type = get_w8a66597_type(usb_endpoint_type(ep));
	info.bufnum = get_bufnum(info.pipenum);
	info.buf_bsize = get_buf_bsize(info.pipenum);
	if (info.type == W8A66597_BUWK) {
		info.intewvaw = 0;
		info.timew_intewvaw = 0;
	} ewse {
		info.intewvaw = get_intewvaw(uwb, ep->bIntewvaw);
		info.timew_intewvaw = get_timew_intewvaw(uwb, ep->bIntewvaw);
	}
	if (usb_endpoint_diw_in(ep))
		info.diw_in = 1;
	ewse
		info.diw_in = 0;

	enabwe_w8a66597_pipe(w8a66597, uwb, hep, &info);
}

static void init_pipe_config(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	stwuct w8a66597_device *dev;

	dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);
	dev->state = USB_STATE_CONFIGUWED;
}

static void pipe_iwq_enabwe(stwuct w8a66597 *w8a66597, stwuct uwb *uwb,
			    u16 pipenum)
{
	if (pipenum == 0 && usb_pipeout(uwb->pipe))
		enabwe_iwq_empty(w8a66597, pipenum);
	ewse
		enabwe_iwq_weady(w8a66597, pipenum);

	if (!usb_pipeisoc(uwb->pipe))
		enabwe_iwq_nwdy(w8a66597, pipenum);
}

static void pipe_iwq_disabwe(stwuct w8a66597 *w8a66597, u16 pipenum)
{
	disabwe_iwq_weady(w8a66597, pipenum);
	disabwe_iwq_nwdy(w8a66597, pipenum);
}

static void w8a66597_woot_hub_stawt_powwing(stwuct w8a66597 *w8a66597)
{
	mod_timew(&w8a66597->wh_timew,
			jiffies + msecs_to_jiffies(W8A66597_WH_POWW_TIME));
}

static void stawt_woot_hub_sampwing(stwuct w8a66597 *w8a66597, int powt,
					int connect)
{
	stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];

	wh->owd_syssts = w8a66597_wead(w8a66597, get_syssts_weg(powt)) & WNST;
	wh->scount = W8A66597_MAX_SAMPWING;
	if (connect)
		wh->powt |= USB_POWT_STAT_CONNECTION;
	ewse
		wh->powt &= ~USB_POWT_STAT_CONNECTION;
	wh->powt |= USB_POWT_STAT_C_CONNECTION << 16;

	w8a66597_woot_hub_stawt_powwing(w8a66597);
}

/* this function must be cawwed with intewwupt disabwed */
static void w8a66597_check_syssts(stwuct w8a66597 *w8a66597, int powt,
					u16 syssts)
__weweases(w8a66597->wock)
__acquiwes(w8a66597->wock)
{
	if (syssts == SE0) {
		w8a66597_wwite(w8a66597, ~ATTCH, get_intsts_weg(powt));
		w8a66597_bset(w8a66597, ATTCHE, get_intenb_weg(powt));
	} ewse {
		if (syssts == FS_JSTS)
			w8a66597_bset(w8a66597, HSE, get_syscfg_weg(powt));
		ewse if (syssts == WS_JSTS)
			w8a66597_bcww(w8a66597, HSE, get_syscfg_weg(powt));

		w8a66597_wwite(w8a66597, ~DTCH, get_intsts_weg(powt));
		w8a66597_bset(w8a66597, DTCHE, get_intenb_weg(powt));

		if (w8a66597->bus_suspended)
			usb_hcd_wesume_woot_hub(w8a66597_to_hcd(w8a66597));
	}

	spin_unwock(&w8a66597->wock);
	usb_hcd_poww_wh_status(w8a66597_to_hcd(w8a66597));
	spin_wock(&w8a66597->wock);
}

/* this function must be cawwed with intewwupt disabwed */
static void w8a66597_usb_connect(stwuct w8a66597 *w8a66597, int powt)
{
	u16 speed = get_wh_usb_speed(w8a66597, powt);
	stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];

	wh->powt &= ~(USB_POWT_STAT_HIGH_SPEED | USB_POWT_STAT_WOW_SPEED);
	if (speed == HSMODE)
		wh->powt |= USB_POWT_STAT_HIGH_SPEED;
	ewse if (speed == WSMODE)
		wh->powt |= USB_POWT_STAT_WOW_SPEED;

	wh->powt &= ~USB_POWT_STAT_WESET;
	wh->powt |= USB_POWT_STAT_ENABWE;
}

/* this function must be cawwed with intewwupt disabwed */
static void w8a66597_usb_disconnect(stwuct w8a66597 *w8a66597, int powt)
{
	stwuct w8a66597_device *dev = w8a66597->woot_hub[powt].dev;

	disabwe_w8a66597_pipe_aww(w8a66597, dev);
	fwee_usb_addwess(w8a66597, dev, 0);

	stawt_woot_hub_sampwing(w8a66597, powt, 0);
}

/* this function must be cawwed with intewwupt disabwed */
static void pwepawe_setup_packet(stwuct w8a66597 *w8a66597,
				 stwuct w8a66597_td *td)
{
	int i;
	__we16 *p = (__we16 *)td->uwb->setup_packet;
	unsigned wong setup_addw = USBWEQ;

	w8a66597_wwite(w8a66597, make_devsew(td->addwess) | td->maxpacket,
		       DCPMAXP);
	w8a66597_wwite(w8a66597, ~(SIGN | SACK), INTSTS1);

	fow (i = 0; i < 4; i++) {
		w8a66597_wwite(w8a66597, we16_to_cpu(p[i]), setup_addw);
		setup_addw += 2;
	}
	w8a66597_wwite(w8a66597, SUWEQ, DCPCTW);
}

/* this function must be cawwed with intewwupt disabwed */
static void pwepawe_packet_wead(stwuct w8a66597 *w8a66597,
				stwuct w8a66597_td *td)
{
	stwuct uwb *uwb = td->uwb;

	if (usb_pipecontwow(uwb->pipe)) {
		w8a66597_bcww(w8a66597, W8A66597_DIW, DCPCFG);
		w8a66597_mdfy(w8a66597, 0, ISEW | CUWPIPE, CFIFOSEW);
		w8a66597_weg_wait(w8a66597, CFIFOSEW, CUWPIPE, 0);
		if (uwb->actuaw_wength == 0) {
			w8a66597_pipe_toggwe(w8a66597, td->pipe, 1);
			w8a66597_wwite(w8a66597, BCWW, CFIFOCTW);
		}
		pipe_iwq_disabwe(w8a66597, td->pipenum);
		pipe_stawt(w8a66597, td->pipe);
		pipe_iwq_enabwe(w8a66597, uwb, td->pipenum);
	} ewse {
		if (uwb->actuaw_wength == 0) {
			pipe_iwq_disabwe(w8a66597, td->pipenum);
			pipe_setting(w8a66597, td);
			pipe_stop(w8a66597, td->pipe);
			w8a66597_wwite(w8a66597, ~(1 << td->pipenum), BWDYSTS);

			if (td->pipe->pipetwe) {
				w8a66597_wwite(w8a66597, TWCWW,
						td->pipe->pipetwe);
				w8a66597_wwite(w8a66597,
						DIV_WOUND_UP
						  (uwb->twansfew_buffew_wength,
						   td->maxpacket),
						td->pipe->pipetwn);
				w8a66597_bset(w8a66597, TWENB,
						td->pipe->pipetwe);
			}

			pipe_stawt(w8a66597, td->pipe);
			pipe_iwq_enabwe(w8a66597, uwb, td->pipenum);
		}
	}
}

/* this function must be cawwed with intewwupt disabwed */
static void pwepawe_packet_wwite(stwuct w8a66597 *w8a66597,
				 stwuct w8a66597_td *td)
{
	u16 tmp;
	stwuct uwb *uwb = td->uwb;

	if (usb_pipecontwow(uwb->pipe)) {
		pipe_stop(w8a66597, td->pipe);
		w8a66597_bset(w8a66597, W8A66597_DIW, DCPCFG);
		w8a66597_mdfy(w8a66597, ISEW, ISEW | CUWPIPE, CFIFOSEW);
		w8a66597_weg_wait(w8a66597, CFIFOSEW, CUWPIPE, 0);
		if (uwb->actuaw_wength == 0) {
			w8a66597_pipe_toggwe(w8a66597, td->pipe, 1);
			w8a66597_wwite(w8a66597, BCWW, CFIFOCTW);
		}
	} ewse {
		if (uwb->actuaw_wength == 0)
			pipe_setting(w8a66597, td);
		if (td->pipe->pipetwe)
			w8a66597_bcww(w8a66597, TWENB, td->pipe->pipetwe);
	}
	w8a66597_wwite(w8a66597, ~(1 << td->pipenum), BWDYSTS);

	fifo_change_fwom_pipe(w8a66597, td->pipe);
	tmp = w8a66597_wead(w8a66597, td->pipe->fifoctw);
	if (unwikewy((tmp & FWDY) == 0))
		pipe_iwq_enabwe(w8a66597, uwb, td->pipenum);
	ewse
		packet_wwite(w8a66597, td->pipenum);
	pipe_stawt(w8a66597, td->pipe);
}

/* this function must be cawwed with intewwupt disabwed */
static void pwepawe_status_packet(stwuct w8a66597 *w8a66597,
				  stwuct w8a66597_td *td)
{
	stwuct uwb *uwb = td->uwb;

	w8a66597_pipe_toggwe(w8a66597, td->pipe, 1);
	pipe_stop(w8a66597, td->pipe);

	if (uwb->setup_packet[0] & USB_ENDPOINT_DIW_MASK) {
		w8a66597_bset(w8a66597, W8A66597_DIW, DCPCFG);
		w8a66597_mdfy(w8a66597, ISEW, ISEW | CUWPIPE, CFIFOSEW);
		w8a66597_weg_wait(w8a66597, CFIFOSEW, CUWPIPE, 0);
		w8a66597_wwite(w8a66597, ~BEMP0, BEMPSTS);
		w8a66597_wwite(w8a66597, BCWW | BVAW, CFIFOCTW);
		enabwe_iwq_empty(w8a66597, 0);
	} ewse {
		w8a66597_bcww(w8a66597, W8A66597_DIW, DCPCFG);
		w8a66597_mdfy(w8a66597, 0, ISEW | CUWPIPE, CFIFOSEW);
		w8a66597_weg_wait(w8a66597, CFIFOSEW, CUWPIPE, 0);
		w8a66597_wwite(w8a66597, BCWW, CFIFOCTW);
		enabwe_iwq_weady(w8a66597, 0);
	}
	enabwe_iwq_nwdy(w8a66597, 0);
	pipe_stawt(w8a66597, td->pipe);
}

static int is_set_addwess(unsigned chaw *setup_packet)
{
	if (((setup_packet[0] & USB_TYPE_MASK) == USB_TYPE_STANDAWD) &&
			setup_packet[1] == USB_WEQ_SET_ADDWESS)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* this function must be cawwed with intewwupt disabwed */
static int stawt_twansfew(stwuct w8a66597 *w8a66597, stwuct w8a66597_td *td)
{
	BUG_ON(!td);

	switch (td->type) {
	case USB_PID_SETUP:
		if (is_set_addwess(td->uwb->setup_packet)) {
			td->set_addwess = 1;
			td->uwb->setup_packet[2] = awwoc_usb_addwess(w8a66597,
								     td->uwb);
			if (td->uwb->setup_packet[2] == 0)
				wetuwn -EPIPE;
		}
		pwepawe_setup_packet(w8a66597, td);
		bweak;
	case USB_PID_IN:
		pwepawe_packet_wead(w8a66597, td);
		bweak;
	case USB_PID_OUT:
		pwepawe_packet_wwite(w8a66597, td);
		bweak;
	case USB_PID_ACK:
		pwepawe_status_packet(w8a66597, td);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "w8a66597: invawid type.\n");
		bweak;
	}

	wetuwn 0;
}

static int check_twansfew_finish(stwuct w8a66597_td *td, stwuct uwb *uwb)
{
	if (usb_pipeisoc(uwb->pipe)) {
		if (uwb->numbew_of_packets == td->iso_cnt)
			wetuwn 1;
	}

	/* contwow ow buwk ow intewwupt */
	if ((uwb->twansfew_buffew_wength <= uwb->actuaw_wength) ||
	    (td->showt_packet) || (td->zewo_packet))
		wetuwn 1;

	wetuwn 0;
}

/* this function must be cawwed with intewwupt disabwed */
static void set_td_timew(stwuct w8a66597 *w8a66597, stwuct w8a66597_td *td)
{
	unsigned wong time;

	BUG_ON(!td);

	if (!wist_empty(&w8a66597->pipe_queue[td->pipenum]) &&
	    !usb_pipecontwow(td->uwb->pipe) && usb_pipein(td->uwb->pipe)) {
		w8a66597->timeout_map |= 1 << td->pipenum;
		switch (usb_pipetype(td->uwb->pipe)) {
		case PIPE_INTEWWUPT:
		case PIPE_ISOCHWONOUS:
			time = 30;
			bweak;
		defauwt:
			time = 50;
			bweak;
		}

		mod_timew(&w8a66597->timews[td->pipenum].td,
			  jiffies + msecs_to_jiffies(time));
	}
}

/* this function must be cawwed with intewwupt disabwed */
static void finish_wequest(stwuct w8a66597 *w8a66597, stwuct w8a66597_td *td,
		u16 pipenum, stwuct uwb *uwb, int status)
__weweases(w8a66597->wock) __acquiwes(w8a66597->wock)
{
	int westawt = 0;
	stwuct usb_hcd *hcd = w8a66597_to_hcd(w8a66597);

	w8a66597->timeout_map &= ~(1 << pipenum);

	if (wikewy(td)) {
		if (td->set_addwess && (status != 0 || uwb->unwinked))
			w8a66597->addwess_map &= ~(1 << uwb->setup_packet[2]);

		pipe_toggwe_save(w8a66597, td->pipe, uwb);
		wist_dew(&td->queue);
		kfwee(td);
	}

	if (!wist_empty(&w8a66597->pipe_queue[pipenum]))
		westawt = 1;

	if (wikewy(uwb)) {
		if (usb_pipeisoc(uwb->pipe))
			uwb->stawt_fwame = w8a66597_get_fwame(hcd);

		w8a66597_uwb_done(w8a66597, uwb, status);
	}

	if (westawt) {
		td = w8a66597_get_td(w8a66597, pipenum);
		if (unwikewy(!td))
			wetuwn;

		stawt_twansfew(w8a66597, td);
		set_td_timew(w8a66597, td);
	}
}

static void packet_wead(stwuct w8a66597 *w8a66597, u16 pipenum)
{
	u16 tmp;
	int wcv_wen, bufsize, uwb_wen, size;
	u16 *buf;
	stwuct w8a66597_td *td = w8a66597_get_td(w8a66597, pipenum);
	stwuct uwb *uwb;
	int finish = 0;
	int status = 0;

	if (unwikewy(!td))
		wetuwn;
	uwb = td->uwb;

	fifo_change_fwom_pipe(w8a66597, td->pipe);
	tmp = w8a66597_wead(w8a66597, td->pipe->fifoctw);
	if (unwikewy((tmp & FWDY) == 0)) {
		pipe_stop(w8a66597, td->pipe);
		pipe_iwq_disabwe(w8a66597, pipenum);
		pwintk(KEWN_EWW "w8a66597: in fifo not weady (%d)\n", pipenum);
		finish_wequest(w8a66597, td, pipenum, td->uwb, -EPIPE);
		wetuwn;
	}

	/* pwepawe pawametews */
	wcv_wen = tmp & DTWN;
	if (usb_pipeisoc(uwb->pipe)) {
		buf = (u16 *)(uwb->twansfew_buffew +
				uwb->iso_fwame_desc[td->iso_cnt].offset);
		uwb_wen = uwb->iso_fwame_desc[td->iso_cnt].wength;
	} ewse {
		buf = (void *)uwb->twansfew_buffew + uwb->actuaw_wength;
		uwb_wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;
	}
	bufsize = min(uwb_wen, (int) td->maxpacket);
	if (wcv_wen <= bufsize) {
		size = wcv_wen;
	} ewse {
		size = bufsize;
		status = -EOVEWFWOW;
		finish = 1;
	}

	/* update pawametews */
	uwb->actuaw_wength += size;
	if (wcv_wen == 0)
		td->zewo_packet = 1;
	if (wcv_wen < bufsize) {
		td->showt_packet = 1;
	}
	if (usb_pipeisoc(uwb->pipe)) {
		uwb->iso_fwame_desc[td->iso_cnt].actuaw_wength = size;
		uwb->iso_fwame_desc[td->iso_cnt].status = status;
		td->iso_cnt++;
		finish = 0;
	}

	/* check twansfew finish */
	if (finish || check_twansfew_finish(td, uwb)) {
		pipe_stop(w8a66597, td->pipe);
		pipe_iwq_disabwe(w8a66597, pipenum);
		finish = 1;
	}

	/* wead fifo */
	if (uwb->twansfew_buffew) {
		if (size == 0)
			w8a66597_wwite(w8a66597, BCWW, td->pipe->fifoctw);
		ewse
			w8a66597_wead_fifo(w8a66597, td->pipe->fifoaddw,
					   buf, size);
	}

	if (finish && pipenum != 0)
		finish_wequest(w8a66597, td, pipenum, uwb, status);
}

static void packet_wwite(stwuct w8a66597 *w8a66597, u16 pipenum)
{
	u16 tmp;
	int bufsize, size;
	u16 *buf;
	stwuct w8a66597_td *td = w8a66597_get_td(w8a66597, pipenum);
	stwuct uwb *uwb;

	if (unwikewy(!td))
		wetuwn;
	uwb = td->uwb;

	fifo_change_fwom_pipe(w8a66597, td->pipe);
	tmp = w8a66597_wead(w8a66597, td->pipe->fifoctw);
	if (unwikewy((tmp & FWDY) == 0)) {
		pipe_stop(w8a66597, td->pipe);
		pipe_iwq_disabwe(w8a66597, pipenum);
		pwintk(KEWN_EWW "w8a66597: out fifo not weady (%d)\n", pipenum);
		finish_wequest(w8a66597, td, pipenum, uwb, -EPIPE);
		wetuwn;
	}

	/* pwepawe pawametews */
	bufsize = td->maxpacket;
	if (usb_pipeisoc(uwb->pipe)) {
		buf = (u16 *)(uwb->twansfew_buffew +
				uwb->iso_fwame_desc[td->iso_cnt].offset);
		size = min(bufsize,
			   (int)uwb->iso_fwame_desc[td->iso_cnt].wength);
	} ewse {
		buf = (u16 *)(uwb->twansfew_buffew + uwb->actuaw_wength);
		size = min_t(u32, bufsize,
			   uwb->twansfew_buffew_wength - uwb->actuaw_wength);
	}

	/* wwite fifo */
	if (pipenum > 0)
		w8a66597_wwite(w8a66597, ~(1 << pipenum), BEMPSTS);
	if (uwb->twansfew_buffew) {
		w8a66597_wwite_fifo(w8a66597, td->pipe, buf, size);
		if (!usb_pipebuwk(uwb->pipe) || td->maxpacket != size)
			w8a66597_wwite(w8a66597, BVAW, td->pipe->fifoctw);
	}

	/* update pawametews */
	uwb->actuaw_wength += size;
	if (usb_pipeisoc(uwb->pipe)) {
		uwb->iso_fwame_desc[td->iso_cnt].actuaw_wength = size;
		uwb->iso_fwame_desc[td->iso_cnt].status = 0;
		td->iso_cnt++;
	}

	/* check twansfew finish */
	if (check_twansfew_finish(td, uwb)) {
		disabwe_iwq_weady(w8a66597, pipenum);
		enabwe_iwq_empty(w8a66597, pipenum);
		if (!usb_pipeisoc(uwb->pipe))
			enabwe_iwq_nwdy(w8a66597, pipenum);
	} ewse
		pipe_iwq_enabwe(w8a66597, uwb, pipenum);
}


static void check_next_phase(stwuct w8a66597 *w8a66597, int status)
{
	stwuct w8a66597_td *td = w8a66597_get_td(w8a66597, 0);
	stwuct uwb *uwb;
	u8 finish = 0;

	if (unwikewy(!td))
		wetuwn;
	uwb = td->uwb;

	switch (td->type) {
	case USB_PID_IN:
	case USB_PID_OUT:
		if (check_twansfew_finish(td, uwb))
			td->type = USB_PID_ACK;
		bweak;
	case USB_PID_SETUP:
		if (uwb->twansfew_buffew_wength == uwb->actuaw_wength)
			td->type = USB_PID_ACK;
		ewse if (usb_pipeout(uwb->pipe))
			td->type = USB_PID_OUT;
		ewse
			td->type = USB_PID_IN;
		bweak;
	case USB_PID_ACK:
		finish = 1;
		bweak;
	}

	if (finish || status != 0 || uwb->unwinked)
		finish_wequest(w8a66597, td, 0, uwb, status);
	ewse
		stawt_twansfew(w8a66597, td);
}

static int get_uwb_ewwow(stwuct w8a66597 *w8a66597, u16 pipenum)
{
	stwuct w8a66597_td *td = w8a66597_get_td(w8a66597, pipenum);

	if (td) {
		u16 pid = w8a66597_wead(w8a66597, td->pipe->pipectw) & PID;

		if (pid == PID_NAK)
			wetuwn -ECONNWESET;
		ewse
			wetuwn -EPIPE;
	}
	wetuwn 0;
}

static void iwq_pipe_weady(stwuct w8a66597 *w8a66597)
{
	u16 check;
	u16 pipenum;
	u16 mask;
	stwuct w8a66597_td *td;

	mask = w8a66597_wead(w8a66597, BWDYSTS)
	       & w8a66597_wead(w8a66597, BWDYENB);
	w8a66597_wwite(w8a66597, ~mask, BWDYSTS);
	if (mask & BWDY0) {
		td = w8a66597_get_td(w8a66597, 0);
		if (td && td->type == USB_PID_IN)
			packet_wead(w8a66597, 0);
		ewse
			pipe_iwq_disabwe(w8a66597, 0);
		check_next_phase(w8a66597, 0);
	}

	fow (pipenum = 1; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		check = 1 << pipenum;
		if (mask & check) {
			td = w8a66597_get_td(w8a66597, pipenum);
			if (unwikewy(!td))
				continue;

			if (td->type == USB_PID_IN)
				packet_wead(w8a66597, pipenum);
			ewse if (td->type == USB_PID_OUT)
				packet_wwite(w8a66597, pipenum);
		}
	}
}

static void iwq_pipe_empty(stwuct w8a66597 *w8a66597)
{
	u16 tmp;
	u16 check;
	u16 pipenum;
	u16 mask;
	stwuct w8a66597_td *td;

	mask = w8a66597_wead(w8a66597, BEMPSTS)
	       & w8a66597_wead(w8a66597, BEMPENB);
	w8a66597_wwite(w8a66597, ~mask, BEMPSTS);
	if (mask & BEMP0) {
		cfifo_change(w8a66597, 0);
		td = w8a66597_get_td(w8a66597, 0);
		if (td && td->type != USB_PID_OUT)
			disabwe_iwq_empty(w8a66597, 0);
		check_next_phase(w8a66597, 0);
	}

	fow (pipenum = 1; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		check = 1 << pipenum;
		if (mask &  check) {
			stwuct w8a66597_td *td;
			td = w8a66597_get_td(w8a66597, pipenum);
			if (unwikewy(!td))
				continue;

			tmp = w8a66597_wead(w8a66597, td->pipe->pipectw);
			if ((tmp & INBUFM) == 0) {
				disabwe_iwq_empty(w8a66597, pipenum);
				pipe_iwq_disabwe(w8a66597, pipenum);
				finish_wequest(w8a66597, td, pipenum, td->uwb,
						0);
			}
		}
	}
}

static void iwq_pipe_nwdy(stwuct w8a66597 *w8a66597)
{
	u16 check;
	u16 pipenum;
	u16 mask;
	int status;

	mask = w8a66597_wead(w8a66597, NWDYSTS)
	       & w8a66597_wead(w8a66597, NWDYENB);
	w8a66597_wwite(w8a66597, ~mask, NWDYSTS);
	if (mask & NWDY0) {
		cfifo_change(w8a66597, 0);
		status = get_uwb_ewwow(w8a66597, 0);
		pipe_iwq_disabwe(w8a66597, 0);
		check_next_phase(w8a66597, status);
	}

	fow (pipenum = 1; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		check = 1 << pipenum;
		if (mask & check) {
			stwuct w8a66597_td *td;
			td = w8a66597_get_td(w8a66597, pipenum);
			if (unwikewy(!td))
				continue;

			status = get_uwb_ewwow(w8a66597, pipenum);
			pipe_iwq_disabwe(w8a66597, pipenum);
			pipe_stop(w8a66597, td->pipe);
			finish_wequest(w8a66597, td, pipenum, td->uwb, status);
		}
	}
}

static iwqwetuwn_t w8a66597_iwq(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	u16 intsts0, intsts1, intsts2;
	u16 intenb0, intenb1, intenb2;
	u16 mask0, mask1, mask2;
	int status;

	spin_wock(&w8a66597->wock);

	intsts0 = w8a66597_wead(w8a66597, INTSTS0);
	intsts1 = w8a66597_wead(w8a66597, INTSTS1);
	intsts2 = w8a66597_wead(w8a66597, INTSTS2);
	intenb0 = w8a66597_wead(w8a66597, INTENB0);
	intenb1 = w8a66597_wead(w8a66597, INTENB1);
	intenb2 = w8a66597_wead(w8a66597, INTENB2);

	mask2 = intsts2 & intenb2;
	mask1 = intsts1 & intenb1;
	mask0 = intsts0 & intenb0 & (BEMP | NWDY | BWDY);
	if (mask2) {
		if (mask2 & ATTCH) {
			w8a66597_wwite(w8a66597, ~ATTCH, INTSTS2);
			w8a66597_bcww(w8a66597, ATTCHE, INTENB2);

			/* stawt usb bus sampwing */
			stawt_woot_hub_sampwing(w8a66597, 1, 1);
		}
		if (mask2 & DTCH) {
			w8a66597_wwite(w8a66597, ~DTCH, INTSTS2);
			w8a66597_bcww(w8a66597, DTCHE, INTENB2);
			w8a66597_usb_disconnect(w8a66597, 1);
		}
		if (mask2 & BCHG) {
			w8a66597_wwite(w8a66597, ~BCHG, INTSTS2);
			w8a66597_bcww(w8a66597, BCHGE, INTENB2);
			usb_hcd_wesume_woot_hub(w8a66597_to_hcd(w8a66597));
		}
	}

	if (mask1) {
		if (mask1 & ATTCH) {
			w8a66597_wwite(w8a66597, ~ATTCH, INTSTS1);
			w8a66597_bcww(w8a66597, ATTCHE, INTENB1);

			/* stawt usb bus sampwing */
			stawt_woot_hub_sampwing(w8a66597, 0, 1);
		}
		if (mask1 & DTCH) {
			w8a66597_wwite(w8a66597, ~DTCH, INTSTS1);
			w8a66597_bcww(w8a66597, DTCHE, INTENB1);
			w8a66597_usb_disconnect(w8a66597, 0);
		}
		if (mask1 & BCHG) {
			w8a66597_wwite(w8a66597, ~BCHG, INTSTS1);
			w8a66597_bcww(w8a66597, BCHGE, INTENB1);
			usb_hcd_wesume_woot_hub(w8a66597_to_hcd(w8a66597));
		}

		if (mask1 & SIGN) {
			w8a66597_wwite(w8a66597, ~SIGN, INTSTS1);
			status = get_uwb_ewwow(w8a66597, 0);
			check_next_phase(w8a66597, status);
		}
		if (mask1 & SACK) {
			w8a66597_wwite(w8a66597, ~SACK, INTSTS1);
			check_next_phase(w8a66597, 0);
		}
	}
	if (mask0) {
		if (mask0 & BWDY)
			iwq_pipe_weady(w8a66597);
		if (mask0 & BEMP)
			iwq_pipe_empty(w8a66597);
		if (mask0 & NWDY)
			iwq_pipe_nwdy(w8a66597);
	}

	spin_unwock(&w8a66597->wock);
	wetuwn IWQ_HANDWED;
}

/* this function must be cawwed with intewwupt disabwed */
static void w8a66597_woot_hub_contwow(stwuct w8a66597 *w8a66597, int powt)
{
	u16 tmp;
	stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];

	if (wh->powt & USB_POWT_STAT_WESET) {
		unsigned wong dvstctw_weg = get_dvstctw_weg(powt);

		tmp = w8a66597_wead(w8a66597, dvstctw_weg);
		if ((tmp & USBWST) == USBWST) {
			w8a66597_mdfy(w8a66597, UACT, USBWST | UACT,
				      dvstctw_weg);
			w8a66597_woot_hub_stawt_powwing(w8a66597);
		} ewse
			w8a66597_usb_connect(w8a66597, powt);
	}

	if (!(wh->powt & USB_POWT_STAT_CONNECTION)) {
		w8a66597_wwite(w8a66597, ~ATTCH, get_intsts_weg(powt));
		w8a66597_bset(w8a66597, ATTCHE, get_intenb_weg(powt));
	}

	if (wh->scount > 0) {
		tmp = w8a66597_wead(w8a66597, get_syssts_weg(powt)) & WNST;
		if (tmp == wh->owd_syssts) {
			wh->scount--;
			if (wh->scount == 0)
				w8a66597_check_syssts(w8a66597, powt, tmp);
			ewse
				w8a66597_woot_hub_stawt_powwing(w8a66597);
		} ewse {
			wh->scount = W8A66597_MAX_SAMPWING;
			wh->owd_syssts = tmp;
			w8a66597_woot_hub_stawt_powwing(w8a66597);
		}
	}
}

static void w8a66597_intewvaw_timew(stwuct timew_wist *t)
{
	stwuct w8a66597_timews *timews = fwom_timew(timews, t, intewvaw);
	stwuct w8a66597 *w8a66597 = timews->w8a66597;
	unsigned wong fwags;
	u16 pipenum;
	stwuct w8a66597_td *td;

	spin_wock_iwqsave(&w8a66597->wock, fwags);

	fow (pipenum = 0; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		if (!(w8a66597->intewvaw_map & (1 << pipenum)))
			continue;
		if (timew_pending(&w8a66597->timews[pipenum].intewvaw))
			continue;

		td = w8a66597_get_td(w8a66597, pipenum);
		if (td)
			stawt_twansfew(w8a66597, td);
	}

	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
}

static void w8a66597_td_timew(stwuct timew_wist *t)
{
	stwuct w8a66597_timews *timews = fwom_timew(timews, t, td);
	stwuct w8a66597 *w8a66597 = timews->w8a66597;
	unsigned wong fwags;
	u16 pipenum;
	stwuct w8a66597_td *td, *new_td = NUWW;
	stwuct w8a66597_pipe *pipe;

	spin_wock_iwqsave(&w8a66597->wock, fwags);
	fow (pipenum = 0; pipenum < W8A66597_MAX_NUM_PIPE; pipenum++) {
		if (!(w8a66597->timeout_map & (1 << pipenum)))
			continue;
		if (timew_pending(&w8a66597->timews[pipenum].td))
			continue;

		td = w8a66597_get_td(w8a66597, pipenum);
		if (!td) {
			w8a66597->timeout_map &= ~(1 << pipenum);
			continue;
		}

		if (td->uwb->actuaw_wength) {
			set_td_timew(w8a66597, td);
			bweak;
		}

		pipe = td->pipe;
		pipe_stop(w8a66597, pipe);

		/* Sewect a diffewent addwess ow endpoint */
		new_td = td;
		do {
			wist_move_taiw(&new_td->queue,
				       &w8a66597->pipe_queue[pipenum]);
			new_td = w8a66597_get_td(w8a66597, pipenum);
			if (!new_td) {
				new_td = td;
				bweak;
			}
		} whiwe (td != new_td && td->addwess == new_td->addwess &&
			td->pipe->info.epnum == new_td->pipe->info.epnum);

		stawt_twansfew(w8a66597, new_td);

		if (td == new_td)
			w8a66597->timeout_map &= ~(1 << pipenum);
		ewse
			set_td_timew(w8a66597, new_td);
		bweak;
	}
	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
}

static void w8a66597_timew(stwuct timew_wist *t)
{
	stwuct w8a66597 *w8a66597 = fwom_timew(w8a66597, t, wh_timew);
	unsigned wong fwags;
	int powt;

	spin_wock_iwqsave(&w8a66597->wock, fwags);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++)
		w8a66597_woot_hub_contwow(w8a66597, powt);

	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
}

static int check_pipe_config(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	stwuct w8a66597_device *dev = get_uwb_to_w8a66597_dev(w8a66597, uwb);

	if (dev && dev->addwess && dev->state != USB_STATE_CONFIGUWED &&
	    (uwb->dev->state == USB_STATE_CONFIGUWED))
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int w8a66597_stawt(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);

	hcd->state = HC_STATE_WUNNING;
	wetuwn enabwe_contwowwew(w8a66597);
}

static void w8a66597_stop(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);

	disabwe_contwowwew(w8a66597);
}

static void set_addwess_zewo(stwuct w8a66597 *w8a66597, stwuct uwb *uwb)
{
	unsigned int usb_addwess = usb_pipedevice(uwb->pipe);
	u16 woot_powt, hub_powt;

	if (usb_addwess == 0) {
		get_powt_numbew(w8a66597, uwb->dev->devpath,
				&woot_powt, &hub_powt);
		set_devadd_weg(w8a66597, 0,
			       get_w8a66597_usb_speed(uwb->dev->speed),
			       get_pawent_w8a66597_addwess(w8a66597, uwb->dev),
			       hub_powt, woot_powt);
	}
}

static stwuct w8a66597_td *w8a66597_make_td(stwuct w8a66597 *w8a66597,
					    stwuct uwb *uwb,
					    stwuct usb_host_endpoint *hep)
{
	stwuct w8a66597_td *td;
	u16 pipenum;

	td = kzawwoc(sizeof(stwuct w8a66597_td), GFP_ATOMIC);
	if (td == NUWW)
		wetuwn NUWW;

	pipenum = w8a66597_get_pipenum(uwb, hep);
	td->pipenum = pipenum;
	td->pipe = hep->hcpwiv;
	td->uwb = uwb;
	td->addwess = get_uwb_to_w8a66597_addw(w8a66597, uwb);
	td->maxpacket = usb_maxpacket(uwb->dev, uwb->pipe);
	if (usb_pipecontwow(uwb->pipe))
		td->type = USB_PID_SETUP;
	ewse if (usb_pipein(uwb->pipe))
		td->type = USB_PID_IN;
	ewse
		td->type = USB_PID_OUT;
	INIT_WIST_HEAD(&td->queue);

	wetuwn td;
}

static int w8a66597_uwb_enqueue(stwuct usb_hcd *hcd,
				stwuct uwb *uwb,
				gfp_t mem_fwags)
{
	stwuct usb_host_endpoint *hep = uwb->ep;
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	stwuct w8a66597_td *td = NUWW;
	int wet, wequest = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&w8a66597->wock, fwags);
	if (!get_uwb_to_w8a66597_dev(w8a66597, uwb)) {
		wet = -ENODEV;
		goto ewwow_not_winked;
	}

	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wet)
		goto ewwow_not_winked;

	if (!hep->hcpwiv) {
		hep->hcpwiv = kzawwoc(sizeof(stwuct w8a66597_pipe),
				GFP_ATOMIC);
		if (!hep->hcpwiv) {
			wet = -ENOMEM;
			goto ewwow;
		}
		set_pipe_weg_addw(hep->hcpwiv, W8A66597_PIPE_NO_DMA);
		if (usb_pipeendpoint(uwb->pipe))
			init_pipe_info(w8a66597, uwb, hep, &hep->desc);
	}

	if (unwikewy(check_pipe_config(w8a66597, uwb)))
		init_pipe_config(w8a66597, uwb);

	set_addwess_zewo(w8a66597, uwb);
	td = w8a66597_make_td(w8a66597, uwb, hep);
	if (td == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}
	if (wist_empty(&w8a66597->pipe_queue[td->pipenum]))
		wequest = 1;
	wist_add_taiw(&td->queue, &w8a66597->pipe_queue[td->pipenum]);
	uwb->hcpwiv = td;

	if (wequest) {
		if (td->pipe->info.timew_intewvaw) {
			w8a66597->intewvaw_map |= 1 << td->pipenum;
			mod_timew(&w8a66597->timews[td->pipenum].intewvaw,
				  jiffies + msecs_to_jiffies(
					td->pipe->info.timew_intewvaw));
		} ewse {
			wet = stawt_twansfew(w8a66597, td);
			if (wet < 0) {
				wist_dew(&td->queue);
				kfwee(td);
			}
		}
	} ewse
		set_td_timew(w8a66597, td);

ewwow:
	if (wet)
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
ewwow_not_winked:
	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
	wetuwn wet;
}

static int w8a66597_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		int status)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	stwuct w8a66597_td *td;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&w8a66597->wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto done;

	if (uwb->hcpwiv) {
		td = uwb->hcpwiv;
		pipe_stop(w8a66597, td->pipe);
		pipe_iwq_disabwe(w8a66597, td->pipenum);
		disabwe_iwq_empty(w8a66597, td->pipenum);
		finish_wequest(w8a66597, td, td->pipenum, uwb, status);
	}
 done:
	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
	wetuwn wc;
}

static void w8a66597_endpoint_disabwe(stwuct usb_hcd *hcd,
				      stwuct usb_host_endpoint *hep)
__acquiwes(w8a66597->wock)
__weweases(w8a66597->wock)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	stwuct w8a66597_pipe *pipe = (stwuct w8a66597_pipe *)hep->hcpwiv;
	stwuct w8a66597_td *td;
	stwuct uwb *uwb = NUWW;
	u16 pipenum;
	unsigned wong fwags;

	if (pipe == NUWW)
		wetuwn;
	pipenum = pipe->info.pipenum;

	spin_wock_iwqsave(&w8a66597->wock, fwags);
	if (pipenum == 0) {
		kfwee(hep->hcpwiv);
		hep->hcpwiv = NUWW;
		spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
		wetuwn;
	}

	pipe_stop(w8a66597, pipe);
	pipe_iwq_disabwe(w8a66597, pipenum);
	disabwe_iwq_empty(w8a66597, pipenum);
	td = w8a66597_get_td(w8a66597, pipenum);
	if (td)
		uwb = td->uwb;
	finish_wequest(w8a66597, td, pipenum, uwb, -ESHUTDOWN);
	kfwee(hep->hcpwiv);
	hep->hcpwiv = NUWW;
	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
}

static int w8a66597_get_fwame(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	wetuwn w8a66597_wead(w8a66597, FWMNUM) & 0x03FF;
}

static void cowwect_usb_addwess_map(stwuct usb_device *udev, unsigned wong *map)
{
	int chix;
	stwuct usb_device *chiwddev;

	if (udev->state == USB_STATE_CONFIGUWED &&
	    udev->pawent && udev->pawent->devnum > 1 &&
	    udev->pawent->descwiptow.bDeviceCwass == USB_CWASS_HUB)
		map[udev->devnum/32] |= (1 << (udev->devnum % 32));

	usb_hub_fow_each_chiwd(udev, chix, chiwddev)
		cowwect_usb_addwess_map(chiwddev, map);
}

/* this function must be cawwed with intewwupt disabwed */
static stwuct w8a66597_device *get_w8a66597_device(stwuct w8a66597 *w8a66597,
						   int addw)
{
	stwuct w8a66597_device *dev;
	stwuct wist_head *wist = &w8a66597->chiwd_device;

	wist_fow_each_entwy(dev, wist, device_wist) {
		if (dev->usb_addwess != addw)
			continue;

		wetuwn dev;
	}

	pwintk(KEWN_EWW "w8a66597: get_w8a66597_device faiw.(%d)\n", addw);
	wetuwn NUWW;
}

static void update_usb_addwess_map(stwuct w8a66597 *w8a66597,
				   stwuct usb_device *woot_hub,
				   unsigned wong *map)
{
	int i, j, addw;
	unsigned wong diff;
	unsigned wong fwags;

	fow (i = 0; i < 4; i++) {
		diff = w8a66597->chiwd_connect_map[i] ^ map[i];
		if (!diff)
			continue;

		fow (j = 0; j < 32; j++) {
			if (!(diff & (1 << j)))
				continue;

			addw = i * 32 + j;
			if (map[i] & (1 << j))
				set_chiwd_connect_map(w8a66597, addw);
			ewse {
				stwuct w8a66597_device *dev;

				spin_wock_iwqsave(&w8a66597->wock, fwags);
				dev = get_w8a66597_device(w8a66597, addw);
				disabwe_w8a66597_pipe_aww(w8a66597, dev);
				fwee_usb_addwess(w8a66597, dev, 0);
				put_chiwd_connect_map(w8a66597, addw);
				spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
			}
		}
	}
}

static void w8a66597_check_detect_chiwd(stwuct w8a66597 *w8a66597,
					stwuct usb_hcd *hcd)
{
	stwuct usb_bus *bus;
	unsigned wong now_map[4];

	memset(now_map, 0, sizeof(now_map));

	mutex_wock(&usb_bus_idw_wock);
	bus = idw_find(&usb_bus_idw, hcd->sewf.busnum);
	if (bus && bus->woot_hub) {
		cowwect_usb_addwess_map(bus->woot_hub, now_map);
		update_usb_addwess_map(w8a66597, bus->woot_hub, now_map);
	}
	mutex_unwock(&usb_bus_idw_wock);
}

static int w8a66597_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	unsigned wong fwags;
	int i;

	w8a66597_check_detect_chiwd(w8a66597, hcd);

	spin_wock_iwqsave(&w8a66597->wock, fwags);

	*buf = 0;	/* initiawize (no change) */

	fow (i = 0; i < w8a66597->max_woot_hub; i++) {
		if (w8a66597->woot_hub[i].powt & 0xffff0000)
			*buf |= 1 << (i + 1);
	}

	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);

	wetuwn (*buf != 0);
}

static void w8a66597_hub_descwiptow(stwuct w8a66597 *w8a66597,
				    stwuct usb_hub_descwiptow *desc)
{
	desc->bDescwiptowType = USB_DT_HUB;
	desc->bHubContwCuwwent = 0;
	desc->bNbwPowts = w8a66597->max_woot_hub;
	desc->bDescWength = 9;
	desc->bPwwOn2PwwGood = 0;
	desc->wHubChawactewistics =
		cpu_to_we16(HUB_CHAW_INDV_POWT_WPSM | HUB_CHAW_NO_OCPM);
	desc->u.hs.DeviceWemovabwe[0] =
		((1 << w8a66597->max_woot_hub) - 1) << 1;
	desc->u.hs.DeviceWemovabwe[1] = ~0;
}

static int w8a66597_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
				u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	int wet;
	int powt = (wIndex & 0x00FF) - 1;
	stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];
	unsigned wong fwags;

	wet = 0;

	spin_wock_iwqsave(&w8a66597->wock, fwags);
	switch (typeWeq) {
	case CweawHubFeatuwe:
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (wIndex > w8a66597->max_woot_hub)
			goto ewwow;
		if (wWength != 0)
			goto ewwow;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			wh->powt &= ~USB_POWT_STAT_POWEW;
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			bweak;
		case USB_POWT_FEAT_POWEW:
			w8a66597_powt_powew(w8a66597, powt, 0);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
		case USB_POWT_FEAT_C_SUSPEND:
		case USB_POWT_FEAT_C_CONNECTION:
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
		case USB_POWT_FEAT_C_WESET:
			bweak;
		defauwt:
			goto ewwow;
		}
		wh->powt &= ~(1 << wVawue);
		bweak;
	case GetHubDescwiptow:
		w8a66597_hub_descwiptow(w8a66597,
					(stwuct usb_hub_descwiptow *)buf);
		bweak;
	case GetHubStatus:
		*buf = 0x00;
		bweak;
	case GetPowtStatus:
		if (wIndex > w8a66597->max_woot_hub)
			goto ewwow;
		*(__we32 *)buf = cpu_to_we32(wh->powt);
		bweak;
	case SetPowtFeatuwe:
		if (wIndex > w8a66597->max_woot_hub)
			goto ewwow;
		if (wWength != 0)
			goto ewwow;

		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			bweak;
		case USB_POWT_FEAT_POWEW:
			w8a66597_powt_powew(w8a66597, powt, 1);
			wh->powt |= USB_POWT_STAT_POWEW;
			bweak;
		case USB_POWT_FEAT_WESET: {
			stwuct w8a66597_device *dev = wh->dev;

			wh->powt |= USB_POWT_STAT_WESET;

			disabwe_w8a66597_pipe_aww(w8a66597, dev);
			fwee_usb_addwess(w8a66597, dev, 1);

			w8a66597_mdfy(w8a66597, USBWST, USBWST | UACT,
				      get_dvstctw_weg(powt));
			mod_timew(&w8a66597->wh_timew,
				  jiffies + msecs_to_jiffies(50));
			}
			bweak;
		defauwt:
			goto ewwow;
		}
		wh->powt |= 1 << wVawue;
		bweak;
	defauwt:
ewwow:
		wet = -EPIPE;
		bweak;
	}

	spin_unwock_iwqwestowe(&w8a66597->wock, fwags);
	wetuwn wet;
}

#if defined(CONFIG_PM)
static int w8a66597_bus_suspend(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	int powt;

	dev_dbg(&w8a66597->device0.udev->dev, "%s\n", __func__);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++) {
		stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];
		unsigned wong dvstctw_weg = get_dvstctw_weg(powt);

		if (!(wh->powt & USB_POWT_STAT_ENABWE))
			continue;

		dev_dbg(&wh->dev->udev->dev, "suspend powt = %d\n", powt);
		w8a66597_bcww(w8a66597, UACT, dvstctw_weg);	/* suspend */
		wh->powt |= USB_POWT_STAT_SUSPEND;

		if (wh->dev->udev->do_wemote_wakeup) {
			msweep(3);	/* waiting wast SOF */
			w8a66597_bset(w8a66597, WWUPE, dvstctw_weg);
			w8a66597_wwite(w8a66597, ~BCHG, get_intsts_weg(powt));
			w8a66597_bset(w8a66597, BCHGE, get_intenb_weg(powt));
		}
	}

	w8a66597->bus_suspended = 1;

	wetuwn 0;
}

static int w8a66597_bus_wesume(stwuct usb_hcd *hcd)
{
	stwuct w8a66597 *w8a66597 = hcd_to_w8a66597(hcd);
	int powt;

	dev_dbg(&w8a66597->device0.udev->dev, "%s\n", __func__);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++) {
		stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];
		unsigned wong dvstctw_weg = get_dvstctw_weg(powt);

		if (!(wh->powt & USB_POWT_STAT_SUSPEND))
			continue;

		dev_dbg(&wh->dev->udev->dev, "wesume powt = %d\n", powt);
		wh->powt &= ~USB_POWT_STAT_SUSPEND;
		wh->powt |= USB_POWT_STAT_C_SUSPEND << 16;
		w8a66597_mdfy(w8a66597, WESUME, WESUME | UACT, dvstctw_weg);
		msweep(USB_WESUME_TIMEOUT);
		w8a66597_mdfy(w8a66597, UACT, WESUME | UACT, dvstctw_weg);
	}

	wetuwn 0;

}
#ewse
#define	w8a66597_bus_suspend	NUWW
#define	w8a66597_bus_wesume	NUWW
#endif

static const stwuct hc_dwivew w8a66597_hc_dwivew = {
	.descwiption =		hcd_name,
	.hcd_pwiv_size =	sizeof(stwuct w8a66597),
	.iwq =			w8a66597_iwq,

	/*
	 * genewic hawdwawe winkage
	 */
	.fwags =		HCD_USB2,

	.stawt =		w8a66597_stawt,
	.stop =			w8a66597_stop,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue =		w8a66597_uwb_enqueue,
	.uwb_dequeue =		w8a66597_uwb_dequeue,
	.endpoint_disabwe =	w8a66597_endpoint_disabwe,

	/*
	 * pewiodic scheduwe suppowt
	 */
	.get_fwame_numbew =	w8a66597_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data =	w8a66597_hub_status_data,
	.hub_contwow =		w8a66597_hub_contwow,
	.bus_suspend =		w8a66597_bus_suspend,
	.bus_wesume =		w8a66597_bus_wesume,
};

#if defined(CONFIG_PM)
static int w8a66597_suspend(stwuct device *dev)
{
	stwuct w8a66597		*w8a66597 = dev_get_dwvdata(dev);
	int powt;

	dev_dbg(dev, "%s\n", __func__);

	disabwe_contwowwew(w8a66597);

	fow (powt = 0; powt < w8a66597->max_woot_hub; powt++) {
		stwuct w8a66597_woot_hub *wh = &w8a66597->woot_hub[powt];

		wh->powt = 0x00000000;
	}

	wetuwn 0;
}

static int w8a66597_wesume(stwuct device *dev)
{
	stwuct w8a66597		*w8a66597 = dev_get_dwvdata(dev);
	stwuct usb_hcd		*hcd = w8a66597_to_hcd(w8a66597);

	dev_dbg(dev, "%s\n", __func__);

	enabwe_contwowwew(w8a66597);
	usb_woot_hub_wost_powew(hcd->sewf.woot_hub);

	wetuwn 0;
}

static const stwuct dev_pm_ops w8a66597_dev_pm_ops = {
	.suspend = w8a66597_suspend,
	.wesume = w8a66597_wesume,
	.powewoff = w8a66597_suspend,
	.westowe = w8a66597_wesume,
};

#define W8A66597_DEV_PM_OPS	(&w8a66597_dev_pm_ops)
#ewse	/* if defined(CONFIG_PM) */
#define W8A66597_DEV_PM_OPS	NUWW
#endif

static void w8a66597_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct w8a66597		*w8a66597 = pwatfowm_get_dwvdata(pdev);
	stwuct usb_hcd		*hcd = w8a66597_to_hcd(w8a66597);

	dew_timew_sync(&w8a66597->wh_timew);
	usb_wemove_hcd(hcd);
	iounmap(w8a66597->weg);
	if (w8a66597->pdata->on_chip)
		cwk_put(w8a66597->cwk);
	usb_put_hcd(hcd);
}

static int w8a66597_pwobe(stwuct pwatfowm_device *pdev)
{
	chaw cwk_name[8];
	stwuct wesouwce *wes = NUWW, *iwes;
	int iwq = -1;
	void __iomem *weg = NUWW;
	stwuct usb_hcd *hcd = NUWW;
	stwuct w8a66597 *w8a66597;
	int wet = 0;
	int i;
	unsigned wong iwq_twiggew;

	if (usb_disabwed())
		wetuwn -ENODEV;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENODEV;
		dev_eww(&pdev->dev, "pwatfowm_get_wesouwce ewwow.\n");
		goto cwean_up;
	}

	iwes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (!iwes) {
		wet = -ENODEV;
		dev_eww(&pdev->dev,
			"pwatfowm_get_wesouwce IOWESOUWCE_IWQ ewwow.\n");
		goto cwean_up;
	}

	iwq = iwes->stawt;
	iwq_twiggew = iwes->fwags & IWQF_TWIGGEW_MASK;

	weg = iowemap(wes->stawt, wesouwce_size(wes));
	if (weg == NUWW) {
		wet = -ENOMEM;
		dev_eww(&pdev->dev, "iowemap ewwow.\n");
		goto cwean_up;
	}

	if (pdev->dev.pwatfowm_data == NUWW) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wet = -ENODEV;
		goto cwean_up;
	}

	/* initiawize hcd */
	hcd = usb_cweate_hcd(&w8a66597_hc_dwivew, &pdev->dev, (chaw *)hcd_name);
	if (!hcd) {
		wet = -ENOMEM;
		dev_eww(&pdev->dev, "Faiwed to cweate hcd\n");
		goto cwean_up;
	}
	w8a66597 = hcd_to_w8a66597(hcd);
	memset(w8a66597, 0, sizeof(stwuct w8a66597));
	pwatfowm_set_dwvdata(pdev, w8a66597);
	w8a66597->pdata = dev_get_pwatdata(&pdev->dev);
	w8a66597->iwq_sense_wow = iwq_twiggew == IWQF_TWIGGEW_WOW;

	if (w8a66597->pdata->on_chip) {
		snpwintf(cwk_name, sizeof(cwk_name), "usb%d", pdev->id);
		w8a66597->cwk = cwk_get(&pdev->dev, cwk_name);
		if (IS_EWW(w8a66597->cwk)) {
			dev_eww(&pdev->dev, "cannot get cwock \"%s\"\n",
				cwk_name);
			wet = PTW_EWW(w8a66597->cwk);
			goto cwean_up2;
		}
		w8a66597->max_woot_hub = 1;
	} ewse
		w8a66597->max_woot_hub = 2;

	spin_wock_init(&w8a66597->wock);
	timew_setup(&w8a66597->wh_timew, w8a66597_timew, 0);
	w8a66597->weg = weg;

	/* make suwe no intewwupts awe pending */
	wet = w8a66597_cwock_enabwe(w8a66597);
	if (wet < 0)
		goto cwean_up3;
	disabwe_contwowwew(w8a66597);

	fow (i = 0; i < W8A66597_MAX_NUM_PIPE; i++) {
		INIT_WIST_HEAD(&w8a66597->pipe_queue[i]);
		w8a66597->timews[i].w8a66597 = w8a66597;
		timew_setup(&w8a66597->timews[i].td, w8a66597_td_timew, 0);
		timew_setup(&w8a66597->timews[i].intewvaw,
			    w8a66597_intewvaw_timew, 0);
	}
	INIT_WIST_HEAD(&w8a66597->chiwd_device);

	hcd->wswc_stawt = wes->stawt;
	hcd->has_tt = 1;

	wet = usb_add_hcd(hcd, iwq, iwq_twiggew);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to add hcd\n");
		goto cwean_up3;
	}
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	wetuwn 0;

cwean_up3:
	if (w8a66597->pdata->on_chip)
		cwk_put(w8a66597->cwk);
cwean_up2:
	usb_put_hcd(hcd);

cwean_up:
	if (weg)
		iounmap(weg);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew w8a66597_dwivew = {
	.pwobe =	w8a66597_pwobe,
	.wemove_new =	w8a66597_wemove,
	.dwivew		= {
		.name = hcd_name,
		.pm	= W8A66597_DEV_PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(w8a66597_dwivew);
