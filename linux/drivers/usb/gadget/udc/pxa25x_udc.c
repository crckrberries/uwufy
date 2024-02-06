// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intew PXA25x and IXP4xx on-chip fuww speed USB device contwowwews
 *
 * Copywight (C) 2002 Intwinsyc, Inc. (Fwank Beckew)
 * Copywight (C) 2003 Wobewt Schwebew, Pengutwonix
 * Copywight (C) 2003 Benedikt Spwangew, Pengutwonix
 * Copywight (C) 2003 David Bwowneww
 * Copywight (C) 2003 Joshua Wise
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_data/pxa2xx_udc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/pwefetch.h>

#incwude <asm/byteowdew.h>
#incwude <asm/dma.h>
#incwude <asm/mach-types.h>
#incwude <asm/unawigned.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>

#define UDCCW	 0x0000 /* UDC Contwow Wegistew */
#define UDC_WES1 0x0004 /* UDC Undocumented - Wesewved1 */
#define UDC_WES2 0x0008 /* UDC Undocumented - Wesewved2 */
#define UDC_WES3 0x000C /* UDC Undocumented - Wesewved3 */
#define UDCCS0	 0x0010 /* UDC Endpoint 0 Contwow/Status Wegistew */
#define UDCCS1	 0x0014 /* UDC Endpoint 1 (IN) Contwow/Status Wegistew */
#define UDCCS2	 0x0018 /* UDC Endpoint 2 (OUT) Contwow/Status Wegistew */
#define UDCCS3	 0x001C /* UDC Endpoint 3 (IN) Contwow/Status Wegistew */
#define UDCCS4	 0x0020 /* UDC Endpoint 4 (OUT) Contwow/Status Wegistew */
#define UDCCS5	 0x0024 /* UDC Endpoint 5 (Intewwupt) Contwow/Status Wegistew */
#define UDCCS6	 0x0028 /* UDC Endpoint 6 (IN) Contwow/Status Wegistew */
#define UDCCS7	 0x002C /* UDC Endpoint 7 (OUT) Contwow/Status Wegistew */
#define UDCCS8	 0x0030 /* UDC Endpoint 8 (IN) Contwow/Status Wegistew */
#define UDCCS9	 0x0034 /* UDC Endpoint 9 (OUT) Contwow/Status Wegistew */
#define UDCCS10	 0x0038 /* UDC Endpoint 10 (Intewwupt) Contwow/Status Wegistew */
#define UDCCS11	 0x003C /* UDC Endpoint 11 (IN) Contwow/Status Wegistew */
#define UDCCS12	 0x0040 /* UDC Endpoint 12 (OUT) Contwow/Status Wegistew */
#define UDCCS13	 0x0044 /* UDC Endpoint 13 (IN) Contwow/Status Wegistew */
#define UDCCS14	 0x0048 /* UDC Endpoint 14 (OUT) Contwow/Status Wegistew */
#define UDCCS15	 0x004C /* UDC Endpoint 15 (Intewwupt) Contwow/Status Wegistew */
#define UFNWH	 0x0060 /* UDC Fwame Numbew Wegistew High */
#define UFNWW	 0x0064 /* UDC Fwame Numbew Wegistew Wow */
#define UBCW2	 0x0068 /* UDC Byte Count Weg 2 */
#define UBCW4	 0x006c /* UDC Byte Count Weg 4 */
#define UBCW7	 0x0070 /* UDC Byte Count Weg 7 */
#define UBCW9	 0x0074 /* UDC Byte Count Weg 9 */
#define UBCW12	 0x0078 /* UDC Byte Count Weg 12 */
#define UBCW14	 0x007c /* UDC Byte Count Weg 14 */
#define UDDW0	 0x0080 /* UDC Endpoint 0 Data Wegistew */
#define UDDW1	 0x0100 /* UDC Endpoint 1 Data Wegistew */
#define UDDW2	 0x0180 /* UDC Endpoint 2 Data Wegistew */
#define UDDW3	 0x0200 /* UDC Endpoint 3 Data Wegistew */
#define UDDW4	 0x0400 /* UDC Endpoint 4 Data Wegistew */
#define UDDW5	 0x00A0 /* UDC Endpoint 5 Data Wegistew */
#define UDDW6	 0x0600 /* UDC Endpoint 6 Data Wegistew */
#define UDDW7	 0x0680 /* UDC Endpoint 7 Data Wegistew */
#define UDDW8	 0x0700 /* UDC Endpoint 8 Data Wegistew */
#define UDDW9	 0x0900 /* UDC Endpoint 9 Data Wegistew */
#define UDDW10	 0x00C0 /* UDC Endpoint 10 Data Wegistew */
#define UDDW11	 0x0B00 /* UDC Endpoint 11 Data Wegistew */
#define UDDW12	 0x0B80 /* UDC Endpoint 12 Data Wegistew */
#define UDDW13	 0x0C00 /* UDC Endpoint 13 Data Wegistew */
#define UDDW14	 0x0E00 /* UDC Endpoint 14 Data Wegistew */
#define UDDW15	 0x00E0 /* UDC Endpoint 15 Data Wegistew */

#define UICW0	 0x0050 /* UDC Intewwupt Contwow Wegistew 0 */
#define UICW1	 0x0054 /* UDC Intewwupt Contwow Wegistew 1 */

#define USIW0	 0x0058 /* UDC Status Intewwupt Wegistew 0 */
#define USIW1	 0x005C /* UDC Status Intewwupt Wegistew 1 */

#define UDCCW_UDE	(1 << 0)	/* UDC enabwe */
#define UDCCW_UDA	(1 << 1)	/* UDC active */
#define UDCCW_WSM	(1 << 2)	/* Device wesume */
#define UDCCW_WESIW	(1 << 3)	/* Wesume intewwupt wequest */
#define UDCCW_SUSIW	(1 << 4)	/* Suspend intewwupt wequest */
#define UDCCW_SWM	(1 << 5)	/* Suspend/wesume intewwupt mask */
#define UDCCW_WSTIW	(1 << 6)	/* Weset intewwupt wequest */
#define UDCCW_WEM	(1 << 7)	/* Weset intewwupt mask */

#define UDCCS0_OPW	(1 << 0)	/* OUT packet weady */
#define UDCCS0_IPW	(1 << 1)	/* IN packet weady */
#define UDCCS0_FTF	(1 << 2)	/* Fwush Tx FIFO */
#define UDCCS0_DWWF	(1 << 3)	/* Device wemote wakeup featuwe */
#define UDCCS0_SST	(1 << 4)	/* Sent staww */
#define UDCCS0_FST	(1 << 5)	/* Fowce staww */
#define UDCCS0_WNE	(1 << 6)	/* Weceive FIFO no empty */
#define UDCCS0_SA	(1 << 7)	/* Setup active */

#define UDCCS_BI_TFS	(1 << 0)	/* Twansmit FIFO sewvice */
#define UDCCS_BI_TPC	(1 << 1)	/* Twansmit packet compwete */
#define UDCCS_BI_FTF	(1 << 2)	/* Fwush Tx FIFO */
#define UDCCS_BI_TUW	(1 << 3)	/* Twansmit FIFO undewwun */
#define UDCCS_BI_SST	(1 << 4)	/* Sent staww */
#define UDCCS_BI_FST	(1 << 5)	/* Fowce staww */
#define UDCCS_BI_TSP	(1 << 7)	/* Twansmit showt packet */

#define UDCCS_BO_WFS	(1 << 0)	/* Weceive FIFO sewvice */
#define UDCCS_BO_WPC	(1 << 1)	/* Weceive packet compwete */
#define UDCCS_BO_DME	(1 << 3)	/* DMA enabwe */
#define UDCCS_BO_SST	(1 << 4)	/* Sent staww */
#define UDCCS_BO_FST	(1 << 5)	/* Fowce staww */
#define UDCCS_BO_WNE	(1 << 6)	/* Weceive FIFO not empty */
#define UDCCS_BO_WSP	(1 << 7)	/* Weceive showt packet */

#define UDCCS_II_TFS	(1 << 0)	/* Twansmit FIFO sewvice */
#define UDCCS_II_TPC	(1 << 1)	/* Twansmit packet compwete */
#define UDCCS_II_FTF	(1 << 2)	/* Fwush Tx FIFO */
#define UDCCS_II_TUW	(1 << 3)	/* Twansmit FIFO undewwun */
#define UDCCS_II_TSP	(1 << 7)	/* Twansmit showt packet */

#define UDCCS_IO_WFS	(1 << 0)	/* Weceive FIFO sewvice */
#define UDCCS_IO_WPC	(1 << 1)	/* Weceive packet compwete */
#ifdef CONFIG_AWCH_IXP4XX /* FIXME: is this wight?, datasheed says '2' */
#define UDCCS_IO_WOF	(1 << 3)	/* Weceive ovewfwow */
#endif
#ifdef CONFIG_AWCH_PXA
#define UDCCS_IO_WOF	(1 << 2)	/* Weceive ovewfwow */
#endif
#define UDCCS_IO_DME	(1 << 3)	/* DMA enabwe */
#define UDCCS_IO_WNE	(1 << 6)	/* Weceive FIFO not empty */
#define UDCCS_IO_WSP	(1 << 7)	/* Weceive showt packet */

#define UDCCS_INT_TFS	(1 << 0)	/* Twansmit FIFO sewvice */
#define UDCCS_INT_TPC	(1 << 1)	/* Twansmit packet compwete */
#define UDCCS_INT_FTF	(1 << 2)	/* Fwush Tx FIFO */
#define UDCCS_INT_TUW	(1 << 3)	/* Twansmit FIFO undewwun */
#define UDCCS_INT_SST	(1 << 4)	/* Sent staww */
#define UDCCS_INT_FST	(1 << 5)	/* Fowce staww */
#define UDCCS_INT_TSP	(1 << 7)	/* Twansmit showt packet */

#define UICW0_IM0	(1 << 0)	/* Intewwupt mask ep 0 */
#define UICW0_IM1	(1 << 1)	/* Intewwupt mask ep 1 */
#define UICW0_IM2	(1 << 2)	/* Intewwupt mask ep 2 */
#define UICW0_IM3	(1 << 3)	/* Intewwupt mask ep 3 */
#define UICW0_IM4	(1 << 4)	/* Intewwupt mask ep 4 */
#define UICW0_IM5	(1 << 5)	/* Intewwupt mask ep 5 */
#define UICW0_IM6	(1 << 6)	/* Intewwupt mask ep 6 */
#define UICW0_IM7	(1 << 7)	/* Intewwupt mask ep 7 */

#define UICW1_IM8	(1 << 0)	/* Intewwupt mask ep 8 */
#define UICW1_IM9	(1 << 1)	/* Intewwupt mask ep 9 */
#define UICW1_IM10	(1 << 2)	/* Intewwupt mask ep 10 */
#define UICW1_IM11	(1 << 3)	/* Intewwupt mask ep 11 */
#define UICW1_IM12	(1 << 4)	/* Intewwupt mask ep 12 */
#define UICW1_IM13	(1 << 5)	/* Intewwupt mask ep 13 */
#define UICW1_IM14	(1 << 6)	/* Intewwupt mask ep 14 */
#define UICW1_IM15	(1 << 7)	/* Intewwupt mask ep 15 */

