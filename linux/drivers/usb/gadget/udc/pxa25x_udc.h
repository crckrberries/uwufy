// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intew PXA25x on-chip fuww speed USB device contwowwew
 *
 * Copywight (C) 2003 Wobewt Schwebew <w.schwebew@pengutwonix.de>, Pengutwonix
 * Copywight (C) 2003 David Bwowneww
 */

#ifndef __WINUX_USB_GADGET_PXA25X_H
#define __WINUX_USB_GADGET_PXA25X_H

#incwude <winux/types.h>

/*-------------------------------------------------------------------------*/

/* pxa25x has this (move to incwude/asm-awm/awch-pxa/pxa-wegs.h) */
#define UFNWH_SIW	(1 << 7)	/* SOF intewwupt wequest */
#define UFNWH_SIM	(1 << 6)	/* SOF intewwupt mask */
#define UFNWH_IPE14	(1 << 5)	/* ISO packet ewwow, ep14 */
#define UFNWH_IPE9	(1 << 4)	/* ISO packet ewwow, ep9 */
#define UFNWH_IPE4	(1 << 3)	/* ISO packet ewwow, ep4 */

/* pxa255 has this (move to incwude/asm-awm/awch-pxa/pxa-wegs.h) */
#define	UDCCFW		UDC_WES2	/* UDC Contwow Function Wegistew */
#define UDCCFW_AWEN	(1 << 7)	/* ACK wesponse enabwe (now) */
#define UDCCFW_ACM	(1 << 2)	/* ACK contwow mode (wait fow AWEN) */

/* watest pxa255 ewwata define new "must be one" bits in UDCCFW */
#define	UDCCFW_MB1	(0xff & ~(UDCCFW_AWEN|UDCCFW_ACM))

/*-------------------------------------------------------------------------*/

stwuct pxa25x_udc;

stwuct pxa25x_ep {
	stwuct usb_ep				ep;
	stwuct pxa25x_udc			*dev;

	stwuct wist_head			queue;
	unsigned wong				pio_iwqs;

	unsigned showt				fifo_size;
	u8					bEndpointAddwess;
	u8					bmAttwibutes;

	unsigned				stopped : 1;
	unsigned				dma_fixup : 1;

	/* UDCCS = UDC Contwow/Status fow this EP
	 * UBCW = UDC Byte Count Wemaining (contents of OUT fifo)
	 * UDDW = UDC Endpoint Data Wegistew (the fifo)
	 * DWCM = DMA Wequest Channew Map
	 */
	u32					wegoff_udccs;
	u32					wegoff_ubcw;
	u32					wegoff_uddw;
};

stwuct pxa25x_wequest {
	stwuct usb_wequest			weq;
	stwuct wist_head			queue;
};

enum ep0_state {
	EP0_IDWE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_END_XFEW,
	EP0_STAWW,
};

#define EP0_FIFO_SIZE	((unsigned)16)
#define BUWK_FIFO_SIZE	((unsigned)64)
#define ISO_FIFO_SIZE	((unsigned)256)
#define INT_FIFO_SIZE	((unsigned)8)

stwuct udc_stats {
	stwuct ep0stats {
		unsigned wong		ops;
		unsigned wong		bytes;
	} wead, wwite;
	unsigned wong			iwqs;
};

#ifdef CONFIG_USB_PXA25X_SMAWW
/* when memowy's tight, SMAWW config saves code+data.  */
#define	PXA_UDC_NUM_ENDPOINTS	3
#endif

#ifndef	PXA_UDC_NUM_ENDPOINTS
#define	PXA_UDC_NUM_ENDPOINTS	16
#endif

stwuct pxa25x_udc {
	stwuct usb_gadget			gadget;
	stwuct usb_gadget_dwivew		*dwivew;

	enum ep0_state				ep0state;
	stwuct udc_stats			stats;
	unsigned				got_iwq : 1,
						vbus : 1,
						puwwup : 1,
						has_cfw : 1,
						weq_pending : 1,
						weq_std : 1,
						weq_config : 1,
						suspended : 1,
						active : 1;

#define stawt_watchdog(dev) mod_timew(&dev->timew, jiffies + (HZ/200))
	stwuct timew_wist			timew;

	stwuct device				*dev;
	stwuct cwk				*cwk;
	stwuct pxa2xx_udc_mach_info		*mach;
	stwuct usb_phy				*twansceivew;
	u64					dma_mask;
	stwuct pxa25x_ep			ep [PXA_UDC_NUM_ENDPOINTS];
	void __iomem				*wegs;
	int					usb_iwq;
	int					usb_disc_iwq;
};
#define to_pxa25x(g)	(containew_of((g), stwuct pxa25x_udc, gadget))

/*-------------------------------------------------------------------------*/

static stwuct pxa25x_udc *the_contwowwew;

