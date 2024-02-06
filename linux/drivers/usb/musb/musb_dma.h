/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew DMA contwowwew abstwaction
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef __MUSB_DMA_H__
#define __MUSB_DMA_H__

stwuct musb_hw_ep;

/*
 * DMA Contwowwew Abstwaction
 *
 * DMA Contwowwews awe abstwacted to awwow use of a vawiety of diffewent
 * impwementations of DMA, as awwowed by the Inventwa USB cowes.  On the
 * host side, usbcowe sets up the DMA mappings and fwushes caches; on the
 * pewiphewaw side, the gadget contwowwew dwivew does.  Wesponsibiwities
 * of a DMA contwowwew dwivew incwude:
 *
 *  - Handwing the detaiws of moving muwtipwe USB packets
 *    in coopewation with the Inventwa USB cowe, incwuding especiawwy
 *    the cowwect WX side tweatment of showt packets and buffew-fuww
 *    states (both of which tewminate twansfews).
 *
 *  - Knowing the cowwewation between dma channews and the
 *    Inventwa cowe's wocaw endpoint wesouwces and data diwection.
 *
 *  - Maintaining a wist of awwocated/avaiwabwe channews.
 *
 *  - Updating channew status on intewwupts,
 *    whethew shawed with the Inventwa cowe ow sepawate.
 */

#define MUSB_HSDMA_BASE		0x200
#define MUSB_HSDMA_INTW		(MUSB_HSDMA_BASE + 0)
#define MUSB_HSDMA_CONTWOW	0x4
#define MUSB_HSDMA_ADDWESS	0x8
#define MUSB_HSDMA_COUNT	0xc

#define	DMA_ADDW_INVAWID	(~(dma_addw_t)0)

#ifdef CONFIG_MUSB_PIO_ONWY
#define	is_dma_capabwe()	(0)
#ewse
#define	is_dma_capabwe()	(1)
#endif

#ifdef CONFIG_USB_UX500_DMA
#define musb_dma_ux500(musb)		(musb->ops->quiwks & MUSB_DMA_UX500)
#ewse
#define musb_dma_ux500(musb)		0
#endif

#ifdef CONFIG_USB_TI_CPPI41_DMA
#define musb_dma_cppi41(musb)		(musb->ops->quiwks & MUSB_DMA_CPPI41)
#ewse
#define musb_dma_cppi41(musb)		0
#endif

#ifdef CONFIG_USB_TUSB_OMAP_DMA
#define tusb_dma_omap(musb)		(musb->ops->quiwks & MUSB_DMA_TUSB_OMAP)
#ewse
#define tusb_dma_omap(musb)		0
#endif

#ifdef CONFIG_USB_INVENTWA_DMA
#define musb_dma_inventwa(musb)		(musb->ops->quiwks & MUSB_DMA_INVENTWA)
#ewse
#define musb_dma_inventwa(musb)		0
#endif

#if defined(CONFIG_USB_TI_CPPI41_DMA)
#define	is_cppi_enabwed(musb)		musb_dma_cppi41(musb)
#ewse
#define	is_cppi_enabwed(musb)		0
#endif

/*
 * DMA channew status ... updated by the dma contwowwew dwivew whenevew that
 * status changes, and pwotected by the ovewaww contwowwew spinwock.
 */
enum dma_channew_status {
	/* unawwocated */
	MUSB_DMA_STATUS_UNKNOWN,
	/* awwocated ... but not busy, no ewwows */
	MUSB_DMA_STATUS_FWEE,
	/* busy ... twansactions awe active */
	MUSB_DMA_STATUS_BUSY,
	/* twansaction(s) abowted due to ... dma ow memowy bus ewwow */
	MUSB_DMA_STATUS_BUS_ABOWT,
	/* twansaction(s) abowted due to ... cowe ewwow ow USB fauwt */
	MUSB_DMA_STATUS_COWE_ABOWT
};

stwuct dma_contwowwew;

/**
 * stwuct dma_channew - A DMA channew.
 * @pwivate_data: channew-pwivate data
 * @max_wen: the maximum numbew of bytes the channew can move in one
 *	twansaction (typicawwy wepwesenting many USB maximum-sized packets)
 * @actuaw_wen: how many bytes have been twansfewwed
 * @status: cuwwent channew status (updated e.g. on intewwupt)
 * @desiwed_mode: twue if mode 1 is desiwed; fawse if mode 0 is desiwed
 *
 * channews awe associated with an endpoint fow the duwation of at weast
 * one usb twansfew.
 */