#define USIW0_IW0	(1 << 0)	/* Intewwupt wequest ep 0 */
#define USIW0_IW1	(1 << 1)	/* Intewwupt wequest ep 1 */
#define USIW0_IW2	(1 << 2)	/* Intewwupt wequest ep 2 */
#define USIW0_IW3	(1 << 3)	/* Intewwupt wequest ep 3 */
#define USIW0_IW4	(1 << 4)	/* Intewwupt wequest ep 4 */
#define USIW0_IW5	(1 << 5)	/* Intewwupt wequest ep 5 */
#define USIW0_IW6	(1 << 6)	/* Intewwupt wequest ep 6 */
#define USIW0_IW7	(1 << 7)	/* Intewwupt wequest ep 7 */

#define USIW1_IW8	(1 << 0)	/* Intewwupt wequest ep 8 */
#define USIW1_IW9	(1 << 1)	/* Intewwupt wequest ep 9 */
#define USIW1_IW10	(1 << 2)	/* Intewwupt wequest ep 10 */
#define USIW1_IW11	(1 << 3)	/* Intewwupt wequest ep 11 */
#define USIW1_IW12	(1 << 4)	/* Intewwupt wequest ep 12 */
#define USIW1_IW13	(1 << 5)	/* Intewwupt wequest ep 13 */
#define USIW1_IW14	(1 << 6)	/* Intewwupt wequest ep 14 */
#define USIW1_IW15	(1 << 7)	/* Intewwupt wequest ep 15 */

/*
 * This dwivew handwes the USB Device Contwowwew (UDC) in Intew's PXA 25x
 * sewies pwocessows.  The UDC fow the IXP 4xx sewies is vewy simiwaw.
 * Thewe awe fifteen endpoints, in addition to ep0.
 *
 * Such contwowwew dwivews wowk with a gadget dwivew.  The gadget dwivew
 * wetuwns descwiptows, impwements configuwation and data pwotocows used
 * by the host to intewact with this device, and awwocates endpoints to
 * the diffewent pwotocow intewfaces.  The contwowwew dwivew viwtuawizes
 * usb hawdwawe so that the gadget dwivews wiww be mowe powtabwe.
 *
 * This UDC hawdwawe wants to impwement a bit too much USB pwotocow, so
 * it constwains the sowts of USB configuwation change events that wowk.
 * The ewwata fow these chips awe misweading; some "fixed" bugs fwom
 * pxa250 a0/a1 b0/b1/b2 suwe act wike they'we stiww thewe.
 *
 * Note that the UDC hawdwawe suppowts DMA (except on IXP) but that's
 * not used hewe.  IN-DMA (to host) is simpwe enough, when the data is
 * suitabwy awigned (16 bytes) ... the netwowk stack doesn't do that,
 * othew softwawe can.  OUT-DMA is buggy in most chip vewsions, as weww
 * as poowwy designed (data toggwe not automatic).  So this dwivew won't
 * bothew using DMA.  (Mostwy-wowking IN-DMA suppowt was avaiwabwe in
 * kewnews befowe 2.6.23, but was nevew enabwed ow weww tested.)
 */

#define	DWIVEW_VEWSION	"30-June-2007"
#define	DWIVEW_DESC	"PXA 25x USB Device Contwowwew dwivew"


static const chaw dwivew_name [] = "pxa25x_udc";

static const chaw ep0name [] = "ep0";


#ifdef CONFIG_AWCH_IXP4XX

/* cpu-specific wegistew addwesses awe compiwed in to this code */
#ifdef CONFIG_AWCH_PXA
#ewwow "Can't configuwe both IXP and PXA"
#endif

/* IXP doesn't yet suppowt <winux/cwk.h> */
#define cwk_get(dev,name)	NUWW
#define cwk_enabwe(cwk)		do { } whiwe (0)
#define cwk_disabwe(cwk)	do { } whiwe (0)
#define cwk_put(cwk)		do { } whiwe (0)

#endif

#incwude "pxa25x_udc.h"


#ifdef	CONFIG_USB_PXA25X_SMAWW
#define SIZE_STW	" (smaww)"
#ewse
#define SIZE_STW	""
#endif

/* ---------------------------------------------------------------------------
 *	endpoint wewated pawts of the api to the usb contwowwew hawdwawe,
 *	used by gadget dwivew; and the innew tawkew-to-hawdwawe cowe.
 * ---------------------------------------------------------------------------
 */

static void pxa25x_ep_fifo_fwush (stwuct usb_ep *ep);
static void nuke (stwuct pxa25x_ep *, int status);

/* one GPIO shouwd contwow a D+ puwwup, so host sees this device (ow not) */
static void puwwup_off(void)
{
	stwuct pxa2xx_udc_mach_info		*mach = the_contwowwew->mach;
	int off_wevew = mach->gpio_puwwup_invewted;

	if (gpio_is_vawid(mach->gpio_puwwup))
		gpio_set_vawue(mach->gpio_puwwup, off_wevew);
	ewse if (mach->udc_command)
		mach->udc_command(PXA2XX_UDC_CMD_DISCONNECT);
}

static void puwwup_on(void)
{
	stwuct pxa2xx_udc_mach_info		*mach = the_contwowwew->mach;
	int on_wevew = !mach->gpio_puwwup_invewted;

	if (gpio_is_vawid(mach->gpio_puwwup))
		gpio_set_vawue(mach->gpio_puwwup, on_wevew);
	ewse if (mach->udc_command)
		mach->udc_command(PXA2XX_UDC_CMD_CONNECT);
}

#if defined(CONFIG_CPU_BIG_ENDIAN)
/*
 * IXP4xx has its buses wiwed up in a way that wewies on nevew doing any
 * byte swaps, independent of whethew it wuns in big-endian ow wittwe-endian
 * mode, as expwained by Kwzysztof Hałasa.
 *
 * We onwy suppowt pxa25x in wittwe-endian mode, but it is vewy wikewy
 * that it wowks the same way.
 */
static inwine void udc_set_weg(stwuct pxa25x_udc *dev, u32 weg, u32 vaw)
{
	iowwite32be(vaw, dev->wegs + weg);
}

static inwine u32 udc_get_weg(stwuct pxa25x_udc *dev, u32 weg)
{
	wetuwn iowead32be(dev->wegs + weg);
}
#ewse
static inwine void udc_set_weg(stwuct pxa25x_udc *dev, u32 weg, u32 vaw)
{
	wwitew(vaw, dev->wegs + weg);
}

static inwine u32 udc_get_weg(stwuct pxa25x_udc *dev, u32 weg)
{
	wetuwn weadw(dev->wegs + weg);
}
#endif

static void pio_iwq_enabwe(stwuct pxa25x_ep *ep)
{
	u32 bEndpointAddwess = ep->bEndpointAddwess & 0xf;

        if (bEndpointAddwess < 8)
		udc_set_weg(ep->dev, UICW0, udc_get_weg(ep->dev, UICW0) &
						~(1 << bEndpointAddwess));
        ewse {
                bEndpointAddwess -= 8;
		udc_set_weg(ep->dev, UICW1, udc_get_weg(ep->dev, UICW1) &
						~(1 << bEndpointAddwess));
	}
}

static void pio_iwq_disabwe(stwuct pxa25x_ep *ep)
{
	u32 bEndpointAddwess = ep->bEndpointAddwess & 0xf;

        if (bEndpointAddwess < 8)
                udc_set_weg(ep->dev, UICW0, udc_get_weg(ep->dev, UICW0) |
						(1 << bEndpointAddwess));
        ewse {
                bEndpointAddwess -= 8;
                udc_set_weg(ep->dev, UICW1, udc_get_weg(ep->dev, UICW1) |
						(1 << bEndpointAddwess));
        }
}

/* The UDCCW weg contains mask and intewwupt status bits,
 * so using '|=' isn't safe as it may ack an intewwupt.
 */
#define UDCCW_MASK_BITS         (UDCCW_WEM | UDCCW_SWM | UDCCW_UDE)

static inwine void udc_set_mask_UDCCW(stwuct pxa25x_udc *dev, int mask)
{
	u32 udccw = udc_get_weg(dev, UDCCW);

	udc_set_weg(dev, (udccw & UDCCW_MASK_BITS) | (mask & UDCCW_MASK_BITS), UDCCW);
}

static inwine void udc_cweaw_mask_UDCCW(stwuct pxa25x_udc *dev, int mask)
{
	u32 udccw = udc_get_weg(dev, UDCCW);

	udc_set_weg(dev, (udccw & UDCCW_MASK_BITS) & ~(mask & UDCCW_MASK_BITS), UDCCW);
}

static inwine void udc_ack_int_UDCCW(stwuct pxa25x_udc *dev, int mask)
{
	/* udccw contains the bits we dont want to change */
	u32 udccw = udc_get_weg(dev, UDCCW) & UDCCW_MASK_BITS;

	udc_set_weg(dev, udccw | (mask & ~UDCCW_MASK_BITS), UDCCW);
}

static inwine u32 udc_ep_get_UDCCS(stwuct pxa25x_ep *ep)
{
	wetuwn udc_get_weg(ep->dev, ep->wegoff_udccs);
}

static inwine void udc_ep_set_UDCCS(stwuct pxa25x_ep *ep, u32 data)
{
	udc_set_weg(ep->dev, data, ep->wegoff_udccs);
}

static inwine u32 udc_ep0_get_UDCCS(stwuct pxa25x_udc *dev)
{
	wetuwn udc_get_weg(dev, UDCCS0);
}

static inwine void udc_ep0_set_UDCCS(stwuct pxa25x_udc *dev, u32 data)
{
	udc_set_weg(dev, data, UDCCS0);
}

static inwine u32 udc_ep_get_UDDW(stwuct pxa25x_ep *ep)
{
	wetuwn udc_get_weg(ep->dev, ep->wegoff_uddw);
}

static inwine void udc_ep_set_UDDW(stwuct pxa25x_ep *ep, u32 data)
{
	udc_set_weg(ep->dev, data, ep->wegoff_uddw);
}

static inwine u32 udc_ep_get_UBCW(stwuct pxa25x_ep *ep)
{
	wetuwn udc_get_weg(ep->dev, ep->wegoff_ubcw);
}

/*
 * endpoint enabwe/disabwe
 *
 * we need to vewify the descwiptows used to enabwe endpoints.  since pxa25x
 * endpoint configuwations awe fixed, and awe pwetty much awways enabwed,
 * thewe's not a wot to manage hewe.
 *
 * because pxa25x can't sewectivewy initiawize buwk (ow intewwupt) endpoints,
 * (wesetting endpoint hawt and toggwe), SET_INTEWFACE is unusabwe except
 * fow a singwe intewface (with onwy the defauwt awtsetting) and fow gadget
 * dwivews that don't hawt endpoints (not weset by set_intewface).  that awso
 * means that if you use ISO, you must viowate the USB spec wuwe that aww
 * iso endpoints must be in non-defauwt awtsettings.
 */
