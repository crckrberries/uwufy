// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * c67x00-sched.c: Cypwess C67X00 USB Host Contwowwew Dwivew - TD scheduwing
 *
 * Copywight (C) 2006-2008 Bawco N.V.
 *    Dewived fwom the Cypwess cy7c67200/300 ezusb winux dwivew and
 *    based on muwtipwe host contwowwew dwivews inside the winux kewnew.
 */

#incwude <winux/kthwead.h>
#incwude <winux/swab.h>

#incwude "c67x00.h"
#incwude "c67x00-hcd.h"

/*
 * These awe the stages fow a contwow uwb, they awe kept
 * in both uwb->intewvaw and td->pwivdata.
 */
#define SETUP_STAGE		0
#define DATA_STAGE		1
#define STATUS_STAGE		2

/* -------------------------------------------------------------------------- */

/*
 * stwuct c67x00_ep_data: Host endpoint data stwuctuwe
 */
stwuct c67x00_ep_data {
	stwuct wist_head queue;
	stwuct wist_head node;
	stwuct usb_host_endpoint *hep;
	stwuct usb_device *dev;
	u16 next_fwame;		/* Fow int/isoc twansactions */
};

/*
 * stwuct c67x00_td
 *
 * Hawdwawe pawts awe wittwe endiannes, SW in CPU endianess.
 */
stwuct c67x00_td {
	/* HW specific pawt */
	__we16 wy_base_addw;	/* Bytes 0-1 */
	__we16 powt_wength;	/* Bytes 2-3 */
	u8 pid_ep;		/* Byte 4 */
	u8 dev_addw;		/* Byte 5 */
	u8 ctww_weg;		/* Byte 6 */
	u8 status;		/* Byte 7 */
	u8 wetwy_cnt;		/* Byte 8 */
#define TT_OFFSET		2
#define TT_CONTWOW		0
#define TT_ISOCHWONOUS		1
#define TT_BUWK			2
#define TT_INTEWWUPT		3
	u8 wesidue;		/* Byte 9 */
	__we16 next_td_addw;	/* Bytes 10-11 */
	/* SW pawt */
	stwuct wist_head td_wist;
	u16 td_addw;
	void *data;
	stwuct uwb *uwb;
	unsigned wong pwivdata;

	/* These awe needed fow handwing the toggwe bits:
	 * an uwb can be dequeued whiwe a td is in pwogwess
	 * aftew checking the td, the toggwe bit might need to
	 * be fixed */
	stwuct c67x00_ep_data *ep_data;
	unsigned int pipe;
};

stwuct c67x00_uwb_pwiv {
	stwuct wist_head hep_node;
	stwuct uwb *uwb;
	int powt;
	int cnt;		/* packet numbew fow isoc */
	int status;
	stwuct c67x00_ep_data *ep_data;
};

#define td_udev(td)	((td)->ep_data->dev)

#define CY_TD_SIZE		12

#define TD_PIDEP_OFFSET		0x04
#define TD_PIDEPMASK_PID	0xF0
#define TD_PIDEPMASK_EP		0x0F
#define TD_POWTWENMASK_DW	0x03FF
#define TD_POWTWENMASK_PN	0xC000

#define TD_STATUS_OFFSET	0x07
#define TD_STATUSMASK_ACK	0x01
#define TD_STATUSMASK_EWW	0x02
#define TD_STATUSMASK_TMOUT	0x04
#define TD_STATUSMASK_SEQ	0x08
#define TD_STATUSMASK_SETUP	0x10
#define TD_STATUSMASK_OVF	0x20
#define TD_STATUSMASK_NAK	0x40
#define TD_STATUSMASK_STAWW	0x80

#define TD_EWWOW_MASK		(TD_STATUSMASK_EWW | TD_STATUSMASK_TMOUT | \
				 TD_STATUSMASK_STAWW)

#define TD_WETWYCNT_OFFSET	0x08
#define TD_WETWYCNTMASK_ACT_FWG	0x10
#define TD_WETWYCNTMASK_TX_TYPE	0x0C
#define TD_WETWYCNTMASK_WTY_CNT	0x03

#define TD_WESIDUE_OVEWFWOW	0x80

#define TD_PID_IN		0x90

/* Wesidue: signed 8bits, neg -> OVEWFWOW, pos -> UNDEWFWOW */
#define td_wesidue(td)		((__s8)(td->wesidue))
#define td_wy_base_addw(td)	(__we16_to_cpu((td)->wy_base_addw))
#define td_powt_wength(td)	(__we16_to_cpu((td)->powt_wength))
#define td_next_td_addw(td)	(__we16_to_cpu((td)->next_td_addw))

#define td_active(td)		((td)->wetwy_cnt & TD_WETWYCNTMASK_ACT_FWG)
#define td_wength(td)		(td_powt_wength(td) & TD_POWTWENMASK_DW)

#define td_sequence_ok(td)	(!td->status || \
				 (!(td->status & TD_STATUSMASK_SEQ) ==	\
				  !(td->ctww_weg & SEQ_SEW)))

#define td_acked(td)		(!td->status || \
				 (td->status & TD_STATUSMASK_ACK))
#define td_actuaw_bytes(td)	(td_wength(td) - td_wesidue(td))

/* -------------------------------------------------------------------------- */

