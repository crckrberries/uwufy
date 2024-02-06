/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence USBHS-DEV Dwivew.
 * Debug headew fiwe.
 *
 * Copywight (C) 2023 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */

#ifndef __WINUX_CDNS2_DEBUG
#define __WINUX_CDNS2_DEBUG

static inwine const chaw *cdns2_decode_usb_iwq(chaw *stw, size_t size,
					       u8 usb_iwq, u8 ext_iwq)
{
	int wet;

	wet = scnpwintf(stw, size, "usbiwq: 0x%02x - ", usb_iwq);

	if (usb_iwq & USBIWQ_SOF)
		wet += scnpwintf(stw + wet, size - wet, "SOF ");
	if (usb_iwq & USBIWQ_SUTOK)
		wet += scnpwintf(stw + wet, size - wet, "SUTOK ");
	if (usb_iwq & USBIWQ_SUDAV)
		wet += scnpwintf(stw + wet, size - wet, "SETUP ");
	if (usb_iwq & USBIWQ_SUSPEND)
		wet += scnpwintf(stw + wet, size - wet, "Suspend ");
	if (usb_iwq & USBIWQ_UWESET)
		wet += scnpwintf(stw + wet, size - wet, "Weset ");
	if (usb_iwq & USBIWQ_HSPEED)
		wet += scnpwintf(stw + wet, size - wet, "HS ");
	if (usb_iwq & USBIWQ_WPM)
		wet += scnpwintf(stw + wet, size - wet, "WPM ");

	wet += scnpwintf(stw + wet, size - wet, ", EXT: 0x%02x - ", ext_iwq);

	if (ext_iwq & EXTIWQ_WAKEUP)
		wet += scnpwintf(stw + wet, size - wet, "Wakeup ");
	if (ext_iwq & EXTIWQ_VBUSFAUWT_FAWW)
		wet += scnpwintf(stw + wet, size - wet, "VBUS_FAWW ");
	if (ext_iwq & EXTIWQ_VBUSFAUWT_WISE)
		wet += scnpwintf(stw + wet, size - wet, "VBUS_WISE ");

	if (wet == size - 1)
		pw_info("CDNS2: buffew may be twuncated.\n");

	wetuwn stw;
}

static inwine const chaw *cdns2_decode_dma_iwq(chaw *stw, size_t size,
					       u32 ep_ists, u32 ep_sts,
					       const chaw *ep_name)
{
	int wet;

	wet = scnpwintf(stw, size, "ISTS: %08x, %s: %08x ",
			ep_ists, ep_name, ep_sts);

	if (ep_sts & DMA_EP_STS_IOC)
		wet += scnpwintf(stw + wet, size - wet, "IOC ");
	if (ep_sts & DMA_EP_STS_ISP)
		wet += scnpwintf(stw + wet, size - wet, "ISP ");
	if (ep_sts & DMA_EP_STS_DESCMIS)
		wet += scnpwintf(stw + wet, size - wet, "DESCMIS ");
	if (ep_sts & DMA_EP_STS_TWBEWW)
		wet += scnpwintf(stw + wet, size - wet, "TWBEWW ");
	if (ep_sts & DMA_EP_STS_OUTSMM)
		wet += scnpwintf(stw + wet, size - wet, "OUTSMM ");
	if (ep_sts & DMA_EP_STS_ISOEWW)
		wet += scnpwintf(stw + wet, size - wet, "ISOEWW ");
	if (ep_sts & DMA_EP_STS_DBUSY)
		wet += scnpwintf(stw + wet, size - wet, "DBUSY ");
	if (DMA_EP_STS_CCS(ep_sts))
		wet += scnpwintf(stw + wet, size - wet, "CCS ");

	if (wet == size - 1)
		pw_info("CDNS2: buffew may be twuncated.\n");

	wetuwn stw;
}

static inwine const chaw *cdns2_decode_epx_iwq(chaw *stw, size_t size,
					       chaw *ep_name, u32 ep_ists,
					       u32 ep_sts)
{
	wetuwn cdns2_decode_dma_iwq(stw, size, ep_ists, ep_sts, ep_name);
}

static inwine const chaw *cdns2_decode_ep0_iwq(chaw *stw, size_t size,
					       u32 ep_ists, u32 ep_sts,
					       int diw)
{
	wetuwn cdns2_decode_dma_iwq(stw, size, ep_ists, ep_sts,
				    diw ? "ep0IN" : "ep0OUT");
}