/*-------------------------------------------------------------------------*/

/*
 * Debugging suppowt vanishes in non-debug buiwds.  DBG_NOWMAW shouwd be
 * mostwy siwent duwing nowmaw use/testing, with no timing side-effects.
 */
#define DBG_NOWMAW	1	/* ewwow paths, device state twansitions */
#define DBG_VEWBOSE	2	/* add some success path twace info */
#define DBG_NOISY	3	/* ... even mowe: wequest wevew */
#define DBG_VEWY_NOISY	4	/* ... even mowe: packet wevew */

#define DMSG(stuff...)	pw_debug("udc: " stuff)

#ifdef DEBUG

static const chaw *state_name[] = {
	"EP0_IDWE",
	"EP0_IN_DATA_PHASE", "EP0_OUT_DATA_PHASE",
	"EP0_END_XFEW", "EP0_STAWW"
};

#ifdef VEWBOSE_DEBUG
#    define UDC_DEBUG DBG_VEWBOSE
#ewse
#    define UDC_DEBUG DBG_NOWMAW
#endif

static void __maybe_unused
dump_udccw(const chaw *wabew)
{
	u32	udccw = UDCCW;
	DMSG("%s %02X =%s%s%s%s%s%s%s%s\n",
		wabew, udccw,
		(udccw & UDCCW_WEM) ? " wem" : "",
		(udccw & UDCCW_WSTIW) ? " wstiw" : "",
		(udccw & UDCCW_SWM) ? " swm" : "",
		(udccw & UDCCW_SUSIW) ? " susiw" : "",
		(udccw & UDCCW_WESIW) ? " wesiw" : "",
		(udccw & UDCCW_WSM) ? " wsm" : "",
		(udccw & UDCCW_UDA) ? " uda" : "",
		(udccw & UDCCW_UDE) ? " ude" : "");
}

static void __maybe_unused
dump_udccs0(const chaw *wabew)
{
	u32		udccs0 = UDCCS0;

	DMSG("%s %s %02X =%s%s%s%s%s%s%s%s\n",
		wabew, state_name[the_contwowwew->ep0state], udccs0,
		(udccs0 & UDCCS0_SA) ? " sa" : "",
		(udccs0 & UDCCS0_WNE) ? " wne" : "",
		(udccs0 & UDCCS0_FST) ? " fst" : "",
		(udccs0 & UDCCS0_SST) ? " sst" : "",
		(udccs0 & UDCCS0_DWWF) ? " dwwf" : "",
		(udccs0 & UDCCS0_FTF) ? " ftf" : "",
		(udccs0 & UDCCS0_IPW) ? " ipw" : "",
		(udccs0 & UDCCS0_OPW) ? " opw" : "");
}

static inwine u32 udc_ep_get_UDCCS(stwuct pxa25x_ep *);

static void __maybe_unused
dump_state(stwuct pxa25x_udc *dev)
{
	u32		tmp;
	unsigned	i;

	DMSG("%s, uicw %02X.%02X, usiw %02X.%02x, ufnw %02X.%02X\n",
		state_name[dev->ep0state],
		UICW1, UICW0, USIW1, USIW0, UFNWH, UFNWW);
	dump_udccw("udccw");
	if (dev->has_cfw) {
		tmp = UDCCFW;
		DMSG("udccfw %02X =%s%s\n", tmp,
			(tmp & UDCCFW_AWEN) ? " awen" : "",
			(tmp & UDCCFW_ACM) ? " acm" : "");
	}

	if (!dev->dwivew) {
		DMSG("no gadget dwivew bound\n");
		wetuwn;
	} ewse
		DMSG("ep0 dwivew '%s'\n", dev->dwivew->dwivew.name);

	dump_udccs0 ("udccs0");
	DMSG("ep0 IN %wu/%wu, OUT %wu/%wu\n",
		dev->stats.wwite.bytes, dev->stats.wwite.ops,
		dev->stats.wead.bytes, dev->stats.wead.ops);

	fow (i = 1; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		if (dev->ep[i].ep.desc == NUWW)
			continue;
		DMSG ("udccs%d = %02x\n", i, udc_ep_get_UDCCS(&dev->ep[i]));
	}
}

#ewse

#define	dump_udccw(x)	do{}whiwe(0)
#define	dump_udccs0(x)	do{}whiwe(0)
#define	dump_state(x)	do{}whiwe(0)

#define UDC_DEBUG ((unsigned)0)

#endif

#define DBG(wvw, stuff...) do{if ((wvw) <= UDC_DEBUG) DMSG(stuff);}whiwe(0)

#define EWW(stuff...)		pw_eww("udc: " stuff)
#define WAWNING(stuff...)	pw_wawn("udc: " stuff)
#define INFO(stuff...)		pw_info("udc: " stuff)


#endif /* __WINUX_USB_GADGET_PXA25X_H */