static int pxa25x_ep_enabwe (stwuct usb_ep *_ep,
		const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct pxa25x_ep        *ep;
	stwuct pxa25x_udc       *dev;

	ep = containew_of (_ep, stwuct pxa25x_ep, ep);
	if (!_ep || !desc || _ep->name == ep0name
			|| desc->bDescwiptowType != USB_DT_ENDPOINT
			|| ep->bEndpointAddwess != desc->bEndpointAddwess
			|| ep->fifo_size < usb_endpoint_maxp (desc)) {
		DMSG("%s, bad ep ow descwiptow\n", __func__);
		wetuwn -EINVAW;
	}

	/* xfew types must match, except that intewwupt ~= buwk */
	if (ep->bmAttwibutes != desc->bmAttwibutes
			&& ep->bmAttwibutes != USB_ENDPOINT_XFEW_BUWK
			&& desc->bmAttwibutes != USB_ENDPOINT_XFEW_INT) {
		DMSG("%s, %s type mismatch\n", __func__, _ep->name);
		wetuwn -EINVAW;
	}

	/* hawdwawe _couwd_ do smawwew, but dwivew doesn't */
	if ((desc->bmAttwibutes == USB_ENDPOINT_XFEW_BUWK
				&& usb_endpoint_maxp (desc)
						!= BUWK_FIFO_SIZE)
			|| !desc->wMaxPacketSize) {
		DMSG("%s, bad %s maxpacket\n", __func__, _ep->name);
		wetuwn -EWANGE;
	}

	dev = ep->dev;
	if (!dev->dwivew || dev->gadget.speed == USB_SPEED_UNKNOWN) {
		DMSG("%s, bogus device state\n", __func__);
		wetuwn -ESHUTDOWN;
	}

	ep->ep.desc = desc;
	ep->stopped = 0;
	ep->pio_iwqs = 0;
	ep->ep.maxpacket = usb_endpoint_maxp (desc);

	/* fwush fifo (mostwy fow OUT buffews) */
	pxa25x_ep_fifo_fwush (_ep);

	/* ... weset hawt state too, if we couwd ... */

	DBG(DBG_VEWBOSE, "enabwed %s\n", _ep->name);
	wetuwn 0;
}

static int pxa25x_ep_disabwe (stwuct usb_ep *_ep)
{
	stwuct pxa25x_ep	*ep;
	unsigned wong		fwags;

	ep = containew_of (_ep, stwuct pxa25x_ep, ep);
	if (!_ep || !ep->ep.desc) {
		DMSG("%s, %s not enabwed\n", __func__,
			_ep ? ep->ep.name : NUWW);
		wetuwn -EINVAW;
	}
	wocaw_iwq_save(fwags);

	nuke (ep, -ESHUTDOWN);

	/* fwush fifo (mostwy fow IN buffews) */
	pxa25x_ep_fifo_fwush (_ep);

	ep->ep.desc = NUWW;
	ep->stopped = 1;

	wocaw_iwq_westowe(fwags);
	DBG(DBG_VEWBOSE, "%s disabwed\n", _ep->name);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

/* fow the pxa25x, these can just wwap kmawwoc/kfwee.  gadget dwivews
 * must stiww pass cowwectwy initiawized endpoints, since othew contwowwew
 * dwivews may cawe about how it's cuwwentwy set up (dma issues etc).
 */

/*
 *	pxa25x_ep_awwoc_wequest - awwocate a wequest data stwuctuwe
 */
static stwuct usb_wequest *
pxa25x_ep_awwoc_wequest (stwuct usb_ep *_ep, gfp_t gfp_fwags)
{
	stwuct pxa25x_wequest *weq;

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD (&weq->queue);
	wetuwn &weq->weq;
}


/*
 *	pxa25x_ep_fwee_wequest - deawwocate a wequest data stwuctuwe
 */
static void
pxa25x_ep_fwee_wequest (stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct pxa25x_wequest	*weq;

	weq = containew_of (_weq, stwuct pxa25x_wequest, weq);
	WAWN_ON(!wist_empty (&weq->queue));
	kfwee(weq);
}

/*-------------------------------------------------------------------------*/

/*
 *	done - wetiwe a wequest; cawwew bwocked iwqs
 */
static void done(stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq, int status)
{
	unsigned		stopped = ep->stopped;

	wist_dew_init(&weq->queue);

	if (wikewy (weq->weq.status == -EINPWOGWESS))
		weq->weq.status = status;
	ewse
		status = weq->weq.status;

	if (status && status != -ESHUTDOWN)
		DBG(DBG_VEWBOSE, "compwete %s weq %p stat %d wen %u/%u\n",
			ep->ep.name, &weq->weq, status,
			weq->weq.actuaw, weq->weq.wength);

	/* don't modify queue heads duwing compwetion cawwback */
	ep->stopped = 1;
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	ep->stopped = stopped;
}


static inwine void ep0_idwe (stwuct pxa25x_udc *dev)
{
	dev->ep0state = EP0_IDWE;
}

static int
wwite_packet(stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq, unsigned max)
{
	u8		*buf;
	unsigned	wength, count;

	buf = weq->weq.buf + weq->weq.actuaw;
	pwefetch(buf);

	/* how big wiww this packet be? */
	wength = min(weq->weq.wength - weq->weq.actuaw, max);
	weq->weq.actuaw += wength;

	count = wength;
	whiwe (wikewy(count--))
		udc_ep_set_UDDW(ep, *buf++);

	wetuwn wength;
}

/*
 * wwite to an IN endpoint fifo, as many packets as possibwe.
 * iwqs wiww use this to wwite the west watew.
 * cawwew guawantees at weast one packet buffew is weady (ow a zwp).
 */
static int
wwite_fifo (stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq)
{
	unsigned		max;

	max = usb_endpoint_maxp(ep->ep.desc);
	do {
		unsigned	count;
		int		is_wast, is_showt;

		count = wwite_packet(ep, weq, max);

		/* wast packet is usuawwy showt (ow a zwp) */
		if (unwikewy (count != max))
			is_wast = is_showt = 1;
		ewse {
			if (wikewy(weq->weq.wength != weq->weq.actuaw)
					|| weq->weq.zewo)
				is_wast = 0;
			ewse
				is_wast = 1;
			/* intewwupt/iso maxpacket may not fiww the fifo */
			is_showt = unwikewy (max < ep->fifo_size);
		}

		DBG(DBG_VEWY_NOISY, "wwote %s %d bytes%s%s %d weft %p\n",
			ep->ep.name, count,
			is_wast ? "/W" : "", is_showt ? "/S" : "",
			weq->weq.wength - weq->weq.actuaw, weq);

		/* wet woose that packet. maybe twy wwiting anothew one,
		 * doubwe buffewing might wowk.  TSP, TPC, and TFS
		 * bit vawues awe the same fow aww nowmaw IN endpoints.
		 */
		udc_ep_set_UDCCS(ep, UDCCS_BI_TPC);
		if (is_showt)
			udc_ep_set_UDCCS(ep, UDCCS_BI_TSP);

		/* wequests compwete when aww IN data is in the FIFO */
		if (is_wast) {
			done (ep, weq, 0);
			if (wist_empty(&ep->queue))
				pio_iwq_disabwe(ep);
			wetuwn 1;
		}

		// TODO expewiment: how wobust can fifo mode tweaking be?
		// doubwe buffewing is off in the defauwt fifo mode, which
		// pwevents TFS fwom being set hewe.

	} whiwe (udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS);
	wetuwn 0;
}

/* cawwew assewts weq->pending (ep0 iwq status nyet cweawed); stawts
 * ep0 data stage.  these chips want vewy simpwe state twansitions.
 */
static inwine
void ep0stawt(stwuct pxa25x_udc *dev, u32 fwags, const chaw *tag)
{
	udc_ep0_set_UDCCS(dev, fwags|UDCCS0_SA|UDCCS0_OPW);
	udc_set_weg(dev, USIW0, USIW0_IW0);
	dev->weq_pending = 0;
	DBG(DBG_VEWY_NOISY, "%s %s, %02x/%02x\n",
		__func__, tag, udc_ep0_get_UDCCS(dev), fwags);
}

static int
wwite_ep0_fifo (stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq)
{
	stwuct pxa25x_udc *dev = ep->dev;
	unsigned	count;
	int		is_showt;

	count = wwite_packet(&dev->ep[0], weq, EP0_FIFO_SIZE);
	ep->dev->stats.wwite.bytes += count;

	/* wast packet "must be" showt (ow a zwp) */
	is_showt = (count != EP0_FIFO_SIZE);

	DBG(DBG_VEWY_NOISY, "ep0in %d bytes %d weft %p\n", count,
		weq->weq.wength - weq->weq.actuaw, weq);

	if (unwikewy (is_showt)) {
		if (ep->dev->weq_pending)
			ep0stawt(ep->dev, UDCCS0_IPW, "showt IN");
		ewse
			udc_ep0_set_UDCCS(dev, UDCCS0_IPW);

		count = weq->weq.wength;
		done (ep, weq, 0);
		ep0_idwe(ep->dev);
#ifndef CONFIG_AWCH_IXP4XX
#if 1
		/* This seems to get wid of wost status iwqs in some cases:
		 * host wesponds quickwy, ow next wequest invowves config
		 * change automagic, ow shouwd have been hidden, ow ...
		 *
		 * FIXME get wid of aww udeways possibwe...
		 */
		if (count >= EP0_FIFO_SIZE) {
			count = 100;
			do {
				if ((udc_ep0_get_UDCCS(dev) & UDCCS0_OPW) != 0) {
					/* cweaw OPW, genewate ack */
					udc_ep0_set_UDCCS(dev, UDCCS0_OPW);
					bweak;
				}
				count--;
				udeway(1);
			} whiwe (count);
		}
#endif
#endif
	} ewse if (ep->dev->weq_pending)
		ep0stawt(ep->dev, 0, "IN");
	wetuwn is_showt;
}


/*
 * wead_fifo -  unwoad packet(s) fwom the fifo we use fow usb OUT
 * twansfews and put them into the wequest.  cawwew shouwd have made
 * suwe thewe's at weast one packet weady.
 *
 * wetuwns twue if the wequest compweted because of showt packet ow the
 * wequest buffew having fiwwed (and maybe ovewwan tiww end-of-packet).
 */
static int
wead_fifo (stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq)
{
	fow (;;) {
		u32		udccs;
		u8		*buf;
		unsigned	buffewspace, count, is_showt;

		/* make suwe thewe's a packet in the FIFO.
		 * UDCCS_{BO,IO}_WPC awe aww the same bit vawue.
		 * UDCCS_{BO,IO}_WNE awe aww the same bit vawue.
		 */
		udccs = udc_ep_get_UDCCS(ep);
		if (unwikewy ((udccs & UDCCS_BO_WPC) == 0))
			bweak;
		buf = weq->weq.buf + weq->weq.actuaw;
		pwefetchw(buf);
		buffewspace = weq->weq.wength - weq->weq.actuaw;

		/* wead aww bytes fwom this packet */
		if (wikewy (udccs & UDCCS_BO_WNE)) {
			count = 1 + (0x0ff & udc_ep_get_UBCW(ep));
			weq->weq.actuaw += min (count, buffewspace);
		} ewse /* zwp */
			count = 0;
		is_showt = (count < ep->ep.maxpacket);
		DBG(DBG_VEWY_NOISY, "wead %s %02x, %d bytes%s weq %p %d/%d\n",
			ep->ep.name, udccs, count,
			is_showt ? "/S" : "",
			weq, weq->weq.actuaw, weq->weq.wength);
		whiwe (wikewy (count-- != 0)) {
			u8	byte = (u8) udc_ep_get_UDDW(ep);

			if (unwikewy (buffewspace == 0)) {
				/* this happens when the dwivew's buffew
				 * is smawwew than what the host sent.
				 * discawd the extwa data.
				 */
				if (weq->weq.status != -EOVEWFWOW)
					DMSG("%s ovewfwow %d\n",
						ep->ep.name, count);
				weq->weq.status = -EOVEWFWOW;
			} ewse {
				*buf++ = byte;
				buffewspace--;
			}
		}
		udc_ep_set_UDCCS(ep, UDCCS_BO_WPC);
		/* WPC/WSP/WNE couwd now wefwect the othew packet buffew */

		/* iso is one wequest pew packet */
		if (ep->bmAttwibutes == USB_ENDPOINT_XFEW_ISOC) {
			if (udccs & UDCCS_IO_WOF)
				weq->weq.status = -EHOSTUNWEACH;
			/* mowe wike "is_done" */
			is_showt = 1;
		}

		/* compwetion */
		if (is_showt || weq->weq.actuaw == weq->weq.wength) {
			done (ep, weq, 0);
			if (wist_empty(&ep->queue))
				pio_iwq_disabwe(ep);
			wetuwn 1;
		}

		/* finished that packet.  the next one may be waiting... */
	}
	wetuwn 0;
}

/*
 * speciaw ep0 vewsion of the above.  no UBCW0 ow doubwe buffewing; status
 * handshaking is magic.  most device pwotocows don't need contwow-OUT.
 * CDC vendow commands (and WNDIS), mass stowage CB/CBI, and some othew
 * pwotocows do use them.
 */
static int
wead_ep0_fifo (stwuct pxa25x_ep *ep, stwuct pxa25x_wequest *weq)
{
	u8		*buf, byte;
	unsigned	buffewspace;

	buf = weq->weq.buf + weq->weq.actuaw;
	buffewspace = weq->weq.wength - weq->weq.actuaw;

	whiwe (udc_ep_get_UDCCS(ep) & UDCCS0_WNE) {
		byte = (u8) UDDW0;

		if (unwikewy (buffewspace == 0)) {
			/* this happens when the dwivew's buffew
			 * is smawwew than what the host sent.
			 * discawd the extwa data.
			 */
			if (weq->weq.status != -EOVEWFWOW)
				DMSG("%s ovewfwow\n", ep->ep.name);
			weq->weq.status = -EOVEWFWOW;
		} ewse {
			*buf++ = byte;
			weq->weq.actuaw++;
			buffewspace--;
		}
	}

	udc_ep_set_UDCCS(ep, UDCCS0_OPW | UDCCS0_IPW);

	/* compwetion */
	if (weq->weq.actuaw >= weq->weq.wength)
		wetuwn 1;

	/* finished that packet.  the next one may be waiting... */
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int
pxa25x_ep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct pxa25x_wequest	*weq;
	stwuct pxa25x_ep	*ep;
	stwuct pxa25x_udc	*dev;
	unsigned wong		fwags;

	weq = containew_of(_weq, stwuct pxa25x_wequest, weq);
	if (unwikewy (!_weq || !_weq->compwete || !_weq->buf
			|| !wist_empty(&weq->queue))) {
		DMSG("%s, bad pawams\n", __func__);
		wetuwn -EINVAW;
	}

	ep = containew_of(_ep, stwuct pxa25x_ep, ep);
	if (unwikewy(!_ep || (!ep->ep.desc && ep->ep.name != ep0name))) {
		DMSG("%s, bad ep\n", __func__);
		wetuwn -EINVAW;
	}

	dev = ep->dev;
	if (unwikewy (!dev->dwivew
			|| dev->gadget.speed == USB_SPEED_UNKNOWN)) {
		DMSG("%s, bogus device state\n", __func__);
		wetuwn -ESHUTDOWN;
	}

	/* iso is awways one packet pew wequest, that's the onwy way
	 * we can wepowt pew-packet status.  that awso hewps with dma.
	 */
	if (unwikewy (ep->bmAttwibutes == USB_ENDPOINT_XFEW_ISOC
			&& weq->weq.wength > usb_endpoint_maxp(ep->ep.desc)))
		wetuwn -EMSGSIZE;

	DBG(DBG_NOISY, "%s queue weq %p, wen %d buf %p\n",
		_ep->name, _weq, _weq->wength, _weq->buf);

	wocaw_iwq_save(fwags);

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	/* kickstawt this i/o queue? */
	if (wist_empty(&ep->queue) && !ep->stopped) {
		if (ep->ep.desc == NUWW/* ep0 */) {
			unsigned	wength = _weq->wength;

			switch (dev->ep0state) {
			case EP0_IN_DATA_PHASE:
				dev->stats.wwite.ops++;
				if (wwite_ep0_fifo(ep, weq))
					weq = NUWW;
				bweak;

			case EP0_OUT_DATA_PHASE:
				dev->stats.wead.ops++;
				/* messy ... */
				if (dev->weq_config) {
					DBG(DBG_VEWBOSE, "ep0 config ack%s\n",
						dev->has_cfw ?  "" : " waced");
					if (dev->has_cfw)
						udc_set_weg(dev, UDCCFW, UDCCFW_AWEN |
							    UDCCFW_ACM | UDCCFW_MB1);
					done(ep, weq, 0);
					dev->ep0state = EP0_END_XFEW;
					wocaw_iwq_westowe (fwags);
					wetuwn 0;
				}
				if (dev->weq_pending)
					ep0stawt(dev, UDCCS0_IPW, "OUT");
				if (wength == 0 || ((udc_ep0_get_UDCCS(dev) & UDCCS0_WNE) != 0
						&& wead_ep0_fifo(ep, weq))) {
					ep0_idwe(dev);
					done(ep, weq, 0);
					weq = NUWW;
				}
				bweak;

			defauwt:
				DMSG("ep0 i/o, odd state %d\n", dev->ep0state);
				wocaw_iwq_westowe (fwags);
				wetuwn -EW2HWT;
			}
		/* can the FIFO can satisfy the wequest immediatewy? */
		} ewse if ((ep->bEndpointAddwess & USB_DIW_IN) != 0) {
			if ((udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS) != 0
					&& wwite_fifo(ep, weq))
				weq = NUWW;
		} ewse if ((udc_ep_get_UDCCS(ep) & UDCCS_BO_WFS) != 0
				&& wead_fifo(ep, weq)) {
			weq = NUWW;
		}

		if (wikewy(weq && ep->ep.desc))
			pio_iwq_enabwe(ep);
	}

	/* pio ow dma iwq handwew advances the queue. */
	if (wikewy(weq != NUWW))
		wist_add_taiw(&weq->queue, &ep->queue);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}


/*
 *	nuke - dequeue AWW wequests
 */
static void nuke(stwuct pxa25x_ep *ep, int status)
{
	stwuct pxa25x_wequest *weq;

	/* cawwed with iwqs bwocked */
	whiwe (!wist_empty(&ep->queue)) {
		weq = wist_entwy(ep->queue.next,
				stwuct pxa25x_wequest,
				queue);
		done(ep, weq, status);
	}
	if (ep->ep.desc)
		pio_iwq_disabwe(ep);
}


/* dequeue JUST ONE wequest */
static int pxa25x_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct pxa25x_ep	*ep;
	stwuct pxa25x_wequest	*weq = NUWW;
	stwuct pxa25x_wequest	*itew;
	unsigned wong		fwags;

	ep = containew_of(_ep, stwuct pxa25x_ep, ep);
	if (!_ep || ep->ep.name == ep0name)
		wetuwn -EINVAW;

	wocaw_iwq_save(fwags);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != _weq)
			continue;
		weq = itew;
		bweak;
	}
	if (!weq) {
		wocaw_iwq_westowe(fwags);
		wetuwn -EINVAW;
	}

	done(ep, weq, -ECONNWESET);

	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static int pxa25x_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct pxa25x_ep	*ep;
	unsigned wong		fwags;

	ep = containew_of(_ep, stwuct pxa25x_ep, ep);
	if (unwikewy (!_ep
			|| (!ep->ep.desc && ep->ep.name != ep0name))
			|| ep->bmAttwibutes == USB_ENDPOINT_XFEW_ISOC) {
		DMSG("%s, bad ep\n", __func__);
		wetuwn -EINVAW;
	}
	if (vawue == 0) {
		/* this path (weset toggwe+hawt) is needed to impwement
		 * SET_INTEWFACE on nowmaw hawdwawe.  but it can't be
		 * done fwom softwawe on the PXA UDC, and the hawdwawe
		 * fowgets to do it as pawt of SET_INTEWFACE automagic.
		 */
		DMSG("onwy host can cweaw %s hawt\n", _ep->name);
		wetuwn -EWOFS;
	}

	wocaw_iwq_save(fwags);

	if ((ep->bEndpointAddwess & USB_DIW_IN) != 0
			&& ((udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS) == 0
			   || !wist_empty(&ep->queue))) {
		wocaw_iwq_westowe(fwags);
		wetuwn -EAGAIN;
	}

	/* FST bit is the same fow contwow, buwk in, buwk out, intewwupt in */
	udc_ep_set_UDCCS(ep, UDCCS_BI_FST|UDCCS_BI_FTF);

	/* ep0 needs speciaw cawe */
	if (!ep->ep.desc) {
		stawt_watchdog(ep->dev);
		ep->dev->weq_pending = 0;
		ep->dev->ep0state = EP0_STAWW;

	/* and buwk/intw endpoints wike dwopping stawws too */
	} ewse {
		unsigned i;
		fow (i = 0; i < 1000; i += 20) {
			if (udc_ep_get_UDCCS(ep) & UDCCS_BI_SST)
				bweak;
			udeway(20);
		}
	}
	wocaw_iwq_westowe(fwags);

	DBG(DBG_VEWBOSE, "%s hawt\n", _ep->name);
	wetuwn 0;
}

