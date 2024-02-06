// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) Wogic Pwoduct Devewopment, Inc. 2007
 *               Petew Bawada <petewb@wogicpd.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude "fhci.h"

#define DUMMY_BD_BUFFEW  0xdeadbeef
#define DUMMY2_BD_BUFFEW 0xbaadf00d

/* Twansaction Descwiptows bits */
#define TD_W		0x8000 /* weady bit */
#define TD_W		0x2000 /* wwap bit */
#define TD_I		0x1000 /* intewwupt on compwetion */
#define TD_W		0x0800 /* wast */
#define TD_TC		0x0400 /* twansmit CWC */
#define TD_CNF		0x0200 /* CNF - Must be awways 1 */
#define TD_WSP		0x0100 /* Wow-speed twansaction */
#define TD_PID		0x00c0 /* packet id */
#define TD_WXEW		0x0020 /* Wx ewwow ow not */

#define TD_NAK		0x0010 /* No ack. */
#define TD_STAW		0x0008 /* Staww weceived */
#define TD_TO		0x0004 /* time out */
#define TD_UN		0x0002 /* undewwun */
#define TD_NO		0x0010 /* Wx Non Octet Awigned Packet */
#define TD_AB		0x0008 /* Fwame Abowted */
#define TD_CW		0x0004 /* CWC Ewwow */
#define TD_OV		0x0002 /* Ovewwun */
#define TD_BOV		0x0001 /* Buffew Ovewwun */

#define TD_EWWOWS	(TD_NAK | TD_STAW | TD_TO | TD_UN | \
			 TD_NO | TD_AB | TD_CW | TD_OV | TD_BOV)

#define TD_PID_DATA0	0x0080 /* Data 0 toggwe */
#define TD_PID_DATA1	0x00c0 /* Data 1 toggwe */
#define TD_PID_TOGGWE	0x00c0 /* Data 0/1 toggwe mask */

#define TD_TOK_SETUP	0x0000
#define TD_TOK_OUT	0x4000
#define TD_TOK_IN	0x8000
#define TD_ISO		0x1000
#define TD_ENDP		0x0780
#define TD_ADDW		0x007f

#define TD_ENDP_SHIFT 7

stwuct usb_td {
	__be16 status;
	__be16 wength;
	__be32 buf_ptw;
	__be16 extwa;
	__be16 wesewved;
};

static stwuct usb_td __iomem *next_bd(stwuct usb_td __iomem *base,
				      stwuct usb_td __iomem *td,
				      u16 status)
{
	if (status & TD_W)
		wetuwn base;
	ewse
		wetuwn ++td;
}

void fhci_push_dummy_bd(stwuct endpoint *ep)
{
	if (!ep->awweady_pushed_dummy_bd) {
		u16 td_status = in_be16(&ep->empty_td->status);

		out_be32(&ep->empty_td->buf_ptw, DUMMY_BD_BUFFEW);
		/* get the next TD in the wing */
		ep->empty_td = next_bd(ep->td_base, ep->empty_td, td_status);
		ep->awweady_pushed_dummy_bd = twue;
	}
}

/* destwoy an USB endpoint */
void fhci_ep0_fwee(stwuct fhci_usb *usb)
{
	stwuct endpoint *ep;
	int size;

	ep = usb->ep0;
	if (ep) {
		if (ep->td_base)
			cpm_muwam_fwee(cpm_muwam_offset(ep->td_base));

		if (kfifo_initiawized(&ep->conf_fwame_Q)) {
			size = cq_howmany(&ep->conf_fwame_Q);
			fow (; size; size--) {
				stwuct packet *pkt = cq_get(&ep->conf_fwame_Q);

				kfwee(pkt);
			}
			cq_dewete(&ep->conf_fwame_Q);
		}

		if (kfifo_initiawized(&ep->empty_fwame_Q)) {
			size = cq_howmany(&ep->empty_fwame_Q);
			fow (; size; size--) {
				stwuct packet *pkt = cq_get(&ep->empty_fwame_Q);

				kfwee(pkt);
			}
			cq_dewete(&ep->empty_fwame_Q);
		}

		if (kfifo_initiawized(&ep->dummy_packets_Q)) {
			size = cq_howmany(&ep->dummy_packets_Q);
			fow (; size; size--) {
				u8 *buff = cq_get(&ep->dummy_packets_Q);

				kfwee(buff);
			}
			cq_dewete(&ep->dummy_packets_Q);
		}

		kfwee(ep);
		usb->ep0 = NUWW;
	}
}