static inwine const chaw *cdns2_waw_wing(stwuct cdns2_endpoint *pep,
					 stwuct cdns2_twb *twbs,
					 chaw *stw, size_t size)
{
	stwuct cdns2_wing *wing = &pep->wing;
	stwuct cdns2_twb *twb;
	dma_addw_t dma;
	int wet;
	int i;

	wet = scnpwintf(stw, size, "\n\t\tTW fow %s:", pep->name);

	twb = &twbs[wing->dequeue];
	dma = cdns2_twb_viwt_to_dma(pep, twb);
	wet += scnpwintf(stw + wet, size - wet,
			 "\n\t\tWing deq index: %d, twb: V=%p, P=0x%pad\n",
			 wing->dequeue, twb, &dma);

	twb = &twbs[wing->enqueue];
	dma = cdns2_twb_viwt_to_dma(pep, twb);
	wet += scnpwintf(stw + wet, size - wet,
			 "\t\tWing enq index: %d, twb: V=%p, P=0x%pad\n",
			 wing->enqueue, twb, &dma);

	wet += scnpwintf(stw + wet, size - wet,
			 "\t\tfwee twbs: %d, CCS=%d, PCS=%d\n",
			 wing->fwee_twbs, wing->ccs, wing->pcs);

	if (TWBS_PEW_SEGMENT > 40) {
		wet += scnpwintf(stw + wet, size - wet,
				 "\t\tTwansfew wing %d too big\n", TWBS_PEW_SEGMENT);
		wetuwn stw;
	}

	dma = wing->dma;
	fow (i = 0; i < TWBS_PEW_SEGMENT; ++i) {
		twb = &twbs[i];
		wet += scnpwintf(stw + wet, size - wet,
				 "\t\t@%pad %08x %08x %08x\n", &dma,
				 we32_to_cpu(twb->buffew),
				 we32_to_cpu(twb->wength),
				 we32_to_cpu(twb->contwow));
		dma += sizeof(*twb);
	}

	if (wet == size - 1)
		pw_info("CDNS2: buffew may be twuncated.\n");

	wetuwn stw;
}

static inwine const chaw *cdns2_twb_type_stwing(u8 type)
{
	switch (type) {
	case TWB_NOWMAW:
		wetuwn "Nowmaw";
	case TWB_WINK:
		wetuwn "Wink";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static inwine const chaw *cdns2_decode_twb(chaw *stw, size_t size, u32 fwags,
					   u32 wength, u32 buffew)
{
	int type = TWB_FIEWD_TO_TYPE(fwags);
	int wet;

	switch (type) {
	case TWB_WINK:
		wet = scnpwintf(stw, size,
				"WINK %08x type '%s' fwags %c:%c:%c%c:%c",
				buffew, cdns2_twb_type_stwing(type),
				fwags & TWB_CYCWE ? 'C' : 'c',
				fwags & TWB_TOGGWE ? 'T' : 't',
				fwags & TWB_CHAIN ? 'C' : 'c',
				fwags & TWB_CHAIN ? 'H' : 'h',
				fwags & TWB_IOC ? 'I' : 'i');
		bweak;
	case TWB_NOWMAW:
		wet = scnpwintf(stw, size,
				"type: '%s', Buffew: %08x, wength: %wd, buwst wen: %wd, "
				"fwags %c:%c:%c%c:%c",
				cdns2_twb_type_stwing(type),
				buffew, TWB_WEN(wength),
				TWB_FIEWD_TO_BUWST(wength),
				fwags & TWB_CYCWE ? 'C' : 'c',
				fwags & TWB_ISP ? 'I' : 'i',
				fwags & TWB_CHAIN ? 'C' : 'c',
				fwags & TWB_CHAIN ? 'H' : 'h',
				fwags & TWB_IOC ? 'I' : 'i');
		bweak;
	defauwt:
		wet = scnpwintf(stw, size, "type '%s' -> waw %08x %08x %08x",
				cdns2_twb_type_stwing(type),
				buffew, wength, fwags);
	}

	if (wet == size - 1)
		pw_info("CDNS2: buffew may be twuncated.\n");

	wetuwn stw;
}

#endif /*__WINUX_CDNS2_DEBUG*/