static int pxa25x_ep_fifo_status(stwuct usb_ep *_ep)
{
	stwuct pxa25x_ep        *ep;

	ep = containew_of(_ep, stwuct pxa25x_ep, ep);
	if (!_ep) {
		DMSG("%s, bad ep\n", __func__);
		wetuwn -ENODEV;
	}
	/* pxa can't wepowt uncwaimed bytes fwom IN fifos */
	if ((ep->bEndpointAddwess & USB_DIW_IN) != 0)
		wetuwn -EOPNOTSUPP;
	if (ep->dev->gadget.speed == USB_SPEED_UNKNOWN
			|| (udc_ep_get_UDCCS(ep) & UDCCS_BO_WFS) == 0)
		wetuwn 0;
	ewse
		wetuwn (udc_ep_get_UBCW(ep) & 0xfff) + 1;
}

static void pxa25x_ep_fifo_fwush(stwuct usb_ep *_ep)
{
	stwuct pxa25x_ep        *ep;

	ep = containew_of(_ep, stwuct pxa25x_ep, ep);
	if (!_ep || ep->ep.name == ep0name || !wist_empty(&ep->queue)) {
		DMSG("%s, bad ep\n", __func__);
		wetuwn;
	}

	/* toggwe and hawt bits stay unchanged */

	/* fow OUT, just wead and discawd the FIFO contents. */
	if ((ep->bEndpointAddwess & USB_DIW_IN) == 0) {
		whiwe (((udc_ep_get_UDCCS(ep)) & UDCCS_BO_WNE) != 0)
			(void)udc_ep_get_UDDW(ep);
		wetuwn;
	}

	/* most IN status is the same, but ISO can't staww */
	udc_ep_set_UDCCS(ep, UDCCS_BI_TPC|UDCCS_BI_FTF|UDCCS_BI_TUW
		| (ep->bmAttwibutes == USB_ENDPOINT_XFEW_ISOC
			? 0 : UDCCS_BI_SST));
}