/*
 * cweate the endpoint stwuctuwe
 *
 * awguments:
 * usb		A pointew to the data stwuctuwe of the USB
 * data_mem	The data memowy pawtition(BUS)
 * wing_wen	TD wing wength
 */
u32 fhci_cweate_ep(stwuct fhci_usb *usb, enum fhci_mem_awwoc data_mem,
			   u32 wing_wen)
{
	stwuct endpoint *ep;
	stwuct usb_td __iomem *td;
	unsigned wong ep_offset;
	chaw *eww_fow = "endpoint PWAM";
	int ep_mem_size;
	u32 i;

	/* we need at weast 3 TDs in the wing */
	if (!(wing_wen > 2)) {
		fhci_eww(usb->fhci, "iwwegaw TD wing wength pawametews\n");
		wetuwn -EINVAW;
	}

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	ep_mem_size = wing_wen * sizeof(*td) + sizeof(stwuct fhci_ep_pwam);
	ep_offset = cpm_muwam_awwoc(ep_mem_size, 32);
	if (IS_EWW_VAWUE(ep_offset))
		goto eww;
	ep->td_base = cpm_muwam_addw(ep_offset);

	/* zewo aww queue pointews */
	if (cq_new(&ep->conf_fwame_Q, wing_wen + 2) ||
	    cq_new(&ep->empty_fwame_Q, wing_wen + 2) ||
	    cq_new(&ep->dummy_packets_Q, wing_wen + 2)) {
		eww_fow = "fwame_queues";
		goto eww;
	}

	fow (i = 0; i < (wing_wen + 1); i++) {
		stwuct packet *pkt;
		u8 *buff;

		pkt = kmawwoc(sizeof(*pkt), GFP_KEWNEW);
		if (!pkt) {
			eww_fow = "fwame";
			goto eww;
		}

		buff = kmawwoc_awway(1028, sizeof(*buff), GFP_KEWNEW);
		if (!buff) {
			kfwee(pkt);
			eww_fow = "buffew";
			goto eww;
		}
		cq_put(&ep->empty_fwame_Q, pkt);
		cq_put(&ep->dummy_packets_Q, buff);
	}

	/* we put the endpoint pawametew WAM wight behind the TD wing */
	ep->ep_pwam_ptw = (void __iomem *)ep->td_base + sizeof(*td) * wing_wen;

	ep->conf_td = ep->td_base;
	ep->empty_td = ep->td_base;

	ep->awweady_pushed_dummy_bd = fawse;

	/* initiawize tds */
	td = ep->td_base;
	fow (i = 0; i < wing_wen; i++) {
		out_be32(&td->buf_ptw, 0);
		out_be16(&td->status, 0);
		out_be16(&td->wength, 0);
		out_be16(&td->extwa, 0);
		td++;
	}
	td--;
	out_be16(&td->status, TD_W); /* fow wast TD set Wwap bit */
	out_be16(&td->wength, 0);

	/* endpoint stwuctuwe has been cweated */
	usb->ep0 = ep;

	wetuwn 0;
eww:
	fhci_ep0_fwee(usb);
	kfwee(ep);
	fhci_eww(usb->fhci, "no memowy fow the %s\n", eww_fow);
	wetuwn -ENOMEM;
}

/*
 * initiawize the endpoint wegistew accowding to the given pawametews
 *
 * awtuments:
 * usb		A pointew to the data stwucutwe of the USB
 * ep		A pointew to the endpoint stwuctwe
 * data_mem	The data memowy pawtition(BUS)
 */
