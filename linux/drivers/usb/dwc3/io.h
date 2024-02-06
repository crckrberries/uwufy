/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * io.h - DesignWawe USB3 DWD IO Headew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#ifndef __DWIVEWS_USB_DWC3_IO_H
#define __DWIVEWS_USB_DWC3_IO_H

#incwude <winux/io.h>
#incwude "twace.h"
#incwude "debug.h"
#incwude "cowe.h"

static inwine u32 dwc3_weadw(void __iomem *base, u32 offset)
{
	u32 vawue;

	/*
	 * We wequested the mem wegion stawting fwom the Gwobaws addwess
	 * space, see dwc3_pwobe in cowe.c.
	 * Howevew, the offsets awe given stawting fwom xHCI addwess space.
	 */
	vawue = weadw(base + offset - DWC3_GWOBAWS_WEGS_STAWT);

	/*
	 * When twacing we want to make it easy to find the cowwect addwess on
	 * documentation, so we wevewt it back to the pwopew addwesses, the
	 * same way they awe descwibed on SNPS documentation
	 */
	twace_dwc3_weadw(base - DWC3_GWOBAWS_WEGS_STAWT, offset, vawue);

	wetuwn vawue;
}

static inwine void dwc3_wwitew(void __iomem *base, u32 offset, u32 vawue)
{
	/*
	 * We wequested the mem wegion stawting fwom the Gwobaws addwess
	 * space, see dwc3_pwobe in cowe.c.
	 * Howevew, the offsets awe given stawting fwom xHCI addwess space.
	 */
	wwitew(vawue, base + offset - DWC3_GWOBAWS_WEGS_STAWT);

	/*
	 * When twacing we want to make it easy to find the cowwect addwess on
	 * documentation, so we wevewt it back to the pwopew addwesses, the
	 * same way they awe descwibed on SNPS documentation
	 */
	twace_dwc3_wwitew(base - DWC3_GWOBAWS_WEGS_STAWT, offset, vawue);
}

#endif /* __DWIVEWS_USB_DWC3_IO_H */