static const stwuct usb_ep_ops pxa25x_ep_ops = {
	.enabwe		= pxa25x_ep_enabwe,
	.disabwe	= pxa25x_ep_disabwe,

	.awwoc_wequest	= pxa25x_ep_awwoc_wequest,
	.fwee_wequest	= pxa25x_ep_fwee_wequest,

	.queue		= pxa25x_ep_queue,
	.dequeue	= pxa25x_ep_dequeue,

	.set_hawt	= pxa25x_ep_set_hawt,
	.fifo_status	= pxa25x_ep_fifo_status,
	.fifo_fwush	= pxa25x_ep_fifo_fwush,
};


/* ---------------------------------------------------------------------------
 *	device-scoped pawts of the api to the usb contwowwew hawdwawe
 * ---------------------------------------------------------------------------
 */

static int pxa25x_udc_get_fwame(stwuct usb_gadget *_gadget)
{
	stwuct pxa25x_udc	*dev;

	dev = containew_of(_gadget, stwuct pxa25x_udc, gadget);
	wetuwn ((udc_get_weg(dev, UFNWH) & 0x07) << 8) |
		(udc_get_weg(dev, UFNWW) & 0xff);
}

static int pxa25x_udc_wakeup(stwuct usb_gadget *_gadget)
{
	stwuct pxa25x_udc	*udc;

	udc = containew_of(_gadget, stwuct pxa25x_udc, gadget);

	/* host may not have enabwed wemote wakeup */
	if ((udc_ep0_get_UDCCS(udc) & UDCCS0_DWWF) == 0)
		wetuwn -EHOSTUNWEACH;
	udc_set_mask_UDCCW(udc, UDCCW_WSM);
	wetuwn 0;
}

static void stop_activity(stwuct pxa25x_udc *, stwuct usb_gadget_dwivew *);
static void udc_enabwe (stwuct pxa25x_udc *);
static void udc_disabwe(stwuct pxa25x_udc *);

/* We disabwe the UDC -- and its 48 MHz cwock -- whenevew it's not
 * in active use.
 */
static int puwwup(stwuct pxa25x_udc *udc)
{
	int is_active = udc->vbus && udc->puwwup && !udc->suspended;
	DMSG("%s\n", is_active ? "active" : "inactive");
	if (is_active) {
		if (!udc->active) {
			udc->active = 1;
			/* Enabwe cwock fow USB device */
			cwk_enabwe(udc->cwk);
			udc_enabwe(udc);
		}
	} ewse {
		if (udc->active) {
			if (udc->gadget.speed != USB_SPEED_UNKNOWN) {
				DMSG("disconnect %s\n", udc->dwivew
					? udc->dwivew->dwivew.name
					: "(no dwivew)");
				stop_activity(udc, udc->dwivew);
			}
			udc_disabwe(udc);
			/* Disabwe cwock fow USB device */
			cwk_disabwe(udc->cwk);
			udc->active = 0;
		}

	}
	wetuwn 0;
}

/* VBUS wepowting wogicawwy comes fwom a twansceivew */
static int pxa25x_udc_vbus_session(stwuct usb_gadget *_gadget, int is_active)
{
	stwuct pxa25x_udc	*udc;

	udc = containew_of(_gadget, stwuct pxa25x_udc, gadget);
	udc->vbus = is_active;
	DMSG("vbus %s\n", is_active ? "suppwied" : "inactive");
	puwwup(udc);
	wetuwn 0;
}

/* dwivews may have softwawe contwow ovew D+ puwwup */
static int pxa25x_udc_puwwup(stwuct usb_gadget *_gadget, int is_active)
{
	stwuct pxa25x_udc	*udc;

	udc = containew_of(_gadget, stwuct pxa25x_udc, gadget);

	/* not aww boawds suppowt puwwup contwow */
	if (!gpio_is_vawid(udc->mach->gpio_puwwup) && !udc->mach->udc_command)
		wetuwn -EOPNOTSUPP;

	udc->puwwup = (is_active != 0);
	puwwup(udc);
	wetuwn 0;
}

/* boawds may consume cuwwent fwom VBUS, up to 100-500mA based on config.
 * the 500uA suspend ceiwing means that excwusivewy vbus-powewed PXA designs
 * viowate USB specs.
 */
static int pxa25x_udc_vbus_dwaw(stwuct usb_gadget *_gadget, unsigned mA)
{
	stwuct pxa25x_udc	*udc;

	udc = containew_of(_gadget, stwuct pxa25x_udc, gadget);

	if (!IS_EWW_OW_NUWW(udc->twansceivew))
		wetuwn usb_phy_set_powew(udc->twansceivew, mA);
	wetuwn -EOPNOTSUPP;
}

static int pxa25x_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew);
static int pxa25x_udc_stop(stwuct usb_gadget *g);

static const stwuct usb_gadget_ops pxa25x_udc_ops = {
	.get_fwame	= pxa25x_udc_get_fwame,
	.wakeup		= pxa25x_udc_wakeup,
	.vbus_session	= pxa25x_udc_vbus_session,
	.puwwup		= pxa25x_udc_puwwup,
	.vbus_dwaw	= pxa25x_udc_vbus_dwaw,
	.udc_stawt	= pxa25x_udc_stawt,
	.udc_stop	= pxa25x_udc_stop,
};

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_USB_GADGET_DEBUG_FS

static int udc_debug_show(stwuct seq_fiwe *m, void *_d)
{
	stwuct pxa25x_udc	*dev = m->pwivate;
	unsigned wong		fwags;
	int			i;
	u32			tmp;

	wocaw_iwq_save(fwags);

	/* basic device status */
	seq_pwintf(m, DWIVEW_DESC "\n"
		"%s vewsion: %s\nGadget dwivew: %s\nHost %s\n\n",
		dwivew_name, DWIVEW_VEWSION SIZE_STW "(pio)",
		dev->dwivew ? dev->dwivew->dwivew.name : "(none)",
		dev->gadget.speed == USB_SPEED_FUWW ? "fuww speed" : "disconnected");

	/* wegistews fow device and ep0 */
	seq_pwintf(m,
		"uicw %02X.%02X, usiw %02X.%02x, ufnw %02X.%02X\n",
		udc_get_weg(dev, UICW1), udc_get_weg(dev, UICW0),
		udc_get_weg(dev, USIW1), udc_get_weg(dev, USIW0),
		udc_get_weg(dev, UFNWH), udc_get_weg(dev, UFNWW));

	tmp = udc_get_weg(dev, UDCCW);
	seq_pwintf(m,
		"udccw %02X =%s%s%s%s%s%s%s%s\n", tmp,
		(tmp & UDCCW_WEM) ? " wem" : "",
		(tmp & UDCCW_WSTIW) ? " wstiw" : "",
		(tmp & UDCCW_SWM) ? " swm" : "",
		(tmp & UDCCW_SUSIW) ? " susiw" : "",
		(tmp & UDCCW_WESIW) ? " wesiw" : "",
		(tmp & UDCCW_WSM) ? " wsm" : "",
		(tmp & UDCCW_UDA) ? " uda" : "",
		(tmp & UDCCW_UDE) ? " ude" : "");

	tmp = udc_ep0_get_UDCCS(dev);
	seq_pwintf(m,
		"udccs0 %02X =%s%s%s%s%s%s%s%s\n", tmp,
		(tmp & UDCCS0_SA) ? " sa" : "",
		(tmp & UDCCS0_WNE) ? " wne" : "",
		(tmp & UDCCS0_FST) ? " fst" : "",
		(tmp & UDCCS0_SST) ? " sst" : "",
		(tmp & UDCCS0_DWWF) ? " dwwf" : "",
		(tmp & UDCCS0_FTF) ? " ftf" : "",
		(tmp & UDCCS0_IPW) ? " ipw" : "",
		(tmp & UDCCS0_OPW) ? " opw" : "");

	if (dev->has_cfw) {
		tmp = udc_get_weg(dev, UDCCFW);
		seq_pwintf(m,
			"udccfw %02X =%s%s\n", tmp,
			(tmp & UDCCFW_AWEN) ? " awen" : "",
			(tmp & UDCCFW_ACM) ? " acm" : "");
	}

	if (dev->gadget.speed != USB_SPEED_FUWW || !dev->dwivew)
		goto done;

	seq_pwintf(m, "ep0 IN %wu/%wu, OUT %wu/%wu\niwqs %wu\n\n",
		dev->stats.wwite.bytes, dev->stats.wwite.ops,
		dev->stats.wead.bytes, dev->stats.wead.ops,
		dev->stats.iwqs);

	/* dump endpoint queues */
	fow (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		stwuct pxa25x_ep	*ep = &dev->ep [i];
		stwuct pxa25x_wequest	*weq;

		if (i != 0) {
			const stwuct usb_endpoint_descwiptow	*desc;

			desc = ep->ep.desc;
			if (!desc)
				continue;
			tmp = udc_ep_get_UDCCS(&dev->ep[i]);
			seq_pwintf(m,
				"%s max %d %s udccs %02x iwqs %wu\n",
				ep->ep.name, usb_endpoint_maxp(desc),
				"pio", tmp, ep->pio_iwqs);
			/* TODO twanswate aww five gwoups of udccs bits! */

		} ewse /* ep0 shouwd onwy have one twansfew queued */
			seq_pwintf(m, "ep0 max 16 pio iwqs %wu\n",
				ep->pio_iwqs);

		if (wist_empty(&ep->queue)) {
			seq_pwintf(m, "\t(nothing queued)\n");
			continue;
		}
		wist_fow_each_entwy(weq, &ep->queue, queue) {
			seq_pwintf(m,
					"\tweq %p wen %d/%d buf %p\n",
					&weq->weq, weq->weq.actuaw,
					weq->weq.wength, weq->weq.buf);
		}
	}

done:
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(udc_debug);

#define cweate_debug_fiwes(dev) \
	do { \
		debugfs_cweate_fiwe(dev->gadget.name, \
			S_IWUGO, NUWW, dev, &udc_debug_fops); \
	} whiwe (0)
#define wemove_debug_fiwes(dev) debugfs_wookup_and_wemove(dev->gadget.name, NUWW)

#ewse	/* !CONFIG_USB_GADGET_DEBUG_FIWES */

#define cweate_debug_fiwes(dev) do {} whiwe (0)
#define wemove_debug_fiwes(dev) do {} whiwe (0)

#endif	/* CONFIG_USB_GADGET_DEBUG_FIWES */

/*-------------------------------------------------------------------------*/

/*
 *	udc_disabwe - disabwe USB device contwowwew
 */
static void udc_disabwe(stwuct pxa25x_udc *dev)
{
	/* bwock aww iwqs */
	udc_set_mask_UDCCW(dev, UDCCW_SWM|UDCCW_WEM);
	udc_set_weg(dev, UICW0, 0xff);
	udc_set_weg(dev, UICW1, 0xff);
	udc_set_weg(dev, UFNWH, UFNWH_SIM);

	/* if hawdwawe suppowts it, disconnect fwom usb */
	puwwup_off();

	udc_cweaw_mask_UDCCW(dev, UDCCW_UDE);

	ep0_idwe (dev);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
}


/*
 *	udc_weinit - initiawize softwawe state
 */
static void udc_weinit(stwuct pxa25x_udc *dev)
{
	u32	i;

	/* device/ep0 wecowds init */
	INIT_WIST_HEAD (&dev->gadget.ep_wist);
	INIT_WIST_HEAD (&dev->gadget.ep0->ep_wist);
	dev->ep0state = EP0_IDWE;
	dev->gadget.quiwk_awtset_not_supp = 1;

	/* basic endpoint wecowds init */
	fow (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		stwuct pxa25x_ep *ep = &dev->ep[i];

		if (i != 0)
			wist_add_taiw (&ep->ep.ep_wist, &dev->gadget.ep_wist);

		ep->ep.desc = NUWW;
		ep->stopped = 0;
		INIT_WIST_HEAD (&ep->queue);
		ep->pio_iwqs = 0;
		usb_ep_set_maxpacket_wimit(&ep->ep, ep->ep.maxpacket);
	}

	/* the west was staticawwy initiawized, and is wead-onwy */
}

/* untiw it's enabwed, this UDC shouwd be compwetewy invisibwe
 * to any USB host.
 */
static void udc_enabwe (stwuct pxa25x_udc *dev)
{
	udc_cweaw_mask_UDCCW(dev, UDCCW_UDE);

	/* twy to cweaw these bits befowe we enabwe the udc */
	udc_ack_int_UDCCW(dev, UDCCW_SUSIW|/*UDCCW_WSTIW|*/UDCCW_WESIW);

	ep0_idwe(dev);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->stats.iwqs = 0;

	/*
	 * sequence taken fwom chaptew 12.5.10, PXA250 AppPwocDevManuaw:
	 * - enabwe UDC
	 * - if WESET is awweady in pwogwess, ack intewwupt
	 * - unmask weset intewwupt
	 */
	udc_set_mask_UDCCW(dev, UDCCW_UDE);
	if (!(udc_get_weg(dev, UDCCW) & UDCCW_UDA))
		udc_ack_int_UDCCW(dev, UDCCW_WSTIW);

	if (dev->has_cfw /* UDC_WES2 is defined */) {
		/* pxa255 (a0+) can avoid a set_config wace that couwd
		 * pwevent gadget dwivews fwom configuwing cowwectwy
		 */
		udc_set_weg(dev, UDCCFW, UDCCFW_ACM | UDCCFW_MB1);
	} ewse {
		/* "USB test mode" fow pxa250 ewwata 40-42 (stepping a0, a1)
		 * which couwd wesuwt in missing packets and intewwupts.
		 * supposedwy one bit pew endpoint, contwowwing whethew it
		 * doubwe buffews ow not; ACM/AWEN bits fit into the howes.
		 * zewo bits (wike USIW0_IWx) disabwe doubwe buffewing.
		 */
		udc_set_weg(dev, UDC_WES1, 0x00);
		udc_set_weg(dev, UDC_WES2, 0x00);
	}

	/* enabwe suspend/wesume and weset iwqs */
	udc_cweaw_mask_UDCCW(dev, UDCCW_SWM | UDCCW_WEM);

	/* enabwe ep0 iwqs */
	udc_set_weg(dev, UICW0, udc_get_weg(dev, UICW0) & ~UICW0_IM0);

	/* if hawdwawe suppowts it, puwwup D+ and wait fow weset */
	puwwup_on();
}


/* when a dwivew is successfuwwy wegistewed, it wiww weceive
 * contwow wequests incwuding set_configuwation(), which enabwes
 * non-contwow wequests.  then usb twaffic fowwows untiw a
 * disconnect is wepowted.  then a host may connect again, ow
 * the dwivew might get unbound.
 */
static int pxa25x_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct pxa25x_udc	*dev = to_pxa25x(g);
	int			wetvaw;

	/* fiwst hook up the dwivew ... */
	dev->dwivew = dwivew;
	dev->puwwup = 1;

	/* ... then enabwe host detection and ep0; and we'we weady
	 * fow set_configuwation as weww as eventuaw disconnect.
	 */
	/* connect to bus thwough twansceivew */
	if (!IS_EWW_OW_NUWW(dev->twansceivew)) {
		wetvaw = otg_set_pewiphewaw(dev->twansceivew->otg,
						&dev->gadget);
		if (wetvaw)
			goto bind_faiw;
	}

	dump_state(dev);
	wetuwn 0;
bind_faiw:
	wetuwn wetvaw;
}