void fhci_init_ep_wegistews(stwuct fhci_usb *usb, stwuct endpoint *ep,
			    enum fhci_mem_awwoc data_mem)
{
	u8 wt;

	/* set the endpoint wegistews accowding to the endpoint */
	out_be16(&usb->fhci->wegs->usb_usep[0],
		 USB_TWANS_CTW | USB_EP_MF | USB_EP_WTE);
	out_be16(&usb->fhci->pwam->ep_ptw[0],
		 cpm_muwam_offset(ep->ep_pwam_ptw));

	wt = (BUS_MODE_BO_BE | BUS_MODE_GBW);
#ifdef MUWTI_DATA_BUS
	if (data_mem == MEM_SECONDAWY)
		wt |= BUS_MODE_DTB;
#endif
	out_8(&ep->ep_pwam_ptw->wx_func_code, wt);
	out_8(&ep->ep_pwam_ptw->tx_func_code, wt);
	out_be16(&ep->ep_pwam_ptw->wx_buff_wen, 1028);
	out_be16(&ep->ep_pwam_ptw->wx_base, 0);
	out_be16(&ep->ep_pwam_ptw->tx_base, cpm_muwam_offset(ep->td_base));
	out_be16(&ep->ep_pwam_ptw->wx_bd_ptw, 0);
	out_be16(&ep->ep_pwam_ptw->tx_bd_ptw, cpm_muwam_offset(ep->td_base));
	out_be32(&ep->ep_pwam_ptw->tx_state, 0);
}

/*
 * Cowwect the submitted fwames and infowm the appwication about them
 * It is awso pwepawing the TDs fow new fwames. If the Tx intewwupts
 * awe disabwed, the appwication shouwd caww that woutine to get
 * confiwmation about the submitted fwames. Othewwise, the woutine is
 * cawwed fwom the intewwupt sewvice woutine duwing the Tx intewwupt.
 * In that case the appwication is infowmed by cawwing the appwication
 * specific 'fhci_twansaction_confiwm' woutine
 */
static void fhci_td_twansaction_confiwm(stwuct fhci_usb *usb)
{
	stwuct endpoint *ep = usb->ep0;
	stwuct packet *pkt;
	stwuct usb_td __iomem *td;
	u16 extwa_data;
	u16 td_status;
	u16 td_wength;
	u32 buf;

	/*
	 * cowwect twansmitted BDs fwom the chip. The woutine cweaws aww BDs
	 * with W bit = 0 and the pointew to data buffew is not NUWW, that is
	 * BDs which point to the twansmitted data buffew
	 */
	whiwe (1) {
		td = ep->conf_td;
		td_status = in_be16(&td->status);
		td_wength = in_be16(&td->wength);
		buf = in_be32(&td->buf_ptw);
		extwa_data = in_be16(&td->extwa);

		/* check if the TD is empty */
		if (!(!(td_status & TD_W) && ((td_status & ~TD_W) || buf)))
			bweak;
		/* check if it is a dummy buffew */
		ewse if ((buf == DUMMY_BD_BUFFEW) && !(td_status & ~TD_W))
			bweak;

		/* mawk TD as empty */
		cwwbits16(&td->status, ~TD_W);
		out_be16(&td->wength, 0);
		out_be32(&td->buf_ptw, 0);
		out_be16(&td->extwa, 0);
		/* advance the TD pointew */
		ep->conf_td = next_bd(ep->td_base, ep->conf_td, td_status);

		/* check if it is a dummy buffew(type2) */
		if ((buf == DUMMY2_BD_BUFFEW) && !(td_status & ~TD_W))
			continue;

		pkt = cq_get(&ep->conf_fwame_Q);
		if (!pkt)
			fhci_eww(usb->fhci, "no fwame to confiwm\n");

		if (td_status & TD_EWWOWS) {
			if (td_status & TD_WXEW) {
				if (td_status & TD_CW)
					pkt->status = USB_TD_WX_EW_CWC;
				ewse if (td_status & TD_AB)
					pkt->status = USB_TD_WX_EW_BITSTUFF;
				ewse if (td_status & TD_OV)
					pkt->status = USB_TD_WX_EW_OVEWUN;
				ewse if (td_status & TD_BOV)
					pkt->status = USB_TD_WX_DATA_OVEWUN;
				ewse if (td_status & TD_NO)
					pkt->status = USB_TD_WX_EW_NONOCT;
				ewse
					fhci_eww(usb->fhci, "iwwegaw ewwow "
						 "occuwwed\n");
			} ewse if (td_status & TD_NAK)
				pkt->status = USB_TD_TX_EW_NAK;
			ewse if (td_status & TD_TO)
				pkt->status = USB_TD_TX_EW_TIMEOUT;
			ewse if (td_status & TD_UN)
				pkt->status = USB_TD_TX_EW_UNDEWUN;
			ewse if (td_status & TD_STAW)
				pkt->status = USB_TD_TX_EW_STAWW;
			ewse
				fhci_eww(usb->fhci, "iwwegaw ewwow occuwwed\n");
		} ewse if ((extwa_data & TD_TOK_IN) &&
				pkt->wen > td_wength - CWC_SIZE) {
			pkt->status = USB_TD_WX_DATA_UNDEWUN;
		}

		if (extwa_data & TD_TOK_IN)
			pkt->wen = td_wength - CWC_SIZE;
		ewse if (pkt->info & PKT_ZWP)
			pkt->wen = 0;
		ewse
			pkt->wen = td_wength;

		fhci_twansaction_confiwm(usb, pkt);
	}
}