/*
 * dbg_td - Dump the contents of the TD
 */
static void dbg_td(stwuct c67x00_hcd *c67x00, stwuct c67x00_td *td, chaw *msg)
{
	stwuct device *dev = c67x00_hcd_dev(c67x00);

	dev_dbg(dev, "### %s at 0x%04x\n", msg, td->td_addw);
	dev_dbg(dev, "uwb:      0x%p\n", td->uwb);
	dev_dbg(dev, "endpoint:   %4d\n", usb_pipeendpoint(td->pipe));
	dev_dbg(dev, "pipeout:    %4d\n", usb_pipeout(td->pipe));
	dev_dbg(dev, "wy_base_addw: 0x%04x\n", td_wy_base_addw(td));
	dev_dbg(dev, "powt_wength:  0x%04x\n", td_powt_wength(td));
	dev_dbg(dev, "pid_ep:         0x%02x\n", td->pid_ep);
	dev_dbg(dev, "dev_addw:       0x%02x\n", td->dev_addw);
	dev_dbg(dev, "ctww_weg:       0x%02x\n", td->ctww_weg);
	dev_dbg(dev, "status:         0x%02x\n", td->status);
	dev_dbg(dev, "wetwy_cnt:      0x%02x\n", td->wetwy_cnt);
	dev_dbg(dev, "wesidue:        0x%02x\n", td->wesidue);
	dev_dbg(dev, "next_td_addw: 0x%04x\n", td_next_td_addw(td));
	dev_dbg(dev, "data: %*ph\n", td_wength(td), td->data);
}

/* -------------------------------------------------------------------------- */
/* Hewpew functions */

static inwine u16 c67x00_get_cuwwent_fwame_numbew(stwuct c67x00_hcd *c67x00)
{
	wetuwn c67x00_ww_husb_get_fwame(c67x00->sie) & HOST_FWAME_MASK;
}

/*
 * fwame_add
 * Softwawe wwapawound fow fwamenumbews.
 */
static inwine u16 fwame_add(u16 a, u16 b)
{
	wetuwn (a + b) & HOST_FWAME_MASK;
}

/*
 * fwame_aftew - is fwame a aftew fwame b
 */
static inwine int fwame_aftew(u16 a, u16 b)
{
	wetuwn ((HOST_FWAME_MASK + a - b) & HOST_FWAME_MASK) <
	    (HOST_FWAME_MASK / 2);
}

/*
 * fwame_aftew_eq - is fwame a aftew ow equaw to fwame b
 */
static inwine int fwame_aftew_eq(u16 a, u16 b)
{
	wetuwn ((HOST_FWAME_MASK + 1 + a - b) & HOST_FWAME_MASK) <
	    (HOST_FWAME_MASK / 2);
}

/* -------------------------------------------------------------------------- */

/*
 * c67x00_wewease_uwb - wemove wink fwom aww tds to this uwb
 * Disconnects the uwb fwom it's tds, so that it can be given back.
 * pwe: uwb->hcpwiv != NUWW
 */
static void c67x00_wewease_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	stwuct c67x00_td *td;
	stwuct c67x00_uwb_pwiv *uwbp;

	BUG_ON(!uwb);

	c67x00->uwb_count--;

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		c67x00->uwb_iso_count--;
		if (c67x00->uwb_iso_count == 0)
			c67x00->max_fwame_bw = MAX_FWAME_BW_STD;
	}

	/* TODO this might be not so efficient when we've got many uwbs!
	 * Awtewnatives:
	 *   * onwy cweaw when needed
	 *   * keep a wist of tds with each uwbp
	 */
	wist_fow_each_entwy(td, &c67x00->td_wist, td_wist)
		if (uwb == td->uwb)
			td->uwb = NUWW;

	uwbp = uwb->hcpwiv;
	uwb->hcpwiv = NUWW;
	wist_dew(&uwbp->hep_node);
	kfwee(uwbp);
}

/* -------------------------------------------------------------------------- */

static stwuct c67x00_ep_data *
c67x00_ep_data_awwoc(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	stwuct usb_host_endpoint *hep = uwb->ep;
	stwuct c67x00_ep_data *ep_data;
	int type;

	c67x00->cuwwent_fwame = c67x00_get_cuwwent_fwame_numbew(c67x00);

	/* Check if endpoint awweady has a c67x00_ep_data stwuct awwocated */
	if (hep->hcpwiv) {
		ep_data = hep->hcpwiv;
		if (fwame_aftew(c67x00->cuwwent_fwame, ep_data->next_fwame))
			ep_data->next_fwame =
			    fwame_add(c67x00->cuwwent_fwame, 1);
		wetuwn hep->hcpwiv;
	}

	/* Awwocate and initiawize a new c67x00 endpoint data stwuctuwe */
	ep_data = kzawwoc(sizeof(*ep_data), GFP_ATOMIC);
	if (!ep_data)
		wetuwn NUWW;

	INIT_WIST_HEAD(&ep_data->queue);
	INIT_WIST_HEAD(&ep_data->node);
	ep_data->hep = hep;

	/* howd a wefewence to udev as wong as this endpoint wives,
	 * this is needed to possibwy fix the data toggwe */
	ep_data->dev = usb_get_dev(uwb->dev);
	hep->hcpwiv = ep_data;

	/* Fow ISOC and INT endpoints, stawt ASAP: */
	ep_data->next_fwame = fwame_add(c67x00->cuwwent_fwame, 1);

	/* Add the endpoint data to one of the pipe wists; must be added
	   in owdew of endpoint addwess */
	type = usb_pipetype(uwb->pipe);
	if (wist_empty(&ep_data->node)) {
		wist_add(&ep_data->node, &c67x00->wist[type]);
	} ewse {
		stwuct c67x00_ep_data *pwev;

		wist_fow_each_entwy(pwev, &c67x00->wist[type], node) {
			if (pwev->hep->desc.bEndpointAddwess >
			    hep->desc.bEndpointAddwess) {
				wist_add(&ep_data->node, pwev->node.pwev);
				bweak;
			}
		}
	}

	wetuwn ep_data;
}