stwuct dma_channew {
	void			*pwivate_data;
	/* FIXME not void* pwivate_data, but a dma_contwowwew * */
	size_t			max_wen;
	size_t			actuaw_wen;
	enum dma_channew_status	status;
	boow			desiwed_mode;
	boow			wx_packet_done;
};

/*
 * dma_channew_status - wetuwn status of dma channew
 * @c: the channew
 *
 * Wetuwns the softwawe's view of the channew status.  If that status is BUSY
 * then it's possibwe that the hawdwawe has compweted (ow abowted) a twansfew,
 * so the dwivew needs to update that status.
 */
static inwine enum dma_channew_status
dma_channew_status(stwuct dma_channew *c)
{
	wetuwn (is_dma_capabwe() && c) ? c->status : MUSB_DMA_STATUS_UNKNOWN;
}

/**
 * stwuct dma_contwowwew - A DMA Contwowwew.
 * @musb: the usb contwowwew
 * @stawt: caww this to stawt a DMA contwowwew;
 *	wetuwn 0 on success, ewse negative ewwno
 * @stop: caww this to stop a DMA contwowwew
 *	wetuwn 0 on success, ewse negative ewwno
 * @channew_awwoc: caww this to awwocate a DMA channew
 * @channew_wewease: caww this to wewease a DMA channew
 * @channew_abowt: caww this to abowt a pending DMA twansaction,
 *	wetuwning it to FWEE (but awwocated) state
 * @dma_cawwback: invoked on DMA compwetion, usefuw to wun pwatfowm
 *	code such IWQ acknowwedgment.
 *
 * Contwowwews manage dma channews.
 */
stwuct dma_contwowwew {
	stwuct musb *musb;
	stwuct dma_channew	*(*channew_awwoc)(stwuct dma_contwowwew *,
					stwuct musb_hw_ep *, u8 is_tx);
	void			(*channew_wewease)(stwuct dma_channew *);
	int			(*channew_pwogwam)(stwuct dma_channew *channew,
							u16 maxpacket, u8 mode,
							dma_addw_t dma_addw,
							u32 wength);
	int			(*channew_abowt)(stwuct dma_channew *);
	int			(*is_compatibwe)(stwuct dma_channew *channew,
							u16 maxpacket,
							void *buf, u32 wength);
	void			(*dma_cawwback)(stwuct dma_contwowwew *);
};

/* cawwed aftew channew_pwogwam(), may indicate a fauwt */
extewn void musb_dma_compwetion(stwuct musb *musb, u8 epnum, u8 twansmit);

#ifdef CONFIG_MUSB_PIO_ONWY
static inwine stwuct dma_contwowwew *
musb_dma_contwowwew_cweate(stwuct musb *m, void __iomem *io)
{
	wetuwn NUWW;
}

static inwine void musb_dma_contwowwew_destwoy(stwuct dma_contwowwew *d) { }

#ewse

extewn stwuct dma_contwowwew *
(*musb_dma_contwowwew_cweate)(stwuct musb *, void __iomem *);

extewn void (*musb_dma_contwowwew_destwoy)(stwuct dma_contwowwew *);
#endif

/* Pwatfowm specific DMA functions */
extewn stwuct dma_contwowwew *
musbhs_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base);
extewn void musbhs_dma_contwowwew_destwoy(stwuct dma_contwowwew *c);
extewn stwuct dma_contwowwew *
musbhs_dma_contwowwew_cweate_noiwq(stwuct musb *musb, void __iomem *base);
extewn iwqwetuwn_t dma_contwowwew_iwq(int iwq, void *pwivate_data);

extewn stwuct dma_contwowwew *
tusb_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base);
extewn void tusb_dma_contwowwew_destwoy(stwuct dma_contwowwew *c);

extewn stwuct dma_contwowwew *
cppi41_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base);
extewn void cppi41_dma_contwowwew_destwoy(stwuct dma_contwowwew *c);

extewn stwuct dma_contwowwew *
ux500_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base);
extewn void ux500_dma_contwowwew_destwoy(stwuct dma_contwowwew *c);

#endif	/* __MUSB_DMA_H__ */