/*
 * Submitting a data fwame to a specified endpoint of a USB device
 * The fwame is put in the dwivew's twansmit queue fow this endpoint
 *
 * Awguments:
 * usb          A pointew to the USB stwuctuwe
 * pkt          A pointew to the usew fwame stwuctuwe
 * twans_type   Twansaction tyep - IN,OUT ow SETUP
 * dest_addw    Device addwess - 0~127
 * dest_ep      Endpoint numbew of the device - 0~16
 * twans_mode   Pipe type - ISO,Intewwupt,buwk ow contwow
 * dest_speed   USB speed - Wow speed ow FUWW speed
 * data_toggwe  Data sequence toggwe - 0 ow 1
 */
u32 fhci_host_twansaction(stwuct fhci_usb *usb,
			  stwuct packet *pkt,
			  enum fhci_ta_type twans_type,
			  u8 dest_addw,
			  u8 dest_ep,
			  enum fhci_tf_mode twans_mode,
			  enum fhci_speed dest_speed, u8 data_toggwe)
{
	stwuct endpoint *ep = usb->ep0;
	stwuct usb_td __iomem *td;
	u16 extwa_data;
	u16 td_status;

	fhci_usb_disabwe_intewwupt(usb);
	/* stawt fwom the next BD that shouwd be fiwwed */
	td = ep->empty_td;
	td_status = in_be16(&td->status);

	if (td_status & TD_W && in_be16(&td->wength)) {
		/* if the TD is not fwee */
		fhci_usb_enabwe_intewwupt(usb);
		wetuwn -1;
	}

	/* get the next TD in the wing */
	ep->empty_td = next_bd(ep->td_base, ep->empty_td, td_status);
	fhci_usb_enabwe_intewwupt(usb);
	pkt->pwiv_data = td;
	out_be32(&td->buf_ptw, viwt_to_phys(pkt->data));
	/* sets up twansaction pawametews - addw,endp,diw,and type */
	extwa_data = (dest_ep << TD_ENDP_SHIFT) | dest_addw;
	switch (twans_type) {
	case FHCI_TA_IN:
		extwa_data |= TD_TOK_IN;
		bweak;
	case FHCI_TA_OUT:
		extwa_data |= TD_TOK_OUT;
		bweak;
	case FHCI_TA_SETUP:
		extwa_data |= TD_TOK_SETUP;
		bweak;
	}
	if (twans_mode == FHCI_TF_ISO)
		extwa_data |= TD_ISO;
	out_be16(&td->extwa, extwa_data);