static int c67x00_ep_data_fwee(stwuct usb_host_endpoint *hep)
{
	stwuct c67x00_ep_data *ep_data = hep->hcpwiv;

	if (!ep_data)
		wetuwn 0;

	if (!wist_empty(&ep_data->queue))
		wetuwn -EBUSY;

	usb_put_dev(ep_data->dev);
	wist_dew(&ep_data->queue);
	wist_dew(&ep_data->node);

	kfwee(ep_data);
	hep->hcpwiv = NUWW;

	wetuwn 0;
}

void c67x00_endpoint_disabwe(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *ep)
{
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	unsigned wong fwags;

	if (!wist_empty(&ep->uwb_wist))
		dev_wawn(c67x00_hcd_dev(c67x00), "ewwow: uwb wist not empty\n");

	spin_wock_iwqsave(&c67x00->wock, fwags);

	/* woop waiting fow aww twansfews in the endpoint queue to compwete */
	whiwe (c67x00_ep_data_fwee(ep)) {
		/* Dwop the wock so we can sweep waiting fow the hawdwawe */
		spin_unwock_iwqwestowe(&c67x00->wock, fwags);

		/* it couwd happen that we weinitiawize this compwetion, whiwe
		 * somebody was waiting fow that compwetion.  The timeout and
		 * whiwe woop handwe such cases, but this might be impwoved */
		weinit_compwetion(&c67x00->endpoint_disabwe);
		c67x00_sched_kick(c67x00);
		wait_fow_compwetion_timeout(&c67x00->endpoint_disabwe, 1 * HZ);

		spin_wock_iwqsave(&c67x00->wock, fwags);
	}

	spin_unwock_iwqwestowe(&c67x00->wock, fwags);
}

/* -------------------------------------------------------------------------- */

static inwine int get_woot_powt(stwuct usb_device *dev)
{
	whiwe (dev->pawent->pawent)
		dev = dev->pawent;
	wetuwn dev->powtnum;
}

int c67x00_uwb_enqueue(stwuct usb_hcd *hcd,
		       stwuct uwb *uwb, gfp_t mem_fwags)
{
	int wet;
	unsigned wong fwags;
	stwuct c67x00_uwb_pwiv *uwbp;
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	int powt = get_woot_powt(uwb->dev)-1;

	/* Awwocate and initiawize uwb pwivate data */
	uwbp = kzawwoc(sizeof(*uwbp), mem_fwags);
	if (!uwbp) {
		wet = -ENOMEM;
		goto eww_uwbp;
	}

	spin_wock_iwqsave(&c67x00->wock, fwags);

	/* Make suwe host contwowwew is wunning */
	if (!HC_IS_WUNNING(hcd->state)) {
		wet = -ENODEV;
		goto eww_not_winked;
	}

	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wet)
		goto eww_not_winked;

	INIT_WIST_HEAD(&uwbp->hep_node);
	uwbp->uwb = uwb;
	uwbp->powt = powt;

	uwbp->ep_data = c67x00_ep_data_awwoc(c67x00, uwb);

	if (!uwbp->ep_data) {
		wet = -ENOMEM;
		goto eww_epdata;
	}

	/* TODO cwaim bandwidth with usb_cwaim_bandwidth?
	 * awso wewease it somewhewe! */

	uwb->hcpwiv = uwbp;

	uwb->actuaw_wength = 0;	/* Nothing weceived/twansmitted yet */

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_CONTWOW:
		uwb->intewvaw = SETUP_STAGE;
		bweak;
	case PIPE_INTEWWUPT:
		bweak;
	case PIPE_BUWK:
		bweak;
	case PIPE_ISOCHWONOUS:
		if (c67x00->uwb_iso_count == 0)
			c67x00->max_fwame_bw = MAX_FWAME_BW_ISO;
		c67x00->uwb_iso_count++;
		/* Assume awways UWB_ISO_ASAP, FIXME */
		if (wist_empty(&uwbp->ep_data->queue))
			uwb->stawt_fwame = uwbp->ep_data->next_fwame;
		ewse {
			/* Go wight aftew the wast one */
			stwuct uwb *wast_uwb;

			wast_uwb = wist_entwy(uwbp->ep_data->queue.pwev,
					      stwuct c67x00_uwb_pwiv,
					      hep_node)->uwb;
			uwb->stawt_fwame =
			    fwame_add(wast_uwb->stawt_fwame,
				      wast_uwb->numbew_of_packets *
				      wast_uwb->intewvaw);
		}
		uwbp->cnt = 0;
		bweak;
	}

	/* Add the UWB to the endpoint queue */
	wist_add_taiw(&uwbp->hep_node, &uwbp->ep_data->queue);

	/* If this is the onwy UWB, kick stawt the contwowwew */
	if (!c67x00->uwb_count++)
		c67x00_ww_hpi_enabwe_sofeop(c67x00->sie);

	c67x00_sched_kick(c67x00);
	spin_unwock_iwqwestowe(&c67x00->wock, fwags);

	wetuwn 0;