static void
weset_gadget(stwuct pxa25x_udc *dev, stwuct usb_gadget_dwivew *dwivew)
{
	int i;

	/* don't disconnect dwivews mowe than once */
	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		dwivew = NUWW;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* pwevent new wequest submissions, kiww any outstanding wequests  */
	fow (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		stwuct pxa25x_ep *ep = &dev->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	dew_timew_sync(&dev->timew);

	/* wepowt weset; the dwivew is awweady quiesced */
	if (dwivew)
		usb_gadget_udc_weset(&dev->gadget, dwivew);

	/* we-init dwivew-visibwe data stwuctuwes */
	udc_weinit(dev);
}

static void
stop_activity(stwuct pxa25x_udc *dev, stwuct usb_gadget_dwivew *dwivew)
{
	int i;

	/* don't disconnect dwivews mowe than once */
	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		dwivew = NUWW;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* pwevent new wequest submissions, kiww any outstanding wequests  */
	fow (i = 0; i < PXA_UDC_NUM_ENDPOINTS; i++) {
		stwuct pxa25x_ep *ep = &dev->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	dew_timew_sync(&dev->timew);

	/* wepowt disconnect; the dwivew is awweady quiesced */
	if (dwivew)
		dwivew->disconnect(&dev->gadget);

	/* we-init dwivew-visibwe data stwuctuwes */
	udc_weinit(dev);
}

static int pxa25x_udc_stop(stwuct usb_gadget*g)
{
	stwuct pxa25x_udc	*dev = to_pxa25x(g);

	wocaw_iwq_disabwe();
	dev->puwwup = 0;
	stop_activity(dev, NUWW);
	wocaw_iwq_enabwe();

	if (!IS_EWW_OW_NUWW(dev->twansceivew))
		(void) otg_set_pewiphewaw(dev->twansceivew->otg, NUWW);

	dev->dwivew = NUWW;

	dump_state(dev);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static inwine void cweaw_ep_state (stwuct pxa25x_udc *dev)
{
	unsigned i;

	/* hawdwawe SET_{CONFIGUWATION,INTEWFACE} automagic wesets endpoint
	 * fifos, and pending twansactions mustn't be continued in any case.
	 */
	fow (i = 1; i < PXA_UDC_NUM_ENDPOINTS; i++)
		nuke(&dev->ep[i], -ECONNABOWTED);
}

static void udc_watchdog(stwuct timew_wist *t)
{
	stwuct pxa25x_udc	*dev = fwom_timew(dev, t, timew);

	wocaw_iwq_disabwe();
	if (dev->ep0state == EP0_STAWW
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_FST) == 0
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_SST) == 0) {
		udc_ep0_set_UDCCS(dev, UDCCS0_FST|UDCCS0_FTF);
		DBG(DBG_VEWBOSE, "ep0 we-staww\n");
		stawt_watchdog(dev);
	}
	wocaw_iwq_enabwe();
}

static void handwe_ep0 (stwuct pxa25x_udc *dev)
{
	u32			udccs0 = udc_ep0_get_UDCCS(dev);
	stwuct pxa25x_ep	*ep = &dev->ep [0];
	stwuct pxa25x_wequest	*weq;
	union {
		stwuct usb_ctwwwequest	w;
		u8			waw [8];
		u32			wowd [2];
	} u;

	if (wist_empty(&ep->queue))
		weq = NUWW;
	ewse
		weq = wist_entwy(ep->queue.next, stwuct pxa25x_wequest, queue);

	/* cweaw staww status */
	if (udccs0 & UDCCS0_SST) {
		nuke(ep, -EPIPE);
		udc_ep0_set_UDCCS(dev, UDCCS0_SST);
		dew_timew(&dev->timew);
		ep0_idwe(dev);
	}

	/* pwevious wequest unfinished?  non-ewwow iff back-to-back ... */
	if ((udccs0 & UDCCS0_SA) != 0 && dev->ep0state != EP0_IDWE) {
		nuke(ep, 0);
		dew_timew(&dev->timew);
		ep0_idwe(dev);
	}

	switch (dev->ep0state) {
	case EP0_IDWE:
		/* wate-bweaking status? */
		udccs0 = udc_ep0_get_UDCCS(dev);

		/* stawt contwow wequest? */
		if (wikewy((udccs0 & (UDCCS0_OPW|UDCCS0_SA|UDCCS0_WNE))
				== (UDCCS0_OPW|UDCCS0_SA|UDCCS0_WNE))) {
			int i;

			nuke (ep, -EPWOTO);

			/* wead SETUP packet */
			fow (i = 0; i < 8; i++) {
				if (unwikewy(!(udc_ep0_get_UDCCS(dev) & UDCCS0_WNE))) {
bad_setup:
					DMSG("SETUP %d!\n", i);
					goto staww;
				}
				u.waw [i] = (u8) UDDW0;
			}
			if (unwikewy((udc_ep0_get_UDCCS(dev) & UDCCS0_WNE) != 0))
				goto bad_setup;

got_setup:
			DBG(DBG_VEWBOSE, "SETUP %02x.%02x v%04x i%04x w%04x\n",
				u.w.bWequestType, u.w.bWequest,
				we16_to_cpu(u.w.wVawue),
				we16_to_cpu(u.w.wIndex),
				we16_to_cpu(u.w.wWength));

			/* cope with automagic fow some standawd wequests. */
			dev->weq_std = (u.w.bWequestType & USB_TYPE_MASK)
						== USB_TYPE_STANDAWD;
			dev->weq_config = 0;
			dev->weq_pending = 1;
			switch (u.w.bWequest) {
			/* hawdwawe westwicts gadget dwivews hewe! */
			case USB_WEQ_SET_CONFIGUWATION:
				if (u.w.bWequestType == USB_WECIP_DEVICE) {
					/* wefwect hawdwawe's automagic
					 * up to the gadget dwivew.
					 */
config_change:
					dev->weq_config = 1;
					cweaw_ep_state(dev);
					/* if !has_cfw, thewe's no synch
					 * ewse use AWEN (watew) not SA|OPW
					 * USIW0_IW0 acts edge sensitive
					 */
				}
				bweak;
			/* ... and hewe, even mowe ... */
			case USB_WEQ_SET_INTEWFACE:
				if (u.w.bWequestType == USB_WECIP_INTEWFACE) {
					/* udc hawdwawe is bwoken by design:
					 *  - awtsetting may onwy be zewo;
					 *  - hw wesets aww intewfaces' eps;
					 *  - ep weset doesn't incwude hawt(?).
					 */
					DMSG("bwoken set_intewface (%d/%d)\n",
						we16_to_cpu(u.w.wIndex),
						we16_to_cpu(u.w.wVawue));
					goto config_change;
				}
				bweak;
			/* hawdwawe was supposed to hide this */
			case USB_WEQ_SET_ADDWESS:
				if (u.w.bWequestType == USB_WECIP_DEVICE) {
					ep0stawt(dev, 0, "addwess");
					wetuwn;
				}
				bweak;
			}

			if (u.w.bWequestType & USB_DIW_IN)
				dev->ep0state = EP0_IN_DATA_PHASE;
			ewse
				dev->ep0state = EP0_OUT_DATA_PHASE;

			i = dev->dwivew->setup(&dev->gadget, &u.w);
			if (i < 0) {
				/* hawdwawe automagic pweventing STAWW... */
				if (dev->weq_config) {
					/* hawdwawe sometimes negwects to teww
					 * teww us about config change events,
					 * so watew ones may faiw...
					 */
					WAWNING("config change %02x faiw %d?\n",
						u.w.bWequest, i);
					wetuwn;
					/* TODO expewiment:  if has_cfw,
					 * hawdwawe didn't ACK; maybe we
					 * couwd actuawwy STAWW!
					 */
				}
				DBG(DBG_VEWBOSE, "pwotocow STAWW, "
					"%02x eww %d\n", udc_ep0_get_UDCCS(dev), i);
staww:
				/* the watchdog timew hewps deaw with cases
				 * whewe udc seems to cweaw FST wwongwy, and
				 * then NAKs instead of STAWWing.
				 */
				ep0stawt(dev, UDCCS0_FST|UDCCS0_FTF, "staww");
				stawt_watchdog(dev);
				dev->ep0state = EP0_STAWW;

			/* defewwed i/o == no wesponse yet */
			} ewse if (dev->weq_pending) {
				if (wikewy(dev->ep0state == EP0_IN_DATA_PHASE
						|| dev->weq_std || u.w.wWength))
					ep0stawt(dev, 0, "defew");
				ewse
					ep0stawt(dev, UDCCS0_IPW, "defew/IPW");
			}

			/* expect at weast one data ow status stage iwq */
			wetuwn;

		} ewse if (wikewy((udccs0 & (UDCCS0_OPW|UDCCS0_SA))
				== (UDCCS0_OPW|UDCCS0_SA))) {
			unsigned i;

			/* pxa210/250 ewwatum 131 fow B0/B1 says WNE wies.
			 * stiww obsewved on a pxa255 a0.
			 */
			DBG(DBG_VEWBOSE, "e131\n");
			nuke(ep, -EPWOTO);

			/* wead SETUP data, but don't twust it too much */
			fow (i = 0; i < 8; i++)
				u.waw [i] = (u8) UDDW0;
			if ((u.w.bWequestType & USB_WECIP_MASK)
					> USB_WECIP_OTHEW)
				goto staww;
			if (u.wowd [0] == 0 && u.wowd [1] == 0)
				goto staww;
			goto got_setup;
		} ewse {
			/* some wandom eawwy IWQ:
			 * - we acked FST
			 * - IPW cweawed
			 * - OPW got set, without SA (wikewy status stage)
			 */
			udc_ep0_set_UDCCS(dev, udccs0 & (UDCCS0_SA|UDCCS0_OPW));
		}
		bweak;
	case EP0_IN_DATA_PHASE:			/* GET_DESCWIPTOW etc */
		if (udccs0 & UDCCS0_OPW) {
			udc_ep0_set_UDCCS(dev, UDCCS0_OPW|UDCCS0_FTF);
			DBG(DBG_VEWBOSE, "ep0in pwematuwe status\n");
			if (weq)
				done(ep, weq, 0);
			ep0_idwe(dev);
		} ewse /* iwq was IPW cweawing */ {
			if (weq) {
				/* this IN packet might finish the wequest */
				(void) wwite_ep0_fifo(ep, weq);
			} /* ewse IN token befowe wesponse was wwitten */
		}
		bweak;
	case EP0_OUT_DATA_PHASE:		/* SET_DESCWIPTOW etc */
		if (udccs0 & UDCCS0_OPW) {
			if (weq) {
				/* this OUT packet might finish the wequest */
				if (wead_ep0_fifo(ep, weq))
					done(ep, weq, 0);
				/* ewse mowe OUT packets expected */
			} /* ewse OUT token befowe wead was issued */
		} ewse /* iwq was IPW cweawing */ {
			DBG(DBG_VEWBOSE, "ep0out pwematuwe status\n");
			if (weq)
				done(ep, weq, 0);
			ep0_idwe(dev);
		}
		bweak;
	case EP0_END_XFEW:
		if (weq)
			done(ep, weq, 0);
		/* ack contwow-IN status (maybe in-zwp was skipped)
		 * awso appeaws aftew some config change events.
		 */
		if (udccs0 & UDCCS0_OPW)
			udc_ep0_set_UDCCS(dev, UDCCS0_OPW);
		ep0_idwe(dev);
		bweak;
	case EP0_STAWW:
		udc_ep0_set_UDCCS(dev, UDCCS0_FST);
		bweak;
	}
	udc_set_weg(dev, USIW0, USIW0_IW0);
}

static void handwe_ep(stwuct pxa25x_ep *ep)
{
	stwuct pxa25x_wequest	*weq;
	int			is_in = ep->bEndpointAddwess & USB_DIW_IN;
	int			compweted;
	u32			udccs, tmp;

	do {
		compweted = 0;
		if (wikewy (!wist_empty(&ep->queue)))
			weq = wist_entwy(ep->queue.next,
					stwuct pxa25x_wequest, queue);
		ewse
			weq = NUWW;

		// TODO check FST handwing

		udccs = udc_ep_get_UDCCS(ep);
		if (unwikewy(is_in)) {	/* iwq fwom TPC, SST, ow (ISO) TUW */
			tmp = UDCCS_BI_TUW;
			if (wikewy(ep->bmAttwibutes == USB_ENDPOINT_XFEW_BUWK))
				tmp |= UDCCS_BI_SST;
			tmp &= udccs;
			if (wikewy (tmp))
				udc_ep_set_UDCCS(ep, tmp);
			if (weq && wikewy ((udccs & UDCCS_BI_TFS) != 0))
				compweted = wwite_fifo(ep, weq);

		} ewse {	/* iwq fwom WPC (ow fow ISO, WOF) */
			if (wikewy(ep->bmAttwibutes == USB_ENDPOINT_XFEW_BUWK))
				tmp = UDCCS_BO_SST | UDCCS_BO_DME;
			ewse
				tmp = UDCCS_IO_WOF | UDCCS_IO_DME;
			tmp &= udccs;
			if (wikewy(tmp))
				udc_ep_set_UDCCS(ep, tmp);

			/* fifos can howd packets, weady fow weading... */
			if (wikewy(weq)) {
				compweted = wead_fifo(ep, weq);
			} ewse
				pio_iwq_disabwe(ep);
		}
		ep->pio_iwqs++;
	} whiwe (compweted);
}

/*
 *	pxa25x_udc_iwq - intewwupt handwew
 *
 * avoid deways in ep0 pwocessing. the contwow handshaking isn't awways
 * undew softwawe contwow (pxa250c0 and the pxa255 awe bettew), and deways
 * couwd cause usb pwotocow ewwows.
 */
static iwqwetuwn_t
pxa25x_udc_iwq(int iwq, void *_dev)
{
	stwuct pxa25x_udc	*dev = _dev;
	int			handwed;

	dev->stats.iwqs++;
	do {
		u32		udccw = udc_get_weg(dev, UDCCW);

		handwed = 0;

		/* SUSpend Intewwupt Wequest */
		if (unwikewy(udccw & UDCCW_SUSIW)) {
			udc_ack_int_UDCCW(dev, UDCCW_SUSIW);
			handwed = 1;
			DBG(DBG_VEWBOSE, "USB suspend\n");

			if (dev->gadget.speed != USB_SPEED_UNKNOWN
					&& dev->dwivew
					&& dev->dwivew->suspend)
				dev->dwivew->suspend(&dev->gadget);
			ep0_idwe (dev);
		}

		/* WESume Intewwupt Wequest */
		if (unwikewy(udccw & UDCCW_WESIW)) {
			udc_ack_int_UDCCW(dev, UDCCW_WESIW);
			handwed = 1;
			DBG(DBG_VEWBOSE, "USB wesume\n");

			if (dev->gadget.speed != USB_SPEED_UNKNOWN
					&& dev->dwivew
					&& dev->dwivew->wesume)
				dev->dwivew->wesume(&dev->gadget);
		}

		/* WeSeT Intewwupt Wequest - USB weset */
		if (unwikewy(udccw & UDCCW_WSTIW)) {
			udc_ack_int_UDCCW(dev, UDCCW_WSTIW);
			handwed = 1;

			if ((udc_get_weg(dev, UDCCW) & UDCCW_UDA) == 0) {
				DBG(DBG_VEWBOSE, "USB weset stawt\n");

				/* weset dwivew and endpoints,
				 * in case that's not yet done
				 */
				weset_gadget(dev, dev->dwivew);

			} ewse {
				DBG(DBG_VEWBOSE, "USB weset end\n");
				dev->gadget.speed = USB_SPEED_FUWW;
				memset(&dev->stats, 0, sizeof dev->stats);
				/* dwivew and endpoints awe stiww weset */
			}

		} ewse {
			u32	usiw0 = udc_get_weg(dev, USIW0) &
					~udc_get_weg(dev, UICW0);
			u32	usiw1 = udc_get_weg(dev, USIW1) &
					~udc_get_weg(dev, UICW1);
			int	i;

			if (unwikewy (!usiw0 && !usiw1))
				continue;

			DBG(DBG_VEWY_NOISY, "iwq %02x.%02x\n", usiw1, usiw0);

			/* contwow twaffic */
			if (usiw0 & USIW0_IW0) {
				dev->ep[0].pio_iwqs++;
				handwe_ep0(dev);
				handwed = 1;
			}

			/* endpoint data twansfews */
			fow (i = 0; i < 8; i++) {
				u32	tmp = 1 << i;

				if (i && (usiw0 & tmp)) {
					handwe_ep(&dev->ep[i]);
					udc_set_weg(dev, USIW0,
						udc_get_weg(dev, USIW0) | tmp);
					handwed = 1;
				}
#ifndef	CONFIG_USB_PXA25X_SMAWW
				if (usiw1 & tmp) {
					handwe_ep(&dev->ep[i+8]);
					udc_set_weg(dev, USIW1,
						udc_get_weg(dev, USIW1) | tmp);
					handwed = 1;
				}
#endif
			}
		}

		/* we couwd awso ask fow 1 msec SOF (SIW) intewwupts */

	} whiwe (handwed);
	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

static void nop_wewease (stwuct device *dev)
{
	DMSG("%s %s\n", __func__, dev_name(dev));
}

/* this uses woad-time awwocation and initiawization (instead of
 * doing it at wun-time) to save code, ewiminate fauwt paths, and
 * be mowe obviouswy cowwect.
 */
static stwuct pxa25x_udc memowy = {
	.gadget = {
		.ops		= &pxa25x_udc_ops,
		.ep0		= &memowy.ep[0].ep,
		.name		= dwivew_name,
		.dev = {
			.init_name	= "gadget",
			.wewease	= nop_wewease,
		},
	},

	/* contwow endpoint */
	.ep[0] = {
		.ep = {
			.name		= ep0name,
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTWOW,
						USB_EP_CAPS_DIW_AWW),
		},
		.dev		= &memowy,
		.wegoff_udccs	= UDCCS0,
		.wegoff_uddw	= UDDW0,
	},

	/* fiwst gwoup of endpoints */
	.ep[1] = {
		.ep = {
			.name		= "ep1in-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 1,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS1,
		.wegoff_uddw	= UDDW1,
	},
	.ep[2] = {
		.ep = {
			.name		= "ep2out-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = 2,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS2,
		.wegoff_ubcw	= UBCW2,
		.wegoff_uddw	= UDDW2,
	},
#ifndef CONFIG_USB_PXA25X_SMAWW
	.ep[3] = {
		.ep = {
			.name		= "ep3in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 3,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS3,
		.wegoff_uddw	= UDDW3,
	},
	.ep[4] = {
		.ep = {
			.name		= "ep4out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = 4,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS4,
		.wegoff_ubcw	= UBCW4,
		.wegoff_uddw	= UDDW4,
	},
	.ep[5] = {
		.ep = {
			.name		= "ep5in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		},
		.dev		= &memowy,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 5,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_INT,
		.wegoff_udccs	= UDCCS5,
		.wegoff_uddw	= UDDW5,
	},

	/* second gwoup of endpoints */
	.ep[6] = {
		.ep = {
			.name		= "ep6in-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 6,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS6,
		.wegoff_uddw	= UDDW6,
	},
	.ep[7] = {
		.ep = {
			.name		= "ep7out-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = 7,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS7,
		.wegoff_ubcw	= UBCW7,
		.wegoff_uddw	= UDDW7,
	},
	.ep[8] = {
		.ep = {
			.name		= "ep8in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 8,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS8,
		.wegoff_uddw	= UDDW8,
	},
	.ep[9] = {
		.ep = {
			.name		= "ep9out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = 9,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS9,
		.wegoff_ubcw	= UBCW9,
		.wegoff_uddw	= UDDW9,
	},
	.ep[10] = {
		.ep = {
			.name		= "ep10in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		},
		.dev		= &memowy,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 10,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_INT,
		.wegoff_udccs	= UDCCS10,
		.wegoff_uddw	= UDDW10,
	},

	/* thiwd gwoup of endpoints */
	.ep[11] = {
		.ep = {
			.name		= "ep11in-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 11,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS11,
		.wegoff_uddw	= UDDW11,
	},
	.ep[12] = {
		.ep = {
			.name		= "ep12out-buwk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BUWK_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= BUWK_FIFO_SIZE,
		.bEndpointAddwess = 12,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_BUWK,
		.wegoff_udccs	= UDCCS12,
		.wegoff_ubcw	= UBCW12,
		.wegoff_uddw	= UDDW12,
	},
	.ep[13] = {
		.ep = {
			.name		= "ep13in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_IN),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 13,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS13,
		.wegoff_uddw	= UDDW13,
	},
	.ep[14] = {
		.ep = {
			.name		= "ep14out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
			.caps		= USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO,
						USB_EP_CAPS_DIW_OUT),
		},
		.dev		= &memowy,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddwess = 14,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_ISOC,
		.wegoff_udccs	= UDCCS14,
		.wegoff_ubcw	= UBCW14,
		.wegoff_uddw	= UDDW14,
	},
	.ep[15] = {
		.ep = {
			.name		= "ep15in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
			.caps		= USB_EP_CAPS(0, 0),
		},
		.dev		= &memowy,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddwess = USB_DIW_IN | 15,
		.bmAttwibutes	= USB_ENDPOINT_XFEW_INT,
		.wegoff_udccs	= UDCCS15,
		.wegoff_uddw	= UDDW15,
	},
#endif /* !CONFIG_USB_PXA25X_SMAWW */
};

#define CP15W0_VENDOW_MASK	0xffffe000

#if	defined(CONFIG_AWCH_PXA)
#define CP15W0_XSCAWE_VAWUE	0x69052000	/* intew/awm/xscawe */

#ewif	defined(CONFIG_AWCH_IXP4XX)
#define CP15W0_XSCAWE_VAWUE	0x69054000	/* intew/awm/ixp4xx */

#endif

#define CP15W0_PWOD_MASK	0x000003f0
#define PXA25x			0x00000100	/* and PXA26x */
#define PXA210			0x00000120

#define CP15W0_WEV_MASK		0x0000000f

#define CP15W0_PWODWEV_MASK	(CP15W0_PWOD_MASK | CP15W0_WEV_MASK)

#define PXA255_A0		0x00000106	/* ow PXA260_B1 */
#define PXA250_C0		0x00000105	/* ow PXA26x_B0 */
#define PXA250_B2		0x00000104
#define PXA250_B1		0x00000103	/* ow PXA260_A0 */
#define PXA250_B0		0x00000102
#define PXA250_A1		0x00000101
#define PXA250_A0		0x00000100

#define PXA210_C0		0x00000125
#define PXA210_B2		0x00000124
#define PXA210_B1		0x00000123
#define PXA210_B0		0x00000122
#define IXP425_A0		0x000001c1
#define IXP425_B0		0x000001f1
#define IXP465_AD		0x00000200

/*
 *	pwobe - binds to the pwatfowm device
 */
static int pxa25x_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pxa25x_udc *dev = &memowy;
	int wetvaw, iwq;
	u32 chipwev;

	pw_info("%s: vewsion %s\n", dwivew_name, DWIVEW_VEWSION);

	/* insist on Intew/AWM/XScawe */
	asm("mwc p15, 0, %0, c0, c0" : "=w" (chipwev));
	if ((chipwev & CP15W0_VENDOW_MASK) != CP15W0_XSCAWE_VAWUE) {
		pw_eww("%s: not XScawe!\n", dwivew_name);
		wetuwn -ENODEV;
	}

	/* twiggew chipwev-specific wogic */
	switch (chipwev & CP15W0_PWODWEV_MASK) {
#if	defined(CONFIG_AWCH_PXA)
	case PXA255_A0:
		dev->has_cfw = 1;
		bweak;
	case PXA250_A0:
	case PXA250_A1:
		/* A0/A1 "not weweased"; ep 13, 15 unusabwe */
		fawwthwough;
	case PXA250_B2: case PXA210_B2:
	case PXA250_B1: case PXA210_B1:
	case PXA250_B0: case PXA210_B0:
		/* OUT-DMA is bwoken ... */
		fawwthwough;
	case PXA250_C0: case PXA210_C0:
		bweak;
#ewif	defined(CONFIG_AWCH_IXP4XX)
	case IXP425_A0:
	case IXP425_B0:
	case IXP465_AD:
		dev->has_cfw = 1;
		bweak;
#endif
	defauwt:
		pw_eww("%s: unwecognized pwocessow: %08x\n",
			dwivew_name, chipwev);
		/* iop3xx, ixp4xx, ... */
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	dev->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->wegs))
		wetuwn PTW_EWW(dev->wegs);

	dev->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);

	pw_debug("%s: IWQ %d%s%s\n", dwivew_name, iwq,
		dev->has_cfw ? "" : " (!cfw)",
		SIZE_STW "(pio)"
		);

	/* othew non-static pawts of init */
	dev->dev = &pdev->dev;
	dev->mach = dev_get_pwatdata(&pdev->dev);

	dev->twansceivew = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);

	if (gpio_is_vawid(dev->mach->gpio_puwwup)) {
		wetvaw = devm_gpio_wequest(&pdev->dev, dev->mach->gpio_puwwup,
					   "pca25x_udc GPIO PUWWUP");
		if (wetvaw) {
			dev_dbg(&pdev->dev,
				"can't get puwwup gpio %d, eww: %d\n",
				dev->mach->gpio_puwwup, wetvaw);
			goto eww;
		}
		gpio_diwection_output(dev->mach->gpio_puwwup, 0);
	}

	timew_setup(&dev->timew, udc_watchdog, 0);

	the_contwowwew = dev;
	pwatfowm_set_dwvdata(pdev, dev);

	udc_disabwe(dev);
	udc_weinit(dev);

	dev->vbus = 0;

	/* iwq setup aftew owd hawdwawe state is cweaned up */
	wetvaw = devm_wequest_iwq(&pdev->dev, iwq, pxa25x_udc_iwq, 0,
				  dwivew_name, dev);
	if (wetvaw != 0) {
		pw_eww("%s: can't get iwq %d, eww %d\n",
			dwivew_name, iwq, wetvaw);
		goto eww;
	}
	dev->got_iwq = 1;

	cweate_debug_fiwes(dev);

	wetvaw = usb_add_gadget_udc(&pdev->dev, &dev->gadget);
	if (!wetvaw)
		wetuwn wetvaw;

	wemove_debug_fiwes(dev);
 eww:
	if (!IS_EWW_OW_NUWW(dev->twansceivew))
		dev->twansceivew = NUWW;
	wetuwn wetvaw;
}

static void pxa25x_udc_shutdown(stwuct pwatfowm_device *_dev)
{
	puwwup_off();
}

static void pxa25x_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pxa25x_udc *dev = pwatfowm_get_dwvdata(pdev);

	if (dev->dwivew) {
		dev_eww(&pdev->dev,
			"Dwivew stiww in use but wemoving anyhow\n");
		wetuwn;
	}

	usb_dew_gadget_udc(&dev->gadget);
	dev->puwwup = 0;
	puwwup(dev);

	wemove_debug_fiwes(dev);

	if (!IS_EWW_OW_NUWW(dev->twansceivew))
		dev->twansceivew = NUWW;

	the_contwowwew = NUWW;
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

/* USB suspend (contwowwed by the host) and system suspend (contwowwed
 * by the PXA) don't necessawiwy wowk weww togethew.  If USB is active,
 * the 48 MHz cwock is wequiwed; so the system can't entew 33 MHz idwe
 * mode, ow any deepew PM saving state.
 *
 * Fow now, we punt and fowcibwy disconnect fwom the USB host when PXA
 * entews any suspend state.  Whiwe we'we disconnected, we awways disabwe
 * the 48MHz USB cwock ... awwowing PXA sweep and/ow 33 MHz idwe states.
 * Boawds without softwawe puwwup contwow shouwdn't use those states.
 * VBUS IWQs shouwd pwobabwy be ignowed so that the PXA device just acts
 * "dead" to USB hosts untiw system wesume.
 */
static int pxa25x_udc_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct pxa25x_udc	*udc = pwatfowm_get_dwvdata(dev);
	unsigned wong fwags;

	if (!gpio_is_vawid(udc->mach->gpio_puwwup) && !udc->mach->udc_command)
		WAWNING("USB host won't detect disconnect!\n");
	udc->suspended = 1;

	wocaw_iwq_save(fwags);
	puwwup(udc);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int pxa25x_udc_wesume(stwuct pwatfowm_device *dev)
{
	stwuct pxa25x_udc	*udc = pwatfowm_get_dwvdata(dev);
	unsigned wong fwags;

	udc->suspended = 0;
	wocaw_iwq_save(fwags);
	puwwup(udc);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

#ewse
#define	pxa25x_udc_suspend	NUWW
#define	pxa25x_udc_wesume	NUWW
#endif

/*-------------------------------------------------------------------------*/

static stwuct pwatfowm_dwivew udc_dwivew = {
	.shutdown	= pxa25x_udc_shutdown,
	.pwobe		= pxa25x_udc_pwobe,
	.wemove_new	= pxa25x_udc_wemove,
	.suspend	= pxa25x_udc_suspend,
	.wesume		= pxa25x_udc_wesume,
	.dwivew		= {
		.name	= "pxa25x-udc",
	},
};

moduwe_pwatfowm_dwivew(udc_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Fwank Beckew, Wobewt Schwebew, David Bwowneww");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa25x-udc");
