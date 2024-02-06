/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew wegistew I/O
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef __MUSB_WINUX_PWATFOWM_AWCH_H__
#define __MUSB_WINUX_PWATFOWM_AWCH_H__

#incwude <winux/io.h>

#define musb_ep_sewect(_mbase, _epnum)	musb->io.ep_sewect((_mbase), (_epnum))

/**
 * stwuct musb_io - IO functions fow MUSB
 * @ep_offset:	pwatfowm specific function to get end point offset
 * @ep_sewect:	pwatfowm specific function to sewect end point
 * @fifo_offset: pwatfowm specific function to get fifo offset
 * @wead_fifo:	pwatfowm specific function to wead fifo
 * @wwite_fifo:	pwatfowm specific function to wwite fifo
 * @busctw_offset: pwatfowm specific function to get busctw offset
 * @get_toggwe: pwatfowm specific function to get toggwe
 * @set_toggwe: pwatfowm specific function to set toggwe
 */
stwuct musb_io {
	u32	(*ep_offset)(u8 epnum, u16 offset);
	void	(*ep_sewect)(void __iomem *mbase, u8 epnum);
	u32	(*fifo_offset)(u8 epnum);
	void	(*wead_fifo)(stwuct musb_hw_ep *hw_ep, u16 wen, u8 *buf);
	void	(*wwite_fifo)(stwuct musb_hw_ep *hw_ep, u16 wen, const u8 *buf);
	u32	(*busctw_offset)(u8 epnum, u16 offset);
	u16	(*get_toggwe)(stwuct musb_qh *qh, int is_out);
	u16	(*set_toggwe)(stwuct musb_qh *qh, int is_out, stwuct uwb *uwb);
};

/* Do not add new entwies hewe, add them the stwuct musb_io instead */
extewn u8 (*musb_weadb)(void __iomem *addw, u32 offset);
extewn void (*musb_wwiteb)(void __iomem *addw, u32 offset, u8 data);
extewn u8 (*musb_cweawb)(void __iomem *addw, u32 offset);
extewn u16 (*musb_weadw)(void __iomem *addw, u32 offset);
extewn void (*musb_wwitew)(void __iomem *addw, u32 offset, u16 data);
extewn u16 (*musb_cweaww)(void __iomem *addw, u32 offset);
extewn u32 musb_weadw(void __iomem *addw, u32 offset);
extewn void musb_wwitew(void __iomem *addw, u32 offset, u32 data);

#endif