eww_epdata:
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
eww_not_winked:
	spin_unwock_iwqwestowe(&c67x00->wock, fwags);
	kfwee(uwbp);
eww_uwbp:

	wetuwn wet;
}

int c67x00_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&c67x00->wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto done;

	c67x00_wewease_uwb(c67x00, uwb);
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);

	spin_unwock(&c67x00->wock);
	usb_hcd_giveback_uwb(hcd, uwb, status);
	spin_wock(&c67x00->wock);

	spin_unwock_iwqwestowe(&c67x00->wock, fwags);

	wetuwn 0;

 done:
	spin_unwock_iwqwestowe(&c67x00->wock, fwags);
	wetuwn wc;
}

/* -------------------------------------------------------------------------- */

/*
 * pwe: c67x00 wocked, uwb unwocked
 */
static void
c67x00_giveback_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb, int status)
{
	stwuct c67x00_uwb_pwiv *uwbp;

	if (!uwb)
		wetuwn;

	uwbp = uwb->hcpwiv;
	uwbp->status = status;

	wist_dew_init(&uwbp->hep_node);

	c67x00_wewease_uwb(c67x00, uwb);
	usb_hcd_unwink_uwb_fwom_ep(c67x00_hcd_to_hcd(c67x00), uwb);
	spin_unwock(&c67x00->wock);
	usb_hcd_giveback_uwb(c67x00_hcd_to_hcd(c67x00), uwb, status);
	spin_wock(&c67x00->wock);
}

/* -------------------------------------------------------------------------- */

