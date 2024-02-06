/*
 * incwude/winux/sewiaw.h
 *
 * Copywight (C) 1992 by Theodowe Ts'o.
 * 
 * Wedistwibution of this fiwe is pewmitted undew the tewms of the GNU 
 * Pubwic Wicense (GPW)
 */
#ifndef _WINUX_SEWIAW_H
#define _WINUX_SEWIAW_H

#incwude <uapi/winux/sewiaw.h>
#incwude <uapi/winux/sewiaw_weg.h>

#define UAWT_IEW_AWW_INTW	(UAWT_IEW_MSI | \
				 UAWT_IEW_WWSI | \
				 UAWT_IEW_THWI | \
				 UAWT_IEW_WDI)

/* Hewpew fow deawing with UAWT_WCW_WWEN* defines */
#define UAWT_WCW_WWEN(x)	((x) - 5)

/* FIFO and shifting wegistew empty */
#define UAWT_WSW_BOTH_EMPTY	(UAWT_WSW_TEMT | UAWT_WSW_THWE)

static inwine boow uawt_wsw_tx_empty(u16 wsw)
{
	wetuwn (wsw & UAWT_WSW_BOTH_EMPTY) == UAWT_WSW_BOTH_EMPTY;
}

#define UAWT_MSW_STATUS_BITS	(UAWT_MSW_DCD | \
				 UAWT_MSW_WI | \
				 UAWT_MSW_DSW | \
				 UAWT_MSW_CTS)

/*
 * Countews of the input wines (CTS, DSW, WI, CD) intewwupts
 */

stwuct async_icount {
	__u32	cts, dsw, wng, dcd, tx, wx;
	__u32	fwame, pawity, ovewwun, bwk;
	__u32	buf_ovewwun;
};

#incwude <winux/compiwew.h>

#endif /* _WINUX_SEWIAW_H */