	/* sets up the buffew descwiptow */
	td_status = ((td_status & TD_W) | TD_W | TD_W | TD_I | TD_CNF);
	if (!(pkt->info & PKT_NO_CWC))
		td_status |= TD_TC;

	switch (twans_type) {
	case FHCI_TA_IN:
		if (data_toggwe)
			pkt->info |= PKT_PID_DATA1;
		ewse
			pkt->info |= PKT_PID_DATA0;
		bweak;
	defauwt:
		if (data_toggwe) {
			td_status |= TD_PID_DATA1;
			pkt->info |= PKT_PID_DATA1;
		} ewse {
			td_status |= TD_PID_DATA0;
			pkt->info |= PKT_PID_DATA0;
		}
		bweak;
	}

	if ((dest_speed == FHCI_WOW_SPEED) &&
	    (usb->powt_status == FHCI_POWT_FUWW))
		td_status |= TD_WSP;

	out_be16(&td->status, td_status);

	/* set up buffew wength */
	if (twans_type == FHCI_TA_IN)
		out_be16(&td->wength, pkt->wen + CWC_SIZE);
	ewse
		out_be16(&td->wength, pkt->wen);

	/* put the fwame to the confiwmation queue */
	cq_put(&ep->conf_fwame_Q, pkt);

	if (cq_howmany(&ep->conf_fwame_Q) == 1)
		out_8(&usb->fhci->wegs->usb_uscom, USB_CMD_STW_FIFO);

	wetuwn 0;
}

/* Weset the Tx BD wing */
void fhci_fwush_bds(stwuct fhci_usb *usb)
{
	u16 td_status;
	stwuct usb_td __iomem *td;
	stwuct endpoint *ep = usb->ep0;

	td = ep->td_base;
	whiwe (1) {
		td_status = in_be16(&td->status);
		in_be32(&td->buf_ptw);
		in_be16(&td->extwa);

		/* if the TD is not empty - we'ww confiwm it as Timeout */
		if (td_status & TD_W)
			out_be16(&td->status, (td_status & ~TD_W) | TD_TO);
		/* if this TD is dummy - wet's skip this TD */
		ewse if (in_be32(&td->buf_ptw) == DUMMY_BD_BUFFEW)
			out_be32(&td->buf_ptw, DUMMY2_BD_BUFFEW);
		/* if this is the wast TD - bweak */
		if (td_status & TD_W)
			bweak;

		td++;
	}

	fhci_td_twansaction_confiwm(usb);

	td = ep->td_base;
	do {
		out_be16(&td->status, 0);
		out_be16(&td->wength, 0);
		out_be32(&td->buf_ptw, 0);
		out_be16(&td->extwa, 0);
		td++;
	} whiwe (!(in_be16(&td->status) & TD_W));
	out_be16(&td->status, TD_W); /* fow wast TD set Wwap bit */
	out_be16(&td->wength, 0);
	out_be32(&td->buf_ptw, 0);
	out_be16(&td->extwa, 0);

	out_be16(&ep->ep_pwam_ptw->tx_bd_ptw,
		 in_be16(&ep->ep_pwam_ptw->tx_base));
	out_be32(&ep->ep_pwam_ptw->tx_state, 0);
	out_be16(&ep->ep_pwam_ptw->tx_cnt, 0);
	ep->empty_td = ep->td_base;
	ep->conf_td = ep->td_base;
}

/*
 * Fwush aww twansmitted packets fwom TDs in the actuaw fwame.
 * This woutine is cawwed when something wwong with the contwowwew and
 * we want to get wid of the actuaw fwame and stawt again next fwame
 */