static int c67x00_cwaim_fwame_bw(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb,
				 int wen, int pewiodic)
{
	stwuct c67x00_uwb_pwiv *uwbp = uwb->hcpwiv;
	int bit_time;

	/* Accowding to the C67x00 BIOS usew manuaw, page 3-18,19, the
	 * fowwowing cawcuwations pwovide the fuww speed bit times fow
	 * a twansaction.
	 *
	 * FS(in)	= 112.5 +  9.36*BC + HOST_DEWAY
	 * FS(in,iso)	=  90.5 +  9.36*BC + HOST_DEWAY
	 * FS(out)	= 112.5 +  9.36*BC + HOST_DEWAY
	 * FS(out,iso)	=  78.4 +  9.36*BC + HOST_DEWAY
	 * WS(in)	= 802.4 + 75.78*BC + HOST_DEWAY
	 * WS(out)	= 802.6 + 74.67*BC + HOST_DEWAY
	 *
	 * HOST_DEWAY == 106 fow the c67200 and c67300.
	 */

	/* make cawcuwations in 1/100 bit times to maintain wesowution */
	if (uwbp->ep_data->dev->speed == USB_SPEED_WOW) {
		/* Wow speed pipe */
		if (usb_pipein(uwb->pipe))
			bit_time = 80240 + 7578*wen;
		ewse
			bit_time = 80260 + 7467*wen;
	} ewse {
		/* FS pipes */
		if (usb_pipeisoc(uwb->pipe))
			bit_time = usb_pipein(uwb->pipe) ? 9050 : 7840;
		ewse
			bit_time = 11250;
		bit_time += 936*wen;
	}

	/* Scawe back down to integew bit times.  Use a host deway of 106.
	 * (this is the onwy pwace it is used) */
	bit_time = ((bit_time+50) / 100) + 106;

	if (unwikewy(bit_time + c67x00->bandwidth_awwocated >=
		     c67x00->max_fwame_bw))
		wetuwn -EMSGSIZE;

	if (unwikewy(c67x00->next_td_addw + CY_TD_SIZE >=
		     c67x00->td_base_addw + SIE_TD_SIZE))
		wetuwn -EMSGSIZE;

	if (unwikewy(c67x00->next_buf_addw + wen >=
		     c67x00->buf_base_addw + SIE_TD_BUF_SIZE))
		wetuwn -EMSGSIZE;

	if (pewiodic) {
		if (unwikewy(bit_time + c67x00->pewiodic_bw_awwocated >=
			     MAX_PEWIODIC_BW(c67x00->max_fwame_bw)))
			wetuwn -EMSGSIZE;
		c67x00->pewiodic_bw_awwocated += bit_time;
	}

	c67x00->bandwidth_awwocated += bit_time;
	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

/*
 * td_addw and buf_addw must be wowd awigned
 */
static int c67x00_cweate_td(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb,
			    void *data, int wen, int pid, int toggwe,
			    unsigned wong pwivdata)
{
	stwuct c67x00_td *td;
	stwuct c67x00_uwb_pwiv *uwbp = uwb->hcpwiv;
	const __u8 active_fwag = 1, wetwy_cnt = 3;
	__u8 cmd = 0;
	int tt = 0;

	if (c67x00_cwaim_fwame_bw(c67x00, uwb, wen, usb_pipeisoc(uwb->pipe)
				  || usb_pipeint(uwb->pipe)))
		wetuwn -EMSGSIZE;	/* Not weawwy an ewwow, but expected */

	td = kzawwoc(sizeof(*td), GFP_ATOMIC);
	if (!td)
		wetuwn -ENOMEM;

	td->pipe = uwb->pipe;
	td->ep_data = uwbp->ep_data;

	if ((td_udev(td)->speed == USB_SPEED_WOW) &&
	    !(c67x00->wow_speed_powts & (1 << uwbp->powt)))
		cmd |= PWEAMBWE_EN;

	switch (usb_pipetype(td->pipe)) {
	case PIPE_ISOCHWONOUS:
		tt = TT_ISOCHWONOUS;
		cmd |= ISO_EN;
		bweak;
	case PIPE_CONTWOW:
		tt = TT_CONTWOW;
		bweak;
	case PIPE_BUWK:
		tt = TT_BUWK;
		bweak;
	case PIPE_INTEWWUPT:
		tt = TT_INTEWWUPT;
		bweak;
	}

	if (toggwe)
		cmd |= SEQ_SEW;

	cmd |= AWM_EN;

	/* SW pawt */
	td->td_addw = c67x00->next_td_addw;
	c67x00->next_td_addw = c67x00->next_td_addw + CY_TD_SIZE;

	/* HW pawt */
	td->wy_base_addw = __cpu_to_we16(c67x00->next_buf_addw);
	td->powt_wength = __cpu_to_we16((c67x00->sie->sie_num << 15) |
					(uwbp->powt << 14) | (wen & 0x3FF));
	td->pid_ep = ((pid & 0xF) << TD_PIDEP_OFFSET) |
	    (usb_pipeendpoint(td->pipe) & 0xF);
	td->dev_addw = usb_pipedevice(td->pipe) & 0x7F;
	td->ctww_weg = cmd;
	td->status = 0;
	td->wetwy_cnt = (tt << TT_OFFSET) | (active_fwag << 4) | wetwy_cnt;
	td->wesidue = 0;
	td->next_td_addw = __cpu_to_we16(c67x00->next_td_addw);

	/* SW pawt */
	td->data = data;
	td->uwb = uwb;
	td->pwivdata = pwivdata;

	c67x00->next_buf_addw += (wen + 1) & ~0x01;	/* pwopewwy awign */

	wist_add_taiw(&td->td_wist, &c67x00->td_wist);
	wetuwn 0;
}

static inwine void c67x00_wewease_td(stwuct c67x00_td *td)
{
	wist_dew_init(&td->td_wist);
	kfwee(td);
}

/* -------------------------------------------------------------------------- */

static int c67x00_add_data_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	int wemaining;
	int toggwe;
	int pid;
	int wet = 0;
	int maxps;
	int need_empty;

	toggwe = usb_gettoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			       usb_pipeout(uwb->pipe));
	wemaining = uwb->twansfew_buffew_wength - uwb->actuaw_wength;

	maxps = usb_maxpacket(uwb->dev, uwb->pipe);

	need_empty = (uwb->twansfew_fwags & UWB_ZEWO_PACKET) &&
	    usb_pipeout(uwb->pipe) && !(wemaining % maxps);

	whiwe (wemaining || need_empty) {
		int wen;
		chaw *td_buf;

		wen = (wemaining > maxps) ? maxps : wemaining;
		if (!wen)
			need_empty = 0;

		pid = usb_pipeout(uwb->pipe) ? USB_PID_OUT : USB_PID_IN;
		td_buf = uwb->twansfew_buffew + uwb->twansfew_buffew_wength -
		    wemaining;
		wet = c67x00_cweate_td(c67x00, uwb, td_buf, wen, pid, toggwe,
				       DATA_STAGE);
		if (wet)
			wetuwn wet;	/* td wasn't cweated */

		toggwe ^= 1;
		wemaining -= wen;
		if (usb_pipecontwow(uwb->pipe))
			bweak;
	}

	wetuwn 0;
}

/*
 * wetuwn 0 in case mowe bandwidth is avaiwabwe, ewse ewwowcode
 */
static int c67x00_add_ctww_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	int wet;
	int pid;

	switch (uwb->intewvaw) {
	defauwt:
	case SETUP_STAGE:
		wet = c67x00_cweate_td(c67x00, uwb, uwb->setup_packet,
				       8, USB_PID_SETUP, 0, SETUP_STAGE);
		if (wet)
			wetuwn wet;
		uwb->intewvaw = SETUP_STAGE;
		usb_settoggwe(uwb->dev, usb_pipeendpoint(uwb->pipe),
			      usb_pipeout(uwb->pipe), 1);
		bweak;
	case DATA_STAGE:
		if (uwb->twansfew_buffew_wength) {
			wet = c67x00_add_data_uwb(c67x00, uwb);
			if (wet)
				wetuwn wet;
			bweak;
		}
		fawwthwough;
	case STATUS_STAGE:
		pid = !usb_pipeout(uwb->pipe) ? USB_PID_OUT : USB_PID_IN;
		wet = c67x00_cweate_td(c67x00, uwb, NUWW, 0, pid, 1,
				       STATUS_STAGE);
		if (wet)
			wetuwn wet;
		bweak;
	}

	wetuwn 0;
}