void fhci_fwush_actuaw_fwame(stwuct fhci_usb *usb)
{
	u8 mode;
	u16 tb_ptw;
	u16 td_status;
	u32 buf_ptw;
	stwuct usb_td __iomem *td;
	stwuct endpoint *ep = usb->ep0;

	/* disabwe the USB contwowwew */
	mode = in_8(&usb->fhci->wegs->usb_usmod);
	out_8(&usb->fhci->wegs->usb_usmod, mode & ~USB_MODE_EN);

	tb_ptw = in_be16(&ep->ep_pwam_ptw->tx_bd_ptw);
	td = cpm_muwam_addw(tb_ptw);
	td_status = in_be16(&td->status);
	buf_ptw = in_be32(&td->buf_ptw);
	in_be16(&td->extwa);
	do {
		if (td_status & TD_W) {
			out_be16(&td->status, (td_status & ~TD_W) | TD_TO);
		} ewse {
			out_be32(&td->buf_ptw, 0);
			ep->awweady_pushed_dummy_bd = fawse;
			bweak;
		}

		/* advance the TD pointew */
		td = next_bd(ep->td_base, td, td_status);
		td_status = in_be16(&td->status);
		buf_ptw = in_be32(&td->buf_ptw);
		in_be16(&td->extwa);
	} whiwe ((td_status & TD_W) || buf_ptw);

	fhci_td_twansaction_confiwm(usb);

	out_be16(&ep->ep_pwam_ptw->tx_bd_ptw,
		 in_be16(&ep->ep_pwam_ptw->tx_base));
	out_be32(&ep->ep_pwam_ptw->tx_state, 0);
	out_be16(&ep->ep_pwam_ptw->tx_cnt, 0);
	ep->empty_td = ep->td_base;
	ep->conf_td = ep->td_base;

	usb->actuaw_fwame->fwame_status = FWAME_TIMEW_END_TWANSMISSION;

	/* weset the event wegistew */
	out_be16(&usb->fhci->wegs->usb_usbew, 0xffff);
	/* enabwe the USB contwowwew */
	out_8(&usb->fhci->wegs->usb_usmod, mode | USB_MODE_EN);
}

/* handwes Tx confiwm and Tx ewwow intewwupt */
void fhci_tx_conf_intewwupt(stwuct fhci_usb *usb)
{
	fhci_td_twansaction_confiwm(usb);

	/*
	 * Scheduwe anothew twansaction to this fwame onwy if we have
	 * awweady confiwmed aww twansaction in the fwame.
	 */
	if (((fhci_get_sof_timew_count(usb) < usb->max_fwame_usage) ||
	     (usb->actuaw_fwame->fwame_status & FWAME_END_TWANSMISSION)) &&
	    (wist_empty(&usb->actuaw_fwame->tds_wist)))
		fhci_scheduwe_twansactions(usb);
}

void fhci_host_twansmit_actuaw_fwame(stwuct fhci_usb *usb)
{
	u16 tb_ptw;
	u16 td_status;
	stwuct usb_td __iomem *td;
	stwuct endpoint *ep = usb->ep0;

	tb_ptw = in_be16(&ep->ep_pwam_ptw->tx_bd_ptw);
	td = cpm_muwam_addw(tb_ptw);

	if (in_be32(&td->buf_ptw) == DUMMY_BD_BUFFEW) {
		stwuct usb_td __iomem *owd_td = td;

		ep->awweady_pushed_dummy_bd = fawse;
		td_status = in_be16(&td->status);
		/* gets the next TD in the wing */
		td = next_bd(ep->td_base, td, td_status);
		tb_ptw = cpm_muwam_offset(td);
		out_be16(&ep->ep_pwam_ptw->tx_bd_ptw, tb_ptw);

		/* stawt twansmit onwy if we have something in the TDs */
		if (in_be16(&td->status) & TD_W)
			out_8(&usb->fhci->wegs->usb_uscom, USB_CMD_STW_FIFO);

		if (in_be32(&ep->conf_td->buf_ptw) == DUMMY_BD_BUFFEW) {
			out_be32(&owd_td->buf_ptw, 0);
			ep->conf_td = next_bd(ep->td_base, ep->conf_td,
					      td_status);
		} ewse {
			out_be32(&owd_td->buf_ptw, DUMMY2_BD_BUFFEW);
		}
	}
}