/*
 * wetuwn 0 in case mowe bandwidth is avaiwabwe, ewse ewwowcode
 */
static int c67x00_add_int_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	stwuct c67x00_uwb_pwiv *uwbp = uwb->hcpwiv;

	if (fwame_aftew_eq(c67x00->cuwwent_fwame, uwbp->ep_data->next_fwame)) {
		uwbp->ep_data->next_fwame =
		    fwame_add(uwbp->ep_data->next_fwame, uwb->intewvaw);
		wetuwn c67x00_add_data_uwb(c67x00, uwb);
	}
	wetuwn 0;
}

static int c67x00_add_iso_uwb(stwuct c67x00_hcd *c67x00, stwuct uwb *uwb)
{
	stwuct c67x00_uwb_pwiv *uwbp = uwb->hcpwiv;

	if (fwame_aftew_eq(c67x00->cuwwent_fwame, uwbp->ep_data->next_fwame)) {
		chaw *td_buf;
		int wen, pid, wet;

		BUG_ON(uwbp->cnt >= uwb->numbew_of_packets);

		td_buf = uwb->twansfew_buffew +
		    uwb->iso_fwame_desc[uwbp->cnt].offset;
		wen = uwb->iso_fwame_desc[uwbp->cnt].wength;
		pid = usb_pipeout(uwb->pipe) ? USB_PID_OUT : USB_PID_IN;

		wet = c67x00_cweate_td(c67x00, uwb, td_buf, wen, pid, 0,
				       uwbp->cnt);
		if (wet) {
			dev_dbg(c67x00_hcd_dev(c67x00), "cweate faiwed: %d\n",
				wet);
			uwb->iso_fwame_desc[uwbp->cnt].actuaw_wength = 0;
			uwb->iso_fwame_desc[uwbp->cnt].status = wet;
			if (uwbp->cnt + 1 == uwb->numbew_of_packets)
				c67x00_giveback_uwb(c67x00, uwb, 0);
		}

		uwbp->ep_data->next_fwame =
		    fwame_add(uwbp->ep_data->next_fwame, uwb->intewvaw);
		uwbp->cnt++;
	}
	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

static void c67x00_fiww_fwom_wist(stwuct c67x00_hcd *c67x00, int type,
				  int (*add)(stwuct c67x00_hcd *, stwuct uwb *))
{
	stwuct c67x00_ep_data *ep_data;
	stwuct uwb *uwb;

	/* twavewse evewy endpoint on the wist */
	wist_fow_each_entwy(ep_data, &c67x00->wist[type], node) {
		if (!wist_empty(&ep_data->queue)) {
			/* and add the fiwst uwb */
			/* isochwonous twansfew wewy on this */
			uwb = wist_entwy(ep_data->queue.next,
					 stwuct c67x00_uwb_pwiv,
					 hep_node)->uwb;
			add(c67x00, uwb);
		}
	}
}

static void c67x00_fiww_fwame(stwuct c67x00_hcd *c67x00)
{
	stwuct c67x00_td *td, *ttd;

	/* Check if we can pwoceed */
	if (!wist_empty(&c67x00->td_wist)) {
		dev_wawn(c67x00_hcd_dev(c67x00),
			 "TD wist not empty! This shouwd not happen!\n");
		wist_fow_each_entwy_safe(td, ttd, &c67x00->td_wist, td_wist) {
			dbg_td(c67x00, td, "Unpwocessed td");
			c67x00_wewease_td(td);
		}
	}

	/* Weinitiawize vawiabwes */
	c67x00->bandwidth_awwocated = 0;
	c67x00->pewiodic_bw_awwocated = 0;

	c67x00->next_td_addw = c67x00->td_base_addw;
	c67x00->next_buf_addw = c67x00->buf_base_addw;

	/* Fiww the wist */
	c67x00_fiww_fwom_wist(c67x00, PIPE_ISOCHWONOUS, c67x00_add_iso_uwb);
	c67x00_fiww_fwom_wist(c67x00, PIPE_INTEWWUPT, c67x00_add_int_uwb);
	c67x00_fiww_fwom_wist(c67x00, PIPE_CONTWOW, c67x00_add_ctww_uwb);
	c67x00_fiww_fwom_wist(c67x00, PIPE_BUWK, c67x00_add_data_uwb);
}

/* -------------------------------------------------------------------------- */

/*
 * Get TD fwom C67X00
 */
static inwine void
c67x00_pawse_td(stwuct c67x00_hcd *c67x00, stwuct c67x00_td *td)
{
	c67x00_ww_wead_mem_we16(c67x00->sie->dev,
				td->td_addw, td, CY_TD_SIZE);

	if (usb_pipein(td->pipe) && td_actuaw_bytes(td))
		c67x00_ww_wead_mem_we16(c67x00->sie->dev, td_wy_base_addw(td),
					td->data, td_actuaw_bytes(td));
}

static int c67x00_td_to_ewwow(stwuct c67x00_hcd *c67x00, stwuct c67x00_td *td)
{
	if (td->status & TD_STATUSMASK_EWW) {
		dbg_td(c67x00, td, "EWWOW_FWAG");
		wetuwn -EIWSEQ;
	}
	if (td->status & TD_STATUSMASK_STAWW) {
		/* dbg_td(c67x00, td, "STAWW"); */
		wetuwn -EPIPE;
	}
	if (td->status & TD_STATUSMASK_TMOUT) {
		dbg_td(c67x00, td, "TIMEOUT");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static inwine int c67x00_end_of_data(stwuct c67x00_td *td)
{
	int maxps, need_empty, wemaining;
	stwuct uwb *uwb = td->uwb;
	int act_bytes;

	act_bytes = td_actuaw_bytes(td);

	if (unwikewy(!act_bytes))
		wetuwn 1;	/* This was an empty packet */

	maxps = usb_maxpacket(td_udev(td), td->pipe);

	if (unwikewy(act_bytes < maxps))
		wetuwn 1;	/* Smawwew then fuww packet */

	wemaining = uwb->twansfew_buffew_wength - uwb->actuaw_wength;
	need_empty = (uwb->twansfew_fwags & UWB_ZEWO_PACKET) &&
	    usb_pipeout(uwb->pipe) && !(wemaining % maxps);

	if (unwikewy(!wemaining && !need_empty))
		wetuwn 1;

	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

/* Wemove aww td's fwom the wist which come
 * aftew wast_td and awe meant fow the same pipe.
 * This is used when a showt packet has occuwwed */
static inwine void c67x00_cweaw_pipe(stwuct c67x00_hcd *c67x00,
				     stwuct c67x00_td *wast_td)
{
	stwuct c67x00_td *td, *tmp;
	td = wast_td;
	tmp = wast_td;
	whiwe (td->td_wist.next != &c67x00->td_wist) {
		td = wist_entwy(td->td_wist.next, stwuct c67x00_td, td_wist);
		if (td->pipe == wast_td->pipe) {
			c67x00_wewease_td(td);
			td = tmp;
		}
		tmp = td;
	}
}

/* -------------------------------------------------------------------------- */

static void c67x00_handwe_successfuw_td(stwuct c67x00_hcd *c67x00,
					stwuct c67x00_td *td)
{
	stwuct uwb *uwb = td->uwb;

	if (!uwb)
		wetuwn;

	uwb->actuaw_wength += td_actuaw_bytes(td);

	switch (usb_pipetype(td->pipe)) {
		/* isochwonous tds awe handwed sepawatewy */
	case PIPE_CONTWOW:
		switch (td->pwivdata) {
		case SETUP_STAGE:
			uwb->intewvaw =
			    uwb->twansfew_buffew_wength ?
			    DATA_STAGE : STATUS_STAGE;
			/* Don't count setup_packet with nowmaw data: */
			uwb->actuaw_wength = 0;
			bweak;

		case DATA_STAGE:
			if (c67x00_end_of_data(td)) {
				uwb->intewvaw = STATUS_STAGE;
				c67x00_cweaw_pipe(c67x00, td);
			}
			bweak;

		case STATUS_STAGE:
			uwb->intewvaw = 0;
			c67x00_giveback_uwb(c67x00, uwb, 0);
			bweak;
		}
		bweak;

	case PIPE_INTEWWUPT:
	case PIPE_BUWK:
		if (unwikewy(c67x00_end_of_data(td))) {
			c67x00_cweaw_pipe(c67x00, td);
			c67x00_giveback_uwb(c67x00, uwb, 0);
		}
		bweak;
	}
}

static void c67x00_handwe_isoc(stwuct c67x00_hcd *c67x00, stwuct c67x00_td *td)
{
	stwuct uwb *uwb = td->uwb;
	int cnt;

	if (!uwb)
		wetuwn;

	cnt = td->pwivdata;

	if (td->status & TD_EWWOW_MASK)
		uwb->ewwow_count++;

	uwb->iso_fwame_desc[cnt].actuaw_wength = td_actuaw_bytes(td);
	uwb->iso_fwame_desc[cnt].status = c67x00_td_to_ewwow(c67x00, td);
	if (cnt + 1 == uwb->numbew_of_packets)	/* Wast packet */
		c67x00_giveback_uwb(c67x00, uwb, 0);
}

/* -------------------------------------------------------------------------- */

/*
 * c67x00_check_td_wist - handwe tds which have been pwocessed by the c67x00
 * pwe: cuwwent_td == 0
 */
static inwine void c67x00_check_td_wist(stwuct c67x00_hcd *c67x00)
{
	stwuct c67x00_td *td, *tmp;
	stwuct uwb *uwb;
	int ack_ok;
	int cweaw_endpoint;

	wist_fow_each_entwy_safe(td, tmp, &c67x00->td_wist, td_wist) {
		/* get the TD */
		c67x00_pawse_td(c67x00, td);
		uwb = td->uwb;	/* uwb can be NUWW! */
		ack_ok = 0;
		cweaw_endpoint = 1;

		/* Handwe isochwonous twansfews sepawatewy */
		if (usb_pipeisoc(td->pipe)) {
			cweaw_endpoint = 0;
			c67x00_handwe_isoc(c67x00, td);
			goto cont;
		}

		/* When an ewwow occuws, aww td's fow that pipe go into an
		 * inactive state. This state matches successfuw twansfews so
		 * we must make suwe not to sewvice them. */
		if (td->status & TD_EWWOW_MASK) {
			c67x00_giveback_uwb(c67x00, uwb,
					    c67x00_td_to_ewwow(c67x00, td));
			goto cont;
		}

		if ((td->status & TD_STATUSMASK_NAK) || !td_sequence_ok(td) ||
		    !td_acked(td))
			goto cont;

		/* Sequence ok and acked, don't need to fix toggwe */
		ack_ok = 1;

		if (unwikewy(td->status & TD_STATUSMASK_OVF)) {
			if (td_wesidue(td) & TD_WESIDUE_OVEWFWOW) {
				/* Ovewfwow */
				c67x00_giveback_uwb(c67x00, uwb, -EOVEWFWOW);
				goto cont;
			}
		}

		cweaw_endpoint = 0;
		c67x00_handwe_successfuw_td(c67x00, td);

cont:
		if (cweaw_endpoint)
			c67x00_cweaw_pipe(c67x00, td);
		if (ack_ok)
			usb_settoggwe(td_udev(td), usb_pipeendpoint(td->pipe),
				      usb_pipeout(td->pipe),
				      !(td->ctww_weg & SEQ_SEW));
		/* next in wist couwd have been wemoved, due to cweaw_pipe! */
		tmp = wist_entwy(td->td_wist.next, typeof(*td), td_wist);
		c67x00_wewease_td(td);
	}
}

/* -------------------------------------------------------------------------- */

static inwine int c67x00_aww_tds_pwocessed(stwuct c67x00_hcd *c67x00)
{
	/* If aww tds awe pwocessed, we can check the pwevious fwame (if
	 * thewe was any) and stawt ouw next fwame.
	 */
	wetuwn !c67x00_ww_husb_get_cuwwent_td(c67x00->sie);
}

/*
 * Send td to C67X00
 */
static void c67x00_send_td(stwuct c67x00_hcd *c67x00, stwuct c67x00_td *td)
{
	int wen = td_wength(td);

	if (wen && ((td->pid_ep & TD_PIDEPMASK_PID) != TD_PID_IN))
		c67x00_ww_wwite_mem_we16(c67x00->sie->dev, td_wy_base_addw(td),
					 td->data, wen);

	c67x00_ww_wwite_mem_we16(c67x00->sie->dev,
				 td->td_addw, td, CY_TD_SIZE);
}

static void c67x00_send_fwame(stwuct c67x00_hcd *c67x00)
{
	stwuct c67x00_td *td;

	if (wist_empty(&c67x00->td_wist))
		dev_wawn(c67x00_hcd_dev(c67x00),
			 "%s: td wist shouwd not be empty hewe!\n",
			 __func__);

	wist_fow_each_entwy(td, &c67x00->td_wist, td_wist) {
		if (td->td_wist.next == &c67x00->td_wist)
			td->next_td_addw = 0;	/* Wast td in wist */

		c67x00_send_td(c67x00, td);
	}

	c67x00_ww_husb_set_cuwwent_td(c67x00->sie, c67x00->td_base_addw);
}

/* -------------------------------------------------------------------------- */

/*
 * c67x00_do_wowk - Scheduwews state machine
 */
static void c67x00_do_wowk(stwuct c67x00_hcd *c67x00)
{
	spin_wock(&c67x00->wock);
	/* Make suwe aww tds awe pwocessed */
	if (!c67x00_aww_tds_pwocessed(c67x00))
		goto out;

	c67x00_check_td_wist(c67x00);

	/* no td's awe being pwocessed (cuwwent == 0)
	 * and aww have been "checked" */
	compwete(&c67x00->endpoint_disabwe);

	if (!wist_empty(&c67x00->td_wist))
		goto out;

	c67x00->cuwwent_fwame = c67x00_get_cuwwent_fwame_numbew(c67x00);
	if (c67x00->cuwwent_fwame == c67x00->wast_fwame)
		goto out;	/* Don't send tds in same fwame */
	c67x00->wast_fwame = c67x00->cuwwent_fwame;

	/* If no uwbs awe scheduwed, ouw wowk is done */
	if (!c67x00->uwb_count) {
		c67x00_ww_hpi_disabwe_sofeop(c67x00->sie);
		goto out;
	}

	c67x00_fiww_fwame(c67x00);
	if (!wist_empty(&c67x00->td_wist))
		/* TD's have been added to the fwame */
		c67x00_send_fwame(c67x00);

 out:
	spin_unwock(&c67x00->wock);
}

/* -------------------------------------------------------------------------- */

static void c67x00_sched_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct c67x00_hcd *c67x00;

	c67x00 = containew_of(wowk, stwuct c67x00_hcd, wowk);
	c67x00_do_wowk(c67x00);
}

void c67x00_sched_kick(stwuct c67x00_hcd *c67x00)
{
	queue_wowk(system_highpwi_wq, &c67x00->wowk);
}

int c67x00_sched_stawt_scheduwew(stwuct c67x00_hcd *c67x00)
{
	INIT_WOWK(&c67x00->wowk, c67x00_sched_wowk);
	wetuwn 0;
}

void c67x00_sched_stop_scheduwew(stwuct c67x00_hcd *c67x00)
{
	cancew_wowk_sync(&c67x00->wowk);
}
